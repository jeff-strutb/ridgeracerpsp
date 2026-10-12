/* The race sound (retail 0x01ca78 to 0x01dbc4): the sounds of a race. It works out which engine
   samples the cars on the grid use, loads their sound banks, starts each car's engine sound
   and every frame moves the listener with the camera, picks the three loudest rival engines
   to play when there are more cars than voices, and fades the race out at the end. One global
   object holds it; its startup code (0x01db58 to 0x01dbc4) builds it. */

#include <stdio.h>
#include <string.h>

extern "C" {
void f_00d354(char *buf, int size, const char *fmt, ...);
void f_10fcbc(void);
void f_10c65c(void);
int f_10c910(signed char);
int f_10c8f4(signed char);
void f_10ddac(int, int, float);
}

/* A pair of values the settings hand back by value. */
struct Pair {
    int a;
    int b;
};

/* A data package or scene player: its entries are found by name. */
struct CPackage {
    void *f_002acc(const char *name);
    int m0[70];
};

/* The sequence manager, as far as its settings and scene players are concerned. */
struct CSequence {
    Pair f_0031c0();
    Pair f_0031dc(int i);
    Pair f_003200(int i);
    CPackage *f_005a38(const char *name);
    void f_005d4c(const char *name);
};

/* A table of the game database. */
struct CTable {
    char *f_0368e8(const char *field, char *rec, int a, int i);
    int m0[7];
};

/* The sound system. */
struct CSound {
    int f_01c458(void *hd, void *bd, int is3d, unsigned short *out);
    void f_01c578();
    void f_01c7a4(int which, int percent);
};

/* A car's engine sound (1904 bytes). */
struct CEngine {
    int m0;
    int id;
    char m8[136];
    float level;
    char m148[1904 - 148];
    void f_0c8fec(int sample);
    void f_0c9310(int);
    void f_0c9b24(int mute);
    void f_0c9b54();
};

/* A sound emitter placed on the course (836 bytes). */
struct CEmitter {
    void f_0ca584(int kind, void *data);
    void f_0ca77c();
    char m0[836];
};

/* The camera the listener follows. */
struct CCamera {
    float pos[3];
    char m12[600];
    float m612;
    char m616[48];
    int m664;
};

/* The race settings this file reads. */
struct CRaceInfo {
    int m0[4];
    int mode;
    int m20;
};

/* The part of the main loop job read here: two flags that keep the race sound held. */
struct CMainLoopView {
    char m0[11];
    unsigned char a;
    unsigned char b;
};

/* One idling sound's data (320 bytes). */
struct CIdling {
    char m0[320];
};

/* A vector of three floats. */
struct Vec3 {
    Vec3() {}
    Vec3(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    void Set(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
    }
    float x, y, z;
};

/* A vector of four floats; its default constructor does nothing. */
struct Vec4 {
    Vec4() {}
    Vec4(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
    void Set(const Vec3 &v, float d)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = d;
    }
    void Set(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
    float x, y, z, w;
};

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

extern "C" {
void f_099b98(Angle *);
void f_09b394(Angle, float *, float *);
int f_114114(Vec3 *pos, Vec3 *vel, Vec3 *front, Vec3 *up);
}

/* An engine sample list: the samples a car can use. */
struct CSampleEntry {
    unsigned short id;
    char m2[94];
};
struct CSampleList {
    short count;
    char m2[14];
    CSampleEntry e[1];
};

extern CSequence D_1dd6b0;
extern CPackage D_1d8988;
extern CPackage D_1d8aa0;
extern CTable D_240740;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern int D_240910;
extern char D_245178[];
extern CSound D_23bb4c;
extern CEngine D_249330[];
extern CEmitter D_24ecc0[];
extern CEmitter D_251a78;
extern CMainLoopView *D_1d88a0;
extern CRaceInfo *D_2407fc;
extern int D_23f7f8;

class CRaceSound {
public:
    void f_01ca78();
    void f_01ca80();
    void f_01cd54();
    void f_01cdf4();
    void f_01cec4();
    int f_01d174();
    void f_01d17c(int a, int b, int *samples, CCamera *camera, int c);
    void f_01d4b8(int flags);
    void f_01d934();
    void f_01d994();
    void f_01dac0(int f);
    bool Busy() { return D_1d88a0->a || D_1d88a0->b; }

