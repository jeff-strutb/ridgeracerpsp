/* The on board replay camera, CamCtrl::CCamOnBoard (retail 0x0f42f8 to 0x0f4a68): a camera
   fixed to the followed car at one of ten mount points (a start up table of 32-byte points
   at D_27ecfc), swaying with the camera sway. Its out of line virtual methods and the
   inline destructors emitted with its vtable. */

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

/* A car as the camera reads it. */
struct OCar {
    char p0[144];
    Vec4 pos;
    Vec4 m160;        /* the velocity */
    char p176[32];
    float q[4];       /* 208, the orientation */
    char p224[1920];
    float m2144;
    char p2148[64];
    int m2212;        /* the car's setting */
};

/* A mount point (32 bytes): its place on the car, its turn, its lens and whether it sways. */
struct OPoint {
    float pos[3];
    float ang[3];
    float fov;
    short lens;
    short m30;
};

/* The view the camera drives. */
struct OView {
    Vec4 eye;
    char p16[464];
    float m480;   /* lens angle */
    char p484[4];
    float m488;   /* far distance */
    char p492[4];
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
    Vec4 m688;    /* the eye, kept */
    float m704;
    float m708;
    char p712[32];
    float m744;
};

/* The camera sway (src/race/CamSway.cpp). */
struct CamSway {
    void f_0f3f30();
    void f_0f411c(float t);
    char m0[196];
    float m196;   /* the sway */
    float m200;
};

}

extern CamCtrl::OPoint D_27ecfc[10];
extern float D_27ecf4;
extern float D_27ecf8;

extern "C" {
void f_0823f0(int n, CamCtrl::OView *v);
float f_0cd3cc(float a);
void f_099b98(CamCtrl::Angle *);
void f_09c720(CamCtrl::Vec4 *o, void *q, CamCtrl::Vec4 *v);
void f_09ff44(CamCtrl::M34 *m);
void f_0a082c(CamCtrl::M34 *m, CamCtrl::Angle a, int i, int j);
void f_09fd1c(CamCtrl::M34 *m, void *q);
void f_0a12ac(CamCtrl::M34 *o, CamCtrl::M34 *a, CamCtrl::M34 *b);
void f_0a4160(CamCtrl::Vec4 *o, CamCtrl::M34 *m, int n);
float f_0a65c4(const void *v);
}

/* The time scale, the degree, the sway speed and the sway unit. */
extern float D_1d5d98;
extern float D_1d5da4;
extern float D_1d5da8;
extern float D_1d5db0;
/* Run time units per frame. */
extern float D_1d5d94;

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

}

namespace CamCtrl {

class CCamOnBoard : public CCamProto {
public:
    virtual ~CCamOnBoard() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f8();

    OView *View() { return (OView *)param.v[0]; }
    OCar *Car() { return (OCar *)param.v[2]; }

