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
extern CDataBase D_2407d0;

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
int f_093c78(void *s, int i);
int f_093c8c(void *s, int i);
float f_093c68(void *s);
float f_093c70(void *s);

struct CCar {
    char pad0[76];
    int m76;
    char pad80[112];
    float m192;
    char pad196[12];
    int rot[4];
    char pad224[1520];
    float m1744;
    float m1748;
    char pad1752[40];
    float m1792;
    int m1796;
    int m1800;
    int m1804;
    char pad1808[28];
    float m1836[3];
    char pad1848[40];
    int m1888;
    char pad1892[8];
    float m1900;
    char pad1904[48];
    int m1952;
    char pad1956[8];
    float m1964;
    char pad1968[176];
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
    char pad60[8];
    int m68;
    char pad72[36];
    int m108;
    int m112;
    char pad116[12];
    int m128;
    int m132;
    char pad136[4];
    float m140;
    float m144;
    char pad148[44];
    int m192;
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
extern char D_24517c[];
void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...);

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

/* @draft 0x08f988 us f_08f988
   WHAT IT DOES: The cornering judge (CCorneringJudge::Process). State 0 waits for the player to
   enter the section in turn (the debug screen shows its distance, its kind and the previous
   section's limit and process times) and records the entry once the player is inside it; state
   1 shows the progress through the section as dots, records the entry time if missing and,
   once past the section's end, the exit time, moving to state 2; state 2 goes back to 0. An
   unknown state is logged and reset. Returns the state.
   Remaining difference: retail places the previous-section fix-up (m16 - 1 when m4 is 0) out of
   line with a jump back; here bb-reorder keeps it inline (both if spellings, and the assign-
   then-fix-up form, compile alike), shifting the state 0 tail; state 1's float registers
   (section start in $f2, the 60.0 load after the division) are a local-alloc tie. Retail's
   shape is k = m4 (v0); if (!k) k = m16 (out of line); prev = k - 1 (a1, the addiu in the join);
   written so (int k = m4; if (k == 0) k = m16;) k ties to a1 and dbr makes it beqzl inline (-8 B). */
int CDjSection::f_08f988()
{
    CCar *p = D_2407fc->player;
    if (m16 == 0) {
        m0 = 0;
        return m0;
    }
    if (m0 == 0) {
        f_02db68(D_24517c, 0x800000, 1, 18, 0xffffff, "Next Corner Rzp = %.1f",
                 m20[p->m2212][m4].m0);
        if (m20[p->m2212][m4].m12 && m20[p->m2212][m4].m13)
            f_02db68(D_24517c, 0x800000, 30, 18, 0xffffff, "(Cornering or Drift)");
        else if (m20[p->m2212][m4].m12)
            f_02db68(D_24517c, 0x800000, 30, 18, 0xffffff, "(Cornering)");
        else if (m20[p->m2212][m4].m13)
            f_02db68(D_24517c, 0x800000, 30, 18, 0xffffff, "(Drift)");
        else
            f_02db68(D_24517c, 0x800000, 30, 18, 0xffffff, "(not assigned)");
        f_02db68(D_24517c, 0x800000, 1, 19, 0xffffff, "MyCar Rzp = %.1f", D_2407fc->m144);
        {
            int prev = m4 - 1;
            if (m4 == 0)
                prev = m16 - 1;
            f_02db68(D_24517c, 0x800000, 1, 21, 0xffffff, "Limit time = %d",
                     m20[p->m2212][prev].m8);
            f_02db68(D_24517c, 0x800000, 1, 22, 0xffffff, "Process time = %d",
                     m20[p->m2212][prev].m20 - m20[p->m2212][prev].m16);
        }
        if (m20[p->m2212][m4].m0 < D_2407fc->m144 && D_2407fc->m144 < m20[p->m2212][m4].m4
            && m20[p->m2212][m4].m16 == 0)
            m0 = 1;
    } else if (m0 == 1) {
        int n = (int)((D_2407fc->m144 - m20[p->m2212][m4].m0)
                      / (m20[p->m2212][m4].m4 - m20[p->m2212][m4].m0) * 60.0f);
        f_02db68(D_24517c, 0x800000, 1, 18, 0xffffff, "timing......");
        f_02db68(D_24517c, 0x800000, 1, 19, 0xffffff, "MyCar Rzp = %.1f", D_2407fc->m144);
        for (int i = 0; i < n; i++)
            f_02db68(D_24517c, 0x800000, i, 20, 0xffffff, ".");
        f_02db68(D_24517c, 0x800000, 1, 21, 0xffffff, "Limit time = %d",
                 m20[p->m2212][m4].m8);
        f_02db68(D_24517c, 0x800000, 1, 22, 0xffffff, "timing......");
        if (m20[p->m2212][m4].m16 == 0)
            m20[p->m2212][m4].m16 = D_2407fc->m48 / 3;
        if (m20[p->m2212][m4].m20 == 0 && m20[p->m2212][m4].m4 < D_2407fc->m144) {
            m20[p->m2212][m4].m20 = D_2407fc->m48 / 3;
            m0 = 2;
        }
    } else if (m0 == 2) {
        m0 = 0;
    } else {
        f_00d354(D_245178, 0x800000, "Errer!! in func CCorneringJudge::Process(): nState = %d\n", m0);
        m0 = 0;
    }
    return m0;
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

/* @implements 0x08ff5c us f_08ff5c
   WHAT IT DOES: The section split check, in race mode 1 once the player is on a section: runs
   the cornering judge and the drift count; when the judge says 2 and the player did not drift,
   compares the split of the section in turn against its reference and returns 3, 1, 2 or 4 by
   the section's two flags (0 when the split was not beaten), then moves on to the next section
   in turn. */
int CDjSection::f_08ff5c()
{
    int r = 0;
    CCar *p = D_2407fc->player;
    if (D_2407fc->m56 == 1 && p->m2212 >= 0) {
        int a = f_08f988();
        int b = f_08fef4();
        if (a == 2) {
            if (b == 0 && m20[p->m2212][m4].m20 - m20[p->m2212][m4].m16 < m20[p->m2212][m4].m8) {
                if (m20[p->m2212][m4].m12 && m20[p->m2212][m4].m13)
                    r = 3;
                else if (m20[p->m2212][m4].m12)
                    r = 1;
                else
                    r = m20[p->m2212][m4].m13 ? 2 : 4;
            }
            if (++m4 == m16)
                m4 = 0;
        }
    }
    return r;
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
    int f_091bf0();
    int f_091d9c();
    int f_0922a0();

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

/* @implements 0x090c2c us f_090c2c
   WHAT IT DOES: The end of race checks, every frame: on the last lap past the final straight
   (or the last corner when the course has no straight) raises event 48 (49 without a straight)
   and stops the event checks; then, in race mode 2, the result events for states 1 (50 to 53
   by place), 2 (61 or 60 by the record), 3 (58 or 59), 4 (57, or 54 to 56 by the tour's extra
   class) and 5 (58 or 59). */
void CDjDetect::f_090c2c()
{
    int first = 1;
    float pos = f_093c68(D_242c90.sections);
    if (pos == 0) {
        pos = f_093c70(D_242c90.sections);
        first = 0;
    }
    if (f_0903c4()->m2212 == D_2407fc->m36 - 1 && pos <= D_2407fc->m144) {
        if (first)
            f_0902e8(48);
        else
            f_0902e8(49);
        m400 = 1;
    }
    CRaceInfo *ri = D_2407fc;
    if (ri->m56 != 2)
        return;
    if (f_090654()) {
        int lap = ri->m112;
        if (lap == 0)
            f_0902e8(50);
        if (lap == 1)
            f_0902e8(51);
        if (lap == 2)
            f_0902e8(52);
        if (lap >= 3)
            f_0902e8(53);
    }
    if (f_09066c()) {
        if (D_2407fc->m132 < D_2407fc->m20[1])
            f_0902e8(61);
        else
            f_0902e8(60);
    }
    if (f_090684()) {
        if (D_2407fc->m112 == 0)
            f_0902e8(58);
        else
            f_0902e8(59);
    }
    if (f_09069c()) {
        if (D_2407fc->m112 < D_2407fc->m68) {
            char *f = D_2407d0.f_0368e8("TourExtra", (char *)D_2407fc->m0[0], 0, 0);
            memcpy(D_24063c, f, D_1a211c[1]);
            int cls = D_24063c[0];
            if (cls == 1)
                f_0902e8(54);
            if (cls == 2)
                f_0902e8(55);
            if (cls == 3)
                f_0902e8(56);
        } else
            f_0902e8(57);
    }
    if (f_0906b4()) {
        if (D_2407fc->m112 == 0)
            f_0902e8(58);
        else
            f_0902e8(59);
    }
}

/* @implements 0x090ef0 us f_090ef0
   WHAT IT DOES: The per-car checks: the boost gauges (events 25, and 26 outside state 2), the
   player's full gauges in mode 1 (27 to 29), the drift against the nearest rival (38, 37, 40,
   39), the boost level (41, 42), the spin (45) and the jumps (46, 47). */
void CDjDetect::f_090ef0()
{
    int r = f_091e9c();
    if (r == 1)
        f_0902bc(25);
    if (!f_09066c() && r == 2)
        f_0902bc(26);
    r = f_092080();
    if (f_0906f8()) {
        if (r == 1)
            f_0902bc(27);
        if (r == 2)
            f_0902bc(28);
        if (r == 3)
            f_0902bc(29);
    }
    r = f_091bf0();
    if (r == -2)
        f_0902bc(38);
    if (r == -1)
        f_0902bc(37);
    if (r == 2)
        f_0902bc(40);
    if (r == 1)
        f_0902bc(39);
    r = f_091d9c();
    if (r == 1)
        f_0902bc(41);
    if (r == 2)
        f_0902bc(42);
    r = f_09211c();
    if (r == 1)
        f_0902bc(45);
    r = f_0922a0();
    if (r == 1)
        f_0902bc(46);
    if (r == 2)
        f_0902bc(47);
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

/* @implements 0x091258 us f_091258
   WHAT IT DOES: The idle checks of race modes 5 and 1: 300 frames of a race flag raise event
   78; the player standing still for over 300 frames raises 79; over 180 frames at a speed of
   50 or less raises 81 in state 2, otherwise 80; then the race time events: 64 and 65 below
   3:02.7 and 1:32.7 (not in state 3), and 66 to 76 as the time falls below the thresholds
   from 32.7 down to 0.15 seconds. */
void CDjDetect::f_091258()
{
    CRaceInfo *ri = D_2407fc;
    if ((ri->m56 == 5) | (ri->m56 == 1)) {
        if (ri->m192 == 0)
            m380 = 0;
        else if (++m380 == 300) {
            f_0902bc(78);
            m380 = 0;
        }
        int wait = 300;
        CCar *p = f_0903c4();
        if (p->m1744 == 0 && p->m1748 == 0) {
            if (++m384 > wait) {
                f_0902bc(79);
                m384 = 0;
            }
        } else
            m384 = 0;
        int slow = 180;
        if (D_2407fc->m140 > 50.0f)
            m388 = 0;
        else if (++m388 > slow) {
            if (f_09066c())
                f_0902bc(81);
            else
                f_0902bc(80);
            m388 = 0;
        }
        if (!f_090684()) {
            if (D_2407fc->m20[3] < 182700)
                f_0902e8(64);
            if (D_2407fc->m20[3] < 92700)
                f_0902e8(65);
        }
        if (D_2407fc->m20[3] < 32699)
            f_0902e8(66);
        if (D_2407fc->m20[3] < 29699)
            f_0902e8(67);
        if (D_2407fc->m20[3] < 26699)
            f_0902e8(68);
        if (D_2407fc->m20[3] < 23700)
            f_0902e8(69);
        if (D_2407fc->m20[3] < 20700)
            f_0902e8(70);
        if (D_2407fc->m20[3] < 17700)
            f_0902e8(71);
        if (D_2407fc->m20[3] < 14700)
            f_0902e8(72);
        if (D_2407fc->m20[3] < 11700)
            f_0902e8(73);
        if (D_2407fc->m20[3] < 8700)
            f_0902e8(74);
        if (D_2407fc->m20[3] < 5700)
            f_0902e8(75);
        if (D_2407fc->m20[3] < 150)
            f_0902e8(76);
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
   if/else or ternary limit gives retail's reload but loads both limits in separate blocks).
   RTL: the second load already goes in pass 09 (cse following the jumps through the skipped
   lim block and the two early returns); retail shares only the HIGH (lui a1 in both arms),
   so its cse path breaks before the lap test and gcse then keeps the load. */
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

/* @draft 0x091714 us f_091714
   WHAT IT DOES: Overtake check. Measures the gaps to the cars ahead and behind (500 when there
   is none) and forgets a pending overtake once both are beyond 15. When the player's place
   changed, notes an overtake made (1) or suffered (-1), or cancels it if the place went back.
   Otherwise counts the frames of a pending overtake: after 48 it is dropped, and once the gap
   (behind for a pass made, ahead for one suffered) exceeds 10 it returns 1 or -1; else 0.
   Remaining difference: the registers and the frame now match; retail zeroes the result in
   every lap-change exit block (move a0,zero before each jump), here the exits share one r = 0
   join block, which moves the delay-slot fills and the block order after the -1 case. */
int CDjDetect::f_091714()
{
    float ahead = 500.0f;
    float lim = 10.0f;
    if (f_0903e4()) {
        float d = f_0903e4()->m2144;
        ahead = d - f_0903c4()->m2144;
        if (ahead < 0)
            ahead += f_090728();
    }
    float behind;
    if (f_090474()) {
        float d = f_0903c4()->m2144;
        behind = d - f_090474()->m2144;
        if (behind < 0)
            behind += f_090728();
    } else
        behind = 500.0f;
    if (ahead > lim + 5.0f && behind > lim + 5.0f) {
        m368 = 0;
        m372 = 0;
    }
    int r;
    if (m36 != D_2407fc->m112) {
        m372 = 0;
        if (m368 == 0) {
            if (D_2407fc->m112 < m36)
                m368 = 1;
            else if (D_2407fc->m112 > m36)
                m368 = -1;
        } else if (m368 == 1) {
            if (D_2407fc->m112 < m36)
                m368 = 1;
            else if (D_2407fc->m112 > m36)
                m368 = 0;
        } else if (m368 == -1) {
            if (D_2407fc->m112 < m36)
                m368 = 0;
            else if (D_2407fc->m112 > m36)
                m368 = -1;
        }
        r = 0;
    } else {
        r = 0;
        if (m368 != 0) {
            if (m368 == 1) {
                int wait = 48;
                if (++m372 > wait) {
                    m372 = 0;
                    m368 = 0;
                } else if (behind > lim) {
                    r = 1;
                    m372 = 0;
                    m368 = 0;
                }
            } else if (m368 == -1) {
                int wait = 48;
                if (++m372 > wait) {
                    m372 = 0;
                    m368 = 0;
                } else if (ahead > lim) {
                    r = -1;
                    m372 = 0;
                    m368 = 0;
                }
            }
        }
    }
    return r;
}

/* @implements 0x091a4c us f_091a4c
   WHAT IT DOES: Battle check, once per lap: forgets records older than 3600 frames, records
   the cars ahead and behind in the first free of three slots, and when all three slots are
   full returns 1 if one car of the first record is also in the second and the third (the
   player has been fighting the same car for three laps), clearing the newest record. */
int CDjDetect::f_091a4c()
{
    int r = 0;
    if (m36 != D_2407fc->m112) {
        for (int i = 0; i < 3; i++)
            if (m16 - m328[i].a > 3600) {
                m328[i].a = 0;
                m328[i].b = -1;
                m328[i].c = -1;
            }
        for (int i = 0; i < 3; i++)
            if (m328[i].a == 0) {
                m328[i].a = m16;
                m328[i].b = (int)f_0903e4();
                m328[i].c = (int)f_090474();
                break;
            }
        if (m328[0].a && m328[1].a && m328[2].a) {
            if (m328[0].b == m328[1].b || m328[0].b == m328[1].c) {
                if (m328[0].b == m328[2].b || m328[0].b == m328[2].c)
                    r = 1;
            } else if (m328[0].c == m328[1].b || m328[0].c == m328[1].c) {
                if (m328[0].c == m328[2].b || m328[0].c == m328[2].c)
                    r = 1;
            }
            int k = 0;
            for (int i = 0; i < 3; i++)
                if (m328[k].a < m328[i].a)
                    k = i;
            m328[k].a = 0;
            m328[k].b = -1;
            m328[k].c = -1;
        }
    }
    return r;
}

/* @implements 0x091bf0 us f_091bf0
   WHAT IT DOES: Drift chance against the nearest rival: while the player drifts at an angle of
   at least 1.5, returns on 20 of every 100 frames below 3, and on every frame from 3 up, a
   value for the drift: -1 or -2 when the player is behind the rival, 1 or 2 when level or
   ahead; otherwise 0. */
int CDjDetect::f_091bf0()
{
    float lo = 1.5f;
    float hi = 3.0f;
    int n = 100;
    if (!f_0903c4()->m1952)
        return 0;
    CCar *c = f_090530();
    if (!c)
        return 0;
    float d = c->m192;
    CCar *p = f_0903c4();
    if (p->m192 < d) {
        if (p->m1964 < lo)
            return 0;
        if (p->m1964 < hi) {
            if (m16 % 100 < 20)
                return -1;
            return 0;
        }
        if (m16 % 100 < n)
            return -2;
        return 0;
    }
    if (p->m1964 < lo)
        return 0;
    if (p->m1964 < hi)
        return m16 % 100 < 20;
    if (m16 % 100 < n)
        return 2;
    return 0;
}

/* @draft 0x091d9c us f_091d9c
   WHAT IT DOES: Boost chance: while the player boosts with a level of at least 1.5, returns 1
   on 20 of every 100 frames below level 3, and 2 from level 3 up; otherwise 0. The 100 held
   in a local is what cse substitutes for the remainder's multiplier (retail's li s1,100).
   Remaining difference: the result lives in a1, not v0: sched1 hoists the level-1.5 return-0
   set above the constant's lui, which local-alloc's update_equiv_regs then puts in v0.
   A result variable for the last two arms (r = ... ? 2 : 0; return r;) is worse (224 B). */
int CDjDetect::f_091d9c()
{
    int n = 100;
    if (!f_0903c4()->m1888)
        return 0;
    float v = f_0903c4()->m1900;
    if (v < 1.5f)
        return 0;
    if (v < 3.0f)
        return m16 % 100 < 20;
    if (m16 % 100 < n)
        return 2;
    return 0;
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

/* @implements 0x0922a0 us f_0922a0
   WHAT IT DOES: Jump check: when the player is in the air (state 1) over a jump the DJ talks
   about, returns 2 for a large jump and 1 for a small one; otherwise 0. */
int CDjDetect::f_0922a0()
{
    int r;
    if (f_0903c4()->m1796 == 1 && f_093c78(D_242c90.sections, f_0903c4()->m1800))
        r = f_093c8c(D_242c90.sections, f_0903c4()->m1800) ? 2 : 1;
    else
        r = 0;
    return r;
}
