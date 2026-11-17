/* The ground polygon set queries (retail 0x0af678 to 0x0b1270): one PolySet per collision
   surface (the road and the run-off area, see CourseAreas.cpp). A set holds a bounding box in
   x and z (+0..+24), an origin and a cell size (+32..+40), a grid of cells (+64) and per cell
   lists of triangles (+80 and +88). The set init (0x0af678) loads the header; the lookups
   (0x0af788 to 0x0b0500) walk the cells that a point's ray crosses, test the triangles of each
   cell (0x0b0910) and return the id of the triangle under the point, optionally with its height.
   0x0b07d4 and 0x0afebc work on one cell record; 0x0b0ae0 gives the height of a triangle at the
   point; 0x0b0d98 gives the normal of a triangle or quad cell; 0x0b1084 is the segment and quad
   intersection used by 0x0b0d98 and 0x0b0ae0. */

typedef struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16))) Vec4;

struct PolySet {
    char m[96];
};

#define PF(T, p, off) (*(T *)((char *)(p) + (off)))

/* One triangle record of a set: 24 bytes. Vertex indices i0, i1, i2 and next (0xffff for a
   triangle, else the fourth vertex of a quad), then the box of the triangle in x and z. */
struct Cell {
    unsigned short i0, i1, i2, next;
    float minx, minz, maxx, maxz;
};

/* One record of the grid table (+80): two counts, the offset of a block of 16 halfwords in the
   block table (+88, 32 bytes per block) and the base id of the block's triangles. */
struct Rec {
    signed char n0;
    signed char n1;
    unsigned short idx;
    unsigned short base;
};

