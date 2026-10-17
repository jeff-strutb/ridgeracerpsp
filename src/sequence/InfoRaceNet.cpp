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
float f_0eede0(int count, int n, float x);
void f_0ede54(void *);
void f_0edec0(void *);
int f_0ee6b8(void *);
void f_0ee788(void *);
void f_037f48(void *);
int f_094254(void *);
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

/* The race's lap timing block (see src/sequence/InfoTimeAttack.cpp). */
struct RaceLaps {
    int m0[99][3];
    char m1188[1216];
    int m2404;  /* sectors per lap */
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
extern char D_241760[];

/* @implements 0x0f088c us f_0f088c
   WHAT IT DOES: The sort comparator of two ints (ascending): *a - *b. (Its user, 0x0f178c, is
   not transcribed yet, so it is kept external here to be emitted.) */
extern "C" int f_0f088c(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

/* The race information record shared by the sequences. */
struct RaceLaps;
struct RaceInfo {
    int m0[6];
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int m52;
    int m56;
    int m60[11];
    int m104;
    int m108;   /* the player's laps */
    int m112;   /* the player's place */
    int m116[4];
    int m132;   /* race time */
    int m136;   /* finishing time */
    int m140;
    float m144;
    int m148[13];
    RaceLaps *m200;
    int m204[4];
    int m220;
};
extern RaceInfo *D_2408f0;
extern RaceInfo *D_2407fc;

/* A member of the network session (40 bytes). */
struct NetMember {
    char m0[9];
    char m9;
    char m10;
    char m11[17];
    int m28;    /* finishing time (-2 none yet, -1 retired) */
    int m32;
    float m36;
};

/* The network session (src/system/NetSession.cpp). */
struct NetState {
    char m0[9];
    signed char m9;
    char m10[74];
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
    int f_086c50();
};
extern CNetSession D_241810;

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

/* The ranking checker (src/race/CheckRanking.cpp), made and destroyed with the
   information. */
struct CDirector {
    CDirector() { f_0ede54(this); }
    ~CDirector() { f_0edec0(this); }
    int f_0ee6b8() { return ::f_0ee6b8(this); }
    void f_0ee788() { ::f_0ee788(this); }
    void f_0ee584() { ::f_0ee584(this); }
    void f_0ee624() { ::f_0ee624(this); }
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

class CInfoRaceNet;
typedef int (CInfoRaceNet::*InfoHandler)();

class CInfoRaceNet : public CInfoBase {
public:
    CInfoRaceNet();
    virtual ~CInfoRaceNet();
    void f_0f0a54();
    virtual int f_038a54();
    virtual void f_038a64();
    void f_0f0aa8();
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
    void *m80;
    int m84;
    int state;
    InfoCar *car;
    int m96;
    int m100;
    int m104;
    CDirector director;
    int m144[4];
    int m160;
};
}

using namespace RacePSP;

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
void CInfoRaceNet::f_0f0a54()
{
    f_0f0aa8();
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
    f_082f38(D_241760);
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
   register. The control flow and the stores match. */
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
   same residue as the normal circuit information's replay state). */
int CInfoRaceNet::f_0f1f78()
{
    D_2408f0->m220 = director.f_0ee6b8();
    D_2408f0->m104 = car->m124;
    f_038a80(0);
    return 0;
}
