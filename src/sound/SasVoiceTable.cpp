/* The SAS voice table (retail 0x10c948 to 0x10d334): the state of the 32 SAS voices and of
   8 extra voices, and three masks of voices waiting for a pitch update, a key off and a
   key-off check. One global instance (D_27f16c), used through the plain functions at the
   end of the file. Each frame the update walks the voices: a starting voice (state 1) times
   out after 120 frames, a playing voice (state 2) has its send levels recomputed from its
   two buses and moved at most 256 a frame towards them, and an ending voice (state 3) is
   released. Errors: 0x80000000 for an unknown key, 0x80000012 when no voice is free. */

/* A bus mix (0x10dfcc). */
struct BusMix {
    float vol;
    short pan;
    unsigned short n;
    char fx[32];
    char bus[32];
};

extern "C" {
int f_10dfcc(short id, BusMix *m);
int f_110630(int t, int level);
void f_110664(int pan, int *l, int *r);
void f_110d24(int ch);
int f_11aeb0(int ch);
int f_11aeec(int ch);
int f_11af28(int ch, int l, int r, int sl, int sr);
int f_11af8c(int ch, int pitch);
unsigned int f_11b1fc(void);
}

/* A voice (76 bytes). */
struct SasVoice {
    unsigned char state;    /* 0 free, 1 starting, 2 playing, 3 ending */
    int age;
    unsigned char b8;
    unsigned char group;
    unsigned char curve;
    unsigned char busA;
    unsigned char busB;
    unsigned char send;
    unsigned char b14;
    unsigned char b15;
    int i16;
    int i20;
    float base;
    short s28;
    int key;
    float vol;
    short pan;
    short s42;
    float gain;
    int i48;
    float mod;
    short pan2;
    short s58;
    short last[4];
    short level;
    short s70;
    unsigned short pitch;
};

class CSasVoices {
public:
    SasVoice voice[32];
    SasVoice ext[8];
    unsigned int pitchMask;
    unsigned int offMask;
    unsigned int endMask;

    ~CSasVoices() {}
    void f_10c948();
    void f_10c9fc();
    int f_10ca04();
    SasVoice *f_10cd34(int a, int ch);
    int f_10cd5c(int a, int key);
    int f_10cd98(int a);
    void f_10ce10();
    void f_10ce80(char *out);
    void f_10ceac(int ch);
    void f_10cec4();
    void f_10cf38(int ch);
    void f_10cf50(int ch);
    void f_10cf70();
    void f_10cfd4(int ch);
    void f_10cfec();
};

CSasVoices *D_27f16c;

/* @implements 0x10c948 us _ZN10CSasVoices8f_10c948Ev
   WHAT IT DOES: Clears the masks and every voice. */
void CSasVoices::f_10c948()
{
    int i;

    pitchMask = 0;
    offMask = 0;
    endMask = 0;
    for (i = 0; i < 32; i++) {
        voice[i].state = 0;
        voice[i].age = 0;
        voice[i].b8 = 0;
        voice[i].group = 0;
        voice[i].curve = 0;
        voice[i].busA = 0;
        voice[i].busB = 0;
        voice[i].send = 0;
        voice[i].b14 = 0;
        voice[i].b15 = 0;
        voice[i].i16 = 0;
        voice[i].i20 = 0;
        voice[i].base = 0;
        voice[i].s28 = 0;
        voice[i].vol = 0;
        voice[i].pan = 0;
        voice[i].s42 = 0;
        voice[i].gain = 0;
        voice[i].mod = 0;
        voice[i].pan2 = 0;
        voice[i].s58 = 0;
        voice[i].level = 0;
        voice[i].s70 = 0;
        voice[i].pitch = 0;
        voice[i].last[0] = 0;
        voice[i].last[1] = 0;
        voice[i].last[2] = 0;
        voice[i].last[3] = 0;
    }
    for (i = 0; i < 8; i++) {
        ext[i].state = 0;
        ext[i].age = 0;
    }
}

/* @implements 0x10c9fc us _ZN10CSasVoices8f_10c9fcEv
   WHAT IT DOES: Nothing. */
void CSasVoices::f_10c9fc()
{
}

/* @implements 0x10ca04 us _ZN10CSasVoices8f_10ca04Ev
   WHAT IT DOES: The per frame voice update. */
int CSasVoices::f_10ca04()
{
    int i;

    for (i = 0; i < 32; i++) {
        SasVoice *v = &voice[i];

        switch (v->state) {
        case 0:
            v->age = 0;
            break;
        case 1:
            if (++v->age >= 120)
                v->state = 0;
            break;
        case 2: {
            BusMix a, b;
            int l, r, sl, sr;
            float s;

            f_10dfcc(v->busA, &a);
            v->level = f_110630(v->curve, (int)(a.vol * v->gain * (v->mod * v->vol + v->base) * 255.0f)) << 4;
            f_10dfcc(v->busB, &b);
            if (b.n == 1 && b.bus[0] == 1)
                s = b.vol * v->send / 127.0f;
            else
                s = 0.0f;
            f_110664(v->pan + v->pan2 + a.pan - 64, &l, &r);
            l = l * v->level / 256;
            r = r * v->level / 256;
            sl = (int)(l * s);
            sr = (int)(r * s);
            if (l - v->last[0] > 256)
                l = v->last[0] + 256;
            else if (v->last[0] - l > 256)
                l = v->last[0] - 256;
            if (r - v->last[1] > 256)
                r = v->last[1] + 256;
            else if (v->last[1] - r > 256)
                r = v->last[1] - 256;
            if (sl - v->last[2] > 256)
                sl = v->last[2] + 256;
            else if (v->last[2] - sl > 256)
                sl = v->last[2] - 256;
            if (sr - v->last[3] > 256)
                sr = v->last[3] + 256;
            else if (v->last[3] - sr > 256)
                sr = v->last[3] - 256;
            if (l > 4096)
                l = 4096;
            if (r > 4096)
                r = 4096;
            if (sl > 4096)
                sl = 4096;
            if (sr > 4096)
                sr = 4096;
            f_11af28(i, l, r, sl, sr);
            v->last[0] = l;
            v->last[1] = r;
            v->last[2] = sl;
            v->last[3] = sr;
            v->age++;
            break;
        }
        case 3:
            f_110d24(i);
            v->age = 0;
            v->state = 0;
            v->key = 0;
            break;
        }
    }
    return 0;
}

/* @implements 0x10cd34 us _ZN10CSasVoices8f_10cd34Eii
   WHAT IT DOES: Returns voice ch, of the extra voices when a is set. */
SasVoice *CSasVoices::f_10cd34(int a, int ch)
{
    if (a)
        return &ext[ch];
    return &voice[ch];
}

/* @implements 0x10cd5c us _ZN10CSasVoices8f_10cd5cEii
   WHAT IT DOES: Returns the voice playing this key. */
int CSasVoices::f_10cd5c(int a, int key)
{
    int i;

    if (a == 0) {
        for (i = 0; i < 32; i++)
            if (voice[i].key == key)
                return i;
    }
    return 0x80000000;
}

/* @implements 0x10cd98 us _ZN10CSasVoices8f_10cd98Ei
   WHAT IT DOES: Returns a free voice (one of the first 29, or of the extra voices when a is
   1). */
int CSasVoices::f_10cd98(int a)
{
    unsigned int i;

    if (a == 0) {
        for (i = 0; i < 29; i++)
            if (voice[i].state == 0)
                return i;
    }
    if (a == 1) {
        for (i = 0; i < 8; i++)
            if (ext[i].state == 0)
                return i;
    }
    return 0x80000012;
}

/* @implements 0x10ce10 us _ZN10CSasVoices8f_10ce10Ev
   WHAT IT DOES: Moves each starting voice that is sounding to playing, and each playing
   voice that has stopped sounding to ending. */
void CSasVoices::f_10ce10()
{
    unsigned int m = f_11b1fc();
    unsigned int i;

    for (i = 0; i < 32; i++) {
        if (m & (1 << i)) {
            if (voice[i].state == 2)
                voice[i].state = 3;
        } else {
            if (voice[i].state == 1)
                voice[i].state = 2;
        }
    }
}

/* @implements 0x10ce80 us _ZN10CSasVoices8f_10ce80EPc
   WHAT IT DOES: Copies every voice's state out. */
void CSasVoices::f_10ce80(char *out)
{
    int i;

    for (i = 0; i < 32; i++)
        out[i] = voice[i].state;
}

/* @implements 0x10ceac us _ZN10CSasVoices8f_10ceacEi
   WHAT IT DOES: Marks voice ch for a pitch update. */
void CSasVoices::f_10ceac(int ch)
{
    pitchMask |= 1 << ch;
}

/* @implements 0x10cec4 us _ZN10CSasVoices8f_10cec4Ev
   WHAT IT DOES: Sets the pitch of every marked voice. */
void CSasVoices::f_10cec4()
{
    int i;

    for (i = 0; pitchMask; i++) {
        if (pitchMask & 1)
            f_11af8c(i, voice[i].pitch);
        pitchMask >>= 1;
    }
}

/* @implements 0x10cf38 us _ZN10CSasVoices8f_10cf38Ei
   WHAT IT DOES: Marks voice ch for a key off. */
void CSasVoices::f_10cf38(int ch)
{
    offMask |= 1 << ch;
}

/* @implements 0x10cf50 us _ZN10CSasVoices8f_10cf50Ei
   WHAT IT DOES: Meant to unmark voice ch for a key off; as written (with ! for ~) it clears
   the whole mask but bit 0. */
void CSasVoices::f_10cf50(int ch)
{
    offMask &= !(1 << ch);
}

/* @implements 0x10cf70 us _ZN10CSasVoices8f_10cf70Ev
   WHAT IT DOES: Keys off every marked voice. */
void CSasVoices::f_10cf70()
{
    int i;

    for (i = 0; offMask; i++) {
        if (offMask & 1)
            f_11aeb0(i);
        offMask >>= 1;
    }
}

/* @implements 0x10cfd4 us _ZN10CSasVoices8f_10cfd4Ei
   WHAT IT DOES: Marks voice ch for a key-off check. */
void CSasVoices::f_10cfd4(int ch)
{
    endMask |= 1 << ch;
}

/* @implements 0x10cfec us _ZN10CSasVoices8f_10cfecEv
   WHAT IT DOES: Keys off every marked voice that is playing; starting voices stay marked for
   the next check. */
void CSasVoices::f_10cfec()
{
    unsigned int keep = 0;
    int i;

    for (i = 0; endMask; i++) {
        if (endMask & 1) {
            if (voice[i].state == 2)
                f_11aeec(i);
            else if (voice[i].state == 1)
                keep |= 1 << i;
        }
        endMask >>= 1;
    }
    endMask = keep;
}

extern "C" {
/* @implements 0x10d0a4 us f_10d0a4
   WHAT IT DOES: Creates the voice table. */
void f_10d0a4(void)
{
    D_27f16c = new CSasVoices;
    D_27f16c->f_10c948();
}

/* @implements 0x10d0d0 us f_10d0d0
   WHAT IT DOES: Clears the voice table. */
void f_10d0d0(void)
{
    D_27f16c->f_10c948();
}

/* @implements 0x10d0f4 us f_10d0f4
   WHAT IT DOES: Deletes the voice table. */
void f_10d0f4(void)
{
    D_27f16c->f_10c9fc();
    delete D_27f16c;
    D_27f16c = 0;
}

/* @implements 0x10d140 us f_10d140
   WHAT IT DOES: The per frame voice update. */
int f_10d140(void)
{
    return D_27f16c->f_10ca04();
}

/* @implements 0x10d160 us f_10d160
   WHAT IT DOES: Returns voice ch, of the extra voices when a is set. */
SasVoice *f_10d160(int a, int ch)
{
    return D_27f16c->f_10cd34(a, ch);
}

/* @implements 0x10d18c us f_10d18c
   WHAT IT DOES: Returns the voice playing this key. */
int f_10d18c(int a, int key)
{
    return D_27f16c->f_10cd5c(a, key);
}

/* @implements 0x10d1b8 us f_10d1b8
   WHAT IT DOES: Returns a free voice. */
int f_10d1b8(int a)
{
    return D_27f16c->f_10cd98(a);
}

/* @implements 0x10d1dc us f_10d1dc
   WHAT IT DOES: Copies every voice's state out. */
void f_10d1dc(char *out)
{
    D_27f16c->f_10ce80(out);
}

/* @implements 0x10d204 us f_10d204
   WHAT IT DOES: Advances the voice states from what is sounding. */
void f_10d204(void)
{
    D_27f16c->f_10ce10();
}

/* @implements 0x10d228 us f_10d228
   WHAT IT DOES: Marks voice ch for a pitch update. */
void f_10d228(int ch)
{
    D_27f16c->f_10ceac(ch);
}

/* @implements 0x10d250 us f_10d250
   WHAT IT DOES: Sets the pitch of every marked voice. */
void f_10d250(void)
{
    D_27f16c->f_10cec4();
}

/* @implements 0x10d274 us f_10d274
   WHAT IT DOES: Marks voice ch for a key off. */
void f_10d274(int ch)
{
    D_27f16c->f_10cf38(ch);
}

/* @implements 0x10d29c us f_10d29c
   WHAT IT DOES: Unmarks voice ch for a key off (see 0x10cf50). */
void f_10d29c(int ch)
{
    D_27f16c->f_10cf50(ch);
}

/* @implements 0x10d2c4 us f_10d2c4
   WHAT IT DOES: Keys off every marked voice. */
void f_10d2c4(void)
{
    D_27f16c->f_10cf70();
}

/* @implements 0x10d2e8 us f_10d2e8
   WHAT IT DOES: Marks voice ch for a key-off check. */
void f_10d2e8(int ch)
{
    D_27f16c->f_10cfd4(ch);
}

/* @implements 0x10d310 us f_10d310
   WHAT IT DOES: Keys off every marked voice that is playing. */
void f_10d310(void)
{
    D_27f16c->f_10cfec();
}
}
