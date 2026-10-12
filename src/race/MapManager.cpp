/* The map manager object file (retail 0x028f80 to 0x0299b0). One global map manager owns
   everything a loaded course needs: three course parts (one per drawing mode), the course
   event data, the motion and map class packs, the shading setup and a further two course
   systems. Allocate loads a course from its packs, Delete frees it again, and two entry points
   per frame update and draw the course part for the current mode. */

#include <string.h>

extern "C" {
int f_126f1c(const char *fmt, ...);
int f_00d354(char *buf, int size, const char *fmt);
void f_0299b8(void *pack);
void f_0299f8(void *pack, void *data);
int f_029a44(void *pack);
int f_029a4c(void *pack, int i);
void *f_029a60(void *pack, int i);
void f_0d7154(void *data, int size, int area);
void f_0d71b8(void *data);
void f_0d71d4(void *data);
void f_0d711c(void *data, void *pack);
void f_0cb688(int id);
int f_02326c(int area);
void f_0d54d0(void *part);
void f_0d54e0(void *part);
void f_0d54e8(void *part, void *shade);
void f_0d5514(void *part, void *view, void *setup);
int f_0d5cbc(void *part, void *view, int mode, int arg, int flag);
void f_0d5d80(void *event, int arg, void *pack);
void f_0ce454(void *shade);
void f_0cf85c(void *shade);
void f_0cf7dc(int arg, int b);
void f_0cf884(void *shade, int b);
void f_0cf8a4(void *shade);
void f_0cf828(void);
void f_0cfaf4(void *view, void *shade, int mode);
void f_0cf8e4(int a, void *view, void *setup);
void f_0cf8c0(void *shade, int a, void *view, void *setup);
void f_0cf90c(void *shade, void *view);
void f_0cf934(void);
void f_0d8150(void *p);
void f_0d8190(void *p);
void f_0d8210(void *p);
void f_0d8270(void *p, int a, int b, int c, int d);
void f_0d7ef4(void *p);
void f_0d7f14(void *p);
void f_0d7f4c(void *p, int a);
void f_02b67c(void *p);
void f_02c960(void *view);
void f_02b7f0(void *view);

int f_02bdcc(void *part, void *view, int arg);
void f_02bbc0(void);
void f_02cec4(void *p, int a, int b);
}

extern char D_245178[];
extern char D_23ffc0[];

struct MainLoopJobView {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern MainLoopJobView *D_1d88a0;

/* The view being drawn: its camera matrix sits at +288. */
struct View {
    char m0[208];
    char m208[80];
    float m288[16];
    char m352[312];
    int m664;
};

/* One course part, set up from another object file. */
struct CoursePart {
    CoursePart() { f_0d54d0(this); }
    ~CoursePart() { f_0d54e0(this); }
    char m[4048];
};

struct EventRecord {
    int m0;
    int m4[15];
};

struct CourseEvents {
    CourseEvents() { m44 = -1; }
    int m0;
    EventRecord *m4;
    int m8[8];
    int m40;
    int m44;
};

/* The pack file reader (src/system/PackFile.cpp). */
struct Pack {
    Pack() { f_0299b8(this); }
    void *m0;
    const char *m4;
    void *m8;
    int m12;
    int m16;
};

struct Shade {
    Shade() { f_0ce454(this); f_0cf85c(this); }
    ~Shade() {}
    int m[13];
};

struct Motion {
    Motion() { f_0d8150(this); }
    ~Motion() { f_0d8190(this); }
    char m[464];
};

struct MapClass {
    MapClass() { f_0d7ef4(this); }
    ~MapClass() { f_0d7f14(this); }
    char m[16];
};

/* A direction: three floats and a padding word. */
struct Dir {
    float x, y, z;
    int w;
};
void f_02b81c(Dir *d);

class MapManager {
public:
    MapManager() { m_isValid = 0; m13020 = 0; }
    void AllocateFree(void *pack, int area);
    void Allocate(void *motionPack, void *classPack, int eventArg, int shadeArg, int motionA,
                  int motionB, int classArg, int a8, int a9, int a10, int a11, int a12, int a13,
                  int extra1, int extra0, int motionC);
    void Delete();
    void Update(int mode, View *view);
    int Draw(int mode, View *view, int arg);
    void f_029688();

