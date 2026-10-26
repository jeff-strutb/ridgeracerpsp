/* Object file 336 (retail 0x0fea38 to 0x0fea50): the reset of two cache words in .bss that the
   GE display list writers of object file 337 use. The word at 0x27f0b0 is the last texture
   list key written (-1 when none is recorded) and the word at 0x27f0b4 is the last part
   record written (0 when none). */

extern "C" int D_27f0b0;
extern "C" int D_27f0b4;

/* @implements 0x0fea38 us f_0fea38
   WHAT IT DOES: Resets the two state words: the first to -1 (nothing recorded) and the second
   to 0. */
extern "C" void f_0fea38(void)
{
    D_27f0b0 = -1;
    D_27f0b4 = 0;
}
