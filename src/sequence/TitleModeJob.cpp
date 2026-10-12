/* The title screen mode job (retail 0x006bbc to 0x0078a0): the game mode that shows the title
   and waits for the player. Like every mode job it is driven by a small script (a table of
   state ranges and a byte code, run by the mode job base): each frame the job queues events
   (0 when a state is entered, 1 once per frame) and the script answers them by running one of
   the job's state handlers, a table of member functions, or by switching state. */

extern short D_1d1074[];
extern unsigned char D_1d1090[];

/* The part of the main loop job this object file reads: a flag byte set while the game is
   paused. */
struct MainLoopJobView {
    char m0[12];
    unsigned char paused;
};
extern MainLoopJobView *D_1d88a0;

/* The front end screen object the title drives: its first member is the current screen layer,
   a polymorphic object; its other words are the screen's status. */
struct LayerSub {
    void *p;
    void f_04b290();
};
class CLayer {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(void *msg, int arg);
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual int v10(int what);
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    LayerSub m4;
    char m8[453 - 8];
    unsigned char m453;
};
struct Screen {
    CLayer *layer;
    int m4[3];
    int status;
    int m20;
    int m24;
    int m28[2];
    bool IsStatus(int s) { return status == s; }
};
extern Screen D_2301b0;
extern char D_2301d4[];

/* The global game state words this mode saves, restores and sets. */
struct SavedPair {
    void Set(int x, int y)
    {
        a = x;
        b = y;
    }
    int a;
    int b;
};
struct GameState {
    int m0[3];
    int m12;
    int m16;
    int m20;
    char p24[14808 - 24];
    int m14808;
    char p14812[15476 - 14812];
    int m15476;
    char p15480[15676 - 15480];
    int m15676;
    char p15680[15708 - 15680];
    int m15708;
};
extern GameState D_233f70;
SavedPair D_1d1a94 = {20000, 2000};
extern int D_240100;
extern int D_237ccc;

/* The memory stick state the title polls. */
struct MemoryStick {
    int m0;
    char m4[2];
    unsigned char inserted;
};
extern MemoryStick D_23ba90;
extern char D_2451f4[];
extern char D_1d8bb8[];
extern char D_1d8cd0[];
extern char D_1d8aa0[];
extern char D_1dd6b0[];

void f_002734(void *loader, unsigned char nowait);
void f_0030c8(void *, int);
void f_005554(void *, int);
int f_0056d0(void *);
int f_002acc(void *, const char *name);
extern "C" void f_00600c(void);
int f_006094(void);
void f_017e1c(Screen *, void *msg);
void f_018abc(Screen *, int);
void f_018b48(Screen *);
void f_0182e4(Screen *, void *msg);
int f_01a900(MemoryStick *);
int f_01ae50(MemoryStick *);
void f_01ad04(MemoryStick *, int);
void f_099718(void *dialog, int);
int f_0998d0(void *dialog);
void f_07ab2c(void *);
void f_07aba8(void *);
void f_0786b8(void *);
void f_078734(void *);

/* A request sent to the screen layer (built and destroyed by the screen code). */
struct LayerMsg {
    LayerMsg() { f_07ab2c(this); }
    ~LayerMsg() { f_07aba8(this); }
    void *vt;
    int m4;
    int m8;
    unsigned char m12;
};

/* A notice sent to the screen object. */
struct ScreenMsg {
    ScreenMsg() { f_0786b8(this); }
    ~ScreenMsg() { f_078734(this); }
    void *vt;
    int m4;
    unsigned char m8;
    unsigned char m9;
};

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
};
}
extern System::CGameModeJob D_1e8ec4;

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
   their vtable slot) run a state handler and queue a state. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int);
    virtual void f_4();
    int f_099948(int state, int event);
};

/* A queue of sixteen script events, read at head and written at tail. */
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

class CTitleModeJob : public CModeJob {
public:
    typedef void (CTitleModeJob::*State)();

    CTitleModeJob();
    virtual ~CTitleModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4();

    void f_0070ec();
    void f_007178();
    void f_00725c();
    void f_0072b0();
    void f_0074d0();
    void f_0074f8();
    void f_007630();
    void f_007638();
    void f_007640();
    void f_007760();
    void f_007768();
    void f_0077ac();

    int state;
    int m8[11];
    short *m52;
    unsigned char *m56;
    bool m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[12];
    int m240;
    unsigned char m244;
};
}

/* @implements 0x006bbc us _ZN8Sequence13CTitleModeJobC2Ev
   WHAT IT DOES: Constructs the title mode job: an empty state queue, the table of state
   handlers and the two layout tables the title screen draws from. */
