/* The car model (retail 0x01dbc4 to 0x02048c): a car's body as the race draws it. It reads the
   car's model header (wheel positions, light positions, body colours), places the body and
   its four wheels every frame from the car's physics state (steering, suspension, wheel spin),
   keeps the brake, head and tail light levels, and draws the light flares. Most of the matrix
   work runs on the vector unit, through the matrix stack helpers at 0x028188 to 0x028eb4.
   The file's static data (two circles of flare offsets), its startup entry and the model's
   inline constructors close the object file (0x0201b4 to 0x02048c). */

#include <math.h>

extern "C" {
int f_026ab0(void *res, int a, int b);
void f_026bc8(void *res, int r, int g, int b);
void f_026e5c(void *res);
void f_026ed8(void *res);
void f_026efc(void *g);
void f_026f70(void *res);
int f_024fb4(void *model);
void f_025118(void *model, int anim);
void f_025154(void *model, int anim, int arg);
int f_02347c(int);
void f_028d94(void *m);
void f_028e9c(void *m);
void f_028188(void *out, void *pos, void *vel);
void f_028a00(void *a, void *b);
void f_028748(void *m);
void f_02842c(void);
void f_0287cc(float x, float y, float z);
void f_0286fc(float x, float y, float z);
void f_02df08(int);
void f_02dba8(void);
unsigned int *f_020cd4(short *pos, int a, unsigned int *list);
void *f_021b38(int size);
}

/* A vector of four floats. */
struct Vec4 {
    float x, y, z, w;
};

/* A 4x4 matrix. */
struct Mat {
    float m[16];
};

/* The car model header in the model data. */
struct CModelHeader {
    char m0[6];
    short angle;
    char m8[32];
    int m40;
    float halfWidth;
    float frontX;
    float frontY;
    float m56;
    float rearX;
    float rearY;
    float m68;
    float axle[3];
    float m84[3];
    char m96[32];
    float light[3];
    float m140;
    unsigned char m144[3];
    unsigned char m147;
    unsigned char colour[3][4];
    unsigned int colour2[3];
    unsigned char m172[3];
    signed char flags;
};

/* The model as the renderer sees it (1712 bytes). */
struct CModel {
    CModel();
    CModelHeader *data;
    int m4;
    int colour;
    int m12;
    Mat world;
    Mat inverse;
    Mat part[17];
    float m1232[15][6];
    unsigned char level[12];
    unsigned int m1604[4];
    unsigned char m1620;
    unsigned int m1624;
    unsigned int m1628;
    unsigned int m1632;
    int m1636[3];
    Vec4 m1648[2];
    int m1680[2];
    int m1688[2];
    int m1696[2];
    short m1704;
    unsigned char m1706;
    unsigned char m1707[5];
};

/* A car's physics state, as far as the model reads it. */
struct CCarState {
    char m0[128];
    int m128;
    char m132[124];
    Vec4 wheelPos[4];
    Vec4 wheelRot[4];
    char m320[256];
    Mat world;
    char m640[1088];
    float m1728;
    float m1732;
    float m1736;
    float m1740;
    char m1744[12];
    float m1756;
    char m1760[32];
    float m1792;
    int m1796;
    char m1800[312];
    int m2112;
    float m2116;
};

class CCarModel {
public:
    CCarModel();
    int f_01dbc4(CModelHeader *data, int a, int b, int colour);
    void f_01dee4();
    void f_01e14c(Mat *world, void *pos, void *vel, void *c);
    void f_01e500(Mat *world);
    void f_01e528(Mat *world, void *pos, void *vel, void *c);
    void f_01e5d0(Mat *world);
    void f_01e648(CCarState *s, Mat *world, Vec4 *pos, Vec4 *vel, void *c);
    void f_01ed64(Mat *world);
    void f_01edfc();
    void f_01ee78();
    void f_01ee98();
    void f_01eebc(int arg);
    void f_01eee4();
    void f_01f234(int a);
    void f_01f264(int a);
    unsigned int *f_01f2f0(unsigned int *list);

