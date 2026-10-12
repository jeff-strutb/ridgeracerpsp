/* Transform building (retail 0x0281d8 to 0x028b30): rotations, translations and scales applied
   to the current transform M700 on the vector unit, rotation matrices about an axis, Euler
   angle matrices, and the planar shadow matrices that flatten a model onto a plane along a
   light direction. Angles are in radians; the vector unit's sine and cosine take quarter
   turns, so every angle is first multiplied by 2/pi. */

/* The vector unit code is written in assembly with the assembler's reordering off, so it never
   moves an instruction into a following delay slot. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[4][4];
} __attribute__((aligned(16)));

extern "C" {
void f_028d94(Matrix *m);
void f_028e9c(const Matrix *m);
Vec4 *f_028128(Vec4 *d, const Vec4 *a);
}

/* The vector unit's cosine and sine of an angle given in quarter turns. */
static inline float VCos(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvcos.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}

static inline float VSin(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvsin.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}

extern "C" {

void f_02842c(void);
void f_0284bc(float a);
void f_0284fc(float a);
void f_02853c(float a);
void f_028748(const Matrix *m);
void f_0287a0(void);
void f_028840(const Vec4 *v);
void f_02889c(Matrix *m, Vec4 plane, const float *light);

/* @implements 0x0281d8 us f_0281d8
   WHAT IT DOES: Rotates a vector by the inverse of the current transform's rotation (its
   transpose), leaving the current transform unchanged. */
Vec4 *f_0281d8(Vec4 *d, const Vec4 *a)
{
    Matrix save;

    f_028d94(&save);
    f_0287a0();
    f_028128(d, a);
    f_028e9c(&save);
    return d;
}

/* @draft 0x02822c us f_02822c
   WHAT IT DOES: Builds the matrix of a rotation by an angle about an axis (a unit vector). */
Matrix *f_02822c(Matrix *m, const float *axis, float angle)
{
    float a = angle * 0.636619772f;
    float c = VCos(a);
    float s = VSin(a);
    float x = axis[0], y = axis[1], z = axis[2];
    float t = 1.0f - c;

    m->m[0][0] = c + x * x * t;
    m->m[0][1] = x * y * t + s * z;
    m->m[0][2] = x * z * t - s * y;
    m->m[1][0] = x * y * t - s * z;
    m->m[1][1] = c + y * y * t;
    m->m[1][2] = y * z * t + s * x;
    m->m[2][0] = x * z * t + s * y;
    m->m[2][1] = y * z * t - s * x;
    m->m[2][2] = c + z * z * t;
    m->m[3][2] = 0.0f;
    m->m[3][3] = 1.0f;
    m->m[0][3] = 0.0f;
    m->m[1][3] = 0.0f;
    m->m[2][3] = 0.0f;
    m->m[3][0] = 0.0f;
    m->m[3][1] = 0.0f;
    return m;
}

/* @draft 0x02832c us f_02832c
   WHAT IT DOES: Builds the matrix of a rotation by an angle about an axis, in the opposite
   direction to f_02822c (its transpose). */
Matrix *f_02832c(Matrix *m, const float *axis, float angle)
{
    float a = angle * 0.636619772f;
    float c = VCos(a);
    float s = VSin(a);
    float x = axis[0], y = axis[1], z = axis[2];
    float t = 1.0f - c;

    m->m[0][0] = c + x * x * t;
    m->m[0][1] = x * y * t - s * z;
    m->m[0][2] = x * z * t + s * y;
    m->m[1][0] = x * y * t + s * z;
    m->m[1][1] = c + y * y * t;
    m->m[1][2] = y * z * t - s * x;
    m->m[2][0] = x * z * t - s * y;
    m->m[2][1] = y * z * t + s * x;
    m->m[2][2] = c + z * z * t;
    m->m[3][2] = 0.0f;
    m->m[3][3] = 1.0f;
    m->m[0][3] = 0.0f;
    m->m[1][3] = 0.0f;
    m->m[2][3] = 0.0f;
    m->m[3][0] = 0.0f;
    m->m[3][1] = 0.0f;
    return m;
}

/* @implements 0x02842c us f_02842c
   WHAT IT DOES: Sets the current transform to the identity. */
void f_02842c(void)
{
    __asm__ volatile(VFPU_BEGIN "vmidt.q M700" VFPU_END : : : "memory");
}

/* @implements 0x028438 us f_028438
   WHAT IT DOES: Sets the current transform to a rotation about the x axis. */
void f_028438(float angle)
{
    float a = angle * 0.636619772f;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tvmidt.q M700\n\tvrot.t C710, S400, [0, c, s]\n\t"
                     "vrot.t C720, S400, [0, -s, c]" VFPU_END
                     : : "m"(a) : "memory");
}

/* @implements 0x028464 us f_028464
   WHAT IT DOES: Sets the current transform to a rotation about the y axis. */
void f_028464(float angle)
{
    float a = angle * 0.636619772f;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tvmidt.q M700\n\tvrot.t C700, S400, [c, 0, -s]\n\t"
                     "vrot.t C720, S400, [s, 0, c]" VFPU_END
                     : : "m"(a) : "memory");
}

/* @implements 0x028490 us f_028490
   WHAT IT DOES: Sets the current transform to a rotation about the z axis. */
void f_028490(float angle)
{
    float a = angle * 0.636619772f;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tvmidt.q M700\n\tvrot.t C700, S400, [c, s, 0]\n\t"
                     "vrot.t C710, S400, [-s, c, 0]" VFPU_END
                     : : "m"(a) : "memory");
}

/* @implements 0x0284bc us f_0284bc
   WHAT IT DOES: Applies a rotation about the x axis to the current transform. */
void f_0284bc(float angle)
{
    float a = angle * 0.636619772f;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tvmidt.q M300\n\tvrot.t C310, S400, [0, c, s]\n\t"
                     "vrot.t C320, S400, [0, -s, c]\n\tvmmul.q M400, M700, M300\n\t"
                     "vmov.q C700, C400\n\tvmov.q C710, C410\n\tvmov.q C720, C420\n\tvmov.q C730, C430" VFPU_END
                     : : "m"(a) : "memory");
}

/* @implements 0x0284fc us f_0284fc
   WHAT IT DOES: Applies a rotation about the y axis to the current transform. */
void f_0284fc(float angle)
{
    float a = angle * 0.636619772f;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tvmidt.q M300\n\tvrot.t C300, S400, [c, 0, -s]\n\t"
                     "vrot.t C320, S400, [s, 0, c]\n\tvmmul.q M400, M700, M300\n\t"
                     "vmov.q C700, C400\n\tvmov.q C710, C410\n\tvmov.q C720, C420\n\tvmov.q C730, C430" VFPU_END
                     : : "m"(a) : "memory");
}

/* @implements 0x02853c us f_02853c
   WHAT IT DOES: Applies a rotation about the z axis to the current transform. */
void f_02853c(float angle)
{
    float a = angle * 0.636619772f;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tvmidt.q M300\n\tvrot.t C300, S400, [c, s, 0]\n\t"
                     "vrot.t C310, S400, [-s, c, 0]\n\tvmmul.q M400, M700, M300\n\t"
                     "vmov.q C700, C400\n\tvmov.q C710, C410\n\tvmov.q C720, C420\n\tvmov.q C730, C430" VFPU_END
                     : : "m"(a) : "memory");
}

/* @implements 0x02857c us f_02857c
   WHAT IT DOES: Builds the matrix of Euler angle rotations about z, then y, then x, leaving the
   current transform unchanged. */
Matrix *f_02857c(Matrix *m, float x, float y, float z)
{
    Matrix save;

    f_028d94(&save);
    f_02842c();
    f_02853c(z);
    f_0284fc(y);
    f_0284bc(x);
    f_028d94(m);
    f_028e9c(&save);
    return m;
}

/* @implements 0x0285fc us f_0285fc
   WHAT IT DOES: Builds the matrix of Euler angle rotations about x, then y, then z, leaving the
   current transform unchanged. */
Matrix *f_0285fc(Matrix *m, float x, float y, float z)
{
    Matrix save;

    f_028d94(&save);
    f_02842c();
    f_0284bc(x);
    f_0284fc(y);
    f_02853c(z);
    f_028d94(m);
    f_028e9c(&save);
    return m;
}

