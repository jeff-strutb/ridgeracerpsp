/* The normal circuit race information object file (retail 0x03e364 to 0x03fe80,
   "RacePSP::CInfoRaceNormalCircuit"). The information side of a normal circuit race: a state
   machine (countdown, race, final lap, finish, result and replay states) stepped once a frame,
   which keeps the shared race information record up to date and decides when the race, the
   replay and the camera changes happen. */

extern "C" {
void f_0ede54(void *);
void f_0edec0(void *);
void f_0ee584(void *);
void f_0ee624(void *);
int f_0ee6b8(void *);
void f_0ee788(void *);
void f_0ee76c(void *);
void f_0ee1d8(void *, int);
int f_0ee66c(void *);
void f_0ee704(void *, int, int);
int f_0a8d5c(void *pos, float *at, int a, int b, int c);
void f_037d50(void *);
void f_037f48(void *);
int f_094254(void *);
float f_0eede0(int count, int n, float x);
}
extern char D_242c90[];
extern int D_27eccc;

/* A row of a table named by its interned name, as the lookups return it (see
   src/sequence/RaceSetup.cpp). */
struct Name {
    int a;
    int b;
    Name() {}
    Name(const Name &o) { a = o.a; b = o.b; }
};

/* A name and row kept in a record. */
struct Slot {
    int a;
    int b;
    Slot &operator=(const Name &n)
    {
        a = n.a;
        b = n.b;
        return *this;
    }
};

/* A table of the game database (src/system/DataBase.cpp). */
struct CTable {
    int m0;
    int nCols;
    int nRows;
    int m12;
    int m16;
    int *colNames;
    int *rowNames;
    int m28;
    int m32;
    char *strings;

    const char *f_036984(const char *name, int add, int *names, int count);
    void *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);

    void *Get(const char *col, const char *row, int i) { return f_0368e8(col, row, i, 0); }
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
extern CTable D_2407d0; /* the race sequences */
extern CTable D_2407a8; /* the courses */
extern CTable D_240740; /* the cars */
extern unsigned char D_24063c[]; /* a field read from a table */
extern const int D_1a211c[];     /* the size of each field type */
extern "C" void *memcpy(void *, const void *, unsigned int);

/* The race information record shared by the sequences. */
struct RaceLaps;
struct InfoCar;
struct RaceInfo {
    Slot seq;    /* the race sequence (its row in the sequence table) */
    Slot course; /* the course (its row in the course table) */
    int m16;     /* the sequence number */
    int m20;     /* a replay */
    int m24;   /* laps of the race */
    int m28;
    int m32;   /* laps to go */
    int m36;
    int m40;
    int m44;
    int m48;   /* race clock */
    int m52;
    int m56;   /* race phase */
    int m60;   /* cars racing */
    int m64;   /* a time trial sequence */
    int m68;   /* the qualifying place */
    int m72;
    int m76;
    int m80;
    int m84;
    int m88;
    int m92;
    Slot car;  /* the player's car (its row in the car table) */
    int m104;
    int m108;  /* the player's laps */
    int m112;  /* the player's place */
    int m116;  /* lap clock */
    int m120;  /* last lap time */
    int m124;  /* best lap time */
    int m128;  /* best lap */
    int m132;  /* race time */
    int m136;  /* finishing time */
    int m140[4];
    float m156; /* the engine's red zone */
    float m160; /* the engine's top revs */
    int m164[8];
    InfoCar *m196; /* the player's car */
    RaceLaps *m200;
    int m204;
    int m208;
    void *m212; /* the ranking's standing table */
    int m216;
    int m220;
};
extern RaceInfo *D_2408f0;
extern RaceInfo *D_2407fc;

/* The race's lap timing block (see src/sequence/InfoTimeAttack.cpp). */
struct RaceLaps {
    int m0[99][3];      /* the player's time at each sector end, per lap */
    int m1188[99][3];
    int m2376;          /* the player's sector */
    int m2380;
    int m2384;          /* the player's lap */
    int m2388;
    float m2392[3];     /* where each sector ends */
    int m2404;          /* sectors per lap */
    int m2408[13][99][3]; /* every car's time at each sector end */
    int m17852[13];     /* every car's sector */
    int m17904[13];     /* every car's lap */
    InfoCar *m17956[13]; /* the cars */
    int m18008[3][3];   /* the target times of each lap's sectors */
};

