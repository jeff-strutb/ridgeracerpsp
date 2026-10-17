/* The fixed point replay camera, CamCtrl::CCamBurial (retail 0x0f27b4 to 0x0f2f5c): a camera
   placed at one of the course's fixed camera points (a table of 60-byte points: the camera
   position, the point it looks at and the lens angle) that turns to follow the nearest car
   and zooms on it. Its out of line virtual methods, the static tuning values built at start
   up from the speed unit, and the inline destructors and show method emitted with its
   vtable. */

/* The speed unit conversion and the camera tuning set elsewhere. */
extern float D_1d5d94;
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
};

/* A car as the camera reads it. */
struct BCar {
    char p0[144];
    Vec4 pos;
    char p160[1984];
    const Vec4 &Pos() const { return pos; }
    float m2144;  /* distance along the course */
};

struct V3 {
    float x, y, z;
};

/* A fixed camera point (60 bytes). */
struct BPoint {
    V3 pos;
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

/* The view the camera drives. */
struct BView {
    V3 pos;
    char p12[468];
    float m480;   /* lens angle */
    char p484[4];
    float m488;   /* far distance */
    char p492[4];
    float m496;   /* lens scale */
    char p500[108];
    V3 m608;       /* the point looked at */
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[28];
    float m704;
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

/* A sub-object of the camera with a reset method elsewhere. */
struct BTimer {
    void f_0f3f30();
    int m0;
};

}

extern CamCtrl::MapMgr D_23c820;

extern "C" {
void f_0823f0(int n, CamCtrl::BView *v);
float f_0cd3cc(float a);
float f_0a65c4(CamCtrl::Vec4 *v);
}

namespace CamCtrl {

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

    BPoint *table;
    BPoint *cur;
    BTimer timer;
    char p40[192];
    float m232[2];
    float m240;
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

/* @draft 0x0f2814 us _ZN7CamCtrl10CCamBurial8f_07f5e0EPi
   WHAT IT DOES: Starts the camera at point *arg: marks the view, resets the timer, puts lens
   setting 2 on the view, places it at the point with the point's lens angle (and its scale),
   aims it at the point's target with a far distance of 300 and the area under the point,
   marks the previous camera's view, clears the zoom, and finds the course area around the
   followed car (1000 either side of it) that the point looks onto.
   Remaining difference: in the copy of the point's target, retail loads y before z (f1, f2);
   here z is loaded first. Statement orders, a struct copy and a fresh pointer do not change
   it. */
void CCamBurial::f_07f5e0(int *arg)
{
    BView *v = View();
    v->m668 = 1;
    v->m672 = 0;
    timer.f_0f3f30();
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
    t->m660 = 2;
    u->m704 = ar;
    t->m664 = 1;
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
