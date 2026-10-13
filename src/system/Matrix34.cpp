/* The three by three float matrix of the camera math library (retail 0x09f344 to 0x09d228). */

extern "C" {
float f_099fc4(float a);
float f_09a154(float a);
}

/* An angle in radians, passed by value in an integer register. */
union Angle {
    float a;
    float Rad() const { return a; }
};

struct Mat34;

struct Mat33 {
    float m[3][3];
};

/* A 3x3 matrix with a translation row. */
struct Mat43 {
    float m[4][3];
};

struct Mat44 {
    float m[4][4];
};

struct Vec3 {
    float v[3];
    Vec3 &f_09fe84(const Mat34 &m, const Vec3 &a);
    Vec3 &f_09ff1c(const Mat34 &m, const Vec3 &a);
    Vec3 &f_0a0994(const Mat34 &m, const Vec3 &a);
};

struct Mat34 {
    float m[3][4];
    Mat34();
    Mat34(float s);
    Mat34(const float (*src)[3]);
    Mat34(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12,
          float m22);
    Mat34(const Vec3 &r0, const Vec3 &r1, const Vec3 &r2);
    Mat34(const Mat34 &s);
    Mat34(const Mat33 &s);
    Mat34(const Mat43 &s);
    Mat34(const Mat44 &s);
    Mat34 &f_09ff44();
    float f_0a0140() const;
    Mat34 &f_0a039c();
    Mat34 f_0a0944() const;
    Mat34 &f_0a082c(Angle a, int i, int j);
    Mat34 &f_0a08e4(Angle a);
    Mat34 &f_0a0904(Angle a);
    Mat34 &f_0a0924(Angle a);
};

/* @implements 0x09f344 us _ZN5Mat34C2Ev
   WHAT IT DOES: Leaves the matrix uninitialised (base object constructor). */
/* @implements 0x09f34c us _ZN5Mat34C1Ev
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34()
{
}

/* @implements 0x09f524 us _ZN5Mat34C2Ef
   WHAT IT DOES: Builds a scaled identity: the diagonal set to s, every other element zero. */
/* @implements 0x09f54c us _ZN5Mat34C1Ef
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(float s)
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[0][0] = m[1][1] = m[2][2] = s;
}

/* @implements 0x09f574 us _ZN5Mat34C2EPA3_Kf
   WHAT IT DOES: Builds the transpose of a 3x3 array (into the padded rows). */
/* @implements 0x09f5c4 us _ZN5Mat34C1EPA3_Kf
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(const float (*src)[3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[j][i] = src[i][j];
}

/* @implements 0x09f614 us _ZN5Mat34C2Efffffffff
   WHAT IT DOES: Builds the matrix from nine elements given column by column. */
/* @implements 0x09f640 us _ZN5Mat34C1Efffffffff
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(float m00, float m10, float m20, float m01, float m11, float m21, float m02,
             float m12, float m22)
{
    m[0][0] = m00;
    m[1][0] = m10;
    m[2][0] = m20;
    m[0][1] = m01;
    m[1][1] = m11;
    m[2][1] = m21;
    m[0][2] = m02;
    m[1][2] = m12;
    m[2][2] = m22;
}

/* @implements 0x09f66c us _ZN5Mat34C2ERK4Vec3S2_S2_
   WHAT IT DOES: Builds the matrix from three row vectors. */
/* @implements 0x09f6b8 us _ZN5Mat34C1ERK4Vec3S2_S2_
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(const Vec3 &r0, const Vec3 &r1, const Vec3 &r2)
{
    m[0][0] = r0.v[0];
    m[0][1] = r0.v[1];
    m[0][2] = r0.v[2];
    m[1][0] = r1.v[0];
    m[1][1] = r1.v[1];
    m[1][2] = r1.v[2];
    m[2][0] = r2.v[0];
    m[2][1] = r2.v[1];
    m[2][2] = r2.v[2];
}

/* @implements 0x09fe04 us _ZN5Mat34C2ERKS_
   WHAT IT DOES: Copies a matrix, column by column. */
/* @implements 0x09fe44 us _ZN5Mat34C1ERKS_
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(const Mat34 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x09fe84 us f_09fe84
   WHAT IT DOES: Sets the vector to the transposed matrix times a and returns it. */
Vec3 &Vec3::f_09fe84(const Mat34 &m, const Vec3 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[1][0] * a.v[1] + m.m[2][0] * a.v[2];
    v[1] = m.m[0][1] * a.v[0] + m.m[1][1] * a.v[1] + m.m[2][1] * a.v[2];
    v[2] = m.m[0][2] * a.v[0] + m.m[1][2] * a.v[1] + m.m[2][2] * a.v[2];
    return *this;
}

