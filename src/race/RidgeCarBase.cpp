/* The race car base class, Car::CRidgeCar (retail 0x0b6754 to 0x0bb350, object 218, plus the
   gap row 219 at 0x0bb350 to 0x0bb480). Its base object and its three sub-objects are built
   in order: the base, the vtable pointer, the sub-object at +7680, the one at +7996 and the
   one at +8064. The race car base also holds the per frame physics step, the course and
   collision checks, the drift and the cornering loss. */

extern "C" {
void f_0ec364(void *);
void f_0ec67c(void *);
void f_0fd6cc(void *);
void f_0fd6dc(void *);
void f_0bd1c4(void *);
void f_0bd1d4(void *);
void f_0bc7cc(void *);
void f_0bc88c(void *);
void f_0bd880(void *);
void f_0b71c0(void *);
void f_0b86ac(void *);
void f_0b6e44(void *);
void f_0b89e8(void *);
void f_0b8884(void *);
void f_0a74cc(void *);
void f_09b070(void *out, void *m, int axis);
void f_0bd234(void *o, float a, float b);
void f_0a5ea4(void *out, void *m, float f);
float f_0a65c4(void *v);
void f_0bc954(void *o, float a, float b, float c, float d, float e, float g, float h);
void f_0a6d4c(void *out, void *m, void *v);
void f_0be874(void *list, void *car);
void f_099b98(float *a);
void f_0a5e1c(void *v, float len);
}

extern char D_1acab8[];
extern char D_245ec0[];

/* A field of the car at a byte offset. */
#define FLT(p, o) (*(float *)((char *)(p) + (o)))
#define INT(p, o) (*(int *)((char *)(p) + (o)))
/* A word read as an integer or as a float (the retail code copies these through integer registers). */
union FloatBits {
    float f;
    int i;
};

#define CHR(p, o) (*(signed char *)((char *)(p) + (o)))

/* The base object (its constructor and destructor are in another object file). */
struct CarBase {
    CarBase() { f_0ec364(this); }
    ~CarBase() { f_0ec67c(this); }
};

/* The vtable pointer. It is stored after the base object is built and before the members. */
struct CarVt : CarBase {
    void *vptr;
    CarVt() { vptr = D_1acab8; }
};

/* The sub-object at +7680 (316 bytes). */
struct SubA {
    SubA() { f_0fd6cc(this); }
    ~SubA() { f_0fd6dc(this); }
    char p[316];
};

/* The sub-object at +7996 (68 bytes). */
struct SubB {
    SubB() { f_0bd1c4(this); }
    ~SubB() { f_0bd1d4(this); }
    char p[68];
};

/* The sub-object at +8064. */
struct SubC {
    SubC() { f_0bc7cc(this); }
    ~SubC() { f_0bc88c(this); }
    char p[1024];
};

namespace Car {

/* The race car base. */
struct CRidgeCar : CarVt {
    char p4[5788];
    char ph[1888];         /* 5792: the physics record */
    SubA a;                /* 7680 */
    SubB b;                /* 7996 */
    SubC c;                /* 8064 */

    CRidgeCar();
    ~CRidgeCar() { vptr = D_1acab8; }
};

CRidgeCar::CRidgeCar()
{
    CHR(this, 7692) = 0;
    INT(this, 7692) &= 0xfffff8ff;
    INT(this, 7692) &= 0xffffc7ff;
    INT(this, 7692) &= 0xffffbfff;
    INT(this, 7692) &= 0xffff7fff;
    INT(this, 7692) &= 0xfffeffff;
}


}

/* @implements 0x0b6754 us _ZN3Car9CRidgeCarC2Ev
   WHAT IT DOES: Base object constructor: builds the base object, the vtable pointer, the three
   sub-objects in order, then clears the state bits in the flag word at +7692. */
/* @implements 0x0b682c us _ZN3Car9CRidgeCarC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */

/* @implements 0x0b6904 us f_0b6904
   WHAT IT DOES: Base object destructor: stores the vtable pointer, then destroys the sub-objects
   at +8064, +7996 and +7680 in turn, then the base object. */
/* @implements 0x0b6990 us f_0b6990
   WHAT IT DOES: Complete object destructor, the same as the base object one. */

