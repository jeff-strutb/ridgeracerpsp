/* Rotation and transform helpers of the camera math library (TU 210, retail 0x09ae9c to
   0x0a5d48): quaternion and Euler conversions, in-place copies, transform inverses and the
   matrix-times-vector products, and the 3x3 row-times-matrix products walked by a biased row
   pointer. The rest of this object file is in Vector3, Matrix33/34/43/44,
   Matrix43p, MatrixProduct and Quaternion; functions keep C linkage under their retail addresses. */

#include <math.h>

namespace m210 {

struct Vec3 { float v[3]; };
struct Vec4 { float v[4]; };
struct Mat44 { float m[4][4]; };
struct Quat { float v[4]; };
struct Mat33 { float m[3][3]; };
struct Mat34 { float m[3][4]; };

extern "C" {

/* @implements 0x09ee58 us f_09ee58
   WHAT IT DOES: Empty function; returns immediately. */
void f_09ee58() {}
/* @implements 0x09ee60 us f_09ee60
   WHAT IT DOES: Empty function; returns immediately. */
void f_09ee60() {}
/* @implements 0x09f148 us f_09f148
   WHAT IT DOES: Empty function; returns immediately. */
void f_09f148() {}
/* @implements 0x09f150 us f_09f150
   WHAT IT DOES: Empty function; returns immediately. */
void f_09f150() {}

Mat34 f_0a01ac(const Mat34 *a);
Mat44 f_0a2e98(const Mat44 *a);

/* @implements 0x0a0334 us f_0a0334
   WHAT IT DOES: Replaces the 3x4 matrix with the result of f_0a01ac on it (in-place transform) and returns it. */
Mat34 *f_0a0334(Mat34 *a)
{
    *a = f_0a01ac(a);
    return a;
}

/* @implements 0x0a2f50 us f_0a2f50
   WHAT IT DOES: Replaces the 4x4 matrix with the result of f_0a2e98 on it (in-place transform) and returns it. */
Mat44 *f_0a2f50(Mat44 *a)
{
    *a = f_0a2e98(a);
    return a;
}

Mat33 f_09dd08(const Mat33 *a);
void f_09c314(Quat *o, const Vec3 *a);
void f_09d858(Mat33 *o, const Quat *q);
void f_09fd1c(Mat34 *o, const Quat *q);
void f_09e770(Quat *o, const Mat33 *m);
void f_09cc50(Quat *o, const Quat *a, const Quat *b, float t);

/* @implements 0x09de90 us f_09de90
   WHAT IT DOES: Replaces the 3x3 matrix with the result of f_09dd08 on it (in-place inverse) and returns it. */
Mat33 *f_09de90(Mat33 *a)
{
    *a = f_09dd08(a);
    return a;
}

/* @implements 0x09e940 us f_09e940
   WHAT IT DOES: Converts the matrix to a quaternion, interpolates it toward q by t, and writes the result back as a 3x3 matrix. */
Mat33 *f_09e940(Mat33 *d, float tt, const Mat33 *m, const Quat *q)
{
    Quat r;
    Quat a;
    f_09e770(&a, m);
    f_09cc50(&r, &a, q, tt);
    f_09d858(d, &r);
    return d;
}

/* @implements 0x09fb54 us f_09fb54
   WHAT IT DOES: Builds a quaternion from the rotation vector and converts it to a 3x4 matrix in the destination. */
void f_09fb54(Mat34 *d, const Vec3 *a)
{
    Mat34 t;
    Quat q;
    f_09c314(&q, a);
    f_09fd1c(&t, &q);
    *d = t;
}

/* @implements 0x09d6f4 us f_09d6f4
   WHAT IT DOES: Builds a quaternion from the rotation vector and converts it to a 3x3 matrix in the destination. */
void f_09d6f4(Mat33 *d, const Vec3 *a)
{
    Mat33 t;
    Quat q;
    f_09c314(&q, a);
    f_09d858(&t, &q);
    *d = t;
}

void f_0a4160(Vec4 *o, const Mat34 *m, int order);

/* Zeroes three floats with the front end's down-counting array loop. */
#define ZERO3(d) { float *zp = (d)->v; int zi = 2; do { *zp++ = 0; } while (--zi != -1); }

/* @implements 0x09afe4 us f_09afe4
   WHAT IT DOES: Zeroes the first three floats, converts the quaternion to a 3x4 matrix and extracts Euler angles of the given axis order into the destination. */
void f_09afe4(Vec4 *d, const Quat *q, int order)
{
    ZERO3(d)
    Vec4 r;
    Mat34 t;
    f_09fd1c(&t, q);
    f_0a4160(&r, &t, order);
    *d = r;
}

/* @implements 0x09b070 us f_09b070
   WHAT IT DOES: The same as f_09afe4 (twin at another address). */
void f_09b070(Vec4 *d, const Quat *q, int order)
{
    ZERO3(d)
    Vec4 r;
    Mat34 t;
    f_09fd1c(&t, q);
    f_0a4160(&r, &t, order);
    *d = r;
}

struct Vec4a {
    float v[4];
    Vec4a() {}
    Vec4a(float x, float y, float z, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
};
struct Mat33T { Mat33 r; Vec4a t; };
struct Mat34T { Mat34 r; Vec4a t; };

Mat33 *f_09df00(Mat33 *m);
Vec3 *f_09da60(Vec3 *d, const Mat33 *m, const Vec4a *a);
Mat34 *f_0a039c(Mat34 *m);
Vec3 *f_09ff1c(Vec3 *d, const Mat34 *m, const Vec4a *a);

/* @implements 0x0a20f8 us f_0a20f8
   WHAT IT DOES: Inverts a rigid transform in place: transposes the 3x3 rotation, then replaces the translation with the rotation times the negated translation. */
Mat33T *f_0a20f8(Mat33T *m)
{
    f_09df00(&m->r);
    Vec4a *tr = &m->t;
    Vec4a res;
    Vec4a n(-tr->v[0], -tr->v[1], -tr->v[2], 1.0f);
    f_09da60((Vec3 *)&res, &m->r, &n);
    *tr = res;
    return m;
}

/* @implements 0x0a2fb8 us f_0a2fb8
   WHAT IT DOES: The same as f_0a20f8 for the 3x4-row rotation layout (translation at +48). */
Mat34T *f_0a2fb8(Mat34T *m)
{
    f_0a039c(&m->r);
    Vec4a *tr = &m->t;
    Vec4a res;
    Vec4a n(-tr->v[0], -tr->v[1], -tr->v[2], 1.0f);
    f_09ff1c((Vec3 *)&res, &m->r, &n);
    *tr = res;
    return m;
}

/* @implements 0x0a51e0 us f_0a51e0
   WHAT IT DOES: Sets d to the 3x3 matrix times vector a (row dot products). */
Vec3 *f_0a51e0(Vec3 *d, const Vec3 *a, const Mat33 *m)
{
    d->v[0] = a->v[0] * m->m[0][0] + a->v[1] * m->m[0][1] + a->v[2] * m->m[0][2];
    d->v[1] = a->v[0] * m->m[1][0] + a->v[1] * m->m[1][1] + a->v[2] * m->m[1][2];
    d->v[2] = a->v[0] * m->m[2][0] + a->v[1] * m->m[2][1] + a->v[2] * m->m[2][2];
    return d;
}

/* @implements 0x0a5278 us f_0a5278
   WHAT IT DOES: Sets d to the 3x4-padded matrix times vector a (row dot products). */
Vec3 *f_0a5278(Vec3 *d, const Vec3 *a, const Mat34 *m)
{
    d->v[0] = a->v[0] * m->m[0][0] + a->v[1] * m->m[0][1] + a->v[2] * m->m[0][2];
    d->v[1] = a->v[0] * m->m[1][0] + a->v[1] * m->m[1][1] + a->v[2] * m->m[1][2];
    d->v[2] = a->v[0] * m->m[2][0] + a->v[1] * m->m[2][1] + a->v[2] * m->m[2][2];
    return d;
}

/* @implements 0x0a5310 us f_0a5310
   WHAT IT DOES: Sets d to the transposed 3x3 matrix times vector a (column dot products). */
Vec3 *f_0a5310(Vec3 *d, const Vec3 *a, const Mat33 *m)
{
    d->v[0] = a->v[0] * m->m[0][0] + a->v[1] * m->m[1][0] + a->v[2] * m->m[2][0];
    d->v[1] = a->v[0] * m->m[0][1] + a->v[1] * m->m[1][1] + a->v[2] * m->m[2][1];
    d->v[2] = a->v[0] * m->m[0][2] + a->v[1] * m->m[1][2] + a->v[2] * m->m[2][2];
    return d;
}

/* @implements 0x0a53a8 us f_0a53a8
   WHAT IT DOES: Sets d to the transposed 3x4-padded matrix times vector a (column dot products). */
Vec3 *f_0a53a8(Vec3 *d, const Vec3 *a, const Mat34 *m)
{
    d->v[0] = a->v[0] * m->m[0][0] + a->v[1] * m->m[1][0] + a->v[2] * m->m[2][0];
    d->v[1] = a->v[0] * m->m[0][1] + a->v[1] * m->m[1][1] + a->v[2] * m->m[2][1];
    d->v[2] = a->v[0] * m->m[0][2] + a->v[1] * m->m[1][2] + a->v[2] * m->m[2][2];
    return d;
}

/* @implements 0x09ae9c us f_09ae9c
   WHAT IT DOES: Zeroes three floats, builds a quaternion from the rotation vector, converts it to a 3x4 matrix and extracts Euler angles of the given axis order into the destination. */
void f_09ae9c(Vec4 *d, const Vec3 *axis, int order)
{
    ZERO3(d)
    Vec4 r;
    Mat34 t;
    Quat q;
    f_09c314(&q, axis);
    f_09fd1c(&t, &q);
    f_0a4160(&r, &t, order);
    *d = r;
}

/* @implements 0x09af40 us f_09af40
   WHAT IT DOES: The same as f_09ae9c (twin at another address). */
void f_09af40(Vec4 *d, const Vec3 *axis, int order)
{
    ZERO3(d)
    Vec4 r;
    Mat34 t;
    Quat q;
    f_09c314(&q, axis);
    f_09fd1c(&t, &q);
    f_0a4160(&r, &t, order);
    *d = r;
}

/* @implements 0x0a5078 us f_0a5078
   WHAT IT DOES: Replaces the vector in place with the 3x3 matrix times it, with w set to 1.0, and returns it. */
Vec4a *f_0a5078(Vec4a *v, const Mat33 *m)
{
    Vec4a r(v->v[0] * m->m[0][0] + v->v[1] * m->m[0][1] + v->v[2] * m->m[0][2],
            v->v[0] * m->m[1][0] + v->v[1] * m->m[1][1] + v->v[2] * m->m[1][2],
            v->v[0] * m->m[2][0] + v->v[1] * m->m[2][1] + v->v[2] * m->m[2][2], 1.0f);
    *v = r;
    return v;
}

/* @implements 0x0a512c us f_0a512c
   WHAT IT DOES: The same as f_0a5078 for the 3x4-padded matrix. */
Vec4a *f_0a512c(Vec4a *v, const Mat34 *m)
{
    Vec4a r(v->v[0] * m->m[0][0] + v->v[1] * m->m[0][1] + v->v[2] * m->m[0][2],
            v->v[0] * m->m[1][0] + v->v[1] * m->m[1][1] + v->v[2] * m->m[1][2],
            v->v[0] * m->m[2][0] + v->v[1] * m->m[2][1] + v->v[2] * m->m[2][2], 1.0f);
    *v = r;
    return v;
}

/* @draft 0x09d858 us f_09d858
   WHAT IT DOES: Converts a quaternion to a 3x3 rotation matrix (scale 2/norm, or 0 when the norm is tiny). */
void f_09d858(Mat33 *m, const Quat *q)
{
    float x = q->v[0], y = q->v[1], z = q->v[2], w = q->v[3];
    float n = x * x + y * y + z * z + w * w;
    float s = fabsf(n) > 1.1920929e-07f ? 2.0f / n : 0.0f;
    float xs = x * s, ys = y * s, zs = z * s;
    float xx = x * xs, yy = y * ys, zz = z * zs;
    float xy = x * ys, xz = x * zs, yz = y * zs;
    float wx = w * xs, wy = w * ys, wz = w * zs;
    m->m[0][0] = 1.0f - (yy + zz);
    m->m[1][0] = xy + wz;
    m->m[2][0] = xz - wy;
    m->m[0][1] = xy - wz;
    m->m[1][1] = 1.0f - (xx + zz);
    m->m[2][1] = yz + wx;
    m->m[0][2] = xz + wy;
    m->m[1][2] = yz - wx;
    m->m[2][2] = 1.0f - (xx + yy);
}

/* @draft 0x09d770 us f_09d770
   WHAT IT DOES: Converts a quaternion to a 3x3 rotation matrix (scale 2/norm, or 0 when the norm is tiny). */
void f_09d770(Mat33 *m, const Quat *q)
{
    float x = q->v[0], y = q->v[1], z = q->v[2], w = q->v[3];
    float n = x * x + y * y + z * z + w * w;
    float s = fabsf(n) > 1.1920929e-07f ? 2.0f / n : 0.0f;
    float xs = x * s, ys = y * s, zs = z * s;
    float xx = x * xs, yy = y * ys, zz = z * zs;
    float xy = x * ys, xz = x * zs, yz = y * zs;
    float wx = w * xs, wy = w * ys, wz = w * zs;
    m->m[0][0] = 1.0f - (yy + zz);
    m->m[1][0] = xy + wz;
    m->m[2][0] = xz - wy;
    m->m[0][1] = xy - wz;
    m->m[1][1] = 1.0f - (xx + zz);
    m->m[2][1] = yz + wx;
    m->m[0][2] = xz + wy;
    m->m[1][2] = yz - wx;
    m->m[2][2] = 1.0f - (xx + yy);
}

/* @draft 0x09fd1c us f_09fd1c
   WHAT IT DOES: Converts a quaternion to a 3x4-padded rotation matrix (scale 2/norm, or 0 when the norm is tiny). */
void f_09fd1c(Mat34 *m, const Quat *q)
{
    float x = q->v[0], y = q->v[1], z = q->v[2], w = q->v[3];
    float n = x * x + y * y + z * z + w * w;
    float s = fabsf(n) > 1.1920929e-07f ? 2.0f / n : 0.0f;
    float xs = x * s, ys = y * s, zs = z * s;
    float xx = x * xs, yy = y * ys, zz = z * zs;
    float xy = x * ys, xz = x * zs, yz = y * zs;
    float wx = w * xs, wy = w * ys, wz = w * zs;
    m->m[0][0] = 1.0f - (yy + zz);
    m->m[1][0] = xy + wz;
    m->m[2][0] = xz - wy;
    m->m[0][1] = xy - wz;
    m->m[1][1] = 1.0f - (xx + zz);
    m->m[2][1] = yz + wx;
    m->m[0][2] = xz + wy;
    m->m[1][2] = yz - wx;
    m->m[2][2] = 1.0f - (xx + yy);
}

/* @draft 0x09fc34 us f_09fc34
   WHAT IT DOES: Converts a quaternion to a 3x4-padded rotation matrix (scale 2/norm, or 0 when the norm is tiny). */
void f_09fc34(Mat34 *m, const Quat *q)
{
    float x = q->v[0], y = q->v[1], z = q->v[2], w = q->v[3];
    float n = x * x + y * y + z * z + w * w;
    float s = fabsf(n) > 1.1920929e-07f ? 2.0f / n : 0.0f;
    float xs = x * s, ys = y * s, zs = z * s;
    float xx = x * xs, yy = y * ys, zz = z * zs;
    float xy = x * ys, xz = x * zs, yz = y * zs;
    float wx = w * xs, wy = w * ys, wz = w * zs;
    m->m[0][0] = 1.0f - (yy + zz);
    m->m[1][0] = xy + wz;
    m->m[2][0] = xz - wy;
    m->m[0][1] = xy - wz;
    m->m[1][1] = 1.0f - (xx + zz);
    m->m[2][1] = yz + wx;
    m->m[0][2] = xz + wy;
    m->m[1][2] = yz - wx;
    m->m[2][2] = 1.0f - (xx + yy);
}

void f_099b98(float *a);
float f_099fc4(float a);
float cosf(float);
extern const float D_1abfa4, D_1abfa8;

/* Rotation vector scaled to an axis-angle quaternion: (axis * sin(a/2), cos(a/2)). */
/* @draft 0x09c0c4 us f_09c0c4
   WHAT IT DOES: Builds an axis-angle quaternion: the axis scaled by sin(angle/2) with w = cos(angle/2).
   Remaining difference: 11 of 37 words: retail loads the constant after moving the angle into $f20 and multiplies in place; the scheduler here loads the constant first. */
void f_09c0c4(Quat *d, const Vec3 *ax, int a)
{
    float h = D_1abfa4 * *(float *)&a;
    float h1 = h;
    f_099b98(&h1);
    float s = f_099fc4(h1);
    float h2 = h;
    d->v[0] = ax->v[0] * s;
    d->v[1] = ax->v[1] * s;
    d->v[2] = ax->v[2] * s;
    f_099b98(&h2);
    d->v[3] = cosf(h2);
}

/* @draft 0x09c158 us f_09c158
   WHAT IT DOES: Builds an axis-angle quaternion: the axis scaled by sin(angle/2) with w = cos(angle/2).
   Remaining difference: 11 of 37 words: retail loads the constant after moving the angle into $f20 and multiplies in place; the scheduler here loads the constant first. */
void f_09c158(Quat *d, const Vec3 *ax, int a)
{
    float h = D_1abfa8 * *(float *)&a;
    float h1 = h;
    f_099b98(&h1);
    float s = f_099fc4(h1);
    float h2 = h;
    d->v[0] = ax->v[0] * s;
    d->v[1] = ax->v[1] * s;
    d->v[2] = ax->v[2] * s;
    f_099b98(&h2);
    d->v[3] = cosf(h2);
}

/* @implements 0x09eda0 us f_09eda0
   WHAT IT DOES: Sets d to the product of two 3x3 matrices, one result row of d per pass. */
Mat33 *f_09eda0(Mat33 *d, const Mat33 *a, const Mat33 *b)
{
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * b->m[0][0] + p[-1] * b->m[1][0] + p[0] * b->m[2][0];
        q[3] = p[-2] * b->m[0][1] + p[-1] * b->m[1][1] + p[0] * b->m[2][1];
        q[6] = p[-2] * b->m[0][2] + p[-1] * b->m[1][2] + p[0] * b->m[2][2];
        p += 3;
        q++;
    }
    return d;
}

}
}

