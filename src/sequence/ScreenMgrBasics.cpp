/* The first two functions of the screen manager's object file (retail 0x017bd4 to 0x017bfc):
   the accessor of the main menu object and the screen manager's request to load the menu
   package. They have no unwind information, so the object file table lists them on their own
   row; the rest of the object file is src/sequence/ScreenManager.cpp. */

/* The part of the screen manager used here: the flag that the menu package is loaded and
   the flag that the loading screen must be set up again. */
struct ScreenMgr {
    int m0;
    unsigned char m4;
    unsigned char m5;
    void f_017be0();
};

/* The main menu object. */
struct MainMenu {
    int m0;
};
extern MainMenu D_2304f8;

/* @implements 0x017bd4 us f_017bd4
   WHAT IT DOES: Returns the main menu object. */
MainMenu *f_017bd4()
{
    return &D_2304f8;
}

/* @implements 0x017be0 us f_017be0
   WHAT IT DOES: Marks the menu package as loaded (once), so the loading screen is not set up
   again. */
void ScreenMgr::f_017be0()
{
    if (!m4) {
        m4 = 1;
        m5 = 0;
    }
}
