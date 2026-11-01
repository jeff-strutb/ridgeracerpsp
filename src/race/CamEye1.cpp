/* The first person (bumper) camera, CamCtrl::CCamEye1 (retail 0x0c4444 to 0x0c4bc4): its
   parameter set up, reset, start and per frame step, then the empty stop method and the
   inline destructors emitted with its vtable (the last three have no unwind entries, so the
   object file map splits them off as their own row). */

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

/* The parameter block of a first person camera. */
struct Eye1Param {
    CamParam base;
    int m24;
    int m28;
    int m32;
};

/* The followed car as the camera reads it. */
struct E1Car {
    char p0[7708];
    float m7708;
    char p7712[2416];
    Vec4 m10128;   /* the eye's offset from the car */
};

/* The view the camera drives. */
struct E1View {
    char p0[488];
    float m488;    /* far distance */
    char p492[168];
    int m660;
    int m664;
    int m668;
    int m672;
};

class CCamEye1 : public CCamProto {
public:
    virtual ~CCamEye1() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f8() {}

    E1View *View() { return (E1View *)param.v[0]; }
    E1Car *Car() { return (E1Car *)param.v[2]; }

    int m28;
    Vec4 ofs;      /* 32 */
    int m48;
};

/* @implements 0x0c4444 us _ZN7CamCtrl8CCamEye13SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block and keeps its extra word. */
void CCamEye1::Set(const CamParam *p)
{
    CCamProto::Set(p);
    m48 = ((const Eye1Param *)p)->m32;
}

/* @implements 0x0c447c us _ZN7CamCtrl8CCamEye15ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamEye1::Reset()
{
    CCamProto::Reset();
}

/* @draft 0x0c4498 us _ZN7CamCtrl8CCamEye18f_07f5e0EPi
   DRAFT: 12 words. The view stores match; retail schedules the height product before the
   w and z stores (constants loaded 0.9, 1, -100), here the 1.0 store goes first. All store
   orders, a reference, a pointer, an inline Set and reloading the car were tried.
   WHAT IT DOES: Starts the camera: marks its view (and clears the previous camera's mark),
   sets a far distance of 300, and puts the eye's offset on the car (0.9 of its height up,
   100 forward) and takes a copy of it. */
void CCamEye1::f_07f5e0(int *arg)
{
    E1View *v = View();
    E1View *o = (E1View *)param.v[1];
    v->m660 = 0;
    v->m668 = 0;
    v->m672 = 1;
    v->m664 = 1;
    if (o)
        o->m660 = 0;
    v->m488 = 300.0f;
    E1Car *c = Car();
    Vec4 &e = c->m10128;
    e.x = 0;
    e.y = c->m7708 * 0.9f;
    e.w = 1.0f;
    e.z = -100.0f;
    Vec4 t = Car()->m10128;
    ofs = t;
}

/* @implements 0x0c4b84 us _ZN7CamCtrl8CCamEye18f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */

/* @implements 0x0c4b8c us _ZN7CamCtrl8CCamEye1D1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0c4b9c us _ZN7CamCtrl8CCamEye1D0Ev
   WHAT IT DOES: Deleting destructor: as above, then frees the object. */

}
