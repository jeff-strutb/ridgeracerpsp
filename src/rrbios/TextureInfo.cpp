/* The texture info store (retail 0x023340 to 0x023e54, and the template methods it instantiates,
   0x023e54 to 0x024474): RRBios::TextureManager::CInfo records, one per texture loaded into
   video memory, kept in a CKeyLinkList (a fixed pool of list nodes plus a keyed table of
   binary search trees) and found by the texture's id. Each record holds the GE command lists
   that select the texture and load its palette, built here from the texture's file header. */

extern "C" {
void *sceGeEdramGetAddr(void);
int sceKernelDcacheWritebackInvalidateRange(const void *p, unsigned int size);
}

/* The 32 byte header of one texture in a texture file. */
struct TexHeader {
    int id;
    unsigned short clutNum;
    unsigned char clutFmt;
    unsigned char levels;
    unsigned short width;
    unsigned short height;
    unsigned char tmode;
    unsigned char format;
    unsigned short flags;
    int clutOfs;
    unsigned int clut;
    unsigned int image;
    int m28;
};

namespace RRBios {
namespace TextureManager {
/* One texture in video memory: its palette load list, its header, its select list. */
class CInfo {
public:
    unsigned int clut[8] __attribute__((aligned(64)));
    TexHeader head;
    unsigned int tex[38];
    unsigned int *clutList;
    unsigned int *clutCall;
    unsigned int *texList;
    unsigned int clutData;
    unsigned int image;
    CInfo() {}
};
}
}

/* A fixed pool of nodes on two lists, the free one and the used one. */
template <class T> class CLinkList {
public:
    struct Node {
        Node *next;
        Node *prev;
        T data;
        Node() {}
        ~Node() {}
    };
    struct Iterator {
        Node *n;
    };

    Node *m_pool;
    Node m_free;
    Node m_used;
    unsigned int m_count;
    unsigned int m_num;

    CLinkList()
    {
        m_pool = 0;
        m_count = 0;
        m_num = 0;
        Alloc(0);
    }
    ~CLinkList()
    {
        if (m_pool)
            Free();
    }
    void Free()
    {
        delete[] m_pool;
        m_pool = 0;
        m_count = 0;
    }
    int Alloc(unsigned int n)
    {
        if (n)
            m_pool = new Node[n];
        m_count = n;
        Reset();
        return 1;
    }
    void Reset();
    Node *Insert(Node *pos, const T &v);
    void Link(Node *pos, Node *n)
    {
        n->next = pos;
        n->prev = pos->prev;
        pos->prev->next = n;
        pos->prev = n;
    }
    Node *Take()
    {
        if (m_num == m_count)
            return m_used.next;
        m_num++;
        Node *n = m_free.next;
        Unlink(n);
        return n;
    }
    void Unlink(Node *n)
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
    }
    void Erase(Node *n)
    {
        if (m_num) {
            m_num--;
            Unlink(n);
            Link(m_free.next, n);
        }
    }
};

/* A keyed table: 101 buckets, each a binary search tree ending in one shared sentinel. */
template <class T> class CKeyTable {
public:
    struct Node {
        Node *m0;
        Node *m4;
        unsigned int key;
        T *value;
    };

    Node *m_nodes;
    Node *m_free;
    unsigned int m_capacity;
    unsigned int m_num;
    Node m_nil;
    Node *m_bucket[101] __attribute__((aligned(64)));

    CKeyTable()
    {
        m_nodes = 0;
        m_free = 0;
        m_capacity = 0;
        m_num = 0;
        Alloc(0);
    }
    ~CKeyTable()
    {
        if (m_nodes)
            Free();
    }
    void Free();
    void Reset();
    int Alloc(unsigned int n);
    T *Find(unsigned int key);
    int Insert(unsigned int key, T *value);
    int Remove(unsigned int key);
    unsigned int Hash(unsigned int key);
    Node *FindNode(unsigned int key);
};

template <class T> class CKeyLinkList : public CLinkList<T> {
public:
    CKeyTable<T> m_table;
    virtual ~CKeyLinkList() {}
    int Remove(unsigned int key);
};

using namespace RRBios::TextureManager;

typedef CLinkList<CInfo>::Node InfoNode;

extern signed char D_1d1a00[];
CKeyLinkList<CInfo> D_23c240;

void f_023d38(CLinkList<CInfo> *l);

/* @draft 0x023340 us f_023340
   WHAT IT DOES: Makes room for n textures: the keyed table and the pool of n records, all on
   the free list. Returns 0 if the table cannot be made. */
int f_023340(unsigned int n)
{
    CKeyLinkList<CInfo> *g = &D_23c240;
    if (!g->m_table.Alloc(n))
        return 0;
    return g->Alloc(n);
}

