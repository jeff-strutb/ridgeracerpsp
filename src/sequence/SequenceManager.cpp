/* The game's sequence manager (retail 0x00322c to 0x00600c): the single object that runs the
   current game mode (title, menus, races, demo and the test modes) as a state machine of
   member-function handlers, and owns the pools of scene players, sub-players and timers that
   each mode starts and stops in groups ("slots"). Also the small helpers that name the menu
   scene to show for each sequence number. */

#include <stdio.h>
#include <string.h>

extern "C" {
void f_0023d4(const char *name);
void f_002380(int a, int b);
void f_002410(void);
int f_002574(void);
void f_002304(void);
void f_002550(int i, int *kind, int *id);
int f_002184(const char *name, int idx);
void f_001ff4(int);
void f_001c1c(void *);
void f_001c24(void *);
void f_001e2c(void *);
void f_00204c(void);
const char *f_01c26c(const char *name);
char *f_036b6c(void *db, const char *key, int id, int sub);
void *f_0368e8(void *db, const char *key, int id, int a, int b);
void f_036f84(void);
void f_03702c(void);
void f_036cb8(void);
void f_036dec(void);
void f_037108(void);
void f_037448(void);
void f_03749c(void);
void f_0374f0(void);
void f_031e8c(void);
void f_037568(void);
void f_040c90(void);
void f_01cd54(void *);
void f_01cdf4(void *);
void f_01ca80(void *);
void f_01cec4(void *);
int f_01d174(void *);
void f_01d994(void *);
void f_094344(void *);
void f_09437c(void *);
int f_094398(void *);
void f_094360(void *);
void f_0970e4(void *);
void f_097100(void *);
int f_09711c(void *);
void f_097124(void *);
void f_092398(void *);
void f_092488(void *);
void f_0924a4(void *);
void f_018b10(void *);
void f_099710(void);
void f_021bbc(void);
void f_021720(void);
void f_0221e8(int);
void f_021750(void);
}

/* A value pair kept per game parameter; only the first word is ever set when clearing. */
struct Param {
    int a;
    int b;
    Param() {}
    Param(int v) : a(v) {}
};

/* A scene player (280 bytes): idx names its entry in the scene table, -1 when unused. */
struct Elem280 {
    int idx;
    char m4[276];
    Elem280() { idx = -1; }
    ~Elem280() { f_0026cc(); }
    void f_0026cc();
    void f_00260c(int id, struct Elem24 *t, int a, int b);
    void f_002734(unsigned char flag);
    int f_002acc(const char *name);
};

/* A sub-player (28 bytes): idx names its entry in the second table, -1 when unused. */
struct Elem28 {
    int idx;
    char m4[24];
    Elem28() { idx = -1; }
    ~Elem28() { f_002be8(); }
    void f_002be8();
    void f_002b34(int kind, int id, struct Elem24 *t);
    void f_002c50(unsigned char flag);
    int f_002e5c();
};

/* A timer (24 bytes). */
struct Elem24 {
    int m0;
    int m4;
    char m8[16];
    Elem24() { m4 = 0; }
    ~Elem24() {}
    void f_0995e0(int length, int start);
    void f_099640();
    Param f_0996b0(int);
    int f_099684(int t, int b);
    void f_0996dc(Param p);
};

/* A group of players started together: the timer it runs on, and the player index ranges. */
struct Slot {
    int timer;
    int b;
    int first;
    int last;
    int subFirst;
    int subLast;
    Param saved;
};

struct SceneEntry {
    const char *name;
    char m4[32];
};

struct SubEntry {
    const char *name;
    char m4[20];
};

extern SceneEntry D_1b8c04[];
extern SubEntry D_1c0614[];

class CSequence;
typedef void (CSequence::*Handler)();

class CSequence {
public:
    unsigned char m0;
    int m4;
    int m8;
    int m12;
    int m16;
    unsigned char m20;
    Param m24[15];
    int m144;
    int m148;
    int m152;
    Param m156[15];
    Param m276;
    int m284;
    char m288[44];
    int m332;
    int m336;
    unsigned char m340;
    int m344;
    Elem280 *m348[80];
    Elem280 m668[80];
    Elem28 m23068[40];
    Elem24 m24188[16];
    Slot m24572[14];
    Handler m25020;
    Handler m25028;

    CSequence() : m20(0), m344(0)
    {
        m25020 = 0;
        m25028 = 0;
        f_0057d0();
    }
    int f_0031b8();
    Param f_0031dc(int i);
    void f_003150(int i, Param p);

    void f_00391c();
    void f_0039c4();
    void f_0039fc();
    void f_003af4();
    void f_003b70();
    void f_003c10();
    void f_003c58();
    void f_003d30();
    void f_003db4();
    void f_003dfc();
    void f_003eb0();
    void f_003f80();
    void f_003fd0();
    void f_004010();
    void f_0040b8();
    void f_0040f0();
    void f_004160();
    void f_004198();
    void f_0043c8();
    void f_004410();
    void f_004484();
    void f_004630();
    void f_004678();
    void f_0046ec();
    void f_004770();
    void f_0047a8();
    void f_00482c();
    void f_004864();
    void f_00493c();
    void f_004958();
    void f_0049e0();
    void f_004a28();
    void f_004ab0();
    void f_004af8();
    void f_004b80();
    void f_004bc8();
    void f_004cf0();
    void f_004d88();
    void f_004df8();
    void f_004ea0();
    void f_004efc();
    void f_005000();
    void f_005044();
    void f_0050ec();
    void f_005170();
    void f_0051a8();
    void f_00522c();
    void f_005264();
    void f_0052e8();
    void f_005320(Slot *s);
    void f_005470(Slot *s);
    void f_005554(unsigned char wait);
    void f_0056c4();
    int f_0056d0();
    void f_005720();
    void f_00578c();
    void f_0057d0();
    void f_0058b4();
    void f_005910();
    void f_0059f4();
    void f_005a1c(Elem280 *e);
    Elem280 *f_005a38(const char *name);
    Elem28 *f_005b8c(const char *name);
    int f_005c34(const char *name);
    void f_005d4c(const char *name);
    void f_005d68(int a, int b);
};

