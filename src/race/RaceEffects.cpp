/* The race effects object file (retail 0x031b98 to 0x032070). One global object gathers the
   race's visual effect systems: the exhaust and spark particles (0x032070 on), the skid marks
   (+44), the leaves and smoke blown about the course (+72) and the sunshine flares (+92). This
   file starts, resets, steps, draws and stops them together, loads their textures from the
   race pack, and holds the global object with its startup entry and inline constructor. */

extern "C" {
unsigned int *f_0216d8(void);
void f_0216e8(unsigned int *p);
unsigned int *f_02df08(unsigned int *p);
unsigned int *f_02dba8(unsigned int *p);
void *f_005c34(char *seq, const char *name);
void *f_022de4(int area, void *file, int id);
void f_0cdbc4(void *m, void *out);
unsigned int *f_0cc584(void *view, unsigned int *p);
}

extern char D_1dd6b0[];

struct Vec4 {
    float x, y, z, w;
};

/* The exhaust and spark particles (their own object file, 0x032070 on). */
template <class T> struct Ring {
    Ring() : size(0), head(0), tail(0), buf(0) {}
    int size;
    int head;
    int tail;
    T *buf;
};

struct Particle;

struct Buckets {
    Buckets() : list(0) {}
    int count;
    Particle **list;
};

class CParticles {
public:
    int step;
    Ring<Particle> fire;
    Ring<Particle> smoke;
    Buckets depth;
};

extern "C" {
int f_032070(CParticles *p, int n);
void *f_032138(CParticles *p, int type, const Vec4 *pos, const Vec4 *vel);
void f_03228c(CParticles *p);
unsigned int *f_032298(CParticles *p, void *view, unsigned int *list);
void f_0328b0(CParticles *p);
}

/* The skid marks (0x032e14 on). */
struct CSkid {
    CSkid() : m0(0), m4(0), m8(0), m12(0) {}
    int m0;
    int m4;
    int m8;
    int m12;
    int m16[3];
};
extern "C" {
void f_032e14(CSkid *s, void *view, int alpha);
void f_032f9c(CSkid *s);
void f_033028(CSkid *s);
unsigned int *f_033034(CSkid *s, void *view, unsigned int *p);
}

/* The blown leaves and smoke (0x035ef0 on). */
struct CLeaves {
    CLeaves() : m0(0), m4(0), m8(0), m12(0) {}
    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
};
extern "C" {
void f_035ef0(CLeaves *l, int n);
void f_035fcc(CLeaves *l);
void f_035ff8(CLeaves *l);
unsigned int *f_0362a8(CLeaves *l, unsigned int *p);
void f_036600(CLeaves *l, const Vec4 *pos, int a, int b, float y);
}

/* One sunshine flare slot. */
struct Flare {
    char m[144];
};

/* A group of four flare slots. */
struct Group {
    Flare f[4];
};

/* The sunshine flares (0x0350cc on). */
struct CSun {
    CSun() : m44(0), m48(0) {}
    int m0[6];
    char m24[20];
    Group *m44;
    int m48;
};
extern "C" {
void f_0350cc(Flare *f, void *sub, int a, int b);
void f_035660(Flare *f, void *sub);
void f_0356b0(CSun *s, void *view, int w, int h, int n);
void f_0357cc(CSun *s);
unsigned int *f_035818(CSun *s, void *view, unsigned int *p, float lo, float hi, float y);
}

struct View {
    char m0[288];
    float m288[16];
    char m352[352];
    float m704;
};

class CRaceEffects {
public:
    void f_031b98(View *view);
    void f_031c04();
    void f_031c40(View *view);
    void f_031cbc(View *view);
    void f_031d4c();
    void f_031d90(int type, const Vec4 *pos, const Vec4 *vel);
    void f_031dac(int i, int j, int a, int b);
    void f_031dfc(int i, int j);
    void f_031e44();
    void f_031e4c(int a, const Vec4 *pos, int b);
    void f_031e8c();

    CParticles particles;
    CSkid skid;
    CLeaves leaves;
    CSun sun;
    char m144[64];
};

/* @implements 0x031b98 us f_031b98
   WHAT IT DOES: Starts the race effects: 50 particles, the skid marks at full opacity, 30 leaves
   and the sunshine flares (64 x 64, 40 of them). */
void CRaceEffects::f_031b98(View *view)
{
    f_032070(&particles, 50);
    f_032e14(&skid, view, 255);
    f_035ef0(&leaves, 30);
    f_0356b0(&sun, view, 64, 64, 40);
}

/* @implements 0x031c04 us f_031c04
   WHAT IT DOES: Marks one frame of effect animation: skid marks, particles and leaves advance
   on their next update. */
void CRaceEffects::f_031c04()
{
    f_033028(&skid);
    f_03228c(&particles);
    f_035ff8(&leaves);
}

/* @draft 0x031c40 us f_031c40
   WHAT IT DOES: Draws the sunshine flares within 200 units above or below the camera height. */
void CRaceEffects::f_031c40(View *view)
{
    float lo = view->m704 - 200.0f;
    float hi = view->m704 + 200.0f;
    f_0216e8(f_035818(&sun, view, f_0216d8(), lo, hi, view->m704));
}

/* @implements 0x031cbc us f_031cbc
   WHAT IT DOES: Draws the effects of one view: leaves, skid marks and particles, then the view's
   own overlay and the dither matrix. */
void CRaceEffects::f_031cbc(View *view)
{
    char *out = m144;
    f_0cdbc4(view->m288, out);
    unsigned int *p = f_0216d8();
    p = f_02df08(p);
    p = f_0362a8(&leaves, p);
    p = f_033034(&skid, view, p);
    p = f_032298(&particles, view, p);
    p = f_0cc584(view, p);
    p = f_02dba8(p);
    f_0216e8(p);
}

/* @implements 0x031d4c us f_031d4c
   WHAT IT DOES: Stops the race effects and frees their buffers. */
void CRaceEffects::f_031d4c()
{
    f_035fcc(&leaves);
    f_0328b0(&particles);
    f_032f9c(&skid);
    f_0357cc(&sun);
}

/* @implements 0x031d90 us f_031d90
   WHAT IT DOES: Emits one exhaust or spark particle at a position with a velocity. */
void CRaceEffects::f_031d90(int type, const Vec4 *pos, const Vec4 *vel)
{
    f_032138(&particles, type, pos, vel);
}

/* @draft 0x031dac us f_031dac
   WHAT IT DOES: Sets up sunshine flare j of group i. */
void CRaceEffects::f_031dac(int i, int j, int a, int b)
{
    Group *g = sun.m44 + i;
    f_0350cc(&g->f[j], sun.m24, a, b);
}

/* @implements 0x031dfc us f_031dfc
   WHAT IT DOES: Clears sunshine flare j of group i. */
void CRaceEffects::f_031dfc(int i, int j)
{
    Group *g = sun.m44 + i;
    f_035660(&g->f[j], sun.m24);
}

/* @implements 0x031e44 us f_031e44
   WHAT IT DOES: Nothing. */
void CRaceEffects::f_031e44()
{
}

/* @implements 0x031e4c us f_031e4c
   WHAT IT DOES: Blows leaves up at a position, starting 50000 units below it. */
void CRaceEffects::f_031e4c(int a, const Vec4 *pos, int b)
{
    f_036600(&leaves, pos, b, a, pos->y - 50000.0f);
}

/* @implements 0x031e8c us f_031e8c
   WHAT IT DOES: Loads the effect textures from the race pack into texture area 1: spark, back
   fire, nitro, black (skid) mark, smoke, leaf and sunshine. */
void CRaceEffects::f_031e8c()
{
    char *seq = D_1dd6b0;
    f_022de4(1, f_005c34(seq, "Spark"), 0xa000001);
    f_022de4(1, f_005c34(seq, "BackFireTex"), 0xa000002);
    f_022de4(1, f_005c34(seq, "NitroTex"), 0xa000007);
    f_022de4(1, f_005c34(seq, "Blackmark"), 0xa000004);
    f_022de4(1, f_005c34(seq, "Smoke"), 0xa000000);
    f_022de4(1, f_005c34(seq, "Leaf"), 0xa000003);
    f_022de4(1, f_005c34(seq, "Sunshine"), 0xa000005);
}

CRaceEffects D_2402e0;

/* @implements 0x031fa8 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global race effects object at startup. */
/* @implements 0x031fec us _GLOBAL__I
   WHAT IT DOES: The startup entry for this file's static data. */
/* @draft 0x03200c us _ZN12CRaceEffectsC1Ev
   WHAT IT DOES: The race effects' constructor: every system starts empty, nothing allocated. */
