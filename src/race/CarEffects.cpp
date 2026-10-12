/* The car effects object file (retail 0x032e14 to 0x034c0c): sparks thrown from under the
   cars, exhaust backfire flashes and nitro flames. Each car has an effect record: the
   transformed exhaust pipe positions and directions, a ring of spark bursts, the backfire
   animation frame and a pool of eighteen flame particles per pipe. The textures are the
   Spark, BackFireTex and NitroTex entries of the race texture pack; everything fades out
   with distance from the camera. A seeded random generator spreads the sparks and flames. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    Vec4 r[4];
};

struct CInfo;

extern "C" {
void *f_125c4c(unsigned int align, unsigned int size);
void free(void *p);
CInfo *f_02347c(unsigned int id);
unsigned int *f_0249a0(CInfo *info, unsigned int *p);
char *f_021b38(unsigned int size);
void f_028e9c(const Matrix *m);
void f_0cdb2c(Matrix *m);
Vec4 *f_027dc8(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027e0c(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);
Vec4 *f_027f3c(Vec4 *d, const Vec4 *a);
Vec4 *f_027f5c(Vec4 *d, const Vec4 *a);
}

extern float D_1d1bc8;
extern float D_1d1bcc;
extern float D_1d1bd0;

/* The car model data: the exhaust pipes in model space (their fourth words hold the flame
   quad's half width and half height) and how many pipes the car has. */
struct CarModelInfo {
    char m0[96];
    Vec4 pipe[2];
    char m128[19];
    signed char npipes;
};

/* The parts of a race car this file reads. */
struct RaceCar {
    char m0[144];
    Vec4 pos;
    char m160[192];
    Vec4 wheelL;
    Vec4 wheelR;
    char m384[192];
    Matrix mtx;
    char m640[1484];
    unsigned int flags;
    char m2128[1200];
    CarModelInfo *info;
    char m3332[68];
    float dist;
    char m3404[2363];
    char hidden;
};

/* The camera: its position, and the distance the effects fade over. */
struct View {
    Vec4 pos;
    char m16[480];
    float m496;
};

/* One burst of four sparks. */
struct Spark {
    Vec4 pos[4];
    Vec4 prev[4];
    Vec4 vel[4];
    float ground;
    unsigned char age;
};

struct SparkRing {
    int cap;
    int head;
    int tail;
    Spark *buf;
};

/* One car's effects. */
struct CarFx {
    Vec4 pipe[2];
    Vec4 flamePos[2][18];
    Vec4 flameVel[2][18];
    Vec4 pipeDir[2];
    SparkRing ring;
    char faded;
    RaceCar *car;
    float nitro;
    int backfire;
    signed char flame[18];
    float fade;
    unsigned char alpha;
    unsigned char m1273;
    unsigned char nitroOn;
    unsigned char m1275;
    unsigned char flameIdx;
};

struct CarFxMgr {
    int nsparks;
    int m4;
    int m8;
    void *sparks;
    CarFx *cars;
    int step;
    int ncars;
};

/* The effects' random generator. */
struct CRand {
    unsigned int seed;
    CRand() { seed = 0; }
    int Get()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return seed >> 8;
    }
};

CRand D_240610;
CInfo *D_240614;
CInfo *D_240618;
CInfo *D_24061c;

/* Vertex of a spark streak: colour then position. */
struct LineVtx {
    unsigned int color;
    float x, y, z;
} __attribute__((packed));

/* Vertex of a flame or flash quad: texture coordinates then position. */
struct QuadVtx {
    float u, v;
    float x, y, z;
} __attribute__((packed));

/* @draft 0x032e14 us f_032e14
   WHAT IT DOES: Sets up the effects for the given number of cars with room for the given
   number of sparks: one 64 byte aligned spark buffer, the car records (each with a ring of ten
   spark bursts, no backfire, no flames), and the three textures. Returns the bytes used. 
   Remaining: retail keeps the per car stores in the order shown but computes the return value and ring pointer differently (420 vs 392 bytes); not yet compared in detail. */
