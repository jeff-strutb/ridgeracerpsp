/* The race's car manager (retail 0x0ca814 to 0x0cb358): the list of cars the race draws.
   It keeps one entry per car (a kind, a depth key, the car's model and the car's name sprite
   row) plus an array of pointers to the entries that is sorted by the depth key each frame,
   and draws every car in that order: a stencil pass, the models with their colour fade by
   distance, the light trails and the lamp flares, and then the rivals' names. */

#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

struct Mat {
    float m[16];
} __attribute__((aligned(16)));

/* The race view: the part used here is the view matrix, the projection and the distance scale. */
struct View {
    char m0[288];
    Mat view;
    Mat proj;
    char m416[80];
    float scale;
};

/* A car's model state as the draw reads it. */
struct Model {
    int m0;
    unsigned int *dl;
    char m8[8];
    Mat world;
    char m80[112];
    Vec4 box;
    char m208[1420];
    unsigned int m1628;
    unsigned int m1632;
    char m1636[76];
};

struct CarModel {
    char m0[288];
    Model model;
    char res[16];
    char table[709];
    signed char m2725;
    signed char m2726;
    signed char m2727;
    signed char m2728;
    void f_01ed64(Mat *world);
    void f_01ee78();
    void f_01ee98();
    void f_01eebc(int arg);
    void f_01eee4();
    unsigned int *f_01f2f0(unsigned int *list);
};

extern "C" {
void f_028e9c(const Mat *m);
unsigned int *f_0251b4(unsigned int *p);
unsigned int *f_025264(unsigned int *p);
unsigned int *f_025068(unsigned int *p);
unsigned int *f_025190(unsigned int *p);
unsigned int *f_027524(unsigned int *p);
unsigned int *f_02769c(unsigned int *p, const Mat *v);
unsigned int *f_01f264(View *v, unsigned int *p);
unsigned int *f_01f9a0(unsigned int *p);
unsigned int *f_026ffc(void *t, const Mat *m, signed char visible, unsigned int *p);
void f_026e5c(void *res);
void f_026efc(void *table);
void f_0cb358(Model *m, unsigned int colour);
int f_0cc8c8(View *view, Vec4 *pos, float r);
void f_0e6854(void);
int f_0e68f8(void);
unsigned int *f_0e6920(unsigned int *p);
void *f_0e698c(void *p);
}

/* A name sprite row (DispName.cpp, which defines its constructor and destructor). */
/* Stand-ins for the constructor and destructor DispName.cpp defines; their names carry the
   retail addresses so the calls made here resolve to them. */
struct f_0e69a0 {
    f_0e69a0();
};
struct f_0e69c8 {
    ~f_0e69c8();
};

class CDispName : public f_0e69a0, public f_0e69c8 {
public:
    void f_0e69e4(const char *name);
    void f_0e6b1c();
    unsigned int *f_0e6b88(View *cam, Vec4 *pos, unsigned int *dl);
    char data[24];
};

struct CarEntry {
    int kind;
    float key;
    CarModel *car;
    CDispName name;
};

struct CarSwitch {
    char m0[664];
    int on;
};

class CCarManager {
public:
    int f_0ca814(int count);
    void f_0ca98c();
    void f_0caa5c(int i, CarModel *car, int kind, const char *name);
    void f_0caab4(CarSwitch *sw);
    void f_0cab50(int lo, int hi);
    void f_0cac40();
    unsigned int *f_0cac88(int flags, View *view, unsigned int *dl);
    unsigned int *f_0cb114(View *view, unsigned int *dl);
    unsigned int *f_0cb2ac(int flags, View *view, unsigned int *dl);

    int n;
    CarEntry *entries;
    CarEntry **order;
};

/* @implements 0x0ca814 us f_0ca814
   WHAT IT DOES: Allocates the entry array (one entry per car, each with an empty name row) and
   the array of entry pointers, points each pointer at its entry, loads the name font and
   records the count. Returns 0, or -1 when an allocation fails (nothing kept then). */
int CCarManager::f_0ca814(int count)
{
    entries = new CarEntry[count];
    if (!entries)
        return -1;
    order = new CarEntry *[count];
    if (!order) {
        delete[] entries;
        entries = 0;
        return -1;
    }
    for (int i = 0; i < count; i++)
        order[i] = &entries[i];
    n = count;
    f_0e6854();
    return 0;
}

/* @implements 0x0ca98c us f_0ca98c
   WHAT IT DOES: Frees every name row, unloads the name font, frees both arrays and clears the
   count. */
void CCarManager::f_0ca98c()
{
    for (int i = 0; i < n; i++)
        entries[i].name.f_0e6b1c();
    f_0e68f8();
    if (order) {
        delete[] order;
        order = 0;
    }
    if (entries) {
        delete[] entries;
        entries = 0;
    }
    n = 0;
}

/* @implements 0x0caa5c us f_0caa5c
   WHAT IT DOES: Fills in one car's entry: its kind, its model and its name. Nothing when the
   list is not allocated or the index is out of range. */
void CCarManager::f_0caa5c(int i, CarModel *car, int kind, const char *name)
{
    CarEntry *e = entries;
    if (e && i < n) {
        e[i].kind = kind;
        e[i].car = car;
        e[i].name.f_0e69e4(name);
    }
}

/* @implements 0x0caab4 us f_0caab4
   WHAT IT DOES: Steps every car's lights for the frame and, when the given switch is on,
   updates its light trails. */
void CCarManager::f_0caab4(CarSwitch *sw)
{
    for (int i = 0; i < n; i++) {
        entries[i].car->f_01eee4();
        if (sw && sw->on)
            f_026efc(entries[i].car->table);
    }
}

/* @implements 0x0cab50 us f_0cab50
   WHAT IT DOES: Quicksort of the entry pointers [lo, hi] by their depth key, ascending. */
void CCarManager::f_0cab50(int lo, int hi)
{
    if (lo >= hi)
        return;
    CarEntry **a = order;
    int mid = (lo + hi) / 2;
    CarEntry *pivot = a[mid];
    a[mid] = a[lo];
    int last = lo;
    for (int i = lo + 1; i <= hi; i++) {
        if (a[i]->key < pivot->key) {
            last++;
            CarEntry *t = a[last];
            a[last] = a[i];
            a[i] = t;
        }
    }
    a[lo] = a[last];
    a[last] = pivot;
    f_0cab50(lo, last - 1);
    f_0cab50(last + 1, hi);
}

/* @implements 0x0cac40 us f_0cac40
   WHAT IT DOES: Takes each car's distance as its key and sorts the entry pointers by it. */
void CCarManager::f_0cac40()
{
    for (int i = 0; i < n; i++)
        entries[i].key = entries[i].car->model.world.m[14];
    f_0cab50(0, n - 1);
}

/* @draft 0x0cac88 us f_0cac88
   WHAT IT DOES: Draws every car for the frame; the flag bits are 1: leave the player kind
   out, 2: leave the player kind's light trails out, 4: draw the third kind's second pass only
   when close. It loads the depth scale into the vector unit and gives each visible car the
   depth range command; then, with the stencil state, draws each car that is inside the view
   (hidden ones are marked) with a colour that fades with distance, then the light trails of the
   cars, then the lamp flares. Returns the end of the list.
   DRAFT: same control flow and calls; about 12 instructions differ in order, the rest in
   register choice. Retail hoists the first loop's address set up above its test and keeps
   the trail loop's table address computation after the kind test; the second-pass call
   shares one constant register. The first loop's unlikely block is forced out of line with
   __builtin_expect (retail's layout; the natural form keeps it inline). */
unsigned int *CCarManager::f_0cac88(int flags, View *view, unsigned int *dl)
{
    Vec4 k = { -32768.0f, 32767.0f, 500.0f, 0.0f };
    int i;
    CarModel *car;
    CarEntry *e;

    f_028e9c(&view->proj);
    __asm__ volatile("lv.q C100.q, %0" : : "m"(k));
    for (i = 0; i < n; i++) {
        car = entries[i].car;
        Model *m = &car->model;
        const Mat *w = &m->world;
        if (__builtin_expect(car->m2727 == 0, 0)) {
            unsigned int depth;
            __asm__ volatile(VFPU_BEGIN
                             "lv.q C310.q, 48(%1)\n\t"
                             "vmov.q C330.q, C310.q\n\t"
                             "vadd.s S332.s, S332.s, S102.s\n\t"
                             "vtfm4.q C300.q, E700.q, C310.q\n\t"
                             "vtfm4.q C320.q, E700.q, C330.q\n\t"
                             "vrcp.s S303.s, S303.s\n\t"
                             "vrcp.s S323.s, S323.s\n\t"
                             "vscl.t C300.t, C300.t, S303.s\n\t"
                             "vscl.t C320.t, C320.t, S323.s\n\t"
                             "vsub.s S302.s, S322.s, S302.s\n\t"
                             "vmul.s S302.s, S302.s, S100.s\n\t"
                             "vadd.s S302.s, S302.s, S101.s\n\t"
                             "sv.s S302.s, %0" VFPU_END
                             : "=m"(depth) : "r"(w));
            m->m1628 = (depth >> 8) | 0x47000000;
        }
    }
    dl = f_0251b4(dl);
    for (i = 0; i < n; i++) {
        int two = 2;
        e = order[i];
        car = e->car;
        if (car->m2727)
            continue;
        if (!car->m2728) {
            if (!f_0cc8c8(view, &car->model.box, 2500.0f)) {
                car->m2727 = two;
                continue;
            }
        }
        int kind = order[i]->kind;
        if (kind == 0 && (flags & 1))
            continue;
        if (kind == two)
            continue;
        int z = (int)(car->model.world.m[14] / view->scale);
        int level = 0;
        if (kind) {
            level = 1;
            if (z < -19999) {
                level = z < -29999;
                level += 2;
            }
        }
        car->m2726 = level;
        unsigned int col = 0xffffff;
        if (z < -14999) {
            if (z < -29999) {
                col = 0;
            } else {
                int c = (-30000 - z) * 255 / 15000;
                col = c | (c << 8) | (c << 16);
            }
        }
        Model *m = &car->model;
        f_0cb358(m, col);
        m->dl = dl;
        car->f_01ee98();
        dl = m->dl;
    }
    dl = f_025068(f_025264(dl));
    for (i = 0; i < n; i++) {
        e = order[i];
        car = e->car;
        if (car->m2727)
            continue;
        if (e->kind == 0 && (flags & 1))
            continue;
        Model *m = &car->model;
        m->dl = dl;
        f_026e5c(car->res);
        if (order[i]->kind != 2) {
            car->f_01ee78();
        } else if (!(flags & 4) || (int)(car->model.world.m[14] / view->scale) < -1899) {
            car->f_01eebc(128);
        }
        dl = m->dl;
    }
    dl = f_027524(f_025190(dl));
    for (i = 0; i < n; i++) {
        e = order[i];
        car = e->car;
        if (e->kind == 0 && (flags & 2))
            continue;
        if (e->kind == 2)
            continue;
        const Mat *m = 0;
        signed char vis = 0;
        if (!car->m2727) {
            m = &car->model.world;
            vis = car->m2725;
        }
        dl = f_026ffc(car->table, m, vis, dl);
    }
    dl = f_01f264(view, f_02769c(dl, &view->view));
    for (i = 0; i < n; i++) {
        e = order[i];
        car = e->car;
        if (car->m2727)
            continue;
        if (e->kind == 0 && (flags & 1))
            continue;
        dl = car->f_01f2f0(dl);
    }
    return f_01f9a0(dl);
}

/* @implements 0x0cb114 us f_0cb114
   WHAT IT DOES: Draws the shadow-side pass of the rival cars, last entry first: each car that
   is still visible (not marked hidden by bit 0) and is not a player kind is placed in the
   view, tested against the view (hidden and skipped when outside), given its fade level from
   its distance (none for the third kind) and drawn with its colour reset; the third kind gets
   a second draw when it is close enough. Returns the end of the list. */
unsigned int *CCarManager::f_0cb114(View *view, unsigned int *dl)
{
    dl = f_025068(dl);
    for (int i = n - 1; i >= 0; i--) {
        int rival = 2;
        CarModel *car = order[i]->car;
        if ((unsigned char)car->m2727 & 1)
            continue;
        if (order[i]->kind == 0)
            continue;
        car->f_01ed64(&view->view);
        if (!f_0cc8c8(view, &car->model.box, 2500.0f)) {
            car->m2727 = rival;
            continue;
        }
        int level = 0;
        if (order[i]->kind != rival) {
            float sc = view->scale;
            float z = car->model.world.m[14];
            int d = (int)(z / sc);
            level = d < -29999;
            level += 2;
        }
        car->m2726 = level;
        Model *m = &car->model;
        f_0cb358(m, 0);
        m->dl = dl;
        f_026e5c(car->res);
        if (order[i]->kind != rival) {
            car->f_01ee78();
        } else {
            float sc = view->scale;
            if ((int)(car->model.world.m[14] / sc) < -1499)
                car->f_01eebc(128);
        }
        dl = m->dl;
    }
    return f_025190(dl);
}

/* @implements 0x0cb2ac us f_0cb2ac
   WHAT IT DOES: Draws the rivals' names: for every entry that is not a player kind and whose
   car is visible, adds the name row standing over the car's position. Returns the end of the
   list. */
unsigned int *CCarManager::f_0cb2ac(int flags, View *view, unsigned int *dl)
{
    dl = f_0e6920(dl);
    for (int i = 0; i < n; i++) {
        if (order[i]->kind == 0)
            continue;
        if (order[i]->car->m2727)
            continue;
        dl = order[i]->name.f_0e6b88(view, &order[i]->car->model.box, dl);
    }
    return (unsigned int *)f_0e698c(dl);
}
