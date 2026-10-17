/* @cflags: -fno-math-errno */
/* Fast single precision math (retail 0x0ccaec to 0x0cd4b4): angle wrapping, polynomial sine,
   cosine and tangent series, the arc sine and arc cosine series and their table driven
   forms, the arc tangent (one argument and two) over a table of quintic pieces, and the
   tangent by a rational approximation. Every reduction by pi or pi/2 subtracts the constant
   in two parts for precision. The absolute value is an inline abs.s (the builtin schedules
   ahead of the constant loads) and rounding to an integer an inline cvt.w.s (current
   rounding mode) through $f4. */

extern "C" {

/* Cubic pieces of the arc cosine (for |x| < 0.75) and arc sine over 32 steps, and quintic
   pieces of the arc tangent over 4 steps. */
extern const float D_1ad730[][4];
extern const float D_1ad8b0[][4];
extern const float D_1ada30[][6];

typedef struct Angle {
    float a;
} Angle;

/* Absolute value. */
static inline float Abs(float f)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(f));
    return r;
}

/* Rounds to the nearest integer. */
static inline int Round(float f)
{
    int i;
    __asm__("cvt.w.s $f4, %1\n\tmfc1 %0, $f4" : "=r"(i) : "f"(f) : "$f4");
    return i;
}

/* @implements 0x0ccaec us f_0ccaec
   WHAT IT DOES: Wraps an angle into (-pi, pi] by whole turns and returns it. */
Angle *f_0ccaec(Angle *p)
{
    if (p->a > 3.14159274f) {
        do
            p->a = p->a - 6.28320312f + 1.78178198e-05f;
        while (p->a > 3.14159274f);
    } else {
        while (p->a <= -3.14159274f)
            p->a = p->a + 6.28320312f - 1.78178198e-05f;
    }
    return p;
}

/* @implements 0x0ccb84 us f_0ccb84
   WHAT IT DOES: Sine by a degree 11 polynomial for an angle within a half turn (mirrored
   about a quarter turn). */
float f_0ccb84(float x)
{
    float a = Abs(x);
    float z, p;
    if (a > 1.57079637f)
        a = 3.14160156f - a - 8.90890988e-06f;
    z = a * a;
    p = ((((z * -2.50521079e-08f + 2.75573188e-06f) * z + -0.000198412701f) * z + 0.00833333377f) * z + -0.166666672f) * z * a + a;
    if (x < 0.0f)
        p = -p;
    return p;
}

/* @implements 0x0ccc24 us f_0ccc24
   WHAT IT DOES: Cosine by a degree 12 polynomial for an angle within a half turn (mirrored
   about a quarter turn, negated past it). */
float f_0ccc24(float x)
{
    float a = Abs(x);
    float t = a;
    float z, p;
    if (a > 1.57079637f)
        t = 3.14160156f - a - 8.90890988e-06f;
    z = t * t;
    p = (((((z * 2.08767559e-09f + -2.755732e-07f) * z + 2.48015876e-05f) * z + -0.00138888892f) * z + 0.0416666679f) * z + -0.5f) * z + 1.0f;
    if (a > 1.57079637f)
        p = -p;
    return p;
}

/* @implements 0x0cccd8 us f_0cccd8
   WHAT IT DOES: Tangent by its degree 11 series (the argument folded by pi past a full
   turn). */
float f_0cccd8(float x)
{
    float a = Abs(x);
    float z, p;
    if (a > 6.28318548f)
        a = 3.14160156f - a - 8.90890988e-06f;
    z = a * a;
    p = ((((z * 0.00886323582f + 0.021869488f) * z + -0.0539682545f) * z + 0.13333334f) * z + 0.333333343f) * z * a + a;
    if (x < 0.0f)
        p = -p;
    return p;
}

/* @implements 0x0ccd78 us f_0ccd78
   WHAT IT DOES: Arc sine by its degree 11 series. */
float f_0ccd78(float x)
{
    float a = Abs(x);
    float z, p;
    if (a > 1.0f)
        a = a - 1.0f;
    z = a * a;
    p = a * (((((z * 0.0223721582f + 0.030381944f) * z + 0.0446428582f) * z + 0.075000003f) * z + 0.166666672f) * z + 1.0f);
    if (x < 0.0f)
        p = -p;
    return p;
}

/* @implements 0x0cce04 us f_0cce04
   WHAT IT DOES: Arc cosine as pi/2 minus the arc sine series. */
float f_0cce04(float x)
{
    float a = Abs(x);
    float z, p;
    if (a > 1.0f)
        a = a - 1.0f;
    z = a * a;
    p = ((((z * -0.0223721582f + -0.030381944f) * z + -0.0446428582f) * z + -0.075000003f) * z + -0.166666672f) * z * a - a + 1.57079637f;
    if (x < 0.0f)
        p = -p;
    return p;
}

