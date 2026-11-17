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
void f_0bc138(Obj *o, float x);
void f_0bb480(Obj *o, int a1, int a2, int a3);
void f_0bb840(Obj *o, int a1, int a2, int a3);
void f_0bc3e0(Obj *o, float a, float b);
void f_0bbcb0(Obj *o, int a1, float a, float b);
}

/* @draft 0x0bbc1c us f_0bbc1c
   WHAT IT DOES: looks up a point on the car's curve. It finds the first table segment whose
   end is at or above x (segments are 500 units wide), then interpolates between the two
   table values at its ends and scales the result by the car's span (word 35).
   Remaining difference: 13 of 37 words differ, all FP register numbering (retail puts the 500.0
   constant in $f1 and the span quotient in $f2; here they are swapped). */
extern "C" float f_0bbc1c(float x, Obj *o) {
    float span = o->w[35].f;
    float m40 = o->w[10].f;
    float xs = x / span;
    Curve *c = (Curve *)o->w[0].p;
    float a = m40 / span;
    int i = 0, j;
    float t;
    for (;;) {
        t = (float)(i + 1) * 500.0f;
        if (xs <= t) { j = i - 1; break; }
        i++;
        if (i >= 20) { j = i - 1; break; }
    }
    float f1 = 0.0f;
    if (j > 0) f1 = c->w[j].f;
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
   Remaining difference: 62/67 words differ, first at +0x4; size 268 vs 264 (first transcription, not yet iterated). */
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
   Remaining difference: 75/104 words differ, first at +0x8; size 404 vs 416; bad refs: +0x18c: refers to 0xbc298, retail 0xbc304 (first transcription, not yet iterated). */
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

/* @draft 0x0bc3e0 us f_0bc3e0
   WHAT IT DOES: the curve-step update used when the car is steered by a pair of scaled inputs:
   it stores the two inputs divided by 0.32, derives the target position on the curve from the
   first, steps the segment index up or down according to the mode and the table bounds, clamps
   the index to the table, and writes the resulting position (word 10) and its scaled value
   (word 11).
   Remaining difference (123/205): the mode test now falls through to the mode != 0 arm as in
   retail (the two `goto clamp`s had made the bp pass predict that arm unlikely). Retail keeps
   idx out of saved registers (a1, reloaded from o->w[4] after each f_0bbc1c call) and keeps
   old*4 in s3 for c[20 + old]; ending each call block with `idx = o->w[4].i;` gets the a1 idx
   but grows the function to 840 B (199 words), so it was not kept. */
extern "C" void f_0bc3e0(Obj *o, float a, float b) {
    int old = o->w[4].i;
    Curve *c = (Curve *)o->w[0].p;
    int mode = o->w[2].i;
    int idx = old;
    float xa = a / 0.32f;
    o->w[22].f = xa;
    o->w[24].f = b / 0.32f;
    float x = xa * (c->w[21 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
    if (mode != 0) {
        if (o->w[33].i == 2) {
            o->w[2].i = 0;
        } else {
            int n = o->w[3].i - 1;
            o->w[3].i = n;
            if (n <= 0) {
                o->w[2].i = 0;
                o->w[5].f = 1.0f;
            } else if (n < 11) {
                if (mode == 3) o->w[2].i = 0;
            }
        }
    } else if (0.0f < o->w[5].f) {
    if (0.01f < o->w[9].f) {
        if (c->w[36 + old].f <= x) {
            idx = old + 1;
            o->w[4].i = idx;
        } else if (old > 0) {
            float F = o->w[22].f * (c->w[20 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
            float lo = f_0bbc1c(x, o);
            idx = o->w[4].i;
            if (F < c->w[36 + idx].f - 500.0f) {
                if (f_0bbc1c(x, o) < lo) {
                    idx = o->w[4].i - 1;
                    o->w[4].i = idx;
                }
            }
        }
    }
    if (old == idx) {
        if (x <= c->w[43].f) {
            idx = old - 1;
            o->w[4].i = idx;
        } else if (idx > 0) {
            float F = o->w[20].f * (c->w[20 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
            float lo = f_0bbc1c(F, o);
            idx = o->w[4].i;
            if (F < c->w[36 + idx].f - 500.0f) {
                if (f_0bbc1c(x, o) < lo) {
                    idx = o->w[4].i - 1;
                    o->w[4].i = idx;
                }
            }
        }
    }
    }
    {
        int hi = c->w[30].i - 1;
        if (hi < idx) {
            o->w[4].i = hi;
            idx = hi;
        }
        if (idx < 0) {
            o->w[4].i = 0;
            idx = 0;
        }
    }
    if (old != idx) {
        o->w[2].i = 1;
        if (idx < old) o->w[2].i = 2;
        o->w[3].i = 12;
        o->w[5].f = 0.0f;
    }
    {
        float p = o->w[22].f * (c->w[21 + idx].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
        o->w[10].f = p;
        o->w[11].f = p * c->w[33].f;
    }
}

/* @draft 0x0bb480 us f_0bb480
   WHAT IT DOES: steps the car's curve segment index. While a lane-change mode is active it
   watches the lateral speed against plus and minus 20 and counts the mode down; otherwise
   it moves the index up or down on request, or from the position against the table
   thresholds, then clamps it to the table and records the direction of any change.
   Remaining difference: 191/243 words differ, first at +0x0; size 972 vs 960 (first transcription, not yet iterated). */
extern "C" void f_0bb480(Obj *o, int a1, int a2, int a3) {
    int old = o->w[4].i;
    int mode = o->w[2].i;
    Curve *c = (Curve *)o->w[0].p;
    int idx = old;
    if (mode != 0) {
        if (o->w[33].i == 2) {
            o->w[2].i = 0;
            goto tail;
        }
        {
            float v = (o->w[22].f - o->w[20].f) / (o->w[35].f * 0.016666668f);
            float av = v < 0.0f ? -v : v;
            if (av < 20.0f) {
                mode = 3;
                o->w[2].i = 3;
                o->w[5].f = 1.0f;
            }
            bool hit;
            if (mode == 1) hit = -20.0f < v;
            else hit = v < 20.0f;
            if (hit) {
                o->w[2].i = 3;
                o->w[5].f = 1.0f;
            }
        }
        {
            int n = o->w[3].i - 1;
            o->w[3].i = n;
            if (n <= 0) {
                o->w[2].i = 0;
                o->w[5].f = 1.0f;
                goto tail;
            }
            if (n < 11 && o->w[2].i == 3) o->w[2].i = 0;
        }
        goto tail;
    }
    if (o->w[1].i != 0) {
        if (a1 != 0) {
            idx = old + 1;
            o->w[4].i = idx;
        } else if (a2 != 0) {
            idx = old - 1;
            o->w[4].i = idx;
        }
        goto clamp;
    }
    if (!(0.0f < o->w[5].f)) goto clamp;
    if (0.01f < o->w[9].f) {
        float x = o->w[10].f;
        if (c->w[36 + old].f <= x) {
            if (a3 == 4 && -1500.0f < o->w[27].f && 0.95f < o->w[6].f) {
                idx = old + 1;
                o->w[4].i = idx;
            }
        } else if (old > 0) {
            float F = o->w[20].f * (c->w[20 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
            float lo = f_0bbc1c(x, o);
            idx = o->w[4].i;
            if (F < c->w[36 + idx].f - 500.0f) {
                if (f_0bbc1c(o->w[10].f, o) < lo) {
                    idx = o->w[4].i - 1;
                    o->w[4].i = idx;
                }
            }
        }
    }
    if (old == idx) {
        if (o->w[10].f <= c->w[43].f) {
            idx = old - 1;
            o->w[4].i = idx;
        } else if (old > 0) {
            float F = o->w[20].f * (c->w[20 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
            float lo = f_0bbc1c(F, o);
            idx = o->w[4].i;
            if (F < c->w[36 + idx].f - 500.0f) {
                if (f_0bbc1c(o->w[10].f, o) < lo) {
                    idx = o->w[4].i - 1;
                    o->w[4].i = idx;
                }
            }
        }
    }
clamp:
    {
        int hi = c->w[30].i - 1;
        if (hi < idx) {
            o->w[4].i = hi;
            idx = hi;
        }
        if (idx < 0) {
            o->w[4].i = 0;
            idx = 0;
        }
    }
tail:
    if (old != idx) {
        o->w[2].i = 1;
        if (idx < old) o->w[2].i = 2;
        o->w[3].i = 12;
        o->w[5].f = 0.0f;
    }
}

/* @draft 0x0bb840 us f_0bb840
   WHAT IT DOES: the sibling of the segment index step above, with the 0.95 gate moved from
   the step-up test to the repeat test and an extra step-down test in the lower branch.
   Remaining difference: 193/250 words differ, first at +0x0; size 1000 vs 988 (first transcription, not yet iterated). */
extern "C" void f_0bb840(Obj *o, int a1, int a2, int a3) {
    int old = o->w[4].i;
    int mode = o->w[2].i;
    Curve *c = (Curve *)o->w[0].p;
    int idx = old;
    if (mode != 0) {
        if (o->w[33].i == 2) {
            o->w[2].i = 0;
            goto tail;
        }
        {
            float v = (o->w[22].f - o->w[20].f) / (o->w[35].f * 0.016666668f);
            float av = v < 0.0f ? -v : v;
            if (av < 20.0f) {
                mode = 3;
                o->w[2].i = 3;
                o->w[5].f = 1.0f;
            }
            bool hit;
            if (mode == 1) hit = -20.0f < v;
            else hit = v < 20.0f;
            if (hit) {
                o->w[2].i = 3;
                o->w[5].f = 1.0f;
            }
        }
        {
            int n = o->w[3].i - 1;
            o->w[3].i = n;
            if (n <= 0) {
                o->w[2].i = 0;
                o->w[5].f = 1.0f;
                goto tail;
            }
            if (n < 11 && o->w[2].i == 3) o->w[2].i = 0;
        }
        goto tail;
    }
    if (o->w[1].i != 0) {
        if (a1 != 0) {
            idx = old + 1;
            o->w[4].i = idx;
        } else if (a2 != 0) {
            idx = old - 1;
            o->w[4].i = idx;
        }
        goto clamp;
    }
    if (!(0.0f < o->w[5].f)) goto clamp;
    if (0.01f < o->w[9].f) {
        float x = o->w[10].f;
        if (c->w[36 + old].f <= x) {
            if (a3 == 4 && -1500.0f < o->w[27].f) {
                idx = old + 1;
                o->w[4].i = idx;
            }
        } else if (x <= c->w[43].f) {
            idx = old - 1;
            o->w[4].i = idx;
        } else if (old > 0) {
            float F = o->w[20].f * (c->w[20 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
            float lo = f_0bbc1c(x, o);
            idx = o->w[4].i;
            if (F < c->w[36 + idx].f - 500.0f) {
                if (f_0bbc1c(o->w[10].f, o) < lo) {
                    idx = o->w[4].i - 1;
                    o->w[4].i = idx;
                }
            }
        }
    }
    if (old == idx && 0.95f < o->w[6].f) {
        if (o->w[10].f <= c->w[43].f) {
            idx = old - 1;
            o->w[4].i = idx;
        } else if (old > 0) {
            float F = o->w[20].f * (c->w[20 + old].f * c->w[29].f) * 60.0f / 6.2831855f + c->w[32].f;
            float lo = f_0bbc1c(F, o);
            idx = o->w[4].i;
            if (F < c->w[36 + idx].f - 500.0f) {
                if (f_0bbc1c(o->w[10].f, o) < lo) {
                    idx = o->w[4].i - 1;
                    o->w[4].i = idx;
                }
            }
        }
    }
clamp:
    {
        int hi = c->w[30].i - 1;
        if (hi < idx) {
            o->w[4].i = hi;
            idx = hi;
        }
        if (idx < 0) {
            o->w[4].i = 0;
            idx = 0;
        }
    }
tail:
    if (old != idx) {
        o->w[2].i = 1;
        if (idx < old) o->w[2].i = 2;
        o->w[3].i = 12;
        o->w[5].f = 0.0f;
    }
}

/* @draft 0x0bbcb0 us f_0bbcb0
   WHAT IT DOES: the main per-frame curve update of a car: it looks up the curve at the current
   position, derives the lateral push (word 16) from the offset and the inputs, integrates the
   speed (word 14) and the acceleration terms (words 17 to 20, 27), advances the position
   (word 10) by the speed with one of three smoothing rules, clamps it to the span of the
   table, runs the ramp update f_0bc138 and stores the scaled position (word 11).
   Remaining difference: 263/290 words differ, first at +0x50; size 1128 vs 1160 (first transcription, not yet iterated). */
extern "C" void f_0bbcb0(Obj *o, int a1, float a, float b) {
    Curve *c = (Curve *)o->w[0].p;
    float x = o->w[10].f;
    float lim = c->w[31].f * o->w[35].f;
    float r = f_0bbc1c(x, o);
    o->w[15].f = r;
    o->w[14].f = r;
    float p = o->w[10].f;
    float p0 = p;
    if (lim <= p) o->w[14].i = 0;
    float zero = 0.0f;
    if (zero < p) {
        float spd = o->w[7].f;
        if (spd < 0.01f || lim <= p) {
            float t = -((p - c->w[32].f) * 0.003f * c->w[35].f);
            o->w[16].f = t;
            if (b < 20.0f) {
                float k = o->w[5].f;
                o->w[16].f = t * (b * 0.025f + (1.0f - k * 0.5f) * 0.5f);
            }
            if (1.0f < b) {
                float m = a < zero ? -a : a;
                if (1.5707964f < m) o->w[16].f = -o->w[16].f;
            }
        } else {
            o->w[16].i = 0;
        }
    } else {
        o->w[16].i = 0;
    }
    {
        float spd = o->w[7].f;
        float k = o->w[5].f;
        int idx = o->w[4].i;
        float v = o->w[14].f * spd + o->w[16].f;
        o->w[14].f = v;
        float acc = v * c->w[21 + idx].f * c->w[29].f;
        o->w[17].f = acc;
        float g = acc * 9.8f * 3.125f;
        o->w[18].f = g;
        float f12;
        float dv;
        if (0.1f < k) {
            float sc = c->w[21 + idx].f * c->w[29].f;
            f12 = o->w[22].f;
            o->w[19].f = g;
            float tgt = f12 * sc;
            if (a1 != 0) {
                float e = tgt - o->w[12].f;
                float w = k * o->w[6].f * 0.95f;
                e = e / 0.016666668f * 0.2f * w;
                float h = (v * (1.0f - w)) / c->w[34].f + e;
                o->w[13].f = h;
                float ang = o->w[12].f + h * 0.016666668f;
                o->w[12].f = ang;
                o->w[19].f = g * k;
                o->w[10].f = ang * 60.0f / 6.2831855f + c->w[32].f;
                float ratio = ang / (c->w[21 + idx].f * c->w[29].f);
                o->w[20].f = ratio;
                o->w[27].f = (f12 - ratio) / 0.016666668f;
            } else {
                o->w[19].i = 0;
                float h = v / (c->w[34].f + 0.03f);
                o->w[13].f = h;
                float ang = (p0 - c->w[32].f) / 60.0f * 6.2831855f + h * 0.016666668f;
                o->w[12].f = ang;
                o->w[10].f = ang * 60.0f / 6.2831855f + c->w[32].f;
                float ratio = ang / (c->w[21 + idx].f * c->w[29].f);
                o->w[20].f = ratio;
                o->w[27].f = (f12 - ratio) / 0.016666668f;
            }
        } else {
            o->w[19].i = 0;
            dv = c->w[34].f;
            if (o->w[33].i == 2) {
                if (o->w[19].f < v) dv = dv * 0.2f;
                else dv = dv * 0.7f;
            }
            float h = v / dv;
            o->w[13].f = h;
            f12 = o->w[22].f;
            float ang = (p0 - c->w[32].f) / 60.0f * 6.2831855f + o->w[13].f * 0.016666668f;
            o->w[12].f = ang;
            o->w[10].f = ang * 60.0f / 6.2831855f + c->w[32].f;
            float ratio = ang / (c->w[21 + idx].f * c->w[29].f);
            o->w[20].f = ratio;
            o->w[27].f = (f12 - ratio) / 0.016666668f;
        }
    }
    {
        float q = o->w[10].f;
        if (lim < q) {
            o->w[10].f = lim;
            q = lim;
            o->w[12].f = (lim - c->w[32].f) / 60.0f * 6.2831855f;
        }
        if (q < c->w[32].f) o->w[10].f = c->w[32].f;
    }
    f_0bc138(o, x);
    o->w[11].f = o->w[10].f * c->w[33].f;
}
