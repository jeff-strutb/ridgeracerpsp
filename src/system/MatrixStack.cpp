/* The matrix stack object files (retail 0x028b30 to 0x028f80). The game keeps its 4x4 matrices
   in VFPU matrix registers while it draws; M700 holds the current transform. One buffer of
   64 byte matrices, handed over by the main loop job at start up, is cut into four stacks laid
   end to end, each with its own top pointer. One stack saves and restores M700 itself; the
   other three hold their current matrix in memory, which can be read, written, pushed and
   popped. Also here: saving and restoring the VFPU matrices M500 to M730 around code that
   uses them. */

extern "C" {
void f_02842c(void);
}

struct Matrix {
    int m[16];
};

extern char D_23c7e0[];
extern Matrix *D_23c7c0;
extern Matrix *D_23c7c4;
extern Matrix *D_23c7c8;
extern Matrix *D_23c7cc;
extern Matrix *D_23c7d0;

/* @implements 0x028b30 us f_028b30
   WHAT IT DOES: Returns the save area used for the VFPU matrices. */
void *f_028b30(void)
{
    return D_23c7e0;
}

/* @implements 0x028b3c us f_028b3c
   WHAT IT DOES: Saves the twelve VFPU columns of M500, M600 and M700 to the given 192 byte area.
   VFPU code, written as inline assembly. */
void f_028b3c(void *save)
{
    __asm__ volatile(
        ".set push\n\t.set noreorder\n\t"
        "sv.q C500, 0($4)\n\tsv.q C510, 16($4)\n\tsv.q C520, 32($4)\n\tsv.q C530, 48($4)\n\t"
        "sv.q C600, 64($4)\n\tsv.q C610, 80($4)\n\tsv.q C620, 96($4)\n\tsv.q C630, 112($4)\n\t"
        "sv.q C700, 128($4)\n\tsv.q C710, 144($4)\n\tsv.q C720, 160($4)\n\tsv.q C730, 176($4)\n\t"
        ".set pop"
        : : "r"(save) : "memory");
}

/* @implements 0x028b74 us f_028b74
   WHAT IT DOES: Restores M500, M600 and M700 from an area written by f_028b3c.
   VFPU code, written as inline assembly. */
void f_028b74(const void *save)
{
    __asm__ volatile(
        "lv.q C500, 0($4)\n\tlv.q C510, 16($4)\n\tlv.q C520, 32($4)\n\tlv.q C530, 48($4)\n\t"
        "lv.q C600, 64($4)\n\tlv.q C610, 80($4)\n\tlv.q C620, 96($4)\n\tlv.q C630, 112($4)\n\t"
        "lv.q C700, 128($4)\n\tlv.q C710, 144($4)\n\tlv.q C720, 160($4)\n\tlv.q C730, 176($4)"
        : : "r"(save) : "memory");
}

/* @implements 0x028bac us f_028bac
   WHAT IT DOES: Sets up the four matrix stacks in one buffer: clears every matrix, places the
   stacks one after another with the given depths, and loads the identity into M700. */
void f_028bac(Matrix *buf, int n0, int n1, int n2, int n3)
{
    int i;
    Matrix *base;

    D_23c7d0 = buf;
    for (i = 0; i < n0 + n1 + n2 + n3; i++) {
        buf->m[0] = 0; buf->m[1] = 0; buf->m[2] = 0; buf->m[3] = 0;
        buf->m[4] = 0; buf->m[5] = 0; buf->m[6] = 0; buf->m[7] = 0;
        buf->m[8] = 0; buf->m[9] = 0; buf->m[10] = 0; buf->m[11] = 0;
        buf->m[12] = 0; buf->m[13] = 0; buf->m[14] = 0; buf->m[15] = 0;
        buf++;
    }
    base = D_23c7d0;
    D_23c7c4 = &base[n0];
    D_23c7c8 = &base[n0 + n1];
    D_23c7cc = &base[n0 + n1 + n2];
    D_23c7c0 = base;
    f_02842c();
}

void f_028d94(Matrix *m);
void f_028e9c(const Matrix *m);
void f_028eb4(const Matrix *m);
void f_028ef8(const Matrix *m);
void f_028f3c(const Matrix *m);

