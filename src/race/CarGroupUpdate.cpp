/* The per frame update of the race's cars (retail 0x0c2f24 to 0x0c4444): the cars are sorted
   into the ones that are driven normally and the ones that are not (by a flag the leveling
   step sets), and each virtual step of the car is run over a group before the next step
   starts. The wireless race keeps the last state received from each remote console in static
   buffers and smooths each remote car towards it. The leveling step decides, from the angle
   of each car relative to the player, which cars are the ones to step normally. */

extern "C" {
void *memcpy(void *, const void *, unsigned int) throw();
int f_126f1c(const char *fmt, ...);
float sqrtf(float);
float f_0af380(const float *a, const float *b);
}

/* A table of the game database (made elsewhere) and the buffer its records are copied to. */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
};
extern CTable D_2407d0;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern "C" char *f_0368e8(CTable *t, const char *field, char *rec, int a, int i);
extern int D_240900;

/* A position or velocity vector. */
struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));
struct Rot4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* A sub object of the car at +2128. */
struct CarSub {
    char m0[16];
    float m16;
    float m20;
    float m24;
};

/* A race car (made elsewhere): its virtual steps are named by their vtable offsets. */
struct CCar {
    virtual ~CCar();
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
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v92();
    virtual void v96();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v112();
    virtual void v116();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v132();
    virtual void v136();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v152();
    virtual void v156();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v172();
    virtual void v176();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v192();
    virtual void v196();
    virtual void v200();
    virtual void v204();
    virtual void v208(float a, float b, float c);
    virtual void v212();
    char m4[72];
    int m76;
    int m80;
    char m84[16];
    int m100;
    char m104[24];
    int m128;
    char m132[1996];
    CarSub sub;
    char m2156[7980];
    int m10136;
    int m10140;
};

/* Per car tuning of a global car group (the 3 floats of the global D_240af4 at +228). */
struct CarGroup {
    char m0[228];
    float x, y, z;
};
extern CarGroup D_240af4;

/* A car's state as exchanged between consoles. */
struct CarState {
    float m0;
    float m4;
    float m8;
    float m12;
    int m16;
    int m20;
    char m24[8];
    int m32;
    bool m36;
    bool m37;
    bool m38;
    bool m39;
    bool m40;
    bool m41;
    bool m42;
    Vec4 pos;
    Vec4 vel;
    Rot4 rot;

    void Init()
    {
        m0 = 0;
        m4 = 0;
        m8 = 2000.0f;
        m12 = 0;
        m42 = 1;
    }
    void f_0849a4(CCar *car);
    void f_084ad0(CCar *car);
    void f_084bd8(int t);
    void f_084cf4(CarState *s);
    void f_084ffc(CarState *s);
};

/* The race packet object (D_241804) and the game packet processor (D_241760). */
struct CNetRacePacket {
    int f_084048(unsigned int ch, CarState *car, char *b);
};
extern CNetRacePacket D_241804;
extern int D_241760;
extern int D_2466fc;
extern int D_2466e0[8];

extern "C" {
void f_0b9d28(void *car, int a, int b);
void f_0a78f0(void *);
void f_0a79a0(void *);
void f_0a79bc(void *);
void f_0a7a48(void *);
void f_0a7a78(void *);
void f_0a7aa8(void *);
void f_0a7ae0(void *);
void f_0a7b18(void *);
void f_0a7b60(void *);
void f_0a7e70(void *);
void f_0a881c(void *);
void f_0a88ac(void *);
}

/* @implements 0x0c2f24 us f_0c2f24
   WHAT IT DOES: Steps n cars (an array of car objects) through one frame: the cars that are
   active are split by their flag at +128 into the normal ones and the others; the normal
   ones run steps 156 to 204 and 80, the others step 156, 208 (with fixed arguments), 212 and
   80. */
