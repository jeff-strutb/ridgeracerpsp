/* @cflags: -fno-math-errno */

/* Car orientation matrices and matrix helpers (retail 0x0a6990 to 0x0a6f6c). Three rotations
   turn a 3x3 orientation about one axis by an angle given as float bits in a register (scaled
   by 2/pi into the vector unit's quarter-turn units). The rest multiply and transform on the
   vector unit, set an identity matrix, and wrap calls to routines in other object files.
   Results are written through the first argument and returned. */

/* The vector unit code is written in assembly with the assembler's reordering off, so it never
   moves a vector store into a following delay slot. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

typedef union {
    unsigned int u;
    float f;
} Bits;

/* A 3x3 orientation: three columns of four floats. */
typedef struct Mat3 {
    float col[3][4];
} __attribute__((aligned(16))) Mat3;

/* A 4x4 matrix in sixteen floats. */
typedef struct Mat4 {
    float m[16];
} Mat4;

/* A vector of four floats. */
typedef struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

void f_099b98(float *t, unsigned int ab);
void f_0a365c();
void f_0a2cd8();
void f_0a2fb8(void);
void f_0a318c();
void f_09b8b8(void);
void f_09bb28();
void f_09bc7c();
void f_09c43c(void);
void f_09c4e8(void);
void f_09c618();
void f_09c54c();
void f_09c5b8(void);
void f_09c720();

/* @implements 0x0a6990 us f_0a6990
   WHAT IT DOES: Turns a 3x3 orientation about its x axis by the angle (float bits in the second
   argument, scaled by 2/pi), and returns it. */
Mat3 *f_0a6990(Mat3 *m, unsigned int ab)
{
    Bits a;
    float t[2];
    float x;

    a.u = ab;
    x = a.f;
    t[0] = x * 0.6366197466850281f;
    f_099b98(t, ab);
    t[1] = t[0];
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%0)\n\tlv.q C010.q, 16(%0)\n\tlv.q C020.q, 32(%0)\n\t"
                     "lv.s S100.s, %1\n\tvmidt.t M200.t\n\t"
                     "vrot.t C210.t, S100.s, [0,c,s]\n\tvrot.t C220.t, S100.s, [0,-s,c]\n\t"
                     "vmmul.t M100.t, M000.t, M200.t\n\t"
                     "sv.q C100.q, 0(%0)\n\tsv.q C110.q, 16(%0)\n\tsv.q C120.q, 32(%0)" VFPU_END
                     : : "r"(m), "m"(t[1]) : "memory");
    return m;
}

/* @implements 0x0a6a04 us f_0a6a04
   WHAT IT DOES: Turns a 3x3 orientation about its y axis by the angle (float bits in the second
   argument, scaled by 2/pi), and returns it. */
Mat3 *f_0a6a04(Mat3 *m, unsigned int ab)
{
    Bits a;
    float t[2];
    float x;

    a.u = ab;
    x = a.f;
    t[0] = x * 0.6366197466850281f;
    f_099b98(t, ab);
    t[1] = t[0];
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%0)\n\tlv.q C010.q, 16(%0)\n\tlv.q C020.q, 32(%0)\n\t"
                     "lv.s S100.s, %1\n\tvmidt.t M200.t\n\t"
                     "vrot.t C200.t, S100.s, [c,0,-s]\n\tvrot.t C220.t, S100.s, [s,0,c]\n\t"
                     "vmmul.t M100.t, M000.t, M200.t\n\t"
                     "sv.q C100.q, 0(%0)\n\tsv.q C110.q, 16(%0)\n\tsv.q C120.q, 32(%0)" VFPU_END
                     : : "r"(m), "m"(t[1]) : "memory");
    return m;
}

/* @implements 0x0a6a78 us f_0a6a78
   WHAT IT DOES: Turns a 3x3 orientation about its z axis by the angle (float bits in the second
   argument, scaled by 2/pi), and returns it. */
Mat3 *f_0a6a78(Mat3 *m, unsigned int ab)
{
    Bits a;
    float t[2];
    float x;

    a.u = ab;
    x = a.f;
    t[0] = x * 0.6366197466850281f;
    f_099b98(t, ab);
    t[1] = t[0];
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%0)\n\tlv.q C010.q, 16(%0)\n\tlv.q C020.q, 32(%0)\n\t"
                     "lv.s S100.s, %1\n\tvmidt.t M200.t\n\t"
                     "vrot.t C200.t, S100.s, [c,s,0]\n\tvrot.t C210.t, S100.s, [-s,c,0]\n\t"
                     "vmmul.t M100.t, M000.t, M200.t\n\t"
                     "sv.q C100.q, 0(%0)\n\tsv.q C110.q, 16(%0)\n\tsv.q C120.q, 32(%0)" VFPU_END
                     : : "r"(m), "m"(t[1]) : "memory");
    return m;
}

/* @implements 0x0a6aec us f_0a6aec
   WHAT IT DOES: Multiplies two 3x3 orientations on the vector unit (first times second) into
   the first argument, and returns it. */
Mat3 *f_0a6aec(Mat3 *d, const Mat3 *a, const Mat3 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%1)\n\tlv.q C010.q, 16(%1)\n\tlv.q C020.q, 32(%1)\n\t"
                     "lv.q C100.q, 0(%2)\n\tlv.q C110.q, 16(%2)\n\tlv.q C120.q, 32(%2)\n\t"
                     "vmmul.t M200.t, M000.t, M100.t\n\t"
                     "sv.q C200.q, 0(%0)\n\tsv.q C210.q, 16(%0)\n\tsv.q C220.q, 32(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a6b20 us f_0a6b20
   WHAT IT DOES: Multiplies two 3x3 orientations on the vector unit (first times second) into
   the first argument, and returns it. The second matrix's last column is loaded a second time
   from the fourth column's place. */
Mat3 *f_0a6b20(Mat3 *d, const Mat3 *a, const Mat3 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%1)\n\tlv.q C010.q, 16(%1)\n\tlv.q C020.q, 32(%1)\n\t"
                     "lv.q C100.q, 0(%2)\n\tlv.q C110.q, 16(%2)\n\tlv.q C120.q, 32(%2)\n\t"
                     "lv.q C120.q, 48(%2)\n\t"
                     "vmmul.t M200.t, M000.t, M100.t\n\t"
                     "sv.q C200.q, 0(%0)\n\tsv.q C210.q, 16(%0)\n\tsv.q C220.q, 32(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a6b58 us f_0a6b58
   WHAT IT DOES: Multiplies two 3x3 orientations on the vector unit, the second one taken from
   its vector-unit register bank E100, into the first argument, and returns it. */
Mat3 *f_0a6b58(Mat3 *d, const Mat3 *a, const Mat3 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%1)\n\tlv.q C010.q, 16(%1)\n\tlv.q C020.q, 32(%1)\n\t"
                     "lv.q C100.q, 0(%2)\n\tlv.q C110.q, 16(%2)\n\tlv.q C120.q, 32(%2)\n\t"
                     "vmmul.t M200.t, M000.t, E100.t\n\t"
                     "sv.q C200.q, 0(%0)\n\tsv.q C210.q, 16(%0)\n\tsv.q C220.q, 32(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a6b8c us f_0a6b8c
   WHAT IT DOES: Multiplies two 3x3 orientations on the vector unit, the first one taken from
   its vector-unit register bank E000, into the first argument, and returns it. */
