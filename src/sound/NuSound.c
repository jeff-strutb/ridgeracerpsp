/* The NU Sound C API (retail 0x10bd70 to 0x10c948): sound system set up, per-frame update
   and pause, master volume, and the key-on entry points that start sound table entries by
   bank name (0x10da7c) or bank number, with or without start settings, a volume and a bus.
   The voice handle functions read and change a playing sound's volume, pan and pitch, stop
   it and test whether it still plays. Errors: 0x80000011 for a tone index past the bank's
   tone count, 0x80000010 for an empty bank slot, 0x8000001a for a bad voice handle,
   0x80000030 for a negative volume. The SAS voice table's init and release that follow
   (0x10c948, 0x10c9fc) belong to the next object file. */

/* A voice handle (the SoundReq of the SAS voice player). */
typedef struct SoundReq {
    int ch;                 /* the voice it plays on */
    unsigned short idx;
    unsigned short bank;
    int key;
    int m12;
    float vol;
    short pan;
    short pad22;
    int delay;
    short pitch;
    short m30;
    int m32;
} SoundReq;

/* A SAS voice's state (0x10d160), the fields read here. */
typedef struct SasVoice {
    unsigned char on;
    char m1[31];
    int key;
} SasVoice;

/* A sound configuration record: its six language bytes at +34. */
typedef struct SoundLang {
    char m0[34];
    char lang[6];
} SoundLang;

extern char D_1d77a8[];         /* the product code */
extern int D_27f168;            /* paused */

int f_10e198(void *config);
int f_10db3c(void);
int f_10f378(void);
void f_110cac(void);
void f_10d900(unsigned int size);
void f_10ea3c(int n);
void f_10ea80(void);
void f_10e788(void);
void f_110f10(void);
void f_10d93c(void);
void f_10f470(void);
int f_10df5c(int t);
void f_10ee58(int t);
int f_10f5ac(void);
void f_111a48(int t);
int f_111e04(void);
int f_10eac8(int t);
void f_110778(int a);
int f_110784(void);
int f_10e0e8(int i);
int f_10ddac(unsigned char i, short pan, float vol);
int f_10e104(int a);
int f_10da7c(unsigned short name);
unsigned int f_10da58(int bank);
int f_10da30(unsigned short bank);
int f_10fd4c(unsigned short bank, unsigned short idx, float vol, short a, short b, SoundReq *q, int mode, int bus, float gain);
int f_10d18c(int a, int key);
SasVoice *f_10d160(int a, int ch);
void f_10f608(int ch);
void f_10ec84(SoundReq *r);
void f_110d24(int ch);
void f_110d4c(int ch);
void f_10fa38(int ch, short pan, short pitch, float vol);
void f_10fae0(int ch, float vol);
void f_10fb10(int ch, short pan);
void f_10fb44(int ch, short pitch);
void f_10ec60(SoundReq *r);
int f_110d74(signed char ch);
int f_110d98(signed char ch);
int f_10d1dc(void);

/* @implements 0x10bd70 us f_10bd70
   WHAT IT DOES: Whether language slot i (under 6) of a configuration record is lang. */
int f_10bd70(int a, signed char lang, unsigned int i, SoundLang *p)
{
    int v = lang;

    lang = 0;
    if (i < 6)
        if (p != 0) {
            signed char *q = (signed char *)(i + (unsigned int)p);
            lang = (q[34] ^ v) == 0;
        }
    return lang;
}

/* @implements 0x10bd9c us f_10bd9c
   WHAT IT DOES: Returns -1. */
int f_10bd9c(void)
{
    return -1;
}

/* @implements 0x10bda4 us f_10bda4
   WHAT IT DOES: Returns 1 (the region). */
int f_10bda4(void)
{
    return 1;
}

/* @implements 0x10bdac us f_10bdac
   WHAT IT DOES: Returns the product code string. */
char *f_10bdac(void)
{
    return D_1d77a8;
}

/* @implements 0x10bdb8 us f_10bdb8
   WHAT IT DOES: Sets up the sound system with a sound memory size (at most 8 MB) and a
   configuration: the configuration, the bank list, the voice player, the output, the
   memory and 64 delay queue entries. */
int f_10bdb8(unsigned int size, void *config)
{
    int r;

    if (size > 0x800000)
        return 0x80000000;
    r = f_10e198(config);
    if (r)
        return r;
    r = f_10db3c();
    if (r)
        return r;
    r = f_10f378();
    if (r)
        return r;
    f_110cac();
    f_10d900(size);
    f_10ea3c(64);
    return 0;
}

/* @implements 0x10be40 us f_10be40
   WHAT IT DOES: The per-frame sound update. */
int f_10be40(void)
{
    f_10ea80();
    f_10e788();
    f_110f10();
    f_10d93c();
    f_10f470();
    return 0;
}

/* @implements 0x10be80 us f_10be80
   WHAT IT DOES: Advances the sound system by t ticks: the timers, the voices, the streams,
   and the fades (stopped while paused). Returns a negative error or 0. */
int f_10be80(int t)
{
    int r = f_10df5c(t);

    if (r < 0)
        return r;
    f_10ee58(t);
    r = f_10f5ac();
    if (r < 0)
        return r;
    f_111a48(t);
    r = f_111e04();
    if (r < 0)
        return r;
    if (D_27f168)
        r = f_10eac8(0);
    else
        r = f_10eac8(t);
    return r < 0 ? r : 0;
}

/* @implements 0x10bf04 us f_10bf04
   WHAT IT DOES: Sets the pause flag. */
int f_10bf04(int pause)
{
    D_27f168 = pause;
    return 0;
}

/* @implements 0x10bf14 us f_10bf14
   WHAT IT DOES: Returns 0. */
int f_10bf14(void)
{
    return 0;
}

/* @draft 0x10bf1c us f_10bf1c
   WHAT IT DOES: Sets the output mode (0 or 1).
   DRAFT: branch shape and size match; retail copies the argument with move v0,a0 before
   seh and schedules the epilogue differently. Switch, || and held-result forms tried. */
int f_10bf1c(short mode)
{
    if (mode == 0)
        goto call;
    if (mode != 1)
        return 0x80000000;
call:
    f_110778(0);
    return 0;
}

/* @implements 0x10bf58 us f_10bf58
   WHAT IT DOES: The output mode. */
short f_10bf58(void)
{
    return f_110784();
}

/* @draft 0x10bf78 us f_10bf78
   WHAT IT DOES: Sets the master volume (not negative).
   DRAFT: one swapped pair; retail sets $f12 before a1 for the f_10ddac call. Float
   temporaries and a short local for the pan tried. */
int f_10bf78(float vol)
{
    if (vol < 0.0f)
        return 0x80000030;
    f_10ddac(0, f_10e0e8(0), vol);
    return 0;
}

/* @implements 0x10bfd0 us f_10bfd0
   WHAT IT DOES: The master volume. */
int f_10bfd0(void)
{
    return f_10e104(0);
}

/* @implements 0x10bfec us f_10bfec
   WHAT IT DOES: Returns 0. */
int f_10bfec(void)
{
    return 0;
}

/* @implements 0x10bff4 us f_10bff4
   WHAT IT DOES: Returns 0. */
int f_10bff4(void)
{
    return 0;
}

/* @implements 0x10bffc us f_10bffc
   WHAT IT DOES: Returns 0. */
int f_10bffc(void)
{
    return 0;
}

/* @implements 0x10c004 us f_10c004
   WHAT IT DOES: Starts tone of the bank named name. */
int f_10c004(unsigned short name, unsigned short tone, SoundReq *voice)
{
    int id = f_10da7c(name);

    if (id < 0)
        return id;
    if (tone >= f_10da58(id))
        return 0x80000011;
    return f_10fd4c(id, tone, 1.0f, 0, 0, voice, 0, -1, 1.0f);
}

