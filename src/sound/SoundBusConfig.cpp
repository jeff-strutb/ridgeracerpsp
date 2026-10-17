/* The sound mixer's configuration loader (retail 0x10e198): reads the mixer's text table
   (the reader at 0x114d6c, entries up to the "//end of" line) into the 32 bus definitions,
   32 FX definitions, 32 groups and the 3D sound parameters that the buses (0x10db3c) are
   built from. */

extern "C" {
void *memset(void *d, int c, unsigned int n);
int sprintf(char *s, const char *fmt, ...);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, unsigned int n);
int atoi(const char *s);
double f_125954(const char *s); /* atof */

void f_114d6c(void *r, const char *text, const char *end);
void f_114dac(void *r);
int f_114db4(void *r, const char *key);
int f_114dd4(void *r, const char *key);
const char *f_114e00(void *r, const char *key, int i);
int f_114f04(void *r, const char *key, int i);
}

/* The text table reader of another object file (0x114d34). */
struct CReader {
    char m[5648];

    CReader(const char *text, const char *end) { f_114d6c(this, text, end); }
    ~CReader() { f_114dac(this); }
    int Find(const char *key) { return f_114db4(this, key); }
    int Count(const char *key) { return f_114dd4(this, key); }
    const char *Get(const char *key, int i) { return f_114e00(this, key, i); }
    int GetInt(const char *key, int i) { return f_114f04(this, key, i); }
};

struct BusDef {
    int used;
    short parent;   /* -1 at the root */
    short pad6;
    float vol;
    short pan;
    short fx;       /* FX send, -1 for none */
};

union FxValues {
    int i[32];
    float f[32];
};

struct FxDef {
    int used;
    int size;       /* bytes of values */
    FxValues v;
};

struct Group {
    int used;
    int value;
};

struct SoundConfig {
    BusDef bus[32];
    FxDef fx[32];
    Group group[32];
    float distanceRange;
    float distance;
    float dopplerRange;
    float dopplerLimit;
    float priorityRate;
    float attenuationRange;
};

extern "C" SoundConfig D_27f674;

/* A value is a float when it has a '.' or an 'f' in it. */
static inline int IsFloat(const char *s)
{
    int i;
    int r = 0;

    for (i = 0; s[i]; i++) {
        if (s[i] == 'f' || s[i] == '.') {
            r = 1;
            break;
        }
    }
    return r;
}

/* A float row's first value, or a default when the row is absent. */
#define GET_FLOAT(r, key, out, def)            \
    do {                                       \
        const char *k_ = key;                  \
        if ((r).Find(k_))                      \
            out = f_125954((r).Get(k_, 0));    \
        else                                   \
            out = def;                         \
    } while (0)

extern "C" {

/* @draft 0x10e198 us f_10e198
   WHAT IT DOES: Parses the mixer configuration text. BusN rows give the parent bus ("None"
   or BusK; bus 0 must be the root), the volume out of 127, the pan and the FX send ("None"
   or FXK); FXN rows give a list of int or float parameters; GROUPN rows one number; the 3D_
   rows the distance, Doppler, priority and attenuation settings, with defaults when absent.
   Returns 0, or 0x80000004/5/6 for a bad parent or FX entry.
   DRAFT: 23 of 380 words differ, all in the FX value loop's entry. Retail computes the
   value array's address before the n <= 0 test (in the blez slot) and copies it into the two
   store pointers after it, with j = 0 before the branch; here both pointers are set after the
   test and j = 0 goes in the slot, which shifts the inner scan by one word. The float stores
   through a pointer local and the int stores through the member keep the two pointers apart
   (one address form for both lets loop combine them). */
int f_10e198(const char *text)
{
    char name[16];
    CReader r(text, "//end of");
    SoundConfig *c = &D_27f674;
    const char *s;
    int i;

    memset(c->bus, 0, sizeof c->bus);
    memset(c->fx, 0, sizeof c->fx);
    memset(c->group, 0, sizeof c->group);

    for (i = 0; i < 32; i++) {
        BusDef *b = &c->bus[i];
        sprintf(name, "Bus%d", i);
        if (r.Find(name)) {
            s = r.Get(name, 0);
            if (i == 0) {
                if (strcmp(s, "None") != 0)
                    return 0x80000004;
                b->parent = -1;
            } else if (strcmp(s, "None") == 0) {
                b->parent = -1;
            } else {
                if (strncmp(s, "Bus", 3) != 0)
                    return 0x80000005;
                b->parent = atoi(s + 3);
                if ((unsigned short)b->parent >= 32)
                    return 0x80000005;
            }
            b->vol = r.GetInt(name, 1) / 127.0f;
            b->pan = r.GetInt(name, 2);
            s = r.Get(name, 3);
            if (i == 0) {
                if (strncmp(s, "None", 4) != 0)
                    return 0x80000006;
                b->fx = -1;
            } else if (strncmp(s, "FX", 2) == 0) {
                b->fx = atoi(s + 2) - 1;
            } else {
                b->fx = -1;
            }
            b->used = 1;
        } else {
            b->used = 0;
        }
    }

    for (i = 0; i < 32; i++) {
        FxDef *f = &c->fx[i];
        sprintf(name, "FX%d", i + 1);
        if (r.Find(name)) {
            int n = r.Count(name);
            int j;
            f->size = n * 4;
            float *fv = f->v.f;
            for (j = 0; j < n; j++) {
                s = r.Get(name, j);
                if (IsFloat(s))
                    fv[j] = f_125954(s);
                else
                    f->v.i[j] = atoi(s);
            }
            f->used = 1;
        } else {
            f->used = 0;
        }
    }

    for (i = 0; i < 32; i++) {
        Group *g = &c->group[i];
        sprintf(name, "GROUP%d", i);
        if (r.Find(name)) {
            g->used = 1;
            g->value = atoi(r.Get(name, 0));
        } else {
            g->used = 0;
        }
    }

    GET_FLOAT(r, "3D_DISTANCE_RANGE", c->distanceRange, 1.0f);
    GET_FLOAT(r, "3D_DISTANCE", c->distance, 8000.0f);
    GET_FLOAT(r, "3D_DOPPLER_RANGE", c->dopplerRange, 1.0f);
    GET_FLOAT(r, "3D_DOPPLER_LIMIT", c->dopplerLimit, 6.0f);
    GET_FLOAT(r, "3D_PRIORITY_RATE", c->priorityRate, 80.0f);
    GET_FLOAT(r, "3D_ATTENUATION_RANGE", c->attenuationRange, 1.0f);
    return 0;
}
}
