/* The SAS sound voice player (retail 0x10ed74 to 0x110790): starts sound table entries on
   SAS voices with their random pitch, pan and volume variations, bus mix and send levels,
   fades a playing sound's volume over a number of ticks, runs the SasCore output thread with
   its two triple buffers, and keeps the pan and level tables. Sounds that cannot start yet go
   to the delay queue (0x10e788). Errors: 0x8000001a for a bad sound handle, 0x80000010/11
   for a bad bank or index, 0x80000017/18 for a sound rejected by its volume range or its
   chance. */

typedef struct SoundReq {
    int ch;                 /* the voice it plays on */
    unsigned short idx;
    unsigned short bank;
    int key;
    int m12;
    float vol;
    short m20;
    short pad22;
    int delay;
    short m28;
    short m30;
    int m32;
} SoundReq;

/* A sound table entry (0x10daa4). */
typedef struct SoundEntry {
    unsigned char m0[2];
    unsigned char flags;        /* bit 2: m15/m32 */
    signed char bus;
    unsigned char m4;
    unsigned char chance;       /* percent */
    unsigned char rnd;          /* random modes: pitch bits 0-1, volume 2-3, pan 4-5 */
    unsigned char m7;
    short m8;
    unsigned short m10;
    short m12;
    short m14;
    unsigned char bus0;
    unsigned char bus1;
    unsigned char send;
    unsigned char m19;
    int m20;
    unsigned short m24;
    unsigned short m26;
    short pitchRange;
    unsigned char m30;
    signed char volRange;
    signed char m32;
    signed char m33;
    signed char panRange;
    signed char m35;
    float m36;
    float minVol;
    float maxVol;
    unsigned short m48;
    unsigned short m50;
    int m52;
    int m56;
    int m60;
} SoundEntry;

/* A SAS voice's state (0x10d160). */
typedef struct SasVoice {
    unsigned char on;
    char m1[3];
    int m4;
    char m8;
    unsigned char bus;
    unsigned char m10;
    unsigned char bus0;
    unsigned char bus1;
    unsigned char send;
    char m14;
    unsigned char m15;
    char m16[8];
    float m24;
    unsigned short m28;
    short pad30;
    int key;
    float vol;
    short pan;
    unsigned short pitch;
    float m44;
    float m48;
    float m52;
    short m56;
    short m58;
    unsigned short l;
    unsigned short r;
    unsigned short sl;
    unsigned short sr;
    short pad68;
    short pan2;
    unsigned short m72;
} SasVoice;

/* A bus chain mix (0x10dfcc). */
typedef struct BusMix {
    float vol;
    short pan;
    unsigned short n;
    unsigned char fx[32];
    unsigned char bus[32];
} BusMix;

typedef struct SoundVoice {
    int id;
    int kind;
    int m8;
} SoundVoice;

/* A volume fade (16 bytes, 32 of them). */
typedef struct Fade {
    float step;
    int count;
    int stop;               /* stop the sound when the fade ends */
    SoundReq *req;
} Fade;

extern Fade D_281498[32];
extern volatile int D_2816a0;            /* the SasCore thread runs */
extern int D_2816a4;            /* its thread id */
extern int D_2816a8[2];         /* the two output buffers */
extern int D_281698;
extern unsigned int D_28169c;   /* random seed */
extern int D_2816b0[];
extern int D_1d77b4;            /* next request key */
extern unsigned char D_1d77b8[][256];
extern unsigned char D_1d79b8[];
extern int D_281eb4;

