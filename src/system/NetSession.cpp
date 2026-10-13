/* The network session object file (retail 0x085344 to 0x088290): the wireless game session
   built on the ad hoc matching library. One console hosts (mode 0) and the others join it
   (mode 1). The host keeps the member table (eight 40-byte entries, entry 0 being itself),
   numbers the members, and sends the table, its own state and the session record to
   everyone over a PDP socket on port 12345; the clients ask to join, follow the host's
   table, and time members out when the matching library no longer lists them. The single
   instance is D_241810; its static data's start and exit entries follow the file
   (0x088290, 0x0882b0). */

#include <string.h>

extern "C" {
int sceKernelWaitSema(int id, int signal, unsigned int *timeout);
int sceKernelSignalSema(int id, int signal);
int sceKernelCreateSema(const char *name, unsigned int attr, int init, int max, void *opt);
int sceKernelDeleteSema(int id);
unsigned int sceKernelGetSystemTimeLow(void);
int sceNetGetLocalEtherAddr(char *mac);
int sceNetAdhocPdpCreate(char *mac, unsigned short port, unsigned int bufsize, int flag);
int sceNetAdhocPdpSend(int id, const char *to, unsigned short port, const void *data,
                       unsigned int len, unsigned int timeout, int flag);
int sceNetAdhocPdpRecv(int id, char *from, unsigned short *port, void *data, int *len,
                       unsigned int timeout, int flag);
int sceNetAdhocPdpDelete(int id, int flag);
int sceNetAdhocMatchingInit(int poolsize);
int sceNetAdhocMatchingTerm(void);
int sceNetAdhocMatchingCreate(int mode, int maxpeers, unsigned short port, int bufsize,
                              unsigned int hello, unsigned int ping, int resend,
                              unsigned int msgdelay, void (*handler)(int, int, unsigned char *, int, void *));
int sceNetAdhocMatchingStart(int id, int prio, int stack, int hprio, int hstack, int optlen,
                             void *opt);
int sceNetAdhocMatchingStop(int id);
int sceNetAdhocMatchingDelete(int id);
int sceNetAdhocMatchingSelectTarget(int id, const char *mac, int optlen, void *opt);
int sceNetAdhocMatchingCancelTarget(int id, const char *mac);
int sceNetAdhocMatchingSetHelloOpt(int id, int optlen, void *opt);
int sceNetAdhocMatchingGetMembers(int id, int *len, void *buf);
int sceNetAdhocMatchingGetPoolMaxAlloc(void);
int iprintf(const char *fmt, ...);
}

/* The ad hoc connection object (D_241e98, AdhocControl.cpp). */
class CAdhocControl {
public:
    int f_088338();
    int f_088340();
    int f_0884f0();
    int f_0886c0();
    void f_0889d0();
    void f_088a10();
};
extern CAdhocControl D_241e98;

/* The game packet processor (D_241760, GamePacketProc.cpp): takes a game packet. */
struct GamePacketProc;
extern GamePacketProc D_241760;
extern "C" void f_083328(GamePacketProc *p, char *from, int type, void *data, int size);

/* The broadcast address. */
extern char D_1d3d1c[];

/* One member of the matching library's member list. */
struct Member {
    Member *next;
    char mac[6];
    char pad[2];
};

/* The session record a console announces (28 bytes): its flags, its MAC address and its
   member number. */
struct Rec {
    int m0;
    int m4;
    char m8;
    char m9;
    char m10;
    char m11;
    char mac[6];
    char m18;
    unsigned char m19;
    int m20;
    int m24;
};

/* A member table entry (40 bytes): the member's record and its timers. */
struct Entry {
    int m0;
    int m4;
    char m8;
    char m9;
    char m10;
    char m11;
    char mac[6];
    char m18;
    unsigned char m19;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
};

/* The 8-byte member state packet. */
struct StatePacket {
    int m20;
    char m10;
    char m19;
};

class CNetSession {
public:
    CNetSession();
    ~CNetSession();

    void f_0853e8();
    void ResetTimers() { for (int i = 0; i < 8; i++) timer[i] = 30000000; }
    void f_0854ec(int s);
    void f_0854f4(char v);
    void f_0854fc(char v);
    char f_085504();
    char f_08550c();
    void f_085514();
    void f_085530(int error);
    void f_085590(int id, int event, unsigned char *mac, int optlen, void *opt);
    void f_085638(int id, int event, unsigned char *mac, int optlen, void *opt);
    void f_08570c(int id, int event, unsigned char *mac, int optlen, void *opt);
    void f_0858a8();
    Entry *f_0858f4();
    Rec *f_085928(const char *mac);
    int f_0859b4();
    void f_0859e0();
    Entry *f_085a1c(int n);
    int f_085a58(int n);
    Entry *f_085a9c(const char *mac, bool self);
    void f_085b28();
    Rec *f_085b64(Rec *r);
    int f_085c30(Rec *r);
    int f_085cc0(const char *mac);
    void f_085d50();
    Entry *f_085d74(Entry *r);
    int f_085e30(Entry *r);
    int f_085ed0(char tag);
    int f_085f58(char tag);
    int f_085f90(Rec *r);
    int f_0860ac(Rec *r);
    int f_086170(Entry *r);
    int f_086274(Entry *r);
    int f_086324();
    int f_086350(Member *buf);
    bool f_08640c();
    void f_086440();
    void f_086470();
    bool f_0864c8();
    void f_0864ec();
    bool f_08651c();
    int f_086528(bool b);
    int f_086598(int v, bool self);
    int f_0865e8();
    int f_086608();
    int f_0866a4(const char *to, void *data, int len);
    int f_086744(const char *to, int type, void *data, int len);
    int f_0867b8(const char *to, int type, int header, void *data, int len);
    int f_086830(char *from, unsigned short *port, void *buf, int *len);
    int f_086908();
    int f_086968();
    int f_086a60(const char *to, int header, void *data, int len);
    int f_086a8c();
    int f_086ab8();
    int f_086afc();
    int f_086b40();
    int f_086b84();
    int f_086bb0();
    int f_086bec();
    int f_086c50();
    int f_086cb4();
    void f_086d0c(char *from, char *data, unsigned int len);
    void f_086e8c(char *from, char *data, int len);
    void f_086fa8(char *from, char *data, int len);
    void f_08704c(char *from, char *data, int len);
    void f_0870e8(char *from, char *data, int len);
    int f_087130();
    int f_0872fc();
    int f_087318(int mode, Rec *r, Entry *e);
    int f_08748c();
    int f_087648();
    void f_087688();
    void f_0876c4();
    void f_087718();
    int f_087760();
    int f_0877a8(bool quick);
    int f_0878b4();
    int f_0879d8();
    int f_087ac4(bool v);
    int f_087b68();
    int f_087bf4();
    int f_087cb4();
    int f_087d0c();
    int f_087e08();
    int f_087e44();
    int f_087ee8();
    int f_087f34();
    void f_088138();
    void f_0881ec();

