/* The player's car (retail 0x0bfae4 to 0x0c078c, "RRP::CRidgeMycar"). It derives from the
   race car (constructed and destroyed in another object file) and adds the player's own per
   frame steps: the boost gauge state machine, the frame time scaling, the tilt and spin of
   the car's body record, the controller's force feedback bits and the camera vectors. */

#include <string.h>

struct Vec4 {
    float x, y, z, w;
    void Clear() { x = w = z = y = 0.0f; }
};

union Angle {
    float a;
};

struct Vec3 {
    float x, y, z;
};

extern "C" {
void f_0b6754(void *car);
void f_0b6904(void *car);
void f_0a5e1c(Vec4 *v, float len);
void f_099b98(float *a);
void f_0a6d4c(Vec4 *out, void *m, Vec4 *v);
void f_0be874(void *list, void *car);
void f_0b1ccc(void *a, void *b, Vec3 *out);
void f_0fe8a4(void *car);
void f_0bcc4c(void *o, Vec4 v, float f);
void f_0bdbdc(void *car);
void f_0b73b4(void *car, int a);
void f_0b7ff4(void *car);
void f_0bb220(void *car, void *spec);
void f_0a6c18(Vec4 *out, void *m, Vec4 *v);
float f_09a9dc(float x, float z);
void f_09ff44(void *m);
void f_0a082c(void *m, Angle a, int axis, int b);
void f_0a6bf4(Vec4 *out, void *m, Vec4 *v);
float f_09a154(float a);
}

extern char D_245ec0[];

/* The race car base (another object file). */
struct CRidgeCar {
    CRidgeCar() { f_0b6754(this); }
    ~CRidgeCar() { f_0b6904(this); }
};

/* The car's spec record. */
struct Spec {
    char p0[4];
    float m4;
    float m8;
    float m12;
    char p16[12];
    char m28[4];
};

/* The input record (m10116). */
struct Pad {
    char p0[3108];
    int m3108;
    int m3112;
    int m3116;
    int m3120;
    int m3124;
};

struct SpecRef {
    int m0;
    char p4[44];
    Spec *m48;
    void Set(Spec *s) { m48 = s; }
};

/* The car's physics record (+5792, 1888 bytes). */
struct Phys {
    float x, y, z;         /* 0 */
    char p12[8];
    float m20;             /* 20 */
    char p24[40];
    Vec4 m64[4];           /* 64 */
    Vec4 m128[4];          /* 128 */
    Vec4 m192;             /* 192 */
    char p208[16];
    Vec4 m224;             /* 224 */
    char p240[144];
    Vec4 m384;             /* 384 */
    char p400[224];
    char m624[144];        /* 624 */
    char m768[212];        /* 768: the body matrix */
    float m980;            /* 980 */
    char p984[76];
    float m1060;           /* 1060 */
    char p1064[32];
    float m1096;           /* 1096 */
    char p1100[20];
    Vec4 m1120;            /* 1120 */
    float m1136;           /* 1136 */
    int m1140;             /* 1140 */
    char p1144[156];
    SpecRef m1300;         /* 1300 */
    char p1352[536];
};

/* The global body record (D_2456d0). */
struct Body {
    char p0[64];
    Vec4 m64;
    char p80[224];
    char m304[200];
    float m504;
    float m508;
    float m512;
    float m516;
    float m520;
};
extern Body *D_2456d0;

struct Bits {
    unsigned b0 : 8;
    unsigned b8 : 3;
    unsigned b11 : 3;
    unsigned b14 : 1;
    unsigned b15 : 1;
    unsigned b16 : 1;
    unsigned rest : 15;
};

namespace RRP {

class CRidgeMycar : public CRidgeCar {
public:
    CRidgeMycar();
    virtual ~CRidgeMycar();
    virtual void f_0bfc04();
    virtual void f_0bfc0c();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void f_0bfc40();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual int f_0bfcd4();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();

