/* The Rally-X mini game object file (retail 0x02dfb4 to 0x031b98), played while the race
   loads. A small state machine (title, play, round start, round clear, demo, game over) runs
   the game: the player's car and up to seven enemy cars drive a 32 x 32 cell maze, the player
   collects flags against a fuel gauge, and the score, high score and lives are drawn with the
   2D sprite helpers at 0x0e79c8 on. Each state has entry, update, exit and two draw handlers
   in a table; the music cues come from the RallyX_BGM package. */

extern "C" {
int f_00222c(const char *name, const char *package);
int f_113424(int ch, void *data, int arg);
void f_113488(int ch);
void f_1135b8(int ch, float volume);
void *f_093330(void);
void f_0933f8(void *snd, int se);
void f_093448(void *snd);
void f_093464(void *snd);
void f_093480(void *snd);
void f_09349c(void *snd);
void f_0934d4(void *snd);
void f_0934f8(void *snd);
void f_093518(void *snd, float volume);
float f_093538(void *snd);
void f_0e84b0(void);
void f_0e84fc(void *map);
void f_0e7c20(void);
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
};

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
   remembered gauge and the final score. */
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

extern "C" void f_031a94(Board *b);

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