extern "C" int f_032e14(CarFxMgr *m, int ncars, int nsparks)
{
    int i, j;

    m->sparks = f_125c4c(64, nsparks * 80);
    m->nsparks = nsparks;
    m->m4 = 0;
    m->m8 = 0;
    m->cars = (CarFx *)f_125c4c(16, ncars * sizeof(CarFx));
    for (i = 0; i < ncars; i++) {
        CarFx *e = &m->cars[i];
        SparkRing *r;
        e->nitroOn = 0;
        e->backfire = 9;
        m->cars[i].m1275 = 0;
        e->car = 0;
        m->cars[i].flameIdx = 0;
        for (j = 0; j < 18; j++)
            m->cars[i].flame[j] = 0;
        r = &m->cars[i].ring;
        r->buf = (Spark *)f_125c4c(64, 10 * sizeof(Spark));
        r->cap = 10;
        r->tail = 0;
        r->head = 0;
    }
    m->ncars = ncars;
    m->step = 0;
    D_240614 = f_02347c(0xa000001);
    D_240618 = f_02347c(0xa000002);
    D_24061c = f_02347c(0xa000007);
    return nsparks * 80 + ncars * sizeof(CarFx);
}

/* @implements 0x032f9c us f_032f9c
   WHAT IT DOES: Frees every car's spark ring, then the spark buffer and the car records. */
extern "C" void f_032f9c(CarFxMgr *m)
{
    int i;

    for (i = 0; i < m->ncars; i++) {
        SparkRing *r = &m->cars[i].ring;
        free(r->buf);
        r->buf = 0;
    }
    free(m->sparks);
    m->sparks = 0;
    free(m->cars);
    m->cars = 0;
}

/* @implements 0x033028 us f_033028
   WHAT IT DOES: Lets the effects animate on the next draw (they advance only on frames where
   the race has stepped). */
extern "C" void f_033028(CarFxMgr *m)
{
    m->step = 1;
}

extern "C" void f_033834(CarFxMgr *m, Spark *s);
extern "C" unsigned int *f_033be0(CarFxMgr *m, CarFx *e, Spark *s, unsigned int *dl);
extern "C" unsigned int *f_033e40(CarFxMgr *m, CarFx *e, View *view, unsigned int *dl);
extern "C" unsigned int *f_034448(CarFxMgr *m, CarFx *e, View *view, unsigned int *dl);

static inline int RingNext(SparkRing *r, int i)
{
    int n = i + 1;
    if (n < r->cap)
        return n;
    return n - r->cap;
}

/* @draft 0x033034 us f_033034
   WHAT IT DOES: Draws all car effects. First, for each shown car, works out how far it is
   faded with distance from the camera and, if it has a backfire or flame running, moves its
   exhaust pipes into world space with their directions (straight back, or splayed for cars
   with twin pipes). Then draws, with the camera's rotation as world matrix, every car's spark
   bursts (advancing and retiring them when the race has stepped), the backfire flashes and the
   nitro flames, and finally restores the drawing state. 
   Remaining: first pass at the transcription; control flow follows retail but registers, stack layout and the clamp sequence are not yet compared. */
