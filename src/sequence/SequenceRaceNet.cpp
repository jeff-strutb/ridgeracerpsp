/* The wireless race sequence object file (retail 0x0414b4 to 0x041a74,
   "RacePSP::CSequenceRaceNet"). The sequence that runs one race of a wireless battle: it sets
   up the chosen course, the cars and the race objects from the battle's settings, runs the race
   states and tears the race objects down at its end. */

extern "C" {
void f_0eae7c(void);
void f_031d4c(void *);
void f_094214(void *);
void f_01d934(void *);
void f_08d7f0(void *);
void f_07e6d0(void *);
void f_03b400(void *);
}
extern char D_2402e0[];
extern char D_242c90[];
extern char D_23be80[];

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};

/* The sound system. */
class CSound {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int a, int b);
    virtual void v3(int a);
    virtual void v4();
    virtual void v5();
};
extern CSound *D_1d3d40;

namespace RacePSP {
class CSequenceBase;
typedef int (CSequenceBase::*Handler)();

/* The base of every sequence (made by its own object file). */
class CSequenceBase {
public:
    CSequenceBase();
    virtual ~CSequenceBase();
    virtual void f_038fd4(int arg);
    virtual int f_038fdc();
    virtual void f_038fe4();
    int f_03959c();
    int f_039588();
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    void *m32;
    void *m36;
    void *m40;
    int m44;
    int m48;
    int m52;
    int state;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
};

class CSequenceStandard : public CSequenceBase {
public:
    CSequenceStandard() {}
    virtual ~CSequenceStandard() {}
};

class CSequenceRaceNet : public CSequenceStandard {
public:
    CSequenceRaceNet();
    virtual ~CSequenceRaceNet();
    virtual void f_038fd4(int arg);
    virtual int f_038fdc();
    virtual void f_038fe4();
};
}

using namespace RacePSP;

/* An object with a virtual interface (the race object at +40). */
class CObj {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

extern Handler D_1d1c7c[];

/* @implements 0x0414b4 us _ZN7RacePSP16CSequenceRaceNetC2Ev
   WHAT IT DOES: builds the sequence on its base. */
CSequenceRaceNet::CSequenceRaceNet()
{
}

/* @implements 0x0414e4 us _ZN7RacePSP16CSequenceRaceNetC1Ev
   WHAT IT DOES: the complete-object copy of the constructor above. */

/* @implements 0x041514 us _ZN7RacePSP16CSequenceRaceNetD2Ev
   WHAT IT DOES: tears the sequence down through its base. */
CSequenceRaceNet::~CSequenceRaceNet()
{
}

/* @implements 0x04153c us _ZN7RacePSP16CSequenceRaceNetD1Ev
   WHAT IT DOES: the complete-object copy of the destructor above. */

/* @implements 0x041564 us _ZN7RacePSP16CSequenceRaceNetD0Ev
   WHAT IT DOES: the deleting destructor. */

/* @implements 0x041954 us CSequenceRaceNet8f_038fdc
   WHAT IT DOES: returns to the idle state once the base reports the end, then runs the handler
   of the current state. */
int CSequenceRaceNet::f_038fdc()
{
    if (f_03959c())
        state = 0;
    return (this->*D_1d1c7c[state])();
}

/* @implements 0x0419e0 us CSequenceRaceNet8f_038fe4
   WHAT IT DOES: ends the race: releases the race objects, the course, the music, the sound and
   the cars, then runs the base's end. */
void CSequenceRaceNet::f_038fe4()
{
    f_0eae7c();
    f_031d4c(D_2402e0);
    f_094214(D_242c90);
    f_01d934(D_23be80);
    f_08d7f0((void *)m48);
    D_1d3d40->v3(0);
    ((CObj *)m40)->v4();
    f_07e6d0((void *)m52);
    f_03b400(m32);
    CSequenceBase::f_038fe4();
}
