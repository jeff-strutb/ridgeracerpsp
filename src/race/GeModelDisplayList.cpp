/* The GE display list writers of object file 337 (retail 0x0fea50 to 0x0ff778). f_0fea50 writes
   a world matrix as packed GE commands. f_0fed1c writes the three commands that end a part's
   list. Not yet transcribed: f_0fed54 (per-model list writer, 920 bytes), f_0ff0ec and f_0ff388
   (two similar per-model list writers, 668 and 1008 bytes). Listed in the report. */

/* A 4x4 block of 32 bit words: rows of four words, the fourth word of each row is not written
   to the list (the matrix is 4x3). Used for the world matrix. */
struct Mat43 {
    unsigned int w[16];
};

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* The matrix temporary that the scaled path writes its three transformed rows into. */
extern "C" Mat43 D_27f0c0;
/* The per-column scale vector (rodata). */
extern "C" const Vec4 D_1b0540;

extern "C" Vec4 *f_02805c(Vec4 *d, const Vec4 *a, const Vec4 *b);

/* Packs one word of a matrix row as a GE command data word: the bits shifted down a byte and
   the 0x3b command in the top byte. */
static __inline__ unsigned int PackWord(unsigned int w)
{
    return (w >> 8) | 0x3b000000;
}

/* @draft 0x0fea50 us f_0fea50
   WHAT IT DOES: Writes a model's world matrix as GE commands: a 0x3a command, then the
   twelve matrix words of the 4x3 block (each row's first three words, packed), then a 0x1f
   command whose low bit is the flag bit 0x10. When flag bit 0x20 is set, the first three rows
   are first multiplied component by component by a fixed scale vector (into a temporary) and
   that copy is written instead; the last row is always written as stored and no 0x1f word
   follows. Returns the pointer past the last written word. */
extern "C" unsigned int *f_0fea50(const Mat43 *m, unsigned int *p, unsigned int flags)
{
    unsigned int *q;
    unsigned int ext;

    if (flags & 0x20) {
        Vec4 scale = D_1b0540;
        Mat43 *t = &D_27f0c0;
        f_02805c((Vec4 *)&t->w[0], (const Vec4 *)&m->w[0], &scale);
        f_02805c((Vec4 *)&t->w[4], (const Vec4 *)&m->w[4], &scale);
        f_02805c((Vec4 *)&t->w[8], (const Vec4 *)&m->w[8], &scale);
        q = p;
        *q++ = 0x3a000000;
        *q++ = PackWord(t->w[0]);
        *q++ = PackWord(t->w[1]);
        *q++ = PackWord(t->w[2]);
        *q++ = PackWord(t->w[4]);
        *q++ = PackWord(t->w[5]);
        *q++ = PackWord(t->w[6]);
        *q++ = PackWord(t->w[8]);
        *q++ = PackWord(t->w[9]);
        *q++ = PackWord(t->w[10]);
        *q++ = PackWord(m->w[12]);
        *q++ = PackWord(m->w[13]);
        *q++ = PackWord(m->w[14]);
        return q;
    }
    *p = 0x3a000000;
    q = p + 1;
    ext = flags & 0x10;
    *q++ = PackWord(m->w[0]);
    *q++ = PackWord(m->w[1]);
    *q++ = PackWord(m->w[2]);
    *q++ = PackWord(m->w[4]);
    *q++ = PackWord(m->w[5]);
    *q++ = PackWord(m->w[6]);
    *q++ = PackWord(m->w[8]);
    *q++ = PackWord(m->w[9]);
    *q++ = PackWord(m->w[10]);
    *q++ = PackWord(m->w[12]);
    *q++ = PackWord(m->w[13]);
    *q++ = PackWord(m->w[14]);
    *q++ = ext ? 0x1f000001 : 0x1f000000;
    return q;
}

/* The model table at D_23c820 (its entries are 64 bytes, indexed by the model number). */
extern "C" char D_23c820[];
extern "C" unsigned int D_27f0b0;
extern "C" unsigned int *D_27f0b4_ptr;
extern "C" unsigned int D_1b0550[];
extern "C" unsigned int *f_0249a0(void *info, unsigned int *p);
extern "C" unsigned int *f_0fea50(const Mat43 *m, unsigned int *p, unsigned int flags);
extern "C" unsigned int *f_0fed1c(unsigned int *p);
extern "C" float floorf(float x);

struct Vec3f {
    float x, y, z;
};

/* A part's sub-record: a texture key, and a count of 16 byte units at offset 12. */
struct SubRec {
    unsigned int key;
    unsigned int w4;
    unsigned int w8;
    unsigned short size;
};

/* A part record: a type word (its high nibble and low 24 bits go into the list), a position
   record (type 1 and 3 read floats from it), a count and an array of sub-record pointers. */
struct Part {
    unsigned int w0;
    Vec3f *pos;
    unsigned int w8;
    unsigned int count;
    SubRec *sub[1];
};

struct PartList {
    unsigned int n;
    Part *parts[1];
};

struct Holder {
    char p0[8];
    PartList *list;
};

/* A model entry (64 bytes): flags at offset 4, the holder at offset 16. */
struct Entry {
    char p0[4];
    unsigned int flags;
    char p8[8];
    Holder *holder;
    char pad[40];
};

/* The table at D_23c820 + 27840 whose entries array is at offset 4. */
struct ModelTable {
    char p0[4];
    Entry *entries;
};

/* @draft 0x0fed54 us f_0fed54
   WHAT IT DOES: Writes one model's display list at a place given by a matrix and a clip word:
   the world matrix (through f_0fea50, with the model's flags), then for each part of the
   model a texture or sub-record block, and for position type 1 and 3 parts the float position
   is wrapped by the table's modulus (trunc, div, floor) before being written as two commands.
   Ends with the f_0fed1c tail. Not yet exact. */
