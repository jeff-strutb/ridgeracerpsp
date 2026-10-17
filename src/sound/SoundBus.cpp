/* The sound mixer's buses (retail 0x10db3c to 0x10e198): 32 volume buses built from the bus
   definitions the mixer configuration loads (0x10e198, the next object file), each with a
   volume, a pan, an FX send and a parent bus, plus a table of the 32 FX definitions in use.
   A bus can fade its volume to a target over a number of ticks, and a sound's final volume
   and pan come from walking its bus chain up to the root. Error 0x80000007 means an invalid
   or unused bus. */

/* A bus definition as the configuration loads it (16 bytes, 32 of them at D_27f674). */
struct BusDef {
    int used;
    short parent;   /* -1 at the root */
    short pad6;
    float vol;
    short pan;
    short fx;       /* FX send, -1 for none */
};

/* An FX definition (136 bytes, 32 of them at D_27f874). */
struct FxDef {
    int used;
    int m4[33];
};

/* A live bus (32 bytes). */
struct Bus {
    BusDef *def;
    float vol;
    short pan;
    short fx;
    signed char state;  /* 0 unused, 1 active, 2 fading */
    char pad13[3];
    int count;          /* fade ticks left */
    float target;
    float step;
    int dirty;          /* the FX send changed */
};

/* An FX slot in use. */
struct FxSlot {
    FxDef *def;
    int dirty;
};

/* A sound's mix result: volume, pan and the FX sends along its bus chain. */
struct BusMix {
    float vol;
    short pan;
    unsigned short n;
    unsigned char fx[32];
    unsigned char bus[32];

    void Add(unsigned char b, unsigned char f)
    {
        fx[n] = f;
        bus[n] = b;
        n++;
    }
};

extern "C" {
extern Bus D_27f174[32];
extern FxSlot D_27f574[32];
extern BusDef D_27f674[32];
extern FxDef D_27f874[32];
extern int D_280974[64];
extern float D_280a74[6];

int f_10db58(void);
int f_10dc50(unsigned char i);
int f_10e120(int i);
BusDef *f_10e168(void);
FxDef *f_10e174(void);

/* @implements 0x10db3c us f_10db3c
   WHAT IT DOES: Sets up the buses (0x10db58). */
int f_10db3c(void)
{
    return f_10db58();
}

/* @implements 0x10db58 us f_10db58
   WHAT IT DOES: Builds the 32 live buses from the loaded definitions: a used definition
   makes an active bus that copies its settings (0x10dc50), an unused one leaves the bus
   free; every bus is marked dirty. Then records which of the 32 FX definitions are in use. */
int f_10db58(void)
{
    BusDef *def = f_10e168();
    FxDef *fx = f_10e174();
    int i;

    for (i = 0; i < 32; i++) {
        Bus *b = &D_27f174[i];
        if (def[i].used) {
            b->state = 1;
            b->def = &def[i];
            f_10dc50(i);
        } else {
            b->state = 0;
            b->def = 0;
        }
        b->dirty = 1;
    }
    for (i = 0; i < 32; i++) {
        FxSlot *s = &D_27f574[i];
        if (fx[i].used) {
            s->def = &fx[i];
            s->dirty = 1;
        } else {
            s->def = 0;
            s->dirty = 0;
        }
    }
    return 0;
}

/* @implements 0x10dc48 us f_10dc48
   WHAT IT DOES: Does nothing and returns 0. */
int f_10dc48(void)
{
    return 0;
}

/* @implements 0x10dc50 us f_10dc50
   WHAT IT DOES: Resets bus i to its definition: active, the definition's pan and volume, and
   its FX send, marking the bus dirty when the send changes. Bus 255 resets every bus that is
   in use. Returns 0x80000007 for an invalid bus. */
int f_10dc50(unsigned char i)
{
    if (i == 255) {
        int j;
        for (j = 0; j < 32; j++)
            if (D_27f174[j].state)
                f_10dc50(j);
        return 0;
    }
    if (!f_10e120(i))
        return 0x80000007;
    Bus *b = &D_27f174[i];
    BusDef *d = b->def;
    b->pan = d->pan;
    b->vol = d->vol;
    b->state = 1;
    if (b->fx != d->fx) {
        b->dirty = 1;
        b->fx = d->fx;
    }
    return 0;
}

/* @implements 0x10dd2c us f_10dd2c
   WHAT IT DOES: Sets bus i's FX send and marks the bus dirty; 0x80000007 for an invalid bus. */
int f_10dd2c(unsigned char i, short fx)
{
    Bus *b = &D_27f174[i];
    if (!f_10e120(i))
        return 0x80000007;
    b->fx = fx;
    b->dirty = 1;
    return 0;
}

/* @implements 0x10dd90 us f_10dd90
   WHAT IT DOES: Returns and clears bus i's dirty flag. */
int f_10dd90(int i)
{
    int d = D_27f174[i].dirty;
    D_27f174[i].dirty = 0;
    return d;
}

/* @implements 0x10ddac us f_10ddac
   WHAT IT DOES: Sets bus i's pan and volume; 0x80000007 for an invalid bus. */
int f_10ddac(unsigned char i, short pan, float vol)
{
    Bus *b = &D_27f174[i];
    if (!f_10e120(i))
        return 0x80000007;
    b->vol = vol;
    b->pan = pan;
    return 0;
}

/* @implements 0x10de18 us f_10de18
   WHAT IT DOES: Sets bus i's volume; 0x80000007 for an invalid bus. */
int f_10de18(unsigned char i, float vol)
{
    Bus *b = &D_27f174[i];
    if (!f_10e120(i))
        return 0x80000007;
    b->vol = vol;
    return 0;
}

/* @implements 0x10de74 us f_10de74
   WHAT IT DOES: Sets bus i's pan; 0x80000007 for an invalid bus. */
int f_10de74(unsigned char i, short pan)
{
    Bus *b = &D_27f174[i];
    if (!f_10e120(i))
        return 0x80000007;
    b->pan = pan;
    return 0;
}

/* @implements 0x10ded0 us f_10ded0
   WHAT IT DOES: Starts a fade of bus i's volume to a target over n ticks; 0x80000007 for an
   invalid bus. */
int f_10ded0(unsigned char i, int n, float target)
{
    Bus *b = &D_27f174[i];
    if (!f_10e120(i))
        return 0x80000007;
    b->state = 2;
    b->count = n;
    b->target = target;
    b->step = (target - b->vol) / (float)n;
    return 0;
}

/* @implements 0x10df5c us f_10df5c
   WHAT IT DOES: Advances every fading bus by dt ticks, landing on the target and going back
   to active when the fade runs out. */
int f_10df5c(int dt)
{
    int i;

    for (i = 0; i < 32; i++) {
        Bus *b = &D_27f174[i];
        if (b->state == 2) {
            b->count -= dt;
            if (b->count > 0) {
                b->vol = b->vol + b->step * (float)dt;
            } else {
                b->state = 1;
                b->vol = b->target;
            }
        }
    }
    return 0;
}

/* @implements 0x10dfcc us f_10dfcc
   WHAT IT DOES: Mixes bus id up its chain to the root: the volumes multiply, the pans add
   about the centre 64, and every bus with an FX send adds that send and the bus to the
   result's lists. Returns 0x80000007 if a bus on the way is invalid. */
int f_10dfcc(short id, BusMix *m)
{
    float vol;
    int pan = 0;

    m->n = 0;
    vol = 1.0f;
    do {
        Bus *b = &D_27f174[id];
        if (!f_10e120(id))
            return 0x80000007;
        if (b->fx != -1)
            m->Add(id, b->fx);
        pan += b->pan - 64;
        vol *= b->vol;
        id = b->def->parent;
    } while (id >= 0);
    m->vol = vol;
    m->pan = pan + 64;
    return 0;
}

/* @implements 0x10e0b4 us f_10e0b4
   WHAT IT DOES: Returns FX slot i's definition (0 when unused). */
FxDef *f_10e0b4(int i)
{
    return D_27f574[i].def;
}

/* @implements 0x10e0cc us f_10e0cc
   WHAT IT DOES: Returns and clears FX slot i's flag. */
int f_10e0cc(int i)
{
    int d = D_27f574[i].dirty;
    D_27f574[i].dirty = 0;
    return d;
}

/* @implements 0x10e0e8 us f_10e0e8
   WHAT IT DOES: Returns bus i's pan. */
short f_10e0e8(unsigned char i)
{
    return D_27f174[i].pan;
}

/* @implements 0x10e104 us f_10e104
   WHAT IT DOES: Returns bus i's volume. */
float f_10e104(unsigned char i)
{
    return D_27f174[i].vol;
}

/* @implements 0x10e120 us f_10e120
   WHAT IT DOES: Returns 1 if i names a bus in use (0 to 31, not free), else 0. */
int f_10e120(int i)
{
    if (D_27f174[i].state == 0 || i >= 32 || i < 0)
        return 0;
    return 1;
}

/* @implements 0x10e168 us f_10e168
   WHAT IT DOES: Returns the bus definition table. */
BusDef *f_10e168(void)
{
    return D_27f674;
}

/* @implements 0x10e174 us f_10e174
   WHAT IT DOES: Returns the FX definition table. */
FxDef *f_10e174(void)
{
    return D_27f874;
}

/* @implements 0x10e180 us f_10e180
   WHAT IT DOES: Returns the group table the configuration loads. */
int *f_10e180(void)
{
    return D_280974;
}

/* @implements 0x10e18c us f_10e18c
   WHAT IT DOES: Returns the 3D sound parameters the configuration loads. */
float *f_10e18c(void)
{
    return D_280a74;
}
}
