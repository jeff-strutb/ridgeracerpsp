/* The NU Sound bank release wrapper (retail 0x10db1c to 0x10db3c, a gap row with no unwind
   information). It sits between the bank list (SoundBank.cpp, which ends at 0x10db1c) and the
   sound mixer's buses (SoundBus.cpp, which starts at 0x10db3c). */

/* Frees the bank buffer and deletes the bank list (SoundBank.cpp). */
void f_10d93c(void);

/* @implements 0x10db1c us f_10db1c
   WHAT IT DOES: Releases every sound bank (frees the bank list's buffer and deletes the list)
   and returns 0. */
int f_10db1c(void)
{
    f_10d93c();
    return 0;
}