/* The race result (see src/sequence/SingleRaceModeJob.cpp). */
struct Tri {
    int v[3];
};
struct RaceResult {
    int m0;
    int m4[29];
    int time[14];
    float lap[3];
    int me;
    int best[3];
    Tri rec[3];
};
extern RaceResult D_240800;

/* The race settings (made elsewhere). */
struct RaceSettings {
    int m0[2];
    int m8;
};
extern RaceSettings D_23f7f0;

/* The game's settings that pause the race. */
struct GameFlags {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern GameFlags *D_1d88a0;

/* The player's car as the information reads it. */
struct InfoCar {
    char m0[92];
    Name m92;        /* the car (its row in the car table) */
    char m100[24];
    int m124;
    char m128[2000];
    char m2128[84];  /* the course position tracker */
    int m2212;       /* laps done */
    char m2216[7900];
    void *m10116;    /* the car's input */
};

/* The car job controller (src/race/CarJobCtrl.cpp). */
struct CCarJobCtrlPSP {
    char m0[12];
    int m12;  /* the player's cars */
    int m16;  /* the other cars */
    char m20[8];
    int m28;
    int m32;
    InfoCar *f_03b518(int i);
    InfoCar *f_03b530(int i);
};

/* The recorder and player of a car's inputs (src/race/PlayerInputProxy.cpp). */
struct CPlayerInputProxy {
    void f_037d6c(int m, int mirrored);
    void f_0386a8();
};

/* What the race information is made from (the sequence's race setup). */
struct InfoSetup {
    const char *m0;   /* the race sequence's name */
    int m4;
    int m8;           /* the random seed */
    int m12;          /* laps of the race */
    int m16;          /* a replay */
    int m20;          /* the frame the replay ends on */
    CCarJobCtrlPSP *m24; /* the cars */
    CPlayerInputProxy *m28; /* the player's inputs */
    CPlayerInputProxy *m32;
    int m36[2];
    int m44;
    int m48;
    int m52;          /* seconds of countdown */
    int m56[3][3];    /* the target times of each lap's sectors (0x7fffffff: none) */
    int m92;          /* the course is mirrored */
    int m96;
    int m100;
    int m104;
};

extern "C" void f_0edf18(void *, CCarJobCtrlPSP *ctrl, Slot laps, int single, float f);

/* The ranking checker and race camera director (src/race/CheckRanking.cpp), made and
   destroyed with the information. */
struct CDirector {
    CDirector() { f_0ede54(this); }
    ~CDirector() { f_0edec0(this); }
    void f_0ee584() { ::f_0ee584(this); }
    void f_0ee624() { ::f_0ee624(this); }
    int f_0ee6b8() { return ::f_0ee6b8(this); }
    void f_0ee788() { ::f_0ee788(this); }
    void f_0ee76c() { ::f_0ee76c(this); }
    void f_0ee1d8(int from) { ::f_0ee1d8(this, from); }
    int f_0ee66c() { return ::f_0ee66c(this); }
    void f_0ee704(int t, int t2) { ::f_0ee704(this, t, t2); }
    void Init(CCarJobCtrlPSP *ctrl, Slot laps, int single, float f) { f_0edf18(this, ctrl, laps, single, f); }
    int Running() { return m20; }
    void *Standing() { return m24; }
    char m0[20];
    int m20;
    void *m24; /* the standing table */
};

namespace RacePSP {
/* The information base (its own object file). */
class CInfoBase {
public:
    CInfoBase();
    virtual ~CInfoBase();
    virtual int f_038a54();
    virtual void f_038a5c();
    virtual void f_038a64();
    virtual void f_038a78();
    void f_038a6c();
    int f_038af4();
    void f_038a80(int);
    int m4[4];
    unsigned int m20;
};

class CInfoRaceNormalCircuit;
typedef int (CInfoRaceNormalCircuit::*InfoHandler)();

class CInfoRaceNormalCircuit : public CInfoBase {
public:
    CInfoRaceNormalCircuit();
    virtual ~CInfoRaceNormalCircuit();
    virtual int f_038a54();
    virtual void f_038a64();
    virtual void f_038a78();
    void f_03e51c(InfoSetup *s);
    int Qualify()
    {
        memcpy(D_24063c, D_2407d0.Get("QualifyPos", (const char *)m4[0], 0), D_1a211c[1]);
        return D_24063c[0];
    }
    int f_03f1c8();
    int f_03f25c();
    int f_03f2f0();
    int f_03f394();
    int f_03f480();
    int f_03f51c();
    int f_03f5b8();
    void f_03f61c();
    void f_03fb40();