struct Loader {
    char m0[52];
    struct Queue {
        char m0[12288];
        int head;
        int tail;
        bool Empty() { return tail == head; }
    } queue;
    unsigned char m12348;
};

struct Queue2 {
    char m0[2048];
    int head;
    int tail;
    bool Empty() { return tail == head; }
};

extern Loader D_1da468;
extern Queue2 D_1d9c5c;
extern char D_23be80[];
extern char D_242c90[];
extern char D_242c4c[];
extern void *D_242dec;
extern char D_2301b0[];
extern char D_240740[];
extern char D_240768[];
extern char D_2407d0[];
extern unsigned char D_24063c[];
extern const int D_1a2120;

CSequence D_1dd6b0;
char D_1e387c[64];
char D_1e38bc[32];
int D_1e38dc;
int D_1e38e0;
int D_1e38e4;
int D_1e38e8;
int D_1e38ec;
int D_1e38f0;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* @implements 0x00322c us f_00322c
   WHAT IT DOES: Shows the menu scene that belongs to the current sequence number (loading,
   start, main, result and pause menus, their wireless variants and the test menus), in the
   console's language. */
void f_00322c()
{
    switch (D_1dd6b0.f_0031b8()) {
    case 17:
        D_1dd6b0.f_005d4c(f_01c26c("TestMainMenu"));
        break;
    case 9:
        D_1dd6b0.f_005d4c(f_01c26c("Loading"));
        break;
    case 10:
        D_1dd6b0.f_005d4c(f_01c26c("StartMenu"));
        break;
    case 12:
        D_1dd6b0.f_005d4c(f_01c26c("MainMenu"));
        break;
    case 13:
        D_1dd6b0.f_005d4c(f_01c26c("ResultMenu"));
        break;
    case 14:
        D_1dd6b0.f_005d4c(f_01c26c("PauseMenu"));
        break;
    case 15:
        D_1dd6b0.f_005d4c(f_01c26c("WirelessResultMenu"));
        break;
    case 16:
        D_1dd6b0.f_005d4c(f_01c26c("WirelessPauseMenu"));
        break;
    case 18:
        D_1dd6b0.f_005d4c(f_01c26c("TestResultMenu"));
        break;
    case 19:
        D_1dd6b0.f_005d4c(f_01c26c("TestPauseMenu"));
        break;
    }
}

/* @implements 0x003308 us f_003308
   WHAT IT DOES: In the test sequences (20 to 24), shows the scene shared by all test modes. */
void f_003308()
{
    if ((unsigned)(D_1dd6b0.f_0031b8() - 20) < 5)
        D_1dd6b0.f_005d4c("TestCommon");
}

/* @implements 0x00335c us f_00335c
   WHAT IT DOES: In the test sequences, shows the scene of the chosen test mode: title, main
   menu, ridge, single race or time attack. */
void f_00335c()
{
    switch (D_1dd6b0.f_0031b8()) {
    case 20:
        D_1dd6b0.f_005d4c("TestTitle");
        break;
    case 21:
        D_1dd6b0.f_005d4c("TestMainMenu2");
        break;
    case 22:
        D_1dd6b0.f_005d4c("TestRidge");
        break;
    case 23:
        D_1dd6b0.f_005d4c("TestSingle");
        break;
    case 24:
        D_1dd6b0.f_005d4c("TestTA");
        break;
    }
}

/* @draft 0x003404 us f_003404
   WHAT IT DOES: Prepares the race scenes for the chosen car: looks up the car's course block
   and shows "Course<block>", copies the car's class record, and shows the engine sound scene
   for a plane-type car or for a truck-type car. */
void f_003404()
{
    strcpy(D_240768, f_036b6c(D_240740, "CarGetBlock", D_1dd6b0.f_0031dc(0).a, -1));
    sprintf(D_1e387c, "Course%s", D_240768);
    D_1dd6b0.f_005d4c(D_1e387c);
    memcpy(D_24063c, f_0368e8(D_240740, "Class", D_1dd6b0.f_0031dc(0).a, 0, 0), D_1a2120);
    if (D_24063c[0] == 7)
        D_1dd6b0.f_005d4c("SoundCarGetPlane");
    else
        D_1dd6b0.f_005d4c("SoundCarGetTruck");
}

/* @implements 0x00352c us f_00352c
   WHAT IT DOES: Starts the two effect sets used by the race result screen. */
void f_00352c()
{
    f_036f84();
    f_03702c();
}

/* @implements 0x003550 us f_003550
   WHAT IT DOES: Starts one effect set. */
void f_003550()
{
    f_036cb8();
}

/* @implements 0x00356c us f_00356c
   WHAT IT DOES: Starts one effect set. */
void f_00356c()
{
    f_036dec();
}

/* @implements 0x003588 us f_003588
   WHAT IT DOES: Starts one effect set. */
void f_003588()
{
    f_037108();
}

/* @implements 0x0035a4 us f_0035a4
   WHAT IT DOES: Nothing (an empty hook of the race sequence). */
void f_0035a4()
{
}

/* @implements 0x0035ac us f_0035ac
   WHAT IT DOES: Starts the race: the race world, the race controller and the race object. */
void f_0035ac()
{
    f_01cd54(D_23be80);
    f_094344(D_242c90);
    f_0970e4(D_242dec);
}

/* @implements 0x0035e4 us f_0035e4
   WHAT IT DOES: Tells the race world to prepare its next stage. */
void f_0035e4()
{
    f_01cdf4(D_23be80);
}

/* @implements 0x003604 us f_003604
   WHAT IT DOES: Frees the common effects and shows the scene that releases them. */
void f_003604()
{
    f_037448();
    D_1dd6b0.f_005d4c("EffectCommon_Free");
}

/* @implements 0x003634 us f_003634
   WHAT IT DOES: Starts one effect set. */
void f_003634()
{
    f_03749c();
}

/* @implements 0x003650 us f_003650
   WHAT IT DOES: Starts one effect set and its companion. */
void f_003650()
{
    f_0374f0();
    f_031e8c();
}

/* @implements 0x003674 us f_003674
   WHAT IT DOES: Starts one effect set. */
