/* The blown leaves object file (retail 0x035ef0 to 0x03680c, the "Leaf" texture). A ring
   buffer of 96 byte leaves: each is thrown up with a velocity, falls under gravity while a
   gust that changes now and then pushes it about, spins about two axes, and is retired when
   it reaches the ground or after 600 frames. Each live leaf is drawn as one textured quad. */

#include <stdlib.h>

/* The vector unit code is written in assembly with the assembler's reordering off, so it never
   moves an instruction into a following delay slot. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    unsigned int m[16];
} __attribute__((aligned(16)));

struct CInfo;

extern "C" {
void *f_125c4c(unsigned int align, unsigned int size);
CInfo *f_02347c(unsigned int id);
unsigned int *f_0249a0(CInfo *info, unsigned int *p);
void f_028c70(void);
void f_028ca8(void);
void f_028d94(Matrix *m);
void f_02842c(void);
void f_0284bc(float a);
void f_02853c(float a);
void f_02880c(float x, float y, float z);
void f_02884c(float x, float y, float z);
Vec4 *f_027dc8(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);
union Angle;
Angle *f_0ccaec(Angle *a);
}

/* An angle in radians. */
union Angle {
    float a;
};

/* One leaf. */
struct Leaf {
    Vec4 pos;
    Vec4 vel;
    Vec4 gust;            /* the push of the current gust */
    float t;              /* how far through the gust (from 0 to 1) */
    float dt;             /* how fast the gust passes */
    Angle rx;             /* spin angles */
    Angle rz;
    int m64;
    float ground;         /* the height it lands at */
    int age;
    unsigned int color;
    unsigned char *count; /* the thrower's count of live leaves */
    int m84[3];
};

/* One quad vertex: texture coordinates and a position in signed bytes. */
struct Vtx {
    unsigned char u, v;
    signed char x, y, z;
};

/* The random number generator of the leaves. */
struct CRand {
    CRand() : seed(0) {}
    unsigned int seed;
};

extern float D_1d1be8;
extern float D_1d1bec;
extern float D_1d1c08;
CInfo *D_240620;
CRand D_240624;
Vtx D_240628[4];

/* A random number from 0 to 1. */
static inline float Rand()
{
    D_240624.seed = D_240624.seed * 0x19660d + 0x3c6ef35f;
    return (int)(D_240624.seed >> 8) * 5.96046448e-08f;
}

static const float D_1a20ec = 1.5f;

class CLeaves {
public:
    int f_035ef0(int n);
    void f_035fcc();
    void f_035ff8();
    unsigned int *f_0362a8(unsigned int *p);
    Leaf *f_036600(const Vec4 *pos, const Vec4 *vel, unsigned char *count, float ground);

    int Next(int i)
    {
        i++;
        if (i >= size)
            return i - size;
        return i;
    }

    int size;
    int head;
    int tail;
    Leaf *buf;
    int step;
};

/* @draft 0x035ef0 us f_035ef0
   WHAT IT DOES: Starts the leaves: room for n of them, the four corners of the leaf quad (a
   flat square on the ground plane, its far edge in front) and the leaf texture.
   Remaining difference: retail keeps the texture record in a0 (move a0,v0) and stores it after
   setting the zero result; here it is stored from v0 first (retail is 2 words longer). */
int CLeaves::f_035ef0(int n)
{
    Leaf *b = (Leaf *)f_125c4c(64, n * sizeof(Leaf));
    step = 1;
    buf = b;
    size = n;
    head = tail = 0;
    D_240628[0].x = -63;
    D_240628[0].y = 0;
    D_240628[0].z = 0;
    D_240628[1].x = 63;
    D_240628[1].y = 0;
    D_240628[1].z = 0;
    D_240628[2].x = -63;
    D_240628[2].y = 0;
    D_240628[2].z = -127;
    D_240628[3].x = 63;
    D_240628[3].y = 0;
    D_240628[3].z = -127;
    D_240628[0].u = 0;
    D_240628[0].v = 0;
    D_240628[1].u = 128;
    D_240628[1].v = 0;
    D_240628[2].u = 0;
    D_240628[2].v = 128;
    D_240628[3].u = 128;
    D_240628[3].v = 128;
    D_240620 = f_02347c(0xa000003);
    return 0;
}

/* @draft 0x035fcc us f_035fcc
   WHAT IT DOES: Frees the leaves. */
void CLeaves::f_035fcc()
{
    free(buf);
    buf = 0;
}

/* @draft 0x035ff8 us f_035ff8
   WHAT IT DOES: Moves every live leaf one frame. A leaf that has reached the ground or is older
   than 600 frames is retired (and its thrower's count lowered). Otherwise it is pushed by its
   gust (a new random gust starts when the old one has passed), falls under gravity, slows
   down by a slightly random drag, moves, and spins.
   Remaining difference: block layout. Retail falls through from the height test into the
   retire path and places the age test with the live path at the end; here the age test
   follows the height test. The constants f23 to f27 are also assigned in a different order. */
