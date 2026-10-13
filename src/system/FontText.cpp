/* The bitmap font text object file (retail 0x07ac1c to 0x07d74c). A text style holds a
   glyph set offset and scales; ASCII and the game's two byte codes are mapped to 10 byte
   glyph records in a fixed table, which are copied into glyph lists or summed into text
   widths. */

#include <string.h>

/* A glyph record: its place in the font texture and its size; the advance width at +6. */
struct Glyph {
    short m0;
    short m2;
    short m4;
    unsigned short width;
    short m8;
};

/* The glyph table: digits, capitals and lower case letters first, then the symbols. */
extern Glyph D_1d33a0[];

/* A text style: a word at +0, the glyph set offset at +4 and the two scales. */
struct TextStyle {
    int m0;
    int set;
    float sx;
    float sy;
};

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