extern "C" unsigned int *f_033034(CarFxMgr *m, View *view, unsigned int *dl)
{
    Matrix rot;
    Vec4 dir;
    int i, k, first;

    f_0cdb2c(&rot);
    for (i = 0; i < m->ncars; i++) {
        CarFx *e = &m->cars[i];
        RaceCar *car = e->car;
        if (car->hidden == 0) {
            float f;
            e->faded = 1;
            f = (car->dist / view->m496 - -0.0f) / -80000.0f;
            e->fade = f;
            if (f < 0)
                e->fade = 0;
            else if (f > 1.0f)
                e->fade = 1.0f;
            else
                e->faded = 0;
            e->fade = 1.0f - e->fade;
            e->alpha = (unsigned int)(e->fade * 115.0f);
            if (e->backfire < 10 || e->nitroOn) {
                f_028e9c(&car->mtx);
                for (k = 0; k < e->car->info->npipes; k++) {
                    f_027f3c(&e->pipe[k], &e->car->info->pipe[k]);
                    if (e->car->flags & 4) {
                        dir.x = k ? 0.5f : -0.5f;
                        dir.y = 0;
                        dir.z = 0.5f;
                    } else if (e->car->flags & 8) {
                        dir.x = k ? 0.2f : -0.2f;
                        dir.y = 0;
                        dir.z = 0.85f;
                    } else {
                        dir.x = 0;
                        dir.y = 0;
                        dir.z = 1.0f;
                    }
                    f_027f5c(&e->pipeDir[k], &dir);
                }
            }
        }
    }
    *dl++ = 0x1200019c;
    *dl++ = 0xe7000001;
    *dl++ = 0x1e000000;
    *dl++ = 0x17000000;
    *dl++ = 0x1f000000;
    *dl++ = 0x1d000000;
    *dl++ = 0xdf0000a2;
    *dl++ = 0xe1ffffff;
    *dl++ = 0x21000001;
    *dl++ = 0xc9000100;
    *dl++ = 0x47470002;
    *dl++ = 0x3a000000;
    *dl++ = 0x3b3f8000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b3f8000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b3f8000;
    for (i = 0; i < m->ncars; i++) {
        CarFx *e = &m->cars[i];
        if (e->car->hidden == 0) {
            int s = e->ring.head;
            first = 1;
            while (s != e->ring.tail) {
                Spark *p = &e->ring.buf[s];
                if (m->step) {
                    if (p->age < 16) {
                        f_033834(m, p);
                        p->age++;
                    } else {
                        if (s == e->ring.head)
                            e->ring.head = RingNext(&e->ring, e->ring.head);
                        s = RingNext(&e->ring, s);
                        continue;
                    }
                }
                if (!e->faded) {
                    if (first) {
                        unsigned int *t = (unsigned int *)&e->car->pos;
                        *dl++ = 0x3a000009;
                        *dl++ = ((t[0] >> 8) & 0xffffff) | 0x3b000000;
                        *dl++ = ((t[1] >> 8) & 0xffffff) | 0x3b000000;
                        *dl++ = ((t[2] >> 8) & 0xffffff) | 0x3b000000;
                    }
                    dl = f_033be0(m, e, p, dl);
                    first = 0;
                }
                s = RingNext(&e->ring, s);
            }
        }
    }
    {
        unsigned int *t = (unsigned int *)&rot;
        *dl++ = 0x3a000000;
        *dl++ = (t[0] >> 8) | 0x3b000000;
        *dl++ = (t[1] >> 8) | 0x3b000000;
        *dl++ = (t[2] >> 8) | 0x3b000000;
        *dl++ = (t[4] >> 8) | 0x3b000000;
        *dl++ = (t[5] >> 8) | 0x3b000000;
        *dl++ = (t[6] >> 8) | 0x3b000000;
        *dl++ = (t[8] >> 8) | 0x3b000000;
        *dl++ = (t[9] >> 8) | 0x3b000000;
        *dl++ = (t[10] >> 8) | 0x3b000000;
    }
    *dl++ = 0x3c000009;
    *dl++ = 0x3d000000;
    *dl++ = 0x3d000000;
    *dl++ = 0x3d000000;
    *dl++ = 0x1e000001;
    *dl++ = 0x12000183;
    *dl++ = 0x55ffffff;
    first = 1;
    for (i = 0; i < m->ncars; i++) {
        CarFx *e = &m->cars[i];
        if (e->backfire < 10) {
            if (e->car->hidden == 0 && !e->faded) {
                if (first)
                    dl = f_0249a0(D_240618, dl);
                first = 0;
                if (e->backfire >= 9)
                    continue;
                dl = f_033e40(m, e, view, dl);
            }
            if (m->step)
                e->backfire++;
        }
    }
    first = 1;
    for (i = 0; i < m->ncars; i++) {
        CarFx *e = &m->cars[i];
        if (e->nitroOn && e->car->hidden == 0 && !e->faded) {
            if (first)
                dl = f_0249a0(D_24061c, dl);
            first = 0;
            dl = f_034448(m, e, view, dl);
        }
    }
    *dl++ = 0xe7000000;
    *dl++ = 0xdf000032;
    *dl++ = 0x47470000;
    m->step = 0;
    return dl;
}

/* @implements 0x033834 us f_033834
   WHAT IT DOES: Moves a burst's four sparks one step: drag on the velocity, gravity, the old
   position kept for the streak, and a bounce (velocity reversed) off the ground height. */
extern "C" void f_033834(CarFxMgr *m, Spark *s)
{
    int k;

    for (k = 0; k < 4; k++) {
        f_027e6c(&s->vel[k], &s->vel[k], D_1d1bc8);
        s->vel[k].y -= D_1d1bcc;
        s->prev[k] = s->pos[k];
        f_027dc8(&s->pos[k], &s->pos[k], &s->vel[k]);
        if (s->ground > s->pos[k].y) {
            s->vel[k].y = -s->vel[k].y;
            s->pos[k].y = s->ground;
        }
    }
}

