/* The three by three float matrix of the camera math library (retail 0x09d038 to 0x09d228). */

struct Mat33;
struct Mat34 {
    float m[3][4];
};

struct Mat44 {
    float m[4][4];
};

/* The vector unit's 4x4 matrix (quadword aligned). */
struct VMatrix {
    float m[4][4];
} __attribute__((aligned(16)));

struct Vec3 {
    float v[3];
    Vec3 &f_09d9c8(const Mat33 &m, const Vec3 &a);
    Vec3 &f_09da60(const Mat33 &m, const Vec3 &a);
    Vec3 &f_09e508(const Mat33 &m, const Vec3 &a);
};

struct Mat33 {
    float m[3][3];
    Mat33();
    Mat33(float s);
    Mat33(const float (*src)[3]);
    Mat33(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12,
          float m22);
    Mat33(const Vec3 &r0, const Vec3 &r1, const Vec3 &r2);
    Mat33(const Mat34 &s);
    Mat33(const Mat44 &s);
    Mat33(const Mat33 &s);
    Mat33(const VMatrix &s);
    Mat33 &f_09da88();
    float f_09dc9c() const;
    Mat33 &f_09df00();
    Mat33 f_09e4b8() const;
};

/* @implements 0x09d038 us _ZN5Mat33C2Ev
   WHAT IT DOES: Leaves the matrix uninitialised (base object constructor). */
/* @implements 0x09d040 us _ZN5Mat33C1Ev
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33()
{
}

/* @implements 0x09d048 us _ZN5Mat33C2Ef
   WHAT IT DOES: Builds a scaled identity: the diagonal set to s, every other element zero. */
/* @implements 0x09d070 us _ZN5Mat33C1Ef
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(float s)
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[0][0] = m[1][1] = m[2][2] = s;
}

/* @implements 0x09d098 us _ZN5Mat33C2EPA3_Kf
   WHAT IT DOES: Builds the transpose of a 3x3 array. */
/* @implements 0x09d0e8 us _ZN5Mat33C1EPA3_Kf
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(const float (*src)[3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[j][i] = src[i][j];
}

/* @implements 0x09d138 us _ZN5Mat33C2Efffffffff
   WHAT IT DOES: Builds the matrix from nine elements given column by column. */
/* @implements 0x09d164 us _ZN5Mat33C1Efffffffff
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(float m00, float m10, float m20, float m01, float m11, float m21, float m02,
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

/* @implements 0x09d190 us _ZN5Mat33C2ERK4Vec3S2_S2_
   WHAT IT DOES: Builds the matrix from three row vectors. */
/* @implements 0x09d1dc us _ZN5Mat33C1ERK4Vec3S2_S2_
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(const Vec3 &r0, const Vec3 &r1, const Vec3 &r2)
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

/* @implements 0x09d940 us _ZN5Mat33C2ERK5Mat34
   WHAT IT DOES: Builds the matrix from a padded-row matrix, column by column. */
/* @implements 0x09d984 us _ZN5Mat33C1ERK5Mat34
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(const Mat34 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x09d9c8 us f_09d9c8
   WHAT IT DOES: Sets the vector to the transposed matrix times a and returns it. */
Vec3 &Vec3::f_09d9c8(const Mat33 &m, const Vec3 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[1][0] * a.v[1] + m.m[2][0] * a.v[2];
    v[1] = m.m[0][1] * a.v[0] + m.m[1][1] * a.v[1] + m.m[2][1] * a.v[2];
    v[2] = m.m[0][2] * a.v[0] + m.m[1][2] * a.v[1] + m.m[2][2] * a.v[2];
    return *this;
}

/* @implements 0x09da60 us f_09da60
   WHAT IT DOES: The same as f_09d9c8, through a call. */
Vec3 &Vec3::f_09da60(const Mat33 &m, const Vec3 &a)
{
    f_09d9c8(m, a);
    return *this;
}

/* @implements 0x09da88 us f_09da88
   WHAT IT DOES: Sets the matrix to the identity and returns it. */
Mat33 &Mat33::f_09da88()
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

/* @implements 0x09dc9c us f_09dc9c
   WHAT IT DOES: Returns the determinant. */
float Mat33::f_09dc9c() const
{
    return m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] + m[1][0] * m[2][1] * m[0][2]
           - m[1][0] * m[0][1] * m[2][2] + m[2][0] * m[1][2] * m[0][1] - m[2][0] * m[1][1] * m[0][2];
}

/* @implements 0x09df00 us f_09df00
   WHAT IT DOES: Transposes the matrix in place and returns it. */
Mat33 &Mat33::f_09df00()
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

/* @draft 0x09e4b8 us f_09e4b8
   WHAT IT DOES: Returns the transposed matrix.
   Remaining difference: retail loads the eighth element (into f19) last, after the other
   register arguments; this source loads it second, right after the stacked ninth. */
Mat33 Mat33::f_09e4b8() const
{
    return Mat33(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}

/* @implements 0x09e508 us f_09e508
   WHAT IT DOES: Sets the vector to the matrix times a and returns it. */
Vec3 &Vec3::f_09e508(const Mat33 &m, const Vec3 &a)
{
    v[0] = m.m[0][0] * a.v[0] + m.m[0][1] * a.v[1] + m.m[0][2] * a.v[2];
    v[1] = m.m[1][0] * a.v[0] + m.m[1][1] * a.v[1] + m.m[1][2] * a.v[2];
    v[2] = m.m[2][0] * a.v[0] + m.m[2][1] * a.v[1] + m.m[2][2] * a.v[2];
    return *this;
}

/* @implements 0x09e9b0 us _ZN5Mat33C2ERK5Mat44
   WHAT IT DOES: Builds the matrix from a 4x4 matrix's upper left 3x3, column by column. */
/* @implements 0x09e9f4 us _ZN5Mat33C1ERK5Mat44
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(const Mat44 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x09ea38 us _ZN5Mat33C2ERKS_
   WHAT IT DOES: Copies a matrix, column by column. */
/* @implements 0x09ea78 us _ZN5Mat33C1ERKS_
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(const Mat33 &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}

/* @implements 0x09eab8 us _ZN5Mat33C2ERK7VMatrix
   WHAT IT DOES: Builds the matrix from a vector unit matrix's upper left 3x3, column by
   column. */
/* @implements 0x09eafc us _ZN5Mat33C1ERK7VMatrix
   WHAT IT DOES: The same, as the complete object constructor. */
Mat33::Mat33(const VMatrix &s)
{
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
}
