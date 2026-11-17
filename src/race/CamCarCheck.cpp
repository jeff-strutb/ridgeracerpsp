/* The car check replay camera, CamCtrl::CCamCarCheck (retail 0x0f2f5c to 0x0f35c0): a camera
   for looking the car over (lens setting 7, a 48 degree lens). Its out of line virtual
   methods and the inline destructors emitted with its vtable. */

/* Degrees to radians, and pi. */
extern float D_1d5da4;
extern float D_1d5d90;

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
    Vec4() {}
    Vec4(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
};

/* A position as the car and the view keep it. */
struct CPos {
    float x, y, z, w;
};

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

/* A 3x4 matrix. */
struct M34 {
    float m[12];
};

/* The followed car as the camera reads it. */
struct CCar {
    char p0[144];
    CPos pos;
    char p160[48];
    float q[4];       /* 208, the orientation */
    char p224[1920];
    float m2144;
    char p2148[64];
    int m2212;
};

/* The view the camera drives. */
struct CView {
    CPos eye;
    char p16[464];
    float m480;   /* lens angle */
    char p484[12];
    float m496;   /* lens scale */
    char p500[72];
    int m572;
    char p576[32];
    float m608, m612, m616;
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    CPos m688;
    float m704;
    float m708;
    char p712[32];
    float m744;
};

/* The pad: held buttons and the pressure of the analog keys. */
struct CPad {
    char p0[16];
    int m16;          /* held buttons */
    char p20[8];
    unsigned short m28;
    char p30[2];
    unsigned short m32;
    char p34[18];
    unsigned short m52, m54, m56, m58, m60, m62, m64, m66;
};

}

extern CamCtrl::CPad D_1d8910;

extern "C" {
void f_0823f0(int n, CamCtrl::CView *v);
float f_0cd3cc(float a);
CamCtrl::Angle *f_099b98(CamCtrl::Angle *);
void f_09b394(CamCtrl::Angle a, float *x, float *y);
void f_09c720(CamCtrl::Vec4 *o, void *m, CamCtrl::Vec4 *v);
CamCtrl::M34 *f_09ff44(CamCtrl::M34 *m);
float f_09a9dc(float y, float x);
CamCtrl::M34 *f_0a082c(CamCtrl::M34 *m, CamCtrl::Angle a, int i, int j);
void f_0a4160(CamCtrl::Vec4 *o, CamCtrl::M34 *m, int n);
}

namespace CamCtrl {

/* An angle wrapped into range. */
struct Rad {
    Angle a;
    Rad(float f)
    {
        a.f = f;
        f_099b98(&a);
    }
};

class CCamCarCheck : public CCamProto {
public:
    virtual ~CCamCarCheck() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f8();

    CView *View() { return (CView *)param.v[0]; }
    CCar *Car() { return (CCar *)param.v[2]; }

