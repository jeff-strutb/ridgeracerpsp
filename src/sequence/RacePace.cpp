/* The race pace object file (retail 0x03fe80 to 0x0414b4). It picks the computer cars' pace
   for a race from the "ComCarPace" and "Pace_%s" databases, draws the random choices among
   equally good candidates, and makes and clears the race's per car record and the pace
   database. */

/* Constructs an object in place. */
inline void *operator new(unsigned int, void *p)
{
    return p;
}

#include <stdio.h>
#include <string.h>

/* The game database's tables (their own object file). */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
};
extern CTable D_2407d0;
extern unsigned char D_24063c[];
extern const int D_1a2120;
extern const int D_1a211c[];
char *f_0368e8(CTable *t, const char *field, char *rec, int a, int i);

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};

/* Whether a sequence record has the given sequence number. */
inline bool IsSequence(const Rec &r, int n)
{
    char *f = f_0368e8(&D_2407d0, "SequenceNumber", r.rec, 0, 0);
    memcpy(D_24063c, f, D_1a2120);
    return D_24063c[0] == n;
}

namespace DB {
/* A database read from a package (its own object file). */
class CDataBase {
public:
    CDataBase() { f_0368b0(); }
    virtual ~CDataBase() {}
    virtual void f_03680c(void *data);
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void f_0368b0();
    int m4[9];
    /* The pace tables read from the package. */
    float m40, m44, m48, m52, m56, m60, m64, m68;
    float m72[13];
    float m124[13];
    float m176[13];
    float m228, m232, m236;
    int m240[3];
};
}

extern "C" void f_041030(DB::CDataBase *db, void *data, int flag);

/* The sequence manager (its own object file). */
struct CSequence {
    void *f_005c34(const char *name);
    void f_005d4c(const char *name);
    char m0[276];
    Rec m276;
};
extern CSequence D_1dd6b0;

/* A wireless link name (its own object file; passed by reference as it has a destructor). */
struct NetName {
    char m0[17];
    signed char m17[11];
    ~NetName();
};

/* One player entry of the wireless link. */
struct LinkEntry {
    char m0[10];
    signed char state;
    signed char id;
    char m12[6];
    signed char used;
    unsigned char m19;
    unsigned int colours;
    char m24[16];
};

/* The wireless link. */
struct Link {
    int m0;
    int m4;
    char m8[85];
    signed char m93;
    char m94[74];
    LinkEntry entry[8];
    int f_0859b4();
};
extern Link D_241810;

/* The race's per car record (cleared by its own function). */
struct RaceCars {
    Rec seq;
    unsigned int seed;
    int cls;
    int count;
    Rec cars[13];
    int m124[13];
    int m176[13];
    int m228[13];
    int m280[13];
    int m332;
    int m336;
    char names[14][20];
    void f_03fe1c();
    void f_03fe80(const int &mode, const Rec &seq, int c1, int c2);
    void f_0408b8(NetName n);
};
extern RaceCars D_240900;
extern DB::CDataBase D_240af4;

/* A random source: a seed stepped by the usual linear congruence. */
struct RandOwner {
    int m0[2];
    unsigned int seed;
};

char *f_036984(CTable *t, char *key, int i, int *index, int count);
extern CTable D_240740;
void f_040dfc(int arg);
int f_040e44(RandOwner *o, int *vals, int *pn);
int f_01fa10(int i);
int f_01fad0(int i);

/* The first byte of a cell of a table, copied out. */
inline unsigned char ByteCell(CTable *t, const char *field, char *rec, int bs)
{
    memcpy(D_24063c, f_0368e8(t, field, rec, 0, 0), bs);
    return D_24063c[0];
}

/* The same with the cell size read afresh after the lookup. */
inline unsigned char ByteCell(CTable *t, const char *field, char *rec)
{
    char *f = f_0368e8(t, field, rec, 0, 0);
    memcpy(D_24063c, f, D_1a211c[1]);
    return D_24063c[0];
}

/* Whether a sequence record has the given sequence number (the cell size read afresh). */
inline bool IsSeqF(const Rec &r, int n)
{
    return ByteCell(&D_2407d0, "SequenceNumber", r.rec) == n;
}

/* Whether a sequence record has the given sequence number (the cell size already read). */
inline bool IsSeq(const Rec &r, int n, int bs)
{
    return ByteCell(&D_2407d0, "SequenceNumber", r.rec, bs) == n;
}

/* The record of a car table row: the key of the row, then the record under that key. */
inline char *CarRow(int i)
{
    char *k = f_036984(&D_240740, 0, i, D_240740.index, D_240740.count);
    return k ? f_036984(&D_240740, k, 0, D_240740.index, D_240740.count) : 0;
}

/* The record a sequence record names in a car table column. */
inline char *RivalRec(const char *field, const Rec &r)
{
    char *k = f_0368e8(&D_2407d0, field, r.rec, 0, 0);
    return k ? f_036984(&D_240740, k, 0, D_240740.index, D_240740.count) : 0;
}

/* @draft 0x03fe80 us _ZN8RaceCars8f_03fe80ERKiRK3Recii
   WHAT IT DOES: makes the race's per car record from the race table: the sequence, the class and
   number of the computer cars, the loading of the pace database for the story sequences, then
   for each computer car picks (at random among the best scored candidates of the class) a car
   from the car table, scoring a pick down against cars already chosen (the same car, the same
   make) and capping how many distinct picks and makes are allowed; unused slots are cleared,
   and the pace pairs (matching the two given selectors) are drawn by the same random pick.
   DRAFT: first transcription. */
void RaceCars::f_03fe80(const int &mode, const Rec &seq, int c1, int c2)
{
    int vals[16];
    Rec pairs[13];
    unsigned char got[13];
    unsigned char same[13];
    Rec tmp;
    Rec z;
    int counts[24];
    int n;
    int n2;
    int c356;
    int c360;
    int i, j, k, s;
    int bs;
    char *f;

    this->seq = seq;
    seed = mode;
    f = f_0368e8(&D_2407d0, "CCar_Level", seq.rec, 0, 0);
    memcpy(D_24063c, f, bs = D_1a211c[1]);
    cls = D_24063c[0];
    count = ByteCell(&D_2407d0, "CCar_Num", seq.rec, bs);
    m332 = 13;
    if (IsSeq(seq, 1, bs) || IsSeq(seq, 4, bs) || IsSeq(seq, 5, bs))
        f_040dfc(ByteCell(&D_2407d0, "CCar_Each", this->seq.rec));
    n = 0;
    c356 = 0;
    c360 = 0;
    for (i = 0; i < 13; i++) {
        vals[i] = 0;
        tmp.rec = 0;
        pairs[i] = tmp;
        got[i] = 0;
        same[i] = 0;
    }
    if (cls) {
        for (i = 0; i < D_240740.count; i++) {
            tmp.rec = CarRow(i);
            if (ByteCell(&D_240740, "Class", tmp.rec) == cls) {
                pairs[n] = tmp;
                n++;
                if (n == 13)
                    break;
            }
        }
        for (k = 0; k < count; k++) {
            s = f_040e44((RandOwner *)this, vals, &n);
            cars[k] = pairs[s];
            if (IsSeqF(this->seq, 5))
                m228[k] = (k + 11) % 12;
            else
                m228[k] = k;
            vals[s] += 9;
            if (!got[s]) {
                got[s] = 1;
                if (c360 < 8)
                    c360++;
                else
                    for (j = 0; j < n; j++)
                        if (!got[j])
                            vals[j] += 999;
            }
            if (same[s]) {
                for (j = 0; j < n; j++)
                    if (f_0368e8(&D_240740, "CarName", cars[k].rec, 0, 0) == f_0368e8(&D_240740, "CarName", pairs[j].rec, 0, 0))
                        vals[j] += 3;
            } else {
                for (j = 0; j < n; j++)
                    if (f_0368e8(&D_240740, "CarName", cars[k].rec, 0, 0) == f_0368e8(&D_240740, "CarName", pairs[j].rec, 0, 0)) {
                        same[j] = 1;
                        vals[j] += 3;
                    }
                if (c356 < 2)
                    c356++;
                else
                    for (j = 0; j < n; j++)
                        if (!same[j])
                            vals[j] += 999;
            }
        }
    } else {
        pairs[0].rec = RivalRec("CCar_Rival0", seq);
        pairs[1].rec = RivalRec("CCar_Rival1", seq);
        n = 2;
    }
    if (ByteCell(&D_2407d0, "CCar_Each", this->seq.rec)) {
        if (!cls) {
            cars[0].rec = RivalRec("CCar_Rival0", seq);
            cars[1].rec = RivalRec("CCar_Rival1", seq);
            cars[2].rec = RivalRec("CCar_Rival2", seq);
        }
        m228[0] = 22;
        m228[1] = 23;
        m228[2] = 24;
        m332 = 25;
    }
    for (k = count; k < 13; k++) {
        z.rec = 0;
        cars[k] = z;
        m124[k] = -1;
        m176[k] = -1;
        m228[k] = -1;
    }
    n2 = 24;
    for (i = 0; i < n2; i++) {
        if (f_01fa10(i) == c1 && f_01fad0(i) == c2)
            counts[i] = 1;
        else
            counts[i] = 0;
    }
    for (k = 0; k < count; k++) {
        if (ByteCell(&D_240740, "Class", cars[k].rec) == 7) {
            m124[k] = -1;
            m176[k] = -1;
        } else {
            s = f_040e44((RandOwner *)this, counts, &n2);
            m124[k] = f_01fa10(s);
            m176[k] = f_01fad0(s);
            counts[s]++;
        }
    }
}

/* A 565 colour kept in the top half of a word, as 24 bit colour (-1 when the flag is set). */
inline int Colour565(unsigned int c)
{
    if (c & 0x8000)
        return -1;
    return ((c >> 27) * 255 / 31 << 16) + ((c >> 21 & 63) * 255 / 63 << 8) + (c >> 16 & 31) * 255 / 31;
}

/* A 555 colour kept in the bottom half of a word, as 24 bit colour (-1 when the flag is set). */
inline int Colour555(unsigned int c)
{
    if (c & 0x8000)
        return -1;
    return ((c >> 10 & 31) * 255 / 31 << 16) + ((c >> 5 & 31) * 255 / 31 << 8) + (c & 31) * 255 / 31;
}

/* @draft 0x0408b8 us _ZN8RaceCars8f_0408b8E7NetName
   WHAT IT DOES: makes the per car record from the wireless link: the player count (the link's
   count less one), the host's id and name, then for every player in use (entries 1 to 7) the
   car whose select number matches, both of its colours as 24 bit colours, its id, the name
   index of that id and the player's name; the unused slots are cleared.
   DRAFT: first transcription. */
void RaceCars::f_0408b8(NetName n)
{
    Rec z;
    int j;
    int i, k, s;
    LinkEntry *h;
    LinkEntry *e;

    count = D_241810.f_0859b4() - 1;
    h = &D_241810.entry[0];
    m336 = h->id;
    m332 = n.m17[h->id] + 13;
    strcpy(names[0], h->m0);
    j = 0;
    for (i = 1, e = &D_241810.entry[1]; i < 8; i++, e++) {
        if (e->used) {
            Rec *c = &cars[j];
            int sel = e->m19;
            for (s = 0; s < D_240740.count; s++) {
                memcpy(D_24063c, f_0368e8(&D_240740, "SelectNum", 0, 0, s), D_1a211c[1]);
                if (sel == D_24063c[0])
                    break;
            }
            c->rec = CarRow(s);
            m124[j] = Colour565(e->colours);
            m176[j] = Colour555(e->colours);
            m280[j] = e->id;
            m228[j] = n.m17[e->id] + 13;
            strcpy(names[j], e->m0);
            j++;
        }
    }
    for (k = count; k < 13; k++) {
        z.rec = 0;
        cars[k] = z;
        m124[k] = -1;
        m176[k] = -1;
        m228[k] = -1;
        m280[j] = -1;
    }
}

/* @draft 0x040c90 us f_040c90
   WHAT IT DOES: for the sequences numbered 1, 4 and 5, loads the pace package named after the
   current sequence ("Pace_<name>").
   Remaining difference: only the saved register numbering. Retail gives the copy size
   (D_1a2120) s1 and the table, field name and buffer addresses s2 to s5; here the size is s5
   (global-alloc takes the size last; same pattern as 0x0897ec). Reading the size into a local
   before the lookup moves its load above the call (66 words, worse). */
void f_040c90()
{
    char name[64];
    Rec r = D_1dd6b0.m276;
    if (r.rec) {
        if (IsSequence(r, 1) || IsSequence(r, 4) || IsSequence(r, 5)) {
            Rec c = D_1dd6b0.m276;
            sprintf(name, "Pace_%s", c.rec);
            D_1dd6b0.f_005d4c(name);
        }
    }
}

/* @implements 0x040dfc us f_040dfc
   WHAT IT DOES: loads the computer car pace database from the "ComCarPace" package entry. */
void f_040dfc(int arg)
{
    f_041030(&D_240af4, D_1dd6b0.f_005c34("ComCarPace"), arg);
}

/* @implements 0x040e44 us f_040e44
   WHAT IT DOES: picks at random one of the indices whose value is the smallest of the n given
   values (below 99999), stepping the owner's random seed. */
int f_040e44(RandOwner *o, int *vals, int *pn)
{
    int list[256];
    int best = 99999;
    int cnt = 0;
    for (int i = 0; i < *pn; i++)
        list[i] = -1;
    for (int j = 0; j < *pn; j++) {
        int v = vals[j];
        if (v < best) {
            best = v;
            list[0] = j;
            for (int k = 1; k < *pn; k++)
                list[k] = -1;
            cnt = 1;
        } else if (v == best) {
            list[cnt] = j;
            cnt++;
        }
    }
    o->seed = o->seed * 0x19660d + 0x3c6ef35f;
    return list[(int)((float)(int)(o->seed >> 8) * 5.9604645e-08f * (float)cnt)];
}

/* @draft 0x040f54 us f_040f54
   WHAT IT DOES: for every car (0xffff): mode 1 makes the per car record and the pace
   database, mode 0 takes the database down.
   Remaining difference: retail tests the make flag again after the record's call (it stays in
   s0); here the two tests are merged, the second body following the first. RTL: pass 03
   (jump) threads only the false edge; cse (pass 09) follows the fall-through through the call
   and folds the second make == 0 test from the first jump's recorded condition. */
void f_040f54(int mode, int car)
{
    int all = car == 0xffff;
    int make = all && mode == 1;
    if (make) {
        D_240900.seed = 0;
        D_240900.f_03fe1c();
    }
    if (make)
        new (&D_240af4) DB::CDataBase;
    if (all && mode == 0)
        D_240af4.DB::CDataBase::~CDataBase();
}

/* @implements 0x040ff0 us f_040ff0
   WHAT IT DOES: makes the record and the database for every car. */
void f_040ff0()
{
    f_040f54(1, 0xffff);
}

/* @implements 0x041010 us f_041010
   WHAT IT DOES: takes the database down for every car. */
void f_041010()
{
    f_040f54(0, 0xffff);
}

/* @implements 0x041030 us f_041030
   WHAT IT DOES: reads the computer car pace tables from the loaded package into the database
   object: the rate and the minimum and maximum distances of the behind and the forward pace
   (with the slope between them), the dash time and rates and the normal rates of the 13 cars,
   and the easy pace base, ratio and offset; then picks the three cars with the best normal rate
   (among the first three when the flag is set), skipping a car already picked.
   DRAFT: first transcription. */
#define S16 (*(short *)D_24063c)
extern "C" void f_041030(DB::CDataBase *db, void *data, int flag)
{
    int c, i, j;
    int a, b;
    char *f;
    float best;

    db->DB::CDataBase::f_03680c(data);
    f = f_0368e8((CTable *)db, "BHD_RATE", 0, 0, 0);
    memcpy(D_24063c, f, a = D_1a211c[2]);
    db->m40 = (float)S16 * 0.001f;
    f = f_0368e8((CTable *)db, "BHD_DIST_MIN", 0, 0, 0);
    memcpy(D_24063c, f, a);
    db->m44 = (float)S16;
    f = f_0368e8((CTable *)db, "BHD_DIST_MAX", 0, 0, 0);
    memcpy(D_24063c, f, a);
    db->m48 = (float)S16;
    db->m52 = (1.0f - db->m40) / (db->m48 - db->m44);
    f = f_0368e8((CTable *)db, "FWD_RATE", 0, 0, 0);
    memcpy(D_24063c, f, a);
    db->m56 = (float)S16 * 0.001f;
    f = f_0368e8((CTable *)db, "FWD_DIST_MIN", 0, 0, 0);
    memcpy(D_24063c, f, a);
    db->m60 = (float)S16;
    f = f_0368e8((CTable *)db, "FWD_DIST_MAX", 0, 0, 0);
    memcpy(D_24063c, f, a);
    db->m64 = (float)S16;
    db->m68 = (db->m56 - 1.0f) / (db->m64 - db->m60);
    for (c = 0; c < 13; c++) {
        f = f_0368e8((CTable *)db, "DSH_TIME_00", 0, c, 0);
        memcpy(D_24063c, f, D_1a211c[1]);
        db->m72[c] = (float)D_24063c[0];
        f = f_0368e8((CTable *)db, "DSH_RATE_00", 0, c, 0);
        memcpy(D_24063c, f, b = D_1a211c[2]);
        db->m124[c] = (float)S16 * 0.001f;
        f = f_0368e8((CTable *)db, "NRM_RATE_00", 0, c, 0);
        memcpy(D_24063c, f, b);
        db->m176[c] = (float)S16 * 0.001f;
    }
    f = f_0368e8((CTable *)db, "EASY_PACE_BASE", 0, 0, 0);
    memcpy(D_24063c, f, b);
    db->m228 = (float)S16 * 0.001f;
    f = f_0368e8((CTable *)db, "EASY_PACE_RATIO", 0, 0, 0);
    memcpy(D_24063c, f, b);
    db->m232 = (float)S16 * 0.001f;
    f = f_0368e8((CTable *)db, "EASY_PACE_OFFSET", 0, 0, 0);
    memcpy(D_24063c, f, b);
    db->m236 = (float)S16 * 0.001f;
    db->m240[2] = db->m240[1] = db->m240[0] = -1;
    for (j = 0; j < 3; j++) {
        best = 0.0f;
        for (i = 0; flag ? i < 3 : i < 13; i++)
            if (best < db->m176[i])
                if (i != db->m240[0] && i != db->m240[1]) {
                    db->m240[j] = i;
                    best = db->m176[i];
                }
    }
}
