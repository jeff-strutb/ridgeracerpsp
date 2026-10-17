/* The computer driven car (retail 0x0c078c to 0x0c19e4, "RRP::CRidgeComcar"). It derives
   from the race car (constructed and destroyed in another object file) and drives itself:
   two setups (from a car table row or from a spec record), the per frame move split into
   virtual steps that are skipped while the car is replayed (mode 2), the boost gauge, the
   frame time scale, and the course following step that places the car on the course line. */

#include <string.h>

union Angle {
    float a;
};

struct Vec4 {
    float x, y, z, w;
};

extern "C" {
void f_0b6754(void *car);
void f_0b6904(void *car);
void f_0a5e1c(Vec4 *v, float len);
void f_099b98(Angle *a);
void f_0bb220(void *car, void *param);
void f_0bcc4c(void *o, Vec4 v, float f);
void f_0bdbdc(void *car);
void f_0b73b4(void *car, int a);
void f_0b7ff4(void *car);
float f_0c2b7c(void *o);
void f_0a5e88(Vec4 *out, Vec4 *a, Vec4 *b);
float f_0a65c4(Vec4 *v);
}

struct Mat34 {
    float m[3][4];
    Mat34 &f_09ff44();
    Mat34 &f_0a082c(Angle a, int i, int j);
};

struct Mat43p {
    float m[4][4];
    Mat43p &f_0a2db0();
};

/* A course line point: the lateral offset and the heading (65536 to a turn). */
struct CourseLine {
    float f;
    short h;
    short pad;
};

/* A position and its Euler angles. */
struct Pose {
    Vec4 pos;
    float rx;
    float heading;
    float rz;
    float rw;
};

extern void *D_2456d0;
extern int D_245ec8;
extern int D_245ecc;

/* The course collision areas of the map manager. */
struct CourseAreas {
    char p0[8];
    int m8;                /* sections */
    float f_0e2260(int i);
    float f_0e26dc(float d);
    void f_0e2d10(float x, float d, float *px, float *py, float *pz);
    int Count() { return m8; }
};
struct MapMgr {
    CourseAreas *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas m12240;
};
extern MapMgr D_23c820;

/* The race car base (another object file). */
struct CRidgeCar {
    CRidgeCar() { f_0b6754(this); }
    ~CRidgeCar() { f_0b6904(this); }
};

/* The car's parameter block (360 bytes), as loaded by f_0bb220. */
struct CarParam {
    int m[90];
};

/* A row of the computer car table (396 bytes). */
struct CarRow {
    int m0;
    CarParam param;
    char p364[28];
    float m392;
};

/* A spec record. */
struct Spec {
    char p0[28];
    CarParam m28;
};

/* The car's own copy of its parameter block. */
struct ParamCopy {
    CarParam param;
    char p360[36];
};

/* The car's physics record (+5792, 1888 bytes). */
struct Phys {
    Pose cur;              /* 0 */
    Pose prev;             /* 32 */
    char p64[128];
    Vec4 m192;             /* 192: velocity per second */
    char p208[16];
    Vec4 m224;             /* 224: velocity */
    char p240[96];
    Vec4 m336;             /* 336: previous velocity */
    Vec4 m352;             /* 352: previous velocity per second */
    char p368[16];
    Vec4 m384;             /* 384 */
    char p400[28];
    int m428;              /* 428: section */
    int m432;              /* 432: previous section */
    int m436;              /* 436: section changed */
    float m440;
    float m444;
    float m448;
    int m452;
    float m456;            /* 456 */
    char p460[12];
    int m472;              /* 472: distance in 1/100 */
    float m476;
    int m480;
    int m484;
    int m488;
    int m492;              /* 492: total distance */
    int m496;
    char p500[268];
    Mat43p m768;           /* 768: body matrix */
    char p832[148];
    float m980;            /* 980: ground height */
    char p984[76];
    float m1060;           /* 1060 */
    char p1064[32];
    float m1096;           /* 1096: speed */
    float m1100;           /* 1100 */
    char p1104[168];
    char m1272[616];       /* 1272 */
};

/* The driving record (+7092). */
struct Drive {
    int m0;
    int m4;
    char p8[8];
    float m16;
    float m20;
    char p24[4];
    float m28;
    char p32[48];
    float m80;
    char p84[40];
    float m124;            /* heading */
    int m128;
    char p132[16];
    float m148;
    float m152;
    CarParam *m156;        /* the parameter block in use */
    ParamCopy m160;        /* 160 */
    char p556[20];
    float m576;
};

