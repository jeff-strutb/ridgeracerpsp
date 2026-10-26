/* The stream channel threads and volume state (retail 0x11198c to 0x11362c): the stream
   library's fade and volume step (D_291a48), the open and play wrappers, the file open of the
   disc stream (D_291980) and the per channel 128-byte records (D_291a54) that hold each
   channel's reader thread, buffer and state. Errors: 0x80000000 for a channel in the wrong
   state, 0x8000000a for a bad argument. */

#include <string.h>

struct VolState {
    float m0;
    float m4;
    int m8;
};

struct StreamChan {
    int state;
    int count;
    void *buf;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int thread;
    int thread2;
    int m60;
    char name[64];
};

struct StreamFile {
    char m0[16];
    short m16;
    char m18[14];
    int m32;
    char m36[8];
    signed char m44;
    char m45[3];
    int m48;
    char m52[32];
    int m84;
    int m88;
    int m92;
    int m96;
    int m100;
    int m104;
    int m108;
    int m112;
    int m116;
    char m120[4];
    int m124;
    int m128;
    int m132;
    int m136;
    int m140;
    char m144[8];
    int m152;
    char m156[20];
    float m176;
};

struct SasSlot {
    char m0[72];
    short m72;
};

struct StreamQuery {
    char m0[20];
    short m20;
    char m22[6];
};

extern struct VolState D_291a48;
extern struct StreamChan D_291a54[];
extern struct StreamFile D_291980;
extern int D_291a0c;

int f_110630(int t, int level);
int f_110f58(int stream, const char *name, int id);
int f_1117d0(int stream, const char *name, int id, int fade);
int f_1113e4(int stream, void *info);
int f_111030(int stream);
int f_111774(int stream, float volume);
struct SasSlot *f_10d160(int a, int ch);
void f_10d228(int ch);
int f_112b70(signed char a0, int a1, int a2, int a3, int a4);
int sceKernelStartThread(int thid, unsigned int arglen, void *argp);
int sceKernelWaitThreadEnd(int thid, unsigned int *timeout);
int sceKernelDeleteThread(int thid);
int sceIoOpenAsync(const char *file, int flags, int mode);
void free(void *p);

/* @draft 0x11198c us f_11198c
   WHAT IT DOES: Starts a stream fade step: reads the stream's length and sets the volume
   state from it. DRAFT: not yet compared. */
int f_11198c(int a0, int n, float vol)
{
    struct StreamQuery q;

    if (a0 != 0)
        return 0x8000000a;
    if (f_1113e4(0, &q) < 0)
        return 0x80000000;
    D_291a48.m8 = n;
    D_291a48.m0 = (float)q.m20 / 127.0f;
    D_291a48.m4 = (vol - D_291a48.m0) / (float)n;
    return 0;
}

/* @draft 0x111a1c us f_111a1c
   WHAT IT DOES: Resets the volume state to zero when the argument is zero. DRAFT. */
int f_111a1c(int a0)
{
    if (a0 == 0) {
        D_291a48.m0 = 0;
        D_291a48.m8 = 0;
        D_291a48.m4 = 0;
        return 0;
    }
    return 0x8000000a;
}

/* @implements 0x111a48 us f_111a48
   WHAT IT DOES: Advances the volume fade by n steps and stops the stream when none remain.
   DRAFT. */
void f_111a48(int n)
{
    if (D_291a48.m8 > 0) {
        D_291a48.m0 = D_291a48.m0 + D_291a48.m4 * (float)n;
        f_111774(0, D_291a48.m0);
        D_291a48.m8 = D_291a48.m8 - n;
        if (D_291a48.m8 <= 0)
            f_111030(0);
    }
}

/* @implements 0x111acc us f_111acc
   WHAT IT DOES: Starts stream stream from the named pack with id (passes through to 0x110f58).
   DRAFT. */
int f_111acc(int stream, const char *name, int id)
{
    return f_110f58(stream, name, id);
}

/* @implements 0x111ae8 us f_111ae8
   WHAT IT DOES: Starts stream stream from the named pack with id and a fade (0x1117d0). DRAFT. */
int f_111ae8(int stream, const char *name, int id, int fade)
{
    return f_1117d0(stream, name, id, fade);
}

/* @implements 0x111b04 us f_111b04
   WHAT IT DOES: Does nothing. DRAFT. */
void f_111b04(void)
{
}

/* @implements 0x111b0c us f_111b0c
   WHAT IT DOES: Returns the UMD check value D_291a0c. DRAFT. */
int f_111b0c(void)
{
    return D_291a0c;
}

/* @draft 0x111b18 us f_111b18
   WHAT IT DOES: Opens the disc stream file name and resets its state; returns 0x80000000 if
   it is already open or fails to open. DRAFT. */
int f_111b18(int unused, const char *name, int a2, int a3)
{
    int r = 0x80000000;
    int fd;

    if (D_291980.m100 == 0) {
        fd = sceIoOpenAsync(name, 1, 0);
        D_291980.m104 = fd;
        if (fd >= 0) {
            D_291980.m16 = 1;
            D_291980.m100 = 1;
            D_291980.m108 = a2;
            D_291980.m112 = a3;
            D_291980.m152 = -1;
            D_291980.m176 = 1.0f;
            D_291980.m140 = 0;
            D_291980.m84 = 0;
            D_291980.m96 = 0;
            D_291980.m88 = 0;
            D_291980.m92 = 0;
            D_291980.m116 = 0;
            D_291980.m124 = 0;
            D_291980.m128 = 0;
            D_291980.m32 = 0;
            D_291980.m132 = 0;
            D_291980.m136 = 0;
            r = 0;
        }
    }
    return r;
}

