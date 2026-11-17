/* The race 2D before-race, replay and movie pieces object file (retail 0x10996c to 0x10aabc,
   with the pieces' destructors and type numbers in the gap row after it). Fj::C2DBeforeRace
   (type 20) is the overlay shown before the start: three labels slide in one after another
   while the race counts down, and the player picks a music track (left and right) and a
   setting (up and down) from the pad. Fj::C2DReplay (21) and Fj::C2DAvPlayer (22) are the
   overlays of the replay and of a movie. None of them keeps sprite handles of its own. */

/* The race's overlay list the piece belongs to (src/race/Race2DParts.cpp): its clock in
   frames at +136. */
namespace Fj {
class C2DList {
public:
    int f_0f63a8();
    int f_0f63d8();
    int f_0f63f0();
    int f_0f6408();
    int f_0f6420();
    int f_0f6438();
    void f_0f64c0(int v);
    int f_0f64d8();

    char m0[136];
    int clock;
};
}
typedef Fj::C2DList Race;

/* The race in progress (null outside a race). */
struct RaceInfo {
    char m0[24];
    int m24;                /* the two times the overlay shows (thirds of a millisecond) */
    int m28;
    char m32[56];
    int m88;
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

extern "C" int sprintf(char *buf, const char *fmt, ...);

/* The race screen (reached through f_017970) and its music text lists (slot 80). */
struct MusicText;
class CScreen {
public:
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void v12();
    virtual void v16();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v32();
    virtual void v36();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v52();
    virtual void v56();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v72();
    virtual void v76();
    virtual MusicText *v80();
};
CScreen *f_017970();
void f_06ca64(void *self, int slot, int text);
void f_06caa8(void *self, int slot, const char *s, int a3);
void *f_06cdf4(void *self, int x, int y, float r, float g, float b, float a, int text, int pri,
               float px, float py);
void f_04d3d8(Group *g, float x0, float y0, float r0, float g0, float b0, float a0,
                           float x1, float y1, float r1, float g1, float b1, float a1,
                           float x2, float y2, float r2, float g2, float b2, float a2,
                           float x3, float y3, float r3, float g3, float b3, float a3);
int f_077b0c(MusicText *t, int disc, int track);
int f_077dd4(MusicText *t, int n);
int f_077e74(MusicText *t, int n, int which);

/* The overlay's bars (x, y, width, height) and their corner colours. */
struct Bar {
    float x, y, w, h;
};
extern const Bar D_1b185c[];
extern const float D_1b19a0[][4][4];

/* The overlay's 13 texts: position, text id and a base for the computed ids. */
struct Item {
    int x, y, text, base, m16;
};
extern const Item D_1b189c[];
extern const int D_1b1aa0[];        /* text ids by number */
extern const int D_1b17f8[];        /* text ids by course */

int f_01c260();                     /* the system language */
int f_06cb40(void *self, int x, int y, int text, float r, float g, float b, float a, int pri);

/* The replay overlay's bars and its four texts' positions (the last three move with the
   language). */
extern const Bar D_1b1b3c[];
extern const float D_1b1b6c[][4][4];
extern const int D_1b1c2c[];
struct Pos {
    int x, y;
};
Pos D_1d7788[4] = { { 12, 254 }, { 415, 254 }, { 425, 254 }, { 439, 254 } };

/* The movie overlay: its five bars, its 16 texts in five languages (English, then languages
   2 to 5) and the movie player's state (two flags, the disc, track and title). */
CScreen *f_017bd4();
extern const Bar D_1b1d7c[];
extern const float D_1b1c3c[][4][4];
extern const Item D_1b1dcc[];
extern const Item D_1b1f0c[];
extern const Item D_1b204c[];
extern const Item D_1b218c[];
extern const Item D_1b22cc[];
struct AvState {
    unsigned char m0;
    unsigned char m1;
    int m4;
    int m8;
    int m12;
};
extern AvState D_245074;

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
    void f_101cf4(int t, int *min, int *sec, int *ms);
    C2DList *List() { return race; }
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
    int course;             /* the music text's track number (set while drawing) */
    int setting;
    int track;
    int mode;               /* 2 in a wireless battle, 1 in a time attack */
    float pos[13];          /* the 13 texts' positions (negative: hidden); 6 to 8 the
                               three labels sliding in */
    float m100[13];         /* their second coordinates; 6 to 8 the labels' slide speeds */
    float fade[4];          /* the bars' widths, the first two fading in */
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

/* @implements 0x10996c us _ZN2Fj13C2DBeforeRace8f_101b1cEP5GroupPNS_7C2DListE
   WHAT IT DOES: Sets the piece up: the label layout, the course's music track and setting,
   and which race kind it shows. Returns 1. */
int C2DBeforeRace::f_101b1c(Group *g, Race *r)
{
    C2DDecorationBase::f_101b1c(g, r);
    pos[0] = pos[1] = pos[2] = pos[3] = 30.0f;
    pos[5] = 60.0f;
    pos[10] = pos[11] = pos[12] = 30.0f;
    pos[4] = 60.0f;
    pos[9] = 30.0f;
    pos[6] = pos[7] = pos[8] = -1.0f;
    m100[9] = m100[10] = m100[11] = m100[12] = m100[0] = m100[1] = m100[2] = m100[3] = m100[4] = m100[5] = 1.0f;
    m100[7] = m100[6] = 0.2f;
    m100[8] = 0.15f;
    fade[0] = fade[1] = 0;
    fade[3] = fade[2] = 1.0f;
    course = List()->f_0f64d8();
    track = D_242cb0.f_09666c(course);
    setting = D_242cb0.f_096728(course);
    if (setting < 0)
        setting = 0;
    mode = 0;
    if (List()->f_0f6438() == 1) {
        if (D_2407fc && D_2407fc->m92 >= 0)
            mode = 2;
    } else if (List()->f_0f6438() == 4 || List()->f_0f6438() == 5)
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
   DRAFT: same size; the race pointer now lives in a1 as in retail (the calls go through the
   inline List() getter, so each call argument is a pseudo that GCSE merges). Left: the
   right-press test, where retail computes the button bit first (srl/andi, bit in v1) and
   or-s the comparison in v0 first; here sched1 puts the slt between srl and andi (lr dies
   at the slt, so the luid tie-break picks it) and local-alloc swaps v0/v1. */
int C2DBeforeRace::f_101b54()
{
    switch (step) {
    case 0:
        if (List()->f_0f63a8() == 1 && (mode == 1 || mode == 2)) {
            time = race->clock;
            step = 1;
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
        pos[6] = (float)((race->clock - time) / 50) * m100[6];
        if (pos[6] > 60.0f)
            pos[6] = m100[6] + 60.0f;
        if (List()->f_0f63a8() == 2) {
            time = race->clock;
            step = 4;
        }
        break;
    case 4:
        pos[7] = (float)((race->clock - time) / 50) * m100[7];
        if (pos[7] > 60.0f)
            pos[7] = m100[7] + 60.0f;
        if (List()->f_0f63a8() == 3) {
            time = race->clock;
            step = 5;
        }
        break;
    case 5:
        pos[8] = (float)((race->clock - time) / 50) * m100[8];
        if (pos[8] > 60.0f)
            pos[8] = m100[8] + 60.0f;
        if (List()->f_0f63a8() == 16) {
            time = race->clock;
            step = 7;
        }
        break;
    case 6:
        step = 7;
        break;
    case 7:
        break;
    }
    if (List()->f_0f63a8() == 16)
        step = 6;
    if (step < 6) {
        unsigned int b = D_245198;
        int ud = D_1d8910[0].f_04325c();
        int lr = D_1d8910[0].f_04320c();

        if (((b >> 7) & 1) | (lr < 0)) {
            if (--track <= 0)
                track = 7;
            setting = 0;
        } else if ((lr > 0) | ((b >> 5) & 1)) {
            if (++track >= 8)
                track = 1;
            setting = 0;
        }
        if (setting >= 0) {
            if ((ud > 0) | ((b >> 4) & 1)) {
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

/* @draft 0x109f04 us _ZN2Fj13C2DBeforeRace8f_101f5cEv
   WHAT IT DOES: Draws the overlay while it runs (in a race, before step 6): the three bars
   (four in a wireless battle) at their fade widths, then each visible text of the nine (13 in
   a wireless battle) at its position, filling in the computed ones first: the music track's
   name, its title and artist, the course and rank, the setting and the two times.
   DRAFT: frame +16 and the bar loop differ: retail loads the bottom-right colour's second
   and third words into f14/f15 and stores them before loading the top-left colour into
   f14..f17 (sched1 puts the register-argument loads after the stack stores); here sched1
   loads f14..f17 first, so those values take f20..f22 (saved). The draw call's clock takes
   t0 here, a0 in retail (local-alloc tie). Case 12 cross-jumps into case 10 only from the
   first f_06caa8 call: when case 12 falls through into the draw, sched1 orders its a1/a2
   setup differently from case 10; with case 12 ending in a jump (shown by moving a case
   after it) it matches retail's cross-jump at the "%03d" sprintf. */
void C2DBeforeRace::f_101f5c()
{
    char buf[3][8];

    if (!D_2407fc)
        return;
    CScreen *s = f_017970();
    if (step >= 6)
        return;
    int n = 9;
    int bars = 3;
    if (List()->f_0f6438() == 2) {
        n = 13;
        bars = 4;
    }
    for (int i = 0; i < bars; i++) {
        const float *w = fade;
        const Bar *r = &D_1b185c[i];
        const float (*c)[4] = D_1b19a0[i];
        f_04d3d8(group, r->x, r->y, c[0][0], c[0][1], c[0][2], c[0][3],
                 r->x + r->w * w[i], r->y, c[1][0], c[1][1], c[1][2], c[1][3],
                 r->x, r->y + r->h, c[2][0], c[2][1], c[2][2], c[2][3],
                 r->x + r->w * w[i], r->y + r->h, c[3][0], c[3][1], c[3][2], c[3][3]);
    }
    const Item *it = D_1b189c;
    for (int i = 0; i < n; i++, it++) {
        if (pos[i] < 0)
            continue;
        int x = it->x;
        int y = it->y;
        int text = it->text;
        int id;
        switch (i) {
        case 4:
            f_06ca64(s, 0, f_077dd4(s->v80(), track));
            break;
        case 5:
            course = f_077b0c(s->v80(), track, setting + 1);
            if (track >= 6) {
                f_06caa8(s, 0, " ", 0);
                f_06caa8(s, 1, " ", 0);
            } else {
                f_06caa8(s, 0, " ", 0);
                f_06caa8(s, 1, " ", 0);
                id = it->base + setting;
                f_06ca64(s, 0, id);
                f_06ca64(s, 1, f_077e74(s->v80(), course, 0));
            }
            List()->f_0f64c0(course);
            break;
        case 6:
            if (mode == 2) {
                text = D_2407fc->m88 + 0xb722ec;
                id = D_1b1aa0[D_2407fc->m92];
                f_06ca64(s, 0, id);
            } else {
                id = it->base + List()->f_0f63f0() - 1;
                if (List()->f_0f63f0() >= 40)
                    id = List()->f_0f63f0() + 0xe4f162;
                f_06ca64(s, 0, id);
                id = D_1b1aa0[List()->f_0f6408()];
                f_06ca64(s, 1, id);
            }
            break;
        case 7:
            f_06ca64(s, 0, D_1b17f8[List()->f_0f63d8()]);
            break;
        case 8:
            id = it->base - List()->f_0f6420() + 1;
            if (mode == 2)
                id = 0xb722de;
            f_06ca64(s, 0, id);
            break;
        case 10: {
            int mn, sc, ms;
            f_101cf4(D_2407fc->m24, &mn, &sc, &ms);
            sprintf(buf[0], "%d", mn);
            sprintf(buf[1], "%02d", sc);
            sprintf(buf[2], "%03d", ms);
            f_06caa8(s, 0, buf[0], 0);
            f_06caa8(s, 1, buf[1], 0);
            f_06caa8(s, 2, buf[2], 0);
            break;
        }
        case 12: {
            int mn, sc, ms;
            f_101cf4(D_2407fc->m28, &mn, &sc, &ms);
            sprintf(buf[0], "%d", mn);
            sprintf(buf[1], "%02d", sc);
            sprintf(buf[2], "%03d", ms);
            f_06caa8(s, 0, buf[0], 0);
            f_06caa8(s, 1, buf[1], 0);
            f_06caa8(s, 2, buf[2], 0);
            break;
        }
        }
        f_06cdf4(s, x, y, 1.0f, 1.0f, 1.0f, 1.0f, text, race->clock % 10 + 480, pos[i], m100[i]);
    }
}

/* @implements 0x10a4d4 us _ZN2Fj9C2DReplay8f_101b1cEP5GroupPNS_7C2DListE
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

/* @draft 0x10a504 us _ZN2Fj9C2DReplay8f_101f5cEv
   WHAT IT DOES: Draws the replay overlay: moves its last three texts for the language, then
   draws its three bars and its four texts.
   DRAFT: one instruction's position: retail loads the group (lw a0,8(s4)) right after the
   first add.s of the bar loop; here sched2 ranks it below every colour load and issues it
   last. Same residue in 0x10a77c. */
void C2DReplay::f_101f5c()
{
    if (f_01c260() == 2) {
        D_1d7788[1].x = 393;
        D_1d7788[2].x = 403;
        D_1d7788[3].x = 417;
    }
    if (f_01c260() == 3) {
        D_1d7788[1].x = 410;
        D_1d7788[2].x = 420;
        D_1d7788[3].x = 434;
    }
    if (f_01c260() == 4) {
        D_1d7788[1].x = 391;
        D_1d7788[2].x = 401;
        D_1d7788[3].x = 415;
    }
    if (f_01c260() == 5) {
        D_1d7788[1].x = 415;
        D_1d7788[2].x = 425;
        D_1d7788[3].x = 439;
    }
    CScreen *s = f_017970();
    for (int i = 0; i < 3; i++) {
        const Bar *r = &D_1b1b3c[i];
        const float (*c)[4] = D_1b1b6c[i];
        f_04d3d8(group, r->x, r->y, c[0][0], c[0][1], c[0][2], c[0][3],
                 r->x + r->w, r->y, c[1][0], c[1][1], c[1][2], c[1][3],
                 r->x, r->y + r->h, c[2][0], c[2][1], c[2][2], c[2][3],
                 r->x + r->w, r->y + r->h, c[3][0], c[3][1], c[3][2], c[3][3]);
    }
    for (int i = 0; i < 4; i++)
        f_06cb40(s, D_1d7788[i].x, D_1d7788[i].y, D_1b1c2c[i], 1.0f, 1.0f, 1.0f, 1.0f, 480);
}

/* @implements 0x10a74c us _ZN2Fj11C2DAvPlayer8f_101b1cEP5GroupPNS_7C2DListE
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

/* @draft 0x10a77c us _ZN2Fj11C2DAvPlayer8f_101f5cEv
   WHAT IT DOES: Draws the movie overlay: its five bars, then its 16 texts in the system
   language, filling in the movie's title, disc and track first and stepping the two flag
   texts back when their flags are set.
   DRAFT: only the bar loop's group load position differs (as in 0x10a504). */
void Fj::C2DAvPlayer::f_101f5c()
{
    const Item *it = D_1b1dcc;
    if (f_01c260() == 2)
        it = D_1b1f0c;
    if (f_01c260() == 3)
        it = D_1b204c;
    if (f_01c260() == 4)
        it = D_1b218c;
    if (f_01c260() == 5)
        it = D_1b22cc;
    CScreen *s = f_017bd4();
    for (int i = 0; i < 5; i++) {
        const Bar *r = &D_1b1d7c[i];
        const float (*c)[4] = D_1b1c3c[i];
        f_04d3d8(group, r->x, r->y, c[0][0], c[0][1], c[0][2], c[0][3],
                 r->x + r->w, r->y, c[1][0], c[1][1], c[1][2], c[1][3],
                 r->x, r->y + r->h, c[2][0], c[2][1], c[2][2], c[2][3],
                 r->x + r->w, r->y + r->h, c[3][0], c[3][1], c[3][2], c[3][3]);
    }
    int disc = D_245074.m4;
    int track = D_245074.m8;
    int title = D_245074.m12;
    for (int i = 0; i < 16; i++, it++) {
        int x = it->x;
        int y = it->y;
        int text = it->text;
        int id;
        switch (i) {
        case 9:
            id = f_077e74(s->v80(), title, 1);
            f_06ca64(s, 0, id);
            break;
        case 10:
            id = f_077dd4(s->v80(), disc);
            f_06ca64(s, 0, id);
            break;
        case 11:
            if (track >= 0) {
                id = it->base + track;
                f_06ca64(s, 0, id);
            } else
                f_06caa8(s, 0, "", 0);
            id = f_077e74(s->v80(), title, 0);
            f_06ca64(s, 1, id);
            break;
        case 14:
            text -= D_245074.m0 != 0;
            break;
        case 15:
            text -= D_245074.m1 != 0;
            break;
        }
        f_06cb40(s, x, y, text, 1.0f, 1.0f, 1.0f, 1.0f, 480);
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
