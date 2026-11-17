/* The car physics object file (retail 0x0a6f6c to 0x0af340): the per car state of the
   physics, its constructor and reset, the per frame step that moves the car's
   simulation values into their stored copies, the four wheel and suspension updates and
   the drive, brake and surface helpers they call. */

#include <math.h>

/* The physics state of one car. Offsets are the retail byte offsets. */
struct CarPhys {
    float m0;
    float m4;
    float m8;
    float m12;
    float m16;
    float m20;
    float m24;
    float m28;
    float m32;
    float m36;
    float m40;
    int m44;
    int m48;
    int m52;
    int m56;
    int m60;
    float m64;
    float m68;
    float m72;
    float m76;
    int m80;
    int m84;
    int m88;
    short m92;
    char p94[2];
    int m96;
    short m100;
    char p102[2];
    int m104;
    int m108;
    int m112;
    unsigned char m116;
    unsigned char m117;
    char p118[2];
    float m120;
    int m124;
    float m128;
    float m132;
    float m136;
    float m140;
    float m144;
    float m148;
    float m152;
    int m156;
    int m160;
    short m164;
    char p166[2];
    float m168;
    int m172;
    int m176;
    int m180;
    short m184;
    char p186[2];
    int m188;
    int m192;
    char p196[396];
    float m592;
    float m596;
    float m600;
    float m604;
    float m608;
    float m612;
    unsigned char m616;
    char p617[7];
};

/* Fields of the per wheel arrays between +196 and +592, addressed by offset. */
#define PF(q, o) ((float *)((char *)(q) + (o)))
#define PI(q, o) ((int *)((char *)(q) + (o)))
#define PH(q, o) ((short *)((char *)(q) + (o)))
extern "C" {
void f_0a7118(void *a, void *b, int c, int d, int e, float f, float g, float h);
void f_0a7118_2(void *a, void *b, int c, int d, int e, float f, float g) __asm__("f_0a7118");
void f_0a6fb4(CarPhys *p);
void f_0a9158(CarPhys *p);
void f_0a9248(CarPhys *p);
void f_0aa374(CarPhys *p);
void f_0aa608(CarPhys *p);
void f_0ab074(CarPhys *p);
void f_0ab220(CarPhys *p);
void f_0ac630(CarPhys *p);
void f_0acd80(CarPhys *p);
void f_0ad82c(CarPhys *p);
void f_0addbc(CarPhys *p);
void f_0aea0c(CarPhys *p);
void f_0aea84(CarPhys *p);
void f_0ae9f8(CarPhys *p);
void f_0a6fac(CarPhys *p);
void f_0a6f88(CarPhys *p);
void *f_099b98(void *p);
float f_0af380(const float *a, const float *b);
short f_0aff7c(void *t, const float *v);
short f_0af788(void *t, const float *v);
int f_0af5e8(void *t, const short *key);
}

/* The state of the car's MapMgr sub-object used by the two track lookups. */
extern char D_23c820[];
extern int D_2456a0;
extern "C" {
void f_0aa3f8(CarPhys *p);
void f_0ab0fc(CarPhys *p);
void f_0ab2a4(CarPhys *p);
}
extern int D_1ac174[];


/* @implements 0x0a6f6c us f_0a6f6c
   WHAT IT DOES: Sets up the car physics state (the first of two entry points). */
extern "C" void f_0a6f6c(CarPhys *p)
{
    f_0a6fb4(p);
}

/* @implements 0x0a6f88 us f_0a6f88
   WHAT IT DOES: Sets up the car physics state (the second entry point). */
extern "C" void f_0a6f88(CarPhys *p)
{
    f_0a6fb4(p);
}

/* @implements 0x0a6fa4 us f_0a6fa4
   WHAT IT DOES: An empty function. */
extern "C" void f_0a6fa4(void)
{
}

/* @implements 0x0a6fac us f_0a6fac
   WHAT IT DOES: An empty function. */
extern "C" void f_0a6fac(CarPhys *p)
{
}

/* A rotation (quaternion) held in the physics state at +64 and +576. */
struct Rot {
    float x, y, z, w;
    void Ident() { x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }
};

/* @draft 0x0a6fb4 us f_0a6fb4
   WHAT IT DOES: Clears the car physics state: zeroes the position, motion and mode fields, sets the two rotations to the identity, and for each of the four wheels zeroes its per wheel values and sets its scale pair to one.
   Remaining difference: store order only. sched1 ranks the w store (its 1.0 register dies there) ahead of x, and int stores pass the float ones; retail keeps x, w, y, z and interleaves 84/88/80 and the wheel loop's short stores differently. Retail's order x(0x40), 84, w, y, z, 88, 80 is not an alias-set effect (m88 is int by its other uses, line ~451); here w/y/z pass the int stores 44/48 because float vs int sets are disjoint, retail keeps them after 48. */
extern "C" void f_0a6fb4(CarPhys *p)
{
    int i;
    p->m0 = 0.0f;
    p->m4 = 0.0f;
    p->m8 = 0.0f;
    p->m12 = 0.0f;
    p->m16 = 0.0f;
    p->m20 = 0.0f;
    p->m24 = 0.0f;
    p->m28 = 0.0f;
    p->m32 = 0.0f;
    p->m36 = 0.0f;
    p->m40 = 0.0f;
    p->m44 = 0;
    p->m48 = 0;
    ((Rot *)&p->m64)->Ident();
    p->m80 = 0;
    p->m84 = 0;
    p->m88 = 0;
    p->m92 = 0;
    p->m96 = 0;
    p->m100 = 0;
    p->m104 = 0;
    p->m108 = 0;
    p->m112 = 0;
    p->m116 = 0;
    p->m117 = 0;
    p->m120 = 0.0f;
    p->m128 = 0.0f;
    p->m132 = 0.0f;
    p->m136 = 0.0f;
    p->m140 = 0.0f;
    p->m144 = 0.0f;
    p->m148 = 0.0f;
    p->m152 = 0.0f;
    p->m156 = 0;
    p->m160 = 0;
    p->m164 = 0;
    p->m168 = 0.0f;
    p->m172 = 0;
    p->m176 = 0;
    p->m180 = 0;
    p->m184 = 0;
    p->m188 = 0;
    for (i = 0; i < 4; i++) {
        PI(p, 192)[i] = 0;
        PI(p, 208)[i] = 0;
        PI(p, 224)[i] = 0;
        PI(p, 240)[i] = 0;
        PI(p, 288)[i] = 0;
        PI(p, 304)[i] = 0;
        PI(p, 320)[i] = 0;
        PI(p, 336)[i] = 0;
        PI(p, 352)[i] = 0;
        PI(p, 432)[i] = 0;
        PI(p, 416)[i] = 0;
        PI(p, 464)[i] = 0;
        PI(p, 448)[i] = 0;
        PI(p, 256)[i] = 0;
        PI(p, 272)[i] = 0;
        PH(p, 368)[i] = 0;
        PI(p, 376)[i] = 0;
        PH(p, 392)[i] = 0;
        PI(p, 400)[i] = 0;
        PI(p, 480)[i] = 0;
        PI(p, 496)[i] = 0;
        PI(p, 512)[i * 4] = 0;
        PF(p, 516)[i * 4] = 1.0f;
        PI(p, 520)[i * 4] = 0;
        PF(p, 524)[i * 4] = 1.0f;
    }
    ((Rot *)PF(p, 576))->Ident();
}

/* @implements 0x0a7e9c us f_0a7e9c
   WHAT IT DOES: An empty function. */
extern "C" void f_0a7e9c(void)
{
}

/* @implements 0x0a7ea4 us f_0a7ea4
   WHAT IT DOES: An empty function. */
extern "C" void f_0a7ea4(void)
{
}

/* @implements 0x0a79a0 us f_0a79a0
   WHAT IT DOES: Runs the step that f_0aa608 does for the car. */
extern "C" void f_0a79a0(CarPhys *p)
{
    f_0aa608(p);
}

/* @implements 0x0a7a48 us f_0a7a48
   WHAT IT DOES: Runs the first set-up step when the car's mode flag is clear. */
extern "C" void f_0a7a48(CarPhys *p)
{
    if (p->m108 == 0)
        f_0a9158(p);
}

/* @implements 0x0a7a78 us f_0a7a78
   WHAT IT DOES: Runs the second set-up step when the car's mode flag is clear. */
extern "C" void f_0a7a78(CarPhys *p)
{
    if (p->m108 == 0)
        f_0aa374(p);
}

/* @implements 0x0a7aa8 us f_0a7aa8
   WHAT IT DOES: Runs one of two update steps by the car's mode flag. */
extern "C" void f_0a7aa8(CarPhys *p)
{
    if (p->m108 == 0)
        f_0ab074(p);
    else
        f_0ab220(p);
}

/* @implements 0x0a7ae0 us f_0a7ae0
   WHAT IT DOES: Runs one of two update steps by the car's mode flag. */
extern "C" void f_0a7ae0(CarPhys *p)
{
    if (p->m108 == 0)
        f_0ac630(p);
    else
        f_0acd80(p);
}

/* @implements 0x0a7b18 us f_0a7b18
   WHAT IT DOES: Runs one of two steps by the car's mode flag, then copies the height to the stored height. */
extern "C" void f_0a7b18(CarPhys *p)
{
    if (p->m108 == 0)
        f_0ad82c(p);
    else
        f_0addbc(p);
    p->m120 = p->m16;
}

/* @implements 0x0a7e70 us f_0a7e70
   WHAT IT DOES: Runs two steps for the car in order. */
extern "C" void f_0a7e70(CarPhys *p)
{
    f_0aea0c(p);
    f_0aea84(p);
}

/* @implements 0x0a86b0 us f_0a86b0
   WHAT IT DOES: Runs one of two steps by the sign of the car's index field. */
extern "C" void f_0a86b0(CarPhys *p)
{
    if (p->m104 < 0)
        f_0aa608(p);
    else
        f_0aa374(p);
}

/* @implements 0x0a86e8 us f_0a86e8
   WHAT IT DOES: Runs one of two steps by the sign of the car's index field. */
extern "C" void f_0a86e8(CarPhys *p)
{
    if (p->m104 < 0)
        f_0ab220(p);
    else
        f_0ab074(p);
}

/* @implements 0x0a8720 us f_0a8720
   WHAT IT DOES: Runs one of two steps by the sign of the car's index field. */
extern "C" void f_0a8720(CarPhys *p)
{
    if (p->m104 < 0)
        f_0acd80(p);
    else
        f_0ac630(p);
}

