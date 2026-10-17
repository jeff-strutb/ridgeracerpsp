/* The radio DJ speech queue object file (retail 0x0f7acc to 0x0f8610; its debug prints say
   "RadioQue"). The queue holds up to 32 nodes, each a run of up to 8 scripts to be spoken
   together, in a circular doubly linked list ordered by priority and age. A new run is first
   staged, then added on the next update, replacing the least important node when the queue
   is full. Each update also counts down the nodes' wait times, drops nodes whose time ran out,
   re-sorts the list and selects the first node whose start delay has passed. */

int f_093f90(const char *fmt, ...);

extern "C" {
int f_0f6b90(void);
}

namespace Radio {

/* A script entry of the DJ's script tables. */
struct Ent {
    unsigned short m0;   /* table */
    short m2;            /* script */
    int m4[5];
    int m24;             /* wait time */
    int m28;             /* start delay */
};

/* A script table's attributes. */
struct Tab {
    signed char pri;       /* priority: the smaller, the more important */
    unsigned char flags;   /* bit 1: drops queued runs of lower priority */
};

/* A script's play record. */
struct Rec {
    unsigned short v[4];
};

/* One script of a node. */
struct Item {
    Rec rec;
    Ent *ent;
    Tab *tab;
    int b;
};

/* A queue node. */
struct Node {
    Item e[8];
    int wait;              /* +160: frames (x16) left before the run is dropped */
    int delay;             /* +164: frames (x16) left before the run may start */
    unsigned short n;      /* +168: number of scripts */
    unsigned int serial;   /* +172: order of addition */
    Node *prev;            /* +176 (0 while the node is free) */
    Node *next;            /* +180 */
};

class CQue {
public:
    CQue();
    ~CQue();
    void f_0f7b6c(int stop);
    Node *f_0f7bd0();
    Ent *f_0f7be8(int i);
    int f_0f7c44();
    Node *f_0f7c5c(int node);
    Ent *f_0f7cc4(int node, int i);
    int f_0f7d40(int node);
    int f_0f7da8(Ent **ents, Rec *recs, unsigned short n, Tab *t, int b);
    int f_0f7f00();
    void f_0f7f50();
    int f_0f7f8c(short max);
    int f_0f7ff4();
    int f_0f8000();
    int f_0f80c8();
    int f_0f82c0();
    int f_0f8318(Node *p);
    int f_0f83a8();
    void f_0f8560();
    int f_0f8568(signed char pri);

    short m0;          /* queue length limit */
    int m4;            /* nodes queued */
    unsigned int m8;   /* serial counter */
    Node m12[32];
    Node m5900;        /* the staged run */
    Node *m6084;       /* the list's head */
    Node *m6088;       /* the selected node */
};

/* @implements 0x0f7acc us _ZN5Radio4CQueC2Ev
   WHAT IT DOES: Makes an empty queue of 32 nodes (base object constructor). */
/* @implements 0x0f7b14 us _ZN5Radio4CQueC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CQue::CQue()
{
    m0 = 32;
    m4 = 0;
    m8 = 0;
    for (int i = 0; i < 32; i++) {
        m12[i].prev = 0;
        m12[i].next = 0;
        m12[i].serial = 0;
    }
    m6084 = &m12[0];
    m6088 = 0;
    m5900.n = 0;
}

/* @implements 0x0f7b5c us _ZN5Radio4CQueD2Ev
   WHAT IT DOES: Nothing (base object destructor). */
/* @implements 0x0f7b64 us _ZN5Radio4CQueD1Ev
   WHAT IT DOES: Nothing (complete object destructor). */
CQue::~CQue()
{
}

/* @implements 0x0f7b6c us f_0f7b6c
   WHAT IT DOES: The per frame update: drops the selection, adds the staged run, counts the
   wait times down unless stopped, re-sorts the list and selects the next node to play. */
void CQue::f_0f7b6c(int stop)
{
    m6088 = 0;
    f_0f83a8();
    f_0f8560();
    if (!stop)
        f_0f8000();
    f_0f80c8();
    f_0f82c0();
}

/* @implements 0x0f7bd0 us f_0f7bd0
   WHAT IT DOES: The selected node, or 0. */
Node *CQue::f_0f7bd0()
{
    Node *p = m6088;
    if (!p)
        return 0;
    return p;
}

/* @implements 0x0f7be8 us f_0f7be8
   WHAT IT DOES: Script i's entry of the selected node; 0 with a message if i is out of range. */
Ent *CQue::f_0f7be8(int i)
{
    Node *p = m6088;
    if (!p)
        return 0;
    if (i < 0 || i >= p->n) {
        f_093f90("RadioQue: GetSelectTableAttr Failed! Invalid NodeNo:%d\n", i);
        return 0;
    }
    return p->e[i].ent;
}

/* @implements 0x0f7c44 us f_0f7c44
   WHAT IT DOES: The number of scripts of the selected node, or -1. */
int CQue::f_0f7c44()
{
    Node *p = m6088;
    if (!p)
        return -1;
    return p->n;
}

/* @draft 0x0f7c5c us f_0f7c5c
   REMAINING DIFFERENCE: retail keeps the result in a3 apart from the walked pointer (v1),
   restoring the zero after the print call; here the two share one register. The result
   variable's lifetime across the print call is not yet matched.
   WHAT IT DOES: The node at a position of the list; 0 when the queue is empty or the position
   is out of range. */
Node *CQue::f_0f7c5c(int node)
{
    Node *r;
    if (m4 > 0) {
        Node *p = m6084;
        if (node < 0 || node >= m0) {
            f_093f90("RadioQue: GetPlayParam Failed! Invalid NodeNo:%d\n", node);
            r = 0;
        } else {
            for (int i = 0; i < node; i++)
                p = p->next;
            r = p;
        }
    } else {
        r = 0;
    }
    return r;
}

/* @draft 0x0f7cc4 us f_0f7cc4
   REMAINING DIFFERENCE: the same result register difference as f_0f7c5c.
   WHAT IT DOES: Script i's entry of the node at a position of the list, or 0. */
Ent *CQue::f_0f7cc4(int node, int i)
{
    Ent *r;
    if (m4 > 0) {
        Node *p = m6084;
        if (node < 0 || node >= m0) {
            f_093f90("RadioQue: GetTableAttr Failed! Invalid NodeNo:%d\n", node);
            r = 0;
        } else {
            for (int k = 0; k < node; k++)
                p = p->next;
            r = p->e[i].ent;
        }
    } else {
        r = 0;
    }
    return r;
}

/* @draft 0x0f7d40 us f_0f7d40
   REMAINING DIFFERENCE: the same result register difference as f_0f7c5c.
   WHAT IT DOES: The number of scripts of the node at a position of the list, or -1. */
int CQue::f_0f7d40(int node)
{
    int r;
    if (m4 > 0) {
        Node *p = m6084;
        if (node < 0 || node >= m0) {
            f_093f90("RadioQue: GetScriptNum Failed! Invalid NodeNo:%d\n", node);
            r = -1;
        } else {
            for (int k = 0; k < node; k++)
                p = p->next;
            r = p->n;
        }
    } else {
        r = -1;
    }
    return r;
}

/* @draft 0x0f7da8 us f_0f7da8
   REMAINING DIFFERENCE: retail indexes ents[i] and recs[i] afresh in each pass (offset register
   first) and assigns the saved registers in another order; here the entry pointer is strength
   reduced.
   WHAT IT DOES: Stages a run of n scripts. A run already staged this frame is kept if it is
   more important, or on a coin toss if it is equally important. A run whose table says so
   first drops the queued runs of lower priority. Returns -1 if the run was not staged. */
int CQue::f_0f7da8(Ent **ents, Rec *recs, unsigned short n, Tab *t, int b)
{
    if (n == 0) {
        f_093f90("RadioQue: Set Que Failed! ScriptNum is Zero \n");
        return -1;
    }
    signed char pri = t->pri;
    if (m5900.n != 0) {
        signed char cur = m5900.e[0].tab->pri;
        if (cur < pri)
            return -1;
        if (pri == cur && (f_0f6b90() & 1))
            return -1;
    }
    if (t->flags & 2)
        f_0f8568(t->pri);
    m5900.n = n;
    m5900.wait = ents[0]->m24;
    m5900.delay = ents[0]->m28;
    for (int i = 0; i < n; i++) {
        Item *d = &m5900.e[i];
        d->ent = ents[i];
        unsigned short *dp = d->rec.v;
        const unsigned short *sp = recs[i].v;
        for (int k = 0; k < 4; k++)
            *dp++ = *sp++;
        d->tab = t;
        d->b = b;
    }
    return 0;
}

/* @implements 0x0f7f00 us f_0f7f00
   WHAT IT DOES: Removes the selected node from the queue (it has been handed to the player). */
int CQue::f_0f7f00()
{
    Node *p = m6088;
    if (!p) {
        f_093f90("RadioQue: Error: Shift Que Failed! No Select Que\n");
        return -1;
    }
    f_0f8318(p);
    m6088 = 0;
    return 0;
}

/* @implements 0x0f7f50 us f_0f7f50
   WHAT IT DOES: Empties the queue and the staged run. */
void CQue::f_0f7f50()
{
    m4 = 0;
    m8 = 0;
    for (int i = 0; i < 32; i++) {
        m12[i].prev = 0;
        m12[i].next = 0;
        m12[i].serial = 0;
    }
    m6084 = 0;
    m6088 = 0;
    m5900.n = 0;
}

/* @draft 0x0f7f8c us f_0f7f8c
   REMAINING DIFFERENCE: retail keeps the limit store before the zero result after the first
   print (its call slot stays a nop); here sched2 puts the result first and it lands in the call
   slot.
   WHAT IT DOES: Sets the queue length limit (at most 32). */
int CQue::f_0f7f8c(short max)
{
    if ((unsigned short)max <= 32) {
        f_093f90("RadioQue: Set QueMax[%d]\n", max);
        m0 = max;
        return 0;
    }
    f_093f90("RadioQue: Set QueMax Failed! Invalid QueMax[%d]\n", max);
    return -1;
}

/* @implements 0x0f7ff4 us f_0f7ff4
   WHAT IT DOES: Tells whether a run is staged. */
int CQue::f_0f7ff4()
{
    return m5900.n != 0;
}

/* @implements 0x0f8000 us f_0f8000
   WHAT IT DOES: Counts every queued node's wait time and start delay down by 16, and drops a
   node whose wait time has run out if its first script has one. */
int CQue::f_0f8000()
{
    if (m4 <= 0)
        return -1;
    Node *p = m6084;
    int n = m4;
    for (int i = 1; i <= n; i++) {
        int w = p->wait;
        Ent *e = p->e[0].ent;
        Node *next = p->next;
        if (w > 0) {
            p->wait = w - 16;
            w = p->wait;
        }
        int d = p->delay;
        if (d > 0)
            p->delay = d - 16;
        if (w <= 0 && e->m24 != 0) {
            f_093f90("RadioQue: Wait Time up! Table[%d] Scr[%d]\n", e->m0, e->m2);
            f_0f8318(p);
        }
        p = next;
    }
    return 0;
}

/* @draft 0x0f80c8 us f_0f80c8
   REMAINING DIFFERENCE: in the slot scan retail stores the priority before loading the serial
   (they may alias there) and keeps the array base in a3; here the serial load is hoisted above
   the store.
   WHAT IT DOES: Re-sorts the queue: orders the node slots by priority, then by age (free slots
   last), and relinks the used ones into the circular list in that order, the most important
   first. */
int CQue::f_0f80c8()
{
    int idx[32];
    int pri[32];
    unsigned int ser[32];
    int n = m4;
    int i, j;

    if (n <= 0)
        return -1;
    for (i = 0; i < m0; i++) {
        Node *p = &m12[i];
        if (p->prev) {
            pri[i] = p->e[0].tab->pri;
            ser[i] = p->serial;
        } else {
            pri[i] = -1;
            ser[i] = 0;
        }
        idx[i] = i;
    }
    for (i = 0; i < m0 - 1; i++) {
        for (j = m0 - 1; j > i; j--) {
            if (pri[j - 1] > pri[j] || (pri[j - 1] == pri[j] && ser[j - 1] > ser[j])) {
                int t = pri[j];
                pri[j] = pri[j - 1];
                pri[j - 1] = t;
                unsigned int s = ser[j];
                ser[j] = ser[j - 1];
                ser[j - 1] = s;
                int k = idx[j];
                idx[j] = idx[j - 1];
                idx[j - 1] = k;
            }
        }
    }
    int first = m0 - n;
    m6084 = &m12[idx[first]];
    for (i = first; i < m0; i++) {
        int cur = idx[i];
        int nx, pv;
        if (i + 1 < m0)
            nx = idx[i + 1];
        else
            nx = idx[first];
        if (i == first)
            pv = idx[m0 - 1];
        else
            pv = idx[i - 1];
        Node *q = &m12[cur];
        q->next = &m12[nx];
        q->prev = &m12[pv];
    }
    return 0;
}

/* @implements 0x0f82c0 us f_0f82c0
   WHAT IT DOES: Selects the first node of the list whose start delay has passed; -1 if none. */
int CQue::f_0f82c0()
{
    if (m4 <= 0)
        return -1;
    Node *head = m6084;
    Node *p = head;
    for (int i = 1; i <= m4; i++) {
        if (p->delay <= 0) {
            m6088 = p;
            return 0;
        }
        if (p->next == head)
            break;
        p = p->next;
    }
    return -1;
}

/* @implements 0x0f8318 us f_0f8318
   WHAT IT DOES: Unlinks a node from the list and frees it. */
int CQue::f_0f8318(Node *p)
{
    if (!p) {
        f_093f90("RadioQue: Error: Delete Que Failed! QueNode Addr is NULL\n");
        return -1;
    }
    if (!p->prev) {
        f_093f90("RadioQue: Error: Delete Que Failed! The Que is not registered \n");
        return -1;
    }
    m4--;
    if (p == m6084) {
        if (m4 == 0)
            m6084 = 0;
        else
            m6084 = p->next;
    }
    Node *prev = p->prev;
    Node *next = p->next;
    prev->next = next;
    next->prev = prev;
    p->next = 0;
    p->prev = 0;
    return 0;
}

/* @implements 0x0f83a8 us f_0f83a8
   WHAT IT DOES: Adds the staged run to the queue: into a free slot linked in at the list's
   end, or, when the queue is full, over the least important node if the run is more
   important. Returns -1 if nothing was staged or there was no room. */
int CQue::f_0f83a8()
{
    int best = -1;
    if (m5900.n == 0)
        return -1;
    int n = m4;
    signed char pri = m5900.e[0].tab->pri;
    if (n >= m0) {
        for (int i = 0; i < m0; i++) {
            if (pri < m12[i].e[0].tab->pri) {
                pri = m12[i].e[0].tab->pri;
                best = i;
            }
        }
        if (best < 0) {
            f_093f90("RadioQue: Add Que Failed! Que Max[%d %d]. Prior[%d]\n", m4, m0, pri);
            return -1;
        }
    } else {
        if (n == 0) {
            m6084 = &m12[0];
            best = 0;
            m6084->prev = m6084;
            m6084->next = m6084;
        } else {
            Node *tail = m6084->prev;
            int i;
            for (i = 0; i < m0; i++) {
                if (m12[i].prev == 0) {
                    best = i;
                    break;
                }
            }
            if (best < 0)
                return -1;
            tail->next = &m12[best];
            m6084->prev = &m12[best];
            m12[best].prev = tail;
            m12[best].next = m6084;
        }
        m4 = n + 1;
    }
    m5900.serial = ++m8;
    m5900.prev = m12[best].prev;
    m5900.next = m12[best].next;
    m12[best] = m5900;
    return 0;
}

/* @implements 0x0f8560 us f_0f8560
   WHAT IT DOES: Clears the staged run. */
void CQue::f_0f8560()
{
    m5900.n = 0;
}

/* @implements 0x0f8568 us f_0f8568
   WHAT IT DOES: Drops every queued node whose run is not more important than pri. */
int CQue::f_0f8568(signed char pri)
{
    if (m4 <= 0)
        return -1;
    for (int i = 0; i < m0; i++) {
        Node *p = &m12[i];
        if (p->prev && !(p->e[0].tab->pri < pri))
            f_0f8318(p);
    }
    return 0;
}

}
