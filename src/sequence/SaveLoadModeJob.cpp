/* The save and load mode job, from its Step (retail 0x011ec8 to 0x012bc4, then the class's
   inline methods emitted out of line at 0x012bc4 to 0x012c2c): the game mode behind the save
   and load menu, which loads, saves and deletes the game's save data on the memory stick. Like
   every mode job it is a state machine: a table of 27 member functions, one per state, a queue
   of state events and a small script interpreter (in the base class) that decides the next
   state. The constructors and Begin come before this, at the end of the previous object file
   (0x011b50 and 0x011ea4); Begin is defined here because it is the class's key function, which
   makes this file emit the vtable and the destructors. The vtable
   (_ZTVN8Sequence16CSaveLoadModeJobE) names Begin, Step, End, the state runner at 0x012b5c and
   the event sender at 0x012bc4. */

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

class CSaveLoadModeJob : public CModeJob {
public:
    typedef void (CSaveLoadModeJob::*State)();

    CSaveLoadModeJob();
    virtual ~CSaveLoadModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4();

    void f_01205c();
    void f_012064();
    void f_012094();
    void f_01209c();
    void f_012234();
    void f_01223c();
    void f_0122bc();
    void f_0123ac();
    void f_0123b4();
    void f_0123d8();
    void f_0125dc();
    void f_0125e4();
    void f_012604();
    void f_012740();
    void f_012748();
    void f_01276c();
    void f_012804();
    void f_01280c();
    void f_01288c();
    void f_01299c();
    void f_0129a4();
    void f_0129cc();
    void f_012a28();
    void f_012a30();
    void f_012ad4();
    void f_012b30();
    void f_012b38();

    int state;
    int m8[11];
    short *m52;
    unsigned char *m56;
    bool m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[27];
    int m360;
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
    LayerSub m4;
    char m8[453 - 8];
    unsigned char m453;
};
struct ScreenMgr {
    CLayer *layer;
};
extern ScreenMgr D_2301b0;
void f_018b48(ScreenMgr *);

/* The game's settings, as far as this object file reads them. */
struct GameState {
    char p0[15684];
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
};
extern GameState D_233f70;

/* The memory stick state: the last error code and the result flags of the last access. */
struct MemoryStick {
    int m0;
    bool m4;
    bool m5;
    bool m6;
    bool m7;
};
extern MemoryStick D_23ba90;
int f_01a900(MemoryStick *);
void f_01a91c(MemoryStick *, int);
int f_01abf4(MemoryStick *);
void f_01ad04(MemoryStick *, int);
int f_01ae50(MemoryStick *);
void f_01bb3c(MemoryStick *);
int f_01bc5c(MemoryStick *);

/* The system message dialog. */
extern char D_2451f4[];
void f_099718(void *dialog, int);
void f_0997ac(void *dialog, int);
int f_0998d0(void *dialog);

void f_07a558(void *);
void f_07a5d4(void *);
void f_0786b8(void *);
void f_078734(void *);
void f_078794(void *);

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

/* A notice sent to the screen object. */
struct ScreenMsg {
    ScreenMsg() { f_0786b8(this); }
    ~ScreenMsg() { f_078734(this); }
    void *vt;
    int m4;
    unsigned char m8;
    unsigned char m9;
};

extern "C" {
int f_006018(void);
}

extern int D_237cc8;
extern unsigned char D_237cfc;

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
};
}
extern System::CGameModeJob D_1e8ec4;

/* Begin (retail 0x011ea4, object file 18, tagged with that object file's functions): starts
   the mode from its first state, with the saved option value. */
void Sequence::CSaveLoadModeJob::Begin()
{
    m68 = 0;
    m360 = D_237cc8;
    m60 = 1;
    m64 = 0;
    m68 = 0;
    state = 0;
}

/* @implements 0x011ec8 us _ZN8Sequence16CSaveLoadModeJob4StepEv
   WHAT IT DOES: Runs one frame of the save and load menu unless the game is paused. On the
   first frame of a state it sends the script the state's entry event; every frame it sends
   the update event, letting the script react to each queued event, and counts the frames
   spent in the state. Except in the states that show the system message dialog or leave the
   mode, it then updates the menu screens. */
int Sequence::CSaveLoadModeJob::Step()
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
    case 2:
    case 3:
    case 7:
    case 8:
    case 9:
        break;
    default:
        f_018b48(&D_2301b0);
        break;
    }
    return 0;
}

/* @implements 0x01204c us _ZN8Sequence16CSaveLoadModeJob3EndEv
   WHAT IT DOES: Leaves the mode, keeping the option value it may have changed. */
void Sequence::CSaveLoadModeJob::End()
{
    D_237cc8 = m360;
}

/* @implements 0x01205c us f_01205c
   WHAT IT DOES: State 0: nothing to do. */