/* @implements 0x0a8758 us f_0a8758
   WHAT IT DOES: Runs one of two steps by the sign of the car's index field; the non-negative case also copies the height. */
extern "C" void f_0a8758(CarPhys *p)
{
    if (p->m104 < 0) {
        f_0addbc(p);
    } else {
        f_0ad82c(p);
        p->m120 = p->m16;
    }
}

/* @implements 0x0ae9f8 us f_0ae9f8
   WHAT IT DOES: Copies the car's two height values to their stored copies. */
extern "C" void f_0ae9f8(CarPhys *p)
{
    p->m128 = p->m16;
    p->m132 = p->m12;
}

/* @implements 0x0a9134 us f_0a9134
   WHAT IT DOES: Looks up a word of the table for index i, zero for index 0. */
extern "C" int f_0a9134(int unused, int i)
{
    return i ? D_1ac174[i - 44] : 0;
}

/* @implements 0x0a79bc us f_0a79bc
   WHAT IT DOES: Copies the car's current position and height into its stored copies when the car is within the window of its last frame, and sets its mode to 2 otherwise. */
extern "C" void f_0a79bc(CarPhys *p)
{
    float d = p->m40 + -4.0f;
    if (d <= p->m20 && p->m20 <= p->m36 + 4.0f) {
        p->m108 = 0;
        p->m592 = p->m0;
        p->m596 = p->m4;
        p->m600 = p->m12;
        p->m608 = p->m8;
        p->m604 = p->m132;
        p->m612 = p->m128;
        p->m616 = p->m116;
    } else {
        p->m108 = 2;
    }
}

/* @implements 0x0a853c us f_0a853c
   WHAT IT DOES: Looks up the car's position on the track: stores the lookup's short result and the table entry for the car's key.*/
extern "C" void f_0a853c(CarPhys *p)
{
    float v[4];
    v[0] = p->m0;
    v[1] = p->m12;
    v[2] = p->m4;
    v[3] = 1.0f;
    char *b = (char *)&D_23c820;
    char *s = b + 12256;
    p->m92 = f_0aff7c(s, v);
    p->m104 = f_0af5e8(s, &p->m92);
}

/* @implements 0x0a85b4 us f_0a85b4
   WHAT IT DOES: The second track lookup: the same as f_0a853c with the second lookup routine.*/
extern "C" void f_0a85b4(CarPhys *p)
{
    float v[4];
    v[0] = p->m0;
    v[1] = p->m12;
    v[2] = p->m4;
    v[3] = 1.0f;
    char *b = (char *)&D_23c820;
    char *s = b + 12256;
    p->m92 = f_0af788(s, v);
    p->m104 = f_0af5e8(s, &p->m92);
}

/* @implements 0x0a862c us f_0a862c
   WHAT IT DOES: Copies the car's position and height to their stored copies, updates the car's mode flag from its index and runs the matching step.
   f_099b98 returns its argument; with that prototype v0 stays live across the call as in retail. */
extern "C" void f_0a862c(CarPhys *p)
{
    p->m24 = p->m16;
    p->m28 = p->m20;
    int m = p->m108;
    f_0ae9f8(p);
    f_099b98((char *)p + 8);
    if (p->m104 < 0) {
        p->m108 = 2;
        return;
    }
    p->m108 = 0;
    if (m < 2)
        f_0a9158(p);
    else
        f_0a9248(p);
}

/* @implements 0x0a87a0 us f_0a87a0
   WHAT IT DOES: Checks the car against the wall window while its mode flag is clear, clearing its index field when it is in range, then runs the two drive steps. */
extern "C" void f_0a87a0(CarPhys *p)
{
    if (p->m108 == 0) {
        if (!(p->m20 < p->m40 + -3.0f) && !(p->m36 + 3.0f < p->m20))
            p->m100 = -1;
    }
    f_0aea0c(p);
    f_0aea84(p);
}

/* @implements 0x0aea0c us f_0aea0c
   WHAT IT DOES: Counts the car's offset from its last reading up or down while it moves past +-500, and clears the direction flag otherwise. */
extern "C" void f_0aea0c(CarPhys *p)
{
    float d = p->m16 - p->m128;
    if (500.0f < d) {
        int c = p->m84;
        int n = c - 1;
        if (c)
            p->m88 = -1;
        p->m84 = n;
    } else if (d < -500.0f) {
        int c = p->m84;
        int n = c + 1;
        if (c != -1)
            p->m88 = 1;
        p->m84 = n;
    } else {
        p->m88 = 0;
    }
}

/* @implements 0x0aea84 us f_0aea84
   WHAT IT DOES: Updates the car's difference value from its height and its last value, through the angle wrap routine. */
extern "C" void f_0aea84(CarPhys *p)
{
    float t = p->m16;
    p->m28 = p->m20 - p->m28;
    p->m24 = f_0af380(&t, &p->m24);
}

/* @implements 0x0a742c us f_0a742c
   WHAT IT DOES: Builds a four-float vector from three float arguments (its last word a plain 1.0) and calls the shared lookup f_0a7118 with it and the two remaining floats. */
extern "C" void f_0a742c(void *a0, int a1, int a2, float x, float y, float z, float w, float u)
{
    float v[4];
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    f_0a7118_2(a0, v, a1, a2, -1, w, u);
}

/* @implements 0x0a747c us f_0a747c
   WHAT IT DOES: Builds a four-float vector from two floats, with a zero second word and a plain 1.0 last word, and calls the shared lookup f_0a7118 with it. */
extern "C" void f_0a747c(void *a0, int a1, int a2, float x, float y, float z, float w)
{
    float v[4];
    v[0] = x;
    v[2] = y;
    v[3] = 1.0f;
    v[1] = 0.0f;
    f_0a7118_2(a0, v, a1, a2, -1, z, w);
}

/* @implements 0x0aa374 us f_0aa374
   WHAT IT DOES: Runs four passes over the car's per-wheel records: each pass copies a few values from the record into the car, runs the step f_0aa3f8 and stores its results back into the record. */
extern "C" void f_0aa374(CarPhys *p)
{
    for (int i = 0; i < 4; i++) {
        float a = ((float *)((char *)p + 192))[i];
        float b = ((float *)((char *)p + 208))[i];
        int c = ((int *)((char *)p + 256))[i];
        int d = ((int *)((char *)p + 272))[i];
        p->m148 = a;
        p->m152 = b;
        p->m156 = c;
        p->m160 = d;
        f_0aa3f8(p);
        float e = p->m140;
        float f = p->m136;
        float g = p->m168;
        ((float *)((char *)p + 304))[i] = e;
        ((float *)((char *)p + 288))[i] = f;
        ((float *)((char *)p + 320))[i] = g;
    }
}

/* @implements 0x0ab074 us f_0ab074
   WHAT IT DOES: Runs four passes over the car's per-wheel records: each pass numbers the record in a global, copies its values into the car, runs f_0ab0fc and stores the result back. */
extern "C" void f_0ab074(CarPhys *p)
{
    for (int i = 0; i < 4; i++) {
        int a = ((int *)((char *)p + 256))[i];
        int b = ((int *)((char *)p + 272))[i];
        float c = ((float *)((char *)p + 304))[i];
        float d = ((float *)((char *)p + 320))[i];
        D_2456a0 = i;
        p->m156 = a;
        p->m140 = c;
        p->m160 = b;
        p->m168 = d;
        f_0ab0fc(p);
        ((float *)((char *)p + 336))[i] = p->m144;
    }
}

/* @implements 0x0ab220 us f_0ab220
   WHAT IT DOES: Runs four passes over the car's per-wheel records: each pass copies two values into the car, runs f_0ab2a4 and stores its results back, the short result going into a packed list. */
extern "C" void f_0ab220(CarPhys *p)
{
    for (int i = 0; i < 4; i++) {
        float a = ((float *)((char *)p + 192))[i];
        float b = ((float *)((char *)p + 208))[i];
        p->m148 = a;
        p->m152 = b;
        f_0ab2a4(p);
        ((float *)((char *)p + 336))[i] = p->m144;
        ((unsigned short *)((char *)p + 368))[i] = p->m184;
        ((int *)((char *)p + 376))[i] = p->m188;
    }
}

/* @implements 0x0ab43c us f_0ab43c
   WHAT IT DOES: Copies the record with index i into the car, runs f_0ab2a4 and stores the car's results back into that record. */
extern "C" void f_0ab43c(CarPhys *p, int i)
{
    float a = ((float *)((char *)p + 192))[i];
    float b = ((float *)((char *)p + 208))[i];
    p->m148 = a;
    p->m152 = b;
    f_0ab2a4(p);
    ((float *)((char *)p + 336))[i] = p->m144;
    ((unsigned short *)((char *)p + 368))[i] = p->m184;
    ((int *)((char *)p + 376))[i] = p->m188;
}


extern float D_2456b0;

/* @draft 0x0a737c us f_0a737c
   WHAT IT DOES: Sets up the car physics state from four float arguments: the position and height, with the mode and index fields reset and the stored copies cleared.
   Remaining difference: retail holds p+64 in v1 (addiu v1,s0,64) and stores 76, 68, 72 through it (12/4/8(v1)) while 64 itself goes through s0: the 68..76 writes come from an inline helper on the +64 sub-object (handbook row 2), whose x store is not v1-based; which helper is not yet known. */
extern "C" void f_0a737c(CarPhys *p, float x, float y, float z, float w)
{
    f_0a6fb4(p);
    p->m84 = -1;
    p->m0 = x;
    p->m12 = y;
    p->m4 = z;
    p->m64 = p->m8 = 0.0f;
    p->m116 = 1;
    p->m68 = p->m76 = 1.0f;
    p->m72 = 0.0f;
    p->m117 = 0;
    p->m120 = p->m128 = p->m16 = w;
    p->m28 = p->m20 = p->m24 = 0.0f;
}

/* @implements 0x0a78f0 us f_0a78f0
   WHAT IT DOES: Copies the height and the second height into their stored copies, runs the height copy, then looks up the car's track position with the lookup chosen by the car's flag, and stores the short result and the table entry for the car's key. */
extern "C" void f_0a78f0(CarPhys *p)
{
    p->m24 = p->m16;
    p->m28 = p->m20;
    f_0ae9f8(p);
    f_099b98((char *)p + 8);
    float v[4];
    v[0] = p->m0;
    v[1] = p->m12;
    v[2] = p->m4;
    v[3] = 1.0f;
    char *b = (char *)&D_23c820;
    char *s = b + 12256;
    if (p->m116 != 0)
        p->m92 = f_0aff7c(s, v);
    else
        p->m92 = f_0af788(s, v);
    p->m104 = f_0af5e8(s, &p->m92);
}