/* @implements 0x02867c us f_02867c
   WHAT IT DOES: Builds the matrix of Euler angle rotations about y, then x, then z, leaving the
   current transform unchanged. */
Matrix *f_02867c(Matrix *m, float x, float y, float z)
{
    Matrix save;

    f_028d94(&save);
    f_02842c();
    f_0284fc(y);
    f_0284bc(x);
    f_02853c(z);
    f_028d94(m);
    f_028e9c(&save);
    return m;
}

/* @implements 0x0286fc us f_0286fc
   WHAT IT DOES: Applies Euler angle rotations (z, then y, then x) to the current transform. */
void f_0286fc(float x, float y, float z)
{
    Matrix m;

    f_028748(f_02857c(&m, x, y, z));
}

/* @implements 0x028720 us f_028720
   WHAT IT DOES: Applies a rotation by an angle about an axis to the current transform. */
void f_028720(const float *axis, float angle)
{
    Matrix m;

    f_028748(f_02822c(&m, axis, angle));
}

/* @implements 0x028748 us f_028748
   WHAT IT DOES: Multiplies the current transform by a matrix. */
void f_028748(const Matrix *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C300, 0(%0)\n\tlv.q C310, 16(%0)\n\tlv.q C320, 32(%0)\n\tlv.q C330, 48(%0)\n\t"
                     "vmmul.q M400, M700, M300\n\t"
                     "vmov.q C700, C400\n\tvmov.q C710, C410\n\tvmov.q C720, C420\n\tvmov.q C730, C430" VFPU_END
                     : : "r"(m) : "memory");
}

/* @implements 0x028774 us f_028774
   WHAT IT DOES: Multiplies the current transform by the transpose of a matrix. */
void f_028774(const Matrix *m)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C300, 0(%0)\n\tlv.q C310, 16(%0)\n\tlv.q C320, 32(%0)\n\tlv.q C330, 48(%0)\n\t"
                     "vmmul.q M400, M700, E300\n\t"
                     "vmov.q C700, C400\n\tvmov.q C710, C410\n\tvmov.q C720, C420\n\tvmov.q C730, C430" VFPU_END
                     : : "r"(m) : "memory");
}

/* @implements 0x0287a0 us f_0287a0
   WHAT IT DOES: Replaces the current transform's rotation with its transpose (its inverse for
   a pure rotation); the translation is kept. */
void f_0287a0(void)
{
    __asm__ volatile(VFPU_BEGIN "vmmov.t M400, M700\n\tvmmov.t M700, E400" VFPU_END : : : "memory");
}

/* @implements 0x0287b0 us f_0287b0
   WHAT IT DOES: Inverts the current transform, taken as a rotation plus a translation. */
void f_0287b0(void)
{
    __asm__ volatile(VFPU_BEGIN "vmmov.t M400, M700\n\tvtfm3.t C430, M700, C730\n\tvmmov.t M700, E400\n\t"
                     "vmov.t C730, C430\n\tvneg.t C730, C730" VFPU_END : : : "memory");
}

/* @implements 0x0287cc us f_0287cc
   WHAT IT DOES: Applies a translation to the current transform. */
void f_0287cc(float x, float y, float z)
{
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tlv.s S401, %1\n\tlv.s S402, %2\n\t"
                     "vtfm3.t C410, E700, C400\n\tvadd.t C730, C730, C410" VFPU_END
                     : : "m"(x), "m"(y), "m"(z) : "memory");
}

/* @implements 0x0287f8 us f_0287f8
   WHAT IT DOES: Applies a translation, given as a vector, to the current transform. */
void f_0287f8(const Vec4 *v)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%0)\n\tvtfm3.t C410, E700, C400\n\tvadd.t C730, C730, C410" VFPU_END
                     : : "r"(v) : "memory");
}

/* @implements 0x02880c us f_02880c
   WHAT IT DOES: Sets the current transform's translation. */
void f_02880c(float x, float y, float z)
{
    Vec4 v;

    v.w = 1.0f;
    v.x = x;
    v.y = y;
    v.z = z;
    f_028840(&v);
}

