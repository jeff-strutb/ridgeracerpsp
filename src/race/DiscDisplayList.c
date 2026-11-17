/* The disc display list commands (retail 0x0e7114 to 0x0e71f0): the scale word D_27e88c that
   sizes the disc, the six-word block that sets the disc's viewport scale and its texture and
   vertex base commands, and the one-word command that follows it. The vertex table and the
   command buffer they point at are built by the next object file (DiscVertexTable.cpp). */

extern float D_27e88c;          /* the disc scale, set by f_0e71e4 */
extern char D_27e990[];         /* the 72-word command buffer the disc is drawn from */

static inline unsigned int FloatBits(float f)
{
    union {
        float f;
        unsigned int u;
    } v;
    v.f = f;
    return v.u;
}

/* @draft 0x0e7114 us f_0e7114
   WHAT IT DOES: Writes a six-word block for the disc when the scale is above 0.01: the
   viewport commands 0x3a000000 and 0x3a000004 with two 0x3b float commands (the scale times
   37 over 100, doubled, and that times 0.5667), then the base and texture address commands of
   the command buffer. Returns the next command slot, or the same slot when the disc is too
   small to draw.
   Remaining difference (24 words, cycle 2026-11-16): entry-block order only. sched1 (lreg dump)
   issues the D_27e88c load and 0.01 compare (insns 29, 31, 35) first, ahead of the a/base chain
   (158 high, 14 lo_sum, 16 sra ...); retail issues the a/base chain first and the compare late
   (c.le.s at +0x34), then the tail differs only in f2/f3 and v0/v1. No source lever named yet for
   the sched1 priority; no change made. */
unsigned int *f_0e7114(unsigned int *p)
{
    unsigned int c4 = 0x3a000004;
    unsigned int *q = p;
    int a = (int)D_27e990;
    unsigned int base = 0x10000000 | ((a >> 24) & 0xf) << 16;
    unsigned int tex = (a & 0x00ffffff) | 0x0a000000;
    float f0;
    float f2;

    if (D_27e88c <= 0.01f)
        return q;
    p[0] = 0x3a000000;
    p[4] = base;
    f0 = D_27e88c * 37.0f;
    p[2] = c4;
    f0 = f0 / 100.0f;
    p[5] = tex;
    f0 = f0 + f0;
    f2 = f0 * 0.56666666f;
    p[1] = 0x3b000000 | (FloatBits(f2) >> 8);
    p[3] = 0x3b000000 | (FloatBits(f0) >> 8);
    q = p + 6;
    return q;
}

/* @implements 0x0e71d4 us f_0e71d4
   WHAT IT DOES: Writes the command 0x24000000 at the slot and returns the slot after it. */
unsigned int *f_0e71d4(unsigned int *p)
{
    *p = 0x24000000;
    return p + 1;
}

/* @implements 0x0e71e4 us f_0e71e4
   WHAT IT DOES: Sets the disc scale D_27e88c to the float argument. */
void f_0e71e4(float s)
{
    D_27e88c = s;
}
