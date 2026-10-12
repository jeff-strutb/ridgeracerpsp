/* The simple drawing object file (retail 0x021fd8 to 0x022b78): screen clearing and untextured
   or textured lines, strips and sprites in screen coordinates. Each call copies its vertices
   byte by byte into a block taken from the back of this frame's display list buffer (the
   source arrays need not be aligned), sets the render state it needs and draws them. It also
   keeps the clear colour, stencil value and depth, and copies images into the draw buffer. */

extern "C" {
void f_1164c8(void *list);
void f_1165dc(int mode, int what);
void f_1166d4(int state);
void f_116898(int state);
void f_116dfc(int prim, int vtype, int count, const void *indices, const void *vertices);
void f_11776c(int psm, int sx, int sy, int width, int height, int srcw, void *src, int dx, int dy,
              int destw, void *dest);
void f_1181c0(unsigned int color);
}

unsigned char *f_021b38(unsigned int size);
void *f_021d5c(void);

/* The pixel format, and the clear colour, stencil value and depth. */
extern int D_23c1c0;
extern unsigned int D_23c1e4;
extern int D_23c1e8;
extern unsigned short D_23c1ec;

/* The vertex layouts the drawing calls build, packed because the vertex block is filled
   without regard to alignment: screen space with 16 bit coordinates, the same with 16 bit
   texture coordinates first, and the floating point forms of both. */
struct SVert {
    unsigned short x, y, z;
} __attribute__((packed));

struct STVert {
    unsigned short u, v;
    unsigned short x, y, z;
} __attribute__((packed));

struct FVert {
    float x, y, z;
} __attribute__((packed));

struct FTVert {
    float u, v;
    float x, y, z;
} __attribute__((packed));

/* The source forms: 16 bit positions and texture coordinates, and floating point vectors and
   texture coordinates. */
struct Pos16 { unsigned short x, y, z; };
struct UV16 { unsigned short u, v; };
struct Vec4 { float x, y, z, w; };
struct Vec2 { float u, v; };

/* @implements 0x021fd8 us f_021fd8
   WHAT IT DOES: waits until the graphics engine has finished drawing. */
void f_021fd8(void)
{
    f_1165dc(0, 0);
}

/* @implements 0x021ff8 us f_021ff8
   WHAT IT DOES: sets the colour the screen is cleared to. */
void f_021ff8(unsigned int color)
{
    D_23c1e4 = color & 0xffffff;
}

/* @implements 0x022010 us f_022010
   WHAT IT DOES: sets the stencil value the screen is cleared to. */
void f_022010(int stencil)
{
    D_23c1e8 = stencil & 0xff;
}

/* @implements 0x022020 us f_022020
   WHAT IT DOES: sets the depth the screen is cleared to. */
void f_022020(unsigned short depth)
{
    D_23c1ec = depth;
}

/* @implements 0x02202c us f_02202c
   WHAT IT DOES: writes the commands that clear the screen (the buffers chosen by the flags) to
   the clear colour, stencil and depth: eight 64 pixel wide sprites covering the screen, with
   the stencil value moved into the alpha bits of the pixel format. Returns the end of the
   commands. */
unsigned int *f_02202c(int flags, unsigned int *p)
{
    unsigned int stencil;
    unsigned char *buf;
    SVert *d;
    int x;

    switch (D_23c1c0) {
    case 1:
        stencil = D_23c1e8 << 7;
        break;
    case 2:
        stencil = D_23c1e8 << 4;
        break;
    case 3:
        stencil = D_23c1e8;
        break;
    default:
        stencil = 0;
        break;
    }
    buf = f_021b38(96);
    d = (SVert *)buf;
    for (x = 0; x < 480; x += 64) {
        d[0].x = x;
        d[0].y = 0;
        d[0].z = D_23c1ec;
        d[1].x = x + 64;
        d[1].y = 272;
        d[1].z = D_23c1ec;
        d += 2;
    }
    *p++ = 0x55000000 | D_23c1e4;
    *p++ = 0x58000000 | stencil;
    *p++ = 0xd3000001 | (flags << 8);
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)buf >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)buf & 0xffffff);
    *p++ = 0x04060010;
    *p++ = 0xd3000000;
    return p;
}

/* @implements 0x0221e8 us f_0221e8
   WHAT IT DOES: clears the screen (the buffers chosen by the flags) through a small call list
   placed in the frame's vertex space. */
void f_0221e8(int flags)
{
    unsigned int *list = (unsigned int *)f_021b38(36);

    *f_02202c(flags, list) = 0x0b000000;
    f_1164c8(list);
}

/* @implements 0x022238 us f_022238
   WHAT IT DOES: draws a line strip in one colour through n points given as 16 bit screen
   coordinates (x, y, z), with depth test, texturing and fog off. */
void f_022238(const Pos16 *v, unsigned int n, unsigned int color)
{
    SVert *buf = (SVert *)f_021b38(n * 6);
    SVert *d = buf;
    unsigned int i;

    for (i = 0; i < n; i++) {
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        v++;
        d++;
    }
    f_116898(7);
    f_116898(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(2, 0x800100, n, 0, buf);
}

/* @implements 0x02231c us f_02231c
   WHAT IT DOES: draws one filled rectangle in one colour from its two corners, given as 16 bit
   screen coordinates, with depth test, blending, texturing and fog off. */
void f_02231c(const Pos16 *v, unsigned int color)
{
    SVert *buf = (SVert *)f_021b38(12);

    buf[0].x = v[0].x;
    buf[0].y = v[0].y;
    buf[0].z = v[0].z;
    buf[1].x = v[1].x;
    buf[1].y = v[1].y;
    buf[1].z = v[1].z;
    f_116898(5);
    f_116898(7);
    f_116898(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(6, 0x800100, 2, 0, buf);
}

/* @implements 0x022400 us f_022400
   WHAT IT DOES: draws one textured rectangle tinted by a colour, from its two corners and
   their texture coordinates, with depth test, blending and fog off and texturing on. */
void f_022400(const Pos16 *v, const UV16 *uv, unsigned int color)
{
    STVert *buf = (STVert *)f_021b38(20);

    buf[0].x = v[0].x;
    buf[0].y = v[0].y;
    buf[0].z = v[0].z;
    buf[0].u = uv[0].u;
    buf[0].v = uv[0].v;
    buf[1].x = v[1].x;
    buf[1].y = v[1].y;
    buf[1].z = v[1].z;
    buf[1].u = uv[1].u;
    buf[1].v = uv[1].v;
    f_116898(5);
    f_116898(7);
    f_1166d4(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(6, 0x800102, 2, 0, buf);
}

/* @implements 0x022530 us f_022530
   WHAT IT DOES: draws a triangle strip in one colour through n points given as 16 bit screen
   coordinates, with depth test, blending, texturing and fog off. */
void f_022530(const Pos16 *v, unsigned int n, unsigned int color)
{
    SVert *buf = (SVert *)f_021b38(n * 6);
    SVert *d = buf;
    unsigned int i;

    for (i = 0; i < n; i++) {
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        v++;
        d++;
    }
    f_116898(5);
    f_116898(7);
    f_116898(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(4, 0x800100, n, 0, buf);
}

/* @implements 0x02261c us f_02261c
   WHAT IT DOES: draws a textured triangle strip tinted by a colour through n points given as
   16 bit screen coordinates and texture coordinates, with depth test, blending and fog off and
   texturing on. */
void f_02261c(const Pos16 *v, const UV16 *uv, unsigned int n, unsigned int color)
{
    STVert *buf = (STVert *)f_021b38(n * 10);
    STVert *d = buf;
    unsigned int i;

    for (i = 0; i < n; i++) {
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        d->u = uv->u;
        d->v = uv->v;
        v++;
        uv++;
        d++;
    }
    f_116898(5);
    f_116898(7);
    f_1166d4(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(4, 0x800102, n, 0, buf);
}

/* @implements 0x022738 us f_022738
   WHAT IT DOES: draws a line strip in one colour through n points given as floating point
   vectors, with depth test, texturing and fog off. */
void f_022738(const Vec4 *v, unsigned int n, unsigned int color)
{
    FVert *buf = (FVert *)f_021b38(n * 12);
    FVert *d = buf;
    unsigned int i;

    for (i = 0; i < n; i++) {
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        v++;
        d++;
    }
    f_116898(7);
    f_116898(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(2, 384, n, 0, buf);
}

/* Retail 0x022848, f_022848: byte-exact here, but its tag stays in src/control/batch6.c.
   WHAT IT DOES: draws a triangle strip in one colour through n points given as floating point
   vectors, with depth test, blending, texturing and fog off. */
void f_022848(const Vec4 *v, unsigned int n, unsigned int color)
{
    FVert *buf = (FVert *)f_021b38(n * 12);
    FVert *d = buf;
    unsigned int i;

    for (i = 0; i < n; i++) {
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        v++;
        d++;
    }
    f_116898(5);
    f_116898(7);
    f_116898(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(4, 384, n, 0, buf);
}

/* @implements 0x022960 us f_022960
   WHAT IT DOES: draws a textured triangle strip tinted by a colour through n points given as
   floating point vectors and texture coordinates, with depth test, blending and fog off and
   texturing on. */
void f_022960(const Vec4 *v, const Vec2 *uv, unsigned int n, unsigned int color)
{
    FTVert *buf = (FTVert *)f_021b38(n * 20);
    FTVert *d = buf;
    unsigned int i;

    for (i = 0; i < n; i++) {
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        d->u = uv->u;
        d->v = uv->v;
        v++;
        uv++;
        d++;
    }
    f_116898(5);
    f_116898(7);
    f_1166d4(9);
    f_116898(10);
    f_1181c0(color);
    f_116dfc(4, 387, n, 0, buf);
}

/* @implements 0x022ac8 us f_022ac8
   WHAT IT DOES: copies a rectangle of an image into the buffer being drawn this frame. */
void f_022ac8(int psm, int sx, int sy, int height, int width, int srcw, void *src, int dx, int dy)
{
    f_11776c(psm, sx, sy, width, height, srcw, src, dx, dy, 512, f_021d5c());
}
