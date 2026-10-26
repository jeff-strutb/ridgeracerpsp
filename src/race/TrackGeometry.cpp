/* Track and car geometry helpers (retail 0x0b1270 to 0x0b6754, an object file with unwind
   information). Two-dimensional points, projections onto a direction, cross products and the
   signed side tests used by the course code. Operations write their result through a pointer
   argument or return it by value, as the retail code does. */

struct Vec2 {
    float x, y;
};

/* A plane kept as a Vec4: normal in x and z (y is zero), and the constant in w. */
struct Plane {
    float x, y, z, w;
};

/* A car or course object: the value at offset 4 is its state word. */
struct StateObj {
    int m0;
    int m4;
};

extern "C" {
int f_0b2120(int a, int b, int c, float *out);
extern const float D_1ac7e0;
void f_0b2f18(int a, int b, int c, int d, void *x, void *y);
void f_0b6710(int a, int b, int c, int d, int e, int f, int g, void *h);
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

/* @draft 0x0b1b28 us f_0b1b28
   WHAT IT DOES: Returns the z component of the cross product of the vectors from the first
   point to the second and to the third point.
   Remaining difference: retail is 128 bytes: it stores the differences to a 64-byte frame and
   reloads them in an interleaved order; this draft is 56 bytes. */
float f_0b1b28(const Vec2 *a, const Vec2 *b, const Vec2 *c)
{
    float dx1 = b->x - a->x;
    float dy1 = b->y - a->y;
    float dx2 = c->x - a->x;
    float dy2 = c->y - a->y;
    return dx1 * dy2 - dy1 * dx2;
}

/* @draft 0x0b1ba8 us f_0b1ba8
   WHAT IT DOES: Stores a value into the object's state word at offset 4, adding 112 when the
   flag is clear.
   Remaining difference: word 0 (xori of the flag) differs; the flag is taken as unsigned char
   with !(flag & 1), which matches the size. */
void f_0b1ba8(StateObj *o, int v, unsigned char flag)
{
    if (!(flag & 1))
        v += 112;
    o->m4 = v;
}

/* @draft 0x0b20d8 us f_0b20d8
   WHAT IT DOES: Computes a plane from the first three arguments through the routine at
   0x0b2120 and stores it at the fourth argument: normal x, zero, normal z, and a constant of 1.0.
   Remaining difference: the two stores at offsets 12 and 8 come in the other order in retail
   (word 0x18 differs). */
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

/* @draft 0x0b6710 us f_0b6710
   WHAT IT DOES: Calls the routine at 0x0b2f18 with two local 8-byte buffers as its last two
   arguments.
   Remaining difference: retail's frame is 64 bytes with the return address at 48 and the
   buffers at 16 and 32; this draft is 32 bytes. */
void f_0b6710(int a, int b, int c, int d, int e, int f, int g, void *h)
{
    float x[4], y[4];

    f_0b2f18(a, b, c, d, x, y);
}

/* @implements 0x0b6738 us f_0b6738
   WHAT IT DOES: Calls the routine at 0x0b6710, passing its own arguments on and a 16-byte local
   buffer as the eighth. */
void f_0b6738(int a, int b, int c, int d, int e, int f, int g, void *h)
{
    float buf[4];

    f_0b6710(a, b, c, d, e, f, g, buf);
}
