/* The custom pad controller (retail 0x0425b0 to 0x043f7c): the pad with a configurable button
   layout. The base CController (0x041d34 to 0x0425b0) keeps the buttons held, newly pressed
   and repeating as masks, plus an analog level per button. The layout is a table per mode
   (D_1d5d70) of seven actions; each action offers a few assignments, each naming its kind and
   up to three button numbers (the button number to mask table is D_1d1ca4). The controller
   keeps the chosen assignment of every action (row 0 of sel) and a pending choice being edited
   (row 1), and reads every action through its chosen assignment. */

/* One assignment of an action: its kind (low four bits; under 2 a plain button mask follows,
   otherwise button numbers) and the buttons. */
struct Assign {
    unsigned int kind;
    int b0;
    int b1;
    int b2;
};

/* One action of a layout: how many assignments it offers, and the assignments. */
struct Action {
    int count;
    Assign *assign;
};

extern signed char D_240bf8[];
extern Action *D_1d5d70[];
extern int D_1d1ca4[];

namespace Controller {
class CController {
public:
    virtual void f_041d34(int port, unsigned char a, unsigned char b);
    virtual ~CController() {}
    virtual void f_041e48();

    int Mode() { return D_240bf8[m4] != -1 ? m5 : 3; }

    signed char m4;
    signed char m5;
    int held;
    int m12;
    int trig;
    int repeat;
    unsigned short level[24];
    unsigned char m72[24];
    unsigned char m96;
    unsigned char m97;
    int m100;
};

class CCustomController : public CController {
public:
    virtual void f_041d34(int port, unsigned char a, unsigned char b);
    int f_042640(int i);
    int f_042698(int i);
    void f_0426c0();
    void f_042730();
    void f_0427a0();
    int f_042888(int i);
    void f_0428c0(int mode, int i, int v);
    int f_042924(int i, int v);
    int f_0429c4(unsigned char *out);
    void f_042e1c(int v);
    int f_042ed4();
    int f_042ef0();
    int f_042f18();
    int f_042f40();
    int f_042f90();
    int f_042fe0();
    int f_043030();
    int f_043058();
    int f_043080();
    int f_0430a8();
    int f_0430d0();
    int f_04311c();
    int f_04316c();
    int f_0431bc();
    int f_0431e4();
    int f_04320c();
    int f_04325c();
    int f_0432ac();
    int f_0432f8();
    void f_0433ec(int *x, int *y);
    int f_043498();
    int f_0434f0();
    int f_043548(int neg, int pos);
    int f_04356c(int i);
    int f_04361c(int i);
    int f_0436ac(int neg, int pos);
    int f_0436d0(int i);
    int f_0437cc(int i);
    int f_04385c(int neg, int pos);
    int f_043880(int i);
    int f_04397c(int i);
    int f_043a0c(int i);
    unsigned int f_043aa0(int i);
    int f_043b2c(int i);
    int f_043b6c(int i);
    int f_043bd0(int i);
    int f_043c34(int i);
    void f_043c98(unsigned char (*buf)[7]);
    void f_043ce0(unsigned char (*buf)[7]);
    void f_043d2c();
    void f_043dd8();
    int f_043e84();
    int f_043eb8();
    void f_043eec();
    int f_043ef4();
    int f_043efc();
    int f_043f04();
    int f_043f0c();
    int f_043f14();
    int f_043f1c();
    int f_043f24();
    int f_043f2c();
    int f_043f34();
    int f_043f3c();

    int Held(int mask) { return held & mask; }
    int Trig(int mask) { return trig & mask; }
    int Repeat(int mask) { return repeat & mask; }

    unsigned char sel[1][7];
    unsigned char tmp[7];
};
}

using namespace Controller;

static inline int Mask(int b)
{
    if ((unsigned int)b < 24)
        return D_1d1ca4[b];
    return -1;
}

/* @implements 0x0425b0 us CCustomController8f_041d34
   WHAT IT DOES: Sets the pad up through the base class, then clears the chosen and the pending
   assignment of every action. */
