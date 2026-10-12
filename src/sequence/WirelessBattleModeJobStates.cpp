/* The wireless battle mode job, from its Step (retail 0x00ddf8 to 0x0117c4, then the class's
   inline methods emitted out of line at 0x0117c4 to 0x0117fc): the game mode that runs ad hoc
   races between consoles, with the lobby, the race entry, the result exchange and the memory
   stick checks around them. Like every mode job it is a state machine: a table of 41 member
   functions, one per state, a queue of state events and a small script interpreter (in the
   base class) that decides the next state. The constructors and Begin come before this, at the
   end of the previous object file (0x00d8e8 and 0x00dd64); Begin is defined here because it is
   the class's key function, which makes this file emit the vtable and the destructors. The
   vtable (_ZTVN8Sequence22CWirelessBattleModeJobE) names Begin, Step, End, the state runner and
   the event sender at 0x01172c and 0x011794. */

#include <string.h>

extern "C" {
int f_0160fc(void);
int f_016168(void);
}

/* The main loop job, as far as this file reads it. */
struct MainLoopJobView {
    char m0[11];
    bool m11;
    bool paused;
};
extern MainLoopJobView *D_1d88a0;

/* The front end's screen manager. Its first member is the object running the current screen,
   called through its vtable. */
class CScreen {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(void *msg, int arg);
    virtual void v3(void *msg, int arg);
};
struct ScreenMgr {
    CScreen *screen;
    int m4[3];
    int phase;
    bool Ready() { return phase == 4; }
};
extern ScreenMgr D_2301b0;
void f_017bfc(ScreenMgr *);
void f_017c88(ScreenMgr *);
void f_018b48(ScreenMgr *);
CScreen *f_017970(void);

/* The ad hoc network session. */
struct NetSession {
    int state;
    int m4;
};
extern NetSession D_241810;
extern char D_241e98[];
void f_085ed0(NetSession *, int);
void f_087f34(NetSession *);
void f_085f58(NetSession *, int);
void f_088138(NetSession *);
int f_088338(void *);
int f_086324(NetSession *);
int f_08651c(NetSession *);
int f_08550c(NetSession *);
int f_0865e8(NetSession *);
void f_086470(NetSession *);
void f_086440(NetSession *);

/* The race settings shared with the race itself. */
struct RaceSettings {
    int m0[6];
    int m24[336];
    int m1368[336];
    char p2712[14848 - 2712];
    int m14848;
    int m14852;
    int m14856;
    char p14860[15468 - 14860];
    int m15468;
    char p15472[15684 - 15472];
    int m15684;
    char p15688[15700 - 15688];
    int m15700;
    char p15704[15716 - 15704];
    char m15716[12];
    int m15728;
};
extern RaceSettings D_233f70;

/* The memory stick state. */
struct MemoryStick {
    int m0;
    char m4[3];
    unsigned char m7;
};
extern MemoryStick D_23ba90;
int f_01a900(MemoryStick *);
void f_01a91c(MemoryStick *, int);
int f_01abf4(MemoryStick *);
void f_01bb3c(MemoryStick *);
int f_01bc5c(MemoryStick *);

/* The system message dialog. */
extern char D_2451f4[];
void f_099718(void *dialog, int);
void f_0997ac(void *dialog, int);
int f_0998d0(void *dialog);

/* The sound and music player. */
extern char D_1dd6b0[];
void f_005554(void *, int);
int f_0056d0(void *);
void f_005720(void *);
void f_0057d0(void *);

void f_07a314(void *);
void f_07a390(void *);
void f_07a88c(void *);
void f_07a908(void *);

/* The reply the lobby screen fills in about the race settings chosen. */
struct LobbyReply {
    LobbyReply() { f_07a314(this); }
    ~LobbyReply() { f_07a390(this); }
    int m0[5];
    int m20;
    int m24[65];
    int m284;
    int m288[4];
};

void f_07a9d8(void *);
void f_07aa54(void *);

