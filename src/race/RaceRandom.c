/* The race random numbers and angle helpers (retail 0x0c2a40 to 0x0c2f24): two linear
   congruential generators (multiplier 0x41c64e6d, increment 12345, the top 16 bits taken)
   with their seeds, their results scaled to 0..1, a generator over a caller's own state, the
   wrap of an angle difference into -pi..pi and an absolute value. */

extern unsigned int D_245ed0;   /* the seed the first generator is restarted from */
extern unsigned int D_245ed4;   /* the first generator's state */
extern unsigned int D_245ed8;   /* the second generator's state */

/* @implements 0x0c2a40 us f_0c2a40
   WHAT IT DOES: Seeds the second generator. */
void f_0c2a40(unsigned int seed)
{
    D_245ed8 = seed;
}

/* @implements 0x0c2a4c us f_0c2a4c
   WHAT IT DOES: Restarts the first generator from its saved seed. */
void f_0c2a4c(void)
{
    D_245ed4 = D_245ed0;
}

/* @implements 0x0c2a60 us f_0c2a60
   WHAT IT DOES: Steps the first generator; returns its top 16 bits. */
unsigned int f_0c2a60(void)
{
    D_245ed4 = D_245ed4 * 0x41c64e6d + 12345;
    return D_245ed4 >> 16;
}

/* @implements 0x0c2a88 us f_0c2a88
   WHAT IT DOES: Steps the second generator; returns its top 16 bits. */
unsigned int f_0c2a88(void)
{
    D_245ed8 = D_245ed8 * 0x41c64e6d + 12345;
    return D_245ed8 >> 16;
}

/* @implements 0x0c2ab0 us f_0c2ab0
   WHAT IT DOES: The first generator scaled to 0..1. */
float f_0c2ab0(void)
{
    return (float)f_0c2a60() / 65535.0f;
}

/* @implements 0x0c2b04 us f_0c2b04
   WHAT IT DOES: The second generator scaled to 0..1. */
float f_0c2b04(void)
{
    return (float)f_0c2a88() / 65535.0f;
}

/* @implements 0x0c2b58 us f_0c2b58
   WHAT IT DOES: Steps a generator whose state the caller holds; returns its top 16 bits. */
unsigned int f_0c2b58(unsigned int *state)
{
    *state = *state * 0x41c64e6d + 12345;
    return *state >> 16;
}

/* @implements 0x0c2b7c us f_0c2b7c
   WHAT IT DOES: A caller's generator scaled to 0..1. */
float f_0c2b7c(unsigned int *state)
{
    return (float)f_0c2b58(state) / 65535.0f;
}

/* @implements 0x0c2bd0 us f_0c2bd0
   WHAT IT DOES: The difference of two angles wrapped into -pi..pi. */
float f_0c2bd0(float a, float b)
{
    float d = a - b;

    if (d > 3.14159274f)
        d -= 6.28318548f;
    else if (d < -3.14159274f)
        d += 6.28318548f;
    return d;
}

/* @implements 0x0c2c24 us f_0c2c24
   WHAT IT DOES: The absolute value. */
float f_0c2c24(float x)
{
    float r;

    if (0 <= x)
        r = x;
    else
        r = -x;
    return r;
}
