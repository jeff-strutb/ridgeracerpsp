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
int rand(void);
}

/* The race in progress (null outside a race). */
struct RaceInfo {
    char m0[8];
    char *course;
    char m12[20];
    int timeLeft;
    int laps;
    char m40[8];
    int m48;
    char m52[4];
    int mode;
    int cars;
    int m64;
    char m68[16];
    int m84;
    char m88[20];
    int lap;
    int position;
    int m116;
    int m120;
    int m124;
    char m128[4];
    int m132;
    char m136[44];
    float nitro[3];
    int m192;
    struct InfoSub *sub;
    struct Records *rec;
    char m204[16];
    struct CarObj *car;
};
extern RaceInfo *D_2407fc;

/* The race's other record tables: the sub table the info window checks, and the table of
   records (three columns per row) that the info window lists. */
/* A car's record (its map position and the like). */
struct CarObj {
    char m0[76];
    int m76;
    char m80[64];
    float x;
    char m148[4];
    float z;
};
struct InfoSub {
    char m0[144];
    float x;
    char m148[4];
    float z;
    char m156[1952];
    int m2108;
    char m2112[100];
    int m2212;
    char m2216[7836];
    int m10052;
};
struct Records {
    int a[297];
    int b[297];
    int m2376, m2380, m2384, m2388;
    char m2392[12];
    int m2404;
    char m2408[15600];
    int c[297];
};

/* The race object (only its clock is read here). */
struct RaceClock {
    int t;
    int m4;
    char m8[4];
    float lo, hi;
};
struct Race {
    char m0[136];
    RaceClock clk;
};
int f_0f6450(Race *r);
int f_0f6420(Race *r);
int f_0f6438(Race *r);
void f_0f64f4(Race *r, int v);
void f_0e71e4(float s);

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
void f_04c0a8(Group *g, int sprite, int x0, int y0, int x1, int y1);
void f_04c3c8(Group *g, int sprite, float x, float y);
void f_04c278(Group *g, int sprite, float x, float y);
void f_04c668(Group *g, int sprite, float r, float gr, float b, float a);
void f_04d16c(Group *g, int sprite);
void f_04d19c(Group *g, int sprite);

/* The digit sprites' texture rectangles (the ten digits, then the plus and minus signs), and
   the two digit colours (white, red). */
extern const Rgba D_1b065c[];
extern const Rgba D_1b07bc[];
extern const Rgba D_1b084c[];
extern const Rgba D_1b071c[];
extern const float D_1b063c[][4];
extern const float D_1b0aa8[][4];   /* the race info comments' texture rectangles */

/* The info window's panel textures: for each of four panel kinds the rectangle (u, v, width,
   height) on the texture. */
extern float D_1d5f74[][4];

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
    /* Moves one sprite. */
    void Move(int i, float x, float y)
    {
        Group *g = group;

        f_04c3c8(g, f_101f54(i), x, y);
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
    int m60[3];
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

    void f_105fa8(float x, float y);
    void f_106090(float x, float y, int sprite, int n);
    void f_106120(float x, float y, int a, int b);
    void f_10636c(int slot, int value, float *p, int flag);

    int sprite[30];
    int m144;
    int m148;
    int m152;
    int m156;
    int m160;
    int m164;
    int m168;
    int m172;
    int m176;
    int m180;
    bool m184;
    int m188;
    int m192[4];
    float m208, m212, m216, m220;
};

class C2DAllTime : public C2DDecorationBase {
public:
    PIECE(23, 54, D_1d5fe4)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_106e8c(int row, int mn, int sc, int ms, int color, unsigned char show);

    int sprite[54];
    int m240;
    int m244;
    unsigned char m248;
    int m252;
    int m256;
    int m260[3];
};

}

using namespace Fj;

/* Fades and moves a sprite by an expression (evaluated after the sprite is looked up). */
#define FADE(i, a)                                           \
    {                                                        \
        Group *g_ = group;                                   \
        f_04c668(g_, f_101f54(i), 1.0f, 1.0f, 1.0f, a);      \
    }
#define MOVE(i, x, y)                                        \
    {                                                        \
        Group *g_ = group;                                   \
        f_04c3c8(g_, f_101f54(i), x, y);                     \
    }

/* Colours a sprite of a time row by the row of the colour table. */
#define TCOLOR(i, c)                                                       \
    {                                                                      \
        Group *g_ = group;                                                 \
        f_04c668(g_, f_101f54(i), D_1b063c[c][0], D_1b063c[c][1],          \
                 D_1b063c[c][2], D_1b063c[c][3]);                          \
    }

/* Sets the texture rectangle of a sprite. */
#define RECT(i, r)                                           \
    {                                                        \
        Group *g_ = group;                                   \
        f_04c1c8(g_, f_101f54(i), r);                        \
    }

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* The course maps, by course. */
extern const MapInfo D_1b0be4[];

/* @draft 0x101f7c us C2DCourseMap8f_101f7c
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
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
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
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
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
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

/* @implements 0x102254 us C2DCourseMap8f_102254
   WHAT IT DOES: Finds the race's course among the 25 course names and keeps its number for
   the map; returns 1 when found, 0 (printing a debug message) when not or outside a race. */
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

/* @draft 0x102730 us C2DCourseMapNormal8f_101b54
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Updates the normal course map: places the first car's marker (sprite 1, texture
   rectangle 0) at the car's map position; once the race has started (blink) and with two
   or more cars, places the second car's marker (sprite 8): in kind 2 races it is rectangle 1
   and hidden unless that car is set and the race flags it, then blinking with the race
   clock, in other races rectangle 2, shown. Returns 0.
   Remaining difference: not compared in detail; the transcription is complete. */
int C2DCourseMapNormal::f_101b54()
{
    float mx, my;
    int s;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    f_101f7c(D_2407fc->sub->x, D_2407fc->sub->z, &mx, &my);
    f_102190(f_101f54(1), 0, 1, mx, my);
    if (!blink && D_2407fc->sub->m2212 >= 0)
        blink = 1;
    if (!blink)
        return 0;
    if (D_2407fc->cars < 2)
        return 0;
    f_101f7c(D_2407fc->car->x, D_2407fc->car->z, &mx, &my);
    s = f_101f54(8);
    if (f_0f6438(race) != 2)
        f_102190(s, 2, 1, mx, my);
    else if (D_2407fc->car->m76 == 0 || D_2407fc->m84 == 0)
        f_102190(s, 1, 0, mx, my);
    else
        f_102190(s, 1, ((unsigned)(race->clk.t / 50) >> 3 ^ 1) & 1, mx, my);
    return 0;
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
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
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
    m60[2] = 0;
    m60[1] = 0;
    m60[0] = 0;
    return 1;
}

/* @implements 0x102ebc us C2DNitro4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DNitro::Draw()
{
    return 1;
}

/* @draft 0x102ec4 us C2DNitro8f_101b54
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Steps the nitro gauge. During the start animation it places the three bars
   (f_103138) from the race's nitro levels (scaled by one hundredth) and clears the race's
   word at +140. After it, each bar starts a refill state (m60[i] = 1) when its level reaches
   100; when the race flags a boost on bar i (kind 1 or 2 and i the selected bar) the bar is
   set to state 2 with a random shake offset (0 to 5, minus 2), and a state 2 bar otherwise
   returns to 0; then the bars are placed with their shake offsets and an alpha taken from
   the race (the second value when a boost began, else the first). Returns 0.
   Remaining difference: about 40 percent of the words; the test of the boost kind (1 or 2) is
   merged into one range test here, retail compares the two kinds one after the other. */
int C2DNitro::f_101b54()
{
    int i;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    if (Starting()) {
        for (i = 0; i < 3; i++)
            f_103138(i, D_2407fc->nitro[i] * 0.01f, 0.0f, 0.0f);
        race->clk.m4 = 0;
        return 0;
    }
    float a[3] = { 0.0f, 0.0f, 0.0f };
    float b[3] = { 0.0f, 0.0f, 0.0f };
    int boost = 0;
    RaceClock *clk = &race->clk;
    float lo = clk->lo;
    float hi = clk->hi;

    for (i = 0; i < 3; i++) {
        if (m60[i] == 0) {
            if (D_2407fc->nitro[i] >= 100.0f)
                m60[i] = 1;
        } else if ((D_2407fc->sub->m2108 == 1 || D_2407fc->sub->m2108 == 2) &&
                   i == D_2407fc->sub->m10052) {
            m60[i] = 2;
            boost = 1;
            a[i] = rand() % 6 + -2.0f;
        } else if (m60[i] == 2) {
            m60[i] = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        if (m60[i])
            b[i] = boost ? hi : lo;
        f_103138(i, D_2407fc->nitro[i] * 0.01f, b[i], a[i]);
    }
    return 0;
}

/* @draft 0x103138 us C2DNitro8f_103138
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Places the three sprites of one nitro gauge bar (bar i, three bars across 35
   pixels apart from x 6, y at 139 plus an offset): the first sprite is drawn scaled by the
   bar's fill (70 percent size, the width scaled by it too), the other two at 70 percent
   size and fixed width, each from the bar's texture and placement table; then the last
   sprite is given the bar's alpha.
   Remaining difference: the order of the corner stores of each quad (the values and the loop agree). */
void C2DNitro::f_103138(int i, float scale, float alpha, float dy)
{
    int idx[9] = { 3, 4, 5, 7, 8, 6, 0, 1, 2 };
    float tbl[3][4] = {
        { 0.0f, 0.0f, 48.0f, 23.0f },
        { -3.0f, 0.0f, 54.0f, 23.0f },
        { -20.0f, -15.0f, 88.0f, 54.0f },
    };
    Corner c[3][4];
    float x = i * 35.0f + 6.0f;
    float y = dy + 139.0f;
    float x0, y0, x1, y1;
    int k;

    x0 = x + tbl[0][0] * 0.7f;
    y0 = y + tbl[0][1] * 0.7f;
    x1 = x0 + tbl[0][2] * 0.7f * scale;
    y1 = y0 + tbl[0][3] * 0.7f;
    c[0][0].x = c[0][2].x = x0;
    c[0][0].y = c[0][1].y = y0;
    c[0][3].x = c[0][1].x = x1;
    c[0][3].y = c[0][2].y = y1;
    c[0][2].u = c[0][0].u = 0;
    c[0][0].v = c[0][1].v = 0;
    c[0][3].u = c[0][1].u = tbl[0][2] * scale;
    c[0][2].v = c[0][3].v = tbl[0][3];
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(idx[i]), c[0]);
    }
    for (k = 1; k < 3; k++) {
        x0 = x + tbl[k][0] * 0.7f;
        y0 = y + tbl[k][1] * 0.7f;
        c[k][0].x = c[k][2].x = x0;
        c[k][0].y = c[k][1].y = y0;
        c[k][2].u = c[k][0].u = 0;
        c[k][0].v = c[k][1].v = 0;
        c[k][3].u = c[k][1].u = tbl[k][2];
        c[k][2].v = c[k][3].v = tbl[k][3];
        c[k][3].x = c[k][1].x = x0 + tbl[k][2] * 0.7f;
        c[k][3].y = c[k][2].y = y0 + tbl[k][3] * 0.7f;
        {
            Group *g = group;

            f_04bf6c(g, f_101f54(idx[i + 3 * k]), c[k]);
        }
    }
    {
        Group *g = group;

        f_04c668(g, f_101f54(idx[i + 6]), 1.0f, 1.0f, 1.0f, alpha);
    }
}

