/* The menu music object file (retail 0x097344 to 0x0980b0): one global CMenuBgm that plays
   the menu music as 24 tones on 24 voices. The "MenuBgm" database gives, for each of the 27
   menu mode and part combinations, which tones sound, their fade time and their volume.
   Start keys the tones of a mode on; Change fades tones in and out to move to another mode
   (or restarts when nothing is playing); a start that has to wait for the previous tones
   to finish is reserved and played later. The static data's startup and shutdown entries
   close the object file. */

#include <string.h>

extern "C" void f_093f90(const char *fmt, ...);

/* One sound voice (36 bytes); its methods are in the voice object file at 0x0fa28c. */
extern "C" void f_0fa28c(void *voice);
struct CVoice {
    CVoice() { f_0fa28c(this); }
    ~CVoice() {}
    int f_0fa3c0(unsigned short id, unsigned short tone, int d, float vol);
    int f_0fa458();
    int f_0fa5a8(int time, float vol);
    int f_0fa5f4(int time);
    int f_0fa640(unsigned short id, unsigned short tone, float vol);
    int f_0fa6d4();
    int m[9];
};

namespace DB {
class CDataBase {
public:
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
    char *f_036984(const char *key, int i, int index, int count);

    void *vptr;
    unsigned int cols;
    unsigned int rows;
    int type;
    int offset;
    int colName;
    int rowName;
};
}

extern DB::CDataBase D_24504c;
extern unsigned char D_24063c[];
extern const int D_1a211c[];

class CMenuBgm {
public:
    CMenuBgm();
    void f_0974cc();
    void f_0974f8();
    void f_097524();
    int f_097680(int mode, int part);
    int f_097878(int mode, int part);
    int f_097ba8();
    int f_097c14(int mode);
    int f_097ca4(int part);
    void f_097cbc();
    void f_097e9c();
    void f_097eec();
    int f_097f28(unsigned int idx);
    int f_097f98();

    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
    unsigned char m20;
    CVoice voice[24];
    int on[24];
    int tone[27][24];
    int fade[27][24];
    float vol[27][24];
};

static CMenuBgm D_242e14;

/* @implements 0x097344 us _ZN8CMenuBgmC2Ev
   WHAT IT DOES: Constructs the 24 voices, resets the play state and clears the tone table
   (base object constructor). */
/* @implements 0x097408 us _ZN8CMenuBgmC1Ev
   WHAT IT DOES: Same as the base object constructor (complete object constructor). */
CMenuBgm::CMenuBgm()
{
    f_097eec();
    f_097e9c();
}

/* @implements 0x0974cc us f_0974cc
   WHAT IT DOES: Resets the play state and loads the tone table from the database. */
void CMenuBgm::f_0974cc()
{
    f_097eec();
    f_097cbc();
}

/* @implements 0x0974f8 us f_0974f8
   WHAT IT DOES: Resets the play state and clears the tone table. */
void CMenuBgm::f_0974f8()
{
    f_097eec();
    f_097e9c();
}

/* @implements 0x097524 us f_097524
   WHAT IT DOES: Plays a reserved start once every voice has finished: keys on the reserved
   mode's tones at their volumes, keys the others off, and marks the music playing. */
void CMenuBgm::f_097524()
{
    int i;
    if (m16 < 0)
        return;
    if (f_097f98() != 1)
        return;
    f_093f90("CMenuBgm: ReservePlay Mode[%d] Part[%d]  ", m4, m12);
    for (i = 0; i < 24; i++) {
        if (tone[m16][i]) {
            voice[i].f_0fa3c0(609, i, 0, vol[m16][i]);
            on[i] = 1;
            f_093f90("Tone[%d] Vol[%f]  ", i, vol[m16][i]);
        } else {
            voice[i].f_0fa640(609, i, 0.0f);
            on[i] = 0;
        }
    }
    f_093f90(" \n");
    m20 = 1;
    m16 = -1;
}

/* @implements 0x097680 us f_097680
   WHAT IT DOES: Starts the music of a menu mode and part: keys the mode's tones on (or
   reserves the start while the voices still sound); returns -1 for an invalid mode or
   part, else 0. */
