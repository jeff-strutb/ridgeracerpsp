/* The race 2D meters object file (retail 0x107edc to 0x10996c): the speed and engine meters
   of the race overlay, each a Fj::C2DMeterBase piece (itself a Fj::C2DDecorationBase): the
   analog dial, the digital readout, and the Pac-Man and Rally-X themed meters of those
   special cars. A meter takes its layout from the car's meter type and draws its needle,
   digits or icons each frame. */

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
    char m116[24];
    float speed;
    char m144[8];
    float rpm;
    float redline;
    float maxRpm;
    int gear;
    char m168[8];
    float boost;
    char m180[12];
    int m192;
    struct Player *player;
};

/* The player's settings: the meter's lamp cell (nonzero picks cell 34) and whether the
   meter is lit (0 lights it). */
struct Player {
    char m0[2112];
    int lamp;
    char m2116[5704];
    int dark;
};
extern RaceInfo *D_2407fc;

/* The race the piece belongs to: its clock in frames at +136. */
struct Race {
    char m0[136];
    int clock;
};
int f_0f63c0(Race *r);
int f_0937f0();

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

/* A rectangle given by its corner and size. */
struct Rect {
    float x, y, w, h;
};

void f_04bf6c(Group *g, int sprite, Corner *c);
void f_04c104(Group *g, int sprite, int cell);

/* A bar's cell strip: the number of cells at +12. */
struct Bar {
    int m0[3];
    int count;
    int m16[5];
};
void f_04c130(Group *g, int sprite, Bar *b, int cell);
void f_04c1c8(Group *g, int sprite, Rgba c);
void f_04c248(Group *g, int sprite, unsigned char on);
void f_04c278(Group *g, int sprite, float x, float y);
void f_04c3c8(Group *g, int sprite, float x, float y);
void f_04c668(Group *g, int sprite, float r, float gr, float b, float a);
void f_04d16c(Group *g, int sprite);
void f_04d19c(Group *g, int sprite);

/* The sprite set names. */
extern const char *D_1d7778;
extern const char *D_1d777c;
extern const char *D_1d7780;
extern const char *D_1d7784;

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
    void f_101da4(Corner *c, const Rect *r);
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
    /* Sets one sprite's brightness, fully opaque. */
    void Tint(int i, float v)
    {
        Group *g = group;

        f_04c668(g, f_101f54(i), v, v, v, 1.0f);
    }
    /* Picks one sprite's cell. */
    void Cell(int i, int cell)
    {
        Group *g = group;

        f_04c104(g, f_101f54(i), cell);
    }
    /* The start animation has not finished. */
    bool Starting() { return state < 3; }

    Race *race;
    Group *group;
    unsigned char on;
    int state;
    int start;
};

/* The parts every meter adds: its type number, how many sprites it shows, where it keeps
   their handles and the name of its sprite set. */
#define METER(TYPE, COUNT, NAME)                                      \
    virtual int f_101f44() { return TYPE; }                           \
    virtual int f_101f4c() { return COUNT; }                          \
    virtual int f_101f54(int i) { return *f_101f64(i); }              \
    virtual int *f_101f64(int i) { return &sprite[i]; }               \
    virtual const char *f_101f6c() { return NAME; }

/* A meter type's layout: a flag (the analog meter's second needle, or -1 when the digital
   meter has no shift lamp) and its sprite rectangles. */
struct MeterLayout {
    int flag;
    Rect r[15];
};
extern MeterLayout D_1d5fe8[];

/* Each meter type's bar, and the bars' cell strips dark and lit. */
extern int D_1d7720[];
extern Bar D_1d74e0[];
extern Bar D_1d7600[];

/* A meter: the car's meter type and its sprites. */
class C2DMeterBase : public C2DDecorationBase {
public:
    void f_107edc(int s, int on);
    void f_107fb0(int s, int on);
    void f_1080d8(int s, int on, float x);

    int type;
    unsigned char m28;
};

class C2DAnalogMeter : public C2DMeterBase {
public:
    METER(16, 10, D_1d7778)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_1088ec(Corner *c, const Rect *r, float a);

    int sprite[10];
};