void f_0c2f24(int n, CCar *c)
{
    CCar *a[16];
    CCar *b[16];
    int na = 0;
    int nb = 0;
    int i;
    if (n <= 0) return;
    for (i = 0; i < n; i++, c++) {
        if (c->m76) {
            if (!c->m128)
                a[na++] = c;
            else
                b[nb++] = c;
        }
    }
    for (i = 0; i < na; i++) a[i]->v156();
    for (i = 0; i < na; i++) a[i]->v160();
    for (i = 0; i < na; i++) a[i]->v164();
    for (i = 0; i < na; i++) a[i]->v168();
    for (i = 0; i < na; i++) a[i]->v172();
    for (i = 0; i < na; i++) a[i]->v176();
    for (i = 0; i < na; i++) a[i]->v180();
    for (i = 0; i < na; i++) a[i]->v184();
    for (i = 0; i < na; i++) a[i]->v188();
    for (i = 0; i < na; i++) a[i]->v192();
    for (i = 0; i < na; i++) a[i]->v196();
    for (i = 0; i < na; i++) a[i]->v200();
    for (i = 0; i < na; i++) a[i]->v204();
    for (i = 0; i < na; i++) a[i]->v80();
    for (i = 0; i < nb; i++) b[i]->v156();
    for (i = 0; i < nb; i++) b[i]->v208(1.024f, 1.0f, 0.0f);
    for (i = 0; i < nb; i++) b[i]->v212();
    for (i = 0; i < nb; i++) b[i]->v80();
}

/* @draft 0x0c32f0 us f_0c32f0
   WHAT IT DOES: Decides which of n cars are in the leveling state: the game database says
   whether the race mode levels cars ("CCar_Each", then "CCar_Level"). A car that is not in
   use is flagged, one that is not a normal car is cleared, and for the others the angle to
   the player car, in proportion to its speed (at least 42.667), is compared to a threshold
   pair for each side to set or clear the flag at +128.
   DRAFT: the control flow and instruction sequence agree; the registers differ (retail hoists
   only the high half of the 42.667 constant out of the loop, this source also hoists the
   first threshold pair, which moves every later register, and a float register differs). */
