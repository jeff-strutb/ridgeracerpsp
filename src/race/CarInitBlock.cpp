/* Car state block, second object file (retail 0x0bc714 to 0x0bd328). The car block is 1500
   bytes: four 368-byte units (a tyre or axle record each) followed by seven words that hold
   the block's angle values. The block set-up clears every unit and the tail; the unit set-up
   clears its words and stores normalised angles; the last functions in the file are small
   helpers on a unit (an empty routine, a copy of zero, a blend, and a per-frame limit update). */

union W {
    int i;
    unsigned int u;
    float f;
    void *p;
};

/* One 368-byte unit (92 words). */
struct Unit {
    W w[92];
};

/* The car block: four units, then seven words. */
struct CarBlock {
    Unit u[4];
    W tail[7];
};

/* The limit record a unit points at (word 13 of the unit). */
struct Lim {
    W w[8];
};

/* Clears three consecutive words (a counted loop in retail). */
static inline void zero3(W *p) {
    int n = 2;
    do {
        n--;
        p->i = 0;
        p++;
    } while (n != -1);
}

extern "C" {
void *memset(void *d, int c, unsigned int n);
float *f_099b98(float *p);
void f_0bd06c(Unit *u);
float f_0bd210(float x, Unit *u);
float f_0c2bd0(float a, float b);
float f_09a9dc(float a, float b);
void f_09ff44(void *m);
void f_0a082c(void *m, int a, int b, int c);
void f_0a6bf4(float *out, void *m, void *u);
void f_0a6c18(float *out, void *m, void *u);
void f_0a5ea4(float *out, float *in, float k);
float sqrtf(float);
}

/* The work record the wheel set-up fills (word k at byte offset 4k). */
struct Work {
    W w[160];
};
extern Work *D_2456d0;

/* @draft 0x0bc714 us f_0bc714
   WHAT IT DOES: sets up the car block: runs the unit set-up on each of the four units, then
   zeroes three tail words and fills them with three normalised angles.
   Remaining difference: word 4 of 46 differs at +0x90: the last load uses v1 where retail uses v0
   (then sched2 lifts lw ra above the two stores). The lreg dump shows why: the first two loads
   are REG_EQUIV copies that update_equiv_regs moved next to their stores (new pseudos, v0);
   the last load (r2) instead carries a REG_EQUIV to its store destination t[2], is not moved,
   and local-alloc gives it v1. Not yet tried: a source shape that makes r2 like r0/r1. */
extern "C" void f_0bc714(CarBlock *b) {
    Unit *s = b->u;
    for (int n = 3; n != -1; n--) {
        f_0bd06c(s);
        s++;
    }
    W *t = &b->tail[3];
    zero3(t);
    W q[3];
    q[0].i = 0;
    f_099b98(&q[0].f);
    int r0 = q[0].i;
    q[1].i = 0;
    t[0].i = r0;
    f_099b98(&q[1].f);
    int r1 = q[1].i;
    q[2].i = 0;
    t[1].i = r1;
    f_099b98(&q[2].f);
    int r2 = q[2].i;
    t[3].i = 0;
    t[2].i = r2;
}

/* @draft 0x0bc7cc us f_0bc7cc
   WHAT IT DOES: the same block set-up as f_0bc714, kept as a separate copy in retail.
   Remaining difference: same source as f_0bc714, same single register difference (see its
   note: the last load's REG_EQUIV is to the store destination, so local-alloc picks v1). */
extern "C" void f_0bc7cc(CarBlock *b) {
    Unit *s = b->u;
    for (int n = 3; n != -1; n--) {
        f_0bd06c(s);
        s++;
    }
    W *t = &b->tail[3];
    zero3(t);
    W q[3];
    q[0].i = 0;
    f_099b98(&q[0].f);
    int r0 = q[0].i;
    q[1].i = 0;
    t[0].i = r0;
    f_099b98(&q[1].f);
    int r1 = q[1].i;
    q[2].i = 0;
    t[1].i = r1;
    f_099b98(&q[2].f);
    int r2 = q[2].i;
    t[3].i = 0;
    t[2].i = r2;
}

/* @implements 0x0bc884 us f_0bc884
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bc884(void) {}

/* @implements 0x0bc88c us f_0bc88c
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bc88c(void) {}

/* @draft 0x0bc894 us f_0bc894
   WHAT IT DOES: clears the four units and the first two tail words, then normalises three
   zero angles and stores them into the block's tail, with a zero word at the end.
   Remaining difference: 42 of 48 words differ; the routine is 180 bytes against retail 192 (the tail store order and count are not yet right). */
