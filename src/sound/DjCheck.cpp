/* The race sound checks object file (retail 0x08e06c to 0x08f608). Each frame the checks
   look at the player's car and the other cars and start one-shot sounds: wall and car hits
   (louder the harder the hit, panned by the angle), cars passing with their horn or siren
   state, the drift squeal, the course's ambient sounds (helicopter, jet, fireworks, plane)
   and the final lap. Sounds play in 3D when the race mode asks for it. Debug lines show the
   hit damage and the ambient sound states. */

extern "C" {
float sqrtf(float);
}

void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...);
int f_0e7718(void *list, int i);
void f_10c09c(int bank, int snd, short pan, int a, float vol, void *h);
int f_10c86c(void *h);
int f_1137cc(int bank, int snd, int a, int b, float vol, void *pos, void *vel, void *dir, void *h);
int f_113ff8(void *pos, void *vel, void *dir, void *h);
void f_1140f4(void *h);

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

/* A sound voice handle. */
struct CSndHandle {
    int m0[9];
};

struct CCar {
    char pad0[76];
    int m76;
    char pad80[48];
    int m128;
    char pad132[12];
    Vec4 pos;
    char pad160[1636];
    int m1796;
    char pad1800[36];
    float m1836[3];
    char pad1848[40];
    int m1888;
    char pad1892[4];
    float m1896;
    float m1900;
    char pad1904[48];
    int m1952;
    char pad1956[4];
    float m1960;
    float m1964;
    char pad1968[140];
    int m2108;
    char pad2112[8];
    int m2120;
};

struct CRaceInfo {
    int m0[4];
    int m16;
    int m20;
    int m24[8];
    int m56;
    char pad60[136];
    CCar *player;
    int m200;
    CCar **cars;
    int m208[2];
    int count;
};
extern CRaceInfo *D_2407fc;

struct CSystemFlags {
    int m0;
    int seed;
    char m8[3];
    unsigned char m11;
    unsigned char m12;
};
extern CSystemFlags *D_1d88a0;

struct CCourseFlags {
    int m0[10];
    int finalLap;
};
extern CCourseFlags *D_1d3d40;

extern char D_24517c[];
extern char D_27eac0[];
extern float D_242c18;
extern float D_242c1c;
extern float D_242c20;
extern float D_242c24;
extern CSndHandle D_242c28;

static inline CCar *RaceCar(int i)
{
    return D_2407fc->cars[i];
}

class CDjCheck {
public:
    CDjCheck();
    ~CDjCheck();
    void f_08e0b4();
    void f_08e0c8();
    void f_08e160();
    void f_08e388();
    void f_08e5d4();
    void f_08e7a8();
    void f_08e97c();
    void f_08ea3c();
    void f_08ee48();
    void f_08ef74();
    CCar *f_08efc8();
    int f_08efd8();
    CCar *f_08f02c(int i);
    CCar *f_08f048(int n);
    float f_08f0a8(CCar *c);
    int f_08f188();
    int f_08f19c();
    int f_08f1b4();
    int f_08f1cc();
    int f_08f1e4();
    int f_08f1fc();
    void f_08f234(int id, float vol, float pan, float c, CSndHandle *h);
    void f_08f360(int id, Vec3 pos, Vec3 vel, float vol, float b, float c, CSndHandle *h);
    void f_08f47c(Vec3 pos, Vec3 vel, CSndHandle *h);
    void f_08f530(CSndHandle *h);
    int f_08f54c(CSndHandle *h);
    int f_08f56c(int id);

    CSndHandle ambient[4];
    int m144;
    int m148;
    int wallWait;
    int carWait;
};

/* @implements 0x08e06c us _ZN8CDjCheckC2Ev
   WHAT IT DOES: Builds the checks with every state cleared. */
CDjCheck::CDjCheck()
{
    f_08e0b4();
}

/* @implements 0x08e088 us _ZN8CDjCheckC1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x08e0a4 us _ZN8CDjCheckD2Ev
   WHAT IT DOES: Nothing to release. */
