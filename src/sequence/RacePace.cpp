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

extern "C" {
void f_041030(void *db, void *data, int arg);
}

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
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void f_0368b0();
    int m4[9];
};
}

/* The sequence manager (its own object file). */
struct CSequence {
    void *f_005c34(const char *name);
    void f_005d4c(const char *name);
    char m0[276];
    Rec m276;
};
extern CSequence D_1dd6b0;

/* The race's per car record (cleared by its own function). */
struct RaceCars {
    int m0[2];
    int m8;
    void f_03fe1c();
};
extern RaceCars D_240900;
extern DB::CDataBase D_240af4;

/* A random source: a seed stepped by the usual linear congruence. */
struct RandOwner {
    int m0[2];
    unsigned int seed;
};

/* @draft 0x040c90 us f_040c90
   WHAT IT DOES: for the sequences numbered 1, 4 and 5, loads the pace package named after the
   current sequence ("Pace_<name>").
   Remaining difference: only the saved register numbering. Retail gives the copy size
   (D_1a2120) s1 and the table, field name and buffer addresses s2 to s5; here the size is s5. */
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
   s0); here the two tests are merged, the second body following the first. */
void f_040f54(int mode, int car)
{
    int all = car == 0xffff;
    int make = all && mode == 1;
    if (make) {
        D_240900.m8 = 0;
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
