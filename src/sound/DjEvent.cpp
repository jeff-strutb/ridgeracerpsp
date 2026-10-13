/* The DJ event object file (retail 0x08d394 to 0x08e06c). The race keeps one event monitor
   (D_242be0): each frame its detector raises flags for up to 82 race events, the raised ones
   are queued, and the oldest queued event is handed to the DJ drive as a voice number. The
   monitor also keeps a small on-screen message log for debugging. */

extern "C" {
int strcmp(const char *, const char *);
int sprintf(char *, const char *, ...);
unsigned int sceKernelGetSystemTimeLow(void);
}

void f_00d354(void *log, int level, const char *fmt, ...);
void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...);
void f_0943d0(void *dj, short voice);

/* The event detector (another object file). */
void f_0900b0(void *);
void f_0900e8(void *);
void f_090320(void *);
int *f_090360(void *);
void f_090368(void *);
void f_0907c4(void *);
void f_0908c0(void *);
void f_090900(void *);
void f_09232c(void *);

/* The per-frame race checks (another object file). */
void f_08e088(void *);
void f_08e0ac(void *);
void f_08e0c8(void *);

extern char D_242c90[];
extern char D_245178[];
extern char D_24517c[];

struct CRaceInfo {
    int m0[5];
    int m20;
};
extern CRaceInfo *D_2407fc;

/* The on-screen message lines, "NULL" when free. */
char D_1d47ac[8][64] = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"};

struct CDjDetect {
    CDjDetect() { f_0900b0(this); }
    ~CDjDetect() { f_0900e8(this); }
    char m0[404];
};

struct CDjCheck {
    CDjCheck() { f_08e088(this); }
    ~CDjCheck() { f_08e0ac(this); }
    char m0[160];
};

/* A queue of up to eight event numbers. */
class CDjQueue {
public:
    CDjQueue();
    ~CDjQueue();
    void Clear()
    {
        count = 0;
        for (int i = 0; i < 8; i++)
            e[i] = 0;
    }
    void f_08dbc0(int v);
    int f_08dbe8();
    void f_08dc28();

    int e[8];
    int count;
};

/* The debug message log: the event flags of the last frame and a timer for the message lines. */
class CDjLog {
public:
    CDjLog();
    ~CDjLog();
    void f_08dd1c();
    void f_08dd5c();
    void f_08de54(const char *s);
    void f_08df0c(const char *fmt, int v);
    void f_08df40(const char *fmt, float v);
    void f_08df90();

    int timer;
    int flag[82];
};

class CDjEvent {
public:
    CDjEvent();
    ~CDjEvent();
    int f_08d484();
    int f_08d644();
    void f_08d764();
    void f_08d7f0();
    int f_08d890(int e);
    void f_08db24();

    int m0;
    int m4;
    CDjQueue queue;
    CDjLog *log;
    CDjDetect *detect;
    CDjCheck *check;
};

/* @implements 0x08d394 us _ZN8CDjEventC2Ev
   WHAT IT DOES: Builds the monitor: an empty queue, a delay of 60 and no state. */
/* @implements 0x08d3c8 us _ZN8CDjEventC1Ev
   WHAT IT DOES: The same, as the complete object. */
CDjEvent::CDjEvent()
{
    m0 = 0;
    m4 = 60;
}

/* @implements 0x08d3fc us _ZN8CDjEventD2Ev
   WHAT IT DOES: Tears the monitor down: frees its parts, then the queue. */
/* @implements 0x08d440 us _ZN8CDjEventD1Ev
   WHAT IT DOES: The same, as the complete object. */
CDjEvent::~CDjEvent()
{
    f_08d7f0();
}

/* @draft 0x08d484 us f_08d484
   WHAT IT DOES: One frame of the monitor (the timed variant). Lets the detector run for the
   race mode (0 and 1 have their own steps), copies its 82 event flags into the log, queues
   every raised event, and hands the oldest queued event to the DJ drive. Then runs the race
   checks, shows the time taken as a percentage of the frame ("IW_CPU"), and updates the log.
   Returns 0.
   Draft: three words differ; retail sets up the print call's colour and format registers
   before the buffer address (an argument order tie). */
int CDjEvent::f_08d484()
{
    unsigned int t0 = sceKernelGetSystemTimeLow();
    int mode = D_2407fc->m20;
    if (mode == 0)
        f_0907c4(detect);
    else if (mode == 1)
        f_0908c0(detect);
    int *flags = f_090360(detect);
    for (int i = 0; i < 82; i++)
        log->flag[i] = flags[i];
    for (int j = 0; j < 82; j++)
        if (flags[j] == 1)
            queue.f_08dbc0(j);
    f_090320(detect);
    int e = queue.f_08dbe8();
    if (e >= 0)
        f_0943d0(D_242c90, f_08d890(e));
    f_08e0c8(check);
    float cpu = (float)(int)(sceKernelGetSystemTimeLow() - t0) / 290.0f / 50.0f * 100.0f;
    f_02db68(D_24517c, 0x800000, 1, 3, 0xffffff, "IW_CPU:%4.1f ", cpu);
    f_090368(detect);
    log->f_08dd1c();
    return 0;
}