/* @draft 0x033918 us f_033918
   WHAT IT DOES: Throws a new burst of sparks from a car, at the given fraction of the way
   between its two rear contact points: four sparks fly along the car's heading, lifted, at
   random spreads, with the ground at the start height. The oldest burst is dropped when the
   ring is full. 
   Remaining: the ring push and random spread follow retail; scheduling and register use of the interpolation differ (700 vs 712 bytes). */
extern "C" void f_033918(CarFxMgr *m, int i, float t)
{
    CarFx *e = &m->cars[i];
    SparkRing *r = &e->ring;
    Spark *s = &r->buf[r->tail];
    RaceCar *car;
    float u, x, y, z;
    Vec4 v;
    int k;

    r->tail = RingNext(r, r->tail);
    if (r->tail == r->head)
        r->head = RingNext(r, r->head);
    s->age = 0;
    car = e->car;
    u = 1.0f - t;
    y = (car->wheelR.y * t + car->wheelL.y * u) - car->pos.y;
    s->ground = y;
    z = (car->wheelR.z * t + car->wheelL.z * u) - car->pos.z;
    x = (car->wheelR.x * t + car->wheelL.x * u) - car->pos.x;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    v.w = 0;
    v.x = car->mtx.r[2].x + 0.0f;
    v.y = car->mtx.r[2].y + 0.5f;
    v.z = car->mtx.r[2].z + 0.0f;
    for (k = 0; k < 4; k++) {
        float dx, dy, dz;
        s->pos[k].x = x;
        s->pos[k].y = y;
        s->pos[k].z = z;
        dx = ((float)D_240610.Get() * 5.9604645e-08f - 0.5f) * D_1d1bd0 * 750.0f;
        dy = ((float)D_240610.Get() * 5.9604645e-08f - 0.5f) * D_1d1bd0 * 750.0f;
        dz = ((float)D_240610.Get() * 5.9604645e-08f - 0.5f) * D_1d1bd0 * 750.0f;
        f_027e6c(&s->vel[k], &v, 600.0f);
        s->vel[k].x += dx;
        s->vel[k].y += dy;
        s->vel[k].z += dz;
    }
}

/* @draft 0x033be0 us f_033be0
   WHAT IT DOES: Draws a burst's four sparks as streaks from their old to their new position,
   bright orange fading to dark red, each drawn five times with small screen offsets to make it
   thicker. 
   Remaining: the packed vertex copies and the command loop are not yet compared word by word. */
extern "C" unsigned int *f_033be0(CarFxMgr *m, CarFx *e, Spark *s, unsigned int *dl)
{
    static const unsigned int ox[5] = { 0x70f0, 0x7100, 0x7110, 0x7100, 0x7100 };
    static const unsigned int oy[5] = { 0x7780, 0x7770, 0x7780, 0x7790, 0x7780 };
    int k, l;

    for (k = 0; k < 4; k++) {
        LineVtx *v = (LineVtx *)f_021b38(32);
        unsigned int base = 0x10000000 | ((((unsigned int)v >> 24) & 0xf) << 16);
        unsigned int addr = ((unsigned int)v & 0xffffff) | 0x01000000;
        v[0].color = (e->alpha << 24) | 0x236bff;
        v[0].x = s->pos[k].x;
        v[0].y = s->pos[k].y;
        v[0].z = s->pos[k].z;
        v[1].color = 0x002593ff;
        v[1].x = s->prev[k].x;
        v[1].y = s->prev[k].y;
        v[1].z = s->prev[k].z;
        *dl++ = base;
        for (l = 0; l < 5; l++) {
            *dl++ = ox[l] | 0x4c000000;
            *dl++ = oy[l] | 0x4d000000;
            *dl++ = addr;
            *dl++ = 0x04020002;
        }
    }
    return dl;
}

/* @draft 0x033e18 us f_033e18
   WHAT IT DOES: Fires a backfire flash on a car (restarts its animation) unless its nitro is
   burning. 
   Remaining: retail adds the element offset to the base (addu v0,v0,a2); this source adds base plus offset. */
extern "C" void f_033e18(CarFxMgr *m, int i)
{
    CarFx *e = &m->cars[i];
    if (!e->nitroOn)
        e->backfire = 0;
}

static inline void PutQuad(QuadVtx *v, float u, float w, const Vec4 *c)
{
    v[0].u = u;
    v[0].v = w;
    v[0].x = c[0].x;
    v[0].y = c[0].y;
    v[0].z = c[0].z;
}

