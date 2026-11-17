/* The car buffer object file (retail 0x0ec364 to 0x0edc98, "Car::CCarBufferPSP"): the base of
   every race car object. It holds the car's state as the model and the race read it (position,
   orientation quaternion, wheel positions and angles, the wheel matrices), the car model, the
   car's motion state and its dynamics block. It builds the car's matrices from that state,
   resets the state, sets a car up from its database record and loads its model, colour table,
   hit model and dynamics data by the record's type. */

extern "C" {
void *memcpy(void *d, const void *s, unsigned int n) throw();
int sprintf(char *buf, const char *fmt, ...) throw();
void f_099b98(void *a);
void f_0a6f88(void *m);
void f_0a6fac(void *m);
void f_0201d4(void *m);
void f_02842c(void);
void f_028d94(void *m);
void *f_005c34(void *loader, const char *name);
void *f_005a38(void *loader, const char *name);
void *f_002acc(void *pkg, const char *name);
void f_026bc8(void *res, int r, int g, int b);
void f_100ef8(void *car);
}

/* A table of the game database (made elsewhere). */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
};
extern "C" char *f_0368e8(CTable *t, const char *field, char *rec, int a, int b);
extern "C" int f_036a3c(CTable *t, char *rec, int *index, int count);
extern CTable D_240740;
extern unsigned char D_24063c[];
extern const int D_1a2120;
extern const int D_1a211c[];   /* the database's field sizes by type (D_1a2120 is [1]) */
extern char D_240768[];
extern char D_1dd6b0[];

/* The first byte of the record last read from the database. */
static inline int rec_byte() { return D_24063c[0]; }

/* An angle in radians, kept in range by f_099b98. */
union Angle {
    float a;
    Angle() : a(0) {}
    Angle(float r) : a(r) { f_099b98(this); }
};

/* Euler angles with their axis order. */
struct Euler {
    Angle a[3];
    int order;
    Euler()
    {
        a[0] = Angle(0.0f);
        a[1] = Angle(0.0f);
        a[2] = Angle(0.0f);
        order = 0;
    }
    void Set(Angle x, Angle y, Angle z)
    {
        a[0] = x;
        a[1] = y;
        a[2] = z;
        order = 0;
    }
};

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
};

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
    void Set(float a, float b, float c)
    {
        x = a;
        y = b;
        z = c;
        w = 1.0f;
    }
};

/* The 4x3 matrix with padded rows (the camera math library). */
struct Mat43p {
    float m[4][4];
    Mat43p() {}
    Mat43p(const Euler &e);
    Mat43p(const Quat &q);
    Mat43p &f_0a2db0();
    Vec4 &T() { return *(Vec4 *)m[3]; }
};
extern "C" {
void f_0a2a00(Mat43p *m, const Euler *e);
void f_0a2bc0(Mat43p *m, const Quat *q);
}
inline Mat43p::Mat43p(const Euler &e) { f_0a2a00(this, &e); }
inline Mat43p::Mat43p(const Quat &q) { f_0a2bc0(this, &q); }

/* The 4x4 matrix. */
struct Mat44 {
    float m[4][4];
};

static inline void mat44_set(Mat44 &d, const Mat43p &s)
{
    d.m[0][0] = s.m[0][0];
    d.m[0][1] = s.m[0][1];
    d.m[0][2] = s.m[0][2];
    d.m[1][0] = s.m[1][0];
    d.m[1][1] = s.m[1][1];
    d.m[1][2] = s.m[1][2];
    d.m[2][0] = s.m[2][0];
    d.m[2][1] = s.m[2][1];
    d.m[2][2] = s.m[2][2];
    d.m[3][0] = s.m[3][0];
    d.m[3][1] = s.m[3][1];
    d.m[3][2] = s.m[3][2];
    d.m[0][3] = 0;
    d.m[1][3] = 0;
    d.m[2][3] = 0;
    d.m[3][3] = 1.0f;
}

