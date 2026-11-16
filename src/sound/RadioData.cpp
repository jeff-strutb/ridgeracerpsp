/* The radio DJ script tables object file (retail 0x10ac24 to 0x10bd14, Radio::CData; its
   debug prints say "RadioData"). It holds the script table data handed over from the stream
   data: a header, one sub header per table (id, script count, offset of its 48 byte script
   entries) and a condition table after the sub headers. Per script it keeps the frame of the
   last play and a play count, and it keeps a ring log of the last scripts played (up to
   LogMax of 100) so a script is not repeated too soon. Script selection weighs the matching
   scripts by their probability byte. A one byte condition helper (its own object file) maps
   file numbers of 30000 and above and tests the per-speaker options. */

void f_093f90(const char *fmt, ...);

extern "C" {
int f_0f6b90(void);
}

namespace Radio {

/* A table's sub header. */
struct Sub {
    unsigned short id;
    unsigned short count;
    int off;                /* its script entries, from the start of the table data */
};

/* The table data's header; the sub headers follow it, then the condition table. */
struct Header {
    char p0[4];
    unsigned short num;     /* tables */
    unsigned short total;   /* scripts in all tables */
    short streams;
    char pa[12];
    short conds;
    short logMax;
    short queMax;
    char p1c[4];
    Sub sub[1];
};

/* A script entry (48 bytes). */
struct Ent {
    unsigned short m0;
    short key;              /* sorted within its table */
    unsigned short id;      /* index into the per-script arrays */
    short cond;
    char p8[2];
    unsigned char nfile;
    unsigned char flag;     /* logged when played */
    char pc[6];
    signed char prob;
    unsigned char max;      /* play count limit, 0 for none */
    char p14[12];
    unsigned short again;   /* replay gap */
    signed char spk[6];
    short file[4];
};

/* Six per-speaker options passed along with a condition. */
struct Opt {
    signed char v[6];
};

/* The condition helper (its own object file). */
class CCond {
public:
    CCond() { f_10bd1c(); }
    ~CCond() { f_10bd2c(); }
    void f_10bd1c();
    void f_10bd2c();
    short f_10bd34(short v);
    int f_10bd70(signed char v, int i, Ent *e);
    char m0;
};

class CPlayer {
public:
    int f_0f7404(unsigned short id);
    int f_0f74c0(Ent *p);
    int f_0f75b0(unsigned short id);
    int f_0f75d8(int i);
};

class CData {
public:
    CData();
    ~CData();
    int f_10ad64(void *data);
    int f_10ae00();
    Ent *f_10ae6c(unsigned short table, short sub);
    short *f_10af20(unsigned short table, short cond);
    short f_10aff0(unsigned short table, short key);
    int f_10b0f8(unsigned short table, short cond, Opt *opt);
    int f_10b3a4(Ent *e, short *out);
    int f_10b428();
    int f_10b460();
    int f_10b498();
    int f_10b4d0();
    int f_10b508(unsigned short table);
    int f_10b554();
    int f_10b58c();
    int f_10b5c4();
    void f_10b63c(unsigned short id);
    int f_10b65c(short v);
    int f_10b6c4(Ent *e);
    int f_10b6f0(Ent *a, Ent *b);
    int f_10b788(int i);
    void f_10b7f0();
    int f_10b874(void *data);
    int f_10b8b0();
    Sub *f_10b8f4(unsigned short table);
    int f_10b96c(unsigned short table);
    int f_10b9e4(Opt *opt, Ent *e);
    Ent *f_10ba78(unsigned short i);
    int f_10bb08(unsigned short id, unsigned short again);
    void f_10bbdc();
    int f_10bbec(Ent *e);
    int f_10bc58(Ent *e);

    int m0;                 /* log: entries */
    int m4;                 /* log: oldest */
    int m8;                 /* log: next free */
    Ent *m12[100];
    short m412;             /* LogMax */
    unsigned int *m416;     /* per script: frame of its last play */
    int *m420;              /* per script: play count */
    Header *m424;
    unsigned int m428;      /* frame counter */
    int m432;               /* the select channel's current stream */
    CCond *m436;
};

}

extern Radio::CPlayer *D_27f09c;

namespace Radio {

/* @implements 0x10ac24 us _ZN5Radio5CDataC2Ev
   WHAT IT DOES: Creates the condition helper (base object constructor). */
/* @implements 0x10ac78 us _ZN5Radio5CDataC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CData::CData()
{
    m436 = new CCond;
}

/* @implements 0x10accc us _ZN5Radio5CDataD2Ev
   WHAT IT DOES: Deletes the condition helper (base object destructor). */
/* @implements 0x10ad18 us _ZN5Radio5CDataD1Ev
   WHAT IT DOES: The same, complete object destructor. */
CData::~CData()
{
    if (m436) {
        delete m436;
        m436 = 0;
    }
}

/* @implements 0x10ad64 us _ZN5Radio5CData8f_10ad64EPv
   WHAT IT DOES: Sets the table data, allocates the per-script play frame and count arrays,
   clears them and the log and sets LogMax to 100. Returns -1 for no data, else 0. */
int CData::f_10ad64(void *data)
{
    if (f_10b874(data))
        return -1;
    Header *h = m424;
    unsigned short n = h->total;
    m416 = new unsigned int[n];
    m420 = new int[n];
    f_10b5c4();
    f_10bbdc();
    m412 = 100;
    f_093f90("RadioData: Set Data: TableNum:%d ScriptNum:%d\n", h->num, n);
    return 0;
}

/* @implements 0x10ae00 us _ZN5Radio5CData8f_10ae00Ev
   WHAT IT DOES: Drops the table data and frees the per-script arrays. Returns -1 when no
   data was set, else 0. */
int CData::f_10ae00()
{
    if (f_10b8b0())
        return -1;
    if (m416) {
        delete[] m416;
        m416 = 0;
    }
    if (m420) {
        delete[] m420;
        m420 = 0;
    }
    return 0;
}

/* @implements 0x10ae6c us _ZN5Radio5CData8f_10ae6cEts
   WHAT IT DOES: Returns script entry sub of the given table, or 0 for an unknown table or an
   index out of range. */
Ent *CData::f_10ae6c(unsigned short table, short sub)
{
    Sub *s = f_10b8f4(table);
    if (!s) {
        f_093f90("RadioData: Error: GetTableAttr Failed! Invaild TableNo[%d]\n", table);
        return 0;
    }
    if (sub >= s->count || sub < 0) {
        f_093f90("RadioData: Error: Get TableAttr Failed! Invalid SubIndex[%d] ScriptNum[%d]\n", sub, s->count);
        return 0;
    }
    return (Ent *)((char *)m424 + s->off) + sub;
}

/* @draft 0x10af20 us _ZN5Radio5CData8f_10af20Ets
   WHAT IT DOES: Returns the condition table cell of the given table and condition (the
   table follows the sub headers, one row per table), or 0 for an unknown table.
   DRAFT: the condition check's error print is placed out of line here; retail keeps it as
   the fall-through, with the unknown-table print cross-jumped into its call. */
short *CData::f_10af20(unsigned short table, short cond)
{
    short idx = f_10b96c(table);
    if (idx < 0) {
        f_093f90("RadioData: GetTableCondition Failed! Invaild TableNo[%d]\n", table);
        return 0;
    }
    int n = f_10b58c();
    if (n < 0)
        return 0;
    if ((cond < 0) & (cond >= n)) {
        f_093f90("RadioData: GetTableCondition Failed! Invaild Condition[%d]\n", cond);
        return 0;
    }
    short k = cond + idx * n;
    return (short *)&m424->sub[f_10b428()] + k;
}

/* @implements 0x10aff0 us _ZN5Radio5CData8f_10aff0Ets
   WHAT IT DOES: Binary searches the given table's entries for the key; returns its index or
   -1. */
short CData::f_10aff0(unsigned short table, short key)
{
    Sub *t = f_10b8f4(table);
    Ent *e, *q;
    short lo, hi, mid;
    if (!t) {
        f_093f90("RadioData: Error: GetSubIndex Failed! Invaild TableNo[%d]\n", table);
        return -1;
    }
    e = (Ent *)((char *)m424 + t->off);
    hi = t->count - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        q = &e[mid];
        if (q->key == key)
            return mid;
        if (q->key < key)
            lo = mid + 1;
        else
            hi = mid;
    }
    if (lo == hi) {
        q = &e[lo];
        if (q->key == key)
            return lo;
    }
    f_093f90("RadioData: Error: GetSubIndex Failed! Not Found TableNo[%d] ScriptNo[%d]\n", table, key);
    return -1;
}

/* @draft 0x10b0f8 us _ZN5Radio5CData8f_10b0f8EtsPNS_3OptE
   WHAT IT DOES: Picks a script of the given table for the condition. Candidates are the
   entries with that condition whose replay gap has passed, under their play limit, whose
   speaker options fit and (if logged) not in the log; one is drawn by probability (or
   uniformly when every probability is negative). Returns its index in the table, or
   0x80000001 for an unknown table, 0x80000002 for no candidate, 0x80000003 when the draw
   fails.
   DRAFT: two registers: retail gives the probability total s6 and the f_10bb08 result s5
   (swapped here), and builds the result in v0 where this builds it in v1 and copies it. */
int CData::f_10b0f8(unsigned short table, short cond, Opt *opt)
{
    short list[256];
    signed char prob[256];
    int sel = -1;
    int num = 0;
    int r;
    int total = 0;
    int i;
    Sub *s = f_10b8f4(table);
    if (!s)
        return 0x80000001;
    Ent *e = (Ent *)((char *)m424 + s->off);
    int n = s->count;
    short *lp = list;
    for (i = 0; i < n; i++, e++) {
        if (e->cond != cond)
            continue;
        r = f_10bb08(e->id, e->again);
        if (r != 1)
            continue;
        if (e->max != 0 && m420[e->id] >= e->max)
            continue;
        if (f_10b9e4(opt, e) != 1)
            continue;
        if (e->flag != 0 && f_10bc58(e) != 0)
            continue;
        *lp++ = i;
        prob[num++] = e->prob;
        if (num >= 256) {
            f_093f90("RadioData: SelectList Over! Num[%d]\n", num);
            break;
        }
    }
    if (num == 0)
        return 0x80000002;
    for (i = 0; i < num; i++)
        total += prob[i];
    if (total > 0) {
        unsigned char r = f_0f6b90() % 100;
        unsigned char acc = 0;
        for (i = 0; i < num; i++) {
            if (prob[i] > 0) {
                acc += prob[i];
                if (r < acc) {
                    sel = i;
                    break;
                }
            }
        }
    } else if (total == 0) {
        f_093f90("RadioData: Probability Total is Zero.\n");
    } else {
        sel = f_0f6b90() % num;
    }
    if (sel >= 0)
        return list[sel];
    return 0x80000003;
}

/* @implements 0x10b3a4 us _ZN5Radio5CData8f_10b3a4EPNS_3EntEPs
   WHAT IT DOES: Copies the entry's four file numbers, mapping those of 30000 and above
   through the condition helper. */
int CData::f_10b3a4(Ent *e, short *out)
{
    unsigned short *p = (unsigned short *)e->file;
    for (int i = 0; i < 4; i++) {
        unsigned short v = *p;
        if ((short)v < 30000)
            *out = v;
        else
            *out = m436->f_10bd34(v - 30000);
        p++;
        out++;
    }
    return 0;
}

/* @implements 0x10b428 us _ZN5Radio5CData8f_10b428Ev
   WHAT IT DOES: Returns the number of tables, or -1 when no data is set. */
int CData::f_10b428()
{
    if (m424)
        return m424->num;
    f_093f90("RadioData: Error: Get TableNum Failed! Table Data has been Not Set yet\n");
    return -1;
}

/* @implements 0x10b460 us _ZN5Radio5CData8f_10b460Ev
   WHAT IT DOES: Returns the tables' LogMax, or -1 when no data is set. */
int CData::f_10b460()
{
    if (m424)
        return m424->logMax;
    f_093f90("RadioData: Error: Get LogMax Failed! Table Data has been Not Set yet\n");
    return -1;
}

/* @implements 0x10b498 us _ZN5Radio5CData8f_10b498Ev
   WHAT IT DOES: Returns the tables' QueMax, or -1 when no data is set. */
int CData::f_10b498()
{
    if (m424)
        return m424->queMax;
    f_093f90("RadioData: Error: Get QueMax Failed! Table Data has been Not Set yet\n");
    return -1;
}

/* @implements 0x10b4d0 us _ZN5Radio5CData8f_10b4d0Ev
   WHAT IT DOES: Returns the number of streams, or -1 when no data is set. */
int CData::f_10b4d0()
{
    if (m424)
        return m424->streams;
    f_093f90("RadioData: Error: Get StreamNum Failed! Table Data has been Not Set yet\n");
    return -1;
}

/* @implements 0x10b508 us _ZN5Radio5CData8f_10b508Et
   WHAT IT DOES: Returns the given table's script count, or -1 for an unknown table. */
int CData::f_10b508(unsigned short table)
{
    Sub *s = f_10b8f4(table);
    if (s)
        return s->count;
    f_093f90("RadioData: Error: Get ScriptNum Failed! TableNo[%d]\n", table);
    return -1;
}

/* @implements 0x10b554 us _ZN5Radio5CData8f_10b554Ev
   WHAT IT DOES: Returns the scripts in all tables, or -1 when no data is set. */
int CData::f_10b554()
{
    if (m424)
        return m424->total;
    f_093f90("RadioData: Error: Get Table Script TotalNum! Table Data has been Not Set yet\n");
    return -1;
}

/* @implements 0x10b58c us _ZN5Radio5CData8f_10b58cEv
   WHAT IT DOES: Returns the number of conditions, or -1 when no data is set. */
int CData::f_10b58c()
{
    if (m424)
        return m424->conds;
    f_093f90("RadioData: GetConditionNum Failed ! Table Data has been Not Set yet\n");
    return -1;
}

/* @implements 0x10b5c4 us _ZN5Radio5CData8f_10b5c4Ev
   WHAT IT DOES: Clears every script's play frame and count, the log, the frame counter and
   the current stream. Returns -1 when no data is set, else 0. */
int CData::f_10b5c4()
{
    int n = f_10b554();
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++) {
        m416[i] = 0;
        m420[i] = 0;
    }
    f_10bbdc();
    m428 = 0;
    m432 = -1;
    return 0;
}

/* @implements 0x10b63c us _ZN5Radio5CData8f_10b63cEt
   WHAT IT DOES: Counts one play of the script. */
void CData::f_10b63c(unsigned short id)
{
    m420[id]++;
}

/* @draft 0x10b65c us _ZN5Radio5CData8f_10b65cEs
   WHAT IT DOES: Sets LogMax (0 to 100). Returns -1 for a value out of range, else 0.
   DRAFT: the error print reloads a1 here (retail reuses the copy made before the branch)
   and the LogMax store is scheduled after the zero result. */
int CData::f_10b65c(short v)
{
    if ((unsigned short)v <= 100) {
        f_093f90("RadioData: Set LogMax[%d]\n", v);
        m412 = v;
        return 0;
    }
    f_093f90("RadioData: Set LogMax Failed! Invalid LogMax[%d]\n", v);
    return -1;
}

/* @implements 0x10b6c4 us _ZN5Radio5CData8f_10b6c4EPNS_3EntE
   WHAT IT DOES: Logs the entry if it is a logged one. Returns -1 if it is not, else 0. */
int CData::f_10b6c4(Ent *e)
{
    if (!e->flag)
        return -1;
    f_10bbec(e);
    return 0;
}

/* @draft 0x10b6f0 us _ZN5Radio5CData8f_10b6f0EPNS_3EntES2_
   WHAT IT DOES: Tells whether two entries are the same script or play the same files.
   DRAFT: retail sets up the two file pointers after the loop's guard and keeps the count in
   t2 and the index in t1; here they are set up before it with the index in a3. */
int CData::f_10b6f0(Ent *a, Ent *b)
{
    if (a == 0 || b == 0) {
        f_093f90("RadioData: IsEqualledFileNo Failed! Invalid Addr 0x%x 0x%x\n", a, b);
        return 0;
    }
    if (a->id == b->id)
        return 1;
    if (a->nfile == 0)
        return 0;
    short *p = a->file;
    short *q = b->file;
    for (int i = 0; i < a->nfile; i++) {
        if (*p != *q)
            return 0;
        p++;
        q++;
    }
    return 1;
}

/* @implements 0x10b788 us _ZN5Radio5CData8f_10b788Ei
   WHAT IT DOES: Returns the id of table i, or -1. */
int CData::f_10b788(int i)
{
    Header *h = m424;
    if (!h) {
        f_093f90("RadioData: GetTableNo Failed! Table Data has been Not Set yet\n");
        return -1;
    }
    if (i < 0 || i >= h->num) {
        f_093f90("RadioData: GetTableNo Failed! Invalid Table Index:%d\n", i);
        return -1;
    }
    Sub *s = &h->sub[i];
    return s->id;
}

/* @draft 0x10b7f0 us _ZN5Radio5CData8f_10b7f0Ev
   WHAT IT DOES: The per-frame step: when the select channel's stream changes, stamps the
   previous stream's script with the frame and takes the new one; counts the frame.
   DRAFT: retail keeps a second copy of this (s1) for the final store of the new stream, and
   the player pointer's high half in s2; the source shape that keeps that copy is not found. */
void CData::f_10b7f0()
{
    if (m432 != D_27f09c->f_0f75d8(0)) {
        if (m432 >= 0)
            m416[m432] = m428;
        m432 = D_27f09c->f_0f75d8(0);
    }
    m428++;
}

/* @implements 0x10b874 us _ZN5Radio5CData8f_10b874EPv
   WHAT IT DOES: Sets the table data. Returns -1 for none, else 0. */
int CData::f_10b874(void *data)
{
    if (!data) {
        f_093f90("RadioData: Error: Set Table Data Failed! Data Addr is NULL\n");
        return -1;
    }
    m424 = (Header *)data;
    return 0;
}

/* @implements 0x10b8b0 us _ZN5Radio5CData8f_10b8b0Ev
   WHAT IT DOES: Drops the table data. Returns -1 when none was set, else 0. */
int CData::f_10b8b0()
{
    int r = 0;
    if (m424)
        m424 = 0;
    else {
        f_093f90("RadioData: Error: Reset Table Data Failed! Table Data has been Not Set yet\n");
        r = -1;
    }
    return r;
}

/* @draft 0x10b8f4 us _ZN5Radio5CData8f_10b8f4Et
   WHAT IT DOES: Returns the sub header of the table with the given id, or 0.
   DRAFT: retail holds the found pointer in a3 and the table count in t0; here those two
   registers are swapped. */
Sub *CData::f_10b8f4(unsigned short table)
{
    Header *h = m424;
    if (!h) {
        f_093f90("RadioData: Error: Get Table SubHeader Failed! Table Data has been Not Set yet\n");
        return 0;
    }
    Sub *s = h->sub;
    int n = h->num;
    for (int i = 0; i < n; i++, s++) {
        Sub *r = s;
        if (r->id == table)
            return r;
    }
    f_093f90("RadioData: GetTableSubHeader Failed! Not Found Table[%d]\n", table);
    return 0;
}

/* @implements 0x10b96c us _ZN5Radio5CData8f_10b96cEt
   WHAT IT DOES: Returns the index of the table with the given id, or -1. */
