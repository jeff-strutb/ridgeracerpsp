/* The race 2D before-race, replay and movie pieces object file (retail 0x10996c to 0x10aabc,
   with the pieces' destructors and type numbers in the gap row after it). Fj::C2DBeforeRace
   (type 20) is the overlay shown before the start: three labels slide in one after another
   while the race counts down, and the player picks a music track (left and right) and a
   setting (up and down) from the pad. Fj::C2DReplay (21) and Fj::C2DAvPlayer (22) are the
   overlays of the replay and of a movie. None of them keeps sprite handles of its own. */

/* The race the piece belongs to: its clock in frames at +136. */
struct Race {
    char m0[136];
    int clock;
};
int f_0f63a8(Race *r);
int f_0f6438(Race *r);
int f_0f64d8(Race *r);

/* The race in progress (null outside a race). */
struct RaceInfo {
    char m0[92];
    int m92;
};
extern RaceInfo *D_2407fc;

/* The race music player (D_242cb0). */
class CBgm {
public:
    int f_09666c(int n);
    int f_096728(int n);
};
extern CBgm D_242cb0;

/* The pad: its held buttons (D_245198) and the controller's repeating directions. */
namespace Controller {
class CCustomController {
public:
    int f_04320c();
    int f_04325c();
};
}
extern unsigned int D_245198;
extern Controller::CCustomController D_1d8910[1];

struct Group;

namespace Fj {

class C2DDecorationBase {
public:
    virtual ~C2DDecorationBase() {}
    virtual int f_101f44() { return 0; }
    virtual int f_101f4c() { return 0; }
    virtual int f_101f54(int i) { return 0; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw() = 0;
    virtual int f_101b54();
    virtual void f_101f5c() {}
    virtual int *f_101f64(int i) { return 0; }
    virtual const char *f_101f6c() { return 0; }
    virtual void f_101f74(float t) {}

    Race *race;
    Group *group;
    unsigned char on;
    int state;
    int start;
};

class C2DBeforeRace : public C2DDecorationBase {
public:
    virtual int f_101f44() { return 20; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f5c();

    int step;               /* 0 waiting, 1 to 5 the labels sliding in, 6 and 7 done */
    int time;               /* the race clock when the current step began */
    int course;
    int setting;
    int track;
    int mode;               /* 2 in a wireless battle, 1 in a time attack */
    float m48[6];
    float pos[3];           /* the three labels' slide positions */
    float m84[10];
    float speed[3];         /* their slide speeds */
    float m136[4];
    float fade[2];          /* the two fades before the labels */
    float m160[2];
};

class C2DReplay : public C2DDecorationBase {
public:
    virtual int f_101f44() { return 21; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f5c();
};

class C2DAvPlayer : public C2DDecorationBase {
public:
    virtual int f_101f44() { return 22; }
    virtual int f_101b1c(Group *group, Race *race);
    virtual int Draw();
    virtual int f_101b54();
    virtual void f_101f5c();
};

/* @implements 0x10996c us _ZN2Fj13C2DBeforeRace8f_101b1cEP5GroupP4Race
   WHAT IT DOES: Sets the piece up: the label layout, the course's music track and setting,
   and which race kind it shows. Returns 1. */
int C2DBeforeRace::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    m48[0] = m48[1] = m48[2] = m48[3] = 30.0f;
    m48[5] = 60.0f;
    m84[1] = m84[2] = m84[3] = 30.0f;
    m48[4] = 60.0f;
    m84[0] = 30.0f;
    pos[0] = pos[1] = pos[2] = -1.0f;
    m136[0] = m136[1] = m136[2] = m136[3] = m84[4] = m84[5] = m84[6] = m84[7] = m84[8] = m84[9] = 1.0f;
    speed[1] = speed[0] = 0.2f;
    speed[2] = 0.15f;
    fade[0] = fade[1] = 0;
    m160[1] = m160[0] = 1.0f;
    course = f_0f64d8(race);
    track = D_242cb0.f_09666c(course);
    setting = D_242cb0.f_096728(course);
    if (setting < 0)
        setting = 0;
    Race *r0 = race;
    mode = 0;
    if (f_0f6438(r0) == 1) {
        if (D_2407fc && D_2407fc->m92 >= 0)
            mode = 2;
    } else if (f_0f6438(race) == 4 || f_0f6438(race) == 5)
        mode = 1;
    step = 0;
    return 1;
}

/* @implements 0x109af0 us _ZN2Fj13C2DBeforeRace4DrawEv
   WHAT IT DOES: Nothing; returns 1. */
int C2DBeforeRace::Draw()
{
    return 1;
}

/* @draft 0x109af8 us _ZN2Fj13C2DBeforeRace8f_101b54Ev
   WHAT IT DOES: Steps the overlay: once the countdown starts (in a wireless battle or a time
   attack) the two fades run over 30 steps of 50 clock units each, then the three labels
   slide in at their speeds as the countdown reaches 2, 3 and 16; at 16 the overlay is done.
   Until then left and right pick the music track (1 to 7, wrapping) and up and down the
   setting (0 to 6, wrapping). Returns 0.
   DRAFT: one word short. Retail keeps the race pointer in a1 through each case and into the
   shared countdown test after the switch (its loads stolen into the cases' branch slots);
   here it is reloaded into v1/a0. Per-case locals made it worse. */
int C2DBeforeRace::f_101b54()
{
    switch (step) {
    case 0:
        if (f_0f63a8(race) == 1 && (mode == 1 || mode == 2)) {
            step = 1;
            time = race->clock;
        }
        break;
    case 1: {
        int c = race->clock;

        fade[0] = (float)((c - time) / 50) * (1.0f / 30);
        if (fade[0] > 1.0f) {
            fade[0] = 1.0f;
            time = c;
            step = 2;
        }
        break;
    }
    case 2: {
        int c = race->clock;

        fade[1] = (float)((c - time) / 50) * (1.0f / 30);
        if (fade[1] > 1.0f) {
            fade[1] = 1.0f;
            time = c;
            step = 3;
        }
        break;
    }
    case 3:
        pos[0] = (float)((race->clock - time) / 50) * speed[0];
        if (pos[0] > 60.0f)
            pos[0] = speed[0] + 60.0f;
        if (f_0f63a8(race) == 2) {
            step = 4;
            time = race->clock;
        }
        break;
    case 4:
        pos[1] = (float)((race->clock - time) / 50) * speed[1];
        if (pos[1] > 60.0f)
            pos[1] = speed[1] + 60.0f;
        if (f_0f63a8(race) == 3) {
            step = 5;
            time = race->clock;
        }
        break;
    case 5:
        pos[2] = (float)((race->clock - time) / 50) * speed[2];
        if (pos[2] > 60.0f)
            pos[2] = speed[2] + 60.0f;
        if (f_0f63a8(race) == 16) {
            step = 7;
            time = race->clock;
        }
        break;
    case 6:
        step = 7;
        break;
    case 7:
        break;
    }
    if (f_0f63a8(race) == 16)
        step = 6;
    if (step < 6) {
        unsigned int b = D_245198;
        int ud = D_1d8910[0].f_04325c();
        int lr = D_1d8910[0].f_04320c();

        if (((b >> 7) & 1) | (lr < 0)) {
            if (--track <= 0)
                track = 7;
            setting = 0;
        } else if (((b >> 5) & 1) | (lr > 0)) {
            if (++track >= 8)
                track = 1;
            setting = 0;
        }
        if (setting >= 0) {
            if (((b >> 4) & 1) | (ud > 0)) {
                if (--setting < 0)
                    setting = 6;
            } else if (((b >> 6) & 1) | (ud < 0)) {
                if (++setting >= 7)
                    setting = 0;
            }
        }
    }
    return 0;
}

/* @implements 0x10a4d4 us _ZN2Fj9C2DReplay8f_101b1cEP5GroupP4Race
   WHAT IT DOES: Binds the piece to its group and race; returns 1. */
int C2DReplay::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    return 1;
}

/* @implements 0x10a4f4 us _ZN2Fj9C2DReplay4DrawEv
   WHAT IT DOES: Nothing; returns 1. */
int C2DReplay::Draw()
{
    return 1;
}

/* @implements 0x10a4fc us _ZN2Fj9C2DReplay8f_101b54Ev
   WHAT IT DOES: Nothing; returns 0. */
int C2DReplay::f_101b54()
{
    return 0;
}

/* @implements 0x10a74c us _ZN2Fj11C2DAvPlayer8f_101b1cEP5GroupP4Race
   WHAT IT DOES: Binds the piece to its group and race; returns 1. */
int C2DAvPlayer::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    return 1;
}

/* @implements 0x10a76c us _ZN2Fj11C2DAvPlayer4DrawEv
   WHAT IT DOES: Nothing; returns 1. */
int C2DAvPlayer::Draw()
{
    return 1;
}

/* @implements 0x10a774 us _ZN2Fj11C2DAvPlayer8f_101b54Ev
   WHAT IT DOES: Nothing; returns 0. */
int C2DAvPlayer::f_101b54()
{
    return 0;
}
}

/* @implements 0x10aabc us _ZN2Fj13C2DBeforeRaceD1Ev
   WHAT IT DOES: The destructor. */
/* @implements 0x10aacc us _ZN2Fj13C2DBeforeRaceD0Ev
   WHAT IT DOES: The deleting destructor. */
/* @implements 0x10aaf4 us _ZN2Fj13C2DBeforeRace8f_101f44Ev
   WHAT IT DOES: The piece type, 20. */
/* @implements 0x10aafc us _ZN2Fj9C2DReplayD1Ev
   WHAT IT DOES: The destructor. */
/* @implements 0x10ab0c us _ZN2Fj9C2DReplayD0Ev
   WHAT IT DOES: The deleting destructor. */
/* @implements 0x10ab34 us _ZN2Fj9C2DReplay8f_101f44Ev
   WHAT IT DOES: The piece type, 21. */
/* @implements 0x10ab3c us _ZN2Fj11C2DAvPlayerD1Ev
   WHAT IT DOES: The destructor. */
/* @implements 0x10ab4c us _ZN2Fj11C2DAvPlayerD0Ev
   WHAT IT DOES: The deleting destructor. */
/* @implements 0x10ab74 us _ZN2Fj11C2DAvPlayer8f_101f44Ev
   WHAT IT DOES: The piece type, 22. */
