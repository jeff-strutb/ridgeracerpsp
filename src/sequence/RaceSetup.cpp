/* The race setup (retail 0x014950 to 0x01797c): the record that describes the race about to be
   run (its sequence, course, laps, the cars of the player and of the rivals, the ghosts), the
   lookups that turn menu choices into that record through the course, car and race tables, the
   copy of the record into the sequence manager, and its save and load through a byte stream
   (the replay and ghost data). */

#include <stdio.h>
#include <string.h>

extern "C" {
void *memcpy(void *, const void *, size_t);
}

/* Two words kept together: a name in a table and its row, or any value pair. */
struct Pair {
    int a;
    int b;
    Pair() { a = 0; }
    Pair(int v) { a = v; }
};

/* A row of a table named by its interned name. */
struct Name {
    int a;
    int b;
    Name() {}
    Name(const Name &o) { a = o.a; b = o.b; }
    inline void Set(struct CTable &t, const char *name);
};


/* A table of the game database: named columns and named rows over a string pool. */
struct CTable {
    int m0;
    int nCols;
    int nRows;
    int m12;
    int m16;
    int *colNames;
    int *rowNames;
    int m28;
    int m32;
    char *strings;

    const char *f_036984(const char *name, int add, int *names, int count);
    void *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
    int f_036a3c(const char *name, int *names, int count);

    const char *Row(int i) { return f_036984(0, i, rowNames, nRows); }
    int Index(const char *name) { return f_036a3c(name, rowNames, nRows); }
    void *Get(const char *col, const char *row, int i) { return f_0368e8(col, row, 0, i); }
    Name Find(const char *name)
    {
        Name r;
        if (name)
            r.a = (int)f_036984(name, 0, rowNames, nRows);
        else
            r.a = 0;
        return r;
    }
};


/* Names the row of the table with the given name (its interned name), none for no name. */
inline void Name::Set(CTable &t, const char *name)
{
    if (name)
        a = (int)t.f_036984(name, 0, t.rowNames, t.nRows);
    else
        a = 0;
}

/* The part of the sequence manager the setup writes. */
class CSequence {
public:
    char m0[276];
    Pair m276;
    int m284;
    char m288[4];
    int m292;
    char m296[24];
    int m320;

    void f_0030c8(int v);
    void f_0030d0(Pair p);
    void f_003150(int i, Pair p);
    void f_00317c(int i, Pair p);
    void f_0057d0();
    int f_005c34(const char *name);
};

/* The race setup record (652 bytes; saved and loaded byte for byte). */
struct RaceSetup {
    Pair seq;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    Pair car[2];
    int m48[2];
    int m56[2];
    int m64[2];
    int m72[2];
    Pair rival[13];
    int m184[13];
    int m236[13];
    int m288[2];
    int m296[2];
    int m304[13];
    int m356[13];
    char name[8][20];
    int m568;
    int m572;
    int m576;
    void *m580;
    void *m584;
    int m588;
    int m592;
    int m596;
    int m600[3][3];
    int m636;
    int m640;
    int m644;
    int m648;

    void ClearPlayer(int i)
    {
        m48[i] = -1;
        m288[i] = -1;
        m296[i] = -1;
        m64[i] = 0;
        m72[i] = 0;
    }
};

extern CSequence D_1dd6b0;
extern RaceSetup D_1ee1f0;
extern CTable D_2407a8;
extern CTable D_240740;
extern CTable D_2407d0;
extern int D_2407f8;
extern int D_240800;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern const int D_1a0e48[];
extern char D_22fd38[];
extern char D_22fd58[];
extern char D_22fd78[];
extern char D_22fd98[];

struct Ghost {
    char m0[36];
    int m36;
    int m40;
};
struct GhostHolder {
    char m0[40];
    Ghost *m40;
};
extern GhostHolder *D_1ee47c;

/* @implements 0x014950 us f_014950
   WHAT IT DOES: Clears the parts of the setup that describe the second car and the ghosts:
   no ghost and no rival record, the wireless flag off, and the second car slot of the sequence
   manager emptied. */
void f_014950()
{
    D_1ee1f0.m568 = -1;
    D_1ee1f0.m28 = -1;
    D_1ee1f0.m572 = -1;
    D_1ee1f0.m576 = 0;
    D_2407f8 = 0;
    for (int i = 1; i < 2; i++) {
        D_1dd6b0.f_00317c(i, Pair());
        D_1ee1f0.car[i] = Pair();
        D_1ee1f0.ClearPlayer(i);
    }
}

/* @implements 0x0149e8 us f_0149e8
   WHAT IT DOES: Tells whether the current race mode is one of the two ghost modes (2 or 6). */
int f_0149e8()
{
    return D_240800 == 2 || D_240800 == 6;
}

/* @implements 0x014a08 us f_014a08
   WHAT IT DOES: Returns a value of the current ghost, 0 when there is none. */
int f_014a08()
{
    Ghost *g = D_1ee47c->m40;
    if (g)
        return g->m36;
    return 0;
}

/* @implements 0x014a28 us f_014a28
   WHAT IT DOES: Takes the pending value of the current ghost (clearing it), 0 when there is no
   ghost. */
int f_014a28()
{
    Ghost *g = D_1ee47c->m40;
    int r = 0;
    if (g) {
        r = g->m40;
        g->m40 = 0;
    }
    return r;
}

/* The course table row whose selection number is the given course. */
static inline void FindCourse(Name &out, int course)
{
    int i;

    for (i = 0; i < D_2407a8.nRows; i++) {
        void *rec = D_2407a8.Get("SelectNum", 0, i);
        memcpy(D_24063c, rec, D_1a211c[1]);
        if (course == D_24063c[0])
            break;
    }
    out.Set(D_2407a8, D_2407a8.Row(i));
}

/* @implements 0x014a4c us f_014a4c
   WHAT IT DOES: Turns a course number of the menus into the course's entry: numbers past 24
   are the reverse layouts of 1 to 24 (the flag is set). It finds the course table row whose
   selection number matches and returns the course value listed for that row. */
int f_014a4c(int course, bool *reverse)
{
    Name id;

    *reverse = 0;
    if (course >= 25) {
        *reverse = 1;
        course -= 24;
    }
    FindCourse(id, course);
    return D_1a0e48[D_2407a8.Index((const char *)id.a)];
}
