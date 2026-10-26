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

struct Record8 {
    float x;
    float y;
};

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
    char m60[32];
    float m92;
    float m96;
    float m100;
    char m104[12];
    float m116;
    char m120[436];
    int m556;
    int m560;
};

struct EightBlock {
    char m0[8];
    float m8;
};

struct MapOwner {
    void *vt;
    char m4[6884];
    float m6888;
    char m6892[200];
    CarBlock car;
    char m7656[36];
    int flags;
    char m7696[300];
    EightBlock e;
    char m8008[1920];
    float m9928;
    char m9932[184];
    char *recs;
};

extern char *D_245ecc; /* the player's car */

/* @implements 0x0fc138 us f_0fc138
   WHAT IT DOES: When the car block is idle (both counters zero) and its level is above 0.2,
   it stores the player's car's value at +6248 into the car block and calls the owner's virtual step with
   1, but only when the lateral value lies in the band the table sets. The value is the float at
   +6248 of the player's car (D_245ecc). */
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
    c->m16 = *(float *)(D_245ecc + 6248);
    ((void (**)(void *, int))o->vt)[30](o, 1);
}

/* @draft 0x0fc1fc us f_0fc1fc
   WHAT IT DOES: When the car block is in state 1 and idle, sets its value to plus or minus 0.9
   from the sign of its two bounds' sum and a latch, then calls the owner's virtual step with 1.
   Not yet byte-exact. */
extern "C" void f_0fc1fc(MapOwner *o)
{
    CarBlock *c = &o->car;
    float s, v;

    if (c->m556 != 1)
        return;
    if (c->m40 || c->m44)
        return;
    s = c->m92 + c->m96;
    if (!(s < 0.0f)) {
        if (c->m560 == 1) {
            if (0.2f < s) {
                c->m560 = 0;
                v = -0.9f;
            } else {
                v = 0.9f;
            }
        } else {
            v = c->m560 ? 0.9f : -0.9f;
        }
    } else {
        int a2 = c->m560;
        if (a2 == 0 && s < -0.2f) {
            a2 = 1;
            c->m560 = 1;
        }
        v = a2 ? 0.9f : -0.9f;
    }
    c->m16 = v;
    ((void (**)(void *, int))o->vt)[30](o, 1);
}

/* @draft 0x0fced0 us f_0fced0
   WHAT IT DOES: Updates the owner's flag word from the car's height against a scaled value of
   the owner's float, sets or clears the 0x700 and 0x3800 bits, calls the owner's virtual step
   62 when the car is low, and then clears the 0x700 bits again when the level is above the
   constant. Not yet byte-exact. */
extern "C" void f_0fced0(MapOwner *o)
{
    unsigned int fl = (unsigned int)o->flags & 0xfffff8ffu & 0xffffc7ffu;
    float ee = o->e.m8 * o->m9928;
    float c116 = o->car.m116;
    unsigned int nfl;

    o->flags = (int)fl;
    if (c116 < ee) {
        o->flags = (int)(fl | 0x700u);
    } else {
        o->flags = (int)fl;
        if (ee + ee <= c116)
            o->flags = (int)(fl | 0x3800u);
        if (ee <= c116)
            ((void (**)(void *))o->vt)[62](o);
    }
    if (!(o->m6888 < 5.5f))
        return;
    nfl = (unsigned int)o->flags;
    if (nfl & 0x700u)
        return;
    o->flags = (int)((nfl | 0x700u) & 0xffffc7ffu);
}

/* The map manager's road records: the owner's record table at +10116, 8 bytes each. */
struct OwnerRecs {
    char m0[10116];
};

/* @draft 0x0fb01c us f_0fb01c
   WHAT IT DOES: Finds a value between -1 and 0 for road record k and the lateral value x: it
   takes the road line's two short values at the record's position and returns the ratio of x
   to the record's span, clamped to the band -1 to 0 (the ratio is taken only once the span is
   positive). Not yet byte-exact. */
extern "C" float f_0fb01c(MapOwner *o, int k, float x)
{
    char *base = D_23c820;
    short a, b;
    float t, den, r;
    Record8 *recs = (Record8 *)((char *)o + 10116) + 0;
    (void)recs;
    t = x - (*(float *)((char *)o + 10116 + k * 8)) * 1.024f;
    f_0e3a74(base + 12240, k, &a, &b);
    if (t < 0.0f) {
        den = (float)a * 0.001f - 1.0f + (*(float *)((char *)o + 10116 + k * 8)) * 1.024f - 2.0f;
    } else {
        den = (float)b * 0.001f - 1.0f - (*(float *)((char *)o + 10116 + k * 8)) * 1.024f - 2.0f;
    }
    r = t / den;
    if (r < -1.0f)
        return -1.0f;
    if (0.0f < r)
        return 0.0f;
    return r;
}

/* @draft 0x0fb240 us f_0fb240
   WHAT IT DOES: Takes the road line's short value at the lower or upper side (chosen by the sign
   of x) for record k, scales it with the record's first float, clamps the sum at zero and
   returns the record's scaled value plus that clamped value times x. Not yet byte-exact. */
extern "C" float f_0fb240(MapOwner *o, int k, float x)
{
    short a, b, v;
    float rec0, d;

    char *base = D_23c820;
    f_0e3a74(base + 12240, k, &a, &b);
    v = x < 0.0f ? a : b;
    rec0 = *(float *)(o->recs + k * 8);
    d = (float)v * 0.001f - 1.0f + rec0 * 1.024f - 2.0f;
    if (d < 0.0f)
        d = 0.0f;
    return rec0 * 1.024f + d * x;
}

/* @draft 0x0fb3f0 us f_0fb3f0
   WHAT IT DOES: The owner's per-mode state step: when the owner has its record table, it sets
   the car's mode, calls the owner's virtual steps for the new mode, and fills the car block's
   smoothed value and its scaled ratio. Not yet byte-exact (control flow is outlined only). */
extern "C" void f_0fb3f0(MapOwner *o, int mode)
{
    CarBlock *c = &o->car;
    float v;

    if (!o->recs)
        return;
    if (mode != 0) {
        if (mode != 1) {
            c->m40 = 1;
            return;
        }
        if (c->m556 != mode) {
            c->m556 = mode;
            ((void (**)(void *, int))o->vt)[27](o, mode);
            ((void (**)(void *, int))o->vt)[28](o, mode);
        }
        v = c->m16 - c->m20[0];
    } else {
        c->m556 = 0;
        ((void (**)(void *, int))o->vt)[29](o, mode);
        v = c->m20[0] - c->m16;
    }
    c->m92 = v;
    if (v < 0.0f)
        c->m96 = -v / (v + 0.0f);
    else
        c->m96 = v / (v + 0.0f);
}

