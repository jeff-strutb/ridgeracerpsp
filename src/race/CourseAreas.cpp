/* @cflags: -fno-math-errno */

/* The course collision areas (retail 0x0e1eec to 0x0e40b8): the map manager's view of the
   course's road line and its ground. The road line is a ring of points one distance unit
   apart, each with a position, a heading and a cross section (a "danmen" profile of 64
   heights across the road). Two polygon sets, the road and the run-off area, answer ground
   height and normal queries; a query falls back to the run-off set when the road set misses.
   Setup also publishes the ring length as the angle wrapping periods of src/system/AngleWrap.c. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* One point of the road line. */
struct RoadPoint {
    float x;
    float z;
    float y;
    short angle;        /* heading, 0x8000 = pi */
    unsigned short m14;
    unsigned short m16;
    unsigned short section;
    unsigned char m20[2];
    signed char m22;
    signed char m23;
};

/* One cross section: 64 heights across the road. */
struct Danmen {
    short h[64];
};

/* A polygon set (src/system, the ground polygon object file). */
struct PolySet {
    char m[96];
};

extern "C" {
void f_0af678(PolySet *p, void *data);
unsigned short f_0af9c4(PolySet *p, const Vec4 *v, float *h);
unsigned short f_0b0234(PolySet *p, const Vec4 *v, float *h);
void f_0af5e8(PolySet *p, unsigned short *id);
float atan2f(float y, float x);
float sqrtf(float x);
}

/* An angle passed by address to the wrap helpers. */
union Angle {
    float a;
};

extern "C" {
Angle *f_099b98(Angle *a);
float f_099efc(float x);
float f_09a07c(float x);
float f_09a86c(float y, float x);
float f_099fc4(float a);
float f_09a154(float a);
float f_09a218(float a);
int f_0af550(const int *a);
}
Vec4 f_0b0d98(PolySet *p, const Vec4 *v, unsigned short *id);

extern float D_2456b0;
extern float D_2456b4;
extern int D_2456b8;
extern int D_2456bc;
extern int D_2456c0;
extern int D_2456c4;

class CourseAreas {
public:
    void f_0e1eec(RoadPoint *road, unsigned int roadSize, Danmen *danmen, void *runOff,
                  unsigned int runOffSize, void *roadPoly, void *runOffPoly);
    void f_0e1fc8(RoadPoint *road, unsigned int roadSize, Danmen *danmen);
    void f_0e1ff0();
    void f_0e1ff8(float d, float *px, float *py, float *pz);
    float f_0e2148(float d);
    float f_0e2260(int i);
    float f_0e229c(float d);
    float f_0e2334(float a, float d);
    int f_0e23d0(float x, float z);
    int f_0e2448(int a, int b, float x, float z);
    int f_0e2558(int a, int b, float x, float z);
    int f_0e2690(int i);
    float f_0e26dc(float d);
    void f_0e274c(float *minX, float *maxX, float *minZ, float *maxZ);
    float f_0e27f8(float x, float z);
    float f_0e286c(float x, float z, Vec4 *n);
    float f_0e2944(float x, float y, float z);
    int f_0e29b8(float *h, float x, float y, float z);
    float f_0e2a54(Vec4 *n, float x, float y, float z);
    float f_0e2b2c();
    void f_0e2f9c(int n, float *side, float *pos, float x, float z);
    void f_0e3a74(int i, unsigned short *a, unsigned short *b);
    void f_0e3a9c(float x, float y, float z);
    float f_0e3b30();
    float f_0e3b3c(float a, float b);

    RoadPoint *road;
    Danmen *danmen;
    int n;
    void *runOff;
    PolySet roadPoly;
    PolySet runOffPoly;
};

/* @draft 0x0e1eec us CourseAreas8f_0e1eec
   WHAT IT DOES: Takes the road line, its cross sections, the run-off data and both polygon
   sets, and publishes the ring lengths as the angle wrapping periods.
   Remaining difference: 21/55 words, scheduling only: the run-off half period is a plain
   signed shift (sra with no sign fix-up), so it is m >> 1. Retail stores n before runOff and
   computes n / 2 (in t4) before moving this to s0; not yet diagnosed in the dumps. */