    Vec4 pos;
    Vec4 rot;
    Vec4 wheel[4];
    Vec4 light[2];
    Vec4 pivot[2];
    Vec4 knuckle[2];
    float steerMax;
    float steer;
    float m200;
    float m204;
    float m208;
    int m212[3];
    Vec4 wheelRot[4];
    CModel model;
    char res[16];
    char m2016[656];
    float m2672;
    float m2676;
    float m2680;
    float m2684;
    float m2688;
    float m2692;
    float m2696;
    float m2700;
    float m2704;
    float m2708;
    float m2712;
    float m2716;
    unsigned char col[3];
    unsigned char m2723;
    signed char mode;
    unsigned char m2725;
    signed char anim;
    unsigned char m2727;
    unsigned char m2728;
    char m2729[7];
};
typedef char CCarModelSize[sizeof(CCarModel) == 2736 ? 1 : -1];
typedef char CModelSize[sizeof(CModel) == 1712 ? 1 : -1];

float f_01df1c(float x);
float f_01df34(float x);
float f_01df48(float x);
float f_01df78(float x);
float f_01dfd8(float x);
void f_01e028(Vec4 *pos, Vec4 *at, Vec4 *rot, Mat *a, Mat *b, Mat *c);
void f_01e094(Vec4 *pos, Vec4 *at, Vec4 *rot, Mat *a, Mat *b, Mat *c);
void f_01e0ec(Vec4 *pivot, Vec4 *at, Mat *out, float angle);
void f_01edb8(float *out, Mat *m);

extern Vec4 D_1d1750;
extern Vec4 D_1d1760;
extern float D_1d1770[];
extern Vec4 D_1d1780;
extern Vec4 D_1d1790;
extern float D_1d17a0[];
extern unsigned char D_1d17b0[][3];
struct CColour12 {
    unsigned char r;
    char m1[3];
    unsigned char g;
    char m5[3];
    unsigned char b;
    char m9[3];
};
extern CColour12 D_1d1800[];
int D_23c0c0;
int D_23c0c4;

/* @draft 0x01dbc4 us f_01dbc4
   WHAT IT DOES: Sets the model up from its model data: the resource it draws with, the wheel,
   light and axle positions (halved, mirrored left to right, then scaled from model units),
   the steering limit, the body colour (one of the car's colour sets) and the light flags.
   Returns 0 if the resource or the model data cannot be set up. */
int CCarModel::f_01dbc4(CModelHeader *data, int a, int b, int colour)
{
    CCarModel tmp;

    if (!f_026ab0(res, a, b))
        return 0;
    model.data = data;
    if (!f_024fb4(&model))
        return 0;
    CModelHeader *h = model.data;
    *(int *)m2016 = h->m40;
    f_026efc(m2016);
    h = model.data;
    float hw = h->halfWidth;
    float fx = h->frontX;
    float rx = h->rearX;
    wheel[0].x = -fx * 0.5f;
    wheel[0].y = h->frontY;
    wheel[0].z = -hw * 0.5f;
    wheel[1].x = fx * 0.5f;
    wheel[1].y = h->frontY;
    wheel[1].z = -hw * 0.5f;
    wheel[2].x = -rx * 0.5f;
    wheel[2].y = h->rearY;
    wheel[2].z = hw * 0.5f;
    wheel[3].x = rx * 0.5f;
    wheel[3].y = h->rearY;
    wheel[3].z = hw * 0.5f;
    light[0].x = h->light[0];
    light[0].y = h->light[1];
    light[0].z = h->light[2];
    light[1].x = -h->light[0];
    light[1].y = h->light[1];
    light[1].z = h->light[2];
    m2716 = h->m140 * 0.5f * 136.0f;
    col[0] = h->m144[0];
    col[1] = h->m144[1];
    col[2] = h->m144[2];
    pivot[0].x = h->axle[0];
    pivot[0].y = h->axle[1];
    pivot[0].z = h->axle[2];
    pivot[1].x = -h->axle[0];
    pivot[1].y = h->axle[1];
    pivot[1].z = h->axle[2];
    knuckle[0].x = h->m84[0];
    knuckle[0].y = h->m84[1];
    knuckle[0].z = h->m84[2];
    knuckle[1].x = h->m84[0];
    knuckle[1].y = -h->m84[1];
    knuckle[1].z = -h->m84[2];
    steerMax = h->angle * 3.1415927f / 180.0f;
    steer = 0.0f;
    for (int i = 0; i < 4; i++) {
        wheel[i].x *= 0.00024414062f;
        wheel[i].y *= 0.00024414062f;
        wheel[i].z *= 0.00024414062f;
    }
    for (int i = 0; i < 2; i++) {
        pivot[i].x *= 0.00024414062f;
        pivot[i].y *= 0.00024414062f;
        pivot[i].z *= 0.00024414062f;
    }
    m2723 = h->flags & 1;
    mode = (h->flags >> 1) & 3;
    f_026bc8(res, h->colour[colour][0], h->colour[colour][1], h->colour[colour][2]);
    f_026e5c(res);
    h = model.data;
    model.m1604[3] = model.m1604[2] = h->colour2[colour] & 0xffffff;
    unsigned int v = h->colour[colour][3];
    model.m1604[0] = v | v << 8 | v << 16;
    v = h->colour2[colour] >> 24;
    model.m1604[1] = v | v << 8 | v << 16;
    model.m1620 = h->m172[colour];
    model.colour = colour;
    return 1;
}

