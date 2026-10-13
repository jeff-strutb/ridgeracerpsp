/* The 4x3 float matrix of the camera math library: a 3x3 rotation in its first three rows and
   a translation in the fourth (retail 0x0a2890 to 0x0a22cc). */

extern "C" {
float f_099fc4(float a);
float f_09a154(float a);
}

/* An angle in radians, passed by value in an integer register. */
union Angle {
    float a;
    float Rad() const { return a; }
};

struct Mat43p;

struct Vec3 {
    float v[3];
    Vec3 &f_0a2cd8(const Mat43p &m, const Vec3 &a);
    Vec3 &f_0a2d88(const Mat43p &m, const Vec3 &a);
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

/* The 4x3 matrix without padding. */
struct Mat43 {
    float m[4][3];
};

/* The padded-row 3x3 matrix's constructors from Euler angles, a rotation vector and a quaternion
   (complete object forms), called on an uninitialised matrix. */
extern "C" {
void f_09f92c(Mat34 *m, const Euler &e);
void f_09fbc4(Mat34 *m, const Vec3 &r);
void f_09fd1c(Mat34 *m, const Quat &q);
}

struct Mat44 {
    float m[4][4];
    Mat44(const Mat43p &s);
    float f_09b9f4() const;
};

struct Mat43p {
    float m[4][4];
    Mat43p(float s);
    Mat43p(float m00, float m10, float m20, float m30, float m01, float m11, float m21, float m31,
          float m02, float m12, float m22, float m32);
    Mat43p(const Mat44 &s);
    Mat43p(const Euler &e);
    Mat43p(const Vec3 &r);
    Mat43p(const Quat &q);
    Mat43p(const Mat33 &r);
    Mat43p(const Mat34 &r);
    Mat43p(const Mat33 &r, const Vec3 &t);
    Mat43p(const Mat34 &r, const Vec3 &t);
    Mat43p(const Mat43 &s);
    Vec3 &f_0a2980();
    Mat34 &f_0a2988();
    const Mat34 &f_0a2cb0() const;
    const Vec3 &f_0a2cb8() const;
    Vec3 &f_0a2cc0(int i);
    const Vec3 &f_0a2ccc(int i) const;
    Mat43p &f_0a2db0();
    Mat43p &f_0a304c(Angle a, int i, int j);
    Mat43p &f_0a3104(Angle a);
    Mat43p &f_0a3124(Angle a);
    Mat43p &f_0a3144(Angle a);
    float f_0a3164() const;
};

/* @implements 0x0a2890 us _ZN6Mat43pC2Ef
   WHAT IT DOES: Builds a scaled identity rotation (the diagonal set to s) with no
   translation. */
/* @implements 0x0a28c4 us _ZN6Mat43pC1Ef
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(float s)
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

/* @implements 0x0a28f8 us _ZN6Mat43pC2Effffffffffff
   WHAT IT DOES: Builds the matrix from twelve elements given column by column. */
/* @implements 0x0a293c us _ZN6Mat43pC1Effffffffffff
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(float m00, float m10, float m20, float m30, float m01, float m11, float m21,
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

/* @implements 0x0a2980 us f_0a2980
   WHAT IT DOES: Returns the translation row. */
Vec3 &Mat43p::f_0a2980()
{
    return *(Vec3 *)m[3];
}

/* @implements 0x0a2988 us f_0a2988
   WHAT IT DOES: Returns the rotation part. */
Mat34 &Mat43p::f_0a2988()
{
    return *(Mat34 *)m;
}

/* @implements 0x0a2990 us _ZN6Mat43pC2ERK5Euler
   WHAT IT DOES: Builds the rotation from Euler angles, with no translation. */
/* @implements 0x0a2a00 us _ZN6Mat43pC1ERK5Euler
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Euler &e)
{
    Mat34 t;
    f_09f92c(&t, e);
    Vec3 *v = (Vec3 *)m[3];
    *(Mat34 *)m = t;
    v->v[0] = v->v[1] = v->v[2] = 0;
}

/* @implements 0x0a2a70 us _ZN6Mat43pC2ERK4Vec3
   WHAT IT DOES: Builds the rotation from a rotation vector, with no translation. */
/* @implements 0x0a2ae0 us _ZN6Mat43pC1ERK4Vec3
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Vec3 &r)
{
    Mat34 t;
    f_09fbc4(&t, r);
    Vec3 *v = (Vec3 *)m[3];
    *(Mat34 *)m = t;
    v->v[0] = v->v[1] = v->v[2] = 0;
}

/* @implements 0x0a2b50 us _ZN6Mat43pC2ERK4Quat
   WHAT IT DOES: Builds the rotation from a quaternion, with no translation. */
/* @implements 0x0a2bc0 us _ZN6Mat43pC1ERK4Quat
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Quat &q)
{
    Mat34 t;
    f_09fd1c(&t, q);
    Vec3 *v = (Vec3 *)m[3];
    *(Mat34 *)m = t;
    v->v[0] = v->v[1] = v->v[2] = 0;
}

/* @implements 0x0a2c30 us _ZN6Mat43pC2ERK5Mat44
   WHAT IT DOES: Builds the matrix from a 4x4 matrix's first three columns, column by column. */
/* @implements 0x0a2c70 us _ZN6Mat43pC1ERK5Mat44
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Mat44 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 4; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x0a2cb0 us f_0a2cb0
   WHAT IT DOES: Returns the rotation part (read only). */
const Mat34 &Mat43p::f_0a2cb0() const
{
    return *(const Mat34 *)m;
}

/* @implements 0x0a2cb8 us f_0a2cb8
   WHAT IT DOES: Returns the translation row (read only). */
const Vec3 &Mat43p::f_0a2cb8() const
{
    return *(const Vec3 *)m[3];
}

/* @implements 0x0a2cc0 us f_0a2cc0
   WHAT IT DOES: Returns row i. */
Vec3 &Mat43p::f_0a2cc0(int i)
{
    return *(Vec3 *)m[i];
}

/* @implements 0x0a2ccc us f_0a2ccc
   WHAT IT DOES: Returns row i (read only). */
const Vec3 &Mat43p::f_0a2ccc(int i) const
{
    return *(const Vec3 *)m[i];
}

/* @implements 0x0a2cd8 us f_0a2cd8
   WHAT IT DOES: Sets the vector to a transformed by the matrix (rotation applied as a row
   vector, then the translation added) and returns it. */
Vec3 &Vec3::f_0a2cd8(const Mat43p &m, const Vec3 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[1][0] * a.v[1] + m.m[2][0] * a.v[2] + m.m[3][0];
    v[1] = m.m[0][1] * a.v[0] + m.m[1][1] * a.v[1] + m.m[2][1] * a.v[2] + m.m[3][1];
    v[2] = m.m[0][2] * a.v[0] + m.m[1][2] * a.v[1] + m.m[2][2] * a.v[2] + m.m[3][2];
    return *this;
}

/* @implements 0x0a2d88 us f_0a2d88
   WHAT IT DOES: The same as f_0a2cd8, through a call. */
Vec3 &Vec3::f_0a2d88(const Mat43p &m, const Vec3 &a)
{
    f_0a2cd8(m, a);
    return *this;
}

/* @implements 0x0a2db0 us f_0a2db0
   WHAT IT DOES: Sets the matrix to the identity and returns it. */
Mat43p &Mat43p::f_0a2db0()
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

/* @implements 0x0a2df0 us _ZN5Mat44C2ERK6Mat43p
   WHAT IT DOES: Builds a 4x4 matrix from a 4x3 one: its three columns, and a last column of
   (0, 0, 0, 1). */
/* @implements 0x0a2e44 us _ZN5Mat44C1ERK6Mat43p
   WHAT IT DOES: The same, as the complete object constructor. */
Mat44::Mat44(const Mat43p &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 4; i++)
            m[i][j] = s.m[i][j];
    m[2][3] = 0;
    m[1][3] = 0;
    m[0][3] = 0;
    m[3][3] = 1.0f;
}

