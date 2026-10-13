/* The quaternion of the camera math library (retail 0x09c43c to 0x09c720). Components are an
   array (x, y, z, w), so stores through one quaternion are taken to reach any other. */

#include <math.h>

struct Quat {
    float v[4];
    Quat() {}
    Quat(float x, float y, float z, float w)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
        v[3] = w;
    }
    Quat &f_09c43c();
    Quat &f_09c4e8();
    Quat f_09c54c() const;
    float f_09c5b8() const;
    Quat &f_09c618(const Quat &a, const Quat &b);
};

/* @draft 0x09c43c us f_09c43c
   WHAT IT DOES: Normalises the quaternion in place and returns it.
   Remaining difference: FP register choice only; retail loads x, y, z, w into f6, f5, f4, f3
   and scales w in place, this source gets f6, f3, f5, f4 (operator forms and local copies
   tried, all the same). */
Quat &Quat::f_09c43c()
{
    float inv = 1.0f / sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
    v[0] *= inv;
    v[1] *= inv;
    v[2] *= inv;
    v[3] *= inv;
    return *this;
}

/* @implements 0x09c4e8 us f_09c4e8
   WHAT IT DOES: Inverts the quaternion in place (the conjugate over the squared norm) and
   returns it. */
Quat &Quat::f_09c4e8()
{
    float inv = 1.0f / (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
    v[0] *= -inv;
    v[1] *= -inv;
    v[2] *= -inv;
    v[3] *= inv;
    return *this;
}

/* @implements 0x09c54c us f_09c54c
   WHAT IT DOES: Returns the inverse quaternion (the conjugate over the squared norm). */
Quat Quat::f_09c54c() const
{
    float inv = 1.0f / (v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
    return Quat(-v[0] * inv, -v[1] * inv, -v[2] * inv, v[3] * inv);
}

/* @implements 0x09c5b8 us f_09c5b8
   WHAT IT DOES: Returns the quaternion's norm. */
float Quat::f_09c5b8() const
{
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}

/* @implements 0x09c618 us f_09c618
   WHAT IT DOES: Sets the quaternion to the Hamilton product a * b and returns it. */
Quat &Quat::f_09c618(const Quat &a, const Quat &b)
{
    v[0] = a.v[3] * b.v[0] + b.v[3] * a.v[0] + a.v[1] * b.v[2] - a.v[2] * b.v[1];
    v[1] = a.v[3] * b.v[1] + b.v[3] * a.v[1] + a.v[2] * b.v[0] - a.v[0] * b.v[2];
    v[2] = a.v[3] * b.v[2] + b.v[3] * a.v[2] + a.v[0] * b.v[1] - a.v[1] * b.v[0];
    v[3] = a.v[3] * b.v[3] - a.v[0] * b.v[0] - a.v[1] * b.v[1] - a.v[2] * b.v[2];
    return *this;
}
