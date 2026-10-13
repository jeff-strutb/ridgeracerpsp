/* The menu voice object file (retail 0x092900 to 0x092c74). The menu voice player (D_242c54)
   maps a menu event to a voice in the menu voice bank and plays it; the language
   announcement takes its bank by the console language. */

int f_01c260(void);
int f_0f65a4(void);
int f_0f67c0(int bank, int set, int voice, float vol);
void f_0f6864(int bank);

extern int D_242c5c;

class CMenuVoice {
public:
    CMenuVoice();
    ~CMenuVoice();
    static CMenuVoice *f_092970();
    void f_09299c();
    void f_0929a4();
    void f_0929ac();
    int f_0929b4(int ev);
    void f_092a38();
    int f_092a58(int ev);

    int m0;
    int set;
};

/* @implements 0x092900 us _ZN10CMenuVoiceC2Ev
   WHAT IT DOES: Builds the voice player. */
CMenuVoice::CMenuVoice()
{
    f_0929a4();
}

/* @implements 0x09291c us _ZN10CMenuVoiceC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x092938 us _ZN10CMenuVoiceD2Ev
   WHAT IT DOES: Takes the voice player down. */
CMenuVoice::~CMenuVoice()
{
    f_0929ac();
}

/* @implements 0x092954 us _ZN10CMenuVoiceD1Ev
   WHAT IT DOES: The same, as the complete object. */

extern CMenuVoice D_242c54;

/* @implements 0x092970 us f_092970
   WHAT IT DOES: Opens the menu voice bank and returns the voice player. */
CMenuVoice *CMenuVoice::f_092970()
{
    D_242c5c = f_0f65a4();
    return &D_242c54;
}

/* @implements 0x09299c us f_09299c
   WHAT IT DOES: Nothing (compiled out). */
void CMenuVoice::f_09299c()
{
}

/* @implements 0x0929a4 us f_0929a4
   WHAT IT DOES: Nothing (compiled out). */
void CMenuVoice::f_0929a4()
{
}

/* @implements 0x0929ac us f_0929ac
   WHAT IT DOES: Nothing (compiled out). */
void CMenuVoice::f_0929ac()
{
}

/* @draft 0x0929b4 us f_0929b4
   WHAT IT DOES: Plays the voice for a menu event at full volume from voice set 632 (the
   language announcement picks its own set); returns the voice handle, or -1 when the event
   has no voice (18).
   Draft: retail loads the bank handle before the voice set for the play call (a load order
   tie). */
int CMenuVoice::f_0929b4(int ev)
{
    set = 632;
    m0 = 0;
    int r = -1;
    if (f_092a58(ev) != 18)
        r = f_0f67c0(D_242c5c, set, f_092a58(ev), 1.0f);
    return r;
}

/* @draft 0x092a38 us f_092a38
   WHAT IT DOES: Stops the menu voices.
   Draft: retail loads the bank handle after the prologue, in the call's delay slot; this
   source hoists it above the frame setup. */
void CMenuVoice::f_092a38()
{
    f_0f6864(D_242c5c);
}

/* @implements 0x092a58 us f_092a58
   WHAT IT DOES: Maps a menu event (0 to 34) to its voice; 8 by default. Event 34, the
   language announcement, also selects the voice set of the console language. */
int CMenuVoice::f_092a58(int ev)
{
    int v = 8;
    switch (ev) {
    case 2: v = 1; break;
    case 3: v = 2; break;
    case 4: v = 3; break;
    case 5: v = 4; break;
    case 6: v = 13; break;
    case 9: v = 15; break;
    case 11: v = 12; break;
    case 13:
    case 14:
    case 16: v = 18; break;
    case 21: v = 7; break;
    case 22: v = 9; break;
    case 23: v = 10; break;
    case 1:
    case 12:
    case 17:
    case 18:
    case 19:
    case 20:
    case 24:
    case 25: v = 8; break;
    case 7:
    case 15:
    case 26: v = 5; break;
    case 27: v = 16; break;
    case 29: v = 17; break;
    case 0:
    case 8:
    case 30:
    case 31: v = 6; break;
    case 10:
    case 32: v = 11; break;
    case 28:
    case 33: v = 14; break;
    case 34:
        set = 634;
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
        v = 2;
        break;
    }
    return v;
}

CMenuVoice D_242c54;

/* @implements 0x092bb8 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the voice player; at exit, destroys it. */

/* @implements 0x092c34 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x092c54 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
