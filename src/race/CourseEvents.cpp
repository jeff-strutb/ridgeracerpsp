/* The course event data (retail 0x0d5d80 to 0x0d6280): the map manager's view of a loaded
   course's event file. Setup turns the file's offsets into pointers; the rest look up the
   course section a position lies in, through a grid of cells and a list of section start
   distances. */

extern "C" {
void *f_029a60(void *pack, int i);
}

/* The event file header. Every pointer-like word is an offset from the header. */
struct EventHeader {
    int objects;        /* offset of the object records */
    int nObjects;
    int entries;        /* offset of the cell entries */
    int nEntries;
    int sections;       /* offset of the section table */
    int nSections;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
    int names;          /* offset of the object names */
    int groups;         /* offset of the group records */
    int nGroups;
    int m64;
    int m68;
    float cellW;
    float cellD;
    int m80;
    int m84;
    int originX;
    int originZ;
};

/* One object: its name, its pack data and a pointer into the file. */
struct EventObject {
    char *name;
    int m4[3];
    void *data;
    int m20;
    int m24;
    int m28[7];
    int loaded;
    int m60;
};

/* One cell entry: the two grid coordinates it covers. */
struct EventEntry {
    int m0;
    int m4;
    int x;
    int z;
};

/* One section: its start distance and its run of cell entries. */
struct EventSection {
    int start;
    int first;
    int count;
    int m12;
};

/* A group: four offsets fixed up into pointers, the last a list of further offsets. */
struct EventGroup {
    int m0;
    int m4;
    int m8;
    int m12;
    int p0;
    int p4;
    int p8;
    int *list;
};

class CourseEvents {
public:
    void Setup(EventHeader *h, void *pack);
    void f_0d5f70();
    int FindSection(int dist);
    int Locate(int dist, int *out, int start, float x, float z, int def);
    int FindCell(int section, int x, int z);
    int CellX(float x);
    int CellZ(float z);
    float CellToX(int i);
    float CellToZ(int i);
    int MidX();
    int MidZ();

    EventHeader *m0;
    EventObject *m4;
    EventEntry *m8;
    char *m12;
    char *m16;
    char *m20;
    char *m24;
    EventSection *m28;
    char *m32;
    EventGroup *m36;
    int m40;
    int m44;
};

/* @draft 0x0d5d80 us _ZN12CourseEvents5Setup
   WHAT IT DOES: Takes a loaded event file: points every table at its place in the file,
   names each object (the names are packed one after another), attaches each object's pack
   entry (none without a pack), marks it loaded and fixes up its file pointer; then fixes up
   every group's pointers and offset list.
   DIFFERS: `this` and the loop counter take each other's saved registers (s4/s5), and the
   object loop's field fix-up load is scheduled ahead of the loaded flag store. */
void CourseEvents::Setup(EventHeader *h, void *pack)
{
    int i;
    char *s;

    m0 = h;
    m4 = (EventObject *)((char *)h + h->objects);
    m8 = (EventEntry *)((char *)h + h->entries);
    m12 = (char *)h + h->m24;
    m28 = (EventSection *)((char *)h + h->sections);
    m16 = (char *)h + h->m64;
    m20 = (char *)h + h->m32;
    m24 = (char *)h + h->m40;
    s = (char *)h + h->names;
    m32 = s;
    m36 = (EventGroup *)((char *)h + h->groups);
    for (i = 0; i < m0->nObjects; i++) {
        m4[i].name = s;
        while (*s)
            s++;
        s++;
        if (pack)
            m4[i].data = f_029a60(pack, i);
        else
            m4[i].data = 0;
        m4[i].loaded = 1;
        m4[i].m24 = (int)((char *)h + m4[i].m24);
    }
    for (i = 0; i < m0->nGroups; i++) {
        EventGroup *g = &m36[i];
        int j;
        g->p0 = (int)((char *)h + g->m0);
        g->p4 = (int)((char *)h + g->m4);
        g->p8 = (int)((char *)h + g->m8);
        g->list = (int *)((char *)h + g->m12);
        for (j = 0; j < m0->nEntries; j++)
            g->list[j] = (int)((char *)h + g->list[j]);
    }
}

/* @implements 0x0d5f70 us _ZN12CourseEvents8f_0d5f70
   WHAT IT DOES: Nothing. */
void CourseEvents::f_0d5f70()
{
}

/* @implements 0x0d5f78 us _ZN12CourseEvents11FindSection
   WHAT IT DOES: Returns the last section whose start distance is at or below the given
   distance (measured from the other end when the course runs in reverse), or -1. */
int CourseEvents::FindSection(int dist)
{
    int i;

    if (m44 != -1)
        dist = m44 - dist - 1;
    for (i = m0->nSections - 1; i >= 0; i--) {
        if (dist >= m28[i].start)
            return i;
    }
    return -1;
}

/* @implements 0x0d5fd8 us _ZN12CourseEvents6Locate
   WHAT IT DOES: Finds the section holding the grid cell of (x, z): starts at the section for
   the distance (or the given one), tries every section once, wrapping round, and returns the
   matching cell entry (or the default). The section reached is written to *out. */
int CourseEvents::Locate(int dist, int *out, int start, float x, float z, int def)
{
    int cx = CellX(x);
    int cz = CellZ(z);
    int n = m0->nSections;
    int s = FindSection(dist);
    int i;

    if (s >= 0)
        start = s;
    for (i = 0; i < n; i++) {
        int r = FindCell(start, cx, cz);
        if (r >= 0) {
            def = r;
            break;
        }
        start++;
        if (start == n)
            start = 0;
    }
    if (out)
        *out = start;
    return def;
}

/* @implements 0x0d60d4 us _ZN12CourseEvents8FindCell
   WHAT IT DOES: Returns the index of the section's cell entry covering (x, z), or -1. */
int CourseEvents::FindCell(int section, int x, int z)
{
    EventSection *sec = &m28[section];
    int first = sec->first;
    int count = sec->count;
    EventEntry *e = &m8[first];
    int i;

    for (i = 0; i < count; i++, e++) {
        if (e->x == x && e->z == z)
            return first + i;
    }
    return -1;
}

/* @implements 0x0d6138 us _ZN12CourseEvents5CellX
   WHAT IT DOES: The grid column of an x coordinate. */
int CourseEvents::CellX(float x)
{
    return (int)((x - m0->cellW * m0->originX) / m0->cellW);
}

/* @implements 0x0d6164 us _ZN12CourseEvents5CellZ
   WHAT IT DOES: The grid row of a z coordinate. */
int CourseEvents::CellZ(float z)
{
    return (int)((z - m0->cellD * m0->originZ) / m0->cellD);
}

/* @implements 0x0d6190 us _ZN12CourseEvents7CellToX
   WHAT IT DOES: The x coordinate of a grid column's edge. */
float CourseEvents::CellToX(int i)
{
    return ((float)i + (float)m0->originX) * m0->cellW;
}

/* @implements 0x0d61b4 us _ZN12CourseEvents7CellToZ
   WHAT IT DOES: The z coordinate of a grid row's edge. */
float CourseEvents::CellToZ(int i)
{
    return ((float)i + (float)m0->originZ) * m0->cellD;
}

/* @implements 0x0d61d8 us _ZN12CourseEvents4MidX
   WHAT IT DOES: The middle of the columns the cell entries cover. */
int CourseEvents::MidX()
{
    int hi = m8[0].x;
    int lo = m8[0].x;
    int i;

    for (i = 1; i < m0->nEntries; i++) {
        if (lo > m8[i].x)
            lo = m8[i].x;
        if (hi < m8[i].x)
            hi = m8[i].x;
    }
    return (lo + hi) / 2;
}

/* @implements 0x0d622c us _ZN12CourseEvents4MidZ
   WHAT IT DOES: The middle of the rows the cell entries cover. */
int CourseEvents::MidZ()
{
    int hi = m8[0].z;
    int lo = m8[0].z;
    int i;

    for (i = 1; i < m0->nEntries; i++) {
        if (lo > m8[i].z)
            lo = m8[i].z;
        if (hi < m8[i].z)
            hi = m8[i].z;
    }
    return (lo + hi) / 2;
}
