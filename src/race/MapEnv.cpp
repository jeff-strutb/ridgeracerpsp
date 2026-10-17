/* The map environment (retail 0x0d7ee4 to 0x0da414): Map::CExcelData, a table exported from a
   spreadsheet (a header with the row count and column offsets, the data, and the column
   names, each after a one-letter type), and Map::CMapEnv, the course's lighting and fog keyed
   by course distance, loaded from the race database and interpolated each frame. */

extern "C" {
int strcmp(const char *a, const char *b);
void f_02db7c(void *p);
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
   where retail uses 0(s0). The skip loop is a goto loop: retail's is not rotated. */
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
    void MakeFog(Fog *f, float *col);
    void Update(float t, float wrap);
    float FogAt(float t, float wrap);

    char m4[172];
    float light[8];
    Fog fog;
    char m244[64];
    unsigned int ambient;
    char m312[64];
    void *model;
    char m380[56];
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