    int m28;
    Vec4 m32;   /* the car's position when the camera started */
    int m48;
    OPoint *cur;
    CamSway sway;
    float m260;
};

/* @implements 0x0f42f8 us _ZN7CamCtrl11CCamOnBoard3SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block (as the base camera). */
void CCamOnBoard::Set(const CamParam *p)
{
    CCamProto::Set(p);
}

/* @implements 0x0f4314 us _ZN7CamCtrl11CCamOnBoard5ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamOnBoard::Reset()
{
    CCamProto::Reset();
}

/* @draft 0x0f4330 us _ZN7CamCtrl11CCamOnBoard8f_07f5e0EPi
   WHAT IT DOES: Starts the camera at mount point *arg: resets the sway, puts the point's lens
   on the view (lens setting 3), notes the car's position, sets the point's lens angle (and
   its scale) and a far distance of 300, numbers the view's setting after the point, clears
   the zoom and marks the previous camera's view.
   Remaining difference: retail loads the far distance constant before the previous view
   pointer; here the pointer load comes first (two words). Reading the pointer after the
   m660 store instead keeps it below that store (it may alias) and costs 14 words. */
void CCamOnBoard::f_07f5e0(int *arg)
{
    cur = &D_27ecfc[*arg];
    sway.f_0f3f30();
    OView *v = View();
    v->m672 = 1;
    v->m668 = cur->lens;
    f_0823f0(3, v);
    Vec4 *pp = &((OCar *)param.v[2])->pos;
    OPoint *e = cur;
    OView *w = View();
    m32 = *pp;
    w->m480 = e->fov * 0.5f;
    w->m496 = 1.0f / f_0cd3cc(w->m480);
    OView *t = View();
    t->m664 = 1;
    t->m488 = 300.0f;
    OView *o = (OView *)param.v[1];
    t->m660 = ((*arg + 1) << 16) | 3;
    m260 = 0;
    if (o)
        o->m660 = -1;
}

/* @draft 0x0f4444 us _ZN7CamCtrl11CCamOnBoard8f_07f5e8Ev
   WHAT IT DOES: Puts the camera on its view each frame: the eye is the mount point turned
   with the car's orientation and added to the car's position; the view is turned by the
   point's angles (plus, for a swaying point, the sway scaled by the car's speed between the
   two tuning speeds, never easing off once reached) and then by the car's orientation. It
   notes the eye, sets the lens setting, the look angles, the car's setting, the eye (and its
   kept copy), the car's distance and twice the lens angle.
   Remaining difference: frame, calls and the matrix copy match. Retail loads the mount
   point's x, y, z in order (here z first), adds the car's position to the eye one component
   at a time through the stack (here the three car loads are hoisted), and schedules the
   view stores at the end differently. */
void CCamOnBoard::f_07f5e8()
{
    float b = 0.0f;
    float a = b;
    OPoint *e = cur;
    Vec4 eye(e->pos[0], e->pos[1], e->pos[2], 1.0f);
    Vec4 t;
    f_09c720(&t, Car()->q, &eye);
    eye = t;
    OCar *c = Car();
    eye.x += c->pos.x;
    eye.y += c->pos.y;
    eye.z += c->pos.z;
    if (cur->m30 != 0) {
        a = f_0a65c4(&c->m160) - D_27ecf8;
        if (a < 0.0f) {
            a = 0.0f;
        } else {
            a = a / (D_27ecf4 - D_27ecf8);
            if (1.0f < a)
                a = 1.0f;
            if (m260 < a)
                m260 = a;
        }
        sway.f_0f411c(a * D_1d5da8 * D_1d5d98 * 60.0f);
        float k = (a + 0.01f) * 3.14159274f * D_1d5db0;
        a = k * 1.2f * sway.m196;
        b = k * 0.6f * sway.m200;
    }
    M34 m;
    f_09ff44(&m);
    f_0a082c(&m, Rad(cur->ang[2]).a, 0, 1);
    f_0a082c(&m, Rad(a + cur->ang[0]).a, 1, 2);
    f_0a082c(&m, Rad(b + cur->ang[1]).a, 2, 0);
    m = Mul(FromQuat(Car()->q), m);
    OView *v = View();
    v->m672 = 1;
    v->m668 = cur->lens;
    m32 = eye;
    Vec4 out;
    f_0a4160(&out, &m, 4);
    v->m608 = out.x;
    v->m612 = out.y;
    v->m616 = out.z;
    OView *w = View();
    OCar *d = Car();
    w->m572 = d->m2212;
    w->eye.x = eye.x;
    w->eye.y = eye.y;
    w->eye.z = eye.z;
    w->m688 = w->eye;
    w->m704 = d->m2144;
    w->m708 = w->m480 + w->m480;
    w->m744 = d->m2144;
}

/* @implements 0x0f47bc us _ZN7CamCtrl11CCamOnBoard8f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamOnBoard::f_07f5f8()
{
}

}

/* The speeds over which the swaying mounts reach full sway, in run time units. */
float D_27ecf4 = D_1d5d94 * 350.0f;
float D_27ecf8 = D_1d5d94 * 150.0f;

/* The ten mount points: in front, behind, the four sides at three heights and two far
   above, all with a 38 degree lens. */
CamCtrl::OPoint D_27ecfc[10] = {
    {{0.0f, 600.0f, -500.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * 0.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{0.0f, 600.0f, 500.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * 180.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{800.0f, 300.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * -90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{-800.0f, 300.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * 90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{800.0f, 1000.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * -90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{-800.0f, 1000.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * 90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{800.0f, 2000.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * -90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{-800.0f, 2000.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * 90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{800.0f, 5000.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * -90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
    {{-800.0f, 5000.0f, 0.0f}, {D_1d5da4 * 0.0f, D_1d5da4 * 90.0f, D_1d5da4 * 0.0f}, D_1d5da4 * 38.0f, 0, 1},
};

/* @draft 0x0f47c4 us __static_initialization_and_destruction_0
   WHAT IT DOES: Converts the sway speeds and builds the mount point table at start up.
   Remaining difference: same size and stores; the constant loads and stores are scheduled
   in another order. */
/* @implements 0x0f4a10 us _GLOBAL__I
   WHAT IT DOES: Runs the above. */

namespace CamCtrl {

/* @implements 0x0f4a30 us _ZN7CamCtrl11CCamOnBoardD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0f4a40 us _ZN7CamCtrl11CCamOnBoardD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */

}