void f_0c32f0(int n, CCar *player, CCar *c)
{
    char *rec = f_0368e8(&D_2407d0, "CCar_Each", (char *)D_240900, 0, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    if (D_24063c[0]) {
        rec = f_0368e8(&D_2407d0, "CCar_Level", (char *)D_240900, 0, 0);
        memcpy(D_24063c, rec, D_1a211c[1]);
        if (!D_24063c[0]) {
            for (int i = 0; i < n; i++) c[i].m128 = 0;
            return;
        }
    }
    CarSub *ps = &player->sub;
    for (int i = 0; i < n; i++) {
        if (!c[i].m76) {
            c[i].m128 = 1;
        } else if (c[i].m80 == 2) {
            float ref = ps->m16;
            float d = f_0af380(&ref, &c[i].sub.m16);
            float hi, lo, s;
            if (d < 0.0f) {
                s = c[i].sub.m24;
                if (!(42.66670227f < s)) s = 42.66670227f;
                hi = 5.0f;
                lo = 4.5f;
            } else {
                CarSub *w = &c[i].sub;
                s = w->m24;
                if (!(42.66670227f < s)) s = 42.66670227f;
                hi = 3.0f;
                lo = 2.5f;
            }
            float r = d / s;
            if (r < 0.0f) r = -r;
            if (c[i].m128 == 0) {
                if (hi < r) c[i].m128 = 1;
            } else {
                if (r < lo) c[i].m128 = 0;
            }
        } else {
            c[i].m128 = 0;
        }
    }
}

/* @implements 0x0c3514 us f_0c3514
   WHAT IT DOES: Levels the cars (f_0c32f0) and then steps them as f_0c2f24 does, except that
   the cars that are not normal get the global group vector D_240af4 as step 208's arguments.
   Returns the number of normal cars. */
int f_0c3514(int n, CCar *player, CCar *c)
{
    CCar *a[16];
    CCar *b[16];
    int na = 0;
    int nb = 0;
    int i;
    if (n <= 0) return 0;
    f_0c32f0(n, player, c);
    for (i = 0; i < n; i++) {
        if (c[i].m76) {
            if (!c[i].m128)
                a[na++] = &c[i];
            else
                b[nb++] = &c[i];
        }
    }
    for (i = 0; i < na; i++) a[i]->v156();
    for (i = 0; i < na; i++) a[i]->v160();
    for (i = 0; i < na; i++) a[i]->v164();
    for (i = 0; i < na; i++) a[i]->v168();
    for (i = 0; i < na; i++) a[i]->v172();
    for (i = 0; i < na; i++) a[i]->v176();
    for (i = 0; i < na; i++) a[i]->v180();
    for (i = 0; i < na; i++) a[i]->v184();
    for (i = 0; i < na; i++) a[i]->v188();
    for (i = 0; i < na; i++) a[i]->v192();
    for (i = 0; i < na; i++) a[i]->v196();
    for (i = 0; i < na; i++) a[i]->v200();
    for (i = 0; i < na; i++) a[i]->v204();
    for (i = 0; i < na; i++) a[i]->v80();
    for (i = 0; i < nb; i++) b[i]->v156();
    for (i = 0; i < nb; i++) b[i]->v208(D_240af4.x, D_240af4.y, D_240af4.z);
    for (i = 0; i < nb; i++) b[i]->v212();
    for (i = 0; i < nb; i++) b[i]->v80();
    return na;
}

/* @draft 0x0c3e34 us f_0c3e34
   WHAT IT DOES: Steps the physics sub objects (at +2128) of n cars given as an array of
   pointers: the cars that are in use are split into the normal ones and the others (the
   cars of kind 0x2002, or without bit 0 and with the flag at +128), and the normal ones run ten
   physics steps one after the other over the group, the others the one step of their kind.
   DRAFT: instruction for instruction the same as retail; only two registers are swapped (the
   count of normal cars and the "any normal cars" flag) and the two stack array pointers are set
   up in the other order. */
void f_0c3e34(int n, CCar **cars)
{
    CCar *a[16];
    CCar *b[16];
    int na = 0;
    int nb = 0;
    int i;
    if (n <= 0) return;
    for (i = 0; i < n; i++) {
        CCar *p = cars[i];
        if (p->m76) {
            int v = p->m80;
            if (v != 0x2002) {
                if ((v & 1) || !p->m128) {
                    a[na++] = p;
                    continue;
                }
            }
            b[nb++] = p;
        }
    }
    for (i = 0; i < na; i++) f_0a78f0(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a79a0(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a79bc(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7a48(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7a78(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7aa8(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7ae0(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7b18(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7b60(&a[i]->sub);
    for (i = 0; i < na; i++) f_0a7e70(&a[i]->sub);
    for (i = 0; i < nb; i++) {
        if (b[i]->m80 == 0x2002)
            f_0a88ac(&b[i]->sub);
        else
            f_0a881c(&b[i]->sub);
    }
}

/* @draft 0x0c40b4 us f_0c40b4
   WHAT IT DOES: Runs virtual steps 16 to 44 of the cars in use that are of an odd kind or
   not flagged, over a group of n cars given as an array of pointers, one step after
   another.
   DRAFT: instruction for instruction the same as retail; only two registers are swapped (the
   count of normal cars and the "any normal cars" flag). */
void f_0c40b4(int n, CCar **cars)
{
    CCar *a[16];
    CCar *b[16];
    int na = 0;
    int nb = 0;
    int i;
    if (n <= 0) return;
    for (i = 0; i < n; i++) {
        CCar *p = cars[i];
        if (p->m76) {
            if ((p->m80 & 1) || !p->m128) {
                a[na++] = p;
                continue;
            }
            b[nb++] = p;
        }
    }
    for (i = 0; i < na; i++) a[i]->v16();
    for (i = 0; i < na; i++) a[i]->v20();
    for (i = 0; i < na; i++) a[i]->v24();
    for (i = 0; i < na; i++) a[i]->v28();
    for (i = 0; i < na; i++) a[i]->v32();
    for (i = 0; i < na; i++) a[i]->v36();
    for (i = 0; i < na; i++) a[i]->v40();
    for (i = 0; i < na; i++) a[i]->v44();
}

/* @implements 0x0c42ac us f_0c42ac
   WHAT IT DOES: Runs 20 sub steps of a frame: each starts the cars in use of the array arr2
   (f_0b9d28 and virtual step 12), runs the group steps (f_0c40b4) on list1, then runs virtual
   step 48 on the cars in use of arr2 and arr3. At the end it levels arr3 against arr2. */
void f_0c42ac(int n1, CCar **list1, int n2, CCar *arr2, int n3, CCar *arr3)
{
    for (int k = 0; k < 20; k++) {
        if (arr2) {
            for (int i = 0; i < n2; i++) {
                if (arr2[i].m76) {
                    f_0b9d28(&arr2[i], 2, 0);
                    arr2[i].v12();
                }
            }
        }
        f_0c40b4(n1, list1);
        if (arr2) {
            for (int i = 0; i < n2; i++) {
                if (arr2[i].m76) arr2[i].v48();
            }
        }
        if (arr3) {
            for (int i = 0; i < n3; i++) {
                if (arr3[i].m76) arr3[i].v48();
            }
        }
    }
    f_0c32f0(n3, arr2, arr3);
}

/* A state that is initialised when constructed (the buffers below). */
struct BufState : CarState {
    BufState() { Init(); }
};

/* @draft 0x0c38f8 us f_0c38f8
   WHAT IT DOES: Keeps the states of the remote cars of a wireless race, for n cars (at most
   8; logs an error otherwise). The three static buffers hold the newest state received for each
   car (newest), the one before it (previous) and the smoothed state the car is driven from
   (current). With flag clear it reads each remote car's (kind 0x2002) newest packet, keeps a
   newer one and brings the state forward by the time since it was sent, and drives the car
   from the smoothed state. With flag set it takes each car's state for sending, and counts
   down a 60 frame timer (D_2466e0) restarted whenever the car's position changed.
   DRAFT: the control flow matches (1292 of 1340 bytes); retail hoists the high halves of
   D_2466fc and D_241760 out of the car loop but not that of D_241804, recomputes the three
   buffer addresses after the guards instead of sharing them, and orders the stores of the
   state reset differently, which changes most registers. */
void f_0c38f8(int n, CCar *cars, int flag)
{
    if (n >= 9) {
        f_126f1c("ERROR : iBufNum>MAX_NET_CAR_NUM");
        return;
    }
    static BufState a_[7];
    static BufState b_[7];
    static BufState c_[7];
    CarState *newest = a_;
    CarState *previous = b_;
    CarState *current = c_;
    struct {
        CarState tmp;
        int t;
    } l;
    if (!flag) {
        for (int i = 0; i < n; i++) {
            CCar *car = &cars[i];
            if (car->m80 == 0x2002) {
                l.tmp.Init();
                int r = D_241804.f_084048(car->m100, &l.tmp, (char *)&l.t);
                if (r != -1 && car->m10136 < l.t) {
                    D_2466fc++;
                    newest[i] = l.tmp;
                    previous[i] = newest[i];
                    car->m10136 = l.t;
                    if (car->m10140) {
                        current[i] = newest[i];
                        current[i].m0 = 0;
                        current[i].m4 = 0;
                        current[i].m8 = 2000.0f;
                        current[i].m12 = 0;
                        current[i].m16 = 0;
                        current[i].m20 = 0;
                        car->m10140 = 0;
                    }
                    newest[i].f_084bd8(D_241760 - l.t);
                    current[i].f_084ffc(&newest[i]);
                } else if (!car->m10140) {
                    newest[i] = previous[i];
                    newest[i].f_084bd8(D_241760 - car->m10136);
                }
                if (!car->m10140) {
                    current[i].f_084cf4(&newest[i]);
                    current[i].f_084ad0(car);
                }
            }
        }
    } else {
        CarState &tmp = l.tmp;
        tmp.Init();
        for (int i = 0; i < n; i++) {
            tmp.f_0849a4(&cars[i]);
            if (tmp.pos.x != current[i].pos.x || tmp.pos.y != current[i].pos.y || tmp.pos.z != current[i].pos.z) {
                sqrtf(current[i].vel.x * current[i].vel.x + current[i].vel.y * current[i].vel.y +
                      current[i].vel.z * current[i].vel.z);
                sqrtf(tmp.vel.x * tmp.vel.x + tmp.vel.y * tmp.vel.y + tmp.vel.z * tmp.vel.z);
                D_2466e0[i] = 60;
            }
            D_2466e0[i]--;
            if (D_2466e0[i] < 0) D_2466e0[i] = 0;
            current[i].f_0849a4(&cars[i]);
        }
    }
}
