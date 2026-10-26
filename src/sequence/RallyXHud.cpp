/* The Rally-X mini game's score and text drawing (retail 0x0e7c4c to 0x0e821c): the glyph
   sprites of the 2D helpers at 0x0e79c8 on, drawn from the font texture. A glyph code is a
   byte: its low five bits pick the column and bits 5 and up the row of the font sheet.
   Escape codes in the message text set the colour, the pen position, the skip and the
   special glyphs; the score, the fuel gauge and the round digits are drawn by the number
   routines. */

extern "C" {
void f_0e79c8(unsigned int color);
void f_0e7a10(int on);
void f_0e7a40(int w, int h);
void f_0e7a54(int x, int y, int u, int v);
void f_0e8014(int x, int y, int n, int flag);
void f_0e7db0(const unsigned char *text, int len, int flag);
void f_0e814c(int x, int y, int n, int flag);
void f_0e7c4c(int x, int y, const char *text, int n, unsigned int color);
void f_0e7cf4(int x, int y, int value, unsigned int color);
}

extern "C" {

/* @implements 0x0e7c4c us f_0e7c4c
   WHAT IT DOES: Draws n glyph sprites of a text in one colour, 8 units apart from x on the
   same row y. Each glyph's texture place comes from its byte: the low five bits give its
   column (8 units each) and the rest its row from the sheet's base at 232. */
void f_0e7c4c(int x, int y, const char *text, int n, unsigned int color)
{
    f_0e79c8(color);
    f_0e7a10(1);
    f_0e7a40(8, 8);
    for (int i = 0; i < n; i++) {
        unsigned char c = text[i];
        f_0e7a54(x, y, (c & 0x1f) * 8, (c >> 5) * 8 + 232);
        x += 8;
    }
}

/* @draft 0x0e7cf4 us f_0e7cf4
   WHAT IT DOES: Draws a non-negative number in one colour as its digits, least significant
   first, right to left from x (each digit 8 units wide), at least one digit. */
void f_0e7cf4(int x, int y, int value, unsigned int color)
{
    f_0e79c8(color);
    f_0e7a10(1);
    f_0e7a40(8, 8);
    do {
        x -= 8;
        int r = value % 10;
        f_0e7a54(x, y, r * 8 + 128, 232);
        value = value / 10;
    } while (value != 0);
}

/* @draft 0x0e7db0 us f_0e7db0
   WHAT IT DOES: Runs a message string through the glyph sprites: a '<' escape sets the
   colour from its three following bytes, '=' sets the pen position, '?' skips a column, '>'
   ends the text, and the other bytes are glyphs (the 64 to 75 range draws the wide and the
   special glyphs). The pen moves 12 units a glyph. */
void f_0e7db0(const unsigned char *text, int len, int flag)
{
    int penX = 0, penY = 0;
    f_0e7a10(1);
    f_0e7a40(8, 8);
    while (len > 0 && text[0] != '>') {
        unsigned char c = text[0];
        if (c == '<') {
            unsigned int col = ((unsigned int)text[3] << 16) | ((unsigned int)text[2] << 8)
                               | text[1] | 0xff000000u;
            f_0e79c8(col);
            text += 3;
        } else if (c == '=') {
            penX = text[1];
            penY = text[2];
            text += 2;
        } else if (c == '?') {
            len -= text[1];
            text += 1;
        } else if (c - 64 < 7u) {
            f_0e7a40(24, 24);
            f_0e7a54(penX, penY, 0, 144);
            text += 1;
            penX += 12;
        } else if (c - 71 < 5u) {
            f_0e7a40(24, 24);
            f_0e7a54(penX, penY, 0, 144);
            text += 1;
            penX += 12;
        } else {
            f_0e7a54(penX, penY, (c & 0x1f) * 8, (c >> 5) * 8 + 232);
            penX += 12;
            text += 1;
        }
        len--;
    }
    (void)flag;
}

/* @draft 0x0e8014 us f_0e8014
   WHAT IT DOES: Draws a one- or two-digit count as glyph sprites in a box: a 5-unit frame
   of four sprites around the digits, placed differently when flag is set (the box then
   starts at the origin, not 5 units in) and for counts of ten and up. */
void f_0e8014(int x, int y, int n, int flag)
{
    if (n < 10) {
        int sx = x + 5;
        if (flag) {
            f_0e7a40(10, 7);
            f_0e7a54(x + 15, y + 10, 116, 249);
            sx = x;
        }
        f_0e7a40(5, 7);
        f_0e7a54(sx, y + 10, 5 * n + 66, 249);
        f_0e7a54(sx + 5, y + 10, 66, 249);
        f_0e7a54(sx + 10, y + 10, 66, 249);
    } else {
        int yy = y + 5;
        f_0e7a40(10, 7);
        if (flag) {
            f_0e7a54(x + 15, y + 7, 116, 249);
            yy = y;
        }
        f_0e7a40(5, 7);
        f_0e7a54(x, yy, 71, 249);
        f_0e7a54(x + 5, yy, 66, 249);
        f_0e7a54(x + 10, yy, 66, 249);
        f_0e7a54(x + 15, yy, 66, 249);
    }
}

/* @implements 0x0e814c us f_0e814c
   WHAT IT DOES: Draws the status icon for a count: an icon from the first three texture
   places for counts 1 to 3, otherwise the count's box (f_0e8014 with the count less 3)
   followed by a 24-unit frame. */
void f_0e814c(int x, int y, int n, int flag)
{
    f_0e79c8(0xffffffffu);
    f_0e7a10(1);
    f_0e7a40(24, 24);
    if (n == 1) {
        f_0e7a54(x, y, 0, 144);
    } else if (n == 2) {
        f_0e7a54(x, y, 24, 144);
    } else if (n == 3) {
        f_0e7a54(x, y, 48, 144);
    } else {
        f_0e8014(x, y, n - 3, flag);
        f_0e7a40(24, 24);
    }
}

}