/* @implements 0x0a881c us f_0a881c
   WHAT IT DOES: Copies the height and the first height into their stored copies, resets the car's mode and index fields and the four per-wheel arrays, then runs the two steps f_0aea0c and f_0aea84. */
extern "C" void f_0a881c(CarPhys *p)
{
    p->m24 = p->m16;
    p->m28 = p->m20;
    f_099b98((char *)p + 8);
    p->m108 = 0;
    p->m120 = p->m16;
    p->m100 = -1;
    float h = p->m12;
    for (int i = 0; i < 4; i++) {
        ((int *)((char *)p + 400))[i] = 0;
        ((short *)((char *)p + 392))[i] = -1;
        ((float *)((char *)p + 336))[i] = h;
        ((int *)((char *)p + 376))[i] = 0;
    }
    f_0aea0c(p);
    f_0aea84(p);
}

/* @implements 0x0a8f0c us f_0a8f0c
   WHAT IT DOES: Compares the car's height and its stored height with a given value, each wrapped by the track length, and returns -1 when the difference is above 500, 1 when it is below -500, and 0 otherwise.*/
extern "C" int f_0a8f0c(CarPhys *p, float x)
{
    float a;
    float b;
    if (p->m16 < x)
        a = (p->m16 + D_2456b0) - x;
    else
        a = p->m16 - x;
    if (p->m128 < x)
        b = (p->m128 + D_2456b0) - x;
    else
        b = p->m128 - x;
    float d = a - b;
    if (500.0f < d)
        return -1;
    if (d < -500.0f)
        return 1;
    return 0;
}

extern "C" {
int f_0d5f78(void *d, int v);
unsigned short f_0af9c4(void *p, const float *v, const float *h);
unsigned short f_0b0234(void *p, const float *v, const float *h);
void f_0aa748(CarPhys *p);
void f_0ab370(CarPhys *p);
}

/* @draft 0x0a88ac us f_0a88ac
   WHAT IT DOES: Updates the car's stored position and height, runs the track step f_0aa748, reads the track lookups for the car's position and copies the result into the car, then runs the wheel step when the lookup result is the sentinel and the two drive steps.
   Remaining difference: first run; the ordering of the stored copies and the lookup pointer arithmetic are not yet matched. */
extern "C" void f_0a88ac(CarPhys *p)
{
    float saved12 = p->m12;
    int savedIdx = p->m104;
    p->m24 = p->m16;
    p->m28 = p->m20;
    f_0ae9f8(p);
    p->m148 = p->m0;
    p->m152 = p->m4;
    if ((short)p->m100 < 0)
        p->m164 = -1;
    else
        p->m164 = p->m100;
    f_0aa748(p);
    p->m20 = p->m140;
    p->m100 = p->m164;
    p->m16 = p->m136;
    char *d = (char *)&D_23c820;
    p->m112 = f_0d5f78(d + 12144, (int)p->m136);
    char *s2 = d + 12256;
    char *s5 = d + 12240;
    float v[4];
    v[0] = p->m0;
    v[1] = p->m12;
    v[2] = p->m4;
    v[3] = 1.0f;
    if (p->m116 == 0)
        p->m92 = f_0af9c4(s2, v, &p->m12);
    else
        p->m92 = f_0b0234(s2, v, &p->m12);
    p->m104 = f_0af5e8(s2, &p->m92);
    if ((unsigned short)p->m92 == 0xffff) {
        f_0ab370(p);
        p->m12 = p->m144;
        p->m92 = p->m184;
        p->m104 = f_0af5e8(s5 + 112, &p->m92);
    }
    if ((unsigned short)p->m92 == 0xffff) {
        p->m12 = saved12;
        p->m104 = savedIdx;
    }
    f_0aea0c(p);
    f_0aea84(p);
}

/* The ground lookup's query point (16-byte aligned), one 6-byte result record, and the
   polygon set inside the race state at D_23c820 + 12352 whose record table is at +80. */
struct GroundPt {
    float x, y, z, w;
} __attribute__((aligned(16)));
struct GroundRec {
    signed char n0, n1;
    unsigned short idx, base;
};
struct GroundSet {
    char m0[80];
    GroundRec *recs;
};
/* A course area record (24 bytes): its base height at +8 and its row in the height table at +18. */
struct CourseArea {
    float m0, m4, y;
    int m12;
    short m16;
    unsigned short row;
    int m20;
};
/* The course areas at D_23c820 + 12240: the area list and a table of 64 heights per row. */
struct CourseAreas {
    CourseArea *list;
    short *tab;
    char m8[104];
};
struct RaceState {
    char m0[12240];
    CourseAreas areas;
    GroundSet polys;
    CourseAreas *Areas() { return &areas; }
    GroundSet *Polys() { return &polys; }
};
extern RaceState D_23c820_state __asm__("D_23c820");

extern "C" {
unsigned short f_0b0500(GroundSet *p, const GroundPt *v, float *h, const GroundRec **rec);
unsigned short f_0afc38(GroundSet *p, const GroundPt *v, float *h, const GroundRec **rec);
float f_0af478(const float *a);
}

/* @implements 0x0ab2a4 us f_0ab2a4
   WHAT IT DOES: Looks up the ground polygon under the wheel probe point with the lookup chosen by the car's flag and stores the polygon id; when nothing is found it zeroes the record number and puts the ground height back to the car's height. The record number (the result record's index in the set's table) is then stored unconditionally, so the zero never survives: retail behaviour, kept as is. */
extern "C" void f_0ab2a4(CarPhys *p)
{
    GroundSet *s = D_23c820_state.Polys();
    GroundPt v;
    const GroundRec *r;
    v.x = p->m148;
    v.y = p->m12;
    v.z = p->m152;
    v.w = 1.0f;
    if (p->m116)
        p->m184 = f_0b0500(s, &v, &p->m144, &r);
    else
        p->m184 = f_0afc38(s, &v, &p->m144, &r);
    if ((unsigned short)p->m184 == 0xffff) {
        p->m188 = 0;
        p->m144 = p->m12;
    }
    p->m188 = r - s->recs;
}

/* @implements 0x0ab370 us f_0ab370
   WHAT IT DOES: The same ground lookup as f_0ab2a4 (its own copy, with its own 1.0 literal). */
extern "C" void f_0ab370(CarPhys *p)
{
    GroundSet *s = D_23c820_state.Polys();
    GroundPt v;
    const GroundRec *r;
    v.x = p->m148;
    v.y = p->m12;
    v.z = p->m152;
    v.w = 1.0f;
    if (p->m116)
        p->m184 = f_0b0500(s, &v, &p->m144, &r);
    else
        p->m184 = f_0afc38(s, &v, &p->m144, &r);
    if ((unsigned short)p->m184 == 0xffff) {
        p->m188 = 0;
        p->m144 = p->m12;
    }
    p->m188 = r - s->recs;
}

/* An angle passed by value in an integer register. */
union Angle {
    float a;
};

struct Vec4 {
    float x, y, z, w;
};

extern "C" {
void f_09b394(Angle a, float *x, float *y);
void f_0a98d8(CarPhys *p);
void f_0a9330(CarPhys *p);
}

/* @draft 0x0a9158 us f_0a9158
   WHAT IT DOES: Stores the truncated speed, then for each of the four wheels turns the wheel's offset by the car's heading, adds the car's position, stores the result as the wheel's position and as the probe point, runs the ground probe f_0a98d8 and keeps its two results for the wheel.
   Remaining difference: retail schedules the v.z load after the first sum (both reloads of v use $f0); sched1 here hoists it above. Not -fno-schedule-insns (breaks 10 others), local order, in-place sums or reading the position first. */
extern "C" void f_0a9158(CarPhys *p)
{
    p->m180 = (int)p->m128;
    Vec4 v;
    Angle a;
    Angle *pa = &a;
    for (int i = 0; i < 4; i++) {
        v.x = ((float *)((char *)p + 224))[i];
        v.y = 0.0f;
        v.z = ((float *)((char *)p + 240))[i];
        v.w = 1.0f;
        a.a = p->m8;
        f_099b98(pa);
        f_09b394(a, &v.z, &v.x);
        float x = p->m0 + v.x;
        float z = p->m4 + v.z;
        ((float *)((char *)p + 192))[i] = x;
        ((float *)((char *)p + 208))[i] = z;
        p->m148 = x;
        p->m152 = z;
        f_0a98d8(p);
        int c = p->m156;
        int d = p->m160;
        ((int *)((char *)p + 256))[i] = c;
        ((int *)((char *)p + 272))[i] = d;
    }
}

/* @draft 0x0a9248 us f_0a9248
   WHAT IT DOES: Runs the wheel update f_0a9330, then for each of the four wheels turns the wheel's offset by the car's heading, adds the car's position, stores the result as the wheel's position and as the probe point, runs the ground probe f_0a98d8 and keeps its two results for the wheel.
   Remaining difference: retail schedules the v.z load after the first sum (both reloads of v use $f0); sched1 here hoists it above. Not -fno-schedule-insns (breaks 10 others), local order, in-place sums or reading the position first. */
extern "C" void f_0a9248(CarPhys *p)
{
    f_0a9330(p);
    Vec4 v;
    Angle a;
    Angle *pa = &a;
    for (int i = 0; i < 4; i++) {
        v.x = ((float *)((char *)p + 224))[i];
        v.y = 0.0f;
        v.z = ((float *)((char *)p + 240))[i];
        v.w = 1.0f;
        a.a = p->m8;
        f_099b98(pa);
        f_09b394(a, &v.z, &v.x);
        float x = p->m0 + v.x;
        float z = p->m4 + v.z;
        ((float *)((char *)p + 192))[i] = x;
        ((float *)((char *)p + 208))[i] = z;
        p->m148 = x;
        p->m152 = z;
        f_0a98d8(p);
        int c = p->m156;
        int d = p->m160;
        ((int *)((char *)p + 256))[i] = c;
        ((int *)((char *)p + 272))[i] = d;
    }
}

/* @draft 0x0af064 us f_0af064
   WHAT IT DOES: Blends the four wheel records of the car p toward those of q by the factor t: a negative surface index is taken from q, the wheel angle moves along the shortest turn (f_0af380) and is wrapped (f_0af478), the surface id is copied and the wheel height is interpolated linearly.
   Remaining difference: retail loads p's height before q's for the final blend; here q's comes first. Verbose sched1: both loads tie on priority (16) and dependents (4); q's wins on INSN_REG_WEIGHT because it is the last use of q+4i (REG_DEAD), while p+4i lives on for the stores. Retail's order needs p's load to kill its base, or q+4i to live past it. */
