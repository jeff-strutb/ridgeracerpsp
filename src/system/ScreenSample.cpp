/* The screen sampling object file (retail 0x02048c to 0x0213a0): two command list writers that
   measure how much of a small screen area is covered (for example a light that may be hidden
   behind scenery). Each one draws a marker sprite over the area with a stencil or alpha test
   against the depth of the scene, then, rendering into a 64 pixel wide work target at the
   top of video memory, sums every sampled pixel of the area into one point with additive
   blending, and leaves the result where the caller can read it back. */

extern "C" {
void *sceGeEdramGetAddr(void);
}

unsigned char *f_021b38(unsigned int size);
void *f_021d5c(void);
unsigned int f_021d38(void);

/* The vertex layouts written into the list buffer, packed: 16 bit screen coordinates, and the
   same with 16 bit texture coordinates first. */
struct SVert {
    unsigned short x, y, z;
} __attribute__((packed));

struct STVert {
    unsigned short u, v;
    unsigned short x, y, z;
} __attribute__((packed));

/* A screen position given by the caller. */
struct Pos16 { unsigned short x, y, z; };

/* The pixel format (owned by the graphics system). */
extern int D_23c1c0;

/* The one pixel line, and the 32 by 1 and 32 by 16 texture sprites, used to read the sums
   back. */
SVert D_1d1940[2] = { { 0, 0, 0 }, { 256, 0, 0 } };
STVert D_1d194c[2] = { { 0, 0, 0, 0, 0 }, { 32, 1, 32, 1, 0 } };
STVert D_1d1960[2] = { { 0, 0, 0, 0, 0 }, { 32, 16, 32, 16, 0 } };

/* The points that clear the sum, one for each writer. */
SVert D_23c198;
SVert D_23c1a0;

/* @implements 0x02048c us f_02048c
   WHAT IT DOES: writes the commands that sample a square around a screen position into the
   given target. The low bits of the mode pick the size of the square and the sampling step
   (4 by 4, 8 by 8, or 16 by 16 sampled every other pixel); the top bit picks a 32 by 16 read
   back instead of 32 by 1. Returns the end of the commands. */