/* A plain matrix slot. */
struct Mat {
    float m[4][4];
};

/* The car's name in the database and its index. */
struct CarName {
    char *rec;
    int index;
};

/* The car's motion state (made and destroyed elsewhere). */
struct CMotion {
    char m0[624];
    CMotion() { f_0a6f88(this); }
    ~CMotion() { f_0a6fac(this); }
};

/* The car's hit state, set up from its hit model. */
struct CHit {
    char m0[264];
    void f_0b1ba8(void *hit, int type);
};

/* The car model's renderer part, as far as this file reads it. */
struct CModelPart {
    char m0[1612];
    unsigned int m1612;
    unsigned int m1616;
    char m1620[92];
    void SetLight(unsigned int v) { m1616 = m1612 = v; }
};

/* The car model (CarModel.cpp). */
struct CCarModel {
    char m0[288];
    CModelPart model;
    char res[16];
    char m2016[720];
    CCarModel() { f_0201d4(this); }
    int f_01dbc4(void *data, int a, void *b, int colour);
    void f_01dee4();
};

/* The car's dynamics block: four sets of Euler angles among plain data. */
struct CCarDyn {
    char m0[16];
    Euler e16;
    char m32[16];
    Euler e48;
    char m64[768];
    Euler e832;
    char m848[96];
    Euler e944;
    CCarDyn();
};

namespace Car {

class CCarBufferPSP {
public:
    CCarBufferPSP();
    virtual ~CCarBufferPSP();
    virtual void f_0eda30();
    virtual void f_0eda38();
    virtual void f_0eda40();
    virtual void f_0eda48();
    virtual void f_0eda50();
    virtual void f_0eda58();
    virtual void f_0eda60();
    virtual void f_0eda68();
    virtual void f_0eda70();
    virtual void f_0eda78();
    virtual void f_0eda80();
    virtual void f_0eda88();
    virtual void f_0eda90();
    virtual int f_0eda98();
    virtual void f_0edaa0();
    virtual int f_0edaa8();
    virtual void f_0edab0();

    void f_0ec708(Vec3 &out) const;
    Mat43p f_0ec724() const;
    void f_0ec780(Mat43p &out) const;
    void f_0ec818(Mat44 &out) const;
    Mat43p f_0ec8b8(int i) const;
    void f_0ec91c(int i, Mat43p &out) const;
    void f_0ec9c8(int i, Mat44 &out) const;
    Mat43p f_0eca68(int i) const;
    void f_0ecacc(int i, Mat43p &out) const;
    void f_0ecb78(int i, Mat44 &out) const;
    void f_0ecc18(const char *c);
    void f_0ecc4c();
    void f_0ed314(int type, int a, CarName name, int b, Quat q, Vec4 p);
    void f_0ed568();
    void f_0ed58c();
    void f_0ed938();
    void f_0eda14();

    char m4[72];
    int m76;
    int m80;
    int m84;
    int m88;
    CarName name;
    int m100;
    int m104;
    short m108[8];
    int m124;
    int m128;
    char m132[12];
    Vec4 pos;
    Vec4 m160;
    Vec4 m176;
    int m192;
    char m196[12];
    Quat rot;
    Vec4 m224;
    Vec4 up;
    Vec4 wheel[4];
    Vec4 m320[4];
    Euler wheelAng[4];
    Vec4 wheel2[4];
    Euler wheelAng2[4];
    Mat m576[9];
    Mat m1152[9];
    float m1728;
    float m1732;
    float m1736;
    float m1740;
    float m1744;
    float m1748;
    int m1752;
    float m1756;
    float m1760;
    float m1764;
    float m1768;
    float m1772;
    float m1776;
    float m1780;
    float m1784;
    float m1788;
    float m1792;
    int m1796;
    int m1800;
    int m1804;
    float m1808;
    float m1812;
    int m1816;
    float m1820;
    int m1824;
    int m1828;
    int m1832;
    int m1836;
    int m1840;
    int m1844;
    char m1848[8];
    Vec4 m1856;
    Vec4 m1872;
    int m1888;
    int m1892;
    float m1896;
    float m1900;
    Vec4 m1904;
    Vec4 m1920;
    Vec4 m1936;
    int m1952;
    int m1956;
    float m1960;
    float m1964;
    int m1968;
    int m1972;
    int m1976;
    int m1980;
    int m1984;
    char m1988[12];
    int m2000[4][4];
    int m2064[4];
    int m2080[4];
    int m2096;
    int m2100;
    int m2104;
    int m2108;
    int m2112;
    int m2116;
    int m2120;
    int m2124;
    CMotion motion;
    void *hit;
    CHit hitState;
    void *mdl;
    void *clut;
    void *dyn;
    char m3032[8];
    CCarModel model;
    int colour;
    int light;
    char m5784[8];
    CCarDyn dynamics;
};

}

using namespace Car;

/* @implements 0x0ec364 us _ZN3Car13CCarBufferPSPC2Ev
   WHAT IT DOES: Builds the car buffer: its wheel angles, motion state, car model and dynamics
   block, then resets the car's state. */
/* @implements 0x0ec4f0 us _ZN3Car13CCarBufferPSPC1Ev
   WHAT IT DOES: The same, as the complete object constructor. */
CCarBufferPSP::CCarBufferPSP() : m88(0)
{
    f_0ecc4c();
}

/* @implements 0x0ec67c us _ZN3Car13CCarBufferPSPD2Ev
   WHAT IT DOES: Takes down the motion state. */
/* @implements 0x0ec6a4 us _ZN3Car13CCarBufferPSPD1Ev
   WHAT IT DOES: The same, as the complete object destructor. */
/* @implements 0x0ec6cc us _ZN3Car13CCarBufferPSPD0Ev
   WHAT IT DOES: The same, then frees the object. */
CCarBufferPSP::~CCarBufferPSP()
{
}

/* @implements 0x0ec708 us _ZNK3Car13CCarBufferPSP8f_0ec708ER4Vec3
   WHAT IT DOES: Returns the car's position. */
void CCarBufferPSP::f_0ec708(Vec3 &out) const
{
    out.x = pos.x;
    out.y = pos.y;
    out.z = pos.z;
}

/* @implements 0x0ec724 us _ZNK3Car13CCarBufferPSP8f_0ec724Ev
   WHAT IT DOES: Returns the car's matrix: its orientation, translated to its position. */
Mat43p CCarBufferPSP::f_0ec724() const
{
    Mat43p m(rot);
    m.T() = pos;
    return m;
}

/* @implements 0x0ec780 us _ZNK3Car13CCarBufferPSP8f_0ec780ER6Mat43p
   WHAT IT DOES: The same, into the given matrix. */
void CCarBufferPSP::f_0ec780(Mat43p &out) const
{
    out = Mat43p(rot);
    out.T() = pos;
}

/* @implements 0x0ec818 us _ZNK3Car13CCarBufferPSP8f_0ec818ER5Mat44
   WHAT IT DOES: The same, as a 4x4 matrix. */
void CCarBufferPSP::f_0ec818(Mat44 &out) const
{
    Mat43p m;
    f_0ec780(m);
    mat44_set(out, m);
}

/* @implements 0x0ec8b8 us _ZNK3Car13CCarBufferPSP8f_0ec8b8Ei
   WHAT IT DOES: Returns wheel i's matrix: its angles, translated to its position. */
Mat43p CCarBufferPSP::f_0ec8b8(int i) const
{
    Mat43p m(wheelAng[i]);
    m.T() = wheel[i];
    return m;
}

/* @implements 0x0ec91c us _ZNK3Car13CCarBufferPSP8f_0ec91cEiR6Mat43p
   WHAT IT DOES: The same, into the given matrix. */
void CCarBufferPSP::f_0ec91c(int i, Mat43p &out) const
{
    out = Mat43p(wheelAng[i]);
    out.T() = wheel[i];
}

/* @implements 0x0ec9c8 us _ZNK3Car13CCarBufferPSP8f_0ec9c8EiR5Mat44
   WHAT IT DOES: The same, as a 4x4 matrix. */
void CCarBufferPSP::f_0ec9c8(int i, Mat44 &out) const
{
    Mat43p m;
    f_0ec91c(i, m);
    mat44_set(out, m);
}

/* @implements 0x0eca68 us _ZNK3Car13CCarBufferPSP8f_0eca68Ei
   WHAT IT DOES: Returns wheel i's matrix from the second set of wheel angles and positions. */
Mat43p CCarBufferPSP::f_0eca68(int i) const
{
    Mat43p m(wheelAng2[i]);
    m.T() = wheel2[i];
    return m;
}

/* @implements 0x0ecacc us _ZNK3Car13CCarBufferPSP8f_0ecaccEiR6Mat43p
   WHAT IT DOES: The same, into the given matrix. */
void CCarBufferPSP::f_0ecacc(int i, Mat43p &out) const
{
    out = Mat43p(wheelAng2[i]);
    out.T() = wheel2[i];
}

/* @implements 0x0ecb78 us _ZNK3Car13CCarBufferPSP8f_0ecb78EiR5Mat44
   WHAT IT DOES: The same, as a 4x4 matrix. */
void CCarBufferPSP::f_0ecb78(int i, Mat44 &out) const
{
    Mat43p m;
    f_0ecacc(i, m);
    mat44_set(out, m);
}

/* @implements 0x0ecc18 us _ZN3Car13CCarBufferPSP8f_0ecc18EPKc
   WHAT IT DOES: Copies the car's six colour bytes. */
void CCarBufferPSP::f_0ecc18(const char *c)
{
    memcpy(&m104, c, 6);
}

/* @draft 0x0ecc4c us _ZN3Car13CCarBufferPSP8f_0ecc4cEv
   WHAT IT DOES: Resets the car's state: no record, the identity orientation at the origin, the
   wheels at (+-1000, 300, +-1000) with zero angles, and the wheel matrices from the current
   view matrix and the identity.
   DRAFT: same stores, but the schedule differs from the start (retail builds the
   orientation's stack temporary first and keeps the stores near field order); 4 bytes short. */