extern "C" unsigned int *f_0fed54(int idx, const Mat43 *mat, unsigned int *p, unsigned int clip)
{
    ModelTable *tb = (ModelTable *)(D_23c820 + 27840);
    Entry *e = (Entry *)((char *)tb->entries + (idx << 6));
    PartList *list = e->holder->list;
    unsigned int i;

    p = f_0fea50(mat, p, e->flags);
    for (i = 0; i < list->n; i++) {
        Part *pt = list->parts[i];
        if (pt != (Part *)D_27f0b4_ptr) {
            *p++ = 0x10000000 | ((pt->w0 >> 24) & 0xf) << 16;
            *p++ = (pt->w0 & 0x00ffffff) | 0x0a000000;
            D_27f0b4_ptr = (unsigned int *)pt;
        }
        for (unsigned int j = 0; j < pt->count; j++) {
            SubRec *sr = pt->sub[j];
            if (sr->key != D_27f0b0) {
                p = f_0249a0(sr, p);
                D_27f0b0 = sr->key;
            }
            *p++ = 0x1e000000;
            *p++ = 0x0a000000 | (((unsigned int)sr + sr->size * 16 + 96) & 0x00ffffff);
        }
    }
    return f_0fed1c(p);
}

/* @draft 0x0ff0ec us f_0ff0ec
   WHAT IT DOES: Writes a model's display list placed at a screen point: the world matrix
   (through f_0fea50), a position command pair from the two float arguments (x, y), the clip
   word as two region commands, then the part and sub-record blocks as in f_0fed54, and the
   f_0fed1c tail. Not yet exact. */
extern "C" unsigned int *f_0ff0ec(int idx, const Mat43 *mat, unsigned int *p, unsigned int clip, float x, float y)
{
    ModelTable *tb = (ModelTable *)(D_23c820 + 27840);
    Entry *e = (Entry *)((char *)tb->entries + (idx << 6));
    PartList *list = e->holder->list;
    unsigned int i;

    p = f_0fea50(mat, p, e->flags);
    *p++ = 0x4a000000 | ((unsigned int)(*(int *)&x) >> 8);
    *p++ = 0x4b000000 | ((unsigned int)(*(int *)&y) >> 8);
    *p++ = 0xc0000000 | (clip & 0x00ffffff);
    for (i = 0; i < list->n; i++) {
        Part *pt = list->parts[i];
        if (pt != (Part *)D_27f0b4_ptr) {
            *p++ = 0x10000000 | ((pt->w0 >> 24) & 0xf) << 16;
            *p++ = (pt->w0 & 0x00ffffff) | 0x0a000000;
            D_27f0b4_ptr = (unsigned int *)pt;
        }
        for (unsigned int j = 0; j < pt->count; j++) {
            SubRec *sr = pt->sub[j];
            if (sr->key != D_27f0b0) {
                p = f_0249a0(sr, p);
                D_27f0b0 = sr->key;
            }
            *p++ = 0x1e000001;
            *p++ = 0x0a000000 | (((unsigned int)sr + sr->size * 16 + 96) & 0x00ffffff);
        }
    }
    return f_0fed1c(p);
}

/* @draft 0x0ff388 us f_0ff388
   WHAT IT DOES: Like f_0fed54 but the position comes from the matrix argument's floats: they
   are wrapped by the table's modulus (trunc, div, floor, with the table's divisor at offset
   13004) and written as two commands, then the part and sub-record blocks, then a 0x1b word
   and the f_0fed1c tail. Not yet exact. */
extern "C" unsigned int *f_0ff388(int idx, const Mat43 *mat, unsigned int *p, unsigned int clip)
{
    ModelTable *tb = (ModelTable *)(D_23c820 + 27840);
    Entry *e = (Entry *)((char *)tb->entries + (idx << 6));
    PartList *list = e->holder->list;
    unsigned int i;

    p = f_0fea50(mat, p, e->flags);
    *p++ = 0x5c000000 | (clip & 0x00ffffff);
    *p++ = 0x5d000000 | (clip >> 24);
    for (i = 0; i < list->n; i++) {
        Part *pt = list->parts[i];
        if (pt != (Part *)D_27f0b4_ptr) {
            *p++ = 0x10000000 | ((pt->w0 >> 24) & 0xf) << 16;
            *p++ = (pt->w0 & 0x00ffffff) | 0x0a000000;
            D_27f0b4_ptr = (unsigned int *)pt;
        }
        for (unsigned int j = 0; j < pt->count; j++) {
            SubRec *sr = pt->sub[j];
            if (sr->key != D_27f0b0) {
                p = f_0249a0(sr, p);
                D_27f0b0 = sr->key;
            }
            *p++ = 0x1e000000;
            *p++ = 0x0a000000 | (((unsigned int)sr + sr->size * 16 + 96) & 0x00ffffff);
        }
    }
    *p++ = 0x1b000000;
    return f_0fed1c(p);
}

/* @implements 0x0fed1c us f_0fed1c
   WHAT IT DOES: Writes three GE commands at the list pointer: a clip region command (0x5c)
   with 0xffffff, a 0x5d command with 0xff, and a 0x20 command with 1; returns the pointer past
   them. */
extern "C" unsigned int *f_0fed1c(unsigned int *p)
{
    *p = 0x5cffffff;
    p++;
    *p = 0x5d0000ff;
    p++;
    *p = 0x20000001;
    p++;
    return p;
}
