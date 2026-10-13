/* The 4x3 float matrix of the camera math library: a 3x3 rotation in its first three rows and
   a translation in the fourth (retail 0x0a1980 to 0x0a22cc). */

extern "C" {
float f_099fc4(float a);
float f_09a154(float a);
}

/* An angle in radians, passed by value in an integer register. */
union Angle {
    float a;
    float Rad() const { return a; }
};

struct Mat43;

struct Vec3 {
    float v[3];
    Vec3 &f_0a1e10(const Mat43 &m, const Vec3 &a);
    Vec3 &f_0a1ec0(const Mat43 &m, const Vec3 &a);
};

/* Euler angles with their axis order. */
struct Euler {
    float a[3];
    int order;
};

struct Quat {
    float v[4];
};

struct Mat33 {
    float m[3][3];
};

/* The 3x3 matrix with rows padded to four floats. */
struct Mat34 {
    float m[3][4];
};

/* The 4x3 matrix with rows padded to four floats. */
struct Mat43p {
    float m[4][4];
};

/* The 3x3 matrix's constructors from Euler angles, a rotation vector and a quaternion (complete
   object forms), called on an uninitialised matrix. */
extern "C" {
void f_09d450(Mat33 *m, const Euler &e);
void f_09d6f4(Mat33 *m, const Vec3 &r);
void f_09d858(Mat33 *m, const Quat &q);
}

struct Mat44 {
    float m[4][4];
    Mat44(const Mat43 &s);
    float f_09b9f4() const;
};

struct Mat43 {
    float m[4][3];
    Mat43(float s);
    Mat43(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31,
          float m02, float m12, float m22, float m32);
    Mat43(const Mat44 &s);
    Mat43(const Euler &e);
    Mat43(const Vec3 &r);
    Mat43(const Quat &q);
    Mat43(const Mat33 &r);
    Mat43(const Mat34 &r);
    Mat43(const Mat33 &r, const Vec3 &t);
    Mat43(const Mat34 &r, const Vec3 &t);
    Mat43(const Mat43p &s);
    Vec3 &f_0a1a70();
    Mat33 &f_0a1a78();
    const Mat33 &f_0a1dd8() const;
    const Vec3 &f_0a1de0() const;
    Vec3 &f_0a1de8(int i);
    const Vec3 &f_0a1dfc(int i) const;
    Mat43 &f_0a1ee8();
    Mat43 &f_0a218c(Angle a, int i, int j);
    Mat43 &f_0a2244(Angle a);
    Mat43 &f_0a2264(Angle a);
    Mat43 &f_0a2284(Angle a);
    float f_0a22a4() const;
};

/* @implements 0x0a1980 us _ZN5Mat43C2Ef
   WHAT IT DOES: Builds a scaled identity rotation (the diagonal set to s) with no
   translation. */
/* @implements 0x0a19b4 us _ZN5Mat43C1Ef
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(float s)
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[0][0] = m[1][1] = m[2][2] = s;
}

/* @implements 0x0a19e8 us _ZN5Mat43C2Effffffffffff
   WHAT IT DOES: Builds the matrix from twelve elements given column by column. */
/* @implements 0x0a1a2c us _ZN5Mat43C1Effffffffffff
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(float m00, float m10, float m20, float m30, float m01, float m11, float m21,
             float m31, float m02, float m12, float m22, float m32)
{
    m[0][0] = m00;
    m[1][0] = m10;
    m[2][0] = m20;
    m[3][0] = m30;
    m[0][1] = m01;
    m[1][1] = m11;
    m[2][1] = m21;
    m[3][1] = m31;
    m[0][2] = m02;
    m[1][2] = m12;
    m[2][2] = m22;
    m[3][2] = m32;
}

/* @implements 0x0a1a70 us f_0a1a70
   WHAT IT DOES: Returns the translation row. */
Vec3 &Mat43::f_0a1a70()
{
    return *(Vec3 *)m[3];
}

/* @implements 0x0a1a78 us f_0a1a78
   WHAT IT DOES: Returns the rotation part. */