void Sequence::CSaveLoadModeJob::f_01205c()
{
}

/* @implements 0x012064 us f_012064
   WHAT IT DOES: State 1: sends the script event 2. */
void Sequence::CSaveLoadModeJob::f_012064()
{
    queue.Push(2);
}

/* @implements 0x012094 us f_012094
   WHAT IT DOES: State 2: nothing to do. */
void Sequence::CSaveLoadModeJob::f_012094()
{
}

/* @draft 0x01209c us f_01209c
   WHAT IT DOES: State 3: the save and load menu itself. It reacts to the item the player
   chose: load (event 4), save (event 5), or delete, which asks first (event 6) unless the
   game saves automatically or the delete needs no confirmation (event 7). Unless the player
   is leaving, it then keeps the option value the screen shows and sends event 2. */
void Sequence::CSaveLoadModeJob::f_01209c()
{
    switch (D_2301b0.layer->v10(3)) {
    case 5:
        queue.Push(4);
        break;
    case 6:
        queue.Push(5);
        break;
    case 8:
        if (!f_006018() && D_237cfc)
            queue.Push(6);
        else
            queue.Push(7);
        break;
    }
    if (D_2301b0.layer->v10(6) == 9)
        return;
    Options o;
    D_2301b0.layer->v3(&o, 0);
    m360 = o.m28;
    queue.Push(2);
}

/* @implements 0x012234 us f_012234
   WHAT IT DOES: State 4: nothing to do. */
void Sequence::CSaveLoadModeJob::f_012234()
{
}

/* @implements 0x01223c us f_01223c
   WHAT IT DOES: State 5: takes the option value from the screen and starts loading the save
   data from the memory stick. */
void Sequence::CSaveLoadModeJob::f_01223c()
{
    Options o;
    D_2301b0.layer->v3(&o, 0);
    m360 = o.m28;
    D_237cc8 = m360;
    f_01a91c(&D_23ba90, 0);
}

/* @draft 0x0122bc us f_0122bc
   WHAT IT DOES: State 6: when the load has finished, tells the screen whether it succeeded,
   restarts the screen layer and sends event 2. */
void Sequence::CSaveLoadModeJob::f_0122bc()
{
    if (!f_01abf4(&D_23ba90))
        return;
    ScreenMsg n;
    f_078794(&n);
    n.m9 = !D_23ba90.m4;
    n.m8 = 1;
    D_2301b0.layer->v2(&n, 0);
    CLayer *l = D_2301b0.layer;
    l->m453 = 1;
    if (l->m4.p)
        l->m4.f_04b290();
    queue.Push(2);
}

/* @implements 0x0123ac us f_0123ac
   WHAT IT DOES: State 7: nothing to do. */
void Sequence::CSaveLoadModeJob::f_0123ac()
{
}

/* @implements 0x0123b4 us f_0123b4
   WHAT IT DOES: State 8: starts checking the memory stick for save data. */
void Sequence::CSaveLoadModeJob::f_0123b4()
{
    f_01ad04(&D_23ba90, 0);
}

/* @draft 0x0123d8 us f_0123d8
   WHAT IT DOES: State 9: when the memory stick check is done, tells the screen what it found
   and restarts the screen layer. When save data was read, it shows the machine and display
   options again. Then it sends event 8 when the stick needs attention and event 2
   otherwise. */
void Sequence::CSaveLoadModeJob::f_0123d8()
{
    if (!f_01ae50(&D_23ba90))
        return;
    ScreenMsg n;
    f_078794(&n);
    n.m8 = !D_23ba90.m6;
    n.m9 = !D_23ba90.m4;
    D_2301b0.layer->v2(&n, 0);
    CLayer *l = D_2301b0.layer;
    l->m453 = 1;
    if (l->m4.p)
        l->m4.f_04b290();
    if (f_01a900(&D_23ba90)) {
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
        D_2301b0.layer->v2(&o, 0);
    }
    if (D_23ba90.m7)
        queue.Push(8);
    else
        queue.Push(2);
}

/* @implements 0x0125dc us f_0125dc
   WHAT IT DOES: State 10: nothing to do. */
void Sequence::CSaveLoadModeJob::f_0125dc()
{
}

/* @implements 0x0125e4 us f_0125e4
   WHAT IT DOES: State 11: starts checking the memory stick before a save. */
void Sequence::CSaveLoadModeJob::f_0125e4()
{
    f_01bb3c(&D_23ba90);
}

/* @draft 0x012604 us f_012604
   WHAT IT DOES: State 12: when the memory stick check is done, sends event 9 if the stick can
   be written; otherwise it tells the screen about the problem, restarts the screen layer and
   sends event 8. */
void Sequence::CSaveLoadModeJob::f_012604()
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
    CLayer *l = D_2301b0.layer;
    l->m453 = 1;
    if (l->m4.p)
        l->m4.f_04b290();
    queue.Push(8);
}

