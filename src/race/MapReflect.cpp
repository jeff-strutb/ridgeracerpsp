/* The reflective course part object file (retail 0x02bbc0 to 0x02c93c). The map manager draws
   course part 2 (the reflective surfaces) through here: a soft edged ring display list drawn
   into a 64 x 64 reflection texture, the course part's drawing with its texture changes and
   reflection mapped meshes, and the global reflection settings object with its defaults. */

#include <math.h>

extern "C" {
void *f_021b38(unsigned int size);
void f_028c70(void);
void f_028ca8(void);
unsigned int *f_0249a0(void *tex, unsigned int *p);
unsigned int *f_02dde8(unsigned int *p);
void f_02b854(int reflect, void *buf, unsigned int *p, void *mesh, void **bufp, unsigned int **pp);
}

/* The game database's tables: records found by index or by name. */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
};
extern CTable D_2407a8;
extern "C" char *f_036984(CTable *t, const char *key, int i, int *index, int count);

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};

/* The reflection settings. */
class MapReflect {
public:
    MapReflect();
    Rec m0;
    int m8;
    int m12;
    int m16;
    int m20;
    float m24;
    float m28;
    float m32;
    float m36;
    int m40;
    float m44;
    int m48;
    int m52;
    int m56;
    int m60;
    float m64;
    float m68;
    float m72;
    float m76;
    float m80;
    int m84;
    float m88;
    int m92;
    float m96;
    float m100;
    int m104;
    float m108;
    float m112;
    int m116;
    int m120;
    int m124;
    int m128;
    int m132;
    int m136;
    int m140;
    int m144;
    int m148;
    int m152;
    int m156;
    int m160;
    int m164;
};
extern MapReflect D_23fefc;
extern int D_23ff70;

/* One vertex of the ring: colour, then a 16 bit screen position. */
struct RingVert {
    unsigned char r, g, b, a;
    short x, y, z;
    short pad;
};

/* The ring's display list: its render state and draw command, then the vertices of a
   triangle strip of 33 inner and outer pairs. */
struct RingList {
    unsigned int cmd[13];
    RingVert v[66];
};
extern RingList D_23fbb0;

/* @draft 0x02bbc0 us f_02bbc0
   Remaining difference: scheduling only; retail stores cmd[0] after the radius and centre
   constant loads and loads 33 and 32 before 1/32 and the pi constant (47 words).
   WHAT IT DOES: Builds the ring display list once per course: render state (blending on,
   depth test off, through mode 16 bit positions with 32 bit colour), then a triangle strip
   ring round the centre of a 64 x 64 texture, from radius 33 at the settings' alpha out to the
   settings' inner radius at half alpha. */
void f_02bbc0(void)
{
    RingList *l = &D_23fbb0;
    int a = (int)l->v;
    int i;

    l->cmd[0] = 0x21000001;
    l->cmd[1] = 0xe0000000;
    l->cmd[2] = 0xdf00006a;
    l->cmd[3] = 0x23000000;
    l->cmd[4] = 0x1d000000;
    l->cmd[5] = 0x22000000;
    l->cmd[6] = 0x17000000;
    l->cmd[7] = 0x1e000000;
    l->cmd[8] = 0x1280011c;
    l->cmd[9] = ((a >> 24) & 0xf) << 16 | 0x10000000;
    l->cmd[10] = (a & 0xffffff) | 0x01000000;
    l->cmd[11] = 0x04040042;
    l->cmd[12] = 0x0b000000;
    for (i = 0; i < 33; i++) {
        float r0 = 33.0f;
        float r1 = D_23fefc.m88;
        float t = (float)i / 32.0f * 2.0f * 3.24159f;
        RingVert *v = &l->v[i * 2];
        v[0].x = (int)(cosf(t) * r0 + 32.0f);
        v[0].y = (int)(sinf(t) * r0 + 32.0f);
        v[0].z = 0;
        v[0].r = 255;
        v[0].g = 255;
        v[0].b = 255;
        v[0].a = D_23fefc.m84;
        v[1].x = (int)(cosf(t) * r1 + 32.0f);
        v[1].y = (int)(sinf(t) * r1 + 32.0f);
        v[1].z = 0;
        v[1].r = 255;
        v[1].g = 255;
        v[1].b = 255;
        v[1].a = 0x80;
    }
}

/* The model data of the loaded course: groups of objects, 64 bytes each. */
struct ObjList {
    unsigned int count;
    struct Mesh *mesh[1];
};
struct ObjGroup {
    int m0;
    unsigned int flags;
    int m8;
    int m12;
    char *objs;
    int m20[11];
};
struct ModelData {
    int m0;
    ObjGroup *group;
};
extern ModelData D_23f790;

/* The course colour: green and blue (the red comes from the map manager). */
struct CourseColor {
    int m0;
    float g;
    float b;
};
extern CourseColor D_23f9a0;

/* The map manager (src/race/MapManager.cpp): the course red and its frame counter. */
extern char D_23c820[];

/* A scrolling texture: kind 1 scrolls by (u, v) every (uFrames, vFrames) frames. */
struct Scroll {
    int kind;
    float u;
    float v;
    float uFrames;
    float vFrames;
};

/* One textured piece of a mesh: its texture and the offset of its vertex data. */
struct Piece {
    void *tex;
    int m4;
    int m8;
    unsigned short data;
};

/* A mesh: its display list, its scroll setting and its pieces. */
struct Mesh {
    unsigned int list;
    Scroll *scroll;
    int m8;
    unsigned int count;
    Piece *piece[1];
};

/* The two texture matrices (4 x 3) the reflection uses. */
extern float D_1d1a1c[12];
extern float D_1d1a4c[12];

struct Vec4 {
    float x, y, z, w;
};

/* Reads a float's bits. */
static inline int FloatBits(float f)
{
    union {
        float f;
        int i;
    } u;
    u.f = f;
    return u.i;
}

/* Writes a GE base and call pair for the display list at address a. */
#define GE_CALL(p, a)                                              \
    do {                                                           \
        int a_ = (a);                                              \
        *(p)++ = ((a_ >> 24) & 0xf) << 16 | 0x10000000;            \
        *(p)++ = (a_ & 0xffffff) | 0x0a000000;                     \
    } while (0)

/* A matrix word as a GE float (the top 24 bits of the float) in a command. */
#define MTX_WORD(m, k) (((*(unsigned int *)&(m)[k] >> 8) & 0xffffff) | 0x3b000000)

/* Uploads a texture matrix. */
static inline unsigned int *TexMatrix(unsigned int *p, unsigned int sel, float *m)
{
    p[0] = 0xe7000000 | sel;
    p[1] = 0x1f000000;
    p[2] = 0x23000000 | !sel;
    p[3] = 0x3a000000;
    p[4] = MTX_WORD(m, 0);
    p[5] = MTX_WORD(m, 1);
    p[6] = MTX_WORD(m, 2);
    p[7] = MTX_WORD(m, 3);
    p[8] = MTX_WORD(m, 4);
    p[9] = MTX_WORD(m, 5);
    p[10] = MTX_WORD(m, 6);
    p[11] = MTX_WORD(m, 7);
    p[12] = MTX_WORD(m, 8);
    p[13] = MTX_WORD(m, 9);
    p[14] = MTX_WORD(m, 10);
    p[15] = MTX_WORD(m, 11);
    return p + 16;
}

/* @draft 0x02bdcc us f_02bdcc
   Remaining difference: the two texture matrix uploads are cross-jumped into one tail here
   (retail keeps both, 292 bytes more), plus register allocation in the mesh loop.
   WHAT IT DOES: Draws the reflective course part into the display list and returns the new
   end of the list. It moves the reflection texture matrix with the camera, sets the texture
   function and dither, then walks the part's command list: 0x8004 picks an object group,
   0x8000 and 0x8002 upload one of the two texture matrices (the first turns reflection
   mapping on for the meshes that follow), 0x8005 and 0x8006 skip a value, 0x8007 ends it, and
   any other number draws that object of the current group. Each mesh calls its display list,
   sets its (possibly scrolling) texture offset and the course colour, then each piece
   selects its texture when it changes and has its vertices drawn by f_02b854. Finally the
   ring list is called when enabled and the render state restored. */
extern "C" unsigned int *f_02bdcc(char *part, Vec4 *view, unsigned int *p)
{
    void *buf = f_021b38(0x30000);
    float *tm;
    Vec4 pos;
    unsigned short *c;
    int lastTex, group, reflect, step;
    unsigned int code;

    f_028c70();
    pos = *view;
    tm = (float *)((int)D_1d1a1c | 0x40000000);
    tm[10] = 0;
    tm[9] = pos.x * D_23fefc.m80;
    tm[11] = pos.z * D_23fefc.m80;
    *p++ = 0xc9010100;
    *p++ = 0x18000000;
    *p++ = 0x19000000;
    *p++ = 0x1a000000;
    *p++ = 0x1b000000;
    c = (unsigned short *)(part + 20);
    lastTex = -1;
    group = -1;
    reflect = 0;
    if (D_23fefc.m60 == 3) {
        *p++ = 0x20000000;
        *p++ = 0xe90000ff;
    }
    p = f_02dde8(p);
    *p++ = 0x20000001;
    while ((code = *c) != 0x8007) {
        step = 1;
        if (code == 0x8005) {
            step = 2;
        } else if (code == 0x8004) {
            step = 2;
            group = c[1];
        } else if (code == 0x8006) {
            step = 2;
        } else if ((short)code < 0) {
            code &= 0x7fff;
            if (code == 0) {
                p = TexMatrix(p, 1, D_1d1a1c);
                reflect = 1;
            } else if (code == 2) {
                p = TexMatrix(p, 0, D_1d1a4c);
                reflect = 0;
            }
        } else {
            ObjGroup *g = &D_23f790.group[group];
            ObjList *ol = *(ObjList **)(g->objs + code * 4 + 8);
            unsigned int i, j;
            for (i = 0; i < ol->count; i++) {
                Mesh *m = ol->mesh[i];
                Scroll *s = m->scroll;
                GE_CALL(p, m->list);
                if (s == 0) {
                    *p++ = 0x4a000000;
                    *p++ = 0x4b000000;
                } else if (s->kind == 1) {
                    int frame = *(int *)(D_23c820 + 13004);
                    float u = s->u * (float)(frame / (int)s->uFrames);
                    float v = s->v * (float)(frame / (int)s->vFrames);
                    u -= floorf(u);
                    v -= floorf(v);
                    if (u < 0)
                        u += 1.0f;
                    if (v < 0)
                        v += 1.0f;
                    *p++ = (FloatBits(u) >> 8) | 0x4a000000;
                    *p++ = (FloatBits(v) >> 8) | 0x4b000000;
                }
                if (g->flags & 1) {
                    int r = (int)(*(float *)(D_23c820 + 12672) * 255.0f);
                    int gr = (int)(D_23f9a0.g * 255.0f);
                    int b = (int)(D_23f9a0.b * 255.0f);
                    *p++ = (r | gr << 8 | b << 16) | 0x5c000000;
                } else {
                    *p++ = 0x5cffffff;
                }
                for (j = 0; j < m->count; j++) {
                    Piece *pc = m->piece[j];
                    if (pc->tex == 0) {
                        *p++ = 0x1e000000;
                    } else if ((int)pc->tex != lastTex) {
                        p = f_0249a0(pc->tex, p);
                        *p++ = 0x1e000001;
                        lastTex = (int)pc->tex;
                    }
                    f_02b854(reflect, buf, p, (char *)pc + pc->data * 16 + 96, &buf, &p);
                }
            }
        }
        c += step;
    }
    if (D_23fefc.m92)
        GE_CALL(p, (int)&D_23fbb0);
    p[0] = 0xc9000100;
    p[1] = 0x9b000001;
    p[3] = 0xe9000000;
    p[2] = 0x20000001;
    p += 4;
    f_028ca8();
    return p;
}

/* @draft 0x02c650 us _ZN10MapReflectC2Ev
   Remaining difference: store order from +0x94: retail stores m8, m104 and m140 to m164 after
   the D_23ff70 store and m100 last (27 words); the first 37 words match in field order.
   WHAT IT DOES: Sets the reflection settings to their defaults (the base object constructor;
   the same body as the complete object constructor that follows). */
MapReflect::MapReflect()
{
    m8 = 0;
    m12 = 180;
    m16 = 38;
    m20 = 10;
    m24 = -6.0f;
    m28 = 0.9f;
    m32 = 2000.0f;
    m36 = 45.0f;
    m40 = 0;
    m44 = 0.9f;
    m48 = 300;
    m52 = 64;
    m56 = 64;
    m60 = 0;
    m64 = 100.0f;
    m68 = 1.0f;
    m72 = 4000.0f;
    m76 = 0.9f;
    m80 = 1.0f;
    m84 = 255;
    m88 = 28.0f;
    m92 = 1;
    m96 = 1000.0f;
    m100 = 1.0f;
    m104 = 0;
    m108 = 1.0f;
    m112 = -1.0f;
    D_23ff70 = 0;
    m124 = 0;
    m128 = 0;
    m136 = 10;
    m140 = 0;
    m144 = 11;
    m148 = 0;
    m152 = 10;
    m156 = 0;
    m160 = 11;
    m164 = 0;
}

/* @draft 0x02c760 us _ZN10MapReflectC1Ev
   WHAT IT DOES: The complete object constructor: the same defaults as above. */

/* @implements 0x02c870 us f_02c870
   WHAT IT DOES: Points the reflection settings at the Mountain_N record of the course table
   (the reflected scenery). */
extern "C" void f_02c870(void)
{
    MapReflect *m = &D_23fefc;
    Rec r;
    const char *n = "Mountain_N";
    if (n)
        r.rec = f_036984(&D_2407a8, n, 0, D_2407a8.index, D_2407a8.count);
    else
        r.rec = 0;
    m->m0 = r;
}

MapReflect D_23fefc;

/* @implements 0x02c8d8 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global reflection settings at start up. */
/* @implements 0x02c91c us _GLOBAL__I
   WHAT IT DOES: Runs the above at start up. */
