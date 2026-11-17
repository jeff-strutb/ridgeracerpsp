/* The race sequence's common part (retail 0x0ea8b4 to 0x0ec254): the state every race sequence
   (normal circuit, time attack, network) shares. It records the race's car list and number,
   reads the sequence number from the race table, registers every car with the race's car
   manager (D_27eca4) and its fade, sets up the small race texture, and steps the per-frame
   draw of the race view and the two blinking flags (D_27ecb1, D_27ecb2) that drive the 2D
   overlay's blink. */

#include <string.h>

struct View;
/* The fade sequence (FadeSequence.cpp). */
class CFadeSequence {
public:
    void f_0ff798();
    void f_0ff7f0();
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
    void f_0caab4(View *view);
    void f_0cac40();
    unsigned int *f_0cac88(int flags, View *view, unsigned int *dl);
    unsigned int *f_0cb114(View *view, unsigned int *dl);
    unsigned int *f_0cb2ac(int flags, View *view, unsigned int *dl);
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
extern signed char D_27ecb0;
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
    char p244[248];
    int m492;
    float m496;
};

/* The map manager, as far as the race view draw uses it. */
struct MapMgr {
    char p0[12248];
    int m12248;
    char p12252[260];
    LightSetup light;
};
extern MapMgr D_23c820;

/* One view of the race (752 bytes). */
struct View {
    View() {}
    float m0 __attribute__((aligned(16)));  /* camera position */
    float m4, m8;
    char m12[276];
    char m288[192];         /* the view's camera matrix */
    float m480;             /* lens angle */
    float m484;             /* aspect */
    float m488;             /* near */
    float m492;             /* far */
    float m496;             /* lens scale */
    int m500;
    int m504;
    int m508;
    int m512;
    int m516;
    float m520;
    float m524;
    char m528[80];
    float m608, m612, m616; /* camera angles */
    char m620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char m676[12];
    float m688, m692, m696; /* camera target */
    char m700[4];
    float m704;
    char m708[40];

    /* The picture size settings for a w by h picture centred at (ox, oy). */
    void SetScreen(int w, int h, float half, int ox = 2048, int oy = 2048)
    {
        m504 = m500 * w;
        m508 = h;
        m512 = ox;
        m516 = oy;
        m520 = w * half;
        m524 = h * half;
    }
};

/* The race effects (RaceEffects.cpp). */
class CRaceEffects {
public:
    void f_031c40(View *view);
    void f_031c04();
    void f_031cbc(View *view);
};
extern CRaceEffects D_2402e0;

/* The car job controller (CarJobCtrl.cpp). */
struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* A colour word and its bytes. */
union Col {
    unsigned int w;
    unsigned char b[4];
    void SetAlpha(unsigned char a) { b[3] = a; }
};

/* The part of the car model (at +288 of the car's model) the race view sets up: the light
   colour, the two light directions and their colours, and the shadow flag. */
struct ModelLight {
    char m0[1624];
    unsigned int col;       /* 1624 */
    char m1628[20];
    Vec4 dir[2];            /* 1648 */
    unsigned int c1[2];     /* 1680 */
    unsigned int c0[2];     /* 1688 */
    unsigned int c2[2];     /* 1696 */
    char m1704[2];
    unsigned char shadow;   /* 1706 */
};

struct RaceCar;
/* The car's model (CarModel.cpp). */
class CCarModel {
public:
    void f_01e648(RaceCar *s, void *world, Vec4 *p, Vec4 *v, void *c);
    void f_01f234(int tex);
    char m0[288];
    ModelLight light;
};

struct RaceCar {
    char m0[80];
    int m80;
    char m84[44];
    int m128;
    char m132[12];
    float m144;
    float m148;
    float m152;
    char m156[1792 - 156];
    float m1792;
    int m1796;
    char m1800[2100 - 1800];
    float m2100;
    char m2104[4];
    int m2108;
    char m2112[16];
    Vec4 m2128;
    float m2144;
    char m2148[44];
    float m2192;
    float m2196;
    float m2200;
    char m2204[3040 - 2204];
    CCarModel model;
};
class CCarJobCtrl {
public:
    RaceCar *f_03b518(int i);
    char m0[12];
    int nplayers;
    int nrivals;
    char m20[12];
    char **cars;
};

/* The course light on the cars (MapLight.cpp). */
struct MapLight {
    char m0[48];
    char m48;
    char m49;
    char m50[2];
    unsigned int col[6];
    unsigned int m76;
    Vec4 m80[2];
    Vec4 m112;
    int m128;
};
extern MapLight D_23ffc0;
void f_02d420(MapLight *l, Vec4 *pos, int max, float dir);
void f_100f78(RaceCar *c, int idx, unsigned int col, int all);



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

/* The camera and matrix helpers (Transform.cpp and others). */
struct Matrix {
    float m[16];
} __attribute__((aligned(16)));
void f_028c70(void);
void f_02842c(void);
void *f_0ccaec(float *p);
void f_0284fc(float a);
void f_0284bc(float a);
void f_02853c(float a);
void f_02880c(float x, float y, float z);
void f_0287b0(void);
void f_028d94(Matrix *m);
void f_028ca8(void);
void f_0cc1f4(View *v, Matrix *m);
void f_0293e4(MapMgr *mm, int a, View *v);
void f_0da098(LightSetup *ls, float a, float b);

/* The pad state. */
struct Pad {
    int m0;
    int m4;
    int m8;
};
extern Pad D_24518c;
extern int D_23ff04;

/* Sets the camera of a view on the graphics engine and works out its matrix. */
static inline void Camera(View *v, Matrix *m)
{
    f_028c70();
    f_02842c();
    float rz = v->m612;
    f_0ccaec(&rz);
    f_0284fc(rz);
    float ry = v->m608;
    f_0ccaec(&ry);
    f_0284bc(ry);
    float rx = v->m616;
    f_0ccaec(&rx);
    f_02853c(rx);
    f_02880c(v->m0, v->m4, v->m8);
    f_0287b0();
    f_028d94(m);
    f_028ca8();
    f_0cc1f4(v, m);
}

/* The 2D drawing helpers (GraphicsDraw.cpp). */
struct Pos16 {
    unsigned short x, y, z;
};
void f_022020(unsigned short depth);
unsigned int *f_02202c(int flags, unsigned int *p);
void f_02231c(const Pos16 *v, unsigned int color);
unsigned int *f_0cc438(View *v, unsigned int *p);
float f_0cd3cc(float x);
void f_02b848(float a);
unsigned int *f_021798(int psm, unsigned int width, int height, unsigned int fbp, void *zbp);
void f_021880(unsigned int *p);

/* The sub screen's frame: its size and position and its depth. */
struct SubScreen {
    char m0[12];
    int w;
    int h;
    int y;
    char m24[24];
    int depth;
    char m52[12];
    float fov;
    float m68;
    float m72;
    float m76;
};
extern SubScreen D_23fefc;
extern int D_27ec94;
extern int D_27ec98;
extern int D_27ec9c;
extern unsigned short D_1d5a94;

/* The map's scissor words for the sub screen. */
struct MapScissor {
    char m0[16];
    unsigned int m16;
    unsigned int m20;
    unsigned int m24;
};
unsigned int *f_0cc584(View *view, unsigned int *p);
unsigned int *f_029524(MapMgr *mm, int a, View *v, unsigned int *p);
unsigned int *f_0cc4e4(int a, int b, int c, int d, unsigned int *p);
extern "C" int f_0ea8a8(void);
void f_0eb440(View *v2, View *v, int a);
void f_0eb6b8(View *v, RaceCar *car);

/* @draft 0x0ea8b4 us f_0ea8b4
   WHAT IT DOES: Steps the race views for a frame. Unless the game is paused it steps the
   course lighting's frame counter and time. Records whether the second view is in use and
   whether the first one is the main view; when the race is the second one both views get
   the full 480x272 picture settings. Sets the second view's camera (while the fade allows)
   and the first one's, steps the car manager, the course lighting, the map, the fade and
   the race effects with them; then steps the blink flags from the pad: on a press of the
   view button the blink mode cycles (two modes in a race of the sequence, three when the
   main view is shown, else two), and while the button is held with the blink on the hold
   counter runs up to 21 frames before the second flag is set. Sets the first blink flag.
   Remaining difference (972 of 976 bytes): the body follows retail statement for statement.
   Retail tests the two pause flags with separate branches (the first one through an out of
   line jump) and sets the map's high part (s2) in each branch slot; here the high part is
   set in the prologue and the second test is a bnezl. A map pointer declared at the top
   made the full address a saved register (worse). The tail differences follow from the
   blink-mode branches' layout. */
void f_0ea8b4(int a, View *v, View *v2, int n)
{
    if (!(D_1d88a0->m11 || D_1d88a0->m12)) {
        D_23c820.light.m492++;
        D_23c820.light.m496 += 1.0f;
    }
    D_27ec84 = v2->m660 != -1;
    D_1d5a90 = v->m668 == 0;
    if (D_27ec88) {
        D_23ff04 = 1;
        v2->m500 = -1;
        v->m500 = -1;
        v->SetScreen(480, 272, 0.5f);
    } else {
        D_23ff04 = 0;
    }
    Matrix m;
    if (f_0ea8a8() && v2) {
        Camera(v2, &m);
        f_0293e4(&D_23c820, 1, v2);
    }
    MapMgr *mm = &D_23c820;
    Camera(v, &m);
    D_27eca4.f_0caab4(v);
    f_0da098(&mm->light, v->m704, mm->m12248);
    f_0293e4(mm, 0, v);
    D_27f100.f_0ff7f0();
    D_2402e0.f_031c04();
    int btn = D_24518c.m0;
    if (D_24518c.m8 & 1) {
        if (D_2407fc->m20) {
            D_27ecb1 = (D_27ecb1 + 1) % 2;
        } else if (D_1d5a90) {
            D_27ecb1 = (D_27ecb1 + 1) % 3;
        } else {
            if (D_27ecb1 > 1)
                D_27ecb1 = 1;
            D_27ecb1 = (D_27ecb1 + 1) % 2;
        }
    }
    if ((btn & 0xe0) == 0x40 && D_27ecb1) {
        if (D_27ecb3 > 20) {
            D_27ecb2 = 1;
        } else {
            D_27ecb3++;
            D_27ecb2 = 0;
        }
    } else {
        D_27ecb2 = 0;
        D_27ecb3 = 0;
    }
    D_27ecb0 = 1;
}

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
   DRAFT (480 of 476 bytes, 48 words): the kind tests are separate ifs (row 108), which
   gives retail's saved constants 1, 0x1001, 0x8001 and branches. Remaining: the memcpy size
   load is scheduled after the lookup result's move, and in the car loop retail fills the
   f_0caa5c slot with the manager's address and steps the counter late; here the slot is a
   nop (+4 bytes). */
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
        if (t == 1)
            kind = 0;
        else if (t == 0x1001)
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

/* @draft 0x0eaeb0 us f_0eaeb0
   WHAT IT DOES: Sets the cars up for the view's draw: every car's model is stepped from the
   car (a hidden car without its matrices); a shown car is lit by the course light at its
   position, its light colour's alpha faded by its damage level, its light colours,
   directions and shadow flag copied onto the model, and (when the race's wheel effects are
   on) its wheel effects run with the sum of the course's four light colours (clamped to
   255). Then the car manager and the race effects are set up and the cars' display list is
   recorded after the six fixed state commands, with the flags 7 or 2 (see below) and a
   second pass when the race has it.
   Remaining difference (1256 of 1268 bytes): the control flow, calls, stack temporaries and
   the flag selects match. Retail holds the course light's address only as a hoisted high
   part (s7) and its colour words through two hoisted bases (l+48, l+52 in s6/s8); here
   loop.c hoists the full address into one register, so the saved set and the frame differ.
   The light colour word lands at sp+80 (put on the stack by purge_addressof, after the
   colour array) where retail has it at sp+64 before the array; a byte-struct colour made the
   copies bytewise (worse). The shadow flag and the car's kind bit load narrow to lbu where
   retail keeps lw. */