void CourseAreas::f_0e1eec(RoadPoint *road, unsigned int roadSize, Danmen *danmen, void *runOff,
                           unsigned int runOffSize, void *roadPoly, void *runOffPoly)
{
    int n = roadSize / 24 - 1;
    int m = runOffSize / 40 - 1;

    this->n = n;
    this->runOff = runOff;
    D_2456b4 = (float)n * 0.5f;
    this->road = road;
    this->danmen = danmen;
    D_2456bc = n / 2;
    D_2456c4 = m >> 1;
    D_2456b0 = (float)n;
    D_2456b8 = n;
    D_2456c0 = m;
    f_0af678(&this->roadPoly, roadPoly);
    f_0af678(&this->runOffPoly, runOffPoly);
}

/* @implements 0x0e1fc8 us CourseAreas8f_0e1fc8
   WHAT IT DOES: Takes a road line and its cross sections only. */
void CourseAreas::f_0e1fc8(RoadPoint *road, unsigned int roadSize, Danmen *danmen)
{
    this->road = road;
    this->danmen = danmen;
    n = roadSize / 24 - 1;
}

/* @implements 0x0e1ff0 us CourseAreas8f_0e1ff0
   WHAT IT DOES: Nothing. */
void CourseAreas::f_0e1ff0()
{
}

/* @draft 0x0e1ff8 us CourseAreas8f_0e1ff8
   WHAT IT DOES: Returns the point on the road centre line at a distance, interpolating
   between the two road points around it (the height includes the cross section's centre).
   Remaining difference: 65/84 words. The three results are now built in place and stored
   together at the end, as retail does. Before the second wrap call retail copies i into t0
   (move t0,v0; addiu t0,t0,1) and keeps d in $f21, y in $f20; here i + 1 is formed in v0 and
   d takes $f20, which shifts every FPR after it. Not yet diagnosed in the dumps. */
void CourseAreas::f_0e1ff8(float d, float *px, float *py, float *pz)
{
    int i = f_0e2690((int)d);
    RoadPoint *p = &road[i];
    float x, y, z;

    d -= (float)i;
    y = p->y + (float)danmen[p->section].h[32];
    z = p->z;
    x = p->x;
    p = &road[f_0e2690(i + 1)];
    x = x * (1.0f - d) + p->x * d;
    y = y * (1.0f - d) + (p->y + (float)danmen[p->section].h[32]) * d;
    z = z * (1.0f - d) + p->z * d;
    *px = x;
    *py = y;
    *pz = z;
}

/* @draft 0x0e2148 us CourseAreas8f_0e2148
   WHAT IT DOES: Returns the road heading at a distance, interpolated the short way round.
   Remaining difference: 51/70 words; retail is one instruction longer: after the wrap call it
   copies the result (move a1,v0) and builds the element address from the copy, and it loads
   road at the very top. An inline heading helper taking (road, i) (tried once) is worse (63). */
float CourseAreas::f_0e2148(float d)
{
    int i = (int)d;
    float t = d - (float)i;
    float a = (float)road[i].angle * 3.05175781e-05f * 3.14159274f;
    float b = (float)road[f_0e2690(i + 1)].angle * 3.05175781e-05f * 3.14159274f;

    if (a - b > 3.14159012f)
        b += 6.28318024f;
    if (b - a > 3.14159012f)
        a += 6.28318024f;
    return a * (1.0f - t) + b * t;
}

/* @implements 0x0e2260 us CourseAreas8f_0e2260
   WHAT IT DOES: Returns a road point's heading in radians. */
float CourseAreas::f_0e2260(int i)
{
    return (float)road[i].angle * 3.05175781e-05f * 3.14159274f;
}

/* @draft 0x0e229c us CourseAreas8f_0e229c
   WHAT IT DOES: Returns the road's slope angle at a distance (over one distance unit).
   DIFFERS: 2/38 words differ, first at +0x68 (not yet worked). */
float CourseAreas::f_0e229c(float d)
{
    float x0, y0, z0, x1, y1, z1;

    f_0e1ff8(d, &x0, &y0, &z0);
    d += 1.0f;
    f_0e1ff8(d, &x1, &y1, &z1);
    return atan2f(y1 - y0, sqrtf((x1 - x0) * (x1 - x0) + (z1 - z0) * (z1 - z0)));
}

