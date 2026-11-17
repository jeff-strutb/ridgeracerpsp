/* The stream channels (retail 0x110e2c to 0x111900): the two disc stream channels of the sound
   library, 196 bytes each (D_291980, the count in D_291a44), with the UMD check callback that
   sets D_291a0c, the channel's three 64-byte buffers, and the per-channel 12-byte slot records
   (D_291a48) that hold a start time. Errors: 0x8000000a for a bad channel, 0x8000000c for a
   channel in the wrong state, 0x80000000 for a count out of range. */

struct Chan {
    int m0;
    int m4;
    unsigned char m8;
    unsigned char m9;
    char m10[2];
    int m12;
    unsigned short state;
    unsigned short m18;
    short m20;
    short m22;
    int m24;
    int m28;
    int m32;
    int m36;
    char m40[12];
    int m52;
    int m56;
    int m60;
    char m64[36];
    int m100;
    int m104;
    char m108[24];
    int m132;
    char m136[4];
    int m140;
    int m144;
    int m148;
    char m152[20];
    int m172;
    float m176;
    char m180[4];
    void *m184;
    void *m188;
    void *m192;
};

struct Info {
    int m0;
    int m4;
    unsigned char m8;
    unsigned char m9;
    char m10[2];
    int m12;
    short m16;
    short m18;
    short m20;
    short m22;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    char m44[4];
};

struct Slot {
    float m0;
    float m4;
    int m8;
};

extern struct Chan D_291980[];
extern int D_291a44;
extern int D_291a0c;
extern struct Slot D_291a48[];
extern int D_281ec0;
extern const float D_1b2e78;
extern const float D_1b2e7c;
extern const float D_1b2e80;
extern const float D_1b2e84;
extern const float D_1b2e88;
extern const float D_1b2e8c;

int f_16e978(void);
int f_16e5c0(const char *, int (*)(int, int, void *), void *);
int f_16e980(int);
void *f_125c4c(unsigned int align, unsigned int size);
void free(void *p);
int f_111b18(int ch, int a1, int a2, int a3);
int f_111e04(void);
void f_111f18(int ch, int a1);
int f_110f58(int ch, int a1, int a2);
int f_111228(int ch);
int f_111030(int ch);
int f_111900(int ch, int a1);

static __inline__ int badch(int ch)
{
    return (ch >= D_291a44) | (ch < 0);
}

/* @implements 0x110e2c us f_110e2c
   WHAT IT DOES: UMD callback: sets D_291a0c to 1 when the disc is not busy (flags 0x30 clear), else 0. */
int f_110e2c(int a, int flags, void *p)
{
    if (flags & 0x30)
        D_291a0c = 0;
    else
        D_291a0c = 1;
    return 0;
}

/* @implements 0x110e54 us f_110e54
   WHAT IT DOES: Sets up n (below 2) disc stream channels, checks the UMD and registers the UMD callback. */
int f_110e54(int n)
{
    int i;
    if (n >= 2)
        return 0x80000000;
    D_291a44 = n;
    for (i = 0; i < n; i++) {
        D_291980[i].state = 0;
        D_291980[i].m104 = -1;
        D_291980[i].m176 = D_1b2e78;
    }
    if (f_16e978())
        D_291980[0].m140 = 0;
    else
        D_291980[0].m140 = 1;
    D_281ec0 = f_16e5c0("UMD Check", f_110e2c, 0);
    f_16e980(D_281ec0);
    return 0;
}

/* @implements 0x110f10 us f_110f10
   WHAT IT DOES: Stops channel 0 slot and frees the three buffers of channel 0. */
int f_110f10(void)
{
    f_111030(-1);
    free(D_291980[0].m192);
    free(D_291980[0].m184);
    free(D_291980[0].m188);
    return 0;
}

/* @implements 0x110f58 us f_110f58
   WHAT IT DOES: Starts stream ch from file name with id: a busy stream is stopped (0x111030),
   reset to full volume and stepped once (0x111e04) first; the slot's fade count is cleared
   and the file is opened (0x111b18), whose result is returned. 0x8000000a for a bad channel. */
int f_110f58(int ch, int name, int id)
{
    struct Chan *c;

    if (badch(ch))
        return 0x8000000a;
    c = &D_291980[ch];
    if (c->state != 0) {
        f_111030(ch);
        c->m176 = D_1b2e7c;
        f_111e04();
    }
    D_291a48[ch].m8 = 0;
    return f_111b18(ch, name, id, 0);
}

/* @implements 0x111030 us f_111030
   WHAT IT DOES: Moves a playing channel (state 1..4) to state 5 (all channels when ch is -1) and clears its slot word. */
int f_111030(int ch)
{
    int i;
    if (ch == -1) {
        for (i = 0; i < D_291a44; i++)
            if (D_291980[i].state)
                D_291980[i].state = 5;
    } else {
        if (D_291980[ch].state)
            D_291980[ch].state = 5;
    }
    D_291a48[ch].m8 = 0;
    return 0;
}

/* @implements 0x1110c8 us f_1110c8
   WHAT IT DOES: Advances channel ch's state machine; with a1 zero it moves a state-4 channel on to 3 or 1. */
int f_1110c8(int ch, int a1)
{
    if (a1) {
        if ((unsigned short)(D_291980[ch].state - 1) < 3) {
            D_291980[ch].state = 4;
            f_111f18(ch, a1);
        }
    } else {
        if (D_291980[ch].state == 4) {
            if (D_291980[0].m100 < 6) {
                D_291980[ch].state = 1;
            } else {
                D_291980[ch].state = 3;
                f_111f18(ch, a1);
            }
        }
    }
    return 0;
}

/* @implements 0x111160 us f_111160
   WHAT IT DOES: Starts channel ch: stops it first if it is busy, clears its slot word, then calls 0x111b18. */
int f_111160(int ch, int a1, int a2)
{
    int r = 0x8000000a;
    if (!badch(ch)) {
        if (D_291980[ch].state) {
            f_111030(ch);
            f_111e04();
        }
        D_291a48[ch].m8 = 0;
        r = f_111b18(ch, a1, a2, 1);
    }
    return r;
}

/* @draft 0x111228 us f_111228
   WHAT IT DOES: Marks a channel state 2 as 3 (all channels when ch is -1, which sets every channel to 3). 
   Remaining difference: block order only. Retail keeps the state 3 store on the fall-through
   of a bne and puts the all-channels loop last; here the store block (state == 2) is placed
   out of line, as the equality-compare prediction makes it unlikely. */
int f_111228(int ch)
{
    int i;
    int r;

    if (ch != -1) {
        r = 0x8000000c;
        if (D_291980[ch].state != 2)
            return r;
        D_291980[ch].state = 3;
        r = 0;
    } else {
        for (i = 0; i < D_291a44; i++)
            D_291980[i].state = 3;
        r = 0;
    }
    return r;
}

/* @implements 0x1112a8 us f_1112a8
   WHAT IT DOES: Empty stub that reports success. */
int f_1112a8(void)
{
    return 0;
}

/* @draft 0x1112b0 us f_1112b0
   WHAT IT DOES: Fades stream ch out over ms: a stream still opening or starting (state 1 or
   2) is stopped at once (state 5); a playing one (state 3 or 4) gets a fade from its volume
   to 0 in its slot. Ch -1 stops every stream not in state 2. 0x8000000c when nothing faded.
   Remaining difference: register choice. The result gets a0 here (so ch is copied to a2)
   where retail gives it v1 and keeps ch in a0. Block order and statements match. */
int f_1112b0(int ch, int ms)
{
    struct Chan *c;
    int i;

    if (ch == -1) {
        for (i = 0; i < D_291a44; i++) {
            if (D_291980[i].state != 2)
                f_111030(i);
        }
        return 0;
    }
    c = &D_291980[ch];
    if ((unsigned short)(c->state - 1) < 2) {
        f_111030(ch);
        c->state = 5;
        return 0x8000000c;
    }
    if ((unsigned short)(c->state - 3) < 2) {
        float v = c->m176;

        D_291a48[ch].m8 = ms;
        D_291a48[ch].m0 = v;
        D_291a48[ch].m4 = (0.0f - v) / (float)ms;
        return 0;
    }
    return 0x8000000c;
}

/* @draft 0x1113e4 us f_1113e4
   WHAT IT DOES: Fills info with stream ch's state: the disc stream's length and loop words
   (also kept in the channel), its format bytes, volume (0..127), state, pan, position and
   the played time from 0x111900; returns the channel's sub-state, 0x8000000a for a bad
   channel.
   Remaining difference: retail reads the channel's fields ahead of the stores into info (the
   +16..+39 block through its own base register, t4), as if read into locals or copied by an
   inline on a sub-record; here each store follows its load. */
int f_1113e4(int ch, struct Info *info)
{
    struct Chan *c;
    int len;
    int vol;

    if (badch(ch))
        return 0x8000000a;
    c = &D_291980[ch];
    len = D_291980[0].m52;
    c->m0 = len;
    info->m0 = len;
    vol = (int)(c->m176 * D_1b2e80);
    c->m4 = D_291980[0].m56;
    info->m4 = c->m4;
    info->m9 = c->m9;
    info->m12 = c->m12;
    info->m8 = c->m8;
    c->m20 = vol;
    info->m16 = c->state;
    info->m18 = c->m18;
    info->m22 = c->m22 + c->m172;
    info->m24 = c->m24;
    info->m28 = c->m28;
    info->m32 = c->m32;
    info->m36 = c->m36;
    info->m20 = vol;
    info->m40 = f_111900(ch, len);
    return c->m100;
}

/* @implements 0x1114f0 us f_1114f0
   WHAT IT DOES: Sets channel ch's flag byte and its two 32-bit limits (0xc000 and 0x40000). */
int f_1114f0(int ch, int a1, int a2, int flag)
{
    int r = 0x8000000a;
    if (!badch(ch)) {
        D_291980[ch].m148 = 0x40000;
        D_291980[ch].m144 = 0xc000;
        D_291980[ch].m9 = flag;
        r = 0;
    }
    return r;
}

/* @implements 0x11154c us f_11154c
   WHAT IT DOES: Empty stub that reports success. */
int f_11154c(void)
{
    return 0;
}

/* @implements 0x111554 us f_111554
   WHAT IT DOES: Allocates channel 0's three 64-byte buffers (sizes from its two size words). */
int f_111554(void)
{
    D_291980[0].m192 = f_125c4c(64, D_291980[0].m148);
    D_291980[0].m184 = f_125c4c(64, D_291980[0].m144);
    D_291980[0].m188 = f_125c4c(64, D_291980[0].m144);
    return 0;
}

/* @implements 0x1115ac us f_1115ac
   WHAT IT DOES: Sets channel ch's m32 and m132 to size/28 in 4096-byte steps, unless it is playing. */
int f_1115ac(int ch, unsigned int size)
{
    int v;
    if (badch(ch))
        return 0x8000000a;
    if (D_291980[ch].state == 2 || D_291980[ch].state == 3)
        return 0x80000000;
    v = (int)((size / 28) << 4);
    v = v / 4096 * 4096;
    D_291980[ch].m132 = v;
    D_291980[ch].m32 = v;
    return 0;
}

/* @implements 0x111644 us f_111644
   WHAT IT DOES: Stores a halfword into channel ch's m18. */
int f_111644(int ch, int v)
{
    int r = 0x8000000a;
    if (!badch(ch)) {
        D_291980[ch].m18 = v;
        r = 0;
    }
    return r;
}

/* @implements 0x111690 us f_111690
   WHAT IT DOES: Stores a sign-extended halfword value into channel ch's m12. */
int f_111690(int ch, int v)
{
    int r = 0x8000000a;
    if (!badch(ch)) {
        D_291980[ch].m12 = (short)v;
        r = 0;
    }
    return r;
}

/* @implements 0x1116e0 us f_1116e0
   WHAT IT DOES: Returns 0x8000000a for a bad channel, else 0. */
int f_1116e0(int ch)
{
    return badch(ch) ? 0x8000000a : 0;
}

/* @implements 0x111718 us f_111718
   WHAT IT DOES: Stores value v (in -128..128) into channel ch's m172; errors otherwise. */
int f_111718(int ch, int v)
{
    int r;
    if (badch(ch)) {
        r = 0x8000000a;
    } else if ((unsigned)(v + 128) >= 257) {
        r = 0x80000000;
    } else {
        D_291980[ch].m172 = v;
        r = 0;
    }
    return r;
}

/* @implements 0x111774 us f_111774
   WHAT IT DOES: Stores a float (clamped at zero) into channel ch's m176. */
int f_111774(int ch, float v)
{
    int r = 0x8000000a;
    if (!badch(ch)) {
        if (v < 0.0f)
            v = 0.0f;
        D_291980[ch].m176 = v;
        r = 0;
    }
    return r;
}

/* @implements 0x1117d0 us f_1117d0
   WHAT IT DOES: Calls 0x110f58, then stores slot ch's record: size a3, a 0 word and 1/(float)a3 as a float. */
int f_1117d0(int ch, int a1, int a2, int a3)
{
    if (badch(ch))
        return 0x8000000a;
    f_110f58(ch, a1, a2);
    D_291a48[ch].m8 = a3;
    D_291a48[ch].m0 = 0;
    D_291a48[ch].m4 = D_1b2e84 / (float)a3;
    return 0;
}

/* @implements 0x111868 us f_111868
   WHAT IT DOES: Calls 0x111228 for ch, then stores slot ch's record: a1, a 0 word and D/(float)a1. */
int f_111868(int ch, int a1)
{
    if (badch(ch))
        return 0x8000000a;
    f_111228(ch);
    D_291a48[ch].m8 = a1;
    D_291a48[ch].m0 = 0;
    D_291a48[ch].m4 = D_1b2e88 / (float)a1;
    return 0;
}

/* @implements 0x111900 us f_111900
   WHAT IT DOES: Returns a scaled duration for a 1-state channel from channel 0's m56 word; 0 for a short one. */
int f_111900(int ch, int a1)
{
    int r = 0x8000000c;

    if (D_291980[ch].state >= 2 && D_291980[0].m56 > 0) {
        r = 0;
        if (a1 >= 17)
            r = (int)((float)(a1 / 16 * 28) / (float)D_291980[0].m56 * D_1b2e8c);
    }
    return r;
}
