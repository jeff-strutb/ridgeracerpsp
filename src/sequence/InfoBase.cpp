/* The race information object file (retail 0x038780 to 0x038bd0, "CInfoBase::CreateInfo").
   It owns the one race information record shared by the sequences: creating it (with its
   large work block), clearing it between races, and taking it down. Also here: the race
   result record's clear, the information base class and the copy of the player car's state
   into the record. */

extern "C" {
void f_00d354(void *log, int level, const char *fmt, ...);
}
extern char D_245178[];

/* Two words of which only the first is set when made (the other keeps whatever was there).
   The two record fields of this shape have distinct types: retail resets them through two
   separate stack temporaries. */
struct InfoPair {
    int a;
    int b;
    InfoPair() : a(0) {}
};
struct InfoPair2 {
    int a;
    int b;
    InfoPair2() : a(0) {}
};

/* The player car as the record reads it. */
struct InfoCar {
    char m0[192];
    float m192;
    char m196[1612];
    float m1808;
    float m1812;
    int m1816;
    float m1820;
    int m1824;
    int m1828;
    float m1832;
    float m1836;
    float m1840;
    float m1844;
    char m1848[296];
    float m2144;
    float m2148;
};

/* The player car's state as recorded. */
struct InfoCarState {
    int m0[11];
    float m44;
    float m48;
    float m52;
    float m56;
    int m60[2];
    int m68;
    float m72;
    float m76;
    float m80;
    float m84;
    float m88;
    float m92;
    int m96;
    InfoCar *car;
};

/* The race information record (224 bytes). */
struct RaceInfo {
    InfoPair m0;
    InfoPair2 m8;
    float m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    float m44;
    int m48;
    int m52;
    int m56;
    int m60;
    int m64[8];
    InfoCarState m96;
    int *m200;
    int m204;
    int m208;
    int m212;
    int m216;
    int m220;
};

/* The race result record (240 bytes). Its base has a constructor that does nothing, so the
   compiler supplies the record's own, which the startup code calls. */
struct RaceResultInit {
    RaceResultInit() {}
};
struct RaceResult : RaceResultInit {
    int m[60];
};

extern RaceInfo *D_2408f0;
extern RaceInfo *D_2407fc;
extern int D_27ecd8;

namespace RacePSP {
class CInfoBase {
public:
    CInfoBase();
    virtual ~CInfoBase();
    virtual int f_038a54();
    virtual void f_038a5c();
    virtual void f_038a64();
    void f_038a6c();
    virtual void f_038a78();
    int f_038af4();

    int m4[4];
    unsigned int m20;
};
}

void f_0388b4();
void f_0388d8();
void f_038828();

/* @implements 0x038780 us f_038780
   WHAT IT DOES: Creates the race information record and its work block, both cleared. If one
   already exists it is taken down first and a warning is logged. */
void f_038780()
{
    if (D_2408f0 == 0) {
        D_2407fc = D_2408f0 = (RaceInfo *)operator new(224);
    } else {
        f_038828();
        D_2407fc = D_2408f0 = (RaceInfo *)operator new(224);
        f_00d354(D_245178, 16, "Warning(%s): %s\n", "CInfoBase::CreateInfo", "already create,now re-create");
    }
    f_0388b4();
    D_2408f0->m200 = (int *)operator new(18044);
    f_0388d8();
}

/* @implements 0x038828 us f_038828
   WHAT IT DOES: Takes down the race information record and its work block; logs a warning
   when there is none. */
void f_038828()
{
    if (D_2408f0 == 0) {
        f_00d354(D_245178, 16, "Warning(%s): %s\n", "CInfoBase::DeleteInfo", "no exist");
        return;
    }
    if (D_2408f0->m200)
        operator delete(D_2408f0->m200);
    operator delete(D_2408f0);
    D_2408f0 = 0;
    D_2407fc = 0;
}

/* @implements 0x0388b4 us f_0388b4
   WHAT IT DOES: Clears the whole race information record. */
void f_0388b4()
{
    int *p = (int *)D_2408f0;
    int i;

    for (i = 0; i < 56; i++)
        *p++ = 0;
}

/* @implements 0x0388d8 us f_0388d8
   WHAT IT DOES: Clears the record's work block. */
void f_0388d8()
{
    int *p = D_2408f0->m200;
    int i;

    for (i = 0; i < 4511; i++)
        *p++ = 0;
}