/* A request to the screen manager to open a screen. */
struct ScreenReq {
    ScreenReq() { f_07a9d8(this); }
    ~ScreenReq() { f_07aa54(this); }
    int m0[2];
    unsigned char m8;
    int m12;
    unsigned char m16;
    unsigned char m17;
    unsigned char m18;
    int m20[3];
};

/* A request to the lobby's message screen. */
struct LobbyMsg {
    LobbyMsg() { f_07a88c(this); }
    ~LobbyMsg() { f_07a908(this); }
    int m0[5];
    int m20;
    int m24[2];
};

extern "C" {
int f_006018(void);
int f_0160bc(void);
int f_015ce4(void);
void f_015204(void);
void f_0156d4(void);
void f_015ed8(void);
void f_016138(void);
void f_0161b8(void);
void f_016220(void);
int f_0194c4(void);
int f_014a08(void);
int f_014a28(void);
}

extern int D_237cc8;
extern unsigned char D_237cfc;

/* This object file's own data: the two racers of a wireless battle (names, name pointers and
   per racer values) and the state of the session. */
unsigned char D_1ee088;
char D_1ee0c4[2][8];
char *D_1ee0d4[2];
int D_1ee0dc[2];
int D_1ee0e4[2];
int D_1ee0ec[2];
int D_1ee0f4[2];
int D_1ee0fc[2];
int D_1ee104[2];
int D_1ee10c;
int D_1ee110;
unsigned char D_1ee114;
int D_1ee118;
int D_1ee11c;
unsigned char D_1ee120;
char D_1ee124[28];
struct Entry {
    char name[20];
    unsigned int m20a : 15;
    unsigned int m20b : 1;
    unsigned int m20c : 16;
};
Entry D_1ee140;
int D_1ee168;
int D_1ee16c;
int D_1ee170;

/* The pad: buttons held (with repeat) and buttons newly pressed. */
namespace Controller {
class CCustomController {
public:
    int Held(int mask) { return held & mask; }
    int Trig(int mask) { return pressed & mask; }
    int m0[2];
    int held;
    int m12;
    int pressed;
};
}
extern Controller::CCustomController D_1d8910[1];

/* The network race's message display. */
extern char D_242cb0[];
void f_096408(char *);
void f_096434(char *, int);
int f_0968e0(char *);
int f_096918(char *);

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
};
}

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
};
}
extern System::CGameModeJob D_1e8ec4;

namespace Sequence {
/* The base of every mode job. Its two virtual functions after the job's own (named here by
   their vtable slot) run a state handler and send the script an event. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int);
    virtual void f_4();
    int f_099948(int state, int event);
};

/* A queue of sixteen state events, read at head and written at tail. */
class CStateQueue {
public:
    CStateQueue() { head = tail = 0; }
    void Push(int v)
    {
        buf[tail++] = v;
        tail &= 15;
    }
    int Pop()
    {
        if (tail == head)
            return -1;
        int v = buf[head++];
        head &= 15;
        return v;
    }
    int buf[16];
    int head;
    int tail;
};

class CWirelessBattleModeJob : public CModeJob {
public:
    typedef void (CWirelessBattleModeJob::*State)();

    CWirelessBattleModeJob();
    virtual ~CWirelessBattleModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int i) { (this->*states[i])(); }
    virtual void f_4() { queue.Push(3); }

    int f_00de58();
    void f_00e068();
    void f_00e084();
    void f_00e12c();
    void f_00e238();

    void f_00e0f4();
    void f_00e0fc();
    void f_00fcb4();
    void f_00e21c();
    void f_00e334();
    void f_00fc68();
    void f_00fc70();
    void f_00fcd8();
    void f_00fd98();
    void f_00fe44();
    void f_00fefc();
    void f_00ff74();
    void f_010100();
    void f_010170();
    void f_010284();
    void f_01028c();
    void f_01031c();
    void f_010378();
    void f_010ac4();
    void f_010b44();
    void f_010b4c();
    void f_011184();
    void f_01118c();
    void f_0111d0();
    void f_01122c();
    void f_011234();
    void f_011254();
    void f_011308();
    void f_011310();
    void f_011334();
    void f_0113cc();
    void f_0113d4();
    void f_011490();
    void f_0114b4();
    void f_01154c();
    void f_011554();
    void f_01157c();
    void f_0115d8();
    void f_0115e0();
    void f_01160c();
    void f_011668();

