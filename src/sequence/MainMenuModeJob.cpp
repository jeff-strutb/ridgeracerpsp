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

/* The front end's screen manager. Its first member is the object that runs the current menu
   screen. */
class CScreen {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(void *msg, int);
    virtual void v3(void *msg, int);
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
