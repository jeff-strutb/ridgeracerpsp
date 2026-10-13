/* The normal circuit race sequence object file (retail 0x0397b4 to 0x039de0,
   "RacePSP::CSequenceRaceNormalCircuit"). The sequence that runs one normal circuit race: it
   sets up the course, the cars, the race information, the views, the replay and the sound from
   the start arguments, runs the race states and tears the race objects down at its end. */

extern "C" {
void f_0eae7c(void);
void f_031d4c(void *);
void f_094214(void *);
void f_01d934(void *);
void f_08d7f0(void *);
void f_07e6d0(void *);
void f_03b400(void *);
void f_08d764(void *);
void f_031b98(void *, int);
void f_0eaca0(void *, int, void *);
void f_089438(int);
void f_0894b0(void *snd, int ms);
void f_0941c8(void *, char *);
int f_07df70(void *);
void f_07dff0(void *rp, void *v0, void *v1, void *car, int a, int b, int net, int c, int d, int e, int f);
void f_01d17c(void *snd, char *course, int b, int c, void *views, int d);
int f_03b518(void *ctrl, int i);
}
extern char D_2402e0[];
extern char D_242c90[];
extern char D_242cb0[];
extern char D_23be80[];

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};
extern "C" void f_096368(void *bgm, Rec r);
extern Rec D_27ecd0;

/* A table of the game database: records found by index or by name. */
struct CTable;
extern "C" char *f_0368e8(CTable *t, const char *field, char *rec, int a, int b);
extern "C" char *f_036984(CTable *t, char *name, int i, int *index, int count);
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
    int m28[2];
    char *base;
};
extern CTable D_2407a8;
extern CTable D_2407d0;

/* The sound system. */
class CSound {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int a, int b);
    virtual void v3(int a);
    virtual void v4();
    virtual void v5();
};
extern CSound *D_1d3d40;

/* Three words of the start arguments copied as a block. */
struct Tri {
    int v[3];
};

/* The start arguments of a race. */
struct SeqArgs {
    char m0[12];
    int m12;
    char m16[12];
    int m28;
    char m32[548];
    int m580;
    int m584;
    int m588;
    int m592;
    char m596[4];
    Tri m600[3];
    int m636;
    int m640;
    int m644;
    int m648;
};

/* The race information's start parameters. */
struct InfoParams {
    Rec course;
    int seed;
    int m12;
    int mode;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36[2];
    int m44;
    int m48;
    int replay;
    Tri m56[3];
    int m92;
    int m96;
    int m100;
    int m104;
};

/* The race's car controller. */
struct CarCtrl {
    char m0[12];
    int m12;
    int m16;
    char m20[12];
    void *m32;
};

/* One view of the race. */
struct View {
    char m0[656];
    int m656;
    char m660[8];
    int m668;
    char m672[80];
};

/* The race information of a normal circuit race (made elsewhere). */
class f_03e3b8_t {
public:
    f_03e3b8_t();
    virtual ~f_03e3b8_t();
    virtual int v2();
    virtual void v3();
    virtual void v4();
    char m4[140];
};
extern "C" void f_03e51c(f_03e3b8_t *info, InfoParams *p);
extern "C" void f_03a51c(CarCtrl *ctrl, char **setup, int seed, char *list, Rec course);

namespace RacePSP {
class CSequenceBase;
typedef int (CSequenceBase::*Handler)();

/* The base of every sequence (made by its own object file). */
class CSequenceBase {
public:
    CSequenceBase();
    virtual ~CSequenceBase();
    virtual void f_038fd4(SeqArgs *a);
    virtual int f_038fdc();
    virtual void f_038fe4();
    void f_03913c(SeqArgs *a);
    int f_03959c();
    char *m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    CarCtrl *m32;
    View *m36;
    f_03e3b8_t *m40;
    int m44;
    void *m48;
    void *m52;
    int state;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
};

class CSequenceStandard : public CSequenceBase {
public:
    CSequenceStandard() {}
    virtual ~CSequenceStandard() {}
};

class CSequenceRaceNormalCircuit : public CSequenceStandard {
public:
    CSequenceRaceNormalCircuit();
    virtual ~CSequenceRaceNormalCircuit();
    virtual void f_038fd4(SeqArgs *a);
    virtual int f_038fdc();
    virtual void f_038fe4();
};
}

using namespace RacePSP;

extern Handler D_1d1c14[];

/* @implements 0x0397b4 us _ZN7RacePSP26CSequenceRaceNormalCircuitC2Ev
   WHAT IT DOES: Builds the sequence on its base. */
CSequenceRaceNormalCircuit::CSequenceRaceNormalCircuit()
{
}

/* @implements 0x0397e4 us _ZN7RacePSP26CSequenceRaceNormalCircuitC1Ev
   WHAT IT DOES: The complete-object copy of the constructor above. */

/* @implements 0x039814 us _ZN7RacePSP26CSequenceRaceNormalCircuitD2Ev
   WHAT IT DOES: Tears the sequence down through its base. */