/* @implements 0x0a304c us f_0a304c
   WHAT IT DOES: Rotates every row's (i, j) pair of elements (translation included) by the
   angle and returns the matrix. */
Mat43p &Mat43p::f_0a304c(Angle a, int i, int j)
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

/* @implements 0x0a3104 us f_0a3104
   WHAT IT DOES: Rotates about the x axis (the (1, 2) pairs). */
Mat43p &Mat43p::f_0a3104(Angle a)
{
    return f_0a304c(a, 1, 2);
}

/* @implements 0x0a3124 us f_0a3124
   WHAT IT DOES: Rotates about the y axis (the (2, 0) pairs). */
Mat43p &Mat43p::f_0a3124(Angle a)
{
    return f_0a304c(a, 2, 0);
}

/* @implements 0x0a3144 us f_0a3144
   WHAT IT DOES: Rotates about the z axis (the (0, 1) pairs). */
Mat43p &Mat43p::f_0a3144(Angle a)
{
    return f_0a304c(a, 0, 1);
}

/* @implements 0x0a3164 us f_0a3164
   WHAT IT DOES: Returns the determinant of the matrix extended to 4x4. */
float Mat43p::f_0a3164() const
{
    Mat44 t(*this);
    return t.f_09b9f4();
}

/* @implements 0x0a3264 us _ZN6Mat43pC2ERK5Mat33
   WHAT IT DOES: Builds the matrix from a rotation, with no translation. */
/* @implements 0x0a32b0 us _ZN6Mat43pC1ERK5Mat33
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Mat33 &r)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
}

/* @implements 0x0a32fc us _ZN6Mat43pC2ERK5Mat34
   WHAT IT DOES: Builds the matrix from a padded-row rotation, with no translation. */
/* @implements 0x0a3344 us _ZN6Mat43pC1ERK5Mat34
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Mat34 &r)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
}

/* @implements 0x0a338c us _ZN6Mat43pC2ERK5Mat33RK4Vec3
   WHAT IT DOES: Builds the matrix from a rotation and a translation. */
/* @implements 0x0a33e4 us _ZN6Mat43pC1ERK5Mat33RK4Vec3
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Mat33 &r, const Vec3 &t)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = t.v[0];
    m[3][1] = t.v[1];
    m[3][2] = t.v[2];
}

/* @implements 0x0a343c us _ZN6Mat43pC2ERK5Mat34RK4Vec3
   WHAT IT DOES: Builds the matrix from a padded-row rotation and a translation. */
/* @implements 0x0a3490 us _ZN6Mat43pC1ERK5Mat34RK4Vec3
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Mat34 &r, const Vec3 &t)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = r.m[i][j];
    m[3][0] = t.v[0];
    m[3][1] = t.v[1];
    m[3][2] = t.v[2];
}

/* @implements 0x0a34e4 us _ZN6Mat43pC2ERK5Mat43
   WHAT IT DOES: Builds the matrix from its unpadded form, column by column. */
/* @implements 0x0a3528 us _ZN6Mat43pC1ERK5Mat43
   WHAT IT DOES: The same, as the complete object constructor. */
Mat43p::Mat43p(const Mat43 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 4; i++)
            m[i][j] = s.m[i][j];
}
