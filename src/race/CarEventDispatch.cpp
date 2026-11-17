/* Car event dispatch object file (retail 0x0bef6c to 0x0bf23c: the tail of the eh object TU 228
   and its gap TU 229): a vector transform helper that builds a rotation from two vectors and
   writes the result into a car block, and the event dispatcher that calls one of two handlers
   on the global block D_245ec0 when the event pair matches. The two small wrappers call the
   dispatcher with the fixed pairs. */

/* Flag choice (whole file, all functions transcribed): the no-schedule-insns2 flag is kept.
   With it, 2 of 5 functions are EXACT (f_0bf1fc, f_0bf21c); without it, 0 of 5 are EXACT (those
   two wrappers become 2 of 8 words wrong and f_0bf190 shows 17 of 29 vs 25 of 29). */

#define FR(p, o) (*(float *)((char *)(p) + (o)))
#define WR(p, o) (*(int *)((char *)(p) + (o)))

extern "C" {
void f_0a5e1c(void *v, float len);
float f_09a9dc(float a, float b);
void f_09ff44(void *p);
void f_099b98(void *p);
void f_0a082c(void *p, int bits, int a2, int a3);
void f_0be85c(void *p);
void f_0be86c(void *p);
void f_0bf190(int a, int b);
void f_0bef6c(void *a0, void *a1, void *a2, void *a3);
void f_0a6bf4(void *out, void *m, void *v);
void f_0a6c18(void *out, void *m, void *v);
void f_0a5e6c(void *d, const void *a, const void *b);
void f_0a5e88(void *d, const void *a, const void *b);
void f_0a5f74(void *d, const void *a, const void *b);
void f_0a5dc8(void *a, void *b);
void f_0a6580(void *p);
int f_0b1bc0(void *o, int n, float x, float z);
int f_0b2f18(void *a0, void *a1, void *a2, void *a3, float x, float y, void *s, void *t);
float f_0e286c(void *self, void *n, float x, float z);
extern "C" float sqrtf(float);
}

/* @cflags: -fno-schedule-insns2 */
extern char D_245ec0[];
extern float D_1acc90;
extern float D_1acc78;
extern float D_1acc7c;
extern float D_1acc80;
extern float D_1acc84;
extern float D_1acc88;
extern float D_1acc8c;
extern char *D_2456d0;
extern char D_23c820[];

static inline void copy16(char *d, const char *s)
{
    WR(d, 0) = WR(s, 0);
    WR(d, 4) = WR(s, 4);
    WR(d, 8) = WR(s, 8);
    WR(d, 12) = WR(s, 12);
}

/* @draft 0x0be874 us f_0be874
   WHAT IT DOES: builds the car's per frame block from its wheel and body vectors: runs the
   vector helpers on the car's blocks, writes the derived vectors into the global block at
   D_2456d0, calls the matrix and angle helpers, and when the result is non zero writes the
   final block values and runs the transform that ends in f_0a5dc8.
   Remaining difference: transcribed from the listing, not yet compared against retail. */
