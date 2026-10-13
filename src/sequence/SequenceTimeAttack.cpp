/* The time attack sequence object file (retail 0x03dd70 to 0x03e344,
   "RacePSP::CSequenceTimeAttack"). The sequence of a time attack race: it starts the race
   (the car job controller, the race job, the views, the course and the sound), steps it through
   its state table each frame and takes it down at the end. */

extern "C" {
void f_0eee74(void *);
void f_0eefd8(void *, void *);
int f_07df70(void *);
void f_07dff0(void *cam, void *view0, void *view1, void *car, void *table, int count, int replay, int a7,
              int a8, int a9, int a10);
void f_01d17c(void *, char *course, int count, void *table, void *views, int a5);
void f_0941c8(void *, int);
void f_096368(void *, void *);
void f_08d764(char *);
void f_031b98(void *, int);
void f_0eaca0(void *, int, void *);
void f_089438(int);
void f_0894b0(void *, int);
void f_0eae7c(void *);
void f_031d4c(void *);
void f_094214(void *);
void f_01d934(void *);
void f_08d7f0(char *);
void f_07e6d0(void *);
}

/* A row of a table named by its interned name. */
struct Name {
    int a;
    int b;
    Name() {}
    Name(const Name &o)
    {
        a = o.a;
        b = o.b;
    }
};

/* A table of the game database. */
struct CTable {
    int m0;
    int nCols;
    int nRows;
    int m12;
    int m16;
    int *colNames;
    int *rowNames;
    const char *f_036984(const char *name, int add, int *names, int count);
    void *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
    Name Find(const char *name)
    {
        Name r;
        if (name)
            r.a = (int)f_036984(name, 0, rowNames, nRows);
        else
            r.a = 0;
        return r;
    }
};
extern CTable D_2407d0;
extern CTable D_2407a8;

/* The course the race runs on, as the course code reads it. */
struct CourseSel {
    int a;
    int b;
    void Set(Name n)
    {
        a = n.a;
        b = n.b;
    }
};
extern CourseSel D_27ecd0;

extern char D_242c90[];
extern char D_242cb0[];
extern char D_23be80[];
extern char D_2402e0[];

/* The sound player. */
class CSound {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int, int);
    virtual void v3(int);
};
extern CSound *D_1d3d40;

/* Three words copied as one. */
struct Vec3 {
    int x;
    int y;
    int z;
};

/* The cars to make, as the car job controller reads them. */
struct CarList {
    int m[38];
};

/* The arguments of a sequence's start. */
struct SeqArgs {
    char *course;
    int m4;
    int seed;
    int m12;
    int m16;
    int m20;
    int mode;
    int m28;
    CarList list;
    char m184[388];
    int m572;
    int m576;
    int m580;
    int m584;
    int m588;
    int m592;
    int m596;
    Vec3 m600[3];
    int m636;
    int m640;
    int m644;
    int m648;
};

/* What the race job is made from. */
struct RaceJobArgs {
    Name course;
    int seed;
    int m12;
    int mode;
    int m20;
    void *cars;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int m52;
    Vec3 m56[3];
    int m92;
    int m96;
    int m100;
    int m104;
};

/* The car job controller (its own object file). */
struct CCarJobCtrlPSP {
    char *m0;
    int m4;
    int m8;
    int m12;
    int m16;
    void *m20;
    void *m24;
    void **m28;
    void **m32;
    int m36;
    int m40;
    int m44;
    int m48;
    void f_03a51c(void *setup, int seed, CarList *l);
    void *f_03b518(int i);
    void f_03b400();
};

/* One view of the race (752 bytes). */
struct View {
    char m0[656];
    int m656;
    int m660;
    int m664;
    int m668;
    char m672[80];
};

/* The race's job (made here). */
class RaceJob {
public:
    virtual ~RaceJob();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

/* The race job's block as it is built. */
struct RaceJobBlock {
    RaceJobBlock() { f_0eee74(this); }
    char m[164];
};

typedef int (*StateFn)();

namespace RacePSP {
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
    CCarJobCtrlPSP *m32;
    View *m36;
    RaceJob *m40;
    int m44;
    char *m48;
    void *m52;
    int m56;
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

class CSequenceTimeAttack : public CSequenceStandard {
public:
    CSequenceTimeAttack();
    virtual ~CSequenceTimeAttack();
    virtual void f_038fd4(SeqArgs *a);
    virtual int f_038fdc();
    virtual void f_038fe4();
};
}

using namespace RacePSP;

typedef int (CSequenceTimeAttack::*SeqHandler)();
extern SeqHandler D_1d1c2c[];

/* @implements 0x03dd70 us _ZN7RacePSP19CSequenceTimeAttackC2Ev
   WHAT IT DOES: Builds the time attack sequence on the sequence base. */
CSequenceTimeAttack::CSequenceTimeAttack()
{
}

/* @implements 0x03dda0 us _ZN7RacePSP19CSequenceTimeAttackC1Ev
   WHAT IT DOES: The complete-object copy of the constructor above. */

/* @implements 0x03ddd0 us _ZN7RacePSP19CSequenceTimeAttackD2Ev
   WHAT IT DOES: Destroys the sequence (the sequence base's destructor). */
CSequenceTimeAttack::~CSequenceTimeAttack()
{
}

/* @implements 0x03ddf8 us _ZN7RacePSP19CSequenceTimeAttackD1Ev
   WHAT IT DOES: The complete-object copy of the destructor above. */

/* @implements 0x03de20 us _ZN7RacePSP19CSequenceTimeAttackD0Ev
   WHAT IT DOES: The deleting destructor. */

/* @draft 0x03de58 us CSequenceTimeAttack8f_038fd4
   WHAT IT DOES: Starts a time attack race: starts the sequence base, picks the first state
   (2 in a replay), selects the course, sets the car job controller up with the next random
   seed, makes the race job from the race's settings, sets up the two views, the camera, the
   course's map, the ghost record and the sound. */
void CSequenceTimeAttack::f_038fd4(SeqArgs *a)
{
    f_03913c(a);
    if (m20)
        m56 = 2;
    else
        m56 = 1;
    D_27ecd0.Set(D_2407a8.Find((const char *)D_2407d0.f_0368e8("CourseNumber", m4, 0, 0)));
    m16 = m16 * 0x19660d + 0x3c6ef35f;
    m32->f_03a51c(&m4, m16, &a->list);
    RaceJob *job = (RaceJob *)new RaceJobBlock;
    RaceJobArgs r;
    Name n = D_2407d0.Find(m4);
    r.course.a = n.a;
    r.course.b = n.b;
    m16 = m16 * 0x19660d + 0x3c6ef35f;
    r.seed = m16;
    r.m12 = a->m12;
    r.mode = m20;
    r.m20 = a->m28;
    r.cars = m32;
    r.m28 = a->m580;
    r.m32 = a->m584;
    r.m44 = a->m588;
    r.m48 = a->m592;
    for (int k = 0; k < 3; k++)
        r.m56[k] = a->m600[k];
    r.m52 = f_07df70(m52);
    r.m40 = a->m572;
    r.m96 = a->m640;
    r.m100 = a->m644;
    r.m104 = a->m648;
    r.m92 = a->m636;
    f_0eefd8(job, &r);
    View *v = m36;
    m40 = job;
    v[0].m668 = 1;
    v[0].m656 = 0;
    v[1].m668 = 0;
    v[1].m656 = 3;
    void *car = m32->f_03b518(0);
    f_07dff0(m52, &m36[0], &m36[1], car, m32->m32, m32->m12 + m32->m16, m20 != 0, 0, 0, 0, 0);
    f_01d17c(D_23be80, m4, m32->m12 + m32->m16, m32->m32, m36, 0);
    Name c = D_2407a8.Find((const char *)D_2407d0.f_0368e8("CourseNumber", m4, 0, 0));
    Name t = c;
    f_0941c8(D_242c90, t.a);
    f_096368(D_242cb0, &t);
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

/* @implements 0x03e224 us CSequenceTimeAttack8f_038fdc
   WHAT IT DOES: The frame step: back to the first state once the sequence's flag is set, then
   runs the current state's handler and returns its result. */
int CSequenceTimeAttack::f_038fdc()
{
    if (f_03959c())
        m56 = 0;
    return (this->*D_1d1c2c[m56])();
}

/* @implements 0x03e2b0 us CSequenceTimeAttack8f_038fe4
   WHAT IT DOES: Ends the race: takes down the sequence's course side, the ghost record, the
   map and the settings, stops the sound and the race job, frees the camera's race data and the
   cars, then ends the sequence base. */
void CSequenceTimeAttack::f_038fe4()
{
    f_0eae7c(this);
    f_031d4c(D_2402e0);
    f_094214(D_242c90);
    f_01d934(D_23be80);
    f_08d7f0(m48);
    D_1d3d40->v3(0);
    m40->v4();
    f_07e6d0(m52);
    m32->f_03b400();
    CSequenceBase::f_038fe4();
}
