/* The replay camera base class, CamCtrl::CCamProto (retail 0x07f564 to 0x07f600): the
   parameter copy and reset that are its out of line virtual methods (so its vtable is
   emitted here), then the inline virtual destructor and the empty start, step, show and
   stop methods, emitted after them in vtable order. */

namespace CamCtrl {

/* A camera's parameter block. */
struct CamParam {
    int v[6];
};

class CCamProto {
public:
    virtual ~CCamProto() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    /* @implements 0x07f5e0 us f_07f5e0
       WHAT IT DOES: Starts the camera: nothing for the base camera. */
    virtual void f_07f5e0(int *arg) {}
    /* @implements 0x07f5e8 us f_07f5e8
       WHAT IT DOES: Steps the camera: nothing for the base camera. */
    virtual void f_07f5e8() {}
    /* @implements 0x07f5f0 us f_07f5f0
       WHAT IT DOES: Shows the camera: nothing for the base camera. */
    virtual void f_07f5f0() {}
    /* @implements 0x07f5f8 us f_07f5f8
       WHAT IT DOES: Stops the camera: nothing for the base camera. */
    virtual void f_07f5f8() {}

    CamParam param;
};

/* @draft 0x07f564 us _ZN7CamCtrl9CCamProto3SetEPKNS_8CamParamE
   WHAT IT DOES: Copies a parameter block into the camera.
   REMAINING DIFFERENCE: retail copies the six words in a scheduled order using four
   registers (loads 0, 16, 8, stores, loads 12, 20, 4, stores); the struct copy gives
   sequential load/store pairs. memcpy, by value, named int and float fields, an 8 aligned
   struct, and all 720 field orders (int and float sources, with and without the first
   scheduling pass) were tried. */
void CCamProto::Set(const CamParam *p)
{
    param = *p;
}

/* @implements 0x07f598 us _ZN7CamCtrl9CCamProto5ResetEv
   WHAT IT DOES: Clears three of the camera's parameters (words 0, 2 and 5). */
void CCamProto::Reset()
{
    param.v[0] = 0;
    param.v[2] = 0;
    param.v[5] = 0;
}

/* @implements 0x07f5a8 us _ZN7CamCtrl9CCamProtoD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   vtable. */
/* @implements 0x07f5b8 us _ZN7CamCtrl9CCamProtoD0Ev
   WHAT IT DOES: Deleting destructor: restores the vtable and frees the object. */

}
