/* The disc vertex table and command buffer (retail 0x0e71f0 to 0x0e764c): the guarded start
   (0x0e71f0) and its wrapper (0x0e7234), and the builder (0x0e7254) that fills the quad's two
   corner vertices at D_27e984 and the disc's 81 vertices at D_27e890 (the centre, then 80 points
   on a circle of radius 127, three signed bytes each), then writes the 72-word command buffer
   D_27e990 that draws them and flushes it to memory. The scale the disc is drawn with is set by
   DiscDisplayList.c. */

extern "C" {
float cosf(float x);
float sinf(float x);
int sceKernelDcacheWritebackRange(void *p, unsigned int size);
void f_0e7254(void *p);
}

extern signed char D_27e984[];  /* the quad's corners: two vertices, three bytes each */
extern signed char D_27e890[];  /* the disc's vertices: 81 of three bytes */
extern unsigned int D_27e990[]; /* the command buffer, 72 words */
extern char D_27eab0[];         /* the argument of the builder */

/* The vertex address command (0x01) for a pointer into the 24-bit address space. */
static inline unsigned int Va(const void *p)
{
    return 0x01000000 | ((unsigned int)p & 0x00ffffff);
}

/* The base command (0x10) for the high address bits of a pointer. */
static inline unsigned int Ba(const void *p)
{
    return 0x10000000 | ((((int)p) >> 24) & 0xf) << 16;
}

/* @implements 0x0e71f0 us f_0e71f0
   WHAT IT DOES: Builds the disc when called with 1 and 0xffff; does nothing for other
   arguments. */
extern "C" void f_0e71f0(int id, int mask)
{
    if (mask == 0xffff && id == 1)
        f_0e7254(D_27eab0);
}

/* @implements 0x0e7234 us f_0e7234
   WHAT IT DOES: Calls f_0e71f0 with 1 and 0xffff. */
extern "C" void f_0e7234(void)
{
    f_0e71f0(1, 0xffff);
}

/* @draft 0x0e7254 us f_0e7254
   WHAT IT DOES: Writes the quad's two corner vertices, the disc's 81 vertices (the centre
   (0, 0), then 80 points at angles 2 pi i / 79 scaled to 127), then the 72 command words of the
   disc's command buffer, and writes the buffer back to memory for 288 bytes. */
extern "C" void f_0e7254(void *unused)
{
    unsigned int *d = D_27e990;
    int k = 0;
    int off = 0;
    int i;
    signed char *v;

    D_27e984[1] = -127;
    D_27e984[2] = 0;
    D_27e984[0] = -127;
    D_27e984[4] = 127;
    D_27e984[5] = 0;
    D_27e984[3] = 127;

    do {
        v = D_27e890 + off;
        v[0] = 0;
        v[1] = 0;
        v[2] = 0;
        v += 3;
        for (i = 0; i < 80; i++) {
            float a = (float)i / 79.0f;
            a = a + a;
            a = a * 3.1415920f;
            v[0] = (int)(cosf(a) * 127.0f);
            v[2] = 0;
            v[1] = (int)(sinf(a) * 127.0f);
            v += 3;
        }
        off += 243;
        k++;
    } while (k <= 0);

    d[12] = 0x3c000000;
    d[25] = 0x3e000000;
    d[0] = 0x3a000001;
    d[4] = 0x3a000005;
    d[9] = 0x3bbfbf77;
    d[10] = 0x3bbf9000;
    d[11] = 0x3b000000;
    d[21] = 0x3d3f0000;
    d[24] = 0x3d000000;
    d[1] = 0x3b000000;
    d[2] = 0x3b000000;
    d[3] = 0x3b000000;
    d[5] = 0x3b000000;
    d[6] = 0x3b000000;
    d[7] = 0x3b000000;
    d[8] = 0x3b000000;
    d[13] = 0x3d3f0000;
    d[14] = 0x3d000000;
    d[15] = 0x3d000000;
    d[16] = 0x3d000000;
    d[17] = 0x3d3f0000;
    d[18] = 0x3d000000;
    d[19] = 0x3d000000;
    d[20] = 0x3d000000;
    d[44] = 0x45450000;
    d[46] = 0x23000000;
    d[48] = 0x17000000;
    d[53] = 0x1d000000;
    d[22] = 0x3d000000;
    d[55] = 0xe8ffffff;
    d[23] = 0x3d000000;
    d[60] = 0x04060002;
    d[45] = 0x46450000;
    d[61] = 0xdd020202;
    d[47] = 0x21000000;
    d[26] = 0x3f3f0000;
    d[27] = 0x3f000000;
    d[28] = 0x3f000000;
    d[29] = 0x3f000000;
    d[30] = 0x3f000000;
    d[31] = 0x3f3f0000;
    d[40] = 0x3f000000;
    d[41] = 0x3f3f0000;
    d[42] = 0x42437000;
    d[43] = 0x43c30800;
    d[49] = 0x1e000000;
    d[50] = 0x55ffffff;
    d[51] = 0x580000ff;
    d[52] = 0x12000080;
    d[54] = 0x24000001;
    d[57] = 0xdcff0001;
    d[58] = Ba(D_27e984);
    d[59] = Va(D_27e984);
    d[62] = 0xdcffff01;
    d[63] = Ba(D_27e890);
    d[56] = 0xdd020202;
    d[64] = Va(D_27e890);
    d[65] = 0x04050051;
    d[67] = 0xdd000000;
    d[32] = 0x3f000000;
    d[68] = 0xdcff0003;
    d[33] = 0x3f000000;
    d[69] = 0x1e000001;
    d[34] = 0x3f000000;
    d[70] = 0x21000001;
    d[35] = 0x3f000000;
    d[36] = 0x3f3f0000;
    d[37] = 0x3f000000;
    d[38] = 0x3f000000;
    d[39] = 0x3f000000;
    d[66] = 0xe8000000;
    d[71] = 0x0b000000;
    sceKernelDcacheWritebackRange(D_27e990, 288);
}