extern "C" void f_0be874(void *a0, char *self)
{
    char sp[336];
    char *s1 = sp + 16;
    char *s0 = sp + 32;
    char *s8 = sp + 144;
    char *s7 = sp + 160;
    char *s6 = D_2456d0;
    char *s5 = self + 5792;
    char *s4 = s6 + 1056;
    char *s2 = self + 2756;
    char *a2 = self + 2128;
    char *v2 = s6 + 1312;
    FR(s4, 44) = FR(s5, 444);
    WR(s4, 40) = WR(s5, 428);
    WR(s6, 1312) = 0;
    WR(v2, 12) = 0;
    WR(v2, 4) = 0;
    WR(v2, 8) = 0;
    *(short *)(s5 + 470) = 0;
    void *saved_a0 = a0;
    f_0b1bc0(s2, WR(a2, 112), FR(self, 2128), FR(self, 2132));
    WR(sp, 16) = WR(s5, 0);
    FR(sp, 20) = -FR(s5, 4);
    FR(sp, 24) = -FR(s5, 8);
    FR(sp, 28) = D_1acc78;
    WR(sp, 32) = WR(s5, 32);
    WR(sp, 36) = WR(s5, 36);
    WR(sp, 40) = WR(s5, 40);
    WR(sp, 44) = WR(s5, 44);
    f_0a5e1c(s1, D_1acc7c);
    FR(sp, 44) = D_1acc78;
    FR(sp, 36) = -FR(sp, 36);
    FR(sp, 40) = -FR(sp, 40);
    f_0a5e1c(s0, D_1acc7c);
    int s1r = f_0b2f18(s2, s1, s0, sp + 48, FR(self, 5812), FR(self, 5844), sp + 96, sp + 112);
    WR(sp, 152) = 0;
    WR(sp, 156) = 0;
    WR(sp, 144) = 0;
    WR(sp, 148) = 0;
    WR(self, 1896) = 0;
    WR(self, 1872) = 0;
    WR(self, 1876) = 0;
    WR(self, 1880) = 0;
    WR(self, 1884) = 0;
    WR(self, 1856) = 0;
    WR(self, 1860) = 0;
    WR(self, 1864) = 0;
    WR(self, 1868) = 0;
    WR(self, 1904) = 0;
    WR(self, 1900) = 0;
    WR(self, 1908) = 0;
    WR(self, 1888) = 0;
    WR(self, 1912) = 0;
    WR(self, 1916) = 0;
    if (s1r == 0) {
        return;
    }
    FR(self, 1896) = FR(sp, 240);
    char *g = (char *)D_23c820;
    *(short *)(s5 + 470) = 1;
    WR(self, 1876) = WR(sp, 52);
    WR(self, 1880) = WR(sp, 56);
    WR(self, 1884) = WR(sp, 60);
    WR(self, 1856) = WR(sp, 64);
    WR(self, 1860) = WR(sp, 68);
    WR(self, 1864) = WR(sp, 72);
    WR(self, 1868) = WR(sp, 76);
    WR(self, 1872) = WR(sp, 48);
    WR(self, 1904) = WR(sp, 80);
    WR(self, 1908) = WR(sp, 84);
    WR(self, 1912) = WR(sp, 88);
    WR(self, 1916) = WR(sp, 92);
    FR(self, 1900) = FR(sp, 244);
    WR(self, 1888) = s1r;
    float e0 = f_0e286c(g, sp + 128, FR(sp, 96), FR(sp, 104));
    FR(sp, 116) = e0;
    FR(sp, 100) = e0;
    FR(sp, 52) = -FR(sp, 52);
    FR(sp, 56) = -FR(sp, 56);
    FR(sp, 60) = D_1acc78;
    f_0a5e1c(sp + 48, D_1acc7c);
    FR(sp, 68) = -FR(sp, 68);
    FR(sp, 72) = -FR(sp, 72);
    FR(sp, 76) = D_1acc78;
    f_0a5e1c(sp + 64, D_1acc7c);
    FR(sp, 84) = -FR(sp, 84);
    FR(sp, 88) = -FR(sp, 88);
    FR(sp, 92) = D_1acc78;
    f_0a5e1c(sp + 80, D_1acc7c);
    FR(sp, 100) = -FR(sp, 100);
    FR(sp, 104) = -FR(sp, 104);
    FR(sp, 108) = D_1acc78;
    f_0a5e1c(sp + 96, D_1acc7c);
    FR(sp, 116) = -FR(sp, 116);
    FR(sp, 120) = -FR(sp, 120);
    FR(sp, 124) = D_1acc78;
    f_0a5e1c(sp + 112, D_1acc7c);
    FR(sp, 132) = -FR(sp, 132);
    FR(sp, 136) = -FR(sp, 136);
    FR(sp, 140) = D_1acc78;
    WR(s4, 64) = WR(sp, 112);
    WR(s4, 68) = WR(sp, 116);
    WR(s4, 72) = WR(sp, 120);
    WR(s4, 76) = WR(sp, 124);
    WR(s4, 96) = WR(sp, 96);
    WR(s4, 100) = WR(sp, 100);
    WR(s4, 104) = WR(sp, 104);
    WR(s4, 108) = WR(sp, 108);
    WR(sp, 144) = WR(sp, 128);
    WR(sp, 148) = WR(sp, 132);
    WR(sp, 152) = WR(sp, 136);
    WR(sp, 156) = WR(sp, 140);
    f_0a5e1c(s8, D_1acc84);
    f_0a5e6c(s7, s6 + 1120, s8);
    WR(s4, 80) = WR(sp, 160);
    WR(s4, 84) = WR(sp, 164);
    WR(s4, 88) = WR(sp, 168);
    f_0a5e6c(s7, s1, s8);
    WR(s4, 92) = WR(sp, 172);
    WR(s4, 112) = WR(sp, 160);
    WR(s4, 116) = WR(sp, 164);
    WR(s4, 120) = WR(sp, 168);
    f_0a5e88(s7, s1, s6 + 1136);
    WR(s4, 124) = WR(sp, 172);
    WR(s4, 128) = WR(sp, 160);
    WR(s4, 132) = WR(sp, 164);
    WR(s4, 136) = WR(sp, 168);
    f_0a5e88(s7, s6 + 1168, s6 + 1120);
    WR(s4, 140) = WR(sp, 172);
    WR(s4, 144) = WR(sp, 160);
    WR(s4, 148) = WR(sp, 164);
    WR(s4, 152) = WR(sp, 168);
    f_0a5f74(s7, s6 + 1184, s6 + 1200);
    WR(s4, 156) = WR(sp, 172);
    WR(sp, 144) = WR(sp, 160);
    WR(sp, 148) = WR(sp, 164);
    WR(sp, 152) = WR(sp, 168);
    WR(sp, 156) = WR(sp, 172);
    f_0a6580(s8);
    WR(sp, 160) = WR(s6, 1056);
    WR(sp, 164) = WR(s4, 4);
    WR(sp, 168) = WR(s4, 8);
    WR(sp, 172) = WR(s4, 12);
    copy16(sp + 176, s6 + 1216);
    copy16(sp + 192, s6 + 1232);
    copy16(sp + 208, s6 + 1248);
    copy16(sp + 224, s6 + 1264);
    f_0bef6c(saved_a0, s8, s7, sp + 176);
    float f20 = FR(sp, 148);
    float sq = sqrtf(D_1acc78 - f20 * f20);
    float r1 = f_09a9dc(f20, sq);
    FR(s4, 256) = r1;
    char *s0b = s4 + 272;
    float r2 = f_09a9dc(-FR(sp, 144), FR(sp, 152));
    FR(s4, 260) = r2;
    f_09ff44(s0b);
    FR(sp, 248) = FR(s4, 260);
    f_099b98(sp + 248);
    f_0a082c(s0b, WR(sp, 248), 2, 0);
    FR(sp, 252) = FR(s4, 256);
    f_099b98(sp + 252);
    f_0a082c(s0b, WR(sp, 252), 1, 2);
    f_0a6bf4(s7, s0b, s5 + 192);
    WR(s4, 368) = WR(sp, 160);
    WR(s4, 372) = WR(sp, 164);
    WR(s4, 376) = WR(sp, 168);
    WR(s4, 380) = WR(sp, 172);
    FR(s4, 368) = FR(s4, 368) * D_1acc88;
    FR(s4, 376) = -8.0f;
    if (FR(s4, 372) < 0.0f) {
        FR(s4, 372) = 0.0f;
    }
    f_0a6c18(s7, s0b, s4 + 368);
    WR(s5, 196) = WR(sp, 164);
    WR(s5, 192) = WR(sp, 160);
    WR(s5, 200) = WR(sp, 168);
    WR(s5, 204) = WR(sp, 172);
    f_0a5dc8(s5, sp + 48);
}

