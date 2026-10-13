/* The vectors of the camera math library (retail 0x09b394 to 0x09b6a0): three- and
   four-component float vectors. Components are arrays, so stores through one vector are taken
   to reach any other. */

#include <math.h>

extern "C" {
float f_099fc4(float a);
float f_09a154(float a);
}

/* An angle in radians, passed by value in an integer register. */
union Angle {
    float a;
    float Rad() const { return a; }
};

struct Mat44 {
    float m[4][4];
};

struct Vec3 {
    float v[3];
    Vec3 &f_09b414(Angle a, int axis);
    Vec3 &f_09b474(const Vec3 &a, const Vec3 &b);
    float f_09b4dc(const Vec3 &b) const;
    Vec3 &f_09b548(const Vec3 &a, const Vec3 &b, float t);
};

struct Vec4 {
    float v[4];
    Vec4() {}
    Vec4(float x, float y, float z, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
    Vec4 &f_09b598(const Mat44 &m);
    Vec4 &f_09b698(const Vec4 &a, const Mat44 &m);
    Vec4 &f_09bc7c(const Mat44 &m, const Vec4 &a);
};

/* @implements 0x09b394 us f_09b394
   WHAT IT DOES: Rotates the pair (x, y) by the angle in its plane. */
void f_09b394(Angle a, float &x, float &y)
{
    float c = f_099fc4(a.Rad());
    float s = f_09a154(a.Rad());
    float px = x, py = y;
    x = px * s - py * c;
    y = px * c + py * s;
}

static const signed char D_1abf80[3] = {2, 0, 1};
static const signed char D_1abf84[3] = {1, 2, 0};

/* @implements 0x09b414 us f_09b414
   WHAT IT DOES: Rotates the vector by the angle about one coordinate axis (0, 1, 2 = x, y, z)
   and returns it. */
Vec3 &Vec3::f_09b414(Angle a, int axis)
{
    f_09b394(a, v[D_1abf84[axis]], v[D_1abf80[axis]]);
    return *this;
}

/* @implements 0x09b474 us f_09b474
   WHAT IT DOES: Sets the vector to the cross product a x b and returns it. */
Vec3 &Vec3::f_09b474(const Vec3 &a, const Vec3 &b)
{
    v[0] = a.v[1] * b.v[2] - a.v[2] * b.v[1];
    v[1] = a.v[2] * b.v[0] - a.v[0] * b.v[2];
    v[2] = a.v[0] * b.v[1] - a.v[1] * b.v[0];
    return *this;
}

/* @draft 0x09b4dc us f_09b4dc
   WHAT IT DOES: Returns the distance to b.
   Remaining difference: retail loads b's x and y before this vector's components; the
   instructions are otherwise the same (operator- and Length forms tried). */
float Vec3::f_09b4dc(const Vec3 &b) const
{
    float x = v[0] - b.v[0], y = v[1] - b.v[1], z = v[2] - b.v[2];
    return sqrtf(x * x + y * y + z * z);
}

/* @implements 0x09b548 us f_09b548
   WHAT IT DOES: Sets the vector to the linear blend of a and b at t and returns it. */
Vec3 &Vec3::f_09b548(const Vec3 &a, const Vec3 &b, float t)
{
    v[0] = a.v[0] + (b.v[0] - a.v[0]) * t;
    v[1] = a.v[1] + (b.v[1] - a.v[1]) * t;
    v[2] = a.v[2] + (b.v[2] - a.v[2]) * t;
    return *this;
}

/* @implements 0x09b598 us f_09b598
   WHAT IT DOES: Transforms the vector in place by the matrix (column vector, M v) and returns
   it. */
Vec4 &Vec4::f_09b598(const Mat44 &m)
{
    *this = Vec4(m.m[0][0] * v[0] + m.m[0][1] * v[1] + m.m[0][2] * v[2] + m.m[0][3] * v[3],
                 m.m[1][0] * v[0] + m.m[1][1] * v[1] + m.m[1][2] * v[2] + m.m[1][3] * v[3],
                 m.m[2][0] * v[0] + m.m[2][1] * v[1] + m.m[2][2] * v[2] + m.m[2][3] * v[3],
                 m.m[3][0] * v[0] + m.m[3][1] * v[1] + m.m[3][2] * v[2] + m.m[3][3] * v[3]);
    return *this;
}

/* @implements 0x09b698 us f_09b698
   WHAT IT DOES: Sets the vector to the matrix times a (column vector, M a) and returns it. */
Vec4 &Vec4::f_09b698(const Vec4 &a, const Mat44 &m)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[0][1] * a.v[1] + m.m[0][2] * a.v[2] + m.m[0][3] * a.v[3];
    v[1] = m.m[1][0] * a.v[0] + m.m[1][1] * a.v[1] + m.m[1][2] * a.v[2] + m.m[1][3] * a.v[3];
    v[2] = m.m[2][0] * a.v[0] + m.m[2][1] * a.v[1] + m.m[2][2] * a.v[2] + m.m[2][3] * a.v[3];
    v[3] = m.m[3][0] * a.v[0] + m.m[3][1] * a.v[1] + m.m[3][2] * a.v[2] + m.m[3][3] * a.v[3];
    return *this;
}

/* @implements 0x09bc7c us f_09bc7c
   WHAT IT DOES: Sets the vector to the transposed matrix times a (row vector, a M) and returns
   it. */
Vec4 &Vec4::f_09bc7c(const Mat44 &m, const Vec4 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[1][0] * a.v[1] + m.m[2][0] * a.v[2] + m.m[3][0] * a.v[3];
    v[1] = m.m[0][1] * a.v[0] + m.m[1][1] * a.v[1] + m.m[2][1] * a.v[2] + m.m[3][1] * a.v[3];
    v[2] = m.m[0][2] * a.v[0] + m.m[1][2] * a.v[1] + m.m[2][2] * a.v[2] + m.m[3][2] * a.v[3];
    v[3] = m.m[0][3] * a.v[0] + m.m[1][3] * a.v[1] + m.m[2][3] * a.v[2] + m.m[3][3] * a.v[3];
    return *this;
}
