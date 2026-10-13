/* The movie subtitle table object file (retail 0x08a3c0 to 0x08a71c): the hard subtitle
   timings of the opening movie, read from the "Hardsub" text entry of the MovieHardSub
   package. Each line is "STR start end id" and the list ends with "END". The movie player
   creates one table for the movies that carry subtitles. */

extern "C" int strcmp(const char *, const char *);
extern "C" int iprintf(const char *, ...);

/* A data package: one archive file from the disc, whose entries are looked up by name. */
class CPackage {
public:
    CPackage() { m0 = -1; }
    ~CPackage() { f_0026cc(); }
    void f_00260c(const char *name, int a, int b);
    void f_0026cc();
    void f_002734(int a);
    char *f_002acc(const char *name);
    int m0;
    int m4[69];
};

class CMovieHardSub {
public:
    CMovieHardSub();
    ~CMovieHardSub();
    int Load();
    void Clear(char *buf, int n);

    int start[15];
    int end[15];
    int id[15];
    int count;
    int m184;
    int m188;
    int m192;
    int m196;
    float m200;
    int m204;
    int m208;
    float m212;
    float m216;
};

/* @implements 0x08a3c0 us _ZN13CMovieHardSubC2Ev
   WHAT IT DOES: Empties the table and sets the subtitle drawing defaults (position 240, 236,
   width 246, scale 0.8, fade over 10 frames). */
/* @implements 0x08a41c us _ZN13CMovieHardSubC1Ev
   WHAT IT DOES: The same constructor (complete object version). */
CMovieHardSub::CMovieHardSub()
{
    m184 = 240;
    m188 = 236;
    m192 = 246;
    m196 = 1;
    m200 = 0.8f;
    m204 = 1;
    m208 = 10;
    m212 = 1.0f;
    count = 0;
    m216 = m212 / m208;
}

/* @implements 0x08a478 us _ZN13CMovieHardSubD2Ev
   WHAT IT DOES: The empty destructor. */
/* @implements 0x08a480 us _ZN13CMovieHardSubD1Ev
   WHAT IT DOES: The same (complete object version). */
CMovieHardSub::~CMovieHardSub()
{
}

/* @draft 0x08a488 us _ZN13CMovieHardSub4LoadEv
   WHAT IT DOES: Opens the MovieHardSub package and parses its Hardsub text: for each "STR"
   line it reads the start, end and id numbers into the next table entry; "END" stores the
   entry count. An unknown word prints an error and returns 1; otherwise returns 0.
   Remaining difference: retail reads the third number's digits with lbu and keeps the byte
   in a register (seb at the compare and at the add, as for the word copy loop); every
   spelling tried gives lb, which shifts the register choice of all three numbers. */
int CMovieHardSub::Load()
{
    char line[128];
    CPackage pkg;
    char word[64];
    int n = 0;

    pkg.f_00260c("MovieHardSub", 0, 0);
    pkg.f_002734(0);
    char *p = pkg.f_002acc("Hardsub");
    if (*p) {
        do {
            int i;
            int a, b, c;
            Clear(word, 64);
            for (i = 0; *p != ' ' && *p != '\n'; i++) {
                word[i] = *p;
                p++;
            }
            p++;
            if (strcmp("END", word) == 0) {
                count = n;
                break;
            }
            if (strcmp("STR", word) != 0) {
                iprintf("ERROR : (work)%s\n", word);
                pkg.f_0026cc();
                return 1;
            }
            a = 0;
            while (*p != ' ') {
                a = a * 10 + *p - '0';
                p++;
            }
            p++;
            b = 0;
            while (*p != ' ') {
                b = b * 10 + *p - '0';
                p++;
            }
            p++;
            c = 0;
            char ch = *p;
            while (ch != '\n') {
                p++;
                c = c * 10 + ch - '0';
                ch = *p;
            }
            start[n] = a;
            end[n] = b;
            id[n] = c;
            p++;
            n++;
        } while (*p);
    }
    pkg.f_0026cc();
    return 0;
}

/* @implements 0x08a6f8 us _ZN13CMovieHardSub5ClearEPci
   WHAT IT DOES: Zeroes n bytes of buf. */
void CMovieHardSub::Clear(char *buf, int n)
{
    for (int i = 0; i < n; i++)
        buf[i] = 0;
}
