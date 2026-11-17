/* The wireless race information object file (retail 0x0f088c to 0x0f27b4,
   "RacePSP::CInfoRaceNet"). The information side of a wireless (ad hoc) race: as the normal
   circuit information, a state machine (countdown, race, final lap, finish, result and replay
   states) stepped once a frame keeps the shared race information record up to date and
   decides when the race, the replay and the camera changes happen; here it also follows the
   network session (D_241810): every member's car, the members' finishing times and the
   session's end of race. It owns a ranking checker (src/race/CheckRanking.cpp). */

extern "C" {
void f_0ee584(void *);
void f_0ee624(void *);
void f_037d50(void *);
void f_082f38(void *);
void f_126f40(void *base, int n, int size, int (*cmp)(const void *, const void *));
int f_0f088c(const void *a, const void *b);
float f_0eede0(int count, int n, float x);
void f_0ede54(void *);
void f_0edec0(void *);
int f_0ee6b8(void *);
void f_0ee788(void *);
void f_037f48(void *);
int f_094254(void *);
void f_0ee76c(void *);
void f_0ee1d8(void *, int);
int f_0ee66c(void *);
void f_0ee704(void *, int, int);
int f_0a8d5c(void *pos, float *at, int a, int b, int c);
}
extern char D_242c90[];
extern int D_27eccc;
/* The race settings (made elsewhere); +8 is the time a lap is worth in the session's
   converted times. */
struct RaceSetup {
    int m0[2];
    int m8;
};
extern RaceSetup D_23f7f0;

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

/* The race's lap timing block: the player's sector times per lap (cumulative within the
   lap), the best times, and every car's sector times (see src/sequence/InfoTimeAttack.cpp). */
