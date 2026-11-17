/* The Rally-X mini game's cars (retail 0x0e8840 to 0x0e9dc0): turning at cell centres,
   driving and sliding along walls, the smoke screen, the player's autopilot that runs from
   the nearest enemy, and the enemy drivers, which steer towards a cell near the player (its
   own cell, or a cell ahead of or behind it on its trail). Directions are 0 up, 1 right,
   2 down, 3 left; positions are in maze units, 384 (24 steps of 16) per cell. The maze cell
   kinds: 1 to 16 walls, 17 a crash cell, 18 smoke, 19 the maze edge; bit 7 marks a cell an
   enemy car is in. */

struct Car;

extern "C" {
unsigned char f_0e8470(int x, int y) throw();
unsigned char f_0e842c(int x, int y);
void *f_093330(void);
int f_0933f8(void *snd, int se);

void f_0e8840(Car *c);
int f_0e8930(Car *c);
void f_0e89f4(Car *c, int *score);
int f_0e8a24(Car *c, int x, int y);
int f_0e8ac8(Car *c);
void f_0e8c58(Car *c);
int f_0e8d78(Car *c, int x, int y);
void f_0e8db0(Car *c);
void f_0e930c(Car *c);
void f_0e9564(Car *c, Car *player);
void f_0e95c4(Car *t, Car *c);
void f_0e9604(Car *t, Car *c);
void f_0e96a0(Car *t, Car *c);
void f_0e973c(Car *t, Car *c);
void f_0e9784(Car *t, Car *c);
void f_0e9820(Car *c, Car *enemy);
void f_0e98e8(Car *t, int ax, int ay, int bx, int by, Car *c);
void f_0e9bf0(Car *c, short tx, short ty);
}

/* A car in the maze (56 bytes). */
struct Car {
    short x, y;          /* position in maze units */
    short cx, cy;        /* cell */
    short cell;          /* cy * 32 + cx */
    short slideX;        /* drift while driving vertically */
    short slideY;        /* drift while driving horizontally */
    short trail[7];      /* the cells last visited, newest first */
    short angle;         /* drawn heading, 16 per step, 192 a full turn */
    short dir;
    short want;          /* the turn asked for, -1 none */
    short turn;          /* the steering held this frame, -1 none */
    short smoke;         /* smoke screens left */
    short speed;
    short enemy;
    short spin;          /* frames spun out after a crash or smoke */
    char moved;          /* entered a new cell this frame */
    char p45[3];
    void (*think)(Car *target, Car *self);
    short thought;       /* the cell the driver last ran in */
    short p54;
};

/* A maze: its cells' kinds after the header. */
struct Map {
    char p0[88];
    unsigned char cell[1024];
};

extern int D_1d5588[4];  /* each direction's cell step in x */
extern int D_1d5598[4];  /* and in y */
extern Map *D_27ebf0;

/* @implements 0x0e8840 us f_0e8840
   WHAT IT DOES: Takes the turn asked for once the car is at its cell centre and the next
   cell that way is open, lining the car up on the new axis; a turn back to the same
   direction, or asked while the car is entering a cell, is dropped.
   DRAFT: block order differs: retail keeps the want = -1 return on the fall-through and the turn path out of line; three spellings tried, all laid out the same way.
   MATCHED: source stores dir before want (sched1 issues them want, dir), so the turn tail no
   longer ends in a want = -1 store that crossjump merged with the early returns. */
void f_0e8840(Car *c)
{
    if (c->dir == c->want) {
        c->want = -1;
        return;
    }
    if (c->moved) {
        c->want = -1;
        return;
    }
    if (c->want == -1)
        return;
    if (!f_0e8930(c))
        return;
    if (!f_0e8a24(c, c->cx + D_1d5588[c->want], c->cy + D_1d5598[c->want]))
        return;
    unsigned short w = c->want;
    if (w & 1)
        c->x = c->cx * 384 + 192;
    else
        c->y = c->cy * 384 + 192;
    c->dir = w;
    c->want = -1;
}

/* @implements 0x0e8930 us f_0e8930
   WHAT IT DOES: Whether the car is near enough its cell's centre across its direction of
   travel to turn (steps 9 to 13 heading up or left, 11 to 15 heading down or right). */
