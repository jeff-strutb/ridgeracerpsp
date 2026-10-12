/* @cflags: -fexceptions */
/* Compiler-identification control set, batch 5. */

/* ---- 0x002b34: buffer setup ---- */
struct Pr2b { int lo, hi; };
struct B2b { int base; int ptr; int aligned; int zero; int h; struct Pr2b pr; };
int f_002260(int);
int f_0022e4(int);
struct Pr2b f_0996b0(int, int);
int f_099684(int, int, int);
int f_125e14(int);

/* @implements 0x002b34 us f_002b34 */
void f_002b34(struct B2b *p, int a, int b, int h, int n)
{
    int sz;
    p->h = h;
    p->zero = 0;
    p->base = f_002260(a);
    sz = f_0022e4(p->base);
    if (p->h) {
        /* statement expression: the call result goes through one stack
           temporary, as a C++ TARGET_EXPR would */
        p->pr = ({ f_0996b0(p->h, 0); });
        p->ptr = f_099684(p->h, sz + 127, n);
    } else {
        p->ptr = f_125e14(sz + 127);
    }
    p->aligned = (p->ptr + 127) & ~127;
}

/* ---- 0x063068: destructor (C++ in retail; cleanup runs the base dtor) ---- */
struct O063 { const void *vt; char pad[28]; char mem[4]; };
extern const char D_1a3fb0[];
void f_0604dc(void *);
void f_04e8d8(struct O063 *);

static __inline__ void o063_base_dtor(struct O063 **pp) { f_04e8d8(*pp); }

/* @implements 0x063068 us f_063068 */
void f_063068(struct O063 *p)
{
    p->vt = D_1a3fb0;
    {
        struct O063 *self __attribute__((cleanup(o063_base_dtor))) = p;
        f_0604dc(self->mem);
    }
}

/* ---- 0x06b624: virtual queries + std::string temporary ---- */
struct Str06b { char *p; };
struct Obj06b;
struct Vt06b {
    char pad0[24];
    int (*kind)(struct Obj06b *);
    char pad1[84 - 28];
    void (*name)(struct Str06b *, struct Obj06b *);
    char pad2[92 - 88];
    int (*count)(struct Obj06b *);
};
struct Obj06b { struct Vt06b *vt; };
struct H06b { struct Obj06b *obj; };
extern const char D_1a4d14;
int f_15e078(const char *, const char *);
void f_05db84(struct Str06b *);

/* libstdc++ v3 (GCC 3.x) basic_string::c_str(): size(), then traits::assign of _S_terminal */
static __inline__ void chr06b_assign(char *c1, const char *c2) { *c1 = *c2; }
static __inline__ char *str06b_c_str(struct Str06b *s)
{
    int n = ((int *)s->p)[-3];
    chr06b_assign(&s->p[n], &D_1a4d14);
    return s->p;
}

static __inline__ void str06b_dtor(struct Str06b *s) { f_05db84(s); }

/* @implements 0x06b624 us f_06b624 */
int f_06b624(void *self, const char *name, struct H06b *h)
{
    int r = -1;
    if (h->obj->vt->kind(h->obj) != 7) {
        r = h->obj->vt->count(h->obj) - 1;
    } else if (name) {
        struct Str06b t __attribute__((cleanup(str06b_dtor)));
        h->obj->vt->name(&t, h->obj);
        r = f_15e078(name, str06b_c_str(&t));
    }
    return r;
}

/* ---- 0x086744 ---- */
struct S086 { char pad[1160]; unsigned char b[4]; char sub[4]; };
void f_12668c(void *, int, int *);
void f_0866a4(struct S086 *, int, unsigned char *, int *);

/* @implements 0x086744 us f_086744 */
void f_086744(struct S086 *p, int a, unsigned char c, int d, int *e)
{
    p->b[0] = c;
    p->b[1] = 1;
    p->b[2] = 1;
    p->b[3] = 1;
    f_12668c(p->sub, d, e);
    f_0866a4(p, a, p->b, e + 1);
}

/* ---- 0x091d9c ---- */
struct G091 { char pad[1888]; int on; char pad2[8]; float v; };
struct A091 { char pad[16]; int n; };
struct G091 *f_0903c4(struct A091 *);

/* @implements 0x091d9c us f_091d9c */
int f_091d9c(struct A091 *a)
{
    float v;
    if (f_0903c4(a)->on == 0)
        return 0;
    v = f_0903c4(a)->v;
    if (v < 1.5f)
        return 0;
    if (v < 3.0f)
        return a->n % 100 < 20;
    return (a->n % 100 < 100) * 2;
}