    int state;              /* 0 */
    int mode;               /* 4: 0 host, 1 client */
    bool m8;
    bool running;           /* 9 */
    bool m10;
    bool m11;
    int sema;               /* 12 */
    int matching;           /* 16 */
    int pdp;                /* 20 */
    int last;               /* 24 */
    int dt;                 /* 28 */
    int m32;
    int m36;
    int m40;
    int m44;
    int timer[8];           /* 48 */
    bool m80;
    bool m81;
    Rec self;               /* 84 */
    Rec pend[2];            /* 112 */
    Entry ent[8];           /* 168 */
    Entry req[4];           /* 488 */
    char rbuf[512];         /* 648 */
    char sbuf[512];         /* 1160 */
};

/* @implements 0x085344 us f_085344
   WHAT IT DOES: Tells whether a MAC address is in a member list. */
int f_085344(Member *m, const char *mac)
{
    while (m) {
        if (memcmp(m->mac, mac, 6) == 0)
            return 1;
        m = m->next;
    }
    return 0;
}

CNetSession D_241810;

/* @implements 0x0853a0 us _ZN11CNetSessionC2Ev
   WHAT IT DOES: Constructs the session: clears it. */
/* @implements 0x0853bc us _ZN11CNetSessionC1Ev
   WHAT IT DOES: The complete-object copy of the constructor above. */
/* @implements 0x0853d8 us _ZN11CNetSessionD2Ev
   WHAT IT DOES: Nothing to release. */
/* @implements 0x0853e0 us _ZN11CNetSessionD1Ev
   WHAT IT DOES: The complete-object copy of the destructor above. */
CNetSession::CNetSession()
{
    f_0853e8();
}

CNetSession::~CNetSession()
{
}

/* @implements 0x0853e8 us f_0853e8
   WHAT IT DOES: Clears the session: state 0, host mode, no semaphore or socket, every timer
   at 30 s, an empty member table and empty packet buffers. */
void CNetSession::f_0853e8()
{
    int i;
    state = 0;
    mode = 0;
    m8 = 1;
    running = 0;
    m11 = 0;
    sema = -1;
    matching = 0;
    last = 0;
    dt = 0;
    m32 = 0;
    m36 = 0;
    m44 = 0;
    m40 = 0;
    m10 = 1;
    pdp = -1;
    ResetTimers();
    m81 = 0;
    m80 = 0;
    memset(&self, 0, sizeof self);
    f_085b28();
    memset(ent, 0, sizeof ent);
    for (i = 0; i < 8; i++)
        ent[i].m11 = -1;
    f_085d50();
    memset(sbuf, 0, sizeof sbuf);
    memset(rbuf, 0, sizeof rbuf);
}

/* @implements 0x0854ec us f_0854ec
   WHAT IT DOES: Sets the state. */
void CNetSession::f_0854ec(int s)
{
    state = s;
}

/* @implements 0x0854f4 us f_0854f4
   WHAT IT DOES: Sets this console's member status. */
void CNetSession::f_0854f4(char v)
{
    ent[0].m10 = v;
}

/* @implements 0x0854fc us f_0854fc
   WHAT IT DOES: Sets the session status announced. */
void CNetSession::f_0854fc(char v)
{
    self.m9 = v;
}

/* @implements 0x085504 us f_085504
   WHAT IT DOES: Returns this console's member status. */
char CNetSession::f_085504()
{
    return ent[0].m10;
}

/* @implements 0x08550c us f_08550c
   WHAT IT DOES: Returns the session status. */
char CNetSession::f_08550c()
{
    return self.m9;
}

/* @implements 0x085514 us f_085514
   WHAT IT DOES: Moves to the failure state 10. */
void CNetSession::f_085514()
{
    f_0854ec(10);
}

/* @implements 0x085530 us f_085530
   WHAT IT DOES: Moves to the failure state 10 on a connection error. */
void CNetSession::f_085530(int error)
{
    f_0854ec(10);
}

/* @implements 0x08554c us f_08554c
   WHAT IT DOES: The matching library's event handler: passes the event to the session. */
void f_08554c(int id, int event, unsigned char *mac, int optlen, void *opt)
{
    D_241810.f_085590(id, event, mac, optlen, opt);
}

/* @implements 0x085590 us f_085590
   WHAT IT DOES: Handles a matching event under the session's semaphore, as the host or as a
   client. */
void CNetSession::f_085590(int id, int event, unsigned char *mac, int optlen, void *opt)
{
    f_085ed0('E');
    if (mode == 0)
        f_085638(id, event, mac, optlen, opt);
    else
        f_08570c(id, event, mac, optlen, opt);
    f_085f58('E');
}

/* @draft 0x085638 us f_085638
   WHAT IT DOES: The host's matching events: a join request is queued; a member that leaves,
   times out or says goodbye is dropped from the table and the members renumbered. */
void CNetSession::f_085638(int id, int event, unsigned char *mac, int optlen, void *opt)
{
    Entry *e;
    switch (event) {
    case 2:
        e = f_085d74((Entry *)opt);
        if (e)
            *e = *(Entry *)opt;
        break;
    case 3:
    case 8:
    case 10:
        e = f_085a9c((char *)mac, 0);
        if (e) {
            e->m18 = 0;
            f_0859e0();
            m36 = 0;
        }
        break;
    }
}

/* @implements 0x08570c us f_08570c
   WHAT IT DOES: A client's matching events: hellos list or forget the hosts seen, the host
   leaving ends the session, a refusal or an acceptance answers the join, and a host lost
   clears the joined flag. */
