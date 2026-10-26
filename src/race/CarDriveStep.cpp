/* The car's drive step (retail 0x0fd6f8 to 0x0fe990, C++ with exceptions): the per frame
   update of one race car's physics. The car block holds the physics record at +5792 (its
   fields are read here by offset), the driving record at +7092, the tyre and drive sub-blocks
   at +7816 and +8064, and a pointer at +8048 to the car's spec. The steps run in order: the
   speed and the lateral offsets are integrated, the drive state is set, the wheel and ground
   forces are summed into the body, and the sub-blocks are updated from the drive bits. */

#define WR(p, o) (*(int *)((char *)(p) + (o)))
#define FR(p, o) (*(float *)((char *)(p) + (o)))
#define HR(p, o) (*(short *)((char *)(p) + (o)))

/* The drive bits at +7692 (read as bit fields by the step). */
struct DriveBits {
    unsigned b0 : 8;
    unsigned b8 : 3;
    unsigned b11 : 3;
    unsigned b14 : 1;
    unsigned b15 : 1;
    unsigned b16 : 1;
    unsigned rest : 15;
};

extern "C" {
float f_0c2bd0(float a, float b);
float f_0fe064(void *car, int k);
void f_0fe674(void *car);
void f_0fdee0(void *car, void *bits);
void f_0fe2a8(void *car, void *bits);
void f_0fe1b8(void *car, void *bits);
void f_0bbcb0(void *sub, int a, float x, float y);
void f_0bb840(void *sub, int a, int b, int c);
void f_0bc240(void *sub, int v);
void f_0fd6f8(void *car);
void f_0fd80c(void *car);
float f_0e26dc(void *obj, float x);
void f_0e2d10(void *obj, float *a, float *b, float *c, float x, float y);
void f_0a5e1c(void *v, float len);
void f_0a5e88(void *out, void *v, void *phys);
void f_0a6c18(void *out, void *m, void *v);
float f_09a9dc(float x, float z);
}

extern char D_23c820[];

/* @implements 0x0fe1b8 us f_0fe1b8
   WHAT IT DOES: Sets the sub-block's ratio (+32) from the 3 bit drive field (b8 / 7), then
   runs its two timers: when the field is non-zero the timer at +36 is raised toward the
   ratio, otherwise it is cleared or follows a rate; the level at +28 takes the timer and is
   squared at the end. */
extern "C" void f_0fe1b8(void *car, void *bp)
{
    DriveBits *bits = (DriveBits *)bp;
    char *s = (char *)car + 7816;
    float f = (float)bits->b8 / 7.0f;
    FR(s, 32) = f;
    if (bits->b8 != 0) {
        float t = FR(s, 36) + 0.0833333358f;
        FR(s, 36) = t;
        if (f < t)
            FR(s, 36) = f;
        FR(s, 28) = FR(s, 36);
        if (WR(s, 8) == 1)
            WR(s, 28) = 0;
    } else {
        if (WR(s, 8) == 2) {
            float t = FR(s, 28) + 0.0833333358f;
            FR(s, 28) = t;
            if (!(t < 1.0f))
                t = 1.0f;
            FR(s, 28) = t;
        } else {
            WR(s, 28) = 0;
            WR(s, 36) = 0;
        }
    }
    FR(s, 28) = FR(s, 28) * FR(s, 28);
}

/* @implements 0x0fddf8 us f_0fddf8
   WHAT IT DOES: Sets the car's per frame value at +916 from the result of the ground test
   (f_0fe064 with k 2) run through the angle helper f_0c2bd0, scaled by 0.15 when the flag at
   +1020 is set, and zero otherwise. */
extern "C" void f_0fddf8(void *car)
{
    char *ph = (char *)car + 5792;
    float r = f_0c2bd0(f_0fe064(car, 2), FR(ph, 964));
    if (WR(ph, 1020) != 0)
        FR(ph, 916) = r * 0.15000000596f;
    else
        WR(ph, 916) = 0;
}

/* @implements 0x0fde50 us f_0fde50
   WHAT IT DOES: Computes the car's steering-like value at +1088: the lateral term from the
   car's two gains and the input at +6040 over the speed at +8088, limited to a bound that is
   scaled from +1060 and the spec at +8048, with the sign of that term kept. */
extern "C" void f_0fde50(void *car)
{
    char *ph = (char *)car + 5792;
    char *q = *(char **)((char *)car + 8048);
    float n = -FR(car, 6040) * FR(ph, 1060) * FR(car, 8084) / FR(car, 8088);
    float bnd = FR(ph, 1060) * 0.5f * 9.8000001907f * FR(q, 20);
    float a = n;
    if (n < 0.0f)
        a = -n;
    float c = a < bnd ? a : bnd;
    float s = c;
    if (n < 0.0f)
        s = -c;
    FR(ph, 1088) = s / bnd;
}

/* @draft 0x0fd6f8 us f_0fd6f8
   WHAT IT DOES: Runs the car's per frame physics block: when the flag at +968 is set the
   speed term at +912 is advanced by the angle helper result (scaled by the spec's gain when
   the spec's value is above 1/60 s), the flag word at +10092 is cleared, the term at +916 is
   scaled by 1/60 and 10, and the drive record's two flags (+4 and +36) are updated from the
   spec's threshold (27.78) and the flag at +470. */