/* @implements 0x0b6ab0 us f_0b6ab0
   WHAT IT DOES: An empty function. */
extern "C" void f_0b6ab0(void *c)
{
    (void)c;
}

/* @implements 0x0b6ab8 us f_0b6ab8
   WHAT IT DOES: An empty function. */
extern "C" void f_0b6ab8(void *c)
{
    (void)c;
}

/* @implements 0x0b6ac0 us f_0b6ac0
   WHAT IT DOES: Copies the two floats at +144 and +152 into +2128 and +2132, takes the second
   float of f_09b070's result for axis 4 of the matrix at +208 into +2136, then calls f_0a74cc on
   the pair at +2128. */
extern "C" void f_0b6ac0(void *cp)
{
    char *c = (char *)cp;
    float out[2];
    float a = FLT(c, 144);
    float b = FLT(c, 152);
    FLT(c, 2128) = a;
    FLT(c, 2132) = b;
    f_09b070(out, c + 208, 4);
    FLT(c, 2136) = out[1];
    f_0a74cc(c + 2128);
}

/* @implements 0x0b6b10 us f_0b6b10
   WHAT IT DOES: Calls f_0bd880 on the car. */
extern "C" void f_0bd880_b(void *c);
extern "C" void f_0b6b10(void *c)
{
    f_0bd880(c);
}

/* @implements 0x0b6b2c us f_0b6b2c
   WHAT IT DOES: Calls f_0b71c0 on the car. */
extern "C" void f_0b6b2c(void *c)
{
    f_0b71c0(c);
}

/* @implements 0x0b6d1c us f_0b6d1c
   WHAT IT DOES: Passes the car's speed, lateral values and the body's height and the follower
   offset to f_0bc954 at +8064.
   Remaining difference: not yet compared. */
extern "C" void f_0b6d1c(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    float a = FLT(c, 6024);
    float b = FLT(ph, 1096);
    float f = FLT(c, 7836);
    float d = FLT(ph, 1136);
    float g = FLT(ph, 1108);
    f_0bc954(c + 8064, a, b, f, d, b, g, a);
}

/* @implements 0x0b6d58 us f_0b6d58
   WHAT IT DOES: Passes two of the physics record's floats to f_0bd234 at +7996.
   Remaining difference: not yet compared. */
extern "C" void f_0b6d58(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    f_0bd234(c + 7996, FLT(ph, 1096), FLT(ph, 1088));
}

/* @implements 0x0b6d80 us f_0b6d80
   WHAT IT DOES: Calls f_0b6e44 on the car. */
extern "C" void f_0b6d80(void *c)
{
    f_0b6e44(c);
}

/* @implements 0x0b6d9c us f_0b6d9c
   WHAT IT DOES: Calls f_0b89e8 on the car. */
extern "C" void f_0b6d9c(void *c)
{
    f_0b89e8(c);
}

/* @implements 0x0b6db8 us f_0b6db8
   WHAT IT DOES: Calls f_0b8884 on the car. */
extern "C" void f_0b6db8(void *c)
{
    f_0b8884(c);
}

/* @implements 0x0b6dd4 us f_0b6dd4
   WHAT IT DOES: Calls the car's virtual slot 19 unless the car's state at +128 is 1.
   Remaining difference: not yet compared. */
extern "C" void f_0b6dd4(void *c)
{
    if (INT(c, 128) != 1) {
        typedef void (*VFn)(void *);
        (*(VFn *)(*(char **)c + 76))(c);
    }
}

/* @implements 0x0b6e08 us f_0b6e08
   WHAT IT DOES: Calls f_0b86ac, f_0b6e44, f_0b89e8 and f_0b8884 on the car in that order.
   Remaining difference: not yet compared. */
extern "C" void f_0b6e08(void *c)
{
    f_0b86ac(c);
    f_0b6e44(c);
    f_0b89e8(c);
    f_0b8884(c);
}

void operator delete(void *);

extern "C" void f_0b6904(void *p)
{
    ((Car::CRidgeCar *)p)->~CRidgeCar();
}

extern "C" void f_0b6990(void *p)
{
    ((Car::CRidgeCar *)p)->~CRidgeCar();
}

