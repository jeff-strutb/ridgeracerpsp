/* The network opponent's car (retail 0x0c19e4 to 0x0c2908, "RRP::CRidgeNetcar"). It derives
   from the computer driven car (constructed and destroyed in another object file) but is
   moved by the packets received from the other machine: most driving steps are empty, the
   boost gauge is started by the received boost level, and the received position and
   orientation are copied into the car. */

#include <string.h>

union Angle {
    float a;
};

struct Vec4 {
    float x, y, z, w;
};

extern "C" {
void f_0c078c(void *car);
void f_0c0834(void *car);
void f_0b89e8(void *car);
void f_09b070(Vec4 *out, void *m, int axis);
}

/* The computer car base (src/race/RidgeComcar.cpp). */
struct CRidgeComcarBase {
    CRidgeComcarBase() { f_0c078c(this); }
    ~CRidgeComcarBase() { f_0c0834(this); }
};

/* The car's physics record (+5792, 1888 bytes). */
struct Phys {
    char p0[1096];
    float m1096;           /* 1096: speed */
    char p1100[788];
};

namespace RRP {

class CRidgeNetcar : public CRidgeComcarBase {
public:
    CRidgeNetcar();
    virtual ~CRidgeNetcar();
    virtual void f_0c1acc();
    virtual void f_0c1ad4();
    virtual void f_0c1adc();
    virtual void f_0c1ae4();
    virtual void f_0c1aec();
    virtual void f_0c1af4();
    virtual void f_0c1afc();
    virtual void f_0c1b04();
    virtual void f_0c1b0c();
    virtual void f_0c1b28();
    virtual void v12();
    virtual void f_0c1b30();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void f_0c1e54();
    virtual void f_0c1b80();
    virtual void v21();
    virtual void f_0c1b38();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void f_0c21b0();
    virtual void f_0c24c4();
    virtual void f_0c24e8();
    virtual void f_0c2824();
    virtual void f_0c282c();
    virtual void f_0c2834();
    virtual void f_0c283c();
    virtual void f_0c2844();
    virtual void f_0c284c();
    virtual void f_0c2854();
    virtual void f_0c285c();
    virtual void f_0c2864();
    virtual void f_0c286c();
    virtual void f_0c2874();
    virtual void f_0c2898();
    virtual void f_0c28e4();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void f_0c21b8();
    virtual void f_0c23d8();
    virtual void f_0c2478();

    char p4[140];
    Vec4 m144;             /* 144: position */
    char p160[48];
    char m208[1628];       /* 208: orientation matrix */
    float m1836;           /* 1836: received boost level */
    char p1840[288];
    float m2128;           /* 2128 */
    float m2132;
    float m2136;
    char p2140[3652];
    Phys phys;             /* 5792 */
    char p7680[12];
    unsigned m7692;        /* 7692: input bits */
    char p7696[84];
    float m7780;           /* 7780 */
    char p7784[4];
    float m7788;           /* 7788 */
    char p7792[164];
    float m7956;           /* 7956 */
    char p7960[1968];
    float m9928;           /* 9928 */
    float m9932;
    float m9936;
    float m9940;
    float m9944;
    char p9948[88];
    float m10036;          /* 10036 */
    float m10040;
    int m10044;            /* boost state */
    float m10048;
    int m10052;
    float m10056;
    float m10060;
    float m10064;
    float m10068;
    char p10072[4];
    float m10076;
    char p10080[4];
    float m10084;
};

}

using namespace RRP;

/* @implements 0x0c19e4 us _ZN3RRP12CRidgeNetcarC2Ev
   WHAT IT DOES: Builds the computer car (base object constructor). */
/* @implements 0x0c1a14 us _ZN3RRP12CRidgeNetcarC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CRidgeNetcar::CRidgeNetcar()
{
}

/* @implements 0x0c1a44 us _ZN3RRP12CRidgeNetcarD2Ev
   WHAT IT DOES: Destroys the computer car (base object destructor). */
/* @implements 0x0c1a6c us _ZN3RRP12CRidgeNetcarD1Ev
   WHAT IT DOES: The same (complete object destructor). */
/* @implements 0x0c1a94 us _ZN3RRP12CRidgeNetcarD0Ev
   WHAT IT DOES: The same, then frees the car (deleting destructor). */
CRidgeNetcar::~CRidgeNetcar()
{
}

/* @implements 0x0c1acc us f_0c1acc
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1acc()
{
}

/* @implements 0x0c1ad4 us f_0c1ad4
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1ad4()
{
}

/* @implements 0x0c1adc us f_0c1adc
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1adc()
{
}

/* @implements 0x0c1ae4 us f_0c1ae4
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1ae4()
{
}

/* @implements 0x0c1aec us f_0c1aec
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1aec()
{
}

/* @implements 0x0c1af4 us f_0c1af4
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1af4()
{
}

/* @implements 0x0c1afc us f_0c1afc
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1afc()
{
}

/* @implements 0x0c1b04 us f_0c1b04
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1b04()
{
}

/* @implements 0x0c1b0c us f_0c1b0c
   WHAT IT DOES: Runs the race car's step f_0b89e8. */
void CRidgeNetcar::f_0c1b0c()
{
    f_0b89e8(this);
}

/* @implements 0x0c1b28 us f_0c1b28
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1b28()
{
}

/* @implements 0x0c1b30 us f_0c1b30
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c1b30()
{
}

/* @implements 0x0c1b38 us f_0c1b38
   WHAT IT DOES: Stores the car's position (x, z) and the heading read from its orientation
   matrix. */
void CRidgeNetcar::f_0c1b38()
{
    Vec4 r;
    f_09b070(&r, m208, 0);
    m2128 = m144.x;
    m2132 = m144.z;
    m2136 = r.y;
}

/* @draft 0x0c1b80 us f_0c1b80
   WHAT IT DOES: The network car's body step.
   DIFFERS: not yet transcribed. */
void CRidgeNetcar::f_0c1b80()
{
}

/* @draft 0x0c1e54 us f_0c1e54
   WHAT IT DOES: Builds the wheel matrices from the received state.
   DIFFERS: not yet transcribed. */
void CRidgeNetcar::f_0c1e54()
{
}

/* @implements 0x0c21b0 us f_0c21b0
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c21b0()
{
}

/* @draft 0x0c21b8 us f_0c21b8
   WHAT IT DOES: The boost gauge state machine (0 idle, 1 rising, 2 holding, 3 falling),
   started by a received boost level above 0.01 (which it consumes). Sets the speed factor,
   capped at 2.
   DIFFERS: retail keeps the physics record in a3 (reused for the constant 3) and the done
   flag in a1 (here a1 and t0), multiplies the falling factor straight into f4, and stores the
   hold time's zero floor from f4 (here sw zero). */
void CRidgeNetcar::f_0c21b8()
{
    Phys *p = &phys;
    float add = 0.0f;
    int done = 0;

    switch (m10044) {
    case 0:
        if (0.01f < m1836) {
            m10036 = m7780;
            m10044 = 1;
            m1836 = add;
            m10056 = 100.0f;
        } else {
            m10036 = 1.0f;
        }
        break;
    case 1:
        m10036 += m10076;
        if (m7788 < m10036) {
            m10036 = m7788;
            m10044 = 2;
        }
    case 2:
        m10056 -= m10060;
        if (m10056 <= add) {
            done = 1;
            m10056 = add;
        }
        break;
    case 3:
        m10036 += m10064;
        if (m10036 < 1.0f) {
            m10036 = 1.0f;
            m10044 = 0;
        }
        if (0.01f < m1836) {
            m10044 = 1;
            m1836 = add;
            m10056 = 100.0f;
        }
        break;
    }
    if (m10044 == 1 || m10044 == 2) {
        if (p->m1096 <= 55.6f)
            add = (55.6f - p->m1096) / 55.6f;
    }
    if (m10044 == 3)
        add = (m10036 - 1.0f) * m10084 * m10068;
    if (done == 1) {
        m10064 = (1.0f - m10036) * 0.008333f;
        m10052 = (m10052 + 1) % 3;
        m10044 = 3;
        m10068 = add;
    }
    m10040 = m10036 + add;
    m10040 = m10040 < 2.0f ? m10040 : 2.0f;
}

/* @implements 0x0c23d8 us f_0c23d8
   WHAT IT DOES: Runs the boost step, then scales the frame time by the boost factor (capped
   at 3), sets its reciprocal and per-second forms and the effect scale (at least 1). */
void CRidgeNetcar::f_0c23d8()
{
    f_0c21b8();
    m9928 = m9928 * m10040;
    float s = m9928 < 3.0f ? m9928 : 3.0f;
    m9928 = s;
    m9932 = 1.0f / s;
    m9936 = s * 0.016666668f;
    m9940 = 1.0f / m9936;
    m9944 = m9932 * 0.016666668f;
    if (1.0f < s)
        m7956 = s;
    else
        m7956 = 1.0f;
}

/* @implements 0x0c2478 us f_0c2478
   WHAT IT DOES: The network car's frame: time scale, the frame steps, the direction
   vector. */
void CRidgeNetcar::f_0c2478()
{
    f_0c23d8();
    f_0c21b0();
    f_0c1b38();
}

/* @implements 0x0c24c4 us f_0c24c4
   WHAT IT DOES: The time scale step. */
void CRidgeNetcar::f_0c24c4()
{
    f_0c23d8();
}

/* @draft 0x0c24e8 us f_0c24e8
   WHAT IT DOES: Applies the received state to the car.
   DIFFERS: not yet transcribed. */
void CRidgeNetcar::f_0c24e8()
{
}

/* @implements 0x0c2824 us f_0c2824
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c2824()
{
}

/* @implements 0x0c282c us f_0c282c
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c282c()
{
}

/* @implements 0x0c2834 us f_0c2834
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c2834()
{
}

/* @implements 0x0c283c us f_0c283c
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c283c()
{
}

/* @implements 0x0c2844 us f_0c2844
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c2844()
{
}

/* @implements 0x0c284c us f_0c284c
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c284c()
{
}

/* @implements 0x0c2854 us f_0c2854
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c2854()
{
}

/* @implements 0x0c285c us f_0c285c
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c285c()
{
}

/* @implements 0x0c2864 us f_0c2864
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c2864()
{
}

/* @implements 0x0c286c us f_0c286c
   WHAT IT DOES: Nothing for a network car. */
void CRidgeNetcar::f_0c286c()
{
}

/* @implements 0x0c2874 us f_0c2874
   WHAT IT DOES: The direction vector (slot 22). */
void CRidgeNetcar::f_0c2874()
{
    f_0c1b38();
}

/* @implements 0x0c2898 us f_0c2898
   WHAT IT DOES: The time scale, the state apply and an empty step (slots 39 to 41). */
void CRidgeNetcar::f_0c2898()
{
    f_0c24c4();
    f_0c24e8();
    f_0c2824();
}

/* @implements 0x0c28e4 us f_0c28e4
   WHAT IT DOES: The direction vector (slot 22). */
void CRidgeNetcar::f_0c28e4()
{
    f_0c1b38();
}

typedef char check_phys[sizeof(Phys) == 1888 ? 1 : -1];
#define OFS(m) ((unsigned)&((CRidgeNetcar *)0)->m)
typedef char check_a[OFS(phys) == 5792 && OFS(m1836) == 1836 && OFS(m2128) == 2128 && OFS(m7692) == 7692 && OFS(m7956) == 7956 && OFS(m9928) == 9928 && OFS(m10036) == 10036 && OFS(m10084) == 10084 && OFS(m208) == 208 ? 1 : -1];