/* @implements 0x0cce9c us f_0cce9c
   WHAT IT DOES: Arc cosine from the tables: the arc cosine table below 0.75, else twice the
   arc sine of sqrt((1 - |x|) / 2); pi minus the result for negative x. */
float f_0cce9c(float x)
{
    float a = Abs(x);
    int i;
    const float *c;
    if (a < 0.75f) {
        i = Round(a * 32.0f);
        a = a - (float)i * 0.03125f;
        c = D_1ad730[i];
        a = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
        if (x < 0.0f)
            return -8.90890988e-06f - a + 3.14160156f;
        return a;
    }
    a = __builtin_sqrtf((1.0f - a) * 0.5f);
    i = Round(a * 32.0f);
    a = a - (float)i * 0.03125f;
    c = D_1ad8b0[i];
    float r = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
    a = r + r;
    if (x < 0.0f)
        return -8.90890988e-06f - a + 3.14160156f;
    return a;
}

/* @implements 0x0ccfe0 us f_0ccfe0
   WHAT IT DOES: Arc sine from the arc sine table below 0.75, else pi/2 minus twice the arc
   sine of sqrt((1 - |x|) / 2); negated for negative x. */
float f_0ccfe0(float x)
{
    float a = Abs(x);
    int i;
    const float *c;
    if (a < 0.75f) {
        i = Round(a * 32.0f);
        a = a - (float)i * 0.03125f;
        c = D_1ad8b0[i];
        a = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
        if (!(x < 0.0f))
            return a;
        return -a;
    }
    a = __builtin_sqrtf((1.0f - a) * 0.5f);
    i = Round(a * 32.0f);
    a = a - (float)i * 0.03125f;
    c = D_1ad8b0[i];
    float r = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
    float q = -4.45445494e-06f - (r + r) + 1.57080078f;
    if (x < 0.0f)
        return -q;
    return q;
}

float f_0cd1b0(float t);

/* @implements 0x0cd12c us f_0cd12c
   WHAT IT DOES: Arc tangent: the table kernel for |x| <= 1, else pi/2 minus the kernel of
   1/|x|; negated for negative x. */
float f_0cd12c(float x)
{
    float a = Abs(x);
    float r;
    float t;
    if (a <= 1.0f)
        t = f_0cd1b0(a);
    else
        t = -4.45445494e-06f - f_0cd1b0(1.0f / a) + 1.57080078f;
    r = t;
    if (x < 0.0f)
        r = -r;
    return r;
}

/* @implements 0x0cd1b0 us f_0cd1b0
   WHAT IT DOES: Arc tangent of t in [0, 1] from the table of quintic pieces. */
float f_0cd1b0(float t)
{
    int i = Round(t * 4.0f);
    const float *c;
    t = t - (float)i * 0.25f;
    c = D_1ada30[i];
    return ((((c[0] * t + c[1]) * t + c[2]) * t + c[3]) * t + c[4]) * t + c[5];
}

/* @implements 0x0cd238 us f_0cd238
   WHAT IT DOES: Arc tangent of y / x over the full turn (0 for the origin), by octant. */
float f_0cd238(float y, float x)
{
    if (x == 0.0f && y == 0.0f)
        return 0.0f;
    if (0.0f <= y) {
        if (0.0f <= x) {
            if (y <= x)
                return f_0cd1b0(y / x);
            return -4.45445494e-06f - f_0cd1b0(x / y) + 1.57080078f;
        }
        x = -x;
        if (y <= x)
            return -8.90890988e-06f - f_0cd1b0(y / x) + 3.14160156f;
        return f_0cd1b0(x / y) - 4.45445494e-06f + 1.57080078f;
    }
    y = -y;
    if (0.0f <= x) {
        if (y <= x)
            return -f_0cd1b0(y / x);
        return f_0cd1b0(x / y) + 4.45445494e-06f - 1.57080078f;
    }
    x = -x;
    if (y <= x)
        return f_0cd1b0(y / x) + 8.90890988e-06f - 3.14160156f;
    return 4.45445494e-06f - f_0cd1b0(x / y) - 1.57080078f;
}

/* @implements 0x0cd3cc us f_0cd3cc
   WHAT IT DOES: Tangent: reduces by the nearest multiple of pi/2 and uses a rational
   approximation, inverted (negative reciprocal) for odd multiples; the largest float for
   an odd multiple's zero. */
float f_0cd3cc(float x)
{
    float k = x * 0.636619747f;
    int n;
    float fn, r, z, q;
    n = Round(x >= 0.0f ? k + 0.5f : k + -0.5f);
    fn = (float)n;
    r = x - fn * 1.57080078f + fn * 4.45445494e-06f;
    z = r * r;
    q = (315.0f - z * 14.0f) * z / ((z - 105.0f) * z + 945.0f);
    if ((n & 1) == 0)
        return r / (1.0f - q);
    if (r == 0.0f)
        return 3.40282347e+38f;
    return (q - 1.0f) / r;
}

}
