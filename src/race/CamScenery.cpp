/* The scenery replay camera, CamCtrl::CCamScenery (retail 0x0f4a68 to 0x0f52a4): a camera at
   one of the course's scenery points (a table of 152-byte points) with two sways, looking at
   the point's target. Its out of line virtual methods and the inline destructors and show
   method emitted with its vtable. */

namespace CamCtrl {
union Angle;
}
extern "C" void f_099b98(CamCtrl::Angle *);

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

struct V3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

/* A car as the camera reads it. */
struct SCar {
    char p0[2144];
    float m2144;  /* distance along the course */
    char p2148[64];
    int m2212;    /* the car's setting */
};

/* A scenery point (152 bytes): the camera moves from pos to pos1 and its target from at to
   at1 over a timed move (start, then accel, cruise and decel frames), with the lens going
   from fov to fov1. */
struct SPoint {
    V3 pos;
    V3 pos1;
    V3 at;
    V3 at1;
    float ang[3];  /* the fixed turn */
    V3 base;       /* the kept eye, unless zero */
    float fov;
    float fov1;
    float m80;     /* the sways' time scale */
    float m84;     /* sway amplitudes */
    float m88;
    float m92;
    float m96;     /* the view's distance, unless zero */
    int start;
    int accel;
    int cruise;
    int decel;
    char p116[4];
    float m120;
    char p124[28];
};

/* The table header: its +24 word is the table's offset from the header. */
struct SHeader {
    char p0[24];
    SPoint *off;
};
struct SParam {
    CamParam base;
    SHeader *table;
};

/* The view the camera drives. */
struct SView {
    union {
        V3 pos;
        Vec4 eye;   /* the same words copied whole */
    };
    char p16[464];
    float m480;   /* lens angle */
    char p484[4];
    float m488;   /* far distance */
    char p492[4];
    float m496;   /* lens scale */
    char p500[72];
    int m572;
    char p576[32];
    V3 m608;      /* the point looked at */
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    Vec4 m688;    /* the eye, kept */
    float m704;
    float m708;
    float m712;
    char p716[20];
    int m736;
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    int f_0e2690(int pos);
    int f_0e2448(int a, int b, float x, float z);
    void f_0e2f9c(int area, int *out, float *at, float x, float z);
    int m0;
};
struct MapMgr {
    CourseAreas *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas m12240;
};

/* The camera sway (src/race/CamSway.cpp). */
struct CamSway {
    void f_0f3f30();
    void f_0f411c(float t);
    char m0[196];
    float m196;   /* the sway */
    float m200;
};

/* A 3x4 matrix. */
struct M34 {
    float m[12];
};

/* An angle wrapped into range. */
struct Rad {
    Angle a;
    Rad(float f)
    {
        a.f = f;
        f_099b98(&a);
    }
};

/* Rotation angles and their axis order. */
struct Rot {
    Rad r[3];
    int order;
};

}

extern "C" {
CamCtrl::Rot f_0825dc(CamCtrl::Vec4 v);
void f_09f92c(CamCtrl::M34 *m, const CamCtrl::Rot &e);
CamCtrl::M34 *f_0a6aec(CamCtrl::M34 *d, const CamCtrl::M34 *a, const CamCtrl::M34 *b);
void f_0a4160(CamCtrl::Vec4 *o, const CamCtrl::M34 *m, int order);
}

/* The time scale, pi and the sway's least amplitude. */
extern float D_1d5d98;
extern float D_1d5d90;
extern float D_1d5db4;

namespace CamCtrl {

/* The rotation as a matrix. */
inline M34 FromRot(const Rot &e)
{
    M34 m;
    f_09f92c(&m, e);
    return m;
}

/* The product of two matrices. */
inline M34 Mul(const M34 &a, const M34 &b)
{
    M34 r;
    f_0a6aec(&r, &a, &b);
    return r;
}

/* Puts the eye on a view. */
inline void SetEye(SView *v, const Vec4 &eye)
{
    v->pos.x = eye.x;
    v->pos.y = eye.y;
    v->pos.z = eye.z;
}

inline float Lerp(float a, float b, float t)
{
    return (b - a) * t + a;
}

}

extern CamCtrl::MapMgr D_23c820;

extern "C" {
void f_0823f0(int n, CamCtrl::SView *v);
float f_0cd3cc(float a);
}

