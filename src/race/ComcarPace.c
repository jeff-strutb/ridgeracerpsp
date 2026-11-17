/* The computer car's pace helpers (retail 0x0fd3fc to 0x0fd6f8, a gap row with no unwind
   information, so plain C): the per frame pace step that holds a computer driven car at a
   distance from the player's car (D_245ecc), a set of two words, a set of empty hooks and a
   float read at +204. The car's physics record is at +5792 and the player's car is read
   through the global pointer on every call. */

/* The physics record. Only the fields the pace step reads are named (the distance along the
   course at +444 and +472, and the flag word at +1020). */
typedef struct Phys {
    char p0[444];
    float m444;
    char p448[24];
    int m472;
    char p476[544];
    int m1020;
} Phys;

extern int D_245ec8;
extern char *D_245ecc;

#define FIELD(t, o, off) (*(t *)((char *)(o) + (off)))

/* @implements 0x0fd3fc us f_0fd3fc
   2026-11-16 second cycle (2 -> 0 words): sched2 issues the last independent store first, so
   the +10132 store is written before the +7692 store; retail's order (+7692, then +10132 in the
   jr delay slot) follows.
   2026-11-16 cycle (26 -> 2 words): one 'bits' variable for both input-bit updates made it a
   global pseudo live across the catch-up block, where local-alloc had put (count - 1) in a0;
   that hard-reg conflict pushed bits to a1 and pulled the count to a0. A separate local 'set'
   for the second update keeps it block-local, so the count is a1 and bits a0 as in retail.
   Earlier: moving the pace store, a copied car pointer local and read-modify-write field
   updates were tried and each made it worse.
   WHAT IT DOES: One pace step for a computer driven car (the car pointer). It returns at once
   while the enable word (+9720) is zero. Otherwise it clears bit 16 of the input bits (+7692) and
   decays the pace value (+10124) by 0.995. It takes the car's distance in 1/100 units (+472) and
   the float at +444 minus the player's car's values (the player's car is read through D_245ecc,
   at its physics record). The mode word (+9708) picks a band of that distance in which the pace
   value gets 100 or 200 added, and when the distance is within 2500 and the player's boost state
   (+10044) is 1, 500 is added. The second value (+10128) then runs down by 1/60 a step: while it
   stays under 8 with the catch-up flag (+10132) set, the shared counter D_245ec8 and the flag are
   cleared, and a value that is not positive is clamped to zero. When it is not positive, a catch-up
   can start: the count at +9704 must be non-zero, the player must be at least 18000 ahead on the
   pace value, the car's +7220 word and its +1020 word (4) must allow it, and the lateral test must
   pass. It then sets +9704 down by one, +10128 to 15, D_245ec8 to 1, +10124 to 0, bit 16 of the
   input bits and +10132 to 1. The names of the fields are the ones the car code uses; the meaning
   of the pace and catch-up values is read from this code only. */
void f_0fd3fc(char *car)
{
    Phys *p;
    Phys *mp;
    char *drv;
    float x, y, f3, f4, dI, dF;
    unsigned bits, set;
    int mode, a1;

    p = (Phys *)(car + 5792);
    drv = car + 7092;
    if (FIELD(int, car, 9720) == 0)
        return;
    x = FIELD(float, car, 10124);
    bits = FIELD(unsigned, car, 7692);
    bits &= 0xfffeffff;
    FIELD(unsigned, car, 7692) = bits;
    f3 = x * 0.995f;
    FIELD(float, car, 10124) = f3;
    mp = (Phys *)(D_245ecc + 5792);
    dI = (float)(p->m472 - mp->m472);
    dF = p->m444 - mp->m444;
    mode = FIELD(int, car, 9708);

    if (mode == 1) {
        if (dI < 2000.0f && -2000.0f < dI)
            FIELD(float, car, 10124) = f3 + 100.0f;
    } else if (mode < 2) {
        if (mode == 0 && dI < -500.0f && -4500.0f < dI)
            FIELD(float, car, 10124) = f3 + 200.0f;
    } else if (mode == 2) {
        if (dI < 4500.0f && 500.0f < dI)
            FIELD(float, car, 10124) = f3 + 200.0f;
    }

    if (dI < 2500.0f && -2500.0f < dI && FIELD(int, D_245ecc, 10044) == 1)
        FIELD(float, car, 10124) = FIELD(float, car, 10124) + 500.0f;

    x = FIELD(float, car, 10128);
    f3 = 0.0f;
    if (0.0f < x) {
        y = x - 0.016666668f;
        FIELD(float, car, 10128) = y;
        if (y < 8.0f) {
            if (FIELD(int, car, 10132) != 0) {
                D_245ec8 = 0;
                FIELD(int, car, 10132) = 0;
            }
        }
        if (!(0.0f < FIELD(float, car, 10128)))
            FIELD(float, car, 10128) = 0.0f;
        return;
    }

    a1 = FIELD(int, car, 9704);
    if (a1 == 0)
        return;
    if (D_245ec8 != 0) {
        if (a1 >= 0)
            return;
    }
    if (FIELD(float, car, 10124) < 18000.0f)
        return;
    if (*(int *)(drv + 128) != 0)
        return;
    if (p->m1020 != 4)
        return;
    if (dI < 0.0f && dF < 2.0f && -2.0f < dF)
        return;
    set = FIELD(unsigned, car, 7692) | 0x10000;
    FIELD(int, car, 9704) = a1 - 1;
    FIELD(float, car, 10128) = 15.0f;
    D_245ec8 = 1;
    FIELD(float, car, 10124) = 0.0f;
    FIELD(int, car, 10132) = 1;
    FIELD(unsigned, car, 7692) = set;
}

/* @implements 0x0fd6c4 us f_0fd6c4
   WHAT IT DOES: An empty hook. */
void f_0fd6c4(void)
{
}

/* @implements 0x0fd6cc us f_0fd6cc
   WHAT IT DOES: An empty hook. */
void f_0fd6cc(void)
{
}

/* @implements 0x0fd6d4 us f_0fd6d4
   WHAT IT DOES: An empty hook. */
void f_0fd6d4(void)
{
}

/* @implements 0x0fd6dc us f_0fd6dc
   WHAT IT DOES: An empty hook. */
void f_0fd6dc(void)
{
}

/* @implements 0x0fd6e4 us f_0fd6e4
   WHAT IT DOES: Stores the two words of its record: the second argument at +0 and the third
   at +4, the +4 store first. */
void f_0fd6e4(int *rec, int a, int b)
{
    rec[0] = a;
    rec[1] = b;
}

/* @implements 0x0fd6f0 us f_0fd6f0
   WHAT IT DOES: Returns the float at +204 of its second argument (the first is unused). */
float f_0fd6f0(void *unused, char *obj)
{
    (void)unused;
    return *(float *)(obj + 204);
}
