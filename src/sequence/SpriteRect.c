/* The 2D sprite rectangle emitter and the sprite counter (retail 0x0e7bc8 to 0x0e7c4c). A
   rectangle is two display list words, appended through the list cursor D_27ebcc: the
   corner at (x + 96, y + 10) and the opposite corner at (x + w + 96, y + h + 10), each packed
   as 10-bit fields above the position with a command tag. The counter D_27ebd0 cycles
   through 0 to 31; the test reports whether it has reached 16. */

extern unsigned int *D_27ebcc;  /* the display list cursor */
extern int D_27ebd0;            /* the sprite counter */

/* @implements 0x0e7bc8 us f_0e7bc8
   WHAT IT DOES: Appends the two display list words of a rectangle at (x, y) of size w by h:
   the first corner at (x + 96, y + 10), then the opposite corner, each with its command tag
   (0xd4000000 and 0xd5000000). The cursor advances by two words. */
void f_0e7bc8(int x, int y, int w, int h)
{
    unsigned int *q = D_27ebcc;

    q[0] = ((x + 96) | ((y + 10) << 10)) | 0xd4000000;
    q++;
    D_27ebcc = q + 1;
    *q = ((x + w + 96) | ((y + h + 10) << 10)) | 0xd5000000;
}

/* @implements 0x0e7c20 us f_0e7c20
   WHAT IT DOES: Steps the sprite counter on one (modulo 32) and returns the new value. */
int f_0e7c20(void)
{
    D_27ebd0 = (D_27ebd0 + 1) & 0x1f;
    return D_27ebd0;
}

/* @implements 0x0e7c38 us f_0e7c38
   WHAT IT DOES: Returns 1 when the sprite counter is 16 or more, 0 when it is below 16. */
int f_0e7c38(void)
{
    return !(D_27ebd0 < 16);
}