/* @implements 0x103438 us C2DNitro8f_101f74
   WHAT IT DOES: Fades the nitro gauge's frame and bar sprites (3 to 8) to alpha t. */
void C2DNitro::f_101f74(float t)
{
    Fade(3, t);
    Fade(4, t);
    Fade(5, t);
    Fade(7, t);
    Fade(8, t);
    Fade(6, t);
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

/* @implements 0x103820 us C2DPosition8f_103820
   WHAT IT DOES: Shows the position as sprites: the player's place n (two digits, the tens sprite
   hidden when zero, the units one pulled left by 10) and the number of cars of (two digits,
   the tens sprite hidden when zero, the units one pulled left by 6), each digit with its
   texture rectangle (the place from a second table when m is set). */
void C2DPosition::f_103820(int n, int of, int m)
{
    int tens;
    int units;

    n %= 100;
    of %= 100;
    tens = n / 10;
    units = n % 10;
    if (tens == 0) {
        Show(4, 0);
        MOVE(5, -10.0f, 0.0f);
    } else {
        Show(4, 1);
        MOVE(5, 0.0f, 0.0f);
    }
    if (m == 0) {
        RECT(4, D_1b07bc[tens]);
        RECT(5, D_1b07bc[units]);
    } else {
        RECT(4, D_1b084c[units]);
        RECT(5, D_1b084c[units]);
    }
    tens = of / 10;
    units = of % 10;
    if (tens == 0) {
        Show(2, 0);
        MOVE(3, -6.0f, 0.0f);
    } else {
        Show(2, 1);
        MOVE(3, 0.0f, 0.0f);
    }
    RECT(2, D_1b071c[tens]);
    RECT(3, D_1b071c[units]);
}

/* @implements 0x103e9c us C2DPositionTour4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DPositionTour::Draw()
{
    return 1;
}

/* @draft 0x103ea4 us C2DPositionTour8f_101b54
   WHAT IT DOES: Once the start animation is over, shows the tour position: while the player
   is behind the lap count of the leader (0x0f6420) the two ring sprites pulse with the clock's
   low phase and the position blinks; otherwise they are plain white. Returns 0.
   Remaining difference: retail keeps 0.5 in two saved FPRs (f20 and a copy in f22, used for
   the add) and 1.0 in f21 in the pulse arm (frame +4 bytes, one more saved FPR); here the
   copy is folded away (416 bytes against 436). */
int C2DPositionTour::f_101b54()
{
    if (!C2DDecorationBase::f_101b54())
        return 0;
    if (Starting())
        return 0;
    int blink = 0;
    RaceInfo *ri = D_2407fc;
    float b = 0.5f;

    if (ri->position < f_0f6420(race)) {
        float half = b;

        b = race->clk.lo * b + half;
        blink = 1;
        {
            Group *g = group;

            f_04c668(g, f_101f54(4), b, b, b, 1.0f);
        }
        {
            Group *g = group;

            f_04c668(g, f_101f54(5), b, b, b, 1.0f);
        }
    } else {
        {
            Group *g = group;

            f_04c668(g, f_101f54(4), 1.0f, 1.0f, 1.0f, 1.0f);
        }
        {
            Group *g = group;

            f_04c668(g, f_101f54(5), 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
    f_103820(D_2407fc->position + 1, D_2407fc->cars, blink);
    return 0;
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

/* @draft 0x104184 us C2DLap8f_104184
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Shows the lap counter as sprites at a horizontal position: the label sprites
   (0 and 1) placed at the position (the first one 40 pixels right of it), the tens sprite (4)
   hidden, the lap digit (sprite 5, 10 pixels left) with its texture rectangle and the number
   of laps digit (sprite 3, 6 further left) with its rectangle, the second tens sprite (2)
   hidden.
   Remaining difference: not compared in detail; the transcription is complete. */
void C2DLap::f_104184(int n, int of, float x)
{
    float y = 0.0f;

    n %= 10;
    of %= 10;
    MOVE(0, x + 40.0f, y);
    MOVE(1, x, y);
    Show(4, 0);
    RECT(5, D_1b07bc[n % 10]);
    MOVE(5, x + -10.0f, y);
    Show(2, 0);
    RECT(3, D_1b071c[of % 10]);
    x += -6.0f;
    MOVE(3, x, y);
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

/* @implements 0x1044fc us C2DRaceInfo8f_101b54
   WHAT IT DOES: The race info comment's step: picks the comment for the race state (the goal
   comments by result in mode 2, the mode 4 comment, or comment 1 while the +192 flag is set,
   blinking every 8 fiftieths of the clock) and shows or hides its sprite. Returns 0. */
int C2DRaceInfo::f_101b54()
{
    if (!C2DDecorationBase::f_101b54())
        return 0;
    RaceInfo *ri = D_2407fc;
    if (ri->mode == 2) {
        if (ri->m64 == 0) {
            f_104620(0);
        } else if (ri->m64 == 1) {
            if (ri->position == 0)
                f_104620(3);
            else
                f_104620(4);
        }
        shown = 1;
    } else if (ri->mode == 4) {
        f_104620(2);
        shown = 1;
    } else if (ri->m192 != 0) {
        f_104620(1);
        shown = (((unsigned)(race->clk.t / 50) >> 3) ^ 1) & 1;
    } else {
        shown = 0;
    }
    {
        Group *g = group;

        f_04c248(g, f_101f54(0), shown);
    }
    return 0;
}

/* @draft 0x104620 us C2DRaceInfo8f_104620
   WHAT IT DOES: Places comment kind's sprite centred on the screen (240, 136): its size from
   the table row, its texture rectangle the strip row kind (28 pixels a row, 200 wide).
   Remaining difference (24 words): the order of the sixteen corner stores (retail x1, y1,
   u0, v0, u1, v1, x0, y0 first) and the table row in a2 rather than v1. */
void C2DRaceInfo::f_104620(int kind)
{
    Corner c[4];
    float w = D_1b0aa8[kind][2];
    float h = D_1b0aa8[kind][3];
    float x = 240.0f - w * 0.5f;
    float y = 136.0f - h * 0.5f;
    float v0 = kind * 28;
    float v1 = kind * 28 + 28;

    c[2].x = c[0].x = x;
    c[1].y = c[0].y = y;
    c[0].u = c[2].u = 0.0f;
    c[0].v = c[1].v = v0;
    c[1].x = c[3].x = x + w;
    c[2].y = c[3].y = y + h;
    c[1].u = c[3].u = 200.0f;
    c[2].v = c[3].v = v1;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(0), c);
    }
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

/* @implements 0x1047ec us C2DRaceInfoStart8f_101b54
   WHAT IT DOES: Runs the start banner from the race clock (the milliseconds since the start,
   negative before it): in each 3000 millisecond step one sprite fades in while the one
   before it fades out and slides, so the count down numbers (sprites 3, 2, 1) follow each
   other from -10500 and the start sign (sprite 0) fades in from the start, then out and away
   by 4500, when it is hidden. Returns 0. */
int C2DRaceInfoStart::f_101b54()
{

    if (!C2DDecorationBase::f_101b54())
        return 0;
    if (D_2407fc->m48 > 0) {
        if ((float)D_2407fc->m48 < 3000.0f) {
            Show(1, 0);
            float f = (float)(D_2407fc->m48 - D_2407fc->m48 / 3000 * 3000);
            f /= 1500.0f;
            if (f >= 1.0f)
                f = 1.0f;
            Show(0, 1);
            FADE(0, f);
        } else if ((float)D_2407fc->m48 < 4500.0f) {
            float f = (float)(D_2407fc->m48 - D_2407fc->m48 / 3000 * 3000);
            f /= 1500.0f;
            if (f >= 1.0f)
                f = 1.0f;
            FADE(0, 1.0f - f);
            MOVE(0, 0.0f, -(f * 16.0f));
        } else if ((float)D_2407fc->m48 >= 4500.0f) {
            Show(0, 0);
        }
    } else if ((float)D_2407fc->m48 > -1500.0f) {
        float f = (float)(D_2407fc->m48 / 3000 * 3000 - D_2407fc->m48);
            f /= 1500.0f;
        FADE(1, f);
        MOVE(1, 0.0f, -(1.0f - f) * 16.0f);
    } else if (D_2407fc->m48 >= -2999) {
        Show(2, 0);
    } else if ((float)D_2407fc->m48 > -4500.0f) {
        Show(1, 1);
        float f = (float)(D_2407fc->m48 / 3000 * 3000 - D_2407fc->m48);
            f /= 1500.0f;
        FADE(1, 1.0f - f);
        MOVE(1, 0.0f, f * 16.0f);
        FADE(2, f);
        MOVE(2, 0.0f, -(1.0f - f) * 16.0f);
    } else if (D_2407fc->m48 >= -5999) {
        Show(3, 0);
    } else if ((float)D_2407fc->m48 > -7500.0f) {
        Show(2, 1);
        float f = (float)(D_2407fc->m48 / 3000 * 3000 - D_2407fc->m48);
            f /= 1500.0f;
        FADE(2, 1.0f - f);
        MOVE(2, 0.0f, f * 16.0f);
        FADE(3, f);
        MOVE(3, 0.0f, -(1.0f - f) * 16.0f);
    } else if (D_2407fc->m48 >= -8999) {
    } else if ((float)D_2407fc->m48 > -10500.0f) {
        Show(3, 1);
        float f = (float)(D_2407fc->m48 / 3000 * 3000 - D_2407fc->m48);
            f /= 1500.0f;
        FADE(3, 1.0f - f);
        MOVE(3, 0.0f, f * 16.0f);
    }
    return 0;
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
    m192[3] = 0;
    m180 = 0;
    m184 = 0;
    m144 = 0;
    m188 = 0;
    m192[2] = 0;
    m192[1] = 0;
    m192[0] = 0;
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

/* @draft 0x10522c us C2DInfoWin8f_101b54
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Steps the info window (the lap record list, two panels that slide in over the
   race) after the start animation. It flags the record selection that changed in m176 (bit 0
   for the best, bit 1 for the second table) and remembers which in m192[3]; then, by state
   m148: 0 waits for a flagged change (or the start of a race of kind 4 or 5), picks the next
   record row and its two panels' places (49,287 and 120,272, or the reverse for the second
   table) and sets them; 1 shows the panels, sets the disc scale to 0 and grows the frame
   with the time that passed (state 2); 2 does the same until the frame is 60 wide (state 3);
   3 slides the panels up the screen until one is above 188 (state 4); 4 waits 180 time
   units, hides the line sprites (state 5) or, while waiting, draws the lines of the
   records; 5 slides the panels back until one is above 128 (state 6); 6 shrinks the frame
   away and returns to state 0. Every call ends by scrolling the background strip
   (f_105fa8). Returns 0.
   Remaining difference: 30 of 863 words, same size. (1) At the five sprite lookups that feed
   f_106090 sched1 puts li a1,N before move a0,this; retail has the reverse. Both moves have
   equal priority, and the tie goes to the one with more dependants (a1, which the outer
   call's a1 copy output-depends on), so it is an RTL difference not yet found. (2) Small
   register choices (the copy of h in state 6 is t0 here, v0 in retail; the second record
   line's y in f1/f0). (3) The jump table must be followed in .rodata by the piece names
   ("course", "label_timelimit", ...), which this file does not define yet. */
int C2DInfoWin::f_101b54()
{
    float p[2];
    int t;
    int w;
    int h;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    if (m160 != D_2407fc->rec->m2384 || m164 != D_2407fc->rec->m2376) {
        m176 |= 1;
        if (!m192[3])
            m192[3] = 1;
    }
    if (m160 != D_2407fc->rec->m2388 || m164 != D_2407fc->rec->m2380) {
        m176 |= 2;
        if (!m192[3])
            m192[3] = 2;
    }
    switch (m148) {
    case 0:
        if (f_0f6438(race) == 2 && (m176 & 1) && D_2407fc->mode != 2) {
            if (m160 == 0 && m164 == 0)
                m192[0] = D_2407fc->rec->c[0];
            m168 = D_2407fc->rec->a[m160 * 3 + m164];
            m208 = 49.0f;
            m212 = 287.0f;
            m216 = 120.0f;
            m220 = 272.0f;
            f_106090(m208, m212, f_101f54(2), 5);
            f_106090(m216, m220, f_101f54(3), 4);
            m164 = D_2407fc->rec->m2376;
            m180 = 1;
            if (m164 == 0)
                m160++;
            m192[m164] = D_2407fc->rec->c[m160 * 3 + m164];
            m148 = 1;
            m176 = 0;
            break;
        }
        if ((m176 & 3) == 3 && D_2407fc->mode != 2 &&
            (f_0f6438(race) == 1 || f_0f6438(race) == 3 || f_0f6438(race) == 4 ||
             f_0f6438(race) == 5)) {
            if (m192[3] != 1) {
                m168 = D_2407fc->rec->a[m160 * 3 + m164];
                m172 = D_2407fc->rec->b[m160 * 3 + m164];
                m208 = 40.0f;
                m212 = 302.0f;
                m216 = 58.0f;
                m220 = 272.0f;
                f_106090(m208, m212, f_101f54(2), 5);
                f_106090(m216, m220, f_101f54(3), 4);
                m164 = D_2407fc->rec->m2376;
                m180 = 1;
            } else {
                m168 = D_2407fc->rec->a[m160 * 3 + m164];
                m172 = D_2407fc->rec->b[m160 * 3 + m164];
                m208 = 58.0f;
                m212 = 272.0f;
                m216 = 40.0f;
                m220 = 302.0f;
                f_106090(m208, m212, f_101f54(2), 5);
                f_106090(m216, m220, f_101f54(3), 4);
                m164 = D_2407fc->rec->m2380;
                m180 = 0;
            }
            if (m164 == 0)
                m160++;
            m148 = 1;
            m176 = 0;
            m192[3] = 0;
            break;
        }
        if (!m184 && (f_0f6438(race) == 4 || f_0f6438(race) == 5) &&
            !D_2407fc->sub->m2212) {
            m180 = 2;
            m208 = 49.0f;
            m212 = 287.0f;
            m216 = 120.0f;
            m220 = 272.0f;
            f_106090(m208, m212, f_101f54(2), 5);
            f_106090(m216, m220, f_101f54(3), 4);
            m184 = 1;
            m148 = 1;
        }
        break;
    case 1:
        m152 = D_2407fc->m48 / 50;
        Show(2, 1);
        Show(3, 1);
        m156 = 0;
        {
            Group *gr = group;

            f_04c0a8(gr, f_101f54(2), 10, 162, 110, 262);
        }
        {
            Group *gr = group;

            f_04c0a8(gr, f_101f54(3), 10, 162, 110, 262);
        }
        Fade(0, 0.5f);
        f_0e71e4(0.0f);
        f_0f64f4(race, 1);
        m148 = 2;
        /* fall through */
    case 2:
        {
            int now = D_2407fc->m48 / 50;

            m156 += now - m152;
            m152 = now;
        }
        t = m156 * 2;
        w = t;
        if (t > 60)
            w = 60;
        h = t;
        if (t > 60)
            h = 60;
        if (m156 >= 31) {
            m148 = 3;
            w = 60;
            h = 60;
        }
        {
            Group *gr = group;

            f_04c0a8(gr, f_101f54(0), 60 - w, 212 - w, h + 60, h + 212);
        }
        Show(0, 1);
        f_0e71e4((float)h / 60.0f);
        break;
    case 3:
        {
            int now = D_2407fc->m48 / 50;
            float d = (float)(now - m152) * 2;

            m152 = now;
            m212 -= d;
            m220 -= d;
        }
        {
            float v = m212;

            if (m180)
                v = m220;
            if (v < 188.0f) {
                m148 = 4;
                m156 = 0;
                break;
            }
        }
        f_106090(m208, m212, f_101f54(2), 5);
        f_106090(m216, m220, f_101f54(3), 4);
        break;
    case 4:
        {
            int now = D_2407fc->m48 / 50;

            m156 += now - m152;
            m152 = now;
        }
        if (m156 > 180) {
            if (m180 == 2) {
                Show(29, 0);
                Show(11, 0);
            } else if (m180 == 3) {
                Show(29, 0);
            } else {
                int i;

                if (f_0f6438(race) == 2)
                    m188 = m168;
                for (i = 0; i < 20; i++)
                    Show(9 + i, 0);
            }
            m148 = 5;
        } else {
            if (m180 == 2) {
                p[0] = m208 + 20.0f;
                p[1] = m212;
                f_106120(p[0], p[1], 1, f_0f6420(race));
            } else if (m180 == 3) {
                p[0] = m216 + 25.0f;
                p[1] = m220;
                f_106120(p[0], p[1], 0, 0);
            } else if (f_0f6438(race) == 2) {
                int n = D_2407fc->rec->m2404;
                int d;

                p[0] = m208 + 20.0f;
                p[1] = m212 - 8.0f;
                d = m168 - m192[(m164 + n - 1) % n];
                if (d < 0)
                    f_10636c(0, d, p, 1);
                else
                    f_10636c(0, d, p, 0);
                p[1] = m212 + 16.0f;
                f_10636c(1, m168, p, 0);
            } else {
                p[0] = m208 + 20.0f;
                p[1] = m212;
                f_10636c(0, m168 - m172, p, 0);
            }
        }
        break;
    case 5:
        {
            int now = D_2407fc->m48 / 50;
            float d = (float)(now - m152) * 2;

            m152 = now;
            m212 -= d;
            m220 -= d;
        }
        {
            float v = m220;

            if (m180)
                v = m212;
            if (v < 128.0f) {
                m148 = 6;
                m156 = 0;
                Show(2, 0);
                Show(3, 0);
                break;
            }
        }
        f_106090(m208, m212, f_101f54(2), 5);
        f_106090(m216, m220, f_101f54(3), 4);
        break;
    case 6:
        {
            int now = D_2407fc->m48 / 50;

            m156 += now - m152;
            m152 = now;
        }
        t = m156 * 2;
        w = t;
        if (t > 60)
            w = 60;
        h = t;
        if (t > 60)
            h = 60;
        if (m156 >= 31) {
            m148 = 0;
            Show(0, 0);
            h = 60;
            w = 60;
        }
        f_0e71e4((float)(60 - h) / 60.0f);
        {
            Group *gr = group;

            f_04c0a8(gr, f_101f54(0), w, w + 152, 120 - h, 272 - h);
        }
        break;
    }
    f_105fa8(10.0f, 162.0f);
    return 0;
}

/* @draft 0x105fa8 us C2DInfoWin8f_105fa8
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Scrolls the info window's background strip: advances the scroll position by 2
   (wrapping at 120) and places the 100 pixel square sprite 0 at the position, its texture
   rectangle starting at 120 minus the scroll. */
void C2DInfoWin::f_105fa8(float x, float y)
{
    Corner c[4];
    float s = 100.0f;
    float v0, v1;
    int t = (m144 + 2) % 120;

    v0 = 120.0f - t;
    v1 = v0 + s;
    m144 = t;
    c[2].x = c[0].x = x;
    c[1].y = c[0].y = y;
    c[0].u = c[2].u = 0.0f;
    c[0].v = c[1].v = v0;
    c[1].x = c[3].x = x + s;
    c[2].y = c[3].y = y + s;
    c[1].u = c[3].u = s;
    c[2].v = c[3].v = v1;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(0), c);
    }
}

/* @draft 0x106090 us C2DInfoWin8f_106090
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Places a 24 pixel square sprite at a position with the texture row n of a strip
   of 24 pixel rows (the texture rectangle from row n to row n + 1). */
void C2DInfoWin::f_106090(float x, float y, int sprite, int n)
{
    Corner c[4];
    float s = 24.0f;
    float v0 = n * s;
    float v1 = (n + 1) * s;

    c[2].x = c[0].x = x;
    c[1].y = c[0].y = y;
    c[0].u = c[2].u = 0.0f;
    c[0].v = c[1].v = v0;
    c[1].x = c[3].x = x + s;
    c[2].y = c[3].y = y + s;
    c[1].u = c[3].u = s;
    c[2].v = c[3].v = v1;
    f_04bf6c(group, sprite, c);
}

/* @draft 0x106120 us C2DInfoWin8f_106120
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Draws a panel's name tag at a position (offset 52 left and 25 up): the tag sprite
   (29) gets its corners and texture rectangle from the table row of the panel kind b (b - 1
   clamped to 0 to 3). For kind a = 1 it also shows the number sprite (11) with the texture
   rectangle of the digit b, 2 right and 16 below the tag, in red.
   Remaining difference: not compared in detail; the transcription is complete. */
void C2DInfoWin::f_106120(float x, float y, int a, int b)
{
    int k = b - 1;
    float x0, y0, u0, v0, u1, v1, x1, y1;
    Corner c[4];

    if (k < 0)
        k = 0;
    if (k > 3)
        k = 3;
    x0 = x - 52.0f;
    y0 = y - 25.0f;
    Show(29, 1);
    u0 = D_1d5f74[k][0];
    x1 = x0 + D_1d5f74[k][2];
    y1 = y0 + D_1d5f74[k][3];
    u1 = u0 + D_1d5f74[k][2];
    v0 = D_1d5f74[k][1];
    v1 = v0 + D_1d5f74[k][3];
    c[0].x = x0;
    c[0].y = y0;
    c[0].u = u0;
    c[0].v = v0;
    c[1].x = x1;
    c[1].y = y0;
    c[1].u = u1;
    c[1].v = v0;
    c[2].x = x0;
    c[2].y = y1;
    c[2].u = u0;
    c[2].v = v1;
    c[3].x = x1;
    c[3].y = y1;
    c[3].u = u1;
    c[3].v = v1;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(29), c);
    }
    if (a == 1) {
        Show(11, 1);
        RECT(11, D_1b065c[b]);
        MOVE(11, x0 + 2.0f, y0 + 16.0f);
        {
            Group *g = group;

            f_04c668(g, f_101f54(11), 1.0f, 0.1f, 0.1f, 1.0f);
        }
    }
}

/* @draft 0x10636c us C2DInfoWin8f_10636c
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Shows a time as sprites for one of the info window's lines (slot 0 to 3, ten
   sprites each from slot * 10): a sign for the first line (plus or minus, the value turned
   positive), then the minutes in two digits (the tens hidden when zero), a colon, the seconds in
   two digits, a point and the milliseconds in three digits, each placed one digit width right
   of the last from the given position and coloured white or red (flag).
   Remaining difference: about a third of the words; the register assignment (retail keeps the sprite set high part in a saved register) and the order of the arguments set for the texture and colour calls. */
void C2DInfoWin::f_10636c(int slot, int value, float *p, int flag)
{
    float x = 0.0f;
    int d[3];
    int mn, sc, ms;
    int s, i;
    int base = slot * 10;

    if (slot == 0) {
        s = f_101f54(base + 11);
        if (value < 0) {
            f_04c1c8(group, s, D_1b065c[11]);
            value = -value;
        } else {
            f_04c1c8(group, s, D_1b065c[10]);
        }
        f_04c248(group, s, 1);
        f_04c278(group, s, p[0] + x, p[1]);
        f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
        s++;
    }
    x = 11.0f;
    f_101cf4(value, &mn, &sc, &ms);
    mn %= 100;
    sc %= 100;
    ms %= 1000;
    d[0] = mn / 10;
    d[1] = mn % 10;
    s = f_101f54(base + 12);
    if (d[0]) {
        f_04c248(group, s, 1);
        f_04c1c8(group, s, D_1b065c[d[0]]);
        f_04c278(group, s, p[0] + x, p[1]);
        x += 11.0f;
        f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
        s++;
    } else {
        f_04c248(group, s, 0);
    }
    s = f_101f54(base + 13);
    f_04c248(group, s, 1);
    f_04c1c8(group, s, D_1b065c[d[1]]);
    f_04c278(group, s, p[0] + x, p[1]);
    f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
    x += 11.0f;
    s = f_101f54(base + 9);
    f_04c248(group, s, 1);
    f_04c278(group, s, p[0] + x, p[1]);
    f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
    d[0] = sc / 10;
    d[1] = sc % 10;
    x += 7.0f;
    s = f_101f54(base + 14);
    for (i = 0; i < 2; i++) {
        f_04c248(group, s, 1);
        f_04c1c8(group, s, D_1b065c[d[i]]);
        f_04c278(group, s, p[0] + x, p[1]);
        x += 11.0f;
        f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
        s++;
    }
    s = f_101f54(base + 10);
    f_04c248(group, s, 1);
    f_04c278(group, s, p[0] + x, p[1]);
    f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
    d[0] = ms / 100;
    d[1] = ms % 100 / 10;
    d[2] = ms % 10;
    x += 7.0f;
    s = f_101f54(base + 16);
    for (i = 0; i < 3; i++) {
        f_04c248(group, s, 1);
        f_04c1c8(group, s, D_1b065c[d[i]]);
        f_04c278(group, s, p[0] + x, p[1]);
        x += 11.0f;
        f_04c668(group, s, D_1b063c[flag][0], D_1b063c[flag][1], D_1b063c[flag][2],
                 D_1b063c[flag][3]);
        s++;
    }
}

/* @draft 0x106a5c us C2DAllTime8f_101b1c
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
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
    m260[0] = 0;
    m244 = 0;
    m252 = 0;
    m256 = -1;
    m260[2] = 0;
    m260[1] = 0;
    return 1;
}

/* @implements 0x106bd4 us C2DAllTime4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DAllTime::Draw()
{
    return 1;
}

/* The pieces' inline methods, emitted with their vtables. */

/* @draft 0x106bdc us C2DAllTime8f_101b54
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Updates the all-time records table once the start animation is over: shows the
   record time of the race clock in row 1; tracks when the lap count changes (blinking row 0,
   the lap time, for 120 time units after a lap, from the lap's start clock); shows the lap
   time in row 0 and the time left in row 2 (zero when out of time, hidden past six
   minutes); notes the best lap times by lap and which is the current best; and shows the
   three best times in rows 3 to 5, the best one in the highlight colour. Returns 0.
   Remaining difference: scheduling only (the race pointer load and the first call's argument order). */
int C2DAllTime::f_101b54()
{
    int min, sec, ms;
    int i;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    if (Starting())
        return 0;
    f_101cf4(D_2407fc->m132, &min, &sec, &ms);
    f_106e8c(1, min, sec, ms, 0, 1);
    if (m252 != D_2407fc->m124) {
        if (m252) {
            m248 = 1;
            m240 = race->clk.t;
        }
        m252 = D_2407fc->m124;
    }
    if ((m240 > 0) & ((race->clk.t - m240) / 50 < 120))
        m248 = ((unsigned)(race->clk.t / 50) >> 3 ^ 1) & 1;
    else
        m248 = 1;
    f_101cf4(m252, &min, &sec, &ms);
    f_106e8c(0, min, sec, ms, 0, m248);
    f_101cf4(D_2407fc->timeLeft, &min, &sec, &ms);
    if (min < 6) {
        if (D_2407fc->timeLeft < 0)
            min = sec = ms = 0;
        f_106e8c(2, min, sec, ms, 0, 1);
    } else {
        f_106e8c(2, min, sec, ms, 0, 0);
    }
    if (m244 != D_2407fc->lap) {
        m260[m244] = D_2407fc->m120;
        if (D_2407fc->m124 == D_2407fc->m120)
            m256 = m244;
        m244 = D_2407fc->lap;
    }
    m260[D_2407fc->lap] = D_2407fc->m116;
    for (i = 0; i < 3; i++) {
        f_101cf4(m260[i], &min, &sec, &ms);
        if (m256 == i)
            f_106e8c(i + 3, min, sec, ms, 1, 1);
        else
            f_106e8c(i + 3, min, sec, ms, 0, 1);
    }
    return 0;
}

/* @draft 0x106e8c us C2DAllTime8f_106e8c
   DRAFT: complete transcription, not byte-exact (see the remaining difference).
   WHAT IT DOES: Shows one row of the all-time records table (row 0 to 5, nine sprites each from
   row * 9): its two background sprites, then a time as sprites: the minutes in two digits
   (the tens hidden when zero), the seconds in two digits and the milliseconds in three, each
   with its texture rectangle and the colour of the given row of the colour table. Rows other
   than the third show blank glyphs (11) in place of the digits of a time that is all zero.
   Remaining difference: most words; the register assignment and the order of the scheduling around the sprite lookups differ. */
void C2DAllTime::f_106e8c(int row, int mn, int sc, int ms, int color, unsigned char show)
{
    int d[3];
    int base = row * 9;
    int s;
    int i;

    mn %= 100;
    sc %= 100;
    ms %= 1000;
    Show(base, show);
    s = base;
    TCOLOR(s++, color);
    Show(s, show);
    TCOLOR(s, color);
    s = base + 2;
    d[0] = mn / 10;
    d[1] = mn % 10;
    if (row != 2 && mn == 0) {
        if ((sc | ms) == 0)
            d[1] = 11;
    }
    f_04c1c8(group, f_101f54(s), D_1b065c[d[0]]);
    Show(s, d[0] ? show : 0);
    TCOLOR(s++, color);
    f_04c1c8(group, f_101f54(s), D_1b065c[d[1]]);
    Show(s, show);
    TCOLOR(s, color);
    s = base + 4;
    d[0] = sc / 10;
    d[1] = sc % 10;
    if (row != 2 && mn == 0) {
        if ((sc | ms) == 0) {
            d[0] = 11;
            d[1] = 11;
        }
    }
    for (i = 0; i < 2; i++) {
        f_04c1c8(group, f_101f54(s + i), D_1b065c[d[i]]);
        Show(s + i, show);
        TCOLOR(s + i, color);
    }
    s = base + 6;
    d[0] = ms / 100;
    d[1] = ms % 100 / 10;
    d[2] = ms % 10;
    if (row != 2 && mn == 0) {
        if ((sc | ms) == 0) {
            d[0] = 11;
            d[1] = 11;
            d[2] = 11;
        }
    }
    for (i = 0; i < 3; i++) {
        f_04c1c8(group, f_101f54(s + i), D_1b065c[d[i]]);
        Show(s + i, show);
        TCOLOR(s + i, color);
    }
}

/* @implements 0x107564 us C2DAllTime8f_101f74
   WHAT IT DOES: Fades the time table's digit sprites to alpha t: for each of the nine
   columns, the rows at 0, 9, 27, 36 and 45 (row 18 is left alone). */
void C2DAllTime::f_101f74(float t)
{
    for (int i = 0; i < 9; i++) {
        Fade(i, t);
        Fade(i + 9, t);
        Fade(i + 27, t);
        Fade(i + 36, t);
        Fade(i + 45, t);
    }
}

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

/* The three labels below keep a rectangle literal each; the object file ends its read only
   data with those literals, after the jump table, so they are placed last here. */

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

/* @implements 0x103c6c us C2DPosition8f_101f74
   WHAT IT DOES: Fades the position display's six sprites to alpha t. */
void C2DPosition::f_101f74(float t)
{
    Fade(0, t);
    Fade(1, t);
    Fade(2, t);
    Fade(3, t);
    Fade(4, t);
    Fade(5, t);
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
