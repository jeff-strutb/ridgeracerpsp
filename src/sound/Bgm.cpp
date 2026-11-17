/* The background music object file (retail 0x0961e0 to 0x096e18, Stream::CBgm). The game's
   music stream: it takes the course's music number from the course database, turns a menu
   number into a music track (the "random" entries pick a track of their group), starts the
   music for a race, a replay or the music player, fades it out, pauses and resumes it, and
   pauses it while the disc is out and restarts it when the disc is back. The one music
   stream is a global object built at start up. */

#include <string.h>

void f_093f90(const char *fmt, ...);
int f_0f6b90(void);     /* the random number */

extern "C" {
int f_111b0c(void);     /* 1 while the disc is out */
}

/* A pair of values the settings hand back by value. */
struct Pair {
    char *a;
    int b;
};

/* The sequence manager, as far as its settings and current race are concerned. */
struct CSequence {
    Pair f_0031dc(int i);
    int m0[69];
    Pair seq;           /* the current race's record */
};
extern CSequence D_1dd6b0;

namespace DB {
class CDataBase {
public:
    CDataBase();
    virtual ~CDataBase();
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
    int m4[9];
};
}
extern DB::CDataBase D_240740;  /* the cars */
extern DB::CDataBase D_2407a8;  /* the courses */
extern DB::CDataBase D_2407d0;  /* the races */

extern unsigned char D_24063c[];
extern const int D_1a211c[2];   /* the database field sizes */
extern const int D_1a2120;      /* the same, second entry */
extern int D_240910;            /* the number of computer cars */

/* A computer car's settings. */
static inline Pair GetS(int i)
{
    Pair r = D_1dd6b0.f_0031dc(i);
    return r;
}

/* Whether a race record has the given sequence number. */
static inline bool IsSequence(const Pair &r, int n)
{
    memcpy(D_24063c, D_2407d0.f_0368e8("SequenceNumber", r.a, 0, 0), D_1a2120);
    return D_24063c[0] == n;
}

/* Whether a car plays the Pac-Man music. */
static inline bool IsPackman(Pair car)
{
    memcpy(D_24063c, D_240740.f_0368e8("BgmPackman", car.a, 0, 0), D_1a2120);
    return D_24063c[0] != 0;
}

namespace Stream {

class CStreamBase {
public:
    CStreamBase();
    virtual ~CStreamBase();
    int f_094604(int ch, int pack);
    int f_094768(int a);
    int f_094d6c(int fade);
    int f_094db0();
    int f_094ed8(int cursor);
    int f_095448();

    int m4;
    int m8;
    int m12;
    char m16[256];
    int m272;
    int m276;
    int m280;
    int m284;
    int m288;
};

class CBgm : public CStreamBase {
public:
    CBgm();
    virtual ~CBgm();
    void f_096334();
    void f_096368(Pair course);
    void f_096408();
    int f_096434(int menu);
    int f_0964c4(int menu);
    int f_09654c();
    int f_0965b4();
    int f_0965ec();
    int f_09662c();
    int f_09664c();
    int f_09666c(int n);
    int f_096728(int n);
    int f_0967c4();
    int f_0968e0();
    int f_096918();
    int f_09694c();
    int f_0969ac();
    int f_096a6c();
    int f_096ab4();
    int f_096b04(int menu);
    void f_096d38();