void f_0eaeb0(int a, View *v, CCarJobCtrl *ctrl, RaceCar *unused)
{
    for (int i = 0; i < ctrl->nplayers + ctrl->nrivals; i++) {
        RaceCar *car = (RaceCar *)ctrl->cars[i];
        CCarModel *model = &car->model;
        if (car->m128) {
            model->f_01e648(car, 0, 0, 0, 0);
        } else {
            Vec4 pos = { car->m144, car->m148, car->m152 };
            f_02d420(&D_23ffc0, &pos, 0, car->m2144);
            Vec4 *q = &car->m2128;
            Vec4 p = { q->x, q->w, q->y };
            Vec4 d = { car->m2192, car->m2196, car->m2200 };
            model->f_01e648(car, v->m288, &p, &d, &D_23ffc0.m112);
            Col c[4];
            Col col;
            if (car->m1796) {
                col.w = D_23ffc0.m76;
                float t = 1.0f - car->m2100 / 1000.0f;
                if (t < 0.0f)
                    t = 0.0f;
                col.SetAlpha((unsigned int)(col.b[3] * t));
            } else {
                col.w = D_23ffc0.m76;
            }
            ModelLight *ml = &model->light;
            ml->col = col.w;
            model->f_01f234(f_0eac94());
            MapLight *l = &D_23ffc0;
            for (int k = 0; k < 2; k++) {
                ml->c1[k] = l->col[2 + k];
                ml->c0[k] = l->col[k];
                ml->c2[k] = l->col[4 + k];
                Vec4 *sd = &l->m80[k];
                Vec4 *dd = &ml->dir[k];
                dd->x = sd->x;
                dd->z = sd->z;
                dd->y = sd->y;
            }
            ml->shadow = l->m128;
            if (D_27ecb0) {
                c[1].w = D_23ffc0.col[1];
                c[0].w = D_23ffc0.col[0];
                c[2].w = D_23ffc0.col[2];
                c[3].w = D_23ffc0.col[3];
                int r = c[0].b[0] + c[1].b[0] + c[2].b[0] + c[3].b[0];
                int g = c[0].b[1] + c[1].b[1] + c[2].b[1] + c[3].b[1];
                int b = c[0].b[2] + c[1].b[2] + c[2].b[2] + c[3].b[2];
                if (r > 255)
                    r = 255;
                if (g > 255)
                    g = 255;
                if (b > 255)
                    b = 255;
                int all = 1;
                if (D_1d5a90)
                    all = !(car->m80 & 1);
                f_100f78(car, i, b << 16 | g << 8 | r, all);
            }
        }
    }
    D_27eca4.f_0cac40();
    D_2402e0.f_031c40(v);
    unsigned int *p = f_0216d8();
    *p++ = 0x5d0000ff;
    *p++ = 0x5c000000;
    *p++ = 0x17000001;
    *p++ = 0x1a000000;
    *p++ = 0x1b000000;
    *p++ = 0x1f000001;
    int flags;
    if (D_2407fc->m20) {
        flags = 0;
        if (v->m672)
            flags = v->m668 ? 2 : 7;
    } else {
        flags = !D_1d5a90 ? 2 : 7;
    }
    p = D_27eca4.f_0cac88(flags, v, p);
    if (D_27ec90)
        p = D_27eca4.f_0cb2ac(flags, v, p);
    f_0216e8(p);
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

/* @draft 0x0eb6b8 us f_0eb6b8
   WHAT IT DOES: Draws the small race texture (the rear view): a copy of the view gets the
   sub screen's lens (angle in degrees, near and far scaled by 1000), a 64x64 picture
   (mirrored when the race is the second one) centred at (1840, 1944), the car's position
   (the view's own when it is the main view), the view's angles turned round and its
   position as the target; its camera is set and the map's pass 2 recorded into the small
   texture.
   Remaining difference (896 of 900 bytes): calls, branch layout (the main view case out of
   line) and the stack layout match. Retail keeps only the sub screen's high part in s2 and
   rebuilds its address at each use (the source names D_23fefc directly; the pointer local
   here takes a saved register and shifts s1/s2), and the screen setup's stores and the
   angle copies are scheduled in another order. */
void f_0eb6b8(View *v, RaceCar *car)
{
    View lv = *v;
    SubScreen *s = &D_23fefc;
    float fov = s->fov / 180.0f * 3.14159f * 0.5f;
    lv.m484 = 1.0f;
    lv.m480 = fov;
    lv.m496 = 1.0f / f_0cd3cc(fov);
    if (D_27ec88)
        lv.SetScreen(-64, 64, 0.5f, 1840, 1944);
    else
        lv.SetScreen(64, 64, 0.5f, 1840, 1944);
    lv.m488 = s->m68 * 1000.0f;
    lv.m492 = s->m72 * 1000.0f;
    f_02b848(s->m76);
    if (!D_1d5a90) {
        lv.m0 = car->m144;
        lv.m4 = car->m148;
        lv.m8 = car->m152;
    } else {
        lv.m0 = v->m0;
        lv.m4 = v->m4;
        lv.m8 = v->m8;
    }
    lv.m608 = -v->m608;
    lv.m612 = v->m612 + 3.14159f;
    lv.m616 = v->m616;
    lv.m688 = lv.m0;
    lv.m692 = lv.m4;
    lv.m696 = lv.m8;
    Matrix m;
    Camera(&lv, &m);
    unsigned int *p = f_021798(D_27ecbc, 64, 64, D_27ecc4, (void *)D_27ecc8);
    *p++ = 0x9b000001;
    *p++ = 0x18000000;
    *p++ = 0x19000000;
    *p++ = 0x1a000000;
    *p++ = 0x1b000000;
    p = f_0cc584(&lv, p);
    f_022020(0);
    p = f_02202c(4, p);
    MapMgr *mm = &D_23c820;
    f_0293e4(mm, 2, &lv);
    p = f_029524(mm, 2, &lv, p);
    p = f_02202c(4, p);
    f_021880(p);
}

/* A colour from three floats in 0..1 as packed bytes (red lowest). */
static inline int Pack(const float *c)
{
    return (int)(c[0] * 255.0f) | (int)(c[1] * 255.0f) << 8 | (int)(c[2] * 255.0f) << 16;
}

/* @draft 0x0eb440 us f_0eb440
   WHAT IT DOES: Draws the sub screen (the second view) in its frame: a border rectangle in
   the border colour around the frame (centred on x 240), then the frame's scissor and the
   map's scissor words, the depth, the second view, the map's pass 1 and the cars' sub
   screen pass between the two second-race commands, the full screen scissor again and the
   first view's closing pass.
   Remaining difference (628 of 632 bytes): calls and arguments in retail's order; register
   allocation differs throughout (retail: frame in s4, map in s6, 0x9b000000 in s8, 240 in
   s3, the three frame fields in s1/s5/s2 across the two state calls). In the scissor words
   retail loads the frame's width, y and height before the first store; here the store comes
   first (reusing the first part's locals there kept them live in saved registers, worse;
   separate locals for the second part are the next thing to try). */
void f_0eb440(View *v2, View *v, int unused)
{
    SubScreen *f = &D_23fefc;
    unsigned int cmd = 0x9b000000;
    MapMgr *mm = &D_23c820;
    int cx = 240;
    f_021720();
    int w = f->w;
    int y = f->y;
    int h = f->h;
    f_116898(1);
    f_116898(4);
    unsigned int col = D_27ec9c << 16 | D_27ec98 << 8 | D_27ec94 | 0xff000000;
    int b = D_1d5a94;
    int x0 = cx - w / 2;
    int x1 = x0 + w;
    int y1 = y + h;
    Pos16 r[2];
    r[0].x = x0 - b;
    r[0].y = y - b;
    r[1].x = x1 + b + 1;
    r[1].y = y1 + b + 1;
    r[0].z = 0;
    r[1].z = 0;
    f_02231c(r, col);
    f_021750();
    unsigned int *p = f_0216d8();
    w = f->w;
    cx -= w / 2;
    *p++ = cx | f->y << 10 | 0xd4000000;
    *p++ = (cx + w) | (f->y + f->h) << 10 | 0xd5000000;
    MapScissor *ms = (MapScissor *)&mm->light.p244[0];
    *p++ = ms->m24;
    *p++ = ms->m16;
    *p++ = ms->m20;
    f_022020(f->depth);
    p = f_02202c(5, p);
    f_022020(0);
    p = f_0cc584(v2, p);
    p = f_029524(mm, 1, v2, p);
    *p++ = (D_27ec88 != 0) | cmd;
    p = D_27eca4.f_0cb114(v2, p);
    *p++ = (D_27ec88 == 0) | cmd;
    *p++ = 0xd4000000;
    *p++ = 0xd50441e0;
    p = f_0cc438(v, p);
    f_0216e8(p);
}

/* @draft 0x0eba3c us f_0eba3c
   WHAT IT DOES: Draws the race view of one player for a frame (the car is looked up from the
   car controller when none is given): steps the view with the car, then twice (the map's
   pass 0, then after the view's own draw its pass 4) sets the graphics engine's three lights
   from the course lighting, records the view and the course map's display list (with a
   closing command when the race is the second one); then the race effects (unless the view
   is in mode 0x20003), the second view's overlay while the fade allows it, sets the fade's
   state from the car (cleared when the race has none) and records the fade pass, closing it
   with the full screen copy when the race is the second one. Clears the first blink flag.
   Each pass's display list pointer is its own variable (one shared variable is allocated to
   a2, the fade pass's register, instead of a1).
   Remaining difference: 2 words, the second pass's f_118b64 float arguments are loaded 240
   then 236 (retail 236 then 240). Named cause (sched1, -da): in the second pass ls dies at
   the m240 load (its last use), so that insn's register weight is 0 and rank_for_schedule
   issues it first; in the first pass ls stays live and the loads keep retail's order. Retail
   needs ls not to die at the m240 load in the second pass; the source shape for that is not
   yet known. */
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
    unsigned int *p = f_0216d8();
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
    unsigned int *q = f_0216d8();
    q = f_0cc584(v, q);
    q = f_029524(mm, 4, v, q);
    if (D_27ec88)
        *q++ = 0x9b000000;
    f_0216e8(q);

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
    unsigned int *r = f_0216d8();
    r = D_27f100.f_0ff81c(v, r);
    if (D_27ec88) {
        *r++ = 0x9b000001;
        r = f_0cc4e4(2048, 2048, 480, 272, r);
    } else {
        *r++ = 0x9b000000;
    }
    f_0216e8(r);
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
