/* Car light trails (retail 0x026ffc to 0x0277c4): every other frame the car's light table
   records the car's matrix and the brightness of its six lamps (four at the front, two at the
   back); lamps that are still lit are drawn as fading strips through the last eight recorded
   positions. Also here: the GE lists that frame the trails' drawing. */

#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

struct Mat {
    float m[16];
};

/* One lamp of the car's light description (36 bytes): which lamp it is, and the two ends of
   its strip with their colours. */
struct LampDesc {
    int lamp;
    float a[3];
    unsigned int colourA;
    float b[3];
    unsigned int colourB;
};

struct LampSet {
    unsigned int count;
    LampDesc lamp[1];
};

/* One recorded step: the car's matrix, the six lamp levels, and whether the step is empty. */
struct LightStep {
    Mat m;
    short level[6];
    short empty;
    short m78;
};

/* The car's light table. */
struct LightTable {
    LampSet *lamps;
    int m4[3];
    LightStep step[8];
    float bright[6];
    unsigned char done[6];
    signed char phase;
};

/* One trail vertex: colour, then position. */
struct TrailVertex {
    unsigned char c[4];
    float x, y, z;
};

extern "C" {
void *f_021b38(int size);
unsigned int *f_02df08(unsigned int *p);
unsigned int *f_02dba8(unsigned int *p);
}

/* Stores a colour byte by byte (the vertex buffer is not word aligned for the GE's sake). */
static inline void PutColour(unsigned char *d, unsigned int c)
{
    d[2] = c >> 16;
    d[3] = c >> 24;
    d[0] = c;
    d[1] = c >> 8;
}

/* @draft 0x026ffc us f_026ffc
   WHAT IT DOES: Draws and records the car's light trails. For every lamp that has not faded
   out it builds a triangle strip through the recorded steps, newest first, stopping at an
   empty step: both ends of the lamp are taken through each step's matrix, and the alpha ramps
   up by 128 per step but never above the lamp's level at that step; strips of at least two
   steps are drawn. Then it records the current step: with no matrix the step is emptied;
   otherwise the lamps' levels are their brightness scaled by how far the car is in front of
   the viewer (full up to 10000 units, fading out from 10000 to 100000, off when behind or when
   the car is hidden) and by which way it faces (front lamps when facing the viewer, rear lamps
   when facing away), and the matrix is kept. Returns the end of the GE list. */
unsigned int *f_026ffc(LightTable *t, const Mat *m, signed char visible, unsigned int *p)
{
    LightStep *s;
    unsigned int i;

    if (t->lamps == 0)
        return p;
    for (i = 0; i < t->lamps->count; i++) {
        LampDesc *d = &t->lamps->lamp[i];
        TrailVertex *v, *buf;
        unsigned int alpha;
        int n, j;

        if (t->done[d->lamp])
            continue;
        if (t->phase)
            s = &t->step[(t->phase - 1) / 2];
        else
            s = &t->step[7];
        buf = v = (TrailVertex *)f_021b38(256);
        alpha = 0;
        n = 0;
        for (j = 0; j < 8; j++) {
            unsigned int lv;

            if (s->empty)
                break;
            lv = s->level[d->lamp];
            if (lv < alpha)
                alpha = lv;
            __asm__ volatile(VFPU_BEGIN "lv.q C300, 0(%1)\n\tlv.q C310, 16(%1)\n\tlv.q C320, 32(%1)\n\tlv.q C330, 48(%1)\n\t"
                             "lv.s S400, 4(%2)\n\tlv.s S401, 8(%2)\n\tlv.s S402, 12(%2)\n\t"
                             "vtfm3.t C410, E300, C400\n\tvadd.t C420, C330, C410\n\t"
                             "sv.s S420, 4(%0)\n\tsv.s S421, 8(%0)\n\tsv.s S422, 12(%0)\n\t"
                             "lv.s S400, 20(%2)\n\tlv.s S401, 24(%2)\n\tlv.s S402, 28(%2)\n\t"
                             "vtfm3.t C410, E300, C400\n\tvadd.t C420, C330, C410\n\t"
                             "sv.s S420, 20(%0)\n\tsv.s S421, 24(%0)\n\tsv.s S422, 28(%0)" VFPU_END
                             : : "r"(v), "r"(s), "r"(d) : "memory");
            PutColour(v[0].c, d->colourA | alpha << 24);
            PutColour(v[1].c, d->colourB | alpha << 24);
            n++;
            alpha += 128;
            if (s == &t->step[0])
                s = &t->step[8];
            v += 2;
            s--;
        }
        if (n < 2)
            continue;
        *p = 0x1200019c;
        p++;
        *p = (((unsigned int)buf >> 24) & 0xf) << 16 | 0x10000000;
        p++;
        *p = ((unsigned int)buf & 0xffffff) | 0x01000000;
        p++;
        *p = (n * 2) | 0x04040000;
        p++;
    }

    s = &t->step[t->phase / 2];
    if (m == 0) {
        for (i = 0; i < 6; i++)
            s->level[i] = 0;
        s->empty = 1;
        return p;
    }
    {
        float k = 0.0f;
        float front, back;

        if (visible) {
            float z = m->m[14];
            if (!(0.0f < z)) {
                if (-10000.0f < z)
                    k = 1.0f;
                else if (-100000.0f < z)
                    k = (z + 100000.0f) / 90000.0f;
            }
        }
        if (0.0f < k && k <= 1.0f) {
            front = 0.0f;
            back = -m->m[10];
            if (0.0f < m->m[10]) {
                back = front;
                front = m->m[10];
            }
            front *= k;
            back *= k;
            s->level[0] = (unsigned int)(t->bright[0] * front) & 0xff;
            s->level[1] = (unsigned int)(t->bright[1] * front) & 0xff;
            s->level[2] = (unsigned int)(t->bright[2] * front) & 0xff;
            s->level[3] = (unsigned int)(t->bright[3] * front) & 0xff;
            s->level[4] = (unsigned int)(t->bright[4] * back) & 0xff;
            s->level[5] = (unsigned int)(t->bright[5] * back) & 0xff;
        } else {
            for (i = 0; i < 6; i++)
                s->level[i] = 0;
        }
        s->m = *m;
        s->empty = 0;
    }
    return p;
}

/* @implements 0x027524 us f_027524
   WHAT IT DOES: Writes the GE state for drawing the light trails: identity view and world
   matrices, then depth, culling, texturing and lighting off, additive blending with alpha, and
   blending on, followed by the common trail state (f_02df08). Returns the end of the list. */
unsigned int *f_027524(unsigned int *p)
{
    *p = 0x3c000000;
    p++;
    *p = 0x3d3f8000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d3f8000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d3f8000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3d000000;
    p++;
    *p = 0x3a000000;
    p++;
    *p = 0x3b3f8000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b3f8000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b3f8000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x3b000000;
    p++;
    *p = 0x1d000000;
    p++;
    *p = 0x1f000000;
    p++;
    *p = 0x1e000000;
    p++;
    *p = 0x17000000;
    p++;
    *p = 0xe7000001;
    p++;
    *p = 0xdf0000a2;
    p++;
    *p = 0xe1ffffff;
    p++;
    *p = 0x21000001;
    p++;
    return f_02df08(p);
}

/* @implements 0x02769c us f_02769c
   WHAT IT DOES: Ends the light trails' drawing: uploads the given view matrix again (if any),
   writes the depth mask command and the common closing state (f_02dba8). Returns the end of
   the list. */
unsigned int *f_02769c(unsigned int *p, const Mat *v)
{
    if (v) {
        *p = 0x3c000000;
        p++;
        *p = (*(const unsigned int *)&v->m[0] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[1] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[2] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[4] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[5] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[6] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[8] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[9] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[10] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[12] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[13] >> 8) | 0x3d000000;
        p++;
        *p = (*(const unsigned int *)&v->m[14] >> 8) | 0x3d000000;
        p++;
    }
    *p = 0xe7000000;
    p++;
    return f_02dba8(p);
}