void CLeaves::f_035ff8()
{
    float gravity;
    float drag;

    drag = D_1d1be8 * 0.25f;
    gravity = D_1d1bec;

    for (int i = head; i != tail; i = Next(i)) {
        Leaf *e = &buf[i];
        e->age++;
        if (e->pos.y <= e->ground + 1.0f) {
            if (i == head)
                head = Next(i);
            if (e->count)
                (*e->count)--;
        } else if (e->age >= 601) {
            if (i == head)
                head = Next(i);
            if (e->count)
                (*e->count)--;
        } else {
            Vec4 r;
            __asm__ volatile(VFPU_BEGIN "vrndf1.t C010\n\tlv.s S000, %1\n\t.word 0xdd0000c0\n\t"
                             "vsub.t C020, C010, C000\n\tsv.q C020, %0" VFPU_END
                             : "=m"(r) : "m"(D_1a20ec) : "memory");
            if (e->t < 1.0f) {
                __asm__ volatile(VFPU_BEGIN "lv.q C400, %0\n\tlv.q C410, %1\n\tlv.s S420, %2\n\t"
                                 "vscl.t C430, C410, S420\n\tvadd.t C410, C430, C400\n\tsv.q C410, %0" VFPU_END
                                 : "+m"(e->vel) : "m"(e->gust), "m"(e->t) : "memory");
                e->t += e->dt;
            } else {
                f_027e6c(&e->gust, &r, D_1d1c08);
                e->gust.y *= 0.7f;
                e->t = 0;
                e->dt = Rand() * 0.1f;
            }
            e->vel.y -= gravity;
            f_027e6c(&e->vel, &e->vel, D_1d1be8 + r.x * drag);
            f_027dc8(&e->pos, &e->pos, &e->vel);
            e->rx.a += 0.147259027f;
            f_0ccaec(&e->rx);
            e->rz.a += 0.392699082f;
            f_0ccaec(&e->rz);
        }
    }
    step = 0;
}

/* @draft 0x0362a8 us f_0362a8
   WHAT IT DOES: Draws the leaves: sets the render state for the leaf texture, then for every
   leaf above the ground loads a transform (spun, stretched to 190 by 532, placed at the leaf)
   and draws the leaf quad in the leaf's colour.
   Remaining difference: the hoisted high halves of the 190 and 532 constants swap s7 and s8
   (2 words); everything else matches. */
unsigned int *CLeaves::f_0362a8(unsigned int *p)
{
    p = f_0249a0(D_240620, p);
    f_028c70();
    *p++ = 0x1d000000;
    *p++ = 0x21000001;
    *p++ = 0xdf000032;
    *p++ = 0x1f000001;
    *p++ = 0x1e000001;
    *p++ = 0x17000000;
    *p++ = 0x12000081;
    *p++ = (((unsigned int)D_240628 >> 24) & 0xf) << 16 | 0x10000000;
    *p++ = 0x580000ff;
    for (int i = head; i != tail; i = Next(i)) {
        Leaf *e = &buf[i];
        if (e->pos.y <= e->ground + 1.0f)
            continue;
        {
            Matrix m;
            f_02842c();
            f_0284bc(e->rx.a);
            f_02853c(e->rz.a);
            f_02884c(190.0f, 1.0f, 532.0f);
            f_02880c(e->pos.x, e->pos.y, e->pos.z);
            f_028d94(&m);
            *p++ = 0x3a000000;
            *p++ = ((m.m[0] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[1] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[2] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[4] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[5] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[6] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[8] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[9] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[10] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[12] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[13] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = ((m.m[14] >> 8) & 0xffffff) | 0x3b000000;
            *p++ = e->color | 0x55000000;
            *p++ = ((int)D_240628 & 0xffffff) | 0x01000000;
            *p++ = 0x04040004;
        }
    }
    step = 0;
    *p++ = 0x1d000001;
    f_028ca8();
    return p;
}

/* @draft 0x036600 us f_036600
   WHAT IT DOES: Throws up one leaf (the oldest is dropped when all are in use) at a position
   with a velocity, a fresh gust due at once, random spin angles and the height it lands at; it
   remembers and raises the thrower's count of live leaves. Returns the leaf. */
Leaf *CLeaves::f_036600(const Vec4 *pos, const Vec4 *vel, unsigned char *count, float ground)
{
    Angle a[2];
    Leaf *e = &buf[tail];
    tail = Next(tail);
    if (tail == head)
        head = Next(head);
    e->t = 2.0f;
    e->vel = *vel;
    e->pos = *pos;
    a[0].a = Rand() * 6.28318531f;
    f_0ccaec(&a[0]);
    e->rx = a[0];
    a[1].a = Rand() * 6.28318531f;
    f_0ccaec(&a[1]);
    e->rz = a[1];
    e->age = 0;
    e->ground = ground;
    e->count = count;
    if (count)
        (*count)++;
    return e;
}

/* @draft 0x0367c4 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, seeds the leaves' random numbers with 0. */

/* @draft 0x0367ec us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */
