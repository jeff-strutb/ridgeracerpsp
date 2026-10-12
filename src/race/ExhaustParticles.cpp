/* The exhaust and smoke particles object file (retail 0x032070 to 0x032e14). Two ring buffers
   of 64 byte particles: short lived exhaust and spark particles (40 frames) and longer lived
   smoke puffs (60 frames). Every frame each live particle is moved (its velocity decays), put
   through the view, and sorted into one of 256 depth buckets; the buckets are then drawn back
   to front as small textured sprites whose size, opacity and texture cell follow the
   particle's age along a cubic curve tabulated at startup. */

#include <stdlib.h>

struct Vec4 {
    float x, y, z, w;
};

struct View {
    char m0[288];
    float m288[16];
    char m352[136];
    float m488;
};

struct CInfo;

extern "C" {
void *f_125c4c(unsigned int align, unsigned int size);
CInfo *f_02347c(unsigned int id);
unsigned int *f_0249a0(CInfo *info, unsigned int *p);
void f_028c70(void);
void f_028ca8(void);
void f_028e9c(const float *m);
unsigned int *f_0cd528(unsigned int *p);
int f_0cc8c8(View *view, Vec4 *pos, float range);
Vec4 *f_027dc8(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);
Vec4 *f_027f3c(Vec4 *d, const Vec4 *a);
char *f_021b38(unsigned int size);
}

/* One particle. */
struct Particle {
    Particle *Next()
    {
        return next;
    }

    Particle *next;      /* next in its depth bucket */
    int color;
    unsigned char type;  /* which age table */
    char m9;
    unsigned char scale; /* opacity scale */
    char m11;
    unsigned short age;
    char m14[2];
    Vec4 pos;
    Vec4 vel;
    Vec4 screen;         /* the position in view space */
};

/* A ring buffer that drops its oldest entry when full. */
template <class T> struct Ring {
    void Init(int n)
    {
        buf = (T *)f_125c4c(64, n * sizeof(T));
        tail = head = 0;
        size = n;
    }
    void Free()
    {
        free(buf);
        buf = 0;
    }
    int Next(int i)
    {
        i++;
        if (i >= size)
            return i - size;
        return i;
    }
    int Count()
    {
        int n = tail - head;
        if (tail < head)
            n += size;
        return n;
    }
    T *At(int i)
    {
        return &buf[i];
    }
    void Pop()
    {
        head = Next(head);
    }
    T *Push()
    {
        T *e = &buf[tail];
        tail = Next(tail);
        if (tail == head)
            head = Next(head);
        return e;
    }

    int size;
    int head;
    int tail;
    T *buf;
};

/* The depth buckets: singly linked lists of particles. */
struct Buckets {
    void Clear()
    {
        for (int i = 0; i < count; i++)
            list[i] = 0;
    }

    void Init(int n)
    {
        count = n;
        list = (Particle **)malloc(n * sizeof(Particle *));
    }
    void Free()
    {
        free(list);
        list = 0;
    }
    Particle *Get(int k)
    {
        return list[k];
    }
    void Add(int k, Particle *e)
    {
        e->next = list[k];
        list[k] = e;
    }

    int count;
    Particle **list;
};

/* One age step of a particle's look: its texture cell, opacity and half size. */
struct Cell {
    unsigned char u0, v0, u1, v1;
    unsigned char alpha;
    unsigned char size;
};

/* One sprite vertex: texture coordinates and a position in signed bytes. */
struct Vtx {
    unsigned char u, v;
    signed char x, y, z;
};

/* A cubic curve of opacity and size over a particle's life: four control values each. */
struct Curve {
    int alpha[4];
    int size[4];
    int end;
};

class CParticles {
public:
    int f_032070(int n);
    Particle *f_032138(int type, const Vec4 *pos, const Vec4 *vel);
    void f_0321ec(const Vec4 *pos, int color);
    void f_03228c();
    unsigned int *f_032298(View *view, unsigned int *p);
    void f_032780(View *view, Particle *e);
    void f_0328b0();
    unsigned int *f_032c20(Particle *e, unsigned int *p);

    int step;
    Ring<Particle> fire;
    Ring<Particle> smoke;
    Buckets depth;
};

extern "C" void f_032918(void);
extern "C" void f_032ad0(int curve, int *alpha, int *size, float t);

CInfo *D_2403b0;
CInfo *D_2403b4;
Cell D_2403b8[40];
Cell D_2404a8[60];
float D_1d1b48 = 0.898f;
float D_1d1b4c = -200000.0f;
Cell *D_1d1b50[2] = { D_2403b8, D_2404a8 };
Curve D_1d1b5c[3] = {
    { { 95, 231, 201, 0 }, { 20, 60, 80, 128 }, -1 },
    { { 255, 215, 117, 0 }, { 40, 70, 105, 127 }, -1 },
    { { 255, 255, 255, 0 }, { 50, 255, 255, 255 }, -1 },
};

