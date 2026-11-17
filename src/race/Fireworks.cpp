/* The fireworks (retail 0x0e428c to 0x0e5460, "Hanabi"): a manager of sixteen shells. Each shell
   rises to a bursting time, then throws a ball of 28 by 4 sparks that drift out and fall, fading
   from one colour of a four colour palette to a second. The sparks are drawn as one textured
   quad each; the fade of their brightness and size is looked up in four curve tables that are
   made at start up from the response curves of the neighbouring object file. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    unsigned int m[16];
} __attribute__((aligned(16)));

struct CInfo;

extern "C" {
float f_0e420c(float x);
float f_0e422c(float x);
float f_0e424c(float x);
float f_0e426c(float x);
unsigned int *f_0249a0(CInfo *info, unsigned int *p);
unsigned int *f_0cc584(void *view, unsigned int *p);
Matrix *f_0cdbc4(const Matrix *m, Matrix *out);
void f_028c70(void);
void f_028ca8(void);
void f_02842c(void);
void f_028748(const Matrix *m);
void f_0287cc(float x, float y, float z);
void f_028d94(Matrix *m);
int sceKernelDcacheWritebackRange(void *p, unsigned int size);
float sinf(float x);
float cosf(float x);
}

struct Curve {
    float x[4];
    float y[4];
};
extern Curve D_1d54bc[];

/* A vertex of the spark quad: texture coordinates and a position in signed bytes. */
struct Vtx {
    signed char u, v;
    signed char x, y, z;
};

/* One spark (32 bytes): where it is and which way it moves. */
struct Spark {
    float pos[3];
    int p12;
    float vel[3];
    int p28;
};

/* The state of a shell. */
struct Body {
    int life;           /* +0: frames to the burst */
    float age;          /* +4: how far through the burst it is, 0 to 1 */
    char p8[8];
    float pos[3];       /* +16: where it bursts */
    char p28[4];
    int palette;        /* +32: which colour pair it fades through */
    float size;         /* +36 */
    float m40;
    float col[3];       /* +44: the colour worked out for it this frame */
    char p56[8];
    Spark spark[4][28];
    char tail[10784 - 64 - 3584];
};

/* One shell (10816 bytes). */
struct Shell {
    CInfo *info;        /* +0: the spark texture, held by the first shell only */
    char p4[28];
    Body body;
};

struct Data4 {
    char p0[16];
    struct Tex16 *m16;
};
struct Tex16 {
    CInfo *info;
};
struct Data8 {
    char p0[4];
    Data4 *m4;
};
struct Data {
    char p0[8];
    Data8 *m8;
};

/* The settings of the manager. */
struct Setup {
    float tableLen;     /* +0: how many entries a curve table has */
    float m4;
    float m8;
    int m12;
    int cols;           /* +16: sparks per ring */
    int rings;          /* +20 */
    float m24, m28, m32;
    int frozen;         /* +36: nonzero while a replay is held */
    int visible;        /* +40 */
    float m44, m48;
    float lowest;       /* +52 */
    float m56;
    float fadeRate;     /* +60 */
    int useTable;       /* +64: look the curves up in the tables */
    char p68[12];
    float m80;
    int m84;
    float m88;
    char p92[4];
    int infoIndex;      /* +96 */
    char p100[12];
    unsigned char *table[4];   /* +112 */
    unsigned int color;        /* +128 */
    float (*curve[4])(float);  /* +132 */
};

/* The map manager (src/race/MapManager.cpp): its random seed at +13020. */
struct MapMgr {
    char m0[13020];
    unsigned int seed;

    int Rand()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return (int)(seed >> 1) % 32768;
    }
    float Rand01()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return (int)((seed >> 1) & 0xffff) / 65535.0f;
    }
    float Range(float lo, float hi) { return Rand01() * (hi - lo) + lo; }
};
extern MapMgr D_23c820;

struct Fireworks {
    Shell shell[16];
    char p0[32];
    Vtx vtx[4];         /* the quad of one spark */
    char p1[12];
    Setup cfg;
};

/* The camera view: its matrix at +288. */
struct View {
    char p0[288];
    Matrix mat;
};

