/* Car physics object file (retail 0x0bd400 to 0x0be8b0, the object TU 226 and its gap TU 227):
   the per frame car update over the four wheel records (368 bytes each, from +8064) and the
   smoothing that follows it. The four empty stubs at 0x0be854 to 0x0be870 belong here too. */

#define FR(p, o) (*(float *)((char *)(p) + (o)))
#define WR(p, o) (*(int *)((char *)(p) + (o)))

static inline int fbits(float f)
{
    union { float f; int i; } u;
    u.f = f;
    return u.i;
}

extern "C" {
void f_0a6d4c(void *out, void *a, void *b);
void f_0a6c18(void *out, void *m, void *v);
void f_0a6580(void *p);
void f_09ff44(void *p);
void f_0a082c(void *p, int bits, int a2, int a3);
void f_099b98(void *p);
float f_09a9dc(float a, float b);
void f_0fa7f0(float a);
void f_0a5f74(void *p);
void f_0a6bf4(void *out, void *a, void *b);
void f_0bd6b0(char *self, int i);
void f_0bd400(char *self, int i);
void f_0bdcb0(char *self);
void f_09b394(int a, void *x, void *y);
void f_0be470(char *self, const void *in, void *out, void *v3, float k);
float f_0a65c4(void *v);
void f_0a5ec8(void *d, void *a, float k);
void f_0a5ea4(void *d, void *a, float k);
void f_0a2db0(void *m, void *v);
}

extern "C" float sqrtf(float);

extern char *D_2456d0;
extern float D_1acc4c;
extern float D_1acc50;
extern float D_1acc54;
extern float D_1acc58;
extern float D_1acc5c;
extern float D_1acc74;
extern float D_1acc60;
extern float D_1acc64;
extern float D_1acc68;
extern float D_1acc6c;
extern float D_1acc70;
extern int D_1ac834[];

/* @draft 0x0bd400 us f_0bd400
   WHAT IT DOES: refreshes one wheel record from the car's vector block and the global body
   block, and copies the wheel's two vectors into the body block.
   Remaining difference: 165 of 172 words differ, size 656 vs 688; the scheduling of the
   loads and stores differs and the sqrt call path is not matched. */
extern "C" void f_0bd400(char *self, int i)
{
    int vo[4];
    int vp[4];
    char *s5 = self + 8064 + i * 368;
    char *s3 = s5 + 272;
    f_0a6d4c(vo, self + 6560, s3);
    char *s4 = D_2456d0;
    char *a3 = s4 + 576;
    WR(a3, 128) = vo[0];
    WR(a3, 132) = vo[1];
    WR(a3, 136) = vo[2];
    WR(a3, 140) = vo[3];
    char *t0 = self + D_1ac834[i] * 4;
    int t2 = WR(self + i * 4, 2624);
    float f0 = FR(s5, 136);
    float f1 = D_1acc4c;
    float f2 = FR(s4, 708);
    f2 = f2 + f0;
    FR(s4, 708) = f2;
    f0 = FR(t0, 2464);
    f0 = -f0;
    f0 = f0 * f1;
    f0 = f0 - f2;
    FR(s3, 64) = f0;
    WR(a3, 172) = t2;
    char *s0 = self + i * 16;
    float g3 = FR(s0, 2640);
    float g2 = -FR(s0, 2648);
    float g1 = -FR(s0, 2644);
    WR(a3, 48) = fbits(g3);
    WR(a3, 52) = fbits(g1);
    WR(a3, 56) = fbits(g2);
    WR(a3, 60) = fbits(D_1acc50);
    WR(s5, 144) = fbits(g3);
    WR(s5, 132) = t2;
    char *t1 = s5 + 144;
    WR(t1, 4) = WR(a3, 52);
    WR(t1, 8) = WR(a3, 56);
    WR(t1, 12) = WR(a3, 60);
    f_0a6c18(vp, self + 6560, s4 + 624);
    WR(s4, 112) = vp[0];
    WR(s4, 116) = vp[1];
    WR(s4, 120) = vp[2];
    WR(s4, 124) = vp[3];
    float len = sqrtf(FR(s4, 116) * FR(s4, 116) + FR(s4, 120) * FR(s4, 120));
    FR(s4, 560) = len;
    float a = f_09a9dc(FR(s4, 120), -FR(s4, 116));
    char *q = s4 + 304;
    float n = -a;
    f_099b98(&n);
    WR(s5, 160) = fbits(n);
    float c = f_09a9dc(FR(s4, 112), FR(s4, 560));
    f_099b98(&c);
    WR(s5, 168) = fbits(c);
    f_09ff44(q);
    float e = -FR(s5, 160);
    f_099b98(&e);
    f_0a082c(q, fbits(e), 1, 2);
    float h = -FR(s5, 168);
    f_099b98(&h);
    f_0a082c(q, fbits(h), 0, 1);
    char *d = s5 + 224;
    char *end = s4 + 352;
    do {
        WR(d, 0) = WR(q, 0);
        WR(d, 4) = WR(q, 4);
        WR(d, 8) = WR(q, 8);
        WR(d, 12) = WR(q, 12);
        q += 16;
        d += 16;
    } while (q != end);
}

