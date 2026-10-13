/* The race 2D overlay base object file (retail 0x089438 to 0x0897ec). Fj::CRace2DBase is the
   common part of the race's 2D screens (the normal race overlay and the movie player one): it
   owns the screen fade mask (Fj::CFadeMask) and starts its fades. The file also holds the
   three static objects (the movie player overlay, the normal overlay and the fade mask) and
   the pointer to the overlay in use. */

extern "C" {
void f_021720(void);
void f_021750(void);
}

struct Pos16 {
    unsigned short x, y, z;
};
void f_02231c(const Pos16 *v, unsigned int color);
void f_0f6314(void *p, int a, unsigned char b);

namespace Fj {

/* A full screen colour mask that fades in or out. */
class CFadeMask {
public:
    CFadeMask()
    {
        on = 0;
        hold = 0;
        color = 0xff000000;
        frames = 0;
        rate = 0;
        frame = 0;
        alpha = 0xff000000;
    }
    virtual ~CFadeMask() {}
    int f_089548();
    void f_0895cc();

    bool on;
    int hold;
    unsigned int color;
    unsigned int alpha;
    float frames;
    float rate;
    float frame;
};

class CRace2DBase {
public:
    CRace2DBase()
    {
        mode = 0;
        m24 = 0;
        m28 = 0;
        m40 = 0;
        m1580 = 0;
        m1584 = 0;
        fade = 0;
    }
    virtual ~CRace2DBase() {}
    virtual int f_089464(int a, int b);
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    void f_089478(int a, int b);
    void f_089498(bool on);
    void f_0894b0(int frames);
    void f_089500(int frames);

    int mode;
    int m8[4];
    int m24;
    int m28;
    int m32[2];
    int m40;
    int m44[3][128];
    int m1580;
    int m1584;
    CFadeMask *fade;
    void *m1592;
};

class CRace2DNormal : public CRace2DBase {
public:
    CRace2DNormal() {}
    virtual ~CRace2DNormal() {}
    virtual int f_089464(int a, int b);
    virtual void v3();
    virtual void v4();
    virtual void v5();
};

class CRace2DAvPlayer : public CRace2DBase {
public:
    CRace2DAvPlayer() {}
    virtual ~CRace2DAvPlayer() {}
    virtual int f_089464(int a, int b);
    virtual void v3();
    virtual void v4();
    virtual void v5();
    int m1596;
};

}

using namespace Fj;

CRace2DAvPlayer D_241eb4;
CRace2DNormal D_2424f4;
CFadeMask D_242b30;
extern CRace2DBase *D_1d3d40;

/* @implements 0x089438 us f_089438
   WHAT IT DOES: Picks the overlay in use (the movie player one when mode is set, else the
   normal one) and gives it the mode. */
void f_089438(int mode)
{
    if (!mode)
        D_1d3d40 = &D_2424f4;
    else
        D_1d3d40 = &D_241eb4;
    D_1d3d40->mode = mode;
}

/* @implements 0x089464 us CRace2DBase8f_089464
   WHAT IT DOES: The common start: attaches the fade mask. */
int CRace2DBase::f_089464(int a, int b)
{
    fade = &D_242b30;
    return 1;
}

/* @implements 0x089478 us f_089478
   WHAT IT DOES: Passes a request on to the attached object at +1592. */
void CRace2DBase::f_089478(int a, int b)
{
    f_0f6314(m1592, a, b);
}

/* @implements 0x089498 us f_089498
   WHAT IT DOES: Shows or hides the fade mask, black and with no fade alpha. */
void CRace2DBase::f_089498(bool on)
{
    CFadeMask *f = fade;
    f->on = on;
    f->color = 0xff000000;
    f->alpha = 0;
}

/* @implements 0x0894b0 us f_0894b0
   WHAT IT DOES: Starts a fade from black over the given number of frames (the mask hides when
   it is done). */
void CRace2DBase::f_0894b0(int frames)
{
    float n = (float)frames;
    CFadeMask *f = fade;
    f->on = 1;
    f->color = 0xff000000;
    f->hold = 0;
    f->frames = n;
    f->frame = 0;
    f->alpha = 0;
    f->rate = -(1.0f / n) * 255.0f;
}

/* @implements 0x089500 us f_089500
   WHAT IT DOES: Starts a fade to black over the given number of frames (the mask stays). */
void CRace2DBase::f_089500(int frames)
{
    float n = (float)frames;
    CFadeMask *f = fade;
    int one = 1;
    f->hold = one;
    f->on = one;
    f->frames = n;
    f->frame = 0;
    f->color = 0;
    f->alpha = 0;
    f->rate = (1.0f / n) * 255.0f;
}

/* @implements 0x089548 us f_089548
   WHAT IT DOES: Steps a running fade by one frame and sets the mask's alpha from it; at the
   end stops the fade and, unless the mask is to stay, hides it. */
int CFadeMask::f_089548()
{
    if (frames != 0.0f) {
        if (frame < frames) {
            float t = frame + 50.0f;
            int a = (int)(rate * t);
            frame = t;
            if (a > 255)
                a = 255;
            alpha = a << 24;
        } else {
            frames = 0.0f;
            if (!hold) {
                color = 0xff000000;
                alpha = 0;
                on = 0;
            }
        }
    }
    return 1;
}

/* @implements 0x0895cc us f_0895cc
   WHAT IT DOES: Draws the mask over the whole screen while it is shown. */
void CFadeMask::f_0895cc()
{
    if (on) {
        Pos16 r[2];
        f_021720();
        r[0].x = 0;
        r[0].y = 0;
        r[0].z = 0xffff;
        r[1].x = 480;
        r[1].y = 272;
        r[1].z = 0xffff;
        f_02231c(r, color + alpha);
        f_021750();
    }
}

/* @draft 0x089644 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs (or destroys) the two overlays and the fade mask.
   Remaining difference: only the order of the constructors' zero stores. Retail interleaves
   them: the two overlays' +4..+40 words, then the movie player overlay's +1580/+1584, the
   vtables, the normal overlay's +1588, the mask's +28, then the rest; here each object's
   stores stay together. */

/* @implements 0x08973c us _GLOBAL__I_
   WHAT IT DOES: Static construction of the file's objects. */

/* @implements 0x08975c us _GLOBAL__D_
   WHAT IT DOES: Static destruction of the file's objects. */

/* @implements 0x08977c us _ZN2Fj11CRace2DBaseD1Ev
   WHAT IT DOES: The overlay base destructor (resets the vtable). */

/* @implements 0x08978c us _ZN2Fj11CRace2DBaseD0Ev
   WHAT IT DOES: The overlay base deleting destructor. */

/* @implements 0x0897b4 us _ZN2Fj9CFadeMaskD1Ev
   WHAT IT DOES: The fade mask destructor (resets the vtable). */

/* @implements 0x0897c4 us _ZN2Fj9CFadeMaskD0Ev
   WHAT IT DOES: The fade mask deleting destructor. */
