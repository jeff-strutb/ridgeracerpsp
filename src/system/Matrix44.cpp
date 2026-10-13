/* The four by four float matrix of the camera math library (retail 0x09b598 to 0x09bd84). */

struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

struct Mat44 {
    float m[4][4];
    Mat44(float s);
    Mat44(const float (*src)[4]);
    Mat44 &f_09b8b8();
    Mat44 &f_09b908();
    float f_09b9f4() const;
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
