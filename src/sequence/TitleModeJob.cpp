/* The title screen mode job (retail from 0x006bbc): the game mode that shows the title and
   waits for the player. It runs as a small state machine: a table of member functions, one
   per state, and a queue of requested states. This file holds the start of the object file
   (the constructors and Begin); the rest of the object file follows from 0x006f34. */


extern short D_1d1074[];
extern unsigned char D_1d1090[];

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
    virtual void f_4(int);
};

/* A queue of sixteen requested states, read at head and written at tail. */
class CStateQueue {
public:
    CStateQueue() { head = tail = 0; }
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
    virtual void f_4(int);

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
    unsigned char m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[12];
    int m240[2];
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