void CCustomController::f_041d34(int port, unsigned char a, unsigned char b)
{
    CController::f_041d34(port, a, b);
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < 7; j++)
            sel[i][j] = 0;
    for (int j = 0; j < 7; j++)
        tmp[j] = 0;
    sel[0][0] = 0;
    sel[0][1] = 0;
    sel[0][2] = 0;
    sel[0][3] = 0;
    sel[0][4] = 0;
    sel[0][5] = 0;
    sel[0][6] = 0;
}

/* @implements 0x042640 us f_042640
   WHAT IT DOES: Steps action i's pending assignment to the next one. Returns 1 when it is
   already the last. */
int CCustomController::f_042640(int i)
{
    if (tmp[i] < f_043b2c(i) - 1) {
        tmp[i]++;
        return 0;
    }
    return 1;
}

/* @implements 0x042698 us f_042698
   WHAT IT DOES: Steps action i's pending assignment to the previous one. Returns 1 when it is
   already the first. */
int CCustomController::f_042698(int i)
{
    if (tmp[i] == 0)
        return 1;
    tmp[i]--;
    return 0;
}

/* @implements 0x0426c0 us f_0426c0
   WHAT IT DOES: Copies the chosen assignments into the pending ones (when the pad has a
   layout). */
void CCustomController::f_0426c0()
{
    if (Mode() > 0)
        return;
    for (int j = 0; j < 7; j++)
        tmp[j] = sel[m5][j];
}

/* @implements 0x042730 us f_042730
   WHAT IT DOES: Makes the pending assignments the chosen ones. */
void CCustomController::f_042730()
{
    if (Mode() > 0)
        return;
    for (int j = 0; j < 7; j++)
        sel[m5][j] = tmp[j];
}

/* @implements 0x0427a0 us f_0427a0
   WHAT IT DOES: Clears the pending assignments, then (in mode 0) sets each action's pending
   assignment to the first. */
void CCustomController::f_0427a0()
{
    for (int j = 0; j < 7; j++)
        tmp[j] = 0;
    if (Mode() != 0)
        return;
    f_042924(0, 0);
    f_042924(1, 0);
    f_042924(2, 0);
    f_042924(3, 0);
    f_042924(4, 0);
    f_042924(5, 0);
    f_042924(6, 0);
    f_042924(6, 0);
}

/* @implements 0x042888 us f_042888
   WHAT IT DOES: Returns the chosen assignment of action i (-1 for no such action). */
int CCustomController::f_042888(int i)
{
    if (m5 > 0)
        return 0;
    if ((unsigned int)i < 7)
        return sel[m5][i];
    return -1;
}

/* @implements 0x0428c0 us f_0428c0
   WHAT IT DOES: Chooses assignment v for action i of the given mode's layout, if the action
   offers it. */
void CCustomController::f_0428c0(int mode, int i, int v)
{
    if (mode > 0)
        return;
    if ((unsigned int)i < 8) {
        if (v < D_1d5d70[mode][i].count && v >= 0)
            sel[mode][i] = v;
    }
}

/* @implements 0x042924 us f_042924
   WHAT IT DOES: Sets action i's pending assignment to v if the action offers it. Returns 0 when
   set, 1 otherwise. */
int CCustomController::f_042924(int i, int v)
{
    if (Mode() > 0)
        return 1;
    if ((unsigned int)i >= 8)
        return 1;
    if (v >= f_043b2c(i))
        return 1;
    if (v < 0)
        return 1;
    tmp[i] = v;
    return 0;
}

/* @implements 0x0429c4 us f_0429c4
   WHAT IT DOES: Counts the button clashes of the pending layout: for every pair of actions it
   compares their buttons (as masks for the kinds that use button numbers), counts each clash
   for both actions in out[] and returns the total. The chosen layout is left as it was, with
   the pending one applied. */
