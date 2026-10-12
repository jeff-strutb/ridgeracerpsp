/* The polygon clipping object files (retail 0x029b58 to 0x02bbc0). Course geometry is sent to
   the graphics engine as triangle strips. Strips that cross the clip planes are cut here
   before they are written into the display list: each vertex is tested against four planes
   (the rows of a plane matrix set from the view each frame) and the strips are rebuilt from
   the parts inside. The object files also keep the camera position, a view direction and a
   scale used to push distant vertices along that direction. */

/* A plane: normal and distance. */
struct Plane {
    float x, y, z, w;
};

/* The four clip planes. */
struct PlaneSet {
    Plane p[4];
};

struct Vector4 {
    float x, y, z, w;
};

extern PlaneSet D_23fb00;
extern Vector4 D_23fb80;
extern Vector4 D_23fb90;
extern float D_23fba0;

PlaneSet *f_02b7e4(void);

/* A textured, coloured strip vertex: texture coordinates, colour, position. */
struct TexVertex {
    float u, v;
    unsigned char c[4];
    float x, y, z;
};

/* @draft 0x029b58 us f_029b58
   WHAT IT DOES: The vector unit version of the strip clipper, for textured, coloured
   vertices, working in two polygon buffers in the fast on-chip memory at 0x10000. Clips a
   triangle strip against the enabled clip planes (bits 0 to 3 of planes) and writes what is
   left as triangle fans. With strips set, the strip is taken two triangles at a time as a quad (one triangle
   when only one is left); otherwise one triangle at a time, every other one with its vertex
   order reversed to keep the winding. Each polygon is cut against each enabled plane in turn:
   vertices on the inner side are kept, and where an edge crosses the plane a new vertex is
   interpolated along the edge (texture coordinates, colour and position). A polygon with
   something left is written as vertices to out and as base, vertex address and fan commands
   to the display list; the ends of both outputs are returned through outEnd and dlEnd.
   Remaining difference: control flow and the vector code match; register allocation differs
   from the strip pointer's register (retail keeps the input in s1, set after the first test)
   and the distance loop's index givs onward. */
void f_029b58(unsigned int planes, TexVertex *out, const TexVertex *in, unsigned int *dl, int n,
              TexVertex **outEnd, unsigned int **dlEnd, int strips)
{
    TexVertex *buf[2];
    int cnt[2];
    float dist[12];
    float di;
    float dj;
    int k;

    buf[0] = (TexVertex *)0x10000;
    buf[1] = (TexVertex *)0x10180;
    for (k = 0; k < n - 2; ) {
        int cur;
        int p;

        cnt[1] = 0;
        cur = 0;
        if (n - k - 2 < 2 || !strips) {
            cnt[0] = 3;
            if (k & 1) {
                buf[0][0] = in[2];
                buf[0][1] = in[1];
                buf[0][2] = in[0];
            } else {
                buf[0][0] = in[0];
                buf[0][1] = in[1];
                buf[0][2] = in[2];
            }
            k++;
            in++;
        } else {
            cnt[0] = 4;
            k += 2;
            buf[0][0] = in[1];
            buf[0][1] = in[3];
            buf[0][2] = in[2];
            buf[0][3] = in[0];
            in += 2;
        }
        for (p = 0; p < 4; p++) {
            if (planes & (1 << p)) {
                Plane *pl = &f_02b7e4()->p[p];
                int i;
                int m;

                /* The signed distance of every vertex from the plane, two at a time. */
                for (i = cnt[cur] - 1; i >= 0; ) {
                    if (i < 2) {
                        __asm__ volatile(
                            "lv.q C000.q, 0(%0)\n"
                            "\tlv.s S010.s, 12(%1)\n\tlv.s S011.s, 16(%1)\n\tlv.s S012.s, 20(%1)\n"
                            "\tvone.s S013.s\n"
                            "\tvdot.q S100.s, C000.q, C010.q\n"
                            "\tsv.s S100.s, 0(%2)"
                            : : "r"(pl), "r"(&buf[cur][i]), "r"(&dist[i]) : "memory");
                        i--;
                    } else {
                        __asm__ volatile(
                            "lv.q C000.q, 0(%0)\n"
                            "\tlv.s S010.s, 12(%1)\n\tlv.s S011.s, 16(%1)\n\tlv.s S012.s, 20(%1)\n"
                            "\tvone.s S013.s\n"
                            "\tlv.s S020.s, -12(%1)\n\tlv.s S021.s, -8(%1)\n"
                            "\tvdot.q S100.s, C000.q, C010.q\n"
                            "\tlv.s S022.s, -4(%1)\n"
                            "\tvone.s S023.s\n"
                            "\tvdot.q S101.s, C000.q, C020.q\n"
                            "\tsv.s S100.s, 0(%2)\n"
                            "\tsv.s S101.s, -4(%2)"
                            : : "r"(pl), "r"(&buf[cur][i]), "r"(&dist[i]) : "memory");
                        i -= 2;
                    }
                }
                m = 0;
                for (i = 0; i < cnt[cur]; i++) {
                    int j = (i + 1) % cnt[cur];
                    TexVertex *a = &buf[cur][i];
                    TexVertex *b;

                    di = dist[i];
                    if (di >= 0.0f) {
                        buf[1 - cur][m] = *a;
                        m++;
                    }
                    dj = dist[j];
                    b = &buf[cur][j];
                    if (di * dj < 0.0f) {
                        /* t = |di| / max(|di| + |dj|, e); the new vertex is a + (b - a) t,
                           the colour converted to floats and back. */
                        __asm__ volatile(
                            "lv.s S200.s, %0\n"
                            "\tlv.s S201.s, %1\n"
                            "\tlbu $8, 8(%2)\n\tlbu $9, 9(%2)\n"
                            "\tvabs.p C200.p, C200.p\n"
                            "\tvcst.s S203.s, VFPU_E\n"
                            "\tlbu $10, 10(%2)\n"
                            "\tvadd.s S202.s, S200.s, S201.s\n"
                            "\tlbu $11, 11(%2)\n"
                            "\tmtv $8, S010.s\n"
                            "\tvmax.s S202.s, S202.s, S203.s\n"
                            "\tmtv $9, S011.s\n\tmtv $10, S012.s\n"
                            "\tvdiv.s S200.s, S200.s, S202.s\n"
                            "\tmtv $11, S013.s\n"
                            "\tlv.s S000.s, 0(%2)\n\tlv.s S001.s, 4(%2)\n"
                            "\tlv.s S020.s, 12(%2)\n\tlv.s S021.s, 16(%2)\n\tlv.s S022.s, 20(%2)\n"
                            "\tvi2f.q C010.q, C010.q, 1/2^0\n"
                            "\tlbu $8, 8(%3)\n\tlbu $9, 9(%3)\n\tlbu $10, 10(%3)\n\tlbu $11, 11(%3)\n"
                            "\tmtv $8, S110.s\n\tmtv $9, S111.s\n\tmtv $10, S112.s\n\tmtv $11, S113.s\n"
                            "\tlv.s S100.s, 0(%3)\n\tlv.s S101.s, 4(%3)\n"
                            "\tlv.s S120.s, 12(%3)\n\tlv.s S121.s, 16(%3)\n\tlv.s S122.s, 20(%3)\n"
                            "\tvi2f.q C110.q, C110.q, 1/2^0\n"
                            "\tvone.s S202.s\n"
                            "\tvsub.s S201.s, S202.s, S200.s\n"
                            "\tvscl.p C300.p, C000.p, S201.s\n"
                            "\tvscl.q C310.q, C010.q, S201.s\n"
                            "\tvscl.t C320.t, C020.t, S201.s\n"
                            "\tvscl.p C000.p, C100.p, S200.s\n"
                            "\tvscl.q C010.q, C110.q, S200.s\n"
                            "\tvscl.t C020.t, C120.t, S200.s\n"
                            "\tvadd.p C000.p, C300.p, C000.p\n"
                            "\tvadd.q C010.q, C310.q, C010.q\n"
                            "\tvadd.t C020.t, C320.t, C020.t\n"
                            "\tsv.s S000.s, 0(%4)\n"
                            "\tvf2in.q C010.q, C010.q, 1/2^23\n"
                            "\tsv.s S001.s, 4(%4)\n"
                            "\tsv.s S020.s, 12(%4)\n"
                            "\tvi2uc.q S120.s, C010.q\n"
                            "\tsv.s S021.s, 16(%4)\n"
                            "\tsv.s S022.s, 20(%4)\n"
                            "\tsv.s S120.s, 8(%4)"
                            : : "m"(di), "m"(dj), "r"(a), "r"(b), "r"(&buf[1 - cur][m])
                            : "$8", "$9", "$10", "$11", "memory");
                        m++;
                    }
                }
                if (m == 0)
                    goto next;
                cur = 1 - cur;
                cnt[cur] = m;
                cnt[1 - cur] = 0;
            }
        }
        {
            int c = cnt[cur];
            int i;

            *dl++ = ((((int)out >> 24) & 0xf) << 16) | 0x10000000;
            *dl++ = ((unsigned int)out & 0xffffff) | 0x01000000;
            *dl++ = c | 0x04050000;
            for (i = 0; i < c; i++)
                *out++ = buf[cur][i];
        }
    next:;
    }
    *outEnd = out;
    *dlEnd = dl;
}

