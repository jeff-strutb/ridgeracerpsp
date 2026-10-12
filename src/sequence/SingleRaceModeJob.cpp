/* The single race mode job (retail 0x008838 to 0x00d46c): the game mode that runs a race
   against the computer cars, time trials and the race menus around them. Like every mode job
   it is a state machine: a table of member functions, one per state, a queue of state events
   and a small script interpreter (in the base class) that decides the next state. Its base
   classes define their virtual functions inline here, so the constructors also set up the base
   classes' vtables on the way; Begin is the class's key function, which makes this file emit
   the vtables, the inline virtual functions and the destructors (0x00d374 to 0x00d46c). */

#include <string.h>

extern "C" {
int f_0160fc(void);
int f_016168(void);
void f_016138(void);
void f_0160bc(void);
void f_0161b8(void);
void f_016220(void);
void f_015204(void);
void f_0156d4(void);
void f_015ec0(void);
void f_015ed8(void);
int f_0149e8(void);
int f_014a08(void);
int f_014a28(void);

int f_0056d0(char *);
void f_005554(char *, int);
void f_005720(char *);
void f_0057d0(char *);

void f_096408(char *);
void f_096434(char *, int);
int f_09654c(char *);
int f_0965b4(char *);
void f_0965ec(char *);
int f_0968e0(char *);
int f_096918(char *);
int f_094db0(char *);
}

extern char D_1dd6b0[];
extern char D_242cb0[];
extern int D_1d1108;
extern int D_1d3d3c;
extern bool D_1edf50;
extern int D_1edf54;
extern int D_1edf58;
extern bool D_1edf5c;
extern bool D_1edf5d;
extern int D_1edf60;
extern int D_1edf64;

/* The pad, as far as this file uses it. */
namespace Controller {
class CCustomController {
public:
    int f_043030();
    int Trig(int mask) { return m16 & mask; }
    int m0[4];
    int m16;
};
}
extern Controller::CCustomController D_1d8910[1];

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
    unsigned int Rand()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return seed;
    }
    void *vt;
    int mode;
    int nextMode;
    void *job;
    unsigned int seed;
};
}
extern System::CGameModeJob D_1e8ec4;

/* The main loop job, as far as this file reads it. */
struct MainLoopJobView {
    char m0[11];
    bool m11;
    bool paused;
};
extern MainLoopJobView *D_1d88a0;

/* The front end's screen manager. Its first member is the current screen layer, a polymorphic
   object that is given settings (v2) and asked for them (v3). */
struct LayerSub {
    void *p;
    void f_04b290();
};
class CLayer {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(void *msg, int arg);
    virtual void v3(void *msg, int arg);
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual int v10(int what);
    void Restart()
    {
        m453 = 1;
        LayerSub *t = &m4;
        void *q = t->p;
        if (q)
            t->f_04b290();
    }
    LayerSub m4;
    char m8[453 - 8];
    unsigned char m453;
};
struct ScreenMgr {
    CLayer *layer;
    int m4[3];
    int phase;
    int m20;
    int m24;
    bool Ready() { return phase == 4; }
};
extern ScreenMgr D_2301b0;
extern "C" {
void f_018b48(ScreenMgr *);
void f_017bfc(ScreenMgr *);
void f_017c88(ScreenMgr *);
}

/* The memory stick state. */
struct MemoryStick {
    int m0;
    char m4[3];
    bool m7;
    int m8[3];
    char *m20;
    int m24;
    int m28;
    int m32;
};
extern MemoryStick D_23ba90;
extern "C" {
int f_01a900(MemoryStick *);
void f_01a91c(MemoryStick *, int);
int f_01abf4(MemoryStick *);
int f_01b1ac(MemoryStick *);
int f_01b6fc(MemoryStick *);
int f_01b91c(MemoryStick *);
void f_01ba4c(MemoryStick *);
int f_01ba88(MemoryStick *);
void f_01bb3c(MemoryStick *);
int f_01bc5c(MemoryStick *);
}

/* The wireless link. */
struct Link {
    int m0;
};
extern Link D_2451f4;
extern "C" {
void f_099718(Link *, int);
void f_0997ac(Link *, int);
int f_0998d0(Link *);
}

/* The debug log; its print is compiled out. */
struct CLog {
    void Printf(int level, const char *fmt, ...) {}
};
extern CLog D_245178;

extern "C" {
int f_016348(char *buf, int *out, int *size);
char *f_01730c(char *ghost, int arg);
void f_014950(void);
void f_1521c8(void *);
int f_0194c4(void);
int f_006018(void);
}
extern char *D_1ee084;

/* A table of the game database: records found by index or by name. */
struct CTable;
extern "C" char *f_0368e8(CTable *t, const char *field, char *rec, int a, int b);
struct CTable {
    char *Field(const char *f, char *rec) { return f_0368e8(this, f, rec, 0, 0); }
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
    int m28[2];
    char *base;
};
extern CTable D_240740;
extern CTable D_2407a8;
extern CTable D_2407d0;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern "C" {
void *memcpy(void *, const void *, unsigned int);
char *f_0368e8(CTable *t, const char *field, char *rec, int a, int b);
char *f_036984(CTable *t, char *name, int i, int *index, int count);
void f_01b7d4(MemoryStick *, int);
}

/* A record found in a database table. */
struct Row {
    char *rec;
    int m4[3];
};

/* Finds the record of the table whose SelectNum field is the given number (the record after
   the last when none is). */
#define FIND_SELECT(out, table, num)                                                   \
    do {                                                                               \
        int key_ = (num);                                                              \
        Row *o_ = (out);                                                               \
        int i_;                                                                        \
        for (i_ = 0; i_ < (table).count; i_++) {                                       \
            memcpy(D_24063c, f_0368e8(&(table), "SelectNum", 0, 0, i_), D_1a211c[1]);  \
            if (key_ == D_24063c[0])                                                   \
                break;                                                                 \
        }                                                                              \
        char *r_ = f_036984(&(table), 0, i_, (table).index, (table).count);            \
        if (r_)                                                                        \
            o_->rec = f_036984(&(table), r_, 0, (table).index, (table).count);         \
        else                                                                           \
            o_->rec = 0;                                                               \
    } while (0)
extern int D_237cc8;
extern unsigned char D_237cfc;

extern "C" {
void f_07a558(void *);
void f_07a5d4(void *);
void f_07827c(void *);
void f_078358(void *);
void f_0782f8(void *);
void f_0783cc(void *);
void f_0784a8(void *);
void f_078448(void *);
void f_07a314(void *);
void f_07a390(void *);
void f_07a9d8(void *);
void f_07aa54(void *);
void f_07aab4(void *);
void f_0792a0(void *);
void f_07937c(void *);
void f_07931c(void *);
}

/* The race setup the front end edits (built and destroyed by the front end code). Its course
   flag table is read 28 bytes long although the next table starts two bytes earlier. */
struct Settings {
    Settings() { f_07a314(this); }
    ~Settings() { f_07a390(this); }
    void *vt;
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32[24];
    int m128;
    int m132;
    unsigned char m136[48];
    unsigned char m184[60];
    unsigned char m244[26];
    unsigned char m270[10];
    int m280;
    int m284;
    bool m288;
    bool m289;
    bool m290;
    unsigned char m291;
    char p292[304 - 292];
};

/* The race settings shared with the race itself. */
struct Tri {
    int v[3];
};
struct RaceSettings {
    int m0[6];
    int m24[336];
    int m1368[336];
    Tri m2712[3][336];
    int m14808;
    unsigned int m14812;
    int m14816[2];
    int m14824[3];
    int m14836[3];
    int m14848[3];
    int m14860;
    int m14864;
    int m14868;
    int m14872[48];
    int m15064[60];
    int m15304[28];
    int m15416[10];
    int m15456[4];
    int m15472;
    int m15476;
    int m15480;
    int m15484[48];
    int m15676;
    int m15680;
    int m15684;
    int m15688;
    int m15692;
    int m15696;
    int m15700;
    int m15704;
    int m15708;
    int m15712;
    unsigned char m15716[8];
    int m15724;
    int m15728;
};
extern RaceSettings D_233f70;

/* The machine and display settings exchanged with the front end; it holds one value per
   car from +84. */
struct Options {
    Options() { f_07a558(this); }
    ~Options() { f_07a5d4(this); }
    char p0[84];
    int m84[63];
};

/* The models of the car the player has picked, shown on the car select screen. */
struct CarModels {
    CarModels() { f_07827c(this); }
    ~CarModels() { f_0782f8(this); }
    void Reset() { f_078358(this); }
    void *vt;
    int m4;
    int mdl;
    int clut;
    int tex;
    int m20;
    int ref;
    int m28;
};

/* The models and data of the course the player has picked, shown on the course select
   screen. */
struct CourseModels {
    CourseModels() { f_0783cc(this); }
    ~CourseModels() { f_078448(this); }
    void Reset() { f_0784a8(this); }
    void *vt;
    int m4;
    int mdl;
    char p12[28 - 12];
    int clut;
    char p32[48 - 32];
    int tex;
    char p52[68 - 52];
    int model;
    char p72[88 - 72];
    int texVram;
    char p92[108 - 92];
    int texMem;
    char p112[128 - 112];
    int mapClip;
    char p132[148 - 132];
    int event;
    char p152[168 - 152];
    int mapEnvC;
    char p172[188 - 172];
    int mapEnvD;
    char p192[208 - 192];
    int motion;
    char p212[228 - 212];
    int roadArea;
    char p232[248 - 232];
    int danmen;
    char p252[288 - 252];
    int carMotion;
    char p292[308 - 292];
    int cameraMotion;
    char p312[336 - 312];
};

/* A request to the screen manager to open a screen (built and destroyed by the screen
   code). */
struct ScreenReq {
    ScreenReq() { f_07a9d8(this); }
    ~ScreenReq() { f_07aa54(this); }
    void Reset() { f_07aab4(this); }
    int m0[2];
    unsigned char m8;
    unsigned int m12;
    unsigned char m16;
    unsigned char m17;
    unsigned char m18;
    int m20[3];
};
/* The result of the race just run: the finishing times by position, the player's lap times,
   the player's position, the best lap times and the course records. */
struct RaceResult {
    char p0[120];
    int time[14];
    float lap[3];
    int me;
    int best[3];
    Tri rec[3];
};
extern RaceResult D_240800;
extern unsigned char D_1edf68;

/* The result screen's message: the player's place, car and times, the course records and
   whether a record was set. */
struct ResultMsg {
    ResultMsg() { f_0792a0(this); }
    ~ResultMsg() { f_07931c(this); }
    void Reset() { f_07937c(this); }
    void *vt;
    int m4;
    int place;
    int car;
    int color;
    int m20;
    int m24;
    int time;
    int laps[6];
    unsigned int avg;
    unsigned int lapMs[6];
    unsigned int record;
    int bestLap;
    bool newRecord;
    bool m93;
    char p94[112 - 94];
    int m112;
    int m116;
    int m120;
    int m124;
};

/* What the race needs to start: the chosen event, random seeds, the course's records, the
   car and the options. */
struct RaceStart {
    int event;
    unsigned int seed1;
    unsigned int seed2;
    int m12;
    int m16;
    Tri m20[3];
    int m56;
    int car[2];
    int color[2];
    int m76[2];
    int m84;
};
extern RaceStart D_1ee198;
extern int D_1d1638[5];

/* A pair of values; only the first is used here. */
struct Param {
    int a;
    int b;
};
extern Param D_1dd7c4;

extern "C" {
void f_003150(char *seq, int i, Row *p);
void f_0030c8(char *seq, int n);
void f_0030f4(char *seq);
void f_00578c(char *seq);
int f_005c34(char *seq, const char *name);
struct Elem280;
Elem280 *f_005a38(char *seq, const char *name);
int f_002acc(Elem280 *e, const char *name);
void f_014cf8(int a, int b);
void f_014dd0(int a, int b);
void f_014ec8(int a);
int f_0151f4(void);
int f_0151e8(void);
void f_01833c(ScreenMgr *, ScreenReq *);
void f_018380(ScreenMgr *, ResultMsg *);
void f_018abc(ScreenMgr *, int);
int f_036a3c(CTable *t, char *rec, int *index, int count);
}

/* The race mode the main menu selected, and this job's script. */
extern int D_1d110c;
extern short D_1d1114[];
extern unsigned char D_1d118c[];

namespace Ng {
class CJob {
public:
    virtual void Begin() {}
    virtual int Step() { return 0; }
    virtual void End() {}
};
}

namespace Sequence {
/* A queue of sixteen state events, read at head and written at tail. */
class CStateQueue {
public:
    CStateQueue() { head = tail = 0; }
    void push(int v)
    {
        buf[tail++] = v;
        tail &= 15;
    }
    int pop()
    {
        if (tail == head)
            return -1;
        int v = buf[head++];
        head &= 15;
        return v;
    }
    int buf[16];
    int head;
    int tail;
};

/* The base of every mode job: the script interpreter's stack and program counter, the script
   (an index of entry points per state and the byte code), the current state and the event
   queue. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int) {}
    virtual void f_4() {}
    int f_099948(int state, int event);

    int sp;
    int pc;
    int stack[10];
    short *table;
    unsigned char *code;
    bool entered;
    int state;
    int frames;
    CStateQueue queue;
};

class CSingleRaceModeJob : public CModeJob {
public:
    typedef void (CSingleRaceModeJob::*State)();

    CSingleRaceModeJob();
    virtual ~CSingleRaceModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int i) { (this->*states[i])(); }
    virtual void f_4() { queue.push(3); }

    void f_009884();
    void f_009a44();
    void f_009bbc();
    void f_009bc4();
    void f_009bf4();
    void f_009c30();
    void f_00a8f4();
    void f_00a8fc();
    void f_00a940();
    void f_00a964();
    void f_00aa10();
    void f_00aac8();
    void f_00ab18();
    void f_00ac54();
    void f_00ac5c();
    void f_00ad84();
    void f_00ad8c();
    void f_00ae1c();
    void f_00ae78();
    void f_00aee8();
    void f_00af44();
    void f_00af98();
    void f_00b04c();
    void f_00b09c();
    void f_00b100();
    void f_00bb14();
    void f_00bbb8();
    void f_00bbc0();
    void f_00c0bc();
    void f_00c0c4();
    void f_00c4b4();
    void f_00c538();
    void f_00c540();
    void f_00c9c8();
    void f_00ca4c();
    void f_00ca54();
    void f_00ccd4();
    void f_00cdb0();
    void f_00cdd0();
    void f_00ce54();
    void f_00ce5c();
    void f_00ce7c();
    void f_00cf30();
    void f_00cf38();
    void f_00cf5c();
    void f_00cff4();
    void f_00cffc();
    void f_00d0b8();
    void f_00d0dc();
    void f_00d174();
    void f_00d17c();
    void f_00d1a4();
    void f_00d200();
    void f_00d208();
    void f_00d234();
    void f_00d290();

    State states[54];
    unsigned char m576;
    int m580[336];
    int m1924[336];
    Tri m3268[3][336];
    int m15364;
    int m15368;
    int m15372;
    int m15376;
    int m15380;
    int m15384[24];
    int m15480;
    int m15484;
    int m15488[48];
    unsigned char m15680[60];
    unsigned char m15740[28];
    unsigned char m15768[10];
    int m15780;
    bool m15784;
    bool m15785;
    bool m15786;
    int m15788;
    int m15792[48];
    bool m15984;
    int m15988;
    int m15992;
    int m15996;
    unsigned char *m16000;
    unsigned char m16004;
    bool m16005;
    int m16008;
    int m16012;
    char *m16016;
    int m16020;
    int m16024;
};
}

/* @implements 0x008838 us _ZN8Sequence18CSingleRaceModeJobC2Ev
   WHAT IT DOES: Constructs the single race mode job: an empty event queue, the table of state
   handlers and the job's script. */
/* @implements 0x008e04 us _ZN8Sequence18CSingleRaceModeJobC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */
Sequence::CSingleRaceModeJob::CSingleRaceModeJob()
{
    states[0] = &CSingleRaceModeJob::f_009bbc;
    states[1] = &CSingleRaceModeJob::f_009bc4;
    states[2] = &CSingleRaceModeJob::f_00a940;
    states[3] = &CSingleRaceModeJob::f_009bf4;
    states[4] = &CSingleRaceModeJob::f_009c30;
    states[5] = &CSingleRaceModeJob::f_00a8f4;
    states[6] = &CSingleRaceModeJob::f_00a8fc;
    states[7] = &CSingleRaceModeJob::f_00ca54;
    states[8] = &CSingleRaceModeJob::f_00ccd4;
    states[9] = &CSingleRaceModeJob::f_00a964;
    states[10] = &CSingleRaceModeJob::f_00aa10;
    states[11] = &CSingleRaceModeJob::f_00aac8;
    states[12] = &CSingleRaceModeJob::f_00ab18;
    states[13] = &CSingleRaceModeJob::f_00ac54;
    states[14] = &CSingleRaceModeJob::f_00ac5c;
    states[15] = &CSingleRaceModeJob::f_00ad84;
    states[16] = &CSingleRaceModeJob::f_00ad8c;
    states[17] = &CSingleRaceModeJob::f_00ae1c;
    states[18] = &CSingleRaceModeJob::f_00ae78;
    states[19] = &CSingleRaceModeJob::f_00aee8;
    states[20] = &CSingleRaceModeJob::f_00af44;
    states[21] = &CSingleRaceModeJob::f_00af98;
    states[22] = &CSingleRaceModeJob::f_00b04c;
    states[23] = &CSingleRaceModeJob::f_00b09c;
    states[24] = &CSingleRaceModeJob::f_00b100;
    states[25] = &CSingleRaceModeJob::f_00bb14;
    states[26] = &CSingleRaceModeJob::f_00bbb8;
    states[27] = &CSingleRaceModeJob::f_00bbc0;
    states[28] = &CSingleRaceModeJob::f_00c0bc;
    states[29] = &CSingleRaceModeJob::f_00c0c4;
    states[30] = &CSingleRaceModeJob::f_00c4b4;
    states[31] = &CSingleRaceModeJob::f_00c538;
    states[32] = &CSingleRaceModeJob::f_00c540;
    states[33] = &CSingleRaceModeJob::f_00c9c8;
    states[34] = &CSingleRaceModeJob::f_00ca4c;
    states[35] = &CSingleRaceModeJob::f_00cdb0;
    states[36] = &CSingleRaceModeJob::f_00cdd0;
    states[37] = &CSingleRaceModeJob::f_00ce54;
    states[38] = &CSingleRaceModeJob::f_00ce5c;
    states[39] = &CSingleRaceModeJob::f_00ce7c;
    states[40] = &CSingleRaceModeJob::f_00cf30;
    states[41] = &CSingleRaceModeJob::f_00cf38;
    states[42] = &CSingleRaceModeJob::f_00cf5c;
    states[43] = &CSingleRaceModeJob::f_00cff4;
    states[44] = &CSingleRaceModeJob::f_00cffc;
    states[45] = &CSingleRaceModeJob::f_00d0b8;
    states[46] = &CSingleRaceModeJob::f_00d0dc;
    states[47] = &CSingleRaceModeJob::f_00d174;
    states[48] = &CSingleRaceModeJob::f_00d17c;
    states[49] = &CSingleRaceModeJob::f_00d1a4;
    states[50] = &CSingleRaceModeJob::f_00d200;
    states[51] = &CSingleRaceModeJob::f_00d208;
    states[52] = &CSingleRaceModeJob::f_00d234;
    states[53] = &CSingleRaceModeJob::f_00d290;
    table = D_1d1114;
    code = D_1d118c;
}

/* @implements 0x0093d0 us _ZN8Sequence18CSingleRaceModeJob5BeginEv
   WHAT IT DOES: Starts the single race mode: takes its own copy of the game's race settings
   (two tables of 336 values, three tables of 336 entries, the settings of the race kind the
   main menu selected, the unlocked cars, courses and options, the records and the machine
   settings), then starts the script from its first state. */
void Sequence::CSingleRaceModeJob::Begin()
{
    frames = 0;
    for (int i = 0; i < 336; i++) {
        m580[i] = D_233f70.m24[i];
        m1924[i] = D_233f70.m1368[i];
    }
    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 336; k++)
        {
            m3268[j][k].v[0] = D_233f70.m2712[j][k].v[0];
            m3268[j][k].v[1] = D_233f70.m2712[j][k].v[1];
            m3268[j][k].v[2] = D_233f70.m2712[j][k].v[2];
        }
    switch (D_1d110c) {
    case 1:
        m15364 = D_233f70.m14816[0];
        m15368 = D_233f70.m14816[1];
        break;
    case 2:
        m15364 = D_233f70.m14824[0];
        m15372 = D_233f70.m14824[1];
        m15368 = D_233f70.m14824[2];
        break;
    case 3:
        m15364 = D_233f70.m14836[0];
        m15372 = D_233f70.m14836[1];
        m15368 = D_233f70.m14836[2];
        break;
    }
    m15376 = D_233f70.m14860;
    m15380 = D_233f70.m14864;
    m15484 = D_233f70.m14868;
    for (int i = 0; i < 48; i++)
        m15488[i] = D_233f70.m14872[i];
    for (int i = 0; i < 60; i++)
        m15680[i] = D_233f70.m15064[i] != 0;
    for (int i = 0; i < 28; i++)
        m15740[i] = D_233f70.m15304[i] != 0;
    for (int i = 0; i < 10; i++)
        m15768[i] = D_233f70.m15416[i] != 0;
    switch (D_1d110c) {
    case 1:
        m15780 = D_233f70.m15456[0];
        break;
    case 2:
        m15780 = D_233f70.m15456[1];
        break;
    case 3:
        m15780 = D_233f70.m15456[2];
        break;
    }
    m15784 = D_233f70.m15472 != 0;
    m15785 = D_233f70.m15476 != 0;
    m15786 = D_233f70.m15480 != 0;
    for (int i = 0; i < 48; i++)
        m15792[i] = D_233f70.m15484[i];
    m15984 = D_233f70.m15676 != 0;
    m15988 = D_233f70.m15680;
    m15992 = D_233f70.m15728;
    m16000 = D_233f70.m15716;
    state = 0;
    frames = 0;
    sp = 0;
    entered = 1;
}

/* @implements 0x00968c us _ZN8Sequence18CSingleRaceModeJob4StepEv
   WHAT IT DOES: Runs one frame of the single race mode. Unless the game is paused, it feeds the
   script the events of the frame (the entry event when a state has just been entered, then the
   frame event), letting it change state, and counts the frame. Then, by state, it updates the
   race (or, while paused, the pause menu) or the front end. */
int Sequence::CSingleRaceModeJob::Step()
{
    int e;

    if (!D_1d88a0->paused) {
        if (entered) {
            queue.push(0);
            while ((e = queue.pop()) >= 0)
                f_099948(state, e);
        }
        entered = 0;
        queue.push(1);
        int s = state;
        while ((e = queue.pop()) >= 0)
            f_099948(s, e);
        frames++;
    }
    switch (state) {
    case 8:
    case 17:
        if (D_1d88a0->paused)
            f_0160fc();
        break;
    case 21:
    case 22:
    case 23:
    case 26:
    case 28:
        break;
    case 9:
        if (D_1d88a0->paused)
            f_016168();
        break;
    default:
        f_018b48(&D_2301b0);
        break;
    }
    return 0;
}

/* @implements 0x009868 us _ZN8Sequence18CSingleRaceModeJob3EndEv
   WHAT IT DOES: Leaves the single race mode, handing its settings back to the shared race
   settings. */
void Sequence::CSingleRaceModeJob::End()
{
    f_009884();
}

/* @implements 0x009884 us f_009884
   WHAT IT DOES: Copies the mode's race setup (the per car and per course tables, the chosen
   course, car and options, the unlocked items and the special flags) into the shared race
   settings, and marks the special event as done when it was won. */
void Sequence::CSingleRaceModeJob::f_009884()
{
    for (int i = 0; i < 336; i++) {
        D_233f70.m24[i] = m580[i];
        D_233f70.m1368[i] = m1924[i];
    }
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 336; j++)
        {
            D_233f70.m2712[i][j].v[0] = m3268[i][j].v[0];
            D_233f70.m2712[i][j].v[1] = m3268[i][j].v[1];
            D_233f70.m2712[i][j].v[2] = m3268[i][j].v[2];
        }
    D_233f70.m14860 = m15376;
    D_233f70.m14868 = m15484;
    for (int i = 0; i < 48; i++)
        D_233f70.m14872[i] = m15488[i];
    for (int i = 0; i < 60; i++)
        D_233f70.m15064[i] = m15680[i];
    for (int i = 0; i < 28; i++)
        D_233f70.m15304[i] = m15740[i];
    for (int i = 0; i < 10; i++)
        D_233f70.m15416[i] = m15768[i];
    D_233f70.m15472 = m15784;
    D_233f70.m15476 = m15785;
    for (int i = 0; i < 48; i++)
        D_233f70.m15484[i] = m15792[i];
    if (D_233f70.m0[5] && D_233f70.m15476)
        m15984 = 1;
    D_233f70.m15676 = m15984;
    D_233f70.m15680 = m15988;
}

/* @implements 0x009a44 us f_009a44
   WHAT IT DOES: Takes the race setup the player chose on the front end (course, car, options
   and the unlocked items) into the mode. */
void Sequence::CSingleRaceModeJob::f_009a44()
{
    Settings o;

    D_2301b0.layer->v3(&o, 0);
    m15364 = o.m12;
    m15372 = o.m16;
    m15368 = o.m20;
    m15376 = o.m24;
    m15380 = o.m28;
    for (unsigned int i = 0; i < 24; i++)
        m15384[i] = o.m32[i];
    m15480 = o.m128;
    m15484 = o.m132;
    for (unsigned int i = 0; i < 48; i++)
        m15488[i] = o.m136[i];
    for (unsigned int i = 0; i < 60; i++)
        m15680[i] = o.m184[i];
    for (unsigned int i = 0; i < 28; i++)
        m15740[i] = o.m244[i];
    for (unsigned int i = 0; i < 10; i++)
        m15768[i] = o.m270[i];
    m15780 = o.m284;
    m15788 = o.m291;
    m15786 = o.m290;
    m15784 = o.m288;
}

/* @implements 0x009bbc us f_009bbc
   WHAT IT DOES: State 0: does nothing (the script drives it). */
void Sequence::CSingleRaceModeJob::f_009bbc()
{
}

/* @implements 0x009bc4 us f_009bc4
   WHAT IT DOES: State 1: moves straight on to the next step of the script. */
void Sequence::CSingleRaceModeJob::f_009bc4()
{
    queue.push(2);
}

/* @implements 0x009bf4 us f_009bf4
   WHAT IT DOES: State 3: clears the status of the background save and load requests. */
void Sequence::CSingleRaceModeJob::f_009bf4()
{
    D_1edf50 = 0;
    D_1edf54 = 0;
    D_1edf58 = 0;
    D_1edf5c = 0;
    D_1edf5d = 0;
    D_1edf60 = 0;
    D_1edf64 = 0;
}

/* @draft 0x009c30 us f_009c30
   WHAT IT DOES: State 4: runs the race setup screens. It draws two random seeds; when the
   player moves to another car or course, it plays that car's or course's sound once the
   previous one has finished and then hands the screen the models to show; it restarts the
   screen when asked to. When the player backs out, it keeps the setup and returns (event 6).
   When the player confirms, it takes the chosen setup, prepares the event of the selected
   race kind (normal race, time attack or the others), fills in what the race needs (seeds,
   the course's records, car, colour and options) and starts the race (event 4, or 5 for a
   sequence that waits for something to load). */
void Sequence::CSingleRaceModeJob::f_009c30()
{
    m16008 = D_1e8ec4.Rand();
    m16012 = D_1e8ec4.Rand();

    int car = D_2301b0.layer->v10(7);
    if (car < 0) {
        if (D_1edf5c) {
            D_1edf5c = 0;
            D_1edf54 = 0;
            D_1edf50 = 0;
            f_00578c(D_1dd6b0);
        }
        car = 0;
    }
    if (car == 0 && !D_1edf50 && D_1edf54)
        car = D_1edf54;
    if (car != 0) {
        D_1edf54 = car;
        if (!D_1edf50 && !f_0056d0(D_1dd6b0)) {
            if (car == -1) {
                D_1edf54 = 0;
                D_1edf50 = 0;
                if (D_1edf5c) {
                    D_1edf5c = 0;
                    f_0057d0(D_1dd6b0);
                }
            } else {
                Row row;
                FIND_SELECT(&row, D_240740, car);
                f_003150(D_1dd6b0, 0, &row);
                f_0030c8(D_1dd6b0, 4);
                f_005554(D_1dd6b0, 1);
                D_1edf58 = car;
                D_1edf5c = 1;
                D_1edf50 = 1;
            }
        }
    }
    if (D_1edf50 && !f_0056d0(D_1dd6b0)) {
        D_1edf50 = 0;
        if (D_1edf58 == D_1edf54) {
            D_1edf54 = 0;
            CarModels m;
            m.Reset();
            m.mdl = f_005c34(D_1dd6b0, "Mdl");
            m.tex = f_005c34(D_1dd6b0, "Tex");
            m.clut = f_005c34(D_1dd6b0, "Clut");
            m.ref = f_005c34(D_1dd6b0, "Ref");
            D_2301b0.layer->v2(&m, 0);
        }
    }

    int course = D_2301b0.layer->v10(8);
    if (course == 0 && !D_1edf5d && D_1edf60)
        course = D_1edf60;
    if (course != 0) {
        D_1edf60 = course;
        if (!D_1edf5d && !D_1edf50) {
            if (course == -1) {
                D_1edf60 = 0;
                D_1edf5d = 0;
                f_0057d0(D_1dd6b0);
            } else {
                Row row;
                FIND_SELECT(&row, D_240740, course);
                f_003150(D_1dd6b0, 0, &row);
                f_0030c8(D_1dd6b0, 5);
                f_005554(D_1dd6b0, 1);
                D_1edf64 = course;
                D_1edf5d = 1;
            }
        }
    }
    if (D_1edf5d && !f_0056d0(D_1dd6b0)) {
        D_1edf5d = 0;
        if (D_1edf64 == D_1edf60) {
            D_1edf60 = 0;
            CourseModels m;
            m.Reset();
            m.mdl = f_005c34(D_1dd6b0, "Mdl");
            m.tex = f_005c34(D_1dd6b0, "Tex");
            m.clut = f_005c34(D_1dd6b0, "Clut");
            Elem280 *e = f_005a38(D_1dd6b0, "Course");
            m.model = f_002acc(e, "Model");
            m.texVram = f_002acc(e, "TexVram");
            m.texMem = f_002acc(e, "TexMem");
            m.mapClip = f_002acc(e, "MapClip");
            m.event = f_002acc(e, "Event");
            m.mapEnvC = f_002acc(e, "MapEnvC");
            m.mapEnvD = f_002acc(e, "MapEnvD");
            m.motion = f_002acc(e, "Motion");
            m.roadArea = f_002acc(e, "RoadArea");
            m.danmen = f_002acc(e, "Danmen");
            m.carMotion = f_002acc(e, "CarMotion");
            m.cameraMotion = f_002acc(e, "CameraMotion");
            m.roadArea = f_002acc(e, "RoadArea");
            D_2301b0.layer->v2(&m, 0);
        }
    }

    if (D_2301b0.layer->v10(3) == 7)
        D_2301b0.layer->Restart();
    if (D_2301b0.layer->v10(6) == 2) {
        f_009a44();
        if ((unsigned int)(m15376 - 1) >= 47)
            m15376 = 1;
        f_009884();
        queue.push(6);
        return;
    }
    if (!D_2301b0.m24)
        return;

    Settings o;
    D_2301b0.layer->v3(&o, 0);
    D_1d1108 = 2;
    D_1d110c = o.m8;
    f_009a44();
    f_0030f4(D_1dd6b0);
    {
        Options op;
        D_2301b0.layer->v3(&op, 0);
        D_1d1638[0] = op.m84[m15364] - 1;
    }
    D_1ee198.m84 = m15992;
    D_1ee198.event = m15780;
    D_1ee198.seed1 = D_1e8ec4.Rand();
    D_1ee198.seed2 = D_1e8ec4.Rand();
    m16004 = 0;
    switch (D_1d110c) {
    case 1:
        if ((unsigned int)(m15376 - 1) < 47) {
            f_014cf8(m15376, m15380);
        } else {
            m16004 = 1;
            m15372 = (&m15380)[m15380];
            f_014dd0(m15372, m15364);
        }
        break;
    case 2:
        f_014dd0(m15372, m15364);
        break;
    case 3:
        f_014ec8(m15372);
        break;
    }

    Row carRow;
    FIND_SELECT(&carRow, D_240740, m15364);
    memcpy(D_24063c, D_240740.Field("Class", carRow.rec), D_1a211c[1]);
    int cls = D_24063c[0] - 1;
    Param seq = D_1dd7c4;
    char *r = D_2407d0.Field("CourseNumber", (char *)seq.a);
    Row crs;
    if (r)
        crs.rec = f_036984(&D_2407a8, r, 0, D_2407a8.index, D_2407a8.count);
    else
        crs.rec = 0;
    Row c = crs;
    int k = cls * 24 + f_036a3c(&D_2407a8, c.rec, D_2407a8.index, D_2407a8.count);
    if (m15788)
        k += 168;
    D_1ee198.m16 = m1924[k];
    D_1ee198.m12 = m580[k];
    for (int i = 0; i < 3; i++)
        D_1ee198.m20[i] = m3268[i][k];
    D_1ee198.car[0] = m15364;
    D_1ee198.color[0] = m15368 - 1;
    D_1ee198.car[1] = 0;
    D_1ee198.m76[0] = m15788;
    D_1d1638[1] = -1;
    D_1ee198.color[1] = 0;
    D_1ee198.m76[1] = 0;
    D_1ee198.m56 = 1;
    f_014950();
    D_1d1638[2] = m15786;
    if (m16004) {
        D_1d1638[3] = m15484;
        if (m15380 < m15480)
            D_1d1638[4] = m15380;
        else
            D_1d1638[4] = 0;
    } else {
        D_1d1638[4] = -1;
    }
    D_1d3d3c = m15780;
    Param sq = D_1dd7c4;
    memcpy(D_24063c, D_2407d0.Field("SequenceNumber", (char *)sq.a), D_1a211c[1]);
    if (D_24063c[0] != 2 || f_0151f4())
        queue.push(4);
    else
        queue.push(5);
}

/* @implements 0x00a8f4 us f_00a8f4
   WHAT IT DOES: State 5: does nothing. */
void Sequence::CSingleRaceModeJob::f_00a8f4()
{
}

/* @implements 0x00a8fc us f_00a8fc
   WHAT IT DOES: State 6: waits until the front end is idle, then moves on. */
void Sequence::CSingleRaceModeJob::f_00a8fc()
{
    if (!D_2301b0.phase)
        queue.push(2);
}

/* @implements 0x00a940 us f_00a940
   WHAT IT DOES: State 2: returns to the main menu mode. */
void Sequence::CSingleRaceModeJob::f_00a940()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x00a964 us f_00a964
   WHAT IT DOES: On its first frame, starts the menu screen and its music; afterwards moves on
   once the music system is ready. Updates the front end every frame. */
void Sequence::CSingleRaceModeJob::f_00a964()
{
    if (frames == 1) {
        f_005720(D_1dd6b0);
        f_015204();
        f_005554(D_1dd6b0, 1);
    } else if (!f_0056d0(D_1dd6b0)) {
        queue.push(2);
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x00aa10 us f_00aa10
   WHAT IT DOES: On its first frame, starts a screen and its music; once the music system is
   ready, closes the front end screen and moves on. Otherwise updates the front end. */
void Sequence::CSingleRaceModeJob::f_00aa10()
{
    if (frames == 1) {
        f_0156d4();
        f_005554(D_1dd6b0, 1);
        f_017bfc(&D_2301b0);
    } else if (!f_0056d0(D_1dd6b0)) {
        f_017c88(&D_2301b0);
        f_015ed8();
        queue.push(2);
    } else {
        f_017bfc(&D_2301b0);
    }
}

/* @implements 0x00aac8 us f_00aac8
   WHAT IT DOES: Starts the race scene and moves on. */
void Sequence::CSingleRaceModeJob::f_00aac8()
{
    f_0160bc();
    queue.push(2);
}

/* @implements 0x00ab18 us f_00ab18
   WHAT IT DOES: While the race runs, handles the pause request and the end of the race: when
   the race is over, it closes the race and goes on to the result (or to the retry branch), and
   when the player pauses, it opens the pause menu. */
void Sequence::CSingleRaceModeJob::f_00ab18()
{
    if (f_0160fc()) {
        f_0161b8();
        if (f_0149e8()) {
            f_0965b4(D_242cb0);
            queue.push(2);
        } else {
            f_096408(D_242cb0);
            queue.push(8);
        }
    } else {
        if (f_014a28() == 1) {
            m15780 = D_1d3d3c;
            f_096434(D_242cb0, D_1d3d3c);
        }
        if (D_1d8910[0].Trig(2) || D_1d8910[0].Trig(0x400000)) {
            if (f_014a08()) {
                D_1d88a0->m11 = 1;
                f_0968e0(D_242cb0);
                queue.push(7);
            }
        }
    }
}

/* @implements 0x00ac54 us f_00ac54
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00ac54()
{
}

/* @implements 0x00ac5c us f_00ac5c
   WHAT IT DOES: Runs the pause menu and acts on the choice: continue the race, retire, restart
   or quit to the menus. */
void Sequence::CSingleRaceModeJob::f_00ac5c()
{
    switch (f_016168()) {
    case 1:
        D_1d88a0->m11 = 0;
        f_096918(D_242cb0);
        queue.push(6);
        break;
    case 5:
        f_094db0(D_242cb0);
        queue.push(10);
        break;
    case 4:
        if (m16004)
            m15376 = 1;
        D_1d1108 = 2;
        f_096408(D_242cb0);
        queue.push(9);
        break;
    case 2:
        f_096408(D_242cb0);
        queue.push(11);
        break;
    }
}

/* @implements 0x00ad84 us f_00ad84
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00ad84()
{
}

/* @implements 0x00ad8c us f_00ad8c
   WHAT IT DOES: Starts the replay on its first frame and, when it ends, closes it and moves
   on. */
void Sequence::CSingleRaceModeJob::f_00ad8c()
{
    if (frames == 1)
        f_016138();
    if (f_0160fc()) {
        f_0161b8();
        queue.push(2);
        D_1d88a0->m11 = 0;
    }
}

/* @implements 0x00ae1c us f_00ae1c
   WHAT IT DOES: Leaves the race scene, stops the music and moves on. */
void Sequence::CSingleRaceModeJob::f_00ae1c()
{
    f_016220();
    f_0057d0(D_1dd6b0);
    queue.push(2);
}

/* @implements 0x00ae78 us f_00ae78
   WHAT IT DOES: Branches on whether the race was finished. */
void Sequence::CSingleRaceModeJob::f_00ae78()
{
    if (f_0149e8())
        queue.push(2);
    else
        queue.push(8);
}

/* @implements 0x00aee8 us f_00aee8
   WHAT IT DOES: Starts the result screen and moves on. */
void Sequence::CSingleRaceModeJob::f_00aee8()
{
    f_015ec0();
    f_09654c(D_242cb0);
    queue.push(2);
}

/* @implements 0x00af44 us f_00af44
   WHAT IT DOES: Starts the replay scene with no replay request pending and moves on. */
void Sequence::CSingleRaceModeJob::f_00af44()
{
    f_0160bc();
    m576 = 0;
    queue.push(2);
}

/* @implements 0x00af98 us f_00af98
   WHAT IT DOES: While the replay runs, starts the replay menu when the player presses the
   button, and when the replay ends moves on (to the menu branch if it was requested). */
void Sequence::CSingleRaceModeJob::f_00af98()
{
    if (D_1d8910[0].f_043030()) {
        m576 = 1;
        f_016138();
        f_0965ec(D_242cb0);
    }
    if (f_0160fc()) {
        if (m576 == 1)
            queue.push(12);
        else
            queue.push(2);
    }
}

/* @implements 0x00b04c us f_00b04c
   WHAT IT DOES: Closes the race scene and moves on. */
void Sequence::CSingleRaceModeJob::f_00b04c()
{
    f_0161b8();
    queue.push(2);
}

/* @implements 0x00b09c us f_00b09c
   WHAT IT DOES: Closes and leaves the race scene, stops the music and moves on. */
void Sequence::CSingleRaceModeJob::f_00b09c()
{
    f_0161b8();
    f_016220();
    f_0057d0(D_1dd6b0);
    queue.push(2);
}

/* @draft 0x00b100 us f_00b100
   WHAT IT DOES: State 24: shows the race result. It finds the record slot of the chosen
   course and car class, opens the result screen (marking a first win of a special event),
   fills the result message with the player's place, finishing time, lap times and average,
   updates the course's best lap and race time records and the record lap times when they
   are beaten, and decides the outcome for the event kind: whether the player qualified in a
   tour (and the tour's extra reward), or the series progress. It adds the course length to
   the total distance driven when the race counts, hands the records to the race settings
   and moves the screen on (to the special page when a tour was completed). */
void Sequence::CSingleRaceModeJob::f_00b100()
{
    int me = D_240800.me;
    Row carRow;
    FIND_SELECT(&carRow, D_240740, m15364);
    memcpy(D_24063c, D_240740.Field("Class", carRow.rec), D_1a211c[1]);
    Param seq = D_1dd7c4;
    int k = D_24063c[0] - 1;
    char *r = D_2407d0.Field("CourseNumber", (char *)seq.a);
    Row crs;
    if (r)
        crs.rec = f_036984(&D_2407a8, r, 0, D_2407a8.index, D_2407a8.count);
    else
        crs.rec = 0;
    Row c = crs;
    k = k * 24 + f_036a3c(&D_2407a8, c.rec, D_2407a8.index, D_2407a8.count);
    if (m15788)
        k += 168;

    ScreenReq req;
    req.Reset();
    req.m12 = D_1d110c;
    req.m16 = m15992;
    req.m17 = 1;
    if (D_240800.time[me] <= 0)
        req.m17 = 0;
    seq = D_1dd7c4;
    req.m18 = 0;
    memcpy(D_24063c, D_2407d0.Field("SequenceNumber", (char *)seq.a), D_1a211c[1]);
    if (D_24063c[0] == 2 && f_0151e8() && !f_0151f4() && !m15788) {
        D_1edf68 = 1;
        req.m18 = 1;
    }
    f_01833c(&D_2301b0, &req);

    ResultMsg m;
    m.Reset();
    m.time = D_240800.time[me] / 3;
    m.car = m15364;
    m.color = m15372;
    m.m20 = m15376;
    m.m24 = m15380;
    m.place = me + 1;
    for (int i = 0; i < 6; i++)
        m.laps[i] = 0;
    m.avg = 0;
    for (int i = 0; i < 6; i++)
        m.lapMs[i] = 0;
    m.bestLap = -1;
    for (int i = 0; i < 3; i++) {
        int t = D_240800.best[i];
        m.laps[i] = t / 3;
        if (t > 0 && (unsigned int)t < (unsigned int)m1924[k]) {
            m1924[k] = t;
            m.bestLap = i + 1;
        }
    }
    for (int i = 0; i < 3; i++)
        m.lapMs[i] = (unsigned int)(D_240800.lap[i] * 1000.0f);
    m.avg = (m.lapMs[0] + m.lapMs[1] + m.lapMs[2]) / 3;
    if (D_240800.lap[2] <= 0.0f)
        m.avg = 0;
    m.newRecord = 0;
    int t = D_240800.time[me];
    if (t > 0 && (unsigned int)t < (unsigned int)m580[k]) {
        m580[k] = t;
        m.newRecord = 1;
    }
    m.record = (unsigned int)m580[k] / 3;
    if (m.newRecord)
        for (int i = 0; i < 3; i++)
            m3268[i][k] = D_240800.rec[i];

    m16005 = 0;
    int tourDone = 0;
    m.m93 = 0;
    seq = D_1dd7c4;
    memcpy(D_24063c, D_2407d0.Field("SequenceNumber", (char *)seq.a), D_1a211c[1]);
    bool tour = D_24063c[0] == 4;
    if (!tour) {
        seq = D_1dd7c4;
        memcpy(D_24063c, D_2407d0.Field("SequenceNumber", (char *)seq.a), D_1a211c[1]);
        tour = D_24063c[0] == 5;
    }
    if (tour) {
        seq = D_1dd7c4;
        m.m112 = 0;
        memcpy(D_24063c, D_2407d0.Field("QualifyPos", (char *)seq.a), D_1a211c[1]);
        if (D_24063c[0] >= m.place) {
            seq = D_1dd7c4;
            memcpy(D_24063c, D_2407d0.Field("TourExtra", (char *)seq.a), D_1a211c[1]);
            switch (D_24063c[0]) {
            case 1:
                m.m112 = 2;
                if (m15792[m15376] < m15380)
                    m15792[m15376] = m15380;
                break;
            case 3:
                tourDone = 1;
            case 2:
                m.m112 = 1;
                m15792[m15376] = 10;
                break;
            }
        }
    } else if (m15380 < m15480) {
        m.m112 = 2;
    } else {
        m16005 = 1;
        m.m112 = 1;
    }

    if (m.time) {
        seq = D_1dd7c4;
        memcpy(D_24063c, D_2407d0.Field("SequenceNumber", (char *)seq.a), D_1a211c[1]);
        bool counts = D_24063c[0] == 4;
        if (!counts) {
            seq = D_1dd7c4;
            memcpy(D_24063c, D_2407d0.Field("SequenceNumber", (char *)seq.a), D_1a211c[1]);
            counts = D_24063c[0] == 5 || m16004;
        }
        if (counts) {
            seq = D_1dd7c4;
            char *r2 = D_2407d0.Field("CourseNumber", (char *)seq.a);
            Row c2;
            if (r2)
                c2.rec = f_036984(&D_2407a8, r2, 0, D_2407a8.index, D_2407a8.count);
            else
                c2.rec = 0;
            Row c3 = c2;
            memcpy(D_24063c, D_2407a8.Field("SelectLength", c3.rec), D_1a211c[2]);
            m15988 += *(short *)D_24063c * 3;
        }
    }
    m.m116 = m15484;
    m.m120 = m15480;
    f_018380(&D_2301b0, &m);
    for (int i = 0; i < 3; i++)
        D_1ee198.m20[i] = m3268[i][k];
    D_1ee198.m12 = m580[k];
    D_1ee198.m16 = m1924[k];
    if (tourDone) {
        m15785 = 1;
        f_018abc(&D_2301b0, 14);
    } else {
        f_018abc(&D_2301b0, 12);
    }
}

/* @implements 0x00bb14 us f_00bb14
   WHAT IT DOES: Waits for the front end to finish its screen, then closes it, allocates a half
   megabyte buffer and builds the race data in it, and moves on. */
void Sequence::CSingleRaceModeJob::f_00bb14()
{
    f_017bfc(&D_2301b0);
    if (D_2301b0.Ready()) {
        f_017c88(&D_2301b0);
        m16020 = 0x80000;
        m16016 = new char[0x80000];
        f_016348(m16016, &m16024, &m16020);
        queue.push(2);
    }
}

/* @implements 0x00bbb8 us f_00bbb8
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00bbb8()
{
}

/* @draft 0x00bbc0 us f_00bbc0
   WHAT IT DOES: State 27: runs the menu after the race result. Its first four choices go to
   the replay, the result branch or the save branch. When the player confirms a choice, it
   frees the race data buffer and acts on it: back to the menus (the race kind's mode), to the
   series next race (moving on in the series, or preparing the next race of a time attack and
   its course records) or to retrying the race. */
void Sequence::CSingleRaceModeJob::f_00bbc0()
{
    switch (D_2301b0.layer->v10(3)) {
    case 1:
        queue.push(16);
        break;
    case 2:
        queue.push(15);
        break;
    case 3:
        queue.push(17);
        break;
    case 4:
        queue.push(17);
        break;
    }
    if (!D_2301b0.m24)
        return;

    ScreenReq req;
    D_2301b0.layer->v3(&req, 0);
    switch (req.m12) {
    case 1:
        if (m16016)
            f_1521c8(m16016);
        queue.push(13);
        break;
    case 4: {
        if (m16016)
            f_1521c8(m16016);
        m15380++;
        if (m16004) {
            m15372 = (&m15380)[m15380];
            f_014dd0(m15372, m15364);
            if (m15380 < m15480)
                D_1d1638[4] = m15380;
            else
                D_1d1638[4] = 0;
        } else {
            f_014cf8(m15376, m15380);
        }
        D_1ee198.event = -1;
        Row carRow;
        FIND_SELECT(&carRow, D_240740, m15364);
        memcpy(D_24063c, D_240740.Field("Class", carRow.rec), D_1a211c[1]);
        int k = D_24063c[0] - 1;
        Param seq = D_1dd7c4;
        char *r = D_2407d0.Field("CourseNumber", (char *)seq.a);
        Row crs;
        if (r)
            crs.rec = f_036984(&D_2407a8, r, 0, D_2407a8.index, D_2407a8.count);
        else
            crs.rec = 0;
        Row c = crs;
        k = k * 24 + f_036a3c(&D_2407a8, c.rec, D_2407a8.index, D_2407a8.count);
        if (m15788)
            k += 168;
        D_1ee198.m16 = m1924[k];
        D_1ee198.m12 = m580[k];
        queue.push(14);
        break;
    }
    case 3:
        if (m16016)
            f_1521c8(m16016);
        D_1d1108 = 2;
        if (m16004 && !m16005)
            m15376 = 1;
        queue.push(9);
        break;
    case 2: {
        if (m16016)
            f_1521c8(m16016);
        int mode;
        switch (D_1d110c) {
        case 2:
            mode = 4;
            break;
        case 1:
            mode = 5;
            break;
        case 3:
            mode = 3;
            break;
        default:
            mode = 4;
            break;
        }
        D_1d1108 = mode;
        if (m16004 && !m16005)
            m15376 = 1;
        queue.push(9);
        break;
    }
    }
}

/* @implements 0x00c0bc us f_00c0bc
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00c0bc()
{
}

/* @implements 0x00c4b4 us f_00c4b4
   WHAT IT DOES: When the memory stick operation is done, restarts the front end screen and
   moves on. */
void Sequence::CSingleRaceModeJob::f_00c4b4()
{
    if (!f_01b1ac(&D_23ba90))
        return;
    D_2301b0.layer->Restart();
    queue.push(2);
}

/* @implements 0x00c538 us f_00c538
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00c538()
{
}

/* @implements 0x00c9c8 us f_00c9c8
   WHAT IT DOES: When the memory stick operation is done, restarts the front end screen and
   moves on. */
void Sequence::CSingleRaceModeJob::f_00c9c8()
{
    if (f_01b6fc(&D_23ba90)) {
        D_2301b0.layer->Restart();
        queue.push(2);
    }
}

/* @implements 0x00ca4c us f_00ca4c
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00ca4c()
{
}

/* @draft 0x00ca54 us f_00ca54
   WHAT IT DOES: Starts reading the ghost of the chosen course and car class from the memory
   stick into a new half megabyte buffer.
   Remaining difference: in the second lookup's loop entry retail puts move s1,a0 before
   addiu s3,v0,%lo(D_1a211c) (+0x104); this build swaps the two. */
void Sequence::CSingleRaceModeJob::f_00ca54()
{
    Row course, car;

    FIND_SELECT(&course, D_2407a8, m15372);
    FIND_SELECT(&car, D_240740, m15364);
    char *p = D_2407a8.Field("SelectNum", course.rec);
    int size = D_1a211c[1];
    memcpy(D_24063c, p, size);
    int c = D_24063c[0] - 1;
    memcpy(D_24063c, D_240740.Field("Class", car.rec), size);
    int k = D_24063c[0] - 1;
    int n = c * 7 + k;
    D_1ee084 = new char[0x80000];
    D_23ba90.m20 = D_1ee084;
    D_23ba90.m24 = 0x80000;
    f_01b7d4(&D_23ba90, n);
}

/* @implements 0x00ccd4 us f_00ccd4
   WHAT IT DOES: When the ghost data has been read from the memory stick, unpacks it (or, when
   the read failed, falls back to no ghost), frees the read buffer and moves on. */
void Sequence::CSingleRaceModeJob::f_00ccd4()
{
    if (f_01b91c(&D_23ba90)) {
        if (f_01a900(&D_23ba90))
            D_245178.Printf(4, "GhostLoad: %d\n", f_01730c(D_1ee084, D_23ba90.m32));
        else
            f_014950();
        if (D_1ee084)
            f_1521c8(D_1ee084);
        queue.push(2);
    }
}

/* @implements 0x00cdb0 us f_00cdb0
   WHAT IT DOES: Starts a memory stick operation. */
void Sequence::CSingleRaceModeJob::f_00cdb0()
{
    f_01ba4c(&D_23ba90);
}

/* @implements 0x00cdd0 us f_00cdd0
   WHAT IT DOES: When the memory stick operation is done, restarts the front end screen and
   moves on. */
void Sequence::CSingleRaceModeJob::f_00cdd0()
{
    if (f_01ba88(&D_23ba90)) {
        D_2301b0.layer->Restart();
        queue.push(2);
    }
}

/* @implements 0x00ce54 us f_00ce54
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00ce54()
{
}

/* @implements 0x00ce5c us f_00ce5c
   WHAT IT DOES: Starts a memory stick operation. */
void Sequence::CSingleRaceModeJob::f_00ce5c()
{
    f_01bb3c(&D_23ba90);
}

/* @implements 0x00ce7c us f_00ce7c
   WHAT IT DOES: When the memory stick operation is done, goes on to the error branch if it was
   cancelled or failed, and otherwise to the success branch. */
void Sequence::CSingleRaceModeJob::f_00ce7c()
{
    if (f_01bc5c(&D_23ba90)) {
        if (D_23ba90.m7 || !f_01a900(&D_23ba90))
            queue.push(18);
        else
            queue.push(12);
    }
}

/* @implements 0x00cf30 us f_00cf30
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00cf30()
{
}

/* @implements 0x00cf38 us f_00cf38
   WHAT IT DOES: Starts saving to the memory stick (first kind of save). */
void Sequence::CSingleRaceModeJob::f_00cf38()
{
    f_01a91c(&D_23ba90, 0);
}

/* @implements 0x00cf5c us f_00cf5c
   WHAT IT DOES: When the save is done, goes on to the success or the error branch. */
void Sequence::CSingleRaceModeJob::f_00cf5c()
{
    if (f_01abf4(&D_23ba90)) {
        if (f_01a900(&D_23ba90))
            queue.push(12);
        else
            queue.push(18);
    }
}

/* @implements 0x00cff4 us f_00cff4
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00cff4()
{
}

/* @implements 0x00cffc us f_00cffc
   WHAT IT DOES: Hands the race setup back to the shared settings and decides whether to offer
   an autosave: not when saving is off, otherwise only when there is something new to save. */
void Sequence::CSingleRaceModeJob::f_00cffc()
{
    f_009884();
    if (!f_0194c4())
        queue.push(20);
    else if (f_006018() || !D_237cfc)
        queue.push(21);
    else
        queue.push(19);
}

/* @implements 0x00d0b8 us f_00d0b8
   WHAT IT DOES: Starts saving to the memory stick (second kind of save). */
void Sequence::CSingleRaceModeJob::f_00d0b8()
{
    f_01a91c(&D_23ba90, 1);
}

/* @implements 0x00d0dc us f_00d0dc
   WHAT IT DOES: When the save is done, goes on to the success or the error branch. */
void Sequence::CSingleRaceModeJob::f_00d0dc()
{
    if (f_01abf4(&D_23ba90)) {
        if (f_01a900(&D_23ba90))
            queue.push(12);
        else
            queue.push(18);
    }
}

/* @implements 0x00d174 us f_00d174
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00d174()
{
}

/* @implements 0x00d17c us f_00d17c
   WHAT IT DOES: Starts the wireless link exchange. */
void Sequence::CSingleRaceModeJob::f_00d17c()
{
    f_099718(&D_2451f4, D_23ba90.m0);
}

/* @implements 0x00d1a4 us f_00d1a4
   WHAT IT DOES: Moves on when the wireless link exchange is done. */
void Sequence::CSingleRaceModeJob::f_00d1a4()
{
    if (f_0998d0(&D_2451f4))
        queue.push(2);
}

/* @implements 0x00d200 us f_00d200
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00d200()
{
}

/* @implements 0x00d208 us f_00d208
   WHAT IT DOES: Clears the pending link request and starts the second wireless exchange. */
void Sequence::CSingleRaceModeJob::f_00d208()
{
    D_237cc8 = 0;
    f_0997ac(&D_2451f4, 1);
}

/* @implements 0x00d234 us f_00d234
   WHAT IT DOES: Moves on when the wireless link exchange is done. */
void Sequence::CSingleRaceModeJob::f_00d234()
{
    if (f_0998d0(&D_2451f4))
        queue.push(2);
}

/* @implements 0x00d290 us f_00d290
   WHAT IT DOES: An idle state. */
void Sequence::CSingleRaceModeJob::f_00d290()
{
}

/* A screen request this file keeps for the whole game (built and destroyed by the screen
   code). */
ScreenReq D_1edf6c;

/* @implements 0x00d298 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup constructs this file's screen request; at shutdown destroys it. */

/* @implements 0x00d314 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x00d334 us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */

/* @implements 0x00d354 us Printf
   WHAT IT DOES: The debug log's print, compiled to nothing. */

/* @implements 0x00d374 us _ZN2Ng4CJob5BeginEv
   WHAT IT DOES: A job's default start: nothing. */

/* @implements 0x00d37c us _ZN2Ng4CJob4StepEv
   WHAT IT DOES: A job's default frame: reports it is not finished. */

/* @implements 0x00d384 us _ZN2Ng4CJob3EndEv
   WHAT IT DOES: A job's default stop: nothing. */

/* @implements 0x00d38c us _ZN8Sequence8CModeJob3f_4Ev
   WHAT IT DOES: A mode job's default script hook: nothing. */

/* @implements 0x00d394 us _ZN8Sequence8CModeJob3f_3Ei
   WHAT IT DOES: A mode job's default state runner: nothing. */

/* @implements 0x00d39c us _ZN8Sequence18CSingleRaceModeJob3f_3Ei
   WHAT IT DOES: Runs the handler of the given state. */

/* @implements 0x00d404 us _ZN8Sequence18CSingleRaceModeJob3f_4Ev
   WHAT IT DOES: Sends the script the "finished" event (3). */

/* @implements 0x00d434 us _ZN8Sequence18CSingleRaceModeJobD1Ev
   WHAT IT DOES: Destroys the single race job (nothing to release). */

/* @implements 0x00d444 us _ZN8Sequence18CSingleRaceModeJobD0Ev
   WHAT IT DOES: Destroys the single race job and frees it. */
