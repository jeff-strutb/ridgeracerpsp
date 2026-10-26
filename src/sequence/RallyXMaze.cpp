/* The Rally-X maze helpers (retail 0x0e821c to 0x0e8840): the HUD slot positions of the
   stage markers and the score digits, the maze cell lookups the cars use, the smoke clearing,
   and the maze generator that places the flags and the fuel cells on the 32 x 56 grid. */

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

/* A maze: its header, then the cell kinds from offset 88 on (32 cells per row, 56 rows). */
struct Map {
    short m0[2];
    short startX, startY;
    short m8[28];
    short enemyStart[8];
    short m80[4];
    unsigned char cell[1792];
};

/* A flag in the maze: its state, its cell and the cell's column and row. */
struct Flag {
    signed char state;
    char m1;
    short cell;
    short cx, cy;
};

extern "C" {
extern Map *D_27ebf0;
extern Stage *D_1d5a7c;
extern signed char D_27ec74;
extern int D_1d5584;
extern Flag D_27ebf4[];
extern int D_27ebd4;
}

extern "C" {

/* @draft 0x0e821c us f_0e821c
   WHAT IT DOES: Gives the slot position of a number n on the 19-slot HUD row: slot 19 is the
   current stage's marker (its start column, row 120); any other slot is laid out as a 10-wide
   grid of 24-unit cells from row 72. */
void f_0e821c(int n, int *px, int *py)
{
    int v = n - 1;
    if (n == 19) {
        Stage *s = &D_1d5a7c[D_27ec74];
        *px = 24 * s->m0;
        *py = 120;
        return;
    }
    int q = v / 10;
    int r = v % 10;
    *px = 24 * r;
    *py = 24 * q + 72;
}

/* @draft 0x0e82c4 us f_0e82c4
   WHAT IT DOES: Lays out a count n in a 12-slot ring: the remainder after dividing by 3
   twelve at a time, then the tens of that remainder, each as a 24-unit step, the first for x
   and the second for y. */
void f_0e82c4(int n, int *px, int *py)
{
    int t = n % 12;
    int q = t / 10;
    int r = t - q * 10;
    *px = 24 * r;
    *py = 24 * q;
}

/* @draft 0x0e8344 us f_0e8344
   WHAT IT DOES: The same slot layout as f_0e82c4 with two variants: when flag is set, x is the
   remainder of the tens and y is the tens plus 168; when clear, x is the remainder of the
   tens of n + 2 and y is the eighths plus 24. */
void f_0e8344(int n, int *px, int *py, int flag)
{
    int t = n % 12;
    if (flag) {
        int q = t / 10;
        int r = t - q * 10;
        *px = 24 * r;
        *py = 24 * q + 168;
    } else {
        int u = t + 2;
        int q = u / 10;
        int r = u - q * 10;
        *px = 24 * r;
        *py = 24 * (t / 8) + 24;
    }
}

/* @draft 0x0e842c us f_0e842c
   WHAT IT DOES: The maze cell kind at (x, y) with bit 7 masked off (the car-occupied mark);
   a point off the 32 x 56 grid is the maze edge, kind 19. */
unsigned char f_0e842c(int x, int y)
{
    unsigned char r;
    r = 19;
    if (x >= 0) {
        if (x < 32) {
            if (y >= 0) {
                if (y < 56) {
                    r = D_27ebf0->cell[y * 32 + x] & 0x7f;
                }
            }
        }
    }
    return r;
}

/* @draft 0x0e8470 us f_0e8470
   WHAT IT DOES: The maze cell byte at (x, y) as stored, with its car-occupied bit; a point off
   the grid is the maze edge, kind 19. */
unsigned char f_0e8470(int x, int y) throw()
{
    unsigned char r = 19;
    if (x >= 0) {
        if (x < 32) {
            if (y >= 0) {
                if (y < 56) {
                    r = D_27ebf0->cell[y * 32 + x];
                }
            }
        }
    }
    return r;
}

/* @implements 0x0e84b0 us f_0e84b0
   WHAT IT DOES: Clears the cells that hold a smoke screen (kind 18) or a set car-occupied bit
   (bit 7) across the whole 32 x 56 grid, so no stale smoke or car mark survives a new maze. */
void f_0e84b0(void)
{
    for (int i = 0; i < 1792; i++) {
        if ((D_27ebf0->cell[i] & 0x7f) == 18) {
            D_27ebf0->cell[i] = 0;
        } else if ((signed char)D_27ebf0->cell[i] < 0) {
            D_27ebf0->cell[i] = 0;
        }
    }
}

/* @draft 0x0e84fc us f_0e84fc
   WHAT IT DOES: Builds a new maze's cell marks: clears the bit 7 mark of the sixteen start
   cells, then places the round's flags on random free start cells (each flag's cell, column
   and row; the first two get states 2 and 3, the rest 1) and marks their cells, then places
   the enemy crash marks from the twelve enemy start cells of the stage. */
void f_0e84fc(void *map)
{
    int used[16];
    for (int i = 0; i < 16; i++) {
        short c = D_27ebf0->m8[i];
        D_27ebf0->cell[c] &= 0x80;
        used[i] = 1;
    }
    int count = D_1d5584;
    if (count > 0) {
        for (int k = 0; k < count; k++) {
            Flag *f = &D_27ebf4[k];
            if (k == 0) {
                f->state = 2;
            } else if (k == 1) {
                f->state = 3;
            } else {
                f->state = 1;
            }
            unsigned int s = (unsigned int)D_27ebd4 * 0x19660d + 0x3c6ef35f;
            D_27ebd4 = (int)s;
            int r = (s >> 1) % 16;
            while (used[r] == 0) {
                r = (r + 1) % 16;
            }
            short c = D_27ebf0->m8[r];
            f->cell = c;
            f->cx = c % 32;
            f->cy = c / 32;
            D_27ebf0->cell[c] = (D_27ebf0->cell[c] & 0x80) | 0x14;
            used[r] = 0;
        }
    }
    for (int i = 0; i < 12; i++) {
        short c = D_27ebf0->m8[16 + i];
        D_27ebf0->cell[c] &= 0x80;
        used[i] = 1;
    }
    for (int k = 0; k < D_1d5a7c[D_27ec74].m10; k++) {
        unsigned int s = (unsigned int)D_27ebd4 * 0x19660d + 0x3c6ef35f;
        D_27ebd4 = (int)s;
        int r = (s >> 1) % 12;
        while (used[r] == 0) {
            r = (r + 1) % 12;
        }
        short c = D_27ebf0->m8[16 + r];
        D_27ebf0->cell[c] = (D_27ebf0->cell[c] & 0x80) | 0x11;
        used[r] = 0;
    }
}

}
