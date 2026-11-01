/* The render setup object file (retail 0x0d6280 to 0x0d7ee4): the course draw. It walks the
   map clipper's command list (the draw groups of a course part), writes the GE commands for
   them into a display list, hands the queued per texture draws on to the writer, which tests
   each against the view and writes (and where needed clips) its display list, and keeps the
   two scratch buffers it needs (the cylinder map display lists and the scissor vertices) in
   the clipper. The model and texture initialisers and the thin wrappers sit between. */

typedef unsigned int u32;

/* A float's bits, for the graphics engine's float command arguments. */
static inline u32 Bits(float f)
{
    union {
        float f;
        u32 u;
    } b;
    b.f = f;
    return b.u;
}

struct V4 {
    float x, y, z, w;
};

/* The camera as the course draw reads it (src/system/CameraView.cpp): position at 0, the second
   plane set at 208, the view matrix words at 288, a turn angle at 480, near and far at 488 and
   492. */
struct DView {
    V4 pos;
    char m16[192];
    V4 planeB[4];
    char m272[16];
    u32 vm[16];
    char m352[128];
    float f480;
    char m484[4];
    float zNear;
    float zFar;
};

/* One command of the shading setup's band table: a draw object and a distance. */
struct DrawKind {
    short kind;
};
struct DrawObj {
    int m0;
    DrawKind *info;
};
struct Band {
    DrawObj *tag;
    float dist;
};
struct Shade {
    int m0[12];
    Band *bands;
};

/* The map clipper (src/race/MapClip.cpp) as far as the draw reads it. */
struct Clip {
    int m0[2];
    Shade *shade;
    char m12[4028];
    char *scis;
    char *cyl;
};

/* A drawable inside a part: a sphere (centre and radius) and the next record is in the
   texture group's queue. */
struct Sphere {
    int m0[4];
    V4 c;
};
struct PartInfo {
    int w0;
};
struct Part {
    int m0;
    PartInfo *info;
    int m8;
    unsigned int count;
    Sphere *sub[1];
};
struct PartList {
    unsigned int n;
    Part *parts[1];
};
struct Holder {
    void *group;
    int m4;
    PartList *lists[1];
};

/* A model entry of the table at D_23f790 (64 bytes). */
struct Model {
    char *name;
    unsigned int flags;
    int m8;
    int type;
    Holder *holder;
    int m20;
    V4 *spheres;
    char m28[36];
};
struct ModelTable {
    int m0;
    Model *tab;
};

/* A word array holding a GE matrix: read as raw words, the translation written as floats. */
union Mat12 {
    u32 w[12];
    float f[12];
};

struct DrawGroups;

typedef u32 *(*DrawFn)(DrawObj *, u32 *);

extern "C" {
extern signed char D_254372;
extern int D_254378;
extern int D_25437c;
extern int D_254380;
extern int D_254384;
extern char *D_254388;
extern int D_23ff04;
extern char D_23c820[];
extern ModelTable D_23f790;
extern Mat12 D_1d4c9c;
extern Mat12 D_1d4ccc;
extern DrawFn D_1d4aec[];
int f_126f1c(const char *fmt, ...);
void f_0cc8a0(void *view);
int f_0cc8c8(void *view, void *c, float r);
int f_0cc9b8(void *view, void *c, float r);
void *f_021b38(unsigned int size);
void f_028c70(void);
void f_028ca8(void);
u32 *f_02dba8(u32 *p);
u32 *f_02dcc8(u32 *p);
void f_02b67c(void *planes);
void f_02b714(void *planes, float d);
void f_0cb8e8(void *group);
void f_0cb940(void *group, void *obj, signed char a, signed char b);
void f_0fea38(void);
int f_0fe990(void *self);
void *f_022d00(void *file, int id);
void *f_022de4(int area, void *file, int id);
void f_0cbd88(void *self);
void f_0231c8(void *self);
void f_0d71f8(DrawGroups *group, DView *view, u32 **dl, char **cyl, char **scis);
}

