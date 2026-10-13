/* Matrix products of the camera math library between its matrix shapes: 3x3, 3x3 with rows
   padded to four floats, 4x3 (a 3x3 with a translation row) and 4x4 (retail 0x09eb40 to
   0x09f524). Each sets its result row by row or column by column and returns it.
   Remaining difference for all of them: retail strength-reduces a's row (or column) into one
   pointer biased to its last element (+8, or +24 for a column) with a down-counter; this
   source biases it at the first element, and does not reduce the column forms at all. */

struct Mat33 {
    float m[3][3];
};

struct Mat34 {
    float m[3][4];
};

struct Mat43 {
    float m[4][3];
};

struct Mat44 {
    float m[4][4];
};

Mat33 &f_09ece8(Mat33 &d, const Mat33 &a, const Mat33 &b);
Mat34 &f_09ee68(Mat34 &d, const Mat33 &a, const Mat34 &b);
Mat34 &f_09efd8(Mat34 &d, const Mat33 &a, const Mat34 &b);
Mat43 &f_09f25c(Mat43 &d, const Mat33 &a, const Mat43 &b);
Mat44 &f_09f354(Mat44 &d, const Mat33 &a, const Mat44 &b);
Mat44 &f_09f43c(Mat44 &d, const Mat33 &a, const Mat44 &b);

/* @draft 0x09ece8 us f_09ece8
   WHAT IT DOES: Sets d[k][i] to the dot product of a's row i with b's row k. */
Mat33 &f_09ece8(Mat33 &d, const Mat33 &a, const Mat33 &b)
{
    for (int i = 0; i < 3; i++) {
        d.m[0][i] = a.m[i][0] * b.m[0][0] + a.m[i][1] * b.m[0][1] + a.m[i][2] * b.m[0][2];
        d.m[1][i] = a.m[i][0] * b.m[1][0] + a.m[i][1] * b.m[1][1] + a.m[i][2] * b.m[1][2];
        d.m[2][i] = a.m[i][0] * b.m[2][0] + a.m[i][1] * b.m[2][1] + a.m[i][2] * b.m[2][2];
    }
    return d;
}

/* @draft 0x09ee68 us f_09ee68
   WHAT IT DOES: Sets d[k][i] to the dot product of a's column i with b's row k. */
Mat34 &f_09ee68(Mat34 &d, const Mat33 &a, const Mat34 &b)
{
    for (int i = 0; i < 3; i++) {
        d.m[0][i] = a.m[0][i] * b.m[0][0] + a.m[1][i] * b.m[0][1] + a.m[2][i] * b.m[0][2];
        d.m[1][i] = a.m[0][i] * b.m[1][0] + a.m[1][i] * b.m[1][1] + a.m[2][i] * b.m[1][2];
        d.m[2][i] = a.m[0][i] * b.m[2][0] + a.m[1][i] * b.m[2][1] + a.m[2][i] * b.m[2][2];
    }
    return d;
}

/* @draft 0x09efd8 us f_09efd8
   WHAT IT DOES: Sets d[k][i] to the dot product of a's row i with b's row k. */
Mat34 &f_09efd8(Mat34 &d, const Mat33 &a, const Mat34 &b)
{
    for (int i = 0; i < 3; i++) {
        d.m[0][i] = a.m[i][0] * b.m[0][0] + a.m[i][1] * b.m[0][1] + a.m[i][2] * b.m[0][2];
        d.m[1][i] = a.m[i][0] * b.m[1][0] + a.m[i][1] * b.m[1][1] + a.m[i][2] * b.m[1][2];
        d.m[2][i] = a.m[i][0] * b.m[2][0] + a.m[i][1] * b.m[2][1] + a.m[i][2] * b.m[2][2];
    }
    return d;
}

/* @draft 0x09f25c us f_09f25c
   WHAT IT DOES: Sets d[k][i] to the dot product of a's row i with b's row k, for b's four
   rows. */
Mat43 &f_09f25c(Mat43 &d, const Mat33 &a, const Mat43 &b)
{
    for (int i = 0; i < 3; i++) {
        d.m[0][i] = a.m[i][0] * b.m[0][0] + a.m[i][1] * b.m[0][1] + a.m[i][2] * b.m[0][2];
        d.m[1][i] = a.m[i][0] * b.m[1][0] + a.m[i][1] * b.m[1][1] + a.m[i][2] * b.m[1][2];
        d.m[2][i] = a.m[i][0] * b.m[2][0] + a.m[i][1] * b.m[2][1] + a.m[i][2] * b.m[2][2];
        d.m[3][i] = a.m[i][0] * b.m[3][0] + a.m[i][1] * b.m[3][1] + a.m[i][2] * b.m[3][2];
    }
    return d;
}

/* @draft 0x09f354 us f_09f354
   WHAT IT DOES: Sets d[k][i] to the dot product of a's column i with b's row k, for b's four
   rows (the first three columns). */
Mat44 &f_09f354(Mat44 &d, const Mat33 &a, const Mat44 &b)
{
    for (int i = 0; i < 3; i++) {
        d.m[0][i] = a.m[0][i] * b.m[0][0] + a.m[1][i] * b.m[0][1] + a.m[2][i] * b.m[0][2];
        d.m[1][i] = a.m[0][i] * b.m[1][0] + a.m[1][i] * b.m[1][1] + a.m[2][i] * b.m[1][2];
        d.m[2][i] = a.m[0][i] * b.m[2][0] + a.m[1][i] * b.m[2][1] + a.m[2][i] * b.m[2][2];
        d.m[3][i] = a.m[0][i] * b.m[3][0] + a.m[1][i] * b.m[3][1] + a.m[2][i] * b.m[3][2];
    }
    return d;
}

/* @draft 0x09f43c us f_09f43c
   WHAT IT DOES: Sets d[k][i] to the dot product of a's row i with b's row k, for b's four
   rows (the first three columns). */
Mat44 &f_09f43c(Mat44 &d, const Mat33 &a, const Mat44 &b)
{
    for (int i = 0; i < 3; i++) {
        d.m[0][i] = a.m[i][0] * b.m[0][0] + a.m[i][1] * b.m[0][1] + a.m[i][2] * b.m[0][2];
        d.m[1][i] = a.m[i][0] * b.m[1][0] + a.m[i][1] * b.m[1][1] + a.m[i][2] * b.m[1][2];
        d.m[2][i] = a.m[i][0] * b.m[2][0] + a.m[i][1] * b.m[2][1] + a.m[i][2] * b.m[2][2];
        d.m[3][i] = a.m[i][0] * b.m[3][0] + a.m[i][1] * b.m[3][1] + a.m[i][2] * b.m[3][2];
    }
    return d;
}
