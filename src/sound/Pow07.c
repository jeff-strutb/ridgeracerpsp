/* A fast power function object file (retail 0x0fa7f0 to 0x0fa900): x to the power 0.7 by a
   logarithm series and a Pade exponential, used by the sound code at 0x0bdc3c. */

/* A float's bits. */
union Bits {
    float f;
    int i;
};

/* @draft 0x0fa7f0 us f_0fa7f0
   REMAINING DIFFERENCE: the operations and constants are retail's, but the float registers
   are allocated differently: retail keeps t^3 in $f12 and copies t to $f1, keeps zero in $f5
   and truncates n in place in $f0.
   WHAT IT DOES: Returns x to the power 0.7 (0 for x <= 0): splits x into a power of two and a
   mantissa in [0.5, 1), takes the natural logarithm from the series 2(t + t^3/3) with
   t = (m - 1)/(m + 1), scales it by 0.7, and rebuilds the power as 2^n times the Pade
   approximation (12 + 6y + y^2)/(12 - 6y + y^2) of e^y for the remainder y. */
float f_0fa7f0(float x)
{
    union Bits u, s;
    float t2, a, b;
    int e, n;

    u.f = x;
    e = (u.i >> 23) - 126;
    s.i = 0x3f800000 - (e << 23);
    if (x <= 0.0f)
        return 0.0f;
    x = x * s.f;
    x = (x - 1.0f) / (x + 1.0f);
    t2 = x * x;
    x = (float)e * 0.6931472f + 2.0f * (x + x * t2 * 0.33333334f);
    x = x * 0.7f;
    n = (int)(x * 1.442695f + (x >= 0.0f ? 0.5f : -0.5f));
    x = x - (float)n * 0.6931472f;
    b = x * 6.0f;
    a = x * x + 12.0f;
    u.f = (a + b) / (a - b);
    u.i = u.i + (n << 23);
    return u.f;
}