extern "C" void f_0af064(CarPhys *p, CarPhys *q, float t)
{
    for (int i = 0; i < 4; i++) {
        if (((int *)((char *)p + 496))[i] < 0)
            ((int *)((char *)p + 496))[i] = ((int *)((char *)q + 496))[i];
        float a = ((float *)((char *)q + 288))[i];
        float b = f_0af380(&a, &((float *)((char *)p + 288))[i]) * t + ((float *)((char *)p + 288))[i];
        float r = f_0af478(&b);
        float c = ((float *)((char *)p + 352))[i];
        float e = (((float *)((char *)q + 352))[i] - c) * t + c;
        ((unsigned short *)((char *)p + 368))[i] = ((unsigned short *)((char *)q + 368))[i];
        ((float *)((char *)p + 288))[i] = r;
        ((float *)((char *)p + 352))[i] = e;
    }
}

/* @draft 0x0ab0fc us f_0ab0fc
   WHAT IT DOES: Sets the car's ground height from the course areas: the position along the area (offset by 32, clamped to 1..62) picks two neighbouring entries of each of the two areas' height rows, each pair is interpolated, added to its area's base height, and the two results are blended by the car's blend factor.
   Remaining difference (29 of 73 words): register choice only: retail keeps the first area's base height in $f11 and the second's in $f10 (here the reverse), and forms the row addresses in v0/v1 the other way round; the instruction sequence is otherwise retail's. 2026-11-16: y0/y1 are multi-block, so global-alloc's priority (refs/live length) decides f10: retail's y0 lives longer (h1 = y1+b issued before h0), here sched puts the a-chain and h0 first, so y0 dies first and wins f10; the order to fix is sched1's, not the allocator's. */
extern "C" void f_0ab0fc(CarPhys *p)
{
    float x = p->m140 + 32.0f;
    CourseAreas *ar = D_23c820_state.Areas();
    CourseArea *e0 = &ar->list[p->m156];
    CourseArea *e1 = &ar->list[p->m160];
    float y0 = e0->y;
    float y1 = e1->y;
    if (x < 1.0f)
        x = 1.0f;
    else if (62.0f < x)
        x = 62.0f;
    int n = (int)x;
    short *t0 = &ar->tab[e0->row * 64 + n];
    short *t1 = &ar->tab[e1->row * 64 + n];
    float a0 = t0[0], a1 = t0[1];
    float b0 = t1[0], b1 = t1[1];
    float da = a1 - a0;
    float db = b1 - b0;
    float f = x - n;
    float b = b0 + db * f;
    float a = a0 + da * f;
    float h1 = y1 + b;
    float h0 = y0 + a;
    p->m144 = (h1 - h0) * p->m168 + h0;
}

extern "C" void f_0aa748(CarPhys *p);

/* @draft 0x0aa608 us f_0aa608
   WHAT IT DOES: Stores the truncated height, then for each of the four wheels turns the wheel's offset by the car's heading, adds the car's position and stores it as the wheel's position and the probe point, takes the wheel's surface id (or -1 when the car has no index), runs the surface step f_0aa748 and keeps its results for the wheel; the last wheel's surface id becomes the car's index.
   Remaining difference: retail schedules the v.z load after the first sum (both reloads of v in $f0), as in f_0a9158. */
extern "C" void f_0aa608(CarPhys *p)
{
    p->m180 = (int)p->m16;
    Vec4 v;
    Angle a;
    Angle *pa = &a;
    float *pz = &v.z;
    unsigned short s;
    for (int i = 0; i < 4; i++) {
        v.x = ((float *)((char *)p + 224))[i];
        v.y = 0.0f;
        v.z = ((float *)((char *)p + 240))[i];
        v.w = 1.0f;
        a.a = p->m8;
        f_099b98(pa);
        f_09b394(a, pz, &v.x);
        float x = p->m0 + v.x;
        float z = p->m4 + v.z;
        ((float *)((char *)p + 192))[i] = x;
        ((float *)((char *)p + 208))[i] = z;
        p->m148 = x;
        p->m152 = z;
        if (p->m100 < 0)
            p->m164 = -1;
        else
            p->m164 = ((short *)((char *)p + 392))[i];
        f_0aa748(p);
        float e = p->m140;
        float f = p->m136;
        float g = p->m168;
        s = p->m164;
        ((float *)((char *)p + 304))[i] = e;
        ((float *)((char *)p + 288))[i] = f;
        ((float *)((char *)p + 320))[i] = g;
        ((unsigned short *)((char *)p + 392))[i] = s;
    }
    p->m100 = s;
}

/* @draft 0x0aaf68 us f_0aaf68
   WHAT IT DOES: The one-wheel form of f_0aa608 for wheel i: stores the truncated height, places the wheel and its probe point, takes its surface id (or -1), runs f_0aa748 and keeps the results for that wheel.
   Remaining difference: scheduling only: retail loads the height and heading first and stores the heading to the stack after the vector; the four result loads come out in another order. 720 setup orders and 72 result orders tried (the best is kept). Retail reads m16 through a0 and m8 through s1 (the saved copy), and stores v.y last (jal delay slot); the order permutations did not reach that, so the cause is not statement order. */
extern "C" void f_0aaf68(CarPhys *p, int i)
{
    Vec4 v;
    Angle a;
    a.a = p->m8;
    v.z = ((float *)((char *)p + 240))[i];
    v.y = 0.0f;
    v.x = ((float *)((char *)p + 224))[i];
    v.w = 1.0f;
    p->m180 = (int)p->m16;
    f_099b98(&a);
    f_09b394(a, &v.z, &v.x);
    float vx = v.x;
    float vz = v.z;
    float x = p->m0 + vx;
    float z = p->m4 + vz;
    ((float *)((char *)p + 192))[i] = x;
    ((float *)((char *)p + 208))[i] = z;
    p->m148 = x;
    p->m152 = z;
    if (p->m100 < 0)
        p->m164 = -1;
    else
        p->m164 = ((short *)((char *)p + 392))[i];
    f_0aa748(p);
    float g = p->m168;
    float f = p->m136;
    float e = p->m140;
    unsigned short h = p->m164;
    ((float *)((char *)p + 320))[i] = g;
    ((unsigned short *)((char *)p + 392))[i] = h;
    ((float *)((char *)p + 304))[i] = e;
    ((float *)((char *)p + 288))[i] = f;
}

static inline float Abs(float x) { return x < 0.0f ? -x : x; }

/* @implements 0x0a8bf4 us f_0a8bf4
   WHAT IT DOES: Tests whether the car crossed the angle b between its previous and current heading: -1 when either heading is more than 6 away, when they are equal or when both lie on the same side; -2 when the crossing runs backwards; otherwise the crossing point as tenths of the step (0 for a step under 0.001). */
extern "C" int f_0a8bf4(CarPhys *p, const float *b)
{
    float t0 = p->m128;
    float d0 = f_0af380(&t0, b);
    if (Abs(d0) > 6.0f)
        return -1;
    float t1 = p->m16;
    float *pt = &t1;
    float d1 = f_0af380(pt, b);
    if (Abs(d1) > 6.0f)
        return -1;
    if (d0 == d1)
        return -1;
    if (d0 < 0.0f && d1 < 0.0f)
        return -1;
    if (0.0f < d0 && 0.0f < d1)
        return -1;
    float diff = d1 - d0;
    if (diff < 0.0f)
        return -2;
    if (diff < 0.001f)
        return 0;
    return (int)(-d0 / diff * 10.0f);
}

/* @implements 0x0a8d5c us f_0a8d5c
   WHAT IT DOES: The general form of f_0a8bf4 for a ring of n steps: -n when the car did not cross the angle b (a heading more than 7 away, equal headings or both on one side), -n-1 when it crossed backwards, otherwise the crossing step k (c/2 for a tiny step, else the crossing point scaled by c) taken back by (k + e) mod n. */
extern "C" int f_0a8d5c(CarPhys *p, const float *b, int c, int n, int e)
{
    float t0 = p->m128;
    float d0 = f_0af380(&t0, b);
    if (Abs(d0) > 7.0f)
        return -n;
    float t1 = p->m16;
    float *pt = &t1;
    float d1 = f_0af380(pt, b);
    if (Abs(d1) > 7.0f)
        return -n;
    if (d0 == d1)
        return -n;
    if (d0 < 0.0f && d1 < 0.0f)
        return -n;
    if (0.0f < d0 && 0.0f < d1)
        return -n;
    float diff = d1 - d0;
    if (diff < 0.0f)
        return -n - 1;
    int k;
    if (diff < 0.001f)
        k = c / 2;
    else
        k = (int)(-d0 / diff * c);
    return k - (k + e) % n;
}

/* One course point (24 bytes) of the point list D_23f7f0, D_2456b8 points in a ring. */
struct CoursePt {
    float x, y, z;
    int m12, m16, m20;
};
struct CoursePos {
    float a, b, c;
};
extern CoursePt *D_23f7f0_pts __asm__("D_23f7f0");
extern int D_2456b8;

/* The course position at s: the points either side of s (wrapping to the first), interpolated. */
static inline CoursePos CourseAt(CoursePt *list, float s)
{
    int n = (int)s;
    float f = s - n;
    CoursePt *a = &list[n];
    CoursePt *b = a + 1;
    if (n + 1 >= D_2456b8)
        b = list;
    CoursePos r;
    r.a = (b->x - a->x) * f + a->x;
    r.b = (b->z - a->z) * f + a->z;
    r.c = (b->y - a->y) * f + a->y;
    return r;
}

/* @draft 0x0a8fa8 us f_0a8fa8
   WHAT IT DOES: Writes into out the course direction at the car's course position: the course point d ahead (wrapped by f_0af478) minus the point at the position, with a last word of 1.0; returns out.
   Remaining difference: retail copies the wrapped position to a new register and converts the second point index back through an integer register (mtc1); register choices follow from that. */
extern "C" float *f_0a8fa8(float *out, CarPhys *c, const float *d)
{
    CoursePt *list = D_23f7f0_pts;
    float s = c->m16;
    CoursePos v = CourseAt(list, s);
    float s2 = s + *d;
    float u = f_0af478(&s2);
    CoursePos w = CourseAt(list, u);
    out[1] = w.b - v.b;
    out[0] = w.a - v.a;
    out[3] = 1.0f;
    out[2] = w.c - v.c;
    return out;
}

/* @draft 0x0af140 us f_0af140
   WHAT IT DOES: Blends wheel i of the cars p and q toward each other: the weight comes from where p's wheel height lies between its two limits (a quarter of the distance to the nearer one, clamped to 0..1); the surface index is shared (a negative one taken from the other car), and the angle (shortest turn, wrapped), the height and the second height are blended and written to both cars; q's surface id is copied to p.
   Remaining difference: retail keeps i*4 in s0 from the prologue and stores q's blended heights in the other order. The -0.0 additions are retail's literals. Cause of the s0 choice (RTL): global-alloc's set_preference ties a sum's dest to its FIRST operand; retail forms p's element as i4+p (s0) and q's as q+i4 (s1), here the call argument &PF(p,288)[i] expands as p+i4 (non-address context) and the qa load as i4+q (address context), the first use in the block fixing each pseudo's form. Needs q's element first taken as a pointer and p's first in an address context. */
extern "C" void f_0af140(CarPhys *p, CarPhys *q, int i)
{
    float a = ((float *)((char *)p + 416))[i];
    float b = ((float *)((char *)p + 432))[i];
    float h = ((float *)((char *)p + 304))[i];
    float t;
    if (h < (a + b) * 0.5f)
        t = a + -0.0f - h;
    else
        t = -0.0f - b + h;
    t *= 0.25f;
    if (t < 0.0f)
        t = 0.0f;
    else if (1.0f < t)
        t = 1.0f;
    if (((int *)((char *)p + 496))[i] < 0)
        ((int *)((char *)p + 496))[i] = ((int *)((char *)q + 496))[i];
    else
        ((int *)((char *)q + 496))[i] = ((int *)((char *)p + 496))[i];
    float qa = ((float *)((char *)q + 288))[i];
    float w = f_0af380(&qa, &((float *)((char *)p + 288))[i]) * t + ((float *)((char *)p + 288))[i];
    float r = f_0af478(&w);
    float c = ((float *)((char *)p + 352))[i];
    float d = ((float *)((char *)p + 336))[i];
    float e = (((float *)((char *)q + 352))[i] - c) * t + c;
    float g = (((float *)((char *)q + 336))[i] - d) * t + d;
    ((float *)((char *)p + 288))[i] = r;
    ((float *)((char *)q + 288))[i] = r;
    ((float *)((char *)p + 352))[i] = e;
    ((float *)((char *)p + 336))[i] = g;
    ((float *)((char *)q + 352))[i] = e;
    ((float *)((char *)q + 336))[i] = g;
    ((unsigned short *)((char *)p + 368))[i] = ((unsigned short *)((char *)q + 368))[i];
}

extern "C" float f_0ac400(CarPhys *p, const float *y, int *s);

/* @implements 0x0ab4ac us f_0ab4ac
   WHAT IT DOES: The force curve of one wheel state. The state *s (its sign gives the direction, its size one of 65 curves) and the slip *x pick a piecewise curve, most shaped by the load *y; a positive slip and a non-positive one use separate tables. A result of zero or less resets the state. */
extern "C" float f_0ab4ac(CarPhys *p, const float *x, const float *y, int *s)
{
    int neg;
    int n;
    if (*s < 0) {
        neg = 1;
        n = -*s;
    } else {
        neg = 0;
        n = *s;
    }
    float r = 0.0f;
    if (r < *x) {
        switch (n) {
        case 1:
            if (*x < 1.0f)
                r = 80.0f;
            else
                r = 0.0f;
            break;
        case 2:
            if (*x < 1.0f) {
                if (*y < 0.25f)
                    r = *x * ((0.25f - *y) * 120.0f + 10.0f) + 15.0f;
                else
                    r = *x * 40.0f * *y + 15.0f;
            } else if (neg) {
                if (*x < 1.55f) {
                    if (*y < 0.25f)
                        r = (1.55f - *x) / 0.55f * ((0.25f - *y) * 120.0f + 25.0f);
                    else
                        r = (1.55f - *x) / 0.55f * (*y * 40.0f + 15.0f);
                }
            } else if (*x < 1.1f) {
                if (*y < 0.25f)
                    r = (1.1f - *x) * ((0.25f - *y) * 1200.0f + 250.0f);
                else
                    r = (1.1f - *x) * (*y * 400.0f + 150.0f);
            }
            break;
        case 9:
            if (*x < 0.6f)
                r = *x * 50.0f + 10.0f;
            else if (neg) {
                if (*x < 1.2f)
                    r = (1.2f - *x) * 100.0f;
            } else if (*x < 0.8f)
                r = (0.8f - *x) * 250.0f + 10.0f;
            else if (*x < 0.9f)
                r = (0.9f - *x) * 100.0f;
            break;
        case 21:
            if (*x < 1.0f) {
                if (*y < 0.75f)
                    r = *x * 40.0f * (1.0f - *y) + 15.0f;
                else
                    r = *x * ((*y - 0.75f) * 120.0f + 10.0f) + 15.0f;
            } else if (neg) {
                if (*x < 1.55f) {
                    if (*y < 0.75f)
                        r = (1.55f - *x) / 0.55f * ((1.0f - *y) * 40.0f + 15.0f);
                    else
                        r = (1.55f - *x) / 0.55f * ((*y - 0.75f) * 120.0f + 25.0f);
                }
            } else if (*x < 1.1f) {
                if (*y < 0.75f)
                    r = (1.1f - *x) * 550.0f * (1.0f - *y);
                else
                    r = (1.1f - *x) * ((*y - 0.75f) * 1200.0f + 250.0f);
            }
            break;
        case 3: case 4: case 5: case 6: case 7: case 8: case 10: case 11: case 12: case 13:
        case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 22: case 23: case 24: {
            float lim = f_0ac400(p, y, s);
            if (*x < lim)
                r = 10.0f;
            else if (*x < lim + 0.1f)
                r = (lim + 0.1f - *x) * 100.0f;
            break;
        }
        case 25:
            if (*x < 0.3f)
                r = *x * 166.66666f + 10.0f;
            else if (*x < 0.75f)
                r = 60.0f;
            else if (*x < 1.05f)
                r = (1.05f - *x) * 166.66666f + 10.0f;
            else if (*x < 1.15f)
                r = (1.15f - *x) * 100.0f;
            break;
        case 26:
            if (*x < 0.44f)
                r = *x * 136.36363f + 10.0f;
            else if (neg) {
                if (*x < 1.14f)
                    r = (1.14f - *x) * 100.0f;
            } else if (*x < 0.44f)
                r = (0.54f - *x) * 700.0f;
            break;
        case 44:
            if (*x < 0.390625f)
                r = *x * 60.0f / 0.390625f + 10.0f;
            else if (*x < 0.9765625f)
                r = (0.9765625f - *x) * 60.0f / 0.5859375f + 10.0f;
            else if (*x < 1.0765625f)
                r = (1.0765625f - *x) * 100.0f;
            break;
        case 45: case 46: case 47: case 48:
            if (*x < 0.9765625f)
                r = 10.0f;
            else if (*x < 1.0765625f)
                r = (1.0765625f - *x) * 100.0f;
            break;
        case 49:
            if (*x < 0.9765625f) {
                if (*y < 0.25f)
                    r = *x / 0.9765625f * (60.0f - *y * 45.0f * 4.0f) + 10.0f;
                else
                    r = *x / 0.9765625f * 60.0f * *y + 10.0f;
            } else if (*x < 1.0765625f) {
                if (*y < 0.25f)
                    r = (1.0765625f - *x) / 0.1f * (60.0f - *y * 45.0f * 4.0f) + 10.0f;
                else
                    r = (1.0765625f - *x) / 0.1f * (*y * 60.0f) + 10.0f;
            }
            break;
        case 50:
            r = *y * 100.0f;
            break;
        case 51:
            r = 100.0f;
            break;
        case 52:
            r = (1.0f - *y) * 100.0f;
            break;
        case 53:
            if (*x < 0.9765625f)
                r = *x * 50.0f;
            else if (*x < 1.0765625f)
                r = (1.0765625f - *x) / 0.1f * 50.0f;
            break;
        case 54:
            if (*x < 0.9765625f) {
                if (*y < 0.95f) {
                    if (*y * 0.9765625f / 0.95f < *x)
                        r = *y / 0.95f * 50.0f;
                    else
                        r = *x / 0.9765625f * 50.0f;
                } else {
                    float k = (*y - 0.95f) / 0.05f;
                    if (0.9765625f - k < *x)
                        r = k * 50.0f;
                    else
                        r = *x / 0.9765625f * 50.0f;
                }
            } else if (*x < 1.0765625f) {
                if (*y < 0.95f) {
                    float k = *y / 0.95f;
                    if (*x < 1.0765625f - k * 0.1f)
                        r = k * 50.0f;
                    else
                        r = (1.0765625f - *x) / 0.1f * 50.0f;
                } else {
                    float k = (*y - 0.95f) / 0.05f;
                    if (*x < k * 0.1f + 0.9765625f)
                        r = k * 50.0f;
                    else
                        r = (1.0765625f - *x) / 0.1f * 50.0f;
                }
            }
            break;
        case 55:
            r = *y * 160.0f;
            break;
        case 56:
            r = 160.0f;
            break;
        case 57:
            r = (1.0f - *y) * 160.0f;
            break;
        case 58:
            r = *y * 150.0f;
            break;
        case 59:
            r = 150.0f;
            break;
        case 60:
            r = (1.0f - *y) * 150.0f;
            break;
        case 61:
            if (*x < 0.78125f)
                r = *x * 40.0f + 10.0f;
            else if (*x < 0.9765625f)
                r = (0.9765625f - *x) * 40.0f / 0.1953125f + 10.0f;
            else if (*x < 1.0765625f)
                r = (1.0765625f - *x) * 10.0f / 0.1f;
            break;
        case 62:
            r = *y * 160.0f;
            break;
        case 63:
            r = 160.0f;
            break;
        case 64:
            r = (1.0f - *y) * 160.0f;
            break;
        }
    } else {
        switch (n) {
        case 1:
            if (-0.1f < *x)
                r = *x * 800.0f + 80.0f;
            else
                r = 0.0f;
            break;
        case 2: case 21:
            if (-0.1f < *x)
                r = *x * 150.0f + 15.0f;
            break;
        case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12:
        case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 25: case 26:
            if (-0.1f < *x)
                r = *x * 100.0f + 10.0f;
            break;
        case 50:
            if (-0.9765625f < *x)
                r = *y * 100.0f * (*x + 0.9765625f);
            break;
        case 51:
            if (-0.9765625f < *x)
                r = (*x + 0.9765625f) * 100.0f;
            break;
        case 52:
            if (-0.9765625f < *x)
                r = (1.0f - *y) * 100.0f * (*x + 0.9765625f);
            break;
        case 55:
            if (-0.29296875f < *x)
                r = *y * 160.0f * (*x + 0.29296875f) / 0.29296875f;
            break;
        case 56:
            if (-0.29296875f < *x)
                r = (*x + 0.29296875f) * 160.0f / 0.29296875f;
            break;
        case 57:
            if (-0.29296875f < *x)
                r = (1.0f - *y) * 160.0f * (*x + 0.29296875f) / 0.29296875f;
            break;
        case 58:
            if (-0.78125f < *x)
                r = *y * 150.0f * (*x + 0.78125f) / 0.78125f;
            break;
        case 59:
            if (-0.78125f < *x)
                r = (*x + 0.78125f) * 150.0f / 0.78125f;
            break;
        case 60:
            if (-0.78125f < *x)
                r = (1.0f - *y) * 150.0f * (*x + 0.78125f) / 0.78125f;
            break;
        case 61:
            if (-0.1f < *x)
                r = *x * 100.0f + 10.0f;
            break;
        case 62:
            if (-0.29296875f < *x)
                r = *y * 160.0f * (*x + 0.29296875f) / 0.29296875f;
            break;
        case 63:
            if (-0.29296875f < *x)
                r = (*x + 0.29296875f) * 160.0f / 0.29296875f;
            break;
        case 64:
            if (-0.29296875f < *x)
                r = (1.0f - *y) * 160.0f * (*x + 0.29296875f) / 0.29296875f;
            break;
        }
    }
    if (r <= 0.0f)
        *s = 0;
    return r;
}

/* A course point viewed as a search node: its position and its heading (65536 steps a turn). */
struct CourseNode {
    float x, y, z;
    short ang;
    short m14;
    int m16, m20;
};
extern CourseNode *D_23f7f0_nodes __asm__("D_23f7f0");

extern "C" {
Angle *f_099b98_a(Angle *a) __asm__("f_099b98");
float f_099efc(float x);
float f_09a07c(float x);
int f_0af550(const int *a);
}

/* @draft 0x0a8a60 us f_0a8a60
   WHAT IT DOES: Places the car on the course line at its course position: interpolates the two course points either side of it (the next one wrapping to the first) for the ground position and height, sets the heading to the interpolated point heading (shortest turn, wrapped), and moves the position sideways by the car's lateral offset turned by that heading.
   Remaining difference: two words: sched1 moves the fraction (s -= n) up from the join block ahead of the point address add, so dbr fills the branch slot with the add; retail has the add first and the subtraction in the slot. A separate fraction variable or the subtraction before the if is worse (s -= n between a and the if: 23 words). Verbose sched1: the cvt and sub are interblock (useful) motions from the join block with priority 101/97, so the sub is picked at t=15 ahead of the sll/addu (priority 1/0) and sched2 then breaks the tie by luid; retail needs the address add ahead of the sub in sched1's output. */
extern "C" void f_0a8a60(CarPhys *p)
{
    float pos[4];
    float off[4];
    Angle d;
    Angle e;
    float *h = &p->m32;
    CourseNode *b = D_23f7f0_nodes;
    float s = p->m16;
    int n = (int)s;
    CourseNode *a = &b[n];
    if (n + 1 < D_2456b8)
        b = a + 1;
    s -= n;
    pos[1] = a->x;
    pos[1] += (b->x - pos[1]) * s;
    pos[0] = a->y;
    pos[0] += (b->y - pos[0]) * s;
    p->m32 = a->ang * 9.58738019107841e-05f;
    d.a = b->ang * 9.58738019107841e-05f - p->m32;
    p->m32 += f_099b98_a(&d)->a * s;
    f_099b98(h);
    e.a = p->m32;
    off[1] = p->m20 * 1024.0f;
    off[0] = 0.0f;
    f_099b98(&e);
    f_09b394(e, &off[0], &off[1]);
    pos[0] += off[0];
    pos[1] += off[1];
    p->m4 = pos[0];
    p->m0 = pos[1];
    p->m12 = a->z;
    p->m12 += (b->z - p->m12) * s;
}

extern "C" {
float f_09a86c(float x, float z);
float f_099fc4(float a);
float f_09a154(float a);
float f_09a218(float a);
}

/* @draft 0x0aa3f8 us f_0aa3f8
   WHAT IT DOES: Projects the probe point (m148, m152) onto the course segment between the points m156 and m160: takes the segment's direction, measures the probe's sideways distance from it (scaled by 1/1024 into m140), corrects the along-segment distance for the two end points' headings, and stores the clamped fraction 0..1 in m168 and the wrapped course position (point m156 plus the fraction) in m136.
   Remaining difference: sched1 order around the first heading call: retail keeps all four products before the call and both sums (den, num) after it, with u's subtraction in the call slot, which costs a sixth saved FPR (f25 holds the angle scale); here num's sum goes before the call and dy*sn into the slot, so the FPRs differ throughout. Sums written after the call are worse (sched1 does not hoist the products back). */
extern "C" void f_0aa3f8(CarPhys *p)
{
    Angle a;
    Angle ra;
    Angle rb;
    Angle da;
    Angle db;
    float w;
    CourseNode *list = D_23f7f0_nodes;
    CourseNode *e = &list[p->m156];
    CourseNode *f = &list[p->m160];
    float ey = e->y;
    float ex = e->x;
    float dy = ey - f->y;
    float dx = ex - f->x;
    a.a = f_09a86c(dx, dy);
    f_099b98(&a);
    float c = f_099fc4(a.a);
    float sn = f_09a154(a.a);
    float den = dx * c + dy * sn;
    float px = p->m148;
    float pz = p->m152;
    float u = (px - ex) * sn - (pz - ey) * c;
    float num = (ex - px) * c + (ey - pz) * sn;
    ra.a = e->ang * 9.58738019107841e-05f;
    f_099b98(&ra);
    rb.a = f->ang * 9.58738019107841e-05f;
    f_099b98(&rb);
    da.a = a.a - ra.a;
    f_099b98(&da);
    float t = u * f_09a218(da.a);
    num += t;
    den += t;
    db.a = a.a - rb.a;
    f_099b98(&db);
    den -= u * f_09a218(db.a);
    num /= den;
    if (num > 1.0f)
        num = 1.0f;
    else if (num < 0.0f)
        num = 0.0f;
    w = p->m156 + num;
    p->m136 = f_0af478(&w);
    p->m168 = num;
    p->m140 = u * 0.0009765625f;
}

/* @implements 0x0ac400 us f_0ac400
   WHAT IT DOES: The surface factor table: for the surface kind *k returns a fixed factor or a linear function of the value *v (cases 7 to 20 and 45 to 48); unknown kinds give 0. */
extern "C" float f_0ac400(CarPhys *p, const float *v, int *k)
{
    float r = 0.0f;
    switch (*k) {
    case 1: r = 0.2f; break;
    case 3: r = 2.6f; break;
    case 4: r = 3.0f; break;
    case 5: r = 0.55f; break;
    case 6: r = 1.2f; break;
    case 7: r = *v; break;
    case 8: r = 1.0f - *v; break;
    case 10: r = *v * 0.26666668f + 0.8f; break;
    case 11: r = *v * 0.26666668f + 1.0666667f; break;
    case 12: r = *v * 0.26666668f + 1.3333334f; break;
    case 9:
    case 13: r = 0.8f; break;
    case 14: r = 1.6f; break;
    case 15: r = 0.26666668f * *v; break;
    case 16: r = (*v + 1.0f) * 0.26666668f; break;
    case 17: r = (*v + 2.0f) * 0.26666668f; break;
    case 18: r = 0.26666668f * (3.0f - *v); break;
    case 19: r = 0.26666668f * (2.0f - *v); break;
    case 20: r = 0.26666668f * (1.0f - *v); break;
    case 2:
    case 21: r = 1.0f; break;
    case 22: r = 0.4f; break;
    case 23: r = 0.3f; break;
    case 24: r = 0.6f; break;
    case 25: r = 1.05f; break;
    case 26: r = 0.44f; break;
    case 45: r = *v * 0.9765625f * 0.5f; break;
    case 46: r = (*v + 1.0f) * 0.9765625f * 0.5f; break;
    case 47: r = (2.0f - *v) * 0.9765625f * 0.5f; break;
    case 48: r = (1.0f - *v) * 0.9765625f * 0.5f; break;
    case 44:
    case 49: r = 0.9765625f; break;
    case 53:
    case 54: r = 1.0765625f; break;
    default: break;
    case 61: r = 0.9765625f; break;
    }
    return r;
}

/* The point index i wrapped into the ring. */
static inline int CourseWrap(int i)
{
    return f_0af550(&i);
}

/* Which side of course point k's heading line the position v lies on (negative: ahead). */
static inline float CourseSide(const float *v, CourseNode *list, int k)
{
    CourseNode *e = &list[k];
    Angle a;
    a.a = e->ang * 9.5873802e-05f;
    float t = f_099b98_a(&a)->a;
    return (v[1] - e->y) * f_09a07c(t) + (v[0] - e->x) * f_099efc(t);
}

/* @draft 0x0a98d8 us f_0a98d8
   WHAT IT DOES: Finds the course segment under the probe point (m148, m152): a binary search over the 16 course points around the car's last point m180, each step testing which side of a point's heading line the probe lies on; the segment's two point indices go into m156 and m160.
   Remaining difference (46 of 587 words): one register swap: retail keeps the point list in s1 and m180 in s2, here the reverse; the code is otherwise retail's. Global-alloc ranks n (pseudo, 21 refs, freq 6250, live 391 insns: priority 63.94) just ahead of the list (16 refs, freq 5000, live 313: 63.90); retail must have n's live length at least 392 against 313, or two fewer insns where both are live. Not the declaration order, not loading the list after v, not the helper as a statement expression (the post-sched1 live lengths do not move), and not a const view of the global (that drops the list below p). */