/* @implements 0x032070 us f_032070
   WHAT IT DOES: Starts the particles: n exhaust particles, 64 smoke puffs, 256 depth buckets,
   the two particle textures and the age tables. Returns the size of the smoke buffer. */
int CParticles::f_032070(int n)
{
    fire.Init(n);
    depth.Init(256);
    smoke.Init(64);
    step = 0;
    D_2403b0 = f_02347c(0xa000000);
    D_2403b4 = f_02347c(0xa000006);
    f_032918();
    return 4096;
}

/* @implements 0x032138 us f_032138
   WHAT IT DOES: Emits an exhaust or spark particle of the given type at a position with a
   velocity (the oldest one is dropped when all are in use). */
Particle *CParticles::f_032138(int type, const Vec4 *pos, const Vec4 *vel)
{
    Particle *e = fire.Push();
    e->type = type;
    e->pos = *pos;
    e->color = 0xffffff;
    e->age = 0;
    e->vel = *vel;
    return e;
}

/* @draft 0x0321ec us f_0321ec
   WHAT IT DOES: Emits a still smoke puff of the given colour at a position. */
void CParticles::f_0321ec(const Vec4 *pos, int color)
{
    Particle *e = smoke.Push();
    e->type = 1;
    e->color = color;
    e->pos = *pos;
    e->age = 0;
    e->vel.x = 0;
    e->vel.y = 0;
    e->vel.z = 0;
    e->scale = 0xff;
}

/* @implements 0x03228c us f_03228c
   WHAT IT DOES: Lets the particles move and age on the next draw. */
void CParticles::f_03228c()
{
    step = 1;
}

/* @draft 0x032298 us f_032298
   WHAT IT DOES: Draws the particles of one view: sets up the sprite render state, moves and
   ages every live particle (retiring the expired ones), sorts them by depth and draws them
   back to front. */
unsigned int *CParticles::f_032298(View *view, unsigned int *p)
{
    if (smoke.Count() == 0 && fire.Count() == 0)
        return p;
    *p++ = 0xdf000032;
    *p++ = 0x21000001;
    *p++ = 0x1e000001;
    *p++ = 0x22000001;
    *p++ = 0x17000000;
    *p++ = 0x1d000000;
    *p++ = 0x55ffffff;
    *p++ = 0xc9000100;
    *p++ = 0xdbff0106;
    *p++ = 0xc6000101;
    *p++ = 0x1f000001;
    *p++ = 0x12000081;
    *p++ = 0x3a000000;
    *p++ = 0x3b457a00;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b455ac0;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b3f8000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3c000000;
    *p++ = 0x3d3f8000;
    *p++ = 0x3d000000;
    *p++ = 0x3d000000;
    *p++ = 0x3d000000;
    *p++ = 0x3d3f8000;
    *p++ = 0x3d000000;
    *p++ = 0x3d000000;
    *p++ = 0x3d000000;
    *p++ = 0x3d3f8000;
    *p++ = 0x3d000000;
    *p++ = 0x3d000000;
    *p++ = 0x3d000000;
    p = f_0249a0(D_2403b0, p);
    f_028c70();
    f_028e9c(view->m288);
    depth.Clear();
    if (smoke.Count() > 0) {
        for (int i = smoke.head; i != smoke.tail; i = smoke.Next(i)) {
            Particle *e = smoke.At(i);
            if (e->age < 59) {
                f_032780(view, e);
                if (step)
                    e->age++;
            } else if (i == smoke.head) {
                smoke.Pop();
            }
        }
    }
    if (fire.Count() > 0) {
        *p++ = 0xe7000001;
        for (int i = fire.head; i != fire.tail; i = fire.Next(i)) {
            Particle *e = fire.At(i);
            if (e->age < 39) {
                f_032780(view, e);
                if (step)
                    e->age++;
            } else if (i == fire.head) {
                fire.Pop();
            }
        }
    }
    for (int i = depth.count - 1; i > 0; i--) {
        Particle *e = depth.Get(i);
        while (e) {
            p = f_032c20(e, p);
            if (!e->next)
                break;
            e = e->next;
        }
    }
    p = f_0cd528(p);
    f_028ca8();
    *p++ = 0xdbff0006;
    *p++ = 0xe7000000;
    *p++ = 0xc6000101;
    step = 0;
    return p;
}

/* @implements 0x032780 us f_032780
   WHAT IT DOES: Moves one particle (its velocity decays by 0.898 a frame) when stepping, then,
   if it is within 1000 units of the view, puts it in the depth bucket for its view depth
   (between the near plane and 200000 units). */
void CParticles::f_032780(View *view, Particle *e)
{
    if (step) {
        f_027e6c(&e->vel, &e->vel, D_1d1b48);
        f_027dc8(&e->pos, &e->pos, &e->vel);
    }
    if (!f_0cc8c8(view, &e->pos, 1000.0f))
        return;
    f_027f3c(&e->screen, &e->pos);
    float z = e->screen.z;
    if (z < D_1d1b4c)
        return;
    float near = view->m488;
    if (near <= z)
        return;
    Buckets *d = &depth;
    int k = (int)((z - near) / (D_1d1b4c - near) * 500.0f);
    int n = d->count;
    if (k >= n)
        k = n - 1;
    else if (k < 0)
        k = 0;
    d->Add(k, e);
}

/* @implements 0x0328b0 us f_0328b0
   WHAT IT DOES: Stops the particles and frees their buffers. */
void CParticles::f_0328b0()
{
    fire.Free();
    depth.Free();
    smoke.Free();
    D_2403b0 = 0;
}

/* @draft 0x032918 us f_032918
   WHAT IT DOES: Tabulates the particles' looks over their lives: for the 40 frames of an exhaust
   particle, opacity and size from curve 0 and one of 20 cells of a 4 x 5 grid of 32 x 16
   texels; for the 60 frames of a smoke puff, curve 1 and one fixed cell. */
void f_032918(void)
{
    int alpha, size;
    Cell *c = D_2403b8;
    for (int i = 0; i < 40; i++, c++) {
        float t = (float)i / 39.0f;
        f_032ad0(0, &alpha, &size, t * 255.0f);
        int k = (int)(t * 19.0f);
        int u = (k % 4) * 32;
        int v = (k / 4) * 16;
        if (size > 128)
            size = 127;
        c->alpha = alpha;
        c->u0 = u;
        c->v0 = v;
        c->u1 = u + 31;
        c->v1 = v + 15;
        c->size = size;
    }
    c = D_2404a8;
    for (int i = 0; i < 60; i++, c++) {
        f_032ad0(1, &alpha, &size, (float)i / 59.0f * 255.0f);
        if (size > 128)
            size = 127;
        c->alpha = alpha;
        c->u0 = 32;
        c->v0 = 80;
        c->u1 = 63;
        c->v1 = 103;
        c->size = size;
    }
}

/* @implements 0x032ad0 us f_032ad0
   WHAT IT DOES: Evaluates a particle curve at t (0 to 255) as a cubic Bezier in fixed point:
   the opacity (at most 255) and the half size (at most 127). */
void f_032ad0(int curve, int *alpha, int *size, float t)
{
    if (t > 255.0f)
        t = 255.0f;
    Curve *c = &D_1d1b5c[curve];
    int i = (int)t;
    int u = 255 - i;
    int uu = (u * u) >> 8;
    int ii = (i * i) >> 8;
    int b1 = (uu * i * 3) >> 8;
    int b2 = (u * ii * 3) >> 8;
    int b3 = (ii * i) >> 8;
    int b0 = (uu * u) >> 8;
    *alpha = (b0 * c->alpha[0] + b1 * c->alpha[1] + b2 * c->alpha[2] + b3 * c->alpha[3]) >> 8;
    *size = (b0 * c->size[0] + b1 * c->size[1] + b2 * c->size[2] + b3 * c->size[3]) >> 8;
    if (*alpha > 255)
        *alpha = 255;
    if (*size > 127)
        *size = 127;
}

static inline unsigned int Bits(float f)
{
    union {
        float f;
        unsigned int u;
    } x;
    x.f = f;
    return x.u;
}

/* @draft 0x032c20 us f_032c20
   WHAT IT DOES: Draws one particle as a sprite: places it at its view position, takes its look
   for its age, and writes a four vertex strip with its colour and opacity. */
unsigned int *CParticles::f_032c20(Particle *e, unsigned int *p)
{
    *p++ = 0x3a000009;
    const Vec4 *w = &e->screen;
    *p++ = (*(unsigned int *)&w->x >> 8) | 0x3b000000;
    *p++ = (*(unsigned int *)&w->y >> 8) | 0x3b000000;
    *p++ = (*(unsigned int *)&w->z >> 8) | 0x3b000000;
    Cell *c = &D_1d1b50[e->type][e->age];
    volatile unsigned int mask = 0xffffff;
    int alpha = c->alpha * e->scale;
    signed char s = c->size;
    signed char ns = -c->size;
    unsigned char u0 = c->u0;
    unsigned char v0 = c->v0;
    unsigned char u1 = c->u1;
    unsigned char v1 = c->v1;
    Vtx *q = (Vtx *)f_021b38(20);
    Vtx *v = q;
    q->u = u0;
    q->v = v0;
    q->x = s;
    q->y = s;
    q->z = 0;
    q++;
    q->u = u1;
    q->v = v0;
    q->x = ns;
    q->y = s;
    q->z = 0;
    q++;
    q->u = u0;
    q->v = v1;
    q->x = s;
    q->y = 0;
    q->z = 0;
    q++;
    q->u = u1;
    q->v = v1;
    q->x = ns;
    q->y = 0;
    q->z = 0;
    *p++ = e->color | 0x55000000;
    *p++ = (alpha >> 8) | 0x58000000;
    *p++ = ((((unsigned int)v >> 24) & 0xf) << 16) | 0x10000000;
    *p++ = ((unsigned int)v & mask) | 0x01000000;
    *p++ = 0x04040004;
    return p;
}