/* @draft 0x0233dc us f_0233dc
   WHAT IT DOES: Frees the keyed table and the record pool. */
void f_0233dc(void)
{
    CKeyLinkList<CInfo> *g = &D_23c240;
    g->m_table.Free();
    g->Free();
}

/* @draft 0x023444 us f_023444
   WHAT IT DOES: Forgets every texture: empties the keyed table and puts every record back on
   the free list. */
void f_023444(void)
{
    CKeyLinkList<CInfo> *g = &D_23c240;
    g->m_table.Reset();
    g->Reset();
}

/* @draft 0x02347c us f_02347c
   WHAT IT DOES: Finds the record of the texture with the given id, or 0. */
CInfo *f_02347c(unsigned int id)
{
    CKeyLinkList<CInfo> *g = &D_23c240;
    return g->m_table.Find(id);
}

/* @draft 0x0234a4 us f_0234a4
   WHAT IT DOES: Takes a record for a new texture id, at the front of the used list, and enters
   it in the table with its command lists cleared. If the id is already present the record goes
   back to the free list and 0 is returned. */
CInfo *f_0234a4(unsigned int id)
{
    CInfo tmp;
    CLinkList<CInfo> *l = &D_23c240;
    InfoNode *n = l->Insert(l->m_used.next, tmp);
    CInfo *p = &n->data;
    if (!D_23c240.m_table.Insert(id, p)) {
        l->Erase(n);
        return 0;
    }
    if (p) {
        p->clutList = 0;
        p->clutCall = 0;
        p->texList = 0;
        p->clutData = 0;
        p->image = 0;
    }
    return p;
}

/* @draft 0x023588 us f_023588
   WHAT IT DOES: Drops the texture with the given id. Returns 1 if it was present. */
int f_023588(unsigned int id)
{
    return D_23c240.Remove(id);
}

/* @draft 0x0235ac us f_0235ac
   WHAT IT DOES: Builds a texture's GE command lists from its file header: the palette load list
   (mode, address, load) if it has a palette, and the select list (texture mode, pixel format,
   then the address, buffer width and size of every mipmap level), and flushes both from the
   data cache so the GE sees them. */
void f_0235ac(CInfo *info, TexHeader *h)
{
    info->head = *h;
    if (h->clutOfs) {
        unsigned int a = h->clut;
        info->clut[0] = h->clutFmt | 0xc500ff00;
        info->clut[1] = (a & 0xffffff) | 0xb0000000;
        info->clut[2] = ((a >> 24) & 0xf) << 16 | 0xb1000000;
        info->clut[3] = h->clutNum | 0xc4000000;
        info->clut[6] = 0xff000000;
        info->clut[7] = 0x0b000000;
        info->clut[4] = 0xff000000;
        info->clut[5] = 0xff000000;
        sceKernelDcacheWritebackInvalidateRange(info, 32);
        info->clutList = info->clut;
        info->clutCall = info->clut;
    } else {
        info->clutList = 0;
        info->clutCall = 0;
    }
    unsigned int img = h->image;
    if (img == 0) {
        info->texList = 0;
        return;
    }
    int n = D_1d1a00[h->format];
    int w = h->width;
    int levels = h->levels;
    int bw = (w + n - 1) / n * n;
    unsigned int *start = info->tex;
    start[0] = (h->tmode << 8) | (levels << 16) | 0xc2000001;
    start[1] = h->format | 0xc3000000;
    int ht = h->height;
    unsigned int *p = &info->tex[2];
    int tw, th;
    for (tw = 256; tw > 0; tw >>= 1)
        if (tw & (w - 1)) {
            tw <<= 1;
            break;
        }
    for (th = 256; th > 0; th >>= 1)
        if (th & (ht - 1)) {
            th <<= 1;
            break;
        }
    *p++ = (img & 0xffffff) | 0xa0000000;
    *p++ = bw | 0xa8000000 | ((img >> 24) & 0xf) << 16;
    int lv = 0;
    int i, j, k;
    i = 0;
    for (k = tw; k != 1; k >>= 1)
        i++;
    j = 0;
    for (k = th; k != 1; k >>= 1)
        j++;
    *p++ = (0xb8000000 | i) | (j << 8);
    while (lv < levels) {
        img += (w + n - 1) / n * ((ht + 7) / 8) * 128;
        bw = ((bw >> 1) + n - 1) / n * n;
        lv++;
        tw >>= 1;
        th >>= 1;
        w >>= 1;
        ht >>= 1;
        *p++ = ((lv << 24) + 0xa0000000) | (img & 0xffffff);
        *p++ = ((lv << 24) + 0xa8000000) | bw | ((img >> 24) & 0xf) << 16;
        i = 0;
        for (k = tw; k != 1; k >>= 1)
            i++;
        j = 0;
        for (k = th; k != 1; k >>= 1)
            j++;
        *p++ = ((lv << 24) + 0xb8000000 | i) | (j << 8);
    }
    p[1] = 0x0b000000;
    p[0] = 0xcb000000;
    sceKernelDcacheWritebackInvalidateRange(start, 152);
    info->texList = start;
}

/* @draft 0x023988 us f_023988
   WHAT IT DOES: Builds only a palette load list (mode, address, count) for a texture whose
   palette is given directly, flushes it from the data cache, and marks the record as having no
   select list. */
void f_023988(CInfo *info, unsigned int fmt, unsigned int num, unsigned int a)
{
    info->clut[0] = fmt | 0xc500ff00;
    info->clut[1] = (a & 0xffffff) | 0xb0000000;
    info->clut[2] = ((a >> 24) & 0xf) << 16 | 0xb1000000;
    info->clut[3] = num | 0xc4000000;
    info->clut[6] = 0xff000000;
    info->clut[7] = 0x0b000000;
    info->clut[4] = 0xff000000;
    info->clut[5] = 0xff000000;
    sceKernelDcacheWritebackInvalidateRange(info, 32);
    info->texList = 0;
    info->clutList = info->clut;
    info->clutCall = info->clut;
}

/* @draft 0x023a20 us f_023a20
   WHAT IT DOES: Builds the select list of a texture given directly (pixel format, width, height
   and video memory address): no mipmaps, buffer width rounded up to 64, and flushes it. */
void f_023a20(CInfo *info, unsigned int format, int w, int h, unsigned int a)
{
    unsigned int *start = info->tex;
    int bw = (w + 63) / 64 * 64;
    unsigned int *p = &info->tex[2];
    start[0] = 0xc2000000;
    start[1] = format | 0xc3000000;
    int tw, th;
    for (tw = 256; tw > 0; tw >>= 1)
        if (tw & (w - 1)) {
            tw <<= 1;
            break;
        }
    for (th = 256; th > 0; th >>= 1)
        if (th & (h - 1)) {
            th <<= 1;
            break;
        }
    *p++ = (a & 0xffffff) | 0xa0000000;
    *p++ = bw | ((a >> 24) & 0xf) << 16 | 0xa8000000;
    int i, j, k;
    i = 0;
    for (k = tw; k != 1; k >>= 1)
        i++;
    j = 0;
    for (k = th; k != 1; k >>= 1)
        j++;
    *p++ = i | (j << 8) | 0xb8000000;
    p[1] = 0x0b000000;
    p[0] = 0xcb000000;
    sceKernelDcacheWritebackInvalidateRange(start, 152);
    info->texList = start;
}

/* @draft 0x023b6c us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the texture info store empty; at shutdown, frees its table
   and pool. */

/* @draft 0x023cf8 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @draft 0x023d18 us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */

/* @draft 0x023d38 us _ZN9CLinkListIN6RRBios14TextureManager5CInfoEE5ResetEv
   WHAT IT DOES: Puts every node of the pool on the free list, in order, and empties the used
   list. */
template <class T> void CLinkList<T>::Reset()
{
    Node *prev = &m_free;
    Node *n = m_pool;
    Node *head = prev;
    unsigned int i = m_count;
    while (i) {
        i--;
        prev->next = n;
        n->prev = prev;
        prev = n;
        n++;
    }
    prev->next = head;
    head->prev = prev;
    m_used.prev = m_used.next = &m_used;
    m_num = 0;
}

/* @draft 0x023d80 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE5AllocEj
   WHAT IT DOES: Makes a table of n nodes and puts them all on its free list. */
template <class T> int CKeyTable<T>::Alloc(unsigned int n)
{
    if (n)
        m_nodes = new Node[n];
    m_capacity = n;
    Reset();
    return 1;
}

/* @draft 0x023e54 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE4FreeEv
   WHAT IT DOES: Frees the table's nodes. */
template <class T> void CKeyTable<T>::Free()
{
    if (m_nodes)
        delete[] m_nodes;
    m_nodes = 0;
    m_capacity = 0;
}

/* @draft 0x023e98 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE5ResetEv
   WHAT IT DOES: Empties the table: chains every node on the free list and points every bucket
   at the sentinel. */
template <class T> void CKeyTable<T>::Reset()
{
    if (m_nodes) {
        Node *n = m_nodes;
        unsigned int i;
        m_free = n;
        for (i = 0; i < m_capacity - 1; i++) {
            n->m0 = n + 1;
            n++;
        }
        n->m0 = 0;
        for (i = 0; i < 101; i++)
            m_bucket[i] = &m_nil;
        m_num = 0;
    }
}