extern "C" void f_0a98d8(CarPhys *p)
{
    CourseNode *list = D_23f7f0_nodes;
    int n = p->m180;
    float v[2];
    v[0] = p->m148;
    v[1] = p->m152;
    if (CourseSide(v, list, n) < 0.0f) {
        int kp4 = CourseWrap(n + 4);
        if (CourseSide(v, list, kp4) < 0.0f) {
            int kp6 = CourseWrap(n + 6);
            if (CourseSide(v, list, kp6) < 0.0f) {
                int kp7 = CourseWrap(n + 7);
                if (CourseSide(v, list, kp7) < 0.0f) {
                    p->m156 = kp7;
                    p->m160 = CourseWrap(n + 8);
                } else {
                    p->m156 = CourseWrap(n + 6);
                    p->m160 = kp7;
                }
            } else {
                int kp5 = CourseWrap(n + 5);
                if (CourseSide(v, list, kp5) < 0.0f) {
                    p->m156 = kp5;
                    p->m160 = CourseWrap(n + 6);
                } else {
                    p->m156 = CourseWrap(n + 4);
                    p->m160 = kp5;
                }
            }
        } else {
            int kp2 = CourseWrap(n + 2);
            if (CourseSide(v, list, kp2) < 0.0f) {
                int kp3 = CourseWrap(n + 3);
                if (CourseSide(v, list, kp3) < 0.0f) {
                    p->m156 = kp3;
                    p->m160 = CourseWrap(n + 4);
                } else {
                    p->m156 = CourseWrap(n + 2);
                    p->m160 = kp3;
                }
            } else {
                int kp1 = CourseWrap(n + 1);
                if (CourseSide(v, list, kp1) < 0.0f) {
                    p->m156 = kp1;
                    p->m160 = CourseWrap(n + 2);
                } else {
                    p->m156 = CourseWrap(n);
                    p->m160 = kp1;
                }
            }
        }
    } else {
        int km4 = CourseWrap(n - 4);
        if (CourseSide(v, list, km4) < 0.0f) {
            int km2 = CourseWrap(n - 2);
            if (CourseSide(v, list, km2) < 0.0f) {
                int km1 = CourseWrap(n - 1);
                if (CourseSide(v, list, km1) < 0.0f) {
                    p->m156 = km1;
                    p->m160 = CourseWrap(n);
                } else {
                    p->m156 = CourseWrap(n - 2);
                    p->m160 = km1;
                }
            } else {
                int km3 = CourseWrap(n - 3);
                if (CourseSide(v, list, km3) < 0.0f) {
                    p->m156 = km3;
                    p->m160 = CourseWrap(n - 2);
                } else {
                    p->m156 = CourseWrap(n - 4);
                    p->m160 = km3;
                }
            }
        } else {
            int km6 = CourseWrap(n - 6);
            if (CourseSide(v, list, km6) < 0.0f) {
                int km5 = CourseWrap(n - 5);
                if (CourseSide(v, list, km5) < 0.0f) {
                    p->m156 = km5;
                    p->m160 = CourseWrap(n - 4);
                } else {
                    p->m156 = CourseWrap(n - 6);
                    p->m160 = km5;
                }
            } else {
                int km7 = CourseWrap(n - 7);
                if (CourseSide(v, list, km7) < 0.0f) {
                    p->m156 = km7;
                    p->m160 = CourseWrap(n - 6);
                } else {
                    p->m156 = CourseWrap(n - 8);
                    p->m160 = km7;
                }
            }
        }
    }
}

extern "C" {
void f_0ad084(CarPhys *p, int i);
void f_0aeacc(CarPhys *p, CarPhys *w);
}

/* A scratch copy of the physics state, built and torn down by the object's own routines. */
struct CarPhysWork : CarPhys {
    CarPhysWork() { f_0a6f88(this); }
    ~CarPhysWork() { f_0a6fac(this); }
};

/* The file's global scratch physics record, built at startup and torn down at exit. */
CarPhysWork D_245430;

/* @implements 0x0af2cc us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the global physics record D_245430 (f_0a6f88); at shutdown, tears it down (f_0a6fac). */
/* @implements 0x0af340 us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above (previously drafted by hand in AngleWrap.c). */
/* @implements 0x0af360 us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */


/* @draft 0x0a74cc us f_0a74cc
   WHAT IT DOES: The per frame physics step of one car: stores the previous height, looks the car up on the track, probes the four wheels, then either keeps the stored state (car inside its window) or reruns the wheel steps on a scratch copy and blends it back, for the whole car or wheel by wheel.
   Remaining difference: loop.c hoists the -1 of the wheel loop's else arm into a sixth saved register (retail loads it in the branch slot), and retail holds the probe point's address in s2 from the prologue; the rest follows from those. */
extern "C" void f_0a74cc(CarPhys *p)
{
    p->m24 = p->m16;
    p->m28 = p->m20;
    f_0ae9f8(p);
    f_099b98((char *)p + 8);
    CarPhysWork w;
    char *b = (char *)&D_23c820;
    char *s = b + 12256;
    char *ar = b + 12240;
    GroundPt pt;
    pt.x = p->m0;
    pt.y = p->m12;
    pt.z = p->m4;
    pt.w = 1.0f;
    if (p->m116)
        p->m92 = f_0aff7c(s, &pt.x);
    else
        p->m92 = f_0af788(s, &pt.x);
    p->m104 = f_0af5e8(s, &p->m92);
    f_0aa608(p);
    float d = p->m40 + -4.0f;
    if (d <= p->m20 && p->m20 <= p->m36 + 4.0f) {
        p->m108 = 0;
        w.m0 = p->m0;
        w.m4 = p->m4;
        w.m8 = p->m8;
        w.m12 = p->m132;
        w.m16 = p->m128;
        w.m116 = p->m116;
        f_0ae9f8(&w);
        f_0a9158(p);
        f_0aa374(p);
        f_0ab074(p);
        f_0ac630(p);
        f_0ad82c(p);
    } else {
        p->m108 = 2;
        f_0ab220(p);
        f_0acd80(p);
        f_0addbc(p);
    }
    p->m120 = p->m16;
    if (p->m108 == 0) {
        if (p->m20 < p->m40 + -0.0f || p->m36 + 0.0f < p->m20) {
            p->m108 = 1;
            {
                int i;
                unsigned short *d, *q;
                i = 0;
                d = (unsigned short *)PH(&w, 392);
                w.m100 = p->m100;
                q = (unsigned short *)PH(p, 392);
                for (; i < 4; i++) {
                    unsigned short h = *q++;
                    float u = PF(p, 224)[i];
                    float t = PF(p, 240)[i];
                    PF(&w, 224)[i] = u;
                    *d++ = h;
                    PF(&w, 240)[i] = t;
                }
            }
            *PF(&w, 172) = *PF(p, 172);
            *PF(&w, 176) = *PF(p, 176);
            f_0aa608(&w);
            f_0ab220(&w);
            f_0acd80(&w);
            f_0addbc(&w);
            f_0aeacc(p, &w);
        } else {
            if ((unsigned short)p->m92 == 0xffff) {
                char *ps = ar + 112;
                if (p->m116)
                    p->m92 = f_0aff7c(ps, &pt.x);
                else
                    p->m92 = f_0af788(ps, &pt.x);
                p->m104 = f_0af5e8(ps, &p->m92);
            }
            p->m100 = -1;
            for (int i = 0; i < 4; i++) {
                if (PF(p, 304)[i] < PF(p, 416)[i] + -0.0f || PF(p, 432)[i] + 0.0f < PF(p, 304)[i]) {
                    {
                        int j;
                        unsigned short *d, *q;
                        j = 0;
                        d = (unsigned short *)PH(&w, 392);
                        w.m100 = p->m100;
                        q = (unsigned short *)PH(p, 392);
                        for (; j < 4; j++) {
                            unsigned short h = *q++;
                            float u = PF(p, 224)[j];
                            float t = PF(p, 240)[j];
                            PF(&w, 224)[j] = u;
                            *d++ = h;
                            PF(&w, 240)[j] = t;
                        }
                    }
                    PI(p, 400)[i] = 1;
                    *PF(&w, 172) = *PF(p, 172);
                    *PF(&w, 176) = *PF(p, 176);
                    f_0aaf68(&w, i);
                    f_0ab43c(&w, i);
                    f_0ad084(&w, i);
                    f_0af140(p, &w, i);
                } else {
                    PH(p, 392)[i] = -1;
                }
            }
        }
    }
    f_0aea0c(p);
    f_0aea84(p);
}

/* @draft 0x0a7eac us f_0a7eac
   WHAT IT DOES: The physics step used when the car is placed on the track: stores the previous height, looks the car up on the track (mode 2 when that fails), probes the wheels with the probe matching the old mode, then either keeps the state (car within 3 of its window) or reruns the wheel steps on a scratch copy and blends it back, for the whole car or wheel by wheel.
   Remaining difference: as in f_0a74cc, the second loop pass hoists the wheel loop's -1 into a sixth saved register (retail: -fno-rerun-loop-opt-like behaviour for this loop, but that flag breaks three exact functions of the file); retail also keeps the two window margins in $f2/$f3 and copies them into $f20/$f21 at the loop. */
extern "C" void f_0a7eac(CarPhys *p)
{
    int mode = p->m108;
    p->m24 = p->m16;
    p->m28 = p->m20;
    f_0ae9f8(p);
    f_099b98((char *)p + 8);
    CarPhysWork w;
    char *b = (char *)&D_23c820;
    char *s = b + 12256;
    GroundPt pt;
    pt.x = p->m0;
    pt.y = p->m12;
    pt.z = p->m4;
    pt.w = 1.0f;
    if (p->m116)
        p->m92 = f_0aff7c(s, &pt.x);
    else
        p->m92 = f_0af788(s, &pt.x);
    p->m104 = f_0af5e8(s, &p->m92);
    if (p->m104 < 0) {
        p->m108 = 2;
        f_0aa608(p);
        f_0ab220(p);
        f_0acd80(p);
        f_0addbc(p);
    } else {
        p->m108 = 0;
        w.m0 = p->m0;
        w.m4 = p->m4;
        w.m8 = p->m8;
        w.m12 = p->m132;
        w.m16 = p->m128;
        w.m116 = p->m116;
        f_0ae9f8(&w);
        if (mode < 2)
            f_0a9158(p);
        else
            f_0a9248(p);
        f_0aa374(p);
        f_0ab074(p);
        f_0ac630(p);
        f_0ad82c(p);
        p->m120 = p->m16;
    }
    if (p->m108 == 0) {
        float lo = -3.0f;
        float hi = 3.0f;
        if (p->m20 < p->m40 + lo || p->m36 + hi < p->m20) {
            p->m108 = 1;
            {
                int i;
                unsigned short *d, *q;
                i = 0;
                d = (unsigned short *)PH(&w, 392);
                w.m100 = p->m100;
                q = (unsigned short *)PH(p, 392);
                for (; i < 4; i++) {
                    unsigned short h = *q++;
                    float u = PF(p, 224)[i];
                    float t = PF(p, 240)[i];
                    PF(&w, 224)[i] = u;
                    *d++ = h;
                    PF(&w, 240)[i] = t;
                }
            }
            *PF(&w, 172) = *PF(p, 172);
            *PF(&w, 176) = *PF(p, 176);
            f_0aa608(&w);
            f_0ab220(&w);
            f_0acd80(&w);
            f_0addbc(&w);
            f_0aeacc(p, &w);
        } else {
            p->m100 = -1;
            for (int i = 0; i < 4; i++) {
                if (PF(p, 304)[i] < PF(p, 416)[i] + lo || PF(p, 432)[i] + hi < PF(p, 304)[i]) {
                    {
                        int j;
                        unsigned short *d, *q;
                        j = 0;
                        d = (unsigned short *)PH(&w, 392);
                        w.m100 = p->m100;
                        q = (unsigned short *)PH(p, 392);
                        for (; j < 4; j++) {
                            unsigned short h = *q++;
                            float u = PF(p, 224)[j];
                            float t = PF(p, 240)[j];
                            PF(&w, 224)[j] = u;
                            *d++ = h;
                            PF(&w, 240)[j] = t;
                        }
                    }
                    PI(p, 400)[i] = 1;
                    *PF(&w, 172) = *PF(p, 172);
                    *PF(&w, 176) = *PF(p, 176);
                    f_0aaf68(&w, i);
                    f_0ab43c(&w, i);
                    f_0ad084(&w, i);
                    f_0af140(p, &w, i);
                } else {
                    PH(p, 392)[i] = -1;
                }
            }
        }
    }
    f_0aea0c(p);
    f_0aea84(p);
}

