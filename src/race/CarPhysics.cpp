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
    int m64;
    int m68;
    int m72;
    int m76;
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
void f_0a6f88(CarPhys *p);
void f_099b98(void *p);
float f_0af380(const float *a, const float *b);
short f_0aff7c(void *t, const float *v);
short f_0af788(void *t, const float *v);
int f_0af5e8(void *t, const short *key);
}

/* The state of the car's MapMgr sub-object used by the two track lookups. */
extern char D_23c820[];
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

/* @draft 0x0a853c us f_0a853c
   WHAT IT DOES: Looks up the car's position on the track: stores the lookup's short result and the table entry for the car's key.
   Remaining difference: the retail pointer to the track sub-object is built as lui plus a 15696 low part, then a plain +12256; this form is not reproduced. */
extern "C" void f_0a853c(CarPhys *p)
{
    float v[4];
    v[0] = p->m0;
    v[2] = p->m4;
    v[1] = p->m12;
    v[3] = 1.0f;
    void *s = (char *)&D_23c820; s = (char *)s + 27952;
    p->m92 = f_0aff7c(s, v);
    p->m104 = f_0af5e8(s, &p->m92);
}

/* @draft 0x0a85b4 us f_0a85b4
   WHAT IT DOES: The second track lookup: the same as f_0a853c with the second lookup routine.
   Remaining difference: the same track sub-object pointer as f_0a853c. */
extern "C" void f_0a85b4(CarPhys *p)
{
    float v[4];
    v[0] = p->m0;
    v[2] = p->m4;
    v[1] = p->m12;
    v[3] = 1.0f;
    void *s = (char *)&D_23c820; s = (char *)s + 27952;
    p->m92 = f_0af788(s, v);
    p->m104 = f_0af5e8(s, &p->m92);
}

/* @draft 0x0a862c us f_0a862c
   WHAT IT DOES: Copies the car's position and height to their stored copies, updates the car's mode flag from its index and runs the matching step.
   Remaining difference: the branch layout at the end (the return jumps to a different block) and the order of the first copies. */
extern "C" void f_0a862c(CarPhys *p)
{
    p->m24 = p->m16;
    p->m28 = p->m20;
    int s0 = p->m108 < 2;
    f_0ae9f8(p);
    f_099b98((char *)p + 8);
    if (p->m104 < 0) {
        p->m108 = 2;
    } else {
        p->m108 = 0;
        if (s0)
            f_0a9158(p);
        else
            f_0a9248(p);
    }
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