/* ---- m210b ---- */
#undef W
#undef B
#undef FLD
#undef DBL
#include <math.h>
namespace m210b {
struct FVec3 { float v[3]; };
struct Vec4a { float v[4]; Vec4a() {} Vec4a(float x, float y, float z, float w) { v[0] = x; v[1] = y; v[2] = z; v[3] = w; } };
struct Vec3 { float v[3]; };
struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Quat { float v[4]; };
struct QuatC { float v[4]; QuatC() {} QuatC(float x, float y, float z, float w) { v[0]=x; v[1]=y; v[2]=z; v[3]=w; } };
struct Mat33 { float m[3][3]; };
struct Mat34 { float m[3][4]; };
struct Mat44 { float m[4][4]; };
struct Mat43 { float m[4][3]; };
extern "C" {
void f_09c314(Vec4a *d, const FVec3 *v);

void f_09bf24(Quat *o, const void *in);
void f_09b2a8(QuatC *o, const QuatC *a);
void f_09fd1c(Mat34 *o, const Quat *q);

/* @implements 0x09b0fc us f_09b0fc
   WHAT IT DOES: Fills a temporary quaternion with f_09bf24, passes it to f_09b2a8 and stores the result in the destination. */
void f_09b0fc(Quat *d, const void *in)
{
    QuatC r;
    QuatC t;
    f_09bf24((Quat *)&t, in);
    f_09b2a8(&r, &t);
    *(QuatC *)d = r;
}

/* @implements 0x09b15c us f_09b15c
   WHAT IT DOES: Fills a temporary quaternion with f_09bf24, passes it to f_09b2a8 and stores the result in the destination. */
void f_09b15c(Quat *d, const void *in)
{
    QuatC r;
    QuatC t;
    f_09bf24((Quat *)&t, in);
    f_09b2a8(&r, &t);
    *(QuatC *)d = r;
}

/* @implements 0x09fbc4 us f_09fbc4
   WHAT IT DOES: Builds a quaternion from the rotation vector and converts it to a 3x4 matrix in the destination. */
void f_09fbc4(Mat34 *d, const Vec3 *a)
{
    Mat34 t;
    Quat q;
    f_09c314((Vec4a *)&q, (const FVec3 *)a);
    f_09fd1c(&t, &q);
    *d = t;
}

void f_0a0bfc(Quat *o, const Mat34 *m);
void f_09cc50(Quat *o, const Quat *a, const Quat *b, float t);

/* @implements 0x0a0dcc us f_0a0dcc
   WHAT IT DOES: Converts the matrix to a quaternion, interpolates it toward q by t, and writes the result back as a 3x4 matrix. */
Mat34 *f_0a0dcc(Mat34 *d, const Mat34 *m, float tt, const Quat *q)
{
    Quat r;
    Quat a;
    f_0a0bfc(&a, m);
    f_09cc50(&r, &a, q, tt);
    f_09fd1c(d, &r);
    return d;
}

/* @implements 0x09ef20 us f_09ef20
   WHAT IT DOES: Sets d to the product of the 3x3 matrix transposed times the 3x4 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +24 byte bias. */
Mat34 *f_09ef20(Mat34 *d, const Mat33 *a, const Mat34 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 6;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-6] * bf[0] + p[-3] * bf[4] + p[0] * bf[8];
        q[4] = p[-6] * bf[1] + p[-3] * bf[5] + p[0] * bf[9];
        q[8] = p[-6] * bf[2] + p[-3] * bf[6] + p[0] * bf[10];
        p += 1;
        q++;
    }
    return d;
}