    int state;
    int m8[11];
    short *m52;
    unsigned char *m56;
    bool m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[41];
    int m472;
    int m476[336];
    int m1820[336];
    int m3164;
    int m3168;
    int m3172;
    int m3176;
    int m3180;
    int m3184;
    int m3188;
    char *m3192;
    int m3196[4];
    signed char m3212;
    bool m3213;
    int m3216;
};
}

int f_00e2c8(void);
void f_00e30c(void);

/* Begin (retail 0x00dd64, object file 16, tagged with that object file's functions): starts
   the mode from its first state, with a copy of the race settings it may change. */
void Sequence::CWirelessBattleModeJob::Begin()
{
    int i;

    m68 = 0;
    for (i = 0; i < 336; i++) {
        m476[i] = D_233f70.m24[i];
        m1820[i] = D_233f70.m1368[i];
    }
    m3192 = D_233f70.m15716;
    m3164 = D_233f70.m14848;
    m60 = 1;
    m3168 = D_233f70.m14852;
    m3172 = D_233f70.m14856;
    m3176 = D_233f70.m15468;
    m3180 = D_233f70.m15684;
    m3184 = D_233f70.m15700;
    m3188 = D_233f70.m15728;
    m64 = 0;
    m68 = 0;
    state = 0;
}

/* @implements 0x00ddf8 us _ZN8Sequence22CWirelessBattleModeJob4StepEv
   WHAT IT DOES: Runs one frame of the mode inside the network session's frame: it opens the
   session's frame, polls the session, runs the mode's frame and closes the session's frame. */
int Sequence::CWirelessBattleModeJob::Step()
{
    f_085ed0(&D_241810, 84);
    f_087f34(&D_241810);
    int r = f_00de58();
    f_085f58(&D_241810, 84);
    return r;
}

/* @implements 0x00de58 us f_00de58
   WHAT IT DOES: One frame of the mode, unless the game is paused: on the first frame of a state
   it sends the script the state's entry event; every frame it sends the update event, letting
   the script react to each queued event, and counts the frames spent in the state. Then,
   depending on the state, it updates the menu screens, or (in two states, while paused) keeps
   the network wait going. */
int Sequence::CWirelessBattleModeJob::f_00de58()
{
    int v;

    if (!D_1d88a0->paused) {
        if (m60) {
            queue.Push(0);
            while ((v = queue.Pop()) >= 0)
                f_099948(m64, v);
        }
        m60 = 0;
        queue.Push(1);
        int s = m64;
        while ((v = queue.Pop()) >= 0)
            f_099948(s, v);
        m68++;
    }
    switch (m64) {
    case 7:
    case 18:
    case 20:
        break;
    case 10:
        if (D_1d88a0->paused)
            f_0160fc();
        break;
    case 11:
        if (D_1d88a0->paused)
            f_016168();
        break;
    default:
        f_018b48(&D_2301b0);
        break;
    }
    return 0;
}

/* @implements 0x00e034 us _ZN8Sequence22CWirelessBattleModeJob3EndEv
   WHAT IT DOES: Leaves the mode: ends the network session and writes back the two race
   settings the mode keeps. */
void Sequence::CWirelessBattleModeJob::End()
{
    f_088138(&D_241810);
    f_00e068();
}

/* @implements 0x00e068 us f_00e068
   WHAT IT DOES: Writes the mode's two kept settings back into the race settings. */
void Sequence::CWirelessBattleModeJob::f_00e068()
{
    D_233f70.m15684 = m3180;
    D_233f70.m15700 = m3184;
}

/* @implements 0x00e084 us f_00e084
   WHAT IT DOES: Asks the lobby screen for the race settings the player chose and keeps the
   course and the second setting. */
void Sequence::CWirelessBattleModeJob::f_00e084()
{
    LobbyReply r;
    D_2301b0.screen->v3(&r, 0);
    m3172 = r.m20;
    m3176 = r.m284;
}

/* @implements 0x00e0f4 us f_00e0f4
   WHAT IT DOES: State 0: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_00e0f4()
{
}

/* @implements 0x00e0fc us f_00e0fc
   WHAT IT DOES: State 1: sends the script event 2. */
void Sequence::CWirelessBattleModeJob::f_00e0fc()
{
    queue.Push(2);
}

/* @implements 0x00e12c us f_00e12c
   WHAT IT DOES: Clears the racers' names and values and the session's counters. */
void Sequence::CWirelessBattleModeJob::f_00e12c()
{
    memset(D_1ee0c4, 0, sizeof(D_1ee0c4));
    memset(D_1ee0d4, 0, sizeof(D_1ee0d4));
    memset(D_1ee0dc, 0, sizeof(D_1ee0dc));
    memset(D_1ee0e4, 0, sizeof(D_1ee0e4));
    memset(D_1ee0ec, 0, sizeof(D_1ee0ec));
    memset(D_1ee0f4, 0, sizeof(D_1ee0f4));
    memset(D_1ee0fc, 0, sizeof(D_1ee0fc));
    memset(D_1ee104, 0, sizeof(D_1ee104));
    D_1ee10c = 0;
    D_1ee110 = 0;
    D_1ee114 = 0;
    D_1ee118 = 0;
    D_1ee11c = 0;
    D_1ee120 = 0;
    D_1ee16c = 0;
    m3213 = 0;
}

/* @implements 0x00e21c us f_00e21c
   WHAT IT DOES: State 3: resets the session and this mode's race data. */
void Sequence::CWirelessBattleModeJob::f_00e21c()
{
    f_00e238();
}

/* @draft 0x00e238 us f_00e238
   WHAT IT DOES: Ends any network session, clears the race data this mode exchanges and puts
   the player's name into both name slots, marking the second slot's entry word.
   Remaining difference: retail sets the entry word at +20 in one read-modify-write (lhu of
   the low half, addu 0xfbe00000, and 0xffff8000, addiu 0x1ff); the bitfield stores here give
   lw/and/ori/sw plus a separate sh of the high half. */
void Sequence::CWirelessBattleModeJob::f_00e238()
{
    f_088138(&D_241810);
    m3216 = 0;
    D_1ee088 = 0;
    f_00e12c();
    strncpy(D_1ee124, m3192, 9);
    strncpy(D_1ee140.name, m3192, 9);
    D_1ee140.m20a = 511;
    D_1ee140.m20c = 0xfbe0;
}

/* @implements 0x00e2c8 us f_00e2c8
   WHAT IT DOES: Tells whether the network link is usable: true when no session is active, or
   when the link is not in one of its three failure states. */
int f_00e2c8(void)
{
    if (!D_1ee088)
        return 1;
    int s = f_088338(D_241e98);
    int failed = s >= 8 && s <= 10;
    return failed == 0;
}

/* @implements 0x00e30c us f_00e30c
   WHAT IT DOES: Ends the network session and marks it inactive. */
void f_00e30c(void)
{
    D_1ee088 = 0;
    f_088138(&D_241810);
}

/* @implements 0x00fc68 us f_00fc68
   WHAT IT DOES: State 5: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_00fc68()
{
}

/* @implements 0x00fc70 us f_00fc70
   WHAT IT DOES: State 6: sends the script event 2 once the screen manager is idle. */
void Sequence::CWirelessBattleModeJob::f_00fc70()
{
    if (D_2301b0.phase == 0)
        queue.Push(2);
}

