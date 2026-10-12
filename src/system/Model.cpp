/* Models (retail 0x024fb4 to 0x026ab0): a model file holds up to eight parts, each a set of
   meshes whose primitives carry ready made GE command lists. Setting a model up turns the
   file's offsets into addresses, looks up the primitives' textures and points their vertex
   and index commands at their data. Drawing a part culls it against the view, loads its
   bones into the vector unit and calls the command lists of its primitives. Also here: the
   short GE command lists that set the render state for model drawing, and the call lists of
   a part's primitives. */

#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

/* A texture record of the texture info store. */
struct CInfo;

/* One primitive: up to three textures, then its GE command list. Vertex and index address
   commands follow a placeholder word that becomes their BASE command. */
struct ModelPrim {
    CInfo *tex[3];
    int m12[3];
    unsigned int list[1];
};

/* A mesh: the offset of its data, and its primitives. */
struct ModelMesh {
    int data;
    unsigned int count;
    ModelPrim *prim[1];
};

/* A part: its meshes, twelve bytes each. */
struct ModelPartEntry {
    int m0;
    ModelMesh *mesh;
    int m8;
};
struct ModelPart {
    unsigned int count;
    ModelPartEntry e[1];
};

/* The model file header. */
struct ModelHeader {
    int m0;
    char m4;
    signed char done;
    short m6;
    ModelPart *part[8];
    int m40;
};

/* A model instance as the game keeps it. */
struct CModel {
    ModelHeader *data;
};

/* A call list of primitive lists: its own command list, then the primitives. */
struct PrimList {
    int list;
    unsigned int count;
    char *prim[1];
};

