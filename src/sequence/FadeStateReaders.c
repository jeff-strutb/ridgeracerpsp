/* Two readers of the screen fade's state words (retail 0x0ea894 to 0x0ea8b4), with an empty
   hook at the start. The fade words live in the bss next to the fade colour (FadeColourState.c). */

extern int D_27ec84;            /* a fade state word, read by f_0ea8a8 */
extern int D_27ec8c;            /* a fade state word, read by f_0ea89c */

/* @implements 0x0ea894 us f_0ea894
   WHAT IT DOES: An empty hook that does nothing. */
void f_0ea894(void)
{
}

/* @implements 0x0ea89c us f_0ea89c
   WHAT IT DOES: Returns the fade state word D_27ec8c. */
int f_0ea89c(void)
{
    return D_27ec8c;
}

/* @implements 0x0ea8a8 us f_0ea8a8
   WHAT IT DOES: Returns the fade state word D_27ec84. */
int f_0ea8a8(void)
{
    return D_27ec84;
}
