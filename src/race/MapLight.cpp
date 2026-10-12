/* The course lighting object file (retail 0x02c93c to 0x02db68). Reflection mapping of the
   reflective course meshes on the vector unit (each vertex gets sphere map coordinates from
   the camera position and its normal), and the light the course casts on a car: the car's
   position is looked up in two sets of shadow polygons, whose vertex colours give the light
   intensity there, and the course's light colours are blended from it into the packed
   ambient, diffuse and specular colours the car is drawn with. */

#include <math.h>

extern "C" {
int f_126f1c(const char *fmt, ...);
void f_028b3c(void *save);
void f_028b74(void *save);
void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...);
}

/* The vector unit code is written in assembly with the assembler's reordering off. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

extern "C" Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);

/* The camera position (x, y, z) and, in w, the reflection's horizontal turn. */
extern Vec4 D_23ffb0;
extern float D_23ffbc;

/* Constants for the reflection: 0, 0.5, 1 and 2. */
extern Vec4 D_1d1a80;

/* @implements 0x02c93c us f_02c93c
   WHAT IT DOES: Sets the reflection's horizontal turn from an angle in radians (as a fraction
   of a full turn, which moves the reflection texture sideways). */
extern "C" void f_02c93c(float angle)
{
    D_23ffbc = angle / 3.14159f * 0.5f;
}

/* @implements 0x02c960 us f_02c960
   WHAT IT DOES: Records the camera position the reflections are computed from. */
extern "C" void f_02c960(float *pos)
{
    D_23ffb0.x = pos[0];
    D_23ffb0.y = pos[1];
    D_23ffb0.z = pos[2];
}

/* A source vertex (colour, normal, position) and the vertex written for the GE (sphere map
   coordinates, colour, position). */
struct SrcVert {
    unsigned int color;
    float nx, ny, nz;
    float x, y, z;
};
struct EnvVert {
    float u, v;
    unsigned int color;
    float x, y, z;
};

/* The sphere map coordinates of one vertex on the vector unit, with the camera position in
   C730 and the constants in C720: the direction to the camera is reflected about the normal;
   v comes from the reflection's height, u from its horizontal direction (bent towards the
   viewer) plus the reflection's turn. R is the vertex's matrix (0, 2 or 4), T the next matrix
   (for temporaries) and K the vertex's index in the batch. */
#define ENV_UV(R, T, K, src, dst)                                                               \
    "lv.s S" #R "00, 16+28*" #K "(" src ")\n\tlv.s S" #R "01, 20+28*" #K "(" src ")\n\t"       \
    "lv.s S" #R "02, 24+28*" #K "(" src ")\n\tlv.s S" #R "10, 4+28*" #K "(" src ")\n\t"        \
    "lv.s S" #R "11, 8+28*" #K "(" src ")\n\tlv.s S" #R "12, 12+28*" #K "(" src ")\n\t"        \
    "vsub.t C" #R "00, C730, C" #R "00\n\t"                                                    \
    "vdot.t S" #T "30, C" #R "00, C" #R "00\n\t"                                               \
    "vrsq.s S" #T "30, S" #T "30\n\t"                                                          \
    "vscl.t C" #R "00, C" #R "00, S" #T "30\n\t"                                               \
    "vdot.t S" #T "30, C" #R "00, C" #R "10\n\t"                                               \
    "vscl.t C" #R "20, C" #R "10, S" #T "30\n\t"                                               \
    "vadd.t C" #R "20, C" #R "20, C" #R "20\n\t"                                               \
    "vsub.t C" #R "20, C" #R "20, C" #R "00\n\t"                                               \
    "vneg.s S" #R "21, S" #R "21\n\t"                                                          \
    "vmul.s S" #R "31, S" #R "21, S721\n\t"                                                    \
    "vadd.s S" #R "31, S" #R "31, S721\n\t"                                                    \
    "vadd.s S" #R "21, S" #R "22, S720\n\t"                                                    \
    "vdot.p S" #T "32, C" #R "20, C" #R "20\n\t"                                               \
    "vrsq.s S" #T "32, S" #T "32\n\t"                                                          \
    "vscl.p C" #R "20, C" #R "20, S" #T "32\n\t"                                               \
    "vadd.s S" #R "21, S" #R "21, S723\n\t"                                                    \
    "vdot.p S" #T "32, C" #R "20, C" #R "20\n\t"                                               \
    "vrsq.s S" #T "32, S" #T "32\n\t"                                                          \
    "vmul.s S" #R "30, S" #T "32, S" #R "20\n\t"                                               \
    "vmul.s S" #R "30, S" #R "30, S721\n\t"                                                    \
    "vadd.s S" #R "30, S" #R "30, S721\n\t"                                                    \
    "vadd.s S" #R "30, S" #R "30, S733\n\t"                                                    \
    "sv.s S" #R "30, 24*" #K "(" dst ")\n\tsv.s S" #R "31, 4+24*" #K "(" dst ")\n\t"

