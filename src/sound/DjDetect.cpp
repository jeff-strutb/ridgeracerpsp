/* The DJ event detector object file (retail 0x08f608 to 0x09232c). Each frame the detector
   looks at the race (the player's position, the lap, the gaps to the cars ahead and behind,
   the time, the section records) and raises flags for the DJ events it sees; the event monitor
   queues the raised ones. A section table keeps per car and per section split records. The
   file's last function, 0x09232c, is in DjSound.cpp. */

struct Pair {
    char *a;
    int b;
};

/* The sequence manager, as far as its car settings are concerned. */
struct CSequence {
    Pair f_003200(int i);
};
extern CSequence D_1dd6b0;

/* The car database. */
struct CDataBase {
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
};
extern CDataBase D_240740;

extern "C" void *memcpy(void *, const void *, unsigned int);

extern unsigned char D_24063c[];
extern const int D_1a211c[];

/* The course's section data. */
struct CCourseData {
    int m0[2];
    void *sections;
};
extern CCourseData D_242c90;

void f_09b070(float *out, const void *rot, int n);
int f_093bac(void *s);
int f_093bc8(void *s, int i, int cls);
int f_093bf0(void *s, int i, int cls);
int f_093c18(void *s, int i, int cls);
int f_093ca0(void *s, int i);
int f_093cb4(void *s, int i);

struct CCar {
    char pad0[76];
    int m76;
    char pad80[128];
    int rot[4];
    char pad224[1568];
    float m1792;
    char pad1796[8];
    int m1804;
    char pad1808[28];
    float m1836[3];
    char pad1848[40];
    int m1888;
    char pad1892[60];
    int m1952;
    char pad1956[188];
    float m2144;
    char pad2148[64];
    int m2212;
};

struct CRaceInfo {
    int m0[4];
    int m16;
    int m20[4];
    int m36;
    int m40[2];
    int m48;
    int m52;
    int m56;
    char pad60[48];
    int m108;
    int m112;
    char pad116[12];
    int m128;
    char pad132[64];
    CCar *player;
    int m200;
    CCar **cars;
    CCar **m208;
    CCar **order;
    int count;
    CCar *marked;
};
extern CRaceInfo *D_2407fc;

struct CSystemFlags {
    int m0;
    int seed;
    char m8[3];
    unsigned char m11;
};
extern CSystemFlags *D_1d88a0;

extern int D_23f7f8;
extern char D_245178[];
void f_00d354(void *log, int level, const char *fmt, ...);

/* One car's record for one section. */
struct CSplit {
    float m0;
    float m4;
    int m8;
    bool m12;
    bool m13;
    int m16;
    int m20;
};

/* The section table: a record per car and per section. */
class CDjSection {
public:
    CDjSection();
    ~CDjSection();
    void f_08f680();
    void f_08f8e4();
    int f_08f988();
    int f_08fef4();
    int f_08ff5c();

    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
    CSplit **m20;
};

/* @implements 0x08f608 us _ZN10CDjSectionC2Ev
   WHAT IT DOES: Builds the table with no records, then loads them. */
CDjSection::CDjSection()
{
    m20 = 0;
    f_08f680();
}

/* @implements 0x08f628 us _ZN10CDjSectionC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x08f648 us _ZN10CDjSectionD2Ev
   WHAT IT DOES: Frees the records. */
CDjSection::~CDjSection()
{
    f_08f8e4();
}

/* @implements 0x08f664 us _ZN10CDjSectionD1Ev
   WHAT IT DOES: The same, as the complete object. */

/* A player car's settings. */
static inline Pair GetM(int i)
{
    Pair r = D_1dd6b0.f_003200(i);
    return r;
}

/* @draft 0x08f680 us f_08f680
   WHAT IT DOES: Looks up the player car's class, counts the course's sections and allocates a
   record row per car, each record starting from the section's reference times for that class
   and its two flags.
   Remaining difference: the bytes match; the "Class" string reference is BADREF only because
   the strings that follow it in .rodata belong to f_08f988 (CCorneringJudge::Process), not yet
   transcribed. */
