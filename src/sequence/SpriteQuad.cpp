/* The 2D sprite quad emitter (retail 0x0e7a54 to 0x0e7bc8). A sprite is two 10-byte vertex
   records in a buffer from the graphics allocator (f_021b38): the first holds the texture
   corner (u, v) and the screen corner (x + 96, y + 10), the second the opposite corner, the
   texture size (D_27ebc0, D_27ebc4) added to (u, v) and the screen size added to the corner.
   Four display list words then draw the two vertices, through the list cursor D_27ebcc. */

extern "C" {
unsigned char *f_021b38(unsigned int size);
}

extern unsigned int *D_27ebcc;      /* the display list cursor */
extern unsigned short D_27ebc0;     /* the sprite width */
extern unsigned short D_27ebc4;     /* the sprite height */

/* Stores a 16-bit value little-endian. */
static inline void Put16(unsigned char *p, int v)
{
    p[0] = (unsigned char)v;
    p[1] = (unsigned char)((unsigned int)v >> 8);
}

/* @draft 0x0e7a54 us f_0e7a54
   WHAT IT DOES: Emits a sprite at (x, y) with texture corner (u, v): the two vertex records
   are written to a new buffer, and the four display list words that draw them (the buffer
   address and the texture-enable tag) are appended through the list cursor. */
extern "C" void f_0e7a54(int x, int y, int u, int v)
{
    unsigned char *b = f_021b38(20);
    unsigned int addr = (unsigned int)b;
    unsigned int *q;

    Put16(b + 0, u & 0xffff);
    Put16(b + 2, v & 0xffff);
    Put16(b + 4, (x + 96) & 0xffff);
    Put16(b + 6, (y + 10) & 0xffff);
    b[8] = 0;
    b[9] = 0;
    Put16(b + 10, (D_27ebc0 + u) & 0xffff);
    Put16(b + 12, (D_27ebc4 + v) & 0xffff);
    Put16(b + 14, (D_27ebc0 + x + 96) & 0xffff);
    Put16(b + 16, (D_27ebc4 + y + 10) & 0xffff);
    b[18] = 0;
    b[19] = 0;

    q = D_27ebcc;
    q[0] = 0x12800102;
    q[1] = 0x10000000 | (((addr >> 24) & 0xf) << 16);
    q[2] = (addr & 0xffffff) | 0x01000000;
    q[3] = 0x04060002;
    D_27ebcc = q + 4;
}
