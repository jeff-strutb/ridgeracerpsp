/* The camera view (retail 0x0cbfe4 to 0x0ccab4): an eye position with its view, projection
   and combined matrices, the viewport, and two sets of four clip planes kept in the VFPU's
   matrices 5 and 6. Setting the view by any of the view projection builders refreshes all
   of it; the box tests at the end test a bounding sphere against the planes in the VFPU. */

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Matrix {
    float m[16];
} __attribute__((aligned(16)));

#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

extern "C" {
float f_027ebc(const Vec4 *a, const Vec4 *b);
void f_028c70(void);
void f_028ca8(void);
int f_027f74(Vec4 *out, const Vec4 *in);
void f_028e9c(const Matrix *m);
void f_028d94(Matrix *m);
void f_028dac(Matrix *out);
void f_028df0(Matrix *out);
void f_0287a0(void);
void f_02842c(void);
void f_028748(const Matrix *m);
Vec4 *f_027f5c(Vec4 *d, const Vec4 *a);
void f_0cd4d0(const Matrix *m);
void f_0cd688(const Vec4 *eye, const Vec4 *dir, const Vec4 *up);
void f_0cd7c0(const Vec4 *eye, const Vec4 *at, const Vec4 *up);
void f_0cd90c(const Vec4 *eye, float x, float y, float z);
void f_0cd9c0(const Vec4 *eye, float x, float y, float z);
void f_0cda74(const Vec4 *a, const Vec4 *b, float angle);
void f_0cde70(float s, float aspect, float n, float f);
void f_0ce068(int type, const Matrix *m);
void f_0ce084(int x, int y, int w, int h);
void f_0ce0b0(Matrix *a, Matrix *b, float s, float aspect, float c, float d, float e);
}

/* A float's bits, for the graphics engine's 24-bit float command arguments. */
static inline unsigned int Bits(float f)
{
    union {
        float f;
        unsigned int u;
    } b;
    b.f = f;
    return b.u;
}

class CView {
public:
    int Project(short *sx, short *sy, float *sz, const Vec4 *p);
    void LookAt(const Vec4 *at, const Vec4 *up);
    void Rotate(const Vec4 *b, float angle);
    void SetEuler(float x, float y, float z);
    void SetEulerYXZ(float x, float y, float z);
    void LookDir(const Vec4 *dir, const Vec4 *up);
    void SetView(const Matrix *m);
    void Update();
    void UpdateProj();
    void Combine(Matrix *out);
    void Apply();
    unsigned int *PutViewport(unsigned int *p);
    unsigned int *Put(unsigned int *p);
    void LoadClip();
    int InSphere(const Vec4 *c, float r);
    int InSphereNear(const Vec4 *c, float r);
    int InsideFar(const Vec4 *c, float r);
    int OutsideFar(const Vec4 *c, float r);

    Vec4 pos;
    Matrix clipA;       /* four clip planes (rows), as built */
    Matrix clipB;
    Vec4 planeA[4];     /* the same normalised, with their distances from the eye */
    Vec4 planeB[4];
    float fwd[3];       /* the viewing direction */
    Matrix view;
    Matrix proj;
    Matrix viewProj;
    int m480;
    float aspect;
    float zNear;
    float zFar;
    float scale;
    int m500;
    int w;
    int h;
    int x;
    int y;
    float halfW;
    float halfH;
    float m528;
    float m532;
};

/* @implements 0x0cbfe4 us _ZN5CView7Project
   WHAT IT DOES: Projects a point to the screen: returns 0 when it is behind the far plane
   or outside 1.3 times the view in x or y, else writes the screen position and depth and
   returns 1. */
int CView::Project(short *sx, short *sy, float *sz, const Vec4 *p)
{
    Vec4 v;
    int r;

    f_028c70();
    f_028e9c(&viewProj);
    r = f_027f74(&v, p);
    f_028ca8();
    if (!r)
        return 0;
    if (1.0f <= v.z)
        return 0;
    if (1.3f < v.x)
        return 0;
    if (v.x < -1.3f)
        return 0;
    if (1.3f < v.y)
        return 0;
    if (v.y < -1.3f)
        return 0;
    *sx = (short)(v.x * (halfW * (float)m500) + halfW);
    *sy = (short)(halfH - halfH * v.y);
    *sz = v.z;
    return 1;
}

