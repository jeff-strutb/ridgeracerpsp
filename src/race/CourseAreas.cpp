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
    void f_0e3bb0(int i, float x, float z, float *px, float *py, float *pz, float *nx, float *ny,
                  float *nz, float *ux, float *uy, float *uz, float *head);

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
   computes n / 2 (in t4) before moving this to s0; not yet diagnosed in the dumps.
   Cycle 2026-11-16 (lreg/greg): sched1 runs; ours ends runOff's (t0) life early so local-alloc
   reuses t0 for the n/2 temps; retail's n/2 lands in t4, i.e. t0-t3 (runOff, runOffSize, both polys)
   were all still live then. Tried int h = n / 2; at the top: CSE folds it, output identical. */
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
   d takes $f20, which shifts every FPR after it. Not yet diagnosed in the dumps.
   Cycle 2026-11-16: retail is 336 bytes (one more insn: move t0,v0, so i's pseudo is not tied
   to v0; retail keeps v0 for the section halfword and p in v1 where this puts p in a2). FPR order
   reads as global-alloc priority (y beat d for $f20 in retail). Tried a separate t = d - (float)i
   for the fraction: identical output (the copy is coalesced), reverted. */
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
   road at the very top. An inline heading helper taking (road, i) (tried once) is worse (63).
   Cycle 2026-11-16 (greg): here the call-result pseudo is tied to v0 and j*3 goes sll v1,v0,1;
   addu v1,v1,v0. Retail's shape (move a1,v0; sll v0,v0,1; addu v0,v0,a1) means two pseudos held j
   (one shifted in v0, a copy in a1). Tried int j = f_0e2690(i + 1); as a named local: identical
   output, reverted. Same move-copy appears in 0x0e1ff8 (move t0,v0). */
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
   Remaining difference: 4/68 words, the same load order residue as f_0e2558 (z read before
   x gives retail's FPRs; sched2 keeps x's load first where retail issues z's). The cause
   found from the dumps is recorded at f_0e2558 and applies here unchanged (2026-11-16). */
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
        dz = road[j].z - z;
        dx = road[j].x - x;
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
   Remaining difference: 4/78 words, the order of the two point loads and subtractions (sched2).
   The skip tests are separate continues (a single || is or-ed into one branch). z is read
   before x so that the x load is the base register's last use: sched1's register-weight
   tie-break then issues it first and local-alloc gives x $f0, as in retail. Retail's final
   order is z load, x load, z sub, x sub; here sched2 keeps sched1's x-first order.
   Diagnosis (sched1/sched2 -fsched-verbose dumps, 2026-11-16): sched1 emits x load, z load,
   x sub, z sub; sched2 has no rank difference between the loads (same priority, both
   independent of the c.lt.s) and keeps that order. Local-alloc's qty_compare gives both load
   temporaries the same priority (2 refs, life 2), so the first-born (x) takes $f0. Retail's
   result is only reachable from a sched1 order z load, x load, x sub, z sub: x's temporary
   then lives 1 insn against z's 3 and wins $f0 on priority, and sched2 issues z's sub first
   because z's load is ready first. Reading x first in the source makes z the base register's
   last use and sched1 issues z first, but its sub then also comes first (lives tie, z born
   first takes $f0); no source shape found that delays z's sub in sched1. No change made. */
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
        dz = road[j].z - z;
        dx = road[j].x - x;
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
   Spelling the tests as `*minX > p->x` compiles identically (tried once).
   Cycle 2026-11-16: ours loads p->x once before the i == 0 branch, so that pseudo spans blocks,
   goes to greg and gets $f1 after the local bound; retail reloads in each block (local $f0). Tried
   if (i == 0) store; else if (cmp) store; for all four: 47/49 words, 196 bytes (no cross-jump), reverted. */
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
   sets (tried once) change nothing that matters (49 words).
   2026-11-16: one PolySet *p switched in the if and a single f_0b0d98(p, ...) after the join
   (the shape 0x0e29b8 also wants): 30/54 words, 204 vs 216 bytes, n in s0 and road in s1 as in
   retail. Remaining difference: retail computes this+112 into s3 in the prologue and its
   run-off arm ends j back to the jal with move a1,s3 in the slot; here s3 = this and the arm
   does addiu s1,s3,112 (p reuses s1), and the copy-out stores are scheduled differently. */
float CourseAreas::f_0e286c(float x, float z, Vec4 *n)
{
    unsigned short id;
    PolySet *p;
    Vec4 v;
    float h;

    v.x = x;
    v.z = z;
    v.w = 1.0f;
    v.y = 0.0f;
    p = &roadPoly;
    id = f_0af9c4(p, &v, &h);
    if (id == 0xffff) {
        p = &runOffPoly;
        id = f_0af9c4(p, &v, &h);
    }
    *n = f_0b0d98(p, &v, &id);
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
   Was 28/40 words with the && form (first result went to s1 and cse reused it as the constant
   for the second test; a local holding 0xffff compiled identically). 2026-11-16: one id local
   tested after the join (id = road; if (id == 0xffff) id = runOff; if (id == 0xffff) return 0)
   gives retail's li 0xffff hoisted before the first call: 7/39 words, retail size.
   Remaining difference: out is s1 and 0xffff s2 (retail s2 / s1), and the second test's tail
   is bne to the store block + j to the epilogue where retail has beq + j back with the lwc1
   in the j slot.
   2026-11-16 second cycle: tried the second call and test nested inside the first test (one id
   local): 28/40 words, size 160, the && result again (first result kept in s1, 0xffff loaded
   after the call), and the second test is still bne + j, so nesting is not the layout lever.
   Restored. */
int CourseAreas::f_0e29b8(float *out, float x, float y, float z)
{
    unsigned short id;
    Vec4 v;
    float h;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1.0f;
    id = f_0b0234(&roadPoly, &v, &h);
    if (id == 0xffff)
        id = f_0b0234(&runOffPoly, &v, &h);
    if (id == 0xffff)
        return 0;
    *out = h;
    return 1;
}

/* @draft 0x0e2a54 us CourseAreas8f_0e2a54
   WHAT IT DOES: Returns the ground height below a point in space and the ground's normal.
   Was 42/62 words with a f_0b0d98 call in each arm (248 bytes). 2026-11-16: one PolySet *p
   switched in the if and one call after the join (as 0x0e286c): 30/54 words, 204 vs 216 bytes.
   Remaining difference (same as 0x0e286c): retail holds this+112 in s3 from the prologue and the
   run-off arm jumps back to the jal with move a1,s3 in the slot; here s3 = this and the arm
   computes addiu s1,s3,112; the copy-out stores are scheduled differently. */
float CourseAreas::f_0e2a54(Vec4 *n, float x, float y, float z)
{
    unsigned short id;
    PolySet *p;
    Vec4 v;
    float h;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = 1.0f;
    p = &roadPoly;
    id = f_0b0234(p, &v, &h);
    if (id == 0xffff) {
        p = &runOffPoly;
        id = f_0b0234(p, &v, &h);
    }
    *n = f_0b0d98(p, &v, &id);
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
   prologue pointers but neither the cross-jump nor that register order (36 words).
   Tried (2026-11-16): a second pointer local q = &runOffPoly at the top, p = q in the if: this+112
   goes to s2 in the prologue and the cross-jump appears, but via a 'move v0,a0' copy and with
   &v in s0 / &roadPoly in s1 (retail s1 / s0): 31 words, reverted. */
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
   changes nothing. Open: what in retail gives -half the higher priority.
   Diagnosis (2026-11-16): global.c's priority is floor_log2(refs) * freq / live length, so
   half's 4 refs weigh 2 against -half's 3 refs weighing 1; -half would need a fourth ref (or
   half one fewer) to be allocated first. Both arms already have one test outside and one inside
   their loop; no source shape found that changes the counts without changing the code. No
   change made. */
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

/* The polygon list a segment is walked against (src/race/TrackGeometry.cpp). */
struct HitList {
    char m[272];
};

/* The map manager's block: the sector lookup object sits at +12144. */
struct MapBlock {
    char pad[12144];
    char m12144[16];
    void *Sectors() { return m12144; }
};
extern MapBlock D_23c820;

extern "C" {
int f_0d5f78(void *d, int v);
int f_0b1bc0(HitList *h, int n, float x, float z);
int f_0b2a00(HitList *h, const Vec4 *a, const Vec4 *b, Vec4 *out, Vec4 *outn);
void f_09b394(Angle a, float *x, float *y);
}

/* @draft 0x0e3bb0 us CourseAreas8f_0e3bb0
   WHAT IT DOES: Places a point on the course from road point i towards (x, z): walks from the
   road centre to the point in steps of at most 1000 units against the sector's wall list and
   stops at the first wall hit (pushed back by the wall's offset), then takes the ground height
   and normal there (*px, *py, *pz and *nx, *ny, *nz), turns an up vector by the wall and normal
   headings when a wall was hit (*ux, *uy, *uz), and stores the road heading interpolated at the
   point's distance in *head.
   Remaining difference: 304/322 words; first transcription, frame layout as retail. Retail checks
   the sqrtf result for NaN and calls sqrtf (the -fmath-errno expansion), which this file's
   -fno-math-errno cannot produce; that call is also why retail keeps the 0.0 (c.y) and 1.0 in
   saved $f22/$f23. Scored without the flag this draft is 177/322 (size 1280 vs 1288), but
   f_0e229c then gains the check (its argument is not provably non-negative as written). */
void CourseAreas::f_0e3bb0(int i, float x, float z, float *px, float *py, float *pz, float *nx,
                           float *ny, float *nz, float *ux, float *uy, float *uz, float *head)
{
    HitList h;
    Vec4 c;
    Vec4 p;
    Vec4 d;
    Vec4 q;
    Vec4 r;
    Vec4 s;
    Vec4 e;
    Vec4 v;
    float side;
    float pos;
    Angle t1;
    Angle t2;
    Angle t3;
    Angle w;
    int sect = f_0d5f78(D_23c820.Sectors(), i);
    int k;
    int hit;

    f_0e1ff8((float)i, &c.x, &c.y, &c.z);
    c.y = 0.0f;
    p.x = x;
    p.y = 0.0f;
    p.z = z;
    p.w = 1.0f;
    d.x = x - c.x;
    d.y = 0.0f;
    d.z = z - c.z;
    d.w = 1.0f;
    float l2 = d.x * d.x + d.y * d.y + d.z * d.z;
    int n = (int)sqrtf(l2) / 1000 + 1;
    q = c;
    r.w = 0.0f;
    r.x = 0.0f;
    r.y = 0.0f;
    r.z = 0.0f;
    d.x /= n;
    d.y /= n;
    d.z /= n;
    hit = 0;
    for (k = 0; k < n; k++) {
        e.x = q.x + d.x;
        e.y = q.y + d.y;
        e.z = q.z + d.z;
        e.w = 1.0f;
        f_0b1bc0(&h, sect, e.x, e.z);
        hit = f_0b2a00(&h, &e, &q, &r, &s);
        if (hit) {
            *px = e.x + r.x;
            *pz = e.z + r.z;
            break;
        }
        q.x += d.x;
        q.y += d.y;
        q.z += d.z;
    }
    if (!hit) {
        f_0b1bc0(&h, sect, p.x, p.z);
        hit = f_0b2a00(&h, &p, &q, &r, &s);
        if (hit) {
            *px = p.x + r.x;
            *pz = p.z + r.z;
        } else {
            *px = p.x;
            *pz = p.z;
        }
    }
    p.x = *px;
    p.z = *pz;
    p.y = 0.0f;
    p.w = 1.0f;
    f_0e2f9c(f_0e2448(i - 50, i + 50, p.x, p.z), &side, &pos, p.x, p.z);
    p.y = f_0e2334(side, pos);
    p.y = f_0e2a54(&e, p.x, p.y, p.z);
    *py = p.y;
    *nx = e.x;
    *ny = e.y;
    *nz = e.z;
    if (hit) {
        float a = f_09a86c(s.x, s.z);
        t1.a = -a;
        f_099b98(&t1);
        f_09b394(t1, &e.z, &e.x);
        t2.a = f_09a86c(e.z, e.y);
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 1.0f;
        v.w = 1.0f;
        f_099b98(&t2);
        f_09b394(t2, &v.y, &v.z);
        t3.a = a;
        f_099b98(&t3);
        f_09b394(t3, &v.z, &v.x);
        *ux = v.x;
        *uy = v.y;
        *uz = v.z;
    }
    k = (int)pos;
    float a = f_0e2260(k);
    float b = f_0e2260(f_0e2690(k + 1));
    w.a = b - a;
    f_099b98(&w);
    w.a = w.a * (a - (int)a);
    f_099b98(&w);
    *head = a + w.a;
}
