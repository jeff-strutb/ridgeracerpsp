/* The looping leaf-blow sound's per-frame tick (retail 0x0ec2cc to 0x0ec35c). Every 61 frames
   the loop checks the byte at +35 against the threshold at +36, and when it is below, blows a
   leaf burst (CRaceEffects::f_031e4c) at the loop's position and stores the burst's colour (three
   bytes at +32..+34, packed) on the burst. The frame counter (+0) then restarts at 1. */

struct LeafLoop {
    int m0;
    unsigned char m4;
    char m5[3];
    char m8[12];
    char m20[12];
    unsigned char m32;
    unsigned char m33;
    unsigned char m34;
    unsigned char m35;
    unsigned char m36;
};

struct LeafBurst {
    char m0[76];
    unsigned int m76;
};

extern char D_2402e0[];
extern "C" LeafBurst *f_031e4c(void *fx, unsigned char *a, void *pos, void *b);

/* @implements 0x0ec2cc us f_0ec2cc
   WHAT IT DOES: Advances the loop's frame counter. Once it reaches 61 and the byte at +35 is
   below the one at +36, blows a leaf burst at the loop's position with the packed colour of its
   three colour bytes. The counter then restarts at 1. */
extern "C" void f_0ec2cc(LeafLoop *p)
{
    unsigned char *t = &p->m35;
    int n = p->m0;
    if (n >= 61) {
        if (*t < t[1]) {
            LeafBurst *r = f_031e4c(D_2402e0, t, p->m8, p->m20);
            r->m76 = (p->m34 << 16) | (p->m33 << 8) | p->m32;
        }
        p->m0 = 0;
        n = 0;
    }
    p->m0 = n + 1;
}