/* @draft 0x0bd6b0 us f_0bd6b0
   WHAT IT DOES: updates one wheel record's slip and travel values from the wheel's
   parameters, clamps them to the range from the record, and sets the record's flags.
   Remaining difference: 108 of 116 words differ, size 396 vs 464; the tail after the second
   clamp is missing part of the retail code. */
extern "C" void f_0bd6b0(char *self, int i)
{
    char *r = self + 8064 + i * 368;
    char *a2 = r + 272;
    char *t0 = self + 5792;
    float f1 = FR(a2, 32);
    float f0 = FR(a2, 80) * f1;
    float f3 = FR(a2, 36);
    float f2 = FR(a2, 60);
    FR(a2, 40) = f3;
    f0 = -f0;
    float f4 = FR(a2, 16);
    FR(a2, 56) = f0;
    f1 = FR(self, 9944);
    f0 = f0 * f1;
    f2 = f2 + f0;
    FR(a2, 60) = f2;
    f0 = FR(self, 9944);
    f2 = f2 * f0;
    f3 = f3 + f2;
    FR(a2, 36) = f3;
    if (!(f3 < f4)) {
        f3 = f4;
    }
    FR(a2, 36) = f3;
    if (!(0.0f < f3)) {
        f3 = 0.0f;
    }
    float f5 = FR(a2, 64);
    FR(a2, 36) = f3;
    if (f5 < f3) {
        FR(a2, 36) = f5;
        WR(r, 128) = 1;
        WR(t0, 1020) = WR(t0, 1020) + 1;
    } else {
        WR(r, 128) = 0;
    }
    WR(a2, 84) = 0;
    f0 = FR(a2, 36);
    WR(a2, 88) = 0;
    if (!(f0 < f4)) {
        f0 = f4;
    }
    FR(a2, 36) = f0;
    if (f0 < 0.0f) {
        FR(a2, 88) = f0;
        FR(a2, 36) = 0.0f;
        int rr = WR(r, 128);
        FR(a2, 84) = f0;
        if (rr != 0) {
            WR(t0, 1016) = WR(t0, 1016) + 1;
        }
    }
    float f6 = FR(a2, 40);
    f4 = FR(a2, 36);
    f0 = FR(a2, 72);
    f2 = 0.0f;
    f1 = f6 - f4;
    f1 = f5 + f1;
    FR(a2, 68) = f1;
    if (0.0f <= f0) {
        if (f4 < f6) {
            f1 = f6;
        } else {
            f1 = f4;
        }
        FR(a2, 40) = f1;
        f6 = f1;
    }
    f1 = f4 - f6;
    f0 = D_1acc54;
    f2 = FR(a2, 48);
    f1 = f1 / f0;
    f3 = FR(a2, 0);
    f2 = f1 - f2;
    FR(a2, 48) = f1;
    FR(a2, 44) = f2;
    WR(r, 0) = fbits(f3);
    f1 = FR(a2, 36);
    f0 = FR(a2, 4);
    f0 = f0 + f1;
    WR(r, 4) = fbits(f0);
    f1 = FR(a2, 8);
    WR(r, 8) = fbits(f1);
}

