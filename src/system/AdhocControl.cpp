/* The ad hoc connection object file (retail 0x0882d0 to 0x088b58): the object that brings
   the console's wireless ad hoc networking up and down. It initialises the network
   libraries, scans for other consoles on the configured channel, joins the game's group and
   tracks the progress through a state number that the library's event handler advances.
   The single instance is D_241e98; the static data's start and exit entries end the file
   (0x088b18). The function at 0x0882d0 before it returns an empty name. */

#include <stdlib.h>
#include <string.h>

extern "C" {
int sceNetInit(int poolsize, int calloutprio, int calloutstack, int netintrprio, int netintrstack);
int sceNetTerm(void);
int sceNetAdhocInit(void);
int sceNetAdhocTerm(void);
int sceNetAdhocctlInit(int stacksize, int priority, void *adhocid);
int sceNetAdhocctlTerm(void);
int sceNetAdhocctlAddHandler(void (*handler)(int, int, void *), void *arg);
int sceNetAdhocctlDelHandler(int id);
int sceNetAdhocctlScan(void);
int sceNetAdhocctlConnect(const char *name);
int sceNetAdhocctlDisconnect(void);
int sceNetAdhocctlGetState(int *state);
int sceNetAdhocctlGetScanInfo(int *size, void *buf);
int sceUtilityGetSystemParamInt(int id, int *value);
int sceKernelDelayThread(unsigned int usec);
char *f_10bdac(void);
}

/* The game's ad hoc id: the type and the product code. */
struct AdhocId {
    int type;
    char product[9];
};
extern AdhocId D_1d3d24;

/* The group name joined. */
extern char D_1d3d34[];

/* The network session object (D_241810, another object file): told about connection errors. */
struct NetSession {
    void f_085514();
    void f_085530(int error);
};
extern NetSession D_241810;

/* One entry of the scan result list. */
struct ScanInfo {
    ScanInfo *next;
    int channel;
};

/* The states:
   0 down, 1 initialised, 2 scanning, 3 scanned, 4 connecting, 5 connected, 6 disconnecting,
   7 disconnected, 8 connection failed, 9 disconnecting after a failure, 10 disconnected after
   a failure, 11 error. */
class CAdhocControl {
public:
    CAdhocControl();
    ~CAdhocControl();

    AdhocId *f_08832c();
    int f_088338();
    int f_088340();
    void f_088348(int s);
    void f_088350();
    void f_088390(int event, int error, void *arg);
    void f_0884cc();
    int f_0884f0();
    int f_088664();
    int f_0886c0();
    int f_0887a8();
    int f_0888c8();
    void f_0889d0();
    void f_088a10();

    int state;
    int handler;
    int events;
    int error;
    int found;
    int channel;
    bool started;
    bool joining;
};

CAdhocControl D_241e98;

/* @implements 0x0882d0 us f_0882d0
   WHAT IT DOES: Returns an empty name. */
const char *f_0882d0()
{
    return "";
}

/* @implements 0x0882dc us _ZN13CAdhocControlC2Ev
   WHAT IT DOES: Starts in state 0 with everything cleared. */
/* @implements 0x0882fc us _ZN13CAdhocControlC1Ev
   WHAT IT DOES: The complete-object copy of the constructor above. */
CAdhocControl::CAdhocControl()
{
    state = 0;
    f_0884cc();
}

/* @implements 0x08831c us _ZN13CAdhocControlD2Ev
   WHAT IT DOES: Nothing to release. */
/* @implements 0x088324 us _ZN13CAdhocControlD1Ev
   WHAT IT DOES: The complete-object copy of the destructor above. */
CAdhocControl::~CAdhocControl()
{
}

/* @implements 0x08832c us f_08832c
   WHAT IT DOES: Returns the game's ad hoc id. */
AdhocId *CAdhocControl::f_08832c()
{
    return &D_1d3d24;
}

/* @implements 0x088338 us f_088338
   WHAT IT DOES: Returns the state. */
int CAdhocControl::f_088338()
{
    return state;
}

