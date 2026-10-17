/* The race 2D overlay pieces object file (retail 0x101f7c to 0x107edc): the pieces the race
   overlay is built from, each a Fj::C2DDecorationBase with its own sprite set. The course
   map (normal and wireless battle forms) with the cars' markers, the time limit, the lap
   time, the nitro gauge, the total and record times, the position (and its time attack tour
   form), the lap counter, the flag, the race info comment, the start and finish banners, the
   info window and the all-time records table. Every piece names its sprite set, keeps its
   sprite handles in an array after the base and fades its sprites in with the start
   animation. */

#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

/* The VFPU's sine and cosine (of a quarter turn per unit). */
static inline float VSin(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvsin.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}

static inline float VCos(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvcos.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}

extern "C" {
int strcmp(const char *a, const char *b);
int iprintf(const char *fmt, ...);
}

/* The race in progress (null outside a race). */
struct RaceInfo {
    char m0[8];
    char *course;
    char m12[20];
    int timeLeft;
    int laps;
    char m40[16];
    int mode;
    int cars;
    char m64[44];
    int lap;
    int position;
    char m116[76];
    int m192;
};
extern RaceInfo *D_2407fc;

struct Race;
int f_0f6450(Race *r);
int f_0f6420(Race *r);

/* The sprite group the pieces draw with. */
struct Group;

/* A sprite colour. */
struct Rgba {
    int r, g, b, a;
};

/* A sprite corner: its position and texture coordinates. */
struct Corner {
    float x, y, u, v;
};

void f_04bf6c(Group *g, int sprite, Corner *c);
void f_04c1c8(Group *g, int sprite, Rgba c);
void f_04c248(Group *g, int sprite, unsigned char on);
void f_04c3c8(Group *g, int sprite, float x, float y);
void f_04c668(Group *g, int sprite, float r, float gr, float b, float a);
void f_04d16c(Group *g, int sprite);
void f_04d19c(Group *g, int sprite);

/* The sprite set names. */
extern const char *D_1d5fb4;
extern const char *D_1d5fb8;
extern const char *D_1d5fbc;
extern const char *D_1d5fc0;
extern const char *D_1d5fc4;
extern const char *D_1d5fc8;
extern const char *D_1d5fcc;
extern const char *D_1d5fd0;
extern const char *D_1d5fd4;
extern const char *D_1d5fd8;
extern const char *D_1d5fdc;
extern const char *D_1d5fe0;
extern const char *D_1d5fe4;

namespace Fj {

class C2DDecorationBase {
public:
    virtual ~C2DDecorationBase() {}
    virtual int f_101f44() { return 0; }
    virtual int f_101f4c() { return 0; }
    virtual int f_101f54(int i) { return 0; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw() = 0;
    virtual int f_101b54();
    virtual void f_101f5c() {}
    virtual int *f_101f64(int i) { return 0; }
    virtual const char *f_101f6c() { return 0; }
    virtual void f_101f74(float t) {}
    void f_101c70(unsigned char on);
    void f_101cf4(int t, int *min, int *sec, int *ms);
    void f_101da4(Corner *c, const Corner *r);
    int f_101e38();

    /* Shows or hides one sprite. */
    void Show(int i, unsigned char on)
    {
        Group *g = group;

        f_04c248(g, f_101f54(i), on);
    }
    /* Sets one sprite's alpha, at full brightness. */
    void Fade(int i, float t)
    {
        Group *g = group;

        f_04c668(g, f_101f54(i), 1.0f, 1.0f, 1.0f, t);
    }
    /* The start animation has not finished. */
    bool Starting() { return state < 3; }

    Race *race;
    Group *group;
    unsigned char on;
    int state;
    int start;
};

/* A course's map: its rotation in degrees, the world units per map pixel, the world centre,
   and the map's centre on the sprite. */
struct MapInfo {
    float rot;
    float scale;
    float cx, cy;
    float mx, my;
};

/* The parts every piece adds: its type number, how many sprites it shows, where it keeps
   their handles and the name of its sprite set. */
#define PIECE(TYPE, COUNT, NAME)                                      \
    virtual int f_101f44() { return TYPE; }                           \
    virtual int f_101f4c() { return COUNT; }                          \
    virtual int f_101f54(int i) { return *f_101f64(i); }              \
    virtual int *f_101f64(int i) { return &sprite[i]; }               \
    virtual const char *f_101f6c() { return NAME; }

class C2DCourseMap : public C2DDecorationBase {
public:
    virtual int f_101f44() = 0;
    virtual int f_101f4c() { return 10; }
    virtual int f_101f54(int i) { return *f_101f64(i); }
    virtual int f_101b1c(Group *group, Race *race) = 0;
    virtual int Draw() = 0;
    virtual int f_101b54() = 0;
    virtual int *f_101f64(int i) { return &sprite[i]; }
    virtual const char *f_101f6c() { return D_1d5fb4; }
    virtual void f_101f74(float t);
    void f_101f7c(float x, float z, float *mx, float *my);
    void f_10207c();
    void f_102190(int s, int rect, unsigned char on, float x, float y);
    int f_102254();

    int flip;
    int course;
    int sprite[10];
};

class C2DCourseMapNormal : public C2DCourseMap {
public:
    virtual int f_101f44() { return 1; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();

    unsigned char blink;
};

class C2DCourseMapWbattle : public C2DCourseMap {
public:
    virtual int f_101f44() { return 2; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
};

class C2DTimeLimit : public C2DDecorationBase {
public:
    PIECE(3, 1, D_1d5fb8)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();

    int sprite[1];
    unsigned char shown;
};

class C2DLapTime : public C2DDecorationBase {
public:
    PIECE(4, 1, D_1d5fbc)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);

    int sprite[1];
};

class C2DNitro : public C2DDecorationBase {
public:
    PIECE(5, 9, D_1d5fc0)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_103138(int i, float x, float y, float z);

    int sprite[9];
    int m60;
    int m64;
    int m68;
};

class C2DTotalTime : public C2DDecorationBase {
public:
    PIECE(6, 1, D_1d5fc4)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);

    int sprite[1];
};

class C2DRecordTime : public C2DDecorationBase {
public:
    PIECE(7, 1, D_1d5fc8)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);

    int sprite[1];
};

class C2DPosition : public C2DDecorationBase {
public:
    PIECE(8, 6, D_1d5fcc)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_103820(int n, int of, int m);

    int sprite[6];
};

class C2DPositionTour : public C2DPosition {
public:
    virtual int f_101f44() { return 9; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
};

class C2DLap : public C2DPosition {
public:
    virtual int f_101f44() { return 10; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    void f_104184(int n, int of, float x);
};

class C2DFlag : public C2DDecorationBase {
public:
    PIECE(11, 1, D_1d5fd0)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();

    int sprite[1];
    int m28;
};

class C2DRaceInfo : public C2DDecorationBase {
public:
    PIECE(12, 1, D_1d5fd4)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    void f_104620(int kind);

    int sprite[1];
    unsigned char shown;
};

class C2DRaceInfoStart : public C2DDecorationBase {
public:
    PIECE(13, 4, D_1d5fd8)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();

    int sprite[4];
};

class C2DRaceInfoFinish : public C2DDecorationBase {
public:
    PIECE(14, 1, D_1d5fdc)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();

    int sprite[1];
};

class C2DInfoWin : public C2DDecorationBase {
public:
    PIECE(15, 30, D_1d5fe0)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();

    int sprite[30];
    int m144;
    int m148;
    char m152[8];
    int m160;
    int m164;
    int m168;
    int m172;
    int m176;
    int m180;
    bool m184;
    int m188;
    int m192;
    int m196;
    int m200;
    int m204;
};

class C2DAllTime : public C2DDecorationBase {
public:
    PIECE(23, 54, D_1d5fe4)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_106e8c(int i, int a, int b, int c, int d, int on);

    int sprite[54];
    int m240;
    int m244;
    unsigned char m248;
    int m252;
    int m256;
    int m260;
    int m264;
    int m268;
};

}

using namespace Fj;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* The course maps, by course. */
extern const MapInfo D_1b0be4[];

/* @draft 0x101f7c us C2DCourseMap8f_101f7c
   WHAT IT DOES: Turns a world position into a position on the course map: scales it to map
   pixels around the course's centre, turns it by the course's map rotation (mirrored when the
   course runs reversed) and offsets it to the map's centre on the sprite.
   Remaining difference: the order of the scale and rotation arithmetic and its registers
   (8 bytes longer here); the sine and cosine and the stores agree. */
void C2DCourseMap::f_101f7c(float x, float z, float *mx, float *my)
{
    const MapInfo *m = &D_1b0be4[course];
    float k = 1.0f / m->scale;
    float a = m->rot * 0.017453292f * 0.63661975f;
    float s, c, u, v;

    x = x * k + (m->cx - m->mx);
    z = z * k + (m->cy - m->my);
    s = VSin(a);
    c = VCos(a);
    v = x * s + z * c;
    u = x * c - z * s;
    if (flip)
        u = -u;
    *mx = m->mx + 375.0f + u - 8.0f;
    *my = m->my + 2.0f + v - 8.0f;
}

/* @draft 0x10207c us C2DCourseMap8f_10207c
   WHAT IT DOES: Places the map sprite: 104 pixels square at the course's map centre, its
   texture mirrored when the course runs reversed.
   Remaining difference: the corner stores' order and registers. */
void C2DCourseMap::f_10207c()
{
    const MapInfo *m = &D_1b0be4[course];
    float my = m->my;
    float mx = m->mx;
    Corner c[4];
    float x0, x1, y0, y1;

    flip = f_0f6450(race);
    x0 = -mx;
    x1 = 104.0f - mx;
    y0 = -my;
    y1 = 104.0f - my;
    if (flip) {
        x1 = -x1;
        x0 = mx;
    }
    x1 = mx + 375.0f + x1;
    y1 = my + 2.0f + y1;
    x0 = mx + 375.0f + x0;
    y0 = my + 2.0f + y0;
    c[0].x = x0;
    c[0].y = y0;
    c[0].u = 0;
    c[0].v = 0;
    c[1].x = x1;
    c[1].y = y0;
    c[1].u = 104.0f;
    c[1].v = 0;
    c[2].x = x0;
    c[2].y = y1;
    c[2].u = 0;
    c[2].v = 104.0f;
    c[3].x = x1;
    c[3].y = y1;
    c[3].u = 104.0f;
    c[3].v = 104.0f;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(0), c);
    }
}

/* The map markers' texture rectangles. */
extern Corner D_1d5e44[];

/* @draft 0x102190 us C2DCourseMap8f_102190
   WHAT IT DOES: Places a car marker sprite at a map position with one of the marker texture
   rectangles, and shows or hides it.
   Remaining difference: retail loads the rectangle's words 4, 0, 8, 12 and stores the corners
   in pairs sharing a value (c[1].u, c[1].x, c[2].y, c[2].v, c[2].x, c[0].x, ...), with this in s2
   and the sprite in s1; here in field order with the two saved registers swapped. */
void C2DCourseMap::f_102190(int s, int rect, unsigned char show, float x, float y)
{
    const Corner *r = &D_1d5e44[rect];
    Corner c[4];

    c[0].x = x;
    c[0].y = y;
    c[0].u = r->x;
    c[0].v = r->y;
    c[1].x = x + r->u;
    c[1].y = y;
    c[1].u = r->x + r->u;
    c[1].v = r->y;
    c[2].x = x;
    c[2].y = y + r->v;
    c[2].u = r->x;
    c[2].v = r->y + r->v;
    c[3].x = x + r->u;
    c[3].y = y + r->v;
    c[3].u = r->x + r->u;
    c[3].v = r->y + r->v;
    f_04bf6c(group, s, c);
    f_04c248(group, s, show);
}

/* @draft 0x102254 us C2DCourseMap8f_102254
   WHAT IT DOES: Finds the race's course among the 25 course names and keeps its number for
   the map; returns 1 when found, 0 (printing a debug message) when not or outside a race.
   Remaining difference: none in the bytes; the debug message is followed in retail .rodata by
   a table this file does not yet define, which the grader's 64 byte window sees. */
int C2DCourseMap::f_102254()
{
    const char *names[25] = {
        "Mountain_N",    "Mountain_R",    "Advanced_N",     "Advanced_R",     "OverPassCity_N",
        "OverPassCity_R", "HeavenAndHell_N", "HeavenAndHell_R", "Short_N",       "Short_R",
        "City_N",        "City_R",        "Plateau_N",      "Plateau_R",      "Novice_N",
        "Novice_R",      "LakeSideGate_N", "LakeSideGate_R", "WonderHill_N",   "WonderHill_R",
        "Long_N",        "Long_R",        "Town_N",         "Town_R",         "Test_Course",
    };
    const char *name;
    int i;

    course = 0;
    if (!D_2407fc)
        return 0;
    name = D_2407fc->course;
    for (i = 0; i < 25; i++) {
        if (!strcmp(name, names[i])) {
            course = i;
            return 1;
        }
    }
    iprintf("### E:Race2d:: No Course Name ...%s \n", name);
    return 0;
}

/* @implements 0x102334 us C2DCourseMap8f_101f74
   WHAT IT DOES: Fades all ten map sprites by the start animation. */
void C2DCourseMap::f_101f74(float t)
{
    Fade(0, t);
    Fade(1, t);
    Fade(2, t);
    Fade(3, t);
    Fade(4, t);
    Fade(5, t);
    Fade(6, t);
    Fade(7, t);
    Fade(8, t);
    Fade(9, t);
}

/* @implements 0x10257c us C2DCourseMapNormal8f_101b1c
   WHAT IT DOES: Sets the normal course map up: hides the nine car markers, finds the course
   and places the map. */
int C2DCourseMapNormal::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    Show(1, 0);
    Show(2, 0);
    Show(3, 0);
    Show(4, 0);
    Show(5, 0);
    Show(6, 0);
    Show(7, 0);
    Show(8, 0);
    Show(9, 0);
    f_102254();
    f_10207c();
    blink = 0;
    return 1;
}

/* @implements 0x102728 us C2DCourseMapNormal4Draw
   WHAT IT DOES: Nothing to draw here (the sprites draw themselves); returns 1. */
int C2DCourseMapNormal::Draw()
{
    return 1;
}

/* @implements 0x1028f0 us C2DCourseMapWbattle8f_101b1c
   WHAT IT DOES: Sets the wireless battle course map up: hides the nine car markers, finds the
   course and places the map. */
int C2DCourseMapWbattle::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    Show(1, 0);
    Show(2, 0);
    Show(3, 0);
    Show(4, 0);
    Show(5, 0);
    Show(6, 0);
    Show(7, 0);
    Show(8, 0);
    Show(9, 0);
    f_102254();
    f_10207c();
    return 1;
}

/* @implements 0x102a98 us C2DCourseMapWbattle4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DCourseMapWbattle::Draw()
{
    return 1;
}

/* @implements 0x102c5c us C2DTimeLimit8f_101b1c
   WHAT IT DOES: Sets the time limit label up: hidden, at (0, 16). */
int C2DTimeLimit::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    Show(0, 0);
    {
        Group *gr = group;

        f_04c3c8(gr, f_101f54(0), 0.0f, 16.0f);
    }
    shown = 0;
    return 1;
}

/* @implements 0x102ce8 us C2DTimeLimit4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DTimeLimit::Draw()
{
    return 1;
}

/* @implements 0x102cf0 us C2DTimeLimit8f_101b54
   WHAT IT DOES: Runs the start animation, then shows the time limit label once the race's
   time left is under six minutes. Returns 0. */
int C2DTimeLimit::f_101b54()
{
    int min, sec, ms;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    f_101cf4(D_2407fc->timeLeft, &min, &sec, &ms);
    if (min < 6 && !shown) {
        Show(0, 1);
        shown = 1;
    }
    return 0;
}

/* @implements 0x102d90 us C2DLapTime8f_101b1c
   WHAT IT DOES: Sets the lap time label up. */
int C2DLapTime::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    return 1;
}

/* @implements 0x102db0 us C2DLapTime4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DLapTime::Draw()
{
    return 1;
}

/* @implements 0x102db8 us C2DLapTime8f_101b54
   WHAT IT DOES: Runs the start animation. Returns 0. */
int C2DLapTime::f_101b54()
{
    C2DDecorationBase::f_101b54();
    return 0;
}

/* @implements 0x102dd8 us C2DLapTime8f_101f74
   WHAT IT DOES: Fades the label in with the start animation. */
void C2DLapTime::f_101f74(float t)
{
    Fade(0, t);
}

/* @draft 0x102e34 us C2DNitro8f_101b1c
   WHAT IT DOES: Sets the nitro gauge up: its three bars empty, nothing counted.
   Remaining difference (4 words): for the first bar retail sets the three float arguments
   before this; here this comes first. */
int C2DNitro::f_101b1c(Group *g, Race *r)
{
    float z = 0;

    C2DDecorationBase::f_101b1c(g, r);
    f_103138(0, z, z, z);
    f_103138(1, z, z, z);
    f_103138(2, z, z, z);
    m68 = 0;
    m64 = 0;
    m60 = 0;
    return 1;
}

/* @implements 0x102ebc us C2DNitro4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DNitro::Draw()
{
    return 1;
}

/* @implements 0x1035b0 us C2DTotalTime8f_101b1c
   WHAT IT DOES: Sets the total time label up. */
int C2DTotalTime::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    return 1;
}

/* @implements 0x1035d0 us C2DTotalTime4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DTotalTime::Draw()
{
    return 1;
}

/* @implements 0x1035d8 us C2DTotalTime8f_101b54
   WHAT IT DOES: Runs the start animation. Returns 0. */
int C2DTotalTime::f_101b54()
{
    C2DDecorationBase::f_101b54();
    return 0;
}

/* @implements 0x1035f8 us C2DTotalTime8f_101f74
   WHAT IT DOES: Fades the label in with the start animation. */
void C2DTotalTime::f_101f74(float t)
{
    Fade(0, t);
}

/* @implements 0x103654 us C2DRecordTime8f_101b1c
   WHAT IT DOES: Sets the lap record label up. */
int C2DRecordTime::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    return 1;
}

/* @implements 0x103674 us C2DRecordTime4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DRecordTime::Draw()
{
    return 1;
}

/* @implements 0x10367c us C2DRecordTime8f_101b54
   WHAT IT DOES: Runs the start animation. Returns 0. */
int C2DRecordTime::f_101b54()
{
    C2DDecorationBase::f_101b54();
    return 0;
}

/* @implements 0x10369c us C2DRecordTime8f_101f74
   WHAT IT DOES: Fades the label in with the start animation. */
void C2DRecordTime::f_101f74(float t)
{
    Fade(0, t);
}


/* @implements 0x1036f8 us C2DPosition8f_101b1c
   WHAT IT DOES: Sets the position display up in a race: the label's colour, then the
   player's position out of the number of cars. */
int C2DPosition::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    if (D_2407fc) {
        {
            Group *gr = group;

            f_04c1c8(gr, f_101f54(0), (Rgba){ 0, 0, 128, 20 });
        }
        f_103820(D_2407fc->position + 1, D_2407fc->cars, 0);
    }
    return 1;
}

/* @implements 0x1037b0 us C2DPosition4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DPosition::Draw()
{
    return 1;
}

/* @implements 0x1037b8 us C2DPosition8f_101b54
   WHAT IT DOES: Runs the start animation, and once it is done shows the player's position
   out of the number of cars. Returns 0. */
int C2DPosition::f_101b54()
{
    if (C2DDecorationBase::f_101b54() && !Starting())
        f_103820(D_2407fc->position + 1, D_2407fc->cars, 0);
    return 0;
}

/* @implements 0x103de4 us C2DPositionTour8f_101b1c
   WHAT IT DOES: Sets the tour position display up in a race: the label's colour, then the
   player's position out of the number of cars. */
int C2DPositionTour::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    if (D_2407fc) {
        {
            Group *gr = group;

            f_04c1c8(gr, f_101f54(0), (Rgba){ 0, 0, 128, 20 });
        }
        f_103820(D_2407fc->position + 1, D_2407fc->cars, 0);
    }
    return 1;
}

/* @implements 0x103e9c us C2DPositionTour4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DPositionTour::Draw()
{
    return 1;
}

/* @implements 0x104058 us C2DLap8f_101b1c
   WHAT IT DOES: Sets the lap counter up in a race: the label's colour, then the lap out of
   the race's laps. */
int C2DLap::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    if (D_2407fc) {
        {
            Group *gr = group;

            f_04c1c8(gr, f_101f54(0), (Rgba){ 130, 0, 240, 20 });
        }
        f_104184(D_2407fc->lap + 1, D_2407fc->laps, -20.0f);
    }
    return 1;
}

/* @implements 0x104114 us C2DLap4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DLap::Draw()
{
    return 1;
}

/* @implements 0x10411c us C2DLap8f_101b54
   WHAT IT DOES: Runs the start animation, and once it is done shows the lap (at most the
   last) out of the race's laps. Returns 0. */
int C2DLap::f_101b54()
{
    if (C2DDecorationBase::f_101b54() && !Starting()) {
        int lap = D_2407fc->lap + 1;

        if (lap > D_2407fc->laps)
            lap = D_2407fc->laps;
        f_104184(lap, D_2407fc->laps, -20.0f);
    }
    return 0;
}

/* @implements 0x104420 us C2DFlag8f_101b1c
   WHAT IT DOES: Sets the flag up hidden. */
int C2DFlag::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    Show(0, 0);
    m28 = 0;
    return 1;
}

/* @implements 0x10447c us C2DFlag4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DFlag::Draw()
{
    return 1;
}

/* @implements 0x104484 us C2DFlag8f_101b54
   WHAT IT DOES: Nothing (the flag has no start animation); returns 0. */
int C2DFlag::f_101b54()
{
    return 0;
}

/* @implements 0x10448c us C2DRaceInfo8f_101b1c
   WHAT IT DOES: Sets the race info comment up hidden, on the first comment. */
int C2DRaceInfo::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    f_104620(1);
    Show(0, 0);
    shown = 0;
    return 1;
}

/* @implements 0x1044f4 us C2DRaceInfo4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DRaceInfo::Draw()
{
    return 1;
}

/* @implements 0x104714 us C2DRaceInfoStart8f_101b1c
   WHAT IT DOES: Sets the start banner up with its four sprites hidden. */
int C2DRaceInfoStart::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    Show(0, 0);
    Show(1, 0);
    Show(2, 0);
    Show(3, 0);
    return 1;
}

/* @implements 0x1047e4 us C2DRaceInfoStart4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DRaceInfoStart::Draw()
{
    return 1;
}

/* @implements 0x104f3c us C2DRaceInfoFinish8f_101b1c
   WHAT IT DOES: Sets the finish banner up hidden. */
int C2DRaceInfoFinish::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    Show(0, 0);
    return 1;
}

/* @implements 0x104f94 us C2DRaceInfoFinish4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DRaceInfoFinish::Draw()
{
    return 1;
}

/* @implements 0x104f9c us C2DRaceInfoFinish8f_101b54
   WHAT IT DOES: Nothing (the banner has no start animation); returns 0. */
int C2DRaceInfoFinish::f_101b54()
{
    return 0;
}

/* @implements 0x104fa4 us C2DInfoWin8f_101b1c
   WHAT IT DOES: Sets the info window up: every sprite hidden (the frame, the title, the
   twenty line sprites and the rest), its state cleared, and two of its sprites given their
   special drawing. */
int C2DInfoWin::f_101b1c(Group *g, Race *r)
{
    int i;

    C2DDecorationBase::f_101b1c(g, r);
    Show(0, 0);
    Show(2, 0);
    Show(29, 0);
    Show(1, 0);
    Show(3, 0);
    Show(4, 0);
    Show(5, 0);
    Show(6, 0);
    Show(7, 0);
    Show(8, 0);
    for (i = 0; i < 20; i++)
        Show(9 + i, 0);
    m176 = 0;
    m164 = 0;
    m160 = 0;
    m172 = 0;
    m168 = 0;
    m204 = 0;
    m180 = 0;
    m184 = 0;
    m144 = 0;
    m188 = 0;
    m200 = 0;
    m196 = 0;
    m192 = 0;
    {
        Group *gr = group;

        f_04d16c(gr, f_101f54(0));
    }
    {
        Group *gr = group;

        f_04d19c(gr, f_101f54(8));
    }
    m148 = 0;
    return 1;
}

/* @implements 0x105224 us C2DInfoWin4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DInfoWin::Draw()
{
    return 1;
}

/* @draft 0x106a5c us C2DAllTime8f_101b1c
   WHAT IT DOES: Sets the all-time records table up: its six rows cleared (all but the third
   shown), its nine number sprites placed, and its state reset.
   Remaining difference (7 words, scheduling): retail stores 248, 240, 260, 244, 252, 256,
   268, 264; here the second -1 store (256) is pulled up after the byte store. */
int C2DAllTime::f_101b1c(Group *g, Race *r)
{
    int base;
    int i;

    C2DDecorationBase::f_101b1c(g, r);
    f_106e8c(0, 0, 0, 0, 0, 1);
    f_106e8c(1, 0, 0, 0, 0, 1);
    f_106e8c(3, 0, 0, 0, 0, 1);
    f_106e8c(4, 0, 0, 0, 0, 1);
    f_106e8c(5, 0, 0, 0, 0, 1);
    f_106e8c(2, 0, 0, 0, 0, 0);
    base = f_101f54(18);
    for (i = 0; i < 9; i++)
        f_04c3c8(group, base + i, -5.0f, 16.0f);
    m248 = 1;
    m240 = -1;
    m260 = 0;
    m244 = 0;
    m252 = 0;
    m256 = -1;
    m268 = 0;
    m264 = 0;
    return 1;
}

/* @implements 0x106bd4 us C2DAllTime4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DAllTime::Draw()
{
    return 1;
}

/* The pieces' inline methods, emitted with their vtables. */

/* @implements 0x1076c8 us _ZN2Fj12C2DCourseMapD1Ev
   WHAT IT DOES: The course map destructor (only the base vtable store is left). */

/* @implements 0x1076d8 us _ZN2Fj12C2DCourseMapD0Ev
   WHAT IT DOES: The course map deleting destructor. */

/* @implements 0x107700 us C2DCourseMap8f_101f4c
   WHAT IT DOES: How many sprites the course map shows. */

/* @implements 0x107708 us C2DCourseMap8f_101f64
   WHAT IT DOES: Where the course map keeps a sprite's handle. */

/* @implements 0x107718 us C2DCourseMap8f_101f6c
   WHAT IT DOES: The name of the course map's sprite set. */

/* @implements 0x107724 us C2DCourseMap8f_101f54
   WHAT IT DOES: The handle of one of the course map's sprites. */

/* @implements 0x10774c us _ZN2Fj18C2DCourseMapNormalD1Ev
   WHAT IT DOES: The normal course map destructor (only the base vtable store is left). */

/* @implements 0x10775c us _ZN2Fj18C2DCourseMapNormalD0Ev
   WHAT IT DOES: The normal course map deleting destructor. */

/* @implements 0x107784 us C2DCourseMapNormal8f_101f44
   WHAT IT DOES: The normal course map's piece type number. */

/* @implements 0x10778c us _ZN2Fj19C2DCourseMapWbattleD1Ev
   WHAT IT DOES: The wireless battle course map destructor (only the base vtable store is left). */

/* @implements 0x10779c us _ZN2Fj19C2DCourseMapWbattleD0Ev
   WHAT IT DOES: The wireless battle course map deleting destructor. */

/* @implements 0x1077c4 us C2DCourseMapWbattle8f_101f44
   WHAT IT DOES: The wireless battle course map's piece type number. */

/* @implements 0x1077cc us _ZN2Fj12C2DTimeLimitD1Ev
   WHAT IT DOES: The time limit label destructor (only the base vtable store is left). */

/* @implements 0x1077dc us _ZN2Fj12C2DTimeLimitD0Ev
   WHAT IT DOES: The time limit label deleting destructor. */

/* @implements 0x107804 us C2DTimeLimit8f_101f44
   WHAT IT DOES: The time limit label's piece type number. */

/* @implements 0x10780c us C2DTimeLimit8f_101f4c
   WHAT IT DOES: How many sprites the time limit label shows. */

/* @implements 0x107814 us C2DTimeLimit8f_101f64
   WHAT IT DOES: Where the time limit label keeps a sprite's handle. */

/* @implements 0x107824 us C2DTimeLimit8f_101f6c
   WHAT IT DOES: The name of the time limit label's sprite set. */

/* @implements 0x107830 us C2DTimeLimit8f_101f54
   WHAT IT DOES: The handle of one of the time limit label's sprites. */

/* @implements 0x107858 us _ZN2Fj10C2DLapTimeD1Ev
   WHAT IT DOES: The lap time label destructor (only the base vtable store is left). */

/* @implements 0x107868 us _ZN2Fj10C2DLapTimeD0Ev
   WHAT IT DOES: The lap time label deleting destructor. */

/* @implements 0x107890 us C2DLapTime8f_101f44
   WHAT IT DOES: The lap time label's piece type number. */

/* @implements 0x107898 us C2DLapTime8f_101f4c
   WHAT IT DOES: How many sprites the lap time label shows. */

/* @implements 0x1078a0 us C2DLapTime8f_101f64
   WHAT IT DOES: Where the lap time label keeps a sprite's handle. */

/* @implements 0x1078b0 us C2DLapTime8f_101f6c
   WHAT IT DOES: The name of the lap time label's sprite set. */

/* @implements 0x1078bc us C2DLapTime8f_101f54
   WHAT IT DOES: The handle of one of the lap time label's sprites. */

/* @implements 0x1078e4 us _ZN2Fj8C2DNitroD1Ev
   WHAT IT DOES: The nitro gauge destructor (only the base vtable store is left). */

/* @implements 0x1078f4 us _ZN2Fj8C2DNitroD0Ev
   WHAT IT DOES: The nitro gauge deleting destructor. */

/* @implements 0x10791c us C2DNitro8f_101f44
   WHAT IT DOES: The nitro gauge's piece type number. */

/* @implements 0x107924 us C2DNitro8f_101f4c
   WHAT IT DOES: How many sprites the nitro gauge shows. */

/* @implements 0x10792c us C2DNitro8f_101f64
   WHAT IT DOES: Where the nitro gauge keeps a sprite's handle. */

/* @implements 0x10793c us C2DNitro8f_101f6c
   WHAT IT DOES: The name of the nitro gauge's sprite set. */

/* @implements 0x107948 us C2DNitro8f_101f54
   WHAT IT DOES: The handle of one of the nitro gauge's sprites. */

/* @implements 0x107970 us _ZN2Fj12C2DTotalTimeD1Ev
   WHAT IT DOES: The total time label destructor (only the base vtable store is left). */

/* @implements 0x107980 us _ZN2Fj12C2DTotalTimeD0Ev
   WHAT IT DOES: The total time label deleting destructor. */

/* @implements 0x1079a8 us C2DTotalTime8f_101f44
   WHAT IT DOES: The total time label's piece type number. */

/* @implements 0x1079b0 us C2DTotalTime8f_101f4c
   WHAT IT DOES: How many sprites the total time label shows. */

/* @implements 0x1079b8 us C2DTotalTime8f_101f64
   WHAT IT DOES: Where the total time label keeps a sprite's handle. */

/* @implements 0x1079c8 us C2DTotalTime8f_101f6c
   WHAT IT DOES: The name of the total time label's sprite set. */

/* @implements 0x1079d4 us C2DTotalTime8f_101f54
   WHAT IT DOES: The handle of one of the total time label's sprites. */

/* @implements 0x1079fc us _ZN2Fj13C2DRecordTimeD1Ev
   WHAT IT DOES: The lap record label destructor (only the base vtable store is left). */

/* @implements 0x107a0c us _ZN2Fj13C2DRecordTimeD0Ev
   WHAT IT DOES: The lap record label deleting destructor. */

/* @implements 0x107a34 us C2DRecordTime8f_101f44
   WHAT IT DOES: The lap record label's piece type number. */

/* @implements 0x107a3c us C2DRecordTime8f_101f4c
   WHAT IT DOES: How many sprites the lap record label shows. */

/* @implements 0x107a44 us C2DRecordTime8f_101f64
   WHAT IT DOES: Where the lap record label keeps a sprite's handle. */

/* @implements 0x107a54 us C2DRecordTime8f_101f6c
   WHAT IT DOES: The name of the lap record label's sprite set. */

/* @implements 0x107a60 us C2DRecordTime8f_101f54
   WHAT IT DOES: The handle of one of the lap record label's sprites. */

/* @implements 0x107a88 us _ZN2Fj11C2DPositionD1Ev
   WHAT IT DOES: The position display destructor (only the base vtable store is left). */

/* @implements 0x107a98 us _ZN2Fj11C2DPositionD0Ev
   WHAT IT DOES: The position display deleting destructor. */

/* @implements 0x107ac0 us C2DPosition8f_101f44
   WHAT IT DOES: The position display's piece type number. */

/* @implements 0x107ac8 us C2DPosition8f_101f4c
   WHAT IT DOES: How many sprites the position display shows. */

/* @implements 0x107ad0 us C2DPosition8f_101f64
   WHAT IT DOES: Where the position display keeps a sprite's handle. */

/* @implements 0x107ae0 us C2DPosition8f_101f6c
   WHAT IT DOES: The name of the position display's sprite set. */

/* @implements 0x107aec us C2DPosition8f_101f54
   WHAT IT DOES: The handle of one of the position display's sprites. */

/* @implements 0x107b14 us _ZN2Fj15C2DPositionTourD1Ev
   WHAT IT DOES: The tour position display destructor (only the base vtable store is left). */

/* @implements 0x107b24 us _ZN2Fj15C2DPositionTourD0Ev
   WHAT IT DOES: The tour position display deleting destructor. */

/* @implements 0x107b4c us C2DPositionTour8f_101f44
   WHAT IT DOES: The tour position display's piece type number. */

/* @implements 0x107b54 us _ZN2Fj6C2DLapD1Ev
   WHAT IT DOES: The lap counter destructor (only the base vtable store is left). */

/* @implements 0x107b64 us _ZN2Fj6C2DLapD0Ev
   WHAT IT DOES: The lap counter deleting destructor. */

/* @implements 0x107b8c us C2DLap8f_101f44
   WHAT IT DOES: The lap counter's piece type number. */

/* @implements 0x107b94 us _ZN2Fj7C2DFlagD1Ev
   WHAT IT DOES: The flag destructor (only the base vtable store is left). */

/* @implements 0x107ba4 us _ZN2Fj7C2DFlagD0Ev
   WHAT IT DOES: The flag deleting destructor. */

/* @implements 0x107bcc us C2DFlag8f_101f44
   WHAT IT DOES: The flag's piece type number. */

/* @implements 0x107bd4 us C2DFlag8f_101f4c
   WHAT IT DOES: How many sprites the flag shows. */

/* @implements 0x107bdc us C2DFlag8f_101f64
   WHAT IT DOES: Where the flag keeps a sprite's handle. */

/* @implements 0x107bec us C2DFlag8f_101f6c
   WHAT IT DOES: The name of the flag's sprite set. */

/* @implements 0x107bf8 us C2DFlag8f_101f54
   WHAT IT DOES: The handle of one of the flag's sprites. */

