/* The screen fade object file (retail 0x100ba4 to 0x100ef8): a full screen overlay drawn from
   the frame just shown, its centre in one colour and its edges in another, as a fan of
   triangles from the screen centre to the corners, one 64 pixel wide column of the screen at
   a time. */

unsigned char *f_021b38(unsigned int size);
void *f_021de8(void);

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* The fan's vertex layout: 16 bit texture coordinates, a colour and a 16 bit position. */
struct FadeVert {
    unsigned short u, v;
    unsigned int color;
    short x, y, z;
};

/* The texture inset of the screen's edges, the fade level (the edges' alpha; nothing is drawn
   at zero or below), the centre's alpha and the grey level of both colours. */
extern int D_1d5e20;
extern int D_27f150;
extern int D_27f154;
extern int D_27f158;

/* @implements 0x100ba4 us f_100ba4
   WHAT IT DOES: Resets the fade: an inset of one texel and the fade level at zero (off). */
void f_100ba4(void)
{
    D_1d5e20 = 1;
    D_27f150 = 0;
}

/* @implements 0x100bbc us f_100bbc
   WHAT IT DOES: Nothing (an empty step). */
void f_100bbc(void)
{
}

/* @implements 0x100bc4 us f_100bc4
   WHAT IT DOES: When the fade level is above zero, writes the commands that draw the frame
   just shown back over the screen as a triangle fan: the centre vertex in the grey level with
   the smaller of the centre alpha and the fade level, the four corners in the grey level with
   the fade level as alpha, their texture coordinates pulled in by the inset. Returns the end
   of the commands. */
unsigned int *f_100bc4(unsigned int *p)
{
    FadeVert *v;
    FadeVert *q;
    unsigned int centre, edge;
    int i;

    if (D_27f150 <= 0)
        return p;
    *p++ = 0x22000000;
    *p++ = 0x24000000;
    *p++ = 0x23000000;
    *p++ = 0x1d000000;
    *p++ = 0x1f000000;
    *p++ = 0x17000000;
    *p++ = 0x1e000001;
    *p++ = 0x20000001;
    *p++ = 0xc6000101;
    *p++ = 0x21000001;
    *p++ = 0xc9000004;
    *p++ = 0xdf000032;
    *p++ = 0xc2000000;
    *p++ = 0xc3000001;
    {
        unsigned int src = (unsigned int)f_021de8();

        *p++ = 0xa0000000 | (src & 0xffffff);
        *p++ = 0xa8000200 | (((src >> 24) & 0xf) << 16);
    }
    *p++ = 0xb8000909;
    *p++ = 0xcb000000;
    *p++ = 0x1280011e;
    v = (FadeVert *)f_021b38(96);
    edge = D_27f150 << 24 | D_27f158 << 16 | D_27f158 << 8 | D_27f158;
    centre = MIN(D_27f150, D_27f154) << 24 | D_27f158 << 16 | D_27f158 << 8 | D_27f158;
    q = &v[0];
    q->x = 240;
    q->y = 136;
    q->u = 240;
    q->v = 136;
    q->color = centre;
    q = &v[1];
    q->x = 0;
    q->y = 0;
    q->u = D_1d5e20;
    q->v = D_1d5e20;
    q->color = edge;
    q = &v[2];
    q->x = 480;
    q->y = 0;
    q->u = 480 - D_1d5e20;
    q->v = D_1d5e20;
    q->color = edge;
    q = &v[3];
    q->x = 480;
    q->y = 272;
    q->u = 480 - D_1d5e20;
    q->v = 272 - D_1d5e20;
    q->color = edge;
    q = &v[4];
    q->x = 0;
    q->y = 272;
    q->u = D_1d5e20;
    q->v = 272 - D_1d5e20;
    q->color = edge;
    q = &v[5];
    q->x = 0;
    q->y = 0;
    q->u = D_1d5e20;
    q->v = D_1d5e20;
    q->color = edge;
    *p++ = 0x10000000 | ((((unsigned int)v >> 24) & 0xf) << 16);
    for (i = 0; i < 8; i++) {
        int x0 = i << 6;
        int x1 = MIN(x0 + 64, 480);

        *p++ = 0xd4000000 | x0;
        *p++ = 0xd5043c00 | (x1 - 1);
        *p++ = 0x01000000 | ((unsigned int)v & 0xffffff);
        *p++ = 0x04050006;
    }
    *p++ = 0xd4000000;
    *p++ = 0xd5043ddf;
    *p++ = 0xc9000100;
    *p++ = 0x22000001;
    return p;
}

/* @implements 0x100ef0 us f_100ef0
   WHAT IT DOES: Nothing (an empty step). */
void f_100ef0(void)
{
}