/* @implements 0x028c70 us f_028c70
   WHAT IT DOES: Pushes the current transform: saves M700 on its stack. */
void f_028c70(void)
{
    f_028d94(D_23c7c8);
    D_23c7c8++;
}

/* @implements 0x028ca8 us f_028ca8
   WHAT IT DOES: Pops the current transform back into M700. */
void f_028ca8(void)
{
    f_028e9c(--D_23c7c8);
}

/* @implements 0x028cd4 us f_028cd4
   WHAT IT DOES: Pushes the second stack (its new top starts as garbage until written). */
void f_028cd4(void)
{
    D_23c7c4++;
}

/* @implements 0x028ce8 us f_028ce8
   WHAT IT DOES: Pops the second stack; the new top is written back onto itself. */
void f_028ce8(void)
{
    f_028eb4(--D_23c7c4);
}

/* @implements 0x028d14 us f_028d14
   WHAT IT DOES: Pushes the first stack. */
void f_028d14(void)
{
    D_23c7c0++;
}

/* @implements 0x028d28 us f_028d28
   WHAT IT DOES: Pops the first stack; the new top is written back onto itself. */
void f_028d28(void)
{
    f_028ef8(--D_23c7c0);
}

/* @implements 0x028d54 us f_028d54
   WHAT IT DOES: Pushes the fourth stack. */
void f_028d54(void)
{
    D_23c7cc++;
}

/* @implements 0x028d68 us f_028d68
   WHAT IT DOES: Pops the fourth stack; the new top is written back onto itself. */
void f_028d68(void)
{
    f_028f3c(--D_23c7cc);
}

/* @implements 0x028d94 us f_028d94
   WHAT IT DOES: Stores M700 to memory. VFPU code, written as inline assembly. */
void f_028d94(Matrix *m)
{
    __asm__ volatile(".set push\n\t.set noreorder\n\t"
                     "sv.q C700, 0($4)\n\tsv.q C710, 16($4)\n\tsv.q C720, 32($4)\n\tsv.q C730, 48($4)\n\t"
                     ".set pop"
                     : : "r"(m) : "memory");
}

/* @implements 0x028dac us f_028dac
   WHAT IT DOES: Copies the top of the second stack out. */
void f_028dac(Matrix *out)
{
    *out = *D_23c7c4;
}

/* @implements 0x028df0 us f_028df0
   WHAT IT DOES: Copies the top of the first stack out. */
void f_028df0(Matrix *out)
{
    *out = *D_23c7c0;
}

/* @implements 0x028e34 us f_028e34
   WHAT IT DOES: Copies the top of the fourth stack out. */
void f_028e34(Matrix *out)
{
    *out = *D_23c7cc;
}

/* @implements 0x028e78 us f_028e78
   WHAT IT DOES: Returns the top of the second stack. */
Matrix *f_028e78(void)
{
    return D_23c7c4;
}

/* @implements 0x028e84 us f_028e84
   WHAT IT DOES: Returns the top of the first stack. */
Matrix *f_028e84(void)
{
    return D_23c7c0;
}

/* @implements 0x028e90 us f_028e90
   WHAT IT DOES: Returns the top of the fourth stack. */
Matrix *f_028e90(void)
{
    return D_23c7cc;
}

/* @implements 0x028e9c us f_028e9c
   WHAT IT DOES: Loads M700 from memory. VFPU code, written as inline assembly. */
void f_028e9c(const Matrix *m)
{
    __asm__ volatile("lv.q C700, 0($4)\n\tlv.q C710, 16($4)\n\tlv.q C720, 32($4)\n\tlv.q C730, 48($4)"
                     : : "r"(m) : "memory");
}

/* @implements 0x028eb4 us f_028eb4
   WHAT IT DOES: Sets the top of the second stack to the given matrix. */
void f_028eb4(const Matrix *m)
{
    *D_23c7c4 = *m;
}

/* @implements 0x028ef8 us f_028ef8
   WHAT IT DOES: Sets the top of the first stack to the given matrix. */
void f_028ef8(const Matrix *m)
{
    *D_23c7c0 = *m;
}

/* @implements 0x028f3c us f_028f3c
   WHAT IT DOES: Sets the top of the fourth stack to the given matrix. */
void f_028f3c(const Matrix *m)
{
    *D_23c7cc = *m;
}