/* @implements 0x006d6c us _ZN8Sequence13CTitleModeJobC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */
Sequence::CTitleModeJob::CTitleModeJob()
{
    states[0] = &CTitleModeJob::f_0070ec;
    states[1] = &CTitleModeJob::f_007178;
    states[2] = &CTitleModeJob::f_00725c;
    states[3] = &CTitleModeJob::f_0072b0;
    states[4] = &CTitleModeJob::f_0074d0;
    states[5] = &CTitleModeJob::f_0074f8;
    states[6] = &CTitleModeJob::f_007630;
    states[7] = &CTitleModeJob::f_007638;
    states[8] = &CTitleModeJob::f_007640;
    states[9] = &CTitleModeJob::f_007760;
    states[10] = &CTitleModeJob::f_007768;
    states[11] = &CTitleModeJob::f_0077ac;
    m52 = D_1d1074;
    m56 = D_1d1090;
}

/* @implements 0x006f1c us _ZN8Sequence13CTitleModeJob5BeginEv
   WHAT IT DOES: Starts the title screen from its first state. */
void Sequence::CTitleModeJob::Begin()
{
    m64 = 0;
    m68 = 0;
    state = 0;
    m60 = 1;
}

/* @draft 0x006f34 us _ZN8Sequence13CTitleModeJob4StepEv
   WHAT IT DOES: Runs one frame of the title screen, unless the game is paused: on the first
   frame of a state it sends the script the enter event, then the per frame event, and counts
   the frames spent in the state. It then updates the screen. */
int Sequence::CTitleModeJob::Step()
{
    int e;

    if (!D_1d88a0->paused) {
        if (m60) {
            queue.Push(0);
            while ((e = queue.Pop()) >= 0)
                f_099948(m64, e);
        }
        m60 = 0;
        queue.Push(1);
        int s = m64;
        while ((e = queue.Pop()) >= 0)
            f_099948(s, e);
        m68++;
    }
    f_018b48(&D_2301b0);
    return 0;
}

/* @implements 0x007090 us _ZN8Sequence13CTitleModeJob3EndEv
   WHAT IT DOES: Leaves the title screen: records a pending flag in the game state, and puts
   back the two game state words the title saved when it started. */
void Sequence::CTitleModeJob::End()
{
    if (D_240100)
        D_233f70.m20 = 1;
    if (D_233f70.m20 && D_233f70.m15476)
        D_233f70.m15676 = 1;
    D_233f70.m12 = D_1d1a94.a;
    D_233f70.m16 = D_1d1a94.b;
}

/* @draft 0x0070ec us f_0070ec
   WHAT IT DOES: State 0: saves two game state words, then opens the title screen layer. */
void Sequence::CTitleModeJob::f_0070ec()
{
    int b = D_233f70.m16;
    int a = D_233f70.m12;
    D_1d1a94.a = a;
    D_1d1a94.b = b;
    LayerMsg msg;
    msg.m12 = 1;
    msg.m8 = 0;
    f_017e1c(&D_2301b0, &msg);
    f_018abc(&D_2301b0, 9);
}

/* @implements 0x007178 us f_007178
   WHAT IT DOES: State 1: once the screen reports it is ready, starts the title layer, releases
   four loaded packages, starts the title music and queues event 2. */
void Sequence::CTitleModeJob::f_007178()
{
    if (D_2301b0.IsStatus(4)) {
        D_2301b0.layer->v10(3);
        f_002734(D_1d8bb8, 1);
        f_002734(D_1d8cd0, 1);
        f_002734(D_1d8aa0, 1);
        f_002734(D_2301d4, 1);
        f_0030c8(D_1dd6b0, 11);
        f_005554(D_1dd6b0, 1);
        queue.Push(2);
    }
}

/* @implements 0x00725c us f_00725c
   WHAT IT DOES: State 2: reads the save data; on failure it remembers the error and uses 0.
   Then it starts watching the memory stick. */
void Sequence::CTitleModeJob::f_00725c()
{
    m244 = 0;
    m240 = f_006094();
    if (m240 < 0) {
        m244 = 1;
        m240 = 0;
    }
    f_01ad04(&D_23ba90, 1);
}

/* @draft 0x0072b0 us f_0072b0
   WHAT IT DOES: State 3: when the memory stick check is done, decides how the title goes on:
   with no memory stick inserted it asks for one (event 4); otherwise it tells the screen layer
   which start the player gets (0 normal, 1 after a save data error, 2 with fewer than 700
   saved), marks the game state and notifies the screen (event 3). */
