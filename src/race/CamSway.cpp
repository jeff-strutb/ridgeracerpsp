/* The replay cameras' sway (retail 0x0f3f30 to 0x0f42f8): a sum of up to sixteen rotating
   arms, each with an angle that turns at its own speed and a length. Stepping it turns every
   arm and adds the arms' ends together; the sway is the sum's first two components. Also
   here: the eased half sine ramp the cameras use for their moves. */

union Angle {
    float f;
    int i;
};

extern "C" {
Angle *f_099b98(Angle *a);
float f_099fc4(float a);
}

/* An angle wrapped into range. */
struct Rad {
    Angle a;
    Rad(float f)
    {
        a.f = f;
        f_099b98(&a);
    }
};

struct Vec4 {
    float x, y, z, w;
};

/* The 3x4 matrix of the camera math library (src/system/Matrix34.cpp). */
struct Mat34 {
    float m[3][4];
    Mat34 &f_09ff44();
    Mat34 &f_0a082c(Angle a, int i, int j);
};

extern "C" void f_0a6bf4(Vec4 *out, Mat34 *m, Vec4 *v);

/* One arm: its angle, its turning speed and its length. */
struct Arm {
    Angle a;
    float speed;
    float len;
};

struct CamSway {
    int n;
    Arm arm[16];
    float m196;
    float m200;

    void f_0f3f30();
    void f_0f40bc(int count, const Arm *src);
    void f_0f411c(float t);
};

/* @implements 0x0f3f30 us _ZN7CamSway8f_0f3f30Ev
   WHAT IT DOES: Sets up the default sway: eight arms, all at angle zero, with fixed speeds
   and lengths. */
void CamSway::f_0f3f30()
{
    n = 8;
    arm[0].a = Rad(0.0f).a;
    arm[1].a = Rad(0.0f).a;
    arm[2].a = Rad(0.0f).a;
    arm[3].a = Rad(0.0f).a;
    arm[4].a = Rad(0.0f).a;
    arm[5].a = Rad(0.0f).a;
    arm[6].a = Rad(0.0f).a;
    arm[7].a = Rad(0.0f).a;
    arm[0].speed = 0.028762141f;
    arm[1].speed = 0.010546118f;
    arm[2].speed = -0.00479369f;
    arm[3].speed = 0.039308257f;
    arm[4].speed = -0.067111664f;
    arm[5].speed = 0.0071905353f;
    arm[6].speed = -0.017449033f;
    arm[7].speed = 0.0033555832f;
    arm[0].len = 8.0f;
    arm[1].len = 5.0f;
    arm[2].len = 3.0f;
    arm[3].len = 5.0f;
    arm[4].len = 4.0f;
    arm[5].len = 2.0f;
    arm[6].len = 1.5f;
    arm[7].len = 10.0f;
}

/* @implements 0x0f40bc us _ZN7CamSway8f_0f40bcEiPK3Arm
   WHAT IT DOES: Takes count arms from src (at most sixteen are copied). */
void CamSway::f_0f40bc(int count, const Arm *src)
{
    n = count;
    for (int i = 0; i < count && i < 16; i++)
        arm[i] = src[i];
}

/* @implements 0x0f411c us _ZN7CamSway8f_0f411cEf
   WHAT IT DOES: Turns every arm by its speed times t and adds up the arms' ends (each arm's
   length rotated by its angle); keeps the sum's first two components as the sway. */
void CamSway::f_0f411c(float t)
{
    Vec4 v;
    Vec4 sum = {0, 0, 0, 1.0f};
    Mat34 m;
    Vec4 r;
    for (int i = 0; i < n; i++) {
        Arm *e = &arm[i];
        e->a.f = e->a.f + t * e->speed;
        f_099b98(&e->a);
        m.f_09ff44();
        m.f_0a082c(Rad(e->a.f).a, 0, 1);
        v.x = e->len;
        v.y = 0;
        v.z = 0;
        v.w = 1.0f;
        f_0a6bf4(&r, &m, &v);
        v = r;
        sum.x += v.x;
        sum.y += v.y;
        sum.z += v.z;
    }
    m196 = sum.x;
    m200 = sum.y;
}

/* @draft 0x0f4290 us f_0f4290
   WHAT IT DOES: The eased ramp of x over [0, 1]: half a sine wave from 0 to 1, x clamped to
   the ramp.
   Remaining difference: retail keeps the clamped value in the argument register (f12, the
   subtraction made in place) and loads pi into f0; here the value goes to f0 and pi to f12.
   Writing the subtraction in place on the parameter gives the same code. */
extern "C" float f_0f4290(float x)
{
    float d = x - 0.5f;
    if (0.5f < d)
        d = 0.5f;
    if (d < -0.5f)
        d = -0.5f;
    return f_099fc4(d * 3.1415927f) * 0.5f + 0.5f;
}