    void f_0bfc48();
    int f_0bfdd0(int v, int lo, int hi);
    void f_0bfe38();
    void f_0bff90();
    void f_0bff98();
    void f_0c01e8();
    void f_0c0270();
    void f_0c063c();
    void f_0c06d4();
    void f_0c071c(Spec *s);

    char p4[140];
    char m144[1620];       /* 144 */
    Vec3 m1764;            /* 1764 */
    char p1776[112];
    int m1888;             /* 1888 */
    char p1892[236];
    float m2128;           /* 2128 */
    float m2132;
    float m2136;
    char p2140[616];
    char m2756[3036];      /* 2756 */
    Phys phys;             /* 5792 */
    char p7680[8];
    Spec *m7688;           /* 7688 */
    Bits m7692;            /* 7692 */
    char p7696[84];
    float m7780;           /* 7780 */
    char p7784[4];
    float m7788;           /* 7788 */
    char p7792[48];
    float m7840;           /* 7840 */
    char p7844[112];
    float m7956;           /* 7956 */
    char p7960[104];
    char m8064[1848];      /* 8064 */
    int m9912;             /* 9912 */
    char p9916[4];
    float m9920;           /* 9920 */
    char p9924[4];
    float m9928;           /* 9928 */
    float m9932;
    float m9936;
    float m9940;
    float m9944;
    char p9948[88];
    float m10036;          /* 10036 */
    float m10040;
    int m10044;            /* boost state */
    float m10048;
    int m10052;
    float m10056;
    float m10060;
    float m10064;
    float m10068;
    char p10072[4];
    float m10076;
    char p10080[4];
    float m10084;
    char p10088[28];
    Pad *m10116;           /* 10116 */
    char p10120[8];
    Vec4 m10128;           /* 10128 */
};

}

using namespace RRP;

/* @implements 0x0bfae4 us _ZN3RRP11CRidgeMycarC2Ev
   WHAT IT DOES: Builds the race car, then clears the input record pointer and the extra
   vector (base object constructor). */
/* @implements 0x0bfb30 us _ZN3RRP11CRidgeMycarC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CRidgeMycar::CRidgeMycar()
{
    m10116 = 0;
    m10128.Clear();
}

/* @implements 0x0bfb7c us _ZN3RRP11CRidgeMycarD2Ev
   WHAT IT DOES: Destroys the race car (base object destructor). */
/* @implements 0x0bfba4 us _ZN3RRP11CRidgeMycarD1Ev
   WHAT IT DOES: The same (complete object destructor). */
/* @implements 0x0bfbcc us _ZN3RRP11CRidgeMycarD0Ev
   WHAT IT DOES: The same, then frees the car (deleting destructor). */
CRidgeMycar::~CRidgeMycar()
{
}

/* @implements 0x0bfc04 us f_0bfc04
   WHAT IT DOES: Nothing for the player's car. */
void CRidgeMycar::f_0bfc04()
{
}

/* @implements 0x0bfc0c us f_0bfc0c
   WHAT IT DOES: The per frame move: runs the player's steps, then the car's virtual step at
   slot 20. */
void CRidgeMycar::f_0bfc0c()
{
    f_0c06d4();
    v20();
}

/* @implements 0x0bfc40 us f_0bfc40
   WHAT IT DOES: Nothing for the player's car. */
void CRidgeMycar::f_0bfc40()
{
}

/* @draft 0x0bfc48 us f_0bfc48
   WHAT IT DOES: Builds the car's direction vector from its position (y relative to the
   ground height), scales it to length 1000, normalizes its angle and stores both.
   DIFFERS: the three reloads before the final stores: retail loads z, the angle, then x;
   this build loads z, x, then the angle. Every store order was tried. */
