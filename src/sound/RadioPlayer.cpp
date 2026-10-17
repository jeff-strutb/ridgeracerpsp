/* The radio DJ manager object file (retail 0x0f6c14 to 0x0f7acc, Radio::CPlayer; its debug
   prints say "RadioManager"). The 16 byte object kept in D_27f09c owns the DJ's speech queue
   (RadioQue.cpp), one stream select channel and the script data tables. It looks up the
   scripts that fit a spoken condition, queues them, and each frame hands the queue's head to
   the stream channel when the channel is free. */

void f_093f90(const char *fmt, ...);

extern "C" {
/* The speech queue (its own object file). */
void f_0f7b14(void *q);
void f_0f7b64(void *q);
void f_0f7b6c(void *q, int stop);
void *f_0f7bd0(void *q);
void *f_0f7be8(void *q, int i);
int f_0f7c44(void *q);
void *f_0f7cc4(void *q, int node, int i);
int f_0f7d40(void *q, int node);
int f_0f7da8(void *q, void *ents, void *recs, int n, void *t, int b);
int f_0f7f00(void *q);
void f_0f7f50(void *q);
int f_0f7f8c(void *q, int max);
int f_0f7ff4(void *q);

/* The stream select channel (its own object file). */
void f_0f8694(void *s);
void f_0f8790(void *s);
void f_0f8808(void *s, int a, int b);
int f_0f88b0(void *s);
int f_0f894c(void *s);
int f_0f8964(void *s);
int f_0f897c(void *s, unsigned short id);
int f_0f89d0(void *s);
int f_0f8a74(void *s);
int f_0f8a98(void *s);
int f_0f8abc(void *s);
int f_0f8ac8(void *s);
void f_0f8aec(void *s, void *node, unsigned short n, int ch);
void f_0f8b48(void *s);
void f_0f8b78(void *s);
int f_0f8b90(void *s);
int f_0f8c0c(void *s);
void f_0f8c6c(void *s);

/* The script data tables (their own object file). */
int f_10ab7c(int speaker);
int f_10abd0(void);
void f_10ac78(void *d);
void f_10ad18(void *d);
int f_10ad64(void *d, void *data);
int f_10ae00(void *d);
void *f_10ae6c(void *d, unsigned short voice, short cond);
void *f_10af20(void *d, unsigned short voice, short table);
short f_10aff0(void *d, unsigned short voice, short cond);
int f_10b0f8(void *d, unsigned short voice, short cond, void *opt);
int f_10b3a4(void *d, void *ent, void *rec);
int f_10b428(void *d);
int f_10b460(void *d);
int f_10b498(void *d);
int f_10b4d0(void *d);
int f_10b508(void *d, unsigned short id);
void f_10b5c4(void *d);
void f_10b63c(void *d, unsigned short id);
void f_10b65c(void *d, int v);
void f_10b6c4(void *d, void *x);
int f_10b6f0(void *d, void *p, void *x);
int f_10b788(void *d, int set);
void f_10b7f0(void *d);
short f_10bd3c(void *t, short v);
}

namespace Radio {

/* The speech queue: its node count at +4. */
struct CQue {
    CQue() { f_0f7b14(this); }
    ~CQue() { f_0f7b64(this); }
    short m0;
    int m4;
    char m8[6084];
};

/* The stream select channel. */
struct CSel {
    CSel() { f_0f8694(this); }
    ~CSel() { f_0f8790(this); }
    int m0;
    int m4;
    int m8;     /* the stream channel it plays on */
    int m12[6];
    int m36;
    int m40;
    int m44[2];
    int m52;
    int m56;
    int m60;
    int m64[44];
};

/* The script data tables. */
struct CData {
    CData() { f_10ac78(this); }
    ~CData() { f_10ad18(this); }
    char m0[436];
    void *m436;
};

/* A script entry of the tables. */
struct Ent {
    unsigned short m0;
    short m2;
    unsigned short m4;
    short m6;
    char m8[4];
    short m12;
    short m14;
};

/* A script's play record. */
struct Rec {
    int m0[2];
};

/* Six per-speaker options passed along with a condition. */
struct Opt {
    signed char v[6];
};

/* A queue node: its play data. */
struct Node {
    int m0[2];
    signed char *m8;
    unsigned char *m12;
};

/* A queue node's table attribute. */
struct Attr {
    int m0;
    unsigned short m4;
};

class CPlayer {
public:
    CPlayer();
    ~CPlayer();
    int f_0f6ea4(void *data);
    int f_0f6f2c();
    void f_0f6f60();
    void f_0f6f7c();
    void f_0f6fb8();
    void f_0f6fd4();
    int f_0f6ff0();
    int f_0f7018();
    int f_0f703c();
    int f_0f7208(unsigned short voice, short cond, const Opt *opt, int b);
    int f_0f72d8(unsigned short voice, const short *conds, unsigned short n);
    int f_0f7404(unsigned short id);
    int f_0f74c0(Ent *p);
    int f_0f75b0(unsigned short id);
    int f_0f75d8(int i);
    int f_0f75fc(int i);
    int f_0f7620();
    int f_0f7684();
    int f_0f76a4(unsigned short voice, short cond, const Opt *opt);
    int f_0f7724(int i);
    int f_0f7738(int i);
    short f_0f774c(int i);
    int f_0f7774(int i);
    int f_0f7788(int i);
    int f_0f779c();
    int f_0f77a8();
    int f_0f77c4();
    int f_0f77e0(unsigned short id);
    int f_0f7800(unsigned short voice, short cond);
    int f_0f7834(int set);
    int f_0f7850();
    int f_0f7858();
    int f_0f7860(unsigned short voice, short cond, Opt *opt, int b);
    int f_0f7a1c(int ch);
    int f_0f7a34(int ch);
    int f_0f7a5c(int ch);

    int m0;        /* stopped */
    CQue *m4;
    CSel *m8[1];
    CData *m12;
};

/* @implements 0x0f6c14 us _ZN5Radio7CPlayerC2Ev
   WHAT IT DOES: Creates the stream select channel, the speech queue and the script tables
   (base object constructor). */
/* @implements 0x0f6cc8 us _ZN5Radio7CPlayerC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CPlayer::CPlayer()
{
    for (int i = 0; i < 1; i++)
        m8[i] = new CSel;
    m4 = new CQue;
    m12 = new CData;
}

/* @implements 0x0f6d7c us _ZN5Radio7CPlayerD2Ev
   WHAT IT DOES: Deletes the script tables, the select channel and the queue (base object
   destructor). */
/* @implements 0x0f6e10 us _ZN5Radio7CPlayerD1Ev
   WHAT IT DOES: The same, complete object destructor. */
CPlayer::~CPlayer()
{
    if (m12) {
        delete m12;
        m12 = 0;
    }
    if (m8[0]) {
        delete m8[0];
        m8[0] = 0;
    }
    if (m4) {
        delete m4;
        m4 = 0;
    }
}

/* @implements 0x0f6ea4 us f_0f6ea4
   WHAT IT DOES: Loads the script tables from the stream data, resets the select channel, sets
   the queue's speaker and length limits from the tables, clears everything and starts the
   tables' timer. Returns -1 if the tables would not load, else 0. */
int CPlayer::f_0f6ea4(void *data)
{
    if (f_10ad64(m12, data))
        return -1;
    f_0f8808(m8[0], 0, -1);
    int v = f_10b460(m12);
    if (v >= 0)
        f_10b65c(m12, v);
    v = f_10b498(m12);
    if (v >= 0)
        f_0f7f8c(m4, v);
    f_0f6f7c();
    f_10abd0();
    return 0;
}

/* @implements 0x0f6f2c us f_0f6f2c
   WHAT IT DOES: Clears everything and releases the script tables; -1 if that failed. */
int CPlayer::f_0f6f2c()
{
    f_0f6f7c();
    return f_10ae00(m12) ? -1 : 0;
}

/* @implements 0x0f6f60 us f_0f6f60
   WHAT IT DOES: Clears everything. */
void CPlayer::f_0f6f60()
{
    f_0f6f7c();
}

/* @implements 0x0f6f7c us f_0f6f7c
   WHAT IT DOES: Marks the manager running and clears the tables' state, the queue and the
   select channel. */
void CPlayer::f_0f6f7c()
{
    m0 = 0;
    f_10b5c4(m12);
    f_0f7f50(m4);
    f_0f8b48(m8[0]);
}

/* @implements 0x0f6fb8 us f_0f6fb8
   WHAT IT DOES: Clears the speech queue. */
void CPlayer::f_0f6fb8()
{
    f_0f7f50(m4);
}

/* @implements 0x0f6fd4 us f_0f6fd4
   WHAT IT DOES: Stops the select channel. */
void CPlayer::f_0f6fd4()
{
    f_0f8b48(m8[0]);
}

/* @implements 0x0f6ff0 us f_0f6ff0
   WHAT IT DOES: Marks the manager stopped and pauses the select channel. */
int CPlayer::f_0f6ff0()
{
    m0 = 1;
    f_0f8b90(m8[0]);
    return 0;
}

/* @implements 0x0f7018 us f_0f7018
   WHAT IT DOES: Marks the manager running and resumes the select channel. */
int CPlayer::f_0f7018()
{
    m0 = 0;
    f_0f8c0c(m8[0]);
    return 0;
}

/* @implements 0x0f703c us f_0f703c
   WHAT IT DOES: The per frame step. Updates the queue; while running, takes the queue's head
   node, finds the stream channel for its speaker, and if a channel is free (or the node may
   interrupt the one playing) hands the node and its scripts to the select channel, marks the
   scripts used and drops the node from the queue. Then updates the select channel and the
   tables. Returns -1 while stopped, else 0. */
int CPlayer::f_0f703c()
{
    f_0f7b6c(m4, m0);
    if (m0 != 0)
        return -1;
    Node *n = (Node *)f_0f7bd0(m4);
    if (n) {
        int spk = n->m8[17];
        int ch = f_10ab7c(spk);
        unsigned char *flags = n->m12;
        if (ch < 0) {
            f_093f90("RadioManager: Invalid Stream Ch:%d Speaker:%d\n", ch, spk);
            f_0f7f00(m4);
        } else {
            int sel = f_0f7a5c(ch);
            if (flags[1] & 1) {
                int k = f_0f7a1c(ch);
                if (k >= 0) {
                    if (f_0f8a98(m8[k]) == 1) {
                        sel = k;
                        f_0f8b48(m8[k]);
                    }
                }
                k = f_0f7a34(ch);
                if (k >= 0)
                    f_0f8b78(m8[k]);
            }
            if (sel >= 0) {
                int num = f_0f7c44(m4);
                f_0f8aec(m8[sel], n, num, ch);
                for (int i = 0; i < num; i++) {
                    Attr *a = (Attr *)f_0f7be8(m4, i);
                    if (a) {
                        f_10b63c(m12, a->m4);
                        f_10b6c4(m12, a);
                    }
                }
                f_0f7f00(m4);
            }
        }
    }
    f_0f8c6c(m8[0]);
    f_10b7f0(m12);
    return 0;
}

/* @implements 0x0f7208 us f_0f7208
   WHAT IT DOES: Asks for a voice's condition with the given speaker options (all -1 when none
   are given): the tables pick a script condition, and that condition is queued. Returns the
   picked condition, negative if none fits. */
int CPlayer::f_0f7208(unsigned short voice, short cond, const Opt *opt, int b)
{
    Opt o;
    if (opt) {
        o = *opt;
    } else {
        for (int i = 0; i < 6; i++)
            o.v[i] = -1;
    }
    int r = f_10b0f8(m12, voice, cond, &o);
    if (r >= 0)
        f_0f7860(voice, r, &o, b);
    return r;
}

/* @implements 0x0f72d8 us f_0f72d8
   WHAT IT DOES: Queues a fixed list of a voice's conditions (ended early by a negative one):
   looks up each condition's script entry and play record, then the table of the first entry,
   and sets them into the queue. Returns -1 on any failure, else 0. */
int CPlayer::f_0f72d8(unsigned short voice, const short *conds, unsigned short n)
{
    Rec recs[8];
    Ent *ents[8];
    Ent *e;

    for (int i = 0; i < n; i++) {
        short c = conds[i];
        if (c < 0)
            break;
        c = f_10aff0(m12, voice, c);
        if (c < 0)
            break;
        e = (Ent *)f_10ae6c(m12, voice, c);
        if (!e)
            return -1;
        f_10b3a4(m12, e, &recs[i]);
        ents[i] = e;
    }
    e = ents[0];
    void *t = f_10af20(m12, voice, e->m6);
    if (!t) {
        f_093f90("RadioManager: SetScriptArray Failed! GetTabelCondition Failed \n");
        return -1;
    }
    return f_0f7da8(m4, ents, recs, n, t, -1) < 0 ? -1 : 0;
}

/* @implements 0x0f7404 us f_0f7404
   WHAT IT DOES: Tells whether any queued node holds a script with the given id. */
int CPlayer::f_0f7404(unsigned short id)
{
    int nodes = m4->m4;
    for (int i = 0; i < nodes; i++) {
        int k = f_0f7d40(m4, i);
        for (int j = 0; j < k; j++) {
            Attr *a = (Attr *)f_0f7cc4(m4, i, j);
            if (a && a->m4 == id)
                return 1;
        }
    }
    return 0;
}

/* @implements 0x0f74c0 us f_0f74c0
   WHAT IT DOES: Tells whether the given script entry is already in the queue (as the tables
   compare them), printing its condition when it is. */
int CPlayer::f_0f74c0(Ent *p)
{
    int nodes = m4->m4;
    if (p == 0)
        return 0;
    for (int i = 0; i < nodes; i++) {
        int k = f_0f7d40(m4, i);
        for (int j = 0; j < k; j++) {
            void *a = f_0f7cc4(m4, i, j);
            if (a) {
                if (f_10b6f0(m12, p, a) == 1) {
                    f_093f90("RadioManager: Addr IN QUE no: %d\n", p->m2);
                    return 1;
                }
            }
        }
    }
    return 0;
}

/* @implements 0x0f75b0 us f_0f75b0
   WHAT IT DOES: Tells whether the select channel is playing the script with the given id. */
int CPlayer::f_0f75b0(unsigned short id)
{
    return f_0f897c(m8[0], id) == 1;
}

/* @implements 0x0f75d8 us f_0f75d8
   WHAT IT DOES: Passes on select channel i's f_0f894c. */
int CPlayer::f_0f75d8(int i)
{
    return f_0f894c(m8[i]);
}

/* @implements 0x0f75fc us f_0f75fc
   WHAT IT DOES: Passes on select channel i's f_0f8964. */
int CPlayer::f_0f75fc(int i)
{
    return f_0f8964(m8[i]);
}

/* @implements 0x0f7620 us f_0f7620
   WHAT IT DOES: Tells whether the DJ has fallen silent: the select channel is idle, the queue
   is empty and no queue entry is selected. */
int CPlayer::f_0f7620()
{
    for (int i = 0; i < 1; i++) {
        if (!f_0f8ac8(m8[i]))
            return 0;
    }
    if (m4->m4 > 0 || f_0f7ff4(m4) == 1)
        return 0;
    return 1;
}

/* @implements 0x0f7684 us f_0f7684
   WHAT IT DOES: Tells whether the select channel is idle. */
int CPlayer::f_0f7684()
{
    return f_0f8ac8(m8[0]) != 0;
}

/* @implements 0x0f76a4 us f_0f76a4
   WHAT IT DOES: Queues a given script condition directly with the given speaker options (all
   -1 when none are given). */
int CPlayer::f_0f76a4(unsigned short voice, short cond, const Opt *opt)
{
    Opt o;
    if (opt) {
        o = *opt;
    } else {
        for (int i = 0; i < 6; i++)
            o.v[i] = -1;
    }
    return f_0f7860(voice, cond, &o, -1);
}

/* @implements 0x0f7724 us f_0f7724
   WHAT IT DOES: Select channel i's word at +36. */
int CPlayer::f_0f7724(int i)
{
    return m8[i]->m36;
}

/* @implements 0x0f7738 us f_0f7738
   WHAT IT DOES: Select channel i's word at +40. */
int CPlayer::f_0f7738(int i)
{
    return m8[i]->m40;
}

/* @implements 0x0f774c us f_0f774c
   WHAT IT DOES: Select channel i's f_0f88b0, as a short. */
short CPlayer::f_0f774c(int i)
{
    return f_0f88b0(m8[i]);
}

/* @implements 0x0f7774 us f_0f7774
   WHAT IT DOES: Select channel i's word at +60. */
int CPlayer::f_0f7774(int i)
{
    return m8[i]->m60;
}

/* @implements 0x0f7788 us f_0f7788
   WHAT IT DOES: Select channel i's word at +52. */
int CPlayer::f_0f7788(int i)
{
    return m8[i]->m52;
}

/* @implements 0x0f779c us f_0f779c
   WHAT IT DOES: The number of queued nodes. */
int CPlayer::f_0f779c()
{
    return m4->m4;
}

/* @implements 0x0f77a8 us f_0f77a8
   WHAT IT DOES: Passes on the tables' f_10b428. */
int CPlayer::f_0f77a8()
{
    return f_10b428(m12);
}

/* @implements 0x0f77c4 us f_0f77c4
   WHAT IT DOES: Passes on the tables' f_10b4d0. */
int CPlayer::f_0f77c4()
{
    return f_10b4d0(m12);
}

/* @implements 0x0f77e0 us f_0f77e0
   WHAT IT DOES: Passes on the tables' f_10b508 for an id. */
int CPlayer::f_0f77e0(unsigned short id)
{
    return f_10b508(m12, id);
}

/* @implements 0x0f7800 us f_0f7800
   WHAT IT DOES: The condition number of a voice's script entry, or -1 if there is none. */
int CPlayer::f_0f7800(unsigned short voice, short cond)
{
    Ent *e = (Ent *)f_10ae6c(m12, voice, cond);
    if (!e)
        return -1;
    return e->m2;
}

/* @implements 0x0f7834 us f_0f7834
   WHAT IT DOES: Passes on the tables' f_10b788 for a set. */
int CPlayer::f_0f7834(int set)
{
    return f_10b788(m12, set);
}

/* @implements 0x0f7850 us f_0f7850
   WHAT IT DOES: Returns -1. */
int CPlayer::f_0f7850()
{
    return -1;
}

/* @implements 0x0f7858 us f_0f7858
   WHAT IT DOES: Returns 0. */
int CPlayer::f_0f7858()
{
    return 0;
}

/* @draft 0x0f7860 us f_0f7860
   REMAINING DIFFERENCE: in retail the loop counter and the two record pointers are stepped in
   the loop's last block, after the next entry's lookup; here sched1's interblock pass hoists
   those increments into the loop's first block (seen in the -da sched dump), and the
   table-pick branch's continue/break layout is inverted.
   WHAT IT DOES: Queues a script condition and the chain of conditions it leads to (up to 8):
   each entry names its next condition, or a table from which the tables pick one with the
   speaker options. The entries, their play records and the first entry's table go into the
   queue. Returns -1 if the select channel cannot take more or a lookup fails, else 0. */
int CPlayer::f_0f7860(unsigned short voice, short cond, Opt *opt, int b)
{
    short conds[8];
    Rec recs[8];
    Ent *ents[8];
    unsigned short n = 0;

    if (f_0f8a74(m8[0])) {
        Ent *e = (Ent *)f_10ae6c(m12, voice, cond);
        if (!e)
            return -1;
        void *t = f_10af20(m12, voice, e->m6);
        if (t) {
            conds[0] = cond;
            for (int i = 0; i < 8; i++) {
                f_10b3a4(m12, e, &recs[i]);
                short next = e->m12;
                ents[i] = e;
                n++;
                if (next < 0) {
                    short tab = e->m14;
                    if (tab < 0)
                        break;
                    int r = f_10b0f8(m12, voice, f_10bd3c(m12->m436, tab), opt);
                    if (r < 0)
                        break;
                    cond = r;
                } else {
                    cond = f_10aff0(m12, e->m0, next);
                }
                e = (Ent *)f_10ae6c(m12, voice, cond);
                conds[n] = cond;
            }
            if (f_0f7da8(m4, ents, recs, n, t, b) >= 0)
                return 0;
        } else {
            f_093f90("RadioManager: Add Que Failed! GetTabelCondition Failed \n");
        }
    } else {
        f_093f90("RadioManager: AddQue Failed! Now Cannot AddQue\n");
    }
    return -1;
}

/* @implements 0x0f7a1c us f_0f7a1c
   WHAT IT DOES: The select channel playing on stream channel ch: 0, or -1 if none. */
int CPlayer::f_0f7a1c(int ch)
{
    for (int i = 0; i < 1; i++) {
        if (ch == m8[i]->m8)
            return i;
    }
    return -1;
}

/* @implements 0x0f7a34 us f_0f7a34
   WHAT IT DOES: The select channel that is busy: 0, or -1 if none. */
int CPlayer::f_0f7a34(int ch)
{
    for (int i = 0; i < 1; i++) {
        if (f_0f89d0(m8[i]) == 1)
            return i;
    }
    return -1;
}

/* @implements 0x0f7a5c us f_0f7a5c
   WHAT IT DOES: A free select channel for stream channel ch: -1 if a channel already plays
   on ch or is busy, else the last idle channel (-1 if none). */
int CPlayer::f_0f7a5c(int ch)
{
    int r = -1;
    for (int i = 0; i < 1; i++) {
        if (ch == m8[i]->m8 || f_0f89d0(m8[i]) == 1)
            return -1;
        if (f_0f8abc(m8[i]) == 1)
            r = i;
    }
    return r;
}

}