/* @draft 0x0d6280 us f_0d6280
   WHAT IT DOES: Draws one part of the course from the clipper's command list. It sets the
   culling and the unit's state commands (written to the display list), keeps the scratch
   buffers (allocating them on a first call), then walks the command words: 0x8004 selects a
   model entry (dither, culling and shading commands, and opens its texture group), 0x8006
   switches between the two list kinds, 0x8005 skips a word, and 0x8000/0x8001/0x8002 write the
   projection and world matrices for the near, the far and the sky draw; every other word is an
   index: in the first list kind it calls the draw function of the clipper's band object, in the
   other it tests each sub object of the model's part list against the view and queues the
   visible ones in the texture group. A group is drawn (0x0d71f8) when the list changes
   model or ends. Ends with the state commands that restore the unit, checks the two scratch
   buffers against their sizes and returns the new end of the display list.
   DRAFT: complete transcription of every path; 3784 bytes against 3724, 502 of 931 words
   aligned. The matrix word blocks and the texture draw loops match; what differs is register
   allocation (retail keeps the view in s8 and the ranking local on the stack, here the
   ranking local takes the saved register and the view spills, which shifts every stack slot
   from 36 up by 4) and the 0x8004 block order.
   (The three float constants of the projection words are set after the two end tests, where
   retail has them, and the two end tests are kept apart because one range test would fold
   them.) */
extern "C" u32 *f_0d6280(Clip *self, unsigned short *cmd, u32 *dl, DView *v, int cullA, int resume)
{
    char *scis;
    char *cyl;
    char *scis0;
    char *cyl0;
    DrawGroups *pend;
    int idx;
    int kind;
    int cull;
    int step;
    int mode;
    V4 p;
    float kF;
    float kA;
    float kB;

    D_254378 = D_254372;
    f_0cc8a0(v);
    scis = 0;
    cyl = 0;
    if (!(cullA | resume)) {
        scis = (char *)f_021b38(0x35000);
        cyl = (char *)f_021b38(8192);
    }
    if (resume) {
        scis = self->scis;
        cyl = self->cyl;
    }
    scis0 = scis;
    cyl0 = cyl;
    pend = 0;
    if (D_23ff04) {
        if (cullA)
            *dl++ = 0x9b000001;
        else
            *dl++ = 0x9b000000;
    } else {
        if (cullA)
            *dl++ = 0x9b000000;
        else
            *dl++ = 0x9b000001;
    }
    *dl++ = 0xc9010100;
    *dl++ = 0xe0000000;
    *dl++ = 0xe1ffffff;
    *dl++ = 0x5d0000ff;
    *dl++ = 0x22000001;
    *dl++ = 0x40000000;
    *dl++ = (v->vm[0] >> 8) | 0x41000000;
    *dl++ = (v->vm[1] >> 8) | 0x41000000;
    *dl++ = 0x41000000;
    *dl++ = (v->vm[4] >> 8) | 0x41000000;
    *dl++ = (v->vm[5] >> 8) | 0x41000000;
    *dl++ = 0x41000000;
    *dl++ = (v->vm[7] >> 8) | 0x41000000;
    *dl++ = (v->vm[8] >> 8) | 0x41000000;
    *dl++ = 0x41000000;
    *dl++ = 0x413f0000;
    *dl++ = 0x413f0000;
    *dl++ = 0x413f8000;
    *dl++ = 0x53000001;
    *dl++ = 0x5cffffff;
    idx = -1;
    kind = -1;
    cull = 0;
    D_1d4c9c.f[10] = 0.0f;
    p = v->pos;
    D_1d4c9c.f[9] = p.x;
    p = v->pos;
    D_1d4c9c.f[11] = p.z;
    f_028c70();

    if (*cmd == 0x8007)
        goto done;
    if (*cmd == 0x8008)
        goto done;
    kF = 3000000.0f;
    kA = -2.0f;
    kB = -6000000.0f;
    do {
        step = 1;
        if ((short)*cmd < 0 && pend) {
            f_0d71f8(pend, v, &dl, &cyl, &scis);
            pend = 0;
        }
        if (*cmd == 0x8005) {
            step = 2;
        } else if (*cmd == 0x8004) {
            idx = cmd[1];
            dl = f_02dba8(dl);
            step = 2;
            D_25437c = 0;
            if (D_23f790.tab[idx].type == 1) {
                *dl++ = 0xdcffff01;
                *dl++ = 0xdd020000;
                *dl++ = 0x24000001;
            } else if (D_23f790.tab[idx].type == 5) {
                *dl++ = 0xdd000000;
                *dl++ = 0xdcff0003;
                *dl++ = 0x24000001;
                dl = f_02dcc8(dl);
                D_25437c = 1;
                D_254380 = *(int *)(D_23c820 + 12820);
            } else if (cull) {
                *dl++ = 0xdd020000;
                *dl++ = 0xdcffff01;
                *dl++ = 0x24000001;
            } else {
                *dl++ = 0x24000000;
            }
            D_254384 = D_23f790.tab[idx].flags & 2;
            if (D_23f790.tab[idx].m8 == 0)
                *dl++ = 0x1f000001 - ((D_23f790.tab[idx].flags & 0x10) == 0);
            else
                *dl++ = 0x1f000000;
            pend = *(DrawGroups **)D_23f790.tab[idx].holder;
            f_0cb8e8(pend);
        } else if (*cmd == 0x8006) {
            step = 2;
            kind = cmd[1];
            if (kind == 1)
                *dl++ = 0x24000000;
            f_0fea38();
        } else if ((short)*cmd < 0) {
            switch (*cmd & 0x7fff) {
            case 2:
                *dl++ = 0xe7000000;
                *dl++ = 0x23000001;
                *dl++ = 0x3a000000;
                *dl++ = ((D_1d4ccc.w[0] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[1] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[2] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[3] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[4] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[5] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[6] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[7] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[8] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[9] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[10] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[11] >> 8) & 0xffffff) | 0x3b000000;
                {
                    float f = v->zFar;
                    float n = v->zNear;
                    float a = f * kA * n / (f - n);
                    float b = -(f + n) / (f - n);
                    cull = cullA == 0;
                    *dl++ = 0x3e00000a;
                    *dl++ = ((Bits(b) >> 8) & 0xffffff) | 0x3f000000;
                    *dl++ = 0x3e00000e;
                    *dl++ = ((Bits(a) >> 8) & 0xffffff) | 0x3f000000;
                }
                break;
            case 0:
                *dl++ = 0xe7000001;
                *dl++ = 0x23000000;
                *dl++ = 0x3a000000;
                *dl++ = ((D_1d4c9c.w[0] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[1] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[2] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[3] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[4] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[5] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[6] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[7] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[8] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[9] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[10] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4c9c.w[11] >> 8) & 0xffffff) | 0x3b000000;
                cull = 0;
                break;
            case 1:
                *dl++ = 0xe7000001;
                *dl++ = 0x23000000;
                *dl++ = 0x3a000000;
                *dl++ = ((D_1d4ccc.w[0] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[1] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[2] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[3] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[4] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[5] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[6] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[7] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[8] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[9] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[10] >> 8) & 0xffffff) | 0x3b000000;
                *dl++ = ((D_1d4ccc.w[11] >> 8) & 0xffffff) | 0x3b000000;
                {
                    float n = v->zNear;
                    float a = n * kB / (kF - n);
                    float b = -(n + kF) / (kF - n);
                    cull = 0;
                    *dl++ = 0x3e00000a;
                    *dl++ = ((Bits(b) >> 8) & 0xffffff) | 0x3f000000;
                    *dl++ = 0x3e00000e;
                    *dl++ = ((Bits(a) >> 8) & 0xffffff) | 0x3f000000;
                }
                break;
            }
        } else {
            if (kind == 1) {
                DrawObj *o = self->shade->bands[(short)*cmd].tag;
                cmd++;
                dl = D_1d4aec[o->info->kind](o, dl);
                goto next;
            }
            mode = 0;
            D_254388 = D_23f790.tab[idx].name;
            if (cull) {
                if (!f_0cc9b8(v, &D_23f790.tab[idx].spheres[*cmd], D_23f790.tab[idx].spheres[*cmd].w)) {
                    mode = (D_23f790.tab[idx].flags & 4) != 0;
                    if (D_23f790.tab[idx].type == 1)
                        mode = 2;
                }
            }
            if (v->f480 + v->f480 < 0.17453279f) {
                if (D_23f790.tab[idx].type == 5) {
                    p = v->pos;
                    mode = 3;
                    f_02b714(&v->planeB[0], p.y);
                } else {
                    f_02b67c(&v->planeB[0]);
                }
            }
            {
                PartList *pl = D_23f790.tab[idx].holder->lists[*cmd];
                unsigned int i;
                for (i = 0; i < pl->n; i++) {
                    Part *pt = pl->parts[i];
                    unsigned int j;
                    for (j = 0; j < pt->count; j++) {
                        Sphere *s = pt->sub[j];
                        if (f_0cc8c8(v, &s->c, s->c.w)) {
                            int b = 0;
                            if (pt->info && pt->info->w0 == 2 && cullA == 0)
                                b = 1;
                            f_0cb940(pend, s, mode, b);
                        }
                    }
                }
            }
        }
        cmd += step;
    next:
        if (*cmd == 0x8007)
            break;
    } while (*cmd != 0x8008);
    if (pend)
        f_0d71f8(pend, v, &dl, &cyl, &scis);
done:
    *dl++ = 0xc9000100;
    *dl++ = 0x9b000001;
    *dl++ = 0x4a000000;
    *dl++ = 0x4b000000;
    *dl++ = 0x5cffffff;
    *dl++ = 0x5d0000ff;
    *dl++ = 0xe7000000;
    *dl++ = 0x24000000;
    *dl++ = 0x22000001;
    *dl++ = 0xdbff0107;
    f_028ca8();
    self->cyl = cyl;
    self->scis = scis;
    if (scis - scis0 > 0x34fff) {
        f_126f1c("SCISSOR_BUFFER_SIZE overflow");
        __asm__ volatile("break");
    }
    if (!(cyl - cyl0 < 8192)) {
        f_126f1c("CYLINDER_MAP_BUFFER_SIZE overflow");
        __asm__ volatile("break");
    }
    return dl;
}

/* @implements 0x0d710c us f_0d710c
   WHAT IT DOES: An empty function (a virtual stub with nothing to do). */
extern "C" void f_0d710c(void *self)
{
}

/* @implements 0x0d7114 us f_0d7114
   WHAT IT DOES: An empty function (the same stub as 0x0d710c). */
extern "C" void f_0d7114(void *self)
{
}

/* @implements 0x0d711c us f_0d711c
   WHAT IT DOES: Initialises the model through 0x0fe990; when that reports failure, logs
   "Model Init Failed" through 0x126f1c. */
extern "C" void f_0d711c(void *self)
{
    if (f_0fe990(self) == 0)
        f_126f1c("Model Init Failed");
}

/* @implements 0x0d7154 us f_0d7154
   WHAT IT DOES: Initialises a texture: an id of -1 goes through 0x022d00 with the object,
   any other id through 0x022de4 with the id and the object; when the result is null it logs
   "Texture Init Failed" through 0x126f1c. */
extern "C" void f_0d7154(void *self, int unused, int id)
{
    void *r;
    if (id == -1) {
        r = f_022d00(self, 0);
        if (r == 0)
            f_126f1c("Texture Init Failed");
        return;
    }
    r = f_022de4(id, self, 0);
    if (r == 0)
        f_126f1c("Texture Init Failed");
}

/* @implements 0x0d71b8 us f_0d71b8
   WHAT IT DOES: Passes its argument on to 0x0cbd88. */
extern "C" void f_0d71b8(void *self)
{
    f_0cbd88(self);
}

/* @implements 0x0d71d4 us f_0d71d4
   WHAT IT DOES: Passes its argument on to 0x0231c8. */
extern "C" void f_0d71d4(void *self)
{
    f_0231c8(self);
}

/* @implements 0x0d71f0 us f_0d71f0
   WHAT IT DOES: An empty function (the same stub as 0x0d710c). */
extern "C" void f_0d71f0(void *self)
{
}

struct SubObj;

/* A queued draw of a texture bucket: the sub object, its two state bytes and the next one. */
struct DrawRec {
    SubObj *obj;
    signed char m4;
    signed char m5;
    DrawRec *next;
};

/* A texture bucket: the texture info (null for none), the first and last queued draw. */
struct DrawBucket {
    void *key;
    DrawRec *head;
    DrawRec *tail;
};

/* A texture group's placement record: a type and four floats. */
struct GroupPos {
    int type;
    float f4;
    float f8;
    float f12;
    float f16;
};

/* A texture group's owner: the palette word and the placement. */
struct GroupInfo {
    u32 w0;
    GroupPos *pos;
};

struct DrawGroup {
    GroupInfo *owner;
    int n;
    DrawBucket *b;
    int m12[3];
};

struct DrawGroups {
    DrawGroup *groups;
    int n;
    int cap;
};

/* The course length word of the map manager at D_23c820. */
static inline int MapLen(char *m)
{
    return *(int *)(m + 13004);
}

extern "C" {
u32 *f_0249a0(void *info, u32 *p);
void f_02c93c(float angle);
float floorf(float x);
void f_0d7568(SubObj *obj, DView *view, int b, int mode, u32 **dl, char **cyl, char **scis);
}

/* @draft 0x0d71f8 us f_0d71f8
   WHAT IT DOES: Draws the queued draws of a texture group table. For each group with
   queued draws it writes, before the first bucket that has any, the palette base and call
   commands of the group's owner and its placement commands (none, the texture shift wrapped
   into a unit square from the course length, the reflection turn, or one fixed command), then
   for each bucket the texture select (the texture info's own call list, then a 0x1e command)
   and hands every queued draw to 0x0d7568 with the view and the three output cursors. The
   cursors are copied in and written back at the end.
   DRAFT: 884 bytes against 880, 180 of 220 words aligned. The control flow, the switch
   order and the frame match; retail gives the texture shift pair the other two float
   registers (the first value in f20) and its tail interleaves the two command words, and
   the closing loads of the cursors differ in order. */
extern "C" void f_0d71f8(DrawGroups *tg, DView *view, u32 **pdl, char **pcyl, char **pscis)
{
    u32 *dl = *pdl;
    char *cyl = *pcyl;
    char *scis = *pscis;
    int i;

    for (i = 0; i < tg->n; i++) {
        DrawGroup *g = &tg->groups[i];
        int started = 0;
        int j;
        for (j = 0; j < g->n; j++) {
            DrawBucket *bk = &g->b[j];
            if (bk->head) {
                DrawRec *r;
                if (!started) {
                    u32 w = g->owner->w0;
                    GroupPos *pos = g->owner->pos;
                    *dl++ = ((((int)w >> 24) & 0xf) << 16) | 0x10000000;
                    *dl++ = (w & 0xffffff) | 0x0a000000;
                    if (pos == 0) {
                        *dl++ = 0x4a000000;
                        *dl++ = 0x4b000000;
                        *dl++ = 0xc0000000;
                    } else {
                        switch ((unsigned)pos->type) {
                        case 1: {
                            int len = MapLen(D_23c820);
                            float u = pos->f4 * (float)(len / (int)pos->f12);
                            float v = pos->f8 * (float)(len / (int)pos->f16);
                            u = u - floorf(u);
                            v = v - floorf(v);
                            if (u < 0.0f)
                                u += 1.0f;
                            if (v < 0.0f)
                                v += 1.0f;
                            *dl++ = 0x4a000000 | ((int)Bits(u) >> 8);
                            *dl++ = 0x4b000000 | ((int)Bits(v) >> 8);
                            *dl++ = 0xc0000000;
                            break;
                        }
                        case 2:
                            f_02c93c(pos->f4);
                            *dl++ = 0x4a000000;
                            *dl++ = 0x4b000000;
                            *dl++ = 0xc0000000;
                            break;
                        case 3:
                            *dl++ = 0xc0000301;
                            break;
                        }
                    }
                    started = 1;
                }
                if (bk->key) {
                    dl = f_0249a0(bk->key, dl);
                    *dl++ = 0x1e000001;
                } else {
                    *dl++ = 0x1e000000;
                }
                r = bk->head;
                do {
                    f_0d7568(r->obj, view, r->m4, r->m5, &dl, &cyl, &scis);
                    r = r->next;
                } while (r);
            }
        }
    }
    *pdl = dl;
    *pscis = scis;
    *pcyl = cyl;
}

/* A queued sub object: the draw state at the start, its bounding sphere and box axes and,
   after its spheres, its GE command list (size sixteen byte spheres past +96). */
struct SubObj {
    int key;
    float f4;
    int m8;
    unsigned short size;
    unsigned short flags;
    V4 c;
    V4 ax[4];
    V4 sph[1];
};

/* The map manager's wrap state: a switch word at 124 and the value it selects at 128. */
struct MapWrap {
    char m0[124];
    int on;
    float val;
};

/* Vertices of the four supported vertex types, as the copy sees them. */
struct Vtx24 {
    long long d[3];
};
struct Vtx24b {
    u32 w[6];
};
struct Vtx28 {
    u32 w[7];
};
struct Vtx32 {
    u32 w[8];
};

extern "C" {
extern MapWrap D_23fefc;
extern char D_2543a0[];
int f_0cca30(void *view, void *c, float r);
float f_027ebc(const void *a, const void *b);
u32 *f_0e4c88(void *m, u32 *p);
int iprintf(const char *fmt, ...);
void f_02c984(void *out, u32 *dl, u32 *src, char **outEnd, char **dlEnd);
void f_02b09c(unsigned planes, char *out, char *in, u32 *dl, int n, char **outEnd, u32 **dlEnd);
void f_02a910(unsigned planes, char *out, char *in, u32 *dl, int n, char **outEnd, u32 **dlEnd);
void f_02a22c(unsigned planes, char *out, char *in, u32 *dl, int n, char **outEnd, u32 **dlEnd);
void f_029b58(unsigned planes, char *out, char *in, u32 *dl, int n, char **outEnd, u32 **dlEnd,
              int strips);
}

/* Rounds to the nearest integer (the unit's own conversion, as in src/system/MathFunc.cpp). */
static inline int Round(float f)
{
    int i;
    __asm__("cvt.w.s $f4, %1\n\tmfc1 %0, $f4" : "=r"(i) : "f"(f) : "$f4");
    return i;
}

/* Writes the call of a command list: the base and call commands, and for a two sided object
   the culling toggles and a second call of the same list a word on. */
static inline u32 *CallList(u32 *p, u32 *list, int twice)
{
    *p++ = ((((int)list >> 24) & 0xf) << 16) | 0x10000000;
    *p++ = ((u32)list & 0xffffff) | 0x0a000000;
    if (twice) {
        *p++ = 0xe7000001;
        *p++ = 0xdbfffe05;
        *p++ = (((u32)list + 12) & 0xffffff) | 0x0a000000;
    }
    return p;
}

/* @draft 0x0d7568 us f_0d7568
   WHAT IT DOES: Writes the display list of one queued sub object. It starts with the colour
   scale command from the object's own fade value (or the map manager's when that is set), finds
   the object's command list after its spheres, and for a reflective object (flag set) first
   converts the list to sphere map coordinates (0x02c984) into the cylinder buffer. Then it adds
   the fog, blend and render state commands the globals ask for. A mode 0 object is drawn by a
   call of its list. Otherwise it is tested against the second plane set: if it lies wholly
   inside (or in the sky mode 3) and the globals allow it, the list is called as well; if not,
   the list is walked: its header and vertex type are copied, and for each strip the strip's
   sphere (from the object's sphere array) is tested against the view, and the vertices are
   copied to the scissor buffer with new base, vertex address and draw commands (when the
   strip lies inside) or clipped against the planes by the clipper that fits the vertex type
   (0x19f, 0x1c3, 0x1dc, 0x1df; any other is reported). A two sided object has its commands
   written a second time with the culling toggled. The three cursors are copied in and written
   back at the end.
   DRAFT: 2464 bytes against 2428, 236 of 607 words aligned. Every path is here; the
   prologue, the colour scale word and the list setup match; from there the register
   allocation differs (object in s4, list in s1 against retail's s5 and s2) and the
   out-of-line blocks are placed in another order, so the vertex type blocks and the clipper
   calls match in shape only. */
extern "C" void f_0d7568(SubObj *obj, DView *view, int bf, int mode, u32 **pdl, char **pcyl,
                         char **pscis)
{
    char *scis;
    char *cyl;
    u32 *dl;
    u32 *list;
    float s;
    u32 *a;

    dl = *pdl;
    cyl = *pcyl;
    scis = *pscis;
    int mask;
    int m2;

    if (D_23fefc.on)
        s = D_23fefc.val;
    else
        s = obj->f4;
    *dl++ = 0xc8000000 | ((Round(s * 16.0f) & 0xff) << 16);
    list = (u32 *)((char *)obj + obj->size * 16 + 96);
    if (bf) {
        u32 *conv = (u32 *)cyl;
        f_02c984(scis, conv, list, &scis, &cyl);
        list = conv;
    }
    if (D_25437c)
        *dl++ = D_254380 | 0x5c000000;
    if (D_254384)
        dl = f_0e4c88(D_2543a0, dl);
    if (mode == 0) {
        if (D_254378 & 2)
            dl = CallList(dl, list, obj->flags & 1);
    } else {
        mask = f_0cca30(view, &obj->c, obj->c.w);
        if (mask) {
            int keep = 0;
            int k;
            for (k = 0; k < 4; k++) {
                if (mask & (1 << k)) {
                    V4 *pl = &view->planeB[k];
                    float d32 = f_027ebc(&obj->ax[0], pl);
                    float d64 = f_027ebc(&obj->ax[2], pl);
                    float d48 = f_027ebc(&obj->ax[1], pl);
                    float ext;
                    if (d32 < 0.0f)
                        d32 = -d32;
                    if (d48 < 0.0f)
                        ext = d32 - d48;
                    else
                        ext = d32 + d48;
                    if (d64 < 0.0f)
                        ext = ext - d64;
                    else
                        ext = ext + d64;
                    ext = ext * 0.5f;
                    pl = &view->planeB[k];
                    if (!(ext < f_027ebc(&obj->ax[3], pl) + pl->w)) {
                        keep = -1;
                        break;
                    }
                }
            }
            mask &= keep;
        }
        if ((mask == 0) & (mode != 3)) {
            if (D_254378 & 2) {
                *dl++ = ((((int)list >> 24) & 0xf) << 16) | 0x10000000;
                *dl++ = ((u32)list & 0xffffff) | 0x0a000000;
                if (obj->flags & 1) {
                    *dl++ = 0xe7000001;
                    *dl++ = 0xdbfffe05;
                    *dl++ = (((u32)list + 12) & 0xffffff) | 0x0a000000;
                }
            }
        } else {
            u32 *q = dl;
            u32 vt;
            u32 *c;
            u32 *start;
            int n;
            int sk = 0;
            u32 word;
            int skip;

            q[0] = list[0];
            q[1] = list[1];
            q[2] = list[2];
            vt = list[3];
            q[3] = vt;
            dl = q + 4;
            start = q + 3;
            c = list + 4;
            do {
                word = *c;
                if ((word & 0xff000000) == 0x12000000) {
                    c++;
                    vt = word;
                    *dl++ = word;
                    word = *c;
                }
                a = (u32 *)((word & 0xff0000) << 8 | (c[1] & 0xffffff));
                n = (unsigned char)c[2];
                m2 = -1;
                c += 3;
                skip = 0;
                if (mode != 3) {
                    if (!f_0cc8c8(view, &obj->sph[sk], obj->sph[sk].w))
                        skip = 1;
                    else
                        m2 = f_0cca30(view, &obj->sph[sk], obj->sph[sk].w);
                }
                if (!skip) {
                if (vt == 0x1200019f) {
                    if (m2 == 0) {
                        if (D_254378 & 4) {
                            int i;
                            Vtx24 *o = (Vtx24 *)scis;
                            Vtx24 *in = (Vtx24 *)a;
                            *dl++ = ((((int)scis >> 24) & 0xf) << 16) | 0x10000000;
                            *dl++ = ((u32)scis & 0xffffff) | 0x01000000;
                            *dl++ = n | 0x04040000;
                            for (i = 0; i < n; i++)
                                *o++ = *in++;
                            scis = (char *)o;
                        }
                    } else if (D_254378 & 1) {
                        f_029b58(m2, scis, (char *)a, dl, n, &scis, &dl, (mode ^ 2) != 0);
                    }
                } else if (vt == 0x120001dc) {
                    if (m2 == 0) {
                        if (D_254378 & 4) {
                            int i;
                            Vtx24b *o = (Vtx24b *)scis;
                            Vtx24b *in = (Vtx24b *)a;
                            *dl++ = ((((int)scis >> 24) & 0xf) << 16) | 0x10000000;
                            *dl++ = ((u32)scis & 0xffffff) | 0x01000000;
                            *dl++ = n | 0x04040000;
                            for (i = 0; i < n; i++)
                                *o++ = *in++;
                            scis = (char *)o;
                        }
                    } else if (D_254378 & 1) {
                        f_02a22c(m2, scis, (char *)a, dl, n, &scis, &dl);
                    }
                } else if (vt == 0x120001df) {
                    if (m2 == 0) {
                        if (D_254378 & 4) {
                            int i;
                            Vtx32 *o = (Vtx32 *)scis;
                            Vtx32 *in = (Vtx32 *)a;
                            *dl++ = ((((int)scis >> 24) & 0xf) << 16) | 0x10000000;
                            *dl++ = ((u32)scis & 0xffffff) | 0x01000000;
                            *dl++ = n | 0x04040000;
                            for (i = 0; i < n; i++)
                                *o++ = *in++;
                            scis = (char *)o;
                        }
                    } else if (D_254378 & 1) {
                        f_02a910(m2, scis, (char *)a, dl, n, &scis, &dl);
                    }
                } else if (vt == 0x120001c3) {
                    if (m2 == 0) {
                        if (D_254378 & 4) {
                            int i;
                            Vtx28 *o = (Vtx28 *)scis;
                            Vtx28 *in = (Vtx28 *)a;
                            *dl++ = ((((int)scis >> 24) & 0xf) << 16) | 0x10000000;
                            *dl++ = ((u32)scis & 0xffffff) | 0x01000000;
                            *dl++ = n | 0x04040000;
                            for (i = 0; i < n; i++)
                                *o++ = *in++;
                            scis = (char *)o;
                        }
                    } else if (D_254378 & 1) {
                        f_02b09c(m2, scis, (char *)a, dl, n, &scis, &dl);
                    }
                } else {
                    iprintf("Scissor : Not Support VType : %x %s\n", vt, D_254388);
                }
                }
                sk++;
            } while ((*c >> 24) != 11);
            if (obj->flags & 1) {
                int cnt = dl - start;
                u32 *o;
                *dl++ = 0xe7000001;
                *dl++ = 0xdbfffe05;
                o = dl;
                for (; cnt > 0; cnt--)
                    *o++ = *start++;
                dl = o;
            }
        }
    }
    *pdl = dl;
    *pscis = scis;
    *pcyl = cyl;
}