int CData::f_10b96c(unsigned short table)
{
    Header *h = m424;
    if (!h) {
        f_093f90("RadioData: GetTableIndex Failed! Table Data has been Not Set yet\n");
        return -1;
    }
    int n = h->num;
    Sub *s = h->sub;
    for (int i = 0; i < n; i++, s++)
        if (s->id == table)
            return i;
    f_093f90("RadioData: GetTableIndex Failed! Not Found Table[%d]\n", table);
    return -1;
}

/* @implements 0x10b9e4 us _ZN5Radio5CData8f_10b9e4EPNS_3OptEPNS_3EntE
   WHAT IT DOES: Tells whether the entry fits the per-speaker options: each speaker set in
   both must pass the condition helper's test. */
int CData::f_10b9e4(Opt *opt, Ent *e)
{
    for (int i = 0; i < 6; i++) {
        if (opt->v[i] >= 0 && e->spk[i] >= 0) {
            if (!m436->f_10bd70(opt->v[i], i, e))
                return 0;
        }
    }
    return 1;
}

/* @implements 0x10ba78 us _ZN5Radio5CData8f_10ba78Et
   WHAT IT DOES: Returns script entry i counted over all tables, or 0. */
Ent *CData::f_10ba78(unsigned short i)
{
    int n = f_10b554();
    if (i >= n) {
        f_093f90("RadioData: GetTableAttr2 Failed! Invalid Index[%d] ScrTotal[%d]\n", i, n);
        return 0;
    }
    Header *h = m424;
    if (!h) {
        f_093f90("RadioData: GetTableAttr2 Failed! Table Data has been Not Set yet\n");
        return 0;
    }
    return (Ent *)((char *)h + h->sub[0].off) + i;
}

/* @implements 0x10bb08 us _ZN5Radio5CData8f_10bb08Ett
   WHAT IT DOES: Tells whether the script's replay gap has passed since its last play (always
   when never played). With a gap, also asks the player whether it is queued or playing; the
   answer is not used. */
int CData::f_10bb08(unsigned short id, unsigned short again)
{
    if (again != 0) {
        if (D_27f09c->f_0f7404(id) == 1 || D_27f09c->f_0f75b0(id) == 1) {
        }
    }
    unsigned int t = m416[id];
    if (t == 0)
        return 1;
    if (t < m428)
        return again * 100 < (m428 - t) * 16;
    f_093f90("RadioData: IsAgainTimeOk Failed! Invalid AaginCnt[%d][%d] FrameCnt\n", id, t, m428);
    return 0;
}

/* @implements 0x10bbdc us _ZN5Radio5CData8f_10bbdcEv
   WHAT IT DOES: Empties the log. */
void CData::f_10bbdc()
{
    m8 = m4 = m0 = 0;
}

/* @implements 0x10bbec us _ZN5Radio5CData8f_10bbecEPNS_3EntE
   WHAT IT DOES: Adds the entry to the log, dropping the oldest when it holds LogMax. */
int CData::f_10bbec(Ent *e)
{
    int count = m0;
    int tail = m8;
    int head = m4;
    if (count >= m412) {
        if (++head >= m412)
            head = 0;
    } else
        count++;
    m0 = count;
    m4 = head;
    m12[tail] = e;
    tail++;
    if (tail >= m412)
        tail = 0;
    m8 = tail;
    return 0;
}

static inline bool InQue(Ent *e)
{
    return D_27f09c->f_0f74c0(e) == 1;
}

/* @draft 0x10bc58 us _ZN5Radio5CData8f_10bc58EPNS_3EntE
   WHAT IT DOES: Tells whether the entry (as f_10b6f0 compares) is in the log or the
   player's queue.
   DRAFT: retail computes the queue test into v0 and copies it to the result register v1;
   here it lands in v1 directly (one word short). */
int CData::f_10bc58(Ent *e)
{
    int pos = m4;
    for (int i = 0; i < m0; i++) {
        if (f_10b6f0(e, m12[pos]) == 1)
            return 1;
        pos++;
        if (pos >= m412)
            pos = 0;
    }
    return InQue(e);
}

}