void CDjSection::f_08f680()
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    m12 = 0;
    Pair p = GetM(0);
    char *c = p.a;
    char *f = D_240740.f_0368e8("Class", c, 0, 0);
    memcpy(D_24063c, f, D_1a211c[1]);
    int cls = D_24063c[0];
    m16 = f_093bac(D_242c90.sections);
    int n = D_2407fc->m36;
    if (m16 == 0) {
        m20 = 0;
        return;
    }
    m20 = new CSplit *[n];
    for (int i = 0; i < n; i++)
        m20[i] = new CSplit[m16];
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < m16; k++) {
            m20[j][k].m0 = f_093bc8(D_242c90.sections, k, cls);
            m20[j][k].m4 = f_093bf0(D_242c90.sections, k, cls);
            m20[j][k].m8 = f_093c18(D_242c90.sections, k, cls);
            m20[j][k].m12 = f_093ca0(D_242c90.sections, k);
            m20[j][k].m13 = f_093cb4(D_242c90.sections, k);
            m20[j][k].m20 = m20[j][k].m16 = 0;
        }
    }
}

/* @implements 0x08f8e4 us f_08f8e4
   WHAT IT DOES: Frees every car's record row and the row table. */
void CDjSection::f_08f8e4()
{
    if (m20) {
        for (int i = 0; i < D_2407fc->m36; i++)
            if (m20[i])
                delete[] m20[i];
        if (m20)
            delete[] m20;
        m20 = 0;
    }
}

/* @implements 0x08fef4 us f_08fef4
   WHAT IT DOES: Counts the player's drift and boost frames while the state is 1 (state 0
   clears the count) and returns the count. */
int CDjSection::f_08fef4()
{
    if (m0 == 0) {
        m12 = 0;
        return 0;
    }
    if (m0 != 1)
        return m12;
    CCar *p = D_2407fc->player;
    if (p->m1888)
        m12++;
    if (p->m1952)
        m12++;
    return m12;
}

static inline CCar *Car(int i)
{
    return D_2407fc->cars[i];
}

/* The event detector. */
class CDjDetect {
public:
    CDjDetect();
    ~CDjDetect();
    void f_090104();
    void f_09022c();
    void f_0902bc(int n);
    void f_0902e8(int n);
    void f_090320();
    void f_090340();
    int *f_090360();
    void f_090368();
    int f_090370();
    CCar *f_0903c4();
    CCar *f_0903d4();
    CCar *f_0903e4();
    CCar *f_090474();
    CCar *f_090530();
    int f_090654();
    int f_09066c();
    int f_090684();
    int f_09069c();
    int f_0906b4();
    int f_0906cc();
    int f_0906e0();
    int f_0906f8();
    int f_090710();
    float f_090728();
    void f_090738();
    void f_090778();
    void f_0907c4();
    void f_0908c0();
    void f_090900();
    void f_090944();
    void f_090aa4();
    void f_090c2c();
    void f_090ef0();
    void f_0910f4();
    int f_091634();
    int f_09196c();
    int f_091e74();
    int f_091e9c();
    int f_092080();
    int f_09211c();
    int f_091714();
    int f_091a4c();
    void f_091258();
    void f_091578();

    CDjSection *section;
    int *count;
    int *flag;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    float m32;
    int m36;
    float m40[32];
    int m168[32];
    float m296[3];
    int m308;
    float m312;
    float m316;
    int m320;
    int m324;
    struct {
        int a;
        int b;
        int c;
    } m328[3];
    int m364;
    int m368;
    int m372;
    int m376;
    int m380;
    int m384;
    int m388;
    int m392;
    int m396;
    bool m400;
};

/* @implements 0x090094 us _ZN9CDjDetectC2Ev
   WHAT IT DOES: Builds the detector. */
CDjDetect::CDjDetect()
{
    f_090104();
}

/* @implements 0x0900b0 us _ZN9CDjDetectC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x0900cc us _ZN9CDjDetectD2Ev
   WHAT IT DOES: Frees the detector's tables. */
CDjDetect::~CDjDetect()
{
    f_09022c();
}

/* @implements 0x0900e8 us _ZN9CDjDetectD1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x090104 us f_090104
   WHAT IT DOES: Creates the section table and the event flag and count arrays (82 events
   each), and clears every counter and record. */
