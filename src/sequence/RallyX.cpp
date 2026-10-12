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