void CNetSession::f_08570c(int id, int event, unsigned char *mac, int optlen, void *opt)
{
    Rec *r;
    switch (event) {
    case 1:
        if (optlen == 0) {
            f_085cc0((char *)mac);
        } else if (optlen == 28) {
            r = f_085b64((Rec *)opt);
            if (r)
                *r = *(Rec *)opt;
        }
        break;
    case 3:
        if (memcmp(self.mac, mac, 6) == 0)
            f_0854ec(9);
        break;
    case 4:
        self.m10 = 0;
        f_0854ec(4);
        break;
    case 6:
        m32 = 30000000;
        self = *(Rec *)opt;
        self.m10 = 1;
        f_0854ec(5);
        break;
    case 8:
    case 10:
        if (memcmp(self.mac, mac, 6) == 0) {
            Entry *e;
            self.m10 = 0;
            e = f_085a9c((char *)mac, 0);
            if (e)
                e->m18 = 0;
        }
        break;
    }
}

/* @implements 0x0858a8 us f_0858a8
   WHAT IT DOES: Empties the member table except entry 0. */
void CNetSession::f_0858a8()
{
    int i;
    for (i = 1; i < 8; i++) {
        memset(&ent[i], 0, sizeof ent[i]);
        ent[i].m11 = -1;
    }
}

/* @implements 0x0858f4 us f_0858f4
   WHAT IT DOES: Returns a free member table entry (not entry 0), or 0. */
Entry *CNetSession::f_0858f4()
{
    int i;
    for (i = 1; i < 8; i++)
        if (!ent[i].m18)
            return &ent[i];
    return 0;
}

/* @implements 0x085928 us f_085928
   WHAT IT DOES: Finds a host seen with the given MAC address. */
Rec *CNetSession::f_085928(const char *mac)
{
    int i;
    for (i = 0; i < 2; i++)
        if (pend[i].m10 && memcmp(pend[i].mac, mac, 6) == 0)
            return &pend[i];
    return 0;
}

/* @implements 0x0859b4 us f_0859b4
   WHAT IT DOES: Counts the members in the table. */
int CNetSession::f_0859b4()
{
    int i, n = 0;
    for (i = 0; i < 8; i++)
        n += ent[i].m18 != 0;
    return n;
}

/* @implements 0x0859e0 us f_0859e0
   WHAT IT DOES: Numbers the members: this console 0, the others from 1 in table order; keeps
   the member count in the session record. */
void CNetSession::f_0859e0()
{
    int i, n = 1;
    ent[0].m11 = 0;
    for (i = 1; i < 8; i++) {
        if (ent[i].m18)
            ent[i].m11 = n++;
        else
            ent[i].m11 = -1;
    }
    self.m19 = n;
}

/* @draft 0x085a1c us f_085a1c
   WHAT IT DOES: Returns the member with the given number, or 0. */
Entry *CNetSession::f_085a1c(int n)
{
    int i;
    for (i = 0; i < 8; i++)
        if (ent[i].m18 && ent[i].m11 == n)
            return &ent[i];
    return 0;
}

/* @draft 0x085a58 us f_085a58
   WHAT IT DOES: Returns the table index of the other member with the given number, or -1. */
int CNetSession::f_085a58(int n)
{
    int i;
    for (i = 1; i < 8; i++)
        if (ent[i].m18 && ent[i].m11 == n)
            return i;
    return -1;
}

/* @draft 0x085a9c us f_085a9c
   WHAT IT DOES: Finds a member by MAC address, entry 0 included only when asked. */
Entry *CNetSession::f_085a9c(const char *mac, bool self)
{
    int i;
    for (i = !self; i < 8; i++)
        if (ent[i].m18 && memcmp(mac, ent[i].mac, 6) == 0)
            return &ent[i];
    return 0;
}

/* @implements 0x085b28 us f_085b28
   WHAT IT DOES: Forgets the hosts seen. */
void CNetSession::f_085b28()
{
    memset(pend, 0, sizeof pend);
}

/* @draft 0x085b64 us f_085b64
   WHAT IT DOES: Returns the slot of a host seen with the record's address, else a free slot,
   else 0. */
Rec *CNetSession::f_085b64(Rec *r)
{
    int i;
    for (i = 0; i < 2; i++)
        if (pend[i].m10 == 1 && memcmp(pend[i].mac, r->mac, 6) == 0)
            return &pend[i];
    for (i = 0; i < 2; i++)
        if (!pend[i].m10)
            return &pend[i];
    return 0;
}

/* @implements 0x085c30 us f_085c30
   WHAT IT DOES: Forgets the host seen with the record's address; tells whether there was one. */
int CNetSession::f_085c30(Rec *r)
{
    int i, found = 0;
    for (i = 0; i < 2; i++) {
        if (pend[i].m10 == 1 && memcmp(pend[i].mac, r->mac, 6) == 0) {
            pend[i].m10 = 0;
            found = 1;
        }
    }
    return found;
}

/* @implements 0x085cc0 us f_085cc0
   WHAT IT DOES: Forgets the host seen with the given address; tells whether there was one. */
int CNetSession::f_085cc0(const char *mac)
{
    int i, found = 0;
    for (i = 0; i < 2; i++) {
        if (pend[i].m10 == 1 && memcmp(pend[i].mac, mac, 6) == 0) {
            pend[i].m10 = 0;
            found = 1;
        }
    }
    return found;
}

/* @implements 0x085d50 us f_085d50
   WHAT IT DOES: Empties the join request queue. */
void CNetSession::f_085d50()
{
    memset(req, 0, sizeof req);
}

/* @draft 0x085d74 us f_085d74
   WHAT IT DOES: Returns the queued request from the entry's address, else a free slot, else 0. */
Entry *CNetSession::f_085d74(Entry *r)
{
    int i;
    for (i = 0; i < 4; i++)
        if (req[i].m18 == 1 && memcmp(req[i].mac, r->mac, 6) == 0)
            return &req[i];
    for (i = 0; i < 4; i++)
        if (!req[i].m18)
            return &req[i];
    return 0;
}

