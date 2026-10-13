/* Start menu methods placed after the menu screens' object file (retail 0x076e90 to
   0x076f98): two flag setters and a constant answer from the start menu's vtable, and the
   reset of the start menu's settings record before its table is loaded. */

/* The part of the start menu object these methods touch. */
struct StartMenu {
    char m0[520];
    bool m520;
    char m521[2];
    bool m523;
};

/* The start menu's settings record, cleared before the table is read into it. */
struct StartMenuSet {
    char m0[48];
    char m48[48];
    char m96[48];
    char m144[48][10];
    char m624[48];
    char m672[48];
    char m720;
    char m721[48];
    int m772[48];
    int m964[26];
    int m1068[26];
    char m1172[832];
    char m2004;
    char m2005[60];
    char m2065[60];
    char m2125[60];
    char m2185[60];
    int m2248[60];
    int m2488[60];
    int m2728[60];
    char m2968;
};

/* @implements 0x076e90 us f_076e90
   WHAT IT DOES: Sets the start menu flag at +520. */
extern "C" void f_076e90(StartMenu *m)
{
    m->m520 = 1;
}

/* @implements 0x076e9c us f_076e9c
   WHAT IT DOES: Answers 0 (the start menu's reply to this vtable query). */
extern "C" int f_076e9c(StartMenu *m)
{
    return 0;
}

/* @implements 0x076ea4 us f_076ea4
   WHAT IT DOES: Sets the start menu flag at +523. */
extern "C" void f_076ea4(StartMenu *m)
{
    m->m523 = 1;
}

/* @implements 0x076eb0 us f_076eb0
   WHAT IT DOES: Clears the start menu's settings record: the 48 entry tables (flags, names
   and values), the 26 entry tables and the 60 entry tables, and the three single flags. The
   26 entry loop clears one name byte per entry from inside an empty inner loop of 8. */
extern "C" void f_076eb0(StartMenuSet *s)
{
    int i, j;

    for (i = 0; i < 48; i++) {
        s->m772[i] = 0;
        s->m0[i] = 0;
        s->m48[i] = 0;
        s->m96[i] = 0;
        s->m624[i] = 0;
        s->m672[i] = 0;
        s->m721[i] = 0;
        for (j = 0; j < 10; j++)
            s->m144[i][j] = 0;
    }
    for (i = 0; i < 26; i++) {
        s->m964[i] = 0;
        s->m1068[i] = 0;
        for (j = 0; j < 8; j++)
            s->m144[i][i] = 0;
    }
    for (i = 0; i < 60; i++) {
        s->m2005[i] = 0;
        s->m2065[i] = 0;
        s->m2125[i] = 0;
        s->m2185[i] = 0;
        s->m2488[i] = 0;
        s->m2728[i] = 0;
        s->m2248[i] = 0;
    }
    s->m720 = 0;
    s->m2004 = 0;
    s->m2968 = 0;
}
