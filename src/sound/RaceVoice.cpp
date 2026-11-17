/* The race voice object file (retail 0x092c74 to 0x0932c0). The race voice player
   (D_242c60) plays a voice for a race event on two voices of the race voice bank, skipping
   a repeat of the same event in the same frame; the voice set follows the console
   language. */

int f_01c260(void);
int f_0f65a4(void);
int f_0f67c0(int bank, int set, int voice, float vol);
void f_0f6864(int bank, int h);
void f_0f6894(int bank, int h);
int f_0f6954(int bank, int h);

extern int D_242c74;

struct CSystemFlags {
    int m0;
    int frame;
};
extern CSystemFlags *D_1d88a0;

class CRaceVoice {
public:
    CRaceVoice();
    ~CRaceVoice();
    static CRaceVoice *f_092ce4();
    void f_092d10();
    void f_092d18();
    void f_092d38();
    void f_092d40(int ev);
    void f_092e18();
    void f_092e94(int h);
    void f_092eb4();
    int f_092ec0(int ev);

    int set;
    int last;
    int voice[2];
    int frame;
};

/* @implements 0x092c74 us _ZN10CRaceVoiceC2Ev
   WHAT IT DOES: Builds the voice player with nothing playing. */
CRaceVoice::CRaceVoice()
{
    f_092d18();
}

/* @implements 0x092c90 us _ZN10CRaceVoiceC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x092cac us _ZN10CRaceVoiceD2Ev
   WHAT IT DOES: Takes the voice player down. */
CRaceVoice::~CRaceVoice()
{
    f_092d38();
}

/* @implements 0x092cc8 us _ZN10CRaceVoiceD1Ev
   WHAT IT DOES: The same, as the complete object. */

extern CRaceVoice D_242c60;

/* @implements 0x092ce4 us f_092ce4
   WHAT IT DOES: Opens the race voice bank and returns the voice player. */
CRaceVoice *CRaceVoice::f_092ce4()
{
    D_242c74 = f_0f65a4();
    return &D_242c60;
}

/* @implements 0x092d10 us f_092d10
   WHAT IT DOES: Nothing (compiled out). */
void CRaceVoice::f_092d10()
{
}

/* @implements 0x092d18 us f_092d18
   WHAT IT DOES: Clears the state: no last event (81), no voices, no frame. */
void CRaceVoice::f_092d18()
{
    last = 81;
    voice[1] = voice[0] = -1;
    frame = -1000;
}

/* @implements 0x092d38 us f_092d38
   WHAT IT DOES: Nothing (compiled out). */
void CRaceVoice::f_092d38()
{
}

/* @draft 0x092d40 us f_092d40
   WHAT IT DOES: Plays the voice for a race event, unless the same event was already played
   this frame: stops what is playing, picks the voice and starts it on both voices.
   Draft: retail loads the system flags pointer before storing the event (this source stores
   first), and jumps from the repeat test's failure back to the body. */
void CRaceVoice::f_092d40(int ev)
{
    if (last == ev && D_1d88a0->frame == frame)
        return;
    f_092e18();
    float vol = 1.0f;
    int v = f_092ec0(ev);
    voice[0] = f_0f67c0(D_242c74, set, v, vol);
    voice[1] = f_0f67c0(D_242c74, set, v, vol);
    last = ev;
    frame = D_1d88a0->frame;
}

/* @implements 0x092e18 us f_092e18
   WHAT IT DOES: Stops both voices where they are still playing, and forgets the last event. */
void CRaceVoice::f_092e18()
{
    for (int i = 0; i < 2; i++)
        if (!f_0f6954(D_242c74, voice[i]))
            f_0f6864(D_242c74, voice[i]);
    last = 81;
}

/* @draft 0x092e94 us f_092e94
   WHAT IT DOES: Passes a voice handle to the bank.
   Draft: retail loads the bank after the prologue, in the call's delay slot (as in the menu
   voice player's stop). */
void CRaceVoice::f_092e94(int h)
{
    f_0f6894(D_242c74, h);
}

/* @implements 0x092eb4 us f_092eb4
   WHAT IT DOES: Forgets the last event. */
void CRaceVoice::f_092eb4()
{
    last = 81;
}

/* @implements 0x092ec0 us f_092ec0
   WHAT IT DOES: Picks the voice for a race event. Sets the voice set from the console
   language (633 English, 557 French, 630 Spanish, 583 German, 605 Italian; English for
   American English and anything else) and returns the event's voice number. Events 0 and 1
   choose at random from the frame count: event 0 one of voices 0 to 3, event 1 voice 0 or
   1 from the second voice set (634, 558, 631, 584, 606). Unlisted events give voice 4. */
int CRaceVoice::f_092ec0(int ev)
{
    int r = 0;
    int rnd = D_1d88a0->frame * 0x19660d + 0x3c6ef35f;

    set = 633;
    if (rnd < 0)
        rnd = -rnd;
    if (f_01c260() == 1)
        set = 633;
    else if (f_01c260() == 2)
        set = 557;
    else if (f_01c260() == 3)
        set = 630;
    else if (f_01c260() == 4)
        set = 583;
    else if (f_01c260() == 5)
        set = 605;
    else if (f_01c260() == 6)
        set = 633;
    else
        set = 633;

    switch (ev) {
    case 0:
        if (rnd % 4 == 0)
            r = 0;
        else if (rnd % 4 == 1)
            r = 1;
        else if (rnd % 4 == 2)
            r = 2;
        else if (rnd % 4 == 3)
            r = 3;
        break;
    case 1:
        if (f_01c260() == 1)
            set = 634;
        else if (f_01c260() == 2)
            set = 558;
        else if (f_01c260() == 3)
            set = 631;
        else if (f_01c260() == 4)
            set = 584;
        else if (f_01c260() == 5)
            set = 606;
        else if (f_01c260() == 6)
            set = 634;
        else
            set = 634;
        if (rnd % 2 == 0)
            r = 0;
        else if (rnd % 2 == 1)
            r = 1;
        break;
    case 3: r = 6; break;
    case 4: r = 5; break;
    case 5: r = 7; break;
    case 6: r = 8; break;
    case 7: r = 9; break;
    case 8: r = 10; break;
    case 9: case 10: r = 1; break;
    case 11: r = 11; break;
    case 12: r = 12; break;
    case 13: case 14: r = 1; break;
    case 15: r = 13; break;
    case 16: r = 14; break;
    case 17: case 18: case 19: r = 1; break;
    case 20: r = 15; break;
    case 21: r = 16; break;
    case 22: r = 17; break;
    case 23: r = 18; break;
    case 24: r = 19; break;
    default: r = 4; break;
    case 49: case 58: r = 28; break;
    case 50: case 59: r = 20; break;
    case 51: case 60: r = 26; break;
    case 52: case 61: r = 21; break;
    case 53: case 62: r = 24; break;
    case 54: case 63: r = 22; break;
    case 55: case 64: r = 23; break;
    case 56: case 65: r = 27; break;
    case 57: case 66: r = 25; break;
    case 67: r = 29; break;
    case 68: r = 30; break;
    case 69: r = 31; break;
    case 70: r = 32; break;
    case 71: r = 46; break;
    case 72: r = 47; break;
    case 73: r = 48; break;
    case 74: r = 49; break;
    case 75: r = 50; break;
    case 76: r = 51; break;
    case 77: r = 52; break;
    case 78: r = 53; break;
    case 79: r = 54; break;
    case 80: r = 17; break;
    }
    return r;
}

CRaceVoice D_242c60;

/* @implements 0x093204 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the voice player; at exit, destroys it. */

/* @implements 0x093280 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0932a0 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
