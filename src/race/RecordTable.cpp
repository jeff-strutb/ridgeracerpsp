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

extern "C" void f_0db2c4(void *a, void *b, int c, int d);
extern "C" void f_0df538(void *self, RecList *l, int i, int key);
extern "C" void f_0dedd0(void *slot, RecList *l, int arg, int i);
extern "C" void f_0de508(void *a, Obj *o);
extern "C" void f_0e0efc(void *a, void *b, void *c, int d, int e, int f);
extern "C" void f_0e12c0(void *a, void *b, void *c, int d, int e);

/* @implements 0x0db824 us f_0db824
   WHAT IT DOES: Calls the 0x0db2c4 routine with the third and fourth arguments zero. */
extern "C" void f_0db824(void *a, void *b)
{
    f_0db2c4(a, b, 0, 0);
}

/* @implements 0x0db844 us f_0db844
   WHAT IT DOES: Calls the 0x0db2c4 routine with the third argument zero and the fourth passed on. */
extern "C" void f_0db844(void *a, void *b, int d)
{
    f_0db2c4(a, b, 0, d);
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