Mat3 *f_0a6b8c(Mat3 *d, const Mat3 *a, const Mat3 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%1)\n\tlv.q C010.q, 16(%1)\n\tlv.q C020.q, 32(%1)\n\t"
                     "lv.q C100.q, 0(%2)\n\tlv.q C110.q, 16(%2)\n\tlv.q C120.q, 32(%2)\n\t"
                     "vmmul.t M200.t, E000.t, M100.t\n\t"
                     "sv.q C200.q, 0(%0)\n\tsv.q C210.q, 16(%0)\n\tsv.q C220.q, 32(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a6bc0 us f_0a6bc0
   WHAT IT DOES: Multiplies two 3x3 orientations on the vector unit, both taken from their
   vector-unit register banks E000 and E100, into the first argument, and returns it. */
Mat3 *f_0a6bc0(Mat3 *d, const Mat3 *a, const Mat3 *b)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%1)\n\tlv.q C010.q, 16(%1)\n\tlv.q C020.q, 32(%1)\n\t"
                     "lv.q C100.q, 0(%2)\n\tlv.q C110.q, 16(%2)\n\tlv.q C120.q, 32(%2)\n\t"
                     "vmmul.t M200.t, E000.t, E100.t\n\t"
                     "sv.q C200.q, 0(%0)\n\tsv.q C210.q, 16(%0)\n\tsv.q C220.q, 32(%0)" VFPU_END
                     : : "r"(d), "r"(a), "r"(b) : "memory");
    return d;
}

/* @implements 0x0a6bf4 us f_0a6bf4
   WHAT IT DOES: Transforms a 3D vector by the vector-unit matrix E100 (rotation part of a
   4x3 orientation) into the first argument, and returns it. */
Vec4 *f_0a6bf4(Vec4 *d, const Mat3 *m, const Vec4 *v)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%2)\n\t"
                     "lv.q C100.q, 0(%1)\n\tlv.q C110.q, 16(%1)\n\tlv.q C120.q, 32(%1)\n\t"
                     "vtfm3.t C010.t, E100.t, C000.t\n\t"
                     "sv.q C010.q, 0(%0)" VFPU_END
                     : : "r"(d), "r"(m), "r"(v) : "memory");
    return d;
}

/* @implements 0x0a6c18 us f_0a6c18
   WHAT IT DOES: Transforms a 3D vector by the matrix M100 (rotation part of a 4x3 orientation)
   into the first argument, and returns it. */
Vec4 *f_0a6c18(Vec4 *d, const Mat3 *m, const Vec4 *v)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C000.q, 0(%2)\n\t"
                     "lv.q C100.q, 0(%1)\n\tlv.q C110.q, 16(%1)\n\tlv.q C120.q, 32(%1)\n\t"
                     "vtfm3.t C010.t, M100.t, C000.t\n\t"
                     "sv.q C010.q, 0(%0)" VFPU_END
                     : : "r"(d), "r"(m), "r"(v) : "memory");
    return d;
}

/* @implements 0x0a6c3c us f_0a6c3c
   WHAT IT DOES: Sets a 4x4 matrix to the identity on the vector unit, and returns it. */
Mat4 *f_0a6c3c(Mat4 *m)
{
    int pad[4];

    pad[0] = (int)m;
    __asm__ volatile(VFPU_BEGIN "lv.q C100.q, 0($sp)\n\tlv.q C110.q, 16($sp)\n\t"
                     "lv.q C120.q, 32($sp)\n\tlv.q C130.q, 48($sp)\n\t"
                     "vmidt.q M100.q\n\t"
                     "sv.q C100.q, 0(%0)\n\tsv.q C110.q, 16(%0)\n\tsv.q C120.q, 32(%0)\n\t"
                     "sv.q C130.q, 48(%0)" VFPU_END
                     : : "r"(m) : "memory");
    return m;
}

/* @implements 0x0a6c74 us f_0a6c74
   WHAT IT DOES: Calls the routine at 0x0a2fb8 with no arguments. */
void f_0a6c74(void)
{
    f_0a2fb8();
}

/* @implements 0x0a6c90 us f_0a6c90
   WHAT IT DOES: Computes a 64-byte matrix product through a temporary with the routine at
   0x0a365c (given the second argument and the third one), then copies the result into the
   first argument, and returns it. */
Mat4 *f_0a6c90(Mat4 *d, const Mat4 *src)
{
    Mat4 t;

    f_0a365c(&t, d, src);
    *d = t;
    return d;
}

/* @implements 0x0a6cfc us f_0a6cfc
   WHAT IT DOES: Calls the routine at 0x0a318c on the argument and returns the argument. */
void *f_0a6cfc(void *d)
{
    f_0a318c(d);
    return d;
}

/* @implements 0x0a6d24 us f_0a6d24
   WHAT IT DOES: Calls the routine at 0x0a365c on the argument and returns the argument. */
void *f_0a6d24(void *d)
{
    f_0a365c(d);
    return d;
}

/* @implements 0x0a6d4c us f_0a6d4c
   WHAT IT DOES: Calls the routine at 0x0a2cd8 on the argument and returns the argument. */
void *f_0a6d4c(void *d)
{
    f_0a2cd8(d);
    return d;
}

/* @implements 0x0a6d74 us f_0a6d74
   WHAT IT DOES: Calls the routine at 0x09b8b8 with no arguments. */
void f_0a6d74(void)
{
    f_09b8b8();
}

/* @implements 0x0a6d90 us f_0a6d90
   WHAT IT DOES: Computes a 64-byte matrix product through a temporary with the routine at
   0x09bb28 (given the second argument and the third one), then copies the result into the
   first argument, and returns it. */
Mat4 *f_0a6d90(Mat4 *d, const Mat4 *src)
{
    Mat4 t;

    f_09bb28(&t, d, src);
    *d = t;
    return d;
}

/* @implements 0x0a6dfc us f_0a6dfc
   WHAT IT DOES: Calls the routine at 0x09bb28 on the argument and returns the argument. */
void *f_0a6dfc(void *d)
{
    f_09bb28(d);
    return d;
}

/* @implements 0x0a6e24 us f_0a6e24
   WHAT IT DOES: Calls the routine at 0x09bc7c on the argument and returns the argument. */
void *f_0a6e24(void *d)
{
    f_09bc7c(d);
    return d;
}

/* @implements 0x0a6e4c us f_0a6e4c
   WHAT IT DOES: Calls the routine at 0x09c43c with no arguments. */
void f_0a6e4c(void)
{
    f_09c43c();
}

/* @implements 0x0a6e68 us f_0a6e68
   WHAT IT DOES: Calls the routine at 0x09c4e8 with no arguments. */
void f_0a6e68(void)
{
    f_09c4e8();
}

/* @implements 0x0a6e84 us f_0a6e84
   WHAT IT DOES: Computes a 16-byte vector through a temporary with the routine at 0x09c618
   (given the second argument and the third one), then copies it into the first argument, and
   returns it. */
Vec4 *f_0a6e84(Vec4 *d, const Vec4 *src)
{
    Vec4 t;

    f_09c618(&t, d, src);
    *d = t;
    return d;
}

/* @implements 0x0a6ed8 us f_0a6ed8
   WHAT IT DOES: Calls the routine at 0x09c54c on the argument and returns the argument. */
void *f_0a6ed8(void *d)
{
    f_09c54c(d);
    return d;
}

/* @implements 0x0a6f00 us f_0a6f00
   WHAT IT DOES: Calls the routine at 0x09c5b8 with no arguments. */
void f_0a6f00(void)
{
    f_09c5b8();
}

/* @implements 0x0a6f1c us f_0a6f1c
   WHAT IT DOES: Calls the routine at 0x09c618 on the argument and returns the argument. */
void *f_0a6f1c(void *d)
{
    f_09c618(d);
    return d;
}

/* @implements 0x0a6f44 us f_0a6f44
   WHAT IT DOES: Calls the routine at 0x09c720 on the argument and returns the argument. */
void *f_0a6f44(void *d)
{
    f_09c720(d);
    return d;
}