int f_0e8930(Car *c)
{
    int lo = 11;
    int hi = 13;
    unsigned short p;

    if (c->dir & 1) {
        p = ((unsigned short)c->x >> 4) % 24;
        if (c->dir == 3)
            lo = 9;
        else
            hi = 15;
        return (p >= lo) & (p <= hi);
    }
    unsigned short q = ((unsigned short)c->y >> 4) % 24;
    if (c->dir == 0)
        lo = 9;
    else
        hi = 15;
    return (q >= lo) & (q <= hi);
}

/* @implements 0x0e89f4 us f_0e89f4
   WHAT IT DOES: Buys three smoke screens for 640 points once the car has none left. */
void f_0e89f4(Car *c, int *score)
{
    if (c->smoke == 0 && *score > 640) {
        c->smoke = 3;
        *score -= 640;
    }
}

/* @draft 0x0e8a24 us f_0e8a24
   WHAT IT DOES: Whether the car may drive into a cell: never a wall or the maze edge, and
   for an enemy not a cell another enemy is in, nor a crash cell.
   DRAFT: the result register differs: retail sets a3 = 1 on the fall-through after a branchy 17/19 test; four spellings came out as setcc or used an extra copy register.
   2026-11-16: retail's a3 is the return-value pseudo itself (no r copy) and its 17/19 test is
   an or of two seq; direct 'return 0/1' with 'if (k == 19 || k == 17) return 0;' gives both
   (37 -> 28 words). Remaining difference: ifcvt turns the trailing 'return 0; return 1;'
   pairs into sltiu/sltu a3 (retail keeps bnez + li a3,1 in the delay slot), and the prologue
   issues move v0,a1 before sw s0 and a second move a0,v0 after the call. */
int f_0e8a24(Car *c, int x, int y)
{
    unsigned char k = f_0e8470(x, y);

    if (c->enemy) {
        if ((signed char)k < 0)
            return 0;
        k &= 0x7f;
        if ((unsigned char)(k - 1) < 16)
            return 0;
        if (k == 19 || k == 17)
            return 0;
        return 1;
    } else {
        if ((unsigned char)(k - 1) < 16)
            return 0;
        if (k == 19)
            return 0;
        return 1;
    }
}

/* @draft 0x0e8ac8 us f_0e8ac8
   WHAT IT DOES: Centres the car across its direction of travel and looks at the cell it is
   driving into: 0 if it may enter it, otherwise that cell's kind.
   DRAFT: registers and scheduling differ: retail re-zero-extends x and y (andi 0xffff) and holds cx in s1 and cy in s0; three local-type variants tried.
   2026-11-16: retail calls f_0e8470 on the fall-through after the f_0e8a24 test (bnez to the
   return-0 tail); here the call is out of line. Tried 'if (!f_0e8a24(..)) return f_0e8470(..);
   return 0;': output identical (93 words), so the layout is decided after expand (bb-reorder),
   not by the source's branch sense; reverted. */
int f_0e8ac8(Car *c)
{
    unsigned int x = (unsigned short)c->x;
    unsigned int y = (unsigned short)c->y;
    int cx = c->cx;
    int cy = c->cy;
    int hx = ((unsigned short)x >> 4) / 12 & 1;
    int hy = ((unsigned short)y >> 4) / 12 & 1;
    int r;

    r = (unsigned short)(((unsigned short)x >> 4) % 24) - 12;
    if (r != 0) {
        if (c->dir == 0 || c->dir == 2)
            c->x = x - r * 16;
        else if (hx)
            cx += c->dir == 1;
        else if (c->dir == 3)
            cx--;
    }
    r = (unsigned short)(((unsigned short)y >> 4) % 24) - 12;
    if (r != 0) {
        if (c->dir == 3 || c->dir == 1)
            c->y = y - r * 16;
        else if (hy)
            cy += c->dir == 2;
        else if (c->dir == 0)
            cy--;
    }
    if (f_0e8a24(c, cx, cy))
        return 0;
    return f_0e8470(cx, cy);
}

/* @draft 0x0e8c58 us f_0e8c58
   WHAT IT DOES: Turns a blocked car: right if that way is open, else left, else back.
   DRAFT: not tuned yet (68 of 72 words differ, same size).
   2026-11-16: retail never reloads dir after the call: 7 saved regs, s0 = seh of the first
   new dir, s4 = seh of the second, each 'sh' stores the unextended %4 result (so the store is
   'c->dir = expr' and the index is CSE'd from it). Tried one 'short d' for both turns
   (c->dir = d): body order matches retail but one pseudo serves both turns (6 saved regs, sh of
   the seh'd value), 68 -> 71 words; reverted. Implied next shape: 'c->dir = (c->dir + 1) % 4;
   short d = c->dir;' then 'c->dir = (d + 2) % 4; short d2 = c->dir;' and '(d2 + 3) % 4'. */