/* @implements 0x0cc118 us _ZN5CView6LookAt
   WHAT IT DOES: Looks from the eye at a point, then refreshes the view. */
void CView::LookAt(const Vec4 *at, const Vec4 *up)
{
    f_0cd7c0(&pos, at, up);
    Update();
}

/* @implements 0x0cc144 us _ZN5CView6Rotate
   WHAT IT DOES: Rotates the view about the axis from the eye to a point, then refreshes. */
void CView::Rotate(const Vec4 *b, float angle)
{
    f_0cda74(&pos, b, angle);
    Update();
}

/* @implements 0x0cc170 us _ZN5CView8SetEuler
   WHAT IT DOES: Sets the view from Euler angles (x, y, z order) at the eye, then
   refreshes. */
void CView::SetEuler(float ax, float ay, float az)
{
    f_0cd90c(&pos, ax, ay, az);
    Update();
}

/* @implements 0x0cc19c us _ZN5CView11SetEulerYXZ
   WHAT IT DOES: Sets the view from Euler angles (y, x, z order) at the eye, then
   refreshes. */
void CView::SetEulerYXZ(float ax, float ay, float az)
{
    f_0cd9c0(&pos, ax, ay, az);
    Update();
}

/* @implements 0x0cc1c8 us _ZN5CView7LookDir
   WHAT IT DOES: Looks from the eye along a direction, then refreshes the view. */
void CView::LookDir(const Vec4 *dir, const Vec4 *up)
{
    f_0cd688(&pos, dir, up);
    Update();
}

/* @implements 0x0cc1f4 us _ZN5CView7SetView
   WHAT IT DOES: Takes a view matrix as it is, then refreshes the view. */
void CView::SetView(const Matrix *m)
{
    f_0cd4d0(m);
    Update();
}

/* @implements 0x0cc224 us _ZN5CView6Update
   WHAT IT DOES: Copies the view matrix in, keeps its viewing direction, rebuilds the
   projection and the combined matrix, builds the clip planes and moves them into view
   space (normalised, with their distance from the eye), and loads them into the VFPU. */
void CView::Update()
{
    Matrix save;
    int i;

    f_028dac(&view);
    fwd[0] = view.m[2];
    fwd[1] = view.m[6];
    fwd[2] = view.m[10];
    UpdateProj();
    Combine(&viewProj);
    f_0ce0b0(&clipA, &clipB, scale, aspect, halfH, m528, m532);
    f_028d94(&save);
    f_028e9c(&view);
    f_0287a0();
    for (i = 0; i < 4; i++) {
        f_027f5c(&planeA[i], (Vec4 *)&clipA.m[i * 4]);
        planeA[i].w = -f_027ebc(&planeA[i], &pos);
        f_027f5c(&planeB[i], (Vec4 *)&clipB.m[i * 4]);
        planeB[i].w = -f_027ebc(&planeB[i], &pos);
    }
    LoadClip();
    f_028e9c(&save);
}

/* @implements 0x0cc344 us _ZN5CView10UpdateProj
   WHAT IT DOES: Builds the perspective projection and copies it in. */
void CView::UpdateProj()
{
    f_0cde70(scale, aspect, zNear, zFar);
    f_028df0(&proj);
}

/* @implements 0x0cc384 us _ZN5CView7Combine
   WHAT IT DOES: Writes projection times view into out, leaving the matrix stack as it
   was. */
void CView::Combine(Matrix *out)
{
    Matrix save;

    f_028d94(&save);
    f_02842c();
    f_028748(&proj);
    f_028748(&view);
    f_028d94(out);
    f_028e9c(&save);
}

/* @implements 0x0cc3e4 us _ZN5CView5Apply
   WHAT IT DOES: Hands the viewport, the view and the projection to the graphics engine and
   loads the clip planes. */
