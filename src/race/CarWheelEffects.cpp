/* The car wheel effects object file (retail 0x100ef8 to 0x101998): the effects a race car
   throws from its wheels and exhaust as it drives. Tyre smoke puffs from the rear wheels on
   surfaces that smoke (or dust from the alternating rear wheel on surfaces that throw it),
   skid marks from the wheels that slide, exhaust puffs while the car revs on the grid, and
   the nitro and backfire flames by the car's boost state. The first bytes of the race car
   hold this file's per car state. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    Vec4 r[4];
};

/* The car's tyre state: its direction of travel, each wheel's skid mark width and the
   surface type under each wheel. */
struct Tyres {
    char m0[64];
    float dir[3];
    char m76[212];
    float skidWidth[4];
    char m304[192];
    int surface[4];
};

/* A direction passed by value, its fourth word a plain zero. */
struct Dir {
    float x, y, z;
    int w;
};

extern "C" {
void f_028e9c(const Matrix *m);
Vec4 *f_027f3c(Vec4 *d, const Vec4 *a);
float f_027ebc(const Vec4 *a, const Vec4 *b);
}


/* A smoke particle as the effects return it: its colour and alpha. */
struct Particle {
    char m0[4];
    unsigned char r, g, b;
    char m7[3];
    unsigned char a;
};

class CParticles {
public:
    void f_0321ec(const Vec4 *pos, unsigned int color);
};

struct CarFxMgr;
extern "C" {
void f_033918(CarFxMgr *m, int i, float t);
void f_033e18(CarFxMgr *m, int i);
void f_034380(CarFxMgr *m, int i);
void f_034410(CarFxMgr *m, int i, float s);
void f_03442c(CarFxMgr *m, int i);
}

/* The race effects: smoke particles first, the car flame effects at +44. */
class CRaceEffects {
public:
    Particle *f_031d90(int type, const Vec4 *pos, const Vec4 *vel);
    int f_031dac(int car, int wheel, const Vec4 *pos, Dir dir, float a, float b);
    void f_031dfc(int car, int wheel);

    CParticles *Particles() { return (CParticles *)m0; }
    CarFxMgr *fx() { return (CarFxMgr *)m44; }
    char m0[44];
    char m44[1];
};
extern CRaceEffects D_2402e0;

/* What a surface throws up, one record per surface type: smoke, skid marks, nitro flames,
   dust. */
struct Surface {
    unsigned char smoke, skid, flame, dust;
};
extern Surface D_1d5e28[];

/* The tuning: the speed below which nothing is thrown, the slide above which the rear wheels
   smoke, the distance between smoke puffs and between dust puffs, the distance between
   exhaust puffs on the grid, and the slide above which a wheel leaves a skid mark. */
extern float D_1d1b34;
extern float D_1d1b38;
extern float D_1d1b3c;
extern float D_1d1b40;
extern float D_1d1b44;
extern float D_1d1bdc;

/* The course light colour that tints the smoke, and where the course keeps it. */
struct Col3 {
    int r, g, b;
};
struct MapMgr {
    char p0[12824];
    Col3 smoke;
};
extern MapMgr D_23c820;
extern Col3 D_27f15c;

/* The parts of a race car this file reads and keeps. */
struct RaceCar {
    int m0;
    float slide[4];
    char puff[4];
    float dist[4];
    char m40;
    char m41[3];
    float dustDist;
    char dustWheel;
    char m49[3];
    float exhaustDist;
    unsigned char flameOn;
    unsigned char flameWait;
    char skid[4];
    short skidWait[4];
    char m70[10];
    int id;
    char m84[44];
    int onGrid;
    char m132[28];
    Vec4 vel;
    char m176[16];
    float speed;
    char m196[124];
    Vec4 wheel[4];
    char m384[192];
    Matrix mtx;
    char m640[1152];
    float boost;
    char m1796[268];
    float grip[4];
    float load[4];
    char m2096[12];
    int boostState;
    char m2112[8];
    int m2120;
    int flags;
    Tyres tyres;
};

