/* The car job controller object file (retail 0x03a2fc to 0x03cf94, "CCarJobCtrlPSP"). It owns
   the cars of a race: the player's cars and the other cars (rivals or ghosts), each kept in an
   array of 10144-byte car objects. It reads the race mode's sequence from the game database,
   builds the car arrays for it, keeps a table of every car and a copy of it sorted by the cars'
   race position, and runs and frees them. */

extern "C" {
void *memcpy(void *, const void *, unsigned int);
void f_00d354(void *log, int level, const char *fmt, ...);
}
extern char D_245178[];

/* A table of the game database (made elsewhere). */
struct CTable {
    void *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
};
extern CTable D_2407d0;
extern unsigned char D_24063c[];
extern const int D_1a211c[];

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
    char m4[2140];
    float m2144;
    char m2148[7996];
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
    CarEntry my[6];
    CarEntry other[13];
};

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
    void *rec = D_2407d0.f_0368e8("SequenceNumber", (char *)mode, 0, 0);
    memcpy(D_24063c, rec, D_1a211c[1]);
    return D_24063c[0];
}

/* @draft 0x03a51c us f_03a51c
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