/* @draft 0x023f04 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE4FindEj
   WHAT IT DOES: Returns the value stored under a key, or 0. */
template <class T> T *CKeyTable<T>::Find(unsigned int key)
{
    Node *n = FindNode(key);
    if (n)
        return n->value;
    return 0;
}

/* @draft 0x023f30 us _ZN9CLinkListIN6RRBios14TextureManager5CInfoEE6Insert
   WHAT IT DOES: Takes a node (from the free list, or the first used one when the pool is full),
   copies the value into it and links it before the given node. */
template <class T> typename CLinkList<T>::Node *CLinkList<T>::Insert(Node *pos, const T &v)
{
    Node *n = Take();
    if (n == 0)
        return &m_used;
    n->data = v;
    Link(pos, n);
    return n;
}

/* @draft 0x023fe8 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE6InsertEj
   WHAT IT DOES: Enters a value under a key. Returns 0 if the table is over full, the key is
   already present, or no node is free. */
template <class T> int CKeyTable<T>::Insert(unsigned int key, T *value)
{
    if (m_num > m_capacity)
        return 0;
    unsigned int h = Hash(key);
    m_nil.key = key;
    Node **link = &m_bucket[h];
    while (key != (*link)->key) {
        if ((*link)->key < key)
            link = &(*link)->m0;
        else
            link = &(*link)->m4;
    }
    Node *n = *link;
    if (n != &m_nil)
        return 0;
    Node *f = m_free;
    Node *next = f->m0;
    if (next == 0)
        return 0;
    f->key = key;
    f->value = value;
    m_num++;
    m_free = next;
    f->m0 = f->m4 = n;
    *link = f;
    return 1;
}

/* @draft 0x0240cc us _ZN12CKeyLinkListIN6RRBios14TextureManager5CInfoEE6RemoveEj
   WHAT IT DOES: Drops the record stored under a key: back to the free list, out of the table.
   Returns 1 if it was present. */
template <class T> int CKeyLinkList<T>::Remove(unsigned int key)
{
    T *p = m_table.Find(key);
    if (!p)
        return 0;
    typename CLinkList<T>::Iterator it;
    for (it.n = this->m_used.next; it.n != &this->m_used; it.n = it.n->next) {
        if (&it.n->data == p) {
            this->Erase(it.n);
            m_table.Remove(key);
            return 1;
        }
    }
    return 0;
}

/* @draft 0x0241a0 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE6RemoveEj
   WHAT IT DOES: Takes a key out of its bucket's search tree (replacing a node with two children
   by the leftmost node of its right subtree) and returns the node to the free list. */
template <class T> int CKeyTable<T>::Remove(unsigned int key)
{
    unsigned int h = Hash(key);
    m_nil.key = key;
    Node **link = &m_bucket[h];
    while (key != (*link)->key) {
        if ((*link)->key < key)
            link = &(*link)->m0;
        else
            link = &(*link)->m4;
    }
    Node *n = *link;
    if (n == &m_nil)
        return 0;
    if (n->m0 == &m_nil) {
        *link = n->m4;
    } else if (n->m4 == &m_nil) {
        *link = n->m0;
    } else {
        Node **pl = &n->m4;
        while ((*pl)->m0 != &m_nil)
            pl = &(*pl)->m0;
        Node *s = *pl;
        *pl = s->m4;
        s->m0 = n->m0;
        s->m4 = n->m4;
        *link = s;
    }
    m_num--;
    n->m0 = m_free;
    m_free = n;
    return 1;
}

/* @draft 0x0242a8 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE4HashEj
   WHAT IT DOES: The bucket of a key: the key modulo 101. */
template <class T> unsigned int CKeyTable<T>::Hash(unsigned int key)
{
    return key % 101;
}

/* @draft 0x0242e0 us _ZN9CKeyTableIN6RRBios14TextureManager5CInfoEE8FindNodeEj
   WHAT IT DOES: Searches a key's bucket tree; returns its node, or 0. */
template <class T> typename CKeyTable<T>::Node *CKeyTable<T>::FindNode(unsigned int key)
{
    unsigned int h = Hash(key);
    m_nil.key = key;
    Node *n = m_bucket[h];
    while (key != n->key) {
        if (n->key < key)
            n = n->m0;
        else
            n = n->m4;
    }
    if (n == &m_nil)
        return 0;
    return n;
}

/* @draft 0x02435c us _ZN12CKeyLinkListIN6RRBios14TextureManager5CInfoEED1Ev
   WHAT IT DOES: Destroys the store: frees the table and the pool. */

/* @draft 0x0243e0 us _ZN12CKeyLinkListIN6RRBios14TextureManager5CInfoEED0Ev
   WHAT IT DOES: Destroys the store and frees it. */
