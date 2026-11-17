/* The course sound emitter lookup (retail 0x0e7718 to 0x0e7768). The emitter list (D_27eac0)
   holds four emitters of 64 bytes, each stamped with a count when it is started (see
   0x0e767c). The lookup returns the emitter of a kind when its stamp is the current count,
   or NULL. The third kind (index 2) is looked up one count behind. */

struct Emitter {
    int id;                 /* the stamp: the count when the emitter was last started */
    int m4[3];
    float prev[4];
    float cur[4];
    int m48[4];
};

extern int D_23faec;       /* the current count */

/* @draft 0x0e7718 us f_0e7718
   WHAT IT DOES: Returns the emitter of the given kind if its stamp equals the count (for
   kind 2, if its stamp plus one does), or NULL otherwise.
   Remaining difference (7 words): retail computes e (addu) in the beq delay slot with the shift
   in v1, i.e. pre-sched2 the addu follows r = 0 and the reload of 2 (ours: sll, addu, li, move);
   and the kind == 2 arm is beql + move / j + nop where ours is bne + nop / j + move (reorg
   optimize_skip did not fire on ours). Tried e computed separately in each arm: 21/21 worse
   (the kind == 2 arm folds e to emitters + 0x80); reverted. */
struct Emitter *f_0e7718(void *emitters, int kind)
{
    struct Emitter *e = (struct Emitter *)emitters + kind;
    struct Emitter *r = 0;

    if (kind != 2) {
        if (e->id == D_23faec)
            r = e;
    } else {
        if (e->id + 1 == D_23faec)
            r = e;
    }
    return r;
}
