/* The first person (bumper) camera, CamCtrl::CCamEye1 (retail 0x0c4444 to 0x0c4bc4): its
   parameter set up, reset, start and per frame step, then the empty stop method and the
   inline destructors emitted with its vtable (the last three have no unwind entries, so the
   object file map splits them off as their own row). */

namespace CamCtrl {

/* An angle, passed by value in an integer register. */
union Angle {
    float f;
    int i;
};

struct CamParam {
    int v[6];
};

class CCamProto {
public:
    virtual ~CCamProto() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg) {}
    virtual void f_07f5e8() {}
    virtual void f_07f5f0() {}
    virtual void f_07f5f8() {}

    CamParam param;
};

struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float a, float b, float c, float d)
    {
        x = a;
        y = b;
        z = c;
        w = d;
    }
};

/* A 3x4 matrix. */
struct M34 {
    float m[12];
};

/* The parameter block of a first person camera. */
struct Eye1Param {
    CamParam base;
    int m24;
    int m28;
    int m32;
};

}

extern "C" {
void f_099b98(CamCtrl::Angle *);
float f_0cd3cc(float a);
void f_09c720(CamCtrl::Vec4 *o, void *m, CamCtrl::Vec4 *v);
void f_09ff44(CamCtrl::M34 *m);
void f_0a082c(CamCtrl::M34 *m, CamCtrl::Angle a, int i, int j);
void f_09fd1c(CamCtrl::M34 *m, void *q);
void f_0a12ac(CamCtrl::M34 *o, CamCtrl::M34 *a, CamCtrl::M34 *b);
void f_0a4160(CamCtrl::Vec4 *o, CamCtrl::M34 *m, int n);
}

namespace CamCtrl {

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

/* Rotation angles and a zero. */
struct Rot {
    Rad r[3];
    float w;
    Rot(float x, float y, float z)
    {
        r[0] = Rad(x);
        r[1] = Rad(y);
        r[2] = Rad(z);
        w = 0;
    }
};

/* The orientation as a matrix. */
inline M34 FromQuat(float *q)
{
    M34 m;
    f_09fd1c(&m, q);
    return m;
}

/* The product of two matrices. */
inline M34 Mul(const M34 &a, const M34 &b)
{
    M34 r;
    f_0a12ac(&r, (M34 *)&a, (M34 *)&b);
    return r;
}

/* The followed car as the camera reads it. */
struct E1Car {
    char p0[144];
    Vec4 pos;
    char p160[48];
    float q[4];       /* 208, the orientation */
    char p224[1904];
    char p2128[16];
    float m2144;
    char p2148[64];
    int m2212;
    char p2216[264];
    float m2480[4];
    char p2496[5212];
    float m7708;
    char p7712[2416];
    Vec4 m10128;   /* the eye's offset from the car */
};

/* The view the camera drives. */
struct E1View {
    Vec4 eye;
    char p16[464];
    float m480;    /* lens angle */
    float m484;
    float m488;    /* far distance */
    float m492;
    float m496;    /* lens scale */
    int m500, m504, m508, m512, m516;
    float m520, m524, m528, m532;
    char p536[36];
    int m572;
    char p576[32];
    float m608, m612, m616;
    char p620[40];
    int m660;
    int m664;
    int m668;
    int m672;
    char p676[12];
    Vec4 m688;
    float m704;
    float m708;
    char p712[32];
    float m744;
};

/* Puts the eye on a view. */
inline void SetEye(E1View *v, const Vec4 &eye)
{
    v->eye.x = eye.x;
    v->eye.y = eye.y;
    v->eye.z = eye.z;
}

/* The camera's second parameter block, as the step reads it. */
struct E1Aux {
    char p0[20];
    float m20;
    char p24[12];
    float m36;
};

/* The screen set up. */
struct E1Screen {
    char p0[12];
    int m12, m16, m20;
    float m24, m28, m32, m36, m40, m44;
};

}

extern CamCtrl::E1Screen D_23fefc;

namespace CamCtrl {

class CCamEye1 : public CCamProto {
public:
    virtual ~CCamEye1() {}
    virtual void Set(const CamParam *p);
    virtual void Reset();
    virtual void f_07f5e0(int *arg);
    virtual void f_07f5e8();
    virtual void f_07f5f8() {}

    E1View *View() { return (E1View *)param.v[0]; }
    E1View *Prev() { return (E1View *)param.v[1]; }
    E1Car *Car() { return (E1Car *)param.v[2]; }

    int m28;
    Vec4 ofs;      /* 32 */
    int m48;
};

/* @implements 0x0c4444 us _ZN7CamCtrl8CCamEye13SetEPKNS_8CamParamE
   WHAT IT DOES: Takes the parameter block and keeps its extra word. */
void CCamEye1::Set(const CamParam *p)
{
    CCamProto::Set(p);
    m48 = ((const Eye1Param *)p)->m32;
}

/* @implements 0x0c447c us _ZN7CamCtrl8CCamEye15ResetEv
   WHAT IT DOES: Resets the base camera. */
void CCamEye1::Reset()
{
    CCamProto::Reset();
}

/* @draft 0x0c4498 us _ZN7CamCtrl8CCamEye18f_07f5e0EPi
   DRAFT: 12 words. The view stores match; retail schedules the height product before the
   w and z stores (constants loaded 0.9, 1, -100), here the 1.0 store goes first. All store
   orders, a reference, a pointer, an inline Set and reloading the car were tried.
   WHAT IT DOES: Starts the camera: marks its view (and clears the previous camera's mark),
   sets a far distance of 300, and puts the eye's offset on the car (0.9 of its height up,
   100 forward) and takes a copy of it. */
void CCamEye1::f_07f5e0(int *arg)
{
    E1View *v = View();
    E1View *o = (E1View *)param.v[1];
    v->m660 = 0;
    v->m668 = 0;
    v->m672 = 1;
    v->m664 = 1;
    if (o)
        o->m660 = 0;
    v->m488 = 300.0f;
    E1Car *c = Car();
    Vec4 &e = c->m10128;
    e.x = 0;
    e.y = c->m7708 * 0.9f;
    e.w = 1.0f;
    e.z = -100.0f;
    Vec4 t = Car()->m10128;
    ofs = t;
}

/* @draft 0x0c453c us _ZN7CamCtrl8CCamEye18f_07f5e8Ev
   DRAFT: all the logic and the call sequence are in retail's order, and the stack frame
   layout (rot 0, the two points 16 and 32, the transform result 48, the up vector 64, the
   matrices 80/128/176, the angles 224, three eye copies 240) matches; 347/406 words differ,
   size 1624 vs 1608. What differs: (1) retail keeps one float zero in $f20 for the up
   vector's x and z (mtc1 zero + swc1 at the two stores); here, after the three Rad
   constructions, cse folds them to sw $0 (tried the Vec4 constructor, a chain, an inline
   Set, a zero helper); (2) retail defines the address of the product matrix (sp+128) after
   the first transform call so it shares the register of the result pointer (sp+48), seven
   saved registers; here it is hoisted before that call and an eighth (s7) is needed;
   (3) the height clamp: retail stores the clamped y in a branch-likely delay slot and
   reloads it, here a mov.s copy follows the store and a plain branch is used.
   WHAT IT DOES: Puts the camera on its view: the eye is the car's offset point and the look
   angles come from the car's orientation turned a fixed angle about one axis, nudged by the
   second parameter block and wrapped; the lens is 55 degrees halved and its scale, the
   car's setting, speed and position and the lens span are copied, and the eye is held at or
   above a height taken from the car's four heights. If a previous view exists, it is set up
   as the mirror of this one (look angles negated, eye raised by the screen's offset) with
   the screen's lens, aspect, far distance and clip rectangle. */
void CCamEye1::f_07f5e8()
{
    Rot rot(0, 0, 0);
    Vec4 v1, v2, t;
    f_09c720(&t, &Car()->q, &ofs);
    v1 = t;
    Vec4 u(0.0f, 1000.0f, 0.0f, 1.0f);
    f_09c720(&t, &Car()->q, &u);
    v2 = t;
    v1.x += Car()->pos.x;
    v1.y += Car()->pos.y;
    v1.z += Car()->pos.z;
    v2.x += Car()->pos.x;
    v2.y += Car()->pos.y;
    v2.z += Car()->pos.z;
    M34 m;
    f_09ff44(&m);
    Angle ang;
    ang.f = 0.017444444f;
    f_099b98(&ang);
    f_0a082c(&m, ang, 1, 2);
    m = Mul(FromQuat(Car()->q), m);
    Vec4 out;
    f_0a4160(&out, &m, 4);
    *(Vec4 *)&rot = out;
    E1Aux *aux = (E1Aux *)m48;
    rot.r[2].a.f += aux->m20 * 1.5f * 9.5873e-05f * 1.5f;
    f_099b98(&rot.r[2].a);
    rot.r[0].a.f += aux->m36 * 0.00026844439f * 1.75f;
    f_099b98(&rot.r[0].a);
    E1View *v = View();
    v->m608 = rot.r[0].a.f;
    v->m612 = rot.r[1].a.f;
    v->m616 = rot.r[2].a.f;
    float h = 0;
    for (int i = 0; i < 4; i++)
        h += Car()->m2480[i];
    float lim = h * 0.25f + 300.0f;
    if (v1.y < lim)
        v1.y = lim;
    SetEye(v, v1);
    float half = 0.5f;
    float lens = 0.9599311f;
    lens *= half;
    v->m480 = lens;
    v->m496 = 1.0f / f_0cd3cc(lens);
    v = View();
    E1Car *c = Car();
    E1View *p = Prev();
    v->m572 = c->m2212;
    v->m704 = c->m2144;
    v->m688 = v->eye;
    v->m708 = v->m480 + v->m480;
    v->m744 = c->m2144;
    if (p) {
        E1Screen *g = &D_23fefc;
        p->m616 = -v->m616;
        p->m612 = v->m612 + 3.14159f;
        p->m608 = g->m24 / 180.0f * 3.14159f - v->m608;
        Vec4 a = v->eye;
        Vec4 b = v->eye;
        b.y += g->m40 * 1000.0f;
        Vec4 d = v->eye;
        p->eye.x = a.x;
        p->eye.y = b.y;
        p->eye.z = d.z;
        p->m480 = lens;
        p->m496 = 1.0f / f_0cd3cc(lens);
        p = Prev();
        p->m572 = Car()->m2212;
        p->m704 = Car()->m2144;
        p->m744 = Car()->m2144;
        d = p->eye;
        p->m688 = d;
        p->m484 = (float)g->m12 / (float)g->m16 * g->m44;
        p->m488 = g->m28 * 1000.0f;
        p->m492 = g->m32 * 1000.0f;
        float l2 = g->m36 / 180.0f * 3.14159f * half;
        p->m480 = l2;
        float s = 1.0f / f_0cd3cc(l2);
        p = Prev();
        p->m504 = -g->m12 * p->m500;
        p->m512 = 2048;
        p->m516 = g->m20 + g->m16 / 2 + 1912;
        p->m508 = g->m16;
        View()->m496 = s;
        p->m532 = (float)(g->m16 / 2 + 5);
        p->m520 = (float)-g->m12 * half;
        p->m524 = (float)g->m16 * half;
        p->m528 = (float)(g->m12 / 2 + 5);
    }
}

/* @implements 0x0c4b84 us _ZN7CamCtrl8CCamEye18f_07f5f8Ev
   WHAT IT DOES: Stops the camera: nothing to do. */

/* @implements 0x0c4b8c us _ZN7CamCtrl8CCamEye1D1Ev
   WHAT IT DOES: Complete object destructor (inline, emitted with the vtable): restores the
   base vtable. */
/* @implements 0x0c4b9c us _ZN7CamCtrl8CCamEye1D0Ev
   WHAT IT DOES: Deleting destructor: as above, then frees the object. */

}
