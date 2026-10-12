/* The program's entry object file (retail 0x0003f0 to 0x000810): main, the exit and power
   callbacks, and loading the system modules the game needs from the disc. */

#include <stdio.h>
#include <string.h>
#include "psp/kernel.h"

extern "C" {
void f_01c1e4(int language);
void f_08a998(void);
void f_0881ec(void *);
void f_06c530(void);
}

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
    int m4;
    int m8;
    int m12;
    void *m16;
    int m20[4];
};
}

namespace System {
class CMainLoopJob : public Ng::CJob {
public:
    CMainLoopJob() { m16 = 0; }
    void f_000810();
    virtual void Begin();
    virtual int Step();
    virtual void End();
};
}


extern System::CMainLoopJob *D_1d88a0;
extern SceUID D_1d889c;
extern char D_1b8ae0[];
extern char D_241810[];
extern char D_1e8ec4[];

/* @implements 0x0003f0 us f_0003f0
   WHAT IT DOES: Runs when the player quits from the system menu. It lets the main loop job
   shut down the game, frees the job, and tells the system the callback succeeded. */
int f_0003f0(int arg1, int arg2, void *common)
{
    D_1d88a0->End();
    delete D_1d88a0;
    return 0;
}

/* @implements 0x000430 us f_000430
   WHAT IT DOES: Runs on power events. When the console has finished resuming from sleep, it
   restarts the three subsystems that do not survive suspend. */
int f_000430(int unknown, int powerInfo, void *common)
{
    if (powerInfo & 0x10000) {
        f_08a998();
        f_0881ec(D_241810);
        f_06c530();
    }
    return 0;
}

/* @implements 0x000478 us f_000478
   WHAT IT DOES: Sets the folder every data file is loaded from, as disc0: followed by the
   given path. */
void f_000478(const char *dir)
{
    sprintf(D_1b8ae0, "disc0:%s", dir);
}

/* @draft 0x0004a4 us f_0004a4
   WHAT IT DOES: Loads and starts one system module from the data folder into the given memory
   partition. It returns the module's id; 0 if the file cannot be opened; or, after undoing
   whatever had already succeeded, the error code of the load or start that failed. */
SceUID f_0004a4(const char *name, int partition)
{
    SceKernelLMOption option;
    char path[256];
    int status = 0;
    SceUID fd, mod;
    int ret;

    sprintf(path, "%s%s", D_1b8ae0, name);
    memset(&option, 0, sizeof(option));
    option.size = sizeof(option);
    option.mpidtext = partition;
    option.position = 0;
    ret = fd = sceIoOpen(path, 1, 0);
    if (ret < 0)
        return 0;
    mod = sceKernelLoadModuleByID(fd, 0, &option);
    ret = mod;
    if (mod >= 0) {
        ret = sceKernelStartModule(mod, 0, 0, &status, 0);
        if (ret >= 0) {
            sceIoClose(fd);
            return mod;
        }
        if (mod > 0) {
            sceKernelStopModule(mod, 0, 0, &status, 0);
            sceKernelUnloadModule(mod);
        }
    }
    if (fd > 0)
        sceIoClose(fd);
    return ret;
}

/* @implements 0x0005c8 us f_0005c8
   WHAT IT DOES: Points the data folder at the game's data on the disc and loads every system
   module the game uses: the kernel-side helpers, sound, video and audio codecs, networking
   for ad hoc play, movie playback and ATRAC3plus music. */
void f_0005c8(void)
{
    f_000478("/PSP_GAME/USRDIR/Data/");
    f_0004a4("Module/kmodule/ifhandle.prx", 1);
    f_0004a4("Module/kmodule/memab.prx", 1);
    f_0004a4("Module/kmodule/pspnet_adhoc_auth.prx", 1);
    f_0004a4("Module/kmodule/sc_sascore.prx", 1);
    f_0004a4("Module/kmodule/videocodec.prx", 1);
    f_0004a4("Module/kmodule/audiocodec.prx", 1);
    f_0004a4("Module/kmodule/mpegbase.prx", 1);
    f_0004a4("Module/module/pspnet.prx", 2);
    f_0004a4("Module/module/pspnet_adhoc.prx", 2);
    f_0004a4("Module/module/pspnet_adhocctl.prx", 2);
    f_0004a4("Module/module/pspnet_adhoc_matching.prx", 2);
    f_0004a4("Module/module/mpeg.prx", 2);
    f_0004a4("Module/module/libatrac3plus.prx", 2);
}

/* @implements 0x0006b8 us main
   WHAT IT DOES: The game's entry point. It applies the console's language setting, installs the
   exit and power callbacks, lets this thread use the vector unit at the game's priority,
   creates the main loop job, maps the disc, loads the system modules and sets up the pad. Then
   it starts the job, steps it until it reports it is finished, stops it and frees it. */
int main(void)
{
    int language = 0;

    sceUtilityGetSystemParamInt(8, &language);
    f_01c1e4(language);
    sceKernelRegisterExitCallback(sceKernelCreateCallback("exit", f_0003f0, 0));
    D_1d889c = sceKernelCreateCallback("PowerCallback", f_000430, 0);
    scePowerRegisterCallback(0, D_1d889c);
    sceKernelChangeCurrentThreadAttr(0, 0x4000);
    sceKernelChangeThreadPriority(0, 111);
    D_1d88a0 = new System::CMainLoopJob;
    D_1d88a0->f_000810();
    sceIoAssign("disc0:", "umd0:", "isofs0:", 1, 0, 0);
    f_0005c8();
    sceCtrlSetSamplingMode(1);
    sceCtrlSetSamplingCycle(0);
    D_1d88a0->m16 = D_1e8ec4;
    D_1d88a0->Begin();
    while (!D_1d88a0->Step())
        ;
    D_1d88a0->End();
    delete D_1d88a0;
    return 0;
}
