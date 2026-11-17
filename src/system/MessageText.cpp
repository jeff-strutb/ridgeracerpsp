/* The message text object file (retail 0x07d74c to 0x07df70). A loaded message file holds
   text in glyph codes: a header, per font tables mapping character codes to glyph codes, an
   id table and the strings. Eight argument slots hold either a string converted to glyph
   codes or the id of another message. A message is laid out into lines of positioned glyphs,
   expanding arguments and nested messages and aligning each line. */

#include <stdio.h>

/* One font's entry in the message file header (32 bytes). */
struct MsgFontEnt {
    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
};

/* The message file header. */
struct MsgHdr {
    int nfont;
    int nmsg;
    int ids;
    int m12;
    MsgFontEnt font[1];
};

/* One entry of a font's character to glyph map. */
struct MsgMap {
    unsigned short code;
    unsigned short glyph;
};

/* One font's tables, resolved to addresses: two character to glyph maps and a third
   table. */
struct MsgFont {
    char *m0;
    MsgMap *map16;
    MsgMap *map8;
};

/* One message id and its string's offset (in glyph codes). */
struct MsgId {
    int id;
    int off;
};

/* An argument slot: a glyph code string, or {-1, -1} followed by a message id. */
union MsgArg {
    short text[32];
    struct {
        short m0;
        short m2;
        int id;
    } ref;
};

/* One positioned glyph of a laid out line (16 bytes). */
struct MsgGlyph {
    short x;
    short m2;
    short m4[6];
};

struct CMessageText {
    CMessageText();
    ~CMessageText();

    int nmsg;
    int nfont;
    MsgHdr *hdr;
    MsgFontEnt *fontEnt;
    MsgFont font[32];
    MsgId *ids;
    short *strs;
    int m408;
    MsgArg arg[8];
};

extern short D_1d3a3c[];

/* One glyph image in a font's glyph table: its rectangle in the font texture (16 bytes). */
struct MsgGlyphImg {
    int x0;
    int y0;
    int x1;
    int y1;
};

/* One laid out line: its glyph count and glyphs (6404 bytes). */
struct MsgLine {
    int n;
    MsgGlyph g[400];
};

/* A laid out message: its line count and lines. */
struct MsgLayout {
    int nlines;
    MsgLine line[1];
};

extern "C" void f_07d89c(CMessageText *m, int slot, const char *s, int unused);
extern "C" short *f_07deec(CMessageText *m, int id);
extern "C" void f_07dec4(CMessageText *m, MsgGlyph *g, int n, int dx);
extern "C" void f_07dea0(CMessageText *m, MsgGlyph *g, int n, int dx);

/* @implements 0x07d74c us _ZN12CMessageTextC2Ev
   WHAT IT DOES: Base object constructor: no message file loaded. */
/* @implements 0x07d754 us _ZN12CMessageTextC1Ev
   WHAT IT DOES: Complete object constructor, the same. */
CMessageText::CMessageText()
{
    hdr = 0;
}

/* @implements 0x07d75c us _ZN12CMessageTextD2Ev
   WHAT IT DOES: Base object destructor: nothing to free. */
/* @implements 0x07d764 us _ZN12CMessageTextD1Ev
   WHAT IT DOES: Complete object destructor, the same. */
CMessageText::~CMessageText()
{
}

/* @implements 0x07d76c us f_07d76c
   WHAT IT DOES: Attaches a loaded message file: takes the counts from its header, resolves
   each font's three tables and the id and string tables to addresses, names the eight
   argument slots "ARG 0" to "ARG 7" and sets the limit at +408 to 100000. Returns 0. */
extern "C" int f_07d76c(CMessageText *m, MsgHdr *h)
{
    char buf[32];
    int i;
    int ids;

    m->hdr = h;
    m->nfont = h->nfont;
    m->nmsg = h->nmsg;
    m->fontEnt = h->font;
    ids = h->ids;
    for (i = 0; i < m->nfont; i++) {
        m->font[i].m0 = (char *)m->hdr + m->fontEnt[i].m4;
        m->font[i].map16 = (MsgMap *)((char *)m->hdr + m->fontEnt[i].m8);
        m->font[i].map8 = (MsgMap *)((char *)m->hdr + m->fontEnt[i].m12);
    }
    m->ids = (MsgId *)((char *)m->hdr + ids);
    m->strs = (short *)(m->ids + m->nmsg);
    for (i = 0; i < 8; i++) {
        sprintf(buf, "ARG %d", i);
        f_07d89c(m, i, buf, 0);
    }
    m->m408 = 100000;
    return 0;
}

