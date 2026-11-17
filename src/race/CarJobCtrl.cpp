/* The car job controller object file (retail 0x03a2fc to 0x03cf94, "CCarJobCtrlPSP"). It owns
   the cars of a race: the player's cars and the other cars (rivals or ghosts), each kept in an
   array of 10144-byte car objects. It reads the race mode's sequence from the game database,
   builds the car arrays for it, keeps a table of every car and a copy of it sorted by the cars'
   race position, and runs and frees them. */

extern "C" {
void *memcpy(void *, const void *, unsigned int);
char *strcpy(char *, const char *);
void f_00d354(void *log, int level, const char *fmt, ...);
unsigned int sceKernelGetSystemTimeLow(void);
}
extern char D_245178[];

/* A table of the game database (made elsewhere). */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
    void *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
};
extern CTable D_2407d0;
extern CTable D_2407a8;
extern unsigned char D_24063c[];
extern const int D_1a211c[];
extern "C" char *f_036984(CTable *t, char *name, int i, int *index, int count);

/* A row of a table as the lookups pass it on. */
struct Row {
    char *rec;
    int m4;
};

/* The time, read through a volatile local. */
static inline unsigned Now()
{
    volatile unsigned t = sceKernelGetSystemTimeLow();
    return t;
}

/* A car's sub object (made elsewhere): a car points at the sub objects of the cars around it
   in the race order. */
struct CarSub {
    char m0[472];
    int m472;
};

struct Pad;
/* A vector of four floats. */
struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* A car (made elsewhere); its constructors are those of the player's car and the two kinds of
   other cars. */
struct CCar {
    virtual ~CCar();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void f_v13();
    virtual void v56();
    virtual int v60();
    virtual void v64();
    virtual int v68();
    virtual void v72();
    int Active() { return m76; }
    char m4[72];
    int m76;
    int m80;
    char m84[16];
    int m100;
    char m104[6];
    char m110[14];
    int m124;
    char m128[2016];
    float m2144;
    char m2148[3628];
    int m5776;
    int m5780;
    char m5784[8];
    char m5792[472];
    int m6264;
    char m6268[668];
    CarSub *m6936;
    CarSub *m6940;
    char m6944[20];
    int m6964;
    int m6968;
    char m6972[20];
    CarSub *m6992;
    CarSub *m6996;
    char m7000[20];
    int m7020;
    int m7024;
    char m7028[792];
    int m7820;
    char m7824[1880];
    int m9704;
    char m9708[4];
    float m9712;
    float m9716;
    int m9720;
    char m9724[196];
    float m9920;
    float m9924;
    char m9928[160];
    int m10088;
    char m10092[24];
    Pad *m10116;           /* the input record */
    Vec4 m10128;
} __attribute__((aligned(16)));

/* The player's cars and the other cars. */
struct CCarMine : CCar {
};
struct CCarOther : CCar {
};

extern "C" {
void f_0eda14(CCar *);
void f_0ed58c(CCar *);
void f_0ed938(CCar *);
void f_0bfb30(void *);
void f_0c1a14(void *);
void f_0c07e0(void *);
}

/* The array elements as they are built: each runs the car kind's own constructor. */
struct CMyCar {
    char m[10144];
    CMyCar() { f_0bfb30(this); }
    ~CMyCar() { ((CCar *)this)->~CCar(); }
} __attribute__((aligned(16)));
struct CRivalCar {
    char m[10144];
    CRivalCar() { f_0c1a14(this); }
    ~CRivalCar() { ((CCar *)this)->~CCar(); }
} __attribute__((aligned(16)));
struct CGhostCar {
    char m[10144];
    CGhostCar() { f_0c07e0(this); }
    ~CGhostCar() { ((CCar *)this)->~CCar(); }
} __attribute__((aligned(16)));

/* One entry of the list of cars to make. */
struct CarEntry {
    int m0;
    int m4;
};

/* What the race passes in: its mode and course, then the player's and the other cars. */
struct CarSetup {
    int m0;
    int m4;
};
struct CarList {
    CarEntry my[2];
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    CarEntry other[13];
    int m152[13];
    int m204[13];
    int m256;
    int m260;
    int m264;
    int m268;
    int m272[13];
    int m324[13];
    char m376[13][20];
};

/* The rubber banding table of the game (made elsewhere): three rows of curve points, one per
   kind of other car (the first row also keeps the slopes), and more floats and ints as seen
   by the other functions. */
union Tune {
    float f[64];
    int i[64];
};
extern Tune D_240af4;

/* Reads one of the curve points of row j of the table (the row of a car that is not 0, 1 or 2
   is left unread). */
static inline float Top(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[14]; break;
    case 1: r = D_240af4.f[41]; break;
    case 2: r = D_240af4.f[54]; break;
    }
    return r;
}
static inline float Hi(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[16]; break;
    case 1: r = D_240af4.f[43]; break;
    case 2: r = D_240af4.f[56]; break;
    }
    return r;
}
static inline float Lo(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[15]; break;
    case 1: r = D_240af4.f[42]; break;
    case 2: r = D_240af4.f[55]; break;
    }
    return r;
}
static inline float SlopeUp(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[17]; break;
    case 1: r = (D_240af4.f[41] - 1.0f) / (D_240af4.f[43] - D_240af4.f[42]); break;
    case 2: r = (D_240af4.f[54] - 1.0f) / (D_240af4.f[56] - D_240af4.f[55]); break;
    }
    return r;
}
static inline float Bot(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[10]; break;
    case 1: r = D_240af4.f[38]; break;
    case 2: r = D_240af4.f[51]; break;
    }
    return r;
}
static inline float Lo2(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[11]; break;
    case 1: r = D_240af4.f[39]; break;
    case 2: r = D_240af4.f[52]; break;
    }
    return r;
}
static inline float Hi2(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[12]; break;
    case 1: r = D_240af4.f[40]; break;
    case 2: r = D_240af4.f[53]; break;
    }
    return r;
}
static inline float SlopeDown(int j)
{
    float r;
    switch (j) {
    case 0: r = D_240af4.f[13]; break;
    case 1: r = (1.0f - D_240af4.f[38]) / (D_240af4.f[40] - D_240af4.f[39]); break;
    case 2: r = (1.0f - D_240af4.f[51]) / (D_240af4.f[53] - D_240af4.f[52]); break;
    }
    return r;
}

extern int D_2408f4;
extern char D_24186d;
extern char D_241760[];

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
    Vec4 rot;

    void Init()
    {
        m0 = 0;
        m4 = 0;
        m8 = 2000.0f;
        m12 = 0;
        m42 = 1;
    }
    void f_0849a4(CCar *car);
};
class CNetRacePacket {
public:
    void f_083fa8(unsigned int ch, CarState *car, char *b);
};
extern CNetRacePacket D_241804;

extern "C" {
void f_0c2c44(int n, void *me, void *cars);
void f_0bfe38(CCar *);
void f_0b9d28(void *car, int a, int b);
void f_0c3514(int n, CCar *player, CCar *c);
void f_0c3e34(int n, CCar **cars);
void f_0c40b4(int n, CCar **cars);
void f_0c7dc4(int n, CCar **cars);
void f_0c38f8(int n, CCar *cars, int flag);
void f_03cf94(void *dst, void *src);
int f_0bfcd4(void *);
void f_0b9c78(void *);
void f_0b6dd4(void *);
void f_0bfba4(void *);
}
extern char D_1acd08[];

/* A copy of a car on the stack. The player's car class copies its base class (made elsewhere),
   sets its own vtable, then copies its two members (the copy constructor the compiler writes:
   the input record pointer, and the vector as one 16-byte block). */
struct CCarCopy {
    char m[10116];
    Pad *m10116;
    Vec4 m10128;
    CCarCopy(CCar *c)
    {
        f_03cf94(this, c);
        *(void **)this = D_1acd08;
        m10116 = c->m10116;
        m10128 = c->m10128;
    }
    ~CCarCopy() { f_0bfba4(this); }
} __attribute__((aligned(16)));

struct CCarJobCtrlPSP {
    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
    CCarMine *m20;
    CCarOther *m24;
    CCar **m28;
    CCar **m32;
    int m36;
    int m40;
    int m44;
    int m48;

    CCarJobCtrlPSP();
    ~CCarJobCtrlPSP();
    void f_03a51c(CarSetup *s, int a, CarList *l);
    void f_03a70c();
    void f_03b400();
    CCar *f_03b518(int i);
    CCar *f_03b530(int i);
    CCar *f_03b548(int i);
    int f_03b55c(int i);
    void f_03b614();
    void f_03b640(CarList *l, int ghost);
    void f_03b9bc();
    void f_03bab8();
    void f_03bbb4();
    void f_03bc38(CarList *l);
    void f_03c340(CarList *l);
    void f_03c8c8(CarList *l);
};

/* @implements 0x03a2fc us CCarJobCtrlPSPC2E
   WHAT IT DOES: Constructs the controller with everything empty. */
/* @implements 0x03a31c us CCarJobCtrlPSPC1E
   WHAT IT DOES: The complete-object copy of the constructor above. */
CCarJobCtrlPSP::CCarJobCtrlPSP()
{
    m36 = 0;
    f_03b614();
}

/* @implements 0x03a33c us CCarJobCtrlPSPD2E
   WHAT IT DOES: Destroys the controller: frees the two car tables and the two car arrays (each
   car destroyed). */
/* @implements 0x03a42c us CCarJobCtrlPSPD1E
   WHAT IT DOES: The complete-object copy of the destructor above. */
CCarJobCtrlPSP::~CCarJobCtrlPSP()
{
    if (m32)
        delete[] m32;
    if (m28)
        delete[] m28;
    delete[] m24;
    delete[] m20;
}

