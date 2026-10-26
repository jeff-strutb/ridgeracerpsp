/* The course road line queries (retail 0x0fa900 to 0x0fd3fc, the object file after the
   sound voice manager): wrappers that the map manager's course areas (D_23c820 + 12240,
   CourseAreas) answer for the cars. They read the road distance of a car, sample the road
   line in front of it and return the gap between two boxes along one axis. */

extern "C" {
/* CourseAreas members (src/race/CourseAreas.cpp) reached through the areas pointer. */
int f_0e2690(void *areas, int i);
void f_0e3a74(void *areas, int i, short *a, short *b);
float f_0e2260(void *areas, int i);
}

/* The map manager object (D_23c820); the course areas sit at +12240. */
extern char D_23c820[];

/* A box with the two float bounds this object file reads (offsets 72 and 104). */
struct Box {
    char m0[72];
    float m72;
    char m76[28];
    float m104;
};

/* @implements 0x0fc2e0 us f_0fc2e0
   WHAT IT DOES: An empty function. */
extern "C" void f_0fc2e0(void)
{
}

/* @implements 0x0fcec0 us f_0fcec0
   WHAT IT DOES: Sets the bits 0x700 in the flag word at +7692 of the object. */
struct FlagHolder {
    char m0[7692];
    int flags;
};

extern "C" void f_0fcec0(FlagHolder *p)
{
    p->flags |= 0x700;
}

/* @draft 0x0fafe8 us f_0fafe8
   WHAT IT DOES: The signed gap between two boxes along one axis, plus a margin of 0.5. The
   flag picks which box's upper bound is taken first. Not yet byte-exact. */
extern "C" float f_0fafe8(void *unused, const Box *a, const Box *b, int flag)
{
    float r;
    if (!flag)
        r = b->m72 - a->m104;
    else
        r = a->m72 - b->m104;
    return r + 0.5f;
}

/* @implements 0x0fa900 us f_0fa900
   WHAT IT DOES: Returns the road line's index for the sum of two distances (the course areas
   map the sum to a road point). */
extern "C" int f_0fa900(int unused, int a, int b)
{
    char *base = D_23c820;
    return f_0e2690(base + 12240, a + b);
}

/* @draft 0x0fb194 us f_0fb194
   WHAT IT DOES: Looks up the road line's two short values for a point (one picked by the sign
   of x), and returns x over their scaled value, or the sign of x when that value is not
   positive. Not yet byte-exact. */
extern "C" float f_0fb194(float x, int i)
{
    short a, b;
    char *base = D_23c820;
    short v;
    float d;

    f_0e3a74(base + 12240, i, &a, &b);
    v = x >= 0.0f ? b : a;
    d = (float)v * 0.001f - 2.0f;
    if (d > 0.0f)
        return x / d;
    return x < 0.0f ? -1.0f : 1.0f;
}

/* @draft 0x0fb364 us f_0fb364
   WHAT IT DOES: Looks up the same road line pair as f_0fb194 and returns x times a scaled
   value of it, or zero when that value is negative. Not yet byte-exact. */
extern "C" float f_0fb364(float x, int i)
{
    short a, b;
    char *base = D_23c820;
    short v;
    float d;

    f_0e3a74(base + 12240, i, &a, &b);
    v = x >= 0.0f ? b : a;
    d = (float)v * 0.001f - 2.0f;
    float r = 0.0f;
    if (!(d < 0.0f))
        r = x * d;
    return r;
}

/* The per-car block at +7092 of the map manager, as the road queries read it. */
struct CarBlock {
    char m0[16];
    float m16;
    char m20[20];
    int m40;
    int m44;
    char m48[8];
    float m56;
    char m60[40];
    float m100;
};

struct MapOwner {
    void *vt;
    char m4[7088];
    CarBlock car;
};

struct GameTop {
    char m0[6248];
    float m6248;
};

extern char D_245ecc[];

/* @draft 0x0fc138 us f_0fc138
   WHAT IT DOES: When the car block is idle (both counters zero) and its level is above 0.2,
   it stores the game's scaled value into the car block and calls the owner's virtual step with
   1, but only when the lateral value lies in the band the table sets. Not yet byte-exact. */
extern "C" void f_0fc138(MapOwner *o)
{
    CarBlock *c = &o->car;
    float L;

    if (c->m40 || c->m44)
        return;
    if (!(0.2f < c->m100))
        return;
    L = c->m56;
    if (0.0f < L) {
        if (!(1.5f < L))
            return;
        if (!(L < 4.0f))
            return;
    } else {
        if (!(-10.0f < L))
            return;
    }
    char *g = D_245ecc;
    c->m16 = (*(GameTop **)(g - 11268))->m6248;
    ((void (**)(void *, int))o->vt)[30](o, 1);
}
