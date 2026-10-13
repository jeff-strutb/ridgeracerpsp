/* The fast trigonometry object file (retail 0x099b98 to 0x09ab88): angle wrapping, table
   driven sines and cosines (cubic pieces over 64 or 32 steps per half turn) and polynomial
   sines and cosines with a two part pi for the range reduction.
   Drafts: retail computes each absolute value into a second register (mov.s in the branch
   slot, then neg.s) and copies it back later; here the copy is propagated away and the
   branch becomes bc1tl with an in-place neg.s. A ternary, an inline helper and an
   if-assign helper give the same code. The angle wrap differs in its loop shape. */

/* Cubic coefficients per table step: ((c0 * t + c1) * t + c2) * t + c3. */
extern const float D_1aa700[][4];
extern const float D_1ab3a0[][4];

typedef struct Angle {
    float a;
} Angle;

/* @draft 0x099b98 us f_099b98
   WHAT IT DOES: Wraps an angle into (-pi, pi] by whole turns (the turn split in two parts
   for precision) and returns it. */
Angle *f_099b98(Angle *p)
{
    if (p->a > 3.14159274f) {
        do {
            p->a = p->a - 6.28320312f + 1.78178198e-05f;
        } while (p->a > 3.14159274f);
    } else if (p->a <= -3.14159274f) {
        do {
            p->a = p->a + 6.28320312f - 1.78178198e-05f;
        } while (p->a <= -3.14159274f);
    }
    return p;
}

/* @draft 0x099c30 us f_099c30
   WHAT IT DOES: Sine from the 64 step table: wraps the angle to a half turn and keeps the
   sign separately. */
float f_099c30(float x)
{
    int neg = 0;
    int i;
    float t, r;
    const float *c;
    if (x < 0.0f) {
        x = -x;
        neg = 1;
    }
    while (x > 3.14159274f)
        x = x - 6.28320312f + 1.78178198e-05f;
    if (x < 0.0f) {
        x = -x;
        neg ^= 1;
    }
    i = (int)(x * 64.0f);
    t = x - (float)i * 0.015625f;
    c = D_1aa700[i];
    r = ((c[0] * t + c[1]) * t + c[2]) * t + c[3];
    if (neg)
        r = -r;
    return r;
}

/* @implements 0x099d14 us f_099d14
   WHAT IT DOES: Sine from the 64 step table for an angle already within a half turn. */
float f_099d14(float x)
{
    float a = x;
    int i;
    float t, r;
    const float *c;
    if (x < 0.0f)
        a = -x;
    i = (int)(a * 64.0f);
    t = a - (float)i * 0.015625f;
    c = D_1aa700[i];
    r = ((c[0] * t + c[1]) * t + c[2]) * t + c[3];
    if (x < 0.0f)
        r = -r;
    return r;
}

/* @draft 0x099da0 us f_099da0
   WHAT IT DOES: Cosine from the 32 step table: wraps the angle's magnitude to a half
   turn. */
float f_099da0(float x)
{
    int i;
    float a, t;
    const float *c;
    a = x;
    if (x < 0.0f)
        a = -x;
    x = a;
    while (x > 3.14159274f)
        x = x - 6.28320312f + 1.78178198e-05f;
    a = x;
    if (x < 0.0f)
        a = -x;
    x = a;
    i = (int)(x * 32.0f);
    t = x - (float)i * 0.03125f;
    c = D_1ab3a0[i];
    return ((c[0] * t + c[1]) * t + c[2]) * t + c[3];
}

/* @draft 0x099e7c us f_099e7c
   WHAT IT DOES: Cosine from the 32 step table for an angle already within a half turn. */
float f_099e7c(float x)
{
    int i;
    float a, t;
    const float *c;
    a = x;
    if (x < 0.0f)
        a = -x;
    x = a;
    i = (int)(x * 32.0f);
    t = x - (float)i * 0.03125f;
    c = D_1ab3a0[i];
    return ((c[0] * t + c[1]) * t + c[2]) * t + c[3];
}

/* @implements 0x099efc us f_099efc
   WHAT IT DOES: Sine by a degree 11 polynomial after reducing the angle by the nearest
   multiple of pi (negated for odd multiples). */
float f_099efc(float x)
{
    float k = x * 0.318309873f;
    int n;
    float fn, r, z, p;
    if (x >= 0.0f)
        k = k + 0.5f;
    else
        k = k + -0.5f;
    n = (int)k;
    fn = (float)n;
    r = x - fn * 3.14160156f + fn * 8.90890988e-06f;
    z = r * r;
    p = ((((z * -2.50521079e-08f + 2.75573188e-06f) * z + -0.000198412701f) * z + 0.00833333377f) * z + -0.166666672f) * z * r + r;
    if (n & 1)
        p = -p;
    return p;
}

/* @draft 0x099fc4 us f_099fc4
   WHAT IT DOES: Sine by a degree 11 polynomial for an angle within a half turn (mirrored
   about a quarter turn). */
float f_099fc4(float x)
{
    float a = x;
    float z, p;
    if (x < 0.0f)
        a = -x;
    if (a > 1.57079637f)
        a = 3.14160156f - a - 8.90890988e-06f;
    z = a * a;
    p = ((((z * -2.50521079e-08f + 2.75573188e-06f) * z + -0.000198412701f) * z + 0.00833333377f) * z + -0.166666672f) * z * a + a;
    if (x < 0.0f)
        p = -p;
    return p;
}
