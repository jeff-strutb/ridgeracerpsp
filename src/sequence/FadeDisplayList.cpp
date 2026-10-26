/* The screen fade's GE display list (retail 0x0e9ebc to 0x0ea894, with the fade's
   colour and draw words). f_0e9ebc scales the fade colour by a level and stores the packed
   colour, then runs f_0e9f0c, which writes the fade's GE command words at a list cursor and
   returns the cursor after them. The state words are in FadeColourState.c and
   FadeStateReaders.c. */

extern "C" {
unsigned char *f_021b38(int size) throw();
unsigned int f_021d38(void) throw();
unsigned int f_021d5c(unsigned int a) throw();
unsigned int f_021e08(unsigned int a) throw();
unsigned int *f_02dba8(unsigned int *list) throw();
unsigned int sceGeEdramGetAddr(unsigned int a) throw();
int f_0e9f0c(int b);
}

extern int D_1d5a80;            /* fade on */
extern int D_1d5a8c;            /* the fade's second channel */
extern int D_27ec78;            /* the packed fade colour */
extern int D_27ec7c;            /* the fade colour's third channel */
extern int D_27ec80;            /* the fade colour's fourth channel */

/* @implements 0x0e9ebc us f_0e9ebc
   WHAT IT DOES: Scales the fade colour by a level and packs it. The fade's level word
   D_27ec80 is multiplied by the float k and truncated to a byte-sized level c; the packed
   colour (c in each of the four bytes) is stored to D_27ec78, and the list builder runs on b,
   returning its result. */
extern "C" int f_0e9ebc(int b, float k)
{
    int c = (int)((float)D_27ec80 * k);
    unsigned int v = ((unsigned int)c << 24) | ((unsigned int)c << 16) | ((unsigned int)c << 8) | c;
    D_27ec78 = v;
    return f_0e9f0c(b);
}

static inline void Put8(unsigned char *p, int off, unsigned int v)
{
    p[off] = (unsigned char)v;
}

/* @draft 0x0e9f0c us f_0e9f0c
   Remaining difference: PARTIAL transcription, not the whole function. This draft is 1540 of
   the retail 2440 bytes. The header, the four-block loop, the vram block, the two-block loop
   and the fixed colour block follow the disassembly; the step loop here writes one 16-byte
   sub-block per step, where retail writes four sub-blocks of records and words (64 bytes per
   step), and the end block's words are approximate. Register allocation and the record byte
   values differ, so the output does not match retail.
   WHAT IT DOES: Writes the fade's GE command list at the cursor b and returns the cursor after
   it. Nothing is written unless the fade is on (D_1d5a80) and its colour is set (D_27ec78). The
   list is a header of buffer and draw-state words, a loop of four blocks, a block from the vram
   address, a loop of two blocks, a fixed colour block, a loop of one block per fade step (up to
   D_1d5a80 steps), and an end block; the cursor after the end block is returned. */
int f_0e9f0c(int b)
{
    unsigned int *s3;
    unsigned int s0, s1, s2, s4, s5, s6, s7, s8, a1, a2, a3, a6, t0, t1, t2, t3, v, col;
    unsigned char *p, *p2;
    int i, n;

    if (D_1d5a80 == 0 || D_27ec78 == 0)
        return b;
    s3 = (unsigned int *)b;
    s0 = f_021e08(b);
    s1 = 0x00ffffff;
    s5 = 0x04060002;
    s6 = 0x10000000;
    v = sceGeEdramGetAddr(s0);
    s4 = v + s0;
    s2 = s1;
    a6 = (s0 & s1) | 0x9c000000;

    /* the header: the buffer and texture addresses, the draw state */
    s3[0] = 0x22000000;
    s3[1] = 0x24000000;
    s3[2] = 0x23000000;
    s3[3] = 0x1d000000;
    s3[4] = 0x21000000;
    s3[5] = 0x1f000000;
    s3[6] = 0x17000000;
    s3[7] = 0x20000000;
    s3[8] = 0x27000000;
    s3[9] = 0x1e000001;
    s3[10] = 0xd2000003;
    s3[11] = a6;
    s3[12] = ((s0 >> 24) << 16) | 0x9d000100;
    s3[13] = 0xc2000000;
    s3[14] = (unsigned int)D_1d5a8c | 0xc3000000;
    v = f_021d5c(0x20000);
    s3[15] = (v & s1) | 0xa0000000;
    s3[16] = (((v >> 24) & 0xf) << 16) | 0xa8000200;
    s3[17] = 0xb8000909;
    s3[18] = 0xc6000101;
    s3[19] = 0xcb000000;
    s3[20] = 0x55ffffff;
    s3[21] = 0x580000ff;
    s3[22] = 0x12800102;
    s3 += 23;

    /* loop 1: four blocks, each a 20-byte record pair and three words */
    for (i = 0; i < 4; i++) {
        p = f_021b38(20);
        a1 = (((unsigned int)p >> 24) & 0xf) << 16 | 0x10000000;
        a2 = ((unsigned int)i * 64) & 0xffff;
        a3 = ((unsigned int)i * 128) & 0xffff;
        t1 = (unsigned int)i * 64 + 64;
        t1 = t1 < 241 ? t1 : 241;
        t2 = (unsigned int)i * 128 + 128;
        t2 = t2 < 481 ? t2 : 481;
        t1 &= 0xffff;
        t2 &= 0xffff;
        t3 = ((unsigned int)p & s1) | 0x01000000;
        Put8(p, 5, a2 >> 8);
        Put8(p, 4, a2);
        Put8(p, 1, a3 >> 8);
        Put8(p, 0, a3);
        Put8(p, 6, 0);
        Put8(p, 7, 0);
        Put8(p, 2, 0);
        Put8(p, 3, 0);
        p2 = p + 10;
        Put8(p2, 3, 1);
        Put8(p2, 6, 0x89);
        Put8(p2, 2, 16);
        Put8(p2, 5, t1 >> 8);
        Put8(p2, 1, t2 >> 8);
        Put8(p2, 4, t1);
        Put8(p2, 7, 0);
        Put8(p2, 0, t2);
        s3[0] = a1;
        s3[1] = t3;
        s3[2] = 0x04060002;
        s3 += 3;
    }

    /* the block at the vram address s4 */
    s3[0] = 0xc9000100;
    s3[1] = 0xc3000003;
    s3[2] = 0xc2000000;
    s3[3] = (s4 & s1) | 0xa0000000;
    s3[4] = (((s4 >> 24) & 0xf) << 16) | 0xa8000100;
    s3[5] = 0xb8000808;
    s3 += 6;

    /* loop 2: two blocks, each a record pair and three words */
    for (i = 0; i < 2; i++) {
        p = f_021b38(20);
        a1 = ((unsigned int)p >> 24) & 0xf;
        a1 = (a1 << 16) | 0x10000000;
        a2 = ((unsigned int)i * 64) & 0xffff;
        a3 = (unsigned int)i * 64 + 64;
        a3 = a3 < 121 ? a3 : 121;
        a3 &= 0xffff;
        t1 = (unsigned int)i * 128 + 128;
        t1 = t1 < 241 ? t1 : 241;
        t1 &= 0xffff;
        t2 = ((unsigned int)p & s1) | 0x01000000;
        Put8(p, 4, a2);
        Put8(p, 5, a2 >> 8);
        Put8(p, 0, ((unsigned int)i * 128) & 0xffff);
        Put8(p, 1, (((unsigned int)i * 128) & 0xffff) >> 8);
        Put8(p, 2, 0);
        Put8(p, 3, 0);
        Put8(p, 6, 0);
        Put8(p, 7, 0);
        p2 = p + 10;
        Put8(p2, 2, 0x88);
        Put8(p2, 5, a3 >> 8);
        Put8(p2, 1, t1 >> 8);
        Put8(p2, 3, 0);
        Put8(p2, 4, a3);
        Put8(p2, 6, 0x44);
        Put8(p2, 7, 0);
        Put8(p2, 0, t1);
        s3[0] = a1;
        s3[1] = t2;
        s3[2] = 0x04060002;
        s3 += 3;
    }

    /* a block of zeros, with the fixed colour words */
    p = f_021b38(20);
    a1 = (((unsigned int)p >> 24) & 0xf) << 16 | 0x10000000;
    a2 = ((unsigned int)p & s1) | 0x01000000;
    p2 = p + 10;
    for (n = 0; n < 8; n++)
        Put8(p, n, 0);
    Put8(p2, 2, 0x44);
    Put8(p2, 0, 0x78);
    Put8(p2, 3, 0);
    Put8(p2, 4, 0x3c);
    Put8(p2, 5, 0);
    Put8(p2, 6, 0x22);
    Put8(p2, 7, 0);
    Put8(p2, 1, 0);
    t0 = 0x21000001;
    t1 = 0xdf0002aa;
    t2 = 0xe0ffffff;
    t3 = 0xe1ffffff;
    s0 = 0x580000ff;
    a3 = 0x12800100;
    s3[0] = a1;
    s3[1] = a2;
    s3[2] = 0x04060002;
    s3[3] = 0xc6000000;
    s3[4] = t0;
    s3[5] = 0x1e000000;
    s3[6] = t1;
    s3[7] = t2;
    s3[8] = t3;
    s3[9] = 0x04060002;
    s3[10] = (unsigned int)D_27ec7c;
    s3[11] = a3;
    s3 += 12;
    col = (unsigned int)D_27ec7c;
    col = col | (col << 8) | (col << 16) | 0x55000000;
    s3[0] = col;
    s3[1] = s0;
    s3 += 2;

    /* the step loop: one 64-byte block per fade step, up to D_1d5a80 steps */
    s8 = 0xcb000000;
    for (i = 0; i < D_1d5a80; i++) {
        s3[0] = s8;
        p = f_021b38(20);
        a2 = (unsigned int)p;
        a1 = ((unsigned int)p >> 24) & 0xf;
        p[4] = 1;
        p2 = p + 10;
        Put8(p2, 4, 61);
        Put8(p2, 6, 34);
        Put8(p2, 0, 60);
        s3[1] = (a1 << 16) | s6;
        s3[2] = ((a2 & s1) | s4);
        s3[3] = s5;
        s3 += 4;
    }

    /* the end block: the cursor after the list is returned */
    s3 = f_02dba8(s3);
    s3[0] = 0x20000001;
    v = f_021d38();
    s3[1] = (v & s1) | 0x9c000000;
    s3[2] = (((v >> 24) & 0xf) << 16) | 0x9d000200;
    s3[3] = 0xd2000000;
    s3[4] = D_1d5a8c;
    s3[5] = 0x2700ffff;
    return (int)(s3 + 21);
}
