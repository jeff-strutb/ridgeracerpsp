/* The sun flare object file (retail 0x0ffb1c to 0x100ba4). At race start it records where the
   sun texture sits in video memory and places the sun far along the course's sun direction.
   Each frame it projects the sun onto the screen and, when it is on screen, draws the sun
   sprite and the commands that sample how much of it is hidden behind scenery. */

extern "C" {
void *sceGeEdramGetAddr(void);
}

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

extern "C" Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);

struct CInfo {
    char p0[228];
    int vram;
};

unsigned char *f_021b38(unsigned int size);
void *f_021d5c(void);
unsigned int f_021d38(void);
void f_021720(void);
void f_021750(void);
CInfo *f_023158(int id);
CInfo *f_02347c(unsigned int id);
extern "C" unsigned int *f_0249a0(CInfo *info, unsigned int *p);

/* The vertex layouts written into the list buffer, packed: 16 bit screen coordinates, and the
   same with 16 bit texture coordinates first. */
struct SVert {
    unsigned short x, y, z;
} __attribute__((packed));

struct STVert {
    unsigned short u, v;
    unsigned short x, y, z;
} __attribute__((packed));

/* A screen position. */
struct Pos16 { unsigned short x, y, z; };

/* The camera (its position first). */
struct Camera {
    float x, y, z;
};
int f_0cbfe4(Camera *cam, short *sx, short *sy, float *depth, Vec4 *pos);
unsigned int *f_10039c(const Pos16 *pos, unsigned int fb, int mode, unsigned int *p);

/* The course lighting set up: the sun's direction, whether the course has a sun, and its
   colour, alpha and size. */
struct LightSetup {
    char p0[400];
    Vec4 sunDir;
    bool sun;
    unsigned char rgb[3];
    unsigned char alpha;
    int width;
    int height;
};
struct MapMgr {
    char p0[12512];
    LightSetup light;
};
extern MapMgr D_23c820;

/* The sun sprite's colour, alpha, half sizes and texture address. */
extern unsigned int D_1d5e10;
extern unsigned char D_1d5e14;
extern unsigned short D_1d5e16;
extern unsigned short D_1d5e18;
extern char *D_1d5e1c;

/* The sun texture's address in video memory and its offset from the start of it, its
   record, the sun's position, and the sampling target's address. */
extern int D_27f120;
extern int D_27f124;
extern CInfo *D_27f128;
extern Vec4 D_27f130;
extern unsigned int D_27f140;
extern SVert D_27f144;

/* Sets the sun sprite's colour, alpha and size; its texture sits near the top of video
   memory. */
static __inline__ void SetSprite(unsigned int color, int alpha, int w, int h)
{
    D_1d5e10 = color;
    D_1d5e14 = alpha;
    D_1d5e16 = w;
    D_1d5e18 = h;
    D_1d5e1c = (char *)0x1fc000;
}

static __inline__ void Copy(Vec4 *d, const Vec4 *s)
{
    *d = *s;
}

/* @draft 0x0ffb1c us f_0ffb1c
   WHAT IT DOES: Sets the sun up for a race: runs the sun texture's lists into a recorded call
   list and keeps its video memory address (and its offset from the start of video memory)
   and its record, puts the sun a million units along the course's sun direction, and copies
   the course's sun colour, alpha and size into the sprite settings, with the sampling target
   near the top of video memory.
   Remaining difference (15 words, scheduling only): retail shifts the colour's two high bytes
   before loading the alpha byte, and its colour bytes land in v0, v1, a0 (here a0, v0, v1);
   the stores and every other instruction agree. */
void f_0ffb1c(void)
{
    MapMgr *mm;
    LightSetup *l;

    f_021720();
    D_27f120 = f_023158(0x0a000005)->vram;
    D_27f124 = D_27f120 - (int)sceGeEdramGetAddr();
    f_021750();
    mm = &D_23c820;
    D_27f128 = f_02347c(0x0a000005);
    Copy(&D_27f130, &mm->light.sunDir);
    f_027e6c(&D_27f130, &D_27f130, 1000000.0f);
    l = &mm->light;
    SetSprite(l->rgb[2] << 16 | l->rgb[1] << 8 | l->rgb[0], l->alpha, l->width, l->height);
    D_27f140 = (unsigned int)sceGeEdramGetAddr() + (unsigned int)D_1d5e1c;
}

/* @implements 0x0ffc40 us f_0ffc40
   WHAT IT DOES: Nothing (an empty per frame step). */
