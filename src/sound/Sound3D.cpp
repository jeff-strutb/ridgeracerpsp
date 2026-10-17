/* @cflags: -fno-math-errno */
/* The 3D sound object (retail 0x114234 to 0x114a4c): the listener's position, velocity and
   orientation, the per-bank tables of 3D sound parameters, and 32 tracked voices with their
   positions. Each update turns every registered voice into a pan angle, a distance
   attenuation and a Doppler pitch scale, and stops voices that become inaudible. The
   attenuation is 1 inside a sound's near distance and falls linearly to 0 at its far one. */

struct SoundReq;

/* A vector as the VFPU helpers (0x1154c4...) use it: 16 bytes. */
struct Vec4 {
    float x, y, z, w;
};

static inline Vec4 operator-(const Vec4 &a, const Vec4 &b)
{
    Vec4 r;

    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

/* A position as voices keep it. */
struct Vec3 {
    float x, y, z;

    void Set(const Vec4 &o)
    {
        x = o.x;
        y = o.y;
        z = o.z;
    }
};

struct Vec4s : Vec4 {
    void Set(const Vec4 &o)
    {
        x = o.x;
        y = o.y;
        z = o.z;
    }
};

/* A 3D sound's distance parameters (24 bytes per sound of a bank). */
struct Sound3DParams {
    int m0[3];
    float far;
    float nearDist;
    float mid;
};

/* A tracked voice (80 bytes). */
struct Voice3D {
    int active;
    int m4[3];
    Vec4s pos;
    Vec4s vel;
    Vec3 x;
    Sound3DParams *params;
    SoundReq *req;
    int m68[3];
};

/* The part of a SAS voice's state used here (0x10d160). */
struct SasVoice3 {
    char m0[44];
    float atten;
    char m48[8];
    short pan;
};

extern "C" {
float *f_10e18c(void);
SasVoice3 *f_10d160(int a, int ch);
int f_10fb44(int ch, short pitch);
void f_10fc04(int ch, float scale);
int f_1140f4(SoundReq *r);
float sqrtf(float x);
void f_115570(Vec4 *eye, Vec4 *at, Vec4 *up);
Vec4 *f_115554(Vec4 *out, Vec4 *in);
Vec4 *f_1154c4(Vec4 *out, Vec4 *a, Vec4 *b);
Vec4 *f_1154dc(Vec4 *out, Vec4 *a);
float f_115514(Vec4 *a, Vec4 *b);
float f_115534(Vec4 *a);
float f_115744(float x);
float f_115380(float x);
float f_115354(float x);
}

class C3DSound {
public:
    Sound3DParams *bank[64];
    Vec4 lpos;              /* listener */
    Vec4 lvel;
    Vec4 lmove;
    Vec4 lup;
    Voice3D v[32];
    float m2880;
    float doppler;          /* the Doppler pitch scale's limit */
    float m2888;

    int f_114234();
    int f_114300(int flags);
    void f_1147a0(int ch, unsigned short b, unsigned short idx);
    void f_1147dc(SoundReq *r, Vec4 *pos, Vec4 *vel, Vec4 *x);
    void f_114854(int ch, short pitch);
    void f_114890(Vec4 *pos, Vec4 *vel, Vec4 *move, Vec4 *up);
    int f_1148f4(int n, unsigned short b, Sound3DParams *p);
    int f_11490c();
    float f_114958(Vec4 *pos, unsigned short b, unsigned short idx);
};

/* @implements 0x114234 us f_114234
   WHAT IT DOES: Takes the 3D settings from the mixer configuration and clears the listener,
   the bank tables and the voices. */
int C3DSound::f_114234()
{
    float *cfg = f_10e18c();
    int i;

    m2880 = cfg[0];
    m2888 = cfg[2];
    doppler = cfg[3];
    lmove.z = 0;
    lmove.y = 0;
    lmove.x = 0;
    lup.z = 0;
    lup.y = 0;
    lup.x = 0;
    lvel.z = 0;
    lvel.y = 0;
    lvel.x = 0;
    lpos.z = 0;
    lpos.y = 0;
    lpos.x = 0;
    for (i = 0; i < 64; i++)
        bank[i] = 0;
    for (i = 0; i < 32; i++) {
        v[i].active = 0;
        v[i].params = 0;
        v[i].req = 0;
        v[i].x.z = 0;
        v[i].x.y = 0;
        v[i].x.x = 0;
        v[i].vel.z = 0;
        v[i].vel.y = 0;
        v[i].vel.x = 0;
        v[i].pos.z = 0;
        v[i].pos.y = 0;
        v[i].pos.x = 0;
    }
    return 0;
}

/* @draft 0x114300 us f_114300
   WHAT IT DOES: The 3D update. When the listener moves, rebuilds the listener's view
   (0x115570) and, for every voice registered since the last update, sets its pan from the
   angle to the listener, its attenuation from the distance, and its pitch from the Doppler
   shift of the relative velocity (clamped to the configured limit), stopping voices that
   become inaudible. flags >> 4 is the frame time.
   DRAFT: 30 of 296 words differ, all FP register choices in the pan angle: retail keeps the
   zero constant and the angle in f4 (the z == 0, x >= 0 case uses the constant itself as the
   angle) and the relative z in f3; here zero is f0, the angle f3 and z f4. */
int C3DSound::f_114300(int flags)
{
    Vec4 t;
    Vec4 rel;
    Vec4 a;
    Vec4 b;
    Vec4 na;
    Vec4 nb;
    int i;

    if (lmove.x == 0.0f && lmove.y == 0.0f && lmove.z == 0.0f)
        return 0;
    t.x = lpos.x + lmove.x;
    t.y = lpos.y + lmove.y;
    t.z = lpos.z + lmove.z;
    f_115570(&lpos, &t, &lup);
    for (i = 0; i < 32; i++) {
        if (v[i].active == 1) {
            SasVoice3 *sv = f_10d160(0, i);
            Sound3DParams *p;
            float ang, dist, f;

            v[i].active = 0;
            f_115554(&rel, &v[i].pos);
            if (0.0f < rel.z) {
                if (0.0f < rel.x)
                    ang = 3.14159274f - f_115744(rel.x / rel.z);
                else
                    ang = -3.14159274f - f_115744(rel.x / rel.z);
            } else if (rel.z == 0.0f) {
                if (rel.x < 0.0f)
                    ang = 1.57079637f;
                else
                    ang = 0.0f;
            } else {
                ang = -f_115744(rel.x / rel.z);
            }
            sv->pan = (int)(ang / 0.0247f);
            dist = sqrtf(rel.x * rel.x + rel.y * rel.y + rel.z * rel.z);
            p = v[i].params;
            if (dist < p->nearDist)
                sv->atten = 1.0f;
            else if (dist < p->mid)
                sv->atten = 1.0f - (dist - p->nearDist) / (p->far - p->nearDist);
            else if (dist < p->far)
                sv->atten = 1.0f - (p->mid - p->nearDist) / (p->far - p->nearDist);
            else
                sv->atten = 0.0f;
            f_1154c4(&a, &v[i].vel, &lvel);
            f_1154c4(&b, &v[i].pos, &lpos);
            if ((a.x == 0.0f && a.y == 0.0f && a.z == 0.0f) || (b.x == 0.0f && b.y == 0.0f && b.z == 0.0f)) {
                f = 1.0f;
            } else {
                float c, ang2, len;

                f_1154dc(&na, &a);
                f_1154dc(&nb, &b);
                c = f_115514(&na, &nb);
                if (!(-1.0f <= c))
                    continue;
                if (!(c <= 1.0f))
                    continue;
                float dt;

                ang2 = f_115380(c);
                len = f_115534(&a);
                dt = (unsigned int)flags >> 4;
                f = 1.0f - m2888 * len * f_115354(ang2) * 60.0f / dt / 340.0f;
            }
            if (doppler < f)
                f = doppler;
            if (f < 1.0f / doppler)
                f = 1.0f / doppler;
            f_10fc04(i, f);
            if (1.5f < sv->atten)
                sv->atten = 1.5f;
            if (sv->atten <= 0.001f)
                f_1140f4(v[i].req);
        }
    }
    return 0;
}

/* @implements 0x1147a0 us f_1147a0
   WHAT IT DOES: Gives voice ch the 3D parameters of sound idx of bank b. */
void C3DSound::f_1147a0(int ch, unsigned short b, unsigned short idx)
{
    v[ch].params = &bank[b][idx];
}

/* @draft 0x1147dc us f_1147dc
   WHAT IT DOES: Registers sound r's voice for this update at a position with a velocity.
   DRAFT: the same stores, scheduled differently: retail loads each source vector z, x, y
   before its stores (as 0x114890 does) and reads the voice index into v0. */
void C3DSound::f_1147dc(SoundReq *r, Vec4 *pos, Vec4 *vel, Vec4 *x)
{
    int ch = *(int *)r;

    v[ch].pos.Set(*pos);
    v[ch].vel.Set(*vel);
    v[ch].x.Set(*x);
    v[ch].req = r;
    v[ch].active = 1;
}

/* @implements 0x114854 us f_114854
   WHAT IT DOES: Sets voice ch's pitch offset in its request and on the voice (0x10fb44). */
void C3DSound::f_114854(int ch, short pitch)
{
    *(short *)((char *)v[ch].req + 28) = pitch;
    f_10fb44(ch, pitch);
}

/* @implements 0x114890 us f_114890
   WHAT IT DOES: Sets the listener's position, velocity, movement and up vectors. */
void C3DSound::f_114890(Vec4 *pos, Vec4 *vel, Vec4 *move, Vec4 *up)
{
    lpos.x = pos->x;
    lpos.y = pos->y;
    lpos.z = pos->z;
    lvel.x = vel->x;
    lvel.y = vel->y;
    lvel.z = vel->z;
    lmove.x = move->x;
    lmove.y = move->y;
    lmove.z = move->z;
    lup.x = up->x;
    lup.y = up->y;
    lup.z = up->z;
}

/* @implements 0x1148f4 us f_1148f4
   WHAT IT DOES: Sets bank b's 3D parameter table. */
int C3DSound::f_1148f4(int n, unsigned short b, Sound3DParams *p)
{
    bank[b] = p;
    return 0;
}

/* @implements 0x11490c us f_11490c
   WHAT IT DOES: Frees every bank's 3D parameter table. */
int C3DSound::f_11490c()
{
    int i;

    for (i = 63; i >= 0; i--) {
        if (bank[i]) {
            delete[] bank[i];
            bank[i] = 0;
            break;
        }
    }
    return 0;
}

/* @draft 0x114958 us f_114958
   WHAT IT DOES: The distance attenuation of sound idx of bank b at a position: 1 inside its
   near distance, falling linearly towards its far distance, 0 beyond.
   DRAFT: the comparisons and returns match; the difference vector's loads and FP registers
   at the start are scheduled differently (retail loads the listener's z before the first
   subtraction). */
float C3DSound::f_114958(Vec4 *pos, unsigned short b, unsigned short idx)
{
    Vec3 d;
    Sound3DParams *p;
    float dist;

    d.x = lpos.x - pos->x;
    d.y = lpos.y - pos->y;
    d.z = lpos.z - pos->z;
    p = &bank[b][idx];
    dist = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    if (dist < p->nearDist)
        return 1.0f;
    if (dist < p->mid)
        return 1.0f - (dist - p->nearDist) / (p->far - p->nearDist);
    if (dist < p->far)
        return 1.0f - (p->mid - p->nearDist) / (p->far - p->nearDist);
    return 0.0f;
}
