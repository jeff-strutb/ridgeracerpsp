/* The main menu mode job (retail from 0x0079f4; this file holds 0x007b60 to 0x008838): the game
   mode behind the main menu. Like the title job it is a small state machine driven by a
   script: a table of member functions, one per state, and a queue of events for the script.
   The constructors and Begin come first in the object file (from 0x0078a0); Begin is defined
   here because it is the class's key function, which makes this file emit the vtable and the
   destructors. */

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
   their vtable slot) run a state handler and send the script its "finished" event. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int);
    virtual void f_4();
    int f_099948(int state, int event);
};

/* A queue of sixteen events, read at head and written at tail. */
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

class CMainMenuModeJob : public CModeJob {
public:
    typedef void (CMainMenuModeJob::*State)();

    CMainMenuModeJob();
    virtual ~CMainMenuModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4();

    void f_007cd4();
    void f_007cf0();
    void f_007d80();
    void f_00823c();
    void f_008244();
    void f_0085a4();
    void f_0085ac();
    void f_0085d0();
    void f_0086b8();
    void f_0086c0();

    int state;
    int m8[11];
    short *m52;
    unsigned char *m56;
    bool m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[9];
};
}

/* The part of the main loop job this object file reads: a flag byte set while the game is
   paused. */
struct MainLoopJobView {
    char m0[12];
    unsigned char paused;
};
extern MainLoopJobView *D_1d88a0;

/* The front end's screen manager. Its first member is the current screen layer, a polymorphic
   object that is given settings (v2) and asked for them (v3). */
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
    bool Ready() { return phase == 4; }
};
extern ScreenMgr D_2301b0;

/* The game's settings and progress, as far as this object file reads and writes them. */
struct GameState {
    char p0[14812];
    unsigned int m14812;
    int m14816[2];
    int m14824[3];
    int m14836[3];
    int m14848[3];
    int m14860;
    int m14864;
    int m14868;
    int m14872[48];
    int m15064[60];
    int m15304[28];
    int m15416[10];
    int m15456[4];
    int m15472;
    int m15476;
    int m15480;
    int m15484[48];
    int m15676;
    unsigned int m15680;
    int m15684;
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
};
extern GameState D_233f70;

/* The memory stick state. */
struct MemoryStick {
    int m0;
    bool m4;
};
extern MemoryStick D_23ba90;

extern int D_1d1108;
extern int D_1d110c;
extern int D_1d1110;

void f_017bfc(ScreenMgr *);
void f_017c88(ScreenMgr *);
void f_018b48(ScreenMgr *);
void f_017e40(ScreenMgr *, void *);
void f_018004(ScreenMgr *, void *);
void f_018070(ScreenMgr *, void *);
void f_01808c(ScreenMgr *, void *);
void f_0182c0(ScreenMgr *, void *);
void f_0182e4(ScreenMgr *, void *);
void f_018abc(ScreenMgr *, int);
void f_019628(GameState *);
void f_0196cc(GameState *);
void f_01959c(GameState *);
void f_01a91c(MemoryStick *, int);
int f_01abf4(MemoryStick *);
void f_07a314(void *);
void f_07a390(void *);
void f_078bf8(void *);
void f_078c74(void *);
void f_079478(void *);
void f_0794f4(void *);
void f_07a558(void *);
void f_07a5d4(void *);
void f_07a744(void *);
void f_07a7c0(void *);
void f_0786b8(void *);
void f_078734(void *);

/* The game settings the screen layer edits (built and destroyed by the screen code). */
struct Settings {
    Settings() { f_07a314(this); }
    ~Settings() { f_07a390(this); }
    void *vt;
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    char p32[132 - 32];
    int m132;
    unsigned char m136[48];
    unsigned char m184[60];
    unsigned char m244[26];
    unsigned char m270[10];
    int m280;
    int m284;
    unsigned char m288;
    unsigned char m289;
    unsigned char m290;
    char p291[304 - 291];
};