/* @draft 0x0a7b60 us f_0a7b60
   WHAT IT DOES: When the car is in mode 0, rebuilds a scratch copy from the stored previous state and either reruns the whole-car wheel steps on it (car outside its window) or, after looking the stored position up on the track if the car has no track piece, reruns and blends the wheels outside their own windows one by one.
   Remaining difference: as in f_0a74cc: the rerun loop pass moves the wheel loop's -1 out of the loop (its first pass finds the move "not desirable", and retail's loop evidently stayed that way), costing a sixth saved register. */
extern "C" void f_0a7b60(CarPhys *p)
{
    if (p->m108 != 0)
        return;
    CarPhysWork w;
    w.m0 = p->m592;
    w.m4 = p->m596;
    w.m12 = p->m600;
    w.m8 = p->m608;
    w.m16 = p->m612;
    w.m116 = p->m616;
    f_0ae9f8(&w);
    if (p->m20 < p->m40 + -0.0f || p->m36 + 0.0f < p->m20) {
        p->m108 = 1;
        {
            int i;
            unsigned short *d, *q;
            i = 0;
            d = (unsigned short *)PH(&w, 392);
            w.m100 = p->m100;
            q = (unsigned short *)PH(p, 392);
            for (; i < 4; i++) {
                unsigned short h = *q++;
                float u = PF(p, 224)[i];
                float t = PF(p, 240)[i];
                PF(&w, 224)[i] = u;
                *d++ = h;
                PF(&w, 240)[i] = t;
            }
        }
        *PF(&w, 172) = *PF(p, 172);
        *PF(&w, 176) = *PF(p, 176);
        f_0aa608(&w);
        f_0ab220(&w);
        f_0acd80(&w);
        f_0addbc(&w);
        f_0aeacc(p, &w);
    } else {
        if ((unsigned short)p->m92 == 0xffff) {
            char *ps = (char *)&D_23c820 + 12352;
            GroundPt pt;
            pt.x = p->m592;
            pt.y = p->m600;
            pt.z = p->m596;
            pt.w = 1.0f;
            if (p->m116)
                p->m92 = f_0aff7c(ps, &pt.x);
            else
                p->m92 = f_0af788(ps, &pt.x);
            p->m104 = f_0af5e8(ps, &p->m92);
        }
        p->m100 = -1;
        for (int i = 0; i < 4; i++) {
            if (PF(p, 304)[i] < PF(p, 416)[i] + -0.0f || PF(p, 432)[i] + 0.0f < PF(p, 304)[i]) {
                {
                    int j;
                    unsigned short *d, *q;
                    j = 0;
                    d = (unsigned short *)PH(&w, 392);
                    w.m100 = p->m100;
                    q = (unsigned short *)PH(p, 392);
                    for (; j < 4; j++) {
                        unsigned short h = *q++;
                        float u = PF(p, 224)[j];
                        float t = PF(p, 240)[j];
                        PF(&w, 224)[j] = u;
                        *d++ = h;
                        PF(&w, 240)[j] = t;
                    }
                }
                PI(p, 400)[i] = 1;
                *PF(&w, 172) = *PF(p, 172);
                *PF(&w, 176) = *PF(p, 176);
                f_0aaf68(&w, i);
                f_0ab43c(&w, i);
                f_0ad084(&w, i);
                f_0af140(p, &w, i);
            } else {
                PH(p, 392)[i] = -1;
            }
        }
    }
}

extern "C" int f_0af4e0(const int *a, const int *b);

/* The ring distance from point b to point a (within half the ring). */
static inline int CourseDiff(int a, const int &b)
{
    return f_0af4e0(&a, &b);
}

/* @draft 0x0aa204 us f_0aa204
   WHAT IT DOES: Finds the course segment under the point pos between the course points lo and hi by bisection: tests the side of the middle point's heading line and recurses into the half that holds pos until the two points are neighbours, returning the lower point of the segment.
   Remaining difference: stack slot numbering only (retail: wrap temporary 16, the copy of lo 20, lo 24, hi 28, then the angle and m); the instructions are otherwise retail's. Not a by-value, by-reference or pointer form of the distance helper, nor a 16-byte probe vector, nor CourseWrap taking a const reference (no slot moves). Retail's order (wrap param before the distance copy, then lo, hi) means the wrap temporary exists before its argument is expanded. */
extern "C" int f_0aa204(const float *pos, int lo, int hi)
{
    float v[2];
    int m = CourseWrap((CourseDiff(lo, hi) >> 1) + hi);
    v[0] = pos[0];
    v[1] = pos[1];
    if (CourseSide(v, D_23f7f0_nodes, m) < 0.0f) {
        if (CourseDiff(hi, m) < 2)
            return m;
        return f_0aa204(pos, m, hi);
    }
    if (CourseDiff(m, lo) < 2)
        return lo;
    return f_0aa204(pos, lo, m);
}

/* A 2D vector of the course plane (x and z). */
struct CVec2 {
    float x, y;
    CVec2() {}
    CVec2(float a, float b) : x(a), y(b) {}
    CVec2 operator-(const CVec2 &o) const { return CVec2(x - o.x, y - o.y); }
    CVec2 operator+(const CVec2 &o) const { return CVec2(x + o.x, y + o.y); }
    CVec2 operator*(float k) const { return CVec2(x * k, y * k); }
    float Dot(CVec2 o) const { return x * o.x + y * o.y; }
    float Len() const { return sqrtf(x * x + y * y); }
};

/* One course segment (40 bytes) of the list at D_23f7fc, D_2456c0 segments in a ring: its
   course position, start point, forward direction, a curve flag, the curve's centre or the
   straight's direction, and the cross line used for the projection. */
struct CourseSeg {
    float pos;
    CVec2 p;
    CVec2 dir;
    int curved;
    CVec2 c;
    CVec2 e;
};
extern CourseSeg *D_23f7fc_segs __asm__("D_23f7fc");
extern int D_2456c0;
extern "C" int f_0af59c(const int *a);

/* The segment index i wrapped into the ring. */
static inline int SegWrap(int i)
{
    return f_0af59c(&i);
}

/* @draft 0x0aa748 us f_0aa748
   WHAT IT DOES: Tracks the probe point (m148, m152) along the course segments: finds the segment from the stored one (searching the whole ring the first time, by course position), steps forward or back to the segment that holds the point, projects the point onto it (a straight or a curve), and stores the course position (m136), its fraction (m168) and the signed distance from the course line (m140).
   Remaining difference: retail is 268 bytes longer: its vector type copies values through the stack (the point stored to the stack first, a segment point copied with float stores, each difference stored, block-copied with integer loads to two places, then reloaded). A grid of 136 class shapes (copy constructor, assignment, by-value or reference operands, member or free dot) on the first dot product came closest with a const-reference operator- assigned into a local and a by-value member Dot (the form used here: 1,864 bytes against 2,080). Reasoned from retail's slot use: the segment point is copied with float stores (a by-value operand with a user copy constructor reproduces that), but retail then keeps the result in its own temporary and block-copies it twice, which this compiler removes once a user copy constructor exists. */
extern "C" void f_0aa748(CarPhys *p)
{
    CourseSeg *list = D_23f7fc_segs;
    if (p->m164 < 0) {
        if (p->m128 < list[0].pos) {
            p->m164 = D_2456c0 - 1;
        } else {
            int k = D_2456c0 >> 1;
            if (p->m128 < list[k].pos)
                k = 1;
            else
                k = k + 1;
            for (; k < D_2456c0; k++)
                if (p->m128 < list[k].pos)
                    break;
            p->m164 = SegWrap(k - 1);
        }
    }
    {
        int idx = p->m164;
        CVec2 v(p->m148, p->m152);
        CourseSeg *s = &list[idx];
        if (s->dir.Dot(v - s->p) >= 0.0f) {
            for (int k = 1; k < D_2456c0; k++) {
                CourseSeg *t = &list[SegWrap(idx + k)];
                if (t->dir.Dot(v - t->p) < 0.0f) {
                    p->m164 = SegWrap(idx + k - 1);
                    break;
                }
            }
        } else {
            for (int k = 1; k < D_2456c0; k++) {
                int j = SegWrap(idx - k);
                CourseSeg *t = &list[j];
                if (t->dir.Dot(v - t->p) >= 0.0f) {
                    p->m164 = j;
                    break;
                }
            }
        }
    }
    CourseSeg *s = &list[p->m164];
    CVec2 v(p->m148, p->m152);
    CVec2 q;
    if (s->curved) {
        CVec2 r = v - s->c;
        float t = s->e.Dot(s->p - s->c) / s->e.Dot(r);
        q = s->c + r * t;
    } else {
        float t = s->e.Dot(s->p - v) / s->e.Dot(s->c);
        q = v + s->c * t;
    }
    CourseSeg *n = &list[SegWrap(p->m164 + 1)];
    float len = (n->p - s->p).Len();
    float ratio = (q - s->p).Len() / len;
    float a = n->pos;
    float d = f_0af380(&a, &s->pos) * ratio + s->pos;
    float pos = f_0af478(&d);
    p->m136 = pos;
    p->m168 = pos - (int)pos;
    float dist = (q - v).Len() * 0.0009765625f;
    if (s->e.Dot(v - s->p) < 0.0f)
        p->m140 = dist;
    else
        p->m140 = -dist;
}
