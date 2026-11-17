/* The fast trigonometry object file (retail 0x099b98 to 0x09ab88): angle wrapping, table
   driven sines and cosines (cubic pieces over 64 or 32 steps per half turn) and polynomial
   sines and cosines with a two part pi for the range reduction.
   Drafts: retail computes each absolute value into a second register (mov.s in the branch
   slot, then neg.s) and copies it back later; here the copy is propagated away and the
   branch becomes bc1tl with an in-place neg.s. A ternary, an inline helper and an
   if-assign helper give the same code. The angle wrap differs in its loop shape. */

#include <math.h>

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

/* @implements 0x09a07c us f_09a07c
   WHAT IT DOES: Cosine by a degree 10 polynomial after reducing the angle by the nearest
   multiple of pi (negated for odd multiples). */
float f_09a07c(float x)
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
    p = (((((z * 2.08767559e-09f + -2.755732e-07f) * z + 2.48015876e-05f) * z + -0.00138888892f) * z + 0.0416666679f) * z + -0.5f) * z + 1.0f;
    if (n & 1)
        p = -p;
    return p;
}

/* @implements 0x09a154 us f_09a154
   WHAT IT DOES: Cosine by a degree 10 polynomial for an angle within a half turn (mirrored
   about a quarter turn, negated past it). */
float f_09a154(float x)
{
    float a, z, p;
    if (x < 0.0f)
        x = -x;
    a = x;
    if (x > 1.57079637f)
        a = 3.14160156f - x - 8.90890988e-06f;
    z = a * a;
    p = (((((z * 2.08767559e-09f + -2.755732e-07f) * z + 2.48015876e-05f) * z + -0.00138888892f) * z + 0.0416666679f) * z + -0.5f) * z + 1.0f;
    if (x > 1.57079637f)
        p = -p;
    return p;
}

/* @implements 0x09a218 us f_09a218
   WHAT IT DOES: Tangent: reduces the angle by the nearest multiple of a quarter turn, takes
   a rational approximation of the reduced angle's tangent and returns it, or for odd
   multiples minus its reciprocal (the largest float when the reduced angle is zero). */
float f_09a218(float x)
{
    float k = x * 0.636619747f;
    int n;
    float fn, z, q;
    if (x >= 0.0f)
        k = k + 0.5f;
    else
        k = k + -0.5f;
    n = (int)k;
    fn = (float)n;
    x = x - fn * 1.57080078f + fn * 4.45445494e-06f;
    z = x * x;
    q = (315.0f - z * 14.0f) * z / ((z - 105.0f) * z + 945.0f);
    if (!(n & 1))
        return x / (1.0f - q);
    if (fabsf(x) > 1.1920929e-07f)
        return (q - 1.0f) / x;
    return 3.40282347e+38f;
}

/* Arctangent table per quarter step of [0, 1]: a degree 5 polynomial in the offset. */
extern const float D_1ab9f0[][6];

/* @implements 0x09a308 us f_09a308
   WHAT IT DOES: Arctangent of a value in [0, 1] from the four step table of degree 5
   pieces. */
float f_09a308(float x)
{
    int i;
    float t;
    const float *c;
    i = (int)(x * 4.0f);
    t = x - (float)i * 0.25f;
    c = D_1ab9f0[i];
    return ((((c[0] * t + c[1]) * t + c[2]) * t + c[3]) * t + c[4]) * t + c[5];
}

/* Arctangent of a non-negative value: above one, a quarter turn minus that of the
   reciprocal. */
static __inline__ float atan_table_pos(float a)
{
    if (a <= 1.0f)
        return f_09a308(a);
    return -4.45445494e-06f - f_09a308(1.0f / a) + 1.57080078f;
}

/* @implements 0x09a38c us f_09a38c
   WHAT IT DOES: Arctangent from the table: reflects magnitudes above one through a quarter
   turn minus the arctangent of the reciprocal, and restores the sign. */
float f_09a38c(float x)
{
    float a = x;
    float r;
    if (x < 0.0f)
        a = -x;
    r = atan_table_pos(a);
    if (x < 0.0f)
        r = -r;
    return r;
}

/* @implements 0x09a420 us f_09a420
   WHAT IT DOES: Two argument arctangent of y over x from the table, by octant: the
   arctangent of the smaller magnitude over the larger, offset by a quarter or half turn
   and signed for the octant. */
float f_09a420(float y, float x)
{
    if (y >= 0.0f) {
        if (x >= 0.0f) {
            if (y <= x)
                return f_09a308(y / x);
            return -4.45445494e-06f - f_09a308(x / y) + 1.57080078f;
        }
        x = -x;
        if (y <= x)
            return -8.90890988e-06f - f_09a308(y / x) + 3.14160156f;
        return f_09a308(x / y) - 4.45445494e-06f + 1.57080078f;
    }
    y = -y;
    if (x >= 0.0f) {
        if (y <= x)
            return -f_09a308(y / x);
        return f_09a308(x / y) + 4.45445494e-06f - 1.57080078f;
    }
    x = -x;
    if (y <= x)
        return f_09a308(y / x) + 8.90890988e-06f - 3.14160156f;
    return 4.45445494e-06f - f_09a308(x / y) - 1.57080078f;
}