/* The record settings sent to the screen. */
struct Records {
    Records() { f_078bf8(this); }
    ~Records() { f_078c74(this); }
    void *vt;
    int m4;
    unsigned char m8[48];
    unsigned char m56;
    float m60;
    int m64;
    char p68[80 - 68];
};

/* A one flag notice sent to the screen. */
struct FlagMsg {
    FlagMsg() { f_079478(this); }
    ~FlagMsg() { f_0794f4(this); }
    void *vt;
    int m4;
    unsigned char m8;
};

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
    unsigned char m28;
    unsigned char m29;
    unsigned char m30;
    unsigned char m31[8];
    char p39[75 - 39];
    unsigned char m75;
    int m76;
    char p80[336 - 80];
};

/* A pair of values sent to the screen. */
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

/* Begin (retail 0x007b48, object file 12, tagged with that object file's functions): starts
   the main menu from its first state. */
void Sequence::CMainMenuModeJob::Begin()
{
    m64 = 0;
    m68 = 0;
    state = 0;
    m60 = 1;
}

/* @implements 0x007b60 us _ZN8Sequence16CMainMenuModeJob4StepEv
   WHAT IT DOES: Runs one frame of the main menu unless the game is paused. On the first frame
   of a state it sends the script the state's entry event; every frame it sends the update
   event, letting the script react to each queued event, and counts the frames spent in the
   state. Unless the menu is leaving (state 2), it then updates the menu screens. */
int Sequence::CMainMenuModeJob::Step()
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
    if (m64 != 2)
        f_018b48(&D_2301b0);
    return 0;
}

/* @implements 0x007ccc us _ZN8Sequence16CMainMenuModeJob3EndEv
   WHAT IT DOES: Nothing to release when the main menu ends. */
void Sequence::CMainMenuModeJob::End()
{
}

/* @implements 0x007cd4 us f_007cd4
   WHAT IT DOES: State 0: opens the main menu screen. */
void Sequence::CMainMenuModeJob::f_007cd4()
{
    f_007d80();
}

/* @implements 0x007cf0 us f_007cf0
   WHAT IT DOES: State 1: waits for the screen manager to become ready, then finishes the
   opening and moves on with event 2; after two frames of waiting it keeps the manager
   updating. */
void Sequence::CMainMenuModeJob::f_007cf0()
{
    if (D_2301b0.Ready()) {
        f_017c88(&D_2301b0);
        queue.Push(2);
    } else if (m68 >= 2) {
        f_017bfc(&D_2301b0);
    }
}

/* @implements 0x007d80 us f_007d80
   WHAT IT DOES: Hands the screen every setting the main menu shows. When the screen is already
   up, it first takes the current settings back from it and forgets the selected course. It
   then fills in the race settings for the selected mode, the unlocked cars, courses and
   options, the records (distance in miles), the machine and display options and the last two
   values, sends each to the screen and selects page 10. */