class C2DDigitalMeter : public C2DMeterBase {
public:
    METER(17, 10, D_1d777c)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_108f64(int on, float t);

    int sprite[10];
};

class C2DPacmanMeter : public C2DMeterBase {
public:
    METER(16, 10, D_1d7780)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);

    int sprite[10];
};

class C2DRallyXMeter : public C2DMeterBase {
public:
    METER(16, 5, D_1d7784)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);
    void f_1095fc(float x, float y, float t);

    int sprite[5];
};

}

using namespace Fj;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* @draft 0x107edc us C2DMeterBase8f_107edc
   WHAT IT DOES: Shows a meter lamp lit or dark: places the sprite at the lamp's rectangle
   for that state and picks the matching cell from the strip of two. */
void C2DMeterBase::f_107edc(int s, int on)
{
    Corner c[4];
    float x = D_1d5fe8[type].r[2 + on].x;
    float y = D_1d5fe8[type].r[2 + on].y;
    float w = D_1d5fe8[type].r[2 + on].w;
    float h = D_1d5fe8[type].r[2 + on].h;
    float u0, v0;

    c[0].x = c[2].x = x;
    c[0].y = c[1].y = y;
    c[1].x = c[3].x = x + w;
    c[2].y = c[3].y = y + h;
    u0 = w * on;
    v0 = 0;
    c[0].u = c[2].u = u0;
    c[0].v = c[1].v = v0;
    c[1].u = c[3].u = u0 + w;
    c[2].v = c[3].v = h + v0;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(s), c);
    }
}

/* @implements 0x107fb0 us C2DMeterBase8f_107fb0
   WHAT IT DOES: Shows a digit (the last decimal digit of n) in a meter sprite: places the
   sprite at the digit's rectangle and picks the digit's cell from the strip of ten. */
void C2DMeterBase::f_107fb0(int s, int n)
{
    Corner c[4];
    float u0, v0;

    n %= 10;
    f_101da4(c, &D_1d5fe8[type].r[3 + n]);
    u0 = 0;
    v0 = D_1d5fe8[type].r[3 + n].h * n;
    c[0].u = c[2].u = u0;
    c[0].v = c[1].v = v0;
    c[1].u = c[3].u = D_1d5fe8[type].r[3 + n].w + u0;
    c[2].v = c[3].v = v0 + D_1d5fe8[type].r[3 + n].h;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(s), c);
    }
}

/* @draft 0x1080d8 us C2DMeterBase8f_1080d8
   WHAT IT DOES: Shows a three-digit number (n below 1000) in three meter sprites from s on,
   the digits step apart from the readout's corner, each taking its 16-pixel cell from the
   strip of ten. */
void C2DMeterBase::f_1080d8(int s, int n, float step)
{
    int d[3];
    Corner c[4];
    int i;

    n %= 1000;
    d[0] = n / 100;
    d[1] = n % 100 / 10;
    d[2] = n % 10;
    for (i = 0; i < 3; i++) {
        float x = D_1d5fe8[type].r[1].x + i * step;
        float y = D_1d5fe8[type].r[1].y;
        float v = d[i] * 16.0f;

        c[0].x = x;
        c[0].y = y;
        c[0].u = 0;
        c[0].v = v;
        c[1].x = x + 16.0f;
        c[1].y = y;
        c[1].u = 16.0f;
        c[1].v = v;
        c[2].x = x;
        c[2].y = y + 16.0f;
        c[2].u = 0;
        c[2].v = v + 16.0f;
        c[3].x = x + 16.0f;
        c[3].y = y + 16.0f;
        c[3].u = 16.0f;
        c[3].v = v + 16.0f;
        {
            Group *g = group;

            f_04bf6c(g, f_101f54(s + i), c);
        }
    }
}

/* @implements 0x1082c4 us C2DAnalogMeter8f_101b1c
   WHAT IT DOES: Sets the analog meter up for the car's meter type: places the dial and the
   needle hub, places the second needle (or hides it when the type has none), sets the lamps
   (lit unless the player turned them off), the needle and the digits, and hides the
   shift lamp. */
int C2DAnalogMeter::f_101b1c(Group *g, Race *r)
{
    Corner c[4];
    int lit = 0;

    C2DDecorationBase::f_101b1c(g, r);
    type = f_0f63c0(race);
    if (D_2407fc)
        lit = D_2407fc->player->dark == 0;
    f_101da4(c, &D_1d5fe8[type].r[0]);
    {
        Group *gr = group;

        f_04bf6c(gr, f_101f54(3), c);
    }
    f_101da4(c, &D_1d5fe8[type].r[11]);
    {
        Group *gr = group;

        f_04bf6c(gr, f_101f54(6), c);
    }
    if (!D_1d5fe8[type].flag) {
        Show(2, 0);
    } else {
        f_101da4(c, &D_1d5fe8[type].r[13]);
        {
            Group *gr = group;

            f_04bf6c(gr, f_101f54(2), c);
        }
    }
    f_107edc(5, lit);
    f_107fb0(4, 1);
    f_1080d8(7, 0, 10.0f);
    Show(1, 0);
    return 1;
}

/* @implements 0x1084b0 us C2DAnalogMeter4Draw
   WHAT IT DOES: Nothing to draw here (the sprites draw themselves); returns 1. */
int C2DAnalogMeter::Draw()
{
    return 1;
}

/* @implements 0x1084b8 us C2DAnalogMeter8f_101b54
   WHAT IT DOES: Updates the analog meter each frame once the start animation runs: turns the
   rev needle over its dial range by the engine speed above 1000 rpm (half speed below 1000
   on type 2 dials), turns the boost needle on dials that have one, picks the lamp cell, shows
   the road speed (km/h, or mph when the game says so) and the gear, and blinks the shift lamp
   at the redline (dim below it). */
int C2DAnalogMeter::f_101b54()
{
    Corner c[4];

    if (!C2DDecorationBase::f_101b54())
        return 0;
    {
        float lo = D_1d5fe8[type].r[12].w;
        float hi = D_1d5fe8[type].r[12].h;

        if (D_1d5fe8[type].flag >= 0) {
            float v = D_2407fc->rpm - 1000.0f;
            float a;

            if (D_1d5fe8[type].flag == 2 && v < 0)
                v *= 0.5f;
            a = 1.0f / (D_2407fc->maxRpm - 1000.0f) * (hi - lo);
            a = lo + a * v;
            if (a < 0)
                a += 360.0f;
            a *= 0.017453292f;
            f_1088ec(c, &D_1d5fe8[type].r[11], a);
            {
                Group *g = group;

                f_04bf6c(g, f_101f54(6), c);
            }
            if (D_1d5fe8[type].flag == 1) {
                float m, t;

                v = (D_2407fc->boost + 1.0f) * 0.33333334f;
                lo = D_1d5fe8[type].r[14].w;
                hi = D_1d5fe8[type].r[14].h;
                m = MAX(v, 0.0f);
                t = MIN(m, 1.0f);
                a = t * (hi - lo) + lo;
                if (a < 0)
                    a += 360.0f;
                a *= 0.017453292f;
                f_1088ec(c, &D_1d5fe8[type].r[13], a);
                {
                    Group *g = group;

                    f_04bf6c(g, f_101f54(2), c);
                }
            }
        }
    }
    if (D_2407fc->player->lamp)
        Cell(0, 34);
    else
        Cell(0, 35);
    {
        float k = 0.216f;

        if (f_0937f0())
            k *= 0.6213712f;
        f_1080d8(7, (int)(D_2407fc->speed * k), 10.0f);
    }
    f_107fb0(4, D_2407fc->gear);
    if (D_2407fc->rpm >= D_2407fc->redline) {
        int lit = (race->clock / 50 & 8) == 0;
        float b = lit ? 1.0f : 0.1f;
        float v = b;

        if (!m28) {
            if (b == 0.1f)
                v = 1.0f;
            else
                m28 = 1;
        }
        Tint(3, v);
    } else {
        Tint(3, 0.1f);
        m28 = 0;
    }
    return 0;
}