/* @draft 0x01dee4 us f_01dee4
   WHAT IT DOES: Releases the model's resource and switches its animation table off. */
void CCarModel::f_01dee4()
{
    f_026ed8(res);
    *(int *)m2016 = 0;
    f_026efc(m2016);
}

/* @implements 0x01df1c us f_01df1c
   WHAT IT DOES: Moves a light level a fifth of the way up towards full. */
float f_01df1c(float x)
{
    return x + 0.2f - x * 0.2f;
}

/* @implements 0x01df34 us f_01df34
   WHAT IT DOES: Moves a light level a fifth of the way down towards off. */
float f_01df34(float x)
{
    return x - x * 0.2f;
}

/* @implements 0x01df48 us f_01df48
   WHAT IT DOES: Fades a light level down by a tenth (twice), switching it off once it drops
   below a tenth. */
float f_01df48(float x)
{
    x = x - x * 0.1f;
    if (x < 0.1f)
        x = 0.0f;
    return x - x * 0.1f;
}

/* @implements 0x01df78 us f_01df78
   WHAT IT DOES: Brightens a light level: slowly while below 0.8 (jumping to 0.8 once past
   0.05), faster above it, up to full. */
float f_01df78(float x)
{
    if (x < 0.8f) {
        x += 0.01f;
        if (0.05f < x)
            x = 0.8f;
    } else {
        x += 0.02f;
        if (1.0f < x)
            x = 1.0f;
    }
    return x;
}

/* @implements 0x01dfd8 us f_01dfd8
   WHAT IT DOES: Dims a light level: down to 0.2 at once, then by 0.02 a frame, off below a
   tenth. */
float f_01dfd8(float x)
{
    if (0.2f < x) {
        x = 0.2f;
    } else {
        x -= 0.02f;
        if (x < 0.1f)
            x = 0.0f;
    }
    return x;
}

/* @implements 0x01e028 us f_01e028
   WHAT IT DOES: Builds a front wheel's three matrices on the vector unit: its position (the
   physics wheel position scaled by the model scale), its steering and spin rotations, and the
   combined placement of the wheel at its mounting point. */
void f_01e028(Vec4 *pos, Vec4 *at, Vec4 *rot, Mat *a, Mat *b, Mat *c)
{
    __asm__ volatile(
        "lv.q C030.q, 0(%0)\n"
        "\tvscl.t C430.t, C030.t, S000.s\n"
        "\tlv.q C030.q, 0(%1)\n"
        "\tlv.q C020.q, 0(%2)\n"
        "\tvscl.t C020.t, C020.t, S001.s\n"
        "\tvmidt.q M300.q\n"
        "\tvrot.t C310.t, S020.s, [0, c, s]\n"
        "\tvrot.t C320.t, S020.s, [0, -s, c]\n"
        "\tvmidt.q M200.q\n"
        "\tvrot.t C200.t, S021.s, [c, 0, -s]\n"
        "\tvrot.t C220.t, S021.s, [s, 0, c]\n"
        "\tvmmul.t M100.t, M200.t, M300.t\n"
        "\tvzero.t R103.t\n"
        "\tsv.q C200.q, 0(%3)\n"
        "\tsv.q C210.q, 16(%3)\n"
        "\tsv.q C220.q, 32(%3)\n"
        "\tsv.q C430.q, 48(%3)\n"
        "\tsv.q C100.q, 0(%4)\n"
        "\tsv.q C110.q, 16(%4)\n"
        "\tsv.q C120.q, 32(%4)\n"
        "\tsv.q C430.q, 48(%4)\n"
        "\tsv.q C300.q, 0(%5)\n"
        "\tsv.q C310.q, 16(%5)\n"
        "\tsv.q C320.q, 32(%5)\n"
        "\tsv.q C030.q, 48(%5)\n"
        "1:"
        : : "r"(pos), "r"(at), "r"(rot), "r"(a), "r"(b), "r"(c) : "memory");
}

