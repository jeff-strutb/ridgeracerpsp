/* The staff roll object file (retail 0x088b58 to 0x089438). The wireless result screen creates
   it: it reads the "EndRoll" script from the sequence package and scrolls its lines up the
   menu layer, one text line ("STR" or the centred "STRC") per script line, until the script's
   "END". */

#include <string.h>

extern "C" {
void f_021720(void);
void f_021750(void);
void f_00d354(char *buf, int size, const char *fmt, ...);
}
extern char D_245178[];

/* The sequence manager (its own object file). */
struct CSequence {
    char *f_005c34(const char *name);
};
extern CSequence D_1dd6b0;

/* The menu layer the roll draws into (its own object file). */
struct CMenuLayer {
    void f_06caa8(int a, int font, int c);
    int f_06cb40(int x, int y, int text, int pri, float r, float g, float b, float a);
    int f_06ccf8(int x, int y, int text, int pri, float sx, float sy, float r, float g, float b,
                  float a);
};

class CEndRoll {
public:
    int f_088b58(CMenuLayer *menu);
    int f_088bc8();
    int f_088bd4();
    void f_088bdc();
    void f_088c1c(int font, int x, int y);
    void f_088cf4(int text, int x, int y, int size);
    void f_088db0(int font, int x, int y, int size);
    void f_088eb4(int text, int x, int y, int size);
    int f_088f9c();

    CMenuLayer *menu;
    bool done;
    char *script;
    int time;
    int speed;
    int pos;
    int y;
    int count;
};

/* @implements 0x088b58 us f_088b58
   WHAT IT DOES: Starts the roll on a menu layer: clears the state and, given a layer, finds
   the "EndRoll" script in the sequence package. Returns 1 when started. */
int CEndRoll::f_088b58(CMenuLayer *m)
{
    int r = 0;
    done = 0;
    script = 0;
    time = 0;
    speed = 0;
    pos = 0;
    y = 0;
    count = 0;
    menu = m;
    if (m) {
        script = D_1dd6b0.f_005c34("EndRoll");
        r = 1;
    }
    return r;
}

/* @implements 0x088bc8 us f_088bc8
   WHAT IT DOES: Forgets the script. */
int CEndRoll::f_088bc8()
{
    script = 0;
    return 1;
}

/* @implements 0x088bd4 us f_088bd4
   WHAT IT DOES: Nothing (returns 1). */
int CEndRoll::f_088bd4()
{
    return 1;
}

/* @implements 0x088bdc us f_088bdc
   WHAT IT DOES: Draws one frame of the roll, noting when the script has ended. */
void CEndRoll::f_088bdc()
{
    f_021720();
    if (f_088f9c())
        done = 1;
    f_021750();
}

/* @implements 0x088c1c us f_088c1c
   WHAT IT DOES: Draws a text line in the given font with a dark shadow one pixel down and
   right, then counts one more line drawn. */
void CEndRoll::f_088c1c(int font, int x, int y)
{
    CMenuLayer *m = menu;
    m->f_06caa8(0, font, 0);
    m->f_06cb40(x + 1, y + 1, 0x2dcab0, count + 480, 0.1f, 0.1f, 0.1f, 1.0f);
    m->f_06cb40(x, y, 0x2dcab0, count + 480, 1.0f, 1.0f, 1.0f, 1.0f);
    count++;
}

/* @implements 0x088cf4 us f_088cf4
   WHAT IT DOES: Draws a text entry with a dark shadow one pixel down and right. */
void CEndRoll::f_088cf4(int text, int x, int y, int size)
{
    CMenuLayer *m = menu;
    m->f_06cb40(x + 1, y + 1, text, count + 480, 0.1f, 0.1f, 0.1f, 1.0f);
    m->f_06cb40(x, y, text, count + 480, 1.0f, 1.0f, 1.0f, 1.0f);
}

/* @implements 0x088db0 us f_088db0
   WHAT IT DOES: Draws a text line in the given font, scaled by size, with a dark shadow one
   pixel down and right, then counts one more line drawn. */
void CEndRoll::f_088db0(int font, int x, int y, int size)
{
    float s = (float)size * 0.014f;
    CMenuLayer *m = menu;
    m->f_06caa8(0, font, 0);
    m->f_06ccf8(x + 1, y + 1, 0x2dcab0, count + 480, s, s, 0.1f, 0.1f, 0.1f, 1.0f);
    m->f_06ccf8(x, y, 0x2dcab0, count + 480, s, s, 1.0f, 1.0f, 1.0f, 1.0f);
    count++;
}

/* @implements 0x088eb4 us f_088eb4
   WHAT IT DOES: Draws a text entry scaled by size, with a dark shadow one pixel down and
   right. */
void CEndRoll::f_088eb4(int text, int x, int y, int size)
{
    float s = (float)size * 0.014f;
    CMenuLayer *m = menu;
    m->f_06ccf8(x + 1, y + 1, text, count + 480, s, s, 0.1f, 0.1f, 0.1f, 1.0f);
    m->f_06ccf8(x, y, text, count + 480, s, s, 1.0f, 1.0f, 1.0f, 1.0f);
}