/* @implements 0x09f090 us f_09f090
   WHAT IT DOES: Sets d to the product of a 3x3 matrix by a 3x4 matrix, one result column per pass, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat34 *f_09f090(Mat34 *d, const Mat33 *a, const Mat34 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[4] + p[0] * bf[8];
        q[4] = p[-2] * bf[1] + p[-1] * bf[5] + p[0] * bf[9];
        q[8] = p[-2] * bf[2] + p[-1] * bf[6] + p[0] * bf[10];
        p += 3;
        q++;
    }
    return d;
}

/* @implements 0x0a0fcc us f_0a0fcc
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 3x3 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +32 byte bias. */
Mat33 *f_0a0fcc(Mat33 *d, const Mat44 *a, const Mat33 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 8;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-8] * bf[0] + p[-4] * bf[1] + p[0] * bf[2];
        q[3] = p[-8] * bf[3] + p[-4] * bf[4] + p[0] * bf[5];
        q[6] = p[-8] * bf[6] + p[-4] * bf[7] + p[0] * bf[8];
        p += 1;
        q++;
    }
    return d;
}

/* @implements 0x0a1084 us f_0a1084
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 3x3 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +32 byte bias. */
Mat33 *f_0a1084(Mat33 *d, const Mat44 *a, const Mat33 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 8;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-8] * bf[0] + p[-4] * bf[3] + p[0] * bf[6];
        q[3] = p[-8] * bf[1] + p[-4] * bf[4] + p[0] * bf[7];
        q[6] = p[-8] * bf[2] + p[-4] * bf[5] + p[0] * bf[8];
        p += 1;
        q++;
    }
    return d;
}

