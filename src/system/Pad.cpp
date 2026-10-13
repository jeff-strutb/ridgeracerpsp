/* The pad reader object file (retail 0x09936c to 0x0995e0): reads the pad's buttons and
   analog stick once a frame and derives the newly pressed buttons and their key repeat
   (a first delay, then a rate) for fourteen buttons. The object file also holds the debug
   text screen object at D_24517c, whose constructor is the only static initialisation. */

extern "C" {
typedef struct SceCtrlData {
    unsigned int TimeStamp;
    unsigned int Buttons;
    unsigned char Lx;
    unsigned char Ly;
    unsigned char Rsrv[6];
} SceCtrlData;
int sceCtrlReadBufferPositive(SceCtrlData *pad_data, int count);
}

struct CPad {
    void f_09936c(int repeatDelay, int repeatRate);
    void f_0993ac(int i, unsigned int bit);
    void f_0993fc();

    unsigned int buttons;
    unsigned int prev;
    unsigned int pressed;
    unsigned int repeat;
    int repeatDelay;
    int repeatRate;
    int count[14];
    int x;
    int y;
};

/* The debug text screen's settings (only the constructor's default is known here). */
struct CDebugColor {
    CDebugColor() : v(128) {}
    int v;
};
struct CDebugText {
    int m0;
    int m4;
    int m8;
    CDebugColor m12;
};

CDebugText D_24517c;
CPad D_24518c;
SceCtrlData D_2451e4;

/* @implements 0x09936c us f_09936c
   WHAT IT DOES: Clears the pad state and sets the key repeat's first delay and rate; every
   button's repeat count starts at the delay. */
void CPad::f_09936c(int repeatDelay, int repeatRate)
{
    int i;
    this->repeatRate = repeatRate;
    buttons = 0;
    prev = 0;
    pressed = 0;
    repeat = 0;
    y = 0;
    x = 0;
    this->repeatDelay = repeatDelay;
    for (i = 0; i < 14; i++)
        count[i] = repeatDelay;
}

/* @implements 0x0993ac us f_0993ac
   WHAT IT DOES: Key repeat of one button: while held, counts down and adds the button to
   the repeat set each time the count runs out (restarting at the rate); when released,
   restarts the count at the first delay. */
void CPad::f_0993ac(int i, unsigned int bit)
{
    if (buttons & bit) {
        if (--count[i] == 0) {
            count[i] = repeatRate;
            repeat |= bit;
        }
    } else {
        count[i] = repeatDelay;
    }
}

/* @implements 0x0993fc us f_0993fc
   WHAT IT DOES: Reads the pad: keeps the previous buttons, reads the new ones and the
   stick (centred; zero while a hold or system button is down), sets the newly pressed
   buttons and runs the key repeat of the fourteen buttons. */
void CPad::f_0993fc()
{
    SceCtrlData *d = &D_2451e4;
    prev = buttons;
    sceCtrlReadBufferPositive(d, 1);
    buttons = d->Buttons;
    if (buttons & 0x30000) {
        y = 0;
        x = 0;
    } else {
        x = d->Lx - 128;
        y = d->Ly - 128;
    }
    repeat = pressed = buttons & ~prev;
    f_0993ac(0, 0x10);
    f_0993ac(1, 0x40);
    f_0993ac(2, 0x80);
    f_0993ac(3, 0x20);
    f_0993ac(4, 0x2000);
    f_0993ac(5, 0x4000);
    f_0993ac(6, 0x1000);
    f_0993ac(7, 0x8000);
    f_0993ac(8, 0x100);
    f_0993ac(9, 0x200);
    f_0993ac(10, 0x1);
    f_0993ac(11, 0x8);
    f_0993ac(12, 0x10000);
    f_0993ac(13, 0x20000);
}

/* @implements 0x099570 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the debug text screen object at startup. */
/* @implements 0x0995b4 us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x0995d4 us _ZN10CDebugTextC1Ev
   WHAT IT DOES: The compiler-generated constructor of the debug text screen object: sets
   its colour default. */