CDjCheck::~CDjCheck()
{
}

/* @implements 0x08e0ac us _ZN8CDjCheckD1Ev
   WHAT IT DOES: The same, as the complete object. */

/* @implements 0x08e0b4 us f_08e0b4
   WHAT IT DOES: Clears the drift state, the squeal count and the two hit timers. */
void CDjCheck::f_08e0b4()
{
    m144 = 0;
    m148 = 0;
    wallWait = 0;
    carWait = 0;
}

/* @implements 0x08e160 us f_08e160
   WHAT IT DOES: Wall hits. While the wait timer runs it only counts down. When the player's
   car has hit a wall, the timer restarts at 10 frames, the hit angle is folded into -pi/2 to
   pi/2 and turned into a pan, and the damage picks the sound: a light knock under 0.8, a
   harder one up to 1.0, a crash from 1.0. Shows the damage on screen. */
void CDjCheck::f_08e160()
{
    float lo = 0.8f;
    float hi = 1.0f;
    if (wallWait > 0) {
        wallWait--;
        return;
    }
    if (f_08efc8()->m1888 != 0) {
        CSndHandle h;
        wallWait = 10;
        float a = f_08efc8()->m1896;
        D_242c18 = a;
        if (a > 1.5707964f)
            D_242c18 = 3.1415927f - a;
        else if (a < -1.5707964f)
            D_242c18 = -3.1415927f - a;
        float pan = -(D_242c18 + D_242c18) / 3.1415927f;
        D_242c18 = pan;
        D_242c1c = f_08efc8()->m1900;
        if (D_242c1c < lo)
            {
                float v = 0.9f;
                if (D_2407fc->m20)
                    v = 1.0f;
                f_08f234(0, v, pan, 0.0f, &h);
            }
        if (lo < D_242c1c && D_242c1c < hi)
            {
                float v = 1.2f;
                if (D_2407fc->m20)
                    v = 1.0f;
                f_08f234(0, v, pan, 0.0f, &h);
            }
        if (hi <= D_242c1c)
            {
                float v = 1.5f;
                if (D_2407fc->m20)
                    v = 1.0f;
                f_08f234(1, v, pan, 0.0f, &h);
            }
    }
    f_02db68(D_24517c, 0x800000, 1, 15, 0xffffff, "WallHitDamage = %f", D_242c1c);
}

/* @implements 0x08e388 us f_08e388
   WHAT IT DOES: Car hits, like the wall hits: a 10-frame wait, the hit angle as the pan, and
   the damage picking the volume (0.5 to 1.5, 1.5 to 3.0, from 3.0). Shows the damage. */
void CDjCheck::f_08e388()
{
    float lo = 0.5f;
    float mid = 1.5f;
    float hi = 3.0f;
    if (carWait > 0) {
        carWait--;
        return;
    }
    if (f_08efc8()->m1952 != 0) {
        CSndHandle h;
        carWait = 10;
        float a = f_08efc8()->m1960;
        D_242c20 = a;
        if (a > 1.5707964f)
            D_242c20 = 3.1415927f - a;
        else if (a < -1.5707964f)
            D_242c20 = -3.1415927f - a;
        float pan = -(D_242c20 + D_242c20) / 3.1415927f;
        D_242c20 = pan;
        D_242c24 = f_08efc8()->m1964;
        if (lo < D_242c24 && D_242c24 < mid)
            {
                float v = 0.9f;
                if (D_2407fc->m20)
                    v = 1.0f;
                f_08f234(2, v, pan, 0.0f, &h);
            }
        if (mid < D_242c24 && D_242c24 < hi)
            {
                float v = 1.2f;
                if (D_2407fc->m20)
                    v = 1.0f;
                f_08f234(2, v, pan, 0.0f, &h);
            }
        if (hi <= D_242c24)
            {
                float v = 1.5f;
                if (D_2407fc->m20)
                    v = 1.0f;
                f_08f234(2, v, pan, 0.0f, &h);
            }
    }
    f_02db68(D_24517c, 0x800000, 1, 16, 0xffffff, "CarHitDamage = %f", D_242c24);
}

/* @implements 0x08e5d4 us f_08e5d4
   WHAT IT DOES: Sirens: plays the player's own siren when it is on (state 3), then, unless
   the race is in mode 2, plays the siren of every other car whose siren is on, at that car's
   position (in mode 3 with five or more cars only half the time). */
void CDjCheck::f_08e5d4()
{
    if (f_08efc8()->m1796 == 3) {
        CSndHandle s;
        f_08f234(3, 1.5f, 0.0f, 0.0f, &s);
    }
    if (f_08f1cc())
        return;
    for (int i = 0; i < f_08efd8(); i++) {
        if (f_08f048(i)->m1796 != 3)
            continue;
        if (f_08f048(i) == f_08efc8())
            continue;
        if (!f_08f1e4() || f_08efd8() < 5 || f_08f1fc() % 100 < 50) {
            if (f_08f048(i)->m128 == 0) {
                Vec3 pos;
                Vec3 vel;
                pos.x = f_08f048(i)->pos.x;
                pos.y = f_08f048(i)->pos.y;
                pos.z = f_08f048(i)->pos.z;
                vel.x = 0.0f;
                vel.z = vel.y = vel.x;
                CSndHandle h;
                f_08f360(3, pos, vel, 1.4f, vel.x, vel.x, &h);
            }
        }
    }
}

/* @implements 0x08e7a8 us f_08e7a8
   WHAT IT DOES: Horns, like the sirens: the player's horn (state 1), then every other car's. */
void CDjCheck::f_08e7a8()
{
    if (f_08efc8()->m2120 == 1) {
        CSndHandle s;
        f_08f234(4, 1.3f, 0.0f, 0.0f, &s);
    }
    if (f_08f1cc())
        return;
    for (int i = 0; i < f_08efd8(); i++) {
        if (f_08f048(i)->m2120 != 1)
            continue;
        if (f_08f048(i) == f_08efc8())
            continue;
        if (!f_08f1e4() || f_08efd8() < 5 || f_08f1fc() % 100 < 50) {
            if (f_08f048(i)->m128 == 0) {
                Vec3 pos;
                Vec3 vel;
                pos.x = f_08f048(i)->pos.x;
                pos.y = f_08f048(i)->pos.y;
                pos.z = f_08f048(i)->pos.z;
                vel.x = 0.0f;
                vel.z = vel.y = vel.x;
                CSndHandle h;
                f_08f360(4, pos, vel, 1.3f, vel.x, vel.x, &h);
            }
        }
    }
}

/* @implements 0x08e97c us f_08e97c
   WHAT IT DOES: The drift squeal: starts it once when the player's car starts drifting
   (state 1), and forgets it when the car is not drifting (state 0 or 3). */
void CDjCheck::f_08e97c()
{
    if (f_08efc8()->m2108 == 0)
        m144 = 0;
    else if (f_08efc8()->m2108 == 3)
        m144 = 0;
    int s = f_08efc8()->m2108;
    if (s == 1 && m144 == 0) {
        float v = 1.2f;
        if (D_2407fc->m20)
            v = 1.0f;
        f_08f234(5, v, 0.0f, 0.0f, &D_242c28);
        m144 = s;
    }
}

/* A course object as the ambient sounds read it: its position and velocity. */
struct CCourseObj {
    int m0[8];
    Vec3 pos;
    int m44;
    Vec3 vel;
};

/* @draft 0x08ea3c us f_08ea3c
   WHAT IT DOES: The course's four ambient sounds (helicopter, jet, fireworks, plane). For
   each one whose object exists: a free voice starts the sound at the object (the fireworks
   at a fixed spot), louder for the fireworks, unless the system is busy; a playing one is
   moved with the object, or stopped while the system is busy. When the object is gone a
   free voice is stopped. Each step is shown on screen. */
void CDjCheck::f_08ea3c()
{
    for (int i = 0; i < 4; i++) {
        CCourseObj *o = (CCourseObj *)f_0e7718(D_27eac0, i);
        if (o) {
            f_10c86c(&ambient[i]);
            Vec3 pos;
            Vec3 vel;
            pos.x = o->pos.x;
            pos.y = o->pos.y;
            pos.z = o->pos.z;
            vel.x = o->vel.x;
            vel.y = o->vel.y;
            vel.z = o->vel.z;
            if (f_08f54c(&ambient[i]) == 1) {
                if (!D_1d88a0->m11 && !D_1d88a0->m12) {
                    if (i == 0) {
                        f_08f360(10, pos, vel, 1.2f, 0.0f, 0.0f, &ambient[0]);
                    } else if (i == 1) {
                        f_08f360(11, pos, vel, 1.2f, 0.0f, 0.0f, &ambient[1]);
                    } else if (i == 2) {
                        pos.x = 630200.0f;
                        pos.y = 172600.0f;
                        pos.z = 1040600.0f;
                        f_08f360(12, pos, vel, 5.0f, 0.0f, 0.0f, &ambient[2]);
                    } else if (i == 3) {
                        f_08f360(13, pos, vel, 1.2f, 0.0f, 0.0f, &ambient[3]);
                    }
                }
                if (i == 0) {
                    f_02db68(D_24517c, 0x800000, 1, 10, 0xffffff, "Heli Sound KeyOn");
                } else if (i == 1) {
                    f_02db68(D_24517c, 0x800000, 1, 10, 0xffffff, "Jet Sound KeyOn");
                } else if (i == 2) {
                    f_02db68(D_24517c, 0x800000, 1, 10, 0xffffff, "Hanabi Sound KeyOn");
                } else if (i == 3) {
                    f_02db68(D_24517c, 0x800000, 1, 10, 0xffffff, "Cessna Sound KeyOn");
                }
            } else {
                if (D_1d88a0->m11 || D_1d88a0->m12) {
                    f_08f530(&ambient[i]);
                } else {
                    if (i == 2) {
                        pos.x = 630200.0f;
                        pos.y = 172600.0f;
                        pos.z = 1040600.0f;
                    }
                    f_08f47c(pos, vel, &ambient[i]);
                }
                if (i == 0) {
                    f_02db68(D_24517c, 0x800000, 1, 11, 0xffffff, "Heli Sound is On the Air");
                } else if (i == 1) {
                    f_02db68(D_24517c, 0x800000, 1, 12, 0xffffff, "Jet Sound is On the Air");
                } else if (i == 2) {
                    f_02db68(D_24517c, 0x800000, 1, 13, 0xffffff, "Hanabi Sound is On the Air");
                } else if (i == 3) {
                    f_02db68(D_24517c, 0x800000, 1, 14, 0xffffff, "Cessna Sound is On the Air");
                }
            }
        } else if (!f_08f54c(&ambient[i])) {
            f_08f530(&ambient[i]);
            const char *m;
            if (i == 0)
                m = "Heli Sound KeyOff";
            else if (i == 1)
                m = "Jet Sound KeyOff";
            else if (i == 2)
                m = "Hanabi Sound KeyOff";
            else if (i == 3)
                m = "Cessna Sound KeyOff";
            else
                continue;
            f_02db68(D_24517c, 0x800000, 1, 10, 0xffffff, m);
        }
    }
}

/* @implements 0x08ee48 us f_08ee48
   WHAT IT DOES: Counts the player's wheels on full squeal (100); when the count rises during
   a drift, plays the squeal for one, two or three wheels. */
