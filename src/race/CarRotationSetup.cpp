/* Car rotation setup object file (retail 0x0bf23c to 0x0bf3b4, the gap TU 230): builds a
   rotation matrix from a 16 byte vector block, applies it to two fixed vectors and writes
   the two resulting vectors out. */

#define FR(p, o) (*(float *)((char *)(p) + (o)))
#define WR(p, o) (*(int *)((char *)(p) + (o)))

static inline int fbits(float f)
{
    union { float f; int i; } u;
    u.f = f;
    return u.i;
}

extern "C" {
void f_09ff44(void *p);
void f_099b98(void *p);
void f_0a082c(void *p, int bits, int a2, int a3);
void f_09fe84(void *out, void *m, void *v);
float f_09a9dc(float a, float b);
void f_0a6bf4(void *out, void *m, void *v);
void f_0bf3b4(const void *pa, const void *pb, void *out);
}

extern "C" float sqrtf(float);

extern float D_1acc94;
extern float D_1acc98;

/* @draft 0x0bf3b4 us f_0bf3b4
   WHAT IT DOES: normalises the first three components of two vectors, takes the angle of
   the first one against the second's and writes a 4 word result (the two angles and a
   third value, negated, and a zero word).
   Remaining difference: locals cut to retail's 144 bytes (t1/t0 then land at 144/148
    as in retail). Retail saves only f20/f21: it rereads the vector components from the
    stack copies at each use (lwc1 16/20/24(sp) after the out clears), where this source
    holds ax..bz in f22-f28 across the sqrt calls (frame 224 vs 192). */
extern "C" void f_0bf3b4(const void *pa, const void *pb, void *out)
{
    char sp[144];
    char *m = sp + 32;
    WR(sp, 0) = WR(pa, 0);
    WR(sp, 4) = WR(pa, 4);
    WR(sp, 8) = WR(pa, 8);
    WR(sp, 12) = WR(pa, 12);
    WR(sp, 16) = WR(pb, 0);
    WR(sp, 20) = WR(pb, 4);
    WR(sp, 24) = WR(pb, 8);
    WR(sp, 28) = WR(pb, 12);
    float ax = FR(sp, 0), ay = FR(sp, 4), az = FR(sp, 8);
    float bx = FR(sp, 16), by = FR(sp, 20), bz = FR(sp, 24);
    float la = sqrtf(ax * ax + ay * ay + az * az);
    WR(out, 0) = 0;
    WR(out, 4) = 0;
    WR(out, 8) = 0;
    float inv = 1.0f / la;
    WR(out, 12) = 0;
    float lb = sqrtf(bx * bx + by * by + bz * bz);
    FR(sp, 104) = inv * az;
    FR(sp, 96) = inv * ax;
    FR(sp, 100) = inv * ay;
    float ib = 1.0f / lb;
    FR(sp, 124) = 1.0f;
    float s = sqrtf(1.0f - ay * ay);
    FR(sp, 112) = ib * bx;
    FR(sp, 120) = ib * bz;
    FR(sp, 116) = ib * by;
    WR(out, 0) = fbits(f_09a9dc(FR(sp, 100), s));
    WR(out, 4) = fbits(f_09a9dc(-FR(sp, 96), FR(sp, 104)));
    f_09ff44(m);
    float t1 = FR(out, 4);
    f_099b98(&t1);
    f_0a082c(m, fbits(t1), 2, 0);
    float t0 = FR(out, 0);
    f_099b98(&t0);
    f_0a082c(m, fbits(t0), 1, 2);
    f_09fe84(sp + 128, m, sp + 112);
    WR(sp, 84) = WR(sp, 132);
    WR(sp, 80) = WR(sp, 128);
    WR(sp, 88) = WR(sp, 136);
    WR(sp, 92) = WR(sp, 140);
    WR(out, 8) = fbits(-f_09a9dc(FR(sp, 80), -FR(sp, 84)));
}

static inline void copy16(char *d, const char *s)
{
    WR(d, 0) = WR(s, 0);
    WR(d, 4) = WR(s, 4);
    WR(d, 8) = WR(s, 8);
    WR(d, 12) = WR(s, 12);
}

/* @draft 0x0bf604 us f_0bf604
   WHAT IT DOES: takes an input vector and a second vector, applies two matrix transforms
   chosen by the magnitudes of the second vector's components (through f_0a6bf4 and
   f_0bf3b4), rebuilds a matrix from the negated input and writes the resulting four words.
   Remaining difference: locals cut to retail's 240 bytes. Retail saves only
   f20/f21 (frame 304); this source keeps the |q| components in f22-f24 as well (320). */