/* A coloured, lit strip vertex: colour, three normal shorts, position. */
struct LitVertex {
    unsigned char c[4];
    unsigned short n[3];
    float x, y, z;
};

/* A textured, coloured, lit strip vertex. */
struct TexLitVertex {
    float u, v;
    unsigned char c[4];
    unsigned short n[3];
    float x, y, z;
};

/* A textured, lit strip vertex. */
struct TexNormVertex {
    float u, v;
    unsigned short n[3];
    float x, y, z;
};

/* @draft 0x02a22c us f_02a22c
   WHAT IT DOES: Clips a triangle strip of coloured, lit vertices against the enabled clip planes (bits 0 to 3 of
   planes) and writes what is left as triangle fans. The strip is taken two triangles at a time
   as a quad (one triangle when only one is left). Each polygon is cut against each enabled
   plane in turn: vertices on the inner side are kept, and where an edge crosses the plane a
   new vertex is interpolated along the edge (position and colour; the normal is taken from the edge's
   first vertex). A polygon with something left is written as vertices to out and as base,
   vertex address and fan commands to the display list; the ends of both outputs are returned
   through outEnd and dlEnd.
   Remaining difference: retail spills planes and keeps the buffer index unscaled (s7), and
   computes the interpolated colour before the position and normal stores of the same block. */
void f_02a22c(unsigned int planes, LitVertex *out, const LitVertex *in, unsigned int *dl, int n,
              LitVertex **outEnd, unsigned int **dlEnd)
{
    LitVertex buf[2][10];
    int cnt[2];
    float dist[12];
    int k;

    for (k = 0; k < n - 2; ) {
        int cur;
        int p;

        cnt[1] = 0;
        if (n - k - 2 < 2) {
            buf[0][0] = in[0];
            buf[0][1] = in[1];
            buf[0][2] = in[2];
            cnt[0] = 3;
            k++;
            in++;
        } else {
            buf[0][0] = in[1];
            buf[0][1] = in[3];
            buf[0][2] = in[2];
            buf[0][3] = in[0];
            cnt[0] = 4;
            k += 2;
            in += 2;
        }
        cur = 0;
        for (p = 0; p < 4; p++) {
            if (planes & (1 << p)) {
                Plane *pl = &f_02b7e4()->p[p];
                int i;
                int m;

                for (i = 0; i < cnt[cur]; i++)
                    dist[i] = buf[cur][i].x * pl->x + buf[cur][i].y * pl->y
                              + buf[cur][i].z * pl->z + pl->w;
                m = 0;
                for (i = 0; i < cnt[cur]; i++) {
                    int j = (i + 1) % cnt[cur];
                    float di = dist[i];
                    LitVertex *a = &buf[cur][i];
                    LitVertex *b = &buf[cur][j];
                    float dj;

                    if (di >= 0.0f) {
                        buf[1 - cur][m] = *a;
                        m++;
                    }
                    dj = dist[j];
                    if (di * dj < 0.0f) {
                        LitVertex *v = &buf[1 - cur][m];
                        float ai = di;
                        float aj = dj;
                        float s;
                        float t = 0.0f;

                        if (di < 0.0f)
                            ai = -di;
                        if (dj < 0.0f)
                            aj = -dj;
                        s = ai + aj;
                        if (s != 0.0f)
                            t = ai / s;
                        v->x = a->x * (1.0f - t) + t * b->x;
                        v->y = a->y * (1.0f - t) + t * b->y;
                        v->z = a->z * (1.0f - t) + t * b->z;
                        v->n[0] = a->n[0];
                        v->n[1] = a->n[1];
                        v->n[2] = a->n[2];
                        v->c[0] = (unsigned char)(a->c[0] * (1.0f - t) + t * b->c[0]);
                        v->c[1] = (unsigned char)(a->c[1] * (1.0f - t) + t * b->c[1]);
                        v->c[2] = (unsigned char)(a->c[2] * (1.0f - t) + t * b->c[2]);
                        v->c[3] = (unsigned char)(a->c[3] * (1.0f - t) + t * b->c[3]);
                        m++;
                    }
                }
                if (m == 0)
                    goto next;
                cur = 1 - cur;
                cnt[cur] = m;
                cnt[1 - cur] = 0;
            }
        }
        {
            int c = cnt[cur];
            int i;

            *dl++ = ((((int)out >> 24) & 0xf) << 16) | 0x10000000;
            *dl++ = ((unsigned int)out & 0xffffff) | 0x01000000;
            *dl++ = c | 0x04050000;
            for (i = 0; i < c; i++)
                *out++ = buf[cur][i];
        }
    next:;
    }
    *outEnd = out;
    *dlEnd = dl;
}

/* @draft 0x02a910 us f_02a910
   WHAT IT DOES: Clips a triangle strip of textured, coloured, lit vertices against the enabled clip planes (bits 0 to 3 of
   planes) and writes what is left as triangle fans. The strip is taken two triangles at a time
   as a quad (one triangle when only one is left). Each polygon is cut against each enabled
   plane in turn: vertices on the inner side are kept, and where an edge crosses the plane a
   new vertex is interpolated along the edge (position, colour and texture coordinates; the normal is taken from the edge's
   first vertex). A polygon with something left is written as vertices to out and as base,
   vertex address and fan commands to the display list; the ends of both outputs are returned
   through outEnd and dlEnd.
   Remaining difference: retail spills planes and keeps the buffer index unscaled (s7), and
   computes the interpolated colour before the position and normal stores of the same block. */
void f_02a910(unsigned int planes, TexLitVertex *out, const TexLitVertex *in, unsigned int *dl,
              int n, TexLitVertex **outEnd, unsigned int **dlEnd)
{
    TexLitVertex buf[2][10];
    int cnt[2];
    float dist[12];
    int k;

    for (k = 0; k < n - 2; ) {
        int cur;
        int p;

        cnt[1] = 0;
        if (n - k - 2 < 2) {
            buf[0][0] = in[0];
            buf[0][1] = in[1];
            buf[0][2] = in[2];
            cnt[0] = 3;
            k++;
            in++;
        } else {
            buf[0][0] = in[1];
            buf[0][1] = in[3];
            buf[0][2] = in[2];
            buf[0][3] = in[0];
            cnt[0] = 4;
            k += 2;
            in += 2;
        }
        cur = 0;
        for (p = 0; p < 4; p++) {
            if (planes & (1 << p)) {
                Plane *pl = &f_02b7e4()->p[p];
                int i;
                int m;

                for (i = 0; i < cnt[cur]; i++)
                    dist[i] = buf[cur][i].x * pl->x + buf[cur][i].y * pl->y
                              + buf[cur][i].z * pl->z + pl->w;
                m = 0;
                for (i = 0; i < cnt[cur]; i++) {
                    int j = (i + 1) % cnt[cur];
                    float di = dist[i];
                    TexLitVertex *a = &buf[cur][i];
                    TexLitVertex *b = &buf[cur][j];
                    float dj;

                    if (di >= 0.0f) {
                        buf[1 - cur][m] = *a;
                        m++;
                    }
                    dj = dist[j];
                    if (di * dj < 0.0f) {
                        TexLitVertex *v = &buf[1 - cur][m];
                        float ai = di;
                        float aj = dj;
                        float s;
                        float t = 0.0f;

                        if (di < 0.0f)
                            ai = -di;
                        if (dj < 0.0f)
                            aj = -dj;
                        s = ai + aj;
                        if (s != 0.0f)
                            t = ai / s;
                        v->x = a->x * (1.0f - t) + t * b->x;
                        v->y = a->y * (1.0f - t) + t * b->y;
                        v->z = a->z * (1.0f - t) + t * b->z;
                        v->n[0] = a->n[0];
                        v->n[1] = a->n[1];
                        v->n[2] = a->n[2];
                        v->c[0] = (unsigned char)(a->c[0] * (1.0f - t) + t * b->c[0]);
                        v->c[1] = (unsigned char)(a->c[1] * (1.0f - t) + t * b->c[1]);
                        v->c[2] = (unsigned char)(a->c[2] * (1.0f - t) + t * b->c[2]);
                        v->c[3] = (unsigned char)(a->c[3] * (1.0f - t) + t * b->c[3]);
                        v->u = a->u * (1.0f - t) + t * b->u;
                        v->v = a->v * (1.0f - t) + t * b->v;
                        m++;
                    }
                }
                if (m == 0)
                    goto next;
                cur = 1 - cur;
                cnt[cur] = m;
                cnt[1 - cur] = 0;
            }
        }
        {
            int c = cnt[cur];
            int i;

            *dl++ = ((((int)out >> 24) & 0xf) << 16) | 0x10000000;
            *dl++ = ((unsigned int)out & 0xffffff) | 0x01000000;
            *dl++ = c | 0x04050000;
            for (i = 0; i < c; i++)
                *out++ = buf[cur][i];
        }
    next:;
    }
    *outEnd = out;
    *dlEnd = dl;
}

/* @draft 0x02b09c us f_02b09c
   WHAT IT DOES: Clips a triangle strip of textured, lit vertices against the enabled clip planes (bits 0 to 3 of
   planes) and writes what is left as triangle fans. The strip is taken two triangles at a time
   as a quad (one triangle when only one is left). Each polygon is cut against each enabled
   plane in turn: vertices on the inner side are kept, and where an edge crosses the plane a
   new vertex is interpolated along the edge (position and texture coordinates; the normal is taken from the edge's
   first vertex). A polygon with something left is written as vertices to out and as base,
   vertex address and fan commands to the display list; the ends of both outputs are returned
   through outEnd and dlEnd.
   Remaining difference: retail spills planes and keeps the buffer index unscaled (s7); the
   rest is register allocation and scheduling that follows from it. */
void f_02b09c(unsigned int planes, TexNormVertex *out, const TexNormVertex *in,
              unsigned int *dl, int n, TexNormVertex **outEnd, unsigned int **dlEnd)
{
    TexNormVertex buf[2][10];
    int cnt[2];
    float dist[12];
    int k;

    for (k = 0; k < n - 2; ) {
        int cur;
        int p;

        cnt[1] = 0;
        if (n - k - 2 < 2) {
            buf[0][0] = in[0];
            buf[0][1] = in[1];
            buf[0][2] = in[2];
            cnt[0] = 3;
            k++;
            in++;
        } else {
            buf[0][0] = in[1];
            buf[0][1] = in[3];
            buf[0][2] = in[2];
            buf[0][3] = in[0];
            cnt[0] = 4;
            k += 2;
            in += 2;
        }
        cur = 0;
        for (p = 0; p < 4; p++) {
            if (planes & (1 << p)) {
                Plane *pl = &f_02b7e4()->p[p];
                int i;
                int m;

                for (i = 0; i < cnt[cur]; i++)
                    dist[i] = buf[cur][i].x * pl->x + buf[cur][i].y * pl->y
                              + buf[cur][i].z * pl->z + pl->w;
                m = 0;
                for (i = 0; i < cnt[cur]; i++) {
                    int j = (i + 1) % cnt[cur];
                    float di = dist[i];
                    TexNormVertex *a = &buf[cur][i];
                    TexNormVertex *b = &buf[cur][j];
                    float dj;

                    if (di >= 0.0f) {
                        buf[1 - cur][m] = *a;
                        m++;
                    }
                    dj = dist[j];
                    if (di * dj < 0.0f) {
                        TexNormVertex *v = &buf[1 - cur][m];
                        float ai = di;
                        float aj = dj;
                        float s;
                        float t = 0.0f;

                        if (di < 0.0f)
                            ai = -di;
                        if (dj < 0.0f)
                            aj = -dj;
                        s = ai + aj;
                        if (s != 0.0f)
                            t = ai / s;
                        v->x = a->x * (1.0f - t) + t * b->x;
                        v->y = a->y * (1.0f - t) + t * b->y;
                        v->z = a->z * (1.0f - t) + t * b->z;
                        v->n[0] = a->n[0];
                        v->n[1] = a->n[1];
                        v->n[2] = a->n[2];
                        v->u = a->u * (1.0f - t) + t * b->u;
                        v->v = a->v * (1.0f - t) + t * b->v;
                        m++;
                    }
                }
                if (m == 0)
                    goto next;
                cur = 1 - cur;
                cnt[cur] = m;
                cnt[1 - cur] = 0;
            }
        }
        {
            int c = cnt[cur];
            int i;

            *dl++ = ((((int)out >> 24) & 0xf) << 16) | 0x10000000;
            *dl++ = ((unsigned int)out & 0xffffff) | 0x01000000;
            *dl++ = c | 0x04050000;
            for (i = 0; i < c; i++)
                *out++ = buf[cur][i];
        }
    next:;
    }
    *outEnd = out;
    *dlEnd = dl;
}

