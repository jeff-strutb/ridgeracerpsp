/* The main loop job (retail 0x000810 to 0x001570): System::CMainLoopJob, the job main() creates
   and steps. It brings the game up (memory statistics, the display, the loading screen, the
   pad, sound and the data packages), runs one frame per step with catch up frames when the game
   falls behind the display, and tears everything down again at exit. The object file also owns
   the global objects that startup builds and shutdown destroys: the pad, the controller, and six
   data packages. */

#include <string.h>

extern "C" {
int sceDisplayGetCurrentHcount(void);
int sceDisplayGetAccumulatedHcount(void);
unsigned int sceKernelGetSystemTimeLow(void);
int sceKernelPowerTick(int type);
int sceKernelCheckCallback(void);
int sceKernelExitGame(void);
}

void f_0213a0(int size);
void f_022c30(int n);
void f_028bac(void *p, int a, int b, int c, int d);
void f_021720(void);
void f_021ff8(int color);
void f_021750(void);
int f_01c260(void);
void f_118f8c(int x, int y, int color, const char *text);
void f_021bbc(void);
void f_021b9c(void);
void f_006040(void);
void f_0058b4(void *p);
void f_005910(void *p);
void f_0059f4(void *p);
void f_005a1c(void *p, void *pack);
void f_01c2cc(void *p, void *data);
void f_01c458(void *p, void *a, void *b, int c, int d);
void f_01c5dc(void *p);
void f_01c648(void *p);
const char *f_01c26c(const char *name);
void f_095f9c(void *p);
void f_095854(void *p, int a, void *data);
void f_096334(void *p);
void f_0960cc(void *p);
void f_093fe0(void *p, void *a, void *b);
void f_09411c(void *p);
void f_02c870(void);
void f_0451b4(int size);
void f_017d94(void *p);
void f_02db94(void);
void f_0221e8(int n);
void f_08a864(void);
void f_027830(void);
void f_088138(void *p);
void f_113488(int n);
void f_10be40(void);
void f_021cb8(void);

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
};
}

/* The display timing settings. Their base part is only known by its constructor, at 0x0992fc;
   the compiler supplies the constructor of the whole. */
struct f_0992fc_t {
    f_0992fc_t();
    int m0[15];
};

struct CDisplayTiming : f_0992fc_t {
    void f_099354(int a, int b);
    int m60;
};

/* The pad reader. */
struct CPad {
    void f_09936c(int repeatDelay, int repeatRate);
    void f_0993fc();
};

/* Heap statistics. */
struct CMemoryStats {
    void f_0992ac();
    void f_09923c();
    int m[11];
};

namespace Controller {
class CCustomController {
public:
    CCustomController() {}
    virtual void f_0425b0(int a, int b, int c);
    virtual ~CCustomController();
    virtual void f_041e48();
    int m4[29];
};
}

/* A data package: one archive file from the disc, whose entries are looked up by name. */
class CPackage {
public:
    CPackage() { m0 = -1; }
    ~CPackage() { f_0026cc(); }
    void f_00260c(const char *name, int a, int b);
    void f_0026cc();
    void f_002734(int a);
    void *f_002acc(const char *name);
    int m0;
    int m4[69];
};

struct CStream {
    void *m0;
    void *m4;
};

/* A table read from the database package. */
struct CTable {
    void f_03680c(void *data);
};

struct CFlags {
    char m0[2056];
    bool loaded;
};

namespace System {
class CMainLoopJob : public Ng::CJob {
public:
    void f_000810();
    virtual void Begin();
    virtual int Step();
    virtual void End();
    void f_000f08();
    int f_001154(bool first);
    void f_001380(Ng::CJob *job);

    int m4;
    bool m8;
    bool m9;
    bool m10;
    bool m11;
    bool m12;
    bool m13;
    bool m14;
    Ng::CJob *m16;
    int m20;
    int m24;
    int m28;
    bool m32;
};
}

