/* The course event data (retail 0x0da414 to 0x0db2c4): the event list loaded from a course's
   event file, the table of optional event parameters (each present a number of times given by
   a bit field of the event's flags, stored one after another behind the fixed header), the
   lookups, copies and dumps built on it, and the event packer used by replays. */

extern "C" {
int iprintf(const char *fmt, ...);
int f_126f1c(const char *s, ...);
void *memcpy(void *d, const void *s, unsigned int n);
}

struct Vec3 {
    float x, y, z;
};

/* A course event: a fixed header, then its parameters. */
struct Event {
    short type;
    unsigned short m2;
    unsigned int flags;
    int m8;
    int m12;
    Vec3 pos;
    int obj;
    int params[1];
};

/* One kind of optional parameter. */
struct EventParam {
    int key;            /* negative ends the table */
    const char *name;
    int m8[7];
    int type;           /* 0: vector, 1: float, 2 to 4: integers */
    int size;           /* in words */
    unsigned int shift;
    unsigned int mask;  /* the count's bit field in the event flags */
    int m52;
    int offset;         /* where the unpacked event keeps it */
};

extern EventParam D_1d4cfc[];

/* The event list: the events of a loaded event file. */
struct EventList {
    int count;
    Event **events;
    int *work;
};

/* The event file: a count and the offsets of its events, from +16. */
struct EventFile {
    int m0;
    int count;
    int m8[2];
    int offs[1];
};

/* An event unpacked: the header and every parameter at a fixed place (the last of each
   kind). */
struct EventFull {
    int w[61];
};

extern int D_23f7f8;   /* the lap time wrap */
extern EventParam *D_254390;

extern "C" {

int f_0dadf0(Event *e);
int *f_0dad68(Event *e, int key, int i);
void f_0daa80(EventList *l, Event *e);

/* @implements 0x0da414 us f_0da414
   WHAT IT DOES: Returns 0 (no time shift for the packed events). */
int f_0da414()
{
    return 0;
}

/* @implements 0x0da41c us f_0da41c
   WHAT IT DOES: Takes an event file: turns its event offsets into pointers in place, marks
   events whose scene bits are clear but for bit 3 with scene bit 0, and allocates a work
   word per event. With no file the list is empty. */
void f_0da41c(EventList *l, EventFile *f)
{
    if (f == 0) {
        l->count = 0;
        l->events = 0;
        l->work = 0;
        return;
    }
    int n = f->count;
    l->events = (Event **)f->offs;
    l->count = n;
    l->work = new int[n];
    for (int i = 0; i < l->count; i++) {
        Event *e = (Event *)((int)l->events[i] + (int)f);
        l->events[i] = e;
        if ((e->m2 & ~8) == 0)
            e->m2 |= 1;
    }
}

/* @implements 0x0da4c0 us f_0da4c0
   WHAT IT DOES: Frees the work words and empties the list. */
int f_0da4c0(EventList *l)
{
    if (l->work)
        delete[] l->work;
    l->count = 0;
    l->events = 0;
    l->work = 0;
    return 0;
}

/* Whether an event belongs to a group: group 0 holds those without a group parameter. */
static inline int InGroup(Event *e, int group)
{
    if ((group == 0) & (((e->flags >> 19) ^ 1) & 1))
        return 1;
    if ((e->flags & 0x80000) && *f_0dad68(e, 0x80000, 0) == group)
        return 1;
    return 0;
}

/* @draft 0x0da50c us f_0da50c
   WHAT IT DOES: Packs the events of a file that belong to a group (group 0: those without
   a group parameter) into one new block: "EVE", the count, the offsets, then the events.
   DIFFERS: retail reloads the event count only after calls (not on the skip path) and keeps
   the file's offset table and the wrap in the other two stack slots; 616 bytes vs 628. */
int *f_0da50c(EventList *l, EventFile *f, int group)
{
    int shift, wrap, i, count, off;
    unsigned int size;
    int *offs, *buf, *o;
    Event *e;

    if (f == 0)
        return 0;
    size = 16;
    shift = f_0da414();
    wrap = D_23f7f8;
    count = 0;
    offs = f->offs;
    for (i = 0; i < f->count; i++) {
        e = (Event *)(offs[i] + (int)f);
        if (InGroup(e, group)) {
            size += f_0dadf0(e);
            count++;
        }
    }
    off = (count + 3) / 4 * 16;
    size += off;
    size += (size + 15) & ~15;
    buf = new int[size / 4];
    buf[1] = count;
    buf[0] = 0x455645;
    off += 16;
    o = buf + 4;
    for (i = 0; i < f->count; i++) {
        e = (Event *)(offs[i] + (int)f);
        if (InGroup(e, group)) {
            *o = off;
            Event *d = (Event *)((char *)buf + off);
            memcpy(d, e, f_0dadf0(e));
            o++;
            if (shift && d->m8 && d->m12) {
                d->m8 -= 200;
                if (d->m8 < 0)
                    d->m8 += wrap;
                d->m12 += 400;
            }
            off += f_0dadf0(e);
        }
    }
    return buf;
}

/* @draft 0x0da780 us f_0da780
   WHAT IT DOES: Unpacks an event: copies its first 244 bytes, then puts the last of each
   parameter kind at that kind's fixed place.
   DIFFERS: the function map runs this and the packer at 0x0da8a0 together as one function
   (0x0da780, 612 bytes); this one is 288. */
void f_0da780(EventFull *out, Event *e)
{
    *out = *(EventFull *)e;
    int *p = e->params;
    for (EventParam *t = D_1d4cfc; t != D_254390; t++) {
        for (int k = ((e->flags & t->mask) >> t->shift) - 1; k >= 0; k--) {
            switch (t->type) {
            case 0:
                *(Vec3 *)((char *)out + t->offset) = *(Vec3 *)p;
                break;
            case 1:
                *(float *)((char *)out + t->offset) = *(float *)p;
                break;
            case 2:
            case 3:
            case 4:
                *(int *)((char *)out + t->offset) = *p;
                break;
            }
            p += t->size;
        }
    }
}

/* (0x0da8a0, inside the mapped 0x0da780) Packs an unpacked event: the header field by field,
   then every parameter present by the flags, from its fixed place. */
void f_0da8a0(Event *out, EventFull *in)
{
    Event *h = (Event *)in;
    out->flags = h->flags;
    out->pos.x = h->pos.x;
    out->m8 = h->m8;
    out->type = h->type;
    out->m12 = h->m12;
    out->pos.y = h->pos.y;
    out->m2 = h->m2;
    out->pos.z = h->pos.z;
    out->obj = h->obj;
    int *p = out->params;
    for (EventParam *t = D_1d4cfc; t != D_254390; t++) {
        int n = (h->flags & t->mask) >> t->shift;
        for (int k = 0; k < n; k++) {
            switch (t->type) {
            case 0:
                *(Vec3 *)p = ((Vec3 *)((char *)in + t->offset))[k];
                p += 3;
                break;
            case 1:
                *(float *)p = ((float *)((char *)in + t->offset))[k];
                p++;
                break;
            case 2:
            case 3:
            case 4:
                *p = ((int *)((char *)in + t->offset))[k];
                p++;
                break;
            }
        }
    }
}

/* @implements 0x0da9e4 us f_0da9e4
   WHAT IT DOES: Prints every event of the list. */
void f_0da9e4(EventList *l)
{
    f_126f1c("==================================================");
    f_126f1c("\xa5\xa4\xa5\xd9\xa5\xf3\xa5\xc8\xa5\xc7\xa1\xbc\xa5\xbf");
    f_126f1c("==================================================");
    for (int i = 0; i < l->count; i++) {
        iprintf("%d--------------------------------------------------\n", i);
        f_0daa80(l, l->events[i]);
    }
}

/* @implements 0x0daa80 us f_0daa80
   WHAT IT DOES: Prints one event: its header, then every parameter present. */
void f_0daa80(EventList *l, Event *e)
{
    iprintf("    Type:%d\n", e->type);
    iprintf("   Model:%d\n", e->obj);
    iprintf("   Scene:0x%x\n", e->m2);
    iprintf("RzpBegin:%d\n", e->m8);
    iprintf("  RzpEnd:%d\n", e->m12);
    iprintf("   Trans:%f %f %f\n", e->pos.x, e->pos.y, e->pos.z);
    int *p = e->params;
    for (EventParam *t = D_1d4cfc; t != D_254390; t++) {
        for (int k = ((e->flags & t->mask) >> t->shift) - 1; k >= 0; k--) {
            switch (t->type) {
            case 0:
                iprintf("%8s:%f %f %f\n", t->name, ((float *)p)[0], ((float *)p)[1], ((float *)p)[2]);
                break;
            case 1:
                iprintf("%8s:%f\n", t->name, *(float *)p);
                break;
            case 3:
                iprintf("%8s:0x%x\n", t->name, *p);
                break;
            case 2:
            case 4:
                iprintf("%8s:%d\n", t->name, *p);
                break;
            }
            p += t->size;
        }
    }
}

/* @implements 0x0dacb4 us f_0dacb4
   WHAT IT DOES: The event's position (as three floats written to out, which is returned). */
float *f_0dacb4(float *out, Event *e)
{
    out[0] = e->pos.x;
    out[1] = e->pos.y;
    out[2] = e->pos.z;
    return out;
}

/* @implements 0x0dacd4 us f_0dacd4
   WHAT IT DOES: The event's rotation (zero without flag 1). */
float *f_0dacd4(float *out, Event *e)
{
    if (e->flags & 1) {
        Vec3 *p = (Vec3 *)e->params;
        out[0] = p->x;
        out[1] = p->y;
        out[2] = p->z;
    } else {
        out[2] = 0;
        out[1] = 0;
        out[0] = 0;
    }
    return out;
}

/* @implements 0x0dad14 us f_0dad14
   WHAT IT DOES: The event's scale (after the rotation when there is one; one without
   flag 2). */
float *f_0dad14(float *out, Event *e)
{
    if (e->flags & 2) {
        Vec3 *p = (Vec3 *)e->params;
        if (e->flags & 1)
            p = (Vec3 *)&e->params[3];
        out[0] = p->x;
        out[1] = p->y;
        out[2] = p->z;
    } else {
        out[0] = out[1] = out[2] = 1.0f;
    }
    return out;
}

/* @implements 0x0dad68 us f_0dad68
   WHAT IT DOES: The i-th value of the event's parameter of the given key, or 0 when it has
   fewer. */
int *f_0dad68(Event *e, int key, int i)
{
    int *p = e->params;
    for (EventParam *t = D_1d4cfc; t != D_254390; t++) {
        int n = (e->flags & t->mask) >> t->shift;
        if (key & t->mask) {
            if (i < n)
                return p + i * t->size;
            return 0;
        }
        p += n * t->size;
    }
    return 0;
}

/* @implements 0x0dadf0 us f_0dadf0
   WHAT IT DOES: The event's size in bytes. */
int f_0dadf0(Event *e)
{
    int size = 32;
    for (EventParam *t = D_1d4cfc; t != D_254390; t++)
        size += ((e->flags & t->mask) >> t->shift) * t->size * 4;
    return size;
}

/* @implements 0x0dae44 us f_0dae44
   WHAT IT DOES: Whether the event is active on a lap, by its lap parameter: 100 even laps,
   0 odd laps, -1000 from lap 0 on, 1000 before it, a negative n every lap but -n-1,
   otherwise lap n-1 only. */
int f_0dae44(Event *e, int lap)
{
    int v = *f_0dad68(e, 4, 0);
    int odd = lap & 1;
    if (v == 100)
        return odd == 0;
    if (v == 0)
        return odd;
    if (v == -1000)
        return lap >= 0;
    if (v == 1000)
        return lap < 0;
    if (v < 0)
        return lap != ~v;
    return lap == v - 1;
}

}

/* Animation data: a header, its first frame table and the frame and key tables, given as
   offsets from the base. */
struct AnimHdr {
    unsigned short flags;   /* 2: per record off switch, 4: keyed by frame, 8: by table */
    short m2;
    short m4;
    unsigned short frameSize;
    int m8;
    unsigned int mode;      /* top 4 bits: frame divider */
};

struct AnimRec {
    int m0;
    unsigned char kind;
    char m5;
    char m6;
    unsigned char flags;    /* 2: off, 4: still */
    int start;
    int still;
};

struct AnimTab {
    int m0[3];
    int stride;
    unsigned int n;
    int m20[11];
    unsigned int w[1];
};

struct AnimData {
    AnimHdr *hdr;
    int *head;
    AnimRec *recs;
    char *b;
    AnimTab *tab;
};

extern int D_1d547c[];  /* the frame size of each record kind */

extern "C" {

/* @implements 0x0daf30 us f_0daf30
   WHAT IT DOES: Sets a parameter block up from its data. */
void f_0daf30(AnimData *pb, char *d)
{
    int *h = (int *)(d + 32);
    pb->recs = (AnimRec *)(d + h[0]);
    pb->b = d + h[1];
    pb->hdr = (AnimHdr *)d;
    pb->head = h;
    pb->tab = (AnimTab *)(d + h[2]);
}

/* @draft 0x0daf64 us f_0daf64
   WHAT IT DOES: The data of record idx at a frame: none when the record is switched off;
   from the frame table (a word per step: offset, and a top byte saying the step is
   continuous); else the still frame or the record's frames laid out by frame size.
   DIFFERS: retail reloads the header flags after the switch-off test and splits the frame
   table offset into two arms; register choice differs throughout. */
char *f_0daf64(AnimData *pb, unsigned int frame, int idx)
{
    AnimHdr *h = pb->hdr;
    if ((h->flags & 2) && (pb->recs[idx].flags & 2))
        return 0;
    if (h->flags & 8) {
        AnimTab *t = pb->tab;
        unsigned int q = frame / t->n;
        unsigned int m = frame % t->n;
        unsigned int w = t->w[q + idx * t->stride];
        if (w & 0xff000000)
            return (char *)t + ((w & 0xffffff) + D_1d547c[pb->recs[idx].kind] * m);
        return (char *)t + (w & 0xffffff);
    }
    if (h->flags & 4) {
        if (frame) {
            if (!(pb->recs[idx].flags & 4))
                return (char *)pb->tab + (pb->head[3] + (frame - 1) * h->frameSize + pb->recs[idx].start);
            frame = 0;
        }
    }
    return (char *)pb->tab + (frame * pb->head[3] + pb->recs[idx].still);
}

/* The frame scaled by the header's divider. */
static inline int Scaled(AnimHdr *h, int frame)
{
    unsigned int k = h->mode >> 28;
    if (k >= 2)
        frame = frame / (int)k;
    return frame;
}

/* @draft 0x0db0d0 us f_0db0d0
   WHAT IT DOES: The same with the frame first divided by the header's divider.
   DIFFERS: as 0x0daf64; 464 bytes vs 500. */
char *f_0db0d0(AnimData *pb, int frame, int idx)
{
    AnimHdr *h = pb->hdr;
    if ((h->flags & 2) && (pb->recs[idx].flags & 2))
        return 0;
    if (h->flags & 8) {
        frame = Scaled(h, frame);
        AnimTab *t = pb->tab;
        unsigned int q = (unsigned int)frame / t->n;
        unsigned int m = (unsigned int)frame % t->n;
        unsigned int w = t->w[q + idx * t->stride];
        if (w & 0xff000000)
            return (char *)t + ((w & 0xffffff) + D_1d547c[pb->recs[idx].kind] * m);
        return (char *)t + (w & 0xffffff);
    }
    if (h->flags & 4) {
        if (frame) {
            if (!(pb->recs[idx].flags & 4))
                return (char *)pb->tab + (pb->head[3] + (Scaled(h, frame) - 1) * h->frameSize + pb->recs[idx].start);
            frame = 0;
        }
    }
    return (char *)pb->tab + (Scaled(h, frame) * pb->head[3] + pb->recs[idx].still);
}

}

/* @implements 0x0daec8 us __static_initialization_and_destruction_0
   WHAT IT DOES: Finds the end of the parameter table at start up. */
/* @implements 0x0daf10 us _GLOBAL__I_
   WHAT IT DOES: Static initialisation of this object file. */

/* The end of the parameter table, found at start up. */
static inline EventParam *ParamEnd()
{
    EventParam *p = D_1d4cfc;
    while (p->key >= 0)
        p++;
    return p;
}

EventParam *D_254390 = ParamEnd();
