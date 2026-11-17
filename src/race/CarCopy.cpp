/* The race car's copy constructors (retail 0x03cf94 to 0x03dd70, the gap object 99, no unwind
   info). The compiler writes both: the race car class (Car::CRidgeCar) and the base object below
   it each copy themselves member by member, emitted out of line in link once sections. Neither
   can throw (every member copy is trivial), so neither gets an unwind entry, which is why the
   object shows no .eh_frame CIE.

   The copy pattern gives the members: scalars are copied one by one (lw/sw, lwc1/swc1 for
   floats, lh/sh, lb/sb, lbu/sb), plain arrays and records as one block (16-byte loops past 32
   bytes), and arrays of a class with a constructor element by element in a counted loop. Each
   group whose first member sits on a 16-byte boundary after a gap starts a 16-byte aligned
   record in the original; its members are kept here as direct members. */

extern char D_1aef10[];
extern char D_1acab8[];

inline void *operator new(unsigned int, void *p) { return p; }

/* A 16-byte vector element with a constructor (arrays of it are copied in a counted loop). */
struct CarVec {
    int x, y, z, w;
    CarVec();
} __attribute__((aligned(16)));

/* A 64-byte matrix element with a constructor. */
struct CarMtx {
    int m[16];
    CarMtx();
};

/* Six bytes copied as one record (byte aligned). */
struct CarBytes6 {
    signed char b[6];
};

/* A matrix row. */
struct CarRow {
    float x, y, z, w;
};

/* A 3-row matrix whose copy constructor copies row by row (the rows are elements of one array,
   so each row copy waits for the one before). */
struct CarMtx34 {
    CarRow v[3];
    CarMtx34();
    CarMtx34(const CarMtx34 &o)
    {
        v[0] = o.v[0];
        v[1] = o.v[1];
        v[2] = o.v[2];
    }
};

/* The same with four rows. */
struct CarMtx44 {
    CarRow v[4];
    CarMtx44();
    CarMtx44(const CarMtx44 &o)
    {
        v[0] = o.v[0];
        v[1] = o.v[1];
        v[2] = o.v[2];
        v[3] = o.v[3];
    }
};

/* The vtable pointer of the base object, set by its copy constructor. */
struct CarBaseVt {
    void *vptr;
    CarBaseVt();
    CarBaseVt(const CarBaseVt &) { vptr = D_1aef10; }
};

#define A16 __attribute__((aligned(16)))

/* The base object of the race car (7680 bytes). */
struct CarBase : CarBaseVt {
    int m4[4];
    int m20;
    int m24[4];
    unsigned char m40;
    float m44;
    unsigned char m48;
    float m52;
    unsigned char m56, m57;
    short m58[2];
    short m62[4];
    float m72;
    int m76, m80, m84, m88;
    int m92[3];
    CarBytes6 m104;
    short m110[7];
    int m124, m128;
    CarMtx34 m144 A16;
    float m192;
    int m208[4] A16;
    int m224[8];
    CarVec m256[4];
    CarVec m320[4];
    CarVec m384[4];
    CarVec m448[4];
    CarVec m512[4];
    char m576[576];
    CarMtx m1152[9];
    int m1728[2];
    float m1736, m1740, m1744, m1748;
    int m1752;
    float m1756, m1760;
    int m1764[3];
    int m1776[4];
    float m1792;
    int m1796, m1800, m1804;
    float m1808, m1812;
    int m1816;
    float m1820, m1824;
    int m1828;
    float m1832;
    int m1836[3];
    int m1856[4] A16;
    int m1872[4];
    int m1888, m1892;
    float m1896, m1900;
    CarMtx34 m1904;
    int m1952, m1956;
    float m1960, m1964;
    int m1968, m1972, m1976;
    float m1980, m1984;
    CarVec m2000[4];
    int m2064[4];
    int m2080[4];
    float m2096, m2100;
    int m2104, m2108, m2112;
    float m2116;
    int m2120, m2124;
    char m2128[617];
    int m2752 A16;
    char m2756[264];
    int m3020, m3024, m3028;
    char m3040[2729] A16;
    int m5776 A16;
    int m5780;
    char m5792[1880] A16;
};

/* The race car's vtable pointer, stored after the base object is copied. */
struct CarVt : CarBase {
    CarVt();
    CarVt(const CarVt &o) : CarBase(o) { vptr = D_1acab8; }
};

namespace Car {

/* The race car (10116 bytes of data). */
struct CRidgeCar : CarVt {
    int m7680[2] A16;
    int m7688, m7692;
    char m7696[80];
    char m7776[40];
    char m7816[180];
    char m7996[56];
    char m8064[1500] A16;
    int m9568 A16;
    float m9572, m9576;
    int m9580, m9584, m9588;
    int m9592[4];
    int m9608[4];
    int m9624[2];
    int m9632[2];
    int m9640;
    int m9644[2];
    int m9652[2];
    int m9660[2];
    float m9668;
    int m9672;
    int m9676[2];
    int m9684[2];
    int m9692, m9696, m9700, m9704, m9708;
    float m9712, m9716;
    int m9720;
    float m9724;
    int m9728[4];
    int m9744[2];
    int m9752[4];
    float m9768, m9772;
    int m9776;
    char m9792[48] A16;
    char m9840[48];
    float m9888, m9892, m9896, m9900;
    int m9904, m9908, m9912, m9916;
    float m9920, m9924, m9928, m9932, m9936, m9940, m9944, m9948;
    CarMtx44 m9952;
    float m10016, m10020;
    float m10024, m10028, m10032, m10036, m10040;
    int m10044;
    float m10048;
    int m10052;
    float m10056, m10060, m10064, m10068;
    int m10072;
    float m10076, m10080, m10084;
    int m10088;
    float m10092, m10096, m10100, m10104, m10108, m10112;
};

}

/* The player's car class, which copies the race car as its base (its own copy is made in
   CarJobCtrl.cpp); it is here only so the compiler emits the race car's copy constructor. */
struct CarCopyUser : Car::CRidgeCar {
    int m10116;
};

void CarCopyUse(CarCopyUser *d, const CarCopyUser &s)
{
    new ((void *)d) CarCopyUser(s);
}

/* @draft 0x03cf94 us CRidgeCarC2ERKS0_
   WHAT IT DOES: Copies a race car: copies the base object (below), sets the race car's vtable
   pointer, then copies every race car member from +7680 to +10116.
   Remaining difference: the 4x4 matrix at +9952 is copied through a pointer to it (the inlined
   row-by-row copy constructor's this), which retail addresses from the car directly; the extra
   pointers cost two saved registers and shift the schedule. */

/* @draft 0x03d528 us CarBaseC2ERKS_
   WHAT IT DOES: Copies the race car's base object: sets its vtable pointer and copies every
   member from +4 to +7672.
   Remaining difference: as in the race car copy, the two 3-row matrices (+144, +1904) are copied
   through pointers retail does not have; and the vtable pointer store is scheduled earlier than
   retail's (here a plain void * member of a separate base, not a real vtable pointer). */