/* @implements 0x01e094 us f_01e094
   WHAT IT DOES: Builds a rear wheel's three matrices on the vector unit: its position, its
   spin rotation, and its placement at the mounting point (rear wheels do not steer). */
void f_01e094(Vec4 *pos, Vec4 *at, Vec4 *rot, Mat *a, Mat *b, Mat *c)
{
    __asm__ volatile(
        "lv.q C030.q, 0(%0)\n"
        "\tvscl.t C430.t, C030.t, S000.s\n"
        "\tlv.q C030.q, 0(%1)\n"
        "\tlv.q C020.q, 0(%2)\n"
        "\tvscl.t C020.t, C020.t, S001.s\n"
        "\tvmidt.q M300.q\n"
        "\tvrot.t C310.t, S020.s, [0, c, s]\n"
        "\tvrot.t C320.t, S020.s, [0, -s, c]\n"
        "\tsv.q C400.q, 0(%3)\n"
        "\tsv.q C410.q, 16(%3)\n"
        "\tsv.q C420.q, 32(%3)\n"
        "\tsv.q C430.q, 48(%3)\n"
        "\tsv.q C300.q, 0(%4)\n"
        "\tsv.q C310.q, 16(%4)\n"
        "\tsv.q C320.q, 32(%4)\n"
        "\tsv.q C430.q, 48(%4)\n"
        "\tsv.q C300.q, 0(%5)\n"
        "\tsv.q C310.q, 16(%5)\n"
        "\tsv.q C320.q, 32(%5)\n"
        "\tsv.q C030.q, 48(%5)\n"
        "1:"
        : : "r"(pos), "r"(at), "r"(rot), "r"(a), "r"(b), "r"(c) : "memory");
}

/* @implements 0x01e0ec us f_01e0ec
   WHAT IT DOES: Builds the matrix of a steering knuckle on the vector unit: the pivot's
   rotations, then the steering angle (added to the knuckle's own angle), placed at the
   pivot. */
void f_01e0ec(Vec4 *pivot, Vec4 *at, Mat *out, float angle)
{
    __asm__ volatile(
        "lv.q C430.q, 0(%0)\n"
        "\tlv.q C020.q, 0(%1)\n"
        "\tlv.s S030.s, %3\n"
        "\tvadd.s S020.s, S020.s, S030.s\n"
        "\tvscl.t C020.t, C020.t, S001.s\n"
        "\tvmidt.q M300.q\n"
        "\tvmidt.q M200.q\n"
        "\tvrot.t C300.t, S022.s, [c, s, 0]\n"
        "\tvrot.t C310.t, S022.s, [-s, c, 0]\n"
        "\tvrot.t C200.t, S021.s, [c, 0, -s]\n"
        "\tvrot.t C220.t, S021.s, [s, 0, c]\n"
        "\tvmmul.t M100.t, M300.t, M200.t\n"
        "\tvmidt.q M200.q\n"
        "\tvrot.t C210.t, S020.s, [0, c, s]\n"
        "\tvrot.t C220.t, S020.s, [0, -s, c]\n"
        "\tvmmul.t M300.t, M100.t, M200.t\n"
        "\tsv.q C300.q, 0(%2)\n"
        "\tsv.q C310.q, 16(%2)\n"
        "\tsv.q C320.q, 32(%2)\n"
        "\tsv.q C430.q, 48(%2)"
        : : "r"(pivot), "r"(at), "r"(out), "m"(angle) : "memory");
}

/* The model scale on the vector unit (model units per world unit). */
static const float kModelScale = 0.00024414062f;

/* How far ahead along the velocity the lights are placed. */
static const float kLightLead = 25.0f;

/* Vector unit helpers. The matrix in M300 is the one being built; M200 and M100 are scratch. */
static inline void VLoadM300(const Mat *m)
{
    __asm__ volatile(
        "lv.q C300.q, 0(%0)\n"
        "\tlv.q C310.q, 16(%0)\n"
        "\tlv.q C320.q, 32(%0)\n"
        "\tlv.q C330.q, 48(%0)"
        : : "r"(m) : "memory");
}

static inline void VStoreM300(Mat *m)
{
    __asm__ volatile(
        "sv.q C300.q, 0(%0)\n"
        "\tsv.q C310.q, 16(%0)\n"
        "\tsv.q C320.q, 32(%0)\n"
        "\tsv.q C330.q, 48(%0)"
        : : "r"(m) : "memory");
}

/* Multiplies the given matrix by M300 and stores the product. */
static inline void VMulStore(const Mat *a, Mat *out)
{
    __asm__ volatile(
        "lv.q C200.q, 0(%0)\n"
        "\tlv.q C210.q, 16(%0)\n"
        "\tlv.q C220.q, 32(%0)\n"
        "\tlv.q C230.q, 48(%0)\n"
        "\tvmmul.q M100.q, M200.q, M300.q\n"
        "\tsv.q C100.q, 0(%1)\n"
        "\tsv.q C110.q, 16(%1)\n"
        "\tsv.q C120.q, 32(%1)\n"
        "\tsv.q C130.q, 48(%1)"
        : : "r"(a), "r"(out) : "memory");
}

/* Stores the inverse of the rigid matrix M300 (transposed rotation, moved translation). */
static inline void VStoreInverse(Mat *out)
{
    __asm__ volatile(
        "vmmov.t M200.t, E300.t\n"
        "\tvtfm3.t C230.t, M300.t, C330.t\n"
        "\tvneg.t C230.t, C230.t\n"
        "\tsv.q C200.q, 0(%0)\n"
        "\tsv.q C210.q, 16(%0)\n"
        "\tsv.q C220.q, 32(%0)\n"
        "\tsv.q C230.q, 48(%0)"
        : : "r"(out) : "memory");
}

/* Scales the translation of the current matrix (M700) to model units. */
static inline void VScaleTranslation()
{
    __asm__ volatile("lv.s S400.s, %0\n\tvscl.t C730.t, C730.t, S400.s" : : "m"(kModelScale));
}

/* Loads the wheel scales into S000 and S001 and sets M400 to the identity. */
static inline void VWheelScale(const Vec4 *scale)
{
    __asm__ volatile("lv.s S000.s, 0(%0)\n\tlv.s S001.s, 4(%0)\n\tvmidt.q M400.q"
                     : : "r"(scale));
}


/* @draft 0x01e14c us f_01e14c
   WHAT IT DOES: Places the model for drawing. It clears the hidden flags, saves the current
   matrix, computes the model's world matrix and its inverse, builds the light matrices from
   the given position, velocity and lighting, then builds every wheel's matrices (the front
   wheels steer; how much depends on the model's steering mode) and the two steering
   knuckles, the shadow vectors, and restores the matrix. */
void CCarModel::f_01e14c(Mat *world, void *p, void *v, void *c)
{
    Vec4 tmp;
    Mat save;
    Vec4 wpos;
    Vec4 wrot;
    float a;

    m2727 = 0;
    m2728 = 0;
    f_028d94(&save);
    VLoadM300(&model.part[0]);
    VMulStore(world, &model.world);
    VStoreInverse(&model.inverse);
    f_028188(&tmp, p, v);
    f_028e9c(&model.inverse);
    f_028a00(&tmp, c);
    f_028748(&model.part[0]);
    VScaleTranslation();
    f_028d94(&model.part[16]);
    f_028e9c(&model.inverse);
    f_028a00(&tmp, &D_1d1750);
    f_028748(&model.part[0]);
    VScaleTranslation();
    f_028d94(&model.part[15]);
    VWheelScale(&D_1d1760);

    wpos.x = wheel[0].x;
    wpos.y = wheel[0].y;
    wpos.z = wheel[0].z;
    if (mode == 1) {
        wrot.x = 0;
        wrot.y = 0;
        wrot.z = wheelRot[0].z;
    } else if (mode == 2) {
        wrot.x = wheelRot[0].x;
        wrot.y = 0;
        wrot.z = wheelRot[0].z;
    } else {
        wrot.x = wheelRot[0].x;
        wrot.y = wheelRot[0].y;
        wrot.z = wheelRot[0].z;
    }
    f_01e028(&wpos, &wheel[0], &wrot, &model.part[5], &model.part[1], &model.part[9]);
    wpos.x = wheel[1].x;
    wpos.y = wheel[1].y;
    wpos.z = wheel[1].z;
    if (mode == 1) {
        wrot.x = 0;
        wrot.y = 0;
        wrot.z = wheelRot[1].z;
    } else if (mode == 2) {
        wrot.x = wheelRot[1].x;
        wrot.y = 0;
        wrot.z = wheelRot[1].z;
    } else {
        wrot.x = wheelRot[1].x;
        wrot.y = wheelRot[1].y;
        wrot.z = wheelRot[1].z;
    }
    f_01e028(&wpos, &wheel[1], &wrot, &model.part[6], &model.part[2], &model.part[10]);
    wpos.x = wheel[2].x;
    wpos.y = wheel[2].y;
    wpos.z = wheel[2].z;
    f_01e094(&wpos, &wheel[2], &wheelRot[2], &model.part[7], &model.part[3], &model.part[11]);
    wpos.x = wheel[3].x;
    wpos.y = wheel[3].y;
    wpos.z = wheel[3].z;
    f_01e094(&wpos, &wheel[3], &wheelRot[3], &model.part[8], &model.part[4], &model.part[12]);

    if (mode == 1) {
        a = 0.0f;
        if (!(wheelRot[0].y <= a)) {
            a = wheelRot[0].y + wheelRot[0].y;
            if (0.69813174f < a)
                a = 0.69813174f;
        }
    } else if (mode == 2) {
        a = wheelRot[0].x;
    } else {
        a = steer;
    }
    f_01e0ec(&pivot[0], &knuckle[0], &model.part[13], a);
    if (mode == 1) {
        a = 0.0f;
        if (!(a <= wheelRot[1].y)) {
            a = -wheelRot[1].y + -wheelRot[1].y;
            if (0.69813174f < a)
                a = 0.69813174f;
        }
    } else if (mode == 2) {
        a = wheelRot[1].x;
    } else {
        a = steer;
    }
    f_01e0ec(&pivot[1], &knuckle[1], &model.part[14], a);
    f_01edfc();
    f_028e9c(&save);
}

/* @draft 0x01e500 us f_01e500
   WHAT IT DOES: Places the model for drawing with the default lighting and no velocity. */
void CCarModel::f_01e500(Mat *world)
{
    f_01e14c(world, &model.part[0].m[12], &model.part[0].m[4], D_1d1770);
}

/* @draft 0x01e528 us f_01e528
   WHAT IT DOES: Builds the model's own matrix from its position and rotation, stores it as the
   body matrix, and places the model for drawing. */
void CCarModel::f_01e528(Mat *world, void *p, void *v, void *c)
{
    Mat save;

    f_028d94(&save);
    f_02842c();
    f_0287cc(pos.x, pos.y, pos.z);
    f_0286fc(rot.x, rot.y, rot.z);
    f_028d94(&model.part[0]);
    f_028e9c(&save);
    f_01e14c(world, p, v, c);
}

/* @draft 0x01e5d0 us f_01e5d0
   WHAT IT DOES: Builds the model's own matrix from its position and rotation, stores it as the
   body matrix, and places the model with the default lighting. */
void CCarModel::f_01e5d0(Mat *world)
{
    Mat save;

    f_028d94(&save);
    f_02842c();
    f_0287cc(pos.x, pos.y, pos.z);
    f_0286fc(rot.x, rot.y, rot.z);
    f_028d94(&model.part[0]);
    f_028e9c(&save);
    f_01e500(world);
}

/* Converts a level from 0 to 255 to a byte, as the game does (through an unsigned int). */
static inline unsigned char Level(float f)
{
    return (unsigned int)f;
}

/* @draft 0x01e648 us f_01e648
   WHAT IT DOES: Updates the model from the car's physics state each frame: whether the car is
   hidden or braking, the drift light level (from the slip angle), the brake, head and reverse
   light levels, the steering in one mode and the engine glow in another, the body and inverse
   matrices, the light matrices (moving the light along the velocity), then every wheel's
   matrices and the steering knuckles. */