void Sequence::CMainMenuModeJob::f_007d80()
{
    Settings a;

    if (D_2301b0.Ready()) {
        D_2301b0.layer->v3(&a, 0);
        D_1d110c = a.m8;
        D_1d1108 = -1;
    }
    a.m8 = D_1d110c;
    a.m280 = D_1d1108;
    switch (a.m8) {
    case 1:
        a.m12 = D_233f70.m14816[0];
        a.m20 = D_233f70.m14816[1];
        break;
    case 2:
        a.m12 = D_233f70.m14824[0];
        a.m16 = D_233f70.m14824[1];
        a.m20 = D_233f70.m14824[2];
        break;
    case 3:
        a.m12 = D_233f70.m14836[0];
        a.m16 = D_233f70.m14836[1];
        a.m20 = D_233f70.m14836[2];
        break;
    case 4:
        a.m12 = D_233f70.m14848[0];
        a.m16 = D_233f70.m14848[1];
        a.m20 = D_233f70.m14848[2];
        break;
    }
    a.m24 = D_233f70.m14860;
    a.m28 = D_233f70.m14864;
    a.m132 = D_233f70.m14868;
    for (unsigned int i = 0; i < 48; i++)
        a.m136[i] = D_233f70.m14872[i];
    for (unsigned int i = 0; i < 60; i++)
        a.m184[i] = D_233f70.m15064[i] != 0;
    for (unsigned int i = 0; i < 28; i++)
        a.m244[i] = D_233f70.m15304[i] != 0;
    for (unsigned int i = 0; i < 10; i++)
        a.m270[i] = D_233f70.m15416[i] != 0;
    switch (D_233f70.m14812) {
    case 1:
        a.m284 = D_233f70.m15456[0];
        break;
    case 2:
        a.m284 = D_233f70.m15456[1];
        break;
    case 3:
        a.m284 = D_233f70.m15456[2];
        break;
    case 4:
        a.m284 = D_233f70.m15456[3];
        break;
    }
    a.m288 = D_233f70.m15472 != 0;
    a.m289 = D_233f70.m15476 != 0;
    a.m290 = D_233f70.m15480 != 0;
    f_017e40(&D_2301b0, &a);

    Records r;
    for (int i = 0; i < 48; i++)
        r.m8[i] = D_233f70.m15484[i];
    r.m56 = D_233f70.m15676 != 0;
    r.m60 = D_233f70.m15680 / 1609.34f;
    r.m64 = D_233f70.m15684;
    f_018004(&D_2301b0, &r);

    FlagMsg f;
    f.m8 = 1;
    f_018070(&D_2301b0, &f);

    Options o;
    o.m8 = D_233f70.m15688;
    o.m12 = D_233f70.m15692;
    o.m16 = D_233f70.m15696;
    o.m20 = D_233f70.m15684;
    o.m24 = D_233f70.m15700;
    o.m28 = D_233f70.m15704 != 0;
    o.m29 = D_233f70.m15708 != 0;
    o.m30 = D_233f70.m15712 != 0;
    for (int i = 0; i < 8; i++)
        o.m31[i] = D_233f70.m15716[i];
    o.m75 = D_233f70.m15728;
    o.m76 = D_233f70.m15724;
    f_01808c(&D_2301b0, &o);

    PairMsg m;
    m.m8 = D_233f70.m15736;
    m.m12 = D_233f70.m15740;
    f_0182c0(&D_2301b0, &m);
    f_018abc(&D_2301b0, 10);
}

/* @implements 0x00823c us f_00823c
   WHAT IT DOES: State 2: nothing to do while the menu runs its opening. */
void Sequence::CMainMenuModeJob::f_00823c()
{
}

/* @implements 0x008244 us f_008244
   WHAT IT DOES: State 3: the main menu itself. When the player resets the settings, it clears
   the game's settings but keeps the machine and display options, takes the screen's options,
   shows everything again and sends event 4. It tracks the menu item the player chose; when
   the player asks to reload the save data it does so and shows everything again. Unless the
   choice is 1 or 2, it then takes the race settings and options the player picked, tells the
   screen to close and sends event 2. */
void Sequence::CMainMenuModeJob::f_008244()
{
    if (D_2301b0.layer->v10(3) == 1) {
        int a = D_233f70.m15688;
        int b = D_233f70.m15692;
        int c = D_233f70.m15696;
        int d = D_233f70.m15704;
        int e = D_233f70.m15708;
        int f = D_233f70.m15712;
        int g = D_233f70.m15728;
        int h = D_233f70.m15724;
        f_0196cc(&D_233f70);
        D_233f70.m15688 = a;
        D_233f70.m15692 = b;
        D_233f70.m15696 = c;
        D_233f70.m15704 = d;
        D_233f70.m15708 = e;
        D_233f70.m15712 = f;
        D_233f70.m15728 = g;
        D_233f70.m15724 = h;
        f_01959c(&D_233f70);
        Options o;
        D_2301b0.layer->v3(&o, 0);
        D_233f70.m15704 = o.m28;
        for (int i = 0; i < 8; i++)
            D_233f70.m15716[i] = o.m31[i];
        f_007d80();
        queue.Push(4);
    }
    int r = D_2301b0.layer->v10(6);
    if (D_1d1110 != r)
        D_1d1110 = r;
    if (D_2301b0.layer->v10(9) == 1) {
        f_019628(&D_233f70);
        {
            ScreenMsg n;
            n.m8 = 1;
            n.m9 = 1;
            f_0182e4(&D_2301b0, &n);
        }
        f_007d80();
    }
    if (D_1d1110 == 1)
        return;
    if (D_1d1110 == 2)
        return;
    Settings s;
    D_2301b0.layer->v3(&s, 0);
    D_1d110c = s.m8;
    D_1d1108 = s.m280;
    {
        ScreenMsg n;
        n.m8 = 1;
        n.m9 = 1;
        f_0182e4(&D_2301b0, &n);
    }
    {
        Options o;
        D_2301b0.layer->v3(&o, 0);
        D_233f70.m15704 = o.m28;
    }
    queue.Push(2);
}

/* @implements 0x0085a4 us f_0085a4
   WHAT IT DOES: State 4: waits. */
void Sequence::CMainMenuModeJob::f_0085a4()
{
}

/* @implements 0x0085ac us f_0085ac
   WHAT IT DOES: State 5: starts saving the settings to the memory stick. */
void Sequence::CMainMenuModeJob::f_0085ac()
{
    f_01a91c(&D_23ba90, 0);
}

/* @implements 0x0085d0 us f_0085d0
   WHAT IT DOES: State 6: when the save has finished, tells the screen whether it succeeded,
   restarts the screen layer and sends event 2. */
void Sequence::CMainMenuModeJob::f_0085d0()
{
    if (f_01abf4(&D_23ba90)) {
        ScreenMsg n;
        n.m9 = !D_23ba90.m4;
        n.m8 = 1;
        D_2301b0.layer->v2(&n, 0);
        D_2301b0.layer->Restart();
        queue.Push(2);
    }
}

/* @implements 0x0086b8 us f_0086b8
   WHAT IT DOES: State 7: waits. */
void Sequence::CMainMenuModeJob::f_0086b8()
{
}

/* @implements 0x0086c0 us f_0086c0
   WHAT IT DOES: State 8: leaves the main menu for the game mode of the item the player chose
   (the races, wireless battle, save and load, or the options). */
void Sequence::CMainMenuModeJob::f_0086c0()
{
    switch (D_1d1110) {
    case 3:
        D_1e8ec4.f_0069ec(2);
        break;
    default:
    case 4:
        D_1e8ec4.f_0069ec(3);
        break;
    case 5:
        D_1e8ec4.f_0069ec(4);
        break;
    case 6:
    case 7:
        D_1e8ec4.f_0069ec(5);
        break;
    case 8:
        D_1e8ec4.f_0069ec(8);
        break;
    case 9:
        D_1e8ec4.f_0069ec(7);
        break;
    }
}

/* @implements 0x008768 us _ZN8Sequence16CMainMenuModeJob3f_3Ei
   WHAT IT DOES: Runs the handler of the given state. */
void Sequence::CMainMenuModeJob::f_3(int i)
{
    (this->*states[i])();
}

/* @implements 0x0087d0 us _ZN8Sequence16CMainMenuModeJob3f_4Ev
   WHAT IT DOES: Queues event 3. */
void Sequence::CMainMenuModeJob::f_4()
{
    queue.Push(3);
}

/* @implements 0x008800 us _ZN8Sequence16CMainMenuModeJobD1Ev
   WHAT IT DOES: The destructor, which has nothing to release. */
/* @implements 0x008810 us _ZN8Sequence16CMainMenuModeJobD0Ev
   WHAT IT DOES: The deleting destructor: destroys the job and frees its memory. */
