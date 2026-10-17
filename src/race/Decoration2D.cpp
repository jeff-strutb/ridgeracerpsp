/* The race 2D decoration base object file (retail 0x101998 to 0x101f7c). Fj::C2DDecorationBase
   is the common part of the race overlay's pieces (lap counter, position, timers, the course
   map and the like): it binds a piece to the race and to its sprite group, runs the start
   animation that slides a piece in when the race begins, shows or hides all its sprites, and
   gives the time and rectangle helpers the pieces share. The file also holds the blinking
   used by the pieces that pulse. */

/* The VFPU's sine (of a quarter turn per unit). */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

static inline float VSin(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvsin.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}

/* The race in progress (null outside a race): its clock in milliseconds at +48. */
struct RaceInfo {
    char m0[48];
    int clock;
};
extern RaceInfo *D_2407fc;

/* The race the piece belongs to: its clock in frames at +136. */
struct Race {
    char m0[136];
    int clock;
};
int f_0f6468(Race *r);
int f_0f63a8(Race *r);

/* The sprite group the piece draws with. */
struct Group;
void f_04c248(Group *g, int sprite, unsigned char on);
int f_04d224(Group *g, int count, int *n);

/* A pulse for blinking pieces: the time it has run and the race clock it last saw, and two
   brightness levels between 0.4 and 1.0 (one cycling every 1.8 s, one every 1.2 s). */
struct Blink {
    int time;
    int phase;
    int clock;
    float slow;
    float fast;
};

/* @implements 0x101998 us f_101998
   WHAT IT DOES: Resets a pulse, taking the race clock when a race is running. */
void f_101998(Blink *b)
{
    b->clock = 0;
    b->time = 0;
    b->phase = 0;
    b->slow = 0;
    b->fast = 0;
    if (D_2407fc && D_2407fc->clock > 0)
        b->clock = D_2407fc->clock;
}

/* @implements 0x1019cc us f_1019cc
   WHAT IT DOES: Advances a pulse by the time the race clock moved (50 ms when no race clock
   runs) and works out its two brightness levels from the elapsed 50 ms steps: a sine over 90
   steps and one over 60, each scaled to between 0.4 and 1.0. */
void f_1019cc(Blink *b)
{
    int step = 50;
    int n;

    if (D_2407fc && D_2407fc->clock > 0) {
        step = D_2407fc->clock - b->clock;
        b->clock = D_2407fc->clock;
    }
    b->time += step;
    b->phase += step;
    n = b->phase / 50;
    b->slow = VSin((float)(n % 90) * 0.034906585f * 0.63661975f) * 0.6f + 0.4f;
    b->fast = VSin((float)(n % 60) * 0.10471976f * 0.63661975f) * 0.6f + 0.4f;
}