/* @implements 0x012740 us f_012740
   WHAT IT DOES: State 13: nothing to do. */
void Sequence::CSaveLoadModeJob::f_012740()
{
}

/* @implements 0x012748 us f_012748
   WHAT IT DOES: State 14: starts loading the save data from the memory stick. */
void Sequence::CSaveLoadModeJob::f_012748()
{
    f_01a91c(&D_23ba90, 0);
}

/* @implements 0x01276c us f_01276c
   WHAT IT DOES: State 15: when the memory stick access is done, sends event 9 on success and
   event 8 on failure. */
void Sequence::CSaveLoadModeJob::f_01276c()
{
    if (!f_01abf4(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90))
        queue.Push(9);
    else
        queue.Push(8);
}

/* @implements 0x012804 us f_012804
   WHAT IT DOES: State 16: nothing to do. */
void Sequence::CSaveLoadModeJob::f_012804()
{
}

/* @implements 0x01280c us f_01280c
   WHAT IT DOES: State 17: takes the option value from the screen and starts saving the game
   to the memory stick. */
void Sequence::CSaveLoadModeJob::f_01280c()
{
    Options o;
    D_2301b0.layer->v3(&o, 0);
    m360 = o.m28;
    D_237cc8 = m360;
    f_01a91c(&D_23ba90, 1);
}

/* @draft 0x01288c us f_01288c
   WHAT IT DOES: State 18: when the save has finished, tells the screen how it went, restarts
   the screen layer and sends event 9 on success and event 8 on failure. */
void Sequence::CSaveLoadModeJob::f_01288c()
{
    if (!f_01abf4(&D_23ba90))
        return;
    ScreenMsg n;
    f_078794(&n);
    n.m8 = !D_23ba90.m6;
    n.m9 = !D_23ba90.m4;
    D_2301b0.layer->v2(&n, 0);
    CLayer *l = D_2301b0.layer;
    l->m453 = 1;
    if (l->m4.p)
        l->m4.f_04b290();
    if (f_01a900(&D_23ba90))
        queue.Push(9);
    else
        queue.Push(8);
}

/* @implements 0x01299c us f_01299c
   WHAT IT DOES: State 19: nothing to do. */
void Sequence::CSaveLoadModeJob::f_01299c()
{
}

/* @implements 0x0129a4 us f_0129a4
   WHAT IT DOES: State 20: opens the system message dialog for the memory stick error. */
void Sequence::CSaveLoadModeJob::f_0129a4()
{
    f_099718(D_2451f4, D_23ba90.m0);
}

/* @implements 0x0129cc us f_0129cc
   WHAT IT DOES: State 21: sends event 2 when the message dialog closes. */
void Sequence::CSaveLoadModeJob::f_0129cc()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x012a28 us f_012a28
   WHAT IT DOES: State 22: nothing to do. */
void Sequence::CSaveLoadModeJob::f_012a28()
{
}

/* @draft 0x012a30 us f_012a30
   WHAT IT DOES: State 23: clears the option value on the screen and in the mode, and opens
   the system message dialog with message 1. */
void Sequence::CSaveLoadModeJob::f_012a30()
{
    Options o;
    D_2301b0.layer->v3(&o, 0);
    o.m28 = 0;
    D_2301b0.layer->v2(&o, 0);
    m360 = 0;
    D_237cc8 = 0;
    f_0997ac(D_2451f4, 1);
}

/* @implements 0x012ad4 us f_012ad4
   WHAT IT DOES: State 24: sends event 2 when the message dialog closes. */
void Sequence::CSaveLoadModeJob::f_012ad4()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x012b30 us f_012b30
   WHAT IT DOES: State 25: nothing to do. */
void Sequence::CSaveLoadModeJob::f_012b30()
{
}

/* @implements 0x012b38 us f_012b38
   WHAT IT DOES: State 26: leaves for the main menu. */
void Sequence::CSaveLoadModeJob::f_012b38()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x012b5c us _ZN8Sequence16CSaveLoadModeJob3f_3Ei
   WHAT IT DOES: Runs the state handler the script names. */
void Sequence::CSaveLoadModeJob::f_3(int i)
{
    (this->*states[i])();
}

/* @implements 0x012bc4 us _ZN8Sequence16CSaveLoadModeJob3f_4Ev
   WHAT IT DOES: Sends the script event 3. */
void Sequence::CSaveLoadModeJob::f_4()
{
    queue.Push(3);
}

/* @implements 0x012bf4 us _ZN8Sequence16CSaveLoadModeJobD1Ev
   WHAT IT DOES: The destructor, which has nothing to release. */
/* @implements 0x012c04 us _ZN8Sequence16CSaveLoadModeJobD0Ev
   WHAT IT DOES: The deleting destructor: destroys the job and frees its memory. */
