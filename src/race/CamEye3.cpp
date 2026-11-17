/* The third person (chase) camera, CamCtrl::CCamEye3 (retail 0x0c4bc4 to 0x0c5938): its
   parameter set up, the start values taken from the followed car, the start, step and stop
   methods, the per frame update and the inline destructors emitted with its vtable. */

extern "C" float sqrtf(float);

namespace CamCtrl {

struct CamParam {
    int v[6];
};

class CCamProto {
public:
    virtual ~CCamProto() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg) {}
    virtual void f_07f5e8() {}
    virtual void f_07f5f0() {}
    virtual void f_07f5f8() {}

    CamParam param;
};

struct Vec4 {
    float x, y, z, w;
    void Zero()
    {
        x = 0;
        w = 0;
        y = 0;
        z = 0;
    }
    float Length() { return sqrtf(x * x + y * y + z * z); }
    void Add(const Vec4 &b)
    {
        x += b.x;
        y += b.y;
        z += b.z;
    }
};

/* The point at a plus b. */
inline Vec4 Point(const Vec4 &a, const Vec4 &b)
{
    Vec4 r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    r.w = 1.0f;
    return r;
}

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

}

extern "C" {
void f_099b98(CamCtrl::Angle *);
float f_09a9dc(float, float);
float f_0cd3cc(float a);
void f_0a6fac(void *m);
void f_09b070(void *d, const void *q, int order);
float f_0a65c4(const CamCtrl::Vec4 *a);
void f_09b394(CamCtrl::Angle a, float *x, float *y);
void f_0a6bf4(CamCtrl::Vec4 *d, const void *m, const CamCtrl::Vec4 *v);
float f_099fc4(float a);
void f_0a5ea4(CamCtrl::Vec4 *d, const CamCtrl::Vec4 *a, float s);
float f_09ad0c(float x);
void f_0a88ac(void *p);
int f_0b1bc0(void *hit, int area, float x, float z);
int f_0b20d8(void *hit, CamCtrl::Vec4 *pos, CamCtrl::Vec4 *last, CamCtrl::Vec4 *out, float r);
void f_0a5dc8(CamCtrl::Vec4 *d, const CamCtrl::Vec4 *b);
void f_0a5e1c(CamCtrl::Vec4 *d, float s);
}

namespace CamCtrl {

/* An angle wrapped into range. */
struct Rad {
    Angle a;
    Rad() { a.f = 0; }
    Rad(float f)
    {
        a.f = f;
        f_099b98(&a);
    }
    void Add(float f)
    {
        a.f += f;
        f_099b98(&a);
    }
};

/* Rotation angles with a fourth (unused) word. */
struct Rot4 {
    Rad r[3];
    int w;
    Rot4(float x, float y, float z)
    {
        r[0] = Rad(x);
        r[1] = Rad(y);
        r[2] = Rad(z);
        w = 0;
    }
};
struct Ang4 {
    int v[4];
};

/* The chase camera's tuning block (CCamEye3::m816). */
struct E3Tune {
    char p0[20];
    float m20;
    char p24[12];
    float m36;
};

/* The followed car's body state (at 5792). */
struct E3Body {
    char p0[768];
    char m768[96];   /* orientation matrix */
    Vec4 m864;       /* velocity */
    char p880[156];
    short m1036;
    char p1038[98];
    float m1136;     /* roll */
    char p1140[776];
};

/* Rotation angles. */
struct Rot {
    Rad r[3];
    Rot(float x, float y, float z)
    {
        r[0] = Rad(x);
        r[1] = Rad(y);
        r[2] = Rad(z);
    }
};

/* The parameter block of a chase camera. */
struct Eye3Param {
    CamParam base;
    int m24;
    int m28;
    int m32;
};

/* The followed car as the camera reads it. */
struct E3Car {
    char p0[144];
    Vec4 pos;
    char p160[48];
    float m208[4];
    char p224[1904];
    struct Orient {
        float m0, m4, m8, m12, m16;
    } m2128;
    char p2148[64];
    int m2212;
    char p2216[264];
    float m2480[4];
    char p2496[3296];
    E3Body body;
    float m7708;
    float m7712;
    char p7716[28];
    float m7744;
    float m7748;
    char p7752[288];
    float m8040;
    char p8044[1684];
    Vec4 m9728;   /* the camera's offset from the car */
};

/* The view the camera drives. */
struct E3View {
    float m0, m4, m8;
    char p12[468];
    float m480;   /* lens angle */
    char p484[4];
    float m488;   /* far distance */
    char p492[4];
    float m496;   /* lens scale */
    char p500[72];
    int m572;
    char p576[32];
    int m608;
    float m612;
    float m616;
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    float m688, m692, m696;
    char p700[4];
    float m704;
    float m708;
    char p712[32];
    float m744;
};

/* The car's motion state (made and destroyed elsewhere). */
struct CMotion {
    void f_0a737c(float a, float b, float c, float d);
    void Set(const E3Car::Orient &o) { f_0a737c(o.m0, o.m12, o.m4, o.m16); }
    float m0;
    float m4;
    int m8;
    float m12;
    char p16[96];
    int m112;
    char p116[508];
    ~CMotion() { f_0a6fac(this); }
};

/* Puts the eye and the point looked at on a view. */
inline void Look(E3View *v, const Vec4 &at, const Vec4 &eye)
{
    v->m608 = *(int *)&at.x;
    v->m612 = at.y;
    v->m616 = at.z;
    v->m0 = eye.x;
    v->m4 = eye.y;
    v->m8 = eye.z;
}

class CCamEye3 : public CCamProto {
public:
    virtual ~CCamEye3() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f0();
    virtual void f_07f5f8();
    void f_0c4c20();

