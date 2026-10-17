/* The time attack race information object file (retail 0x0eee20 to 0x0f088c,
   "RacePSP::CInfoTimeAttack"). The information side of a time attack race: it reads the
   race setup (the sequence and course numbers, the car's engine and the course's sectors),
   then steps a state machine once a frame (countdown, race, final lap, finish, result and
   replay states) which keeps the shared race information record and the race result up to
   date, times the sectors and the laps, and decides when the race and the replay end. It
   owns a ranking checker (src/race/CheckRanking.cpp). */

extern "C" {
void f_0ede54(void *);
void f_0edec0(void *);
void f_0ee584(void *);
void f_0ee624(void *);
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

/* The race information record shared by the sequences. */
struct RaceLaps;
struct InfoCar;
struct RaceInfo {
    int m0[6];
    int m24;   /* laps of the race */
    int m28;
    int m32;   /* laps to go */
    int m36;
    int m40;
    int m44;
    int m48;   /* race clock */
    int m52;
    int m56;   /* race phase */
    int m60[4];
    int m76;   /* the course record */
    int m80;   /* a new record was set */
    int m84;
    int m88[4];
    int m104;
    int m108;  /* the player's laps */
    int m112;  /* the player's place */
    int m116;  /* lap clock */
    int m120;  /* last lap time */
    int m124;  /* best lap time */
    int m128;  /* best lap */
    int m132;  /* race time */
    int m136;  /* finishing time */
    int m140[15];
    RaceLaps *m200;
    int m204[4];
    int m220;
};
extern RaceInfo *D_2408f0;
extern RaceInfo *D_2407fc;

/* The race's lap timing block: the player's sector times per lap (cumulative within the
   lap), then the best times by lap and sector (see src/race/CheckRanking.cpp). */
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

/* The time attack settings (made elsewhere). */
struct TimeAttackSetup {
    int m0[2];
    int m8;
};
extern TimeAttackSetup D_23f7f0;

/* The game's settings that pause the race. */
struct GameFlags {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern GameFlags *D_1d88a0;

/* The player's car as the information reads it. */
struct InfoCar {
    char m0[124];
    int m124;
    char m128[2000];
    char m2128[84];  /* the course position tracker */
    int m2212;       /* laps done */
    char m2216[4048];
    int m6264;
};

/* The race display flags object (made elsewhere). */
struct InfoView {
    char m0[76];
    int m76;
    char m80[48];
    int m128;
};

/* The ranking checker (src/race/CheckRanking.cpp), made and destroyed with the
   information. */
struct CDirector {
    CDirector() { f_0ede54(this); }
    ~CDirector() { f_0edec0(this); }
    void f_0ee584() { ::f_0ee584(this); }
    void f_0ee624() { ::f_0ee624(this); }
    void f_0ee788() { ::f_0ee788(this); }
    void f_0ee76c() { ::f_0ee76c(this); }
    void f_0ee1d8(int from) { ::f_0ee1d8(this, from); }
    int f_0ee66c() { return ::f_0ee66c(this); }
    void f_0ee704(int t, int t2) { ::f_0ee704(this, t, t2); }
    char m0[36];
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
    void f_038a80(int);
    int m4[4];
    unsigned int m20;
};

class CInfoTimeAttack;
typedef int (CInfoTimeAttack::*InfoHandler)();

class CInfoTimeAttack : public CInfoBase {
public:
    CInfoTimeAttack();
    virtual ~CInfoTimeAttack();
    virtual int f_038a54();
    virtual void f_038a64();
    virtual void f_038a78();
    int f_0efcc8();
    int f_0efd5c();
    int f_0efe5c();
    int f_0eff00();
    int f_0effd0();
    int f_0f006c();
    int f_0f0108();
    void f_0f013c();
    void f_0f0638();

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
    void *m80;
    void *m84;
    int state;
    InfoCar *car;
    InfoView *view;
    int m100;
    int m104;
    int m108;
    CDirector director;
    int m148;
    int m152;
    float m156;
    float m160;
};
}

using namespace RacePSP;

extern InfoHandler D_1d5a98[];

/* @implements 0x0eee20 us _ZN7RacePSP15CInfoTimeAttackC2Ev
   WHAT IT DOES: builds the information on its base and makes its ranking checker. */
CInfoTimeAttack::CInfoTimeAttack()
{
}

/* @implements 0x0eee74 us _ZN7RacePSP15CInfoTimeAttackC1Ev
   WHAT IT DOES: the complete-object copy of the constructor above. */

/* @implements 0x0eeec8 us _ZN7RacePSP15CInfoTimeAttackD2Ev
   WHAT IT DOES: destroys the ranking checker, then the base. */
CInfoTimeAttack::~CInfoTimeAttack()
{
}

/* @implements 0x0eef20 us _ZN7RacePSP15CInfoTimeAttackD1Ev
   WHAT IT DOES: the complete-object copy of the destructor above. */

/* @implements 0x0eef78 us _ZN7RacePSP15CInfoTimeAttackD0Ev
   WHAT IT DOES: the deleting destructor. */

/* @implements 0x0ef790 us CInfoTimeAttack8f_038a54
   WHAT IT DOES: the per frame step. Does nothing while the game is paused; otherwise runs the
   current state's handler, counts the frame and raises the flags whose frame has come: the
   end (returned) and the two timed events at +40 and +48. Outside the replay, when the
   pending display change's frame comes, clears it and switches the display flags. */
int CInfoTimeAttack::f_038a54()
{
    GameFlags *g = D_1d88a0;
    if (g->m11 || g->m12)
        return 0;
    if (m72 == 1)
        m72 = 2;
    int r = (this->*D_1d5a98[state])();
    int f = ++m4[3];
    if (f == m100)
        r = 1;
    if (f == m44)
        m40 = 1;
    if (m4[3] == m60)
        m48 = 1;
    if (m32 >= 0 && m152 && m4[3] == m156) {
        m152 = 0;
        view->m128 = 1;
        view->m76 = 0;
    }
    return r;
}

/* @implements 0x0ef8e0 us CInfoTimeAttack8f_038a64
   WHAT IT DOES: the end of the race: outside the replay writes the ranking into the race
   result, frees the ranking checker and the objects at +80 and +84, and, outside the replay,
   notes the frame the race ended on and fills the race result: the final phase, the winning
   time, each lap's time from the player's sector times (sectors 2 or 3 a lap; -1 for a lap
   not timed), each lap's time converted for display and, when the race was not completed,
   the player's sector times (-1 elsewhere). */
void CInfoTimeAttack::f_038a64()
{
    if (m24 == 0)
        director.f_0ee584();
    director.f_0ee624();
    if (m80)
        f_037d50(m80);
    if (m84)
        f_037d50(m84);
    if (m24)
        return;
    if (m28 < 0)
        m28 = m4[3];
    RaceInfo *ri = D_2408f0;
    RaceResult *r = &D_240800;
    D_240800.m0 = ri->m56;
    if (r->time[1] > 0)
        r->time[0] = r->time[1];
    r->best[2] = r->best[1] = r->best[0] = -1;
    r->me = 0;
    RaceLaps *l = ri->m200;
    if (l->m2404 == 2) {
        if (l->m0[0][0] >= 0 && l->m0[0][1] >= 0) {
            r->best[0] = l->m0[0][1];
            if (l->m0[1][0] >= 0 && l->m0[1][1] >= 0) {
                r->best[1] = l->m0[1][1] - l->m0[0][1];
                if (l->m0[2][0] >= 0 && l->m0[2][1] >= 0)
                    r->best[2] = l->m0[2][1] - l->m0[1][1];
            }
        }
    } else if (l->m2404 == 3) {
        if (l->m0[0][0] >= 0 && l->m0[0][1] >= 0 && l->m0[0][2] >= 0) {
            r->best[0] = l->m0[0][2];
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
                D_240800.rec[i].v[j] = D_2408f0->m200->m0[i][j];
    }
}

/* @implements 0x0efc08 us CInfoTimeAttack8f_038a78
   WHAT IT DOES: the per frame display step: clears the display flags whose condition is over
   and passes the objects at +80 and +84 on to their handler when their flags are set. */
void CInfoTimeAttack::f_038a78()
{
    RaceInfo *ri = D_2408f0;
    if (ri->m84 && m32 >= 0 && m152 && ri->m48 >= 0)
        view->m128 = 0;
    if (!m24 && m32 >= 0 && !m152)
        view->m76 = 0;
    if (m148)
        f_037f48(m80);
    if (m152)
        f_037f48(m84);
}

/* @implements 0x0efcc8 us f_0efcc8
   WHAT IT DOES: the countdown state: records the car, advances the race clock and, once the
   countdown is over, starts the race (state 1, race phase 5) and schedules the first timed
   event two seconds on. */
int CInfoTimeAttack::f_0efcc8()
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

/* @implements 0x0efd5c us f_0efd5c
   WHAT IT DOES: the race state: steps the race; when the laps are done goes to the finish
   (state 5, phase 3) for two seconds; when the car's time has run past the limit at +160,
   goes straight to the result (state 6, phase 7) and schedules the end; advances the race
   clock. */
int CInfoTimeAttack::f_0efd5c()
{
    if (m24 == 0)
        m36 = 1;
    f_0f0638();
    RaceInfo *ri = D_2408f0;
    if (ri->m32 <= 0) {
        ri->m56 = 3;
        D_27eccc = 3;
        car->m124 = 3;
        state = 5;
        m104 = 120;
        m36 = 0;
    }
    if (car->m6264 * 0.009765f < m160) {
        ri->m56 = 7;
        D_27eccc = 7;
        car->m124 = 5;
        state = 6;
        m72 = 1;
        if (m24 == 0) {
            m100 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    D_2408f0->m104 = car->m124;
    D_2408f0->m48 += 50;
    return 0;
}

/* @implements 0x0efe5c us f_0efe5c
   WHAT IT DOES: the final lap state: as the race state through the other step, unless the
   car's finish is of kind 2; then goes to state 4. */
int CInfoTimeAttack::f_0efe5c()
{
    if (m24 == 0)
        m36 = 1;
    f_0f013c();
    RaceInfo *ri = D_2408f0;
    if (ri->m32 <= 0 && m108 != 2) {
        ri->m56 = 3;
        D_27eccc = 3;
        car->m124 = 3;
        state = 4;
        m104 = 120;
        m36 = 0;
    }
    D_2408f0->m104 = car->m124;
    D_2408f0->m48 += 50;
    return 0;
}

/* @implements 0x0eff00 us f_0eff00
   WHAT IT DOES: the result state: steps the ranking checker, records the car, advances the
   race clock and, outside the replay, schedules the end once the music allows (or after
   eight seconds). */
int CInfoTimeAttack::f_0eff00()
{
    director.f_0ee788();
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    D_2408f0->m48 += 50;
    m108 = 0;
    if (m24 == 0 && m100 < 0) {
        if (f_094254(D_242c90) == 1) {
            m100 = m4[3] + 120;
            m60 = m4[3] + 60;
        } else if (m28 + 480 < m4[3]) {
            m100 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    return 0;
}

/* @implements 0x0effd0 us f_0effd0
   WHAT IT DOES: the finish state after the final lap step: when its two seconds are up (and
   the finish is not of kind 2) goes to the result (state 6, phase 4) and schedules the end. */
int CInfoTimeAttack::f_0effd0()
{
    f_0f013c();
    if (--m104 == 0 && m108 != 2) {
        D_2408f0->m56 = 4;
        state = 6;
        m72 = 1;
        if (m24 == 0) {
            m100 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    int c = car->m124;
    D_2408f0->m104 = c;
    D_2408f0->m48 += 50;
    return 0;
}

/* @implements 0x0f006c us f_0f006c
   WHAT IT DOES: the same finish state after the race step. */
int CInfoTimeAttack::f_0f006c()
{
    f_0f0638();
    if (--m104 == 0 && m108 != 2) {
        D_2408f0->m56 = 4;
        state = 6;
        m72 = 1;
        if (m24 == 0) {
            m100 = m4[3] + 120;
            m60 = m4[3] + 60;
        }
    }
    int c = car->m124;
    D_2408f0->m104 = c;
    D_2408f0->m48 += 50;
    return 0;
}

/* @implements 0x0f0108 us f_0f0108
   WHAT IT DOES: the replay state: records the car. */
int CInfoTimeAttack::f_0f0108()
{
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    return 0;
}

/* @draft 0x0f013c us f_0f013c
   WHAT IT DOES: the race step of the final laps: records the car, steps the ranking, then asks
   the car's position tracker how far it is from the line. A car that reaches a new lap is
   noted (kind 1, or 2 when it is the race's last). Kind 1 closes the lap: its time, the
   player's lap and sector table, and the lap clock restarts. Kind 2 finishes the race: the
   lap, race and finishing times, the finish phase (state 3), the course record check outside
   the replay, the end schedule, the last sector time and the ranking's finish. Otherwise
   kind 0 times the player's sector ends. Then the best lap, the ranking sort and the player's
   place, every other car's sector and lap times, and the race clock.
   Remaining difference: allocation. Retail loads each race clock for the tracker call into a3
   and builds clock % 3 in t0 (the fifth argument) from the sign onwards; here the clock goes
   to t0 and the quotient to other registers, which shifts the registers of every tracker call
   (a separate local for the remainder only moves it to a2/a3/t0). The control flow matches. */
void CInfoTimeAttack::f_0f013c()
{
    f_038a80(0);
    director.f_0ee76c();
    float at = 0;
    int clk = D_2408f0->m116;
    int r = f_0a8d5c(car->m2128, &at, 50, 3, clk % 3);
    if (r < -2) {
        m108 = 0;
    } else {
        InfoCar *c = car;
        RaceInfo *ri = D_2408f0;
        int laps = c->m2212;
        if (ri->m108 < laps) {
            ri->m108 = laps;
            if (laps == ri->m36)
                m108 = 2;
            else
                m108 = 1;
        } else {
            m108 = 0;
        }
    }
    RaceInfo *ri = D_2408f0;
    RaceLaps *l = ri->m200;
    int sec = l->m2376;
    int lap = l->m2384;
    float end = l->m2392[sec];
    switch (m108) {
    case 0: {
        float at2 = end;
        int clk2 = ri->m132;
        int r2 = f_0a8d5c(car->m2128, &at2, 50, 3, clk2 % 3);
        if (r2 >= -2 && car->m2212 == lap) {
            RaceLaps *l2 = D_2408f0->m200;
            if (sec != l2->m2404 - 1) {
                l2->m0[lap][sec] = D_2408f0->m132 + r2;
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
        l->m0[lap][sec] = ri->m132 + r;
        l->m2384++;
        l->m2376 = 0;
        ri->m132 += 50;
        break;
    case 2:
        ri->m120 = ri->m116 += r;
        ri->m132 += r;
        ri->m136 = ri->m48 + r;
        car->m124 = 1;
        ri->m56 = 2;
        D_27eccc = 2;
        state = 3;
        if (m24 == 0) {
            if (m28 < 0)
                m28 = m4[3] + 120;
            if (m100 < 0) {
                if (f_094254(D_242c90) == 1) {
                    m100 = m4[3] + 120;
                    m60 = m4[3] + 60;
                } else if (m28 + 480 < m4[3]) {
                    m100 = m4[3] + 120;
                    m60 = m4[3] + 60;
                }
            }
            if (m32 < 0 || D_2408f0->m132 < D_2408f0->m76) {
                D_2408f0->m80 = 1;
                D_2408f0->m76 = D_2408f0->m132;
            } else {
                D_2408f0->m80 = 0;
            }
        }
        {
            RaceInfo *q = D_2408f0;
            q->m200->m0[lap][sec] = q->m132;
            q->m200->m2384++;
            q->m200->m2376 = 0;
            director.f_0ee704(q->m136, q->m132);
        }
        m36 = 0;
        break;
    }
    if (m108) {
        RaceInfo *q = D_2408f0;
        if (q->m120 < q->m124) {
            q->m124 = q->m120;
            q->m128 = q->m108 - 1;
        }
    }
    director.f_0ee1d8(0);
    RaceInfo *q = D_2408f0;
    q->m112 = director.f_0ee66c();
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
        int r3 = f_0a8d5c(c->m2128, &at3, 50, 3, clk3 % 3);
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
    D_2408f0->m32 -= 50;
}

/* @draft 0x0f0638 us f_0f0638
   WHAT IT DOES: the race step before the final laps: records the car, steps the ranking and,
   once the car has crossed the line onto its first lap, starts the lap clock and the race
   time and goes to the race state (state 2, phase 1). Then the ranking sort and the player's
   place, every other car's sector and lap times, and the race clock.
   Remaining difference: the same clock % 3 register choice as 0x0f013c; otherwise the code
   matches word for word. */
void CInfoTimeAttack::f_0f0638()
{
    f_038a80(0);
    director.f_0ee76c();
    float at = 0;
    int clk = D_2408f0->m116;
    int r = f_0a8d5c(car->m2128, &at, 50, 3, clk % 3);
    if (r < -2) {
        m108 = 0;
    } else {
        InfoCar *c = car;
        if (c->m2212 < 0) {
            m108 = 0;
        } else {
            m108 = 1;
            D_2408f0->m108 = c->m2212;
        }
    }
    if (m108) {
        RaceInfo *ri = D_2408f0;
        ri->m132 = ri->m116 = 50 - r;
        state = 2;
        ri->m56 = 1;
        D_27eccc = 1;
    }
    director.f_0ee1d8(0);
    RaceInfo *ri = D_2408f0;
    ri->m112 = director.f_0ee66c();
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
        int r3 = f_0a8d5c(c->m2128, &at3, 50, 3, clk3 % 3);
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
    D_2408f0->m32 -= 50;
}