extern const char *D_1b8be0[];
extern int D_1b8bfc;
extern int D_1d9c20;
extern int D_1d9c24;
extern int D_1d9c28;
extern CFlags D_1d9c5c;
extern char D_1d9020[];
extern char D_1dd6b0[];
extern char D_23bb4c[];
extern char D_241810[];
extern CStream D_242ca8;
extern char D_242cb0[];
extern char D_242c90[];
extern CTable D_2407a8;
extern CTable D_240740;
extern CTable D_2407d0;
extern CTable D_24504c;
extern char D_2301b0[];
extern CPackage D_2301d4;
extern int D_24517c;
extern int D_245178;
extern CPad D_24518c;

CDisplayTiming D_1d88a4;
CMemoryStats D_1d88e4;
Controller::CCustomController D_1d8910[1];
CPackage D_1d8988;
CPackage D_1d8aa0;
CPackage D_1d8bb8;
CPackage D_1d8cd0;
CPackage D_1d8de8;
CPackage D_1d8f00;

/* @implements 0x000810 us f_000810
   WHAT IT DOES: The first setup when the game starts. It records the heap statistics, sets up
   the memory and the display, clears the screen, and shows NOW LOADING (in the console's
   language, centred) on both display buffers; in German it adds the two dots of the umlaut. */
void System::CMainLoopJob::f_000810()
{
    const char *msg;
    int w;

    D_1d88e4.f_0992ac();
    f_0213a0(0x180000);
    f_022c30(1000);
    f_028bac(D_1d9020, 8, 8, 32, 0);
    f_021720();
    f_021ff8(0);
    f_021750();
    msg = D_1b8be0[f_01c260()];
    w = strlen(msg) * 4;
    f_118f8c(240 - w, 131, -1, msg);
    if (f_01c260() == 4) {
        f_118f8c(247 - w, 123, -1, ".");
        f_118f8c(250 - w, 123, -1, ".");
    }
    f_021bbc();
    f_021720();
    f_021ff8(0);
    f_021750();
    f_118f8c(240 - w, 131, -1, msg);
    if (f_01c260() == 4) {
        f_118f8c(247 - w, 123, -1, ".");
        f_118f8c(250 - w, 123, -1, ".");
    }
}

/* @draft 0x0009b8 us _ZN6System12CMainLoopJob5BeginEv
   WHAT IT DOES: Starts the game. It clears the job's flags, starts the controller and the pad,
   then loads the sound data for the console's language and registers its banks, the engine
   sounds, the streamed music tables, the course, car, race and menu music databases, the
   Rally-X data and the main menu package, and finally starts the first job. */
void System::CMainLoopJob::Begin()
{
    m4 = 0;
    D_1d9c20 = 1;
    m8 = true;
    m9 = true;
    m10 = true;
    m11 = false;
    m12 = false;
    m13 = false;
    m14 = false;
    D_1d8910[0].f_0425b0(0, 10, 5);
    D_24517c = -1;
    D_245178 = -1;
    D_1d88a4.m60 = -1;
    D_24518c.f_09936c(10, 5);
    D_1d88a4.f_099354(256, 8);
    f_006040();
    f_0058b4(D_1dd6b0);
    D_1d9c5c.loaded = false;
    D_1d9c20 = 2;

    int lang = f_01c260();
    switch (lang) {
    case 2: D_1d8988.f_00260c("SoundCommonHD_Fr", 0, 0); break;
    case 3: D_1d8988.f_00260c("SoundCommonHD_Sp", 0, 0); break;
    case 4: D_1d8988.f_00260c("SoundCommonHD_Ge", 0, 0); break;
    case 5: D_1d8988.f_00260c("SoundCommonHD_It", 0, 0); break;
    default: D_1d8988.f_00260c("SoundCommonHD_En", 0, 0); break;
    }
    D_1d8988.f_002734(0);
    f_01c2cc(D_23bb4c, D_1d8988.f_002acc("SndCnfg"));
    {
        CPackage bd;
        switch (lang) {
        case 2: bd.f_00260c("SoundCommonBD_Fr", 0, 0); break;
        case 3: bd.f_00260c("SoundCommonBD_Sp", 0, 0); break;
        case 4: bd.f_00260c("SoundCommonBD_Ge", 0, 0); break;
        case 5: bd.f_00260c("SoundCommonBD_It", 0, 0); break;
        default: bd.f_00260c("SoundCommonBD_En", 0, 0); break;
        }
        bd.f_002734(0);
        f_01c458(D_23bb4c, D_1d8988.f_002acc("System"), bd.f_002acc("System"), 0, 0);
        f_01c458(D_23bb4c, D_1d8988.f_002acc("RallyX"), bd.f_002acc("RallyX"), 0, 0);
        f_01c458(D_23bb4c, D_1d8988.f_002acc("M_PLAYER"), bd.f_002acc("M_PLAYER"), 0, 0);
        bd.f_0026cc();
    }
    D_1d9c20 = 3;
    f_005a1c(D_1dd6b0, &D_1d8988);
    D_1d8aa0.f_00260c("EngineSoundData", 0, 0);
    f_095f9c(&D_242ca8);
    D_1d8f00.f_00260c("StreamCommon", 0, 0);
    D_1d8f00.f_002734(0);
    f_095854(D_242ca8.m4, 0, D_1d8f00.f_002acc("BgmHeader"));
    f_096334(D_242cb0);
    void *tbl = D_1d8f00.f_002acc("DjTbl");
    f_093fe0(D_242c90, tbl, D_1d8f00.f_002acc("DjDrive"));
    D_1d9c20 = 4;
    D_1d8de8.f_00260c("DB", 0, 0);
    D_1d8de8.f_002734(0);
    D_2407a8.f_03680c(D_1d8de8.f_002acc("Course"));
    D_240740.f_03680c(D_1d8de8.f_002acc("Car"));
    D_2407d0.f_03680c(D_1d8de8.f_002acc("Race"));
    D_24504c.f_03680c(D_1d8de8.f_002acc("MenuBgm"));
    f_02c870();
    f_0451b4(0x100000);
    f_017d94(D_2301b0);
    D_1d8bb8.f_00260c("RallyXCommon", 0, 0);
    D_1d8cd0.f_00260c("RallyX_BGM", 0, 0);
    D_2301d4.f_00260c(f_01c26c("MainMenuSwg"), 0, 0);
    D_1d9c5c.loaded = true;
    m16->Begin();
}

/* @implements 0x000f08 us f_000f08
   WHAT IT DOES: Marks the start of a frame: it records how far the display is through the
   current scanline count and the system time at which this frame's first line began. */
void System::CMainLoopJob::f_000f08()
{
    int line = sceDisplayGetCurrentHcount();
    D_1d9c24 = sceDisplayGetAccumulatedHcount() - line;
    volatile int now = sceKernelGetSystemTimeLow();
    D_1d9c28 = now - line * 16683 / 286;
}

/* @implements 0x000f7c us f_000f7c
   WHAT IT DOES: Returns how much of a frame time (as a percentage of 1/60 s) has passed since
   the frame started. */
float f_000f7c(void)
{
    volatile int now = sceKernelGetSystemTimeLow();
    return (float)(now - D_1d9c28) * 100.0f / 16683.0f;
}

/* @implements 0x000fcc us f_000fcc
   WHAT IT DOES: Tells whether the display has already passed the given number of frames since
   this frame started (less a few scanlines of slack), that is whether the game is behind. */
int f_000fcc(int frames)
{
    return sceDisplayGetAccumulatedHcount() - D_1d9c24 > frames * 286 - 5;
}

/* f_001014, retail 0x001014 (byte exact; its tag is held by the control set, src/control/batch4.c)
   WHAT IT DOES: Returns how many frames have passed since this frame started, counting a frame
   once 201 of its 286 scanlines have gone. */
