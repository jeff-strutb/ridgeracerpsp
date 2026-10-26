/* Five tiny functions of the sound layer (retail 0x10bd14 to 0x10bd3c): four empty
   stubs that return at once and one that returns -1. They sit between the radio script
   tables and the NU Sound C API and are hooks with no work to do: the no-op slots that
   a table of callbacks points at when a feature is not present. */

/* @implements 0x10bd14 us f_10bd14
   WHAT IT DOES: Empty stub; returns at once. */
void f_10bd14(void)
{
}

/* @implements 0x10bd1c us f_10bd1c
   WHAT IT DOES: Empty stub; returns at once. */
void f_10bd1c(void)
{
}

/* @implements 0x10bd24 us f_10bd24
   WHAT IT DOES: Empty stub; returns at once. */
void f_10bd24(void)
{
}

/* @implements 0x10bd2c us f_10bd2c
   WHAT IT DOES: Empty stub; returns at once. */
void f_10bd2c(void)
{
}

/* @implements 0x10bd34 us f_10bd34
   WHAT IT DOES: Returns -1 (no value). */
int f_10bd34(void)
{
    return -1;
}
