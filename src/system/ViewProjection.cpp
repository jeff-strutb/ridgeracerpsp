/* The camera and projection object file (retail 0x0cd4b4 to 0x0ce068). The view matrix is
   kept on the matrix stack's second stack and the projection matrix on its first; this file
   reads and writes them, builds them (look-at, Euler angle and axis rotations, orthographic and
   perspective projections) and hands them to the graphics engine. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[16];
} __attribute__((aligned(16)));

/* Writes the negation of a vector's first three components. */
static inline void SetNeg(Vec4 *d, const Vec4 *s)
{
    d->x = -s->x;
    d->y = -s->y;
    d->z = -s->z;
}

/* The same from a plain float array. */
static inline void SetNegF(Vec4 *d, const float *s)
{
    d->x = -s[0];
    d->y = -s[1];
    d->z = -s[2];
}

extern "C" {
void f_028cd4(void);
void f_028ce8(void);
void f_028d94(Matrix *m);
void f_028dac(Matrix *out);
void f_028df0(Matrix *out);
Matrix *f_028e78(void);
Matrix *f_028e84(void);
void f_028e9c(const Matrix *m);
void f_028eb4(const Matrix *m);
void f_028ef8(const Matrix *m);
Vec4 *f_027e0c(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027edc(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027f18(Vec4 *d, const Vec4 *a);
Vec4 *f_027f3c(Vec4 *d, const Vec4 *a);
Vec4 *f_027f5c(Vec4 *d, const Vec4 *a);
Matrix *f_02832c(Matrix *m, const Vec4 *axis, float angle);
Matrix *f_0285fc(Matrix *m, float x, float y, float z);
Matrix *f_02867c(Matrix *m, float x, float y, float z);
float f_0cd3cc(float a);
void f_0ce068(int type, const Matrix *m);
void f_0ce0a8(Matrix *m);
}

/* @implements 0x0cd4b4 us f_0cd4b4
   WHAT IT DOES: Copies the view matrix out. */
void f_0cd4b4(Matrix *out)
{
    f_028dac(out);
}

/* @implements 0x0cd4d0 us f_0cd4d0
   WHAT IT DOES: Sets the view matrix and hands it to the graphics engine. */
void f_0cd4d0(const Matrix *m)
{
    f_028eb4(m);
    f_0ce068(1, m);
}

/* @implements 0x0cd500 us f_0cd500
   WHAT IT DOES: Hands the current view matrix to the graphics engine. */
void f_0cd500(void)
{
    f_0ce068(1, f_028e78());
}

#define VIEW_WORD(k) *p = (m[k] >> 8) | 0x3d000000; p++;

/* @implements 0x0cd528 us f_0cd528
   WHAT IT DOES: Writes the view matrix into a display list as graphics engine commands: the
   matrix upload start, then the twelve entries of its upper 4x3 part. Returns the next free
   word. */
unsigned int *f_0cd528(unsigned int *p)
{
    const unsigned int *m = (const unsigned int *)f_028e78();
    *p = 0x3c000000;
    p++;
    VIEW_WORD(0) VIEW_WORD(1) VIEW_WORD(2)
    VIEW_WORD(4) VIEW_WORD(5) VIEW_WORD(6)
    VIEW_WORD(8) VIEW_WORD(9) VIEW_WORD(10)
    VIEW_WORD(12) VIEW_WORD(13) VIEW_WORD(14)
    return p;
}

/* @implements 0x0cd650 us f_0cd650
   WHAT IT DOES: Pushes the view matrix stack. */
void f_0cd650(void)
{
    f_028cd4();
}

/* @implements 0x0cd66c us f_0cd66c
   WHAT IT DOES: Pops the view matrix stack. */
void f_0cd66c(void)
{
    f_028ce8();
}

/* Sets all sixteen entries of a matrix. */
static inline void SetMatrix(Matrix *m, float a0, float a1, float a2, float a3, float a4, float a5,
                             float a6, float a7, float a8, float a9, float a10, float a11,
                             float a12, float a13, float a14, float a15)
{
    m->m[0] = a0;
    m->m[1] = a1;
    m->m[2] = a2;
    m->m[3] = a3;
    m->m[4] = a4;
    m->m[5] = a5;
    m->m[6] = a6;
    m->m[7] = a7;
    m->m[8] = a8;
    m->m[9] = a9;
    m->m[10] = a10;
    m->m[11] = a11;
    m->m[12] = a12;
    m->m[13] = a13;
    m->m[14] = a14;
    m->m[15] = a15;
}

/* Fills the view matrix from a normalised viewing direction, then moves the eye position into
   its translation. */
static inline __attribute__((always_inline)) void LookAt(const Vec4 *eye, Vec4 *dir, const Vec4 *up)
{
    Vec4 side, top;
    Matrix save;
    Vec4 t;
    Matrix *m;

    f_027edc(&side, up, dir);
    f_027f18(&side, &side);
    f_027edc(&top, dir, &side);
    m = f_028e78();
    SetMatrix(m, side.x, top.x, dir->x, 0.0f,
              side.y, top.y, dir->y, 0.0f,
              side.z, top.z, dir->z, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f);
    f_028d94(&save);
    f_028e9c(m);
    f_027f3c(&t, eye);
    f_028e9c(&save);
    SetNeg((Vec4 *)&m->m[12], &t);
}

/* @draft 0x0cd688 us f_0cd688
   WHAT IT DOES: Builds the view matrix for an eye position looking along a direction, with the
   given up vector.
   DIFFERS: 4 words after the f_028e78 call: retail puts `move s0,v0` before the first matrix
   store and `addiu s1,sp,48; move a0,s1` before the second; ours one store later each. */
void f_0cd688(const Vec4 *eye, const Vec4 *dir, const Vec4 *up)
{
    Vec4 d;

    f_027f18(&d, dir);
    LookAt(eye, &d, up);
}

/* @draft 0x0cd7c0 us f_0cd7c0
   WHAT IT DOES: Builds the view matrix for an eye position looking at a target point, with the
   given up vector.
   DIFFERS: the same 4 scheduling words as f_0cd688. */
void f_0cd7c0(const Vec4 *eye, const Vec4 *at, const Vec4 *up)
{
    Vec4 d;

    f_027e0c(&d, eye, at);
    f_027f18(&d, &d);
    LookAt(eye, &d, up);
}

/* @implements 0x0cd90c us f_0cd90c
   WHAT IT DOES: Builds the view matrix from Euler angles (x, then y, then z) and an eye
   position. */
void f_0cd90c(const Vec4 *eye, float x, float y, float z)
{
    Matrix save;
    Vec4 t;
    Matrix *m = f_028e78();

    f_0285fc(m, x, y, z);
    f_028d94(&save);
    f_028e9c(m);
    f_027f5c(&t, eye);
    f_028e9c(&save);
    SetNegF((Vec4 *)&m->m[12], &t.x);
}

/* @implements 0x0cd9c0 us f_0cd9c0
   WHAT IT DOES: Builds the view matrix from Euler angles (y, then x, then z) and an eye
   position. */
void f_0cd9c0(const Vec4 *eye, float x, float y, float z)
{
    Matrix save;
    Vec4 t;
    Matrix *m = f_028e78();

    f_02867c(m, x, y, z);
    f_028d94(&save);
    f_028e9c(m);
    f_027f5c(&t, eye);
    f_028e9c(&save);
    SetNegF((Vec4 *)&m->m[12], &t.x);
}

static const Vec4 D_1adaf0 = {0.0f, 1.0f, 0.0f, 0.0f};

/* @implements 0x0cda74 us f_0cda74
   WHAT IT DOES: Builds the view matrix as a rotation by an angle about the axis from one point
   to another, then transforms the up direction by it (the result is not kept). */
void f_0cda74(const Vec4 *a, const Vec4 *b, float angle)
{
    Vec4 axis;
    Matrix save;
    Matrix *m;

    f_027e0c(&axis, a, b);
    f_027f18(&axis, &axis);
    m = f_028e78();
    f_02832c(m, &axis, angle);
    Vec4 up = D_1adaf0;
    f_028d94(&save);
    f_028e9c(m);
    f_027f5c(&up, &up);
    f_028e9c(&save);
}

/* @draft 0x0cdb2c us f_0cdb2c
   WHAT IT DOES: Writes the transpose of the view matrix's rotation part (its inverse rotation)
   as a full matrix with no translation. Returns the output.
   DIFFERS: the nine loads are scheduled in another order (retail loads entry 5 last and gives it
   $f2); the stores agree. */
Matrix *f_0cdb2c(Matrix *out)
{
    Matrix *m = f_028e78();
    SetMatrix(out, m->m[0], m->m[4], m->m[8], 0.0f,
              m->m[1], m->m[5], m->m[9], 0.0f,
              m->m[2], m->m[6], m->m[10], 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f);
    return out;
}

/* @draft 0x0cdbc4 us f_0cdbc4
   WHAT IT DOES: Writes the transpose of a matrix's rotation part as a full matrix with no
   translation. Returns the output.
   DIFFERS: as f_0cdb2c, only the load order and FP registers. */
Matrix *f_0cdbc4(const Matrix *m, Matrix *out)
{
    SetMatrix(out, m->m[0], m->m[4], m->m[8], 0.0f,
              m->m[1], m->m[5], m->m[9], 0.0f,
              m->m[2], m->m[6], m->m[10], 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f);
    return out;
}

/* @implements 0x0cdc3c us f_0cdc3c
   WHAT IT DOES: Copies the projection matrix out. */
void f_0cdc3c(Matrix *out)
{
    f_028df0(out);
}

/* @implements 0x0cdc58 us f_0cdc58
   WHAT IT DOES: Sets the projection matrix and hands it to the graphics engine. */
void f_0cdc58(const Matrix *m)
{
    f_028ef8(m);
    f_0ce068(0, m);
}

/* @implements 0x0cdc88 us f_0cdc88
   WHAT IT DOES: Hands the current projection matrix to the graphics engine. */
void f_0cdc88(void)
{
    f_0ce068(0, f_028e84());
}

/* @implements 0x0cdcb0 us f_0cdcb0
   WHAT IT DOES: Builds an orthographic projection matrix from the left, right, bottom, top,
   near and far planes. */
void f_0cdcb0(float l, float r, float b, float t, float n, float f)
{
    float sx = 2.0f / (r - l);
    float sy = 2.0f / (t - b);
    float sz = -2.0f / (f - n);
    float tx = -(r + l) / (r - l);
    float ty = -(t + b) / (t - b);
    float tz = -(f + n) / (f - n);

    SetMatrix(f_028e84(), sx, 0.0f, 0.0f, 0.0f,
              0.0f, sy, 0.0f, 0.0f,
              0.0f, 0.0f, sz, 0.0f,
              tx, ty, tz, 1.0f);
}

/* @implements 0x0cdd90 us f_0cdd90
   WHAT IT DOES: Builds a perspective projection matrix from a field of view angle, an aspect
   ratio and the near and far planes, and passes it on. */
void f_0cdd90(float fov, float aspect, float n, float f)
{
    float t, ta, A, B;
    Matrix *m;

    t = f_0cd3cc(fov);
    ta = t * aspect;
    A = -(f + n) / (f - n);
    B = f * -2.0f * n / (f - n);
    m = f_028e84();
    SetMatrix(m, 1.0f / ta, 0.0f, 0.0f, 0.0f,
              0.0f, 1.0f / t, 0.0f, 0.0f,
              0.0f, 0.0f, A, -1.0f,
              0.0f, 0.0f, B, 0.0f);
    f_0ce0a8(m);
}

/* @implements 0x0cde70 us f_0cde70
   WHAT IT DOES: Builds a perspective projection matrix from a vertical scale, an aspect ratio
   and the near and far planes, and passes it on. */
void f_0cde70(float s, float aspect, float n, float f)
{
    float sx, A, B;
    Matrix *m;

    sx = 1.0f / (1.0f / s * aspect);
    A = -(f + n) / (f - n);
    B = f * -2.0f * n / (f - n);
    m = f_028e84();
    SetMatrix(m, sx, 0.0f, 0.0f, 0.0f,
              0.0f, s, 0.0f, 0.0f,
              0.0f, 0.0f, A, -1.0f,
              0.0f, 0.0f, B, 0.0f);
    f_0ce0a8(m);
}

/* @implements 0x0cdf38 us f_0cdf38
   WHAT IT DOES: Builds an off-centre perspective projection matrix (a field of view angle, an
   aspect ratio, a window offset and the near and far planes) and passes it on. */
void f_0cdf38(float a, float b, float c, float d, float e, float g, float n, float f)
{
    float t, tb, A, B;
    Matrix *mm;
    float *m;
    d = d + d;
    g = g + g;
    t = f_0cd3cc(a);
    tb = t * b;
    A = -(f + n) / (f - n);
    B = f * -2.0f * n / (f - n);
    d = d - c;
    mm = f_028e84();
    m = mm->m;
    m[10] = A;
    m[11] = -1.0f;
    m[15] = m[13] = m[12] = m[7] = m[6] = m[4] = m[3] = m[2] = m[1] = 0.0f;
    m[14] = B;
    m[5] = 1.0f / t * e;
    e = e - g;
    m[0] = 1.0f / tb * c;
    m[8] = d + 1.0f;
    m[9] = e - 1.0f;
    f_0ce0a8(mm);
}
