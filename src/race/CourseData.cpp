/* The course data object file (retail 0x037448 to 0x037abc). It shows and frees the course's
   scene ("Course<name>" and "Course<name>_Free"), loads the free texture area and hands every
   part of the course scene to the map manager, and finds the replay and computer car line
   data. It also holds the course database. */

#include <stdio.h>
#include <string.h>

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
    CPackage *f_005a38(const char *name);
    void f_005d4c(const char *name);
};
extern CSequence D_1dd6b0;

/* A stream's settings, found by name. */
struct BgmEntry {
    const char *name;
    int m4[2];
    int arg;
    int m16[2];
};
extern BgmEntry D_1c0614[];
extern "C" int f_00222c(const char *name, const char *package);

/* The course collision areas of the map manager. */
struct CourseAreas {
    void f_0e1eec(void *road, int roadArg, void *danmen, void *runOff, int runOffArg,
                  void *roadPoly, void *runOffPoly);
};

/* The map manager. */
struct MapMgr {
    void f_028f80(void *pack, int area);
    void f_029040(void *model, void *texMem, void *mapClip, void *event, void *envC,
                  void *envD, void *motion, void *roadArea, void *danmen, void *runOffArea,
                  void *runOffPoly, void *roadPoly, void *wallHit, void *lightPoint,
                  void *shadePoly, int reverse);
    CourseAreas *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas m12240;
};
extern MapMgr D_23c820;

/* The wall hit data. */
struct WallHit {
    void f_0c5938(void *data);
    int m0[8];
    int m32;
    int m36[128];
};
extern WallHit D_246700;

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
extern const int D_1a211c[7];

/* The course database. */
DB::CDataBase D_2407a8;

/* @implements 0x037448 us f_037448
   WHAT IT DOES: Shows the course's free scene. */
void f_037448(void)
{
    char name[256];
    Pair p = D_1dd6b0.f_0031c0();
    sprintf(name, "Course%s_Free", (char *)p.a);
    D_1dd6b0.f_005d4c(name);
}

/* @implements 0x03749c us f_03749c
   WHAT IT DOES: Shows the course's scene. */
void f_03749c(void)
{
    char name[256];
    Pair p = D_1dd6b0.f_0031c0();
    sprintf(name, "Course%s", (char *)p.a);
    D_1dd6b0.f_005d4c(name);
}

/* @implements 0x0374f0 us f_0374f0
   WHAT IT DOES: Loads the free scene's textures into the map manager's free texture area. */
void f_0374f0(void)
{
    char name[256];
    Pair p = D_1dd6b0.f_0031c0();
    sprintf(name, "Course%s_Free", (char *)p.a);
    D_23c820.f_028f80(D_1dd6b0.f_005a38(name)->f_002acc("TexVram"), 1);
}

/* @draft 0x037568 us f_037568
   WHAT IT DOES: Loads the course: sets up the collision areas from the scene's road, run off
   and cross section data, the wall hits (with no wall touched yet), and hands the model,
   textures, clip, event, environment, motion, light and shade data to the map manager with
   the course's reverse flag from the course database.
   Remaining difference: the address of D_24063c is kept in a saved register across the
   database lookup (retail keeps only its high half), which costs one register, so the wall
   hit data is spilled to the stack instead of the model and texture memory data, and the
   size D_1a211c[1] is loaded through an address register rather than as D_1a2120 directly. */
void f_037568(void)
{
    char name[256];
    {
        Pair p = D_1dd6b0.f_0031c0();
        sprintf(name, "Course%s", (char *)p.a);
    }
    int i = f_00222c("RoadArea", name);
    int roadArg = D_1c0614[i].arg;
    i = f_00222c("RunOffArea", name);
    int runOffArg = D_1c0614[i].arg;
    void *roadArea = D_1dd6b0.f_005a38(name)->f_002acc("RoadArea");
    void *danmen = D_1dd6b0.f_005a38(name)->f_002acc("Danmen");
    void *runOffArea = D_1dd6b0.f_005a38(name)->f_002acc("RunOffArea");
    void *roadPoly = D_1dd6b0.f_005a38(name)->f_002acc("RoadPoly");
    void *runOffPoly = D_1dd6b0.f_005a38(name)->f_002acc("RunOffPoly");
    void *wallHit = D_1dd6b0.f_005a38(name)->f_002acc("WallHit");
    D_23c820.Areas()->f_0e1eec(roadArea, roadArg, danmen, runOffArea, runOffArg, roadPoly,
                             runOffPoly);
    D_246700.f_0c5938(wallHit);
    D_246700.m32 = 0;
    for (int i = 0; i < 128; i++)
        D_246700.m36[i] = -1;
    void *model = D_1dd6b0.f_005a38(name)->f_002acc("Model");
    void *texMem = D_1dd6b0.f_005a38(name)->f_002acc("TexMem");
    void *mapClip = D_1dd6b0.f_005a38(name)->f_002acc("MapClip");
    void *event = D_1dd6b0.f_005a38(name)->f_002acc("Event");
    void *envC = D_1dd6b0.f_005a38(name)->f_002acc("MapEnvC");
    void *envD = D_1dd6b0.f_005a38(name)->f_002acc("MapEnvD");
    void *motion = D_1dd6b0.f_005a38(name)->f_002acc("Motion");
    void *lightPoint = D_1dd6b0.f_005a38(name)->f_002acc("LightPoint");
    void *shadePoly = D_1dd6b0.f_005a38(name)->f_002acc("ShadePoly");
    {
        Pair p = D_1dd6b0.f_0031c0();
        memcpy(D_24063c, D_2407a8.f_0368e8("IsReverse", (char *)p.a, 0, 0), D_1a211c[1]);
    }
    D_23c820.f_029040(model, texMem, mapClip, event, envC, envD, motion, roadArea, danmen,
                      runOffArea, runOffPoly, roadPoly, wallHit, lightPoint, shadePoly,
                      D_24063c[0]);
}

/* @implements 0x037938 us f_037938
   WHAT IT DOES: Returns the course scene's replay data. */
void *f_037938(void)
{
    char name[256];
    Pair p = D_1dd6b0.f_0031c0();
    sprintf(name, "Course%s", (char *)p.a);
    return D_1dd6b0.f_005a38(name)->f_002acc("Replay");
}

/* @implements 0x03799c us f_03799c
   WHAT IT DOES: Returns the course scene's computer car line data. */
void *f_03799c(void)
{
    char name[256];
    Pair p = D_1dd6b0.f_0031c0();
    sprintf(name, "Course%s", (char *)p.a);
    return D_1dd6b0.f_005a38(name)->f_002acc("ComCarLine");
}

/* @implements 0x037a00 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the course database (empty); at exit, destroys it. */

/* @implements 0x037a7c us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x037a9c us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
