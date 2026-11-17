/* The course event jobs (retail 0x0cfaf4 to 0x0d54c8): the things placed along a course that
   come alive as the camera nears them. Every event has a type (0 to 35); each type is a class
   with four static handlers reached through four tables indexed by type: Eval scores how
   urgently the event wants to run (-1: not at all), Run runs it for a frame, Release lets go
   of what it holds, and Flag answers 1. Types without handlers of their own use the base
   class's. The object file ends with the job work list the handlers run under. */

#include <string.h>

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[4][4];
} __attribute__((aligned(16)));

extern "C" {
int f_126f1c(const char *fmt, ...);
Vec4 *f_027dc8(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027e0c(Vec4 *d, const Vec4 *a, const Vec4 *b);
float f_027ebc(const Vec4 *a, const Vec4 *b);
int f_0cc8c8(void *view, const Vec4 &centre, float r);
void f_028c70(void);
void f_028ca8(void);
void f_028d94(Matrix *m);
void f_02842c(void);
void f_0284bc(float a);
void f_0284fc(float a);
void f_02853c(float a);
void f_0287cc(float x, float y, float z);
void f_02884c(float x, float y, float z);
void f_02880c(float x, float y, float z);
void f_028748(const Matrix *m);
void f_028e9c(const void *m);
int f_0fed54(int obj, Matrix *m, int arg, int mode);
}

/* A course object of the event data: its bounding spheres, its distance along the course
   and its draw radius. */
struct EvObject {
    char *name;
    int m4[3];          /* m4[0]: flags */
    void *data;         /* +16: its pack data */
    int nBoxes;
    Vec4 *boxes;
    int m28[4];
    float dist;
    int m48[3];
    float radius;
};

struct EvData {
    EvObject *Obj(int i) { return &objs[i]; }
    void *header;
    EvObject *objs;
};

/* The course's model classes, kept by the map manager. */
struct MapClass {
    int m[4];
};

/* The map manager (src/race/MapManager.cpp), holding the event data at +12144. */
struct MapMgr {
    MapClass *Classes() { return &m12976; }
    EvData *Events() { return &m12144; }
    EvObject &Object(int i) { return m12144.objs[i]; }
    int Rand()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return (int)(seed >> 1) % 32768;
    }
    char m0[12144];
    EvData m12144;
    char m12152[96];
    int length;         /* +12248: the course's length */
    char m12252[724];
    MapClass m12976;    /* the course's model classes */
    int m12992;
    int m12996;
    char valid;
    signed char replay; /* +13001: a replay is running */
    char m13002[2];
    int frame;          /* +13004 */
    int m13008[3];
    unsigned int seed;  /* +13020 */
};
extern MapMgr D_23c820;

/* The camera of the frame being run: its position first. */
extern Vec4 *D_2542a0;

/* The camera's distance along the course. */
#define VIEW_DIST() (*(float *)((char *)D_2542a0 + 704))

/* Whether a sphere is in the camera's view. */
static inline int InView(const Vec4 &c, float r)
{
    return f_0cc8c8(D_2542a0, c, r);
}

/* The camera-facing matrix of the frame being run (built by Begin). */
extern Matrix D_2542b0;

/* The camera-facing matrix about the vertical axis only (built by Begin). */
extern Matrix D_2542f0;

static inline Vec4 ToVec4(const Vec3 &p)
{
    Vec4 r = {0, 0, 0, 0};
    r.x = p.x;
    r.y = p.y;
    r.z = p.z;
    return r;
}

static inline Vec4 operator+(const Vec4 &a, const Vec4 &b)
{
    Vec4 r;
    f_027dc8(&r, &a, &b);
    return r;
}

static inline void Sub(Vec4 *d, Vec4 a, const Vec4 &b)
{
    f_027e0c(d, &a, &b);
}

static inline Vec4 operator-(Vec4 a, const Vec4 &b)
{
    Vec4 r;
    f_027e0c(&r, &a, &b);
    return r;
}

/* A course event as loaded from the event file. */
struct Event {
    short type;
    short m2;
    unsigned int flags;
    int m8;
    int m12;
    Vec3 pos;
    int obj;
    Vec3 m32;           /* the rotation when flag 1 is set */
    Vec3 m44;
};

/* The event's rotation (zero without flag 1) and scale (one without flag 2), from the event
   data's own object file. */
extern "C" Vec3 f_0dacd4(Event *ev);
extern "C" Vec3 f_0dad14(Event *ev);

/* An event parameter by key and index, from the event data's object file. */
extern "C" int *f_0dad68(Event *ev, int key, int i);

/* The course's sound emitters. */
extern char D_27eac0[];
extern "C" void f_0e767c(void *emitters, int kind, float x, float y, float z);
extern "C" int f_0ff388(int obj, Matrix *m, int arg, int colour);
extern "C" void f_0ccaec(float *angle);
extern "C" int f_0ff0ec(int obj, Matrix *m, int arg, int colour, float a, float b);

/* The course's effect manager and the replay flag it is told. */
struct EffectMgr {
    char m0[173156];
    int replay;
};
extern EffectMgr D_2543a0;
extern "C" int f_0e4d28(EffectMgr *m, int arg, Vec4 *view, float x, float y, float z);

/* A looping sound held by the shared object of type 33 (at +16). */
struct EvLoop {
    int m0[4];
    int snd;
};
extern "C" char *f_0d8114(MapClass *c, int id);
extern "C" void f_0daf30(void *pb, char *d);
extern "C" void f_0ec2b8(void *snd);
extern "C" void f_0ec2cc(void *snd);
extern "C" void f_0ec35c(void *snd);
extern "C" void f_0ec2a8(void *snd);
extern "C" void f_0ec2b0(void *snd);
extern "C" void f_0e428c(EffectMgr *m, void *data);
extern "C" void f_0e43ec(EffectMgr *m, void *owner);

/* The frame counter. */
extern int D_23faec;

#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

/* The VFPU's sine and cosine (of a quarter turn per unit). No memory clobber: loads around
   them stay hoisted (CEvent17::Eval keeps the flock pointer out of its loop). */
static inline float VSin(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvsin.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a));
    return r;
}

static inline float VCos(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvcos.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a));
    return r;
}

/* An object shared by every job of one kind, kept alive by a reference count: built when
   the first job takes it. */
struct EvShared;
struct EvSharedVt {
    void (*Init)(EvShared *s);
};
struct EvShared {
    EvSharedVt *vt;
    int m4;
    int ref;
    int m12;
    int *hidden;        /* +16: per part, nonzero to skip it */
    Vec4 *offsets;      /* +20: per part, its offset */
    int m24[2];
    int angle;          /* +32: a turning angle, 65536 to the turn */
    int m36[3];
    Vec4 m48[4];        /* its placement matrix, the last row its offset */
    int m112[256];
    int m1136;
    int m1140[2];
    int m1148;          /* the camera it was last set up for */
    int m1152;          /* a turning angle, 65536 to the turn */
};

/* The shared object of type 34: a frame animation started once the camera passes a point. */
struct EvTimer {
    EvSharedVt *vt;
    int m4;
    int ref;
    int period;
    int count;
    int time;
    int started;
    int m28[2];
    int m36;
};

/* An animation's parameter block (set up by f_0daf30 in the event data's object file). */
struct AnimHdr {
    int m0;
    unsigned short frames;
};
struct AnimBlock {
    AnimHdr *hdr;
    int m4[6];
    float time;         /* +28: the frame shown */
    int m32;
};

/* A sampled animation key: translation, scale and rotation (65536 to the turn). */
struct MotKey {
    float t[3];
    float s[3];
    short r[3];
    short pad;
};
extern "C" void f_0e0778(MotKey *k, AnimBlock *a, int b, int c);

/* An angle of 65536 to the turn in radians. */
static inline float Rad(int a)
{
    return (float)a * 6.2831855f * 1.52587890625e-05f;
}

/* A pigeon of the flock shared by the jobs of type 17 (128 bytes). */
struct HatoBird {
    int state;          /* 0: perched, 1: flying, 2: animated */
    float x, z;         /* its offset from the event */
    float speed;
    float range;        /* +16 */
    float rate;         /* +20 */
    AnimBlock anim;     /* +24 */
    int m60;
    Matrix m;           /* +64 */

    /* Back to rest at a random offset within its range, with a random speed. */
    void Scatter()
    {
        state = 0;
        speed = rate * -1.7881393432617188e-06f * D_23c820.Rand();
        float r = range * 3.0517578125e-05f * D_23c820.Rand();
        float a = (float)(D_23c820.Rand() * 2) * 6.2831855f * 1.52587890625e-05f * 0.63661975f;
        x = r * VCos(a);
        z = r * VSin(a);
        anim.time = 0;
    }
};

/* The shared flock of type 17 (Map::Event::CHatoWork). */
struct EvHato {
    EvSharedVt *vt;
    int m4;
    int ref;
    int count;
    HatoBird *birds;
    int cam;            /* the camera it was last scattered for */
};

struct EvSharedHolder {
    EvShared *p;
};

/* The work record of a running event job. */
struct EventWork {
    int m0;
    Event *ev;
    EvSharedHolder *shared;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
};

class CEventHandler {
public:
    static float Eval(EventWork *w);
    static int Run(EventWork *w, int arg);
    static void Release(EventWork *w);
    static int Flag() { return 1; }
};

#define EVENT_TYPE(N)                               \
    class CEvent##N : public CEventHandler {    \
    public:                                         \
        static float Eval(EventWork *w);            \
        static int Run(EventWork *w, int arg);      \
        static void Release(EventWork *w);          \
        static int Flag() { return 1; }             \
    };

EVENT_TYPE(00)
EVENT_TYPE(01)
EVENT_TYPE(02)
EVENT_TYPE(03)
EVENT_TYPE(04)
EVENT_TYPE(05)
EVENT_TYPE(06)
EVENT_TYPE(12)
EVENT_TYPE(16)
EVENT_TYPE(17)
EVENT_TYPE(18)
EVENT_TYPE(19)
EVENT_TYPE(21)
EVENT_TYPE(23)
EVENT_TYPE(24)
EVENT_TYPE(32)
EVENT_TYPE(33)
EVENT_TYPE(34)

/* Type 20 has handlers of its own but answers through the base class's Flag. */
class CEvent20 : public CEventHandler {
public:
    static float Eval(EventWork *w);
    static int Run(EventWork *w, int arg);
    static void Release(EventWork *w);
};

/* @implements 0x0cfc6c us _ZN8CEvent004Eval
   WHAT IT DOES: Asks to run while the event's object is in view and within its draw radius
   of the camera: nearer objects and objects further along the course score higher. */
