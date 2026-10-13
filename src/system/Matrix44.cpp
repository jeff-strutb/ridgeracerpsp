/* The four by four float matrix of the camera math library (retail 0x09b598 to 0x09bd84). */

struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

struct Vec3 {
    float v[3];
};

struct Mat33 {
    float m[3][3];
};

struct Mat34 {
    float m[3][4];
};

struct Mat44 {
    float m[4][4];
    Mat44(const Mat33 &s);
    Mat44(const Mat34 &s);
    Vec3 &f_0a3748(int i);
    Vec3 &f_0a3754();
    Vec3 &f_0a375c();
    Vec3 &f_0a3764();
    const Vec3 &f_0a376c(int i) const;
    const Vec3 &f_0a3778() const;
    const Vec3 &f_0a3780() const;
    const Vec3 &f_0a3788() const;
    Mat44(float s);
    Mat44(const float (*src)[4]);
    Mat44 &f_09b8b8();
    Mat44 &f_09b908();
    float f_09b9f4() const;
    Mat44 &f_09bb28(const Mat44 &a, const Mat44 &b);
};

/* @implements 0x09b7a0 us _ZN5Mat44C2Ef
   WHAT IT DOES: Builds a scaled identity: the diagonal set to s, every other element zero. */
/* @implements 0x09b7e4 us _ZN5Mat44C1Ef
   WHAT IT DOES: The same, as the complete object constructor. */
Mat44::Mat44(float s)
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = s;
}

/* @implements 0x09b828 us _ZN5Mat44C2EPA4_Kf
   WHAT IT DOES: Builds the transpose of a 4x4 array. */
/* @implements 0x09b870 us _ZN5Mat44C1EPA4_Kf
   WHAT IT DOES: The same, as the complete object constructor. */
Mat44::Mat44(const float (*src)[4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[j][i] = src[i][j];
}

/* @implements 0x09b8b8 us f_09b8b8
   WHAT IT DOES: Sets the matrix to the identity and returns it. */
Mat44 &Mat44::f_09b8b8()
{
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    return *this;
}

/* @draft 0x09b908 us f_09b908
   WHAT IT DOES: Inverts the matrix in place by Gauss-Jordan elimination on the diagonal
   (no pivot search) and returns it.
   Remaining difference: retail recomputes the pivot's address as ((4k + k) << 2) from two
   counters each pass; this source strength-reduces it into one pointer. */
Mat44 &Mat44::f_09b908()
{
    for (int k = 0; k < 4; k++) {
        float p = m[k][k];
        for (int i = 0; i < 4; i++)
            m[i][k] /= p;
        m[k][k] = 1.0f / p;
        for (int j = 0; j < 4; j++) {
            if (j == k)
                continue;
            float f = m[k][j];
            for (int i = 0; i < 4; i++) {
                if (i == k)
                    m[k][j] = -f / p;
                else
                    m[i][j] -= m[i][k] * f;
            }
        }
    }
    return *this;
}

/* @draft 0x09b9f4 us f_09b9f4
   WHAT IT DOES: Returns the determinant: eliminates a copy of the matrix the same way as the
   inverse and multiplies the pivots. Same remaining difference as the inverse. */
float Mat44::f_09b9f4() const
{
    Mat44 t = *this;
    float d = 1.0f;
    for (int k = 0; k < 4; k++) {
        float p = t.m[k][k];
        d *= p;
        for (int i = 0; i < 4; i++)
            t.m[i][k] /= p;
        t.m[k][k] = 1.0f / p;
        for (int j = 0; j < 4; j++) {
            if (j == k)
                continue;
            float f = t.m[k][j];
            for (int i = 0; i < 4; i++) {
                if (i == k)
                    t.m[k][j] = -f / p;
                else
                    t.m[i][j] -= t.m[i][k] * f;
            }
        }
    }
    return d;
}

/* @draft 0x09bb28 us f_09bb28
   WHAT IT DOES: Sets the matrix to the product b * a (row-major, column vectors) and returns
   it, one column per pass.
   Remaining difference: retail keeps a's row addresses as separate counters 16, 32, 48 (+4
   per pass) added to a's base; this source steps one pointer into a (flat indexing tried). */
Mat44 &Mat44::f_09bb28(const Mat44 &a, const Mat44 &b)
{
    for (int i = 0; i < 4; i++) {
        m[0][i] = a.m[0][i] * b.m[0][0] + a.m[1][i] * b.m[0][1] + a.m[2][i] * b.m[0][2] + a.m[3][i] * b.m[0][3];
        m[1][i] = a.m[0][i] * b.m[1][0] + a.m[1][i] * b.m[1][1] + a.m[2][i] * b.m[1][2] + a.m[3][i] * b.m[1][3];
        m[2][i] = a.m[0][i] * b.m[2][0] + a.m[1][i] * b.m[2][1] + a.m[2][i] * b.m[2][2] + a.m[3][i] * b.m[2][3];
        m[3][i] = a.m[0][i] * b.m[3][0] + a.m[1][i] * b.m[3][1] + a.m[2][i] * b.m[3][2] + a.m[3][i] * b.m[3][3];
    }
    return *this;
}

/* @implements 0x0a3748 us f_0a3748
   WHAT IT DOES: Returns row i as a vector. */
Vec3 &Mat44::f_0a3748(int i)
{
    return *(Vec3 *)m[i];
}

/* @implements 0x0a3754 us f_0a3754
   WHAT IT DOES: Returns row 0 (the x axis) as a vector. */
Vec3 &Mat44::f_0a3754()
{
    return *(Vec3 *)m[0];
}

/* @implements 0x0a375c us f_0a375c
   WHAT IT DOES: Returns row 1 (the y axis) as a vector. */
Vec3 &Mat44::f_0a375c()
{
    return *(Vec3 *)m[1];
}

/* @implements 0x0a3764 us f_0a3764
   WHAT IT DOES: Returns row 2 (the z axis) as a vector. */
Vec3 &Mat44::f_0a3764()
{
    return *(Vec3 *)m[2];
}

/* @implements 0x0a376c us f_0a376c
   WHAT IT DOES: Returns row i as a vector (read only). */
const Vec3 &Mat44::f_0a376c(int i) const
{
    return *(const Vec3 *)m[i];
}

/* @implements 0x0a3778 us f_0a3778
   WHAT IT DOES: Returns row 0 (the x axis) as a vector (read only). */
const Vec3 &Mat44::f_0a3778() const
{
    return *(const Vec3 *)m[0];
}

/* @implements 0x0a3780 us f_0a3780
   WHAT IT DOES: Returns row 1 (the y axis) as a vector (read only). */
const Vec3 &Mat44::f_0a3780() const
{
    return *(const Vec3 *)m[1];
}

/* @implements 0x0a3788 us f_0a3788
   WHAT IT DOES: Returns row 2 (the z axis) as a vector (read only). */
const Vec3 &Mat44::f_0a3788() const
{
    return *(const Vec3 *)m[2];
}

/* @implements 0x0a3790 us _ZN5Mat44C2ERK5Mat33
   WHAT IT DOES: Builds a 4x4 matrix from a 3x3 one, with a zero last row and column and a 1 in
   the corner. */
/* @implements 0x0a37fc us _ZN5Mat44C1ERK5Mat33
   WHAT IT DOES: The same, as the complete object constructor. */
Mat44::Mat44(const Mat33 &s)
{
    for (int j = 0; j < 3; j++) {
        int i;
        for (i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
        m[i][j] = 0;
    }
    m[2][3] = 0;
    m[1][3] = 0;
    m[0][3] = 0;
    m[3][3] = 1.0f;
}

/* @implements 0x0a3868 us _ZN5Mat44C2ERK5Mat34
   WHAT IT DOES: Builds a 4x4 matrix from a padded-row 3x3 one, with a zero last row and column
   and a 1 in the corner. */
/* @implements 0x0a38d0 us _ZN5Mat44C1ERK5Mat34
   WHAT IT DOES: The same, as the complete object constructor. */
Mat44::Mat44(const Mat34 &s)
{
    for (int j = 0; j < 3; j++) {
        int i;
        for (i = 0; i < 3; i++)
            m[i][j] = s.m[i][j];
        m[i][j] = 0;
    }
    m[2][3] = 0;
    m[1][3] = 0;
    m[0][3] = 0;
    m[3][3] = 1.0f;
}
