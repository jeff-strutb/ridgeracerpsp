/* @cflags: -fno-math-errno */

/* The sound library's helpers (retail 0x11529c to 0x115800, a gap row with no unwind
   information): applying a bus's FX definition to the SAS effect unit, the vector unit maths
   the 3D sound object uses (cosine, arc cosine and arc tangent from piecewise polynomial
   tables, 3D vector difference, normalisation, cross and dot products, length, the listener
   view matrix and a transform by it), an empty debug print and two empty hooks. The function
   at 0x115180 at the start of the row is the text table reader's (TextTable.cpp). The arc
   cosine and arc tangent are the same code as the math library at 0x0ccaec (MathFunc.cpp),
   over their own copies of its tables: absolute value as an inline abs.s and rounding as an
   inline cvt.w.s. */

/* The vector unit code runs with the assembler's reordering on, so the final vector store
   lands in the return's delay slot. */

typedef struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

/* A bus chain mix (0x10dfcc). */
typedef struct BusMix {
    float vol;
    short pan;
    unsigned short n;
    unsigned char fx[32];
    unsigned char bus[32];
} BusMix;

/* An FX slot's effect settings. */
typedef struct FxParams {
    int type;
    int delay;
    int feedback;
} FxParams;

typedef struct FxDef {
    int used;
    int m4;
    FxParams p;
} FxDef;

int f_10dfcc(short id, BusMix *m);
FxDef *f_10e0b4(int i);
void f_11b30c(int type);                 /* SAS effect type */
void f_11b274(int dry, int wet);         /* SAS effect dry and wet switches */
void f_11b2c0(int delay, int feedback);  /* SAS effect parameters */

/* The polynomial tables: cubics for the arc cosine near 0 and near 1 (32 steps per unit),
   quintics for the arc tangent on 0..1 (4 steps). */
extern const float D_1b3160[][4];
extern const float D_1b32e0[][4];
extern const float D_1b3460[][6];

/* The w of a transformed point, and the listener's view matrix. */
extern float D_1d7a38;
extern float D_2826e0[16] __attribute__((aligned(16)));

/* Absolute value. */
static __inline__ float Abs(float f)
{
    float r;
    __asm__("abs.s %0, %1" : "=f"(r) : "f"(f));
    return r;
}

/* Rounds to the nearest integer (the current rounding mode). */
static __inline__ int Round(float f)
{
    int i;
    __asm__("cvt.w.s $f4, %1\n\tmfc1 %0, $f4" : "=r"(i) : "f"(f) : "$f4");
    return i;
}

/* Applies FX slot i's settings to the SAS effect unit. */
static __inline__ int ApplyFx(unsigned char i)
{
    FxParams *p = &f_10e0b4(i)->p;
    f_11b30c(p->type - 1);
    f_11b274(1, 1);
    f_11b2c0(p->delay, p->feedback);
    return 0;
}

/* @implements 0x11529c us f_11529c
   WHAT IT DOES: Mixes bus 1 up its chain and applies the first FX slot it sends to: sets the
   SAS effect type, turns dry and wet on and sets the delay and feedback. Returns the mix's
   error, else 0. */
int f_11529c(void)
{
    BusMix m;
    int r = f_10dfcc(1, &m);

    if (r < 0)
        return r;
    return ApplyFx(m.fx[0]);
}

/* @implements 0x115304 us f_115304
   WHAT IT DOES: Applies FX slot i's settings to the SAS effect unit (type, dry and wet on,
   delay and feedback). Returns 0. */
int f_115304(unsigned char i)
{
    return ApplyFx(i);
}

/* @implements 0x115354 us f_115354
   WHAT IT DOES: The cosine of x radians, on the vector unit (which takes quarter turns). */
float f_115354(float x)
{
    float r;

    x = x * 0.63661975f;
    __asm__ volatile("lv.s S400, %1\n\tvcos.s S401, S400\n\tsv.s S401, %0" : "=m"(r) : "m"(x));
    return r;
}

/* @implements 0x115380 us f_115380
   WHAT IT DOES: The arc cosine of x: a cubic per 1/32 of |x| below 0.75, and above it twice
   the arc sine of sqrt((1 - |x|) / 2) the same way; pi minus that for negative x (pi
   subtracted in two parts). */
float f_115380(float x)
{
    float a = Abs(x);
    int i;
    const float *c;
    float r;

    if (a < 0.75f) {
        i = Round(a * 32.0f);
        a = a - (float)i * 0.03125f;
        c = D_1b3160[i];
        a = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
        if (x < 0.0f)
            return -8.90890988e-06f - a + 3.14160156f;
        return a;
    }
    a = __builtin_sqrtf((1.0f - a) * 0.5f);
    i = Round(a * 32.0f);
    a = a - (float)i * 0.03125f;
    c = D_1b32e0[i];
    r = ((c[0] * a + c[1]) * a + c[2]) * a + c[3];
    a = r + r;
    if (x < 0.0f)
        return -8.90890988e-06f - a + 3.14160156f;
    return a;
}

/* @implements 0x1154c4 us f_1154c4
   WHAT IT DOES: out = a - b (3D). Returns out. */
