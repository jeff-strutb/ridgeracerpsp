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

struct Obj {
    char m0[24];
    int value;              /* +24 */
    float f28;              /* +28 */
};

extern "C" void f_0df538(void *self, RecList *l, int i, int key);
extern "C" void f_0dedd0(void *slot, RecList *l, int arg, int i);
extern "C" void f_0de508(void *a, Obj *o);
extern "C" void f_0e0efc(void *a, void *b, void *c, int d, int e, int f);
extern "C" void f_0e12c0(void *a, void *b, void *c, int d, int e);

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
    short m2;
    short m4;
    unsigned short frameSize;
    int m8;
    unsigned int mode;
};

struct AnimRec {
    int m0;
    unsigned char kind;     /* +4 */
    char m5;
    char m6;
    unsigned char flags;
    int start;
    int still;
};

struct AnimData {
    AnimHdr *hdr;           /* +0 */
    int *head;              /* +4 */
    AnimRec *recs;          /* +8 */
    unsigned char *nodes;   /* +12 */
    void *tab;              /* +16 */
    int m20;
    int frame;              /* +24 */
};

extern "C" unsigned char *f_0db0d0(AnimData *pb, int frame, int idx);
extern "C" unsigned char *f_0daf64(AnimData *pb, unsigned int frame, int idx);
extern "C" void f_0e1e34(AnimData *pb, const unsigned char *p, unsigned short *x, unsigned short *y,
                         unsigned short *z);

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

/* @draft 0x0e0724 us f_0e0724
   WHAT IT DOES: Stores a float as a fixed integer in the object's +24 field (values from 2^31 up keep the
   sign bit set), then calls the routine at 0x0de508. */
extern "C" void f_0e0724(void *a, Obj *o)
{
    float x = o->f28;
    int v = (int)x;
    if (x >= 2147483648.0f)
        v = (int)(x - 2147483648.0f) | 0x80000000;
    o->value = v;
    f_0de508(a, o);
}

/* @implements 0x0e1254 us f_0e1254
   WHAT IT DOES: Calls the routine at 0x0e0efc with flag 1 and zeros for the last two. */
extern "C" void f_0e1254(void *a, void *b, void *c)
{
    f_0e0efc(a, b, c, 1, 0, 0);
}

/* @implements 0x0e1278 us f_0e1278
   WHAT IT DOES: Calls the routine at 0x0e0efc with zeros for the last three. */
extern "C" void f_0e1278(void *a, void *b, void *c)
{
    f_0e0efc(a, b, c, 0, 0, 0);
}

/* @implements 0x0e129c us f_0e129c
   WHAT IT DOES: Calls the routine at 0x0e0efc with the fourth argument zero, flag 1 and the fifth passed on. */
extern "C" void f_0e129c(void *a, void *b, void *c, int d)
{
    f_0e0efc(a, b, c, 0, 1, d);
}

/* @implements 0x0e1498 us f_0e1498
   WHAT IT DOES: Calls the routine at 0x0e12c0 with zeros for the last two arguments. */
extern "C" void f_0e1498(void *a, void *b, void *c)
{
    f_0e12c0(a, b, c, 0, 0);
}

/* @implements 0x0e14b8 us f_0e14b8
   WHAT IT DOES: Calls the routine at 0x0e12c0 with flag 1 and the fifth argument passed on. */
extern "C" void f_0e14b8(void *a, void *b, void *c, int d)
{
    f_0e12c0(a, b, c, 1, d);
}