int CCustomController::f_0429c4(unsigned char *out)
{
    unsigned char save[1][7];
    int n;
    int i;

    if (Mode() > 0)
        return 0;
    f_043ce0(save);
    f_042730();
    n = 0;
    for (int j = 0; j < 7; j++)
        out[j] = 0;
    for (i = 0; i < 7; i++) {
        int a = f_043b6c(i);
        int b = f_043bd0(i);
        int c = f_043c34(i);
        if (f_043a0c(i) >= 2) {
            a = Mask(a);
            b = Mask(b);
            c = Mask(c);
        }
        for (int k = 6; k > i; k--) {
            int a2 = f_043b6c(k);
            int b2 = f_043bd0(k);
            int c2 = f_043c34(k);
            if (f_043a0c(k) >= 2) {
                a2 = Mask(a2);
                b2 = Mask(b2);
                c2 = Mask(c2);
            }
            if (a != -1) {
                if (a == a2) { n++; out[i]++; out[k]++; }
                if (a == b2) { n++; out[i]++; out[k]++; }
                if (a == c2) { n++; out[i]++; out[k]++; }
            }
            if (b != -1) {
                if (b == a2) { n++; out[i]++; out[k]++; }
                if (b == b2) { n++; out[i]++; out[k]++; }
                if (b == c2) { n++; out[i]++; out[k]++; }
            }
            if (c != -1) {
                if (c == a2) { n++; out[i]++; out[k]++; }
                if (c == b2) { n++; out[i]++; out[k]++; }
                if (c == c2) { n++; out[i]++; out[k]++; }
            }
        }
    }
    f_043c98(save);
    f_042730();
    return n;
}

/* @implements 0x042e1c us f_042e1c
   WHAT IT DOES: Resets the pending layout, sets every action's pending assignment to v and
   applies it. */
void CCustomController::f_042e1c(int v)
{
    f_0427a0();
    f_042924(0, v);
    f_042924(1, v);
    f_042924(2, v);
    f_042924(3, v);
    f_042924(4, v);
    f_042924(5, v);
    f_042924(6, v);
    f_042924(6, v);
    f_042730();
}

/* @implements 0x042ed4 us f_042ed4
   WHAT IT DOES: Returns the chosen assignment of the first action. */
int CCustomController::f_042ed4()
{
    return f_042888(0);
}

/* @implements 0x042ef0 us f_042ef0
   WHAT IT DOES: Whether button 0x800 or 0x1000 is held. */
int CCustomController::f_042ef0()
{
    return Held(0x800) || Held(0x1000);
}

/* @implements 0x042f18 us f_042f18
   WHAT IT DOES: Whether button 0x2000 or 0x400 is held. */
int CCustomController::f_042f18()
{
    return Held(0x2000) || Held(0x400);
}

/* @implements 0x042f40 us f_042f40
   WHAT IT DOES: The steering of action 0, scaled by 255 when given by buttons; otherwise that
   of action 1. */
int CCustomController::f_042f40()
{
    int v = f_04356c(0);
    if (v)
        return v * 255;
    return f_04356c(1);
}

/* @implements 0x042f90 us f_042f90
   WHAT IT DOES: The left/right direction held on the pad (directional buttons or 0x4000/0x8000
   buttons). */
int CCustomController::f_042f90()
{
    int v = f_043548(32, 8);
    v += f_043548(0x4000, 0x8000);
    return v;
}

/* @implements 0x042fe0 us f_042fe0
   WHAT IT DOES: The up/down direction held on the pad. */
int CCustomController::f_042fe0()
{
    int v = f_043548(16, 4);
    v += f_043548(0x20000, 0x10000);
    return v;
}

/* @implements 0x043030 us f_043030
   WHAT IT DOES: Whether button 0x800 or 0x1000 was just pressed. */
int CCustomController::f_043030()
{
    return Trig(0x800) || Trig(0x1000);
}

/* @implements 0x043058 us f_043058
   WHAT IT DOES: Whether button 0x2000 or 0x400 was just pressed. */
int CCustomController::f_043058()
{
    return Trig(0x2000) || Trig(0x400);
}

/* @implements 0x043080 us f_043080
   WHAT IT DOES: Whether button 0x800 or 0x1000 was just pressed. */
int CCustomController::f_043080()
{
    return Trig(0x800) || Trig(0x1000);
}

/* @implements 0x0430a8 us f_0430a8
   WHAT IT DOES: Whether button 0x2000 or 0x400 was just pressed. */
int CCustomController::f_0430a8()
{
    return Trig(0x2000) || Trig(0x400);
}

/* @implements 0x0430d0 us f_0430d0
   WHAT IT DOES: The direction just pressed on action 0, or else on action 1. */
int CCustomController::f_0430d0()
{
    int v = f_0436d0(0);
    if (v)
        return v;
    return f_0436d0(1);
}

/* @implements 0x04311c us f_04311c
   WHAT IT DOES: The left/right direction just pressed. */
