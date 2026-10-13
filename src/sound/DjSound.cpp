/* The DJ sound bank object file (retail 0x09232c to 0x092900). The menu DJ (D_242c4c) holds
   three sound bank slots (title, voice, music); loading picks the console language's
   sound header and DJ data from the archive manager and opens one bank per slot, freeing
   closes them again. The first function is the tail of the event detector's file. */

void f_00d354(void *log, int level, const char *fmt, ...);
int f_01c260(void);
void f_01c458(void *p, void *a, void *b, int c, short *slot);
void f_01c578(void *p);

struct CPackage {
    void *f_002acc(const char *name);
};
CPackage *f_005a38(void *mgr, const char *name);
void f_005d4c(void *mgr, const char *name);

extern char D_1dd6b0[];
extern char D_23bb4c[];
extern char D_245178[];

/* The event detector (its file ends here). */
class CDjDetect {
public:
    void f_0902bc(int n);
    void f_09232c();
};

/* @implements 0x09232c us f_09232c
   WHAT IT DOES: Sends the detector request 78. */
void CDjDetect::f_09232c()
{
    f_0902bc(78);
}

class CDjSound {
public:
    CDjSound();
    ~CDjSound();
    void f_092398();
    void f_092488();
    void f_0924a4();
    void f_0924c0();
    void f_0927f0();

    short slot[3];
};

/* @implements 0x092348 us _ZN8CDjSoundC2Ev
   WHAT IT DOES: Builds the menu DJ with no banks open. */
CDjSound::CDjSound()
{
    for (int i = 0; i < 3; i++)
        slot[i] = -1;
}

/* @implements 0x092368 us _ZN8CDjSoundC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x092388 us _ZN8CDjSoundD2Ev
   WHAT IT DOES: Nothing to release. */
CDjSound::~CDjSound()
{
}

/* @implements 0x092390 us _ZN8CDjSoundD1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x092398 us f_092398
   WHAT IT DOES: Releases the language's DJ data from the archive manager. */
void CDjSound::f_092398()
{
    if (f_01c260() == 1)
        f_005d4c(D_1dd6b0, "MenuDj_En_Free");
    else if (f_01c260() == 2)
        f_005d4c(D_1dd6b0, "MenuDj_Fr_Free");
    else if (f_01c260() == 3)
        f_005d4c(D_1dd6b0, "MenuDj_Sp_Free");
    else if (f_01c260() == 4)
        f_005d4c(D_1dd6b0, "MenuDj_Ge_Free");
    else if (f_01c260() == 5)
        f_005d4c(D_1dd6b0, "MenuDj_It_Free");
    else if (f_01c260() == 6)
        f_005d4c(D_1dd6b0, "MenuDj_En_Free");
    else
        f_005d4c(D_1dd6b0, "MenuDj_En_Free");
    f_00d354(D_245178, 0x800000, "MenuDj_Free Data Loaded!!\n");
}

/* @implements 0x092488 us f_092488
   WHAT IT DOES: Loads the menu DJ's banks. */
void CDjSound::f_092488()
{
    f_0924c0();
}

/* @implements 0x0924a4 us f_0924a4
   WHAT IT DOES: Frees the menu DJ's banks. */
void CDjSound::f_0924a4()
{
    f_0927f0();
}

/* Opens the three banks from a sound header and a DJ data archive. */
#define OPEN_BANKS(hd, dj)                                                                    \
    do {                                                                                      \
        void *a = f_005a38(D_1dd6b0, hd)->f_002acc("TITLE");                                  \
        f_01c458(D_23bb4c, a, f_005a38(D_1dd6b0, dj)->f_002acc("TITLE"), 0, &slot[0]);        \
        a = f_005a38(D_1dd6b0, hd)->f_002acc("S_VOICE");                                      \
        f_01c458(D_23bb4c, a, f_005a38(D_1dd6b0, dj)->f_002acc("S_VOICE"), 0, &slot[1]);      \
        a = f_005a38(D_1dd6b0, hd)->f_002acc("S_BGM");                                        \
        f_01c458(D_23bb4c, a, f_005a38(D_1dd6b0, dj)->f_002acc("S_BGM"), 0, &slot[2]);        \
    } while (0)

/* @implements 0x0924c0 us f_0924c0
   WHAT IT DOES: Opens the title, voice and music banks for the console language (English by
   default). */
void CDjSound::f_0924c0()
{
    if (f_01c260() == 1)
        OPEN_BANKS("SoundCommonHD_En", "MenuDj_En_Free");
    else if (f_01c260() == 2)
        OPEN_BANKS("SoundCommonHD_Fr", "MenuDj_Fr_Free");
    else if (f_01c260() == 3)
        OPEN_BANKS("SoundCommonHD_Sp", "MenuDj_Sp_Free");
    else if (f_01c260() == 4)
        OPEN_BANKS("SoundCommonHD_Ge", "MenuDj_Ge_Free");
    else if (f_01c260() == 5)
        OPEN_BANKS("SoundCommonHD_It", "MenuDj_It_Free");
    else if (f_01c260() == 6)
        OPEN_BANKS("SoundCommonHD_En", "MenuDj_En_Free");
    else
        OPEN_BANKS("SoundCommonHD_En", "MenuDj_En_Free");
}

/* @implements 0x0927f0 us f_0927f0
   WHAT IT DOES: Closes the three banks. */
void CDjSound::f_0927f0()
{
    for (int i = 0; i < 3; i++) {
        f_01c578(D_23bb4c);
        slot[i] = -1;
    }
}

CDjSound D_242c4c;

/* @implements 0x09284c us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the menu DJ; at exit, destroys it. */

/* @implements 0x0928c0 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0928e0 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
