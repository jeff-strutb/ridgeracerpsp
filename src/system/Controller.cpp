/* The controller object file (retail 0x041d34 to 0x0425b0, "Controller::CController").
   A controller reads the pad each frame and keeps, for every one of its 24 inputs, whether it is
   held, newly pressed or auto-repeating, plus an analog strength (0 to 255) per input; the
   analog stick's four directions are inputs 14 to 17. */

/* The pad state read by the system each frame. */
struct PadData {
    int buttons;
    int m4;
    int pressed;
    int m12[17];
    int stickX;
    int stickY;
};
extern PadData D_24518c;
extern signed char D_240bf0;

/* Whether a button was pressed this frame. */
inline bool Pressed(int m)
{
    return D_24518c.pressed & m;
}
extern char D_240bf4[2];
extern signed char D_240bf8[];

namespace Controller {
class CController {
public:
    virtual void f_041d34(int port, unsigned char delay, unsigned char rate);
    virtual ~CController() {}
    virtual void f_041e48();
    void f_041dc4();
    void f_041de8(int i);
    void f_041f18();
    void f_042440(int mask, int i, short v);
    void f_0424a4(int mask, int i, int v, int dir, int boost);

    /* Counts an input's auto-repeat down; when it runs out the input repeats. */
    void Repeat(int mask, int i)
    {
        if (--timer[i] == 0) {
            timer[i] = rate;
            repeat |= mask;
        }
    }

    signed char port;
    signed char mode;
    int hold;
    int last;
    int trig;
    int repeat;
    short level[24];
    unsigned char timer[24];
    unsigned char delay;
    unsigned char rate;
    int m100;
};
}

using namespace Controller;

/* @implements 0x041d34 us f_041d34
   WHAT IT DOES: opens the controller on a port with an auto-repeat delay and rate: records the
   port in the port table, clears the input state and every input's level, and sets every
   input's repeat timer to the delay. */
void CController::f_041d34(int p, unsigned char d, unsigned char r)
{
    port = p;
    D_240bf8[port] = p;
    D_240bf4[0] = 0;
    D_240bf4[1] = 0;
    rate = r;
    hold = 0;
    last = 0;
    trig = 0;
    repeat = 0;
    delay = d;
    for (int i = 0; i < 24; i++) {
        level[i] = 0;
        timer[i] = delay;
    }
    mode = 3;
    D_240bf0 = -1;
    m100 = 1;
}

/* @implements 0x041dc4 us f_041dc4
   WHAT IT DOES: restarts every input's repeat timer at the delay. */
void CController::f_041dc4()
{
    for (int i = 0; i < 24; i++)
        timer[i] = delay;
}

/* @implements 0x041de8 us f_041de8
   WHAT IT DOES: restarts one input's repeat timer at the delay. */
void CController::f_041de8(int i)
{
    timer[i] = delay;
}

/* @implements 0x041df8 us f_041df8
   WHAT IT DOES: the mode a port is to be read in; always 0 (the local pad). */
signed char f_041df8(signed char port, signed char mode)
{
    return 0;
}

/* @implements 0x041e00 us f_041e00
   WHAT IT DOES: whether button 0x8 or 0x1000 was pressed this frame. */
bool f_041e00()
{
    return Pressed(8) || Pressed(0x1000);
}

/* @implements 0x041e2c us f_041e2c
   WHAT IT DOES: whether button 0x4000 was pressed this frame. */
int f_041e2c()
{
    if (D_24518c.pressed & 0x4000)
        return 1;
    return 0;
}

/* @implements 0x041e40 us f_041e40
   WHAT IT DOES: always 0. */
int f_041e40()
{
    return 0;
}

/* @implements 0x041e48 us f_041e48
   WHAT IT DOES: the per frame update: picks the read mode for the port, clears the state when
   it changes, reads the pad in mode 0 and otherwise clears the inputs and their timers. */
void CController::f_041e48()
{
    signed char old = mode;
    mode = f_041df8(D_240bf8[port], old);
    if (mode != old) {
        hold = 0;
        last = 0;
        trig = 0;
        repeat = 0;
        for (int i = 0; i < 24; i++)
            level[i] = 0;
    }
    if (mode == 0) {
        f_041f18();
    } else {
        hold = 0;
        last = 0;
        trig = 0;
        repeat = 0;
        for (int i = 0; i < 24; i++) {
            timer[i] = delay;
            level[i] = 0;
        }
    }
}

/* @implements 0x041f18 us f_041f18
   WHAT IT DOES: reads the pad: maps the held and the pressed buttons to the controller's input
   bits, then updates every input's level and repeat, the stick's four directions from its
   doubled axes, and adds the newly pressed inputs to the repeating ones. */
void CController::f_041f18()
{
    PadData *pad = &D_24518c;
    int axis[2];
    int b = pad->buttons;
    int p = pad->pressed;
    axis[0] = pad->stickX * 2;
    axis[1] = pad->stickY * 2;
    last = hold;
    hold = 0;
    trig = 0;
    repeat = 0;
    if (b & 0x10)
        hold |= 4;
    if (b & 0x40)
        hold |= 0x10;
    if (b & 0x80)
        hold |= 0x20;
    if (b & 0x20)
        hold |= 0x8;
    if (b & 0x8)
        hold |= 0x2;
    if (b & 0x1)
        hold |= 0x1;
    if (b & 0x4000)
        hold |= 0x1000;
    if (b & 0x2000)
        hold |= 0x800;
    if (b & 0x8000)
        hold |= 0x2000;
    if (b & 0x1000)
        hold |= 0x400;
    if (b & 0x100)
        hold |= 0x100;
    if (b & 0x200)
        hold |= 0x200;
    if (b & 0x10000)
        hold |= 0x400000;
    if (b & 0x20000)
        hold |= 0x800000;
    if (p & 0x10)
        trig |= 4;
    if (p & 0x40)
        trig |= 0x10;
    if (p & 0x80)
        trig |= 0x20;
    if (p & 0x20)
        trig |= 0x8;
    if (p & 0x8)
        trig |= 0x2;
    if (p & 0x1)
        trig |= 0x1;
    if (p & 0x4000)
        trig |= 0x1000;
    if (p & 0x2000)
        trig |= 0x800;
    if (p & 0x8000)
        trig |= 0x2000;
    if (p & 0x1000)
        trig |= 0x400;
    if (p & 0x100)
        trig |= 0x100;
    if (p & 0x200)
        trig |= 0x200;
    if (p & 0x10000)
        trig |= 0x400000;
    if (p & 0x20000)
        trig |= 0x800000;
    f_042440(1, 0, 0);
    f_042440(2, 1, 0);
    f_042440(4, 2, 0);
    f_042440(8, 3, 0);
    f_042440(0x10, 4, 0);
    f_042440(0x20, 5, 0);
    f_042440(0x40, 6, 0);
    f_042440(0x80, 7, 0);
    f_042440(0x100, 8, 0);
    f_042440(0x200, 9, 0);
    f_042440(0x400, 10, 0);
    f_042440(0x800, 11, 0);
    f_042440(0x1000, 12, 0);
    f_042440(0x2000, 13, 0);
    f_0424a4(0x4000, 14, axis[0], -1, 0);
    f_0424a4(0x8000, 15, axis[0], 1, 0);
    f_0424a4(0x10000, 16, axis[1], -1, 0);
    f_0424a4(0x20000, 17, axis[1], 1, 0);
    f_042440(0x40000, 18, 0);
    f_042440(0x80000, 19, 0);
    f_042440(0x100000, 20, 0);
    f_042440(0x200000, 21, 0);
    f_042440(0x400000, 22, 0);
    f_042440(0x800000, 23, 0);
    repeat |= trig;
}

/* @implements 0x042438 us f_042438
   WHAT IT DOES: always 1. */
int f_042438()
{
    return 1;
}

/* @implements 0x042440 us f_042440
   WHAT IT DOES: updates a digital input: stores its level and, while it is held, counts its
   repeat down; when it is released its repeat timer restarts at the delay. */
void CController::f_042440(int mask, int i, short v)
{
    level[i] = v;
    if (hold & mask)
        Repeat(mask, i);
    else
        timer[i] = delay;
}

/* @draft 0x0424a4 us f_0424a4
   WHAT IT DOES: updates an analog input from an axis value in the given direction: values the
   other way give level 0; past the dead zone (128) the value is boosted and clamped to 255,
   the input counts as held (and pressed if it was not held last frame) and repeats.
   Remaining difference: retail stores the level before the 128 test (the test result reuses
   the address register v0) and fills that branch's slot from the timer reset (bnezl); here
   the test is hoisted above the store into v1 and the store fills the slot. */
void CController::f_0424a4(int mask, int i, int v, int dir, int boost)
{
    if (v >= 0) {
        if (dir < 0) {
            level[i] = 0;
            return;
        }
    } else {
        if (dir >= 0) {
            level[i] = 0;
            return;
        }
        v = -v;
    }
    if (boost != 0 && v > 128)
        v += boost;
    if (v >= 256)
        v = 255;
    level[i] = v;
    if (v > 128) {
        hold |= mask;
        if (!(last & mask))
            trig |= mask;
        Repeat(mask, i);
    } else
        timer[i] = delay;
}

/* @implements 0x042578 us _ZN10Controller11CControllerD1Ev
   WHAT IT DOES: the destructor (nothing to release). */

/* @implements 0x042588 us _ZN10Controller11CControllerD0Ev
   WHAT IT DOES: the deleting destructor. */
