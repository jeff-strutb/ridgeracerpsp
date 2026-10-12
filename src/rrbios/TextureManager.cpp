/* The texture manager front end (retail 0x022c30 to 0x023340): carves video memory into a
   palette area and three texture areas, loads the textures of a texture file into an area
   (each one entered in the texture info store under its id, its pixels and palette copied to
   video memory and its GE command lists built), and drops them again by file, by id or by
   area. */

extern "C" {
void *sceGeEdramGetAddr(void);
}

/* The 32 byte header of one texture in a texture file. */
struct TexHeader {
    int id;
    unsigned short clutNum;
    unsigned char clutFmt;
    unsigned char levels;
    unsigned short width;
    unsigned short height;
    unsigned char tmode;
    unsigned char format;
    unsigned short flags;
    int clutOfs;
    unsigned int clut;
    unsigned int image;
    int m28;
};

/* A texture file: a 16 byte header with the texture count, then the texture headers. */
struct TexFile {
    int m0;
    unsigned short m4;
    unsigned short count;
    int m8;
    int m12;
};

namespace RRBios {
namespace TextureManager {
class CInfo {
public:
    unsigned int clut[8] __attribute__((aligned(64)));
    TexHeader head;
    unsigned int tex[38];
    unsigned int *clutList;
    unsigned int *clutCall;
    unsigned int *texList;
    unsigned int clutData;
    unsigned int image;
    CInfo() {}
};
}
}

using namespace RRBios::TextureManager;

int f_023340(unsigned int n);
void f_0233dc(void);
void f_023444(void);
CInfo *f_02347c(unsigned int id);
CInfo *f_0234a4(unsigned int id);
int f_023588(unsigned int id);
void f_0235ac(CInfo *info, TexHeader *h);
void f_023988(CInfo *info, unsigned int fmt, unsigned int num, int a);
void f_023a20(CInfo *info, unsigned int format, int w, int h, int a);
int f_024474(int n);
int f_02452c(int area, int id);
void f_024754(int area);
int f_02486c(int area, int i);
int f_0248d0(int area);
TexFile *f_024918(void *file);
TexHeader *f_024920(void *file, int i);
void f_024930(TexHeader *h);
void f_024aec(CInfo *info);
void f_024b34(TexHeader *h);
int f_024d24(TexHeader *h, unsigned int *clutPos, unsigned int *pos, unsigned int end);

unsigned int D_23c1f0;
unsigned int D_23c1f4;
unsigned int D_23c1f8[3];
unsigned int D_23c204[3];
unsigned int D_23c210[3];

/* @draft 0x022c30 us f_022c30
   WHAT IT DOES: Sets up texture memory for n textures: the start and fill point of the palette
   area and of texture areas 1 and 2 in video memory (area 1 from 0xcc000, area 2 from
   0x154000, both ending at 0x1fe000), the info store and the id lists. Returns 1 on success. */
int f_022c30(int n)
{
    unsigned int base = (unsigned int)sceGeEdramGetAddr();
    unsigned int a = base + 0xcc000;
    unsigned int e = a + 0x132000;
    unsigned int b = base + 0x154000;
    D_23c204[1] = a;
    D_23c210[1] = e;
    D_23c1f8[2] = b;
    D_23c1f8[1] = a;
    D_23c204[2] = b;
    D_23c210[2] = e;
    D_23c1f0 = base + 960;
    D_23c1f4 = base + 960;
    if (!f_023340(n))
        return 0;
    return f_024474(n) != 0;
}

/* @implements 0x022ce4 us f_022ce4
   WHAT IT DOES: Frees the texture info store. */
void f_022ce4(void)
{
    f_0233dc();
}

/* @implements 0x022d00 us f_022d00
   WHAT IT DOES: Enters every texture of a texture file that is not loaded yet, without copying
   it to video memory: optionally renumbers the textures from the given id, relocates each
   header and builds its command lists over the file's own pixels. Returns the file, or 0. */
void *f_022d00(void *file, int id)
{
    TexFile *f = f_024918(file);
    if (!f)
        return 0;
    int i;
    for (i = 0; i < f->count; i++) {
        TexHeader *e = f_024920(file, i);
        if (id) {
            e->id = id;
            id++;
        }
        CInfo *info = f_02347c(e->id);
        if (info == 0) {
            info = f_0234a4(e->id);
            f_024930(e);
            info->clutData = e->clutOfs;
            info->image = e->image;
            f_0235ac(info, e);
        }
    }
    return file;
}

/* @implements 0x022de4 us f_022de4
   WHAT IT DOES: Loads every texture of a texture file that is not loaded yet into a texture
   area: optionally renumbers them from the given id, records each id in the area's list,
   enters it in the info store, copies its pixels (and, for areas 0 and 1, its palette to the
   palette area) to video memory and builds its command lists. Returns the file, or 0. */
