/* @cflags: -fno-math-errno */

/* The vector library (retail 0x027c84 to 0x0281d8): two-component vectors in plain floating
   point, three- and four-component vectors and planes on the vector unit (quadword aligned,
   loaded and stored whole). Every operation writes its result through the first argument and
   returns it. M700 is the current transform kept by the matrix stack. */

/* The vector unit code is written in assembly with the assembler's reordering off, so it never
   moves a vector store into a following delay slot. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

typedef struct Vec2 {
    float x, y;
} Vec2;

typedef struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

float f_027ebc(const Vec4 *a, const Vec4 *b);
float f_0280c8(const Vec4 *a, const Vec4 *b);

/* @implements 0x027c84 us f_027c84
   WHAT IT DOES: Adds two 2D vectors. */
Vec2 *f_027c84(Vec2 *d, const Vec2 *a, const Vec2 *b)
{
    d->x = a->x + b->x;
    d->y = a->y + b->y;
    return d;
}

/* @implements 0x027cac us f_027cac
   WHAT IT DOES: Adds a number to both components of a 2D vector. */
Vec2 *f_027cac(Vec2 *d, const Vec2 *a, float s)
{
    d->x = a->x + s;
    d->y = a->y + s;
    return d;
}

/* @implements 0x027ccc us f_027ccc
   WHAT IT DOES: Meant to subtract two 2D vectors, but subtracts the first from itself, so the
   result is always zero (the second vector is never read). */
Vec2 *f_027ccc(Vec2 *d, const Vec2 *a, const Vec2 *b)
{
    d->x = a->x - a->x;
    d->y = a->y - a->y;
    return d;
}

/* @implements 0x027cec us f_027cec
   WHAT IT DOES: Subtracts a number from both components of a 2D vector. */
Vec2 *f_027cec(Vec2 *d, const Vec2 *a, float s)
{
    d->x = a->x - s;
    d->y = a->y - s;
    return d;
}

/* @implements 0x027d0c us f_027d0c
   WHAT IT DOES: Meant to multiply two 2D vectors component by component, but scales both
   components by the second vector's x. */
Vec2 *f_027d0c(Vec2 *d, const Vec2 *a, const Vec2 *b)
{
    float s = b->x;

    d->x = a->x * s;
    d->y = a->y * s;
    return d;
}

/* @implements 0x027d30 us f_027d30
   WHAT IT DOES: Scales a 2D vector by a number. */
Vec2 *f_027d30(Vec2 *d, const Vec2 *a, float s)
{
    d->x = a->x * s;
    d->y = a->y * s;
    return d;
}

/* @implements 0x027d50 us f_027d50
   WHAT IT DOES: Divides both components of a 2D vector by a number. */
Vec2 *f_027d50(Vec2 *d, const Vec2 *a, float s)
{
    d->x = a->x / s;
    d->y = a->y / s;
    return d;
}

/* @implements 0x027d70 us f_027d70
   WHAT IT DOES: Returns the length of a 2D vector. */
float f_027d70(const Vec2 *a)
{
    return __builtin_sqrtf(a->x * a->x + a->y * a->y);
}

/* @implements 0x027d8c us f_027d8c
   WHAT IT DOES: Scales a 2D vector to length 1. */
Vec2 *f_027d8c(Vec2 *d, const Vec2 *a)
{
    float x = a->x, y = a->y;
    float k = 1.0f / __builtin_sqrtf(x * x + y * y);
    d->x = x * k;
    d->y = y * k;
    return d;
}

/* @implements 0x027dc8 us f_027dc8
   WHAT IT DOES: Adds two 3D vectors. */
Vec4 *f_027dc8(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvadd.t C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x027de4 us f_027de4
   WHAT IT DOES: Adds a number to each component of a 3D vector. */
Vec4 *f_027de4(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S410, %2\n\t.word 0xdd000000\n\tvadd.t C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x027e0c us f_027e0c
   WHAT IT DOES: Subtracts one 3D vector from another. */
Vec4 *f_027e0c(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvsub.t C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x027e28 us f_027e28
   WHAT IT DOES: Subtracts a number from each component of a 3D vector. */
Vec4 *f_027e28(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S410, %2\n\t.word 0xdd000000\n\tvsub.t C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x027e50 us f_027e50
   WHAT IT DOES: Multiplies two 3D vectors component by component. */
Vec4 *f_027e50(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvmul.t C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x027e6c us f_027e6c
   WHAT IT DOES: Scales a 3D vector by a number. */
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S410, %2\n\tvscl.t C420, C400, S410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x027e90 us f_027e90
   WHAT IT DOES: Divides a 3D vector by a number (scales it by the reciprocal). */
Vec4 *f_027e90(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "vone.s S411\n\tlv.s S410, %2\n\tlv.q C400, 0(%1)\n\tvdiv.s S412, S411, S410\n\t"
                     "vscl.t C420, C400, S412\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x027ebc us f_027ebc
   WHAT IT DOES: Returns the dot product of two 3D vectors. */
float f_027ebc(const Vec4 *a, const Vec4 *b)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvdot.t S420, C400, C410\n\tsv.s S420, %0" VFPU_END
                     : "=m"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

/* @implements 0x027edc us f_027edc
   WHAT IT DOES: Returns the cross product of two 3D vectors. */
Vec4 *f_027edc(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvcrsp.t C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x027ef8 us f_027ef8
   WHAT IT DOES: Returns the length of a 3D vector. */
float f_027ef8(const Vec4 *a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvdot.t S410, C400, C400\n\tvsqrt.s S411, S410\n\tsv.s S411, %0" VFPU_END
                     : "=m"(r) : "r"(a) : "memory");
    return r;
}

/* @implements 0x027f18 us f_027f18
   WHAT IT DOES: Scales a 3D vector to length 1, keeping the result's fourth component. */
Vec4 *f_027f18(Vec4 *d, const Vec4 *a)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvdot.t S410, C400, C400\n\tvrsq.s S411, S410\n\tlv.q C420, 0(%0)\n\t"
                     "vscl.t C420, C400, S411\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a) : "memory");
    return d;
}

static const float D_1a1a80 = 1.0f;

/* @implements 0x027f3c us f_027f3c
   WHAT IT DOES: Transforms a point by the current matrix (M700), taking its fourth component as
   1. */
Vec4 *f_027f3c(Vec4 *d, const Vec4 *a)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S403, %2\n\tvtfm4.q C410, E700, C400\n\tsv.q C410, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(D_1a1a80) : "memory");
    return d;
}

/* @implements 0x027f5c us f_027f5c
   WHAT IT DOES: Transforms a direction by the current matrix (rotation and scale only). */
Vec4 *f_027f5c(Vec4 *d, const Vec4 *a)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvtfm3.t C410, E700, C400\n\tsv.q C410, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a) : "memory");
    return d;
}

/* @implements 0x027f74 us f_027f74
   WHAT IT DOES: Projects a point through the current matrix: transforms it with a fourth
   component of 1, then divides by the resulting fourth component. Returns 0 when that
   component is zero (the point is not projected), otherwise whether the reciprocal used is
   non-zero. */
int f_027f74(Vec4 *d, const Vec4 *a)
{
    float k;
    int r;

    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvone.s S420\n\tvone.s S403\n\tvtfm4.q C410, E700, C400\n\tsv.q C410, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a) : "memory");
    r = 0;
    if (d->w != 0.0f) {
        __asm__ volatile(VFPU_BEGIN "lv.q C410, 0(%1)\n\tvdiv.s S421, S420, S413\n\tvscl.t C410, C410, S421\n\tsv.q C410, 0(%1)\n\t"
                     "sv.s S421, %0" VFPU_END
                         : "=m"(k) : "r"(d) : "memory");
        if (k != 0.0f)
            r = 1;
    }
    return r;
}