extern "C" {
Vec4 *f_0a5e6c(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_0a5e88(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_0a5f74(Vec4 *d, const Vec4 *a, const Vec4 *b);
float f_0a5f54(const Vec4 *a, const Vec4 *b);
Vec4 *f_0a65e4(Vec4 *d, const Vec4 *a);
float f_0a65c4(const Vec4 *a);
int f_0b0910(PolySet *p, const Vec4 *v, const unsigned short *id);
float f_0b0ae0(PolySet *p, const Vec4 *v, const Cell *c);
void f_0b1084(const void *a0, const Vec4 *a1, const Vec4 *a2, Vec4 *a3);
}

/* @draft 0x0b1084 us f_0b1084
   WHAT IT DOES: Intersects the line through the point a1 along the edge from a2[0] to a2[1]
   (or, when that edge is nearly parallel to the edge a2[2] to a2[3], along the line through a
   point of that edge) with the edges a2[1] to a2[2] and a2[3] to a2[0]; writes the two crossings
   to a3[0] and a3[1]. Returns with a3 untouched when one of the two lines is parallel.
   Remaining difference: size 420 vs 492; 122/123 words differ from +0x0 (the six-load prologue and the float order of the cross terms are scheduled differently). */
void f_0b1084(const void *a0, const Vec4 *a1, const Vec4 *a2, Vec4 *a3)
{
    float ex, nz, ax, az, dn, adn, tn, yx, yz, dl, dk, t2;

    ex = a2[1].x - a2[0].x;
    nz = a2[0].z - a2[1].z;
    dn = nz * (a2[3].x - a2[2].x) + ex * (a2[3].z - a2[2].z);
    adn = dn < 0.0f ? -dn : dn;
    if (adn < 100.0f) {
        ax = a1->x;
        az = a1->z;
    } else {
        tn = (nz * (a2[1].x - a2[2].x) + ex * (a2[1].z - a2[2].z)) / dn;
        yx = a2[2].x + tn * (a2[3].x - a2[2].x);
        yz = a2[2].z + tn * (a2[3].z - a2[2].z);
        ex = yx - a1->x;
        nz = a1->z - yz;
        ax = yx;
        az = yz;
    }
    dl = nz * (a2[1].x - a2[2].x) + ex * (a2[1].z - a2[2].z);
    if (dl == 0.0f)
        return;
    tn = (ex * (az - a2[2].z) + nz * (ax - a2[2].x)) / dl;
    a3[0].x = a2[2].x + tn * (a2[1].x - a2[2].x);
    a3[0].y = a2[2].y + tn * (a2[1].y - a2[2].y);
    a3[0].z = a2[2].z + tn * (a2[1].z - a2[2].z);
    dk = nz * (a2[0].x - a2[3].x) + ex * (a2[0].z - a2[3].z);
    if (dk == 0.0f)
        return;
    t2 = (ex * (az - a2[3].z) + nz * (ax - a2[3].x)) / dk;
    a3[1].x = a2[3].x + t2 * (a2[0].x - a2[3].x);
    a3[1].y = a2[3].y + t2 * (a2[0].y - a2[3].y);
    a3[1].z = a2[3].z + t2 * (a2[0].z - a2[3].z);
}

/* @draft 0x0b0d98 us f_0b0d98
   WHAT IT DOES: Returns the unit normal of the cell with the id (through id) of the set: for a
   quad cell, the cross product of the two crossing segments that f_0b1084 finds from the point
   v; for a triangle, the cross product of its two edges, normalised.
   Remaining difference: size 672 vs 748; 183/187 words differ from +0x4 (the locals sit at other stack offsets, and the calls to f_0b1084 and the cross product are scheduled differently). */
Vec4 f_0b0d98(PolySet *p, const Vec4 *v, unsigned short *id)
{
    Vec4 tri[3];
    Vec4 dir1;
    Vec4 d2;
    Vec4 n;
    Vec4 q[5];
    Vec4 o1[2];
    Vec4 o2[2];
    Vec4 r;
    const Cell *c = (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)*id);
    const float *vt = PF(const float *, p, 72);
    unsigned short i0 = c->i0, i1 = c->i1, i2 = c->i2, i3 = c->next;
    int k;

    if (i3 != 0xffff) {
        for (k = 0; k < 3; k++) {
            ((float *)&q[0])[k] = vt[3 * i0 + k];
            ((float *)&q[1])[k] = vt[3 * i1 + k];
            ((float *)&q[2])[k] = vt[3 * i2 + k];
            ((float *)&q[3])[k] = vt[3 * i3 + k];
            ((float *)&q[4])[k] = vt[3 * i0 + k];
        }
        f_0b1084(p, v, &q[0], &o1[0]);
        f_0b1084(p, v, &q[1], &o2[0]);
        f_0a5e88(&d2, &o2[1], &o2[0]);
        dir1.x = o1[1].x - o1[0].x;
        dir1.y = o1[1].y - o1[0].y;
        dir1.z = o1[1].z - o1[0].z;
        dir1.w = 1.0f;
        f_0a5f74(&n, &d2, &dir1);
        f_0a65e4(&r, &n);
        return r;
    } else {
        tri[0].x = vt[3 * i0 + 0];
        tri[0].y = vt[3 * i0 + 1];
        tri[0].z = vt[3 * i0 + 2];
        tri[0].w = 1.0f;
        tri[1].x = vt[3 * i1 + 0];
        tri[1].y = vt[3 * i1 + 1];
        tri[1].z = vt[3 * i1 + 2];
        tri[1].w = 1.0f;
        tri[2].x = vt[3 * i2 + 0];
        tri[2].y = vt[3 * i2 + 1];
        tri[2].z = vt[3 * i2 + 2];
        tri[2].w = 1.0f;
        f_0a5e88(&d2, &tri[2], &tri[1]);
        n.x = tri[1].x - tri[0].x;
        n.y = tri[1].y - tri[0].y;
        n.z = tri[1].z - tri[0].z;
        n.w = 1.0f;
        f_0a5f74(&dir1, &d2, &n);
        f_0a65e4(&r, &dir1);
        return r;
    }
}

/* @draft 0x0b0ae0 us f_0b0ae0
   WHAT IT DOES: Returns the height of a cell's triangle at the point's x and z. A quad cell
   (next index not 0xffff) splits at the crossings found by f_0b1084 and interpolates along
   the crossing segment (by x or by z, whichever is the longer span); a triangle gives the
   point's y less the normal's dot product with the offset from the first vertex, over the
   normal's y.
   Remaining difference: size 680 vs 696; 172/174 words differ from +0x0; a call to f_0a5e88 sits where retail calls f_0a65e4 (+0x280) because the normalise and the subtraction are scheduled differently. */
float f_0b0ae0(PolySet *p, const Vec4 *v, const Cell *c)
{
    const float *vt = PF(const float *, p, 72);
    Vec4 q[4];
    Vec4 o[2];
    Vec4 e0, nrm, dir, n2, tmp;
    unsigned short i0 = c->i0, i1 = c->i1, i2 = c->i2, i3 = c->next;
    int k;

    if (c->next != 0xffff) {
        for (k = 0; k < 3; k++) {
            ((float *)&q[0])[k] = vt[3 * i1 + k];
            ((float *)&q[1])[k] = vt[3 * i2 + k];
            ((float *)&q[2])[k] = vt[3 * i3 + k];
            ((float *)&q[3])[k] = vt[3 * i0 + k];
        }
        f_0b1084(p, v, q, o);
        {
            float dx = o[0].x - o[1].x;
            float dz = o[0].z - o[1].z;
            float t;
            if (dx < 0.0f)
                dx = -dx;
            if (dz < 0.0f)
                dz = -dz;
            if (dz < dx)
                t = (v->x - o[0].x) / (o[1].x - o[0].x);
            else
                t = (v->z - o[0].z) / (o[1].z - o[0].z);
            return o[0].y + t * (o[1].y - o[0].y);
        }
    } else {
        float dot;
        Vec4 P0, P1, P2;

        P0.x = vt[3 * i0 + 0];
        P0.y = vt[3 * i0 + 1];
        P0.z = vt[3 * i0 + 2];
        P0.w = 1.0f;
        P1.x = vt[3 * i1 + 0];
        P1.y = vt[3 * i1 + 1];
        P1.z = vt[3 * i1 + 2];
        P1.w = 1.0f;
        P2.x = vt[3 * i2 + 0];
        P2.y = vt[3 * i2 + 1];
        P2.z = vt[3 * i2 + 2];
        P2.w = 1.0f;
        f_0a5e88(&e0, &P2, &P1);
        dir.x = P1.x - P0.x;
        dir.y = P1.y - P0.y;
        dir.z = P1.z - P0.z;
        dir.w = 1.0f;
        f_0a5f74(&n2, &e0, &dir);
        f_0a65e4(&nrm, &n2);
        f_0a5e88(&tmp, v, &P0);
        dot = f_0a5f54(&nrm, &tmp);
        return v->y - dot / nrm.y;
    }
}

/* @draft 0x0af678 us f_0af678
   WHAT IT DOES: Loads a polygon set from its data block: the count, the cell list and the
   triangle table of the set, and the origin and cell size of its first record.
   Remaining difference: size 272 vs 272; 49/68 words differ from +0x8 (the header stores are ordered differently around the f_0a5e6c call). 2026-11-16: the running pointer lands in a1 because sched1 issues the n load before data+4, so data dies in the add and local-alloc ties the pointer to it; retail adds first (data still live, pointer in a3, freeing a1 for the early move a1,s1). */
void f_0af678(PolySet *p, void *data)
{
    char *a3 = (char *)data + 4;
    unsigned int n = *(unsigned int *)data;
    unsigned int m, k, g;
    char *v0;
    char *s0;
    struct W4 {
        int a, b, c, d;
    } sum;

    PF(char *, p, 52) = a3;
    PF(unsigned int, p, 48) = n;
    a3 += n * 4;
    PF(char *, p, 56) = a3;
    a3 += n * 4;
    m = *(unsigned int *)a3;
    a3 += 4;
    PF(char *, p, 72) = a3;
    PF(unsigned int, p, 68) = m;
    v0 = a3 + m * 12;
    k = *(unsigned int *)v0;
    a3 = v0 + 4;
    PF(char *, p, 64) = a3;
    PF(unsigned int, p, 60) = k;
    s0 = a3 + k * 24;
    PF(float, p, 0) = *(float *)(s0 + 0);
    PF(float, p, 4) = *(float *)(s0 + 4);
    PF(float, p, 8) = *(float *)(s0 + 8);
    PF(float, p, 32) = *(float *)(s0 + 12);
    PF(float, p, 36) = *(float *)(s0 + 16);
    PF(float, p, 40) = *(float *)(s0 + 20);
    f_0a5e6c((Vec4 *)&sum, (Vec4 *)p, (Vec4 *)((char *)p + 32));
    PF(int, p, 16) = sum.a;
    PF(int, p, 20) = sum.b;
    PF(int, p, 24) = sum.c;
    PF(int, p, 28) = sum.d;
    g = *(unsigned int *)(s0 + 24);
    PF(unsigned int, p, 84) = g;
    PF(char *, p, 88) = s0 + 28;
    PF(unsigned int, p, 76) = *(unsigned int *)(s0 + 28 + 32 * g);
    PF(char *, p, 80) = s0 + 28 + 32 * g + 4;
}

/* The grid descent shared by the point queries (0x0af8b0 to 0x0af954 in each walk): starting
   at the last record of the grid table, each level subdivides the cell size by 4 in x and z,
   finds the 4 by 4 sub-cell the point is in and moves to the record that sub-cell names, up to
   100 levels. A record whose first count is 0 ends the walk. Returns 0 when the point is outside
   the box or the set is empty, 1 when the walk ends in a record (rec, blk: the block of the
   record's triangle list) and 2 when the next record index goes negative. */
static int cell_walk(PolySet *p, const Vec4 *v, const Rec **recOut, char **blkOut)
{
    int t2 = (int)PF(unsigned int, p, 76);
    int t3 = 0;
    float ox, oz, wx, wz;
    const char *tab;
    char *rb;
    const Rec *r;
    char *blk;

    if (t2 <= 0)
        return 0;
    if (PF(float, p, 16) < v->x)
        return 0;
    if (v->x < PF(float, p, 0))
        return 0;
    if (PF(float, p, 24) < v->z)
        return 0;
    if (v->z < PF(float, p, 8))
        return 0;
    ox = PF(float, p, 0);
    oz = PF(float, p, 8);
    wx = PF(float, p, 32);
    wz = PF(float, p, 40);
    t2 = t2 - 1;
    tab = PF(const char *, p, 80);
    rb = PF(char *, p, 88);
    do {
        r = (const Rec *)(tab + 6 * t2);
        blk = rb + 32 * r->idx;
        t3++;
        if (r->n0 == 0)
            break;
        wx = wx * 0.25f;
        wz = wz * 0.25f;
        {
            float fx = (v->x - ox) / wx;
            float fz = (v->z - oz) / wz;
            int ix = (int)fx;
            int iz = (int)fz;
            int sub = ix + 4 * iz;
            unsigned short a1;

            ox = ox + wx * (float)ix;
            oz = oz + wz * (float)iz;
            if (sub == 0)
                a1 = r->base;
            else
                a1 = (unsigned short)(((const unsigned short *)blk)[sub - 1] + r->base);
            t2 = (short)a1;
            if (t2 < 0)
                return 2;
        }
    } while (t3 < 100);
    *recOut = r;
    *blkOut = blk;
    return 1;
}

/* The id of the i-th triangle of a record: the record's base, then running deltas from the
   block's halfword list. */
static unsigned short tri_id(const char *blk, const Rec *r, int i)
{
    unsigned short base = r->base;
    if (i == 0)
        return base;
    return (unsigned short)(((const unsigned short *)blk)[i - 1] + base);
}

/* @draft 0x0af788 us f_0af788
   WHAT IT DOES: Returns the id of the triangle of the set under a point (x, z), or 0xffff when
   the point is outside the set.
   Remaining difference: size 556 vs 572; the result is returned in v0 where retail keeps it in a0 and moves it at the epilogue; the grid walk is otherwise written out inline as retail. */
unsigned short f_0af788(PolySet *p, const Vec4 *v)
{
    int t2 = (int)PF(unsigned int, p, 76);
    float x, z;
    Vec4 org, cs;
    int t3;
    const char *tab;
    char *rb;
    Rec *r;
    char *blk;
    int i;
    unsigned short sid;
    unsigned short r2;

    if (t2 <= 0)
        goto none;
    x = v->x;
    if (PF(float, p, 16) < x)
        goto none;
    if (x < PF(float, p, 0))
        goto none;
    z = v->z;
    if (PF(float, p, 24) < z)
        goto none;
    if (z < PF(float, p, 8))
        goto none;
    org = PF(Vec4, p, 0);
    cs = PF(Vec4, p, 32);
    t2 = t2 - 1;
    t3 = 0;
    tab = PF(const char *, p, 80);
    rb = PF(char *, p, 88);
    do {
        r = (Rec *)(tab + 6 * t2);
        blk = rb + 32 * r->idx;
        t3++;
        if (r->n0 == 0)
            break;
        {
            unsigned short a1 = r->base;
            int ix, iz, sub;
            cs.x = cs.x * 0.25f;
            cs.z = cs.z * 0.25f;
            ix = (int)((x - org.x) / cs.x);
            iz = (int)((z - org.z) / cs.z);
            org.x = org.x + cs.x * (float)ix;
            org.z = org.z + cs.z * (float)iz;
            sub = ix + 4 * iz;
            if (sub != 0)
                a1 = (unsigned short)(((unsigned short *)blk)[sub - 1] + r->base);
            t2 = (short)a1;
            if (t2 < 0)
                goto none;
        }
    } while (t3 < 100);
    if (r->n1 <= 0)
        goto none;
    for (i = 0; i < r->n1; i++) {
        if (i == 0)
            sid = r->base;
        else
            sid = (unsigned short)(((unsigned short *)blk)[i - 1] + r->base);
        if (f_0b0910(p, v, &sid))
            goto done;
    }
    none:
    return 0xffff;
done:
    return sid;
}

/* @draft 0x0af9c4 us f_0af9c4
   WHAT IT DOES: The triangle query of 0x0af788 that also returns the height of the triangle
   under the point, written through h.
   Remaining difference: size 220 vs 628; the grid walk is 408 bytes short (the walk is shared with f_0af788, same gap), so 157/157 words differ. */
unsigned short f_0af9c4(PolySet *p, const Vec4 *v, float *h)
{
    const Rec *r;
    char *blk;
    int i;

    if (cell_walk(p, v, &r, &blk) != 1)
        return 0xffff;
    if (r->n1 <= 0)
        return 0xffff;
    for (i = 0; i < r->n1; i++) {
        unsigned short sid = tri_id(blk, r, i);
        if (f_0b0910(p, v, &sid)) {
            *h = f_0b0ae0(p, v, (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)sid));
            return sid;
        }
    }
    return 0xffff;
}

/* @draft 0x0afc38 us f_0afc38
   WHAT IT DOES: The triangle query that also returns the height (through h) and the cell
   record it found (through rec; NULL when the walk runs off the table).
   Remaining difference: size 252 vs 644; the grid walk is 392 bytes short, and the record store and the height call are not yet scheduled as retail. */
unsigned short f_0afc38(PolySet *p, const Vec4 *v, float *h, const Rec **rec)
{
    const Rec *r;
    char *blk;
    int i;
    int w = cell_walk(p, v, &r, &blk);

    if (w == 2) {
        *rec = 0;
        return 0xffff;
    }
    if (w != 1)
        return 0xffff;
    *rec = r;
    if (r->n1 <= 0)
        return 0xffff;
    for (i = 0; i < r->n1; i++) {
        unsigned short sid = tri_id(blk, r, i);
        if (f_0b0910(p, v, &sid)) {
            *h = f_0b0ae0(p, v, (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)sid));
            return sid;
        }
    }
    return 0xffff;
}

/* @draft 0x0afebc us f_0afebc
   WHAT IT DOES: Walks the triangles of one cell record and returns the first id whose triangle
   holds the point, or 0xffff for none.
   Remaining difference: size 192 vs 192; 21/48 words differ from +0x1c (the record pointer is held in t3 where retail uses a2: retail loads rec->base at the loop top before `move a2,sp`, so rec dies there and takes a2; here sched1 puts the argument moves first, rec conflicts with a2; retail also sets i = 0 in the prologue and shares the 0xffff return). */
unsigned short f_0afebc(PolySet *p, const Vec4 *v, const Rec **recp)
{
    const Rec *rec = *recp;
    char *blk = PF(char *, p, 88) + 32 * rec->idx;
    int i;
    unsigned short sid;

    if (rec->n1 <= 0)
        return 0xffff;
    for (i = 0; i < rec->n1; i++) {
        unsigned short base = rec->base;
        unsigned short x = base;
        if (i != 0)
            x = (unsigned short)(((unsigned short *)blk)[i - 1] + base);
        sid = x;
        if (f_0b0910(p, v, &sid))
            return sid;
        rec = *recp;
    }
    return 0xffff;
}

/* @draft 0x0aff7c us f_0aff7c
   WHAT IT DOES: The triangle query that also checks the point's height against the triangles
   of the cell: among the triangles holding the point and within 2000 units of its y, the one
   nearest in height is returned, or 0xffff for none.
   Remaining difference: size 288 vs 696; the grid walk and the band loop are not yet matched (174/174 words differ from +0x0). */
unsigned short f_0aff7c(PolySet *p, const Vec4 *v)
{
    const Rec *r;
    char *blk;
    unsigned short best = 0xffff;
    float bestd = 2000.0f;
    int i;

    if (cell_walk(p, v, &r, &blk) != 1)
        return 0xffff;
    if (r->n1 <= 0)
        return 0xffff;
    for (i = 0; i < r->n1; i++) {
        unsigned short sid = tri_id(blk, r, i);
        if (f_0b0910(p, v, &sid)) {
            float d = f_0b0ae0(p, v, (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)sid)) - v->y;
            if (d < 0.0f)
                d = -d;
            if (d < bestd) {
                bestd = d;
                best = sid;
            }
        }
    }
    return best;
}

