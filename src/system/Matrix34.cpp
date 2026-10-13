/* The three by three float matrix of the camera math library (retail 0x09f344 to 0x09d228). */

struct Vec3 {
    float v[3];
};

struct Mat34 {
    float m[3][4];
    Mat34();
    Mat34(float s);
    Mat34(const float (*src)[3]);
    Mat34(float m00, float m10, float m20, float m01, float m11, float m21, float m02, float m12,
          float m22);
    Mat34(const Vec3 &r0, const Vec3 &r1, const Vec3 &r2);
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