/* @implements 0x0e2334 us CourseAreas8f_0e2334
   WHAT IT DOES: Returns the ground height at a sideways offset (-32 to 31) and a distance.
   The point index is taken before the offset is clamped and the point's address formed after
   it, offset first (handbook: addu with the offset register first is integer arithmetic). */
float CourseAreas::f_0e2334(float a, float d)
{
    int i = (int)f_0e26dc(d);
    int k = (int)a;

    if (k < -32)
        k = -32;
    if (k >= 32)
        k = 31;
    RoadPoint *p = (RoadPoint *)(i * (int)sizeof(RoadPoint) + (int)road);
    return p->y + (float)danmen[p->section].h[k + 32];
}

/* @implements 0x0e23d0 us CourseAreas8f_0e23d0
   WHAT IT DOES: Returns the road point nearest a position. */
int CourseAreas::f_0e23d0(float x, float z)
{
    float min = -1.0f;
    int best = 0;
    int i;
    float dx, dz;

    for (i = 0; i < n; i++) {
        dx = road[i].x - x;
        dz = road[i].z - z;
        if (i == 0 || dx * dx + dz * dz < min) {
            min = dx * dx + dz * dz;
            best = i;
        }
    }
    return best;
}

/* @draft 0x0e2448 us CourseAreas8f_0e2448
   WHAT IT DOES: Returns the road point nearest a position among those from a to b (going
   round the ring), or -1.
   DIFFERS: 10/68 words differ, first at +0x8c (not yet worked). */
int CourseAreas::f_0e2448(int a, int b, float x, float z)
{
    float min = -1.0f;
    int best = -1;
    int i, j;
    float dx, dz;

    if (b < a)
        b += n;
    for (i = a; i <= b; i++) {
        j = f_0e2690(i);
        dx = road[j].x - x;
        dz = road[j].z - z;
        if (min < 0.0f || dx * dx + dz * dz < min) {
            min = dx * dx + dz * dz;
            best = j;
        }
    }
    return best;
}

/* @draft 0x0e2558 us CourseAreas8f_0e2558
   WHAT IT DOES: Returns the road point nearest a position within 50 points of a, skipping
   those before b; a when none qualifies.
   Remaining difference: 10/78 words, FPR choice only: retail loads road[j].z into $f1 and x
   into $f0 and squares dx into $f2, dz into $f1; here z takes $f0. The two skip tests are
   separate continues (a single || is or-ed into one branch). Not yet diagnosed in the dumps. */
int CourseAreas::f_0e2558(int a, int b, float x, float z)
{
    float min = -1.0f;
    int best = a;
    int i, j;
    float dx, dz;

    for (i = a - 50; i < n && i < a + 50; i++) {
        j = f_0e2690(i);
        if (j < 0)
            continue;
        if (j < b)
            continue;
        dx = road[j].x - x;
        dz = road[j].z - z;
        if (min < 0.0f || dx * dx + dz * dz < min) {
            min = dx * dx + dz * dz;
            best = j;
        }
    }
    return best;
}

/* @implements 0x0e2690 us CourseAreas8f_0e2690
   WHAT IT DOES: Wraps a road point index into the ring. */
int CourseAreas::f_0e2690(int i)
{
    int r = 0;

    if (n > 0) {
        r = i;
        while (r >= n)
            r -= n;
        while (r < 0)
            r += n;
    }
    return r;
}

/* @implements 0x0e26dc us CourseAreas8f_0e26dc
   WHAT IT DOES: Wraps a distance into the ring length. */
float CourseAreas::f_0e26dc(float d)
{
    float len = (float)n;
    float r = 0.0f;

    if (len > 0.0f) {
        r = d;
        while (r >= len)
            r -= len;
        while (r < 0.0f)
            r += len;
    }
    return r;
}

/* @draft 0x0e274c us CourseAreas8f_0e274c
   WHAT IT DOES: Returns the bounding rectangle of the road line.
   Remaining difference: 29/43 words. Retail puts the field in $f0 and the bound in $f1 for
   every test and uses plain beqz (no beqzl) for the i == 0 shortcuts; here the field takes $f1.
   Spelling the tests as `*minX > p->x` compiles identically (tried once). */
void CourseAreas::f_0e274c(float *minX, float *maxX, float *minZ, float *maxZ)
{
    int i;
    RoadPoint *p = road;

    for (i = 0; i < n; i++) {
        if (i == 0 || p->x < *minX)
            *minX = p->x;
        if (i == 0 || *maxX < p->x)
            *maxX = p->x;
        if (i == 0 || p->z < *minZ)
            *minZ = p->z;
        if (i == 0 || *maxZ < p->z)
            *maxZ = p->z;
        p++;
    }
}

/* @implements 0x0e27f8 us CourseAreas8f_0e27f8
   WHAT IT DOES: Returns the ground height under a point (road first, then run-off). */
float CourseAreas::f_0e27f8(float x, float z)
{
    Vec4 v;
    float h;

    v.x = x;
    v.z = z;
    v.w = 1.0f;
    v.y = 0.0f;
    if (f_0af9c4(&roadPoly, &v, &h) == 0xffff)
        f_0af9c4(&runOffPoly, &v, &h);
    return h;
}

/* @draft 0x0e286c us CourseAreas8f_0e286c
   WHAT IT DOES: Returns the ground height under a point and the ground's normal there.
   Remaining difference: 42/62 words. Retail cross-jumps the run-off arm into the road arm's
   f_0b0d98 call (j with move a1,s3 in the slot), so both arms' copy-outs of the returned
   vector were identical RTL after reload; here the two copies are scheduled differently and
   stay separate. Retail also keeps n in s0 and the road set in s1. Pointer locals for the two
   sets (tried once) change nothing that matters (49 words). */
float CourseAreas::f_0e286c(float x, float z, Vec4 *n)
{
    unsigned short id;
    Vec4 v;
    float h;

    v.x = x;
    v.z = z;
    v.w = 1.0f;
    v.y = 0.0f;
    id = f_0af9c4(&roadPoly, &v, &h);
    if (id == 0xffff) {
        id = f_0af9c4(&runOffPoly, &v, &h);
        *n = f_0b0d98(&runOffPoly, &v, &id);
    } else {
        *n = f_0b0d98(&roadPoly, &v, &id);
    }
    return h;
}

/* @implements 0x0e2944 us CourseAreas8f_0e2944
   WHAT IT DOES: Returns the ground height below a point in space. */
float CourseAreas::f_0e2944(float x, float y, float z)
{
    Vec4 v;
    float h;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1.0f;
    if (f_0b0234(&roadPoly, &v, &h) == 0xffff)
        f_0b0234(&runOffPoly, &v, &h);
    return h;
}

/* @draft 0x0e29b8 us CourseAreas8f_0e29b8
   WHAT IT DOES: Finds the ground height below a point in space; returns 0 when there is no
   ground there.
   Remaining difference: 28/40 words. Retail loads li s1,0xffff before the first call and
   compares both results against s1; here the first result goes to s1 and, on the path where it
   equals 0xffff, cse reuses it as the constant for the second test. A local holding 0xffff
   (handbook row 309) compiles identically. */
int CourseAreas::f_0e29b8(float *out, float x, float y, float z)
{
    Vec4 v;
    float h;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1.0f;
    if (f_0b0234(&roadPoly, &v, &h) == 0xffff && f_0b0234(&runOffPoly, &v, &h) == 0xffff)
        return 0;
    *out = h;
    return 1;
}

/* @draft 0x0e2a54 us CourseAreas8f_0e2a54
   WHAT IT DOES: Returns the ground height below a point in space and the ground's normal.
   DIFFERS: 42/62 words differ, first at +0xc (not yet worked). */
float CourseAreas::f_0e2a54(Vec4 *n, float x, float y, float z)
{
    unsigned short id;
    Vec4 v;
    float h;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1.0f;
    id = f_0b0234(&roadPoly, &v, &h);
    if (id == 0xffff) {
        id = f_0b0234(&runOffPoly, &v, &h);
        *n = f_0b0d98(&runOffPoly, &v, &id);
    } else {
        *n = f_0b0d98(&roadPoly, &v, &id);
    }
    return h;
}

/* @implements 0x0e2b2c us CourseAreas8f_0e2b2c
   WHAT IT DOES: Returns 0 (an emptied query). */
