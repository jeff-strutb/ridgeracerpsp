/* Compiler-identification control set, batch 3. */

/* ---- 0x026efc: nested clear loops over a short grid ---- */
struct Row26e { char pad[40]; short v[7]; char pad2[26]; };
struct G26e { int on; char pad[36]; struct Row26e row[8]; unsigned char flag[7]; };

/* @implements 0x026efc us f_026efc */
void f_026efc(struct G26e *g)
{
    int i, j;
    if (g->on) {
        for (i = 0; i < 6; i++) {
            g->flag[i] = 1;
            for (j = 0; j < 8; j++)
                g->row[j].v[i] = 0;
        }
        for (j = 0; j < 8; j++)
            g->row[j].v[6] = 1;
        g->flag[6] = 0;
    }
}

/* ---- 0x02fecc ---- */
extern int D_2400d4;
extern int D_2402d0;
void f_02dfb4(int);

/* @implements 0x02fecc us f_02fecc */
void f_02fecc(void)
{
    if (D_2400d4 > 180) {
        f_02dfb4(1);
        D_2402d0 = 0;
    }
}

/* ---- 0x064454: string-returning accessor. Retail is C++: the 8 trailing bytes are an EH landing pad
   (jal _Unwind_Resume = f_166df8). The same body built with cc1plus (Str returned by value,
   empty-dtor Alloc temporary) is EXACT; in C, sched1 interblock hoists the a1/a2 argument setup above
   the branches (no EH edges to stop it), so this C version stays DIFF. ---- */
struct Str064 { int w[4]; };
struct B064 { int a; int h; };
struct A064 { char pad[8]; unsigned char named; char pad2[3]; struct B064 *b; int id; int pad3; const char *str; char name[4]; };
int f_15c098(int, int, int);
void f_05a3e8(struct Str064 *, int, void *);
void f_05e4a8(struct Str064 *, const char *);

/* @implements 0x064454 us f_064454 */
struct Str064 *f_064454(struct Str064 *r, struct A064 *a)
{
    if (a->named) {
        f_05e4a8(r, a->name);
        return r;
    }
    if (a->id == -1) {
        f_05e4a8(r, a->str);
        return r;
    }
    {
        char alloc;
        f_05a3e8(r, f_15c098(a->b->h, 7, a->id), &alloc);
        return r;
    }
}

/* ---- 0x0877a8: DIFF only through k. Retail selects k with sltiu/negu/and/addu (ifcvt store-flag-constants);
   psp-gcc 1.3.1 and 1.7.1 always emit movz here, and retail contains no movz/movn anywhere. ---- */
struct P087 { char pad[9]; unsigned char active; char pad2[18]; int dt; int t0; char pad3[12]; int t1; char pad4[44]; char a[84]; char b[4]; };
int f_086350(struct P087 *, void *);
int f_085344(void *, void *);
void f_088138(struct P087 *);
void f_0854ec(struct P087 *, int);

/* @implements 0x0877a8 us f_0877a8 */
int f_0877a8(struct P087 *p, unsigned char quick)
{
    char buf[192];
    int k = quick ? 1000000 : 30000000;
    int r;
    if (!p->active)
        return 0;
    r = f_086350(p, buf);
    if (r < 0)
        return r;
    if (f_085344(buf, p->a))
        p->t0 = 1000000;
    else if ((p->t0 -= p->dt) < 0) {
        f_088138(p);
        p->t0 = 30000000;
        f_0854ec(p, 9);
        return 1;
    }
    if (f_085344(buf, p->b))
        p->t1 = k;
    else if ((p->t1 -= p->dt) < 0) {
        f_088138(p);
        p->t1 = 30000000;
        f_0854ec(p, 9);
        return 1;
    }
    return 1;
}

/* ---- 0x0b20d8 ---- */
int f_0b2120(int, int, int, float *);
extern const float D_1ac7e0;

/* @implements 0x0b20d8 us f_0b20d8 */
int f_0b20d8(int a, int b, int c, float *out)
{
    float t[2];
    int r = f_0b2120(a, b, c, t);
    out[0] = t[0];
    out[1] = 0.0f;
    out[2] = t[1];
    out[3] = D_1ac7e0;
    return r;
}