/* @implements 0x07d878 us f_07d878
   WHAT IT DOES: Detaches the message file. */
extern "C" void f_07d878(CMessageText *m)
{
    m->hdr = 0;
}

/* @implements 0x07d880 us f_07d880
   WHAT IT DOES: Makes an argument slot refer to another message by id. */
extern "C" void f_07d880(CMessageText *m, int slot, int id)
{
    m->arg[slot].text[1] = m->arg[slot].text[0] = -1;
    m->arg[slot].ref.id = id;
}

/* @draft 0x07d89c us f_07d89c
   WHAT IT DOES: Sets an argument slot to an ASCII string converted to the small font's glyph
   codes: capitals from 2, lower case from 28, digits from 54, '.' as 127 and anything else as
   1; the string is ended with 0.
   REMAINING DIFFERENCE: the control flow and the lbu/seb loads match; retail keeps the
   capital test in v1 and the glyph value in v0 and puts the lower case sltiu in the first
   branch's delay slot, where this build puts the -63 add (register allocation order). */
extern "C" void f_07d89c(CMessageText *m, int slot, const char *s, int unused)
{
    short *d = m->arg[slot].text;
    int i;

    for (i = 0; s[i]; i++) {
        if ((unsigned char)(s[i] - 'A') < 26)
            *d = s[i] - 'A' + 2;
        else if ((unsigned char)(s[i] - 'a') < 26)
            *d = s[i] - 'a' + 28;
        else if ((unsigned char)(s[i] - '0') < 10)
            *d = s[i] - '0' + 54;
        else if (s[i] == '.')
            *d = 127;
        else
            *d = 1;
        d++;
    }
    *d = 0;
}

/* @draft 0x07d948 us f_07d948
   WHAT IT DOES: Sets an argument slot to a Shift-JIS string converted to a font's glyph codes.
   Lead bytes 0x81 to 0x9f and 0xe0 to 0xef take the next byte with them; each character code
   is looked up in the font's map and characters not in it are dropped. Does nothing when no
   message file is attached.
   REMAINING DIFFERENCE: 3 words at the loop's back edge. Retail tests the reloaded byte in
   v0 and copies it to t0 in the branch slot; this build tests t0 directly and fills the slot
   from the loop head. Unsigned char, int and short variables and four loop shapes tried. */
extern "C" void f_07d948(CMessageText *m, int slot, const unsigned char *s, int font)
{
    short *d;
    MsgFontEnt *e;
    MsgFont *f;
    int c;
    int code;
    MsgMap *map;
    int k;

    if (m->hdr == 0)
        return;
    d = m->arg[slot].text;
    f = &m->font[font];
    e = &m->fontEnt[font];
    while ((c = *s) != 0) {
        if ((unsigned char)(c - 0x81) < 31 | (unsigned char)(c - 0xe0) < 16) {
            code = s[0] | (s[1] << 8);
            s += 2;
        } else {
            code = c;
            s++;
        }
        for (k = 0, map = f->map8; k < e->m20; k++) {
            if (map->code == code) {
                *d++ = map->glyph;
                break;
            }
            map++;
        }
    }
    *d = 0;
}

/* @implements 0x07da28 us f_07da28
   WHAT IT DOES: Sets an argument slot to a string of 16-bit character codes converted to a
   font's glyph codes through its second map; characters not in the map are dropped. Does
   nothing when no message file is attached. */
extern "C" void f_07da28(CMessageText *m, int slot, const unsigned short *s, int font)
{
    short *d;
    MsgFontEnt *e;
    MsgFont *f;
    MsgMap *map;
    unsigned short c;
    int k;

    if (m->hdr == 0)
        return;
    d = m->arg[slot].text;
    f = &m->font[font];
    e = &m->fontEnt[font];
    c = *s;
    while (c) {
        for (k = 0, map = f->map16; k < e->m16; k++) {
            if (map->code == (short)c) {
                *d++ = map->glyph;
                break;
            }
            map++;
        }
        s++;
        c = *s;
    }
    *d = 0;
}

/* @draft 0x07dacc us f_07dacc
   WHAT IT DOES: Lays out a message into lines of positioned glyphs. The first code of the
   message is its font; each glyph code takes its rectangle from the font's glyph table and
   advances the pen by its width. Code -2 ends the line, as does a space (1) once the pen has
   reached the wrap limit at +408; -3 centres and -5 right-aligns the following lines (within
   the given width), -4 does nothing, -100 to -199 insert an argument slot (its text or the
   message it refers to) and codes below -199 insert the message whose id follows in two
   codes. Inserted text is walked through a stack of return positions. Returns the font, or
   -1 when the message id is unknown.
   Remaining difference: allocation. Global-alloc gives the wrap flag a register (fp) and
   spills the font, where retail keeps the font in s7 and the flag at sp+88; with the flag in a
   register fold turns "wrap && c == 1" into an and of set-flags where retail branches. Holding
   the pen state in a local struct was tried and is wrong: it loses retail's strength-reduced
   line pointers (s4, s6, s8, sp+96), so line is a plain register variable in retail. */
extern "C" int f_07dacc(CMessageText *m, int id, MsgLayout *out, int width)
{
    unsigned short *stk[16];
    int depth = 0;
    int line = 0;
    int n = 0;
    int x = 0;
    int center = 0;
    int right = 0;
    int wrap = 0;
    unsigned short *s;
    int font;
    short *p = f_07deec(m, id);

    if (p == 0)
        return -1;
    font = p[0];
    s = (unsigned short *)(p + 1);
    for (;;) {
        unsigned short u = *s;
        int c = (short)u;
        if (c == 0) {
            if (depth == 0)
                break;
            s = stk[--depth];
            continue;
        }
        if (x >= m->m408)
            wrap = 1;
        if ((wrap && c == 1) || c == -2) {
            if (center)
                f_07dea0(m, out->line[line].g, n, width - x);
            if (right)
                f_07dec4(m, out->line[line].g, n, width - x);
            out->line[line].n = n;
            line++;
            n = 0;
            x = 0;
            wrap = 0;
        } else if (c >= 0) {
            MsgGlyphImg *e = &((MsgGlyphImg *)m->font[font].m0)[c - 1];
            MsgGlyph *g = &out->line[line].g[n];
            g->m4[4] = u;
            g->m4[0] = e->x0;
            g->m4[1] = e->y0;
            g->m4[2] = e->x1;
            g->m4[3] = e->y1;
            g->m2 = 0;
            n++;
            g->x = x;
            x += e->x1 - e->x0;
        } else if (c == -3) {
            center = 1;
            right = 0;
        } else if (c == -5) {
            center = 0;
            right = 1;
        } else if (c == -4) {
        } else if (c < -199) {
            stk[depth++] = s + 3;
            s = (unsigned short *)(f_07deec(m, s[1] | (s[2] << 16)) + 1);
        } else if (c < -99) {
            MsgArg *a = &m->arg[-100 - c];
            stk[depth++] = s + 1;
            s = (unsigned short *)a->text;
            if (a->text[0] < 0)
                s = (unsigned short *)(f_07deec(m, a->ref.id) + 1);
            s--;
        }
        s++;
    }
    if (center)
        f_07dea0(m, out->line[line].g, n, width - x);
    if (right)
        f_07dec4(m, out->line[line].g, n, width - x);
    out->nlines = line + 1;
    out->line[line].n = n;
    return font;
}

/* @implements 0x07de74 us f_07de74
   WHAT IT DOES: Returns the first glyph code of a message (its font number), or -1 when the
   id is unknown. */
extern "C" int f_07de74(CMessageText *m, int id)
{
    short *p = f_07deec(m, id);
    int r = -1;
    if (p)
        r = *p;
    return r;
}

/* @implements 0x07dea0 us f_07dea0
   WHAT IT DOES: Centres a run of laid out glyphs: moves them right by half the spare width. */
extern "C" void f_07dea0(CMessageText *m, MsgGlyph *g, int n, int dx)
{
    f_07dec4(m, g, n, dx / 2);
}

/* @implements 0x07dec4 us f_07dec4
   WHAT IT DOES: Moves a run of laid out glyphs right by a distance. */
extern "C" void f_07dec4(CMessageText *m, MsgGlyph *g, int n, int dx)
{
    int i;

    for (i = 0; i < n; i++)
        g[i].x += dx;
}

/* @implements 0x07deec us f_07deec
   WHAT IT DOES: Finds a message by id and returns its string, or the shared empty string when
   the id is unknown. */
extern "C" short *f_07deec(CMessageText *m, int id)
{
    int i;

    for (i = 0; i < m->nmsg; i++) {
        if (m->ids[i].id == id)
            return &m->strs[m->ids[i].off];
    }
    return D_1d3a3c;
}

/* @implements 0x07df34 us f_07df34
   WHAT IT DOES: Returns 1 when a message with the id exists, 0 otherwise. */
extern "C" int f_07df34(CMessageText *m, int id)
{
    int i;

    for (i = 0; i < m->nmsg; i++) {
        if (m->ids[i].id == id)
            return 1;
    }
    return 0;
}
