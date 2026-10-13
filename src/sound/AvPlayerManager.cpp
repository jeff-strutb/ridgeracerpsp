/* The AV player manager object file (retail 0x09816c to 0x09923c): the music player of the
   AV player screen. It plays the tracks of six discs (disc 6 is the DJ disc, whose 30
   entries come from all other discs) with optional shuffle and repeat, follows the pad
   commands (previous and next track, previous and next disc, shuffle, repeat), and keys
   the DJ voice's start and next-track lines in the current language's sound bank on two
   voices. A state machine steps the DJ line, the track's fade in and out and the music
   playback of the music player at D_242cb0. */

extern "C" {
void f_093f90(const char *fmt, ...);
void f_0fa28c(void *voice);
int f_0f6b90(void);
int f_01c260(void);
int f_077b0c(void *info, int disc, int track);
}

/* One sound voice (36 bytes); its methods are in the voice object file at 0x0fa28c. */
struct CVoice {
    CVoice() { f_0fa28c(this); }
    ~CVoice() {}
    int f_0fa2e8(unsigned short bank, unsigned short tone);
    int f_0fa458();
    int f_0fa6d4();
    int m[9];
};

/* The music player (0x094xxx). */
struct CMusicPlayer {
    int f_094d6c(int time);
    void f_094db0();
    int f_094fb0();
    int f_095404();
    int f_0964c4(int track);
};
extern CMusicPlayer D_242cb0;

/* The pad, as far as its analog stick is concerned. */
struct CCustomController {
    int f_04311c();
    int f_04316c();
};
extern CCustomController D_1d8910;
extern int D_245194;

/* A track's information, filled by 0x077b0c. */
struct TrackInfo {
    int m[120];
};

class CAvPlayerManager {
public:
    CAvPlayerManager();
    int f_0981fc(int disc);
    void f_098290();
    void f_0982c4();
    void f_0983bc();
    void f_0983ec();
    void f_09840c();
    void f_098438();
    void f_098478();
    void f_0984a4();
    void f_0984e4();
    void f_09850c();
    void f_098534();
    void f_0985bc();
    void f_0985f0();
    void f_098674();
    void f_0986d8();
    int f_098824(int cmd);
    void f_098920();
    void f_0989cc();
    void f_098a78();
    void f_098a80();
    void f_098b2c();
    void f_098bd4();
    void f_098c1c();
    int f_098c3c();
    void f_098c74();
    int f_098c98();
    int f_098cbc();
    int f_098db0();
    int f_098ea4();
    int f_098ed8();
    int f_098f4c();
    void f_098ff0();
    int f_0990c8(int disc);
    void f_0990d8();
    int f_099148();

    unsigned char m0;
    unsigned char m1;
    unsigned char m2;
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40[6];
    int m64[30];
    CVoice m184;
    CVoice m220;
    int m256;
};

static CAvPlayerManager D_245074;

/* @implements 0x09816c us _ZN16CAvPlayerManagerC2Ev
   WHAT IT DOES: Constructs the two voices and initialises the player (base object
   constructor). */
/* @implements 0x0981b4 us _ZN16CAvPlayerManagerC1Ev
   WHAT IT DOES: Same as the base object constructor (complete object constructor). */
CAvPlayerManager::CAvPlayerManager()
{
    f_0990d8();
}

/* @implements 0x0981fc us f_0981fc
   WHAT IT DOES: Starts the player on a disc (1 to 6): initialises it and selects the disc;
   the DJ disc (6) starts in the DJ list at no track with the list shuffled. Returns -1 for
   an invalid disc. */
int CAvPlayerManager::f_0981fc(int disc)
{
    if (f_0990c8(disc) < 0) {
        f_093f90("CAvPlayerManager: Init Failed! Invalid Disc[%d]\n", disc);
        return -1;
    }
    f_093f90("CAvPlayerManager: Init Disc[%d]\n", disc);
    f_0990d8();
    m4 = disc;
    if (disc == 6) {
        m2 = 1;
        m8 = -1;
        f_098ff0();
    }
    return 0;
}