    int m292;           /* the menu number */
    int m296;           /* the track (-1 none) */
    int m300;           /* the course's menu number */
    int m304;           /* 1 while a resume is still to be retried */
    int m308;           /* the play cursor kept over a pause */
    unsigned char m312; /* the disc is out */
    unsigned char m313; /* paused */
};

/* @implements 0x0961e0 us _ZN6Stream4CBgmC2Ev
   WHAT IT DOES: Makes the music stream with no track (base object constructor). */
/* @implements 0x096234 us _ZN6Stream4CBgmC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CBgm::CBgm()
{
    f_096d38();
}

/* @implements 0x096288 us _ZN6Stream4CBgmD2Ev
   WHAT IT DOES: Forgets the stream channel and data (base object destructor). */
/* @implements 0x0962bc us _ZN6Stream4CBgmD1Ev
   WHAT IT DOES: The same (complete object destructor). */
/* @implements 0x0962f0 us _ZN6Stream4CBgmD0Ev
   WHAT IT DOES: The same, then frees the object (deleting destructor). */
CBgm::~CBgm()
{
    m8 = -1;
    m12 = 0;
}

/* @implements 0x096334 us f_096334
   WHAT IT DOES: Clears the track and sets the stream up on channel 0 and pack 0. */
void CBgm::f_096334()
{
    f_096d38();
    f_094604(0, 0);
}

/* @implements 0x096368 us f_096368
   WHAT IT DOES: Takes the course's music number from the course database (when there is a
   course) and clears the pause and the retry. */
void CBgm::f_096368(Pair course)
{
    if (course.a) {
        char *f = D_2407a8.f_0368e8("Bgm", course.a, 0, 0);
        memcpy(D_24063c, f, D_1a211c[1]);
        int bgm = D_24063c[0];
        m300 = bgm;
        f_093f90("Stream CBgm: Setup: Course BGM:%d\n", bgm);
    }
    m304 = 0;
    m313 = 0;
}

/* @implements 0x096408 us f_096408
   WHAT IT DOES: Clears the track and stops the stream. */
void CBgm::f_096408()
{
    f_096d38();
    f_094db0();
}

/* @implements 0x096434 us f_096434
   WHAT IT DOES: Selects the race's music from the menu number (-1: the course's) and starts
   it, unless the disc is out (then the kept cursor is cleared). Returns the start's result,
   or -1. */
int CBgm::f_096434(int menu)
{
    int disc = f_111b0c();
    if (f_096b04(menu) < 0)
        return -1;
    if (disc == 1) {
        m308 = 0;
        return -1;
    }
    f_093f90("Stream CBgm: StartGame: BGM:%d MenuNo:%d\n", m296, m292);
    m304 = 0;
    m312 = 0;
    return f_094768(m296);
}

/* @implements 0x0964c4 us f_0964c4
   WHAT IT DOES: Selects the music player's music from the menu number and starts it, unless
   the disc is out. Returns the start's result, or -1. */
int CBgm::f_0964c4(int menu)
{
    int disc = f_111b0c();
    if (f_096b04(menu) < 0)
        return -1;
    if (disc == 1)
        return -1;
    f_093f90("Stream CBgm: StartAvPlayer: BGM:%d MenuNo:%d\n", m296, m292);
    m304 = 0;
    m312 = 0;
    return f_094768(m296);
}

/* @implements 0x09654c us f_09654c
   WHAT IT DOES: Starts the selected music again for the replay, unless the disc is out (then
   the kept cursor is cleared). Returns the start's result, or -1. */
int CBgm::f_09654c()
{
    if (f_111b0c() == 1) {
        m308 = 0;
        return -1;
    }
    f_093f90("Stream CBgm: StartReplay: BGM:%d MenuNo:%d\n", m296, m292);
    m304 = 0;
    m312 = 0;
    return f_094768(m296);
}

/* @implements 0x0965b4 us f_0965b4
   WHAT IT DOES: Fades the race's music out over 1500. */
int CBgm::f_0965b4()
{
    f_093f90("Stream CBgm: FadeOutGame\n");
    return f_094d6c(1500);
}

/* @implements 0x0965ec us f_0965ec
   WHAT IT DOES: Clears the track and fades the replay's music out over 1500. */
int CBgm::f_0965ec()
{
    f_093f90("Stream CBgm: FadeOutReplay\n");
    f_096d38();
    return f_094d6c(1500);
}

/* @implements 0x09662c us f_09662c
   WHAT IT DOES: Returns the group of the current track. */
int CBgm::f_09662c()
{
    return f_09666c(m296 + 1);
}

/* @implements 0x09664c us f_09664c
   WHAT IT DOES: Returns the current track's place in its group. */
int CBgm::f_09664c()
{
    return f_096728(m296 + 1);
}

/* @implements 0x09666c us f_09666c
   WHAT IT DOES: Returns the group (1 to 5) of a menu number: tracks 1-6, 7-12, 13-18, 19-24
   and 25-30, or the random pick 31 to 35 of each group; 6 for the random pick of all (255),
   7 for no music (0), -1 otherwise. */
int CBgm::f_09666c(int n)
{
    switch (n) {
    case 0:
        return 7;
    case 31:
        return 1;
    case 32:
        return 2;
    case 33:
        return 3;
    case 34:
        return 4;
    case 35:
        return 5;
    case 255:
        return 6;
    }
    if (n >= 1 && n < 7)
        return 1;
    if (n >= 7 && n < 13)
        return 2;
    if (n >= 13 && n < 19)
        return 3;
    if (n >= 19 && n < 25)
        return 4;
    return (n >= 25 && n < 31) ? 5 : -1;
}

/* @implements 0x096728 us f_096728
   WHAT IT DOES: Returns a menu number's place in its group (0 to 5), 6 for a random pick, or
   -1. */
int CBgm::f_096728(int n)
{
    if (n >= 31 && n < 36)
        return 6;
    int g = f_09666c(n);
    if (g < 0)
        return -1;
    int first;
    switch (g) {
    case 1:
        first = 1;
        break;
    case 2:
        first = 7;
        break;
    case 3:
        first = 13;
        break;
    case 4:
        first = 19;
        break;
    case 5:
        first = 25;
        break;
    default:
        return -1;
    }
    return n - first;
}

/* @draft 0x0967c4 us f_0967c4
   WHAT IT DOES: Says whether the current race plays the Pac-Man music: race type 5 with the
   first computer car's "BgmPackman" flag set.
   DRAFT: ten words: retail keeps the field size in s1 and the race record's address in s2
   (its lui of the size in v1); here the allocator swaps the two and uses v0.
   Remaining difference: greg (nmG) ranks the record address (pseudo 184, 3 refs over 58 insns) above the
   size (202, 3 refs over 74 insns, 3 calls); retail's order needs the size live shorter or the address longer. */
int CBgm::f_0967c4()
{
    bool r;
    Pair seq = D_1dd6b0.seq;
    if (IsSequence(seq, 5)) {
        if (D_240910 > 0) {
            r = IsPackman(GetS(0));
        } else {
            f_093f90("CBgm: IsPackman Failed! Invalid ComCar Num:%d\n", D_240910);
            r = false;
        }
    } else {
        r = false;
    }
    return r;
}

/* @implements 0x0968e0 us f_0968e0
   WHAT IT DOES: Pauses the music (the stream itself only while the disc is in). Returns 0. */
int CBgm::f_0968e0()
{
    m313 = 1;
    if (!m312)
        f_096a6c();
    return 0;
}

/* @implements 0x096918 us f_096918
   WHAT IT DOES: Resumes the music (the stream itself only while the disc is in). Returns 0. */
int CBgm::f_096918()
{
    m313 = 0;
    if (!m312)
        f_096ab4();
    return 0;
}

/* @implements 0x09694c us f_09694c
   WHAT IT DOES: Retries a failed resume. Returns 0, or -1 when it fails again. */
int CBgm::f_09694c()
{
    if (m304 != 1)
        return 0;
    if (f_094ed8(m308) < 0)
        return -1;
    f_093f90("Stream CBgm: RetryPauseOff Success\n");
    m304 = 0;
    return 0;
}

/* @implements 0x0969ac us f_0969ac
   WHAT IT DOES: Watches the disc: pauses the music when it goes out, and when it is back
   restarts the track (no kept cursor) or resumes it, unless the music is paused. Returns 0. */
int CBgm::f_0969ac()
{
    int disc = f_111b0c();
    if (!m312) {
        if (disc == 1) {
            m312 = disc;
            if (!m313)
                f_096a6c();
            f_093f90("StreamInterface: No Disc!\n");
        }
    } else if (disc == 0) {
        m312 = 0;
        if (!m313) {
            if (m308 == 0 && m296 >= 0)
                f_094768(m296);
            else
                f_096ab4();
        }
        f_093f90("StreamInterface: Disc Ok\n");
    }
    return 0;
}

/* @implements 0x096a6c us f_096a6c
   WHAT IT DOES: Keeps the play cursor and stops the stream. Returns 0, or -1 with no track. */
int CBgm::f_096a6c()
{
    if (m296 < 0)
        return -1;
    m308 = f_095448();
    f_094db0();
    return 0;
}

/* @implements 0x096ab4 us f_096ab4
   WHAT IT DOES: Plays the stream again from the kept cursor, marking a failure for a retry.
   Returns 0, or -1. */
int CBgm::f_096ab4()
{
    if (m296 < 0)
        return -1;
    if (f_094ed8(m308) < 0) {
        m304 = 1;
        return -1;
    }
    return 0;
}

/* @implements 0x096b04 us f_096b04
   WHAT IT DOES: Turns a menu number (-1: the course's) into a track: 0 is no music, 31 to 35
   a random track of a group, 255 a random track of all 30, else the numbered track. Returns
   0, or -1 for no music. */
int CBgm::f_096b04(int menu)
{
    if (menu < 0)
        m292 = m300;
    else
        m292 = menu;
    int r;
    switch (m292) {
    case 0:
        f_093f90("Stream CBgm: StartGame: BGM OFF\n");
        m296 = -1;
        break;
    case 31:
        r = f_0f6b90() % 6;
        m296 = r + 1;
        break;
    case 32:
        r = f_0f6b90() % 6;
        m296 = r + 7;
        break;
    case 33:
        r = f_0f6b90() % 6;
        m296 = r + 13;
        break;
    case 34:
        r = f_0f6b90() % 6;
        m296 = r + 19;
        break;
    case 35:
        r = f_0f6b90() % 6;
        m296 = r + 25;
        break;
    case 255:
        r = f_0f6b90() % 30;
        m296 = r + 1;
        break;
    default:
        m296 = m292;
        break;
    }
    if (m296 > 0)
        m296--;
    if (m296 < 0)
        return -1;
    f_093f90("Stream CBgm: SelectNo: BGM:%d MenuNo:%d\n", m296, m292);
    return 0;
}

/* @implements 0x096d38 us f_096d38
   WHAT IT DOES: Clears the track, the menu numbers, the kept cursor, the pause and the disc
   state. */
void CBgm::f_096d38()
{
    m292 = -1;
    m296 = -1;
    m300 = -1;
    m304 = 0;
    m308 = -1;
    m312 = 0;
    m313 = 0;
}

}

/* The music stream. */
Stream::CBgm D_242cb0;

/* @implements 0x096d5c us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the music stream at start up and destroys it at exit. */
/* @implements 0x096dd8 us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
/* @implements 0x096df8 us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */
