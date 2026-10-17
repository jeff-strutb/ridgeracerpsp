/* Texture groups (retail 0x0cb694 to 0x0cbfe4): draw lists sorted by texture. A table holds
   one group per texture group of a model; each group keeps one bucket per texture, and each
   frame the drawing code appends draw records (taken from a fixed pool) to the bucket of
   the texture they use, so all draws of one texture go out together. Also the relocation
   of the texture group file (offsets turned into pointers, GE address commands patched). */

extern "C" {
int iprintf(const char *fmt, ...);
void *f_02347c(void *name);
void f_1166d4(int n);
}

/* One queued draw: the object, two bytes of state and the next record of the bucket. */
struct DrawRec {
    void *obj;
    char m4;
    char m5;
    DrawRec *next;
};

/* One texture: its id and the draws queued for it this frame. */
struct TexBucket {
    int key;
    DrawRec *head;
    DrawRec *tail;
};

/* An object to draw: its bucket at +8. */
struct TexDraw {
    int m0[2];
    TexBucket *bucket;
};

/* One texture group. */
struct TexGroup {
    void *owner;
    int n;              /* textures in use */
    TexBucket *b;
    int pri;
    int cap;
    int uses;
};

extern DrawRec D_251dc0[762];   /* the draw record pool */
extern DrawRec *D_254178;       /* the next free record */

class CTexGroupTable {
public:
    CTexGroupTable(int n);
    ~CTexGroupTable();
    TexBucket *Get(TexGroup *g, int *key);
    void Reset();
    void Add(TexDraw *d, int a, int b);
    void Dump();
    TexGroup *Open(void *owner, int idx, int n);

    TexGroup *groups;
    int n;
    int cap;
};

/* @implements 0x0cb694 us _ZN14CTexGroupTableC2Ei
   WHAT IT DOES: Base object constructor: allocates n empty groups. */
/* @implements 0x0cb6dc us _ZN14CTexGroupTableC1Ei
   WHAT IT DOES: Complete object constructor: the same. */
CTexGroupTable::CTexGroupTable(int count)
{
    cap = count;
    groups = new TexGroup[count];
    n = count;
}

/* @implements 0x0cb724 us _ZN14CTexGroupTableD2Ev
   WHAT IT DOES: Base object destructor: frees every group's buckets, then the groups. */
/* @implements 0x0cb7c0 us _ZN14CTexGroupTableD1Ev
   WHAT IT DOES: Complete object destructor: the same. */
CTexGroupTable::~CTexGroupTable()
{
    for (int i = 0; i < n; i++) {
        if (groups[i].b)
            delete[] groups[i].b;
    }
    if (groups)
        delete[] groups;
}

/* @implements 0x0cb85c us _ZN14CTexGroupTable3Get
   WHAT IT DOES: Counts a use of the group and returns its bucket for the texture, adding a
   bucket when the texture is new to the group. */
TexBucket *CTexGroupTable::Get(TexGroup *g, int *key)
{
    g->uses++;
    for (int i = 0; i < g->n; i++) {
        if (g->b[i].key == *key)
            return &g->b[i];
    }
    g->b[g->n].key = *key;
    g->n++;
    return &g->b[g->n - 1];
}

/* @implements 0x0cb8e8 us _ZN14CTexGroupTable5Reset
   WHAT IT DOES: Empties every bucket and rewinds the draw record pool. */
void CTexGroupTable::Reset()
{
    for (int i = 0; i < n; i++) {
        TexGroup *g = &groups[i];
        for (int j = 0; j < g->n; j++) {
            g->b[j].head = 0;
            g->b[j].tail = 0;
        }
    }
    D_254178 = D_251dc0;
}

/* @implements 0x0cb940 us _ZN14CTexGroupTable3Add
   WHAT IT DOES: Takes a record from the pool and appends it to the draw's bucket. */