void f_0e8c58(Car *c)
{
    short cx = c->cx;
    short cy = c->cy;

    c->dir = (c->dir + 1) % 4;
    if (f_0e8a24(c, cx + D_1d5588[c->dir], cy + D_1d5598[c->dir]))
        return;
    c->dir = (c->dir + 2) % 4;
    if (f_0e8a24(c, cx + D_1d5588[c->dir], cy + D_1d5598[c->dir]))
        return;
    c->dir = (c->dir + 3) % 4;
}

/* @implements 0x0e8d78 us f_0e8d78
   WHAT IT DOES: Whether the car is within 12 steps of a point on both axes (a catch). */
int f_0e8d78(Car *c, int x, int y)
{
    int dx = ((unsigned short)c->x >> 4) - x;
    int dy = ((unsigned short)c->y >> 4) - y;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    return dx < 12 && dy < 12;
}

/* @draft 0x0e8db0 us f_0e8db0
   WHAT IT DOES: Moves a car one frame: a spun out car turns on the spot for 70 frames;
   otherwise its drawn heading turns towards its direction, it drives (7/8 speed across),
   drifts with the steering held, centres itself and turns away from a blocked cell, and
   updates its cell and trail. An enemy marks the cell it is in and spins out on smoke or a
   crash cell.
   DRAFT: not tuned yet (1344 vs 1372 bytes); the control flow follows retail.
   2026-11-16: retail keeps the spin >= 71 code on the fall-through (bnezl to the out-of-line
   spin < 71 return block); writing 'if (c->spin >= 71) {..} else {..; return;}' gives that
   (328 -> 184 words). Remaining from the top: retail forms the enemy cell address as
   base + cell + 80 then lbu/sb 8(v1) (here one 88 offset), loads spin with lh a2 (here lhu
   a1 kept for spin++), and the body is still 28 bytes longer. */
void f_0e8db0(Car *c)
{
    short hit;

    if (c->enemy)
        D_27ebf0->cell[c->cell] &= 0x7f;
    if (c->spin > 0) {
        if (c->spin >= 71) {
            c->angle = c->dir * 48;
            if (c->moved)
                c->spin = 0;
        } else {
            c->angle += 5;
            c->spin++;
            D_27ebf0->cell[c->cell] |= 0x80;
            return;
        }
    }
    short a = c->dir * 3;
    if (a == c->angle >> 4) {
        c->angle = a * 16;
    } else {
        short d = a - (c->angle >> 4);
        if (d > 0 ? d < 7 : d < -5)
            c->angle += 3;
        else
            c->angle -= 3;
    }
    if (c->angle < 0)
        c->angle += 192;
    if (c->angle > 192)
        c->angle -= 192;

    int px = (unsigned short)c->x;
    int py = (unsigned short)c->y;
    if (c->dir == 0 || c->dir == 2) {
        if (c->dir == 0)
            c->y -= c->speed;
        else
            c->y += c->speed;
        if (c->turn == 3) {
            c->slideX -= 4;
            if (c->slideX < -64)
                c->slideX = -64;
        } else if (c->turn == 1) {
            c->slideX += 4;
            if (c->slideX > 64)
                c->slideX = 64;
        } else if (c->slideX != 0) {
            if (c->slideX < 0) {
                c->slideX += 4;
                if (c->slideX > 0)
                    c->slideX = 0;
            } else {
                c->slideX -= 4;
                if (c->slideX < 0)
                    c->slideX = 0;
            }
        }
        hit = f_0e8ac8(c);
        if (hit) {
            c->y = (py >> 4) / 24 * 384 + 192;
            c->cy = ((unsigned short)c->y >> 4) / 24;
            f_0e8c58(c);
        } else {
            c->cy = ((unsigned short)c->y >> 4) / 24;
        }
    } else {
        if (c->dir == 3)
            c->x -= c->speed - (c->speed >> 3);
        else
            c->x += c->speed - (c->speed >> 3);
        if (c->turn == 0) {
            c->slideY -= 4;
            if (c->slideY < -64)
                c->slideY = -64;
        } else if (c->turn == 2) {
            c->slideY += 4;
            if (c->slideY > 64)
                c->slideY = 64;
        } else if (c->slideY != 0) {
            if (c->slideY < 0) {
                c->slideY += 4;
                if (c->slideY > 0)
                    c->slideY = 0;
            } else {
                c->slideY -= 4;
                if (c->slideY < 0)
                    c->slideY = 0;
            }
        }
        hit = f_0e8ac8(c);
        if (hit) {
            c->x = (px >> 4) / 24 * 384 + 192;
            c->cx = ((unsigned short)c->x >> 4) / 24;
            f_0e8c58(c);
        } else {
            c->cx = ((unsigned short)c->x >> 4) / 24;
        }
    }
    c->cy = ((unsigned short)c->y >> 4) / 24;
    c->cx = ((unsigned short)c->x >> 4) / 24;
    c->turn = -1;
    c->cell = c->cy * 32 + c->cx;
    if (c->cell != c->trail[0]) {
        c->trail[6] = c->trail[5];
        c->trail[5] = c->trail[4];
        c->trail[4] = c->trail[3];
        c->trail[3] = c->trail[2];
        c->trail[2] = c->trail[1];
        c->trail[1] = c->trail[0];
        c->trail[0] = c->cell;
        c->moved = 1;
    } else {
        c->moved = 0;
    }
    if (c->enemy) {
        if (c->spin <= 0 && (D_27ebf0->cell[c->cell] & 0x7f) == 18)
            c->spin = 1;
        if (hit == 17 || (hit & 0x80))
            c->spin = 1;
        D_27ebf0->cell[c->cell] |= 0x80;
    }
}