/* @draft 0x033e40 us f_033e40
   WHAT IT DOES: Draws a car's backfire flash at each exhaust pipe: a camera facing quad
   showing the animation frame (nine frames on a three by three sheet), faded with distance. 
   Remaining: same size as retail; byte store order of the packed vertices and register use differ. */
extern "C" unsigned int *f_033e40(CarFxMgr *m, CarFx *e, View *view, unsigned int *dl)
{
    Vec4 c[4];
    CarModelInfo *info = e->car->info;
    float w = info->pipe[0].w;
    float h = info->pipe[1].w;
    int k;

    c[0].x = -w;
    c[0].y = h;
    c[0].z = 0;
    c[0].w = 0;
    c[1].x = w;
    c[1].y = h;
    c[1].z = 0;
    c[1].w = 0;
    c[2].x = -w;
    c[2].y = -h;
    c[2].z = 0;
    c[2].w = 0;
    c[3].x = w;
    c[3].y = -h;
    c[3].z = 0;
    c[3].w = 0;
    *dl++ = ((unsigned int)(e->fade * 255.0f) & 0xff) | 0x58000000;
    for (k = 0; k < e->car->info->npipes; k++) {
        Vec4 *p = &e->pipe[k];
        float d[3];
        unsigned int *t = (unsigned int *)d;
        int f, q, r;
        float u, v0;
        QuadVtx *v;

        d[0] = p->x - view->pos.x;
        d[1] = p->y - view->pos.y;
        d[2] = p->z - view->pos.z;
        *dl++ = 0x3a000009;
        *dl++ = ((t[0] >> 8) & 0xffffff) | 0x3b000000;
        *dl++ = ((t[1] >> 8) & 0xffffff) | 0x3b000000;
        *dl++ = ((t[2] >> 8) & 0xffffff) | 0x3b000000;
        f = e->backfire;
        q = f / 3;
        r = f - q * 3;
        u = (float)r * (1.0f / 3.0f);
        v0 = (float)q * (1.0f / 3.0f);
        v = (QuadVtx *)f_021b38(80);
        v[0].u = u;
        v[0].v = v0;
        v[0].x = c[0].x;
        v[0].y = c[0].y;
        v[0].z = c[0].z;
        v[1].u = u + (1.0f / 3.0f);
        v[1].v = v0;
        v[1].x = c[1].x;
        v[1].y = c[1].y;
        v[1].z = c[1].z;
        v[2].u = u;
        v[2].v = v0 + (1.0f / 3.0f);
        v[2].x = c[2].x;
        v[2].y = c[2].y;
        v[2].z = c[2].z;
        v[3].u = u + (1.0f / 3.0f);
        v[3].v = v0 + (1.0f / 3.0f);
        v[3].x = c[3].x;
        v[3].y = c[3].y;
        v[3].z = c[3].z;
        *dl++ = 0x10000000 | ((((unsigned int)v >> 24) & 0xf) << 16);
        *dl++ = ((unsigned int)v & 0xffffff) | 0x01000000;
        *dl++ = 0x04040004;
    }
    return dl;
}

/* @draft 0x034380 us f_034380
   WHAT IT DOES: Turns a car's nitro flames on at full size; when they were off, clears its
   flame particles and stops any backfire. 
   Remaining: retail loads the record base before the index shift and adds offset plus base; two words of order. */
extern "C" void f_034380(CarFxMgr *m, int i)
{
    CarFx *e = &m->cars[i];
    int j;

    e->nitro = 1.0f;
    if (!e->nitroOn) {
        e->nitroOn = 1;
        e->backfire = 9;
        m->cars[i].m1275 = 1;
        m->cars[i].flameIdx = 0;
        m->cars[i].m1273 = 0;
        for (j = 0; j < 18; j++)
            m->cars[i].flame[j] = -1;
    }
}

/* @implements 0x034410 us f_034410
   WHAT IT DOES: Sets the size of a car's nitro flames. */
extern "C" void f_034410(CarFxMgr *m, int i, float s)
{
    m->cars[i].nitro = s;
}

/* @implements 0x03442c us f_03442c
   WHAT IT DOES: Turns a car's nitro flames off. */
extern "C" void f_03442c(CarFxMgr *m, int i)
{
    m->cars[i].nitroOn = 0;
}

