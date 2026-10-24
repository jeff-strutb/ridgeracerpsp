/* The race sequence's common part (retail 0x0ea8b4 to 0x0ec254): the state every race sequence
   (normal circuit, time attack, network) shares. It records the race's car list and number,
   reads the sequence number from the race table, registers every car with the race's car
   manager (D_27eca4) and its fade, sets up the small race texture, and steps the per-frame
   draw of the race view and the two blinking flags (D_27ecb1, D_27ecb2) that drive the 2D
   overlay's blink. */

#include <string.h>

/* The fade sequence (FadeSequence.cpp). */
class CFadeSequence {
public:
    void f_0ff798();
    void f_0ffa44();
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

/* @implements 0x0ec1cc us f_0ec1cc
   WHAT IT DOES: Draws the race's 2D overlay: its first pass always, its second pass unless
   the game is running normally with the blink on and its second flag off. */
void f_0ec1cc(void)
{
    D_1d3d40->v4();
    if (D_1d88a0->m11 || D_1d88a0->m12 || !D_27ecb1 || D_27ecb2)
        D_1d3d40->v5();
}
