/* The graphics system object file (retail 0x0213a0 to 0x021fd8): brings up the PSP graphics
   engine and owns the frame. Two display list buffers alternate, one per frame. Each frame's
   buffer holds a chain of recorded call lists, built front to back by the drawing code, while
   short lived vertex data is taken from the back of the same buffer. At the frame flip the
   chain of the finished buffer is called in order from one direct list, the screen buffers are
   swapped, and the other buffer is reset for the next frame. The object file also keeps where
   the draw, display and depth buffers sit in video memory, and can rebuild them for a 16 or
   32 bit pixel format. */

#include <stdlib.h>

extern "C" {
void sceKernelDcacheWritebackAll(void);
int sceDisplayWaitVblankStart(void);
void *sceGeEdramGetAddr(void);

void *f_125c4c(unsigned int align, unsigned int size);
int f_126f1c(const char *fmt, ...);
void f_115e98(void);
void f_115f60(void);
void f_115f8c(int cid, void *list, int size);
void f_116258(void);
int f_1165c4(void);
void f_1165dc(int mode, int what);
void f_1164c8(void *list);
void f_1166d4(int state);
void f_116898(int state);
void f_11610c(const void *matrix);
void f_116b04(int type, const void *matrix);
void f_117b98(int psm, unsigned int fbp, int width);
void f_117c90(int psm, unsigned int fbp, int width);
void f_117cf8(unsigned int zbp, int width);
void f_117d74(int width, int height, unsigned int dispbp, int dispbw);
void f_117e34(int mode);
void *f_117e9c(void);
void f_117f20(int x, int y, int width, int height);
void f_117fb4(int x, int y);
void f_1178a8(int mode);
void f_1178d0(int mode);
void f_1178f8(int mode);
void f_1180c8(int x, int y);
void f_11839c(int mode);
void f_1183f0(int mode);
void f_118738(int op, int src);
void f_11875c(int op, int src);
void f_1187d8(int op, int src);
void f_1187fc(int mode, float value);
void f_118858(int sfail, int zfail, int zpass);
void f_118928(void);
void f_118a20(float u, float v);
void f_118a54(float u, float v);
void f_118c48(int func, int ref, int mask);
void f_118c80(int func);
void f_118ca0(int mask);
void f_118d04(int x, int y, int w, int h);
void f_118e30(int op, int src, int dst, unsigned int srcfix, unsigned int dstfix);
unsigned int *f_022bc0(void *p);
void f_022bd4(void);
}

unsigned int f_021d38(void);

/* The two display list buffers, the size of each, which one is being filled this frame, the
   end of the open call list chunk, and the low end of the data taken from the back. */
void *D_23c1a8[2];
unsigned int D_23c1b0;
int D_23c1b4;
unsigned int *D_23c1b8;
char *D_23c1bc;

/* The pixel format, which screen buffer is drawn this frame, the buffers' offsets in video
   memory (draw, display, depth) and their addresses, and whether depth is off for the
   current target. */
int D_23c1c0;
int D_23c1c4;
unsigned int D_23c1c8[3];
void *D_23c1d4[3];
int D_23c1e0;

/* The dither matrix and the identity matrix. */
int D_1d1980[16] = {
    -4, 0, -3, 1,
    2, -2, 3, -1,
    -3, 1, -4, 0,
    3, -1, 2, -2,
};
float D_1d19c0[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

/* @implements 0x0213a0 us f_0213a0
   WHAT IT DOES: brings up the graphics engine. Allocates the two display list buffers, each
   half of the given size (stopping the game with a message if memory runs out), places the
   draw, display and depth buffers in video memory for the 16 bit format, and sets the whole
   default render state: viewport, scissor, depth range and test, culling, shading, blending,
   texture filtering and wrapping, dithering and identity matrices. It then turns the display
   on, waits for the vertical blank and opens the first frame's list buffer. */
void f_0213a0(unsigned int size)
{
    size = (size >> 1) & ~15;
    D_23c1b0 = size;
    D_23c1a8[0] = f_125c4c(64, size);
    D_23c1a8[1] = f_125c4c(64, size);
    if (D_23c1a8[0] == 0 || D_23c1a8[1] == 0) {
        f_126f1c("Error(PSPInit) : Displaylist buffer memory not allocated.");
        abort();
    }
    f_115e98();
    f_115f8c(0, D_23c1a8[0], D_23c1b0);
    D_23c1c4 = 0;
    f_117b98(1, 0, 512);
    D_23c1c0 = 1;
    D_23c1c8[0] = 0;
    D_23c1d4[0] = sceGeEdramGetAddr();
    f_117d74(480, 272, 0x44000, 512);
    D_23c1c8[1] = 0x44000;
    D_23c1d4[1] = (char *)sceGeEdramGetAddr() + 0x44000;
    f_117cf8(0x88000, 512);
    D_23c1c8[2] = 0x88000;
    D_23c1d4[2] = (char *)sceGeEdramGetAddr() + 0x88000;
    f_1180c8(1808, 1912);
    f_117f20(2048, 2048, 480, 272);
    f_1178a8(0);
    f_1178f8(0);
    f_1178d0(0);
    f_118c48(6, 0, 255);
    f_1166d4(0);
    f_118c80(7);
    f_118ca0(0);
    f_1166d4(1);
    f_117fb4(0xffff, 0);
    f_118d04(0, 0, 480, 272);
    f_1166d4(2);
    f_116898(3);
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
    f_11839c(0);
    f_1166d4(5);
    f_1183f0(1);
    f_11610c(D_1d1980);
    f_1166d4(6);
    f_116898(7);
    f_1166d4(8);
    f_116898(9);
    f_118738(7, 1);
    f_11875c(0, 1);
    f_1187d8(1, 1);
    f_1187fc(0, 0.0f);
    f_118858(0, 0, 0);
    f_118a54(0.0f, 0.0f);
    f_118a20(1.0f, 1.0f);
    f_116898(10);
    f_116898(15);
    f_116898(16);
    f_116898(17);
    f_116898(18);
    f_116898(19);
    f_116898(20);
    f_116b04(0, D_1d19c0);
    f_116b04(1, D_1d19c0);
    f_116b04(2, D_1d19c0);
    f_116b04(3, D_1d19c0);
    f_117e34(1);
    f_116258();
    f_1165dc(0, 0);
    sceDisplayWaitVblankStart();
    D_23c1b4 = 0;
    f_022bd4();
}

/* @implements 0x0216d8 us f_0216d8
   WHAT IT DOES: returns where the next recorded call list starts: just past the open chunk's
   link word. */
unsigned int *f_0216d8(void)
{
    return D_23c1b8 + 1;
}

/* Close the open chunk at p: link it to a new chunk aligned after p, which becomes the open
   chunk. */
static inline void Link(void *p)
{
    unsigned int **prev;

    p = f_022bc0(p);
    prev = (unsigned int **)D_23c1b8;
    D_23c1b8 = (unsigned int *)p;
    *prev = (unsigned int *)p;
}

/* @implements 0x0216e8 us f_0216e8
   WHAT IT DOES: closes a call list that was written by hand: puts a return command at the given
   end, links the open chunk to a new chunk aligned just after it, and makes that the open
   chunk. */
void f_0216e8(unsigned int *p)
{
    *p = 0x0b000000;
    Link(p + 1);
}

/* @implements 0x021720 us f_021720
   WHAT IT DOES: starts recording a call list into the open chunk of this frame's buffer. */
void f_021720(void)
{
    f_115f8c(1, D_23c1b8 + 1, D_23c1b0);
}

/* The end of a recorded call list: link the open chunk to a new chunk after the list, then
   finish the list. */
static inline void EndList(void)
{
    Link((char *)D_23c1b8 + f_1165c4() + 64);
    f_116258();
}

/* @implements 0x021750 us f_021750
   WHAT IT DOES: finishes the call list being recorded and chains it into this frame. */
void f_021750(void)
{
    EndList();
}

/* Rounds a width up to a multiple of 64 pixels. */
static inline unsigned int Align64(unsigned int w)
{
    return (w + 63) >> 6 << 6;
}

/* @implements 0x021798 us f_021798
   WHAT IT DOES: writes the graphics engine commands that point drawing at another target
   (pixel format, colour buffer and width, and the depth buffer, or depth writes and depth test
   off when there is none) and set the scissor to the target's size. Returns the end of the
   commands written. */
unsigned int *f_021798(int psm, unsigned int width, int height, unsigned int fbp, void *zbp)
{
    unsigned int *p = D_23c1b8 + 1;
    unsigned int bw = Align64(width);

    *p++ = 0xd2000000 | psm;
    *p++ = 0x9c000000 | (fbp & 0xffffff);
    *p++ = 0x9d000000 | (bw | ((fbp >> 24) << 16));
    if (zbp == 0) {
        *p++ = 0xe7000001;
        *p++ = 0x23000000;
        D_23c1e0 = 1;
    } else {
        *p++ = 0x9e000000 | ((unsigned int)zbp & 0xffffff);
        *p++ = 0x9f000000 | (bw | (((unsigned int)zbp >> 24) << 16));
        D_23c1e0 = 0;
    }
    *p++ = 0xd4000000;
    *p++ = 0xd5000000 | (width - 1) | ((height - 1) << 10);
    return p;
}

/* @implements 0x021880 us f_021880
   WHAT IT DOES: writes the commands that point drawing back at the screen's back buffer
   (restoring the depth buffer, or depth writes and test if they were turned off), resets the
   scissor to the full screen, and closes the hand written call list there. */
void f_021880(unsigned int *p)
{
    unsigned int fbp = f_021d38();
    unsigned int **prev;

    *p++ = 0xd2000000 | D_23c1c0;
    *p++ = 0x9c000000 | (fbp & 0xffffff);
    *p++ = 0x9d000000 | ((fbp >> 24) << 16) | 512;
    if (D_23c1e0) {
        *p++ = 0xe7000000;
        *p++ = 0x23000001;
    } else {
        unsigned int zbp = D_23c1c8[2];

        *p++ = 0x9e000000 | (zbp & 0xffffff);
        *p++ = 0x9f000000 | ((zbp >> 24) << 16) | 512;
    }
    *p++ = 0xd4000000;
    *p++ = 0xd5000000 | 479 | (271 << 10);
    *p++ = 0xcc000000;
    *p++ = 0x0b000000;
    p = f_022bc0(p);
    prev = (unsigned int **)D_23c1b8;
    D_23c1b8 = p;
    *prev = p;
}

/* @implements 0x02199c us f_02199c
   WHAT IT DOES: starts recording a call list that draws into another target: sets the pixel
   format and colour buffer, the depth buffer (or turns depth writes and test off when there is
   none), and a scissor of the target's size. */
void f_02199c(int psm, unsigned int width, int height, unsigned int fbp, unsigned int zbp)
{
    unsigned int bw;

    f_115f8c(1, D_23c1b8 + 1, D_23c1b0);
    bw = (width + 63) >> 6 << 6;
    f_117c90(psm, fbp, bw);
    if (zbp) {
        f_117cf8(zbp, bw);
        D_23c1e0 = 0;
    } else {
        f_118ca0(1);
        f_116898(1);
        D_23c1e0 = 1;
    }
    f_118d04(0, 0, width, height);
}

/* @implements 0x021a80 us f_021a80
   WHAT IT DOES: ends a call list started by f_02199c: points drawing back at the screen's back
   buffer, restores the depth buffer (or depth writes and test), resets the full screen
   scissor, and chains the list into this frame. */
void f_021a80(void)
{
    f_117c90(D_23c1c0, f_021d38(), 512);
    if (D_23c1e0) {
        f_118ca0(0);
        f_1166d4(1);
    } else {
        f_117cf8(D_23c1c8[2], 512);
    }
    f_118d04(0, 0, 480, 272);
    f_118928();
    EndList();
}

/* @implements 0x021b38 us f_021b38
   WHAT IT DOES: takes a block of the given size (rounded up to 64 bytes) from the back of this
   frame's list buffer, for vertex data that lives until the frame is drawn. */
char *f_021b38(unsigned int size)
{
    D_23c1bc -= (size + 63) >> 6 << 6;
    return D_23c1bc;
}

/* @implements 0x021b58 us f_021b58
   WHAT IT DOES: returns how much of this frame's list buffer is in use. */
int f_021b58(void)
{
    return D_23c1b0 + ((char *)D_23c1b8 - D_23c1bc) + 4;
}

/* @implements 0x021b80 us f_021b80
   WHAT IT DOES: returns how much of this frame's list buffer is still free. */
int f_021b80(void)
{
    return D_23c1bc - (char *)D_23c1b8 - 4;
}

/* @implements 0x021b9c us f_021b9c
   WHAT IT DOES: waits until the graphics engine has finished drawing. */
void f_021b9c(void)
{
    f_1165dc(0, 0);
}

/* @implements 0x021bbc us f_021bbc
   WHAT IT DOES: the frame flip. Writes the data cache back, waits for the previous frame's
   drawing and for the vertical blank, swaps the screen buffers, then ends this frame's chain
   of call lists and draws it from one direct list, and opens the other list buffer for the
   next frame. */
void f_021bbc(void)
{
    unsigned int *p;

    sceKernelDcacheWritebackAll();
    f_1165dc(0, 0);
    sceDisplayWaitVblankStart();
    D_23c1c4 = (unsigned int)f_117e9c() != D_23c1c8[0];
    *D_23c1b8 = 0;
    p = (unsigned int *)D_23c1a8[D_23c1b4];
    p = f_022bc0(p);
    f_115f8c(0, D_23c1b8 + 1, D_23c1b0);
    while (*p) {
        f_1164c8(p + 1);
        p = (unsigned int *)*p;
    }
    f_116258();
    f_022bd4();
}

/* @implements 0x021c9c us f_021c9c
   WHAT IT DOES: waits for the vertical blank. */
void f_021c9c(void)
{
    sceDisplayWaitVblankStart();
}

/* @implements 0x021cb8 us f_021cb8
   WHAT IT DOES: shuts the graphics engine down: waits for drawing to finish, frees both list
   buffers and stops the engine. */
void f_021cb8(void)
{
    f_021b9c();
    free(D_23c1a8[0]);
    free(D_23c1a8[1]);
    f_115f60();
}

/* @implements 0x021cf8 us f_021cf8
   WHAT IT DOES: returns the video memory offset of the buffer shown this frame. */
unsigned int f_021cf8(void)
{
    return D_23c1c8[D_23c1c4];
}

/* @implements 0x021d18 us f_021d18
   WHAT IT DOES: returns the address of the buffer shown this frame. */
void *f_021d18(void)
{
    return D_23c1d4[D_23c1c4];
}

/* @implements 0x021d38 us f_021d38
   WHAT IT DOES: returns the video memory offset of the buffer being drawn this frame. */
unsigned int f_021d38(void)
{
    return D_23c1c8[D_23c1c4 ^ 1];
}

/* @implements 0x021d5c us f_021d5c
   WHAT IT DOES: returns the address of the buffer being drawn this frame. */
void *f_021d5c(void)
{
    return D_23c1d4[D_23c1c4 ^ 1];
}

/* @implements 0x021d80 us f_021d80
   WHAT IT DOES: the same as f_021d38, under another name. */
unsigned int f_021d80(void)
{
    return D_23c1c8[D_23c1c4 ^ 1];
}

/* @implements 0x021da4 us f_021da4
   WHAT IT DOES: the same as f_021d5c, under another name. */
void *f_021da4(void)
{
    return D_23c1d4[D_23c1c4 ^ 1];
}

/* @implements 0x021dc8 us f_021dc8
   WHAT IT DOES: the same as f_021cf8, under another name. */
unsigned int f_021dc8(void)
{
    return D_23c1c8[D_23c1c4];
}

/* @implements 0x021de8 us f_021de8
   WHAT IT DOES: the same as f_021d18, under another name. */
void *f_021de8(void)
{
    return D_23c1d4[D_23c1c4];
}

/* @implements 0x021e08 us f_021e08
   WHAT IT DOES: returns the video memory offset of the depth buffer. */
unsigned int f_021e08(void)
{
    return D_23c1c8[2];
}

/* @implements 0x021e14 us f_021e14
   WHAT IT DOES: returns the address of the depth buffer. */
void *f_021e14(void)
{
    return D_23c1d4[2];
}

/* @implements 0x021e20 us f_021e20
   WHAT IT DOES: switches the screen to another pixel format. Flips twice so nothing is being
   drawn, fills all of video memory with the given value, then, through a temporary direct
   list, lays the draw, display and depth buffers out again (twice as far apart for the 32 bit
   format) and flips once more. */
void f_021e20(int psm, unsigned int fill)
{
    unsigned int *v;
    void *list;
    int i;

    f_021bbc();
    f_021bbc();
    v = (unsigned int *)sceGeEdramGetAddr();
    for (i = 0; i < 0x44000; i++)
        *v++ = fill;
    list = f_125c4c(64, 1024);
    f_115f8c(0, list, 1024);
    if (psm == 3) {
        f_117b98(3, 0, 512);
        D_23c1c8[0] = 0;
        D_23c1d4[0] = sceGeEdramGetAddr();
        f_117d74(480, 272, 0x88000, 512);
        D_23c1c8[1] = 0x88000;
        D_23c1d4[1] = (char *)sceGeEdramGetAddr() + 0x88000;
        f_117cf8(0x110000, 512);
        D_23c1c8[2] = 0x110000;
        D_23c1d4[2] = (char *)sceGeEdramGetAddr() + 0x110000;
    } else {
        f_117b98(psm, 0, 512);
        D_23c1c8[0] = 0;
        D_23c1d4[0] = sceGeEdramGetAddr();
        f_117d74(480, 272, 0x44000, 512);
        D_23c1c8[1] = 0x44000;
        D_23c1d4[1] = (char *)sceGeEdramGetAddr() + 0x44000;
        f_117cf8(0x88000, 512);
        D_23c1c8[2] = 0x88000;
        D_23c1d4[2] = (char *)sceGeEdramGetAddr() + 0x88000;
    }
    D_23c1c0 = psm;
    f_116258();
    f_1165dc(0, 0);
    f_021bbc();
    free(list);
}
