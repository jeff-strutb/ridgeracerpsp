/* The course event buffers (retail 0x0ce454 to 0x0cfaf4). The course event data (the global
   Map::CEventDataMgr, one block per data set) lists every event placed along the course with
   its start distance and length. The event list owned by the map manager walks that data as
   the camera moves round the course: two cursors (one ahead in start order, one behind in end
   order) find the events whose range the camera has entered, and each one taken is given a
   Map::CEventBuffer from a ring of 512. Every frame the live buffers are scored by their
   event type's handler; those that want to run are put in a band list sorted by score (a heap
   sort), which the map clipper reads. Buffers whose event has been left behind are released
   and the ring is compacted. */

struct Event {
    short type;
    short m2;
    int flags;
    int start;
    int len;
};

/* The camera: the lap at +572, its distance along the course at +704. */
struct View {
    char m0[572];
    int lap;
    char m576[128];
    float dist;
};

/* The map manager (src/race/MapManager.cpp): its random seed at +13020. */
struct MapMgr {
    char m0[13020];
    unsigned int seed;

    int Rand()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return (int)(seed >> 1) % 32768;
    }
};

namespace Map {

struct Band;

class CEventBuffer {
public:
    CEventBuffer() { Clear(); }
    virtual ~CEventBuffer() {}
    void Clear()
    {
        ev = 0;
        data = 0;
        index = -1;
        count = -1;
        state = 0;
        m30 = 0;
        m24 = 0;
        m12 = 0;
    }

    Event *ev;
    void *data;
    void *m12;
    int count;
    int index;
    int m24;
    short state;
    short m30;
    Band *band;
};

/* One entry of the band list: a buffer that wants to run, and its score. */
struct Band {
    CEventBuffer *buf;
    float dist;
};

/* One set of event data. */
struct Block {
    Block() : count(0), events(0), data(0) {}
    ~Block() {}
    int count;
    Event **events;
    int *data;
    int m12;
    int m16;
    int m20;
    void *table[18];
};

class CEventDataMgr;
}
void f_0cf778(Map::CEventDataMgr *m);
namespace Map {

class CEventDataMgr {
public:
    CEventDataMgr() { f_0cf778(this); }
    virtual ~CEventDataMgr() {}
    Block *First() { return &blk[0]; }
    Block blk[3];
};

}

using namespace Map;

/* The event list kept by the map manager. */
struct EventList {
    CEventBuffer *bufs;
    int size;
    int head;
    int tail;
    Event **events;
    int *data;
    int n;
    void **table;
    unsigned int *active;
    int cur0;
    int cur1;
    short *order;
    Band *bands;

    int Active(int i) { return active[i >> 5] & (1 << (i & 31)); }
    int Prev(int i) { return (i + size - 1) % size; }
};

typedef float (*EvalFn)(CEventBuffer *b);
typedef void (*ReleaseFn)(CEventBuffer *b);

extern "C" {
float *f_0dad68(Event *e, int flag, int arg);
int f_0dae44(Event *e, int arg);
void f_0da41c(Block *b);
void f_0da4c0(Block *b);
void f_0d2ef0(Block *b);
void f_0d37bc(void);
void f_0d3b2c(int a, View *v, void *s);
void f_0d3d94(void);
void f_0e764c(void *p);
void f_0e766c(void *p);
void f_0e7674(void *p);
}

extern MapMgr D_23c820;
extern int D_23f7f8;
extern char D_27eac0[];
extern EvalFn D_1d4a5c[];
extern ReleaseFn D_1d4b7c[];

void f_0ce6c4(EventList *l, CEventDataMgr *m);
void f_0ce944(EventList *l);
void f_0cec9c(EventList *l, View *v, void *a, int b, int pos);
void f_0cee28(EventList *l, int n);
void f_0cefe8(EventList *l, Event *e, int *data, int i);
void f_0cf104(EventList *l, int i);
void f_0cf1c0(EventList *l, int len, int pos);
int f_0cf5e0(EventList *l, int pos);
int f_0cf64c(EventList *l, int pos);
unsigned int f_0cf6d4(EventList *l, Event *e);
void f_0cf778(CEventDataMgr *m);

/* @implements 0x0ce454 us f_0ce454
   WHAT IT DOES: Constructs an empty event list. */
void f_0ce454(EventList *l)
{
    l->bufs = 0;
    l->active = 0;
    l->order = 0;
    l->bands = 0;
    l->size = 0;
}

/* @implements 0x0ce46c us f_0ce46c
   WHAT IT DOES: Allocates the ring of 512 event buffers and the band list, then sets the list
   up for the given event data. */
void f_0ce46c(EventList *l, CEventDataMgr *m)
{
    l->size = 512;
    l->bufs = new CEventBuffer[512];
    l->bands = new Band[l->size];
    l->bands[0].buf = 0;
    f_0ce6c4(l, m);
}

/* @implements 0x0ce520 us f_0ce520
   WHAT IT DOES: Frees the buffers, the active bits, the end order and the band list. */
void f_0ce520(EventList *l)
{
    delete[] l->bufs;
    l->bufs = 0;
    if (l->active)
        delete[] l->active;
    l->active = 0;
    if (l->order)
        delete[] l->order;
    l->order = 0;
    if (l->bands)
        delete[] l->bands;
    l->bands = 0;
}

/* @implements 0x0ce5e8 us f_0ce5e8
   WHAT IT DOES: Decides whether an event is taken on this lap: flag 4 asks the event data,
   flag 0x20000 takes it with the probability stored in the event. */
int f_0ce5e8(EventList *l, Event *e, int lap)
{
    if ((e->flags & 4) && !f_0dae44(e, lap))
        return 0;
    if (e->flags & 0x20000) {
        float *p = f_0dad68(e, 0x20000, 0);
        if ((int)(*p * 32767.0f) < D_23c820.Rand())
            return 0;
    }
    return 1;
}

/* @implements 0x0ce6c4 us f_0ce6c4
   WHAT IT DOES: Takes the first event data block: its events, their data and the type table;
   reallocates the active bits, clears every buffer and empties the ring, and builds the end
   order. */
void f_0ce6c4(EventList *l, CEventDataMgr *m)
{
    int i, n;
    unsigned int *p;

    Block *b = m->First();

    l->n = b->count;
    l->events = b->events;
    l->table = b->table;
    l->data = b->data;
    if (l->active)
        delete[] l->active;
    l->active = 0;
    if (l->order)
        delete[] l->order;
    l->order = 0;
    n = (l->n + 31) / 32;
    if (n == 0)
        n = 1;
    p = new unsigned int[n];
    l->active = p;
    for (i = 0; i < n; i++)
        p[i] = 0;
    for (i = 0; i < l->size; i++)
        l->bufs[i].Clear();
    l->head = l->tail = 0;
    f_0ce944(l);
}

/* @draft 0x0ce7e4 us f_0ce7e4
   WHAT IT DOES: Restarts the list at a position: releases every buffer, places both cursors
   and takes every event whose range holds the position.
   DIFFERS: 3 words after the second cursor call: retail stores the cursor before loading the
   event count (`sw v0,40(s2); lui; lw a1,24(s2)`), ours loads the count first. */
void f_0ce7e4(EventList *l, int lap, int pos)
{
    int i, len, d;
    Event *e;

    i = l->head;
    while (i != l->tail) {
        i = (i + l->size - 1) % l->size;
        f_0cf104(l, i);
    }
    l->head = l->tail = 0;
    l->cur0 = f_0cf5e0(l, pos);
    l->cur1 = f_0cf64c(l, pos);
    len = D_23f7f8;
    for (i = 0; i < l->n; i++) {
        e = l->events[i];
        d = pos - e->start;
        while (d < 0)
            d += len;
        if (e->len < d)
            continue;
        if (f_0ce5e8(l, e, lap - (pos < e->start)))
            f_0cefe8(l, e, &l->data[i], i);
    }
}

/* @implements 0x0ce944 us f_0ce944
   WHAT IT DOES: Builds the end order: the events sorted by where they end, last first. */
void f_0ce944(EventList *l)
{
    int n = l->n;
    int i, j, best;
    unsigned int max;
    int *used;
    unsigned int *ends;

    if (n == 0)
        return;
    l->order = new short[n];
    used = new int[n];
    ends = new unsigned int[n];
    for (i = 0; i < n; i++) {
        used[i] = 0;
        ends[i] = f_0cf6d4(l, l->events[i]);
    }
    for (i = 0; i < n; i++) {
        best = -1;
        max = 0;
        for (j = 0; j < n; j++) {
            if (used[j])
                continue;
            if (ends[j] < max)
                continue;
            max = ends[j];
            best = j;
        }
        l->order[i] = best;
        used[best] = 1;
    }
    if (used)
        delete[] used;
    if (ends)
        delete[] ends;
}

/* @implements 0x0ceaac us f_0ceaac
   WHAT IT DOES: The per frame step: moves both cursors over the events the camera has reached
   (ahead in start order, behind in end order), taking each one not yet active, then scores
   the live buffers. */
void f_0ceaac(EventList *l, View *v, void *a, int b)
{
    int n = l->n;
    int pos, len, lap, k, first, i, d;
    int *cur;
    Event *e;

    if (n == 0)
        return;
    pos = (int)v->dist;
    len = D_23f7f8;
    lap = v->lap;
    for (k = 0; k < 2; k++) {
        if (k == 0) {
            cur = &l->cur0;
            first = l->cur0;
        } else {
            cur = &l->cur1;
            first = l->cur1;
        }
        do {
            if (k == 0)
                i = *cur;
            else
                i = l->order[*cur];
            if (!l->Active(i)) {
                e = l->events[i];
                d = pos - e->start;
                while (d < 0)
                    d += len;
                if (!(d < e->len) && e->len)
                    break;
                if (f_0ce5e8(l, e, k ? lap - (pos < e->start) : lap + (len < pos + (e->start - pos) % len)))
                    f_0cefe8(l, e, &l->data[i], i);
            }
            *cur = (*cur + 1) % n;
        } while (*cur != first);
    }
    f_0cec9c(l, v, a, b, pos);
}

/* Whether the position has gone past an event's range (events of length 0 never end). */
static inline int Passed(Event *e, int pos, int len)
{
    int r = e->len;
    int d;

    if (r != 0) {
        d = pos - e->start;
        while (d < 0)
            d += len;
        if (d <= r)
            r = 0;
    }
    return r;
}

/* @implements 0x0cec9c us f_0cec9c
   WHAT IT DOES: Scores every live buffer with its type's handler; marks those left behind
   for release, lists those that want to run in the band list, then compacts the ring and
   sorts the bands. */
void f_0cec9c(EventList *l, View *v, void *a, int b, int pos)
{
    Band *band = l->bands;
    int i = l->tail;
    int len = D_23f7f8;
    int n = 0;
    CEventBuffer *buf;
    Event *e;
    int d;

    band->buf = 0;
    while (i != l->head) {
        buf = &l->bufs[i];
        e = buf->ev;
        if (Passed(e, pos, len)) {
            buf->state = -1;
        } else {
            buf->count++;
            band->dist = D_1d4a5c[e->type](buf);
            if (band->dist >= 0.0f) {
                band->buf = buf;
                n++;
                buf->band = band;
                band++;
                band->buf = 0;
            } else {
                buf->band = 0;
            }
        }
        i++;
        if (i == l->size)
            i = 0;
    }
    f_0cf1c0(l, len, pos);
    f_0cee28(l, n);
}

/* @draft 0x0cee28 us f_0cee28
   WHAT IT DOES: Sorts the first n bands by score (a heap sort, highest last).
   DIFFERS: register choice only: retail keeps the child offset j*8 in a0 (ours v1) and the
   second phase's element pointer in t3 (ours t2). */
void f_0cee28(EventList *l, int n)
{
    Band *a = l->bands - 1;
    Band t;
    int i, j, k;

    for (k = n / 2; k > 0; k--) {
        i = k;
        t = a[i];
        for (j = k * 2; j <= n; j *= 2) {
            if (j < n && a[j].dist < a[j + 1].dist)
                j++;
            if (a[j].dist <= t.dist)
                break;
            a[i] = a[j];
            i = j;
        }
        a[i] = t;
    }
    while (n >= 2) {
        t = a[n];
        a[n] = a[1];
        n--;
        i = 1;
        for (j = 2; j <= n; j *= 2) {
            if (j < n && a[j].dist < a[j + 1].dist)
                j++;
            if (a[j].dist <= t.dist)
                break;
            a[i] = a[j];
            i = j;
        }
        a[i] = t;
    }
}

/* @implements 0x0cefe8 us f_0cefe8
   WHAT IT DOES: Takes the next buffer of the ring for an event (releasing the oldest when the
   ring is full) and marks the event active. */
void f_0cefe8(EventList *l, Event *e, int *data, int i)
{
    int next = (l->head + 1) % l->size;
    CEventBuffer *b;

    if (next == l->tail) {
        f_0cf104(l, next);
        l->tail = (l->tail + 1) % l->size;
    }
    b = &l->bufs[l->head];
    b->index = i;
    b->count = -1;
    b->m24 = 0;
    b->ev = e;
    l->active[i >> 5] |= 1 << (i & 31);
    b->m12 = l->table[e->type];
    l->head = next;
    b->state = 0;
    b->m30 = 0;
    b->data = data;
}

/* @implements 0x0cf104 us f_0cf104
   WHAT IT DOES: Releases a buffer: lets its type's handler go, clears its event's active bit
   and marks it dead. */
void f_0cf104(EventList *l, int i)
{
    CEventBuffer *b;

    if (l->head == l->tail)
        return;
    b = &l->bufs[i];
    if (b->index >= 0) {
        D_1d4b7c[b->ev->type](b);
        b->ev = 0;
        l->active[b->index >> 5] &= ~(1 << (b->index & 31));
        b->index = -1;
    }
    b->state = -1;
}

/* @draft 0x0cf1c0 us f_0cf1c0
   WHAT IT DOES: Compacts the ring (moving live buffers over dead ones toward the head),
   advances the tail past dead buffers, then moves both cursors back over inactive events that
   are still in reach.
   DIFFERS: retail keeps the compaction loop's index twice (s1 for the slot and the loop test,
   s4 for the next step) and saves s8; ours keeps one, so the frame and every later register
   choice differ. The control flow and the cursor scans agree. */
void f_0cf1c0(EventList *l, int len, int pos)
{
    int i, j, k, cur, best, dist, d;
    Event *e;
    CEventBuffer *s, *t;

    i = l->head;
    while (i != l->tail) {
        j = l->Prev(i);
        i = j;
        if (l->bufs[j].state == -1) {
            f_0cf104(l, j);
            for (d = j; d != l->tail; ) {
                k = d;
                d = l->Prev(k);
                s = &l->bufs[d];
                if (s->state != -1) {
                    if (s->band)
                        s->band->buf = &l->bufs[j];
                    l->bufs[j] = l->bufs[d];
                    l->bufs[d].index = -1;
                    f_0cf104(l, d);
                    break;
                }
                f_0cf104(l, d);
            }
        }
    }
    for (i = l->tail; i != l->head; i = (i + 1) % l->size)
        if (l->bufs[i].state == -1)
            l->tail = (i + 1) % l->size;

    cur = l->cur0;
    e = l->events[cur];
    best = cur;
    dist = (e->start - pos + len) % len;
    if (dist == 0)
        dist = len;
    j = cur;
    for (;;) {
        j = (j + l->n - 1) % l->n;
        if (j == cur)
            break;
        if (l->Active(j))
            continue;
        e = l->events[j];
        if (e->len % len == 0)
            continue;
        if (dist < (e->start - pos + len) % len)
            break;
        best = j;
    }
    l->cur0 = best;

    cur = l->cur1;
    e = l->events[l->order[cur]];
    best = cur;
    dist = (pos + len * 2 - (e->start + e->len)) % len;
    j = cur;
    for (;;) {
        j = (j + l->n - 1) % l->n;
        if (j == cur)
            break;
        k = l->order[j];
        if (l->Active(k))
            continue;
        e = l->events[k];
        if (e->len % len == 0)
            continue;
        d = (pos + len * 2 - (e->start + e->len)) % len;
        if (!(d < dist))
            break;
        best = j;
    }
    l->cur1 = best;
}

/* @implements 0x0cf5e0 us f_0cf5e0
   WHAT IT DOES: Returns the event whose start is the nearest ahead of a position. */
int f_0cf5e0(EventList *l, int pos)
{
    int len = D_23f7f8;
    int min = len;
    int best = 0;
    int i, d;

    for (i = 0; i < l->n; i++) {
        d = (l->events[i]->start + len - pos) % len;
        if (d <= min) {
            min = d;
            best = i;
        }
    }
    return best;
}

/* @implements 0x0cf64c us f_0cf64c
   WHAT IT DOES: Returns the place in the end order of the event whose end is the nearest
   behind a position. */
int f_0cf64c(EventList *l, int pos)
{
    int len = D_23f7f8;
    int min = len + 1;
    int best = 0;
    int i, d;
    Event *e;

    for (i = 0; i < l->n; i++) {
        e = l->events[l->order[i]];
        d = (pos - (e->start + e->len) + len * 2) % len;
        if (d < min) {
            min = d;
            best = i;
        }
    }
    return best;
}

/* @implements 0x0cf6d4 us f_0cf6d4
   WHAT IT DOES: Returns where an event ends, wrapped into the course length. */
unsigned int f_0cf6d4(EventList *l, Event *e)
{
    unsigned int v = e->start + e->len;
    unsigned int len = D_23f7f8;
    while (v >= len)
        v -= len;
    return v;
}

/* @implements 0x0cf70c us f_0cf70c
   WHAT IT DOES: Sets up the event data from its two arguments and loads the first block. */
void f_0cf70c(CEventDataMgr *m, int a, int b)
{
    m->blk[1].m12 = b;
    m->blk[0].m16 = m->blk[0].m12 = a;
    f_0da41c(&m->blk[0]);
}

/* @implements 0x0cf738 us f_0cf738
   WHAT IT DOES: Frees the event data (the first block, three times over). */
void f_0cf738(CEventDataMgr *m)
{
    int i;

    for (i = 0; i < 3; i++)
        f_0da4c0(m->blk);
}

/* @implements 0x0cf778 us f_0cf778
   WHAT IT DOES: Clears the three event data blocks. */
void f_0cf778(CEventDataMgr *m)
{
    int k, j;

    for (k = 0; k < 3; k++) {
        m->blk[k].m12 = 0;
        m->blk[k].m16 = 0;
        m->blk[k].count = 0;
        m->blk[k].events = 0;
        m->blk[k].data = 0;
        for (j = 0; j < 18; j++)
            m->blk[k].table[j] = 0;
    }
}

/* @implements 0x0cf7d4 us f_0cf7d4
   WHAT IT DOES: Nothing. */
void f_0cf7d4(void)
{
}

CEventDataMgr D_25417c;

/* @implements 0x0cf7dc us f_0cf7dc
   WHAT IT DOES: Loads the course event data and starts the event jobs and the course
   objects. */
void f_0cf7dc(int a, int b)
{
    f_0cf70c(&D_25417c, a, b);
    f_0d2ef0(D_25417c.blk);
    f_0e764c(D_27eac0);
}

/* @implements 0x0cf828 us f_0cf828
   WHAT IT DOES: Frees the course event data, the event jobs and the course objects. */
void f_0cf828(void)
{
    f_0cf738(&D_25417c);
    f_0d37bc();
    f_0e766c(D_27eac0);
}

/* @implements 0x0cf85c us f_0cf85c
   WHAT IT DOES: Empties an event list and clears the event data. */
void f_0cf85c(EventList *l)
{
    f_0ce454(l);
    f_0cf778(&D_25417c);
}

/* @implements 0x0cf884 us f_0cf884
   WHAT IT DOES: Allocates an event list over the course event data. */
void f_0cf884(EventList *l, int b)
{
    f_0ce46c(l, &D_25417c);
}

/* @implements 0x0cf8a4 us f_0cf8a4
   WHAT IT DOES: Frees an event list. */
void f_0cf8a4(EventList *l)
{
    f_0ce520(l);
}

/* @implements 0x0cf8c0 us f_0cf8c0
   WHAT IT DOES: Runs an event list's per frame step for a view. */
void f_0cf8c0(EventList *l, int a, View *v)
{
    f_0ceaac(l, v, l, a);
}

/* @implements 0x0cf8e4 us f_0cf8e4
   WHAT IT DOES: Runs the event jobs and the course objects for a view. */
void f_0cf8e4(int a, View *v, void *s)
{
    f_0d3b2c(a, v, s);
    f_0e7674(D_27eac0);
}

/* @implements 0x0cf90c us f_0cf90c
   WHAT IT DOES: Restarts an event list at a view's position. */
void f_0cf90c(EventList *l, View *v)
{
    int lap = v->lap;
    f_0ce7e4(l, lap, (int)v->dist);
}

/* @implements 0x0cf934 us f_0cf934
   WHAT IT DOES: Draws the event jobs. */
void f_0cf934(void)
{
    f_0d3d94();
}

/* @implements 0x0cf950 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs and destroys the course event data. */
/* @implements 0x0cfa10 us _GLOBAL__I_
   WHAT IT DOES: Static construction entry. */
/* @implements 0x0cfa30 us _GLOBAL__D_
   WHAT IT DOES: Static destruction entry. */
/* @implements 0x0cfa50 us _ZN3Map12CEventBufferD1Ev
   WHAT IT DOES: Destroys an event buffer. */
/* @implements 0x0cfa60 us _ZN3Map12CEventBufferD0Ev
   WHAT IT DOES: Destroys and frees an event buffer. */
/* @implements 0x0cfa88 us _ZN3Map13CEventDataMgrD1Ev
   WHAT IT DOES: Destroys the event data. */
/* @implements 0x0cfab4 us _ZN3Map13CEventDataMgrD0Ev
   WHAT IT DOES: Destroys and frees the event data. */