    CoursePart m0[3];
    CourseEvents m12144;
    Pack m12192;
    Pack m12212;
    int m12232[2];
    int m12240[52];
    Shade m12448[1];
    int m12500[3];
    Motion m12512;
    MapClass m12976;
    int m12992;
    int m12996;
    char m_isValid;
    char m13001;
    int m13004;
    int m13008;
    int m13012;
    char m13016;
    int m13020;
};

extern CoursePart *D_254374;

/* @implements 0x028f80 us MapManager12AllocateFree
   WHAT IT DOES: Loads every texture of the given pack into the given texture area, and
   remembers that area so Delete can empty it. */
void MapManager::AllocateFree(void *data, int area)
{
    if (m_isValid)
        f_126f1c("MapManager::Allocate  m_isValid == 0  in AllocateFree");
    Pack pack;
    int i;
    f_0299f8(&pack, data);
    for (i = 0; i < f_029a44(&pack); i++)
        f_0d7154(f_029a60(&pack, i), f_029a4c(&pack, i), area);
    m13012 = area;
}

/* @draft 0x029040 us MapManager8AllocateE
   WHAT IT DOES: Loads a course: reads the motion and map class packs, sets up the motion and
   event systems, loads the textures of the map class pack, creates the motions, then brings up
   the map class, the three course parts, the event and shading systems, optionally a further
   system, and marks the manager valid. Progress is logged to a text buffer. */
void MapManager::Allocate(void *motionPack, void *classPack, int eventArg, int shadeArg,
                          int motionA, int motionB, int classArg, int a8, int a9, int a10,
                          int a11, int a12, int a13, int extra1, int extra0, int motionC)
{
    int i;

    if (m_isValid)
        f_126f1c("MapManager::Allocate  m_isValid == 0  in Allocate");
    f_0299f8(&m12192, motionPack);
    f_0299f8(&m12212, classPack);
    f_0d8270(&m12512, motionA, motionB, motionC, m12240[2]);
    f_0d5d80(&m12144, eventArg, &m12192);
    m12144.m40 = 0;
    m12144.m44 = motionC ? m12240[2] : -1;
    for (i = 0; i < f_029a44(&m12212); i++)
        f_0d7154(f_029a60(&m12212, i), f_029a4c(&m12212, i), -1);
    for (i = 0; i < f_029a44(&m12192); i++) {
        f_0cb688(m12144.m4[i].m0);
        f_0d711c(f_029a60(&m12192, i), &m12212);
    }
    f_00d354(D_245178, 1024, "Motion init\n");
    f_0d7f4c(&m12976, classArg);
    f_00d354(D_245178, 1024, "MapClass init\n");
    D_254374 = m0;
    f_0d54e8(&m0[0], m12448);
    f_0d54e8(&m0[1], 0);
    f_0d54e8(&m0[2], 0);
    f_00d354(D_245178, 1024, "Event init\n");
    f_0cf85c(m12448);
    f_0cf7dc(shadeArg, 0);
    f_0cf884(m12448, 0);
    f_00d354(D_245178, 1024, "Shade init\n");
    if (extra0 && extra1)
        f_02cec4(D_23ffc0, extra0, extra1);
    m13020 = 0x12dfc3e;
    m13016 = 1;
    m_isValid = 1;
    m12992 = 0;
    m12996 = 0;
    m13004 = 0;
    m13008 = 0;
    f_02bbc0();
    f_00d354(D_245178, 1024, "MapManager Allocate done\n");
}

/* @implements 0x0292fc us MapManager6Delete
   WHAT IT DOES: Frees the loaded course: releases the map class and motion entries, the
   motion system and the course textures, and shuts down the shading. */
void MapManager::Delete()
{
    int i;

    if (!m_isValid)
        f_126f1c("MapManager::Allocate  m_isValid == 1  in Delete");
    for (i = 0; i < f_029a44(&m12212); i++)
        f_0d71d4(f_029a60(&m12212, i));
    for (i = 0; i < f_029a44(&m12192); i++)
        f_0d71b8(f_029a60(&m12192, i));
    f_0d8210(&m12512);
    f_02326c(m13012);
    f_0cf8a4(m12448);
    f_0cf828();
    m_isValid = 0;
}

/* @implements 0x0293e4 us MapManager6Update
   WHAT IT DOES: Updates the course part for the given mode (0, 1 or 2) against the view. In
   mode 0 the shading is updated first, and refreshed when a refresh was requested. */
void MapManager::Update(int mode, View *view)
{
    MainLoopJobView *job = D_1d88a0;

    m13001 = job->m11 || job->m12;
    if (view->m664)
        m13016 = 1;
    switch (mode) {
    case 0:
        f_0cfaf4(view, m12448, 0);
        m12144.m40 = 0;
        f_0cf8e4(0, view, m12240);
        if (m13016) {
            m13016 = 0;
            f_0cf90c(m12448, view);
        }
        f_0cf8c0(m12448, 0, view, m12240);
        f_0d5514(&m0[0], view, m12240);
        break;
    case 1:
        m12144.m40 = 2;
        f_0d5514(&m0[1], view, m12240);
        break;
    case 2:
        m12144.m40 = 3;
        f_0d5514(&m0[2], view, m12240);
        break;
    }
}

/* @implements 0x029524 us MapManager4Draw
   WHAT IT DOES: Draws the course part for the given mode against the view and returns the
   updated draw state. Mode 2 draws with the view's forward direction; mode 4 draws course
   part 0 with the shading set for it. */
int MapManager::Draw(int mode, View *view, int arg)
{
    f_02b67c(view->m208);
    f_02c960(view);
    switch (mode) {
    case 0:
        f_0cfaf4(view, m12448, 0);
        arg = f_0d5cbc(&m0[0], view, 0, arg, 0);
        break;
    case 1:
        arg = f_0d5cbc(&m0[1], view, 1, arg, 0);
        break;
    case 2: {
        f_02b7f0(view);
        float *m = view->m288;
        Dir dir = { -m[2], -m[6], -m[10], 0 };
        f_02b81c(&dir);
        arg = f_02bdcc(&m0[2], view, arg);
        break;
    }
    case 4:
        f_0cfaf4(view, m12448, 4);
        arg = f_0d5cbc(&m0[0], view, 0, arg, 1);
        break;
    }
    return arg;
}

/* @implements 0x029688 us f_029688
   WHAT IT DOES: Requests a shading refresh and resets the frame counter. */
void MapManager::f_029688()
{
    m13016 = 1;
    m13004 = 0;
    f_0cf934();
}

MapManager D_23c820;

/* @implements 0x0296b0 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global map manager at start up and destroys it at exit. */
/* @implements 0x0297e4 us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
/* @implements 0x029804 us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */
/* @draft 0x029824 us _ZN10MapManagerC1Ev
   WHAT IT DOES: Constructs the map manager: the three course parts, the event data, two empty
   pack readers, the shading, motion and map class systems; nothing is loaded yet. */