Mat33 &Mat43::f_0a1a78()
{
    return *(Mat33 *)m;
}

/* @implements 0x0a1a80 us _ZN5Mat43C2ERK5Euler
   WHAT IT DOES: Builds the rotation from Euler angles, with no translation. */
/* @implements 0x0a1af8 us _ZN5Mat43C1ERK5Euler
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Euler &e)
{
    Mat33 t;
    f_09d450(&t, e);
    Vec3 *v = (Vec3 *)m[3];
    *(Mat33 *)m = t;
    v->v[0] = v->v[1] = v->v[2] = 0;
}

/* @implements 0x0a1b70 us _ZN5Mat43C2ERK4Vec3
   WHAT IT DOES: Builds the rotation from a rotation vector, with no translation. */
/* @implements 0x0a1be8 us _ZN5Mat43C1ERK4Vec3
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Vec3 &r)
{
    Mat33 t;
    f_09d6f4(&t, r);
    Vec3 *v = (Vec3 *)m[3];
    *(Mat33 *)m = t;
    v->v[0] = v->v[1] = v->v[2] = 0;
}

/* @implements 0x0a1c60 us _ZN5Mat43C2ERK4Quat
   WHAT IT DOES: Builds the rotation from a quaternion, with no translation. */
/* @implements 0x0a1cd8 us _ZN5Mat43C1ERK4Quat
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Quat &q)
{
    Mat33 t;
    f_09d858(&t, q);
    Vec3 *v = (Vec3 *)m[3];
    *(Mat33 *)m = t;
    v->v[0] = v->v[1] = v->v[2] = 0;
}

/* @implements 0x0a1d50 us _ZN5Mat43C2ERK5Mat44
   WHAT IT DOES: Builds the matrix from a 4x4 matrix's first three columns, column by column. */
/* @implements 0x0a1d94 us _ZN5Mat43C1ERK5Mat44
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Mat44 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 4; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x0a1dd8 us f_0a1dd8
   WHAT IT DOES: Returns the rotation part (read only). */
const Mat33 &Mat43::f_0a1dd8() const
{
    return *(const Mat33 *)m;
}

/* @implements 0x0a1de0 us f_0a1de0
   WHAT IT DOES: Returns the translation row (read only). */
const Vec3 &Mat43::f_0a1de0() const
{
    return *(const Vec3 *)m[3];
}

/* @implements 0x0a1de8 us f_0a1de8
   WHAT IT DOES: Returns row i. */
Vec3 &Mat43::f_0a1de8(int i)
{
    return *(Vec3 *)m[i];
}

/* @implements 0x0a1dfc us f_0a1dfc
   WHAT IT DOES: Returns row i (read only). */
const Vec3 &Mat43::f_0a1dfc(int i) const
{
    return *(const Vec3 *)m[i];
}

/* @implements 0x0a1e10 us f_0a1e10
   WHAT IT DOES: Sets the vector to a transformed by the matrix (rotation applied as a row
   vector, then the translation added) and returns it. */
Vec3 &Vec3::f_0a1e10(const Mat43 &m, const Vec3 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[1][0] * a.v[1] + m.m[2][0] * a.v[2] + m.m[3][0];
    v[1] = m.m[0][1] * a.v[0] + m.m[1][1] * a.v[1] + m.m[2][1] * a.v[2] + m.m[3][1];
    v[2] = m.m[0][2] * a.v[0] + m.m[1][2] * a.v[1] + m.m[2][2] * a.v[2] + m.m[3][2];
    return *this;
}

/* @implements 0x0a1ec0 us f_0a1ec0
   WHAT IT DOES: The same as f_0a1e10, through a call. */
Vec3 &Vec3::f_0a1ec0(const Mat43 &m, const Vec3 &a)
{
    f_0a1e10(m, a);
    return *this;
}

/* @implements 0x0a1ee8 us f_0a1ee8
   WHAT IT DOES: Sets the matrix to the identity and returns it. */
Mat43 &Mat43::f_0a1ee8()
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[0][0] = m[1][1] = m[2][2] = 1.0f;
    return *this;
}

