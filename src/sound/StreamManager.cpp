/* The stream manager object files (retail 0x095c1c to 0x095cb8 and 0x095f84 to 0x0961e0): the
   stream library's state (Stream::CStreamState), started with the stream loop callback, and
   the manager that creates and deletes the state and the stream data (one global object).
   The manager also prints the background music's disc and track for debugging. */

void f_093f90(const char *fmt, ...);
void f_095660(int ch);
void f_0956a8();

extern "C" {
int f_110e54(int);
void f_1114f0(int, int, int, int);
void f_111554(void);
void f_111b04(void *work, int n);
int f_1112a8(void (*callback)(int), int);
void f_02db68(void *screen, int x, int y, int z, int color, const char *fmt, ...);
}

/* The stream library's set up values. */
struct StreamConfig {
    int m0;
    int m4;
    int m8;
};
extern const StreamConfig D_1a9780 = { 0x20000, 0, 1 };

/* The background music player (its own object file). */
class CBgm {
public:
    int f_09662c();
    int f_09664c();
    void f_0969ac();
    void f_09694c();
};
extern CBgm D_242cb0;
extern char D_24517c[];

namespace Stream {

class CStreamState {
public:
    CStreamState();
    int f_095c34();
    void f_095cb0();

    int m0;
    char m4[264];
};

/* The stream data (StreamData.cpp). */
class CStreamData {
public:
    CStreamData();
    ~CStreamData();
    void *m0;
    void *m4;
};

/* @implements 0x095c1c us _ZN6Stream12CStreamStateC2Ev
   WHAT IT DOES: Makes the state, marked ready (base object constructor). */
/* @implements 0x095c28 us _ZN6Stream12CStreamStateC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CStreamState::CStreamState()
{
    m0 = 1;
}

/* @implements 0x095c34 us f_095c34
   WHAT IT DOES: Starts the sound library's streaming: its set up values, its work area,
   cleared loop counters and the loop callback. Returns 0. */
int CStreamState::f_095c34()
{
    f_110e54(1);
    f_1114f0(0, D_1a9780.m0, D_1a9780.m4, D_1a9780.m8);
    f_111554();
    f_111b04(m4, 1);
    f_0956a8();
    f_1112a8(f_095660, 0);
    m0 = 1;
    return 0;
}

/* @implements 0x095cb0 us f_095cb0
   WHAT IT DOES: Nothing. */
void CStreamState::f_095cb0()
{
}

}

using Stream::CStreamState;
using Stream::CStreamData;

CStreamData *D_242ca0;
CStreamState *D_242ca4;

class CStreamManager {
public:
    CStreamManager();
    ~CStreamManager() {}
    int f_095f9c();
    void f_096048();
    void f_0960cc();

    CStreamState *m0;
    CStreamData *m4;
};

/* @implements 0x095f84 us _ZN14CStreamManagerC2Ev
   WHAT IT DOES: Makes the manager with nothing created (base object constructor). */
/* @implements 0x095f90 us _ZN14CStreamManagerC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CStreamManager::CStreamManager()
{
    m4 = 0;
    m0 = 0;
}

/* @draft 0x095f9c us f_095f9c
   WHAT IT DOES: Creates the stream state and the stream data and marks the state ready.
   Returns 1.
   Remaining difference: retail keeps each global's full address in s1 (built before the new)
   and both new results in s0, and shares one li 1 for the store and the result; here the
   first global is stored through its %lo, the objects use other saved registers and the 1
   is loaded twice. */
int CStreamManager::f_095f9c()
{
    D_242ca4 = new CStreamState;
    D_242ca0 = new CStreamData;
    m0 = D_242ca4;
    m4 = D_242ca0;
    return m0->m0 = 1;
}

/* @implements 0x096048 us f_096048
   WHAT IT DOES: Prints the background music's disc and track, then updates the player. */
void CStreamManager::f_096048()
{
    int disc = D_242cb0.f_09662c();
    int track = D_242cb0.f_09664c();
    f_02db68(D_24517c, 8192, 2, 20, 0xffffff, "BGM: DISC[%d] TRACK[%d]", disc, track + 1);
    D_242cb0.f_0969ac();
    D_242cb0.f_09694c();
}

/* @implements 0x0960cc us f_0960cc
   WHAT IT DOES: Deletes the stream data and the stream state and clears the manager. */
void CStreamManager::f_0960cc()
{
    delete D_242ca0;
    if (D_242ca4)
        delete D_242ca4;
    D_242ca4 = 0;
    D_242ca0 = 0;
    m0 = 0;
    m4 = 0;
}

/* The stream manager the game uses. */
CStreamManager D_242ca8;

/* @implements 0x09615c us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global stream manager at startup (its destructor does
   nothing). */
/* @implements 0x0961a0 us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x0961c0 us _GLOBAL__D_
   WHAT IT DOES: Shutdown entry of the object file's static data. */