/* @draft 0x0b0234 us f_0b0234
   WHAT IT DOES: The height query: returns the id of the triangle under a point and its
   height through h, or 0xffff for none. Among the triangles holding the point, the one nearest
   in height (within 2000 units of the point's y) is chosen.
   Remaining difference: size 308 vs 716; the grid walk and the band loop are not yet matched (179/179 words differ from +0x0). */
unsigned short f_0b0234(PolySet *p, const Vec4 *v, float *h)
{
    const Rec *r;
    char *blk;
    unsigned short best = 0xffff;
    float bestd = 2000.0f;
    int i;

    if (cell_walk(p, v, &r, &blk) != 1)
        return 0xffff;
    if (r->n1 <= 0)
        return 0xffff;
    for (i = 0; i < r->n1; i++) {
        unsigned short sid = tri_id(blk, r, i);
        if (f_0b0910(p, v, &sid)) {
            float hh = f_0b0ae0(p, v, (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)sid));
            float d = hh - v->y;
            if (d < 0.0f)
                d = -d;
            if (d < bestd) {
                bestd = d;
                best = sid;
                *h = hh;
            }
        }
    }
    return best;
}

/* @draft 0x0b0500 us f_0b0500
   WHAT IT DOES: The cell query that also returns the height (through h) and the cell record it
   found (through rec; NULL when the walk runs off the table). Triangle choice as in 0x0b0234.
   Remaining difference: size 340 vs 724; the grid walk and the band loop with the record store are not yet matched (181/181 words differ from +0x0). */
unsigned short f_0b0500(PolySet *p, const Vec4 *v, float *h, const Rec **rec)
{
    const Rec *r;
    char *blk;
    unsigned short best = 0xffff;
    float bestd = 2000.0f;
    int i;
    int w = cell_walk(p, v, &r, &blk);

    if (w == 2) {
        *rec = 0;
        return 0xffff;
    }
    if (w != 1)
        return 0xffff;
    *rec = r;
    if (r->n1 <= 0)
        return 0xffff;
    for (i = 0; i < r->n1; i++) {
        unsigned short sid = tri_id(blk, r, i);
        if (f_0b0910(p, v, &sid)) {
            float hh = f_0b0ae0(p, v, (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)sid));
            float d = hh - v->y;
            if (d < 0.0f)
                d = -d;
            if (d < bestd) {
                bestd = d;
                best = sid;
                *h = hh;
            }
        }
    }
    return best;
}

/* @draft 0x0b07d4 us f_0b07d4
   WHAT IT DOES: Walks the triangles of one cell record (the ids are the record's base plus
   running deltas from the cell's table); each triangle that holds the point is tested by
   the height of its plane, and the one nearest the point's y (within 2000 units) is returned,
   or 0xffff for none.
   Remaining difference: size 316 vs 316; 25/79 words differ from +0x24 (register allocation and slot filling around the id build). Tried 2026-11-16: reading rec->base twice (no base local) gives retail's gcse copy (lhu v1 at the loop top, rec in a2, the copy in the beqz slot) but the copy comes out andi v0,v1,0xffff (x is unsigned short, retail: move) and the early return no longer shares move v0,s5 (320 B); next: x as int with the cast only on the sum. */
unsigned short f_0b07d4(PolySet *p, const Vec4 *v, const Rec **recp)
{
    const Rec *rec = *recp;
    char *blk = PF(char *, p, 88) + 32 * rec->idx;
    unsigned short best = 0xffff;
    float bestd = 2000.0f;
    int i;

    if (rec->n1 <= 0)
        return 0xffff;
    for (i = 0; i < rec->n1; i++) {
        unsigned short base = rec->base;
        unsigned short x = base;
        unsigned short sid;
        if (i != 0)
            x = (unsigned short)(((unsigned short *)blk)[i - 1] + base);
        sid = x;
        if (f_0b0910(p, v, &sid)) {
            float d = f_0b0ae0(p, v, (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)sid)) - v->y;
            if (d < 0.0f)
                d = -d;
            if (d < bestd) {
                bestd = d;
                best = sid;
            }
        }
        rec = *recp;
    }
    return best;
}

/* @draft 0x0b0910 us f_0b0910
   WHAT IT DOES: Tests whether a point lies inside one triangle (or quad) of the set and returns
   1 when it does: the point must be inside the cell's box and on the inner side of every edge
   within one unit of the edge's length.
   The point-minus-vertex difference lives in a third Vec4 (retail's frame is 144, its x and z
   stored at sp+80/88), the vertex table pointer is read inside the copy loop (hoisted to the
   preheader) and the box tests put the point's coordinate first.
   Remaining difference: 13 words in the edge loop: retail loads vert[i].z after the store of
   w.x (and v->z before it); here sched1 hoists vert[i].z above the store. Reaching vert[i]
   through const Vec4 *a = &vert[i] changes nothing. */
int f_0b0910(PolySet *p, const Vec4 *v, const unsigned short *id)
{
    const Cell *c = (const Cell *)(PF(const char *, p, 64) + 24 * (unsigned int)*id);
    Vec4 vert[4];
    Vec4 edge;
    Vec4 w;
    int n, i, k;

    if (v->x > c->maxx)
        return 0;
    if (v->x < c->minx)
        return 0;
    if (v->z > c->maxz)
        return 0;
    if (v->z < c->minz)
        return 0;

    n = (c->next == 0xffff) ? 3 : 4;
    for (k = 0; k < n; k++) {
        unsigned short idx = ((const unsigned short *)c)[k];
        const float *vt = PF(const float *, p, 72);
        ((float *)&vert[k])[0] = vt[3 * idx + 0];
        ((float *)&vert[k])[1] = vt[3 * idx + 1];
        ((float *)&vert[k])[2] = vt[3 * idx + 2];
    }
    for (i = 0; i < n; i++) {
        int j = (i + 1) % n;
        float len, d;
        f_0a5e88(&edge, &vert[j], &vert[i]);
        edge.y = 0.0f;
        len = f_0a65c4(&edge);
        w.x = v->x - vert[i].x;
        w.z = v->z - vert[i].z;
        d = (edge.z * w.x - edge.x * w.z) / len;
        if (1.0f < d)
            return 0;
    }
    return 1;
}
