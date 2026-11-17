/* An engine sound curve (retail 0x0ca0bc to 0x0ca584): ten control points (two rows of
   ten values, D_24ec70) joined by a uniform cubic B-spline, each segment sampled at 8 steps
   from a 32 entry basis table. The curve is evaluated at a step, and inverted: the step whose
   first value reaches an input is found by halving, and the second value interpolated
   there. */

extern float D_24ec70[2][10];   /* the control points: first and second values */

/* @draft 0x0ca0bc us f_0ca0bc
   DRAFT: only register numbering differs (the weight index j is in a1 and its counter in a0; retail has them the other way round).
   Cause (greg): allocno order puts n (pseudo 203) before j (199); n takes the first free reg a0,
   then j takes its preference a1 (hard-reg copy). Retail needs j=a0, n=a1.
   Tried: the counter as the parameter step itself (incoming a1 preference): 8 -> 20 words, reverted.
   WHAT IT DOES: Evaluates the curve at a step (8 per segment): sums the basis weights of
   the four control points around it (indices clamped to 0..9) into both outputs. */
void f_0ca0bc(void *unused, int step, float *a, float *b)
{
    float w[32] = {
        0.000325521f, 0.002604167f, 0.008789063f, 0.020833332f, 0.040690105f, 0.0703125f, 0.11165365f, 0.16666667f,
        0.23600261f, 0.31510416f, 0.39811197f, 0.47916666f, 0.5524089f, 0.6119792f, 0.65201825f, 0.6666667f,
        0.65201825f, 0.6119792f, 0.5524089f, 0.47916666f, 0.39811197f, 0.31510416f, 0.23600261f, 0.16666667f,
        0.11165365f, 0.0703125f, 0.040690105f, 0.020833332f, 0.008789063f, 0.002604167f, 0.000325521f, 0.0f,
    };
    int i = step / 8 - 1;
    int j = step - i * 8 + 15;
    int n;

    *a = 0;
    *b = 0;
    if (j >= 0) {
        n = j;
        do {
            int k = i++;

            n -= 8;
            if (k < 0)
                k = 0;
            else if (k >= 10)
                k = 9;
            *a += D_24ec70[0][k] * w[j];
            *b += D_24ec70[1][k] * w[j];
            j = n;
        } while (n >= 0);
    }
}

/* @implements 0x0ca1a8 us f_0ca1a8
   WHAT IT DOES: Inverts the curve. Loads the ten control points of both rows from two short
   arrays, then finds the segment (1..9) and the sub-step (1..8) whose first value reaches x
   by halving, evaluating the curve at each probe, and linearly interpolates the second value
   between the two surrounding samples. Inputs at or below the first sample or at or above
   the last return the end values. One int serves as loop index, segment, probe and sample
   index (retail keeps all of them in a1). */
#define PROBE(i) f_0ca0bc(ctx, (i), &r1[(i)], &r2[(i)])

float f_0ca1a8(void *ctx, int xi, short *a, short *b)
{
    float r1[76];
    float r2[76];
    float x = xi;
    int i, base, n;

    for (i = 0; i < 10; i++) {
        D_24ec70[0][i] = a[i];
        D_24ec70[1][i] = b[i];
    }
    f_0ca0bc(ctx, -8, &r1[0], &r2[0]);
    if (x <= r1[0])
        return r2[0];
    f_0ca0bc(ctx, 80, &r1[72], &r2[72]);
    if (r1[72] <= x)
        return r2[72];
    PROBE(32);
    if (r1[32] < x) {
        PROBE(48);
        if (r1[48] < x) {
            PROBE(56);
            if (r1[56] < x) {
                PROBE(64);
                i = r1[64] < x ? 9 : 8;
            } else
                i = 7;
        } else {
            PROBE(40);
            i = r1[40] < x ? 6 : 5;
        }
    } else {
        PROBE(16);
        if (r1[16] < x) {
            PROBE(24);
            i = r1[24] < x ? 4 : 3;
        } else {
            PROBE(8);
            i = r1[8] < x ? 2 : 1;
        }
    }
    i--;
    base = i * 8;
    i = base + 4;
    f_0ca0bc(ctx, i, &r1[i], &r2[i]);
    if (r1[i] < x) {
        i = base + 6;
        f_0ca0bc(ctx, i, &r1[i], &r2[i]);
        if (r1[i] < x) {
            i = base + 7;
            f_0ca0bc(ctx, i, &r1[i], &r2[i]);
            n = r1[i] < x ? 8 : 7;
        } else {
            i = base + 5;
            f_0ca0bc(ctx, i, &r1[i], &r2[i]);
            n = r1[i] < x ? 6 : 5;
        }
    } else {
        i = base + 2;
        f_0ca0bc(ctx, i, &r1[i], &r2[i]);
        if (r1[i] < x) {
            i = base + 3;
            f_0ca0bc(ctx, i, &r1[i], &r2[i]);
            n = r1[i] < x ? 4 : 3;
        } else {
            i = base + 1;
            f_0ca0bc(ctx, i, &r1[i], &r2[i]);
            n = r1[i] < x ? 2 : 1;
        }
    }
    n--;
    i = base + n;
    return (x - r1[i]) * (r2[i + 1] - r2[i]) / (r1[i + 1] - r1[i]) + r2[i];
}