void CView::Apply()
{
    int a = x, b = y, c = w, d = h;
    f_0ce084(a, b, c, d);
    f_0ce068(1, &view);
    f_0ce068(0, &proj);
    LoadClip();
}

/* @draft 0x0cc438 us _ZN5CView11PutViewport
   WHAT IT DOES: Writes the viewport scale and offset commands into a display list; returns
   the next free word.
   DIFFERS: FP register choice for the converted values (retail converts the negated half
   height from a separate register, f4 into f3) and the order of the first two loads; all
   24 orders of the four locals tried, also int locals and an inline helper. */
unsigned int *CView::PutViewport(unsigned int *p)
{
    float sw = (float)(w / 2);
    float sh = (float)-(h / 2);
    float ox = (float)x;
    float oy = (float)y;
    *p = (Bits(sw) >> 8) | 0x42000000;
    p++;
    *p = (Bits(sh) >> 8) | 0x43000000;
    p++;
    *p = (Bits(ox) >> 8) | 0x45000000;
    p++;
    *p = (Bits(oy) >> 8) | 0x46000000;
    p++;
    return p;
}

/* @draft 0x0cc4e4 us _Z11PutViewportiiiiPj
   WHAT IT DOES: The same for a given viewport.
   DIFFERS: FP register choice only, as in the member version. */
unsigned int *PutViewport(int x, int y, int w, int h, unsigned int *p)
{
    float sw = (float)(w / 2);
    float sh = (float)-(h / 2);
    float ox = (float)x;
    float oy = (float)y;
    *p = (Bits(sw) >> 8) | 0x42000000;
    p++;
    *p = (Bits(sh) >> 8) | 0x43000000;
    p++;
    *p = (Bits(ox) >> 8) | 0x45000000;
    p++;
    *p = (Bits(oy) >> 8) | 0x46000000;
    p++;
    return p;
}

#define VIEW_WORD(k) *p = (((const unsigned int *)view.m)[k] >> 8) | 0x3d000000; p++;
#define PROJ_WORD(k) *p = (((const unsigned int *)proj.m)[k] >> 8) | 0x3f000000; p++;

/* @draft 0x0cc584 us _ZN5CView3Put
   WHAT IT DOES: Writes the viewport, the view matrix's 4x3 part and the projection matrix
   into a display list, and loads the clip planes; returns the next free word.
   DIFFERS: only the viewport part's FP registers, as in PutViewport. */
unsigned int *CView::Put(unsigned int *p)
{
    float sw = (float)(w / 2);
    float sh = (float)-(h / 2);
    float ox = (float)x;
    float oy = (float)y;
    *p = (Bits(sw) >> 8) | 0x42000000;
    p++;
    *p = (Bits(sh) >> 8) | 0x43000000;
    p++;
    *p = (Bits(ox) >> 8) | 0x45000000;
    p++;
    *p = (Bits(oy) >> 8) | 0x46000000;
    p++;
    *p = 0x3c000000;
    p++;
    VIEW_WORD(0) VIEW_WORD(1) VIEW_WORD(2)
    VIEW_WORD(4) VIEW_WORD(5) VIEW_WORD(6)
    VIEW_WORD(8) VIEW_WORD(9) VIEW_WORD(10)
    VIEW_WORD(12) VIEW_WORD(13) VIEW_WORD(14)
    *p = 0x3e000000;
    p++;
    PROJ_WORD(0) PROJ_WORD(1) PROJ_WORD(2) PROJ_WORD(3)
    PROJ_WORD(4) PROJ_WORD(5) PROJ_WORD(6) PROJ_WORD(7)
    PROJ_WORD(8) PROJ_WORD(9) PROJ_WORD(10) PROJ_WORD(11)
    PROJ_WORD(12) PROJ_WORD(13) PROJ_WORD(14) PROJ_WORD(15)
    LoadClip();
    return p;
}

/* @implements 0x0cc8a0 us _ZN5CView8LoadClip
   WHAT IT DOES: Loads the second plane set into VFPU matrix 5 and the first into matrix 6
   (as rows). */