/* @implements 0x10c09c us f_10c09c
   WHAT IT DOES: Starts tone of the bank named name with start settings and a volume. */
int f_10c09c(unsigned short name, unsigned short tone, short a, short b, SoundReq *voice, float vol)
{
    int id = f_10da7c(name);

    if (id < 0)
        return id;
    if (tone >= f_10da58(id))
        return 0x80000011;
    return f_10fd4c(id, tone, vol, a, b, voice, 0, -1, 1.0f);
}

/* @implements 0x10c158 us f_10c158
   WHAT IT DOES: Starts tone of a bank. */
int f_10c158(unsigned short bank, unsigned short tone, SoundReq *voice)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (tone >= f_10da58(bank))
        return 0x80000011;
    return f_10fd4c(bank, tone, 1.0f, 0, 0, voice, 0, -1, 1.0f);
}

/* @implements 0x10c1f8 us f_10c1f8
   WHAT IT DOES: Starts tone of a bank with start settings and a volume. */
int f_10c1f8(unsigned short bank, unsigned short tone, short a, short b, SoundReq *voice, float vol)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (tone >= f_10da58(bank))
        return 0x80000011;
    return f_10fd4c(bank, tone, vol, a, b, voice, 0, -1, 1.0f);
}

/* @implements 0x10c2bc us f_10c2bc
   WHAT IT DOES: Starts tone of the bank named name on a bus. */
int f_10c2bc(unsigned short name, unsigned short tone, signed char bus, SoundReq *voice)
{
    int id = f_10da7c(name);

    if (id < 0)
        return id;
    if (tone >= f_10da58(id))
        return 0x80000011;
    return f_10fd4c(id, tone, 1.0f, 0, 0, voice, 0, bus, 1.0f);
}

/* @implements 0x10c360 us f_10c360
   WHAT IT DOES: Starts tone of the bank named name on a bus with start settings and a
   volume. */
int f_10c360(unsigned short name, unsigned short tone, signed char bus, short a, short b, SoundReq *voice, float vol)
{
    int id = f_10da7c(name);

    if (id < 0)
        return id;
    if (tone >= f_10da58(id))
        return 0x80000011;
    return f_10fd4c(id, tone, vol, a, b, voice, 0, bus, 1.0f);
}

/* @implements 0x10c428 us f_10c428
   WHAT IT DOES: Starts tone of a bank on a bus. */
int f_10c428(unsigned short bank, unsigned short tone, signed char bus, SoundReq *voice)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (tone >= f_10da58(bank))
        return 0x80000011;
    return f_10fd4c(bank, tone, 1.0f, 0, 0, voice, 0, bus, 1.0f);
}

/* @implements 0x10c4d4 us f_10c4d4
   WHAT IT DOES: Starts tone of a bank on a bus with start settings and a volume. */
int f_10c4d4(unsigned short bank, unsigned short tone, signed char bus, short a, short b, SoundReq *voice, float vol)
{
    if (f_10da30(bank) == 0x80000010)
        return 0x80000010;
    if (tone >= f_10da58(bank))
        return 0x80000011;
    return f_10fd4c(bank, tone, vol, a, b, voice, 0, bus, 1.0f);
}

/* @implements 0x10c5a4 us f_10c5a4
   WHAT IT DOES: Stops a playing sound: finds its voice by key, keys it off, clears the
   handle and frees the voice. 1 when the handle holds no sound. */
int f_10c5a4(SoundReq *r)
{
    int ch;

    if (!r->key)
        return 1;
    ch = f_10d18c(0, r->key);
    if ((unsigned int)ch >= 32)
        return 0x8000001a;
    f_10f608(ch);
    f_10ec84(r);
    f_110d24(ch);
    return 0;
}

/* @implements 0x10c624 us f_10c624
   WHAT IT DOES: Stops voice ch. */
