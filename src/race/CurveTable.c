/* The response curves (retail 0x0e40b8 to 0x0e428c): cubic Bezier curves given as four x
   control values followed by four y control values. A lookup steps the curve parameter from
   0 to 1 in 1/256 steps until the curve's x reaches the input, and returns the curve's y
   there, kept within its end values. Four fixed curves are looked up through wrappers. */

/* A curve: the x and y control values. */
struct Curve {
    float x[4];
    float y[4];
};

extern struct Curve D_1d54bc;
extern struct Curve D_1d54dc;
extern struct Curve D_1d54fc;
extern struct Curve D_1d551c;

/* @implements 0x0e40b8 us f_0e40b8
   WHAT IT DOES: One coordinate of a cubic Bezier curve at parameter t. */
float f_0e40b8(const float *p, float t)
{
    float u = 1.0f - t;
    float w[4];

    w[0] = u * u * u;
    w[1] = 3.0f * u * u * t;
    w[2] = 3.0f * u * t * t;
    w[3] = t * t * t;
    return p[0] * w[0] + p[1] * w[1] + p[2] * w[2] + p[3] * w[3];
}

/* @draft 0x0e4128 us f_0e4128
   DRAFT: 3 words. Retail branches to the found path with a plain bc1t (the parameter copy to
   $f12 in its delay slot, done on both paths); here the found path is predicted taken and
   gets a bc1tl with the pointer move. goto, break, continue, inverted tests, a do loop and
   __builtin_expect were tried.
   -da (2026-11-16): f_0e40b8 is detected pure (defined earlier in the TU), so each call is a
   libcall block (call_insn/u) whose arg moves are emitted a0 first. In the loop block (c and t
   both live after) sched1 issues the $f12 move first (retail's order, both calls); in the found
   block the moves kill their sources (c->y's hoisted pseudo and t) and sched1 keeps a0 first,
   so dbr has a0's move as the target's first insn and annuls it. Retail needs the found
   block's two moves to schedule like the loop block's; the source shape is not yet known.
   WHAT IT DOES: The curve's y where its x first reaches the input (its last y if never),
   kept to its end values when it leaves 0..1. */
float f_0e4128(struct Curve *c, float x)
{
    float t;

    for (t = 0; t < 1.0f; t += 0.00390625f) {
        if (x <= f_0e40b8(c->x, t)) {
            float y = f_0e40b8(c->y, t);

            if (y < 0)
                y = c->y[0];
            if (1.0f < y)
                y = c->y[3];
            return y;
        }
    }
    return c->y[3];
}

/* @implements 0x0e420c us f_0e420c
   WHAT IT DOES: Looks up the first fixed curve. */
float f_0e420c(float x)
{
    return f_0e4128(&D_1d54bc, x);
}

/* @implements 0x0e422c us f_0e422c
   WHAT IT DOES: Looks up the second fixed curve. */
float f_0e422c(float x)
{
    return f_0e4128(&D_1d54dc, x);
}

/* @implements 0x0e424c us f_0e424c
   WHAT IT DOES: Looks up the third fixed curve. */
float f_0e424c(float x)
{
    return f_0e4128(&D_1d54fc, x);
}

/* @implements 0x0e426c us f_0e426c
   WHAT IT DOES: Looks up the fourth fixed curve. */
float f_0e426c(float x)
{
    return f_0e4128(&D_1d551c, x);
}