/* ---- 0x0ec8b8 ---- */
struct V0ec { int x[4]; };
struct S0ec { char pad[48]; struct V0ec v; };
struct T0ec { char pad[256]; struct V0ec a[8]; struct V0ec b[8]; };
void f_0a2a00(struct S0ec *, struct V0ec *);

static __inline__ void v0ec_copy(struct V0ec *d, const struct V0ec *s) { *d = *s; }

/* @implements 0x0ec8b8 us f_0ec8b8 */
struct S0ec *f_0ec8b8(struct S0ec *s, struct T0ec *t, int i)
{
    f_0a2a00(s, &t->b[i]);
    v0ec_copy(&s->v, &t->a[i]);
    return s;
}

/* ---- 0x0f1aa0 ---- */
struct Q0f1 { char pad[124]; int f124; };
struct P0f1 { char pad[24]; int f24; char p1[8]; int f36; char p2[48]; int f88; struct Q0f1 *q; char p3[4]; int f100; };
struct G0f1 { char pad[32]; int f32; char p1[12]; int f48; char p2[4]; int f56; char p3[44]; int f104; };
extern struct G0f1 *D_2408f0;
extern int D_27eccc;
void f_0f24ec(struct P0f1 *);

/* @implements 0x0f1aa0 us f_0f1aa0 */
int f_0f1aa0(struct P0f1 *p)
{
    struct G0f1 *g;
    if (p->f24 == 0)
        p->f36 = 1;
    f_0f24ec(p);
    g = D_2408f0;
    if (g->f32 <= 0) {
        g->f56 = 3;
        D_27eccc = 3;
        p->q->f124 = 3;
        p->f88 = 5;
        p->f100 = 120;
        p->f36 = 0;
    }
    g->f104 = p->q->f124;
    g->f48 += 50;
    return 0;
}

/* ---- 0x10ad64 ---- */
struct Q10a { char pad[4]; unsigned short id; unsigned short n; };
struct P10a { char pad[412]; short f412; char p1[2]; void *buf0; void *buf1; struct Q10a *q; };
extern char D_1b25c0[];
int f_10b874(struct P10a *);
void *f_153558(int);
void f_10b5c4(struct P10a *);
void f_10bbdc(struct P10a *);
void f_093f90(const char *, int, int);

/* @implements 0x10ad64 us f_10ad64 */
int f_10ad64(struct P10a *p)
{
    struct Q10a *q;
    int n;
    if (f_10b874(p))
        return -1;
    q = p->q;
    n = q->n;
    p->buf0 = f_153558(n * 4);
    p->buf1 = f_153558(n * 4);
    f_10b5c4(p);
    f_10bbdc(p);
    p->f412 = 100;
    f_093f90(D_1b25c0, q->id, n);
    return 0;
}

/* ---- 0x10dd2c ---- */
struct E10d { char pad[10]; short f10; char p1[16]; int f28; };
extern struct E10d D_27f174[];
int f_10e120(int);

/* @implements 0x10dd2c us f_10dd2c */
int f_10dd2c(unsigned char i, short v)
{
    struct E10d *e = &D_27f174[i];
    if (!f_10e120(i))
        return 0x80000007;
    e->f10 = v;
    e->f28 = 1;
    return 0;
}

/* ---- 0x115304 ---- */
struct Y115 { int a, b, c; };
struct X115 { char pad[8]; struct Y115 y; };
struct X115 *f_10e0b4(int);
void f_11b30c(int);
void f_11b274(int, int);
void f_11b2c0(int, int);

/* @implements 0x115304 us f_115304 */
int f_115304(unsigned char i)
{
    struct Y115 *y = &f_10e0b4(i)->y;
    f_11b30c(y->a - 1);
    f_11b274(1, 1);
    f_11b2c0(y->b, y->c);
    return 0;
}

/* ---- 0x126cf4 ---- */
extern int D_28cb78;
extern int D_28cb7c;
void f_16e4a0(int);

/* @implements 0x126cf4 us f_126cf4 */
void f_126cf4(void)
{
    if (--D_28cb78 == 0)
        f_16e4a0(D_28cb7c);
}

/* ---- 0x131910 ---- */
struct O131 { const void *vt; };
extern const char D_1b5d10[];
void f_14bd20(struct O131 *);
void f_1521a8(struct O131 *);

/* @implements 0x131910 us f_131910 */
void f_131910(struct O131 *o)
{
    o->vt = D_1b5d10;
    f_14bd20(o);
    f_1521a8(o);
}
