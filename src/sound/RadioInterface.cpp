/* The radio DJ interface object file (retail 0x093fb8 to 0x094488, Radio::CInterface). It owns
   the DJ's stream player (one global object), the course drive data reader and the voice
   condition table, and passes the race's events to them: setting up a course, starting and
   stopping, and asking the DJ to say something for a condition. */

extern "C" {
unsigned int sceKernelGetSystemTimeLow(void);
}

void f_093f90(const char *fmt, ...);

namespace Radio {

/* The DJ's stream player (its own object file). */
class CPlayer {
public:
    CPlayer();
    ~CPlayer();
    int m0;
    int m4[3];
};

/* The DJ's voice condition table (its own object file). */
class CTable {
public:
    CTable();
    int m0;
    int m4;
    int m8;
    int m12[3];
};

}

using Radio::CPlayer;
using Radio::CTable;

/* The course drive data reader (RadioDrive.cpp). */
class RadioDrive {
public:
    RadioDrive();
    ~RadioDrive();
    int f_09384c(void *data);
    void f_0938a4();
    int f_0938ac(const char *course);
    void f_093b74();
    int m0[19];
};

extern "C" {
void f_0f6ea4(CPlayer *p, void *data);
void f_0f6bc0(unsigned int seed);
int f_0f703c(CPlayer *p);
int f_0f6f60(CPlayer *p);
void f_0f6f7c(CPlayer *p);
int f_0f7620(CPlayer *p);
void f_0f6fd4(CPlayer *p);
int f_0f6ff0(CPlayer *p);
int f_0f7018(CPlayer *p);
int f_0f7834(CPlayer *p, int set);
int f_0f7208(CPlayer *p, int voice, int cond, int a, int b);
void f_0f9a08(CTable *t);
int f_0f9a28(CTable *t);
int f_0f9ad4(CTable *t);
int f_0f9a8c(CTable *t);
int f_0f9acc(CTable *t);
int f_0f9b30(CTable *t);
}

extern CPlayer *D_27f09c;

namespace Radio {

class CInterface {
public:
    CInterface();
    ~CInterface() {}
    void Clear()
    {
        m8 = 0;
        m0 = 0;
        m4 = 0;
        m5 = 0;
    }
    void f_093fe0(void *stream, void *drive);
    void f_0940e8();
    void f_09411c();
    void f_0941c8(const char *course);
    void f_094214();
    int f_094254();
    void f_094290();
    void f_0942b4();
    void f_0942f0();
    void f_094310();
    int f_094330();
    int f_094344();
    int f_094360();
    int f_09437c();
    int f_094398();
    int f_0943b4();
    int f_0943d0(short cond);