/* @implements 0x1088ec us C2DAnalogMeter8f_1088ec
   WHAT IT DOES: Builds a needle's corners: the needle rectangle r[0] placed about its pivot
   (r[1]'s corner), turned by the angle a (radians) and moved to the pivot. */
void C2DAnalogMeter::f_1088ec(Corner *c, const Rect *r, float a)
{
    float s, co;
    int i;

    a *= 0.63661975f;
    c[0].x = c[2].x = -r[1].x;
    c[1].x = c[3].x = r[0].w - r[1].x;
    c[0].y = c[1].y = -r[1].y;
    c[2].y = c[3].y = r[0].h - r[1].y;
    c[0].u = c[2].u = 0;
    c[1].u = c[3].u = r[0].w;
    c[0].v = c[1].v = 0;
    c[2].v = c[3].v = r[0].h;
    s = VSin(a);
    co = VCos(a);
    for (i = 0; i < 4; i++) {
        float x = c[i].x;
        float y = c[i].y;

        c[i].x = x * co - y * s;
        c[i].y = x * s + y * co;
        c[i].x += r[0].x;
        c[i].y += r[0].y;
    }
}

/* @implements 0x1089ec us C2DAnalogMeter8f_101f74
   WHAT IT DOES: Fades the meter's ten sprites in with the start animation. */
void C2DAnalogMeter::f_101f74(float t)
{
    int i;

    for (i = 0; i < 10; i++)
        Fade(i, t);
}

/* @implements 0x108a80 us C2DDigitalMeter8f_101b1c
   WHAT IT DOES: Sets the digital meter up for the car's meter type: places the readout,
   sets the lamps (lit unless the player turned them off), the bar and the digits, places
   the shift lamp (or hides it when the type has none) and hides the other indicators. */
int C2DDigitalMeter::f_101b1c(Group *g, Race *r)
{
    Corner c[4];
    int lit = 0;

    C2DDecorationBase::f_101b1c(g, r);
    type = f_0f63c0(race);
    if (D_2407fc)
        lit = D_2407fc->player->dark == 0;
    f_101da4(c, &D_1d5fe8[type].r[0]);
    {
        Group *gr = group;

        f_04bf6c(gr, f_101f54(3), c);
    }
    f_107edc(5, lit);
    f_107fb0(4, 1);
    f_1080d8(7, 0, 10.0f);
    if (D_1d5fe8[type].flag == -1) {
        f_101da4(c, &D_1d5fe8[type].r[11]);
        {
            Group *gr = group;

            f_04bf6c(gr, f_101f54(6), c);
        }
    } else {
        Show(6, 0);
    }
    Show(2, 0);
    Show(1, 0);
    return 1;
}

/* @implements 0x108c4c us C2DDigitalMeter4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DDigitalMeter::Draw()
{
    return 1;
}

/* @draft 0x108c54 us C2DDigitalMeter8f_101b54
   WHAT IT DOES: Updates the digital meter each frame once the start animation runs: fills
   the rev bar by the engine speed over its top speed (clamped to 0..1), picks the lamp cell
   and the bar's strip with it, shows the road speed (km/h, or mph when the game says so) and
   the gear, and blinks the shift lamp at the redline (dim below it).
   Remaining difference (8 words, register choice in the clamp): retail has the product v in
   $f12, the MAX result m in $f2 and the MIN's 1.0 in $f0; here v is in $f2, m in $f12 and
   1.0 in $f2. Diagnosed 2026-11-16 (greg dump, no source change made): global-alloc takes m
   (pseudo 199, preferences $f2 and $f12, the latter through t's copy into $f12 for f_108f64)
   first and gives it $f12, then v (186, preference $f2) gets $f2. Retail's assignment is the
   mirror image, so retail's v carries the $f12 preference instead (source shape not yet
   identified; Pac-Man's `v = MAX(v, 0)` form gives a bc1fl, not retail's two moves). */
int C2DDigitalMeter::f_101b54()
{
    float t;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    {
        float v = D_2407fc->rpm * (1.0f / D_2407fc->maxRpm);
        float m = MAX(v, 0.0f);

        t = MIN(m, 1.0f);
    }
    if (D_2407fc->player->lamp) {
        Cell(0, 34);
        f_108f64(1, t);
    } else {
        Cell(0, 35);
        f_108f64(0, t);
    }
    {
        float k = 0.216f;

        if (f_0937f0())
            k *= 0.6213712f;
        f_1080d8(7, (int)(D_2407fc->speed * k), 10.0f);
    }
    f_107fb0(4, D_2407fc->gear);
    if (D_2407fc->rpm >= D_2407fc->redline) {
        int lit = (race->clock / 50 & 8) == 0;
        float b = lit ? 1.0f : 0.1f;
        float v = b;

        if (!m28) {
            if (b == 0.1f)
                v = 1.0f;
            else
                m28 = 1;
        }
        Tint(3, v);
    } else {
        Tint(3, 0.1f);
        m28 = 0;
    }
    return 0;
}

/* @implements 0x108ed0 us C2DDigitalMeter8f_101f74
   WHAT IT DOES: Fades the meter's ten sprites in with the start animation. */
void C2DDigitalMeter::f_101f74(float t)
{
    int i;

    for (i = 0; i < 10; i++)
        Fade(i, t);
}

/* @implements 0x108f64 us C2DDigitalMeter8f_108f64
   WHAT IT DOES: Fills the digital meter's bar to the fraction t of its cells, from the meter
   type's lit or dark cell strip. */
void C2DDigitalMeter::f_108f64(int on, float t)
{
    Bar *b;

    if (!on)
        b = &D_1d74e0[D_1d7720[type]];
    else
        b = &D_1d7600[D_1d7720[type]];
    {
        Group *g = group;

        f_04c130(g, f_101f54(0), b, (int)(t * b->count));
    }
}

/* @implements 0x10902c us C2DPacmanMeter8f_101b1c
   WHAT IT DOES: Sets the Pac-Man meter up for the car's meter type: places its frame, sets
   the lamps (lit unless the player turned them off), the bar and the digits. */
int C2DPacmanMeter::f_101b1c(Group *g, Race *r)
{
    Corner c[4];
    int lit = 0;

    C2DDecorationBase::f_101b1c(g, r);
    C2DDecorationBase::f_101b1c(g, r);
    type = f_0f63c0(race);
    if (D_2407fc)
        lit = D_2407fc->player->dark == 0;
    f_101da4(c, &D_1d5fe8[type].r[0]);
    {
        Group *gr = group;

        f_04bf6c(gr, f_101f54(4), c);
    }
    f_107edc(9, lit);
    f_107fb0(5, 1);
    f_1080d8(6, 0, 10.0f);
    return 1;
}

/* @implements 0x10912c us C2DPacmanMeter4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DPacmanMeter::Draw()
{
    return 1;
}

/* @draft 0x109134 us C2DPacmanMeter8f_101b54
   WHAT IT DOES: Updates the Pac-Man meter each frame once the start animation runs: raises
   its two rev markers by the engine speed over its top speed (clamped to 0..1, up to 75
   pixels), shows the road speed (km/h, or mph when the game says so) and the gear, and
   blinks the shift lamp at the redline (dim below it).
   Remaining difference (6 words, register choice): the first marker call's table row
   (type * 244 + D_1d5fe8: pseudos 212, 213, 215) is in a2 in retail, a1 here. Diagnosed
   2026-11-16 (sched1/greg dumps, no source change made): sched1 issues the x load into $f12
   (insn 118, the row's last use) ahead of `a1 = f_101f54 result` (insn 117), so the row no
   longer overlaps a1 and local-alloc gives it a1. In retail a1 was still live over the row
   at allocation. The second call (x + 82, no direct $f12 load) matches with the row in v1. */
int C2DPacmanMeter::f_101b54()
{
    float t;

    if (!C2DDecorationBase::f_101b54())
        return 0;
    {
        float v = D_2407fc->rpm * (1.0f / D_2407fc->maxRpm);

        v = MAX(v, 0.0f);
        t = MIN(v, 1.0f);
    }
    {
        Group *g = group;

        f_04c278(g, f_101f54(1), D_1d5fe8[type].r[11].x, D_1d5fe8[type].r[11].y - t * 75.0f);
    }
    {
        Group *g = group;

        f_04c278(g, f_101f54(2), D_1d5fe8[type].r[11].x + 82.0f,
                 D_1d5fe8[type].r[11].y - t * 75.0f);
    }
    {
        float k = 0.216f;

        if (f_0937f0())
            k *= 0.6213712f;
        f_1080d8(6, (int)(D_2407fc->speed * k), 10.0f);
    }
    f_107fb0(5, D_2407fc->gear);
    if (D_2407fc->rpm >= D_2407fc->redline) {
        int lit = (race->clock / 50 & 8) == 0;
        float b = lit ? 1.0f : 0.1f;
        float v = b;

        if (!m28) {
            if (b == 0.1f)
                v = 1.0f;
            else
                m28 = 1;
        }
        Tint(4, v);
    } else {
        Tint(4, 0.1f);
        m28 = 0;
    }
    return 0;
}

/* @implements 0x1093e8 us C2DPacmanMeter8f_101f74
   WHAT IT DOES: Fades the meter's ten sprites in with the start animation. */
void C2DPacmanMeter::f_101f74(float t)
{
    int i;

    for (i = 0; i < 10; i++)
        Fade(i, t);
}

/* @implements 0x10947c us C2DRallyXMeter8f_101b1c
   WHAT IT DOES: Sets the Rally-X meter up: the car's meter type, then its gauge empty at 16. */
int C2DRallyXMeter::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    C2DDecorationBase::f_101b1c(g, r);
    type = f_0f63c0(race);
    f_1080d8(2, 0, 16.0f);
    return 1;
}

/* @implements 0x1094f0 us C2DRallyXMeter4Draw
   WHAT IT DOES: Nothing to draw here; returns 1. */
int C2DRallyXMeter::Draw()
{
    return 1;
}

/* @draft 0x1094f8 us C2DRallyXMeter8f_101b54
   WHAT IT DOES: Updates the Rally-X meter each frame once the start animation runs: fills
   its gauge by the engine speed over its top speed (clamped to 0..1) and shows the road
   speed (km/h, or mph when the game says so). */
int C2DRallyXMeter::f_101b54()
{
    if (!C2DDecorationBase::f_101b54())
        return 0;
    {
        float v = D_2407fc->rpm * (1.0f / D_2407fc->maxRpm);
        float m = MAX(v, 0.0f);
        float t = MIN(m, 1.0f);

        f_1095fc(D_1d5fe8[type].r[11].x, D_1d5fe8[type].r[11].y, t);
    }
    {
        float k = 0.216f;

        if (f_0937f0())
            k *= 0.6213712f;
        f_1080d8(2, (int)(D_2407fc->speed * k), 16.0f);
    }
    return 0;
}

/* @implements 0x1095fc us C2DRallyXMeter8f_1095fc
   WHAT IT DOES: Shows the Rally-X gauge at (x, y): a 126 by 32 sprite whose cell slides
   along its strip by t (0..1, over 315 pixels). */
void C2DRallyXMeter::f_1095fc(float x, float y, float t)
{
    Corner c[4];
    float u0, v0;

    c[0].x = c[2].x = x;
    c[0].y = c[1].y = y;
    c[1].x = c[3].x = x + 126.0f;
    c[2].y = c[3].y = y + 32.0f;
    u0 = t * 315.0f;
    v0 = 0;
    c[0].u = c[2].u = u0;
    c[0].v = c[1].v = v0;
    c[1].u = c[3].u = u0 + 126.0f;
    c[2].v = c[3].v = 32.0f + v0;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(1), c);
    }
}

/* @implements 0x1096a8 us C2DRallyXMeter8f_101f74
   WHAT IT DOES: Fades the meter's five sprites in with the start animation. */
void C2DRallyXMeter::f_101f74(float t)
{
    int i;

    for (i = 0; i < 5; i++)
        Fade(i, t);
}

/* The meters' inline methods, emitted with their vtables. */

/* @implements 0x10973c us _ZN2Fj14C2DAnalogMeterD1Ev
   WHAT IT DOES: The analog meter destructor (only the base vtable store is left). */

/* @implements 0x10974c us _ZN2Fj14C2DAnalogMeterD0Ev
   WHAT IT DOES: The analog meter deleting destructor. */

/* @implements 0x109774 us C2DAnalogMeter8f_101f44
   WHAT IT DOES: The analog meter's piece type number. */

/* @implements 0x10977c us C2DAnalogMeter8f_101f4c
   WHAT IT DOES: How many sprites the analog meter shows. */

/* @implements 0x109784 us C2DAnalogMeter8f_101f64
   WHAT IT DOES: Where the analog meter keeps a sprite's handle. */

/* @implements 0x109794 us C2DAnalogMeter8f_101f6c
   WHAT IT DOES: The name of the analog meter's sprite set. */

/* @implements 0x1097a0 us C2DAnalogMeter8f_101f54
   WHAT IT DOES: The handle of one of the analog meter's sprites. */

/* @implements 0x1097c8 us _ZN2Fj15C2DDigitalMeterD1Ev
   WHAT IT DOES: The digital meter destructor (only the base vtable store is left). */

/* @implements 0x1097d8 us _ZN2Fj15C2DDigitalMeterD0Ev
   WHAT IT DOES: The digital meter deleting destructor. */

/* @implements 0x109800 us C2DDigitalMeter8f_101f44
   WHAT IT DOES: The digital meter's piece type number. */

/* @implements 0x109808 us C2DDigitalMeter8f_101f4c
   WHAT IT DOES: How many sprites the digital meter shows. */

/* @implements 0x109810 us C2DDigitalMeter8f_101f64
   WHAT IT DOES: Where the digital meter keeps a sprite's handle. */

/* @implements 0x109820 us C2DDigitalMeter8f_101f6c
   WHAT IT DOES: The name of the digital meter's sprite set. */

/* @implements 0x10982c us C2DDigitalMeter8f_101f54
   WHAT IT DOES: The handle of one of the digital meter's sprites. */

/* @implements 0x109854 us _ZN2Fj14C2DPacmanMeterD1Ev
   WHAT IT DOES: The Pac-Man meter destructor (only the base vtable store is left). */

/* @implements 0x109864 us _ZN2Fj14C2DPacmanMeterD0Ev
   WHAT IT DOES: The Pac-Man meter deleting destructor. */

/* @implements 0x10988c us C2DPacmanMeter8f_101f44
   WHAT IT DOES: The Pac-Man meter's piece type number. */

/* @implements 0x109894 us C2DPacmanMeter8f_101f4c
   WHAT IT DOES: How many sprites the Pac-Man meter shows. */

/* @implements 0x10989c us C2DPacmanMeter8f_101f64
   WHAT IT DOES: Where the Pac-Man meter keeps a sprite's handle. */

/* @implements 0x1098ac us C2DPacmanMeter8f_101f6c
   WHAT IT DOES: The name of the Pac-Man meter's sprite set. */

/* @implements 0x1098b8 us C2DPacmanMeter8f_101f54
   WHAT IT DOES: The handle of one of the Pac-Man meter's sprites. */

/* @implements 0x1098e0 us _ZN2Fj14C2DRallyXMeterD1Ev
   WHAT IT DOES: The Rally-X meter destructor (only the base vtable store is left). */

/* @implements 0x1098f0 us _ZN2Fj14C2DRallyXMeterD0Ev
   WHAT IT DOES: The Rally-X meter deleting destructor. */

/* @implements 0x109918 us C2DRallyXMeter8f_101f44
   WHAT IT DOES: The Rally-X meter's piece type number. */

/* @implements 0x109920 us C2DRallyXMeter8f_101f4c
   WHAT IT DOES: How many sprites the Rally-X meter shows. */

/* @implements 0x109928 us C2DRallyXMeter8f_101f64
   WHAT IT DOES: Where the Rally-X meter keeps a sprite's handle. */

/* @implements 0x109938 us C2DRallyXMeter8f_101f6c
   WHAT IT DOES: The name of the Rally-X meter's sprite set. */

/* @implements 0x109944 us C2DRallyXMeter8f_101f54
   WHAT IT DOES: The handle of one of the Rally-X meter's sprites. */