/* @draft 0x0bd880 us f_0bd880
   WHAT IT DOES: runs the four wheel updates, the per wheel smoothing and the body
   bookkeeping, then the second pass that copies the wheel vectors into the body.
   Remaining difference: 200 of 215 words differ, size 824 vs 860; the call order near the
   end is wrong (retail calls f_0a5f74 where the source calls f_0a6580, and f_0a6580 where
   it calls f_0a082c). Also the tail after f_0a6bf4 is written from the listing, not checked. */
extern "C" void f_0bd880(char *self)
{
    char *s5 = self + 8064;
    char *s4 = self + 5792;
    char *s6 = D_2456d0;
    char *s3 = s6 + 576;
    WR(s4, 1016) = 0;
    WR(s4, 1020) = 0;
    for (int i = 0; i < 4; i++) {
        f_0bd400(self, i);
    }
    char *s0 = s5;
    for (int i = 0; i < 4; i++) {
        float f1 = FR(s4, 256);
        float f3 = FR(s0, 280);
        float f0 = FR(s4, 228);
        float f2 = FR(s0, 272);
        float f4 = FR(s4, 264);
        f1 = f1 * f3;
        f0 = f0 + f1;
        f2 = f2 * f4;
        f0 = f0 - f2;
        FR(s6, 496) = f0;
        f1 = FR(self, 9944);
        f0 = f0 * f1;
        FR(s0, 344) = f0;
        f_0bd6b0(self, i);
        s0 += 368;
    }
    f_0bdcb0(self);
    char *a0 = s3;
    char *a1 = s5;
    for (int i = 3; i >= 0; i--) {
        WR(a0, 176) = WR(a1, 272);
        WR(a0, 180) = WR(a1, 276);
        WR(a0, 184) = WR(a1, 280);
        WR(a0, 188) = WR(a1, 284);
        FR(a0, 180) = -FR(a1, 336);
        a0 += 16;
        a1 += 368;
    }
    float f2 = FR(s3, 176);
    float f0 = FR(s3, 224);
    char *v0 = s3 + 224;
    float f4 = FR(v0, 8);
    f0 = f0 - f2;
    float f1 = FR(v0, 4);
    f2 = FR(s3, 180);
    float f3 = FR(s3, 184);
    float sp[4];
    sp[0] = f0;
    f1 = f1 - f2;
    f4 = f4 - f3;
    float f5 = D_1acc58;
    sp[1] = f1;
    sp[3] = f5;
    sp[2] = f4;
    WR(s3, 240) = fbits(sp[0]);
    WR(s3, 244) = fbits(sp[1]);
    f2 = FR(s3, 208);
    f0 = FR(s3, 192);
    WR(s3, 248) = fbits(sp[2]);
    f2 = f2 - f0;
    f4 = FR(s3, 196);
    f3 = FR(s3, 200);
    WR(s3, 252) = fbits(sp[3]);
    f1 = FR(s3, 216);
    f0 = FR(s3, 212);
    sp[0] = f2;
    f1 = f1 - f3;
    f0 = f0 - f4;
    sp[3] = f5;
    sp[2] = f1;
    sp[1] = f0;
    WR(s3, 256) = fbits(sp[0]);
    WR(s3, 260) = fbits(sp[1]);
    WR(s3, 264) = fbits(sp[2]);
    WR(s3, 268) = fbits(sp[3]);
    f_0a5f74(sp);
    char *s2 = s3 + 48;
    WR(s3, 48) = fbits(sp[0]);
    WR(s3, 52) = fbits(sp[1]);
    WR(s3, 56) = fbits(sp[2]);
    WR(s3, 60) = fbits(sp[3]);
    f_0a6580(s2);
    f_09ff44(s0 = s6 + 304);
    f_0a082c(s0, WR(s4, 24), 0, 1);
    f_0a082c(s0, WR(s4, 16), 1, 2);
    f_0a6bf4(sp, s0, s2);
    WR(s4, 936) = WR(sp, 8);
    WR(s4, 940) = WR(sp, 12);
    WR(s4, 932) = WR(sp, 4);
    WR(s4, 928) = WR(sp, 0);
    f_0a6580(s4 + 928);
    float z0 = 0.0f;
    WR(sp, 0) = fbits(z0);
    f_099b98(&z0);
    float z1 = 0.0f;
    f_099b98(&z1);
    float z2 = 0.0f;
    f_099b98(&z2);
    WR(s4, 944) = fbits(z0);
    WR(s4 + 944, 12) = 0;
    WR(s4 + 944, 4) = fbits(z1);
    WR(s4 + 944, 8) = fbits(z2);
    float a = f_09a9dc(FR(s4, 932), -FR(s4, 936));
    a = -a;
    float b = a;
    f_099b98(&b);
    float q = sqrtf(FR(s4, 932) * FR(s4, 932) + FR(s4, 936) * FR(s4, 936));
    FR(s4, 500) = q;
    float c = f_09a9dc(FR(s4, 928), q);
    c = -c;
    f_099b98(&c);
    WR(s4, 952) = fbits(c);
}

/* @implements 0x0be854 us f_0be854
   WHAT IT DOES: empty stub. */
extern "C" void f_0be854(void *p)
{
}

/* @implements 0x0be85c us f_0be85c
   WHAT IT DOES: empty stub. */
extern "C" void f_0be85c(void *p)
{
}

/* @implements 0x0be864 us f_0be864
   WHAT IT DOES: empty stub. */
extern "C" void f_0be864(void *p)
{
}

/* @implements 0x0be86c us f_0be86c
   WHAT IT DOES: empty stub. */
extern "C" void f_0be86c(void *p)
{
}

/* @draft 0x0bdbdc us f_0bdbdc
   WHAT IT DOES: for each of the four wheel records (from +8064, 368 bytes apart, lowest index
   first) it works out a slip value from the record's two travel values, passes the scaled
   slip to f_0fa7f0 with its sign taken from the scaled value, and stores the sum of the two
   results back into the record.
   Remaining difference: transcribed from the listing; the retail prologue also saves f22,
   which the listing never uses, and the call and store order are not yet matched. */
extern "C" void f_0bdbdc(char *car)
{
    char *s0 = car + 8064;
    int s1 = 3;
    do {
        float x = FR(s0, 320);
        float q = x / D_1acc5c;
        float d = FR(s0, 288) - FR(s0, 308);
        float e = -(FR(s0, 292) * d);
        FR(s0, 348) = e;
        if (0.0f < x) {
            f_0fa7f0(q);
        } else {
            f_0fa7f0(-q);
        }
        float t = FR(s0, 296) * x;
        s1--;
        FR(s0, 324) = t;
        int v = WR(s0, 128);
        FR(s0, 352) = e;
        float u = e + t;
        FR(s0, 348) = u;
        if (v != 0) {
            FR(s0, 116) = u;
        }
        s0 += 368;
    } while (s1 >= 0);
}

static inline void copy16p(char *d, const char *s)
{
    WR(d, 0) = WR(s, 0);
    WR(d, 4) = WR(s, 4);
    WR(d, 8) = WR(s, 8);
    WR(d, 12) = WR(s, 12);
}

/* @draft 0x0be470 us f_0be470
   WHAT IT DOES: transforms the input vector through the car's matrices (f_0a6bf4 and f_0a6c18
   against the blocks at +6416, +6368 and +576), takes the angle of one component against the
   float argument and writes a 16 byte vector to the output; the sign of the first component
   selects one of two transform chains.
   Remaining difference: not yet compared against retail. */
