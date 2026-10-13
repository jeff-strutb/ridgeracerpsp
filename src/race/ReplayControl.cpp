/* The replay controller object file (retail 0x07df70 to 0x07f564). During a replay it reads
   the recorded race's length from the "Replay" package entry, advances the replay clock,
   handles the pad (skip, camera change), switches between the replay cameras and drives the
   replay's mode handlers, which the race sequence calls through a table of member pointers. */

void *f_005c34(char *seq, const char *name);
extern char D_1dd6b0[];

namespace Controller {
struct CCustomController {
    int f_0437cc(int i);
};
}
extern Controller::CCustomController D_1d8910[1];

/* The replay's recorded header: the recorded length at +16 (frames). */
struct ReplayInfo {
    int m0[4];
    int length;
};

/* An object driven through its vtable (the replay camera and the replay overlays). */
struct ReplayPart {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Start(int);
    virtual void Step();
    virtual void Show();
    virtual void Stop();
};

/* The overlay object at +3248. */
struct ReplayOverlay : ReplayPart {
    char m4[736];
    int m740;
};

struct ReplayState {
    char m0[24];
    int m24;
};
extern ReplayState *D_1d3d40;

struct ReplayFlags {
    int m0;
    int m4;
};
extern ReplayFlags D_241754;
extern float D_241450;
extern int D_241454;

struct ReplayView {
    char m0[664];
    int m664;
};

struct Replay {
    char m0[3060];
    ReplayPart *cam[11];
    ReplayView *m3104;
    char m3108[20];
    ReplayInfo *info;
    char m3132[8];
    int mode;
    int curMode;
    char m3148[4];
    ReplayPart *curCam;
    char m3156[16];
    int m3172;
    int clock;
    char m3180[16];
    int m3196;
    char m3200[4];
    int m3204;
    char m3208[4];
    int m3212;
    char m3216[32];
    ReplayOverlay *m3248;
    ReplayPart *m3252;
};

extern "C" void f_07ee5c(Replay *r);
extern "C" void f_07ebdc(Replay *r);
extern "C" void f_07ecb8(Replay *r);
extern "C" void f_07edd4(Replay *r);

/* @implements 0x07df70 us f_07df70
   WHAT IT DOES: Finds the recorded replay ("Replay" in the race package), keeps its header
   and returns its length in units of five frames. */
extern "C" int f_07df70(Replay *r)
{
    ReplayInfo *info = (ReplayInfo *)f_005c34(D_1dd6b0, "Replay");
    r->info = info;
    return info->length / 5;
}

/* @implements 0x07dfcc us f_07dfcc
   WHAT IT DOES: Returns the value at +3196 in units of five frames. */
extern "C" int f_07dfcc(Replay *r)
{
    return r->m3196 / 5;
}

/* @implements 0x07ebc4 us f_07ebc4
   WHAT IT DOES: Nothing. */
extern "C" void f_07ebc4(Replay *r)
{
}

/* @implements 0x07ebcc us f_07ebcc
   WHAT IT DOES: Nothing. */
extern "C" void f_07ebcc(Replay *r)
{
}

/* @implements 0x07ebd4 us f_07ebd4
   WHAT IT DOES: Nothing. */
extern "C" void f_07ebd4(Replay *r)
{
}

/* @implements 0x07ebdc us f_07ebdc
   WHAT IT DOES: On the camera button (pad trigger 5) toggles between the two replay views:
   from view 0 it asks for view 1 and clears the display flag that matches the screen mode,
   from view 1 it asks for view 0 and sets it again. */
extern "C" void f_07ebdc(Replay *r)
{
    if (!D_1d8910[0].f_0437cc(5))
        return;
    if (r->curMode == 0) {
        r->mode = 1;
        if (r->m3204)
            D_241754.m4 &= ~0x10000;
        else
            D_241754.m4 &= ~0x8000;
    } else if (r->curMode == 1) {
        r->mode = 0;
        if (r->m3204)
            D_241754.m4 |= 0x10000;
        else
            D_241754.m4 |= 0x8000;
    }
}

/* @implements 0x07eca8 us f_07eca8
   WHAT IT DOES: Nothing. */
extern "C" void f_07eca8(Replay *r)
{
}

/* @implements 0x07ecb0 us f_07ecb0
   WHAT IT DOES: Nothing. */
extern "C" void f_07ecb0(Replay *r)
{
}

/* @implements 0x07ecb8 us f_07ecb8
   WHAT IT DOES: Advances the replay clock. While the recording lasts it shows the overlay,
   publishes the clock as a float and selects view 4, then steps the overlay (state 16). At
   the end (or at once for an empty recording) it settles the view once from the display
   flags, hides the overlay and steps the second part instead (state 17). */
extern "C" void f_07ecb8(Replay *r)
{
    f_07ee5c(r);
    if (r->clock < r->info->length) {
        r->m3248->m740 = 1;
        r->m3172 = 0;
        D_241450 = r->clock;
        D_241454 = 0;
        r->mode = 4;
        r->m3248->Show();
        D_1d3d40->m24 = 16;
        return;
    }
    if (r->clock == r->info->length || (r->info->length == 0 && r->m3212 == 0)) {
        r->m3212 = 1;
        if (r->m3204 == 0) {
            if (D_241754.m4 & 0x8000)
                r->mode = 0;
            else
                r->mode = 1;
        } else {
            if (D_241754.m4 & 0x10000)
                r->mode = 0;
            else
                r->mode = 1;
        }
        r->m3248->m740 = 0;
    }
    r->m3252->Show();
    D_1d3d40->m24 = 17;
}

/* @implements 0x07edd4 us f_07edd4
   WHAT IT DOES: Switches the replay camera when the requested view changed: marks the view
   for a redraw, stops the current camera, takes the camera for the new view and starts it. */
extern "C" void f_07edd4(Replay *r)
{
    if (r->mode == r->curMode)
        return;
    r->m3104->m664 = 1;
    if (r->curCam)
        r->curCam->Stop();
    r->curMode = r->mode;
    r->curCam = r->cam[r->mode];
    r->curCam->Start(0);
}

/* @implements 0x07ee5c us f_07ee5c
   WHAT IT DOES: Advances the replay clock by 5, up to the limit of 1260000. */
extern "C" void f_07ee5c(Replay *r)
{
    if (r->clock < 1260000)
        r->clock += 5;
}

/* @implements 0x07eec8 us f_07eec8
   WHAT IT DOES: One replay frame: pad handling, the clock and overlays, the camera switch and
   the current camera's step. */
extern "C" void f_07eec8(Replay *r)
{
    f_07ebdc(r);
    f_07ecb8(r);
    f_07edd4(r);
    r->curCam->Step();
}
