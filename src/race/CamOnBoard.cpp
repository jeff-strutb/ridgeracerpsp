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
};

/* A car as the camera reads it. */
struct OCar {
    char p0[144];
    Vec4 pos;
};

/* A mount point (32 bytes). */
struct OPoint {
    float pos[3];
    char p12[12];
    float fov;
    short lens;
    short m30;
};

/* The view the camera drives. */
struct OView {
    char p0[480];
    float m480;   /* lens angle */
    char p484[4];
    float m488;   /* far distance */
    char p492[4];
    float m496;   /* lens scale */
    char p500[160];
    int m660;
    int m664;
    int m668;
    int m672;
};

/* The camera sway (src/race/CamSway.cpp). */
struct CamSway {
    void f_0f3f30();
    char m0[204];
};

}

extern CamCtrl::OPoint D_27ecfc[10];

extern "C" {
void f_0823f0(int n, CamCtrl::OView *v);
float f_0cd3cc(float a);
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
   pointer; here the pointer load comes first (two words). */
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

/* @implements 0x0f47bc us _ZN7CamCtrl11CCamOnBoard8f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */
void CCamOnBoard::f_07f5f8()
{
}

/* @implements 0x0f4a30 us _ZN7CamCtrl11CCamOnBoardD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0f4a40 us _ZN7CamCtrl11CCamOnBoardD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */

}
