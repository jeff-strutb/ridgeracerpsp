/* A small object file (retail 0x022b78 to 0x022bc0): opening and finishing a direct display
   list outside the frame's own list buffers. */

extern "C" {
void f_115f8c(int cid, void *list, int size);
void f_116258(void);
}

/* The two display list buffers and the size of each (owned by the graphics system). */
extern void *D_23c1a8[2];
extern unsigned int D_23c1b0;

/* @implements 0x022b78 us f_022b78
   WHAT IT DOES: opens a direct display list. It passes the address of the table of the two
   list buffers, not a buffer itself, as the list memory. */
void f_022b78(void)
{
    f_115f8c(0, D_23c1a8, D_23c1b0);
}

/* @implements 0x022ba4 us f_022ba4
   WHAT IT DOES: finishes the display list being built. */
void f_022ba4(void)
{
    f_116258();
}
