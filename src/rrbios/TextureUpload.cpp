/* Texture upload (retail 0x024aec to 0x024fb4): running a loaded texture's GE command lists,
   setting up the GE for a texture straight from a texture file, and copying a texture's
   palette and pixels (every mipmap level) into video memory at an area's fill point. */

#include <string.h>

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
    unsigned int clutOfs;
    unsigned int clut;
    unsigned int image;
    int m28;
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

void f_1164c8(void *list);
void f_1186c8(int format, int levels, int tmode, int swizzle);
void f_118948(int level, int w, int h, int bw, unsigned int addr);
void f_118ac4(int fmt, int shift, int mask, int start);
void f_118afc(int num, unsigned int addr);

extern signed char D_1d1a08[];
extern signed char D_1d1a10[];

/* The smallest power of two at least n (n up to 512). */
static inline int Pow2(int n)
{
    int k;
    for (k = 256; k > 0; k >>= 1)
        if (k & (n - 1)) {
            k <<= 1;
            break;
        }
    return k;
}

/* @implements 0x024aec us f_024aec
   WHAT IT DOES: Has the GE run a loaded texture's palette load list and select list. */
void f_024aec(CInfo *info)
{
    unsigned int *q = info->clutCall;
    if (q)
        f_1164c8(q);
    q = info->texList;
    if (q)
        f_1164c8(q);
}

/* @draft 0x024b34 us f_024b34
   WHAT IT DOES: Sets the GE up for a texture straight from a texture file: palette mode and
   load if it has one, then the texture mode and the address, size and buffer width of every
   mipmap level. */
void f_024b34(TexHeader *h)
{
    if (h->clutOfs) {
        f_118ac4(h->clutFmt, 0, 255, 0);
        f_118afc(h->clutNum, h->clut);
    }
    unsigned int img = h->image;
    if (!img)
        return;
    int levels = h->levels;
    int n = D_1d1a08[h->format];
    f_1186c8(h->format, levels, h->tmode, 1);
    int w = h->width;
    int ht = h->height;
    int bw = (w + n - 1) / n * n;
    unsigned int a = img;
    int tw, th;
    for (tw = 256; tw > 0; tw >>= 1)
        if (tw & (w - 1)) {
            tw <<= 1;
            break;
        }
    for (th = 256; th > 0; th >>= 1)
        if (th & (ht - 1)) {
            th <<= 1;
            break;
        }
    f_118948(0, tw, th, bw, img);
    int lv;
    for (lv = 0; lv < levels;) {
        bw = ((bw >> 1) + n - 1) / n * n;
        a += (w + n - 1) / n * ((ht + 7) / 8) * 128;
        lv++;
        tw >>= 1;
        th >>= 1;
        w >>= 1;
        ht >>= 1;
        f_118948(lv, tw, th, bw, a);
    }
}

/* @draft 0x024d24 us f_024d24
   WHAT IT DOES: Copies a texture into video memory. Its palette goes to the palette area when
   one is given (a 64 byte palette, while the area has room below 0x883c0) or else to the
   texture area's fill point; its pixels, every mipmap level, follow at the texture area's fill
   point, which then moves past them. The header's palette and pixel addresses are pointed at
   the copies. Stops when the area has no room left. */
int f_024d24(TexHeader *h, unsigned int *clutPos, unsigned int *pos, unsigned int end)
{
    if (h->clutOfs) {
        unsigned int *dst = 0;
        int shared = 0;
        unsigned int size = h->clutNum << 5;
        unsigned int e;
        if (clutPos && size == 64) {
            e = *clutPos + 1024;
            if ((unsigned int)sceGeEdramGetAddr() + 0x883c0 >= e) {
                dst = clutPos;
                shared = 1;
                goto copy;
            }
        }
        e = *pos + size;
        if (end >= e)
            dst = pos;
    copy:
        if (!dst)
            return 0;
        memcpy((void *)*dst, (void *)h->clutOfs, size);
        if (h->clut == h->clutOfs)
            h->clut = *dst;
        h->clutOfs = *dst;
        if (shared == 1)
            *dst = h->clutOfs + 1024;
        else
            *dst = h->clutOfs + size;
    }
    unsigned int src = h->image;
    if (!src)
        return 0;
    int n = D_1d1a10[h->format];
    int w = h->width;
    int levels = h->levels;
    int ht = h->height;
    Pow2(w);
    Pow2(ht);
    unsigned int size = (w + n - 1) / n * ((ht + 7) / 8) * 128;
    unsigned int d = *pos;
    unsigned int e = d + size;
    if (end < e)
        return 0;
    memcpy((void *)d, (void *)src, size);
    d = e;
    int lv;
    for (lv = 0; lv < levels;) {
        w >>= 1;
        ht >>= 1;
        src += size;
        lv++;
        size = (w + n - 1) / n * ((ht + 7) / 8) * 128;
        e = d + size;
        if (end < e)
            return 0;
        memcpy((void *)d, (void *)src, size);
        d = e;
    }
    h->image = *pos;
    *pos = d;
    return 0;
}
