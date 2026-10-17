/* The radio DJ's playback state machine object file (retail 0x0f8610 to 0x0f970c; its debug
   prints say "RadioState" and "StateManager"). The 240 byte object owns two stream players
   (RadioStream.cpp) and plays one queue node: for each script of the node it picks the
   stream channel of the script's speaker, asks the stream for the script's sound files one
   after another, waits for each to be ready and to end, and waits out the blank time
   between scripts. When the next script is on the other channel the two players are swapped
   so the next file can be prepared while the current one plays. */

void f_093f90(const char *fmt, ...);

extern "C" {
int f_10ab7c(signed char speaker);

/* The stream player (its own object file). */
void f_0f9778(void *s);
void f_0f9844(void *s);
int f_0f98a4(void *s, int table, int script);
int f_0f990c(void *s);
void f_0f9914(void *s);
int f_0f9944(void *s);
int f_0f9960(void *s);
int f_0f997c(void *s, int ch, int b);
int f_0f9984(void *s, int ch);
int f_0f998c(void *s);
int f_0f99a8(void *s);
int f_0f99b0(void *s, int script, int r);
int f_0f99b8(void *s);
int f_0f99c0(void *s, int script);
}

int D_27f0a0;   /* frames spent waiting for a stream to get ready */

namespace Radio {

/* A script entry of the DJ's script tables. */
struct Ent {
    unsigned short m0;   /* table */
    short m2;            /* script */
    unsigned short m4;   /* id */
    short m6;
    char m8[2];
    unsigned char m10;   /* number of sound files */
    char m11[6];
    signed char m17;     /* speaker */
    char m18[2];
    int m20;             /* blank time after the script */
};

/* A script table's attributes. */
struct Tab {
    signed char pri;
    unsigned char flags;   /* bit 3: cannot be interrupted, bit 4: interrupts */
};

/* One script of a queue node. */
struct Item {
    short rec[4];   /* the script's sound files */
    Ent *ent;
    Tab *tab;
    int b;
};

struct Items {
    Item e[8];
};

/* A queue node (RadioQue.cpp). */
struct Node {
    Items items;
};

/* The stream player. */
struct CStream {
    CStream() { f_0f9778(this); }
    ~CStream() { f_0f9844(this); }
    void *m0;
    void *m4;
};

class CState {
public:
    CState();
    ~CState();
    int f_0f8808(int ch, int ch2);
    short f_0f88b0();
    int f_0f88f4();
    int f_0f8920();
    int f_0f894c();
    int f_0f8964();
    int f_0f897c(unsigned short id);
    int Has(unsigned short id)
    {
        for (int i = 0; i < m56; i++) {
            if (m64.e[i].ent->m4 == id)
                return 1;
        }
        return 0;
    }
    int f_0f89d0(int ch);
    int f_0f8a74();
    int f_0f8a98();
    int f_0f8abc();
    int f_0f8ac8();
    void f_0f8aec(Node *n, unsigned short num, int ch);
    void f_0f8b48();
    void f_0f8b78();
    int f_0f8b90();
    int f_0f8c0c();
    void f_0f8c6c();
    void f_0f8db0();
    void f_0f8dc8();
    void f_0f8df4();
    void f_0f8eac();
    void f_0f8f6c();
    void f_0f90d4();
    void f_0f910c();
    void f_0f9210();
    void f_0f9288();
    void f_0f92b8();
    void f_0f93b8();
    void f_0f9420();
    void f_0f9444();
    void f_0f9520();
    void f_0f9530();
    void f_0f9538();
    void f_0f9560();
    int f_0f959c();
    short f_0f95c8();
    int f_0f966c();

    int m0;             /* stream channel of the first player */
    int m4;             /* stream channel of the second player, -1 if none */
    int m8;             /* stream channel playing, -1 if none */
    CStream *m12;       /* the player in use */
    CStream *m16;       /* the player preparing the next file */
    CStream *m20[2];
    int m28;            /* index of the player in use */
    int m32;            /* index of the other player */
    int m36;            /* 0 idle, 1 playing */
    int m40;            /* playing step */
    int m44;            /* step saved while paused */
    int m48;            /* sound file of the script */
    int m52;            /* script of the node */
    unsigned short m56; /* number of scripts */
    int m60;            /* blank time left */
    Items m64;          /* the node's scripts */
    int m224;           /* retries */
    int m228;           /* stop after this script */
    int m232;           /* time waited for ready */
    int m236;           /* time waited for the end */
};

/* @implements 0x0f8610 us _ZN5Radio6CStateC2Ev
   WHAT IT DOES: Creates the two stream players and makes the first one current (base object
   constructor). */
/* @implements 0x0f8694 us _ZN5Radio6CStateC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CState::CState()
{
    m20[0] = new CStream;
    m20[1] = new CStream;
    m32 = 1;
    m12 = m20[0];
    m28 = 0;
    m16 = 0;
}

/* @implements 0x0f8718 us _ZN5Radio6CStateD2Ev
   WHAT IT DOES: Deletes the two stream players (base object destructor). */
/* @implements 0x0f8790 us _ZN5Radio6CStateD1Ev
   WHAT IT DOES: The same, complete object destructor. */
CState::~CState()
{
    if (m20[0]) {
        delete m20[0];
        m20[0] = 0;
    }
    if (m20[1]) {
        delete m20[1];
        m20[1] = 0;
    }
    m12 = 0;
    m16 = 0;
}

/* @implements 0x0f8808 us f_0f8808
   WHAT IT DOES: Clears the state and sets the two players' stream channels (the first must be
   channel 0, the second channel 0 or none). Returns -1 for an invalid channel. */
int CState::f_0f8808(int ch, int ch2)
{
    f_0f9560();
    if (ch < 0 || ch >= 1) {
        f_093f90("RadioState: StateManager Initialize Failed! Invalid Ch[%d]\n", ch);
        return -1;
    }
    f_0f997c(m20[0], ch, 0);
    m8 = -1;
    m0 = ch;
    if (ch2 >= 1) {
        f_093f90("RadioState: StateManager Initialize Failed! Invalid Another Ch[%d]\n", ch2);
        return -1;
    }
    if (ch2 >= 0)
        f_0f997c(m20[1], ch2, 0);
    m4 = ch2;
    m16 = 0;
    return 0;
}

/* @implements 0x0f88b0 us f_0f88b0
   WHAT IT DOES: The current script's current sound file, or -1. */
short CState::f_0f88b0()
{
    short r = -1;
    if (m64.e[m52].ent)
        r = m64.e[m52].rec[m48];
    return r;
}

/* @implements 0x0f88f4 us f_0f88f4
   WHAT IT DOES: The current script's table, or -1. */
int CState::f_0f88f4()
{
    int r = -1;
    Ent *e = m64.e[m52].ent;
    if (e)
        r = e->m0;
    return r;
}

/* @implements 0x0f8920 us f_0f8920
   WHAT IT DOES: The current script's number, or -1. */
int CState::f_0f8920()
{
    int r = -1;
    Ent *e = m64.e[m52].ent;
    if (e)
        r = e->m2;
    return r;
}

/* @implements 0x0f894c us f_0f894c
   WHAT IT DOES: The first script's id, or -1. */
int CState::f_0f894c()
{
    Ent *e = m64.e[0].ent;
    if (!e)
        return -1;
    return e->m4;
}

/* @implements 0x0f8964 us f_0f8964
   WHAT IT DOES: The first script's word at +6, or -1. */
int CState::f_0f8964()
{
    Ent *e = m64.e[0].ent;
    if (!e)
        return -1;
    return e->m6;
}

/* @draft 0x0f897c us f_0f897c
   REMAINING DIFFERENCE: retail keeps the result in t0 through the loop (set to 1 in the match
   branch's slot and back to 0 after the loop); here the inline search's result is copied
   through v0 and v1.
   WHAT IT DOES: Tells whether the node being played holds the script with the given id. */
int CState::f_0f897c(unsigned short id)
{
    int r = 0;
    if (m64.e[0].ent)
        r = Has(id);
    return r;
}

/* @implements 0x0f89d0 us f_0f89d0
   WHAT IT DOES: Tells whether a later script of the node being played is on stream channel
   ch. */
int CState::f_0f89d0(int ch)
{
    if (m8 < 0)
        return 0;
    for (int i = m52 + 1; i < m56; i++) {
        if (ch == f_10ab7c(m64.e[i].ent->m17))
            return 1;
    }
    return 0;
}

/* @implements 0x0f8a74 us f_0f8a74
   WHAT IT DOES: Tells whether a new node may be queued: nothing is playing, or the node being
   played may be interrupted. */
int CState::f_0f8a74()
{
    int r = 1;
    if (m64.e[0].ent) {
        int f = m64.e[0].tab->flags & 8;
        r = f == 0;
    }
    return r;
}

/* @implements 0x0f8a98 us f_0f8a98
   WHAT IT DOES: Tells whether the node being played does not interrupt (or nothing plays). */
int CState::f_0f8a98()
{
    int r = 1;
    if (m64.e[0].ent) {
        int f = m64.e[0].tab->flags & 0x10;
        r = f == 0;
    }
    return r;
}

/* @implements 0x0f8abc us f_0f8abc
   WHAT IT DOES: Tells whether the state machine is idle. */
int CState::f_0f8abc()
{
    return m36 == 0;
}

/* @implements 0x0f8ac8 us f_0f8ac8
   WHAT IT DOES: Tells whether the state machine is idle with no node. */
int CState::f_0f8ac8()
{
    if (m36 == 0 && m64.e[0].ent == 0)
        return 1;
    return 0;
}

/* @implements 0x0f8aec us f_0f8aec
   WHAT IT DOES: Takes a node to play: copies its scripts and sets the stream channel (the
   first player's when none is given). */
void CState::f_0f8aec(Node *n, unsigned short num, int ch)
{
    m64 = n->items;
    m56 = num;
    if (ch < 0)
        m8 = m0;
    else
        m8 = ch;
}

/* @implements 0x0f8b48 us f_0f8b48
   WHAT IT DOES: Stops the player in use and clears the state. */
void CState::f_0f8b48()
{
    f_0f9914(m12);
    f_0f9560();
}

/* @implements 0x0f8b78 us f_0f8b78
   WHAT IT DOES: Asks for a stop after the script playing. */
void CState::f_0f8b78()
{
    if (m8 >= 0)
        m228 = 1;
}

/* @implements 0x0f8b90 us f_0f8b90
   WHAT IT DOES: Pauses the stream while playing. Returns -1 if it was not paused. */
int CState::f_0f8b90()
{
    if (m36 != 1 || m40 == 12)
        return -1;
    if (f_0f9944(m12) < 0)
        return -1;
    m44 = m40;
    m40 = 12;
    f_093f90("RadioState: PauseOn Stream Ch[%d]\n", m8);
    return 0;
}

/* @implements 0x0f8c0c us f_0f8c0c
   WHAT IT DOES: Resumes a paused stream. Returns -1 if it was not resumed. */
int CState::f_0f8c0c()
{
    if (m40 == 12) {
        if (f_0f9960(m12) < 0)
            return -1;
        m40 = m44;
        f_093f90("RadioState: PauseOff Stream Ch[%d]\n", m8);
        return 0;
    }
    return -1;
}

/* @implements 0x0f8c6c us f_0f8c6c
   WHAT IT DOES: The per frame step: starts when idle with a node, else runs the playing step. */
void CState::f_0f8c6c()
{
    switch (m36) {
    case 0:
        f_0f8db0();
        break;
    case 1:
        switch (m40) {
        case 0:
            f_0f8dc8();
            break;
        case 1:
            f_0f8df4();
            break;
        case 2:
            f_0f8eac();
            break;
        case 3:
            f_0f8f6c();
            break;
        case 4:
            f_0f90d4();
            break;
        case 5:
            f_0f9210();
            break;
        case 6:
            f_0f9288();
            break;
        case 7:
            f_0f92b8();
            break;
        case 8:
            f_0f93b8();
            break;
        case 9:
            f_0f9420();
            break;
        case 10:
            f_0f9444();
            break;
        case 11:
            f_0f9520();
            break;
        case 12:
            f_0f9530();
            break;
        case 13:
            f_0f9538();
            break;
        default:
            f_0f9538();
            break;
        }
        break;
    }
}

/* @implements 0x0f8db0 us f_0f8db0
   WHAT IT DOES: Starts playing once a node has been taken. */
void CState::f_0f8db0()
{
    if (m64.e[0].ent)
        m36 = 1;
}

/* @implements 0x0f8dc8 us f_0f8dc8
   WHAT IT DOES: Step 0: makes the first player current and clears the counters. */
void CState::f_0f8dc8()
{
    m12 = m20[0];
    m16 = 0;
    m40 = 1;
    m224 = 0;
    m232 = 0;
    m236 = 0;
    m28 = 0;
    m32 = 1;
}

/* @implements 0x0f8df4 us f_0f8df4
   WHAT IT DOES: Step 1: finds the stream channel of the script's speaker and sets it on the
   player, then goes to step 3. */
void CState::f_0f8df4()
{
    int spk = m64.e[m52].ent->m17;
    int ch = f_10ab7c(spk);
    if (ch < 0) {
        f_093f90("RadioState: Invalid StreamCh:%d. Speaker:%d\n", ch, spk);
        m40 = 13;
    }
    if (f_0f9984(m12, ch) < 0) {
        f_093f90("RadioState: CheckCh Failed! SetStreamCh Failed\n");
        m40 = 13;
    }
    m8 = ch;
    m40 = 3;
}

/* @implements 0x0f8eac us f_0f8eac
   WHAT IT DOES: Step 2: the same for a later script, unless the next file is already being
   prepared; then goes to step 4. */
void CState::f_0f8eac()
{
    int spk = m64.e[m52].ent->m17;
    int ch = f_10ab7c(spk);
    if (ch < 0) {
        f_093f90("RadioState: Invalid StreamCh:%d. Speaker:%d\n", ch, spk);
        m40 = 13;
    }
    if (m16 == 0) {
        if (f_0f9984(m12, ch) < 0) {
            f_093f90("RadioState: CheckCh2 Failed! SetStreamCh Failed\n");
            m40 = 13;
        }
    }
    m8 = ch;
    m40 = 4;
}

/* @implements 0x0f8f6c us f_0f8f6c
   WHAT IT DOES: Step 3: asks the player for the script's current sound file (step 5, or step
   7 when it is already loaded), retrying up to 6 times; a script without files waits out its
   blank time (step 9) or ends (step 10). */
void CState::f_0f8f6c()
{
    int num = f_0f959c();
    m60 = m64.e[m52].ent->m20;
    if (num > 0) {
        int tbl = f_0f88f4();
        int scr = f_0f88b0();
        if (tbl >= 0 && scr >= 0) {
            int r;
            if (f_0f99b8(m12) == 1 && (r = f_0f99c0(m12, scr)) != 0) {
                if (f_0f99b0(m12, scr, r) >= 0) {
                    m40 = 7;
                    m224 = 0;
                    goto done;
                }
            } else if (f_0f98a4(m12, tbl, scr) >= 0) {
                m40 = 5;
                m224 = 0;
                goto done;
            }
            if (++m224 >= 6) {
                f_093f90("RadioState: StreamReady Failed! RetryCnt %d\n", m224);
                m40 = 10;
                m60 = 0;
            }
        } else {
            f_093f90("RadioState: GetPlayFile Failed!\n");
            m40 = 10;
        }
    } else if (num == 0) {
        if (m60 > 0) {
            m40 = 9;
            f_093f90("RadioState: LinkIndex[%d/%d] BlankCnt[%d]\n", m52, m56, m60);
        } else {
            m40 = 10;
        }
    } else {
        f_093f90("RadioState: Invalid FileNum:%d\n", num);
        m40 = 13;
    }
done:
    D_27f0a0 = 0;
}

/* @implements 0x0f90d4 us f_0f90d4
   WHAT IT DOES: Step 4: the next file, on the other player when there is a second channel. */
void CState::f_0f90d4()
{
    if (m4 >= 0)
        f_0f910c();
    else
        f_0f8f6c();
}

/* @implements 0x0f910c us f_0f910c
   WHAT IT DOES: Swaps to the other player (which has prepared the file) and checks the
   script's file, then waits for it (step 5); a script without files waits out its blank time
   or ends. */
void CState::f_0f910c()
{
    int num = f_0f959c();
    if (m4 >= 0) {
        int k = 1 - m28;
        m32 = m28;
        m12 = m20[k];
        m28 = k;
    }
    m60 = m64.e[m52].ent->m20;
    if (num > 0) {
        int tbl = f_0f88f4();
        int scr = f_0f88b0();
        if (tbl >= 0 && scr >= 0) {
            m40 = 5;
        } else {
            f_093f90("RadioState: GetPlayFile Failed!\n");
            m40 = 10;
        }
    } else if (num == 0) {
        if (m60 > 0) {
            m40 = 9;
            f_093f90("RadioState: LinkIndex[%d/%d] BlankCnt[%d]\n", m52, m56, m60);
        } else {
            m40 = 10;
        }
    } else {
        f_093f90("RadioState: Invalid FileNum:%d\n", num);
        m40 = 13;
    }
    D_27f0a0 = 0;
}

/* @implements 0x0f9210 us f_0f9210
   WHAT IT DOES: Step 5: waits for the stream to be ready (then step 6), giving up after a
   while. */
void CState::f_0f9210()
{
    D_27f0a0++;
    if (f_0f99a8(m12) == 1) {
        m40 = 6;
        return;
    }
    m232 += 16;
    if (m232 >= 10000) {
        f_093f90("RadioState: IsReady Time Up! %d\n", m232);
        m40 = 13;
    }
}

/* @implements 0x0f9288 us f_0f9288
   WHAT IT DOES: Step 6: starts the stream, then step 7. */
void CState::f_0f9288()
{
    f_0f990c(m12);
    m40 = 7;
}

/* @implements 0x0f92b8 us f_0f92b8
   WHAT IT DOES: Step 7: with a second channel, has the other player prepare the next file
   while this one plays; then step 8. */
void CState::f_0f92b8()
{
    if (m4 < 0) {
        m40 = 8;
        return;
    }
    int tbl = f_0f88f4();
    short scr = f_0f95c8();
    int ch = f_0f966c();
    if (scr >= 0 && ch >= 0) {
        m16 = m20[m32];
        if (m28 == 0)
            ch = m4;
        f_0f9984(m16, ch);
        if (f_0f98a4(m16, tbl, scr) >= 0) {
            m40 = 8;
            m224 = 0;
        } else if (++m224 >= 6) {
            f_093f90("RadioState: StreamReady Failed! RetryCnt %d\n", m224);
            m40 = 10;
            m60 = 0;
        }
    } else {
        m40 = 8;
    }
}

/* @implements 0x0f93b8 us f_0f93b8
   WHAT IT DOES: Step 8: waits for the stream to end (then step 10), giving up after a while. */
void CState::f_0f93b8()
{
    if (f_0f998c(m12) == 1) {
        m40 = 10;
        return;
    }
    m236 += 16;
    if (m236 >= 20000) {
        f_093f90("RadioState: IsEnd Time Up! %d\n", m236);
        m40 = 13;
    }
}

/* @implements 0x0f9420 us f_0f9420
   WHAT IT DOES: Step 9: waits out the blank time, then step 10. */
void CState::f_0f9420()
{
    m60 -= 16;
    if (m60 <= 0)
        m40 = 10;
}

/* @draft 0x0f9444 us f_0f9444
   REMAINING DIFFERENCE: retail computes the next script index in place in v1 and hoists it
   above the blank-time test; here it stays below the test in t0.
   WHAT IT DOES: Step 10: goes on to the script's next file (step 4), stops when asked, waits
   out the blank time (step 9), goes on to the next script (step 11), or ends the node. */
void CState::f_0f9444()
{
    Ent *e = m64.e[m52].ent;
    short k = m48;
    k = k + 1;
    short j = m52;
    if (k < e->m10) {
        m40 = 4;
        m48 = k;
    } else {
        if (m228) {
            f_0f9560();
            f_093f90("RadioState: Reserve Stop\n\n");
            return;
        }
        if (m60 > 0) {
            m40 = 9;
            return;
        }
        j++;
        if (j >= m56) {
            f_0f9560();
            f_093f90("RadioState: End\n\n");
            return;
        }
        m40 = 11;
        m52 = j;
    }
    m224 = 0;
    m232 = 0;
    m236 = 0;
}

/* @implements 0x0f9520 us f_0f9520
   WHAT IT DOES: Step 11: starts the next script at its first file (step 2). */
void CState::f_0f9520()
{
    m40 = 2;
    m48 = 0;
}

/* @implements 0x0f9530 us f_0f9530
   WHAT IT DOES: Step 12 (paused): nothing. */
void CState::f_0f9530()
{
}

/* @implements 0x0f9538 us f_0f9538
   WHAT IT DOES: Step 13 (error): clears the state. */
void CState::f_0f9538()
{
    f_0f9560();
    f_093f90("RadioState: Error: Radio State\n");
}

/* @implements 0x0f9560 us f_0f9560
   WHAT IT DOES: Clears the state: no channel, no node, idle. */
void CState::f_0f9560()
{
    m228 = 0;
    m64.e[0].ent = 0;
    m48 = 0;
    m52 = 0;
    m56 = 0;
    m60 = 0;
    m36 = 0;
    m40 = 0;
    m44 = 0;
    m224 = 0;
    m232 = 0;
    m236 = 0;
    m8 = -1;
}

/* @implements 0x0f959c us f_0f959c
   WHAT IT DOES: The number of sound files of the current script, or -1. */
int CState::f_0f959c()
{
    int r = -1;
    Ent *e = m64.e[m52].ent;
    if (e)
        r = e->m10;
    return r;
}

/* @draft 0x0f95c8 us f_0f95c8
   REMAINING DIFFERENCE: the next script's entry and its file count swap v0 and v1.
   WHAT IT DOES: The sound file after the current one: the script's next file, else the next
   script's first file; -1 if none. */
short CState::f_0f95c8()
{
    short r;
    Ent *e = m64.e[m52].ent;
    if (e) {
        short j = m52;
        short k = m48;
        k = k + 1;
        if (k < e->m10) {
            r = m64.e[j].rec[k];
        } else {
            j = j + 1;
            if (j < m56 && m64.e[j].ent->m10)
                r = m64.e[j].rec[0];
            else
                r = -1;
        }
    } else {
        r = -1;
    }
    return r;
}

/* @draft 0x0f966c us f_0f966c
   REMAINING DIFFERENCE: retail loads and steps the next script index above the file test (in
   a0, this copied to a1); here the load fills the branch-likely slot.
   WHAT IT DOES: The stream channel of the sound file after the current one; -1 if none. */
int CState::f_0f966c()
{
    int r;
    Ent *e = m64.e[m52].ent;
    if (e) {
        short k = m48;
        k = k + 1;
        if (k < e->m10) {
            r = m8;
        } else {
            short j = m52;
            j = j + 1;
            if (j < m56 && m64.e[j].ent->m10)
                r = f_10ab7c(m64.e[j].ent->m17);
            else
                r = -1;
        }
    } else {
        r = -1;
    }
    return r;
}

}
