/* The TV style replay camera, CamCtrl::CCamTV (retail 0x07f600 to 0x081dcc): its reset, the
   static tuning values built at start up from the unit conversions, and the inline
   destructors emitted with its vtable. */

/* Degrees to radians, and the speed unit conversion. */
extern float D_1d5da4;
extern float D_1d5d94;

namespace CamCtrl {
union Angle;
}
extern "C" CamCtrl::Angle *f_099b98(CamCtrl::Angle *);
/* The eased ramp of x over [0, 1]. */
extern "C" float f_0f4290(float x);

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
    void operator+=(const Vec4 &o)
    {
        x += o.x;
        y += o.y;
        z += o.z;
    }
};

/* A vector scaled, as a point (w = 1). */
static inline Vec4 operator*(float t, const Vec4 &v)
{
    Vec4 r;
    r.x = t * v.x;
    r.y = t * v.y;
    r.z = t * v.z;
    r.w = 1.0f;
    return r;
}

/* A car's replay camera data. */
struct TVCar {
    char p0[12];
    float m12;
    float pos;
    char p20[64];
    int m84;
};
struct TVOwner {
    char p0[144];
    Vec4 m144;
    Vec4 *Pos() { return &m144; }
    char p160[48];
    struct {
        int v[4];
    } m208;
    void *State() { return &m208; }
    char p224[1904];
    TVCar car;
};

/* A shot's look: on, a mode, and its two turn angles. */
struct TVLook {
    int on;
    int mode;
    float start;
    float m12;
    float a, b;
    float m24;
};

/* A shot's eased move: frames to speed up, at speed and to slow down, its start time and
   end, and whether it keeps its value. */
struct TVMove {
    int cruise;
    int accel;
    int decel;
    float start;
    float target;
    int keep;
};

/* A camera shot. */
struct TVPoint {
    char p0[12];
    float x, y, z;
};
struct Vec3 {
    float x, y, z;
};
struct TVShot {
    char p0[8];
    int fixed;
    Vec3 pos;
    char p24[16];
    char ramp[16];
    /* The shot's look: on, a mode, and its two turn angles. */
    TVLook look;
    char p84[16];
    TVMove move;
    int m124;
    int m128;
    int m132;
    float m136;
    int retarget;
    Vec3 tgt;
    int m156;
    char p160[80];
    float m240;
    char p244[32];
    int m276;
    char p280[8];
    float m288;
    char p292[20];
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    int f_0e2690(int pos);
    float f_0e26dc(float pos);
    int f_0e2448(int a, int b, float x, float z);
    void f_0e2d10(float *x, float *y, float *z, float fx, float fz);
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

/* A sub-object of the camera with a reset method elsewhere. */
struct TVTimer {
    void f_0f3f30();
    void f_0f411c(float t);
    int m0;
};


/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

/* An angle wrapped into range. */
struct Rad {
    Angle a;
    Rad(float f)
    {
        a.f = f;
        f_099b98(&a);
    }
};

/* The lens data of the camera's view. */
struct TVView {
    float px, py, pz;
    char p12[468];
    float fov;
    float m484;
    float m488;
    char p492[4];
    float zoom;
    char p500[72];
    int m572;
    char p576[32];
    float m608, m612, m616;
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    float m688, m692, m696;
    char p700[4];
    float m704;
    float m708;
    float m712;
    int m716;
    char p720[16];
    float m736;
    int m740;
    float m744;
};

class CCamTV : public CCamProto {
public:
    TVShot *f_0802fc();
    void f_080b48();
    void f_080b50();
    void f_080f90();
    void f_0817e0();
    void f_080660();
    void f_08140c(struct Mat34 *out, float t, float ry, float rx, float lim);
    void f_081944();
    float f_081610();
    void f_081b10();
    void f_0817fc(struct Mat34 *out, float t, float ry, float rx);
    void f_081604();
    void f_0804bc();

    virtual ~CCamTV() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f834(int *arg);
    virtual void f_07f8cc();
    virtual void f_07fa84();
    virtual void f_0802f0();

