/* Car body palettes and light fades (retail 0x026ab0 to 0x026ffc). A car's palette file holds
   one entry per body texture: a base palette and a paint mask palette. Setting the file up
   reserves a fresh palette in video memory for every entry; tinting writes base plus the mask
   scaled by the chosen body colour into those palettes; applying them points each body texture
   at its tinted palette. The light table keeps six lamps' brightness for eight steps each and
   fades them out a little every frame. */

/* One palette of a car's palette file. */
struct PalEntry {
    int tex;            /* the body texture's id, replaced by its record once set up */
    unsigned int n;     /* colours */
    unsigned int fmt;   /* 0: 5650, 1: 5551, 2: 4444, 3: 8888 */
    int m12;
    unsigned short c[1]; /* n base colours, then n mask colours */
};

/* A car's palette file: a flag byte (bit 7 once set up), the palette count and the offsets of
   the palettes (pointers once set up). */
struct PalFile {
    int m0;
    char m4;
    signed char done;
    unsigned short count;
    PalEntry *entry[1];
};

/* A texture record of the texture info store. */
struct CInfo {
    int tex;
    char m4[212];
    int clut;
    int m220;
    int m224;
    unsigned int vram;
};

/* The palette set a car draws with: its file and the id of its first palette. */
struct CPalette {
    PalFile *file;
    int first;
};

/* Six lamps of eight steps each: per step the six brightness levels, and per lamp whether it
   has faded out completely. */
struct LightRow {
    char pad[40];
    short v[7];
    char pad2[26];
};
struct LightTable {
    int on;
    char pad[36];
    LightRow row[8];
    unsigned char done[6];
    signed char phase;
};

extern "C" {
CInfo *f_022f54(int area, int id, unsigned int fmt, unsigned int n);
CInfo *f_02347c(unsigned int id);
}

extern int D_1d1a18;

/* @draft 0x026ab0 us f_026ab0
   WHAT IT DOES: Sets up a car's palettes from its palette file in the given texture area: on
   first use it turns the file's offsets into pointers, reserves a new palette id for each
   entry (counting up from a global id), and looks up each entry's body texture. Marks the
   file as set up and returns 1.
   Remaining difference: retail keeps the offset loop's index counting up (slt against the
   count held in a2); this source compiles it to a down counter in s0, which shifts the
   register use of the rest. */
int f_026ab0(CPalette *p, int area, PalFile *f)
{
    int i;

    p->file = f;
    if (f == 0)
        return 1;
    if (f->done >= 0) {
        for (i = 0; i < f->count; i++)
            f->entry[i] = (PalEntry *)((char *)f->entry[i] + (int)f);
    }
    p->first = D_1d1a18;
    for (i = 0; i < p->file->count; i++) {
        PalEntry *e = p->file->entry[i];
        f_022f54(area, D_1d1a18, e->fmt, e->n);
        D_1d1a18++;
        if (p->file->done >= 0)
            e->tex = (int)f_02347c(e->tex);
    }
    p->file->done |= 0x80;
    return 1;
}

/* @implements 0x026bc8 us f_026bc8
   WHAT IT DOES: Paints the car: for every palette, each colour becomes the base colour plus the
   mask colour with its red, green and blue scaled by the body colour (0 to 255), written into
   the car's palette in video memory in the palette's own pixel format. */
