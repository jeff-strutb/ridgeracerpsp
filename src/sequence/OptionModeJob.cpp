/* The option mode job (retail 0x012c2c to 0x014950): the game mode behind the options menu,
   where the player changes the machine and display settings, watches the demo replays and
   loads or saves the settings on the memory stick. Like every mode job it is a state machine:
   a table of 37 member functions, one per state, a queue of state events and a small script
   interpreter (in the base class) that decides the next state. The constructors and Begin
   close the previous object file (0x012c2c to 0x013540, after the save and load mode job's
   inline methods); Step, End and the state handlers fill the next one; the class's inline
   methods emitted out of line (the event sender and the destructors) follow at 0x0148e8. The
   vtable (_ZTVN8Sequence14COptionModeJobE) names Begin, Step, End, the state runner at
   0x014880 and the event sender at 0x0148e8. */

#include <stdio.h>

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
};
}

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

class COptionModeJob : public CModeJob {
public:
    typedef void (COptionModeJob::*State)();

    COptionModeJob();
    virtual ~COptionModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4();

    void f_0136dc();

    void f_013794();
    void f_0137b0();
    void f_0137e0();
    void f_0137e8();
    void f_013b60();
    void f_013b68();
    void f_013bac();
    void f_013c44();
    void f_013d0c();
    void f_013ef0();
    void f_013f34();
    void f_01400c();
    void f_013d84();
    void f_013dc4();
    void f_013ee8();
    void f_014014();
    void f_0140c8();
    void f_01419c();
    void f_0141f0();
    void f_0142b8();
    void f_014308();
    void f_01436c();
    void f_01438c();
    void f_0144c8();
    void f_0144d0();
    void f_0144f4();
    void f_01458c();
    void f_014594();
    void f_0145b8();
    void f_0146c0();
    void f_0146c8();
    void f_0146f0();
    void f_01474c();
    void f_014754();
    void f_0147f8();
    void f_014854();
    void f_01485c();

    int state;
    int m8[11];
    short *m52;
    unsigned char *m56;
    bool m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[37];
    int m440;
    int m444;
    int m448;
    int m452;
    int m456;
    bool m460;
    int m464;
    int m468;
    int m472;
    int m476;
    unsigned char m480[8];
    int m488;
    int m492;
    int m496;
    bool m500;
    int m504;
    int m508;
    bool m512;
    bool m513;
};
}

/* This object file's script tables. */
extern short D_1d1528[];
extern unsigned char D_1d1574[];

/* The part of the main loop job this object file uses: a flag byte set while the game is
   paused, and the flag that lets the pad skip a replay. */
struct MainLoopJobView {
    char m0[12];
    unsigned char paused;
    char p13[32 - 13];
    bool m32;
};
extern MainLoopJobView *D_1d88a0;

/* The front end's screen manager. Its first member is the current screen layer, a polymorphic
   object that is given settings (v2), asked for them (v3) and asked what the player did
   (v10). */
struct LayerSub {
    void *p;
    void f_04b290();
};
class CLayer {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(void *msg, int arg);
    virtual void v3(void *msg, int arg);
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual int v10(int what);
    void Restart()
    {
        m453 = 1;
        LayerSub *t = &m4;
        if (t->p)
            t->f_04b290();
    }
    LayerSub m4;
    char m8[453 - 8];
    bool m453;
};
struct ScreenMgr {
    CLayer *layer;
    int m4[3];
    int phase;
};
extern ScreenMgr D_2301b0;
void f_017bfc(ScreenMgr *);
void f_017c88(ScreenMgr *);
void f_018af8(ScreenMgr *);
void f_018b04(ScreenMgr *);
void f_018b48(ScreenMgr *);

/* The game's settings, as far as this object file reads and writes them. */
struct GameState {
    int m0[3];
    int m12;
    int m16;
    int m20;
    char p24[15476 - 24];
    int m15476;
    char p15480[15676 - 15480];
    int m15676;
    char p15680[15688 - 15680];
    int m15688;
    int m15692;
    int m15696;
    int m15700;
    int m15704;
    int m15708;
    int m15712;
    unsigned char m15716[8];
    int m15724;
    int m15728;
    int m15732;
    int m15736;
    int m15740;
    char p15744[15756 - 15744];
    unsigned char m15756;
};
extern GameState D_233f70;
void f_01959c(GameState *);

/* The two values the title keeps between modes. */
struct SavedPair {
    int a;
    int b;
};
extern SavedPair D_1d1a94;
extern int D_240100;

/* The memory stick state: the last error code, the result flags of the last access and the
   buffer a replay is read into. */
struct MemoryStick {
    int m0;
    bool m4;
    bool m5;
    bool m6;
    bool m7;
    int m8[3];
    char *m20;
    int m24;
    int m28;
    int m32;
};
extern MemoryStick D_23ba90;
int f_01a900(MemoryStick *);
void f_01a91c(MemoryStick *, int);
int f_01abf4(MemoryStick *);
void f_01b284(MemoryStick *);
int f_01b3b8(MemoryStick *);
void f_01bb3c(MemoryStick *);
int f_01bc5c(MemoryStick *);

/* The system message dialog. */
extern char D_2451f4[];
void f_099718(void *dialog, int);
void f_0997ac(void *dialog, int);
int f_0998d0(void *dialog);

/* The sequence player that runs the demo replays. */
struct CSequence {
    char p0[284];
    int m284;
};
extern CSequence D_1dd6b0;
void f_0030c8(CSequence *, int);
void f_0030f4(CSequence *);
void f_005554(CSequence *, int);
int f_0056d0(CSequence *);
void f_005720(CSequence *);
void f_0057d0(CSequence *);
int f_005c34(CSequence *, const char *);

/* The replay being shown, built by the replay code. Its constructor (0x041aa4) belongs to
   that code, so the object is created through a plain block of its size that runs it. */
void f_041aa4(void *);
struct CReplayBlock {
    CReplayBlock() { f_041aa4(this); }
    char p0[84];
};
class CReplay {
public:
    virtual ~CReplay();
    virtual void v2();
    virtual int v3();
    virtual void v4();
    void f_041b5c();
    char p4[24 - 4];
    int m24;
    char p28[84 - 28];
};
extern CReplay *D_1ee18c;
extern bool D_1ee190;
extern char *D_1ee194;

/* The race camera and the sound effects. */
extern char D_245074[];
void f_0981fc(void *, int);
void f_0982c4(void *);
void f_098290(void *);
void f_0983bc(void *);
extern char D_242e14[];
void f_097680(void *, int, int);

/* The pad. */
namespace Controller {
class CCustomController {
public:
    int f_043030();
};
}
extern Controller::CCustomController D_1d8910[1];

/* The debug log. */
extern char D_245178[];

extern "C" {
void f_00d354(void *log, int level, const char *fmt, ...);
int f_006018(void);
void f_0160bc(void);
int f_0160fc(void);
void f_016138(void);
void f_0161b8(void);
void f_016220(void);
void f_015ed8(void);
int f_016b28(void *, int);
void f_016fd4(void);
void f_0170a8(void);
void f_017788(int);
void f_1521c8(void *);
}
int f_00222c(const char *name, const char *package);
int f_0022e4(int i);

extern int D_1d1108;
extern int D_237cc8;

void f_07a558(void *);
void f_07a5d4(void *);
void f_07a744(void *);
void f_07a7c0(void *);
void f_0786b8(void *);
void f_078734(void *);

/* The machine and display settings exchanged with the screen. */
struct Options {
    Options() { f_07a558(this); }
    ~Options() { f_07a5d4(this); }
    void *vt;
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    bool m28;
    bool m29;
    bool m30;
    unsigned char m31[8];
    char p39[75 - 39];
    signed char m75;
    int m76;
    int m80;
    char p84[336 - 84];
};

/* A pair of values exchanged with the screen: the demo replay and the sound setting. */
struct PairMsg {
    PairMsg() { f_07a744(this); }
    ~PairMsg() { f_07a7c0(this); }
    void *vt;
    int m4;
    int m8;
    int m12;
};

/* A notice sent to the screen object. */
struct ScreenMsg {
    ScreenMsg() { f_0786b8(this); }
    ~ScreenMsg() { f_078734(this); }
    void *vt;
    int m4;
    bool m8;
    bool m9;
};

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
};
}
extern System::CGameModeJob D_1e8ec4;

/* @implements 0x012c2c us _ZN8Sequence14COptionModeJobC2Ev
   WHAT IT DOES: Constructs the option mode job: an empty state queue, the table of state
   handlers and the two script tables. */
/* @implements 0x013048 us _ZN8Sequence14COptionModeJobC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */
Sequence::COptionModeJob::COptionModeJob()
{
    states[0] = &COptionModeJob::f_013794;
    states[1] = &COptionModeJob::f_0137b0;
    states[2] = &COptionModeJob::f_0137e0;
    states[3] = &COptionModeJob::f_0137e8;
    states[4] = &COptionModeJob::f_013b60;
    states[5] = &COptionModeJob::f_013b68;
    states[6] = &COptionModeJob::f_013bac;
    states[7] = &COptionModeJob::f_013c44;
    states[8] = &COptionModeJob::f_013d0c;
    states[9] = &COptionModeJob::f_013ef0;
    states[10] = &COptionModeJob::f_013f34;
    states[11] = &COptionModeJob::f_01400c;
    states[12] = &COptionModeJob::f_013d84;
    states[13] = &COptionModeJob::f_013dc4;
    states[14] = &COptionModeJob::f_013ee8;
    states[15] = &COptionModeJob::f_014014;
    states[16] = &COptionModeJob::f_0140c8;
    states[17] = &COptionModeJob::f_01419c;
    states[18] = &COptionModeJob::f_0141f0;
    states[19] = &COptionModeJob::f_0142b8;
    states[20] = &COptionModeJob::f_014308;
    states[21] = &COptionModeJob::f_01436c;
    states[22] = &COptionModeJob::f_01438c;
    states[23] = &COptionModeJob::f_0144c8;
    states[24] = &COptionModeJob::f_0144d0;
    states[25] = &COptionModeJob::f_0144f4;
    states[26] = &COptionModeJob::f_01458c;
    states[27] = &COptionModeJob::f_014594;
    states[28] = &COptionModeJob::f_0145b8;
    states[29] = &COptionModeJob::f_0146c0;
    states[30] = &COptionModeJob::f_0146c8;
    states[31] = &COptionModeJob::f_0146f0;
    states[32] = &COptionModeJob::f_01474c;
    states[33] = &COptionModeJob::f_014754;
    states[34] = &COptionModeJob::f_0147f8;
    states[35] = &COptionModeJob::f_014854;
    states[36] = &COptionModeJob::f_01485c;
    m52 = D_1d1528;
    m56 = D_1d1574;
}

/* @implements 0x013464 us _ZN8Sequence14COptionModeJob5BeginEv
   WHAT IT DOES: Starts the options menu from its first state, with a copy of the settings it
   edits: the machine and display options, the sound and replay settings and the two values
   the title keeps. */
void Sequence::COptionModeJob::Begin()
{
    m68 = 0;
    m440 = D_233f70.m15688;
    m444 = D_233f70.m15692;
    m448 = D_233f70.m15696;
    m476 = D_233f70.m15700;
    m452 = D_233f70.m15704;
    m456 = D_233f70.m15708;
    m460 = D_233f70.m15712 != 0;
    for (int i = 0; i < 8; i++)
        m480[i] = D_233f70.m15716[i];
    m464 = D_233f70.m15728;
    m468 = D_233f70.m15724;
    m488 = D_233f70.m15732;
    m492 = D_233f70.m15736;
    m496 = D_233f70.m15740;
    m504 = D_233f70.m12;
    m508 = D_233f70.m16;
    m512 = D_233f70.m20 != 0;
    m500 = D_233f70.m15676 != 0;
    m64 = 0;
    m68 = 0;
    state = 0;
    m60 = 1;
}

/* @implements 0x013540 us _ZN8Sequence14COptionModeJob4StepEv
   WHAT IT DOES: Runs one frame of the options menu unless the game is paused. On the first
   frame of a state it sends the script the state's entry event; every frame it sends the
   update event, letting the script react to each queued event, and counts the frames spent
   in the state. Except while a replay is shown or the menu is waiting, it then updates the
   menu screens. */
