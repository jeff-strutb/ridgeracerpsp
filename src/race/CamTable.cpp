/* Replay camera settings and helpers (retail 0x0823f0 to 0x0828c4): the table of camera
   lens settings and its static initialisation, the wall hit test for a camera position, a
   clamped linear ramp and the angles that look along a direction. */

extern "C" void *memset(void *, int, unsigned int);

/* Degrees to radians. */
extern float D_1d5da4;

/* A camera lens setting (52 bytes). */
struct CamLens {
    float fov;
    float m4;
    float m8;
    int m12;
    int m16;
    int m20;
    float m24;
    int m28;
    float m32;
    int m36;
    float m40;
    int m44;
    int m48;
};

/* The parts of a replay camera that a lens sets. */
struct CamView {
    char p0[480];
    float fov;
    char p484[12];
    float zoom;
    char p500[168];
    int m668;
    char p672[4];
    int m676;
    char p680[32];
    float m712;
    int m716;
    int m720;
    int m724;
    float m728;
    int m732;
    float m736;
};

extern "C" float f_0cd3cc(float);

extern CamLens D_241580[9];

/* @draft 0x0823f0 us f_0823f0
   REMAINING DIFFERENCE: retail loads all eight lens fields in store order before the
   stores; here (a restrict view pointer gives the nearest result) the last int load is
   hoisted first and the float loads take other registers. Locals in store order schedule
   the loads by type instead.
   WHAT IT DOES: Puts lens setting n on a camera: half the field of view and its zoom (one
   over its tangent), and the lens's other parameters. */
void f_0823f0(int n, CamView *__restrict v)
{
    CamLens *l = &D_241580[n];
    v->m676 = 0;
    v->fov = l->fov * 0.5f;
    float zoom = 1.0f / f_0cd3cc(v->fov);
    v->m736 = l->m40;
    v->m712 = l->m4;
    v->m716 = l->m12;
    v->m720 = l->m48;
    v->m724 = l->m16;
    v->m728 = l->m24;
    v->m668 = l->m28;
    v->m732 = l->m44;
    v->zoom = zoom;
}

/* The course collision areas of the map manager. */
struct CourseAreas {
    float f_0e27f8(float x, float z);
};
struct MapMgr {
    CourseAreas *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas m12240;
};
extern MapMgr D_23c820;

/* The wall hit tester. */
extern char D_241478[];
extern "C" int f_0b1bc0(void *hit, int area, float x, float z);
extern "C" int f_0b20d8(void *hit, float *pos, int a, float *out, float r);

/* The debug text buffer. */
extern char D_24517c[];

/* @implements 0x0828c4 us f_0828c4
   WHAT IT DOES: Debug text output (compiled out). */
inline void f_0828c4(char *buf, int line, const char *fmt, ...)
{
}

/* @implements 0x08249c us f_08249c
   WHAT IT DOES: Tests a camera position against the walls within 100 units (the corrected
   position goes to out) and keeps the camera at least 100 units above the ground. Returns
   the wall test's result. */
int f_08249c(float *pos, int a, int area, float *out)
{
    int hit;
    float g;
    f_0b1bc0(D_241478, area, pos[0], pos[2]);
    hit = f_0b20d8(D_241478, pos, a, out, 100.0f);
    g = D_23c820.Areas()->f_0e27f8(pos[0], pos[2]);
    if (pos[1] + 100.0f < g)
        out[1] = g + 100.0f;
    else
        out[1] = 0;
    if (hit)
        f_0828c4(D_24517c, 8, "HIT HIT HIT!!!!\n");
    return hit;
}

/* A ramp: hiVal at and above hi, loVal at and below lo, linear between. */
struct Ramp {
    float hiVal;
    float hi;
    float loVal;
    float lo;
};

/* @implements 0x082588 us f_082588
   WHAT IT DOES: Reads a ramp at x. */
float f_082588(Ramp *r, float x)
{
    if (x <= r->lo)
        return r->loVal;
    if (r->hi <= x)
        return r->hiVal;
    return r->loVal + (r->hiVal - r->loVal) * ((x - r->lo) / (r->hi - r->lo));
}

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

extern "C" {
void f_099b98(Angle *);
float f_09a9dc(float, float);
void f_09b394(Angle, float *, float *);
}

/* An angle wrapped into range. */
struct Rad {
    Angle a;
    Rad() { a.f = 0; }
    Rad(float f)
    {
        a.f = f;
        f_099b98(&a);
    }
};

/* Rotation angles and their order. */
struct Rot {
    Rad r[3];
    int order;
};

struct Vec4 {
    float x, y, z, w;
};

/* @draft 0x0825dc us f_0825dc
   REMAINING DIFFERENCE: retail holds &v.z in a third saved register from after the first
   wrap call and schedules the result stores later (320 against 308 bytes); the call
   sequence and the by-value copy of the direction match.
   WHAT IT DOES: The rotation (order 4) that turns the forward axis to the direction v: the
   yaw from its x and z, then the pitch from its height after undoing the yaw. */
Rot f_0825dc(Vec4 v)
{
    Vec4 *p = &v;
    float *z = &p->z;
    Rot r;
    r.r[0] = Rad(0);
    r.r[1] = Rad(0);
    r.r[2] = Rad(0);
    r.order = 4;
    r.r[1] = Rad(f_09a9dc(-p->x, -p->z));
    f_09b394(Rad(-r.r[1].a.f).a, z, &p->x);
    r.r[0] = Rad(f_09a9dc(p->y, -p->z));
    r.r[2] = Rad(0);
    return r;
}

/* The lens settings. */
CamLens D_241580[9] = {
    {D_1d5da4 * 27.5f, 1.0f, 1.0f, 0, 0, 0, 0, 0, 1.0f, -1, 1.0f, 0, 0},
    {D_1d5da4 * 30.0f, 1.0f, 1.0f, 0, 0, 0, 0, 1, 1.0f, -1, 1.0f, 1, 1},
    {D_1d5da4 * 15.0f, 0.5f, 0.5f, 0, 0, 0, 0, 1, 1.0f, -1, 1.0f, 0, 0},
    {D_1d5da4 * 27.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1, 1.0f, -1, 1.0f, 0, 0},
    {D_1d5da4 * 27.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1, 1.0f, -1, 1.0f, 0, 0},
    {D_1d5da4 * 27.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1, 1.0f, -1, 1.0f, 0, 0},
    {D_1d5da4 * 27.5f, 0, 0, 0, 0, 0, 0, 0, 1.0f, -1, 1.0f, 0, 0},
    {D_1d5da4 * 30.0f, 1.0f, 1.0f, 0, 0, 0, 0, 1, 1.0f, -1, 1.0f, 1, 1},
};

/* @implements 0x08271c us __static_initialization_and_destruction_0
   WHAT IT DOES: Fills in the lens settings at start up (the fields of view are in degrees
   converted at run time). */
/* @implements 0x0828a4 us _GLOBAL__I
   WHAT IT DOES: Runs the above. */
