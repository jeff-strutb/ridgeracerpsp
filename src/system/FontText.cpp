/* The bitmap font text object file (retail 0x07ac1c to 0x07d74c). A text style holds a
   glyph set offset and scales; ASCII and the game's two byte codes are mapped to 10 byte
   glyph records in a fixed table, which are copied into glyph lists or summed into text
   widths. */

#include <string.h>

/* A glyph record: the texture page it is drawn from, its texture coordinates (u, v), its
   advance width (which is also its width in the texture) and its height. */
struct Glyph {
    unsigned char page;
    unsigned char m1;
    unsigned short u;
    unsigned short v;
    unsigned short width;
    unsigned short height;
};

/* The glyph table: digits, capitals and lower case letters first, then the symbols. Two runs
   inside it are addressed through their own symbols (retail builds their addresses apart
   from the table's): the four brace and tilde glyphs (entry 156) and three single symbols
   (entries 166 to 168). */
extern Glyph D_1d33a0[];
extern Glyph D_1d39b8[];
extern Glyph D_1d3a1c[];
extern Glyph D_1d3a26[];
extern Glyph D_1d3a30[];

/* A text style: the texture table (one texture per glyph page, held as a word), the glyph
   set offset and the two scales. */
struct TextStyle {
    int m0;
    int set;
    float sx;
    float sy;
};

/* The textured rectangle drawer (defined at the end of the file). */
extern "C" int f_07d574(TextStyle *t, int x0, int y0, int z0, int u0, int v0, int x1, int y1,
                        int z1, int u1, int v1, int tex, float r, float g, float b, float a);

/* @implements 0x07ac1c us f_07ac1c
   WHAT IT DOES: Resets a text style: first glyph set, unit scales. */
extern "C" void f_07ac1c(TextStyle *t)
{
    t->m0 = 0;
    t->set = 0;
    t->sx = 1.0f;
    t->sy = 1.0f;
}

/* @implements 0x07ac38 us f_07ac38
   WHAT IT DOES: Sets the word at +0 of a text style. */
extern "C" void f_07ac38(TextStyle *t, int v)
{
    t->m0 = v;
}

/* @implements 0x07ac40 us f_07ac40
   WHAT IT DOES: Selects the first glyph set. */
extern "C" void f_07ac40(TextStyle *t)
{
    t->set = 0;
}

/* @draft 0x07ac48 us f_07ac48
   WHAT IT DOES: Converts an ASCII and Shift-JIS half width (katakana) string into glyph
   records in a text style: digits, letters, punctuation, katakana and a few symbols each
   append a copy of their glyph to the output list; other characters are skipped. Returns the
   number of glyphs written.
   REMAINING DIFFERENCE: the control flow and every case's address arithmetic match. Retail
   hoists thirteen case bases out of the loop, all but the brace run's; this build also
   hoists the brace run's base and not the 0xa1 to 0xa3 one, so the registers differ (and
   retail keeps the output pointer in a2, copied back from s0 after strlen). */
extern "C" int f_07ac48(TextStyle *t, const char *s, Glyph *out)
{
    unsigned int len = strlen(s);
    int n = 0;
    Glyph *g = 0;
    unsigned int i;

    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            g = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            g = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            g = &D_1d33a0[c - 'a' + 36 + t->set];
        else if ((unsigned char)(c - 0xc0) < 32)
            g = &D_1d33a0[c - 0xc0 + 62 + t->set];
        else if (c == 0x80)
            g = &D_1d33a0[c - 0x80 + 222 + t->set];
        else if (c >= 0xe0)
            g = &D_1d33a0[c - 0xe0 + 95 + t->set];
        else if (c == 0x81)
            g = &D_1d33a0[c - 0x81 + 256 + t->set];
        else if ((unsigned char)(c - '!') < 15)
            g = &D_1d33a0[c - '!' + 128 + t->set];
        else if ((unsigned char)(c - ':') < 7)
            g = &D_1d33a0[c - ':' + 143 + t->set];
        else if ((unsigned char)(c - '[') < 6)
            g = &D_1d33a0[c - '[' + 150 + t->set];
        else if ((unsigned char)(c - '{') < 4)
            g = &D_1d39b8[c - '{' + t->set];
        else if ((unsigned char)(c - 0xa1) < 3)
            g = &D_1d33a0[c - 0xa1 + 160 + t->set];
        else if (c == 0xa5)
            g = &D_1d33a0[c - 0xa5 + 328 + t->set];
        else if (c == 0xb1)
            g = &D_1d33a0[c - 0xb1 + 341 + t->set];
        else if (c == 0xb2)
            g = &D_1d33a0[c - 0xb2 + 343 + t->set];
        else if (c == 0xb7)
            g = &D_1d3a1c[t->set];
        else if (c == 0xbf)
            g = &D_1d3a26[t->set];
        else if (c == 0x82)
            g = &D_1d3a30[t->set];
        if (g) {
            *out = *g;
            out++;
            n++;
            g = 0;
        }
    }
    return n;
}

/* @implements 0x07b018 us f_07b018
   WHAT IT DOES: Draws an ASCII and Shift-JIS half width (katakana) string in a text style at
   (x, y) with proportional spacing, tinted by a colour given as four 0 to 1 floats: each
   mapped character (the f_07bbcc set) is drawn scaled by the style and the pen advances by
   its scaled width; a space advances 5 and other characters are skipped. Returns 0 when the
   style has no texture table or the string is empty, otherwise 1. */
extern "C" int f_07b018(TextStyle *t, int x, int y, int align, const char *s, float r, float g,
                        float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    len = strlen(s);
    i = 0;
    gl = 0;
    if (len == 0)
        return ret;
next:
    if (i < len) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            gl = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            gl = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            gl = &D_1d33a0[c - 'a' + 36 + t->set];
        else if ((unsigned char)(c - 0xc0) < 32)
            gl = &D_1d33a0[c - 0xc0 + 62 + t->set];
        else if (c == 0x80)
            gl = &D_1d33a0[94 + t->set];
        else if (c >= 0xe0)
            gl = &D_1d33a0[c - 0xe0 + 95 + t->set];
        else if (c == 0x81)
            gl = &D_1d33a0[127 + t->set];
        else if ((unsigned char)(c - '!') < 15)
            gl = &D_1d33a0[c - '!' + 128 + t->set];
        else if ((unsigned char)(c - ':') < 7)
            gl = &D_1d33a0[c - ':' + 143 + t->set];
        else if ((unsigned char)(c - '[') < 6)
            gl = &D_1d33a0[c - '[' + 150 + t->set];
        else if ((unsigned char)(c - '{') < 4)
            gl = &D_1d33a0[c - '{' + 156 + t->set];
        else if ((unsigned char)(c - 0xa1) < 3)
            gl = &D_1d33a0[c - 0xa1 + 160 + t->set];
        else if (c == 0xa5)
            gl = &D_1d33a0[163 + t->set];
        else if (c == 0xb1)
            gl = &D_1d33a0[164 + t->set];
        else if (c == 0xb2)
            gl = &D_1d33a0[165 + t->set];
        else if (c == 0xb7)
            gl = &D_1d33a0[166 + t->set];
        else if (c == 0xbf)
            gl = &D_1d33a0[167 + t->set];
        else if (c == 0x82)
            gl = &D_1d33a0[168 + t->set];
        else if (c == ' ')
            x += 5;
        if (gl) {
            f_07d574(t, x, y, -1, gl->u, gl->v, x + (int)(gl->width * t->sx),
                     y + (int)(gl->height * t->sy), -1, gl->u + gl->width, gl->v + gl->height,
                     ((int *)t->m0)[gl->page], r, g, b, a);
            x += (int)(gl->width * t->sx);
            gl = 0;
        }
        i++;
        goto next;
    }
    ret = 1;
    return ret;
}