/* @implements 0x085e30 us f_085e30
   WHAT IT DOES: Removes the queued request from the entry's address; tells whether there was
   one. */
int CNetSession::f_085e30(Entry *r)
{
    int i;
    if (!r)
        return 0;
    for (i = 0; i < 4; i++) {
        if (req[i].m18 == 1 && memcmp(req[i].mac, r->mac, 6) == 0) {
            req[i].m18 = 0;
            return 1;
        }
    }
    return 0;
}

/* @draft 0x085ed0 us f_085ed0
   WHAT IT DOES: Takes the session semaphore (0.1 s timeout); reports a timeout with the
   caller's tag. */
int CNetSession::f_085ed0(char tag)
{
    unsigned int timeout = 100000;
    int r;
    if (sema < 0)
        return 0;
    r = sceKernelWaitSema(sema, 1, &timeout);
    if (timeout == 0)
        iprintf("sema %c timeout! %d, rv=%08x\n", tag, 0, r);
    return r;
}

/* @implements 0x085f58 us f_085f58
   WHAT IT DOES: Releases the session semaphore. */
int CNetSession::f_085f58(char tag)
{
    if (sema < 0)
        return 0;
    return sceKernelSignalSema(sema, 1);
}

/* @draft 0x085f90 us f_085f90
   WHAT IT DOES: Asks a host seen to let this console join (a record without the host flag
   means go back to the host list). */
int CNetSession::f_085f90(Rec *r)
{
    int ret;
    if (!r->m10) {
        f_0854ec(4);
        return 1;
    }
    if (state < 2 || state >= 7)
        return 0;
    if (D_241e98.f_088338() != 5)
        return 0;
    f_0854ec(3);
    m32 = 30000000;
    ret = sceNetAdhocMatchingSelectTarget(matching, r->mac, 40, &ent[0]);
    if (ret < 0) {
        f_085c30(r);
        return ret;
    }
    f_085c30(r);
    self = *r;
    return 1;
}

/* @draft 0x0860ac us f_0860ac
   WHAT IT DOES: Withdraws a join request to a host. */
int CNetSession::f_0860ac(Rec *r)
{
    int ret;
    if (!r->m10)
        return 1;
    if (state < 2 || state >= 7)
        return 0;
    if (D_241e98.f_088338() != 5)
        return 0;
    ret = sceNetAdhocMatchingCancelTarget(matching, r->mac);
    if (ret < 0) {
        f_085c30(r);
        return ret;
    }
    f_085c30(r);
    self.m10 = 0;
    f_0854ec(2);
    return 1;
}

/* @implements 0x086170 us f_086170
   WHAT IT DOES: The host accepts a queued join request: the member goes into the table. */
int CNetSession::f_086170(Entry *r)
{
    int ret;
    Entry *e;
    if (!r->m18)
        return 1;
    if (state != 8)
        return 0;
    if (D_241e98.f_088338() != 5)
        return 0;
    ret = sceNetAdhocMatchingSelectTarget(matching, r->mac, 28, &self);
    if (ret < 0) {
        f_085e30(r);
        return ret;
    }
    e = f_0858f4();
    if (e)
        *e = *r;
    f_085e30(r);
    return 1;
}

/* @implements 0x086274 us f_086274
   WHAT IT DOES: The host refuses a queued join request. */
int CNetSession::f_086274(Entry *r)
{
    int ret;
    if (!r->m18)
        return 1;
    if (state != 8)
        return 0;
    if (D_241e98.f_088338() != 5)
        return 0;
    ret = sceNetAdhocMatchingCancelTarget(matching, r->mac);
    if (ret < 0) {
        f_085e30(r);
        return ret;
    }
    f_085e30(r);
    return 1;
}

/* @draft 0x086324 us f_086324
   WHAT IT DOES: Tells whether the session is up (state 6 or 8). */
int CNetSession::f_086324()
{
    if (state == 6 || state == 8)
        return 1;
    return 0;
}

/* @draft 0x086350 us f_086350
   WHAT IT DOES: Reads the matching library's member list (at most 16 members) into a buffer;
   an empty list when the session is not up. */
int CNetSession::f_086350(Member *buf)
{
    if ((state == 5 || state == 6 || state == 8) && D_241e98.f_088338() == 5) {
        int len = 0;
        int r = sceNetAdhocMatchingGetMembers(matching, &len, 0);
        if (r < 0)
            return r;
        if ((unsigned int)len > 192)
            return 0;
        r = sceNetAdhocMatchingGetMembers(matching, &len, buf);
        if (r < 0)
            return r;
        return 1;
    }
    buf->next = 0;
    return 0;
}

/* @implements 0x08640c us f_08640c
   WHAT IT DOES: The host's flag 10 as host, else whether the session status is 0. */
bool CNetSession::f_08640c()
{
    if (mode == 0)
        return m10;
    return f_08550c() == 0;
}

/* @implements 0x086440 us f_086440
   WHAT IT DOES: Sets the session status 5 and announces it. */
void CNetSession::f_086440()
{
    f_0854fc(5);
    f_086cb4();
}

/* @implements 0x086470 us f_086470
   WHAT IT DOES: As host, sets the session status and this console's member status to 4 and
   announces both. */
void CNetSession::f_086470()
{
    if (mode != 0)
        return;
    f_0854fc(4);
    f_086cb4();
    f_0854f4(4);
    f_086b40();
}

/* @implements 0x0864c8 us f_0864c8
   WHAT IT DOES: Tells whether the session status is 4. */
bool CNetSession::f_0864c8()
{
    return f_08550c() == 4;
}

/* @implements 0x0864ec us f_0864ec
   WHAT IT DOES: Sets this console's member status to 4 and announces it. */
void CNetSession::f_0864ec()
{
    f_0854f4(4);
    f_086b40();
}

/* @implements 0x08651c us f_08651c
   WHAT IT DOES: Tells whether this console has joined a host. */
bool CNetSession::f_08651c()
{
    return self.m10 != 0;
}

/* @draft 0x086528 us f_086528
   WHAT IT DOES: Sets this console's member status to 3 (ready) or 0 and announces the table;
   nothing to do when it is already so. */
int CNetSession::f_086528(bool b)
{
    if (b) {
        if (f_085504() == 3)
            return 1;
        f_0854f4(3);
    } else {
        if (!f_085504())
            return 1;
        f_0854f4(0);
    }
    return f_086afc();
}

/* @draft 0x086598 us f_086598
   WHAT IT DOES: Tells whether every member (this console included only when asked) has the
   given member status. */
int CNetSession::f_086598(int v, bool self)
{
    int i;
    for (i = !self; i < 8; i++)
        if (ent[i].m18 && ent[i].m10 != v)
            return 0;
    return 1;
}

/* @implements 0x0865e8 us f_0865e8
   WHAT IT DOES: Tells whether all the other members are ready. */
int CNetSession::f_0865e8()
{
    return f_086598(3, 0);
}

/* @implements 0x086608 us f_086608
   WHAT IT DOES: Opens the PDP socket on port 12345 (closing an open one first). */
int CNetSession::f_086608()
{
    char mac[8];
    int r;
    if (D_241e98.f_088338() != 5)
        return -1;
    if (pdp >= 0) {
        r = f_086908();
        if (r < 0)
            return r;
    }
    r = sceNetGetLocalEtherAddr(mac);
    if (r < 0)
        return r;
    pdp = sceNetAdhocPdpCreate(mac, 12345, 8192, 0);
    if (pdp < 0)
        return r;
    return 1;
}

/* @draft 0x0866a4 us f_0866a4
   WHAT IT DOES: Sends data to an address on port 12345. */
int CNetSession::f_0866a4(const char *to, void *data, int len)
{
    int r = 0;
    if (pdp < 0)
        return r;
    if (D_241e98.f_088338() == 5) {
        r = sceNetAdhocPdpSend(pdp, to, 12345, data, len, 0, 0);
        if (r >= 0)
            r = 1;
    }
    return r;
}

/* @implements 0x086744 us f_086744
   WHAT IT DOES: Sends a packet: the type byte, three 1 bytes, then the data. */
int CNetSession::f_086744(const char *to, int type, void *data, int len)
{
    sbuf[0] = type;
    sbuf[1] = 1;
    sbuf[2] = 1;
    sbuf[3] = 1;
    memcpy(sbuf + 4, data, len);
    return f_0866a4(to, sbuf, len + 4);
}

/* @draft 0x0867b8 us f_0867b8
   WHAT IT DOES: Sends a packet: the type byte, the header's low three bytes high first, then
   the data. */
int CNetSession::f_0867b8(const char *to, int type, int header, void *data, int len)
{
    sbuf[0] = type;
    sbuf[1] = header >> 16;
    sbuf[2] = header >> 8;
    sbuf[3] = header;
    memcpy(sbuf + 4, data, len);
    return f_0866a4(to, sbuf, len + 4);
}

/* @draft 0x086830 us f_086830
   WHAT IT DOES: Receives a packet without waiting: its length, 0 when there is none, or the
   error. */
int CNetSession::f_086830(char *from, unsigned short *port, void *buf, int *len)
{
    int r = 0;
    if (pdp < 0)
        return r;
    if (D_241e98.f_088338() == 5) {
        r = sceNetAdhocPdpRecv(pdp, from, port, buf, len, 0, 1);
        switch (r) {
        case (int)0x80410709:
        case (int)0x80410715:
            *len = 0;
            return 0;
        }
        if (r < 0)
            return r;
        return *len;
    }
    return r;
}

/* @implements 0x086908 us f_086908
   WHAT IT DOES: Closes the PDP socket. */
int CNetSession::f_086908()
{
    int r = 0;
    if (pdp >= 0) {
        r = sceNetAdhocPdpDelete(pdp, 0);
        if (r < 0) {
            pdp = -1;
            return r;
        }
        pdp = -1;
        r = 1;
    }
    return r;
}

/* @draft 0x086968 us f_086968
   WHAT IT DOES: Broadcasts the member table (type 0): every member's entry. */
int CNetSession::f_086968()
{
    int i, len = 4;
    char *d = sbuf + 4;
    sbuf[0] = 0;
    sbuf[1] = 0;
    sbuf[2] = 0;
    sbuf[3] = 0;
    for (i = 0; i < 8; i++) {
        if (ent[i].m18) {
            memcpy(d, &ent[i], sizeof(Entry));
            len += sizeof(Entry);
            d += sizeof(Entry);
        }
    }
    return f_0866a4(D_1d3d1c, sbuf, len);
}

/* @implements 0x086a60 us f_086a60
   WHAT IT DOES: Sends a game packet (type 5) with its header. */
int CNetSession::f_086a60(const char *to, int header, void *data, int len)
{
    return f_0867b8(to, 5, header, data, len);
}

/* @implements 0x086a8c us f_086a8c
   WHAT IT DOES: Broadcasts this console's member entry (type 2). */
int CNetSession::f_086a8c()
{
    return f_086744(D_1d3d1c, 2, &ent[0], sizeof(Entry));
}

/* @implements 0x086ab8 us f_086ab8
   WHAT IT DOES: Broadcasts this console's member state (type 4). */
int CNetSession::f_086ab8()
{
    StatePacket p;
    p.m20 = ent[0].m20;
    p.m10 = ent[0].m10;
    p.m19 = ent[0].m19;
    return f_086744(D_1d3d1c, 4, &p, sizeof p);
}

/* @implements 0x086afc us f_086afc
   WHAT IT DOES: Broadcasts this console's member entry, at most once every 180 frames (a
   later request is flagged for f_087718). */
int CNetSession::f_086afc()
{
    if (m44) {
        m81 = 1;
        return 1;
    }
    m44 = 180;
    m81 = 0;
    return f_086a8c();
}

/* @implements 0x086b40 us f_086b40
   WHAT IT DOES: Broadcasts this console's member state, at most once every 180 frames. */
int CNetSession::f_086b40()
{
    if (m44) {
        m81 = 1;
        return 1;
    }
    m44 = 180;
    m81 = 0;
    return f_086ab8();
}

/* @implements 0x086b84 us f_086b84
   WHAT IT DOES: Broadcasts the session record (type 1). */
int CNetSession::f_086b84()
{
    return f_086744(D_1d3d1c, 1, &self, sizeof self);
}

/* @implements 0x086bb0 us f_086bb0
   WHAT IT DOES: Broadcasts the session status (type 3). */
int CNetSession::f_086bb0()
{
    char p[2];
    p[0] = self.m9;
    p[1] = self.m11;
    return f_086744(D_1d3d1c, 3, p, 2);
}

/* @draft 0x086bec us f_086bec
   WHAT IT DOES: As a listening host, sets the matching hello data to the session record (or
   none). */
int CNetSession::f_086bec()
{
    int r;
    if (state != 8)
        return 0;
    if (m10)
        r = sceNetAdhocMatchingSetHelloOpt(matching, 28, &self);
    else
        r = sceNetAdhocMatchingSetHelloOpt(matching, 0, 0);
    if (r < 0)
        return r;
    return 1;
}

/* @draft 0x086c50 us f_086c50
   WHAT IT DOES: Updates the hello data and broadcasts the session record, at most once every
   180 frames. */
int CNetSession::f_086c50()
{
    f_086bec();
    if (m40) {
        m36 = 5000000;
        m80 = 1;
        return 1;
    }
    m40 = 180;
    m80 = 0;
    return f_086b84();
}

/* @implements 0x086cb4 us f_086cb4
   WHAT IT DOES: Updates the hello data and broadcasts the session status, at most once every
   180 frames. */
int CNetSession::f_086cb4()
{
    f_086bec();
    if (m40) {
        m80 = 1;
        return 1;
    }
    m40 = 180;
    m80 = 0;
    return f_086bb0();
}

/* @draft 0x086d0c us f_086d0c
   WHAT IT DOES: A client takes the member table from its host: rebuilds its table from the
   entries, takes its own number, and announces itself again if its entry differs. */
void CNetSession::f_086d0c(char *from, char *data, unsigned int len)
{
    unsigned int n;
    int i;
    Entry *e;
    if (mode == 0)
        return;
    if (!self.m10)
        return;
    if (memcmp(from, self.mac, 6) != 0)
        return;
    n = len / 40;
    if ((len % 40 != 0) | (n > 8))
        return;
    for (i = 1; i < 8; i++)
        ent[i].m18 = 0;
    if (n == 0)
        return;
    for (e = (Entry *)data; n; n--, e++) {
        if (memcmp(ent[0].mac, e->mac, 6) == 0) {
            ent[0].m11 = e->m11;
            if (memcmp(&ent[0], e, 40) != 0)
                f_086a8c();
        } else {
            Entry *f = f_0858f4();
            if (f)
                *f = *e;
        }
    }
}

/* @implements 0x086e8c us f_086e8c
   WHAT IT DOES: Takes a member's entry (type 2) into the table. */
void CNetSession::f_086e8c(char *from, char *data, int len)
{
    int i;
    if (len != 40)
        return;
    for (i = 1; i < 8; i++) {
        if (ent[i].m18 && memcmp(ent[i].mac, from, 6) == 0) {
            memcpy(&ent[i], data, 40);
            return;
        }
    }
}

/* @implements 0x086fa8 us f_086fa8
   WHAT IT DOES: Takes a member's state (type 4) into the table. */
void CNetSession::f_086fa8(char *from, char *data, int len)
{
    int i;
    if (len != 8)
        return;
    for (i = 1; i < 8; i++) {
        if (ent[i].m18 && memcmp(ent[i].mac, from, 6) == 0) {
            ent[i].m10 = data[4];
            ent[i].m19 = data[5];
            ent[i].m20 = *(int *)data;
            return;
        }
    }
}

/* @implements 0x08704c us f_08704c
   WHAT IT DOES: Takes the host's session record (type 1). */
void CNetSession::f_08704c(char *from, char *data, int len)
{
    if (len == 28)
        memcpy(&self, data, 28);
}

/* @implements 0x0870e8 us f_0870e8
   WHAT IT DOES: Takes the host's session status (type 3). */
void CNetSession::f_0870e8(char *from, char *data, int len)
{
    if (len == 2) {
        f_0854fc(data[0]);
        self.m11 = data[1];
    }
}

/* @implements 0x087130 us f_087130
   WHAT IT DOES: Receives one packet and hands it on by its type (0 member table, 1 session
   record, 2 member entry, 3 session status, 4 member state, 5 game packet), ignoring
   consoles that are neither members nor the host; returns 0 when there was none. */
int CNetSession::f_087130()
{
    char from[8];
    unsigned short port = 0;
    int len = 512;
    int r, i, known;
    r = f_086830(from, &port, rbuf, &len);
    if (r <= 0)
        return r;
    known = 0;
    for (i = 0; i < 8; i++) {
        if (ent[i].m18 && memcmp(ent[i].mac, from, 6) == 0) {
            known = 1;
            break;
        }
    }
    if (memcmp(self.mac, from, 6) == 0)
        known = 1;
    if (!known)
        return 1;
    int type = rbuf[0];
    int header = (((rbuf[1] << 8) + rbuf[2]) << 8) + rbuf[3];
    switch (type) {
    case 0:
        f_086d0c(from, rbuf + 4, len - 4);
        break;
    case 1:
        f_08704c(from, rbuf + 4, len - 4);
        break;
    case 2:
        f_086e8c(from, rbuf + 4, len - 4);
        break;
    case 3:
        f_0870e8(from, rbuf + 4, len - 4);
        break;
    case 4:
        f_086fa8(from, rbuf + 4, len - 4);
        break;
    case 5:
        f_083328(&D_241760, from, header, rbuf + 4, len - 4);
        break;
    case 6:
        break;
    }
    return 1;
}

/* @implements 0x0872fc us f_0872fc
   WHAT IT DOES: Returns the matching library's largest pool allocation. */
int CNetSession::f_0872fc()
{
    return sceNetAdhocMatchingGetPoolMaxAlloc();
}

/* @implements 0x087318 us f_087318
   WHAT IT DOES: Starts a session as host (mode 0) or client with the given session record
   and member entry: clears everything, makes the entry member 0, and brings ad hoc
   networking up (or starts matching at once when it is already up). */
