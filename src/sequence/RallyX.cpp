/* The Rally-X mini game object file (retail 0x02dfb4 to 0x031b98), played while the race
   loads. A small state machine (title, play, round start, round clear, demo, game over) runs
   the game: the player's car and up to seven enemy cars drive a 32 x 32 cell maze, the player
   collects flags against a fuel gauge, and the score, high score and lives are drawn with the
   2D sprite helpers at 0x0e79c8 on. Each state has entry, update, exit and two draw handlers
   in a table; the music cues come from the RallyX_BGM package. */

struct Car;

extern "C" {
int f_00222c(const char *name, const char *package);
int f_113424(int ch, void *data, int arg);
void f_113488(int ch);
void f_1135b8(int ch, float volume);
void *f_093330(void);
int f_0933f8(void *snd, int se);
void f_093448(void *snd, int h);
void f_093464(void *snd);
void f_093480(void *snd, int h, float volume);
int f_09349c(void *snd, int h);
void f_0934d4(void *snd);
void f_0934f8(void *snd);
void f_093518(void *snd, float volume);
float f_093538(void *snd);
int sceDisplayWaitVblankStart(void);
int f_0e7c38(void);
void f_0e84b0(void);
void f_0e84fc(void *map);
void f_0e7c20(void);
void f_0e9820(Car *car, Car *enemies);
void f_0e8db0(Car *car);
void f_0e8840(Car *car);
void f_0e89f4(Car *car, int *fuel);
void f_0e930c(Car *car);
void f_0e9564(Car *car, Car *player);
int f_0e8d78(Car *car, int x, int y);
void f_0e79c8(unsigned int color);
void f_0e7a10(int on);
void f_0e7a40(int w, int h);
void f_0e7a54(int x, int y, int u, int v);
unsigned char f_0e842c(int x, int y);
void f_0e821c(int n, int *px, int *py);
void f_0e82c4(int n, int *px, int *py);
void f_0e8344(int n, int *px, int *py, int flag);
void f_0e814c(int x, int y, int n, int flag);
void f_0e7bc8(int x, int y, int w, int h);
int f_0e7db0(const char *text, int frame, int hidden);
void f_0e7c4c(int x, int y, const char *text, int n, unsigned int color);
void f_0e7cf4(int x, int y, int value, unsigned int color);
}

/* A package of named resources. */
class CPackage {
public:
    void *f_002acc(const char *name);
    int m0;
    int m4[69];
};
extern CPackage D_1d8cd0;

/* A music cue: its name and stream arguments. */
struct BgmEntry {
    const char *name;
    int m4[2];
    int arg;
    int m16[2];
};
extern BgmEntry D_1c0614[];

/* One state of the mini game. */
struct State {
    void (*enter)(void);
    void (*update)(int pad);
    void (*exit)(void);
    void (*draw)(void);
    void (*draw2)(void);
};

/* A car in the maze. */
struct Car {
    short x, y;          /* position in maze units (384 per cell) */
    short cx, cy;        /* cell */
    unsigned short m8;
    short m10;
    short m12;
    short trail[6];
    short cell;
    short m28;
    short m30;
    short m32;
    short m34;
    short m36;
    short dir;
    short m40;
    short m42;
    char alive;
    char m45[3];
    int (*think)(Car *car);
    unsigned short m52;
    short m54;
};

/* A stage: its maze, the cars' starting directions and the enemy drivers. */
struct Stage {
    short m0;
    short map;
    short m4;
    short dir;
    short enemyDir;
    short m10;
    short enemies;
    short driver[7];
};

/* A maze. */
struct Map {
    short m0[2];
    short startX, startY;
    short m8[28];
    short enemyStart[8];
    unsigned int wallColor;
    short m84[2];
    unsigned char cell[1024]; /* each cell's kind (low 7 bits) */
};

/* A flag in the maze: its state (0 none, 1 to 3 waiting, 4 on taken) and its cell. */
struct Flag {
    signed char state;
    char m1[3];
    short cx, cy;
};
extern int D_1d5584;
extern Flag D_27ebf4[];

/* The score board: ten entries and the round's flags. */
struct Board {
    int a[11];
    int b[11];
    int m88;
};

extern signed char D_27ec74;
extern signed char D_27ec75;
extern Stage *D_1d5a7c;
extern Stage D_1d5910[];
extern Stage D_1d55ac[];
extern unsigned char D_1d55a8[];
extern Map *D_27ebd8[];
extern Map *D_27ebf0;

signed char D_1d1a90 = 1;
unsigned int D_1d1a94[2] = { 20000, 2000 };
int D_1d1a9c = 3;
float D_1d1aa0 = 1.0f;
float D_1d1aa4 = 0.8f;
extern State D_1d1aa8[];
extern int (*D_1d1b20[])(Car *car);

Board D_240064;
signed char D_2400c0;
signed char D_2400c1;
signed char D_2400c2;
signed char D_2400c3;
signed char D_2400c4;
signed char D_2400c5;
int D_2400c8;
int D_2400cc;
int D_2400d0;
int D_2400d4;
int D_2400d8;
int D_2400dc;
unsigned int D_2400e0;
int D_2400e4;
int D_2400e8;
int D_2400ec;
int D_2400f0;
int D_2400f4;
int D_2400f8;
int D_2400fc;
int D_240100;
Car D_240104[7];
Car D_24028c;
int D_2402c4;
int D_2402c8;
int D_2402cc;
int D_2402d0;
int D_2402d4;

/* The states that play the round music's tail. */
static inline bool IsPlayState(int s)
{
    return s == 0 || s == 4;
}

/* Starts a music cue of the RallyX_BGM package on channel 0. */
static inline void PlayBgm(const char *name)
{
    int arg = D_1c0614[f_00222c(name, "RallyX_BGM")].arg;
    f_113424(0, D_1d8cd0.f_002acc(name), arg);
    f_1135b8(0, D_1d1aa4);
}

/* @implements 0x02dfb4 us f_02dfb4
   WHAT IT DOES: Changes the mini game state: runs the old state's exit handler, stops its
   music, enters the new state (resetting the state frame counter) and starts the new state's
   jingle (start, second start or high score). */
void f_02dfb4(int state)
{
    State *tbl = D_1d1aa8;
    if (tbl[D_2400c8].exit)
        tbl[D_2400c8].exit();
    if (D_2400c8 != 2)
        f_113488(0);
    if (D_2400c8 == 4)
        f_0934d4(f_093330());
    if (IsPlayState(D_2400c8))
        D_2400c5 = 0;
    f_093464(f_093330());
    D_2400d4 = 0;
    D_2400c8 = state;
    if (tbl[state].enter)
        tbl[state].enter();
    if (D_2400c8 == 2)
        PlayBgm("START");
    if (D_2400c8 == 3)
        PlayBgm("START2");
    if (D_2400c8 == 5)
        PlayBgm("HIGH");
    if (D_2400c8 == 4)
        f_0934f8(f_093330());
    if (IsPlayState(D_2400c8))
        D_2400c5 = 1;
}

/* Selects the stage list of the current mode (normal or the hidden one) from its first stage. */
static inline void SelectStages()
{
    signed char hidden = D_2400c1;
    D_27ec75 = hidden;
    D_27ec74 = 0;
    Stage *list = D_1d5910;
    if (!hidden)
        list = D_1d55ac;
    D_1d5a7c = list;
}

void f_02e380(void);
void f_02e400(void);
void f_02e704(void);

/* @draft 0x02e264 us f_02e264
   WHAT IT DOES: Starts the mini game (in demo mode or not): clears the flags and counters,
   keeps the two high scores at least 20000 and 2000, clears the score board, selects the
   normal stages and enters the title state (or, in demo mode, starts a game at once), and
   remembers the music volume. */
void f_02e264(int demo)
{
    D_2402d0 = 0;
    D_2400c4 = 0;
    D_2402c8 = 0;
    D_2400c3 = demo;
    D_2400d8 = 0;
    D_2400c5 = 0;
    D_2400c1 = 0;
    if (D_1d1a94[0] < 20000)
        D_1d1a94[0] = 20000;
    if (D_1d1a94[1] < 2000)
        D_1d1a94[1] = 2000;
    D_240100 = 0;
    for (int i = 0; i < 11; i++) {
        D_240064.a[i] = -1;
        D_240064.b[i] = -1;
    }
    D_240064.m88 = 0;
    SelectStages();
    if (D_2400c3) {
        f_02e380();
        f_02dfb4(1);
    } else {
        f_02dfb4(0);
    }
    D_1d1aa0 = f_093538(f_093330());
}

/* @draft 0x02e380 us f_02e380
   WHAT IT DOES: Starts a new game: three lives, no score, no extra life awarded, no new high
   score; unless a stage was chosen in stage select, starts from the first stage. Then starts
   the first round. */
void f_02e380(void)
{
    signed char chosen = D_1d1a90;
    D_1d1a9c = 3;
    D_2400e0 = 0;
    D_2400dc = 0;
    D_2400c2 = 0;
    if (!chosen)
        SelectStages();
    f_02e400();
}

/* Places a car at the start of the round in a cell. */
static inline void Place(Car *c, short cx, short cy)
{
    c->x = cx * 384 + 192;
    c->y = cy * 384 + 192;
}

/* @draft 0x02e400 us f_02e400
   WHAT IT DOES: Starts a round of the current stage: loads its maze, puts the player's car at
   the maze start and each enemy car at its start cell with its driver (enemies 5 and 6 wait
   before leaving), then resets the round (f_02e704). */
void f_02e400(void)
{
    Stage *st = &D_1d5a7c[D_27ec74];
    D_27ebf0 = D_27ebd8[st->map];
    f_0e84fc(D_27ebf0);
    Map *m = D_27ebf0;
    st = &D_1d5a7c[D_27ec74];
    Car *p = &D_24028c;
    short sx = m->startX;
    short sy = m->startY;
    short cell = sy * 32 + sx;
    p->x = sx * 384 + 192;
    p->y = sy * 384 + 192;
    p->m52 = p->m8;
    p->m32 = -1;
    p->cell = cell;
    p->dir = 2;
    p->alive = 1;
    p->m12 = 0;
    p->cx = sx;
    p->cy = sy;
    p->trail[0] = cell;
    p->trail[1] = cell;
    p->trail[2] = cell;
    p->trail[3] = cell;
    p->trail[4] = cell;
    p->trail[5] = cell;
    p->m30 = 0;
    p->m28 = 0;
    p->m40 = 0;
    p->m42 = 0;
    p->m36 = 0;
    p->m10 = 0;
    p->think = 0;
    for (int i = 0; i < st->enemies; i++) {
        Car *c = &D_240104[i];
        int w = 32;
        int pos = m->enemyStart[i];
        short cx = pos % w;
        short cy = pos / w;
        short ccell = cy * 32 + cx;
        c->m52 = c->m8;
        c->alive = 1;
        c->m30 = 0;
        c->m28 = 0;
        c->m32 = -1;
        c->dir = 2;
        c->m40 = 1;
        c->m42 = 0;
        c->m36 = 0;
        c->m10 = 0;
        c->m12 = 0;
        c->y = cy * 384 + 192;
        c->x = cx * 384 + 192;
        c->cell = ccell;
        c->cx = cx;
        c->cy = cy;
        c->trail[0] = ccell;
        c->trail[1] = ccell;
        c->trail[2] = ccell;
        c->trail[3] = ccell;
        c->trail[4] = ccell;
        c->trail[5] = ccell;
        c->think = D_1d1b20[st->driver[i]];
        if (i == 5 || i == 6) {
            c->m30 = 2;
            c->m28 = 96;
        }
    }
    D_2400e4 = 0;
    f_02e704();
}

/* @draft 0x02e664 us f_02e664
   WHAT IT DOES: Enters the title state: clears the hidden code progress and the chosen stage,
   and selects the current mode's stages. */
void f_02e664(void)
{
    signed char hidden = D_2400c1;
    D_2400c0 = 0;
    D_1d1a90 = 0;
    D_27ec75 = hidden;
    D_27ec74 = 0;
    Stage *list = D_1d5910;
    if (!hidden)
        list = D_1d55ac;
    D_1d5a7c = list;
}

/* @draft 0x02e6ac us f_02e6ac
   WHAT IT DOES: Enters the demo state: in the hidden mode, starts a round of its fifth stage. */
void f_02e6ac(void)
{
    signed char hidden = D_2400c1;
    if (hidden) {
        D_27ec75 = hidden;
        D_27ec74 = 0;
        Stage *list = D_1d5910;
        if (!hidden)
            list = D_1d55ac;
        D_1d5a7c = list;
        D_27ec74 = 4;
        f_02e400();
    }
}

/* @draft 0x02e704 us f_02e704
   WHAT IT DOES: Resets the round after a start or a crash: every car back at its start cell
   facing the stage's directions, a full fuel gauge, the counters cleared, and the maze's
   display reset. */
void f_02e704(void)
{
    Map *m = D_27ebf0;
    Stage *st = &D_1d5a7c[D_27ec74];
    Car *p = &D_24028c;
    short sx = m->startX;
    short sy = m->startY;
    short cell = sy * 32 + sx;
    p->x = sx * 384 + 192;
    p->y = sy * 384 + 192;
    p->trail[1] = cell;
    p->m32 = -1;
    p->alive = 1;
    p->cx = sx;
    p->cy = sy;
    p->trail[0] = cell;
    p->m30 = 0;
    p->m28 = 0;
    p->m42 = 0;
    p->m36 = 0;
    p->m10 = 0;
    p->m12 = 0;
    p->dir = st->dir;
    for (int i = 0; i < st->enemies; i++) {
        Car *c = &D_240104[i];
        int w = 32;
        int pos = m->enemyStart[i];
        short cx = pos % w;
        short cy = pos / w;
        short ccell = cy * 32 + cx;
        c->m30 = 0;
        c->m28 = 0;
        c->m32 = -1;
        c->m42 = 0;
        c->m36 = 0;
        c->alive = 1;
        c->m10 = 0;
        c->m12 = 0;
        c->x = cx * 384 + 192;
        c->y = cy * 384 + 192;
        c->trail[1] = ccell;
        c->cx = cx;
        c->cy = cy;
        c->trail[0] = ccell;
        c->dir = st->enemyDir;
        if (i == 5 || i == 6) {
            c->m30 = 2;
            c->m28 = 96;
        }
    }
    D_2400d8 = 1;
    D_2400f4 = 0x9600;
    D_2400d4 = 0;
    D_2400e8 = 0;
    D_2400ec = 0;
    D_2400f0 = 0;
    D_2400d0 = 0;
    f_0e84b0();
}

/* @draft 0x02e8e8 us f_02e8e8
   WHAT IT DOES: Counts the fuel left into the score at the end of a round, 160 fuel units (8
   points) a frame. When asked to start, first remembers the gauge and the final score so the
   count can be skipped. Returns whether there was fuel left to count; with none, restores the
   remembered gauge and the final score.
   Remaining difference: entry block order. Retail sched1 puts counting = 0 ahead of the two %hi loads that ce2 (if-case-2) moves up from the start == 0 edge block, so dbr fills the beqz slot with lui t1; ours has the zero last (all three are priority-0 ties in sched1, picked last-LUID first), so the zero lands in the slot. Needs the zero after the hoisted %hi loads in the block, or a priority above 0; the source shape for that is not found. */
int f_02e8e8(int start)
{
    int counting = 0;
    if (start) {
        int f = D_2400f4;
        D_2400f8 = f;
        D_2400fc = D_2400e0 + ((f / 6 * 5) >> 4) / 10 * 10;
    }
    int f = D_2400f4;
    if (f > 0) {
        if (f < 160) {
            D_2400f4 = 0;
            D_2400e0 += (f / 6 * 5) >> 4;
        } else {
            D_2400f4 = f - 160;
            D_2400e0 += 8;
        }
        counting = 1;
    } else {
        D_2400f4 = D_2400f8;
        D_2400e0 = D_2400fc;
    }
    return counting;
}

/* @implements 0x02e9e8 us f_02e9e8
   WHAT IT DOES: Stops the mini game's sounds and restores the music volume. */
void f_02e9e8(void)
{
    f_113488(0);
    f_093464(f_093330());
    f_093518(f_093330(), D_1d1aa0);
}

void f_031a94(Board *b);

/* @implements 0x02ea2c us f_02ea2c
   WHAT IT DOES: Runs one frame of the mini game: steps the score board and the sprite
   animation; while a state change is pending, counts down to it; otherwise counts the frame,
   awards the extra lives at 20000 and 80000 points, notes a score of 50000, keeps the high
   score, and runs the current state's update with the pad. */
void f_02ea2c(int pad)
{
    f_031a94(&D_240064);
    f_0e7c20();
    if (!(D_2400d8 & 0x400)) {
        if (D_2400d0 > 0) {
            if (--D_2400d0 == 0)
                f_02dfb4(D_2400cc);
            return;
        }
        D_2400d4++;
        if (D_2400dc == 0 && D_2400e0 >= 20000) {
            D_1d1a9c++;
            D_2400dc = 1;
            f_0933f8(f_093330(), 9);
        } else if (D_2400dc == 1 && D_2400e0 >= 80000) {
            D_1d1a9c++;
            D_2400dc = 2;
            f_0933f8(f_093330(), 9);
        }
        unsigned int score = D_2400e0;
        if (score > 49999)
            D_240100 = 1;
        unsigned int *high = &D_1d1a94[D_2400c1];
        if (*high < score) {
            *high = score;
            D_2400c2 = 1;
        }
    }
    D_1d1aa8[D_2400c8].update(pad);
    D_2402c8 = pad;
}

/* @implements 0x02ebc8 us f_02ebc8
   WHAT IT DOES: Draws the mini game: the current state's two draw handlers. */
void f_02ebc8(void)
{
    D_1d1aa8[D_2400c8].draw();
    D_1d1aa8[D_2400c8].draw2();
}

/* A newly pressed pad. */
static inline bool Pressed(int pad)
{
    return pad != D_2402d4 && pad != 0;
}

/* @draft 0x02ec38 us f_02ec38
   WHAT IT DOES: The title state's update. Watches for the hidden code (Square, Up, Down, Down,
   Left, Right? pressed in turn) that unlocks stage select; L+R+Select toggles the hidden
   mode; in stage select, left and right choose the stage; Start begins the game. */
void f_02ec38(int pad)
{
    if (Pressed(pad)) {
        if (D_2400c0 == 0 && (pad & 0x40))
            D_2400c0 = 1;
        else if (D_2400c0 == 1 && (pad & 0x200))
            D_2400c0 = 2;
        else if (D_2400c0 == 2 && (pad & 0x80))
            D_2400c0 = 3;
        else if (D_2400c0 == 3 && (pad & 0x80))
            D_2400c0 = 4;
        else if (D_2400c0 == 4 && (pad & 0x10))
            D_2400c0 = 5;
        else if (D_2400c0 == 5 && (pad & 0x100)) {
            D_1d1a90 = 1;
            f_0933f8(f_093330(), 10);
        } else
            D_2400c0 = 0;
    }
    if (Pressed(pad) && (pad & 0xc0) == 0xc0 && (pad & 1)) {
        D_2400d4 = 0;
        D_2400c1 = !D_2400c1;
        D_2402d0 = 0;
        SelectStages();
    }
    if (D_1d1a90) {
        if (!(D_2402d4 & 4) && (pad & 4)) {
            int n = D_1d55a8[D_27ec75];
            D_27ec74 = (D_27ec74 - 1) % n;
            if (D_27ec74 < 0)
                D_27ec74 = n - 1;
        }
        if (!(D_2402d4 & 8) && (pad & 8))
            D_27ec74 = (D_27ec74 + 1) % D_1d55a8[D_27ec75];
    }
    D_2402d4 = pad;
    if (pad & 0x20) {
        if (pad & 0x10) {
            D_1d1a90 = 1;
            D_27ec74 = D_2402d0;
        }
        f_02dfb4(2);
        f_02e400();
    }
}

/* Queues a sound effect of the score board's voice table, if there is room. */
static inline void Sfx(int id)
{
    Board *b = &D_240064;
    if (b->m88 < 11)
        b->b[b->m88++] = id;
}

/* Stops every voice of the board and empties the queue down to one effect. */
static inline void StopVoices(int id)
{
    Board *b = &D_240064;
    for (int i = 0; i < 11; i++) {
        if (b->a[i] != -1)
            f_093448(f_093330(), b->a[i]);
        b->a[i] = -1;
        b->b[i] = -1;
    }
    b->m88 = 1;
    b->b[0] = id;
}

/* Starts a music cue of the RallyX_BGM package on channel 0, waiting for the stream. */
static inline void PlayBgmWait(const char *name)
{
    int arg = D_1c0614[f_00222c(name, "RallyX_BGM")].arg;
    while (f_113424(0, D_1d8cd0.f_002acc(name), arg))
        sceDisplayWaitVblankStart();
}

/* @draft 0x02ef14 us f_02ef14
   WHAT IT DOES: The play state's update, once a frame with the pad. Start toggles the pause
   (not in demo mode, not while the car is down). D_2400d8 holds the phase of the round: 1 the
   count in before the start (after two seconds the stage music starts and the voices are
   cleared), 4 game over (three seconds, then back to the title or the high score), 8 round
   over (one second, then the next stage), 0x10 fuel counted (clears when it is done), 0x20 all
   flags taken (2.5 seconds, then the fuel is counted into the score), 0x40 car lost (two
   seconds, then a new round or game over), 0x80 and 0x100 the fuel count of the last flag;
   with none of them the round is played: the pad steers the car (and Circle? uses the smoke
   boost), the engine voices follow the car's gear, a flag reached is taken and scored (the
   special flag asks for the fuel count), the fuel gauge drains and the cars spin when it is
   empty, the enemies drive after two seconds and a crash or ten flags ends the round.
   DRAFT: every path is transcribed, size 3284 vs 3388. Retail tests the sound slots with nor (~x == 0), keeps the flag loop's state test in an out of line block, and orders the if-chain on D_2400d8 with a leading zero test; the pause toggle, the music start, the flag scoring and the fuel logic match in effect but not in schedule and register use, so most words differ. */
void f_02ef14(int pad)
{
    if (!(D_2402c8 & 0x20) && (pad & 0x20)) {
        if (D_2400d8 & 0x400) {
            D_2400d8 &= ~0x400;
            f_1135b8(0, D_1d1aa4);
            f_093518(f_093330(), D_1d1aa0);
        } else if (!D_2400c3 && !(D_2400d8 & 4)) {
            D_2400d8 |= 0x400;
            f_1135b8(0, 0.0f);
            D_1d1aa0 = f_093538(f_093330());
            f_093518(f_093330(), 0.0f);
        }
    }
    int fl = D_2400d8;
    if (fl & 0x400)
        return;
    if (fl != 0) {
        if (fl & 1) {
            if (D_2400d4 > 120) {
                D_2400d8 = fl & ~1;
                f_113488(0);
                D_2400d4 = 0;
                Stage *st = &D_1d5a7c[D_27ec74];
                if (st->m4 == 1) {
                    const char *name = "BGM2";
                    int arg = D_1c0614[f_00222c(name, "RallyX_BGM")].arg;
                    f_113424(0, D_1d8cd0.f_002acc(name), arg);
                } else {
                    PlayBgmWait("BGM1");
                }
                f_1135b8(0, D_1d1aa4);
                Board *b = &D_240064;
                for (int i = 0; i < 11; i++) {
                    b->a[i] = -1;
                    b->b[i] = -1;
                }
                b->m88 = 0;
                D_2402c4 = 0;
                D_2402cc = 0;
            }
            return;
        }
        if (fl & 4) {
            D_2402d0 = D_27ec74;
            if (D_2400d4 > 180) {
                if (D_2400c3) {
                    D_2400c4 = 1;
                    D_2400d4 = 0;
                } else {
                    int next;
                    if (D_2400c2)
                        next = 5;
                    else
                        next = 0;
                    f_02dfb4(next);
                }
            }
            return;
        }
        if (fl & 8) {
            if (D_2400d4 > 60) {
                D_27ec74 = (D_27ec74 + 1) % D_1d55a8[D_27ec75];
                f_02e400();
                int next;
                if (D_1d5a7c[D_27ec74].m4 == 1)
                    next = 3;
                else
                    next = 1;
                f_02dfb4(next);
            }
            return;
        }
        if (fl & 0x10) {
            if (f_02e8e8(0))
                return;
            Board *b = &D_240064;
            int h = b->a[5];
            if (h != -1) {
                f_093448(f_093330(), h);
                b->a[5] = -1;
            }
            D_2400d4 = 0;
            D_2400d8 |= 8;
            D_2400f4 = 0;
            return;
        }
        if (fl & 0x20) {
            if (D_2400d4 > 150) {
                D_2400d4 = 0;
                D_2400d8 = fl | 0x10;
                f_02e8e8(1);
                Sfx(5);
            }
            return;
        }
        if (fl & 0x40) {
            if (D_2400d4 > 120) {
                if (D_1d1a9c > 0) {
                    f_02e704();
                } else {
                    D_2400d8 = fl | 4;
                    D_2400c4 = 1;
                    D_2400d4 = 0;
                }
            }
            return;
        }
        if (fl & 0x80) {
            if (f_02e8e8(0))
                return;
            D_2400d8 = 0;
            Board *b = &D_240064;
            int h = b->a[5];
            if (h != -1) {
                f_093448(f_093330(), h);
                b->a[5] = -1;
            }
            return;
        }
        if (fl & 0x100) {
            if (f_02e8e8(1))
                D_2400d8 = (D_2400d8 & ~0x100) | 0x80;
            else
                D_2400d8 = 0;
            return;
        }
    }
    Car *p = &D_24028c;
    if (pad & 1) {
        p->m34 = p->m32 = 0;
    } else if (pad & 2) {
        p->m34 = p->m32 = 2;
    } else if (pad & 4) {
        p->m34 = p->m32 = 3;
    } else if (pad & 8) {
        p->m34 = p->m32 = 1;
    }
    if ((pad & 0x10) && !(D_2402c8 & 0x10) && D_1d5a7c[D_27ec74].m4 != 1)
        f_0e89f4(p, &D_2400f4);
    f_0e8840(p);
    f_0e8db0(p);
    f_0e930c(p);
    Board *b = &D_240064;
    if (b->a[1] == -1)
        Sfx(1);
    if (b->a[0] == -1)
        Sfx(0);
    int gear = p->m30;
    if (gear != 0 && gear != 2) {
        if (b->a[1] != -1)
            f_093480(f_093330(), b->a[1], 0.0f);
        if (b->a[0] != -1)
            f_093480(f_093330(), b->a[0], 1.0f);
    } else {
        if (b->a[0] != -1)
            f_093480(f_093330(), b->a[0], 0.0f);
        if (b->a[1] != -1)
            f_093480(f_093330(), b->a[1], 1.0f);
    }
    Flag *f = D_27ebf4;
    for (int i = 0; i < D_1d5584; i++, f++) {
        if (f->state != 0 && f->state < 4 && f->cx == p->cx && f->cy == p->cy) {
            D_27ebf0->cell[(short)p->m8] &= 0x80;
            if (f->state == 3 && D_2400f4 > 0) {
                D_2400d8 |= 0x100;
                Sfx(3);
                Sfx(5);
                if (b->a[0] != -1) {
                    f_093448(f_093330(), b->a[0]);
                    b->a[0] = -1;
                }
                if (b->a[1] != -1) {
                    f_093448(f_093330(), b->a[1]);
                    b->a[1] = -1;
                }
            } else if (f->state == 2) {
                D_2400ec = 1;
                Sfx(4);
            } else {
                Sfx(3);
            }
            if (D_2400ec)
                D_2400e0 += (D_2400f0 + 1) * 200;
            else
                D_2400e0 += (D_2400f0 + 1) * 100;
            f->state = D_2400f0 + 4;
            D_2400f0++;
            D_2400e4++;
            break;
        }
    }
    if ((D_27ebf0->cell[(short)p->m8] & 0x7f) == 17)
        D_2400e8 = 1;
    if (D_2400f4 > 0) {
        D_2400f4 -= 7;
        if (D_2400f4 <= 0 && !D_2402cc) {
            p->dir -= 19;
            Stage *st = &D_1d5a7c[D_27ec74];
            for (int i = 0; i < st->enemies; i++)
                D_240104[i].dir += 16;
            D_2402cc = 1;
            D_2400f4 = 0;
        }
    }
    if ((D_2400f4 / 40 >> 4) < 11) {
        if (!D_2402c4) {
            Sfx(8);
            D_2402c4 = 1;
        }
    }
    if (D_2400d4 >= 120) {
        for (int i = 0; i < D_1d5a7c[D_27ec74].enemies; i++) {
            Car *c = &D_240104[i];
            if (D_1d5a7c[D_27ec74].m4 != 1 || D_2400f4 <= 0) {
                f_0e9564(c, p);
                f_0e8db0(c);
            }
            if (f_0e8d78(c, (unsigned short)p->x >> 4, (unsigned short)p->y >> 4))
                D_2400e8 = 1;
        }
    }
    if (D_2400e8) {
        if (D_1d5a7c[D_27ec74].m4 != 1) {
            D_2400d4 = 0;
            D_1d1a9c--;
            D_2400d8 |= 0x40;
        } else {
            D_2400d4 = 0;
            D_2400d8 |= 8;
        }
        f_113488(0);
        StopVoices(6);
    }
    if (D_2400e4 >= 10) {
        D_2400d4 = 0;
        D_2400d8 |= 0x20;
        f_113488(0);
        StopVoices(7);
    }
}

/* @draft 0x02fc50 us f_02fc50
   WHAT IT DOES: The demo state's update: the player's car drives itself; a flag reached is
   taken (its cell cleared, numbered by the flags taken so far); a crash cell or an enemy
   catching the car (enemies move after two seconds) ends the demo. Start begins a game (round
   start state); once the demo has ended or ten flags are taken it returns to the title in
   three seconds, and before that Select returns at once.
   Remaining difference: retail tests the flag's state with its own branch to an out of line
   block (the < 4 test precomputed) and rebuilds the player car's address there; here the two
   tests are combined with sltu/and and the address is hoisted. The rest matches. */
void f_02fc50(int pad)
{
    f_0e9820(&D_24028c, D_240104);
    f_0e8db0(&D_24028c);
    f_0e930c(&D_24028c);
    Flag *f = D_27ebf4;
    for (int i = 0; i < D_1d5584; i++, f++) {
        if (f->state != 0 && f->state < 4 && f->cx == D_24028c.cx && f->cy == D_24028c.cy) {
            D_27ebf0->cell[(short)D_24028c.m8] &= 0x80;
            f->state = D_2400f0 + 4;
            D_2400f0++;
            break;
        }
    }
    Car *p = &D_24028c;
    if ((D_27ebf0->cell[(short)p->m8] & 0x7f) == 17)
        D_2400e8 = 1;
    if (D_2400d4 >= 120) {
        for (int i = 0; i < D_1d5a7c[D_27ec74].enemies; i++) {
            Car *c = &D_240104[i];
            f_0e9564(c, p);
            f_0e8db0(c);
            if (f_0e8d78(c, (unsigned short)D_24028c.x >> 4, (unsigned short)p->y >> 4))
                D_2400e8 = 1;
        }
    }
    if (pad & 0x20) {
        f_02dfb4(2);
    } else if (D_2400e8 || D_2400f0 >= 10) {
        D_2400d0 = 180;
        D_2400cc = 0;
    } else if (pad & 0x10) {
        f_02dfb4(0);
    }
}

/* @implements 0x02fec4 us f_02fec4
   WHAT IT DOES: An empty state handler. */
void f_02fec4(void)
{
}

/* @implements 0x02fecc us f_02fecc
   WHAT IT DOES: The round start state's update: after three seconds starts play (state 1)
   and clears the remembered stage. */
void f_02fecc(int pad)
{
    if (D_2400d4 > 180) {
        f_02dfb4(1);
        D_2402d0 = 0;
    }
}

/* @implements 0x02ff08 us f_02ff08
   WHAT IT DOES: The new high score state's update: after eight seconds goes back to the
   title state. */
void f_02ff08(int pad)
{
    if (D_2400d4 > 480)
        f_02dfb4(0);
}

/* The glyph code of a digit. */
static inline int Digit(int n)
{
    return n + 16;
}

/* @implements 0x02ff40 us f_02ff40
   WHAT IT DOES: Draws the title screen (state 0): clears the 224 x 224 area in the mode's
   colour and runs the title text (the game name, the cast list of the cars and the maze
   objects; devil cars in the hidden mode, red cars otherwise) through the glyph writer, a
   frame every four ticks. When the writer has finished and no stage was chosen in stage
   select, starts a new game (state 4, the demo). */
void f_02ff40(void)
{
    f_0e7bc8(0, 0, 224, 224);
    f_0e7a10(0);
    f_0e79c8(D_2400c1 ? 0xffa0a0a0u : 0xff4797ffu);
    f_0e7a40(288, 224);
    f_0e7a54(0, 0, 0, 0);
    if (D_2400c1) {
        char t[212] = {
            61, 67, 16, 60, -1, 0, 0, 45, 36, 54, 15, 49, 32, 43, 43, 56, 13, 55, 63, 10, 61, 91, 32,
            60, -1, -1, -1, 34, 32, 50, 51, 63, 10, 61, 24, 46, 64, 63, 2, 61, 59, 56, 44, 56, 15,
            34, 32, 49, 63, 10, 61, 24, 64, 65, 63, 2, 61, 59, 72, 35, 36, 53, 40, 43, 15, 34, 32,
            49, 63, 10, 61, 24, 82, 66, 63, 2, 61, 59, 88, 34, 39, 36, 34, 42, 15, 47, 46, 40, 45,
            51, 63, 10, 61, 24, 98, 67, 63, 2, 61, 59, 104, 50, 47, 36, 34, 40, 32, 43, 15, 34, 39,
            36, 34, 42, 15, 47, 46, 40, 45, 51, 63, 10, 61, 24, 114, 68, 63, 2, 61, 59, 120, 43, 52,
            34, 42, 56, 15, 34, 39, 36, 34, 42, 15, 47, 46, 40, 45, 51, 63, 10, 61, 24, -120, 69, 63,
            2, 61, 59, -112, 49, 46, 34, 42, 15, 8, 15, 35, 32, 45, 38, 36, 49, 15, 1, 15, 9, 63, 10,
            61, 24, -96, 70, 63, 10, 61, 59, -88, 50, 44, 46, 42, 36, 15, 50, 34, 49, 36, 36, 45, 63,
            10, 61, 89, -57, 71, 72, 73, 74, 75, 63, 30, 62
        };
        if (f_0e7db0(t, D_2400d4 / 4, D_2400c1))
            return;
    } else {
        char t[210] = {
            61, 67, 16, 60, -1, 0, 0, 45, 36, 54, 15, 49, 32, 43, 43, 56, 13, 55, 63, 10, 61, 91, 32,
            60, -1, -1, -1, 34, 32, 50, 51, 63, 10, 61, 24, 46, 64, 63, 2, 61, 59, 56, 44, 56, 15,
            34, 32, 49, 63, 10, 61, 24, 64, 65, 63, 2, 61, 59, 72, 49, 36, 35, 15, 34, 32, 49, 63,
            10, 61, 24, 82, 66, 63, 2, 61, 59, 88, 34, 39, 36, 34, 42, 15, 47, 46, 40, 45, 51, 63,
            10, 61, 24, 98, 67, 63, 2, 61, 59, 104, 50, 47, 36, 34, 40, 32, 43, 15, 34, 39, 36, 34,
            42, 15, 47, 46, 40, 45, 51, 63, 10, 61, 24, 114, 68, 63, 2, 61, 59, 120, 43, 52, 34, 42,
            56, 15, 34, 39, 36, 34, 42, 15, 47, 46, 40, 45, 51, 63, 10, 61, 24, -120, 69, 63, 2, 61,
            59, -112, 49, 46, 34, 42, 15, 8, 15, 35, 32, 45, 38, 36, 49, 15, 1, 15, 9, 63, 10, 61,
            24, -96, 70, 63, 10, 61, 59, -88, 50, 44, 46, 42, 36, 15, 50, 34, 49, 36, 36, 45, 63, 10,
            61, 89, -57, 71, 72, 73, 74, 75, 63, 30, 62
        };
        if (f_0e7db0(t, D_2400d4 / 4, D_2400c1))
            return;
    }
    if (!D_1d1a90) {
        f_02e380();
        f_02dfb4(4);
    }
}

/* @implements 0x030148 us f_030148
   WHAT IT DOES: Draws the round start screen (state 2): clears the 224 x 224 area to black and
   lists the extra life awards ("1ST BONUS FOR 20000 PTS", "2ND BONUS FOR 80000 PTS") and, in
   blue, the copyright lines at the bottom. */
void f_030148(void)
{
    char bonus[9] = { 33, 46, 45, 52, 50, 15, 37, 46, 49 };
    char pts[3] = { 47, 51, 50 };
    char copyright[27] = { 59, 15, 17, 25, 24, 16, 15, 17, 25, 24, 17, 15, 18, 16, 16, 20, 15, 45,
                           32, 44, 34, 46, 15, 43, 51, 35, 14 };
    char rights[20] = { 32, 43, 43, 15, 49, 40, 38, 39, 51, 50, 15, 49, 36, 50, 36, 49, 53, 36, 35, 14 };
    f_0e7bc8(0, 0, 224, 224);
    f_0e7a10(0);
    f_0e79c8(0xff000000u);
    f_0e7a40(288, 224);
    f_0e7a54(0, 0, 0, 0);
    static const int bonusPoints[2] = { 20000, 80000 };
    f_0e7c4c(23, 98, "\021" "23", 3, 0xffffffffu);
    f_0e7c4c(23, 114, "\022-#", 3, 0xffffffffu);
    f_0e7c4c(55, 98, bonus, 9, 0xffffffffu);
    f_0e7c4c(55, 114, bonus, 9, 0xffffffffu);
    f_0e7cf4(181, 98, bonusPoints[0], 0xffffffffu);
    f_0e7cf4(181, 114, bonusPoints[1], 0xffffffffu);
    f_0e7c4c(191, 98, pts, 3, 0xffffffffu);
    f_0e7c4c(191, 114, pts, 3, 0xffffffffu);
    f_0e7c4c(10, 186, copyright, 27, 0xff0000ffu);
    f_0e7c4c(27, 202, rights, 20, 0xff0000ffu);
}

/* @implements 0x0304a0 us f_0304a0
   WHAT IT DOES: Draws the new high score screen (state 5): clears the area to dark red and
   writes "YOU DID IT !!" and "THE HIGH SCORE OF THE DAY." in blue; the score itself
   blinks (shown for 30 ticks of every 61), right aligned as glyph digits behind a marker
   glyph; below it "GO FOR THE WORLD RECORD NOW !!" in yellow. */
void f_0304a0(void)
{
    f_0e7bc8(0, 0, 224, 224);
    f_0e7a10(0);
    f_0e79c8(0xff940000u);
    f_0e7a40(288, 224);
    f_0e7a54(0, 0, 0, 0);
    char didIt[13] = { 56, 46, 52, 15, 35, 40, 35, 15, 40, 51, 15, 1, 1 };
    f_0e7c4c(64, 48, didIt, 13, 0xff0000ffu);
    char theHigh[14] = { 51, 39, 36, 15, 39, 40, 38, 39, 15, 50, 34, 46, 49, 36 };
    f_0e7c4c(52, 80, theHigh, 14, 0xff000000u);
    char ofTheDay[11] = { 46, 37, 15, 51, 39, 36, 15, 35, 32, 56, 14 };
    f_0e7c4c(76, 96, ofTheDay, 11, 0xff000000u);
    if (D_2400d4 % 61 < 30) {
        unsigned char buf[64];
        unsigned char i = 62;
        unsigned char n = 1;
        unsigned int v = D_2400e0;
        buf[63] = 2;
        if (v != 0) {
            do {
                buf[i--] = v % 10 + 16;
                n++;
                v /= 10;
            } while (v != 0);
        }
        buf[i] = 2;
        n++;
        f_0e7c4c(112 - n * 4, 120, (const char *)&buf[i], n, 0xff0000ffu);
    }
    char goFor[16] = { 38, 46, 15, 37, 46, 49, 15, 51, 39, 36, 15, 54, 46, 49, 43, 35 };
    f_0e7c4c(52, 144, goFor, 16, 0xff00ffffu);
    char record[13] = { 49, 36, 34, 46, 49, 35, 15, 45, 46, 54, 15, 1, 1 };
    f_0e7c4c(68, 160, record, 13, 0xff00ffffu);
}