int f_10c09c(unsigned short bank, unsigned short idx, short a, short b, SoundReq *r, float v);
int f_10c1f8(unsigned short bank, unsigned short idx, short a, short b, SoundReq *r, float v);
int f_10c5a4(SoundReq *r);
float f_10c698(SoundReq *r);
int f_10c764(SoundReq *r, float v);
int f_10d0a4(void);
int f_10d0d0(void);
int f_10d140(void);
SasVoice *f_10d160(int a, int ch);
int f_10d1b8(int a);
void f_10d204(void);
int f_10d228(int ch);
int f_10d250(void);
int f_10d274(int ch);
int f_10d2c4(void);
int f_10d2e8(int ch);
int f_10d310(void);
int f_10da30(unsigned short bank);
unsigned int f_10da58(unsigned short bank);
SoundEntry *f_10daa4(unsigned short bank, unsigned short idx);
int f_10dd90(int i);
int f_10dfcc(short id, BusMix *m);
int f_10eaec(SoundReq *r);
int f_10eb28(SoundReq *q, SoundVoice *v, int flag);
int f_110dbc(int a, int *out, int bus);
int f_110df0(int a, int b, int bus, int ch);
int f_115304(unsigned char i);
int f_11529c(void);
int f_119130(void);
int f_119dc8(int a, int b);
int f_119ea0(int a, int b);
int f_119f80(int a, int b, int c, int d);
int f_11aeb0(int ch);
int f_11af28(int ch, int l, int r, int sl, int sr);
int f_11af8c(int ch, int pitch);
int f_11afdc(int ch, int a, int b, int c);
int f_11b1a8(int ch, int a, int b);
int f_11b394(int a);
int f_11b3ec(void);
int f_125c4c(int align, int size);
float powf(float x, float y);
void free(void *p);
int sceKernelCreateThread(const char *name, int (*entry)(int, void *), int prio, int stack, int attr, void *opt);
int sceKernelStartThread(int id, int len, void *arg);
int sceKernelWaitThreadEnd(int id, void *timeout);
int sceKernelDeleteThread(int id);
int sceKernelExitThread(int status);

int f_10ee74(int n, SoundReq *r, float target);
int f_10ef34(unsigned short bank, unsigned short idx, int n, SoundReq *r, float vol);
int f_10f018(unsigned short bank, unsigned short idx, short a, short b, float vol, int n, SoundReq *r);
int f_10f0a8(unsigned short bank, unsigned short idx, int n, SoundReq *r, float vol);
int f_10f138(unsigned short bank, unsigned short idx, short a, short b, float vol, int n, SoundReq *r);
int f_10f1c4(int n, SoundReq *r);
int f_10f288(SoundReq *r);
void f_10f2d4(int dt);
int f_10f4c4(int args, void *argp);
unsigned int f_110364(void);
void f_10f628(SoundReq *r, int ch, int bank, unsigned short idx, float vol, short a, short b);
void f_10f6e0(SoundReq *r, int ch, int bank, unsigned short idx, float vol, short a, short b);
void f_10f73c(SoundEntry *e, int *vol, short *pan, short *pitch);
int f_10f990(unsigned short bank, unsigned short idx, int flag, SoundReq *q);
float f_10f9dc(short cents);
int f_10fd4c(unsigned short bank, unsigned short idx, short a, short b, SoundReq *q, int mode, float vol, int bus, float gain);
int f_11041c(unsigned short bank, unsigned short idx, SoundVoice *v);
int f_1105dc(int pan);
int f_110630(int t, int level);
void f_110664(int pan, int *l, int *r);

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* A request handle that names a voice. */
static __inline__ int Valid(SoundReq *r)
{
    return r && r->ch < 32;
}

/* @implements 0x10ed74 us f_10ed74
   WHAT IT DOES: Fades sound r's volume to a target over n ticks (0x10ee74). */
int f_10ed74(int n, SoundReq *r, float target)
{
    return f_10ee74(n, r, target);
}

/* @implements 0x10ed90 us f_10ed90
   WHAT IT DOES: Starts a sound with a fade in over n ticks (0x10ef34). */
int f_10ed90(unsigned short bank, unsigned short idx, int n, SoundReq *r, float vol)
{
    return f_10ef34(bank, idx, n, r, vol);
}

/* @implements 0x10edb0 us f_10edb0
   WHAT IT DOES: Starts a sound with settings a and b and a fade in (0x10f018). */
int f_10edb0(unsigned short bank, unsigned short idx, short a, short b, float vol, int n, SoundReq *r)
{
    return f_10f018(bank, idx, a, b, vol, n, r);
}

/* @implements 0x10edd8 us f_10edd8
   WHAT IT DOES: Starts a sound the second way with a fade in (0x10f0a8). */
int f_10edd8(unsigned short bank, unsigned short idx, int n, SoundReq *r, float vol)
{
    return f_10f0a8(bank, idx, n, r, vol);
}

/* @implements 0x10edf8 us f_10edf8
   WHAT IT DOES: Starts a sound the second way with settings a and b and a fade in
   (0x10f138). */
int f_10edf8(unsigned short bank, unsigned short idx, short a, short b, float vol, int n, SoundReq *r)
{
    return f_10f138(bank, idx, a, b, vol, n, r);
}

/* @implements 0x10ee20 us f_10ee20
   WHAT IT DOES: Fades sound r out over n ticks (0x10f1c4). */
int f_10ee20(int n, SoundReq *r)
{
    return f_10f1c4(n, r);
}

/* @implements 0x10ee3c us f_10ee3c
   WHAT IT DOES: Cancels sound r's fade (0x10f288). */
int f_10ee3c(SoundReq *r)
{
    return f_10f288(r);
}

/* @implements 0x10ee58 us f_10ee58
   WHAT IT DOES: Advances the fades by dt ticks (0x10f2d4). */
void f_10ee58(int dt)
{
    f_10f2d4(dt);
}

/* @draft 0x10ee74 us f_10ee74
   WHAT IT DOES: Fades sound r's volume from where it is to a target over n ticks.
   DRAFT: control flow and stores match; retail tests and passes the incoming a1 (beqz a1,
   lw 0(a1), move a0,a1) before r is in s0, keeps the result in a2, and has n in s2 and the
   fade table base in s1 (here the other way round). */
int f_10ee74(int n, SoundReq *r, float target)
{
    int ret = 0x8000001a;

    if (r) {
        Fade *f = &D_281498[r->ch];
        if (r->ch < 32) {
            f->step = (target - f_10c698(r)) / (float)n;
            D_281498[r->ch].count = n;
            D_281498[r->ch].req = r;
            D_281498[r->ch].stop = 0;
            ret = 0;
        }
    }
    return ret;
}

/* @implements 0x10ef34 us f_10ef34
   WHAT IT DOES: Starts a sound (0x10c09c) and fades it in from silence to vol over n ticks;
   with n 0 it starts at vol. 0x80000000 for a negative n. */
int f_10ef34(unsigned short bank, unsigned short idx, int n, SoundReq *r, float vol)
{
    int ret;

    if (n < 0)
        return 0x80000000;
    if (n == 0) {
        ret = f_10c09c(bank, idx, 0, 0, r, vol);
        D_281498[r->ch].step = vol;
    } else {
        ret = f_10c09c(bank, idx, 0, 0, r, 0.0f);
        D_281498[r->ch].step = vol / (float)n;
    }
    D_281498[r->ch].count = n;
    D_281498[r->ch].req = r;
    D_281498[r->ch].stop = 0;
    return ret;
}

/* @implements 0x10f018 us f_10f018
   WHAT IT DOES: Starts a sound with settings a and b (0x10c09c) silent and fades it in to vol
   over n ticks. */
int f_10f018(unsigned short bank, unsigned short idx, short a, short b, float vol, int n, SoundReq *r)
{
    int ret = f_10c09c(bank, idx, a, b, r, 0.0f);

    D_281498[r->ch].step = vol / (float)n;
    D_281498[r->ch].count = n;
    D_281498[r->ch].req = r;
    D_281498[r->ch].stop = 0;
    return ret;
}

/* @implements 0x10f0a8 us f_10f0a8
   WHAT IT DOES: Starts a sound the second way (0x10c1f8) silent and fades it in to vol over
   n ticks. */
int f_10f0a8(unsigned short bank, unsigned short idx, int n, SoundReq *r, float vol)
{
    int ret = f_10c1f8(bank, idx, 0, 0, r, 0.0f);

    D_281498[r->ch].step = vol / (float)n;
    D_281498[r->ch].count = n;
    D_281498[r->ch].req = r;
    D_281498[r->ch].stop = 0;
    return ret;
}

/* @implements 0x10f138 us f_10f138
   WHAT IT DOES: Starts a sound the second way with settings a and b (0x10c1f8) and fades its
   volume by vol / n per tick over n ticks. */
int f_10f138(unsigned short bank, unsigned short idx, short a, short b, float vol, int n, SoundReq *r)
{
    int ret = f_10c1f8(bank, idx, a, b, r, vol);

    D_281498[r->ch].step = vol / (float)n;
    D_281498[r->ch].count = n;
    D_281498[r->ch].req = r;
    D_281498[r->ch].stop = 0;
    return ret;
}

/* @draft 0x10f1c4 us f_10f1c4
   WHAT IT DOES: Fades sound r out to silence over n ticks and stops it at the end; a sound
   that is already silent is stopped (0x10c5a4) at once.
   DRAFT: 15 words in the head differ: as in 0x10ee74, retail uses the incoming a1 for the
   first tests and the call and keeps the result in a2 (here a1). */
int f_10f1c4(int n, SoundReq *r)
{
    int ret = 0x8000001a;
    float step;

    if (Valid(r)) {
        step = -f_10c698(r) / (float)n;
        D_281498[r->ch].step = step;
        if (step >= 0.0f) {
            f_10c5a4(r);
            ret = 0;
        } else {
            D_281498[r->ch].count = n;
            D_281498[r->ch].req = r;
            D_281498[r->ch].stop = 1;
            ret = 0;
        }
    }
    return ret;
}

/* @implements 0x10f288 us f_10f288
   WHAT IT DOES: Cancels sound r's fade. */
int f_10f288(SoundReq *r)
{
    int ret = 0x8000001a;

    if (r && r->ch < 32) {
        D_281498[r->ch].step = 0;
        D_281498[r->ch].count = 0;
        D_281498[r->ch].stop = 0;
        ret = 0;
    }
    return ret;
}

/* @implements 0x10f2d4 us f_10f2d4
   WHAT IT DOES: Steps every running fade by dt ticks, setting its sound's volume (0x10c764);
   a fade that runs out stops its sound if it was a fade out. */
void f_10f2d4(int dt)
{
    Fade *f = D_281498;
    int i;

    for (i = 31; i >= 0; i--, f++) {
        if (f->count > 0 && f->req) {
            f_10c764(f->req, f->req->vol + f->step * (float)dt);
            f->count -= dt;
            if (f->count <= 0 && f->stop)
                f_10c5a4(f->req);
        }
    }
}

/* @implements 0x10f378 us f_10f378
   WHAT IT DOES: Starts the SAS sound system: the SAS core and its voices, the two output
   buffers and the SasCore thread. Returns the first failure's code, else 0. */
int f_10f378(void)
{
    int r;

    r = f_119130();
    if (r)
        return r;
    f_119ea0(0, 0);
    f_119dc8(0, 768);
    f_119dc8(1, 2048);
    f_119dc8(2, 2048);
    r = f_11b3ec();
    if (r)
        return r;
    f_11529c();
    f_10d0a4();
    D_2816a8[0] = f_125c4c(64, 3072);
    D_2816a8[1] = f_125c4c(64, 3072);
    D_2816a0 = 1;
    D_2816a4 = sceKernelCreateThread("SasCore thread", f_10f4c4, 16, 0x10000, 0, 0);
    sceKernelStartThread(D_2816a4, 0, 0);
    return 0;
}

/* @implements 0x10f470 us f_10f470
   WHAT IT DOES: Stops the SasCore thread, waits for it and frees the output buffers. */
void f_10f470(void)
{
    D_2816a0 = 0;
    sceKernelWaitThreadEnd(D_2816a4, 0);
    sceKernelDeleteThread(D_2816a4);
    free((void *)D_2816a8[0]);
    free((void *)D_2816a8[1]);
}

