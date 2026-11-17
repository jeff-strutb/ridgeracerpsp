/* The course road line queries (retail 0x0fa900 to 0x0fd3fc, the object file after the
   sound voice manager): wrappers that the map manager's course areas (D_23c820 + 12240,
   CourseAreas) answer for the cars. They read the road distance of a car, sample the road
   line in front of it and return the gap between two boxes along one axis. */

#define FLD(p, off) (*(float *)((char *)(p) + (off)))
#define INT(p, off) (*(int *)((char *)(p) + (off)))

union Angle { float a; };

/* Vector helpers (src/system/VectorInline.c). Vec4 is aligned for the vector helpers; V4 is
   the unaligned form the matrix helpers take in the body record code. */
struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct V4 {
    float x, y, z, w;
};

struct Out {
    float f;
    int flag;
};

/* A road record of the owner's table: two floats (the sweep and the first float). */
struct Record8 {
    float f0;
    float f4;
};

/* A road record: the road distance and two shorts (the heading source). */
struct RoadRec {
    float d;
    short s4;
    short s6;
};

/* A box with the two float bounds this object file reads (offsets 72 and 104). */
struct Box {
    char m0[72];
    float m72;
    char m76[28];
    float m104;
};

struct FlagHolder {
    char m0[7692];
    int flags;
};

struct EightBlock {
    char m0[8];
    float m8;
};

/* The per-car block at +7092 of the map manager, as the road queries read it. The union at +20
   is the char view the sweep reads and the float view the road point queries read. */
struct CarBlock {
    int m0;
    char p4[8];
    float m12;
    float m16;
    union {
        char m20[20];
        float m20f;
    };
    int m40;
    int m44;
    char m48[8];
    float m56;
    float m60;
    float m64;
    int m68;
    float m72;
    float m76;
    char m80[8];
    float m88;
    float m92;
    float m96;
    float m100;
    float m104;
    char p108[4];
    float m112;
    float m116;
    char m120[436];
    int m556;
    int m560;
};

/* The map manager object: the virtual table, the floats of the owner, the car block at +7092,
   the flag word at +7692 and the road record table at +10116. */
