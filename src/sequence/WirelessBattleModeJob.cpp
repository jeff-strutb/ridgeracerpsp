/* The wireless battle mode job (retail 0x00d46c to 0x0117fc): the game mode that runs ad hoc
   races between consoles, with the lobby, the race entry, the result exchange and the memory
   stick checks around them. Like every mode job it is a state machine: a table of 41 member
   functions, one per state, a queue of state events and a small script interpreter (in the
   base class) that decides the next state. The constructors and Begin come first, then Step,
   the state handlers and the static data's initialisation, then the class's inline methods
   emitted out of line (0x01172c to 0x0117fc). The vtable
   (_ZTVN8Sequence22CWirelessBattleModeJobE) names Begin, Step, End, the state runner at
   0x01172c and the event sender at 0x011794. */

#include <string.h>

extern "C" {
int f_0160fc(void);
int f_016168(void);
}

/* The main loop job, as far as this file reads it. */
struct MainLoopJobView {
    char m0[11];
    bool m11;
    bool paused;
};
extern MainLoopJobView *D_1d88a0;

/* The front end's screen manager. Its first member is the object running the current screen,
   called through its vtable. */
class CScreen {
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
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void SetTeam(int team);
    virtual int Team();
};
struct ScreenMgr {
    CScreen *screen;
    int m4[3];
    int phase;
    int m20;
    int m24;
    bool Ready() { return phase == 4; }
};
extern ScreenMgr D_2301b0;
void f_017bfc(ScreenMgr *);
void f_017c88(ScreenMgr *);
void f_018b48(ScreenMgr *);
CScreen *f_017970(void);
void f_018af8(ScreenMgr *);

/* The ad hoc network session. */
struct NetInfo {
    char m0[11];
    signed char team;
    bool SetTeam(signed char t)
    {
        if (team == t)
            return false;
        team = t;
        return true;
    }
};
/* A player taking part in a race: name, presence, colour, console id, two small settings,
   car, the player's games played and win percentage. */
struct Racer {
    char name[10];
    signed char present;
    signed char color;
    char id[6];
    unsigned char rank : 2;
    unsigned char group : 3;
    unsigned char m18c : 3;
    unsigned char car;
    unsigned int games : 24;
    unsigned int pct : 8;
    int m24;
};

/* One console in the session: its player's name, state, colour, whether it is present, its
   car, its emblem colours, games and win percentage, its finishing time, its gap to the winner
   (-1 when it did not finish) and its distance run. */
struct NetEntry {
    char name[10];
    signed char state;
    signed char color;
    char id[6];
    signed char active;
    unsigned char car;
    unsigned int emblem : 15;
    unsigned int noEmblem : 1;
    unsigned int emblem2 : 16;
    unsigned int games : 24;
    unsigned int pct : 8;
    int time;
    int gap;
    float dist;
};
struct NetSession {
    int state;
    int m4;
    char m8[76];
    NetInfo info;
    char m96[16];
    Racer racers[2];
    NetEntry entries[8];
};
extern NetSession D_241810;
extern char D_241e98[];
void f_085ed0(NetSession *, int);
void f_087f34(NetSession *);
void f_085f58(NetSession *, int);
void f_088138(NetSession *);
int f_088338(void *);
int f_086324(NetSession *);
int f_08651c(NetSession *);
int f_08550c(NetSession *);
int f_0865e8(NetSession *);
void f_086470(NetSession *);
int f_086598(NetSession *, int, int);
int f_0859b4(NetSession *);
int f_0864c8(NetSession *);
void f_0864ec(NetSession *);
void f_086cb4(NetSession *);
int f_08640c(NetSession *);
void f_087318(NetSession *, int join, Racer *me, NetEntry *entry);
Racer *f_085928(NetSession *, char *id);
void f_085f90(NetSession *);
void f_087ac4(NetSession *, int);
void f_086afc(NetSession *);
NetEntry *f_085a1c(NetSession *, int i);
void f_086528(NetSession *, int);
void f_086440(NetSession *);

/* The race settings shared with the race itself. */
struct RaceSettings {
    int m0[6];
    int m24[336];
    int m1368[336];
    char p2712[14848 - 2712];
    int m14848;
    int m14852;
    int m14856;
    char p14860[15468 - 14860];
    int m15468;
    char p15472[15684 - 15472];
    int m15684;
    char p15688[15700 - 15688];
    int m15700;
    char p15704[15716 - 15704];
    char m15716[12];
    int m15728;
};
extern RaceSettings D_233f70;

/* The memory stick state. */
struct MemoryStick {
    int m0;
    char m4[3];
    unsigned char m7;
};
extern MemoryStick D_23ba90;
int f_01a900(MemoryStick *);
void f_01a91c(MemoryStick *, int);
int f_01abf4(MemoryStick *);
void f_01bb3c(MemoryStick *);
int f_01bc5c(MemoryStick *);

/* The system message dialog. */
extern char D_2451f4[];
void f_099718(void *dialog, int);
void f_0997ac(void *dialog, int);
int f_0998d0(void *dialog);

/* The sound and music player. */
extern char D_1dd6b0[];
void f_005554(void *, int);
int f_0056d0(void *);
void f_005720(void *);
void f_0057d0(void *);

void f_07a314(void *);
void f_07a390(void *);
void f_07a88c(void *);
void f_07a908(void *);

/* The reply the lobby screen fills in about the race settings chosen. */
struct LobbyReply {
    LobbyReply() { f_07a314(this); }
    ~LobbyReply() { f_07a390(this); }
    int m0[2];
    int m8;
    int m12;
    int m16;
    int m20;
    int m24[65];
    int m284;
    int m288[4];
};


/* A request to the lobby's message screen. */
struct LobbyMsg {
    LobbyMsg() { f_07a88c(this); }
    ~LobbyMsg() { f_07a908(this); }
    int m0[5];
    int m20;
    int m24[2];
};

void f_079478(void *);
void f_0794f4(void *);
void f_079854(void *);
void f_0798d0(void *);
void f_079a20(void *);
void f_079a9c(void *);
void f_079b78(void *);
void f_079bf4(void *);
void f_079cb8(void *);
void f_079d34(void *);
void f_0795bc(void *);
void f_079638(void *);
void f_079df8(void *);
void f_079e74(void *);
void f_07a558(void *);
void f_07a5d4(void *);
void f_07827c(void *);
void f_0782f8(void *);
void f_078358(void *);

/* Tells the lobby screen whether the link is usable. */
struct LinkMsg {
    LinkMsg() { f_079478(this); }
    ~LinkMsg() { f_0794f4(this); }
    int m0[2];
    bool ok;
};

/* The list of consoles found: names, games played, win percentages and cars. */
struct ConsoleList {
    ConsoleList() { f_079854(this); }
    ~ConsoleList() { f_0798d0(this); }
    int m0[2];
    int count;
    char name[8][8];
    int games[8];
    int pct[8];
    int car[8];
};

/* The two racers of the agreed race, as tables the screen reads. */
struct RacerList {
    RacerList() { f_079a20(this); }
    ~RacerList() { f_079a9c(this); }
    int m0[2];
    int count;
    char **names;
    int *car;
    int *pct;
    int *games;
    int *rank;
    int *group;
    int *color;
};

/* Tells the lobby screen the other console refused or dropped the race. */
struct RefusedMsg {
    RefusedMsg() { f_079b78(this); }
    ~RefusedMsg() { f_079bf4(this); }
    int m0[2];
    bool m8;
};

/* Tells the lobby screen the connection was lost. */
struct LostMsg {
    LostMsg() { f_079cb8(this); }
    ~LostMsg() { f_079d34(this); }
    int m0[2];
    bool m8;
};

/* The settings the player chose to host with. */
struct HostReply {
    HostReply() { f_0795bc(this); }
    ~HostReply() { f_079638(this); }
    int m0[2];
    int rank;
    int group;
    int color;
};

/* The session the player chose to join. */
struct JoinReply {
    JoinReply() { f_079df8(this); }
    ~JoinReply() { f_079e74(this); }
    int m0[2];
    int index;
};

/* The emblem chosen for each car. */
struct EmblemReply {
    EmblemReply() { f_07a558(this); }
    ~EmblemReply() { f_07a5d4(this); }
    int m0[21];
    int emblem[63];
};

/* The car model to preview: its model, texture, palette and reflection data. */
struct ModelMsg {
    ModelMsg() { f_07827c(this); }
    ~ModelMsg() { f_0782f8(this); }
    void Reset() { f_078358(this); }
    int m0[2];
    int mdl;
    int clut;
    int tex;
    int m20;
    int ref;
};

extern unsigned char D_1d1469;
extern int D_1d1638;
extern char D_241e98[];

extern "C" {
unsigned int f_01fa10(int);
unsigned int f_01fad0(int);
void f_003150(char *seq, int i, struct Rec *r);
void f_0030c8(char *seq, int n);
void f_0030f4(char *seq);
void f_00578c(char *seq);
int f_005c34(char *seq, const char *name);
int sprintf(char *, const char *, ...);
int f_006018(void);
int f_0160bc(void);
int f_015ce4(void);
void f_015204(void);
void f_0156d4(void);
void f_015ed8(void);
void f_016138(void);
void f_0161b8(void);
void f_016220(void);
int f_0194c4(void);
int f_014a08(void);
int f_014a28(void);
void f_014fb0(int team, int car);
}

/* The game database's tables: records found by index or by name. */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
};
extern CTable D_240740;
extern CTable D_2407a8;
extern CTable D_2407d0;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
char *f_0368e8(CTable *t, const char *field, char *rec, int a, int i);
char *f_036984(CTable *t, char *key, int i, int *index, int count);
int f_036a3c(CTable *t, char *rec, int *index, int count);

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};
extern Rec D_1dd7c4;
extern int D_1d110c;

void f_07a9d8(void *);
void f_07aa54(void *);
void f_07aab4(void *);
void f_0792a0(void *);
void f_07931c(void *);
void f_07937c(void *);
void f_07a08c(void *);
void f_07a108(void *);

/* A request to the screen manager to open a screen. */
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
   the player's position and the best lap times. */
struct RaceResult {
    char p0[120];
    int time[14];
    float lap[3];
    int me;
    int best[3];
};
extern RaceResult D_240800;

/* The result screen's message: the player's place, car and times. */
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

/* The ranking screen's list: one line per console. */
struct RankLine {
    int rank;
    int car;
    int gap;
    int m12;
    char name[12];
};
struct RankMsg {
    RankMsg() { f_07a08c(this); }
    ~RankMsg() { f_07a108(this); }
    void *vt;
    int m4;
    int count;
    RankLine line[8];
};
void f_01833c(ScreenMgr *, ScreenReq *);
void f_018380(ScreenMgr *, ResultMsg *);
void f_0184e8(ScreenMgr *, RankMsg *);
void f_018abc(ScreenMgr *, int);
extern int D_1d1108;

/* Finds the car whose SelectNum is the given number. */
#define FIND_CAR(out, num)                                                               \
    do {                                                                                 \
        Rec *o_ = (out);                                                                 \
        int key_ = (num);                                                                \
        int i_;                                                                          \
        for (i_ = 0; i_ < D_240740.count; i_++) {                                        \
            memcpy(D_24063c, f_0368e8(&D_240740, "SelectNum", 0, 0, i_), D_1a211c[1]);   \
            if (key_ == D_24063c[0])                                                     \
                break;                                                                   \
        }                                                                                \
        char *p_ = f_036984(&D_240740, 0, i_, D_240740.index, D_240740.count);           \
        if (p_)                                                                          \
            o_->rec = f_036984(&D_240740, p_, 0, D_240740.index, D_240740.count);        \
        else                                                                             \
            o_->rec = 0;                                                                 \
    } while (0)

/* The course's index in its table. */
inline int CourseIndex(Rec c)
{
    return f_036a3c(&D_2407a8, c.rec, D_2407a8.index, D_2407a8.count);
}

/* The record of the course the player chose. */
inline Rec ChosenCourse(Rec sel)
{
    Rec r;
    char *n = f_0368e8(&D_2407d0, "CourseNumber", sel.rec, 0, 0);
    if (n)
        r.rec = f_036984(&D_2407a8, n, 0, D_2407a8.index, D_2407a8.count);
    else
        r.rec = 0;
    return r;
}

extern short D_1d1310[];
extern unsigned char D_1d1368[];
extern int D_237cc8;
extern unsigned char D_237cfc;

/* This object file's own data: the two racers of a wireless battle (names, name pointers and
   per racer values) and the state of the session. */
unsigned char D_1ee088;
Racer D_1ee08c[2];
char D_1ee0c4[2][8];
char *D_1ee0d4[2];
int D_1ee0dc[2];
int D_1ee0e4[2];
int D_1ee0ec[2];
int D_1ee0f4[2];
int D_1ee0fc[2];
int D_1ee104[2];
int D_1ee10c;
int D_1ee110;
unsigned char D_1ee114;
int D_1ee118;
int D_1ee11c;
unsigned char D_1ee120;
Racer D_1ee124;
NetEntry D_1ee140;
int D_1ee168;
int D_1ee16c;
int D_1ee170;
/* What the race needs to start: the chosen event, random seeds, the course's records, the
   cars and the options. */
struct Tri {
    int v[3];
};
struct RaceStart {
    int event;
    unsigned int seed1;
    unsigned int seed2;
    int record;
    int lapRecord;
    Tri m20[3];
    int m56;
    int car[2];
    int color[2];
    int m76[2];
    int m84;
};
RaceStart D_1ee198;

/* The pad: buttons held (with repeat) and buttons newly pressed. */
namespace Controller {
class CCustomController {
public:
    int Held(int mask) { return held & mask; }
    int Trig(int mask) { return pressed & mask; }
    int m0[2];
    int held;
    int m12;
    int pressed;
};
}
extern Controller::CCustomController D_1d8910[1];

/* The network race's message display. */
extern char D_242cb0[];
void f_096408(char *);
void f_096434(char *, int);
int f_0968e0(char *);
int f_096918(char *);

/* Sets the player's team and car, finds the course chosen in the lobby and takes its
   settings, then shows the race entry (event 12). */
#define PICK_COURSE(team)                                                                \
    do {                                                                                 \
        f_014fb0((team), m3164);                                                         \
        Rec car_;                                                                        \
        FIND_CAR(&car_, m3164);                                                           \
        memcpy(D_24063c, f_0368e8(&D_240740, "Class", car_.rec, 0, 0), D_1a211c[1]);     \
        int cls_ = D_24063c[0] - 1;                                                      \
        Rec crs_ = ChosenCourse(D_1dd7c4);                                               \
        int n_ = cls_ * 24 + CourseIndex(crs_);                                          \
        D_1ee198.lapRecord = m1820[n_];                                                  \
        D_1ee198.record = m476[n_];                                                      \
        f_018af8(&D_2301b0);                                                             \
        queue.Push(12);                                                                  \
    } while (0)

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
};
}

namespace System {
class CGameModeJob {
public:
    void f_0069ec(int mode);
    unsigned int Rand()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return seed;
    }
    int m0[4];
    unsigned int seed;
};
}
extern System::CGameModeJob D_1e8ec4;

namespace Sequence {
/* The base of every mode job. Its two virtual functions after the job's own (named here by
   their vtable slot) run a state handler and send the script an event. */
class CModeJob : public Ng::CJob {
public:
    virtual void f_3(int);
    virtual void f_4();
    int f_099948(int state, int event);
};

/* A queue of sixteen state events, read at head and written at tail. */
class CStateQueue {
public:
    CStateQueue() { head = tail = 0; }
    void Push(int v)
    {
        buf[tail++] = v;
        tail &= 15;
    }
    int Pop()
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

class CWirelessBattleModeJob : public CModeJob {
public:
    typedef void (CWirelessBattleModeJob::*State)();

    CWirelessBattleModeJob();
    virtual ~CWirelessBattleModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int i) { (this->*states[i])(); }
    virtual void f_4() { queue.Push(3); }

    int f_00de58();
    void f_00e068();
    void f_00e084();
    void f_00e12c();
    void f_00e238();

    void f_00e0f4();
    void f_00e0fc();
    void f_00fcb4();
    void f_00e21c();
    void f_00e334();
    void f_00fc68();
    void f_00fc70();
    void f_00fcd8();
    void f_00fd98();
    void f_00fe44();
    void f_00fefc();
    void f_00ff74();
    void f_010100();
    void f_010170();
    void f_010284();
    void f_01028c();
    void f_01031c();
    void f_010378();
    void f_010ac4();
    void f_010b44();
    void f_010b4c();
    void f_011184();
    void f_01118c();
    void f_0111d0();
    void f_01122c();
    void f_011234();
    void f_011254();
    void f_011308();
    void f_011310();
    void f_011334();
    void f_0113cc();
    void f_0113d4();
    void f_011490();
    void f_0114b4();
    void f_01154c();
    void f_011554();
    void f_01157c();
    void f_0115d8();
    void f_0115e0();
    void f_01160c();
    void f_011668();

    int state;
    int m8[11];
    short *m52;
    unsigned char *m56;
    bool m60;
    int m64;
    int m68;
    CStateQueue queue;
    State states[41];
    int m472;
    int m476[336];
    int m1820[336];
    int m3164;
    int m3168;
    int m3172;
    int m3176;
    int m3180;
    int m3184;
    int m3188;
    char *m3192;
    int m3196;
    int m3200;
    unsigned int m3204;
    unsigned int m3208;
    signed char m3212;
    bool m3213;
    int m3216;
};
}

int f_00e2c8(void);
void f_00e30c(void);

/* @implements 0x00d46c us _ZN8Sequence22CWirelessBattleModeJobC2Ev
   WHAT IT DOES: Constructs the wireless battle mode job: an empty event queue, the table of
   state handlers and the job's script. */
/* @implements 0x00d8e8 us _ZN8Sequence22CWirelessBattleModeJobC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */
Sequence::CWirelessBattleModeJob::CWirelessBattleModeJob()
{
    states[0] = &CWirelessBattleModeJob::f_00e0f4;
    states[1] = &CWirelessBattleModeJob::f_00e0fc;
    states[2] = &CWirelessBattleModeJob::f_00fcb4;
    states[3] = &CWirelessBattleModeJob::f_00e21c;
    states[4] = &CWirelessBattleModeJob::f_00e334;
    states[5] = &CWirelessBattleModeJob::f_00fc68;
    states[6] = &CWirelessBattleModeJob::f_00fc70;
    states[7] = &CWirelessBattleModeJob::f_00fcd8;
    states[8] = &CWirelessBattleModeJob::f_00fd98;
    states[9] = &CWirelessBattleModeJob::f_00fe44;
    states[10] = &CWirelessBattleModeJob::f_00fefc;
    states[11] = &CWirelessBattleModeJob::f_00ff74;
    states[12] = &CWirelessBattleModeJob::f_010100;
    states[13] = &CWirelessBattleModeJob::f_010170;
    states[14] = &CWirelessBattleModeJob::f_010284;
    states[15] = &CWirelessBattleModeJob::f_01028c;
    states[16] = &CWirelessBattleModeJob::f_01031c;
    states[17] = &CWirelessBattleModeJob::f_010378;
    states[18] = &CWirelessBattleModeJob::f_010ac4;
    states[19] = &CWirelessBattleModeJob::f_010b44;
    states[20] = &CWirelessBattleModeJob::f_010b4c;
    states[21] = &CWirelessBattleModeJob::f_011184;
    states[22] = &CWirelessBattleModeJob::f_01118c;
    states[23] = &CWirelessBattleModeJob::f_0111d0;
    states[24] = &CWirelessBattleModeJob::f_01122c;
    states[25] = &CWirelessBattleModeJob::f_011234;
    states[26] = &CWirelessBattleModeJob::f_011254;
    states[27] = &CWirelessBattleModeJob::f_011308;
    states[28] = &CWirelessBattleModeJob::f_011310;
    states[29] = &CWirelessBattleModeJob::f_011334;
    states[30] = &CWirelessBattleModeJob::f_0113cc;
    states[31] = &CWirelessBattleModeJob::f_0113d4;
    states[32] = &CWirelessBattleModeJob::f_011490;
    states[33] = &CWirelessBattleModeJob::f_0114b4;
    states[34] = &CWirelessBattleModeJob::f_01154c;
    states[35] = &CWirelessBattleModeJob::f_011554;
    states[36] = &CWirelessBattleModeJob::f_01157c;
    states[37] = &CWirelessBattleModeJob::f_0115d8;
    states[38] = &CWirelessBattleModeJob::f_0115e0;
    states[39] = &CWirelessBattleModeJob::f_01160c;
    states[40] = &CWirelessBattleModeJob::f_011668;
    m52 = D_1d1310;
    m56 = D_1d1368;
}

/* @implements 0x00dd64 us _ZN8Sequence22CWirelessBattleModeJob5BeginEv
   WHAT IT DOES: Starts the mode from its first state, with a copy of the race settings it may
   change. */
void Sequence::CWirelessBattleModeJob::Begin()
{
    RaceSettings *g = &D_233f70;
    int i;

    m68 = 0;
    for (i = 0; i < 336; i++) {
        m476[i] = g->m24[i];
        m1820[i] = g->m1368[i];
    }
    m3164 = g->m14848;
    m60 = 1;
    m3192 = g->m15716;
    m3168 = g->m14852;
    m3172 = g->m14856;
    m3176 = g->m15468;
    m3180 = g->m15684;
    m3184 = g->m15700;
    m3188 = g->m15728;
    m68 = 0;
    state = 0;
    m64 = 0;
}

/* @implements 0x00ddf8 us _ZN8Sequence22CWirelessBattleModeJob4StepEv
   WHAT IT DOES: Runs one frame of the mode inside the network session's frame: it opens the
   session's frame, polls the session, runs the mode's frame and closes the session's frame. */
int Sequence::CWirelessBattleModeJob::Step()
{
    f_085ed0(&D_241810, 84);
    f_087f34(&D_241810);
    int r = f_00de58();
    f_085f58(&D_241810, 84);
    return r;
}

/* @implements 0x00de58 us f_00de58
   WHAT IT DOES: One frame of the mode, unless the game is paused: on the first frame of a state
   it sends the script the state's entry event; every frame it sends the update event, letting
   the script react to each queued event, and counts the frames spent in the state. Then,
   depending on the state, it updates the menu screens, or (in two states, while paused) keeps
   the network wait going. */
int Sequence::CWirelessBattleModeJob::f_00de58()
{
    int v;

    if (!D_1d88a0->paused) {
        if (m60) {
            queue.Push(0);
            while ((v = queue.Pop()) >= 0)
                f_099948(m64, v);
        }
        m60 = 0;
        queue.Push(1);
        int s = m64;
        while ((v = queue.Pop()) >= 0)
            f_099948(s, v);
        m68++;
    }
    switch (m64) {
    case 7:
    case 18:
    case 20:
        break;
    case 10:
        if (D_1d88a0->paused)
            f_0160fc();
        break;
    case 11:
        if (D_1d88a0->paused)
            f_016168();
        break;
    default:
        f_018b48(&D_2301b0);
        break;
    }
    return 0;
}

/* @implements 0x00e034 us _ZN8Sequence22CWirelessBattleModeJob3EndEv
   WHAT IT DOES: Leaves the mode: ends the network session and writes back the two race
   settings the mode keeps. */
void Sequence::CWirelessBattleModeJob::End()
{
    f_088138(&D_241810);
    f_00e068();
}

/* @implements 0x00e068 us f_00e068
   WHAT IT DOES: Writes the mode's two kept settings back into the race settings. */
void Sequence::CWirelessBattleModeJob::f_00e068()
{
    D_233f70.m15684 = m3180;
    D_233f70.m15700 = m3184;
}

/* @implements 0x00e084 us f_00e084
   WHAT IT DOES: Asks the lobby screen for the race settings the player chose and keeps the
   course and the second setting. */
void Sequence::CWirelessBattleModeJob::f_00e084()
{
    LobbyReply r;
    D_2301b0.screen->v3(&r, 0);
    m3172 = r.m20;
    m3176 = r.m284;
}

/* @implements 0x00e0f4 us f_00e0f4
   WHAT IT DOES: State 0: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_00e0f4()
{
}

/* @implements 0x00e0fc us f_00e0fc
   WHAT IT DOES: State 1: sends the script event 2. */
void Sequence::CWirelessBattleModeJob::f_00e0fc()
{
    queue.Push(2);
}

/* @implements 0x00e12c us f_00e12c
   WHAT IT DOES: Clears the racers' names and values and the session's counters. */
void Sequence::CWirelessBattleModeJob::f_00e12c()
{
    memset(D_1ee0c4, 0, sizeof(D_1ee0c4));
    memset(D_1ee0d4, 0, sizeof(D_1ee0d4));
    memset(D_1ee0dc, 0, sizeof(D_1ee0dc));
    memset(D_1ee0e4, 0, sizeof(D_1ee0e4));
    memset(D_1ee0ec, 0, sizeof(D_1ee0ec));
    memset(D_1ee0f4, 0, sizeof(D_1ee0f4));
    memset(D_1ee0fc, 0, sizeof(D_1ee0fc));
    memset(D_1ee104, 0, sizeof(D_1ee104));
    D_1ee10c = 0;
    D_1ee110 = 0;
    D_1ee114 = 0;
    D_1ee118 = 0;
    D_1ee11c = 0;
    D_1ee120 = 0;
    D_1ee16c = 0;
    m3213 = 0;
}

/* @implements 0x00e21c us f_00e21c
   WHAT IT DOES: State 3: resets the session and this mode's race data. */
void Sequence::CWirelessBattleModeJob::f_00e21c()
{
    f_00e238();
}

/* @draft 0x00e238 us f_00e238
   WHAT IT DOES: Ends any network session, clears the race data this mode exchanges and puts
   the player's name into both name slots, marking the second slot's entry word.
   Remaining difference: retail sets the entry word at +20 in one read-modify-write (lhu of
   the low half, addu 0xfbe00000, and 0xffff8000, addiu 0x1ff); the bitfield stores here give
   lw/and/ori/sw plus a separate sh of the high half. */
void Sequence::CWirelessBattleModeJob::f_00e238()
{
    f_088138(&D_241810);
    m3216 = 0;
    D_1ee088 = 0;
    f_00e12c();
    strncpy(D_1ee124.name, m3192, 9);
    strncpy(D_1ee140.name, m3192, 9);
    D_1ee140.emblem = 511;
    D_1ee140.emblem2 = 0xfbe0;
}

/* @implements 0x00e2c8 us f_00e2c8
   WHAT IT DOES: Tells whether the network link is usable: true when no session is active, or
   when the link is not in one of its three failure states. */
int f_00e2c8(void)
{
    if (!D_1ee088)
        return 1;
    int s = f_088338(D_241e98);
    int failed = s >= 8 && s <= 10;
    return failed == 0;
}

/* @implements 0x00e30c us f_00e30c
   WHAT IT DOES: Ends the network session and marks it inactive. */
void f_00e30c(void)
{
    D_1ee088 = 0;
    f_088138(&D_241810);
}

/* @draft 0x00e334 us f_00e334
   WHAT IT DOES: State 4: the wireless lobby itself, run every frame. It draws two random
   numbers for the session, tells the lobby screen how the link is (and whether this console
   hosts), and follows the session's state: it lists the consoles found while searching (state
   8), collects the two racers' names, cars, colours and records once a race is agreed (states
   12 and 2, after three seconds), and reports a lost or refused connection (states 6 and 4).
   It then acts on the lobby screen's request: host a race (1), join one (2), pick a session
   to join (5), cancel the search (6), leave (7), show the consoles in the chosen session (8)
   or end the session (9). It previews the car the player points at, and when the player
   leaves the screen it ends the session (event 6); when the screen is done it takes the race
   settings, the random seeds, the course records and the player's car for the race and moves
   on (event 4). */
void Sequence::CWirelessBattleModeJob::f_00e334()
{
    m3204 = D_1e8ec4.Rand();
    m3208 = D_1e8ec4.Rand();
    int link = f_088338(D_241e98);
    int st = D_241810.state;
    if (st == 8) {
        LinkMsg msg;
        msg.ok = f_00e2c8();
        D_2301b0.screen->v2(&msg, 0);
    } else if (D_241810.m4 == 1 && !m3213) {
        LinkMsg msg;
        msg.ok = f_00e2c8();
        D_2301b0.screen->v2(&msg, 0);
        m3213 = 1;
    }
    if (st == 11)
        D_2301b0.screen->v13();
    else if (D_1ee088 && (link == 11 || st == 4 || st == 10 || st == 9))
        D_2301b0.screen->v11();
    else if (!f_00e2c8())
        D_2301b0.screen->v12();

    int i, n;
    if (st == 8) {
        ConsoleList list;
        NetEntry *e = D_241810.entries;
        n = 0;
        for (i = 0; i < 8; i++, e++) {
            if (e->active && e->state == 1) {
                sprintf(list.name[n], "%s", e->name);
                list.games[n] = e->games;
                list.pct[n] = e->pct;
                list.car[n] = e->car;
                n++;
            }
        }
        list.count = n;
        if (n == 8)
            f_087ac4(&D_241810, 1);
        for (; n < 8; n++)
            ;
        D_2301b0.screen->v2(&list, 0);
    }
    if (st == 12) {
        D_1ee10c++;
        if (D_1ee110 == 0 && D_1ee10c > 180) {
            D_1ee110 = 1;
            for (i = 0; i < 2; i++)
                D_1ee0d4[i] = D_1ee0c4[i];
            RacerList rl;
            rl.names = D_1ee0d4;
            rl.car = D_1ee0ec;
            rl.pct = D_1ee0f4;
            rl.games = D_1ee0fc;
            rl.rank = D_1ee104;
            rl.group = D_1ee0dc;
            rl.color = D_1ee0e4;
            n = 0;
            for (i = 0; i < 2; i++) {
                Racer *r = &D_241810.racers[i];
                D_1ee08c[i] = *r;
                if (r->present) {
                    sprintf(D_1ee0c4[n], "%s", r->name);
                    D_1ee0dc[n] = r->group;
                    D_1ee0e4[n] = r->color;
                    D_1ee0ec[n] = r->car;
                    D_1ee0f4[n] = r->pct;
                    D_1ee0fc[n] = r->games;
                    D_1ee104[n] = r->rank;
                    n++;
                }
            }
            rl.count = n;
            for (; n < 2; n++)
                D_1ee0c4[n][0] = 0;
            D_2301b0.screen->v2(&rl, 0);
        } else if (D_1ee110 == 1) {
            n = 0;
            for (i = 0; i < 2; i++) {
                Racer *r = &D_241810.racers[i];
                D_1ee08c[i] = *r;
                if (r->present) {
                    sprintf(D_1ee0c4[n], "%s", r->name);
                    D_1ee0dc[n] = r->group;
                    D_1ee0e4[n] = r->color;
                    D_1ee0ec[n] = r->car;
                    D_1ee0f4[n] = r->pct;
                    D_1ee0fc[n] = r->games;
                    D_1ee104[n] = r->rank;
                    n++;
                }
            }
        }
    }
    if (st == 2) {
        D_1ee10c++;
        if (D_1ee110 == 0 && D_1ee10c > 180) {
            D_1ee110 = 1;
            for (i = 0; i < 2; i++)
                D_1ee0d4[i] = D_1ee0c4[i];
            RacerList rl;
            rl.names = D_1ee0d4;
            rl.car = D_1ee0ec;
            rl.pct = D_1ee0f4;
            rl.games = D_1ee0fc;
            rl.rank = D_1ee104;
            rl.group = D_1ee0dc;
            rl.color = D_1ee0e4;
            n = 0;
            for (i = 0; i < 2; i++) {
                Racer *r = &D_241810.racers[i];
                D_1ee08c[i] = *r;
                if (r->present) {
                    sprintf(D_1ee0c4[n], "%s", r->name);
                    D_1ee0dc[n] = r->group;
                    D_1ee0e4[n] = r->color;
                    D_1ee0ec[n] = r->car;
                    D_1ee0f4[n] = r->pct;
                    D_1ee0fc[n] = r->games;
                    D_1ee104[n] = r->rank;
                    n++;
                }
            }
            rl.count = n;
            for (; n < 2; n++)
                D_1ee0c4[n][0] = 0;
            if (rl.count == 0 && f_088338(D_241e98) == 5)
                f_088138(&D_241810);
            D_2301b0.screen->v2(&rl, 0);
        } else if (D_1ee110 == 1) {
            n = 0;
            for (i = 0; i < 2; i++) {
                Racer *r = &D_241810.racers[i];
                D_1ee08c[i] = *r;
                if (r->present) {
                    sprintf(D_1ee0c4[n], "%s", r->name);
                    D_1ee0dc[n] = r->group;
                    D_1ee0e4[n] = r->color;
                    D_1ee0ec[n] = r->car;
                    D_1ee0f4[n] = r->pct;
                    D_1ee0fc[n] = r->games;
                    D_1ee104[n] = r->rank;
                    n++;
                }
            }
        }
    }
    if (st == 6 && D_1ee110 == 2) {
        D_1ee110 = 3;
        RefusedMsg m;
        m.m8 = 1;
        D_2301b0.screen->v2(&m, 0);
        if (!f_08651c(&D_241810)) {
            f_0057d0(D_1dd6b0);
            queue.Push(7);
        }
    } else if (st == 4) {
        if (D_1ee110 == 2) {
            D_1ee110 = 3;
            if (f_088338(D_241e98) == 5)
                f_088138(&D_241810);
            RefusedMsg m;
            m.m8 = 0;
            D_2301b0.screen->v2(&m, 0);
        }
    } else if (!f_08640c(&D_241810) && D_1ee110 == 3) {
        D_1ee110 = 4;
        LostMsg m;
        m.m8 = 1;
        D_2301b0.screen->v2(&m, 0);
    }

    switch (D_2301b0.screen->v10(2)) {
    case 1: {
        f_00e12c();
        int pct = 0;
        if (m3180)
            pct = m3184 * 100 / m3180;
        D_1ee140.pct = pct;
        D_1ee140.games = m3180;
        HostReply h;
        D_2301b0.screen->v3(&h, 0);
        m3168 = h.color;
        m3196 = h.group;
        m3200 = h.rank;
        f_088138(&D_241810);
        D_1ee124.pct = pct;
        D_1ee124.color = m3168;
        D_1ee124.games = m3180;
        D_1ee124.rank = m3200;
        D_1ee088 = 1;
        D_1ee124.group = m3196;
        D_1ee168 = 0;
        f_087318(&D_241810, 0, &D_1ee124, &D_1ee140);
        D_1ee10c = 0;
        D_1ee110 = 0;
        break;
    }
    case 2:
        f_00e12c();
        f_088138(&D_241810);
        D_1ee088 = 1;
        D_1ee168 = 1;
        f_087318(&D_241810, 1, &D_1ee124, &D_1ee140);
        D_1ee10c = 0;
        D_1ee110 = 0;
        break;
    case 5: {
        JoinReply j;
        D_2301b0.screen->v3(&j, 0);
        D_1ee10c = 0;
        D_1ee16c = j.index;
        D_1ee110 = 2;
        if (st == 2) {
            Racer *e = f_085928(&D_241810, D_1ee08c[j.index].id);
            if (e) {
                m3168 = e->color;
                m3200 = e->rank;
                int pct = 0;
                if (m3180)
                    pct = m3184 * 100 / m3180;
                D_241810.entries[0].pct = pct;
                D_241810.entries[0].games = m3180;
                f_085f90(&D_241810);
            } else {
                D_1ee110 = 3;
                RefusedMsg m;
                m.m8 = 0;
                D_2301b0.screen->v2(&m, 0);
            }
        }
        break;
    }
    case 6:
        f_087ac4(&D_241810, 1);
        break;
    case 7:
        f_00e30c();
        break;
    case 8: {
        if (D_1d1469)
            D_1d1469 = 0;
        ConsoleList list;
        LobbyReply r;
        D_2301b0.screen->v3(&r, 0);
        m3164 = r.m12;
        NetEntry *me = &D_241810.entries[0];
        EmblemReply q;
        D_2301b0.screen->v3(&q, 0);
        int em = q.emblem[m3164];
        if (em) {
            me->noEmblem = 0;
            unsigned int c = f_01fa10(em - 1);
            me->emblem2 = ((c >> 19) << 11) + (((c >> 10) & 0x3f) << 5) + ((c & 0xff) >> 3);
            unsigned int d = f_01fad0(em - 1);
            me->emblem = ((d >> 19) & 0x1f) * 1024 + ((d >> 11) & 0x1f) * 32 + ((d & 0xff) >> 3);
        } else {
            me->noEmblem = 1;
        }
        if (me->car != m3164)
            me->car = m3164;
        f_086afc(&D_241810);
        n = 0;
        for (int k = 0; k < 8; k++) {
            NetEntry *e = f_085a1c(&D_241810, k);
            if (e) {
                sprintf(list.name[n], "%s", e->name);
                list.games[n] = e->games;
                list.pct[n] = e->pct;
                list.car[n] = e->car;
                n++;
            }
        }
        list.count = n;
        for (; n < 8; n++)
            list.name[n][0] = 0;
        D_2301b0.screen->v2(&list, 0);
        f_086528(&D_241810, 1);
        if (f_0865e8(&D_241810))
            f_018af8(&D_2301b0);
        break;
    }
    case 9:
        f_088138(&D_241810);
        break;
    }

    int car = D_2301b0.screen->v10(7);
    if (car < 0) {
        car = 0;
        if (D_1ee120) {
            D_1ee120 = 0;
            D_1ee118 = 0;
            D_1ee114 = 0;
            f_00578c(D_1dd6b0);
        }
    }
    if (car == 0 && !D_1ee114)
        car = D_1ee118;
    if (car != 0) {
        D_1ee118 = car;
        if (!D_1ee114 && !f_0056d0(D_1dd6b0)) {
            Rec c;
            FIND_CAR(&c, car);
            f_003150(D_1dd6b0, 0, &c);
            f_0030c8(D_1dd6b0, 4);
            f_005554(D_1dd6b0, 1);
            D_1ee11c = car;
            D_1ee120 = 1;
            D_1ee114 = 1;
        }
    }
    if (D_1ee114 && !f_0056d0(D_1dd6b0)) {
        D_1ee114 = 0;
        if (D_1ee11c == D_1ee118) {
            D_1ee118 = 0;
            ModelMsg mm;
            mm.Reset();
            mm.mdl = f_005c34(D_1dd6b0, "Mdl");
            mm.tex = f_005c34(D_1dd6b0, "Tex");
            mm.clut = f_005c34(D_1dd6b0, "Clut");
            mm.ref = f_005c34(D_1dd6b0, "Ref");
            D_2301b0.screen->v2(&mm, 0);
        }
    }

    D_2301b0.screen->v10(3);
    if (D_2301b0.screen->v10(6) == 2) {
        f_00e30c();
        f_00e084();
        f_00e068();
        queue.Push(6);
        return;
    }
    if (!D_2301b0.m24)
        return;
    LobbyReply r;
    D_2301b0.screen->v3(&r, 0);
    D_1d110c = r.m8;
    D_1d1108 = 6;
    f_00e084();
    f_0030f4(D_1dd6b0);
    {
        EmblemReply q;
        D_2301b0.screen->v3(&q, 0);
        D_1d1638 = q.emblem[m3164] - 1;
    }
    D_1ee198.m84 = m3188;
    D_1ee198.event = m3176;
    D_1ee198.seed1 = D_1e8ec4.Rand();
    D_1ee198.seed2 = D_1e8ec4.Rand();
    f_014fb0(m3168, m3164);
    Rec c;
    FIND_CAR(&c, m3164);
    memcpy(D_24063c, f_0368e8(&D_240740, "Class", c.rec, 0, 0), D_1a211c[1]);
    int cls = D_24063c[0] - 1;
    Rec crs = ChosenCourse(D_1dd7c4);
    int k = cls * 24 + CourseIndex(crs);
    D_1ee198.car[0] = m3164;
    D_1ee198.m76[0] = 0;
    D_1ee198.color[0] = m3172 - 1;
    D_1ee198.lapRecord = m1820[k];
    D_1ee198.record = m476[k];
    D_1ee198.m56 = 1;
    queue.Push(4);
}

/* @implements 0x00fc68 us f_00fc68
   WHAT IT DOES: State 5: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_00fc68()
{
}

/* @implements 0x00fc70 us f_00fc70
   WHAT IT DOES: State 6: sends the script event 2 once the screen manager is idle. */
void Sequence::CWirelessBattleModeJob::f_00fc70()
{
    if (D_2301b0.phase == 0)
        queue.Push(2);
}

/* @implements 0x00fcb4 us f_00fcb4
   WHAT IT DOES: State 2: asks the game mode job to switch to mode 1 (the main menu). */
void Sequence::CWirelessBattleModeJob::f_00fcb4()
{
    D_1e8ec4.f_0069ec(1);
}

/* @implements 0x00fcd8 us f_00fcd8
   WHAT IT DOES: State 7: sends event 2 when the lobby step is done; if the network session is
   down, stops the sound and sends event 7. */
void Sequence::CWirelessBattleModeJob::f_00fcd8()
{
    if (f_015ce4())
        queue.Push(2);
    if (!f_086324(&D_241810) || !f_08651c(&D_241810)) {
        f_0057d0(D_1dd6b0);
        queue.Push(7);
    }
}

/* @implements 0x00fd98 us f_00fd98
   WHAT IT DOES: State 8: on its first frame starts the lobby screen and its music; later sends
   event 2 once the music has stopped. The screen manager is updated every frame. */
void Sequence::CWirelessBattleModeJob::f_00fd98()
{
    if (m68 == 1) {
        f_005720(D_1dd6b0);
        f_015204();
        f_005554(D_1dd6b0, 1);
    } else if (!f_0056d0(D_1dd6b0)) {
        queue.Push(2);
    }
    f_017bfc(&D_2301b0);
}

/* @implements 0x00fe44 us f_00fe44
   WHAT IT DOES: State 9: on its first frame starts the next screen and its music; once the
   music has stopped it closes the screen manager's step, finishes the screen and sends event
   2; otherwise the screen manager is updated. */
void Sequence::CWirelessBattleModeJob::f_00fe44()
{
    if (m68 == 1) {
        f_0156d4();
        f_005554(D_1dd6b0, 1);
    } else {
        if (f_0056d0(D_1dd6b0))
            goto update;
        f_017c88(&D_2301b0);
        f_015ed8();
        queue.Push(2);
        return;
    }
update:
    f_017bfc(&D_2301b0);
}

/* @implements 0x00fefc us f_00fefc
   WHAT IT DOES: State 10: clears the retry counter, opens the lobby, starts the network session
   if it is not running and sends event 2. */
void Sequence::CWirelessBattleModeJob::f_00fefc()
{
    m3212 = 0;
    f_0160bc();
    if (!D_241810.m4)
        f_086440(&D_241810);
    queue.Push(2);
}

/* @implements 0x00ff74 us f_00ff74
   WHAT IT DOES: State 11: waits in the lobby. When the lobby closes, it ends the session for
   results 2 and 3 (remembering why, event 9) and goes on with event 5 otherwise. While the
   lobby is open, holding cancel or the second button for six frames after pressing it asks
   to leave (event 8). */
void Sequence::CWirelessBattleModeJob::f_00ff74()
{
    int r = f_0160fc();
    if (r) {
        f_0161b8();
        f_096408(D_242cb0);
        if (r == 2 || r == 3) {
            f_00e30c();
            D_1ee170 = r;
            queue.Push(9);
        } else {
            queue.Push(5);
        }
        return;
    }
    if (f_014a28() == 1)
        f_096434(D_242cb0, -1);
    if (D_1d8910[0].Trig(2) || D_1d8910[0].Trig(0x400000)) {
        m3212 = 1;
    } else if (m3212 > 0 && (D_1d8910[0].Held(2) || D_1d8910[0].Held(0x400000))) {
        m3212++;
        if (m3212 >= 6) {
            m3212 = 0;
            if (f_014a08()) {
                f_0968e0(D_242cb0);
                queue.Push(8);
            }
        }
    } else {
        m3212 = 0;
    }
}

/* @implements 0x010100 us f_010100
   WHAT IT DOES: State 12: shows the lobby message for the session's role (1 when joining, 2
   when hosting). */
void Sequence::CWirelessBattleModeJob::f_010100()
{
    LobbyMsg msg;
    int hosting = D_1ee168 != 0;
    msg.m20 = hosting + 1;
    f_017970()->v2(&msg, 0);
}

/* @implements 0x010170 us f_010170
   WHAT IT DOES: State 13: waits for the race entry screen. When the player enters, it starts
   the session as host if it is not running; when the entry is cancelled it ends the session
   and leaves (event 10); when the entry fails, or the session drops while waiting, it shows
   the error and goes back (event 6). */
void Sequence::CWirelessBattleModeJob::f_010170()
{
    switch (f_016168()) {
    case 2:
        if (!D_241810.m4 && f_0865e8(&D_241810)) {
            f_096408(D_242cb0);
            f_086470(&D_241810);
        }
        break;
    case 4:
    case 5:
        f_00e30c();
        f_096408(D_242cb0);
        queue.Push(10);
        break;
    case 1:
        f_096918(D_242cb0);
        queue.Push(6);
        break;
    default:
        if (f_08550c(&D_241810) != 7) {
            f_096918(D_242cb0);
            queue.Push(6);
        }
        break;
    }
}

/* @implements 0x010284 us f_010284
   WHAT IT DOES: State 14: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_010284()
{
}

/* @implements 0x01028c us f_01028c
   WHAT IT DOES: State 15: on its first frame opens the wait screen; when the wait is over it
   closes it, sends event 2 and clears the main loop's flag. */
void Sequence::CWirelessBattleModeJob::f_01028c()
{
    if (m68 == 1)
        f_016138();
    if (f_0160fc()) {
        f_0161b8();
        queue.Push(2);
        D_1d88a0->m11 = 0;
    }
}

/* @implements 0x01031c us f_01031c
   WHAT IT DOES: State 16: closes the lobby, stops the sound and sends event 2. */
void Sequence::CWirelessBattleModeJob::f_01031c()
{
    f_016220();
    f_0057d0(D_1dd6b0);
    queue.Push(2);
}

/* @draft 0x010378 us f_010378
   WHAT IT DOES: State 17: shows the race result. It finds the record slot of the chosen course
   and car class, opens the result screen, fills the result message with the player's place,
   car, finishing time, best laps, lap times and the course record, then ranks the consoles
   that finished (by gap to the winner; those that did not finish after them, by distance run)
   and shows the ranking with each player's car and gap. It counts a win when the player's
   time is the winner's and a loss otherwise. */
void Sequence::CWirelessBattleModeJob::f_010378()
{
    int me = D_240800.me;
    Rec car;
    FIND_CAR(&car, m3164);
    memcpy(D_24063c, f_0368e8(&D_240740, "Class", car.rec, 0, 0), D_1a211c[1]);
    int cls = D_24063c[0] - 1;
    Rec crs = ChosenCourse(D_1dd7c4);
    int k = cls * 24 + CourseIndex(crs);

    ScreenReq req;
    req.Reset();
    req.m12 = D_1d110c;
    req.m16 = m3188;
    req.m8 = D_1ee168 == 0;
    req.m17 = 0;
    req.m18 = 0;
    f_01833c(&D_2301b0, &req);

    ResultMsg m;
    m.Reset();
    m.time = D_240800.time[me] / 3;
    m.car = m3164;
    m.color = m3168;
    m.place = me + 1;
    m.m24 = 1;
    m.m20 = 1;
    m.record = (unsigned int)m476[k] / 3;
    int i;
    for (i = 0; i < 6; i++)
        m.laps[i] = 0;
    m.avg = 0;
    for (i = 0; i < 6; i++)
        m.lapMs[i] = 0;
    m.bestLap = -1;
    for (i = 0; i < 3; i++)
        m.laps[i] = D_240800.best[i] / 3;
    for (i = 0; i < 3; i++)
        m.lapMs[i] = (unsigned int)(D_240800.lap[i] * 1000.0f);
    m.newRecord = 0;
    m.m93 = 0;
    m.m112 = 0;
    f_018380(&D_2301b0, &m);

    NetEntry *e = D_241810.entries;
    int list[8];
    int n = 0;
    for (i = 0; i < 8; i++)
        if (e[i].active && e[i].time != -2)
            list[n++] = i;
    for (i = 0; i < n - 1; i++) {
        int b = i;
        for (int j = i + 1; j < n; j++) {
            NetEntry *pj = &e[list[j]];
            NetEntry *pb = &e[list[b]];
            if (pj->gap == -1) {
                if (pb->gap == -1 && !(pj->dist < pb->dist))
                    b = j;
            } else if (pb->gap == -1 || !(pb->gap < pj->gap)) {
                b = j;
            }
        }
        int t = list[b];
        list[b] = list[i];
        list[i] = t;
    }

    RankMsg r;
    for (i = 0; i < n; i++) {
        r.line[i].rank = i + 1;
        r.line[i].car = e[list[i]].car;
        if (i == 0)
            r.line[i].gap = e[list[0]].time / 3;
        else if (e[list[i]].gap == -1)
            r.line[i].gap = 0;
        else
            r.line[i].gap = (e[list[i]].gap - e[list[0]].gap) / 3;
        r.line[i].m12 = 1;
        sprintf(r.line[i].name, "%s", e[list[i]].name);
    }
    for (; i < 8; i++)
        r.line[i].name[0] = 0;
    r.count = n;
    f_0184e8(&D_2301b0, &r);
    if (e[list[0]].time != D_240800.time[me])
        m3180++;
    else
        m3184++;
    f_018abc(&D_2301b0, 13);
}

/* State 18 (retail 0x010ac4). Byte-exact, but left untagged here: the compiler control set
   (src/control/batch2.c) already holds that address's tag.
   WHAT IT DOES: State 18: updates the screen manager; once it is ready, finishes its step and
   sends event 2. */
void Sequence::CWirelessBattleModeJob::f_010ac4()
{
    f_017bfc(&D_2301b0);
    if (D_2301b0.Ready()) {
        f_017c88(&D_2301b0);
        queue.Push(2);
    }
}

/* @implements 0x010b44 us f_010b44
   WHAT IT DOES: State 19: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_010b44()
{
}

/* @draft 0x010b4c us f_010b4c
   WHAT IT DOES: State 20: the lobby. As a guest it keeps the screen's team choice and the
   session's in step; as host it follows the host's choice. When the session is ready the race
   course is picked (event 12); when the session is lost it ends it and goes back (event 7).
   Otherwise, once the screen has an answer: leaving with 3 or 0 and 2 ends the session and
   goes back to the menu (event 10), 4 enters the race (event 12) and 1 restarts the session as
   host when it is not running. */
void Sequence::CWirelessBattleModeJob::f_010b4c()
{
    if (D_241810.m4 == 1) {
        D_2301b0.screen->SetTeam(D_241810.info.team);
        m3168 = D_2301b0.screen->Team();
        if (f_0864c8(&D_241810)) {
            f_0864ec(&D_241810);
            PICK_COURSE(m3168);
            return;
        }
    } else {
        signed char team = D_2301b0.screen->Team();
        if (D_241810.info.SetTeam(team)) {
            f_086cb4(&D_241810);
            m3168 = team;
        }
        if (f_08550c(&D_241810) == 4) {
            if (D_241810.state != 8 || f_0859b4(&D_241810) < 2) {
                f_088138(&D_241810);
                queue.Push(7);
                return;
            }
        }
        if (f_086598(&D_241810, 4, 1)) {
            if (D_241810.state != 8) {
                queue.Push(7);
                return;
            }
            PICK_COURSE(team);
            return;
        }
    }
    if (!D_2301b0.m24)
        return;
    ScreenReq req;
    D_2301b0.screen->v3(&req, 0);
    switch (req.m12) {
    case 1:
        if (!D_241810.m4 && f_08550c(&D_241810) != 4)
            f_086470(&D_241810);
        break;
    case 3:
        f_00e30c();
        D_1d1108 = 2;
        queue.Push(10);
        break;
    case 4:
        queue.Push(12);
        break;
    case 2:
    default:
        f_00e30c();
        D_1d1108 = 6;
        queue.Push(10);
        break;
    }
}

/* @implements 0x011184 us f_011184
   WHAT IT DOES: State 21: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_011184()
{
}

/* @implements 0x01118c us f_01118c
   WHAT IT DOES: State 22: opens the system message dialog, with message 2 when the race ended
   for reason 3 and message 0 otherwise. */
void Sequence::CWirelessBattleModeJob::f_01118c()
{
    if (D_1ee170 == 3)
        f_0997ac(D_2451f4, 2);
    else
        f_0997ac(D_2451f4, 0);
}

/* @implements 0x0111d0 us f_0111d0
   WHAT IT DOES: State 23: sends event 2 when the message dialog closes. */
void Sequence::CWirelessBattleModeJob::f_0111d0()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x01122c us f_01122c
   WHAT IT DOES: State 24: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_01122c()
{
}

/* @implements 0x011234 us f_011234
   WHAT IT DOES: State 25: starts checking the memory stick. */
void Sequence::CWirelessBattleModeJob::f_011234()
{
    f_01bb3c(&D_23ba90);
}

/* @implements 0x011254 us f_011254
   WHAT IT DOES: State 26: when the memory stick check is done, sends event 13 if the stick can
   be written, and event 7 otherwise. */
void Sequence::CWirelessBattleModeJob::f_011254()
{
    if (!f_01bc5c(&D_23ba90))
        return;
    if (!D_23ba90.m7 && f_01a900(&D_23ba90))
        queue.Push(13);
    else
        queue.Push(7);
}

/* @implements 0x011308 us f_011308
   WHAT IT DOES: State 27: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_011308()
{
}

/* @implements 0x011310 us f_011310
   WHAT IT DOES: State 28: starts loading the save data from the memory stick. */
void Sequence::CWirelessBattleModeJob::f_011310()
{
    f_01a91c(&D_23ba90, 0);
}

/* @implements 0x011334 us f_011334
   WHAT IT DOES: State 29: when the memory stick access is done, sends event 13 on success and
   event 7 on failure. */
void Sequence::CWirelessBattleModeJob::f_011334()
{
    if (!f_01abf4(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90))
        queue.Push(13);
    else
        queue.Push(7);
}

/* @implements 0x0113cc us f_0113cc
   WHAT IT DOES: State 30: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_0113cc()
{
}

/* @implements 0x0113d4 us f_0113d4
   WHAT IT DOES: State 31: writes the kept settings back, then sends event 15 when there is
   nothing new to save, event 14 when the game should save automatically, and event 16
   otherwise. */
void Sequence::CWirelessBattleModeJob::f_0113d4()
{
    f_00e068();
    if (!f_0194c4())
        queue.Push(15);
    else if (f_006018() || !D_237cfc)
        queue.Push(16);
    else
        queue.Push(14);
}

/* @implements 0x011490 us f_011490
   WHAT IT DOES: State 32: starts writing the save data to the memory stick. */
void Sequence::CWirelessBattleModeJob::f_011490()
{
    f_01a91c(&D_23ba90, 1);
}

/* @implements 0x0114b4 us f_0114b4
   WHAT IT DOES: State 33: when the memory stick access is done, sends event 13 on success and
   event 7 on failure. */
void Sequence::CWirelessBattleModeJob::f_0114b4()
{
    if (!f_01abf4(&D_23ba90))
        return;
    if (f_01a900(&D_23ba90))
        queue.Push(13);
    else
        queue.Push(7);
}

/* @implements 0x01154c us f_01154c
   WHAT IT DOES: State 34: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_01154c()
{
}

/* @implements 0x011554 us f_011554
   WHAT IT DOES: State 35: opens the system message dialog for the memory stick's error. */
void Sequence::CWirelessBattleModeJob::f_011554()
{
    f_099718(D_2451f4, D_23ba90.m0);
}

/* @implements 0x01157c us f_01157c
   WHAT IT DOES: State 36: sends event 2 when the message dialog closes. */
void Sequence::CWirelessBattleModeJob::f_01157c()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x0115d8 us f_0115d8
   WHAT IT DOES: State 37: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_0115d8()
{
}

/* @implements 0x0115e0 us f_0115e0
   WHAT IT DOES: State 38: clears the pending save flag and opens the system message dialog
   with message 1. */
void Sequence::CWirelessBattleModeJob::f_0115e0()
{
    D_237cc8 = 0;
    f_0997ac(D_2451f4, 1);
}

/* @implements 0x01160c us f_01160c
   WHAT IT DOES: State 39: sends event 2 when the message dialog closes. */
void Sequence::CWirelessBattleModeJob::f_01160c()
{
    if (f_0998d0(D_2451f4))
        queue.Push(2);
}

/* @implements 0x011668 us f_011668
   WHAT IT DOES: State 40: nothing to do. */
void Sequence::CWirelessBattleModeJob::f_011668()
{
}

/* The static data of this object file: the lobby's screen request, built at startup. */
ScreenReq D_1ee174;

/* @implements 0x011670 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the lobby's screen request; at shutdown, destroys it. */

/* @implements 0x0116ec us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x01170c us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */

/* The class's inline virtual functions and destructors, emitted out of line here with the
   vtable.
   @implements 0x01172c us _ZN8Sequence22CWirelessBattleModeJob3f_3Ei
   WHAT IT DOES: Runs the state handler the script names. */

/* @implements 0x011794 us _ZN8Sequence22CWirelessBattleModeJob3f_4Ev
   WHAT IT DOES: Sends the script event 3. */

/* @implements 0x0117c4 us _ZN8Sequence22CWirelessBattleModeJobD1Ev
   WHAT IT DOES: The destructor, which has nothing to release. */
/* @implements 0x0117d4 us _ZN8Sequence22CWirelessBattleModeJobD0Ev
   WHAT IT DOES: The deleting destructor: destroys the job and frees its memory. */