extern "C" void f_0bc894(CarBlock *b) {
    memset(&b->u[0], 0, 368);
    memset(&b->u[1], 0, 368);
    memset(&b->u[2], 0, 368);
    memset(&b->u[3], 0, 368);
    b->tail[2].i = 0;
    float z = b->tail[2].f;
    b->tail[0].i = 0;
    b->tail[1].i = 0;
    W q[3];
    q[0].f = z;
    f_099b98(&q[0].f);
    q[1].f = z;
    f_099b98(&q[1].f);
    q[2].f = z;
    f_099b98(&q[2].f);
    b->tail[6].i = 0;
    b->tail[3].i = q[0].i;
    b->tail[4].i = q[1].i;
    b->tail[5].i = q[2].i;
}

/* @implements 0x0bd064 us f_0bd064
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bd064(void) {}

/* @draft 0x0bd06c us f_0bd06c
   WHAT IT DOES: sets up one unit: clears its three-word groups and fills them with
   normalised angles from the unit's set-up values.
   Remaining difference: 4 of 84 words differ, first at +0x12c (the last tail store block):
   the same v1-for-v0 last load as f_0bc714 (REG_EQUIV to the destination n[2]; see there). */
extern "C" void f_0bd06c(Unit *u) {
    W t[9];
    W *s = &u->w[12];
    zero3(s);
    t[0].i = 0;
    f_099b98(&t[0].f);
    int r0 = t[0].i;
    t[1].i = 0;
    s[0].i = r0;
    f_099b98(&t[1].f);
    int r1 = t[1].i;
    t[2].i = 0;
    s[1].i = r1;
    f_099b98(&t[2].f);
    int r2 = t[2].i;
    s[3].i = 0;
    s[2].i = r2;
    W *m = &u->w[16];
    zero3(m);
    t[3].i = 0;
    f_099b98(&t[3].f);
    int r3 = t[3].i;
    t[4].i = 0;
    m[0].i = r3;
    f_099b98(&t[4].f);
    int r4 = t[4].i;
    m[1].i = r4;
    t[5].i = 0;
    f_099b98(&t[5].f);
    int r5 = t[5].i;
    m[3].i = 0;
    m[2].i = r5;
    W *n = &u->w[40];
    zero3(n);
    t[6].i = 0;
    f_099b98(&t[6].f);
    int r6 = t[6].i;
    t[7].i = 0;
    n[0].i = r6;
    f_099b98(&t[7].f);
    int r7 = t[7].i;
    n[1].i = r7;
    t[8].i = 0;
    f_099b98(&t[8].f);
    int r8 = t[8].i;
    n[3].i = 0;
    n[2].i = r8;
}

/* @implements 0x0bd1bc us f_0bd1bc
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bd1bc(void) {}

/* @implements 0x0bd1c4 us f_0bd1c4
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bd1c4(void) {}

/* @implements 0x0bd1cc us f_0bd1cc
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bd1cc(void) {}

/* @implements 0x0bd1d4 us f_0bd1d4
   WHAT IT DOES: an empty routine (returns at once). */
extern "C" void f_0bd1d4(void) {}

/* @implements 0x0bd1dc us f_0bd1dc
   WHAT IT DOES: zeroes the unit's first word and copies that zero float into the other
   words of the unit that hold its output values. */
extern "C" void f_0bd1dc(Unit *u) {
    u->w[0].i = 0;
    float z = u->w[0].f;
    u->w[12].f = z;
    u->w[3].f = z;
    u->w[2].f = z;
    u->w[6].f = z;
    u->w[7].f = z;
    u->w[9].f = z;
    u->w[8].f = z;
    u->w[10].f = z;
    u->w[11].f = z;
    u->w[1].f = z;
}

/* @implements 0x0bd210 us f_0bd210
   WHAT IT DOES: blends the argument toward the unit's second word: t = m4 * (1 - x) + x,
   and returns t times the unit's first word. */
extern "C" float f_0bd210(float x, Unit *u) {
    float t = u->w[1].f * (1.0f - x) + x;
    return t * u->w[0].f;
}

/* @draft 0x0bd234 us f_0bd234
   WHAT IT DOES: clamps the input to the limit record's first value, sets the unit's first and
   second outputs from it, blends the unit's angle with the second argument, and derives the
   unit's remaining outputs from the limit record's third value.
   Remaining difference (14 words, tail only): the w1 block as `if (x < l->w[1].f)` with the
   limit re-read (retail reloads it after the w0 store) and the zero store in the else fixed
   the layout. Left: retail keeps -r in f3 and r/60 in f2 (ours f2/f1), divisors reload into
   f1, and the w6 store comes after the w8 store and the second divisor load. */
