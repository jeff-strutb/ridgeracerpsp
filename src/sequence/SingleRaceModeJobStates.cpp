/* The single race mode job, from its Step (retail 0x00968c to 0x00d404, then the class's inline
   methods emitted out of line at 0x00d404 to 0x00d46c): the game mode that runs a race against
   the computer cars, time trials and the race menus around them. Like every mode job it is a
   state machine: a table of member functions, one per state, a queue of state events and a
   small script interpreter (in the base class) that decides the next state. The constructors
   and Begin come before this, at the end of the previous object file. */

#include <string.h>

extern "C" {
int f_0160fc(void);
int f_016168(void);
void f_016138(void);
void f_0160bc(void);
void f_0161b8(void);
void f_016220(void);
void f_015204(void);
void f_0156d4(void);
void f_015ec0(void);
void f_015ed8(void);
int f_0149e8(void);
int f_014a08(void);
int f_014a28(void);

int f_0056d0(char *);
void f_005554(char *, int);
void f_005720(char *);
void f_0057d0(char *);

void f_096408(char *);
void f_096434(char *, int);
int f_09654c(char *);
int f_0965b4(char *);
void f_0965ec(char *);
int f_0968e0(char *);
int f_096918(char *);
int f_094db0(char *);
}

extern char D_1dd6b0[];
extern char D_242cb0[];
extern int D_1d1108;
extern int D_1d3d3c;
extern bool D_1edf50;
extern int D_1edf54;
extern int D_1edf58;
extern bool D_1edf5c;
extern bool D_1edf5d;
extern int D_1edf60;
extern int D_1edf64;

/* The pad, as far as this file uses it. */
namespace Controller {
class CCustomController {
public:
    int f_043030();
    int Trig(int mask) { return m16 & mask; }
    int m0[4];
    int m16;
};
}
extern Controller::CCustomController D_1d8910[1];

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
};
}
extern System::CGameModeJob D_1e8ec4;

/* The main loop job, as far as this file reads it. */
struct MainLoopJobView {
    char m0[11];
    bool m11;
    bool paused;
};
extern MainLoopJobView *D_1d88a0;

/* The object D_2301b0 points at (the race front end), called through its vtable. */
class CFrontEnd {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void Read(void *dst, int arg);
};
struct FrontEndRef {
    CFrontEnd *p;
    int m4[3];
    int m16;
    int m20;
    int m24;
};
extern FrontEndRef D_2301b0;
extern "C" {
void f_018b48(FrontEndRef *);
void f_017bfc(FrontEndRef *);
void f_017c88(FrontEndRef *);
}

extern "C" {
void f_07a314(void *);
void f_07a390(void *);
}

/* The race setup the front end edits (built and destroyed by the front end code). Its course
   flag table is read 28 bytes long although the next table starts two bytes earlier. */
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
    int m32[24];
    int m128;
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
    unsigned char m291;
    char p292[304 - 292];
};

/* The race settings shared with the race itself. */
struct Tri {
    int a, b, c;
};
struct RaceSettings {
    int m0[5];
    int m20;
    int m24[336];
    int m1368[336];
    Tri m2712[3 * 336];
    int m14808[13];
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
    int m15680;
};
extern RaceSettings D_233f70;

namespace Ng {
class CJob {
public:
    virtual void Begin() {}
    virtual int Step() { return 0; }
    virtual void End() {}
};
}