/* @implements 0x0b6a1c us f_0b6a1c
   WHAT IT DOES: The deleting destructor: runs the destructor on the car and frees it.
   Remaining difference: not yet compared. */
extern "C" void f_0b6a1c(void *p)
{
    Car::CRidgeCar *c = (Car::CRidgeCar *)p;
    c->~CRidgeCar();
    operator delete(p);
}

/* @implements 0x0b8d1c us f_0b8d1c
   WHAT IT DOES: An empty function. */
extern "C" void f_0b8d1c(void *c)
{
    (void)c;
}

/* @implements 0x0b99c8 us f_0b99c8
   WHAT IT DOES: Returns the car's word at +1952. */
extern "C" int f_0b99c8(void *c)
{
    return INT(c, 1952);
}

/* @implements 0x0b9e04 us f_0b9e04
   WHAT IT DOES: Stores the second argument at +9904 of the car. */
extern "C" void f_0b9e04(void *c, int v)
{
    INT(c, 9904) = v;
}

/* @implements 0x0b9e0c us f_0b9e0c
   WHAT IT DOES: Stores 1.0 at +7836 of the car (the follower's offset field). */
extern "C" void f_0b9e0c(void *c)
{
    FLT(c, 7836) = 1.0f;
}


/* @draft 0x0b9098 us f_0b9098
   WHAT IT DOES: Copies the first three entries of each row of a 4x4 matrix and sets the last
   column to zero, except the bottom right entry which is 1.0. */
extern "C" void f_0b9098(float *dst, float *src)
{
    for (int i = 0; i < 4; i++)
        for (int k = 0; k < 3; k++)
            dst[i * 4 + k] = src[i * 4 + k];
    FLT(dst, 12) = 0.0f;
    FLT(dst, 60) = 1.0f;
    FLT(dst, 28) = 0.0f;
    FLT(dst, 44) = 0.0f;
}

/* @draft 0x0b9c78 us f_0b9c78
   WHAT IT DOES: Takes a vector from the car's field at +1856 scaled by 0.06 and its length
   along the car's heading, and stores the sign-corrected value at +10112 when it is larger.
   Remaining difference: not yet compared; the operand order is a guess. */
extern "C" void f_0b9c78(void *cp)
{
    char *c = (char *)cp;
    struct V4 {
        float x, y, z, w;
    };
    V4 out;
    f_0a5ea4(&out, c + 1856, 0.06f);
    V4 v = out;
    float f1 = f_0a65c4(&v);
    if (FLT(c, 1896) < 0.0f)
        f1 = -f1;
    float f0 = FLT(c, 10112);
    float f3 = f1;
    if (f0 < 0.0f)
        f0 = -f0;
    if (f1 < 0.0f)
        f3 = -f1;
    if (f0 < f3)
        FLT(c, 10112) = f1;
}

/* @implements 0x0bb350 us f_0bb350
   WHAT IT DOES: Clears the car's fields from +4 to +176 (the words at +140 are set to 1.0).
   Remaining difference: the constant is read from .rodata at 0x1acb30 and written as a literal;
   not yet compared. */
extern "C" void f_0bb350(void *cp)
{
    char *c = (char *)cp;
    INT(c, 4) = 0;
    INT(c, 8) = 0;
    INT(c, 12) = 0;
    INT(c, 16) = 0;
    INT(c, 20) = 0;
    INT(c, 24) = 0;
    INT(c, 28) = 0;
    INT(c, 32) = 0;
    INT(c, 36) = 0;
    INT(c, 40) = 0;
    INT(c, 44) = 0;
    INT(c, 48) = 0;
    INT(c, 52) = 0;
    INT(c, 56) = 0;
    INT(c, 60) = 0;
    INT(c, 64) = 0;
    INT(c, 68) = 0;
    INT(c, 72) = 0;
    INT(c, 76) = 0;
    INT(c, 80) = 0;
    INT(c, 84) = 0;
    INT(c, 88) = 0;
    INT(c, 92) = 0;
    INT(c, 96) = 0;
    INT(c, 100) = 0;
    INT(c, 104) = 0;
    INT(c, 108) = 0;
    INT(c, 112) = 0;
    INT(c, 116) = 0;
    INT(c, 120) = 0;
    INT(c, 124) = 0;
    INT(c, 128) = 0;
    INT(c, 132) = 0;
    INT(c, 136) = 0;
    FLT(c, 140) = 1.0f;
    INT(c, 144) = 0;
    INT(c, 148) = 0;
    INT(c, 152) = 0;
    INT(c, 156) = 0;
    INT(c, 160) = 0;
    INT(c, 164) = 0;
    INT(c, 168) = 0;
    INT(c, 172) = 0;
    INT(c, 176) = 0;
}

/* @draft 0x0bb40c us f_0bb40c
   WHAT IT DOES: Stores the pointer to a 20 float table in the car, keeps the largest of its
   values at +152, and stores that value (at least 2.0) at +160.
   Remaining difference: not yet compared. Guesses in the loop's operand order and the
   dead store to +160. */
extern "C" float f_0bb40c(void *cp, float *v)
{
    char *c = (char *)cp;
    INT(c, 152) = 0;
    float *p = v + 1;
    INT(c, 0) = (int)v;
    for (int k = 19; k >= 0; k--) {
        float x = *p;
        float m = FLT(c, 152);
        float r = x < m ? m : x;
        FLT(c, 152) = r;
        p++;
    }
    float m = FLT(c, 152);
    FLT(c, 160) = m / 15.0f;
    float r = m < 2.0f ? 2.0f : m;
    FLT(c, 160) = r;
    return r;
}

/* @draft 0x0b9b8c us f_0b9b8c
   WHAT IT DOES: When the car's state at +128 is not 1, sets four vectors in the physics record
   at +64 (each 16 bytes): each is a matrix row transformed by f_0a6d4c, with y and z negated,
   w set to 1.0, then scaled by f_0a5e1c to length 1000. Then calls f_0be874 on the list at
   D_245ec0 and returns the word at +1888; returns 0 otherwise.
   Remaining difference: retail sets r = 0 (move a1,zero) before the state test and keeps it in a1; GCC sinks it into the else path, so the size is 232 against 236. */
extern "C" int f_0b9b8c(void *cp)
{
    char *c = (char *)cp;
    int r = 0;
    if (INT(c, 128) != 1) {
        char *p = c + 5792;
        float one = 1.0f;
        for (int n = 0; n < 4; n++) {
            int o[3];
            f_0a6d4c(o, c + 6560, p + 64);
            INT(p, 136) = o[2];
            INT(p, 132) = o[1];
            INT(p, 128) = o[0];
            FLT(p, 132) = -FLT(p, 132);
            FLT(p, 136) = -FLT(p, 136);
            FLT(p, 140) = one;
            f_0a5e1c(p + 128, 1000.0f);
            p += 16;
        }
        f_0be874(D_245ec0, c);
        r = INT(c, 1888);
    }
    return r;
}

/* @draft 0x0bb154 us f_0bb154
   WHAT IT DOES: Builds a vector from the car's words at +144, +148 and +152 (the last two
   negated, the w component 1.0), normalises it to length 0.001 with f_0a5e1c and stores it in
   the physics record. Then stores the truncated word at +2144 into the record at +428, adds the
   word at +980 of the record to the float at +4 of the record, and writes the result of
   f_099b98 on the word at +2136 to +20 of the record.
   Remaining difference: retail reloads the word at +5796 after the three copies and keeps the
   truncated word in $f2; this build loads +5796 early and uses $f3 (18 of 51 words differ). */
extern "C" void f_0bb154(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    FloatBits v[4];
    v[0].i = INT(c, 144);
    v[1].i = INT(c, 148);
    v[2].i = INT(c, 152);
    v[1].f = -v[1].f;
    v[2].f = -v[2].f;
    v[3].f = 1.0f;
    f_0a5e1c(v, 0.001f);
    INT(ph, 0) = v[0].i;
    int k = (int)FLT(c, 2144);
    INT(ph, 12) = v[3].i;
    INT(ph, 4) = v[1].i;
    INT(ph, 8) = v[2].i;
    FLT(c, 5796) = FLT(c, 5796) + FLT(c, 6772);
    INT(ph, 428) = k;
    FloatBits t;
    t.f = FLT(c, 2136);
    f_099b98(&t.f);
    INT(c, 5812) = t.i;
}

