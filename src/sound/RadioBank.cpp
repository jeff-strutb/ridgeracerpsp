/* The radio DJ's voice bank object file (retail 0x0f99c8 to 0x0fa284, Radio::CTable; its debug
   prints say "Radio CBank"). The 24 byte object picks the two voice banks of a race: the DJ
   (normal, fake for some rival races, or female) and the race's own bank (the course's, or
   one of the shared ones by race mode, chosen at random), and loads and transfers them to the
   sound memory, naming each by the bank name and the language ("<bank>_<lang>_Free"). */

#include <stdio.h>
#include <string.h>

void f_093f90(const char *fmt, ...);

extern "C" {
int f_01c260(void);   /* the language */
int f_0f6b90(void);   /* the DJ's random number */
}

/* A pair of values handed back by value. */
struct Pair {
    int a;
    int b;
};

/* A data package: its entries are found by name. */
struct CPackage {
    int f_002acc(const char *name);
};
extern CPackage D_1d8988;

/* The sequence manager, as far as its settings and scene players are concerned. */
struct CSequence {
    Pair f_0031c0();
    Pair f_0031dc(int i);
    CPackage *f_005a38(const char *name);
    void f_005d4c(const char *name);
    char m0[276];
    Pair m276;
};
extern CSequence D_1dd6b0;

/* The sound memory. */
struct CSoundMem {
    void f_01c458(int id, int size, int b, unsigned short *out);
    void f_01c578();
};
extern CSoundMem D_23bb4c;

/* A game database table. */
struct CTableDB {
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
};
extern CTableDB D_2407a8;   /* courses */
extern CTableDB D_2407d0;   /* sequences */
extern CTableDB D_240740;   /* cars */

extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern int D_240910;        /* number of computer cars */

/* The voice bank names. */
const char *D_1d5db8[20] = {
    "DjNormal", "DjFake",   "DjFemale", "DjBsAllM", "DjBsDuel", "DjBsNet",  "DjBsSing",
    "DjBsTime", "DjBsCrim", "DjBsCrys", "DjBsDiab", "DjBsDown", "DjBsGree", "DjBsLake",
    "DjBsMidt", "DjBsRidg", "DjBsSeas", "DjBsSilv", "DjBsSuns", "DjBsUnio",
};

/* Tells whether the sequence row read last has the given mode. */
static inline bool IsSeq(int k)
{
    return D_24063c[0] == k;
}

/* Reads a sequence's row and tells whether its mode is k. */
static inline bool Seq(const char *row, int k)
{
    char *f = D_2407d0.f_0368e8("SequenceNumber", row, 0, 0);
    memcpy(D_24063c, f, D_1a211c[1]);
    return D_24063c[0] == k;
}

/* Computer car i's settings row. */
static inline Pair Car(int i)
{
    Pair r = D_1dd6b0.f_0031dc(i);
    return r;
}

namespace Radio {

class CTable {
public:
    CTable();
    void f_0f9a08();
    int f_0f9a28();
    int f_0f9a8c();
    int f_0f9acc();
    void f_0f9ad4();
    int f_0f9b30(int id);
    int f_0f9b50(int bank);
    int f_0f9c68(int bank);
    static int f_0f9e04();
    int f_0f9f88();

    int m0;    /* banks transferred */
    int m4;    /* the DJ's bank */
    int m8;    /* the race's bank */
    int m12;   /* banks picked */
    int m16;   /* the DJ bank's sound memory id */
    int m20;   /* the race bank's sound memory id */
};

/* @implements 0x0f99c8 us _ZN5Radio6CTableC2Ev
   WHAT IT DOES: Makes a table with no banks (base object constructor). */
/* @implements 0x0f99e8 us _ZN5Radio6CTableC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CTable::CTable()
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    m12 = 0;
    m16 = -1;
    m20 = -1;
}

/* @implements 0x0f9a08 us f_0f9a08
   WHAT IT DOES: Clears the table: no banks. */
void CTable::f_0f9a08()
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    m12 = 0;
    m16 = -1;
    m20 = -1;
}

/* @implements 0x0f9a28 us f_0f9a28
   WHAT IT DOES: Picks the two banks once and asks for both to be loaded. */
int CTable::f_0f9a28()
{
    if (m12 == 0) {
        m4 = f_0f9e04();
        m8 = f_0f9f88();
        m12 = 1;
    }
    f_0f9b50(m4);
    return f_0f9b50(m8);
}

/* @implements 0x0f9a8c us f_0f9a8c
   WHAT IT DOES: Transfers both loaded banks to the sound memory (the result is whatever the
   last transfer left, as in retail). */
int CTable::f_0f9a8c()
{
    m16 = f_0f9c68(m4);
    m20 = f_0f9c68(m8);
    m12 = 0;
}

/* @implements 0x0f9acc us f_0f9acc
   WHAT IT DOES: Tells whether the banks are ready: always 1. */
int CTable::f_0f9acc()
{
    return 1;
}

/* @implements 0x0f9ad4 us f_0f9ad4
   WHAT IT DOES: Frees every transferred bank from the sound memory. */
void CTable::f_0f9ad4()
{
    while (m0 > 0) {
        m0--;
        D_23bb4c.f_01c578();
    }
    m16 = -1;
    m20 = -1;
}

/* @implements 0x0f9b30 us f_0f9b30
   WHAT IT DOES: The sound memory id of the bank holding a voice: the DJ's bank for voices 559
   to 561, else the race's bank. */
int CTable::f_0f9b30(int id)
{
    if (id >= 559 && id <= 561)
        return m16;
    return m20;
}

/* @implements 0x0f9b50 us f_0f9b50
   WHAT IT DOES: Asks for a bank's free scene to be loaded for the language. */
int CTable::f_0f9b50(int bank)
{
    char name[32];
    char lang[3];
    int l = f_01c260();
    if (bank < 0 || bank >= 20) {
        f_093f90("Radio CBank: LoadRequest Failed:%d\n", bank);
        return -1;
    }
    switch (l) {
    case 2:
        strcpy(lang, "Fr");
        break;
    case 3:
        strcpy(lang, "Sp");
        break;
    case 4:
        strcpy(lang, "Ge");
        break;
    case 5:
        strcpy(lang, "It");
        break;
    default:
        strcpy(lang, "En");
        break;
    }
    sprintf(name, "%s_%s_Free", D_1d5db8[bank], lang);
    D_1dd6b0.f_005d4c(name);
    f_093f90("Radio CBank: LoadRequest[%s]\n", name);
    return 0;
}

/* @draft 0x0f9c68 us f_0f9c68
   REMAINING DIFFERENCE: the returned id and the transfer count swap v0 and v1, so the result is
   copied to v0 at the end (one word longer).
   WHAT IT DOES: Transfers a loaded bank's data to the sound memory and returns its id there. */
int CTable::f_0f9c68(int bank)
{
    unsigned short id;
    char name[32];
    char lang[3];
    if (bank >= 0 && bank < 20) {
        strcpy(name, D_1d5db8[bank]);
        int h = D_1d8988.f_002acc(name);
        switch (f_01c260()) {
        case 2:
            strcpy(lang, "Fr");
            break;
        case 3:
            strcpy(lang, "Sp");
            break;
        case 4:
            strcpy(lang, "Ge");
            break;
        case 5:
            strcpy(lang, "It");
            break;
        default:
            strcpy(lang, "En");
            break;
        }
        sprintf(name, "%s_%s_Free", D_1d5db8[bank], lang);
        int size = D_1dd6b0.f_005a38(name)->f_002acc("Bd");
        f_093f90("Radio CBank: Transfer[%s]\n", name);
        D_23bb4c.f_01c458(h, size, 0, &id);
        int r = id;
        m0++;
        return r;
    }
    f_093f90("Radio CBank: Transfer Failed:%d\n", bank);
    return -1;
}

/* @draft 0x0f9e04 us f_0f9e04
   REMAINING DIFFERENCE: retail schedules the result copy (move v0,v1) first in the epilogue
   block, so its returns jump past it; the size table address register (v1/v0) and the female
   flag register also differ.
   WHAT IT DOES: Picks the DJ's bank: in a rival race the fake DJ for the computer car that has
   one (in modes 0, 1 and 6), the female DJ for a car that has her, else the normal DJ. */
int CTable::f_0f9e04()
{
    Pair r = D_1dd6b0.m276;
    int mode = f_01c260();
    char *f = D_2407d0.f_0368e8("SequenceNumber", (char *)r.a, 0, 0);
    int size = D_1a211c[1];
    memcpy(D_24063c, f, size);
    if (!IsSeq(5))
        return 0;
    if (D_240910 <= 0) {
        f_093f90("Radio CBank: ReadData Failed! Invalid ComCar Num:%d\n", D_240910);
        return -1;
    }
    Pair c = Car(0);
    f = D_240740.f_0368e8("DjFake", (char *)c.a, 0, 0);
    memcpy(D_24063c, f, size);
    if (D_24063c[0] == 0) {
        f = D_240740.f_0368e8("DjFemale", (char *)c.a, 0, 0);
        memcpy(D_24063c, f, size);
        return (D_24063c[0] != 0) * 2;
    }
    switch (mode) {
    case 0:
    case 1:
    case 6:
        return 1;
    }
    return 0;
}

/* @draft 0x0f9f88 us f_0f9f88
   REMAINING DIFFERENCE: in the coin toss between the time attack and shared banks retail keeps
   the remainder in a0 and builds the result in a2 in place; the first sequence lookup also
   loads its two addresses in the other order.
   WHAT IT DOES: Picks the race's bank by the race's sequence: one of the shared banks or the
   course's own, at random, with the time attack, net and single race banks for their modes;
   -1 for an unknown mode or course. */
int CTable::f_0f9f88()
{
    Pair r = D_1dd6b0.m276;
    Pair c = D_1dd6b0.f_0031c0();
    char name[32];
    char *cn = (char *)c.a;
    sprintf(name, "DjBs%s", D_2407a8.f_0368e8("DjCourseName", cn, 0, 0));
    int course = -1;
    for (int i = 0; i < 20; i++) {
        if (strcmp(name, D_1d5db8[i]) == 0) {
            course = i;
            break;
        }
    }
    if (course < 0) {
        f_093f90("Radio CBank: ReadData Failed! NotFound Course DataBlock:%s\n", name);
        return -1;
    }
    const char *col = "SequenceNumber";
    char *f = D_2407d0.f_0368e8(col, (char *)r.a, 0, 0);
    int size = D_1a211c[1];
    memcpy(D_24063c, f, size);
    int res;
    if (IsSeq(1))
        goto single;
    memcpy(D_24063c, D_2407d0.f_0368e8(col, (char *)r.a, 0, 0), size);
    if (IsSeq(4)) {
        int k;
single:
        k = f_0f6b90() % 3;
        if (k == 0)
            res = 3;
        else if (k == 1)
            res = course;
        else
            res = 6;
    } else {
        memcpy(D_24063c, D_2407d0.f_0368e8(col, (char *)r.a, 0, 0), size);
        if (IsSeq(2)) {
            int k = f_0f6b90() % 2;
            res = k != 0;
            res = res * 4 + 3;
        } else {
            memcpy(D_24063c, D_2407d0.f_0368e8(col, (char *)r.a, 0, 0), size);
            if (IsSeq(5))
                return -1;
            memcpy(D_24063c, D_2407d0.f_0368e8(col, (char *)r.a, 0, 0), size);
            if (IsSeq(3)) {
                int k = f_0f6b90() % 3;
                if (k == 0)
                    res = 3;
                else if (k == 1)
                    res = course;
                else
                    res = 5;
            } else {
                f_093f90("Radio CBank: ReadData Failed! Invalid Mode:%s\n", (char *)c.a);
                res = -1;
            }
        }
    }
    return res;
}

}
