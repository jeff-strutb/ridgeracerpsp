/* The car data object file (retail 0x036cb8 to 0x037448). It shows and frees the scenes of
   the cars in the race (the player cars' "<name>_M" and the computer cars' "<name>_S"), the
   car class scene "C<class>", and loads the cars' textures. It also holds the car database. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern "C" void f_00d354(char *buf, int size, const char *fmt, ...);
extern char D_245178[];
void *f_022de4(int area, void *file, int id);

/* A pair of values the settings hand back by value. */
struct Pair {
    char *a;
    int b;
};

/* A data package or scene player: its entries are found by name. */
struct CPackage {
    void *f_002acc(const char *name);
    int m0[70];
};

/* The sequence manager, as far as its car settings and scene players are concerned. */
struct CSequence {
    Pair f_0031dc(int i);
    Pair f_003200(int i);
    CPackage *f_005a38(const char *name);
    void *f_005c34(const char *name);
    void f_005d4c(const char *name);
};
extern CSequence D_1dd6b0;

namespace DB {
class CDataBase {
public:
    CDataBase() { Clear(); }
    virtual ~CDataBase() {}
    virtual int Set(void *data);
    virtual int f_0368d8();
    virtual int f_0368e0();
    virtual char *Data() { return (char *)m36; }
    virtual void Clear();
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
    int f_036a3c(const char *name, int *names, unsigned int n);

    unsigned int cols;
    unsigned int rows;
    int type;
    int offset;
    int colName;
    int rowName;
    int m28;
    int m32;
    int m36;
};
}

extern unsigned char D_24063c[];
extern const int D_1a211c[];

/* A computer car's settings. */
static inline Pair GetS(int i)
{
    Pair r = D_1dd6b0.f_0031dc(i);
    return r;
}

/* A player car's settings. */
static inline Pair GetM(int i)
{
    Pair r = D_1dd6b0.f_003200(i);
    return r;
}

/* The car database. */
DB::CDataBase D_240740;
/* A scene name being built. */
char D_240768[64];

/* @implements 0x036cb8 us f_036cb8
   WHAT IT DOES: Shows the free scenes of the two player cars and of the car class. */
void f_036cb8(void)
{
    for (int i = 0; i < 2; i++) {
        Pair p = D_1dd6b0.f_003200(i);
        char *n = p.a;
        if (n) {
            sprintf(D_240768, "%s_M_Free", D_1dd6b0.f_003200(i).a);
            D_1dd6b0.f_005d4c(D_240768);
        }
    }
    Pair p = D_1dd6b0.f_0031dc(0);
    char *n = p.a;
    if (n) {
        char *c = D_1dd6b0.f_0031dc(0).a;
        char *f = D_240740.f_0368e8("Class", c, 0, 0);
        memcpy(D_24063c, f, D_1a211c[1]);
        sprintf(D_240768, "C%d_Free", D_24063c[0]);
        D_1dd6b0.f_005d4c(D_240768);
    }
}

/* @implements 0x036dec us f_036dec
   WHAT IT DOES: Shows the scenes of the two player cars (by car name and by car) and of the
   car class. */
void f_036dec(void)
{
    for (int i = 0; i < 2; i++) {
        Pair p = D_1dd6b0.f_003200(i);
        char *n = p.a;
        if (n) {
            const char *col = "CarName";
            sprintf(D_240768, "%s_M", D_240740.f_0368e8(col, D_1dd6b0.f_003200(i).a, 0, 0));
            D_1dd6b0.f_005d4c(D_240768);
            sprintf(D_240768, "%s_M", D_1dd6b0.f_003200(i).a);
            D_1dd6b0.f_005d4c(D_240768);
        }
    }
    Pair p = D_1dd6b0.f_0031dc(0);
    char *n = p.a;
    if (n) {
        char *c = D_1dd6b0.f_0031dc(0).a;
        char *f = D_240740.f_0368e8("Class", c, 0, 0);
        memcpy(D_24063c, f, D_1a211c[1]);
        sprintf(D_240768, "C%d", D_24063c[0]);
        D_1dd6b0.f_005d4c(D_240768);
    }
}

/* @implements 0x036f84 us f_036f84
   WHAT IT DOES: Shows the scenes of the computer cars. */
void f_036f84(void)
{
    for (int i = 0; i < 14; i++) {
        Pair p = D_1dd6b0.f_0031dc(i);
        char *n = p.a;
        if (n) {
            sprintf(D_240768, "%s_S", D_1dd6b0.f_0031dc(i).a);
            D_1dd6b0.f_005d4c(D_240768);
        }
    }
}

/* @implements 0x03702c us f_03702c
   WHAT IT DOES: Shows the scenes of the computer cars, each twice. */
void f_03702c(void)
{
    for (int i = 0; i < 14; i++) {
        Pair p = D_1dd6b0.f_0031dc(i);
        char *n = p.a;
        if (n) {
            sprintf(D_240768, "%s_S", D_1dd6b0.f_0031dc(i).a);
            D_1dd6b0.f_005d4c(D_240768);
            sprintf(D_240768, "%s_S", D_1dd6b0.f_0031dc(i).a);
            D_1dd6b0.f_005d4c(D_240768);
        }
    }
}

/* @draft 0x037108 us f_037108
   WHAT IT DOES: Loads the textures of the two player cars' free scenes, then those of the
   computer cars by their row in the car database; stops the game when a texture file is not
   valid.
   Remaining difference (4 words): in the second loop retail stores the settings pair to its
   two stack copies in the first loop's order (high words, then the low word of the copy, the
   variable's low word in the branch slot); here the two copies come out the other way. */
void f_037108(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        Pair p = GetM(i);
        if (p.a) {
            sprintf(D_240768, "%s_M_Free", p.a);
            if (!f_022de4(1, D_1dd6b0.f_005a38(D_240768)->f_002acc("Tex"), 0)) {
                f_00d354(D_245178, 1, "Error(RCOViewerInit) : This RTS File is not RTS file.\n");
                abort();
            }
        }
    }
    for (i = 0; i < 14; i++) {
        Pair p = GetS(i);
        if (p.a) {
            sprintf(D_240768, "Tex%d",
                    D_240740.f_036a3c(p.a, (int *)D_240740.rowName, D_240740.rows));
            if (!f_022de4(1, D_1dd6b0.f_005c34(D_240768), 0)) {
                f_00d354(D_245178, 1, "Error(RCOViewerInit) : This RTS File is not RTS file.\n");
                abort();
            }
        }
    }
}

/* @implements 0x037294 us f_037294
   WHAT IT DOES: Loads the textures of the computer cars' scenes; stops the game when a
   texture file is not valid. */
void f_037294(void)
{
    for (int i = 0; i < 14; i++) {
        Pair p = GetS(i);
        char *n = D_1dd6b0.f_0031dc(i).a;
        if (n) {
            sprintf(D_240768, "%s_S", p.a);
            if (!f_022de4(1, D_1dd6b0.f_005a38(D_240768)->f_002acc("Tex"), 0)) {
                f_00d354(D_245178, 1, "Error(RCOViewerInit) : This RTS File is not RTS file.\n");
                abort();
            }
        }
    }
}

/* @implements 0x03738c us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the car database (empty); at exit, destroys it. */

/* @implements 0x037408 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x037428 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
