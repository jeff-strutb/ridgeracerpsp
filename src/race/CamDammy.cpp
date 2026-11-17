/* The stand-in replay cameras (retail 0x0f35c0 to 0x0f3f30): CamCtrl::CCamDammy, which does
   nothing but keep its parameters, and the two fixed eye cameras CCamDammyEye1 and
   CCamDammyEye3, which set the view's flags when they start. Their out of line virtual
   methods and the inline destructors emitted with their vtables. */

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

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

/* A 3x4 matrix. */
struct M34 {
    float m[12];
};

}

extern "C" {
void f_099b98(CamCtrl::Angle *);
float f_0cd3cc(float a);
void f_09c720(CamCtrl::Vec4 *o, void *m, CamCtrl::Vec4 *v);
void f_09ff44(CamCtrl::M34 *m);
void f_0a082c(CamCtrl::M34 *m, CamCtrl::Angle a, int i, int j);
void f_09fd1c(CamCtrl::M34 *m, void *q);
void f_0a12ac(CamCtrl::M34 *o, CamCtrl::M34 *a, CamCtrl::M34 *b);
void f_0a4160(CamCtrl::Vec4 *o, CamCtrl::M34 *m, int n);
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

/* Rotation angles and a zero. */
struct Rot {
    Rad r[3];
    float w;
    Rot(float x, float y, float z)
    {
        r[0] = Rad(x);
        r[1] = Rad(y);
        r[2] = Rad(z);
        w = 0;
    }
};

/* The orientation as a matrix. */
inline M34 FromQuat(float *q)
{
    M34 m;
    f_09fd1c(&m, q);
    return m;
}

/* The product of two matrices. */
inline M34 Mul(const M34 &a, const M34 &b)
{
    M34 r;
    f_0a12ac(&r, (M34 *)&a, (M34 *)&b);
    return r;
}

/* The car's body sizes. */
struct DBody {
    char p0[448];
    float m448;   /* height */
};

/* A position as the car keeps it. */
struct DPos {
    float x, y, z, w;
};

/* The followed car as the cameras read it. */
struct DCar {
    char p0[144];
    DPos pos;
    char p160[48];
    float q[4];       /* 208, the orientation */
    char p224[1920];
    float m2144;
    char p2148[64];
    int m2212;
    char p2216[5464];
    DBody *m7680;
};

/* The screen set up. */
struct DScreen {
    char p0[12];
    int m12, m16, m20;
    float m24, m28, m32, m36, m40, m44;
};

/* The view the cameras drive. */
struct DView {
    DPos eye;
    char p16[464];
    float m480;    /* lens angle */
    float m484;
    float m488;    /* far distance */
    float m492;
    float m496;    /* lens scale */
    int m500, m504, m508, m512, m516;
    float m520, m524, m528, m532;
    char p536[36];
    int m572;
    char p576[32];
    Angle m608;
    float m612, m616;
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    DPos m688;     /* the eye, kept */
    float m704;
    float m708;
    char p712[32];
    float m744;
};

}

extern CamCtrl::DScreen D_23fefc;

namespace CamCtrl {

class CCamDammy : public CCamProto {
public:
    virtual ~CCamDammy() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f8();
};

class CCamDammyEye1 : public CCamProto {
public:
    virtual ~CCamDammyEye1() {}
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();

    DView *View() { return (DView *)param.v[0]; }
    DView *Prev() { return (DView *)param.v[1]; }
    DCar *Car() { return (DCar *)param.v[2]; }
};

class CCamDammyEye3 : public CCamProto {
public:
    virtual ~CCamDammyEye3() {}
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();

