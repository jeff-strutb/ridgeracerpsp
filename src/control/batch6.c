/* Compiler-identification control set, batch 6. */

struct VT { int (*f[16])(); };

/* ---- 0x01b91c ---- */
struct S1b4 { char pad[16]; int v; };
struct P1b9 {
    int code;
    unsigned char b4, b5, b6, b7;
    void *obj;
    int pad12;
    struct S1b4 *info;
    int pad20[3];
    int val;
};
struct G1e3 { char pad[1480]; int code; };
extern struct G1e3 D_1e38f4;
int f_006680(struct G1e3 *);
void f_006728(struct G1e3 *);
int f_01a900(struct P1b9 *);
int f_0193a8(void *);
void f_019228(void *);
void f_1521a8(void *);

/* @implements 0x01b91c us f_01b91c */
int f_01b91c(struct P1b9 *p)
{
    int r = f_006680(&D_1e38f4);
    int code;
    void *o;
    if (r) {
    f_006728(&D_1e38f4);
    code = D_1e38f4.code;
    p->b4 = 0;
    p->b5 = 0;
    p->b6 = 0;
    p->b7 = 0;
    p->code = code;
    switch (code) {
    case 0x80110301:
    case 0x80110302:
        p->b4 = 1;
        break;
    case 0x80110306:
        p->b7 = 1;
        break;
    case 0x80110307:
        p->b6 = 1;
        break;
    }
    if (f_01a900(p)) {
        if (!f_0193a8(p->obj)) {
            p->val = p->info->v;
        } else {
            p->b7 = 1;
            p->code = 0x80110306;
        }
    }
    f_1521a8(p->info);
    o = p->obj;
    if (o) {
        f_019228(o);
        f_1521a8(o);
    }
    }
    return r;
}

/* ---- 0x03dd70 ---- */
extern char D_1a2720[];
void f_038bd0(void *);

/* @implements 0x03dd70 us f_03dd70 */
void f_03dd70(void **p)
{
    f_038bd0(p);
    *p = D_1a2720;
}

/* ---- 0x07a930 ---- */
extern char D_1a6a50[];
void f_078098(void *);

/* @implements 0x07a930 us f_07a930 */
void f_07a930(void **p)
{
    *p = D_1a6a50;
    f_078098(p);
    f_1521a8(p);
}

/* ---- 0x07ee80 ---- */
struct O7e { struct VT *vt; };
struct P7e { char pad[3152]; struct O7e *o; };
void f_07ebdc(struct P7e *);
void f_07ecb8(struct P7e *);
void f_07edd4(struct P7e *);

/* @implements 0x07ee80 us f_07ee80 */
void f_07ee80(struct P7e *p)
{
    struct O7e *o;
    f_07ebdc(p);
    f_07ecb8(p);
    f_07edd4(p);
    o = p->o;
    o->vt->f[5](o);
}

/* ---- 0x08e0c8 ---- */
struct F1d8 { char pad[11]; unsigned char b11, b12; };
struct F240 { char pad[20]; int busy; };
extern struct F1d8 *D_1d88a0;
extern struct F240 *D_2407fc;
void f_08e160(void);
void f_08e388(void *);
void f_08e5d4(void *);
void f_08e7a8(void *);
void f_08e97c(void *);
void f_08ee48(void *);
void f_08ef74(void *);
void f_08ea3c(void *);

/* @implements 0x08e0c8 us f_08e0c8 */
void f_08e0c8(void *p)
{
    struct F1d8 *g = D_1d88a0;
    if (!g->b11 && !g->b12) {
        f_08e160();
        f_08e388(p);
        f_08e5d4(p);
        f_08e7a8(p);
        f_08e97c(p);
        if (!D_2407fc->busy) {
            f_08ee48(p);
            f_08ef74(p);
        }
    }
    f_08ea3c(p);
}

/* ---- 0x0cdf38 ---- */
float f_0cd3cc(float);
float *f_028e84(void);
void f_0ce0a8(float *);

/* @implements 0x0cdf38 us f_0cdf38 */
void f_0cdf38(float a, float b, float c, float d, float e, float g, float n, float f)
{
    float t, tb, A, B;
    float *m;
    d = d + d;
    g = g + g;
    t = f_0cd3cc(a);
    tb = t * b;
    A = -(f + n) / (f - n);
    B = f * -2.0f * n / (f - n);
    d = d - c;
    m = f_028e84();
    m[10] = A;
    m[11] = -1.0f;
    m[15] = m[13] = m[12] = m[7] = m[6] = m[4] = m[3] = m[2] = m[1] = 0.0f;
    m[14] = B;
    m[5] = 1.0f / t * e;
    e = e - g;
    m[0] = 1.0f / tb * c;
    m[8] = d + 1.0f;
    m[9] = e - 1.0f;
    f_0ce0a8(m);
}

/* ---- 0x0f2eac ---- */
extern float D_1d5d94;
extern float D_27ecec, D_27ecf0;

/* @implements 0x0f2eac us f_0f2eac */
void f_0f2eac(int a, int b)
{
    if (b == 0xffff && a == 1) {
        D_27ecec = D_1d5d94 * 105.0f;
        D_27ecf0 = D_1d5d94 * 75.0f;
    }
}

/* ---- 0x0fa640 ---- */
extern char D_1b00b4[];
int f_10ed90(unsigned short, unsigned short, int, int, float);
long long f_16401c(float);
void f_093f90(const char *, ...);

/* @implements 0x0fa640 us f_0fa640 */
int f_0fa640(int a, unsigned short id, unsigned short ch, int d, float f)
{
    int r = f_10ed90(id, ch, d, a, f);
    if (r < 0) {
        f_093f90(D_1b00b4, r, id, ch, f_16401c(f));
        return -1;
    }
    return 0;
}

/* ---- 0x10aff0 ---- */
struct E10b { short a; short key; char pad[44]; };
struct T10b { short a; unsigned short count; int off; };
struct P10b { char pad[424]; char *base; };
extern char D_1b26f0[], D_1b273c[];
struct T10b *f_10b8f4(struct P10b *, unsigned short);

/* @implements 0x10aff0 us f_10aff0 */
int f_10aff0(struct P10b *p, unsigned short id, short key)
{
    struct T10b *t = f_10b8f4(p, id);
    struct E10b *e, *q;
    short lo, hi, mid;
    if (!t) {
        f_093f90(D_1b273c, id);
        return -1;
    }
    e = (struct E10b *)(p->base + t->off);
    hi = t->count - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        q = &e[mid];
        if (q->key == key)
            return mid;
        if (q->key < key)
            lo = mid + 1;
        else
            hi = mid;
    }
    if (lo == hi) {
        q = &e[lo];
        if (q->key == key)
            return lo;
    }
    f_093f90(D_1b26f0, id, key);
    return -1;
}

/* ---- 0x12f1c4 (newlib ratio) ----
   NOT TAGGED: config/us/funcs.csv gives 0x12f1c4 a size of 320, but the range holds two
   functions: ratio (0x12f1c4..0x12f263, 160 bytes) and _mprec_log10 at 0x12f264 (own prologue).
   This body was scored while tagged: all 40 words of 0x12f1c4..0x12f263 matched under both
   1.3.1 and 1.7.1; only the 40 words belonging to 0x12f264 differed (map mis-cut). */
struct Bigint { struct Bigint *next; int k, maxwds, sign, wds; };
union du { double d; unsigned int i[2]; };
double f_12ef30(struct Bigint *, int *);

double f_12f1c4(struct Bigint *a, struct Bigint *b)
{
    union du da, db;
    int k, ka, kb;
    da.d = f_12ef30(a, &ka);
    db.d = f_12ef30(b, &kb);
    k = ka - kb + 32 * (a->wds - b->wds);
    if (k > 0)
        da.i[1] += k * 0x100000;
    else {
        k = -k;
        db.i[1] += k * 0x100000;
    }
    return da.d / db.d;
}

/* ---- 0x14ccc4 ---- */
struct SB {
    struct VT *vt;
    char pad4[12];
    unsigned char flag;
    char pad17[3];
    unsigned char *eback;
    unsigned char *gptr;
    char pad28[8];
    int cnt;
};

/* @implements 0x14ccc4 us f_14ccc4 */
int f_14ccc4(struct SB *s)
{
    if (s->gptr && s->eback < s->gptr) {
        s->gptr--;
        if (s->cnt && s->flag)
            s->cnt--;
        return *s->gptr;
    }
    return s->vt->f[11](s, -1);
}
