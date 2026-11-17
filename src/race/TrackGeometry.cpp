/* Track and car geometry helpers (retail 0x0b1270 to 0x0b6754, an object file with unwind
   information). Two-dimensional points, projections onto a direction, cross products and the
   signed side tests used by the course code. Operations write their result through a pointer
   argument or return it by value, as the retail code does. */

struct Vec2 {
    float x, y;
};

/* A plane kept as a Vec4: normal in x and z (y is zero), and the constant in w. */
struct V4 {
    float a[4];
};

struct Plane {
    float x, y, z, w;
};

/* A car or course object: the value at offset 4 is its state word. */
struct StateObj {
    int m0;
    int m4;
};

extern "C" {
int f_0b2120_3(int a, int b, int c, float *out) __asm__("f_0b2120");
extern const float D_1ac7e0;
void f_0b2f18_i(int a, int b, int c, int d, int e, int f, int g, int h, float x, float y, void *s, void *t) __asm__("f_0b2f18");
/* The caller at 0x0b6738 passes no floats: it sees the routine through an alias with eight
   integer arguments. */
void f_0b6710_8(int a, int b, int c, int d, int e, int f, int g, int h) __asm__("f_0b6710");
}

static inline Vec2 operator-(const Vec2 &a, const Vec2 &b)
{
    Vec2 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    return r;
}

static inline float Dot(const Vec2 &a, const Vec2 &b)
{
    return a.x * b.x + a.y * b.y;
}

static inline Vec2 operator*(const Vec2 &a, float s)
{
    Vec2 r;
    r.x = a.x * s;
    r.y = a.y * s;
    return r;
}

/* @draft 0x0b1400 us f_0b1400
   WHAT IT DOES: Projects the vector from the first point to the third onto a direction: the
   component along the direction, scaled back into a vector.
   Remaining difference: this source compiles to a 48-byte frame (three slots: op- result 16, d 0,
   product 32); retail's 112-byte frame has seven 16-byte slots with d at 16, the op- result at 64,
   the product at 80 and 0/32/48/96 unused, so retail's inline helpers create four more stack
   temporaries (e.g. constructor-built returns); not yet identified. */
Vec2 f_0b1400(const Vec2 *a, const Vec2 *, const Vec2 *b, const Vec2 *dir)
{
    Vec2 d = *b - *a;
    return *dir * Dot(d, *dir);
}

/* @draft 0x0b17ac us f_0b17ac
   WHAT IT DOES: Takes three points, forms the edge vector from the first to the second and the
   vector from the first to the third, and returns the third's offset projected onto the unit
   normal of the first edge (the normal is the first edge turned a quarter, scaled by the cross
   product of the two edges; a zero-length normal is left unscaled).
   Remaining difference: 332 bytes against retail's 476, and every word differs; the stack
   temporaries and the normalisation path (with its sqrtf fallback) are not yet matched. */
Vec2 f_0b17ac(const Vec2 *a, const Vec2 *b, const Vec2 *c)
{
    Vec2 ab = *b - *a;
    Vec2 ac = *c - *a;
    float k = ab.x * ac.y - ab.y * ac.x;
    Vec2 n;
    n.x = -ab.y * k;
    n.y = ab.x * k;
    float len = __builtin_sqrtf(n.x * n.x + n.y * n.y);
    if (len != 0.0f) {
        float s = 1.0f / len;
        n.x = n.x * s;
        n.y = n.y * s;
    }
    float d = Dot(ac, n);
    return n * d;
}

/* The difference of two points given by address; retail wraps the subtraction in a second
   by-value layer, which gives each result its own stack slot. */
static inline Vec2 Diff(const Vec2 *a, const Vec2 *b)
{
    return *a - *b;
}

static inline float Cross(Vec2 a, Vec2 b)
{
    return a.x * b.y - a.y * b.x;
}

/* @implements 0x0b1b28 us f_0b1b28
   WHAT IT DOES: Returns the z component of the cross product of the vectors from the first
   point to the second and to the third point. */
float f_0b1b28(const Vec2 *a, const Vec2 *b, const Vec2 *c)
{
    return Cross(Diff(b, a), Diff(c, a));
}

/* @implements 0x0b1ba8 us f_0b1ba8
   WHAT IT DOES: Stores a value into the object's state word at offset 4, adding 112 when the
   flag is clear.
   Retail computes (flag ^ 1) & 1. */
void f_0b1ba8(StateObj *o, int v, int flag)
{
    if ((flag ^ 1) & 1)
        v += 112;
    o->m4 = v;
}

/* @implements 0x0b20d8 us f_0b20d8
   WHAT IT DOES: Computes a plane from the first three arguments through the routine at
   0x0b2120 and stores it at the fourth argument: normal x, zero, normal z, and a constant of 1.0. */
int f_0b20d8(int a, int b, int c, float *out)
{
    float t[2];
    int r = f_0b2120_3(a, b, c, t);
    out[0] = t[0];
    out[1] = 0.0f;
    out[2] = t[1];
    out[3] = D_1ac7e0;
    return r;
}

/* @implements 0x0b6710 us f_0b6710
   WHAT IT DOES: Calls the routine at 0x0b2f18 with its own eight integer arguments and two
   floats passed on, and two local 16-byte buffers as the last two arguments. */
void f_0b6710(int a, int b, int c, int d, int e, int f, int g, int h, float x, float y)
{
    V4 p, q;

    f_0b2f18_i(a, b, c, d, e, f, g, h, x, y, &p, &q);
}

/* @implements 0x0b6738 us f_0b6738
   WHAT IT DOES: Calls the routine at 0x0b6710, passing its own arguments on and a 16-byte local
   buffer as the eighth. */
void f_0b6738(int a, int b, int c, int d, int e, int f, int g, void *h)
{
    float buf[4];

    f_0b6710_8(a, b, c, d, e, f, g, (int)buf);
}

/* An angle in radians, passed by value in an integer register. */
union Angle {
    float a;
};

extern "C" {
float f_09a9dc(float x, float z);
Angle *f_099b98(Angle *a);
void f_09b394(Angle a, float *x, float *y);
}

/* @implements 0x0b1a78 us f_0b1a78
   WHAT IT DOES: Turns both points by the negated heading of the first point (its angle about
   the origin, wrapped and applied as a rotation to each), then returns whether the second point
   lies at a negative x, or the first's x is less than the second's.
   f_099b98 returns its argument; with that prototype v0 stays live across the call as in retail. */
int f_0b1a78(const Vec2 *a, const Vec2 *b)
{
    Vec2 p = *a;
    Vec2 q = *b;
    float ang = -f_09a9dc(a->y, a->x);
    Angle t1;
    t1.a = ang;
    f_099b98(&t1);
    f_09b394(t1, &p.x, &p.y);
    Angle t2;
    t2.a = ang;
    f_099b98(&t2);
    f_09b394(t2, &q.x, &q.y);
    if (q.x < 0.0f)
        return 1;
    if (p.x < q.x)
        return 1;
    return 0;
}

/* @draft 0x0b1988 us f_0b1988
   WHAT IT DOES: Forms the vectors from the first point to the second and to the third, turns
   both by the negated heading of the first (the second point's vector), and returns whether the
   third's x is negative or the second's x is less than the third's.
   Remaining difference: 57 of 60 words differ, and the frame is 232 bytes against retail's 240 (retail keeps f20 for the negated angle across the calls). */
int f_0b1988(const Vec2 *a, const Vec2 *b, const Vec2 *c)
{
    Vec2 p = *b - *a;
    Vec2 q = *c - *a;
    float ang = -f_09a9dc(p.y, p.x);
    Angle t1;
    t1.a = ang;
    f_099b98(&t1);
    f_09b394(t1, &p.x, &p.y);
    Angle t2;
    t2.a = ang;
    f_099b98(&t2);
    f_09b394(t2, &q.x, &q.y);
    if (q.x < 0.0f)
        return 1;
    if (p.x < q.x)
        return 1;
    return 0;
}

/* A three-component float point with its middle component zero. */
struct Vec3 {
    float x, y, z;
};

/* A plane record: x and z are the normal, y is zero in the plane, w is the constant. */
struct PlaneRec {
    float x, y, z, w;
};

/* A car outline: a vertex count, the centre of its bounding circle (x, z), the circle's radius,
   and up to sixteen outline vertices. */
struct Shape {
    int n;
    float cx, cz, r;
    Vec2 v[16];
};

/* A list of plane records: two halfword counts, then a word, then the pointer array. */
struct PlaneList {
    unsigned short m0;
    unsigned short m2;
    Shape *m4;
    PlaneRec *m8[1];
};

extern "C" {
extern char D_246700;
int f_0c5998(void *g, void *arr, void *p, int n, unsigned short *out);
}

/* @draft 0x0b1bc0 us f_0b1bc0
   WHAT IT DOES: Builds the point (x, 0, z), runs the list search at 0x0c5998 on it, stores the
   count and the second halfword, then removes every record that duplicates the first pair of
   words (x equal to z and y equal to w), shifting the later pointers down, and returns the
   count.
   Remaining difference: 52 of 67 words differ, from +0x20 (the scheduling of the search call's argument setup and the shift loop). */