void CCarBufferPSP::f_0ecc4c()
{
    CarName n;
    int i;

    m76 = 0;
    m80 = 0;
    m84 = 0;
    m88 = 0;
    n.rec = 0;
    name = n;
    m100 = -1;
    m104 = 0;
    m108[0] = 0;
    m108[1] = 0;
    m108[2] = 0;
    m108[3] = 0;
    m108[4] = 0;
    m108[5] = 0;
    m108[6] = 0;
    m108[7] = 0;
    m124 = 0;
    m128 = 0;
    pos.Set(0, 0, 0);
    m160.Set(0, 0, 0);
    m176.Set(0, 0, 0);
    m192 = 0;
    rot = Quat(0, 0, 0, 1.0f);
    m224.Set(0, 0, 0);
    up.Set(0, 0, 0);
    m1744 = 0;
    m1748 = 0;
    m1752 = 1;
    m1756 = 0;
    m1760 = 0;
    m1764 = 1000000.0f;
    m1768 = 1000000.0f;
    m1772 = 1000000.0f;
    m1776 = 0;
    m1780 = 0;
    m1784 = 0;
    m1788 = 0;
    m1792 = 0;
    m1796 = 0;
    m1800 = 0;
    m1804 = 0;
    m1808 = 0;
    m1812 = 0;
    m1816 = 1;
    m1820 = 0;
    m1824 = 0;
    m1828 = 0;
    m1832 = 0;
    m1836 = 0;
    m1840 = 0;
    m1844 = 0;
    m1856.Set(0, 0, 0);
    m1872.Set(0, 0, 0);
    m1888 = 0;
    m1892 = 0;
    m1896 = 0;
    m1900 = 0;
    m1904.Set(0, 0, 0);
    m1920.Set(0, 0, 0);
    m1936.Set(0, 0, 0);
    m1952 = 0;
    m1956 = 0;
    m1960 = 0;
    m1964 = 0;
    m1968 = 0;
    m1972 = 0;
    m1976 = 0;
    m1980 = 0;
    m1984 = 0;
    for (i = 0; i < 4; i++) {
        m320[i].x = 0;
        m320[i].y = 0;
        m320[i].z = 0;
        m320[i].w = 0;
        m2000[i][0] = 0;
        m2000[i][1] = 0;
        m2000[i][2] = 0;
        m2000[i][3] = 0;
        m2064[i] = 0;
        m2080[i] = 0;
    }
    m2096 = 0;
    m2100 = 0;
    m2104 = 0;
    m2108 = 0;
    m2112 = 0;
    m2116 = 0;
    m2120 = 0;
    m2124 = 0;
    hit = 0;
    mdl = 0;
    clut = 0;
    dyn = 0;
    colour = 0;
    light = 0;
    up.Set(0, 1.0f, 0);
    wheel[0].Set(1000.0f, 300.0f, -1000.0f);
    wheel[1].Set(-1000.0f, 300.0f, -1000.0f);
    wheel[2].Set(1000.0f, 300.0f, 1000.0f);
    wheel[3].Set(-1000.0f, 300.0f, 1000.0f);
    wheelAng[0].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheelAng[1].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheelAng[2].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheelAng[3].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheel2[0].Set(1000.0f, 300.0f, -1000.0f);
    wheel2[1].Set(-1000.0f, 300.0f, -1000.0f);
    wheel2[2].Set(1000.0f, 300.0f, 1000.0f);
    wheel2[3].Set(-1000.0f, 300.0f, 1000.0f);
    wheelAng2[0].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheelAng2[1].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheelAng2[2].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    wheelAng2[3].Set(Angle(0.0f), Angle(0.0f), Angle(0.0f));
    m1728 = m1732 = 1.0f;
    m1736 = 0;
    m1740 = 0;
    f_02842c();
    Mat view;
    f_028d94(&view);
    for (i = 0; i < 9; i++)
        m576[i] = view;
    Mat43p id;
    id.f_0a2db0();
    for (i = 0; i < 9; i++)
        m1152[i] = *(Mat *)&id;
}

/* @draft 0x0ed314 us _ZN3Car13CCarBufferPSP8f_0ed314Eii7CarNamei4Quat4Vec4
   WHAT IT DOES: Sets the car up: its type, record, orientation and position, with the
   velocities and the other motion values cleared, reads its effect type from the database and
   sets up its wheel effects.
   DRAFT: same stores; the argument loads take other registers and the vectors' x
   stores and the integer clears are scheduled later than retail's. */
void CCarBufferPSP::f_0ed314(int type, int a, CarName n, int b, Quat q, Vec4 p)
{
    m80 = type;
    m84 = a;
    name = n;
    m88 = b;
    rot = q;
    pos = p;
    m160.Set(0, 0, 0);
    m76 = 1;
    m1752 = 1;
    m176.Set(0, 0, 0);
    m124 = 0;
    m224.Set(0, 0, 0);
    up.Set(0, 0, 0);
    m1764 = 1000000.0f;
    m1744 = 0;
    m1748 = 0;
    m1756 = 0;
    m1772 = 1000000.0f;
    m1768 = 1000000.0f;
    m1760 = 0;
    m1776 = 0;
    m1780 = 0;
    m1784 = 0;
    m1788 = 0;
    m1808 = 0;
    m1812 = 0;
    m1820 = 0;
    m1856.Set(0, 0, 0);
    m1816 = 1;
    m1888 = 0;
    m1872.Set(0, 0, 0);
    m1892 = 0;
    m1952 = 0;
    m1896 = 0;
    m1900 = 0;
    m1920.Set(0, 0, 0);
    m1936.Set(0, 0, 0);
    m1964 = 0;
    m1956 = 0;
    m1960 = 0;
    memcpy(D_24063c, f_0368e8(&D_240740, "EffectType", name.rec, 0, 0), D_1a2120);
    hit = 0;
    m2124 = D_24063c[0];
    f_100ef8(this);
}

