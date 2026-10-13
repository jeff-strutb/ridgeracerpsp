/* The standard sequence states object file (retail 0x039de0 to 0x03a2fc). The race states the
   standard sequences share through their state tables: the race itself, the countdown and the
   replay. Each frame they update the race information, the cars, the race sound, the music and
   the cameras, skip what a paused game must not run, and move to the next state when the
   information says so. */

extern "C" {
void f_03e354(void);
void f_07ea64(void *);
int f_07e73c(void *);
void f_0ea8b4(int a, void *v0, void *v1, int n);
void f_094290(void *);
void f_0940e8(void *);
void f_0942b4(void *);
void f_096048(void *);
void f_08d484(void *);
void f_08d644(void *);
void f_03a70c(void *);
int f_03b518(void *ctrl, int i);
void f_0eba3c(int a, void *v0, void *v1, void *ctrl, int car);
void f_0ec1cc(void);
void f_089500(void *snd, int ms);
}
extern char D_242c90[];
extern char D_242ca8[];

/* The main loop's pause flags. */
struct MainLoopJobView {
    char m0[11];
    bool m11;
    bool m12;
    unsigned char m13;
    bool m14;
    bool Paused() { return m11 || m12; }
};
extern MainLoopJobView *D_1d88a0;

/* The race sound. */
struct CRaceSound {
    char m0[548];
    float m548;
    void f_01d4b8(int n);
};
extern CRaceSound D_23be80;

/* The sound system. */
class CSound {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2(int a, int b);
    virtual void v3(int a);
    virtual void v4();
    virtual void v5();
};
extern CSound *D_1d3d40;

/* The race information. */
class CInfo {
public:
    virtual ~CInfo();
    virtual int f_038a54();
    virtual void f_038a5c();
    virtual void f_038a64();
    virtual void f_038a78();
    char m4[44];
    int m48;
    char m52[20];
    int m72;
    int m76;
};

/* One view of the race. */
struct View {
    char m0[664];
    int m664;
    char m668[84];
};

namespace RacePSP {
class CSequenceBase {
public:
    virtual ~CSequenceBase();
    void f_0395b4();
    void f_039608();
    char *m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    void *m32;
    View *m36;
    CInfo *m40;
    int m44;
    void *m48;
    void *m52;
    int state;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
};

class CSequenceStandard : public CSequenceBase {
public:
    virtual ~CSequenceStandard() {}
    int f_039de0();
    int f_03a06c();
    int f_03a19c();
    void Cameras()
    {
        if (!D_1d88a0->m14 && state) {
            f_0eba3c(0, m36, &m36[1], m32, f_03b518(m32, 0));
            f_0ec1cc();
        }
    }
};
}

using namespace RacePSP;

/* @implements 0x039de0 us f_039de0
   WHAT IT DOES: The race state: sends the second race message (outside replays), updates the
   race information, the cars and the cameras unless paused, takes the race information's
   result, fades the sound once at the race's end, updates the music, the race sound and the
   cars, and goes idle with the result when there is one; then updates the race cameras. */
int CSequenceStandard::f_039de0()
{
    int r = 0;

    if (m20 != 2)
        f_039608();
    m40->m76 = 0;
    m36[0].m664 = 0;
    m36[1].m664 = 0;
    if (!D_1d88a0->Paused() && m40->m72 == 0)
        m40->f_038a78();
    if (!D_1d88a0->Paused() && m40->m72 == 0)
        f_03a70c(m32);
    if (!D_1d88a0->Paused())
        r = m40->f_038a54();
    f_03e354();
    if (m40->m72 < 2)
        f_07ea64(m52);
    if (!D_1d88a0->Paused())
        f_0ea8b4(0, m36, &m36[1], m40->m72);
    {
        int end = m40->m48;
        m40->m48 = 0;
        if (end) {
            f_089500(D_1d3d40, 3000);
            D_23be80.m548 = 0.99f;
        }
    }
    if (D_1d88a0->Paused())
        f_094290(D_242c90);
    else
        f_0940e8(D_242c90);
    f_096048(D_242ca8);
    D_23be80.f_01d4b8(m40->m72);
    if (!D_1d88a0->Paused())
        m40->f_038a5c();
    f_08d484(m48);
    if (r) {
        m68 = r;
        state = 0;
    }
    Cameras();
    return 0;
}

/* @implements 0x03a06c us f_03a06c
   WHAT IT DOES: The countdown state: sends the first race message, updates the cars and the
   countdown, the views' cameras, the music and the start lights, and steps to the next state
   when the countdown says so (starting the race music when it is over); then updates the race
   cameras. */
int CSequenceStandard::f_03a06c()
{
    f_0395b4();
    m36[0].m664 = 0;
    m36[1].m664 = 0;
    f_03e354();
    int step = f_07e73c(m52);
    f_0ea8b4(0, m36, &m36[1], 0);
    if (D_1d88a0->Paused())
        f_094290(D_242c90);
    else
        f_0940e8(D_242c90);
    f_096048(D_242ca8);
    f_08d644(m48);
    if (step) {
        state++;
        if (step == 2)
            f_0942b4(D_242c90);
    }
    Cameras();
    return 0;
}

/* @implements 0x03a19c us f_03a19c
   WHAT IT DOES: The replay state: updates the race information (whose answer ends the replay),
   the cars, the replay, the cameras, the music and the race sound, and the information's view
   unless paused; at the end goes idle, otherwise clears the result and steps on; then updates
   the race cameras. */
int CSequenceStandard::f_03a19c()
{
    m36[0].m664 = 0;
    m36[1].m664 = 0;
    int done = m40->f_038a54();
    f_03e354();
    f_07ea64(m52);
    f_0ea8b4(0, m36, &m36[1], 0);
    if (D_1d88a0->Paused())
        f_094290(D_242c90);
    else
        f_0940e8(D_242c90);
    f_096048(D_242ca8);
    D_23be80.f_01d4b8(0);
    if (!D_1d88a0->Paused())
        m40->f_038a5c();
    if (done)
        state = 0;
    else {
        m68 = 0;
        state++;
    }
    Cameras();
    return 0;
}
