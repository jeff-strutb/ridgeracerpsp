/* The game mode job (retail 0x0067b4 to 0x006bbc): the job the main loop steps every frame. It
   owns one job per game mode (title, main menu, single race, wireless battle, options, save and
   load), runs the current one and switches to another when a mode asks for it. The two
   functions at 0x006b7c and 0x006b9c are the object file's own static constructor and
   destructor entry points, which the compiler generates. */

#include "psp/kernel.h"

extern "C" {
unsigned int sceKernelGetSystemTimeLow(void);
}

void f_0196cc(void *);
void f_01959c(void *);
extern char D_233f70[];

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
};
}

namespace Sequence {
/* The base of every mode job. Its two virtual functions after the job's own (named here by
   their vtable slot) run a state handler and queue a state; each mode job adds its own virtual
   destructor, which is why the static destruction below keeps one guard per object. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int);
    virtual void f_4(int);
};

class CTitleModeJob : public CModeJob {
public:
    CTitleModeJob();
    virtual ~CTitleModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4(int);
    char m4[0xf8 - 4];
};

class CMainMenuModeJob : public CModeJob {
public:
    CMainMenuModeJob();
    virtual ~CMainMenuModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4(int);
    char m4[0xd8 - 4];
};

class CSingleRaceModeJob : public CModeJob {
public:
    CSingleRaceModeJob();
    virtual ~CSingleRaceModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4(int);
    char m4[0x3e9c - 4];
};

class CWirelessBattleModeJob : public CModeJob {
public:
    CWirelessBattleModeJob();
    virtual ~CWirelessBattleModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4(int);
    char m4[0xc94 - 4];
};

class COptionModeJob : public CModeJob {
public:
    COptionModeJob();
    virtual ~COptionModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4(int);
    char m4[0x204 - 4];
};

class CSaveLoadModeJob : public CModeJob {
public:
    CSaveLoadModeJob();
    virtual ~CSaveLoadModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int);
    virtual void f_4(int);
    char m4[4];
};
}

/* The part of the main loop job this object file reads: a flag byte set while the game is
   paused, when the play time stops counting. */
struct MainLoopJobView {
    char m0[12];
    unsigned char paused;
};
extern MainLoopJobView *D_1d88a0;

namespace System {
class CGameModeJob : public Ng::CJob {
public:
    CGameModeJob();
    virtual void Begin();
    virtual int Step();
    virtual void End();
    Sequence::CModeJob *f_006978(int mode);
    void f_0069ec(int mode);
    void f_0069f4();

    int mode;
    int nextMode;
    Sequence::CModeJob *job;
    unsigned int seed;
    int frames;
    unsigned char m24;
};
}

System::CGameModeJob D_1e8ec4;
Sequence::CTitleModeJob D_1e8ee0;
Sequence::CMainMenuModeJob D_1e8fd8;
Sequence::CSingleRaceModeJob D_1e90b0;
Sequence::CWirelessBattleModeJob D_1ecf4c;
Sequence::COptionModeJob D_1edbe0;
Sequence::CSaveLoadModeJob D_1edde4;

/* @implements 0x0067b4 us _ZN6System12CGameModeJobC2Ev
   WHAT IT DOES: Constructs the game mode job with no mode job running and seeds its random
   number generator from the system clock. */
/* @implements 0x0067fc us _ZN6System12CGameModeJobC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */
System::CGameModeJob::CGameModeJob()
{
    volatile unsigned int t;

    seed = 0;
    job = 0;
    m24 = 0;
    t = sceKernelGetSystemTimeLow();
    seed = t;
}

/* @implements 0x006844 us _ZN6System12CGameModeJob5BeginEv
   WHAT IT DOES: Starts the game: clears the play time, resets two shared systems and starts
   the title screen mode. */
void System::CGameModeJob::Begin()
{
    m24 = 0;
    frames = 0;
    f_0196cc(D_233f70);
    f_01959c(D_233f70);
    job = f_006978(0);
    job->Begin();
}

/* @implements 0x0068b0 us _ZN6System12CGameModeJob4StepEv
   WHAT IT DOES: Runs one frame of the current mode, counts the frame unless the game is
   paused, switches mode if one was requested and steps the random number generator. It never
   reports itself finished. */
int System::CGameModeJob::Step()
{
    job->Step();
    if (!D_1d88a0->paused)
        frames++;
    f_0069f4();
    seed = seed * 0x19660d + 0x3c6ef35f;
    return 0;
}

/* @implements 0x006934 us _ZN6System12CGameModeJob3EndEv
   WHAT IT DOES: Stops the current mode, if one is running. */
void System::CGameModeJob::End()
{
    if (job) {
        job->End();
        job = 0;
    }
}

/* @implements 0x006978 us f_006978
   WHAT IT DOES: Makes the given mode the current and the requested one, and returns the job
   that runs it. Several mode numbers share a job (the single race job serves three of them,
   and any unknown number). */
Sequence::CModeJob *System::CGameModeJob::f_006978(int m)
{
    mode = nextMode = m;
    switch (m) {
    case 0:
        return &D_1e8ee0;
    case 1:
        return &D_1e8fd8;
    case 2:
    case 3:
    case 4:
    default:
        return &D_1e90b0;
    case 5:
    case 6:
        return &D_1ecf4c;
    case 7:
        return &D_1edde4;
    case 8:
        return &D_1edbe0;
    }
}

/* @implements 0x0069ec us f_0069ec
   WHAT IT DOES: Requests a switch to another mode, done at the end of the current frame. */
void System::CGameModeJob::f_0069ec(int m)
{
    nextMode = m;
}

/* @implements 0x0069f4 us f_0069f4
   WHAT IT DOES: When another mode has been requested, stops the current mode's job and starts
   the new one. */
void System::CGameModeJob::f_0069f4()
{
    if (mode != nextMode) {
        job->End();
        job = f_006978(nextMode);
        job->Begin();
    }
}

/* @implements 0x006a58 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the game mode job and every mode job; at shutdown,
   destroys the mode jobs in the reverse order. */

/* @implements 0x006b7c us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x006b9c us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */
