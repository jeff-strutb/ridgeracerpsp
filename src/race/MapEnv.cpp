/* The map environment (retail 0x0d7ee4 to 0x0da414): Map::CExcelData, a table exported from a
   spreadsheet (a header with the row count and column offsets, the data, and the column
   names, each after a one-letter type), and Map::CMapEnv, the course's lighting and fog keyed
   by course distance, loaded from the race database and interpolated each frame. */

#include <string.h>

extern "C" {
void f_02db7c(void *p);
int f_00d354(char *buf, int n, const char *fmt, ...);
int f_126f1c(const char *fmt, ...);
}

/* The size of a cell of each column type (the game database's table). */
extern const int D_1a211c[];

/* The value of the last cell read from the game database (copied, as cells are not aligned). */
union Cell {
    unsigned char b;
    float f;
    int i;
};
extern Cell D_24063c;

/* The log line buffer. */
extern char D_245178[];
extern char D_245177[];
extern char D_245176[];
extern char D_245175[];
extern char D_245174[];

/* A vector of four floats. */
struct Vec4 {
    float x, y, z, w;
};
Vec4 *f_027f18(Vec4 *d, const Vec4 *a);

namespace DB {
/* The game database (see src/system/DataBase.cpp); here the stack tables read by the loader. */
class CDataBase {
public:
    CDataBase() { Clear(); }
    virtual ~CDataBase() {}
    virtual int f_03680c(void *data);
    virtual int f_0368d8();
    virtual int f_0368e0();
    virtual char *Data() { return (char *)m36; }
    virtual void Clear();
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
    int f_036a3c(const char *name, int names, int n);

    int cols;
    int rows;
    int type;
    int offset;
    int colName;
    int rowName;
    int m28;
    int m32;
    int m36;
};
}

namespace Map {

/* The exported table's header: the row count, then from +16 the column offsets. */
struct ExcelHeader {
    int count;
    int m4[3];
    int offs[1];
};

/* The exported file's header: offsets of the data and of the names. */
struct ExcelFile {
    int m0;
    int data;
    int names;
};

class CExcelData {
public:
    CExcelData();
    virtual ~CExcelData();
    void Set(ExcelFile *f);
    char *Name(int i);
    char *Column(int i);
    int Type(const char *name);
    int Find(const char *name);
    char *Get(const char *name);
    char *At(int i);
    void Init();