/* Copies the smoke colour. */
static __inline__ void Copy(Col3 *d, const Col3 *s)
{
    *d = *s;
}

/* The nitro flames by the car's boost state: on for states 1 and 2, sized by the boost for
   state 3, off otherwise. */
#define FLAMES(c, idx)                                    \
    do {                                                  \
        if ((c)->boostState == 1)                         \
            f_034380(D_2402e0.fx(), idx);                 \
        else if ((c)->boostState == 2)                    \
            f_034380(D_2402e0.fx(), idx);                 \
        else if ((c)->boostState == 3)                    \
            f_034410(D_2402e0.fx(), idx, (c)->boost);     \
        else                                              \
            f_03442c(D_2402e0.fx(), idx);                 \
    } while (0)

void f_1010ac(RaceCar *c);
void f_1010e4(RaceCar *c, unsigned int col);
void f_1011fc(RaceCar *c, unsigned int col);
void f_10156c(RaceCar *c, int idx, int all);
void f_10177c(RaceCar *c, int idx);

/* @implements 0x100ef8 us f_100ef8
   WHAT IT DOES: Resets a car's wheel effects for a race: the smoke state, no skid marks, the
   flames off, and takes the course's smoke colour. */
void f_100ef8(RaceCar *c)
{
    MapMgr *mm;
    int i;

    f_1010ac(c);
    for (i = 0; i < 4; i++) {
        c->skid[i] = 0;
        c->skidWait[i] = 0;
    }
    c->dustWheel = 0;
    mm = &D_23c820;
    Copy(&D_27f15c, &mm->smoke);
    c->flameWait = c->flameOn = 0;
}

/* @draft 0x100f78 us f_100f78
   WHAT IT DOES: One frame of a car's wheel effects. A car with the id 0x8001 only shows
   its flames. A car still on the grid revs (exhaust puffs) and leaves
   skid marks; otherwise each wheel's slide is its grip times its load, then come the smoke,
   the exhaust, the skid marks and the flames.
   Remaining difference (9 words): retail keeps the slide loop's pointer in v0 and its counter
   in v1, filling the grid test's delay slot with the pointer copy; here they land in v1 and
   a2 and the copy is scheduled before the branch. */
void f_100f78(RaceCar *c, int idx, unsigned int col, int all)
{
    if (c->id == 0x8001) {
        FLAMES(c, idx);
        return;
    }
    if (c->onGrid) {
        f_10156c(c, idx, all);
        f_1010e4(c, col);
    } else {
        for (int i = 0; i < 4; i++)
            c->slide[i] = c->grip[i] * c->load[i];
        f_1011fc(c, col);
        f_1010e4(c, col);
        f_10156c(c, idx, all);
        f_10177c(c, idx);
    }
}

/* @implements 0x1010ac us f_1010ac
   WHAT IT DOES: Resets the smoke state: no puff on either rear wheel, the distances since
   the last smoke, dust and exhaust puffs at zero. */
void f_1010ac(RaceCar *c)
{
    int i;

    for (i = 2; i < 4; i++) {
        c->puff[i] = -1;
        c->dist[i] = 0;
    }
    c->m40 = 0;
    c->exhaustDist = 0;
    c->dustDist = 0;
}

/* The exhaust puff's offset from the car's centre. */
static const Vec4 D_1b0580 = { 0.0f, -200.0f, 2500.0f, 0.0f };

/* Every 4500 units driven, puffs exhaust smoke 2500 units ahead of and 200 below the car's
   centre, in the given colour slightly darkened. */
#define EXHAUST(c, col)                                                          \
    do {                                                                         \
        (c)->exhaustDist += (c)->speed;                                          \
        if (D_1d1b44 <= (c)->exhaustDist) {                                      \
            (c)->exhaustDist = 0;                                                \
            off = D_1b0580;                                                      \
            f_028e9c(&(c)->mtx);                                                 \
            f_027f3c(&p, &off);                                                  \
            r = (unsigned int)(((unsigned char *)&col)[0] * 255) >> 8;           \
            g = (unsigned int)(((unsigned char *)&col)[1] * 255) >> 8;           \
            b = (unsigned int)(((unsigned char *)&col)[2] * 255) >> 8;           \
            if (r > 255)                                                         \
                r = 255;                                                         \
            if (g > 255)                                                         \
                g = 255;                                                         \
            if (b > 255)                                                         \
                b = 255;                                                         \
            q = (unsigned char *)&t;                                             \
            q[0] = r;                                                            \
            q[1] = g;                                                            \
            q[2] = b;                                                            \
            D_2402e0.Particles()->f_0321ec(&p, t);                               \
        }                                                                        \
    } while (0)

/* @draft 0x1010e4 us f_1010e4
   WHAT IT DOES: While the car is in state 1 with boost state 1 or 2, counts the distance
   driven and every 4500 units puffs exhaust smoke 2500 units ahead of and 200 below the
   car's centre, in the given colour slightly darkened.
   Remaining difference (10 words, scheduling): retail loads the offset constant's words in
   the order 0, 12, 8, 4 (stores 0, 12, 4, 8) with the distance clear after the address; here
   0, 12, 4, 8. */
void f_1010e4(RaceCar *c, unsigned int col)
{
    Vec4 p;
    Vec4 off;
    unsigned int t;
    unsigned char *q;
    unsigned int r, g, b;

    if (c->flags == 1) {
        if (c->boostState != 1) {
            if (c->boostState != 2)
                return;
        }
        EXHAUST(c, col);
    }
}

/* @draft 0x1011fc us f_1011fc
   WHAT IT DOES: The rear wheels' smoke. On a smoking surface, while the car is fast enough
   and the wheel slides, a smoke puff in the course's smoke colour tinted by the given colour
   leaves the wheel every 3000 units. On a dusty surface, while the wheel has load, a dust puff
   leaves the two rear wheels in turn every 4000 units, fading in with speed (from 10 up over
   200 units).
   Remaining difference (most words): retail addresses the puff flags both from i + c and
   from a separately stepped pointer, keeps the surface entry pointer as its own stepped
   register and rematerialises the -1 and table constants, where here they are hoisted;
   the control flow and the calls agree. */
void f_1011fc(RaceCar *c, unsigned int col)
{
    unsigned char *rgb = (unsigned char *)&col;
    int i;
    Particle *p;
    float f;
    unsigned int r, g, b;
    int a;

    for (i = 2; i < 4; i++) {
        Surface *s = &D_1d5e28[c->tyres.surface[i]];

        if (s->smoke) {
            if (c->speed < D_1d1b34 || c->slide[i] < D_1d1b38) {
                c->puff[i] = -1;
                c->dist[i] = 0;
                continue;
            }
            if (D_1d1b3c <= c->dist[i]) {
                c->puff[i] = 0;
                p = D_2402e0.f_031d90(0, &c->wheel[i], &c->vel);
                r = D_27f15c.r * rgb[0] >> 8;
                g = D_27f15c.g * rgb[1] >> 8;
                b = D_27f15c.b * rgb[2] >> 8;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                p->r = r;
                p->b = b;
                p->g = g;
                a = 0xaf;
                if (c->puff[i])
                    a = 0x8f;
                p->a = a;
                c->dist[i] = 0;
            }
        } else if (s->dust) {
            if (c->load[i] == 0.0f) {
                c->puff[i] = -1;
                c->dist[i] = 0;
                continue;
            }
            if (D_1d1b40 <= c->dustDist) {
                c->puff[i] = 1;
                p = D_2402e0.f_031d90(0, &c->wheel[2 + c->dustWheel], &c->vel);
                r = p->r * rgb[0] >> 8;
                g = p->g * rgb[1] >> 8;
                b = p->b * rgb[2] >> 8;
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                p->r = r;
                p->b = b;
                p->g = g;
                f = (c->speed - 10.0f) / 200.0f;
                if (f < 0.0f)
                    f = 0.0f;
                else if (1.0f < f)
                    f = 1.0f;
                p->a = (int)(f * 255.0f);
                c->dustDist = 0;
                c->dustWheel = (c->dustWheel + 1) & 1;
            }
            c->dustDist += c->speed;
        }
        c->puff[i] = -1;
        c->dist[i] += c->speed;
    }
}

/* @draft 0x10156c us f_10156c
   WHAT IT DOES: The skid marks. Each wheel (only the rear ones unless all is set) that slides
   more than the skid threshold on a surface that marks, while the car is fast enough and off
   the grid, extends its skid mark along the car's direction, its width from the wheel and its
   strength from the slide; a wheel that stops sliding ends its mark and waits 255 frames
   before it may start a new one.
   Remaining difference: here loop.c hoists the race effects' address and 255 out of the
   loop, which spills the all-wheels flag to the stack and turns the non-short-circuit rear
   wheel test into branches; retail rematerialises both constants and keeps the flag in s8. */
void f_10156c(RaceCar *c, int idx, int all)
{
    Tyres *t = &c->tyres;
    int i;
    int any = all != 0;

    for (i = 0; i < 4; i++) {
        float s;

        if (--c->skidWait[i] < 0)
            c->skidWait[i] = 0;
        s = c->slide[i];
        if (D_1d1bdc < s && D_1d1b34 < c->speed && !c->onGrid && D_1d5e28[t->surface[i]].skid &&
            (any | (i >= 2)) && c->skidWait[i] == 0) {
            Dir d = { t->dir[0], t->dir[1], t->dir[2], 0 };

            s = (s - D_1d1bdc) / (1.0f - D_1d1bdc) * 0.7f;
            if (D_2402e0.f_031dac(idx, i, &c->wheel[i], d, t->skidWidth[i], s)) {
                c->skid[i] = 1;
            } else {
                c->skid[i] = 0;
                c->skidWait[i] = 255;
            }
            continue;
        }
        if (c->skid[i]) {
            D_2402e0.f_031dfc(idx, i);
            c->skidWait[i] = 255;
        }
        c->skid[i] = 0;
    }
}

/* The up direction. */
static const Vec4 D_1b0590 = { 0.0f, 1.0f, 0.0f, 0.0f };

/* @draft 0x10177c us f_10177c
   WHAT IT DOES: The flames. A car that has finished (and is not set to keep them) gets the
   finish flames; then the nitro flames by the boost state. When both rear wheels are on a
   surface that allows it, the car is fast and level and the mean load on the rear wheels is
   above 0.8, a backfire burst of up to 50 frames fires once 60 quiet frames have passed, at
   the balance of the two loads; any other frame counts quiet frames.
   Remaining difference: retail keeps boost states 1 and 2 as separate targets (the second
   jumping into the first's call) and lays the backfire burst out of line; here the two
   targets merge and the burst falls through. */
void f_10177c(RaceCar *c, int idx)
{
    Matrix *m = &c->mtx;
    Tyres *t;

    if (c->m2120 && !(c->flags & 2))
        f_033e18(D_2402e0.fx(), idx);
    FLAMES(c, idx);
    t = &c->tyres;
    if (D_1d5e28[t->surface[2]].flame && D_1d5e28[t->surface[3]].flame &&
        !(c->load[3] < 0.8f && c->load[2] < 0.8f) && !(c->speed < D_1d1b34) &&
        !(f_027ebc(&D_1b0590, &m->r[1]) < 0.998f)) {
        float sum = c->load[3] + c->load[2];

        if (sum != 0.0f && 0.8f < sum * 0.5f && c->flameOn < 50 && !(c->flameWait < 60)) {
            f_033918(D_2402e0.fx(), idx, c->load[3] / sum);
            c->flameOn++;
            return;
        }
    }
    if (c->flameOn)
        c->flameWait = 0;
    c->flameOn = 0;
    if (c->flameWait < 60)
        c->flameWait++;
}
