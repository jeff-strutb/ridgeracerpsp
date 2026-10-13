/* The environment sound bank (retail 0x0970c0 to 0x097344): the course's environment sound
   bank "Env<course>" with its load count and the sound system's bank handle. Loading
   transfers the bank's header and body to the sound system; unloading releases it once per
   load; the free request frees the course's "Env<course>_Free" scene. Its own object file,
   placed after the CEnviron object file's static data entries. */

#include <stdio.h>

extern "C" {
void f_093f90(const char *fmt, ...);
int f_01c458(void *snd, void *header, void *body, int a, unsigned short *handle);
void f_01c578(void *snd);
}

/* A pair of values the settings hand back by value. */
struct Pair {
    char *a;
    int b;
};

/* A data package: its entries are found by name. */
struct CPackage {
    void *f_002acc(const char *name);
};

/* The sequence manager, as far as the course setting and the scene players are concerned. */
struct CSequence {
    Pair f_0031c0();
    CPackage *f_005a38(const char *name);
    void f_005d4c(const char *name);
};

namespace DB {
class CDataBase {
public:
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
};
}

extern CSequence D_1dd6b0;
extern DB::CDataBase D_2407a8;
extern CPackage D_1d8988;
extern char D_23bb4c[];

struct CEnvBank {
    CEnvBank();
    void f_0970d8();
    int f_0970e4();
    int f_097100();
    int f_09711c();
    void f_097124();
    int f_097174();
    int f_097208();

    int m0;
    unsigned short m4;
};

/* @implements 0x0970c0 us _ZN8CEnvBankC2Ev
   WHAT IT DOES: Clears the bank (base object constructor). */
/* @implements 0x0970cc us _ZN8CEnvBankC1Ev
   WHAT IT DOES: Clears the bank (complete object constructor). */
CEnvBank::CEnvBank()
{
    m0 = 0;
    m4 = 0;
}

/* @implements 0x0970d8 us f_0970d8
   WHAT IT DOES: Clears the load count and the bank handle. */
void CEnvBank::f_0970d8()
{
    m0 = 0;
    m4 = 0;
}

/* @implements 0x0970e4 us f_0970e4
   WHAT IT DOES: Requests the course's free scene (0x097174). */
int CEnvBank::f_0970e4()
{
    return f_097174();
}

/* @implements 0x097100 us f_097100
   WHAT IT DOES: Loads the course's bank into the sound system (0x097208). */
int CEnvBank::f_097100()
{
    return f_097208();
}

/* @implements 0x09711c us f_09711c
   WHAT IT DOES: Returns 1 (always ready). */
int CEnvBank::f_09711c()
{
    return 1;
}

/* @implements 0x097124 us f_097124
   WHAT IT DOES: Releases the bank from the sound system once per load and clears the
   handle. */
void CEnvBank::f_097124()
{
    while (m0 > 0) {
        m0--;
        f_01c578(D_23bb4c);
        m4 = 0;
    }
}

/* @implements 0x097174 us f_097174
   WHAT IT DOES: Frees the scene "Env<course>_Free" of the current course and logs the
   request. */
int CEnvBank::f_097174()
{
    CSequence *seq = &D_1dd6b0;
    Pair p = seq->f_0031c0();
    char buf[32];
    char *row = p.a;
    char *name = D_2407a8.f_0368e8("DjCourseName", row, 0, 0);
    sprintf(buf, "Env%s_Free", name);
    seq->f_005d4c(buf);
    f_093f90("Sound CEnvBank: LoadRequest[%s]\n", buf);
    return 0;
}

/* @implements 0x097208 us f_097208
   WHAT IT DOES: Finds the course's bank header "Env<course>" in the common sound package
   and its body "Bd" in the scene "Env<course>_Free", transfers both to the sound system
   (which returns the bank handle), counts the load and logs it. */
int CEnvBank::f_097208()
{
    CSequence *seq = &D_1dd6b0;
    const char *col = "DjCourseName";
    DB::CDataBase *db = &D_2407a8;
    Pair p = seq->f_0031c0();
    char buf[32];
    sprintf(buf, "Env%s", db->f_0368e8(col, p.a, 0, 0));
    void *header = D_1d8988.f_002acc(buf);
    sprintf(buf, "Env%s_Free", db->f_0368e8(col, p.a, 0, 0));
    f_01c458(D_23bb4c, header, seq->f_005a38(buf)->f_002acc("Bd"), 0, &m4);
    m0++;
    f_093f90("Sound CEnvBank: Transfer[%s] BankHandle[%d]\n", buf, m4);
    return 0;
}
