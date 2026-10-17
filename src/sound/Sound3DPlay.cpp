/* The 3D sound play interface (retail 0x113644 to 0x114234): starts sounds at a position
   through the 3D sound object (0x114234, D_2826d0), which gives the distance attenuation a
   sound starts with and then tracks it. A sound too far away to hear (attenuation under
   0.01) is not started (0x8000001b); 0x80000000 for an unknown bank. The variants take a bank
   by name (0x10da7c) or by number, start settings, a volume and a bus. */

struct SoundReq {
    int ch;
    unsigned short idx;
    unsigned short bank;
    int key;
    int m12;
    float vol;
};

/* A listener record: 16 bytes of header and its 80-byte entries. */
struct ListenerEntry {
    char m[80];
};

struct Listener {
    char m0[8];
    unsigned short n;
    char m10[6];
    ListenerEntry e[1];
};

extern "C" {
int f_10da7c(unsigned short name);
int f_10dad4(unsigned short bank);
int f_10fd4c(unsigned short bank, unsigned short idx, short a, short b, SoundReq *q, int mode, float vol, int bus, float gain);
void f_10c5a4(SoundReq *r);
int f_10c764(SoundReq *r, float v);
void f_10d334(struct Listener *l, int a, unsigned short *b);
int f_10d360(void);
}

/* The 3D sound object of the next object file. */
class C3DSound {
public:
    char m0[2888];
    float m2888;
    int m2892;

    int f_114234();
    int f_114300(int a);
    void f_1147a0(int ch, unsigned short bank, unsigned short idx);
    void f_1147dc(SoundReq *r, void *pos, void *vel, void *x);
    void f_114854(int ch, short a);
    void f_114890(int a, int b, int c, int d);
    void f_1148f4(int a, int b, void *p);
    int f_11490c();
    float f_114958(void *pos, unsigned short bank, unsigned short idx);
};

extern C3DSound *D_2826d0;