/* @implements 0x088340 us f_088340
   WHAT IT DOES: Returns the number of consoles the last scan found on the channel. */
int CAdhocControl::f_088340()
{
    return found;
}

/* @implements 0x088348 us f_088348
   WHAT IT DOES: Sets the state. */
void CAdhocControl::f_088348(int s)
{
    state = s;
}

/* @implements 0x088350 us f_088350
   WHAT IT DOES: Forgets the events seen and the last error. */
void CAdhocControl::f_088350()
{
    events = 0;
    error = 0;
}

/* @implements 0x08835c us f_08835c
   WHAT IT DOES: The library's event handler: passes the event to the object. */
void f_08835c(int event, int error, void *arg)
{
    D_241e98.f_088390(event, error, arg);
}

/* @implements 0x088390 us f_088390
   WHAT IT DOES: Records a library event (as a flag bit) and advances the state: an error
   moves to the failure states (and tells the session), a connection completes a connect, a
   disconnection completes a disconnect, a finished scan is noted for f_0888c8. */
void CAdhocControl::f_088390(int event, int err, void *arg)
{
    switch (event) {
    case 0:
        events |= 1;
        error = err;
        switch (err) {
        case (int)0x80410b03:
        case (int)0x80410d0c:
            f_088348(8);
            D_241810.f_085514();
            break;
        default:
            D_241810.f_085530(err);
            f_088348(11);
            break;
        }
        break;
    case 1:
        events |= 2;
        error = 0;
        if (f_088338() == 4)
            f_088348(5);
        break;
    case 2:
        events |= 4;
        error = 0;
        joining = 0;
        if (f_088338() == 6)
            f_088348(7);
        else if (f_088338() == 9)
            f_088348(10);
        break;
    case 3:
        events |= 8;
        error = 0;
        break;
    }
}

/* @implements 0x0884cc us f_0884cc
   WHAT IT DOES: Clears the object: no handler, no events, no channel, not started. */
void CAdhocControl::f_0884cc()
{
    handler = -1;
    events = 0;
    error = 0;
    found = -1;
    started = 0;
    joining = 0;
    channel = -1;
}

/* @implements 0x0884f0 us f_0884f0
   WHAT IT DOES: Brings ad hoc networking up: the network, ad hoc and ad hoc control libraries
   (with the game's product code), the event handler and the channel from the system
   settings (11 when automatic), then starts a scan. On a failure it shuts everything down
   again and returns the error. */
int CAdhocControl::f_0884f0()
{
    int r;
    f_0884cc();
    r = sceNetInit(0x20000, 16, 0x2000, 16, 0x2000);
    if (r < 0)
        goto fail;
    r = sceNetAdhocInit();
    if (r < 0)
        goto fail;
    started = 1;
    memcpy(D_1d3d24.product, f_10bdac(), 9);
    r = sceNetAdhocctlInit(0x4000, 18, &D_1d3d24);
    if (r < 0)
        goto fail;
    f_088348(1);
    f_088350();
    r = sceNetAdhocctlAddHandler(f_08835c, 0);
    if (r < 0)
        goto fail;
    handler = r;
    channel = 0;
    r = sceUtilityGetSystemParamInt(2, &channel);
    if (r < 0)
        goto fail;
    if (channel == 0)
        channel = 11;
    return f_088664();
fail:
    f_088a10();
    return r;
}

/* @implements 0x088664 us f_088664
   WHAT IT DOES: Starts a scan for other consoles (state 2; 11 when it cannot start). */
int CAdhocControl::f_088664()
{
    f_088348(2);
    int r = sceNetAdhocctlScan();
    if (r < 0)
        f_088348(11);
    return r;
}

/* @draft 0x0886c0 us f_0886c0
   WHAT IT DOES: Joins the game's group, bringing networking up first when it is down.
   Returns 1 when the connect started, 0x80000021 while busy, or a library error.
   Remaining difference: on a failed connect retail clears the joining flag before copying
   the error into the result register (this source copies first; two words). */
int CAdhocControl::f_0886c0()
{
    int s, st, r, c;
    if (f_088338() == 0) {
        int e = f_0884f0();
        if (e < 0)
            return e;
    }
    s = f_088338();
    if (s == 2)
        goto busy;
    if (s == 4)
        goto busy;
    if (s == 5)
        goto busy;
    if (s == 6)
        goto busy;
    r = sceNetAdhocctlGetState(&st);
    if (r < 0)
        return r;
    if (st != 0 && st != 2)
        return 0x80000021;
    f_088348(4);
    joining = 1;
    c = sceNetAdhocctlConnect(D_1d3d34);
    if (c >= 0)
        return 1;
    joining = 0;
    return c;
busy:
    return 0x80000021;
}

/* @draft 0x0887a8 us f_0887a8
   WHAT IT DOES: Leaves the group and waits until the library reports the disconnection.
   Returns 1 after waiting, 0 when there was nothing to wait for, or a library error.
   Remaining difference: retail keeps the result in a0 (this source gets a1), and loads the
   constant 9 for the wait loop before the joining flag store. */
int CAdhocControl::f_0887a8()
{
    if (f_088338() == 9) {
        while (f_088338() == 9)
            sceKernelDelayThread(1000);
        return 1;
    }
    int s = f_088338();
    if (s == 3) {
        f_088348(7);
        return 0;
    }
    if (!joining) {
        if (s == 8)
            f_088348(10);
        else if (s == 6)
            f_088348(7);
        return 0;
    }
    if (s == 8)
        f_088348(9);
    else
        f_088348(6);
    int r = sceNetAdhocctlDisconnect();
    if (r < 0) {
        joining = 0;
        return r;
    }
    joining = 0;
    for (;;) {
        s = f_088338();
        if (s == 6) {
            sceKernelDelayThread(1000);
            continue;
        }
        if (s == 9) {
            sceKernelDelayThread(1000);
            continue;
        }
        return 1;
    }
}

/* @implements 0x0888c8 us f_0888c8
   WHAT IT DOES: After a finished scan, counts the consoles found on the configured channel
   (state 3). Returns 1 when counted, 0 while the scan runs or when it failed with a
   connection error (state 9), or a library error. */
int CAdhocControl::f_0888c8()
{
    if (!(events & 8))
        return 0;
    if (error == (int)0x80410d0c) {
        found = -1;
        f_088348(9);
        return 0;
    }
    int size = 0;
    int r = sceNetAdhocctlGetScanInfo(&size, 0);
    if (r < 0)
        return r;
    found = 0;
    if (size != 0) {
        ScanInfo *buf = (ScanInfo *)malloc(size);
        r = sceNetAdhocctlGetScanInfo(&size, buf);
        if (r < 0) {
            free(buf);
            return r;
        }
        for (ScanInfo *p = buf; p != 0; p = p->next)
            if (p->channel == channel)
                found++;
        free(buf);
    }
    f_088348(3);
    return 1;
}

/* @implements 0x0889d0 us f_0889d0
   WHAT IT DOES: Per frame: while scanning, checks for the scan result. */
void CAdhocControl::f_0889d0()
{
    if (f_088338() == 2)
        f_0888c8();
}

/* @implements 0x088a10 us f_088a10
   WHAT IT DOES: Takes ad hoc networking down: leaves the group, removes the handler and shuts
   the libraries down; then returns to state 0 unless a failure state (10, 11) is kept. */
void CAdhocControl::f_088a10()
{
    f_0887a8();
    if (started) {
        if (handler >= 0) {
            sceNetAdhocctlDelHandler(handler);
            handler = -1;
        }
        sceNetAdhocctlTerm();
        sceNetAdhocTerm();
        sceNetTerm();
    }
    started = 0;
    int s = f_088338();
    if (s != 10 && s != 11)
        f_088348(0);
}

/* @implements 0x088aa4 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the ad hoc object; at exit, destroys it. */

/* @implements 0x088b18 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x088b38 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