void CCarModel::f_01e648(CCarState *s, Mat *world, Vec4 *p, Vec4 *v, void *c)
{
    Vec4 tmp;
    Mat save;
    Vec4 wrot;
    Vec4 *rp;
    float a, t, f, g;

    m2727 = s->m128;
    if ((signed char)m2727 != 0)
        return;
    m2728 = s->m1796 != 0;
    m2725 = s->m2112;
    double d = s->m2116;
    if (d < 0.0)
        d = -d;
    a = (float)d;
    if (a < 0.2617994f)
        t = 0.0f;
    else if (a < 1.2217306f)
        t = (a - 0.2617994f) / 0.9599312f;
    else
        t = 1.0f;
    t = t * 255.0f;
    model.level[9] = Level(255.0f - t);
    model.level[10] = Level(t);
    model.level[1] = Level(s->m1728 * 255.0f);
    model.level[2] = Level(s->m1728 * 255.0f);
    f = s->m1736 * 255.0f;
    model.level[3] = Level(f);
    m2672 = f;
    f = s->m1740 * 255.0f;
    model.level[4] = Level(f);
    m2676 = f;
    if (mode == 2)
        m200 = s->m2116 * 0.2f;
    if (mode == 3) {
        g = s->m1792 * 255.0f;
        if (s->m1756 < -10000.0f)
            f = 0.0f;
        else if (s->m1756 < 14000.0f)
            f = (s->m1756 - -10000.0f) / 24000.0f * 255.0f;
        else
            f = 255.0f;
        if (f < g)
            f = g;
        model.level[7] = Level(f);
        model.level[5] = Level(g);
    }
    f_028d94(&save);
    VLoadM300(&s->world);
    VStoreM300(&model.part[0]);
    VMulStore(world, &model.world);
    VStoreInverse(&model.inverse);
    __asm__ volatile(
        "lv.q C210.q, 0(%0)\n"
        "\tlv.s S220.s, %2\n"
        "\tlv.q C200.q, 0(%1)\n"
        "\tvscl.t C210.t, C210.t, S220.s\n"
        "\tvadd.t C200.t, C200.t, C210.t\n"
        "\tsv.q C200.q, 0(%1)"
        : : "r"(v), "r"(p), "m"(kLightLead) : "memory");
    f_028188(&tmp, p, v);
    f_028e9c(&model.inverse);
    f_028a00(&tmp, c);
    f_028748(&model.part[0]);
    VScaleTranslation();
    f_028d94(&model.part[16]);
    f_028e9c(&model.inverse);
    f_028a00(&tmp, &D_1d1780);
    f_028748(&model.part[0]);
    VScaleTranslation();
    f_028d94(&model.part[15]);
    VWheelScale(&D_1d1790);

    rp = &s->wheelRot[1];
    if (mode == 1) {
        wrot.x = 0;
        wrot.y = 0;
        wrot.z = s->wheelRot[1].z;
        rp = &wrot;
    } else if (mode == 2) {
        wrot.x = s->wheelRot[1].x;
        wrot.y = 0;
        wrot.z = s->wheelRot[1].z;
        rp = &wrot;
    }
    f_01e028(&s->wheelPos[1], &wheel[0], rp, &model.part[5], &model.part[1], &model.part[9]);
    rp = &s->wheelRot[0];
    if (mode == 1) {
        wrot.x = 0;
        wrot.y = 0;
        wrot.z = s->wheelRot[0].z;
        rp = &wrot;
    } else if (mode == 2) {
        wrot.x = s->wheelRot[0].x;
        wrot.y = 0;
        wrot.z = s->wheelRot[0].z;
        rp = &wrot;
    }
    f_01e028(&s->wheelPos[0], &wheel[1], rp, &model.part[6], &model.part[2], &model.part[10]);
    f_01e094(&s->wheelPos[3], &wheel[2], &s->wheelRot[3], &model.part[7], &model.part[3],
             &model.part[11]);
    f_01e094(&s->wheelPos[2], &wheel[3], &s->wheelRot[2], &model.part[8], &model.part[4],
             &model.part[12]);

    if (mode == 1) {
        a = 0.0f;
        if (!(s->wheelRot[1].y <= a)) {
            a = s->wheelRot[1].y + s->wheelRot[1].y;
            if (0.69813174f < a)
                a = 0.69813174f;
        }
    } else if (mode == 2) {
        a = -m208;
    } else {
        a = steer;
    }
    f_01e0ec(&pivot[0], &knuckle[0], &model.part[13], a);
    if (mode == 1) {
        a = 0.0f;
        if (!(a <= s->wheelRot[0].y)) {
            a = -s->wheelRot[0].y + -s->wheelRot[0].y;
            if (0.69813174f < a)
                a = 0.69813174f;
        }
    } else if (mode == 2) {
        a = -m208;
    } else {
        a = steer;
    }
    f_01e0ec(&pivot[1], &knuckle[1], &model.part[14], a);
    f_01edfc();
    f_028e9c(&save);
}