    ExcelHeader *head;
    char *data;
    char *names;
};

/* @implements 0x0d7ee4 us _ZN3Map10CExcelDataC2Ev
   WHAT IT DOES: Base object constructor: sets the vtable. */
/* @implements 0x0d7ef4 us _ZN3Map10CExcelDataC1Ev
   WHAT IT DOES: Complete object constructor: the same. */
CExcelData::CExcelData()
{
}

/* @implements 0x0d7f04 us _ZN3Map10CExcelDataD2Ev
   WHAT IT DOES: Base object destructor: nothing to free. */
/* @implements 0x0d7f14 us _ZN3Map10CExcelDataD1Ev
   WHAT IT DOES: Complete object destructor: the same. */
/* @implements 0x0d7f24 us _ZN3Map10CExcelDataD0Ev
   WHAT IT DOES: Deleting destructor. */
CExcelData::~CExcelData()
{
}

/* @implements 0x0d7f4c us _ZN3Map10CExcelData3Set
   WHAT IT DOES: Takes an exported file: the header is the file itself, the data and the
   names are at the offsets it gives. */
void CExcelData::Set(ExcelFile *f)
{
    head = (ExcelHeader *)f;
    data = (char *)(f->data + (int)f);
    names = (char *)(f->names + (int)f);
    Init();
}

/* @implements 0x0d7f84 us _ZN3Map10CExcelData4Name
   WHAT IT DOES: The i-th of the strings in the names area (0 when there are fewer). */
char *CExcelData::Name(int i)
{
    char *p = names;
    for (int k = 0; k < head->count; k++) {
        if (k == i)
            return p;
        while (*p)
            p++;
        p++;
    }
    return 0;
}

/* @implements 0x0d7fdc us _ZN3Map10CExcelData6Column
   WHAT IT DOES: The data of column i. */
char *CExcelData::Column(int i)
{
    int *o = &head->offs[i];
    return data + *o;
}

/* @implements 0x0d7ff8 us _ZN3Map10CExcelData4Type
   WHAT IT DOES: A column's type from its type letter: 0 integer, 1 float, -1 unknown. */
int CExcelData::Type(const char *name)
{
    if (name[0] == 'i')
        return 0;
    if (name[0] == 'f')
        return 1;
    return -1;
}

/* @draft 0x0d8020 us _ZN3Map10CExcelData4Find
   WHAT IT DOES: The index of the column with the given name (after its type letter), or
   -1.
   DIFFERS: one word: the skip loop's first load is addressed as 1(s1) (the entry plus one)
   where retail uses 0(s0). The skip loop is a goto loop: retail's is not rotated.
   Tried (2026-11-16): moving the first load after the label (c = *q; q++; if (c) goto next)
   lets loop.c rotate the loop (22 words); the load must stay before the label. */
int CExcelData::Find(const char *name)
{
    char *p = names;
    for (int i = 0; i < head->count; i++) {
        char *q = p + 1;
        if (strcmp(name, q) == 0)
            return i;
        if (*p) {
            char c = *q;
        next:
            q++;
            if (c) {
                c = *q;
                goto next;
            }
        }
        p = q;
    }
    return -1;
}

/* @implements 0x0d80d0 us _ZN3Map10CExcelData3Get
   WHAT IT DOES: The data of the column with the given name, or 0. */
char *CExcelData::Get(const char *name)
{
    int i = Find(name);
    if (i < 0)
        return 0;
    return Column(i);
}

/* @implements 0x0d8114 us _ZN3Map10CExcelData2At
   WHAT IT DOES: The data of column i. */
char *CExcelData::At(int i)
{
    return Column(i);
}

/* @implements 0x0d8130 us _ZN3Map10CExcelData4Init
   WHAT IT DOES: Nothing. */
void CExcelData::Init()
{
}

/* A light key: its course distance, the fog's two distance pairs, the light colour and its
   strength, and the ambient level. */
struct LightKey {
    float key;
    float fog[4];
    unsigned char r, g, b, a;
    unsigned char ambient;
};

/* A fog key: a course distance and a value. */
struct FogKey {
    float key;
    float value;
};

/* The fog: two (distance, level) pairs and the graphics engine commands built from them. */
struct Fog {
    float d0, d1;
    float l0, l1;
    unsigned int cmdEnd;
    unsigned int cmdDist;
    unsigned int cmdColor;
    float start;
    float end;
};

/* A float's bits. */
static inline unsigned int Bits(float f)
{
    union {
        float f;
        unsigned int u;
    } b;
    b.f = f;
    return b.u;
}

class CMapEnv {
public:
    CMapEnv();
    virtual ~CMapEnv();
    void SetModel(void *m);
    void Free();
    void Load(void *course, void *light, int flip, int total);
    void MakeFog(Fog *f, float *col);
    void Update(float t, float wrap);
    float FogAt(float t, float wrap);