int Sequence::COptionModeJob::Step()
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
    case 4:
    case 7:
    case 15:
    case 16:
    case 17:
        break;
    default:
        f_018b48(&D_2301b0);
        break;
    }
    return 0;
}

/* @implements 0x0136d4 us _ZN8Sequence14COptionModeJob3EndEv
   WHAT IT DOES: Nothing to release when the options menu ends. */
void Sequence::COptionModeJob::End()
{
}

/* @implements 0x0136dc us f_0136dc
   WHAT IT DOES: Writes the edited settings back into the game's settings. */
void Sequence::COptionModeJob::f_0136dc()
{
    D_233f70.m15688 = m440;
    D_233f70.m15692 = m444;
    D_233f70.m15696 = m448;
    D_233f70.m15700 = m476;
    D_233f70.m15704 = m452;
    D_233f70.m15708 = m456;
    D_233f70.m15712 = m460;
    for (int i = 0; i < 8; i++)
        D_233f70.m15716[i] = m480[i];
    D_233f70.m15728 = m464;
    D_233f70.m15724 = m468;
    D_233f70.m15732 = m488;
    D_233f70.m15736 = m492;
    D_233f70.m15740 = m496;
    D_233f70.m12 = m504;
    D_233f70.m16 = m508;
    D_233f70.m20 = m512;
    D_233f70.m15676 = m500;
}

/* @implements 0x013794 us f_013794
   WHAT IT DOES: State 0: hands the two values the title keeps back to it. */
void Sequence::COptionModeJob::f_013794()
{
    D_1d1a94.a = m504;
    D_1d1a94.b = m508;
}

/* @implements 0x0137b0 us f_0137b0
   WHAT IT DOES: State 1: sends the script event 2. */
void Sequence::COptionModeJob::f_0137b0()
{
    queue.Push(2);
}

/* @implements 0x0137e0 us f_0137e0
   WHAT IT DOES: State 2: nothing to do. */
void Sequence::COptionModeJob::f_0137e0()
{
}

/* @implements 0x0137e8 us f_0137e8
   WHAT IT DOES: State 3: the options menu itself. When the player picks a demo replay or the
   sound test, it plays it (event 7 for a replay, 6 and 8 for the others). When the player
   leaves, or asks to save, it takes every setting from the screen, writes them into the game's
   settings and sends event 2; a save goes on with event 4, or with event 5 when the game
   saves automatically or the memory stick is not usable.
   The two flag stores share one constant through a local, which retail loads once. */
void Sequence::COptionModeJob::f_0137e8()
{
    bool save = false;
    switch (D_2301b0.layer->v10(3)) {
    case 8:
        save = true;
        break;
    case 9: {
        PairMsg p;
        D_2301b0.layer->v3(&p, 0);
        m492 = p.m8;
        m496 = p.m12;
        f_0030f4(&D_1dd6b0);
        if (m496 >= 1 && m496 <= 6) {
            D_1dd6b0.m284 = m496;
            f_018b04(&D_2301b0);
            f_018af8(&D_2301b0);
            queue.Push(7);
        } else if (m496 == 7) {
            queue.Push(6);
        } else if (m496 == 8) {
            queue.Push(8);
        }
        break;
    }
    }
    if (D_2301b0.layer->v10(6) == 8 && !save)
        return;
    Options o;
    D_2301b0.layer->v3(&o, 0);
    m440 = o.m8;
    m444 = o.m12;
    m448 = o.m16;
    m476 = o.m24;
    m452 = o.m28;
    m456 = o.m29;
    m460 = o.m30;
    for (int i = 0; i < 8; i++)
        m480[i] = o.m31[i];
    m464 = o.m75;
    m468 = o.m76;
    m488 = o.m80;
    PairMsg p;
    D_2301b0.layer->v3(&p, 0);
    m492 = p.m8;
    m496 = p.m12;
    m504 = D_1d1a94.a;
    m508 = D_1d1a94.b;
    bool one = 1;
    if (D_240100)
        m512 = one;
    if (m512 && D_233f70.m15476)
        m500 = one;
    f_0136dc();
    f_01959c(&D_233f70);
    if (!save)
        queue.Push(2);
    else if (f_006018() || !D_233f70.m15756)
        queue.Push(5);
    else
        queue.Push(4);
}

