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
    char m116[76];
    int m192;
    struct Player *player;
};

/* The player's settings: whether the meter is lit (0 lights it). */
struct Player {
    char m0[7820];
    int dark;
};
extern RaceInfo *D_2407fc;

struct Race;
int f_0f63c0(Race *r);

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
    Corner r[15];
};
extern MeterLayout D_1d5fe8[];

/* A meter: the car's meter type and its sprites. */
class C2DMeterBase : public C2DDecorationBase {
public:
    void f_107edc(int s, int on);
    void f_107fb0(int s, int on);
    void f_1080d8(int s, int on, float x);

    int type;
    int m28;
};

class C2DAnalogMeter : public C2DMeterBase {
public:
    METER(16, 10, D_1d7778)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);

    int sprite[10];
};

class C2DDigitalMeter : public C2DMeterBase {
public:
    METER(17, 10, D_1d777c)
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f74(float t);

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

    int sprite[5];
};

}

using namespace Fj;

/* @draft 0x107fb0 us C2DMeterBase8f_107fb0
   WHAT IT DOES: Shows a digit (the last decimal digit of n) in a meter sprite: places the
   sprite at the digit's rectangle and picks the digit's cell from the strip of ten.
   Remaining difference (17 words, scheduling): retail loads the group pointer before the
   sprite lookup's argument moves and stores the corners around them; the store order (found
   by compiling every chain order in one scratch file) and the address arithmetic agree. */
void C2DMeterBase::f_107fb0(int s, int n)
{
    Corner c[4];
    float u0, v0;

    n %= 10;
    f_101da4(c, &D_1d5fe8[type].r[3 + n]);
    u0 = 0;
    v0 = D_1d5fe8[type].r[3 + n].v * n;
    c[0].u = c[2].u = u0;
    c[0].v = c[1].v = v0;
    c[1].u = c[3].u = D_1d5fe8[type].r[3 + n].u + u0;
    c[2].v = c[3].v = v0 + D_1d5fe8[type].r[3 + n].v;
    {
        Group *g = group;

        f_04bf6c(g, f_101f54(s), c);
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

/* @implements 0x108ed0 us C2DDigitalMeter8f_101f74
   WHAT IT DOES: Fades the meter's ten sprites in with the start animation. */
void C2DDigitalMeter::f_101f74(float t)
{
    int i;

    for (i = 0; i < 10; i++)
        Fade(i, t);
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
