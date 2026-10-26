/* The third person (chase) camera, CamCtrl::CCamEye3 (retail 0x0c4bc4 to 0x0c5938): its
   parameter set up, the start values taken from the followed car, the start, step and stop
   methods and the inline destructors emitted with its vtable. The per frame update
   (0x0c4df4, 2300 bytes, the vtable's f_07f5f0 slot) is not transcribed yet. */

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
    char p160[1968];
    struct Orient {
        float m0, m4, m8, m12, m16;
    } m2128;
    char p2148[64];
    int m2212;
    char p2216[5492];
    float m7708;
    char p7712[32];
    float m7744;
    float m7748;
    char p7752[1976];
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
    char m0[624];
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
    int m688;
    int m692[3];
    Vec4 carPos;     /* 704 */
    int m720;
    int m724;
    int m728;
    int m732;
    int m736;
    float m740;
    int m744;
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