void f_003674()
{
    f_037568();
}

/* @draft 0x003690 us f_003690
   WHAT IT DOES: Nothing (an empty hook of the race sequence). */
void f_003690()
{
}

/* @draft 0x003698 us f_003698
   WHAT IT DOES: Nothing (an empty hook). The function map merges it into f_003690. */
void f_003698()
{
}

/* @draft 0x0036a0 us f_0036a0
   WHAT IT DOES: Copies the record for the current sequence number and shows the pause menu,
   the wireless pause menu when the record says the race is wireless. */
void f_0036a0()
{
    Param p = D_1dd6b0.m276;
    memcpy(D_24063c, f_0368e8(D_2407d0, "SequenceNumber", p.a, 0, 0), D_1a2120);
    D_1dd6b0.f_005d4c(f_01c26c(D_24063c[0] == 3 ? "WirelessPauseMenu" : "PauseMenu"));
}

/* @implements 0x003744 us f_003744
   WHAT IT DOES: Starts the title screen's scene. */
void f_003744()
{
    f_040c90();
}

/* @implements 0x003760 us f_003760
   WHAT IT DOES: Shows the scene of the demo whose number the manager holds ("Demo<n>"). */
void f_003760()
{
    sprintf(D_1e38bc, "Demo%d", D_1dd6b0.m284);
    D_1dd6b0.f_005d4c(D_1e38bc);
}

/* @implements 0x0037b4 us f_0037b4
   WHAT IT DOES: Nothing (an empty hook). */
void f_0037b4()
{
}

/* @implements 0x0037bc us f_0037bc
   WHAT IT DOES: Returns the length in frames of the scenes just requested. */
int f_0037bc()
{
    f_002410();
    int r = f_002574();
    f_002304();
    return r;
}

/* @implements 0x0037f0 us f_0037f0
   WHAT IT DOES: Returns a fixed length for the single race intro timer. */
int f_0037f0()
{
    return 0x220000;
}

/* @implements 0x0037f8 us f_0037f8
   WHAT IT DOES: Returns a fixed length for the time attack intro timer. */
int f_0037f8()
{
    return 0x80000;
}

/* @implements 0x003800 us f_003800
   WHAT IT DOES: Starts an effect set and returns the length of its scenes (never negative). */
int f_003800()
{
    int len = 0;
    f_00356c();
    int r = f_0037bc();
    len = MAX(r, len);
    return len;
}

/* @implements 0x003830 us f_003830
   WHAT IT DOES: Starts the race and returns the length of its scenes (never negative). */
int f_003830()
{
    int len = 0;
    f_0035ac();
    int r = f_0037bc();
    len = MAX(r, len);
    return len;
}

/* @implements 0x003860 us f_003860
   WHAT IT DOES: Prepares the next race stage and returns the length of its scenes. */
int f_003860()
{
    int len = 0;
    f_0035e4();
    int r = f_0037bc();
    len = MAX(r, len);
    return len;
}

/* @implements 0x003890 us f_003890
   WHAT IT DOES: Frees the common effects, starts an effect set and returns the length of
   their scenes (never negative). */
int f_003890()
{
    int len = 0;
    f_003604();
    f_003550();
    int r = f_0037bc();
    len = MAX(r, len);
    return len;
}

/* @implements 0x0038c8 us f_0038c8
   WHAT IT DOES: Starts an effect set and returns the length of its scenes (never negative). */
int f_0038c8()
{
    int len = 0;
    f_003634();
    int r = f_0037bc();
    len = MAX(r, len);
    return len;
}

/* @implements 0x0038f8 us f_0038f8
   WHAT IT DOES: Shows the pause menu for the current sequence and returns its length. */
int f_0038f8()
{
    f_0036a0();
    return f_0037bc();
}

/* @implements 0x00391c us f_00391c
   WHAT IT DOES: Enters a menu sequence: resets everything, starts the menu scene of the
   sequence number on the main timer and runs its players, then waits in f_0039c4 to leave. */
void CSequence::f_00391c()
{
    f_0057d0();
    f_00322c();
    m24188[0].f_0995e0(f_0037bc() + m332, 0);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_00322c();
    f_005320(&m24572[1]);
    m336 = m24188[0].f_099684(m332, 0);
    m25020 = 0;
    m25028 = &CSequence::f_0039c4;
}

/* @implements 0x0039c4 us f_0039c4
   WHAT IT DOES: Leaves a menu sequence: stops its players and the main timer. */
void CSequence::f_0039c4()
{
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x0039fc us f_0039fc
   WHAT IT DOES: Enters the start menu: shows the main menu and then the start menu scenes,
   times them, and runs the start menu's players. */
void CSequence::f_0039fc()
{
    f_0057d0();
    f_092398(D_242c4c);
    int a = f_0037bc();
    D_1dd6b0.f_005d4c(f_01c26c("MainMenu"));
    int b = f_0037bc();
    m24188[0].f_0995e0(MAX(a, b), 0);
    D_1dd6b0.f_005d4c(f_01c26c("StartMenu"));
    m24188[1].f_0995e0(f_0037bc(), 0);
    m24572[0].timer = 1;
    m24572[0].b = 0;
    m24572[0].first = 0;
    m24572[0].subFirst = 0;
    D_1dd6b0.f_005d4c(f_01c26c("StartMenu"));
    f_005320(&m24572[0]);
    m25020 = 0;
}

/* @implements 0x003af4 us f_003af4
   WHAT IT DOES: Enters sequence 11 (from the start menu into the main menu): unless already
   there, opens the menu controller, runs the players on the first timer and waits in
   f_003b70. */
void CSequence::f_003af4()
{
    if (m144 == 11) {
        m25020 = 0;
        return;
    }
    m24572[1].first = 1;
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].subFirst = 0;
    f_092398(D_242c4c);
    f_005320(&m24572[1]);
    m25020 = &CSequence::f_003b70;
}

/* @implements 0x003b70 us f_003b70
   WHAT IT DOES: Switches the running menu to the main menu scene and its players, and waits
   in f_003c10 to leave. */
