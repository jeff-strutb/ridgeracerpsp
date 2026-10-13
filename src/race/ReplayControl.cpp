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

/* A camera event: from its time on, the replay uses this view and camera parameter; a
   negative time ends the list. */
struct ReplayEvent {
    float time;
    int mode;
    int sub;
};

/* The replay's recorded header: the recorded length at +16 (frames) and the offsets of three
   camera event lists. */
struct ReplayInfo {
    int m0[2];
    int m8;
    int m12;
    int length;
    int m20;
    struct {
        int m0;
        int off;
    } list[3];
    ReplayEvent *List(int k) { return (ReplayEvent *)(list[k].off + (int)this); }
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    float f_0e3b3c(float a, float b);
};
struct MapMgr {
    CourseAreas *Areas() { return &m12240; }
    char m0[12240];
    CourseAreas m12240;
};
extern MapMgr D_23c820;

/* An object driven through its vtable (the replay camera and the replay overlays). */
struct ReplayPart {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Start(int *arg);
    virtual void Step();
    virtual void Show();
    virtual void Stop();
};

/* The overlay object at +3248. */
struct ReplayOverlay : ReplayPart {
    char m4[736];
    int m740;
    char m744[8];
    int m752;
};

/* The player's car as the replay sees it: the race time at +2144 and the lap at +2212. */
struct ReplayCar {
    char m0[2144];
    float time;
    char m2148[64];
    int lap;
};

int f_0f2de8(ReplayPart *cam);

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
    char m3108[4];
    ReplayCar *car;
    char m3116[12];
    ReplayInfo *info;
    char m3132[8];
    int mode;
    int curMode;
    char m3148[4];
    ReplayPart *curCam;
    int m3156;
    int m3160;
    int m3164;
    int m3168;
    int list;
    int clock;
    float bestTime;
    int bestLap;
    int m3188;
    ReplayEvent *ev;
    int m3196;
    char m3200[4];
    int m3204;
    char m3208[4];
    int m3212;
    int m3216;
    char m3220[4];
    int m3224;
    int m3228;
    char m3232[16];
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

/* Defined at the end of the file: these callers must not see that it is empty (retail
   reloads fields after calling it). */
extern "C" void f_07eca8(Replay *r);

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
        r->list = 0;
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

#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* @implements 0x07ef10 us f_07ef10
   WHAT IT DOES: Tracks the player's progress for the replay after the recording ends: keeps
   the best lap and time reached, notes when the car comes within 40 of that time on the
   course, and once it has caught up again shows the finish overlay. Picks the camera event
   list from the lap (lap + 2, at most 2); list 0 while the recording still lasts. */
extern "C" void f_07ef10(Replay *r)
{
    ReplayInfo *info = r->info;
    ReplayCar *car = r->car;
    int lap = car->lap;
    float t = car->time;
    int n;

    if (r->clock < info->length) {
        r->list = 0;
        return;
    }
    if (r->bestLap < lap) {
        r->bestTime = t;
        r->bestLap = lap;
    } else if (r->bestLap == lap && r->bestTime < t) {
        r->bestTime = t;
    }
    if (r->m3228 == 0) {
        if (D_23c820.Areas()->f_0e3b3c(t, r->bestTime) < -40.0f)
            r->m3228 = 1;
    }
    if (r->m3228) {
        if (lap >= r->bestLap && r->bestTime <= t) {
            r->m3216 = 1;
            r->m3228 = 0;
            r->m3248->m752 = 0;
        }
    }
    n = r->bestLap + 2;
    r->list = n;
    if (n > 2)
        r->list = 2;
}

/* @implements 0x07f04c us f_07f04c
   WHAT IT DOES: In view 2, once the camera parameter has been applied, asks the view 2 camera
   whether it has finished and then moves to view 4; in any other case clears the finished
   flag. */
extern "C" void f_07f04c(Replay *r)
{
    if (r->mode == 2 && r->m3160 == r->m3156) {
        if (f_0f2de8(r->cam[2]))
            r->m3224 = 1;
        if (r->m3224)
            r->mode = 4;
        return;
    }
    r->m3224 = 0;
}

/* @implements 0x07f0bc us f_07f0bc
   WHAT IT DOES: Switches the replay camera when the requested view (low half of the mode) or
   the camera parameter changed: stops the current camera, takes the new one and starts it
   with the parameter, which comes from the mode's high half (less one) or the current
   camera event. Flags the change at +3168. */
extern "C" void f_07f0bc(Replay *r)
{
    int arg;

    if (r->mode == r->curMode && r->m3160 == r->m3156) {
        r->m3168 = 0;
        return;
    }
    r->m3168 = 1;
    if (r->curCam)
        r->curCam->Stop();
    r->curMode = r->mode;
    r->m3156 = r->m3160;
    r->curCam = r->cam[r->mode & 0xffff];
    arg = 0;
    if (r->list) {
        if (r->mode >> 16)
            arg = (r->mode >> 16) - 1;
        else
            arg = r->ev->sub;
    }
    if (r->curCam)
        r->curCam->Start(&arg);
}

/* @implements 0x07f194 us f_07f194
   WHAT IT DOES: The common end of a replay frame: draws both overlays, settles the view 2
   finish, forces camera 3 with parameter 1 in state 4 once the car has caught up, switches
   the camera, steps it and marks the view for a redraw after a switch. */
extern "C" void f_07f194(Replay *r)
{
    r->m3248->Show();
    r->m3252->Show();
    r->m3168 = 0;
    f_07f04c(r);
    if (r->m3164 == 4 && r->m3228)
        r->mode = 0x10003;
    f_07f0bc(r);
    r->curCam->Step();
    if (r->m3168)
        r->m3104->m664 = 1;
}

/* @implements 0x07f240 us f_07f240
   WHAT IT DOES: Replay mode handler: advances the clock and the progress tracking; while the
   recording lasts uses view 4 with the overlay shown (state 16), afterwards follows the
   chosen camera event list with the overlay hidden (state 17). In state 4 steps through the
   events up to the best time and takes the event's view and parameter. Publishes the time
   and the list number (0 to 9, else 6) and ends the frame. */
extern "C" void f_07f240(Replay *r)
{
    int n;

    f_07ee5c(r);
    f_07ef10(r);
    if (r->list == 0) {
        r->mode = 4;
        r->m3248->m740 = 1;
        r->ev = 0;
        D_1d3d40->m24 = 16;
    } else {
        r->ev = r->info->List(r->list);
        r->m3248->m740 = 0;
        D_1d3d40->m24 = 17;
    }
    f_07eca8(r);
    if (r->m3164 == 4 && r->list) {
        while (r->ev[1].time >= 0.0f && r->ev[1].time < r->bestTime)
            r->ev++;
        r->mode = r->ev->mode;
        r->m3160 = r->ev->sub;
    }
    if (r->list == 0)
        D_241450 = r->clock;
    else
        D_241450 = r->bestTime;
    n = MAX(r->list, 0);
    if (n >= 10)
        n = 6;
    D_241454 = n;
    f_07f194(r);
}

/* @implements 0x07f3b4 us f_07f3b4
   WHAT IT DOES: Replay mode handler for the finished race: advances the clock and the
   progress tracking, follows the chosen camera event list with the overlay hidden, in state
   4 steps through the events up to the replay clock (until the length at +8, unless the
   flag at +3188 is 1) or else up to the best time, publishes the best time and the list
   number and ends the frame. */
extern "C" void f_07f3b4(Replay *r)
{
    ReplayInfo *info;
    ReplayEvent *ev;
    int n;

    f_07ee5c(r);
    f_07ef10(r);
    info = r->info;
    ev = info->List(r->list);
    r->m3248->m740 = 0;
    r->ev = ev;
    f_07eca8(r);
    if (r->m3164 == 4) {
        if (r->clock < info->m8 && r->m3188 != 1) {
            while (ev[1].time >= 0.0f && ev[1].time < r->clock) {
                r->ev++;
                ev = r->ev;
            }
        } else {
            while (r->ev[1].time >= 0.0f && r->ev[1].time < r->bestTime)
                r->ev++;
        }
        r->mode = r->ev->mode;
        r->m3160 = r->ev->sub;
    }
    D_241450 = r->bestTime;
    n = r->list;
    n = MAX(n, 0);
    if (n >= 10)
        n = 6;
    D_241454 = n;
    f_07f194(r);
}

/* @implements 0x07eca8 us f_07eca8
   WHAT IT DOES: Nothing. */
extern "C" void f_07eca8(Replay *r)
{
}
