/* The memory stick insertion flag (retail 0x00600c to 0x006040): the callback the memory stick
   driver calls on insert or eject, and the two accessors the save code uses to see whether a
   card was inserted since it last looked. */

extern unsigned char D_1e8ec0;

/* @implements 0x00600c us f_00600c
   WHAT IT DOES: Forgets that a memory stick was inserted. */
void f_00600c(void)
{
    D_1e8ec0 = 0;
}

/* @implements 0x006018 us f_006018
   WHAT IT DOES: Returns whether a memory stick has been inserted since the flag was last
   cleared. */
unsigned char f_006018(void)
{
    return D_1e8ec0;
}

/* @implements 0x006024 us f_006024
   WHAT IT DOES: The memory stick driver's callback: on an insertion event (1) it records that
   a card was inserted. It always reports success. */
int f_006024(int count, int event, void *common)
{
    if (event == 1)
        D_1e8ec0 = event;
    return 0;
}
