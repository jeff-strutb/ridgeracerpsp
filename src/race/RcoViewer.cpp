/* The RCO viewer (retail 0x0e5460 to 0x0e6854): the small scene viewer of the race code. It
   owns a camera (a position, a lens and an orientation), a scene object (2736 bytes) set up
   from an RTS file ("RCOViewerInit"), two sprite sources (the size of the picture they fit
   to) and two lights that are set up from the course's lighting. Drawing it takes the camera
   from the sprite positions, lights the scene from the course lighting and records the scene
   into the display list. */

#include <stdlib.h>

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[16];
} __attribute__((aligned(16)));

extern "C" {
void f_00d354(char *buf, int size, const char *fmt, ...);
float f_0cd3cc(float x);
void f_021e20(int psm, unsigned int fill);
void *f_0ccaec(float *p);
void f_028c70(void);
void f_028ca8(void);
void f_02842c(void);
void f_0284bc(float a);
void f_0284fc(float a);
void f_02853c(float a);
void f_02880c(float x, float y, float z);
void f_0287b0(void);
void f_028d94(Matrix *m);
void f_028e9c(const Matrix *m);
Vec4 *f_027f18(Vec4 *d, const Vec4 *a);
Vec4 *f_027f5c(Vec4 *d, const Vec4 *a);
int f_027f74(Vec4 *d, const Vec4 *a);
void f_0cc1f4(void *v, Matrix *m);
void f_118428(int light, int what, int n, const Vec4 *v);
void f_118560(int light, float a, float b, const Vec4 *v);
void f_1184fc(int light, float a, float b, float c);
void f_1185dc(int light, int what, int color);
extern char D_245178[];
}

/* The texture record a sprite source fits to: its width at +4. */
struct Tex {
    char p0[4];
    unsigned short width;
};

/* A sprite source (80 bytes): the texture it fits to and the position and angles it works
   out from it. */
struct Sprite {
    Tex *tex;
    int m4, m8, m12, m16, m20, m24;
    float m28;
    int m32;
    float m36;
    char p40[8];
    Vec4 pos;
    Vec4 rot;
};

/* A light (80 bytes): spot position, direction and colours. */
struct Light {
    float m0, m4, m8, m12, m16;
    float m20, m24, m28;
    float m32, m36, m40;
    int m44, m48, m52;
    int m56, m60, m64;
    int m68, m72, m76;
};

/* A work record the sprite lookup hands back (32 bytes). */
struct Rec {
    float x, y, z;
    char p12[12];
    short a, b, c;
    char p30[2];
};
extern "C" Rec f_0e0778(Sprite *s, int a, int b);

/* The scene's lens settings, as far as the viewer reads them. */
struct Lens {
    char p0[52];
    float m52;
    char p56[8];
    float m64;
};

/* The scene object the viewer owns (2736 bytes). */
struct Scene {
    Vec4 pos;
    Vec4 rot;
    char p32[192];
    float m224;
    char p228[12];
    float m240;
    char p244[12];
    float m256;
    char p260[12];
    float m272;
    char p276[12];
    Lens *m288;
    int m292;
    int m296;
    int m300;
    char p304[64];
    Matrix m368;
    char p432[1504];
    Vec4 light;
    char p1952[16];
    int m1968;
    char p1972[4];
    int m1976;
    char p1980[4];
    int m1984;
    char p1988[6];
    unsigned char m1994;
    char p1995[731];
    unsigned char m2726;
    char p2727[9];
};


/* The course data the viewer searches for the environment map texture: groups of items
   whose entries have a type word and a pointer to the texture address. */
struct Ent {
    int m0;
    int *type;
    int m8, m12;
    int *tex;
};
struct Itm {
    unsigned long n;
    Ent *e[1];
};
struct Grp {
    char p0[6];
    unsigned short n;
    Itm *i[1];
};
struct Slot {
    Grp *g;
    char p4[60];
};
struct Top {
    int m0;
    long n;
};
struct Slots {
    char hdr[16];
    Slot s[1];
};
struct Dir {
    Top *top;
    Slots *slots;
};

/* The course lighting the map manager holds (at +12512): the colours the viewer lights its
   scene with (each three floats), the light direction and the light class. */
struct LightSetup {
    char p0[16];
    float c1[3];
    char p28[4];
    float c0[3];
    char p44[4];
    float dir[3];
    char p60[20];
    float c2[3];
    char p92[4];
    float c3[3];
    char p108[4];
    float c4[3];
    char p124[4];
    float c5[3];
    char p140[4];
    float m144;
    float m148;
    char p152[80];
    int m232;
    float m236;
    float m240;
    char p244[136];
    int cls;
    float m384;
    char p388[104];
    int m492;
    float m496;
};

/* The map manager, as far as the viewer uses it. */
struct MapMgr {
    char p0[12144];
    Dir dir;
    char p12152[88];
    char areas[272];
    LightSetup light;
};
extern MapMgr D_23c820;
extern unsigned char D_1d5a88;

/* The viewer: a camera (position, lens, orientation), the scene, the two sprite sources and
   the two lights. */
struct RcoViewer {
    Vec4 pos;
    char p16[272];
    char m288[192];
    float fov;              /* 480 */
    float aspect;
    float far;
    float near;
    float scale;
    int m500;
    int m504;
    int m508;
    int m512;
    int m516;
    float m520;
    float m524;
    float m528;
    float m532;
    char p536[32];
    int m568;
    int m572;
    char p576[32];
    float rx, ry, rz;       /* 608 */
    char p620[36];
    int m656;
    char p660[4];
    int m664;
    char p668[20];
    float m688, m692, m696;
    char p700[4];
    float m704;
    char p708[44];
    Scene *scene;           /* 752 */
    char p756[12];
    Sprite a;               /* 768 */
    Sprite b;               /* 848 */
    float m928;
    float m932;
    char p936[8];
    Vec4 m944;
    int m960;
    Light l1;               /* 964 */
    Light l2;               /* 1044 */
};

/* Functions of this file that earlier ones call. */
extern "C" {
void f_0e6124(RcoViewer *unused, RcoViewer *v);
void f_0e6334(Sprite *p, int unused);
void f_0e6378(Sprite *s);
float f_0e6460(Sprite *s);
void f_0e617c(RcoViewer *v, RcoViewer *c, float size);
void f_0e66cc(Light *l, int idx, Matrix *m);
void f_0e6474(Light *l, int idx, int cls);
}

/* Sets up the lens and screen settings that go with the viewer's picture size: its own
   size scaled by the lens and the clip volume's depth range (the second pass overrides the
   near and far planes). */
static inline void SetScreen(RcoViewer *v, int w, int h, float half)
{
    v->m504 = v->m500 * w;
    v->m508 = h;
    v->m512 = 2048;
    v->m516 = 2048;
    v->m520 = w * half;
    v->m524 = h * half;
    v->m528 = 1400.0f;
    v->m532 = 1400.0f;
}

/* @draft 0x0e5460 us f_0e5460
   WHAT IT DOES: Sets the viewer up for the first mode: a lens of about 30 degrees (half of
   1.0472 radians) with its scale, an aspect of 1.7647, near and far planes (2000000 first,
   then 3000000), a 480 by 272 picture, the clear camera position and angles, and switches
   the screen to the 32 bit format.
   DRAFT: same size and calls; the four constants kept in float registers across the calls
   (0.0, 0.5, 1.0, 300.0) take other registers than in retail (retail f21 = 1.0, f22 = 0.0,
   f23 = 0.5; here f21 = 0.0, f22 = 0.5, f23 = 1.0), which changes 46 of 88 words. */
extern "C" void f_0e5460(RcoViewer *v)
{
    float half = 0.5f;
    float fov = 1.0471967f * half;
    float zero = 0.0f;
    v->m500 = 1;
    v->pos.x = zero;
    v->pos.y = zero;
    v->pos.z = zero;
    v->fov = fov;
    float t = f_0cd3cc(fov);
    float one = 1.0f;
    float far = 300.0f;
    float r = one / t;
    v->near = 2000000.0f;
    v->aspect = 1.7647059f;
    SetScreen(v, 480, 272, half);
    v->far = far;
    v->fov = fov;
    v->scale = r;
    t = f_0cd3cc(fov);
    r = one / t;
    v->far = far;
    v->near = 3000000.0f;
    v->fov = fov;
    v->scale = r;
    t = f_0cd3cc(fov);
    r = one / t;
    v->rz = zero;
    v->rx = zero;
    v->ry = zero;
    v->m656 = 0;
    v->scale = r;
    f_021e20(3, 0);
}

/* @draft 0x0e55c0 us f_0e55c0
   WHAT IT DOES: The same setup for the second mode (the same numbers).
   DRAFT: as f_0e5460 (float constants in other registers). */
extern "C" void f_0e55c0(RcoViewer *v)
{
    float half = 0.5f;
    float fov = 1.0471967f * half;
    float zero = 0.0f;
    v->m500 = 1;
    v->pos.x = zero;
    v->pos.y = zero;
    v->pos.z = zero;
    v->fov = fov;
    float t = f_0cd3cc(fov);
    float one = 1.0f;
    float far = 300.0f;
    float r = one / t;
    v->near = 2000000.0f;
    v->aspect = 1.7647059f;
    SetScreen(v, 480, 272, half);
    v->far = far;
    v->fov = fov;
    v->scale = r;
    t = f_0cd3cc(fov);
    r = one / t;
    v->far = far;
    v->near = 3000000.0f;
    v->fov = fov;
    v->scale = r;
    t = f_0cd3cc(fov);
    r = one / t;
    v->rz = zero;
    v->rx = zero;
    v->ry = zero;
    v->m656 = 0;
    v->scale = r;
    f_021e20(3, 0);
}

/* @implements 0x0e5720 us f_0e5720
   WHAT IT DOES: Switches the screen to pixel format 1 with a clear fill. */
extern "C" void f_0e5720(void)
{
    f_021e20(1, 0);
}

/* @implements 0x0e5740 us f_0e5740
   WHAT IT DOES: The same, for the viewer's second mode. */
extern "C" void f_0e5740(void)
{
    f_021e20(1, 0);
}

extern "C" {
void *f_022de4(int area, void *file, int id);
void f_01dbc4(Scene *s, void *a, int b, void *c, void *d);
void f_0201d4(void *p);
void f_028f80(MapMgr *mm, void *pack, int area);
void f_029040(MapMgr *mm, void *model, void *texMem, void *mapClip, void *event, void *envC,
              void *envD, void *motion, void *roadArea, void *danmen, void *runOffArea,
              void *runOffPoly, void *roadPoly, void *wallHit, void *lightPoint,
              void *shadePoly, int reverse);
void f_0e1fc8(void *areas, void *road, int roadSize, void *danmen);
void f_0e9e58(int a);
}

/* @draft 0x0e5760 us f_0e5760
   WHAT IT DOES: Initialises the viewer from an RTS file ("RCOViewerInit"): hands the course
   data (model, textures, clip, event, environment and motion data) to the map manager and
   sets up the course's collision areas, the camera at the origin, and creates the scene
   object and loads it from the file (a message and abort when it is not an RTS file). Sets
   up the two sprite sources, clears the viewer's own light and tracking state, searches the
   course data for the environment map texture address (the first entry of type 2 or 3),
   and sets both lights up from the course's light class.
   DRAFT: same size and the same calls and loops; the register of the scene pointer reloaded
   for its last-argument store (retail v1/v0, here s0/v0) and the search loop's registers and
   bottom (retail keeps the counter step and the break test after the type test, here the
   step and the bound compare are hoisted above it and every loop register is one higher)
   differ: 32 of 175 words. */
extern "C" void f_0e5760(RcoViewer *v, void *p2, void *p3, void *p4, void *p5, void *p6,
                         void *p7, void *p8, void *p9, void *p10, void *p11, void *p12,
                         void *p13, void *p14, int p15, void *p16, void *p17, void *p18)
{
    MapMgr *mm = &D_23c820;
    Scene *sc;
    int i, j;
    unsigned long k;

    f_0e1fc8(mm->areas, p13, p15, p14);
    f_028f80(mm, p6, 2);
    f_029040(mm, p5, p7, p8, p9, p10, p11, p12, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    f_0e6124(v, v);
    sc = (Scene *)operator new(2736);
    f_0201d4(sc);
    v->scene = sc;
    if (!f_022de4(2, p3, 0)) {
        f_00d354(D_245178, 1, "Error(RCOViewerInit) : This RTS File is not RTS file.\n");
        abort();
    }
    f_01dbc4(v->scene, p2, 2, p4, p18);
    sc = v->scene;
    sc->m296 = (int)p18;
    f_0e6334(&v->a, (int)p17);
    f_0e6334(&v->b, (int)p16);
    v->m932 = 0;
    v->m928 = 0;
    v->m944.z = 0;
    v->m944.y = 0;
    v->m944.x = 0;
    v->m960 = 0;
    Dir *d = &mm->dir;
    for (i = 0; i < d->top->n; i++) {
        Grp *g = d->slots->s[i].g;
        for (j = 0; j < g->n; j++) {
            Itm *it = g->i[j];
            for (k = 0; k < it->n; k++) {
                Ent *e = it->e[k];
                if (e->type) {
                    if (*e->type == 2)
                        goto set;
                    if (*e->type == 3) {
                    set:
                        v->m960 = *e->tex;
                    }
                }
                if (v->m960)
                    break;
            }
        }
    }
    f_00d354(D_245178, 1024, "CarGet StaticEnvMap TexAddr : %p\n", v->m960);
    f_0e9e58(3);
    MapMgr *m2 = &D_23c820;
    LightSetup *ls = &m2->light;
    D_1d5a88 = 1;
    f_0e6474(&v->l1, 0, ls->cls);
    f_0e6474(&v->l2, 1, ls->cls);
}

/* A scene or map destructor pair the viewer calls on shutdown. */
extern "C" {
void f_0292fc(void *mm);
void f_01dee4(Scene *s);
void f_0ea894(void);
}

/* @implements 0x0e5a1c us f_0e5a1c
   WHAT IT DOES: Shuts the viewer down: releases the map manager's course, destroys and
   frees the scene object and runs the fade shutdown. */
extern "C" void f_0e5a1c(RcoViewer *v)
{
    f_0292fc(&D_23c820);
    f_01dee4(v->scene);
    ::operator delete(v->scene);
    f_0ea894();
}

struct MainLoopJobView {
    char p0[14];
    unsigned char m14;
};
extern MainLoopJobView *D_1d88a0;

extern "C" {
Vec4 *f_027e0c(Vec4 *d, const Vec4 *a, const Vec4 *b);
float f_027ef8(const Vec4 *a);
void f_01e5d0(Scene *s, void *world);
void f_021720(void);
void f_021750(void);
void f_0cc3e4(RcoViewer *v);
void f_118380(float a);
void f_1184d8(int a);
void f_116898(int a);
void f_1166d4(int a);
void f_118b64(int a, float b, float c);
void f_0293e4(MapMgr *mm, int a, RcoViewer *v);
unsigned int *f_029524(MapMgr *mm, int a, RcoViewer *v, unsigned int *p);
void f_11817c(unsigned int c);
unsigned int *f_0216d8(void);
void f_0216e8(unsigned int *p);
unsigned int *f_025068(unsigned int *p);
unsigned int *f_025190(unsigned int *p);
void f_01ee78(Scene *s);
}

static inline void Copy3(float *d, const float *s)
{
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
}

/* A colour from three floats in 0..1 as packed bytes (red lowest). */
static inline int Pack(const float *c)
{
    return (int)(c[0] * 255.0f) | (int)(c[1] * 255.0f) << 8 | (int)(c[2] * 255.0f) << 16;
}

/* @draft 0x0e5a60 us f_0e5a60
   WHAT IT DOES: Draws the viewer for one frame (nothing when the main loop job is busy).
   Aims the camera at the first sprite source, fits the second one with the given size
   setting and puts its position and angles, the course's light direction and the course's
   three colours (packed as bytes) on the scene. Works out how far the second source moved
   since last frame and, when the course's light distance setting is below the given size,
   turns the viewer's two angles back by that distance over the lens's two scales. Sets
   the scene's angle fields, draws it through the model code (the scene's byte flags set,
   the environment texture address passed on when found), then sets the graphics engine's
   three lights up from the course lighting and the viewer's two lights, records the course
   map's display list and the scene's two passes (the second one through the stencil end
   commands) and closes the list.
   DRAFT: 1724 bytes against 1732, 390 of 433 words differ (the score counts a one word
   shift as a mismatch from there on). All 48 calls are in retail's order with the same
   arguments; the difference is instruction scheduling and registers: the colour packing and
   the copies onto the scene (the first 120 instructions after the second call) load and
   store in another order with other float registers, and the closing commands compute the
   list end as a second pointer (retail: addiu v1,v0,16; move a0,v1) rather than adding to the
   returned pointer. */
extern "C" void f_0e5a60(RcoViewer *v, float t)
{
    MapMgr *mm;
    Sprite *b;
    Scene *sc;
    float k1, k2, d;
    Vec4 tmp;

    if (D_1d88a0->m14)
        return;
    mm = &D_23c820;
    f_0e617c(v, v, t);
    b = &v->b;
    b->m36 = t;
    f_0e6378(b);
    LightSetup *ls = &mm->light;
    float *dir = ls->dir;
    sc = v->scene;
    Vec4 *bp = &v->b.pos;
    float *lp = &sc->light.x;
    float x = dir[0], y = dir[1], z = dir[2];
    lp[2] = z;
    lp[1] = y;
    lp[0] = x;
    sc->m1968 = Pack(ls->c0);
    sc->m1976 = Pack(ls->c3);
    sc->m1984 = Pack(ls->c5);
    sc->pos = *bp;
    sc->rot = v->b.rot;
    k1 = sc->m288->m64 * 6.28318f;
    k2 = sc->m288->m52 * 6.28318f;
    f_027e0c(&tmp, bp, &v->m944);
    d = f_027ef8(&tmp);
    v->m944 = *bp;
    if (ls->m384 < t) {
        v->m932 = v->m932 - d / k1 * 3.14159f * 2.0f;
        v->m928 = v->m928 - d / k2 * 3.14159f * 2.0f;
    }
    sc = v->scene;
    sc->m224 = v->m928;
    sc->m240 = v->m928;
    sc->m256 = v->m932;
    sc->m272 = v->m932;
    f_01e5d0(sc, v->m288);
    v->scene->m2726 = 0;
    v->scene->m1994 = 1;
    if (v->m960)
        v->scene->m300 = v->m960;
    f_021720();
    f_0cc3e4(v);
    f_118380(ls->m144);
    f_1184d8(1);
    float *c4 = ls->c4;
    float *c1 = ls->c1;
    float *c2 = ls->c2;
    f_1185dc(0, 1, 0);
    f_1185dc(0, 2, 0);
    f_1185dc(0, 4, Pack(c4));
    f_118428(0, 0, 6, (Vec4 *)dir);
    f_1185dc(1, 1, Pack(c1));
    f_1185dc(1, 2, Pack(c2));
    f_1185dc(1, 4, 0);
    f_118428(1, 0, 2, (Vec4 *)dir);
    f_1185dc(2, 1, Pack(c1));
    f_1185dc(2, 2, Pack(c2));
    f_1185dc(2, 4, Pack(c4));
    f_118428(2, 0, 6, (Vec4 *)dir);
    f_116898(11);
    f_116898(12);
    f_116898(13);
    f_116898(14);
    f_0e66cc(&v->l1, 3, 0);
    f_118b64(ls->m232, ls->m236, ls->m240);
    f_021750();
    mm->light.m492++;
    mm->light.m496 += 1.0f;
    f_0293e4(mm, 0, v);
    unsigned int *dl = f_0216d8();
    dl = f_029524(mm, 0, v, dl);
    f_0216e8(dl);
    f_021720();
    f_11817c(0xff000000);
    f_118380(ls->m148);
    f_0e66cc(&v->l1, 2, &v->scene->m368);
    f_0e66cc(&v->l2, 3, &v->scene->m368);
    f_1166d4(11);
    f_1166d4(10);
    f_116898(12);
    f_1166d4(13);
    f_1166d4(14);
    f_021750();
    unsigned int *r = f_025068(f_0216d8());
    v->scene->m292 = (int)r;
    f_01ee78(v->scene);
    unsigned int *p = f_025190((unsigned int *)v->scene->m292);
    p[0] = 0xe2001d0c;
    p[1] = 0xe300f3e2;
    p[2] = 0xe4000c1d;
    p[3] = 0xe500e2f3;
    f_0216e8(p + 4);
}

/* @implements 0x0e6124 us f_0e6124
   WHAT IT DOES: Puts a viewer at the origin with no turn: its position (the fourth word is
   whatever was in the temporary), the two flags and the three angles all cleared. */
extern "C" void f_0e6124(RcoViewer *unused, RcoViewer *v)
{
    float z = 0.0f;
    Vec4 p;
    p.x = z;
    p.y = z;
    p.z = z;
    v->pos = p;
    v->m568 = 0;
    v->rx = z;
    v->ry = z;
    v->rz = z;
    v->m572 = 0;
    v->m704 = z;
    v->m664 = 0;
}

extern float D_23fa84;

/* @draft 0x0e617c us f_0e617c
   WHAT IT DOES: Points a viewer's camera at its first sprite source: fits the source (with
   the given size setting), takes the lens from the course's angle (in degrees, halved, with
   its scale), puts the camera at the source's position and turns it to the source's angles,
   then builds the camera matrix from the position and the three angles and hands it to the
   camera.
   DRAFT: same size and calls; the position and angle copies load and store their three
   floats in a different order and take other float registers (17 of 85 words). */
extern "C" void f_0e617c(RcoViewer *v, RcoViewer *c, float size)
{
    Matrix m;
    float a, b, d;
    Sprite *s = &v->a;

    s->m36 = size;
    f_0e6378(s);
    c->fov = D_23fa84 / 180.0f * 3.14159f * 0.5f;
    c->scale = 1.0f / f_0cd3cc(c->fov);
    Vec4 *p = &s->pos;
    Vec4 *r = &s->rot;
    c->pos.x = p->x;
    c->pos.y = p->y;
    c->pos.z = p->z;
    c->rx = r->x;
    c->ry = r->y;
    c->rz = r->z;
    c->m688 = p->x;
    c->m692 = p->y;
    c->m696 = p->z;
    f_028c70();
    f_02842c();
    a = c->rz;
    f_0ccaec(&a);
    f_02853c(a);
    b = c->ry;
    f_0ccaec(&b);
    f_0284fc(b);
    d = c->rx;
    f_0ccaec(&d);
    f_0284bc(d);
    f_02880c(c->pos.x, c->pos.y, c->pos.z);
    f_0287b0();
    f_028d94(&m);
    f_028ca8();
    f_0cc1f4(c, &m);
}

/* @implements 0x0e62d0 us f_0e62d0
   WHAT IT DOES: Returns the width of the wider of the viewer's two sprite sources. */
extern "C" float f_0e62d0(RcoViewer *v)
{
    Sprite *a = &v->a;
    Sprite *b = &v->b;
    float x = f_0e6460(a);
    float y = f_0e6460(b);
    Sprite *w = a;
    if (!(y < x))
        w = b;
    return f_0e6460(w);
}

/* @implements 0x0e6334 us f_0e6334
   WHAT IT DOES: Clears a sprite source (its texture and settings) and runs its base setup. */
extern "C" void f_0daf30(Sprite *p);
extern "C" void f_0e6334(Sprite *p, int unused)
{
    p->m36 = 0;
    p->tex = 0;
    p->m4 = 0;
    p->m8 = 0;
    p->m12 = 0;
    p->m16 = 0;
    p->m20 = 0;
    p->m24 = 0;
    p->m28 = 0;
    p->m32 = 0;
    f_0daf30(p);
}

/* @implements 0x0e6378 us f_0e6378
   WHAT IT DOES: Fits a sprite source: limits its size setting to the texture's width less
   one, then looks up the position and angles of its two ends and keeps them (the angles in
   radians, from 16 bit turns). */
extern "C" void f_0e6378(Sprite *s)
{
    float w = (float)(s->tex->width - 1);
    float t = s->m36;
    s->m28 = t;
    if (w <= t)
        s->m28 = w;
    Rec r0 = f_0e0778(s, 0, 0);
    Rec r1 = f_0e0778(s, 0, 1);
    s->pos.x = r0.x;
    s->pos.y = r0.y;
    s->pos.z = r0.z;
    s->rot.x = (float)r1.a * 6.2831855f * 1.52587890625e-05f;
    s->rot.y = (float)r1.b * 6.2831855f * 1.52587890625e-05f;
    s->rot.z = (float)r1.c * 6.2831855f * 1.52587890625e-05f;
}

/* @implements 0x0e6460 us f_0e6460
   WHAT IT DOES: Returns the width of a sprite source's texture as a float. */
extern "C" float f_0e6460(Sprite *s)
{
    return (float)s->tex->width;
}

/* @draft 0x0e6474 us f_0e6474
   WHAT IT DOES: Sets up one of the viewer's two lights from the course's light class (1 or
   2): prints which class it is, then fills the light's spot position, direction, spot angles
   and colours with the preset for that class and for light number idx (0 or 1).
   DRAFT: same size and control flow (the four presets share their store tails as in retail);
   about 36 of 150 words differ: the constants take other registers and the stores of each
   preset come out in a different order. */
extern "C" void f_0e6474(Light *l, int idx, int cls)
{
    if (cls == 1) {
        f_00d354(D_245178, 1024, "==== CarGet Spot Light Class 1 ====\n");
        if (idx == 0) {
            l->m0 = 10.0f;
            l->m4 = 0;
            l->m8 = 1.0f;
            l->m12 = 0;
            l->m16 = 0;
            l->m20 = -0.6f;
            l->m24 = 6.0f;
            l->m28 = -11.0f;
            l->m32 = 0;
            l->m36 = 1.0f;
            l->m40 = 0;
            l->m44 = 166;
            l->m48 = 156;
            l->m52 = 150;
            l->m56 = 60;
            l->m60 = 50;
            l->m64 = 60;
            l->m68 = 128;
            l->m72 = 128;
            l->m76 = 128;
        } else {
            l->m0 = 7.0f;
            l->m4 = 0;
            l->m8 = 1.0f;
            l->m12 = 0;
            l->m16 = 0;
            l->m20 = -0.6f;
            l->m24 = 6.0f;
            l->m28 = -15.1f;
            l->m32 = 0;
            l->m36 = 1.0f;
            l->m40 = 0;
            l->m44 = 166;
            l->m48 = 156;
            l->m52 = 150;
            l->m56 = 40;
            l->m60 = 40;
            l->m64 = 40;
            l->m68 = 128;
            l->m72 = 128;
            l->m76 = 128;
        }
    } else {
        f_00d354(D_245178, 1024, "==== CarGet Spot Light Class 2 ====\n");
        if (idx == 0) {
            l->m0 = 6.0f;
            l->m4 = 0;
            l->m8 = 1.0f;
            l->m12 = 0;
            l->m16 = 0;
            l->m20 = -0.0f;
            l->m24 = 6.0f;
            l->m28 = -9.0f;
            l->m32 = 0;
            l->m36 = 1.0f;
            l->m40 = 0;
            l->m44 = 166;
            l->m48 = 156;
            l->m52 = 150;
            l->m56 = 60;
            l->m60 = 50;
            l->m64 = 60;
            l->m68 = 128;
            l->m72 = 128;
            l->m76 = 128;
        } else {
            l->m0 = 1.0f;
            l->m4 = 0;
            l->m8 = 1.0f;
            l->m12 = 0;
            l->m16 = 0;
            l->m20 = -0.6f;
            l->m24 = 6.0f;
            l->m28 = -19.1f;
            l->m32 = 0;
            l->m36 = 1.0f;
            l->m40 = 0;
            l->m44 = 166;
            l->m48 = 156;
            l->m52 = 150;
            l->m56 = 60;
            l->m60 = 60;
            l->m64 = 60;
            l->m68 = 128;
            l->m72 = 128;
            l->m76 = 128;
        }
    }
}

/* @implements 0x0e66cc us f_0e66cc
   WHAT IT DOES: Sets light number idx up on the graphics engine from a light record: its
   position (scaled by 1000 and, when a matrix is given, transformed by it), its spot angles,
   its direction (normalised, and turned by the matrix) and its three colours. */
extern "C" void f_0e66cc(Light *l, int idx, Matrix *m)
{
    Vec4 d;
    Vec4 e;

    d.x = l->m20 * 1000.0f;
    d.y = l->m24 * 1000.0f;
    d.z = l->m28 * 1000.0f;
    d.w = 0;
    e.x = l->m32;
    e.y = l->m36;
    e.z = l->m40;
    e.w = 0;
    f_027f18(&e, &e);
    if (m) {
        f_028c70();
        f_028e9c(m);
        f_027f74(&d, &d);
        f_027f5c(&e, &e);
        f_028ca8();
    }
    f_118428(idx, 2, 6, &d);
    f_118560(idx, l->m0, l->m4, &e);
    f_1184fc(idx, l->m8, l->m12, l->m16);
    f_1185dc(idx, 1, l->m56 | l->m60 << 8 | l->m64 << 16);
    f_1185dc(idx, 2, l->m44 | l->m48 << 8 | l->m52 << 16);
    f_1185dc(idx, 4, l->m68 | l->m72 << 8 | l->m76 << 16);
}
