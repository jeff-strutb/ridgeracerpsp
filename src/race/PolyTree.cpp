/* A course polygon tree (retail 0x0c6078 to 0x0c66f4): a quadtree over a rectangle of the
   course in x and z, loaded from course data (the light and shadow polygon sets of
   MapLight.cpp, the wall sets of WallHit.cpp). Each node record packs a level (top 6 bits,
   0 for a branch) with a block index (low 10 bits) and the offset of its children; a branch's
   block of 16 halfwords gives the child of each of its 4x4 cells (negative for none). The
   lookups find the leaf under a point, or gather the polygon ids of the leaves under it. */

/* The data header: the tree's rectangle, its node and block counts, the scale of the ids. */
struct TreeHdr {
    int magic;          /* 512 when the data is used in place */
    float x, z, w, h;
    short nodes;
    short blocks;
    signed char m24;
    signed char m25;
    signed char scale;
    signed char roots;  /* the number of root nodes, or 0 for one */
};

/* One node record: as stored in the data, and as the tree keeps it. */
struct NodeSrc {
    signed char level;
    unsigned char block;
    unsigned short child;
};

struct Node {
    unsigned short block : 10;
    signed short level : 6;
    unsigned short child;
};

/* A rectangle in x and z. */
struct Rect {
    float x, z, w, h;
};

struct PolyTree {
    int type;           /* 0 none, 1 nodes unpacked into their own array, 2 data used in place */
    void *data;
    TreeHdr *hdr;
    Node *node;
    short *block;
    int ids;            /* the address of the polygon ids */
};

extern "C" {
int f_0c61fc(PolyTree *t, int *out, int max, Rect *r, float x, float z, Node *n, int depth);
int f_0c644c(PolyTree *t, Rect *r, Node *n, int depth, float x, float z);
}

/* @implements 0x0c6078 us f_0c6078
   WHAT IT DOES: Loads a tree from course data (or empties it for none): data marked 512 is
   used in place; otherwise its node records are unpacked into a new array. Then finds the
   blocks after the nodes and the ids after the blocks. */
extern "C" void f_0c6078(PolyTree *t, int *data)
{
    if (!data) {
        t->type = 0;
        t->hdr = 0;
        t->node = 0;
        return;
    }
    t->data = data;
    t->hdr = (TreeHdr *)data;
    TreeHdr *h;
    if (*data == 512) {
        h = (TreeHdr *)data;
        t->type = 2;
        Node *np = (Node *)(h + 1);
        t->node = np;
        t->block = (short *)(np + h->nodes);
    } else {
        NodeSrc *src = (NodeSrc *)(data + 6);
        t->hdr = (TreeHdr *)(data - 1);
        t->type = 1;
        t->node = new Node[t->hdr->nodes];
        h = t->hdr;
        t->block = (short *)(src + h->nodes);
        for (int i = 0; i < t->hdr->nodes; i++) {
            t->node[i].level = src[i].level;
            t->node[i].block = src[i].block;
            t->node[i].child = src[i].child;
            h = t->hdr;
        }
    }
    t->ids = (int)(t->block + h->blocks * 16);
}

/* @implements 0x0c61b4 us f_0c61b4
   WHAT IT DOES: Frees the unpacked node array of a loaded tree. */
extern "C" void f_0c61b4(PolyTree *t)
{
    if (t->type == 1 && t->node) {
        delete[] t->node;
        t->node = 0;
    }
}

/* @draft 0x0c61fc us f_0c61fc
   DRAFT: full logic, size 592 matches; 87/148 words differ, all from register allocation:
   retail keeps the output pointer in t3 and the block-code value in t2, here they are
   swapped, which shifts the loop and call registers. Declaring `ret` before the 0xf400
   block lets cse reuse it as the clamp zero (the word is lost); declared after it, as here,
   retail's layout is matched. Tried: ret placements, `depth++` in place, nested if shapes,
   a copy of out, out[i] indexing, a MAX macro.
   WHAT IT DOES: Gathers the polygon ids under a point into out, from the node n at the
   given depth, and returns how many were written. A node with a level above 0 holds that
   many ids (cell values); the special block codes 0xf400, 0xf800 and 0xfc00 in its top 6
   bits stand for a branch of 4x4 cells to descend by the point, a single slot picked by the
   root, and all sixteen cells followed by the next node. An id is written as the base of the
   ids plus the cell value and the node's child offset, times the header's scale. */