void *f_022de4(int area, void *file, int id)
{
    TexFile *f = f_024918(file);
    if (!f)
        return 0;
    int i;
    for (i = 0; i < f->count; i++) {
        TexHeader *e = f_024920(file, i);
        if (id) {
            e->id = id;
            id++;
        }
        if (f_02347c(e->id) == 0) {
            f_02452c(area, e->id);
            CInfo *info = f_0234a4(e->id);
            f_024930(e);
            if (area < 2)
                f_024d24(e, &D_23c1f4, &D_23c204[area], D_23c210[area]);
            else
                f_024d24(e, 0, &D_23c204[area], D_23c210[area]);
            info->clutData = e->clutOfs;
            info->image = e->image;
            f_0235ac(info, e);
        }
    }
    return file;
}

/* @implements 0x022f54 us f_022f54
   WHAT IT DOES: Reserves room for a palette of n colours (32 or 16 bit) at the fill point of a
   texture area under a new id, and builds its load list. Returns the record, or 0 if the id is
   taken. */
CInfo *f_022f54(int area, int id, unsigned int fmt, unsigned int n)
{
    CInfo *info = f_02347c(id);
    if (info != 0)
        return 0;
    f_02452c(area, id);
    unsigned int size = n * 4;
    info = f_0234a4(id);
    if (fmt == 3) {
        n = (n + 7) >> 3;
    } else {
        size = n * 2;
        n = (n + 15) >> 4;
    }
    unsigned int *pos = &D_23c204[area];
    info->clutData = *pos;
    f_023988(info, fmt, n, *pos);
    *pos += size;
    return info;
}

/* @implements 0x023038 us f_023038
   WHAT IT DOES: Enters a texture that already sits in video memory (format, size, offset in
   video memory) under a new id and builds its select list. Returns the record, or 0 if the id
   is taken. */
CInfo *f_023038(unsigned int fmt, int w, int h, unsigned int ofs, int id)
{
    CInfo *info = f_02347c(id);
    if (info != 0)
        return 0;
    info = f_0234a4(id);
    ofs += (unsigned int)sceGeEdramGetAddr();
    info->image = ofs;
    f_023a20(info, fmt, w, h, ofs);
    return info;
}

/* @implements 0x0230e0 us f_0230e0
   WHAT IT DOES: Relocates every texture header of a texture file. Returns the file, or 0. */
void *f_0230e0(void *file)
{
    TexFile *f = f_024918(file);
    if (!f)
        return 0;
    int i;
    for (i = 0; i < f->count; i++)
        f_024930(f_024920(file, i));
    return file;
}

/* @implements 0x023158 us f_023158
   WHAT IT DOES: Makes the GE run the palette and select lists of the texture with the given id.
   Returns its record, or 0 if it is not loaded. */
CInfo *f_023158(int id)
{
    CInfo *info = f_02347c(id);
    if (!info)
        return 0;
    f_024aec(info);
    return info;
}

/* @implements 0x023198 us f_023198
   WHAT IT DOES: Sends texture i of a texture file to the GE directly from the file. Returns its
   header. */
TexHeader *f_023198(void *file, int i)
{
    TexHeader *e = f_024920(file, i);
    f_024b34(e);
    return e;
}

/* @implements 0x0231c8 us f_0231c8
   WHAT IT DOES: Drops every texture of a texture file. Returns 0 as soon as one is not
   loaded. */
int f_0231c8(void *file)
{
    int i = 0;
    TexFile *f = f_024918(file);
    for (; i < f->count;) {
        TexHeader *e = f_024920(file, i);
        i++;
        if (f_023588(e->id) != 1)
            return 0;
    }
    return 1;
}

/* @implements 0x023250 us f_023250
   WHAT IT DOES: Drops the texture with the given id. */
int f_023250(int id)
{
    return f_023588(id);
}

/* @implements 0x02326c us f_02326c
   WHAT IT DOES: Empties a texture area: drops every texture recorded in it, clears its id list
   and rewinds its fill point and the palette area's. Returns 0 if the area is empty or a
   texture is missing. */
int f_02326c(int area)
{
    int n = f_0248d0(area);
    if (n == 0)
        return 0;
    int i;
    for (i = 0; i < n; i++)
        if (!f_023588(f_02486c(area, i)))
            return 0;
    f_024754(area);
    D_23c1f4 = D_23c1f0;
    D_23c204[area] = D_23c1f8[area];
    return 1;
}

/* @implements 0x023324 us f_023324
   WHAT IT DOES: Forgets every texture. */
void f_023324(void)
{
    f_023444();
}
