/* The normal race overlay object file (retail 0x0897ec to 0x08a144). Fj::CRace2DNormal is the
   race 2D overlay of an ordinary race: it loads the race panel's parts (the "soukou" panel
   package and its pieces, per panel type), creates the movie and subtitle players it shares
   with the movie overlay, steps and draws them with the fade mask, and frees it all. */

#include <string.h>

void f_0451b4(int size);
void f_0f52a4(void *sub, int kind, void *owner);
void f_04b914(void *movie);
void f_04b994(void *movie);
void f_04b9c4(void *movie, void *swg, int *a, int b, int *c);
void f_04bef8(void *movie);
void f_0231c8(void *tex);
int f_0f5a34(void *sub);
void f_0f5ac8(void *sub);
void f_0f5b70(void *sub);
void f_04b724(void *movie);
void f_04b978(void *movie);
void f_04d350(void *movie);
void f_04d3b4(void *movie);
void f_04d548(void *movie);
void f_04d648(void *movie);

namespace Fj {

/* The movie (its own object file). */
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
    int type;
    int m32;
    int m36;
    int m40;
    void *m44[128];
    int m556[128];
    int m1068[128];
    void *m1580;
    CMovie *movie;
    CFadeMask *fade;
    CSubtitle *sub;
};

class CRace2DNormal : public CRace2DBase {
public:
    virtual ~CRace2DNormal() {}
    virtual int f_089464(int a, int b);
    virtual int v3();
    virtual int v4();
    virtual void v5();
    int f_089cd4(int arg);
    int f_08a060(const char *course);
};

}

using namespace Fj;

/* A race panel part: its kind (-1 ends a table), its id and its name in the panel package. */
struct PanelPart {
    int kind;
    int id;
    char name[16];
};
extern PanelPart D_1d3d44[36];
extern PanelPart D_1d40a4[36];
extern PanelPart D_1d43ec[36];

/* The game database's tables (their own object file). */
struct CTable;
extern CTable D_240740;
extern CTable D_2407d0;
char *f_0368e8(CTable *t, const char *field, char *rec, int a, int i);
extern unsigned char D_24063c[];
extern const int D_1a2120;

/* The race being set up (its own object file). */
struct RaceInfo {
    char *m0;
    int m4;
    char *course;
    int m12;
    int kind;
    char m20[48];
    int m68;
    char m72[24];
    char *car;
};
extern RaceInfo *D_2407fc;

/* @draft 0x0897ec us CRace2DNormal8f_089464
   WHAT IT DOES: Starts the overlay: clears the tables, reads the race's kind, panel type,
   course and (for the tour kinds 4 and 5) the tour numbers from the databases, loads the
   panel parts, creates and starts the movie (-1 when that fails) with the panel package when
   there is one, and the subtitle player (by race kind). Returns 1 (0 when the parts fail).
   Remaining difference: the database copy size, the copy buffer's address and its high half
   take saved registers s5, s1, s4 here against s1, s4, s5 in retail; the string pool also
   needs the panel loader's strings (f_089cd4) ahead of the course names. */