/* @implements 0x10f4c4 us f_10f4c4
   WHAT IT DOES: The SasCore thread: while running, renders the next 1 KB part of the current
   output buffer and updates the voices; after three parts it outputs the buffer, switches
   to the other one and counts 768 more samples. */
int f_10f4c4(int args, void *argp)
{
    volatile int buf = 0;
    volatile int part = 0;

    while (D_2816a0) {
        f_11b394(D_2816a8[buf] + part * 1024);
        f_10d204();
        part++;
        if (part >= 3) {
            part = 0;
            f_119f80(0, 0x8000, 0x8000, D_2816a8[buf]);
            buf ^= 1;
            D_281698 += 768;
        }
    }
    sceKernelExitThread(0);
    return 0;
}

/* @implements 0x10f5ac us f_10f5ac
   WHAT IT DOES: The per-frame sound update: applies bus 1's FX when it changed, updates the
   voices, and returns the last step's result when negative, else 0. */
int f_10f5ac(void)
{
    int r;

    if (f_10dd90(1))
        f_115304(1);
    f_10d250();
    f_10d2c4();
    f_10d310();
    r = f_10d140();
    return MIN(r, 0);
}

/* @implements 0x10f608 us f_10f608
   WHAT IT DOES: Stops voice ch (0x10d2e8) and returns 0. */
int f_10f608(int ch)
{
    f_10d2e8(ch);
    return 0;
}

/* @implements 0x10f628 us f_10f628
   WHAT IT DOES: Fills a sound request from the sound table entry and the start settings. */
void f_10f628(SoundReq *r, int ch, int bank, unsigned short idx, float vol, short a, short b)
{
    SoundEntry *e = f_10daa4(bank, idx);

    r->idx = idx;
    r->bank = bank;
    r->ch = ch;
    r->m12 = e->m10;
    r->vol = vol;
    r->m20 = a;
    r->m28 = b;
    r->delay = e->m20;
    r->m30 = e->bus0;
    r->m32 = (e->flags >> 2) & 1;
}

/* @implements 0x10f6e0 us f_10f6e0
   WHAT IT DOES: Fills a sound request (0x10f628) and gives it the next request key, which
   wraps from 0x7fffffff to 1. */
void f_10f6e0(SoundReq *r, int ch, int bank, unsigned short idx, float vol, short a, short b)
{
    f_10f628(r, ch, bank, idx, vol, a, b);
    r->key = D_1d77b4;
    D_1d77b4++;
    if (D_1d77b4 == 0x7fffffff)
        D_1d77b4 = 1;
}

/* @implements 0x10f73c us f_10f73c
   WHAT IT DOES: Draws the random variations a sound table entry asks for: pitch, volume and
   pan each either both ways, down only or up only within the entry's range. */
void f_10f73c(SoundEntry *e, int *vol, short *pan, short *pitch)
{
    if (e->rnd & 3) switch (e->rnd & 3) {
    case 1:
        *pitch = f_110364() % (e->pitchRange * 2) - e->pitchRange;
        break;
    case 2:
        *pitch = -(f_110364() % e->pitchRange);
        break;
    case 3:
        *pitch = f_110364() % e->pitchRange;
        break;
    }
    if (e->rnd & 0x0c) switch ((e->rnd & 0x0c) >> 2) {
    case 1:
        *vol = f_110364() % (e->volRange * 2) - e->volRange;
        break;
    case 2:
        *vol = -(f_110364() % e->volRange);
        break;
    case 3:
        *vol = f_110364() % e->volRange;
        break;
    }
    if (e->rnd & 0x30) switch ((e->rnd & 0x30) >> 4) {
    case 1:
        *pan = f_110364() % (e->panRange * 2) - e->panRange;
        break;
    case 2:
        *pan = -(f_110364() % e->panRange);
        break;
    case 3:
        *pan = f_110364() % e->panRange;
        break;
    }
}