    int frame() { return m4[3]; }

    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int m52;
    int m56;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
    CPlayerInputProxy *m80; /* the player's inputs */
    CPlayerInputProxy *m84;
    int state;
    InfoCar *car;
    int m96;
    int m100;
    int m104;
    CDirector director;
};
}

using namespace RacePSP;

extern InfoHandler D_1d1c44[];

/* @implements 0x03e364 us _ZN7RacePSP22CInfoRaceNormalCircuitC2Ev
   WHAT IT DOES: builds the information on its base and makes its camera director. */
CInfoRaceNormalCircuit::CInfoRaceNormalCircuit()
{
}

/* @implements 0x03e3b8 us _ZN7RacePSP22CInfoRaceNormalCircuitC1Ev
   WHAT IT DOES: the complete-object copy of the constructor above. */

/* @implements 0x03e40c us _ZN7RacePSP22CInfoRaceNormalCircuitD2Ev
   WHAT IT DOES: destroys the camera director, then the base. */
CInfoRaceNormalCircuit::~CInfoRaceNormalCircuit()
{
}

/* @implements 0x03e464 us _ZN7RacePSP22CInfoRaceNormalCircuitD1Ev
   WHAT IT DOES: the complete-object copy of the destructor above. */

/* @implements 0x03e4bc us _ZN7RacePSP22CInfoRaceNormalCircuitD0Ev
   WHAT IT DOES: the deleting destructor. */

/* The course of a race sequence: the course table's row named by the sequence's course
   number. */
static inline Name CourseOf(const char *seq)
{
    Name c = D_2407a8.Find((const char *)D_2407d0.Get("CourseNumber", seq, 0));
    return c;
}

/* Whether the race's sequence has the given number. */
static inline bool SeqIs(int n)
{
    memcpy(D_24063c, D_2407d0.Get("SequenceNumber", (const char *)D_2408f0->seq.a, 0), D_1a211c[1]);
    return D_24063c[0] == n;
}

/* @draft 0x03e51c us f_03e51c
   WHAT IT DOES: sets the information up for the race from the sequence's race setup: looks
   up the race sequence and its number, clears the frame count, takes the random seed, the
   replay flag and frames (the end and its timed events; none outside the replay) and the
   player's inputs (recording, or playing back in the replay). Then fills the race
   information record: the sequence and course rows, the number, the replay flag, the laps,
   the clock (three hours to go, the countdown before zero after a random wait), the number
   of cars, whether the sequence is a time trial, the qualifying place (sequences 4 and 5),
   the player's car (its finish kind 2 until it crosses the line, its row, its engine's red
   zone and top revs from the car table), the lap and sector counters, the course's sectors
   and where each ends (no times yet), outside the replay each lap's sector target times
   (the setup's, or defaults by the number of sectors), the course sizes, and starts the
   ranking checker on the cars (the standing table and the director's shot); finally the
   ranking's car of each place.
   Remaining difference: the control flow, calls and stores follow retail, but the frame is
   96 bytes against 112. Retail gives each row temporary its own stack slot (the sequence row
   at 0, the course row found at 32 and copied to 16, the car row copied to 48; the ranking's
   laps reuse 32), here they all share 0 (the same open residue as the wireless 0x0f0aa8).
   With fewer slots the registers differ: here D_2408f0's high part is held in fp and the
   record pointer for the qualifying place is spilled, where retail rematerialises the lui at
   every read and keeps the pointer in s7. */
void CInfoRaceNormalCircuit::f_03e51c(InfoSetup *s)
{
    f_038a6c();
    const char *name = s->m0;
    if (name)
        m4[0] = (int)D_2407d0.f_036984(name, 0, D_2407d0.rowNames, D_2407d0.nRows);
    else
        m4[0] = 0;
    memcpy(D_24063c, D_2407d0.Get("SequenceNumber", (const char *)m4[0], 0), D_1a211c[1]);
    m4[2] = D_24063c[0];
    m4[3] = 0;
    m20 = s->m8;
    state = 0;
    m24 = s->m16;
    if (m24) {
        m96 = s->m20;
        m48 = 0;
        m28 = s->m20;
        m60 = s->m20 - 60;
    } else {
        m60 = -1;
        m96 = -1;
        m28 = -1;
        m48 = 0;
    }
    m80 = s->m28;
    m84 = s->m32;
    m44 = -1;
    m36 = 0;
    m40 = 0;
    m72 = 0;
    m104 = 0;
    m76 = 0;
    if (m24) {
        m80->f_037d6c(1, s->m92);
    } else {
        m80->f_037d6c(0, s->m92);
        m84->f_0386a8();
    }
    D_2408f0->seq = D_2407d0.Find((const char *)m4[0]);
    D_2408f0->course = CourseOf((const char *)m4[0]);
    RaceInfo *ri = D_2408f0;
    ri->m16 = m4[2];
    ri->m20 = s->m16;
    ri->m24 = s->m44;
    ri->m28 = s->m48;
    ri->m32 = 10800000;
    ri->m36 = s->m12;
    ri->m52 = -f_038af4();
    ri = D_2408f0;
    ri->m48 = ri->m52 - s->m52 * 50 - 3000;
    ri->m60 = s->m24->m12 + s->m24->m16;
    ri->m64 = SeqIs(5);
    D_2408f0->m68 = (SeqIs(4) || SeqIs(5)) ? Qualify() : 0;
    ri = D_2408f0;
    ri->m72 = 0;
    ri->m84 = 0;
    ri->m88 = s->m100;
    ri->m92 = s->m104;
    ri->m196 = s->m24->f_03b518(0);
    InfoCar *c = s->m24->f_03b518(0);
    c->m124 = 2;
    car = c;
    ri = D_2408f0;
    ri->car = Name(c->m92);
    c->m10116 = m80;
    ri->m112 = ri->m60 - 1;
    ri->m124 = ri->m28;
    ri->m104 = c->m124;
    ri->m128 = -1;
    ri->m108 = 0;
    ri->m116 = 0;
    ri->m120 = 0;
    ri->m132 = 0;
    ri->m136 = 0;
    memcpy(D_24063c, D_240740.Get("RedRev", (const char *)D_2408f0->car.a, 0), D_1a211c[2]);
    ri->m156 = *(short *)D_24063c;
    ri = D_2408f0;
    memcpy(D_24063c, D_240740.Get("MaxRev", (const char *)ri->car.a, 0), D_1a211c[2]);
    ri->m160 = *(short *)D_24063c;
    f_038a80(0);
    RaceLaps *l = D_2408f0->m200;
    l->m2376 = 0;
    l->m2384 = 0;
    memcpy(D_24063c, D_2407a8.Get("SectionNum", (const char *)D_2408f0->course.a, 0), D_1a211c[1]);
    l->m2404 = D_24063c[0];
    for (int j = 0; j < D_2408f0->m200->m2404; j++) {
        RaceLaps *l2 = D_2408f0->m200;
        memcpy(D_24063c, D_2407a8.f_0368e8("SectionRzp_0", (const char *)D_2408f0->course.a, j, 0), D_1a211c[2]);
        l2->m2392[j] = *(short *)D_24063c;
        for (int k = 0; k < 99; k++)
            D_2408f0->m200->m0[k][j] = -1;
    }
    if (D_2408f0->m20 == 0) {
        if (s->m56[0][0] == 0x7fffffff) {
            RaceLaps *l3 = D_2408f0->m200;
            int t = 0;
            if (l3->m2404 == 2) {
                for (int i = 0; i < 3; i++) {
                    t += 899295;
                    l3->m18008[i][0] = t;
                    t += 900000;
                    l3->m18008[i][1] = t;
                    l3->m18008[i][2] = -1;
                }
            } else if (l3->m2404 == 3) {
                for (int i = 0; i < 3; i++) {
                    t += 719295;
                    l3->m18008[i][0] = t;
                    t += 540000;
                    l3->m18008[i][1] = t;
                    t += 540000;
                    l3->m18008[i][2] = t;
                }
            }
        } else {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < D_2408f0->m200->m2404; j++)
                    D_2408f0->m200->m18008[i][j] = s->m56[i][j];
        }
    }
    CCarJobCtrlPSP *ctrl = s->m24;
    ri = D_2408f0;
    ri->m56 = 0;
    ri->m216 = ctrl->m12 + ctrl->m16;
    ri->m204 = ctrl->m32;
    ri->m208 = ctrl->m28;
    D_27eccc = 0;
    director.Init(ctrl, ri->course, 0, D_23f7f0.m8);
    ri = D_2408f0;
    ri->m212 = director.Standing();
    ri->m220 = director.f_0ee6b8();
    for (int i = 0; i < s->m24->m16; i++)
        D_2408f0->m200->m17956[i] = s->m24->f_03b530(i);
}

/* @implements 0x03ed4c us CInfoRaceNormalCircuit8f_038a54
   WHAT IT DOES: the per frame step. Does nothing while the game is paused; otherwise runs the
   current state's handler, counts the frame and raises the flags whose frame has come: the
   end (returned), and the two timed events at +40 and +48. */
int CInfoRaceNormalCircuit::f_038a54()
{
    GameFlags *g = D_1d88a0;
    if (g->m11 || g->m12)
        return 0;
    if (m72 == 1)
        m72 = 2;
    int r = (this->*D_1d1c44[state])();
    int f = ++m4[3];
    if (f == m96)
        r = 1;
    if (f == m44)
        m40 = 1;
    if (m4[3] == m60)
        m48 = 1;
    return r;
}

/* @implements 0x03ee54 us CInfoRaceNormalCircuit8f_038a64
   WHAT IT DOES: the end of the race: outside the replay writes the ranking into the race
   result, frees the ranking checker and the object at +80, and, outside the replay, notes the
   frame the race ended on and fills the race result: the final phase, the player's place,
   each lap's time from the player's sector times measured from the start line time (sectors
   2 or 3 a lap; -1 for a lap not timed), each lap's time converted for display and, when the
   race was not completed, the player's sector times from the start (-1 elsewhere). */
void CInfoRaceNormalCircuit::f_038a64()
{
    if (m24 == 0)
        director.f_0ee584();
    director.f_0ee624();
    if (m80)
        f_037d50(m80);
    if (m24)
        return;
    if (m28 < 0)
        m28 = m4[3];
    RaceInfo *ri = D_2408f0;
    RaceResult *r = &D_240800;
    D_240800.m0 = ri->m56;
    r->me = ri->m112;
    r->best[2] = r->best[1] = r->best[0] = -1;
    RaceLaps *l = ri->m200;
    if (l->m2404 == 2) {
        if (l->m0[0][0] >= 0 && l->m0[0][1] >= 0) {
            r->best[0] = l->m0[0][1] - l->m0[ri->m36][0];
            if (l->m0[1][0] >= 0 && l->m0[1][1] >= 0) {
                r->best[1] = l->m0[1][1] - l->m0[0][1];
                if (l->m0[2][0] >= 0 && l->m0[2][1] >= 0)
                    r->best[2] = l->m0[2][1] - l->m0[1][1];
            }
        }
    } else if (l->m2404 == 3) {
        if (l->m0[0][0] >= 0 && l->m0[0][1] >= 0 && l->m0[0][2] >= 0) {
            r->best[0] = l->m0[0][2] - l->m0[ri->m36][0];
            if (l->m0[1][0] >= 0 && l->m0[1][1] >= 0 && l->m0[1][2] >= 0) {
                r->best[1] = l->m0[1][2] - l->m0[0][2];
                if (l->m0[2][0] >= 0 && l->m0[2][1] >= 0 && l->m0[2][2] >= 0)
                    r->best[2] = l->m0[2][2] - l->m0[1][2];
            }
        }
    }
    for (int i = 0; i < D_2407fc->m36; i++) {
        if (D_240800.best[i] > 0)
            D_240800.lap[i] = f_0eede0(D_240800.best[i], 1, D_23f7f0.m8);
        else
            D_240800.lap[i] = 0;
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            D_240800.rec[i].v[j] = -1;
    if (D_2408f0->m132 < D_2408f0->m24) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < D_2408f0->m200->m2404; j++)
                D_240800.rec[i].v[j] = D_2408f0->m200->m0[i][j]
                    - D_2408f0->m200->m0[D_2408f0->m36][0];
    }
}

/* @implements 0x03f1ac us CInfoRaceNormalCircuit8f_038a78
   WHAT IT DOES: passes the object at +80 on to its handler. */
void CInfoRaceNormalCircuit::f_038a78()
{
    f_037f48(m80);
}

/* @implements 0x03f1c8 us f_03f1c8
   WHAT IT DOES: the countdown state: records the car, advances the race clock and, once the
   countdown is over, starts the race (state 1, race phase 5) and schedules the first timed
   event two seconds on. */
int CInfoRaceNormalCircuit::f_03f1c8()
{
    f_038a80(0);
    RaceInfo *ri = D_2408f0;
    ri->m48 += 50;
    if (ri->m48 >= 0) {
        state = 1;
        ri->m56 = 5;
        D_27eccc = 5;
        car->m124 = 0;
        if (m24 == 0)
            m44 = m4[3] + 120;
        m76 = 1;
    }
    D_2408f0->m104 = car->m124;
    return 0;
}

/* @implements 0x03f25c us f_03f25c
   WHAT IT DOES: the race state: steps the race; when the laps are done goes to the finish
   (state 5, phase 3) for two seconds; advances the race clock. */
int CInfoRaceNormalCircuit::f_03f25c()
{
    if (m24 == 0)
        m36 = 1;
    f_03fb40();
    RaceInfo *ri = D_2408f0;
    if (ri->m32 <= 0) {
        ri->m56 = 3;
        D_27eccc = 3;
        car->m124 = 3;
        state = 5;
        m100 = 120;
        m36 = 0;
    }
    int c = car->m124;
    ri->m104 = c;
    ri->m48 += 50;
    return 0;
}

/* @implements 0x03f2f0 us f_03f2f0
   WHAT IT DOES: the final lap state: as the race state through the other step, unless the
   car's finish is of kind 2; then goes to state 4. */
int CInfoRaceNormalCircuit::f_03f2f0()
{
    if (m24 == 0)
        m36 = 1;
    f_03f61c();
    RaceInfo *ri = D_2408f0;
    if (ri->m32 <= 0 && m104 != 2) {
        ri->m56 = 3;
        D_27eccc = 3;
        car->m124 = 3;
        state = 4;
        m100 = 120;
        m36 = 0;
    }
    D_2408f0->m104 = car->m124;
    D_2408f0->m48 += 50;
    return 0;
}

/* @draft 0x03f394 us f_03f394
   WHAT IT DOES: the result state: steps the camera director and records its shot, records the
   car, advances the race clock and, outside the replay, schedules the end once the music
   allows (or after eight seconds).
   Remaining difference: retail loads D_2408f0 for the director's shot after setting up the
   call's argument, so the record pointer reuses the director's saved register (three saved
   registers); here the load comes first and a fourth saved register is used. */
int CInfoRaceNormalCircuit::f_03f394()
{
    director.f_0ee788();
    D_2408f0->m220 = director.f_0ee6b8();
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    D_2408f0->m48 += 50;
    m104 = 0;
    if (m24 == 0 && m96 < 0) {
        if (f_094254(D_242c90) == 1) {
            m60 = m4[3] + 60;
            m96 = m4[3] + 120;
        } else if (m28 + 480 < m4[3]) {
            m60 = m4[3] + 60;
            m96 = m4[3] + 120;
        }
    }
    return 0;
}

/* @implements 0x03f480 us f_03f480
   WHAT IT DOES: the finish state after the final lap step: when its two seconds are up (and
   the finish is not of kind 2) goes to the result (state 6, phase 4) and schedules the end. */