/* @implements 0x013b60 us f_013b60
   WHAT IT DOES: State 4: nothing to do. */
void Sequence::COptionModeJob::f_013b60()
{
}

/* @implements 0x013b68 us f_013b68
   WHAT IT DOES: State 5: sends event 2 once the screen manager is idle. */
void Sequence::COptionModeJob::f_013b68()
{
    if (!D_2301b0.phase)
        queue.Push(2);
}

/* @implements 0x013bac us f_013bac
   WHAT IT DOES: State 6: creates the replay player for the chosen demo and starts the replay
   camera and sound for it. */
void Sequence::COptionModeJob::f_013bac()
{
    D_1ee18c = (CReplay *)new CReplayBlock;
    D_1ee18c->f_041b5c();
    f_0981fc(D_245074, m492);
    f_0983bc(D_245074);
    D_1ee190 = 0;
}

/* @implements 0x013c44 us f_013c44
   WHAT IT DOES: State 7: runs the replay. A press of the skip button marks it skipped; until
   then the camera keeps playing. Sends event 2 when the replay has finished. */
void Sequence::COptionModeJob::f_013c44()
{
    D_1d88a0->m32 = 0;
    if (D_1d8910[0].f_043030()) {
        D_1ee18c->m24 = 1;
        D_1ee190 = 1;
    }
    if (!D_1ee190)
        f_0982c4(D_245074);
    if (D_1ee18c->v3())
        queue.Push(2);
}

/* @implements 0x013d0c us f_013d0c
   WHAT IT DOES: State 8: stops the replay camera, ends and frees the replay player and fades
   the screen back in. */
void Sequence::COptionModeJob::f_013d0c()
{
    f_098290(D_245074);
    D_1ee18c->v4();
    delete D_1ee18c;
    f_097680(D_242e14, 8, -1);
}

/* @implements 0x013d84 us f_013d84
   WHAT IT DOES: State 12: allocates a 512 KB buffer and starts reading a replay from the
   memory stick into it. */
void Sequence::COptionModeJob::f_013d84()
{
    D_1ee194 = new char[0x80000];
    D_23ba90.m20 = D_1ee194;
    D_23ba90.m24 = 0x80000;
    f_01b284(&D_23ba90);
}

/* @implements 0x013dc4 us f_013dc4
   WHAT IT DOES: State 13: when the replay read is done, unpacks the replay and moves on to
   show it (event 9), or fades back in and reports the failure (event 10). Then it frees the
   buffer. */
void Sequence::COptionModeJob::f_013dc4()
{
    if (!f_01b3b8(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90)) {
        int n = f_016b28(D_1ee194, D_23ba90.m32);
        f_00d354(D_245178, 4, "ReplayLoad: %d\n", n);
        queue.Push(9);
        f_018b04(&D_2301b0);
        f_018af8(&D_2301b0);
    } else {
        f_097680(D_242e14, 8, -1);
        queue.Push(10);
    }
    if (D_1ee194)
        f_1521c8(D_1ee194);
}

/* @implements 0x013ee8 us f_013ee8
   WHAT IT DOES: State 14: nothing to do. */
void Sequence::COptionModeJob::f_013ee8()
{
}

/* @implements 0x013ef0 us f_013ef0
   WHAT IT DOES: State 9: starts the chosen demo sequence. */
void Sequence::COptionModeJob::f_013ef0()
{
    D_1dd6b0.m284 = m496;
    f_0030c8(&D_1dd6b0, 1);
    f_005554(&D_1dd6b0, 1);
}

/* @implements 0x013f34 us f_013f34
   WHAT IT DOES: State 10: keeps the menu screens going while the demo sequence loads; when it
   is ready it unpacks the chosen demo's data, starts it and sends event 2. */
void Sequence::COptionModeJob::f_013f34()
{
    if (!f_0056d0(&D_1dd6b0)) {
        int data = f_005c34(&D_1dd6b0, "Data");
        char name[256];
        sprintf(name, "Demo%d", m496);
        f_016b28((void *)data, f_0022e4(f_00222c("Data", name)));
        f_017788(m496);
        queue.Push(2);
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x01400c us f_01400c
   WHAT IT DOES: State 11: nothing to do. */
void Sequence::COptionModeJob::f_01400c()
{
}

/* @implements 0x014014 us f_014014
   WHAT IT DOES: State 15: on its first frame starts the sound test sequence; afterwards it
   sends event 2 once the sequence is ready. It keeps the menu screens going. */
void Sequence::COptionModeJob::f_014014()
{
    if (m68 == 1) {
        D_1d1108 = 7;
        f_005720(&D_1dd6b0);
        f_016fd4();
        f_005554(&D_1dd6b0, 1);
    } else if (!f_0056d0(&D_1dd6b0)) {
        queue.Push(2);
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x0140c8 us f_0140c8
   WHAT IT DOES: State 16: on its first frame starts the sequence back to the menu; once it is
   ready it reopens the menu screens, restarts the race camera and sends event 2. */
void Sequence::COptionModeJob::f_0140c8()
{
    if (m68 == 1) {
        f_0170a8();
        f_005554(&D_1dd6b0, 1);
    } else if (!f_0056d0(&D_1dd6b0)) {
        f_017c88(&D_2301b0);
        f_015ed8();
        f_0981fc(D_245074, m492);
        f_0983bc(D_245074);
        queue.Push(2);
        return;
    } else {
        f_017bfc(&D_2301b0);
        return;
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x01419c us f_01419c
   WHAT IT DOES: State 17: starts the replay shown from the memory stick and sends event 2. */
void Sequence::COptionModeJob::f_01419c()
{
    f_0160bc();
    m513 = 0;
    queue.Push(2);
}

/* @implements 0x0141f0 us f_0141f0
   WHAT IT DOES: State 18: runs the replay from the memory stick. A press of the skip button
   stops the camera and the replay; when the replay has finished it sends event 9 if it was
   skipped and event 2 otherwise. */
void Sequence::COptionModeJob::f_0141f0()
{
    f_0982c4(D_245074);
    if (D_1d8910[0].f_043030()) {
        m513 = 1;
        f_016138();
        f_098290(D_245074);
    }
    if (f_0160fc()) {
        if (m513 == 1)
            queue.Push(9);
        else
            queue.Push(2);
    }
}

/* @implements 0x0142b8 us f_0142b8
   WHAT IT DOES: State 19: ends the replay and sends event 2. */
void Sequence::COptionModeJob::f_0142b8()
{
    f_0161b8();
    queue.Push(2);
}

/* @implements 0x014308 us f_014308
   WHAT IT DOES: State 20: ends the replay, frees its data, starts the sequence back to the
   menu and sends event 2. */
void Sequence::COptionModeJob::f_014308()
{
    f_0161b8();
    f_016220();
    f_0057d0(&D_1dd6b0);
    queue.Push(2);
}

/* @implements 0x01436c us f_01436c
   WHAT IT DOES: State 21: starts checking the memory stick before a save. */
void Sequence::COptionModeJob::f_01436c()
{
    f_01bb3c(&D_23ba90);
}

/* @implements 0x01438c us f_01438c
   WHAT IT DOES: State 22: when the memory stick check is done, sends event 9 if the stick can
   be written; otherwise it tells the screen about the problem, restarts the screen layer and
   sends event 10. */
void Sequence::COptionModeJob::f_01438c()
{
    if (!f_01bc5c(&D_23ba90))
        return;
    if (!D_23ba90.m7 && f_01a900(&D_23ba90)) {
        queue.Push(9);
        return;
    }
    ScreenMsg n;
    n.m9 = !D_23ba90.m4;
    n.m8 = 1;
    D_2301b0.layer->v2(&n, 0);
    D_2301b0.layer->Restart();
    queue.Push(10);
}

/* @implements 0x0144c8 us f_0144c8
   WHAT IT DOES: State 23: nothing to do. */
void Sequence::COptionModeJob::f_0144c8()
{
}

/* @implements 0x0144d0 us f_0144d0
   WHAT IT DOES: State 24: starts loading the save data from the memory stick. */
void Sequence::COptionModeJob::f_0144d0()
{
    f_01a91c(&D_23ba90, 0);
}

/* @implements 0x0144f4 us f_0144f4
   WHAT IT DOES: State 25: when the memory stick access is done, sends event 9 on success and
   event 10 on failure. */
void Sequence::COptionModeJob::f_0144f4()
{
    if (!f_01abf4(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90))
        queue.Push(9);
    else
        queue.Push(10);
}

/* @implements 0x01458c us f_01458c
   WHAT IT DOES: State 26: nothing to do. */
void Sequence::COptionModeJob::f_01458c()
{
}

/* @implements 0x014594 us f_014594
   WHAT IT DOES: State 27: starts saving the game to the memory stick. */
void Sequence::COptionModeJob::f_014594()
{
    f_01a91c(&D_23ba90, 1);
}

/* @implements 0x0145b8 us f_0145b8
   WHAT IT DOES: State 28: when the save has finished, tells the screen how it went, restarts
   the screen layer and sends event 9 on success and event 10 on failure. */
void Sequence::COptionModeJob::f_0145b8()
{
    if (!f_01abf4(&D_23ba90))
        return;
    ScreenMsg n;
    n.m8 = !D_23ba90.m6;
    n.m9 = !D_23ba90.m4;
    D_2301b0.layer->v2(&n, 0);
    D_2301b0.layer->Restart();
    if (f_01a900(&D_23ba90))
        queue.Push(9);
    else
        queue.Push(10);
}

/* @implements 0x0146c0 us f_0146c0
   WHAT IT DOES: State 29: nothing to do. */
void Sequence::COptionModeJob::f_0146c0()
{
}

/* @implements 0x0146c8 us f_0146c8
   WHAT IT DOES: State 30: opens the system message dialog for the memory stick error. */
void Sequence::COptionModeJob::f_0146c8()
{
    f_099718(D_2451f4, D_23ba90.m0);
}

/* @implements 0x0146f0 us f_0146f0
   WHAT IT DOES: State 31: sends event 2 when the message dialog closes. */
void Sequence::COptionModeJob::f_0146f0()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x01474c us f_01474c
   WHAT IT DOES: State 32: nothing to do. */
void Sequence::COptionModeJob::f_01474c()
{
}

/* @implements 0x014754 us f_014754
   WHAT IT DOES: State 33: clears the save option on the screen and in the mode, and opens the
   system message dialog with message 1. */
void Sequence::COptionModeJob::f_014754()
{
    Options o;
    D_2301b0.layer->v3(&o, 0);
    CLayer *l = D_2301b0.layer;
    o.m28 = 0;
    l->v2(&o, 0);
    m452 = 0;
    D_237cc8 = 0;
    f_0997ac(D_2451f4, 1);
}

/* @implements 0x0147f8 us f_0147f8
   WHAT IT DOES: State 34: sends event 2 when the message dialog closes. */
void Sequence::COptionModeJob::f_0147f8()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x014854 us f_014854
   WHAT IT DOES: State 35: nothing to do. */
void Sequence::COptionModeJob::f_014854()
{
}

/* @implements 0x01485c us f_01485c
   WHAT IT DOES: State 36: leaves for the main menu. */
void Sequence::COptionModeJob::f_01485c()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x014880 us _ZN8Sequence14COptionModeJob3f_3Ei
   WHAT IT DOES: Runs the state handler the script names. */
void Sequence::COptionModeJob::f_3(int i)
{
    (this->*states[i])();
}

/* @implements 0x0148e8 us _ZN8Sequence14COptionModeJob3f_4Ev
   WHAT IT DOES: Sends the script event 3. */
void Sequence::COptionModeJob::f_4()
{
    queue.Push(3);
}

/* @implements 0x014918 us _ZN8Sequence14COptionModeJobD1Ev
   WHAT IT DOES: The destructor, which has nothing to release. */
/* @implements 0x014928 us _ZN8Sequence14COptionModeJobD0Ev
   WHAT IT DOES: The deleting destructor: destroys the job and frees its memory. */
