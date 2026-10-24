/* @cflags: -fno-math-errno */

/* The second vector library (retail 0x0a5d48 to 0x0a6990, an object file with no unwind
   information): element access on 4x4 matrices, three- and four-component vectors on the
   vector unit and in plain floating point, normalisation, matrix-vector transforms and
   orthonormal basis builders. Unlike the library at 0x027c84 it uses vector matrices 0 to 2.
   Operations write their result through the first argument and return it. */

/* The vector unit code is written in assembly with the assembler's reordering off, so it never
   moves a vector store into a following delay slot. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

typedef struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

/* The row orders for f_0a67fc: which row is kept, which is made perpendicular to it, and which
   becomes their cross product. */
static const signed char D_1ac12c[6][3] = {
    { 0, 1, 2 }, { 0, 2, 1 }, { 1, 2, 0 }, { 1, 0, 2 }, { 2, 0, 1 }, { 2, 1, 0 },
};

/* @implements 0x0a5d48 us f_0a5d48
   WHAT IT DOES: Returns the address of element (column i, row j) of a 4x4 matrix. */
float *f_0a5d48(float m[4][4], int i, int j)
{
    return &m[j][i];
}

/* @implements 0x0a5d5c us f_0a5d5c
   WHAT IT DOES: Returns the address of element (column i, row j) of a 4x4 matrix (a second
   copy). */
float *f_0a5d5c(float m[4][4], int i, int j)
{
    return &m[j][i];
}

/* @implements 0x0a5d70 us f_0a5d70
   WHAT IT DOES: Returns element (column i, row j) of a 4x4 matrix. */
float f_0a5d70(const float m[4][4], int i, int j)
{
    return m[j][i];
}

/* @implements 0x0a5d88 us f_0a5d88
   WHAT IT DOES: Returns the address of element (column i, row j) of a 4x4 matrix (a third
   copy). */
float *f_0a5d88(float m[4][4], int i, int j)
{
    return &m[j][i];
}

/* @implements 0x0a5d9c us f_0a5d9c
   WHAT IT DOES: Negates a 3D vector in place. */
Vec4 *f_0a5d9c(Vec4 *d)
{
    d->x = -d->x;
    d->y = -d->y;
    d->z = -d->z;
    return d;
}

/* @implements 0x0a5dc8 us f_0a5dc8
   WHAT IT DOES: Adds a 3D vector to another in place. */
Vec4 *f_0a5dc8(Vec4 *d, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvadd.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5de4 us f_0a5de4
   WHAT IT DOES: Subtracts a 3D vector from another in place. */
Vec4 *f_0a5de4(Vec4 *d, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvsub.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5e00 us f_0a5e00
   WHAT IT DOES: Multiplies a 3D vector by another component by component, in place. */
Vec4 *f_0a5e00(Vec4 *d, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvmul.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5e1c us f_0a5e1c
   WHAT IT DOES: Scales a 3D vector by a number in place. */
Vec4 *f_0a5e1c(Vec4 *d, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.s S010, %1\n\tvscl.t C020, C000, S010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a5e40 us f_0a5e40
   WHAT IT DOES: Divides a 3D vector by a number in place (scales it by the reciprocal). */
Vec4 *f_0a5e40(Vec4 *d, float s)
{
    __asm__ volatile(VFPU_BEGIN "vone.s S011\n\tlv.q C000, 0(%0)\n\tlv.s S010, %1\n\tvdiv.s S012, S011, S010\n\t"
                     "vscl.t C020, C000, S012\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a5e6c us f_0a5e6c
   WHAT IT DOES: Adds two 3D vectors. */
Vec4 *f_0a5e6c(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvadd.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5e88 us f_0a5e88
   WHAT IT DOES: Subtracts one 3D vector from another. */
Vec4 *f_0a5e88(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvsub.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5ea4 us f_0a5ea4
   WHAT IT DOES: Scales a 3D vector by a number. */
Vec4 *f_0a5ea4(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.s S010, %2\n\tvscl.t C020, C000, S010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a5ec8 us f_0a5ec8
   WHAT IT DOES: Divides a 3D vector by a number (scales it by the reciprocal). */
Vec4 *f_0a5ec8(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "vone.s S011\n\tlv.q C000, 0(%1)\n\tlv.s S010, %2\n\tvdiv.s S012, S011, S010\n\t"
                     "vscl.t C020, C000, S012\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a5ef4 us f_0a5ef4
   WHAT IT DOES: Scales a 3D vector by a number (the number-first form of f_0a5ea4). */
Vec4 *f_0a5ef4(Vec4 *d, const Vec4 *a, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.s S010, %2\n\tvscl.t C020, C000, S010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a5f18 us f_0a5f18
   WHAT IT DOES: Multiplies two 3D vectors component by component. */
Vec4 *f_0a5f18(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvmul.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5f34 us f_0a5f34
   WHAT IT DOES: Returns the squared length of a 3D vector (its dot product with itself). */
float f_0a5f34(const Vec4 *a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvdot.t S020, C000, C010\n\tsv.s S020, %0" VFPU_END
                     : "=m"(r) : "r"(a), "r"(a) : "memory");
    return r;
}

/* @implements 0x0a5f54 us f_0a5f54
   WHAT IT DOES: Returns the dot product of two 3D vectors. */
float f_0a5f54(const Vec4 *a, const Vec4 *b)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvdot.t S020, C000, C010\n\tsv.s S020, %0" VFPU_END
                     : "=m"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

/* @implements 0x0a5f74 us f_0a5f74
   WHAT IT DOES: Returns the cross product of two 3D vectors. */
Vec4 *f_0a5f74(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvcrsp.t C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5f90 us f_0a5f90
   WHAT IT DOES: Negates a 4D vector in place. */
Vec4 *f_0a5f90(Vec4 *d)
{
    d->x = -d->x;
    d->y = -d->y;
    d->z = -d->z;
    d->w = -d->w;
    return d;
}

/* @implements 0x0a5fc8 us f_0a5fc8
   WHAT IT DOES: Adds a 4D vector to another in place. */
Vec4 *f_0a5fc8(Vec4 *d, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvadd.q C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a5fe4 us f_0a5fe4
   WHAT IT DOES: Subtracts a 4D vector from another in place. */
Vec4 *f_0a5fe4(Vec4 *d, const Vec4 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvsub.q C020, C000, C010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a6000 us f_0a6000
   WHAT IT DOES: Scales a 4D vector by a number in place. */
Vec4 *f_0a6000(Vec4 *d, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.s S010, %1\n\tvscl.q C020, C000, S010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a6024 us f_0a6024
   WHAT IT DOES: Divides a 4D vector by a number in place (scales it by the reciprocal). */
Vec4 *f_0a6024(Vec4 *d, float s)
{
    __asm__ volatile(VFPU_BEGIN "vone.s S011\n\tlv.q C000, 0(%0)\n\tlv.s S010, %1\n\tvdiv.s S012, S011, S010\n\t"
                     "vscl.q C020, C000, S012\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a6050 us f_0a6050
   WHAT IT DOES: Stores the negation of a 4D vector. */
Vec4 *f_0a6050(Vec4 *d, const Vec4 *a)
{
    d->x = -a->x;
    d->y = -a->y;
    d->z = -a->z;
    d->w = -a->w;
    return d;
}

/* @implements 0x0a6088 us f_0a6088
   WHAT IT DOES: Adds two points: the sum's x, y, z, with the fourth component set to 1. */
Vec4 *f_0a6088(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvadd.q C020, C000, C010\n\tsv.q C020, %0" VFPU_END
                     : "=m"(t) : "r"(a), "r"(b) : "memory");
    d->x = t[0];
    d->y = t[1];
    d->z = t[2];
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a60cc us f_0a60cc
   WHAT IT DOES: Subtracts two points: the difference's x, y, z, with the fourth component set
   to 1. */
Vec4 *f_0a60cc(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvsub.q C020, C000, C010\n\tsv.q C020, %0" VFPU_END
                     : "=m"(t) : "r"(a), "r"(b) : "memory");
    d->x = t[0];
    d->y = t[1];
    d->z = t[2];
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a6110 us f_0a6110
   WHAT IT DOES: Scales a point by a number, with the fourth component set to 1. */
Vec4 *f_0a6110(Vec4 *d, const Vec4 *a, float s)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.s S010, %2\n\tvscl.q C020, C000, S010\n\tsv.q C020, %0" VFPU_END
                     : "=m"(t) : "r"(a), "m"(s) : "memory");
    d->x = t[0];
    d->y = t[1];
    d->z = t[2];
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a6158 us f_0a6158
   WHAT IT DOES: Divides a point by a number, with the fourth component set to 1. */
Vec4 *f_0a6158(Vec4 *d, const Vec4 *a, float s)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ volatile(VFPU_BEGIN "vone.s S011\n\tlv.q C000, 0(%1)\n\tlv.s S010, %2\n\tvdiv.s S012, S011, S010\n\t"
                     "vscl.q C020, C000, S012\n\tsv.q C020, %0" VFPU_END
                     : "=m"(t) : "r"(a), "m"(s) : "memory");
    d->x = t[0];
    d->y = t[1];
    d->z = t[2];
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a61a8 us f_0a61a8
   WHAT IT DOES: Scales a point by a number, with the fourth component set to 1 (the
   number-first form of f_0a6110). */
Vec4 *f_0a61a8(Vec4 *d, const Vec4 *a, float s)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.s S010, %2\n\tvscl.q C020, C000, S010\n\tsv.q C020, %0" VFPU_END
                     : "=m"(t) : "r"(a), "m"(s) : "memory");
    d->x = t[0];
    d->y = t[1];
    d->z = t[2];
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a61f0 us f_0a61f0
   WHAT IT DOES: Sets a point to the origin (0, 0, 0, 1). */
Vec4 *f_0a61f0(Vec4 *d)
{
    d->x = 0.0f;
    d->y = 0.0f;
    d->z = 0.0f;
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a6210 us f_0a6210
   WHAT IT DOES: Negates a 4D vector in place (a second copy). */
Vec4 *f_0a6210(Vec4 *d)
{
    d->x = -d->x;
    d->y = -d->y;
    d->z = -d->z;
    d->w = -d->w;
    return d;
}

/* @implements 0x0a6248 us f_0a6248
   WHAT IT DOES: Negates a 3D vector in place (a second copy). */
Vec4 *f_0a6248(Vec4 *d)
{
    d->x = -d->x;
    d->y = -d->y;
    d->z = -d->z;
    return d;
}

/* @implements 0x0a6274 us f_0a6274
   WHAT IT DOES: Adds a 4D vector to another in place, in plain floating point. */
Vec4 *f_0a6274(Vec4 *d, const float *a)
{
    d->x += a[0];
    d->y += a[1];
    d->z += a[2];
    d->w += a[3];
    return d;
}

/* @implements 0x0a62bc us f_0a62bc
   WHAT IT DOES: Subtracts a 4D vector from another in place, in plain floating point. */
Vec4 *f_0a62bc(Vec4 *d, const float *a)
{
    d->x -= a[0];
    d->y -= a[1];
    d->z -= a[2];
    d->w -= a[3];
    return d;
}

/* @implements 0x0a6304 us f_0a6304
   WHAT IT DOES: Scales a 4D vector by a number in place, in plain floating point. */
Vec4 *f_0a6304(Vec4 *d, float s)
{
    d->x *= s;
    d->y *= s;
    d->z *= s;
    d->w *= s;
    return d;
}

/* @implements 0x0a633c us f_0a633c
   WHAT IT DOES: Divides a 4D vector by a number in place, in plain floating point. */
Vec4 *f_0a633c(Vec4 *d, float s)
{
    d->x /= s;
    d->y /= s;
    d->z /= s;
    d->w /= s;
    return d;
}

/* @implements 0x0a6374 us f_0a6374
   WHAT IT DOES: Returns the squared length of a 4D vector, in plain floating point. */
float f_0a6374(const Vec4 *a)
{
    return a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w;
}

/* @implements 0x0a63a4 us f_0a63a4
   WHAT IT DOES: Stores a point with x, y, z negated and the fourth component kept. */
Vec4 *f_0a63a4(Vec4 *d, const Vec4 *a)
{
    d->x = -a->x;
    d->y = -a->y;
    d->z = -a->z;
    d->w = a->w;
    return d;
}

/* @implements 0x0a63d8 us f_0a63d8
   WHAT IT DOES: Stores the negation of a 4D vector (a second copy). */
Vec4 *f_0a63d8(Vec4 *d, const Vec4 *a)
{
    d->x = -a->x;
    d->y = -a->y;
    d->z = -a->z;
    d->w = -a->w;
    return d;
}

/* @implements 0x0a6410 us f_0a6410
   WHAT IT DOES: Adds two 4D vectors, in plain floating point. */
Vec4 *f_0a6410(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    d->x = a->x + b->x;
    d->y = a->y + b->y;
    d->z = a->z + b->z;
    d->w = a->w + b->w;
    return d;
}

/* @implements 0x0a6458 us f_0a6458
   WHAT IT DOES: Subtracts one 4D vector from another, in plain floating point. */
Vec4 *f_0a6458(Vec4 *d, const Vec4 *a, const Vec4 *b)
{
    d->x = a->x - b->x;
    d->y = a->y - b->y;
    d->z = a->z - b->z;
    d->w = a->w - b->w;
    return d;
}

/* @implements 0x0a64a0 us f_0a64a0
   WHAT IT DOES: Scales a 4D vector by a number, in plain floating point. */
Vec4 *f_0a64a0(Vec4 *d, const Vec4 *a, float s)
{
    d->x = s * a->x;
    d->y = s * a->y;
    d->z = s * a->z;
    d->w = s * a->w;
    return d;
}

/* @implements 0x0a64d8 us f_0a64d8
   WHAT IT DOES: Divides a 4D vector by a number, in plain floating point. */
Vec4 *f_0a64d8(Vec4 *d, const Vec4 *a, float s)
{
    d->x = a->x / s;
    d->y = a->y / s;
    d->z = a->z / s;
    d->w = a->w / s;
    return d;
}

/* @implements 0x0a6510 us f_0a6510
   WHAT IT DOES: Scales a 4D vector by a number, in plain floating point (a second copy). */
Vec4 *f_0a6510(Vec4 *d, const Vec4 *a, float s)
{
    d->x = s * a->x;
    d->y = s * a->y;
    d->z = s * a->z;
    d->w = s * a->w;
    return d;
}

/* @implements 0x0a6548 us f_0a6548
   WHAT IT DOES: Never returns: loops on itself (a stop for an unreachable case). */
void f_0a6548(void)
{
    for (;;)
        ;
}

/* @implements 0x0a6550 us f_0a6550
   WHAT IT DOES: Sets a 3D vector's length to a number in place (normalises it, then scales). */
Vec4 *f_0a6550(Vec4 *d, float s)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.s S010, %1\n\tvdot.t S020, C000, C000\n\tvrsq.s S021, S020\n\t"
                     "vscl.t C020, C000, S021\n\tvscl.t C020, C020, S010\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d), "m"(s) : "memory");
    return d;
}

/* @implements 0x0a6580 us f_0a6580
   WHAT IT DOES: Scales a 3D vector to length 1 in place. */
Vec4 *f_0a6580(Vec4 *d)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tvdot.t S010, C000, C000\n\tvrsq.s S011, S010\n\t"
                     "vscl.t C020, C000, S011\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d) : "memory");
    return d;
}

/* @implements 0x0a65a0 us f_0a65a0
   WHAT IT DOES: Transforms a 3D vector in place by the 3x3 part of a matrix (rows of four). */
Vec4 *f_0a65a0(Vec4 *d, const Vec4 *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C100, 0(%1)\n\tlv.q C110, 16(%1)\n\tlv.q C120, 32(%1)\n\t"
                     "vtfm3.t C010, M100, C000\n\tsv.q C010, 0(%0)" VFPU_END
                     : : "r"(d), "r"(m) : "memory");
    return d;
}

/* @implements 0x0a65c4 us f_0a65c4
   WHAT IT DOES: Returns the length of a 3D vector. */
float f_0a65c4(const Vec4 *a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tvdot.t S020, C000, C000\n\tvsqrt.s S000, S020\n\tsv.s S000, %0" VFPU_END
                     : "=m"(r) : "r"(a) : "memory");
    return r;
}

/* @implements 0x0a65e4 us f_0a65e4
   WHAT IT DOES: Stores a 3D vector scaled to length 1. */
Vec4 *f_0a65e4(Vec4 *d, const Vec4 *a)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tvdot.t S010, C000, C000\n\tvrsq.s S011, S010\n\t"
                     "vscl.t C000, C000, S011\n\tsv.q C000, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a) : "memory");
    return d;
}

/* @implements 0x0a6604 us f_0a6604
   WHAT IT DOES: Transforms a 3D vector by the 3x3 part of a matrix (rows of four). */
Vec4 *f_0a6604(Vec4 *d, const Vec4 *a, const Vec4 *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C100, 0(%2)\n\tlv.q C110, 16(%2)\n\tlv.q C120, 32(%2)\n\t"
                     "vtfm3.t C010, M100, C000\n\tsv.q C010, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(m) : "memory");
    return d;
}

/* @implements 0x0a6628 us f_0a6628
   WHAT IT DOES: Transforms a 3D vector by the transpose of a 4x4 matrix's 3x3 part (the
   inverse rotation, for an orthonormal matrix). */
Vec4 *f_0a6628(Vec4 *d, const Vec4 *a, const Vec4 *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C100, 0(%2)\n\tlv.q C110, 16(%2)\n\tlv.q C120, 32(%2)\n\t"
                     "lv.q C130, 48(%2)\n\tvtfm3.t C010, E100, C000\n\tsv.q C010, 0(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(m) : "memory");
    return d;
}

/* @implements 0x0a6650 us f_0a6650
   WHAT IT DOES: Returns the distance between two 3D points. */
float f_0a6650(const Vec4 *a, const Vec4 *b)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tvsub.t C020, C000, C010\n\tvmul.t C010, C020, C020\n\t"
                     "vadd.s S010, S010, S011\n\tvadd.s S010, S010, S012\n\tvsqrt.s S000, S010\n\tsv.s S000, %0" VFPU_END
                     : "=m"(r) : "r"(a), "r"(b) : "memory");
    return r;
}

/* @implements 0x0a6680 us f_0a6680
   WHAT IT DOES: Builds a look-at rotation (three rows) from an eye point to a target, with the
   world y axis as up: the third row is the unit direction from the target to the eye, the
   second is up made perpendicular to it, the first their cross product. */
void f_0a6680(const Vec4 *eye, const Vec4 *at, Vec4 *m)
{
    Vec4 up;

    up.z = up.x = 0.0f;
    up.w = up.y = 1.0f;
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvsub.t C000, C000, C010\n\tvdot.t S010, C000, C000\n\t"
                     "vrsq.s S011, S010\n\tvscl.t C120, C000, S011\n\tlv.q C110, %3\n\tvscl.t C020, C120, S121\n\t"
                     "vsub.t C110, C110, C020\n\tvdot.t S010, C110, C110\n\tvrsq.s S011, S010\n\tvscl.t C110, C110, S011\n\t"
                     "vcrsp.t C100, C110, C120\n\tsv.q C100, 0(%2)\n\tsv.q C110, 16(%2)\n\tsv.q C120, 32(%2)" VFPU_END
                     : : "r"(eye), "r"(at), "r"(m), "m"(up) : "memory");
}

/* @implements 0x0a66e8 us f_0a66e8
   WHAT IT DOES: Builds a look-at rotation (three rows) from an eye point to a target with a
   given up vector: as f_0a6680, but up is the third argument (its y projection is taken along
   the direction's y, so it assumes up is the y axis). */
void f_0a66e8(const Vec4 *eye, const Vec4 *at, const Vec4 *up, Vec4 *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 0(%1)\n\tvsub.t C000, C000, C010\n\tvdot.t S010, C000, C000\n\t"
                     "vrsq.s S011, S010\n\tvscl.t C120, C000, S011\n\tlv.q C110, 0(%2)\n\tvscl.t C020, C120, S121\n\t"
                     "vsub.t C110, C110, C020\n\tvdot.t S010, C110, C110\n\tvrsq.s S011, S010\n\tvscl.t C110, C110, S011\n\t"
                     "vcrsp.t C100, C110, C120\n\tsv.q C100, 0(%3)\n\tsv.q C110, 16(%3)\n\tsv.q C120, 32(%3)" VFPU_END
                     : : "r"(eye), "r"(at), "r"(up), "r"(m) : "memory");
}

/* @implements 0x0a6730 us f_0a6730
   WHAT IT DOES: Meant to interpolate between two 3D points by t, but the result is stored to a
   local and never reaches the destination, which is returned unchanged. The return copy
   (move v0,a0) follows the assembly in retail, which it does only when the assembly clobbers
   v0. */
Vec4 *f_0a6730(Vec4 *d, const Vec4 *a, const Vec4 *b, float t)
{
    Vec4 r;
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C010, 0(%2)\n\tlv.q C020, %3\n\tvsub.t C030, C010, C000\n\t"
                     "vscl.t C010, C030, S020\n\tvadd.t C000, C000, C010\n\tsv.q C000, %0" VFPU_END
                     : "=m"(r) : "r"(a), "r"(b), "m"(t) : "memory", "v0");
    return d;
}

/* @implements 0x0a6760 us f_0a6760
   WHAT IT DOES: Divides a point in place by its fourth component, which becomes 1. */
void f_0a6760(Vec4 *d)
{
    __asm__ volatile(VFPU_BEGIN "vone.s S011\n\tlv.q C000, 0(%0)\n\tvmov.s S010, S003\n\tvdiv.s S012, S011, S010\n\t"
                     "vscl.t C020, C000, S012\n\tvone.s S023\n\tsv.q C020, 0(%0)" VFPU_END
                     : : "r"(d) : "memory");
}

/* @implements 0x0a6784 us f_0a6784
   WHAT IT DOES: Transforms a 4D vector in place by a 4x4 matrix. */
Vec4 *f_0a6784(Vec4 *d, const Vec4 *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C100, 0(%1)\n\tlv.q C110, 16(%1)\n\tlv.q C120, 32(%1)\n\t"
                     "lv.q C130, 48(%1)\n\tvtfm4.q C010, M100, C000\n\tsv.q C010, 0(%0)" VFPU_END
                     : : "r"(d), "r"(m) : "memory");
    return d;
}

/* @implements 0x0a67ac us f_0a67ac
   WHAT IT DOES: Transforms a point by a 4x4 matrix, keeping x, y, z and setting the fourth
   component to 1. */
Vec4 *f_0a67ac(Vec4 *d, const Vec4 *a, const Vec4 *m)
{
    float t[4] __attribute__((aligned(16)));
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%1)\n\tlv.q C100, 0(%2)\n\tlv.q C110, 16(%2)\n\tlv.q C120, 32(%2)\n\t"
                     "lv.q C130, 48(%2)\n\tvtfm4.q C010, M100, C000\n\tsv.q C010, %0" VFPU_END
                     : "=m"(t) : "r"(a), "r"(m) : "memory");
    d->x = t[0];
    d->y = t[1];
    d->z = t[2];
    d->w = 1.0f;
    return d;
}

/* @implements 0x0a67fc us f_0a67fc
   WHAT IT DOES: Re-orthonormalises the three rows of a rotation in place (Gram-Schmidt) in
   the row order chosen by k: the first row is normalised, the second made perpendicular to it
   and normalised, the third replaced by their cross product. */
Vec4 *f_0a67fc(Vec4 *m, int k)
{
    Vec4 *a = &m[D_1ac12c[k][0]];
    Vec4 *b = &m[D_1ac12c[k][1]];
    Vec4 *c = &m[D_1ac12c[k][2]];
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tvdot.t S010, C000, C000\n\tvrsq.s S011, S010\n\tvscl.t C100, C000, S011\n\t"
                     "lv.q C000, 0(%1)\n\tvdot.t S020, C100, C000\n\tvscl.t C010, C100, S020\n\tvsub.t C000, C000, C010\n\t"
                     "vdot.t S010, C000, C000\n\tvrsq.s S011, S010\n\tvscl.t C110, C000, S011\n\tvcrsp.t C120, C100, C110\n\t"
                     "sv.q C100, 0(%0)\n\tsv.q C110, 0(%1)\n\tsv.q C120, 0(%2)" VFPU_END
                     : : "r"(a), "r"(b), "r"(c) : "memory");
    return m;
}

/* @implements 0x0a687c us f_0a687c
   WHAT IT DOES: Multiplies a 3x3 rotation (rows of four) in place by another. */
Vec4 *f_0a687c(Vec4 *d, const Vec4 *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000, 0(%0)\n\tlv.q C010, 16(%0)\n\tlv.q C020, 32(%0)\n\tlv.q C100, 0(%1)\n\t"
                     "lv.q C110, 16(%1)\n\tlv.q C120, 32(%1)\n\tvmmul.t M200, M000, M100\n\tsv.q C200, 0(%0)\n\t"
                     "sv.q C210, 16(%0)\n\tsv.q C220, 32(%0)" VFPU_END
                     : : "r"(d), "r"(m) : "memory");
    return d;
}

/* @implements 0x0a68b0 us f_0a68b0
   WHAT IT DOES: Builds a rotation (three rows) looking along a direction, with the world y
   axis as up: the third row is the unit negated direction, the second up made perpendicular to
   it, the first their cross product. */
Vec4 *f_0a68b0(Vec4 *m, const Vec4 *dir)
{
    Vec4 up;

    up.z = up.x = 0.0f;
    up.w = up.y = 1.0f;
    __asm__ volatile(VFPU_BEGIN "vzero.t C010\n\tlv.q C000, 0(%1)\n\tvsub.t C000, C010, C000\n\tvdot.t S010, C000, C000\n\t"
                     "vrsq.s S011, S010\n\tvscl.t C120, C000, S011\n\tlv.q C110, %2\n\tvdot.t S010, C110, C120\n\t"
                     "vscl.t C020, C120, S010\n\tvsub.t C110, C110, C020\n\tvdot.t S010, C110, C110\n\tvrsq.s S011, S010\n\t"
                     "vscl.t C110, C110, S011\n\tvcrsp.t C100, C110, C120\n\tsv.q C100, 0(%0)\n\tsv.q C110, 16(%0)\n\t"
                     "sv.q C120, 32(%0)" VFPU_END
                     : : "r"(m), "r"(dir), "m"(up) : "memory");
    return m;
}

/* @implements 0x0a6920 us f_0a6920
   WHAT IT DOES: Builds a rotation (three rows) looking along a direction with a given up
   vector, as f_0a68b0. The default up vector is still built on the stack but not used. */
Vec4 *f_0a6920(Vec4 *m, const Vec4 *dir, const Vec4 *u)
{
    Vec4 up;

    up.z = up.x = 0.0f;
    up.w = up.y = 1.0f;
    __asm__ volatile(VFPU_BEGIN "vzero.t C010\n\tlv.q C000, 0(%1)\n\tvsub.t C000, C010, C000\n\tvdot.t S010, C000, C000\n\t"
                     "vrsq.s S011, S010\n\tvscl.t C120, C000, S011\n\tlv.q C110, 0(%2)\n\tvdot.t S010, C110, C120\n\t"
                     "vscl.t C020, C120, S010\n\tvsub.t C110, C110, C020\n\tvdot.t S010, C110, C110\n\tvrsq.s S011, S010\n\t"
                     "vscl.t C110, C110, S011\n\tvcrsp.t C100, C110, C120\n\tsv.q C100, 0(%0)\n\tsv.q C110, 16(%0)\n\t"
                     "sv.q C120, 32(%0)" VFPU_END
                     : : "r"(m), "r"(dir), "r"(u), "m"(up) : "memory");
    return m;
}