struct Lane {
    char p0[128];
    float m128;
};

/* The course follower (+7816). */
struct Follow {
    Lane *m0;
    char p4[20];
    float m24;
};

/* Clears the shared computer car counter on construction. */
struct ComCount {
    ComCount() { D_245ec8 = 0; }
};

namespace RRP {

class CRidgeComcar : public CRidgeCar, public ComCount {
public:
    CRidgeComcar();
    virtual ~CRidgeComcar();
    virtual void f_0c08bc();
    virtual void f_0c08c4();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void f_0c0900();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void f_0c0908();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void f_0c0d98();
    virtual void f_0c11dc();
    virtual void f_0c121c();
    virtual void f_0c1250();
    virtual void f_0c1284();
    virtual void f_0c12b8();
    virtual void f_0c12f0();
    virtual void f_0c1314();
    virtual void f_0c1348();
    virtual void f_0c13c0();
    virtual void f_0c13dc();
    virtual void f_0c1400();
    virtual void f_0c141c();
    virtual void f_0c1438();
    virtual void f_0c145c(float a, float b, float c);
    virtual void f_0c1860();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void f_0c0edc();
    virtual void f_0c10e8();
    virtual void f_0c1190();

    /* The direction record: x and z of the direction vector and the heading. */
    void SetDir(float h, float x, float z)
    {
        m2128 = x;
        m2132 = z;
        m2136 = h;
    }
    void f_0c0984(int i, CarRow *tab);
    void f_0c0b3c(Spec *s);
    void f_0c0d00(Spec *s);

    char p4[2124];
    float m2128;           /* 2128 */
    float m2132;
    float m2136;
    float m2140;
    float m2144;           /* 2144: distance along the course */
    float m2148;
    char p2152[104];
    float m2256;           /* 2256: previous distance */
    float m2260;
    char p2264[3528];
    Phys phys;             /* 5792 */
    char p7680[8];
    Spec *m7688;           /* 7688 */
    unsigned m7692;        /* 7692: input bits */
    char p7696[84];
    float m7780;           /* 7780 */
    char p7784[4];
    float m7788;           /* 7788 */
    char p7792[24];
    Follow m7816;          /* 7816 */
    char p7844[112];
    float m7956;           /* 7956 */
    char p7960[104];
    char m8064[1508];      /* 8064 */
    float m9572;           /* 9572 */
    char p9576[336];
    int m9912;             /* 9912: 2 while replayed */
    char p9916[4];
    float m9920;           /* 9920 */
    float m9924;
    float m9928;
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
    CourseLine *m10116;    /* 10116: the course line */
    int m10120;
    int m10124;
    int m10128;
    int m10132;
    int m10136;
    int m10140;
};

}

using namespace RRP;

/* @draft 0x0c078c us _ZN3RRP12CRidgeComcarC2Ev
   WHAT IT DOES: Builds the race car, clears the two shared counters, and starts with no
   target (-1) and one lap (base object constructor).
   DIFFERS: scheduling only: retail clears D_245ec8 before forming the vtable address and
   stores 10140 before 10136; every statement order, a clearing base class and volatile
   globals were tried. */
/* @draft 0x0c07e0 us _ZN3RRP12CRidgeComcarC1Ev
   WHAT IT DOES: The same (complete object constructor).
   DIFFERS: as the base object constructor. */
CRidgeComcar::CRidgeComcar()
{
    m10140 = 1;
    m10136 = -1;
    m10120 = 0;
    D_245ecc = 0;
}

/* @implements 0x0c0834 us _ZN3RRP12CRidgeComcarD2Ev
   WHAT IT DOES: Destroys the race car (base object destructor). */
/* @implements 0x0c085c us _ZN3RRP12CRidgeComcarD1Ev
   WHAT IT DOES: The same (complete object destructor). */
/* @implements 0x0c0884 us _ZN3RRP12CRidgeComcarD0Ev
   WHAT IT DOES: The same, then frees the car (deleting destructor). */
CRidgeComcar::~CRidgeComcar()
{
}

/* @implements 0x0c08bc us f_0c08bc
   WHAT IT DOES: Nothing for a computer car. */
