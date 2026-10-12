/* The save and load mode job, its start (retail 0x0117fc to 0x011ec8): the constructors and
   Begin. The save and load job runs the menu that loads, saves and deletes the game's save
   data on the memory stick; the rest of the class (from its Step at 0x011ec8) is in
   SaveLoadModeJob.cpp, which also defines Begin as the class's key function. The object file
   this part sits in follows the wireless battle mode job's inline functions. */

extern short D_1d146c[];
extern unsigned char D_1d1498[];
extern int D_237cc8;

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

/* @implements 0x0117fc us _ZN8Sequence16CSaveLoadModeJobC2Ev
   WHAT IT DOES: Constructs the save and load mode job: an empty event queue, the table of
   state handlers and the job's script. */
/* @implements 0x011b50 us _ZN8Sequence16CSaveLoadModeJobC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */
Sequence::CSaveLoadModeJob::CSaveLoadModeJob()
{
    states[0] = &CSaveLoadModeJob::f_01205c;
    states[1] = &CSaveLoadModeJob::f_012064;
    states[2] = &CSaveLoadModeJob::f_012094;
    states[3] = &CSaveLoadModeJob::f_01209c;
    states[4] = &CSaveLoadModeJob::f_012234;
    states[5] = &CSaveLoadModeJob::f_01223c;
    states[6] = &CSaveLoadModeJob::f_0122bc;
    states[7] = &CSaveLoadModeJob::f_0123ac;
    states[8] = &CSaveLoadModeJob::f_0123b4;
    states[9] = &CSaveLoadModeJob::f_0123d8;
    states[10] = &CSaveLoadModeJob::f_0125dc;
    states[11] = &CSaveLoadModeJob::f_0125e4;
    states[12] = &CSaveLoadModeJob::f_012604;
    states[13] = &CSaveLoadModeJob::f_012740;
    states[14] = &CSaveLoadModeJob::f_012748;
    states[15] = &CSaveLoadModeJob::f_01276c;
    states[16] = &CSaveLoadModeJob::f_012804;
    states[17] = &CSaveLoadModeJob::f_01280c;
    states[18] = &CSaveLoadModeJob::f_01288c;
    states[19] = &CSaveLoadModeJob::f_01299c;
    states[20] = &CSaveLoadModeJob::f_0129a4;
    states[21] = &CSaveLoadModeJob::f_0129cc;
    states[22] = &CSaveLoadModeJob::f_012a28;
    states[23] = &CSaveLoadModeJob::f_012a30;
    states[24] = &CSaveLoadModeJob::f_012ad4;
    states[25] = &CSaveLoadModeJob::f_012b30;
    states[26] = &CSaveLoadModeJob::f_012b38;
    m52 = D_1d146c;
    m56 = D_1d1498;
}

/* @draft 0x011ea4 us _ZN8Sequence16CSaveLoadModeJob5BeginEv
   WHAT IT DOES: Starts the mode from its first state, with the saved option value.
   Remaining difference: retail keeps the frame counter store first (sw zero,68 before the
   load of D_237cc8) and holds the loaded value in a1 with li v1,1 issued before the load;
   every order of these five statements (and a volatile source) gives the load first and the
   counter store after it. */
void Sequence::CSaveLoadModeJob::Begin()
{
    m68 = 0;
    m360 = D_237cc8;
    m60 = 1;
    m64 = 0;
    m68 = 0;
    state = 0;
}
