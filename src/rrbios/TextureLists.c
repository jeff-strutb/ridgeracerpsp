/* Texture area bookkeeping and texture file access (retail 0x024474 to 0x024aec): the list of
   texture ids loaded into each of the three texture areas (one array kept sorted by area, with
   a start and a count per area), the walk over a texture file's headers and the relocation of
   their offsets, and the GE calls that select a loaded texture, with a cache of the last
   palette and texture selected. */

#include <stdlib.h>
#include <string.h>

/* One loaded texture id and the area it went to. */
struct Slot {
    unsigned int area;
    int id;
};

/* The part of the id array that belongs to one area. */
struct Group {
    unsigned int start;
    unsigned int num;
};

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
    int clut;
    int image;
    int m28;
};

/* A texture file: a 16 byte header, then the texture headers. */
struct TexFile {
    int m0;
    unsigned short m4;
    unsigned short count;
    int m8;
    int m12;
    struct TexHeader entries[1];
};

/* The texture info record's command list pointers (see TextureInfo.cpp). */
struct CInfo {
    unsigned int clut[8];
    unsigned int head[8];
    unsigned int tex[38];
    int clutList;
    int clutCall;
    int texList;
};

struct Slot *D_23c780;
unsigned int D_23c784;
unsigned int D_23c788;
struct Group D_23c78c[3];
int D_23c7a4;
int D_23c7a8;

/* @implements 0x024474 us f_024474
   WHAT IT DOES: Allocates the id array for n textures and empties every area. Returns 0 if the
   memory cannot be had. */
int f_024474(int n)
{
    int i;
    D_23c780 = malloc(n * 8);
    if (!D_23c780)
        return 0;
    D_23c788 = n;
    D_23c784 = 0;
    for (i = 0; i < 3; i++) {
        D_23c78c[i].start = 0;
        D_23c78c[i].num = 0;
    }
    return 1;
}

/* @implements 0x0244e4 us f_0244e4
   WHAT IT DOES: Frees the id array. */
void f_0244e4(void)
{
    if (D_23c780)
        free(D_23c780);
    D_23c780 = 0;
    D_23c784 = 0;
}

/* @draft 0x02452c us f_02452c
   WHAT IT DOES: Records a texture id at the end of an area's part of the id array, moving the
   later areas up by one. Returns 0 if there is no array, the area is out of range or the array
   is full. */
int f_02452c(unsigned int area, int id)
{
    struct Slot *p = D_23c780;
    struct Group *g;
    unsigned int pos;
    int i;
    if (!p)
        return 0;
    if (area >= 3)
        return 0;
    if (D_23c784 == D_23c788)
        return 0;
    g = &D_23c78c[area];
    pos = g->start + g->num;
    memmove(&p[pos + 1], &p[pos], (D_23c784 - pos) * 8);
    p = &D_23c780[pos];
    p->area = area;
    p->id = id;
    D_23c784++;
    g->num++;
    for (i = 2 - area; i != 0; i--) {
        g++;
        g->start++;
    }
    return 1;
}

/* @draft 0x02463c us f_02463c
   WHAT IT DOES: Removes a texture id from an area's part of the id array, moving the later
   areas down by one. */
void f_02463c(unsigned int area, int id)
{
    struct Slot *p = D_23c780;
    struct Group *g;
    unsigned int n, i;
    int k;
    if (!p)
        return;
    if (area >= 3)
        return;
    if (D_23c784 == 0)
        return;
    g = &D_23c78c[area];
    n = g->num;
    if (n == 0)
        return;
    for (i = g->start; n != 0; n--, i++)
        if (p[i].id == id)
            break;
    if (n == 0)
        return;
    memmove(&D_23c780[i], &D_23c780[i + 1], (D_23c784 - (i + 1)) * 8);
    g->num--;
    D_23c784--;
    for (k = 2 - area; k != 0; k--) {
        g++;
        g->start--;
    }
}

/* @draft 0x024754 us f_024754
   WHAT IT DOES: Removes every id of an area from the id array, moving the later areas down. */
void f_024754(unsigned int area)
{
    struct Slot *p = D_23c780;
    struct Group *g;
    unsigned int count, end, n;
    int k;
    if (!p)
        return;
    if (area >= 3)
        return;
    count = D_23c784;
    if (count == 0)
        return;
    g = &D_23c78c[area];
    if (g->num == 0)
        return;
    end = g->start + g->num;
    memmove(&p[g->start], &p[end], (count - end) * 8);
    n = g->num;
    D_23c784 -= n;
    g->num = 0;
    for (k = 2 - area; k != 0; k--) {
        g++;
        g->start -= n;
    }
}