int f_001014(void)
{
    int t, z;
    t = sceDisplayGetAccumulatedHcount();
    t -= D_1d9c24;
    t -= sceDisplayGetCurrentHcount();
    z = t % 286 < 201;
    return t / 286 + (z == 0);
}

/* @implements 0x001088 us f_001088
   WHAT IT DOES: Returns the time since the frame started in microseconds. */
int f_001088(void)
{
    return (int)(f_000f7c() * 166.83f);
}

/* @implements 0x0010b8 us _ZN6System12CMainLoopJob4StepEv
   WHAT IT DOES: Runs one display frame of the game. It waits for the display, runs a normal
   frame, then, while the display has already moved past the frames done, runs up to two more
   frames without drawing to catch up. The main loop never ends from here. */
int System::CMainLoopJob::Step()
{
    int n;

    f_021bbc();
    sceKernelGetSystemTimeLow();
    n = 0;
    f_001154(true);
    D_1b8bfc = 1;
    while (n < 3) {
        sceKernelGetSystemTimeLow();
        n++;
        if (f_000fcc(D_1b8bfc) == 0)
            break;
        f_001154(false);
        D_1b8bfc = D_1b8bfc + 1;
    }
    return 0;
}

/* @implements 0x001154 us f_001154
   WHAT IT DOES: Runs one game frame. A first frame of a display frame starts the frame timing
   and the draw lists; a catch up frame skips drawing. It reads the pad and the controller,
   steps the current job, keeps the console awake, and updates sound, the heap statistics and
   the sound banks, then counts the frame. */
int System::CMainLoopJob::f_001154(bool first)
{
    m32 = true;
    m14 = !first;
    if (!m14) {
        f_000f08();
        m28 = sceKernelGetSystemTimeLow();
        f_02db94();
        f_021720();
        f_0221e8(7);
        f_021750();
    }
    D_24518c.f_0993fc();
    {
        Controller::CCustomController *pad = D_1d8910;
        pad->f_041e48();
    }
    if (!m14)
        f_08a864();
    m16->Step();
    if (m32)
        sceKernelPowerTick(0);
    else
        sceKernelPowerTick(1);
    f_005910(D_1dd6b0);
    D_1d88e4.f_09923c();
    f_01c648(D_23bb4c);
    f_000f7c();
    f_021b9c();
    f_000f7c();
    m4++;
    return 0;
}

/* @draft 0x00127c us _ZN6System12CMainLoopJob3EndEv
   WHAT IT DOES: Shuts the game down. It ends the current job, then undoes each startup stage
   that was reached: the display, the sound, the streamed music and the sound banks. It lets
   the system run its callbacks for 300 more frames and then exits the game. */
void System::CMainLoopJob::End()
{
    int i;

    if (m16) {
        m16->End();
        m16 = 0;
    }
    f_027830();
    if (D_1d9c20 > 0)
        f_088138(D_241810);
    if (D_1d9c20 >= 2)
        f_0059f4(D_1dd6b0);
    if (D_1d9c20 >= 4) {
        f_09411c(D_242c90);
        f_0960cc(&D_242ca8);
    }
    if (D_1d9c20 >= 3) {
        f_113488(0);
        f_01c5dc(D_23bb4c);
        f_10be40();
    }
    for (i = 0; i < 300; i++) {
        sceKernelCheckCallback();
        f_021bbc();
    }
    f_021cb8();
    sceKernelExitGame();
}

/* @implements 0x001380 us f_001380
   WHAT IT DOES: Switches to another job: ends the current one, then starts the new one. */
void System::CMainLoopJob::f_001380(Ng::CJob *job)
{
    m16->End();
    m16 = job;
    job->Begin();
}

/* @draft 0x0013d0 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the display timing block, the controller and the six data
   packages (each starting with no file); at shutdown, releases the packages and destroys the
   controller. */

/* @implements 0x001514 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x001534 us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */

/* CDisplayTiming::CDisplayTiming, retail 0x001554 (its tag is held by the control set,
   src/control/batch1.c; the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The display timing block's constructor as the startup code calls it. */