/* @implements 0x098290 us f_098290
   WHAT IT DOES: Stops the music and both voices and initialises the player. */
void CAvPlayerManager::f_098290()
{
    f_098c74();
    f_098ea4();
    f_0990d8();
}

/* @implements 0x0982c4 us f_0982c4
   WHAT IT DOES: The frame step: handles the pad, then runs the current state's step. */
void CAvPlayerManager::f_0982c4()
{
    f_0986d8();
    switch (m256) {
    case 0: f_0983ec(); break;
    case 1: f_09840c(); break;
    case 2: f_098438(); break;
    case 3: f_098478(); break;
    case 4: f_0984a4(); break;
    case 5: f_09850c(); break;
    case 6: f_0984e4(); break;
    case 7: f_098534(); break;
    case 8: f_0985bc(); break;
    case 9: f_0985f0(); break;
    case 10: f_098674(); break;
    }
}

/* @implements 0x0983bc us f_0983bc
   WHAT IT DOES: Requests the start and looks up the current track. */
void CAvPlayerManager::f_0983bc()
{
    m16 = 1;
    m12 = f_098ed8();
}

/* @implements 0x0983ec us f_0983ec
   WHAT IT DOES: State 0: on a start request, goes to state 1 (DJ start line). */
void CAvPlayerManager::f_0983ec()
{
    if (m16 == 1) {
        m256 = 1;
        m16 = 0;
    }
}

/* @implements 0x09840c us f_09840c
   WHAT IT DOES: State 1: keys the DJ start line on and waits for it (state 2). */
void CAvPlayerManager::f_09840c()
{
    f_098cbc();
    m256 = 2;
}

/* @implements 0x098438 us f_098438
   WHAT IT DOES: State 2: when the DJ line has finished, goes to the fade-in wait (state 6). */
void CAvPlayerManager::f_098438()
{
    if (m184.f_0fa6d4() == 1) {
        m256 = 6;
        m32 = 0;
    }
}

/* @implements 0x098478 us f_098478
   WHAT IT DOES: State 3: keys the DJ next-track line on and waits for it (state 4). */
void CAvPlayerManager::f_098478()
{
    f_098db0();
    m256 = 4;
}

/* @implements 0x0984a4 us f_0984a4
   WHAT IT DOES: State 4: when the DJ line has finished, goes to the fade-in wait (state 6). */
void CAvPlayerManager::f_0984a4()
{
    if (m184.f_0fa6d4() == 1) {
        m256 = 6;
        m32 = 0;
    }
}

/* @implements 0x0984e4 us f_0984e4
   WHAT IT DOES: State 6: waits 500 time units, then goes to the track start (state 8). */
void CAvPlayerManager::f_0984e4()
{
    if (m32 >= 500) {
        m256 = 8;
        m32 = 0;
    } else {
        m32 += 16;
    }
}

/* @implements 0x09850c us f_09850c
   WHAT IT DOES: State 5: waits 500 time units, then goes to the DJ next-track line
   (state 3). */
void CAvPlayerManager::f_09850c()
{
    if (m32 >= 500) {
        m256 = 3;
        m32 = 0;
    } else {
        m32 += 16;
    }
}

/* @implements 0x098534 us f_098534
   WHAT IT DOES: State 7: after a pad command, waits at least 500 time units and for the
   music to stop, then goes to the DJ next-track line (state 3) after a track change or
   straight to the track start (state 8) otherwise. */
void CAvPlayerManager::f_098534()
{
    if (m24 >= 500 && D_242cb0.f_094fb0() == 1) {
        switch (m20) {
        case 1:
        case 3:
        case 4:
            m256 = 3;
            break;
        default:
            m256 = 8;
            break;
        }
        return;
    }
    m24 += 16;
}

/* @implements 0x0985bc us f_0985bc
   WHAT IT DOES: State 8: starts the current track and goes to the playing state (9). */
void CAvPlayerManager::f_0985bc()
{
    m28 = 0;
    if (f_098c3c() >= 0)
        m256 = 9;
}

/* @implements 0x0985f0 us f_0985f0
   WHAT IT DOES: State 9: counts the play time; while the track plays with at most 4000
   time units left, fades it out and goes to the end wait (state 10). */
void CAvPlayerManager::f_0985f0()
{
    int left = D_242cb0.f_095404();
    m28 += 16;
    if (D_242cb0.f_094fb0() == 0 && left > 0 && left <= 4000) {
        f_098c98();
        m256 = 10;
    }
}

/* @implements 0x098674 us f_098674
   WHAT IT DOES: State 10: when the music has stopped, repeats the track (state 8) or moves
   to the next track and its wait (state 5). */
void CAvPlayerManager::f_098674()
{
    if (D_242cb0.f_094fb0() == 1) {
        m28 = 0;
        m32 = 0;
        if (m1) {
            m256 = 8;
        } else {
            f_0989cc();
            m256 = 5;
        }
    }
}

/* @implements 0x0986d8 us f_0986d8
   WHAT IT DOES: Turns the pad's buttons and stick into commands: previous and next disc,
   previous and next track (in the first 2000 time units a previous goes to the track
   before, later it restarts the track), shuffle and repeat. */
void CAvPlayerManager::f_0986d8()
{
    int pad = D_245194;
    int x = D_1d8910.f_04311c();
    int y = D_1d8910.f_04316c();
    if ((pad & 0x80) || x < 0)
        f_098824(3);
    if ((pad & 0x20) || x > 0)
        f_098824(4);
    if ((pad & 0x40) || y < 0)
        f_098824(1);
    if ((pad & 0x10) || y > 0) {
        if (m28 >= 2000)
            f_098824(2);
        else
            f_098824(0);
    }
    if (pad & 0x1000)
        f_098824(5);
    if (pad & 0x8000)
        f_098824(6);
}

/* @draft 0x098824 us f_098824
   WHAT IT DOES: Runs a pad command (0 to 6). A track or disc command also stops the music
   and voices, remembers the command and goes to the command wait (state 7). Returns -1 for
   an unknown command. */
int CAvPlayerManager::f_098824(int cmd)
{
    switch (cmd) {
    case 0: f_098920(); break;
    case 1: f_0989cc(); break;
    case 2: f_098a78(); break;
    case 3: f_098b2c(); break;
    case 4: f_098a80(); break;
    case 5: f_098bd4(); break;
    case 6: f_098c1c(); break;
    default: return -1;
    }
    if (cmd != 5 && cmd != 6) {
        m24 = 0;
        m32 = 0;
        m28 = 0;
        f_098c74();
        f_098ea4();
        m256 = 7;
        m20 = cmd;
    }
    return 0;
}

/* @implements 0x098920 us f_098920
   WHAT IT DOES: Goes to the previous track (in the DJ list, the shuffled order or the
   disc), wrapping around, and looks it up. */
void CAvPlayerManager::f_098920()
{
    if (m2 == 1) {
        m36--;
        if (m36 < 0)
            m36 = 29;
        m8 = -1;
    } else if (m0 == 1) {
        m36--;
        if (m36 < 0)
            m36 = 5;
        m8 = m40[m36];
    } else {
        if (m8 == 0)
            m8 = 5;
        else
            m8--;
    }
    m12 = f_098ed8();
}

/* @implements 0x0989cc us f_0989cc
   WHAT IT DOES: Goes to the next track (in the DJ list, the shuffled order or the disc),
   wrapping around, and looks it up. */
void CAvPlayerManager::f_0989cc()
{
    if (m2 == 1) {
        m36++;
        if (m36 >= 30)
            m36 = 0;
        m8 = -1;
    } else if (m0 == 1) {
        m36++;
        if (m36 >= 6)
            m36 = 0;
        m8 = m40[m36];
    } else {
        if (m8 == 5)
            m8 = 0;
        else
            m8++;
    }
    m12 = f_098ed8();
}

/* @implements 0x098a78 us f_098a78
   WHAT IT DOES: Nothing (the restart command needs no change). */
void CAvPlayerManager::f_098a78()
{
}

/* @implements 0x098a80 us f_098a80
   WHAT IT DOES: Goes to the next disc (after 5 the DJ disc, after it disc 1) at its first
   track, reshuffles when shuffle is on, and looks the track up. */
void CAvPlayerManager::f_098a80()
{
    m2 = 0;
    m8 = 0;
    m36 = 0;
    if (m4 == 6) {
        m4 = 1;
    } else if (m4 == 5) {
        m4 = 6;
        m2 = 1;
        m8 = -1;
        f_098ff0();
    } else {
        m4++;
    }
    if (m0 == 1 && m2 == 0)
        f_098f4c();
    m12 = f_098ed8();
}

/* @implements 0x098b2c us f_098b2c
   WHAT IT DOES: Goes to the previous disc (before 1 the DJ disc, before it disc 5) at its
   first track, reshuffles when shuffle is on, and looks the track up. */
void CAvPlayerManager::f_098b2c()
{
    m2 = 0;
    m8 = 0;
    m36 = 0;
    if (m4 == 6) {
        m4 = 5;
    } else if (m4 == 1) {
        m4 = 6;
        m2 = 1;
        m8 = -1;
        f_098ff0();
    } else {
        m4--;
    }
    if (m0 == 1 && m2 == 0)
        f_098f4c();
    m12 = f_098ed8();
}

/* @implements 0x098bd4 us f_098bd4
   WHAT IT DOES: Toggles shuffle; turning it on shuffles the disc's tracks (not on the DJ
   disc). */
void CAvPlayerManager::f_098bd4()
{
    if (m0 == 1) {
        m0 = 0;
        m36 = 0;
    } else {
        m0 = 1;
        if (m2 == 0)
            f_098f4c();
    }
}

/* @implements 0x098c1c us f_098c1c
   WHAT IT DOES: Toggles repeat. */
void CAvPlayerManager::f_098c1c()
{
    if (m1 == 1)
        m1 = 0;
    else
        m1 = 1;
}

/* @implements 0x098c3c us f_098c3c
   WHAT IT DOES: Looks up the current track and starts it on the music player. */
int CAvPlayerManager::f_098c3c()
{
    m12 = f_098ed8();
    return D_242cb0.f_0964c4(m12);
}

/* @implements 0x098c74 us f_098c74
   WHAT IT DOES: Clears the play time and stops the music. */
void CAvPlayerManager::f_098c74()
{
    m28 = 0;
    D_242cb0.f_094db0();
}

/* @implements 0x098c98 us f_098c98
   WHAT IT DOES: Fades the music out over 4000 time units. */
int CAvPlayerManager::f_098c98()
{
    return D_242cb0.f_094d6c(4000);
}

/* @implements 0x098cbc us f_098cbc
   WHAT IT DOES: Keys one of four random DJ start lines (tones 6, 5, 4, 3) of the
   language's bank on both voices; logs and returns -1 for an invalid bank or tone. */
int CAvPlayerManager::f_098cbc()
{
    int bank = f_099148();
    int tone = -1;
    int r = f_0f6b90() % 4;
    switch (r) {
    case 0: tone = 6; break;
    case 1: tone = 5; break;
    case 2: tone = 4; break;
    case 3: tone = 3; break;
    }
    if (bank < 0) {
        f_093f90("CAvPlayerManager: KeyOnStartDj Failed! Invalid BankId[%d]\n", bank);
        return -1;
    }
    if (tone < 0) {
        f_093f90("CAvPlayerManager: KeyOnStartDj Failed! Invalid ToneNo[%d]\n", tone);
        return -1;
    }
    m220.f_0fa2e8(bank, tone);
    return m184.f_0fa2e8(bank, tone);
}

/* @implements 0x098db0 us f_098db0
   WHAT IT DOES: Keys one of four random DJ next-track lines (tones 2, 1, 0, 7) of the
   language's bank on both voices; logs and returns -1 for an invalid bank or tone. */
int CAvPlayerManager::f_098db0()
{
    int bank = f_099148();
    int tone = -1;
    int r = f_0f6b90() % 4;
    switch (r) {
    case 0: tone = 2; break;
    case 1: tone = 1; break;
    case 2: tone = 0; break;
    case 3: tone = 7; break;
    }
    if (bank < 0) {
        f_093f90("CAvPlayerManager: KeyOnNextDj Failed! Invalid BankId[%d]\n", bank);
        return -1;
    }
    if (tone < 0) {
        f_093f90("CAvPlayerManager: KeyOnNextDj Failed! Invalid ToneNo[%d]\n", tone);
        return -1;
    }
    m220.f_0fa2e8(bank, tone);
    return m184.f_0fa2e8(bank, tone);
}

/* @implements 0x098ea4 us f_098ea4
   WHAT IT DOES: Stops both voices. */
int CAvPlayerManager::f_098ea4()
{
    m220.f_0fa458();
    return m184.f_0fa458();
}

/* @draft 0x098ed8 us f_098ed8
   WHAT IT DOES: Returns the current track's number: the DJ list entry, or the disc's track
   (through the shuffled order when shuffle is on) looked up by disc and track. */
int CAvPlayerManager::f_098ed8()
{
    TrackInfo info;
    if (m2 == 1)
        return m64[m36];
    if (m0 == 1)
        m8 = m40[m36];
    return f_077b0c(&info, m4, m8 + 1);
}

/* @draft 0x098f4c us f_098f4c
   WHAT IT DOES: Shuffles the disc's six tracks into the shuffled order. */
int CAvPlayerManager::f_098f4c()
{
    int a[6];
    int i, n;
    n = 0;
    for (i = 0; i < 6; i++)
        a[i] = n++;
    for (n = 6; n > 0;) {
        int r = f_0f6b90() % n;
        n--;
        m40[n] = a[r];
        a[r] = a[n];
        a[n] = -1;
    }
    return 0;
}

/* @draft 0x098ff0 us f_098ff0
   WHAT IT DOES: Builds the DJ list: the six tracks of discs 1 to 5, shuffled. */
void CAvPlayerManager::f_098ff0()
{
    TrackInfo info;
    int a[30];
    int disc, track, n;
    n = 0;
    for (disc = 1; disc < 6; disc++)
        for (track = 0; track < 6;) {
            track++;
            a[n++] = f_077b0c(&info, disc, track);
        }
    for (n = 30; n > 0;) {
        int r = f_0f6b90() % n;
        n--;
        m64[n] = a[r];
        a[r] = a[n];
        a[n] = -1;
    }
}

/* @implements 0x0990c8 us f_0990c8
   WHAT IT DOES: Returns 0 for a valid disc (1 to 6), else -1. */
int CAvPlayerManager::f_0990c8(int disc)
{
    return (disc >= 1 && disc <= 6) - 1;
}

/* @implements 0x0990d8 us f_0990d8
   WHAT IT DOES: Initialises the player: disc 1, no command, shuffle, repeat and DJ list
   off, every counter, order and list entry zero, state 0. */
void CAvPlayerManager::f_0990d8()
{
    int i;
    m4 = 1;
    m20 = -1;
    m0 = 0;
    m1 = 0;
    m2 = 0;
    m8 = 0;
    m12 = 0;
    m16 = 0;
    m24 = 0;
    m28 = 0;
    m32 = 0;
    m36 = 0;
    for (i = 0; i < 6; i++)
        m40[i] = 0;
    for (i = 0; i < 30; i++)
        m64[i] = 0;
    m256 = 0;
}

/* @implements 0x099148 us f_099148
   WHAT IT DOES: Returns the DJ voice's sound bank for the current language (-1 for an
   unknown language). */
int CAvPlayerManager::f_099148()
{
    int bank;
    switch (f_01c260()) {
    case 0:
    case 1:
    case 6:
        bank = 607;
        break;
    case 2: bank = 556; break;
    case 3: bank = 629; break;
    case 4: bank = 582; break;
    case 5: bank = 604; break;
    default: bank = -1; break;
    }
    return bank;
}

/* @implements 0x0991b8 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global AV player manager at startup. */
/* @implements 0x0991fc us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x09921c us _GLOBAL__D_
   WHAT IT DOES: Shutdown entry of the object file's static data. */