struct InfoCar;
struct RaceLaps {
    int m0[99][3];      /* the player's time at each sector end, per lap */
    int m1188[99][3];   /* the best times (see src/race/CheckRanking.cpp) */
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
/* The game packet processor (src/system/GamePacketProc.cpp); its first word is the shared
   race clock. */
struct PacketProc {
    int clock;
};
extern PacketProc D_241760;

/* The race packet sender (src/race/NetRacePacket.cpp). */
struct CNetRacePacket {
    void f_083edc(int t);
    int f_083f1c(int *a, int *b, int *c);
};
extern CNetRacePacket D_241804;
extern int D_27ece4; /* frames spent waiting for the host's start */
extern int D_27ece8; /* frames the host has waited for the start time */

/* @implements 0x0f088c us f_0f088c
   WHAT IT DOES: The sort comparator of two ints (ascending): *a - *b. (Its user, 0x0f178c, is
   not transcribed yet, so it is kept external here to be emitted.) */
extern "C" int f_0f088c(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

/* The race information record shared by the sequences. */
struct RaceInfo {
    Slot seq;   /* the race sequence (its row in the sequence table) */
    Slot course; /* the course (its row in the course table) */
    int m16;    /* the sequence number */
    int m20;    /* a replay */
    int m24;
    int m28;
    int m32;    /* race clock to go */
    int m36;    /* laps of the race */
    int m40;
    int m44;
    int m48;    /* race clock */
    int m52;
    int m56;    /* race phase */
    int m60;    /* cars racing */
    int m64;
    int m68;
    int m72;
    int m76;
    int m80;
    int m84;
    int m88;
    int m92;
    Slot car;   /* the player's car (its row in the car table) */
    int m104;
    int m108;   /* the player's laps */
    int m112;   /* the player's place */
    int m116;   /* lap clock */
    int m120;   /* last lap time */
    int m124;   /* best lap time */
    int m128;   /* best lap */
    int m132;   /* race time */
    int m136;   /* finishing time */
    int m140;
    float m144;
    int m148;
    int m152;
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

/* A member of the network session (40 bytes). */
struct NetMember {
    char m0[9];
    char m9;
    signed char m10;  /* the member's race state (7 ready to start) */
    char m11[7];
    signed char m18;  /* the member is in the session */
    char m19[9];
    int m28;    /* finishing time (-2 none yet, -1 retired) */
    int m32;
    float m36;
};

/* The network session (src/system/NetSession.cpp). */
struct NetState {
    char m0[9];
    signed char m9;   /* the session's race state */
    char m10[8];
    unsigned char m18; /* the session's race settings */
    char m19[5];
    int m24;          /* the start time on the race clock */
    char m28[56];
};
struct CNetSession {
    char m0[4];
    int m4;
    char m8[76];
    NetState state;
    NetMember member[8];
    NetMember *Me() { return &member[0]; }
    NetState *State() { return &state; }
    int f_086afc();
    int f_086b40();
    int f_086b84();
    int f_086c50();
    int f_086324();
    bool f_08651c();
    void *f_085a1c(int n);
    void *f_085a9c(const char *mac, unsigned char self);
};
extern CNetSession D_241810;

/* The ad hoc connection (src/system/AdhocControl.cpp). */
struct CAdhocControl {
    int f_088338();
};
extern CAdhocControl D_241e98;
extern "C" unsigned int sceKernelGetSystemTimeLow(void);
extern unsigned int D_27ece0; /* the system time at the last frame */

/* The game's settings that pause the race. */
struct GameFlags {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern GameFlags *D_1d88a0;

/* The player's car as the information reads it. */
struct InfoCar {
    char m0[76];
    int m76;         /* taking part in the ranking */
    char m80[12];
    Name m92;        /* the car (its row in the car table) */
    char m100[4];
    char m104[20];   /* the console's address in the session */
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
    int m8;
    int m12;          /* laps of the race */
    int m16;          /* a replay */
    int m20;          /* the frame the replay ends on */
    CCarJobCtrlPSP *m24; /* the cars */
    CPlayerInputProxy *m28; /* the player's inputs */
    CPlayerInputProxy *m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int m52;          /* seconds of countdown */
    int m56[9];
    int m92;          /* the course is mirrored */
};

/* The ranking checker (src/race/CheckRanking.cpp), made and destroyed with the
   information. */
extern "C" void f_0edf18(void *, CCarJobCtrlPSP *ctrl, Slot laps, int single, float f);
struct CDirector {
    CDirector() { f_0ede54(this); }
    ~CDirector() { f_0edec0(this); }
    int f_0ee6b8() { return ::f_0ee6b8(this); }
    void f_0ee788() { ::f_0ee788(this); }
    void f_0ee584() { ::f_0ee584(this); }
    void f_0ee624() { ::f_0ee624(this); }
    void f_0ee76c() { ::f_0ee76c(this); }
    void f_0ee1d8(int from) { ::f_0ee1d8(this, from); }
    int f_0ee66c() { return ::f_0ee66c(this); }
    void f_0ee704(int t, int t2) { ::f_0ee704(this, t, t2); }
    void Init(CCarJobCtrlPSP *ctrl, Slot laps, int single, float f) { f_0edf18(this, ctrl, laps, single, f); }
    int Holding() { return m20; }
    void *Standing() { return m24; }
    char m0[20];
    int m20;   /* the race clock is held at five minutes */
    void *m24; /* the standing table */
    char m28[8];
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
    void f_038a80(int);
    int m4[4];
    unsigned int m20;
};

class CInfoRaceNet;
typedef int (CInfoRaceNet::*InfoHandler)();

class CInfoRaceNet : public CInfoBase {
public:
    CInfoRaceNet();
    virtual ~CInfoRaceNet();
    void f_0f0a54(InfoSetup *s);
    virtual int f_038a54();
    virtual void f_038a64();
    void f_0f0aa8(InfoSetup *s);
    int f_0f178c();
    int f_0f10bc();
    void f_0f1474();
    virtual void f_038a78();
    int f_0f1aa0();
    int f_0f1b34();
    int f_0f1bd8();
    int f_0f1d44();
    int f_0f1e64();
    int f_0f1f78();
    void f_0f1fdc();
    void f_0f24ec();

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
    int m144;     /* clock samples taken */
    int m148[3];  /* the clock offsets sampled from the host */
    int m160;
    int m164;     /* the start time has not been applied yet */
};
}

using namespace RacePSP;

extern InfoHandler D_1d5ad0[];

/* @implements 0x0f089c us _ZN7RacePSP12CInfoRaceNetC2Ev
   WHAT IT DOES: builds the information on its base and makes its ranking checker. */
CInfoRaceNet::CInfoRaceNet()
{
}

/* @implements 0x0f08f0 us _ZN7RacePSP12CInfoRaceNetC1Ev
   WHAT IT DOES: the complete-object copy of the constructor above. */

/* @implements 0x0f0944 us _ZN7RacePSP12CInfoRaceNetD2Ev
   WHAT IT DOES: destroys the ranking checker, then the base. */
CInfoRaceNet::~CInfoRaceNet()
{
}

/* @implements 0x0f099c us _ZN7RacePSP12CInfoRaceNetD1Ev
   WHAT IT DOES: the complete-object copy of the destructor above. */

/* @implements 0x0f09f4 us _ZN7RacePSP12CInfoRaceNetD0Ev
   WHAT IT DOES: the deleting destructor. */

/* @implements 0x0f0a54 us f_0f0a54
   WHAT IT DOES: sets the information up for the race (0x0f0aa8). */
void CInfoRaceNet::f_0f0a54(InfoSetup *s)
{
    f_0f0aa8(s);
}

/* @implements 0x0f0a70 us CInfoRaceNet8f_038a54
   WHAT IT DOES: the per frame step (0x0f10bc). */
int CInfoRaceNet::f_038a54()
{
    return f_0f10bc();
}

/* @implements 0x0f0a8c us CInfoRaceNet8f_038a64
   WHAT IT DOES: the end of the race (0x0f1474). */
void CInfoRaceNet::f_038a64()
{
    f_0f1474();
}

/* The course of a race sequence: the course table's row named by the sequence's course
   number. */
static inline Name CourseOf(const char *seq)
{
    Name c = D_2407a8.Find((const char *)D_2407d0.Get("CourseNumber", seq, 0));
    return c;
}

/* @draft 0x0f0aa8 us _ZN7RacePSP12CInfoRaceNet8f_0f0aa8E
   WHAT IT DOES: sets the information up for the race from the sequence's race setup. Resets
   the packet processor and every member's finishing times (none yet), looks up the race
   sequence and its number, clears the frame count and the race clock, and takes the replay
   flag and frames (the end and its timed events; none outside the replay), the player's
   inputs (recording, or playing back in the replay) and the second input object. Then fills
   the race information record: the sequence and course rows, the number, the replay flag,
   the laps, the clock (three hours to go, the countdown before zero), the number of cars,
   the session's race settings, the player's car (its finish kind 2 until it crosses the
   line, its row, its engine's red zone and top revs from the car table), the lap and sector
   counters, the course's sectors and where each ends (no times yet), the course sizes, and
   starts the ranking checker on the cars (the player's place, the standing table and its
   shot); finally the ranking's car of each place.
   Cycle 2026-11-16: the sequence, course and car rows held in named locals (seq, course,
   row; the lever from CInfoTimeAttack::f_0eefd8) give retail's 112-byte frame (was 80) --
   kept, 323 -> 311 words, 1520 -> 1516 vs 1556 bytes.
   Remaining difference: the control flow, the calls and the stores follow retail; the
   stack slots of the rows may still differ as on 0x0eefd8 (retail: course found at 32 and
   copied to 16, car row at 48, laps at 32). Retail also addresses the size
   table D_1a211c from a base register at every read (lui/addiu then lw 4 or 8), as if the
   size index were a variable propagated after expansion; here one address is CSE'd for the
   whole function. Register allocation and store order follow from those. */
void CInfoRaceNet::f_0f0aa8(InfoSetup *s)
{
    f_038a6c();
    f_082f38(&D_241760);
    NetMember *m = D_241810.Me();
    for (int i = 0; i < 8; i++) {
        m[i].m28 = -2;
        m[i].m32 = -2;
        m[i].m36 = 1.17549435e-38f;
    }
    const char *name = s->m0;
    if (name)
        m4[0] = (int)D_2407d0.f_036984(name, 0, D_2407d0.rowNames, D_2407d0.nRows);
    else
        m4[0] = 0;
    memcpy(D_24063c, D_2407d0.Get("SequenceNumber", (const char *)m4[0], 0), D_1a211c[1]);
    m4[2] = D_24063c[0];
    m4[3] = 0;
    m20 = s->m8;
    D_241760.clock = 0;
    m144 = 0;
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
    Name seq = D_2407d0.Find((const char *)m4[0]);
    D_2408f0->seq = seq;
    Name course = CourseOf((const char *)m4[0]);
    D_2408f0->course = course;
    RaceInfo *ri = D_2408f0;
    ri->m16 = m4[2];
    ri->m20 = s->m16;
    ri->m24 = s->m44;
    ri->m28 = s->m48;
    ri->m32 = 10800000;
    ri->m36 = s->m12;
    ri->m48 = -s->m52 * 50 - 3000;
    ri->m52 = 0;
    ri->m60 = s->m24->m12 + s->m24->m16;
    ri->m64 = 0;
    ri->m68 = 0;
    ri->m72 = D_241810.State()->m18 & 3;
    ri->m84 = 0;
    ri->m88 = 0;
    ri->m92 = 0;
    ri->m196 = s->m24->f_03b518(0);
    InfoCar *c = s->m24->f_03b518(0);
    c->m124 = 2;
    car = c;
    ri = D_2408f0;
    Name row = Name(c->m92);
    ri->car = row;
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
    CCarJobCtrlPSP *ctrl = s->m24;
    ri = D_2408f0;
    ri->m56 = 0;
    ri->m216 = ctrl->m12 + ctrl->m16;
    ri->m204 = ctrl->m32;
    ri->m208 = ctrl->m28;
    D_27eccc = 0;
    director.Init(ctrl, ri->course, 0, D_23f7f0.m8);
    D_2408f0->m112 = director.f_0ee66c();
    D_2408f0->m212 = director.Standing();
    D_2408f0->m220 = director.f_0ee6b8();
    m160 = 1;
    for (int i = 0; i < s->m24->m16; i++)
        D_2408f0->m200->m17956[i] = s->m24->f_03b530(i);
}

/* @draft 0x0f10bc us _ZN7RacePSP12CInfoRaceNet8f_0f10bcEv
   WHAT IT DOES: the per frame step. Runs the current state's handler and counts the frame.
   While the session is up and every member is still there (each car's console found among
   the members; a car whose console is gone is dropped from the ranking), advances the race
   clock by the frames the system clock has gone on since the last frame (rounded; one frame
   right after the start). Once the end is scheduled, marks the player's member finished
   when every member has a finishing time, and the host marks the session finished when
   every member is. Returns 1 for the end once its frame has come and the session is
   finished, 2 (3 when the connection is lost) when the session is down, and raises the two
   timed events at +40 and +48.
   Cycle 2026-11-16: both member scans written 'if (!m[i].m18) continue;' followed by the
   test (handbook: a block after 'if (cond) continue;' goes out of line), so the rest of the
   test sits out of line and the flag test falls through to the latch as in retail: 115 ->
   12 words, size now 952 as retail.
   Remaining difference: register choice only: retail loads m96 into a2 (here a0) at the
   three reloads after the clock, and the State()->m9 == 8 test uses v0/a0/v1 where here it
   is a1/v1/v0. Not yet diagnosed (next: the lreg/greg allocation of the m96 pseudo). */
int CInfoRaceNet::f_0f10bc()
{
    if (m72 == 1)
        m72 = 2;
    int r = (this->*D_1d5ad0[state])();
    m4[3]++;
    if (D_241e98.f_088338() != 5 || !D_241810.f_086324())
        return D_241e98.f_088338() == 10 ? 3 : 2;
    if (!D_241810.f_08651c())
        return 2;
    if (!D_241810.f_085a1c(0))
        return 2;
    if (!D_241810.f_085a9c(car->m104, 1))
        return 2;
    for (int i = 0; i < 13; i++) {
        InfoCar *c = D_2408f0->m200->m17956[i];
        if (!c)
            break;
        void *e = D_241810.f_085a9c(c->m104, 1);
        if (!e && c->m76) {
            D_2408f0->m60--;
            director.f_0ee1d8(0);
            c->m76 = 0;
        }
    }
    unsigned int t = sceKernelGetSystemTimeLow();
    t -= 0x10000000;
    if (m160) {
        D_241760.clock += 50;
        m160 = 0;
    } else {
        unsigned int d = t - D_27ece0;
        unsigned int n = d / 16666;
        if (d % 16666 >= 8334)
            n++;
        D_241760.clock += n * 50;
    }
    D_27ece0 = t;
    if (m96 != -1 && D_241810.State()->m9 != 8) {
        NetMember *m = D_241810.Me();
        int ok = 1;
        for (int i = 0; i < 8; i++) {
            if (!m[i].m18)
                continue;
            if (m[i].m28 == -2 && m[i].m32 == -2) {
                ok = 0;
                break;
            }
        }
        if (ok)
            m->m10 = 8;
        D_241810.f_086afc();
        if (D_241810.m4 == 0) {
            int all = 1;
            for (int i = 0; i < 8; i++) {
                if (!m[i].m18)
                    continue;
                if (m[i].m10 != 8) {
                    all = 0;
                    break;
                }
            }
            if (all) {
                D_241810.State()->m9 = 8;
                D_241810.f_086c50();
            }
        }
    }
    int f = m4[3];
    if (f >= m96 && D_241810.State()->m9 == 8) {
        for (int i = 0; i < 8; i++)
            ;
        r = 1;
    }
    if (f == m44)
        m40 = 1;
    if (f == m60)
        m48 = 1;
    return r;
}

/* @implements 0x0f1474 us _ZN7RacePSP12CInfoRaceNet8f_0f1474Ev
   WHAT IT DOES: the end of the race: outside the replay writes the ranking into the race
   result, frees the ranking checker and the object at +80, and, outside the replay, notes
   the frame the race ended on and fills the race result: the final phase, the player's
   place, each lap's time from the player's sector times (sectors 2 or 3 a lap; -1 for a lap
   not timed), each lap's time converted for display and no sector times. Then ends the
   session's race: clears the player's member's flag, marks it ended (3), tells the session
   and, when it is not hosting, marks its own state ended too and tells the members. */
void CInfoRaceNet::f_0f1474()
{
    if (m24 == 0)
        director.f_0ee584();
    director.f_0ee624();
    if (m80)
        f_037d50(m80);
    if (m24 == 0) {
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
    }
    f_082f38(&D_241760);
    CNetSession *net = &D_241810;
    NetMember *me = net->Me();
    NetState *st = net->State();
    me->m10 = 3;
    me->m9 = 0;
    net->f_086afc();
    if (net->m4 == 0) {
        st->m9 = 3;
        net->f_086c50();
    }
}

/* @implements 0x0f1770 us CInfoRaceNet8f_038a78
   WHAT IT DOES: passes the object at +80 on to its handler. */
void CInfoRaceNet::f_038a78()
{
    f_037f48(m80);
}

/* @draft 0x0f178c us _ZN7RacePSP12CInfoRaceNet8f_0f178cEv
   WHAT IT DOES: the countdown state: records the car and agrees the start time with the
   other consoles. The host, once every member in the session is ready, sets the start six
   seconds on, marks itself and the session ready and sends the table. A client already
   ready tells the host; otherwise it asks the host for its clock now and then and, from
   three replies, moves the race clock by the median offset and marks itself ready. Once the
   session is ready: until the start time the host repeats its table every eighth frame;
   then the race clock is moved by the time past the start (once), advances, and when the
   countdown is over the race starts (state 1, race phase 5) as in the normal circuit
   information.
   Remaining difference: the frame (retail 64 bytes, two fewer saved registers) and the
   member scan's addressing (retail steps a member pointer from member 1 with member 0's
   address precomputed); the clock sampling loop is close.
   Cycle 2026-11-16: retail rebuilds &D_241810 (lui/addiu) where needed; here it stays in s2
   and &member-scan bases in s6/s7. Tried dropping the 'net' local (D_241810. directly): 123
   -> 196 words, 800 bytes, still 80-byte frame with s0-s7 -- reverted; the extra saved
   registers come from elsewhere (the member scan's precomputed bases, s7 = D_241810+168). */
int CInfoRaceNet::f_0f178c()
{
    f_038a80(0);
    CNetSession *net = &D_241810;
    NetState *st = net->State();
    if (st->m9 == 7) {
        int clk = D_241760.clock;
        if (clk < st->m24) {
            if (net->m4 == 0) {
                if ((++D_27ece8 & 7) == 0)
                    net->f_086b84();
            }
        } else {
            if (m164) {
                D_2408f0->m48 += clk - st->m24;
                m164 = 0;
            }
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
        }
    } else {
        m164 = 1;
        if (net->m4 == 0) {
            int ok = 1;
            for (int i = 1; i < 8; i++) {
                if (net->member[i].m18 && net->member[i].m10 != 7) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                st->m24 = D_241760.clock + 6000;
                net->Me()->m10 = 7;
                st->m9 = 7;
                net->f_086c50();
            }
        } else if (net->Me()->m10 == 7) {
            net->f_086b40();
        } else {
            if ((D_27ece4 & 15) == 0 && st->m9 == 5)
                D_241804.f_083edc(D_241760.clock);
            D_27ece4++;
            float k = 0.5f;
            for (;;) {
                int t[3];
                if (D_241804.f_083f1c(&t[0], &t[1], &t[2]) == -1)
                    break;
                if (!t[1])
                    break;
                m148[m144++] = (int)(t[1] + (t[2] - t[0]) * k) - D_241760.clock;
                if (m144 >= 3) {
                    f_126f40(m148, 3, 4, f_0f088c);
                    D_241760.clock += m148[m144 / 2];
                    net->Me()->m10 = 7;
                    net->f_086b40();
                    break;
                }
            }
        }
    }
    D_2408f0->m104 = car->m124;
    return 0;
}

/* @implements 0x0f1aa0 us f_0f1aa0
   WHAT IT DOES: the race state: steps the race; when the laps are done goes to the finish
   (state 5, phase 3) for two seconds; advances the race clock. */
int CInfoRaceNet::f_0f1aa0()
{
    if (m24 == 0)
        m36 = 1;
    f_0f24ec();
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

/* @implements 0x0f1b34 us f_0f1b34
   WHAT IT DOES: the final lap state: as the race state through the other step, unless the
   car's finish is of kind 2; then goes to state 4. */
int CInfoRaceNet::f_0f1b34()
{
    if (m24 == 0)
        m36 = 1;
    f_0f1fdc();
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

/* @draft 0x0f1bd8 us f_0f1bd8
   WHAT IT DOES: the result state: when the player's member has no finishing time yet, gives
   it the race and finishing times and the time converted with the session's lap length,
   and tells the session; then steps the session and the ranking checker, records the
   checker's shot and the car, advances the race clock and, outside the replay, schedules
   the end once the music allows (or after eight seconds).
   Remaining difference: allocation around the checker's shot, as in the normal circuit
   information's result state: retail computes the checker's address late into s0 and loads
   D_2408f0 into the same register in the call's slot; here the address gets its own saved
   register. The control flow and the stores match.
   Cycle 2026-11-16 (diff + sched order): the root is the order of two insns before the
   f_0ee6b8 call. Retail: a0 = &director, then the D_2408f0 load (dbr puts it in the jal
   slot), so &director dies before the pointer is born and both share s0. Here the pointer
   load comes first (expand_assignment expands the LHS before the inlined wrapper's body,
   whose parameter copy carries the a0 move), so they overlap. Same order on 0x0f1f78 and on
   the normal circuit's 0x03f5b8. A non-inline direct call is not the answer (a CALL_EXPR
   rhs is expanded before the LHS, putting the load after the call). No change tried. */
int CInfoRaceNet::f_0f1bd8()
{
    NetMember *me = D_241810.Me();
    if (me->m28 == -2 && me->m32 == -2) {
        RaceInfo *ri = D_2407fc;
        me->m28 = ri->m132;
        me->m32 = ri->m136;
        me->m36 = D_23f7f0.m8 * ri->m108 + ri->m144;
        D_241810.f_086afc();
    }
    D_241810.f_086afc();
    director.f_0ee788();
    D_2408f0->m220 = director.f_0ee6b8();
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    D_2408f0->m48 += 50;
    m104 = 0;
    if (m24 == 0 && m96 < 0) {
        if (f_094254(D_242c90) == 1) {
            m96 = m4[3] + 120;
            m60 = m4[3] + 60;
        } else if (m28 + 480 < m4[3]) {
            m96 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    return 0;
}

/* @implements 0x0f1d44 us f_0f1d44
   WHAT IT DOES: the finish state after the final lap step: marks the player's member retired
   when it has no finishing time yet, steps the session and, when its two seconds are up
   (and the finish is not of kind 2), goes to the result (state 6, phase 4) and schedules the
   end. */
int CInfoRaceNet::f_0f1d44()
{
    NetMember *me = D_241810.Me();
    if (me->m28 == -2 && me->m32 == -2) {
        me->m28 = -1;
        me->m32 = -1;
        me->m36 = D_2407fc->m108 * D_23f7f0.m8 + D_2407fc->m144;
        D_241810.f_086afc();
    }
    D_241810.f_086afc();
    f_0f1fdc();
    if (--m100 <= 0 && m104 != 2) {
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

/* @implements 0x0f1e64 us f_0f1e64
   WHAT IT DOES: the same finish state after the race step, the retired member's converted
   time being one lap short. */
int CInfoRaceNet::f_0f1e64()
{
    NetMember *me = D_241810.Me();
    if (me->m28 == -2 && me->m32 == -2) {
        me->m28 = -1;
        me->m32 = -1;
        me->m36 = -D_23f7f0.m8 + D_2407fc->m144;
        D_241810.f_086afc();
    }
    D_241810.f_086afc();
    f_0f24ec();
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

/* @draft 0x0f1f78 us f_0f1f78
   WHAT IT DOES: the replay state: records the ranking checker's shot and the car.
   Remaining difference: the saved registers of D_2408f0's high part and of the loaded record
   pointer are swapped (retail s1/s2), and retail loads the pointer in the call's slot (the
   same residue as the normal circuit information's replay state).
   Cycle 2026-11-16 (lreg): local-alloc orders by priority log2(refs)*refs/span: the record
   pointer (pseudo 183, 2 refs over 6 insns) outranks D_2408f0's high part (185, 3 refs over
   22), so it takes s1. Retail's order needs the pointer live over more than ~15 insns, i.e.
   sched1 loading it earlier or its store later. No source change found that implies that;
   none tried. (tools/fn.py --rtl misses this section: the bare tag name is matched without
   the class prefix.) */
int CInfoRaceNet::f_0f1f78()
{
    D_2408f0->m220 = director.f_0ee6b8();
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    return 0;
}

/* @draft 0x0f1fdc us f_0f1fdc
   WHAT IT DOES: the race step of the final laps: records the car, steps the ranking, then asks
   the car's position tracker how far it is from the line. A car that reaches a new lap is
   noted (kind 1, or 2 when it is the race's last). Kind 1 closes the lap: its time, the
   player's lap and sector table, and the lap clock restarts. Kind 2 finishes the race: the
   lap, race and finishing times, the finish phase (state 3), outside the replay the end
   schedule, the last sector time and the ranking's finish. Otherwise kind 0 times the
   player's sector ends. Then the best lap, the ranking sort, the player's place and the
   ranking's shot, every other car's sector and lap times, and the race clock (held at five
   minutes while the ranking says so). As the time attack information's (0x0f013c).
   Remaining difference: two words, the same as the time attack information's: retail keeps
   the sector end step's tracker result in a3 (the register of the race time it was computed
   from); here it shares t0 with the first tracker result. A separate local gives a1 (it is
   allocated before the laps pointer); reusing the race time's variable for the result makes
   it one multi-block pseudo that conflicts with a0..a3 and gets t1. */
void CInfoRaceNet::f_0f1fdc()
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
    D_2408f0->m220 = director.f_0ee6b8();
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
    if (director.Holding() && m104 != 2 && D_2408f0->m32 > 30050)
        D_2408f0->m32 = 30000;
    else
        D_2408f0->m32 -= 50;
}

/* @implements 0x0f24ec us f_0f24ec
   WHAT IT DOES: the race step before the final laps: records the car, steps the ranking and,
   once the car has crossed the line onto its first lap, starts the lap clock and the race
   time, notes the first lap's start and goes to the race state (state 2, phase 1). Then the
   ranking sort, the player's place and the ranking's shot, every other car's sector and lap
   times, and the race clock (held at five minutes while the ranking says so). As the time
   attack information's (0x0f0638). */
void CInfoRaceNet::f_0f24ec()
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
    D_2408f0->m220 = director.f_0ee6b8();
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
    if (director.Holding() && m104 != 2 && D_2408f0->m32 > 30050)
        D_2408f0->m32 = 30000;
    else
        D_2408f0->m32 -= 50;
}
