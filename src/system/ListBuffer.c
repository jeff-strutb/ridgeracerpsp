/* The list buffer object file (retail 0x022bc0 to 0x022c30), plain C: the alignment of list
   chunks, and the switch to the other display list buffer at the start of a frame. */

/* The two display list buffers, the size of each, which one is being filled, the open chunk,
   and the low end of the frame's data taken from the back (owned by the graphics system). */
extern void *D_23c1a8[2];
extern unsigned int D_23c1b0;
extern int D_23c1b4;
extern unsigned int *D_23c1b8;
extern char *D_23c1bc;

/* @implements 0x022bc0 us f_022bc0
   WHAT IT DOES: returns where a chunk starting at or after the given address puts its link
   word, so that the commands after the link are 64 byte aligned. */
unsigned int *f_022bc0(void *p)
{
    return (unsigned int *)((((unsigned int)p + 67) >> 6 << 6) - 4);
}

/* @implements 0x022bd4 us f_022bd4
   WHAT IT DOES: switches to the other display list buffer: its back end becomes the low end of
   the frame's data, and its first chunk becomes the open chunk. */
void f_022bd4(void)
{
    int i = D_23c1b4 ^ 1;
    char *buf = D_23c1a8[i];

    D_23c1bc = buf + D_23c1b0;
    D_23c1b4 = i;
    D_23c1b8 = f_022bc0(buf);
}