int CNetSession::f_087318(int m, Rec *r, Entry *e)
{
    int i;
    f_0853e8();
    mode = m;
    self = *r;
    self.m19 = 1;
    for (i = 0; i < 8; i++) {
        ent[i].m18 = 0;
        ent[i].m11 = -1;
    }
    ent[0] = *e;
    ent[0].m18 = 1;
    ent[0].m32 = ent[0].m28 = -1;
    ent[0].m36 = 0;
    m32 = 0;
    ResetTimers();
    if (D_241e98.f_088338() == 5)
        return f_08748c();
    f_0854ec(1);
    D_241e98.f_0884f0();
    return 1;
}

/* @draft 0x08748c us f_08748c
   WHAT IT DOES: Starts matching: opens the socket, creates the semaphore, initialises the
   matching library and creates and starts the context (host or client); the host then
   listens (state 8), a client looks for hosts (state 2). A failure ends the session. */
int CNetSession::f_08748c()
{
    int r;
    m10 = 1;
    if (running)
        return 0;
    f_085b28();
    f_085d50();
    f_0858a8();
    m36 = 0;
    sceNetGetLocalEtherAddr(ent[0].mac);
    r = f_086608();
    if (r < 0)
        goto fail;
    if (sema < 0) {
        r = sceKernelCreateSema("NPI", 0, 1, 255, 0);
        if (r < 0)
            goto fail;
        sema = r;
    }
    r = sceNetAdhocMatchingInit(0x8000);
    if (r < 0)
        goto fail;
    m8 = 1;
    int mm;
    if (mode == 0) {
        self.m10 = 1;
        ent[0].m11 = 0;
        sceNetGetLocalEtherAddr(self.mac);
        mm = 1;
    } else {
        self.m10 = 0;
        mm = 2;
    }
    r = sceNetAdhocMatchingCreate(mm, 8, 1, 16384, 1000000, 5000000, 6, 500000, f_08554c);
    if (r < 0)
        goto fail;
    matching = r;
    r = sceNetAdhocMatchingStart(matching, 17, 16384, 16, 16384, 28, &self);
    if (r < 0)
        goto fail;
    running = 1;
    if (mode == 0) {
        f_0854f4(1);
        f_0854ec(8);
    } else {
        f_0854ec(2);
    }
    return 1;
fail:
    f_088138();
    f_0854ec(10);
    return r;
}

/* @implements 0x087648 us f_087648
   WHAT IT DOES: Stops the matching context. */
int CNetSession::f_087648()
{
    int r;
    if (!running)
        return 1;
    running = 0;
    r = sceNetAdhocMatchingStop(matching);
    if (r < 0)
        return r;
    return 1;
}

/* @implements 0x087688 us f_087688
   WHAT IT DOES: Measures the time since the last call. */
void CNetSession::f_087688()
{
    int t = sceKernelGetSystemTimeLow();
    if (last)
        dt = t - last;
    last = t;
}

/* @implements 0x0876c4 us f_0876c4
   WHAT IT DOES: A client's announce throttle: sends a held back session record when the wait
   runs out. */
void CNetSession::f_0876c4()
{
    if (mode)
        return;
    if (m40 > 0 && --m40 == 0 && m80) {
        m40 = 180;
        m80 = 0;
        f_086b84();
    }
}

/* @implements 0x087718 us f_087718
   WHAT IT DOES: Sends a held back member entry when the wait runs out. */
void CNetSession::f_087718()
{
    if (m44 > 0 && --m44 == 0 && m81) {
        m44 = 180;
        m81 = 0;
        f_086a8c();
    }
}

/* @implements 0x087760 us f_087760
   WHAT IT DOES: Ends the session when its status is 9 (closed). */
int CNetSession::f_087760()
{
    if (f_08550c() == 9) {
        f_088138();
        return 1;
    }
    return 0;
}

/* @implements 0x0877a8 us f_0877a8
   WHAT IT DOES: A client's watch on the host: while the matching library lists the host and
   this console, the timers are reset; when either is missing for 30 s (or 1 s for the host
   when asked) the session ends (state 9). */
int CNetSession::f_0877a8(bool quick)
{
    Member buf[16];
    int k = quick ? 1000000 : 30000000;
    int r;
    if (!running)
        return 0;
    r = f_086350(buf);
    if (r < 0)
        return r;
    if (f_085344(buf, self.mac))
        m32 = 1000000;
    else if ((m32 -= dt) < 0) {
        f_088138();
        m32 = 30000000;
        f_0854ec(9);
        return 1;
    }
    if (f_085344(buf, ent[0].mac))
        timer[0] = k;
    else if ((timer[0] -= dt) < 0) {
        f_088138();
        timer[0] = 30000000;
        f_0854ec(9);
        return 1;
    }
    return 1;
}

/* @draft 0x0878b4 us f_0878b4
   WHAT IT DOES: The host's join requests: accepts the first one queued while listening with
   room, else refuses it; closes the session when the table is full and reopens it when
   there is room again. */
int CNetSession::f_0878b4()
{
    int i;
    for (i = 0; i < 4; i++) {
        Entry *q = &req[i];
        if (q->m18) {
            if (running && m10 && f_0858f4()) {
                f_086170(&req[i]);
                f_0859e0();
                f_086bec();
                m36 = 0;
                return 1;
            }
            f_086274(q);
            return 1;
        }
    }
    if (m10 && f_0859b4() >= 8)
        f_087ac4(0);
    if (!m10 && !m11 && f_0859b4() < 8)
        f_087b68();
    return 1;
}

/* @implements 0x0879d8 us f_0879d8
   WHAT IT DOES: The host's watch on its members: one the matching library no longer lists
   for 30 s is dropped and the members renumbered. */
int CNetSession::f_0879d8()
{
    Member buf[16];
    int i, r;
    if (!running)
        return 0;
    r = f_086350(buf);
    if (r < 0)
        return r;
    for (i = 1; i < 8; i++) {
        if (ent[i].m18) {
            if (f_085344(buf, ent[i].mac))
                timer[i] = 1000000;
            else if ((timer[i] -= dt) < 0) {
                timer[i] = 30000000;
                ent[i].m18 = 0;
                f_0859e0();
                m36 = 0;
            }
        }
    }
    return 1;
}

/* @draft 0x087ac4 us f_087ac4
   WHAT IT DOES: The host stops taking members (status 2): no hello data. */