void CRidgeMycar::f_0bfc48()
{
    Vec4 v;
    v.x = phys.x;
    v.y = -(phys.y - phys.m980);
    v.z = -phys.z;
    v.w = 1.0f;
    f_0a5e1c(&v, 1000.0f);
    float a = phys.m20;
    f_099b98(&a);
    m2136 = a;
    m2132 = v.z;
    m2128 = v.x;
}

/* @implements 0x0bfcd4 us f_0bfcd4
   WHAT IT DOES: Transforms the four wheel points by the body matrix (y and z flipped, w 1,
   scaled to length 1000), registers the car with the draw list, and reads back its
   position vector; returns the draw flag. */
int CRidgeMycar::f_0bfcd4()
{
    Phys *p = &phys;
    int i;
    Vec4 t;
    for (i = 0; i < 4; i++) {
        f_0a6d4c(&t, p->m768, &p->m64[i]);
        *(Vec3 *)&p->m128[i] = *(Vec3 *)&t;
        p->m128[i].w = 1.0f;
        p->m128[i].y = -p->m128[i].y;
        p->m128[i].z = -p->m128[i].z;
        f_0a5e1c(&p->m128[i], 1000.0f);
    }
    f_0be874(D_245ec0, this);
    f_0b1ccc(m2756, m144, (Vec3 *)&t);
    m1764.x = t.x;
    m1764.y = t.y;
    m1764.z = t.z;
    return m1888;
}

/* @implements 0x0bfdd0 us f_0bfdd0
   WHAT IT DOES: Maps a signed input between lo and hi (mirrored for negative input) onto
   0..127. */
int CRidgeMycar::f_0bfdd0(int v, int lo, int hi)
{
    if (v >= 0) {
        if (v < lo)
            v = lo;
        if (v > hi)
            v = hi;
        v -= lo;
        if (v < 0)
            v = lo;
    } else {
        if (v > -lo)
            v = -lo;
        if (v < -hi)
            v = -hi;
        v += lo;
        if (v > 0)
            v = -lo;
    }
    if (lo < hi)
        v = v * 127 / (hi - lo);
    return v;
}

/* @draft 0x0bfe38 us f_0bfe38
   WHAT IT DOES: Packs the force feedback bits from the input record: strength, two levels,
   direction flags and (except in mode 2) the vibration bit.
   DIFFERS: retail keeps the first level unshifted in s2 across the third call (move in the
   call slot, sra after it, +1 instruction) and computes d == -1 before d == 1; this build
   shifts in the call slot. */
void CRidgeMycar::f_0bfe38()
{
    Pad *pad = m10116;
    int a = pad->m3108;
    int b = pad->m3112;
    int d = pad->m3120;
    int e = pad->m3124;
    int s = f_0bfdd0(pad->m3116, 64, 200);
    int l1 = f_0bfdd0(a, 0, 100);
    int l2 = f_0bfdd0(b, 0, 100);
    l1 >>= 4;
    if (l1)
        l1 = 7;
    l2 >>= 4;
    if (l2)
        l2 = 7;
    m7692.b0 = s;
    m7692.b8 = l1;
    m7692.b11 = l2;
    m7692.b14 = d == 1;
    m7692.b15 = d == -1;
    if (m9912 == 2)
        m7692.b16 = 0;
    else
        m7692.b16 = e;
}

/* @implements 0x0bff90 us f_0bff90
   WHAT IT DOES: Nothing. */
void CRidgeMycar::f_0bff90()
{
}

/* @draft 0x0bff98 us f_0bff98
   WHAT IT DOES: The boost gauge state machine (0 idle, 1 rising, 2 holding, 3 falling) and
   the resulting speed factor, capped at 2.
   DIFFERS: three spots: retail multiplies the falling factor straight into the result
   register (f4), stores the zero floor of the hold time from f4 (this build: sw zero), and in
   state 1 stores the speed before loading the new state. */
