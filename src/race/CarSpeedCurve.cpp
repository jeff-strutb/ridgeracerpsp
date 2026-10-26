/* Car speed curve and slip state, first object file (retail 0x0bbc1c to 0x0bc714, the gap
   words included). A car keeps a curve table (a float array at the start of its curve block:
   twenty entries at byte offsets 4, 8, ... 80) and a state record with a mode (word 8), a
   counter (word 12), a step index (word 16), and a few float state values. The curve lookup
   interpolates the table at a point scaled by the car's span; the state update advances the
   counter, the index, and the smoothed value per frame. */

union W {
    int i;
    unsigned int u;
    float f;
    void *p;
};

/* The curve block: word k is at byte offset 4k. Word 0 is unused here; words 1 to 20 are the
   table; word 31 is the curve's scale value (offset 124). */
struct Curve {
    W w[64];
};

/* The car's state record: word k is at byte offset 4k. */
struct Obj {
    W w[64];
};

extern "C" {
float f_0bbc1c(float x, Obj *o);
}

/* @draft 0x0bbc1c us f_0bbc1c
   WHAT IT DOES: looks up a point on the car's curve. It finds the first table segment whose
   end is at or above x (segments are 500 units wide), then interpolates between the two
   table values at its ends and scales the result by the car's span (word 35).
   Remaining difference: 22 of 37 words differ; size 140 vs 148. Retail computes the segment
   index separately on the loop-break path and the loop-exit path (two extra instructions). */
extern "C" float f_0bbc1c(float x, Obj *o) {
    float span = o->w[35].f;
    float m40 = o->w[10].f;
    float xs = x / span;
    Curve *c = (Curve *)o->w[0].p;
    float a = m40 / span;
    int i = 0;
    float t;
    do {
        t = (float)(i + 1) * 500.0f;
        if (xs <= t) break;
        i++;
    } while (i < 20);
    float f1 = 0.0f;
    if (i - 1 > 0) f1 = c->w[i].f;
    float f0 = c->w[i + 1].f;
    float d = t - a;
    f1 = f1 - f0;
    f1 = f1 * d;
    f1 = f1 / 500.0f;
    f0 = f0 + f1;
    return f0 * span;
}

/* @draft 0x0bc138 us f_0bc138
   WHAT IT DOES: the per-frame ramp of the state record: while the mode gate holds, it tracks
   the lateral offset, accumulates a clamped step into word 43, and counts word 42 down to
   zero, raising word 41 every eighth step.
   Remaining difference: not yet scored. */
extern "C" void f_0bc138(Obj *o, float x) {
    Curve *c = (Curve *)o->w[0].p;
    o->w[41].i = 0;
    if (o->w[7].f < 0.001f) {
        float t = c->w[31].f * o->w[35].f - 2000.0f;
        if (t < o->w[10].f && o->w[2].i != 1) {
            float e = x - o->w[10].f;
            if (e < 0.0f) {
                o->w[44].f = 0.0f;
                o->w[43].f = 0.0f;
            } else {
                float r = e - o->w[44].f;
                float g = 0.0f;
                if (0.0f < r) g = r;
                float s = o->w[43].f + g;
                o->w[43].f = s;
                if (10.0f < s) {
                    o->w[43].f = 0.0f;
                    o->w[42].i += 7;
                }
                o->w[44].f = e;
            }
        }
    } else {
        o->w[42].i = 0;
        o->w[43].f = 0.0f;
        o->w[44].f = 0.0f;
    }
    int v = o->w[42].i;
    if (v > 0) {
        v = v - 1;
        o->w[42].i = v;
        if ((v & 7) == 0) o->w[41].i = 1;
    }
}

/* @draft 0x0bc240 us f_0bc240
   WHAT IT DOES: updates the two-value smoothing state of the object from the curve lookup at
   its span, with a clamp on the stored value and a second smoothed pair held in words 36 and 37.
   Remaining difference: not yet scored. */
extern "C" void f_0bc240(Obj *o, int a1) {
    int s1 = (o->w[2].i == 0) ? a1 : 0;
    if (s1 <= 0) {
        o->w[39].f = 0.0f;
    } else {
        float f = o->w[39].f + 1.0f;
        if (f < 7.0f) f = 7.0f;
        o->w[39].f = f;
    }
    float r = f_0bbc1c(o->w[10].f, o);
    float q = (float)(7 - s1) * 15.0f;
    float d = r - q;
    float e;
    if (0.0f < d) {
        e = d / o->w[38].f;
        float g = e;
        if (1.0f < e) g = 1.0f;
        float b = 1.0f - g;
        e = 1.0f - b * b;
    } else {
        e = d * 0.6000000238418579f / o->w[38].f;
    }
    float k = 0.49000000953674316f;
    float f0 = o->w[39].f / 7.0f - 0.5f;
    float f3 = f0 + f0;
    if (!(0.0f < f3)) {
        k = 0.49000000953674316f;
    } else {
        k = 0.699999988079071f;
    }
    float f2 = e * 0.30000001192092896f + f3 * k;
    float f4 = o->w[36].f;
    if (0.0f < f2) f2 = f2 * o->w[40].f;
    f2 = f2 - f4;
    f2 = f2 * 0.23999999463558197f;
    float B = o->w[37].f + f2;
    float C = B - B * 0.30000001192092896f;
    o->w[37].f = C;
    o->w[36].f = f4 + C;
}