void CDjCheck::f_08ee48()
{
    float full = 100.0f;
    int n = 0;
    for (int i = 0; i < 3; i++)
        if (f_08efc8()->m1836[i] == full)
            n++;
    if (m148 < n) {
        CSndHandle h;
        full = 1.0f;
        if (f_08f1b4()) {
            if (n == 1)
                f_08f234(6, full, 0.0f, 0.0f, &h);
            if (n == 2)
                f_08f234(7, full, 0.0f, 0.0f, &h);
            if (n == 3)
                f_08f234(8, full, 0.0f, 0.0f, &h);
        }
    }
    m148 = n;
}

/* @implements 0x08ef74 us f_08ef74
   WHAT IT DOES: Plays the final lap sound once when the course flags it. */
void CDjCheck::f_08ef74()
{
    CSndHandle h;
    if (D_1d3d40->finalLap) {
        f_08f234(9, 1.0f, 0.0f, 0.0f, &h);
        D_1d3d40->finalLap = 0;
    }
}

/* @implements 0x08efc8 us f_08efc8
   WHAT IT DOES: Returns the player's car. */
CCar *CDjCheck::f_08efc8()
{
    return D_2407fc->player;
}

/* @implements 0x08efd8 us f_08efd8
   WHAT IT DOES: Counts the cars that are in the race. */
int CDjCheck::f_08efd8()
{
    int n = 0;
    for (int i = 0; i < D_2407fc->count; i++)
        if (RaceCar(i)->m76)
            n++;
    return n;
}

/* @implements 0x08f02c us f_08f02c
   WHAT IT DOES: Returns car i of the race's car table. */
CCar *CDjCheck::f_08f02c(int i)
{
    return D_2407fc->cars[i];
}

/* @implements 0x08f048 us f_08f048
   WHAT IT DOES: Returns the n-th car that is in the race, or null. */
CCar *CDjCheck::f_08f048(int n)
{
    int k = -1;
    for (int i = 0; i < D_2407fc->count; i++) {
        CCar *c = D_2407fc->cars[i];
        k += c->m76 != 0;
        if (k == n)
            return c;
    }
    return 0;
}

/* @draft 0x08f0a8 us f_08f0a8
   WHAT IT DOES: Returns the distance from the player's car to another car. */
float CDjCheck::f_08f0a8(CCar *c)
{
    Vec4 *pp = &f_08efc8()->pos;
    Vec4 *qq = &c->pos;
    Vec4 p = *pp;
    Vec4 q = *qq;
    Vec4 d;
    d.x = q.x - p.x;
    d.y = q.y - p.y;
    d.z = q.z - p.z;
    d.w = 1.0f;
    return sqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
}

/* @implements 0x08f188 us f_08f188
   WHAT IT DOES: Whether the race state is 0. */
int CDjCheck::f_08f188()
{
    return D_2407fc->m56 == 0;
}

/* @implements 0x08f19c us f_08f19c
   WHAT IT DOES: Whether the race state is 5. */
int CDjCheck::f_08f19c()
{
    return D_2407fc->m56 == 5;
}

/* @implements 0x08f1b4 us f_08f1b4
   WHAT IT DOES: Whether the race state is 1 (racing). */
int CDjCheck::f_08f1b4()
{
    return D_2407fc->m56 == 1;
}

/* @implements 0x08f1cc us f_08f1cc
   WHAT IT DOES: Whether the race mode is 2. */
int CDjCheck::f_08f1cc()
{
    return D_2407fc->m16 == 2;
}

/* @implements 0x08f1e4 us f_08f1e4
   WHAT IT DOES: Whether the race mode is 3. */
int CDjCheck::f_08f1e4()
{
    return D_2407fc->m16 == 3;
}

/* @implements 0x08f1fc us f_08f1fc
   WHAT IT DOES: A pseudo-random number from the system seed (one linear congruential step),
   made positive. */
int CDjCheck::f_08f1fc()
{
    int r = D_1d88a0->seed * 0x19660d + 0x3c6ef35f;
    if (r < 0)
        r = -r;
    return r;
}

/* @implements 0x08f234 us f_08f234
   WHAT IT DOES: Plays a check sound: looks up its sound number (37 means none), then plays it
   flat with the pan, or in 3D at the player's car (scaled by 1/1000) when the race mode
   asks for it. */
