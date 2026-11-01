/* @cflags: -fno-cse-skip-blocks */
/* The race random numbers and angle helpers (retail 0x0c2a40 to 0x0c2f24): two linear
   congruential generators (multiplier 0x41c64e6d, increment 12345, the top 16 bits taken)
   with their seeds, their results scaled to 0..1, a generator over a caller's own state, the
   wrap of an angle difference into -pi..pi and an absolute value. */

extern unsigned int D_245ed0;   /* the seed the first generator is restarted from */
extern unsigned int D_245ed4;   /* the first generator's state */
extern unsigned int D_245ed8;   /* the second generator's state */

/* @implements 0x0c2a40 us f_0c2a40
   WHAT IT DOES: Seeds the second generator. */
void f_0c2a40(unsigned int seed)
{
    D_245ed8 = seed;
}

/* @implements 0x0c2a4c us f_0c2a4c
   WHAT IT DOES: Restarts the first generator from its saved seed. */
void f_0c2a4c(void)
{
    D_245ed4 = D_245ed0;
}

/* @implements 0x0c2a60 us f_0c2a60
   WHAT IT DOES: Steps the first generator; returns its top 16 bits. */
unsigned int f_0c2a60(void)
{
    D_245ed4 = D_245ed4 * 0x41c64e6d + 12345;
    return D_245ed4 >> 16;
}

/* @implements 0x0c2a88 us f_0c2a88
   WHAT IT DOES: Steps the second generator; returns its top 16 bits. */
unsigned int f_0c2a88(void)
{
    D_245ed8 = D_245ed8 * 0x41c64e6d + 12345;
    return D_245ed8 >> 16;
}

/* @implements 0x0c2ab0 us f_0c2ab0
   WHAT IT DOES: The first generator scaled to 0..1. */
float f_0c2ab0(void)
{
    return (float)f_0c2a60() / 65535.0f;
}

/* @implements 0x0c2b04 us f_0c2b04
   WHAT IT DOES: The second generator scaled to 0..1. */
float f_0c2b04(void)
{
    return (float)f_0c2a88() / 65535.0f;
}

/* @implements 0x0c2b58 us f_0c2b58
   WHAT IT DOES: Steps a generator whose state the caller holds; returns its top 16 bits. */
unsigned int f_0c2b58(unsigned int *state)
{
    *state = *state * 0x41c64e6d + 12345;
    return *state >> 16;
}

/* @implements 0x0c2b7c us f_0c2b7c
   WHAT IT DOES: A caller's generator scaled to 0..1. */
float f_0c2b7c(unsigned int *state)
{
    return (float)f_0c2b58(state) / 65535.0f;
}

/* @implements 0x0c2bd0 us f_0c2bd0
   WHAT IT DOES: The difference of two angles wrapped into -pi..pi. */
float f_0c2bd0(float a, float b)
{
    float d = a - b;

    if (d > 3.14159274f)
        d -= 6.28318548f;
    else if (d < -3.14159274f)
        d += 6.28318548f;
    return d;
}

/* @implements 0x0c2c24 us f_0c2c24
   WHAT IT DOES: The absolute value. */
float f_0c2c24(float x)
{
    float r;

    if (0 <= x)
        r = x;
    else
        r = -x;
    return r;
}

extern char *D_2407fc;  /* the race manager; its +72 field is the rank-table index 1..3 */
extern float D_2456b0;  /* full turn (2 pi), the scale of the lap counter */

/* @implements 0x0c2c44 us f_0c2c44
   WHAT IT DOES: Rubber-banding for car `me` among the `n` cars at `cars` (stride 10144). A
   car's progress is (float)lap * D_2456b0 + position (lap at +2212, position at +2144). Finds
   the leader's progress and the gap to `me`. The manager's +72 field (1..3) picks a column of
   the per-rank tables. A float at me+9948 is eased by 1/60 per call: up toward 100 while `me`
   is the leader or level (gap <= 0), down toward -100 while it trails. The float at me+9920 is
   then set to 1.0 + factor * (blend * scale + offset), where blend is the gap beyond the dead
   zone as a fraction of its span clamped to 0..1, and factor is 1 - ease/limit (leading) or
   |ease|/limit (trailing), each capped at 1. An index outside 1..3, or no leader found, just
   sets me+9920 to 1.0; no cars returns without writing. File flag: -fno-cse-skip-blocks. */
void f_0c2c44(int n, char *me, char *cars)
{
    float dead[4] = {0.0f, 5.0f, 0.0f, 0.0f};
    float span[4] = {100.0f, 60.0f, 80.0f, 100.0f};
    float off[4] = {0.0f, 0.0f, 0.0f, 0.02f};
    float scale[4] = {0.0f, 0.1f, 0.14f, 0.19f};
    float lim[4] = {1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f, 1.5f};
    int k = *(int *)(D_2407fc + 72);
    float g2, e, s, best, v, gap, ease, ratio, blend;
    int lead, i;

    if (k > 0)
        if (k < 4) {
            if (n <= 0)
                return;
            best = -1000000.0f;
            lead = -1;
            for (i = 0; i < n; i++) {
                v = (float)*(int *)(cars + i * 10144 + 2212) * D_2456b0
                    + *(float *)(cars + i * 10144 + 2144);
                if (best < v) {
                    best = v;
                    lead = i;
                }
            }
            if (lead >= 0)
                if (lead < n)
                    goto main;
        }
    *(float *)(me + 9920) = 1.0f;
    return;
main:
    v = (float)*(int *)(me + 2212) * D_2456b0 + *(float *)(me + 2144);
    gap = best - v;
    g2 = gap - dead[k];
    if (gap <= 0.0f) {
        e = *(float *)(me + 9948);
        ease = 0.0f;
        if (0.0f < e)
            ease = e;
        s = ease + 0.016666667f;
        *(float *)(me + 9948) = ease;
        if (!(s < 100.0f))
            s = 100.0f;
        *(float *)(me + 9948) = s;
        ratio = s < lim[k] ? s / lim[k] : 1.0f;
        ratio = 1.0f - ratio;
    } else {
        e = *(float *)(me + 9948);
        ease = 0.0f;
        if (e < 0.0f)
            ease = e;
        *(float *)(me + 9948) = ease;
        s = ease - 0.016666667f;
        ease = s > -100.0f ? s : -100.0f;
        *(float *)(me + 9948) = ease;
        ratio = -ease < lim[k] ? -ease / lim[k] : 1.0f;
    }
    if (g2 < 0.0f)
        blend = 0.0f;
    else if (span[k] <= g2)
        blend = 1.0f;
    else
        blend = g2 / span[k];
    blend = blend * scale[k];
    blend = blend + off[k];
    *(float *)(me + 9920) = ratio * blend + 1.0f;
}