int f_0b1bc0(PlaneList *o, int n, float x, float z)
{
    Vec3 p;
    unsigned short out16;
    p.x = x;
    p.y = 0.0f;
    p.z = z;
    int cnt = f_0c5998(&D_246700, o->m8, &p, n, &out16);
    o->m0 = (unsigned short)cnt;
    o->m2 = out16;
    if ((cnt & 0xffff) == 0)
        return o->m0;
    int i = 0;
    while (i < (cnt & 0xffff)) {
        PlaneRec *e = o->m8[i];
        if (e->x == e->z && e->y == e->w) {
            int last = (cnt & 0xffff) - 1;
            if (i < last) {
                for (int k = i; k < last; k++)
                    o->m8[k] = o->m8[k + 1];
            }
            cnt = cnt - 1;
            o->m0 = (unsigned short)cnt;
        } else {
            i++;
        }
    }
    return cnt & 0xffff;
}

/* @draft 0x0b1270 us f_0b1270
   WHAT IT DOES: Forms the edge vector from the first point to the second and the vector from
   the first to the third, takes the cross product of the two, and returns the edge's normal
   (the first edge turned a quarter, scaled by that cross product), normalised when its length
   is not zero.
   Remaining difference: all 100 words differ and the frame is 288 bytes against retail's 400: the angle wrap and the two-rotation path are not yet written out as retail has them. */
Vec2 f_0b1270(const Vec2 *a, const Vec2 *b, const Vec2 *c)
{
    Vec2 ab = *b - *a;
    Vec2 ac = *c - *a;
    float k = ab.x * ac.y - ab.y * ac.x;
    Vec2 n;
    n.x = -ab.y * k;
    n.y = ab.x * k;
    float len = __builtin_sqrtf(n.x * n.x + n.y * n.y);
    if (len != 0.0f) {
        float s = 1.0f / len;
        n.x = n.x * s;
        n.y = n.y * s;
    }
    return n;
}

extern "C" {
Vec2 f_0b1470(const Vec2 *a, const Vec2 *b, const Vec2 *c);
}

/* @draft 0x0b1470 us f_0b1470
   WHAT IT DOES: Takes three points A, B and C. Forms the normal of the edge A to B scaled by
   the cross product of the two edges (normalised when its length is not zero), projects the
   edge A to C onto it, and returns one of three vectors: the edge B to C when the offset of
   B plus the projection is shorter than A to C, the edge A to C when the offset is not shorter
   than the projected length, and otherwise the projection itself.
   Remaining difference: 186 of 207 words differ and the frame is 796 bytes against 828; the sqrt NaN fallbacks and the store order of the temporaries are not yet matched. */
Vec2 f_0b1470(const Vec2 *a, const Vec2 *b, const Vec2 *c)
{
    Vec2 ab = *b - *a;
    Vec2 ac = *c - *a;
    Vec2 bc = *c - *b;
    float k = ab.x * ac.y - ab.y * ac.x;
    Vec2 n;
    n.x = -ab.y * k;
    n.y = ab.x * k;
    float len = __builtin_sqrtf(n.x * n.x + n.y * n.y);
    if (len != 0.0f) {
        float s = 1.0f / __builtin_sqrtf(n.x * n.x + n.y * n.y);
        n.x = s * n.x;
        n.y = s * n.y;
    }
    float al = __builtin_sqrtf(ac.x * ac.x + ac.y * ac.y);
    float d = ac.x * n.x + ac.y * n.y;
    Vec2 proj = n * d;
    Vec2 q;
    q.x = ab.x + proj.x;
    q.y = ab.y + proj.y;
    float ql = __builtin_sqrtf(q.x * q.x + q.y * q.y);
    if (ql < al)
        return bc;
    float t = __builtin_sqrtf(q.x * q.x + bc.y * bc.y);
    float ql2 = __builtin_sqrtf(q.x * q.x + q.y * q.y);
    if (ql2 < t)
        return ac;
    return proj;
}

/* @draft 0x0b1ccc us f_0b1ccc
   WHAT IT DOES: For each record of the list, takes the segment from its first pair to its
   second pair, projects the third point (the first two words of the query) onto it through
   0x0b1470, and keeps the shortest result below 50000. The output is the negated kept vector
   as a plane (x, 0, z, 1.0). Returns whether any record was kept.
   Remaining difference: 103 of 116 words differ and the frame is 376 bytes against 464 (the stack copies of the segment ends and the normalisation temporaries). */
int f_0b1ccc(const PlaneList *o, const PlaneRec *q, PlaneRec *out)
{
    Vec2 c;
    c.x = q->x;
    c.y = q->z;
    float best = 50000.0f;
    Vec2 mn;
    mn.x = best;
    mn.y = best;
    int found = 0;
    int i = 0;
    if (o->m0 != 0) {
        do {
            PlaneRec *e = o->m8[i];
            Vec2 p0;
            p0.x = e->x;
            p0.y = e->y;
            Vec2 p1;
            p1.x = e->z;
            p1.y = e->w;
            Vec2 r = f_0b1470(&p0, &p1, &c);
            float len = __builtin_sqrtf(r.x * r.x + r.y * r.y);
            if (len < best) {
                best = len;
                mn.x = -r.x;
                mn.y = -r.y;
                found = 1;
            }
            i++;
        } while (i < o->m0);
    }
    out->x = mn.x;
    out->y = 0.0f;
    out->z = mn.y;
    out->w = 1.0f;
    return found;
}

/* @draft 0x0b1e9c us f_0b1e9c
   WHAT IT DOES: The same search as 0x0b1ccc, which also keeps the index of the shortest
   record; when one is found it writes the record's two end pairs as plane-form values to the
   two extra outputs. Returns whether a record was kept.
   Remaining difference: 129 of 143 words differ and the frame is 484 bytes against 572 (the output and segment temporaries are not yet placed as retail does). */
int f_0b1e9c(const PlaneList *o, const PlaneRec *q, PlaneRec *out, PlaneRec *seg0, PlaneRec *seg1)
{
    Vec2 c;
    c.x = q->x;
    c.y = q->z;
    float best = 50000.0f;
    Vec2 mn;
    mn.x = best;
    mn.y = best;
    int found = 0;
    int bestIdx = 0;
    int i = 0;
    if (o->m0 != 0) {
        do {
            PlaneRec *e = o->m8[i];
            Vec2 p0;
            p0.x = e->x;
            p0.y = e->y;
            Vec2 p1;
            p1.x = e->z;
            p1.y = e->w;
            Vec2 r = f_0b1470(&p0, &p1, &c);
            float len = __builtin_sqrtf(r.x * r.x + r.y * r.y);
            if (len < best) {
                best = len;
                mn.x = -r.x;
                mn.y = -r.y;
                bestIdx = i;
                found = 1;
            }
            i++;
        } while (i < o->m0);
    }
    out->x = mn.x;
    out->y = 0.0f;
    out->z = mn.y;
    out->w = 1.0f;
    if (found == 1) {
        PlaneRec *e = o->m8[bestIdx];
        seg0->x = e->x;
        seg0->y = 0.0f;
        seg0->z = e->y;
        seg0->w = 1.0f;
        seg1->x = e->z;
        seg1->y = 0.0f;
        seg1->z = e->w;
        seg1->w = 1.0f;
    }
    return found;
}

extern "C" {
float f_09a86c(float y, float x);
}

/* A point on the ground plane: x, an unused height and z. */
struct Pt3 {
    float x, y, z;
};

static inline float Len2(const Vec2 &v)
{
    return __builtin_sqrtf(v.x * v.x + v.y * v.y);
}

/* @draft 0x0b2a00 us f_0b2a00
   WHAT IT DOES: Walks the segment from the first point to the second against every edge of the
   list. For each edge that the segment crosses (both ends of the segment on opposite sides of
   the edge and both ends of the edge on opposite sides of the segment) it finds the crossing
   (the segment scaled by the ratio of the two end distances; for a parallel edge it takes the
   nearer end of the edge), and keeps the longest such offset, pushed on by five units. The best
   offset goes to the first output as (x, 0, z); when one was found, the normal of its edge
   (the edge direction turned a quarter) goes to the second output as (x, 0, z, 1.0), and the
   result is 1, otherwise 0.
   Remaining difference: not yet compared word by word against retail; the stack temporaries of
   the by-value vectors are not matched. */