    void f_081360();
    void f_08138c();
    void f_081938();
    void f_0803dc();
    void f_0817d0();
    void f_0817d8();
    void f_080f04();
    Vec4 f_0803e4();

    int m28;
    TVShot *shot;
    TVCar *car;
    TVTimer t40;
    char p44[192];
    float sway1X, sway1Y;
    TVTimer t244;
    char p248[192];
    float swayX, swayY;
    int m448;
    char p452[12];
    float shotX, shotY, shotZ;
    char p476[4];
    float m480, m484, m488;
    char p492[4];
    float m496, m500, m504;
    char p508[4];
    float m512;
    float m516;
    float m520;
    float m524;
    float m528;
    float m532;
    int m536;
    int m540;
    int m544;
    int m548;
    char p552[4];
    int m556;
    int m560;
    char p564[12];
    Vec4 m576;
    float m592;
    float m596;
    char p600[12];
    int m612;
    int m616;
    char p620[4];
    struct Quad {
        int v[4];
    };
    Vec4 m624, m640;
    float m656;
    float m660;
    char p664[24];
    int m688;
    Angle m692;
    Angle m696;
    int m700;
    float m704;
    float m708;
    float m712;
    float m716;
    float m720;
    int m724;
    float m728;
    float m732;
    float m736;
    int m740;
    int m744;
    int m748;
    int m752;
    char p756[12];
    Quad m768;
};

}

extern CamCtrl::MapMgr D_23c820;

/* The three fixed shots: the two selectable ones and the one before the start. */
extern CamCtrl::TVShot D_1d3aac[2];
extern const CamCtrl::TVShot D_1a73c0;
/* The current lap, and the race time. */
extern int D_241454;
extern float D_241450;
extern "C" int iprintf(const char *, ...);
extern "C" void f_125b5c(int) __attribute__((noreturn));

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
        float tmp;
        areas->f_0e2d10(&s->pos.x, &tmp, &s->pos.z, s->pos.x, s->pos.z);
        shot->fixed = 0;
    } else {
        shotX = s->pos.x;
        shotY = s->pos.y;
        shotZ = s->pos.z;
    }
    s = shot;
    if (s->retarget != 0) {
        float tmp;
        areas->f_0e2d10(&s->tgt.x, &tmp, &s->tgt.z, s->tgt.x, s->tgt.z);
        s->retarget = 0;
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

/* @implements 0x0802f0 us _ZN7CamCtrl6CCamTV8f_0802f0Ev
   WHAT IT DOES: Stops the camera: clears a flag on the object it follows. */
void CCamTV::f_0802f0()
{
    ((int *)param.v[0])[185] = 0;
}

/* @implements 0x0802fc us _ZN7CamCtrl6CCamTV8f_0802fcEv
   WHAT IT DOES: Finds the shot to show (CCamTV::SearchTVCameraData): one of the two fixed
   shots when the camera is in a fixed mode, the start shot before the first lap, else the
   first entry of the lap's shot list whose time is not yet reached (or is negative). Notes
   whether the shot changed since the last search. Stops the game on a lap past 6. */
TVShot *CCamTV::f_0802fc()
{
    if (m752 == 1)
        return &D_1d3aac[0];
    if (m752 == 2)
        return &D_1d3aac[1];
    int lap = D_241454;
    if (lap == 0)
        return (TVShot *)&D_1a73c0;
    if (lap < 7) {
        int base = m28;
        int i = 0;
        int *e = (int *)(*(int *)(base + 32 + lap * 8) + base);
    next:
        if (0.0f <= *(float *)&e[2] && *(float *)&e[2] < D_241450) {
            i++;
            e += 2;
            goto next;
        }
        if (i != m748)
            m744 = 1;
        else
            m744 = 0;
        TVShot *r = (TVShot *)(e[1] + base);
        m748 = i;
        return r;
    }
    iprintf("!!!ERROR!!! No Such Data Lap %d @CCamTV::SearchTVCameraData\n", lap);
    f_125b5c(1);
}

/* @implements 0x080b48 us _ZN7CamCtrl6CCamTV8f_080b48Ev
   WHAT IT DOES: Clears a counter. */
void CCamTV::f_080b48()
{
    m688 = 0;
}

/* @implements 0x081604 us _ZN7CamCtrl6CCamTV8f_081604Ev
   WHAT IT DOES: Clears two words. */
void CCamTV::f_081604()
{
    m712 = 0;
    m704 = 0;
}

/* @implements 0x0817e0 us _ZN7CamCtrl6CCamTV8f_0817e0Ev
   WHAT IT DOES: Resets the sub-object at 244. */
void CCamTV::f_0817e0()
{
    t244.f_0f3f30();
}

/* @implements 0x081360 us _ZN7CamCtrl6CCamTV8f_081360Ev
   WHAT IT DOES: Resets the sub-object at 40 and clears a word. */
void CCamTV::f_081360()
{
    t40.f_0f3f30();
    m716 = 0;
}

}

/* The time scale, pi, and the sway unit (one over 32768). */
extern float D_1d5d98;
extern float D_1d5d90;
extern float D_1d3a68;
/* Frames per unit of the shot moves. */
extern float D_1d5da0;

namespace CamCtrl {

/* An angle kept in range by f_099b98; zero by default. */
union EAngle {
    float a;
    EAngle() : a(0) {}
    EAngle(float r) : a(r) { f_099b98((Angle *)this); }
};

/* Euler angles with their axis order. */
struct Euler {
    EAngle a[3];
    int order;
    Euler(EAngle x, EAngle y, EAngle z, int o)
    {
        a[0] = x;
        a[1] = y;
        a[2] = z;
        order = o;
    }
};

/* The 3x3 matrix with rows padded to four floats. */
struct Mat34 {
    float m[3][4];
};

}

extern "C" void f_09f92c(CamCtrl::Mat34 *m, const CamCtrl::Euler &e);

namespace CamCtrl {

/* @implements 0x08140c us _ZN7CamCtrl6CCamTV8f_08140cEPNS_5Mat34Effff
   WHAT IT DOES: Advances the camera shake by t and builds the shake rotation: the shake
   strength (blended from the values at 720 and 708 by 704, over lim times 0.03 and at
   most 1) eased and scaled by the shake's fade-in at 716, turns the shake's two components
   by rx and ry into angles (order 4) in out; then fades the shake in a step (0.2 of the
   time scale) up to 1. */
void CCamTV::f_08140c(Mat34 *out, float t, float ry, float rx, float lim)
{
    float x = m720 * (1.0f - m704);
    x = x + m708 * m704;
    float l = lim * 0.03f;
    if (l < x)
        x = 1.0f;
    else
        x = x / l;
    x = f_0f4290(x) * m716 * 16.0f * D_1d5d90 * D_1d3a68;
    t40.f_0f411c(t * D_1d5d98);
    float *sw = &sway1X;
    Mat34 m;
    f_09f92c(&m, Euler(EAngle(rx * sway1X * x), EAngle(ry * sw[1] * x), EAngle(0.0f), 4));
    *out = m;
    m716 = m716 + D_1d5d98 * 0.2f;
    if (1.0f < m716)
        m716 = 1.0f;
}

/* @implements 0x0817fc us _ZN7CamCtrl6CCamTV8f_0817fcEPNS_5Mat34Efff
   WHAT IT DOES: Advances the camera sway by t and builds the sway rotation: the sway's two
   components scaled by rx and ry into angles (16 sway units to the radian step), turned
   about the first two axes (order 4) into out. */
void CCamTV::f_0817fc(Mat34 *out, float t, float ry, float rx)
{
    t244.f_0f411c(t * D_1d5d98);
    float ax = rx * swayX * 16.0f * D_1d5d90 * D_1d3a68;
    float ay = ry * swayY * 16.0f * D_1d5d90 * D_1d3a68;
    Mat34 m;
    f_09f92c(&m, Euler(EAngle(ax), EAngle(ay), EAngle(0.0f), 4));
    *out = m;
}

/* @draft 0x081944 us _ZN7CamCtrl6CCamTV8f_081944Ev
   Remaining difference: FP registers only: retail's speed lands in f4 (the register the
   cruise frames' float just freed), here f5, and the slow-down branch swaps f0 and f1.
   WHAT IT DOES: Runs the shot's eased move once its start time comes round (time wrapped
   by twice the period at 736, or at once in the timed mode at 740): counts the move's
   frame up by 5 to its end, starts the value from the look's base, and adds this frame's
   share of the distance: ramping up over the speed-up frames, full while at speed, and
   ramping down over the slow-down frames. */
void CCamTV::f_081944()
{
    TVMove *m = &shot->move;
    TVLook *lk = &shot->look;
    if (m->cruise == 0)
        return;
    float d = D_241450 - m->start;
    while (d < 0.0f)
        d += m736 * 2.0f;
    if ((m740 != 0 && m->start <= D_241450) || d <= m736) {
        if (m724 == 0 && m->keep == 0)
            m728 = lk->m24;
        int total = m->cruise + m->accel + m->decel;
        if (m724 < total) {
            m724 += 5;
            if (total < m724)
                m724 = total;
        }
        int t = m724;
        float sp = (m->target - lk->m24) /
                   (((float)(m->accel + m->decel) * 0.5f + (float)m->cruise) / D_1d5da0);
        if (t < m->accel)
            m728 += sp * ((float)t / (float)m->accel);
        else if (t < m->accel + m->cruise)
            m728 += sp;
        else
            m728 += sp * (1.0f - (float)(t - m->accel - m->cruise) / (float)m->decel);
    }
}

/* @implements 0x081938 us _ZN7CamCtrl6CCamTV8f_081938Ev
   WHAT IT DOES: Clears two words. */
void CCamTV::f_081938()
{
    m724 = 0;
    m728 = 0;
}

}

extern "C" {
void f_0a65e4(CamCtrl::Vec4 *out, void *in);
float f_0a65c4(CamCtrl::Vec4 *v);
}
extern float D_1d5d9c;
extern float D_24144c;
struct Ramp;
float f_082588(Ramp *r, float x);
extern "C" float *f_0a8fa8(float *out, void *c, const float *d);
struct Tune;
extern Tune D_241458;
extern Tune D_241468;
/* The zoom ramp over distance. */
extern Ramp D_1d3a6c;
/* The camera's height above the car. */
extern float D_1d3a64;
void f_09b394(CamCtrl::Angle a, float *x, float *y);
CamCtrl::Vec4 f_09c720(const void *q, const CamCtrl::Vec4 *b);

namespace CamCtrl {

/* @implements 0x08138c us _ZN7CamCtrl6CCamTV8f_08138cEv
   WHAT IT DOES: The distance between the two stored positions, scaled. */
void CCamTV::f_08138c()
{
    Vec4 a, b;
    f_0a65e4(&a, &m624);
    f_0a65e4(&b, &m640);
    a.x = a.x - b.x;
    a.y = a.y - b.y;
    a.z = a.z - b.z;
    m720 = f_0a65c4(&a) * D_1d5d9c;
}

/* @implements 0x0803dc us _ZN7CamCtrl6CCamTV8f_0803dcEv
   WHAT IT DOES: Debug display of the camera state (compiled out). */
void CCamTV::f_0803dc()
{
}

/* @draft 0x0803e4 us _ZN7CamCtrl6CCamTV8f_0803e4Ev
   Remaining difference: the two %hi registers of 80/D_24144c are swapped (retail v0 for
   D_24144c); local-alloc gives the 80.0 pseudo the first choice because update_equiv_regs
   moves its lui next to its use and shortens its life.
   WHAT IT DOES: The camera's aim offset: the course direction at the car, looking ahead by
   the shot's ramp read at the value at 656, scaled by half of 80 over the speed unit (at
   most 1, which is kept at 660). */
Vec4 CCamTV::f_0803e4()
{
    float d = f_082588((Ramp *)((char *)shot + 40), m656);
    Vec4 v;
    f_0a8fa8(&v.x, car, &d);
    float k = 80.0f / D_24144c;
    Vec4 r = v;
    if (1.0f < k)
        k = 1.0f;
    m660 = k;
    float h = k * 0.5f;
    r.x *= h;
    r.y *= h;
    r.z *= h;
    return r;
}

/* @draft 0x0804bc us _ZN7CamCtrl6CCamTV8f_0804bcEv
   Remaining difference: retail loads D_1d3a64 before the position copy (here after it,
   held by the copy's float stores; declaring it const did not move it) and orders the
   unit vector's stores x, z, y, w and the final copy's registers differently.
   WHAT IT DOES: Aims the camera: the followed object's position less the shot position
   (the height raised by 350, the car's and the shot's heights, then halved) and its
   length; then, when the shot has a look set, its mode and a unit vector turned by the
   shot's two angles, carried into the object's frame for mode 2. */
void CCamTV::f_0804bc()
{
    m624 = *((TVOwner *)param.v[2])->Pos();
    m624.x = m624.x - shotX;
    m624.y = (m624.y + (D_1d3a64 + car->m12 + shot->m240)) * 0.5f;
    Vec4 *d = &m624;
    d->y = d->y - shotY;
    d->z = d->z - shotZ;
    m656 = f_0a65c4(d);
    TVLook *lk = &shot->look;
    m612 = lk->on;
    if (m612 != 0) {
        Vec4 *u = &m576;
        u->x = 0;
        u->y = 0;
        u->z = -1.0f;
        u->w = 1.0f;
        m616 = lk->mode;
        f_09b394(Rad(lk->a).a, &u->y, &u->z);
        f_09b394(Rad(lk->b).a, &u->z, &u->x);
        if (shot->fixed == 2)
            *u = f_09c720(((TVOwner *)param.v[2])->State(), u);
    }
}

/* @draft 0x081610 us _ZN7CamCtrl6CCamTV8f_081610Ev
   Remaining difference: global-alloc puts the ramp value in f20 and 1.0/150 in f21/f22
   in retail (here 1.0, 150, ramp), and retail's two zero returns share one block that the
   frame-count tests fall into; here the zero is set before the first test.
   WHAT IT DOES: Steps the shot's timing from the frame count at 448: the eased progress
   over 600 frames (kept at 712), the span left after the two offsets, the previous zoom
   saved; eases the value at 512 toward the distance ramp (near or far set by 40000) over
   the first 150 frames, and returns the zoom: easing in over the first 150 frames, out
   until 750, scaled by the distance ramp (0 before the start and after 750). */
float CCamTV::f_081610()
{
    m712 = (float)m448 / 600.0f;
    if (m712 < 0.0f)
        m712 = 0.0f;
    else if (1.0f < m712)
        m712 = 1.0f;
    m712 = f_0f4290(m712);
    float k = 1.0f - (m592 + m596);
    m708 = m720;
    m704 = 0;
    if (m448 <= 0)
        return 0.0f;
    float d = m656;
    float a = f_082588(40000.0f < d ? (Ramp *)&D_241458 : (Ramp *)&D_241468, d);
    float x = (float)m448 / 150.0f;
    if (1.0f < x)
        x = 1.0f;
    float e = f_0f4290(x) * k;
    m512 = a * e + m512 * (1.0f - e);
    int c = m448;
    float n = (float)c;
    float f;
    if (c < 150)
        f = f_0f4290(n / 150.0f) * k;
    else if (c < 750)
        f = (1.0f - f_0f4290((n - 150.0f) / 600.0f)) * k;
    else
        return 0.0f;
    return f * f_082588(&D_1d3a6c, m656);
}

/* @draft 0x080660 us _ZN7CamCtrl6CCamTV8f_080660Ev
   Remaining difference: only the direction blend into 624 is scheduled differently
   (retail adds x straight after copying it and shares the 1.0 %hi between the zero
   direction and the scaled vector's w); the rest matches.
   WHAT IT DOES: Runs the shot's look blend: while the look is on and its time has come
   round, first counts down the hold at 616 and then the blend at 612 by 5 frames; the
   eased share left (kept at 592) mixes the look direction at 576 with the camera's
   own direction (normalised, or straight ahead when it has no length) into 624, and
   sets the look angle at 728 and blends half the look's value into 512. */
void CCamTV::f_080660()
{
    TVLook *lk = &shot->look;
    if (m612 != 0) {
        float d = D_241450 - lk->start;
        while (d < 0.0f)
            d += m736 * 2.0f;
        if ((m740 != 0 && lk->start <= D_241450) || d <= m736) {
            if (0.0f < (float)m616) {
                m616 -= 5;
            } else {
                m612 -= 5;
                if (m612 < 0)
                    m612 = 0;
            }
        }
        m592 = f_0f4290((float)m612 / (float)lk->on);
        Vec4 dir = m624;
        float len = f_0a65c4(&dir);
        if (len <= 0.0f) {
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = 0.0f;
            dir.w = 1.0f;
        } else {
            dir.x /= len;
            dir.y /= len;
            dir.z /= len;
        }
        float t = m592;
        m624 = t * m576;
        m624 += (1.0f - t) * dir;
        m728 = m592 * lk->m24;
        m512 = lk->m12 * 0.5f * m592 + m512 * (1.0f - m592);
    } else {
        m592 = 0.0f;
    }
}

/* @implements 0x0817d0 us _ZN7CamCtrl6CCamTV8f_0817d0Ev
   WHAT IT DOES: Debug display (compiled out). */
void CCamTV::f_0817d0()
{
}

/* @implements 0x0817d8 us _ZN7CamCtrl6CCamTV8f_0817d8Ev
   WHAT IT DOES: Debug display (compiled out). */
void CCamTV::f_0817d8()
{
}

/* @implements 0x080f04 us _ZN7CamCtrl6CCamTV8f_080f04Ev
   WHAT IT DOES: Takes the shot's two angles (wrapped) and the followed object's four word
   state, and clears a counter. */
void CCamTV::f_080f04()
{
    char *s = (char *)shot + 160;
    m700 = 0;
    m692 = Rad(*(float *)(s + 20)).a;
    m696 = Rad(*(float *)(s + 28)).a;
    m768 = *(Quad *)((TVOwner *)param.v[2])->State();
}

}

