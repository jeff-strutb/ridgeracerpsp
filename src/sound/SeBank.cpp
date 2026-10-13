/* The sound effect bank object file (retail 0x0932c0 to 0x093680): one global object that
   plays the game's eleven fixed sound effects through the sound player at D_27ee3c. Each
   effect has an enable flag; a request plays the effect's voice at the object's volume.
   The static data's startup and shutdown entries close the object file. */

extern "C" {
void *f_0f65a4(void);
int f_0f671c(void *player, int state, int voice, float volume);
int f_0f6864(void *player);
int f_0f6894(void *player);
int f_0f68d8(void *player);
int f_0f6954(void *player);
void f_0f6904(void *player, float volume);
}

class CSeBank {
public:
    CSeBank();
    ~CSeBank();
    static CSeBank *f_093330();
    static void f_09333c();
    void f_093360();
    void f_0933b8();
    int f_0933f8(int se);
    int f_093448();
    int f_093464();
    int f_093480();
    int f_09349c();
    void f_0934b8(int se);
    void f_0934c8(int se);
    void f_0934d4();
    void f_0934f8();
    void f_093518(float volume);
    float f_093538();
    int f_093540(int se);

    int m0;
    void *m4;
    unsigned char m8[11];
    float m20;
};

static CSeBank D_242c78;

/* @implements 0x0932c0 us _ZN7CSeBankC2Ev
   WHAT IT DOES: Constructs the bank by initialising it (base object constructor). */
/* @implements 0x0932dc us _ZN7CSeBankC1Ev
   WHAT IT DOES: Constructs the bank by initialising it (complete object constructor). */
CSeBank::CSeBank()
{
    f_093360();
}

/* @implements 0x0932f8 us _ZN7CSeBankD2Ev
   WHAT IT DOES: Destroys the bank by shutting it down (base object destructor). */
/* @implements 0x093314 us _ZN7CSeBankD1Ev
   WHAT IT DOES: Destroys the bank by shutting it down (complete object destructor). */
CSeBank::~CSeBank()
{
    f_0933b8();
}

/* @implements 0x093330 us f_093330
   WHAT IT DOES: Returns the one global bank. */
CSeBank *CSeBank::f_093330()
{
    return &D_242c78;
}

/* @implements 0x09333c us f_09333c
   WHAT IT DOES: Shuts the global bank down: stops its player and enables every effect. */
void CSeBank::f_09333c()
{
    f_093330()->f_0933b8();
}

/* @implements 0x093360 us f_093360
   WHAT IT DOES: Attaches the sound player, marks the bank ready, enables all eleven effects
   and sets the volume to full. */
void CSeBank::f_093360()
{
    int i;
    m4 = f_0f65a4();
    m0 = 1;
    for (i = 0; i < 11; i++)
        m8[i] = 1;
    m20 = 1.0f;
}

/* @implements 0x0933b8 us f_0933b8
   WHAT IT DOES: Stops the player and enables every effect again. */
void CSeBank::f_0933b8()
{
    int i;
    f_093464();
    for (i = 0; i < 11; i++)
        m8[i] = 1;
}

/* @implements 0x0933f8 us f_0933f8
   WHAT IT DOES: Plays an effect if it is enabled, on its voice at the bank's volume; returns
   the player's result, or -1 for a disabled effect. */
int CSeBank::f_0933f8(int se)
{
    if (m8[se]) {
        m0 = 1;
        return f_0f671c(m4, m0, f_093540(se), m20);
    }
    return -1;
}

/* @implements 0x093448 us f_093448
   WHAT IT DOES: Forwards to the player (0x0f6864). */
int CSeBank::f_093448()
{
    return f_0f6864(m4);
}

/* @implements 0x093464 us f_093464
   WHAT IT DOES: Stops the player (0x0f6894). */
int CSeBank::f_093464()
{
    return f_0f6894(m4);
}

/* @implements 0x093480 us f_093480
   WHAT IT DOES: Forwards to the player (0x0f68d8). */
int CSeBank::f_093480()
{
    return f_0f68d8(m4);
}

/* @implements 0x09349c us f_09349c
   WHAT IT DOES: Forwards to the player (0x0f6954). */
int CSeBank::f_09349c()
{
    return f_0f6954(m4);
}

/* @implements 0x0934b8 us f_0934b8
   WHAT IT DOES: Enables one effect. */
void CSeBank::f_0934b8(int se)
{
    m8[se] = 1;
}

/* @implements 0x0934c8 us f_0934c8
   WHAT IT DOES: Disables one effect. */
void CSeBank::f_0934c8(int se)
{
    m8[se] = 0;
}

/* @implements 0x0934d4 us f_0934d4
   WHAT IT DOES: Enables every effect. */
void CSeBank::f_0934d4()
{
    int i;
    for (i = 0; i < 11; i++)
        m8[i] = 1;
}

/* @implements 0x0934f8 us f_0934f8
   WHAT IT DOES: Disables every effect. */
void CSeBank::f_0934f8()
{
    int i;
    for (i = 0; i < 11; i++)
        m8[i] = 0;
}

/* @implements 0x093518 us f_093518
   WHAT IT DOES: Sets the bank's volume and passes it to the player. */
void CSeBank::f_093518(float volume)
{
    m20 = volume;
    f_0f6904(m4, volume);
}

/* @implements 0x093538 us f_093538
   WHAT IT DOES: Returns the bank's volume. */
float CSeBank::f_093538()
{
    return m20;
}

/* @implements 0x093540 us f_093540
   WHAT IT DOES: Maps an effect number to the voice that plays it; unknown effects use
   voice 8. */
int CSeBank::f_093540(int se)
{
    int v;
    switch (se) {
    case 0: v = 3; break;
    case 1: v = 4; break;
    case 2: v = 0; break;
    case 3: v = 6; break;
    case 4: v = 10; break;
    case 5: v = 7; break;
    case 6: v = 8; break;
    case 7: v = 5; break;
    case 8: v = 9; break;
    case 9: v = 2; break;
    case 10: v = 1; break;
    default: v = 8; break;
    }
    return v;
}

/* @implements 0x0935c4 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global bank at startup and destroys it at shutdown. */
/* @implements 0x093640 us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x093660 us _GLOBAL__D_
   WHAT IT DOES: Shutdown entry of the object file's static data. */
