/* The speed unit setting (retail 0x06b6fc to 0x06b7b4): a flag choosing miles per hour over
   kilometres per hour, the conversion of a speed into the chosen unit, and a small table
   lookup kept beside them. */

/* Nonzero when speeds are shown in miles per hour. */
extern signed char D_2413b0;

/* @implements 0x06b6fc us f_06b6fc
   WHAT IT DOES: Sets the speed unit flag (nonzero for miles per hour). */
void f_06b6fc(int mph)
{
    D_2413b0 = mph;
}

/* @implements 0x06b708 us f_06b708
   WHAT IT DOES: Returns the speed unit flag. */
int f_06b708(void)
{
    return D_2413b0;
}

/* @implements 0x06b714 us f_06b714
   WHAT IT DOES: Converts a speed in kilometres per hour into the chosen unit: divided by
   1.609344 (and truncated) when miles per hour are selected, unchanged otherwise. */
int f_06b714(int kmh)
{
    if (D_2413b0)
        return (int)((float)kmh / 1.609344f);
    return kmh;
}

/* @implements 0x06b748 us f_06b748
   WHAT IT DOES: Maps an index 0 to 8 to a fixed code (0, 1, 3, 9, 5, 7, 11, 255, 0); any other
   index gives 0. */
int f_06b748(unsigned int i)
{
    switch (i) {
    case 1:
        return 1;
    default:
    case 0:
        return 0;
    case 2:
        return 3;
    case 3:
        return 9;
    case 4:
        return 5;
    case 5:
        return 7;
    case 6:
        return 11;
    case 7:
        return 255;
    case 8:
        return 0;
    }
}
