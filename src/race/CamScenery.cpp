/* The scenery replay camera, CamCtrl::CCamScenery (retail 0x0f4a68 to 0x0f52a4): a camera at
   one of the course's scenery points (a table of 152-byte points) with two sways, looking at
   the point's target. Its out of line virtual methods and the inline destructors and show
   method emitted with its vtable. */

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

/* A car as the camera reads it. */
struct SCar {
    char p0[2144];
    float m2144;  /* distance along the course */
};

/* A scenery point (152 bytes). */
struct SPoint {
    V3 pos;
    char p12[12];
    V3 at;
    char p36[36];
    float fov;
    char p76[44];
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
    V3 pos;
    char p12[468];
    float m480;   /* lens angle */
    char p484[4];
    float m488;   /* far distance */
    char p492[4];
    float m496;   /* lens scale */
    char p500[108];
    V3 m608;      /* the point looked at */
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[36];
    float m712;
    char p716[20];
    int m736;
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    int f_0e2690(int pos);
    int f_0e2448(int a, int b, float x, float z);
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
    char m0[204];
};

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
   s1; here it gets s1 and the view s0. The code is otherwise the same. */
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