extern "C" int f_0b2a00(const PlaneList *o, const Pt3 *pa, const Pt3 *pb, Pt3 *out, PlaneRec *outn)
{
    Vec2 B;
    B.x = pb->x;
    B.y = pb->z;
    Vec2 A;
    A.x = pa->x;
    A.y = pa->z;
    Vec2 best;
    best.x = 0.0f;
    best.y = 0.0f;
    float bestLen = 0.0f;
    int found = 0;
    int bestIdx = 0;
    int i = 0;
    if (o->m0 != 0) {
        do {
            const PlaneRec *e = o->m8[i];
            float dx = B.x - A.x;
            float dy = B.y - A.y;
            float t1 = dx * (e->y - B.y) + dy * (B.x - e->x);
            float t2 = dx * (e->w - B.y) + dy * (B.x - e->z);
            if (t1 * t2 > 0.0f)
                goto next;
            {
                float u1 = (e->x - e->z) * (B.y - e->y) + (e->y - e->w) * (e->x - B.x);
                float u2 = (e->x - e->z) * (A.y - e->y) + (e->y - e->w) * (e->x - A.x);
                if (u1 * u2 > 0.0f)
                    goto next;
                float a1 = u1 < 0.0f ? -u1 : u1;
                float a2 = u2 < 0.0f ? -u2 : u2;
                Vec2 r;
                if (a1 != 0.0f || a2 != 0.0f) {
                    float s = a2 / (a1 + a2);
                    r.y = dy * s;
                    r.x = dx * s;
                } else if (B.x == A.x) {
                    float z0 = e->y - B.y;
                    float z1 = e->w - B.y;
                    r.y = z0;
                    if (z0 < z1)
                        r.x = e->x - B.x;
                    else
                        r.x = e->z - B.x;
                } else {
                    float x0 = e->x - B.x;
                    float x1 = e->z - B.x;
                    r.x = x0;
                    if (x0 < x1)
                        r.y = e->y - B.y;
                    else
                        r.y = e->w - B.y;
                }
                if (!(bestLen < Len2(r)))
                    goto next;
                bestLen = Len2(r);
                best = r;
                float l = Len2(best);
                Vec2 n;
                n.x = best.x * (1.0f / l);
                n.y = best.y * (1.0f / l);
                best.x = n.x * 5.0f + r.x;
                best.y = n.y * 5.0f + r.y;
                found = 1;
                bestIdx = i;
            }
        next:
            i++;
        } while (i < o->m0);
    }
    out->x = best.x;
    out->z = best.y;
    out->y = 0.0f;
    if (found == 1) {
        const PlaneRec *e = o->m8[bestIdx];
        Vec2 d;
        d.x = e->z - e->x;
        d.y = e->w - e->y;
        float l = Len2(d);
        float s = 1.0f / l;
        Vec2 u;
        u.y = d.y * s;
        u.x = d.x * s;
        Angle ang;
        ang.a = f_09a86c(u.y, u.x);
        f_099b98(&ang);
        Vec2 v;
        v.x = 0.0f;
        v.y = 1.0f;
        f_09b394(ang, &v.x, &v.y);
        outn->x = v.x;
        outn->y = 0.0f;
        outn->z = v.y;
        outn->w = 1.0f;
    }
    return found;
}

extern "C" {
float f_09a07c(float a);
}

/* Tests whether the segment A to B crosses the edge e (its two ends on opposite sides of the
   segment and the segment's ends on opposite sides of the edge). On a crossing it returns 1 and
   the distances of the segment's two ends from the edge's line. */
static inline int CrossesEdge(const PlaneRec *e, const Vec2 &A, const Vec2 &B, float &a1, float &a2)
{
    float dx = B.x - A.x;
    float dy = B.y - A.y;
    float t1 = dx * (e->y - B.y) + dy * (B.x - e->x);
    float t2 = dx * (e->w - B.y) + dy * (B.x - e->z);
    if (t1 * t2 > 0.0f)
        return 0;
    float u1 = (e->x - e->z) * (B.y - e->y) + (e->y - e->w) * (e->x - B.x);
    float u2 = (e->x - e->z) * (A.y - e->y) + (e->y - e->w) * (e->x - A.x);
    if (u1 * u2 > 0.0f)
        return 0;
    a1 = u1 < 0.0f ? -u1 : u1;
    a2 = u2 < 0.0f ? -u2 : u2;
    return 1;
}

/* @draft 0x0b2120 us f_0b2120
   WHAT IT DOES: Slides a displacement along the edges of the list. It walks the segment from
   the first point to the second against every edge, keeping the longest crossing offset (as in
   0x0b2a00, pushed on by the float argument). The offset is stored to the in-out vector; when
   a crossing was found, the vector's angle against the crossing edge decides whether the
   neighbouring edge (the next vertex pair or the previous) also blocks the shifted segment,
   and if so the offset is scaled back to that edge and pushed on again. The in-out vector is
   finally increased by the offset. Returns whether a crossing was found.
   Remaining difference: not yet compared word by word against retail; stack temporaries of the
   by-value vectors not matched. */
extern "C" int f_0b2120(const PlaneList *o, const Pt3 *pa, const Pt3 *pb, Vec2 *out, float eps)
{
    Vec2 B;
    B.x = pb->x;
    B.y = pb->z;
    Vec2 A;
    A.x = pa->x;
    A.y = pa->z;
    Vec2 best;
    best.x = 0.0f;
    best.y = 0.0f;
    float bestLen = 0.0f;
    int found = 0;
    int bestIdx = 0;
    int i = 0;
    if (o->m0 != 0) {
        do {
            const PlaneRec *e = o->m8[i];
            float a1, a2;
            if (CrossesEdge(e, A, B, a1, a2)) {
                float dx = B.x - A.x;
                float dy = B.y - A.y;
                Vec2 r;
                if (a1 != 0.0f || a2 != 0.0f) {
                    float s = a2 / (a1 + a2);
                    r.y = dy * s;
                    r.x = dx * s;
                } else if (B.x == A.x) {
                    float z0 = e->y - B.y;
                    float z1 = e->w - B.y;
                    r.y = z0;
                    if (z0 < z1)
                        r.x = e->x - B.x;
                    else
                        r.x = e->z - B.x;
                } else {
                    float x0 = e->x - B.x;
                    float x1 = e->z - B.x;
                    r.x = x0;
                    if (x0 < x1)
                        r.y = e->y - B.y;
                    else
                        r.y = e->w - B.y;
                }
                if (bestLen < Len2(r)) {
                    bestLen = Len2(r);
                    best = r;
                    float l = Len2(best);
                    Vec2 n;
                    n.x = best.x * (1.0f / l);
                    n.y = best.y * (1.0f / l);
                    best.x = n.x * eps + r.x;
                    best.y = n.y * eps + r.y;
                    found = 1;
                    bestIdx = i;
                }
            }
            i++;
        } while (i < o->m0);
    }
    out->x = best.x;
    out->y = best.y;
    if (found == 0)
        return found;

    const PlaneRec *e = o->m8[bestIdx];
    Vec2 d;
    d.x = e->z - e->x;
    d.y = e->w - e->y;
    float edgeAng = f_09a9dc(d.y, d.x);
    Vec2 v;
    v.x = -out->x;
    v.y = -out->y;
    float vAng = -f_09a9dc(v.y, v.x);
    float vLen = Len2(v);
    Angle diff;
    diff.a = vAng - -edgeAng;
    f_099b98(&diff);
    if (diff.a < 0.0f)
        diff.a = -diff.a;
    float along = vLen * f_09a07c(diff.a);
    Vec2 slide;
    slide.x = along;
    slide.y = 0.0f;
    Angle t1;
    t1.a = edgeAng;
    f_099b98(&t1);
    f_09b394(t1, &slide.x, &slide.y);
    Vec2 push;
    push.x = 0.0f;
    push.y = eps;
    Angle t2;
    t2.a = edgeAng;
    f_099b98(&t2);
    f_09b394(t2, &push.x, &push.y);
    best.x = slide.x + push.x;
    best.y = slide.y + push.y;

    const PlaneRec *n;
    Angle da;
    if (diff.a < 1.5707963705062866f) {
        n = (const PlaneRec *)((const char *)e + 8);
        da.a = -f_09a9dc(n->w - n->y, n->z - n->x) - -edgeAng;
    } else {
        n = (const PlaneRec *)((const char *)e - 8);
        da.a = -edgeAng + f_09a9dc(n->w - n->y, n->z - n->x);
    }
    f_099b98(&da);
    if (da.a < -1.5717964172363281f)
        da.a = da.a + 3.1415927410125732f;
    if (da.a > 1.5717964172363281f)
        da.a = da.a - 3.1415927410125732f;
    if (da.a < 0.0f) {
        Vec2 nB;
        nB.x = pa->x + out->x;
        nB.y = pa->z + out->y;
        Vec2 nA;
        nA.x = nB.x + best.x;
        nA.y = nB.y + best.y;
        float c1, c2;
        if (CrossesEdge(n, nA, nB, c1, c2)) {
            float ratio = c1 / (c1 + c2);
            best.y = best.y * ratio;
            best.x = best.x * ratio;
            Vec2 neg;
            neg.x = -best.x;
            neg.y = -best.y;
            float l = Len2(neg);
            float s = 1.0f / l;
            Vec2 u;
            u.y = neg.y * s;
            u.x = neg.x * s;
            best.y = best.y + u.y * eps;
            best.x = best.x + u.x * eps;
        }
    }
    out->x = out->x + best.x;
    out->y = out->y + best.y;
    return found;
}


/* The height query of the course areas, reached through the map manager. */
struct CourseAreas2 {
    float f_0e2944(float x, float y, float z);
};
struct MapMgr2 {
    CourseAreas2 *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas2 m12240;
};
extern MapMgr2 D_23c820;

