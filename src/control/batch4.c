/* Compiler-identification control set, batch 4. */

/* ---- 0x001014 ---- */
extern int D_1d9c24;
int f_16e6d0(void);
int f_16e6c8(void);

/* @implements 0x001014 us f_001014 */
int f_001014(void)
{
    int t, z;
    t = f_16e6d0();
    t -= D_1d9c24;
    t -= f_16e6c8();
    z = t % 286 < 201;
    return t / 286 + (z == 0);
}

/* ---- 0x01dac0 ---- */
struct S01d { char pad[16]; short state; char pad2[66]; int x84; };
struct G01d { char pad[11]; unsigned char a, b; };
extern struct G01d *D_1d88a0;

static __inline__ int g01d_busy(void) { return D_1d88a0->a || D_1d88a0->b; }

/* @implements 0x01dac0 us f_01dac0 */
void f_01dac0(struct S01d *p, int f)
{
    if (p->state == 0) {
        p->state = g01d_busy() | f;
    } else if (p->state == 1) {
        p->state = g01d_busy() | f;
        if (p->state == 0)
            p->state = 2;
    } else {
        p->state = 0;
    }
    if (p->x84 == 0)
        p->state = 1;
}

/* ---- 0x024930 ---- */
struct H024 {
    char pad0[4];
    unsigned short n4;
    unsigned char type6;
    char pad7[7];
    unsigned short flags;
    int p16;
    int p20;
    int p24;
};

/* @implements 0x024930 us f_024930 */
void f_024930(struct H024 *h)
{
    unsigned short fl = h->flags;
    if (fl & 1)
        return;
    if (h->p16) {
        if (h->type6 == 3)
            h->n4 = (h->n4 + 7) >> 3;
        else
            h->n4 = (h->n4 + 15) >> 4;
        h->p20 = h->p16 = h->p16 + (int)h;
    }
    if (h->p24)
        h->p24 += (int)h;
    h->flags = fl | 1;
}

/* ---- 0x028b3c ---- */
/* @implements 0x028b3c us f_028b3c */
void f_028b3c(void *m)
{
    __asm__ volatile(
        "sv.q C500.q, 0(%0)\n\tsv.q C510.q, 16(%0)\n\tsv.q C520.q, 32(%0)\n\tsv.q C530.q, 48(%0)\n\t"
        "sv.q C600.q, 64(%0)\n\tsv.q C610.q, 80(%0)\n\tsv.q C620.q, 96(%0)\n\tsv.q C630.q, 112(%0)\n\t"
        "sv.q C700.q, 128(%0)\n\tsv.q C710.q, 144(%0)\n\tsv.q C720.q, 160(%0)\n\tsv.q C730.q, 176(%0)"
        : : "r"(m) : "memory");
}

/* ---- 0x068ab8 ---- */
struct O068;
struct VT068 { char pad[36]; int (*get)(struct O068 *); };
struct O068 { struct VT068 *vt; };
struct Y068 { char pad[44]; struct O068 *o; };
void f_15f6dc(int);
void f_05daa4(void *, int);

/* @implements 0x068ab8 us f_068ab8 */
void *f_068ab8(void *self, struct Y068 *y)
{
    struct O068 *o = y->o;
    f_15f6dc(o->vt->get(o));
    f_05daa4(self, 0);
    return self;
}

/* ---- 0x07a838 ----
   C++ constructor with an EH landing pad (base dtor f_078098 + _Unwind_Resume f_166df8 on throw);
   C cannot express the throw-only cleanup, so this stays DIFF. */
struct C07a { void *vt; };
extern char D_1a6a50[];
void f_078078(struct C07a *);
void f_07a968(struct C07a *);

/* @implements 0x07a838 us f_07a838 */
void f_07a838(struct C07a *p)
{
    f_078078(p);
    p->vt = D_1a6a50;
    f_07a968(p);
}

/* ---- 0x0c644c ---- */
struct R0c6 { float x, y, w, h; };
struct N0c6 { short h; unsigned short off; };
struct T0c6 { char pad[12]; struct N0c6 *leaves; char *nodes; };
extern const float D_1ad3c4;
extern const float D_1ad3c8;

/* @implements 0x0c644c us f_0c644c */
int f_0c644c(struct T0c6 *t, struct R0c6 *r, struct N0c6 *n, int depth, float x, float y)
{
    short h = n->h;
    short *cell = (short *)(t->nodes + (h & 0x3ff) * 32);
    int ret = depth;
    if ((h >> 10) == 0) {
        struct R0c6 c;
        int i, j, k;
        ret = 0;
        c.w = r->w * D_1ad3c4;
        c.h = r->h * D_1ad3c4;
        i = (x - r->x) * (D_1ad3c8 / c.w);
        if (i < 0)
            i = 0;
        if (i > 3)
            i = 3;
        j = (y - r->y) * (D_1ad3c8 / c.h);
        if (j < 0)
            j = 0;
        if (j > 3)
            j = 3;
        k = cell[j * 4 + i];
        if (k >= 0) {
            c.x = r->x + i * c.w;
            c.y = r->y + j * c.h;
            ret = f_0c644c(t, &c, &t->leaves[k + n->off], depth + 1, x, y);
        }
    }
    return ret;
}