/* @implements 0x0308cc us f_0308cc
   WHAT IT DOES: Draws the stage intro (state 3): clears the 224 x 224 screen area in the
   mode's colour and runs the intro text through the glyph writer, a frame every four ticks.
   The message names the stage ("CHALLENGING STAGE NO." the round number, the stage's two
   counts) and says that the red cars (devil cars in the hidden mode) do not move until the
   fuel runs out. When the writer has finished the text, play starts (state 1). */
void f_0308cc(void)
{
    f_0e7bc8(0, 0, 224, 224);
    f_0e7a10(0);
    f_0e79c8(D_2400c1 ? 0xffa0a0a0u : 0xff4797ffu);
    f_0e7a40(288, 224);
    f_0e7a54(0, 0, 0, 0);
    int round;
    if (D_2400c1) {
        int s = D_27ec74;
        round = 1;
        if (s != 2) {
            int h = s != 8;
            round = h + 2;
        }
    } else {
        int s = D_27ec74;
        round = 1;
        if (s >= 3)
            round = (s - 6) / 4 + 2;
    }
    if (D_2400c1) {
        char text[119] = {
            61, 36, 40, 60, -1, 0, 0,
            34, 39, 32, 43, 43, 36, 45, 38, 40, 45, 38, 15, 50, 51, 32, 38, 36, /* CHALLENGING STAGE */
            63, 2, 61, 92, 63, 60, -1, -1, -1,
            45, 46, 14, round + 16, /* NO. */
            63, 2, 61, 83, 88, 69,
            63, 2, 61, 116, 96, 29, 15, Digit(D_1d5a7c[D_27ec74].m10),
            63, 2, 61, 83, 123, 65,
            63, 2, 61, 116, -128, 29, 15, Digit(D_1d5a7c[D_27ec74].enemies),
            63, 2, 61, 36, -104,
            35, 36, 53, 40, 43, 15, 34, 32, 49, 50, 15, 35, 46, 45, 7, 51, 15, 44, 46, 53, 36, /* DEVIL CARS DON'T MOVE */
            63, 2, 61, 28, -89,
            52, 45, 51, 40, 43, 15, 37, 52, 36, 43, 15, 49, 52, 45, 50, 15, 46, 52, 51, 14, /* UNTIL FUEL RUNS OUT. */
            63, 30, 62
        };
        if (f_0e7db0(text, D_2400d4 / 4, D_2400c1))
            return;
        f_02dfb4(1);
    } else {
        char text[117] = {
            61, 36, 40, 60, -1, 0, 0,
            34, 39, 32, 43, 43, 36, 45, 38, 40, 45, 38, 15, 50, 51, 32, 38, 36, /* CHALLENGING STAGE */
            63, 2, 61, 92, 63, 60, -1, -1, -1,
            45, 46, 14, round + 16, /* NO. */
            63, 2, 61, 83, 88, 69,
            63, 2, 61, 116, 96, 29, 15, Digit(D_1d5a7c[D_27ec74].m10),
            63, 2, 61, 83, 123, 65,
            63, 2, 61, 116, -128, 29, 15, Digit(D_1d5a7c[D_27ec74].enemies),
            63, 2, 61, 36, -104,
            49, 36, 35, 15, 34, 32, 49, 50, 15, 35, 46, 45, 7, 51, 15, 44, 46, 53, 36, /* RED CARS DON'T MOVE */
            63, 2, 61, 28, -89,
            52, 45, 51, 40, 43, 15, 37, 52, 36, 43, 15, 49, 52, 45, 50, 15, 46, 52, 51, 14, /* UNTIL FUEL RUNS OUT. */
            63, 30, 62
        };
        if (f_0e7db0(text, D_2400d4 / 4, D_2400c1))
            return;
        f_02dfb4(1);
    }
}

/* The texts of the draw handlers in glyph codes, without terminators. */
static const char D_game[4] = { 38, 32, 44, 36 };
static const char D_over[4] = { 46, 53, 36, 49 };
static const char D_pause[5] = { 47, 32, 52, 50, 36 };
static const char D_hiScoreA[8] = { 39, 40, 13, 50, 34, 46, 49, 36 };
static const char D_round[5] = { 49, 46, 52, 45, 35 };

/* @draft 0x031094 us f_031094
   WHAT IT DOES: Draws the maze (play and demo states): clears the 224 x 224 area in the
   mode's colour, scrolls the view to the player's car (the 12 x 12 cells around it, 24 units
   a cell, each wall tile in the maze's colour, the rest white), draws the flags in view
   (taken flags that have scrolled out of view are cleared), then the enemy cars, and the
   player's car in the middle of the view (the crash picture after a crash). Over the maze it
   writes GAME OVER when the game is over, or the blinking PAUSE when paused.
   DRAFT: size 1184 vs 1196. The maze loops match in structure; retail loads the car's m12 first and the flag test as a plain lb with an out of line block (the window test written as one chain with the state reloaded), keeps the inner loop's guard in a stack slot, and builds the player's crash picture arguments in registers; here they go through the stack. */
void f_031094(void)
{
    f_0e7bc8(0, 0, 224, 224);
    f_0e7a10(0);
    f_0e79c8(D_2400c1 ? 0xffa0a0a0u : 0xff4797ffu);
    f_0e7a40(224, 224);
    f_0e7a54(0, 0, 0, 0);
    Car *p = &D_24028c;
    unsigned short sx = ((unsigned short)p->x + p->m10) >> 4;
    unsigned short sy = ((unsigned short)p->y + p->m12) >> 4;
    unsigned short col = sx / 24;
    unsigned short row = sy / 24;
    int ox = sx - 100;
    int oy = sy - 100;
    short x0 = -32 - (sx - col * 24);
    short y0 = -32 - (sy - row * 24);
    f_0e7a10(1);
    f_0e7a40(24, 24);
    short y = y0;
    for (int r = row - 6; r < row + 6; r++) {
        short x = x0;
        for (int c = col - 6; c < col + 6; c++) {
            int t = f_0e842c(c, r);
            if ((unsigned)(t - 1) < 19) {
                unsigned int color = 0xffffffffu;
                if ((unsigned)(t - 1) < 16) {
                    color = 0xff808080u;
                    if (!D_2400c1) {
                        unsigned int w = 0;
                        if (D_27ebf0)
                            w = D_27ebf0->wallColor;
                        color = w;
                    }
                }
                f_0e79c8(color);
                int u, v;
                f_0e821c(t, &u, &v);
                f_0e7a54(x, y, u, v);
            }
            x += 24;
        }
        y += 24;
    }
    f_0e79c8(0xffffffffu);
    Flag *f = D_27ebf4;
    for (int i = 0; i < D_1d5584; i++, f++) {
        if (f->state == 0)
            continue;
        if (f->cx < col - 6 || col + 6 < f->cx || f->cy < row - 6 || row + 6 < f->cy) {
            if (f->state >= 4)
                f->state = 0;
        } else {
            f_0e814c(f->cx * 24 - ox + 12, f->cy * 24 - oy + 12, f->state, D_2400ec);
        }
    }
    for (int i = 0; i < D_1d5a7c[D_27ec74].enemies; i++) {
        Car *c = &D_240104[i];
        int u, v;
        f_0e8344(c->m28 >> 4, &u, &v, D_2400c1);
        f_0e7a54((unsigned short)c->x / 16 - ox, (unsigned short)c->y / 16 - oy, u, v);
    }
    int u, v;
    if (D_2400e8) {
        u = 192;
        v = 96;
    } else {
        f_0e82c4(p->m28 >> 4, &u, &v);
    }
    f_0e7a54(100, 100, u, v);
    if (D_2400d8 & 4) {
        f_0e7c4c(96, 104, D_game, 4, 0xffffffffu);
        f_0e7c4c(96, 112, D_over, 4, 0xffffffffu);
    } else if (D_2400d8 & 0x400) {
        if (f_0e7c38()) {
            f_0e7c4c(92, 108, D_pause, 5, 0xffffffffu);
        }
    }
}

/* @implements 0x031540 us f_031540
   WHAT IT DOES: Draws the side panel of the title, demo and high score states: clears the
   64 x 224 strip right of the maze, writes "HI-SCORE" with the mode's high score below it,
   and, when a stage was chosen in stage select, "ROUND" with the stage's number. */
void f_031540(void)
{
    f_0e7bc8(224, 0, 64, 224);
    f_0e7a10(0);
    f_0e79c8(0xff000000u);
    f_0e7a40(64, 224);
    f_0e7a54(224, 0, 0, 0);
    f_0e7c4c(224, 0, D_hiScoreA, 8, 0xffffffffu);
    f_0e7cf4(288, 8, D_1d1a94[D_2400c1], 0xff0000ffu);
    if (D_1d1a90) {
        f_0e7c4c(224, 207, D_round, 5, 0xffffffffu);
        f_0e7cf4(288, 207, D_27ec74 + 1, 0xffffffffu);
    }
}

static const char D_hiScoreB[8] = { 39, 40, 13, 50, 34, 46, 49, 36 };
static const char D_score[5] = { 50, 34, 46, 49, 36 };

/* @draft 0x031634 us f_031634
   WHAT IT DOES: Draws the side panel of the play states: clears the 64 x 224 strip, draws the
   radar (a 64 x 112 box with a blue dot for each enemy car, a blinking yellow dot for the
   player's car, a yellow dot for each flag waiting and a blinking one for the special flag),
   the fuel gauge (a bar that is blue when low) and the texts "HI-SCORE" with the high score,
   "SCORE" with the score (rounded down to tens), "ROUND" with the stage number, the spare
   cars, and GAME OVER over the strip when the game is over.
   DRAFT: size 1112 vs 1120. Retail picks the fuel bar colour with a branch (lui/ori in the slot) and the special flag's blink colour as (cond & k) - k with the opposite sense, saves five registers (s0 to s4) where this form uses s5 too, and steps the flag loop's index after reloading the flag count. */
void f_031634(void)
{
    f_0e7bc8(224, 0, 64, 224);
    f_0e7a10(0);
    f_0e79c8(0xff000000u);
    f_0e7a40(64, 224);
    f_0e7a54(224, 0, 0, 0);
    f_0e79c8(0xff944a25u);
    f_0e7a40(64, 112);
    f_0e7a54(224, 80, 0, 0);
    f_0e7a40(2, 2);
    f_0e79c8(0xff0000ffu);
    for (int i = 0; i < D_1d5a7c[D_27ec74].enemies; i++) {
        Car *c = &D_240104[i];
        f_0e7a54(c->cx * 2 + 224, c->cy * 2 + 80, 0, 0);
    }
    f_0e79c8(f_0e7c38() ? 0xff000000u : 0xff00ffffu);
    f_0e7a54(D_24028c.cx * 2 + 224, D_24028c.cy * 2 + 80, 0, 0);
    Flag *f = D_27ebf4;
    for (int i = 0; i < D_1d5584; i++, f++) {
        if (f->state == 0)
            continue;
        if (f->state >= 4)
            continue;
        unsigned int color = 0xff00ffffu;
        if (f->state == 2)
            color = f_0e7c38() ? 0u : 0xff00ffffu;
        f_0e79c8(color);
        f_0e7a54(f->cx * 2 + 224, f->cy * 2 + 80, 0, 0);
    }
    f_0e7a10(1);
    f_0e79c8(0xffffffffu);
    f_0e7a40(64, 8);
    f_0e7a54(224, 57, 129, 248);
    int level = D_2400f4 / 40 >> 4;
    f_0e7a10(0);
    f_0e79c8(level < 11 ? 0xff0000ffu : 0xff00ffffu);
    f_0e7a40(level, 6);
    f_0e7a54(286 - level, 66, 0, 0);
    f_0e7c4c(224, 0, D_hiScoreB, 8, 0xffffffffu);
    f_0e7cf4(288, 8, D_1d1a94[D_2400c1], 0xff0000ffu);
    f_0e7c4c(224, 16, D_score, 5, 0xffffffffu);
    f_0e7cf4(288, 24, D_2400e0 / 10 * 10, 0xffde9400u);
    f_0e7c4c(224, 207, D_round, 5, 0xffffffffu);
    f_0e7cf4(288, 207, D_27ec74 + 1, 0xffffffffu);
    f_0e79c8(0xffffffffu);
    f_0e7a40(18, 11);
    int x = 224;
    for (int i = 0; i < D_1d1a9c - 1; i++) {
        f_0e7a54(x, 192, 237, 0);
        x += 14;
    }
    if (D_2400d8 & 4) {
        f_0e7c4c(96, 104, D_game, 4, 0xffffffffu);
        f_0e7c4c(96, 112, D_over, 4, 0xffffffffu);
    }
}

/* @implements 0x031a94 us f_031a94
   WHAT IT DOES: Steps the sound effect queue: starts the effect at the head of the queue if
   no voice plays it yet, and once it plays, drops it from the queue; then frees the voices
   whose effect has ended. */
void f_031a94(Board *b)
{
    int busy = b->m88 != 0;
    if (b->b[0] == -1) {
        b->m88 = 0;
        busy = 0;
    }
    if (busy) {
        if (b->a[b->b[0]] == -1)
            b->a[b->b[0]] = f_0933f8(f_093330(), b->b[0]);
        if (b->a[b->b[0]] != -1) {
            int n = --b->m88;
            for (int i = 0; i < n; i++)
                b->b[i] = b->b[i + 1];
        }
    }
    for (int i = 0; i < 11; i++) {
        if (b->a[i] != -1) {
            if (f_09349c(f_093330(), b->a[i]))
                b->a[i] = -1;
        }
    }
}