/* @implements 0x00fcb4 us f_00fcb4
   WHAT IT DOES: State 2: asks the game mode job to switch to mode 1 (the main menu). */
void Sequence::CWirelessBattleModeJob::f_00fcb4()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x00fcd8 us f_00fcd8
   WHAT IT DOES: State 7: sends event 2 when the lobby step is done; if the network session is
   down, stops the sound and sends event 7. */
void Sequence::CWirelessBattleModeJob::f_00fcd8()
{
    if (f_015ce4())
        queue.Push(2);
    if (!f_086324(&D_241810) || !f_08651c(&D_241810)) {
        f_0057d0(D_1dd6b0);
        queue.Push(7);
    }
}

/* @implements 0x00fd98 us f_00fd98
   WHAT IT DOES: State 8: on its first frame starts the lobby screen and its music; later sends
   event 2 once the music has stopped. The screen manager is updated every frame. */
void Sequence::CWirelessBattleModeJob::f_00fd98()
{
    if (m68 == 1) {
        f_005720(D_1dd6b0);
        f_015204();
        f_005554(D_1dd6b0, 1);
    } else if (!f_0056d0(D_1dd6b0)) {
        queue.Push(2);
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x00fe44 us f_00fe44
   WHAT IT DOES: State 9: on its first frame starts the next screen and its music; once the
   music has stopped it closes the screen manager's step, finishes the screen and sends event
   2; otherwise the screen manager is updated. */
void Sequence::CWirelessBattleModeJob::f_00fe44()
{
    if (m68 == 1) {
        f_0156d4();
        f_005554(D_1dd6b0, 1);
    } else {
        if (f_0056d0(D_1dd6b0))
            goto update;
        f_017c88(&D_2301b0);
        f_015ed8();
        queue.Push(2);
        return;
    }
update:
    f_017bfc(&D_2301b0);
}

/* @implements 0x00fefc us f_00fefc
   WHAT IT DOES: State 10: clears the retry counter, opens the lobby, starts the network session
   if it is not running and sends event 2. */
void Sequence::CWirelessBattleModeJob::f_00fefc()
{
    m3212 = 0;
    f_0160bc();
    if (!D_241810.m4)
        f_086440(&D_241810);
    queue.Push(2);
}

/* @implements 0x00ff74 us f_00ff74
   WHAT IT DOES: State 11: waits in the lobby. When the lobby closes, it ends the session for
   results 2 and 3 (remembering why, event 9) and goes on with event 5 otherwise. While the
   lobby is open, holding cancel or the second button for six frames after pressing it asks
   to leave (event 8). */
void Sequence::CWirelessBattleModeJob::f_00ff74()
{
    int r = f_0160fc();
    if (r) {
        f_0161b8();
        f_096408(D_242cb0);
        if (r == 2 || r == 3) {
            f_00e30c();
            D_1ee170 = r;
            queue.Push(9);
        } else {
            queue.Push(5);
        }
        return;
    }
    if (f_014a28() == 1)
        f_096434(D_242cb0, -1);
    if (D_1d8910[0].Trig(2) || D_1d8910[0].Trig(0x400000)) {
        m3212 = 1;
    } else if (m3212 > 0 && (D_1d8910[0].Held(2) || D_1d8910[0].Held(0x400000))) {
        m3212++;
        if (m3212 >= 6) {
            m3212 = 0;
            if (f_014a08()) {
                f_0968e0(D_242cb0);
                queue.Push(8);
            }
        }
    } else {
        m3212 = 0;
    }
}

/* @implements 0x010100 us f_010100
   WHAT IT DOES: State 12: shows the lobby message for the session's role (1 when joining, 2
   when hosting). */
void Sequence::CWirelessBattleModeJob::f_010100()
{
    LobbyMsg msg;
    int hosting = D_1ee168 != 0;
    msg.m20 = hosting + 1;
    f_017970()->v2(&msg, 0);
}

/* @implements 0x010170 us f_010170
   WHAT IT DOES: State 13: waits for the race entry screen. When the player enters, it starts
   the session as host if it is not running; when the entry is cancelled it ends the session
   and leaves (event 10); when the entry fails, or the session drops while waiting, it shows
   the error and goes back (event 6). */
void Sequence::CWirelessBattleModeJob::f_010170()
{
    switch (f_016168()) {
    case 2:
        if (!D_241810.m4 && f_0865e8(&D_241810)) {
            f_096408(D_242cb0);
            f_086470(&D_241810);
        }
        break;
    case 4:
    case 5:
        f_00e30c();
        f_096408(D_242cb0);
        queue.Push(10);
        break;
    case 1:
        f_096918(D_242cb0);
        queue.Push(6);
        break;
    default:
        if (f_08550c(&D_241810) != 7) {
            f_096918(D_242cb0);
            queue.Push(6);
        }
        break;
    }
}

/* @implements 0x010284 us f_010284
   WHAT IT DOES: State 14: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_010284()
{
}

/* @implements 0x01028c us f_01028c
   WHAT IT DOES: State 15: on its first frame opens the wait screen; when the wait is over it
   closes it, sends event 2 and clears the main loop's flag. */
void Sequence::CWirelessBattleModeJob::f_01028c()
{
    if (m68 == 1)
        f_016138();
    if (f_0160fc()) {
        f_0161b8();
        queue.Push(2);
        D_1d88a0->m11 = 0;
    }
}

/* @implements 0x01031c us f_01031c
   WHAT IT DOES: State 16: closes the lobby, stops the sound and sends event 2. */
void Sequence::CWirelessBattleModeJob::f_01031c()
{
    f_016220();
    f_0057d0(D_1dd6b0);
    queue.Push(2);
}

/* State 18 (retail 0x010ac4). Byte-exact, but left untagged here: the compiler control set
   (src/control/batch2.c) already holds that address's tag.
   WHAT IT DOES: State 18: updates the screen manager; once it is ready, finishes its step and
   sends event 2. */
void Sequence::CWirelessBattleModeJob::f_010ac4()
{
    f_017bfc(&D_2301b0);
    if (D_2301b0.Ready()) {
        f_017c88(&D_2301b0);
        queue.Push(2);
    }
}

/* @implements 0x010b44 us f_010b44
   WHAT IT DOES: State 19: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_010b44()
{
}

/* @implements 0x011184 us f_011184
   WHAT IT DOES: State 21: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_011184()
{
}

/* @implements 0x01118c us f_01118c
   WHAT IT DOES: State 22: opens the system message dialog, with message 2 when the race ended
   for reason 3 and message 0 otherwise. */
void Sequence::CWirelessBattleModeJob::f_01118c()
{
    if (D_1ee170 == 3)
        f_0997ac(D_2451f4, 2);
    else
        f_0997ac(D_2451f4, 0);
}

/* @implements 0x0111d0 us f_0111d0
   WHAT IT DOES: State 23: sends event 2 when the message dialog closes. */
void Sequence::CWirelessBattleModeJob::f_0111d0()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x01122c us f_01122c
   WHAT IT DOES: State 24: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_01122c()
{
}

/* @implements 0x011234 us f_011234
   WHAT IT DOES: State 25: starts checking the memory stick. */
void Sequence::CWirelessBattleModeJob::f_011234()
{
    f_01bb3c(&D_23ba90);
}

/* @implements 0x011254 us f_011254
   WHAT IT DOES: State 26: when the memory stick check is done, sends event 13 if the stick can
   be written, and event 7 otherwise. */
void Sequence::CWirelessBattleModeJob::f_011254()
{
    if (!f_01bc5c(&D_23ba90))
        return;
    if (!D_23ba90.m7 && f_01a900(&D_23ba90))
        queue.Push(13);
    else
        queue.Push(7);
}

/* @implements 0x011308 us f_011308
   WHAT IT DOES: State 27: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_011308()
{
}

/* @implements 0x011310 us f_011310
   WHAT IT DOES: State 28: starts loading the save data from the memory stick. */
void Sequence::CWirelessBattleModeJob::f_011310()
{
    f_01a91c(&D_23ba90, 0);
}

/* @implements 0x011334 us f_011334
   WHAT IT DOES: State 29: when the memory stick access is done, sends event 13 on success and
   event 7 on failure. */
void Sequence::CWirelessBattleModeJob::f_011334()
{
    if (!f_01abf4(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90))
        queue.Push(13);
    else
        queue.Push(7);
}

/* @implements 0x0113cc us f_0113cc
   WHAT IT DOES: State 30: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_0113cc()
{
}

/* @implements 0x0113d4 us f_0113d4
   WHAT IT DOES: State 31: writes the kept settings back, then sends event 15 when there is
   nothing new to save, event 14 when the game should save automatically, and event 16
   otherwise. */
void Sequence::CWirelessBattleModeJob::f_0113d4()
{
    f_00e068();
    if (!f_0194c4())
        queue.Push(15);
    else if (f_006018() || !D_237cfc)
        queue.Push(16);
    else
        queue.Push(14);
}

/* @implements 0x011490 us f_011490
   WHAT IT DOES: State 32: starts writing the save data to the memory stick. */
void Sequence::CWirelessBattleModeJob::f_011490()
{
    f_01a91c(&D_23ba90, 1);
}

/* @implements 0x0114b4 us f_0114b4
   WHAT IT DOES: State 33: when the memory stick access is done, sends event 13 on success and
   event 7 on failure. */
void Sequence::CWirelessBattleModeJob::f_0114b4()
{
    if (!f_01abf4(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90))
        queue.Push(13);
    else
        queue.Push(7);
}

/* @implements 0x01154c us f_01154c
   WHAT IT DOES: State 34: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_01154c()
{
}

/* @implements 0x011554 us f_011554
   WHAT IT DOES: State 35: opens the system message dialog for the memory stick's error. */
void Sequence::CWirelessBattleModeJob::f_011554()
{
    f_099718(D_2451f4, D_23ba90.m0);
}

/* @implements 0x01157c us f_01157c
   WHAT IT DOES: State 36: sends event 2 when the message dialog closes. */
void Sequence::CWirelessBattleModeJob::f_01157c()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x0115d8 us f_0115d8
   WHAT IT DOES: State 37: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_0115d8()
{
}

/* @implements 0x0115e0 us f_0115e0
   WHAT IT DOES: State 38: clears the pending save flag and opens the system message dialog
   with message 1. */
void Sequence::CWirelessBattleModeJob::f_0115e0()
{
    D_237cc8 = 0;
    f_0997ac(D_2451f4, 1);
}

/* @implements 0x01160c us f_01160c
   WHAT IT DOES: State 39: sends event 2 when the message dialog closes. */
void Sequence::CWirelessBattleModeJob::f_01160c()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x011668 us f_011668
   WHAT IT DOES: State 40: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_011668()
{
}

/* The static data of this object file: the lobby's screen request, built at startup. */
ScreenReq D_1ee174;

/* @implements 0x011670 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the lobby's screen request; at shutdown, destroys it. */

/* @implements 0x0116ec us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x01170c us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */

/* The class's inline virtual functions and destructors, emitted out of line here with the
   vtable.
   @implements 0x01172c us _ZN8Sequence22CWirelessBattleModeJob3f_3Ei
   WHAT IT DOES: Runs the state handler the script names. */

/* @implements 0x011794 us _ZN8Sequence22CWirelessBattleModeJob3f_4Ev
   WHAT IT DOES: Sends the script event 3. */

/* @implements 0x0117c4 us _ZN8Sequence22CWirelessBattleModeJobD1Ev
   WHAT IT DOES: The destructor, which has nothing to release. */
/* @implements 0x0117d4 us _ZN8Sequence22CWirelessBattleModeJobD0Ev
   WHAT IT DOES: The deleting destructor: destroys the job and frees its memory. */
