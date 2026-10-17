/* The voice groups (retail 0x110790 to 0x110e2c): 32 polyphony groups set up from the mixer
   configuration's GROUP rows (0x10e198), each with a voice limit and a slot table of voices
   and their priorities. A sound starting on a full group takes the slot of the lowest
   priority voice (the older one on a tie), stopping it. One global instance (D_281eb8).
   Errors: 0x80000013 for a group with no slots, 0x80000019 when every voice outranks the new
   sound. */

struct VoiceGroup {
    int max;
    int count;
    int ch[32];             /* -1 for a free slot */
    int prio[32];
};

/* A group row of the configuration (0x10e180). */
struct GroupRow {
    int used;
    int value;
};

/* The part of a SAS voice's state used here (0x10d160). */
struct SasVoice {
    unsigned char on;
    char m1[3];
    int age;
    char m8;
    unsigned char group;
};

extern "C" {
GroupRow *f_10e180(void);
SasVoice *f_10d160(int a, int ch);
void f_10d29c(int ch);
void f_10d2e8(int ch);
int f_10f608(int ch);
}

class CVoiceGroups {
public:
    VoiceGroup m[32];

    void f_110790();
    void f_110818();
    void f_110820(int ch);
    void f_110918(int grp);
    int f_1109cc(int grp);
    int f_1109ec(int grp);
    int f_110a04(int prio, int *slot, int grp);
    void f_110c74(int prio, int slot, int grp, int ch);
};

extern CVoiceGroups *D_281eb8;

/* @implements 0x110790 us _ZN12CVoiceGroups8f_110790Ev
   WHAT IT DOES: Sets every configured group up empty with its voice limit. */
void CVoiceGroups::f_110790()
{
    GroupRow *row = f_10e180();
    int i, j;

    for (i = 0; i < 32; i++) {
        if (row[i].used) {
            m[i].max = row[i].value;
            m[i].count = 0;
            for (j = 0; j < m[i].max; j++) {
                m[i].ch[j] = -1;
                m[i].prio[j] = -1;
            }
        }
    }
}

/* @implements 0x110818 us _ZN12CVoiceGroups8f_110818Ev
   WHAT IT DOES: Does nothing (the groups need no shutdown). */
void CVoiceGroups::f_110818()
{
}

/* @implements 0x110820 us _ZN12CVoiceGroups8f_110820Ei
   WHAT IT DOES: Frees voice ch's slot in its group. */
void CVoiceGroups::f_110820(int ch)
{
    SasVoice *v = f_10d160(0, ch);
    int i;

    for (i = 0; i < m[v->group].max; i++) {
        if (m[v->group].ch[i] == ch) {
            m[v->group].ch[i] = -1;
            m[v->group].prio[i] = -1;
            m[v->group].count--;
        }
    }
}

/* @implements 0x110918 us _ZN12CVoiceGroups8f_110918Ei
   WHAT IT DOES: Stops every voice of group grp (0x10f608) and frees its slots. */
void CVoiceGroups::f_110918(int grp)
{
    int i;

    for (i = 0; i < m[grp].max; i++) {
        if (m[grp].ch[i] != -1) {
            f_10f608(m[grp].ch[i]);
            m[grp].ch[i] = -1;
            m[grp].prio[i] = -1;
            m[grp].count--;
        }
    }
}

/* @implements 0x1109cc us _ZN12CVoiceGroups8f_1109ccEi
   WHAT IT DOES: Returns group grp's free slots. */
int CVoiceGroups::f_1109cc(int grp)
{
    return m[grp].max - m[grp].count;
}

/* @implements 0x1109ec us _ZN12CVoiceGroups8f_1109ecEi
   WHAT IT DOES: Returns group grp's voice limit. */
int CVoiceGroups::f_1109ec(int grp)
{
    return m[grp].max;
}

/* @draft 0x110a04 us _ZN12CVoiceGroups8f_110a04EiPii
   WHAT IT DOES: Finds a slot in group grp for a sound of priority prio: the first free one,
   or else the lowest priority voice's (the older on a tie), whose voice is stopped.
   DRAFT: 67 of 156 words differ. Retail keeps the "take slot i" block as the fall-through of
   the priority test with the tie checks out of line; here GCC makes it a branch-likely
   target. Retail also returns each code straight in v0 (here through t0) and keeps the
   current best index in a1. */
int CVoiceGroups::f_110a04(int prio, int *slot, int grp)
{
    int i;

    *slot = 0;
    if (m[grp].max <= 0)
        return 0x80000013;
    if (m[grp].count >= m[grp].max) {
        for (i = 1; i < m[grp].max; i++) {
            if (m[grp].prio[i] >= m[grp].prio[*slot]) {
                if (m[grp].prio[i] != m[grp].prio[*slot])
                    continue;
                if (m[grp].prio[i] != -1
                    && f_10d160(0, m[grp].ch[i])->age <= f_10d160(0, m[grp].ch[*slot])->age)
                    continue;
            }
            *slot = i;
        }
        if (prio < m[grp].prio[*slot] || m[grp].prio[*slot] == -1)
            return 0x80000019;
        SasVoice *v = f_10d160(0, m[grp].ch[*slot]);
        if (v->on == 1) {
            v->on = 0;
            f_10d29c(m[grp].ch[*slot]);
        } else {
            f_10d2e8(m[grp].ch[*slot]);
        }
        m[grp].ch[*slot] = -1;
        m[grp].prio[*slot] = -1;
        m[grp].count--;
        return 0;
    } else {
        for (i = 0; i < m[grp].max; i++) {
            if (m[grp].ch[i] == -1) {
                *slot = i;
                return 0;
            }
        }
        return 0;
    }
}

/* @implements 0x110c74 us _ZN12CVoiceGroups8f_110c74Eiiii
   WHAT IT DOES: Puts voice ch with priority prio into slot of group grp. */
void CVoiceGroups::f_110c74(int prio, int slot, int grp, int ch)
{
    m[grp].count++;
    m[grp].ch[slot] = ch;
    m[grp].prio[slot] = prio;
}

extern "C" {
/* @implements 0x110cac us f_110cac
   WHAT IT DOES: Creates the global voice groups and sets them up. */
void f_110cac(void)
{
    D_281eb8 = new CVoiceGroups;
    D_281eb8->f_110790();
}

/* @implements 0x110cd8 us f_110cd8
   WHAT IT DOES: Shuts the global voice groups down and deletes them. */
void f_110cd8(void)
{
    D_281eb8->f_110818();
    if (D_281eb8)
        delete D_281eb8;
    D_281eb8 = 0;
}

/* @implements 0x110d24 us f_110d24
   WHAT IT DOES: Frees voice ch's slot in the global groups. */
void f_110d24(int ch)
{
    D_281eb8->f_110820(ch);
}

/* @implements 0x110d4c us f_110d4c
   WHAT IT DOES: Stops every voice of group grp. */
void f_110d4c(int grp)
{
    D_281eb8->f_110918(grp);
}

/* @implements 0x110d74 us f_110d74
   WHAT IT DOES: Returns group grp's free slots. */
int f_110d74(int grp)
{
    return D_281eb8->f_1109cc(grp);
}

/* @implements 0x110d98 us f_110d98
   WHAT IT DOES: Returns group grp's voice limit. */
int f_110d98(int grp)
{
    return D_281eb8->f_1109ec(grp);
}

/* @implements 0x110dbc us f_110dbc
   WHAT IT DOES: Finds a slot in group grp for a sound of priority prio (0x110a04). */
int f_110dbc(int prio, int *slot, int grp)
{
    return D_281eb8->f_110a04(prio, slot, grp);
}

/* @implements 0x110df0 us f_110df0
   WHAT IT DOES: Puts voice ch into a slot of group grp (0x110c74). */
void f_110df0(int prio, int slot, int grp, int ch)
{
    D_281eb8->f_110c74(prio, slot, grp, ch);
}
}