/* @implements 0x02b67c us f_02b67c
   WHAT IT DOES: Sets the four clip planes from the given plane matrix. */
void f_02b67c(const PlaneSet *m)
{
    D_23fb00.p[0] = m->p[0];
    D_23fb00.p[1] = m->p[1];
    D_23fb00.p[2] = m->p[2];
    D_23fb00.p[3] = m->p[3];
}

/* @implements 0x02b714 us f_02b714
   WHAT IT DOES: Sets the four clip planes from the given plane matrix, then moves each plane
   by the given distance along its own second axis (the fourth component becomes minus the
   second times the distance). */
void f_02b714(const PlaneSet *m, float d)
{
    D_23fb00.p[0] = m->p[0];
    D_23fb00.p[1] = m->p[1];
    D_23fb00.p[2] = m->p[2];
    D_23fb00.p[3] = m->p[3];
    D_23fb00.p[0].w = -D_23fb00.p[0].y * d;
    D_23fb00.p[1].w = -D_23fb00.p[1].y * d;
    D_23fb00.p[2].w = -D_23fb00.p[2].y * d;
    D_23fb00.p[3].w = -D_23fb00.p[3].y * d;
}

/* @implements 0x02b7e4 us f_02b7e4
   WHAT IT DOES: Returns the four clip planes. */
PlaneSet *f_02b7e4(void)
{
    return &D_23fb00;
}

/* @implements 0x02b7f0 us f_02b7f0
   WHAT IT DOES: Sets the camera position. */
void f_02b7f0(const Vector4 *v)
{
    D_23fb80 = *v;
}

/* @implements 0x02b81c us f_02b81c
   WHAT IT DOES: Sets the direction distant vertices are pushed along. */
void f_02b81c(const Vector4 *v)
{
    D_23fb90 = *v;
}

/* @implements 0x02b848 us f_02b848
   WHAT IT DOES: Sets how far distant vertices are pushed per unit of distance. */
void f_02b848(float s)
{
    D_23fba0 = s;
}

extern "C" {
void f_028b3c(void *save);
void f_028b74(const void *save);
}
void f_027e6c(Vector4 *out, const Vector4 *in, float t);

/* A strip vertex: texture coordinates and colour, then the position. */
struct StripVertex {
    int m0[3];
    float pos[3];
};

/* @draft 0x02b854 us f_02b854
   WHAT IT DOES: Copies a display list of triangle strips into a new list and a new vertex
   buffer, pushing every vertex away from the camera along the push direction by its distance
   from the camera times the push scale. The camera position used is first adjusted for the
   given mode. The source list is a header of four words, then per strip its vertex address
   (base and offset commands) and its primitive command, up to a return command. For each strip
   the new list gets base, vertex address and triangle strip commands pointing at the moved
   vertices. The ends of both outputs are returned through the last two arguments. The VFPU
   matrices the routine uses are saved and restored around it.
   Remaining difference (23 words, all register choice): the strip vertex count is allocated to
   a2 and the vertex offset word to a1 (retail the reverse), the hoisted command constants take
   t3 to t6 in another order, and the 0xff mask is scheduled after the base mask. */
void f_02b854(int mode, StripVertex *out, unsigned int *dl, const unsigned int *cmds,
              StripVertex **outEnd, unsigned int **dlEnd)
{
    char save[192];
    Vector4 cam;
    unsigned int c;

    f_028b3c(save);
    *dl++ = *cmds++;
    *dl++ = *cmds++;
    *dl++ = *cmds++;
    *dl++ = *cmds++;
    f_027e6c(&cam, &D_23fb80, (float)(1 - mode));
    __asm__ volatile(
        "lv.q C730.q, %0\n"
        "\tlv.s S720.s, %1\n"
        "\tlv.q C710.q, %2"
        : : "m"(cam), "m"(D_23fba0), "m"(D_23fb90));
    do {
        c = *cmds++;
        unsigned int lo = *cmds++;
        StripVertex *src = (StripVertex *)(((c & 0xff0000) << 8) | (lo & 0xffffff));
        unsigned int prim = *cmds++;
        int n;

        *dl++ = ((((int)out >> 24) & 0xf) << 16) | 0x10000000;
        *dl++ = ((unsigned int)out & 0xffffff) | 0x01000000;
        n = prim & 0xff;
        *dl++ = n | 0x04040000;
        do {
            if (n > 3) {
                __asm__ volatile(
                    "lv.s S000.s, 12(%0)\n\tlv.s S001.s, 16(%0)\n\tlv.s S002.s, 20(%0)\n"
                    "\tlv.s S200.s, 36(%0)\n\tlv.s S201.s, 40(%0)\n\tlv.s S202.s, 44(%0)\n"
                    "\tlv.s S400.s, 60(%0)\n\tlv.s S401.s, 64(%0)\n\tlv.s S402.s, 68(%0)\n"
                    "\tvsub.t C010.t, C000.t, C730.t\n"
                    "\tvsub.t C210.t, C200.t, C730.t\n"
                    "\tvsub.t C410.t, C400.t, C730.t\n"
                    "\tlw $8, 0(%0)\n\tlw $9, 4(%0)\n"
                    "\tvdot.t S020.s, C010.t, C010.t\n"
                    "\tlw $10, 8(%0)\n"
                    "\tvdot.t S220.s, C210.t, C210.t\n"
                    "\tvdot.t S420.s, C410.t, C410.t\n"
                    "\tsw $8, 0(%1)\n\tsw $9, 4(%1)\n"
                    "\tvsqrt.s S020.s, S020.s\n"
                    "\tsw $10, 8(%1)\n"
                    "\tvsqrt.s S220.s, S220.s\n"
                    "\tvsqrt.s S420.s, S420.s\n"
                    "\tlw $8, 24(%0)\n\tlw $9, 28(%0)\n\tlw $10, 32(%0)\n"
                    "\tvmul.s S020.s, S020.s, S720.s\n"
                    "\tvmul.s S220.s, S220.s, S720.s\n"
                    "\tvmul.s S420.s, S420.s, S720.s\n"
                    "\tsw $8, 24(%1)\n\tsw $9, 28(%1)\n\tsw $10, 32(%1)\n"
                    "\tvscl.t C100.t, C710.t, S020.s\n"
                    "\tvscl.t C300.t, C710.t, S220.s\n"
                    "\tvscl.t C500.t, C710.t, S420.s\n"
                    "\tlw $8, 48(%0)\n\tlw $9, 52(%0)\n\tlw $10, 56(%0)\n"
                    "\tvadd.t C100.t, C000.t, C100.t\n"
                    "\tvadd.t C300.t, C200.t, C300.t\n"
                    "\tvadd.t C500.t, C400.t, C500.t\n"
                    "\tsw $8, 48(%1)\n\tsw $9, 52(%1)\n\tsw $10, 56(%1)\n"
                    "\tsv.s S100.s, 12(%1)\n\tsv.s S101.s, 16(%1)\n\tsv.s S102.s, 20(%1)\n"
                    "\tsv.s S300.s, 36(%1)\n\tsv.s S301.s, 40(%1)\n\tsv.s S302.s, 44(%1)\n"
                    "\tsv.s S500.s, 60(%1)\n\tsv.s S501.s, 64(%1)\n\tsv.s S502.s, 68(%1)"
                    : : "r"(src), "r"(out) : "$8", "$9", "$10", "memory");
                n -= 3;
                out += 3;
                src += 3;
            } else if (n > 2) {
                __asm__ volatile(
                    "lv.s S000.s, 12(%0)\n\tlv.s S001.s, 16(%0)\n\tlv.s S002.s, 20(%0)\n"
                    "\tlv.s S200.s, 36(%0)\n\tlv.s S201.s, 40(%0)\n\tlv.s S202.s, 44(%0)\n"
                    "\tvsub.t C010.t, C000.t, C730.t\n"
                    "\tvsub.t C210.t, C200.t, C730.t\n"
                    "\tlw $8, 0(%0)\n\tlw $9, 4(%0)\n\tlw $10, 8(%0)\n"
                    "\tvdot.t S020.s, C010.t, C010.t\n"
                    "\tvdot.t S220.s, C210.t, C210.t\n"
                    "\tsw $8, 0(%1)\n\tsw $9, 4(%1)\n\tsw $10, 8(%1)\n"
                    "\tvsqrt.s S020.s, S020.s\n"
                    "\tvsqrt.s S220.s, S220.s\n"
                    "\tlw $8, 24(%0)\n\tlw $9, 28(%0)\n\tlw $10, 32(%0)\n"
                    "\tvmul.s S020.s, S020.s, S720.s\n"
                    "\tvmul.s S220.s, S220.s, S720.s\n"
                    "\tsw $8, 24(%1)\n\tsw $9, 28(%1)\n\tsw $10, 32(%1)\n"
                    "\tvscl.t C100.t, C710.t, S020.s\n"
                    "\tvscl.t C300.t, C710.t, S220.s\n"
                    "\tvadd.t C100.t, C000.t, C100.t\n"
                    "\tvadd.t C300.t, C200.t, C300.t\n"
                    "\tsv.s S100.s, 12(%1)\n\tsv.s S101.s, 16(%1)\n\tsv.s S102.s, 20(%1)\n"
                    "\tsv.s S300.s, 36(%1)\n\tsv.s S301.s, 40(%1)\n\tsv.s S302.s, 44(%1)"
                    : : "r"(src), "r"(out) : "$8", "$9", "$10", "memory");
                n -= 2;
                out += 2;
                src += 2;
            } else {
                __asm__ volatile(
                    "lv.s S000.s, 12(%0)\n\tlv.s S001.s, 16(%0)\n\tlv.s S002.s, 20(%0)\n"
                    "\tvsub.t C010.t, C000.t, C730.t\n"
                    "\tlw $8, 0(%0)\n\tlw $9, 4(%0)\n\tlw $10, 8(%0)\n"
                    "\tvdot.t S020.s, C010.t, C010.t\n"
                    "\tvsqrt.s S020.s, S020.s\n"
                    "\tsw $8, 0(%1)\n\tsw $9, 4(%1)\n\tsw $10, 8(%1)\n"
                    "\tvmul.s S020.s, S020.s, S720.s\n"
                    "\tvscl.t C100.t, C710.t, S020.s\n"
                    "\tvadd.t C100.t, C000.t, C100.t\n"
                    "\tsv.s S100.s, 12(%1)\n\tsv.s S101.s, 16(%1)\n\tsv.s S102.s, 20(%1)"
                    : : "r"(src), "r"(out) : "$8", "$9", "$10", "memory");
                n--;
                out++;
                src++;
            }
        } while (n != 0);
    } while ((*cmds >> 24) != 11);
    *outEnd = out;
    *dlEnd = dl;
    f_028b74(save);
}