extern float D_23ff60;
/* The race in progress (its course position at 44). */
struct TVRace {
    char p0[44];
    float m44;
};
extern TVRace *D_2407fc;
void f_0823f0(int n, CamCtrl::TVView *v);

namespace CamCtrl {

/* A lens step: below the field of view key, the view's distance scale. */
struct LensStep {
    float key;
    float val;
};

}

extern "C" float f_0cd3cc(float);
extern CamCtrl::LensStep D_1d3a7c[6];

namespace CamCtrl {

/* @implements 0x07f8cc us _ZN7CamCtrl6CCamTV8f_07f8ccEv
   WHAT IT DOES: Puts the camera's state on its view: half the field of view and its zoom,
   the shot position, the aim, the course position (moved along the course), the lens and
   tracking values, and the followed distance (the car's own position when the shot's is
   negative); during a lap, the view's distance scale looked up from twice the field of
   view in the lens steps (interpolated between steps), times 1000. */
void CCamTV::f_07f8cc()
{
    TVView *v = (TVView *)param.v[0];
    v->fov = m512 * 0.5f;
    v->zoom = 1.0f / f_0cd3cc(v->fov);
    TVView *w = (TVView *)param.v[0];
    w->px = shotX;
    w->py = shotY;
    w->pz = shotZ;
    w->m608 = m496;
    w->m612 = m500;
    w->m616 = m504;
    m516 = D_23c820.Areas()->f_0e26dc(m516);
    TVView *u = (TVView *)param.v[0];
    u->m704 = m516;
    u->m688 = m480;
    u->m692 = m484;
    u->m696 = m488;
    u->m572 = m544;
    u->m716 = m556;
    u->m708 = m528;
    u->m740 = shot->m276;
    u->m712 = m520;
    u->m744 = shot->m288 < 0.0f ? ((TVOwner *)param.v[2])->car.pos : m532;
    u->m736 = m524;
    u->m664 = m548;
    if (D_241454 != 0) {
        float x = u->fov * 2.0f;
        float r = D_1d3a7c[5].val;
        LensStep *e = D_1d3a7c;
        for (int i = 0; i < 6; i++, e++) {
            if (e->key < x) {
                if (i == 0) {
                    r = e->val;
                } else {
                    float t = (x - e->key) / (e[-1].key - e->key);
                    r = e[-1].val * t + e->val * (1.0f - t);
                }
                break;
            }
        }
        u->m488 = r * 1000.0f;
    }
}

/* @draft 0x07f834 us _ZN7CamCtrl6CCamTV8f_07f834EPi
   REMAINING DIFFERENCE: only the FP registers of the far distance (retail f0 for the
   result and the course value, f1 for 1000); an in-place multiply and a ternary were
   tried.
   WHAT IT DOES: Starts the camera: puts lens setting 4 on the view, takes its far distance
   (300, or the course value times 1000 when the course setting is on) and marks the view
   and the previous camera's view. */
void CCamTV::f_07f834(int *arg)
{
    TVView *v = (TVView *)param.v[0];
    v->m668 = 1;
    v->m672 = 0;
    f_0823f0(4, v);
    TVView *w = (TVView *)param.v[0];
    m732 = w->m712;
    float d;
    if (D_241454 == 0)
        d = 300.0f;
    else
        d = D_23ff60 * 1000.0f;
    TVView *o = (TVView *)param.v[1];
    w->m488 = d;
    w->m664 = 1;
    w->m660 = 4;
    if (o)
        o->m660 = -1;
}

/* @draft 0x081b10 us _ZN7CamCtrl6CCamTV8f_081b10Ev
   Remaining difference: only the course areas address of mode 1: sched1 here hoists its
   lui/addiu into the entry block (retail keeps it in the mode 1 block, after this->param
   is read through a0); everything else is the same code two words later.
   WHAT IT DOES: Places the fixed shot of the current fixed mode on the course: in mode 1
   at the followed car (0.8 in from its side, height taken from the object, kind 3); in
   mode 2 five across at the race position with its height raised 4000, aimed at a point
   1.5 the other side raised 2200, with fixed spans of 450. */
void CCamTV::f_081b10()
{
    if (m752 == 1) {
        TVOwner *o = (TVOwner *)param.v[2];
        float pos = o->car.pos;
        float side = *(float *)o->car.p20 - 0.8f;
        if (pos < 0.0f)
            pos = 0.0f;
        D_23c820.Areas()->f_0e2d10(&D_1d3aac[0].pos.x, &D_1d3aac[0].pos.y, &D_1d3aac[0].pos.z,
                                   side, pos);
        D_1d3aac[0].pos.y = ((TVOwner *)param.v[2])->m144.y;
        D_1d3aac[0].fixed = 3;
    } else if (m752 == 2) {
        CourseAreas *areas = D_23c820.Areas();
        float pos = D_2407fc->m44;
        if (pos < 0.0f)
            pos = 0.0f;
        areas->f_0e2d10(&D_1d3aac[1].pos.x, &D_1d3aac[1].pos.y, &D_1d3aac[1].pos.z, 5.0f, pos);
        D_1d3aac[1].pos.y = D_1d3aac[1].pos.y + 4000.0f;
        D_1d3aac[1].m136 = D_2407fc->m44 - 10.0f;
        D_1d3aac[1].m128 = D_1d3aac[1].m132 = 450;
        D_1d3aac[1].tgt = D_1d3aac[1].pos;
        D_1d3aac[1].m124 = 0;
        D_1d3aac[1].retarget = 0;
        D_1d3aac[1].m156 = 0;
        areas->f_0e2d10(&D_1d3aac[1].tgt.x, &D_1d3aac[1].tgt.y, &D_1d3aac[1].tgt.z, -1.5f, pos);
        D_1d3aac[1].tgt.y = D_1d3aac[1].tgt.y + 2200.0f;
    }
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
