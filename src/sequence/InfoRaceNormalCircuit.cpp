/* The normal circuit race information object file (retail 0x03e364 to 0x03fe80,
   "RacePSP::CInfoRaceNormalCircuit"). The information side of a normal circuit race: a state
   machine (countdown, race, final lap, finish, result and replay states) stepped once a frame,
   which keeps the shared race information record up to date and decides when the race, the
   replay and the camera changes happen. */

extern "C" {
void f_0ede54(void *);
void f_0edec0(void *);
int f_0ee6b8(void *);
void f_0ee788(void *);
void f_037f48(void *);
int f_094254(void *);
}
extern char D_242c90[];
extern int D_27eccc;

/* The race information record shared by the sequences. */
struct RaceInfo {
    int m0[8];
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int m52;
    int m56;
    int m60[11];
    int m104;
    int m108[28];
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
};

/* The race camera director (made and destroyed by its own object file). */
struct CDirector {
    CDirector() { f_0ede54(this); }
    ~CDirector() { f_0edec0(this); }
    int f_0ee6b8() { return ::f_0ee6b8(this); }
    void f_0ee788() { ::f_0ee788(this); }
    char m0[4];
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

class CInfoRaceNormalCircuit;
typedef int (CInfoRaceNormalCircuit::*InfoHandler)();

class CInfoRaceNormalCircuit : public CInfoBase {
public:
    CInfoRaceNormalCircuit();
    virtual ~CInfoRaceNormalCircuit();
    virtual int f_038a54();
    virtual void f_038a64();
    virtual void f_038a78();
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
    void *m80;
    int m84;
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
