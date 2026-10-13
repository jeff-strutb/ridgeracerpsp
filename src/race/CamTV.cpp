/* The TV style replay camera, CamCtrl::CCamTV (retail 0x07f600 to 0x081dcc): its reset, the
   static tuning values built at start up from the unit conversions, and the inline
   destructors emitted with its vtable. */

/* Degrees to radians, and the speed unit conversion. */
extern float D_1d5da4;
extern float D_1d5d94;

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

/* A car's replay camera data. */
struct TVCar {
    char p0[16];
    float pos;
    char p20[64];
    int m84;
};
struct TVOwner {
    char p0[2128];
    TVCar car;
};

/* A camera shot. */
struct TVPoint {
    char p0[12];
    float x, y, z;
};
struct TVShot {
    char p0[8];
    int fixed;
    float x, y, z;
    char p24[100];
    char p124[16];
    int retarget;
    float tx;
    char p148[4];
    float tz;
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    int f_0e2690(int pos);
    int f_0e2448(int a, int b, float x, float z);
    void f_0e2d10(float *x, int *out, float *z, float fx, float fz);
    int m0;
    int m4;
    int length;
};
struct MapMgr {
    CourseAreas *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas m12240;
};

/* The extended parameter block of a TV camera. */
struct TVParam {
    CamParam base;
    int m24;
};

class CCamTV : public CCamProto {
public:
    TVShot *f_0802fc();
    void f_080b48();
    void f_080b50();
    void f_080f04();
    void f_080f90();
    void f_0817e0();
    void f_081360();
    void f_081604();
    void f_0804bc();

    virtual ~CCamTV() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f834(int *arg);
    virtual void f_07f8cc();
    virtual void f_07fa84();
    virtual void f_0802f0();

    int m28;
    TVShot *shot;
    TVCar *car;
    char p40[408];
    int m448;
    char p452[12];
    float shotX, shotY, shotZ;
    char p476[40];
    float m516;
    int m520;
    float m524;
    float m528;
    float m532;
    int m536;
    int m540;
    int m544;
    char p548[8];
    int m556;
    int m560;
    char p564[28];
    int m592;
    int m596;
    char p600[24];
    struct Quad {
        int v[4];
    } m624, m640;
    char p656[80];
    float m736;
    int m740;
    char p744[4];
    int m748;
    int m752;
};

}

extern CamCtrl::MapMgr D_23c820;

namespace CamCtrl {

/* @draft 0x07f600 us _ZN7CamCtrl6CCamTV3SetEPKNS_8CamParamE
   REMAINING DIFFERENCE: first transcription; member layout and scheduling unchecked.
   WHAT IT DOES: Sets the camera up from a parameter block: the base parameters, the car
   followed and its position, the first shot (its position snapped to the course when the
   shot is not fixed, and its target likewise), then resets every part of the camera and
   finds the course area 1000 units either side of the car. */
void CCamTV::Set(const CamParam *cp)
{
    const TVParam *p = (const TVParam *)cp;
    CourseAreas *areas = D_23c820.Areas();
    TVShot *s;
    int pos, a, b;
    CCamProto::Set(cp);
    m28 = p->m24;
    car = &((TVOwner *)param.v[2])->car;
    m516 = car->pos;
    m532 = car->pos;
    m544 = car->m84;
    m448 = 0;
    s = f_0802fc();
    shot = s;
    m736 = (float)areas->length * 0.5f;
    if (s->fixed == 1) {
        int tmp;
        areas->f_0e2d10(&s->x, &tmp, &s->z, s->x, s->z);
        shot->fixed = 0;
    } else {
        shotX = s->x;
        shotY = s->y;
        shotZ = s->z;
    }
    s = shot;
    if (*(int *)(s->p124 + 16) != 0) {
        int tmp;
        areas->f_0e2d10(&s->tx, &tmp, &s->tz, *(float *)(s->p124 + 20), *(float *)(s->p124 + 28));
        *(int *)(s->p124 + 16) = 0;
    }
    f_080b48();
    f_080b50();
    f_080f04();
    f_080f90();
    f_0817e0();
    f_081360();
    m592 = 0;
    m596 = 0;
    f_081604();
    f_0804bc();
    m640 = m624;
    m524 = 1.0f;
    m520 = 0;
    pos = (int)car->pos;
    shot = 0;
    m540 = 0;
    m536 = 0;
    m556 = 0;
    m560 = 0;
    m740 = 0;
    m748 = 0;
    m752 = 0;
    a = areas->f_0e2690(pos - 1000);
    b = areas->f_0e2690(pos + 1000);
    m532 = (float)areas->f_0e2448(a, b, shotX, shotZ);
}

/* @implements 0x07f818 us _ZN7CamCtrl6CCamTV5ResetEv
   WHAT IT DOES: Resets the camera as the base camera does. */
void CCamTV::Reset()
{
    CCamProto::Reset();
}

/* @implements 0x081d94 us _ZN7CamCtrl6CCamTVD1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x081da4 us _ZN7CamCtrl6CCamTVD0Ev
   WHAT IT DOES: Deleting destructor: restores the base vtable and frees the object. */

}

/* The camera's speed and aim tuning, in run time units. */
float D_24144c = D_1d5d94 * 150.0f;
struct Tune {
    float a, b, c, d;
};
Tune D_241458 = {D_1d5da4 * 0.4f, 300000.0f, D_1d5da4 * 1.65f, 40000.0f};
Tune D_241468 = {D_1d5da4 * 1.65f, 40000.0f, D_1d5da4 * 6.0f, 5000.0f};

/* @implements 0x081cc4 us __static_initialization_and_destruction_0
   WHAT IT DOES: Converts the camera's tuning values at start up. */
/* @implements 0x081d74 us _GLOBAL__I
   WHAT IT DOES: Runs the above. */