/* @draft 0x034448 us f_034448
   WHAT IT DOES: Draws a car's nitro flames. When the race has stepped, a new flame particle
   leaves each pipe along the pipe's direction at a random speed scaled by the nitro size, and
   every live particle slows and moves on and ages one frame (eighteen frames, two per picture
   of a three by three sheet). Each live particle is drawn as a camera facing quad at its pipe,
   faded with distance and scaled by the nitro size. 
   Remaining: first pass at the transcription; register and stack slot use differ throughout. */
extern "C" unsigned int *f_034448(CarFxMgr *m, CarFx *e, View *view, unsigned int *dl)
{
    Vec4 c[4];
    Vec4 tmp;
    CarModelInfo *info;
    int idx = (e->flameIdx + 1) % 18 & 0xff;
    float w, h;
    int k, j;

    info = e->car->info;
    w = info->pipe[0].w;
    h = info->pipe[1].w;
    c[0].x = -w;
    c[0].y = h;
    c[0].z = 0;
    c[0].w = 0;
    c[1].x = w;
    c[1].y = h;
    c[1].z = 0;
    c[1].w = 0;
    c[2].x = -w;
    c[2].y = -h;
    c[2].z = 0;
    c[2].w = 0;
    c[3].x = w;
    c[3].y = -h;
    c[3].z = 0;
    c[3].w = 0;
    if (m->step) {
        e->flame[idx] = 0;
        e->flameIdx = idx;
    }
    for (k = 0; k < e->car->info->npipes; k++) {
        if (m->step) {
            float sp = ((float)D_240610.Get() * 5.9604645e-08f + 0.2f) * 160.0f * e->nitro;
            e->flamePos[k][idx].x = 0;
            e->flamePos[k][idx].y = 0;
            e->flamePos[k][idx].z = 0;
            f_027e6c(&e->flameVel[k][idx], &e->pipeDir[k], sp);
        }
        for (j = 0; j < 18; j++) {
            int n = (j + idx) % 18;
            signed char *fr = &e->flame[n];
            Vec4 *pos, *vel;
            unsigned int *t = (unsigned int *)&tmp;
            int f, q, r;
            float u, v0;
            QuadVtx *v;

            if (*fr < 0)
                continue;
            pos = &e->flamePos[k][n];
            vel = &e->flameVel[k][n];
            f_027dc8(&tmp, pos, &e->pipe[k]);
            f_027e0c(&tmp, &tmp, &view->pos);
            *dl++ = 0x3a000009;
            *dl++ = ((t[0] >> 8) & 0xffffff) | 0x3b000000;
            *dl++ = ((t[1] >> 8) & 0xffffff) | 0x3b000000;
            *dl++ = ((t[2] >> 8) & 0xffffff) | 0x3b000000;
            *dl++ = ((unsigned int)(e->nitro * 255.0f * e->fade) & 0xff) | 0x58000000;
            f = *fr / 2;
            q = f / 3;
            r = f - q * 3;
            u = (float)r * (1.0f / 3.0f);
            v0 = (float)q * (1.0f / 3.0f);
            v = (QuadVtx *)f_021b38(80);
            v[0].u = u;
            v[0].v = v0;
            v[0].x = c[0].x;
            v[0].y = c[0].y;
            v[0].z = c[0].z;
            v[1].u = u + (1.0f / 3.0f);
            v[1].v = v0;
            v[1].x = c[1].x;
            v[1].y = c[1].y;
            v[1].z = c[1].z;
            v[2].u = u;
            v[2].v = v0 + (1.0f / 3.0f);
            v[2].x = c[2].x;
            v[2].y = c[2].y;
            v[2].z = c[2].z;
            v[3].u = u + (1.0f / 3.0f);
            v[3].v = v0 + (1.0f / 3.0f);
            v[3].x = c[3].x;
            v[3].y = c[3].y;
            v[3].z = c[3].z;
            *dl++ = 0x10000000 | ((((unsigned int)v >> 24) & 0xf) << 16);
            *dl++ = ((unsigned int)v & 0xffffff) | 0x01000000;
            *dl++ = 0x04040004;
            if (m->step && k == 0)
                (*fr)++;
            if (m->step) {
                f_027e6c(vel, vel, 0.9f);
                f_027dc8(pos, pos, vel);
            }
        }
    }
    return dl;
}

/* @implements 0x034bc4 us __static_initialization_and_destruction_0
   WHAT IT DOES: Seeds the effects' random generator with 0 at start up. */
/* @implements 0x034bec us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
