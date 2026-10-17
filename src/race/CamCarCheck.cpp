/* The car check replay camera, CamCtrl::CCamCarCheck (retail 0x0f2f5c to 0x0f35c0): a camera
   for looking the car over (lens setting 7, a 48 degree lens). Its out of line virtual
   methods and the inline destructors emitted with its vtable. */

/* Degrees to radians. */
extern float D_1d5da4;

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

/* The view the camera drives. */
struct CView {
    char p0[480];
    float m480;   /* lens angle */
    char p484[12];
    float m496;   /* lens scale */
    char p500[160];
    int m660;
    int m664;
    int m668;
    int m672;
};

}

extern "C" {
void f_0823f0(int n, CamCtrl::CView *v);
float f_0cd3cc(float a);
}

namespace CamCtrl {

class CCamCarCheck : public CCamProto {
public:
    virtual ~CCamCarCheck() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f8();

    CView *View() { return (CView *)param.v[0]; }
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