    int m0;
    int count;
    int m8[2];
    short state;
    int m20;
    char m24[60];
    int m84;
    char *wall[12];
    CCamera *camera;
    int m140;
    Vec4 listener;
    char m160[96];
    int sample[64];
    int nSample;
    int nEmitter;
    int m520[4];
    int m536;
    int m540;
    int m544;
    float fade;
    CIdling *idling[6];
};

CRaceSound D_23be80;

/* @implements 0x01ca78 us f_01ca78
   WHAT IT DOES: Does nothing. */
void CRaceSound::f_01ca78()
{
}

/* @draft 0x01ca80 us f_01ca80
   WHAT IT DOES: Works out the engine samples the race needs. For the player's car and then
   each rival it looks up the car's name and maximum revs in the car table (reporting both),
   reads the car's engine sample list from the engine sound package and adds every sample not
   yet listed. It then sorts the list and reports it. */
void CRaceSound::f_01ca80()
{
    char name[48];
    int i, j, k;

    nSample = 0;
    count = D_240910 + 1;
    for (i = 0; i < count; i++) {
        Pair p;
        if (i == 0) {
            p = D_1dd6b0.f_003200(0);
            sprintf(name, "%s", D_240740.f_0368e8("CarName", (char *)p.a, 0, 0));
        } else {
            p = D_1dd6b0.f_0031dc(i - 1);
            sprintf(name, "com_%s", D_240740.f_0368e8("CarName", (char *)p.a, 0, 0));
        }
        memcpy(D_24063c, D_240740.f_0368e8("MaxRev", (char *)p.a, 0, 0), D_1a211c[2]);
        f_00d354(D_245178, 128, "%s %.1f\n", name, (float)*(short *)D_24063c);
        CSampleList *list = (CSampleList *)D_1d8aa0.f_002acc(name);
        for (j = 0; j < list->count; j++) {
            for (k = 0; k < nSample; k++)
                if (sample[k] == list->e[j].id)
                    break;
            if (k == nSample)
                sample[nSample++] = list->e[j].id;
        }
    }
    int n = nSample;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (sample[i] < sample[j]) {
                int t = sample[i];
                sample[i] = sample[j];
                sample[j] = t;
            }
        }
    }
    f_00d354(D_245178, 128, "Use EngineSample List\n");
    for (i = 0; i < nSample; i++)
        f_00d354(D_245178, 128, "E%03d\n", sample[i] + 1);
}

/* @implements 0x01cd54 us f_01cd54
   WHAT IT DOES: Releases the race's sound scenes: the common race sounds and each engine
   sample's sample data. */
void CRaceSound::f_01cd54()
{
    char name[48];
    int i;

    D_1dd6b0.f_005d4c("Sound_Race_Free");
    for (i = 0; i < nSample; i++) {
        sprintf(name, "EngineSampleE%03d_Free", sample[i] + 1);
        D_1dd6b0.f_005d4c(name);
    }
}

/* @implements 0x01cdf4 us f_01cdf4
   WHAT IT DOES: Shows the race's sound scenes: the course's wall sounds, the idling sounds and
   each engine sample's header. */
void CRaceSound::f_01cdf4()
{
    char name[48];
    int i;

    Pair p = D_1dd6b0.f_0031c0();
    sprintf(name, "WallSound_%s", (char *)p.a);
    D_1dd6b0.f_005d4c(name);
    D_1dd6b0.f_005d4c("Idling");
    for (i = 0; i < nSample; i++) {
        sprintf(name, "EngineSampleE%03d", sample[i] + 1);
        D_1dd6b0.f_005d4c(name);
    }
}

/* @draft 0x01cec4 us f_01cec4
   WHAT IT DOES: Loads the race's sound banks (the common race bank and one bank per engine
   sample) into the sound processor, then starts an engine sound emitter for the player's car
   and each rival, using the car's engine data, and the course's map sound emitter. */
void CRaceSound::f_01cec4()
{
    char name[48];
    int i;

    void *hd = D_1d8988.f_002acc("Race");
    D_23bb4c.f_01c458(hd, D_1dd6b0.f_005a38("Sound_Race_Free")->f_002acc("RaceBd"), 1, 0);
    for (i = 0; i < nSample; i++) {
        sprintf(name, "EngineSampleE%03d", sample[i] + 1);
        hd = D_1dd6b0.f_005a38(name)->f_002acc("Hd");
        sprintf(name, "EngineSampleE%03d_Free", sample[i] + 1);
        D_23bb4c.f_01c458(hd, D_1dd6b0.f_005a38(name)->f_002acc("Bd"), 1, 0);
    }
    Pair p;
    p = D_1dd6b0.f_003200(0);
    D_24ecc0[0].f_0ca584(0, D_1d8aa0.f_002acc(D_240740.f_0368e8("CarName", (char *)p.a, 0, 0)));
    nEmitter++;
    for (i = 1; i < count; i++) {
        p = D_1dd6b0.f_0031dc(i - 1);
        sprintf(name, "com_%s", D_240740.f_0368e8("CarName", (char *)p.a, 0, 0));
        D_24ecc0[i].f_0ca584(0, D_1d8aa0.f_002acc(name));
        nEmitter++;
    }
    D_251a78.f_0ca584(1, D_1d8988.f_002acc("MapDat"));
    f_10fcbc();
}

/* @implements 0x01d174 us f_01d174
   WHAT IT DOES: Reports that the race sound is ready. */
int CRaceSound::f_01d174()
{
    return 1;
}

/* @draft 0x01d17c us f_01d17c
   WHAT IT DOES: Starts the race sound: records the camera to follow (reporting a fatal error
   if there is none), gives each car its engine sample, holds the sound while the game is
   held, finds the idling and wall sound data, measures the sound processor's free voices and
   sets the four effect volumes (lower in one race mode). */
void CRaceSound::f_01d17c(int a, int b, int *samples, CCamera *cam, int c)
{
    int i;

    m0 = a;
    if (cam)
        camera = cam;
    else
        f_00d354(D_245178, 128, "No Camera!!!!! Fatal Error\n");
    m544 = c;
    m84 = 0;
    fade = 1.0f;
    CEngine *e = D_249330;
    e->id = 0;
    e->f_0c8fec(samples[0]);
    for (int j = 1; j < count; j++) {
        e++;
        e->id = j;
        e->f_0c8fec(samples[j]);
    }
    state = Busy();
    for (int k = 0; k < 6; k++)
        idling[k] = (CIdling *)D_1dd6b0.f_005a38("Idling")->f_002acc("Data") + k;
    for (int n = 0; n < 4; n++)
        m520[n] = f_10c910(n) - f_10c8f4(n);
    m536 = m520[0] + m520[1] + m520[2] + m520[3];
    Pair p = D_1dd6b0.f_0031c0();
    m20 = (D_23f7f8 / 2 + 15) / 16 * 16;
    char *w = (char *)D_1dd6b0.f_005a38("WallSound_")->f_002acc("Dat");
    wall[0] = w;
    wall[1] = wall[0] + m20;
    wall[2] = wall[1] + m20;
    wall[3] = wall[2] + m20;
    wall[4] = wall[3] + m20;
    wall[5] = wall[4] + m20;
    wall[6] = wall[5] + m20;
    wall[7] = wall[6] + m20;
    wall[8] = wall[7] + m20;
    wall[9] = wall[8] + m20;
    wall[10] = wall[9] + m20;
    wall[11] = wall[10] + m20;
    if (D_2407fc->m20 == 2) {
        D_23bb4c.f_01c7a4(4, 70);
        D_23bb4c.f_01c7a4(5, 70);
        D_23bb4c.f_01c7a4(6, 70);
        D_23bb4c.f_01c7a4(7, 70);
    } else {
        D_23bb4c.f_01c7a4(4, 100);
        D_23bb4c.f_01c7a4(5, 100);
        D_23bb4c.f_01c7a4(6, 100);
        D_23bb4c.f_01c7a4(7, 100);
    }
    f_10ddac(1, 64, 0.0f);
}

/* @draft 0x01d4b8 us f_01d4b8
   WHAT IT DOES: Called every frame of the race. It places the listener at the camera (and
   its velocity from the last frame), with the camera's facing. At the end of a race it fades
   the race volume out over a hundred frames and then holds the sound; otherwise it updates
   the hold state. With more than four cars it keeps only the three loudest rivals' engines
   playing. It then steps every car's engine sound and measures the free voices again. */
void CRaceSound::f_01d4b8(int flags)
{
    int i, k;
    CCamera *cam = camera;

    Vec3 pos;
    pos.x = cam->pos[0] / 1000.0f;
    pos.y = cam->pos[1] / 1000.0f;
    pos.z = cam->pos[2] / 1000.0f;
    Vec3 vel;
    Vec3 front;
    Vec3 up;
    if (cam->m664) {
        vel.x = 0;
        vel.y = 0;
        vel.z = 0;
    } else {
        vel.x = pos.x - listener.x;
        vel.y = pos.y - listener.y;
        vel.z = pos.z - listener.z;
    }
    Vec4 v(0.0f, 0.0f, -1.0f, 1.0f);
    Angle ang;
    ang.f = cam->m612;
    f_099b98(&ang);
    f_09b394(ang, &v.z, &v.x);
    front.Set(v.x, v.y, v.z);
    v.Set(0.0f, 1.0f, 0.0f, 1.0f);
    up.Set(v.x, v.y, v.z);
    f_114114(&pos, &vel, &front, &up);
    if (D_2407fc->mode == 3) {
        if (fade < 1.0f && 0.0f <= fade) {
            D_23bb4c.f_01c7a4(3, (int)(fade * 100.0f));
            f_10ddac(1, 64, fade);
            fade = fade - 0.01f;
        } else if (fade <= 0.0f) {
            f_01dac0(1);
        }
        if (count >= 4) {
            int sel[3] = { 1, 2, 3 };
            float max = 0.0f;
            int best = 0;
            for (i = 1; i < 4; i++) {
                if (max < D_249330[i].level) {
                    max = D_249330[i].level;
                    best = i;
                }
            }
            for (i = 4; i < count; i++) {
                if (max < D_249330[i].level)
                    continue;
                {
                    for (k = 0; k < 3; k++)
                        if (best == sel[k])
                            sel[k] = i;
                    max = 0.0f;
                    best = 0;
                    for (k = 0; k < 3; k++) {
                        CEngine *c = &D_249330[sel[k]];
                        if (max < c->level) {
                            max = c->level;
                            best = sel[k];
                        }
                    }
                }
            }
            for (i = 1; i < count; i++)
                D_249330[i].f_0c9b24(1);
            for (i = 0; i < 3; i++)
                D_249330[sel[i]].f_0c9b24(0);
        }
    } else {
        f_01dac0(flags & 1);
    }
    D_249330[0].f_0c9310(3);
    for (i = 1; i < count; i++)
        D_249330[i].f_0c9310(3);
    m84++;
    for (i = 0; i < 4; i++)
        m520[i] = f_10c910(i) - f_10c8f4(i);
    m536 = m520[0] + m520[1] + m520[2] + m520[3];
    listener.Set(pos.x, pos.y, pos.z, 1.0f);
}

/* WHAT IT DOES: Stops every car's engine sound.
   (Transcribed byte-exact as C in src/control/batch2.c; the tag at 0x01d934 stays there for now.) */
void CRaceSound::f_01d934()
{
    int i;
    for (i = 0; i < count; i++)
        D_249330[i].f_0c9b54();
}

/* @draft 0x01d994 us f_01d994
   WHAT IT DOES: Ends the race sound: stops every emitter, pops the engine banks and the race
   bank, forgets the idling data, stops the map emitter, silences the effect volumes and
   restores the race volume and the output level. */
void CRaceSound::f_01d994()
{
    int i;

    while (nEmitter > 0) {
        nEmitter--;
        D_24ecc0[nEmitter].f_0ca77c();
    }
    while (nSample > 0) {
        nSample--;
        D_23bb4c.f_01c578();
    }
    for (i = 0; i < 6; i++)
        idling[i] = 0;
    D_251a78.f_0ca77c();
    D_23bb4c.f_01c578();
    D_23bb4c.f_01c7a4(4, 0);
    D_23bb4c.f_01c7a4(5, 0);
    D_23bb4c.f_01c7a4(6, 0);
    D_23bb4c.f_01c7a4(7, 0);
    D_23bb4c.f_01c7a4(3, 100);
    f_10ddac(1, 64, 0.8f);
    f_10c65c();
}

/* WHAT IT DOES: Updates the hold state: holds the race sound while the game is held or when
   asked, marks it released (2) the frame the hold ends, and keeps it held before the first
   frame has run.
   (Transcribed byte-exact as C in src/control/batch4.c; the tag at 0x01dac0 stays there for now.) */
void CRaceSound::f_01dac0(int f)
{
    if (state == 0) {
        state = Busy() | f;
    } else if (state == 1) {
        state = Busy() | f;
        if (state == 0)
            state = 2;
    } else {
        state = 0;
    }
    if (m84 == 0)
        state = 1;
}

/* @implements 0x01db58 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the race sound object. */

/* @implements 0x01db9c us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x01dbbc us CRaceSoundC1Ev
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The race sound object's constructor, which has nothing to set. */