unsigned int *f_02048c(const Pos16 *pos, unsigned int fb, int mode, unsigned int *p)
{
    char *tex = (char *)sceGeEdramGetAddr() + 0x1fff00;
    int count = 0;
    short off = 0;
    int step = 0;
    SVert *marker;
    STVert *pts;
    STVert *d;
    short x0, x1, y0, y1, x, y;
    int n, i;

    *p++ = 0x20000000;
    *p++ = 0xe7000001;
    *p++ = 0x21000001;
    *p++ = 0xdf0000a2;
    *p++ = 0xe1ffffff;
    *p++ = 0xc6000000;
    *p++ = 0xc9000103;
    switch (mode & 0x7f) {
    case 0:
        count = 16;
        off = 2;
        step = 1;
        break;
    case 1:
        count = 64;
        off = 4;
        step = 1;
        break;
    case 2:
        count = 64;
        off = 8;
        step = 2;
        break;
    }
    *p++ = 0x23000001;
    *p++ = 0x24000001;
    *p++ = 0x22000000;
    *p++ = 0xdcffff01;
    *p++ = 0xdd020101;
    *p++ = 0xe8ffffff;
    marker = (SVert *)f_021b38(12);
    marker[0].x = pos->x - off;
    marker[0].y = pos->y - off;
    marker[0].z = pos->z;
    marker[1].x = off + pos->x;
    marker[1].y = off + pos->y;
    marker[1].z = pos->z;
    *p++ = 0x1e000000;
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)marker >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)marker & 0xffffff);
    *p++ = 0x04060002;
    *p++ = 0xc2000000;
    *p++ = 0xc3000000 | D_23c1c0;
    {
        unsigned int src = (unsigned int)f_021d5c();

        *p++ = 0xa0000000 | (src & 0xffffff);
        *p++ = 0xa8000200 | (((src >> 24) & 0xf) << 16);
    }
    *p++ = 0xb8000909;
    *p++ = 0xd2000003;
    *p++ = 0x9c1fff00;
    *p++ = 0x9d000040;
    *p++ = 0xcb000000;
    *p++ = 0xe8000000;
    *p++ = 0x55000000;
    *p++ = 0x58000000;
    *p++ = 0xd3000301;
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)&D_23c198 >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)&D_23c198 & 0xffffff);
    *p++ = 0x04000001;
    *p++ = 0xd3000000;
    *p++ = 0x23000000;
    *p++ = 0x22000001;
    *p++ = 0xdd040404;
    *p++ = 0x1e000001;
    *p++ = 0xe8ffffff;
    x0 = pos->x - off;
    x1 = off + pos->x;
    y0 = pos->y - off;
    y1 = off + pos->y;
    if (x0 < 0)
        x0 = 0;
    else if (x0 > 480)
        x0 = 480;
    if (x1 < 0)
        x1 = 0;
    else if (x1 > 480)
        x1 = 480;
    if (y0 < 0)
        y0 = 0;
    else if (y0 > 272)
        y0 = 272;
    if (y1 < 0)
        y1 = 0;
    else if (y1 > 272)
        y1 = 272;
    pts = (STVert *)f_021b38(count * 10);
    n = 0;
    d = pts;
    for (y = y0; y < y1; y += step) {
        for (x = x0; x < x1; x += step) {
            d->u = x;
            d->v = y;
            d->x = 0;
            d->y = 0;
            d->z = 0;
            d++;
            n++;
        }
    }
    if (n > 0) {
        *p++ = 0x12800102;
        *p++ = 0x10000000 | ((((unsigned int)pts >> 24) & 0xf) << 16);
        for (i = 0; i < 128; i += count) {
            *p++ = 0x01000000 | ((unsigned int)pts & 0xffffff);
            *p++ = 0x04000000 | count;
        }
    }
    *p++ = 0xc2000000;
    *p++ = 0xc3000000;
    *p++ = 0xc7000000;
    *p++ = 0xa0000000 | ((unsigned int)tex & 0xffffff);
    *p++ = 0xa8000200 | ((((unsigned int)tex >> 24) & 0xf) << 16);
    *p++ = 0xb8000001;
    *p++ = 0x9c000000 | (fb & 0xffffff);
    *p++ = 0x9d000020 | ((fb >> 24) << 16);
    *p++ = 0x58000000;
    *p++ = 0xd3000201;
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)D_1d1940 >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)D_1d1940 & 0xffffff);
    *p++ = 0x04010002;
    *p++ = 0xd3000000;
    *p++ = 0xd2000000;
    *p++ = 0xcb000000;
    *p++ = 0x24000000;
    *p++ = 0x22000000;
    *p++ = 0xe8000000;
    *p++ = 0x55ffffff;
    *p++ = 0x580000ff;
    *p++ = 0x12800102;
    if (mode & 0x80) {
        *p++ = 0x10000000 | ((((unsigned int)D_1d1960 >> 24) & 0xf) << 16);
        *p++ = 0x01000000 | ((unsigned int)D_1d1960 & 0xffffff);
    } else {
        *p++ = 0x10000000 | ((((unsigned int)D_1d194c >> 24) & 0xf) << 16);
        *p++ = 0x01000000 | ((unsigned int)D_1d194c & 0xffffff);
    }
    *p++ = 0x04060002;
    *p++ = 0xd2000000 | D_23c1c0;
    {
        unsigned int dst = f_021d38();

        *p++ = 0x9c000000 | (dst & 0xffffff);
        *p++ = 0x9d000200 | ((dst >> 24) << 16);
    }
    *p++ = 0x23000001;
    *p++ = 0x22000001;
    *p++ = 0xc9000100;
    *p++ = 0xe7000000;
    *p++ = 0x20000001;
    *p++ = 0xcc000000;
    return p;
}

/* @implements 0x020cd4 us f_020cd4
   WHAT IT DOES: the second sampler. Writes the commands that sample a square around a screen
   position (the mode picks the size and step as for f_02048c) and sum it into one pixel of the
   work target, then point drawing back at the screen's back buffer. Returns the end of the
   commands. */
