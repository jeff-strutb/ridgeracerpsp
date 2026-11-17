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
void *f_0a5ea4(void *out, void *m, float f);
void *f_0a5dc8(void *d, void *b);
float f_0a65c4(void *v);
void f_0bc954(void *o, float a, float b, float c, float d, float e, float g, float h);
void f_0a6d4c(void *out, void *m, void *v);
void f_0be874(void *list, void *car);
float *f_099b98(float *a);
void f_0a5e1c(void *v, float len);

void f_0e2f9c(void *m, float a, float b, int i, float *o1, float *o2);
int f_0e2690(void *m, int i);
float f_0e2260(void *m, int i);
float f_09a9dc(float x, float z);
void f_0a6bf4(void *out, void *m, void *v);
float f_0c2bd0(float a, float b);
}

struct MapMgr {
    char m0[12240];
    char m12240[1];
};
extern MapMgr D_23c820;
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
};
extern CTable D_240740;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern "C" {
char *f_0368e8(CTable *t, const char *field, char *rec, int a, int i);
char *f_036984(CTable *t, char *key, int i, int *index, int count);
void *memcpy(void *d, const void *s, unsigned int n) throw();
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

/* A 16-byte vector whose words are copied through integer registers. */
struct V4w {
    FloatBits x, y, z, w;
};

extern void *D_2456d0;
extern "C" float sqrtf(float);
extern "C" {
void f_0a6c18(void *out, void *m, void *v);
void *f_09ff44(void *m);
void *f_0a082c(void *m, FloatBits angle, int i, int j);
}

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

/* An angle wrapped by f_099b98 when it is made from a value (zero by default). */
struct Angle {
    FloatBits v;
    Angle() { v.f = 0.0f; }
    Angle(float x)
    {
        v.f = x;
        f_099b98(&v.f);
    }
};

/* Three angles and a pad word, built from three values. */
struct Rot3 {
    Angle a[3];
    int w;
    Rot3(float x, float y, float z)
    {
        a[0] = Angle(x);
        a[1] = Angle(y);
        a[2] = Angle(z);
        w = 0;
    }
};

#define SHT(p, o) (*(short *)((char *)(p) + (o)))
#define USH(p, o) (*(unsigned short *)((char *)(p) + (o)))

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

/* @draft 0x0b6b48 us f_0b6b48
   WHAT IT DOES: Updates the car's course position: stores the truncated course coordinate at
   +2144 as the record's segment (+428), keeping the old one at +432. When the segment
   changed, adds the step (wrapped to half the course's segment count either way) times 102
   to the distance at +472, sets the moved flag at +436, and when the distance moved since +496
   is 100 or more adds it to the odometer at +492 (capped at 2000000000) and resyncs +496.
   Then stores the ground speed (the length of x and z of the velocity at +9952) at +496 of
   the global body record, the full speed at +1096 of the record and that speed times 3.6 at
   +1092, and two values scaled by 3.125 at +7816+96 and +7816+88.
   Remaining difference: retail forms the course areas address in two steps (D_23c820, then
   +12240) and loads +8 from it; combine folds this build's single-use address into the load
   (lw 12248), so everything after +0x48 is shifted by two words. */
extern "C" void f_0b6b48(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    char *q = c + 7816;
    char *g = (char *)D_2456d0;
    int old = INT(ph, 428);
    int k = (int)FLT(c, 2144);
    INT(ph, 432) = old;
    INT(ph, 428) = k;
    INT(ph, 436) = 0;
    if (old != k) {
        MapMgr *mp = &D_23c820;
        char *mm = mp->m12240;
        int n = INT(mm, 8);
        int d = k - old;
        int h = n >> 1;
        if (h < d)
            d -= n;
        if (d < -h)
            d += n;
        int nd = INT(ph, 472) + d * 102;
        int diff = nd - INT(ph, 496);
        if (diff < 0)
            diff = -diff;
        INT(ph, 436) = 1;
        INT(ph, 472) = nd;
        if (diff / 100 > 0) {
            INT(ph, 492) += diff;
            if (INT(ph, 492) > 1999999999)
                INT(ph, 492) = 2000000000;
            INT(ph, 496) = INT(ph, 472);
        }
    }
    V4w s = *(V4w *)(c + 9952);
    float h = sqrtf(s.x.f * s.x.f + s.z.f * s.z.f);
    FLT(g, 496) = h;
    float l = sqrtf(h * h + s.y.f * s.y.f);
    FLT(ph, 1096) = l;
    FLT(ph, 1092) = l * 3.6f;
    FLT(q, 96) = FLT(ph, 232) * 3.125f;
    FLT(q, 88) = FLT(ph, 1096) * 3.125f;
}

/* @implements 0x0b71c0 us f_0b71c0
   WHAT IT DOES: Sets up the car's orientation: copies the vector at +2192 into +6688 (y and z
   negated, w 1.0), transforms it by the matrix at +6560 into the global body record's +48,
   takes the heading angle (the negated angle of its z and -y) into +6624 and the pitch angle
   (of x against the length of y and z, which goes to +560 of the body record) into +6632,
   both wrapped by f_099b98. Then builds the matrix at +6416 from identity rotated by the two
   negated angles, and transforms the vectors at +6016 and +6048 by it into +864 and +880 of
   the physics record. The transform helpers are declared void here: retail's copies after
   them allocate v0 first, so the calls do not set v0. */
extern "C" void f_0b71c0(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    char *g = (char *)D_2456d0;
    V4w tmp;
    FloatBits t1;
    FloatBits t2;
    FloatBits t3;
    FloatBits t4;
    char *v = c + 6688;
    *(V4w *)(ph + 896) = *(V4w *)(c + 2192);
    float y = FLT(c, 6692);
    float z = FLT(c, 6696);
    FLT(v, 4) = -y;
    FLT(v, 8) = -z;
    FLT(v, 12) = 1.0f;
    f_0a6c18(&tmp, c + 6560, v);
    *(V4w *)(g + 48) = tmp;
    t1.f = -f_09a9dc(FLT(g, 56), -FLT(g, 52));
    f_099b98(&t1.f);
    *(FloatBits *)(c + 6624) = t1;
    float len = sqrtf(FLT(g, 52) * FLT(g, 52) + FLT(g, 56) * FLT(g, 56));
    FLT(g, 560) = len;
    t2.f = f_09a9dc(FLT(g, 48), len);
    f_099b98(&t2.f);
    *(FloatBits *)(c + 6632) = t2;
    char *m = c + 6416;
    f_09ff44(m);
    t3.f = -FLT(c, 6624);
    f_099b98(&t3.f);
    f_0a082c(m, t3, 1, 2);
    t4.f = -FLT(c, 6632);
    f_099b98(&t4.f);
    f_0a082c(m, t4, 0, 1);
    f_0a6bf4(&tmp, m, c + 6016);
    *(V4w *)(ph + 864) = tmp;
    f_0a6bf4(&tmp, m, c + 6048);
    *(V4w *)(ph + 880) = tmp;
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

/* @draft 0x0b6e44 us f_0b6e44
   WHAT IT DOES: Builds the body matrix at +576 of the physics record: the heading angle (the
   negated angle of the record's +904 and -+900) and the pitch angle (of +896 against the
   length of +900 and +904) rotate an identity matrix. Then combines the wheel contact
   halfwords of the sub-object at +8064 into +968 and +970 of the record, and sets +972 when
   the spec's flag bits ask for a contact that is present, clears +452 and +456, and splits
   the course coordinate at +2144 into its fraction (+448, scaled into +440, +476 and +484)
   and stores the lateral coordinate scaled at +444, the progress over a 60th at +1100 and
   the coordinate times 100 truncated at +480.
   Remaining difference: the angle and matrix half (+0x28 to +0x120) matches; global-alloc
   swaps s2/s3 between the car and the +8064 pointer, retail reloads the spec's flag word at
   the join after the first contact test where this build's gcse keeps it in a register, and
   the closing float block is scheduled differently (68 of 147 words, size 588 vs 584). */
extern "C" void f_0b6e44(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    char *sc = c + 8064;
    Rot3 r(0.0f, 0.0f, 0.0f);
    r.a[0] = Angle(-f_09a9dc(FLT(ph, 904), -FLT(ph, 900)));
    float len = sqrtf(FLT(ph, 900) * FLT(ph, 900) + FLT(ph, 904) * FLT(ph, 904));
    r.a[2] = Angle(f_09a9dc(FLT(ph, 896), len));
    char *m = ph + 576;
    f_09ff44(m);
    f_0a082c(m, r.a[2].v, 0, 1);
    f_0a082c(m, r.a[0].v, 1, 2);
    INT(ph, 972) = 0;
    char *sp = *(char **)(ph + 1104);
    SHT(ph, 968) = USH(sc, 128) & USH(sc, 496);
    SHT(ph, 970) = USH(sc, 864) & USH(sc, 1232);
    if (INT(sp, 4) & 1) {
        if (SHT(ph, 970) != 0)
            INT(ph, 972) = 1;
    }
    if (INT(sp, 4) & 2) {
        if (SHT(ph, 968) != 0)
            INT(ph, 972) = 1;
    }
    INT(ph, 452) = 0;
    INT(ph, 456) = 0;
    float x = FLT(c, 2144);
    float fr = x - (float)(int)x;
    INT(ph, 488) = INT(ph, 484);
    FLT(ph, 448) = fr;
    float f = fr * 1.024f;
    FLT(ph, 440) = f;
    FLT(ph, 476) = f;
    FLT(ph, 444) = FLT(c, 2148) * 1.024f;
    INT(ph, 484) = INT(ph, 472) + (int)(f * 100.0f);
    FLT(ph, 1100) = (FLT(c, 2144) - FLT(c, 2256)) / 0.016666668f;
    INT(ph, 480) = (int)(FLT(c, 2144) * 100.0f);
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

/* @draft 0x0b86ac us f_0b86ac
   WHAT IT DOES: The car's per frame bookkeeping: runs f_0bd880 and f_0b71c0, stores the
   truncated course coordinate at +2144 as the record's segment (+428, the old one at +432),
   adds the wrapped segment step times 102 to the distance at +472 when it changed and sets
   the moved flag at +436. Then stores the ground speed at +496 of the global body record,
   the full speed at +1096 of the record and that speed times 3.6 at +1092, the values scaled
   by 3.125 at +7816+96 and +7816+88, and passes the speeds to the sub-objects at +8064
   (f_0bc954) and +7996 (f_0bd234).
   Remaining difference: the same as f_0b6b48: retail forms the course areas address in two
   steps (D_23c820, then +12240) and loads +8 from it; this build folds it into lw 12248. */
extern "C" void f_0b86ac(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    char *q = c + 7816;
    char *sb = c + 7996;
    char *g = (char *)D_2456d0;
    f_0bd880(c);
    f_0b71c0(c);
    int old = INT(ph, 428);
    int k = (int)FLT(c, 2144);
    INT(ph, 432) = old;
    INT(ph, 428) = k;
    if (old != k) {
        MapMgr *mp = &D_23c820;
        char *mm = mp->m12240;
        int n = INT(mm, 8);
        int d = k - old;
        int h = n >> 1;
        if (h < d)
            d -= n;
        if (d < -h)
            d += n;
        INT(ph, 472) += d * 102;
    }
    if (INT(ph, 432) != INT(ph, 428))
        INT(ph, 436) = 1;
    else
        INT(ph, 436) = 0;
    V4w s = *(V4w *)(c + 9952);
    float h = sqrtf(s.x.f * s.x.f + s.z.f * s.z.f);
    FLT(g, 496) = h;
    float l = sqrtf(h * h + s.y.f * s.y.f);
    FLT(ph, 1096) = l;
    FLT(ph, 1092) = l * 3.6f;
    FLT(q, 96) = FLT(ph, 232) * 3.125f;
    FLT(q, 88) = FLT(ph, 1096) * 3.125f;
    f_0bc954(c + 8064, FLT(q, 96), FLT(q, 80), FLT(q, 20), FLT(ph, 1136), FLT(ph, 1096),
             FLT(ph, 1108), FLT(ph, 232));
    f_0bd234(sb, FLT(ph, 1096), FLT(ph, 1088));
}

/* The car's name in the database and its index. */
struct CarName {
    char *rec;
    int index;
};

/* An orientation quaternion. */
struct Quat {
    float v[4];
    Quat(float x, float y, float z, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
};

/* A position. */
struct Vec4 {
    float x, y, z, w;
    Vec4(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
};

extern "C" {
void *memset(void *d, int v, unsigned int n) throw();
void f_0ecc4c(void *c);
void f_0ed314(void *c, int type, int a, CarName n, int b, Quat q, Vec4 p);
void f_0bb350(void *p);
void f_0bd1dc(void *p);
void f_0bc894(void *p);
float f_0e26dc(void *m, float d);
void f_0b94b0(void *c);
void f_0b9e04(void *c, int v);
}

/* Zeroes a 16-byte vector field. */
static inline void zero4(char *v)
{
    FLT(v, 0) = 0.0f;
    FLT(v, 4) = 0.0f;
    FLT(v, 8) = 0.0f;
    FLT(v, 12) = 0.0f;
}

/* Zeroes a 16-byte block of words (int typed, so its stores stay ordered with the car's other
   word stores). */
static inline void zero4i(char *v)
{
    INT(v, 0) = 0;
    INT(v, 4) = 0;
    INT(v, 8) = 0;
    INT(v, 12) = 0;
}

/* @implements 0x0b8d24 us f_0b8d24
   WHAT IT DOES: Sets the race car up for a race: runs the car buffer's reset (f_0ecc4c) and
   set up (f_0ed314, with an identity orientation and a zero position), stores the type and the
   database name, clears the physics record, sets the not-type-bit-0 flag at +6208, resets
   the sub-objects at +7816, +7996 and +8064, clears the block at +7696, takes the road point
   of the start distance from the course areas into +9572 with the second float at +9576 and
   the last word at +9580, clears the course zone tables (the zone factor at +9668 is 1.0),
   reads the drift values from the database (f_0b94b0), clears the vectors and matrices from
   +9728 to +9840 and the step values, and sets the timing constants (1/60 and 60) and the
   1.0 scales from +9920 to +10040, clearing the rest up to +10112. */
extern "C" void f_0b8d24(void *cp, int type, int a, CarName n, int b, int last, float d, float f)
{
    char *c = (char *)cp;
    f_0ecc4c(c);
    CarName nm = n;
    f_0ed314(c, type, a, nm, b, Quat(0.0f, 0.0f, 0.0f, 1.0f), Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    INT(c, 80) = type;
    *(CarName *)(c + 92) = n;
    memset(c + 5792, 0, 1888);
    INT(c, 6208) = !(type & 1);
    f_0bb350(c + 7816);
    f_0bd1dc(c + 7996);
    f_0bc894(c + 8064);
    memset(c + 7696, 0, 80);
    INT(c, 7776) = 0;
    INT(c, 7780) = 0;
    INT(c, 7784) = 0;
    INT(c, 7788) = 0;
    INT(c, 7792) = 0;
    INT(c, 7796) = 0;
    INT(c, 7800) = 0;
    INT(c, 7804) = 0;
    INT(c, 7808) = 0;
    INT(c, 7812) = 0;
    MapMgr *mp = &D_23c820;
    FLT(c, 9572) = f_0e26dc(mp->m12240, d);
    FLT(c, 9576) = f;
    INT(c, 9580) = last;
    INT(c, 9584) = 0;
    INT(c, 9588) = 0;
    for (int i = 0; i < 4; i++) {
        INT(c, 9592 + i * 4) = 0;
        INT(c, 9608 + i * 4) = 0;
        INT(c, 9624 + i * 4) = 0;
    }
    INT(c, 9640) = 0;
    for (int i = 0; i < 2; i++) {
        INT(c, 9644 + i * 4) = 0;
        INT(c, 9652 + i * 4) = 0;
        INT(c, 9660 + i * 4) = 0;
    }
    FLT(c, 9668) = 1.0f;
    INT(c, 9672) = 0;
    for (int i = 0; i < 2; i++) {
        INT(c, 9676 + i * 4) = 0;
        INT(c, 9684 + i * 4) = 0;
    }
    INT(c, 9692) = 0;
    INT(c, 9696) = 0;
    INT(c, 9700) = 0;
    INT(c, 9704) = 0;
    INT(c, 9708) = 0;
    INT(c, 9712) = 0;
    INT(c, 9716) = 0;
    INT(c, 9720) = 0;
    INT(c, 9724) = 0;
    f_0b94b0(c);
    zero4i(c + 9728);
    INT(c, 9776) = 0;
    INT(c, 9744) = 0;
    INT(c, 9748) = 0;
    INT(c, 9752) = 0;
    INT(c, 9756) = 0;
    INT(c, 9760) = 0;
    INT(c, 9764) = 0;
    INT(c, 9768) = 0;
    INT(c, 9772) = 0;
    f_09ff44(c + 9792);
    f_09ff44(c + 9840);
    INT(c, 9888) = 0;
    INT(c, 9892) = 0;
    INT(c, 9896) = 0;
    INT(c, 9900) = 0;
    f_0b9e04(c, 0);
    INT(c, 9908) = 0;
    INT(c, 9912) = 0;
    INT(c, 9916) = 0;
    FLT(c, 9920) = 1.0f;
    FLT(c, 9924) = 1.0f;
    FLT(c, 9928) = 1.0f;
    FLT(c, 9932) = 1.0f;
    FLT(c, 9936) = 0.016666668f;
    FLT(c, 9940) = 59.999996f;
    FLT(c, 9944) = 0.016666668f;
    FLT(c, 9948) = 0.0f;
    zero4(c + 9952);
    zero4(c + 9968);
    zero4(c + 9984);
    zero4(c + 10000);
    FLT(c, 10016) = 1.0f;
    FLT(c, 10020) = 1.0f;
    FLT(c, 10024) = 1.0f;
    FLT(c, 10028) = 1.0f;
    FLT(c, 10032) = 1.0f;
    FLT(c, 10036) = 1.0f;
    FLT(c, 10040) = 1.0f;
    INT(c, 10044) = 0;
    INT(c, 10048) = 0;
    INT(c, 10052) = 0;
    INT(c, 10056) = 0;
    INT(c, 10060) = 0;
    INT(c, 10064) = 0;
    INT(c, 10068) = 0;
    INT(c, 10072) = 0;
    INT(c, 10076) = 0;
    INT(c, 10080) = 0;
    INT(c, 10084) = 0;
    INT(c, 10088) = 0;
    INT(c, 10092) = 0;
    INT(c, 10096) = 0;
    INT(c, 10100) = 0;
    INT(c, 10104) = 0;
    INT(c, 10108) = 0;
    INT(c, 10112) = 0;
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

/* @implements 0x0b99d0 us f_0b99d0
   WHAT IT DOES: Moves the car: adds the velocity at +1936 to the position at +144, then adds
   the velocity scaled by 0.001 (y and z negated, w 1.0) to the physics record's position.
   Unless the car's state at +80 is 1 with a mode word at +2108 other than 0 or 3, it also
   adds the vector at +1920 scaled by 0.06 (y and z negated) to the record's +192. Then takes
   the length of the +1920 vector scaled by 0.06, signed by the float at +1960, and stores it
   at +10112 when its size is larger than the size of the value there. */
extern "C" void f_0b99d0(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    V4w v;
    V4w t;
    f_0a5dc8(c + 144, c + 1936);
    f_0a5ea4(&v, c + 1936, 0.001f);
    v.y.f = -v.y.f;
    v.z.f = -v.z.f;
    v.w.f = 1.0f;
    f_0a5dc8(ph, &v);
    if (INT(c, 80) != 1 || INT(c, 2108) == 0 || INT(c, 2108) == 3) {
        f_0a5ea4(&t, c + 1920, 0.06f);
        v.y.i = t.y.i;
        v.z.i = t.z.i;
        v.x.i = t.x.i;
        v.y.f = -v.y.f;
        v.z.f = -v.z.f;
        v.w.f = 1.0f;
        f_0a5dc8(ph + 192, &v);
    }
    f_0a5ea4(&t, c + 1920, 0.06f);
    v = t;
    float f1 = f_0a65c4(&v);
    if (FLT(c, 1960) < 0.0f)
        f1 = -f1;
    float f0 = FLT(c, 10112);
    if (f0 < 0.0f)
        f0 = -f0;
    float f3 = f1 < 0.0f ? -f1 : f1;
    if (f0 < f3)
        FLT(c, 10112) = f1;
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


/* @implements 0x0b9098 us f_0b9098
   WHAT IT DOES: Copies the first three entries of each row of a 4x4 matrix and sets the last
   column to zero, except the bottom right entry which is 1.0. */
extern "C" void f_0b9098(float *dst, float *src)
{
    for (int i = 0; i < 4; i++)
        for (int k = 0; k < 3; k++)
            dst[i * 4 + k] = src[i * 4 + k];
    FLT(dst, 28) = 0.0f;
    FLT(dst, 44) = 0.0f;
    FLT(dst, 60) = 1.0f;
    FLT(dst, 12) = 0.0f;
}

/* @implements 0x0b9c78 us f_0b9c78
   WHAT IT DOES: Takes a vector from the car's field at +1856 scaled by 0.06 and its length
   along the car's heading, and stores the sign-corrected value at +10112 when it is larger. */
extern "C" void f_0b9c78(void *cp)
{
    char *c = (char *)cp;
    struct V4 {
        float x, y, z, w;
    };
    V4 v;
    V4 out;
    f_0a5ea4(&out, c + 1856, 0.06f);
    v = out;
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

/* @implements 0x0bb40c us f_0bb40c
   WHAT IT DOES: Stores the pointer to a 20 float table in the car, keeps the largest of its
   values at +152, stores that value over 15 at +160 and then overwrites it with the value
   capped at 2.0, which it returns. */
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
    float r = m < 2.0f ? m : 2.0f;
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

/* @implements 0x0bb154 us f_0bb154
   WHAT IT DOES: Builds a vector from the car's words at +144, +148 and +152 (the last two
   negated, the w component 1.0), normalises it to length 0.001 with f_0a5e1c and stores it in
   the physics record. Then stores the truncated word at +2144 into the record at +428, adds the
   word at +980 of the record to the float at +4 of the record, and writes the result of
   f_099b98 on the word at +2136 to +20 of the record. The record words are copied as
   the float/int union, so the reload of +5796 (the record's second word) stays after them. */
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
    ((FloatBits *)ph)[0] = v[0];
    int k = (int)FLT(c, 2144);
    ((FloatBits *)ph)[3] = v[3];
    ((FloatBits *)ph)[1] = v[1];
    ((FloatBits *)ph)[2] = v[2];
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

/* @draft 0x0b708c us f_0b708c
   WHAT IT DOES: Builds the heading vector from the physics record (y and z negated, w 1.0),
   scales it to length 1000, asks the course manager for the road segment, then steps the
   segment index forward until it matches the stored one, and stores the resulting distance
   (102 per step, less the manager's word at +8 when the car's word at +2212 is negative) at
   +496 and +472 of the record before calling f_0b6e44.
   Remaining difference: 23 of 77 words; retail schedules move a0,sp after the c[5792] load (here hoisted), the 1000.0 constant load and the D_23c820 base differ in position, and trunc.w.s uses f0 not f1. */
extern "C" void f_0b708c(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    MapMgr *mp = &D_23c820;
    char *mm = mp->m12240;
    int dist = 0;
    int j = 0;
    FloatBits v[4];
    float o[2];
    v[2].i = INT(ph, 8);
    v[1].i = INT(ph, 4);
    v[2].f = -v[2].f;
    v[1].f = -v[1].f;
    v[0].i = INT(c, 5792);
    v[3].f = 1.0f;
    f_0a5e1c(v, 1000.0f);
    f_0e2f9c(mm, v[0].f, v[2].f, INT(ph, 428), &o[0], &o[1]);
    int idx = f_0e2690(mm, (int)o[1]);
    INT(ph, 428) = idx;
    INT(ph, 432) = idx;
    for (;;) {
        dist += 102;
        if (INT(ph, 428) == j)
            break;
        j++;
        j = f_0e2690(mm, j);
    }
    if (INT(c, 2212) < 0)
        dist -= INT(mm, 8) * 102;
    INT(ph, 472) = dist;
    INT(ph, 496) = dist;
    INT(ph, 492) = 0;
    f_0b6e44(c);
}

/* @draft 0x0b8884 us f_0b8884
   WHAT IT DOES: Finds the car's heading angles: the angle of the velocity and of the body's
   direction in the physics record (+960, +964), then, against the road direction at the
   course position, sets the two flags at +468 and +464 when the car points more than a quarter
   turn away from the road, and stores the lateral offset term at +1024.
   Remaining difference: retail copies the first abs() result into a second register ($f2) before the negate; here it is negated in place (45 of 89 words, size 352 vs 356). */
extern "C" void f_0b8884(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    FloatBits t[4];
    FloatBits u[4];
    FLT(ph, 960) = f_09a9dc(FLT(c, 6656), FLT(c, 6664));
    f_0a6bf4(u, c + 6416, c + 5984);
    t[0].i = u[0].i;
    t[2].i = u[2].i;
    t[1].i = u[1].i;
    t[3].i = u[3].i;
    FLT(ph, 964) = f_09a9dc(t[2].f, t[0].f);
    MapMgr *mp = &D_23c820;
    float road = f_0e2260(mp->m12240, (int)FLT(c, 2144));
    float a = f_0c2bd0(f_09a9dc(-t[0].f, t[2].f), road);
    float b = a < 0.0f ? -a : a;
    if (1.5707963705f < b)
        *(short *)(ph + 468) = 1;
    else
        *(short *)(ph + 468) = 0;
    float d = f_0c2bd0(FLT(ph, 20), road);
    if (d < 0.0f)
        d = -d;
    if (1.5707963705f < d)
        INT(ph, 464) = 1;
    else
        INT(ph, 464) = 0;
    FLT(ph, 1024) = -FLT(c, 2140) * 0.0010000000474974513f - FLT(ph, 4);
}

extern "C" {
unsigned int f_0c2a60(void);
float f_0e3b3c(void *m, float a, float b);
}

/* @implements 0x0b89e8 us f_0b89e8
   WHAT IT DOES: The course zone checks. While no zone is held (+1036 of the record is 0) the
   grip factor at +9900 is 1.0, and at 27.78 or more with the spin flag (+468) clear the car's
   course and lateral coordinates are tested against the zone table at +9592: an entry the car
   is inside holds the zone (its index at +9588, the segment at +1040, its factor at +9900).
   A held zone is released when the car is more than 10.0 from its segment. Then the factor at
   +9668 is 1.5 or the value of the table at +9644 the car is inside, and unless the word at
   +9672 is 255 (which sets +2112 to 1) the table at +9676 decides a hit: the countdown at
   +9692 is started from a random value (negative on a hit), counted towards zero, and the
   flag at +2112 is toggled when it runs out. */
extern "C" void f_0b89e8(void *cp)
{
    char *c = (char *)cp;
    char *ph = c + 5792;
    MapMgr *mp = &D_23c820;
    char *areas = mp->m12240;
    if (SHT(ph, 1036) == 0) {
        FLT(c, 9900) = 1.0f;
        if (FLT(ph, 1096) >= 27.78f && SHT(ph, 468) == 0) {
            int a = (int)FLT(c, 2144);
            int b = (int)FLT(c, 2256);
            for (int i = 0; i < INT(c, 9584); i++) {
                if (a < INT(c, 9592 + i * 4))
                    break;
                if (b < INT(c, 9608 + i * 4)) {
                    INT(c, 9588) = i;
                    SHT(ph, 1036) = 1;
                    INT(ph, 1040) = INT(ph, 428);
                    FLT(c, 9900) = FLT(c, 9624 + i * 4);
                }
            }
        }
    }
    if (SHT(ph, 1036) == 1) {
        int seg = f_0e2690(areas, INT(ph, 1040));
        float d = f_0e3b3c(areas, FLT(c, 2144), (float)seg);
        if (d < 0.0f)
            d = -d;
        if (10.0f < d)
            SHT(ph, 1036) = 0;
    }
    FLT(c, 9668) = 1.5f;
    int x = (int)FLT(c, 2144);
    int z = (int)FLT(c, 2256);
    int n = INT(c, 9640);
    for (int i = 0; i < n; i++) {
        if (x < INT(c, 9644 + i * 4))
            break;
        if (z < INT(c, 9652 + i * 4))
            FLT(c, 9668) = FLT(c, 9660 + i * 4);
    }
    if (INT(c, 9672) == 255) {
        INT(c, 2112) = 1;
        return;
    }
    int hit = 0;
    int flip = 0;
    int hx = (int)FLT(c, 2144);
    int hz = (int)FLT(c, 2256);
    for (int i = 0; i < INT(c, 9672); i++) {
        if (hx < INT(c, 9676 + i * 4))
            break;
        if (hz < INT(c, 9684 + i * 4))
            hit = 1;
    }
    int k = INT(c, 9692);
    if (k == 0) {
        if (hit == 0) {
            if (INT(c, 2112) == 1) {
                k = f_0c2a60() % 10;
                k = INT(c, 9692) = k + 1;
            }
        } else if (INT(c, 2112) == 0) {
            k = f_0c2a60() % 10;
            k = INT(c, 9692) = ~k;
        }
    }
    if (k != 0) {
        if (k > 0) {
            if (hit == 1) {
                INT(c, 9692) = 0;
            } else {
                INT(c, 9692) = k - 1;
                if (k - 1 <= 0) {
                    flip = 1;
                    INT(c, 9692) = 0;
                }
            }
        } else {
            if (hit == 0) {
                INT(c, 9692) = 0;
            } else {
                INT(c, 9692) = k + 1;
                if (k + 1 >= 0) {
                    INT(c, 9692) = 0;
                    flip = 1;
                }
            }
        }
    }
    if (flip == 1)
        INT(c, 2112) = 1 - INT(c, 2112);
}

/* @draft 0x0b94b0 us f_0b94b0
   WHAT IT DOES: Reads the car's drift and nitro tuning values from the game database: when the
   car has a record key (+92) it finds that record, then copies the "DriftType", "Grade",
   "NitroFreq", "NitroTrigger" and "CorneringLossRatio" fields into +9696, +9700, +9704, +9708
   and +9724 of the car.
   Remaining difference: retail keeps the record pointer in a stack slot stored once (sw v0,0(sp)) with the no-key arm out of line and a different saved register order; this build is 416 bytes against 404 (50 of 104 words). */
extern "C" void f_0b94b0(void *cp)
{
    char *c = (char *)cp;
    char *volatile rec;
    if (INT(c, 92) != 0)
        rec = f_036984(&D_240740, *(char **)(c + 92), 0, D_240740.index, D_240740.count);
    else
        rec = 0;
    int n = D_1a211c[1];
    memcpy(D_24063c, f_0368e8(&D_240740, "DriftType", rec, 0, 0), n);
    INT(c, 9696) = D_24063c[0];
    memcpy(D_24063c, f_0368e8(&D_240740, "Grade", rec, 0, 0), n);
    INT(c, 9700) = D_24063c[0];
    memcpy(D_24063c, f_0368e8(&D_240740, "NitroFreq", rec, 0, 0), n);
    INT(c, 9704) = D_24063c[0];
    memcpy(D_24063c, f_0368e8(&D_240740, "NitroTrigger", rec, 0, 0), n);
    INT(c, 9708) = D_24063c[0];
    memcpy(D_24063c, f_0368e8(&D_240740, "CorneringLossRatio", rec, 0, 0), D_1a211c[4]);
    FLT(c, 9724) = *(float *)D_24063c;
}

/* Three angles and an order word (a wheel's Euler angles). */
struct Euler {
    Angle a[3];
    int w;
    void Set(Angle x, Angle y, Angle z)
    {
        a[0] = x;
        a[1] = y;
        a[2] = z;
        w = 0;
    }
};

/* A float vector. */
struct V4f {
    float x, y, z, w;
};

/* A 4x4 matrix and the 3x4 rotation part. */
struct M44 {
    float m[4][4];
};
struct M34 {
    float m[3][4];
};

extern "C" void f_0a28c4(void *m, float s);
extern "C" void f_09fd1c(void *m, const void *q);

/* A point moved by the car's body offset at +9728, w set to 1.0. */
static inline void BodyOffset(V4f &r, char *c, const V4f &p)
{
    r.x = p.x + FLT(c, 9728);
    r.y = p.y + FLT(c, 9732);
    r.z = p.z + FLT(c, 9736);
    r.w = 1.0f;
}

/* @draft 0x0b9644 us f_0b9644
   WHAT IT DOES: Places the body and the wheels: each wheel offset's height (+260 + 16 i) is
   the front (+9744) or rear (+9748) ride height plus the wheel's own (+9752 + 4 i), also kept
   at +452 + 16 i. Sets the front and rear wheel angles at +384 and +400 (steering from the
   records at +8112 and +8480, spin +9768) and the single angles at +416, +432, +516 and +532.
   Builds the body matrix from the orientation quaternion (+208) and the offset position,
   keeps it at +1152 (4x3) and +576 (4x4), then moves each wheel to its offset position (less
   the ride height) transformed by the body matrix, keeping the previous positions at +2000.
   Remaining difference: sched2 order only (12 of 225 words, same size and registers): the
   body offset add loads p.y/p.x before +9728/+9732 in retail (here after), and in the loop
   the +256 load and the x/z stores of the offset vector are one slot apart. */
extern "C" void f_0b9644(void *cp)
{
    char *c = (char *)cp;
    M44 mat;
    V4f v;
    M34 t;
    Euler *fr = (Euler *)(c + 384);
    Euler *rr = (Euler *)(c + 400);
    FLT(c, 260) = FLT(c, 9744) + FLT(c, 9752);
    FLT(c, 276) = FLT(c, 9744) + FLT(c, 9756);
    FLT(c, 292) = FLT(c, 9748) + FLT(c, 9760);
    FLT(c, 308) = FLT(c, 9748) + FLT(c, 9764);
    FLT(c, 452) = FLT(c, 260);
    FLT(c, 468) = FLT(c, 276);
    FLT(c, 484) = FLT(c, 292);
    FLT(c, 500) = FLT(c, 308);
    Angle sf(-FLT(c, 8112));
    fr->Set(sf, Angle(FLT(c, 9768)), Angle(0.0f));
    Angle sr(-FLT(c, 8480));
    rr->Set(sr, Angle(FLT(c, 9768)), Angle(0.0f));
    *(Angle *)(c + 416) = Angle(-FLT(c, 8848));
    *(Angle *)(c + 432) = Angle(-FLT(c, 9216));
    *(Angle *)(c + 516) = Angle(FLT(c, 9768));
    *(Angle *)(c + 532) = Angle(FLT(c, 9768));
    f_0a28c4(&mat, 1.0f);
    BodyOffset(v, c, *(V4f *)(c + 144));
    *(V4f *)mat.m[3] = v;
    f_09fd1c(&t, c + 208);
    *(M34 *)mat.m = t;
    *(M44 *)(c + 1152) = mat;
    f_0b9098((float *)(c + 576), (float *)&mat);
#define wp ((V4f *)(c + 320))
    for (int i = 0; i < 4; i++) {
        ((V4f *)(c + 2000))[i] = wp[i];
        BodyOffset(v, c, ((V4f *)(c + 256))[i]);
        wp[i] = v;
        wp[i].y = wp[i].y - (i < 2 ? FLT(c, 9744) : FLT(c, 9748));
        f_0a6d4c(&v, &mat, &wp[i]);
        wp[i] = v;
    }
#undef wp
}