void Sequence::CTitleModeJob::f_0072b0()
{
    if (!f_01ae50(&D_23ba90))
        return;
    LayerMsg msg;
    if (f_01a900(&D_23ba90)) {
        queue.Push(3);
        msg.m8 = 0;
    } else if (m244) {
        msg.m8 = 1;
        f_00600c();
        queue.Push(3);
    } else if (!D_23ba90.inserted) {
        queue.Push(4);
        return;
    } else if (m240 < 700) {
        queue.Push(3);
        msg.m8 = 2;
    } else {
        queue.Push(3);
        msg.m8 = 0;
    }
    msg.m12 = D_233f70.m15708 != 0;
    D_2301b0.layer->v2(&msg, 0);
    CLayer *l = D_2301b0.layer;
    l->m453 = 1;
    if (l->m4.p)
        l->m4.f_04b290();
    D_233f70.m14808 = 1;
    ScreenMsg n;
    n.m8 = f_01a900(&D_23ba90);
    n.m9 = 1;
    f_0182e4(&D_2301b0, &n);
}

/* @implements 0x0074d0 us f_0074d0
   WHAT IT DOES: State 4: opens the system message dialog about the memory stick. */
void Sequence::CTitleModeJob::f_0074d0()
{
    f_099718(D_2451f4, D_23ba90.m0);
}

/* @draft 0x0074f8 us f_0074f8
   WHAT IT DOES: State 5: when the message dialog closes, starts the title layer normally,
   notifies the screen and queues event 2. */
void Sequence::CTitleModeJob::f_0074f8()
{
    if (!f_0998d0(D_2451f4))
        return;
    LayerMsg msg;
    msg.m8 = 0;
    msg.m12 = D_237ccc != 0;
    D_2301b0.layer->v2(&msg, 0);
    CLayer *l = D_2301b0.layer;
    l->m453 = 1;
    if (l->m4.p)
        l->m4.f_04b290();
    ScreenMsg n;
    n.m8 = f_01a900(&D_23ba90);
    n.m9 = 1;
    f_0182e4(&D_2301b0, &n);
    queue.Push(2);
}

/* @implements 0x007630 us f_007630
   WHAT IT DOES: State 6: nothing to do. */
void Sequence::CTitleModeJob::f_007630()
{
}

/* @implements 0x007638 us f_007638
   WHAT IT DOES: State 7: nothing to do. */
void Sequence::CTitleModeJob::f_007638()
{
}

/* @implements 0x007640 us f_007640
   WHAT IT DOES: State 8: the title waiting for the player. When the layer reports a choice it
   queues event 6. Otherwise it keeps the high score display and the music going, and queues
   event 2 when the screen asks for it. */
void Sequence::CTitleModeJob::f_007640()
{
    if (D_2301b0.layer->v10(3) == 1) {
        queue.Push(6);
        return;
    }
    if (f_002acc(D_1d8cd0, "HIGH"))
        D_2301b0.layer->v18();
    if (!f_0056d0(D_1dd6b0))
        D_2301b0.layer->v17();
    if (D_2301b0.m24)
        queue.Push(2);
}

/* @implements 0x007760 us f_007760
   WHAT IT DOES: State 9: nothing to do. */
void Sequence::CTitleModeJob::f_007760()
{
}

/* @implements 0x007768 us f_007768
   WHAT IT DOES: State 10: queues event 2 once the screen is idle. */
void Sequence::CTitleModeJob::f_007768()
{
    if (D_2301b0.status == 0)
        queue.Push(2);
}

/* @implements 0x0077ac us f_0077ac
   WHAT IT DOES: State 11: asks the game mode job to switch to mode 1 (the main menu). */
void Sequence::CTitleModeJob::f_0077ac()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x0077d0 us _ZN8Sequence13CTitleModeJob3f_3Ei
   WHAT IT DOES: Runs the state handler the script names. */
void Sequence::CTitleModeJob::f_3(int i)
{
    (this->*states[i])();
}

/* @implements 0x007838 us _ZN8Sequence13CTitleModeJob3f_4Ev
   WHAT IT DOES: Queues event 5. */
void Sequence::CTitleModeJob::f_4()
{
    queue.Push(5);
}

/* @implements 0x007868 us _ZN8Sequence13CTitleModeJobD1Ev
   WHAT IT DOES: The destructor, which has nothing to release. */
/* @implements 0x007878 us _ZN8Sequence13CTitleModeJobD0Ev
   WHAT IT DOES: The deleting destructor: destroys the job and frees its memory. */