void CDjCheck::f_08f234(int id, float vol, float pan, float c, CSndHandle *h)
{
    unsigned short snd = f_08f56c(id);
    pan *= 64.0f;
    short p = (short)pan;
    if (snd == 37)
        return;
    if (D_2407fc->m20 != 0) {
        Vec3 pos;
        pos.x = f_08efc8()->pos.x / 1000.0f;
        pos.y = f_08efc8()->pos.y / 1000.0f;
        pos.z = f_08efc8()->pos.z / 1000.0f;
        Vec3 vel;
        vel.z = 0.0f;
        vel.y = 0.0f;
        vel.x = 0.0f;
        Vec3 dir;
        dir.z = 0.0f;
        dir.y = 0.0f;
        dir.x = 0.0f;
        f_1137cc(562, snd, 0, 0, vol, &pos, &vel, &dir, h);
    } else {
        f_10c09c(562, snd, p, 0, vol, h);
    }
}

/* @implements 0x08f360 us f_08f360
   WHAT IT DOES: Plays a check sound in 3D at a given position and velocity (scaled by
   1/1000), and shows the result. */
void CDjCheck::f_08f360(int id, Vec3 p, Vec3 v, float vol, float b, float c, CSndHandle *h)
{
    unsigned short snd = f_08f56c(id);
    if (snd == 37)
        return;
    Vec3 sp, sv;
    sp.x = p.x / 1000.0f;
    sp.y = p.y / 1000.0f;
    sp.z = p.z / 1000.0f;
    sv.x = v.x / 1000.0f;
    sv.y = v.y / 1000.0f;
    sv.z = v.z / 1000.0f;
    Vec3 dir;
    dir.z = 0.0f;
    dir.y = 0.0f;
    dir.x = 0.0f;
    int r = f_1137cc(562, snd, 0, 0, vol, &sp, &sv, &dir, h);
    f_02db68(D_24517c, 0x800000, 1, 8, 0xffffff, "KeyOn3D result = %x", r);
}

/* @implements 0x08f47c us f_08f47c
   WHAT IT DOES: Moves a playing 3D sound to a new position and velocity (scaled by 1/1000). */
void CDjCheck::f_08f47c(Vec3 p, Vec3 v, CSndHandle *h)
{
    Vec3 sp, sv, dir;
    dir.x = dir.y = dir.z = 0.0f;
    sp.x = p.x / 1000.0f;
    sp.y = p.y / 1000.0f;
    sp.z = p.z / 1000.0f;
    sv.x = v.x / 1000.0f;
    sv.y = v.y / 1000.0f;
    sv.z = v.z / 1000.0f;
    f_113ff8(&sp, &sv, &dir, h);
}

/* @implements 0x08f530 us f_08f530
   WHAT IT DOES: Stops a sound. */
void CDjCheck::f_08f530(CSndHandle *h)
{
    f_1140f4(h);
}

/* @implements 0x08f54c us f_08f54c
   WHAT IT DOES: Whether a sound is playing. */
int CDjCheck::f_08f54c(CSndHandle *h)
{
    return f_10c86c(h) != 0;
}

/* @implements 0x08f56c us f_08f56c
   WHAT IT DOES: Maps a check sound (0 to 13) to its number in the sound bank; 37 for none. */
int CDjCheck::f_08f56c(int id)
{
    int s = 37;
    switch (id) {
    case 0: s = 13; break;
    case 1: s = 12; break;
    case 2: s = 15; break;
    case 3: s = 16; break;
    case 4: s = 33; break;
    case 5: s = 31; break;
    case 6: s = 26; break;
    case 7: s = 27; break;
    case 8: s = 28; break;
    case 9: s = 0; break;
    case 10: s = 24; break;
    case 11: s = 23; break;
    case 12: s = 21; break;
    case 13: s = 22; break;
    }
    return s;
}
