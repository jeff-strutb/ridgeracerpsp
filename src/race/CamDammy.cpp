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

/* The view the cameras drive. */
struct DView {
    char p0[660];
    int m660;
    int m664;
    int m668;
    int m672;
};

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
};

class CCamDammyEye3 : public CCamProto {
public:
    virtual ~CCamDammyEye3() {}
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
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