void CRidgeComcar::f_0c08bc()
{
}

/* @implements 0x0c08c4 us f_0c08c4
   WHAT IT DOES: The per frame move: the computer car's frame (slot 68), then the car's
   virtual step at slot 20. */
void CRidgeComcar::f_0c08c4()
{
    f_0c1190();
    v20();
}

/* @implements 0x0c0900 us f_0c0900
   WHAT IT DOES: Nothing for a computer car. */
void CRidgeComcar::f_0c0900()
{
}

/* @implements 0x0c0908 us f_0c0908
   WHAT IT DOES: Builds the car's direction vector from its position (y relative to the
   ground height), scales it to length 1000, and stores it with the heading. */
void CRidgeComcar::f_0c0908()
{
    Vec4 v;
    v.x = phys.cur.pos.x;
    v.y = -(phys.cur.pos.y - phys.m980);
    v.z = -phys.cur.pos.z;
    v.w = 1.0f;
    f_0a5e1c(&v, 1000.0f);
    SetDir(phys.cur.heading, v.x, v.z);
}

/* @draft 0x0c0984 us f_0c0984
   WHAT IT DOES: Sets the car up from row i of a car table: clears the physics record, loads
   the row's parameters, keeps them, takes the start heading from the direction vector,
   computes the heading a quarter turn on (wrapped into -pi..pi), and starts the driving
   record (gear, speeds, lane offset) and the course follower.
   DIFFERS: scheduling only: retail loads the heading word into v1 and stores it after the
   quarter-turn constant's load, and interleaves the ra/s5 restores with the last stores. */
void CRidgeComcar::f_0c0984(int i, CarRow *tab)
{
    Phys *p = &phys;
    Follow *f = &m7816;
    Drive *d = (Drive *)((char *)this + 7092);
    memset(p, 0, sizeof(Phys));
    CarRow *r = &tab[i];
    CarParam *prm = &r->param;
    f_0bb220(this, prm);
    d->m156 = prm;
    d->m152 = r->m392;
    d->m80 = 2.0f;
    Angle a;
    a.a = m2136;
    f_099b98(&a);
    *(Angle *)&phys.cur.heading = a;
    Angle b;
    b.a = phys.cur.heading + 1.5707964f;
    f_099b98(&b);
    d->m124 = b.a;
    if (3.1415927f < b.a)
        d->m124 = b.a - 6.2831855f;
    else if (b.a < -3.1415927f)
        d->m124 = b.a + 6.2831855f;
    d->m4 = 1;
    d->m0 = 1;
    d->m16 = d->m20 = p->m456;
    d->m28 = f_0c2b7c(p->m1272) * 3.0f + 5.0f;
    Lane *l = f->m0;
    float g = f_0c2b7c(p->m1272);
    D_245ec8 = 0;
    d->m576 = l->m128 + g * 3000.0f;
    f->m24 = 1.0f;
    m10124 = 0;
    m10128 = 0;
    m10132 = 0;
}

/* @draft 0x0c0b3c us f_0c0b3c
   WHAT IT DOES: Sets the car up from a spec record: as the table setup, with the parameter
   block copied into the car, the start heading taken from the course areas at the car's
   start position, and the target and lap counters reset.
   DIFFERS: register allocation: retail keeps the physics record in s2, reuses the spec's s0
   for the constant 1 and the lane in s1 (here s1, s2, s0), plus the heading copy schedule of
   0x0c0984. */
void CRidgeComcar::f_0c0b3c(Spec *s)
{
    Phys *p = &phys;
    Follow *f = &m7816;
    Drive *d = (Drive *)((char *)this + 7092);
    memset(p, 0, sizeof(Phys));
    f_0bb220(this, &s->m28);
    f_0c0d00(s);
    d->m152 = 0.0f;
    d->m80 = 2.0f;
    m7688 = s;
    Angle a;
    a.a = D_23c820.Areas()->f_0e2260((int)m9572);
    f_099b98(&a);
    *(Angle *)&phys.cur.heading = a;
    Angle b;
    b.a = phys.cur.heading + 1.5707964f;
    f_099b98(&b);
    d->m124 = b.a;
    if (3.1415927f < b.a)
        d->m124 = b.a - 6.2831855f;
    else if (b.a < -3.1415927f)
        d->m124 = b.a + 6.2831855f;
    d->m4 = 1;
    d->m0 = 1;
    d->m16 = d->m20 = p->m456;
    d->m28 = f_0c2b7c(p->m1272) * 3.0f + 5.0f;
    Lane *l = f->m0;
    float g = f_0c2b7c(p->m1272);
    D_245ec8 = 0;
    m10140 = 1;
    d->m576 = l->m128 + g * 3000.0f;
    m10136 = -1;
    f->m24 = 1.0f;
    m10132 = 0;
    m10124 = 0;
    m10128 = 0;
}

/* @implements 0x0c0d00 us f_0c0d00
   WHAT IT DOES: Copies the spec's parameter block into the car's own copy and uses it. */
void CRidgeComcar::f_0c0d00(Spec *s)
{
    Drive *d = (Drive *)((char *)this + 7092);
    memset(&d->m160, 0, sizeof(ParamCopy));
    d->m160.param = s->m28;
    d->m156 = &d->m160.param;
}

/* @implements 0x0c0d98 us f_0c0d98
   WHAT IT DOES: The computer car's frame steps: clears the global body record, runs the
   driving steps (only the replay step and the body step while replayed), then the sound,
   camera, effect and light steps. */
void CRidgeComcar::f_0c0d98()
{
    Phys *p = &phys;
    memset(D_2456d0, 0, 1632);
    if (m9912 != 2) {
        v32();
        v33();
        v34();
        v35();
        v36();
        v37();
        v63();
    } else {
        v64();
        v36();
    }
    f_0bcc4c(m8064, p->m384, p->m1060);
    f_0bdbdc(this);
    v23();
    f_0b73b4(this, 0);
    f_0b7ff4(this);
}

/* @draft 0x0c0edc us f_0c0edc
   WHAT IT DOES: The boost gauge state machine (0 idle, 1 rising, 2 holding, 3 falling): the
   computer car boosts whenever its boost input is set. Sets the speed factor, capped at 2.
   DIFFERS: two spots: retail multiplies the falling factor straight into the result register
   (f4) and stores the hold time's zero floor from f4; this build multiplies through f0 and
   stores sw zero. If-chains, declaration orders and split multiplies do not fix it. */