    CTable *m0;
    bool m4;   /* a condition is pending */
    bool m5;   /* stopped before the start */
    RadioDrive *m8;
};

/* @implements 0x093fb8 us _ZN5Radio10CInterfaceC2Ev
   WHAT IT DOES: Makes an interface with nothing created (base object constructor). */
/* @implements 0x093fcc us _ZN5Radio10CInterfaceC1Ev
   WHAT IT DOES: Makes an interface with nothing created (complete object constructor). */
CInterface::CInterface()
{
    m8 = 0;
    m0 = 0;
    m4 = 0;
    m5 = 0;
}

/* @implements 0x093fe0 us f_093fe0
   WHAT IT DOES: Creates the stream player, the drive data reader and the condition table,
   gives them their data, and seeds the DJ's random choices from the system clock. */
void CInterface::f_093fe0(void *stream, void *drive)
{
    D_27f09c = new CPlayer;
    m8 = new RadioDrive;
    m0 = new CTable;
    f_0f6ea4(D_27f09c, stream);
    m8->f_09384c(drive);
    f_0f9a08(m0);
    m4 = 0;
    m5 = 0;
    f_0f6bc0(sceKernelGetSystemTimeLow());
    f_093f90("Radio CInterface: Random Seed:%d\n", sceKernelGetSystemTimeLow());
}

/* @implements 0x0940e8 us f_0940e8
   WHAT IT DOES: Shuts the player down and lets the drive data reader go. */
void CInterface::f_0940e8()
{
    f_0f703c(D_27f09c);
    m8->f_0938a4();
}

/* @implements 0x09411c us f_09411c
   WHAT IT DOES: Deletes the drive data reader, the stream player and the condition table and
   clears the interface. */
void CInterface::f_09411c()
{
    delete m8;
    delete D_27f09c;
    if (m0)
        delete m0;
    D_27f09c = 0;
    Clear();
}

/* @implements 0x0941c8 us f_0941c8
   WHAT IT DOES: Sets up the player and the drive data for a course. */
void CInterface::f_0941c8(const char *course)
{
    f_0f6f60(D_27f09c);
    m8->f_0938ac(course);
    m4 = 0;
    m5 = 0;
}

/* @implements 0x094214 us f_094214
   WHAT IT DOES: Resets the player and the drive data. */
void CInterface::f_094214()
{
    f_0f6f7c(D_27f09c);
    m8->f_093b74();
    m4 = 0;
    m5 = 0;
}

/* @implements 0x094254 us f_094254
   WHAT IT DOES: Whether a condition is pending and the player is in state 1. */
int CInterface::f_094254()
{
    int r = 0;
    if (m4)
        r = f_0f7620(D_27f09c) == 1;
    return r;
}

/* @implements 0x094290 us f_094290
   WHAT IT DOES: Stops the player. */
void CInterface::f_094290()
{
    f_0f6fd4(D_27f09c);
}

/* @implements 0x0942b4 us f_0942b4
   WHAT IT DOES: Stops the player before the race starts and remembers that. */
void CInterface::f_0942b4()
{
    f_093f90("Radio CInterface: StopBeforeStart\n");
    m5 = 1;
    f_094290();
}

/* @implements 0x0942f0 us f_0942f0
   WHAT IT DOES: Forwards to the player (0x0f6ff0). */
void CInterface::f_0942f0()
{
    f_0f6ff0(D_27f09c);
}

/* @implements 0x094310 us f_094310
   WHAT IT DOES: Forwards to the player (0x0f7018). */
void CInterface::f_094310()
{
    f_0f7018(D_27f09c);
}

/* @implements 0x094330 us f_094330
   WHAT IT DOES: Whether the player is busy. */
int CInterface::f_094330()
{
    return D_27f09c->m0 != 0;
}

/* @implements 0x094344 us f_094344
   WHAT IT DOES: Forwards to the condition table (0x0f9a28). */
int CInterface::f_094344()
{
    return f_0f9a28(m0);
}

/* @implements 0x094360 us f_094360
   WHAT IT DOES: Forwards to the condition table (0x0f9ad4). */
int CInterface::f_094360()
{
    return f_0f9ad4(m0);
}

/* @implements 0x09437c us f_09437c
   WHAT IT DOES: Forwards to the condition table (0x0f9a8c). */
int CInterface::f_09437c()
{
    return f_0f9a8c(m0);
}

/* @implements 0x094398 us f_094398
   WHAT IT DOES: Forwards to the condition table (0x0f9acc). */
int CInterface::f_094398()
{
    return f_0f9acc(m0);
}

/* @implements 0x0943b4 us f_0943b4
   WHAT IT DOES: Forwards to the condition table (0x0f9b30). */
int CInterface::f_0943b4()
{
    return f_0f9b30(m0);
}

/* @implements 0x0943d0 us f_0943d0
   WHAT IT DOES: Asks the DJ to talk about a condition. Conditions 50 to 62 and 78 mark a
   condition pending. Condition 0 is dropped once the player was stopped before the start.
   Returns 0, or -1 when the player refused. */
int CInterface::f_0943d0(short cond)
{
    int c = cond;
    int set;
    if (c >= 50) {
        if (c < 63)
            m4 = 1;
        else if (c == 78)
            m4 = 1;
    }
    if (c == 0) {
        if (m5) {
            f_093f90("Radio CInterface: SetCondition: Condition[%d] is Canceled\n", 0);
            return -1;
        }
        set = m0->m8;
    } else {
        set = m0->m4;
    }
    int v = f_0f7834(D_27f09c, set);
    if (f_0f7208(D_27f09c, (unsigned short)v, c, 0, -1) < 0)
        return -1;
    return 0;
}

}

/* The DJ interface the race uses. */
Radio::CInterface D_242c90;

/* @implements 0x094488 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global DJ interface at startup (its destructor does nothing). */
/* @implements 0x0944cc us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x0944ec us _GLOBAL__D_
   WHAT IT DOES: Shutdown entry of the object file's static data. */