    E3View *View() { return (E3View *)param.v[0]; }
    E3Car *Car() { return (E3Car *)param.v[2]; }
    Vec4 At() { return m760; }

    int m28;
    CMotion motion;
    Vec4 ofs;        /* 656 */
    float dist;      /* 672 */
    float ang;       /* 676 */
    int m680;
    int m684;
    float m688;
    int m692[3];
    Vec4 carPos;     /* 704 */
    float m720;
    float m724;
    float m728;
    float m732;
    int m736;
    float m740;
    float m744;
    float m748;
    float m752;
    float m756;
    Vec4 m760;
    int m776[2];
    Vec4 m784;
    Vec4 m800;
    int m816;
    int m820[3];
    Vec4 m832;
    char m848[64];
};

/* @implements 0x0c4bc4 us _ZN7CamCtrl8CCamEye33SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block, keeps its extra word and sets up the camera. */
void CCamEye3::Set(const CamParam *p)
{
    CCamProto::Set(p);
    m816 = ((const Eye3Param *)p)->m32;
    f_0c4c20();
}

/* @implements 0x0c4c04 us _ZN7CamCtrl8CCamEye35ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamEye3::Reset()
{
    CCamProto::Reset();
}

/* @draft 0x0c4c20 us _ZN7CamCtrl8CCamEye38f_0c4c20Ev
   DRAFT: the second half (motion set up, car position, clears) matches; the offset and eye
   arithmetic is scheduled differently (retail computes the length only after the m800 clear
   and keeps the car pointer in v1).
   WHAT IT DOES: Sets the camera up behind the car: its offset from the car (raised by the
   car's two heights and pushed back), the eye at the car plus that offset, the offset's
   length and angle, the car's position, and the remaining state cleared, with a lens angle
   of a quarter turn. */
void CCamEye3::f_0c4c20()
{
    E3Car *c = Car();
    ofs = c->m9728;
    ofs.y += c->m7708 + c->m7744;
    ofs.z += c->m7748;
    m832 = m784 = Point(c->pos, ofs);
    m800.Zero();
    dist = ofs.Length();
    ang = f_09a9dc(ofs.y, ofs.z);
    m756 = f_09a9dc(ofs.y, ofs.z);
    c = Car();
    m680 = 0;
    Vec4 *pp = &c->pos;
    carPos = *pp;
    m688 = 0;
    motion.Set(c->m2128);
    m740 = 1.0f;
    m752 = 0.78539819f;
    m720 = 0;
    m724 = 0;
    m728 = 0;
    m732 = 0;
    m744 = 0;
    m736 = 0;
    m748 = 0.78539819f;
}

/* @draft 0x0c4df4 us _ZN7CamCtrl8CCamEye38f_07f5f0Ev
   DRAFT: whole-function hand transcription, 2292 vs 2300 bytes. One cycle: declaring d and q
   before e gives retail's frame (r 0, d 16, q 32, e 48, up 64, t 80) -- kept. Remaining
   difference from the first word: retail keeps 0.0 in $f20 for the whole entry (mtc1 zero, the
   Rad() loop stores swc1 $f20, the m720 and k clamps compare against it, and acc is loaded from
   d.x into the same register); here the loop stores sw zero and acc's d.x load is a separate
   pseudo, so allocation and scheduling diverge from +0x4 on. Not yet checked: the 0.0 shape
   (a float zero local shared by the Rad ctor and the clamps), m784/m800 add order.
   WHAT IT DOES: The per frame update. Takes the car's heading, eases the camera's sway terms
   toward the car's speed scaled values and its roll, raises the followed point to half way to
   the car's wheel height (eased by a sine), swings the pitch toward the car's slope (holding a
   direction once it starts to move), places the eye at the rotated offset behind the car kept
   300 above the ground, pushes it out of walls (else lets the push decay), and sets the angles
   the view looks along. */
void CCamEye3::f_07f5f0()
{
    Rot4 r(0, 0, 0);
    Vec4 d;
    Vec4 q;
    E3Car *c = Car();
    E3Body *b = &c->body;
    Ang4 e;
    f_09b070(&e, c->m208, 4);
    *(Ang4 *)&r = e;
    d.x = 0;
    d.y = 0;
    d.z = 0;
    d.w = 1.0f;
    m720 -= 0.008f;
    if (m720 < 0)
        m720 = 0;
    float acc = d.x;
    float k = f_0a65c4(&c->body.m864) - 1.944446f;
    if (k < 0)
        k = 0;
    else {
        k /= 11.11112f;
        if (k > 1.0f)
            k = 1.0f;
    }
    k -= m720;
    if (k < 0)
        k = 0;
    float sp = Car()->m8040 * k;
    m724 += (sp * -37.5f - m724) * 0.12f;
    m728 += (sp * -0.01308997f - m728) * 0.12f;
    m732 += (sp * -0.017453292f - m732) * 0.2f;
    acc += m728;
    acc += m732;
    float roll = b->m1136;
    if (roll > 1.5707964f)
        roll = 3.1415927f - roll;
    else if (roll < -1.5707964f)
        roll = -3.1415927f - roll;
    roll *= k;
    float dr = roll - m744;
    if (dr > 0.15707964f)
        dr = 0.15707964f;
    else if (dr < -0.15707964f)
        dr = -0.15707964f;
    m744 = dr + m744;
    acc += m744 * 0.25f;
    r.r[1].Add(acc);
    f_09b394(r.r[1].a, &d.z, &d.x);

    float w;
    E3Car *c2 = Car();
    for (int i = 0; i < 4; i++)
        w = c2->m2480[i];
    float lift = c2->m7708 * c2->m7712;
    w *= 0.25f;
    Vec4 up;
    up.x = 0;
    up.y = 1.0f;
    up.z = 0;
    up.w = 1.0f;
    Vec4 t;
    f_0a6bf4(&t, b->m768, &up);
    up = t;
    Vec4 *pp = &Car()->pos;
    carPos = *pp;
    float h = (carPos.y + w) * 0.5f - carPos.y;
    if (h > 50.0f)
        h = 50.0f;
    else if (h < -50.0f)
        h = -50.0f;
    carPos.y += f_099fc4(h / 50.0f * 3.1415927f * 0.5f) * 50.0f;
    f_0a5ea4(&t, &up, lift);
    carPos.Add(t);
    carPos.Add(d);

    if (b->m1036 >= 2)
        m680 = -1;
    else {
        q = *(const Vec4 *)((const char *)&Car()->m2128 + 64);
        Rad n(-r.r[1].a.f);
        f_09b394(n.a, &q.z, &q.x);
        float a = f_09a9dc(q.z, q.y);
        float f;
        if (a > 0)
            f = 0.25f;
        else
            f = 1.25f;
        a *= f;
        float da = a - m688;
        if (m680 == -1) {
            m680 = 1;
            m684 = da > 0;
        }
        if (da < m748 && da > -m752)
            m680 = 0;
        else if (da > 0) {
            if (m684 != 1)
                m680 = 0;
        } else if (m684 != 0)
            m680 = 0;
        if (da > 0) {
            if (da > m748)
                da = m748;
        } else if (da < -m752)
            da = -m752;
        m688 += da;
        m752 = 0.017453292f;
        m748 = 0.017453292f;
    }

    m784 = ofs;
    Rad p(m688);
    f_09b394(p.a, &m784.y, &m784.z);
    float y = m784.y;
    f_09b394(r.r[1].a, &m784.z, &m784.x);
    m784.Add(carPos);
    float lim = motion.m12 + 300.0f;
    if (m784.y < lim) {
        float s = (lim - m784.y + y) / dist;
        if (!(s < 1.0f))
            s = 1.0f;
        m688 = -(f_09ad0c(s) - ang);
        m784 = ofs;
        Rad p2(m688);
        f_09b394(p2.a, &m784.y, &m784.z);
        f_09b394(r.r[1].a, &m784.z, &m784.x);
        m784.Add(carPos);
    }
    motion.m0 = m784.x;
    motion.m4 = m784.z;
    f_0a88ac(&motion);
    m784.Add(m800);
    f_0b1bc0(m848, motion.m112, m784.x, m784.z);
    if (f_0b20d8(m848, &m784, &m832, &t, 5.0f)) {
        f_0a5dc8(&m784, &t);
        f_0a5dc8(&m800, &t);
    } else
        f_0a5e1c(&m800, 0.95f);
    m832 = m784;
    E3Tune *tn = (E3Tune *)m816;
    r.r[1].Add(tn->m20 * 1.5f * 9.5873e-05f);
    Rot4 &v = *(Rot4 *)&m760;
    v = r;
    float pitch = m688 + -0.017453292f;
    if (!(pitch > -0.7853982f))
        pitch = -0.7853982f;
    pitch += tn->m36 * 0.0002684444f;
    v.r[0] = Rad(pitch);
    v.r[2] = Rad(0);
}

/* @implements 0x0c56f0 us _ZN7CamCtrl8CCamEye38f_07f5e0EPi
   WHAT IT DOES: Starts the camera: marks its view, marks the previous camera's view and sets
   a far distance of 300. */
void CCamEye3::f_07f5e0(int *arg)
{
    E3View *v = View();
    E3View **pp = (E3View **)&param.v[1];
    E3View *o = *pp;
    v->m668 = 1;
    v->m672 = 1;
    v->m664 = 1;
    v->m660 = 1;
    if (o)
        o->m660 = -1;
    v->m488 = 300.0f;
}

/* @draft 0x0c5728 us _ZN7CamCtrl8CCamEye38f_07f5e8Ev
   DRAFT: 4 bytes long. Retail shares one stack slot between the zero rotation and the copy
   of the point looked at (frame 64), and its third angle store is dead; here they get
   separate slots and a fourth saved register.
   WHAT IT DOES: Puts the camera on its view: the eye and the point looked at, a 55 degree
   lens and its scale, the car's setting, speed and position, and the lens span. */
void CCamEye3::f_07f5e8()
{
    Vec4 eye;
    Rot(0, 0, 0);
    eye = m784;
    E3View *v = View();
    Look(v, At(), eye);
    v->m480 = 0.95993108f * 0.5f;
    v->m496 = 1.0f / f_0cd3cc(v->m480);
    E3Car *c = Car();
    E3View *w = View();
    w->m572 = c->m2212;
    w->m704 = c->m2128.m16;
    w->m688 = c->pos.x;
    w->m692 = c->pos.y;
    w->m696 = c->pos.z;
    w->m708 = w->m480 + w->m480;
    w->m744 = c->m2128.m16;
}

/* @implements 0x0c5888 us _ZN7CamCtrl8CCamEye38f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamEye3::f_07f5f8()
{
}

/* @implements 0x0c5890 us _ZN7CamCtrl8CCamEye3D1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): frees the
   motion state and restores the base vtable. */
/* @implements 0x0c58e0 us _ZN7CamCtrl8CCamEye3D0Ev
   WHAT IT DOES: Deleting destructor: as above, then frees the object. */

}