void f_026bc8(CPalette *p, int r, int g, int b)
{
    unsigned short *d16;
    unsigned int *d32;
    unsigned short *s16;
    unsigned int *s32;
    unsigned short *m16;
    unsigned int *m32;
    int i;

    if (p->file == 0)
        return;
    d16 = 0;
    d32 = 0;
    s16 = 0;
    s32 = 0;
    m16 = 0;
    m32 = 0;
    for (i = 0; i < p->file->count; i++) {
        PalEntry *e = p->file->entry[i];
        CInfo *info = f_02347c(p->first + i);
        unsigned int k;

        if (e->fmt == 3) {
            d32 = (unsigned int *)info->vram;
            d32 = (unsigned int *)((unsigned int)d32 | 0x40000000);
            s32 = (unsigned int *)e->c;
            m32 = s32 + e->n;
        } else {
            d16 = (unsigned short *)info->vram;
            d16 = (unsigned short *)((unsigned int)d16 | 0x40000000);
            s16 = e->c;
            m16 = s16 + e->n;
        }
        for (k = 0; k < e->n; k++) {
            unsigned int cr, cg, cb;

            switch (e->fmt) {
            case 0:
                cr = *m16 & 0x1f;
                cg = (*m16 >> 5) & 0x3f;
                cb = *m16 >> 11;
                break;
            case 1:
                cr = *m16 & 0x1f;
                cg = (*m16 >> 5) & 0x1f;
                cb = (*m16 >> 10) & 0x1f;
                break;
            case 2:
                cr = *m16 & 0xf;
                cg = (*m16 >> 4) & 0xf;
                cb = (*m16 >> 8) & 0xf;
                break;
            default:
                cr = *m32 & 0xff;
                cg = (*m32 >> 8) & 0xff;
                cb = (*m32 >> 16) & 0xff;
                break;
            }
            cr = cr * r / 255;
            cg = cg * g / 255;
            cb = cb * b / 255;
            switch (e->fmt) {
            case 0:
                *d16++ = *s16++ + (cr | cg << 5 | cb << 11);
                m16++;
                break;
            case 1:
                *d16++ = *s16++ + (cr | cg << 5 | cb << 10);
                m16++;
                break;
            case 2:
                *d16++ = *s16++ + (cr | cg << 4 | cb << 8);
                m16++;
                break;
            default:
                *d32++ = *s32++ + (cr | cg << 8 | cb << 16);
                m32++;
                break;
            }
        }
    }
}

/* @implements 0x026e5c us f_026e5c
   WHAT IT DOES: Points every body texture of the car at its tinted palette. */
void f_026e5c(CPalette *p)
{
    PalFile *f = p->file;
    int i;

    if (f == 0)
        return;
    for (i = 0; i < f->count; i++) {
        CInfo *tex = (CInfo *)f->entry[i]->tex;
        tex->m220 = f_02347c(p->first + i)->clut;
        f = p->file;
    }
}

/* @implements 0x026ed8 us f_026ed8
   WHAT IT DOES: Releases a car's palettes: the palette ids start again from the first one. */
void f_026ed8(CPalette *p)
{
    if (p->file) {
        D_1d1a18 = 0x0a000100;
        p->file = 0;
    }
}

/* @implements 0x026efc us f_026efc
   WHAT IT DOES: Resets the light table: all six lamps off and not faded, the seventh level of
   every step full on, and the fade phase back to the start. (Also transcribed in the control
   set.) */
void f_026efc(LightTable *t)
{
    int i, j;

    if (t->on) {
        for (i = 0; i < 6; i++) {
            t->done[i] = 1;
            for (j = 0; j < 8; j++)
                t->row[j].v[i] = 0;
        }
        for (j = 0; j < 8; j++)
            t->row[j].v[6] = 1;
        t->phase = 0;
    }
}

/* @draft 0x026f70 us f_026f70
   WHAT IT DOES: Fades the lamps one frame: every level drops by 21 and stops at zero; a lamp is
   marked faded only if all eight of its levels reached zero. The fade phase counts 0 to 15.
   Remaining difference: retail recomputes the column address (sll/addu from the lamp index)
   every outer pass and steps the faded flag by a byte pointer; this source strength reduces
   both, which adds one register and shifts the rest. */
void f_026f70(LightTable *t)
{
    int i, j;

    if (t->on) {
        for (i = 0; i < 6; i++) {
            t->done[i] = 1;
            for (j = 0; j < 8; j++) {
                short v = t->row[j].v[i] -= 21;
                if (v <= 0)
                    t->row[j].v[i] = 0;
                else
                    t->done[i] = 0;
            }
        }
        if (++t->phase >= 16)
            t->phase = 0;
    }
}
