/* A small object file (retail 0x03e344 to 0x03e364) after the time attack sequence: two
   routines that reset the same race counter to 1000. The sequence base calls the first when a
   sequence starts, the sequences call the second. */

extern int D_2408f8;

/* @implements 0x03e344 us f_03e344
   WHAT IT DOES: Sets the race counter to 1000. */
void f_03e344(void)
{
    D_2408f8 = 1000;
}

/* @implements 0x03e354 us f_03e354
   WHAT IT DOES: Sets the race counter to 1000 (a second copy of the routine above). */
void f_03e354(void)
{
    D_2408f8 = 1000;
}