void CDjDetect::f_090104()
{
    section = new CDjSection;
    flag = new int[82];
    count = new int[82];
    f_090320();
    f_090340();
    m12 = 0;
    m16 = 0;
    m20 = 0;
    m24 = 0;
    int i;
    for (i = 0; i < 32; i++) {
        m40[i] = 0;
        m168[i] = 0;
    }
    for (int j = 0; j < 3; j++)
        m296[j] = 0;
    m308 = 0;
    m312 = 0;
    m316 = 0;
    m320 = 0;
    m28 = -1;
    m396 = -1;
    m364 = 0;
    m368 = 0;
    m372 = 0;
    m376 = 0;
    m380 = 0;
    m384 = 0;
    m388 = 0;
    m400 = 0;
    m324 = 0;
    for (i = 0; i < 3; i++) {
        m328[i].a = 0;
        m328[i].b = -1;
        m328[i].c = -1;
    }
}

/* @implements 0x09022c us f_09022c
   WHAT IT DOES: Frees the flag and count arrays and the section table. */
void CDjDetect::f_09022c()
{
    if (flag)
        delete[] flag;
    flag = 0;
    if (count)
        delete[] count;
    count = 0;
    delete section;
    section = 0;
}

/* @implements 0x0902bc us f_0902bc
   WHAT IT DOES: Raises event n and counts it. */
void CDjDetect::f_0902bc(int n)
{
    flag[n] = 1;
    count[n]++;
}

/* @implements 0x0902e8 us f_0902e8
   WHAT IT DOES: Raises event n the first time only, and counts it. */
void CDjDetect::f_0902e8(int n)
{
    if (count[n] == 0)
        flag[n] = 1;
    count[n]++;
}

/* @implements 0x090320 us f_090320
   WHAT IT DOES: Lowers every event flag. */
void CDjDetect::f_090320()
{
    for (int i = 0; i < 82; i++)
        flag[i] = 0;
}

/* @implements 0x090340 us f_090340
   WHAT IT DOES: Clears every event count. */
void CDjDetect::f_090340()
{
    for (int i = 0; i < 82; i++)
        count[i] = 0;
}

/* @implements 0x090360 us f_090360
   WHAT IT DOES: Returns the event flags. */
int *CDjDetect::f_090360()
{
    return flag;
}

/* @implements 0x090368 us f_090368
   WHAT IT DOES: Nothing. */
void CDjDetect::f_090368()
{
}

/* @implements 0x090370 us f_090370
   WHAT IT DOES: Counts the cars still in the race. */
int CDjDetect::f_090370()
{
    int n = 0;
    for (int i = 0; i < D_2407fc->count; i++)
        if (Car(i)->m76)
            n++;
    return n;
}

/* @implements 0x0903c4 us f_0903c4
   WHAT IT DOES: Returns the player's car. */
CCar *CDjDetect::f_0903c4()
{
    return D_2407fc->player;
}

/* @implements 0x0903d4 us f_0903d4
   WHAT IT DOES: Returns the race's marked car. */
CCar *CDjDetect::f_0903d4()
{
    return D_2407fc->marked;
}

/* @implements 0x0903e4 us f_0903e4
   WHAT IT DOES: Returns the car one place ahead of the player, or 0 when the player leads. */
CCar *CDjDetect::f_0903e4()
{
    int i;
    for (i = 0; i < D_2407fc->count; i++)
        if (D_2407fc->order[i] == f_0903c4())
            break;
    if (i == 0)
        return 0;
    return D_2407fc->order[i - 1];
}

/* @implements 0x090474 us f_090474
   WHAT IT DOES: Returns the car one place behind the player, or 0 when the player is last of
   the cars still running. */
CCar *CDjDetect::f_090474()
{
    int i;
    for (i = 0; i < D_2407fc->count; i++)
        if (D_2407fc->order[i] == f_0903c4())
            break;
    if (i < f_090370() - 1)
        return D_2407fc->order[i + 1];
    return 0;
}

/* @implements 0x090530 us f_090530
   WHAT IT DOES: Returns the nearest rival by distance: the car ahead or behind, whichever gap
   is smaller (0 when the player runs alone). */
CCar *CDjDetect::f_090530()
{
    if (f_090370() == 1)
        return 0;
    int i;
    for (i = 0; i < D_2407fc->count; i++)
        if (D_2407fc->m208[i] == f_0903c4())
            break;
    if (i >= f_090370() - 1)
        return D_2407fc->order[i - 1];
    if (i == 0)
        return D_2407fc->order[1];
    CCar **o = D_2407fc->order;
    if (o[i - 1]->m2144 - o[i]->m2144 < o[i]->m2144 - o[i + 1]->m2144)
        return o[i - 1];
    return o[i + 1];
}