namespace Sequence {
/* A queue of sixteen state events, read at head and written at tail. */
class CStateQueue {
public:
    void push(int v)
    {
        buf[tail++] = v;
        tail &= 15;
    }
    int pop()
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

/* The base of every mode job: the script interpreter's stack and program counter, the script
   (an index of entry points per state and the byte code), the current state and the event
   queue. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int) {}
    virtual void f_4() {}
    int f_099948(int state, int event);

    int sp;
    int pc;
    int stack[10];
    short *table;
    unsigned char *code;
    bool entered;
    int state;
    int frames;
    CStateQueue queue;
};

class CSingleRaceModeJob : public CModeJob {
public:
    typedef void (CSingleRaceModeJob::*State)();

    CSingleRaceModeJob();
    virtual ~CSingleRaceModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int i) { (this->*states[i])(); }
    virtual void f_4() { queue.push(3); }

    void f_009884();
    void f_009a44();
    void f_009bbc();
    void f_009bc4();
    void f_009bf4();
    void f_009c30();
    void f_00a8f4();
    void f_00a8fc();
    void f_00a940();
    void f_00a964();
    void f_00aa10();
    void f_00aac8();
    void f_00ab18();
    void f_00ac54();
    void f_00ac5c();
    void f_00ad84();
    void f_00ad8c();
    void f_00ae1c();
    void f_00ae78();
    void f_00aee8();
    void f_00af44();
    void f_00af98();
    void f_00b04c();
    void f_00b09c();

    State states[54];
    unsigned char m576;
    int m580[336];
    int m1924[336];
    Tri m3268[3 * 336];
    int m15364;
    int m15368;
    int m15372;
    int m15376;
    int m15380;
    int m15384[24];
    int m15480;
    int m15484;
    int m15488[48];
    unsigned char m15680[60];
    unsigned char m15740[28];
    unsigned char m15768[10];
    int m15780;
    unsigned char m15784;
    unsigned char m15785;
    unsigned char m15786;
    int m15788;
    int m15792[48];
    unsigned char m15984;
    int m15988;
    int m15992;
    int m15996;
    void *m16000;
    unsigned char m16004;
    int m16008;
    int m16012;
    int m16016[3];
};
}

/* @implements 0x00968c us _ZN8Sequence18CSingleRaceModeJob4StepEv
   WHAT IT DOES: Runs one frame of the single race mode. Unless the game is paused, it feeds the
   script the events of the frame (the entry event when a state has just been entered, then the
   frame event), letting it change state, and counts the frame. Then, by state, it updates the
   race (or, while paused, the pause menu) or the front end. */
int Sequence::CSingleRaceModeJob::Step()
{
    int e;

    if (!D_1d88a0->paused) {
        if (entered) {
            queue.push(0);
            while ((e = queue.pop()) >= 0)
                f_099948(state, e);
        }
        entered = 0;
        queue.push(1);
        int s = state;
        while ((e = queue.pop()) >= 0)
            f_099948(s, e);
        frames++;
    }
    switch (state) {
    case 8:
    case 17:
        if (D_1d88a0->paused)
            f_0160fc();
        break;
    case 21:
    case 22:
    case 23:
    case 26:
    case 28:
        break;
    case 9:
        if (D_1d88a0->paused)
            f_016168();
        break;
    default:
        f_018b48(&D_2301b0);
        break;
    }
    return 0;
}

/* @implements 0x009868 us _ZN8Sequence18CSingleRaceModeJob3EndEv
   WHAT IT DOES: Leaves the single race mode, handing its settings back to the shared race
   settings. */
void Sequence::CSingleRaceModeJob::End()
{
    f_009884();
}

/* @draft 0x009884 us f_009884
   WHAT IT DOES: Copies the mode's race setup (the per car and per course tables, the chosen
   course, car and options, the unlocked items and the special flags) into the shared race
   settings, and marks the special event as done when it was won.
   Remaining difference: the three row copy loop. Retail keeps the row offset as i*63 and
   shifts it left by 6 in the outer loop, addressing both tables from their structure bases
   (D_233f70+2712(a0)); this source steps a 4032 byte offset and folds 2712 into the base. */
void Sequence::CSingleRaceModeJob::f_009884()
{
    int i, j;

    for (i = 0; i < 336; i++) {
        D_233f70.m24[i] = m580[i];
        D_233f70.m1368[i] = m1924[i];
    }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 336; j++)
            D_233f70.m2712[336 * i + j] = m3268[336 * i + j];
    D_233f70.m14860 = m15376;
    D_233f70.m14868 = m15484;
    for (i = 0; i < 48; i++)
        D_233f70.m14872[i] = m15488[i];
    for (i = 0; i < 60; i++)
        D_233f70.m15064[i] = m15680[i];
    for (i = 0; i < 28; i++)
        D_233f70.m15304[i] = m15740[i];
    for (i = 0; i < 10; i++)
        D_233f70.m15416[i] = m15768[i];
    D_233f70.m15472 = m15784;
    D_233f70.m15476 = m15785;
    for (i = 0; i < 48; i++)
        D_233f70.m15484[i] = m15792[i];
    if (D_233f70.m20 && D_233f70.m15476)
        m15984 = 1;
    D_233f70.m15676 = m15984;
    D_233f70.m15680 = m15988;
}

/* @draft 0x009a44 us f_009a44
   WHAT IT DOES: Takes the race setup the player chose on the front end (course, car, options
   and the unlocked items) into the mode.
   Remaining difference: the last four copies (+0x12c to +0x150) are scheduled differently;
   retail loads 284, 291, 290 then 288 and stores 15780, 15788, 15784, 15786. No order of the
   four statements reproduces it. */
void Sequence::CSingleRaceModeJob::f_009a44()
{
    Settings o;

    D_2301b0.p->Read(&o, 0);
    m15364 = o.m12;
    m15372 = o.m16;
    m15368 = o.m20;
    m15376 = o.m24;
    m15380 = o.m28;
    for (unsigned int i = 0; i < 24; i++)
        m15384[i] = o.m32[i];
    m15480 = o.m128;
    m15484 = o.m132;
    for (unsigned int i = 0; i < 48; i++)
        m15488[i] = o.m136[i];
    for (unsigned int i = 0; i < 60; i++)
        m15680[i] = o.m184[i];
    for (unsigned int i = 0; i < 28; i++)
        m15740[i] = o.m244[i];
    for (unsigned int i = 0; i < 10; i++)
        m15768[i] = o.m270[i];
    m15780 = o.m284;
    m15788 = o.m291;
    m15784 = o.m288;
    m15786 = o.m290;
}

/* @implements 0x009bbc us f_009bbc
   WHAT IT DOES: State 0: does nothing (the script drives it). */
void Sequence::CSingleRaceModeJob::f_009bbc()
{
}

/* @implements 0x009bc4 us f_009bc4
   WHAT IT DOES: State 1: moves straight on to the next step of the script. */
void Sequence::CSingleRaceModeJob::f_009bc4()
{
    queue.push(2);
}

/* @implements 0x009bf4 us f_009bf4
   WHAT IT DOES: State 3: clears the status of the background save and load requests. */
void Sequence::CSingleRaceModeJob::f_009bf4()
{
    D_1edf50 = 0;
    D_1edf54 = 0;
    D_1edf58 = 0;
    D_1edf5c = 0;
    D_1edf5d = 0;
    D_1edf60 = 0;
    D_1edf64 = 0;
}

/* @implements 0x00a8f4 us f_00a8f4
   WHAT IT DOES: State 5: does nothing. */
void Sequence::CSingleRaceModeJob::f_00a8f4()
{
}

/* @implements 0x00a8fc us f_00a8fc
   WHAT IT DOES: State 6: waits until the front end is idle, then moves on. */
void Sequence::CSingleRaceModeJob::f_00a8fc()
{
    if (!D_2301b0.m16)
        queue.push(2);
}

/* @implements 0x00a940 us f_00a940
   WHAT IT DOES: State 2: returns to the main menu mode. */
void Sequence::CSingleRaceModeJob::f_00a940()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x00a964 us f_00a964
   WHAT IT DOES: On its first frame, starts the menu screen and its music; afterwards moves on
   once the music system is ready. Updates the front end every frame. */
void Sequence::CSingleRaceModeJob::f_00a964()
{
    if (frames == 1) {
        f_005720(D_1dd6b0);
        f_015204();
        f_005554(D_1dd6b0, 1);
    } else if (!f_0056d0(D_1dd6b0)) {
        queue.push(2);
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x00aa10 us f_00aa10
   WHAT IT DOES: On its first frame, starts a screen and its music; once the music system is
   ready, closes the front end screen and moves on. Otherwise updates the front end. */
void Sequence::CSingleRaceModeJob::f_00aa10()
{
    if (frames == 1) {
        f_0156d4();
        f_005554(D_1dd6b0, 1);
        f_017bfc(&D_2301b0);
    } else if (!f_0056d0(D_1dd6b0)) {
        f_017c88(&D_2301b0);
        f_015ed8();
        queue.push(2);
    } else {
        f_017bfc(&D_2301b0);
    }
}

/* @implements 0x00aac8 us f_00aac8
   WHAT IT DOES: Starts the race scene and moves on. */
void Sequence::CSingleRaceModeJob::f_00aac8()
{
    f_0160bc();
    queue.push(2);
}

/* @implements 0x00ab18 us f_00ab18
   WHAT IT DOES: While the race runs, handles the pause request and the end of the race: when
   the race is over, it closes the race and goes on to the result (or to the retry branch), and
   when the player pauses, it opens the pause menu. */
void Sequence::CSingleRaceModeJob::f_00ab18()
{
    if (f_0160fc()) {
        f_0161b8();
        if (f_0149e8()) {
            f_0965b4(D_242cb0);
            queue.push(2);
        } else {
            f_096408(D_242cb0);
            queue.push(8);
        }
    } else {
        if (f_014a28() == 1) {
            m15780 = D_1d3d3c;
            f_096434(D_242cb0, D_1d3d3c);
        }
        if (D_1d8910[0].Trig(2) || D_1d8910[0].Trig(0x400000)) {
            if (f_014a08()) {
                D_1d88a0->m11 = 1;
                f_0968e0(D_242cb0);
                queue.push(7);
            }
        }
    }
}

/* @implements 0x00ac54 us f_00ac54
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00ac54()
{
}

/* @implements 0x00ac5c us f_00ac5c
   WHAT IT DOES: Runs the pause menu and acts on the choice: continue the race, retire, restart
   or quit to the menus. */
void Sequence::CSingleRaceModeJob::f_00ac5c()
{
    switch (f_016168()) {
    case 1:
        D_1d88a0->m11 = 0;
        f_096918(D_242cb0);
        queue.push(6);
        break;
    case 5:
        f_094db0(D_242cb0);
        queue.push(10);
        break;
    case 4:
        if (m16004)
            m15376 = 1;
        D_1d1108 = 2;
        f_096408(D_242cb0);
        queue.push(9);
        break;
    case 2:
        f_096408(D_242cb0);
        queue.push(11);
        break;
    }
}

/* @implements 0x00ad84 us f_00ad84
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00ad84()
{
}

/* @implements 0x00ad8c us f_00ad8c
   WHAT IT DOES: Starts the replay on its first frame and, when it ends, closes it and moves
   on. */
void Sequence::CSingleRaceModeJob::f_00ad8c()
{
    if (frames == 1)
        f_016138();
    if (f_0160fc()) {
        f_0161b8();
        queue.push(2);
        D_1d88a0->m11 = 0;
    }
}

/* @implements 0x00ae1c us f_00ae1c
   WHAT IT DOES: Leaves the race scene, stops the music and moves on. */
void Sequence::CSingleRaceModeJob::f_00ae1c()
{
    f_016220();
    f_0057d0(D_1dd6b0);
    queue.push(2);
}

/* @implements 0x00ae78 us f_00ae78
   WHAT IT DOES: Branches on whether the race was finished. */
void Sequence::CSingleRaceModeJob::f_00ae78()
{
    if (f_0149e8())
        queue.push(2);
    else
        queue.push(8);
}

/* @implements 0x00aee8 us f_00aee8
   WHAT IT DOES: Starts the result screen and moves on. */
void Sequence::CSingleRaceModeJob::f_00aee8()
{
    f_015ec0();
    f_09654c(D_242cb0);
    queue.push(2);
}

/* @implements 0x00af44 us f_00af44
   WHAT IT DOES: Starts the replay scene with no replay request pending and moves on. */
void Sequence::CSingleRaceModeJob::f_00af44()
{
    f_0160bc();
    m576 = 0;
    queue.push(2);
}

/* @implements 0x00af98 us f_00af98
   WHAT IT DOES: While the replay runs, starts the replay menu when the player presses the
   button, and when the replay ends moves on (to the menu branch if it was requested). */
void Sequence::CSingleRaceModeJob::f_00af98()
{
    if (D_1d8910[0].f_043030()) {
        m576 = 1;
        f_016138();
        f_0965ec(D_242cb0);
    }
    if (f_0160fc()) {
        if (m576 == 1)
            queue.push(12);
        else
            queue.push(2);
    }
}

/* @implements 0x00b04c us f_00b04c
   WHAT IT DOES: Closes the race scene and moves on. */
void Sequence::CSingleRaceModeJob::f_00b04c()
{
    f_0161b8();
    queue.push(2);
}

/* @implements 0x00b09c us f_00b09c
   WHAT IT DOES: Closes and leaves the race scene, stops the music and moves on. */
void Sequence::CSingleRaceModeJob::f_00b09c()
{
    f_0161b8();
    f_016220();
    f_0057d0(D_1dd6b0);
    queue.push(2);
}