/* @implements 0x0ed568 us _ZN3Car13CCarBufferPSP8f_0ed568Ev
   WHAT IT DOES: Sets up the hit state from the hit model for the car's type. */
void CCarBufferPSP::f_0ed568()
{
    hitState.f_0b1ba8(hit, m80);
}

/* @draft 0x0ed58c us _ZN3Car13CCarBufferPSP8f_0ed58cEv
   WHAT IT DOES: Loads the car's model, colour table, hit model and dynamics data: for the
   player's and the other cars by the record's car name ("<name>_M"), for a panel car by its
   panel type's numbered entries, and for type 0x4001 the "<record>_S" set with no dynamics.
   DRAFT: two differences: in the car name case the table and "CarName" saved
   registers are swapped (s3/s4), and the second dynamics lookup loads its arguments in another
   order. */
void CCarBufferPSP::f_0ed58c()
{
    char *rec = name.rec;
    if (rec == 0)
        return;
    switch (m80) {
    case 1:
    case 0x1001:
    case 0x8001:
        sprintf(D_240768, "%s_M", f_0368e8(&D_240740, "CarName", rec, 0, 0));
        mdl = f_002acc(f_005a38(D_1dd6b0, D_240768), "Mdl");
        sprintf(D_240768, "%s_M", name.rec);
        clut = f_002acc(f_005a38(D_1dd6b0, D_240768), "Clut");
        sprintf(D_240768, "%s_M", f_0368e8(&D_240740, "CarName", name.rec, 0, 0));
        hit = f_002acc(f_005a38(D_1dd6b0, D_240768), "Hit");
        sprintf(D_240768, "%s_M", name.rec);
        dyn = f_002acc(f_005a38(D_1dd6b0, D_240768), "Dyn");
        break;
    case 2:
    case 0x2002:
        memcpy(D_24063c, f_0368e8(&D_240740, "PanelType", rec, 0, 0), D_1a2120);
        sprintf(D_240768, "Mdl%d", D_24063c[0]);
        mdl = f_005c34(D_1dd6b0, D_240768);
        sprintf(D_240768, "Clut%d", f_036a3c(&D_240740, name.rec, D_240740.index, D_240740.count));
        clut = f_005c34(D_1dd6b0, D_240768);
        memcpy(D_24063c, f_0368e8(&D_240740, "PanelType", name.rec, 0, 0), D_1a2120);
        sprintf(D_240768, "Hit%d", D_24063c[0]);
        hit = f_005c34(D_1dd6b0, D_240768);
        sprintf(D_240768, "Dyn%d", f_036a3c(&D_240740, name.rec, D_240740.index, D_240740.count));
        dyn = f_005c34(D_1dd6b0, D_240768);
        break;
    case 0x4001:
        sprintf(D_240768, "%s_S", rec);
        mdl = f_002acc(f_005a38(D_1dd6b0, D_240768), "Mdl");
        sprintf(D_240768, "%s_S", name.rec);
        clut = f_002acc(f_005a38(D_1dd6b0, D_240768), "Clut");
        sprintf(D_240768, "%s_S", name.rec);
        hit = f_002acc(f_005a38(D_1dd6b0, D_240768), "Hit");
        dyn = 0;
        break;
    }
}

