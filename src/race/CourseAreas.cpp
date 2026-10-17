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
   DIFFERS: 43/57 words differ, first at +0x10 (not yet worked). */
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
    D_2456c4 = m / 2;
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
   DIFFERS: 65/84 words differ, first at +0x38 (not yet worked). */
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
    *px = x * (1.0f - d) + p->x * d;
    *py = y * (1.0f - d) + (p->y + (float)danmen[p->section].h[32]) * d;
    *pz = z * (1.0f - d) + p->z * d;
}

/* @draft 0x0e2148 us CourseAreas8f_0e2148
   WHAT IT DOES: Returns the road heading at a distance, interpolated the short way round.
   DIFFERS: 51/70 words differ, first at +0x8 (not yet worked). */
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

/* @draft 0x0e2334 us CourseAreas8f_0e2334
   WHAT IT DOES: Returns the ground height at a sideways offset (-32 to 31) and a distance.
   DIFFERS: 35/39 words differ, first at +0x0 (not yet worked). */
float CourseAreas::f_0e2334(float a, float d)
{
    int k = (int)a;
    RoadPoint *p = &road[(int)f_0e26dc(d)];

    if (k < -32)
        k = -32;
    if (k >= 32)
        k = 31;
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
   DIFFERS: 51/79 words differ, first at +0x50 (not yet worked). */
int CourseAreas::f_0e2558(int a, int b, float x, float z)
{
    float min = -1.0f;
    int best = a;
    int i, j;
    float dx, dz;

    for (i = a - 50; i < n && i < a + 50; i++) {
        j = f_0e2690(i);
        if (j < 0 || j < b)
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
   DIFFERS: 29/43 words differ, first at +0x4 (not yet worked). */
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
   DIFFERS: 42/62 words differ, first at +0xc (not yet worked). */
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
   DIFFERS: 28/40 words differ, first at +0x30 (not yet worked). */
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
   DIFFERS: 15/37 words differ, first at +0x14 (not yet worked). */
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
   DIFFERS: 6/29 words differ, first at +0x14 (not yet worked). */
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
