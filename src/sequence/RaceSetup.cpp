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
    Pair() {}
    Pair(int v) { a = v; }
    inline void Set(const struct Name &n);
    inline Pair(const struct Name &n);
    inline Pair(const struct Slot &s);
};

/* A name and row kept in a record (plain data, saved byte for byte). */
struct Slot {
    int a;
    int b;
    Slot &operator=(const Pair &p)
    {
        a = p.a;
        b = p.b;
        return *this;
    }
    inline Slot &operator=(const struct Name &n);
};

inline Pair::Pair(const Slot &s)
{
    a = s.a;
    b = s.b;
}

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


inline Slot &Slot::operator=(const Name &n)
{
    a = n.a;
    b = n.b;
    return *this;
}

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

/* The two players' cars; their setup code is in the next object file. */
struct Cars {
    Slot e[2];
    Cars() { f_017968(); }
    void f_017968();
    Slot &operator[](int i) { return e[i]; }
};

/* Three options kept together. */
struct Choice3 {
    int a;
    int b;
    int c;
};

extern int D_1ee1a4;

/* The race setup record (652 bytes; saved and loaded byte for byte). */
struct RaceSetup {
    Name seq;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    Cars car;
    int m48[2];
    int m56[2];
    int m64[2];
    int m72[2];
    Slot rival[13];
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

    RaceSetup() {}
    inline void SetOptions();
    void SetMode() { m588 = D_1ee1a4; }
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
extern const int D_1a0f28[];
extern char D_22fd38[];
extern char D_22fd58[];
extern char D_22fd78[];
extern char D_22fd98[];

struct Ghost {
    char m0[36];
    int m36;
    int m40;
};
/* The result of a race. */
struct RaceResult {
    int times[8];
};

/* The rules object of the race being run, made for the race's mode. */
class CRaceRule {
public:
    virtual ~CRaceRule();
    virtual void v8();
    virtual struct RaceResult *v12();
    struct RaceResult *Result()
    {
        struct RaceResult *r = v12();
        if (!r)
            return 0;
        return r;
    }
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

/* The course display object, reached through its accessor. */
class CCourseView {
public:
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void v12();
    virtual void v16();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v32();
    virtual void v36();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v52();
    virtual void v56();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v72();
    virtual void v76();
    virtual void *v80();
};
CCourseView *f_017970();

extern "C" {
void f_01797c(void);
int f_017a20(void);
void f_017ad8(void);
int f_0967c4(void *);
int f_077d38(void *, int);
CRaceRule *f_0396b0(int mode);
void f_0292fc(void *);
void f_038828(void);
}
void f_038780(const Name &seq);
extern char D_242cb0[];
extern char D_23c820[];
extern int D_1d3d3c;

/* A ghost record: the recorded runs of up to 16 cars. */
struct GhostTrack {
    int f_044608(int i);
    void f_04461c(int i);
    int f_044644(int i);
    void f_0447ac(void *data, int size);
    void f_044c3c(int i);
};
extern "C" {
void f_043fa4(void *);
void f_043fdc(void *);
}

/* The packer's dictionary (made and destroyed by the packer code). */
struct CodecDict {
    char m0[16];
    CodecDict() { f_043fa4(this); }
    ~CodecDict() { f_043fdc(this); }
};

/* Three counters of a packer channel. */
struct CodecCount {
    int a;
    int b;
    int c;
    void Clear()
    {
        a = 0;
        b = 0;
        c = 0;
    }
};

/* One channel of the packer. */
struct CodecChannel {
    int m0;
    int m4;
    CodecCount in;
    CodecCount out;
    int m32;
    int m36;
    int m40;
    int m44;
    bool m48;
    int m52;
    int m56;
    int m60;
    CodecChannel()
    {
        m0 = 0;
        m4 = 0;
        m32 = 1;
        m36 = 0;
        m40 = 0;
        m44 = 0;
        m48 = 0;
        m52 = 0;
        in.Clear();
        out.Clear();
        m60 = 0;
    }
};

/* The packer used for the saved replays: 16 channels of bytes packed into one stream. */
struct Codec {
    char m0[2056];
    CodecChannel ch[16];
    CodecDict dict;

    void f_0447ac(void *data, int size);
    int f_044608(int i);
    void f_04461c(int i);
    int f_044644(int i);
    void f_0449c0(int i, int byte);
    void f_044a28(int i);
    int f_044a68(int i);
    void f_044aa4(void *work, int n);
    void f_044b44(int i, int a);
    void f_044c3c(int i);
    void f_044d98();
};

extern "C" {
void f_037c34(void *);
void f_037d0c(void *);
}
struct GhostData {
    int m0[3];
    GhostTrack track;
    char m13[134220 - 13];
    GhostData() { f_037c34(this); }
    ~GhostData() { f_037d0c(this); }
    void f_037d30(int a, int b);
};
extern GhostData D_1ee480;
extern GhostData D_20f0cc;

/* The wireless session. */
extern "C" {
void f_083ac0(void *);
void f_083aec(void *);
}

/* A player's name entry of the wireless link (made and destroyed by the link code). */
struct NetName {
    int m0[6];
    unsigned char m24;
    NetName() { f_083ac0(this); }
    ~NetName() { f_083aec(this); }
    void f_083af4(int n);
    void f_083bd4(int id);
    void f_083c18();
};
extern NetName D_22fd18;

/* A counter of the link, cleared at program start. */
struct LinkCount {
    int n;
    LinkCount() { n = 0; }
};

/* The wireless session: the players of a wireless race and their choices. */
struct Session {
    int m0[4];
    int count;
    Pair cars[13];
    int m124[13];
    int m176[13];
    int m228[13];
    int m280[13];
    int m332;
    int m336;
    char name[20];
    char names[13][20];

    void f_03fe1c();
    void f_03fe80(const int &mode, const Name &seq, int c1, int c2);
    void f_0408b8(NetName n);
};
extern Session D_240900;

/* One player entry of the wireless link. */
struct LinkEntry {
    char m0[10];
    signed char state;
    signed char id;
    char m12[6];
    signed char used;
    char m19;
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
    int f_086324();
    int f_0859b4();
    void f_086b40();
    void f_086cb4();
};
extern Link D_241810;

/* The message queue of the wireless link. */
struct LinkQueue {
    void f_0840f4(NetName *n);
    int f_084150(NetName *n);
};
extern LinkQueue D_241804;
extern int D_1d164c;
extern unsigned char D_22fdb8;

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

RaceSetup D_1ee1f0;
GhostData D_1ee480;
GhostData D_20f0cc;
NetName D_22fd18;
LinkCount D_22fd34;

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
        D_1dd6b0.f_00317c(i, Pair(0));
        D_1ee1f0.car[i] = Pair(0);
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

/* Names the row of the course table given by another row. */
static inline void Lookup2(Name &out, Name n)
{
    out.Set(D_2407a8, (const char *)n.a);
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

/* @implements 0x01515c us f_01515c
   WHAT IT DOES: Returns the number of laps of the current race sequence. */
int f_01515c()
{
    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    void *rec = D_2407d0.Get("Laps", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    return D_24063c[0];
}

/* @implements 0x0151e8 us f_0151e8
   WHAT IT DOES: Returns the ghost choice of the setup. */
int f_0151e8()
{
    return D_1ee1f0.m576;
}

/* @implements 0x0151f4 us f_0151f4
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
            D_1dd6b0.f_00317c(i, Pair(0));
            D_1ee1f0.car[i] = Pair(0);
            D_1ee1f0.ClearPlayer(i);
        }
    }
    for (i = 0; i < 13; i++) {
        D_1dd6b0.f_003150(i, Pair(0));
        D_1ee1f0.rival[i] = Pair(0);
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

/* A colour packed as 5, 6 and 5 bits (red, green, blue) in the top half of the word, made
   into a 24 bit colour; -1 when the word's bit 15 says there is none. */
static inline int Colour565(unsigned int c)
{
    if (c & 0x8000)
        return -1;
    unsigned int r = c >> 27;
    unsigned int g = (c >> 21) & 0x3f;
    unsigned int b = (c >> 16) & 0x1f;
    return ((r * 255 / 31) << 16) + ((g * 255 / 63) << 8) + b * 255 / 31;
}

/* A colour packed as 5, 5 and 5 bits in the bottom half of the word, made into a 24 bit
   colour; -1 when bit 15 says there is none. */
static inline int Colour555(unsigned int c)
{
    if (c & 0x8000)
        return -1;
    unsigned int r = (c & 0x7c00) >> 10;
    unsigned int g = (c & 0x3e0) >> 5;
    unsigned int b = c & 0x1f;
    return ((r * 255 / 31) << 16) + ((g * 255 / 31) << 8) + b * 255 / 31;
}

/* @draft 0x0156d4 us f_0156d4
   WHAT IT DOES: Builds the setup of a wireless race. A two player link race sends the local
   player's name entry to the session; other modes send the setup's choices. Every player of
   the session becomes a rival (with its car, colours and options, and in link races its
   name), the local player's own car, colours and name are taken from the link, and the
   sequence manager is given the course, the sequence and the player's car. */
void f_0156d4()
{
    int i;
    int n;

    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    int mode = D_1ee1f0.m20;
    void *rec = D_2407d0.Get("SequenceNumber", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    if (IsMode(3))
        D_240900.f_0408b8(D_22fd18);
    else
        D_240900.f_03fe80(mode, seq, D_1ee1f0.m288[0], D_1ee1f0.m296[0]);
    n = D_240900.count;
    if (D_241810.f_086324() != 0)
        n = D_241810.f_0859b4() - 1;
    for (i = 0; i < n; i++) {
        if (D_240900.count > 0)
            D_1ee1f0.rival[i] = D_240900.cars[i % D_240900.count];
        else
            D_1ee1f0.rival[i] = D_240740.Find("fiera_0_s");
        D_1ee1f0.m184[i] = D_240900.m228[i];
        D_1ee1f0.m236[i] = D_240900.m280[i];
        rec = D_2407d0.Get("SequenceNumber", (const char *)seq.a, 0);
        memcpy(D_24063c, rec, D_1a211c[1]);
        if (IsMode(3))
            strcpy(D_1ee1f0.name[i + 1], D_240900.names[i]);
        D_1ee1f0.m304[i] = D_240900.m124[i];
        D_1ee1f0.m356[i] = D_240900.m176[i];
        D_1dd6b0.f_003150(i, D_1ee1f0.rival[i]);
    }
    D_1ee1f0.m56[0] = D_240900.m336;
    D_1ee1f0.m48[0] = D_240900.m332;
    rec = D_2407d0.Get("SequenceNumber", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    if (IsMode(3)) {
        strcpy(D_1ee1f0.name[0], D_240900.name);
        D_1ee1f0.m288[0] = Colour565(D_241810.entry[0].colours);
        D_1ee1f0.m296[0] = Colour555(D_241810.entry[0].colours);
    }
    void *num = D_2407d0.Get("CourseNumber", (const char *)seq.a, 0);
    Name course;
    Lookup2(course, D_2407a8.Find((const char *)num));
    D_1dd6b0.f_0030d0(course);
    Pair cur = D_1ee1f0.seq;
    D_1dd6b0.m276 = cur;
    D_1dd6b0.m320 = D_1ee1f0.m16;
    D_1dd6b0.f_0030c8(8);
    D_1dd6b0.f_00317c(0, D_1ee1f0.car[0]);
    D_1dd6b0.m292 = 0;
}

/* @draft 0x015ce4 us f_015ce4
   WHAT IT DOES: One step of waiting for the players of a link race. When asked to (and the link
   is idle) it first sends the list of the players taking part. While the link is idle and not
   yet started it checks every other player: when all are ready the link is started; otherwise
   the local player's entry is sent again every 16 steps. Once started (or stopped), it
   answers whether waiting is over (1), or, while the link is busy, takes a message from it and
   marks the local player ready when the message came. */
int f_015ce4()
{
    int i;
    LinkEntry *e = D_241810.entry;

    if (D_241810.m4 == 0 && D_1d164c) {
        D_22fd18.f_083af4(8);
        for (i = 0; i < 8; i++) {
            if (e[i].used)
                D_22fd18.f_083bd4(e[i].id);
        }
        D_22fd18.f_083c18();
        D_1d164c = 0;
    }
    if (D_241810.m93 != 6 && D_241810.m4 == 0) {
        bool ready = 1;
        for (i = 1; i < 8; i++) {
            if (e[i].used && e[i].state != 6) {
                ready = 0;
                break;
            }
        }
        if (ready) {
            D_241810.m93 = 6;
            D_241810.f_086cb4();
            return 0;
        }
        if ((D_22fdb8 & 0xf) == 0)
            D_241804.f_0840f4(&D_22fd18);
        D_22fdb8++;
        return 0;
    }
    if (D_241810.m93 != 6) {
        if (D_241810.m93 != 5) {
            if (D_241810.m4 == 1) {
                if (D_241804.f_084150(&D_22fd18) != -1)
                    e[0].state = 6;
                D_241810.f_086b40();
                return 0;
            }
        }
    }
    D_1d164c = 1;
    return 1;
}

/* @implements 0x015ec0 us f_015ec0
   WHAT IT DOES: Marks the setup as coming from a replay. */
void f_015ec0()
{
    D_1ee1f0.m24 = 1;
}

/* @implements 0x015ed0 us f_015ed0
   WHAT IT DOES: Nothing. */
void f_015ed0()
{
}

void f_01614c(int unused);
void f_01619c();

/* @draft 0x015ed8 us f_015ed8
   WHAT IT DOES: Starts the rules of the race about to be run. It looks up the course, starts the
   effects, picks the background music (the fixed one in the attract demo, otherwise the one the
   course view chooses for the course), loads the sequence and makes the rules object for the
   sequence's race mode. */
void f_015ed8()
{
    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    void *num = D_2407d0.Get("CourseNumber", (const char *)seq.a, 0);
    Name course;
    Lookup2(course, D_2407a8.Find((const char *)num));
    f_01614c(0);
    if (D_1ee198 == -1) {
        if (f_0967c4(D_242cb0) == 1) {
            D_1d3d3c = 27;
        } else {
            void *v = f_017970()->v80();
            void *rec = D_2407a8.Get("SelectNum", (const char *)course.a, 0);
            memcpy(D_24063c, rec, D_1a211c[1]);
            D_1d3d3c = f_077d38(v, D_24063c[0]);
        }
    }
    f_038780(seq);
    void *rec = D_2407d0.Get("SequenceNumber", (const char *)seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    D_1ee47c = f_0396b0(D_24063c[0]);
}

/* @draft 0x0160bc us f_0160bc
   WHAT IT DOES: Copies the chosen option into the setup and tells the rules object the race is
   starting.
   Remaining difference: retail forms the setup's full address (addiu) and stores at +588;
   this build folds the offset into the %lo of the store (one word shorter). */
void f_0160bc()
{
    CRaceRule *r = D_1ee47c;
    D_1ee1f0.SetMode();
    r->v8();
}

/* @draft 0x0160fc us f_0160fc
   WHAT IT DOES: Asks the rules object for its result; none (0) when it has none.
   Remaining difference: retail tests with bnez and fills the slot with the result copy,
   then zeroes on the fall through; this build tests with beqz (the two moves swap). */
RaceResult *f_0160fc()
{
    return D_1ee47c->Result();
}

/* @implements 0x016138 us f_016138
   WHAT IT DOES: Tells the rules object the race has been abandoned. */
void f_016138()
{
    D_1ee47c->m24 = 1;
}

/* @implements 0x01614c us f_01614c
   WHAT IT DOES: Starts the race effects. */
void f_01614c(int unused)
{
    f_01797c();
}

/* @implements 0x016168 us f_016168
   WHAT IT DOES: Lets the rules object finish its result, then steps the race effects. */
void f_016168()
{
    D_1ee47c->v12();
    f_017a20();
}

/* @implements 0x01619c us f_01619c
   WHAT IT DOES: Stops the race effects. */
void f_01619c()
{
    f_017ad8();
}

/* @implements 0x0161b8 us f_0161b8
   WHAT IT DOES: Ends the race in the rules object and keeps its results in the setup: the
   rival record and the ghost, and (unless the race came from a replay) the best lap and time. */
void f_0161b8()
{
    D_1ee47c->v16();
    CRaceRule *r = D_1ee47c;
    D_1ee1f0.m28 = r->m64;
    D_1ee1f0.m568 = r->m60;
    if (D_1ee1f0.m24 == 0) {
        D_1ee1f0.m572 = r->m72;
        D_1ee1f0.m576 = r->m76;
    }
}

/* @implements 0x016220 us f_016220
   WHAT IT DOES: Ends the race: stops the effects, deletes the rules object and frees the race
   resources. */
void f_016220()
{
    f_01619c();
    if (D_1ee47c)
        delete D_1ee47c;
    D_1ee47c = 0;
    f_0292fc(D_23c820);
    f_038828();
}

/* A byte stream over a buffer of a known size. */
struct Stream {
    unsigned int size;
    unsigned int pos;
    unsigned char *p;

    void f_016280(unsigned char *buf, unsigned int n);
    unsigned int f_016290(const unsigned char *src, unsigned int n);
    unsigned int f_0162ec(unsigned char *dst, unsigned int n);
};

/* Retail 0x016280 (f_016280), byte-exact, not tagged here: the control set
   (src/control/batch1.c) claims this address.
   WHAT IT DOES: Starts the stream at the beginning of the given buffer. */
void Stream::f_016280(unsigned char *buf, unsigned int n)
{
    p = buf;
    size = n;
    pos = 0;
}

/* @implements 0x016290 us f_016290
   WHAT IT DOES: Writes up to n bytes into the stream (as many as fit) and returns how many. */
unsigned int Stream::f_016290(const unsigned char *src, unsigned int n)
{
    unsigned int i;
    unsigned int k = size - pos;

    if (n < k)
        k = n;
    for (i = 0; i < k; i++)
        *p++ = *src++;
    pos += k;
    return k;
}

/* @implements 0x0162ec us f_0162ec
   WHAT IT DOES: Reads up to n bytes from the stream (as many as are left) and returns how many. */
unsigned int Stream::f_0162ec(unsigned char *dst, unsigned int n)
{
    unsigned int i;
    unsigned int k = size - pos;

    if (n < k)
        k = n;
    for (i = 0; i < k; i++)
        *dst++ = *p++;
    pos += k;
    return k;
}

void f_0177b0();

/* @draft 0x016348 us f_016348
   WHAT IT DOES: Saves the race setup and the two ghost records into the given buffer: a zero
   word, the race sequence's row, the packed setup record, then each ghost record (the
   recorded one first), storing the stream position after each ghost. It returns 0, or a
   negative code for the part that did not fit. At the end, a two player race whose setup has
   a ghost choice gets its players swapped back. */
int f_016348(unsigned char *data, int *firstEnd, int *size)
{
    int status = 0;
    Stream st;
    int i;
    int j;
    int k;
    int magic;
    int idx;
    int n;
    unsigned char *blk;
    unsigned char *q;

    st.f_016280(data, *size);
    unsigned char *work = new unsigned char[0x20000];
    Codec codec;
    codec.f_044aa4(work, 512);
    magic = 0;
    if (st.f_016290((unsigned char *)&magic, 4) != 4) {
        status = -2;
        goto done;
    }
    idx = D_2407d0.Index((const char *)D_1ee1f0.seq.a);
    if (st.f_016290((unsigned char *)&idx, 4) != 4) {
        status = -2;
        goto done;
    }
    D_1ee1f0.seq.b = D_2407d0.Index((const char *)D_1ee1f0.seq.a);
    for (i = 0; i < 2; i++) {
        if (D_1ee1f0.car[i].a)
            D_1ee1f0.car[i].b = D_240740.Index((const char *)D_1ee1f0.car[i].a);
    }
    for (i = 0; i < 13; i++) {
        if (D_1ee1f0.rival[i].a)
            D_1ee1f0.rival[i].b = D_240740.Index((const char *)D_1ee1f0.rival[i].a);
    }
    codec.f_044b44(0, 1);
    for (i = 0; i < (int)sizeof(RaceSetup); i++)
        codec.f_0449c0(0, ((unsigned char *)&D_1ee1f0)[i]);
    codec.f_044a28(0);
    n = codec.f_044608(0);
    blk = new unsigned char[n + 4];
    *(int *)blk = n;
    q = blk + 4;
    codec.f_04461c(0);
    for (k = 0; k < n; k++)
        *q++ = codec.f_044644(0);
    if (st.f_016290(blk, n + 4) != (unsigned int)(n + 4)) {
        delete[] blk;
        codec.f_044c3c(0);
        status = -7;
        goto done;
    }
    delete[] blk;
    codec.f_044c3c(0);
    if (D_2407f8 == 0) {
        n = 0;
        for (i = 0; i < 16; i++)
            n += D_1ee480.track.f_044608(i);
        if (n >= 0) {
            blk = new unsigned char[n + 4];
            *(int *)blk = n;
            q = blk + 4;
            for (j = 0; j < 16; j++) {
                D_1ee480.track.f_04461c(j);
                int cnt = D_1ee480.track.f_044608(j);
                for (k = 0; k < cnt; k++)
                    *q++ = D_1ee480.track.f_044644(j);
            }
            if (st.f_016290(blk, n + 4) != (unsigned int)(n + 4)) {
                delete[] blk;
                status = -4;
                goto done;
            }
            delete[] blk;
        }
        *firstEnd = st.pos;
        n = 0;
        for (i = 0; i < 16; i++)
            n += D_20f0cc.track.f_044608(i);
        if (n >= 0) {
            blk = new unsigned char[n + 4];
            *(int *)blk = n;
            q = blk + 4;
            for (j = 0; j < 16; j++) {
                D_20f0cc.track.f_04461c(j);
                int cnt = D_20f0cc.track.f_044608(j);
                for (k = 0; k < cnt; k++)
                    *q++ = D_20f0cc.track.f_044644(j);
            }
            if (st.f_016290(blk, n + 4) != (unsigned int)(n + 4)) {
                delete[] blk;
                status = -5;
                goto done;
            }
            delete[] blk;
        }
    } else {
        n = 0;
        for (i = 0; i < 16; i++)
            n += D_20f0cc.track.f_044608(i);
        if (n >= 0) {
            blk = new unsigned char[n + 4];
            *(int *)blk = n;
            q = blk + 4;
            for (j = 0; j < 16; j++) {
                D_20f0cc.track.f_04461c(j);
                int cnt = D_20f0cc.track.f_044608(j);
                for (k = 0; k < cnt; k++)
                    *q++ = D_20f0cc.track.f_044644(j);
            }
            if (st.f_016290(blk, n + 4) != (unsigned int)(n + 4)) {
                delete[] blk;
                status = -5;
                goto done;
            }
            delete[] blk;
        }
        *firstEnd = st.pos;
        n = 0;
        for (i = 0; i < 16; i++)
            n += D_1ee480.track.f_044608(i);
        if (n >= 0) {
            blk = new unsigned char[n + 4];
            *(int *)blk = n;
            q = blk + 4;
            for (j = 0; j < 16; j++) {
                D_1ee480.track.f_04461c(j);
                int cnt = D_1ee480.track.f_044608(j);
                for (k = 0; k < cnt; k++)
                    *q++ = D_1ee480.track.f_044644(j);
            }
            if (st.f_016290(blk, n + 4) != (unsigned int)(n + 4)) {
                delete[] blk;
                status = -4;
                goto done;
            }
            delete[] blk;
        }
    }
    *size = st.pos;
done:
    codec.f_044d98();
    delete[] work;
    void *rec = D_2407d0.Get("SequenceNumber", (const char *)D_1ee1f0.seq.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    if (IsMode(2) && f_0151e8())
        f_0177b0();
    return status;
}

/* @draft 0x016b28 us f_016b28
   WHAT IT DOES: Loads what f_016348 saved: checks the leading zero word, unpacks the setup
   record, turns its table rows back into names (the sequence, the cars and the rivals), checks
   that the sequence is the one saved, and unpacks the two ghost records. Returns 0, or a
   negative code for the part that was missing or wrong. */
int f_016b28(unsigned char *data, unsigned int size)
{
    int status = 0;
    Stream st;
    int i;
    int magic;
    int idx;
    int len;
    unsigned char *blk;

    st.f_016280(data, size);
    unsigned char *work = new unsigned char[0x20000];
    Codec codec;
    codec.f_044aa4(work, 512);
    if (st.f_0162ec((unsigned char *)&magic, 4) != 4 || magic != 0) {
        status = -2;
        goto done;
    }
    if (st.f_0162ec((unsigned char *)&idx, 4) != 4) {
        status = -2;
        goto done;
    }
    if (st.f_0162ec((unsigned char *)&len, 4) != 4) {
        status = -3;
        goto done;
    }
    if (len > 0) {
        blk = new unsigned char[len];
        if (st.f_0162ec(blk, len) != (unsigned int)len) {
            delete[] blk;
            status = -3;
            goto done;
        }
        codec.f_0447ac(blk, len);
        delete[] blk;
        for (i = 0; i < (int)sizeof(RaceSetup); i++)
            ((unsigned char *)&D_1ee1f0)[i] = codec.f_044a68(0);
        for (i = 0; i < 16; i++)
            codec.f_044c3c(i);
    }
    D_1ee1f0.m580 = &D_1ee480;
    D_1ee1f0.m584 = &D_20f0cc;
    D_2407f8 = 0;
    D_1ee1f0.seq.a = (int)D_2407d0.Row(D_1ee1f0.seq.b);
    for (i = 0; i < 2; i++) {
        if (D_1ee1f0.car[i].a)
            D_1ee1f0.car[i].a = (int)D_240740.Row(D_1ee1f0.car[i].b);
    }
    for (i = 0; i < 13; i++) {
        if (D_1ee1f0.rival[i].a)
            D_1ee1f0.rival[i].a = (int)D_240740.Row(D_1ee1f0.rival[i].b);
    }
    if (D_2407d0.Index((const char *)D_1ee1f0.seq.a) != idx) {
        status = -3;
        goto done;
    }
    if (st.f_0162ec((unsigned char *)&len, 4) != 4) {
        status = -2;
        goto done;
    }
    if (len > 0) {
        blk = new unsigned char[len];
        if (st.f_0162ec(blk, len) != (unsigned int)len) {
            delete[] blk;
            status = -2;
            goto done;
        }
        for (i = 0; i < 16; i++)
            D_1ee480.track.f_044c3c(i);
        D_1ee480.track.f_0447ac(blk, len);
        delete[] blk;
    }
    if (st.f_0162ec((unsigned char *)&len, 4) != 4) {
        status = -2;
        goto done;
    }
    if (len > 0) {
        blk = new unsigned char[len];
        if (st.f_0162ec(blk, len) != (unsigned int)len) {
            delete[] blk;
            status = -2;
            goto done;
        }
        for (i = 0; i < 16; i++)
            D_20f0cc.track.f_044c3c(i);
        D_20f0cc.track.f_0447ac(blk, len);
        delete[] blk;
    }
done:
    codec.f_044d98();
    delete[] work;
    return status;
}

/* @implements 0x016fd4 us f_016fd4
   WHAT IT DOES: Prepares a replay of the race just run: hands the race sequence back to the
   sequence manager, marks the setup as a replay, restarts the wireless session's record and
   resets the sequence manager. */
void f_016fd4()
{
    D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    D_1dd6b0.m276 = Pair(D_1ee1f0.seq);
    D_1ee1f0.m24 = 2;
    D_240900.f_03fe1c();
    D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    D_1dd6b0.f_0057d0();
    D_1dd6b0.f_0030c8(0);
}

/* @draft 0x0170a8 us f_0170a8
   WHAT IT DOES: Builds the sequence manager's view of a wireless race from the setup: sends the
   setup's choices to the session, gives every player's car as a rival slot, and sets the
   course, the sequence and both players' cars. */
void f_0170a8()
{
    int i;
    int n;

    Name seq = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    int mode = D_1ee1f0.m20;
    D_240900.f_03fe80(mode, seq, D_1ee1f0.m288[0], D_1ee1f0.m296[0]);
    n = D_240900.count;
    for (i = 0; i < n; i++)
        D_1dd6b0.f_003150(i, D_1ee1f0.rival[i]);
    Name seq2 = D_2407d0.Find((const char *)D_1ee1f0.seq.a);
    void *rec = D_2407d0.Get("SequenceNumber", (const char *)seq2.a, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    void *num = D_2407d0.Get("CourseNumber", (const char *)seq2.a, 0);
    Name course;
    Lookup2(course, D_2407a8.Find((const char *)num));
    D_1dd6b0.f_0030d0(course);
    Pair cur = D_1ee1f0.seq;
    D_1dd6b0.m276 = cur;
    D_1dd6b0.m320 = D_1ee1f0.m16;
    D_1dd6b0.f_0030c8(8);
    D_1dd6b0.f_00317c(0, D_1ee1f0.car[0]);
    D_1dd6b0.f_00317c(1, D_1ee1f0.car[1]);
    D_1dd6b0.m292 = 0;
}

/* @draft 0x01730c us f_01730c
   WHAT IT DOES: Loads a saved replay into the second player's slot: unpacks the saved setup
   into a local copy, names its rows again, checks the sequence matches, loads the replay's
   ghost record into the second ghost, and copies the first player's car, options, colours and
   record times of the saved race into the second player of the current setup. Returns 0 or a
   negative code. */
int f_01730c(unsigned char *data, unsigned int size)
{
    int status = 0;
    RaceSetup rs;
    Stream st;
    int i;
    int magic;
    int idx;
    int len;
    unsigned char *blk;

    st.f_016280(data, size);
    unsigned char *work = new unsigned char[0x20000];
    Codec codec;
    codec.f_044aa4(work, 512);
    if (st.f_0162ec((unsigned char *)&magic, 4) != 4 || magic != 0) {
        status = -2;
        goto done;
    }
    if (st.f_0162ec((unsigned char *)&idx, 4) != 4) {
        status = -2;
        goto done;
    }
    if (st.f_0162ec((unsigned char *)&len, 4) != 4) {
        status = -3;
        goto done;
    }
    if (len > 0) {
        blk = new unsigned char[len];
        if (st.f_0162ec(blk, len) != (unsigned int)len) {
            delete[] blk;
            status = -3;
            goto done;
        }
        codec.f_0447ac(blk, len);
        delete[] blk;
        for (i = 0; i < (int)sizeof(RaceSetup); i++)
            ((unsigned char *)&rs)[i] = codec.f_044a68(0);
        for (i = 0; i < 16; i++)
            codec.f_044c3c(i);
    }
    D_1ee1f0.m584 = &D_20f0cc;
    D_1ee1f0.m580 = &D_1ee480;
    D_2407f8 = 0;
    rs.seq.a = (int)D_2407d0.Row(rs.seq.b);
    for (i = 0; i < 2; i++) {
        if (rs.car[i].a)
            rs.car[i].a = (int)D_240740.Row(rs.car[i].b);
    }
    for (i = 0; i < 13; i++) {
        if (rs.rival[i].a)
            rs.rival[i].a = (int)D_240740.Row(rs.rival[i].b);
    }
    if (D_2407d0.Index((const char *)rs.seq.a) != idx) {
        status = -3;
        goto done;
    }
    if (st.f_0162ec((unsigned char *)&len, 4) != 4) {
        status = -2;
        goto done;
    }
    if (len > 0) {
        blk = new unsigned char[len];
        if (st.f_0162ec(blk, len) != (unsigned int)len) {
            delete[] blk;
            status = -2;
            goto done;
        }
        for (i = 0; i < 16; i++)
            D_20f0cc.track.f_044c3c(i);
        D_20f0cc.track.f_0447ac(blk, len);
        delete[] blk;
    }
    D_1ee1f0.m296[1] = rs.m296[0];
    D_1ee1f0.m572 = rs.m572;
    D_1ee1f0.m64[1] = rs.m64[0];
    D_1ee1f0.m72[1] = rs.m72[0];
    D_1ee1f0.m288[1] = rs.m288[0];
    D_1dd6b0.f_00317c(1, rs.car[0]);
    D_1ee1f0.car[1] = rs.car[0];
done:
    codec.f_044d98();
    delete[] work;
    return status;
}

/* @implements 0x017788 us f_017788
   WHAT IT DOES: Sets the rival record of the setup from the table of records for the given
   course (1 based), when the course has one. */
void f_017788(int course)
{
    int v = D_1a0f28[course - 1];
    if (v > 0)
        D_1ee1f0.m28 = v;
}

template <class T> inline void Swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}

/* @draft 0x0177b0 us f_0177b0
   WHAT IT DOES: Swaps the two players of a two player race: their cars, options and colours,
   and which ghost record each one writes. */
void f_0177b0()
{
    D_2407f8 = 1 - D_2407f8;
    Swap(D_1ee1f0.car[0], D_1ee1f0.car[1]);
    Swap(D_1ee1f0.m64[0], D_1ee1f0.m64[1]);
    Swap(D_1ee1f0.m72[0], D_1ee1f0.m72[1]);
    Swap(D_1ee1f0.m288[0], D_1ee1f0.m288[1]);
    Swap(D_1ee1f0.m296[0], D_1ee1f0.m296[1]);
}

/* @implements 0x017868 us __static_initialization_and_destruction_0
   WHAT IT DOES: Builds the setup record, the two ghost records and the local player's name
   entry at program start, and tears the name entry and the ghost records down at exit. */

/* @implements 0x017928 us _GLOBAL__I_
   WHAT IT DOES: The program-start hook that builds this file's objects. */

/* @implements 0x017948 us _GLOBAL__D_
   WHAT IT DOES: The program-exit hook that tears them down. */