void CRidgeMycar::f_0bff98()
{
    Phys *p = &phys;
    float add = 0.0f;
    int done = 0;

    if (m10044 == 1) {
        m10036 += m10076;
        if (m7788 < m10036) {
            m10036 = m7788;
            m10044 = 2;
        }
        goto hold;
    } else if (m10044 < 2) {
        if (m10044 == 0) {
            if (m7692.b16) {
                if (100.0f <= m10048) {
                    m10036 = m7780;
                    m10048 -= 100.0f;
                    m10044 = 1;
                    m10056 = 100.0f;
                }
            } else {
                m10036 = 1.0f;
            }
        }
    } else if (m10044 == 2) {
    hold:
        m10056 -= m10060;
        if (m10056 <= add) {
            done = 1;
            m10056 = add;
        }
    } else if (m10044 == 3) {
        m10036 += m10064;
        if (m10036 < 1.0f) {
            m10036 = 1.0f;
            m10044 = 0;
        }
        if (m7692.b16 && 100.0f <= m10048) {
            m10048 -= 100.0f;
            m10044 = 1;
            m10056 = 100.0f;
        }
    }
    if (m10044 == 1 || m10044 == 2) {
        if (p->m1096 <= 55.6f)
            add = (55.6f - p->m1096) / 55.6f;
    }
    if (m10044 == 3)
        add = (m10036 - 1.0f) * m10084 * m10068;
    if (done == 1) {
        m10064 = (1.0f - m10036) * 0.008333f;
        m10052 = (m10052 + 1) % 3;
        m10044 = 3;
        m10068 = add;
    }
    m10040 = m10036 + add;
    m10040 = m10040 < 2.0f ? m10040 : 2.0f;
}

/* @implements 0x0c01e8 us f_0c01e8
   WHAT IT DOES: Runs the boost step, then sets the frame time scale (the boost factor times
   the base scale, capped at 3) and its reciprocal and per-second forms. */
void CRidgeMycar::f_0c01e8()
{
    f_0bff98();
    m9928 = m9920 * m10040;
    float s = m9928 < 3.0f ? m9928 : 3.0f;
    m7956 = s;
    m9928 = s;
    m9932 = 1.0f / s;
    m9936 = s * 0.016666668f;
    m9940 = 1.0f / m9936;
    m9944 = m9932 * 0.016666668f;
}

/* @draft 0x0c0270 us f_0c0270
   WHAT IT DOES: Updates the global body record from the car: the heading of the velocity
   seen in the body frame gives the side slip angle (folded into 0..pi/2); below the spec's
   slip limit the lateral force grows with it, above it is the full grip; the force is scaled
   by the frame time, the slip direction and (below 10) the speed. The car's lateral force
   vector is then rotated into the slip frame, capped by the grip, softened past the spec's
   second limit, and rotated back into the world.
   DIFFERS: only the opening stores: retail stores the zero x of the up vector first and loads
   the spec pointer before the stores; this build stores x after y, z and w and loads the spec
   pointer later. Store chains, separate stores and declaration orders do not change it. */
