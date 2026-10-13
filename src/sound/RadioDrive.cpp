/* The radio DJ drive data object file (retail 0x093814 to 0x093fe0, RadioDrive). It reads the
   radio's per course data: a binary block of 24 course sub-headers (name, offset of the
   corner table and number of points), each course's corner table holding one 16 byte entry
   per point and car class, and the course table row of the game database that gives the
   course's last corner and straight positions and which jumps, corners and drifts the DJ
   talks about. The debug print at the end is empty in the retail build. */

#include <string.h>

/* The game database's tables (their own object file). */
struct CTable {
    int m0;
    int m4;
    int count;
    int m12[3];
    int *index;
    char *f_0368e8(const char *col, const char *row, int colAdd, int rowAdd);
};
extern CTable D_2407a8;
extern "C" char *f_036984(CTable *t, const char *key, int i, int *index, int count);
extern unsigned char D_24063c[];
extern const int D_1a211c[];

/* A record found in a database table. */
struct Rec {
    char *rec;
    int m4;
};

/* One course's sub-header in the binary block. */
struct RadioSub {
    char name[16];
    int corners;            /* offset of the corner table from the block's start */
    unsigned short points;  /* number of points */
    unsigned short m22;
    int m24[2];
};

struct RadioBin {
    int m0[4];
    RadioSub sub[24];
};

/* One corner table entry (a point for one car class). */
struct RadioCorner {
    int m0;
    int m4;
    int m8;
    int m12;
};

void f_093f90(const char *fmt, ...);

class RadioDrive {
public:
    RadioDrive();
    ~RadioDrive();
    int f_09384c(void *data);
    void f_0938a4();
    int f_0938ac(const char *course);
    void f_093b74();
    int f_093bac();
    int f_093bc8(int point, int cls);
    int f_093bf0(int point, int cls);
    int f_093c18(int point, int cls);
    int f_093c40(int point, int cls);
    float f_093c68();
    float f_093c70();
    int f_093c78(int i);
    int f_093c8c(int i);
    int f_093ca0(int i);
    int f_093cb4(int i);
    RadioSub *f_093cc8(int course);
    int f_093d30(int course);
    char *f_093d5c(int course);
    RadioCorner *f_093d88(int course, int point, int cls);
    int f_093e38(int course);
    int f_093e64(int course, int point, int cls);
    int f_093e90(int course, int point, int cls);
    int f_093ebc(int course, int point, int cls);
    int f_093ee8(int course, int point, int cls);
    int f_093f14(int cls);
    void f_093f4c();

    RadioBin *m0;
    int m4;     /* the current course's index, -1 for none */
    int m8;     /* the course's database row */
    float m12;  /* LastCornerRzp */
    float m16;  /* LastStraightRzp */
    int m20[4]; /* DjJump_0..3 */
    int m36[4]; /* JumpLarge_0..3 */
    int m52[3]; /* DJCorner_0..2 */
    int m64[3]; /* DJDrift_0..2 */
};

/* @implements 0x093814 us _ZN10RadioDriveC2Ev
   WHAT IT DOES: Makes a reader with no data and no course (base object constructor). */
/* @implements 0x093828 us _ZN10RadioDriveC1Ev
   WHAT IT DOES: Makes a reader with no data and no course (complete object constructor). */
RadioDrive::RadioDrive()
{
    m8 = 0;
    m0 = 0;
    m4 = -1;
}

/* @implements 0x09383c us _ZN10RadioDriveD2Ev
   WHAT IT DOES: Nothing to release (base object destructor). */
/* @implements 0x093844 us _ZN10RadioDriveD1Ev
   WHAT IT DOES: Nothing to release (complete object destructor). */
RadioDrive::~RadioDrive()
{
}

/* @implements 0x09384c us f_09384c
   WHAT IT DOES: Attaches the binary block, clears the course and the course values. Returns
   0, or -1 when no block was given. */
int RadioDrive::f_09384c(void *data)
{
    int r = -1;
    if (data) {
        m0 = (RadioBin *)data;
        f_093f90("RadioDrive: Init:0x%x \n", data);
        r = 0;
    }
    m4 = -1;
    f_093f4c();
    return r;
}

/* @implements 0x0938a4 us f_0938a4
   WHAT IT DOES: Nothing. */
void RadioDrive::f_0938a4()
{
}

/* @implements 0x0938ac us f_0938ac
   WHAT IT DOES: Selects the course of the given name: finds its sub-header, finds its row of
   the course table and reads the last corner and straight positions and the DJ's jump,
   corner and drift flags. Returns 0, or -1 when there is no such course. */
int RadioDrive::f_0938ac(const char *course)
{
    int i, j;
    if (!course) {
        m4 = -1;
        f_093f90("RadioDrive: Setup Failed! szCourse is NULL \n");
        return -1;
    }
    for (i = 0; i < 24; i++) {
        if (strcmp(f_093d5c(i), course) == 0) {
            m4 = i;
            Rec r;
            if (course)
                r.rec = f_036984(&D_2407a8, course, 0, D_2407a8.index, D_2407a8.count);
            else
                r.rec = 0;
            m8 = (int)r.rec;
            f_093f90("RadioDrive: Setup Course[%s] index[%i]\n", r.rec, m4);
            char *f = D_2407a8.f_0368e8("LastCornerRzp", r.rec, 0, 0);
            int size = D_1a211c[4];
            memcpy(D_24063c, f, size);
            m12 = *(float *)D_24063c;
            memcpy(D_24063c, D_2407a8.f_0368e8("LastStraightRzp", r.rec, 0, 0), size);
            m16 = *(float *)D_24063c;
            for (j = 0; j < 4; j++) {
                char *g = D_2407a8.f_0368e8("DjJump_0", r.rec, j, 0);
                int n = D_1a211c[1];
                memcpy(D_24063c, g, n);
                m20[j] = D_24063c[0];
                memcpy(D_24063c, D_2407a8.f_0368e8("JumpLarge_0", r.rec, j, 0), n);
                m36[j] = D_24063c[0];
            }
            for (j = 0; j < 3; j++) {
                char *g = D_2407a8.f_0368e8("DJCorner_0", r.rec, j, 0);
                int n = D_1a211c[1];
                memcpy(D_24063c, g, n);
                m52[j] = D_24063c[0];
                memcpy(D_24063c, D_2407a8.f_0368e8("DJDrift_0", r.rec, j, 0), n);
                m64[j] = D_24063c[0];
            }
            return 0;
        }
    }
    f_093f90("RadioDrive: Setup Failed! szCourse[%s] is not Found \n", course);
    return -1;
}

/* @implements 0x093b74 us f_093b74
   WHAT IT DOES: Clears the course selection. */
void RadioDrive::f_093b74()
{
    f_093f90("RadioDrive: Reset \n");
    m4 = -1;
    m8 = 0;
}

/* @implements 0x093bac us f_093bac
   WHAT IT DOES: Returns the current course's number of points. */
int RadioDrive::f_093bac()
{
    return f_093e38(m4);
}

/* @implements 0x093bc8 us f_093bc8
   WHAT IT DOES: Returns the first value of the current course's corner entry for a point and
   car class. */
int RadioDrive::f_093bc8(int point, int cls)
{
    return f_093e64(m4, point, cls);
}

/* @implements 0x093bf0 us f_093bf0
   WHAT IT DOES: Returns the second value of the current course's corner entry. */
int RadioDrive::f_093bf0(int point, int cls)
{
    return f_093e90(m4, point, cls);
}

/* @implements 0x093c18 us f_093c18
   WHAT IT DOES: Returns the third value of the current course's corner entry. */
int RadioDrive::f_093c18(int point, int cls)
{
    return f_093ebc(m4, point, cls);
}

/* @implements 0x093c40 us f_093c40
   WHAT IT DOES: Returns the fourth value of the current course's corner entry. */
int RadioDrive::f_093c40(int point, int cls)
{
    return f_093ee8(m4, point, cls);
}

/* @implements 0x093c68 us f_093c68
   WHAT IT DOES: Returns the course's last corner position. */
float RadioDrive::f_093c68()
{
    return m12;
}

/* @implements 0x093c70 us f_093c70
   WHAT IT DOES: Returns the course's last straight position. */
float RadioDrive::f_093c70()
{
    return m16;
}

/* @implements 0x093c78 us f_093c78
   WHAT IT DOES: Whether the DJ talks about jump i. */
int RadioDrive::f_093c78(int i)
{
    return m20[i] != 0;
}

/* @implements 0x093c8c us f_093c8c
   WHAT IT DOES: Whether jump i is a large one. */
int RadioDrive::f_093c8c(int i)
{
    return m36[i] != 0;
}

/* @implements 0x093ca0 us f_093ca0
   WHAT IT DOES: Whether the DJ talks about corner i. */
int RadioDrive::f_093ca0(int i)
{
    return m52[i] != 0;
}

/* @implements 0x093cb4 us f_093cb4
   WHAT IT DOES: Whether the DJ talks about drift i. */
int RadioDrive::f_093cb4(int i)
{
    return m64[i] != 0;
}

/* @implements 0x093cc8 us f_093cc8
   WHAT IT DOES: Returns a course's sub-header, or 0 for a bad index or no data. */
RadioSub *RadioDrive::f_093cc8(int course)
{
    RadioSub *s;
    if ((unsigned int)course < 24) {
        if (m0) {
            s = &m0->sub[course];
        } else {
            f_093f90("RadioDrive: GetSubHeader Failed! BinData is NULL \n");
            s = 0;
        }
    } else {
        f_093f90("RadioDrive: GetSubHeader Failed! Invalid CourseIndex:%d \n", course);
        s = 0;
    }
    return s;
}

/* @implements 0x093d30 us f_093d30
   WHAT IT DOES: Returns a course's corner table offset, or 0. */
int RadioDrive::f_093d30(int course)
{
    RadioSub *s = f_093cc8(course);
    if (s)
        return s->corners;
    return 0;
}

/* @implements 0x093d5c us f_093d5c
   WHAT IT DOES: Returns a course's name, or 0. */
char *RadioDrive::f_093d5c(int course)
{
    RadioSub *s = f_093cc8(course);
    char *n = 0;
    if (s)
        n = s->name;
    return n;
}

/* @implements 0x093d88 us f_093d88
   WHAT IT DOES: Returns a course's corner entry for a point and car class, or 0 for a bad
   point or class. */
RadioCorner *RadioDrive::f_093d88(int course, int point, int cls)
{
    RadioSub *s = f_093cc8(course);
    if (!s)
        return 0;
    if (point < 0 || point >= s->points) {
        f_093f90("RadioDrive: GetCornerAddr Failed! Invalid Point[%d]\n", point);
        return 0;
    }
    int c = f_093f14(cls);
    if (c < 0)
        return 0;
    int k = point * 7 + c;
    return (RadioCorner *)(k * 16 + ((int)m0 + s->corners));
}

/* @implements 0x093e38 us f_093e38
   WHAT IT DOES: Returns a course's number of points, or 0. */
int RadioDrive::f_093e38(int course)
{
    RadioSub *s = f_093cc8(course);
    if (s)
        return s->points;
    return 0;
}

/* @implements 0x093e64 us f_093e64
   WHAT IT DOES: Returns the first value of a corner entry, or -1. */
int RadioDrive::f_093e64(int course, int point, int cls)
{
    RadioCorner *c = f_093d88(course, point, cls);
    if (c)
        return c->m0;
    return -1;
}

/* @implements 0x093e90 us f_093e90
   WHAT IT DOES: Returns the second value of a corner entry, or -1. */
int RadioDrive::f_093e90(int course, int point, int cls)
{
    RadioCorner *c = f_093d88(course, point, cls);
    if (c)
        return c->m4;
    return -1;
}

/* @implements 0x093ebc us f_093ebc
   WHAT IT DOES: Returns the third value of a corner entry, or -1. */
int RadioDrive::f_093ebc(int course, int point, int cls)
{
    RadioCorner *c = f_093d88(course, point, cls);
    if (c)
        return c->m8;
    return -1;
}

/* @implements 0x093ee8 us f_093ee8
   WHAT IT DOES: Returns the fourth value of a corner entry, or -1. */
int RadioDrive::f_093ee8(int course, int point, int cls)
{
    RadioCorner *c = f_093d88(course, point, cls);
    if (c)
        return c->m12;
    return -1;
}

/* @implements 0x093f14 us f_093f14
   WHAT IT DOES: Turns a car class (1 to 7) into a table column (0 to 6), or -1. */
int RadioDrive::f_093f14(int cls)
{
    if (cls >= 1 && cls <= 7)
        return cls - 1;
    f_093f90("RadioDrive: ConvertCarClass Failed! Invalid CarClass:%d \n", cls);
    return -1;
}

/* @implements 0x093f4c us f_093f4c
   WHAT IT DOES: Clears the course values. */
void RadioDrive::f_093f4c()
{
    int i;
    m12 = 0;
    m16 = 0;
    for (i = 0; i < 4; i++) {
        m20[i] = 0;
        m36[i] = 0;
    }
    for (i = 0; i < 3; i++) {
        m52[i] = 0;
        m64[i] = 0;
    }
}

/* @implements 0x093f90 us f_093f90
   WHAT IT DOES: The debug print; empty in the retail build. */
void f_093f90(const char *fmt, ...)
{
}