/* @implements 0x090654 us f_090654
   WHAT IT DOES: Tells whether the race state is 1. */
int CDjDetect::f_090654()
{
    return D_2407fc->m16 == 1;
}

/* @implements 0x09066c us f_09066c
   WHAT IT DOES: Tells whether the race state is 2. */
int CDjDetect::f_09066c()
{
    return D_2407fc->m16 == 2;
}

/* @implements 0x090684 us f_090684
   WHAT IT DOES: Tells whether the race state is 3. */
int CDjDetect::f_090684()
{
    return D_2407fc->m16 == 3;
}

/* @implements 0x09069c us f_09069c
   WHAT IT DOES: Tells whether the race state is 4. */
int CDjDetect::f_09069c()
{
    return D_2407fc->m16 == 4;
}

/* @implements 0x0906b4 us f_0906b4
   WHAT IT DOES: Tells whether the race state is 5. */
int CDjDetect::f_0906b4()
{
    return D_2407fc->m16 == 5;
}

/* @implements 0x0906cc us f_0906cc
   WHAT IT DOES: Tells whether the race mode is 0. */
int CDjDetect::f_0906cc()
{
    return D_2407fc->m56 == 0;
}

/* @implements 0x0906e0 us f_0906e0
   WHAT IT DOES: Tells whether the race mode is 5. */
int CDjDetect::f_0906e0()
{
    return D_2407fc->m56 == 5;
}

/* @implements 0x0906f8 us f_0906f8
   WHAT IT DOES: Tells whether the race mode is 1. */
int CDjDetect::f_0906f8()
{
    return D_2407fc->m56 == 1;
}

/* @implements 0x090710 us f_090710
   WHAT IT DOES: Tells whether the race mode is 2. */
int CDjDetect::f_090710()
{
    return D_2407fc->m56 == 2;
}

/* @implements 0x090728 us f_090728
   WHAT IT DOES: Returns the frame counter as a float. */
float CDjDetect::f_090728()
{
    return D_23f7f8;
}

/* @implements 0x090738 us f_090738
   WHAT IT DOES: Notes whether the player has passed a new section since the last frame. */
void CDjDetect::f_090738()
{
    if (m28 < f_0903c4()->m2212)
        m392 = 1;
    else
        m392 = 0;
}

/* @implements 0x090778 us f_090778
   WHAT IT DOES: Remembers the player's section, distance and lap for the next frame. */
void CDjDetect::f_090778()
{
    m28 = f_0903c4()->m2212;
    m32 = f_0903c4()->m2144;
    m36 = D_2407fc->m112;
}

/* @implements 0x0907c4 us f_0907c4
   WHAT IT DOES: The frame step. Unless the game is paused: notes a new section; before the
   first frame is done runs the event checks; then the per-frame checks, remembers the state
   and counts the frames, the frames in modes 5 or 1 and the frames in mode 1. */
void CDjDetect::f_0907c4()
{
    if (D_1d88a0->m11)
        return;
    f_090738();
    if (!m400) {
        f_090944();
        f_090aa4();
        f_090ef0();
        if (!f_09066c())
            f_0910f4();
        f_091258();
        f_091578();
    }
    f_090c2c();
    f_090778();
    m16++;
    if (f_0906e0() || f_0906f8())
        m20++;
    if (f_0906f8())
        m24++;
}

/* @implements 0x0908c0 us f_0908c0
   WHAT IT DOES: Raises event 63 in race state 2, otherwise event 62. */
void CDjDetect::f_0908c0()
{
    if (f_09066c())
        f_0902e8(63);
    else
        f_0902e8(62);
}

/* @implements 0x090900 us f_090900
   WHAT IT DOES: Raises event 0 on the first call and counts the calls. */
void CDjDetect::f_090900()
{
    if (m12 == 0)
        f_0902e8(0);
    m12++;
}

/* @implements 0x090944 us f_090944
   WHAT IT DOES: Time checks: raises events 5 to 8 as the race time passes -9, -6 and -3
   seconds and zero, the start position events 11, 10 and 9 at frame 120, and while the player
   is still in the first section beyond 300, event 12 (13 on the final lap in state 3). */
