/* The time attack race information object file (retail 0x0eede0 to 0x0f088c,
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
void f_037d50(void *);
void f_037f48(void *);
int f_094254(void *);
}
extern char D_242c90[];
extern int D_27eccc;

/* @implements 0x0eede0 us f_0eede0
   WHAT IT DOES: Converts a sector distance into a time: zero when count is not positive,
   otherwise x * 10800 * n / count * 1.024. */
extern "C" float f_0eede0(int count, int n, float x)
{
    if (count <= 0)
        return 0;
    return x * 10800.0f * n / count * 1.024f;
}

/* The race information record shared by the sequences. */
struct RaceLaps;
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
    int m60[6];
    int m84;
    int m88[4];
    int m104;
    int m108[6];
    int m132;  /* laps done */
    int m136[16];
    RaceLaps *m200;
    int m204[4];
    int m220;
};
extern RaceInfo *D_2408f0;

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
    char m128[6136];
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
