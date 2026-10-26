/* A sound index check (retail 0x10bd3c to 0x10bd70): the index is the second argument, a
   signed 16 bit value. Below 84 it is returned as it is; from 84 up both arguments are passed
   on to the fallback that returns -1 (f_10bd9c in the NU Sound C API). */

int f_10bd9c(int a, int idx);

/* @implements 0x10bd3c us f_10bd3c
   WHAT IT DOES: Returns the 16 bit index in the second argument when it is below 84; otherwise
   passes the first argument and the index on to the fallback f_10bd9c and returns its result. */
int f_10bd3c(int a, short idx)
{
    if (idx < 84)
        return idx;
    return f_10bd9c(a, idx);
}
