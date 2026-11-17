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
    unsigned short m16;
    char m18[14];
    int m32;
    char m36[8];
    signed char m44;
    char m45[3];
    int m48;
    int m52;
    int m56;
    int m60;
    unsigned short m64;
    unsigned short m66;
    int m68;
    int m72;
    unsigned short m76;
    char m78[2];
    int m80;
    int m84;
    int m88;
    int m92;
    int m96;
    int m100;
    int m104;
    int m108;
    int m112;
    int m116;
    int m120;
    int m124;
    int m128;
    int m132;
    int m136;
    int m140;
    char m144[8];
    int m152;
    char m156[20];
    float m176;
    char m180[4];
    char *m184;
    char *m188;
    char *m192;
};

struct SasSlot {
    unsigned char m0;
    char m1[3];
    int m4;
    char m8;
    unsigned char m9;
    unsigned char m10;
    unsigned char m11;
    unsigned char m12;
    unsigned char m13;
    char m14;
    unsigned char m15;
    char m16[8];
    int m24;
    short m28;
    char m30[6];
    float m36;
    short m40;
    short m42;
    float m44;
    char m48[4];
    float m52;
    short m56;
    short m58;
    short m60;
    short m62;
    short m64;
    short m66;
    short m68;
    short m70;
    short m72;
};

struct StreamQuery {
    char m0[20];
    short m20;
    char m22[26];
};

extern struct VolState D_291a48;
extern struct StreamChan D_291a54[];
extern struct StreamFile D_291980;
extern int D_291a0c;

int f_110630(int t, int level);
int f_111900(int ch, int a1);
int f_1112b0(int ch, int ms);
int f_111f98(int ch);
int sceIoLseekAsync(int fd, long long offset, int whence);
int f_110f58(int stream, const char *name, int id);
int f_1117d0(int stream, const char *name, int id, int fade);
int f_1113e4(int stream, void *info);
int f_111030(int stream);
int f_111774(int stream, float volume);
struct SasSlot *f_10d160(int a, int ch);
void f_10d228(int ch);
int f_110dbc(int prio, int *slot, int grp);
void f_110df0(int prio, int slot, int grp, int ch);
int f_10dfcc(short id, float *mix);
void f_110664(int pan, int *l, int *r);
void f_10d274(int ch);
int f_11b1a8(int ch, int a, int b);
int f_11af28(int ch, int l, int r, int sl, int sr);
int f_11af8c(int ch, int pitch);
int f_112b70(signed char nch, int pos, int n, int dst, int blk);
void *f_125c4c(int align, int size);
int f_112c98(int args, void *argp);
int f_113050(int args, void *argp);
int sceKernelCreateThread(const char *name, int (*entry)(int, void *), int prio, int stack, int attr, void *opt);
void *memcpy(void *d, const void *s, unsigned int n);
int sceKernelStartThread(int thid, unsigned int arglen, void *argp);
int sceKernelWaitThreadEnd(int thid, unsigned int *timeout);
int sceKernelDeleteThread(int thid);
int sceIoOpenAsync(const char *file, int flags, int mode);
void free(void *p);

/* @implements 0x11198c us f_11198c
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

/* @implements 0x111a1c us f_111a1c
   WHAT IT DOES: Resets the volume state to zero when the argument is zero. DRAFT. */
int f_111a1c(int a0)
{
    if (a0 == 0) {
        D_291a48.m0 = 0;
        D_291a48.m4 = 0;
        D_291a48.m8 = 0;
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

/* @implements 0x111b18 us f_111b18
   WHAT IT DOES: Opens the disc stream file name and resets its state; returns 0x80000000 if
   it is already open or fails to open. DRAFT. */
int f_111b18(int unused, const char *name, int a2, int a3)
{
    int fd;

    if (D_291980.m100 != 0)
        return 0x80000000;
    fd = sceIoOpenAsync(name, 1, 0);
    D_291980.m104 = fd;
    if (fd < 0)
        return 0x80000000;
    D_291980.m16 = 1;
    D_291980.m100 = 1;
    D_291980.m108 = a2;
    D_291980.m112 = a3;
    D_291980.m152 = -1;
    D_291980.m176 = 1.0f;
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
    D_291980.m140 = 0;
    return 0;
}

/* @draft 0x111be0 us f_111be0
   WHAT IT DOES: Sets up the two stream voices ch and ch + 1 (left and right, panned -64 and
   +64 from the stream's pan) from the disc stream's header: rate, format bytes, volume and
   pan, then starts them on their SAS voices with full pitch. */
void f_111be0(int ch)
{
    float mix[20];
    int slot = 0;
    int l, r;
    int i;
    int pan = -64;
    float rate;
    int base;

    for (i = 0; i < 2; i++) {
        struct SasSlot *v;

        f_110dbc(127, &slot, 0);
        v = f_10d160(0, ch);
        rate = (float)D_291980.m72 / 1000.0f;
        base = D_291980.m76;
        v->m42 = 0;
        v->m40 = base;
        v->m24 = 0;
        v->m11 = D_291980.m64;
        v->m44 = 1.0f;
        v->m12 = D_291980.m66;
        v->m15 = 1;
        v->m13 = D_291980.m68;
        v->m10 = 1;
        v->m36 = rate;
        v->m70 = base + pan;
        v->m56 = pan;
        v->m52 = D_291980.m176;
        v->m4 = 0;
        v->m58 = 0;
        v->m28 = 4096;
        v->m9 = 0;
        v->m72 = 4096;
        f_10dfcc(v->m11, mix);
        v->m68 = f_110630(v->m10, (int)(mix[0] * v->m36 * 255.0f)) << 4;
        f_110664(v->m70, &l, &r);
        v->m64 = 0;
        v->m66 = 0;
        l = l * v->m68 / 256;
        r = r * v->m68 / 256;
        v->m0 = 1;
        v->m60 = l;
        v->m62 = r;
        f_10d274(ch);
        f_110df0(127, slot, 0, ch);
        f_11b1a8(ch, 255, 8134);
        f_11af28(ch, l, r, 0, 0);
        f_11af8c(ch, 4096);
        pan += 128;
        ch++;
    }
}

/* @implements 0x111e04 us f_111e04
   WHAT IT DOES: The disc stream's step: in phase 2, once the two positions read by 0x111900
   are within 2000 of each other, starts the 2000 ms fade (0x1112b0) and moves to phase 3;
   before phase 3, a stream that is not playing is rewound to its start and its state reset.
   Then runs the stream's reader step (0x111f98) and returns its result. */
int f_111e04(void)
{
    if (D_291980.m128 == 2) {
        int a = f_111900(0, D_291980.m52);
        int b = f_111900(0, D_291980.m32);
        if (a - b < 2000) {
            f_1112b0(0, 2000);
            D_291980.m128++;
        }
    }
    if (D_291980.m128 >= 3 && D_291980.m16 == 0) {
        sceIoLseekAsync(D_291980.m104, D_291980.m108, 0);
        D_291980.m100 = 3;
        D_291980.m16 = 1;
        D_291980.m152 = -1;
        D_291980.m176 = 1.0f;
        D_291980.m112 = 0;
        D_291980.m84 = 0;
        D_291980.m96 = 0;
        D_291980.m88 = 0;
        D_291980.m92 = 0;
        D_291980.m116 = 0;
        D_291980.m124 = 0;
        D_291980.m128 = 0;
        D_291980.m32 = 0;
        D_291980.m136 = 0;
        D_291980.m132 = 0;
    }
    return f_111f98(0);
}

/* @implements 0x111f18 us f_111f18
   WHAT IT DOES: Sets the flag word of the two stream voices 29 and 30 (4096 when flag is zero,
   else 1) and updates each. DRAFT. */
void f_111f18(int unused, int flag)
{
    int i;

    for (i = 0; i < 2; i++) {
        struct SasSlot *v = f_10d160(0, i + 29);
        if (flag)
            v->m72 = 1;
        else
            v->m72 = 4096;
        f_10d228(i + 29);
    }
}

/* @draft 0x112aa8 us f_112aa8
   WHAT IT DOES: Writes n bytes into the disc stream buffer at its position, wrapping at 0x20000
   and advancing the position. DRAFT. */
int f_112aa8(int a0, int a1, int a2)
{
    struct StreamFile *f = &D_291980;
    int size = 0x20000;
    int pos = f->m84 + a1;
    int wrap = pos - size;
    int first = a1 - wrap;
    int res;

    if (size < pos) {
        res = 0;
        f_112b70(f->m44, a0, first, a2, f->m48);
        f_112b70(f->m44, 0, wrap, a2 + first, f->m48);
    } else {
        res = f_112b70(f->m44, a0, a1, a2, f->m48);
    }
    f->m84 = wrap;
    return res;
}

/* @draft 0x1131dc us f_1131dc
   WHAT IT DOES: Sets up the two ATRAC3 channels: their buffer sizes n0 and n1, every field
   cleared (full volume, no file), each one's data buffer (n + 2 bytes, none when n is not
   positive) and 32764-byte work buffer, then creates the play thread (0x112c98) and the read
   thread (0x113050).
   Remaining difference: the thread handles' stores reuse the table's high half from the entry
   block in a saved register (s3, 16 more bytes of frame); retail rebuilds it with lui after the
   loops. Statement order matches retail. */
int f_1131dc(int n0, int n1)
{
    struct StreamChan *c;
    int i;

    D_291a54[0].count = n0;
    D_291a54[1].count = n1;
    for (i = 0; i < 2; i++) {
        c = &D_291a54[i];
        c->state = 0;
        c->buf = 0;
        c->m12 = 0;
        c->m16 = 0;
        c->m20 = 0;
        c->m24 = f_110630(1, 255) << 7;
        c->m28 = 0;
        c->m32 = 0;
        c->m36 = 0;
        c->m40 = 0;
        c->m48 = 0;
        c->thread = 0;
        c->thread2 = 0;
        c->m44 = 0;
        c->m60 = -1;
    }
    for (i = 0; i < 2; i++) {
        c = &D_291a54[i];
        if (c->count > 0)
            c->buf = f_125c4c(64, c->count + 2);
        else
            c->buf = 0;
        c->m12 = (int)f_125c4c(64, 32764);
    }
    D_291a54[0].thread2 = sceKernelCreateThread("ATRAC3 play thread", f_112c98, 17, 0x10000, 0, 0);
    D_291a54[0].thread = sceKernelCreateThread("ATRAC3 read thread", f_113050, 112, 0x10000, 0, 0);
    return 0;
}

/* @draft 0x113328 us f_113328
   WHAT IT DOES: Frees channel 0's buffer and ends and deletes its two reader threads. DRAFT. */
int f_113328(void)
{
    if (D_291a54[0].count > 0)
        free(D_291a54[0].buf);
    sceKernelWaitThreadEnd(D_291a54[0].thread, 0);
    sceKernelDeleteThread(D_291a54[0].thread);
    sceKernelWaitThreadEnd(D_291a54[0].thread2, 0);
    sceKernelDeleteThread(D_291a54[0].thread2);
    return 0;
}

/* @implements 0x11338c us f_11338c
   WHAT IT DOES: Copies the name into channel ch and starts its reader thread (0x80000000 if
   the channel is busy). DRAFT. */
int f_11338c(int ch, const char *name)
{
    int n;

    if (D_291a54[ch].state != 0)
        return 0x80000000;
    n = strlen(name);
    memcpy(D_291a54[ch].name, name, n);
    D_291a54[ch].state = 1;
    D_291a54[ch].m48 = 0;
    return sceKernelStartThread(D_291a54[ch].thread, 4, &ch);
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

/* @implements 0x1134e8 us f_1134e8
   WHAT IT DOES: Copies the name into channel ch and starts its first reader thread with m48 = 1
   (0x80000000 if busy). DRAFT. */
int f_1134e8(int ch, const char *name)
{
    int n;

    if (D_291a54[ch].state != 0)
        return 0x80000000;
    n = strlen(name);
    memcpy(D_291a54[ch].name, name, n);
    D_291a54[ch].state = D_291a54[ch].m48 = 1;
    return sceKernelStartThread(D_291a54[ch].thread, 4, &ch);
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
