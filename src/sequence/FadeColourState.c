/* The screen fade's colour state (retail 0x0e9dc0 to 0x0e9ebc): a reset of the fade flag, the
   start-of-fade setup that marks the fade on, and the copy of the map light's fade colour into
   the fade's packed colour words. The fade step in FadeSequence.cpp and the GE list builder in
   FadeDisplayList.cpp read these words. */

extern int D_27ebd4;            /* the fade flag cleared by the reset */
extern int D_1d5a80;            /* fade on (1) and the first fade channel */
extern int D_1d5a8c;            /* the fade's second channel, from the caller */
extern int D_27ec78;            /* the packed fade colour */
extern int D_27ec7c;            /* the fade colour's third channel */
extern int D_27ec80;            /* the fade colour's fourth channel */
extern unsigned char D_23c820[]; /* the map (MapMgr); its light starts at 12512 */

static inline int Is(int x, int k)
{
    return x == k;
}

/* @implements 0x0e9dc0 us f_0e9dc0
   WHAT IT DOES: Clears the fade flag when called with a == 1 and b == 0xffff. Its caller
   passes those two values for the reset. */
void f_0e9dc0(int a, int b)
{
    if (Is(b, 0xffff) & Is(a, 1))
        D_27ebd4 = 0;
}

/* @implements 0x0e9de8 us f_0e9de8
   WHAT IT DOES: The reset of the fade flag, with the two values the reset checks. */
void f_0e9de8(void)
{
    f_0e9dc0(1, 0xffff);
}

/* @implements 0x0e9e08 us f_0e9e08
   WHAT IT DOES: Marks the fade on (D_1d5a80 = 1) and clears the two packed colour words that
   follow the fade colour. */
void f_0e9e08(void)
{
    D_1d5a80 = 1;
    D_27ec78 = 0;
    D_27ec7c = 0;
}

/* @implements 0x0e9e28 us f_0e9e28
   WHAT IT DOES: The same start-of-fade setup as f_0e9e08: fade on, and the two colour words
   cleared. It is a second copy of that routine in retail. */
void f_0e9e28(void)
{
    D_1d5a80 = 1;
    D_27ec78 = 0;
    D_27ec7c = 0;
}

/* @implements 0x0e9e48 us f_0e9e48
   WHAT IT DOES: An empty hook that does nothing. */
void f_0e9e48(void)
{
}

/* @implements 0x0e9e50 us f_0e9e50
   WHAT IT DOES: An empty hook that does nothing. */
void f_0e9e50(void)
{
}

/* @implements 0x0e9e58 us f_0e9e58
   WHAT IT DOES: Copies the map light's three fade bytes into the fade state. The first byte
   (offset 432) goes to D_1d5a80; the second (433) is spread into a packed opaque colour
   (0xff000000 plus the byte in each of the three colour channels) that goes to D_27ec78, and
   also to D_27ec80; the third (434) goes to D_27ec7c. The argument is stored in D_1d5a8c. */
void f_0e9e58(int a)
{
    unsigned char *l0 = D_23c820;
    unsigned char *lt = l0 + 12512;
    unsigned char g = lt[433];
    unsigned char r = lt[432];
    unsigned char b = lt[434];
    unsigned int col = 0xff000000 | ((unsigned int)g << 16) | ((unsigned int)g << 8) | g;
    D_1d5a80 = r;
    D_27ec78 = col;
    D_27ec7c = b;
    D_1d5a8c = a;
    D_27ec80 = g;
}

/* @implements 0x0e9eb4 us f_0e9eb4
   WHAT IT DOES: An empty hook that does nothing. */
void f_0e9eb4(void)
{
}