    char m4[12];
    float mAmb[3];
    float m28;
    float cAmb[3];
    float m44;
    Vec4 diffDir;
    Vec4 shadowDir;
    float mDiff[3];
    float m92;
    float cDiff[3];
    float m108;
    float mSpec[3];
    float m124;
    float cSpec[3];
    float m140;
    float mSpecP, cSpecP;
    float m152[2];
    float dEnv[3];
    float m172;
    float light[8];
    Fog fog;
    Fog bfog;
    float cull;
    float m284;
    float sdw[4];
    float ambShade;
    unsigned int ambient;
    int smoke[3];
    char m324[12];
    float key[3];
    float m348;
    int m352;
    float m356;
    float sdwMin, sdwMax, specMin, specMax;
    void *model;
    int cls;
    float tireRot;
    float fovY;
    char m392[8];
    Vec4 sun;
    unsigned char sunType, sunR, sunG, sunB, sunA;
    int sunW, sunH;
    unsigned char glareLoop, glareMul, glareThr;
    LightKey *keys;
    int nKeys;
    FogKey *fogKeys;
    int nFogKeys;
    float last;
};

/* @implements 0x0d8138 us _ZN3Map7CMapEnvC2Ev
   WHAT IT DOES: Base object constructor: no tables yet. */
/* @implements 0x0d8150 us _ZN3Map7CMapEnvC1Ev
   WHAT IT DOES: Complete object constructor: the same. */
CMapEnv::CMapEnv()
{
    keys = 0;
    fogKeys = 0;
}

/* @implements 0x0d8168 us _ZN3Map7CMapEnvD2Ev
   WHAT IT DOES: Base object destructor: frees the tables. */
/* @implements 0x0d8190 us _ZN3Map7CMapEnvD1Ev
   WHAT IT DOES: Complete object destructor: the same. */
/* @implements 0x0d81b8 us _ZN3Map7CMapEnvD0Ev
   WHAT IT DOES: Deleting destructor. */
CMapEnv::~CMapEnv()
{
    Free();
}

/* @implements 0x0d81f0 us _ZN3Map7CMapEnv8SetModel
   WHAT IT DOES: Keeps the course model and passes it on to 0x02db7c. */
void CMapEnv::SetModel(void *m)
{
    model = m;
    f_02db7c(m);
}

/* @implements 0x0d8210 us _ZN3Map7CMapEnv4Free
   WHAT IT DOES: Frees the fog and light tables. */
void CMapEnv::Free()
{
    if (keys)
        delete[] keys;
    keys = 0;
    if (fogKeys)
        delete[] fogKeys;
    fogKeys = 0;
}

/* Reads one cell of a table row: copies it to the read buffer and gives it as a byte, a float
   or a word. The size argument is a local that caches the cell size (loaded at its first use
   in a stretch of reads, as "(bs = D_1a211c[1])", then reused). */
#define RDX(db, sz, name, row, T) \
    ({ memcpy(&D_24063c, (db).f_0368e8(name, row, 0, 0), sz); D_24063c.T; })
#define RDB(sz, name) RDX(db1, sz, name, "Course", b)
#define RDF(sz, name) RDX(db1, sz, name, "Course", f)
#define RDI(sz, name) RDX(db1, sz, name, "Course", i)
#define RDX2(db, sz, name, T) \
    ({ memcpy(&D_24063c, (db).f_0368e8(name, 0, 0, i), sz); D_24063c.T; })
#define RDX3(db, name, T) \
    ({ memcpy(&D_24063c, (db).f_0368e8(name, 0, 0, row), D_1a211c[4]); D_24063c.T; })
#define SB(v) ((v) = D_1a211c[1])
#define SI(v) ((v) = D_1a211c[3])
#define SF(v) ((v) = D_1a211c[4])

/* @draft 0x0d8270 us _ZN3Map7CMapEnv4Load
   DRAFT: complete transcription; the same instructions as retail up to register choice and
   some spill slots (7,436 of 7,452 bytes).
   WHAT IT DOES: Loads the course's lighting from two game database tables (the course table,
   whose "Course" row holds the settings, and the light table, one row per key). In the light
   table column RZP is the course distance; a negative value ends a section: first the light
   keys, then the fog keys. Both are counted, allocated and read (reversed along the lap when
   flip is set: the distance becomes total - distance - 1): per light key the fog distances
   and levels, the colour, and the road reference (when the table has that column); per fog
   key the distance and one level. The course row then gives the back mirror's fog (a default
   and a warning when absent) and its colour, the map and car ambient, diffuse and specular
   colours (bytes scaled by a strength), the diffuse and shadow directions (normalised), the
   cull range, shadow and smoke colours, the key light (defaults when absent), dither (passed
   to SetModel), class, the sun (type, direction, colour, size), glare, ambient shade and the
   car's tyre rotation and field of view (defaults when absent). It ends by updating the
   lighting for course distance 0 and logging each step.
   DIFFERS: register allocation and spill slots. Retail keeps the read buffer's address in a
   saved register through each stretch of reads and spills the four light key field addresses
   (frame 192); here the frame is 176 and the key loop gives that register to a field address.
   Also tried: the cell size is read once per stretch into a local ("(bs = D_1a211c[1])", as
   array elements are never CSE'd across calls by this compiler, retail's are); the log
   buffer is named through five aliases (D_245177+1, D_245176+2...) because one address makes
   the global const-prop share its high half in a saved register for the whole function,
   which retail does not (retail's later log calls rebuild it); that costs the key loop its
   register.
   Diagnosed 2026-11-02 (-da dumps): in the two counting loops retail loads D_24063c's high
   half once per loop (lui s0 / lui s2 in each pre-header, loop.c's movable), while here
   GCSE's PRE turns every D_24063c high half into one reaching register (set in five
   pre-headers, live across 176 calls) that global-alloc spills, so each use gets its own lui.
   -fno-gcse is ruled out: it breaks Update and FogAt. */
void CMapEnv::Load(void *course, void *lightDb, int flip, int total)
{
    DB::CDataBase db1;
    DB::CDataBase db2;
    f_00d354(D_245178, 1024, "MapEnv Init\n");
    db1.f_03680c(course);
    db2.f_03680c(lightDb);
    f_00d354(D_245178, 1024, "MapEnv Init Num DynamicParam : %d\n", db2.rows);
    int i = 0;
    nKeys = 0;
    nFogKeys = 0;
    for (; i < db2.rows; i++) {
        memcpy(&D_24063c, db2.f_0368e8("RZP", 0, 0, i), D_1a211c[4]);
        if (D_24063c.f < 0.0f)
            break;
        nKeys++;
    }
    i++;
    for (; i < db2.rows; i++) {
        memcpy(&D_24063c, db2.f_0368e8("RZP", 0, 0, i), D_1a211c[4]);
        if (D_24063c.f < 0.0f)
            break;
        nFogKeys++;
    }
    f_00d354(D_245177+1, 1024, "NumDynamicParam : %d , %d\n", nKeys, nFogKeys);
    keys = new LightKey[nKeys];
    fogKeys = new FogKey[nFogKeys];
    for (i = 0; i < nKeys; i++) {
        int j;
        int fs, bs;
        if (flip) {
            j = nKeys - i - 1;
            keys[j].key = ((float)total - RDX(db2, D_1a211c[4], "RZP", 0, f)) - 1.0f;
        } else {
            j = i;
            keys[i].key = RDX(db2, D_1a211c[4], "RZP", 0, f);
        }
        keys[j].fog[0] = RDX2(db2, SF(fs), "Near", f) * 1000.0f;
        keys[j].fog[1] = RDX2(db2, fs, "Far", f) * 1000.0f;
        keys[j].fog[2] = RDX2(db2, fs, "Max", f);
        keys[j].fog[3] = RDX2(db2, fs, "Min", f);
        keys[j].r = RDX2(db2, SB(bs), "FogR", b);
        keys[j].g = RDX2(db2, bs, "FogG", b);
        keys[j].b = RDX2(db2, bs, "FogB", b);
        keys[j].a = RDX2(db2, bs, "FogA", b);
        if (db2.f_036a3c("RoadRef", db2.colName, db2.cols) != -1)
            keys[j].ambient = RDX2(db2, bs, "RoadRef", b);
    }
    for (i = 0; i < nFogKeys; i++) {
        int j;
        int row = nKeys + i + 1;
        if (flip) {
            j = nFogKeys - i - 1;
            fogKeys[j].key = ((float)total - RDX3(db2, "RZP", f)) - 1.0f;
        } else {
            j = i;
            fogKeys[i].key = RDX3(db2, "RZP", f);
        }
        fogKeys[j].value = RDX3(db2, "Near", f);
    }
    f_00d354(D_245176+2, 1024, "MapEnv Init  pass1\n");
    int fs, bs, ws;
    if (db1.f_036a3c("BFogNear", db1.colName, db1.cols) == -1) {
        bfog.d0 = 200000.0f;
        light[6] = 0.5f;
        bfog.d1 = 1000000.0f;
        bfog.l0 = 0.0f;
        bfog.l1 = 255.0f;
        light[4] = 0.5f;
        light[5] = 0.5f;
        f_126f1c("Warnning!! BackMirror Fog Prameter undefined");
    } else {
        bfog.d0 = RDF(SF(fs), "BFogNear") * 1000.0f;
        bfog.d1 = RDF(fs, "BFogFar") * 1000.0f;
        bfog.l1 = RDF(fs, "BFogMax");
        bfog.l0 = RDF(fs, "BFogMin");
        float a = (float)RDB(SB(bs), "BFogA") / 255.9f;
        light[4] = (float)RDB(bs, "BFogR") / 255.9f * a;
        light[5] = (float)RDB(bs, "BFogG") / 255.9f * a;
        light[6] = (float)RDB(bs, "BFogB") / 255.9f * a;
    }
    MakeFog(&bfog, &light[4]);
    {
        float a = (float)RDB(SB(bs), "MAmbA") / 255.9f;
        mAmb[0] = (float)RDB(bs, "MAmbR") / 255.9f * a;
        mAmb[1] = (float)RDB(bs, "MAmbG") / 255.9f * a;
        mAmb[2] = (float)RDB(bs, "MAmbB") / 255.9f * a;
        a = (float)RDB(bs, "CAmbA") / 255.9f;
        cAmb[0] = (float)RDB(bs, "CAmbR") / 255.9f * a;
        cAmb[1] = (float)RDB(bs, "CAmbG") / 255.9f * a;
        cAmb[2] = (float)RDB(bs, "CAmbB") / 255.9f * a;
        a = (float)RDB(bs, "MDiffA") / 255.9f;
        mDiff[0] = (float)RDB(bs, "MDiffR") / 255.9f * a;
        mDiff[1] = (float)RDB(bs, "MDiffG") / 255.9f * a;
        mDiff[2] = (float)RDB(bs, "MDiffB") / 255.9f * a;
        a = (float)RDB(bs, "CDiffA") / 255.9f;
        cDiff[0] = (float)RDB(bs, "CDiffR") / 255.9f * a;
        cDiff[1] = (float)RDB(bs, "CDiffG") / 255.9f * a;
        cDiff[2] = (float)RDB(bs, "CDiffB") / 255.9f * a;
        a = (float)RDB(bs, "MSpeA") / 255.9f;
        mSpec[0] = (float)RDB(bs, "MSpeR") / 255.9f * a;
        mSpec[1] = (float)RDB(bs, "MSpeG") / 255.9f * a;
        mSpec[2] = (float)RDB(bs, "MSpeB") / 255.9f * a;
        a = (float)RDB(bs, "CSpeA") / 255.9f;
        cSpec[0] = (float)RDB(bs, "CSpeR") / 255.9f * a;
        cSpec[1] = (float)RDB(bs, "CSpeG") / 255.9f * a;
        cSpec[2] = (float)RDB(bs, "CSpeB") / 255.9f * a;
    }
    mSpecP = RDF(SF(fs), "MSpeP");
    cSpecP = RDF(fs, "CSpeP");
    {
        float a = (float)RDB(bs, "DEnvA") / 255.9f;
        dEnv[0] = (float)RDB(bs, "DEnvR") / 255.9f * a;
        dEnv[1] = (float)RDB(bs, "DEnvG") / 255.9f * a;
        dEnv[2] = (float)RDB(bs, "DEnvB") / 255.9f * a;
    }
    diffDir.x = RDF(fs, "DiffX");
    diffDir.y = RDF(fs, "DiffY");
    diffDir.z = RDF(fs, "DiffZ");
    f_027f18(&diffDir, &diffDir);
    cull = RDF(fs, "CullRange") * 1000.0f;
    shadowDir.x = RDF(fs, "SdwX");
    shadowDir.y = RDF(fs, "SdwY");
    shadowDir.z = RDF(fs, "SdwZ");
    f_027f18(&shadowDir, &shadowDir);
    sdw[0] = (float)RDB(bs, "SdwR") / 255.9f;
    sdw[1] = (float)RDB(bs, "SdwG") / 255.9f;
    sdw[2] = (float)RDB(bs, "SdwB") / 255.9f;
    sdw[3] = (float)RDB(bs, "SdwA") / 255.9f;
    {
        float a = (float)RDB(bs, "SmokeA") / 255.9f;
        smoke[0] = (int)((float)RDB(bs, "SmokeR") * a);
        smoke[1] = (int)((float)RDB(bs, "SmokeG") * a);
        smoke[2] = (int)((float)RDB(bs, "SmokeB") * a);
    }
    if (db1.f_036a3c("KeyR", db1.colName, db1.cols) == -1) {
        key[0] = 0.0f;
        key[1] = 0.0f;
        key[2] = 1.0f;
        m352 = 0;
        m356 = 1.0f;
        sdwMin = 0.3f;
        sdwMax = 0.5f;
        specMin = -0.2f;
        specMax = 0.7f;
    } else {
        key[0] = RDF(fs, "KeyR");
        key[1] = RDF(fs, "KeyG");
        key[2] = RDF(fs, "KeyB");
        m352 = 0;
        m356 = 1.0f;
        sdwMin = RDF(fs, "SdwMin");
        sdwMax = RDF(fs, "SdwMax");
        specMin = RDF(fs, "SpecMin");
        specMax = RDF(fs, "SpecMax");
    }
    int dither = 0;
    if (db1.f_036a3c("Dither", db1.colName, db1.cols) != -1)
        dither = RDB(D_1a211c[1], "Dither");
    SetModel((void *)dither);
    int c = db1.f_036a3c("Class", db1.colName, db1.cols);
    if (c != -1)
        c = RDB(D_1a211c[1], "Class");
    cls = c;
    sunType = RDB(SB(bs), "SunS_Type");
    sun.x = RDF(SF(fs), "SunS_X");
    sun.y = RDF(fs, "SunS_Y");
    sun.z = RDF(fs, "SunS_Z");
    f_027f18(&sun, &sun);
    sunR = RDB(bs, "SunS_R");
    sunG = RDB(bs, "SunS_G");
    sunB = RDB(bs, "SunS_B");
    sunA = RDB(bs, "SunS_A");
    sunW = RDI(SI(ws), "SunS_W");
    sunH = RDI(ws, "SunS_H");
    glareLoop = RDB(bs, "Glare_Loop");
    glareMul = RDB(bs, "Glare_Baisuu");
    glareThr = RDB(bs, "Glare_Shikiichi");
    ambShade = (float)RDB(bs, "AmbShade") / 255.9f;
    if (db1.f_036a3c("CarGetFovY", db1.colName, db1.cols) == -1) {
        tireRot = 0.0f;
        fovY = 30.0f;
    } else {
        tireRot = RDF(fs, "CarGetTireRot");
        fovY = RDF(fs, "CarGetFovY");
    }
    f_00d354(D_245175+3, 1024, "MapEnv Init pass2\n");
    last = -1.0f;
    Update(0.0f, 10000.0f);
    f_00d354(D_245174+4, 1024, "MapEnv Init Done\n");
}

/* @draft 0x0d9f8c us _ZN3Map7CMapEnv7MakeFog
   WHAT IT DOES: Builds the fog commands: the line through the two (distance, level) pairs
   gives the distances where the level is 0 and 255; the end, the reciprocal span and the
   colour (from 0..1 components) become graphics engine commands.
   DIFFERS: FP register choice (retail: slope in f5, first distance in f3, zero in f6) and
   the order of the two distance stores; 50 statement orders tried. */
void CMapEnv::MakeFog(Fog *f, float *col)
{
    float full = 255.0f;
    float d = f->d1 - f->d0;
    if (d == 0.0f)
        d = 1e-06f;
    float k = (f->l1 - f->l0) / d;
    if (k == 0.0f)
        k = 1e-06f;
    float b = f->l0 - k * f->d0;
    f->end = (full - b) / k;
    f->start = (0.0f - b) / k;
    unsigned int end = (Bits(f->end) >> 8) | 0xcd000000;
    float span = f->end - f->start;
    f->cmdColor = (int)(col[0] * full) | ((int)(col[1] * full) << 8) | ((int)(col[2] * full) << 16) | 0xcf000000;
    if (span == 0.0f)
        span = 1e-06f;
    f->cmdEnd = end;
    f->cmdDist = (Bits(1.0f / span) >> 8) | 0xce000000;
}

/* @implements 0x0da098 us _ZN3Map7CMapEnv6Update
   WHAT IT DOES: For a course distance (wrapping at the lap length) finds the light keys
   around it and blends them: the fog pairs, the light colour scaled by its strength, and
   the ambient level; then rebuilds the fog commands. Nothing when the distance is
   unchanged. */
void CMapEnv::Update(float t, float wrap)
{
    if (t == last)
        return;
    int n = nKeys;
    LightKey *cur = keys;
    last = t;
    LightKey *next = &keys[1 % n];
    for (int i = 0; i < n; i++) {
        LightKey *e = (LightKey *)(i * sizeof(LightKey) + (int)keys);
        if (t < e->key)
            break;
        cur = e;
        next = &keys[(i + 1) % n];
    }
    float b = next->key;
    float a = cur->key;
    if (b < a) {
        b += wrap;
        if (t < a)
            t += wrap;
    }
    float d = b - a;
    float r;
    if (t < a)
        r = 0.0f;
    else if (d == 0.0f)
        r = 0.0f;
    else
        r = (t - a) / d;
    float s = 1.0f - r;
    fog.d0 = s * cur->fog[0] + r * next->fog[0];
    fog.d1 = s * cur->fog[1] + r * next->fog[1];
    fog.l1 = s * cur->fog[2] + r * next->fog[2];
    fog.l0 = s * cur->fog[3] + r * next->fog[3];
    float k = (s * (float)cur->a + r * (float)next->a) / 255.9f / 255.9f;
    light[0] = (s * (float)cur->r + r * (float)next->r) * k;
    light[1] = (s * (float)cur->g + r * (float)next->g) * k;
    light[2] = (s * (float)cur->b + r * (float)next->b) * k;
    int v = (int)(s * (float)cur->ambient + r * (float)next->ambient);
    ambient = v | (v << 8) | (v << 16);
    MakeFog(&fog, light);
}

/* @implements 0x0da324 us _ZN3Map7CMapEnv5FogAt
   WHAT IT DOES: The fog key value at a course distance, blended between the keys around
   it; 0 without keys. */
float CMapEnv::FogAt(float t, float wrap)
{
    int n = nFogKeys;
    if (n == 0)
        return 0.0f;
    FogKey *cur = fogKeys;
    FogKey *next = &fogKeys[1];
    for (int i = 0; i < n; i++) {
        FogKey *e = (FogKey *)(i * sizeof(FogKey) + (int)fogKeys);
        if (t < e->key)
            break;
        cur = e;
        next = &fogKeys[(i + 1) % n];
    }
    float b = next->key;
    float a = cur->key;
    if (b < a) {
        b += wrap;
        if (t < a)
            t += wrap;
    }
    float d = b - a;
    float r;
    if (t < a)
        r = 0.0f;
    else if (d == 0.0f)
        r = 0.0f;
    else
        r = (t - a) / d;
    return (1.0f - r) * cur->value + r * next->value;
}

}