extern "C" int f_0c61fc(PolyTree *t, int *out, int root, Rect *r, float x, float z, Node *n, int depth)
{
    unsigned short h = *(unsigned short *)n;
    short *cell = t->block + (h & 0x3ff) * 16;
    int ret = 0;
    int code = h & 0xfc00;
    if (code != 0xf400) {
        if (code == 0xfc00) {
            int i;
            for (i = 0; i < 16; i++)
                *out++ = t->ids + (cell[i] + n->child) * t->hdr->scale;
            depth++;
            n++;
            return f_0c61fc(t, out, root, r, x, z, n, depth) + 16;
        }
        if (code == 0xf800) {
            int k = cell[root];
            if (k < 0)
                return 0;
            return f_0c61fc(t, out, root, r, x, z, &t->node[k + n->child], depth);
        }
        int lv = (short)h >> 10;
        if (lv > 0) {
            int i;
            for (i = 0; i < lv; i++) {
                *out++ = t->ids + (cell[i] + n->child) * t->hdr->scale;
                ret++;
            }
        }
        return ret;
    }
    Rect c;
    int i, j, k;
    c.w = r->w * 0.25f;
    c.h = r->h * 0.25f;
    i = (x - r->x) * (1.0f / c.w);
    if (i < 0)
        i = 0;
    if (i > 3)
        i = 3;
    j = (z - r->z) * (1.0f / c.h);
    if (j < 0)
        j = 0;
    if (j > 3)
        j = 3;
    k = cell[j * 4 + i];
    if (k < 0)
        return 0;
    c.x = r->x + i * c.w;
    c.z = r->z + j * c.h;
    depth++;
    return f_0c61fc(t, out, root, &c, x, z, &t->node[k + n->child], depth);
}

/* @draft 0x0c644c us f_0c644c
   DRAFT: full logic; 72/77 words differ, size 300 vs 308. Retail clamps the two cell
   indices with `max` against one fresh zero register set before the level test (move t5,
   zero, hoisted above the branch); here cse2 reuses the level register (known 0 on that
   path) as the zero, so that word is missing and the registers shift. With the compiler
   flag -fno-rerun-cse-after-loop the zero is a fresh register (size 308, 54/77 differ) but
   then it is loaded twice and 6 f_0c61fc words get worse, so the flag is not used. Tried:
   early return, level in a variable, MAX macro, zero variable, bitfield accesses.
   WHAT IT DOES: Finds the leaf under a point: at a branch, picks the cell of its 4x4 grid
   holding the point and descends into its child (0 when the cell has none); at a leaf,
   returns the depth reached. */
extern "C" int f_0c644c(PolyTree *t, Rect *r, Node *n, int depth, float x, float z)
{
    short h = *(short *)n;
    short *cell = t->block + (h & 0x3ff) * 16;
    int ret = depth;
    if ((h >> 10) == 0) {
        Rect c;
        int i, j, k;
        ret = 0;
        c.w = r->w * 0.25f;
        c.h = r->h * 0.25f;
        i = (x - r->x) * (1.0f / c.w);
        if (i < 0)
            i = 0;
        if (i > 3)
            i = 3;
        j = (z - r->z) * (1.0f / c.h);
        if (j < 0)
            j = 0;
        if (j > 3)
            j = 3;
        k = cell[j * 4 + i];
        if (k >= 0) {
            c.x = r->x + i * c.w;
            c.z = r->z + j * c.h;
            ret = f_0c644c(t, &c, &t->node[k + n->child], depth + 1, x, z);
        }
    }
    return ret;
}

/* @implements 0x0c6580 us f_0c6580
   WHAT IT DOES: Gathers the polygon ids under a point from one root (0 when the point is
   outside the tree or the root does not exist); returns how many were written. */
extern "C" int f_0c6580(PolyTree *t, int *out, int root, float x, float z)
{
    TreeHdr *h = t->hdr;
    int n = 0;
    if (h) {
        Rect r;
        r.x = h->x; r.z = h->z; r.w = h->w; r.h = h->h;
        if (x < r.x) return n;
        if (r.x + r.w <= x) return n;
        if (z < r.z) return n;
        if (r.z + r.h <= z) return n;
        if (h->roots != 0 && root >= h->roots)
            return n;
        n = f_0c61fc(t, out, root, &r, x, z, t->node, 0);
        return n;
    }
    return n;
}

/* @implements 0x0c6630 us f_0c6630
   WHAT IT DOES: Finds the depth of the leaf under a point from one root (-1 when the point
   is outside the tree or the root does not exist). */
extern "C" int f_0c6630(PolyTree *t, int root, float x, float z)
{
    TreeHdr *h = t->hdr;
    int n = -1;
    if (h) {
        Rect r;
        r.x = h->x;
        r.z = h->z;
        r.w = h->w;
        r.h = h->h;
        if (x < r.x)
            return n;
        if (r.x + r.w <= x)
            return n;
        if (z < r.z)
            return n;
        if (r.z + r.h <= z)
            return n;
        if (h->roots != 0 && root >= h->roots)
            return n;
        Node *p = t->node;
        if (t->hdr->roots)
            p += root;
        n = f_0c644c(t, &r, p, 0, x, z);
        return n;
    }
    return n;
}