int CCustomController::f_04311c()
{
    int v = f_0436ac(32, 8);
    v += f_0436ac(0x4000, 0x8000);
    return v;
}

/* @implements 0x04316c us f_04316c
   WHAT IT DOES: The up/down direction just pressed. */
int CCustomController::f_04316c()
{
    int v = f_0436ac(16, 4);
    v += f_0436ac(0x20000, 0x10000);
    return v;
}

/* @implements 0x0431bc us f_0431bc
   WHAT IT DOES: Whether button 0x800 or 0x1000 repeats. */
int CCustomController::f_0431bc()
{
    return Repeat(0x800) || Repeat(0x1000);
}

/* @implements 0x0431e4 us f_0431e4
   WHAT IT DOES: Whether button 0x2000 or 0x400 repeats. */
int CCustomController::f_0431e4()
{
    return Repeat(0x2000) || Repeat(0x400);
}

/* @implements 0x04320c us f_04320c
   WHAT IT DOES: The left/right direction repeating. */
int CCustomController::f_04320c()
{
    int v = f_04385c(32, 8);
    v += f_04385c(0x4000, 0x8000);
    return v;
}

/* @implements 0x04325c us f_04325c
   WHAT IT DOES: The up/down direction repeating. */
int CCustomController::f_04325c()
{
    int v = f_04385c(16, 4);
    v += f_04385c(0x20000, 0x10000);
    return v;
}

/* @implements 0x0432ac us f_0432ac
   WHAT IT DOES: The direction repeating on action 0, or else on action 1. */
int CCustomController::f_0432ac()
{
    int v = f_043880(0);
    if (v)
        return v;
    return f_043880(1);
}

/* @implements 0x0432f8 us f_0432f8
   WHAT IT DOES: The analog steering of action 0: for an axis kind (3, 4) the difference of its
   two buttons' levels; for kind 5 also the third level in the high half. */
int CCustomController::f_0432f8()
{
    int t = f_043a0c(0);
    if (t == 3 || t == 4) {
        int r = level[f_043bd0(0)];
        r -= level[f_043b6c(0)];
        return r;
    }
    if (t == 5) {
        int hi = level[f_043c34(0)];
        int r = level[f_043bd0(0)];
        r -= level[f_043b6c(0)];
        return (hi << 16) | (r & 0xffff);
    }
    return 0;
}

/* @implements 0x0433ec us f_0433ec
   WHAT IT DOES: For an action 0 of kind 5, its steering (difference of two levels) and its third
   level; zero for both otherwise. */
void CCustomController::f_0433ec(int *x, int *y)
{
    if (f_043a0c(0) == 5) {
        *y = level[f_043c34(0)];
        int v = level[f_043bd0(0)];
        v -= level[f_043b6c(0)];
        *x = v;
        return;
    }
    *x = 0;
    *y = 0;
}

/* @implements 0x043498 us f_043498
   WHAT IT DOES: The analog level of action 2 when it is of kind 2, else 0. */
int CCustomController::f_043498()
{
    int r = 0;
    if (f_043a0c(2) == 2)
        r = level[f_043b6c(2)];
    return r;
}

/* @implements 0x0434f0 us f_0434f0
   WHAT IT DOES: The analog level of action 3 when it is of kind 2, else 0. */
int CCustomController::f_0434f0()
{
    int r = 0;
    if (f_043a0c(3) == 2)
        r = level[f_043b6c(3)];
    return r;
}

/* @implements 0x043548 us f_043548
   WHAT IT DOES: 1 while a pos button is held, else -1 while a neg button is held, else 0. */
int CCustomController::f_043548(int neg, int pos)
{
    if (held & pos)
        return 1;
    if (held & neg)
        return -1;
    return 0;
}

/* @implements 0x04356c us f_04356c
   WHAT IT DOES: The direction held on action i: for button kinds 1, -1 or 0 from its two
   buttons; otherwise the difference of the two analog levels. */
int CCustomController::f_04356c(int i)
{
    if (f_043a0c(i) < 2) {
        if (held & f_043bd0(i))
            return 1;
        if (held & f_043b6c(i))
            return -1;
        return 0;
    }
    int v = level[f_043bd0(i)];
    v -= level[f_043b6c(i)];
    return v;
}

/* @implements 0x04361c us f_04361c
   WHAT IT DOES: Whether action i's button is held. */
int CCustomController::f_04361c(int i)
{
    if (f_043a0c(i) < 2)
        return (held & f_043b6c(i)) != 0;
    return (held & Mask(f_043b6c(i))) != 0;
}

/* @implements 0x0436ac us f_0436ac
   WHAT IT DOES: 1 when a pos button was just pressed, else -1 for a neg button, else 0. */
int CCustomController::f_0436ac(int neg, int pos)
{
    if (trig & pos)
        return 1;
    if (trig & neg)
        return -1;
    return 0;
}

/* @implements 0x0436d0 us f_0436d0
   WHAT IT DOES: The direction just pressed on action i. */
int CCustomController::f_0436d0(int i)
{
    if (f_043a0c(i) < 2) {
        if (trig & f_043bd0(i))
            return 1;
        if (trig & f_043b6c(i))
            return -1;
        return 0;
    }
    if (trig & Mask(f_043bd0(i)))
        return 1;
    if (trig & Mask(f_043b6c(i)))
        return -1;
    return 0;
}

/* @implements 0x0437cc us f_0437cc
   WHAT IT DOES: Whether action i's button was just pressed. */
int CCustomController::f_0437cc(int i)
{
    if (f_043a0c(i) < 2)
        return (trig & f_043b6c(i)) != 0;
    return (trig & Mask(f_043b6c(i))) != 0;
}

/* @implements 0x04385c us f_04385c
   WHAT IT DOES: 1 when a pos button repeats, else -1 for a neg button, else 0. */
int CCustomController::f_04385c(int neg, int pos)
{
    if (repeat & pos)
        return 1;
    if (repeat & neg)
        return -1;
    return 0;
}

/* @implements 0x043880 us f_043880
   WHAT IT DOES: The direction repeating on action i. */
int CCustomController::f_043880(int i)
{
    if (f_043a0c(i) < 2) {
        if (repeat & f_043bd0(i))
            return 1;
        if (repeat & f_043b6c(i))
            return -1;
        return 0;
    }
    if (repeat & Mask(f_043bd0(i)))
        return 1;
    if (repeat & Mask(f_043b6c(i)))
        return -1;
    return 0;
}

/* @implements 0x04397c us f_04397c
   WHAT IT DOES: Whether action i's button repeats. */
int CCustomController::f_04397c(int i)
{
    if (f_043a0c(i) < 2)
        return (repeat & f_043b6c(i)) != 0;
    return (repeat & Mask(f_043b6c(i))) != 0;
}

/* @draft 0x043a0c us f_043a0c
   WHAT IT DOES: The kind of action i's chosen assignment: actions 7 to 9 are plain buttons (1),
   10 to 17 kind 0; 255 for none.
   Remaining difference: block layout; retail keeps the table path as the fall-through and the kind mask after it (the same shape as f_043aa0, which matches), here the constant kinds come first. */
int CCustomController::f_043a0c(int i)
{
    unsigned int k;
    if (m5 > 0)
        return 255;
    if (i < 7)
        k = D_1d5d70[m5][i].assign[f_042888(i)].kind;
    else if (i < 10)
        k = 1;
    else if (i < 18)
        k = 0;
    else
        return 255;
    return k & 0xf;
}

/* @implements 0x043aa0 us f_043aa0
   WHAT IT DOES: The kind word of action i's chosen assignment, with its flags. */
unsigned int CCustomController::f_043aa0(int i)
{
    unsigned int k;
    if (m5 > 0)
        return 255;
    if (i < 7)
        k = D_1d5d70[m5][i].assign[f_042888(i)].kind;
    else if (i < 10)
        k = 1;
    else if (i < 18)
        k = 0;
    else
        return 255;
    return k;
}

/* @implements 0x043b2c us f_043b2c
   WHAT IT DOES: How many assignments action i offers. */
int CCustomController::f_043b2c(int i)
{
    if (m5 > 0)
        return -1;
    if ((unsigned int)i < 7)
        return D_1d5d70[m5][i].count;
    return 1;
}

/* @implements 0x043b6c us f_043b6c
   WHAT IT DOES: The first button of action i's chosen assignment. */
int CCustomController::f_043b6c(int i)
{
    if (m5 > 0)
        return -1;
    if (i < 7)
        return D_1d5d70[m5][i].assign[f_042888(i)].b0;
    return -1;
}

/* @implements 0x043bd0 us f_043bd0
   WHAT IT DOES: The second button of action i's chosen assignment. */
int CCustomController::f_043bd0(int i)
{
    if (m5 > 0)
        return -1;
    if (i < 7)
        return D_1d5d70[m5][i].assign[f_042888(i)].b1;
    return -1;
}

/* @implements 0x043c34 us f_043c34
   WHAT IT DOES: The third button of action i's chosen assignment. */
int CCustomController::f_043c34(int i)
{
    if (m5 > 0)
        return -1;
    if (i < 7)
        return D_1d5d70[m5][i].assign[f_042888(i)].b2;
    return -1;
}

/* @implements 0x043c98 us f_043c98
   WHAT IT DOES: Restores the chosen assignments from buf. */
void CCustomController::f_043c98(unsigned char (*buf)[7])
{
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < 7; j++)
            sel[i][j] = buf[i][j];
}

/* @implements 0x043ce0 us f_043ce0
   WHAT IT DOES: Saves the chosen assignments into buf. */
void CCustomController::f_043ce0(unsigned char (*buf)[7])
{
    for (int i = 0; i < 1; i++)
        for (int j = 0; j < 7; j++)
            buf[i][j] = sel[i][j];
}

/* @implements 0x043d2c us f_043d2c
   WHAT IT DOES: Resets the layout to every action's first assignment. */
void CCustomController::f_043d2c()
{
    f_0427a0();
    f_042924(0, 0);
    f_042924(1, 0);
    f_042924(2, 0);
    f_042924(3, 0);
    f_042924(4, 0);
    f_042924(5, 0);
    f_042924(6, 0);
    f_042924(6, 0);
    f_042730();
}

/* @implements 0x043dd8 us f_043dd8
   WHAT IT DOES: The same reset as f_043d2c. */
void CCustomController::f_043dd8()
{
    f_0427a0();
    f_042924(0, 0);
    f_042924(1, 0);
    f_042924(2, 0);
    f_042924(3, 0);
    f_042924(4, 0);
    f_042924(5, 0);
    f_042924(6, 0);
    f_042924(6, 0);
    f_042730();
}

/* @implements 0x043e84 us f_043e84
   WHAT IT DOES: Whether button 0x10 was just pressed while 0x400 and 0x800 are held. */
int CCustomController::f_043e84()
{
    return Trig(0x10) && Held(0x400) && Held(0x800);
}

/* @implements 0x043eb8 us f_043eb8
   WHAT IT DOES: Whether button 4 was just pressed while 0x400 and 0x800 are held. */
int CCustomController::f_043eb8()
{
    return Trig(4) && Held(0x400) && Held(0x800);
}

/* @implements 0x043eec us f_043eec
   WHAT IT DOES: Nothing. */
void CCustomController::f_043eec() {}

/* @implements 0x043ef4 us f_043ef4
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043ef4() { return 0; }

/* @implements 0x043efc us f_043efc
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043efc() { return 0; }

/* @implements 0x043f04 us f_043f04
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f04() { return 0; }

/* @implements 0x043f0c us f_043f0c
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f0c() { return 0; }

/* @implements 0x043f14 us f_043f14
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f14() { return 0; }

/* @implements 0x043f1c us f_043f1c
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f1c() { return 0; }

/* @implements 0x043f24 us f_043f24
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f24() { return 0; }

/* @implements 0x043f2c us f_043f2c
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f2c() { return 0; }

/* @implements 0x043f34 us f_043f34
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f34() { return 0; }

/* @implements 0x043f3c us f_043f3c
   WHAT IT DOES: Returns 0. */
int CCustomController::f_043f3c() { return 0; }

/* The implicit destructor, emitted out of line for the vtable.
   @implements 0x043f44 us _ZN10Controller17CCustomControllerD1Ev
   WHAT IT DOES: Destroys the controller (the base destructor stores the base vtable).
   @implements 0x043f54 us _ZN10Controller17CCustomControllerD0Ev
   WHAT IT DOES: Destroys the controller and frees it. */
