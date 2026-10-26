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

/* @implements 0x0fed1c us f_0fed1c
   WHAT IT DOES: Writes three GE commands at the list pointer: a clip region command (0x5c)
   with 0xffffff, a 0x5d command with 0xff, and a 0x20 command with 1; returns the pointer past
   them. */
extern "C" unsigned int *f_0fed1c(unsigned int *p)
{
    /* Each step is its own statement, so the pointer is stepped in place between the stores
       (with *p++ the steps fold into store offsets). */
    *p = 0x5cffffff;
    p++;
    *p = 0x5d0000ff;
    p++;
    *p = 0x20000001;
    p++;
    return p;
}