void CSequence::f_003b70()
{
    f_092488(D_242c4c);
    f_005470(&m24572[1]);
    m24572[1].first = 1;
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].subFirst = 0;
    D_1dd6b0.f_005d4c(f_01c26c("MainMenu"));
    f_005320(&m24572[1]);
    m25020 = 0;
    m25028 = &CSequence::f_003c10;
}

/* @implements 0x003c10 us f_003c10
   WHAT IT DOES: Leaves the main menu: closes the menu controller, stops the players and the
   main timer. */
void CSequence::f_003c10()
{
    f_0924a4(D_242c4c);
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x003c58 us f_003c58
   WHAT IT DOES: Enters the main menu (sequence 12). Coming from sequence 11 it only stops the
   start menu's players and timer. Otherwise it resets, opens the menu controller, times the
   menu scenes and runs the players, then continues in f_003d30. */
void CSequence::f_003c58()
{
    if (m144 == 11) {
        f_005470(&m24572[0]);
        m24188[1].f_099640();
        m25020 = 0;
        return;
    }
    f_0057d0();
    f_092398(D_242c4c);
    int a = f_0037bc();
    f_00322c();
    int b = f_0037bc();
    m24188[0].f_0995e0(MAX(a, b), 0);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_092398(D_242c4c);
    f_005320(&m24572[1]);
    m25020 = &CSequence::f_003d30;
}

/* @implements 0x003d30 us f_003d30
   WHAT IT DOES: Restarts the menu's players once and waits in f_003db4 to leave. */
void CSequence::f_003d30()
{
    f_092488(D_242c4c);
    f_005470(&m24572[1]);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_00322c();
    f_005320(&m24572[1]);
    m25020 = 0;
    m25028 = &CSequence::f_003db4;
}

/* @implements 0x003db4 us f_003db4
   WHAT IT DOES: Leaves the menu: closes the menu controller, stops the players and the main
   timer. */
void CSequence::f_003db4()
{
    f_0924a4(D_242c4c);
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x003dfc us f_003dfc
   WHAT IT DOES: Enters a test sequence (20 to 24). Moving between test sequences only swaps
   the test mode's scene. Otherwise it resets, shows the common test scene on a long timer and
   then switches to the test mode's scene in f_003eb0. */
void CSequence::f_003dfc()
{
    Elem24 *t = &m24188[0];
    if ((unsigned)(m144 - 20) < 5) {
        f_003f80();
        f_003eb0();
        return;
    }
    f_0057d0();
    t->f_0995e0(0x800000, 0);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_003308();
    f_005320(&m24572[1]);
    m336 = t->f_099684(m332, 0);
    m25020 = &CSequence::f_003eb0;
}

/* @implements 0x003eb0 us f_003eb0
   WHAT IT DOES: Shows the scene of the chosen test mode on the second timer, synchronised to
   the main timer, runs its players and waits in f_003fd0 to leave. */
void CSequence::f_003eb0()
{
    m24572[2].timer = 1;
    m24572[2].b = 0;
    Elem24 *t = &m24188[0];
    m24572[2].saved = t->f_0996b0(0);
    f_00335c();
    int len = f_0037bc();
    m24188[1].f_0995e0(len, t->f_099684(len, 0));
    f_00335c();
    m24572[2].first = 8;
    m24572[2].subFirst = 4;
    f_005320(&m24572[2]);
    m25020 = 0;
    m25028 = &CSequence::f_003fd0;
}

/* @implements 0x003f80 us f_003f80
   WHAT IT DOES: Stops the test mode's players and timer and restores the main timer. */
void CSequence::f_003f80()
{
    f_005470(&m24572[2]);
    m24188[1].f_099640();
    m24188[0].f_0996dc(m24572[2].saved);
}

/* @implements 0x003fd0 us f_003fd0
   WHAT IT DOES: Leaves a test sequence: stops the test mode and the common test scene. */
void CSequence::f_003fd0()
{
    f_003f80();
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x004010 us f_004010
   WHAT IT DOES: Enters a menu sequence like f_00391c, leaving through f_0040b8. */
void CSequence::f_004010()
{
    f_0057d0();
    f_00322c();
    m24188[0].f_0995e0(f_0037bc() + m332, 0);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_00322c();
    f_005320(&m24572[1]);
    m336 = m24188[0].f_099684(m332, 0);
    m25020 = 0;
    m25028 = &CSequence::f_0040b8;
}

/* @implements 0x0040b8 us f_0040b8
   WHAT IT DOES: Leaves a menu sequence: stops its players and the main timer. */
void CSequence::f_0040b8()
{
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x0040f0 us f_0040f0
   WHAT IT DOES: Enters sequence 3: shows the menu scene of the sequence on the second timer
   and runs its players. */
void CSequence::f_0040f0()
{
    f_00322c();
    m24188[1].f_0995e0(f_0037bc(), 0);
    m24572[3].timer = 1;
    m24572[3].first = 8;
    m24572[3].subFirst = 4;
    m24572[3].b = 0;
    f_00322c();
    f_005320(&m24572[3]);
    m25020 = 0;
}

/* @implements 0x004160 us f_004160
   WHAT IT DOES: Leaves sequence 3: stops its players and the second timer. */
void CSequence::f_004160()
{
    f_005470(&m24572[3]);
    m24188[1].f_099640();
    m25028 = 0;
}

/* @draft 0x004198 us f_004198
   WHAT IT DOES: Enters the single race (sequence 5). It saves the 14 game parameters and
   clears them; coming from the race setup it stops the old car scenes, from sequence 4 it
   resets. It starts the intro timer and, when a car is chosen, shows the result effects and
   the car's course and sound scenes with that car's parameter in force, then restores the
   parameters and continues in f_0043c8. */
void CSequence::f_004198()
{
    Param saved[14];
    int i;

    for (i = 0; i < 14; i++) {
        saved[i] = f_0031dc(i);
        f_003150(i, Param(0));
    }
    if (m144 == 5) {
        if (m156[0].a) {
            f_005470(&m24572[4]);
            f_005470(&m24572[5]);
        }
    } else {
        if (m144 == 4)
            f_0057d0();
        m24188[2].f_0995e0(f_0037f0(), 0);
    }
    if (saved[0].a) {
        m24572[5].timer = 2;
        m24572[5].first = 24;
        m24572[5].subFirst = 12;
        m24572[5].b = 0;
        f_003150(0, saved[0]);
        f_00352c();
        f_005320(&m24572[5]);
        f_003150(0, Param(0));
    }
    if (saved[0].a) {
        m24572[4].timer = 2;
        m24572[4].first = 48;
        m24572[4].subFirst = 24;
        m24572[4].b = 0;
        f_003150(0, saved[0]);
        f_003404();
        f_005320(&m24572[4]);
        f_003150(0, Param(0));
    }
    for (i = 0; i < 14; i++)
        f_003150(i, saved[i]);
    m25020 = &CSequence::f_0043c8;
}

/* @implements 0x0043c8 us f_0043c8
   WHAT IT DOES: Remembers the parameters the race was entered with and waits in f_004410 to
   leave. */
void CSequence::f_0043c8()
{
    for (int i = 0; i < 14; i++)
        m156[i] = m24[i];
    m25020 = 0;
    m25028 = &CSequence::f_004410;
}

/* @implements 0x004410 us f_004410
   WHAT IT DOES: Leaves the single race: stops the car scenes and the intro timer, forgets the
   remembered parameters and leaves through f_003db4. */
void CSequence::f_004410()
{
    f_005470(&m24572[4]);
    f_005470(&m24572[5]);
    m24188[2].f_099640();
    for (int i = 0; i < 14; i++)
        m156[i] = Param(0);
    m25028 = &CSequence::f_003db4;
}

/* @draft 0x004484 us f_004484
   WHAT IT DOES: Enters the time attack (sequence 4), like f_004198 but with only the result
   effects scenes, and continues in f_004630. */
void CSequence::f_004484()
{
    Param saved[14];
    int i;

    for (i = 0; i < 14; i++) {
        saved[i] = f_0031dc(i);
        f_003150(i, Param(0));
    }
    if (m144 == 4) {
        if (m156[0].a)
            f_005470(&m24572[5]);
    } else {
        if (m144 == 5)
            f_0057d0();
        m24188[2].f_0995e0(f_0037f8(), 0);
    }
    if (saved[0].a) {
        m24572[5].timer = 2;
        m24572[5].first = 24;
        m24572[5].subFirst = 12;
        m24572[5].b = 0;
        f_003150(0, saved[0]);
        f_00352c();
        f_005320(&m24572[5]);
        f_003150(0, Param(0));
    }
    for (i = 0; i < 14; i++)
        f_003150(i, saved[i]);
    m25020 = &CSequence::f_004630;
}

/* @implements 0x004630 us f_004630
   WHAT IT DOES: Remembers the parameters the time attack was entered with and waits in
   f_004678 to leave. */
void CSequence::f_004630()
{
    for (int i = 0; i < 14; i++)
        m156[i] = m24[i];
    m25020 = 0;
    m25028 = &CSequence::f_004678;
}

/* @implements 0x004678 us f_004678
   WHAT IT DOES: Leaves the time attack: stops the scenes and the intro timer, forgets the
   remembered parameters and leaves through f_003db4. */
void CSequence::f_004678()
{
    Elem24 *t = &m24188[2];
    f_005470(&m24572[5]);
    t->f_099640();
    for (int i = 0; i < 14; i++)
        m156[i] = Param(0);
    m25028 = &CSequence::f_003db4;
}

/* @implements 0x0046ec us f_0046ec
   WHAT IT DOES: Enters sequence 6: resets, starts an effect set timed on the main timer and
   runs its players, then waits in f_004770 to leave. */
void CSequence::f_0046ec()
{
    f_0057d0();
    f_003550();
    m24188[0].f_0995e0(f_0037bc(), 0);
    m24572[10].timer = 0;
    m24572[10].b = 0;
    m24572[10].first = 0;
    m24572[10].subFirst = 0;
    f_003550();
    f_005320(&m24572[10]);
    m25020 = 0;
    m25028 = &CSequence::f_004770;
}

/* @implements 0x004770 us f_004770
   WHAT IT DOES: Leaves sequence 6: stops its players and the main timer. */
void CSequence::f_004770()
{
    f_005470(&m24572[10]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x0047a8 us f_0047a8
   WHAT IT DOES: Enters sequence 7, like f_0046ec with another effect set, then waits in
   f_00482c to leave. */
void CSequence::f_0047a8()
{
    f_0057d0();
    f_00356c();
    m24188[0].f_0995e0(f_0037bc(), 0);
    m24572[10].timer = 0;
    m24572[10].b = 0;
    m24572[10].first = 0;
    m24572[10].subFirst = 0;
    f_00356c();
    f_005320(&m24572[10]);
    m25020 = 0;
    m25028 = &CSequence::f_00482c;
}

/* @implements 0x00482c us f_00482c
   WHAT IT DOES: Leaves sequence 7: stops its players and the main timer. */
void CSequence::f_00482c()
{
    f_005470(&m24572[10]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x004864 us f_004864
   WHAT IT DOES: Measures the race's opening: lets the race world prepare, then times each
   stage of the opening (effects, next stage, race start, two more effect sets and the pause
   menu) and starts the main timer on the longest path through them. */
void CSequence::f_004864()
{
    f_01ca80(D_23be80);
    D_1e38dc = f_003890();
    D_1e38e0 = f_003860();
    D_1e38e4 = f_003830();
    D_1e38e8 = f_0038c8();
    D_1e38ec = f_003800();
    D_1e38f0 = f_0038f8();
    int len = D_1e38dc;
    len = MAX(D_1e38e0 + D_1e38e4, len);
    len = MAX(D_1e38e0 + D_1e38e8 + D_1e38ec + D_1e38f0, len);
    m24188[0].f_0995e0(len, 0);
}

/* @implements 0x00493c us f_00493c
   WHAT IT DOES: Stops the main timer. */
void CSequence::f_00493c()
{
    m24188[0].f_099640();
}

/* @implements 0x004958 us f_004958
   WHAT IT DOES: Starts the first stage of the race opening on the second timer,
   synchronised to the main timer, saving the main timer's state. */
void CSequence::f_004958()
{
    m24572[6].timer = 1;
    m24572[6].b = 0;
    Elem24 *t = &m24188[0];
    m24572[6].saved = t->f_0996b0(0);
    int len = D_1e38dc;
    m24188[1].f_0995e0(len, t->f_099684(len, 0));
}

/* @implements 0x0049e0 us f_0049e0
   WHAT IT DOES: Stops the first opening stage and restores the main timer. */
void CSequence::f_0049e0()
{
    m24188[1].f_099640();
    m24188[0].f_0996dc(m24572[6].saved);
}

/* @implements 0x004a28 us f_004a28
   WHAT IT DOES: Starts the second stage of the race opening on the second timer. */
void CSequence::f_004a28()
{
    m24572[7].timer = 1;
    m24572[7].b = 0;
    Elem24 *t = &m24188[0];
    m24572[7].saved = t->f_0996b0(0);
    int len = D_1e38e0;
    m24188[1].f_0995e0(len, t->f_099684(len, 0));
}

/* @implements 0x004ab0 us f_004ab0
   WHAT IT DOES: Stops the second opening stage and restores the main timer. */
void CSequence::f_004ab0()
{
    m24188[1].f_099640();
    m24188[0].f_0996dc(m24572[7].saved);
}

/* @implements 0x004af8 us f_004af8
   WHAT IT DOES: Starts the third stage of the race opening on the third timer. */
void CSequence::f_004af8()
{
    m24572[8].timer = 2;
    m24572[8].b = 0;
    Elem24 *t = &m24188[0];
    m24572[8].saved = t->f_0996b0(0);
    int len = D_1e38e4;
    m24188[2].f_0995e0(len, t->f_099684(len, 0));
}

/* @implements 0x004b80 us f_004b80
   WHAT IT DOES: Stops the third opening stage and restores the main timer. */
void CSequence::f_004b80()
{
    m24188[2].f_099640();
    m24188[0].f_0996dc(m24572[8].saved);
}

/* @implements 0x004bc8 us f_004bc8
   WHAT IT DOES: Starts the last three stages of the race opening on the third, fourth and
   fifth timers. */
void CSequence::f_004bc8()
{
    Elem24 *t = &m24188[0];
    m24572[9].timer = 2;
    m24572[9].b = 0;
    m24572[9].saved = t->f_0996b0(0);
    int len = D_1e38e8;
    m24188[2].f_0995e0(len, t->f_099684(len, 0));
    m24572[10].timer = 3;
    m24572[10].b = 0;
    m24572[10].saved = t->f_0996b0(0);
    len = D_1e38ec;
    m24188[3].f_0995e0(len, t->f_099684(len, 0));
    m24572[12].timer = 4;
    m24572[12].b = 0;
    m24572[12].saved = t->f_0996b0(0);
    len = D_1e38f0;
    m24188[4].f_0995e0(len, t->f_099684(len, 0));
}

/* @implements 0x004cf0 us f_004cf0
   WHAT IT DOES: Stops the last three opening stages, restoring the main timer each time. */
void CSequence::f_004cf0()
{
    m24188[4].f_099640();
    m24188[0].f_0996dc(m24572[12].saved);
    m24188[3].f_099640();
    m24188[0].f_0996dc(m24572[10].saved);
    m24188[2].f_099640();
    m24188[0].f_0996dc(m24572[9].saved);
}

/* @implements 0x004d88 us f_004d88
   WHAT IT DOES: Enters the race (sequence 8): resets, measures the opening, starts its first
   stage with the common effects and runs its players, then continues in f_004df8. */
void CSequence::f_004d88()
{
    f_0057d0();
    f_004864();
    f_004958();
    f_003604();
    f_003550();
    m24572[6].first = 0;
    m24572[6].subFirst = 0;
    f_005320(&m24572[6]);
    m25020 = &CSequence::f_004df8;
}

/* @implements 0x004df8 us f_004df8
   WHAT IT DOES: Moves the race opening on: ends the first stage, runs the second (the next
   race stage) and the third (the race start), then waits for the race in f_004ea0. */
void CSequence::f_004df8()
{
    f_003650();
    f_003588();
    f_005470(&m24572[6]);
    f_0049e0();
    f_004a28();
    f_0035e4();
    m24572[7].first = 0;
    m24572[7].subFirst = 0;
    f_005320(&m24572[7]);
    f_004af8();
    f_0035ac();
    m24572[8].first = 16;
    m24572[8].subFirst = 8;
    f_005320(&m24572[8]);
    m25020 = &CSequence::f_004ea0;
}

/* @implements 0x004ea0 us f_004ea0
   WHAT IT DOES: Tells the race world, controller and race object that the opening is done,
   then waits in f_004efc for all three to be ready. */
void CSequence::f_004ea0()
{
    f_01cec4(D_23be80);
    f_09437c(D_242c90);
    f_097100(D_242dec);
    m25020 = &CSequence::f_004efc;
}

/* @implements 0x004efc us f_004efc
   WHAT IT DOES: Once the race world, controller and race object are all ready, ends the
   third opening stage and runs the last three (two effect sets and the pause menu), then
   continues in f_005000. */
void CSequence::f_004efc()
{
    if (f_01d174(D_23be80) == 1 && f_094398(D_242c90) && f_09711c(D_242dec)) {
        f_005470(&m24572[8]);
        f_004b80();
        f_004bc8();
        f_003634();
        m24572[9].first = 16;
        m24572[9].subFirst = 8;
        f_005320(&m24572[9]);
        f_00356c();
        m24572[10].first = 24;
        m24572[10].subFirst = 12;
        f_005320(&m24572[10]);
        f_0036a0();
        m24572[12].first = 76;
        m24572[12].subFirst = 38;
        f_005320(&m24572[12]);
        m25020 = &CSequence::f_005000;
    }
}

/* @implements 0x005000 us f_005000
   WHAT IT DOES: Starts the race's last effect set and waits in f_005044 to leave. */
void CSequence::f_005000()
{
    f_003674();
    m25020 = 0;
    m25028 = &CSequence::f_005044;
}

/* @implements 0x005044 us f_005044
   WHAT IT DOES: Leaves the race: ends the race object, controller and world, stops every
   opening stage's players and timers and the main timer. */
void CSequence::f_005044()
{
    f_097124(D_242dec);
    f_094360(D_242c90);
    f_01d994(D_23be80);
    f_003690();
    f_0035a4();
    f_005470(&m24572[12]);
    f_005470(&m24572[10]);
    f_005470(&m24572[9]);
    f_005470(&m24572[7]);
    f_004cf0();
    f_004ab0();
    f_00493c();
    m25028 = 0;
}

/* @implements 0x0050ec us f_0050ec
   WHAT IT DOES: Enters the title (sequence 0): resets, shows the title scene on the main
   timer, runs its players and waits in f_005170 to leave. */
void CSequence::f_0050ec()
{
    f_0057d0();
    f_003744();
    m24188[0].f_0995e0(f_0037bc(), 0);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_003744();
    f_005320(&m24572[1]);
    m25020 = 0;
    m25028 = &CSequence::f_005170;
}

/* @implements 0x005170 us f_005170
   WHAT IT DOES: Leaves the title: stops its players and the main timer. */
void CSequence::f_005170()
{
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x0051a8 us f_0051a8
   WHAT IT DOES: Enters the demo (sequence 1): resets, shows the demo's scene on the main
   timer, runs its players and waits in f_00522c to leave. */
void CSequence::f_0051a8()
{
    f_0057d0();
    f_003760();
    m24188[0].f_0995e0(f_0037bc(), 0);
    m24572[1].timer = 0;
    m24572[1].b = 0;
    m24572[1].first = 0;
    m24572[1].subFirst = 0;
    f_003760();
    f_005320(&m24572[1]);
    m25020 = 0;
    m25028 = &CSequence::f_00522c;
}

/* @implements 0x00522c us f_00522c
   WHAT IT DOES: Leaves the demo: stops its players and the main timer. */
void CSequence::f_00522c()
{
    f_005470(&m24572[1]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @implements 0x005264 us f_005264
   WHAT IT DOES: Enters sequence 2: resets, starts its (empty) scene on the main timer, runs
   its players and waits in f_0052e8 to leave. */
void CSequence::f_005264()
{
    f_0057d0();
    f_0037b4();
    m24188[0].f_0995e0(f_0037bc(), 0);
    m24572[13].timer = 0;
    m24572[13].b = 0;
    m24572[13].first = 0;
    m24572[13].subFirst = 0;
    f_0037b4();
    f_005320(&m24572[13]);
    m25020 = 0;
    m25028 = &CSequence::f_0052e8;
}

/* @implements 0x0052e8 us f_0052e8
   WHAT IT DOES: Leaves sequence 2: stops its players and the main timer. */
void CSequence::f_0052e8()
{
    f_005470(&m24572[13]);
    m24188[0].f_099640();
    m25028 = 0;
}

/* @draft 0x005320 us f_005320
   WHAT IT DOES: Starts a slot: for each of the 64 requested scenes, takes the next free scene
   player (or sub-player, for a scene with a part) from the slot's ranges, starts it on the
   slot's timer, and records where each range ends. */
void CSequence::f_005320(Slot *s)
{
    int i;
    int n = s->first;
    int m = s->subFirst;
    Elem280 *p = &m668[n];
    Elem28 *q = &m23068[m];
    Elem24 *t = &m24188[s->timer];
    int b = s->b;

    f_002410();
    for (i = 0; i < 64; i++) {
        int kind, id;
        f_002550(i, &kind, &id);
        if (id) {
            if (kind == 0) {
                p->f_00260c(id, t, b, b);
                n++;
                p->f_002734(m0);
                p++;
            } else {
                q->f_002b34(kind, id, t);
                q->f_002c50(m0);
                m++;
                q++;
            }
        }
    }
    s->subLast = m;
    s->last = n;
    f_002304();
}

/* @implements 0x005470 us f_005470
   WHAT IT DOES: Stops a slot: releases its scene players and sub-players, last first, and
   empties its ranges. */
void CSequence::f_005470(Slot *s)
{
    int first = s->first;
    int subFirst = s->subFirst;
    int subLast = s->subLast;
    int i;

    for (i = s->last - 1; i >= first; i--)
        m668[i].f_0026cc();
    for (i = subLast - 1; i >= subFirst; i--)
        m23068[i].f_002be8();
    s->first = 0;
    s->subFirst = 0;
    s->last = 0;
    s->subLast = 0;
}

/* @draft 0x005554 us f_005554
   WHAT IT DOES: Starts the sequence the manager was asked for: picks the entry handler for its
   number. Unless told not to wait, it then steps the sequence until it has finished
   entering. */
void CSequence::f_005554(unsigned char nowait)
{
    f_099710();
    m0 = nowait;
    switch (m8) {
    case 9:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
        m25020 = &CSequence::f_00391c;
        break;
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        m25020 = &CSequence::f_003dfc;
        break;
    case 10:
        m25020 = &CSequence::f_0039fc;
        break;
    case 11:
        m25020 = &CSequence::f_003af4;
        break;
    case 12:
        m25020 = &CSequence::f_003c58;
        break;
    case 3:
        m25020 = &CSequence::f_0040f0;
        break;
    case 5:
        m25020 = &CSequence::f_004198;
        break;
    case 4:
        m25020 = &CSequence::f_004484;
        break;
    case 6:
        m25020 = &CSequence::f_0046ec;
        break;
    case 7:
        m25020 = &CSequence::f_0047a8;
        break;
    case 8:
        m25020 = &CSequence::f_004d88;
        break;
    case 0:
        m25020 = &CSequence::f_0050ec;
        break;
    case 1:
        m25020 = &CSequence::f_0051a8;
        break;
    case 2:
        m25020 = &CSequence::f_005264;
        break;
    }
    if (m0 == 0) {
        while (f_0056d0() == 1)
            f_005910();
    }
}

/* @implements 0x0056c4 us f_0056c4
   WHAT IT DOES: Records the requested sequence as the current one. */
void CSequence::f_0056c4()
{
    m144 = m8;
}

/* @implements 0x0056d0 us f_0056d0
   WHAT IT DOES: Returns whether the sequence is still busy: the loader is working or has
   queued requests, or a handler is still pending. */
int CSequence::f_0056d0()
{
    if (D_1da468.m12348 || !D_1da468.queue.Empty() || !D_1d9c5c.Empty())
        return 1;
    return m25020 != 0;
}

/* @implements 0x005720 us f_005720
   WHAT IT DOES: Runs the sequence until it is idle, keeping the frame going (step, draw,
   wait for vertical blank, flip) meanwhile. */
void CSequence::f_005720()
{
    while (f_0056d0() == 1) {
        f_005910();
        f_021bbc();
        f_021720();
        f_0221e8(7);
        f_021750();
    }
}

/* @implements 0x00578c us f_00578c
   WHAT IT DOES: Asks for a reset: at once when idle, otherwise marks it to happen when the
   current handler has finished. */
void CSequence::f_00578c()
{
    if (f_0056d0())
        m340 = 1;
    else
        f_0057d0();
}

/* @implements 0x0057d0 us f_0057d0
   WHAT IT DOES: Resets the sequence: stops the sound loader, forgets the current sequence,
   and either runs the pending leave handler or releases every scene player, sub-player and
   timer. */
void CSequence::f_0057d0()
{
    f_018b10(D_2301b0);
    m144 = -1;
    if (m25028) {
        (this->*m25028)();
    } else {
        int i;
        for (i = 0; i < 80; i++)
            m668[i].f_0026cc();
        for (i = 0; i < 40; i++)
            m23068[i].f_002be8();
        for (i = 0; i < 16; i++)
            m24188[i].f_099640();
    }
}

/* @implements 0x0058b4 us f_0058b4
   WHAT IT DOES: Initialises the manager's environment: clears the extra length, sets up the
   scene tables and the loader, and clears all 15 game parameters and their remembered
   copies. */
void CSequence::f_0058b4()
{
    m332 = 0;
    f_001ff4(0);
    f_001c1c(&D_1da468);
    for (int i = 0; i < 15; i++) {
        m24[i] = Param(0);
        m156[i] = Param(0);
    }
}

/* @implements 0x005910 us f_005910
   WHAT IT DOES: One step of the sequence: when the loaders are idle, runs the pending
   handler; when that finishes the transition, makes the requested sequence current and
   performs a reset that was asked for meanwhile. Then lets the loader run. */
void CSequence::f_005910()
{
    if (!D_1da468.m12348 && D_1da468.queue.Empty() && D_1d9c5c.Empty() && m25020) {
        (this->*m25020)();
        if (!m25020) {
            f_0056c4();
            if (m340) {
                m340 = 0;
                f_0057d0();
            }
        }
    }
    f_001c24(&D_1da468);
}

/* @implements 0x0059f4 us f_0059f4
   WHAT IT DOES: Shuts the loader and the scene tables down. */
void CSequence::f_0059f4()
{
    f_001e2c(&D_1da468);
    f_00204c();
}

/* @implements 0x005a1c us f_005a1c
   WHAT IT DOES: Adds an outside scene player to the list searched by name. */
void CSequence::f_005a1c(Elem280 *e)
{
    m348[m344++] = e;
}

static inline bool Match(const char *s, const char *name)
{
    while (*name && *s == *name) {
        s++;
        name++;
    }
    return *name == 0;
}

/* @draft 0x005a38 us f_005a38
   WHAT IT DOES: Finds the scene player showing the named scene: first among the manager's
   own players, then among the outside players added to its list. Returns 0 if none. */
Elem280 *CSequence::f_005a38(const char *name)
{
    int i;

    for (i = 0; i < 80; i++)
        if (m668[i].idx != -1 && Match(D_1b8c04[m668[i].idx].name, name))
            break;
    if (i < 80)
        return &m668[i];
    for (i = 0; i < 80; i++)
        if (m348[i]->idx != -1 && Match(D_1b8c04[m348[i]->idx].name, name))
            break;
    if (i < 80)
        return m348[i];
    return 0;
}

/* @draft 0x005b8c us f_005b8c
   WHAT IT DOES: Finds the sub-player showing the named part. The function map merges it into
   f_005a38. */
Elem28 *CSequence::f_005b8c(const char *name)
{
    int i;

    for (i = 0; i < 40; i++)
        if (m23068[i].idx != -1 && Match(D_1c0614[m23068[i].idx].name, name))
            break;
    return &m23068[i];
}

/* @draft 0x005c34 us f_005c34
   WHAT IT DOES: Sends a named event to the scene player or sub-player that knows it and
   returns its answer, 0 if none does. */
int CSequence::f_005c34(const char *name)
{
    int i;

    for (i = 0; i < 80; i++) {
        Elem280 *e = &m668[i];
        if (e->idx != -1 && f_002184(name, e->idx) != -1)
            return e->f_002acc(name);
    }
    for (i = 0; i < 40; i++) {
        Elem28 *e = &m23068[i];
        if (e->idx != -1 && strcmp(D_1c0614[e->idx].name, name) == 0)
            return e->f_002e5c();
    }
    return 0;
}

/* @implements 0x005d4c us f_005d4c
   WHAT IT DOES: Requests the named scene. */
void CSequence::f_005d4c(const char *name)
{
    f_0023d4(name);
}

/* @implements 0x005d68 us f_005d68
   WHAT IT DOES: Requests a scene part by its owner and name. */
void CSequence::f_005d68(int a, int b)
{
    f_002380(a, b);
}

/* @implements 0x005d88 us __static_initialization_and_destruction_0
   WHAT IT DOES: Builds the sequence manager at program start and tears it down at exit. */

/* @implements 0x005ea4 us _GLOBAL__I_D_1dd6b0
   WHAT IT DOES: The program-start hook that builds the sequence manager. */

/* @implements 0x005ec4 us _GLOBAL__D_D_1dd6b0
   WHAT IT DOES: The program-exit hook that tears the sequence manager down. */

/* @draft 0x005ee4 us _ZN9CSequenceC1Ev
   WHAT IT DOES: Builds the manager: marks every player free, clears the timers and the
   handlers, and resets. (Defined in the class.) */