float CEvent00::Eval(EventWork *w)
{
    EvData *d = D_23c820.Events();
    Event *ev = w->ev;
    int n = ev->obj;
    Vec4 *box = d->Obj(n)->boxes;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        o = &d->objs[n];
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = ToVec4(w->ev->pos);
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0cfe10 us _ZN8CEvent003Run
   WHAT IT DOES: Draws the event's object at the event's position, rotated and scaled as the
   event says, and returns what the draw returns. */
int CEvent00::Run(EventWork *w, int arg)
{
    Event *ev = w->ev;
    Vec4 p;
    Matrix m;
    int obj;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    p.w = 1.0f;
    obj = ev->obj;
    f_028c70();
    f_02842c();
    f_0287cc(p.x, p.y, p.z);
    if (w->ev->flags & 1) {
        Vec3 r = f_0dacd4(w->ev);
        f_02853c(r.z);
        f_0284fc(r.y);
        f_0284bc(r.x);
    }
    if (w->ev->flags & 2) {
        Vec3 s = f_0dad14(w->ev);
        f_02884c(s.x, s.y, s.z);
    }
    f_028d94(&m);
    f_028ca8();
    return f_0fed54(obj, &m, arg, -1);
}

/* @implements 0x0cff30 us _ZN8CEvent007Release
   WHAT IT DOES: Nothing to release. */
void CEvent00::Release(EventWork *w)
{
}

/* @implements 0x0cff38 us _ZN8CEvent014Eval
   WHAT IT DOES: The same score as type 0's (its own copy of the constants). */
float CEvent01::Eval(EventWork *w)
{
    EvData *d = D_23c820.Events();
    Event *ev = w->ev;
    Vec4 *box = d->Obj(ev->obj)->boxes;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        o = d->Obj(w->ev->obj);
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = ToVec4(w->ev->pos);
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0d00dc us _ZN8CEvent013Run
   WHAT IT DOES: Draws the event's object facing the camera (scaled first when the event
   says) at the event's position, and returns what the draw returns. */
int CEvent01::Run(EventWork *w, int arg)
{
    Event *ev = w->ev;
    Matrix m;

    if (ev->flags & 2) {
        Vec3 s = f_0dad14(ev);
        f_02842c();
        f_028748(&D_2542b0);
        f_02884c(s.x, s.y, s.z);
        f_028d94(&m);
        ev = w->ev;
    } else
        m = D_2542b0;
    m.m[3][0] = ev->pos.x;
    m.m[3][1] = ev->pos.y;
    m.m[3][2] = ev->pos.z;
    return f_0fed54(ev->obj, &m, arg, -1);
}

/* @implements 0x0d01c0 us _ZN8CEvent017Release
   WHAT IT DOES: Nothing to release. */
void CEvent01::Release(EventWork *w)
{
}

/* @implements 0x0d01c8 us _ZN8CEvent204Eval
   WHAT IT DOES: The same score as type 0's (its own copy of the constants). */
float CEvent20::Eval(EventWork *w)
{
    EvData *d = D_23c820.Events();
    Event *ev = w->ev;
    Vec4 *box = d->Obj(ev->obj)->boxes;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        o = d->Obj(w->ev->obj);
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = ToVec4(w->ev->pos);
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0d036c us _ZN8CEvent203Run
   WHAT IT DOES: Draws the event's object facing the camera, fading it in, holding it and
   fading it out over a repeating period (from the frame counter when the period is given
   negative, else from the job's own time); outside the cycle it draws nothing. */
int CEvent20::Run(EventWork *w, int arg)
{
    int period = *f_0dad68(w->ev, 0x3800, 0);
    int hold = *f_0dad68(w->ev, 0xe00000, 0);
    int fade = *f_0dad68(w->ev, 0xe00000, 1);
    int t;
    float a;

    if (period < 0) {
        t = D_23faec;
        period = -period;
    } else
        t = (w->m16 << 10) / 60;
    t %= period;
    a = 1.0f;
    if (t < fade)
        a = (float)t / (float)fade;
    else {
        t -= fade;
        if (t >= hold) {
            t -= hold;
            if (t >= fade)
                return arg;
            a = (float)(fade - t) / (float)fade;
        }
    }
    {
        int colour = ((int)(a * 255.0f) << 24) | 0xffffff;
        Matrix m = D_2542b0;
        Event *ev = w->ev;
        m.m[3][0] = ev->pos.x;
        m.m[3][1] = ev->pos.y;
        m.m[3][2] = ev->pos.z;
        return f_0fed54(ev->obj, &m, arg, colour);
    }
}

/* @implements 0x0d0524 us _ZN8CEvent207Release
   WHAT IT DOES: Nothing to release. */
void CEvent20::Release(EventWork *w)
{
}

/* @draft 0x0d052c us _ZN8CEvent024Eval
   WHAT IT DOES: Asks to run while the camera is within the object's draw radius of the
   event: nearer objects and objects further along the course score higher.
   DIFFERS: the event position's x is loaded into $f1 rather than $f0 (2 words). Deciding
   pass: local-alloc. With sched2 enabled, block_alloc first tries each qty over a lifetime
   widened by one insn on each side (fake_birth/fake_death) to avoid false dependences. y's
   load/store pair is adjacent and goes first (shortest life, $f0); x's store is directly
   followed by y's load, so x's widened life touches y and x takes $f1, and z (right after y's
   store) takes $f1 too. Retail's x $f0, y $f0, z $f1 needs one more insn between x's store
   and y's load in the order local-alloc sees (after sched1 and update_equiv_regs, which moves
   the c = q word loads and the D_2542a0 lui down to their uses), e.g. the D_2542a0 load
   scheduled after x's store by sched1. Not yet found which source shape does that. */
float CEvent02::Eval(EventWork *w)
{
    Event *ev = w->ev;
    EvObject *o = &D_23c820.m12144.objs[ev->obj];
    float r2 = o->radius;
    float dist = o->dist;
    float l2;
    Vec4 c;

    r2 = r2 * r2;
    Vec4 q = ToVec4(ev->pos);
    c = q;
    f_027e0c(&q, &c, D_2542a0);
    l2 = f_027ebc(&q, &q);
    float r;
    if (r2 < l2)
        r = -1.0f;
    else
        r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    return r;
}

/* @implements 0x0d0630 us _ZN8CEvent023Run
   WHAT IT DOES: Draws the event's object turned about the vertical axis to face the camera
   (scaled first when the event says) at the event's position. */
int CEvent02::Run(EventWork *w, int arg)
{
    Event *ev = w->ev;
    int obj = ev->obj;
    Matrix m;

    if (ev->flags & 2) {
        Vec3 s = f_0dad14(ev);
        f_02842c();
        f_028748(&D_2542f0);
        f_02884c(s.x, s.y, s.z);
        f_028d94(&m);
        ev = w->ev;
    } else
        m = D_2542f0;
    m.m[3][0] = ev->pos.x;
    m.m[3][1] = ev->pos.y;
    m.m[3][2] = ev->pos.z;
    return f_0fed54(obj, &m, arg, -1);
}

/* @implements 0x0d0720 us _ZN8CEvent027Release
   WHAT IT DOES: Nothing to release. */
void CEvent02::Release(EventWork *w)
{
}

/* @implements 0x0d0728 us _ZN8CEvent034Eval
   WHAT IT DOES: Never asks to run. */
float CEvent03::Eval(EventWork *w)
{
    return -1.0f;
}

/* @implements 0x0d0734 us _ZN8CEvent033Run
   WHAT IT DOES: Does nothing; passes the argument back. */
int CEvent03::Run(EventWork *w, int arg)
{
    return arg;
}

/* @implements 0x0d073c us _ZN8CEvent037Release
   WHAT IT DOES: Nothing to release. */
void CEvent03::Release(EventWork *w)
{
}

/* @draft 0x0d0744 us _ZN8CEvent044Eval
   WHAT IT DOES: The same score as type 2's (its own copy of the constants).
   DIFFERS: as type 2's. */
float CEvent04::Eval(EventWork *w)
{
    Event *ev = w->ev;
    EvObject *o = &D_23c820.m12144.objs[ev->obj];
    float r2 = o->radius;
    float dist = o->dist;
    float l2;
    Vec4 c;

    r2 = r2 * r2;
    Vec4 q = ToVec4(ev->pos);
    c = q;
    f_027e0c(&q, &c, D_2542a0);
    l2 = f_027ebc(&q, &q);
    float r;
    if (r2 < l2)
        r = -1.0f;
    else
        r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    return r;
}

/* @implements 0x0d0848 us _ZN8CEvent043Run
   WHAT IT DOES: Draws the event's object facing the camera, its facing applied about the
   event's position. */
int CEvent04::Run(EventWork *w, int arg)
{
    Event *ev = w->ev;
    Vec4 p;
    Matrix m;
    int obj;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    p.w = 1.0f;
    obj = ev->obj;
    m = D_2542b0;
    f_028c70();
    f_02842c();
    f_02880c(p.x, p.y, p.z);
    f_028748(&m);
    f_028d94(&m);
    f_028ca8();
    return f_0fed54(obj, &m, arg, -1);
}

/* @implements 0x0d0930 us _ZN8CEvent047Release
   WHAT IT DOES: Nothing to release. */
void CEvent04::Release(EventWork *w)
{
}

/* @implements 0x0d0938 us _ZN8CEvent054Eval
   WHAT IT DOES: Never asks to run. */
float CEvent05::Eval(EventWork *w)
{
    return -1.0f;
}

/* @implements 0x0d0944 us _ZN8CEvent053Run
   WHAT IT DOES: Does nothing; passes the argument back. */
int CEvent05::Run(EventWork *w, int arg)
{
    return arg;
}

/* @implements 0x0d094c us _ZN8CEvent057Release
   WHAT IT DOES: Nothing to release. */
void CEvent05::Release(EventWork *w)
{
}

/* @draft 0x0d0954 us _ZN8CEvent064Eval
   WHAT IT DOES: Takes the shared object on the job's first frame (building it when this is
   the first taker, and restarting it when the camera has changed), places the event at the
   object's offset, starts the event's sound when it has one, and scores like type 0.
   DIFFERS: the first-frame block's layout and the copy of the placed position. */
float CEvent06::Eval(EventWork *w)
{
    Event *ev = w->ev;
    EvShared *sh = w->shared->p;
    int n = ev->obj;
    Vec4 *box;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    if (w->m16 == 0) {
        if (++sh->ref == 1)
            sh->vt->Init(sh);
        if (*(int *)((char *)D_2542a0 + 572) != sh->m1148) {
            sh->m1148 = *(int *)((char *)D_2542a0 + 572);
            sh->m1136 = 0;
        }
    }
    f_027dc8(&p, &p, &sh->m48[3]);
    if (w->ev->flags & 0x80000)
        f_0e767c(D_27eac0, 1, p.x, p.y, p.z);
    EvData *d = D_23c820.Events();
    box = d->Obj(n)->boxes;
    f_027dc8(&c, box, &p);
    if (!InView(c, box->w))
        r = -1.0f;
    else {
        o = &d->objs[n];
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = {0, 0, 0, 0};
        q.x = p.x;
        q.y = p.y;
        q.z = p.z;
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0d0b78 us _ZN8CEvent063Run
   WHAT IT DOES: Draws the event's object with the shared object's matrix at the event's
   position (through the second draw path for objects flagged 0x40). */
int CEvent06::Run(EventWork *w, int arg)
{
    EvShared *sh = w->shared->p;
    int n = w->ev->obj;
    Matrix m;

    f_028c70();
    f_028e9c(sh->m48);
    f_0287cc(w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
    f_028d94(&m);
    f_028ca8();
    if (D_23c820.m12144.Obj(n)->m4[0] & 0x40)
        return f_0ff388(n, &m, arg, -1);
    return f_0fed54(n, &m, arg, -1);
}

/* @implements 0x0d0c3c us _ZN8CEvent067Release
   WHAT IT DOES: Lets go of the shared object, complaining when the count goes below zero. */
void CEvent06::Release(EventWork *w)
{
    EvShared *sh = w->shared->p;
    if (--sh->ref < 0)
        f_126f1c("CEventJobWorkBase  Refrence Counter Overflow!!");
}

/* @implements 0x0d0c80 us _ZN8CEvent214Eval
   WHAT IT DOES: Takes the shared object on the job's first frame (building it when this is
   the first taker), places the event at the object's offset, sets the event's sound going
   (kind 3 when the event says, else 0), and scores like type 0. */
float CEvent21::Eval(EventWork *w)
{
    Event *ev = w->ev;
    EvShared *sh = w->shared->p;
    int n = ev->obj;
    Vec4 *box;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    if (w->m16 == 0) {
        if (++sh->ref == 1)
            sh->vt->Init(sh);
    }
    f_027dc8(&p, &p, &sh->m48[3]);
    if (!(w->ev->flags & 0x80000))
        f_0e767c(D_27eac0, 0, p.x, p.y, p.z);
    else
        f_0e767c(D_27eac0, 3, p.x, p.y, p.z);
    EvData *d = D_23c820.Events();
    box = d->Obj(n)->boxes;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        o = &d->objs[n];
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = {0, 0, 0, 0};
        q.x = p.x;
        q.y = p.y;
        q.z = p.z;
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0d0e94 us _ZN8CEvent213Run
   WHAT IT DOES: Draws the event's object with the shared object's matrix at the event's
   position (rotated when the event says), then up to two turning parts named by the event's
   parameters, placed by the event's part count and kind and turned by the shared angle. */
int CEvent21::Run(EventWork *w, int arg)
{
    EvShared *sh = w->shared->p;
    Matrix m;
    int k;

    f_028c70();
    f_028e9c(sh->m48);
    f_0287cc(w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
    if (w->ev->flags & 1) {
        Vec3 r = f_0dacd4(w->ev);
        f_02853c(r.z);
        f_0284fc(r.y);
        f_0284bc(r.x);
    }
    f_028d94(&m);
    arg = f_0fed54(w->ev->obj, &m, arg, -1);
    k = (w->ev->flags >> 14) & 7;
    f_028c70();
    if (k > 0) {
        if (!(w->ev->flags & 0x80000)) {
            f_0287cc(0.0f, 4400.0f, 100.0f);
            f_0284bc(1.5707964f);
        } else {
            f_0287cc(0.0f, 0.0f, -8200.0f);
            f_0284fc(3.14159f);
        }
        f_02853c(sh->m1152 * 6.2831855f * 1.52587890625e-05f);
        f_028d94(&m);
        arg = f_0fed54(*f_0dad68(w->ev, 0x1c000, 0), &m, arg, -1);
    }
    f_028ca8();
    if (k >= 2) {
        f_0287cc(0.0f, 774.0f, -5477.0f);
        f_0284fc(1.5707964f);
        f_02853c(sh->m1152 * 6.2831855f * 1.52587890625e-05f);
        f_028d94(&m);
        arg = f_0fed54(*f_0dad68(w->ev, 0x1c000, 1), &m, arg, -1);
    }
    f_028ca8();
    return arg;
}

/* @implements 0x0d10c4 us _ZN8CEvent217Release
   WHAT IT DOES: Lets go of the shared object, complaining when the count goes below zero. */
void CEvent21::Release(EventWork *w)
{
    EvShared *sh = w->shared->p;
    if (--sh->ref < 0)
        f_126f1c("CEventJobWorkBase  Refrence Counter Overflow!!");
}

/* @draft 0x0d1108 us _ZN8CEvent164Eval
   WHAT IT DOES: Takes the shared object on the job's first frame (building it when this is
   the first taker) and scores like type 2.
   DIFFERS: as type 2's. */
float CEvent16::Eval(EventWork *w)
{
    EvShared *sh = w->shared->p;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 c;

    if (w->m16 == 0) {
        if (++sh->ref == 1)
            sh->vt->Init(sh);
    }
    Event *ev = w->ev;
    o = &D_23c820.m12144.objs[ev->obj];
    r2 = o->radius;
    dist = o->dist;
    r2 = r2 * r2;
    Vec4 q = ToVec4(ev->pos);
    c = q;
    f_027e0c(&q, &c, D_2542a0);
    l2 = f_027ebc(&q, &q);
    if (r2 < l2)
        r = -1.0f;
    else
        r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    return r;
}

/* @implements 0x0d1258 us _ZN8CEvent163Run
   WHAT IT DOES: Draws the event's object at the event's position (rotated when the event
   says), turned about z by the shared object's angle. */
int CEvent16::Run(EventWork *w, int arg)
{
    int n = w->ev->obj;
    EvShared *sh = w->shared->p;
    Matrix m;
    float a;

    f_028c70();
    f_02842c();
    f_02880c(w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
    if (w->ev->flags & 1) {
        Vec3 r = f_0dacd4(w->ev);
        f_02853c(r.z);
        f_0284fc(r.y);
        f_0284bc(r.x);
    }
    a = sh->angle * 6.2831855f * 1.52587890625e-05f;
    f_0ccaec(&a);
    f_02853c(a);
    f_028d94(&m);
    f_028ca8();
    return f_0fed54(n, &m, arg, -1);
}

/* @implements 0x0d135c us _ZN8CEvent167Release
   WHAT IT DOES: Lets go of the shared object, complaining when the count goes below zero. */
void CEvent16::Release(EventWork *w)
{
    EvShared *sh = w->shared->p;
    if (--sh->ref < 0)
        f_126f1c("CEventJobWorkBase  Refrence Counter Overflow!!");
}

/* @implements 0x0d13a0 us _ZN8CEvent124Eval
   WHAT IT DOES: Always scores 0. */
float CEvent12::Eval(EventWork *w)
{
    return 0.0f;
}

/* @implements 0x0d13ac us _ZN8CEvent123Run
   WHAT IT DOES: Does nothing; passes the argument back. */
int CEvent12::Run(EventWork *w, int arg)
{
    return arg;
}

/* @implements 0x0d13b4 us _ZN8CEvent127Release
   WHAT IT DOES: Nothing to release. */
void CEvent12::Release(EventWork *w)
{
}

/* @implements 0x0d13bc us _ZN8CEvent244Eval
   WHAT IT DOES: On the job's first frame picks its animation start (a random phase when the
   event's period is negative, else the current frame), then scores like type 0. */
float CEvent24::Eval(EventWork *w)
{
    Event *ev = w->ev;
    int n = ev->obj;
    EvData *d;
    Vec4 *box;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    if (w->m16 == 0) {
        if (*f_0dad68(ev, 0x3800, 0) < 0)
            w->m24 = D_23c820.Rand();
        else
            w->m24 = D_23c820.frame;
    }
    d = D_23c820.Events();
    box = d->Obj(n)->boxes;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        o = &d->objs[n];
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = ToVec4(w->ev->pos);
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0d15c8 us _ZN8CEvent243Run
   WHAT IT DOES: Draws the event's object at the event's position through the animated draw:
   the model index steps through the event's frame count at its period from the job's start,
   with a blend weight from two more parameters. */
int CEvent24::Run(EventWork *w, int arg)
{
    Event *ev = w->ev;
    Vec4 p;
    Matrix m;
    int obj, period, count, k;
    float a;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    p.w = 1.0f;
    obj = ev->obj;
    period = *f_0dad68(ev, 0x3800, 0);
    count = *f_0dad68(w->ev, 0x40000, 0);
    int num = *f_0dad68(w->ev, 0xe00000, 1);
    int den = *f_0dad68(w->ev, 0xe00000, 2);
    k = ((D_23faec - w->m24) << 10) / (period * 60) % count;
    a = (float)num / (float)den;
    f_028c70();
    f_02842c();
    f_02880c(p.x, p.y, p.z);
    f_028d94(&m);
    f_028ca8();
    return f_0ff0ec(obj + k, &m, arg, -1, a, 0.0f);
}

/* @implements 0x0d1730 us _ZN8CEvent247Release
   WHAT IT DOES: Nothing to release. */
void CEvent24::Release(EventWork *w)
{
}

/* @implements 0x0d1738 us _ZN8CEvent234Eval
   WHAT IT DOES: On the job's first frame picks its animation start (a random phase within the
   frame count when the event's period is negative, else the current frame), then scores like
   type 0. */
float CEvent23::Eval(EventWork *w)
{
    Event *ev = w->ev;
    int n = ev->obj;
    EvData *d;
    Vec4 *box;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    if (w->m16 == 0) {
        if (*f_0dad68(ev, 0x3800, 0) < 0) {
            int f = D_23c820.frame;
            if (f == 0)
                w->m24 = 0;
            else
                w->m24 = D_23c820.Rand() % f;
        } else
            w->m24 = D_23c820.frame;
    }
    d = D_23c820.Events();
    box = d->Obj(n)->boxes;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        o = &d->objs[n];
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = ToVec4(w->ev->pos);
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @draft 0x0d1964 us _ZN8CEvent233Run
   WHAT IT DOES: Draws the event's frames at the event's position (rotated when the event
   says): the current frame of the cycle fully, fading in over the event's fade time, and the
   other frames fading out over the fade time after their turn.
   DIFFERS: retail keeps the fade-time block in line after its test; this build moves it out
   of line, shifting the code that follows. */
int CEvent23::Run(EventWork *w, int arg)
{
    Event *ev = w->ev;
    Vec4 p;
    Matrix m;
    float fade = 0.0f;
    int obj, period, count, t, cur, cycle, i;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    p.w = 1.0f;
    obj = ev->obj;
    if ((ev->flags & 0x3800) > 0x800) {
        fade = *f_0dad68(ev, 0x3800, 1) * 60.0f;
        if (fade < 0.0f)
            fade = -fade;
    }
    period = *f_0dad68(w->ev, 0x3800, 0) * 60;
    count = *f_0dad68(w->ev, 0x40000, 0);
    if (period < 0)
        period = -period;
    t = (D_23faec - w->m24) << 10;
    cur = t / period % count;
    f_028c70();
    f_02842c();
    f_02880c(p.x, p.y, p.z);
    if (w->ev->flags & 1) {
        Vec3 r = f_0dacd4(w->ev);
        f_02853c(r.z);
        f_0284fc(r.y);
        f_0284bc(r.x);
    }
    f_028d94(&m);
    f_028ca8();
    for (i = 0; i < count; i++) {
        cycle = count * period;
        if (i == cur) {
            float f = (float)(t % period);
            if (f < fade) {
                f = f / fade;
                if (f < 0.0f)
                    f = 0.0f;
                if (1.0f < f)
                    f = 1.0f;
                arg = f_0fed54(obj + i, &m, arg, ((int)(f * 254.0f) << 24) | 0xffffff);
            } else
                arg = f_0fed54(obj + i, &m, arg, -1);
        } else {
            float f = (float)((t - (i + 1) * period) % cycle);
            if (0.0f <= f && f < fade) {
                f = 1.0f - f / fade;
                if (f < 0.0f)
                    f = 0.0f;
                if (1.0f < f)
                    f = 1.0f;
                arg = f_0fed54(obj + i, &m, arg, ((int)(f * 254.0f) << 24) | 0xffffff);
            }
        }
    }
    return arg;
}

/* @implements 0x0d1c98 us _ZN8CEvent237Release
   WHAT IT DOES: Nothing to release. */
void CEvent23::Release(EventWork *w)
{
}

/* @draft 0x0d1ca0 us _ZN8CEvent184Eval
   WHAT IT DOES: Takes the shared object on the job's first frame (building it when this is
   the first taker) and scores like type 2.
   DIFFERS: as type 2's. */
float CEvent18::Eval(EventWork *w)
{
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 c;

    if (w->m16 == 0) {
        EvShared *sh = w->shared->p;
        if (++sh->ref == 1)
            sh->vt->Init(sh);
    }
    Event *ev = w->ev;
    o = &D_23c820.m12144.objs[ev->obj];
    r2 = o->radius;
    dist = o->dist;
    r2 = r2 * r2;
    Vec4 q = ToVec4(ev->pos);
    c = q;
    f_027e0c(&q, &c, D_2542a0);
    l2 = f_027ebc(&q, &q);
    if (r2 < l2)
        r = -1.0f;
    else
        r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    return r;
}

/* An angle in radians wrapped to one turn through the 16-bit angle, and its reverse. */
static inline float WrapAngle(float a)
{
    return (float)((int)(a * 65536.0f / 6.2831855f) & 0xffff) * 6.2831855f * 1.52587890625e-05f;
}

static inline float ReverseAngle(float a)
{
    return (float)(0xffff - (int)(a * 65536.0f / 6.2831855f)) * 6.2831855f * 1.52587890625e-05f;
}

/* @implements 0x0d1df0 us _ZN8CEvent183Run
   WHAT IT DOES: Draws each of the shared object's two parts that is not hidden: at the event's
   position and rotation, then at the part's offset with the rotation undone (scaled when the
   event says), facing the camera. */
int CEvent18::Run(EventWork *w, int arg)
{
    int obj = w->ev->obj;
    EvShared *sh = w->shared->p;
    Matrix m;
    int i;

    for (i = 0; i < 2; i++) {
        int *h = &sh->hidden[i];
        if (*h > 0)
            continue;
        f_028c70();
        f_02842c();
        f_0287cc(w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
        if (w->ev->flags & 1) {
            Vec3 r = f_0dacd4(w->ev);
            f_02853c(WrapAngle(r.z));
            f_0284fc(WrapAngle(r.y));
            f_0284bc(WrapAngle(r.x));
        }
        {
            Vec4 *o = &sh->offsets[i];
            f_0287cc(o->x, o->y, o->z);
        }
        if (w->ev->flags & 1) {
            Vec3 r = f_0dacd4(w->ev);
            f_0284bc(ReverseAngle(r.x));
            f_0284fc(ReverseAngle(r.y));
            f_02853c(ReverseAngle(r.z));
        }
        if (w->ev->flags & 2) {
            Vec3 sc = f_0dad14(w->ev);
            f_02884c(sc.x, sc.y, sc.z);
        }
        f_028748(&D_2542b0);
        f_028d94(&m);
        f_028ca8();
        arg = f_0fed54(obj, &m, arg, -1);
    }
    return arg;
}

/* @implements 0x0d20a8 us _ZN8CEvent187Release
   WHAT IT DOES: Lets go of the shared object, complaining when the count goes below zero. */
void CEvent18::Release(EventWork *w)
{
    EvShared *sh = w->shared->p;
    if (--sh->ref < 0)
        f_126f1c("CEventJobWorkBase  Refrence Counter Overflow!!");
}

/* @implements 0x0d20ec us _ZN8CEvent324Eval
   WHAT IT DOES: Always scores 2000. */
float CEvent32::Eval(EventWork *w)
{
    return 2000.0f;
}

/* @implements 0x0d20f8 us _ZN8CEvent323Run
   WHAT IT DOES: Sets the event's sound going (kind 2) at the event's position and runs the
   effect manager there, telling it whether this is a replay. */
int CEvent32::Run(EventWork *w, int arg)
{
    f_0e767c(D_27eac0, 2, w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
    D_2543a0.replay = D_23c820.replay;
    return f_0e4d28(&D_2543a0, arg, D_2542a0, w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
}

/* @implements 0x0d2184 us _ZN8CEvent327Release
   WHAT IT DOES: Nothing to release. */
void CEvent32::Release(EventWork *w)
{
}

/* @implements 0x0d218c us _ZN8CEvent334Eval
   WHAT IT DOES: Starts the shared looping sound on the job's first frame, keeps it going, and
   scores 0. */
float CEvent33::Eval(EventWork *w)
{
    EvLoop *l = (EvLoop *)w->shared->p;
    if (w->m16 == 0)
        f_0ec2b8(&l->snd);
    f_0ec2cc(&l->snd);
    return 0.0f;
}

/* @implements 0x0d21d8 us _ZN8CEvent333Run
   WHAT IT DOES: Does nothing; passes the argument back. */
int CEvent33::Run(EventWork *w, int arg)
{
    return arg;
}

/* @implements 0x0d21e0 us _ZN8CEvent337Release
   WHAT IT DOES: Stops the shared looping sound. */
void CEvent33::Release(EventWork *w)
{
    f_0ec35c(&((EvLoop *)w->shared->p)->snd);
}

/* @implements 0x0d2204 us _ZN8CEvent174Eval
   WHAT IT DOES: Takes the shared flock on the job's first frame (building it when this is the
   first taker) and, when the camera has cut, scatters every pigeon to a random offset at rest;
   once the camera passes the event's start distance, sets the perched flock flying. Scores 0.
   The animation time it clears is a float: an int store there orders differently in sched2. */
float CEvent17::Eval(EventWork *w)
{
    EvHato *sh = (EvHato *)w->shared->p;

    if (w->m16 == 0) {
        if (++sh->ref == 1)
            sh->vt->Init((EvShared *)sh);
        int cam = *(int *)((char *)D_2542a0 + 572);
        if (cam != sh->cam) {
            sh->cam = cam;
            for (int i = 0; i < sh->count; i++) {
                HatoBird *b = &sh->birds[i];
                b->state = 0;
                b->speed = b->rate * -1.7881393432617188e-06f * D_23c820.Rand();
                float r = b->range * 3.0517578125e-05f * D_23c820.Rand();
                float a = (float)(D_23c820.Rand() * 2) * 6.2831855f * 1.52587890625e-05f * 0.63661975f;
                b->x = r * VCos(a);
                b->z = r * VSin(a);
                b->anim.time = 0;
            }
        }
    }
    if (sh->birds->state == 0) {
        int len = D_23c820.length;
        int at = (int)VIEW_DIST() + len - w->ev->m8;
        while (at >= len)
            at -= len;
        if (at >= *f_0dad68(w->ev, 0x700, 0))
            for (int i = 0; i < sh->count; i++)
                sh->birds[i].state = 1;
    }
    return 0.0f;
}

/* @draft 0x0d247c us _ZN8CEvent173Run
   WHAT IT DOES: Draws every pigeon of the shared flock at the event's position plus its
   offset, with its own matrix, either facing the camera or (flag 0x80000) turned by the
   event's rotation on both sides. A flying pigeon (state 2) runs its wing frames from its
   speed; when the event gives a hold range, a pigeon past it shows the last frame.
   Remaining difference: the translation call's arguments are built z first in retail (the
   offset's z in $f0, pos.z loaded before pos.x, the z sum added first); here expand_call
   evaluates them left to right. The shape that puts z first is not found. */
int CEvent17::Run(EventWork *w, int arg)
{
    EvHato *sh = (EvHato *)w->shared->p;
    int frames = *f_0dad68(w->ev, 0x40000, 0);
    int period = *f_0dad68(w->ev, 0xe00000, 0);
    int from = -1, len = -1;
    Matrix m;

    int keys = (w->ev->flags >> 21) & 7;
    if (keys >= 6) {
        from = *f_0dad68(w->ev, 0xe00000, 4);
        len = *f_0dad68(w->ev, 0xe00000, 5);
    }
    int face = !(w->ev->flags & 0x80000);
    f_028c70();
    for (int i = 0; i < sh->count; i++) {
        HatoBird *b = &sh->birds[i];
        f_02842c();
        f_0287cc(w->ev->pos.x + b->x, w->ev->pos.y, w->ev->pos.z + b->z);
        if (!face && (w->ev->flags & 1)) {
            Vec3 r = f_0dacd4(w->ev);
            f_02853c(r.z);
            f_0284fc(r.y);
            f_0284bc(r.x);
        }
        f_028748(&b->m);
        if (face)
            f_028748(&D_2542b0);
        else if (w->ev->flags & 1) {
            Vec3 r = f_0dacd4(w->ev);
            f_02853c(r.z);
            f_0284fc(r.y);
            f_0284bc(r.x);
        }
        f_028d94(&m);
        int frame = 0;
        if (b->state == 2) {
            float t = b->speed * 1024.0f;
            frame = (int)(t / ((float)period * 60.0f)) % (frames - 1) + 1;
            if (from >= 0 && len > 0 && (int)(t / 60.0f) % (from + len) > from)
                frame = frames - 1;
        }
        arg = f_0fed54(w->ev->obj + frame, &m, arg, -1);
    }
    f_028ca8();
    return arg;
}

/* @implements 0x0d274c us _ZN8CEvent177Release
   WHAT IT DOES: Lets go of the shared object, complaining when the count goes below zero. */
void CEvent17::Release(EventWork *w)
{
    EvShared *sh = w->shared->p;
    if (--sh->ref < 0)
        f_126f1c("CEventJobWorkBase  Refrence Counter Overflow!!");
}

/* @draft 0x0d2790 us _ZN8CEvent194Eval
   WHAT IT DOES: While the event's object is in view, sets the job's alpha by interpolating the
   event's (distance, alpha) keys at the camera's distance along the course (fading to 0 at the
   event's end distance), then scores like type 0; without keys it never runs.
   DIFFERS: the job and the map manager take each other's saved registers, and the map
   manager's address is rebuilt after the key search. */
float CEvent19::Eval(EventWork *w)
{
    MapMgr *mm = &D_23c820;
    Event *ev = w->ev;
    int obj = ev->obj;
    Vec4 *box = mm->m12144.objs[obj].boxes;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;
    int pd = 0, pa = 0, nd, na, d, i, n;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    f_027dc8(&c, box, &p);
    if (!f_0cc8c8(D_2542a0, c, box->w))
        r = -1.0f;
    else {
        w->m24 = 100;
        ev = w->ev;
        n = (ev->flags >> 21) & 7;
        if (n == 0)
            r = -1.0f;
        else {
            int len = mm->length;
            d = ((int)VIEW_DIST() + len - ev->m8) % len;
            nd = 0;
            na = 100;
            for (i = 0; i < n; i++) {
                pa = na;
                pd = nd;
                nd = *f_0dad68(w->ev, 0x700, i);
                na = *f_0dad68(w->ev, 0xe00000, i);
                if (d < nd)
                    break;
            }
            ev = w->ev;
            if (i == n) {
                pd = nd;
                nd = ev->m12;
                pa = na;
                na = 0;
            }
            if (nd - pd == 0)
                w->m24 = na;
            else
                w->m24 = ((nd - d) * pa + (d - pd) * na) / (nd - pd);
            o = &D_23c820.m12144.objs[obj];
            r2 = o->radius;
            dist = o->dist;
            r2 = r2 * r2;
            Vec4 q = ToVec4(ev->pos);
            c = q;
            f_027e0c(&q, &c, D_2542a0);
            l2 = f_027ebc(&q, &q);
            if (r2 < l2)
                r = -1.0f;
            else
                r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
        }
    }
    return r;
}

/* @implements 0x0d2a54 us _ZN8CEvent193Run
   WHAT IT DOES: Draws the event's object at the event's position (rotated when the event
   says), facing the camera unless flagged 0x80000, scaled when the event says, with the alpha
   its score left in the job. */
int CEvent19::Run(EventWork *w, int arg)
{
    Matrix m;

    f_028c70();
    f_02842c();
    f_0287cc(w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
    if (w->ev->flags & 1) {
        Vec3 r = f_0dacd4(w->ev);
        f_02853c(r.z);
        f_0284fc(r.y);
        f_0284bc(r.x);
    }
    if (!(w->ev->flags & 0x80000))
        f_028748(&D_2542b0);
    if (w->ev->flags & 2) {
        Vec3 sc = f_0dad14(w->ev);
        f_02884c(sc.x, sc.y, sc.z);
    }
    f_028d94(&m);
    f_028ca8();
    return f_0fed54(w->ev->obj, &m, arg, (w->m24 << 24) | 0xffffff);
}

/* @implements 0x0d2b74 us _ZN8CEvent197Release
   WHAT IT DOES: Nothing to release. */
void CEvent19::Release(EventWork *w)
{
}

/* @draft 0x0d2b7c us _ZN8CEvent344Eval
   WHAT IT DOES: Starts the shared animation (once) when the camera's distance along the
   course reaches the event's start distance, then scores like type 0.
   DIFFERS: the object table load in the visible arm takes v1 rather than v0, and the camera
   pointer is loaded late for the subtraction (+4 B). */
float CEvent34::Eval(EventWork *w)
{
    Event *ev = w->ev;
    EvTimer *t = (EvTimer *)w->shared->p;
    int n = ev->obj;
    EvData *d;
    Vec4 *box;
    EvObject *o;
    float r2, dist, l2, r;
    Vec4 p = {0, 0, 0, 0};
    Vec4 c;
    int start, len, at;

    p.x = ev->pos.x;
    p.y = ev->pos.y;
    p.z = ev->pos.z;
    start = *f_0dad68(ev, 0x700, 0);
    len = D_23c820.length;
    at = (int)VIEW_DIST() + len - w->ev->m8;
    while (at >= len)
        at -= len;
    if (at >= start && t->started == 0) {
        t->started = 1;
        t->time = 0;
        t->m36 = 0;
    }
    d = D_23c820.Events();
    box = d->Obj(n)->boxes;
    f_027dc8(&c, box, &p);
    if (!InView(c, box->w))
        r = -1.0f;
    else {
        o = &d->objs[n];
        r2 = o->radius;
        dist = o->dist;
        r2 = r2 * r2;
        Vec4 q = ToVec4(w->ev->pos);
        c = q;
        f_027e0c(&q, &c, D_2542a0);
        l2 = f_027ebc(&q, &q);
        if (r2 < l2)
            r = -1.0f;
        else
            r = (dist + 0.999f) - l2 / 2000.0f / 2000.0f / 1000.0f / 1000.0f;
    }
    return r;
}

/* @implements 0x0d2da0 us _ZN8CEvent343Run
   WHAT IT DOES: Draws the frame of the shared animation its time has reached at the event's
   position (rotated and scaled as the event says). */
int CEvent34::Run(EventWork *w, int arg)
{
    EvTimer *t = (EvTimer *)w->shared->p;
    Matrix m;

    f_028c70();
    f_02842c();
    f_0287cc(w->ev->pos.x, w->ev->pos.y, w->ev->pos.z);
    if (w->ev->flags & 1) {
        Vec3 r = f_0dacd4(w->ev);
        f_02853c(r.z);
        f_0284fc(r.y);
        f_0284bc(r.x);
    }
    if (w->ev->flags & 2) {
        Vec3 sc = f_0dad14(w->ev);
        f_02884c(sc.x, sc.y, sc.z);
    }
    f_028d94(&m);
    f_028ca8();
    return f_0fed54(w->ev->obj + t->time / (t->period * 60) % t->count, &m, arg, -1);
}

/* @implements 0x0d2ecc us _ZN8CEvent347Release
   WHAT IT DOES: Nothing to release. */
void CEvent34::Release(EventWork *w)
{
}

/* @implements 0x0d2ed4 us _ZN13CEventHandler4Eval
   WHAT IT DOES: Default: never asks to run. */
float CEventHandler::Eval(EventWork *w)
{
    return -1.0f;
}

/* @implements 0x0d2ee0 us _ZN13CEventHandler3Run
   WHAT IT DOES: Default: does nothing; passes the argument back. */
int CEventHandler::Run(EventWork *w, int arg)
{
    return arg;
}

/* @implements 0x0d2ee8 us _ZN13CEventHandler7Release
   WHAT IT DOES: Default: nothing to release. */
void CEventHandler::Release(EventWork *w)
{
}

/* One set of event data (src/race/EventBuffer.cpp): its events and, per event, its work
   object. */
struct Block {
    int count;
    Event **events;
    void **work;

    void *&Work(int i) { return work[i]; }
};

namespace Map {
namespace Event {

/* The work objects shared by the jobs of one kind of event: set up from an event, updated
   once a frame while any job holds them, stopped when the last job lets go. */
class CEventJobWorkBase {
public:
    virtual void Update() = 0;
    virtual void Setup(::Event *e) = 0;
    virtual void Stop() = 0;
    virtual void Reset();
    CEventJobWorkBase() : ref(0) {}
    void Init() {}

    ::Event *ev;
    int ref;
};

/* Moving models (type 6 and relatives): a placement matrix and a camera cut counter. */
class CMotWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();
    virtual void Reset();

    AnimBlock anim;     /* +12 */
    Vec4 matrix[4];
    int m112[256];
    float m1136;        /* the animation's start time */
    float m1140;        /* its speed */
    char loop;          /* +1144 */
    int cam;

    void Init();

    /* Steps the animation time by the speed (wrapping when it loops, else holding at the
       end). */
    void Step()
    {
        m1136 = m1136 + m1140;
        float last = (float)(anim.hdr->frames - 1);
        if (last <= m1136 / 60.0f) {
            float end = last * 60.0f;
            if (loop)
                m1136 = m1136 - end;
            else
                m1136 = end;
        }
        anim.time = m1136 / 60.0f;
    }
};

/* The helicopter: a moving model of its own. */
class CHeliWork : public CMotWork {
public:
    virtual void Update();
    CHeliWork() { m1164 = 0; m1160 = 0; m1156 = 0; angle = 0; }

    int angle;
    int m1156;
    int m1160;
    int m1164;
};

/* The cyclists. */
class CCycleWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();
    CCycleWork() { m12 = 0; m16 = 0; }

    int *m12;
    int *m16;
    int m20[4];
};

/* The flashes. */
class CFlashWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();
    CFlashWork() { m16 = 0; m20 = 0; }

    int m12;
    int *m16;
    int *m20;
};

/* The fireworks: started through the effect manager. */
class CHanabiWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();
    CHanabiWork() { active = 0; }

    int active;
};

/* The falling leaves. */
class CLeafWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();
    bool IsActive() { return active == 1; }
    CLeafWork() { active = 0; }

    int active;
    int m16;
    int count;
    float pos[3];
    float rot[3];
    unsigned char colour[3];
    int m52;
};

/* The pigeons. */
class CHatoWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();

    int count;
    HatoBird *birds;
    int cam;
};

/* The cows: a frame animation run forwards or backwards on cue. */
class CUshiWork : public CEventJobWorkBase {
public:
    virtual void Update();
    virtual void Setup(::Event *e);
    virtual void Stop();
    virtual void Reset();

    int period;
    int count;
    int time;
    int state;
    int length;
    int cam;
    int m36;
    int frame;
};

/* The work objects of one kind: an array built from the events of one type. */
template <class T> class CWorkList {
public:
    void Build(Block *b, int type)
    {
        int i, k;

        count = 0;
        for (i = 0; i < b->count; i++)
            if (b->events[i]->type == type)
                count++;
        if (count == 0) {
            arr = 0;
            return;
        }
        arr = new T[count];
        k = 0;
        for (i = 0; i < b->count; i++) {
            ::Event *e = b->events[i];
            if (e->type == type) {
                arr[k].Setup(e);
                arr[k].Init();
                b->Work(i) = &arr[k];
                k++;
            }
        }
    }
    void UpdateAll()
    {
        for (int i = 0; i < count; i++)
            arr[i].Update();
    }
    void ResetAll()
    {
        for (int i = 0; i < count; i++)
            arr[i].Reset();
    }
    void Free()
    {
        int i;

        for (i = 0; i < count; i++)
            arr[i].Stop();
        delete[] arr;
    }

    T *arr;
    int count;
};

extern CWorkList<CMotWork> D_254330;
extern CWorkList<CHeliWork> D_254338;
extern CWorkList<CCycleWork> D_254340;
extern CWorkList<CFlashWork> D_254348;
extern CWorkList<CHanabiWork> D_254350;
extern CWorkList<CLeafWork> D_254358;
extern CWorkList<CHatoWork> D_254360;
extern CWorkList<CUshiWork> D_254368;

/* @implements 0x0d2ef0 us f_0d2ef0
   WHAT IT DOES: Builds the work objects of every kind from a set of event data: for each kind,
   counts the events of its type, allocates that many objects, sets each up from its event and
   records it as the event's work object. */
extern "C" void f_0d2ef0(Block *b)
{
    D_254330.Build(b, 6);
    D_254338.Build(b, 21);
    D_254340.Build(b, 16);
    D_254348.Build(b, 18);
    D_254350.Build(b, 32);
    D_254358.Build(b, 33);
    D_254360.Build(b, 17);
    D_254368.Build(b, 34);
}

/* @implements 0x0d37bc us f_0d37bc
   WHAT IT DOES: Stops every work object of every kind and frees the arrays. Free's first call
   is instantiated eagerly too, and is inlined only when written with a plain `delete[] arr`
   (the compiler's own null test): with an explicit `if` the eager instance is refused. */
extern "C" void f_0d37bc(void)
{
    D_254330.Free();
    D_254338.Free();
    D_254340.Free();
    D_254348.Free();
    D_254350.Free();
    D_254358.Free();
    D_254360.Free();
    D_254368.Free();
}

/* @implements 0x0d3b2c us f_0d3b2c
   WHAT IT DOES: Updates every work object of every kind for a frame (the view arguments are
   not used). */
extern "C" void f_0d3b2c(int a, void *view, void *s)
{
    D_254330.UpdateAll();
    D_254338.UpdateAll();
    D_254340.UpdateAll();
    D_254348.UpdateAll();
    D_254350.UpdateAll();
    D_254358.UpdateAll();
    D_254360.UpdateAll();
    D_254368.UpdateAll();
}

/* @implements 0x0d3d94 us f_0d3d94
   WHAT IT DOES: Resets the work objects of the kinds that keep a camera cut counter (the
   moving models, the helicopter and the cows). */
extern "C" void f_0d3d94(void)
{
    D_254330.ResetAll();
    D_254338.ResetAll();
    D_254368.ResetAll();
}

/* @implements 0x0d3e98 us _ZN3Map5Event8CMotWork5Setup
   WHAT IT DOES: Takes the event. */
void CMotWork::Setup(::Event *e)
{
    ev = e;
}

/* @implements 0x0d3ea0 us _ZN3Map5Event8CMotWork4Stop
   WHAT IT DOES: Nothing to stop. */
void CMotWork::Stop()
{
}

/* @implements 0x0d3ea8 us _ZN3Map5Event17CEventJobWorkBase5Reset
   WHAT IT DOES: Default: nothing to reset. */
void CEventJobWorkBase::Reset()
{
}

/* @draft 0x0d3eb0 us _ZN3Map5Event8CMotWork4Init
   WHAT IT DOES: Sets the moving model up from its event: its animation's parameter block from
   the model class the event names, its start time and speed (from the event's parameters
   when given, else 0 and 60), whether it loops, and no camera seen yet.
   Remaining difference: the first test's arms are laid out the other way round. The bp pass
   gives `n < 2` the opcode-positive heuristic (canonicalised to n > 1, 79%) on top of the call
   heuristic (30%), 61.7% for the call arm, so bbro makes it the fall-through; retail keeps
   the zero store there, as for `n < 3`. */
void CMotWork::Init()
{
    int id = *f_0dad68(ev, 0xe0, 0);
    memset(&anim, 0, sizeof anim);
    f_0daf30(&anim, f_0d8114(D_23c820.Classes(), id));
    int n = (ev->flags & 0x3800) >> 11;
    if (n < 2)
        m1136 = 0;
    else
        m1136 = (float)*f_0dad68(ev, 0x3800, 1) * 60.0f;
    if (n < 3)
        m1140 = 60.0f;
    else
        m1140 = (float)*f_0dad68(ev, 0x3800, 2) * 0.6f;
    if (*f_0dad68(ev, 0x3800, 0))
        loop = 0;
    else
        loop = 1;
    cam = -1;
}

/* @implements 0x0d3fe8 us _ZN3Map5Event8CMotWork5Reset
   WHAT IT DOES: Clears the cut counter. */
void CMotWork::Reset()
{
    m1136 = 0;
}

/* @implements 0x0d3ff0 us _ZN3Map5Event9CHeliWork6Update
   WHAT IT DOES: While any job holds it, turns its four bobbing angles and (outside replays)
   steps its animation and builds its matrix: the key's translation lifted by a bob of 150,
   the key's rotation with an extra sway about y, and the key's scale. The replay flag is the
   map manager's member (+13001): as a scalar global, alias analysis lets sched1 hoist its
   load above the angle stores. The keys are plain locals (through a pointer parameter they
   take a saved register). */
void CHeliWork::Update()
{
    if (ref == 0)
        return;
    angle = (angle - 7827) & 0xffff;
    m1156 = (m1156 - 4187) & 0xffff;
    m1160 = (m1160 + 236) & 0xffff;
    m1164 = (m1164 + 509) & 0xffff;
    if (D_23c820.replay)
        return;
    MotKey k0, k1;
    Step();
    f_0e0778(&k0, &anim, 0, 0);
    f_0e0778(&k1, &anim, 0, 1);
    f_028c70();
    f_02842c();
    f_0287cc(k0.t[0], k0.t[1] + VSin(Rad(m1164) * 0.63661975f) * 150.0f, k0.t[2]);
    f_02853c(Rad(k1.r[2]));
    f_0284fc(Rad(k1.r[1]));
    f_0284fc(VSin(Rad(m1160) * 0.63661975f) * 0.031459f);
    f_0284bc(Rad(k1.r[0]));
    f_02884c(k0.s[0], k0.s[1], k0.s[2]);
    f_028d94((Matrix *)matrix);
    f_028ca8();
}

/* @implements 0x0d4380 us _ZN3Map5Event10CCycleWork4Stop
   WHAT IT DOES: Frees the two tables. */
void CCycleWork::Stop()
{
    if (m12)
        delete[] m12;
    if (m16)
        delete[] m16;
}

/* @implements 0x0d46e0 us _ZN3Map5Event10CFlashWork4Stop
   WHAT IT DOES: Frees the two tables. */
void CFlashWork::Stop()
{
    if (m16)
        delete[] m16;
    if (m20)
        delete[] m20;
}

/* @implements 0x0d492c us _ZN3Map5Event11CHanabiWork5Setup
   WHAT IT DOES: Starts the event object's firework through the effect manager, once. */
void CHanabiWork::Setup(::Event *e)
{
    if (active == 0) {
        active = 1;
        f_0e428c(&D_2543a0, D_23c820.m12144.Obj(e->obj)->data);
    }
}

/* @draft 0x0d4980 us _ZN3Map5Event11CHanabiWork4Stop
   WHAT IT DOES: Stops the firework if it is running.
   DIFFERS: the field test is scheduled differently against the prologue (+4 B). */
void CHanabiWork::Stop()
{
    if (active == 1) {
        active = 0;
        f_0e43ec(&D_2543a0, this);
    }
}

/* @implements 0x0d49bc us _ZN3Map5Event11CHanabiWork6Update
   WHAT IT DOES: Nothing per frame. */
void CHanabiWork::Update()
{
}

/* @implements 0x0d49c4 us _ZN3Map5Event9CLeafWork5Setup
   WHAT IT DOES: Takes the event, starts the leaves once, and copies the event's position,
   rotation (zero without one), leaf count and colour. */
void CLeafWork::Setup(::Event *e)
{
    ev = e;
    if (active == 0) {
        active = 1;
        f_0ec2a8(this);
    }
    pos[0] = ev->pos.x;
    pos[1] = ev->pos.y;
    pos[2] = ev->pos.z;
    if (ev->flags & 1) {
        Vec3 r = f_0dacd4(ev);
        rot[0] = r.x;
        rot[1] = r.y;
        rot[2] = r.z;
    } else {
        rot[0] = 0;
        rot[1] = 0;
        rot[2] = 0;
    }
    count = *f_0dad68(ev, 0x40000, 0);
    colour[0] = *f_0dad68(ev, 0xe00000, 0);
    colour[1] = *f_0dad68(ev, 0xe00000, 1);
    colour[2] = *f_0dad68(ev, 0xe00000, 2);
}

/* @draft 0x0d4ac4 us _ZN3Map5Event9CLeafWork4Stop
   WHAT IT DOES: Stops the leaves if they are running.
   DIFFERS: retail loads the field ahead of the stack adjustment and fills the branch slot
   with the return address store; this build keeps the prologue first (+4 B). */
void CLeafWork::Stop()
{
    if (active == 1) {
        active = 0;
        f_0ec2b0(this);
    }
}

/* @implements 0x0d4af4 us _ZN3Map5Event9CLeafWork6Update
   WHAT IT DOES: Nothing per frame. */
void CLeafWork::Update()
{
}

/* @implements 0x0d4afc us _ZN3Map5Event9CHatoWork5Setup
   WHAT IT DOES: Takes the event and builds its flock: the bird count, rate and range from the
   event's parameters, each bird's animation from the model class the event names, each
   scattered at rest; no camera seen yet (rate stored before range: sched2 keeps source
   order). */
void CHatoWork::Setup(::Event *e)
{
    ev = e;
    float rate = (float)*f_0dad68(e, 0xe00000, 2);
    float range = (float)*f_0dad68(e, 0xe00000, 3);
    count = *f_0dad68(e, 0xe00000, 1);
    birds = new HatoBird[count];
    for (int i = 0; i < count; i++) {
        HatoBird *b = &birds[i];
        int id = *f_0dad68(e, 0xe0, 0);
        memset(&b->anim, 0, sizeof b->anim);
        f_0daf30(&b->anim, f_0d8114(D_23c820.Classes(), id));
        b->rate = rate;
        b->range = range;
        b->Scatter();
    }
    cam = -1;
}

/* @implements 0x0d4d64 us _ZN3Map5Event9CHatoWork4Stop
   WHAT IT DOES: Frees the birds. */
void CHatoWork::Stop()
{
    if (birds)
        delete[] birds;
}

/* @implements 0x0d4e04 us _ZN3Map5Event9CUshiWork5Setup
   WHAT IT DOES: Takes the event and its period (32 unless the event gives one) and frame
   count, and resets the animation. */
void CUshiWork::Setup(::Event *e)
{
    ev = e;
    if (e->flags & 8)
        period = *f_0dad68(e, 0x700, 0);
    else
        period = 32;
    int n = *f_0dad68(e, 0x40000, 0);
    cam = -9999;
    m36 = 0;
    count = n;
    time = 0;
    state = 0;
    length = n * period * 60;
}

/* @implements 0x0d4eb0 us _ZN3Map5Event9CUshiWork4Stop
   WHAT IT DOES: Nothing to stop. */
void CUshiWork::Stop()
{
}

/* @implements 0x0d4eb8 us _ZN3Map5Event9CUshiWork6Update
   WHAT IT DOES: Runs the animation forwards to its end (state 1) or backwards to 80% of it
   (state 2), then holds (state 3) until the camera cuts, which returns it to rest. */
void CUshiWork::Update()
{
    switch (state) {
    case 0:
        break;
    case 1:
        time += 1024;
        if (time >= length) {
            state = 3;
            time = length - 1;
            frame = length - 1;
        }
        break;
    case 2:
        time -= 1024;
        if (time < length * 8 / 10) {
            state = 3;
            frame = time;
        }
        break;
    case 3:
        if (cam == -9999)
            cam = *(int *)((char *)D_2542a0 + 572);
        if (cam != *(int *)((char *)D_2542a0 + 572))
            state = 0;
        cam = *(int *)((char *)D_2542a0 + 572);
        break;
    }
}

/* @implements 0x0d4f9c us _ZN3Map5Event9CUshiWork5Reset
   WHAT IT DOES: Back to rest. */
void CUshiWork::Reset()
{
    cam = -9999;
    time = 0;
    m36 = 0;
    state = 0;
}

/* @implements 0x0d4fb4 us _ZN3Map5Event9CWorkListINS0_8CMotWorkEE5Build
   WHAT IT DOES: CWorkList<CMotWork>::Build (defined in the class above), emitted out of line.
   With -fexceptions, mark_used instantiates a template called before the caller is known to
   throw (the first call of f_0d2ef0) at once, and that instance meets the inliner's size limit
   with its real statement count; the later instances are instantiated by the inliner itself
   and inlined. */

}
}


typedef float (*EvalFn)(EventWork *);
typedef int (*RunFn)(EventWork *, int);
typedef void (*ReleaseFn)(EventWork *);
typedef int (*FlagFn)();

#define BASE CEventHandler
#define ROW4(f) &CEvent00::f, &CEvent01::f, &CEvent02::f, &CEvent03::f, &CEvent04::f, &CEvent05::f, &CEvent06::f, \
    &BASE::f, &BASE::f, &BASE::f, &BASE::f, &BASE::f, &CEvent12::f, &BASE::f, &BASE::f, &BASE::f,                 \
    &CEvent16::f, &CEvent17::f, &CEvent18::f, &CEvent19::f, &CEvent20::f, &CEvent21::f, &BASE::f, &CEvent23::f,   \
    &CEvent24::f, &BASE::f, &BASE::f, &BASE::f, &BASE::f, &BASE::f, &BASE::f, &BASE::f,                           \
    &CEvent32::f, &CEvent33::f, &CEvent34::f, &BASE::f

/* The handler tables, indexed by event type. */
EvalFn D_1d4a5c[36] = { ROW4(Eval) };
RunFn D_1d4aec[36] = { ROW4(Run) };
ReleaseFn D_1d4b7c[36] = { ROW4(Release) };
FlagFn D_1d4c0c[36] = { ROW4(Flag) };

/* @implements 0x0d5430 us _ZN8CEvent004Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5438 us _ZN8CEvent014Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5440 us _ZN8CEvent024Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5448 us _ZN8CEvent034Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5450 us _ZN8CEvent044Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5458 us _ZN8CEvent054Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5460 us _ZN8CEvent064Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5468 us _ZN8CEvent124Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5470 us _ZN8CEvent164Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5478 us _ZN8CEvent174Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5480 us _ZN8CEvent184Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5488 us _ZN8CEvent194Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5490 us _ZN8CEvent214Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d5498 us _ZN8CEvent234Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d54a0 us _ZN8CEvent244Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d54a8 us _ZN8CEvent324Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d54b0 us _ZN8CEvent334Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d54b8 us _ZN8CEvent344Flag
   WHAT IT DOES: Answers 1. */
/* @implements 0x0d54c0 us _ZN13CEventHandler4Flag
   WHAT IT DOES: Default: answers 1. */
