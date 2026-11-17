/* The race sequence's common part (retail 0x0ea8b4 to 0x0ec254): the state every race sequence
   (normal circuit, time attack, network) shares. It records the race's car list and number,
   reads the sequence number from the race table, registers every car with the race's car
   manager (D_27eca4) and its fade, sets up the small race texture, and steps the per-frame
   draw of the race view and the two blinking flags (D_27ecb1, D_27ecb2) that drive the 2D
   overlay's blink. */

#include <string.h>

/* The fade sequence (FadeSequence.cpp). */
struct View;
class CFadeSequence {
public:
    void f_0ff798();
    unsigned int *f_0ff81c(View *v, unsigned int *p);
    void f_0ffa44();
    void Set(int s, float level)
    {
        m8 = m4;
        m4 = s;
        m16 = level;
    }

    int m0;
    int m4;
    int m8;
    float m12;
    float m16;
};
extern CFadeSequence D_27f100;

/* The race's car manager (its own object file, 0x0ca814..). */
class CCarManager {
public:
    void f_0ca814(int n);
    void f_0ca98c();
    void f_0caa5c(int i, void *a, int kind, void *b);
};
extern CCarManager D_27eca4;

/* The 2D overlay of the race (Race2DBase.cpp). */
class CRace2DBase {
public:
    virtual ~CRace2DBase() {}
    virtual int f_089464(int a, int b);
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
};
extern CRace2DBase *D_1d3d40;

/* The part of the main loop job read here. */
struct MainLoopJobView {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern MainLoopJobView *D_1d88a0;

/* The race table (CTable) and the race being set up. */
struct CTable;
extern CTable D_2407d0;
char *f_0368e8(CTable *t, const char *field, char *rec, int a, int i);
extern unsigned char D_24063c[];
extern const int D_1a2120;
struct RaceInfo {
    char *m0;
    char m4[16];
    int m20;
};
extern RaceInfo *D_2407fc;

/* The race's per-car records (1280 bytes each). */
struct CarSlot {
    char m0[1236];
    void *car;
    char m1240[40];
};
struct CarSlots {
    CarSlot slot[8];
};
extern CarSlots *D_24031c;

/* A car of the race. */
struct Car {
    char m0[80];
    int kind;
    char m84[110 - 84];
};

/* The cars of a sequence. */
struct CarList {
    char m0[12];
    int nplayers;
    int nrivals;
    char m20[12];
    char **cars;
};

unsigned int f_021e08(void);
void *f_023038(unsigned int fmt, int w, int h, unsigned int ofs, int id);
int f_023250(int id);

extern int D_1d5a90;
extern int D_27ec84;
extern int D_27ec88;
extern int D_27ec90;
extern void *D_27eca0;
extern int D_27ecb4;
extern int D_27ecbc;
extern int D_27ecc0;
extern int D_27ecc4;
extern int D_27ecc8;
extern bool D_27ecb0;
extern signed char D_27ecb1;
extern signed char D_27ecb2;
extern unsigned char D_27ecb3;

void f_0eb3a4(void);
void f_0eb41c(void);

/* The course lighting the map manager holds (at +12512), as in RcoViewer.cpp. */
struct LightSetup {
    char p0[16];
    float c1[3];
    char p28[20];
    float dir[3];
    char p60[20];
    float c2[3];
    char p92[20];
    float c4[3];
    char p124[20];
    float m144;
    float m148;
    char p152[80];
    int m232;
    float m236;
    float m240;
};

/* The map manager, as far as the race view draw uses it. */
struct MapMgr {
    char p0[12512];
    LightSetup light;
};
extern MapMgr D_23c820;

/* One view of the race (752 bytes). */
struct View {
    char m0[660];
    int m660;
    char m664[88];
};

/* The race effects (RaceEffects.cpp). */
class CRaceEffects {
public:
    void f_031cbc(View *view);
};
extern CRaceEffects D_2402e0;

/* The car job controller (CarJobCtrl.cpp). */
struct RaceCar {
    char m0[1792];
    float m1792;
    char m1796[2108 - 1796];
    int m2108;
};
class CCarJobCtrl {
public:
    RaceCar *f_03b518(int i);
};

void f_021720(void);
void f_021750(void);
unsigned int *f_0216d8(void);
void f_0216e8(unsigned int *p);
void f_118380(float a);
void f_1184d8(int a);
void f_1185dc(int light, int what, int color);
void f_118428(int light, int what, int n, const float *v);
void f_116898(int a);
void f_118b64(int a, float b, float c);
unsigned int *f_0cc584(View *view, unsigned int *p);
unsigned int *f_029524(MapMgr *mm, int a, View *v, unsigned int *p);
unsigned int *f_0cc4e4(int a, int b, int c, int d, unsigned int *p);
extern "C" int f_0ea8a8(void);
void f_0eaeb0(int a, View *v, CCarJobCtrl *ctrl, RaceCar *car);
void f_0eb440(View *v2, View *v, int a);
void f_0eb6b8(View *v, RaceCar *car);

/* @implements 0x0eac84 us f_0eac84
   WHAT IT DOES: Returns 0. */
int f_0eac84(void)
{
    return 0;
}

/* @implements 0x0eac8c us f_0eac8c
   WHAT IT DOES: Does nothing. */
void f_0eac8c(void)
{
}

/* @implements 0x0eac94 us f_0eac94
   WHAT IT DOES: Returns the id of the race's small texture. */
int f_0eac94(void)
{
    return D_27ecc0;
}

/* @draft 0x0eaca0 us f_0eaca0
   WHAT IT DOES: Starts a race sequence: records the car list's number and the sequence
   object, starts the fade, sets up the race texture, reads the race's sequence number from the
   race table (type 3 is flagged), copies every car into the race's car records, registers the
   cars with the car manager (each with its kind: 0 for the player kinds 1 and 0x1001, 2 for
   0x8001, else 1), and clears the blink flags.
   DRAFT: everything to the car loop matches; retail keeps 1, 0x1001 and 0x8001 in saved
   registers and branches on 1 and 0x1001 where this if-converts the kind (-1 word). */
void f_0eaca0(CarList *list, int number, void *seq)
{
    D_27ecb4 = number;
    D_27ec84 = 1;
    D_27eca0 = seq;
    D_1d5a90 = 1;
    D_27ec88 = number;
    D_27f100.f_0ff798();
    f_0eb3a4();
    char *f = f_0368e8(&D_2407d0, "SequenceNumber", D_2407fc->m0, 0, 0);
    memcpy(D_24063c, f, D_1a2120);
    D_27ec90 = D_24063c[0] == 3;
    for (int j = 0; j < list->nplayers + list->nrivals; j++)
        D_24031c->slot[j].car = list->cars[j];
    D_27eca4.f_0ca814(list->nplayers + list->nrivals);
    for (int i = 0; i < list->nplayers + list->nrivals; i++) {
        char *car = list->cars[i];
        *(int *)(car + 4952) = 0xff000000;
        int t = *(int *)(car + 80);
        int kind;
        if (t == 1 || t == 0x1001)
            kind = 0;
        else
            kind = t == 0x8001 ? 2 : 1;
        D_27eca4.f_0caa5c(i, car + 3040, kind, car + 110);
    }
    D_27ecb0 = 0;
    D_27ecb1 = 0;
    D_27ecb2 = 0;
    D_27ecb3 = 0;
}

/* @implements 0x0eae7c us f_0eae7c
   WHAT IT DOES: Ends a race sequence: ends the fade, releases the car manager's cars and the
   race texture. */
void f_0eae7c(void)
{
    D_27f100.f_0ffa44();
    D_27eca4.f_0ca98c();
    f_0eb41c();
}

/* @implements 0x0eb3a4 us f_0eb3a4
   WHAT IT DOES: Sets up the race's small 64x64 texture in video memory at 0x1fe000. */
void f_0eb3a4(void)
{
    D_27ecbc = 0;
    D_27ecc0 = 0x0a000200;
    D_27ecc4 = 0x1fe000;
    D_27ecc8 = f_021e08();
    f_023038(D_27ecbc, 64, 64, D_27ecc4, D_27ecc0);
}

/* @implements 0x0eb41c us f_0eb41c
   WHAT IT DOES: Releases the race's small texture. */
void f_0eb41c(void)
{
    f_023250(f_0eac94());
}

/* A colour from three floats in 0..1 as packed bytes (red lowest). */
static inline int Pack(const float *c)
{
    return (int)(c[0] * 255.0f) | (int)(c[1] * 255.0f) << 8 | (int)(c[2] * 255.0f) << 16;
}

/* @draft 0x0eba3c us f_0eba3c
   WHAT IT DOES: Draws the race view of one player for a frame (the car is looked up from the
   car controller when none is given): steps the view with the car, then twice (the map's
   pass 0, then after the view's own draw its pass 4) sets the graphics engine's three lights
   from the course lighting, records the view and the course map's display list (with a
   closing command when the race is the second one); then the race effects (unless the view
   is in mode 0x20003), the second view's overlay while the fade allows it, sets the fade's
   state from the car (cleared when the race has none) and records the fade pass, closing it
   with the full screen copy when the race is the second one. Clears the first blink flag. */
void f_0eba3c(int a, View *v, View *v2, CCarJobCtrl *ctrl, RaceCar *car)
{
    if (!car)
        car = ctrl->f_03b518(a);
    f_0eb6b8(v, car);
    f_021720();
    MapMgr *mm = &D_23c820;
    LightSetup *ls = &mm->light;
    float *c4 = ls->c4;
    float *dir = ls->dir;
    float *c1 = ls->c1;
    float *c2 = ls->c2;
    unsigned int *p;

    f_118380(ls->m144);
    f_1184d8(1);
    f_1185dc(0, 1, 0);
    f_1185dc(0, 2, 0);
    f_1185dc(0, 4, Pack(c4));
    f_118428(0, 0, 6, dir);
    f_1185dc(1, 1, Pack(c1));
    f_1185dc(1, 2, Pack(c2));
    f_1185dc(1, 4, 0);
    f_118428(1, 0, 2, dir);
    f_1185dc(2, 1, Pack(c1));
    f_1185dc(2, 2, Pack(c2));
    f_1185dc(2, 4, Pack(c4));
    f_118428(2, 0, 6, dir);
    f_116898(11);
    f_116898(12);
    f_116898(13);
    f_116898(14);
    f_118b64(ls->m232, ls->m236, ls->m240);
    f_021750();
    p = f_0216d8();
    p = f_0cc584(v, p);
    p = f_029524(mm, 0, v, p);
    if (D_27ec88)
        *p++ = 0x9b000000;
    f_0216e8(p);

    f_0eaeb0(a, v, ctrl, car);

    f_021720();
    f_118380(ls->m144);
    f_1184d8(1);
    f_1185dc(0, 1, 0);
    f_1185dc(0, 2, 0);
    f_1185dc(0, 4, Pack(c4));
    f_118428(0, 0, 6, dir);
    f_1185dc(1, 1, Pack(c1));
    f_1185dc(1, 2, Pack(c2));
    f_1185dc(1, 4, 0);
    f_118428(1, 0, 2, dir);
    f_1185dc(2, 1, Pack(c1));
    f_1185dc(2, 2, Pack(c2));
    f_1185dc(2, 4, Pack(c4));
    f_118428(2, 0, 6, dir);
    f_116898(11);
    f_116898(12);
    f_116898(13);
    f_116898(14);
    f_118b64(ls->m232, ls->m236, ls->m240);
    f_021750();
    p = f_0216d8();
    p = f_0cc584(v, p);
    p = f_029524(mm, 4, v, p);
    if (D_27ec88)
        *p++ = 0x9b000000;
    f_0216e8(p);

    if (v->m660 != 0x20003)
        D_2402e0.f_031cbc(v);
    if (f_0ea8a8() && ((D_1d5a90 != 0) & (v2 != 0))) {
        if (D_27ecb1 != 2)
            f_0eb440(v2, v, 0);
    }
    if (D_2407fc->m20)
        D_27f100.Set(0, 0.0f);
    else
        D_27f100.Set(car->m2108, car->m1792);
    p = f_0216d8();
    p = D_27f100.f_0ff81c(v, p);
    if (D_27ec88) {
        *p++ = 0x9b000001;
        p = f_0cc4e4(2048, 2048, 480, 272, p);
    } else {
        *p++ = 0x9b000000;
    }
    f_0216e8(p);
    D_27ecb0 = 0;
}

/* @implements 0x0ec1cc us f_0ec1cc
   WHAT IT DOES: Draws the race's 2D overlay: its first pass always, its second pass unless
   the game is running normally with the blink on and its second flag off. */
void f_0ec1cc(void)
{
    D_1d3d40->v4();
    if (D_1d88a0->m11 || D_1d88a0->m12 || !D_27ecb1 || D_27ecb2)
        D_1d3d40->v5();
}