void CDjDetect::f_090944()
{
    if (D_2407fc->m48 > -9000)
        f_0902e8(5);
    if (D_2407fc->m48 > -6000)
        f_0902e8(6);
    if (D_2407fc->m48 > -3000)
        f_0902e8(7);
    if (D_2407fc->m48 >= 0)
        f_0902e8(8);
    if (m20 == 120) {
        int s = f_0903c4()->m1804;
        if (s == 0)
            f_0902e8(11);
        else if (s == 1)
            f_0902e8(10);
        else if (s == 2)
            f_0902e8(9);
    }
    CCar *p = f_0903c4();
    if (p->m2212 == 0 && p->m2144 > 300.0f) {
        if (f_090684() && D_2407fc->m112 == 1)
            f_0902e8(13);
        else
            f_0902e8(12);
    }
}

/* @implements 0x090aa4 us f_090aa4
   WHAT IT DOES: Position checks on a new section: event 14 for a change of place, 17, 16 and
   24 for third, second and first place, and in first place outside state 2 the lap events 18
   to 23. */
void CDjDetect::f_090aa4()
{
    if (m392 != 1)
        return;
    if (D_2407fc->m56 == 2)
        return;
    int r = D_2407fc->m36 - D_2407fc->m108;
    if (r != D_2407fc->m36) {
        if (f_091e74() == 1)
            f_0902bc(14);
    }
    if (r == 3)
        f_0902e8(17);
    if (r == 2)
        f_0902e8(16);
    if (r == 1) {
        if (f_09066c())
            f_0902e8(24);
    }
    if (r == 1 && !f_09066c()) {
        int lap = D_2407fc->m112;
        if (lap == 0)
            f_0902bc(18);
        else if (lap == 1)
            f_0902bc(19);
        else if (lap == 2)
            f_0902bc(20);
        else if (lap == 3)
            f_0902bc(21);
        else if (lap >= 4 && lap <= 7)
            f_0902bc(22);
        else if (lap >= 8)
            f_0902bc(23);
    }
}

/* @implements 0x0910f4 us f_0910f4
   WHAT IT DOES: The rival checks of mode 1: outside state 3 the car behind (events 30, 31),
   then the overtakes (33 passed, 32 passed by), and outside state 3 the car ahead (36, 35)
   and the battle event 34. */
void CDjDetect::f_0910f4()
{
    if (D_2407fc->m56 != 1)
        return;
    int r;
    if (!f_090684()) {
        r = f_091634();
        if (r == 1)
            f_0902bc(30);
        if (r == 2)
            f_0902bc(31);
    }
    r = f_091714();
    if (r == 1)
        f_0902bc(33);
    if (r == -1)
        f_0902bc(32);
    if (!f_090684()) {
        r = f_09196c();
        if (r == 1)
            f_0902bc(36);
        if (r == 2)
            f_0902bc(35);
    }
    if (!f_090684()) {
        r = f_091a4c();
        if (r == 1)
            f_0902bc(34);
    }
}

/* @implements 0x091578 us f_091578
   WHAT IT DOES: Turns the section table's split result into events 44 and 43 (result 3 picks
   one by the frame count's parity). */
void CDjDetect::f_091578()
{
    int r = section->f_08ff5c();
    if (r == 1)
        f_0902bc(44);
    if (r == 2)
        f_0902bc(43);
    if (r == 3) {
        if ((m16 & 1) == 0)
            f_0902bc(44);
        else
            f_0902bc(43);
    }
    if (r == 4)
        f_0902bc(44);
}

/* @implements 0x091634 us f_091634
   WHAT IT DOES: Watches the car behind: once it has stayed within 15 for 300 frames, returns 1
   (2 when it is the race's marked car); otherwise 0. */
int CDjDetect::f_091634()
{
    if (!f_090474())
        return 0;
    float d = f_0903c4()->m2144;
    d = d - f_090474()->m2144;
    if (d < 0)
        d += f_090728();
    if (d > 15.0f) {
        m364 = 0;
        return 0;
    }
    int wait = 300;
    m364++;
    if (m364 > wait) {
        m364 = 0;
        CCar *b = f_090474();
        int h = b != f_0903d4();
        return h + 1;
    }
    return 0;
}