void CRidgeComcar::f_0c0edc()
{
    Phys *p = &phys;
    float add = 0.0f;
    int done = 0;

    switch (m10044) {
    case 0:
        if (m7692 & 0x10000) {
            m10036 = m7780;
            m10044 = 1;
            m10056 = 100.0f;
        } else {
            m10036 = 1.0f;
        }
        break;
    case 1:
        m10036 += m10076;
        if (m7788 < m10036) {
            m10036 = m7788;
            m10044 = 2;
        }
    case 2:
        m10056 -= m10060;
        if (m10056 <= add) {
            done = 1;
            m10056 = add;
        }
        break;
    case 3:
        m10036 += m10064;
        if (m10036 < 1.0f) {
            m10036 = 1.0f;
            m10044 = 0;
        }
        if (m7692 & 0x10000) {
            m10044 = 1;
            m10056 = 100.0f;
        }
        break;
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

/* @implements 0x0c10e8 us f_0c10e8
   WHAT IT DOES: Runs the boost step, then sets the frame time scale (base scale times the
   car's own scale times the boost factor, capped at 3), its reciprocal and per-second forms,
   and the effect scale (at least 1). */
void CRidgeComcar::f_0c10e8()
{
    f_0c0edc();
    m9928 = m9920 * m9924 * m10040;
    float s = m9928 < 3.0f ? m9928 : 3.0f;
    m9928 = s;
    m9932 = 1.0f / s;
    m9936 = s * 0.016666668f;
    m9940 = 1.0f / m9936;
    m9944 = m9932 * 0.016666668f;
    if (1.0f < s)
        m7956 = s;
    else
        m7956 = 1.0f;
}

/* @implements 0x0c1190 us f_0c1190
   WHAT IT DOES: The computer car's frame: time scale, the frame steps, the direction
   vector. */
void CRidgeComcar::f_0c1190()
{
    f_0c10e8();
    f_0c0d98();
    f_0c0908();
}

/* @implements 0x0c11dc us f_0c11dc
   WHAT IT DOES: Time scale, then clears the global body record. */
void CRidgeComcar::f_0c11dc()
{
    void *b = D_2456d0;
    f_0c10e8();
    memset(b, 0, 1632);
}

/* @implements 0x0c121c us f_0c121c
   WHAT IT DOES: Driving step 32 unless replayed. */
void CRidgeComcar::f_0c121c()
{
    if (m9912 != 2)
        v32();
}

/* @implements 0x0c1250 us f_0c1250
   WHAT IT DOES: Driving step 33 unless replayed. */
void CRidgeComcar::f_0c1250()
{
    if (m9912 != 2)
        v33();
}

/* @implements 0x0c1284 us f_0c1284
   WHAT IT DOES: Driving step 34 unless replayed. */
void CRidgeComcar::f_0c1284()
{
    if (m9912 != 2)
        v34();
}

/* @implements 0x0c12b8 us f_0c12b8
   WHAT IT DOES: The replay step when replayed, otherwise driving step 35. */
void CRidgeComcar::f_0c12b8()
{
    if (m9912 == 2)
        v64();
    else
        v35();
}

/* @implements 0x0c12f0 us f_0c12f0
   WHAT IT DOES: Driving step 36. */
void CRidgeComcar::f_0c12f0()
{
    v36();
}

/* @implements 0x0c1314 us f_0c1314
   WHAT IT DOES: Driving step 37 unless replayed. */
void CRidgeComcar::f_0c1314()
{
    if (m9912 != 2)
        v37();
}

/* @implements 0x0c1348 us f_0c1348
   WHAT IT DOES: Driving step 63 unless replayed, then the sound step. */
void CRidgeComcar::f_0c1348()
{
    Phys *p = &phys;
    if (m9912 != 2)
        v63();
    f_0bcc4c(m8064, p->m384, p->m1060);
}

/* @implements 0x0c13c0 us f_0c13c0
   WHAT IT DOES: The camera step. */
void CRidgeComcar::f_0c13c0()
{
    f_0bdbdc(this);
}

/* @implements 0x0c13dc us f_0c13dc
   WHAT IT DOES: The body step (slot 23). */
void CRidgeComcar::f_0c13dc()
{
    v23();
}

/* @implements 0x0c1400 us f_0c1400
   WHAT IT DOES: The effect step. */
void CRidgeComcar::f_0c1400()
{
    f_0b73b4(this, 0);
}

/* @implements 0x0c141c us f_0c141c
   WHAT IT DOES: The light step. */
void CRidgeComcar::f_0c141c()
{
    f_0b7ff4(this);
}

/* @implements 0x0c1438 us f_0c1438
   WHAT IT DOES: The direction vector (slot 22). */
void CRidgeComcar::f_0c1438()
{
    f_0c0908();
}

/* @draft 0x0c145c us f_0c145c
   WHAT IT DOES: Moves the computer car along the course line (skipped while replayed): keeps
   the previous pose and velocities, advances the distance by a * (frame scale * b + c) and
   lets the course areas wrap it, looks up the course line point (lateral offset and heading)
   for the new section, places the car there (scaled by 1/1000, y and z flipped), sets its
   heading, velocity and course heading (a quarter turn on, wrapped into -pi..pi, plus the
   pending steer), rebuilds the body matrix from the angles and the position, and derives the
   per-second velocity and the speed.
   DIFFERS: register choice for the course line lookup (retail loads the table into v1 and
   the scaled index into v0, here swapped) and retail loads the heading before the quarter
   turn constant. */
void CRidgeComcar::f_0c145c(float a, float b, float c)
{
    CourseAreas *ar = D_23c820.Areas();
    Phys *p = &phys;
    Vec4 v = {0.0f, 0.0f, 0.0f, 0.0f};

    if (m9912 == 2)
        return;
    m2256 = m2144;
    m2260 = m2140;
    Drive *d = (Drive *)((char *)this + 7092);
    p->prev = p->cur;
    p->m336 = p->m224;
    p->m352 = p->m192;
    float step = a * (m9928 * b + c);
    float dist = m2144 + step;
    dist = ar->f_0e26dc(dist);
    int sec = (int)dist;
    CourseLine *e = &m10116[sec];
    float x = e->f;
    float h = (float)-e->h * 9.58738e-05f;
    p->m432 = p->m428;
    p->m428 = sec;
    m2136 = h;
    ar->f_0e2d10(x, dist, &v.x, &v.y, &v.z);
    m2140 = v.y;
    m2148 = x;
    m2144 = dist;
    v.y = -v.y;
    v.z = -v.z;
    v.w = 1.0f;
    f_0a5e1c(&v, 0.001f);
    p->cur.pos = v;
    float hh = h;
    f_099b98((Angle *)&hh);
    Vec4 *vel = &p->m224;
    vel->x = 0.0f;
    *(Angle *)&phys.cur.heading = *(Angle *)&hh;
    vel->z = step;
    vel->w = 1.0f;
    vel->y = 0.0f;
    f_0a5e1c(vel, 59.999996f);
    Angle k;
    k.a = phys.cur.heading + 1.5707964f;
    f_099b98(&k);
    d->m124 = k.a;
    if (3.1415927f < k.a)
        d->m124 = k.a - 6.2831855f;
    else if (k.a < -3.1415927f)
        d->m124 = k.a + 6.2831855f;
    d->m124 = d->m124 + d->m148;
    d->m148 = 0.0f;
    d->m128 = 0;
    p->m768.f_0a2db0();
    Mat34 rot;
    rot.f_09ff44();
    Angle m;
    m.a = -p->cur.rz;
    f_099b98(&m);
    rot.f_0a082c(m, 0, 1);
    Angle n;
    n.a = -p->cur.rx;
    f_099b98(&n);
    rot.f_0a082c(n, 1, 2);
    Angle o;
    o.a = -p->cur.heading;
    f_099b98(&o);
    rot.f_0a082c(o, 2, 0);
    *(Mat34 *)p->m768.m = rot;
    Vec4 *tr = (Vec4 *)p->m768.m[3];
    *tr = p->cur.pos;
    Vec4 t;
    f_0a5e88(&t, &p->cur.pos, &p->prev.pos);
    p->m192 = t;
    f_0a5e1c(&p->m192, 60.0f);
    p->m1096 = f_0a65c4(&p->m192);
}

/* @draft 0x0c1860 us f_0c1860
   WHAT IT DOES: Tracks the car along the course: when the course section changed, adds the
   section step (102 per section, wrapped around the lap) to the distance and the absolute
   change to the total distance (capped at 2e9); then splits the position along the course
   into its fraction and scaled forms, keeps the previous scaled distance, sets the speed along
   the course per second, and runs the direction vector step.
   DIFFERS: retail forms the course areas' address with a separate +12240 before loading the
   section count (this build folds it into the load), which shifts the schedule after it. */
void CRidgeComcar::f_0c1860()
{
    Phys *p = &phys;
    p->m436 = 0;
    if (p->m432 != p->m428) {
        int n = D_23c820.Areas()->Count();
        int d = p->m428 - p->m432;
        if (n >> 1 < d)
            d -= n;
        if (d < -(n >> 1))
            d += n;
        int pos = p->m472 + d * 102;
        int a = pos - p->m496;
        if (a < 0)
            a = -a;
        p->m436 = 1;
        p->m472 = pos;
        if (a / 100 > 0) {
            p->m492 += a;
            if (p->m492 > 1999999999)
                p->m492 = 2000000000;
            p->m496 = p->m472;
        }
    }
    p->m452 = 0;
    p->m456 = 0.0f;
    float f = m2144 - (int)m2144;
    p->m488 = p->m484;
    p->m448 = f;
    p->m440 = f * 1.024f;
    p->m476 = p->m440;
    p->m444 = m2148 * 1.024f;
    p->m484 = p->m472 + (int)(p->m440 * 100.0f);
    p->m480 = (int)(m2144 * 100.0f);
    p->m1100 = (m2144 - m2256) / 0.016666668f;
    f_0c0908();
}

typedef char check_phys[sizeof(Phys) == 1888 ? 1 : -1];
typedef char check_drive[sizeof(Drive) == 580 ? 1 : -1];
#define OFS(m) ((unsigned)&((CRidgeComcar *)0)->m)
typedef char check_a[OFS(phys) == 5792 && OFS(m7688) == 7688 && OFS(m7816) == 7816 && OFS(m9572) == 9572 && OFS(m9912) == 9912 && OFS(m10036) == 10036 && OFS(m10116) == 10116 && OFS(m10140) == 10140 && OFS(m8064) == 8064 && OFS(m7956) == 7956 && OFS(m2128) == 2128 ? 1 : -1];