/* Copies a vertex's colour and position after its sphere map coordinates. */
static inline void EnvCopy(EnvVert *d, SrcVert *s)
{
    d->color = s->color;
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

/* @draft 0x02c984 us f_02c984
   Remaining difference: retail interleaves the vector unit loads of the batched vertices and
   allocates the source and output pointers differently (343 of 360 words).
   WHAT IT DOES: Converts a reflective mesh's display list for reflection mapping. It copies
   the list's first three commands, sets a vertex type of float texture coordinates, 32 bit
   colour and float positions, then for each triangle strip of the source (base, vertex
   address and draw commands; a vertex type command there is reported as an error) writes the
   vertex address of a new vertex buffer and the strip's draw command, and fills the buffer:
   each vertex gets sphere map coordinates from the camera position and its normal (three, two
   or one vertex at a time on the vector unit), then its colour and position. Ends the new
   list with a return and hands back the ends of the vertex buffer and of the list. The
   vector unit registers are saved around it. */
extern "C" void f_02c984(EnvVert *out, unsigned int *dl, unsigned int *src, EnvVert **outEnd,
                         unsigned int **dlEnd)
{
    char save[192];
    unsigned int base;

    f_028b3c(save);
    __asm__ volatile(VFPU_BEGIN "lv.q C730, 0(%0)\n\tlv.q C720, 0(%1)" VFPU_END
                     : : "r"(&D_23ffb0), "r"(&D_1d1a80) : "memory");
    *dl++ = *src++;
    *dl++ = *src++;
    *dl++ = *src;
    src += 2;
    *dl++ = 0x1200019f;
    base = *src;
    do {
        unsigned int vaddr, prim;
        int n;
        SrcVert *v;

        if ((base & 0xff000000) == 0x12000000) {
            f_126f1c("Vetex Format Error!!");
            base = *src;
        }
        src++;
        vaddr = *src++;
        prim = *src;
        *dl++ = (((int)out >> 24) & 0xf) << 16 | 0x10000000;
        *dl++ = ((int)out & 0xffffff) | 0x01000000;
        n = prim & 0xff;
        *dl++ = n | 0x04040000;
        v = (SrcVert *)(((base & 0xffffff) << 8) | (vaddr & 0xffffff));
        src++;
        do {
            if (n >= 4) {
                __asm__ volatile(VFPU_BEGIN ENV_UV(0, 1, 0, "%0", "%1") ENV_UV(2, 3, 1, "%0", "%1")
                                 ENV_UV(4, 5, 2, "%0", "%1") VFPU_END
                                 : : "r"(v), "r"(out) : "memory");
                n -= 3;
                EnvCopy(out++, v++);
                EnvCopy(out++, v++);
                EnvCopy(out++, v++);
            } else if (n >= 3) {
                __asm__ volatile(VFPU_BEGIN ENV_UV(0, 1, 0, "%0", "%1") ENV_UV(2, 3, 1, "%0", "%1") VFPU_END
                                 : : "r"(v), "r"(out) : "memory");
                n -= 2;
                EnvCopy(out++, v++);
                EnvCopy(out++, v++);
            } else {
                __asm__ volatile(VFPU_BEGIN ENV_UV(0, 1, 0, "%0", "%1") VFPU_END
                                 : : "r"(v), "r"(out) : "memory");
                n -= 1;
                EnvCopy(out++, v++);
            }
        } while (n);
    } while (((base = *src) >> 24) != 0x0b);
    *dl++ = 0x0b000000;
    *outEnd = out;
    *dlEnd = dl;
    f_028b74(save);
}

/* A set of shadow polygons (another object file's class): loaded from course data, freed, and
   searched for the polygons under a point. */
extern "C" {
void f_0c6078(void *set, void *data);
void f_0c61b4(void *set);
int f_0c6580(void *set, void **found, int max, float x, float z);
}
struct PolySet {
    PolySet()
    {
        m0 = 0;
        m4 = 0;
        m8 = 0;
        m12 = 0;
        m16 = 0;
        m20 = 0;
    }
    ~PolySet() { f_0c61b4(this); }
    int m0, m4, m8, m12, m16, m20;
};
struct ShadowSet : PolySet {
    ~ShadowSet() { f_0c61b4(this); }
};

/* The light on the car: the two shadow polygon sets (the second holds the light intensity),
   then the colours worked out each frame. */
class MapLight {
public:
    MapLight() {}
    ShadowSet m0;
    ShadowSet m24;
    char m48;
    char m49;
    unsigned int m52[6];
    unsigned int m76;
    Vec4 m80;
    float m96;
    float m100;
    float m104;
    float m108;
    Vec4 m112;
    int m128;
};

/* @implements 0x02cec4 us f_02cec4
   WHAT IT DOES: Loads the course's two shadow polygon sets, when the course has them, and
   records which are present. */
extern "C" void f_02cec4(MapLight *l, void *light, void *shadow)
{
    if (*(int *)light) {
        f_0c6078(&l->m24, light);
        l->m49 = 1;
    } else {
        l->m49 = 0;
    }
    if (*(int *)shadow) {
        f_0c6078(&l->m0, shadow);
        l->m48 = 1;
    } else {
        l->m48 = 0;
    }
}

/* A shadow polygon: a triangle (or, with bit 0 of the flags, a parallelogram) on the ground
   given by a corner and two edges, its height, and a colour at each of its three corners. */
struct ShadowPoly {
    unsigned int flags;
    float x;
    float y;
    float z;
    float e1x, e1z;
    float e2x, e2z;
    unsigned char col[3][4];
};

/* Sets a colour to white and returns it. */
static inline Vec4 *White(Vec4 *c)
{
    c->w = 1.0f;
    c->z = 1.0f;
    c->y = 1.0f;
    c->x = 1.0f;
    return c;
}

/* @draft 0x02cf3c us f_02cf3c
   Remaining difference: one word, the green blend product (mul.s $f4,$f3,$f4 in retail,
   operands swapped here); no spelling of the three blends tried gives both.
   WHAT IT DOES: Works out the light at a point on the course. Of the light polygons under the
   point it takes the lowest one that contains it (points just outside an edge count while
   nothing has been found yet), blends the polygon's corner colours at the point, and returns
   that colour brightened towards white by one minus its alpha. Without light polygons, when
   none contains the point, or for a degenerate polygon (reported), the light is plain white. */
extern "C" Vec4 *f_02cf3c(MapLight *l, Vec4 *out, Vec4 *pos, int max)
{
    float b[3];
    ShadowPoly *found[32];
    float best;
    int hit, n, i;

    if (!l->m49)
        return White(out);
    best = 10000000.0f;
    n = f_0c6580(&l->m24, (void **)found, max, pos->x, pos->z);
    hit = -1;
    for (i = 0; i < n; i++) {
        ShadowPoly *t = found[i];
        float e1x = t->e1x * 0.001f;
        float e1z = t->e1z * 0.001f;
        float e2x = t->e2x * 0.001f;
        float e2z = t->e2z * 0.001f;
        float dx = (pos->x - t->x) * 0.001f;
        float dz = (pos->z - t->z) * 0.001f;
        float d11 = e1x * e1x + e1z * e1z;
        float d22 = e2x * e2x + e2z * e2z;
        float d12 = e1x * e2x + e1z * e2z;
        float d1 = e1x * dx + e1z * dz;
        float d2 = e2x * dx + e2z * dz;
        float det = d11 * d22 - d12 * d12;
        float u = d22 * d1 - d12 * d2;
        float v = d11 * d2 - d12 * d1;
        int clamped;

        if (det == 0) {
            f_126f1c("Error!! Shadow Polygon det = 0");
            return White(out);
        }
        clamped = 0;
        if (9999999.0f < best) {
            if (u < 0 && det * -0.01f < u) {
                u = 0;
                clamped = 1;
            }
            if (v < 0 && det * -0.01f < v) {
                v = 0;
                clamped = 1;
            }
        }
        if (0 <= u && 0 <= v &&
            (((t->flags & 1) && u <= det && v <= det) || u + v <= det) && t->y < best) {
            if (!clamped)
                best = t->y;
            hit = i;
            b[1] = u / det;
            if (b[1] < 0)
                b[1] = 0;
            b[2] = v / det;
            if (b[2] < 0)
                b[2] = 0;
            b[0] = 1.0f - b[1] - b[2];
        }
    }
    if (hit < 0)
        return White(out);
    {
        ShadowPoly *t = found[hit];
        float a;
        out->x = (b[0] * t->col[0][0] + b[1] * t->col[1][0] + b[2] * t->col[2][0]) * (1.0f / 255.0f);
        out->y = (b[0] * t->col[0][1] + b[1] * t->col[1][1] + b[2] * t->col[2][1]) * (1.0f / 255.0f);
        out->z = (b[0] * t->col[0][2] + b[1] * t->col[1][2] + b[2] * t->col[2][2]) * (1.0f / 255.0f);
        a = (b[0] * t->col[0][3] + b[1] * t->col[1][3] + b[2] * t->col[2][3]) * (1.0f / 255.0f);
        out->w = 1.0f;
        out->x = (1.0f - a) + a * out->x;
        out->y = (1.0f - a) + out->y * a;
        out->z = (1.0f - a) + a * out->z;
    }
    return out;
}

/* @implements 0x02d370 us f_02d370
   WHAT IT DOES: Packs a colour of three components (0 to 1) into GE colour bytes. */
extern "C" unsigned int f_02d370(Vec4 *c)
{
    return (int)(c->x * 255.0f) | (int)(c->y * 255.0f) << 8 | (int)(c->z * 255.0f) << 16;
}

/* @implements 0x02d3bc us f_02d3bc
   WHAT IT DOES: Packs a colour of four components (0 to 1) into GE colour bytes. */
extern "C" unsigned int f_02d3bc(Vec4 *c)
{
    return (int)(c->x * 255.0f) | (int)(c->y * 255.0f) << 8 | (int)(c->z * 255.0f) << 16 |
           (int)(c->w * 255.0f) << 24;
}

/* The map manager's lighting setup (src/race/MapManager.cpp: the motion system at +12512). */
struct LightSetup {
    char p0[32];
    Vec4 diffuse;
    Vec4 m48;
    Vec4 m64;
    Vec4 m80;
    Vec4 ambient;
    Vec4 m112;
    Vec4 specular;
    char p144[144];
    Vec4 shadow;
    float floor;
    char p308[28];
    Vec4 dir;
    char p352[8];
    float shadowLo, shadowHi;
    float specLo, specHi;
};
struct MapMgr {
    char p0[12248];
    int m12248;
    char p12252[260];
    LightSetup light;
};
extern MapMgr D_23c820;
extern char D_24517c[];
extern "C" float f_0da324(LightSetup *l, float dir, float n);

/* A smooth step from 0 at lo to 1 at hi. */
static inline float Smooth(float x, float lo, float hi)
{
    float t;
    if (x <= lo)
        return 0;
    if (hi <= x)
        return 1.0f;
    t = (x - lo) / (hi - lo);
    return t * -2.0f * t * t + t * 3.0f * t;
}

/* @draft 0x02d420 us f_02d420
   Remaining difference: register allocation and scheduling of the vector copies and the
   smooth steps throughout (control flow and calls match).
   WHAT IT DOES: Works out the light on a car at the given position for this frame. It looks
   up the light colour 3000 units below the position, takes its brightness along the light
   direction, and from that the specular and shadow strengths (smooth steps between the
   course's limits). The course's ambient colour is tinted by the light, the diffuse colour
   tinted towards it, the specular colour scaled by the specular strength and the shadow
   alpha by the shadow strength. A direction rate from the motion system then splits each of
   ambient, diffuse and specular into two packed colours (for the two directions blended), and
   records which of them dominates. The values are printed to the (compiled out) debug
   text. */
extern "C" void f_02d420(MapLight *l, Vec4 *pos, int max, float dir)
{
    MapMgr *mm = &D_23c820;
    LightSetup *ls = &mm->light;
    Vec4 p = *pos;
    Vec4 amb = mm->light.ambient;
    Vec4 dif = mm->light.diffuse;
    Vec4 spc = mm->light.specular;
    Vec4 shd = mm->light.shadow;
    Vec4 r, q, d, t0, t1, t2, t3, t4, t5;
    float k, lit, spec, shadow, rate, rest;

    q.x = p.x;
    q.y = p.y - 3000.0f;
    q.z = p.z;
    f_02cf3c(l, &r, &q, max);
    d = mm->light.dir;
    k = ls->floor;
    lit = r.x * d.x + r.y * d.y + r.z * d.z;
    amb.x = amb.x * r.x;
    amb.y = amb.y * r.y;
    amb.z = amb.z * r.z;
    dif.x = dif.x * (r.x * (1.0f - k) + k);
    dif.y = dif.y * (r.y * (1.0f - k) + k);
    dif.z = dif.z * (r.z * (1.0f - k) + k);
    spec = Smooth(lit, ls->specLo, ls->specHi);
    shadow = Smooth(lit, ls->shadowLo, ls->shadowHi);
    l->m80 = ls->m48;
    spc.x = spc.x * spec;
    spc.y = spc.y * spec;
    spc.z = spc.z * spec;
    shd.w = shd.w * shadow;
    l->m100 = 1.0f;
    l->m96 = 0;
    l->m104 = 0;
    l->m112 = ls->m64;
    l->m76 = f_02d3bc(&shd);
    rate = f_0da324(ls, dir, (float)mm->m12248);
    rest = 1.0f - rate;
    f_027e6c(&t0, &amb, rest);
    f_027e6c(&t1, &amb, rate);
    f_027e6c(&t2, &dif, rest);
    f_027e6c(&t3, &dif, rate);
    f_027e6c(&t4, &spc, rest);
    f_027e6c(&t5, &spc, rate);
    l->m52[0] = f_02d370(&t0) & 0xffffff;
    l->m52[2] = f_02d370(&t2) & 0xffffff;
    l->m52[4] = f_02d370(&t4) & 0xffffff;
    l->m52[1] = f_02d370(&t1) & 0xffffff;
    l->m52[3] = f_02d370(&t3) & 0xffffff;
    l->m52[5] = f_02d370(&t5) & 0xffffff;
    if (rate < 0.01f)
        l->m128 = 1;
    else if (0.99f < rate)
        l->m128 = 2;
    else
        l->m128 = 3;
    f_02db68(D_24517c, 1024, 32, 20, -1, "Intensity : %5.2f%5.2f%5.2f", r.x, r.y, r.z);
    f_02db68(D_24517c, 1024, 32, 21, -1, "Lit       : %5.2f", lit);
    f_02db68(D_24517c, 1024, 32, 22, -1, "Specular  : %5.2f", spec);
    f_02db68(D_24517c, 1024, 32, 23, -1, "Shadow    : %5.2f", shadow);
    f_02db68(D_24517c, 1024, 32, 24, -1, "DirRate   : %5.2f %d", rate, l->m128);
}

MapLight D_23ffc0;

/* @implements 0x02da28 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the course light at start up (empty shadow polygon sets) and frees
   its shadow polygons at exit. */
/* @implements 0x02db28 us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
/* @implements 0x02db48 us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */
