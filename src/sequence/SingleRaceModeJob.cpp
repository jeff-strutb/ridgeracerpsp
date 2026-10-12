/* The single race mode job, its start (retail 0x008838 to 0x00968c): the constructors and Begin.
   The single race job runs races against the computer cars, time trials and the race menus
   around them; the rest of the class (from its Step at 0x00968c) is in
   SingleRaceModeJobStates.cpp. Its base classes define their virtual functions inline here, so
   the constructors also set up the base classes' vtables on the way. */

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

/* The race mode the main menu selected. */
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

    int sp;
    int pc;
    int stack[10];
    short *table;
    unsigned char *code;
    bool entered;
    int state;
    int frames;
};

class CSingleRaceModeJob : public CModeJob {
public:
    typedef void (CSingleRaceModeJob::*State)();

    CSingleRaceModeJob();
    virtual ~CSingleRaceModeJob() {}
    virtual void Begin();
    virtual int Step();
    virtual void End();
    virtual void f_3(int i);
    virtual void f_4();

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

    CStateQueue queue;
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
    int m15384[25];
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
    int m16008;
    int m16012;
    int m16016[3];
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