extern "C" {
void sceKernelDcacheWritebackAll(void);
void f_022010(int stencil);
unsigned int *f_02202c(int flags, unsigned int *p);
CInfo *f_02347c(unsigned int id);
void f_024a28(void);
unsigned int *f_024a3c(CInfo *info, unsigned int *p);
ModelHeader *f_025280(ModelHeader *h);
void f_025288(ModelPart *g);
void f_0252f0(ModelMesh *m);
void f_025364(ModelPrim *p);
void f_025590(CModel *m, ModelPart *part);
void f_025eb8(CModel *m, ModelPart *part, int arg);
unsigned int *f_026948(unsigned int *p, char *prim, int idx);
unsigned int *f_026a6c(unsigned int *p, int addr);

/* @draft 0x024fb4 us f_024fb4
   WHAT IT DOES: Sets a model up from its file the first time it is used: turns the offsets of
   its parts (and of the extra table at +40) into addresses, sets each part up, writes the
   data cache back so the GE sees the changes, and marks the file as set up. Returns the file,
   or 0 if there is none.
   Remaining difference: retail sets the part pointer register (move s0,s2) before the
   set up test, leaving li s1,7 in the bltz slot; here the move fills the slot. */
int f_024fb4(CModel *m)
{
    ModelHeader *h = f_025280(m->data);
    int i;

    if (h == 0)
        return 0;
    if (h->done >= 0) {
        for (i = 0; i < 8; i++) {
            if (h->part[i]) {
                h->part[i] = (ModelPart *)((char *)h->part[i] + (int)h);
                f_025288(h->part[i]);
            }
        }
        if (h->m40)
            h->m40 += (int)h;
        sceKernelDcacheWritebackAll();
        h->done |= 0x80;
    }
    return (int)m->data;
}

/* @implements 0x025068 us f_025068
   WHAT IT DOES: Forgets the last texture and palette selected, then writes the render state
   for drawing models without a stencil (alpha test, blending and depth function settings)
   to a GE list. Returns the end of the list. */
unsigned int *f_025068(unsigned int *p)
{
    f_024a28();
    *p = 0xe0000000;
    p++;
    *p = 0xe1ffffff;
    p++;
    *p = 0x5c000000;
    p++;
    *p = 0x5d0000ff;
    p++;
    *p = 0x21000001;
    p++;
    *p = 0x5e000001;
    p++;
    *p = 0x5b418000;
    p++;
    *p = 0x5f000001;
    p++;
    *p = 0x60000001;
    p++;
    return p;
}

/* @implements 0x025118 us f_025118
   WHAT IT DOES: Draws one part of a model, if the model has that part. */
void f_025118(CModel *m, int part)
{
    if (m->data->part[part])
        f_025590(m, m->data->part[part]);
}

/* @implements 0x025154 us f_025154
   WHAT IT DOES: Draws one part of a model the second way (f_025eb8), if the model has that
   part. */
void f_025154(CModel *m, int part, int arg)
{
    if (m->data->part[part])
        f_025eb8(m, m->data->part[part], arg);
}

/* @implements 0x025190 us f_025190
   WHAT IT DOES: Writes two GE commands that end the stencil pass of model drawing. Returns the
   end of the list. */
unsigned int *f_025190(unsigned int *p)
{
    *p = 0xc0000000;
    p++;
    *p = 0x4746fffe;
    p++;
    return p;
}

/* @implements 0x0251b4 us f_0251b4
   WHAT IT DOES: Clears the stencil buffer to 0 and writes the render state for the stencil
   pass of model drawing. Returns the end of the list. */
unsigned int *f_0251b4(unsigned int *p)
{
    f_022010(0);
    p = f_02202c(2, p);
    *p = 0x24000001;
    p++;
    *p = 0xdcff0002;
    p++;
    *p = 0xdd030000;
    p++;
    *p = 0xe0000000;
    p++;
    *p = 0xe1ffffff;
    p++;
    *p = 0x5c000000;
    p++;
    *p = 0x5d0000ff;
    p++;
    *p = 0x21000001;
    p++;
    return p;
}

/* @implements 0x025264 us f_025264
   WHAT IT DOES: Writes two GE commands that switch the stencil test off again. Returns the end
   of the list. */
unsigned int *f_025264(unsigned int *p)
{
    *p = 0x24000000;
    p++;
    *p = 0xc0000000;
    p++;
    return p;
}

/* @implements 0x025280 us f_025280
   WHAT IT DOES: Returns the model file it is given. */
ModelHeader *f_025280(ModelHeader *h)
{
    return h;
}

/* @implements 0x025288 us f_025288
   WHAT IT DOES: Sets a model part up: turns the offset of each of its meshes into an address
   and sets the mesh up. */
void f_025288(ModelPart *g)
{
    unsigned int i;

    for (i = 0; i < g->count; i++) {
        g->e[i].mesh = (ModelMesh *)((char *)g->e[i].mesh + (int)g);
        f_0252f0(g->e[i].mesh);
    }
}

/* @implements 0x0252f0 us f_0252f0
   WHAT IT DOES: Sets a mesh up: turns the offset of its data and of each primitive into
   addresses and sets each primitive up. */
void f_0252f0(ModelMesh *m)
{
    unsigned int i;

    m->data += (int)m;
    for (i = 0; i < m->count; i++) {
        m->prim[i] = (ModelPrim *)((char *)m->prim[i] + (int)m);
        f_025364(m->prim[i]);
    }
}

/* Points an address command at its data, which lies at the given offset from the primitive,
   and turns the word before it into the BASE command for the address's upper bits. */
static inline void Relocate(unsigned int *base, unsigned int *c, ModelPrim *p, unsigned int op)
{
    unsigned int a = *c + (unsigned int)p;
    *c = a;
    *base = ((a >> 24) & 0xf) << 16 | 0x10000000;
    ((unsigned char *)c)[3] = op;
}

/* @implements 0x025364 us f_025364
   WHAT IT DOES: Sets a primitive up: replaces each of its three texture ids by the texture's
   record (0 if it is not loaded), then walks its GE command list up to the RET command and
   points every vertex and index address command at its data, writing the BASE command for
   the address's upper bits into the word before it. */
void f_025364(ModelPrim *p)
{
    unsigned int *c;
    int i;

    for (i = 0; i < 3; i++) {
        if (p->tex[i]) {
            CInfo *t = f_02347c((unsigned int)p->tex[i]);
            if (t)
                p->tex[i] = t;
            else
                p->tex[i] = 0;
        }
    }
    c = p->list;
    while (((unsigned char *)c)[3] != 11) {
        unsigned int *base = c;
        unsigned int op = ((unsigned char *)c)[3];
        if (op == 1) {
            c++;
        } else if (op == 2) {
            c++;
        } else {
            c++;
            continue;
        }
        Relocate(base, c, p, op);
        c++;
    }
}

/* @implements 0x025440 us f_025440
   WHAT IT DOES: Returns the signed distance of a bounding plane (normal at +0, point at +48)
   from the viewer, both taken through the view matrix in M400. */
float f_025440(const float *b)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.q C300, 0(%1)\n\tlv.q C330, 48(%1)\n\tvtfm3.t C310, E400, C300\n\t"
                     "vtfm3.t C320, E400, C330\n\tvadd.t C320, C430, C320\n\tvdot.t S313, C320, C310\n\t"
                     "sv.s S313, %0" VFPU_END
                     : "=m"(r) : "r"(b) : "memory");
    return r;
}

static const float D_1a1914 = 4096.0f;

/* @implements 0x02546c us f_02546c
   WHAT IT DOES: Loads the model's view matrix (at +16, rotation scaled by 4096) into M400 and
   tests eight bounding planes against the viewer, keeping one visibility bit pair per plane
   in the halfword at +1704. */
void f_02546c(char *m)
{
    unsigned short bits;
    float zero;

    __asm__ volatile(VFPU_BEGIN "lv.q C400, 0(%0)\n\tlv.q C410, 16(%0)\n\tlv.q C420, 32(%0)\n\tlv.q C430, 48(%0)\n\t"
                     "lv.s S300, %1\n\tvscl.t C400, C400, S300\n\tvscl.t C410, C410, S300\n\tvscl.t C420, C420, S300" VFPU_END
                     : : "r"(m + 16), "m"(D_1a1914) : "memory");
    zero = 0.0f;
    bits = 0;
    if (f_025440((float *)(m + 208)) <= zero)
        bits = 0x22;
    if (zero <= f_025440((float *)(m + 272)))
        bits |= 0x44;
    if (f_025440((float *)(m + 336)) <= zero)
        bits |= 0x88;
    if (zero <= f_025440((float *)(m + 400)))
        bits |= 0x110;
    if (f_025440((float *)(m + 720)) <= zero)
        bits |= 0x200;
    if (zero <= f_025440((float *)(m + 784)))
        bits |= 0x400;
    if (f_025440((float *)(m + 848)) <= zero)
        bits |= 0x800;
    if (zero <= f_025440((float *)(m + 912)))
        bits |= 0x1000;
    *(unsigned short *)(m + 1704) = bits;
}

/* @implements 0x026898 us f_026898
   WHAT IT DOES: Writes the GE calls that draw a primitive list: a call to the list's own
   commands, then each primitive's texture selection and command list. Returns the end of the
   list. */
unsigned int *f_026898(unsigned int *p, PrimList *l, int idx)
{
    unsigned int i;
    int a = l->list;

    *p = ((a >> 24) & 0xf) << 16 | 0x10000000;
    p++;
    *p = (a & 0xffffff) | 0x0a000000;
    p++;
    for (i = 0; i < l->count; i++)
        p = f_026948(p, l->prim[i], idx);
    return p;
}

/* @implements 0x026948 us f_026948
   WHAT IT DOES: Writes the GE commands that draw one primitive with its texture number idx:
   texture mapping on with that texture selected (only if it changed), or off when it has none,
   then a call to the primitive's command list. Returns the end of the list. */
unsigned int *f_026948(unsigned int *p, char *prim, int idx)
{
    int a;

    if (((CInfo **)prim)[idx]) {
        p = f_024a3c(((CInfo **)prim)[idx], p);
        *p = 0x1e000001;
    } else {
        *p = 0x1e000000;
    }
    p++;
    a = (int)(prim + 16);
    *p = ((a >> 24) & 0xf) << 16 | 0x10000000;
    p++;
    *p = (a & 0xffffff) | 0x0a000000;
    p++;
    return p;
}

/* @implements 0x0269e8 us f_0269e8
   WHAT IT DOES: Writes the GE calls of every primitive of a list without textures, between two
   render state commands. Returns the end of the list. */
unsigned int *f_0269e8(unsigned int *p, PrimList *l)
{
    unsigned int i;

    *p = 0xc9000000;
    p++;
    for (i = 0; i < l->count; i++)
        p = f_026a6c(p, (int)l->prim[i]);
    *p = 0xc9000100;
    p++;
    return p;
}

/* @implements 0x026a6c us f_026a6c
   WHAT IT DOES: Writes a GE call to a primitive's command list (16 bytes into it). Returns the
   end of the list. */
unsigned int *f_026a6c(unsigned int *p, int prim)
{
    int a = prim + 16;

    *p = ((a >> 24) & 0xf) << 16 | 0x10000000;
    p++;
    *p = (a & 0xffffff) | 0x0a000000;
    p++;
    return p;
}

}
