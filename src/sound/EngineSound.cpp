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
int f_10c360(unsigned short name, unsigned short tone, signed char bus, short a, short b, SoundReq *voice, float vol);
int f_10c5a4(SoundReq *r);
int f_10c6fc(SoundReq *r, short pan, short pitch, float vol);
int f_10c810(short pitch, SoundReq *r);
int f_10c86c(SoundReq *r);
int f_113c60(unsigned short name, unsigned short idx, signed char bus, short a, short b, float vol, void *pos, void *vel, void *x, SoundReq *r);
int f_113ff8(void *pos, void *vel, void *x, SoundReq *r);
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

/* One sound slot (52 bytes). The first slot's head words double as the wall-hit state. */
struct Slot {
    float f0;
    short s4;
    short s6;
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
    char m5[87];
    unsigned char b92;
    unsigned char b93;
};

/* The camera the listener follows. */
struct CCamera {
    char m0[664];
    int m664;
};

/* The race view state read here. */
struct CRaceView {
    char m0[16];
    short m16;
    char m18[118];
    CCamera *cam;
};

extern CRaceView D_23be80;

class CEngineSound {
public:
    void *car;
    int id;
    int m8;
    unsigned int m12;
    char m16[112];
    Vec3 pos;
    float m140;
    float level;
    float m148;
    int count;
    char m156[8];
    short m164;
    short m166;
    char m168[16];
    int m184;
    int m188;
    Slot slot[2][16];
    char m1856[16];
    int m1872;
    char m1876[12];
    Vec3 last;
    float m1900;

    int f_0c80a8(unsigned short name, unsigned char idx, short a, short b, int i, int j, float vol);
    int f_0c827c(unsigned short name, unsigned char idx, short a, short b, int i, int j, float vol);
    int f_0c8360(int i, int j);
    int f_0c84a4(short pan, short pitch, int i, int j, int force, float vol);
    int f_0c8618(int i, int j);
    float f_0c8694(int sel, Sample *s);
    void f_0c8bf4(int row, int add, int flag);
    void f_0c9a80();
    void f_0c9b24(short mute);
    void f_0c9b54();
};

/* @draft 0x0c80a8 us _ZN12CEngineSound8f_0c80a8Ethssiif
   WHAT IT DOES: Starts a voice in slot [i][j] if the slot is free and fewer than four
   voices started this frame: 2D in the near views of the player's car, 3D at the car
   otherwise. Returns 1 when it started. 
   DRAFT: register allocation and the 3D branch's address computation differ (448 vs 468 bytes). */
int CEngineSound::f_0c80a8(unsigned short name, unsigned char idx, short a, short b, int i, int j, float vol)
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

/* @draft 0x0c827c us _ZN12CEngineSound8f_0c827cEthssiif
   WHAT IT DOES: Starts a 2D voice in slot [i][j] on bus 1 (row 0) or 0, or bus 3 for a
   car other than the player's. Returns 1 when it started, -1 when four voices already
   started this frame, 0 when the slot is busy, else the library's error. 
   DRAFT: the result and status variables are allocated differently (t1/t5 swap) and the bus select is scheduled later. */
int CEngineSound::f_0c827c(unsigned short name, unsigned char idx, short a, short b, int i, int j, float vol)
{
    int ret = -1;
    int r = 0;

    if (count++ < 4) {
        Slot *s = &slot[i][j];
        int bus;

        if (m8 & 1)
            bus = i == 0;
        else
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

/* @draft 0x0c84a4 us _ZN12CEngineSound8f_0c84a4Essiiif
   WHAT IT DOES: Updates the voice in slot [i][j]: pan, pitch and volume of a 2D voice;
   the pitch alone of a quiet 3D voice of the player's car in the near views, otherwise
   the 3D voice's position, velocity, pitch and volume. Returns 1 when the slot plays. 
   DRAFT: the 3D velocity select is laid out differently (388 vs 372 bytes). */
int CEngineSound::f_0c84a4(short pan, short pitch, int i, int j, int force, float vol)
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

/* @draft 0x0c9a80 us _ZN12CEngineSound8f_0c9a80Ev
   WHAT IT DOES: Steps the player's car's view state with the camera's inside flag
   (0 outside, 1 going inside, 2 going outside), then takes the race's forced view if
   one is set; other cars take the forced view or their own. 
   DRAFT: the final view fallback loads m166 with lhu and stores in a different order (retail lh into the stored register). */
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
        if (!v) {
            v = m166;
            m164 = v;
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