float CourseAreas::f_0e2b2c()
{
    return 0.0f;
}

/* The point index i wrapped into the ring. */
static inline int RoadWrap(int i)
{
    return f_0af550(&i);
}

/* Which side of road point k's heading line the position v lies on (negative: ahead). */
static inline float RoadSide(const float *v, RoadPoint *list, int k)
{
    RoadPoint *e = &list[k];
    Angle a;
    a.a = e->angle * 9.5873802e-05f;
    float t = f_099b98(&a)->a;
    return (v[1] - e->z) * f_09a07c(t) + (v[0] - e->x) * f_099efc(t);
}

/* @draft 0x0e2f9c us CourseAreas8f_0e2f9c
   WHAT IT DOES: Finds the road segment under a position near road point n (a binary search
   over the 16 points around it, testing which side of each point's heading line the position
   lies on), then projects the position onto that segment: stores the distance along the road
   (the segment's first point plus the clamped fraction 0..1, corrected for both end points'
   headings) in *pos and the sideways offset (scaled by 1/1024) in *side.
   Remaining difference: 9/694 words, all sched2 order on the projection's tail. Retail adds
   den's two products before num's after the first heading wrap call, then num += t before
   den += t; here each pair is the other way round (sched2 keeps sched1's order for these
   equal-priority sums, and sched1 issues num's sum first because den's dx*c product has the
   fewest dependents and is chosen last). Retail also stores *pos before *side; with *side
   written first (needed for retail's s7/s8 assignment: global-alloc ranks side ahead only when
   its store is earlier) sched2 here stores *side first. Computing dx*c before the sine call
   (tried) moves FPRs and does not reorder the sums. */
void CourseAreas::f_0e2f9c(int n, float *side, float *pos, float x, float z)
{
    RoadPoint *list = road;
    float v[2];
    int a, b;

    v[0] = x;
    v[1] = z;
    if (RoadSide(v, list, n) < 0.0f) {
        int kp4 = RoadWrap(n + 4);
        if (RoadSide(v, list, kp4) < 0.0f) {
            int kp6 = RoadWrap(n + 6);
            if (RoadSide(v, list, kp6) < 0.0f) {
                int kp7 = RoadWrap(n + 7);
                if (RoadSide(v, list, kp7) < 0.0f) {
                    a = kp7;
                    b = RoadWrap(n + 8);
                } else {
                    a = RoadWrap(n + 6);
                    b = kp7;
                }
            } else {
                int kp5 = RoadWrap(n + 5);
                if (RoadSide(v, list, kp5) < 0.0f) {
                    a = kp5;
                    b = RoadWrap(n + 6);
                } else {
                    a = RoadWrap(n + 4);
                    b = kp5;
                }
            }
        } else {
            int kp2 = RoadWrap(n + 2);
            if (RoadSide(v, list, kp2) < 0.0f) {
                int kp3 = RoadWrap(n + 3);
                if (RoadSide(v, list, kp3) < 0.0f) {
                    a = kp3;
                    b = RoadWrap(n + 4);
                } else {
                    a = RoadWrap(n + 2);
                    b = kp3;
                }
            } else {
                int kp1 = RoadWrap(n + 1);
                if (RoadSide(v, list, kp1) < 0.0f) {
                    a = kp1;
                    b = RoadWrap(n + 2);
                } else {
                    a = RoadWrap(n);
                    b = kp1;
                }
            }
        }
    } else {
        int km4 = RoadWrap(n - 4);
        if (RoadSide(v, list, km4) < 0.0f) {
            int km2 = RoadWrap(n - 2);
            if (RoadSide(v, list, km2) < 0.0f) {
                int km1 = RoadWrap(n - 1);
                if (RoadSide(v, list, km1) < 0.0f) {
                    a = km1;
                    b = RoadWrap(n);
                } else {
                    a = RoadWrap(n - 2);
                    b = km1;
                }
            } else {
                int km3 = RoadWrap(n - 3);
                if (RoadSide(v, list, km3) < 0.0f) {
                    a = km3;
                    b = RoadWrap(n - 2);
                } else {
                    a = RoadWrap(n - 4);
                    b = km3;
                }
            }
        } else {
            int km6 = RoadWrap(n - 6);
            if (RoadSide(v, list, km6) < 0.0f) {
                int km5 = RoadWrap(n - 5);
                if (RoadSide(v, list, km5) < 0.0f) {
                    a = km5;
                    b = RoadWrap(n - 4);
                } else {
                    a = RoadWrap(n - 6);
                    b = km5;
                }
            } else {
                int km7 = RoadWrap(n - 7);
                if (RoadSide(v, list, km7) < 0.0f) {
                    a = km7;
                    b = RoadWrap(n - 6);
                } else {
                    a = RoadWrap(n - 8);
                    b = km7;
                }
            }
        }
    }

    Angle h;
    Angle ra;
    Angle rb;
    Angle da;
    Angle db;
    RoadPoint *e = &road[a];
    RoadPoint *f = &road[b];
    float ez = e->z;
    float ex = e->x;
    float dz = ez - f->z;
    float dx = ex - f->x;
    h.a = f_09a86c(dx, dz);
    f_099b98(&h);
    float c = f_099fc4(h.a);
    float sn = f_09a154(h.a);
    float den = dx * c + dz * sn;
    float num = (ex - x) * c + (ez - z) * sn;
    float u = (x - ex) * sn - (z - ez) * c;
    ra.a = e->angle * 3.14159274f * 3.05175781e-05f;
    f_099b98(&ra);
    rb.a = f->angle * 3.14159274f * 3.05175781e-05f;
    f_099b98(&rb);
    da.a = h.a - ra.a;
    f_099b98(&da);
    float t = u * f_09a218(da.a);
    num += t;
    den += t;
    db.a = h.a - rb.a;
    f_099b98(&db);
    den -= u * f_09a218(db.a);
    float r = num / den;
    if (r > 1.0f)
        r = 1.0f;
    else if (r < 0.0f)
        r = 0.0f;
    *side = u * 0.0009765625f;
    *pos = a + r;
}

/* @implements 0x0e3a74 us CourseAreas8f_0e3a74
   WHAT IT DOES: Returns two fields of a road point. */
void CourseAreas::f_0e3a74(int i, unsigned short *a, unsigned short *b)
{
    RoadPoint *p = &road[i];

    *a = p->m16;
    *b = p->m14;
}

/* @draft 0x0e3a9c us CourseAreas8f_0e3a9c
   WHAT IT DOES: Passes the ground polygon below a point in space on to its polygon set.
   Remaining difference: 15/37 words. Retail builds &roadPoly (s0), &v (s1) and &runOffPoly
   (s2) in the prologue and cross-jumps the run-off arm into the shared f_0af5e8 call (j with
   move a0,s2 in the slot). Two pointer locals with a call in each arm (tried once) get the
   prologue pointers but neither the cross-jump nor that register order (36 words). */
void CourseAreas::f_0e3a9c(float x, float y, float z)
{
    unsigned short id;
    Vec4 v;
    float h;
    PolySet *p = &roadPoly;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1.0f;
    id = f_0b0234(p, &v, &h);
    if (id == 0xffff) {
        p = &runOffPoly;
        id = f_0b0234(p, &v, &h);
    }
    f_0af5e8(p, &id);
}

/* @implements 0x0e3b30 us CourseAreas8f_0e3b30
   WHAT IT DOES: Returns 0 (an emptied query). */
float CourseAreas::f_0e3b30()
{
    return 0.0f;
}

/* @draft 0x0e3b3c us CourseAreas8f_0e3b3c
   WHAT IT DOES: Returns the distance from b to a along the ring, wrapped to within half a
   lap.
   DIFFERS: 6/29 words: retail puts half in $f2 and -half in $f0; here half takes $f0. Both are
   allocated by global-alloc, which takes half first on priority (4 refs over 9 insns against
   -half's 3 over 6, refs weighted by block frequency). A separate -half variable declared first
   changes nothing. Open: what in retail gives -half the higher priority. */
float CourseAreas::f_0e3b3c(float a, float b)
{
    float len = (float)n;
    float half = len * 0.5f;

    a -= b;
    if (a < -half) {
        do
            a += len;
        while (a < -half);
    } else {
        while (half < a)
            a -= len;
    }
    return a;
}
