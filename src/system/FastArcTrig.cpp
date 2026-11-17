/* The table driven arc cosine and arc sine (retail 0x09ab88 to 0x09ae9c): cubic pieces over
   32 steps below 0.75, and above it twice the arc sine of sqrt((1 - |x|) / 2). The square
   root keeps its errno call. */

#include <math.h>

extern "C" {

/* Cubic pieces of the arc cosine (for |x| < 0.75) and of the arc sine, over 32 steps. */
extern const float D_1aba70[][4];
extern const float D_1abbf0[][4];

/* Absolute value. */
static inline float Abs(float f)
{
    float r = f;
    if (f < 0.0f)
        r = -f;
    return r;
}

/* @implements 0x09ab88 us f_09ab88
   WHAT IT DOES: Arc cosine from the tables: the arc cosine table below 0.75, else twice the
   arc sine of sqrt((1 - |x|) / 2); pi minus the result for negative x. */
float f_09ab88(float x)
{
    float a = Abs(x);
    if (a < 0.75f) {
        int i = (int)(a * 32.0f);
        a = a - (float)i * 0.03125f;
        const float *c = D_1aba70[i];
        a = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
        if (x < 0.0f)
            return -8.90890988e-06f - a + 3.14160156f;
        return a;
    }
    a = sqrtf((1.0f - a) * 0.5f);
    int i = (int)(a * 32.0f);
    a = a - (float)i * 0.03125f;
    const float *c = D_1abbf0[i];
    float r = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
    a = r + r;
    if (x < 0.0f)
        return -8.90890988e-06f - a + 3.14160156f;
    return a;
}

/* @implements 0x09ad0c us f_09ad0c
   WHAT IT DOES: Arc sine from the arc sine table below 0.75, else pi/2 minus twice the arc
   sine of sqrt((1 - |x|) / 2); negated for negative x. */
float f_09ad0c(float x)
{
    float a = Abs(x);
    if (a < 0.75f) {
        int i = (int)(a * 32.0f);
        a = a - (float)i * 0.03125f;
        const float *c = D_1abbf0[i];
        a = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
        if (!(x < 0.0f))
            return a;
        return -a;
    }
    a = sqrtf((1.0f - a) * 0.5f);
    int i = (int)(a * 32.0f);
    a = a - (float)i * 0.03125f;
    const float *c = D_1abbf0[i];
    float r = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
    float q = -4.45445494e-06f - (r + r) + 1.57080078f;
    if (x < 0.0f)
        return -q;
    return q;
}

}
