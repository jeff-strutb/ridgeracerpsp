/* Compiler-identification control set, batch 1: small leaf and call-through functions.
   Not filed into real TUs; this file only answers "which psp-gcc, which flags". */

extern int D_23c1b0;
extern char D_23c1a8[];
extern int D_27f09c;
extern char D_1a62b0[];

void f_0992fc(void);
void f_115f8c(int, void *, int);
void f_029a18(int *);
void f_04a580(int *);
void f_0935c4(int, int);
void f_028eb4(void);
void f_0ce068(int, int);
void f_0f6ff0(int);

/* @implements 0x001554 us f_001554 */
void f_001554(void) { f_0992fc(); }

/* @implements 0x016280 us f_016280 */
void f_016280(int *p, int a, int b)
{
    p[2] = a;
    p[0] = b;
    p[1] = 0;
}

/* @implements 0x022b78 us f_022b78 */
void f_022b78(void) { f_115f8c(0, D_23c1a8, D_23c1b0); }

/* @implements 0x0299f8 us f_0299f8 */
void f_0299f8(int *p, int a)
{
    *p = a;
    f_029a18(p);
}

/* @implements 0x076e30 us f_076e30 */
void f_076e30(int *p)
{
    *p = (int)D_1a62b0;
    f_04a580(p);
}

/* @implements 0x093640 us f_093640 */
void f_093640(void) { f_0935c4(1, 0xffff); }

/* @implements 0x0942f0 us f_0942f0 */
void f_0942f0(void) { f_0f6ff0(D_27f09c); }

/* @implements 0x0a65c4 us f_0a65c4 */
float f_0a65c4(float *v)
{
    float r;
    __asm__("lv.q C000.q, 0(%1)\n\tvdot.t S020.s, C000.t, C000.t\n\tvsqrt.s S000.s, S020.s\n\tsv.s S000.s, %0"
            : "=m"(r) : "r"(v));
    return r;
}

/* @implements 0x0cd4d0 us f_0cd4d0 */
void f_0cd4d0(int a)
{
    f_028eb4();
    f_0ce068(1, a);
}

/* @implements 0x0f6438 us f_0f6438 */
int f_0f6438(char *p)
{
    int *q = *(int **)(p + 132);
    if (q)
        return q[2];
    return 0;
}
