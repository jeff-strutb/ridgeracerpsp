/* Record-table helpers of the object file at retail 0x0db2c4 to 0x0e14d8: calls with fixed
   trailing arguments, and walks over a table of 16-byte records and of 32-byte slots. */

/* A record list: a header whose halfword at +2 is the count, and 16-byte records at +8. */
struct RecHdr {
    short m0;
    unsigned short count;
};

struct Rec16 {
    char m0[6];
    unsigned char key;      /* +6 */
    char m7[9];
};

struct RecList {
    RecHdr *hdr;            /* +0 */
    int m4;
    Rec16 *recs;            /* +8 */
};

struct Flags {
    int m0, m4, m8;
    unsigned flags;         /* +12 */
};

struct Holder {
    Flags *inner;           /* +0 */
};

extern "C" void f_0df538(void *self, RecList *l, int i, int key);
extern "C" void f_0dedd0(void *slot, RecList *l, int arg, int i);

/* Matrix-stack and transform routines (VFPU, src/system). */
struct Matrix {
    float m[16];
};

extern "C" {
void f_02842c(void);
void f_0284bc(float a);
void f_0284fc(float a);
void f_02853c(float a);
void f_0287cc(float x, float y, float z);
void f_02884c(float x, float y, float z);
void f_028c70(void);
void f_028ca8(void);
void f_028d94(Matrix *m);
void f_028e9c(const Matrix *m);
}

/* Animation data (src/race/EventData.cpp): the header, the record list and the node stream,
   with the current frame at +24. */
struct AnimHdr {
    unsigned short flags;
    unsigned short count;   /* +2: record count */
    short m4;
    unsigned short frameSize;
    int m8;
    unsigned int mode;
};

struct AnimRec {
    short m0;
    short parent;           /* +2: -1 for a node with its own pose key */
    unsigned char kind;     /* +4 */
    char m5;
    unsigned char key;      /* +6: index into the pose key array */
    unsigned char flags;
    int start;
    int still;
};

struct AnimData {
    AnimHdr *hdr;           /* +0 */
    int *head;              /* +4: word 6 is the segment table offset */
    AnimRec *recs;          /* +8 */
    unsigned char *nodes;   /* +12 */
    int *tab;               /* +16: three key-track offsets per record, then their key counts */
    int m20;
    int frame;              /* +24 */
    float time;             /* +28 */
};

extern "C" unsigned char *f_0db0d0(AnimData *pb, int frame, int idx);
extern "C" unsigned char *f_0daf64(AnimData *pb, unsigned int frame, int idx);
extern "C" void f_0de508(void *a, AnimData *pb);
extern "C" void f_0e1e34(AnimData *pb, const unsigned char *p, unsigned short *x, unsigned short *y,
                         unsigned short *z);

/* A pose key (src/system/KeyBlend.c): translation, scale and three 16-bit angles. */
struct Key {
    float t[3];             /* +0 */
    float s[3];             /* +12 */
    short r[3];             /* +24 */
    unsigned short pad;
};

/* A float read from four unaligned bytes. */
/* A 16-bit angle (a full turn is 65536), read from two unaligned bytes. */
union Bytes2 {
    unsigned short v;
    unsigned char b[2];
};

union Bytes4 {
    float f;
    struct {
        unsigned char b0, b1, b2, b3;
    } b;
};

/* The 16-bit little-endian node index at p. */
static inline short Read16(const unsigned char *p)
{
    return (short)(p[0] | (p[1] << 8));
}

/* @implements 0x0db2c4 us f_0db2c4
   WHAT IT DOES: Walks the node stream of an animation at its current frame and stores each node's
   transform into the matrix array: -1 restarts from the identity (or the given base matrix), -2 ends;
   each node's record kind says whether its data is a scale, a rotation or a translation. */