int CMenuBgm::f_097680(int mode, int part)
{
    int i;
    int m = f_097c14(mode);
    int p = 0;
    if (part >= 0)
        p = f_097ca4(part);
    if (m < 0)
        return -1;
    if (p < 0)
        return -1;
    if (m20 == 1)
        f_093f90("CMenuBgm: Start: Error! Multiple Start Function! Mode[%d] Part[%d]\n", m, p);
    m0 = -1;
    m4 = m;
    m8 = -1;
    m12 = p;
    m16 = -1;
    int idx = m * 3 + p;
    f_093f90("CMenuBgm: Start: Mode[%d] Part[%d]  ", m, p);
    if (f_097f28(idx) == 1) {
        for (i = 0; i < 24; i++)
            on[i] = 0;
        f_093f90("Not KeyOn\n");
        return 0;
    }
    if (!f_097f98()) {
        m16 = idx;
        f_093f90("Tone has not Finished\n");
        return 0;
    }
    for (i = 0; i < 24; i++) {
        if (tone[idx][i]) {
            voice[i].f_0fa3c0(609, i, 0, vol[idx][i]);
            on[i] = 1;
            f_093f90("Tone[%d] Vol[%f]  ", i, vol[idx][i]);
        } else {
            voice[i].f_0fa640(609, i, 0.0f);
            on[i] = 0;
        }
    }
    f_093f90(" \n");
    m20 = 1;
    return 0;
}

/* @draft 0x097878 us f_097878
   WHAT IT DOES: Changes the music to another menu mode and part. While playing, fades the
   new mode's tones in and the others out (or fades everything out when the new mode has no
   tones); when stopped, restarts like Start. Returns -1 for an invalid mode or part. */
int CMenuBgm::f_097878(int mode, int part)
{
    int i;
    int m = f_097c14(mode);
    int p = 0;
    if (part >= 0)
        p = f_097ca4(part);
    if (m < 0)
        return -1;
    if (p < 0)
        return -1;
    m16 = -1;
    m0 = m4;
    m4 = m;
    m8 = m12;
    m12 = p;
    f_093f90("CMenuBgm: Change: Mode[%d -> %d] Part[%d -> %d] ", m0, m4, m8, m12);
    int idx = m * 3 + p;
    if (m20 == 0) {
        if (f_097f28(idx) == 1) {
            for (i = 0; i < 24; i++)
                on[i] = 0;
            f_093f90("Not KeyOn\n");
            return 0;
        }
        if (!f_097f98()) {
            m16 = idx;
            f_093f90("Tone has not Finished\n");
            return 0;
        }
        m20 = 1;
        f_093f90(" Restart\n");
        for (i = 0; i < 24; i++) {
            if (tone[idx][i]) {
                voice[i].f_0fa3c0(609, i, 0, vol[idx][i]);
                on[i] = 1;
                f_093f90("Tone[%d] Vol[%f]  ", i, vol[idx][i]);
            } else {
                voice[i].f_0fa640(609, i, 0.0f);
                on[i] = 0;
            }
        }
        f_093f90("\n");
        return 0;
    }
    if (f_097f28(idx) == 1) {
        for (i = 0; i < 24; i++) {
            int t = fade[idx][i];
            voice[i].f_0fa5f4(t);
            on[i] = 0;
            f_093f90("FadeKeyOff: Tone[%d] FadeTime[%d]  ", i, t);
        }
        m20 = 0;
        f_093f90("\n");
        return 0;
    }
    for (i = 0; i < 24; i++) {
        if (tone[idx][i]) {
            if (!on[i]) {
                int t = fade[idx][i];
                voice[i].f_0fa5a8(t, vol[idx][i]);
                on[i] = 1;
                f_093f90("FadeIn: Tone[%d] FadeTime[%d] Vol[%f]  ", i, t, vol[idx][i]);
            }
        } else {
            if (on[i]) {
                int t = fade[idx][i];
                voice[i].f_0fa5a8(t, 0.0f);
                on[i] = 0;
                f_093f90("FadeOut: Tone[%d] FadeTime[%d]  ", i, t);
            }
        }
    }
    f_093f90("\n");
    return 0;
}

/* @implements 0x097ba8 us f_097ba8
   WHAT IT DOES: Stops the music: resets the play state and stops every voice. */
int CMenuBgm::f_097ba8()
{
    int i;
    f_097eec();
    for (i = 0; i < 24; i++) {
        voice[i].f_0fa458();
        on[i] = 0;
    }
    f_093f90("CMenuBgm: Stop \n ");
    return 0;
}

/* @implements 0x097c14 us f_097c14
   WHAT IT DOES: Converts a menu mode number (1 to 9) to a table mode (0 to 8); logs and
   returns -1 for any other number. */
int CMenuBgm::f_097c14(int mode)
{
    int r;
    switch (mode) {
    case 1: r = 0; break;
    default:
        f_093f90("CMenuBgm: ConvertMode Failed! Invalid Mode[%d]\n", mode);
        r = -1;
        break;
    case 2: r = 1; break;
    case 3: r = 2; break;
    case 4: r = 3; break;
    case 5: r = 4; break;
    case 6: r = 5; break;
    case 7: r = 6; break;
    case 8: r = 7; break;
    case 9: r = 8; break;
    }
    return r;
}

/* @implements 0x097ca4 us f_097ca4
   WHAT IT DOES: Converts a part number (1 to 3) to a table part (0 to 2), else -1. */
int CMenuBgm::f_097ca4(int part)
{
    part--;
    if (part >= 3)
        part = -1;
    return part;
}

/* @draft 0x097cbc us f_097cbc
   WHAT IT DOES: Loads the tone table from the menu music database: for each mode and part
   row, each tone's on flag, fade time and volume (three columns per tone). */
void CMenuBgm::f_097cbc()
{
    int m, p, i;
    for (m = 0; m < 9; m++) {
        for (p = 0; p < 3; p++) {
            int col = 0;
            for (i = 0; i < 24; i++) {
                DB::CDataBase *db = &D_24504c;
                memcpy(D_24063c, db->f_0368e8(0, db->f_036984(0, m * 3 + p, db->rowName, db->rows), col, 0), D_1a211c[1]);
                tone[m * 3 + p][i] = D_24063c[0];
                memcpy(D_24063c, db->f_0368e8(0, db->f_036984(0, m * 3 + p, db->rowName, db->rows), col + 1, 0), D_1a211c[2]);
                fade[m * 3 + p][i] = *(short *)D_24063c;
                memcpy(D_24063c, db->f_0368e8(0, db->f_036984(0, m * 3 + p, db->rowName, db->rows), col + 2, 0), D_1a211c[4]);
                vol[m * 3 + p][i] = *(float *)D_24063c;
                col += 3;
            }
        }
    }
}

/* @implements 0x097e9c us f_097e9c
   WHAT IT DOES: Clears the tone table: no tone on, no fade time, full volume. */
void CMenuBgm::f_097e9c()
{
    int m, i;
    for (m = 0; m < 27; m++) {
        for (i = 0; i < 24; i++) {
            tone[m][i] = 0;
            fade[m][i] = 0;
            vol[m][i] = 1.0f;
        }
    }
}

/* @implements 0x097eec us f_097eec
   WHAT IT DOES: Resets the play state: no reserved start, no mode or part, not playing, all
   tones off. */
void CMenuBgm::f_097eec()
{
    int i;
    m0 = -1;
    m4 = -1;
    m8 = -1;
    m12 = -1;
    m20 = 0;
    m16 = -1;
    for (i = 0; i < 24; i++)
        on[i] = 0;
}

/* @implements 0x097f28 us f_097f28
   WHAT IT DOES: Returns 1 if a mode and part row has no tone on, else 0; logs and returns 0
   for an invalid row. */
int CMenuBgm::f_097f28(unsigned int idx)
{
    int i;
    if (idx >= 27) {
        f_093f90("CMenuBgm: IsAllToneOffForDB Failed! Invalid Mode[%d] \n", idx);
        return 0;
    }
    for (i = 0; i < 24; i++) {
        if (tone[idx][i])
            return 0;
    }
    return 1;
}

/* @implements 0x097f98 us f_097f98
   WHAT IT DOES: Returns 1 if every voice has finished sounding, else 0. */
int CMenuBgm::f_097f98()
{
    int i;
    for (i = 0; i < 24; i++) {
        if (!voice[i].f_0fa6d4())
            return 0;
    }
    return 1;
}

/* @implements 0x097fec us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global menu music object at startup and destroys its voices
   at shutdown. */
/* @implements 0x098070 us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x098090 us _GLOBAL__D_
   WHAT IT DOES: Shutdown entry of the object file's static data. */
