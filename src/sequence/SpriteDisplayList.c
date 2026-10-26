/* The 2D sprite display list writers (retail 0x0e79b0 to 0x0e7a54). The list cursor is the
   global D_27ebcc: a pointer to the next free display list word. The writers append a
   colour command (with the colour kept in D_27ebc8), a texture-enable command and the sprite
   sizes (kept in D_27ebc0 and D_27ebc4) that the sprite emitters of 0x0e7a54 and 0x0e7bc8 use.
   Used by the Rally-X mini game's score, lives and fuel drawing. */

extern unsigned int *D_27ebcc;  /* the display list cursor */
extern unsigned int D_27ebc8;   /* the last colour written */
extern int D_27ebc0;            /* sprite width */
extern int D_27ebc4;            /* sprite height */

/* @implements 0x0e79b0 us f_0e79b0
   WHAT IT DOES: Sets the display list cursor to the given list position. */
void f_0e79b0(unsigned int *list)
{
    D_27ebcc = list;
}

/* @implements 0x0e79bc us f_0e79bc
   WHAT IT DOES: Returns the display list cursor. */
unsigned int *f_0e79bc(void)
{
    return D_27ebcc;
}

/* @implements 0x0e79c8 us f_0e79c8
   WHAT IT DOES: Appends the colour command for an RGBA colour: its low 24 bits with the
   colour command tag, then the alpha byte with the following command tag. The colour is
   kept in D_27ebc8 and the cursor advances by two words. */
void f_0e79c8(unsigned int color)
{
    unsigned int *q = D_27ebcc;

    D_27ebc8 = color;
    q[0] = (color & 0xffffff) | 0x55000000;
    q++;
    D_27ebcc = q + 1;
    *q = (color >> 24) | 0x58000000;
}

/* @draft 0x0e7a10 us f_0e7a10
   WHAT IT DOES: Appends one word of the texture-enable command: the flag (1 when on, 0
   when off) is or-ed into the command tag 0x1e000000. The cursor advances by one word. */
void f_0e7a10(int on)
{
    unsigned int *q;

    if (on) {
        q = D_27ebcc;
        *q = 0x1e000001;
        q++;
    } else {
        q = D_27ebcc;
        *q = 0x1e000000;
        q++;
    }
    D_27ebcc = q;
}

/* @implements 0x0e7a40 us f_0e7a40
   WHAT IT DOES: Stores the sprite width and height that the sprite emitters use. */
void f_0e7a40(int w, int h)
{
    D_27ebc0 = w;
    D_27ebc4 = h;
}
