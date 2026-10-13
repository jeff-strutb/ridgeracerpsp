/* Angle and period wrapping helpers (retail 0x0af380 to 0x0af678). The periods are
   globals set at start up elsewhere: a full turn and a half turn in radians, and integer
   periods with their halves. */

extern float D_2456b0; /* full turn (2 pi) */
extern float D_2456b4; /* half turn (pi) */
extern int D_2456b8;   /* integer period */
extern int D_2456bc;   /* half of the integer period */
extern int D_2456c0;   /* a second integer period */

/* @implements 0x0af380 us f_0af380
   WHAT IT DOES: Returns *a - *b wrapped into the half-open range around zero by adding or
   subtracting full turns until it lies within plus or minus a half turn. */
float f_0af380(const float *a, const float *b)
{
    float d = *a - *b;

    if (d < -D_2456b4) {
        do
            d += D_2456b0;
        while (d < -D_2456b4);
    } else if (D_2456b4 < d) {
        do
            d -= D_2456b0;
        while (D_2456b4 < d);
    }
    return d;
}

/* @implements 0x0af3fc us f_0af3fc
   WHAT IT DOES: The same wrap of *a - *b, with *b read first. */
float f_0af3fc(const float *a, const float *b)
{
    float t = *b;
    float d = *a - t;

    if (d < -D_2456b4) {
        do
            d += D_2456b0;
        while (d < -D_2456b4);
    } else if (D_2456b4 < d) {
        do
            d -= D_2456b0;
        while (D_2456b4 < d);
    }
    return d;
}

/* @implements 0x0af478 us f_0af478
   WHAT IT DOES: Wraps *a into [0, full turn). */
float f_0af478(const float *a)
{
    float d = *a;

    if (d < 0.0f) {
        do
            d += D_2456b0;
        while (d < 0.0f);
    } else if (D_2456b0 <= d) {
        do
            d -= D_2456b0;
        while (D_2456b0 <= d);
    }
    return d;
}

/* @implements 0x0af4e0 us f_0af4e0
   WHAT IT DOES: Integer form of the difference wrap: *a - *b brought within plus or minus
   half the integer period. */
int f_0af4e0(const int *a, const int *b)
{
    int d = *a - *b;

    if (d < -D_2456bc) {
        do
            d += D_2456b8;
        while (d < -D_2456bc);
    } else if (D_2456bc < d) {
        do
            d -= D_2456b8;
        while (D_2456bc < d);
    }
    return d;
}

/* @implements 0x0af550 us f_0af550
   WHAT IT DOES: Wraps *a into [0, integer period). */
int f_0af550(const int *a)
{
    int v = *a;

    if (v < 0) {
        do
            v += D_2456b8;
        while (v < 0);
    } else if (v >= D_2456b8) {
        do
            v -= D_2456b8;
        while (v >= D_2456b8);
    }
    return v;
}

/* @implements 0x0af59c us f_0af59c
   WHAT IT DOES: Wraps *a into [0, second integer period). */
int f_0af59c(const int *a)
{
    int v = *a;

    if (v < 0) {
        do
            v += D_2456c0;
        while (v < 0);
    } else if (v >= D_2456c0) {
        do
            v -= D_2456c0;
        while (v >= D_2456c0);
    }
    return v;
}

/* A step table: n ascending keys and the value that applies from each key on. */
struct StepTable {
    char pad[48];
    int n;
    int *vals;
    int *keys;
};

/* @implements 0x0af5e8 us f_0af5e8
   WHAT IT DOES: Looks a 16-bit key up in a step table: -1 for the 0xffff "none" key, the
   only value of a one-entry table, else the value of the last step whose key is not above
   the given key (the final value when the key is past every step). */
int f_0af5e8(struct StepTable *t, const unsigned short *key)
{
    int i;

    if (*key == 0xffff)
        return -1;
    if (t->n == 1)
        return t->vals[0];
    for (i = 1; i < t->n; i++)
        if (*key < t->keys[i])
            return t->vals[i - 1];
    return t->vals[t->n - 1];
}
