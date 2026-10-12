/* The debug print and dither object file (retail 0x02db68 to 0x02dfb4). The debug text print
   is compiled out in retail (an empty function). A frame counter and two flags choose the
   GE dither matrix written into display lists: a fixed matrix, or one of two matrices
   alternating every frame so the dither pattern averages out over time. */

extern int D_240050;
extern int D_240054;
extern int D_240058;

/* @implements 0x02db68 us f_02db68
   WHAT IT DOES: Prints formatted debug text at a screen position in a colour. Compiled out in
   retail: it does nothing. */
void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...)
{
}

/* @implements 0x02db7c us f_02db7c
   WHAT IT DOES: Sets the flag that selects the second pair of frame alternating dither matrices. */
void f_02db7c(int on)
{
    D_240054 = on;
}

/* @implements 0x02db88 us f_02db88
   WHAT IT DOES: Sets the flag that forces the fixed dither matrix. */
void f_02db88(int on)
{
    D_240058 = on;
}

/* @implements 0x02db94 us f_02db94
   WHAT IT DOES: Counts one frame (the counter's low bit picks the dither matrix). */
void f_02db94(void)
{
    D_240050++;
}

/* Writes the four GE dither matrix commands (DTH0 to DTH3), one row each, and returns the new
   end of the list. */
static __inline__ unsigned int *Dither(unsigned int *p, int r0, int r1, int r2, int r3)
{
    p[0] = 0xe2000000 | r0;
    p[1] = 0xe3000000 | r1;
    p[2] = 0xe4000000 | r2;
    p[3] = 0xe5000000 | r3;
    return p + 4;
}

/* @implements 0x02dba8 us f_02dba8
   WHAT IT DOES: Writes the dither matrix for this frame into the display list and returns the
   new end of the list: the fixed matrix when forced, otherwise one of two pairs of matrices,
   alternating with the frame counter. */
unsigned int *f_02dba8(unsigned int *p)
{
    if (D_240058)
        return Dither(p, 0x5140, 0x3726, 0x4051, 0x2637);
    if (!D_240054) {
        if (D_240050 & 1)
            return Dither(p, 0x0e0e, 0xe0e0, 0x0e0e, 0xe0e0);
        return Dither(p, 0xc1c1, 0x1c1c, 0xc1c1, 0x1c1c);
    }
    if (D_240050 & 1)
        return Dither(p, 0x4242, 0x2424, 0x4242, 0x2424);
    return Dither(p, 0x0505, 0x5050, 0x0505, 0x5050);
}

/* @implements 0x02dcc8 us f_02dcc8
   WHAT IT DOES: Like f_02dba8, with a second set of dither matrices. */
unsigned int *f_02dcc8(unsigned int *p)
{
    if (D_240058)
        return Dither(p, 0xbfc0, 0xd9ea, 0xc0bf, 0xead9);
    if (!D_240054) {
        if (D_240050 & 1)
            return Dither(p, 0x0202, 0x2020, 0x0202, 0x2020);
        return Dither(p, 0x4f4f, 0xf4f4, 0x4f4f, 0xf4f4);
    }
    if (D_240050 & 1)
        return Dither(p, 0xcece, 0xecec, 0xcece, 0xecec);
    return Dither(p, 0x0b0b, 0xb0b0, 0x0b0b, 0xb0b0);
}

/* @implements 0x02dde8 us f_02dde8
   WHAT IT DOES: The same as f_02dba8 (a separate copy used by the course drawing). */
unsigned int *f_02dde8(unsigned int *p)
{
    if (D_240058)
        return Dither(p, 0x5140, 0x3726, 0x4051, 0x2637);
    if (!D_240054) {
        if (D_240050 & 1)
            return Dither(p, 0x0e0e, 0xe0e0, 0x0e0e, 0xe0e0);
        return Dither(p, 0xc1c1, 0x1c1c, 0xc1c1, 0x1c1c);
    }
    if (D_240050 & 1)
        return Dither(p, 0x4242, 0x2424, 0x4242, 0x2424);
    return Dither(p, 0x0505, 0x5050, 0x0505, 0x5050);
}

/* @implements 0x02df08 us f_02df08
   WHAT IT DOES: Writes the fixed dither matrix when forced, otherwise one of the two matrices
   alternating with the frame counter (the pair f_02dba8 uses when its first flag is set).
   Returns the new end of the list. */
unsigned int *f_02df08(unsigned int *p)
{
    if (D_240058)
        return Dither(p, 0x5140, 0x3726, 0x4051, 0x2637);
    if (D_240050 & 1)
        return Dither(p, 0x4242, 0x2424, 0x4242, 0x2424);
    return Dither(p, 0x0505, 0x5050, 0x0505, 0x5050);
}
