/* Car to car collision (retail 0x0c66f4 to 0x0c801c): every car carries a hit model, a
   convex outline of up to sixteen points (x and z, in the car's own frame) inside a bounding
   circle. The outline of a car is turned into the world frame, the two outlines of a pair
   are tested against each other, and a hit leaves the cars a push (an accumulated vector
   along the hit edge, a turn angle taken from the contact point, and a strength) and the
   hit flag at +1952. */

extern "C" {
void f_099b98(void *a);
void f_09b394(int angle, float *x, float *y);
float f_09a9dc(float z, float x);
float f_09a218(float a);
float f_0a65c4(const void *v);
void *f_0a5e6c(void *d, const void *a, const void *b);
void *f_0a5e88(void *d, const void *a, const void *b);
void *f_0a5dc8(void *d, const void *b);
void *f_0a5de4(void *d, const void *b);
void *f_0a5e1c(void *d, float s);
float sqrtf(float);
int f_0c67e8(struct Car *a, struct Car *b, int mode);
}

static inline float FAbs(float x)
{
    return x < 0.0f ? -x : x;
}

struct P2 {
    float x, z;
};

/* An angle in radians, wrapped into range by f_099b98 when made. */
union Angle {
    float a;
    Angle(float r) : a(r) { f_099b98(this); }
};

struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};

struct HitPoint {
    float x, z;
};

/* The hit model inside a car's model record (at +112): the point count, the radius of the
   bounding circle and the outline points. */
struct HitModel {
    int count;
    char pad4[8];
    float radius;
    HitPoint pt[16];
};

struct CarModel {
    char pad0[112];
    HitModel hit;
};

/* A point or vector in the plane (x and z); the compiler spaces these 16 bytes apart. */
struct V2 {
    float x, z;
} __attribute__((aligned(16)));

struct Car {
    char pad0[76];
    int m76;
    unsigned char m80;
    char pad81[47];
    int m128;
    char pad132[12];
    Vec4 m144;
    Vec4 m160;
    char pad176[1920 - 176];
    Vec4 m1920;
    Vec4 m1936;
    int m1952;
    int pad1956;
    float m1960;
    float m1964;
    char pad1968[2136 - 1968];
    float m2136;
    char pad2140[2752 - 2140];
    CarModel *m2752;
};

/* @implements 0x0c66f4 us f_0c66f4
   WHAT IT DOES: Writes the outline points of a car's hit model (at +112 of the model record)
   into out as world vectors: each point (x, 0, z, 1) is turned about the vertical axis by
   the angle at *ang and then moved by the vector at pos. The position is added through float
   pointers, as retail does. */
extern "C" void f_0c66f4(CarModel *m, Vec4 *pos, float *ang, Vec4 *out)
{
    HitModel *h = &m->hit;
    int i;
    for (i = 0; i < h->count; i++) {
        Vec4 *o = &out[i];
        float px = h->pt[i].x, pz = h->pt[i].z;
        o->x = px;
        o->y = 0.0f;
        o->z = pz;
        o->w = 1.0f;
        Angle a(*ang);
        f_09b394(*(int *)&a, &o->z, &o->x);
        float *of = &o->x;
        float *pf = &pos->x;
        of[0] += pf[0];
        of[1] += pf[1];
        of[2] += pf[2];
    }
}