struct MapOwner {
    void *vt;
    char m4[2124];
    float m2128;
    float m2132;
    char p2136[4];
    float m2140;
    float m2144;
    char p2148[4072];
    int m6220;
    char p6224[12];
    float m6236;
    char p6240[648];
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

/* The map manager object (D_23c820); the course areas sit at +12240. */
extern char D_23c820[];
extern char *D_245ecc; /* the player's car */
extern char *D_2456d0; /* the global body record */

extern "C" {
/* CourseAreas members (src/race/CourseAreas.cpp) reached through the areas pointer. */
int f_0e2690(void *areas, int i);
void f_0e3a74(void *areas, int i, short *a, short *b);
float f_0e2260(void *areas, int i);
void f_0e1ff8(void *areas, float d, float *px, float *py, float *pz);
float f_0c2b7c(void *self);
float f_0c2bd0(float a, float b);
float f_0af380(float *a, float *b);
void f_0fe674(void *o);
void f_0bbcb0(void *q, float a, float b, int c);
void f_0bb480(void *q, int a, int b, int c);
void f_0fe1b8(void *o, void *flags);
void f_0fe2a8(void *o, void *flags);
/* Callees of the body record code, as their other files declare them. */
float f_09a9dc(float x, float z);
void f_09ff44(void *m);
void f_099b98(void *a);
void f_0a082c(void *self, union Angle a, int i, int j);
void f_0a6bf4(void *out, void *m, void *v);
float f_099efc(float x);
float f_09a07c(float x);
/* Vector helpers: the pointer-result form, and the by-value form of the same symbol. */
Vec4 *f_0a5e88(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 f_0a5e88_v(const Vec4 *a, const Vec4 *b) __asm__("f_0a5e88");
Vec4 *f_0a5dc8(Vec4 *d, const Vec4 *b);
Vec4 *f_0a5e1c(Vec4 *d, float s);
float sqrtf(float);
}

/* @implements 0x0fa900 us f_0fa900
   WHAT IT DOES: Returns the road line's index for the sum of two distances (the course areas
   map the sum to a road point). */
extern "C" int f_0fa900(int unused, int a, int b)
{
    char *base = D_23c820;
    return f_0e2690(base + 12240, a + b);
}

/* @draft 0x0fa928 us f_0fa928
   WHAT IT DOES: Places the car on the road line: the road distance from the virtual query
   (slot 54) and its successor give two road points and headings, interpolated by the
   fractional distance; a lateral offset from the car block picks the sideways value, and the
   point is moved by the lateral offset along the heading, then taken into the owner's frame
   through the owner's matrix and passed to the angle helper. Not yet byte-exact. */
extern "C" void f_0fa928(MapOwner *o)
{
    char *base = D_23c820;
    char *areas = base + 12240;
    char *s8 = (char *)o + 5792;
    float x = o->m2144;
    float frac = x - (float)(int)x;
    int k = ((int (**)(void *, int, int))o->vt)[54](o, *(int *)(s8 + 428), 10);
    int j = f_0e2690(areas, k + 1);
    short s0, s2, s4;
    Vec4 pk, pj, d, q, t, tc;
    float h, dh, f20, f22;

    if (o->car.m0 == 0) {
        float rk = *(float *)(o->recs + k * 8);
        float rj = *(float *)(o->recs + j * 8);
        f20 = (rk + (rj - rk) * frac) * 1.024f;
        if (o->car.m12 < 0.0f) {
            f_0e3a74(areas, k, &s2, &s0);
            f_0e3a74(areas, j, &s4, &s0);
            f22 = ((float)s2 + (float)(s4 - s2) * frac) * 0.001f - 1.0f + f20 - 2.0f;
            if (f22 < 0.0f)
                f22 = 0.0f;
            f22 = f22 * o->car.m12 + f20;
        } else {
            f_0e3a74(areas, k, &s0, &s2);
            f_0e3a74(areas, j, &s0, &s4);
            f22 = ((float)s2 + (float)(s4 - s2) * frac) * 0.001f - 1.0f + f20 - 2.0f;
            if (f22 < 0.0f)
                f22 = 0.0f;
            f22 = f22 * o->car.m12 + f20;
        }
    } else {
        if (o->car.m20f < 0.0f) {
            f_0e3a74(areas, k, &s2, &s0);
            f_0e3a74(areas, j, &s4, &s0);
        } else {
            f_0e3a74(areas, k, &s0, &s2);
            f_0e3a74(areas, j, &s0, &s4);
        }
        f22 = ((float)s2 + (float)(s4 - s2) * frac) * 0.001f - 2.0f;
        f22 = f22 * o->car.m20f;
    }

    f_0e1ff8(areas, (float)k, (float *)&pk, &pk.y, &pk.z);
    f_0e1ff8(areas, (float)j, (float *)&pj, &pj.y, &pj.z);
    f_0a5e88(&d, &pj, &pk);
    q = d;
    f_0a5e1c(&q, frac);
    f_0a5dc8(&q, &pk);
    q.y = -q.y;
    q.z = -q.z;
    q.w = 1.0f;
    f_0a5e1c(&q, 0.001f);

    h = f_0e2260(areas, k);
    dh = f_0e2260(areas, j) - h;
    f_099b98(&dh);
    h = h + dh * frac;
    f_099b98(&h);
    {
        float sx = f_09a07c(h);
        q.x = q.x + sx * f22;
    }
    {
        float cz = f_099efc(h);
        q.z = q.z + cz * f22;
    }
    d.x = o->m2128;
    d.y = -o->m2140;
    d.z = -o->m2132;
    d.w = 1.0f;
    f_0a5e1c(&d, 0.001f);
    f_0a5e88(&t, &q, &d);
    tc = t;
    f_0a6bf4(&t, (char *)o + 6320, &tc);
    tc = t;
    f_09a9dc(tc.z, tc.x);
}

/* @draft 0x0fadd4 us f_0fadd4
   WHAT IT DOES: Per-frame update of the global body record (D_2456d0) from the player's car
   and the owner's float state: it derives the record's angle floats, runs the two matrix helpers
   on the vector at +64, and copies the resulting vector into the owner's block at +1120.
   Not yet byte-exact. */
extern "C" void f_0fadd4(char *o)
{
    char *b = o + 5792;
    char *s3 = D_2456d0;
    char *s1 = s3 + 304;
    char *s0 = s3 + 64;
    float z = 0.0f;
    float v, f0, f1, f2;
    struct V4 t;
    union Angle a;

    v = FLD(o, 7212);
    if (v < z)
        v = -v;
    FLD(s3, 504) = v;
    if (v < z) {
        v = -v;
        FLD(s3, 504) = v;
    }
    if (1.5707963705062866f <= v) {
        v = 3.1415927410125732f - v;
        FLD(s3, 504) = v;
    }
    if (!(v < 0.01745329238474369f))
        goto big;
    v = v / 0.01745329238474369f;
    FLD(s3, 504) = v;
    INT(b, 1140) = 0;
    f0 = FLD(b, 1060) * 9.800000190734863f;
    f0 = f0 * v;
    f0 = f0 * 0.20000000298023224f;
    FLD(s3, 508) = f0;
    goto cont;
big:
    f1 = FLD(b, 1060) * 9.800000190734863f;
    INT(b, 1140) = 1;
    f1 = f1 * 0.20000000298023224f;
    FLD(s3, 508) = f1;
cont:
    f2 = FLD(b, 1096);
    if (f2 < 10.0f) {
        f0 = f2 * 0.10000000149011612f;
        f1 = FLD(s3, 508) * f0;
        FLD(s3, 508) = f1;
    }
    INT(s3, 64) = 0;
    INT(s0, 4) = 0;
    INT(s0, 8) = 0;
    INT(s0, 12) = 0;
    f0 = f_09a9dc(FLD(b, 224), FLD(b, 232));
    f0 = -f0;
    FLD(b, 1136) = f0;
    f0 = -FLD(s3, 508);
    f1 = FLD(o, 9724);
    f0 = f0 * f1;
    FLD(s3, 72) = f0;
    f_09ff44(s1);
    a.a = FLD(b, 1136);
    f_099b98(&a);
    f_0a082c(s1, a, 2, 0);
    f_0a6bf4(&t, s1, (struct V4 *)s0);
    *(struct V4 *)(b + 1120) = t;
    f_0a6bf4(&t, b + 672, (struct V4 *)(b + 1120));
    *(struct V4 *)(b + 1120) = t;
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
    r += 0.5f;
    return r;
}

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

/* @implements 0x0fb194 us f_0fb194
   WHAT IT DOES: Looks up the road line's two short values for a point (one picked by the sign
   of x), and returns x over their scaled value, or the sign of x when that value is not
   positive. */
extern "C" float f_0fb194(void *self, int i, float x)
{
    short a, b;
    char *base = D_23c820;
    short v;
    float d;

    f_0e3a74(base + 12240, i, &a, &b);
    v = x >= 0.0f ? b : a;
    d = (float)v;
    d *= 0.001f;
    d -= 2.0f;
    if (d > 0.0f)
        return x / d;
    return x >= 0.0f ? 1.0f : -1.0f;
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

/* @implements 0x0fb364 us f_0fb364
   WHAT IT DOES: Looks up the same road line pair as f_0fb194 and returns x times a scaled
   value of it, or zero when that value is negative. */
extern "C" float f_0fb364(void *self, int i, float x)
{
    short a, b;
    char *base = D_23c820;
    short v;
    float d;

    f_0e3a74(base + 12240, i, &a, &b);
    v = x >= 0.0f ? b : a;
    d = (float)v;
    d *= 0.001f;
    d -= 2.0f;
    float r;
    if (d < 0.0f)
        r = 0.0f;
    else
        r = x * d;
    return r;
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

/* @draft 0x0fb534 us f_0fb534
   WHAT IT DOES: Looks up the road record of the segment's index and the owner's road line
   values for it, and when the lateral value lies inside -2 to 2 it calls the owner's virtual
   step 28 with the sum or difference of the two bounds and writes the result and a flag to the
   out pair; otherwise it zeroes the out pair.
   Remaining difference: register choice only; retail gives s to s1 and out to s0, here the
   other way round (global allocation order of the two parameters). */
extern "C" void f_0fb534(char *o, char *s, char *out)
{
    char *recs = *(char **)(o + 10116);
    float m = FLD(s, 444);
    float t = FLD(recs + INT(s, 428) * 8, 0) * 1.024f - m;
    short a, b;
    float t2, res;

    if (2.0f < t || t < -2.0f) {
        FLD(out, 0) = 0.0f;
        INT(out, 4) = 0;
        return;
    }
    char *base = D_23c820;

    f_0e3a74(base + 12240, INT(s, 428), &a, &b);
    m = FLD(s, 444);
    if (m < 0.0f) {
        t2 = (((float)b * 0.001f - m) - 2.0f) * 0.5f;
        t2 += m;
    } else {
        t2 = (((float)a * 0.001f + m) - 2.0f) * 0.5f;
        t2 -= m;
    }
    res = ((float (*)(void *, int, float))((*(void ***)o)[28]))(o, INT(s, 428), t2);
    FLD(out, 0) = res;
    INT(out, 4) = 1;
}

/* @draft 0x0fb680 us f_0fb680
   WHAT IT DOES: Returns 0 when the owner's first object pointer is null, else 1. Writes the car's
   value at +56 from the two object queries: for each of the two objects, a planar distance
   difference divided by 1/60 gives a ratio, and the value is the ratio when it is nonzero (or the
   negated gap when the ratio is zero and the object's float is under the threshold). Then it
   keeps the two smallest of the ratios in a local triple and the matching object floats at +60
   and +64, counts the inserts at +68 (up to 2), and bubble-sorts the values at +56..+64. Not yet
   byte-exact. */
extern "C" int f_0fb680(void *o)
{
    char *P = (char *)o + 5792;
    CarBlock *car = (CarBlock *)((char *)o + 7092);
    float ar[16];
    Vec4 tmp;
    float mm[3];
    float g, L1, L2, D, q;
    float *tp;
    char *p;
    int i, j, cnt;

    for (i = 0; i < 2; i++) {
        ar[i] = 0.0f;
        ar[i + 8] = 0.0f;
    }
    car->m56 = -3.4028234663852886e+38f;
    if (!*(void **)(P + 1144))
        return 0;

    tp = ar;
    p = P;
    for (i = 0; i < 2; i++, p += 4, tp++) {
        if (!*(void **)(p + 1144))
            break;
        q = ((float (**)(void *, void *, void *, int))(*(void **)o))[24](o, P, *(void **)(p + 1144), 0);
        *tp = (float)*(int *)(p + 1172) * 0.01f - q;

        tmp = f_0a5e88_v((Vec4 *)(P + 32), (Vec4 *)((char *)*(void **)(p + 1144) + 32));
        L1 = sqrtf(tmp.x * tmp.x + tmp.z * tmp.z);

        tmp = f_0a5e88_v((Vec4 *)P, (Vec4 *)*(void **)(p + 1144));
        L2 = sqrtf(tmp.x * tmp.x + tmp.z * tmp.z);

        D = L2 - L1;
        g = D / 0.016666668f;
        if (g < 0.0f)
            tp[8] = *tp / -g;
        if (*(int *)((char *)*(void **)(p + 1144) + 416) != 0)
            continue;
        if (tp[8] != 0.0f)
            car->m56 = tp[8];
        else if (*tp < *(float *)(P + 1096) * 0.8f)
            car->m56 = -g;
    }

    mm[0] = 3.4028234663852886e+38f;
    mm[1] = 3.4028234663852886e+38f;
    cnt = car->m68;
    {
        float *rp = ar + 8;
        void **ap = (void **)(P + 1144);
        for (j = 0; j < 2; j++, rp++, ap++) {
            float rj = *rp;
            if (rj < 2.0f && 0.0f < rj) {
                float cur = mm[1];
                if (rj < cur) {
                    mm[1] = rj;
                    cur = rj;
                    car->m64 = *(float *)((char *)*ap + 444);
                    if (cnt < 2) {
                        cnt = cnt + 1;
                        car->m68 = cnt;
                    }
                }
                if (cur < mm[0]) {
                    float a = car->m64;
                    float b = car->m60;
                    mm[2] = cur;
                    mm[1] = mm[0];
                    mm[0] = cur;
                    car->m64 = b;
                    car->m60 = a;
                }
            }
        }
    }

    if (cnt - 1 > 0) {
        int m = cnt - 1;
        float *s = &car->m56;
        for (i = 0; i < m; i++) {
            for (j = m; j > i; j--) {
                if (s[j + 1] < s[j]) {
                    float tmp = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = tmp;
                }
            }
        }
    }
    return 1;
}

/* @draft 0x0fba10 us f_0fba10
   WHAT IT DOES: Virtual-step query on the owner's car block. The mode word (+68) picks the
   sample count; the car's floats are sampled into a small array, the largest step is found, and
   when the sample lies outside the band (-2, 2) the owner's virtual step 28 is called, its float
   result and a flag are stored to the output. Not yet byte-exact. */
extern "C" int f_0fba10(char *o, struct Out *out)
{
    char *c = o + 7092;
    char *b = o + 5792;
    float tmp[4];
    float best, x, d, f1, f2, f3;
    int mode, i, k, bi, m;
    struct Record8 *rec;
    char *recs;

    mode = INT(c, 68);
    if (mode == 0)
        return 0;
    if (mode == 1) {
        k = INT(b, 428);
        recs = *(char **)(o + 10116);
        rec = (struct Record8 *)(recs + k * 8);
        f2 = FLD(c, 60) - rec->f0 * 1.024f;
        d = f2 < 0.0f ? -f2 : f2;
        if (2.5f < d)
            return 0;
    }
    k = INT(b, 428);
    recs = *(char **)(o + 10116);
    tmp[0] = FLD(c, 72);
    for (i = 0; i < mode; i++)
        tmp[i + 1] = FLD(c, 60 + i * 4);
    m = mode + 1;
    tmp[m] = FLD(c, 76);
    best = 0.0f;
    bi = 0;
    for (i = 0; i < m; i++) {
        d = tmp[i] - tmp[i + 1];
        if (d < 0.0f)
            d = -d;
        if (best < d) {
            best = d;
            bi = i;
        }
    }
    rec = (struct Record8 *)(recs + k * 8);
    f1 = best * 0.5f;
    f3 = tmp[bi];
    f2 = rec->f0 * 1.024f;
    x = f1 + f3 - f2;
    if (!(x < 2.0f))
        goto call;
    if (!(-2.0f < x))
        goto call;
    return 0;
call:
    {
        void **vt = *(void ***)o;
        float r = ((float (*)(void *, int))vt[28])(o, k);
        out->f = r;
        out->flag = 1;
    }
    return 1;
}

/* @draft 0x0fbbe8 us f_0fbbe8
   WHAT IT DOES: Searches the owner's two child lists (+1144 and +1200, two entries each) for a
   child whose float at +444 lies in the band set by the record's span: for each child it calls the
   owner's virtual step 24 and tests the child's scaled mode value against the result, then returns
   the first child that passes the band test, or null. Not yet byte-exact. */
extern "C" char *f_0fbbe8(char *o)
{
    char *b = o + 5792;
    void **vt = *(void ***)o;
    char *recs, *p, *child;
    float rec0, bf, f20, f21, f22, f23, f24, ret, v, f0, f1, c444, k;
    int cnt, idx;

    idx = ((int (*)(void *, int))vt[54])(o, INT(b, 428));
    recs = *(char **)(o + 10116);
    rec0 = FLD(recs + idx * 8, 0);
    bf = FLD(b, 444);
    k = 1.024f;
    f21 = 0.009999999776482582f;
    f20 = rec0 * k;
    f22 = f20 - bf;
    f24 = -1.5f;
    f23 = 1.5f;
    cnt = 0;
    p = b;
    for (;;) {
        child = *(char **)(p + 1144);
        cnt++;
        if (!child)
            break;
        ret = ((float (*)(void *, void *, void *, int))vt[24])(o, b, child, 0);
        v = (float)INT(p, 1172) * f21;
        if (v < ret) {
            c444 = FLD(child, 444);
            f1 = c444 - bf;
            f0 = c444 - f20;
            if (f22 < 0.0f) {
                if (f1 < 0.0f && f24 < f0)
                    return child;
            } else {
                if (0.0f < f1 && f0 < f23)
                    return child;
            }
        }
        p += 4;
        if (!(cnt < 2))
            break;
    }
    f21 = -0.009999999776482582f;
    cnt = 0;
    p = b;
    for (;;) {
        child = *(char **)(p + 1200);
        cnt++;
        if (!child)
            return 0;
        ret = ((float (*)(void *, void *, void *, int))vt[24])(o, b, child, 1);
        v = (float)INT(p, 1228) * f21;
        if (v < ret) {
            c444 = FLD(child, 444);
            f1 = c444 - bf;
            f0 = c444 - f20;
            if (f22 < 0.0f) {
                if (f1 < 0.0f && f24 < f0)
                    return child;
            } else {
                if (0.0f < f1 && f0 < f23)
                    return child;
            }
        }
        p += 4;
        if (!(cnt < 2))
            return 0;
    }
}

/* @draft 0x0fbe28 us f_0fbe28
   WHAT IT DOES: Builds the car's box from the road point's two shorts (the lower bound from the
   first, the upper from the second), widens it in two loops over the owner's object tables
   (each object's float at +444 against the owner's float at +6236), then, when the car's
   height flags put it outside the box, sets the car's height from the owner's virtual query
   and calls the owner's virtual step with 1 or 0. Not yet byte-exact. */
extern "C" void f_0fbe28(MapOwner *o)
{
    char *base = D_23c820;
    char *areas = base + 12240;
    char *s2 = (char *)o + 5792;
    CarBlock *car = &o->car;
    short m16s, m14s;
    char *p;
    int i;

    f_0e3a74(areas, *(int *)(s2 + 428), &m16s, &m14s);
    car->m72 = -((float)m16s * 0.001f - 2.0f);
    car->m76 = (float)m14s * 0.001f - 2.0f;

    p = s2;
    for (i = 0; i < 2; i++, p += 4) {
        void *obj = *(void **)(p + 1144);
        float t, a, dd;
        if (!obj)
            break;
        t = ((float (**)(void *, void *, void *, int))o->vt)[24](o, s2, obj, 0);
        if ((float)*(int *)(p + 1172) * 0.01f < t) {
            a = *(float *)((char *)obj + 444);
            dd = a - o->m6236;
            if (dd < 0.0f) {
                float y = a + 3.0f;
                if (car->m72 < y)
                    car->m72 = y;
            } else {
                float y = a - 3.0f;
                if (y < car->m76)
                    car->m76 = y;
            }
        }
    }

    p = s2;
    for (i = 0; i < 2; i++, p += 4) {
        void *obj = *(void **)(p + 1200);
        float t, a, dd;
        if (!obj)
            break;
        t = ((float (**)(void *, void *, void *, int))o->vt)[24](o, s2, obj, 1);
        if ((float)*(int *)(p + 1228) * -0.01f < t) {
            a = *(float *)((char *)obj + 444);
            dd = a - o->m6236;
            if (dd < 0.0f) {
                float y = a + 3.0f;
                if (car->m72 < y)
                    car->m72 = y;
            } else {
                float y = a - 3.0f;
                if (y < car->m76)
                    car->m76 = y;
            }
        }
    }

    {
        int k = *(int *)(s2 + 428);
        float *rec = (float *)(o->recs + k * 8);
        float F = rec[0] * 1.024f;
        float G;
        int flags = 0;
        if (F < car->m72)
            flags = 1;
        else if (car->m76 < F)
            flags = 1;
        G = o->m6236;
        if (G < car->m72)
            flags |= 2;
        else if (car->m76 < G)
            flags |= 2;
        if (flags == 0)
            return;
        if (flags & 1) {
            car->m16 = ((float (**)(void *, int))o->vt)[28](o, k);
            ((void (**)(void *, int))o->vt)[30](o, 1);
        } else {
            ((void (**)(void *, int))o->vt)[30](o, 0);
        }
    }
}

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
   Remaining difference: after setting the latch, retail tests it again (li a2,1; beqz a2) where
   jump threading here goes straight to the 0.9 store; s also takes f2 here, f1 in retail. */
extern "C" void f_0fc1fc(MapOwner *o)
{
    CarBlock *c = &o->car;
    float s;
    int latch;

    if (c->m556 != 1)
        return;
    if (c->m40 || c->m44)
        return;
    s = c->m92 + c->m96;
    latch = c->m560;
    if (s < 0.0f) {
        if (latch == 0 && s < -0.2f) {
            c->m560 = 1;
            latch = 1;
        }
    } else {
        if (latch == 1 && 0.2f < s) {
            c->m560 = 0;
            latch = 0;
        }
    }
    c->m16 = latch ? 0.9f : -0.9f;
    ((void (**)(void *, int))o->vt)[30](o, 1);
}

/* @implements 0x0fc2e0 us f_0fc2e0
   WHAT IT DOES: An empty function. */
extern "C" void f_0fc2e0(void)
{
}

/* @implements 0x0fc2e8 us f_0fc2e8
   WHAT IT DOES: Car road state update: clears the car's +68 and fills its two +60 floats with
   the float maximum, then when the owner has its record table it calls the owner's virtual
   steps 58 and 31 and a probe (57) and steps 59 and 65; the common tail returns unless the
   car's counters at +40 and the bounds at +28 and +24 allow the update, and then either calls
   the owner's virtual step 30 or refreshes the car's bounds from the road sample. */
extern "C" void f_0fc2e8(char *o)
{
    char *p = o + 5792;
    char *c = o + 7092;
    float tmp, r1, r2, t;
    int i;

    INT(c, 68) = 0;
    for (i = 0; i < 2; i++)
        ((float *)(c + 60))[i] = 3.4028234663852886e+38f;
    INT(c, 40) = 0;
    if (*(char **)(o + 10116) != 0) {
        ((void (*)(void *))((*(void ***)o)[58]))(o);
        ((void (*)(void *))((*(void ***)o)[31]))(o);
        if (((int (*)(void *, float *))((*(void ***)o)[57]))(o, &tmp)) {
            FLD(c, 16) = tmp;
            INT(c, 44) = 1;
            ((void (*)(void *, int))((*(void ***)o)[30]))(o, 1);
        }
        ((void (*)(void *))((*(void ***)o)[59]))(o);
        ((void (*)(void *))((*(void ***)o)[65]))(o);
    }
    if (INT(c, 40) != 0)
        return;
    if (!(FLD(c, 28) <= 0.0f))
        return;
    if (!(FLD(c, 24) <= 0.0f))
        return;
    INT(c, 44) = 0;
    if (INT(c, 0) != 0) {
        ((void (*)(void *, int))((*(void ***)o)[30]))(o, 0);
        return;
    }
    if (!(FLD(c, 28) <= 0.0f))
        return;
    r1 = f_0c2b7c(p + 1272);
    t = (r1 - 0.5f) * 0.2f;
    FLD(c, 32) = 1.0f;
    FLD(c, 8) = t;
    FLD(c, 36) = t - FLD(c, 12);
    FLD(c, 24) = 1.0f;
    r2 = f_0c2b7c(p + 1272);
    FLD(c, 28) = r2 + 1.0f;
}

/* @draft 0x0fc4a8 us f_0fc4a8
   WHAT IT DOES: Updates the car block's two sweep floats (+8..+28) from its state word (+0):
   state 1 advances the sweep against its limit and state 0 advances the other pair, each with
   the 1/60 step, clamping the bound values at zero. Not yet byte-exact. */
extern "C" void f_0fc4a8(char *o)
{
    char *b = o + 5792;
    char *c = o + 7092;
    float f0, f1, f2, f3, f4;
    int st = INT(o, 7092);

    if (st == 0)
        goto st0;
    if (st != 1)
        return;
    FLD(c, 12) = 0.0f;
    f4 = FLD(c, 24);
    FLD(c, 8) = 0.0f;
    if (!(0.0f < f4))
        goto l598;
    f2 = FLD(c, 36);
    if (INT(b, 1020) == 4) {
        f1 = FLD(c, 20) + f2;
        f0 = f4 - 0.01666666753590107f;
        FLD(c, 20) = f1;
        FLD(c, 24) = f0;
    }
l4f4:
    if (!(0.0f < f2))
        goto l554;
    f1 = FLD(c, 16);
    f0 = FLD(c, 20);
    if (f1 <= f0) {
        FLD(c, 20) = f1;
        FLD(c, 24) = 0.0f;
    }
    f0 = FLD(c, 24);
l528:
    if (!(f0 <= 0.0f))
        return;
    FLD(c, 24) = 0.0f;
    FLD(c, 20) = FLD(c, 16);
    return;
l554:
    if (!(f2 < 0.0f)) {
        f0 = FLD(c, 24);
        goto l528;
    }
    f1 = FLD(c, 16);
    f0 = FLD(c, 20);
    if (f0 <= f1) {
        FLD(c, 20) = f1;
        FLD(c, 24) = 0.0f;
    }
    f0 = FLD(c, 24);
    goto l528;
l598:
    f0 = FLD(c, 28) - 0.01666666753590107f;
    FLD(c, 28) = f0;
    if (f0 < 0.0f)
        FLD(c, 24) = 0.0f;
    return;
st0:
    f4 = FLD(c, 24);
    if (!(0.0f < f4))
        goto l6c4;
    f3 = FLD(c, 32);
    f1 = FLD(c, 36);
    f0 = 0.5f;
    f1 = f1 / f3;
    f2 = 0.01666666753590107f;
    f0 = f3 * f0;
    f1 = f1 * f2;
    if (!(f0 < f4)) {
        f2 = f1 + f1;
        f0 = f4 / f0;
    } else {
        f3 = f3 - f4;
        f0 = f3 / f0;
    }
    f2 = f2 * f0;
    if (INT(b, 1020) == 4) {
        f1 = FLD(c, 12) + f2;
        f0 = f4 - 0.01666666753590107f;
        FLD(c, 12) = f1;
        FLD(c, 24) = f0;
    }
l620:
    f3 = 0.0f;
    if (!(0.0f < f2))
        goto l67c;
    f1 = FLD(c, 8);
    f0 = FLD(c, 12);
    if (f1 <= f0) {
        FLD(c, 12) = f1;
        FLD(c, 24) = 0.0f;
    }
    f0 = FLD(c, 24);
l658:
    f1 = 0.0f;
    if (!(f0 <= f1))
        return;
    f0 = FLD(c, 8);
    FLD(c, 24) = 0.0f;
    FLD(c, 12) = f0;
    return;
l67c:
    if (!(f2 < 0.0f)) {
        f0 = FLD(c, 24);
        goto l658;
    }
    f1 = FLD(c, 8);
    f0 = FLD(c, 12);
    if (f0 <= f1) {
        FLD(c, 12) = f1;
        FLD(c, 24) = 0.0f;
    }
    f0 = FLD(c, 24);
    goto l658;
l6c4:
    f0 = FLD(c, 28) - 0.01666666753590107f;
    FLD(c, 28) = f0;
    if (f0 < 0.0f)
        FLD(c, 24) = 0.0f;
    return;
}

/* @draft 0x0fc6e8 us f_0fc6e8
   WHAT IT DOES: Walks the road line ahead of the car over a distance taken from the car's
   value at +88 (clamped to 10..100). It sums the heading changes between successive road
   points, splitting them into a negative and a positive sum, and records the total of their
   absolute values and the change with the largest absolute value. The first heading comes
   from the angle helper. When the car's int at +0 is zero the walk reads each road record's
   short at +4 for its heading; otherwise it takes the heading from the road line's heading
   query. Writes the sums and the mean-scaled total to the car block. Not yet byte-exact. */
extern "C" void f_0fc6e8(MapOwner *o)
{
    char *s8 = (char *)o + 5792;
    CarBlock *car = (CarBlock *)((char *)o + 7092);
    char *base = D_23c820;
    char *areas = base + 12240;
    volatile float acc0 = 0.0f;
    volatile float acc4 = 0.0f;
    float sum = 0.0f;
    float peak = 0.0f;
    float m, t, ang, f20, w;
    int i;

    car->m88 = *(float *)(s8 + 1096);
    if (100.0f < car->m88)
        car->m88 = 100.0f;
    m = car->m88;
    if (m < 10.0f) {
        car->m88 = 10.0f;
        m = 10.0f;
    }

    ang = f_0c2bd0(car->m112, *(float *)(s8 + 992));
    t = ang + *(float *)(s8 + 992);
    if (3.14159265f < t)
        t -= 6.28318548f;
    else if (t < -3.14159265f)
        t += 6.28318548f;

    i = f_0e2690(areas, *(int *)(s8 + 428) + (int)(car->m88 / 2.5f));
    if (ang < 0.0f)
        acc0 += ang;
    else
        acc4 += ang;
    {
        float ab = ang;
        if (ang < 0.0f)
            ab = -ang;
        sum += ab;
    }

    if (car->m0 == 0) {
        if (0.0f < m) {
            do {
                const RoadRec *r = (const RoadRec *)(o->recs + i * 8);
                w = (float)(-(int)r->s4) * 3.14159265f * (1.0f / 32768.0f) + 1.57079637f;
                if (3.14159265f < w)
                    w -= 6.28318548f;
                else if (w < -3.14159265f)
                    w += 6.28318548f;
                ang = f_0c2bd0(t, w);
                f20 = ang;
                if (3.14159265f < ang)
                    f20 = ang - 6.28318548f;
                else if (ang < -3.14159265f)
                    f20 = ang + 6.28318548f;
                if (f20 < 0.0f)
                    acc0 += f20;
                else
                    acc4 += f20;
                {
                    float ab = f20;
                    if (f20 < 0.0f)
                        ab = -f20;
                    sum += ab;
                }
                if (peak < (f20 < 0.0f ? -f20 : f20))
                    peak = f20;
                m -= 1.024f;
                i = f_0e2690(areas, i + 1);
                t = w;
            } while (0.0f < m);
        }
    } else {
        if (0.0f < m) {
            do {
                float a = f_0e2260(areas, i) + 1.57079637f;
                if (3.14159265f < a)
                    a -= 6.28318548f;
                else if (a < -3.14159265f)
                    a += 6.28318548f;
                f20 = t - a;
                if (3.14159265f < f20)
                    f20 -= 6.28318548f;
                else if (f20 < -3.14159265f)
                    f20 += 6.28318548f;
                if (f20 < 0.0f)
                    acc0 += f20;
                else
                    acc4 += f20;
                {
                    float ab = f20;
                    if (f20 < 0.0f)
                        ab = -f20;
                    sum += ab;
                }
                if (peak < (f20 < 0.0f ? -f20 : f20))
                    peak = f20;
                a = f_0e2260(areas, i) + 1.57079637f;
                if (3.14159265f < a)
                    a -= 6.28318548f;
                else if (a < -3.14159265f)
                    a += 6.28318548f;
                m -= 1.024f;
                i = f_0e2690(areas, i + 1);
                t = a;
            } while (0.0f < m);
        }
    }

    car->m104 = peak;
    car->m100 = sum;
    car->m92 = acc0;
    car->m116 = sum * 0.0166666668f;
    car->m96 = acc4;
}

/* @draft 0x0fcc08 us f_0fcc08
   WHAT IT DOES: Car road sampling: when the car's counter at +128 is clear and the owner's
   state at +1020 is 4, it samples the road line three times along the car's distance, sums the
   weighted results into +144, stores the last index at +132, and sets the car's +128 counter
   with a derived bound at +140. Not yet byte-exact. */
extern "C" void f_0fcc08(char *o)
{
    char *base = D_23c820;
    char *areas = base + 12240;
    char *c = o + 7092;
    char *p = o + 5792;
    int v, idx, n;
    float f21, f22, f23, f20, val, r, r2, half;

    half = 0.5f;

    if (INT(c, 128) != 0)
        return;
    if (INT(p, 1020) != 4)
        return;
    v = INT(p, 428);
    f22 = (float)v;
    f21 = f_0e2260(areas, v);
    f23 = 0.0f;
    n = 2;
    do {
        f20 = f21;
        f22 = f22 + FLD(p, 1096);
        idx = f_0e2690(areas, (int)f22);
        INT(c, 132) = idx;
        val = f_0e2260(areas, idx);
        f21 = val;
        f23 = f23 + f_0c2bd0(val, f20) * half;
        n--;
    } while (n >= 0);
    FLD(c, 144) = f23;
    r = f_0c2b7c(p + 1272);
    FLD(c, 144) = FLD(c, 144) * ((r * 0.4f - 0.2f) + 1.0f);
    r2 = f_0c2b7c(p + 1272);
    FLD(c, 140) = (r2 + 3.0f) - half;
    INT(c, 128) = 1;
    FLD(c, 136) = 0.0f;
}

/* @draft 0x0fcd88 us f_0fcd88
   WHAT IT DOES: Per-frame step of the car block: when the car block's counter at +128 is set,
   it folds the car's value at +136 against its bound at +140 into a triangle wave, stores the
   absolute value (clamped at 1.0) at the owner's +10092, and when the road sample at +428 and
   the car's +132 disagree in sign it advances the car's value at +124 and clears the counter.
   Remaining difference: two words, the order of the two argument address setups for
   0x0af380 (retail sets a0 = sp before a1 = sp + 4). */
extern "C" void f_0fcd88(char *o)
{
    char *p = o + 5792;
    char *c = o + 7092;
    int s1;
    float f2, f3, ab, v, r, n136;
    float fa[2];

    int cnt;

    s1 = 0;
    cnt = INT(c, 128);
    INT(o, 10092) = 0;
    if (cnt == 0)
        return;
    f3 = FLD(c, 136);
    f2 = FLD(c, 140) * 0.5f;
    if (f3 < f2) {
        r = f3 / f2;
        f3 = FLD(c, 144) * r;
    } else {
        float m144 = FLD(c, 144);
        float q = (f3 - f2) / f2;
        f3 = m144 - m144 * q;
    }
    ab = f3;
    if (f3 < 0.0f)
        ab = -f3;
    FLD(o, 10092) = ab;
    v = (ab < 1.0f) ? ab : 1.0f;
    FLD(o, 10092) = v;
    FLD(c, 148) = f3;
    n136 = FLD(c, 136) + 0.016666668f;
    FLD(c, 136) = n136;
    if (FLD(c, 140) <= n136)
        s1 = 1;
    fa[1] = (float)INT(c, 132);
    fa[0] = (float)INT(p, 428);
    if ((int)f_0af380(fa, &fa[1]) >= 0)
        s1 = 1;
    if (s1 == 0)
        return;
    FLD(c, 124) = FLD(c, 124) + FLD(c, 148);
    INT(c, 128) = 0;
    FLD(c, 148) = 0.0f;
}

/* @implements 0x0fcec0 us f_0fcec0
   WHAT IT DOES: Sets the bits 0x700 in the flag word at +7692 of the object. */
extern "C" void f_0fcec0(FlagHolder *p)
{
    p->flags |= 0x700;
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

/* @draft 0x0fcfd8 us f_0fcfd8
   WHAT IT DOES: Per-frame road update: runs the owner's three setup calls, then when the
   owner's state at +972 is set it advances the owner's +6648 by the car's +76 value and a term
   built from the car's +152 and +156 record, decays the car's +152 and clamps it at zero, then
   writes the owner's +1088 constant and, when the car's +124 is clear, sets it to 1. Not yet
   byte-exact. */
extern "C" void f_0fcfd8(char *o)
{
    char *p = o + 5792;
    char *q = o + 7816;
    char *c = o + 7092;
    int fl;
    float f4, m152, r, term, nm;
    char *v3;
    float zero = 0.0f;

    f_0fe674(o);
    f_0bbcb0(q, FLD(p, 1136), FLD(p, 1096), INT(p, 972));
    fl = INT(o, 7692);
    f_0bb480(q, (fl >> 14) & 1, (fl >> 15) & 1, INT(p, 1020));
    f_0fe1b8(o, o + 7692);
    f_0fe2a8(o, o + 7692);
    if (INT(p, 972) != 0) {
        f4 = FLD(o, 6648) + FLD(q, 76);
        FLD(o, 6648) = f4;
        m152 = FLD(c, 152);
        if (zero < m152) {
            v3 = *(char **)(c + 156);
            if (FLD(v3, 388) <= 60.0f) {
                r = m152 / FLD(v3, 388);
                term = r * FLD(v3, 392);
            } else {
                r = m152 / FLD(v3, 388);
                term = (r * r) * FLD(v3, 392);
            }
            term = term * 9.8f / 0.32f;
            FLD(o, 6648) = f4 + term;
            nm = FLD(c, 152) - 0.016666668f;
            FLD(c, 152) = nm;
            if (nm < zero)
                FLD(c, 152) = 0.0f;
        }
    }
    FLD(p, 1088) = 0.225f;
    if (FLD(q, 124) == 0.0f) {
        if (INT(o, 9912) != 2 && FLD(q, 36) == 0.0f)
            FLD(q, 124) = 1.0f;
    }
}

/* @draft 0x0fd184 us f_0fd184
   WHAT IT DOES: Per-frame steering update of the car block: it takes the owner's virtual step 55
   value, clamps it against the car's two angle bounds, advances the car's heading (+120) and
   wraps the heading and the owner's two angle floats (+124, +912) into the range -pi..pi, then
   stores the scaled sine-like ratios at +916 and +1108. Not yet byte-exact. */
extern "C" void f_0fd184(char *o)
{
    char *s3 = o + 7996;
    char *b = o + 5792;
    char *car = o + 7092;
    void **vt = *(void ***)o;
    float r1, x, t1, t2, x2, a, x3, x4, f0, f1, s;
    union Angle sp;

    r1 = ((float (*)(void *))vt[55])(o);
    FLD(car, 112) = r1;
    x = f_0c2bd0(r1, FLD(car, 124));
    t1 = FLD(s3, 8) * FLD(o, 9928) * FLD(o, 9668);
    if (t1 < x) {
        x = t1;
    } else {
        t2 = FLD(s3, 12) * FLD(o, 9928) * FLD(o, 9668);
        if (x < t2)
            x = t2;
    }
    x2 = f_0c2bd0(x, FLD(car, 120));
    FLD(car, 120) = FLD(car, 120) + x2 * 30.0f * 0.01666666753590107f;
    f0 = f_09a9dc(FLD(b, 224), FLD(b, 232));
    f0 = -f0;
    FLD(b, 1108) = f0;
    if (INT(b, 1020) >= 3) {
        s = FLD(car, 124) + FLD(car, 120);
        FLD(car, 124) = s;
        if (3.1415927410125732f < s)
            FLD(car, 124) = s - 6.2831854820251465f;
        else if (s < -3.1415927410125732f)
            FLD(car, 124) = s + 6.2831854820251465f;
    }
    sp.a = FLD(b, 20) + 1.5707963705062866f;
    f_099b98(&sp);
    a = sp.a;
    if (3.1415927410125732f < a)
        a = a - 6.2831854820251465f;
    else if (a < -3.1415927410125732f)
        a = a + 6.2831854820251465f;
    x3 = f_0c2bd0(FLD(car, 124), a);
    f1 = x3 * 0.01666666753590107f;
    f1 = f1 / 0.05000000074505806f;
    FLD(b, 912) = f1;
    f0 = FLD(car, 148) * 0.01666666753590107f;
    f0 = f0 / 0.05000000074505806f;
    f1 = f1 + f0;
    FLD(b, 912) = f1;
    if (3.1415927410125732f < f1)
        FLD(b, 912) = f1 - 6.2831854820251465f;
    else if (f1 < -3.1415927410125732f)
        FLD(b, 912) = f1 + 6.2831854820251465f;
    x4 = f_0c2bd0(FLD(car, 124), FLD(b, 964));
    if (INT(b, 1020) >= 3) {
        f0 = x4 * 0.01666666753590107f;
        f0 = f0 / 0.05000000074505806f;
        FLD(b, 916) = f0;
    } else {
        FLD(b, 916) = x4 * 0.01666666753590107f;
    }
}