extern "C" void f_0db2c4(AnimData *pb, Matrix *out, int useBase, Matrix *base)
{
    Bytes2 ax, ay, az;
    unsigned short rx, ry, rz;
    const unsigned char *p;
    short id;

    ax.v = 0;
    ay.v = 0;
    az.v = 0;
    f_028c70();
    if (!useBase)
        f_02842c();
    else
        f_028e9c(base);
    p = pb->nodes;
    while ((id = Read16(p)) != -2) {
        p += 2;
        if (id != -1) {
            unsigned char *d = f_0db0d0(pb, pb->frame, id);
            if (d) {
                AnimRec *rec = &pb->recs[id];
                switch (rec->kind) {
                case 0:
                    f_02884c((float)d[0], 1.0f, 1.0f);
                    break;
                case 1:
                    f_02884c(1.0f, (float)d[0], 1.0f);
                    break;
                case 2:
                    f_02884c(1.0f, 1.0f, (float)d[0]);
                    break;
                case 3: {
                    Bytes4 x, y, z;
                    x.b.b0 = d[0]; x.b.b1 = d[1]; x.b.b2 = d[2]; x.b.b3 = d[3];
                    d += 4;
                    y.b.b0 = d[0]; y.b.b1 = d[1]; y.b.b2 = d[2]; y.b.b3 = d[3];
                    d += 4;
                    z.b.b0 = d[0]; z.b.b1 = d[1]; z.b.b2 = d[2]; z.b.b3 = d[3];
                    f_02884c(x.f, y.f, z.f);
                    break;
                }
                case 4: {
                    ax.b[0] = d[0];
                    ax.b[1] = d[1];
                    {
                        unsigned short a = ax.v;
                        rx = a;
                    }
                    f_0284bc(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                }
                case 5: {
                    ay.b[0] = d[0];
                    ay.b[1] = d[1];
                    {
                        unsigned short a = ay.v;
                        rx = a;
                    }
                    f_0284fc(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                }
                case 6: {
                    az.b[0] = d[0];
                    az.b[1] = d[1];
                    {
                        unsigned short a = az.v;
                        rx = a;
                    }
                    f_02853c(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                }
                case 7: {
                    f_0e1e34(pb, d, &rx, &ry, &rz);
                    f_02853c(rz * 6.28318548f * (1.0f / 65536.0f));
                    f_0284fc(ry * 6.28318548f * (1.0f / 65536.0f));
                    f_0284bc(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                }
                case 8:
                    f_0287cc((float)d[0], 0.0f, 0.0f);
                    break;
                case 9:
                    f_0287cc(0.0f, (float)d[0], 0.0f);
                    break;
                case 10:
                    f_0287cc(0.0f, 0.0f, (float)d[0]);
                    break;
                case 11: {
                    Bytes4 x, y, z;
                    x.b.b0 = d[0]; x.b.b1 = d[1]; x.b.b2 = d[2]; x.b.b3 = d[3];
                    d += 4;
                    y.b.b0 = d[0]; y.b.b1 = d[1]; y.b.b2 = d[2]; y.b.b3 = d[3];
                    d += 4;
                    z.b.b0 = d[0]; z.b.b1 = d[1]; z.b.b2 = d[2]; z.b.b3 = d[3];
                    f_0287cc(x.f, y.f, z.f);
                    break;
                }
                }
                f_028d94(&out[id]);
            }
        } else {
            if (!useBase)
                f_02842c();
            else
                f_028e9c(base);
        }
    }
    f_028ca8();
}

/* @implements 0x0db824 us f_0db824
   WHAT IT DOES: Calls the 0x0db2c4 routine with the third and fourth arguments zero. */
extern "C" void f_0db824(AnimData *a, Matrix *b)
{
    f_0db2c4(a, b, 0, 0);
}

/* @implements 0x0db844 us f_0db844
   WHAT IT DOES: Calls the 0x0db2c4 routine with the third argument zero and the fourth passed on. */
extern "C" void f_0db844(AnimData *a, Matrix *b, Matrix *d)
{
    f_0db2c4(a, b, 0, d);
}

/* @implements 0x0db864 us f_0db864
   WHAT IT DOES: The same node walk as 0x0db2c4, starting from the identity, with a second animation
   supplying the translation for nodes of kind 7 (followed by that node's packed rotation); kinds 12
   to 15 store the transform unchanged. */
extern "C" void f_0db864(AnimData *pb, AnimData *pos, Matrix *out)
{
    Bytes2 ax, ay, az;
    unsigned short rx, ry, rz;
    const unsigned char *p;
    short id;

    f_028c70();
    f_02842c();
    ax.v = 0;
    ay.v = 0;
    az.v = 0;
    p = pb->nodes;
    while ((id = Read16(p)) != -2) {
        p += 2;
        if (id != -1) {
            unsigned char *d = f_0db0d0(pb, pb->frame, id);
            if (d) {
                unsigned char *t = f_0daf64(pos, pos->frame, id);
                AnimRec *rec = &pb->recs[id];
                switch (rec->kind) {
                case 0:
                    f_02884c((float)d[0], 1.0f, 1.0f);
                    break;
                case 1:
                    f_02884c(1.0f, (float)d[0], 1.0f);
                    break;
                case 2:
                    f_02884c(1.0f, 1.0f, (float)d[0]);
                    break;
                case 3: {
                    Bytes4 x, y, z;
                    x.b.b0 = d[0]; x.b.b1 = d[1]; x.b.b2 = d[2]; x.b.b3 = d[3];
                    d += 4;
                    y.b.b0 = d[0]; y.b.b1 = d[1]; y.b.b2 = d[2]; y.b.b3 = d[3];
                    d += 4;
                    z.b.b0 = d[0]; z.b.b1 = d[1]; z.b.b2 = d[2]; z.b.b3 = d[3];
                    f_02884c(x.f, y.f, z.f);
                    break;
                }
                case 4:
                    ax.b[0] = d[0];
                    ax.b[1] = d[1];
                    {
                        unsigned short a = ax.v;
                        rx = a;
                    }
                    f_0284bc(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                case 5:
                    ay.b[0] = d[0];
                    ay.b[1] = d[1];
                    {
                        unsigned short a = ay.v;
                        rx = a;
                    }
                    f_0284fc(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                case 6:
                    az.b[0] = d[0];
                    az.b[1] = d[1];
                    {
                        unsigned short a = az.v;
                        rx = a;
                    }
                    f_02853c(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                case 7: {
                    Bytes4 x, y, z;
                    x.b.b0 = t[0]; x.b.b1 = t[1]; x.b.b2 = t[2]; x.b.b3 = t[3];
                    t += 4;
                    y.b.b0 = t[0]; y.b.b1 = t[1]; y.b.b2 = t[2]; y.b.b3 = t[3];
                    t += 4;
                    z.b.b0 = t[0]; z.b.b1 = t[1]; z.b.b2 = t[2]; z.b.b3 = t[3];
                    f_0287cc(x.f, y.f, z.f);
                    f_0e1e34(pb, d, &rx, &ry, &rz);
                    f_02853c(rz * 6.28318548f * (1.0f / 65536.0f));
                    f_0284fc(ry * 6.28318548f * (1.0f / 65536.0f));
                    f_0284bc(rx * 6.28318548f * (1.0f / 65536.0f));
                    break;
                }
                case 8:
                    f_0287cc((float)d[0], 0.0f, 0.0f);
                    break;
                case 9:
                    f_0287cc(0.0f, (float)d[0], 0.0f);
                    break;
                case 10:
                    f_0287cc(0.0f, 0.0f, (float)d[0]);
                    break;
                case 11: {
                    Bytes4 x, y, z;
                    x.b.b0 = d[0]; x.b.b1 = d[1]; x.b.b2 = d[2]; x.b.b3 = d[3];
                    d += 4;
                    y.b.b0 = d[0]; y.b.b1 = d[1]; y.b.b2 = d[2]; y.b.b3 = d[3];
                    d += 4;
                    z.b.b0 = d[0]; z.b.b1 = d[1]; z.b.b2 = d[2]; z.b.b3 = d[3];
                    f_0287cc(x.f, y.f, z.f);
                    break;
                }
                case 12:
                case 13:
                case 14:
                case 15:
                    break;
                }
                f_028d94(&out[id]);
            }
        } else {
            f_02842c();
        }
    }
    f_028ca8();
}

/* Angle interpolation work block (src/system/KeyBlend.c): two angle triples in, the signed
   difference and its squared length out. */
struct AngLerp {
    unsigned short from[3];     /* +0 */
    unsigned short to[3];       /* +6 */
    short delta[3];             /* +12 */
    float dist;                 /* +20 */
    int m24;
};

/* The difference of the two triples and its squared length. */
static inline void Diff(AngLerp *l)
{
    unsigned short d0 = l->to[0] - l->from[0];
    unsigned short d1 = l->to[1] - l->from[1];
    unsigned short d2 = l->to[2] - l->from[2];
    float x = (short)d0, y = (short)d1, z = (short)d2;

    l->delta[0] = d0;
    l->delta[1] = d1;
    l->delta[2] = d2;
    l->dist = x * x + y * y + z * z;
}

/* @draft 0x0dbf04 us f_0dbf04
   WHAT IT DOES: Finds the shorter way from one angle triple to another: the target triple and its
   equivalent (x + half a turn, half a turn - y, z + half a turn) are both measured, and the block
   keeps the one with the smaller squared difference.
   Remaining difference: register allocation and schedule only (size equal). This build keeps the
   0x8000 constant in a register from the start and so uses one more temporary (t7), shifting every
   later choice by one register; retail materialises it with the second triple's loads. */
extern "C" void f_0dbf04(AngLerp *a)
{
    AngLerp l0 = *a;
    AngLerp l1 = *a;

    Diff(&l0);
    l1.to[0] += 0x8000;
    l1.to[1] = 0x8000 - l1.to[1];
    l1.to[2] += 0x8000;
    Diff(&l1);
    if (l0.dist < l1.dist)
        *a = l0;
    else
        *a = l1;
}

/* @draft 0x0dfa88 us f_0dfa88
   WHAT IT DOES: Calls the routine at 0x0df538 for each record of the list whose key equals the given key. */
extern "C" void f_0dfa88(void *self, RecList *l, int key)
{
    for (int i = 0; i < l->hdr->count; i++) {
        if (l->recs[i].key == key)
            f_0df538(self, l, i, l->recs[i].key);
    }
}

/* @draft 0x0dfb1c us f_0dfb1c
   WHAT IT DOES: Calls the routine at 0x0dedd0 for each 32-byte slot starting at the given pointer, one per
   slot of the list. */
extern "C" void f_0dfb1c(char *p, RecList *l, int arg)
{
    for (int i = 0; i < l->hdr->count; i++, p += 32)
        f_0dedd0(p, l, arg, i);
}

/* @implements 0x0dfb98 us f_0dfb98
   WHAT IT DOES: Reads the top four bits of the flags word at +12 of the holder's header. */
extern "C" unsigned f_0dfb98(Holder *h)
{
    return h->inner->flags >> 28;
}

/* A spline key: a value, its tangent and the frame it falls on. */
struct HKey {
    float v;                /* +0 */
    float tan;              /* +4 */
    unsigned short time;    /* +8 */
    short pad;
};

/* @draft 0x0dfba8 us f_0dfba8
   WHAT IT DOES: Evaluates a Hermite spline through n keys at frame t: finds the span whose end key
   is at or after t and blends its two values and tangents with the cubic Hermite weights.
   Remaining difference: the span search loop (8 bytes short, every later word shifted). Retail
   counts i from 1 against n and recomputes j = i - 1 inside the loop and again on the normal exit,
   then tests j == -1; this spelling counts j against n - 1 (blez guard). The arithmetic after the
   search matches retail's instruction for instruction. */
extern "C" float f_0dfba8(HKey *e, int n, float t)
{
    int j;

    for (j = 0; j < n - 1; j++) {
        if (t <= (float)e[j + 1].time)
            break;
    }
    if (j == -1)
        return 0.0f;
    {
        HKey *a = &e[j];
        HKey *b = a + 1;
        float s = (t - (float)a->time) / (float)(b->time - a->time);
        return (1.0f - s) * (1.0f - s) * (1.0f + 2.0f * s) * a->v + (3.0f - 2.0f * s) * s * s * b->v +
               (1.0f - s) * (1.0f - s) * s * a->tan + s * s * (s - 1.0f) * b->tan;
    }
}

/* @draft 0x0dfca4 us f_0dfca4
   WHAT IT DOES: The same spline evaluation for an angle key track, returning the result converted from
   radians to a 16-bit angle.
   Remaining difference: the span search loop, as in 0x0dfba8. */
extern "C" short f_0dfca4(HKey *e, int n, float t)
{
    int j;
    short r = 0;

    for (j = 0; j < n - 1; j++) {
        if (t <= (float)e[j + 1].time)
            break;
    }
    if (j != -1) {
        HKey *a = &e[j];
        HKey *b = a + 1;
        float s = (t - (float)a->time) / (float)(b->time - a->time);
        r = (short)(int)(((1.0f - s) * (1.0f - s) * (1.0f + 2.0f * s) * a->v +
                          (3.0f - 2.0f * s) * s * s * b->v + (1.0f - s) * (1.0f - s) * s * a->tan +
                          s * s * (s - 1.0f) * b->tan) * 65536.0f / 6.28318548f);
    }
    return r;
}

/* @implements 0x0dfdc8 us f_0dfdc8
   WHAT IT DOES: Builds a record's pose key from its spline tracks at the animation's current time:
   the key is reset to no translation, unit scale and zero angles, then the record kind says which
   angles (kinds 4 to 7) or the translation (kind 11) come from the tracks. */
extern "C" void f_0dfdc8(AnimData *pb, Key *k, int idx)
{
    int j = idx * 3;

    k->r[0] = k->r[1] = k->r[2] = 0;
    k->t[0] = k->t[1] = k->t[2] = 0.0f;
    k->s[0] = k->s[1] = k->s[2] = 1.0f;
    AnimHdr *h = pb->hdr;
    AnimRec *rec = &pb->recs[idx];
    int *tab = pb->tab;
    int *cnt = tab + h->count * 3;
    HKey *e = (HKey *)((char *)h + tab[j]);
    float t = pb->time;
    switch (rec->kind) {
    case 7:
        k->r[0] = f_0dfca4(e, cnt[j], t);
        j++;
        e = (HKey *)((char *)h + tab[j]);
        k->r[1] = f_0dfca4(e, cnt[j], t);
        j++;
        e = (HKey *)((char *)h + tab[j]);
        k->r[2] = f_0dfca4(e, cnt[j], t);
        break;
    case 8:
    case 9:
    case 10:
        break;
    case 4:
        k->r[0] = f_0dfca4(e, cnt[j], t);
        break;
    case 5:
        k->r[1] = f_0dfca4(e, cnt[j], t);
        break;
    case 6:
        k->r[2] = f_0dfca4(e, cnt[j], t);
        break;
    case 11:
        k->t[0] = f_0dfba8(e, cnt[j], t);
        j++;
        e = (HKey *)((char *)h + tab[j]);
        k->t[1] = f_0dfba8(e, cnt[j], t);
        j++;
        e = (HKey *)((char *)h + tab[j]);
        k->t[2] = f_0dfba8(e, cnt[j], t);
        break;
    }
}

/* A float from four unaligned bytes at p. */
static inline float GetF(const unsigned char *p)
{
    Bytes4 u;

    u.b.b0 = p[0];
    u.b.b1 = p[1];
    u.b.b2 = p[2];
    u.b.b3 = p[3];
    return u.f;
}

/* @draft 0x0dffd8 us f_0dffd8
   WHAT IT DOES: Builds the pose keys of every record from the spline tracks; for records of kind 7
   the translation comes instead from the second animation's frame data (three unaligned floats),
   unless that animation's header has flag 0x100 set, in which case nothing is built.
   Remaining difference: 21 words in the kind-7 block. Here the third float's address (d + 8) is
   formed with the second's, before the second store, in its own register (a3); retail forms it in
   the same register as the second (a2), after the second store, which suggests the pointer is
   stepped between the reads rather than offset. */
extern "C" void f_0dffd8(Key *keys, AnimData *pb, AnimData *pos)
{
    int i;

    if (pos->hdr->flags & 0x100)
        return;
    for (i = 0; i < pb->hdr->count; i++, keys++) {
        f_0dfdc8(pb, keys, i);
        AnimRec *rec = &pb->recs[i];
        if (rec->kind == 7) {
            unsigned char *d = f_0daf64(pos, pos->frame, i);
            keys->t[0] = GetF(d);
            keys->t[1] = GetF(d + 4);
            keys->t[2] = GetF(d + 8);
        }
    }
}

/* The frame segment table of an animation: segment end frames, segment lengths and the count. */
struct SegTab {
    unsigned short end[32];     /* +0 */
    unsigned short len[32];     /* +64 */
    unsigned short n;           /* +128 */
};

/* @draft 0x0e01a8 us f_0e01a8
   WHAT IT DOES: Splits the animation's current time into the two frames to blend and the fraction
   between them, through the segment table (each passed segment adds its length to the frame base;
   the last frame of a segment does not blend forward) and the header's frame divider. Returns 0 when
   the animation has no segment table or fewer than two segments.
   Remaining difference: 17 words. (1) Retail converts the time for the loop tests before the loop's
   blez guard; here loop.c hoists it into the preheader after the guard. (2) Retail holds the first
   frame in t0, the register of the 0/1 result, so the source probably reuses the result variable
   for it; here it gets a0. */
extern "C" int f_0e01a8(AnimData *pb, int *f0, int *f1, float *frac)
{
    int wrap = 0;
    int off = pb->head[6];
    int i, base, a, b;
    unsigned int k;
    float time, fr;
    AnimHdr *h;
    SegTab *sg;

    if (off == 0)
        return 0;
    h = pb->hdr;
    sg = (SegTab *)((char *)h + off);
    if (sg->n < 2)
        return 0;
    time = pb->time;
    base = 0;
    for (i = 0; i < sg->n - 1; i++) {
        if ((int)time == sg->end[i] - 1)
            wrap = 1;
        if ((int)time < sg->end[i])
            break;
        base += sg->len[i];
    }
    k = h->mode >> 28;
    if (k < 2) {
        a = (int)time;
        fr = 0.0f;
        b = a;
        if (wrap != 1) {
            fr = time - (float)a;
            b = a + 1;
        }
    } else if (!wrap) {
        float q = time / (float)(int)k;
        a = (int)q;
        b = a + 1;
        fr = q - (float)a;
    } else {
        float q = time / (float)(int)k;
        a = b = (int)q + 1;
        fr = 1.0f;
    }
    *f0 = a + base;
    *f1 = b + base;
    *frac = fr;
    return 1;
}

/* @implements 0x0e0724 us f_0e0724
   WHAT IT DOES: Sets the animation's whole frame number from its current time (an unsigned
   conversion), then calls the routine at 0x0de508. */
extern "C" void f_0e0724(void *a, AnimData *pb)
{
    pb->frame = (unsigned int)pb->time;
    f_0de508(a, pb);
}

/* @draft 0x0e0efc us f_0e0efc
   WHAT IT DOES: Walks the node stream of an animation and stores each node's transform, built from
   the pose key of the same index (the record kind says which parts of the key apply), into the matrix
   array; -1 restarts from the identity, or the given base matrix when the mode is 1, mirrored in x
   when the mirror flag is 1.
   Remaining difference: 10 words, global-alloc's choice between two pairs of parameters: retail
   gives out s5 and keys s4, mode s7 and mirror s6; here they are swapped. Each pair has equal use
   counts and live lengths one insn apart (from the order of the parameter copies), so the priority
   tie goes the other way; the source shape that changes it is not found. */
extern "C" void f_0e0efc(Matrix *out, Key *keys, AnimData *pb, int mirror, int mode, Matrix *base)
{
    const unsigned char *p;
    short id;

    f_028c70();
    if (mode == 1)
        f_028e9c(base);
    else
        f_02842c();
    if (mirror == 1)
        f_02884c(-1.0f, 1.0f, 1.0f);
    p = pb->nodes;
    while ((id = Read16(p)) != -2) {
        p += 2;
        if (id != -1) {
            AnimRec *rec = &pb->recs[id];
            Key *k = &keys[id];
            switch (rec->kind) {
            case 0:
                f_02884c(k->s[0], 1.0f, 1.0f);
                break;
            case 1:
                f_02884c(1.0f, k->s[1], 1.0f);
                break;
            case 2:
                f_02884c(1.0f, 1.0f, k->s[2]);
                break;
            case 3:
                f_02884c(k->s[0], k->s[1], k->s[2]);
                break;
            case 4:
                f_0284bc(k->r[0] * 6.28318548f * (1.0f / 65536.0f));
                break;
            case 5:
                f_0284fc(k->r[1] * 6.28318548f * (1.0f / 65536.0f));
                break;
            case 6:
                f_02853c(k->r[2] * 6.28318548f * (1.0f / 65536.0f));
                break;
            case 7:
                f_0287cc(k->t[0], k->t[1], k->t[2]);
                f_02853c(k->r[2] * 6.28318548f * (1.0f / 65536.0f));
                f_0284fc(k->r[1] * 6.28318548f * (1.0f / 65536.0f));
                f_0284bc(k->r[0] * 6.28318548f * (1.0f / 65536.0f));
                break;
            case 8:
                f_0287cc(k->t[0], 0.0f, 0.0f);
                break;
            case 9:
                f_0287cc(0.0f, k->t[1], 0.0f);
                break;
            case 10:
                f_0287cc(0.0f, 0.0f, k->t[2]);
                break;
            case 11:
                f_0287cc(k->t[0], k->t[1], k->t[2]);
                break;
            case 12:
            case 13:
            case 14:
            case 15:
                break;
            }
            f_028d94(&out[id]);
        } else {
            if (mode == 1)
                f_028e9c(base);
            else
                f_02842c();
            if (mirror == 1)
                f_02884c(-1.0f, 1.0f, 1.0f);
        }
    }
    f_028ca8();
}

/* @implements 0x0e1254 us f_0e1254
   WHAT IT DOES: Calls the routine at 0x0e0efc with flag 1 and zeros for the last two. */
extern "C" void f_0e1254(Matrix *a, Key *b, AnimData *c)
{
    f_0e0efc(a, b, c, 1, 0, 0);
}

/* @implements 0x0e1278 us f_0e1278
   WHAT IT DOES: Calls the routine at 0x0e0efc with zeros for the last three. */
extern "C" void f_0e1278(Matrix *a, Key *b, AnimData *c)
{
    f_0e0efc(a, b, c, 0, 0, 0);
}

/* @implements 0x0e129c us f_0e129c
   WHAT IT DOES: Calls the routine at 0x0e0efc with the fourth argument zero, flag 1 and the fifth passed on. */
extern "C" void f_0e129c(Matrix *a, Key *b, AnimData *c, Matrix *d)
{
    f_0e0efc(a, b, c, 0, 1, d);
}

/* @draft 0x0e12c0 us f_0e12c0
   WHAT IT DOES: Walks the node stream of an animation and stores, for every node with its own pose
   key, the transform built from that key (translation, rotations about z, y and x, then scale) into
   the matrix slot of the key; -1 restarts from the identity, or from the given base matrix when the
   mode is 1.
   Remaining difference: frame and every saved register. The second loop pass (rerun) hoists the
   constants -2 (loop test) and 1 (mode test) into saved registers here (insns "life 1, savings 1",
   moved in pass 2, "not desirable" in pass 1), which pushes out and keys onto the stack; retail
   hoists only -1, so its loop as seen by loop.c's threshold test must be larger. */
extern "C" void f_0e12c0(Matrix *out, Key *keys, AnimData *pb, int mode, Matrix *base)
{
    const unsigned char *p;
    short id;

    f_028c70();
    if (mode == 1)
        f_028e9c(base);
    else
        f_02842c();
    p = pb->nodes;
    while ((id = Read16(p)) != -2) {
        p += 2;
        if (id != -1) {
            AnimRec *rec = &pb->recs[id];
            if (rec->parent == -1) {
                int k = rec->key;
                Key *kk = &keys[k];
                f_0287cc(kk->t[0], kk->t[1], kk->t[2]);
                f_02853c(kk->r[2] * 6.28318548f * (1.0f / 65536.0f));
                f_0284fc(kk->r[1] * 6.28318548f * (1.0f / 65536.0f));
                f_0284bc(kk->r[0] * 6.28318548f * (1.0f / 65536.0f));
                f_02884c(kk->s[0], kk->s[1], kk->s[2]);
                f_028d94(&out[k]);
            }
        } else {
            if (mode == 1)
                f_028e9c(base);
            else
                f_02842c();
        }
    }
    f_028ca8();
}

/* @implements 0x0e1498 us f_0e1498
   WHAT IT DOES: Calls the routine at 0x0e12c0 with zeros for the last two arguments. */
extern "C" void f_0e1498(Matrix *a, Key *b, AnimData *c)
{
    f_0e12c0(a, b, c, 0, 0);
}

/* @implements 0x0e14b8 us f_0e14b8
   WHAT IT DOES: Calls the routine at 0x0e12c0 with flag 1 and the fifth argument passed on. */
extern "C" void f_0e14b8(Matrix *a, Key *b, AnimData *c, Matrix *d)
{
    f_0e12c0(a, b, c, 1, d);
}
