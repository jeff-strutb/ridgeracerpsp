/* Blending of keyframed poses (retail 0x0e14d8 to 0x0e1eec). A pose key is six floats and
   three 16-bit angles in 32 bytes. A blend object holds a key count, a set count and a list
   of sets, each a key array and a weight array. Helpers blend the sets into an output key
   array, apply a swap list to a key array, step a key cursor, and unpack angle triples. */

struct Key {
    float f[6];                 /* +0 */
    unsigned short r[3];        /* +24 */
    unsigned short pad;         /* +30 */
};

struct KeySet {
    struct Key *keys;           /* +0 */
    float *w;                   /* +4 */
};

struct Blend {
    int n;                      /* +0 key count */
    int m;                      /* +4 set count */
    struct KeySet sets[1];      /* +8 */
};

/* Angle interpolation work block: two angle triples in, the signed difference out. */
struct AngLerp {
    unsigned short from[3];
    unsigned short to[3];
    short delta[3];
};

extern void f_0dbf04(struct AngLerp *a);

/* Sequence of key indices (-1 = none) for the swap pass. */
struct SwapList {
    int count;
    int *idx;
};

/* A key cursor: the set descriptor, an index and a fractional position. */
struct Cursor {
    struct { int m0; unsigned short count; } *seq;   /* count at +4 */
    int pad[5];
    unsigned idx;               /* +24 */
    float pos;                  /* +28 */
};

/* @draft 0x0e14d8 us f_0e14d8
   WHAT IT DOES: Blends every key of a multi-set pose into the output: for each key it derives a cumulative weight for each set after the first, and lerps the running result toward that set's key by it.
   DRAFT: 17 words differ, all in the lerp block's instruction schedule: retail stores the third source angle and sets up the call argument before the six second-key float loads, and loads the second key's first angle ahead of the six subtracts. */
void f_0e14d8(struct Blend *b, struct Key *out)
{
    int i, j;
    float t[16];
    struct Key *o;

    for (i = 0; i < b->n; i++) {
        for (j = 0; j < b->m - 1; j++) {
            float sum = 0.0f;
            int k;
            for (k = 0; k <= j + 1; k++)
                sum += b->sets[k].w[i];
            if (sum < 0.001f)
                t[j] = -10.0f;
            else
                t[j] = b->sets[j + 1].w[i] / sum;
        }
        o = &out[i];
        for (j = 0; j < b->m - 1; j++) {
            if (t[j] < -0.5f)
                continue;
            {
                struct Key *a, *c;
                struct AngLerp l;
                float x0, x1, x2, x3, x4, x5;
                float d0, d1, d2, d3, d4, d5;
                if (j == 0) {
                    a = &b->sets[0].keys[i];
                    c = &b->sets[1].keys[i];
                } else {
                    a = o;
                    c = &b->sets[j + 1].keys[i];
                }
                x0 = a->f[0]; x1 = a->f[1]; x2 = a->f[2];
                x3 = a->f[3]; x4 = a->f[4]; x5 = a->f[5];
                l.from[0] = a->r[0];
                l.from[1] = a->r[1];
                l.from[2] = a->r[2];
                d0 = c->f[0] - x0; d1 = c->f[1] - x1; d2 = c->f[2] - x2;
                d3 = c->f[3] - x3; d4 = c->f[4] - x4; d5 = c->f[5] - x5;
                l.to[0] = c->r[0];
                l.to[1] = c->r[1];
                l.to[2] = c->r[2];
                d0 *= t[j]; d1 *= t[j]; d2 *= t[j]; d3 *= t[j]; d4 *= t[j]; d5 *= t[j];
                o->f[0] = x0 + d0;
                o->f[1] = x1 + d1;
                o->f[2] = x2 + d2;
                o->f[3] = x3 + d3;
                o->f[4] = x4 + d4;
                o->f[5] = x5 + d5;
                f_0dbf04(&l);
                o->r[0] = (int)((float)l.from[0] + t[j] * (float)l.delta[0]);
                o->r[1] = (int)((float)l.from[1] + t[j] * (float)l.delta[1]);
                o->r[2] = (int)((float)l.from[2] + t[j] * (float)l.delta[2]);
            }
        }
    }
}

/* @draft 0x0e17d8 us f_0e17d8
   WHAT IT DOES: Blends one key of a multi-set pose into the output: derives a cumulative weight for each set after the first, and lerps the running result toward that set's key by it, as the all-keys routine does for each key.
   DRAFT: same 17-word schedule difference as f_0e14d8 in the lerp block (third source angle store and call argument set up come before the second key's float loads in retail). */
void f_0e17d8(struct Blend *b, struct Key *out, int i)
{
    int j;
    float t[16];
    struct Key *o;

    for (j = 0; j < b->m - 1; j++) {
        float sum = 0.0f;
        int k;
        for (k = 0; k <= j + 1; k++)
            sum += b->sets[k].w[i];
        if (sum < 0.001f)
            t[j] = -10.0f;
        else
            t[j] = b->sets[j + 1].w[i] / sum;
    }
    o = &out[i];
    for (j = 0; j < b->m - 1; j++) {
        if (t[j] < -0.5f)
            continue;
        {
            struct Key *a, *c;
            struct AngLerp l;
            float x0, x1, x2, x3, x4, x5;
            float d0, d1, d2, d3, d4, d5;
            if (j == 0) {
                a = &b->sets[0].keys[i];
                c = &b->sets[1].keys[i];
            } else {
                a = o;
                c = &b->sets[j + 1].keys[i];
            }
            x0 = a->f[0]; x1 = a->f[1]; x2 = a->f[2];
            x3 = a->f[3]; x4 = a->f[4]; x5 = a->f[5];
            l.from[0] = a->r[0];
            l.from[1] = a->r[1];
            l.from[2] = a->r[2];
            d0 = c->f[0] - x0; d1 = c->f[1] - x1; d2 = c->f[2] - x2;
            d3 = c->f[3] - x3; d4 = c->f[4] - x4; d5 = c->f[5] - x5;
            l.to[0] = c->r[0];
            l.to[1] = c->r[1];
            l.to[2] = c->r[2];
            d0 *= t[j]; d1 *= t[j]; d2 *= t[j]; d3 *= t[j]; d4 *= t[j]; d5 *= t[j];
            o->f[0] = x0 + d0;
            o->f[1] = x1 + d1;
            o->f[2] = x2 + d2;
            o->f[3] = x3 + d3;
            o->f[4] = x4 + d4;
            o->f[5] = x5 + d5;
            f_0dbf04(&l);
            o->r[0] = (int)((float)l.from[0] + t[j] * (float)l.delta[0]);
            o->r[1] = (int)((float)l.from[1] + t[j] * (float)l.delta[1]);
            o->r[2] = (int)((float)l.from[2] + t[j] * (float)l.delta[2]);
        }
    }
}

/* @draft 0x0e1aa8 us f_0e1aa8
   WHAT IT DOES: Blends the first two sets of a pose into the output: every key is the first set's key moved toward the second set's key by the first set's weight for that key, the angles by the shortest way round.
   DRAFT: 51 words differ, all instruction scheduling inside the loop body (retail delays the angle loads and stores between the float stores; every statement order tried schedules the same); registers, loop and frame match. */
void f_0e1aa8(struct Blend *b, struct Key *out)
{
    int i;
    struct AngLerp l;

    for (i = 0; i < b->n; i++) {
        struct Key *a = &b->sets[0].keys[i];
        struct Key *c = &b->sets[1].keys[i];
        struct Key *o = &out[i];
        struct KeySet *ks = b->sets;

        o->f[0] = a->f[0] + (c->f[0] - a->f[0]) * ks->w[i];
        o->f[1] = a->f[1] + (c->f[1] - a->f[1]) * ks->w[i];
        o->f[2] = a->f[2] + (c->f[2] - a->f[2]) * ks->w[i];
        o->f[3] = a->f[3] + (c->f[3] - a->f[3]) * ks->w[i];
        o->f[4] = a->f[4] + (c->f[4] - a->f[4]) * ks->w[i];
        o->f[5] = a->f[5] + (c->f[5] - a->f[5]) * ks->w[i];
        l.from[0] = a->r[0];
        l.from[1] = a->r[1];
        l.from[2] = a->r[2];
        l.to[0] = c->r[0];
        l.to[1] = c->r[1];
        l.to[2] = c->r[2];
        f_0dbf04(&l);
        o->r[0] = (int)((float)l.from[0] + ks->w[i] * (float)l.delta[0]);
        o->r[1] = (int)((float)l.from[1] + ks->w[i] * (float)l.delta[1]);
        o->r[2] = (int)((float)l.from[2] + ks->w[i] * (float)l.delta[2]);
    }
}

/* @implements 0x0e1ca8 us f_0e1ca8
   WHAT IT DOES: Applies a swap list to a key array: for each list entry that is not -1, the key at the entry's position is exchanged with the key whose index the entry holds. */
void f_0e1ca8(struct Key *keys, struct SwapList *list)
{
    int i;
    struct Key tmp;

    for (i = 0; i < list->count; i++) {
        if (list->idx[i] != -1) {
            tmp = keys[i];
            keys[i] = keys[list->idx[i]];
            keys[list->idx[i]] = tmp;
        }
    }
}

/* @implements 0x0e1dac us f_0e1dac
   WHAT IT DOES: Advances a key cursor to the next key index, wrapping to zero at the end of its key list. */
void f_0e1dac(struct Cursor *c)
{
    c->idx++;
    if (c->idx >= c->seq->count)
        c->idx = 0;
}

/* @implements 0x0e1dd8 us f_0e1dd8
   WHAT IT DOES: Moves a key cursor's fractional position by a step, wrapping to zero once it reaches the last key and to the key count when it goes below zero. */
void f_0e1dd8(struct Cursor *c, float step)
{
    float p = c->pos + step;

    c->pos = p;
    if ((float)(c->seq->count - 1) <= p) {
        c->pos = 0.0f;
        return;
    }
    if (p < 0.0f)
        c->pos = (float)c->seq->count;
}

/* Packed-angle formats: the format code is in the top four bits of the word at +12. */
struct AngSrc {
    int m0, m4, m8;
    unsigned fmt;               /* +12 */
};
struct AngObj {
    struct AngSrc *src;
};

/* @draft 0x0e1e34 us f_0e1e34
   WHAT IT DOES: Unpacks three 16-bit angles from a byte stream: formats below 6 hold three plain little-endian halfwords; the others pack them in four bytes of 14, 5 and 5 bit fields.
   DRAFT: size 180 vs 184 and 43 words differ; retail keeps the source pointer and the three output pointers in copies (move t1..t3) and reads the packed bytes in the order 1, 2, 0, 3 with the three stores last, which this form does not reproduce. */
void f_0e1e34(struct AngObj *o, const unsigned char *p, short *x, short *y, short *z)
{
    if ((o->src->fmt >> 28) < 6) {
        *x = p[0] | (p[1] << 8);
        p += 2;
        *y = p[0] | (p[1] << 8);
        p += 2;
        *z = p[0] | (p[1] << 8);
        return;
    }
    *x = (p[3] << 8) | (p[2] & 0xe0);
    *y = ((p[2] & 0x1f) << 11) | ((p[1] >> 2) << 5);
    *z = ((p[1] & 3) << 14) | (p[0] << 6);
}