int CInfoRaceNormalCircuit::f_03f480()
{
    f_03f61c();
    if (--m100 == 0 && m104 != 2) {
        D_2408f0->m56 = 4;
        state = 6;
        m72 = 1;
        if (m24 == 0) {
            m96 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    int c = car->m124;
    D_2408f0->m104 = c;
    D_2408f0->m48 += 50;
    return 0;
}

/* @implements 0x03f51c us f_03f51c
   WHAT IT DOES: the same finish state after the race step. */
int CInfoRaceNormalCircuit::f_03f51c()
{
    f_03fb40();
    if (--m100 == 0 && m104 != 2) {
        D_2408f0->m56 = 4;
        state = 6;
        m72 = 1;
        if (m24 == 0) {
            m96 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    int c = car->m124;
    D_2408f0->m104 = c;
    D_2408f0->m48 += 50;
    return 0;
}

/* @draft 0x03f5b8 us f_03f5b8
   WHAT IT DOES: the replay state: records the camera director's shot and the car.
   Remaining difference: the saved registers of D_2408f0's high part and of the loaded record
   pointer are swapped (retail s1/s2), and retail loads the pointer in the call's slot. */
int CInfoRaceNormalCircuit::f_03f5b8()
{
    D_2408f0->m220 = director.f_0ee6b8();
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    return 0;
}

/* @draft 0x03f61c us f_03f61c
   WHAT IT DOES: the race step of the final laps: records the car, steps the ranking, then asks
   the car's position tracker how far it is from the line. A car that reaches a new lap is
   noted (kind 1, or 2 when it is the race's last). Kind 1 closes the lap: its time, the
   player's sector table, and the lap clock restarts. Kind 2 finishes the race: the lap, race
   and finishing times, the finish phase (state 3), the end schedule outside the replay, the
   last sector time and the ranking's finish. Otherwise kind 0 times the player's sector ends.
   Then the best lap, the ranking sort, the player's place and the director's shot, every
   other car's sector and lap times, and the race clock (held at 900000 while the ranking
   runs and the race is not over).
   Remaining difference: two words, the same as the time attack's 0x0f013c. Retail keeps the
   sector end step's tracker result in a3, a register of its own; here it shares t0 with the
   first tracker result. */
void CInfoRaceNormalCircuit::f_03f61c()
{
    f_038a80(0);
    director.f_0ee76c();
    float at = 0;
    int clk = D_2408f0->m116;
    int ph = clk / 3;
    ph = clk - ph * 3;
    int r = f_0a8d5c(car->m2128, &at, 50, 3, ph);
    if (r < -2) {
        m104 = 0;
    } else {
        InfoCar *c = car;
        RaceInfo *ri = D_2408f0;
        int laps = c->m2212;
        if (ri->m108 < laps) {
            ri->m108 = laps;
            if (laps == ri->m36)
                m104 = 2;
            else
                m104 = 1;
        } else {
            m104 = 0;
        }
    }
    RaceInfo *ri = D_2408f0;
    RaceLaps *l = ri->m200;
    int sec = l->m2376;
    int lap = l->m2384;
    float end = l->m2392[sec];
    switch (m104) {
    case 0: {
        float at2 = end;
        int clk2 = ri->m132;
        int ph2 = clk2 / 3;
        ph2 = clk2 - ph2 * 3;
        r = f_0a8d5c(car->m2128, &at2, 50, 3, ph2);
        if (r >= -2 && car->m2212 == lap) {
            RaceInfo *q = D_2408f0;
            RaceLaps *l2 = q->m200;
            if (sec != l2->m2404 - 1) {
                l2->m0[lap][sec] = q->m48 + r;
                l2->m2376++;
            }
        }
        D_2408f0->m116 += 50;
        D_2408f0->m132 += 50;
        break;
    }
    case 1:
        ri->m120 = ri->m116 + r;
        ri->m116 = 50 - r;
        l->m0[lap][sec] = ri->m48 + r;
        l->m2384++;
        l->m2376 = 0;
        ri->m132 += 50;
        break;
    case 2:
        ri->m116 = ri->m120 = ri->m116 + r;
        ri->m132 += r;
        ri->m136 = ri->m48 + r;
        car->m124 = 1;
        ri->m56 = 2;
        D_27eccc = 2;
        state = 3;
        if (m24 == 0) {
            if (m28 < 0)
                m28 = m4[3] + 120;
            if (m96 < 0) {
                if (f_094254(D_242c90) == 1) {
                    m96 = m4[3] + 120;
                    m60 = m4[3] + 60;
                } else if (m28 + 480 < m4[3]) {
                    m96 = m4[3] + 120;
                    m60 = m4[3] + 60;
                }
            }
        }
        {
            RaceInfo *q = D_2408f0;
            q->m200->m0[lap][sec] = q->m136;
            q->m200->m2384++;
            q->m200->m2376 = 0;
            director.f_0ee704(q->m136, q->m132);
        }
        m36 = 0;
        break;
    }
    if (m104) {
        RaceInfo *q = D_2408f0;
        if (q->m120 < q->m124) {
            q->m124 = q->m120;
            q->m128 = q->m108 - 1;
        }
    }
    director.f_0ee1d8(0);
    RaceInfo *q = D_2408f0;
    q->m112 = director.f_0ee66c();
    RaceInfo *q2 = D_2408f0;
    q2->m220 = director.f_0ee6b8();
    for (int i = 0; i < 13; i++) {
        InfoCar *c = D_2408f0->m200->m17956[i];
        if (!c)
            break;
        int lp = D_2408f0->m200->m17904[i];
        if (lp == D_2408f0->m36)
            continue;
        int clk3 = D_2408f0->m48;
        sec = D_2408f0->m200->m17852[i];
        float at3 = D_2408f0->m200->m2392[sec];
        int ph3 = clk3 / 3;
        ph3 = clk3 - ph3 * 3;
        int r3 = f_0a8d5c(c->m2128, &at3, 50, 3, ph3);
        if (r3 < -2)
            continue;
        RaceLaps *l3 = D_2408f0->m200;
        if (l3->m17956[i]->m2212 < lp)
            continue;
        l3->m2408[i][lp][sec] = D_2408f0->m48 + r3;
        if (++l3->m17852[i] == l3->m2404) {
            l3->m17852[i] = 0;
            l3->m17904[i]++;
        }
    }
    if (director.Running() && m104 != 2 && D_2408f0->m32 > 900050)
        D_2408f0->m32 = 900000;
    else
        D_2408f0->m32 -= 50;
}

/* @implements 0x03fb40 us f_03fb40
   WHAT IT DOES: the race step before the final laps: records the car, steps the ranking and,
   once the car has crossed the line onto its first lap, notes the start line time, starts the
   lap clock and the race time and goes to the race state (state 2, phase 1). Then the ranking
   sort, the player's place and the director's shot, every other car's sector and lap times,
   and the race clock (held at 900000 while the ranking runs and the race is not over). */
void CInfoRaceNormalCircuit::f_03fb40()
{
    f_038a80(0);
    director.f_0ee76c();
    float at = 0;
    int clk = D_2408f0->m116;
    int ph = clk / 3;
    ph = clk - ph * 3;
    int r = f_0a8d5c(car->m2128, &at, 50, 3, ph);
    if (r < -2) {
        m104 = 0;
    } else {
        InfoCar *c = car;
        if (c->m2212 < 0) {
            m104 = 0;
        } else {
            m104 = 1;
            D_2408f0->m108 = c->m2212;
        }
    }
    if (m104) {
        RaceInfo *ri = D_2408f0;
        ri->m132 = ri->m116 = 50 - r;
        ri->m200->m0[ri->m36][0] = ri->m48 + r;
        state = 2;
        ri->m56 = 1;
        D_27eccc = 1;
    }
    director.f_0ee1d8(0);
    RaceInfo *ri = D_2408f0;
    ri->m112 = director.f_0ee66c();
    RaceInfo *q2 = D_2408f0;
    q2->m220 = director.f_0ee6b8();
    for (int i = 0; i < 13; i++) {
        InfoCar *c = D_2408f0->m200->m17956[i];
        if (!c)
            break;
        int lp = D_2408f0->m200->m17904[i];
        if (lp == D_2408f0->m36)
            continue;
        int clk3 = D_2408f0->m48;
        int s3 = D_2408f0->m200->m17852[i];
        float at3 = D_2408f0->m200->m2392[s3];
        int ph3 = clk3 / 3;
        ph3 = clk3 - ph3 * 3;
        int r3 = f_0a8d5c(c->m2128, &at3, 50, 3, ph3);
        if (r3 < -2)
            continue;
        RaceLaps *l3 = D_2408f0->m200;
        if (l3->m17956[i]->m2212 < lp)
            continue;
        l3->m2408[i][lp][s3] = D_2408f0->m48 + r3;
        if (++l3->m17852[i] == l3->m2404) {
            l3->m17852[i] = 0;
            l3->m17904[i]++;
        }
    }
    if (director.Running() && m104 != 2 && D_2408f0->m32 > 900050)
        D_2408f0->m32 = 900000;
    else
        D_2408f0->m32 -= 50;
}

/* Two words of which only the first is set when made. */
struct CarPair {
    int a;
    int b;
    CarPair() : a(0) {}
};
struct CarPair2 {
    int a;
    int b;
    CarPair2() : a(0) {}
};

/* The race's per car record (at D_240900). */
struct RaceCars {
    CarPair m0;
    int m8;
    int m12;
    int m16;
    CarPair2 m20[13];
    int m124[13];
    int m176[13];
    int m228[13];
    int m280[13];
    int m332;
    void f_03fe1c();
};

/* @draft 0x03fe1c us f_03fe1c
   WHAT IT DOES: clears the per car record: the counters, every car's pair and the three
   per car slots (to -1).
   Remaining difference: retail stores +4 (the temporary's second word) before the zero at +8;
   here +8 comes first. No order of these statements (single or chained) gives retail's. */
void RaceCars::f_03fe1c()
{
    m12 = 0;
    m16 = 0;
    m332 = 0;
    m8 = 0;
    m0 = CarPair();
    for (int i = 0; i < 13; i++) {
        m20[i] = CarPair2();
        m124[i] = -1;
        m176[i] = -1;
        m228[i] = -1;
    }
}
