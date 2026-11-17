/* The fixed point replay camera, CamCtrl::CCamBurial (retail 0x0f27b4 to 0x0f2f5c): a camera
   placed at one of the course's fixed camera points (a table of 60-byte points: the camera
   position, the point it looks at and the lens angle) that turns to follow the nearest car
   and zooms on it. Its out of line virtual methods, the static tuning values built at start
   up from the speed unit, and the inline destructors and show method emitted with its
   vtable. */

/* The speed unit conversion and the camera tuning set elsewhere. */
extern float D_1d5d94;
extern float D_1d5d74; /* how near a car must be to the point to zoom */
extern float D_1d5d78; /* the distance of full zoom */
extern float D_1d5d7c; /* the zoom curve */
extern float D_1d5d80; /* the sway's time step */
extern float D_1d5d84; /* the zoom's decay */
extern float D_1d5d88; /* the sway's angle scale */
extern float D_1d5d98;
extern float D_27ecec, D_27ecf0;
extern float D_1d5d8c; /* how close a car must come to a point's camera to be in view */

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
    Vec4(float a, float b, float c) : x(a), y(b), z(c), w(1.0f) {}
    void operator-=(const Vec4 &o)
    {
        x -= o.x;
        y -= o.y;
        z -= o.z;
    }
    Vec4 operator-(const Vec4 &o) const { return Vec4(x - o.x, y - o.y, z - o.z); }
};

/* A car as the camera reads it. */
struct BCar {
    char p0[144];
    Vec4 pos;
    Vec4 m160;    /* the velocity */
    char p176[1968];
    const Vec4 &Pos() const { return pos; }
    float m2144;  /* distance along the course */
    char p2148[64];
    int m2212;    /* the car's setting */
};

struct V3 {
    float x, y, z;
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

/* A position as the point table keeps it. */
struct P3 {
    float x, y, z;
};

/* A fixed camera point (60 bytes). */
struct BPoint {
    P3 pos;
    V3 at;
    float fov;
    char p28[24];
    int m52;      /* the point is in use */
    char p56[4];
};

/* The camera's parameter block: the view, the previous camera's view, the car and the
   point table (a header whose +20 word is the table's offset from the header). */
struct BHeader {
    char p0[20];
    BPoint *off;
};
struct BParam {
    CamParam base;
    BHeader *table;
};

/* Four words of a view, copied whole. */
struct Quad {
    float x, y, z, w;
};

/* The view the camera drives. */
struct BView {
    union {
        P3 pos;
        Quad eye;
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
    V3 m608;       /* the look angles */
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    Quad m688;     /* the eye, kept */
    float m704;
    float m708;
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    int f_0e23d0(float x, float z);
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

}

/* The replay cameras' sway (src/race/CamSway.cpp). */
union SwayAngle {
    float f;
    int i;
};
struct Arm {
    SwayAngle a;
    float speed;
    float len;
};
struct CamSway {
    int n;
    Arm arm[16];
    float m196;
    float m200;