Vec4 *f_1154c4(Vec4 *out, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile("lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvsub.t C420, C400, C410\n\tsv.q C420, 0(%0)"
                     : : "r"(out), "r"(a), "r"(b) : "memory");
    return out;
}

/* @implements 0x1154dc us f_1154dc
   WHAT IT DOES: out = a normalised (3D; out's w is kept). Returns out. */
Vec4 *f_1154dc(Vec4 *out, const Vec4 *a)
{
    __asm__ volatile("lv.q C400, 0(%1)\n\tvdot.t S410, C400, C400\n\tvrsq.s S411, S410\n\tlv.q C420, 0(%0)\n\t"
                     "vscl.t C420, C400, S411\n\tsv.q C420, 0(%0)"
                     : : "r"(out), "r"(a) : "memory");
    return out;
}

/* @implements 0x1154fc us f_1154fc
   WHAT IT DOES: out = a x b. Returns out. */
Vec4 *f_1154fc(Vec4 *out, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile("lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvcrsp.t C420, C400, C410\n\tsv.q C420, 0(%0)"
                     : : "r"(out), "r"(a), "r"(b) : "memory");
    return out;
}

/* @implements 0x115514 us f_115514
   WHAT IT DOES: The 3D dot product of a and b. */
float f_115514(const Vec4 *a, const Vec4 *b)
{
    float r;

    __asm__ volatile("lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvdot.t S420, C400, C410\n\tsv.s S420, %0"
                     : "=m"(r) : "r"(a), "r"(b));
    return r;
}

/* @implements 0x115534 us f_115534
   WHAT IT DOES: The length of a 3D vector. */
float f_115534(const Vec4 *a)
{
    float r;

    __asm__ volatile("lv.q C400, 0(%1)\n\tvdot.t S410, C400, C400\n\tvsqrt.s S411, S410\n\tsv.s S411, %0"
                     : "=m"(r) : "r"(a));
    return r;
}

/* @implements 0x115554 us f_115554
   WHAT IT DOES: out = the point in (w = 1) transformed by the view matrix held in vector
   matrix 0. Returns out. */
Vec4 *f_115554(Vec4 *out, const Vec4 *in)
{
    __asm__ volatile("lv.q C400, 0(%1)\n\tlv.s S403, %2\n\tvtfm4.q C410, E000, C400\n\tsv.q C410, 0(%0)"
                     : : "r"(out), "r"(in), "m"(D_1d7a38) : "memory");
    return out;
}

/* @implements 0x115570 us f_115570
   WHAT IT DOES: Builds the view matrix looking from eye towards at with the given up vector
   (D_2826e0: the side, up and back axes as columns, the eye moved to the origin) and loads it
   into vector matrix 0. */
void f_115570(const Vec4 *eye, const Vec4 *at, const Vec4 *up)
{
    Vec4 u, z, x;
    float *m = D_2826e0;

    f_1154dc(&u, up);
    f_1154c4(&z, eye, at);
    f_1154dc(&z, &z);
    f_1154fc(&x, &u, &z);
    f_1154dc(&x, &x);
    f_1154fc(&u, &z, &x);
    m[0] = x.x;
    m[4] = x.y;
    m[8] = x.z;
    m[1] = u.x;
    m[5] = u.y;
    m[9] = u.z;
    m[2] = z.x;
    m[6] = z.y;
    m[10] = z.z;
    m[3] = 0;
    m[7] = 0;
    m[11] = 0;
    m[12] = -f_115514(&x, eye);
    m[13] = -f_115514(&u, eye);
    m[14] = -f_115514(&z, eye);
    m[15] = 1.0f;
    __asm__ volatile("lv.q C000, 0(%0)\n\tlv.q C010, 16(%0)\n\tlv.q C020, 32(%0)\n\tlv.q C030, 48(%0)"
                     : : "r"(m) : "memory");
}

/* @implements 0x1156bc us f_1156bc
   WHAT IT DOES: The arc tangent of x in 0..1: a quintic per quarter. */
float f_1156bc(float x)
{
    int i = Round(x * 4.0f);
    const float *c;

    x = x - (float)i * 0.25f;
    c = D_1b3460[i];
    return ((((c[0] * x + c[1]) * x + c[2]) * x + c[3]) * x + c[4]) * x + c[5];
}

/* @implements 0x115744 us f_115744
   WHAT IT DOES: The arc tangent of x: from the table directly up to |x| = 1, as pi/2 minus
   the arc tangent of 1/|x| above it, negated for negative x. */
float f_115744(float x)
{
    float a = Abs(x);
    float r;
    float t;

    if (a <= 1.0f)
        t = f_1156bc(a);
    else
        t = -4.45445494e-06f - f_1156bc(1.0f / a) + 1.57080078f;
    r = t;
    if (x < 0.0f)
        r = -r;
    return r;
}

/* @implements 0x1157c8 us f_1157c8
   WHAT IT DOES: The debug print, compiled out. */
void f_1157c8(const char *fmt, ...)
{
}

/* @implements 0x1157f0 us f_1157f0
   WHAT IT DOES: Nothing. */
void f_1157f0(void)
{
}

/* @implements 0x1157f8 us f_1157f8
   WHAT IT DOES: Nothing. */
void f_1157f8(void)
{
}