void f_0ffc40(void)
{
}

/* Writes one sprite corner: texture coordinates and screen position. */
#define VERT(q, U, V, X, Y) ((q)->u = (U), (q)->v = (V), (q)->x = (X), (q)->y = (Y), (q)->z = 0)

/* @implements 0x0ffc48 us f_0ffc48
   WHAT IT DOES: Draws the sun when the course has one: projects the sun's position (relative
   to the camera's ground position) onto the screen and, when it lands on the screen, writes
   the commands that measure how much of it is visible into the sun texture, then draws the
   sun as sixteen sprites from that texture around its screen position, one 64 pixel wide
   column of the screen at a time (eight scissor columns). Returns the end of the commands. */
unsigned int *f_0ffc48(Camera *cam, unsigned int *p)
{
    Vec4 v;
    Pos16 pos;
    float depth;
    STVert *t;
    STVert *q;
    unsigned short i;

    if (!D_23c820.light.sun)
        return p;
    v.y = D_27f130.y;
    v.x = cam->x + D_27f130.x;
    v.z = cam->z + D_27f130.z;
    if (!f_0cbfe4(cam, (short *)&pos.x, (short *)&pos.y, &depth, &v))
        return p;
    {
        short x = pos.x, y = pos.y;

        pos.z = 0;
        if (x < 0 || x > 480 || y < 0 || y > 272)
            return p;
        p = f_10039c(&pos, D_27f124, 2, p);
        p = f_0249a0(D_27f128, p);
        *p++ = 0xcb000000;
        *p++ = 0x1e000001;
        *p++ = 0x23000000;
        *p++ = 0x1f000000;
        *p++ = 0xe7000001;
        *p++ = 0x22000000;
        *p++ = 0x21000001;
        *p++ = 0xdf0000a6;
        *p++ = 0xe1ffffff;
        *p++ = 0xc6000101;
        *p++ = 0xc9000100;
        *p++ = 0xc7000101;
        *p++ = 0x55000000 | D_1d5e10;
        *p++ = 0x58000000 | D_1d5e14;
        t = (STVert *)f_021b38(160);
        q = &t[0];
        VERT(q, 63, 255, x, y);
        q = &t[1];
        VERT(q, 1, 129, x - D_1d5e16 / 2, y - D_1d5e18);
        q = &t[2];
        VERT(q, 1, 255, x - D_1d5e16 / 2, y);
        q = &t[3];
        VERT(q, 63, 129, x, y + D_1d5e18);
        q = &t[4];
        VERT(q, 63, 129, x, y - D_1d5e18);
        q = &t[5];
        VERT(q, 1, 255, x + D_1d5e16 / 2, y);
        q = &t[6];
        VERT(q, 63, 255, x, y);
        q = &t[7];
        VERT(q, 1, 129, x + D_1d5e16 / 2, y + D_1d5e18);
        q = &t[8];
        VERT(q, 63, 127, x - D_1d5e16 / 2, y);
        q = &t[9];
        VERT(q, 1, 1, x - D_1d5e16, y - D_1d5e18);
        q = &t[10];
        VERT(q, 1, 127, x - D_1d5e16, y);
        q = &t[11];
        VERT(q, 63, 1, x - D_1d5e16 / 2, y + D_1d5e18);
        q = &t[12];
        VERT(q, 63, 1, x + D_1d5e16 / 2, y - D_1d5e18);
        q = &t[13];
        VERT(q, 1, 127, x + D_1d5e16, y);
        q = &t[14];
        VERT(q, 63, 127, x + D_1d5e16 / 2, y);
        q = &t[15];
        VERT(q, 1, 1, x + D_1d5e16, y + D_1d5e18);
        *p++ = 0x12800102;
        *p++ = 0x10000000 | ((((unsigned int)t >> 24) & 0xf) << 16);
        for (i = 0; i < 8; i++) {
            *p++ = 0xd4000000 | (i << 6);
            *p++ = 0xd5043c00 | ((i << 6) + 63);
            *p++ = 0x01000000 | ((unsigned int)t & 0xffffff);
            *p++ = 0x04060010;
        }
        *p++ = 0xd4000000;
        *p++ = 0xd5043ddf;
        *p++ = 0x23000001;
        *p++ = 0x22000001;
        *p++ = 0xdf000032;
        *p++ = 0xe7000000;
    }
    return p;
}