extern "C" void f_0be470(char *self, const void *in, void *out, void *v3, float k)
{
    char sp[256];
    char *s1 = sp + 96;
    char *s4 = sp + 144;
    char *s7 = sp + 64;
    char *s0 = sp + 160;
    char *s2 = self + 6368;
    WR(sp, 0) = WR(in, 0);
    WR(sp, 4) = WR(in, 4);
    WR(sp, 8) = WR(in, 8);
    WR(sp, 12) = WR(in, 12);
    f_09ff44(s1);
    FR(sp, 80) = 0.0f;
    FR(sp, 84) = k;
    FR(sp, 88) = 0.0f;
    FR(sp, 92) = D_1acc74;
    f_0a6bf4(s4, self + 6416, sp);
    copy16p(sp + 16, s4);
    f_0a6c18(s4, s2, v3);
    WR(sp, 32) = WR(sp, 16);
    WR(sp, 36) = WR(sp, 20);
    WR(sp, 40) = WR(sp, 24);
    FR(sp, 44) = D_1acc74;
    FR(sp, 36) = -FR(sp, 36);
    FR(sp, 40) = -FR(sp, 40);
    copy16p(sp + 48, s4);
    float r1 = f_09a9dc(FR(sp, 32), FR(sp, 40));
    float n1 = -r1;
    FR(sp, 176) = n1;
    f_099b98(sp + 176);
    f_09b394(WR(sp, 176), sp + 40, sp + 32);
    FR(sp, 180) = n1;
    f_099b98(sp + 180);
    f_0a082c(s1, WR(sp, 180), 2, 0);
    FR(sp, 52) = -FR(sp, 52);
    FR(sp, 56) = -FR(sp, 56);
    FR(sp, 60) = D_1acc74;
    f_0a6bf4(s4, s1, sp + 48);
    copy16p(sp + 64, s4);
    if (0.0f < FR(sp, 64)) {
        FR(sp, 76) = 0.0f;
        FR(sp, 64) = 0.0f;
        FR(sp, 68) = 0.0f;
        FR(sp, 72) = 0.0f;
    } else {
        FR(sp, 64) = -FR(sp, 64);
        FR(sp, 72) = 0.0f;
        FR(sp, 68) = 0.0f;
        f_0a6c18(s4, s1, s7);
        WR(sp, 68) = WR(sp, 148);
        WR(sp, 64) = WR(sp, 144);
        WR(sp, 72) = WR(sp, 152);
        FR(sp, 76) = D_1acc74;
        FR(sp, 68) = -FR(sp, 68);
        FR(sp, 72) = -FR(sp, 72);
        f_0a6bf4(s4, s2, s7);
        copy16p(sp + 64, s4);
    }
    WR(v3, 12) = WR(sp, 76);
    WR(v3, 0) = WR(sp, 64);
    WR(v3, 4) = WR(sp, 68);
    WR(v3, 8) = WR(sp, 72);
    char *m576 = self + 576;
    float r2 = f_09a9dc(k, FR(sp, 40));
    f_0a6c18(s0, m576, out);
    WR(sp, 148) = WR(sp, 164);
    FR(sp, 156) = D_1acc74;
    WR(sp, 152) = WR(sp, 168);
    FR(sp, 148) = -FR(sp, 148);
    FR(sp, 152) = -FR(sp, 152);
    WR(sp, 144) = WR(sp, 160);
    f_0a6bf4(s0, s1, s4);
    WR(sp, 144) = WR(sp, 160);
    WR(sp, 156) = WR(sp, 172);
    FR(sp, 144) = FR(sp, 144) - r2;
    WR(sp, 148) = WR(sp, 164);
    WR(sp, 152) = WR(sp, 168);
    f_0a6c18(s0, s1, s4);
    WR(sp, 148) = WR(sp, 164);
    WR(sp, 144) = WR(sp, 160);
    WR(sp, 152) = WR(sp, 168);
    FR(sp, 148) = -FR(sp, 148);
    FR(sp, 156) = D_1acc74;
    FR(sp, 152) = -FR(sp, 152);
    f_0a6bf4(s0, m576, s4);
    WR(out, 12) = WR(sp, 172);
    WR(out, 0) = WR(sp, 160);
    WR(out, 4) = WR(sp, 164);
    WR(out, 8) = WR(sp, 168);
}

/* @draft 0x0bdcb0 us f_0bdcb0
   WHAT IT DOES: lists the wheel records whose first value is negative, sorts that list, runs the
   correction chain on the two worst wheels (f_0be470 and the matrix helpers) and writes the
   results back into the car block and the global block D_2456d0.
   Remaining difference: transcribed block by block from the listing (labels keep retail's
   branch structure); not yet compared against retail. */
