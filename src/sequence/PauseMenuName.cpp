/* The pause menu name object file (retail 0x093680 to 0x093814): picks the pause menu's
   resource name for the current language, using the wireless battle variant when the game
   runs in wireless mode (mode 3). */

extern "C" int f_01c260(void);

struct CGameMode {
    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
};

extern CGameMode *D_2407fc;

/* @implements 0x093680 us f_093680
   WHAT IT DOES: Returns the pause menu resource name for the current language (1 English,
   2 French, 3 Spanish, 4 German, 5 Italian, 6 American English; English otherwise), the
   wireless variant in wireless mode. */
const char *f_093680(void)
{
    const char *name;
    if (f_01c260() == 1)
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuEN" : "PauseMenuEN";
    else if (f_01c260() == 2)
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuFR" : "PauseMenuFR";
    else if (f_01c260() == 3)
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuSP" : "PauseMenuSP";
    else if (f_01c260() == 4)
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuGE" : "PauseMenuGE";
    else if (f_01c260() == 5)
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuIT" : "PauseMenuIT";
    else if (f_01c260() == 6)
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuAM" : "PauseMenuAM";
    else
        name = D_2407fc->m16 == 3 ? "WirelessPauseMenuEN" : "PauseMenuEN";
    return name;
}

/* @implements 0x0937f0 us f_0937f0
   WHAT IT DOES: Tells whether the language is American English (6). */
int f_0937f0(void)
{
    return f_01c260() == 6;
}