extern "C" {

/* @implements 0x113644 us f_113644
   WHAT IT DOES: Creates the 3D sound object and sets it up. */
void f_113644(void)
{
    D_2826d0 = new C3DSound;
    D_2826d0->f_114234();
}

/* @implements 0x113670 us f_113670
   WHAT IT DOES: Deletes the 3D sound object. */
int f_113670(void)
{
    if (D_2826d0)
        delete D_2826d0;
    D_2826d0 = 0;
    return 0;
}

/* @implements 0x1136b4 us f_1136b4
   WHAT IT DOES: Starts sound idx of the bank named name at a position. */
int f_1136b4(unsigned short name, unsigned short idx, void *pos, void *vel, void *x, SoundReq *r)
{
    int id = f_10da7c(name);
    unsigned short bank = id;
    float d;

    if (id < 0)
        return id;
    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, 0, 0, r, 0, 1.0f, -1, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x1137cc us f_1137cc
   WHAT IT DOES: Starts sound idx of the bank named name at a position with start settings
   and a volume. */
int f_1137cc(unsigned short name, unsigned short idx, short a, short b, float vol, void *pos, void *vel, void *x, SoundReq *r)
{
    int id = f_10da7c(name);
    unsigned short bank = id;
    float d;

    if (id < 0)
        return id;
    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, a, b, r, 0, vol, -1, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113908 us f_113908
   WHAT IT DOES: Starts sound idx of a bank at a position. */
int f_113908(unsigned short bank, unsigned short idx, void *pos, void *vel, void *x, SoundReq *r)
{
    float d;

    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, 0, 0, r, 0, 1.0f, -1, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113a10 us f_113a10
   WHAT IT DOES: Starts sound idx of a bank at a position with start settings and a volume. */
int f_113a10(unsigned short bank, unsigned short idx, short a, short b, float vol, void *pos, void *vel, void *x, SoundReq *r)
{
    float d;

    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, a, b, r, 0, vol, -1, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113b3c us f_113b3c
   WHAT IT DOES: Starts sound idx of the bank named name at a position on a bus. */
int f_113b3c(unsigned short name, unsigned short idx, signed char bus, void *pos, void *vel, void *x, SoundReq *r)
{
    int id = f_10da7c(name);
    unsigned short bank = id;
    float d;

    if (id < 0)
        return id;
    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, 0, 0, r, 0, 1.0f, bus, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113c60 us f_113c60
   WHAT IT DOES: Starts sound idx of the bank named name at a position on a bus with start
   settings and a volume. */
int f_113c60(unsigned short name, unsigned short idx, signed char bus, short a, short b, float vol, void *pos, void *vel, void *x, SoundReq *r)
{
    int id = f_10da7c(name);
    unsigned short bank = id;
    float d;

    if (id < 0)
        return id;
    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, a, b, r, 0, vol, bus, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113dac us f_113dac
   WHAT IT DOES: Starts sound idx of a bank at a position on a bus. */
int f_113dac(unsigned short bank, unsigned short idx, signed char bus, void *pos, void *vel, void *x, SoundReq *r)
{
    float d;

    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, 0, 0, r, 0, 1.0f, bus, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113ec0 us f_113ec0
   WHAT IT DOES: Starts sound idx of a bank at a position on a bus with start settings and a
   volume. */
int f_113ec0(unsigned short bank, unsigned short idx, signed char bus, short a, short b, float vol, void *pos, void *vel, void *x, SoundReq *r)
{
    float d;

    if (!f_10dad4(bank))
        return 0x80000000;
    d = D_2826d0->f_114958(pos, bank, idx);
    if (d < 0.01f)
        return 0x8000001b;
    f_10fd4c(bank, idx, a, b, r, 0, vol, bus, d);
    D_2826d0->f_1147dc(r, pos, vel, x);
    D_2826d0->f_1147a0(r->ch, bank, idx);
    return 0;
}

/* @implements 0x113ff8 us f_113ff8
   WHAT IT DOES: Moves playing sound r to a new position. */
int f_113ff8(void *pos, void *vel, void *x, SoundReq *r)
{
    if ((unsigned int)r->ch < 32) {
        D_2826d0->f_1147dc(r, pos, vel, x);
        return 0;
    }
    return 0x80000000;
}

/* @implements 0x114048 us f_114048
   WHAT IT DOES: Sets playing sound r's volume and setting a and moves it to a new
   position. */
int f_114048(int unused, short a, void *pos, void *vel, void *x, SoundReq *r, float vol)
{
    if ((unsigned int)r->ch < 32) {
        f_10c764(r, vol);
        D_2826d0->f_114854(r->ch, a);
        D_2826d0->f_1147dc(r, pos, vel, x);
        return 0;
    }
    return 0x80000000;
}

/* @implements 0x1140f4 us f_1140f4
   WHAT IT DOES: Stops sound r (0x10c5a4). */
int f_1140f4(SoundReq *r)
{
    f_10c5a4(r);
    return 0;
}

/* @implements 0x114114 us f_114114
   WHAT IT DOES: Passes four settings to the 3D sound object (0x114890). */
int f_114114(int a, int b, int c, int d)
{
    D_2826d0->f_114890(a, b, c, d);
    return 0;
}

/* @implements 0x114154 us f_114154
   WHAT IT DOES: Sets the 3D sound object's setting at +2888. */
int f_114154(float v)
{
    D_2826d0->m2888 = v;
    return 0;
}

/* @implements 0x114168 us f_114168
   WHAT IT DOES: Does nothing and returns 0. */
int f_114168(void)
{
    return 0;
}

/* @implements 0x114170 us f_114170
   WHAT IT DOES: Sets the 3D sound object's setting at +2888 (a second entry point). */
int f_114170(float v)
{
    D_2826d0->m2888 = v;
    return 0;
}

/* @draft 0x114184 us f_114184
   WHAT IT DOES: Updates the listener record (0x10d334) and passes its current entry to the
   3D sound object (0x1148f4).
   DRAFT: retail keeps the record in s1 and b in s0 and computes the entry address into s1
   (the record's own register) before copying it to a3; here the two are swapped. */
int f_114184(Listener *l, int a, unsigned short *b)
{
    f_10d334(l, a, b);
    D_2826d0->f_1148f4(l->n, *b, &l->e[l->n]);
    return 0;
}

/* @implements 0x1141e8 us f_1141e8
   WHAT IT DOES: Updates the 3D sound object (0x11490c), then 0x10d360. */
void f_1141e8(void)
{
    D_2826d0->f_11490c();
    f_10d360();
}

/* @implements 0x114210 us f_114210
   WHAT IT DOES: Advances the 3D sound object (0x114300). */
int f_114210(int a)
{
    return D_2826d0->f_114300(a);
}
}