    float dist;    /* 28 */
    float yaw;     /* 32 */
    float pitch;   /* 36 */
    float lens;    /* 40, in radians */
    int spin;      /* 44, turning on its own */
    float spinRate; /* 48 */
};

/* @implements 0x0f2f5c us _ZN7CamCtrl12CCamCarCheck3SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block (as the base camera). */
void CCamCarCheck::Set(const CamParam *p)
{
    CCamProto::Set(p);
}

/* @implements 0x0f2f78 us _ZN7CamCtrl12CCamCarCheck5ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamCarCheck::Reset()
{
    CCamProto::Reset();
}

/* @implements 0x0f2f94 us _ZN7CamCtrl12CCamCarCheck8f_07f5e0EPi
   WHAT IT DOES: Starts the camera: marks the view, puts lens setting 7 on it with a 48 degree
   lens angle (and its scale), and marks the previous camera's view. */
void CCamCarCheck::f_07f5e0(int *arg)
{
    CView *v = View();
    v->m668 = 1;
    f_0823f0(7, v);
    CView *w = View();
    w->m480 = D_1d5da4 * 48.0f * 0.5f;
    w->m496 = 1.0f / f_0cd3cc(w->m480);
    CView *o = (CView *)param.v[1];
    CView *t = View();
    t->m664 = 1;
    t->m660 = 7;
    if (o)
        o->m660 = -1;
}

/* @draft 0x0f3034 us _ZN7CamCtrl12CCamCarCheck8f_07f5e8Ev
   WHAT IT DOES: Steps the camera from the pad: one button toggles turning on its own, and
   pairs of analog keys (beyond a dead zone of 80) change the lens, the distance, the turn
   rate, the yaw and the pitch. The yaw wraps within two turns, the pitch stays between 0
   and just under a quarter turn and the lens between 1 and 75 degrees. The eye is put at
   the distance behind the car, turned by pitch and yaw and by the car's orientation, and
   looks at the car; the lens, its scale and the car's setting, speed and the eye are
   copied to the view. */
void CCamCarCheck::f_07f5e8()
{
    CPad *held = &D_1d8910;
    if (held->m16 & 0x1000) {
        if (spin)
            spin = 0;
        else
            spin = 1;
    }
    CPad *pad = &D_1d8910;
    int dl = pad->m62 - pad->m60;
    int dy = pad->m54 - pad->m52;
    int dp = pad->m56 - pad->m58;
    int dr = pad->m28 - pad->m32;
    int dd = pad->m64 - pad->m66;
    if (dl > 80)
        lens += (float)(dl - 80) * 1e-5f;
    else if (dl < -80)
        lens += (float)(dl + 80) * 1e-5f;
    if (dd > 80)
        dist += (float)(dd - 80);
    else if (dd < -80)
        dist += (float)(dd + 80);
    if (dr > 80)
        spinRate += (float)(dr - 80) * 1e-6f;
    else if (dr < -80)
        spinRate += (float)(dr + 80) * 1e-6f;
    if (dy > 80) {
        dy -= 80;
        yaw += D_1d5d90 * 0.005f * 0.01f * (float)dy;
    } else if (dy < -80) {
        dy += 80;
        yaw += D_1d5d90 * 0.005f * 0.01f * (float)dy;
    } else
        dy = 0;
    if (dp > 80)
        pitch += D_1d5d90 * 0.005f * 0.005f * (float)(dp - 80);
    else if (dp < -80)
        pitch += D_1d5d90 * 0.005f * 0.005f * (float)(dp + 80);
    if ((spin != 0) & (dy == 0))
        yaw += D_1d5d90 * spinRate;
    if (yaw > D_1d5d90 * 2.0f)
        yaw -= D_1d5d90 * 2.0f;
    if (yaw < -D_1d5d90 * 2.0f)
        yaw += D_1d5d90 * 2.0f;
    if (pitch >= D_1d5d90 * 0.5f - 0.001f)
        pitch = D_1d5d90 * 0.5f - 0.001f;
    if (pitch < 0.0f)
        pitch = 0.0f;
    if (lens < D_1d5da4)
        lens = D_1d5da4;
    if (lens > D_1d5da4 * 75.0f)
        lens = D_1d5da4 * 75.0f;
    Vec4 v(0.0f, 0.0f, -dist, 1.0f);
    f_09b394(Rad(pitch).a, &v.y, &v.z);
    f_09b394(Rad(yaw).a, &v.z, &v.x);
    Vec4 t;
    f_09c720(&t, &Car()->q, &v);
    v = t;
    v.x += Car()->pos.x;
    v.y += Car()->pos.y;
    v.z += Car()->pos.z;
    M34 m;
    f_09ff44(&m);
    float h = f_09a9dc(v.x - Car()->pos.x, v.z - Car()->pos.z);
    f_0a082c(&m, Rad(0.0f).a, 0, 1);
    f_0a082c(&m, Rad(-pitch).a, 1, 2);
    f_0a082c(&m, Rad(h).a, 2, 0);
    Vec4 out;
    CView *w = View();
    f_0a4160(&out, &m, 4);
    w->m608 = out.x;
    w->m612 = out.y;
    w->m616 = out.z;
    CView *u = View();
    u->eye.x = v.x;
    u->eye.y = v.y;
    u->eye.z = v.z;
    u->m480 = lens * 0.5f;
    u->m496 = 1.0f / f_0cd3cc(u->m480);
    CCar *c = Car();
    CView *x = View();
    x->m572 = c->m2212;
    x->m704 = c->m2144;
    x->m688 = x->eye;
    x->m708 = x->m480 + x->m480;
    x->m744 = c->m2144;
}

/* @implements 0x0f3580 us _ZN7CamCtrl12CCamCarCheck8f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamCarCheck::f_07f5f8()
{
}

/* @implements 0x0f3588 us _ZN7CamCtrl12CCamCarCheckD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0f3598 us _ZN7CamCtrl12CCamCarCheckD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */

}