/* @implements 0x027fd4 us f_027fd4
   WHAT IT DOES: Adds two 4D vectors. */
Vec4 *f_027fd4(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvadd.q C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x027ff0 us f_027ff0
   WHAT IT DOES: Adds a number to each component of a 4D vector. */
Vec4 *f_027ff0(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S410, %2\n\t.word 0xdd000000\n\tvadd.q C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x028018 us f_028018
   WHAT IT DOES: Subtracts one 4D vector from another. */
Vec4 *f_028018(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvsub.q C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x028034 us f_028034
   WHAT IT DOES: Subtracts a number from each component of a 4D vector. */
Vec4 *f_028034(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S410, %2\n\t.word 0xdd000000\n\tvsub.q C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x02805c us f_02805c
   WHAT IT DOES: Multiplies two 4D vectors component by component. */
Vec4 *f_02805c(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvmul.q C420, C400, C410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x028078 us f_028078
   WHAT IT DOES: Scales a 4D vector by a number. */
Vec4 *f_028078(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.s S410, %2\n\tvscl.q C420, C400, S410\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x02809c us f_02809c
   WHAT IT DOES: Divides a 4D vector by a number (scales it by the reciprocal). */
Vec4 *f_02809c(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "vone.s S411\n\tlv.s S410, %2\n\tlv.q C400, 0(%1)\n\tvdiv.s S412, S411, S410\n\t"
                     "vscl.q C420, C400, S412\n\tsv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x0280c8 us f_0280c8
   WHAT IT DOES: Returns the dot product of two 4D vectors. */
float f_0280c8(const Vec4 *a, const Vec4 *b)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tlv.q C410, 0(%2)\n\tvdot.q S420, C400, C410\n\tsv.s S420, %0" VFPU_END
                     : "=m"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

/* @implements 0x0280e8 us f_0280e8
   WHAT IT DOES: Returns the length of a 4D vector. */
float f_0280e8(const Vec4 *a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvdot.q S410, C400, C400\n\tvsqrt.s S411, S410\n\tsv.s S411, %0" VFPU_END
                     : "=m"(r) : "r"(a) : "memory");
    return r;
}

/* @implements 0x028108 us f_028108
   WHAT IT DOES: Scales a 4D vector to length 1. */
Vec4 *f_028108(Vec4 *d, const Vec4 *a)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvdot.q S410, C400, C400\n\tvrsq.s S411, S410\n\tvscl.q C420, C400, S411\n\t"
                     "sv.q C420, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a) : "memory");
    return d;
}

/* @implements 0x028128 us f_028128
   WHAT IT DOES: Transforms a 4D vector by the current matrix. */
Vec4 *f_028128(Vec4 *d, const Vec4 *a)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvtfm4.q C410, E700, C400\n\tsv.q C410, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a) : "memory");
    return d;
}

/* @implements 0x028140 us f_028140
   WHAT IT DOES: Returns the dot product of two 4D vectors (a second name for f_0280c8). */
float f_028140(const Vec4 *a, const Vec4 *b)
{
    return f_0280c8(a, b);
}

/* @implements 0x02815c us f_02815c
   WHAT IT DOES: Returns a point's signed distance from a plane (normal in x, y, z, offset in
   w). */
float f_02815c(const Vec4 *plane, const Vec4 *p)
{
    return f_027ebc(plane, p) + plane->w;
}

/* @implements 0x028188 us f_028188
   WHAT IT DOES: Builds the plane through a point with the given normal: the normal goes in x,
   y, z and the negated distance of the point along it in w. */
Vec4 *f_028188(Vec4 *d, const Vec4 *p, const float *n)
{
    d->x = n[0];
    d->y = n[1];
    d->z = n[2];
    d->w = -f_027ebc(p, (const Vec4 *)n);
    return d;
}