extern "C" void f_0fd6f8(void *car)
{
    char *ph = (char *)car + 5792;
    char *d = (char *)car + 7092;
    char *q = *(char **)((char *)car + 8048);
    if (HR(ph, 968) != 0) {
        float r = f_0c2bd0(FR(ph, 1108), FR(ph, 912));
        if (0.0166666675f < FR(q, 16))
            FR(ph, 912) = FR(ph, 912) + (r * 0.0166666675f) * FR(car, 9892);
        else
            FR(ph, 912) = FR(ph, 912) + r;
    }
    WR(car, 10092) = 0;
    FR(ph, 916) = FR(ph, 916) * 0.0166666675f * 10.0f;
    if (WR(ph, 1140) != 0) {
        if (WR(d, 36) == 0) {
            if (27.7800007f < FR(ph, 1096))
                WR(d, 4) = 1;
        }
    } else {
        WR(d, 36) = 0;
    }
    if (HR(ph, 470) != 0)
        WR(d, 36) = 1;
}

/* @implements 0x0fe8a4 us f_0fe8a4
   WHAT IT DOES: The car's drive step: clears the drive bits when the timer at +9912 is
   negative, runs the sub-step f_0fe674, updates the tyre sub-block with the bits, runs the
   two drive helpers and the level helper, adds the level to the car's accumulator at +6648
   when the flag at +972 is set, then runs the two force steps f_0fde50 and f_0fdee0. */
extern "C" void f_0fe8a4(void *car)
{
    char *ph = (char *)car + 5792;
    char *s = (char *)car + 7816;
    DriveBits *bits = (DriveBits *)((char *)car + 7692);
    if (WR(car, 9912) < 0)
        WR(car, 7692) = 0;
    f_0fe674(car);
    f_0bbcb0(s, WR(ph, 972), FR(ph, 1136), FR(ph, 1096));
    f_0bb840(s, bits->b14, bits->b15, WR(ph, 1020));
    f_0fe1b8(car, bits);
    f_0fe2a8(car, bits);
    f_0bc240(s, bits->b8);
    if (WR(ph, 972) != 0)
        FR(car, 6648) = FR(car, 6648) + FR(s, 76);
    f_0fde50(car);
    f_0fdee0(car, bits);
}

/* @draft 0x0fdee0 us f_0fdee0
   WHAT IT DOES: Updates the car's two sub-block levels (+16, +20, from the scaled gains at
   +8 and +12 over 127) from the signed byte at the drive bits, then moves the car's value
   at +1108 (x0.2 when the byte is zero, else adds or clamps the level at +32/+36 against the
   level at +16/+20), clamps the ratio at +44 to 1.0, and finally runs the drive step f_0fd6f8
   or f_0fd80c according to the drive state at +4 and raises the output at +10048 when the
   flag at +10088 is set. */
extern "C" void f_0fdee0(void *car, void *bits)
{
    char *ph = (char *)car + 5792;
    char *d = (char *)car + 7092;
    char *s2 = (char *)car + 7996;
    signed char k = *(signed char *)bits;
    float a = (float)k;
    if (a < 0.0f)
        a = -a;
    FR(s2, 20) = FR(s2, 12) * a / 127.0f;
    FR(s2, 16) = FR(s2, 8) * a / 127.0f;
    if (k == 0) {
        FR(ph, 1108) = FR(ph, 1108) * 0.2f;
    } else {
        float v;
        if (k < 0) {
            v = FR(ph, 1108) + FR(s2, 32);
            FR(ph, 1108) = v;
            if (!(v < FR(s2, 16)))
                v = FR(s2, 16);
        } else {
            v = FR(ph, 1108) + FR(s2, 36);
            FR(ph, 1108) = v;
            if (!(FR(s2, 20) < v))
                v = FR(s2, 20);
        }
        FR(ph, 1108) = v;
    }
    if (FR(s2, 16) == 0.0f) {
        FR(s2, 44) = 0.0f;
    } else {
        float q = FR(ph, 1108) / FR(s2, 16);
        float aq = q;
        if (q < 0.0f)
            aq = -q;
        FR(s2, 44) = aq < 1.0f ? aq : 1.0f;
    }
    if (WR(d, 4) == 0)
        f_0fd6f8(car);
    else if (WR(d, 4) == 1)
        f_0fd80c(car);
    if (WR(car, 10088) == 1)
        FR(car, 10048) = 300.0f;
}

/* @draft 0x0fe064 us f_0fe064
   WHAT IT DOES: Returns a float: the car's value from the input k (negated when the halfword
   at +468 is set), offset by the float at +2144, passed through the helper f_0e26dc into the
   global block at D_23c820; the three outputs of f_0e2d10 (y and z negated) form a vector
   that is normalised by f_0a5e1c, transformed by f_0a5e88 and f_0a6c18 against the matrix at
   +576, and its x and z components are passed to f_09a9dc. */
struct Vec4Out {
    float x, y, z, w;
};

extern "C" float f_0fe064(void *car, int k)
{
    char *ph = (char *)car + 5792;
    char *g = D_23c820 + 12240;
    short h = HR(ph, 468);
    float t = FR(car, 2144) + (float)(h != 0 ? -k : k);
    float r = f_0e26dc(g, t);
    float o0, o1, o2;
    f_0e2d10(g, &o0, &o1, &o2, FR(car, 2148), r);
    Vec4Out v;
    v.x = o0;
    v.y = -o1;
    v.z = -o2;
    v.w = 1.0f;
    f_0a5e1c(&v, 0.001f);
    Vec4Out w = v;
    Vec4Out o;
    f_0a5e88(&o, &w, ph);
    Vec4Out tmp = o;
    f_0a6c18(&o, ph + 576, &tmp);
    return f_09a9dc(o.z, o.x);
}