/* @implements 0x09a590 us f_09a590
   WHAT IT DOES: The table two argument arctangent, returning zero when both arguments are
   within float epsilon of zero. */
float f_09a590(float y, float x)
{
    if (fabsf(x) < 1.1920929e-07f && fabsf(y) < 1.1920929e-07f)
        return 0.0f;
    if (y >= 0.0f) {
        if (x >= 0.0f) {
            if (y <= x)
                return f_09a308(y / x);
            return -4.45445494e-06f - f_09a308(x / y) + 1.57080078f;
        }
        x = -x;
        if (y <= x)
            return -8.90890988e-06f - f_09a308(y / x) + 3.14160156f;
        return f_09a308(x / y) - 4.45445494e-06f + 1.57080078f;
    }
    y = -y;
    if (x >= 0.0f) {
        if (y <= x)
            return -f_09a308(y / x);
        return f_09a308(x / y) + 4.45445494e-06f - 1.57080078f;
    }
    x = -x;
    if (y <= x)
        return f_09a308(y / x) + 8.90890988e-06f - 3.14160156f;
    return 4.45445494e-06f - f_09a308(x / y) - 1.57080078f;
}

/* @implements 0x09a73c us f_09a73c
   WHAT IT DOES: Arctangent of a value in [0, 1] by a degree 9 polynomial. */
float f_09a73c(float x)
{
    return ((((((((x * -0.0235559866f + 0.0950712338f) * x + -0.102869205f) * x + -0.0914973021f) * x + 0.256714284f) * x + -0.0179185495f) * x + -0.330302447f) * x + -0.000251847727f) * x + 1.00000799f) * x + -4.15739372e-08f;
}

/* Arctangent of a non-negative value: above one, a quarter turn minus that of the
   reciprocal. */
static __inline__ float atan_poly_pos(float a)
{
    if (a <= 1.0f)
        return f_09a73c(a);
    return -4.45445494e-06f - f_09a73c(1.0f / a) + 1.57080078f;
}

/* @implements 0x09a7d8 us f_09a7d8
   WHAT IT DOES: Polynomial arctangent: reflects magnitudes above one through a quarter
   turn minus the arctangent of the reciprocal, and restores the sign. */
float f_09a7d8(float x)
{
    float a = x;
    float r;
    if (x < 0.0f)
        a = -x;
    r = atan_poly_pos(a);
    if (x < 0.0f)
        r = -r;
    return r;
}

/* @implements 0x09a86c us f_09a86c
   WHAT IT DOES: Two argument arctangent of y over x by the polynomial, by octant (as
   f_09a420). */
float f_09a86c(float y, float x)
{
    if (y >= 0.0f) {
        if (x >= 0.0f) {
            if (y <= x)
                return f_09a73c(y / x);
            return -4.45445494e-06f - f_09a73c(x / y) + 1.57080078f;
        }
        x = -x;
        if (y <= x)
            return -8.90890988e-06f - f_09a73c(y / x) + 3.14160156f;
        return f_09a73c(x / y) - 4.45445494e-06f + 1.57080078f;
    }
    y = -y;
    if (x >= 0.0f) {
        if (y <= x)
            return -f_09a73c(y / x);
        return f_09a73c(x / y) + 4.45445494e-06f - 1.57080078f;
    }
    x = -x;
    if (y <= x)
        return f_09a73c(y / x) + 8.90890988e-06f - 3.14160156f;
    return 4.45445494e-06f - f_09a73c(x / y) - 1.57080078f;
}

/* @implements 0x09a9dc us f_09a9dc
   WHAT IT DOES: The polynomial two argument arctangent, returning zero when both
   arguments are within float epsilon of zero. */
float f_09a9dc(float y, float x)
{
    if (fabsf(x) < 1.1920929e-07f && fabsf(y) < 1.1920929e-07f)
        return 0.0f;
    if (y >= 0.0f) {
        if (x >= 0.0f) {
            if (y <= x)
                return f_09a73c(y / x);
            return -4.45445494e-06f - f_09a73c(x / y) + 1.57080078f;
        }
        x = -x;
        if (y <= x)
            return -8.90890988e-06f - f_09a73c(y / x) + 3.14160156f;
        return f_09a73c(x / y) - 4.45445494e-06f + 1.57080078f;
    }
    y = -y;
    if (x >= 0.0f) {
        if (y <= x)
            return -f_09a73c(y / x);
        return f_09a73c(x / y) + 4.45445494e-06f - 1.57080078f;
    }
    x = -x;
    if (y <= x)
        return f_09a73c(y / x) + 8.90890988e-06f - 3.14160156f;
    return 4.45445494e-06f - f_09a73c(x / y) - 1.57080078f;
}