/* @implements 0x107c20 us _ZN2Fj11C2DRaceInfoD1Ev
   WHAT IT DOES: The race info comment destructor (only the base vtable store is left). */

/* @implements 0x107c30 us _ZN2Fj11C2DRaceInfoD0Ev
   WHAT IT DOES: The race info comment deleting destructor. */

/* @implements 0x107c58 us C2DRaceInfo8f_101f44
   WHAT IT DOES: The race info comment's piece type number. */

/* @implements 0x107c60 us C2DRaceInfo8f_101f4c
   WHAT IT DOES: How many sprites the race info comment shows. */

/* @implements 0x107c68 us C2DRaceInfo8f_101f64
   WHAT IT DOES: Where the race info comment keeps a sprite's handle. */

/* @implements 0x107c78 us C2DRaceInfo8f_101f6c
   WHAT IT DOES: The name of the race info comment's sprite set. */

/* @implements 0x107c84 us C2DRaceInfo8f_101f54
   WHAT IT DOES: The handle of one of the race info comment's sprites. */

/* @implements 0x107cac us _ZN2Fj16C2DRaceInfoStartD1Ev
   WHAT IT DOES: The start banner destructor (only the base vtable store is left). */

/* @implements 0x107cbc us _ZN2Fj16C2DRaceInfoStartD0Ev
   WHAT IT DOES: The start banner deleting destructor. */

/* @implements 0x107ce4 us C2DRaceInfoStart8f_101f44
   WHAT IT DOES: The start banner's piece type number. */

/* @implements 0x107cec us C2DRaceInfoStart8f_101f4c
   WHAT IT DOES: How many sprites the start banner shows. */

/* @implements 0x107cf4 us C2DRaceInfoStart8f_101f64
   WHAT IT DOES: Where the start banner keeps a sprite's handle. */

/* @implements 0x107d04 us C2DRaceInfoStart8f_101f6c
   WHAT IT DOES: The name of the start banner's sprite set. */

/* @implements 0x107d10 us C2DRaceInfoStart8f_101f54
   WHAT IT DOES: The handle of one of the start banner's sprites. */

/* @implements 0x107d38 us _ZN2Fj17C2DRaceInfoFinishD1Ev
   WHAT IT DOES: The finish banner destructor (only the base vtable store is left). */

/* @implements 0x107d48 us _ZN2Fj17C2DRaceInfoFinishD0Ev
   WHAT IT DOES: The finish banner deleting destructor. */

/* @implements 0x107d70 us C2DRaceInfoFinish8f_101f44
   WHAT IT DOES: The finish banner's piece type number. */

/* @implements 0x107d78 us C2DRaceInfoFinish8f_101f4c
   WHAT IT DOES: How many sprites the finish banner shows. */

/* @implements 0x107d80 us C2DRaceInfoFinish8f_101f64
   WHAT IT DOES: Where the finish banner keeps a sprite's handle. */

/* @implements 0x107d90 us C2DRaceInfoFinish8f_101f6c
   WHAT IT DOES: The name of the finish banner's sprite set. */

/* @implements 0x107d9c us C2DRaceInfoFinish8f_101f54
   WHAT IT DOES: The handle of one of the finish banner's sprites. */

/* @implements 0x107dc4 us _ZN2Fj10C2DInfoWinD1Ev
   WHAT IT DOES: The info window destructor (only the base vtable store is left). */

/* @implements 0x107dd4 us _ZN2Fj10C2DInfoWinD0Ev
   WHAT IT DOES: The info window deleting destructor. */

/* @implements 0x107dfc us C2DInfoWin8f_101f44
   WHAT IT DOES: The info window's piece type number. */

/* @implements 0x107e04 us C2DInfoWin8f_101f4c
   WHAT IT DOES: How many sprites the info window shows. */

/* @implements 0x107e0c us C2DInfoWin8f_101f64
   WHAT IT DOES: Where the info window keeps a sprite's handle. */

/* @implements 0x107e1c us C2DInfoWin8f_101f6c
   WHAT IT DOES: The name of the info window's sprite set. */

/* @implements 0x107e28 us C2DInfoWin8f_101f54
   WHAT IT DOES: The handle of one of the info window's sprites. */

/* @implements 0x107e50 us _ZN2Fj10C2DAllTimeD1Ev
   WHAT IT DOES: The all-time records table destructor (only the base vtable store is left). */

/* @implements 0x107e60 us _ZN2Fj10C2DAllTimeD0Ev
   WHAT IT DOES: The all-time records table deleting destructor. */

/* @implements 0x107e88 us C2DAllTime8f_101f44
   WHAT IT DOES: The all-time records table's piece type number. */

/* @implements 0x107e90 us C2DAllTime8f_101f4c
   WHAT IT DOES: How many sprites the all-time records table shows. */

/* @implements 0x107e98 us C2DAllTime8f_101f64
   WHAT IT DOES: Where the all-time records table keeps a sprite's handle. */

/* @implements 0x107ea8 us C2DAllTime8f_101f6c
   WHAT IT DOES: The name of the all-time records table's sprite set. */

/* @implements 0x107eb4 us C2DAllTime8f_101f54
   WHAT IT DOES: The handle of one of the all-time records table's sprites. */
