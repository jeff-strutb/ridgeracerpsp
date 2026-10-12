/* Sony PSP system calls used by the game, with the names PPSSPP's NID tables give their NIDs
   (config/us/imports.csv). Prototypes follow the calls as the retail code makes them. */
#ifndef PSP_KERNEL_H
#define PSP_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceUID;
typedef unsigned int SceSize;
typedef int (*SceKernelCallbackFunction)(int arg1, int arg2, void *common);

typedef struct SceKernelLMOption {
    SceSize size;
    SceUID mpidtext;
    SceUID mpiddata;
    unsigned int flags;
    char position;
    char access;
    char creserved[2];
} SceKernelLMOption;

SceUID sceIoOpen(const char *file, int flags, int mode);
int sceIoClose(SceUID fd);
int sceIoAssign(const char *dev1, const char *dev2, const char *dev3, int mode, void *argp, int argl);
SceUID sceKernelLoadModuleByID(SceUID fid, int flags, SceKernelLMOption *option);
int sceKernelStartModule(SceUID modid, SceSize argsize, void *argp, int *status, void *option);
int sceKernelStopModule(SceUID modid, SceSize argsize, void *argp, int *status, void *option);
int sceKernelUnloadModule(SceUID modid);
SceUID sceKernelCreateCallback(const char *name, SceKernelCallbackFunction func, void *arg);
int sceKernelRegisterExitCallback(SceUID cbid);
int scePowerRegisterCallback(int slot, SceUID cbid);
int sceKernelChangeCurrentThreadAttr(int unknown, int attr);
int sceKernelChangeThreadPriority(SceUID thid, int priority);
int sceUtilityGetSystemParamInt(int id, int *value);
int sceCtrlSetSamplingMode(int mode);
int sceCtrlSetSamplingCycle(int cycle);

#ifdef __cplusplus
}
#endif
#endif