/* @draft 0x111f18 us f_111f18
   WHAT IT DOES: Sets the flag word of the two stream voices 29 and 30 (4096 when flag is zero,
   else 1) and updates each. DRAFT. */
void f_111f18(int unused, int flag)
{
    int i;

    for (i = 0; i < 2; i++) {
        struct SasSlot *v = f_10d160(0, i + 29);
        if (flag == 0)
            v->m72 = 4096;
        else
            v->m72 = 1;
        f_10d228(i + 29);
    }
}

/* @draft 0x112aa8 us f_112aa8
   WHAT IT DOES: Writes n bytes into the disc stream buffer at its position, wrapping at 0x20000
   and advancing the position. DRAFT. */
int f_112aa8(int a0, int a1, int a2)
{
    int pos = D_291980.m84 + a1;
    int wrap = pos - 0x20000;
    int first = a1 - wrap;
    int res;

    if (0x20000 < pos) {
        res = 0;
        f_112b70(D_291980.m44, a0, first, a2, D_291980.m48);
        f_112b70(D_291980.m44, 0, wrap, a2 + first, D_291980.m48);
    } else {
        res = f_112b70(D_291980.m44, a0, a1, a2, D_291980.m48);
    }
    D_291980.m84 = wrap;
    return res;
}

/* @draft 0x113328 us f_113328
   WHAT IT DOES: Frees channel 0's buffer and ends and deletes its two reader threads. DRAFT. */
int f_113328(void)
{
    struct StreamChan *c = &D_291a54[0];

    if (c->count > 0)
        free(c->buf);
    sceKernelWaitThreadEnd(c->thread, 0);
    sceKernelDeleteThread(c->thread);
    sceKernelWaitThreadEnd(c->thread2, 0);
    sceKernelDeleteThread(c->thread2);
    return 0;
}

/* @draft 0x11338c us f_11338c
   WHAT IT DOES: Copies the name into channel ch and starts its reader thread (0x80000000 if
   the channel is busy). DRAFT. */
int f_11338c(int ch, const char *name)
{
    struct StreamChan *c = &D_291a54[ch];

    if (c->state != 0)
        return 0x80000000;
    memcpy(c->name, name, strlen(name));
    c->state = 1;
    c->m48 = 0;
    return sceKernelStartThread(c->thread, 4, &ch);
}

/* @implements 0x113424 us f_113424
   WHAT IT DOES: Starts channel ch's second reader thread with its buffer and count. DRAFT. */
int f_113424(int ch, void *buf, int n)
{
    struct StreamChan *c = &D_291a54[ch];

    if (c->state != 0)
        return 0x80000000;
    c->state = 1;
    c->buf = buf;
    c->m36 = n;
    c->m20 = 0;
    c->m48 = 0;
    return sceKernelStartThread(c->thread2, 4, &ch);
}

/* @implements 0x113488 us f_113488
   WHAT IT DOES: Marks channel ch as done (state 3 gives 0 and sets m28), else 0x80000000. DRAFT. */
int f_113488(int ch)
{
    struct StreamChan *c = &D_291a54[ch];

    if (c->state == 3) {
        c->m28 = 1;
        return 0;
    }
    return 0x80000000;
}

/* @implements 0x1134bc us f_1134bc
   WHAT IT DOES: Stores a value below 2 in channel ch's m40, else 0x80000000. DRAFT. */
int f_1134bc(int ch, unsigned int v)
{
    struct StreamChan *c = &D_291a54[ch];

    if (v >= 2)
        return 0x80000000;
    c->m40 = v;
    return 0;
}

/* @draft 0x1134e8 us f_1134e8
   WHAT IT DOES: Copies the name into channel ch and starts its first reader thread with m48 = 1
   (0x80000000 if busy). DRAFT. */
int f_1134e8(int ch, const char *name)
{
    struct StreamChan *c = &D_291a54[ch];

    if (c->state != 0)
        return 0x80000000;
    memcpy(c->name, name, strlen(name));
    c->state = 1;
    c->m48 = 1;
    return sceKernelStartThread(c->thread, 4, &ch);
}

/* @implements 0x113580 us f_113580
   WHAT IT DOES: Sets m48 to 2 when the state is 1 or 2, else 0x80000000. DRAFT. */
int f_113580(int ch)
{
    struct StreamChan *c = &D_291a54[ch];

    if ((unsigned int)(c->state - 1) < 2) {
        c->m48 = 2;
        return 0;
    }
    return 0x80000000;
}

/* @implements 0x1135b8 us f_1135b8
   WHAT IT DOES: Converts a float level to a voice level (0x110630) and stores it shifted in
   m24. DRAFT. */
int f_1135b8(int ch, float x)
{
    struct StreamChan *c = &D_291a54[ch];

    c->m24 = f_110630(1, (short)(int)(x * 255.0f)) << 7;
    return 0;
}

/* @implements 0x113610 us f_113610
   WHAT IT DOES: Stores a value in channel ch's m60. DRAFT. */
int f_113610(int ch, int v)
{
    D_291a54[ch].m60 = v;
    return 0;
}

/* @implements 0x11362c us f_11362c
   WHAT IT DOES: Returns channel ch's state. DRAFT. */
int f_11362c(int ch)
{
    return D_291a54[ch].state;
}