unsigned int *f_020cd4(const Pos16 *pos, int mode, unsigned int *p)
{
    char *tex = (char *)sceGeEdramGetAddr() + 0x1fff00;
    int count = 0;
    short off = 0;
    int step = 0;
    SVert *marker;
    STVert *pts;
    STVert *d;
    short x0, x1, y0, y1, x, y;
    int n, i;

    *p++ = 0x20000000;
    *p++ = 0xe7000001;
    *p++ = 0x21000001;
    *p++ = 0xdf0000a2;
    *p++ = 0xe1ffffff;
    *p++ = 0xc6000000;
    *p++ = 0xc9000103;
    switch (mode) {
    case 0:
        count = 16;
        off = 2;
        step = 1;
        break;
    case 1:
        count = 64;
        off = 4;
        step = 1;
        break;
    case 2:
        count = 64;
        off = 8;
        step = 2;
        break;
    }
    *p++ = 0x23000001;
    *p++ = 0x24000001;
    *p++ = 0x22000000;
    *p++ = 0xdcffff01;
    *p++ = 0xdd020101;
    *p++ = 0xe8ffffff;
    marker = (SVert *)f_021b38(12);
    marker[0].x = pos->x - off;
    marker[0].y = pos->y - off;
    marker[0].z = pos->z;
    marker[1].x = off + pos->x;
    marker[1].y = off + pos->y;
    marker[1].z = pos->z;
    *p++ = 0x1e000000;
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)marker >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)marker & 0xffffff);
    *p++ = 0x04060002;
    *p++ = 0xc2000000;
    *p++ = 0xc3000000 | D_23c1c0;
    {
        unsigned int src = (unsigned int)f_021d5c();

        *p++ = 0xa0000000 | (src & 0xffffff);
        *p++ = 0xa8000200 | (((src >> 24) & 0xf) << 16);
    }
    *p++ = 0xb8000909;
    *p++ = 0xd2000003;
    *p++ = 0x9c1fff00;
    *p++ = 0x9d000040;
    *p++ = 0xcb000000;
    *p++ = 0xe8000000;
    *p++ = 0x55ffffff;
    *p++ = 0x58000000;
    *p++ = 0xd3000301;
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)&D_23c1a0 >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)&D_23c1a0 & 0xffffff);
    *p++ = 0x04000001;
    *p++ = 0xd3000000;
    *p++ = 0x23000000;
    *p++ = 0x22000001;
    *p++ = 0xdd040404;
    *p++ = 0x1e000001;
    *p++ = 0xe8ffffff;
    x0 = pos->x - off;
    x1 = off + pos->x;
    y0 = pos->y - off;
    y1 = off + pos->y;
    if (x0 < 0)
        x0 = 0;
    else if (x0 > 480)
        x0 = 480;
    if (x1 < 0)
        x1 = 0;
    else if (x1 > 480)
        x1 = 480;
    if (y0 < 0)
        y0 = 0;
    else if (y0 > 272)
        y0 = 272;
    if (y1 < 0)
        y1 = 0;
    else if (y1 > 272)
        y1 = 272;
    pts = (STVert *)f_021b38(count * 10);
    n = 0;
    d = pts;
    for (y = y0; y < y1; y += step) {
        for (x = x0; x < x1; x += step) {
            d->u = x;
            d->v = y;
            d->x = 0;
            d->y = 0;
            d->z = 0;
            d++;
            n++;
        }
    }
    if (n > 0) {
        *p++ = 0x12800102;
        *p++ = 0x10000000 | ((((unsigned int)pts >> 24) & 0xf) << 16);
        for (i = 0; i < 128; i += count) {
            *p++ = 0x01000000 | ((unsigned int)pts & 0xffffff);
            *p++ = 0x04000000 | count;
        }
    }
    *p++ = 0xc2000001;
    *p++ = 0xc3000003;
    *p++ = 0xc7000000;
    *p++ = 0xa0000000 | ((unsigned int)tex & 0xffffff);
    *p++ = 0xa8000200 | ((((unsigned int)tex >> 24) & 0xf) << 16);
    *p++ = 0xb8000000;
    *p++ = 0xd2000000 | D_23c1c0;
    {
        unsigned int dst = f_021d38();

        *p++ = 0x9c000000 | (dst & 0xffffff);
        *p++ = 0x9d000200 | ((dst >> 24) << 16);
    }
    *p++ = 0x24000000;
    *p++ = 0xe8000000;
    *p++ = 0x23000001;
    *p++ = 0xc9000100;
    *p++ = 0xe7000000;
    *p++ = 0x20000001;
    *p++ = 0xcc000000;
    return p;
}
