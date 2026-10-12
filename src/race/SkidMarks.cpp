/* The skid mark object file (retail 0x034c0c to 0x035ef0, the "Blackmark" texture): each car
   has four tyre tracks; a track keeps the last two points a tyre passed and, while the tyre
   slides, a strip of quads behind it in a shared pool. A strip is a fixed run of vertices
   (two per point) in one buffer allocated at load time; when a strip is full it is closed
   and the track starts a new one. Closed strips fade with distance from the camera and are
   recycled once the pool runs low. */

/* A vector unit quadword: three coordinates and a fourth word kept zero. */
struct Vec4 {
    float x, y, z;
    int w;
} __attribute__((aligned(16)));

struct Matrix;
struct CInfo;

extern "C" {
void *f_125c4c(unsigned int align, unsigned int size);
void free(void *p);
CInfo *f_02347c(unsigned int id);
unsigned int *f_0249a0(CInfo *info, unsigned int *p);
char *f_021b38(unsigned int size);
void f_028c70(void);
void f_028ca8(void);
void f_028e9c(const Matrix *m);
float f_027ebc(const Vec4 *a, const Vec4 *b);
Vec4 *f_027f18(Vec4 *d, const Vec4 *a);
Vec4 *f_027edc(Vec4 *d, const Vec4 *a, const Vec4 *b);
Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);
float f_0e3b3c(void *view, float a, float b);
}

extern float D_1d1bd4;
extern float D_1d1bd8;
extern unsigned char D_1d1be0[4];
extern unsigned char D_1d1be4[4];
extern char D_23f7f0[];

/* One strip vertex: texture coordinates, colour, position (GE 8 bit uv, 8888 colour, float). */
struct SkidVtx {
    unsigned char u, v;
    unsigned short pad;
    unsigned int color;
    float x, y, z;
};

/* One strip in the pool. */
struct SkidRec {
    unsigned short count;
    unsigned short state;
    float start;
    float end;
    SkidVtx *verts;
} __attribute__((packed));

struct SkidPool {
    SkidRec *recs;
    unsigned int stride;
    int count;
    int used;
    unsigned int next;
};

/* One point of a track: where the tyre was, the half width vector across it, the strip's
   distance mark there and the mark's opacity. */
struct SkidPoint {
    Vec4 p;
    Vec4 d;
    Vec4 m32;
    float mark;
    unsigned char alpha;
};

struct SkidTrack {
    SkidPoint pt[2];
    unsigned short cur;
    unsigned short count;
    SkidRec *rec;
    bool Drawable() { return count > 1; }
};

struct SkidCar {
    SkidTrack t[4];
};

struct SkidMarks {
    CInfo *tex;
    int m4;
    int nrec;
    int nvert;
    int keep;
    int ncars;
    SkidPool pool;
    SkidCar *cars;
    void *buf;
};

/* @implements 0x034c0c us f_034c0c
   WHAT IT DOES: Returns how many bytes a pool of the given number of strips needs, each strip
   holding the given number of points (two vertices per point). */
extern "C" unsigned int f_034c0c(SkidPool *p, int nvert, int nrec)
{
    return nvert * nrec * 2 * sizeof(SkidVtx) + nrec * sizeof(SkidRec);
}

/* @implements 0x034c2c us f_034c2c
   WHAT IT DOES: Lays out the strip pool in the given buffer: the strip records first, then
   each strip's vertices, every strip empty and unused. */
extern "C" void f_034c2c(SkidPool *p, void *buf, int nvert, int nrec)
{
    unsigned int i;
    SkidVtx *v;

    p->stride = nvert * 2;
    p->recs = (SkidRec *)buf;
    p->count = nrec;
    p->next = 0;
    p->used = 0;
    v = (SkidVtx *)((SkidRec *)buf + nrec);
    for (i = 0; i < (unsigned int)p->count; i++) {
        p->recs[i].count = 0;
        p->recs[i].state = 0;
        p->recs[i].start = 0;
        p->recs[i].end = 0;
        p->recs[i].verts = v;
        v += p->stride;
    }
}

/* @draft 0x034cfc us f_034cfc
   WHAT IT DOES: Takes a free strip from the pool, searching round from where the last search
   stopped; returns 0 when every strip is in use. 
   Remaining: retail keeps the result in v1 (zeroed on both failure paths, moved to v0 at the single exit); this source holds it in a saved temporary, shifting registers. */
extern "C" SkidRec *f_034cfc(SkidPool *p)
{
    SkidRec *r = 0;

    if (p->used < p->count) {
        unsigned int idx = p->next;
        unsigned int k;
        for (k = 0; k < (unsigned int)p->count; k++) {
            if (p->recs[idx].state == 0) {
                p->recs[idx].state = 1;
                p->recs[idx].count = 0;
                p->recs[idx].start = 0;
                p->recs[idx].end = 0;
                p->used++;
                p->next = (p->next + 1) % p->count;
                r = &p->recs[idx];
                break;
            }
            idx = (idx + 1) % p->count;
        }
    }
    return r;
}

/* @implements 0x034df4 us f_034df4
   WHAT IT DOES: Gives a strip back to the pool. */
extern "C" void f_034df4(SkidPool *p, SkidRec *r)
{
    r->state = 0;
    r->count = 0;
    if (--p->used < 0)
        p->used = 0;
}

/* @implements 0x034e24 us f_034e24
   WHAT IT DOES: Appends one point to a strip: two vertices either side of the tyre's path,
   with the given opacity, the texture coordinates cycling down the strip. */
extern "C" void f_034e24(SkidPool *p, SkidRec *r, SkidPoint *s, int alpha)
{
    unsigned int n = r->count;
    SkidVtx *v = &r->verts[n];
    unsigned int c = (alpha << 24) | 0xffffff;

    v->x = s->p.x + s->d.x;
    v->color = c;
    v->y = s->p.y + s->d.y;
    v->z = s->p.z + s->d.z;
    v->u = D_1d1be0[n & 3];
    v->v = D_1d1be4[n & 3];
    v++;
    v->color = c;
    v->x = s->p.x - s->d.x;
    v->y = s->p.y - s->d.y;
    v->z = s->p.z - s->d.z;
    v->u = D_1d1be0[((n & 3) + 1) & 3];
    v->v = D_1d1be4[((n & 3) + 1) & 3];
    r->count += 2;
}

/* @implements 0x034f5c us f_034f5c
   WHAT IT DOES: Starts a strip at a point, fully transparent, and records the point's mark as
   the strip's start and end. */
extern "C" void f_034f5c(SkidPool *p, SkidRec *r, SkidPoint *s)
{
    f_034e24(p, r, s, 0);
    r->start = s->mark;
    r->end = s->mark;
}

extern "C" void f_03505c(SkidPool *p, SkidRec *r, SkidPoint *s);

/* @implements 0x034fd0 us f_034fd0
   WHAT IT DOES: Extends a strip to a point. When the strip has no room left it is closed at
   that point instead and 0 is returned. */
extern "C" int f_034fd0(SkidPool *p, SkidRec *r, SkidPoint *s)
{
    if (!(r->count < p->stride - 4)) {
        f_03505c(p, r, s);
        return 0;
    }
    f_034e24(p, r, s, s->alpha);
    r->end = s->mark;
    return 1;
}

/* @implements 0x03505c us f_03505c
   WHAT IT DOES: Closes a strip with a transparent last point, so it starts to fade. */
extern "C" void f_03505c(SkidPool *p, SkidRec *r, SkidPoint *s)
{
    f_034e24(p, r, s, 0);
    r->end = s->mark;
    r->state = 2;
}

/* @implements 0x0350bc us f_0350bc
   WHAT IT DOES: Empties a tyre track (no points, no strip). */
extern "C" void f_0350bc(SkidTrack *t)
{
    t->rec = 0;
    t->count = 0;
    t->cur = 0;
}

static inline void SetPoint(SkidPoint *s, const Vec4 *p, const Vec4 &d, float mark, unsigned int alpha)
{
    s->p = *p;
    s->d = d;
    s->mark = mark;
    s->alpha = alpha;
}

static inline Vec4 Sub(const Vec4 *a, const Vec4 *b)
{
    Vec4 r;
    r.x = a->x - b->x;
    r.y = a->y - b->y;
    r.z = a->z - b->z;
    r.w = 0;
    return r;
}

/* @implements 0x0351a8 us f_0351a8
   WHAT IT DOES: Starts a track at a point: both remembered points at the tyre's position with
   no width, the older one transparent. */
extern "C" void f_0351a8(SkidTrack *t, const Vec4 *pos, const Vec4 *dir, float mark, float alpha)
{
    Vec4 zero = {0, 0, 0, 0};

    SetPoint(&t->pt[0], pos, zero, mark, 0);
    SetPoint(&t->pt[1], pos, zero, mark, (unsigned int)(alpha * 255.0f));
    t->cur = 1;
    t->count = 1;
}

/* @implements 0x03529c us f_03529c
   WHAT IT DOES: Moves a track's tyre to a new point. The width vector is the step's direction
   crossed with the given up vector and scaled. Once the tyre has moved far enough the point
   is committed: the first committed point starts the track's strip, later ones extend it,
   and when the strip is full the track is closed and emptied (returning 0). Returns 0 also
   when the tyre has not moved at all. */
extern "C" int f_03529c(SkidTrack *t, SkidPool *pool, const Vec4 *pos, const Vec4 *up, float mark, float alpha)
{
    Vec4 v;
    float len;

    v = Sub(pos, &t->pt[(t->cur + 1) & 1].p);
    len = f_027ebc(&v, &v);

    if (len == 0.0f)
        return 0;
    f_027f18(&v, &v);
    f_027edc(&v, &v, up);
    f_027e6c(&v, &v, D_1d1bd8);
    SetPoint(&t->pt[t->cur], pos, v, mark, (unsigned int)(alpha * 255.0f));
    if (D_1d1bd4 < len) {
        if (t->count == 1) {
            SkidPoint *p1 = &t->pt[1];
            t->pt[0].d = p1->d;
            f_034f5c(pool, t->rec, &t->pt[0]);
            f_034fd0(pool, t->rec, p1);
        } else if (t->count != 0) {
            if (!f_034fd0(pool, t->rec, &t->pt[t->cur])) {
                t->count++;
                t->cur = (t->cur + 1) & 1;
                SetPoint(&t->pt[t->cur], pos, v, mark, (unsigned int)(alpha * 255.0f));
                f_03505c(pool, t->rec, &t->pt[t->cur]);
                f_0350bc(t);
                return 0;
            }
        }
        t->count++;
        t->cur = (t->cur + 1) & 1;
        SetPoint(&t->pt[t->cur], pos, v, mark, (unsigned int)(alpha * 255.0f));
    }
    return 1;
}

/* @implements 0x0350cc us f_0350cc
   WHAT IT DOES: Feeds one tyre position to a track while the tyre slides: the point is pushed
   along the given offset first. A track without a strip takes one from the pool (returning 0
   if none is free) and starts there. */
extern "C" int f_0350cc(SkidTrack *t, SkidPool *pool, const Vec4 *pos, const Vec4 *ofs, float mark, float alpha)
{
    Vec4 q;
    q.x = pos->x + ofs->x * 200.0f;
    q.y = pos->y + ofs->y * 200.0f;
    q.z = pos->z + ofs->z * 200.0f;
    if (t->rec)
        return f_03529c(t, pool, &q, ofs, mark, alpha);
    t->rec = f_034cfc(pool);
    if (t->rec == 0)
        return 0;
    f_0351a8(t, &q, ofs, mark, alpha);
    return 1;
}

/* @implements 0x035660 us f_035660
   WHAT IT DOES: Ends a track when its tyre stops sliding: closes its strip at the last point
   and empties the track. */
extern "C" void f_035660(SkidTrack *t, SkidPool *pool)
{
    if (t->rec) {
        f_03505c(pool, t->rec, &t->pt[t->cur]);
        f_0350bc(t);
    }
}

/* @implements 0x0356b0 us f_0356b0
   WHAT IT DOES: Sets up the skid marks for the given number of cars: four empty tracks per car,
   a pool of strips in one 64 byte aligned buffer, and the Blackmark texture. Returns the
   pool's size in bytes. */
extern "C" unsigned int f_0356b0(SkidMarks *m, int ncars, int nrec, int nvert, int keep)
{
    int i, j;
    unsigned int size;

    m->keep = keep;
    m->m4 = 400;
    m->nrec = nrec;
    m->nvert = nvert;
    m->ncars = ncars;
    m->cars = new SkidCar[ncars];
    for (i = 0; i < m->ncars; i++)
        for (j = 0; j < 4; j++) {
            SkidCar *c = &m->cars[i];
            f_0350bc(&c->t[j]);
        }
    size = f_034c0c(&m->pool, nvert, nrec);
    f_034c2c(&m->pool, m->buf = f_125c4c(64, size), nvert, nrec);
    m->tex = f_02347c(0xa000004);
    return size;
}

/* @implements 0x0357cc us f_0357cc
   WHAT IT DOES: Frees the tracks and the strip pool. */
extern "C" void f_0357cc(SkidMarks *m)
{
    if (m->cars)
        delete[] m->cars;
    m->cars = 0;
    free(m->buf);
    m->buf = 0;
}

extern "C" unsigned int *f_035aa0(SkidMarks *m, unsigned int *dl, float x, float y, float z);
extern "C" unsigned int *f_035d1c(SkidMarks *m, SkidTrack *t, unsigned int *dl);

/* @implements 0x035818 us f_035818
   WHAT IT DOES: Draws the skid marks in the car's frame: selects the Blackmark texture, sets
   blending, an identity world matrix and the vertex format, draws the pool's strips, then the
   piece between each track's two remembered points, and restores the state. */
extern "C" unsigned int *f_035818(SkidMarks *m, char *car, unsigned int *dl, float x, float y, float z)
{
    int i, j;

    f_028c70();
    f_028e9c((const Matrix *)(car + 288));
    dl = f_0249a0(m->tex, dl);
    *dl++ = 0xdf000032;
    *dl++ = 0x21000001;
    *dl++ = 0x1e000001;
    *dl++ = 0x22000001;
    *dl++ = 0x17000000;
    *dl++ = 0x1f000001;
    *dl++ = 0xdbff0106;
    *dl++ = 0xe7000001;
    *dl++ = 0xc9000100;
    *dl++ = 0x1d000001;
    *dl++ = 0x3a000000;
    *dl++ = 0x3b3f8000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b3f8000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b3f8000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x3b000000;
    *dl++ = 0x47470064;
    *dl++ = 0x1200019d;
    dl = f_035aa0(m, dl, x, y, z);
    for (i = 0; i < m->ncars; i++)
        for (j = 0; j < 4; j++)
        {
            SkidCar *c = &m->cars[i];
            if (c->t[j].Drawable())
                dl = f_035d1c(m, &c->t[j], dl);
        }
    f_028ca8();
    *dl++ = 0xdbff0006;
    *dl++ = 0xe7000000;
    *dl++ = 0x47470000;
    return dl;
}

/* @draft 0x035aa0 us f_035aa0
   WHAT IT DOES: Draws every strip of the pool with at least three points as a triangle strip.
   A strip whose both ends are further from the camera than the fade distance is not drawn;
   if it is closed and the pool is running low, it is marked for recycling, and strips so
   marked are returned to the pool. 
   Remaining: retail keeps the pool pointer in s2 and a copy in a1 reset at the loop latch for the recycle call; register choice and the state 2 test branch direction differ. */
extern "C" unsigned int *f_035aa0(SkidMarks *m, unsigned int *dl, float x, float y, float z)
{
    SkidPool *pool = &m->pool;
    unsigned int i;

    for (i = 0; i < (unsigned int)pool->count; i++) {
        SkidRec *r = &m->pool.recs[i];
        float a, b;
        if (r->state == 3) {
            f_034df4(&m->pool, r);
            continue;
        }
        if (r->count < 3)
            continue;
        {
        float s0 = r->start, s1 = r->end;
        a = 1.0f - f_0e3b3c(D_23f7f0, z, s0) / 700.0f;
        b = 1.0f - f_0e3b3c(D_23f7f0, z, s1) / 700.0f;
        }
        if (a < 0 && b < 0) {
            if (r->state == 2 && m->keep < pool->used)
                r->state = 3;
            continue;
        }
        *dl++ = 0x10000000 | ((((unsigned int)r->verts >> 24) & 0xf) << 16);
        *dl++ = ((unsigned int)r->verts & 0xffffff) | 0x01000000;
        *dl++ = r->count | 0x04040000;
    }
    return dl;
}

/* @implements 0x035d1c us f_035d1c
   WHAT IT DOES: Draws the piece of a track between its two remembered points, the part its
   strip does not cover yet, as a four vertex strip. */
extern "C" unsigned int *f_035d1c(SkidMarks *m, SkidTrack *t, unsigned int *dl)
{
    SkidVtx *v = (SkidVtx *)f_021b38(80);
    SkidVtx *v0 = v;
    SkidPoint *a = &t->pt[(t->cur + 1) & 1];
    SkidPoint *b;

    v->color = (a->alpha << 24) | 0xffffff;
    v->x = a->p.x + a->d.x;
    v->y = a->p.y + a->d.y;
    v->z = a->p.z + a->d.z;
    v->u = 0;
    v->v = 0;
    v++;
    v->color = (a->alpha << 24) | 0xffffff;
    v->x = a->p.x - a->d.x;
    v->y = a->p.y - a->d.y;
    v->z = a->p.z - a->d.z;
    v->u = 0x80;
    v->v = 0;
    v++;
    b = &t->pt[t->cur];
    v->color = (b->alpha << 24) | 0xffffff;
    v->x = b->p.x + b->d.x;
    v->y = b->p.y + b->d.y;
    v->z = b->p.z + b->d.z;
    v->u = 0;
    v->v = 0x80;
    v++;
    v->color = (b->alpha << 24) | 0xffffff;
    v->x = b->p.x - b->d.x;
    v->y = b->p.y - b->d.y;
    v->z = b->p.z - b->d.z;
    v->u = 0x80;
    v->v = 0x80;
    *dl++ = 0x10000000 | ((((unsigned int)v0 >> 24) & 0xf) << 16);
    *dl++ = ((unsigned int)v0 & 0xffffff) | 0x01000000;
    *dl++ = 0x04040004;
    return dl;
}
