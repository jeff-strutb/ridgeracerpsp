/* The game's language setting (retail 0x01c1e4 to 0x01c2cc): which of the seven text languages
   is in use, chosen from the console's system language at start up, and the file names that
   carry the matching language suffix. */

#include <stdio.h>

int f_10bda4(void);

/* The current text language. */
int D_1d1730 = 1;
extern char D_23bacc[];

/* @implements 0x01c1e4 us f_01c1e4
   WHAT IT DOES: Picks the game's text language from the console's language setting. French,
   Spanish, German, Italian and Dutch (system languages 2 to 6) map straight across; Japanese,
   English and anything unknown use English, or language 6 when the region query says so. */
void f_01c1e4(int language)
{
    int l;

    switch (language) {
    default:
        l = 1;
        if (f_10bda4() == 1)
            l = 6;
        break;
    case 6:
        l = 6;
        break;
    case 2:
        l = 2;
        break;
    case 3:
        l = 3;
        break;
    case 4:
        l = 4;
        break;
    case 5:
        l = 5;
        break;
    }
    D_1d1730 = l;
}

/* @implements 0x01c260 us f_01c260
   WHAT IT DOES: Returns the game's current text language. */
int f_01c260(void)
{
    return D_1d1730;
}

/* @implements 0x01c26c us f_01c26c
   WHAT IT DOES: Builds the name of a language specific file: the given name followed by the
   current language's suffix, in a shared buffer it returns. */
char *f_01c26c(const char *name)
{
    /* Each language's file name suffix (6 is American English). */
    static const char *suffix[] = { "JP", "EN", "FR", "SP", "GE", "IT", "AM" };
    char *buf = D_23bacc;
    sprintf(buf, "%s%s", name, suffix[f_01c260()]);
    return buf;
}
