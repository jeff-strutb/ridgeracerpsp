/* The course event jobs (retail 0x0cfaf4 to 0x0d54c8): the things placed along a course that
   come alive as the camera nears them. Every event has a type (0 to 35); each type is a class
   with four static handlers reached through four tables indexed by type: Eval scores how
   urgently the event wants to run (-1: not at all), Run runs it for a frame, Release lets go
   of what it holds, and Flag answers 1. Types without handlers of their own use the base
   class's. The object file ends with the job work list the handlers run under. */

extern "C" {
int f_126f1c(const char *fmt, ...);
}

/* A course event as loaded from the event file. */
struct Event {
    short type;
    short m2;
    int flags;
    int m8;
    int m12;
    float x, y, z;
    int obj;
};

/* The work record of a running event job. */
struct EventWork {
    int m0;
    Event *ev;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
};

class CEventJobWorkBase {
public:
    static float Eval(EventWork *w);
    static int Run(EventWork *w, int arg);
    static void Release(EventWork *w);
    static int Flag() { return 1; }
};

#define EVENT_TYPE(N)                               \
    class CEvent##N : public CEventJobWorkBase {    \
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
class CEvent20 : public CEventJobWorkBase {
public:
    static float Eval(EventWork *w);
    static int Run(EventWork *w, int arg);
    static void Release(EventWork *w);
};

/* @implements 0x0cff30 us _ZN8CEvent007Release
   WHAT IT DOES: Nothing to release. */
void CEvent00::Release(EventWork *w)
{
}

/* @implements 0x0d01c0 us _ZN8CEvent017Release
   WHAT IT DOES: Nothing to release. */
void CEvent01::Release(EventWork *w)
{
}

/* @implements 0x0d0524 us _ZN8CEvent207Release
   WHAT IT DOES: Nothing to release. */
void CEvent20::Release(EventWork *w)
{
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

/* @implements 0x0d1730 us _ZN8CEvent247Release
   WHAT IT DOES: Nothing to release. */
void CEvent24::Release(EventWork *w)
{
}

/* @implements 0x0d1c98 us _ZN8CEvent237Release
   WHAT IT DOES: Nothing to release. */
void CEvent23::Release(EventWork *w)
{
}

/* @implements 0x0d20ec us _ZN8CEvent324Eval
   WHAT IT DOES: Always scores 2000. */
float CEvent32::Eval(EventWork *w)
{
    return 2000.0f;
}

/* @implements 0x0d2184 us _ZN8CEvent327Release
   WHAT IT DOES: Nothing to release. */
void CEvent32::Release(EventWork *w)
{
}

/* @implements 0x0d2b74 us _ZN8CEvent197Release
   WHAT IT DOES: Nothing to release. */
void CEvent19::Release(EventWork *w)
{
}

/* @implements 0x0d2ecc us _ZN8CEvent347Release
   WHAT IT DOES: Nothing to release. */
void CEvent34::Release(EventWork *w)
{
}

/* @implements 0x0d2ed4 us _ZN17CEventJobWorkBase4Eval
   WHAT IT DOES: Default: never asks to run. */
float CEventJobWorkBase::Eval(EventWork *w)
{
    return -1.0f;
}

/* @implements 0x0d2ee0 us _ZN17CEventJobWorkBase3Run
   WHAT IT DOES: Default: does nothing; passes the argument back. */
int CEventJobWorkBase::Run(EventWork *w, int arg)
{
    return arg;
}

/* @implements 0x0d2ee8 us _ZN17CEventJobWorkBase7Release
   WHAT IT DOES: Default: nothing to release. */
void CEventJobWorkBase::Release(EventWork *w)
{
}

typedef float (*EvalFn)(EventWork *);
typedef int (*RunFn)(EventWork *, int);
typedef void (*ReleaseFn)(EventWork *);
typedef int (*FlagFn)();

#define BASE CEventJobWorkBase
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
/* @implements 0x0d54c0 us _ZN17CEventJobWorkBase4Flag
   WHAT IT DOES: Default: answers 1. */