void CView::LoadClip()
{
    __asm__ volatile(VFPU_BEGIN "lv.q R500, 208(%0)\n\tlv.q R501, 224(%0)\n\tlv.q R502, 240(%0)\n\tlv.q R503, 256(%0)\n\t"
                     "lv.q R600, 144(%0)\n\tlv.q R601, 160(%0)\n\tlv.q R602, 176(%0)\n\tlv.q R603, 192(%0)" VFPU_END
                     : : "r"(this) : "memory");
}

/* @implements 0x0cc8c8 us _ZN5CView8InSphere
   WHAT IT DOES: Whether a sphere reaches inside all four first planes (each plane distance
   plus the radius is positive). */
int CView::InSphere(const Vec4 *c, float r)
{
    Vec4 d;

    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvone.s S403\n\tvtfm4.q C410, E600, C400\n\tlv.s S420, %2\n\t"
                     ".word 0xdd000000\n\tvadd.q C430, C410, C420\n\tsv.q C430, %0" VFPU_END
                     : "=m"(d) : "r"(c), "m"(r) : "memory");
    return d.x > 0.0f && d.y > 0.0f && d.z > 0.0f && d.w > 0.0f;
}

/* @implements 0x0cc940 us _ZN5CView12InSphereNear
   WHAT IT DOES: Whether a sphere lies wholly inside the four first planes. */
int CView::InSphereNear(const Vec4 *c, float r)
{
    Vec4 d;

    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvone.s S403\n\tvtfm4.q C410, E600, C400\n\tlv.s S420, %2\n\t"
                     ".word 0xdd000000\n\tvsub.q C430, C410, C420\n\tsv.q C430, %0" VFPU_END
                     : "=m"(d) : "r"(c), "m"(r) : "memory");
    return d.x > 0.0f && d.y > 0.0f && d.z > 0.0f && d.w > 0.0f;
}

/* @implements 0x0cc9b8 us _ZN5CView9InsideFar
   WHAT IT DOES: Whether a sphere lies wholly inside the four second planes. */
int CView::InsideFar(const Vec4 *c, float r)
{
    Vec4 d;

    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvone.s S403\n\tvtfm4.q C410, E500, C400\n\tlv.s S420, %2\n\t"
                     ".word 0xdd000000\n\tvsub.q C430, C410, C420\n\tsv.q C430, %0" VFPU_END
                     : "=m"(d) : "r"(c), "m"(r) : "memory");
    return d.x > 0.0f && d.y > 0.0f && d.z > 0.0f && d.w > 0.0f;
}

/* @implements 0x0cca30 us _ZN5CView10OutsideFar
   WHAT IT DOES: Which of the four second planes a sphere crosses or lies outside of, as
   bits 0 to 3. */
int CView::OutsideFar(const Vec4 *c, float r)
{
    Vec4 d;
    int m = 0;

    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%1)\n\tvone.s S403\n\tvtfm4.q C410, E500, C400\n\tlv.s S420, %2\n\t"
                     ".word 0xdd000000\n\tvsub.q C430, C410, C420\n\tsv.q C430, %0" VFPU_END
                     : "=m"(d) : "r"(c), "m"(r) : "memory");
    if (d.x < 0.0f)
        m = 1;
    if (d.y < 0.0f)
        m |= 2;
    if (d.z < 0.0f)
        m |= 4;
    if (d.w < 0.0f)
        m |= 8;
    return m;
}

/* @implements 0x0ccab4 us ZeroOne
   WHAT IT DOES: Returns 0. */
float ZeroOne()
{
    return 0.0f;
}

/* @implements 0x0ccac0 us ZeroTwo
   WHAT IT DOES: Returns 0. */
float ZeroTwo()
{
    return 0.0f;
}

/* @implements 0x0ccacc us OneOne
   WHAT IT DOES: Returns 1. */
float OneOne()
{
    return 1.0f;
}

/* @implements 0x0ccad8 us ZeroThree
   WHAT IT DOES: Returns 0. */
float ZeroThree()
{
    return 0.0f;
}

/* @implements 0x0ccae4 us _Z7NoValuev
   WHAT IT DOES: Returns 0. */
int NoValue()
{
    return 0;
}
