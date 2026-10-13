/* The race voice object file (retail 0x092c74 to 0x0932c0). The race voice player
   (D_242c60) plays a voice for a race event on two voices of the race voice bank, skipping
   a repeat of the same event in the same frame; the voice set follows the console
   language. */

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

CRaceVoice D_242c60;

/* @implements 0x093204 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the voice player; at exit, destroys it. */

/* @implements 0x093280 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0932a0 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