extern "C" void f_0bdcb0(char *self)
{
    char sp[272];
    char *s2 = self + 5792;
    char *s3 = self + 8064;
    char *s4 = D_2456d0;
    char *s0;
    char *s7;
    char *s8;
    char *s3b;
    char *v0;
    char *v1;
    char *a2p;
    char *a2q;
    char *p;
    char *v;
    char *a0p;
    int s5 = 0;
    int s6 = 0;
    int a3 = 0;
    int a2 = 0;
    int n;
    int a1;
    int idx0;
    int idx1;
    int x;
    float f22 = D_1acc60;
    float f3 = FR(self, 8344) - FR(self, 9080);
    float f20;
    float f21;
    float f0;
    float f1;
    float f2;
    float f4;
    float f5;
    float f6;
    float f7;
    float f12;
    float g0;
    float g1;
    float r;

    p = sp;
    v = self + 8424;
    do {
        if (FR(v, 0) < 0.0f) {
            FR(p, 0) = FR(v, 0);
            WR(p, 16) = a2;
            a3++;
            p += 4;
        }
        v += 368;
        a2++;
    } while (a2 < 4);
    if (a3 == 0) {
        return;
    }
    if (a3 >= 2) {
        n = a3;
        do {
            a1 = 1;
            if (1 < n) {
                a0p = sp + 4;
                a1 = n - 1;
                do {
                    g0 = FR(a0p, -4);
                    g1 = FR(a0p, 0);
                    a1--;
                    if (g1 < g0) {
                        FR(a0p, 0) = g0;
                        FR(a0p, -4) = g1;
                        x = WR(a0p, 16);
                        WR(a0p, 16) = WR(a0p, 12);
                        WR(a0p, 12) = x;
                    }
                    a0p += 4;
                } while (a1 != 0);
            }
            n--;
        } while (n >= 2);
    }
    f21 = -f3;
    WR(sp, 32) = 0;
    WR(sp, 36) = 0;
    WR(sp, 40) = 0;
    WR(sp, 44) = 0;
    WR(sp, 80) = 0;
    WR(sp, 84) = 0;
    WR(sp, 88) = 0;
    WR(sp, 92) = 0;
    WR(sp, 48) = 0;
    WR(sp, 52) = 0;
    WR(sp, 56) = 0;
    WR(sp, 60) = 0;
    if (a3 >= 3) {
        FR(sp, 36) = FR(sp, 8);
        f2 = FR(sp, 4) - FR(sp, 8);
        f1 = FR(sp, 0) - FR(sp, 8);
        s5 = 1;
        s6 = 1;
        FR(sp, 4) = f2;
        FR(sp, 0) = f1;
    }
    if (a3 < 2) {
        goto L45c;
    }
    idx0 = WR(sp, 16);
    idx1 = WR(sp, 20);
    if (idx0 + idx1 == 3) {
        goto L424;
    }

    /* E path: wheel vectors through f_0a65c4 and the two helpers, then the first compare. */
    f20 = D_1acc64;
    s0 = sp + 112;
    v0 = s3 + idx0 * 368;
    WR(sp, 96) = WR(v0, 272);
    a2p = v0 + 272;
    v1 = s3 + idx1 * 368;
    WR(sp, 100) = WR(a2p, 4);
    WR(sp, 104) = WR(a2p, 8);
    FR(sp, 108) = f20;
    a2q = v1 + 272;
    f2 = -FR(sp, 100);
    FR(sp, 100) = f2;
    f3 = -FR(sp, 104);
    FR(sp, 104) = f3;
    f1 = FR(sp, 96);
    WR(sp, 112) = WR(v1, 272);
    WR(sp, 116) = WR(a2q, 4);
    f0 = FR(sp, 112) - f1;
    FR(sp, 112) = f0;
    WR(sp, 120) = WR(a2q, 8);
    f1 = -FR(sp, 116) - f2;
    FR(sp, 116) = f1;
    FR(sp, 124) = f20;
    f0 = -FR(sp, 120) - f3;
    FR(sp, 120) = f0;
    r = f_0a65c4(s0);
    f_0a5ec8(sp + 128, s0, r);
    WR(sp, 112) = WR(sp, 128);
    f12 = -FR(sp, 96);
    WR(sp, 116) = WR(sp, 132);
    f1 = FR(sp, 112);
    f12 = f12 * f1;
    WR(sp, 120) = WR(sp, 136);
    f0 = FR(sp, 100);
    f1 = FR(sp, 116);
    f0 = f0 * f1;
    f12 = f12 - f0;
    WR(sp, 124) = WR(sp, 140);
    f1 = FR(sp, 104);
    f0 = FR(sp, 120);
    f1 = f1 * f0;
    f12 = f12 - f1;
    f_0a5ea4(sp + 128, sp + 112, f12);
    f3 = FR(sp, 100) + FR(sp, 132);
    f0 = FR(sp, 132);
    f1 = D_1acc68;
    f2 = FR(sp, 104) + FR(sp, 136);
    f12 = f21 * f1;
    f6 = FR(sp, 4);
    f1 = FR(sp, 96) + FR(sp, 128);
    f3 = -f3;
    f2 = -f2;
    FR(sp, 96) = f1;
    FR(sp, 100) = f3;
    FR(sp, 104) = f2;
    if (f12 < f6) {
        f1 = f6;
    } else {
        f1 = f12;
    }
    FR(sp, 108) = f20;
    goto L_post_compare1;

L424:
    f21 = -f3;
    s5 = 1;
    s6 = 1;
    s8 = sp + 64;
    s7 = sp + 96;
    s0 = sp + 48;
    FR(sp, 36) = FR(sp, 36) + FR(sp, 4);
    FR(sp, 0) = FR(sp, 0) - FR(sp, 4);
    goto L08c;

L45c:
    s8 = sp + 64;
    s7 = sp + 96;
    s0 = sp + 48;
    goto L08c;

L_post_compare1:
    f6 = f1;
    f3 = D_1acc64;
    f0 = FR(sp, 36);
    f1 = f3 - f22;
    f12 = f6 * f22;
    f4 = FR(s2, 256);
    f5 = FR(s2, 260);
    f1 = f6 * f1;
    f2 = FR(s2, 264);
    s8 = sp + 64;
    s7 = sp + 96;
    f0 = f0 + f1;
    s0 = sp + 48;
    FR(sp, 36) = f0;
    FR(sp, 64) = f4;
    FR(sp, 68) = f5;
    FR(sp, 72) = f2;
    FR(sp, 76) = f3;
    f_0be470(self, s7, s0, s8, f12);
    f2 = FR(sp, 84) + FR(sp, 68);
    f0 = FR(sp, 4);
    f3 = FR(sp, 0) - f0;
    f4 = FR(s2, 256);
    f5 = FR(s2, 264);
    f6 = FR(sp, 64);
    f7 = FR(sp, 72);
    f1 = FR(sp, 80);
    f0 = FR(sp, 88);
    f4 = f4 + f6;
    f5 = f5 + f7;
    f1 = f1 + f6;
    f0 = f0 + f7;
    FR(sp, 84) = f2;
    FR(sp, 80) = f1;
    FR(sp, 88) = f0;
    FR(s2, 256) = f4;
    FR(s2, 264) = f5;
    FR(sp, 0) = f3;

L08c:
    /* Common block: the second wheel pass (entered from the E path, the idx sum 3 path and the
       cnt < 2 path). */
    v0 = s3 + WR(sp, 16) * 368;
    WR(sp, 96) = WR(v0, 272);
    a2p = v0 + 272;
    f0 = D_1acc68;
    f3 = FR(s2, 256);
    f6 = FR(sp, 0);
    f12 = f21 * f0;
    s5++;
    WR(sp, 100) = WR(a2p, 4);
    f1 = FR(s2, 260);
    f2 = FR(s2, 264);
    WR(sp, 104) = WR(a2p, 8);
    f0 = D_1acc64;
    WR(sp, 108) = WR(a2p, 12);
    FR(sp, 64) = f3;
    FR(sp, 68) = f1;
    FR(sp, 72) = f2;
    FR(sp, 76) = f0;
    if (f12 < f6) {
        f0 = f6;
    } else {
        f0 = f12;
    }
    /* L104: the second correction call. */
    f1 = D_1acc64;
    f12 = f0 * f22;
    f1 = f1 - f22;
    f1 = f0 * f1;
    f0 = FR(sp, 36) + f1;
    FR(sp, 36) = f0;
    f_0be470(self, s7, s0, s8, f12);
    FR(s2, 16) = FR(s2, 16) + FR(sp, 48);
    f1 = FR(sp, 64);
    f7 = FR(sp, 72);
    f4 = FR(s2, 256) + f1;
    f5 = FR(s2, 264);
    f2 = FR(sp, 80) + f1;
    f0 = FR(sp, 68);
    f1 = FR(sp, 84) + f0;
    f5 = f5 + f7;
    f3 = FR(sp, 88) + f7;
    FR(s2, 256) = f4;
    FR(s2, 264) = f5;
    FR(sp, 80) = f2;
    FR(sp, 84) = f1;
    FR(sp, 88) = f3;
    f_099b98(s2 + 16);
    f0 = FR(s2, 24) + FR(sp, 56);
    FR(s2, 24) = f0;
    f_099b98(s2 + 24);
    if (s5 == 2) {
        goto L380;
    }

L1b8:
    s3b = s2 + 768;
    s0 = sp + 144;
    f_0a2db0(s3b, s2 + 576);
    f_09ff44(s0);
    f0 = -FR(s2, 24);
    FR(sp, 192) = f0;
    f_099b98(sp + 192);
    f_0a082c(s0, WR(sp, 192), 0, 1);
    f0 = -FR(s2, 16);
    FR(sp, 196) = f0;
    f_099b98(sp + 196);
    f_0a082c(s0, WR(sp, 196), 1, 2);
    f0 = -FR(s2, 20);
    FR(sp, 200) = f0;
    f_099b98(sp + 200);
    f_0a082c(s0, WR(sp, 200), 2, 0);
    {
        char *d = s3b;
        char *e = sp + 144;
        do {
            copy16p(d, e);
            d += 16;
            e += 16;
        } while (e != sp + 192);
    }
    WR(s2, 816) = WR(s2, 0);
    WR(s2 + 816, 4) = WR(s2, 4);
    WR(s2 + 816, 8) = WR(s2, 8);
    WR(s2 + 816, 12) = WR(s2, 12);
    WR(s4, 48) = 0;
    FR(s4 + 48, 12) = D_1acc64;
    FR(s4 + 48, 4) = D_1acc64;
    WR(s4 + 48, 8) = 0;
    f_0a6c18(sp + 128, s3b, s4 + 48);
    WR(s4, 64) = WR(sp, 128);
    WR(s4, 68) = WR(sp, 132);
    WR(s4, 72) = WR(sp, 136);
    WR(s4, 76) = WR(sp, 140);
    f_0a5ea4(sp + 128, s4 + 64, D_1acc70);
    WR(s2, 384) = WR(sp, 128);
    WR(s2, 388) = WR(sp, 132);
    WR(s2, 392) = WR(sp, 136);
    WR(s2, 396) = WR(sp, 140);
    WR(s2, 400) = WR(s4, 64);
    WR(s2, 404) = WR(s4, 68);
    WR(s2, 408) = WR(s4, 72);
    WR(s2, 412) = WR(s4, 76);
    return;

L380:
    f_0a6bf4(sp + 128, s2 + 576, sp + 32);
    WR(sp, 32) = WR(sp, 128);
    WR(sp, 36) = WR(sp, 132);
    WR(sp, 40) = WR(sp, 136);
    f0 = FR(sp, 32);
    f2 = FR(s2, 0) + f0;
    f1 = FR(sp, 36);
    f3 = FR(s2, 4) + f1;
    f0 = FR(sp, 40);
    f4 = FR(s2, 8) + f0;
    WR(sp, 44) = WR(sp, 140);
    FR(s2, 0) = f2;
    FR(s2, 4) = f3;
    if (s6 == 0) {
        FR(s2, 8) = f4;
        goto L1b8;
    }
    FR(s2, 8) = f4;
    f1 = FR(self, 9896);
    f0 = D_1acc6c;
    f2 = FR(self, 9932);
    f3 = FR(s2, 196);
    f1 = f1 * f0;
    f1 = f1 * f2;
    if (f1 < f3) {
        FR(s2, 196) = f1;
    }
    goto L1b8;

}
