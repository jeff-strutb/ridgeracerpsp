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
void f_0b2f18(int a, int b, int c, int d, int e, int f, int g, int h, float x, float y, void *s, void *t);
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
   Remaining difference: the frame is now 112 bytes as in retail, but the prologue schedules the
   four loads after the stack adjustment and the struct temporaries are placed differently
   (about 20 of 28 words differ, from +0x10). */
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

    f_0b2f18(a, b, c, d, e, f, g, h, x, y, &p, &q);
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
void f_099b98(Angle *a);
void f_09b394(Angle a, float *x, float *y);
}

/* @draft 0x0b1a78 us f_0b1a78
   WHAT IT DOES: Turns both points by the negated heading of the first point (its angle about
   the origin, wrapped and applied as a rotation to each), then returns whether the second point
   lies at a negative x, or the first's x is less than the second's.
   Remaining difference: 8 of 44 words differ, from +0x0c: the float arguments are loaded from the first point before the struct copies, and retail stores the copies in the order y, y, x, x. */
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

/* A list of plane records: two halfword counts, then a word, then the pointer array. */
struct PlaneList {
    unsigned short m0;
    unsigned short m2;
    int m4;
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