/* @implements 0x10f990 us f_10f990
   WHAT IT DOES: Reads the sound's voice settings (0x11041c) and starts request q on them now
   (0x10eb28). */
int f_10f990(unsigned short bank, unsigned short idx, int flag, SoundReq *q)
{
    SoundVoice v;

    f_11041c(bank, idx, &v);
    return f_10eb28(q, &v, flag);
}

/* @implements 0x10f9dc us f_10f9dc
   WHAT IT DOES: The pitch ratio for a pitch in cents: 1 at 0, 4 from 2400 up, else
   2 ^ (cents / 1200). */
float f_10f9dc(short cents)
{
    if (cents == 0)
        return 1.0f;
    if (cents >= 2400)
        return 4.0f;
    return powf(2.0f, cents / 1200.0f);
}

/* @implements 0x10fa38 us f_10fa38
   WHAT IT DOES: Sets voice ch's volume, setting a and pitch offset, and its pitch word from
   the base pitch and the offset. */
int f_10fa38(int ch, short a, short pitch, float vol)
{
    SasVoice *v = f_10d160(0, ch);
    float base;

    v->m52 = vol;
    v->m56 = a;
    v->m58 = pitch;
    base = v->m28;
    v->m72 = (int)(base * f_10f9dc(pitch + v->pitch));
    return f_10d228(ch);
}

/* @implements 0x10fae0 us f_10fae0
   WHAT IT DOES: Sets voice ch's volume. */
void f_10fae0(int ch, float vol)
{
    f_10d160(0, ch)->m52 = vol;
}

/* @implements 0x10fb10 us f_10fb10
   WHAT IT DOES: Sets voice ch's setting a. */
void f_10fb10(int ch, short a)
{
    f_10d160(0, ch)->m56 = a;
}

/* @implements 0x10fb44 us f_10fb44
   WHAT IT DOES: Sets voice ch's pitch offset and recomputes its pitch word. */
int f_10fb44(int ch, short pitch)
{
    SasVoice *v = f_10d160(0, ch);
    float base;

    v->m58 = pitch;
    base = v->m28;
    base = base * v->m48;
    v->m72 = (unsigned int)(base * f_10f9dc(pitch + v->pitch));
    return f_10d228(ch);
}

/* @implements 0x10fc04 us f_10fc04
   WHAT IT DOES: Sets voice ch's pitch scale and recomputes its pitch word. */
int f_10fc04(int ch, float scale)
{
    SasVoice *v = f_10d160(0, ch);
    float base;

    v->m48 = scale;
    base = v->m28;
    v->m72 = (unsigned int)(base * scale * f_10f9dc(v->pitch + v->m58));
    return f_10d228(ch);
}

/* @implements 0x10fcbc us f_10fcbc
   WHAT IT DOES: Resets the voice states and sets up all 31 SAS voices silent on the shared
   1 KB buffer. */
void f_10fcbc(void)
{
    int i;

    f_10d0d0();
    for (i = 0; i < 31; i++) {
        f_11afdc(i, (int)D_2816b0, 1024, 0);
        f_11b1a8(i, 255, 8134);
        f_11af28(i, 0, 0, 0, 0);
        f_11af8c(i, 4096);
        f_11aeb0(i);
    }
}

/* @implements 0x10fd4c us f_10fd4c
   WHAT IT DOES: Starts a sound table entry on a free voice. A sound outside its volume
   range or failing its chance is rejected; one with a delay is queued; otherwise the voice
   gets the entry's settings with their random variations, the volume and pan of its two
   buses, its level, pan and send levels and its pitch, and is keyed on. Returns 0 or an
   error. */