/* @draft 0x0c67e8 us f_0c67e8
   DRAFT: complete transcription (every path), size 5228 vs 5596; every word is graded
   different because the register allocation and frame differ from the start: retail keeps
   the two cars in stack slots (672, 676) and the two hit model pointers in 680/684, here the
   cars sit in s7/s8; retail declares eight vector temporaries (one per copy in the
   normalise-and-scale chains at +0x8f0 and +0xd20, which here are scalar code), and keeps
   the ranges and sides as memory resident vectors that the loop optimiser promotes (the
   loads before the edge loop at +0x31c). About 1120 of 1399 instructions agree in
   opcode order. Third parameter: unused in the body, but the pair loop at 0x0c7dc4 passes 0.
   WHAT IT DOES: Tests the outlines of two cars against each other. The cars' positions (with
   their pending push at +1936) give the distance between them: beyond the sum of the two
   bounding radii there is no hit, and below 1 the cars are moved apart by 10 each so the
   direction is defined. The hit model is the record at +0 of the car's model when either car
   has bit 0 of the byte at +80 set, otherwise the one at +112. Each outline is turned by its
   car's heading, B moved to its offset from A. The outlines hit when an edge of one crosses
   an edge of the other (collinear edges count when their boxes overlap), or when A's centre
   lies inside B. On a hit the frame is turned so the line between the cars is an axis, and
   every vertex of one outline is tested against every edge of the other to find the deepest
   penetration (the vertex, the edge, the depth, the contact points in each car's frame and
   the penetration vector). The vector is lengthened by 10 (or set to 100 along x when tiny)
   and cut to the sum of the radii when longer. Each car's push (+1936) is set to the vector
   scaled by a share taken from the lengths of the two cars' vectors at +160; the part of the
   centre offset across the hit edge is added to one car's accumulated push (+1920) and taken
   from the other; each gets a turn angle (+1960) from its contact point and a strength
   (+1964) of its push times 0.01. Returns 1 on a hit (and sets the hit flag at +1952 of both
   when an edge crossed), 0 otherwise. */
extern "C" int f_0c67e8(Car *a, Car *b, int mode)
{
    P2 minA, maxA, minB, maxB;
    float side1, side2, t40, t44, prod1, prod2;
    float ax[16], az[16], bx[16], bz[16];
    float ux, uz;
    V2 u, v, e;
    Vec4 pa, pb, d, tmp;
    short i, j, i1, j1;

    HitModel *ha, *hb;
    if (!(a->m80 & 1) && !(b->m80 & 1)) {
        ha = &a->m2752->hit;
        hb = &b->m2752->hit;
    } else {
        ha = (HitModel *)a->m2752;
        hb = (HitModel *)b->m2752;
    }
    short nA = ha->count;
    short nB = hb->count;
    float yawA = a->m2136;
    float yawB = b->m2136;
    f_0a5e6c(&pa, &a->m144, &a->m1936);
    f_0a5e6c(&pb, &b->m144, &b->m1936);
    f_0a5e88(&d, &pb, &pa);
    float rr = ha->radius + hb->radius;
    if (rr < f_0a65c4(&d))
        return 0;
    float len = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
    if (len < 1.0f) {
        pa.x += 10.0f;
        pb.x += -10.0f;
        pa.z += 10.0f;
        pb.z += -10.0f;
        d = Vec4(pb.x - pa.x, pb.y - pa.y, pb.z - pa.z, 1.0f);
    }
    for (i = 0; i < nA; i++) {
        ux = ha->pt[i].x;
        uz = ha->pt[i].z;
        Angle ang(-yawA);
        f_09b394(*(int *)&ang, &ux, &uz);
        ax[i] = ux;
        az[i] = uz;
    }
    for (j = 0; j < nB; j++) {
        ux = hb->pt[j].x;
        uz = hb->pt[j].z;
        Angle ang(-yawB);
        f_09b394(*(int *)&ang, &ux, &uz);
        bx[j] = ux + d.x;
        bz[j] = uz + d.z;
    }
    int hit = 0;
    if (nA > 0) {
    }
    for (i = 0; i < nA; i++) {
        i1 = (i + 1) % nA;
        for (j = 0; j < nB; j++) {
            j1 = (j + 1) % nB;
            float ex = ax[i] - ax[i1];
            float ez = az[i] - az[i1];
            side1 = ex * (bz[j] - az[i]) + ez * (ax[i] - bx[j]);
            side2 = ex * (bz[j1] - az[i]) + ez * (ax[i] - bx[j1]);
            prod1 = side1 * side2;
            if (!(0.0f < prod1))
                goto crossing;
            continue;
        crossing:
            float fx = bx[j] - bx[j1];
            float fz = bz[j] - bz[j1];
            side1 = fx * (az[i] - bz[j]) + fz * (bx[j] - ax[i]);
            side2 = fx * (az[i1] - bz[j]) + fz * (bx[j] - ax[i1]);
            prod2 = side1 * side2;
            if (0.0f < prod2)
                continue;
            if (FAbs(prod1) < 1.1920929e-07f && FAbs(prod2) < 1.1920929e-07f) {
                if (ax[i1] < ax[i]) {
                    minA.x = ax[i1];
                    maxA.x = ax[i];
                } else {
                    minA.x = ax[i];
                    maxA.x = ax[i1];
                }
                if (bx[j1] < bx[j]) {
                    minB.x = bx[j1];
                    maxB.x = bx[j];
                } else {
                    minB.x = bx[j];
                    maxB.x = bx[j1];
                }
                if (maxB.x < minA.x || maxA.x < minB.x)
                    continue;
                if (az[i1] < az[i]) {
                    minA.z = az[i1];
                    maxA.z = az[i];
                } else {
                    minA.z = az[i];
                    maxA.z = az[i1];
                }
                if (bz[j1] < bz[j]) {
                    minB.z = bz[j1];
                    maxB.z = bz[j];
                } else {
                    minB.z = bz[j];
                    maxB.z = bz[j1];
                }
                if (maxB.z < minA.z || maxA.z < minB.z)
                    continue;
            }
            hit = 1;
            a->m1952 = hit;
            b->m1952 = hit;
            i = nA;
            j = nB;
        }
    }
    if (!hit) {
        prod2 = sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
        if (ha->radius < prod2)
            return 0;
        for (j = 0; j < nB; j++) {
            j1 = (j + 1) % nB;
            prod1 = bx[j] * bz[j1] - bx[j1] * bz[j];
            if (0.0f < prod1)
                return 0;
        }
    }
    float theta = f_09a9dc(-d.x, -d.z);
    for (i = 0; i < nA; i++) {
        u.x = ax[i];
        u.z = az[i];
        Angle ang(theta);
        f_09b394(*(int *)&ang, &u.x, &u.z);
        ax[i] = u.x;
        az[i] = u.z;
    }
    for (j = 0; j < nB; j++) {
        u.x = bx[j];
        u.z = bz[j];
        Angle ang(theta);
        f_09b394(*(int *)&ang, &u.x, &u.z);
        bx[j] = u.x;
        bz[j] = u.z;
    }
    V2 p0, p1, n;
    float best;
    int bestA, bestB, flag;
    best = n.z = n.x = p1.z = p1.x = p0.z = p0.x = 0.0f;
    bestA = bestB = -1;
    flag = 1;
    for (i = 0; i < nA; i++) {
        for (j = 0; j < nB; j++) {
            int jm = (j + 1) % nB;
            if (bz[j] < az[i] && bz[jm] < az[i])
                continue;
            int lo = j, hi = jm;
            if (bx[jm] < bx[j]) {
                lo = jm;
                hi = j;
            }
            if (ax[i] < bx[lo])
                continue;
            if (bx[hi] < ax[i])
                continue;
            prod1 = (bx[hi] - bx[lo]) * (az[i] - bz[lo]) - (bz[hi] - bz[lo]) * (ax[i] - bx[lo]);
            if (0.0f < prod1)
                continue;
            float depth;
            if (FAbs(bx[j] - bx[jm]) < 1.1920929e-07f) {
                depth = (bz[j] < bz[jm] ? bz[j] : bz[jm]) - az[i];
            } else {
                float ang = f_09a9dc(bz[jm] - bz[j], bx[jm] - bx[j]);
                depth = bz[j] + (ax[i] - bx[j]) * f_09a218(ang) - az[i];
            }
            if (depth < 0.0f)
                continue;
            u.x = ax[i];
            u.z = az[i];
            Angle t1(-theta);
            f_09b394(*(int *)&t1, &u.x, &u.z);
            v.x = ax[i];
            v.z = az[i] - depth;
            Angle t2(-theta);
            f_09b394(*(int *)&t2, &v.x, &v.z);
            e.x = u.x - v.x;
            e.z = u.z - v.z;
            u.x = u.x - d.x;
            u.z = u.z - d.z;
            Angle t3(yawB);
            f_09b394(*(int *)&t3, &u.x, &u.z);
            Angle t4(yawA);
            f_09b394(*(int *)&t4, &v.x, &v.z);
            float ad = depth < 0.0f ? -depth : depth;
            if (best < ad) {
                best = ad;
                bestA = i;
                bestB = j;
                p0 = v;
                p1 = u;
                n = e;
            }
        }
    }
    for (i = 0; i < nB; i++) {
        for (j = 0; j < nA; j++) {
            int jm = (j + 1) % nA;
            if (bz[i] < az[j] && bz[i] < az[jm])
                continue;
            int lo = j, hi = jm;
            if (ax[jm] < ax[j]) {
                lo = jm;
                hi = j;
            }
            if (bx[i] < ax[lo])
                continue;
            if (ax[hi] < bx[i])
                continue;
            prod1 = (ax[hi] - ax[lo]) * (bz[i] - az[lo]) - (az[hi] - az[lo]) * (bx[i] - ax[lo]);
            if (prod1 < 0.0f)
                continue;
            float depth;
            if (FAbs(ax[j] - ax[jm]) < 1.1920929e-07f) {
                depth = (az[j] < az[jm] ? az[j] : az[jm]) - bz[i];
            } else {
                float ang = f_09a9dc(az[jm] - az[j], ax[jm] - ax[j]);
                depth = az[j] + (bx[i] - ax[j]) * f_09a218(ang) - bz[i];
            }
            if (0.0f < depth)
                continue;
            u.x = bx[i];
            u.z = bz[i];
            Angle t1(-theta);
            f_09b394(*(int *)&t1, &u.x, &u.z);
            v.x = bx[i];
            v.z = bz[i] - depth;
            Angle t2(-theta);
            f_09b394(*(int *)&t2, &v.x, &v.z);
            e.x = v.x - u.x;
            e.z = v.z - u.z;
            v.x = v.x - d.x;
            v.z = v.z - d.z;
            Angle t3(yawA);
            f_09b394(*(int *)&t3, &u.x, &u.z);
            Angle t4(yawB);
            f_09b394(*(int *)&t4, &v.x, &v.z);
            float ad = depth < 0.0f ? -depth : depth;
            if (best < ad) {
                best = ad;
                bestA = j;
                bestB = i;
                flag = 0;
                p0 = u;
                p1 = v;
                n = e;
            }
        }
    }
    len = sqrtf(n.x * n.x + n.z * n.z);
    if (len < 0.1f) {
        n.x = 100.0f;
        n.z = 0.0f;
    } else {
        len = sqrtf(n.x * n.x + n.z * n.z);
        float k = 1.0f / len;
        n.x += n.x * k * 10.0f;
        n.z += n.z * k * 10.0f;
    }
    len = sqrtf(n.x * n.x + n.z * n.z);
    rr = ha->radius + hb->radius;
    if (rr < len) {
        n.x = ax[bestA];
        n.z = az[bestA];
        len = sqrtf(n.x * n.x + n.z * n.z);
        float k = 1.0f / len;
        n.x = n.x * k * (ha->radius + hb->radius);
        n.z = n.z * k * (ha->radius + hb->radius);
    }
    Vec4 ca = a->m160;
    Vec4 cb = b->m160;
    Vec4 dc;
    f_0a5e88(&dc, &cb, &ca);
    float la = f_0a65c4(&ca);
    float lb = f_0a65c4(&cb);
    float diff = lb - la;
    float ratio;
    if (diff < 0.0f) {
        ratio = FAbs(la) < 1.1920929e-07f ? -1.0f : diff / la;
    } else {
        ratio = FAbs(lb) < 1.1920929e-07f ? 1.0f : diff / lb;
    }
    ratio = ratio < 1.0f ? ratio : 1.0f;
    ratio = -1.0f < ratio ? ratio : -1.0f;
    float w = ratio * 0.5 + 0.5;
    a->m1936.x = n.x;
    a->m1936.z = n.z;
    a->m1936.w = 1.0f;
    a->m1936.y = 0.0f;
    b->m1936.x = -n.x;
    b->m1936.z = -n.z;
    b->m1936.w = 1.0f;
    b->m1936.y = 0.0f;
    f_0a5e1c(&a->m1936, w);
    f_0a5e1c(&b->m1936, 1.0f - w);
    {
        Vec4 g;
        V2 ed;
        if (flag) {
            Angle q(-yawB);
            HitPoint q0 = hb->pt[bestB];
            HitPoint q1 = hb->pt[(bestB + 1) % nB];
            ed.x = q1.x - q0.x;
            ed.z = q1.z - q0.z;
            f_09b394(*(int *)&q, &ed.x, &ed.z);
        } else {
            Angle q(-yawA);
            HitPoint q0 = ha->pt[bestA];
            HitPoint q1 = ha->pt[(bestA + 1) % nA];
            ed.x = q0.x - q1.x;
            ed.z = q0.z - q1.z;
            f_09b394(*(int *)&q, &ed.x, &ed.z);
        }
        float eang = f_09a9dc(ed.z, ed.x);
        g.x = dc.x;
        g.y = 0.0f;
        g.z = dc.z;
        g.w = 1.0f;
        Angle r1(eang);
        f_09b394(*(int *)&r1, &g.z, &g.x);
        g.x = 0.0f;
        Angle r2(-eang);
        f_09b394(*(int *)&r2, &g.z, &g.x);
        f_0a5dc8(&a->m1920, &g);
        f_0a5de4(&b->m1920, &g);
    }
    a->m1960 = -f_09a9dc(p0.x, -p0.z);
    b->m1960 = -f_09a9dc(p1.x, -p1.z);
    a->m1964 = f_0a65c4(&a->m1920) * 0.01f;
    b->m1964 = f_0a65c4(&b->m1920) * 0.01f;
    return 1;
}

/* @implements 0x0c7dc4 us f_0c7dc4
   WHAT IT DOES: Tests every pair of the cars that are in play (the model pointer set and the
   state not 1). First it clears each car's push vectors and hit flag, remembering which cars
   had the flag. Then each pair is run through the outline test, and a hit stores its result
   in both cars. Last, cars that had the flag keep their accumulated push without its height. */
extern "C" void f_0c7dc4(int n, Car **cars)
{
    int had[12];
    Vec4 v;
    Car *list[16];
    int i, j, m;

    for (i = 0; i < n; i++) {
        Car *c = cars[i];
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 0.0f;
        c->m1936 = v;
        had[i] = c->m1952;
        c->m1952 = 0;
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 0.0f;
        c->m1920 = v;
    }
    m = 0;
    for (i = 0; i < n; i++) {
        if (!cars[i]->m76)
            continue;
        if (cars[i]->m128 == 1)
            continue;
        list[m++] = cars[i];
    }
    for (i = 0; i < m; i++) {
        for (j = m - 1; j > i; j--) {
            if (i == j)
                continue;
            int r = f_0c67e8(list[i], list[j], 0);
            if (r) {
                list[i]->m1952 = r;
                list[j]->m1952 = r;
            }
        }
    }
    v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 0.0f;
    for (i = 0; i < n; i++) {
        if (had[i]) {
            Car *c = cars[i];
            Vec4 *p = &c->m1920;
            v = *p;
            v.y = 0.0f;
            c->m1920 = v;
        }
    }
}