extern "C" void f_0bd234(Unit *s, float x, float y) {
    Lim *l = (Lim *)s->w[13].p;
    float lim = l->w[1].f;
    float xc = x < lim ? x : lim;
    s->w[0].f = xc * 0.2f * 0.01666666753590107f;
    if (x < l->w[1].f) {
        float q = x / l->w[1].f;
        float d = 1.0f - q;
        s->w[1].f = d * d;
    } else {
        s->w[1].i = 0;
    }
    float v;
    if (0.0f < y) {
        v = l->w[2].f + l->w[6].f * y;
    } else {
        v = l->w[2].f;
    }
    float r = f_0bd210(v, s);
    s->w[2].f = r;
    float nr = -r;
    float a = r * 0.01666666753590107f;
    s->w[3].f = nr;
    float b = nr * 0.01666666753590107f;
    a = a / l->w[3].f;
    s->w[8].f = a;
    s->w[6].f = r;
    b = b / l->w[3].f;
    s->w[9].f = b;
}

/* @draft 0x0bc954 us f_0bc954
   WHAT IT DOES: applies one frame of steering input to the car block. The two inputs are scaled
   by 1/60; depending on the block's mode (word 368 of the tail) they are routed to the front
   pair (units 0 and 1) and the rear pair (units 2 and 3) as angle increments, dead-zoned at
   0.005 and normalised. Three further inputs are clamped to a steering angle, which is
   stepped through the angle helper f_0c2bd0 and stored, normalised, in the tail and in the
   word 13 of units 0 and 1.
   Remaining difference: 179/190 words differ, first at +0x8; size 732 vs 760 (first transcription, not yet iterated). */
extern "C" void f_0bc954(CarBlock *b, float a, float bb, float c, float d, float e, float g, float h) {
    a = a * 0.016666668f;
    bb = bb * 0.016666668f;
    float zero = 0.0f;
    float f20, f21;
    int mode = b->tail[0].i;
    if (mode == 1) {
        if (zero < c) {
            f20 = a;
            if (h < zero) f20 = -bb;
            else f20 = bb;
        } else {
            f20 = a;
        }
        f21 = a;
    } else if (mode == 3) {
        if (zero < c) {
            f21 = bb;
            if (h < zero) f21 = -bb;
            f20 = f21;
        } else {
            f21 = a;
            f20 = f21;
        }
    } else {
        f20 = a;
        if (zero < c) {
            f21 = bb;
            if (h < zero) f21 = -bb;
        } else {
            f21 = a;
        }
    }
    f20 = f20 / b->u[0].w[34].f;
    f21 = f21 / b->u[2].w[34].f;
    {
        float m = f20 < zero ? -f20 : f20;
        if (m < 0.005f) f20 = zero;
        m = f21 < zero ? -f21 : f21;
        if (m < 0.005f) f21 = zero;
    }
    b->u[0].w[12].f = b->u[0].w[12].f + f20;
    f_099b98(&b->u[0].w[12].f);
    b->u[1].w[12].f = b->u[1].w[12].f + f20;
    f_099b98(&b->u[1].w[12].f);
    b->u[2].w[12].f = b->u[2].w[12].f + f21;
    f_099b98(&b->u[2].w[12].f);
    b->u[3].w[12].f = b->u[3].w[12].f + f21;
    f_099b98(&b->u[3].w[12].f);
    float ang = d < zero ? -d : d;
    if (e < 0.15f) ang = zero;
    float lim = (g < zero ? -g : g) * 15.0f;
    if (ang < lim) ang = lim;
    if (0.6108653f < ang) ang = 0.6108653f;
    int small = 0;
    if (ang < 0.0349066f) small = 1;
    if (g < zero) ang = -ang;
    float st = f_0c2bd0(ang, b->tail[2].f);
    float step;
    if (small != 0) step = st * 5.0f;
    else step = st + st;
    b->tail[2].f = b->tail[2].f + step * 0.016666668f;
    float t0 = b->tail[2].f;
    f_099b98(&t0);
    b->u[0].w[13].f = t0;
    float t1 = b->tail[2].f;
    f_099b98(&t1);
    b->u[1].w[13].f = t1;
}

/* @draft 0x0bcc4c us f_0bcc4c
   WHAT IT DOES: derives the car block's wheel orientation from a 4-word direction vector and a
   scale. It stores the vector in the work record, computes the two direction angles (with
   the length of its y/z part), builds the wheel matrix and writes a rotated quad into each of
   the four units, derives the front and rear weight splits from the unit flags, and then
   scales and writes the per-unit contact vectors and clears the force words.
   Remaining difference: 258/262 words differ, first at +0x4; size 1028 vs 1048; bad refs: +0x7c: refers to 0x99b98, retail 0x9a9dc; +0x124: refers to 0xa6bf4, retail 0xa082c (first transcription, not yet iterated). */
extern "C" void f_0bcc4c(CarBlock *b, float x, float *v) {
    Work *wk = D_2456d0;
    float sv[4];
    float l[4];
    float tmp;
    sv[0] = v[0];
    sv[1] = v[1];
    sv[2] = v[2];
    sv[3] = v[3];
    wk->w[4].f = sv[0];
    wk->w[5].f = sv[1];
    wk->w[6].f = sv[2];
    wk->w[7].f = sv[3];
    tmp = -f_09a9dc(wk->w[6].f, wk->w[5].f);
    f_099b98(&tmp);
    b->tail[3].f = tmp;
    float len = sqrtf(wk->w[5].f * wk->w[5].f + wk->w[6].f * wk->w[6].f);
    wk->w[140].f = len;
    tmp = -f_09a9dc(wk->w[4].f, len);
    f_099b98(&tmp);
    b->tail[5].f = tmp;
    f_09ff44(&wk->w[76]);
    f_0a082c(&wk->w[76], b->tail[3].i, 1, 2);
    f_0a082c(&wk->w[76], b->tail[5].i, 0, 1);
    {
        Unit *u = b->u;
        for (int n = 3; n >= 0; n--) {
            f_0a6bf4(l, &wk->w[76], &u->w[4]);
            u->w[8].f = l[0];
            u->w[9].f = l[1];
            u->w[10].f = l[2];
            u->w[11].f = l[3];
            u++;
        }
    }
    float s = b->u[0].w[10].f + b->u[1].w[10].f;
    if (s < 0.0f) s = -s;
    wk->w[124].f = s;
    float r = b->u[2].w[10].f + b->u[3].w[10].f;
    if (r < 0.0f) r = -r;
    wk->w[125].f = r;
    float fr = r / (s + r);
    wk->w[128].f = fr;
    wk->w[129].f = 1.0f - fr;
    s = b->u[0].w[8].f + b->u[2].w[8].f;
    if (s < 0.0f) s = -s;
    wk->w[126].f = s;
    r = b->u[1].w[8].f + b->u[3].w[8].f;
    if (r < 0.0f) r = -r;
    wk->w[127].f = r;
    fr = r / (s + r);
    wk->w[130].f = fr;
    wk->w[131].f = 1.0f - fr;
    if (b->u[0].w[32].i == 0 && b->u[1].w[32].i == 0) {
        wk->w[128].f = 0.0f;
        wk->w[129].f = 1.0f;
    } else if (b->u[2].w[32].i == 0 && b->u[3].w[32].i == 0) {
        wk->w[129].f = 0.0f;
        wk->w[128].f = 1.0f;
    }
    if (b->u[0].w[32].i != 0) {
        if (b->u[1].w[32].i != 0) {
            wk->w[132].f = wk->w[128].f * wk->w[130].f;
            wk->w[133].f = wk->w[128].f * wk->w[131].f;
        } else {
            wk->w[132].f = wk->w[128].f;
            wk->w[133].i = 0;
        }
    } else {
        wk->w[132].i = 0;
        wk->w[133].f = wk->w[128].f;
    }
    if (b->u[2].w[32].i != 0) {
        if (b->u[3].w[32].i != 0) {
            wk->w[134].f = wk->w[129].f * wk->w[130].f;
            wk->w[135].f = wk->w[129].f * wk->w[131].f;
        } else {
            wk->w[134].f = wk->w[129].f;
            wk->w[135].i = 0;
        }
    } else {
        wk->w[134].i = 0;
        wk->w[135].f = wk->w[129].f;
    }
    x = -x;
    {
        Unit *u = b->u;
        float *k = &wk->w[132].f;
        for (int n = 3; n >= 0; n--) {
            f_0a5ea4(l, sv, x * *k);
            k++;
            u->w[20].f = l[0];
            u->w[21].f = l[1];
            u->w[22].f = l[2];
            u->w[23].f = l[3];
            u++;
        }
    }
    {
        Unit *u = b->u;
        for (int n = 3; n >= 0; n--) {
            u->w[28].i = 0;
            u->w[29].i = 0;
            u->w[30].i = 0;
            u->w[31].i = 0;
            f_0a6bf4(l, &u->w[56], &u->w[20]);
            wk->w[12].f = l[0];
            wk->w[13].f = l[1];
            wk->w[14].f = l[2];
            wk->w[14].i = 0;
            wk->w[15].f = l[3];
            wk->w[12].i = 0;
            f_0a6c18(l, &u->w[56], &wk->w[12]);
            u->w[24].f = l[0];
            u->w[25].f = l[1];
            u->w[26].f = l[2];
            u->w[27].f = l[3];
            if (u->w[32].i != 0) {
                u->w[28].f = l[0];
                u->w[29].f = l[1];
                u->w[30].f = l[2];
                u->w[31].f = l[3];
            }
            u++;
        }
    }
}