/* Reads the sequence number of a race mode from the game database. */
static inline int Sequence(int mode)
{
    /* The key in a local: its address is formed before the database's, which ends the high
       half's life one insn sooner and gives it s6 ahead of the list argument in f_03a51c. */
    const char *name = "SequenceNumber";
    void *rec = D_2407d0.f_0368e8(name, (char *)mode, 0, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    return D_24063c[0];
}

/* @implements 0x03a51c us f_03a51c
   WHAT IT DOES: Sets the controller up for a race: clears it, keeps the race mode and course
   and the random seed, reads the mode's car flags and sequence number from the game database
   and builds the cars the sequence needs (logging an error for an unknown sequence), then
   sorts the cars. */
void CCarJobCtrlPSP::f_03a51c(CarSetup *s, int seed, CarList *l)
{
    f_03b614();
    m0 = s->m0;
    m4 = s->m4;
    m40 = seed;
    m36 = seed;
    void *rec = D_2407d0.f_0368e8("CCar_Each", (char *)m0, 0, 0);
    int size = D_1a211c[1];
    memcpy(D_24063c, rec, size);
    int each = D_24063c[0];
    int mode = s->m0;
    m48 = each;
    memcpy(D_24063c, D_2407d0.f_0368e8("SequenceNumber", (char *)mode, 0, 0), size);
    switch (D_24063c[0]) {
    case 1:
    case 4:
    case 5:
        m8 = 3;
        f_03bc38(l);
        break;
    case 2:
        m8 = 1;
        f_03c340(l);
        break;
    case 3:
        m8 = 3;
        f_03c8c8(l);
        break;
    default: {
        int mode = s->m0;
        f_00d354(D_245178, 0x4000, "Error(%s): %s = %d, %s = %d\n", "CCarJobCtrlPSP::Init", "mode_num", mode,
                 "sequence", Sequence(mode));
        break;
    }
    }
    f_03bab8();
}

/* @implements 0x03a70c us f_03a70c
   WHAT IT DOES: Runs the cars for one frame, timing it. The cars in use are started (the
   player's cars also run the rubber band against the other cars and, when the car is in the
   state 0x1001, every third frame a copy of it is stepped to send its state over the wireless
   link), the other cars are started and ranked against the player, the table of every car is
   sorted, the neighbours of each car in the race order are recorded, the other cars' speed
   factors are worked out from their distance to the player through the rubber band table, and
   every car is stepped through the virtual steps (the collision steps first when the mode
   has bit 2). */
void CCarJobCtrlPSP::f_03a70c()
{
    if (m8 == 0)
        return;
    unsigned start = Now();
    if (m20) {
        for (int i = 0; i < m12; i++) {
            if (m20[i].Active()) {
                f_0c2c44(m16, m20, m24);
                f_0bfe38(&m20[i]);
                f_0b9d28(&m20[i], m20->m124, 0);
                m20[i].v2();
                CCar *car = &m20[i];
                if (car->m80 == 0x1001) {
                    int id = car->m100;
                    if (++D_2408f4 % 3 == 0) {
                        CCarCopy tmp(car);
                        CCar *list[1];
                        list[0] = (CCar *)&tmp;
                        f_0c3e34(1, list);
                        if (((CCar *)&tmp)->m76 && f_0bfcd4(&tmp))
                            f_0b9c78(&tmp);
                        f_0c40b4(1, list);
                        f_0b6dd4(&tmp);
                        CarState st;
                        st.Init();
                        st.f_0849a4((CCar *)&tmp);
                        if (D_24186d == 7)
                            D_241804.f_083fa8(id, &st, D_241760);
                    }
                }
            }
        }
    }
    if (m24) {
        for (int i = 0; i < m16; i++) {
            if (m24[i].Active())
                f_0b9d28(&m24[i], m20->m124, 0);
        }
        if (m24->m80 == 0x2002) {
            f_0c38f8(m16, m24, 0);
            f_0c3514(m16, m20, m24);
        } else
            f_0c3514(m16, m20, m24);
    }
    f_03bab8();
    if (m16 > 0 && f_03b518(0)->m80 == 1) {
        int n = m12 + m16;
        for (int i = 0; i < n; i++) {
            {
                CCar *me = m28[i];
                CCar *p1 = m28[(i + n - 1) % n];
                if (p1) {
                    me->m6936 = (CarSub *)((char *)p1 + 5792);
                    me->m6964 = me->m6264 - p1->m6264;
                } else
                    me->m6936 = 0;
            }
            {
                CCar *me = m28[i];
                CCar *p2 = n < 3 ? 0 : m28[(i + n - 2) % n];
                if (p2) {
                    me->m6940 = (CarSub *)((char *)p2 + 5792);
                    me->m6968 = me->m6264 - p2->m6264;
                } else
                    me->m6940 = 0;
            }
            {
                CCar *me = m28[i];
                CCar *n1 = m28[(i + 1) % n];
                if (n1) {
                    me->m6992 = (CarSub *)((char *)n1 + 5792);
                    me->m7020 = n1->m6264 - me->m6264;
                } else
                    me->m6992 = 0;
            }
            {
                CCar *me = m28[i];
                CCar *n2 = n < 3 ? 0 : m28[(i + 2) % n];
                if (n2) {
                    me->m6996 = (CarSub *)((char *)n2 + 5792);
                    me->m7024 = n2->m6264 - me->m6264;
                } else
                    me->m6996 = 0;
            }
        }
        if (m48) {
            for (int j = 0; j < m16; j++) {
                float d = (float)f_03b530(j)->m6264 * 0.009765f - (float)f_03b518(0)->m6264 * 0.009765f;
                float f = 1.0f;
                if (0.0f < d) {
                    if (Hi(j) < d)
                        f = Top(j);
                    else if (Lo(j) < d)
                        f = (d - Lo(j)) * SlopeUp(j) + 1.0f;
                } else {
                    if (d < Lo2(j))
                        f = Bot(j);
                    else if (d < Hi2(j))
                        f = (d - Hi2(j)) * SlopeDown(j) + 1.0f;
                }
                if (0.0f < m24[j].m9712 && m20->m124 != 2) {
                    m24[j].m9712 = m24[j].m9712 - 0.016666668f;
                    m24[j].m9924 = f * m24[j].m9716;
                } else
                    m24[j].m9924 = f;
            }
        } else {
            float d = (float)f_03b530(D_240af4.i[60])->m6264 * 0.009765f - (float)f_03b518(0)->m6264 * 0.009765f;
            float f = 1.0f;
            if (0.0f < d) {
                if (D_240af4.f[16] < d)
                    f = D_240af4.f[14];
                else if (D_240af4.f[15] < d)
                    f = (d - D_240af4.f[15]) * D_240af4.f[17] + 1.0f;
            } else {
                if (d < D_240af4.f[11])
                    f = D_240af4.f[10];
                else if (d < D_240af4.f[12])
                    f = (d - D_240af4.f[12]) * D_240af4.f[13] + 1.0f;
            }
            for (int j = 0; j < m16; j++) {
                if (0.0f < m24[j].m9712 && m20->m124 != 2) {
                    m24[j].m9712 = m24[j].m9712 - 0.016666668f;
                    m24[j].m9924 = f * m24[j].m9716;
                } else
                    m24[j].m9924 = f;
            }
        }
    }
    f_0c3e34(m12 + m16, m28);
    if (m8 & 2) {
        f_0c7dc4(m12 + m16, m28);
        if (m20) {
            for (int i = 0; i < m12; i++) {
                if (m20[i].Active() && m20[i].v60())
                    m20[i].v64();
            }
        }
        if (m24) {
            for (int i = 0; i < m16; i++) {
                if (m24[i].Active() && m24[i].v60())
                    m24[i].v64();
            }
        }
    }
    if (m20) {
        for (int i = 0; i < m12; i++) {
            if (m20[i].Active() && m20[i].v68())
                m20[i].v72();
        }
    }
    if (m24) {
        for (int i = 0; i < m16; i++) {
            if (m24[i].Active() && m24[i].v68())
                m24[i].v72();
        }
    }
    f_0c40b4(m12 + m16, m28);
    if (m20) {
        for (int i = 0; i < m12; i++) {
            if (m20[i].Active())
                m20[i].v11();
        }
    }
    if (m24) {
        for (int i = 0; i < m16; i++) {
            if (m24[i].Active())
                m24[i].v11();
        }
    }
    if (m20->m80 == 0x1001)
        f_0c38f8(m16, m24, 1);
    start = Now() - start;
    m44 = start;
}

/* @implements 0x03b400 us f_03b400
   WHAT IT DOES: Shuts the cars down: a virtual call on every car, then each car's own stop
   routine, then frees the arrays and clears the controller. */
void CCarJobCtrlPSP::f_03b400()
{
    int i;
    for (i = 0; i < m12; i++)
        m20[i].f_v13();
    for (i = 0; i < m16; i++)
        m24[i].f_v13();
    for (i = 0; i < m12; i++)
        f_0eda14(&m20[i]);
    for (i = 0; i < m16; i++)
        f_0eda14(&m24[i]);
    f_03b9bc();
    f_03b614();
}

/* @implements 0x03b518 us f_03b518
   WHAT IT DOES: Returns the player's car with the given index. */
CCar *CCarJobCtrlPSP::f_03b518(int i)
{
    return &m20[i];
}

/* @implements 0x03b530 us f_03b530
   WHAT IT DOES: Returns the other car with the given index. */
CCar *CCarJobCtrlPSP::f_03b530(int i)
{
    return &m24[i];
}

/* @implements 0x03b548 us f_03b548
   WHAT IT DOES: Returns the car in the given slot of the table of every car. */
CCar *CCarJobCtrlPSP::f_03b548(int i)
{
    return m28[i];
}

/* @implements 0x03b55c us f_03b55c
   WHAT IT DOES: Returns the slot of the given player's car in the table of every car (its
   race position once sorted); 0 when there is no table, -1 with a warning when it is not in
   it. */
int CCarJobCtrlPSP::f_03b55c(int n)
{
    if (m28) {
        CCar *me = f_03b518(n);
        int count = m12 + m16;
        int i;
        for (i = 0; i < count; i++) {
            if (me == f_03b548(i))
                return i;
        }
        f_00d354(D_245178, 16, "Warning(%s): %s\n", "CCarJobCtrlPSP::GetMyCarPosition", "Buffer not found");
        return -1;
    }
    return 0;
}
/* @implements 0x03b614 us f_03b614
   WHAT IT DOES: Clears the controller's mode, counts, arrays and tables. */
void CCarJobCtrlPSP::f_03b614()
{
    m8 = 0;
    m12 = 0;
    m16 = 0;
    m20 = 0;
    m24 = 0;
    m28 = 0;
    m32 = 0;
    m36 = 0;
    m40 = 0;
    m44 = 0;
}

/* @implements 0x03b640 us f_03b640
   WHAT IT DOES: Builds the car arrays from the list of cars to make: counts the player's cars
   (at most 2) and the other cars (at most 13), makes the player's cars and then the other cars
   (rivals, or ghosts when the flag is clear), and fills the table of every car and its sorted
   copy with the player's cars first. With no player's car it logs an error. */
void CCarJobCtrlPSP::f_03b640(CarList *l, int rival)
{
    int i;
    int n = 0;
    for (i = 0; i < 2; i++) {
        if (!l->my[i].m0)
            break;
        n++;
    }
    if (n > 0) {
        m12 = n;
        m20 = (CCarMine *)new CMyCar[n];
    } else {
        f_00d354(D_245178, 16, "Error(%s): %s = %d\n", "CCarJobCtrlPSP::CreateBuffers", "m_iNumMyCars", n);
    }
    for (i = 0, n = 0; i < 13; i++) {
        if (!l->other[i].m0)
            break;
        n++;
    }
    if (n > 0) {
        m16 = n;
        if (rival)
            m24 = (CCarOther *)new CRivalCar[n];
        else
            m24 = (CCarOther *)new CGhostCar[n];
    } else {
        m16 = 0;
        m24 = 0;
    }
    m28 = new CCar *[m12 + m16];
    for (i = 0; i < m12; i++)
        m28[i] = &m20[i];
    for (i = 0; i < m16; i++)
        m28[m12 + i] = &m24[i];
    m32 = new CCar *[m12 + m16];
    for (i = 0; i < m12; i++)
        m32[i] = &m20[i];
    for (i = 0; i < m16; i++)
        m32[m12 + i] = &m24[i];
}

/* @implements 0x03b9bc us f_03b9bc
   WHAT IT DOES: Frees the two car tables and the two car arrays (each car destroyed) and
   clears their pointers and counts. */
void CCarJobCtrlPSP::f_03b9bc()
{
    if (m32)
        delete[] m32;
    m32 = 0;
    if (m28)
        delete[] m28;
    m28 = 0;
    delete[] m24;
    m24 = 0;
    m16 = 0;
    delete[] m20;
    m20 = 0;
    m12 = 0;
}

/* @implements 0x03bab8 us f_03bab8
   WHAT IT DOES: Sorts the table of every car by each car's race progress, highest first (an
   insertion sort from the end); with no table it only warns, in the modes that sort. */
void CCarJobCtrlPSP::f_03bab8()
{
    if (m28 == 0) {
        if (m8 & 2)
            f_00d354(D_245178, 16, "Warning(%s): %s = %d, (%s)\n", "CCarJobCtrlPSP::Sorting", "m_iMode", m8,
                     "Nothing SortCarBuffers");
        return;
    }
    if (m8 & 2) {
        int n = m12 + m16;
        int i;
        for (i = n - 1; i > 0; i--) {
            CCar *c = m28[i - 1];
            float k = c->m2144;
            int j;
            for (j = i; j < n; j++) {
                CCar *o = m28[j];
                if (!(k < o->m2144))
                    break;
                m28[j - 1] = o;
            }
            if (j != i)
                m28[j - 1] = c;
        }
    }
}

/* @implements 0x03bbb4 us f_03bbb4
   WHAT IT DOES: Runs two per-car routines on every car of the second table. */
void CCarJobCtrlPSP::f_03bbb4()
{
    int i;
    for (i = 0; i < m12 + m16; i++) {
        f_0ed58c(m32[i]);
        f_0ed938(m32[i]);
    }
}