extern "C" {
void f_0e428c(Fireworks *m, Data *data);
void f_0e43ec(Fireworks *m, void *owner);
void f_0e444c(Fireworks *m, Body *b);
unsigned int *f_0e486c(Fireworks *m, Body *b, unsigned int *p);
float f_0e49dc(Fireworks *m, int i, float x);
void f_0e4a9c(Fireworks *m);
Curve *f_0e4c74(Fireworks *m, int i);
unsigned int *f_0e4c88(Fireworks *m, unsigned int *p);
unsigned int *f_0e4d28(Fireworks *m, unsigned int *p, View *view, float x, float y, float z);
void f_0e5394(Fireworks *m, float v);
}

/* @implements 0x0e4c74 us f_0e4c74
   WHAT IT DOES: The address of the given response curve of the neighbouring object file. */
Curve *f_0e4c74(Fireworks *m, int i)
{
    return &D_1d54bc[i];
}

/* @implements 0x0e43ec us f_0e43ec
   WHAT IT DOES: Frees the four curve tables. */
void f_0e43ec(Fireworks *m, void *owner)
{
    for (int i = 0; i < 4; i++) {
        if (m->cfg.table[i])
            delete[] m->cfg.table[i];
    }
}

/* One corner of the spark quad. */
static inline void SetV(Vtx *q, int u, int v, int x, int y, int z)
{
    q->x = x;
    q->y = y;
    q->z = z;
    q->u = u;
    q->v = v;
}

/* @draft 0x0e5394 us f_0e5394
   DRAFT: same instructions and size; the register numbers of the byte constants and the order
   of the last corner's last two stores differ (18 words).
   WHAT IT DOES: Sets the corners of the spark quad: a square 126 wide, its height spanning
   one unit about the given offset. */
void f_0e5394(Fireworks *m, float v)
{
    int a = (int)((v + -0.5f) * 127.0f);
    int b = (int)((v + 0.5f) * 127.0f);
    Vtx *q = m->vtx;

    SetV(q, 0, 0, -63, a, 0);
    q++;
    SetV(q, 0, 127, -63, b, 0);
    q++;
    SetV(q, 127, 0, 63, a, 0);
    q++;
    SetV(q, 127, 127, 63, b, 0);
    sceKernelDcacheWritebackRange(m->vtx, 20);
}

/* @implements 0x0e4c88 us f_0e4c88
   WHAT IT DOES: Writes the render state of the sparks into the display list: blending on
   with the manager's colour, the texture function and the colour table. */
unsigned int *f_0e4c88(Fireworks *m, unsigned int *p)
{
    *p++ = 0x56ffffff;
    *p++ = 0x8f000000;
    *p++ = m->cfg.color | 0x90000000;
    *p++ = 0x18000001;
    *p++ = 0x5f000100;
    *p++ = 0x63490ba6;
    *p++ = 0x64489105;
    *p++ = 0x654972eb;
    *p++ = 0x5c808080;
    return p;
}

/* @draft 0x0e49dc us f_0e49dc
   DRAFT: same instructions; the registers of the settings base and the table flag differ
   (a3/a2 for t0/a3, 15 words).
   WHAT IT DOES: A curve value at the given position along its length, from the table when
   tables are in use (the entry at the position, a byte scaled to 0..1) and otherwise from
   the curve itself. */
float f_0e49dc(Fireworks *m, int i, float x)
{
    unsigned char **t = &m->cfg.table[i];
    float (**f)(float) = (float (**)(float))&m->cfg.color + i;

    if (m->cfg.useTable) {
        if (x < 0)
            x = 0;
        if (m->cfg.tableLen - 1.0f < x)
            x = m->cfg.tableLen - 1.0f;
        return (*t)[(int)x] / 255.0f;
    }
    return f[1](x / m->cfg.tableLen);
}

/* @draft 0x0e4a9c us f_0e4a9c
   DRAFT: same size and structure; retail addresses the four curve pointers from the colour
   word (base +0x2a4c0, displacements 4..16, an `ori 0xa4c0` constant) where this builds
   +0x2a4c4 (108 words). Casting to the colour word, an array indexed from it, a struct at
   the colour and a union were all tried.
   WHAT IT DOES: Makes the four curve tables: a byte per entry of the response curve (0 to 255). */
void f_0e4a9c(Fireworks *m)
{
    m->cfg.curve[0] = f_0e420c;
    m->cfg.curve[1] = f_0e422c;
    m->cfg.curve[2] = f_0e424c;
    m->cfg.curve[3] = f_0e426c;
    for (int k = 0; k < 4; k++) {
        m->cfg.table[k] = new unsigned char[(int)m->cfg.tableLen + 1];
        for (int i = 0; i < (int)m->cfg.tableLen; i++)
            m->cfg.table[k][i] = (unsigned int)(m->cfg.curve[k](i / m->cfg.tableLen) * 255.0f);
        m->cfg.table[k][(int)m->cfg.tableLen] = 0;
    }
}

/* @draft 0x0e428c us f_0e428c
   DRAFT: same size; 7 words differ, all in the flag/zero stores before the first
   f_0e5394 call. The two flags are set by one chained assignment, which is what puts the
   constant 1 in $a3 at the top as retail does.
   Cycle 2026-11-16: the 740 store came before the 130.0 store because sched1 emitted li 740
   (and li 4) ahead of the 270.0 constant's lui/lwc1, so after reload v0 reuse fixed that
   order in sched2. Writing m4 = 270.0f before m12 = 740 puts the 270.0 load first: 16 -> 7
   words. Remaining difference: retail stores m84, visible, frozen, lowest, m56, useTable,
   fadeRate, then infoIndex in the call's delay slot; here useTable goes first (leftmost of the
   chained assignment) and m56 lands in the delay slot. Untried lever: the chain written as
   visible = useTable = 1 (handbook: leftmost element first, the rest right to left).
   WHAT IT DOES: Sets the fireworks up: the spark texture of the event's object, the settings,
   the quad, all sixteen shells ready to burst, the curve tables and the quad again. */
void f_0e428c(Fireworks *m, Data *data)
{
    m->cfg.m80 = 1001.0f;
    m->cfg.m88 = 1250.0f;
    m->shell[0].info = data->m8->m4->m16->info;
    m->cfg.m8 = 1200.0f;
    m->cfg.tableLen = 130.0f;
    m->cfg.m4 = 270.0f;
    m->cfg.m12 = 740;
    m->cfg.cols = 28;
    m->cfg.rings = 4;
    m->cfg.m24 = 400.0f;
    m->cfg.m28 = 25.0f;
    m->cfg.m32 = 170.0f;
    m->cfg.m48 = 0.9f;
    m->cfg.m44 = 4.0f;
    m->cfg.m84 = 0;
    m->cfg.useTable = m->cfg.visible = 1;
    m->cfg.frozen = 0;
    m->cfg.lowest = -0.2f;
    m->cfg.m56 = 0;
    m->cfg.fadeRate = 0.2f;
    m->cfg.infoIndex = 0;
    f_0e5394(m, m->cfg.lowest);
    for (int i = 0; i < 16; i++)
        f_0e444c(m, &m->shell[i].body);
    f_0e4a9c(m);
    f_0e5394(m, m->cfg.lowest);
    m->cfg.color = 0;
}

/* @implements 0x0e444c us f_0e444c
   WHAT IT DOES: Readies one shell at random: a time to burst, a place about the middle of the
   sky, a palette, a size and a duration, and the velocities of its 28 by 4 sparks, spread
   over a sphere (the angle about the up axis from the column, the angle from it from the
   ring) at the shell's speed. */
void f_0e444c(Fireworks *m, Body *b)
{
    b->life = D_23c820.Rand() % m->cfg.m12;
    b->age = 0;
    b->pos[0] = D_23c820.Range(-m->cfg.m32, m->cfg.m32);
    b->pos[1] = D_23c820.Range(-m->cfg.m28, m->cfg.m28);
    b->pos[2] = D_23c820.Range(-m->cfg.m32, m->cfg.m32);
    b->palette = D_23c820.Rand() % 4;
    b->pos[0] *= 1000.0f;
    b->pos[1] *= 1000.0f;
    b->pos[2] *= 1000.0f;
    D_23c820.Rand();
    b->size = m->cfg.m4 * 1000.0f * D_23c820.Range(0.7f, 1.0f);
    b->m40 = m->cfg.tableLen * D_23c820.Range(0.7f, 1.0f);
    if (D_23c820.Rand01() + b->age < m->cfg.m56)
        b->size = m->cfg.m4 * 1000.0f * 1.3f;
    for (int ring = 0; ring < m->cfg.rings; ring++) {
        for (int col = 0; col < m->cfg.cols; col++) {
            Spark *sp = &b->spark[ring][col];
            sp->pos[2] = sp->pos[1] = sp->pos[0] = 0;
            float c = (float)col / m->cfg.cols * 3.14159f * 2;
            float a = (float)ring / m->cfg.rings * 3.14159f;

            sp->vel[0] = sinf(a) * cosf(c) * m->cfg.m4 * 1000.0f;
            sp->vel[2] = cosf(a) * m->cfg.m4 * 1000.0f;
            sp->vel[1] = sinf(a) * sinf(c) * m->cfg.m4 * 1000.0f;
        }
    }
    if (m->cfg.useTable)
        f_0e5394(m, m->cfg.lowest);
}

/* @draft 0x0e486c us f_0e486c
   DRAFT: same size and instruction sequence up to the palette lookup; retail computes the palette
   row address as index+frame (this has frame+index), keeps the 1.0 in $f0 and shares one
   row base register for the second colour's first two components (46 words).
   WHAT IT DOES: Works out a shell's colour for this moment of its burst: its palette pair mixed
   by the second curve, dimmed by the third. Writes the colour (0 to 1 each) into the shell
   and the colour command for the display list. Returns the end of the list. */
unsigned int *f_0e486c(Fireworks *m, Body *b, unsigned int *p)
{
    f_0e49dc(m, 1, b->age);
    float g = f_0e49dc(m, 2, b->age);
    float h = f_0e49dc(m, 3, b->age);
    float pal[4][2][4] = {
        {{1.0f, 0.4f, 0.4f, 0}, {0.4f, 0.4f, 1.0f, 0}},
        {{0.4f, 1.0f, 0.4f, 0}, {1.0f, 0.4f, 0.4f, 0}},
        {{1.0f, 1.0f, 0.4f, 0}, {0.4f, 1.0f, 1.0f, 0}},
        {{1.0f, 0.4f, 1.0f, 0}, {0.4f, 0.4f, 1.0f, 0}},
    };
    float *c0 = pal[b->palette][0];
    float *c1 = pal[b->palette][1];
    float inv = 1.0f - g;

    b->col[1] = (g * c1[1] + inv * c0[1]) * h;
    b->col[2] = (g * c1[2] + inv * c0[2]) * h;
    b->col[0] = (g * c1[0] + inv * c0[0]) * h;
    *p++ = (int)(b->col[0] * 255.0f) | (int)(b->col[1] * 255.0f) << 8 | (int)(b->col[2] * 255.0f) << 16 | 0xe0000000;
    return p;
}

/* @draft 0x0e4d28 us f_0e4d28
   DRAFT: 3 words shorter than retail (1632 vs 1644 bytes) and 298 of 411 words differ, mostly
   register numbers and scheduling of the display-list stores. Retail keeps the vertex address
   and the quad base word in stack slots (136..144) and spills the view-matrix pointer after
   the texture set up; here the register allocation and the stack slot order differ, and the
   retail loop recomputes the vertex address word (and 0xffffff, or 0x01000000) from the
   saved address where this keeps the first one.
   WHAT IT DOES: Draws the fireworks into the display list: loads the settings' sphere scale,
   sets up the quad and the spark texture, then for each shell that has burst places a
   billboard (the inverse of the view turned to face the viewer, at the shell's position) and
   draws the quad scaled to the shell's size in its colour, counting the shell on and
   starting it over when it is done. The sum of the shells' colours, scaled and kept to 1, is
   left as the manager's colour. Returns the end of the list. */
unsigned int *f_0e4d28(Fireworks *m, unsigned int *p, View *view, float x, float y, float z)
{
    Setup *c = &m->cfg;
    Matrix *vm;
    float r, g, b;

    if (!c->visible)
        return p;
    *p++ = 0x3a000000;
    *p++ = (*(unsigned int *)&m->cfg.m8 >> 8) | 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = (*(unsigned int *)&m->cfg.m8 >> 8) | 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = (*(unsigned int *)&m->cfg.m8 >> 8) | 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x3b000000;
    *p++ = 0x12000081;
    int addr = (int)&m->vtx;
    unsigned int base = ((addr >> 24) & 0xf) << 16 | 0x10000000;
    *p++ = base;
    *p++ = (addr & 0xffffff) | 0x01000000;
    *p++ = 0xe7000001;
    *p++ = 0x1d000000;
    *p++ = 0x1f000000;
    *p++ = 0x17000000;
    *p++ = 0x21000001;
    *p++ = 0xe1ffffff;
    *p++ = 0xdf0000aa;
    *p++ = 0xdbff0306;
    *p++ = 0x22000000;
    p = f_0249a0(((CInfo **)m)[c->infoIndex], p);
    *p++ = 0x1e000001;
    *p++ = 0x55ffffff;
    *p++ = 0x580000ff;
    r = g = b = 0;
    vm = &view->mat;
    for (int i = 0; i < 16; i++) {
        Body *sh = &m->shell[i].body;

        if (!c->frozen)
            sh->life--;
        if (sh->life > 0)
            continue;
        {
            Matrix inv, out;
            float size;

            f_0cdbc4(vm, &inv);
            f_028c70();
            f_02842c();
            f_028748(vm);
            f_0287cc(x + sh->pos[0], y + sh->pos[1], z + sh->pos[2]);
            f_028748(&inv);
            f_028d94(&out);
            f_028ca8();
            *p++ = 0x3c000000;
            *p++ = (out.m[0] >> 8) | 0x3d000000;
            *p++ = (out.m[1] >> 8) | 0x3d000000;
            *p++ = (out.m[2] >> 8) | 0x3d000000;
            *p++ = (out.m[4] >> 8) | 0x3d000000;
            *p++ = (out.m[5] >> 8) | 0x3d000000;
            *p++ = (out.m[6] >> 8) | 0x3d000000;
            *p++ = (out.m[8] >> 8) | 0x3d000000;
            *p++ = (out.m[9] >> 8) | 0x3d000000;
            *p++ = (out.m[10] >> 8) | 0x3d000000;
            *p++ = (out.m[12] >> 8) | 0x3d000000;
            *p++ = (out.m[13] >> 8) | 0x3d000000;
            *p++ = (out.m[14] >> 8) | 0x3d000000;
            size = f_0e49dc(m, 0, sh->age) * sh->size;
            p = f_0e486c(m, sh, p);
            r += sh->col[0];
            g += sh->col[1];
            b += sh->col[2];
            if (!c->frozen)
                sh->age += 1.0f;
            if (c->tableLen <= sh->age)
                f_0e444c(m, sh);
            sceKernelDcacheWritebackRange(&size, 4);
            *p++ = 0x3a000000;
            *p++ = ((*(unsigned int *)&size >> 8) & 0xffffff) | 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = ((*(unsigned int *)&size >> 8) & 0xffffff) | 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = ((*(unsigned int *)&size >> 8) & 0xffffff) | 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = 0x3b000000;
            *p++ = base;
            *p++ = (addr & 0xffffff) | 0x01000000;
            *p++ = 0x04040004;
        }
    }
    *p++ = 0xe7000000;
    *p++ = 0xdf0000aa;
    r *= c->fadeRate;
    b *= c->fadeRate;
    g *= c->fadeRate;
    if (1.0f < r)
        r = 1.0f;
    if (1.0f < g)
        g = 1.0f;
    if (1.0f < b)
        b = 1.0f;
    m->cfg.color = (int)(r * 255.0f) | (int)(g * 255.0f) << 8 | (int)(b * 255.0f) << 16;
    p = f_0cc584(view, p);
    *p++ = 0x22000001;
    return p;
}
