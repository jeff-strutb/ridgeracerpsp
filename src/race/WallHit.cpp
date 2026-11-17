/* The course wall hits, Map::WallHit::CManagerBase and CManager (retail 0x0c5938 to 0x0c6078):
   the wall polygons loaded from the course's "WallHit" data (a polygon set, another object
   file's class), plus up to 128 extra walls added at run time, each an 8 point outline with
   its bounding box, found through a slot table. One global instance (D_246700). */

extern "C" {
void f_0c6078(void *set, void *data);
void f_0c61b4(void *set);
int f_0c6580(void *set, void **found, int max, float x, float z);
}

struct Vec4 {
    float x, y, z, w;
};

namespace Map {
namespace WallHit {

/* A set of wall polygons searched by position. */
struct PolySet {
    PolySet()
    {
        m0 = 0;
        m4 = 0;
        m8 = 0;
        m12 = 0;
        m16 = 0;
        m20 = 0;
    }
    ~PolySet() { f_0c61b4(this); }
    int m0, m4, m8, m12, m16, m20;
};

struct Point {
    float x, z;
};

/* A wall added at run time (84 bytes): its outline and bounding box. */
struct Wall {
    int count;
    Point pt[8];
    float minx, minz;
    float maxx, maxz;
};

class CManagerBase {
public:
    CManagerBase() : m4(0) {}
    virtual ~CManagerBase() { f_0c5954(); }
    virtual void f_0c5938(void *data);
    void f_0c5954();
    int f_0c5970(void **found, Vec4 *pos, int max);
    int f_0c5998(void **found, Vec4 *pos, int max, int *nPoly);
    int f_0c5b04(float a, float b, float w, float d);
    void f_0c5cf4(int id);

    int m4;
    PolySet set;
    int count;
    int slot[128];
    Wall wall[128];
};

class CManager : public CManagerBase {
public:
    CManager()
    {
        count = 0;
        for (int i = 0; i < 128; i++)
            slot[i] = -1;
    }
    virtual ~CManager() {}
    virtual void f_0c5938(void *data);
};

/* @implements 0x0c5938 us _ZN3Map7WallHit12CManagerBase8f_0c5938EPv
   WHAT IT DOES: Loads the course's wall polygons. */
void CManagerBase::f_0c5938(void *data)
{
    f_0c6078(&set, data);
}

/* @implements 0x0c5954 us _ZN3Map7WallHit12CManagerBase8f_0c5954Ev
   WHAT IT DOES: Frees the course's wall polygons. */
void CManagerBase::f_0c5954()
{
    f_0c61b4(&set);
}

/* @implements 0x0c5970 us _ZN3Map7WallHit12CManagerBase8f_0c5970EPPvP4Vec4i
   WHAT IT DOES: Finds up to max course wall polygons under a point; returns how many. */
int CManagerBase::f_0c5970(void **found, Vec4 *pos, int max)
{
    return f_0c6580(&set, found, max, pos->x, pos->z);
}

/* @implements 0x0c5998 us _ZN3Map7WallHit12CManagerBase8f_0c5998EPPvP4Vec4iPi
   WHAT IT DOES: Finds the course wall polygons under a point (their count stored through
   nPoly when given), then appends the outline points of every added wall whose box holds the
   point and that lie within 15000 of it (from the third point to the third last). At most 64
   are stored and counted. */
int CManagerBase::f_0c5998(void **found, Vec4 *pos, int max, int *nPoly)
{
    int n = f_0c6580(&set, found, max, pos->x, pos->z);
    int k, j;

    if (nPoly)
        *nPoly = n;
    Wall *w = wall;
    for (k = 0; k < count; k++, w++) {
        if (w->minx <= pos->x && pos->x <= w->maxx && w->minz <= pos->z && pos->z <= w->maxz) {
            for (j = 2; j < w->count - 2; j++) {
                float dx = pos->x - w->pt[j].x;
                float dz = pos->z - w->pt[j].z;
                if (dx * dx + dz * dz < 225000000.0f) {
                    if (n < 64)
                        found[n] = &w->pt[j];
                    n++;
                }
            }
        }
    }
    if (n > 64)
        n = 64;
    return n;
}

/* @draft 0x0c5b04 us _ZN3Map7WallHit12CManagerBase8f_0c5b04Effff
   DRAFT: two words differ, the register holding the wall size 84 for the multiply (v0 in
   retail, a1 here); every ordering of the count and slot statements tried keeps it.
   Named cause (lreg dump): local-alloc's combine_regs ties the constant 84 (r199, dies in
   the multiply insn 78) into the product's quantity (r198), which is also tied to the wall
   address (r200), so all three get a1. Retail has the product and address tied (a1) but not
   the constant (v0), so in retail the multiply's dying input was not tieable (or the
   product's quantity was taken first). No source shape identified; no change made.
   WHAT IT DOES: Adds a wall in the first free slot: an 8 point outline and its bounding box
   grown by 15000 on every side. Returns the slot. */
int CManagerBase::f_0c5b04(float a, float b, float w, float d)
{
    int id = -1;
    int i;

    for (i = 0; i < 128; i++) {
        if (slot[i] == -1) {
            id = i;
            break;
        }
    }
    int n = count;
    Wall *e = wall + n;
    slot[id] = n;
    n++;
    count = n;
    Vec4 p[8] = {
        { w, 0, d, 1.0f }, { w, 0, -d, 1.0f }, { -w, 0, -d, 1.0f }, { -w, 0, d, 1.0f },
        { w, 0, d, 1.0f }, { w, 0, -d, 1.0f }, { -w, 0, -d, 1.0f }, { -w, 0, d, 1.0f },
    };
    Vec4 t;
    e->count = 8;
    for (i = 0; i < e->count; i++) {
        e->pt[i].x = t.x;
        e->pt[i].z = t.z;
        if (i == 0) {
            e->maxx = e->pt[0].x;
            e->maxz = e->pt[0].z;
            e->minx = e->pt[0].x;
            e->minz = e->pt[0].z;
        } else {
            if (e->pt[i].x < e->minx)
                e->minx = e->pt[i].x;
            if (e->pt[i].z < e->minz)
                e->minz = e->pt[i].z;
            if (e->maxx < e->pt[i].x)
                e->maxx = e->pt[i].x;
            if (e->maxz < e->pt[i].z)
                e->maxz = e->pt[i].z;
        }
    }
    e->minx -= 15000.0f;
    e->minz -= 15000.0f;
    e->maxx += 15000.0f;
    e->maxz += 15000.0f;
    return id;
}

/* @implements 0x0c5cf4 us _ZN3Map7WallHit12CManagerBase8f_0c5cf4Ei
   WHAT IT DOES: Removes the wall in a slot: the last wall moves into its place and the slot
   that held the last wall is pointed there; the slot is freed. */
void CManagerBase::f_0c5cf4(int id)
{
    int i;

    count--;
    for (i = 0; i < 128; i++) {
        if (count == slot[i]) {
            if (id != i) {
                wall[slot[id]] = wall[count];
                slot[i] = slot[id];
            }
            break;
        }
    }
    slot[id] = -1;
}

/* @implements 0x0c6034 us _ZN3Map7WallHit8CManager8f_0c5938EPv
   WHAT IT DOES: Loads the course's wall polygons and removes every added wall. */
void CManager::f_0c5938(void *data)
{
    CManagerBase::f_0c5938(data);
    count = 0;
    for (int i = 0; i < 128; i++)
        slot[i] = -1;
}

/* @implements 0x0c5ee4 us _ZN3Map7WallHit12CManagerBaseD1Ev
   WHAT IT DOES: Complete object destructor: frees the wall polygons. */
/* @implements 0x0c5f34 us _ZN3Map7WallHit12CManagerBaseD0Ev
   WHAT IT DOES: Deleting destructor: frees the wall polygons and the object. */
/* @implements 0x0c5f8c us _ZN3Map7WallHit8CManagerD1Ev
   WHAT IT DOES: Complete object destructor: frees the wall polygons. */
/* @implements 0x0c5fdc us _ZN3Map7WallHit8CManagerD0Ev
   WHAT IT DOES: Deleting destructor: frees the wall polygons and the object. */

}
}

Map::WallHit::CManager D_246700;

/* @draft 0x0c5dc4 us __static_initialization_and_destruction_0
   DRAFT: the zeroing stores of the constructor are scheduled in another order (retail stores
   the last polygon set word, then m4 and the set's first word, before the rest).
   WHAT IT DOES: Constructs the global wall hit manager at start up and destroys it at exit. */
/* @implements 0x0c5ea4 us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
/* @implements 0x0c5ec4 us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */
