/* The delayed sound start queue (retail 0x10e788 to 0x10ed74): up to 64 pending sound
   requests, each started through the voice code (0x1104ec) when its delay runs out, plus the
   immediate start path that copies a request, reads the voice's length and starts it while
   fewer than 16 starts are in progress. One global queue (D_280a90) is reached through
   D_280a8c while it is open. Error 0x80000000 means the queue is closed, already open or the
   request is invalid. */

/* A sound request (36 bytes). */
struct SoundReq {
    int state;              /* -1 free, 0 pending */
    unsigned short idx;
    unsigned short bank;
    int key;
    int m12;
    float vol;
    short m20;
    short pad22;
    int delay;              /* ticks left */
    short m28;
    short pad30;
    int m32;
};

/* A queued request and the key it was queued under. */
struct SoundQEntry {
    SoundReq r;
    int qkey;
};

/* The voice a request is started on. */
struct SoundVoice {
    int id;                 /* -1 or 255 when none */
    int kind;               /* 0 any, 2 or 3 by the start's flag */
    int m8;
};

/* What the voice code reports about a sound. */
struct SoundInfo {
    int m0;
    int m4;
    int length;
};

extern "C" {
int f_1104ec(unsigned short bank, unsigned short idx, SoundReq *r);
int f_110390(unsigned short bank, unsigned short idx, SoundReq *r);
int f_11041c(unsigned short bank, unsigned short idx, SoundInfo *info);
extern int D_281494; /* starts in progress */
}

class CSoundDelayQueue {
public:
    SoundQEntry e[64];
    int count;

    CSoundDelayQueue();
    ~CSoundDelayQueue() {}
    int f_10e7a8(int n);
    int f_10e7d8();
    int f_10e7e8(int dt);
    int f_10e898(SoundReq *r);
    int f_10e8e4();
    int f_10e918(int key);
    int f_10e958(SoundReq *r);
    int f_10e9e8(SoundReq *r);
};

CSoundDelayQueue *D_280a8c;
CSoundDelayQueue D_280a90;

extern "C" {
/* @implements 0x10e788 us f_10e788
   WHAT IT DOES: Does nothing and returns 0. */
int f_10e788(void)
{
    return 0;
}
}

/* @implements 0x10e790 us _ZN16CSoundDelayQueueC2Ev
   WHAT IT DOES: Constructs the queue closed (no entries). */
/* @implements 0x10e79c us _ZN16CSoundDelayQueueC1Ev
   WHAT IT DOES: The complete-object form of the same constructor. */
CSoundDelayQueue::CSoundDelayQueue()
{
    count = -1;
}

/* @implements 0x10e7a8 us _ZN16CSoundDelayQueue8f_10e7a8Ei
   WHAT IT DOES: Opens the queue with n free entries. */
int CSoundDelayQueue::f_10e7a8(int n)
{
    int i;

    for (i = 0; i < n; i++)
        e[i].r.state = -1;
    count = n;
    return 0;
}

/* @implements 0x10e7d8 us _ZN16CSoundDelayQueue8f_10e7d8Ev
   WHAT IT DOES: Closes the queue. */
int CSoundDelayQueue::f_10e7d8()
{
    count = -1;
    return 0;
}

/* @implements 0x10e7e8 us _ZN16CSoundDelayQueue8f_10e7e8Ei
   WHAT IT DOES: Counts every pending request down by dt ticks; one whose delay runs out is
   started (0x1104ec) with its queue key and freed. */
int CSoundDelayQueue::f_10e7e8(int dt)
{
    int i;

    for (i = 0; i < count; i++) {
        SoundQEntry *q = &e[i];
        if (q->r.state == -1)
            continue;
        int t = q->r.delay - dt;
        if (t > 0) {
            q->r.delay = t;
        } else {
            q->r.delay = 0;
            q->r.key = q->qkey;
            f_1104ec(q->r.bank, q->r.idx, &q->r);
            q->r.state = -1;
        }
    }
    return 0;
}

/* @implements 0x10e898 us _ZN16CSoundDelayQueue8f_10e898EP8SoundReq
   WHAT IT DOES: Drops every pending request with r's key. */
int CSoundDelayQueue::f_10e898(SoundReq *r)
{
    int i;

    for (i = 0; i < count; i++)
        if (e[i].r.state != -1 && e[i].r.key == r->key)
            e[i].r.state = -1;
    return 0;
}

/* @implements 0x10e8e4 us _ZN16CSoundDelayQueue8f_10e8e4Ev
   WHAT IT DOES: Drops every request. */
int CSoundDelayQueue::f_10e8e4()
{
    int i;

    for (i = 0; i < count; i++)
        e[i].r.state = -1;
    return 0;
}

/* @implements 0x10e918 us _ZN16CSoundDelayQueue8f_10e918Ei
   WHAT IT DOES: Returns how many pending requests have the key. */
int CSoundDelayQueue::f_10e918(int key)
{
    int i;
    int n = 0;

    for (i = 0; i < count; i++)
        if (e[i].r.state != -1)
            n += e[i].r.key == key;
    return n;
}

/* @implements 0x10e958 us _ZN16CSoundDelayQueue8f_10e958EP8SoundReq
   WHAT IT DOES: Queues a copy of r in the first free entry, pending, under r's key; returns
   -1 when the queue is full. */
int CSoundDelayQueue::f_10e958(SoundReq *r)
{
    int i;

    for (i = 0; i < count; i++) {
        if (e[i].r.state == -1) {
            e[i].r = *r;
            e[i].r.state = 0;
            e[i].qkey = r->key;
            return 0;
        }
    }
    return -1;
}

/* @implements 0x10e9e8 us _ZN16CSoundDelayQueue8f_10e9e8EP8SoundReq
   WHAT IT DOES: Updates the first pending request queued under r's key with r's volume and
   the two settings at +20 and +28. */
int CSoundDelayQueue::f_10e9e8(SoundReq *r)
{
    int i;

    for (i = 0; i < count; i++) {
        if (e[i].r.state == 0 && e[i].qkey == r->key) {
            e[i].r.vol = r->vol;
            e[i].r.m20 = r->m20;
            e[i].r.m28 = r->m28;
            break;
        }
    }
    return 0;
}

extern "C" {
/* @implements 0x10ea3c us f_10ea3c
   WHAT IT DOES: Opens the global queue with n entries; 0x80000000 if it is already open. */
int f_10ea3c(int n)
{
    if (D_280a8c)
        return 0x80000000;
    D_280a8c = &D_280a90;
    D_280a90.f_10e7a8(n);
    return 0;
}

/* @implements 0x10ea80 us f_10ea80
   WHAT IT DOES: Closes the global queue; 0x80000000 if it is not open. */
int f_10ea80(void)
{
    if (!D_280a8c)
        return 0x80000000;
    int r = D_280a8c->f_10e7d8();
    D_280a8c = 0;
    return r;
}

/* @implements 0x10eac8 us f_10eac8
   WHAT IT DOES: Advances the global queue by dt ticks. */
int f_10eac8(int dt)
{
    return D_280a8c->f_10e7e8(dt);
}

/* @implements 0x10eaec us f_10eaec
   WHAT IT DOES: Queues a delayed request on the global queue; 0x80000000 if it has no
   delay. */
int f_10eaec(SoundReq *r)
{
    if (!r->delay)
        return 0x80000000;
    return D_280a8c->f_10e958(r);
}

/* @implements 0x10eb28 us f_10eb28
   WHAT IT DOES: Starts request q on a voice now: rejects a missing voice or one of the
   wrong kind for the flag, builds a copy of the request for that voice, takes the sound's
   length off its delay and starts it (0x1104ec) while fewer than 16 starts are in progress,
   keeping the start's setting at +12. Returns the start's result or 0x80000000. */
int f_10eb28(SoundReq *q, SoundVoice *v, int flag)
{
    int ret = 0x80000000;
    SoundReq r;
    SoundInfo info;

    if (v->id != -1 && v->id != 255) {
        if (v->kind == 0 || v->kind == (flag ? 2 : 3)) {
            r.bank = q->bank;
            r.idx = v->id;
            r.vol = q->vol;
            r.m20 = q->m20;
            r.m28 = q->m28;
            r.m12 = q->m12;
            r.key = q->key;
            r.delay = v->m8;
            f_110390(q->bank, v->id, &r);
            f_11041c(q->bank, q->idx, &info);
            r.delay -= info.length;
            D_281494++;
            if (D_281494 < 16) {
                ret = f_1104ec(q->bank, v->id, &r);
                q->m12 = r.m12;
            }
            D_281494--;
        }
    }
    return ret;
}

/* @implements 0x10ec60 us f_10ec60
   WHAT IT DOES: Updates a pending request on the global queue (0x10e9e8). */
int f_10ec60(SoundReq *r)
{
    return D_280a8c->f_10e9e8(r);
}

/* @implements 0x10ec84 us f_10ec84
   WHAT IT DOES: Drops the global queue's requests with r's key. */
int f_10ec84(SoundReq *r)
{
    return D_280a8c->f_10e898(r);
}

/* @implements 0x10eca8 us f_10eca8
   WHAT IT DOES: Drops every request on the global queue. */
int f_10eca8(void)
{
    return D_280a8c->f_10e8e4();
}

/* @implements 0x10ecc8 us f_10ecc8
   WHAT IT DOES: Returns how many requests on the global queue share r's key. */
int f_10ecc8(SoundReq *r)
{
    return D_280a8c->f_10e918(r->key);
}
}

/* @implements 0x10ecf0 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global queue at start up. */
/* @implements 0x10ed34 us _GLOBAL__I
   WHAT IT DOES: The start up entry for this file's static data. */
/* @implements 0x10ed54 us _GLOBAL__D
   WHAT IT DOES: The shutdown entry for this file's static data. */