/* @implements 0x038900 us f_038900
   WHAT IT DOES: Resets the race information record for a new race: the counters and flags,
   the player car's recorded state and the work block. */
void f_038900()
{
    int i;

    if (D_2408f0 == 0)
        return;
    D_2408f0->m0 = InfoPair();
    D_2408f0->m8 = InfoPair2();
    D_2408f0->m16 = 0.0f;
    D_2408f0->m20 = 0;
    D_2408f0->m24 = 0;
    D_2408f0->m28 = 0;
    D_2408f0->m32 = 0;
    D_2408f0->m36 = 0;
    D_2408f0->m44 = 0.0f;
    D_2408f0->m48 = 0;
    D_2408f0->m52 = 0;
    D_2408f0->m56 = 0;
    D_2408f0->m60 = 0;
    {
        int *q = (int *)&D_2408f0->m96;
        for (i = 0; i < 26; i++)
            *q++ = 0;
    }
    if (D_2408f0->m200)
        f_0388d8();
    D_2408f0->m204 = 0;
    D_2408f0->m208 = 0;
    D_2408f0->m212 = 0;
    D_2408f0->m216 = 0;
    D_2408f0->m220 = 0;
}

RaceResult D_240800;

/* @implements 0x0389c0 us f_0389c0
   WHAT IT DOES: Clears the race result record. */
void f_0389c0()
{
    int *p = D_240800.m;
    int i;

    for (i = 0; i < 60; i++)
        *p++ = 0;
}

/* @implements 0x0389e4 us _ZN7RacePSP9CInfoBaseC2Ev
   WHAT IT DOES: Makes the information base: no random seed yet. */
RacePSP::CInfoBase::CInfoBase()
{
    m20 = 0;
}

/* @implements 0x0389f8 us _ZN7RacePSP9CInfoBaseC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x038a0c us _ZN7RacePSP9CInfoBaseD2Ev
   WHAT IT DOES: Takes down the information base (nothing to free). */
RacePSP::CInfoBase::~CInfoBase()
{
}

/* @implements 0x038a1c us _ZN7RacePSP9CInfoBaseD1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x038a2c us _ZN7RacePSP9CInfoBaseD0Ev
   WHAT IT DOES: The same, then frees the object. */

/* @implements 0x038a54 us f_038a54
   WHAT IT DOES: Default answer of the information hook: yes. */
int RacePSP::CInfoBase::f_038a54()
{
    return 1;
}

/* @implements 0x038a5c us f_038a5c
   WHAT IT DOES: Default information hook: nothing. */
void RacePSP::CInfoBase::f_038a5c()
{
}

/* @implements 0x038a64 us f_038a64
   WHAT IT DOES: Default information hook: nothing. */
void RacePSP::CInfoBase::f_038a64()
{
}

/* @implements 0x038a6c us f_038a6c
   WHAT IT DOES: Clears a race flag. */
void RacePSP::CInfoBase::f_038a6c()
{
    D_27ecd8 = 0;
}

/* @implements 0x038a78 us f_038a78
   WHAT IT DOES: Default information hook: nothing. */
void RacePSP::CInfoBase::f_038a78()
{
}

/* @implements 0x038a80 us f_038a80
   WHAT IT DOES: Copies the player car's position, speed and orientation into the record. */
void f_038a80()
{
    InfoCarState *s = &D_2408f0->m96;
    InfoCar *c = s->car;

    s->m44 = c->m192;
    s->m68 = c->m1816;
    s->m48 = c->m2144;
    s->m52 = c->m2148;
    s->m96 = c->m1828;
    s->m56 = c->m1820;
    s->m72 = c->m1808;
    s->m76 = c->m1812;
    s->m80 = c->m1832;
    s->m84 = c->m1836;
    s->m88 = c->m1840;
    s->m92 = c->m1844;
}

/* @implements 0x038af4 us f_038af4
   WHAT IT DOES: Steps the random seed and returns a random time from 9000 to 15000 in
   steps of 300. */
int RacePSP::CInfoBase::f_038af4()
{
    m20 = m20 * 0x19660d + 0x3c6ef35f;
    return (m20 >> 4) % 21 * 300 + 9000;
}

/* @implements 0x038b64 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the race result record. */

/* @implements 0x038ba8 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x038bc8 us RaceResultC1Ev
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The race result record's constructor as the startup code calls it. */