/* @implements 0x0ed938 us _ZN3Car13CCarBufferPSP8f_0ed938Ev
   WHAT IT DOES: Builds the car model from the loaded model and colour table in the colour of
   the car's grade, and when the car has a colour and a light level sets the palette from the
   colour's three bytes and the model's light levels. */
void CCarBufferPSP::f_0ed938()
{
    char *f = f_0368e8(&D_240740, "Grade", name.rec, 0, 0);
    memcpy(D_24063c, f, D_1a211c[1]);
    model.f_01dbc4(mdl, 1, clut, rec_byte() % 3);
    if (colour >= 0 && light >= 0) {
        f_026bc8(model.res, colour & 0xff, (colour >> 8) & 0xff, (colour >> 16) & 0xff);
        model.model.SetLight(light);
    }
}

/* @implements 0x0eda14 us _ZN3Car13CCarBufferPSP8f_0eda14Ev
   WHAT IT DOES: Runs the car model's per-frame update. */
void CCarBufferPSP::f_0eda14()
{
    model.f_01dee4();
}

/* @implements 0x0eda30 us _ZN3Car13CCarBufferPSP8f_0eda30Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda30() {}
/* @implements 0x0eda38 us _ZN3Car13CCarBufferPSP8f_0eda38Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda38() {}
/* @implements 0x0eda40 us _ZN3Car13CCarBufferPSP8f_0eda40Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda40() {}
/* @implements 0x0eda48 us _ZN3Car13CCarBufferPSP8f_0eda48Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda48() {}
/* @implements 0x0eda50 us _ZN3Car13CCarBufferPSP8f_0eda50Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda50() {}
/* @implements 0x0eda58 us _ZN3Car13CCarBufferPSP8f_0eda58Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda58() {}
/* @implements 0x0eda60 us _ZN3Car13CCarBufferPSP8f_0eda60Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda60() {}
/* @implements 0x0eda68 us _ZN3Car13CCarBufferPSP8f_0eda68Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda68() {}
/* @implements 0x0eda70 us _ZN3Car13CCarBufferPSP8f_0eda70Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda70() {}
/* @implements 0x0eda78 us _ZN3Car13CCarBufferPSP8f_0eda78Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda78() {}
/* @implements 0x0eda80 us _ZN3Car13CCarBufferPSP8f_0eda80Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda80() {}
/* @implements 0x0eda88 us _ZN3Car13CCarBufferPSP8f_0eda88Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda88() {}
/* @implements 0x0eda90 us _ZN3Car13CCarBufferPSP8f_0eda90Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0eda90() {}
/* @implements 0x0eda98 us _ZN3Car13CCarBufferPSP8f_0eda98Ev
   WHAT IT DOES: Empty query; returns 0. */
int CCarBufferPSP::f_0eda98() { return 0; }
/* @implements 0x0edaa0 us _ZN3Car13CCarBufferPSP8f_0edaa0Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0edaa0() {}
/* @implements 0x0edaa8 us _ZN3Car13CCarBufferPSP8f_0edaa8Ev
   WHAT IT DOES: Empty query; returns 0. */
int CCarBufferPSP::f_0edaa8() { return 0; }
/* @implements 0x0edab0 us _ZN3Car13CCarBufferPSP8f_0edab0Ev
   WHAT IT DOES: Empty hook. */
void CCarBufferPSP::f_0edab0() {}

/* A file scope object whose construction needs no code. */
struct CEmpty {
    CEmpty() {}
};
static CEmpty D_empty;

/* @implements 0x0edab8 us __static_initialization_and_destruction_0
   WHAT IT DOES: This file's static set up, which has nothing to do. */
/* @implements 0x0edac0 us _GLOBAL__I__ZN3Car13CCarBufferPSPC2Ev
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x0edae0 us _ZN7CCarDynC1Ev
   (retail emits it after the static init, in a link once section; an out of line definition
   gives the same code)
   WHAT IT DOES: The dynamics block's constructor: clears its four sets of Euler angles. */
CCarDyn::CCarDyn()
{
}
