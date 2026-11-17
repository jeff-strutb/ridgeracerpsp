/* The table interpolation (retail 0x0c801c to 0x0c80a8, the object file before the engine
   sound): a 128-entry float table sampled every 10 units, read with linear interpolation. */

/* @draft 0x0c801c us f_0c801c
   WHAT IT DOES: The value of table t at x, interpolated between its entries every 10 units;
   x below 0 gives the first entry, x at or past the last step the last (entry 127).
   Remaining difference (6 words): retail loads t[i] after both subtractions of lo (into lo's
   dead f3); sched1 issues it first here. Computing d and w in locals first does not move it.
   Cycle 2026-11-16 (RTL): sched1 already puts both subtractions of lo (insns 46, 54) before the
   loads; the real decider is local-alloc giving t[i] (pseudo 218) $f4 instead of lo's dead $f3, so
   sched2 has no anti-dependence holding the load back. Retail's t[i] in $f3 is what forces it late.
   No source lever found for the lreg choice; no change made. */
float f_0c801c(void *unused, int x, float *t)
{
    int i = x / 10;
    float lo, d, w;

    if (i >= 127)
        return t[127];
    if (x < 0)
        return t[0];
    lo = (float)(i * 10);
    d = (float)x - lo;
    w = (float)(i * 10 + 10) - lo;
    return d * (t[i + 1] - t[i]) / w + t[i];
}
