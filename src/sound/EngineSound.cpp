/* A car's engine sound (retail 0x0c80a8 to 0x0ca044): one object per car on the grid
   (D_249330, 1904 bytes each). It owns two rows of sound slots, each slot one playing
   voice: row 0 holds the engine samples, row 1 the tyre, wall and other surface noises.
   A slot is started as a plain 2D voice for the player's own car in the near camera
   views, and as a 3D voice placed at the car (with a velocity from its last position)
   otherwise. At most four voices start in one frame. */

/* A voice handle of the sound library (see NuSound.c). */
struct SoundReq {
    int ch;
    unsigned short idx;
    unsigned short bank;
    int key;
    int m12;
    float vol;
};

extern "C" {
int f_10c360(unsigned short name, unsigned short tone, int bus, short a, short b, SoundReq *voice, float vol);
int f_10c5a4(SoundReq *r);
int f_10c6fc(SoundReq *r, short pan, short pitch, float vol);
int f_10c810(short pitch, SoundReq *r);
int f_10c86c(SoundReq *r);
int f_113c60(unsigned short name, unsigned short idx, signed char bus, short a, short b, float vol, void *pos, void *vel, void *x, SoundReq *r);
int f_113ff8(void *pos, void *vel, void *x, SoundReq *r);
void f_10ddac(int, int, float);
int f_114048(int unused, short a, void *pos, void *vel, void *x, SoundReq *r, float vol);
int f_1140f4(SoundReq *r);
}

/* A vector of three floats. */
struct Vec3 {
    Vec3() {}
    Vec3(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    float x, y, z;
};

/* A position as stored in an object (no constructor, so the engine sounds need no
   construction at startup). */
struct Pos3 {
    float x, y, z;
};

/* A vector of four floats. */
struct Vec4 {
    Vec4() {}
    Vec4(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
    float x, y, z, w;
    float f_09b4dc(const Vec4 &b) const;
};

/* A pair of words. */
struct Pair {
    int a;
    int b;
};

/* One sound slot (52 bytes). The first slot's head words double as the wall-hit state. */
struct Slot {
    union {
        float f0;
        float *tab0;    /* the sample's two curves (slots 1.. of a row hold them) */
    };
    union {
        struct {
            short s4;
            short s6;
        };
        float *tab1;
    };
    int i8;
    int state;      /* 0 free, 1 playing 2D, 2 playing 3D */
    SoundReq req;
    int m36[4];
};

/* An engine sample's settings (the course sound data). */
struct Sample {
    unsigned short name;
    unsigned char b2;
    unsigned char b3;
    unsigned char b4;
    char m5;
    unsigned char b6;
    unsigned char b7;
    char m8[80];
    unsigned short u88;
    unsigned char b90;
    char m91;
    unsigned char b92;
    unsigned char b93;
    unsigned short u94;
};

/* The sample table of a car or of the common sounds: a count, then the samples. */
struct SampleSet {
    short count;
    char m2[14];
    Sample s[1];
};

/* The two curves of an engine sample, in a table record. */
struct EmitEnt {
    int a;
    int b;
    char m8[44];
};

/* A sound table record (836 bytes): the sample set, then the curves of its samples. */
struct EmitRec {
    SampleSet *set;
    char m4[44];
    EmitEnt e[15];
    char m828[8];
};

extern EmitRec D_24ecc0[];
extern EmitRec D_251a78;

/* The sound system, as far as the voices go. */
struct CSound {
    void f_01c618(SoundReq *r);
};
extern CSound D_23bb4c;

/* The game database table of the car settings. */
struct CTable {
    char *f_0368e8(const char *field, char *rec, int a, int i);
};
extern CTable D_240740;
extern int D_24063c;
extern const int D_1a211c[];
extern "C" {
int f_0f6b90();
void *memcpy(void *d, const void *s, unsigned int n);
}


/* The camera the listener follows. */
struct CCamera {
    char m0[612];
    float m612;
    char m616[44];
    int m660;
    int m664;
    char m668[76];
    float m744;
};

/* The race view state read here. */
struct CRaceView {
    int m0;
    int m4;
    char m8[8];
    short m16;
    char m18[70];
    signed char *m88;
    signed char *m92;
    signed char *m96;
    char m100[4];
    signed char *m104;
    signed char *m108;
    char m112[8];
    signed char *m120[2];
    signed char *m128[2];
    CCamera *cam;
    Vec4 m144;
    char m160[392];
    signed char *m552[8];
};

/* The race settings this file reads. */
struct CRaceInfo {
    int m0[4];
    int mode;
    int m20;
    char m24[24];
    int m48;
    char m52[4];
    int m56;
};
extern CRaceInfo *D_2407fc;

/* A car, as far as its engine sound reads it. */
struct EngCar {
    char m0[76];
    int m76;
    int m80;
    char m84[8];
    Pair m92;
    char m100[28];
    int m128;
    char m132[12];
    Vec4 pos144;
    char m160[32];
    float m192;
    char m196[1548];
    float m1744;
    float m1748;
    int m1752;
    float m1756;
    char m1760[4];
    Pos3 pos;
    float m1776;
    char m1780[12];
    float m1792;
    int m1796;
    char m1800[32];
    float m1832;
    char m1836[308];
    float m2144;
    float m2148;
    char m2152[8];
    float m2160;
    char m2164[468];
    int m2632[2];
};

/* An angle, wrapped by f_099b98. */
union Angle {
    float f;
};

extern CRaceView D_23be80;

extern "C" {
float *f_099b98(float *a);
int f_0828c4(char *buf, int line, const char *fmt, ...);
}
extern char D_24517c[];
extern unsigned char D_1d4a48[];
extern unsigned char D_1d4a50[];
extern unsigned char D_1d4a58[];

class CEngineSound {
public:
    EngCar *car;
    int id;
    int m8;
    unsigned int m12;
    int m16[8];
    int m48;
    int m52;
    int m56;
    int m60[4];
    int m76;
    int m80;
    short m84;
    short m86;
    short m88;
    short m90;
    int m92[2];
    char m100[8];
    float m108;
    int m112;
    char m116[12];
    Pos3 pos;
    float m140;
    float level;
    float m148;
    int count;
    short m156;
    short m158;
    int m160;
    short m164;
    short m166;
    int m168;
    float m172;
    float m176;
    float m180;
    int m184;
    int m188;
    Slot slot[2][16];
    char m1856[8];
    int m1864;
    int m1868;
    int m1872;
    char m1876[12];
    Pos3 last;
    float m1900;

    int f_0c80a8(float vol, unsigned short name, unsigned char idx, short a, short b, int i, int j);
    int f_0c827c(float vol, unsigned short name, unsigned char idx, short a, short b, int i, int j);
    int f_0c8360(int i, int j);
    int f_0c84a4(float vol, short pan, short pitch, int i, int j, int force);
    int f_0c8618(int i, int j);
    float f_0c8694(int sel, Sample *s);
    void f_0c8bf4(int row, int add, int flag);
    void f_0c9a80();
    void f_0c9b24(short mute);
    void f_0c9b54();
    float f_0c801c(int x, float *tab);
    float f_0c8704(int status, Sample *s, int i, short *pan);
    void f_0c8fec(int c);
    void f_0c9310(int flags);
    void f_0c9bd8();
    void f_0c9d2c();
    void f_0c9e6c();
    ~CEngineSound() {}
};

/* @draft 0x0c80a8 us _ZN12CEngineSound8f_0c80a8E
   WHAT IT DOES: Starts a voice in slot [i][j] if the slot is free and fewer than four
   voices started this frame: 2D in the near views of the player's car, 3D at the car
   otherwise. Returns 1 when it started. 
   DRAFT: register allocation and the 3D branch's address computation differ (448 vs 468 bytes). */
int CEngineSound::f_0c80a8(float vol, unsigned short name, unsigned char idx, short a, short b, int i, int j)
{
    int ret = 0;

    if (count++ < 4) {
        Slot *s = &slot[i][j];

        if (s->state == 0) {
            if ((m12 < 2 || m12 == 3) && (m8 & 1)) {
                int r = f_10c360(name, idx, 0, a, b, &s->req, vol);

                if (r == 0 || r == (int)0x80000018) {
                    s->state = 1;
                    ret = 1;
                }
            } else {
                Vec3 p(pos.x, pos.y, pos.z);
                Vec3 v(pos.x - last.x, pos.y - last.y, pos.z - last.z);
                Vec3 x(0.0f, 0.0f, 0.0f);
                int r = f_113c60(name, idx, 0, 0, b, vol, &p, &v, &x, &slot[i][j].req);

                if (r == 0 || r == (int)0x80000018) {
                    slot[i][j].state = 2;
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

/* @draft 0x0c827c us _ZN12CEngineSound8f_0c827cE
   WHAT IT DOES: Starts a 2D voice in slot [i][j] on bus 1 (row 0) or 0, or bus 3 for a
   car other than the player's. Returns 1 when it started, -1 when four voices already
   started this frame, 0 when the slot is busy, else the library's error. 
   DRAFT: the result and status variables are allocated differently (t1/t5 swap) and the bus select is scheduled later. */
int CEngineSound::f_0c827c(float vol, unsigned short name, unsigned char idx, short a, short b, int i, int j)
{
    int ret = -1;
    int r = 0;

    if (count++ < 4) {
        Slot *s = &slot[i][j];
        int bus = i == 0;

        if ((m8 & 1) == 0)
            bus = 3;
        if (s->state == 0) {
            r = f_10c360(name, idx, bus, a, b, &slot[i][j].req, vol);
            if (r == 0 || r == (int)0x80000018) {
                s->state = 1;
                r = 1;
            }
        }
        ret = r;
    }
    return ret;
}

/* @draft 0x0c8360 us _ZN12CEngineSound8f_0c8360Eii
   WHAT IT DOES: Stops the voice in slot [i][j]; a 3D voice of the player's car in the
   near views is first moved far away. Returns 1 when one was stopped. 
   DRAFT: the slot address is computed once instead of retail's two forms; the 3D far-away move block placement differs. */
int CEngineSound::f_0c8360(int i, int j)
{
    Slot *s = &slot[i][j];

    if (s->state == 1) {
        f_10c5a4(&s->req);
        s->state = 0;
        return 1;
    }
    if (s->state == 2) {
        if (m164 != 0 && (m8 & 1)) {
            Vec3 p(-30000.0f, -30000.0f, -30000.0f);
            Vec3 v(0.0f, 0.0f, 0.0f);
            Vec3 x(0.0f, 0.0f, 0.0f);

            f_113ff8(&p, &v, &x, &slot[i][j].req);
        }
        f_1140f4(&slot[i][j].req);
        slot[i][j].state = 0;
        return 1;
    }
    return 0;
}

/* @draft 0x0c84a4 us _ZN12CEngineSound8f_0c84a4E
   WHAT IT DOES: Updates the voice in slot [i][j]: pan, pitch and volume of a 2D voice;
   the pitch alone of a quiet 3D voice of the player's car in the near views, otherwise
   the 3D voice's position, velocity, pitch and volume. Returns 1 when the slot plays. 
   DRAFT: the 3D velocity select is laid out differently (388 vs 372 bytes). */
int CEngineSound::f_0c84a4(float vol, short pan, short pitch, int i, int j, int force)
{
    CRaceView *g = &D_23be80;
    int state = slot[i][j].state;

    if (state == 1) {
        f_10c6fc(&slot[i][j].req, pan, pitch, vol);
        return 1;
    }
    if (state == 2) {
        CCamera *cam = g->cam;

        if (force || level < 20.0f || cam->m664) {
            Vec3 p(pos.x, pos.y, pos.z);
            Vec3 v;
            Vec3 x(0.0f, 0.0f, 0.0f);

            if (cam->m664)
                v = Vec3(0.0f, 0.0f, 0.0f);
            else
                v = Vec3(pos.x - last.x, pos.y - last.y, pos.z - last.z);
            f_114048(0, pitch, &p, &v, &x, &slot[i][j].req, vol);
        } else {
            f_10c810(pitch, &slot[i][j].req);
        }
        return 1;
    }
    return 0;
}

/* @draft 0x0c8618 us _ZN12CEngineSound8f_0c8618Eii
   WHAT IT DOES: Tests whether the voice in slot [i][j] has ended; frees the slot and
   returns 1 if so, else -1. 
   DRAFT: retail keeps the result in a3 and the call on the fall-through path; this keeps it in s1. */
int CEngineSound::f_0c8618(int i, int j)
{
    Slot *s = &slot[i][j];
    int ret = -1;

    if (s->state) {
        ret = -1;
        if (f_10c86c(&slot[i][j].req) == 1) {
            s->state = 0;
            ret = 1;
        }
    }
    return ret;
}

/* @implements 0x0c8694 us _ZN12CEngineSound8f_0c8694EiP6Sample
   WHAT IT DOES: The volume of a sample for the view (mode 3 and 5 use the far volume):
   the view's percentage times the sample's own percentage. Selector 11 uses the second
   mode word. */
float CEngineSound::f_0c8694(int sel, Sample *s)
{
    int mode;
    float v;

    if (sel == 11)
        mode = m1872;
    else
        mode = m12;
    if (mode == 3)
        v = s->b4 / 100.0f;
    else if (mode == 5)
        v = s->b4 / 100.0f;
    else
        v = s->b3 / 100.0f;
    return v * (s->b92 / 100.0f);
}

/* @draft 0x0c8704 us _ZN12CEngineSound8f_0c8704EiP6SampleiPs
   WHAT IT DOES: The strength (0 to 1) of a slot's sound by the sample's type (b2) and the
   engine state. Types 1 to 3 ramp on the engine's gear counters between the sample's two
   limits (up, down, up on the second counter); 6 and 7 follow the gear change; 8 handles the
   wheel noises (slot 3 and 5) with the car's flag; 9 to 22 handle the wall and surface
   sounds: the pan offset (written to *pan) for the two sides, the speed ramps, the revs
   and the skid hold. Returns the strength.
   DRAFT: the switch lays out as retail (two jump tables) but the blocks are scheduled differently (1204 vs 1264 bytes, 291 of 316 words differ); the m84/m88 stores to the sample table come out as lbu where retail loads the halfword, and the i == 7 test of type 8 is not reproduced. */
float CEngineSound::f_0c8704(int status, Sample *s, int i, short *pan)
{
    float r = 0;
    int t = s->b2;

    *pan = 0;
    switch (t) {
    case 0:
        r = 1.0f;
        break;
    case 1:
        if (s->b6 < m48) {
            if (m48 < s->b7)
                r = (float)(m48 - s->b6) / (float)(s->b7 - s->b6);
            else
                r = 1.0f;
        }
        break;
    case 2:
        if (!(s->b6 < m48)) {
            r = 1.0f;
        } else if (m48 < s->b7) {
            r = 1.0f - (float)(m48 - s->b6) / (float)(s->b7 - s->b6);
        }
        break;
    case 3:
        if (s->b6 < m52) {
            if (m52 < s->b7)
                r = (float)(m52 - s->b6) / (float)(s->b7 - s->b6);
            else
                r = 1.0f;
        }
        break;
    case 4:
    case 5:
        break;
    case 6:
        if ((m56 == m1864 + 1) | (status == 0))
            r = 1.0f;
        break;
    case 7:
        if ((m56 == m1864 - 1) | (status == 0))
            r = 1.0f;
        break;
    case 8:
        if (i == 5) {
            r = m108;
            if (car->m1796)
                r = 0;
            D_251a78.set->s[5].b93 = m88;
        } else if (i < 6) {
            if (i == 3) {
                r = 1.0 - m108;
                if (car->m1796)
                    r = 0;
                D_251a78.set->s[3].b93 = m84;
            }
        }
        break;
    default: {
        int want;

        switch (t) {
        case 9:
            want = -1;
            break;
        case 10:
            if (m188 == 1) {
                *pan = m184 + 64;
                r = slot[0][0].f0 * D_23be80.m92[m112] / 75.0f;
            }
            if (m188 == 2) {
                *pan = m184 - 64;
                r = slot[0][0].f0 * D_23be80.m88[m112] / 75.0f;
            }
            return r;
        case 11: {
            CRaceView *g = &D_23be80;
            int k = m112;

            if (g->m108[k] >= 80 && g->m104[k] >= 80) {
                r = (float)m188 / 80.0f;
            } else {
                if (m188 == 1) {
                    *pan = m184 + 64;
                    r = slot[0][0].f0 * g->m108[k] / 60.0f;
                }
                if (m188 == 2) {
                    *pan = m184 - 64;
                    r = slot[0][0].f0 * g->m104[k] / 60.0f;
                }
            }
            return r;
        }
        case 12:
            want = 1;
            break;
        case 13:
            want = 2;
            break;
        case 14:
            want = 3;
            break;
        case 15:
            want = 4;
            break;
        case 16:
            want = 5;
            break;
        case 17:
            want = 6;
            break;
        case 18:
            want = 7;
            break;
        case 19:
            if (!(s->b6 < m48) && s->b6 < m1868)
                return 1.0f;
            if (status)
                return r;
            return 1.0f;
        case 20:
            if (status == 0) {
                r = m180;
                if (m176 + 0.05f < -car->m1832)
                    m180 = 0;
            } else if (!(-car->m1832 < m176 - 0.2f)) {
                m180 = 0;
            } else if (!(0.8f < m176)) {
                m180 = 0;
            } else {
                float v = m176;

                if (1.0f < v)
                    v = 1.0f;
                m180 = v;
                r = v;
            }
            m176 = -car->m1832;
            return r;
        case 21:
            return car->m1792;
        default:
            return r;
        }
        if (m56 == want)
            return 1.0f;
        break;
    }
    }
    return r;
}

/* @draft 0x0c8bf4 us _ZN12CEngineSound8f_0c8bf4Eiii
   WHAT IT DOES: Steps a row of the sound slots (row 0 the engine samples, row 1 the common
   ones; add counts the frames a slot waited, flag allows a new voice). For every sample it
   skips the ones this car does not use, gets the sample's strength (f_0c8704), scales it by the
   view's volume and the engine's curve of the revs (f_0c801c) and then starts the voice when
   the slot is free, stops it when it has gone quiet, or updates it. For row 0 it ends by
   saving the state and the position for the next frame.
   DRAFT: the control flow and calls are those of retail, but the register allocation differs: retail keeps the row test in a stack slot and the sample offsets as two stepping registers, this build uses fewer registers (996 vs 1016 bytes). */
void CEngineSound::f_0c8bf4(int row, int add, int flag)
{
    short pan = 0;
    int n, i;
    int r1 = row != 0;

    if (row)
        n = D_251a78.set->count;
    else
        n = D_24ecc0[id].set->count;
    for (i = 0; i < n; i++) {
        float vol = 0;
        Sample *smp;
        int idx;

        if ((m8 & 2) && r1 && i != 5 && i != 9)
            continue;
        if ((m8 & 1) && r1 && i == 9)
            continue;
        if (row)
            smp = &D_251a78.set->s[i];
        else
            smp = &D_24ecc0[id].set->s[i];
        if (slot[0][0].s4 != 2) {
            int st = -1;

            if (slot[row][i].req.key)
                st = f_0c8618(row, i);
            float a = f_0c8704(st, smp, i, &pan);

            if (!(a < 0.001f)) {
                float b = f_0c8694(m12, smp);

                if (!(b < 0.001f)) {
                    if (smp->b90)
                        idx = m80;
                    else
                        idx = m76;
                    f_0c801c(idx, slot[row][i + 1].tab1);
                    float c = f_0c801c(idx, slot[row][i + 1].tab0);

                    idx = (short)((int)c + smp->u94);
                    if (smp->b2 == 21) {
                        if (slot[row][i].state) {
                            idx = (short)(idx + m168);
                            m168++;
                        } else {
                            m168 = 0;
                        }
                    }
                    vol = c * a * b * m148;
                }
            }
        }
        if (slot[row][i].state == 0) {
            if (0.1f < vol) {
                if (flag && slot[row][i].i8 >= smp->u88) {
                    if (f_0c80a8(vol, smp->name, smp->b93, pan, idx, row, i))
                        slot[row][i].i8 = 0;
                }
            } else {
                slot[row][i].i8 += add;
            }
        } else {
            if (vol < 0.001f)
                f_0c8360(row, i);
            else
                f_0c84a4(vol, pan, idx, row, i, flag);
        }
    }
    if (row == 0) {
        m1868 = m48;
        m1864 = m56;
        *(Vec4 *)&last = *(Vec4 *)&pos;
    }
}

/* @draft 0x0c8fec us _ZN12CEngineSound8f_0c8fecEi
   WHAT IT DOES: Sets the engine sound up for a car: takes the curves of the car's engine
   samples and of the common samples into the slots, clears the slots and the voices, takes
   the view mode (the player's car follows the camera's, others use 1), places the sound at the
   car, resets the state, and reads the car's maximum revolutions from the car table to set the
   rev scale (m172).
   DRAFT: the loops are laid out as retail (the curve copy loops with a stepping pointer and an offset, the 16 slot clear down-counted), but the rest differs in scheduling and register use (784 vs 804 bytes); the camera field is read as lbu where retail loads the word and masks. */
void CEngineSound::f_0c8fec(int c)
{
    int i, n;
    EmitRec *e;

    car = (EngCar *)c;
    e = &D_24ecc0[id];
    n = e->set->count;
    char *dd = (char *)this;
    int off = 0;
    for (i = 0; i < n; i++) {
        int ta = *(int *)((char *)e + off + 48);
        int tb = *(int *)((char *)e + off + 52);
        *(int *)(dd + 244) = ta;
        *(int *)(dd + 248) = tb;
        dd += 52;
        off += 52;
    }
    n = D_251a78.set->count;
    EmitRec *r1 = &D_251a78;
    dd = (char *)this;
    off = 0;
    for (i = 0; i < n; i++) {
        int ta = *(int *)((char *)r1 + off + 48);
        int tb = *(int *)((char *)r1 + off + 52);
        *(int *)(dd + 1076) = ta;
        *(int *)(dd + 1080) = tb;
        dd += 52;
        off += 52;
    }
    dd = (char *)this;
    for (i = 0; i < 16; i++) {
        *(int *)(dd + 200) = 0;
        *(int *)(dd + 1032) = 0;
        dd += 52;
    }
    slot[0][0].s4 = 1;
    m8 = car->m80;
    m48 = 0;
    m52 = 0;
    m56 = 0;
    m76 = 0;
    m80 = 0;
    if (m8 & 1) {
        m1872 = m12;
        m12 = D_23be80.cam->m660 & 0xff;
    } else {
        m1872 = m12;
        m12 = 1;
    }
    m112 = 0;
    Vec4 t = car->pos144;
    Vec4 q(t.x / 1000.0f, t.y / 1000.0f, t.z / 1000.0f, 1.0f);
    *(Vec4 *)&pos = q;
    for (i = 0; i < 16; i++) {
        slot[1][i].state = 0;
        slot[0][i].state = 0;
        slot[1][i].i8 = 0;
        slot[0][i].i8 = 0;
        D_23bb4c.f_01c618(&slot[0][i].req);
        D_23bb4c.f_01c618(&slot[1][i].req);
    }
    for (i = 0; i < 4; i++)
        m60[i] = 0;
    level = 0;
    m156 = f_0f6b90() % 6;
    m1872 = 1;
    m160 = 0;
    m184 = 0;
    m188 = 0;
    m92[1] = 0;
    m92[0] = 0;
    m1864 = 0;
    m1868 = 0;
    *(Vec4 *)&last = *(Vec4 *)&pos;
    slot[0][0].f0 = 0;
    m180 = 0;
    m176 = 0;
    Pair r = car->m92;
    char *f = D_240740.f_0368e8("MaxRev", (char *)r.a, 0, 0);
    memcpy(&D_24063c, f, D_1a211c[2]);
    m172 = 10000.0f / (float)(short)D_24063c;
}

/* @draft 0x0c9310 us _ZN12CEngineSound8f_0c9310Ei
   WHAT IT DOES: The per frame step of a car's engine sound (flags: 1 lets row 0 start new
   voices, 2 row 1). Unless the car has no engine or is stopped (state 0x8001), it mutes
   by the car's flag, steps the view state, and (while not holding a wall hit) shifts the revs,
   load and speed histories and works out the engine's levels (m48, m52, m56, m76, m80, m112)
   from the car. For the player's car (and the others in a different way) it places the sound
   at the car, runs the gear, wall and skid sounds, sets the volume of the surface
   noise, finds the distance to the listener (level) and turns it into the volume scale m148, then
   advances the wall state and steps both rows of slots. Other cars take their levels from the
   engine tables by distance (the level counted down in hundredths).
   DRAFT: the structure is retail's but the register allocation and the volume scale selects differ (1932 vs 1904 bytes); retail loads the slot flags with lhu + seh and masks the camera word with andi. */
void CEngineSound::f_0c9310(int flags)
{
    CRaceView *g = &D_23be80;
    EngCar *c = car;

    if (c->m76 == 0)
        return;
    if (c->m80 == 0x8001)
        return;
    if (D_2407fc->mode != 3 || g->m4 < 4) {
        if (c->m128)
            f_0c9b24(1);
        else
            f_0c9b24(0);
    }
    f_0c9a80();
    short us = slot[0][0].s4;
    if (us != 2) {
        int sum = 0;
        int k;

        for (k = 3; k > 0; k--)
            m60[k] = m60[k - 1];
        for (k = 7; k > 0; k--) {
            m16[k] = m16[k - 1];
            sum += m16[k - 1];
        }
        c = car;
        m60[0] = (int)(c->m1756 * m172);
        int avg = (m60[0] + m60[1] + m60[2] + m60[3]) / 4;
        m76 = avg / 5;
        int v = (int)(c->m1744 * 127.0f);
        m16[0] = v;
        int a = (v + sum + m48 * 8 + 10) / 16;
        if (a < 0) {
            m48 = 0;
        } else {
            if (a > 127)
                a = 127;
            m48 = a;
        }
        a = (int)(c->m1748 * 127.0f);
        if (a < 0) {
            m52 = 0;
        } else {
            if (a > 127)
                a = 127;
            m52 = a;
        }
        m56 = c->m1752;
        m112 = (int)c->m2144 / 2;
        m80 = (int)(c->m192 * 0.216f);
    }
    c = car;
    if (m8 & 1) {
        if (D_2407fc->m20)
            m112 = (int)g->cam->m744 / 2;
        count = 0;
        {
            Vec4 t = c->pos144;
            Vec4 q(t.x / 1000.0f, t.y / 1000.0f, t.z / 1000.0f, 1.0f);
            *(Vec4 *)&pos = q;
        }
        f_0c9bd8();
        f_0c9d2c();
        f_0c9e6c();
        f_10ddac(1, 64, (float)g->m96[m112] / 50.0f);
        if (g->cam->m664) {
            m1872 = m12;
            m12 = g->cam->m660 & 0xff;
        }
        c = car;
        {
            Vec4 b;
            b = Vec4(c->pos144.x / 1000.0f, c->pos144.y / 1000.0f, c->pos144.z / 1000.0f, 1.0f);
            Vec4 l = g->m144;
            level = b.f_09b4dc(l);
        }
        float v = 1.0f;
        if (D_2407fc->m20 && m12 != 0 && m12 != 3 && D_2407fc->m48 > 0) {
            if (level < 20.0f)
                v = (20.0f - level) / 20.0f + 1.0f;
        }
        m148 = v;
        if (m164 == 1) {
            slot[0][0].s4 = 2;
        } else if (m164 == 2) {
            int i;

            for (i = 0; i < 16; i++) {
                slot[0][i].i8 = 0;
                slot[1][i].i8 = 0;
            }
            slot[0][0].s4 = 1;
        }
        f_0c8bf4(0, 17, flags & 1);
        f_0c8bf4(1, 17, flags & 2);
    } else {
        {
            Vec4 t = c->pos144;
            Vec4 q(t.x / 1000.0f, t.y / 1000.0f, t.z / 1000.0f, 1.0f);
            *(Vec4 *)&pos = q;
        }
        if (us != 2) {
            count = 2;
            f_0c9bd8();
            c = car;
            {
                Vec4 b;
                b = Vec4(c->pos144.x / 1000.0f, c->pos144.y / 1000.0f, c->pos144.z / 1000.0f, 1.0f);
                Vec4 l = g->m144;
                level = b.f_09b4dc(l);
            }
            float v = 1.0f;
            if (D_2407fc->m56) {
                if (D_2407fc->m20) {
                    if (level < 20.0f)
                        v = (20.0f - level) / 20.0f + 1.0f;
                } else {
                    if (level < 20.0f)
                        v = (20.0f - level) * 0.6f / 20.0f + 1.0f;
                }
            }
            m148 = v;
            int q3 = -D_2407fc->m48 / 100;
            if (q3 > 0 && D_2407fc->mode != 3) {
                int w = 481 - q3;
                if (w < 0)
                    w = 0;
                signed char *tb = g->m552[m156];
                int e = w / 3;
                int r = w - e * 3;
                int p = tb[e * 2 + 1];
                if (p < 0) {
                    m48 = 0;
                } else {
                    if (p > 127)
                        p = 127;
                    m48 = p;
                }
                signed char *tc = g->m552[m156];
                int e0 = tc[e * 2];
                int e1 = tc[e * 2 + 2];
                float f = (float)((e0 * (3 - r) + e1 * r) * 100) / 3.0f;
                m76 = (int)(f * m172) / 5;
            }
        }
        if (m164 == 1) {
            slot[0][0].s4 = 2;
        } else if (m164 == 2) {
            int i;

            for (i = 0; i < 16; i++) {
                slot[0][i].i8 = 0;
                slot[1][i].i8 = 0;
            }
            slot[0][0].s4 = 1;
        }
        f_0c8bf4(0, 17, flags & 1);
        f_0c8bf4(1, 17, flags & 2);
    }
}

/* @implements 0x0c9a80 us _ZN12CEngineSound8f_0c9a80Ev
   WHAT IT DOES: Steps the player's car's view state with the camera's inside flag
   (0 outside, 1 going inside, 2 going outside), then takes the race's forced view if
   one is set; other cars take the forced view or their own. */
void CEngineSound::f_0c9a80()
{
    CRaceView *g = &D_23be80;

    if (m8 & 1) {
        switch (m164) {
        case 0:
            if (g->cam->m664)
                m164 = 1;
            break;
        case 1:
            if (!g->cam->m664)
                m164 = 2;
            break;
        case 2:
            m164 = 0;
            break;
        }
        int v = g->m16;

        if (v)
            m164 = v;
    } else {
        int v = g->m16;

        m164 = v;
        if (v == 0) {
            int w = m166;
            m164 = w;
        }
    }
}

/* @implements 0x0c9b24 us _ZN12CEngineSound8f_0c9b24Es
   WHAT IT DOES: Sets the mute state; unmuting a muted engine marks it 2 (resuming). */
void CEngineSound::f_0c9b24(short mute)
{
    if (m166 == 1 && mute == 0)
        m166 = 2;
    else
        m166 = mute;
}

/* @implements 0x0c9b54 us _ZN12CEngineSound8f_0c9b54Ev
   WHAT IT DOES: Stops the engine: marks it stopping, runs both rows down, and for the
   player's car stops the two skid slots. */
void CEngineSound::f_0c9b54()
{
    slot[0][0].s4 = 2;
    f_0c8bf4(0, 17, 1);
    f_0c8bf4(1, 17, 1);
    if (m8 & 1) {
        f_0c8360(1, 10);
        f_0c8360(1, 11);
    }
}

/* @draft 0x0c9bd8 us _ZN12CEngineSound8f_0c9bd8Ev
   WHAT IT DOES: Takes the car's two gear selections and its engine load, prints them as
   debug text, and when the tone for a selection changes stops the voice of the matching
   skid slot in row 1 (slot 3 and slot 5).
   DRAFT: the first loop is a counted pointer loop but reversed (bgez) where retail counts up (slti); retail also keeps two pointers into this (for the m84 and m88 halfwords at this+80 and this+84) that this build addresses directly. */
void CEngineSound::f_0c9bd8()
{
    int i;
    int *d = m92;
    int *sp = car->m2632;

    for (i = 0; i < 2; i++)
        *d++ = *sp++;
    m108 = car->m1776;
    car->m1776 = 0;
    for (i = 0; i < 2; i++)
        f_0828c4(D_24517c, 128, "%d(R%d S%d) J%d", m92[i], D_1d4a48[m92[i]], D_1d4a50[m92[i]], car->m1796);
    int top = m92[0] > m92[1] ? m92[0] : m92[1];

    if (m84 != D_1d4a48[top]) {
        f_0c8360(1, 3);
        m84 = D_1d4a48[top];
    }
    if (m88 != D_1d4a50[top]) {
        f_0c8360(1, 5);
        m88 = D_1d4a50[top];
    }
}

/* @draft 0x0c9d2c us _ZN12CEngineSound8f_0c9d2cEv
   WHAT IT DOES: The wall scrape sound: the car's heading relative to the camera and its
   velocity give the pan (m184) and a volume (m192) that is silent above a speed, full
   below a lower one and a ramp between; a wall hit selects state 1 or 2 by the car's
   flag; prints the three values as debug text.
   DRAFT: only the register numbering differs (8 of 80 words): retail keeps the car in v1, the position copy source in a1 and the first copied word in a0.
   Cycle 2026-11-16: ours ties pp to the car's pseudo (a1, car dies at pp); retail keeps car live
   past pp (h loaded after it). Tried reading h after the struct copy: car and pp split but car
   lands in a1, the h/cam loads sink below the copy, 16 words; reverted. Untried: keep h first but
   use car again after the copy (e.g. read m2160 via a second car use). */
void CEngineSound::f_0c9d2c()
{
    Pos3 *pp = &car->pos;
    Angle a;
    float h = car->m2160;
    Pos3 v = *pp;
    a.f = h - D_23be80.cam->m612;
    float *r = f_099b98(&a.f);
    float d2 = v.x * v.x + v.z * v.z;

    m184 = (int)(*r * 40.44f);
    if (d2 > 36000000.0f)
        slot[0][0].f0 = 0;
    else if (d2 < 4000000.0f)
        slot[0][0].f0 = 1.0f;
    else
        slot[0][0].f0 = (36000000.0f - d2) / 32000000.0f;
    m188 = 0;
    if (slot[0][0].f0 > 0) {
        if (car->m2148 > 0)
            m188 = 1;
        else
            m188 = 2;
    }
    f_0828c4(D_24517c, 128, "Wall  :%d %1.2f %d", m188, (double)slot[0][0].f0, m184);
}

/* @implements 0x0c9e6c us _ZN12CEngineSound8f_0c9e6cEv
   WHAT IT DOES: Runs the two skid noise slots (row 1, slots 10 and 11, one per side with the
   pan offset by 64): when the surface under that side is one that squeals (level below 2) and its
   volume is above a tenth, the voice is started (view state 2 and up), updated if it plays
   (view state 0) or stopped (view state 1); a faint one is stopped. */
void CEngineSound::f_0c9e6c()
{
    CRaceView *g = &D_23be80;
    int i;

    for (i = 0; i < 2; i++) {
        int k = m112;
        float vol = g->m128[i][k] / 100.0f;
        int st = g->m120[i][k];
        int j = (short)(i + 10);

        if (st < 2) {
            int tone = D_1d4a58[st];
            int b = m184;
            short pan = b - 64;

            if (i)
                pan = b + 64;
            if (0.1f < vol) {
                int v = g->m16;

                if (v == 0) {
                    f_0c8618(1, j);
                    if (slot[1][j].state) {
                        f_0c84a4(vol, pan, 0, 1, j, 1);
                        continue;
                    }
                } else if (v == 1) {
                    f_0c8360(1, j);
                    continue;
                }
                f_0c827c(vol, 562, tone, pan, 0, 1, j);
            } else {
                if (slot[1][j].state)
                    f_0c8360(1, j);
            }
        }
    }
}

/* The engine sound of each car on the grid. */
CEngineSound D_249330[12];

/* @implements 0x0ca044 us __static_initialization_and_destruction_0
   WHAT IT DOES: At shutdown, runs the (empty) destructor over the twelve engine sounds, last
   first; nothing is built at startup. */

/* @implements 0x0ca07c us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0ca09c us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */
