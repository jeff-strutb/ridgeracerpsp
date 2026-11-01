/* The car physics object file (retail 0x0a6f6c to 0x0af340): the per car state of the
   physics, its constructor and reset, the per frame step that moves the car's
   simulation values into their stored copies, the four wheel and suspension updates and
   the drive, brake and surface helpers they call. */

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
    char p617[23];
};
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
void f_0a6fac(void);
void f_0a6fac_p(CarPhys *p) __asm__("f_0a6fac");
void f_0a6f88(CarPhys *p);
void f_099b98(void *p);
float f_0af380(const float *a, const float *b);
short f_0aff7c(void *t, const float *v);
short f_0af788(void *t, const float *v);
int f_0af5e8(void *t, const short *key);
}

/* The state of the car's MapMgr sub-object used by the two track lookups. */
extern char D_23c820[];
extern char D_245430[];
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
extern "C" void f_0a6fac(void)
{
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

/* @draft 0x0a862c us f_0a862c
   WHAT IT DOES: Copies the car's position and height to their stored copies, updates the car's mode flag from its index and runs the matching step.
   Remaining difference: 2 of 33 words: retail loads m104 into v1 (the 2 for the store goes into v0 in the bltz slot); this loads it into v0. Not the return type, a predicate, a local, a status variable or a goto (all tried). */
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

/* @draft 0x0af2cc us f_0af2cc
   WHAT IT DOES: Calls one of two routines on the global car record D_245430: f_0a6f88 when the first argument is 1 and the second is 0xffff, and f_0a6fac when the first is 0 and the second is 0xffff.
   Remaining difference: retail keeps the second call inline (beqz to the epilogue); here GCC's call heuristic (70%) moves it out of line like the first. Not a goto, an inverted early return, a bool, or a pointer local. */
extern "C" void f_0af2cc(int a, int b)
{
    int s = b == 0xffff;
    if (s && a == 1)
        f_0a6f88((CarPhys *)D_245430);
    if (s && a == 0)
        f_0a6fac_p((CarPhys *)D_245430);
}

extern float D_2456b0;

/* @draft 0x0a737c us f_0a737c
   WHAT IT DOES: Sets up the car physics state from four float arguments: the position and height, with the mode and index fields reset and the stored copies cleared.
   Remaining difference: store order (first run). */
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
   Remaining difference: retail loads p's height before q's for the final blend; here q's comes first. */
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
   Remaining difference (29 of 73 words): register choice only: retail keeps the first area's base height in $f11 and the second's in $f10 (here the reverse), and forms the row addresses in v0/v1 the other way round; the instruction sequence is otherwise retail's. */
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
   Remaining difference: scheduling only: retail loads the height and heading first and stores the heading to the stack after the vector; the four result loads come out in another order. 720 setup orders and 72 result orders tried (the best is kept). */
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
   Remaining difference: retail keeps i*4 in s0 from the prologue and stores q's blended heights in the other order. The -0.0 additions are retail's literals. */
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
