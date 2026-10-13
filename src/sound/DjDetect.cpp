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

int f_093bac(void *s);
int f_093bc8(void *s, int i, int cls);
int f_093bf0(void *s, int i, int cls);
int f_093c18(void *s, int i, int cls);
int f_093ca0(void *s, int i);
int f_093cb4(void *s, int i);

struct CCar {
    char pad0[76];
    int m76;
    char pad80[1724];
    int m1804;
    char pad1808[80];
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
    char pad116[80];
    CCar *player;
    int m200;
    CCar **cars;
    CCar **m208;
    CCar **order;
    int count;
    int m220;
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

/* @implements 0x08f680 us f_08f680
   WHAT IT DOES: Looks up the player car's class, counts the course's sections and allocates a
   record row per car, each record starting from the section's reference times for that class
   and its two flags. */
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
    int f_0903d4();
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
    int m40[32];
    int m168[32];
    int m296[3];
    int m308;
    int m312;
    int m316;
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
   WHAT IT DOES: Returns the race's word at +220. */
int CDjDetect::f_0903d4()
{
    return D_2407fc->m220;
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