extern "C" void f_0bf604(const void *pa, void *out, const void *pq)
{
    char sp[240];
    char *s0 = sp + 32;
    char *s3 = sp + 80;
    char *s5 = sp + 128;
    char *s6 = sp + 144;
    char *s1 = sp + 192;
    char *p = sp + 160;
    WR(sp, 0) = WR(pa, 0);
    WR(sp, 4) = WR(pa, 4);
    WR(sp, 8) = WR(pa, 8);
    WR(sp, 12) = WR(pa, 12);
    WR(sp, 16) = WR(pq, 0);
    WR(sp, 20) = WR(pq, 4);
    WR(sp, 24) = WR(pq, 8);
    WR(sp, 28) = WR(pq, 12);
    float q0 = FR(sp, 16);
    if (q0 < 0.0f) {
        q0 = -q0;
    }
    float q1 = FR(sp, 20);
    if (q1 < 0.0f) {
        q1 = -q1;
    }
    float q2 = FR(sp, 24);
    if (q2 < 0.0f) {
        q2 = -q2;
    }
    FR(sp, 176) = q0;
    FR(sp, 180) = q1;
    FR(sp, 184) = q2;
    FR(sp, 188) = 1.0f;
    f_09ff44(s3);
    FR(sp, 208) = -FR(sp, 8);
    f_099b98(sp + 208);
    f_0a082c(s3, WR(sp, 208), 0, 1);
    FR(sp, 212) = -FR(sp, 0);
    f_099b98(sp + 212);
    f_0a082c(s3, WR(sp, 212), 1, 2);
    FR(sp, 216) = -FR(sp, 4);
    f_099b98(sp + 216);
    f_0a082c(s3, WR(sp, 216), 2, 0);
    FR(sp, 152) = 0.0f;
    FR(sp, 148) = -1.0f;
    FR(sp, 156) = 1.0f;
    FR(sp, 128) = 0.0f;
    FR(sp, 132) = 0.0f;
    FR(sp, 136) = 1.0f;
    FR(sp, 140) = 1.0f;
    FR(sp, 144) = 0.0f;
    if (0.001f <= q0) {
        f_09ff44(s0);
        FR(sp, 220) = -FR(sp, 16);
        f_099b98(sp + 220);
        f_0a082c(s0, WR(sp, 220), 1, 2);
        f_0a6bf4(s1, s0, s5);
        copy16(s5, s1);
        f_0a6bf4(s1, s0, s6);
        copy16(s6, s1);
        f_0a6bf4(s1, s3, s5);
        copy16(s5, s1);
        f_0a6bf4(s1, s3, s6);
        copy16(s6, s1);
        f_0bf3b4(s5, s6, p);
    } else {
        copy16(p, sp);
    }
    f_09ff44(s3);
    FR(sp, 224) = -FR(sp, 168);
    f_099b98(sp + 224);
    f_0a082c(s3, WR(sp, 224), 0, 1);
    FR(sp, 228) = -FR(sp, 160);
    f_099b98(sp + 228);
    f_0a082c(s3, WR(sp, 228), 1, 2);
    FR(sp, 232) = -FR(sp, 164);
    f_099b98(sp + 232);
    f_0a082c(s3, WR(sp, 232), 2, 0);
    FR(sp, 156) = 1.0f;
    FR(sp, 148) = -1.0f;
    WR(sp, 128) = 0;
    WR(sp, 132) = 0;
    FR(sp, 136) = 1.0f;
    FR(sp, 140) = 1.0f;
    WR(sp, 144) = 0;
    WR(sp, 152) = 0;
    if (0.001f <= q1) {
        f_09ff44(s0);
        FR(sp, 236) = -FR(sp, 20);
        f_099b98(sp + 236);
        f_0a082c(s0, WR(sp, 236), 2, 0);
        f_0a6bf4(s1, s0, s5);
        copy16(s5, s1);
        f_0a6bf4(s1, s3, s5);
        copy16(s5, s1);
        f_0a6bf4(s1, s3, s6);
        copy16(s6, s1);
        f_0bf3b4(s5, s6, p);
    }
    if (0.001f <= q2) {
        FR(sp, 168) = FR(sp, 168) + FR(sp, 24);
    }
    WR(out, 12) = WR(sp, 172);
    WR(out, 0) = WR(sp, 160);
    WR(out, 4) = WR(sp, 164);
    WR(out, 8) = WR(sp, 168);
}

/* @draft 0x0bf23c us f_0bf23c
   WHAT IT DOES: copies a 16 byte vector, builds a rotation matrix from its three components
   (negated, each through f_099b98), applies it to two fixed vectors and writes both results
   to the two output vectors.
   Remaining difference: not yet compared; the transformed results are written from the
   listing and have not been scored. */
extern "C" void f_0bf23c(void *o1, void *o2, const void *in)
{
    char sp[160];
    char *m = sp + 16;
    char *s3 = sp + 96;
    WR(sp, 12) = WR(in, 12);
    WR(sp, 4) = WR(in, 4);
    WR(sp, 8) = WR(in, 8);
    WR(sp, 0) = WR(in, 0);
    f_09ff44(m);
    float t = -FR(sp, 8);
    FR(sp, 112) = t;
    f_099b98(sp + 112);
    f_0a082c(m, WR(sp, 112), 0, 1);
    t = -FR(sp, 0);
    FR(sp, 116) = t;
    f_099b98(sp + 116);
    f_0a082c(m, WR(sp, 116), 1, 2);
    t = -FR(sp, 4);
    FR(sp, 120) = t;
    f_099b98(sp + 120);
    f_0a082c(m, WR(sp, 120), 2, 0);
    float f2 = D_1acc94;
    float f0 = D_1acc98;
    FR(sp, 64) = 0.0f;
    FR(sp, 68) = 0.0f;
    FR(sp, 72) = f2;
    FR(sp, 76) = f2;
    FR(sp, 80) = 0.0f;
    FR(sp, 84) = f0;
    FR(sp, 88) = 0.0f;
    FR(sp, 92) = f2;
    f_09fe84(s3, m, sp + 64);
    WR(o1, 0) = WR(s3, 0);
    WR(o1, 12) = WR(s3, 12);
    WR(o1, 4) = WR(s3, 4);
    WR(o1, 8) = WR(s3, 8);
    f_09fe84(s3, m, sp + 80);
    WR(o2, 0) = WR(s3, 0);
    WR(o2, 12) = WR(s3, 12);
    WR(o2, 4) = WR(s3, 4);
    WR(o2, 8) = WR(s3, 8);
}
