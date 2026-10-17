/* The map clipper (retail 0x0d54c8 to 0x0d5d80): one per course part. Each frame it finds the
   course section and grid cell the camera is in, builds a list of draw commands for the
   parts of the course visible from there, and later hands that list to the drawing code.
   Debug flags shared by every clipper sit in .bss beside it. */

struct ClipEvents;

extern "C" {
unsigned int sceKernelGetSystemTimeLow(void);
int f_126f1c(const char *fmt, ...);
int f_0cc8c8(void *view, void *box, float r);
void f_0d710c(void *clip, short *list, void *out);
int f_0d5fd8(ClipEvents *events, int dist, int *out, int start, float x, float z, int def);
int f_0d6280(void *clip, short *list, int arg, void *view, int mode, int marked);
}

/* The camera: its position at +688, its distance along the course at +704. */
struct Vec4 {
    float x, y, z, w;
};

struct ClipView {
    char m0[688];
    Vec4 pos;
    float dist;
};

/* The course event data, as the clipper reads it (src/race/CourseEvents.cpp). */
struct ClipBox {
    float x, y, z, r;
};

struct ClipObject {
    char *name;
    int m4[2];
    int type;           /* 1: drawn inside a group of its own */
    void *data;
    int nBoxes;
    ClipBox *boxes;
    int m28[4];
    float dist;
    int m48[2];
    int loaded;
    int m60;
};

struct ClipRef {
    int obj;
    int m4;
};

struct ClipGroup {
    int m0[4];
    int *first;         /* object references drawn first, ended by -1 */
    int *inner;         /* those drawn inside a type 1 run */
    int *boxed;         /* those drawn box by box */
    char **runs;        /* per cell: (skip, count) box runs per object, ended by 255 */
};

struct ClipHeader {
    int m0[12];
    int nObjects;
};

struct ClipEvents {
    ClipHeader *header;
    ClipObject *objs;
    int m8;
    ClipRef *firstRefs;
    ClipRef *innerRefs;
    ClipRef *boxedRefs;
    ClipRef *order;
    int m28[2];
    ClipGroup *groups;
    int group;
};

/* The fog bands of the shading setup: a nonzero tag and a start distance, ended by tag 0. */
struct FogBand {
    int tag;
    float dist;
};

struct ClipShade {
    int m0[12];
    FogBand *bands;
};

extern signed char D_254370;
extern signed char D_254371;      /* nonzero: keep the last section and cell */
extern signed char D_254372;
extern ClipEvents *D_254374;      /* the course event data */

class CMapClip {
public:
    CMapClip();
    ~CMapClip();
    void Init(ClipShade *shade);
    void Update(ClipView *view);
    void Build(int cell, ClipView *view);
    int Draw(ClipView *view, int mode, int arg, int flag);

    int section;
    int cell;
    ClipShade *shade;
    int buildTime;
    int drawTime;
    short list[2000];
    int m4020[4];
    short *mark;
    int m4040[2];
};

/* @implements 0x0d54c8 us _ZN8CMapClipC2Ev
   WHAT IT DOES: Base object constructor: nothing to do. */
/* @implements 0x0d54d0 us _ZN8CMapClipC1Ev
   WHAT IT DOES: Complete object constructor: the same. */
CMapClip::CMapClip()
{
}

/* @implements 0x0d54d8 us _ZN8CMapClipD2Ev
   WHAT IT DOES: Base object destructor: nothing to do. */
/* @implements 0x0d54e0 us _ZN8CMapClipD1Ev
   WHAT IT DOES: Complete object destructor: the same. */
CMapClip::~CMapClip()
{
}

/* @implements 0x0d54e8 us _ZN8CMapClip4Init
   WHAT IT DOES: Takes the shading setup, starts at section and cell 0, and resets the shared
   debug flags. */
void CMapClip::Init(ClipShade *s)
{
    shade = s;
    cell = 0;
    section = 0;
    D_254372 = -1;
    D_254370 = 0;
    D_254371 = 0;
}

/* @implements 0x0d5514 us _ZN8CMapClip6Update
   WHAT IT DOES: Unless the section is frozen, locates the camera's section and cell from its
   distance and position; then builds the draw list for that cell and finishes it, timing the
   locate and build. */
void CMapClip::Update(ClipView *view)
{
    buildTime = sceKernelGetSystemTimeLow();
    if (!D_254371) {
        Vec4 p = view->pos;
        Vec4 q = view->pos;
        cell = f_0d5fd8(D_254374, (int)view->dist, &section, section, p.x, q.z, cell);
    }
    buildTime = sceKernelGetSystemTimeLow() - buildTime;
    Build(cell, view);
    f_0d710c(this, list, m4020);
}

/* @draft 0x0d55ec us _ZN8CMapClip5Build
   WHAT IT DOES: Builds the draw list for a grid cell. The list is 16-bit words: commands
   (0x8000 and up) and indices. First every object the cell's group draws whole (each with all
   its boxes when loaded), then every object drawn box by box (the boxes the camera can see),
   then the course objects in order: entering and leaving the inner objects around type 1
   runs, opening a fog band whenever an object lies beyond the next band, and listing the boxes
   of each object's runs for this cell (every box in group 3, otherwise those in view). The
   point where objects first lie at 3001 or more is marked for the far pass. Overflowing the
   2000-word list stops with a message.
   DIFFERS: retail keeps the list pointer in a register from the start (the first stores are
   not folded into offsets from `this`) and has a 112-byte frame; the order and spills differ
   throughout. */
void CMapClip::Build(int c, ClipView *view)
{
    ClipEvents *ev = D_254374;
    short *p = list;
    FogBand *band = 0;
    char *run = ev->groups[ev->group].runs[c];
    int *ref;
    short n;
    int prev;
    int k;

    if (shade)
        band = shade->bands;
    ref = ev->groups[ev->group].first;
    *p++ = 0x8006;
    n = 0;
    *p++ = 0;
    mark = 0;
    if (*ref >= 0) {
        *p++ = 0x8000;
        do {
            ClipRef *r = &ev->firstRefs[*ref];
            ClipObject *o = &ev->objs[r->obj];
            int i;
            *p++ = 0x8004;
            *p++ = r->obj;
            if (o->loaded)
                for (i = 0; i < o->nBoxes; i++)
                    *p++ = i;
            ref++;
        } while (*ref >= 0);
    }
    ref = ev->groups[ev->group].boxed;
    if (*ref >= 0) {
        *p++ = 0x8001;
        do {
            ClipRef *r = &ev->boxedRefs[*ref];
            ClipObject *o = &ev->objs[r->obj];
            int i;
            *p++ = 0x8004;
            *p++ = r->obj;
            for (i = 0; i < o->nBoxes; i++) {
                ClipBox *b = &o->boxes[i];
                if (f_0cc8c8(view, b, b->r) && o->loaded)
                    *p++ = i;
            }
            ref++;
        } while (*ref >= 0);
    }
    *p++ = 0x8002;
    prev = -1;
    for (k = 0; k < ev->header->nObjects; k++) {
        ClipRef *r = &ev->order[k];
        ClipObject *o = &ev->objs[r->obj];
        ClipBox *boxes = o->boxes;
        int type = o->type;
        int bi;

        if (prev == 1 && type != 1) {
            int *q = ev->groups[ev->group].inner;
            if (*q >= 0) {
                *p++ = 0x8000;
                do {
                    ClipRef *r2 = &ev->innerRefs[*q];
                    ClipObject *o2 = &ev->objs[r2->obj];
                    *p++ = 0x8004;
                    q++;
                    *p++ = r2->obj;
                    if (o2->loaded)
                        *p++ = 0;
                } while (*q >= 0);
                *p++ = 0x8005;
                *p++ = 0;
                *p++ = 0x8002;
            }
        }
        if (band && band->tag && band->dist < o->dist) {
            *p++ = 0x8006;
            *p++ = 1;
            *p++ = 0x8003;
            do {
                if (o->dist <= band->dist)
                    break;
                if (!mark && 3001.0f <= band->dist) {
                    *p++ = 0x8008;
                    mark = p;
                    *p++ = 0x8006;
                    *p++ = 1;
                    *p++ = 0x8003;
                }
                band++;
                *p++ = n++;
            } while (band->tag);
            *p++ = 0x8006;
            *p++ = 0;
            *p++ = 0x8005;
            *p++ = 0;
            *p++ = 0x8002;
        }
        prev = type;
        bi = 0;
        if ((unsigned char)*run != 255) {
            if (!mark && 3001.0f <= o->dist) {
                *p++ = 0x8008;
                mark = p;
                *p++ = 0x8006;
                *p++ = 0;
                *p++ = 0x8002;
            }
            *p++ = 0x8004;
            *p++ = r->obj;
        }
        while ((unsigned char)*run != 255) {
            int j;
            bi += (unsigned char)*run++;
            for (j = 0; j < (unsigned char)*run; j++, bi++) {
                ClipBox *b = &boxes[bi];
                if (ev->group == 3) {
                    if (ev->objs[r->obj].loaded)
                        *p++ = bi;
                } else if (ev->objs[r->obj].loaded) {
                    if (f_0cc8c8(view, b, b->r))
                        *p++ = bi;
                }
            }
            run++;
        }
        run++;
    }
    if (band && band->tag) {
        *p++ = 0x8006;
        *p++ = 1;
        *p++ = 0x8003;
        do {
            if (!mark && 3001.0f <= band->dist) {
                *p++ = 0x8008;
                mark = p;
                *p++ = 0x8006;
                *p++ = 1;
                *p++ = 0x8003;
            }
            band++;
            *p++ = n++;
        } while (band->tag);
    }
    *p++ = 0x8007;
    if (p - list >= 2000) {
        f_126f1c("MapClip Buffer overflow");
        __asm__ volatile ("break");
    }
}

/* @implements 0x0d5cbc us _ZN8CMapClip4Draw
   WHAT IT DOES: Draws the list (from the marked point when asked, which does nothing when no
   point was marked and returns the argument), timing it. */
int CMapClip::Draw(ClipView *view, int mode, int arg, int flag)
{
    int r;

    drawTime = sceKernelGetSystemTimeLow();
    if (!flag)
        r = f_0d6280(this, list, arg, view, mode, 0);
    else if (mark)
        r = f_0d6280(this, mark, arg, view, mode, 1);
    else
        r = arg;
    drawTime = sceKernelGetSystemTimeLow() - drawTime;
    return r;
}