/* @draft 0x07b4c8 us f_07b4c8
   WHAT IT DOES: Draws an ASCII and Shift-JIS half width (katakana) string in a text style at
   (x, y) on a fixed pitch, tinted by a colour given as four 0 to 1 floats: each mapped
   character (the f_07bbcc set) is drawn scaled by the style and the pen advances by the
   scaled pitch, except punctuation ('!' to '/'), which advances by its own scaled width; a
   space advances half the scaled pitch and other characters are skipped. Alignment 2 ends the
   text at x and 3 centres it on x (using the scaled pitch times the length). Returns 0 when
   the style has no texture table or the string is empty, otherwise 1.
   Remaining difference: as in f_07c344, global-alloc gives the style pointer s0 and the
   alignment/index s1 (retail the reverse) and the colour floats other saved FPRs; in the
   alignment blocks the FP temporaries differ, so align 2's tail cross-jumps into align 3's
   (8 bytes short). The control flow and every address match. */
extern "C" int f_07b4c8(TextStyle *t, int x, int y, int pitch, int align, const char *s,
                        float r, float g, float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;
    int adv;

    if (t->m0 == 0)
        return ret;
    len = strlen(s);
    adv = pitch;
    gl = 0;
    if (len == 0)
        return ret;
    if (align == 2)
        x -= (int)((float)(pitch * len) * t->sx);
    else if (align == 3)
        x -= (int)((float)(int)((float)(pitch * len) * t->sx) * 0.5f);
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            gl = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            gl = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            gl = &D_1d33a0[c - 'a' + 36 + t->set];
        else if ((unsigned char)(c - 0xc0) < 32)
            gl = &D_1d33a0[c - 0xc0 + 62 + t->set];
        else if (c == 0x80)
            gl = &D_1d33a0[94 + t->set];
        else if (c >= 0xe0)
            gl = &D_1d33a0[c - 0xe0 + 95 + t->set];
        else if (c == 0x81)
            gl = &D_1d33a0[127 + t->set];
        else if ((unsigned char)(c - '!') < 15) {
            gl = &D_1d33a0[c - '!' + 128 + t->set];
            adv = gl->width;
        }
        else if ((unsigned char)(c - ':') < 7)
            gl = &D_1d33a0[c - ':' + 143 + t->set];
        else if ((unsigned char)(c - '[') < 6)
            gl = &D_1d33a0[c - '[' + 150 + t->set];
        else if ((unsigned char)(c - '{') < 4)
            gl = &D_1d33a0[c - '{' + 156 + t->set];
        else if ((unsigned char)(c - 0xa1) < 3)
            gl = &D_1d33a0[c - 0xa1 + 160 + t->set];
        else if (c == 0xa5)
            gl = &D_1d33a0[163 + t->set];
        else if (c == 0xb1)
            gl = &D_1d33a0[164 + t->set];
        else if (c == 0xb2)
            gl = &D_1d33a0[165 + t->set];
        else if (c == 0xb7)
            gl = &D_1d33a0[166 + t->set];
        else if (c == 0xbf)
            gl = &D_1d33a0[167 + t->set];
        else if (c == 0x82)
            gl = &D_1d33a0[168 + t->set];
        else if (c == ' ')
            x += (int)((float)pitch * 0.5f * t->sx);
        if (gl) {
            f_07d574(t, x, y, -1, gl->u, gl->v, x + (int)(gl->width * t->sx),
                     y + (int)(gl->height * t->sy), -1, gl->u + gl->width, gl->v + gl->height,
                     ((int *)t->m0)[gl->page], r, g, b, a);
            x += (int)(adv * t->sx);
            adv = pitch;
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @implements 0x07ba68 us f_07ba68
   WHAT IT DOES: Returns the width of an ASCII string in a text style: digits, capitals, lower
   case letters, a two byte code introduced by 0x83 and the 0x81 code each add their glyph's
   advance width; other characters add nothing. */
extern "C" int f_07ba68(TextStyle *t, const char *s)
{
    unsigned int len = strlen(s);
    int w = 0;
    Glyph *g = 0;
    unsigned int i;

    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            g = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            g = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            g = &D_1d33a0[c - 'a' + 36 + t->set];
        else if (c == 0x83) {
            i++;
            c = s[i];
            g = &D_1d33a0[c - 2 + t->set];
        } else if (c == 0x81) {
            i++;
            g = &D_1d33a0[149 + t->set];
        }
        if (g) {
            w += g->width;
            g = 0;
        }
    }
    return w;
}

/* @implements 0x07bbcc us f_07bbcc
   WHAT IT DOES: Returns the width of an ASCII and Shift-JIS half width (katakana) string in a
   text style, over the same character set as f_07ac48: each mapped character adds its glyph's
   advance width, a space adds 9 and other characters add nothing. */
extern "C" int f_07bbcc(TextStyle *t, const char *s)
{
    unsigned int len = strlen(s);
    int w = 0;
    Glyph *g = 0;
    unsigned int i;

    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            g = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            g = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            g = &D_1d33a0[c - 'a' + 36 + t->set];
        else if ((unsigned char)(c - 0xc0) < 32)
            g = &D_1d33a0[c - 0xc0 + 62 + t->set];
        else if (c == 0x80)
            g = &D_1d33a0[94 + t->set];
        else if (c >= 0xe0)
            g = &D_1d33a0[c - 0xe0 + 95 + t->set];
        else if (c == 0x81)
            g = &D_1d33a0[127 + t->set];
        else if ((unsigned char)(c - '!') < 15)
            g = &D_1d33a0[c - '!' + 128 + t->set];
        else if ((unsigned char)(c - ':') < 7)
            g = &D_1d33a0[c - ':' + 143 + t->set];
        else if ((unsigned char)(c - '[') < 6)
            g = &D_1d33a0[c - '[' + 150 + t->set];
        else if ((unsigned char)(c - '{') < 4)
            g = &D_1d33a0[c - '{' + 156 + t->set];
        else if ((unsigned char)(c - 0xa1) < 3)
            g = &D_1d33a0[c - 0xa1 + 160 + t->set];
        else if (c == 0xa5)
            g = &D_1d33a0[163 + t->set];
        else if (c == 0xb1)
            g = &D_1d33a0[164 + t->set];
        else if (c == 0xb2)
            g = &D_1d33a0[165 + t->set];
        else if (c == 0xb7)
            g = &D_1d33a0[166 + t->set];
        else if (c == 0xbf)
            g = &D_1d33a0[167 + t->set];
        else if (c == 0x82)
            g = &D_1d33a0[168 + t->set];
        else if (c == ' ') {
            g = 0;
            w += 9;
        }
        if (g) {
            w += g->width;
            g = 0;
        }
    }
    return w;
}

/* @implements 0x07bf78 us f_07bf78
   WHAT IT DOES: Returns the width of a string of glyph codes (at most n, ending at 0) in a
   text style: each code adds its glyph's advance width and 255 adds 16. */
extern "C" int f_07bf78(TextStyle *t, unsigned int n, const char *s)
{
    Glyph *g = 0;
    int w = 0;
    unsigned int len;
    unsigned int i;

    for (len = 0; len < n; len++) {
        if (s[len] == 0)
            break;
    }
    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if (c != 0 && c != 0xff)
            g = &D_1d33a0[c + t->set];
        else if (c == 0xff)
            w += 16;
        if (g) {
            w += g->width;
            g = 0;
        }
    }
    return w;
}

/* The texture bank and the textured rectangle drawer. */
extern "C" void *f_023198(int tex, int i);

/* A screen position and a texture coordinate pair, as the rectangle drawer reads them. */
struct Pos16 { unsigned short x, y, z; };
struct UV16 { unsigned short u, v; };
extern "C" void f_022400(const Pos16 *v, const UV16 *uv, unsigned int color);

extern "C" int f_07d574(TextStyle *t, int x0, int y0, int z0, int u0, int v0, int x1, int y1,
                        int z1, int u1, int v1, int tex, float r, float g, float b, float a);

/* @draft 0x07c03c us f_07c03c
   WHAT IT DOES: Draws an ASCII string in a text style at (x, y), one character cell of the
   given pitch per glyph, tinted by a colour given as four 0 to 1 floats: digits, letters, a
   two byte code introduced by 0x83 and the 0x81 code each draw their glyph scaled by the style
   and centred in its cell; other characters are skipped. Alignment 2 ends the text at x and
   3 centres it on x. Returns 0 when the style has no texture table or the string is empty,
   otherwise 1.
   Remaining difference: as in f_07d060, the alignment 3 block builds the 0.5 constant's
   address half in v1 instead of v0 (local-alloc choice); every other word matches.
   (2026-11-16: the cause is sched1. With the mult's latency pending it issues the 0.5 HIGH and
   load (insns 97, 99) before floatsisf2 (96); update_equiv_regs then moves them after 96, but
   local-alloc still sees 203 (the product) live across 4 insns, overlapping 207, so 207 gets
   v1. Retail needs 96 ahead of the constant in sched1's order.) Not a named constant: retail's
   .rodata holds 0.5f seven times at 0x1a7188-0x1a71a0, one per function's literal pool (this
   function's at 0x1a718c, f_07d060's at 0x1a719c), so the source writes the literal. */
extern "C" int f_07c03c(TextStyle *t, int x, int y, int pitch, int align, const char *s,
                        float r, float g, float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    len = strlen(s);
    gl = 0;
    if (len == 0)
        return ret;
    if (align == 2)
        x -= pitch * len;
    else if (align == 3)
        x -= (int)((float)(int)(pitch * len) * 0.5f);
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            gl = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            gl = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            gl = &D_1d33a0[c - 'a' + 36 + t->set];
        else if (c == 0x83) {
            i++;
            c = s[i];
            gl = &D_1d33a0[c - 2 + t->set];
        } else if (c == 0x81) {
            i++;
            gl = &D_1d33a0[149 + t->set];
        }
        if (gl) {
            float w = gl->width * t->sx;
            int x0 = x + (int)(((float)pitch - w) * 0.5f);
            f_07d574(t, x0, y, -1, gl->u, gl->v, x0 + (int)w, y + (int)(gl->height * t->sy), -1,
                     gl->u + gl->width, gl->v + gl->height, ((int *)t->m0)[gl->page], r, g, b, a);
            x += pitch;
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @draft 0x07c344 us f_07c344
   WHAT IT DOES: Draws an ASCII string in a text style at (x, y) with proportional spacing,
   tinted by a colour given as four 0 to 1 floats: digits and letters are drawn scaled by the
   style and the pen advances by each one's scaled width; other characters are skipped.
   Alignment 2 ends the text at x and 3 centres it on x (using the measured width). Returns 0
   when the style has no texture table or the string is empty, otherwise 1.
   Remaining difference: global-alloc gives x s2 and the alignment/index s3 (retail the
   reverse), and in both alignment blocks local-alloc picks the FP registers in the other
   order (retail keeps the measured width in f0 and truncates in place). */
extern "C" int f_07c344(TextStyle *t, int x, int y, int align, const char *s, float r, float g,
                        float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    len = strlen(s);
    gl = 0;
    if (len == 0)
        return ret;
    if (align == 2) {
        x -= (int)(f_07ba68(t, s) * t->sx);
    } else if (align == 3) {
        x -= (int)((int)(f_07ba68(t, s) * t->sx) * 0.5f);
    }
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            gl = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            gl = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            gl = &D_1d33a0[c - 'a' + 36 + t->set];
        if (gl) {
            f_07d574(t, x, y, -1, gl->u, gl->v, x + (int)(gl->width * t->sx),
                     y + (int)(gl->height * t->sy), -1, gl->u + gl->width, gl->v + gl->height,
                     ((int *)t->m0)[gl->page], r, g, b, a);
            x += (int)(gl->width * t->sx);
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @draft 0x07c610 us f_07c610
   WHAT IT DOES: Draws an ASCII and Shift-JIS half width (katakana) string in a text style at
   (x, y), one character cell of the given pitch per glyph, tinted by a colour given as four 0
   to 1 floats: each mapped character (the f_07bbcc set) draws its glyph scaled by the style
   and centred in its cell, a space is an empty cell and other characters are skipped.
   Alignment 2 ends the text at x and 3 centres it on x. Returns 0 when the style has no
   texture table or the string is empty, otherwise 1.
   Remaining difference: global-alloc gives the style pointer s0 and the alignment/index s1
   (retail the reverse: pseudo 182 is allocated before 186/195 here); every other word matches. */
extern "C" int f_07c610(TextStyle *t, int x, int y, int pitch, int align, const char *s,
                        float r, float g, float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    len = strlen(s);
    gl = 0;
    if (len == 0)
        return ret;
    if (align == 2)
        x -= pitch * len;
    else if (align == 3)
        x -= (int)((float)(int)(pitch * len) * 0.5f);
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            gl = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            gl = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            gl = &D_1d33a0[c - 'a' + 36 + t->set];
        else if ((unsigned char)(c - 0xc0) < 32)
            gl = &D_1d33a0[c - 0xc0 + 62 + t->set];
        else if (c == 0x80)
            gl = &D_1d33a0[94 + t->set];
        else if (c >= 0xe0)
            gl = &D_1d33a0[c - 0xe0 + 95 + t->set];
        else if (c == 0x81)
            gl = &D_1d33a0[127 + t->set];
        else if ((unsigned char)(c - '!') < 15)
            gl = &D_1d33a0[c - '!' + 128 + t->set];
        else if ((unsigned char)(c - ':') < 7)
            gl = &D_1d33a0[c - ':' + 143 + t->set];
        else if ((unsigned char)(c - '[') < 6)
            gl = &D_1d33a0[c - '[' + 150 + t->set];
        else if ((unsigned char)(c - '{') < 4)
            gl = &D_1d33a0[c - '{' + 156 + t->set];
        else if ((unsigned char)(c - 0xa1) < 3)
            gl = &D_1d33a0[c - 0xa1 + 160 + t->set];
        else if (c == 0xa5)
            gl = &D_1d33a0[163 + t->set];
        else if (c == 0xb1)
            gl = &D_1d33a0[164 + t->set];
        else if (c == 0xb2)
            gl = &D_1d33a0[165 + t->set];
        else if (c == 0xb7)
            gl = &D_1d33a0[166 + t->set];
        else if (c == 0xbf)
            gl = &D_1d33a0[167 + t->set];
        else if (c == 0x82)
            gl = &D_1d33a0[168 + t->set];
        else if (c == ' ') {
            gl = 0;
            x += pitch;
        }
        if (gl) {
            float w = gl->width * t->sx;
            int x0 = x + (int)(((float)pitch - w) * 0.5f);
            f_07d574(t, x0, y, -1, gl->u, gl->v, x0 + (int)w, y + (int)(gl->height * t->sy), -1,
                     gl->u + gl->width, gl->v + gl->height, ((int *)t->m0)[gl->page], r, g, b, a);
            x += pitch;
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @draft 0x07cb24 us f_07cb24
   WHAT IT DOES: Draws an ASCII and Shift-JIS half width (katakana) string in a text style at
   (x, y) with proportional spacing, tinted by a colour given as four 0 to 1 floats: each
   mapped character (the f_07bbcc set) is drawn scaled by the style and the pen advances by
   its scaled width; a space advances 9 and other characters are skipped. Alignment 2 ends the
   text at x and 3 centres it on x (using the width f_07bbcc measures). Returns 0 when the
   style has no texture table or the string is empty, otherwise 1.
   Remaining difference: as in f_07c344, global-alloc gives the style pointer s1 and the
   alignment/index s2 (retail the reverse), the four colour floats land in other saved FPRs,
   and both alignment blocks pick the FP temporaries in the other order. */
extern "C" int f_07cb24(TextStyle *t, int x, int y, int align, const char *s, float r, float g,
                        float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    len = strlen(s);
    gl = 0;
    if (len == 0)
        return ret;
    if (align == 2) {
        x -= (int)(f_07bbcc(t, s) * t->sx);
    } else if (align == 3) {
        x -= (int)((int)(f_07bbcc(t, s) * t->sx) * 0.5f);
    }
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if ((unsigned char)(c - '0') < 10)
            gl = &D_1d33a0[c - '0' + t->set];
        else if ((unsigned char)(c - 'A') < 26)
            gl = &D_1d33a0[c - 'A' + 10 + t->set];
        else if ((unsigned char)(c - 'a') < 26)
            gl = &D_1d33a0[c - 'a' + 36 + t->set];
        else if ((unsigned char)(c - 0xc0) < 32)
            gl = &D_1d33a0[c - 0xc0 + 62 + t->set];
        else if (c == 0x80)
            gl = &D_1d33a0[94 + t->set];
        else if (c >= 0xe0)
            gl = &D_1d33a0[c - 0xe0 + 95 + t->set];
        else if (c == 0x81)
            gl = &D_1d33a0[127 + t->set];
        else if ((unsigned char)(c - '!') < 15)
            gl = &D_1d33a0[c - '!' + 128 + t->set];
        else if ((unsigned char)(c - ':') < 7)
            gl = &D_1d33a0[c - ':' + 143 + t->set];
        else if ((unsigned char)(c - '[') < 6)
            gl = &D_1d33a0[c - '[' + 150 + t->set];
        else if ((unsigned char)(c - '{') < 4)
            gl = &D_1d33a0[c - '{' + 156 + t->set];
        else if ((unsigned char)(c - 0xa1) < 3)
            gl = &D_1d33a0[c - 0xa1 + 160 + t->set];
        else if (c == 0xa5)
            gl = &D_1d33a0[163 + t->set];
        else if (c == 0xb1)
            gl = &D_1d33a0[164 + t->set];
        else if (c == 0xb2)
            gl = &D_1d33a0[165 + t->set];
        else if (c == 0xb7)
            gl = &D_1d33a0[166 + t->set];
        else if (c == 0xbf)
            gl = &D_1d33a0[167 + t->set];
        else if (c == 0x82)
            gl = &D_1d33a0[168 + t->set];
        else if (c == ' ') {
            gl = 0;
            x += 9;
        }
        if (gl) {
            f_07d574(t, x, y, -1, gl->u, gl->v, x + (int)(gl->width * t->sx),
                     y + (int)(gl->height * t->sy), -1, gl->u + gl->width, gl->v + gl->height,
                     ((int *)t->m0)[gl->page], r, g, b, a);
            x += (int)(gl->width * t->sx);
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @draft 0x07d060 us f_07d060
   WHAT IT DOES: Draws a string of glyph codes (at most n, ending at 0) in a text style at
   (x, y), one character cell of the given pitch per code, tinted by a colour given as four 0
   to 1 floats. Alignment 2 ends the text at x and 3 centres it on x. Each glyph is scaled by
   the style and centred in its cell; code 255 is an empty cell. Returns 0 when the style has
   no texture table or the string is empty, otherwise 1.
   Remaining difference: in the alignment 3 block the 0.5 constant's address half is built in
   v1 instead of v0 (local-alloc gives it v1 after update_equiv_regs moves the load next to its
   use); every other word matches. Root cause as in f_07c03c: sched1 places the constant's
   HIGH and load ahead of floatsisf2 while the mult's latency is pending. Its 0.5f is this
   function's own literal-pool word (0x1a719c), so a named constant is ruled out. */
extern "C" int f_07d060(TextStyle *t, int x, int y, int pitch, int align, unsigned int n,
                        const char *s, float r, float g, float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    gl = 0;
    for (len = 0; len < n; len++) {
        if (s[len] == 0)
            break;
    }
    if (len == 0)
        return ret;
    if (align == 2)
        x -= pitch * len;
    else if (align == 3)
        x -= (int)((float)(int)(pitch * len) * 0.5f);
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if (c != 0 && c != 0xff)
            gl = &D_1d33a0[c + t->set];
        else if (c == 0xff)
            x += pitch;
        if (gl) {
            float w = gl->width * t->sx;
            int x0 = x + (int)(((float)pitch - w) * 0.5f);
            f_07d574(t, x0, y, -1, gl->u, gl->v, x0 + (int)w, y + (int)(gl->height * t->sy), -1,
                     gl->u + gl->width, gl->v + gl->height, ((int *)t->m0)[gl->page], r, g, b, a);
            x += pitch;
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @draft 0x07d2d8 us f_07d2d8
   WHAT IT DOES: Draws a string of glyph codes (at most n, ending at 0) in a text style at
   (x, y) with proportional spacing, tinted by a colour given as four 0 to 1 floats: each
   glyph is scaled by the style and the pen advances by its scaled width; code 255 advances
   16. Alignment 2 ends the text at x and 3 centres it on x (using the measured width).
   Returns 0 when the style has no texture table or the string is empty, otherwise 1.
   Remaining difference: in both alignment blocks local-alloc picks the FP registers in the
   other order (retail keeps the measured width in f0 and truncates in place); the loop and
   every other word match. In align 2 retail gives the int-in-FPR (mtc1) f0, the tied cvt/mul
   pair f1 and the truncation f0 again: the mtc1 pseudo is allocated before the 4-ref cvt/mul qty,
   which this source's priorities (refs/length) do not allow. */
extern "C" int f_07d2d8(TextStyle *t, int x, int y, int align, unsigned int n, const char *s,
                        float r, float g, float b, float a)
{
    int ret = 0;
    Glyph *gl;
    unsigned int len;
    unsigned int i;

    if (t->m0 == 0)
        return ret;
    gl = 0;
    for (len = 0; len < n; len++) {
        if (s[len] == 0)
            break;
    }
    if (len == 0)
        return ret;
    if (align == 2) {
        x -= (int)(f_07bf78(t, n, s) * t->sx);
    } else if (align == 3) {
        x -= (int)((int)(f_07bf78(t, n, s) * t->sx) * 0.5f);
    }
    for (i = 0; i < len; i++) {
        unsigned char c = s[i];
        if (c != 0 && c != 0xff)
            gl = &D_1d33a0[c + t->set];
        else if (c == 0xff)
            x += 16;
        if (gl) {
            f_07d574(t, x, y, -1, gl->u, gl->v, x + (int)(gl->width * t->sx),
                     y + (int)(gl->height * t->sy), -1, gl->u + gl->width, gl->v + gl->height,
                     ((int *)t->m0)[gl->page], r, g, b, a);
            x += (int)(gl->width * t->sx);
            gl = 0;
        }
    }
    ret = 1;
    return ret;
}

/* @implements 0x07d574 us f_07d574
   WHAT IT DOES: Draws one textured rectangle from its two corners (position and texture
   coordinates) with the given texture, tinted by a colour given as four 0 to 1 floats that
   are packed into one 32-bit colour. Returns 1. */
extern "C" int f_07d574(TextStyle *t, int x0, int y0, int z0, int u0, int v0, int x1, int y1,
                        int z1, int u1, int v1, int tex, float r, float g, float b, float a)
{
    Pos16 p[2];
    UV16 uv[2];
    unsigned int c;

    c = ((unsigned int)(r * 255.0f) & 0xff) | (((unsigned int)(g * 255.0f) & 0xff) << 8) |
        (((unsigned int)(b * 255.0f) & 0xff) << 16) | ((unsigned int)(a * 255.0f) << 24);
    f_023198(tex, 0);
    p[0].z = z0;
    p[1].z = z1;
    p[0].x = x0;
    p[0].y = y0;
    p[1].x = x1;
    p[1].y = y1;
    uv[0].u = u0;
    uv[0].v = v0;
    uv[1].u = u1;
    uv[1].v = v1;
    f_022400(p, uv, c);
    return 1;
}