int f_10fd4c(unsigned short bank, unsigned short idx, short a, short b, SoundReq *q, int mode, float vol, int bus, float gain)
{
    BusMix m0, m1;
    short pan, pitch;
    int tmp;
    int dvol;
    int l, r;
    SoundEntry *e = f_10daa4(bank, idx);
    int ch = f_10d1b8(0);
    int res;
    int queued;
    int sr, sl;
    int g;
    float x;
    SasVoice *v;

    if (ch >= 0) {
        if (e == 0)
            return 0x80000000;
        if (!((e->maxVol != 1.0f && e->maxVol < vol) || (e->minVol != 0.0f && vol < e->minVol))) {
            if (f_110364() % 100 < e->chance) {
                if (bus == -1)
                    bus = e->bus;
                res = f_110dbc(e->m4, &tmp, bus);
                if (res >= 0) {
                    pitch = 0;
                    pan = 0;
                    dvol = 0;
                    if (e->rnd)
                        f_10f73c(e, &dvol, &pan, &pitch);
                    if (mode == 1) {
                        int key = q->key;
                        int delay = q->delay;
                        f_10f6e0(q, ch, bank, idx, vol, a, b);
                        q->key = key;
                        q->delay = delay;
                    } else {
                        f_10f6e0(q, ch, bank, idx, vol, a, b);
                    }
                    queued = f_10eaec(q);
                    if (queued != 0x80000000)
                        return 0;

                    v = f_10d160(0, ch);
                    v->vol = (e->m30 + dvol) / 127.0f;
                    v->pan = e->m32 + pan;
                    v->pitch = e->m26 + pitch;
                    v->bus0 = e->bus0;
                    v->bus1 = e->bus1;
                    v->send = e->send;
                    v->m15 = (e->flags >> 2) & 1;
                    v->m4 = 0;
                    v->m10 = e->m7;
                    v->m56 = a;
                    v->m58 = b;
                    v->m24 = e->m36;
                    v->m44 = gain;
                    v->m48 = 1.0f;
                    v->m28 = e->m24;
                    v->m52 = vol;
                    v->bus = bus;
                    if ((res = f_10dfcc(e->bus0, &m0)) >= 0 && (res = f_10dfcc(e->bus1, &m1)) >= 0) {
                        x = v->m28;
                        v->m72 = (unsigned int)(x * f_10f9dc(b + v->pitch));
                        v->pan2 = a + v->pan + m0.pan - 64;
                        sr = 0;
                        sl = 0;
                        g = f_110630(e->m7, (int)(m0.vol * v->m44 * (vol * v->vol + v->m24) * 255.0f)) << 4;
                        f_110664(v->pan2, &l, &r);
                        l = l * g / 256;
                        r = r * g / 256;
                        if ((unsigned char)(e->bus1 - 1) < 2) {
                            sl = (float)l * m1.vol * e->send / 127.0f;
                            sr = (float)r * m1.vol * e->send / 127.0f;
                        }
                        v->l = l;
                        v->r = r;
                        v->sl = sl;
                        v->sr = sr;
                        f_11afdc(ch, e->m52 + e->m60, e->m56, 1);
                        f_11b1a8(ch, e->m48, e->m50);
                        f_11af28(ch, l, r, sl, sr);
                        f_11af8c(ch, v->m72);
                        v->on = 1;
                        v->key = q->key;
                        f_10d274(ch);
                        f_110df0(e->m4, tmp, bus, ch);
                        f_10f990(bank, idx, 1, q);
                        return 0;
                    } else {
                        f_10f990(bank, idx, 0, q);
                        return res;
                    }
                } else {
                    f_10f628(q, ch, bank, idx, vol, a, b);
                    f_10f990(bank, idx, 0, q);
                    return res;
                }
            } else {
                f_10f628(q, ch, bank, idx, vol, a, b);
                f_10f990(bank, idx, 0, q);
                return 0x80000018;
            }
        } else {
            f_10f628(q, ch, bank, idx, vol, a, b);
            f_10f990(bank, idx, 0, q);
            return 0x80000017;
        }
    } else {
        f_10f628(q, ch, bank, idx, vol, a, b);
        f_10f990(bank, idx, 0, q);
        return ch;
    }
}

/* @implements 0x110364 us f_110364
   WHAT IT DOES: The sound code's random number generator: a linear congruential step,
   returning 15 bits. */
unsigned int f_110364(void)
{
    D_28169c = D_28169c * 0x0696542d + 12345;
    return (D_28169c >> 16) & 0x7fff;
}

/* @implements 0x110390 us f_110390
   WHAT IT DOES: Copies sound (bank, idx)'s length into request r; 0x80000010/11 for a bad
   bank or index. */
int f_110390(unsigned short bank, unsigned short idx, SoundReq *r)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (!(idx < f_10da58(bank)))
        return 0x80000011;
    r->delay = f_10daa4(bank, idx)->m20;
    return 0;
}

/* @implements 0x11041c us f_11041c
   WHAT IT DOES: Reads sound (bank, idx)'s voice settings; 0x80000010/11 for a bad bank or
   index. */
int f_11041c(unsigned short bank, unsigned short idx, SoundVoice *v)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (!(idx < f_10da58(bank)))
        return 0x80000011;
    if (f_10daa4(bank, idx)->m8 == -1)
        v->id = -1;
    else
        v->id = f_10daa4(bank, idx)->m8;
    v->kind = f_10daa4(bank, idx)->m12;
    v->m8 = f_10daa4(bank, idx)->m20;
    return 0;
}

/* @draft 0x1104ec us f_1104ec
   WHAT IT DOES: Starts request r's sound now (0x10fd4c) at its volume and settings;
   0x80000010/11 for a bad bank or index.
   DRAFT: 3 words differ: retail moves bank and idx into a0/a1 before r into t0 (the moves
   are hoisted above the index test); here t0 goes first. */
int f_1104ec(unsigned short bank, unsigned short idx, SoundReq *r)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (!(idx < f_10da58(bank)))
        return 0x80000011;
    f_10fd4c(bank, idx, r->m20, r->m28, r, 1, r->vol, -1, 1.0f);
    return 0;
}

/* @implements 0x11058c us f_11058c
   WHAT IT DOES: A debug print that prints nothing. */
void f_11058c(const char *fmt, ...)
{
}

/* @implements 0x1105b4 us f_1105b4
   WHAT IT DOES: A second debug print that prints nothing. */
void f_1105b4(const char *fmt, ...)
{
}

/* @implements 0x1105dc us f_1105dc
   WHAT IT DOES: Wraps a pan into -127 to 127 by steps of 255. */
int f_1105dc(int pan)
{
    if (pan < -127)
        pan = f_1105dc(pan + 255);
    if (pan > 127)
        pan = f_1105dc(pan - 255);
    return pan;
}

/* @implements 0x110630 us f_110630
   WHAT IT DOES: Looks a level up in curve table t: 0 below 0, 255 from 256 up. */
int f_110630(int t, int level)
{
    if (level < 0)
        return 0;
    if (level >= 256)
        return 255;
    return D_1d77b8[t][255 - level];
}

/* @draft 0x110664 us f_110664
   WHAT IT DOES: The left and right gains for a pan from the pan table, wrapping the pan into
   range first.
   DRAFT: 3 words differ: retail forms the table address before li 127 and reuses v0 for
   the constant; here 127 goes in v1 first. */
void f_110664(int pan, int *l, int *r)
{
    unsigned char *t;
    int i, j;

    if (pan < -127 || pan > 127)
        pan = f_1105dc(pan);
    t = D_1d79b8;
    i = 127 - pan;
    j = pan;
    if (pan < 0) {
        i = pan + 127;
        j = -pan;
    }
    *l = t[i];
    *r = t[j];
}

/* @implements 0x1106ec us f_1106ec
   WHAT IT DOES: Loads curve table t from 256 bytes. */
int f_1106ec(const unsigned char *src, int t)
{
    __builtin_memcpy(D_1d77b8[t], src, 256);
    return 0;
}

/* @implements 0x110778 us f_110778
   WHAT IT DOES: Stores a value for 0x110784. */
void f_110778(int x)
{
    D_281eb4 = x;
}

/* @implements 0x110784 us f_110784
   WHAT IT DOES: Returns the value stored by 0x110778. */
int f_110784(void)
{
    return D_281eb4;
}