/* @implements 0x09ff1c us f_09ff1c
   WHAT IT DOES: The same as f_09fe84, through a call. */
Vec3 &Vec3::f_09ff1c(const Mat34 &m, const Vec3 &a)
{
    f_09fe84(m, a);
    return *this;
}

/* @implements 0x09ff44 us f_09ff44
   WHAT IT DOES: Sets the matrix to the identity and returns it. */
Mat34 &Mat34::f_09ff44()
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[0][0] = m[1][1] = m[2][2] = 1.0f;
    return *this;
}

/* @implements 0x0a0140 us f_0a0140
   WHAT IT DOES: Returns the determinant. */
float Mat34::f_0a0140() const
{
    return m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] + m[1][0] * m[2][1] * m[0][2]
           - m[1][0] * m[0][1] * m[2][2] + m[2][0] * m[1][2] * m[0][1] - m[2][0] * m[1][1] * m[0][2];
}

/* @implements 0x0a039c us f_0a039c
   WHAT IT DOES: Transposes the matrix in place and returns it. */
Mat34 &Mat34::f_0a039c()
{
    float t;
    t = m[1][0];
    m[1][0] = m[0][1];
    m[0][1] = t;
    t = m[2][0];
    m[2][0] = m[0][2];
    m[0][2] = t;
    t = m[2][1];
    m[2][1] = m[1][2];
    m[1][2] = t;
    return *this;
}

/* @draft 0x0a0944 us f_0a0944
   WHAT IT DOES: Returns the transposed matrix.
   Remaining difference: as for the 3x3 matrix's f_09e4b8, retail loads the eighth element
   last; this source loads it second. */
Mat34 Mat34::f_0a0944() const
{
    return Mat34(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}

/* @implements 0x0a0994 us f_0a0994
   WHAT IT DOES: Sets the vector to the matrix times a and returns it. */
Vec3 &Vec3::f_0a0994(const Mat34 &m, const Vec3 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[0][1] * a.v[1] + m.m[0][2] * a.v[2];
    v[1] = m.m[1][0] * a.v[0] + m.m[1][1] * a.v[1] + m.m[1][2] * a.v[2];
    v[2] = m.m[2][0] * a.v[0] + m.m[2][1] * a.v[1] + m.m[2][2] * a.v[2];
    return *this;
}

/* @implements 0x0a0e3c us _ZN5Mat34C2ERK5Mat33
   WHAT IT DOES: Builds the matrix from a 3x3 matrix, column by column. */
/* @implements 0x0a0e80 us _ZN5Mat34C1ERK5Mat33
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(const Mat33 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x0a0ec4 us _ZN5Mat34C2ERK5Mat43
   WHAT IT DOES: Builds the matrix from a 4x3 matrix's rotation part, column by column. */
/* @implements 0x0a0f08 us _ZN5Mat34C1ERK5Mat43
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(const Mat43 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x0a0f4c us _ZN5Mat34C2ERK5Mat44
   WHAT IT DOES: Builds the matrix from a 4x4 matrix's upper left 3x3, column by column. */
/* @implements 0x0a0f8c us _ZN5Mat34C1ERK5Mat44
   WHAT IT DOES: The same, as the complete object constructor. */
Mat34::Mat34(const Mat44 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x0a082c us f_0a082c
   WHAT IT DOES: Rotates every row's (i, j) pair of elements by the angle and returns the
   matrix. */
Mat34 &Mat34::f_0a082c(Angle a, int i, int j)
{
    float c = f_099fc4(a.Rad());
    float s = f_09a154(a.Rad());
    for (int r = 0; r < 3; r++) {
        float x = m[r][i], y = m[r][j];
        m[r][i] = x * s - y * c;
        m[r][j] = x * c + y * s;
    }
    return *this;
}

/* @implements 0x0a08e4 us f_0a08e4
   WHAT IT DOES: Rotates about the x axis (the (1, 2) pairs). */
Mat34 &Mat34::f_0a08e4(Angle a)
{
    return f_0a082c(a, 1, 2);
}

/* @implements 0x0a0904 us f_0a0904
   WHAT IT DOES: Rotates about the y axis (the (2, 0) pairs). */
Mat34 &Mat34::f_0a0904(Angle a)
{
    return f_0a082c(a, 2, 0);
}

/* @implements 0x0a0924 us f_0a0924
   WHAT IT DOES: Rotates about the z axis (the (0, 1) pairs). */
Mat34 &Mat34::f_0a0924(Angle a)
{
    return f_0a082c(a, 0, 1);
}
