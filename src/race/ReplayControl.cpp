/* The replay controller object file (retail 0x07df70 to 0x07f564). During a replay it reads
   the recorded race's length from the "Replay" package entry, advances the replay clock,
   handles the pad (skip, camera change), switches between the replay cameras and drives the
   replay's mode handlers, which the race sequence calls through a table of member pointers. */

void *f_005c34(char *seq, const char *name);
extern char D_1dd6b0[];

namespace Controller {
struct CCustomController {
    int f_043030();
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

/* The replay's recorded header: lengths, the recorded length at +16 (frames) and offsets
   of the opening's event list, the camera spots and zones, and seven pairs of camera event
   and camera track lists. */
struct ReplayInfo {
    int m0;
    int opening;
    int m8;
    int m12;
    int length;
    int spots;
    int zones;
    struct {
        int ev;
        int track;
    } pair[7];
    ReplayEvent *List(int k) { return (ReplayEvent *)(pair[k].ev + (int)this); }
};

/* The course collision areas of the map manager. */
struct CourseAreas {
    int f_0e23d0(float x, float z);
    float f_0e26dc(float d);
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
    virtual void v2(struct CamArg *p);
    virtual void Reset();
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
    float x;
    float y;
    float z;
    char m12[560];
    int m572;
    char m576[32];
    float rx;
    float ry;
    float rz;
    char m620[40];
    int m660;
    int m664;
    char m668[20];
    int m688;
    int m692;
    int m696;
    char m700[4];
    int m704;
    float m708;
    char m712[12];
    int m724;
    char m728[12];
    int m740;
};

/* The replay's view of the player's car display at +3356. */
struct ReplayCarView {
    char m0[704];
    float m704;
    char m708[36];
    float m744;
};

struct Matrix;
void f_028c70(void);
void f_02842c(void);
void f_0284bc(float a);
void f_0284fc(float a);
void f_02853c(float a);
void f_02880c(float x, float y, float z);
void f_0287b0(void);
void f_028d94(Matrix *m);
void f_028ca8(void);
void f_0ccaec(float *a);
void f_0cc1f4(ReplayView *v, Matrix *m);
void f_082e00(void *p);

struct MainLoopJobView {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern MainLoopJobView *D_1d88a0;

extern "C" void f_00d354(void *log, int level, const char *fmt, ...);
extern char D_245178[];

/* Sets up the camera transform from a view's rotation (each angle normalised first) and
   position and hands the resulting matrix to the view. */
static inline void SetCamera(ReplayView *v)
{
    char m[64];
    float a, b, c;

    f_028c70();
    f_02842c();
    a = v->ry;
    f_0ccaec(&a);
    f_0284fc(a);
    b = v->rx;
    f_0ccaec(&b);
    f_0284bc(b);
    c = v->rz;
    f_0ccaec(&c);
    f_02853c(c);
    f_02880c(v->x, v->y, v->z);
    f_0287b0();
    f_028d94((Matrix *)m);
    f_028ca8();
    f_0cc1f4(v, (Matrix *)m);
}

void f_082df8(void *p);

/* A fixed camera spot (60 bytes): its position and its distance along the course, computed
   on first use (negative until then). */
struct ReplaySpot {
    float x;
    float y;
    float z;
    char m12[44];
    float dist;
};

/* A camera zone (152 bytes): two positions and their distances along the course. */
struct ReplayZone {
    float x0;
    float y0;
    float z0;
    float x1;
    float y1;
    float z1;
    char m24[112];
    float d0;
    float d1;
    char m144[8];
};

/* A camera track of the recording: how its start and end are placed on the course and
   their distances along it. */
struct ReplayTrack {
    char m0[8];
    int startKind;
    float x0;
    float y0;
    float z0;
    char m24[100];
    int endKind;
    char m128[12];
    int endKind2;
    float x1;
    float y1;
    float z1;
    char m156[132];
    float d0;
    float d1;
};

/* An entry of a track list: a negative time ends it. */
struct ReplayTrackRef {
    float time;
    int off;
};

struct Replay;
/* The replay's mode handlers: one row per replay kind, one column per state. */
struct ReplayModes {
    ReplayOverlay *overlay;
    ReplayPart *m4;
    void (Replay::*handler[2][3])();
};

struct Replay {
    void f_07ee80();
    void f_07eec8();
    void f_07f240();
    void f_07f3b4();

    char m0[3060];
    ReplayPart *cam[11];
    ReplayView *m3104;
    void *m3108;
    ReplayCar *car;
    int m3116;
    int m3120;
    int m3124;
    ReplayInfo *info;
    char m3132[4];
    void *m3136;
    int mode;
    int curMode;
    int m3148;
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
    int m3200;
    int m3204;
    int m3208;
    int m3212;
    int m3216;
    int m3220;
    int m3224;
    int m3228;
    int m3232;
    int m3236;
    int m3240;
    int m3244;
    ReplayModes modes;
    char m3304[48];
    ReplayView *m3352;
    ReplayCarView *m3356;
    int m3360;
};

extern "C" void f_07ee5c(Replay *r);
extern "C" void f_07e3a8(Replay *r, ReplayEvent *ev, struct ReplaySpot *spot, struct ReplayZone *zone);
extern "C" void f_07e568(Replay *r, struct ReplayTrackRef *list);
void f_082dc0(void *p, ReplayCar *car);
void *f_154448(void *p, const void *from, const void *to);
extern char D_1a7248[];
extern char D_1a73a0[];
extern int D_24175c;
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

/* @draft 0x07dff0 us f_07dff0
   REMAINING DIFFERENCE: saved register assignment (retail keeps &m3304 in s2, the fifth and
   sixth arguments in s1 and s0) and the schedule of the member pointer constant copies and
   the following field stores; the control flow and the calls match.
   WHAT IT DOES: Sets the replay controller up for a race: the mode handlers, the view, car
   and display objects and settings, the starting view from the debug flags, the recorded
   replay (found in the race package unless given), the cameras' parameters, the opening's
   length, the overlays (the TV camera when there is one), and places every camera spot,
   zone and track of the recording on the course. */
extern "C" void f_07dff0(Replay *r, ReplayView *view, void *p2, ReplayCar *car, int a4, int a5,
                         int a6, int a7, int a8, int a9, ReplayInfo *info)
{
    ReplaySpot *spots;
    ReplayZone *zones;
    float z[4];
    int i;

    f_00d354(D_245178, 0x40000, "Initalize CCamCtrl %x\n", r);
    f_082dc0(r->m3304, car);
    r->modes.handler[0][0] = &Replay::f_07ee80;
    r->modes.handler[0][1] = &Replay::f_07eec8;
    r->modes.handler[1][0] = &Replay::f_07f240;
    r->modes.handler[1][1] = &Replay::f_07f3b4;
    r->m3120 = a5;
    r->m3148 = a6;
    r->curMode = 6;
    r->m3116 = a4;
    r->m3188 = a8;
    r->m3124 = a6;
    r->m3204 = a9;
    r->m3160 = 0;
    r->m3156 = 0;
    r->clock = 0;
    r->m3212 = 0;
    r->m3136 = r->m3304;
    r->curCam = r->cam[6];
    r->m3104 = view;
    r->m3108 = p2;
    r->car = car;
    if (D_24175c & 1) {
        r->m3164 = 0;
        r->mode = 0;
    } else {
        int m = (D_24175c & 2) ? 1 : 4;
        r->mode = m;
        r->m3164 = m;
    }
    r->m3356 = (ReplayCarView *)p2;
    r->m3216 = 0;
    r->m3220 = 0;
    r->m3224 = 0;
    r->m3228 = 0;
    r->m3232 = 0;
    r->m3236 = 0;
    r->m3240 = 0;
    r->m3244 = 0;
    r->m3352 = view;
    r->m3360 = 0;
    if (info == 0)
        r->info = (ReplayInfo *)f_005c34(D_1dd6b0, "Replay");
    else
        r->info = info;
    view->m572 = 0;
    view->m740 = 0;
    r->m3168 = 0;
    r->list = 0;
    D_241454 = 0;
    view->m660 = r->curMode;
    r->m3208 = 0;
    r->bestLap = car->lap - 1;
    view->m708 = 0.785375f;
    view->m724 = 0;
    z[3] = 1.0f;
    view->m704 = 0;
    view->m688 = 0;
    view->m692 = 0;
    view->m696 = 0;
    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    r->bestTime = 0;
    for (i = 0; i < 9; i++) {
        if (r->cam[i])
            r->cam[i]->v2((CamArg *)&r->m3104);
    }
    r->m3196 = 0;
    if (r->m3148) {
        D_241450 = 0;
        r->m3200 = r->info->m8;
        D_241454 = 8;
    } else {
        D_241450 = 0;
        r->m3200 = r->info->m0;
        D_241454 = 7;
    }
    if (r->cam[4])
        r->modes.overlay = (ReplayOverlay *)f_154448(r->cam[4], D_1a7248, D_1a73a0);
    else
        r->modes.overlay = 0;
    r->modes.m4 = r->cam[1];
    spots = (ReplaySpot *)(r->info->spots + (int)r->info);
    zones = (ReplayZone *)(r->info->zones + (int)r->info);
    f_07e3a8(r, (ReplayEvent *)(r->info->opening + (int)r->info), spots, zones);
    f_07e3a8(r, (ReplayEvent *)(r->info->m12 + (int)r->info), spots, zones);
    for (i = 0; i < 7; i++)
        f_07e3a8(r, (ReplayEvent *)(r->info->pair[i].ev + (int)r->info), spots, zones);
    for (i = 0; i < 7; i++)
        f_07e568(r, (ReplayTrackRef *)(r->info->pair[i].track + (int)r->info));
}

/* @implements 0x07e6d0 us f_07e6d0
   WHAT IT DOES: Resets the replay: clears the object at +3304 and resets every one of the nine
   cameras that exists. */
extern "C" void f_07e6d0(Replay *r)
{
    int i;

    f_082df8(r->m3304);
    for (i = 0; i < 9; i++) {
        if (r->cam[i])
            r->cam[i]->Reset();
    }
}

/* @draft 0x07e73c us f_07e73c
   REMAINING DIFFERENCE: not yet close. Retail returns through v1, strength reduces the event
   search to a pointer that starts at ev + 12, and inlines the camera switch and transform
   setup; the block layout and registers still differ.
   WHAT IT DOES: One frame of the opening scenery (the attract camera run before the race).
   Unless paused: follows the opening's camera event list up to the clock, switches the
   camera when the view or parameter changed and steps it, advances the clock by 5 and sets
   up the camera transform. From frame 3 on, once the clock passes the opening's length or a
   button is pressed, logs the end and leaves the opening (to view 4 when the race has a
   second replay kind, else view 0). Returns 0 while running, 1 at the end of the opening
   and 2 when it was skipped. */
extern "C" int f_07e73c(Replay *r)
{
    ReplayEvent *ev;
    int ret = 0;
    int i;
    int arg;

    if (D_1d88a0->m11)
        return ret;
    if (D_1d88a0->m12)
        return ret;
    if (r->m3196 == 0)
        r->modes.overlay->m740 = 1;
    ev = (ReplayEvent *)(r->info->opening + (int)r->info);
    r->ev = ev;
    for (i = 0; ev[i + 1].time >= 0.0f && ev[i + 1].time < (float)r->m3196; i++)
        ;
    D_1d3d40->m24 = i + 1;
    r->ev = &r->ev[i];
    r->mode = r->ev->mode;
    r->m3160 = r->ev->sub;
    if (r->mode == r->curMode && r->m3160 == r->m3156) {
        r->m3168 = 0;
    } else {
        r->m3168 = 1;
        if (r->curCam)
            r->curCam->Stop();
        r->curMode = r->mode;
        r->m3156 = r->m3160;
        r->curCam = r->cam[r->mode & 0xffff];
        arg = 0;
        if (r->mode >> 16)
            arg = (r->mode >> 16) - 1;
        else
            arg = r->ev->sub;
        if (r->curCam)
            r->curCam->Start(&arg);
    }
    r->curCam->Step();
    r->m3196 += 5;
    SetCamera(r->m3352);
    r->m3208 = 1;
    if (r->m3168)
        r->m3352->m664 = 1;
    if (r->m3196 < 3)
        return ret;
    if (r->m3200 >= r->m3196 && !D_1d8910[0].f_043030())
        return ret;
    f_00d354(D_245178, 8, "end opening secenery %d/%d\n", r->m3196, r->m3200);
    r->curMode = 6;
    if (r->m3148)
        r->mode = 4;
    else
        r->mode = 0;
    ret = 1;
    if (r->m3200 >= r->m3196 && D_1d8910[0].f_043030())
        ret = 2;
    return ret;
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
        r->modes.overlay->m740 = 1;
        r->list = 0;
        D_241450 = r->clock;
        D_241454 = 0;
        r->mode = 4;
        r->modes.overlay->Show();
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
        r->modes.overlay->m740 = 0;
    }
    r->modes.m4->Show();
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
void Replay::f_07eec8()
{
    Replay *r = this;

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
            r->modes.overlay->m752 = 0;
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
    r->modes.overlay->Show();
    r->modes.m4->Show();
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
void Replay::f_07f240()
{
    Replay *r = this;
    int n;

    f_07ee5c(r);
    f_07ef10(r);
    if (r->list == 0) {
        r->mode = 4;
        r->modes.overlay->m740 = 1;
        r->ev = 0;
        D_1d3d40->m24 = 16;
    } else {
        r->ev = r->info->List(r->list);
        r->modes.overlay->m740 = 0;
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
void Replay::f_07f3b4()
{
    Replay *r = this;
    ReplayInfo *info;
    ReplayEvent *ev;
    int n;

    f_07ee5c(r);
    f_07ef10(r);
    info = r->info;
    ev = info->List(r->list);
    r->modes.overlay->m740 = 0;
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

/* @implements 0x07e3a8 us f_07e3a8
   WHAT IT DOES: Places the camera spots and zones that an event list uses on the course: for
   each event in view 2 the spot's distance along the course, for each event in view 5 the
   zone's start and end distances, computed from their positions the first time and
   normalised to the lap afterwards. */
extern "C" void f_07e3a8(Replay *r, ReplayEvent *ev, ReplaySpot *spot, ReplayZone *zone)
{
    CourseAreas *ar = D_23c820.Areas();
    int i;

    for (i = 0; ev[i].time >= 0.0f; i++) {
        if (ev[i].mode == 2) {
            ReplaySpot *p = (ReplaySpot *)(ev[i].sub * (int)sizeof(ReplaySpot) + (int)spot);
            float d;
            if (p->dist < 0.0f) {
                d = ar->f_0e23d0(p->x, p->z);
                spot[ev[i].sub].dist = d;
            } else {
                d = ar->f_0e26dc(p->dist);
                p->dist = d;
            }
        } else if (ev[i].mode == 5) {
            ReplayZone *p = (ReplayZone *)(ev[i].sub * (int)sizeof(ReplayZone) + (int)zone);
            if (p->d0 < 0.0f) {
                float d = ar->f_0e23d0(p->x0, p->z0);
                zone[ev[i].sub].d0 = d;
                d = ar->f_0e23d0(zone[ev[i].sub].x1, zone[ev[i].sub].z1);
                zone[ev[i].sub].d1 = d;
            } else if (p->d1 < 0.0f) {
                p->d0 = ar->f_0e26dc(p->d0);
                zone[ev[i].sub].d1 = zone[ev[i].sub].d0;
            }
        }
    }
}

/* @implements 0x07e568 us f_07e568
   WHAT IT DOES: Places the recording's camera tracks on the course: a track's start distance
   comes from its start position (kind 0) or its z (kind 1), and its end distance copies the
   start (no end) or comes from the end position (kind 0) or its z (kind 1). */
extern "C" void f_07e568(Replay *r, ReplayTrackRef *list)
{
    CourseAreas *ar = D_23c820.Areas();
    int i;

    for (i = 0; list[i].time >= 0.0f; i++) {
        ReplayTrack *t = (ReplayTrack *)(list[i].off + (int)r->info);
        if (t->d0 < 0.0f) {
            float d;
            if (t->startKind == 0) {
                d = ar->f_0e23d0(t->x0, t->z0);
                t->d0 = d;
            } else if (t->startKind == 1) {
                d = t->z0;
                t->d0 = d;
            }
            if (t->d1 < 0.0f) {
                if (t->endKind != 0) {
                    if (t->endKind2 == 0) {
                        d = ar->f_0e23d0(t->x1, t->z1);
                        t->d1 = d;
                    } else if (t->endKind2 == 1) {
                        d = t->z1;
                        t->d1 = d;
                    }
                } else {
                    t->d1 = t->d0;
                }
            }
        } else if (t->d1 < 0.0f) {
            t->d1 = t->d0;
        }
    }
}

/* @draft 0x07ea64 us f_07ea64
   WHAT IT DOES: The replay's frame: unless the game is paused, steps the object at +3304,
   runs the handler for the current replay kind and state, and copies the car display's
   value at +704 to +744. Then sets up the camera transform from the view's rotation (each
   angle normalised first) and position, and hands the resulting matrix to the view.
   REMAINING DIFFERENCE: 4 words in the handler call. Retail forms the entry address as
   (index * 8 + this) + 3248 at the call and reloads the delta this-relative; this build
   keeps this + 3248 in a3 from before the index arithmetic. A direct member access folds
   the 3248 away, an inline method on the sub-object differs more. */
extern "C" void f_07ea64(Replay *r)
{
    if (!D_1d88a0->m11 && !D_1d88a0->m12) {
        f_082e00(r->m3304);
        ReplayModes *md = &r->modes;
        (r->*md->handler[r->m3148][r->m3188])();
        if (r->m3356)
            r->m3356->m744 = r->m3356->m704;
    }
    SetCamera(r->m3104);
}
