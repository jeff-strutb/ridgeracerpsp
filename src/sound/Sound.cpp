/* The sound system (retail 0x01c2cc to 0x01ca80): starting the sound library, the stack of
   sound banks loaded from the disc and pushed to the sound processor, and the eight volume
   settings. One global object holds it all. The static data's startup and shutdown entries
   close the object file (0x01ca30 to 0x01ca78). */

#include <stdio.h>
#include <stdlib.h>

extern "C" {
int f_10bdb8(int size, void *config);
void f_110e54(int);
void f_1114f0(int, int, int, int);
void f_111554(void);
void f_1112a8(int, int);
void f_1131dc(int, int);
int f_113644(void);
void f_114154(float);
int f_10bf1c(int);
float f_10e104(int channel);
void f_10ddac(int, int, float);
void f_10de18(int channel, float volume);
int f_10d334(void *hd, void *bd, unsigned short *id);
int f_114184(void *hd, void *bd, unsigned short *id);
void f_10d360(void);
int f_10d37c(unsigned short id, unsigned short *status);
void f_114210(int);
void f_10be80(int);
void f_00d354(char *buf, int size, const char *fmt, ...);
int f_027850(const char *name, int, int);
int f_02799c(int fd);
void f_027958(int fd, void *buf, int size);
void f_02793c(int fd);
}

extern char D_245178[];

/* A sound bank's header and sample data addresses, as the bank stack records them. */
struct CBankInfo {
    int m0;
    short m4;
    short m6;
    int m8;
    int m12;
    int m16;
    short m20;
    int m24;
    short m28;
    short m30;
    int m32;
};

class CSound {
public:
    ~CSound() {}
    void f_01c2cc(void *config);
    int f_01c458(void *hd, void *bd, int is3d, unsigned short *out);
    void f_01c578();
    void f_01c5dc();
    void f_01c618(CBankInfo *info);
    void f_01c648();
    void f_01c7a4(int which, int percent);
    float f_01c858(int which);
    void *f_01c8b0(const char *name);
    int f_01c96c(const char *name, int is3d, unsigned short *out);

    int count;
    int top;
    int state[64];
    void *hd[64];
    void *bd[64];
    float volume[8];
};

CSound D_23bb4c;
int D_23be74;
int D_23be78;

/* @implements 0x01c2cc us f_01c2cc
   WHAT IT DOES: Starts the sound library with the given configuration, or with the one in
   Sound/nus_config_ps2.txt when none is given (stopping with an error report if it fails),
   sets up the output, empties the bank stack and records the library's eight default
   volumes. */
void CSound::f_01c2cc(void *config)
{
    int r;

    if (config) {
        r = f_10bdb8(0x4b0000, config);
        if (r) {
            f_00d354(D_245178, 128, "NU Sound Init Error : %x \n", r);
            for (;;)
                ;
        }
    } else {
        config = f_01c8b0("Sound/nus_config_ps2.txt");
        r = f_10bdb8(0x4b0000, config);
        if (r) {
            f_00d354(D_245178, 128, "NU Sound Init Error : %x \n", r);
            for (;;)
                ;
        }
        free(config);
    }
    f_110e54(1);
    f_1114f0(0, 0x20000, 0x4000, 1);
    f_111554();
    f_1112a8(0, 0);
    f_1131dc(0, 0);
    f_113644();
    f_114154(1.0f);
    f_10bf1c(1);
    count = -10;
    top = -1;
    volume[0] = f_10e104(28);
    volume[1] = f_10e104(29);
    volume[2] = f_10e104(30);
    volume[3] = f_10e104(0);
    volume[4] = f_10e104(10);
    volume[5] = f_10e104(11);
    volume[6] = f_10e104(14);
    volume[7] = f_10e104(15);
    f_10ddac(1, 64, 0.8f);
}

/* @implements 0x01c458 us f_01c458
   WHAT IT DOES: Pushes a sound bank (header and sample data already in memory) to the sound
   processor, as a 3D bank when asked. On success it records the bank on the stack under the
   id the library gave it and hands the id back; otherwise it reports and returns the error. */
int CSound::f_01c458(void *h, void *b, int is3d, unsigned short *out)
{
    unsigned short id;
    int r;

    if (is3d == 1) {
        r = f_114184(h, b, &id);
        if (r != 0) {
            f_00d354(D_245178, 128, "Bank Puch Failed. code:%x\n", r);
            return r;
        }
    } else {
        r = f_10d334(h, b, &id);
        if (r != 0) {
            f_00d354(D_245178, 128, "Bank Puch Failed. code:%x\n", r);
            return r;
        }
    }
    state[id] = 1;
    hd[id] = h;
    bd[id] = b;
    top = id;
    count = id;
    f_00d354(D_245178, 128, "hd_addr:%x bd_addr:%x tmp:%d\n", h, b, id);
    if (out)
        *out = id;
    return 0;
}

/* @implements 0x01c578 us f_01c578
   WHAT IT DOES: Pops the most recently pushed sound bank, if any, and marks its slot free. */
void CSound::f_01c578()
{
    if (top >= 0) {
        f_10d360();
        f_00d354(D_245178, 128, "BankPop %d\n", top);
        state[top--] = 0;
    }
}

/* @implements 0x01c5dc us f_01c5dc
   WHAT IT DOES: Pops every sound bank. */
void CSound::f_01c5dc()
{
    while (top >= 0)
        f_01c578();
}

/* @implements 0x01c618 us f_01c618
   WHAT IT DOES: Clears a bank description. */
void CSound::f_01c618(CBankInfo *info)
{
    info->m0 = 0;
    info->m4 = 0;
    info->m6 = 0;
    info->m8 = 0;
    info->m12 = 0;
    info->m16 = 0;
    info->m20 = 0;
    info->m24 = 0;
    info->m28 = 0;
    info->m30 = 0;
    info->m32 = 0;
}

/* @implements 0x01c648 us f_01c648
   WHAT IT DOES: Called every frame: steps the library's update (on alternating channels), then
   checks every bank still being transferred to the sound processor. When all banks are in
   place it reports the transfer finished and stops checking. */
void CSound::f_01c648()
{
    int i, done;
    unsigned short status;

    if (D_23be74++ % 3 == 0) {
        f_114210(D_23be78 + 16);
        f_10be80(D_23be78 + 16);
    } else {
        f_114210(D_23be78 + 17);
        f_10be80(D_23be78 + 17);
    }
    D_23be78 = 0;
    for (i = 0, done = 0; i <= count; i++) {
        if (state[i] == 1) {
            f_10d37c(i, &status);
            if (status == 3) {
                done++;
                state[i] = 4;
            }
        } else {
            done++;
        }
    }
    if (done == count + 1) {
        f_00d354(D_245178, 128, "Bank Transfer End\n");
        count = -10;
    }
}

/* @implements 0x01c7a4 us f_01c7a4
   WHAT IT DOES: Sets one of the eight volumes to the given percentage of its default. */
void CSound::f_01c7a4(int which, int percent)
{
    float f = (float)percent / 100.0f;

    switch (which) {
    case 1:
        f_10de18(28, volume[0] * f);
        break;
    case 0:
        f_10de18(30, volume[2] * f);
        break;
    case 2:
        f_10de18(29, volume[1] * f);
        break;
    case 3:
        f_10de18(0, volume[3] * f);
        break;
    case 4:
        f_10de18(10, volume[4] * f);
        break;
    case 5:
        f_10de18(11, volume[5] * f);
        break;
    case 6:
        f_10de18(14, volume[6] * f);
        break;
    case 7:
        f_10de18(15, volume[7] * f);
        break;
    }
}

/* @implements 0x01c858 us f_01c858
   WHAT IT DOES: Returns the current level of one of the first three volumes. */
float CSound::f_01c858(int which)
{
    switch (which) {
    case 0:
        return f_10e104(30);
    case 1:
        return f_10e104(28);
    case 2:
        return f_10e104(29);
    }
}

/* @implements 0x01c8b0 us f_01c8b0
   WHAT IT DOES: Reads a whole file from the data folder into newly allocated memory and returns
   it; it stops with an error report if the file cannot be opened. */
void *CSound::f_01c8b0(const char *name)
{
    int fd = f_027850(name, 0, 2);
    if (fd >= 0) {
        f_00d354(D_245178, 128, "FileOpen:%s\n", name);
        int size = f_02799c(fd);
        void *buf = malloc(size);
        f_027958(fd, buf, size);
        f_02793c(fd);
        return buf;
    }
    f_00d354(D_245178, 128, "FileCan'tOpen:%s\n", name);
    for (;;)
        ;
}

/* @implements 0x01c96c us f_01c96c
   WHAT IT DOES: Loads a sound bank by name (the header from name.phd, or name.p3d for a 3D
   bank, and the samples from name.pbd) and pushes it to the sound processor. */
int CSound::f_01c96c(const char *name, int is3d, unsigned short *out)
{
    char h[80];
    char b[80];

    sprintf(b, "%s.pbd", name);
    if (is3d)
        sprintf(h, "%s.p3d", name);
    else
        sprintf(h, "%s.phd", name);
    void *hdata = f_01c8b0(h);
    return f_01c458(hdata, f_01c8b0(b), is3d, out);
}

/* @implements 0x01ca30 us __static_initialization_and_destruction_0
   WHAT IT DOES: The sound object needs no work at startup or shutdown. */

/* @implements 0x01ca38 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x01ca58 us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */
