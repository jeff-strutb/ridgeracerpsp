/* The sound code's random numbers (retail 0x0f6b90 to 0x0f6c14): a linear congruential
   generator (the Numerical Recipes constants) whose seed D_27f098 is cleared at start up. */

/* The generator's seed. */
struct Seed {
    unsigned int v;
    Seed() { v = 0; }
};
Seed D_27f098;

/* @implements 0x0f6b90 us f_0f6b90
   WHAT IT DOES: Steps the seed (seed * 1664525 + 1013904223) and returns its top 31 bits. */
extern "C" unsigned int f_0f6b90()
{
    D_27f098.v = D_27f098.v * 1664525 + 1013904223;
    return D_27f098.v >> 1;
}

/* @implements 0x0f6bc0 us f_0f6bc0
   WHAT IT DOES: Sets the seed. */
extern "C" void f_0f6bc0(unsigned int s)
{
    D_27f098.v = s;
}

/* @implements 0x0f6bcc us __static_initialization_and_destruction_0
   WHAT IT DOES: Clears the seed at start up. */
/* @implements 0x0f6bf4 us _GLOBAL__I
   WHAT IT DOES: Runs the above. */