CSequenceRaceNormalCircuit::~CSequenceRaceNormalCircuit()
{
}

/* @implements 0x03983c us _ZN7RacePSP26CSequenceRaceNormalCircuitD1Ev
   WHAT IT DOES: The complete-object copy of the destructor above. */

/* @implements 0x039864 us _ZN7RacePSP26CSequenceRaceNormalCircuitD0Ev
   WHAT IT DOES: The deleting destructor. */

/* @draft 0x03989c us CSequenceRaceNormalCircuit8f_038fd4
   WHAT IT DOES: Starts the race: the base start, then the first state (2 in a replay, else
   1), the course's record, the cars (with a new random seed), the race information (with
   another seed, the start arguments' grid and the replay), both views' modes, the replay, the
   race sound, the music, the race effects and the camera, and the race sound mode and a 3
   second sound fade in. */
void CSequenceRaceNormalCircuit::f_038fd4(SeqArgs *a)
{
    CSequenceBase::f_03913c(a);
    int s = 1;
    if (m20)
        s = 2;
    state = s;
    {
        Rec r;
        char *n = f_0368e8(&D_2407d0, "CourseNumber", m4, 0, 0);
        if (n)
            r.rec = f_036984(&D_2407a8, n, 0, D_2407a8.index, D_2407a8.count);
        else
            r.rec = 0;
        D_27ecd0 = r;
        m16 = m16 * 0x19660d + 0x3c6ef35f;
        f_03a51c(m32, &m4, m16, a->m32, r);
    }
    f_03e3b8_t *info = new f_03e3b8_t;
    {
        InfoParams p;
        if (m4)
            p.course.rec = f_036984(&D_2407d0, m4, 0, D_2407d0.index, D_2407d0.count);
        else
            p.course.rec = 0;
        m16 = m16 * 0x19660d + 0x3c6ef35f;
        p.seed = m16;
        p.m12 = a->m12;
        p.mode = m20;
        p.m20 = a->m28;
        p.m24 = (int)m32;
        p.m28 = a->m580;
        p.m32 = a->m584;
        p.m44 = a->m588;
        p.m48 = a->m592;
        for (int i = 0; i < 3; i++)
            p.m56[i] = a->m600[i];
        p.replay = f_07df70(m52);
        p.m92 = a->m636;
        p.m96 = a->m640;
        p.m100 = a->m644;
        p.m104 = a->m648;
        f_03e51c(info, &p);
    }
    m40 = info;
    m36[0].m668 = 1;
    m36[0].m656 = 0;
    m36[1].m668 = 0;
    m36[1].m656 = 3;
    f_07dff0(m52, m36, &m36[1], (void *)f_03b518(m32, 0), (int)m32->m32, m32->m12 + m32->m16, m20 != 0, 0, 0, 0, 0);
    f_01d17c(D_23be80, m4, m32->m12 + m32->m16, (int)m32->m32, m36, 0);
    {
        Rec r;
        char *n = f_0368e8(&D_2407d0, "CourseNumber", m4, 0, 0);
        if (n)
            r.rec = f_036984(&D_2407a8, n, 0, D_2407a8.index, D_2407a8.count);
        else
            r.rec = 0;
        f_0941c8(D_242c90, r.rec);
        f_096368(D_242cb0, r);
    }
    f_08d764(m48);
    f_031b98(D_2402e0, m32->m12 + m32->m16);
    f_0eaca0(m32, a->m636, m52);
    int k = m20 == 1;
    if (m20 == 2)
        k = 2;
    f_089438(k);
    D_1d3d40->v2(a->m636, 0);
    f_0894b0(D_1d3d40, 3000);
}

/* @implements 0x039c60 us CSequenceRaceNormalCircuit8f_038fdc
   WHAT IT DOES: Returns to the idle state once the base reports the end, then runs the
   handler of the current state. */
int CSequenceRaceNormalCircuit::f_038fdc()
{
    if (f_03959c())
        state = 0;
    return (this->*D_1d1c14[state])();
}

/* @implements 0x039cec us CSequenceRaceNormalCircuit8f_038fe4
   WHAT IT DOES: Ends the race: releases the race objects, the course, the music, the sound,
   the race information, the replay and the cars, then runs the base's end. */
void CSequenceRaceNormalCircuit::f_038fe4()
{
    f_0eae7c();
    f_031d4c(D_2402e0);
    f_094214(D_242c90);
    f_01d934(D_23be80);
    f_08d7f0(m48);
    D_1d3d40->v3(0);
    m40->v4();
    f_07e6d0(m52);
    f_03b400(m32);
    CSequenceBase::f_038fe4();
}

/* @implements 0x039d80 us _ZN7RacePSP17CSequenceStandardD0Ev
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The standard sequence's deleting destructor. */

/* @implements 0x039db8 us _ZN7RacePSP17CSequenceStandardD1Ev
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The standard sequence's destructor. */