/* @implements 0x02482c us f_02482c
   WHAT IT DOES: Empties every area of the id array. */
void f_02482c(void)
{
    int i;
    if (D_23c780) {
        D_23c784 = 0;
        for (i = 0; i < 3; i++) {
            D_23c78c[i].start = 0;
            D_23c78c[i].num = 0;
        }
    }
}

/* @draft 0x02486c us f_02486c
   WHAT IT DOES: Returns the id of texture i of an area, or -1. */
int f_02486c(unsigned int area, unsigned int i)
{
    struct Slot *p = D_23c780;
    struct Group *g;
    if (!p)
        return -1;
    if (area >= 3)
        return -1;
    g = &D_23c78c[area];
    if (D_23c784 == 0)
        return -1;
    if (i >= g->num)
        return -1;
    return p[g->start + i].id;
}

/* @implements 0x0248d0 us f_0248d0
   WHAT IT DOES: Returns how many textures an area holds. */
int f_0248d0(unsigned int area)
{
    if (!D_23c780)
        return 0;
    if (area >= 3)
        return 0;
    if (D_23c784 == 0)
        return 0;
    return D_23c78c[area].num;
}

/* @implements 0x024918 us f_024918
   WHAT IT DOES: Returns a texture file's header (the file itself). */
struct TexFile *f_024918(void *file)
{
    return file;
}

/* @implements 0x024920 us f_024920
   WHAT IT DOES: Returns the header of texture i of a texture file. */
struct TexHeader *f_024920(void *file, int i)
{
    return &((struct TexFile *)file)->entries[i];
}

/* A texture header as the relocation sees it. */
struct H024 {
    int m0;
    unsigned short n4;
    unsigned char type6;
    char pad7[7];
    unsigned short flags;
    int p16;
    int p20;
    int p24;
};

/* @implements 0x024930 us f_024930
   (also transcribed in the control set)
   WHAT IT DOES: Relocates a texture header once: turns its palette and pixel offsets into
   addresses, and its palette size from colours into 8 or 16 colour blocks. */
void f_024930(struct H024 *h)
{
    unsigned short fl = h->flags;
    if (fl & 1)
        return;
    if (h->p16) {
        if (h->type6 == 3)
            h->n4 = (h->n4 + 7) >> 3;
        else
            h->n4 = (h->n4 + 15) >> 4;
        h->p20 = h->p16 = h->p16 + (int)h;
    }
    if (h->p24)
        h->p24 += (int)h;
    h->flags = fl | 1;
}

/* @draft 0x0249a0 us f_0249a0
   WHAT IT DOES: Writes into a display list the GE calls of a texture's palette load list and
   select list (base, then call, for each one it has). Returns the new end of the list. */
unsigned int *f_0249a0(struct CInfo *info, unsigned int *p)
{
    int a = info->clutCall;
    unsigned int base = ((a >> 24) & 0xf) << 16 | 0x10000000;
    unsigned int call = (a & 0xffffff) | 0x0a000000;
    if (a) {
        *p++ = base;
        *p++ = call;
    }
    a = info->texList;
    base = ((a >> 24) & 0xf) << 16 | 0x10000000;
    call = (a & 0xffffff) | 0x0a000000;
    if (a) {
        *p++ = base;
        *p++ = call;
    }
    return p;
}

/* @implements 0x024a28 us f_024a28
   WHAT IT DOES: Forgets the last palette and texture selected. */
void f_024a28(void)
{
    D_23c7a4 = 0;
    D_23c7a8 = 0;
}

/* @draft 0x024a3c us f_024a3c
   WHAT IT DOES: Like f_0249a0, but skips the palette or select list call when it is the one
   selected last. Returns the new end of the list. */
unsigned int *f_024a3c(struct CInfo *info, unsigned int *p)
{
    int a = info->clutCall;
    if (a) {
        unsigned int base = ((a >> 24) & 0xf) << 16 | 0x10000000;
        unsigned int call = (a & 0xffffff) | 0x0a000000;
        if (D_23c7a4 != a) {
            D_23c7a4 = a;
            *p++ = base;
            *p++ = call;
        }
    }
    a = info->texList;
    if (a) {
        unsigned int base = ((a >> 24) & 0xf) << 16 | 0x10000000;
        unsigned int call = (a & 0xffffff) | 0x0a000000;
        if (D_23c7a8 != a) {
            D_23c7a8 = a;
            *p++ = base;
            *p++ = call;
        }
    }
    return p;
}