namespace CamCtrl {

class CCamScenery : public CCamProto {
public:
    virtual ~CCamScenery() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f0() {}
    virtual void f_07f5f8();

    SView *View() { return (SView *)param.v[0]; }

    SPoint *table;
    SPoint *cur;
    CamSway sway;
    CamSway sway2;
    int m444;
    float m448;
};

/* @implements 0x0f4a68 us _ZN7CamCtrl11CCamScenery3SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block and finds the point table from its header. */
void CCamScenery::Set(const CamParam *p)
{
    CCamProto::Set(p);
    SHeader *h = ((const SParam *)p)->table;
    table = (SPoint *)((int)h->off + (int)h);
}

/* @implements 0x0f4aa8 us _ZN7CamCtrl11CCamScenery5ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamScenery::Reset()
{
    CCamProto::Reset();
}

/* @draft 0x0f4ac4 us _ZN7CamCtrl11CCamScenery8f_07f5e0EPi
   WHAT IT DOES: Starts the camera at point *arg: marks the view, resets both sways and runs
   the first ahead by 50, puts lens setting 5 on the view, places it at the point with the
   point's lens angle (and its scale), aims it at the point's target, finds the course area
   around the followed car (1000 either side of it) that the point looks onto, sets a far
   distance of 3500, marks the previous camera's view and takes the point's view setting.
   Remaining difference: allocation of the map manager's area pointer. Retail builds it in the
   sway pointer's saved register (its high half in the sway step call's slot) and the view in
   s1; here it gets s1 and the view s0. The code is otherwise the same.
   2026-11-16: retail's lui s0 sits in the f_0f411c jal slot after move a0,s0, so the area
   pointer's high half is set before that call in retail's RTL and shares s0 with &sway.
   Tried the areas line above sway.f_0f411c(50.0f): 57 words (the whole pointer is live
   across the call and takes a new saved register); reverted. */
void CCamScenery::f_07f5e0(int *arg)
{
    SView *v = View();
    v->m668 = 1;
    v->m672 = 0;
    sway.f_0f3f30();
    sway2.f_0f3f30();
    sway.f_0f411c(50.0f);
    cur = &table[*arg];
    CourseAreas *areas = D_23c820.Areas();
    f_0823f0(5, View());
    SPoint *e = cur;
    SView *w = View();
    w->pos.x = e->pos.x;
    w->pos.y = e->pos.y;
    w->pos.z = e->pos.z;
    w->m480 = e->fov * 0.5f * 0.5f;
    w->m496 = 1.0f / f_0cd3cc(w->m480);
    SPoint *f = cur;
    SView *u = View();
    SCar *car = (SCar *)param.v[2];
    u->m608.x = f->at.x;
    u->m608.y = f->at.y;
    u->m608.z = f->at.z;
    int d = (int)car->m2144;
    int lo = d - 1000;
    int hi = d + 1000;
    lo = areas->f_0e2690(lo);
    hi = areas->f_0e2690(hi);
    m448 = areas->f_0e2448(lo, hi, cur->pos.x, cur->pos.z);
    SView *t = View();
    SView *o = (SView *)param.v[1];
    t->m664 = 1;
    t->m488 = 3500.0f;
    m444 = 0;
    t->m660 = 5;
    if (o)
        o->m660 = -1;
    t->m736 = 0;
    t->m712 = cur->m120;
}

/* @draft 0x0f4c7c us _ZN7CamCtrl11CCamScenery8f_07f5e8Ev
   WHAT IT DOES: Steps the camera by 5 frames along the point's timed move: the share of the
   move done (eased in over the accel frames, linear while cruising, eased out over the decel
   frames) places the eye between the point's two positions, its target between the two
   targets and the lens between the two angles. The view is aimed along eye to target, swayed
   by the two sways (stronger while moving) and turned by the point's fixed angles, the eye is
   kept (or the point's base eye), the view's distance is the car's (or the point's), and the
   course area under the eye is updated.
   Remaining difference: retail keeps the not-started case as the fall-through and moves the
   ramp's four arms after the epilogue; here ce2 (find_if_case_1) hoists the not-started
   arm's zero into the test block and inverts the branch, so the ramp falls through and every
   later word is displaced. The frame is 16 bytes larger, and retail reloads the eye's y and z
   from the stack after storing the view's x (the eye local may alias the view there); the
   call sequence, the matrix products and their copy loops, and the tail match. */
void CCamScenery::f_07f5e8()
{
    float k = 0.0f;
    float f;
    m444 += 5;
    SPoint *e = cur;
    float total = (float)(e->accel + e->decel) * 0.5f + (float)e->cruise;
    if (m444 <= e->start) {
        f = 0.0f;
    } else if (m444 <= e->start + e->accel) {
        k = (float)(m444 - e->start) / (float)e->accel;
        f = k * k * 0.5f * (float)e->accel / total;
    } else if (m444 <= e->start + e->accel + e->cruise) {
        f = (float)(m444 - e->start - e->accel) / (float)e->cruise;
        k = 1.0f;
        f = ((float)e->accel * 0.5f + f * (float)e->cruise) / total;
    } else if (m444 <= e->start + e->accel + e->cruise + e->decel) {
        float u = (float)(m444 - e->start - e->accel - e->cruise) / (float)e->decel;
        k = 1.0f - u;
        f = ((float)e->accel * 0.5f + (float)e->cruise +
             (float)e->decel * 0.5f * (1.0f - k * k)) / total;
    } else {
        f = 1.0f;
    }
    float *sw = &sway2.m196;
    SView *v = View();
    float amp = D_1d5db4 + (1.0f - D_1d5db4) * k;
    v->m480 = Lerp(e->fov, e->fov1, f) * 0.5f * 0.5f;
    v->m496 = 1.0f / f_0cd3cc(v->m480);
    SPoint *c = cur;
    SView *u = View();
    Vec4 p;
    p.x = Lerp(c->pos.x, c->pos1.x, f);
    p.y = Lerp(c->pos.y, c->pos1.y, f);
    p.z = Lerp(c->pos.z, c->pos1.z, f);
    SetEye(u, p);
    Vec4 d;
    d.x = Lerp(c->at.x, c->at1.x, f);
    d.y = Lerp(c->at.y, c->at1.y, f);
    d.z = Lerp(c->at.z, c->at1.z, f);
    d.x -= p.x;
    d.y -= p.y;
    d.z -= p.z;
    Rot r = f_0825dc(d);
    M34 m = FromRot(r);
    sway2.f_0f411c(cur->m80 * D_1d5d98);
    r.r[0] = Rad(amp * cur->m88 * sway2.m196 * 16.0f * D_1d5d90 * 3.0517578125e-05f);
    r.r[1] = Rad(amp * cur->m84 * sw[1] * 16.0f * D_1d5d90 * 3.0517578125e-05f);
    sway.f_0f411c(cur->m80 * D_1d5d98);
    r.r[2] = Rad(amp * cur->m92 * sway.m196 * 16.0f * D_1d5d90 * 3.0517578125e-05f);
    m = Mul(m, FromRot(r));
    r.r[0] = Rad(cur->ang[0]);
    r.r[1] = Rad(cur->ang[1]);
    r.r[2] = Rad(cur->ang[2]);
    m = Mul(m, FromRot(r));
    Vec4 out;
    SView *w = View();
    f_0a4160(&out, &m, 4);
    SPoint *g = cur;
    w->m608.x = out.x;
    w->m608.y = out.y;
    w->m608.z = out.z;
    SView *t = View();
    if (g->base.x == 0.0f) {
        t->m688 = t->eye;
    } else {
        t->m688.x = g->base.x;
        t->m688.y = g->base.y;
        t->m688.z = g->base.z;
    }
    SCar *car = (SCar *)param.v[2];
    if (g->m96 == 0.0f)
        t->m704 = car->m2144;
    else
        t->m704 = g->m96;
    t->m572 = car->m2212 + 1;
    t->m708 = t->m480 + t->m480;
    {
        int area[2];
        D_23c820.Areas()->f_0e2f9c((int)m448, area, &m448, p.x, p.z);
    }
}

/* @implements 0x0f525c us _ZN7CamCtrl11CCamScenery8f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamScenery::f_07f5f8()
{
}

/* @implements 0x0f5264 us _ZN7CamCtrl11CCamSceneryD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0f5274 us _ZN7CamCtrl11CCamSceneryD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */
/* @implements 0x0f529c us _ZN7CamCtrl11CCamScenery8f_07f5f0Ev
   WHAT IT DOES: Shows the camera: nothing to do (inline, emitted with the vtable). */

}
