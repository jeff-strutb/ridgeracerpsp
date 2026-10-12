/* Compiler-identification control set, batch 2: medium functions (loops, branches, float args, struct copy). */

struct E01d { char b[1904]; };
struct Q01d { int a; int n; };
extern struct E01d D_249330[];
void f_0c9b54(struct E01d *);

/* @implements 0x01d934 us f_01d934 */
void f_01d934(struct Q01d *q)
{
    int i;
    for (i = 0; i < q->n; i++)
        f_0c9b54(&D_249330[i]);
}

int f_15c07c(void *, int, int);
void f_15ca34(void *, int, int, float);

/* @implements 0x04b464 us f_04b464 */
void f_04b464(void **p, int b, float f)
{
    void *s = *p;
    f_15ca34(s, f_15c07c(s, 3, b), 0, f);
}

struct G092 { char pad[1796]; int mode; int val; };
struct H092 { int a, b, c; };
extern struct H092 D_242c90;
struct G092 *f_0903c4(int);
int f_093c78(int, int);
int f_093c8c(int, int);

/* @implements 0x0922a0 us f_0922a0 */
int f_0922a0(int a)
{
    if (f_0903c4(a)->mode == 1) {
        if (f_093c78(D_242c90.c, f_0903c4(a)->val))
            return 2 - (f_093c8c(D_242c90.c, f_0903c4(a)->val) == 0);
    }
    return 0;
}

struct M0a6 { int m[16]; };
void f_09bb28(struct M0a6 *, struct M0a6 *, int);

/* @implements 0x0a6d90 us f_0a6d90 */
struct M0a6 *f_0a6d90(struct M0a6 *p, int b)
{
    struct M0a6 t;
    f_09bb28(&t, p, b);
    *p = t;
    return p;
}
