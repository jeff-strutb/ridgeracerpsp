/* The race camera's set of replay cameras (retail 0x081dcc to 0x0823f0): the constructor of
   the object that holds every replay camera (the two eyes, two dummies, the car check, burial,
   on board, TV and scenery cameras) and the table of pointers to them, as base object and
   complete object constructors; then the TV camera's inline constructor, emitted here because
   the set's constructor calls it (it is defined after that constructor, so it is not inlined).
   The angle union has no int member: with one, the int order word of the Euler angles would
   share its alias set and a false anti dependence changes the TV constructor's schedule. The set's own class name is not known (it is the start of
   the camera controller that ReplayControl.cpp calls CCamCtrl); it keeps the name that
   SequenceBase.cpp gives its constructor. */

/* Degrees to radians. */
extern float D_1d5da4;

/* An angle in radians, kept in range by f_099b98. */
union Angle {
    float a;
    Angle() : a(0) {}
    Angle(float r);
};

extern "C" {
Angle *f_099b98(Angle *a);
void f_0a6f88(void *m);
void f_0a6fac(void *m);
}

inline Angle::Angle(float r) : a(r)
{
    f_099b98(this);
}

/* Euler angles with their axis order. */
struct Euler {
    Angle a[3];
    int order;
    Euler()
    {
        a[0] = Angle(0.0f);
        a[1] = Angle(0.0f);
        a[2] = Angle(0.0f);
        order = 0;
    }
};

/* One arm of a camera sway: its angle, its turning speed and its length. */
struct Arm {
    Angle a;
    float speed;
    float len;
};

/* A camera sway (src/race/CamSway.cpp): up to sixteen rotating arms. */
struct CamSway {
    int n;
    Arm arm[16];
    float m196;
    float m200;
};

/* The car's motion state (made and destroyed elsewhere). */
struct CMotion {
    char m0[624];
    CMotion() { f_0a6f88(this); }
    ~CMotion() { f_0a6fac(this); }
} __attribute__((aligned(16)));

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

/* The first person eye (64 bytes). */
class CCamEye1 : public CCamProto {
public:
    virtual ~CCamEye1() {}
    virtual void Set(const CamParam *p);

    int m28;
    float ofs[4];
    int m48;
    char p52[12];
};

/* The third person eye (1120 bytes). */
class CCamEye3 : public CCamProto {
public:
    virtual ~CCamEye3() {}
    virtual void Set(const CamParam *p);

    int m28;
    CMotion motion;
    char p656[104];
    Euler m760;
    char p776[344];
};

/* A camera that does nothing (28 bytes). */
class CCamDammy : public CCamProto {
public:
    virtual ~CCamDammy() {}
    virtual void Set(const CamParam *p);
};

/* The car check camera (56 bytes): its far distance, its rotation in radians and its
   settings. */
class CCamCarCheck : public CCamProto {
public:
    virtual ~CCamCarCheck() {}
    virtual void Set(const CamParam *p);
    CCamCarCheck()
    {
        m28 = 5000.0f;
        rot[0] = D_1d5da4 * 0.0f;
        rot[1] = D_1d5da4 * 45.0f;
        rot[2] = D_1d5da4 * 48.0f;
        m44 = 1;
        m48 = 0.005f;
        m52 = 1;
    }

    float m28;
    float rot[3];
    int m44;
    float m48;
    int m52;
};

/* The burial camera (256 bytes). */
class CCamBurial : public CCamProto {
public:
    virtual ~CCamBurial() {}
    virtual void Set(const CamParam *p);
    CCamBurial() : table(0) {}

    void *table;
    void *cur;
    CamSway sway;
    char p240[16];
};

/* The on board camera (272 bytes). */
class CCamOnBoard : public CCamProto {
public:
    virtual ~CCamOnBoard() {}
    virtual void Set(const CamParam *p);

    int m28;
    float m32[4];
    int m48;
    void *cur;
    CamSway sway;
    float m260;
    char p264[8];
};

/* The TV camera (784 bytes). */
class CCamTV : public CCamProto {
public:
    virtual ~CCamTV() {}
    virtual void Set(const CamParam *p);
    CCamTV();

    int m28;
    void *shot;
    void *car;
    CamSway sway;
    CamSway sway2;
    char p448[48];
    Euler m496;
    char p512[180];
    Angle m692;
    Angle m696;
    char p700[84];
};

/* The scenery camera (452 bytes). */
class CCamScenery : public CCamProto {
public:
    virtual ~CCamScenery() {}
    virtual void Set(const CamParam *p);
    CCamScenery() : table(0) {}

    void *table;
    void *cur;
    CamSway sway;
    CamSway sway2;
    int m444;
    float m448;
};

}

/* The replay cameras and the table of them (3104 bytes). */
struct f_08206c_t {
    f_08206c_t();
    CamCtrl::CCamEye1 eye1;
    CamCtrl::CCamEye3 eye3;
    CamCtrl::CCamDammy dammy1184;
    CamCtrl::CCamDammy dammy1212;
    CamCtrl::CCamCarCheck carCheck;
    CamCtrl::CCamBurial burial;
    CamCtrl::CCamOnBoard onBoard;
    CamCtrl::CCamTV tv;
    CamCtrl::CCamScenery scenery;
    CamCtrl::CCamProto *cam[11];
};

/* @implements 0x081dcc us _ZN10f_08206c_tC2Ev
   WHAT IT DOES: Builds every replay camera in place (base object constructor) and fills the
   camera table: the first and third person eyes, the burial, on board, TV and scenery
   cameras, the second dummy, the car check camera and the first dummy. */
/* @implements 0x08206c us _ZN10f_08206c_tC1Ev
   WHAT IT DOES: Same as the base object constructor (complete object constructor). */
f_08206c_t::f_08206c_t()
{
    cam[0] = &eye1;
    cam[1] = &eye3;
    cam[2] = &burial;
    cam[3] = &onBoard;
    cam[4] = &tv;
    cam[5] = &scenery;
    cam[6] = &dammy1212;
    cam[7] = &carCheck;
    cam[8] = &dammy1184;
}

/* @implements 0x08230c us _ZN7CamCtrl6CCamTVC1Ev
   WHAT IT DOES: Builds the TV camera (inline, emitted here): its vtable, the arm angles of its
   two sways cleared, its rotation set to zero angles, and two more angles cleared. It is
   defined after the set's constructor, so the tree inliner (which runs as each non-inline
   function is finished) has no body to inline there and calls it instead. */
inline CamCtrl::CCamTV::CCamTV()
{
}
