/* The view setup object file (retail 0x0ce068 to 0x0ce454): hands matrices and the viewport
   to the graphics library, and builds the side planes of the view frustum (as unit normals)
   for the camera code. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[16];
} __attribute__((aligned(16)));

extern "C" {
void f_116b04(int type, const Matrix *m);
void f_117f20(int x, int y, int width, int height);
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);
Vec4 *f_027f18(Vec4 *d, const Vec4 *a);
}

/* @implements 0x0ce068 us f_0ce068
   WHAT IT DOES: Loads a matrix (projection 0, view 1, ...) into the graphics engine. */
void f_0ce068(int type, const Matrix *m)
{
    f_116b04(type, m);
}

/* @implements 0x0ce084 us f_0ce084
   WHAT IT DOES: Sets the graphics engine's viewport. */
void f_0ce084(int x, int y, int width, int height)
{
    f_117f20(x, y, width, height);
}

/* @implements 0x0ce0a0 us f_0ce0a0
   WHAT IT DOES: Nothing (an emptied hook). */
void f_0ce0a0(void)
{
}

/* @implements 0x0ce0a8 us f_0ce0a8
   WHAT IT DOES: Nothing; called with each new projection matrix (an emptied hook). */
void f_0ce0a8(Matrix *m)
{
}

/* Sets the first three components of a vector. */
static inline void SetVec(Vec4 *p, float x, float y, float z)
{
    p->x = x;
    p->y = y;
    p->z = z;
}

/* Sets a plane normal and scales it to length 1. */
static inline void SetNormal(Vec4 *p, float x, float y, float z)
{
    p->x = x;
    p->y = y;
    p->z = z;
    f_027f18(p, p);
}

/* @implements 0x0ce0b0 us f_0ce0b0
   WHAT IT DOES: Builds two sets of four frustum side plane normals: the first from the
   horizontal and vertical extents at depth 1, the second from the screen half sizes divided by
   the focal distance. */
void f_0ce0b0(Vec4 *a, Vec4 *b, float x, float y, float d, float w, float h)
{
    SetNormal(&a[0], x, 0.0f, -y);
    SetNormal(&a[1], -x, 0.0f, -y);
    SetNormal(&a[2], 0.0f, x, -1.0f);
    SetNormal(&a[3], 0.0f, -x, -1.0f);
    float sw = -(w / d);
    float sh = -(h / d);
    SetNormal(&b[0], x, 0.0f, sw);
    SetNormal(&b[1], -x, 0.0f, sw);
    SetNormal(&b[2], 0.0f, x, sh);
    SetNormal(&b[3], 0.0f, -x, sh);
}

/* @implements 0x0ce21c us f_0ce21c
   WHAT IT DOES: Builds the four side plane normals of a view window (a screen rectangle given
   by its position and size) into a work array, copying each to the output; the far side's
   normals are flipped. */
void f_0ce21c(Vec4 *out, Vec4 *p, float a, float b, float c, float w, float x, float h, float y)
{
    float sx, sy;

    if (w == 0.0f)
        w = 1.0f;
    if (h == 0.0f)
        h = 1.0f;
    sx = 2.0f / w;
    sy = 2.0f / h;
    SetVec(&p[0], a, 0.0f, (-1.0f + sx * x) * b - 0.5f);
    f_027f18(&p[0], &p[0]);
    out[0] = p[0];
    SetVec(&p[1], a, 0.0f, (-1.0f + sx * (x + 1.0f)) * b + 0.5f);
    f_027f18(&p[1], &p[1]);
    f_027e6c(&p[1], &p[1], -1.0f);
    out[1] = p[1];
    SetVec(&p[2], 0.0f, -a, -1.0f + sy * y - 0.5f);
    f_027f18(&p[2], &p[2]);
    out[2] = p[2];
    SetVec(&p[3], 0.0f, -a, -1.0f + sy * (y + 1.0f) + 0.5f);
    f_027f18(&p[3], &p[3]);
    f_027e6c(&p[3], &p[3], -1.0f);
    out[3] = p[3];
}