/* The rotation helper used all over the body: wrap the angle, then rotate (x, y) by it. */
static inline void Rot(float ang, float *x, float *y)
{
    Angle t;
    t.a = ang;
    f_099b98(&t);
    f_09b394(t, x, y);
}

struct PVec {
    float x, y, z, w;
};

#define SQ3(a, b, c) ((a) * (a) + (b) * (b) + (c) * (c))

/* Sweep the outline vertices (from the A to the B arrays) across the edge ep: for every vertex
   path that crosses the edge, form the overshoot, and keep the longest one, pushed on by ten
   units. */
#define SWEEP_EDGE(ep, TRACK, LBL)                                                             \
    {                                                                                       \
        float ex = (ep)[0] - (ep)[2];                                                       \
        float ey = (ep)[1] - (ep)[3];                                                       \
        short k;                                                                            \
        for (k = 0; k < o->m4->n; k++) {                                                    \
            {                                                                               \
                dA = ex * (Ay[k] - (ep)[1]) + ey * ((ep)[0] - Ax[k]);                          \
                dB = ex * (By[k] - (ep)[1]) + ey * ((ep)[0] - Bx[k]);                          \
                pA = dA * dB;                                                      \
                if (pA > 0.0f)                                                           \
                    continue;                                                  \
                sA = (Ax[k] - Bx[k]) * ((ep)[1] - Ay[k]) + (Ay[k] - By[k]) * (Ax[k] - (ep)[0]);            \
                sB = (Ax[k] - Bx[k]) * ((ep)[3] - Ay[k]) + (Ay[k] - By[k]) * (Ax[k] - (ep)[2]);            \
                pB = sA * sB;                                                      \
                if (pB > 0.0f)                                                           \
                    continue;                                                  \
                aA = dA < 0.0f ? -dA : dA;                                      \
                aB = dB < 0.0f ? -dB : dB;                                      \
                if (aA == 0.0f && aB == 0.0f) {                                       \
                    if (Ax[k] == Bx[k]) {                                                         \
                        dA = (ep)[1] - Ay[k];                                               \
                        dB = (ep)[3] - Ay[k];                                               \
                        if (dA < dB) {                                                \
                            V1808.y = dA;                                                \
                            V1808.x = (ep)[0] - Ax[k];                                         \
                        } else {                                                            \
                            V1808.y = dB;                                                \
                            V1808.x = (ep)[2] - Ax[k];                                         \
                        }                                                                   \
                    } else {                                                                \
                        dA = (ep)[0] - Ax[k];                                               \
                        dB = (ep)[2] - Ax[k];                                               \
                        if (dA < dB)                                                  \
                            V1808.y = (ep)[1] - Ay[k];                                         \
                        else                                                                \
                            V1808.y = (ep)[3] - Ay[k];                                         \
                        V1808.x = dA;                                                    \
                    }                                                                       \
                } else {                                                                    \
                    float fr = aB / (aA + aB);                                     \
                    V1808.x = (Ax[k] - Bx[k]) * fr;                                               \
                    V1808.y = (Ay[k] - By[k]) * fr;                                               \
                }                                                                           \
                if (best < __builtin_sqrtf(V1808.x * V1808.x + V1808.y * V1808.y)) {        \
                    best = __builtin_sqrtf(V1808.x * V1808.x + V1808.y * V1808.y);          \
                    V1824 = V1808;                                                          \
                    float il = 1.0f / __builtin_sqrtf(V1824.x * V1824.x + V1824.y * V1824.y); \
                    V2048.y = il * V1824.y;                                                 \
                    V2048.x = il * V1824.x;                                                 \
                    V1824 = V2048;                                                          \
                    V1840 = V2048;                                                          \
                    V2016 = V2048;                                                          \
                    float uy = V1824.y * eps;                                             \
                    float ux = V1824.x * eps;                                             \
                    V1824.x = ux + V1808.x;                                                 \
                    V1824.y = uy + V1808.y;                                                 \
                    V2032 = V2048;                                                          \
                    if (TRACK) {                                                            \
                        bestEdge = (unsigned short)i;                                       \
                        bestVert = (unsigned short)k;                                       \
                        w.a[0] = V1808.x;                                                   \
                        w.a[2] = V1808.y;                                                   \
                    }                                                                       \
                }                                                                           \
            }                                                                               \
        }                                                                                   \
    }

struct Flag {
    unsigned short v;
    Flag() {}
};

/* @draft 0x0b2f18 us f_0b2f18
   WHAT IT DOES: Moves a car outline (the shape at the list's offset 4: a bounding circle and up
   to sixteen vertices) from the position Q to the position P (the orientations are the two
   float arguments) against the wall edges of the list, and reports how it was blocked. Edges
   are first culled in a frame turned along the motion; the vertices of the outline at both
   ends are swept across the surviving edges, the longest overshoot (pushed on by ten units)
   becomes the first correction. The corrected outline is then tested against the remaining
   edges for a vertex bisector contact (result 2) and for edges that cut into the outline
   (result 3). The corrections add up into the first output (x, height, z), the second output
   gets the final slide along the contact edge (height from the course areas), and the
   remaining outputs get the contact vertex angle, a speed, the edge direction and the edge's
   two end points. Returns 0 (no contact) to 3.
   DRAFT: complete transcription of every path; size 14,200 vs 14,328 bytes. Proven so far
   (each matches retail's code at that point): flags is an array of a class with an empty
   constructor (Flag), declared after result = 0 and before Qp, which gives retail's empty
   127-step-32 loop and keeps the frame offsets; every loop indexes the edge points as Vec2
   pts[128] through short jj = i * 2, storing through a float pointer (retail's separate
   &pts + jj*8 base) and reading pts[jj] / pts[jj + 1]; the edge loops of the sweep and of the
   second look, the later sweep (from istart), and the two later edge loops (the count loop and the seg loop, whose seg copy is
   field by field as in retail's lwc1/swc1), are for loops with "if (flags[i].v) continue;",
   whose continue prediction (56%) makes bb-reorder chain the increment first and put the bodies
   out of line as in retail. All 117 calls now come in retail's order. The first correction's bounds are single
   expressions (xlo = -(o->m4->r + sqrtf(..)), xhi = sqrtf(len) + r + sqrtf(..)): the r operand
   stays a MEM through the shape pointer loaded before the sqrt, so retail reloads o->m4 only once
   (after len), and so are the later bounds and radius sums; the second cull loop has retail's while guard. Inner loops whose tests skip to
   the next element are for loops with continue (not goto to the increment), which gives
   retail's out-of-line placement of the code after the first test. Open: retail keeps hitAny in memory (spilled) and hoists the angle addresses and the
   constant 1 out of the first cull loop; the block with f_0b1b28 at retail 0x1e78 is still
   placed differently (resolved: it was the seg loop). The seg loop's edge ends ea and eb are
   written at each use (retail recomputes (s2 + 1) % 2 per use). Register choice and scheduling
   still differ throughout.
   One-cycle diagnosis, count-loop body: retail re-forms ep after the inner loop (addu s1,t2,s1)
   with base addressing (addiu t2,sp,496); a per-use ep gives offset addressing (496(a0)), so ep
   is a pointer variable and the re-forming is reload rematerialising it under pressure. Retail
   also spills hitAny (2284) where this keeps it in s6.
   Count-loop inner k loop (retail 0x2434..0x24d0): ep is re-formed as the k loop's first
   statement. cse1 gives the in-loop &pts[jj0] its own pseudo, so gcse does not load-PRE
   ep[0]/ep[1] against the pre-loop ex/ey loads; loop.c hoists the address and it survives as
   retail's move a0,v0, giving retail's bottom-tested loop with ep reloaded at each use. (With
   one ep, gcse PREs those loads into the latch: beqzl exit, latch reloads, j back.) Reading
   ex/ey as pts[jj0] - pts[jj0 + 1] also stops the PRE but gives offset addressing (496(v0))
   where retail has base addressing. The k loop reads o->m4->n in its test and in the modulus
   (no local n): gcse replaces the fully redundant in-loop loads with copies of the reaching
   register, which are retail's move a1,v1 / move t0,v1 and the in-loop move a1,t0. Still
   different here: retail re-forms ep after the loop (addu s1,t2,s1);
   after the loop retail computes both V464 differences into $f0/$f1 and copies them to the
   argument registers, where this computes x straight into $f13.
   Open: the second look's xi selection. Retail keeps xi = V464.x inline and puts both other
   cases out of line; the != form here and an == else-if chain (tried once) both differ.
   Layout aids with no counterpart in the original: the two unused angle locals (retail leaves
   a hole of two slots after the first outline loop) and the packed scratch array tt.
   Retail also reads a stale vector in the slide's second box (V1808 is the leftover of the
   last cull iteration); that is kept here as in retail. */
extern "C" int f_0b2f18(PlaneList *o, const Pt3 *P, const Pt3 *Q, float *out3, float *out4,
                        float *outAng, float *outSpd, float *out7, float fx, float fy,
                        float *outA, float *outB)
{
#define V448 (*(Vec2 *)&v448)
#define V464 (*(Vec2 *)&v464)
#define V480 (*(Vec2 *)&v480)
    float tt[12];
#define dA tt[0]
#define dB tt[1]
#define sA tt[2]
#define sB tt[3]
#define aA tt[4]
#define aB tt[5]
#define pA tt[8]
#define pB tt[9]
    V4 w;
    float Ax[16], Ay[16], Bx[16], By[16], Cx[16], Cy[16];
    PVec v448, v464, v480;
    Vec2 pts[128];
#define PJ(i) pts[(short)((i) * 2)]
#define PK(i) pts[(short)((i) * 2) + 1]
    int bestEdge, bestVert, result, hitAny, side;
    float best, bestLen2, ang, xlo, xhi, yhi, ylo, rad, zero, ang2, xi;
    short i, k;
    unsigned short cnt;

    float eps = 10.0f;
    w.a[0] = 0.0f;
    w.a[1] = 0.0f;
    w.a[2] = 0.0f;
    w.a[3] = 0.0f;
    bestEdge = 0xffff;
    bestVert = 0xffff;
    result = 0;
    Flag flags[128];
    PVec v_Qp;
#define Qp (*(Vec2 *)&v_Qp)
    PVec v_Pp;
#define Pp (*(Vec2 *)&v_Pp)
    PVec v_V1808;
#define V1808 (*(Vec2 *)&v_V1808)
    PVec v1824;
#define V1824 (*(Vec2 *)&v1824)
    PVec v_V1840;
#define V1840 (*(Vec2 *)&v_V1840)
    PVec v_V1856;
#define V1856 (*(Vec2 *)&v_V1856)
    PVec v_V1872;
#define V1872 (*(Vec2 *)&v_V1872)
    PVec v_V1888;
#define V1888 (*(Vec2 *)&v_V1888)
    PVec v_V1904;
#define V1904 (*(Vec2 *)&v_V1904)
    PlaneRec seg;
    PVec v_V1936;
#define V1936 (*(Vec2 *)&v_V1936)
    V4 D, acc;
    PVec v_V1984;
#define V1984 (*(Vec2 *)&v_V1984)
    PVec v_V2000;
#define V2000 (*(Vec2 *)&v_V2000)
    PVec v_V2016;
#define V2016 (*(Vec2 *)&v_V2016)
    PVec v_V2032;
#define V2032 (*(Vec2 *)&v_V2032)
    PVec v_V2048;
#define V2048 (*(Vec2 *)&v_V2048)
    V4 v2064, v2080, v2096;
    out3[0] = 0.0f;
    out3[1] = 0.0f;
    out3[2] = 0.0f;
    out3[3] = 0.0f;
    out4[0] = 0.0f;
    out4[1] = 0.0f;
    out4[2] = 0.0f;
    out4[3] = 0.0f;
    hitAny = 0;
    *outAng = 0.0f;
    *outSpd = 0.0f;
    if (o->m0 == 0)
        return 0;

    /* Frame along the motion, and the outline's reach. */
    Qp.x = Q->x;
    Qp.y = Q->z;
    Pp.x = P->x;
    Pp.y = P->z;
    V1872.x = Pp.x - Qp.x;
    V1872.y = Pp.y - Qp.y;
    V1808 = V1872;
    V1840 = V1872;
    V1856 = V1872;
    ang = -f_09a9dc(V1808.y, V1808.x);
    rad = o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
    xlo = -rad;
    xhi = __builtin_sqrtf(V1808.x * V1808.x + V1808.y * V1808.y) - xlo;
    yhi = rad;
    ylo = xlo;

    /* Cull the edges: flag 1 = outside the box around the motion. */
    i = 0;
    while (i < o->m0) {
        PlaneRec *e = o->m8[i];
        short jj = i * 2;
        float *ep = &pts[jj].x;
        ep[0] = e->x;
        ep[1] = e->y;
        V1808 = pts[jj];
        V1808.x = V1808.x - Qp.x;
        V1808.y = V1808.y - Qp.y;
        Rot(ang, &V1808.x, &V1808.y);
        ep[3] = e->w;
        ep[2] = e->z;
        V1824 = pts[jj + 1];
        V1824.x = V1824.x - Qp.x;
        V1824.y = V1824.y - Qp.y;
        Rot(ang, &V1824.x, &V1824.y);
        short j = i;
        i = i + 1;
        flags[j].v = 1;
        if (V1808.x < xlo && V1824.x < xlo)
            continue;
        if (xhi < V1808.x && xhi < V1824.x)
            continue;
        if (yhi < V1808.y && yhi < V1824.y)
            continue;
        if (V1808.y < ylo && V1824.y < ylo)
            continue;
        hitAny = 1;
        flags[j].v = 0;
    }
    if (!hitAny)
        return 0;

    /* The outline at the start (A, turned by fy) and at the end (B, turned by fx). */
    best = 0.0f;
    V1824.x = 0.0f;
    V1824.y = 0.0f;
    i = 0;
    if (o->m4->n > 0) {
        do {
            V448 = o->m4->v[i];
            Rot(-fy, &V448.x, &V448.y);
            V448.x = V448.x + Q->x;
            V448.y = V448.y + Q->z;
            Ax[i] = V448.x;
            Ay[i] = V448.y;
            V448 = o->m4->v[i];
            Rot(-fx, &V448.x, &V448.y);
            V448.x = V448.x + P->x;
            V448.y = V448.y + P->z;
            Bx[i] = V448.x;
            By[i] = V448.y;
            i = i + 1;
        } while (i < o->m4->n);
    }

    Angle pad1, pad2;
    __asm__("" : : "m"(pad1), "m"(pad2));

    /* Sweep the outline across every surviving edge. */
    for (i = 0; i < o->m0; i++) {
        if (flags[i].v != 0)
            continue;
        short jj = i * 2;
        float *ep = &pts[jj].x;
        SWEEP_EDGE(ep, 1, sw1)
    }

    /* First correction. */
    V1888 = Pp;
    out3[0] = V1824.x;
    out3[2] = V1824.y;
    if (bestEdge != 0xffff) {
        V1888.x = V1888.x + V1824.x;
        V1888.y = V1888.y + V1824.y;
        result = 1;
        i = 0;
        if (o->m4->n > 0) {
            do {
                Bx[i] = Bx[i] + V1824.x;
                By[i] = By[i] + V1824.y;
                i = i + 1;
            } while (i < o->m4->n);
        }
        V1840.x = V1888.x - Qp.x;
        V1840.y = V1888.y - Qp.y;
        V1808 = V1840;
        V1872 = V1840;
        V1856 = V1840;
        ang = -f_09a9dc(V1808.y, V1808.x);
        xlo = -(o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz));
        xhi = __builtin_sqrtf(V1808.x * V1808.x + V1808.y * V1808.y) + o->m4->r
              + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
        yhi = o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
        ylo = -(o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz));
        i = 0;
        while (i < o->m0) {
            short jj = i * 2;
            V1808 = pts[jj];
            V1808.x = V1808.x - Qp.x;
            V1808.y = V1808.y - Qp.y;
            Rot(ang, &V1808.x, &V1808.y);
            V1824 = pts[jj + 1];
            V1824.x = V1824.x - Qp.x;
            V1824.y = V1824.y - Qp.y;
            Rot(ang, &V1824.x, &V1824.y);
            short j = i;
            i = i + 1;
            flags[j].v = 1;
            if (V1808.x < xlo && V1824.x < xlo)
                continue;
            if (xhi < V1808.x && xhi < V1824.x)
                continue;
            if (yhi < V1808.y && yhi < V1824.y)
                continue;
            if (V1808.y < ylo && V1824.y < ylo)
                continue;
            flags[j].v = 0;
        }
    }

    /* Second look: the outline after the first correction against the vertex contacts. */
    i = 0;
    if (o->m4->n > 0) {
        do {
            Cx[i] = Bx[i];
            Cy[i] = By[i];
            i = i + 1;
        } while (i < o->m4->n);
    }
    zero = 0.0f;
    V1872.x = zero;
    V1872.y = zero;
    bestLen2 = zero;
    ang2 = zero;
    for (i = 0; i < o->m0; i++) {
        if (flags[i].v != 0)
            continue;
            {
                short jj = i * 2;
                float *ep = &pts[jj].x;
                float ex = ep[0] - ep[2];
                float ey = ep[1] - ep[3];
                for (k = 0; k < o->m4->n; k++) {
                    {
                        short k1 = (k + 1) % o->m4->n;
                        float c0x = Cx[k], c0y = Cy[k], c1x = Cx[k1], c1y = Cy[k1];
                        dA = ex * (c0y - ep[1]) + ey * (ep[0] - c0x);
                        dB = ex * (c1y - ep[1]) + ey * (ep[0] - c1x);
                        pA = dA * dB;
                        if (pA > 0.0f)
                            continue;
                        sA = (c0x - c1x) * (ep[1] - c0y) + (c0y - c1y) * (c0x - ep[0]);
                        sB = (c0x - c1x) * (ep[3] - c0y) + (c0y - c1y) * (c0x - ep[2]);
                        pB = sA * sB;
                        if (pB > 0.0f)
                            continue;
                        V464.x = c0x;
                        V464.y = c0y;
                        side = 1;
                        V480.x = Cx[k1];
                        V480.y = Cy[k1];
                        if (!(f_0b1b28(&V464, &V480, (const Vec2 *)&ep[2]) > 0.0f))
                            side = 0;
                        {
                            Vec2 *vv = (Vec2 *)((char *)o->m8[i] + 8 * (side ^ 1));
                            side = side ^ 1;
                            V448.x = vv[1].x - vv[0].x;
                            V448.y = vv[1].y - vv[0].y;
                            V1808.x = vv[-1].x - vv[0].x;
                            V1808.y = vv[-1].y - vv[0].y;
                            V1904.x = V448.x + V1808.x;
                            V1904.y = V448.y + V1808.y;
                            Vec2 *rv = &((Vec2 *)pts)[2 * i + side];
                            V464.y = Cy[k] - rv->y;
                            V464.x = Cx[k] - rv->x;
                            V480.y = Cy[k1] - rv->y;
                            V480.x = Cx[k1] - rv->x;
                            V1840 = V1904;
                            V1824 = V1904;
                            V1856 = V1904;
                            ang = -f_09a9dc(V1824.y, V1824.x);
                            Rot(ang, &V464.x, &V464.y);
                            Rot(ang, &V480.x, &V480.y);
                            if (V464.y * V480.y > 0.0f)
                                continue;
                            if (V464.y != 0.0f) {
                                if (V480.y == 0.0f)
                                    xi = V480.x;
                                else
                                    xi = V464.x - V464.y * ((V480.x - V464.x) / (V480.y - V464.y));
                            } else
                                xi = V464.x;
                            V1840.x = Pp.x - Qp.x;
                            V1840.y = Pp.y - Qp.y;
                            V1856 = V1840;
                            V1904 = V1840;
                            float l1 = __builtin_sqrtf(V1904.x * V1904.x + V1904.y * V1904.y);
                            V1904.x = Cx[k] - Ax[k];
                            V1904.y = Cy[k] - Ay[k];
                            float l2 = __builtin_sqrtf(V1904.x * V1904.x + V1904.y * V1904.y);
                            short k2 = (k + 1) % o->m4->n;
                            V1904.x = Cx[k2] - Ax[k2];
                            V1904.y = Cy[k2] - Ay[k2];
                            float l3 = __builtin_sqrtf(V1904.x * V1904.x + V1904.y * V1904.y);
                            (void)l1;
                            (void)l2;
                            (void)l3;
                            if (2314.81494140625f < xi)
                                continue;
                            if (xi <= bestLen2)
                                continue;
                            bestEdge = (unsigned short)i;
                            bestLen2 = xi;
                            if (side != 0) {
                                if (o->m0 != 0) {
                                    unsigned short a;
                                    for (a = 0; a < o->m0; a++) {
                                        PlaneRec *q = o->m8[a];
                                        if (vv->x == q->x) {
                                            if (vv->y == q->y)
                                                bestEdge = a;
                                        }
                                    }
                                }
                            }
                            ang2 = ang;
                            V1872.x = -(xi + eps);
                            V1872.y = 0.0f;
                            bestVert = (unsigned short)k;
                            Rot(-ang, &V1872.x, &V1872.y);
                        }
                    }
                }
            }
    }
    if (bestLen2 != 0.0f) {
        result = 2;
        V1824.y = 0.0f;
        V1824.x = eps;
        Rot(-ang2, &V1824.x, &V1824.y);
        out3[0] = out3[0] + V1872.x;
        out3[2] = out3[2] + V1872.y;
        w.a[0] = w.a[0] + (V1872.x + V1824.x);
        w.a[2] = w.a[2] + (V1872.y + V1824.y);
    }

    /* Third look: the outline after the second correction, against the edge boxes. */
    if (result != 0) {
        V1888.x = V1888.x + V1872.x;
        V1888.y = V1888.y + V1872.y;
        i = 0;
        if (o->m4->n > 0) {
            do {
                Bx[i] = Bx[i] + V1872.x;
                By[i] = By[i] + V1872.y;
                i = i + 1;
            } while (i < o->m4->n);
        }
        xlo = V1888.x - (o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz));
        xhi = V1888.x + o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
        yhi = V1888.y + o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
        ylo = V1888.y - (o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz));
        cnt = o->m0;
        if (cnt != 0) {
            i = 0;
            do {
                PlaneRec *e = o->m8[i];
                PJ(i).x = e->x;
                PJ(i).y = e->y;
                PK(i).y = e->w;
                PK(i).x = e->z;
                short j = i;
                i = i + 1;
                flags[j].v = 1;
                if (e->x < xlo && e->z < xlo)
                    continue;
                if (xhi < e->x && xhi < e->z)
                    continue;
                if (yhi < e->y && yhi < e->w)
                    continue;
                if (e->y < ylo && e->w < ylo)
                    continue;
                flags[j].v = 0;
            } while (i < cnt);
            for (i = 0; i < o->m0; i++) {
                if (flags[i].v != 0)
                    continue;
                    {
                        short jj0 = i * 2;
                        float *ep = &pts[jj0].x;
                        float ex = ep[0] - ep[2];
                        float ey = ep[1] - ep[3];
                        for (k = 0; k < o->m4->n; k++) {
                            float *ep = &pts[jj0].x;
                            short k1 = (k + 1) % o->m4->n;
                            dA = ex * (By[k] - ep[1]) + ey * (ep[0] - Bx[k]);
                            dB = ey * (ep[0] - Bx[k1]) + ex * (By[k1] - ep[1]);
                            pA = dA * dB;
                            if (pA > 0.0f)
                                continue;
                            sA = (Bx[k] - Bx[k1]) * (ep[1] - By[k]) + (By[k] - By[k1]) * (Bx[k] - ep[0]);
                            sB = (Bx[k] - Bx[k1]) * (ep[3] - By[k]) + (By[k] - By[k1]) * (Bx[k] - ep[2]);
                            pB = sA * sB;
                            if (pB > 0.0f)
                                continue;
                            break;
                        }
                        if (k < o->m4->n) {
                            V1904.x = 0.0f;
                            bestLen2 = V1904.x;
                            V1904.y = 0.0f;
                            V464.x = ep[2] - ep[0];
                            V464.y = ep[3] - ep[1];
                            ang = -f_09a9dc(V464.y, V464.x);
                            V1856.x = __builtin_sqrtf(V464.x * V464.x + V464.y * V464.y);
                            V1856.y = 0.0f;
                            k = 0;
                            if (o->m4->n > 0) {
                                do {
                                    V1808.x = Bx[k] - ep[0];
                                    V1808.y = By[k] - ep[1];
                                    Rot(ang, &V1808.x, &V1808.y);
                                    Cx[k] = V1808.x;
                                    Cy[k] = -V1808.y;
                                    k = k + 1;
                                } while (k < o->m4->n);
                            }
                            for (k = 0; k < o->m4->n; k++) {
                                if (Cy[k] < 0.0f)
                                    continue;
                                if (Cx[k] < 0.0f)
                                    continue;
                                if (V1856.x < Cx[k])
                                    continue;
                                if (Cy[k] <= bestLen2)
                                    continue;
                                bestEdge = (unsigned short)i;
                                bestVert = (unsigned short)k;
                                bestLen2 = Cy[k];
                            }
                            int n = o->m4->n;
                            for (k = 0; k < n; k++) {
                                {
                                    short k1 = (k + 1) % n;
                                    short lo, hi;
                                    float y;
                                    if (Cx[k] < Cx[k1]) {
                                        lo = k;
                                        hi = k1;
                                    } else {
                                        lo = k1;
                                        hi = k;
                                    }
                                    if (Cx[lo] <= 0.0f && 0.0f <= Cx[hi]) {
                                        if (Cx[hi] - Cx[lo] < 9.999999747378752e-05f) {
                                            y = Cy[k] < Cy[k1] ? Cy[k] : Cy[k1];
                                        } else {
                                            y = Cy[lo] - Cx[lo] * ((Cy[k1] - Cy[k]) / (Cx[k1] - Cx[k]));
                                        }
                                        if (y <= bestLen2)
                                            continue;
                                        bestEdge = (unsigned short)i;
                                        bestVert = (unsigned short)k;
                                        bestLen2 = y;
                                    } else if (Cx[lo] <= V1856.x && V1856.x <= Cx[hi]) {
                                        if (Cx[hi] - Cx[lo] < 9.999999747378752e-05f) {
                                            y = Cy[k] < Cy[k1] ? Cy[k] : Cy[k1];
                                        } else {
                                            y = Cy[lo] + (V1856.x - Cx[lo]) * ((Cy[k1] - Cy[k]) / (Cx[k1] - Cx[k]));
                                        }
                                        if (y <= bestLen2)
                                            continue;
                                        bestEdge = (unsigned short)i;
                                        bestVert = (unsigned short)k;
                                        bestLen2 = y;
                                    }
                                }
                            }
                            if (bestLen2 != 0.0f) {
                                result = 3;
                                V1904.x = 0.0f;
                                V1904.y = -(bestLen2 + eps);
                                Rot(-ang, &V1904.x, &V1904.y);
                                V1808.x = 0.0f;
                                V1808.y = eps;
                                Rot(-ang, &V1808.x, &V1808.y);
                                w.a[0] = w.a[0] - (V1904.x + V1808.x);
                                w.a[2] = w.a[2] - (V1904.y + V1808.y);
                                out3[0] = out3[0] - V1904.x;
                                out3[2] = out3[2] - V1904.y;
                                V1888.x = V1888.x - V1904.x;
                                V1888.y = V1888.y - V1904.y;
                                k = 0;
                                if (o->m4->n > 0) {
                                    do {
                                        Bx[k] = Bx[k] - V1904.x;
                                        By[k] = By[k] - V1904.y;
                                        k = k + 1;
                                    } while (k < o->m4->n);
                                }
                                xlo = -(V1888.x + o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz));
                                xhi = V1888.x + o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
                                yhi = V1888.y + o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
                                ylo = -(V1888.y + o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz));
                                {
                                    short j = i + 1;
                                    cnt = o->m0;
                                    while (j < (int)cnt) {
                                        PlaneRec *e = o->m8[j];
                                        short jj = j;
                                        j = j + 1;
                                        flags[jj].v = 0;
                                        if (e->x < xlo && e->z < xlo)
                                            continue;
                                        if (xhi < e->x && xhi < e->z)
                                            continue;
                                        if (yhi < e->y && yhi < e->w)
                                            continue;
                                        if (e->y < ylo && e->w < ylo)
                                            continue;
                                        flags[jj].v = 0;
                                    }
                                }
                            }
                        }
                    }
            }
        }
    }

    /* Slide along the contact edge (or the contact vertex's edge). */
    Angle a2172;
    a2172.a = 0.0f;
    zero = a2172.a;
    acc.a[0] = zero;
    acc.a[1] = zero;
    acc.a[2] = zero;
    acc.a[3] = zero;
    if (bestEdge != 0xffff) {
        float f22, f20, f24, f21;
        if (result & 1) {
            PlaneRec *e = o->m8[bestEdge];
            V448.x = e->z - e->x;
            V448.y = e->w - e->y;
            f22 = f_09a9dc(V448.y, V448.x);
            f21 = -f22;
            V1808.y = -out3[2];
            V1808.x = -out3[0];
            f20 = -f_09a9dc(V1808.y, V1808.x);
            float lenv = __builtin_sqrtf(V1808.x * V1808.x + V1808.y * V1808.y);
            a2172.a = f20 - f21;
            f_099b98(&a2172);
            if (a2172.a < zero)
                a2172.a = -a2172.a;
            float along = lenv * f_09a07c(a2172.a);
            V1824.y = zero;
            V1824.x = along;
            Rot(f22, &V1824.x, &V1824.y);
            ang = -f_09a9dc(V1824.y, V1824.x);
            V1904.x = zero;
            V1904.y = eps;
            Rot(f22, &V1904.x, &V1904.y);
            acc.a[0] = V1824.x + V1904.x;
            acc.a[1] = zero;
            acc.a[2] = V1824.y + V1904.y;
            acc.a[3] = 1.0f;
            V1824.x = acc.a[0];
            V1824.y = acc.a[2];
        } else {
            Shape *s = o->m4;
            int vn = bestVert + 1;
            V2000.x = s->v[bestVert].x + s->cx;
            V2000.y = s->v[bestVert].y + s->cz;
            V1840 = V2000;
            V1984 = V2000;
            V448 = V2000;
            short nx = (short)(vn % s->n);
            V1840.y = s->v[nx].y + s->cz;
            V1840.x = s->v[nx].x + s->cx;
            V1808 = V1840;
            V1984 = V1840;
            V2000 = V1840;
            Rot(-fx, &V448.x, &V448.y);
            Rot(-fx, &V1808.x, &V1808.y);
            float bx0 = P->x + out3[0];
            float bz0 = P->z + out3[2];
            V448.x = V448.x + bx0;
            V1808.x = V1808.x + bx0;
            V1808.y = V1808.y + bz0;
            V448.y = V448.y + bz0;
            V1840.x = V1808.x - V448.x;
            V1840.y = V1808.y - V448.y;
            V1824 = V1840;
            V1984 = V1840;
            V2000 = V1840;
            f22 = f_09a9dc(V1824.y, V1824.x);
            f24 = -f22;
            f20 = __builtin_sqrtf(out3[0] * out3[0] + out3[1] * out3[1] + out3[2] * out3[2]);
            a2172.a = f24 + f_09a9dc(-out3[2], -out3[0]);
            float along = f20 * f_09a07c(a2172.a);
            V1856.y = zero;
            V1856.x = along;
            Rot(f22, &V1856.x, &V1856.y);
            ang = -f_09a9dc(V1856.y, V1856.x);
            V1904.y = -eps;
            V1904.x = zero;
            Rot(f22, &V1904.x, &V1904.y);
            acc.a[0] = V1856.x + V1904.x;
            acc.a[1] = zero;
            acc.a[2] = V1856.y + V1904.y;
            acc.a[3] = 1.0f;
            V1856.x = acc.a[0];
            V1856.y = acc.a[2];
        }

        /* Cull the edges around the slid outline and find how far it must be pushed back. */
        V448.x = P->x + out3[0];
        V448.y = P->z + out3[2];
        rad = o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
        {
            float la = __builtin_sqrtf(acc.a[0] * acc.a[0] + acc.a[1] * acc.a[1] + acc.a[2] * acc.a[2]);
            xlo = -rad;
            xhi = la - xlo;
            yhi = rad;
        }
        hitAny = 0;
        i = 0;
        while (i < o->m0) {
            {
                PlaneRec *e = o->m8[i];
                short jj = i * 2;
                V1808.x = e->x - V448.x;
                V1808.y = e->y - V448.y;
                Rot(ang, &V1808.x, &V1808.y);
                pts[jj] = V1808;
                V1824.y = e->w - V448.y;
                V1824.x = e->z - V448.x;
                Rot(ang, &V1824.x, &V1824.y);
                pts[jj + 1] = V1824;
                short j = i;
                i = i + 1;
                flags[j].v = 1;
                if (V1808.x < zero && V1824.x < zero)
                    continue;
                if (xhi < V1808.x && xhi < V1824.x)
                    continue;
                if (yhi < V1808.y && yhi < V1824.y)
                    continue;
                if (V1808.y < xlo && V1824.y < xlo)
                    continue;
                hitAny = 1;
                flags[j].v = 0;
            }
        }
        if (hitAny) {
            i = 0;
            best = 0.0f;
            if (o->m4->n > 0) {
                do {
                    V448 = o->m4->v[i];
                    Rot(-fx, &V448.x, &V448.y);
                    V448.x = V448.x + acc.a[0];
                    V448.y = V448.y + acc.a[2];
                    Rot(ang, &V448.x, &V448.y);
                    Bx[i] = V448.x;
                    By[i] = V448.y;
                    i = i + 1;
                } while (i < o->m4->n);
            }
            for (i = 0; i < o->m0; i++) {
                if (flags[i].v != 0)
                    continue;
                    {
                        short jj1 = i * 2;
                        float *ep = &pts[jj1].x;
                        seg.x = ep[0];
                        seg.y = ep[1];
                        seg.z = ep[2];
                        seg.w = ep[3];
                        V1840.x = seg.z - seg.x;
                        V1840.y = seg.w - seg.y;
                        V1936 = V1840;
                        V1984 = V1840;
                        V2000 = V1840;
                        int s2 = 1;
                        if (!(seg.y < seg.w))
                            s2 = 0;
                        s2 = s2 ^ 1;
                        for (k = 0; k < o->m4->n; k++) {
                            {
                                short k1 = (k + 1) % o->m4->n;
                                V1904.y = By[k];
                                V1904.x = Bx[k];
                                V448.x = Bx[k1];
                                V448.y = By[k1];
                                if (V1904.y < V448.y) {
                                    V1984 = V448;
                                    V2000 = V1904;
                                } else {
                                    V1984 = V1904;
                                    V2000 = V448;
                                }
                                if (f_0b1b28((const Vec2 *)&seg.x, (const Vec2 *)&seg.z, &V448) > 0.0f)
                                    continue;
                                {
#define ea (&((Vec2 *)&seg)[s2])
#define eb (&((Vec2 *)&seg)[(s2 + 1) % 2])
                                    float gap8, gap0, g;
                                    if (eb->y < V2000.y)
                                        continue;
                                    if (V1984.y < ea->y)
                                        continue;
                                    if (V2000.y < ea->y)
                                        gap8 = (V2000.x + (ea->y - V2000.y) * ((V1984.x - V2000.x) / (V1984.y - V2000.y))) - ea->x;
                                    else
                                        gap8 = -((ea->x + (V2000.y - ea->y) * ((eb->x - ea->x) / (eb->y - ea->y))) - V2000.x);
                                    if (eb->y < V1984.y)
                                        gap0 = (V2000.x + (eb->y - V2000.y) * ((V1984.x - V2000.x) / (V1984.y - V2000.y))) - eb->x;
                                    else
                                        gap0 = -((ea->x + (V1984.y - ea->y) * ((eb->x - ea->x) / (eb->y - ea->y))) - V1984.x);
                                    g = gap0 < gap8 ? gap0 : gap8;
                                    if (best < g) {
                                        if (g <= __builtin_sqrtf(acc.a[0] * acc.a[0] + acc.a[1] * acc.a[1] + acc.a[2] * acc.a[2])) {
                                            bestEdge = (unsigned short)i;
                                            best = g;
#undef ea
#undef eb
                                        }
                                    }
                                }
                            }
                        }
                    }
            }
            if (0.0f < best) {
                V1824.y = 0.0f;
                V1824.x = -(best + eps);
                Rot(-ang, &V1824.x, &V1824.y);
                acc.a[0] = acc.a[0] + V1824.x;
                acc.a[2] = acc.a[2] + V1824.y;
            }
        }

        /* The other group of edges, against the outline in world coordinates. */
        cnt = o->m0;
        if (o->m2 < cnt) {
            short istart = (bestEdge < o->m2) ? o->m2 : 0;
            V2000.x = P->x + out3[0];
            V2000.y = P->z + out3[2];
            V1984.x = V2000.x + acc.a[0];
            V1984.y = V2000.y + acc.a[2];
            ang = -f_09a9dc(acc.a[2], acc.a[0]);
            rad = o->m4->r + __builtin_sqrtf(o->m4->cx * o->m4->cx + o->m4->cz * o->m4->cz);
            {
                float lv = __builtin_sqrtf(V1808.x * V1808.x + V1808.y * V1808.y);
                xlo = -rad;
                xhi = lv - xlo;
                yhi = rad;
            }
            i = istart;
            hitAny = 0;
            if (i < (int)cnt) {
                do {
                    PlaneRec *e = o->m8[i];
                    PJ(i).x = e->x;
                    PJ(i).y = e->y;
                    PK(i).y = e->w;
                    PK(i).x = e->z;
                    V1808 = PJ(i);
                    V1808.x = V1808.x - V2000.x;
                    V1808.y = V1808.y - V2000.y;
                    Rot(ang, &V1808.x, &V1808.y);
                    V1824 = PK(i);
                    V1824.x = V1824.x - V2000.x;
                    V1824.y = V1824.y - V2000.y;
                    Rot(ang, &V1824.x, &V1824.y);
                    short j = i;
                    i = i + 1;
                    flags[j].v = 1;
                    if (V1808.x < xlo && V1824.x < xlo)
                        continue;
                    if (xhi < V1808.x && xhi < V1824.x)
                        continue;
                    if (yhi < V1808.y && yhi < V1824.y)
                        continue;
                    if (V1808.y < xlo && V1824.y < xlo)
                        continue;
                    hitAny = 1;
                    flags[j].v = 0;
                } while (i < (int)cnt);
                if (hitAny) {
                    best = 0.0f;
                    V1824.x = 0.0f;
                    V1824.y = 0.0f;
                    k = 0;
                    if (o->m4->n > 0) {
                        do {
                            V2032.y = o->m4->v[k].y + o->m4->cz;
                            V2032.x = o->m4->v[k].x + o->m4->cx;
                            V448 = V2032;
                            V2016 = V2032;
                            V1840 = V2032;
                            Rot(-fx, &V448.x, &V448.y);
                            V448.x = V448.x + V2000.x;
                            V448.y = V448.y + V2000.y;
                            Ax[k] = V448.x;
                            Ay[k] = V448.y;
                            Bx[k] = V448.x + acc.a[0];
                            By[k] = V448.y + acc.a[2];
                            k = k + 1;
                        } while (k < o->m4->n);
                    }
                    for (i = istart; i < (int)cnt; i++) {
                        if (flags[i].v != 0)
                            continue;
                        short jj2 = i * 2;
                        float *ep = &pts[jj2].x;
        SWEEP_EDGE(ep, 0, sw2)
                    }
                    acc.a[0] = acc.a[0] + V1824.x;
                    acc.a[2] = acc.a[2] + V1824.y;
                }
            }
        }
        out3[0] = out3[0] + acc.a[0];
        w.a[0] = w.a[0] + acc.a[0];
        w.a[2] = w.a[2] + acc.a[2];
        out3[2] = out3[2] + acc.a[2];
    }

    /* The final slide and the contact data. */
    pA = 0.0f;
    pB = 0.0f;
    D.a[0] = 0.0f;
    D.a[1] = 0.0f;
    D.a[2] = 0.0f;
    D.a[3] = 0.0f;
    if (result == 0)
        return 0;
    {
        float h1 = D_23c820.Areas()->f_0e2944(P->x + out3[0], P->y + out3[1], P->z + out3[2]);
        float h0 = D_23c820.Areas()->f_0e2944(P->x, P->y, P->z);
        out3[1] = h1 - h0;
        v2080.a[0] = P->x + w.a[0];
        v2080.a[1] = P->y + out3[1];
        v2080.a[2] = P->z + w.a[2];
        v2080.a[3] = 1.0f;
        pA = h0;
        w.a[1] = h1 - h0;
        PlaneRec *e = o->m8[bestEdge];
        V448.x = e->z - e->x;
        V448.y = e->w - e->y;
        float eang = f_09a9dc(V448.y, V448.x);
        v2096.a[0] = v2080.a[0] - P->x;
        v2096.a[1] = v2080.a[1] - P->y;
        v2096.a[2] = v2080.a[2] - P->z;
        v2096.a[3] = 1.0f;
        v2064 = v2096;
        Rot(eang, &v2064.a[2], &v2064.a[0]);
        if (v2064.a[0] * v2064.a[0] + v2064.a[2] * v2064.a[2] < 9.999999747378752e-05f) {
            v2064.a[1] = 0.0f;
        } else {
            float q = v2064.a[2] / __builtin_sqrtf(v2064.a[0] * v2064.a[0] + v2064.a[2] * v2064.a[2]);
            if (q < 0.0f)
                q = -q;
            v2064.a[1] = v2064.a[1] * q;
        }
        float vlen = __builtin_sqrtf(SQ3(v2064.a[0], v2064.a[1], v2064.a[2]));
        v2096.a[0] = P->x - Q->x;
        v2096.a[1] = P->y - Q->y;
        v2096.a[2] = P->z - Q->z;
        v2096.a[3] = 1.0f;
        D = v2096;
        if (__builtin_sqrtf(SQ3(D.a[0], D.a[1], D.a[2])) < vlen) {
            float dl = __builtin_sqrtf(SQ3(D.a[0], D.a[1], D.a[2]));
            float vl = __builtin_sqrtf(SQ3(v2064.a[0], v2064.a[1], v2064.a[2]));
            float sc = dl / vl;
            pB = sc;
            v2064.a[0] = v2064.a[0] * sc;
            v2064.a[1] = v2064.a[1] * sc;
            v2064.a[2] = v2064.a[2] * sc;
        }
        v2064.a[1] = v2064.a[1] < 163.3333740234375f ? v2064.a[1] : 163.3333740234375f;
        v2064.a[0] = 0.0f;
        Rot(-eang, &v2064.a[2], &v2064.a[0]);
        *(V4 *)out4 = v2064;
        {
            int vn = bestVert + 1;
            Shape *s = o->m4;
            int modv = vn % s->n;
            (void)modv;
            V2016.y = s->v[bestVert].y + s->cz;
            V2016.x = s->v[bestVert].x + s->cx;
            V448 = V2016;
            V2032 = V2016;
            V2048 = V2016;
            *outAng = -f_09a9dc(V448.x, -V448.y);
        }
        *outSpd = __builtin_sqrtf(SQ3(out4[0], out4[1], out4[2])) * 0.009999999776482582f;
        PlaneRec *ee = o->m8[bestEdge];
        V448.y = P->z - Q->z;
        V448.x = P->x - Q->x;
        if (ee->z == ee->x && ee->w == ee->y)
            ee = o->m8[bestEdge + 1];
        float zz = 0.0f;
        out7[0] = ee->z - ee->x;
        out7[1] = zz;
        out7[2] = ee->w - ee->y;
        out7[3] = 1.0f;
        float inv = 1.0f / __builtin_sqrtf(out7[0] * out7[0] + zz + out7[2] * out7[2]);
        out7[0] = out7[0] * inv;
        out7[2] = out7[2] * inv;
        out7[1] = out7[1] * inv;
        outA[3] = 1.0f;
        outA[0] = ee->x;
        outA[2] = ee->y;
        outA[1] = zz;
        outB[3] = 1.0f;
        outB[0] = ee->z;
        outB[1] = zz;
        outB[2] = ee->w;
    }
    return result;
}
#undef dA
#undef dB
#undef sA
#undef sB
#undef aA
#undef aB
#undef pA
#undef pB
#undef V448
#undef V464
#undef V480