/* @draft 0x01ed64 us f_01ed64
   WHAT IT DOES: Unless the model is hidden, recomputes its world matrix from the given matrix
   and its body matrix. */
void CCarModel::f_01ed64(Mat *world)
{
    m2727 &= 1;
    if (!m2727) {
        VLoadM300(&model.part[0]);
        VMulStore(world, &model.world);
    }
}

/* @implements 0x01edb8 us f_01edb8
   WHAT IT DOES: Transforms the two shadow vectors (left on the vector unit) by a matrix's
   rotation and stores the six results interleaved. */
void f_01edb8(float *out, Mat *m)
{
    __asm__ volatile(
        "lv.q C300.q, 0(%1)\n"
        "\tvdot.t S303.s, C400.t, C300.t\n"
        "\tlv.q C310.q, 16(%1)\n"
        "\tvdot.t S313.s, C400.t, C310.t\n"
        "\tlv.q C320.q, 32(%1)\n"
        "\tvdot.t S323.s, C400.t, C320.t\n"
        "\tsv.s S303.s, 0(%0)\n"
        "\tsv.s S313.s, 8(%0)\n"
        "\tsv.s S323.s, 16(%0)\n"
        "\tvdot.t S303.s, C410.t, C300.t\n"
        "\tvdot.t S313.s, C410.t, C310.t\n"
        "\tvdot.t S323.s, C410.t, C320.t\n"
        "\tsv.s S303.s, 4(%0)\n"
        "\tsv.s S313.s, 12(%0)\n"
        "\tsv.s S323.s, 20(%0)\n"
        "1:"
        : : "r"(out), "r"(m) : "memory");
}

/* @draft 0x01edfc us f_01edfc
   WHAT IT DOES: Computes the shadow vectors: the world matrix's first two columns, negated,
   stored for the body and transformed into each steering knuckle's frame. */
void CCarModel::f_01edfc()
{
    __asm__ volatile(
        "lv.s S400.s, 0(%0)\n"
        "\tlv.s S401.s, 16(%0)\n"
        "\tlv.s S402.s, 32(%0)\n"
        "\tlv.s S410.s, 4(%0)\n"
        "\tlv.s S411.s, 20(%0)\n"
        "\tlv.s S412.s, 36(%0)\n"
        "\tvneg.t C400.t, C400.t\n"
        "\tvneg.t C410.t, C410.t"
        : : "r"(&model.world) : "memory");
    __asm__ volatile(
        "sv.s S400.s, 0(%0)\n"
        "\tsv.s S410.s, 4(%0)\n"
        "\tsv.s S401.s, 8(%0)\n"
        "\tsv.s S411.s, 12(%0)\n"
        "\tsv.s S402.s, 16(%0)\n"
        "\tsv.s S412.s, 20(%0)"
        : : "r"(model.m1232[0]) : "memory");
    f_01edb8(model.m1232[13], &model.part[13]);
    f_01edb8(model.m1232[14], &model.part[14]);
}

/* @implements 0x01ee78 us f_01ee78
   WHAT IT DOES: Starts the model's current animation. */
void CCarModel::f_01ee78()
{
    f_025118(&model, anim);
}

/* @implements 0x01ee98 us f_01ee98
   WHAT IT DOES: Starts the second variant of the model's current animation. */
void CCarModel::f_01ee98()
{
    f_025118(&model, anim + 4);
}

/* @implements 0x01eebc us f_01eebc
   WHAT IT DOES: Passes a value to the model's current animation. */
void CCarModel::f_01eebc(int arg)
{
    f_025154(&model, anim, arg);
}