/* @implements 0x08d644 us f_08d644
   WHAT IT DOES: One frame of the monitor (the plain variant): nothing in race mode 2;
   otherwise the detector runs, the flags are copied and queued, the oldest queued event goes
   to the DJ drive, and the log is updated. Returns 0. */
int CDjEvent::f_08d644()
{
    if (D_2407fc->m20 == 2)
        return 0;
    f_090900(detect);
    int *flags = f_090360(detect);
    for (int i = 0; i < 82; i++)
        log->flag[i] = flags[i];
    for (int j = 0; j < 82; j++)
        if (flags[j] == 1)
            queue.f_08dbc0(j);
    f_090320(detect);
    int e = queue.f_08dbe8();
    if (e >= 0)
        f_0943d0(D_242c90, f_08d890(e));
    f_090368(detect);
    log->f_08dd1c();
    return 0;
}

/* @implements 0x08d764 us f_08d764
   WHAT IT DOES: Creates the monitor's parts: the log, the event detector and the race checks. */
void CDjEvent::f_08d764()
{
    log = new CDjLog;
    detect = new CDjDetect;
    check = new CDjCheck;
}

/* @implements 0x08d7f0 us f_08d7f0
   WHAT IT DOES: Deletes the monitor's parts and clears the pointers. */
void CDjEvent::f_08d7f0()
{
    if (log)
        delete log;
    if (detect)
        delete detect;
    if (check)
        delete check;
    log = 0;
    detect = 0;
    check = 0;
}

/* @implements 0x08d890 us f_08d890
   WHAT IT DOES: Maps an event number (0 to 81) to the DJ voice that announces it; 0 for
   events with no voice. */
int CDjEvent::f_08d890(int e)
{
    switch (e) {
    case 0: return 0;
    case 5: return 1;
    case 6: return 2;
    case 7: return 3;
    case 8: return 4;
    case 9: return 5;
    case 10: return 6;
    case 11: return 7;
    case 12: return 8;
    case 13: return 9;
    case 14: return 65;
    case 16: return 17;
    case 17: return 18;
    case 15:
    case 18: return 10;
    case 19: return 11;
    case 20: return 12;
    case 21: return 13;
    case 22: return 14;
    case 23: return 15;
    case 24: return 16;
    case 25: return 25;
    case 26: return 26;
    case 27: return 27;
    case 28: return 28;
    case 29: return 29;
    case 30: return 30;
    case 31: return 31;
    case 32: return 32;
    case 33: return 33;
    case 34: return 34;
    case 35: return 35;
    case 36: return 36;
    case 37: return 37;
    case 38: return 38;
    case 39: return 39;
    case 40: return 40;
    case 41: return 41;
    case 42: return 42;
    case 43: return 43;
    case 44: return 44;
    case 45: return 45;
    case 46: return 46;
    case 47: return 47;
    case 48: return 48;
    case 49: return 49;
    case 50: return 50;
    case 51: return 51;
    case 52: return 52;
    case 53: return 53;
    case 54: return 54;
    case 55: return 55;
    case 56: return 56;
    case 57: return 57;
    case 58: return 59;
    case 59: return 60;
    case 60: return 61;
    case 61: return 62;
    case 62: return 63;
    case 63: return 64;
    case 64: return 66;
    case 65: return 67;
    case 66: return 68;
    case 67: return 69;
    case 68: return 70;
    case 69: return 71;
    case 70: return 72;
    case 71: return 73;
    case 72: return 74;
    case 73: return 75;
    case 74: return 76;
    case 75: return 77;
    case 76: return 78;
    case 77: return 79;
    case 78: return 80;
    case 79: return 81;
    case 80: return 82;
    case 81: return 83;
    }
    return 0;
}

/* @implements 0x08db24 us f_08db24
   WHAT IT DOES: Passes a request on to the event detector. */
void CDjEvent::f_08db24()
{
    f_09232c(detect);
}

/* @implements 0x08db40 us _ZN8CDjQueueC2Ev
   WHAT IT DOES: Builds an empty queue. */
/* @implements 0x08db60 us _ZN8CDjQueueC1Ev
   WHAT IT DOES: The same, as the complete object. */
CDjQueue::CDjQueue()
{
    Clear();
}

/* @implements 0x08db80 us _ZN8CDjQueueD2Ev
   WHAT IT DOES: Empties the queue. */
/* @implements 0x08dba0 us _ZN8CDjQueueD1Ev
   WHAT IT DOES: The same, as the complete object. */
CDjQueue::~CDjQueue()
{
    Clear();
}

/* @implements 0x08dbc0 us f_08dbc0
   WHAT IT DOES: Appends an event number unless the queue is full. */
void CDjQueue::f_08dbc0(int v)
{
    if (count < 8) {
        e[count] = v;
        count++;
    }
}

/* @implements 0x08dbe8 us f_08dbe8
   WHAT IT DOES: Takes the oldest event number off the queue; -1 when it is empty. */
int CDjQueue::f_08dbe8()
{
    if (count <= 0)
        return -1;
    int r = e[0];
    for (int i = 0; i < count; i++)
        e[i] = e[i + 1];
    count--;
    return r;
}

/* @implements 0x08dc28 us f_08dc28
   WHAT IT DOES: Logs the queue's eight slots on one line. */
void CDjQueue::f_08dc28()
{
    f_00d354(D_245178, 0x800000, "Que\t");
    for (int i = 0; i < 8; i++)
        f_00d354(D_245178, 0x800000, "%d:%d ", i, e[i]);
    f_00d354(D_245178, 0x800000, "\n");
}

/* @implements 0x08dcc4 us _ZN6CDjLogC2Ev
   WHAT IT DOES: Builds the log: a 60-frame message timer and no flags. */
/* @implements 0x08dce8 us _ZN6CDjLogC1Ev
   WHAT IT DOES: The same, as the complete object. */
CDjLog::CDjLog()
{
    timer = 60;
    f_08df90();
}

/* @implements 0x08dd0c us _ZN6CDjLogD2Ev
   WHAT IT DOES: Nothing to release. */
/* @implements 0x08dd14 us _ZN6CDjLogD1Ev
   WHAT IT DOES: The same, as the complete object. */
CDjLog::~CDjLog()
{
}

/* @implements 0x08dd1c us f_08dd1c
   WHAT IT DOES: Per frame: walks the flags (the display of them is compiled out), clears them
   and shows the message lines. */
void CDjLog::f_08dd1c()
{
    for (int i = 0; i < 82; i++) {
    }
    f_08df90();
    f_08dd5c();
}

/* @implements 0x08dd5c us f_08dd5c
   WHAT IT DOES: Shows the first message line, if any, for 60 frames; then scrolls the lines
   up by one, frees the last and restarts the timer. */
void CDjLog::f_08dd5c()
{
    if (strcmp(D_1d47ac[0], "NULL")) {
        if (timer < 0) {
            for (int i = 0; i < 7; i++)
                sprintf(D_1d47ac[i], "%s", D_1d47ac[i + 1]);
            sprintf(D_1d47ac[7], "NULL");
            timer = 60;
        } else {
            f_02db68(D_24517c, 0x800000, 1, 24, 0xffffff, "DJ \" %s \" ", D_1d47ac[0]);
            timer--;
        }
    }
}

/* @draft 0x08de54 us f_08de54
   WHAT IT DOES: Puts a message into the first free line; warns when all are in use.
   Draft: the counter, the line pointer and the constant 8 get retail's registers; retail
   copies the line pointer (move v1,s1) before stepping it and saves ra last. */
void CDjLog::f_08de54(const char *s)
{
    for (int i = 0; i != 8; i++) {
        if (!strcmp(D_1d47ac[i], "NULL")) {
            sprintf(D_1d47ac[i], "%s", s);
            return;
        }
    }
    f_02db68(D_24517c, 0x800000, 1, 25, 0xffffff, "QUE ga ippai.");
}

/* @implements 0x08df0c us f_08df0c
   WHAT IT DOES: Formats a message with one integer and queues it. */
void CDjLog::f_08df0c(const char *fmt, int v)
{
    char buf[64];
    sprintf(buf, fmt, v);
    f_08de54(buf);
}

/* @implements 0x08df40 us f_08df40
   WHAT IT DOES: Formats a message with one float and queues it. */
void CDjLog::f_08df40(const char *fmt, float v)
{
    char buf[64];
    sprintf(buf, fmt, v);
    f_08de54(buf);
}

/* @implements 0x08df90 us f_08df90
   WHAT IT DOES: Clears the 82 event flags. */
void CDjLog::f_08df90()
{
    for (int i = 0; i < 82; i++)
        flag[i] = 0;
}

CDjEvent D_242be0;

/* @implements 0x08dfb0 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the event monitor; at exit, destroys it. */

/* @implements 0x08e02c us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x08e04c us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
