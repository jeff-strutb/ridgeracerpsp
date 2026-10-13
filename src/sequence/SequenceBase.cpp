/* The sequence base object file (retail 0x038bd0 to 0x0397b4). CSequenceBase is the common
   part of the race sequences: it finds the course record, resets the race information and
   builds the race's working objects (the race state, the two views and the camera), and
   takes them down again. Also here: the sequence factory. */

extern "C" {
void *memcpy(void *, const void *, unsigned int);
void f_029688(void *);
void f_03e344(void);
int f_096f70(void *);
int f_096fdc(void *);
float f_0cd3cc(float);
void f_03a31c(void *);
void f_03a42c(void *);
void f_0a6fac(void *);

void f_0397e4(void *);
void f_03dda0(void *);
void f_0414e4(void *);
}

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
extern CTable D_2407d0;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern char D_242be0[];
extern char D_242dec[];
extern char D_23c820[];

void f_038900();
void f_0389c0();

/* The race information record as the sequences read it. */
struct SeqInfo {
    char m0[76];
    int m76;
    int m80;
};
extern SeqInfo *D_2408f0;

namespace CamCtrl {
class CCamProto {
public:
    virtual ~CCamProto() {}
    virtual void f_07f564();
};
}

/* Camera parts, all made from the camera prototype. */
struct CamPart28 : CamCtrl::CCamProto {
    char m4[24];
};
struct CamPart56 : CamCtrl::CCamProto {
    char m4[52];
};
struct CamPart64 : CamCtrl::CCamProto {
    char m4[60];
};
struct CamPart256 : CamCtrl::CCamProto {
    char m4[252];
};
struct CamPart272 : CamCtrl::CCamProto {
    char m4[268];
};
struct CamPart784 : CamCtrl::CCamProto {
    char m4[780];
};
struct CamPart496 : CamCtrl::CCamProto {
    char m4[492];
};

/* The eye's motion state (made and destroyed elsewhere). */
struct CamMotion {
    char m0[1088] __attribute__((aligned(16)));
    ~CamMotion() { f_0a6fac(this); }
};

namespace CamCtrl {
/* The third person eye. */
class CCamEye3 : public CCamProto {
public:
    virtual ~CCamEye3() {}
    virtual void f_0c4bc4();
    char m4[28];
    CamMotion m32;
    CamPart28 m1120;
    CamPart28 m1148;
    CamPart56 m1176;
    CamPart256 m1232;
    CamPart272 m1488;
    CamPart784 m1760;
    CamPart496 m2544;
};
}

/* The camera's tail: its state and flags. */
struct CamTail {
    int m0;
    int m4;
    int m8;
    int m12[2];
    int m20;
    int m24;
    bool m28;
    char m29[171];
    bool m200;
    char m201[43];
    int m244;
    int m248[6];
    CamTail()
    {
        m0 = 0;
        m244 = 0;
        m200 = 0;
        m8 = 0;
        m20 = 0;
        m28 = 0;
    }
};

/* The race camera's two eyes. Only their constructor's address is known (0x08206c). */
struct f_08206c_t {
    f_08206c_t();
    CamPart64 m0;
    CamCtrl::CCamEye3 m64;
};

/* The race camera (3376 bytes): the eyes and the camera's state. */
struct Camera : f_08206c_t {
    Camera() {}
    CamTail m3104;
};

/* One view of the race (752 bytes). */
struct View {
    int m0;
    int m4;
    int m8;
    char m12[468];
    float fov;
    float aspect;
    float zNear;
    float zFar;
    float cot;
    int count;
    int width;
    int height;
    int m512;
    int m516;
    float cx;
    float cy;
    float m528;
    float m532;
    char m536[72];
    int m608;
    int m612;
    int m616;
    char m620[36];
    int m656;
    char m660[92];
};

/* The race state (52 bytes; made and destroyed elsewhere). */
struct RaceState {
    RaceState() { f_03a31c(this); }
    ~RaceState() { f_03a42c(this); }
    char m0[52];
};

/* The race's job (made by the sequence that uses it). */
class RaceJob {
public:
    virtual ~RaceJob();
    char m4[24];
    int m28;
};

/* The arguments of a sequence's start. */
struct SeqArgs {
    char *course;
    int m4;
    int seed;
    int m12[3];
    int mode;
};

namespace RacePSP {
class CSequenceBase {
public:
    CSequenceBase();
    virtual ~CSequenceBase();
    virtual void f_038fd4();
    virtual int f_038fdc();
    virtual void f_038fe4();
    void f_03913c(SeqArgs *a);
    void f_03924c();
    void f_03925c();
    void f_0392b0();
    void f_039480();
    int f_039588();
    int f_03959c();
    void f_0395b4();
    void f_039608();
    void f_03965c();
    int Sent(int bit) { return m28 & bit; }
    static CSequenceBase *f_0396b0(unsigned int kind);

    char *m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    RaceState *m32;
    View *m36;
    RaceJob *m40;
    int m44;
    char *m48;
    Camera *m52;
    int m56;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
};
}

using namespace RacePSP;

/* @implements 0x038bd0 us _ZN7RacePSP13CSequenceBaseC2Ev
   WHAT IT DOES: Makes the sequence base with none of its working objects. */
CSequenceBase::CSequenceBase()
{
    m16 = 0;
    m32 = 0;
    m36 = 0;
    m40 = 0;
    m52 = 0;
    m60 = 0;
    m68 = 0;
    m48 = 0;
}

/* @implements 0x038c00 us _ZN7RacePSP13CSequenceBaseC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x038c30 us _ZN7RacePSP13CSequenceBaseD2Ev
   WHAT IT DOES: Takes down the sequence's working objects: the camera, the race job, the
   views and the race state. */
CSequenceBase::~CSequenceBase()
{
    delete[] m52;
    delete m40;
    if (m36)
        delete[] m36;
    delete m32;
}

/* @implements 0x038d64 us _ZN7RacePSP13CSequenceBaseD1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x038e98 us _ZN7RacePSP13CSequenceBaseD0Ev
   WHAT IT DOES: The same, then frees the sequence. */

/* @implements 0x038fd4 us f_038fd4
   WHAT IT DOES: Default sequence hook: nothing. */
void CSequenceBase::f_038fd4()
{
}

/* @implements 0x038fdc us f_038fdc
   WHAT IT DOES: Default sequence hook: done. */
int CSequenceBase::f_038fdc()
{
    return 1;
}

/* @implements 0x038fe4 us f_038fe4
   WHAT IT DOES: Ends the sequence: keeps the race job's result and two of the race
   information's values, then takes down the working objects. */
void CSequenceBase::f_038fe4()
{
    m64 = m40->m28;
    m72 = D_2408f0->m76;
    m76 = D_2408f0->m80;
    delete[] m52;
    delete m40;
    if (m36)
        delete[] m36;
    delete m32;
    m32 = 0;
    m36 = 0;
    m40 = 0;
    m52 = 0;
}

/* @implements 0x03913c us f_03913c
   WHAT IT DOES: Starts the sequence: finds the course record by name and its sequence number,
   takes the random seed and the mode, resets the race information (and the result when the
   mode is 0), builds the race state, the views and the camera, and resets the map. */
void CSequenceBase::f_03913c(SeqArgs *a)
{
    char *name = a->course;
    if (name)
        m4 = f_036984(&D_2407d0, name, 0, D_2407d0.index, D_2407d0.count);
    else
        m4 = 0;
    char *f = f_0368e8(&D_2407d0, "SequenceNumber", m4, 0, 0);
    memcpy(D_24063c, f, D_1a211c[1]);
    m12 = D_24063c[0];
    m16 = a->seed;
    m20 = a->mode;
    f_038900();
    if (m20 == 0)
        f_0389c0();
    f_03925c();
    f_0392b0();
    f_039480();
    f_03924c();
    m24 = 0;
    m28 = 0;
    f_03e344();
    f_029688(D_23c820);
}

/* @implements 0x03924c us f_03924c
   WHAT IT DOES: Points the sequence at the race's settings block. */
void CSequenceBase::f_03924c()
{
    m48 = D_242be0;
}

/* @implements 0x03925c us f_03925c
   WHAT IT DOES: Builds the race state. */
void CSequenceBase::f_03925c()
{
    m32 = new RaceState;
}

/* @draft 0x0392b0 us f_0392b0
   WHAT IT DOES: Builds the two views: each full screen (480 by 272, centred), 30 degrees of
   field of view, with its depth range. */
void CSequenceBase::f_0392b0()
{
    View *v = new View[2];
    int i;

    for (i = 0; i < 2; i++) {
        View *e = &v[i];
        e->count = 1;
        e->m0 = 0;
        e->m4 = 0;
        e->m8 = 0;
        e->fov = 0.523598f;
        e->cot = 1.0f / f_0cd3cc(0.523598f);
        e->width = e->count * 480;
        e->zNear = 300.0f;
        e->zFar = 2000000.0f;
        e->m528 = 1400.0f;
        e->m532 = 1400.0f;
        e->aspect = 1.76471f;
        e->m512 = 2048;
        e->m516 = 2048;
        e->height = 272;
        e->cx = 240.0f;
        e->cy = 136.0f;
        e->fov = 0.523598f;
        e->cot = 1.0f / f_0cd3cc(0.523598f);
        e->zNear = 300.0f;
        e->zFar = 3000000.0f;
        e->fov = 0.523598f;
        e->cot = 1.0f / f_0cd3cc(0.523598f);
        e->m608 = 0;
        e->m612 = 0;
        e->m616 = 0;
        e->m656 = 0;
    }
    m36 = v;
}

/* @draft 0x039480 us f_039480
   WHAT IT DOES: Builds the race camera and clears its state. */
void CSequenceBase::f_039480()
{
    m52 = new Camera[1];
}

/* @implements 0x039588 us f_039588
   WHAT IT DOES: Returns the sequence's result, 1 when none was set. */
int CSequenceBase::f_039588()
{
    int r = m68;
    if (r == 0)
        r = 1;
    return r;
}

/* @implements 0x03959c us f_03959c
   WHAT IT DOES: Tells whether the sequence's flag is set. */
int CSequenceBase::f_03959c()
{
    int r = 0;
    if (m24)
        r = 1;
    return r;
}

/* @implements 0x0395b4 us f_0395b4
   WHAT IT DOES: In mode 0, sends the first race message once. */
void CSequenceBase::f_0395b4()
{
    if (m20 == 0 && !Sent(1)) {
        f_096f70(D_242dec);
        m28 |= 1;
    }
}

/* @implements 0x039608 us f_039608
   WHAT IT DOES: In mode 0, sends the second race message once. */
void CSequenceBase::f_039608()
{
    if (m20 == 0 && !Sent(2)) {
        f_096fdc(D_242dec);
        m28 |= 2;
    }
}

/* @implements 0x03965c us f_03965c
   WHAT IT DOES: In mode 0, sends the second race message once more (its own flag). */
void CSequenceBase::f_03965c()
{
    if (m20 == 0 && !Sent(4)) {
        f_096fdc(D_242dec);
        m28 |= 4;
    }
}

/* Sequences made elsewhere: plain blocks whose constructors call theirs. */
struct SeqCircuit {
    SeqCircuit() { f_0397e4(this); }
    char m[80];
};
struct SeqKind2 {
    SeqKind2() { f_03dda0(this); }
    char m[80];
};
struct SeqKind3 {
    SeqKind3() { f_0414e4(this); }
    char m[80];
};

/* @implements 0x0396b0 us f_0396b0
   WHAT IT DOES: Makes the sequence of the given kind: 1, 4 and 5 are the normal circuit
   race, 2 and 3 two other kinds; 0 and anything else make none. */
CSequenceBase *CSequenceBase::f_0396b0(unsigned int kind)
{
    CSequenceBase *s;

    switch (kind) {
    case 1:
        s = (CSequenceBase *)new SeqCircuit;
        break;
    default:
        s = 0;
        break;
    case 2:
        s = (CSequenceBase *)new SeqKind2;
        break;
    case 3:
        s = (CSequenceBase *)new SeqKind3;
        break;
    case 4:
        s = (CSequenceBase *)new SeqCircuit;
        break;
    case 5:
        s = (CSequenceBase *)new SeqCircuit;
        break;
    }
    return s;
}
