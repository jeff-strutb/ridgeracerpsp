/* The sound effect player object file (retail 0x0f6534 to 0x0f6b90). Its one instance,
   D_27ee3c (see src/sound/SeBank.cpp), loads sound banks into the sound system and plays
   effects on sixteen channels taken round robin, and stops them, sets their volume and tells
   which are free. The file's static data are the instance's construction and destruction. */

#include <stdio.h>

extern "C" {
void f_01c618(void *sys, void *ch);
void f_01c96c(void *sys, const char *name, int a, unsigned short *handle);
void f_01c578(void *sys);
void f_10c1f8(unsigned short bank, unsigned short snd, short pan, int a, void *h, float vol);
void f_10c09c(unsigned short bank, unsigned short snd, short pan, int a, void *h, float vol);
void f_10c5a4(void *h);
int f_10c764(void *h, float vol);
int f_10c86c(void *h);
void f_10d37c(unsigned short ch, int *state);
}
extern char D_23bb4c[];

/* One playing channel's sound request (36 bytes). */
struct SeChannel {
    char m0[36];
};

class CSePlayer {
public:
    CSePlayer();
    ~CSePlayer();
    int f_0f65b0();
    int f_0f6638();
    unsigned short f_0f6664(const char *name);
    void f_0f66cc();
    int f_0f6704(int v);
    int f_0f6710(int v);
    int f_0f671c(int bank, int snd, float vol);
    int f_0f67c0(int bank, int snd, float vol);
    int f_0f6864(int i);
    int f_0f6894();
    int f_0f68d8(int i, float vol);
    void f_0f6904(float vol);
    int f_0f6954(int i);
    int f_0f6a08();
    int f_0f6a7c();

    int loads;
    int m4;
    int m8;
    float m12;
    int m16;
    int m20;
    SeChannel ch[16];
    int last;
};

extern CSePlayer D_27ee3c;

/* @implements 0x0f6534 us _ZN9CSePlayerC2Ev
   WHAT IT DOES: Sets the player up (base object constructor). */
/* @implements 0x0f6550 us _ZN9CSePlayerC1Ev
   WHAT IT DOES: Sets the player up (complete object constructor). */
CSePlayer::CSePlayer()
{
    f_0f65b0();
}

/* @implements 0x0f656c us _ZN9CSePlayerD2Ev
   WHAT IT DOES: Resets the player (base object destructor). */
/* @implements 0x0f6588 us _ZN9CSePlayerD1Ev
   WHAT IT DOES: Resets the player (complete object destructor). */
CSePlayer::~CSePlayer()
{
    f_0f6638();
}

/* @implements 0x0f65a4 us f_0f65a4
   WHAT IT DOES: Returns the player instance. */
extern "C" CSePlayer *f_0f65a4()
{
    return &D_27ee3c;
}

/* @implements 0x0f65b0 us _ZN9CSePlayer8f_0f65b0Ev
   WHAT IT DOES: Clears the player (no bank, full volume) and registers its sixteen channels
   with the sound system. Returns 1. */
int CSePlayer::f_0f65b0()
{
    loads = -1;
    m4 = 0;
    m8 = 0;
    m12 = 1.0f;
    m16 = 0;
    m20 = 0;
    for (int i = 0; i < 16; i++)
        f_01c618(D_23bb4c, &ch[i]);
    last = 0;
    return 1;
}

/* @implements 0x0f6638 us _ZN9CSePlayer8f_0f6638Ev
   WHAT IT DOES: Clears the player (no bank, full volume). Returns 1. */
int CSePlayer::f_0f6638()
{
    loads = -1;
    m4 = 0;
    m8 = 0;
    m12 = 1.0f;
    m16 = 0;
    m20 = 0;
    return 1;
}

/* @implements 0x0f6664 us _ZN9CSePlayer8f_0f6664EPKc
   WHAT IT DOES: Loads the sound bank "Sound/<name>" into the sound system, counts the load
   and returns the bank's handle. */
unsigned short CSePlayer::f_0f6664(const char *name)
{
    unsigned short h;
    char buf[64];
    sprintf(buf, "Sound/%s", name);
    f_01c96c(D_23bb4c, buf, 0, &h);
    loads++;
    return h;
}

/* @implements 0x0f66cc us _ZN9CSePlayer8f_0f66ccEv
   WHAT IT DOES: Releases a bank from the sound system and counts it off. */
void CSePlayer::f_0f66cc()
{
    f_01c578(D_23bb4c);
    loads--;
}

/* @implements 0x0f6704 us _ZN9CSePlayer8f_0f6704Ei
   WHAT IT DOES: Sets the word at +4. Returns 1. */
int CSePlayer::f_0f6704(int v)
{
    m4 = v;
    return 1;
}

/* @implements 0x0f6710 us _ZN9CSePlayer8f_0f6710Ei
   WHAT IT DOES: Sets the word at +8. Returns 1. */
int CSePlayer::f_0f6710(int v)
{
    m8 = v;
    return 1;
}

/* @implements 0x0f671c us _ZN9CSePlayer8f_0f671cEiif
   WHAT IT DOES: Plays sound snd of bank on the next free channel at the given volume (one
   way of starting it, 0x10c1f8) and remembers the channel. Returns the channel, or -1 when
   none is free. */
int CSePlayer::f_0f671c(int bank, int snd, float vol)
{
    int i = f_0f6a08();
    if (i != -1) {
        f_10c1f8(bank, snd, 0, 0, &ch[i], vol);
        last = i;
        return i;
    }
    return -1;
}

/* @implements 0x0f67c0 us _ZN9CSePlayer8f_0f67c0Eiif
   WHAT IT DOES: The same with the other way of starting a sound (0x10c09c). */
int CSePlayer::f_0f67c0(int bank, int snd, float vol)
{
    int i = f_0f6a08();
    if (i != -1) {
        f_10c09c(bank, snd, 0, 0, &ch[i], vol);
        last = i;
        return i;
    }
    return -1;
}

/* @implements 0x0f6864 us _ZN9CSePlayer8f_0f6864Ei
   WHAT IT DOES: Stops channel i. Returns 1. */
int CSePlayer::f_0f6864(int i)
{
    f_10c5a4(&ch[i]);
    return 1;
}

/* @implements 0x0f6894 us _ZN9CSePlayer8f_0f6894Ev
   WHAT IT DOES: Stops every channel. Returns 1. */
int CSePlayer::f_0f6894()
{
    for (int i = 0; i < 16; i++)
        f_10c5a4(&ch[i]);
    return 1;
}

/* @implements 0x0f68d8 us _ZN9CSePlayer8f_0f68d8Eif
   WHAT IT DOES: Sets channel i's volume. */
int CSePlayer::f_0f68d8(int i, float vol)
{
    return f_10c764(&ch[i], vol);
}

/* @implements 0x0f6904 us _ZN9CSePlayer8f_0f6904Ef
   WHAT IT DOES: Sets every channel's volume. */
void CSePlayer::f_0f6904(float vol)
{
    for (int i = 0; i < 16; i++)
        f_10c764(&ch[i], vol);
}

/* @implements 0x0f6954 us _ZN9CSePlayer8f_0f6954Ei
   WHAT IT DOES: Returns 1 when channel i is free (its state is 1, or the not-playing code
   0x80000000). */
int CSePlayer::f_0f6954(int i)
{
    SeChannel *c = &ch[i];
    if (f_10c86c(c) == 1 || f_10c86c(c) == (int)0x80000000)
        return 1;
    return 0;
}

/* @draft 0x0f69b8 us f_0f69b8
   WHAT IT DOES: Returns the first sound system channel whose state is not 3.
   Remaining difference: retail reads the state into v1; here v0 (two words). */
extern "C" int f_0f69b8()
{
    int state = 0;
    for (int i = 0;; i++) {
        f_10d37c(i, &state);
        if (state != 3)
            return i;
    }
}

/* @implements 0x0f6a08 us _ZN9CSePlayer8f_0f6a08Ev
   WHAT IT DOES: Finds a free channel, starting after the last one used and wrapping round.
   Returns it, or -1 when all sixteen are busy. */
int CSePlayer::f_0f6a08()
{
    int k = last;
    for (int n = 0; n < 16; n++) {
        k++;
        if (k >= 16)
            k = 0;
        if (f_0f6954(k))
            return k;
    }
    return -1;
}

/* @implements 0x0f6a7c us _ZN9CSePlayer8f_0f6a7cEv
   WHAT IT DOES: Counts the channels whose state is 0. */
int CSePlayer::f_0f6a7c()
{
    int n = 0;
    for (int i = 0; i < 16; i++)
        n += f_10c86c(&ch[i]) == 0;
    return n;
}

/* The player instance. */
CSePlayer D_27ee3c;

/* @implements 0x0f6ad4 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs (or destroys) the player instance. */
/* @implements 0x0f6b50 us _GLOBAL__I
   WHAT IT DOES: Static construction of the player. */
/* @implements 0x0f6b70 us _GLOBAL__D
   WHAT IT DOES: Static destruction of the player. */