/* ---- 0x094768: StreamBase start ---- */
struct C094 { int state; };
extern struct C094 *D_242ca4;
struct S094 { char pad[8]; int h; int arg; char name[4]; };
int f_095538(struct S094 *, int);
int f_110f58(int, char *, int);
void f_0956dc(int, int);
void f_093f90(const char *, ...);

/* @implements 0x094768 us f_094768 */
int f_094768(struct S094 *s, int x)
{
    int r;
    if (D_242ca4->state != 1)
        return -1;
    if (f_095538(s, x) < 0) {
        f_093f90("StreamBase: Start Failed!\n");
        return -1;
    }
    r = f_110f58(s->h, s->name, s->arg);
    if (r >= 0) {
        f_0956dc(s->h, r);
        return 0;
    }
    f_093f90("StreamBase: Start Failed! nuSoundStreamStart ERROR CODE:0x%x\n", r);
    return -1;
}

/* ---- 0x097004 ---- */
extern char D_242dec[];
void f_096e84(void *);
void f_096f2c(void *);

/* @implements 0x097004 us f_097004 */
void f_097004(int a, int b)
{
    if (b == 0xffff && a == 1)
        f_096e84(D_242dec);
    if (b == 0xffff && a == 0)
        f_096f2c(D_242dec);
}

/* ---- 0x09d678: 36-byte struct from a 16-byte one ---- */
struct M09d { int m[9]; };
struct Q09d { int q[4]; };
void f_09c314(struct Q09d *);
void f_09d858(struct M09d *, struct Q09d *);

/* @implements 0x09d678 us f_09d678 */
void f_09d678(struct M09d *out)
{
    struct M09d m;
    struct Q09d q;
    f_09c314(&q);
    f_09d858(&m, &q);
    *out = m;
}

/* ---- 0x0cb940: node pool append ---- */
struct L0cb;
struct N0cb { void *obj; signed char a, b; char pad[2]; struct N0cb *next; };
struct L0cb { int x; struct N0cb *head; struct N0cb *tail; };
struct O0cb { int x, y; struct L0cb *list; };
extern struct N0cb *D_254178;

/* @implements 0x0cb940 us f_0cb940 */
void f_0cb940(void *self, struct O0cb *o, int a, int b)
{
    struct L0cb *l = o->list;
    D_254178->b = a;
    D_254178->a = b;
    D_254178->next = 0;
    D_254178->obj = o;
    if (l->tail == 0) {
        l->head = D_254178;
        l->tail = D_254178;
    } else {
        l->tail->next = D_254178;
        l->tail = D_254178;
    }
    D_254178++;
}

/* ---- 0x0e6334: sched1 hoists the store holding the base pointer's REG_DEAD,
   so retail's first store (offset 32) is the last one in source order ---- */
struct S0e6 { int m[8]; int a, b; };
void f_0daf30(struct S0e6 *);

/* @implements 0x0e6334 us f_0e6334 */
void f_0e6334(struct S0e6 *p)
{
    p->b = 0;
    p->m[0] = 0;
    p->m[1] = 0;
    p->m[2] = 0;
    p->m[3] = 0;
    p->m[4] = 0;
    p->m[5] = 0;
    p->m[6] = 0;
    p->m[7] = 0;
    p->a = 0;
    f_0daf30(p);
}

/* ---- 0x13c8b0: virtual call forwarding two 8-byte structs by value.
   Retail also saves unused s0/s1 and has 16 extra frame bytes (C++ EH residue). ---- */
struct V13c { int x, y; };
struct O13c;
struct Vt13c { char pad[28]; void (*m)(struct O13c *, struct V13c, struct V13c); };
struct O13c { struct Vt13c *vt; };

/* @implements 0x13c8b0 us f_13c8b0 */
void f_13c8b0(struct O13c *o, struct V13c a, struct V13c b)
{
    o->vt->m(o, a, b);
}

/* ---- 0x140a5c: forward a struct copied field by field (inline C++ copy ctor)
   and a char. Retail also saves unused s0/s1 and has 16 extra frame bytes. ---- */
struct K140 { int a; char b; };
void f_14133c(void *, struct K140, int, signed char);

/* @implements 0x140a5c us f_140a5c */
void f_140a5c(void *o, struct K140 *k, int c, signed char d)
{
    struct K140 t;
    t.a = k->a;
    t.b = k->b;
    f_14133c(o, t, c, d);
}