/* ---- 0x0e6854 ---- */
struct B0e6 { char pad[4]; int on; char pad2[36]; int tab[1]; };
struct L0e6 { unsigned char idx; char pad[159]; };
extern int D_27e880;
extern int D_27e884;
extern int D_27e888;
extern char D_1aed20[];
struct B0e6 *f_017970(void);
void f_07ac1c(void *);
int f_07ac48(void *, void *, struct L0e6 *);
void f_022d00(int, int);
int f_02347c(int);

/* @implements 0x0e6854 us f_0e6854 */
void f_0e6854(void)
{
    char buf[16];
    struct L0e6 l;
    int *tab;

    if (f_017970()->on == 0)
        return;
    tab = f_017970()->tab;
    f_07ac1c(buf);
    f_07ac48(buf, D_1aed20, &l);
    D_27e880 = 0x0a000280;
    f_022d00(tab[l.idx], D_27e880);
    D_27e884 = f_02347c(D_27e880);
    D_27e888 = 1;
}

/* ---- 0x102cf0 ---- */
struct P102;
struct VT102 { char pad[16]; int (*fn)(struct P102 *, int); };
struct P102 { struct VT102 *vt; char pad4[4]; void *x8; char pad12[16]; unsigned char done; };
struct W102 { char pad[32]; int x32; };
extern struct W102 *D_2407fc;
int f_101b54(struct P102 *);
void f_101cf4(struct P102 *, int, int *, int *, int *);
void f_04c248(void *, int, int);

/* @implements 0x102cf0 us f_102cf0 */
int f_102cf0(struct P102 *p)
{
    int a, b, c;
    if (!f_101b54(p))
        return 0;
    f_101cf4(p, D_2407fc->x32, &a, &b, &c);
    if (a < 6 && !p->done) {
        void *o = p->x8;
        f_04c248(o, p->vt->fn(p, 0), 1);
        p->done = 1;
    }
    return 0;
}

/* ---- 0x110e54 ---- */
struct E110 { char pad0[16]; short s16; char pad18[86]; int i104; char pad108[32]; int x140; char pad144[32]; float f176; char pad180[16]; };
extern int D_291a44;
extern struct E110 D_291980[];
extern const float D_1b2e78;
extern int D_281ec0;
int f_16e978(void);
int f_16e5c0(const char *, int (*)(int, int, void *), void *);
int f_16e980(int);
int f_110e2c(int, int, void *);

/* @implements 0x110e54 us f_110e54 */
int f_110e54(int n)
{
    int i;
    if (n >= 2)
        return 0x80000000;
    D_291a44 = n;
    for (i = 0; i < n; i++) {
        D_291980[i].s16 = 0;
        D_291980[i].i104 = -1;
        D_291980[i].f176 = D_1b2e78;
    }
    if (f_16e978())
        D_291980[0].x140 = 0;
    else
        D_291980[0].x140 = 1;
    D_281ec0 = f_16e5c0("UMD Check", f_110e2c, 0);
    f_16e980(D_281ec0);
    return 0;
}

/* ---- 0x14df20 ----
   C++ (refcounted rep dispose) inside an EH region; retail ends with a landing pad. In plain C the
   calls do not end basic blocks, so sched1 sinks rep = d - 12 below the first call. */
int f_16e498(void);
void f_16e4a0(int);
void f_15075c(void *, void *);

struct Rep14d { int len; int cap; volatile int refcount; };

static __inline__ int xadd14d(volatile int *m, int v)
{
    int r;
    int s = f_16e498();
    r = *m;
    *m += v;
    f_16e4a0(s);
    return r;
}

static __inline__ void rep14d_dispose(struct Rep14d *r, void *a)
{
    if (xadd14d(&r->refcount, -1) <= 0)
        f_15075c(r, a);
}

/* @implements 0x14df20 us f_14df20 */
void f_14df20(char **p)
{
    char a;
    rep14d_dispose((struct Rep14d *)(*p - 12), &a);
}

/* ---- 0x119dc8 ----
   NOT TAGGED: the map entry for 0x119dc8 (216 bytes) covers two functions; a second one with its
   own prologue starts at 0x119e38. The body below is the first function (0x119dc8..0x119e37).
   Its 28 words match retail only with -frename-registers (or -O3), not at -O2. */
extern int D_28bca8[];
int f_16e680(int, int);

int f_119dc8(unsigned int ch, int len)
{
    if (ch >= 4)
        return 0x80440010;
    if (len < 64 || len > 0xffc0)
        return 0x80440011;
    if (len & 0x3f)
        return 0x80440011;
    return f_16e680(D_28bca8[ch], len);
}
