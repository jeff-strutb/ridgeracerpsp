/* Disc file access (retail 0x0277c4 to 0x027c84): mapping the disc device, opening data files
   by their path under the game's data folder, synchronous and asynchronous reads, seeking and
   the callback asynchronous reads report to. */

#include <string.h>
#include <stdio.h>
#include "psp/kernel.h"

extern "C" {
int iprintf(const char *fmt, ...);
int f_126f1c(const char *fmt, ...);
int sceIoUnassign(const char *dev);
int sceIoRead(SceUID fd, void *buf, int size);
long long sceIoLseek(SceUID fd, long long offset, int whence);
SceUID sceIoOpenAsync(const char *file, int flags, int mode);
int sceIoCloseAsync(SceUID fd);
int sceIoReadAsync(SceUID fd, void *buf, int size);
int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void *arg);
int sceIoWaitAsync(SceUID fd, long long *res);
int sceIoPollAsync(SceUID fd, long long *res);
}

extern SceUID D_23c7b0;
extern void *D_23c7b4;

/* @implements 0x0277c4 us f_0277c4
   WHAT IT DOES: Maps the disc device (disc0:) onto the UMD drive's ISO file system, printing an
   error if the system refuses. Returns the system's result. */
int f_0277c4(void)
{
    int r = sceIoAssign("disc0:", "umd0:", "isofs0:", 1, 0, 0);
    if (r < 0)
        iprintf("ERROR : sceIoAssign(%x)\n", r);
    return r;
}

/* @implements 0x027830 us f_027830
   WHAT IT DOES: Removes the disc device mapping when the game shuts down. */
void f_027830(void)
{
    sceIoUnassign("disc0:");
}

/* @implements 0x027850 us f_027850
   WHAT IT DOES: Opens a data file for reading by its path under the game's data folder on the
   disc (a leading slash is dropped and backslashes become slashes). Opening for writing is
   refused with an error and returns -1; a failed open prints the system's error code and
   returns it. */
int f_027850(const char *name, int write, int mode)
{
    char path[256];
    SceUID fd;
    char *p;

    name += (name[0] == '/' || name[0] == '\\');
    memset(path, 0, strlen(path));
    sprintf(path, "disc0:/PSP_GAME/USRDIR/Data/%s", name);
    for (p = path; *p; p++)
        if (*p == '\\')
            *p = '/';
    if (write) {
        f_126f1c("ERROR : Cannot open write file");
        return -1;
    }
    fd = sceIoOpen(path, 1, 0644);
    if (fd >= 0)
        return fd;
    iprintf("ERROR : sceIoOpen(%x)\n", fd);
    return fd;
}

/* @implements 0x02793c us f_02793c
   WHAT IT DOES: Closes a data file. */
void f_02793c(SceUID fd)
{
    sceIoClose(fd);
}

/* @implements 0x027958 us f_027958
   WHAT IT DOES: Reads bytes from a data file into a buffer and waits for them. */
int f_027958(SceUID fd, void *buf, int size)
{
    return sceIoRead(fd, buf, size);
}

/* @implements 0x027974 us f_027974
   WHAT IT DOES: Moves a data file's read position (from the start, the current position or the
   end). */
int f_027974(SceUID fd, int offset, int whence)
{
    return sceIoLseek(fd, offset, whence);
}

/* @implements 0x02799c us f_02799c
   WHAT IT DOES: Returns a data file's size in bytes by seeking to its end, then puts the read
   position back where it was. */
int f_02799c(SceUID fd)
{
    int cur = sceIoLseek(fd, 0, 1);
    int size = sceIoLseek(fd, 0, 2);
    sceIoLseek(fd, cur, 0);
    return size;
}

/* @implements 0x027a28 us f_027a28
   WHAT IT DOES: The asynchronous form of the data file open: starts opening a file under the
   game's data folder and returns at once. Writing is refused; a failed request prints the
   system's error code and returns it. */
int f_027a28(const char *name, int write, int mode)
{
    char path[256];
    SceUID fd;
    char *p;

    name += (name[0] == '/' || name[0] == '\\');
    memset(path, 0, strlen(path));
    sprintf(path, "disc0:/PSP_GAME/USRDIR/Data/%s", name);
    for (p = path; *p; p++)
        if (*p == '\\')
            *p = '/';
    if (write) {
        f_126f1c("ERROR : Cannot open file for writing");
        return -1;
    }
    fd = sceIoOpenAsync(path, 1, 0644);
    if (fd >= 0)
        return fd;
    iprintf("ERROR : sceIoOpenAsync(%x)\n", fd);
    return fd;
}

/* @implements 0x027b14 us f_027b14
   WHAT IT DOES: Starts closing a data file without waiting. */
void f_027b14(SceUID fd)
{
    sceIoCloseAsync(fd);
}

/* @implements 0x027b30 us f_027b30
   WHAT IT DOES: Starts an asynchronous read of a data file, first attaching the game's read
   completion callback to the file. */
int f_027b30(SceUID fd, void *buf, int size)
{
    int r = sceIoSetAsyncCallback(fd, D_23c7b0, D_23c7b4);
    if (r < 0)
        iprintf("ERROR : sceIoSetAsyncCallback(%x)\n", r);
    return sceIoReadAsync(fd, buf, size);
}

/* @implements 0x027bac us f_027bac
   WHAT IT DOES: Collects the result of an asynchronous file operation: mode 0 waits for it to
   finish, mode 1 only checks whether it has. Any other mode is an error and returns -1. */
int f_027bac(SceUID fd, int mode, long long *res)
{
    if (mode == 0)
        return sceIoWaitAsync(fd, res);
    if (mode == 1)
        return sceIoPollAsync(fd, res);
    f_126f1c("ERROR : Invalid mode");
    return -1;
}

/* @implements 0x027c00 us f_027c00
   WHAT IT DOES: Writing files to the disc is not possible; this reports it and returns -1. */
int f_027c00(SceUID fd, const void *buf, int size)
{
    f_126f1c("Cannot write!!");
    return -1;
}

/* @implements 0x027c24 us f_027c24
   WHAT IT DOES: Creates the callback that asynchronous reads report their completion to and
   remembers it with its argument. Returns the callback's id. */
SceUID f_027c24(const char *name, SceKernelCallbackFunction func, void *arg)
{
    D_23c7b0 = sceKernelCreateCallback(name, func, arg);
    if (D_23c7b0 < 0)
        iprintf("ERROR : sceKernelCreateCallback(%x)\n", D_23c7b0);
    D_23c7b4 = arg;
    return D_23c7b0;
}