int CNetSession::f_087ac4(bool v)
{
    int r;
    if (mode != 0)
        return 0;
    m11 = v;
    m10 = 0;
    if (state < 2 || state >= 9)
        return 0;
    if (D_241e98.f_088338() != 5)
        return 0;
    r = sceNetAdhocMatchingSetHelloOpt(matching, 0, 0);
    if (r < 0)
        return r;
    f_0854fc(2);
    return f_086b84();
}

/* @draft 0x087b68 us f_087b68
   WHAT IT DOES: The host takes members again (status 0): the session record as hello data. */
int CNetSession::f_087b68()
{
    m10 = 1;
    m11 = 0;
    if (state < 2 || state >= 9)
        return 0;
    if (D_241e98.f_088338() != 5)
        return 0;
    f_086bec();
    f_0854fc(0);
    return f_086b84();
}

/* @implements 0x087bf4 us f_087bf4
   WHAT IT DOES: A joined client's frame: watches the host, and once the table it holds has
   as many members as the session record and the matching library lists them all, marks
   itself ready (status 1) and goes on to state 6. */
int CNetSession::f_087bf4()
{
    Member buf[16];
    Member *p;
    int n;
    f_087718();
    f_0877a8(0);
    if (f_087760())
        return 1;
    if (!self.m10)
        return 0;
    if (f_0859b4() != self.m19)
        return 0;
    if (f_086350(buf) < 0)
        return 0;
    n = 0;
    p = buf;
    do {
        p = p->next;
        n++;
    } while (p);
    if (self.m19 != n)
        return 0;
    f_0854f4(1);
    f_086b40();
    f_0854ec(6);
    return 0;
}

/* @implements 0x087cb4 us f_087cb4
   WHAT IT DOES: Leaves the session (state 9) while connected. */
int CNetSession::f_087cb4()
{
    if (D_241e98.f_088338() == 5) {
        f_088138();
        f_0854ec(9);
    }
    return 1;
}

/* @draft 0x087d0c us f_087d0c
   WHAT IT DOES: Waits for ad hoc networking to come up: starts matching once connected, and
   fails on the states that cannot lead there. */
int CNetSession::f_087d0c()
{
    switch (D_241e98.f_088338()) {
    case 3:
        if (mode == 0) {
            if (D_241e98.f_088340() > 0)
                f_0854ec(11);
            else
                D_241e98.f_0886c0();
        } else if (mode == 1) {
            if (D_241e98.f_088340() > 0)
                D_241e98.f_0886c0();
            else
                f_0854ec(12);
        }
    case 2:
    case 4:
        return 1;
    case 0:
    case 1:
        break;
    case 5:
        return f_08748c();
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
        f_088138();
        break;
    }
    f_0854ec(10);
    return 1;
}

/* @implements 0x087e08 us f_087e08
   WHAT IT DOES: A client's frame in the session. */
int CNetSession::f_087e08()
{
    f_087718();
    f_0877a8(1);
    f_087760();
    return 1;
}

/* @implements 0x087e44 us f_087e44
   WHAT IT DOES: The host's frame in the session: throttled announcements, join requests, the
   member watch, and every 5 s the session record and table for everyone. */
int CNetSession::f_087e44()
{
    f_0876c4();
    f_087718();
    f_0878b4();
    f_0879d8();
    if ((m36 -= dt) < 0) {
        if (f_0859b4() >= 2) {
            f_086b84();
            f_086968();
        }
        f_086bec();
        m36 = 5000000;
    }
    f_087760();
    return 1;
}

/* @implements 0x087ee8 us f_087ee8
   WHAT IT DOES: Waits for the join answer; gives up (state 4) when the wait runs out. */
int CNetSession::f_087ee8()
{
    if ((m32 -= dt) < 0) {
        f_0854ec(4);
        m32 = 0;
    }
    return 1;
}

/* @draft 0x087f34 us f_087f34
   WHAT IT DOES: The session's frame: follows ad hoc networking (ending the session on a
   failure), takes every packet received, then runs the state's step. */
int CNetSession::f_087f34()
{
    D_241e98.f_0889d0();
    switch (state) {
    case 0:
        return 1;
    case 9:
        return f_087cb4();
    case 10:
        if (D_241e98.f_088338() == 8 || D_241e98.f_088338() == 11)
            f_088138();
        return 1;
    case 11:
    case 12:
        return 1;
    }
    f_087688();
    if (D_241e98.f_088338() == 8) {
        f_088138();
        return 1;
    }
    if (D_241e98.f_088338() == 11 && D_241810.state != 10)
        goto fail;
    if (D_241e98.f_088338() != 2 && D_241e98.f_088338() != 3 && D_241e98.f_088338() != 4
        && D_241e98.f_088338() != 5)
        goto fail;
    while (f_087130() > 0)
        ;
    switch (state) {
    case 1:
        return f_087d0c();
    case 3:
        return f_087ee8();
    case 5:
        return f_087bf4();
    case 6:
        return f_087e08();
    case 8:
        return f_087e44();
    }
    return 1;
fail:
    f_088138();
    f_0854ec(10);
    return 1;
}

/* @implements 0x088138 us f_088138
   WHAT IT DOES: Ends the session: closes the socket, stops and deletes the matching context,
   ends the matching library, deletes the semaphore, empties the table and takes ad hoc
   networking down. */
void CNetSession::f_088138()
{
    f_086908();
    f_087648();
    if (matching > 0) {
        sceNetAdhocMatchingDelete(matching);
        matching = 0;
    }
    if (m8) {
        sceNetAdhocMatchingTerm();
        m8 = 0;
    }
    if (sema >= 0) {
        f_085f58('9');
        sceKernelDeleteSema(sema);
        sema = -1;
    }
    f_0854ec(0);
    self.m19 = 1;
    mode = 0;
    f_0858a8();
    D_241e98.f_088a10();
}

/* @implements 0x0881ec us f_0881ec
   WHAT IT DOES: Ends the session in the failure state 10. */
void CNetSession::f_0881ec()
{
    f_088138();
    f_0854ec(10);
}

/* @implements 0x08821c us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the session object; at exit, destroys it. */

/* @implements 0x088290 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0882b0 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