/* @draft 0x0b9d28 us f_0b9d28
   WHAT IT DOES: When the second argument is zero, reads the word at +9912, runs f_0b9e0c
   when that word is 2 and the first argument is 0, then stores the first argument at +7948
   and +9912 and the old word at +9916. Otherwise stores the old word at +9916 and switches on
   the first argument: case 0 sets +9912 and +9916 to 2, case 2 runs f_0b9e0c and clears
   +9912 when the word is 2, case 4 sets +9912 to 1; then stores the word at +7948.
   Remaining difference: the register assignment (retail keeps the record pointer in s0, this build in s1); 40 of 55 words differ, size 212 against 220. */
extern "C" void f_0b9d28(void *cp, int a1, int a2)
{
    char *c = (char *)cp;
    if (a2 == 0) {
        int m = INT(c, 9912);
        if (a1 == 0 && m == 2) {
            f_0b9e0c(c);
            m = INT(c, 9912);
        }
        INT(c, 7948) = a1;
        INT(c, 9916) = m;
        INT(c, 9912) = a1;
        return;
    }
    int m = INT(c, 9912);
    INT(c, 9916) = m;
    switch (a1) {
    case 0:
        INT(c, 9912) = 2;
        INT(c, 9916) = 2;
        m = 2;
        break;
    case 2:
        if (m == 2) {
            f_0b9e0c(c);
            m = 0;
            INT(c, 9912) = 0;
        }
        break;
    case 4:
        INT(c, 9912) = 1;
        m = 1;
        break;
    default:
        break;
    }
    INT(c, 7948) = m;
}

/* @draft 0x0bb220 us f_0bb220
   WHAT IT DOES: Takes the spec record (the second argument). Stores 1.0 divided by its word at
   +12 at +9888 and stores the word at +12 at +1060 of the physics record. Then runs four
   records of 368 bytes from +8336 (each takes its +16 word into +36 and +40, adds the spec's
   +16 word to it, and sets +24 and +28 from the spec's +20 and +24 words scaled by 9.8 / 0.3
   and +32 to 10.0). Sets +1080 and +1072 to the physics record's +1060 times 9.8, calls
   f_0bb40c on +7816 with the spec's +28, stores the spec's +208 record at +8048, scales its
   +212 word by 1/3.6 when its +236 word is 0 (then sets that word to 1), and sets +9892 to
   1.0 divided by the word at +16 of that record.
   Remaining difference: size 292 against 304 and the prologue register order differs (70 of 76 words differ). */
extern "C" void f_0bb220(void *cp, void *spec)
{
    char *c = (char *)cp;
    char *s = (char *)spec;
    char *ph = c + 5792;
    float inv = 1.0f / FLT(s, 12);
    FLT(ph, 1060) = FLT(s, 12);
    *(void **)(ph + 1104) = spec;
    FLT(c, 9888) = inv;
    char *p = c + 8336;
    for (int i = 3; i >= 0; i--) {
        float v = FLT(p, 16);
        FLT(p, 36) = v;
        FLT(p, 40) = v;
        FLT(p, 16) = v + FLT(s, 16);
        FLT(p, 24) = FLT(s, 20) * 9.8f / 0.3f;
        FLT(p, 28) = FLT(s, 24) * 9.8f / 0.3f;
        FLT(p, 32) = 10.0f;
        p += 368;
    }
    float t = FLT(ph, 1060) * 9.8f;
    FLT(ph, 1080) = t;
    FLT(ph, 1072) = t;
    f_0bb40c(c + 7816, (float *)(s + 28));
    char *a = s + 208;
    *(void **)(c + 8048) = a;
    if (INT(a, 28) == 0) {
        INT(a, 28) = 1;
        FLT(a, 4) = FLT(a, 4) * 0.2777779996f;
    }
    INT(ph, 1272) = 0;
    char *q = *(char **)(c + 8048);
    FLT(c, 9892) = 1.0f / FLT(q, 16);
}