/* @draft 0x0e930c us f_0e930c
   WHAT IT DOES: Clears the smoke on the edges of the 12 x 12 cells around the car, and
   lays a smoke screen in the cell behind it when it has one left and that cell is empty
   (with its sound effect).
   DRAFT: not tuned yet (616 vs 600 bytes): the loop guards and the saved-register constants differ.
   2026-11-16: retail's loop counters are int (addiu s0,s0,1, no seh; fixed x/y and x0/y0 stay
   short/seh'd). Tried 'int i' counters for all four loops: size now 600 = retail, but
   107 -> 116 words, so reverted. What remains with int counters: retail keeps the cell index
   as a strength-reduced giv (horizontal: addu a1,s4,s0 before the branch; vertical: s1 =
   y0*32 + x, addiu s1,s1,32 per step) and holds D_27ebf0's hi in s8/s7; here the index is
   recomputed from the counter (sll a1,s0,5) and the table word reloaded in the delay slot. */
void f_0e930c(Car *c)
{
    short x, y;
    short x0, y0;

    x0 = c->cx - 6;
    y = c->cy - 6;
    for (x = x0; x < x0 + 12; x++)
        if (f_0e842c(x, y) == 18)
            D_27ebf0->cell[y * 32 + x] &= 0x80;
    y = c->cy + 6;
    for (x = x0; x < x0 + 12; x++)
        if (f_0e842c(x, y) == 18)
            D_27ebf0->cell[y * 32 + x] &= 0x80;
    y0 = c->cy - 6;
    x = c->cx - 6;
    for (y = y0; y < y0 + 12; y++)
        if (f_0e842c(x, y) == 18)
            D_27ebf0->cell[y * 32 + x] &= 0x80;
    x = c->cx + 6;
    for (y = y0; y < y0 + 12; y++)
        if (f_0e842c(x, y) == 18)
            D_27ebf0->cell[y * 32 + x] &= 0x80;
    if (c->smoke > 0 && (D_27ebf0->cell[c->trail[1]] & 0x7f) == 0) {
        D_27ebf0->cell[c->trail[1]] = (D_27ebf0->cell[c->trail[1]] & 0x80) | 18;
        c->smoke--;
        f_0933f8(f_093330(), 2);
    }
}

/* @implements 0x0e9564 us f_0e9564
   WHAT IT DOES: Runs an enemy's driver once per cell, when the car can turn. The cell is
   copied through a short local, which is promoted to a sign-extended register (retail's lh). */
void f_0e9564(Car *c, Car *player)
{
    if (f_0e8930(c) && c->thought != c->cell) {
        c->think(player, c);
        short cell = c->cell;
        c->thought = cell;
    }
}

/* @implements 0x0e95c4 us f_0e95c4
   WHAT IT DOES: The driver that heads for the player's own cell. */
void f_0e95c4(Car *t, Car *c)
{
    int w = 32;
    int h = 32;
    int x = t->cell % h;
    int y = t->cell / w;
    f_0e98e8(t, t->cx, t->cy, t->cx, t->cy, c);
}

/* @implements 0x0e9604 us f_0e9604
   WHAT IT DOES: The driver that heads five cells ahead of where the player was two cells
   ago. */
void f_0e9604(Car *t, Car *c)
{
    int dx = 0;
    int dy = 0;

    if (t->dir == 0)
        dy = -5;
    else if (t->dir == 2)
        dy = 5;
    else if (t->dir == 3)
        dx = -5;
    else if (t->dir == 1)
        dx = 5;
    int w = 32;
    int x = t->trail[2] % w + dx;
    short y = t->trail[2] / w + dy;
    f_0e98e8(t, t->cx, t->cy, x, y, c);
}

/* @implements 0x0e96a0 us f_0e96a0
   WHAT IT DOES: The driver that heads three cells behind where the player was two cells
   ago. */
void f_0e96a0(Car *t, Car *c)
{
    int dx = 0;
    int dy = 0;

    if (t->dir == 0)
        dy = -3;
    else if (t->dir == 2)
        dy = 3;
    else if (t->dir == 3)
        dx = -3;
    else if (t->dir == 1)
        dx = 3;
    int w = 32;
    int x = t->trail[2] % w - dx;
    short y = t->trail[2] / w - dy;
    f_0e98e8(t, t->cx, t->cy, x, y, c);
}

/* @implements 0x0e973c us f_0e973c
   WHAT IT DOES: The driver that heads for where the player was three cells ago. */
void f_0e973c(Car *t, Car *c)
{
    int w = 32;
    int h = 32;
    int x = t->trail[3] % h;
    int y = t->trail[3] / w;
    f_0e98e8(t, t->cx, t->cy, x, y, c);
}

/* @implements 0x0e9784 us f_0e9784
   WHAT IT DOES: The driver that heads one cell behind where the player was two cells
   ago. */
void f_0e9784(Car *t, Car *c)
{
    int dx = 0;
    int dy = 0;

    if (t->dir == 0)
        dy = -1;
    else if (t->dir == 2)
        dy = 1;
    else if (t->dir == 3)
        dx = -1;
    else if (t->dir == 1)
        dx = 1;
    int w = 32;
    int x = t->trail[2] % w - dx;
    short y = t->trail[2] / w - dy;
    f_0e98e8(t, t->cx, t->cy, x, y, c);
}

/* @draft 0x0e9820 us f_0e9820
   WHAT IT DOES: The player's autopilot (demo): steers away from the enemy (towards it
   across x when it is more than ten cells off), buys smoke when the enemy is within three
   cells, and takes the turn chosen.
   DRAFT: dx and dy swap registers (a3/v1) in both blocks; four orderings tried.
   2026-11-16 (greg): dy (pseudo 189, allocated first) conflicts with v1 through the block-2
   cx-load locals, so it takes a3 and dx takes its v1 preference. Tried fresh locals for the
   block-2 dy/dx (splits the live ranges): 17 -> 23 words, every local moves; reverted. */
void f_0e9820(Car *c, Car *e)
{
    int ex = e->cx;
    int cx = c->cx;
    int cy = c->cy;
    int dy, dx;
    dx = cx - ex;
    int ax = dx < 0 ? -dx : dx;
    dy = cy - e->cy;
    if (ax > 10)
        dx = -dx;
    f_0e9bf0(c, cx + dx, cy + dy);
    dy = c->cy - e->cy;
    dx = c->cx - e->cx;
    if (dy * dy + dx * dx < 9) {
        int score = 0x9600;
        f_0e89f4(c, &score);
    }
    f_0e8840(c);
}

/* @draft 0x0e98e8 us f_0e98e8
   WHAT IT DOES: An enemy's steering at a junction (three or more open ways): towards the
   target cell (b), or the player's own cell (a) when the target is within five cells of a
   T junction, taking the player's side on an axis where the two lie on opposite sides; and
   it turns aside when the player is just behind it in its own row or column. Then takes the
   turn chosen.
   DRAFT: registers differ from the first product on, and the two-target choice block is laid out differently; the y*y > x*x spelling that fixed f_0e9bf0 made this one worse.
   2026-11-16 (fold): retail's aside block is all branches (dir tested first, then the
   delta) with the |dxa| <= 1 test as one range (addiu 1; sltiu 3); here fold_truthop makes
   'dir == k && dya > 0' a TRUTH_AND of setccs because dya/dxa are simple (non-addressable
   local decls). Tried grouping '(dxa >= -1 && dxa <= 1)': the range merges as retail, but
   the setcc ORs stay, 102 -> 118 words; reverted. Implied next shape: use the deltas as
   non-simple operands (inline 'ax - px' etc. instead of the dxa/dya locals) so the &&/||
   stay short-circuit. */
void f_0e98e8(Car *t, int ax0, int ay0, int bx0, int by0, Car *c)
{
    short ax = ax0;
    short ay = ay0;
    short bx = bx0;
    short by = by0;
    short px = c->cx;
    short py = c->cy;
    int l = 0, r = 0, u = 0, d = 0;
    int n = 0;

    if (f_0e8a24(c, px - 1, py)) {
        l = 1;
        n = 1;
    }
    if (f_0e8a24(c, px + 1, py)) {
        r = 1;
        n++;
    }
    if (f_0e8a24(c, px, py - 1)) {
        u = 1;
        n++;
    }
    if (f_0e8a24(c, px, py + 1)) {
        d = 1;
        n++;
    }
    if (n >= 3) {
        int dxa = ax - px;
        int dxb = bx - px;
        int dya = ay - py;
        int dyb = by - py;
        int x = dxb;
        int y = dyb;
        short nd = c->dir;

        if (dxa * dxb <= 0) {
            if (dya == dyb)
                goto aside;
            x = dxa;
        }
        if (dya * dyb <= 0) {
            if (dxa == x)
                goto aside;
            y = dya;
        }
        if (n == 3 && x * x + y * y < 25) {
            x = dxa;
            y = dya;
        }
        if (x * x < y * y) {
            if (y <= 0 && u)
                nd = 0;
            if (d && y >= 0)
                nd = 2;
        } else {
            if (x <= 0 && l)
                nd = 3;
            if (r && x >= 0)
                nd = 1;
        }
    aside:
        if ((c->dir == 0 || c->dir == 2) && dxa >= -1 && dxa <= 1) {
            if ((c->dir == 0 && dya > 0) || (c->dir == 2 && dya < 0))
                nd = r ? 1 : 3;
        } else if (dya >= -1 && dya <= 1) {
            if ((c->dir == 3 && dxa > 0) || (c->dir == 1 && dxa < 0))
                nd = d ? 2 : 0;
        }
        if (nd != -1 && nd != c->dir && (nd + 2) % 4 != c->dir)
            c->turn = c->want = nd;
    }
    f_0e8840(c);
}

/* @implements 0x0e9bf0 us f_0e9bf0
   WHAT IT DOES: The autopilot's steering at a junction: along the axis on which the target
   is farther, towards it, never straight back; then takes the turn chosen. */
void f_0e9bf0(Car *c, short tx, short ty)
{
    short px = c->cx;
    short py = c->cy;
    int l = 0, r = 0, u = 0, d = 0;
    int n = 0;

    if (f_0e8a24(c, px - 1, py)) {
        l = 1;
        n = 1;
    }
    if (f_0e8a24(c, px + 1, py)) {
        r = 1;
        n++;
    }
    if (f_0e8a24(c, px, py - 1)) {
        u = 1;
        n++;
    }
    if (f_0e8a24(c, px, py + 1)) {
        d = 1;
        n++;
    }
    if (n >= 3) {
        int x = tx - px;
        int y = ty - py;
        short nd = c->dir;

        if (y * y > x * x) {
            if (y <= 0 && u)
                nd = 0;
            if (d && y >= 0)
                nd = 2;
        } else {
            if (x <= 0 && l)
                nd = 3;
            if (r && x >= 0)
                nd = 1;
        }
        int back = (nd + 2) % 4;
        if (nd != -1 && nd != c->dir && back != c->dir)
            c->turn = c->want = nd;
    }
    f_0e8840(c);
}