/* @draft 0x0bef6c us f_0bef6c
   WHAT IT DOES: copies the first vector and the second vector into a 224 byte frame and copies a
   64 byte table into the frame, takes the angle of the first vector against its own length, and
   builds a rotation from the second vector's negated components. Two matrix transforms
   (f_0a082c) are applied to a matrix that is copied to the frame, and the transformed result is
   left in the frame.
   Remaining difference: not yet compared against retail. */
extern "C" void f_0bef6c(void *a0, void *a1, void *a2, void *a3)
{
    char sp[224];
    char *s0 = sp;
    char *s1 = sp + 16;
    char *s2 = sp + 32;
    WR(sp, 0) = WR(a1, 0);
    WR(sp, 4) = WR(a1, 4);
    WR(sp, 8) = WR(a1, 8);
    WR(sp, 12) = WR(a1, 12);
    WR(sp, 16) = WR(a2, 0);
    WR(sp, 20) = WR(a2, 4);
    WR(sp, 24) = WR(a2, 8);
    WR(sp, 28) = WR(a2, 12);
    {
        char *d = sp + 32;
        const char *e = (const char *)a3;
        const char *end = (const char *)a3 + 64;
        do {
            copy16(d, e);
            d += 16;
            e += 16;
        } while (e != end);
    }
    float d0 = f_09a9dc(FR(s0, 0), FR(s0, 8));
    float nd0 = -d0;
    float len = sqrtf(FR(s0, 0) * FR(s0, 0) + FR(s0, 8) * FR(s0, 8));
    float c = f_09a9dc(FR(s0, 4), len);
    FR(sp, 116) = -FR(s1, 4);
    FR(sp, 112) = -FR(s1, 0);
    FR(sp, 120) = -FR(s1, 8);
    FR(sp, 124) = D_1acc90;
    char *m = sp + 128;
    {
        WR(sp, 96) = WR(sp, 112);
        WR(sp, 100) = WR(sp, 116);
        WR(sp, 104) = WR(sp, 120);
        WR(sp, 108) = WR(sp, 124);
    }
    f_09ff44(m);
    char *v = sp + 176;
    FR(sp, 176) = nd0;
    f_099b98(v);
    f_0a082c(m, WR(sp, 176), 2, 0);
    FR(sp, 180) = c;
    f_099b98(sp + 180);
    f_0a082c(m, WR(sp, 180), 1, 2);
    {
        char *d = s2;
        char *e = m;
        do {
            copy16(d, e);
            d += 16;
            e += 16;
        } while (e != v);
    }
    WR(sp, 116) = WR(sp, 100);
    WR(sp, 124) = WR(sp, 108);
    WR(sp, 120) = WR(sp, 104);
    WR(sp, 80) = WR(sp, 96);
    WR(sp, 84) = WR(sp, 116);
    WR(sp, 88) = WR(sp, 120);
    WR(sp, 92) = WR(sp, 124);
}

/* @draft 0x0bf190 us f_0bf190
   WHAT IT DOES: calls the handler f_0be85c on D_245ec0 when the event is 1 with the code
   0xffff, and f_0be86c when it is 0 with the code 0xffff.
   Remaining difference: 17 of 29 words differ, size 116 vs 108; the retail code saves the
   first argument across the call and orders the two tests differently. nmQ: retail keeps
   both calls on the fall-through (beqz around them) and tests the second as and(ok, a==0);
   here bb-reorder moves the calls out of line and combine splits the second test into
   bnez/bnezl. The `and` operands are ok first (and v0,s0,v0). */
extern "C" void f_0bf190(int a, int b)
{
    int t1 = (a == 1);
    int ok = (b == 0xffff);
    if (t1 & ok) {
        f_0be85c(D_245ec0);
    }
    if ((a == 0) & ok) {
        f_0be86c(D_245ec0);
    }
}

/* @implements 0x0bf1fc us f_0bf1fc
   WHAT IT DOES: calls the dispatcher with the event pair (1, 0xffff). */
extern "C" void f_0bf1fc(void)
{
    f_0bf190(1, 0xffff);
}

/* @implements 0x0bf21c us f_0bf21c
   WHAT IT DOES: calls the dispatcher with the event pair (0, 0xffff). */
extern "C" void f_0bf21c(void)
{
    f_0bf190(0, 0xffff);
}
