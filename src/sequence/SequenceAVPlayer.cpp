/* The movie player sequence object file (retail 0x041a74 to 0x041d34,
   "RacePSP::CSequenceAVPlayer"). The sequence that plays a movie: it stops the music, fades the
   sound out and runs one state until the movie's fade has reached its end, then returns to the
   idle state. */

extern "C" {
void f_096368(void *bgm, struct Rec r);
void f_096048(void *);
void f_089438(int);
void f_0894b0(void *snd, int ms);
void f_089500(void *snd, int ms);
}
extern char D_242cb0[];
extern char D_242ca8[];

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};

/* The sound system. */
class CSound {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int a, int b);
    virtual void v3(int a);
    virtual void v4();
    virtual void v5();
};
extern CSound *D_1d3d40;

namespace RacePSP {
class CSequenceBase;
typedef int (CSequenceBase::*Handler)();

/* The base of every sequence (made by its own object file). */
class CSequenceBase {
public:
    CSequenceBase();
    virtual ~CSequenceBase();
    virtual void f_038fd4(int arg);
    virtual int f_038fdc();
    virtual void f_038fe4();
    int f_03959c();
    int f_039588();
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    void *m32;
    void *m36;
    void *m40;
    int m44;
    int m48;
    int m52;
    int state;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
};

class CSequenceStandard : public CSequenceBase {
public:
    CSequenceStandard() {}
    virtual ~CSequenceStandard() {}
};

class CSequenceAVPlayer : public CSequenceStandard {
public:
    CSequenceAVPlayer();
    virtual ~CSequenceAVPlayer();
    virtual int f_038fdc();
    virtual void f_038fe4();
    int f_041b5c();
    int f_041c78();
    int fade;
};
}

using namespace RacePSP;

extern Handler D_1d1c94[];

/* @implements 0x041a74 us _ZN7RacePSP17CSequenceAVPlayerC2Ev
   WHAT IT DOES: builds the sequence on its base. */
CSequenceAVPlayer::CSequenceAVPlayer()
{
}

/* @implements 0x041aa4 us _ZN7RacePSP17CSequenceAVPlayerC1Ev
   WHAT IT DOES: the complete-object copy of the constructor above. */

/* @implements 0x041ad4 us _ZN7RacePSP17CSequenceAVPlayerD2Ev
   WHAT IT DOES: tears the sequence down through its base. */
CSequenceAVPlayer::~CSequenceAVPlayer()
{
}

/* @implements 0x041afc us _ZN7RacePSP17CSequenceAVPlayerD1Ev
   WHAT IT DOES: the complete-object copy of the destructor above. */

/* @implements 0x041b24 us _ZN7RacePSP17CSequenceAVPlayerD0Ev
   WHAT IT DOES: the deleting destructor. */

/* @implements 0x041b5c us f_041b5c
   WHAT IT DOES: starts the movie: the fade counter at -9000, the play state, the flag at +24
   cleared; stops the music, mutes the sound and starts a 3 second sound fade. */
int CSequenceAVPlayer::f_041b5c()
{
    state = 1;
    fade = -9000;
    m24 = 0;
    Rec r;
    r.rec = 0;
    f_096368(D_242cb0, r);
    f_089438(2);
    D_1d3d40->v2(0, 0);
    f_0894b0(D_1d3d40, 3000);
}

/* @implements 0x041bd4 us CSequenceAVPlayer8f_038fdc
   WHAT IT DOES: runs the handler of the current state. */
int CSequenceAVPlayer::f_038fdc()
{
    return (this->*D_1d1c94[state])();
}

/* @implements 0x041c4c us CSequenceAVPlayer8f_038fe4
   WHAT IT DOES: ends the sequence by telling the sound system. */
void CSequenceAVPlayer::f_038fe4()
{
    D_1d3d40->v3(0);
}

/* @implements 0x041c78 us f_041c78
   WHAT IT DOES: the play state: advances the fade, starts it once the movie has ended, updates
   the menu music and the sound, and goes idle when the fade is complete. */
int CSequenceAVPlayer::f_041c78()
{
    if (fade)
        fade += 50;
    if (f_03959c() && fade == 0) {
        fade = 50;
        f_089500(D_1d3d40, 3000);
    }
    f_096048(D_242ca8);
    D_1d3d40->v4();
    D_1d3d40->v5();
    if (fade >= 9000)
        state = 0;
    return 0;
}