int CRace2DNormal::f_089464(int a, int b)
{
    CRace2DBase::f_089464(a, b);
    f_0451b4(0x200000);
    for (int i = 0; i < 128; i++) {
        m44[i] = 0;
        m556[i] = 0;
        m1068[i] = 0;
    }
    m12 = 4;
    m8 = 1;
    m36 = a;
    type = 0;
    m32 = 0;
    m16 = 0;
    m20 = 0;
    if (D_2407fc) {
        m8 = D_2407fc->kind;
        char *f = f_0368e8(&D_240740, "PanelType", D_2407fc->car, 0, 0);
        memcpy(D_24063c, f, D_1a2120);
        type = D_24063c[0];
        char *c = D_2407fc->course;
        if (c)
            m32 = f_08a060(c);
        if (m8 == 4 || m8 == 5) {
            f = f_0368e8(&D_2407d0, "TourNum", D_2407fc->m0, 0, 0);
            memcpy(D_24063c, f, D_1a2120);
            int n = D_24063c[0];
            m16 = n;
            f = f_0368e8(&D_2407d0, "TourExtra", D_2407fc->m0, 0, 0);
            memcpy(D_24063c, f, D_1a2120);
            n = D_24063c[0];
            if (n < 2) {
                f = f_0368e8(&D_2407d0, "TourSubNum", D_2407fc->m0, 0, 0);
                memcpy(D_24063c, f, D_1a2120);
                n = D_24063c[0];
            } else
                n = 0;
            m20 = n;
            m12 = D_2407fc->m68;
        }
    }
    if (f_089cd4(b))
        return 0;
    movie = new CMovie;
    if (!movie)
        return -1;
    f_04b994(movie);
    if (m1580) {
        f_04b9c4(movie, m1580, m1068, 0, m556);
        f_04bef8(movie);
    }
    sub = new CSubtitle;
    if (sub) {
        if (m8 == 1)
            f_0f52a4(sub, 0, this);
        else if (m8 == 2)
            f_0f52a4(sub, 1, this);
        else if (m8 == 3)
            f_0f52a4(sub, 2, this);
        else
            f_0f52a4(sub, 3, this);
    }
    return 1;
}

/* @implements 0x089ad0 us CRace2DNormal2v3
   WHAT IT DOES: Ends the overlay: frees the subtitle player, stops the movie, frees the panel
   parts the overlay loaded (kind 0 in the panel type's table), then frees the movie.
   Returns 1. */
int CRace2DNormal::v3()
{
    if (sub) {
        f_0f5a34(sub);
        if (sub)
            delete sub;
        sub = 0;
    }
    if (movie) {
        f_04b724(movie);
        f_04d648(movie);
    }
    for (int i = 0; i < 36; i++) {
        int kind;
        if (type == 20)
            kind = D_1d40a4[i].kind;
        else if (type == 21)
            kind = D_1d43ec[i].kind;
        else
            kind = D_1d3d44[i].kind;
        if (m44[i]) {
            if (!kind)
                f_0231c8(m44[i]);
            m44[i] = 0;
        }
    }
    if (movie) {
        delete movie;
        movie = 0;
    }
    m1580 = 0;
    return 1;
}

/* @implements 0x089c30 us CRace2DNormal2v4
   WHAT IT DOES: Steps the subtitles and the fade. Returns 0. */
int CRace2DNormal::v4()
{
    if (sub)
        f_0f5ac8(sub);
    fade->f_089548();
    return 0;
}

/* @implements 0x089c78 us CRace2DNormal2v5
   WHAT IT DOES: Draws the movie, the subtitles, the movie's overlay and the fade mask. */
void CRace2DNormal::v5()
{
    f_04d350(movie);
    if (sub)
        f_0f5b70(sub);
    f_04d3b4(movie);
    f_04d548(movie);
    fade->f_0895cc();
}

/* @implements 0x08a060 us f_08a060
   WHAT IT DOES: Returns the index of a course name (0 to 24) in the course list, or 0 when it
   is not there. */
int CRace2DNormal::f_08a060(const char *course)
{
    const char *names[25] = {
        "Mountain_N", "Mountain_R", "Advanced_N", "Advanced_R", "OverPassCity_N",
        "OverPassCity_R", "HeavenAndHell_N", "HeavenAndHell_R", "Short_N", "Short_R",
        "City_N", "City_R", "Plateau_N", "Plateau_R", "Novice_N", "Novice_R",
        "LakeSideGate_N", "LakeSideGate_R", "WonderHill_N", "WonderHill_R", "Long_N",
        "Long_R", "Town_N", "Town_R", "Test_Course",
    };
    for (int i = 0; i < 25; i++) {
        if (strcmp(course, names[i]) == 0)
            return i;
    }
    return 0;
}

/* @implements 0x08a10c us _ZN2Fj13CRace2DNormalD1Ev
   WHAT IT DOES: The overlay destructor (resets the vtable to the base one). */

/* @implements 0x08a11c us _ZN2Fj13CRace2DNormalD0Ev
   WHAT IT DOES: The overlay deleting destructor. */