/* @draft 0x09196c us f_09196c
   WHAT IT DOES: Watches the car ahead: once the player has stayed within 15 of it (20 on the
   final lap) for 180 frames, returns 1 (2 on the final lap); otherwise 0.
   Remaining difference: retail reloads D_2407fc for the second lap test and keeps the result
   in a0; here the pointer and the constant 1 stay in registers from the limit choice (an
   if/else or ternary limit gives retail's reload but loads both limits in separate blocks). */
int CDjDetect::f_09196c()
{
    if (!f_0903e4()) {
        m376 = 0;
        return 0;
    }
    float d = f_0903e4()->m2144;
    d = d - f_0903c4()->m2144;
    if (d < 0)
        d += f_090728();
    float lim = 20.0f;
    if (D_2407fc->m112 != 1)
        lim = 15.0f;
    if (d > lim) {
        m376 = 0;
        return 0;
    }
    m376++;
    if (m376 < 181)
        return 0;
    if (D_2407fc->m112 == 1) {
        m376 = 0;
        return 2;
    }
    m376 = 0;
    return 1;
}

/* @implements 0x091e74 us f_091e74
   WHAT IT DOES: Tells whether the race's leader changed since the last call. */
int CDjDetect::f_091e74()
{
    int r = 0;
    if (D_2407fc->m128 != m396) {
        m396 = D_2407fc->m128;
        r = 1;
    }
    return r;
}

/* @implements 0x091e9c us f_091e9c
   WHAT IT DOES: Watches every car's boost gauge: a gauge that empties clears the car's mark;
   a gauge that rises marks the car once, and the first rise of the player returns 1 while a
   rival's within 15 of the player returns 2 (logging its slot and distance); a full gauge
   marks it, a falling one clears the mark. */
int CDjDetect::f_091e9c()
{
    for (int i = 0; i < D_2407fc->count; i++) {
        CCar *c = D_2407fc->cars[i];
        if (c->m1792 == 0) {
            m40[i] = 0;
            m168[i] = 0;
        } else if (m40[i] < c->m1792) {
            m40[i] = c->m1792;
            if (m168[i] == 0) {
                m168[i] = 1;
                CCar *p = f_0903c4();
                if (c == p)
                    return 1;
                double dist = p->m2144 - c->m2144;
                f_00d354(D_245178, 0x800000, "BufferNum = %d  Distance = %f\n", i, dist);
                double a = dist;
                if (a < 0)
                    a = -a;
                if (!(a >= 15.0))
                    return 2;
            } else {
                m40[i] = c->m1792;
                m168[i] = 1;
            }
        } else if (c->m1792 == 1.0f) {
            m40[i] = 1.0f;
            m168[i] = 1;
        } else if (c->m1792 < m40[i]) {
            m40[i] = c->m1792;
            m168[i] = 0;
        }
    }
    return 0;
}

/* @implements 0x092080 us f_092080
   WHAT IT DOES: Copies the player's three gauges and counts the full ones; returns the count
   when it grew since the last call, otherwise 0. */
int CDjDetect::f_092080()
{
    int n = 0;
    for (int i = 0; i < 3; i++) {
        float v = f_0903c4()->m1836[i];
        m296[i] = v;
        if (v == 100.0f)
            n++;
    }
    if (m308 < n) {
        m308 = n;
        return n;
    }
    m308 = n;
    return 0;
}

/* @draft 0x09211c us f_09211c
   WHAT IT DOES: Spin check: adds up the player's heading change (wrapped into -pi to pi);
   a change of direction or 199 frames restart it, and a full turn either way returns 1.
   Remaining difference: retail reloads the frame count after the angle store and the angle
   for the double compare; here both stay in registers (the angle sum lands in $f12). */
int CDjDetect::f_09211c()
{
    float a[4];
    f_09b070(a, f_0903c4()->rot, 4);
    float d = a[1] - m312;
    m312 = a[1];
    if (d < -3.14159265f)
        d += 6.2831853f;
    if (d > 3.14159265f)
        d -= 6.2831853f;
    m316 += d;
    m320++;
    int wait = 198;
    int r = 0;
    if ((m316 > 0 && d < 0) || (m316 < 0 && d > 0) || m320 > wait) {
        m320 = 0;
    } else {
        double v = m316;
        if (v < 0)
            v = -v;
        if (!(v > 6.28318548202514648))
            return 0;
        m320 = 0;
        r = 1;
    }
    m316 = 0;
    return r;
}
