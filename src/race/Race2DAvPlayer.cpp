/* The movie player race overlay object file (retail 0x08a144 to 0x08a3c0). Fj::CRace2DAvPlayer
   is the race 2D overlay used while a movie plays: it creates the movie and its subtitle
   player, steps and draws them with the fade mask, and frees them. */

void f_0451b4(int size);
void f_0f52a4(void *sub, int kind, void *owner);
int f_0f5a34(void *sub);
void f_0f5ac8(void *sub);
void f_0f5b70(void *sub);
void f_04b914(void *movie);
void f_04b978(void *movie);
void f_04b994(void *movie);
void f_04d350(void *movie);
void f_04d3b4(void *movie);
void f_04d648(void *movie);

namespace Fj {

/* The movie (its own object file): constructed by f_04b914, which may throw. */
struct CMovie {
    CMovie() { f_04b914(this); }
    ~CMovie() { f_04b978(this); }
    char m0[56];
};

/* The subtitle player (its own object file). */
struct CSubtitle {
    CSubtitle()
    {
        m128 = 0;
        m132 = 0;
    }
    char m0[128];
    int m128;
    int m132;
    char m136[20];
};

class CFadeMask {
public:
    virtual ~CFadeMask() {}
    int f_089548();
    void f_0895cc();
};

class CRace2DBase {
public:
    virtual ~CRace2DBase() {}
    virtual int f_089464(int a, int b);
    virtual int v3() = 0;
    virtual int v4() = 0;
    virtual void v5() = 0;

    int mode;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44[128];
    int m556[128];
    int m1068[128];
    int m1580;
    CMovie *movie;
    CFadeMask *fade;
    CSubtitle *sub;
};

class CRace2DAvPlayer : public CRace2DBase {
public:
    virtual ~CRace2DAvPlayer() {}
    virtual int f_089464(int a, int b);
    virtual int v3();
    virtual int v4();
    virtual void v5();
    int m1596;
};

}

using namespace Fj;

/* @implements 0x08a144 us CRace2DAvPlayer8f_089464
   WHAT IT DOES: Starts the overlay: clears the tables, creates and starts the movie (-1 when
   that fails) and the subtitle player (kind 4 for mode 2, else 5). Returns 1. */
int CRace2DAvPlayer::f_089464(int a, int b)
{
    CRace2DBase::f_089464(a, b);
    f_0451b4(0x200000);
    for (int i = 0; i < 128; i++) {
        m44[i] = 0;
        m556[i] = 0;
        m1068[i] = 0;
    }
    m12 = 4;
    m36 = a;
    m8 = 1;
    m28 = 0;
    m32 = 0;
    m16 = 0;
    m20 = 0;
    m1580 = 0;
    movie = new CMovie;
    if (!movie)
        return -1;
    f_04b994(movie);
    sub = new CSubtitle;
    if (sub) {
        if (mode == 2)
            f_0f52a4(sub, 4, this);
        else
            f_0f52a4(sub, 5, this);
    }
    return 1;
}

/* @implements 0x08a244 us CRace2DAvPlayer2v3
   WHAT IT DOES: Ends the overlay: frees the subtitle player and the movie. Returns 1. */
int CRace2DAvPlayer::v3()
{
    if (sub) {
        f_0f5a34(sub);
        if (sub)
            delete sub;
        sub = 0;
    }
    if (movie) {
        f_04d648(movie);
        delete movie;
        movie = 0;
    }
    m1580 = 0;
    return 1;
}

/* @implements 0x08a2ec us CRace2DAvPlayer2v4
   WHAT IT DOES: Steps the subtitles and the fade. Returns 0. */
int CRace2DAvPlayer::v4()
{
    if (sub)
        f_0f5ac8(sub);
    fade->f_089548();
    return 0;
}

/* @implements 0x08a334 us CRace2DAvPlayer2v5
   WHAT IT DOES: Draws the movie, the subtitles and the fade mask. */
void CRace2DAvPlayer::v5()
{
    f_04d350(movie);
    if (sub)
        f_0f5b70(sub);
    f_04d3b4(movie);
    fade->f_0895cc();
}

/* @implements 0x08a388 us _ZN2Fj15CRace2DAvPlayerD1Ev
   WHAT IT DOES: The overlay destructor (resets the vtable to the base one). */

/* @implements 0x08a398 us _ZN2Fj15CRace2DAvPlayerD0Ev
   WHAT IT DOES: The overlay deleting destructor. */
