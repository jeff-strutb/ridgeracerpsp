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
}

/* @draft 0x0bc714 us f_0bc714
   WHAT IT DOES: sets up the car block: runs the unit set-up on each of the four units, then
   zeroes three tail words and fills them with three normalised angles.
   Remaining difference: word 4 of 46 differs at +0x90: the last load uses v1 where retail uses v0. */
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
   Remaining difference: same source as f_0bc714, same single register difference. */
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
   Remaining difference: 4 of 84 words differ, first at +0x12c (the last tail store block). */
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
   Remaining difference: 58 of 61 words differ, first at +0xc (the clamp and the register allocation of the first store group). */
extern "C" void f_0bd234(Unit *s, float x, float y) {
    Lim *l = (Lim *)s->w[13].p;
    float lim = l->w[1].f;
    float xc = x < lim ? x : lim;
    s->w[0].f = xc * 0.2f * 0.01666666753590107f;
    if (!(x < lim)) {
        s->w[1].i = 0;
    } else {
        float q = x / lim;
        float d = 1.0f - q;
        s->w[1].f = d * d;
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