int f_10c624(signed char ch)
{
    if ((unsigned char)ch < 32) {
        f_110d4c(ch);
        return 0;
    }
    return 0x80000000;
}

/* @implements 0x10c65c us f_10c65c
   WHAT IT DOES: Stops all 32 voices. */
int f_10c65c(void)
{
    int i;

    for (i = 0; i < 32; i++)
        f_110d4c(i);
    return 0;
}

/* @implements 0x10c698 us f_10c698
   WHAT IT DOES: A handle's volume (0 for no handle or a bad voice). */
float f_10c698(SoundReq *r)
{
    float v = 0.0f;

    if (r && r->ch < 32)
        v = r->vol;
    return v;
}

/* @implements 0x10c6bc us f_10c6bc
   WHAT IT DOES: A handle's pan. */
int f_10c6bc(SoundReq *r)
{
    int v = 0;

    if (r && r->ch < 32)
        v = r->pan;
    return v;
}

/* @implements 0x10c6dc us f_10c6dc
   WHAT IT DOES: A handle's pitch. */
int f_10c6dc(SoundReq *r)
{
    int v = 0;

    if (r && r->ch < 32)
        v = r->pitch;
    return v;
}

/* @implements 0x10c6fc us f_10c6fc
   WHAT IT DOES: Sets a playing sound's volume, pan and pitch. */
int f_10c6fc(SoundReq *r, short pan, short pitch, float vol)
{
    if ((unsigned int)r->ch >= 32)
        return 0x8000001a;
    r->vol = vol;
    r->pan = pan;
    r->pitch = pitch;
    f_10fa38(r->ch, pan, pitch, vol);
    f_10ec60(r);
    return 0;
}

/* @implements 0x10c764 us f_10c764
   WHAT IT DOES: Sets a playing sound's volume. */
int f_10c764(SoundReq *r, float vol)
{
    if ((unsigned int)r->ch >= 32)
        return 0x8000001a;
    r->vol = vol;
    f_10fae0(r->ch, vol);
    f_10ec60(r);
    return 0;
}

/* @implements 0x10c7b4 us f_10c7b4
   WHAT IT DOES: Sets a playing sound's pan. */
int f_10c7b4(short pan, SoundReq *r)
{
    if ((unsigned int)r->ch >= 32)
        return 0x8000001a;
    r->pan = pan;
    f_10fb10(r->ch, pan);
    f_10ec60(r);
    return 0;
}

/* @implements 0x10c810 us f_10c810
   WHAT IT DOES: Sets a playing sound's pitch. */
int f_10c810(short pitch, SoundReq *r)
{
    if ((unsigned int)r->ch >= 32)
        return 0x8000001a;
    r->pitch = pitch;
    f_10fb44(r->ch, pitch);
    f_10ec60(r);
    return 0;
}

/* @implements 0x10c86c us f_10c86c
   WHAT IT DOES: 0 while the handle's sound still plays, 1 once it has ended. */
int f_10c86c(SoundReq *r)
{
    int ch = r->ch;
    SasVoice *v;

    if ((unsigned int)ch >= 32)
        return 0x80000000;
    if (!r->key)
        return 1;
    ch = f_10d18c(0, r->key);
    if (ch == 0x80000000)
        return 1;
    v = f_10d160(0, ch);
    if (v->on && v->key)
        return 0;
    return 1;
}

/* @implements 0x10c8f4 us f_10c8f4
   WHAT IT DOES: Bus ch's first level. */
int f_10c8f4(signed char ch)
{
    return f_110d74(ch);
}

/* @implements 0x10c910 us f_10c910
   WHAT IT DOES: Bus ch's second level. */
int f_10c910(signed char ch)
{
    return f_110d98(ch);
}

/* @implements 0x10c92c us f_10c92c
   WHAT IT DOES: The number of voices in use. */
int f_10c92c(void)
{
    return f_10d1dc();
}