void CTexGroupTable::Add(TexDraw *d, int a, int b)
{
    TexBucket *bk = d->bucket;
    D_254178->m5 = a;
    D_254178->m4 = b;
    D_254178->next = 0;
    D_254178->obj = d;
    if (bk->tail == 0) {
        bk->tail = bk->head = D_254178;
    } else {
        bk->tail->next = D_254178;
        bk->tail = D_254178;
    }
    D_254178++;
}

/* @implements 0x0cb990 us _ZN14CTexGroupTable4Dump
   WHAT IT DOES: Prints the groups: textures in use, uses and priority. */
void CTexGroupTable::Dump()
{
    iprintf("TextureGroup : %d\n", n);
    for (int i = 0; i < n; i++)
        iprintf("\tTexture : %d / %d  Pri:%d\n", groups[i].n, groups[i].uses, groups[i].pri);
}

/* @implements 0x0cba20 us _ZN14CTexGroupTable4Open
   WHAT IT DOES: Sets group idx up for an owner with room for n textures. */
TexGroup *CTexGroupTable::Open(void *owner, int idx, int count)
{
    groups[idx].owner = owner;
    groups[idx].b = new TexBucket[count];
    groups[idx].cap = count;
    groups[idx].n = 0;
    groups[idx].uses = 0;
    return &groups[idx];
}

/* A model's texture group data: groups of parts, each part with its draws. */
struct TexPart {
    int m0[2];
    int group;          /* texture group number */
    unsigned nDraws;
    TexDraw *draws[1];
};

struct TexPartList {
    unsigned n;
    TexPart *parts[1];
};

struct TexModel {
    CTexGroupTable *table;
    short m4;
    unsigned short nLists;
    TexPartList *lists[1];
};

/* @draft 0x0cbaa0 us _Z14BuildTexGroupsP8TexModel
   WHAT IT DOES: Builds a model's texture group table: one group per group number used by
   its parts, each sized for the distinct textures of that group's draws, and gives every
   draw its texture's bucket.
   DIFFERS: s4 and s5 swapped (the second pass's part pointer and the texture count); 13
   spellings of the loops, locals and the distinct-texture search tried. */
void BuildTexGroups(TexModel *m)
{
    int texs[256];
    int max = 0;
    unsigned i, j, k, d;
    int nTex, t;
    CTexGroupTable *table;
    TexGroup *g;

    for (i = 0; i < m->nLists; i++) {
        TexPartList *l = m->lists[i];
        for (j = 0; j < l->n; j++) {
            if (max < l->parts[j]->group)
                max = l->parts[j]->group;
        }
    }
    table = new CTexGroupTable(max + 1);
    m->table = table;
    for (k = 0; k <= max; k++) {
        nTex = 0;
        for (i = 0; i < m->nLists; i++) {
            TexPartList *l = m->lists[i];
            for (j = 0; j < l->n; j++) {
                TexPart *p = l->parts[j];
                if (p->group == k) {
                    for (d = 0; d < p->nDraws; d++) {
                        TexDraw *dr = p->draws[d];
                        for (t = 0; t < nTex; t++) {
                            if (texs[t] == dr->m0[0])
                                break;
                        }
                        if (t == nTex)
                            texs[nTex++] = dr->m0[0];
                    }
                }
            }
        }
        g = 0;
        for (i = 0; i < m->nLists; i++) {
            TexPartList *l = m->lists[i];
            for (j = 0; j < l->n; j++) {
                TexPart *p = l->parts[j];
                if (p->group == k) {
                    if (g == 0)
                        g = table->Open(p, k, nTex);
                    for (d = 0; d < p->nDraws; d++) {
                        TexDraw *dr = p->draws[d];
                        dr->bucket = table->Get(g, dr->m0);
                    }
                }
            }
        }
    }
}

/* @implements 0x0cbd88 us FreeTexGroups
   WHAT IT DOES: Deletes a model's texture group table. */
void FreeTexGroups(TexModel *m)
{
    CTexGroupTable *t = m->table;
    delete t;
}

/* @implements 0x0cbdc0 us _Z11TexFileDataPv
   WHAT IT DOES: Returns the file data as it is. */
void *TexFileData(void *p)
{
    return p;
}

/* The texture group file: a count and the offsets of its entries. */
struct TexFile {
    unsigned n;
    int offs[1];
};

/* One entry: offsets of its texture records, one of an animation record. */
struct TexEntry {
    int m0;
    int anim;
    int m8;
    unsigned n;
    int offs[1];
};

/* An animation record: type 1 holds two speeds given per second. */
struct TexAnim {
    int type;
    float u;
    float v;
};

/* A texture record: its name (looked up into a texture), and from +120 a GE command list
   ended by an opcode 11 word. Opcodes 1 and 2 mark an address pair: the marker word becomes
   the base command and the next word's offset becomes the low address bits. */
union GeCmd {
    unsigned w;
    unsigned char b[4];
};

struct TexRecord {
    void *tex;
    int m4[29];
    GeCmd cmds[1];
};

void RelocTexEntry(TexEntry *e);
void ScaleTexAnim(TexAnim *a);
void RelocTexRecord(TexRecord *r);

/* @implements 0x0cbdc8 us _Z12RelocTexFileP7TexFile
   WHAT IT DOES: Turns the file's entry offsets into pointers and relocates each entry. */
void RelocTexFile(TexFile *f)
{
    for (unsigned i = 0; i < f->n; i++) {
        f->offs[i] += (int)f;
        RelocTexEntry((TexEntry *)f->offs[i]);
    }
}

/* @implements 0x0cbe30 us _Z13RelocTexEntryP8TexEntry
   WHAT IT DOES: Relocates an entry: its animation record (scaled to per frame), its first
   word and every texture record. */
void RelocTexEntry(TexEntry *e)
{
    if (e->anim) {
        e->anim += (int)e;
        ScaleTexAnim((TexAnim *)e->anim);
    }
    e->m0 += (int)e;
    for (unsigned i = 0; i < e->n; i++) {
        e->offs[i] += (int)e;
        RelocTexRecord((TexRecord *)e->offs[i]);
    }
}

/* @implements 0x0cbec0 us _Z12ScaleTexAnimP7TexAnim
   WHAT IT DOES: Turns a type 1 animation's per second speeds into per frame ones. */
void ScaleTexAnim(TexAnim *a)
{
    if (a->type == 1) {
        a->u /= 60.0f;
        a->v /= 60.0f;
    }
}

/* @implements 0x0cbef8 us _Z14RelocTexRecordP9TexRecord
   WHAT IT DOES: Looks the record's texture up by name and patches the address pairs of
   its command list. */
void RelocTexRecord(TexRecord *r)
{
    GeCmd *c;
    int op;

    if (r->tex) {
        void *t = f_02347c(r->tex);
        if (t)
            r->tex = t;
        else
            r->tex = 0;
    }
    c = r->cmds;
    while (c->b[3] != 11) {
        op = c->b[3];
        switch (op) {
        case 1: {
            GeCmd *b = c;
            c++;
            c->w = c->w + (int)r;
            b->w = 0x10000000 | (((c->w >> 24) & 0xf) << 16);
            c->b[3] = op;
            break;
        }
        case 2: {
            GeCmd *b = c;
            c++;
            c->w = c->w + (int)r;
            b->w = 0x10000000 | (((c->w >> 24) & 0xf) << 16);
            c->b[3] = op;
            break;
        }
        }
        c++;
    }
}

/* @implements 0x0cbfb0 us TexInit0
   WHAT IT DOES: Nothing. */
void TexInit0()
{
}

/* @implements 0x0cbfb8 us TexInit1
   WHAT IT DOES: Nothing. */
void TexInit1()
{
}

/* @implements 0x0cbfc0 us TexInit2
   WHAT IT DOES: Nothing. */
void TexInit2()
{
}

/* @implements 0x0cbfc8 us _Z8TexSetupv
   WHAT IT DOES: Calls 0x1166d4 with 8. */
void TexSetup()
{
    f_1166d4(8);
}
