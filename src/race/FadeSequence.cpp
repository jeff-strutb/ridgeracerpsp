/* A screen fade sequence object file (retail 0x0ff778 to 0x0ffb1c), with one static object
   (D_27f100). Its step drives the screen fade colours of ScreenFade.cpp by state: a timed
   fade in from black, a fixed tint, a tint scaled by a level, or (state 0) a slow fade of
   the picture through two other passes. */

extern "C" {
int f_0e9e58(int a);
void f_0e9eb4(void);
int f_0e9ebc(int b);
int f_0e9f0c(int b);
void f_0ea894(void);
void f_0ffb1c(void);
void f_0ffc40(void);
int f_0ffc48(int a, int b);
void f_100390(void);
void f_100ba4(void);
void f_100bbc(void);
int f_100bc4(int b);
void f_100ef0(void);
}

extern int D_1d5e08;            /* use the second pass */
extern unsigned char D_1d5a88[]; /* the picture fade is on */
extern int D_1d5e20;            /* fade colours (ScreenFade.cpp) */
extern int D_27f150;
extern int D_27f154;
extern int D_27f158;

class CFadeSequence {
public:
    CFadeSequence();
    ~CFadeSequence();
    void f_0ff798();
    void f_0ff7f0();
    int f_0ff81c(int a, int b);
    void f_0ffa44();

    int m0;             /* frames in the state */
    int m4;             /* state */
    int m8;             /* state of the last step */
    float m12;          /* picture fade level */
    float m16;          /* tint level */
    signed char m20;    /* the fade in has finished */
};

/* @implements 0x0ff778 us _ZN13CFadeSequenceC2Ev
   WHAT IT DOES: Nothing (base object constructor). */
/* @implements 0x0ff780 us _ZN13CFadeSequenceC1Ev
   WHAT IT DOES: Nothing (complete object constructor). */
CFadeSequence::CFadeSequence()
{
}

/* @implements 0x0ff788 us _ZN13CFadeSequenceD2Ev
   WHAT IT DOES: Nothing (base object destructor). */
/* @implements 0x0ff790 us _ZN13CFadeSequenceD1Ev
   WHAT IT DOES: Nothing (complete object destructor). */
CFadeSequence::~CFadeSequence()
{
}

/* @implements 0x0ff798 us f_0ff798
   WHAT IT DOES: Sets up the passes and clears the sequence (picture fade level 1). */
void CFadeSequence::f_0ff798()
{
    f_0e9e58(1);
    f_0ffb1c();
    f_100ba4();
    m4 = 0;
    m8 = 0;
    m12 = 1.0f;
    m16 = 0;
    m20 = 0;
    m0 = 0;
}

/* @implements 0x0ff7f0 us f_0ff7f0
   WHAT IT DOES: Releases the passes. */
void CFadeSequence::f_0ff7f0()
{
    f_100bbc();
    f_0e9eb4();
    f_0ffc40();
}

/* @draft 0x0ff81c us f_0ff81c
   REMAINING DIFFERENCE: retail tests the states in order 0, 1, 2, 3 and places the bodies in
   the order fade step, 3, 2, 1, 0; this switch dispatches as a tree and keeps case 0 early.
   WHAT IT DOES: The per frame step: sets the fade colours for the state (state 1 fades in
   from black over 30 frames, state 2 holds the tint, state 3 scales it by the tint level)
   and runs the fade pass; state 0 instead runs the picture fade passes while that fade is
   on. Returns what the passes hand back. */
int CFadeSequence::f_0ff81c(int a, int b)
{
    if (D_1d5e08)
        b = f_0ffc48(a, b);
    int st = m4;
    if (st != m8) {
        if (st == 1) {
            m12 = 0;
            m20 = 0;
            m0 = 0;
        }
    }
    switch (st) {
    case 0:
        if (!D_1d5a88[0])
            return b;
        if (m12 < 1.0f) {
            b = f_0e9ebc(b);
            m12 += 0.0033333334f;
        } else {
            b = f_0e9f0c(b);
        }
        return b;
    case 1:
        if (!m20) {
            if (m0 >= 30)
                m20 = 1;
            float t = (float)m0 / 30.0f;
            D_1d5e20 = 7;
            D_27f158 = 37;
            float u = 1.0f - t;
            D_27f154 = (int)(u * 110.0f + t * 0.0f);
            D_27f150 = (int)(u * 145.0f + t * 150.0f);
            break;
        }
    case 2:
        D_27f150 = 150;
        D_1d5e20 = 7;
        D_27f158 = 37;
        D_27f154 = 0;
        break;
    case 3:
        D_27f154 = (int)(m16 * 0.0f);
        D_1d5e20 = (int)(m16 * 7.0f);
        D_27f150 = (int)(m16 * 150.0f);
        D_27f158 = 37;
        break;
    }
    b = f_100bc4(b);
    m0++;
    return b;
}

/* @implements 0x0ffa44 us f_0ffa44
   WHAT IT DOES: Runs the three passes' per frame updates. */
void CFadeSequence::f_0ffa44()
{
    f_0ea894();
    f_100390();
    f_100ef0();
}

CFadeSequence D_27f100;

/* @implements 0x0ffa70 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the sequence object at startup and destructs it at shutdown. */

/* @implements 0x0ffadc us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0ffafc us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */
