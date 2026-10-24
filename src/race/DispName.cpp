/* The name display (CDispName, retail 0x0e6854 to 0x0e7114): a player name drawn as a row of
   font glyph sprites standing at a point in the world. Regist turns the name into glyph
   records and builds two sprite lists from them (drawn on alternate frames); Render projects
   the name's two corner points, sizes the row by their screen distance (clamped, and not
   drawn when far too small or large), lays the sprites out from the projected centre and adds
   the display list commands that draw them. The font texture (0x0a000280) is shared by every
   instance: loaded by the setup function, released by the shutdown one. */

struct Glyph;
struct TextStyle;
struct CInfo;

/* A glyph record as Regist reads it: its place in the font texture and its size. */
struct GlyphRec {
    unsigned short m0;
    unsigned short u;
    unsigned short v;
    unsigned short width;
    unsigned short height;
};

/* A sprite corner: texture coordinates and position (two per glyph). */
struct Vtx {
    unsigned short u, v;
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[16];
} __attribute__((aligned(16)));

/* The camera as Render reads it: its view rotation and projection. */
struct CameraView {
    char m0[288];
    Matrix view;
    char m160[64];
    Matrix proj;
};

/* The part of the screen object used here (0x017970): an enable flag and the font texture
   file per language. */
struct ScreenInfo {
    int m0;
    int on;
    char m8[36];
    int font[1];
};

extern "C" {
ScreenInfo *f_017970(void);
void f_07ac1c(TextStyle *t);
int f_07ac48(TextStyle *t, const char *s, GlyphRec *out);
void *f_022d00(int file, int id);
CInfo *f_02347c(int id);
int f_023250(int id);
unsigned int *f_0249a0(CInfo *info, unsigned int *p);
int f_00d354(char *buf, int size, const char *fmt, ...);
Matrix *f_0cdbc4(const Matrix *m, Matrix *out);
void f_028c70(void);
void f_02842c(void);
void f_028748(const Matrix *m);
Vec4 *f_027f3c(Vec4 *d, const Vec4 *a);
void f_028ca8(void);
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);
}

/* Absolute value in double precision. */
static inline double Fabs(double x)
{
    if (x < 0.0)
        x = -x;
    return x;
}

extern char D_245178[];         /* the debug message buffer */

extern int D_27e880;            /* the font texture's id */
extern CInfo *D_27e884;         /* its texture */
extern int D_27e888;            /* set up */

extern float D_1d553c;          /* the name's height above the point */
extern float D_1d5540;          /* width and height scales */
extern float D_1d5544;
extern float D_1d5548;          /* the size clamp */
extern float D_1d554c;
extern float D_1d5550;          /* the drawn size range */
extern float D_1d5554;
extern int D_1d5558;            /* the colour */
extern int D_1d555c;
extern int D_1d5560;

class CDispName {
public:
    Vtx *buf[2];
    int nv;
    int n;
    int frame;
    float width;

    CDispName();
    ~CDispName();
    void f_0e69e4(const char *name);
    void f_0e6b1c();
    unsigned int *f_0e6b88(CameraView *cam, Vec4 *pos, unsigned int *dl);
};

/* @implements 0x0e6854 us f_0e6854
   WHAT IT DOES: Loads the font texture of the current language (if the screen is enabled) and
   marks the name display set up. */
extern "C" void f_0e6854(void)
{
    char buf[16];
    GlyphRec g[16];
    int *tab;

    if (f_017970()->on == 0)
        return;
    tab = f_017970()->font;
    f_07ac1c((TextStyle *)buf);
    f_07ac48((TextStyle *)buf, "a", g);
    D_27e880 = 0x0a000280;
    f_022d00(tab[*(unsigned char *)&g[0]], D_27e880);
    D_27e884 = f_02347c(D_27e880);
    D_27e888 = 1;
}

/* @implements 0x0e68f8 us f_0e68f8
   WHAT IT DOES: Releases the font texture and marks the name display shut down. Returns the
   release's result. */
extern "C" int f_0e68f8(void)
{
    int r = f_023250(D_27e880);
    D_27e888 = 0;
    return r;
}

/* @implements 0x0e6920 us f_0e6920
   WHAT IT DOES: Adds the display list commands that select the font texture and the sprite
   drawing state (when set up). Returns the next command slot. */
extern "C" unsigned int *f_0e6920(unsigned int *p)
{
    if (!D_27e888)
        return p;
    p = f_0249a0(D_27e884, p);
    *p++ = 0x1e000001;
    *p++ = 0x21000001;
    *p++ = 0xdf000032;
    return p;
}

/* @implements 0x0e698c us f_0e698c
   WHAT IT DOES: Returns its argument. */
extern "C" void *f_0e698c(void *p)
{
    return p;
}

/* @implements 0x0e6994 us _ZN9CDispNameC2Ev
   WHAT IT DOES: An empty name: no sprite lists. */
/* @implements 0x0e69a0 us _ZN9CDispNameC1Ev
   WHAT IT DOES: The complete-object copy of the constructor. */
CDispName::CDispName()
{
    buf[1] = buf[0] = 0;
}

/* @implements 0x0e69ac us _ZN9CDispNameD2Ev
   WHAT IT DOES: Frees the sprite lists. */
/* @implements 0x0e69c8 us _ZN9CDispNameD1Ev
   WHAT IT DOES: The complete-object copy of the destructor. */
CDispName::~CDispName()
{
    f_0e6b1c();
}

/* @implements 0x0e69e4 us _ZN9CDispName8f_0e69e4EPKc
   WHAT IT DOES: Registers a name: converts it to glyph records (up to 16) and builds both
   sprite lists from them (two corners per glyph, holding its texture rectangle), summing the
   glyph widths into the row width. Nothing when the name is null or the display is not set
   up. */
void CDispName::f_0e69e4(const char *name)
{
    char st[16];
    GlyphRec g[16];
    int c;
    int j, i;

    if (name == 0 || !D_27e888)
        return;
    f_07ac1c((TextStyle *)st);
    f_00d354(D_245178, 1024, "CDispName::Regist  Name:%s\n", name);
    c = f_07ac48((TextStyle *)st, name, g);
    nv = c * 2;
    n = c;
    buf[0] = new Vtx[nv];
    buf[1] = new Vtx[nv];
    width = 0;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < n; i++) {
            Vtx *v = &buf[j][i * 2];
            v[0].u = g[i].u;
            v[0].v = g[i].v;
            v[1].u = g[i].u + g[i].width;
            v[1].v = g[i].v + g[i].height;
            if (j == 0)
                width += g[i].width;
        }
    }
    frame = 0;
}

/* @implements 0x0e6b1c us _ZN9CDispName8f_0e6b1cEv
   WHAT IT DOES: Frees both sprite lists (when the display is set up). */
void CDispName::f_0e6b1c()
{
    if (!D_27e888)
        return;
    if (buf[0])
        delete[] buf[0];
    if (buf[1])
        delete[] buf[1];
    buf[1] = buf[0] = 0;
}

/* @draft 0x0e6b88 us _ZN9CDispName8f_0e6b88EP10CameraViewP4Vec4Pj
   WHAT IT DOES: Draws the name standing above pos (raised by D_1d553c in place): projects its
   two corners, takes the row's screen size from their distance, clamps it (not drawn below 0.1
   or above 4), lays this frame's sprite list out from the projected centre and adds the
   commands that draw it in the name colour. Returns the next command slot.
   DRAFT: same size; everything past the first call matches. In the prologue retail keeps the
   frame counter in v0 and the corner initialiser's address in v1 (swapped here) and stores
   the initialiser's first word last, in the first call's delay slot; four statement orders
   and declaration splits did not move it. The scorer also reports the second double
   constant's high word (272.0) as differing, since it reads 8 bytes from the middle of the
   constant. */
unsigned int *CDispName::f_0e6b88(CameraView *cam, Vec4 *pos, unsigned int *dl)
{
    if (!D_27e888)
        return dl;
    if (buf[0] == 0) {
        f_00d354(D_245178, 1024, "CDispName::Render Error.  this instance is not initilized\n");
        return dl;
    }
    pos->y = pos->y + D_1d553c;
    Vec4 cur;
    Vec4 s;
    Matrix m;
    Vec4 c[2] = { { -1.2f, 0.0f, 0.0f, 1.0f }, { 1.2f, 230.0f, 0.0f, 1.0f } };
    Vec4 a;
    Vec4 b;
    Vtx *v = buf[frame++ & 1];

    f_0cdbc4(&cam->view, &m);
    m.m[14] = pos->z;
    m.m[12] = pos->x;
    m.m[13] = pos->y;
    f_028c70();
    f_02842c();
    f_028748(&cam->proj);
    f_028748(&m);
    f_027f3c(&a, &c[0]);
    f_027f3c(&b, &c[1]);
    f_028ca8();
    if (a.w <= 0.0f)
        return dl;
    f_027e6c(&a, &a, 1.0f / a.w);
    f_027e6c(&b, &b, 1.0f / b.w);
    s.x = (a.x + b.x) * 0.5f * 240.0f + 240.0f;
    s.y = (a.y + b.y) * 0.5f * -136.0f + 136.0f;
    s.z = (a.z + b.z) * 0.5f * -32768.0f + 32767.0f;
    float w = Fabs(a.x - b.x) * 2710.027099609375 * D_1d5540;
    float h = Fabs(a.y - b.y) * 272.0f * D_1d5544;
    if (w < D_1d5550)
        return dl;
    if (D_1d5554 < w)
        return dl;
    float k = w;
    if (w < D_1d5548)
        k = D_1d5548;
    if (D_1d554c < w)
        k = D_1d554c;
    k = k / w;
    w = w * k;
    h = h * k;
    cur.x = s.x - width * 0.5f * w;
    cur.y = s.y;
    cur.z = s.z;
    for (int i = 0; i < n; i++) {
        Vtx *q = &v[i * 2];
        q[0].x = cur.x;
        q[0].y = cur.y - h;
        q[0].z = cur.z;
        float d = (float)(q[1].u - q[0].u) * w;
        q[1].x = cur.x + d;
        q[1].y = cur.y;
        q[1].z = cur.z;
        cur.x = cur.x + d;
    }
    *dl++ = 0x23000001;
    *dl++ = 0x1d000000;
    *dl++ = 0x22000000;
    *dl++ = 0x17000000;
    *dl++ = D_1d5558 | D_1d555c << 8 | D_1d5560 << 16 | 0x55000000;
    *dl++ = 0x580000ff;
    *dl++ = 0x12800182;
    *dl++ = ((int)v >> 24 & 0xf) << 16 | 0x10000000;
    *dl++ = ((int)v & 0xffffff) | 0x01000000;
    *dl++ = nv | 0x04060000;
    return dl;
}