/* @implements 0x100390 us f_100390
   WHAT IT DOES: Forgets the sun texture's record. */
void f_100390(void)
{
    D_27f128 = 0;
}

/* @implements 0x10039c us f_10039c
   WHAT IT DOES: Writes the commands that measure how much of the sun is visible: the sun
   marker is drawn over a small square around its screen position with a stencil test against
   the scene's depth, then the square is sampled into one pixel of the sampling target with
   additive blending, and that pixel is copied into the given target (fb, the sun texture).
   The mode picks the size of the square and the sampling step (4 by 4, 8 by 8, or 16 by 16
   sampled every other pixel). Returns the end of the commands. */
unsigned int *f_10039c(const Pos16 *pos, unsigned int fb, int mode, unsigned int *p)
{
    int count = 0;
    short off = 0;
    int step = 0;
    SVert *marker;
    STVert *pts;
    STVert *d;
    STVert *line;
    STVert *q;
    short x0, x1, y0, y1, x, y;
    short n;
    unsigned int tex;

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
    *p++ = 0x21000000;
    *p++ = 0x20000000;
    *p++ = 0x22000000;
    *p++ = 0xe7000001;
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
    *p++ = 0xc3000001;
    {
        unsigned int src = (unsigned int)f_021d5c();

        *p++ = 0xa0000000 | (src & 0xffffff);
        *p++ = 0xa8000200 | (((src >> 24) & 0xf) << 16);
    }
    *p++ = 0xb8000909;
    *p++ = 0xd2000003;
    *p++ = 0x9c000000 | ((unsigned int)D_1d5e1c & 0xffffff);
    *p++ = 0x9d000040 | (((unsigned int)D_1d5e1c >> 24) << 16);
    *p++ = 0xcb000000;
    *p++ = 0xe8000000;
    *p++ = 0x55ffffff;
    *p++ = 0x58000000;
    *p++ = 0xd3000301;
    *p++ = 0x12800100;
    *p++ = 0x10000000 | ((((unsigned int)&D_27f144 >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)&D_27f144 & 0xffffff);
    *p++ = 0x04000001;
    *p++ = 0xd3000000;
    *p++ = 0x23000000;
    *p++ = 0x22000001;
    *p++ = 0x21000001;
    *p++ = 0xdd040404;
    *p++ = 0xdbffff02;
    *p++ = 0x1e000001;
    *p++ = 0xc9000103;
    *p++ = 0xc6000000;
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
        *p++ = 0x01000000 | ((unsigned int)pts & 0xffffff);
        *p++ = 0x04000000 | count;
    }
    tex = D_27f140;
    *p++ = 0xcc000000;
    *p++ = 0xc2000000;
    *p++ = 0xc3000003;
    *p++ = 0xc7000000;
    *p++ = 0xa0000000 | (tex & 0xffffff);
    *p++ = 0xa8000200 | (((tex >> 24) & 0xf) << 16);
    *p++ = 0xb8000009;
    *p++ = 0x9c000000 | (fb & 0xffffff);
    *p++ = 0x9d000100 | ((fb >> 24) << 16);
    *p++ = 0x24000000;
    *p++ = 0x22000000;
    *p++ = 0xe8000000;
    *p++ = 0x21000001;
    *p++ = 0xdf0000a6;
    *p++ = 0xe1000000;
    q = (STVert *)f_021b38(20);
    line = q;
    q->u = 0;
    q->v = 0;
    q->x = 0;
    q->y = 0;
    q->z = 0;
    q++;
    q->u = 1;
    q->v = 1;
    q->x = 256;
    q->y = 1;
    q->z = 0;
    *p++ = 0x12800102;
    *p++ = 0x10000000 | ((((unsigned int)line >> 24) & 0xf) << 16);
    *p++ = 0x01000000 | ((unsigned int)line & 0xffffff);
    *p++ = 0x04060002;
    *p++ = 0xd2000001;
    {
        unsigned int dst = f_021d38();

        *p++ = 0x9c000000 | (dst & 0xffffff);
        *p++ = 0x9d000200 | ((dst >> 24) << 16);
    }
    *p++ = 0x23000001;
    *p++ = 0x22000001;
    *p++ = 0x22000001;
    *p++ = 0xc9000100;
    *p++ = 0xe7000000;
    *p++ = 0x20000001;
    *p++ = 0xc9000100;
    *p++ = 0x22000001;
    *p++ = 0xdbff0006;
    *p++ = 0xcc000000;
    return p;
}