    void f_0f3f30();
    void f_0f411c(float t);
};

extern CamCtrl::MapMgr D_23c820;

extern "C" {
void f_0823f0(int n, CamCtrl::BView *v);
CamCtrl::Angle *f_099b98(CamCtrl::Angle *);
CamCtrl::M34 *f_09ff44(CamCtrl::M34 *m);
CamCtrl::M34 *f_0a082c(CamCtrl::M34 *m, CamCtrl::Angle a, int i, int j);
void f_0a4160(CamCtrl::Vec4 *o, CamCtrl::M34 *m, int n);
float f_0cd3cc(float a);
float f_0a65c4(CamCtrl::Vec4 *v);
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

class CCamBurial : public CCamProto {
public:
    virtual ~CCamBurial() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f0() {}
    virtual void f_07f5f8();
    int f_0f2de8();

    BView *View() { return (BView *)param.v[0]; }
    BCar *Car() { return (BCar *)param.v[2]; }
    BCar **Cars() { return (BCar **)param.v[3]; }

    BPoint *table;
    BPoint *cur;
    CamSway sway;   /* 36 */
    float m240;     /* the zoom */
    char p244[4];
    float m248;
};

/* @implements 0x0f27b4 us _ZN7CamCtrl10CCamBurial3SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block and finds the point table from its header; no
   point is chosen yet. */
void CCamBurial::Set(const CamParam *p)
{
    CCamProto::Set(p);
    BHeader *h = ((const BParam *)p)->table;
    table = (BPoint *)((int)h->off + (int)h);
    cur = 0;
}

/* @implements 0x0f27f8 us _ZN7CamCtrl10CCamBurial5ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamBurial::Reset()
{
    CCamProto::Reset();
}

/* @implements 0x0f2814 us _ZN7CamCtrl10CCamBurial8f_07f5e0EPi
   WHAT IT DOES: Starts the camera at point *arg: marks the view, resets the sway, puts lens
   setting 2 on the view, places it at the point with the point's lens angle (and its scale),
   gives it the point's look angles with a far distance of 300 and the area under the point,
   marks the previous camera's view, clears the zoom, and finds the course area around the
   followed car (1000 either side of it) that the point looks onto. */
void CCamBurial::f_07f5e0(int *arg)
{
    BView *v = View();
    v->m668 = 1;
    v->m672 = 0;
    sway.f_0f3f30();
    cur = &table[*arg];
    f_0823f0(2, View());
    BPoint *e = cur;
    BView *w = View();
    w->pos.x = e->pos.x;
    w->pos.y = e->pos.y;
    w->pos.z = e->pos.z;
    w->m480 = e->fov * 0.5f * 0.5f;
    w->m496 = 1.0f / f_0cd3cc(w->m480);
    CourseAreas *areas = D_23c820.Areas();
    BPoint *f = cur;
    BView *u = View();
    u->m608.x = f->at.x;
    u->m608.y = f->at.y;
    u->m608.z = f->at.z;
    u->m488 = 300.0f;
    int ar = areas->f_0e23d0(f->pos.x, f->pos.z);
    BView *t = View();
    BView *o = (BView *)param.v[1];
    u->m704 = ar;
    t->m664 = 1;
    t->m660 = 2;
    m240 = 0;
    if (o)
        o->m660 = -1;
    int d = (int)((BCar *)param.v[2])->m2144;
    int lo = d - 1000;
    int hi = d + 1000;
    lo = areas->f_0e2690(lo);
    hi = areas->f_0e2690(hi);
    int out[4];
    m248 = areas->f_0e2448(lo, hi, cur->pos.x, cur->pos.z);
    areas->f_0e2f9c((int)m248, out, &m248, cur->pos.x, cur->pos.z);
}

/* @implements 0x0f29e0 us _ZN7CamCtrl10CCamBurial8f_07f5e8Ev
   WHAT IT DOES: Steps the camera: finds the car nearest the point's camera; when it is
   nearer than the zoom distance, the zoom target grows as it comes closer (full inside the
   full zoom distance), scaled by the car's speed above a threshold, and the zoom keeps the
   larger of it and its current value. The sway steps, and the view is placed at the point,
   turned by the point's angles plus the sway (stronger with more zoom), with the point's
   lens halved twice and its scale; the zoom then decays, and the car's setting, the lens
   span and the eye are copied to the view. */
void CCamBurial::f_07f5e8()
{
    Vec4 p, d;
    BPoint *e = cur;
    Vec4 at(e->pos.x, e->pos.y, e->pos.z);
    float best = D_1d5d74;
    BCar *near = Car();
    for (int i = 0; i < param.v[4]; i++) {
        p = Cars()[i]->Pos();
        d = p - at;
        float l = f_0a65c4(&d);
        if (l < best) {
            best = l;
            near = Cars()[i];
        }
    }
    if (best < D_1d5d74) {
        best -= D_1d5d78;
        if (best < 0.0f) {
            best = 1.0f;
        } else {
            best /= D_1d5d74 - D_1d5d78;
            best = 1.0f - best;
            best *= D_1d5d7c * best;
        }
        float r = f_0a65c4(&near->m160) - D_27ecf0;
        if (!(r < 0.0f)) {
            r /= D_27ecec - D_27ecf0;
            if (r > 1.0f)
                r = 1.0f;
            best *= r;
            if (best > 1.0f)
                best = 1.0f;
            if (m240 < best)
                m240 = best;
        }
    }
    Vec4 eye(cur->pos.x, cur->pos.y, cur->pos.z);
    float *sw = &sway.m196;
    sway.f_0f411c(D_1d5d80 * D_1d5d98);
    float amp = (m240 + 0.01f) * 3.1415927f * D_1d5d88;
    M34 m;
    f_09ff44(&m);
    f_0a082c(&m, Rad(cur->at.z).a, 0, 1);
    f_0a082c(&m, Rad(amp * sway.m196 + cur->at.x).a, 1, 2);
    f_0a082c(&m, Rad(amp * sw[1] + cur->at.y).a, 2, 0);
    Vec4 out;
    BView *v = View();
    f_0a4160(&out, &m, 4);
    BPoint *g = cur;
    v->m608.x = out.x;
    v->m608.y = out.y;
    v->m608.z = out.z;
    m240 *= D_1d5d84;
    BView *u = View();
    u->pos.x = eye.x;
    u->pos.y = eye.y;
    u->pos.z = eye.z;
    u->m480 = g->fov * 0.5f * 0.5f;
    u->m496 = 1.0f / f_0cd3cc(u->m480);
    BView *w = View();
    BCar *c = Car();
    w->m572 = c->m2212;
    w->m688 = w->eye;
    w->m708 = w->m480 + w->m480;
}

/* @implements 0x0f2de0 us _ZN7CamCtrl10CCamBurial8f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamBurial::f_07f5f8()
{
}

/* @implements 0x0f2de8 us _ZN7CamCtrl10CCamBurial8f_0f2de8Ev
   WHAT IT DOES: Returns 1 when a point is chosen, in use, and the followed car is closer to
   its camera than the in-view distance. */
int CCamBurial::f_0f2de8()
{
    BPoint *e = cur;
    if (e && e->m52) {
        Vec4 p = ((BCar *)param.v[2])->Pos();
        Vec4 q(e->pos.x, e->pos.y, e->pos.z);
        p -= q;
        if (f_0a65c4(&p) < D_1d5d8c)
            return 1;
    }
    return 0;
}

}

/* The camera's speed tuning, in run time units. */
float D_27ecec = D_1d5d94 * 105.0f;
float D_27ecf0 = D_1d5d94 * 75.0f;

/* @implements 0x0f2eac us __static_initialization_and_destruction_0
   WHAT IT DOES: Converts the camera's tuning values at start up. */
/* @implements 0x0f2efc us _GLOBAL__I
   WHAT IT DOES: Runs the above. */

namespace CamCtrl {
/* @implements 0x0f2f1c us _ZN7CamCtrl10CCamBurialD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0f2f2c us _ZN7CamCtrl10CCamBurialD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */
/* @implements 0x0f2f54 us _ZN7CamCtrl10CCamBurial8f_07f5f0Ev
   WHAT IT DOES: Shows the camera: nothing to do (inline, emitted with the vtable). */
}