    DView *View() { return (DView *)param.v[0]; }
    DCar *Car() { return (DCar *)param.v[2]; }
};

/* @implements 0x0f35c0 us _ZN7CamCtrl9CCamDammy3SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block (as the base camera). */
void CCamDammy::Set(const CamParam *p)
{
    CCamProto::Set(p);
}

/* @implements 0x0f35dc us _ZN7CamCtrl9CCamDammy5ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamDammy::Reset()
{
    CCamProto::Reset();
}

/* @implements 0x0f35f8 us _ZN7CamCtrl9CCamDammy8f_07f5e0EPi
   WHAT IT DOES: Starts the camera: nothing to do. */
void CCamDammy::f_07f5e0(int *arg)
{
}

/* @implements 0x0f3600 us _ZN7CamCtrl9CCamDammy8f_07f5e8Ev
   WHAT IT DOES: Steps the camera: nothing to do. */
void CCamDammy::f_07f5e8()
{
}

/* @implements 0x0f3608 us _ZN7CamCtrl9CCamDammy8f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamDammy::f_07f5f8()
{
}

/* @implements 0x0f3610 us _ZN7CamCtrl13CCamDammyEye18f_07f5e0EPi
   WHAT IT DOES: Starts the camera: clears the view's lens setting and marks it, clears the
   previous camera's view's setting, and sets the view's last two flags to 0 and 1. */
void CCamDammyEye1::f_07f5e0(int *arg)
{
    DView *o = (DView *)param.v[1];
    DView *v = (DView *)param.v[0];
    v->m660 = 0;
    v->m668 = 0;
    o->m660 = 0;
    v->m672 = 1;
    v->m664 = 1;
}

/* @draft 0x0f3634 us _ZN7CamCtrl13CCamDammyEye18f_07f5e8Ev
   WHAT IT DOES: Puts the camera on its view: the eye is a point 0.9 of the car's height up
   and 100 back (turned with the car's orientation) and the look angles come from the car's
   orientation turned a fixed angle about one axis; a 55 degree lens halved and its scale,
   and the car's setting, speed and the eye position are copied. If a previous view exists,
   it is set up as the mirror of this one (turned half a turn, eye raised by the screen's
   offset) with the screen's lens, aspect, far distance and clip rectangle. */
void CCamDammyEye1::f_07f5e8()
{
    Vec4 eye;
    Vec4 ofs(0.0f, Car()->m7680->m448 * 0.9f, -100.0f, 1.0f);
    Vec4 p(ofs.x, ofs.y + 0.0f, ofs.z, ofs.w);
    Vec4 t;
    f_09c720(&t, &Car()->q, &p);
    eye = t;
    eye.x += Car()->pos.x;
    eye.y += Car()->pos.y;
    eye.z += Car()->pos.z;
    Rot rot(0, 0, 0);
    M34 m;
    f_09ff44(&m);
    Angle a1;
    a1.f = 0.017444444f;
    f_099b98(&a1);
    f_0a082c(&m, a1, 1, 2);
    Angle a2;
    a2.f = 0;
    f_099b98(&a2);
    f_0a082c(&m, a2, 2, 0);
    m = Mul(FromQuat(Car()->q), m);
    Vec4 out;
    f_0a4160(&out, &m, 4);
    *(Vec4 *)&rot = out;
    DView *v = View();
    v->m608 = rot.r[0].a;
    v->m612 = rot.r[1].a.f;
    v->m616 = rot.r[2].a.f;
    v->eye.x = eye.x;
    v->eye.y = eye.y;
    v->eye.z = eye.z;
    float half = 0.5f;
    float lens = 0.9599311f;
    float l = lens * half;
    v->m480 = l;
    v->m496 = 1.0f / f_0cd3cc(l);
    DCar *c = Car();
    DView *w = View();
    int prev = param.v[1];
    w->m572 = c->m2212;
    w->m704 = c->m2144;
    w->m688.x = eye.x;
    w->m688.y = eye.y;
    w->m688.z = eye.z;
    w->m708 = lens;
    w->m744 = c->m2144;
    if (prev) {
        DView *q = (DView *)prev;
        DScreen *g = &D_23fefc;
        q->m608.f = w->m608.f + g->m24 / 180.0f * 3.14159f;
        q->m612 = w->m612 + 3.14159f;
        q->m616 = -w->m616;
        float lift = g->m40 * 1000.0f;
        DPos a = w->eye;
        DPos b = w->eye;
        float y = b.y + lift;
        DPos d = w->eye;
        q->eye.x = a.x;
        q->eye.y = y;
        q->eye.z = d.z;
        q->m480 = l;
        q->m496 = 1.0f / f_0cd3cc(l);
        c = Car();
        q = Prev();
        q->m572 = c->m2212;
        q->m704 = c->m2144;
        q->m744 = c->m2144;
        d = q->eye;
        q->m688 = d;
        q->m484 = (float)g->m12 / (float)g->m16 * g->m44;
        q->m488 = g->m28 * 1000.0f;
        q->m492 = g->m32 * 1000.0f;
        float l2 = g->m36 / 180.0f * 3.14159f * half;
        q->m480 = l2;
        float s = 1.0f / f_0cd3cc(l2);
        DView *r = Prev();
        int nw = -g->m12;
        int h = g->m16;
        int top = g->m20 + h / 2 + 1912;
        r->m504 = nw * r->m500;
        r->m512 = 2048;
        r->m516 = top;
        r->m508 = h;
        q->m496 = s;
        r->m532 = (float)(g->m16 / 2 + 5);
        r->m520 = (float)nw * half;
        r->m524 = (float)h * half;
        r->m528 = (float)(g->m12 / 2 + 5);
    }
}

/* @implements 0x0f3b88 us _ZN7CamCtrl13CCamDammyEye38f_07f5e0EPi
   WHAT IT DOES: Starts the camera: puts lens setting 1 on the view, sets its flags and
   marks the previous camera's view. */
void CCamDammyEye3::f_07f5e0(int *arg)
{
    DView *o = (DView *)param.v[1];
    DView *v = (DView *)param.v[0];
    v->m660 = 1;
    v->m672 = 1;
    o->m660 = -1;
    v->m664 = 1;
    v->m668 = 1;
}

/* @draft 0x0f3bb0 us _ZN7CamCtrl13CCamDammyEye38f_07f5e8Ev
   WHAT IT DOES: Puts the camera on its view: the eye is a point 800 above and 5000 along
   the car (turned with the car's orientation) and the look angles come from the car's
   orientation turned a fixed angle about one axis; a 55 degree lens halved and its scale,
   and the car's setting, speed and the eye position are copied.
   Remaining difference: (1) the stores of the two offset vectors (sp+16, sp+32) come out in
   another order (sched2 tie-break among independent stores); (2) rot.w's zero store is
   placed before the third angle's reload, retail loads first; (3) after the output copy
   into rot, the m608 store and the lens constant loads are scheduled differently. */
void CCamDammyEye3::f_07f5e8()
{
    Vec4 eye;
    Vec4 ofs(0.0f, Car()->m7680->m448 + 800.0f, 5000.0f, 1.0f);
    Vec4 p(ofs.x, ofs.y + 0.0f, ofs.z, ofs.w);
    Vec4 t;
    f_09c720(&t, &Car()->q, &p);
    eye = t;
    eye.x += Car()->pos.x;
    eye.y += Car()->pos.y;
    eye.z += Car()->pos.z;
    Rot rot(0, 0, 0);
    M34 m;
    f_09ff44(&m);
    Angle a1;
    a1.f = 0.017444444f;
    f_099b98(&a1);
    f_0a082c(&m, a1, 1, 2);
    Angle a2;
    a2.f = 0;
    f_099b98(&a2);
    f_0a082c(&m, a2, 2, 0);
    m = Mul(FromQuat(Car()->q), m);
    Vec4 out;
    f_0a4160(&out, &m, 4);
    *(Vec4 *)&rot = out;
    DView *v = View();
    v->m608 = rot.r[0].a;
    v->m612 = rot.r[1].a.f;
    v->m616 = rot.r[2].a.f;
    v->eye.x = eye.x;
    v->eye.y = eye.y;
    v->eye.z = eye.z;
    float lens = 0.9599311f;
    v->m480 = lens * 0.5f;
    v->m496 = 1.0f / f_0cd3cc(v->m480);
    DCar *c = Car();
    DView *w = View();
    w->m572 = c->m2212;
    w->m704 = c->m2144;
    w->m688.x = eye.x;
    w->m688.y = eye.y;
    w->m688.z = eye.z;
    w->m708 = lens;
    w->m744 = c->m2144;
}

/* @implements 0x0f3e88 us _ZN7CamCtrl9CCamDammyD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0f3e98 us _ZN7CamCtrl9CCamDammyD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */
/* @implements 0x0f3ec0 us _ZN7CamCtrl13CCamDammyEye1D1Ev
   WHAT IT DOES: Complete object destructor of the first eye camera (inline). */
/* @implements 0x0f3ed0 us _ZN7CamCtrl13CCamDammyEye1D0Ev
   WHAT IT DOES: Deleting destructor of the first eye camera. */
/* @implements 0x0f3ef8 us _ZN7CamCtrl13CCamDammyEye3D1Ev
   WHAT IT DOES: Complete object destructor of the third eye camera (inline). */
/* @implements 0x0f3f08 us _ZN7CamCtrl13CCamDammyEye3D0Ev
   WHAT IT DOES: Deleting destructor of the third eye camera. */

}
