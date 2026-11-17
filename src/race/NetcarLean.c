/* The network car's lean (retail 0x0c2908 to 0x0c2a08, the object file after the network
   car): the lean value at the car's +5792 + 1108, driven by the steering byte of the car's
   input bits, and its ratio to the current limit. */

#define FLD(p, off) (*(float *)((char *)(p) + (off)))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

extern const float D_1acfc8;    /* 127.0, the steering byte's full scale */
extern const float D_1acfcc;    /* the decay of the lean with no steering */

/* @draft 0x0c2908 us f_0c2908
   WHAT IT DOES: Scales the car's two lean limits (+7996 + 8 and + 12) by the steering
   magnitude, then moves the lean toward the steered side by its step (+32 when steering one
   way, +36 the other), limited by the scaled limit, or decays it when there is no steering;
   stores the lean's magnitude over the first limit (0 when that limit is 0).
   Remaining difference (29 words): retail forms c right after the first read and p in the
   bc1f slot, and re-reads the steering byte before the limit stores (here after); the
   magnitude path keeps r in f1. Reading the byte into an int local before the stores lets
   CSE merge it with the first read (64 words), so retail's second read follows the join. */
void f_0c2908(char *car, signed char *bits)
{
    float a = (float)*bits;
    char *c = car + 7996;
    char *p;

    if (a < 0.0f)
        a = -a;
    p = car + 5792;
    FLD(c, 16) = FLD(c, 8) * a / D_1acfc8;
    FLD(c, 20) = FLD(c, 12) * a / D_1acfc8;
    if (*bits != 0) {
        if (*bits >= 0) {
            FLD(p, 1108) += FLD(c, 36);
            FLD(p, 1108) = MAX(FLD(p, 1108), FLD(c, 20));
        } else {
            FLD(p, 1108) += FLD(c, 32);
            FLD(p, 1108) = MIN(FLD(p, 1108), FLD(c, 16));
        }
    } else {
        FLD(p, 1108) *= D_1acfcc;
    }
    if (FLD(c, 16) != 0.0f) {
        float r = FLD(p, 1108) / FLD(c, 16);

        FLD(c, 44) = r;
        if (r < 0.0f)
            r = -r;
        FLD(c, 44) = r;
    } else {
        FLD(c, 44) = 0.0f;
    }
}
