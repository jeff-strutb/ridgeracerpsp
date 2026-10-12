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
    inline void Set(const struct Name &n);
    inline Pair(const struct Name &n);
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


inline Pair::Pair(const Name &n)
{
    a = n.a;
    b = n.b;
}

inline void Pair::Set(const Name &n)
{
    a = n.a;
    b = n.b;
}

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

/* Three options kept together. */
struct Choice3 {
    int a;
    int b;
    int c;
};

/* The race setup record (652 bytes; saved and loaded byte for byte). */
struct RaceSetup {
    Name seq;
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
    struct GhostData *m580;
    struct GhostData *m584;
    int m588;
    int m592;
    int m596;
    Choice3 opt[3];
    int m636;
    int m640;
    int m644;
    int m648;

    inline void SetOptions();
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
/* The rules object of the race being run, made for the race's mode. */
class CRaceRule {
public:
    virtual ~CRaceRule();
    virtual void v8();
    virtual void *v12();
    virtual void v16();
    int m4[5];
    int m24;
    int m28[3];
    Ghost *m40;
    int m44[4];
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
};
extern CRaceRule *D_1ee47c;

/* A ghost record: the recorded runs of up to 16 cars. */
struct GhostTrack {
    int f_044608(int i);
    void f_04461c(int i);
    int f_044644(int i);
    void f_0447ac(void *data, int size);
    void f_044c3c(int i);
};
struct GhostData {
    int m0[3];
    GhostTrack track;
    void f_037c34();
    void f_037d0c();
    void f_037d30(int a, int b);
};
extern GhostData D_1ee480;
extern GhostData D_20f0cc;

/* The wireless session. */
struct Session {
    void f_03fe1c();
};
extern Session D_240900;

extern int D_1ee198;
extern int D_1ee19c;
extern int D_1ee1a0;
extern int D_1ee1a4;
extern int D_1ee1a8;
extern Choice3 D_1ee1ac[3];
extern int D_1ee1d0;
extern int D_1ee1d4[2];
extern int D_1ee1dc[2];
extern int D_1ee1e4[2];
extern int D_1ee1ec;
extern int D_1d1638[2];
extern int D_1d1640;
extern int D_1d1644;
extern int D_1d1648;

extern "C" {
int f_01fa10(int);
int f_01fad0(int);
}

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

/* The row of a table whose selection number is the given one. */
static inline void FindSelect(Name &out, CTable &t, int num)
{
    int i;

    for (i = 0; i < t.nRows; i++) {
        void *rec = t.Get("SelectNum", 0, i);
        memcpy(D_24063c, rec, D_1a211c[1]);
        if (num == D_24063c[0])
            break;
    }
    out.Set(t, t.Row(i));
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
    FindSelect(id, D_2407a8, course);
    return D_1a0e48[D_2407a8.Index((const char *)id.a)];
}

/* @implements 0x014b9c us f_014b9c
   WHAT IT DOES: Turns a car number of the menus into the car's class (0 to 6): it finds the
   car table row whose selection number matches and reads the class from the car's record. */
int f_014b9c(int car)
{
    Name id;

    FindSelect(id, D_240740, car);
    void *rec = D_240740.Get("Class", (const char *)id.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    int c = D_24063c[0];
    if (c >= 7)
        c = 6;
    return c;
}

/* Names the row of a table with the given name. */
static inline void Lookup(Name &out, const char *name)
{
    Name n = D_2407d0.Find(name);
    out = D_2407d0.Find((const char *)n.a);
}

/* @implements 0x014cf8 us f_014cf8
   WHAT IT DOES: Selects the wireless time trial race sequence for the given two numbers
   ("wt_<a>_<b>"), forward direction. */
void f_014cf8(int a, int b)
{
    sprintf(D_22fd38, "wt_%d_%d", a, b);
    Lookup(D_1ee1f0.seq, D_22fd38);
    D_1ee1f0.m636 = 0;
    D_1dd6b0.m276.Set(D_1ee1f0.seq);
}

/* @implements 0x014dd0 us f_014dd0
   WHAT IT DOES: Selects the single race sequence for the chosen course and car
   ("sr_<course>_c<class>"), in the course's direction. */
void f_014dd0(int course, int car)
{
    bool reverse = 0;
    int c = f_014a4c(course, &reverse);
    int cls = f_014b9c(car);
    sprintf(D_22fd58, "sr_%02d_c%d", c, cls);
    Lookup(D_1ee1f0.seq, D_22fd58);
    D_1ee1f0.m636 = reverse;
    D_1dd6b0.m276.Set(D_1ee1f0.seq);
}

/* @implements 0x014ec8 us f_014ec8
   WHAT IT DOES: Selects the time attack sequence for the chosen course ("ta_<course>"), in the
   course's direction, and clears the ghost choice. */
void f_014ec8(int course)
{
    bool reverse = 0;
    int c = f_014a4c(course, &reverse);
    sprintf(D_22fd78, "ta_%02d", c);
    Lookup(D_1ee1f0.seq, D_22fd78);
    D_1ee1f0.m636 = reverse;
    D_1ee1f0.m576 = 0;
    D_1dd6b0.m276.Set(D_1ee1f0.seq);
}

/* @implements 0x014fb0 us f_014fb0
   WHAT IT DOES: Selects the wireless battle sequence for the chosen course ("wb_<course>_c1"),
   in the course's direction. */
void f_014fb0(int course)
{
    bool reverse = 0;
    int c = f_014a4c(course, &reverse);
    sprintf(D_22fd98, "wb_%02d_c1", c);
    Lookup(D_1ee1f0.seq, D_22fd98);
    D_1ee1f0.m636 = reverse;
    D_1dd6b0.m276.Set(D_1ee1f0.seq);
}

/* @draft 0x0150a0 us f_0150a0
   WHAT IT DOES: Returns the course of the current race sequence: the course table row named by
   the sequence's course number.
   Remaining difference: the course row's slot is at sp+16 here and sp+32 in retail (retail
   has one more 16 byte stack slot before it); the 4 words that address it differ. */
Pair f_0150a0()
{
    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    void *num = D_2407d0.Get("CourseNumber", (const char *)seq.a, 0);
    Name course = D_2407a8.Find((const char *)num);
    return course;
}

/* @draft 0x01515c us f_01515c
   WHAT IT DOES: Returns the number of laps of the current race sequence. */
int f_01515c()
{
    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    void *rec = D_2407d0.Get("Laps", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    return D_24063c[0];
}

/* @draft 0x0151e8 us f_0151e8
   WHAT IT DOES: Returns the ghost choice of the setup. */
int f_0151e8()
{
    return D_1ee1f0.m576;
}

/* @draft 0x0151f4 us f_0151f4
   WHAT IT DOES: Tells whether the course is run in reverse. */
bool f_0151f4()
{
    return D_1ee1f0.m636 != 0;
}

/* Copies the chosen race options into the setup. */
inline void RaceSetup::SetOptions()
{
    int j;

    m588 = D_1ee1a4;
    m592 = D_1ee1a8;
    for (j = 0; j < 3; j++)
        opt[j] = D_1ee1ac[j];
    m596 = D_1ee1ec;
}

/* Tells whether the record just read is of the given race mode. */
static inline bool IsMode(int mode)
{
    return D_24063c[0] == mode;
}

/* @draft 0x015204 us f_015204
   WHAT IT DOES: Builds the setup for a race from the player's choices: picks which ghost
   record is written and which is played against, copies the chosen options, clears the
   second car (unless the sequence is a two player one) and every rival, reads the laps and
   the rivals' level of the sequence, and fills in each player's car (from its selection
   number), colour and options. Then it resets the sequence manager. */
void f_015204()
{
    int i;

    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    D_1ee480.f_037d30(0, 0);
    D_20f0cc.f_037d30(0, 1);
    D_1ee1f0.m580 = !D_2407f8 ? &D_1ee480 : &D_20f0cc;
    D_1ee1f0.m584 = !D_2407f8 ? &D_20f0cc : &D_1ee480;
    D_1ee1f0.m24 = 0;
    D_240900.f_03fe1c();
    D_1ee1f0.SetOptions();
    void *rec = D_2407d0.Get("SequenceNumber", (const char *)D_1ee1f0.seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    if (!IsMode(2)) {
        for (i = 1; i < 2; i++) {
            D_1dd6b0.f_00317c(i, Pair());
            D_1ee1f0.car[i] = Pair();
            D_1ee1f0.ClearPlayer(i);
        }
    }
    for (i = 0; i < 13; i++) {
        D_1dd6b0.f_003150(i, Pair());
        D_1ee1f0.rival[i] = Pair();
        D_1ee1f0.m184[i] = -1;
        D_1ee1f0.m304[i] = -1;
        D_1ee1f0.m356[i] = -1;
    }
    D_1ee1f0.m8 = D_1ee19c;
    D_1ee1f0.m20 = D_1ee1a0;
    D_1ee1f0.m640 = D_1d1640;
    D_1ee1f0.m644 = D_1d1644;
    D_1ee1f0.m648 = D_1d1648;
    int size = D_1a211c[1];
    rec = D_2407d0.Get("Laps", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, size);
    D_1ee1f0.m12 = D_24063c[0];
    rec = D_2407d0.Get("CCar_Level", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, size);
    D_1ee1f0.m16 = D_24063c[0];
    for (i = 0; i < D_1ee1d0; i++) {
        int num = D_1ee1d4[i];
        int k;
        for (k = 0; k < D_240740.nRows; k++) {
            rec = D_240740.Get("SelectNum", 0, k);
            memcpy(D_24063c, rec, D_1a211c[1]);
            if (num == D_24063c[0])
                break;
        }
        D_1ee1f0.car[i] = D_240740.Find(D_240740.Row(k));
        if (D_1d1638[i] < 0) {
            D_1ee1f0.m288[i] = -1;
            D_1ee1f0.m296[i] = -1;
        } else {
            D_1ee1f0.m288[i] = f_01fa10(D_1d1638[i]);
            D_1ee1f0.m296[i] = f_01fad0(D_1d1638[i]);
        }
        D_1ee1f0.m48[i] = i;
        D_1ee1f0.m64[i] = D_1ee1dc[i];
        D_1ee1f0.m72[i] = D_1ee1e4[i];
    }
    D_1dd6b0.f_0057d0();
    D_1dd6b0.f_0030c8(0);
}