void CRidgeMycar::f_0c0270()
{
    Phys *p = &phys;
    Body *b = D_2456d0;
    Spec *spec = p->m1300.m48;
    Vec4 *up = &b->m64;
    Vec4 t;

    b->m64.x = up->w = up->z = up->y = 0.0f;
    p->m1120.Clear();
    f_0a6c18(&t, p->m768, &p->m192);
    p->m224 = t;
    float r = -f_09a9dc(phys.m224.x, phys.m224.z);
    p->m1136 = r;
    b->m504 = r;
    if (r < 0.0f)
        b->m504 = -r;
    if (1.5707964f <= b->m504)
        b->m504 = 3.1415927f - b->m504;
    b->m520 = b->m504;
    float lim = spec->m8 * 3.1415927f / 180.0f;
    if (b->m504 < lim) {
        b->m504 = b->m504 / lim;
        p->m1140 = 0;
        b->m508 = p->m1060 * 9.8f * b->m504 * spec->m4;
    } else {
        p->m1140 = 1;
        b->m508 = p->m1060 * 9.8f * spec->m4;
    }
    b->m508 = b->m508 * m9928;
    if (p->m1136 < 0.0f)
        b->m508 = -b->m508;
    if (p->m1096 < 10.0f)
        b->m508 = b->m508 * (p->m1096 * 0.1f);
    up->y = 0.0f;
    up->z = 0.0f;
    up->w = 0.0f;
    b->m64.x = b->m508;
    f_09ff44(b->m304);
    Angle a;
    a.a = p->m1136;
    f_099b98(&a.a);
    f_0a082c(b->m304, a, 2, 0);
    f_0a6bf4(&t, b->m304, up);
    p->m1120 = t;
    float half = 0.5f;
    float z = p->m1120.z;
    if (z < 0.0f)
        z = -z;
    b->m512 = z;
    b->m512 = b->m512 < p->m1060 * 9.8f ? b->m512 : p->m1060 * 9.8f;
    if (p->m1060 * 9.8f * spec->m12 < b->m512) {
        b->m520 = b->m520 + b->m520;
        float c = f_09a154(b->m520);
        b->m520 = c * c;
        b->m516 = (b->m512 - p->m1060 * 9.8f * spec->m12) * b->m520;
        b->m512 = b->m516 + p->m1060 * 9.8f * spec->m12;
        if (0.0f < p->m1120.z)
            p->m1120.z = b->m512 * half;
        else
            p->m1120.z = -b->m512 * half;
    }
    f_09ff44(b->m304);
    Angle a2;
    a2.a = -p->m1136;
    f_099b98(&a2.a);
    f_0a082c(b->m304, a2, 2, 0);
    f_0a6bf4(&t, b->m304, &p->m1120);
    p->m1120 = t;
    f_0a6c18(&t, p->m624, &p->m1120);
    p->m1120 = t;
}

/* @implements 0x0c063c us f_0c063c
   WHAT IT DOES: Clears the global body record, then runs the sound, camera, body, effect
   and light steps. */
void CRidgeMycar::f_0c063c()
{
    Phys *p = &phys;
    memset(D_2456d0, 0, 1632);
    f_0bcc4c(m8064, p->m384, p->m1060);
    f_0bdbdc(this);
    f_0c0270();
    f_0b73b4(this, 0);
    f_0b7ff4(this);
}

/* @implements 0x0c06d4 us f_0c06d4
   WHAT IT DOES: The player's frame: time scale, the race step when racing, the body update
   and the direction vector. */
void CRidgeMycar::f_0c06d4()
{
    f_0c01e8();
    if (m9912 >= 0)
        f_0fe8a4(this);
    f_0c063c();
    f_0bfc48();
}

/* @draft 0x0c071c us f_0c071c
   WHAT IT DOES: Clears the physics record, loads the spec, and keeps the spec pointer.
   DIFFERS: retail keeps this in s1 and the spec in s0 (swapped here), and stores the spec
   pointer through this+7092 with offset 48 instead of folding it to 7140. */
void CRidgeMycar::f_0c071c(Spec *s)
{
    Phys *p = &phys;
    memset(p, 0, sizeof(Phys));
    f_0bb220(this, s->m28);
    phys.m1300.Set(s);
    m7688 = s;
    p->m1300.m0 = 0;
    m7840 = 1.0f;
}

typedef char check_phys[sizeof(Phys) == 1888 ? 1 : -1];
#define OFS(m) ((unsigned)&((CRidgeMycar *)0)->m)
typedef char check_a[OFS(phys) == 5792 && OFS(m7688) == 7688 && OFS(m9912) == 9912 && OFS(m10036) == 10036 && OFS(m10116) == 10116 && OFS(m10128) == 10128 && OFS(m8064) == 8064 && OFS(m7956) == 7956 && OFS(m1888) == 1888 && OFS(m2128) == 2128 ? 1 : -1];