namespace Fj {

/* A rectangle given by its corner and size. */
struct Rect {
    float x, y, w, h;
};

/* A sprite corner: its position and texture coordinates. */
struct Corner {
    float x, y, u, v;
};

class C2DDecorationBase {
public:
    virtual ~C2DDecorationBase() {}
    virtual int f_101f44() { return 0; }
    virtual int f_101f4c() { return 0; }
    virtual int f_101f54(int i) { return 0; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual void Draw() = 0;
    virtual int f_101b54();
    virtual void f_101f5c() {}
    virtual int *f_101f64(int i) { return 0; }
    virtual int f_101f6c() { return 0; }
    virtual void f_101f74(float t) {}
    void f_101c70(unsigned char on);
    void f_101cf4(int t, int *min, int *sec, int *ms);
    void f_101da4(Corner *c, const Rect *r);
    int f_101e38();

    Race *race;
    Group *group;
    unsigned char on;
    int state;
    int start;
};

}

using namespace Fj;

/* @implements 0x101b1c us C2DDecorationBase8f_101b1c
   WHAT IT DOES: Binds the piece to its sprite group and race, sets its sprites up and resets
   its start animation. */
int C2DDecorationBase::f_101b1c(Group *g, Race *r)
{
    group = g;
    race = r;
    f_101e38();
    start = 0;
    state = 0;
    return 1;
}

/* @implements 0x101b54 us C2DDecorationBase8f_101b54
   WHAT IT DOES: Steps the start animation. Nothing happens without a race or while the race
   says so. The piece waits (state 0) until the race's countdown reaches 16, then (state 1)
   notes the race clock and (state 2) slides in over 120 clock steps of 50, then stays in
   (state 3). Returns 1 while the animation has run, 0 while waiting. */
int C2DDecorationBase::f_101b54()
{
    int t;
    float f;

    if (!D_2407fc)
        return 0;
    if (f_0f6468(race))
        return 0;
    switch (state) {
    case 0:
        if (f_0f63a8(race) >= 16)
            state = 1;
        return 0;
    case 1:
        start = race->clock;
        state = 2;
    case 2:
        t = (race->clock - start) / 50;
        f = t * 0.008333334f;
        if (t >= 120) {
            state = 3;
            f = 1.0f;
        }
        f_101f74(f);
        return 1;
    default:
        return 1;
    }
}

/* @implements 0x101c70 us C2DDecorationBase8f_101c70
   WHAT IT DOES: Shows or hides every sprite of the piece. */
void C2DDecorationBase::f_101c70(unsigned char show)
{
    int i;

    on = show;
    for (i = 0; i < f_101f4c(); i++) {
        Group *g = group;

        f_04c248(g, f_101f54(i), on);
    }
}

/* @implements 0x101cf4 us C2DDecorationBase8f_101cf4
   WHAT IT DOES: Splits a time in thirds of a millisecond into minutes (below 100), seconds
   and milliseconds. */
void C2DDecorationBase::f_101cf4(int t, int *min, int *sec, int *ms)
{
    int total = t / 3;
    int s = total / 1000;
    int m = s / 60;

    *ms = total - s * 1000;
    *sec = s - m * 60;
    *min = m - m / 100 * 100;
}

/* @implements 0x101da4 us C2DDecorationBase8f_101da4
   WHAT IT DOES: Turns a rectangle into the four corners of a sprite strip, texture
   coordinates running over the rectangle's size. */
void C2DDecorationBase::f_101da4(Corner *c, const Rect *r)
{
    c[0].x = r->x;
    c[0].y = r->y;
    c[1].x = r->x + r->w;
    c[1].y = r->y;
    c[2].x = r->x;
    c[2].y = r->y + r->h;
    c[3].x = r->x + r->w;
    c[3].y = r->y + r->h;
    c[0].u = 0;
    c[0].v = 0;
    c[1].u = r->w;
    c[1].v = 0;
    c[2].u = 0;
    c[2].v = r->h;
    c[3].u = r->w;
    c[3].v = r->h;
}

/* @implements 0x101e38 us C2DDecorationBase8f_101e38
   WHAT IT DOES: Sets the piece's sprites up: allocates as many sprites in its group as the
   piece has and stores each one's handle in the piece. Returns 0 when the piece has none. */
int C2DDecorationBase::f_101e38()
{
    int n;
    int first;
    int i;

    Group *g;

    if (!f_101f6c() || !f_101f64(0))
        return 0;
    n = 0;
    g = group;
    first = f_04d224(g, f_101f6c(), &n);
    for (i = 0; i < n; i++)
        *f_101f64(i) = first + i;
    return 1;
}

/* @implements 0x101f0c us _ZN2Fj17C2DDecorationBaseD1Ev
   WHAT IT DOES: The decoration base destructor (resets the vtable). */

/* @implements 0x101f1c us _ZN2Fj17C2DDecorationBaseD0Ev
   WHAT IT DOES: The decoration base deleting destructor. */

/* @implements 0x101f44 us C2DDecorationBase8f_101f44
   WHAT IT DOES: The base piece's answer to a query: none (0). */

/* @implements 0x101f4c us C2DDecorationBase8f_101f4c
   WHAT IT DOES: The number of sprites a base piece shows: none. */

/* @implements 0x101f54 us C2DDecorationBase8f_101f54
   WHAT IT DOES: The handle of a base piece's sprite: none. */

/* @implements 0x101f5c us C2DDecorationBase8f_101f5c
   WHAT IT DOES: Nothing (a step the pieces may add). */

/* @implements 0x101f64 us C2DDecorationBase8f_101f64
   WHAT IT DOES: Where a base piece keeps a sprite handle: nowhere (0). */

/* @implements 0x101f6c us C2DDecorationBase8f_101f6c
   WHAT IT DOES: The number of sprites a base piece allocates: none. */

/* @implements 0x101f74 us C2DDecorationBase8f_101f74
   WHAT IT DOES: Nothing (the base piece does not animate in). */