/* @implements 0x0a113c us f_0a113c
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 3x3 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat33 *f_0a113c(Mat33 *d, const Mat44 *a, const Mat33 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[1] + p[0] * bf[2];
        q[3] = p[-2] * bf[3] + p[-1] * bf[4] + p[0] * bf[5];
        q[6] = p[-2] * bf[6] + p[-1] * bf[7] + p[0] * bf[8];
        p += 4;
        q++;
    }
    return d;
}

/* @implements 0x0a11f4 us f_0a11f4
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 3x3 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat33 *f_0a11f4(Mat33 *d, const Mat44 *a, const Mat33 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[3] + p[0] * bf[6];
        q[3] = p[-2] * bf[1] + p[-1] * bf[4] + p[0] * bf[7];
        q[6] = p[-2] * bf[2] + p[-1] * bf[5] + p[0] * bf[8];
        p += 4;
        q++;
    }
    return d;
}

/* @implements 0x0a1454 us f_0a1454
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 3x4 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat34 *f_0a1454(Mat34 *d, const Mat44 *a, const Mat34 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[1] + p[0] * bf[2];
        q[4] = p[-2] * bf[4] + p[-1] * bf[5] + p[0] * bf[6];
        q[8] = p[-2] * bf[8] + p[-1] * bf[9] + p[0] * bf[10];
        p += 4;
        q++;
    }
    return d;
}

/* @implements 0x0a150c us f_0a150c
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 3x4 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat34 *f_0a150c(Mat34 *d, const Mat44 *a, const Mat34 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[4] + p[0] * bf[8];
        q[4] = p[-2] * bf[1] + p[-1] * bf[5] + p[0] * bf[9];
        q[8] = p[-2] * bf[2] + p[-1] * bf[6] + p[0] * bf[10];
        p += 4;
        q++;
    }
    return d;
}

/* @implements 0x0a15c4 us f_0a15c4
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 4x3 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +32 byte bias. */
Mat43 *f_0a15c4(Mat43 *d, const Mat44 *a, const Mat43 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 8;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-8] * bf[0] + p[-4] * bf[1] + p[0] * bf[2];
        q[3] = p[-8] * bf[3] + p[-4] * bf[4] + p[0] * bf[5];
        q[6] = p[-8] * bf[6] + p[-4] * bf[7] + p[0] * bf[8];
        q[9] = p[-8] * bf[9] + p[-4] * bf[10] + p[0] * bf[11];
        p += 1;
        q++;
    }
    return d;
}

/* @implements 0x0a16ac us f_0a16ac
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 4x3 matrix, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat43 *f_0a16ac(Mat43 *d, const Mat44 *a, const Mat43 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[1] + p[0] * bf[2];
        q[3] = p[-2] * bf[3] + p[-1] * bf[4] + p[0] * bf[5];
        q[6] = p[-2] * bf[6] + p[-1] * bf[7] + p[0] * bf[8];
        q[9] = p[-2] * bf[9] + p[-1] * bf[10] + p[0] * bf[11];
        p += 4;
        q++;
    }
    return d;
}


void f_0a0944(Mat34 *o, const Mat34 *s);
void f_09fe84(Vec4 *o, const Mat34 *m, const Vec4 *a);
void f_09e4b8(Mat33 *o, const Mat33 *s);
void f_09d9c8(Vec4 *o, const Mat33 *m, const Vec4 *a);

/* @draft 0x09eb40 us f_09eb40
   WHAT IT DOES: Sets d[j][i] to the sum over k of a[k][i] * b[j][k] for two 3x3 matrices (a transposed times b transposed), one column per pass.
   Remaining difference: retail keeps an up-counting loop with separate address registers for the second and third source rows and reloads a's three elements for every result row (no common subexpression across the stores). Tried (m210c): byte-offset and float-index forms, manual offset counters written as int + (int)a (matches the addu operand order, but gets a recomputed sll/addu for the first row), local copies; none matched. */
Mat33 *f_09eb40(Mat33 *d, const Mat33 *a, const Mat33 *b)
{
    int i = 0;
    do {
        d->m[0][i] = a->m[0][i] * b->m[0][0] + a->m[1][i] * b->m[0][1] + a->m[2][i] * b->m[0][2];
        d->m[1][i] = a->m[0][i] * b->m[1][0] + a->m[1][i] * b->m[1][1] + a->m[2][i] * b->m[1][2];
        d->m[2][i] = a->m[0][i] * b->m[2][0] + a->m[1][i] * b->m[2][1] + a->m[2][i] * b->m[2][2];
        i++;
    } while (i < 3);
    return d;
}

/* @draft 0x09f158 us f_09f158
   WHAT IT DOES: Sets d[j][i] to the sum over k of a[k][i] * b[j][k] for a 3x3 matrix a and a four-row matrix b (a transposed times b transposed), one column of d per pass over four result rows; returns d.
   Remaining difference: same unsolved codegen as f_09eb40: retail strength-reduces a's second and third rows to byte-offset counters added to a each pass, and reloads a for every result. */
Mat43 *f_09f158(Mat43 *d, const Mat33 *a, const Mat43 *b)
{
    int i = 0;
    do {
        d->m[0][i] = a->m[0][i] * b->m[0][0] + a->m[1][i] * b->m[0][1] + a->m[2][i] * b->m[0][2];
        d->m[1][i] = a->m[0][i] * b->m[1][0] + a->m[1][i] * b->m[1][1] + a->m[2][i] * b->m[1][2];
        d->m[2][i] = a->m[0][i] * b->m[2][0] + a->m[1][i] * b->m[2][1] + a->m[2][i] * b->m[2][2];
        d->m[3][i] = a->m[0][i] * b->m[3][0] + a->m[1][i] * b->m[3][1] + a->m[2][i] * b->m[3][2];
        i++;
    } while (i < 3);
    return d;
}

/* @draft 0x09ec14 us f_09ec14
   WHAT IT DOES: Sets d[j][i] to the sum over k of a[k][i] * b[k][j] for two 3x3 matrices (a transposed times b), one column of d per pass; returns d.
   Remaining difference: same loop shape and same unsolved codegen as f_09eb40: retail keeps a byte-offset counter per source row and reloads a's three elements for every result; ours 184 bytes vs 212 (float-pointer and byte-offset forms tried, 180 and 204 bytes, none matched). */
Mat33 *f_09ec14(Mat33 *d, const Mat33 *a, const Mat33 *b)
{
    int i = 0;
    do {
        d->m[0][i] = a->m[0][i] * b->m[0][0] + a->m[1][i] * b->m[1][0] + a->m[2][i] * b->m[2][0];
        d->m[1][i] = a->m[0][i] * b->m[0][1] + a->m[1][i] * b->m[1][1] + a->m[2][i] * b->m[2][1];
        d->m[2][i] = a->m[0][i] * b->m[0][2] + a->m[1][i] * b->m[1][2] + a->m[2][i] * b->m[2][2];
        i++;
    } while (i < 3);
    return d;
}

/* @draft 0x0a318c us f_0a318c
   WHAT IT DOES: Inverts a rigid transform: the rotation part is transposed (f_0a0944) into d and the translation becomes the negated source translation rotated by the inverse (f_09fe84).
   Remaining difference: callee-saved register choice (s0/s1 swapped) and the final copy's address form. */
Mat44 *f_0a318c(Mat44 *d, const Mat44 *s)
{
    Mat34 t;
    Vec4 r;
    f_0a0944(&t, (const Mat34 *)s);
    *(Mat34 *)d = t;
    const Vec3 *tr = (const Vec3 *)s->m[3];
    Vec4 n(-s->m[3][0], -tr->v[1], -tr->v[2], 1.0f);
    f_09fe84(&r, (const Mat34 *)d, &n);
    Vec4 *dt = (Vec4 *)d->m[3];
    *dt = r;
    return d;
}

/* @draft 0x0a22cc us f_0a22cc
   WHAT IT DOES: Inverts a 3x3 rotation plus translation transform: the rotation is transposed (f_09e4b8) into d and the translation becomes the negated source translation rotated by the inverse (f_09d9c8).
   Remaining difference: register choice and the nine-word copy's tail. */
Mat43 *f_0a22cc(Mat43 *d, const Mat43 *s)
{
    Mat33 t;
    Vec4 r;
    f_09e4b8(&t, (const Mat33 *)s);
    *(Mat33 *)d = t;
    const Vec3 *tr = (const Vec3 *)s->m[3];
    Vec4 n(-s->m[3][0], -tr->v[1], -tr->v[2], 1.0f);
    f_09d9c8(&r, (const Mat33 *)d, &n);
    Vec4 *dt = (Vec4 *)d->m[3];
    *dt = r;
    return d;
}

/* @implements 0x0a1898 us f_0a1898
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 4x4 matrix using only the first three columns of each source row, three passes over the source in a down-counting loop, pointer-walking the source with the +8 byte bias. */
Mat44 *f_0a1898(Mat44 *d, const Mat44 *a, const Mat44 *b)
{
    const float *bf = (const float *)b;
    const float *p = (const float *)a + 2;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-2] * bf[0] + p[-1] * bf[1] + p[0] * bf[2];
        q[4] = p[-2] * bf[4] + p[-1] * bf[5] + p[0] * bf[6];
        q[8] = p[-2] * bf[8] + p[-1] * bf[9] + p[0] * bf[10];
        q[12] = p[-2] * bf[12] + p[-1] * bf[13] + p[0] * bf[14];
        p += 4;
        q++;
    }
    return d;
}

float f_09ab88(float x);
/* @implements 0x09b1bc us f_09b1bc
   WHAT IT DOES: Builds a rotation vector from a quaternion: copies the axis part with a constant fourth component, then scales it by twice f_09ab88 of the quaternion's w over the axis length. */
void f_09b1bc(QuatC *d, const QuatC *q)
{
    *d = QuatC(q->v[0], q->v[1], q->v[2], 1.0f);
    float len = sqrtf(d->v[0] * d->v[0] + d->v[1] * d->v[1] + d->v[2] * d->v[2]);
    float s = 2.0f * f_09ab88(q->v[3]) / len;
    d->v[0] *= s;
    d->v[1] *= s;
    d->v[2] *= s;
}

/* @implements 0x09b2a8 us f_09b2a8
   WHAT IT DOES: Builds a rotation vector from a quaternion: copies the axis part with a constant fourth component, then scales it by twice f_09ab88 of the quaternion's w over the axis length. (Twin of f_09b1bc with its own constant.) */
void f_09b2a8(QuatC *d, const QuatC *q)
{
    *d = QuatC(q->v[0], q->v[1], q->v[2], 1.0f);
    float len = sqrtf(d->v[0] * d->v[0] + d->v[1] * d->v[1] + d->v[2] * d->v[2]);
    float s = 2.0f * f_09ab88(q->v[3]) / len;
    d->v[0] *= s;
    d->v[1] *= s;
    d->v[2] *= s;
}

/* @implements 0x0a365c us f_0a365c
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 4x4 matrix with the fourth row of the source added to the last result row, three passes in a down-counting loop. */
Mat44 *f_0a365c(Mat44 *d, const Mat44 *a, const Mat44 *b)
{
    const float *p = (const float *)a;
    const float *bf = (const float *)b;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[0] * bf[0] + p[4] * bf[1] + p[8] * bf[2];
        q[4] = p[0] * bf[4] + p[4] * bf[5] + p[8] * bf[6];
        q[8] = p[0] * bf[8] + p[4] * bf[9] + p[8] * bf[10];
        q[12] = p[0] * bf[12] + p[4] * bf[13] + p[8] * bf[14] + p[12];
        p++;
        q++;
    }
    return d;
}

/* @implements 0x0a27a0 us f_0a27a0
   WHAT IT DOES: Sets d to the product of a 4x3 matrix by a 4x4 matrix with the fourth row of the source added to the last result row, three passes in a down-counting loop. */
Mat44 *f_0a27a0(Mat44 *d, const Mat43 *a, const Mat44 *b)
{
    const float *p = (const float *)a + 6;
    const float *bf = (const float *)b;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-6] * bf[0] + p[-3] * bf[1] + p[0] * bf[2];
        q[4] = p[-6] * bf[4] + p[-3] * bf[5] + p[0] * bf[6];
        q[8] = p[-6] * bf[8] + p[-3] * bf[9] + p[0] * bf[10];
        q[12] = p[-6] * bf[12] + p[-3] * bf[13] + p[0] * bf[14] + p[3];
        p++;
        q++;
    }
    return d;
}

/* @implements 0x0a356c us f_0a356c
   WHAT IT DOES: Sets d to the product of a 4x4 matrix by a 4x3 matrix with the fourth row of the source added to the last result row, three passes in a down-counting loop. */
Mat43 *f_0a356c(Mat43 *d, const Mat44 *a, const Mat43 *b)
{
    const float *p = (const float *)a + 8;
    const float *bf = (const float *)b;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[-8] * bf[0] + p[-4] * bf[1] + p[0] * bf[2];
        q[3] = p[-8] * bf[3] + p[-4] * bf[4] + p[0] * bf[5];
        q[6] = p[-8] * bf[6] + p[-4] * bf[7] + p[0] * bf[8];
        q[9] = p[-8] * bf[9] + p[-4] * bf[10] + p[0] * bf[11] + p[4];
        p++;
        q++;
    }
    return d;
}

/* @implements 0x0a26b4 us f_0a26b4
   WHAT IT DOES: Sets d to the product of two 4x3 matrices with the fourth row of the first added to the last result row, three passes in a down-counting loop. */
Mat43 *f_0a26b4(Mat43 *d, const Mat43 *a, const Mat43 *b)
{
    const float *p = (const float *)a;
    const float *bf = (const float *)b;
    float *q = (float *)d;
    for (int i = 2; i >= 0; i--) {
        q[0] = p[0] * bf[0] + p[3] * bf[1] + p[6] * bf[2];
        q[3] = p[0] * bf[3] + p[3] * bf[4] + p[6] * bf[5];
        q[6] = p[0] * bf[6] + p[3] * bf[7] + p[6] * bf[8];
        q[9] = p[0] * bf[9] + p[3] * bf[10] + p[6] * bf[11] + p[9];
        p++;
        q++;
    }
    return d;
}

extern const float D_1abfac, D_1abfb0, D_1abfb4, D_1abfb8;
void f_099b98(float *a);
void f_09c158(Quat *d, const Vec4a *ax, int a);

/* @implements 0x09c1ec us f_09c1ec
   WHAT IT DOES: Builds the rotation quaternion of a rotation vector: if its length is below a small epsilon the result is (0, 0, 0, 1); otherwise the unit axis and the length (adjusted through f_099b98) go to f_09c158 and the result is copied out. */
void f_09c1ec(Vec4a *d, const FVec3 *v)
{
    Vec4a ax;
    float s = sqrtf(v->v[0] * v->v[0] + v->v[1] * v->v[1] + v->v[2] * v->v[2]);
    if (s < D_1abfac) {
        d->v[2] = 0;
        d->v[1] = 0;
        d->v[0] = 0;
        d->v[3] = D_1abfb0;
        return;
    }
    float n = s;
    float uy = v->v[1] / n;
    float uz = v->v[2] / n;
    ax = Vec4a(v->v[0] / n, uy, uz, 1.0f);
    Quat r;
    f_099b98(&n);
    f_09c158(&r, &ax, *(int *)&n);
    *d = *(Vec4a *)&r;
}

/* @implements 0x09c314 us f_09c314
   WHAT IT DOES: The same as f_09c1ec (twin at another address): builds the rotation quaternion of a rotation vector: if its length is below a small epsilon the result is (0, 0, 0, 1); otherwise the unit axis and the length (adjusted through f_099b98) go to f_09c158 and the result is copied out. */
void f_09c314(Vec4a *d, const FVec3 *v)
{
    Vec4a ax;
    float s = sqrtf(v->v[0] * v->v[0] + v->v[1] * v->v[1] + v->v[2] * v->v[2]);
    if (s < D_1abfb4) {
        d->v[2] = 0;
        d->v[1] = 0;
        d->v[0] = 0;
        d->v[3] = D_1abfb8;
        return;
    }
    float n = s;
    float uy = v->v[1] / n;
    float uz = v->v[2] / n;
    ax = Vec4a(v->v[0] / n, uy, uz, 1.0f);
    Quat r;
    f_099b98(&n);
    f_09c158(&r, &ax, *(int *)&n);
    *d = *(Vec4a *)&r;
}


}
}