/* @implements 0x028840 us f_028840
   WHAT IT DOES: Sets the current transform's translation from a vector (all four
   components). */
void f_028840(const Vec4 *v)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C730, 0(%0)" VFPU_END : : "r"(v) : "memory");
}

/* @implements 0x02884c us f_02884c
   WHAT IT DOES: Applies a scale along each axis to the current transform. */
void f_02884c(float x, float y, float z)
{
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %0\n\tlv.s S401, %1\n\tlv.s S402, %2\n\t"
                     "vscl.t C300, C700, S400\n\tvscl.t C310, C710, S401\n\tvscl.t C320, C720, S402\n\t"
                     "vmmov.t M700, M300" VFPU_END
                     : : "m"(x), "m"(y), "m"(z) : "memory");
}

/* @implements 0x028880 us f_028880
   WHAT IT DOES: Applies a scale along each axis, given as a vector, to the current
   transform. */
void f_028880(const Vec4 *v)
{
    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%0)\n\t"
                     "vscl.t C300, C700, S400\n\tvscl.t C310, C710, S401\n\tvscl.t C320, C720, S402\n\t"
                     "vmmov.t M700, M300" VFPU_END
                     : : "r"(v) : "memory");
}

/* @draft 0x02889c us f_02889c
   WHAT IT DOES: Builds the matrix that projects points onto a plane along the line from a
   point light, for drawing a shadow flattened on the ground. */
void f_02889c(Matrix *m, Vec4 p, const float *l)
{
    float d = p.x * l[0] + p.y * l[1] + p.z * l[2] + p.w;
    float k = 1.0f / (d - ((-p.x - p.y - p.z) + (d - p.w)));

    m->m[0][0] = (d - l[0] * p.x) * k;
    m->m[1][0] = -l[0] * p.y * k;
    m->m[2][0] = -l[0] * p.z * k;
    m->m[3][0] = -l[0] * p.w * k;
    m->m[0][1] = -l[1] * p.x * k;
    m->m[1][1] = (d - l[1] * p.y) * k;
    m->m[2][1] = -l[1] * p.z * k;
    m->m[3][1] = -l[1] * p.w * k;
    m->m[0][2] = -l[2] * p.x * k;
    m->m[1][2] = -l[2] * p.y * k;
    m->m[2][2] = (d - l[2] * p.z) * k;
    m->m[3][2] = -l[2] * p.w * k;
    m->m[3][3] = 1.0f;
    m->m[0][3] = 0.0f;
    m->m[1][3] = 0.0f;
    m->m[2][3] = 0.0f;
}

/* @implements 0x028a00 us f_028a00
   WHAT IT DOES: Applies to the current transform the matrix that projects points onto a plane
   along a light direction, for drawing a shadow flattened on the ground. */
void f_028a00(const Vec4 *p, const float *l)
{
    Matrix m;
    float d = p->x * l[0] + p->y * l[1] + p->z * l[2];
    float k = 1.0f / d;

    m.m[0][0] = (d - l[0] * p->x) * k;
    m.m[1][0] = -l[0] * p->y * k;
    m.m[2][0] = -l[0] * p->z * k;
    m.m[3][0] = -l[0] * p->w * k;
    m.m[0][1] = -l[1] * p->x * k;
    m.m[1][1] = (d - l[1] * p->y) * k;
    m.m[2][1] = -l[1] * p->z * k;
    m.m[3][1] = -l[1] * p->w * k;
    m.m[0][2] = -l[2] * p->x * k;
    m.m[1][2] = -l[2] * p->y * k;
    m.m[2][2] = (d - l[2] * p->z) * k;
    m.m[3][2] = -l[2] * p->w * k;
    m.m[3][3] = 1.0f;
    m.m[0][3] = 0.0f;
    m.m[1][3] = 0.0f;
    m.m[2][3] = 0.0f;
    f_028748(&m);
}

/* @draft 0x028b04 us f_028b04
   WHAT IT DOES: Sets the current transform to the point light shadow matrix of f_02889c. */
void f_028b04(Vec4 p, const float *l)
{
    Matrix m;

    f_02889c(&m, p, l);
    f_028e9c(&m);
}

}
