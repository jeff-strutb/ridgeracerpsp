/* The palette ramp writer (retail 0x0cb3f4 to 0x0cb688, the object file after the model tint):
   writes the commands that draw a row of coloured line segments into a texture's palette
   (256 entries wide), used by the SWG player (src/system/SwgPlayer.cpp) for animated palette
   colours. */

extern "C" {
void *sceGeEdramGetAddr(void);
}

unsigned char *f_021b38(unsigned int size);
unsigned int f_021d38(void);

/* The pixel format (owned by the graphics system). */
extern int D_23c1c0;

/* A point of the ramp: where its segment ends, its colour up to the limit and past it. The
   list ends with an end of -1. */
struct RampPoint {
    int x;
    unsigned int c0;
    unsigned int c1;
};

/* A texture as the writer reads it: its palette's address at +228. */
struct RampTex {
    char m0[228];
    unsigned int clut;
};

/* A line vertex as written into the list buffer: 32 bit colour, 16 bit screen position. */
struct RampVert {
    unsigned int color;
    short x, y, z;
    short pad;
};

/* @implements 0x0cb3f4 us f_0cb3f4
   The vertices are written as v[nv] and v[nv + 1]: loop.c strength-reduces that address into
   its own pointer, whose initial copy of the buffer it places in the preheader after the
   hoisted invariants, as retail does. A separate cursor (w = v; w += 2) puts the copy right
   after the call instead.
   WHAT IT DOES: Writes, at p, the commands that draw the ramp into texture t's palette: no
   depth writes, no blending, no texturing, 32 bit pixels into the palette as a 256 wide
   target; then one line per point from the previous end to its own, in its first colour,
   clipped at the limit, and from the limit on every remaining point's line in its second
   colour; then the screen target back, depth writes, blending and texturing on again.
   Returns the advanced list pointer. */
extern "C" unsigned int *f_0cb3f4(const RampPoint *pts, int limit, const RampTex *t, unsigned int *p)
{
    unsigned int fb = t->clut;
    fb -= (unsigned int)sceGeEdramGetAddr();
    *p++ = 0xe7000001;
    *p++ = 0x21000000;
    *p++ = 0x1e000000;
    *p++ = 0xd2000003;
    *p++ = (fb & 0xffffff) | 0x9c000000;
    *p++ = ((fb >> 24) << 16) | 0x9d000100;

    int n = 0;
    while (pts[n].x != -1)
        n++;
    RampVert *v = (RampVert *)f_021b38((n + 1) * 2 * sizeof(RampVert));
    int done = 0;
    int nv = 0;
    int x = 0;
    for (int i = 0; i < n; i++) {
        if (!done) {
            v[nv].color = pts[i].c0;
            v[nv].x = x;
            v[nv].y = 0;
            v[nv].z = 0;
            v[nv + 1].color = pts[i].c0;
            if (pts[i].x > limit) {
                x = limit;
                done = 1;
            } else
                x = pts[i].x;
            v[nv + 1].x = x;
            v[nv + 1].y = 0;
            v[nv + 1].z = 0;
            nv += 2;
        }
        if (done == 1) {
            v[nv].color = pts[i].c1;
            v[nv].x = x;
            v[nv].y = 0;
            v[nv].z = 0;
            v[nv + 1].color = pts[i].c1;
            x = pts[i].x;
            v[nv + 1].x = x;
            v[nv + 1].y = 0;
            v[nv + 1].z = 0;
            nv += 2;
        }
    }

    *p++ = 0x1280011c;
    *p++ = (((unsigned int)v >> 24) & 0xf) << 16 | 0x10000000;
    *p++ = ((unsigned int)v & 0xffffff) | 0x01000000;
    *p++ = nv | 0x04010000;
    *p++ = D_23c1c0 | 0xd2000000;
    unsigned int r = f_021d38();
    *p++ = (r & 0xffffff) | 0x9c000000;
    *p++ = ((r >> 24) << 16) | 0x9d000200;
    *p++ = 0xe7000000;
    *p++ = 0x21000001;
    *p++ = 0x1e000001;
    *p++ = 0xcc000000;
    return p;
}