/* ---- m210c ---- */
namespace m210c {
struct Mat44 { float m[4][4]; };

extern "C" {
/* @draft 0x0a12ac us f_0a12ac
   WHAT IT DOES: Sets d[j][i] to the sum over k of a[k][i] * b[b[j][k]] for two 4x4 matrices (only the upper-left 3x3 is used), one column of d per pass; returns d.
   Remaining difference: same unsolved codegen as f_09eb40: retail strength-reduces a's second and third rows to byte-offset counters added to a each pass, and reloads a for every result. */
Mat44 *f_0a12ac(Mat44 *d, const Mat44 *a, const Mat44 *b)
{
    int i = 0;
    do {
        d->m[0][i] = a->m[0][i] * b->m[0][0] + a->m[1][i] * b->m[0][1] + a->m[2][i] * b->m[0][2];
        d->m[1][i] = a->m[0][i] * b->m[1][0] + a->m[1][i] * b->m[1][1] + a->m[2][i] * b->m[1][2];
        d->m[2][i] = a->m[0][i] * b->m[2][0] + a->m[1][i] * b->m[2][1] + a->m[2][i] * b->m[2][2];
        i++;
    } while (i < 3);
    return d;
}

/* @draft 0x0a1794 us f_0a1794
   WHAT IT DOES: Sets d[j][i] to the sum over k of a[k][i] * b[j][k] for 4x4 matrices (upper-left 3x3 of a, four result rows), one column of d per pass; returns d.
   Remaining difference: same unsolved codegen as f_09eb40: retail strength-reduces a's second and third rows to byte-offset counters added to a each pass, and reloads a for every result. */
Mat44 *f_0a1794(Mat44 *d, const Mat44 *a, const Mat44 *b)
{
    int i = 0;
    do {
        d->m[0][i] = a->m[0][i] * b->m[0][0] + a->m[1][i] * b->m[0][1] + a->m[2][i] * b->m[0][2];
        d->m[1][i] = a->m[0][i] * b->m[1][0] + a->m[1][i] * b->m[1][1] + a->m[2][i] * b->m[1][2];
        d->m[2][i] = a->m[0][i] * b->m[2][0] + a->m[1][i] * b->m[2][1] + a->m[2][i] * b->m[2][2];
        d->m[3][i] = a->m[0][i] * b->m[3][0] + a->m[1][i] * b->m[3][1] + a->m[2][i] * b->m[3][2];
        i++;
    } while (i < 3);
    return d;
}

/* @draft 0x0a1380 us f_0a1380
   WHAT IT DOES: Sets d[j][i] to the sum over k of a[k][i] * b[b[k][j]] for two 4x4 matrices (only the upper-left 3x3 is used), one column of d per pass; returns d.
   Remaining difference: same unsolved codegen as f_09eb40: retail strength-reduces a's second and third rows to byte-offset counters added to a each pass, and reloads a for every result. */
Mat44 *f_0a1380(Mat44 *d, const Mat44 *a, const Mat44 *b)
{
    int i = 0;
    do {
        d->m[0][i] = a->m[0][i] * b->m[0][0] + a->m[1][i] * b->m[1][0] + a->m[2][i] * b->m[2][0];
        d->m[1][i] = a->m[0][i] * b->m[0][1] + a->m[1][i] * b->m[1][1] + a->m[2][i] * b->m[2][1];
        d->m[2][i] = a->m[0][i] * b->m[0][2] + a->m[1][i] * b->m[1][2] + a->m[2][i] * b->m[2][2];
        i++;
    } while (i < 3);
    return d;
}

}
extern "C" {
void f_0a2e44(Mat44 *r);
Mat44 *f_09b908(Mat44 *a);
void f_0a2c70(Mat44 *d, const Mat44 *s);

/* @implements 0x0a2e98 us f_0a2e98
   WHAT IT DOES: Builds a 4x4 matrix with f_0a2e44, runs it through f_09b908 on a copy, and passes the result to f_0a2c70 to fill the destination. */
Mat44 *f_0a2e98(Mat44 *d)
{
    Mat44 t1;
    Mat44 t3;
    Mat44 t2;
    f_0a2e44(&t1);
    t2 = t1;
    t3 = *f_09b908(&t2);
    f_0a2c70(d, &t3);
    return d;
}

struct Quat2 { float v[4]; Quat2() {} Quat2(float x, float y, float z, float w) { v[0] = x; v[1] = y; v[2] = z; v[3] = w; } };
struct Vec3b { float v[3]; };
extern const float D_1abfc8, D_1abfcc, D_1abfd0;
Quat2 *c_qmul(Quat2 *d, const Quat2 *a, Quat2 b) __asm__("f_09c618");
Quat2 c_qinv(const Quat2 *q) __asm__("f_09c54c");

/* @draft 0x09c720 us f_09c720
   WHAT IT DOES: Rotates the vector b by the quaternion q: multiplies q by (b, 1), then by the inverse of q, and returns the vector part with w = 1.
   Remaining difference: retail keeps its locals in four slots (the argument copy and the final vector copy share one) and this source uses five. */
Quat2 f_09c720(const Quat2 *q, const Vec3b *b)
{
    Quat2 t1;
    {
        Quat2 v(b->v[0], b->v[1], b->v[2], D_1abfc8);
        Quat2 bc;
        bc = v;
        c_qmul(&t1, q, bc);
    }
    Quat2 inv = c_qinv(q);
    Vec3b res;
    {
        Quat2 r;
        c_qmul(&r, &t1, inv);
        res = *(Vec3b *)&r;
    }
    return Quat2(res.v[0], res.v[1], res.v[2], D_1abfc8);
}

/* @draft 0x09c810 us f_09c810
   WHAT IT DOES: Quaternion lerp: d = (1 - t) * a + (t or -t) * b, taking the negated weight when the dot product of a and b is negative; returns d.
   Remaining difference: 16 words: register choice in the dot product (retail loads b[0], b[1] into $f2, $f1; ours the reverse). */
Quat2 *f_09c810(Quat2 *d, const Quat2 *a, const Quat2 *b, float t)
{
    float dot = a->v[0] * b->v[0] + a->v[1] * b->v[1] + a->v[2] * b->v[2] + a->v[3] * b->v[3];
    float u = D_1abfcc - t;
    float x = u * a->v[0], y = u * a->v[1], z = u * a->v[2], w = u * a->v[3];
    if (dot < 0.0f)
        t = -t;
    *d = Quat2(x, y, z, w);
    *d = Quat2(d->v[0] + t * b->v[0], d->v[1] + t * b->v[1], d->v[2] + t * b->v[2], d->v[3] + t * b->v[3]);
    struct T16 { float f[4]; ~T16() {} } pad;
    return d;
}

/* @draft 0x09c930 us f_09c930
   WHAT IT DOES: Quaternion lerp: d = (1 - t) * a + (t or -t) * b, taking the negated weight when the dot product of a and b is not negative; returns d.
   Remaining difference: 16 words, the same as f_09c810: register choice in the dot product (retail loads b[0], b[1] into $f2, $f1; ours the reverse). */
Quat2 *f_09c930(Quat2 *d, const Quat2 *a, const Quat2 *b, float t)
{
    float dot = a->v[0] * b->v[0] + a->v[1] * b->v[1] + a->v[2] * b->v[2] + a->v[3] * b->v[3];
    float u = D_1abfd0 - t;
    float x = u * a->v[0], y = u * a->v[1], z = u * a->v[2], w = u * a->v[3];
    if (dot >= 0.0f)
        t = -t;
    *d = Quat2(x, y, z, w);
    *d = Quat2(d->v[0] + t * b->v[0], d->v[1] + t * b->v[1], d->v[2] + t * b->v[2], d->v[3] + t * b->v[3]);
    struct T16 { float f[4]; ~T16() {} } pad;
    return d;
}

}

/* Rotation matrix to rotation vector: the antisymmetric part gives the axis and acos of the
   clamped trace the angle; near 0 or pi it goes through Euler angles and a quaternion. */
struct Vec3 { float v[3]; };
struct Quat4 { float v[4]; };
extern "C" {
float c_acos(float x) __asm__("f_09ab88");
float c_atan2(float y, float x) __asm__("f_09a86c");
void c_wrap(float *a) __asm__("f_099b98");
void c_eul2quat(Quat4 *o, const void *in) __asm__("f_09bf24");
void c_quat2rv(Quat4 *o, const Quat4 *a) __asm__("f_09b2a8");
}
struct Ang {
    float a;
    Ang() : a(0.0f) {}
    Ang(float x) : a(x) { c_wrap(&a); }
};
struct AngI { int a; AngI() : a(0) {} AngI(const Ang &o) { a = *(const int *)&o; } };
struct Euler {
    AngI e[3];
    float w;
    Euler() __attribute__((always_inline));
};
inline Euler::Euler()
{
    e[0] = Ang(0.0f);
    e[1] = Ang(0.0f);
    e[2] = Ang(0.0f);
    w = 0.0f;
}
extern "C" {
extern const float D_1ac0a0, D_1ac0a4, D_1ac0a8, D_1ac0ac, D_1ac0b0, D_1ac0b4;
extern const float D_1ac0b8, D_1ac0bc, D_1ac0c0, D_1ac0c4, D_1ac0c8, D_1ac0cc;
extern const float D_1ac0d0, D_1ac0d4, D_1ac0d8, D_1ac0dc, D_1ac0e0, D_1ac0e4;
extern const float D_1ac0e8, D_1ac0ec, D_1ac0f0, D_1ac0f4, D_1ac0f8, D_1ac0fc;

/* @draft 0x0a4408 us f_0a4408
   WHAT IT DOES: Converts a rotation matrix (3x3, rows of three) to a rotation vector in d: if the antisymmetric part of the matrix is above a small threshold the axis is that part scaled to the angle acos((clamped trace - 1) / 2); otherwise it extracts Euler angles (each wrapped by f_099b98, with a gimbal fallback when the cosine of the middle angle is tiny), builds a quaternion with f_09bf24 and converts it with f_09b2a8.
   Remaining difference: six words differ: retail copies the last Euler angle through v1 and loads the middle-angle operands before the copy. */
void f_0a4408(Vec3 *d, const float *m)
{
    d->v[0] = m[5] - m[7];
    d->v[1] = m[6] - m[2];
    d->v[2] = m[1] - m[3];
    if (fabsf(d->v[0]) > D_1ac0a0 || fabsf(d->v[1]) > D_1ac0a0 || fabsf(d->v[2]) > D_1ac0a0) {
        float tr = m[0] + m[4] + m[8];
        if (tr <= D_1ac0a4)
            tr = D_1ac0a4;
        else if (tr >= D_1ac0a8)
            tr = D_1ac0a8;
        float ang = c_acos((tr - D_1ac0ac) * D_1ac0b0);
        float s = ang / sqrtf(d->v[0] * d->v[0] + d->v[1] * d->v[1] + d->v[2] * d->v[2]);
        d->v[0] *= s;
        d->v[1] *= s;
        d->v[2] *= s;
        return;
    }
    Euler e;
    float cy = sqrtf(m[0] * m[0] + m[1] * m[1]);
    if (cy > D_1ac0b4) {
        e.e[0] = Ang(c_atan2(m[5], m[8]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(c_atan2(m[1], m[0]));
    } else {
        e.e[0] = Ang(c_atan2(-m[7], m[4]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(0.0f);
    }
    Quat4 r;
    Quat4 q;
    c_eul2quat(&q, &e);
    c_quat2rv(&r, &q);
    *(Quat4 *)d = r;
}

/* @draft 0x0a4724 us f_0a4724
   WHAT IT DOES: Converts a rotation matrix (3x3, rows of three) to a rotation vector in d: if the antisymmetric part of the matrix is above a small threshold the axis is that part scaled to the angle acos((clamped trace - 1) / 2); otherwise it extracts Euler angles (each wrapped by f_099b98, with a gimbal fallback when the cosine of the middle angle is tiny), builds a quaternion with f_09bf24 and converts it with f_09b2a8.
   Remaining difference: six words differ: retail copies the last Euler angle through v1 and loads the middle-angle operands before the copy. */
void f_0a4724(Vec3 *d, const float *m)
{
    d->v[0] = m[5] - m[7];
    d->v[1] = m[6] - m[2];
    d->v[2] = m[1] - m[3];
    if (fabsf(d->v[0]) > D_1ac0b8 || fabsf(d->v[1]) > D_1ac0b8 || fabsf(d->v[2]) > D_1ac0b8) {
        float tr = m[0] + m[4] + m[8];
        if (tr <= D_1ac0bc)
            tr = D_1ac0bc;
        else if (tr >= D_1ac0c0)
            tr = D_1ac0c0;
        float ang = c_acos((tr - D_1ac0c4) * D_1ac0c8);
        float s = ang / sqrtf(d->v[0] * d->v[0] + d->v[1] * d->v[1] + d->v[2] * d->v[2]);
        d->v[0] *= s;
        d->v[1] *= s;
        d->v[2] *= s;
        return;
    }
    Euler e;
    float cy = sqrtf(m[0] * m[0] + m[1] * m[1]);
    if (cy > D_1ac0cc) {
        e.e[0] = Ang(c_atan2(m[5], m[8]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(c_atan2(m[1], m[0]));
    } else {
        e.e[0] = Ang(c_atan2(-m[7], m[4]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(0.0f);
    }
    Quat4 r;
    Quat4 q;
    c_eul2quat(&q, &e);
    c_quat2rv(&r, &q);
    *(Quat4 *)d = r;
}

/* @draft 0x0a4a40 us f_0a4a40
   WHAT IT DOES: Converts a rotation matrix (3x4, rows of four) to a rotation vector in d: if the antisymmetric part of the matrix is above a small threshold the axis is that part scaled to the angle acos((clamped trace - 1) / 2); otherwise it extracts Euler angles (each wrapped by f_099b98, with a gimbal fallback when the cosine of the middle angle is tiny), builds a quaternion with f_09bf24 and converts it with f_09b2a8.
   Remaining difference: six words differ: retail copies the last Euler angle through v1 and loads the middle-angle operands before the copy. */
void f_0a4a40(Vec3 *d, const float *m)
{
    d->v[0] = m[6] - m[9];
    d->v[1] = m[8] - m[2];
    d->v[2] = m[1] - m[4];
    if (fabsf(d->v[0]) > D_1ac0d0 || fabsf(d->v[1]) > D_1ac0d0 || fabsf(d->v[2]) > D_1ac0d0) {
        float tr = m[0] + m[5] + m[10];
        if (tr <= D_1ac0d4)
            tr = D_1ac0d4;
        else if (tr >= D_1ac0d8)
            tr = D_1ac0d8;
        float ang = c_acos((tr - D_1ac0dc) * D_1ac0e0);
        float s = ang / sqrtf(d->v[0] * d->v[0] + d->v[1] * d->v[1] + d->v[2] * d->v[2]);
        d->v[0] *= s;
        d->v[1] *= s;
        d->v[2] *= s;
        return;
    }
    Euler e;
    float cy = sqrtf(m[0] * m[0] + m[1] * m[1]);
    if (cy > D_1ac0e4) {
        e.e[0] = Ang(c_atan2(m[6], m[10]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(c_atan2(m[1], m[0]));
    } else {
        e.e[0] = Ang(c_atan2(-m[9], m[5]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(0.0f);
    }
    Quat4 r;
    Quat4 q;
    c_eul2quat(&q, &e);
    c_quat2rv(&r, &q);
    *(Quat4 *)d = r;
}

/* @draft 0x0a4d5c us f_0a4d5c
   WHAT IT DOES: Converts a rotation matrix (3x4, rows of four) to a rotation vector in d: if the antisymmetric part of the matrix is above a small threshold the axis is that part scaled to the angle acos((clamped trace - 1) / 2); otherwise it extracts Euler angles (each wrapped by f_099b98, with a gimbal fallback when the cosine of the middle angle is tiny), builds a quaternion with f_09bf24 and converts it with f_09b2a8.
   Remaining difference: six words differ: retail copies the last Euler angle through v1 and loads the middle-angle operands before the copy. */
void f_0a4d5c(Vec3 *d, const float *m)
{
    d->v[0] = m[6] - m[9];
    d->v[1] = m[8] - m[2];
    d->v[2] = m[1] - m[4];
    if (fabsf(d->v[0]) > D_1ac0e8 || fabsf(d->v[1]) > D_1ac0e8 || fabsf(d->v[2]) > D_1ac0e8) {
        float tr = m[0] + m[5] + m[10];
        if (tr <= D_1ac0ec)
            tr = D_1ac0ec;
        else if (tr >= D_1ac0f0)
            tr = D_1ac0f0;
        float ang = c_acos((tr - D_1ac0f4) * D_1ac0f8);
        float s = ang / sqrtf(d->v[0] * d->v[0] + d->v[1] * d->v[1] + d->v[2] * d->v[2]);
        d->v[0] *= s;
        d->v[1] *= s;
        d->v[2] *= s;
        return;
    }
    Euler e;
    float cy = sqrtf(m[0] * m[0] + m[1] * m[1]);
    if (cy > D_1ac0fc) {
        e.e[0] = Ang(c_atan2(m[6], m[10]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(c_atan2(m[1], m[0]));
    } else {
        e.e[0] = Ang(c_atan2(-m[9], m[5]));
        e.e[1] = Ang(c_atan2(-m[2], cy));
        e.e[2] = Ang(0.0f);
    }
    Quat4 r;
    Quat4 q;
    c_eul2quat(&q, &e);
    c_quat2rv(&r, &q);
    *(Quat4 *)d = r;
}


struct EulOut {
    AngI e[3];
    int order;
    static void *operator new(unsigned, void *p) { return p; }
    EulOut(const float *m, int order_, const float &eps) __attribute__((always_inline));
};
extern "C" { extern const signed char D_1abf6c[]; }
inline EulOut::EulOut(const float *m, int order_, const float &eps)
{
    const signed char *t = D_1abf6c + order_ * 3;
    int i = t[0];
    int j = t[1];
    int k = t[2];
    int i3 = 3 * i;
    float cy = sqrtf(m[i3 + i] * m[i3 + i] + m[i3 + j] * m[i3 + j]);
    AngI last;
    if (cy > eps) {
        e[i] = Ang(c_atan2(m[3 * j + k], m[4 * k]));
        e[j] = Ang(c_atan2(-m[i3 + k], cy));
        last = Ang(c_atan2(m[i3 + j], m[i3 + i]));
    } else {
        e[i] = Ang(c_atan2(-m[3 * k + j], m[4 * j]));
        e[j] = Ang(c_atan2(-m[i3 + k], cy));
        last = Ang(0.0f);
    }
    e[k] = last;
    if (order_ & 1) {
        e[0] = Ang(-*(float *)&e[0]);
        e[1] = Ang(-*(float *)&e[1]);
        e[2] = Ang(-*(float *)&e[2]);
    }
    order = order_;
}
extern "C" { extern const float D_1ac090; extern const float D_1ac094; }
/* @draft 0x0a3938 us f_0a3938
   WHAT IT DOES: Extracts three Euler angles from a 3x3 rotation matrix for the axis order code (0..23, three signed bytes per order in the table at D_1abf6c plus a parity bit): the middle angle from atan2 of the off-axis element and the sqrt of the sum of squares of two elements, with the gimbal-lock fallback when that is below a threshold; every angle is wrapped by f_099b98, negated first when the order's low bit is set, and the order code is stored after the three angles.
   Remaining difference: same size (704 bytes) but register assignment differs: retail keeps the two element addresses in saved registers and reuses the first axis register for the angle slot address, this source gets a different assignment and spills one address. */
void f_0a3938(EulOut *d, const float *m, int order)
{
    new (d) EulOut(m, order, D_1ac090);
}

/* @draft 0x0a3bf8 us f_0a3bf8
   WHAT IT DOES: Extracts three Euler angles from a 3x3 rotation matrix for the axis order code (0..23, three signed bytes per order in the table at D_1abf6c plus a parity bit): the middle angle from atan2 of the off-axis element and the sqrt of the sum of squares of two elements, with the gimbal-lock fallback when that is below a threshold; every angle is wrapped by f_099b98, negated first when the order's low bit is set, and the order code is stored after the three angles.
   Remaining difference: same size (704 bytes) but register assignment differs: retail keeps the two element addresses in saved registers and reuses the first axis register for the angle slot address, this source gets a different assignment and spills one address. */
void f_0a3bf8(EulOut *d, const float *m, int order)
{
    new (d) EulOut(m, order, D_1ac094);
}

struct EulOutB {
    AngI e[3];
    int order;
    static void *operator new(unsigned, void *p) { return p; }
    EulOutB(const float *m, int order_, const float &eps) __attribute__((always_inline));
};
inline EulOutB::EulOutB(const float *m, int order_, const float &eps)
{
    const signed char *t = D_1abf6c + order_ * 3;
    int i = t[0];
    int j = t[1];
    int k = t[2];
    int i4 = 4 * i;
    float cy = sqrtf(m[i4 + i] * m[i4 + i] + m[i4 + j] * m[i4 + j]);
    if (cy > eps) {
        e[i] = Ang(c_atan2(m[4 * j + k], m[5 * k]));
        e[j] = Ang(c_atan2(-m[i4 + k], cy));
        e[k] = Ang(c_atan2(m[i4 + j], m[i4 + i]));
    } else {
        e[i] = Ang(c_atan2(-m[4 * k + j], m[5 * j]));
        e[j] = Ang(c_atan2(-m[i4 + k], cy));
        e[k] = Ang(0.0f);
    }
    if (order_ & 1) {
        e[0] = Ang(-*(float *)&e[0]);
        e[1] = Ang(-*(float *)&e[1]);
        e[2] = Ang(-*(float *)&e[2]);
    }
    order = order_;
}
extern "C" { extern const float D_1ac098; extern const float D_1ac09c; }

/* @draft 0x0a3eb8 us f_0a3eb8
   WHAT IT DOES: Extracts three Euler angles from a 3x3 rotation matrix for the axis order code (0..23, three signed bytes per order in the table at D_1abf6c plus a parity bit): the middle angle from atan2 of the off-axis element and the sqrt of the sum of squares of two elements, with the gimbal-lock fallback when that is below a threshold; every angle is wrapped by f_099b98, negated first when the order's low bit is set; the rows of the matrix are four floats wide.
   Remaining difference: 47 of 170 words differ, all after the first branch: retail stores the last angle in the delay slot of the parity test after the two branches join (plain bnez), this source gets bnezl with the first negation load in the slot; moving the last angle into a joined local fixes the shape but changes the register assignment. */
void f_0a3eb8(EulOutB *d, const float *m, int order)
{
    new (d) EulOutB(m, order, D_1ac098);
}

/* @draft 0x0a4160 us f_0a4160
   WHAT IT DOES: Extracts three Euler angles from a 3x3 rotation matrix for the axis order code (0..23, three signed bytes per order in the table at D_1abf6c plus a parity bit): the middle angle from atan2 of the off-axis element and the sqrt of the sum of squares of two elements, with the gimbal-lock fallback when that is below a threshold; every angle is wrapped by f_099b98, negated first when the order's low bit is set; the rows of the matrix are four floats wide.
   Remaining difference: 47 of 170 words differ, all after the first branch: retail stores the last angle in the delay slot of the parity test after the two branches join (plain bnez), this source gets bnezl with the first negation load in the slot; moving the last angle into a joined local fixes the shape but changes the register assignment. */
void f_0a4160(EulOutB *d, const float *m, int order)
{
    new (d) EulOutB(m, order, D_1ac09c);
}

}
}