/* @implements 0x0a1f28 us _ZN5Mat44C2ERK5Mat43
   WHAT IT DOES: Builds a 4x4 matrix from a 4x3 one: its three columns, and a last column of
   (0, 0, 0, 1). */
/* @implements 0x0a1f80 us _ZN5Mat44C1ERK5Mat43
   WHAT IT DOES: The same, as the complete object constructor. */
Mat44::Mat44(const Mat43 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 4; i++)
            m[i][j] = s.m[i][j];
    m[2][3] = 0;
    m[1][3] = 0;
    m[0][3] = 0;
    m[3][3] = 1.0f;
}

/* @implements 0x0a218c us f_0a218c
   WHAT IT DOES: Rotates every row's (i, j) pair of elements (translation included) by the
   angle and returns the matrix. */
Mat43 &Mat43::f_0a218c(Angle a, int i, int j)
{
    float c = f_099fc4(a.Rad());
    float s = f_09a154(a.Rad());
    for (int r = 0; r < 4; r++) {
        float x = m[r][i], y = m[r][j];
        m[r][i] = x * s - y * c;
        m[r][j] = x * c + y * s;
    }
    return *this;
}

/* @implements 0x0a2244 us f_0a2244
   WHAT IT DOES: Rotates about the x axis (the (1, 2) pairs). */
Mat43 &Mat43::f_0a2244(Angle a)
{
    return f_0a218c(a, 1, 2);
}

/* @implements 0x0a2264 us f_0a2264
   WHAT IT DOES: Rotates about the y axis (the (2, 0) pairs). */
Mat43 &Mat43::f_0a2264(Angle a)
{
    return f_0a218c(a, 2, 0);
}

/* @implements 0x0a2284 us f_0a2284
   WHAT IT DOES: Rotates about the z axis (the (0, 1) pairs). */
Mat43 &Mat43::f_0a2284(Angle a)
{
    return f_0a218c(a, 0, 1);
}

/* @implements 0x0a22a4 us f_0a22a4
   WHAT IT DOES: Returns the determinant of the matrix extended to 4x4. */
float Mat43::f_0a22a4() const
{
    Mat44 t(*this);
    return t.f_09b9f4();
}

/* @implements 0x0a23ac us _ZN5Mat43C2ERK5Mat33
   WHAT IT DOES: Builds the matrix from a rotation, with no translation. */
/* @implements 0x0a23f4 us _ZN5Mat43C1ERK5Mat33
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Mat33 &r)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
}

/* @implements 0x0a243c us _ZN5Mat43C2ERK5Mat34
   WHAT IT DOES: Builds the matrix from a padded-row rotation, with no translation. */
/* @implements 0x0a2488 us _ZN5Mat43C1ERK5Mat34
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Mat34 &r)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
}

/* @implements 0x0a24d4 us _ZN5Mat43C2ERK5Mat33RK4Vec3
   WHAT IT DOES: Builds the matrix from a rotation and a translation. */
/* @implements 0x0a2528 us _ZN5Mat43C1ERK5Mat33RK4Vec3
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Mat33 &r, const Vec3 &t)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = t.v[0];
    m[3][1] = t.v[1];
    m[3][2] = t.v[2];
}

/* @implements 0x0a257c us _ZN5Mat43C2ERK5Mat34RK4Vec3
   WHAT IT DOES: Builds the matrix from a padded-row rotation and a translation. */
/* @implements 0x0a25d4 us _ZN5Mat43C1ERK5Mat34RK4Vec3
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Mat34 &r, const Vec3 &t)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = t.v[0];
    m[3][1] = t.v[1];
    m[3][2] = t.v[2];
}

/* @implements 0x0a262c us _ZN5Mat43C2ERK6Mat43p
   WHAT IT DOES: Builds the matrix from its padded-row form, column by column. */
/* @implements 0x0a2670 us _ZN5Mat43C1ERK6Mat43p
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43::Mat43(const Mat43p &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 4; i++)
            m[i][j] = s.m[i][j];
}
