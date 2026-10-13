/* The Huffman coder and the channel packer (retail 0x043f7c to 0x045128). The packer keeps up
   to 16 byte channels in one work buffer of 256-byte blocks, chained through a block table and
   handed out from a free list. A channel is written as Huffman codes of its bytes, with runs of
   zero bytes coded as run lengths; it is read back by decoding the same codes. Is::CHuffman
   holds no data of its own: its tables are global (D_1d1d04, a code and length per symbol;
   D_1d2d04, the canonical code ranges per length; D_240bfc, the symbol of each code, built by
   the constructor). The channel functions after the static initialisation are inline methods
   emitted out of line. */

extern "C" {
void f_131e60(void *);
void f_131ee4(void *);
}

/* A symbol's code: the code left-aligned or right-aligned in 16 bits and its length. When
   decoding, len holds the zero-run length instead. */
struct Code {
    void Align() { bits <<= 16 - len; }
    void SetBits(unsigned short b) { bits = b; }
    unsigned short bits;
    int len;
};

/* The codes of one length: the length, how many, the first index into the symbol table and the
   first code. The list ends with a zero length. */
struct CodeRange {
    unsigned short len;
    unsigned short n;
    unsigned short base;
    unsigned short first;
};

extern Code D_1d1d04[];
extern CodeRange D_1d2d04[];
extern unsigned short D_240bfc[];

namespace Is {
class CHuffman {
public:
    CHuffman();
    virtual ~CHuffman();
    void f_044014();
    Code f_0440e0(unsigned char run, unsigned char sym);
    void f_044120();
    int f_044128(Code *c);
};
}

using namespace Is;

/* A position in a channel's block chain: block, byte in the block and bit in the byte. */
struct Pos {
    int blk;
    int pos;
    int bit;
    void Set(int b)
    {
        blk = b;
        pos = 0;
        bit = 0;
    }
    void Clear()
    {
        blk = 0;
        pos = 0;
        bit = 0;
    }
};

union Word {
    unsigned int Get() { return w; }
    void Set(unsigned short v)
    {
        h[1] = 0;
        h[0] = v;
    }
    unsigned int w;
    unsigned short h[2];
    unsigned char b[4];
};

/* One channel of the packer. */
struct Chan {
    int m0;
    int m4;     /* first block */
    Pos wr;
    Pos rd;
    int m32;    /* bytes written */
    int m36;    /* bytes put */
    int m40;    /* bytes read */
    int m44;
    char m48;
    int m52;    /* zero run */
    int m56;    /* state of the serialiser */
    Word m60;   /* bits read ahead */
    void Init()
    {
        m0 = 0;
        m4 = 0;
        m32 = 1;
        m36 = 0;
        m40 = 0;
        m44 = 0;
        m48 = 0;
        m52 = 0;
        wr.Clear();
        rd.Clear();
        m60.w = 0;
    }
};

class CCodec {
public:
    int f_0441e4();
    void f_04420c(int b);
    int f_044228();
    void f_044230(Chan c);
    void f_044294(int ch, int bits, int n);
    void f_0443e0(int ch, Code c);
    void f_04449c(Pos *p, int n);
    Code f_044500(Chan *c, int n);
    int f_044608(int ch);
    void f_04461c(int ch);
    int f_044644(int ch);
    int f_0447ac(unsigned char *p, int len);
    int f_0449c0(int ch, unsigned char v);
    int f_044a28(int ch);
    int f_044a68(int ch);
    int f_044aa4(unsigned char *buf, int n);
    int f_044b44(int ch, int mode);
    void f_044c3c(int ch);
    void f_044cd4(int ch);
    int f_044d30();
    void f_044d98();
    void Put(int ch, Code k)
    {
        k.bits <<= 16 - k.len;
        f_0443e0(ch, k);
    }
    void PutRef(int ch, Code &k)
    {
        k.bits <<= 16 - k.len;
        f_0443e0(ch, k);
    }
    __attribute__((noinline)) int f_044e5c(int ch, unsigned char v)
    {
        Chan *c = &chan[ch];
        Code k;
        if (v != 0) {
            if (c->m52 != 0) {
                k = huff.f_0440e0(0, c->m52 - 1);
                k.bits <<= 16 - k.len;
                f_0443e0(ch, k);
                c->m52 = 0;
            }
            k = huff.f_0440e0(v, 0);
            k.bits <<= 16 - k.len;
            f_0443e0(ch, k);
            return 1;
        }
        c->m52++;
        if (c->m52 < 256)
            return 1;
        k = huff.f_0440e0(0, c->m52 - 1);
        k.bits <<= 16 - k.len;
        f_0443e0(ch, k);
        c->m52 -= 256;
        return 1;
    }
    __attribute__((noinline)) int f_044fcc(int ch)
    {
        Chan *c = &chan[ch];
        Code k;
        if (c->m52 != 0) {
            k = huff.f_0440e0(0, c->m52 - 1);
            k.Align();
            f_0443e0(ch, k);
            c->m52 = 0;
        }
        return 1;
    }
    __attribute__((noinline)) int f_04506c(Chan *c)
    {
        int r = 0;
        if (c->m52 != 0) {
            c->m52--;
        } else {
            Code q;
            q.bits = c->m60.h[0];
            int len = huff.f_044128(&q);
            c->m52 = q.len;
            r = (unsigned char)q.bits;
            q = f_044500(c, len);
            c->m60.w <<= len;
            c->m60.h[1] = 0;
            c->m60.h[0] |= q.bits;
        }
        return r;
    }

    unsigned short list[512];
    int count;
    unsigned short next[512];
    unsigned char *data;
    Chan chan[16];
    CHuffman huff;
    int m3084;
};

/* The object made by the library at startup. */
struct CLibObject {
    CLibObject() { f_131e60(this); }
    ~CLibObject() { f_131ee4(this); }
    char m0[1024];
};

/* @implements 0x043f7c us _ZN2Is8CHuffmanC2Ev
   WHAT IT DOES: Makes the coder and builds its symbol table.
   @implements 0x043fa4 us _ZN2Is8CHuffmanC1Ev
   WHAT IT DOES: The same, as the complete-object constructor. */
CHuffman::CHuffman()
{
    f_044014();
}

/* @implements 0x043fcc us _ZN2Is8CHuffmanD2Ev
   WHAT IT DOES: Destroys the coder.
   @implements 0x043fdc us _ZN2Is8CHuffmanD1Ev
   WHAT IT DOES: Destroys the coder.
   @implements 0x043fec us _ZN2Is8CHuffmanD0Ev
   WHAT IT DOES: Destroys the coder and frees it. */
CHuffman::~CHuffman() {}

/* @implements 0x044014 us f_044014
   WHAT IT DOES: Builds the symbol table: for every code of every length, finds the symbol with
   that code and length and records it at the code's index. */
void CHuffman::f_044014()
{
    for (int k = 0; D_1d2d04[k].len != 0; k++) {
        int first = D_1d2d04[k].first;
        for (int j = 0; j < D_1d2d04[k].n; j++) {
            int s;
            for (s = 0; s < 512; s++) {
                if (D_1d1d04[s].len == D_1d2d04[k].len && D_1d1d04[s].bits == first + j)
                    break;
            }
            D_240bfc[D_1d2d04[k].base + j] = s;
        }
    }
}

/* @implements 0x0440e0 us f_0440e0
   WHAT IT DOES: The code of a zero run (run - 1 + 256, when run is given) or of a byte. */
Code CHuffman::f_0440e0(unsigned char run, unsigned char sym)
{
    int s = run | 0x100;
    if (run == 0)
        s = sym;
    return D_1d1d04[s];
}

/* @implements 0x044120 us f_044120
   WHAT IT DOES: Nothing. */
void CHuffman::f_044120() {}

/* @implements 0x044128 us f_044128
   WHAT IT DOES: Decodes the code at the top of c->bits: stores the byte in bits (and 0 in len)
   or the zero-run length in len (and 0 in bits) and returns the code's length; for an invalid
   code, a run of 1 and length 16. */
int CHuffman::f_044128(Code *c)
{
    int v = c->bits;
    for (int k = 0; D_1d2d04[k].len != 0; k++) {
        int x = v >> (16 - D_1d2d04[k].len);
        if (x < D_1d2d04[k].first + D_1d2d04[k].n) {
            int s = D_240bfc[D_1d2d04[k].base + (x - D_1d2d04[k].first)];
            if (s & 0x100) {
                c->bits = s & 0xff;
                c->len = 0;
            } else {
                c->len = s & 0xff;
                c->bits = 0;
            }
            return D_1d2d04[k].len;
        }
    }
    c->len = 1;
    c->bits = 0;
    return 16;
}

/* @implements 0x0441e4 us f_0441e4
   WHAT IT DOES: Takes a block from the free list; -1 when none is left. */
int CCodec::f_0441e4()
{
    int r = -1;
    if (count != 0) {
        count--;
        r = list[count];
    }
    return r;
}

/* @implements 0x04420c us f_04420c
   WHAT IT DOES: Returns block b to the free list. */
void CCodec::f_04420c(int b)
{
    list[count] = b;
    count++;
}

/* @implements 0x044228 us f_044228
   WHAT IT DOES: The number of free blocks. */
int CCodec::f_044228()
{
    return count;
}

/* @implements 0x044230 us f_044230
   WHAT IT DOES: Clears the byte at a channel's write position. */
void CCodec::f_044230(Chan c)
{
    data[c.wr.pos + (c.wr.blk << 8)] = 0;
}

/* @draft 0x044294 us f_044294
   WHAT IT DOES: Ors bits into the byte at channel ch's write position; once the byte holds n of
   8 bits it moves to the next byte, taking a new block at a block's end (flagging overflow when
   none is free), clears it and counts it. */
void CCodec::f_044294(int ch, int bits, int n)
{
    unsigned char *p = &data[chan[ch].wr.pos + (chan[ch].wr.blk << 8)];
    bits |= *p;
    *p = bits;
    if (n < 8) {
        chan[ch].wr.bit = n;
        return;
    }
    chan[ch].wr.bit = 0;
    if (chan[ch].wr.pos == 255) {
        chan[ch].wr.pos = 0;
        int b = f_0441e4();
        if (b < 0) {
            m3084 = 1;
        } else {
            int old = chan[ch].wr.blk;
            chan[ch].wr.blk = b;
            next[old] = b;
        }
        f_044230(chan[ch]);
        chan[ch].m32++;
    } else {
        chan[ch].wr.pos++;
        f_044230(chan[ch]);
        chan[ch].m32++;
    }
}

/* @draft 0x0443e0 us f_0443e0
   WHAT IT DOES: Writes a left-aligned code of c.len bits to channel ch, a byte at a time. */
void CCodec::f_0443e0(int ch, Code c)
{
    Word w;
    w.h[1] = 0;
    w.h[0] = c.bits;
    int n = chan[ch].wr.bit + c.len;
    w.w <<= 8 - chan[ch].wr.bit;
    for (int k = 2; n != 0; k--) {
        int m = n < 8 ? n : 8;
        n -= m;
        f_044294(ch, w.b[k], m);
    }
}

/* @implements 0x04449c us f_04449c
   WHAT IT DOES: Moves a read position on by n bits, following the block chain. */
void CCodec::f_04449c(Pos *p, int n)
{
    p->bit += n;
    while (p->bit >= 8) {
        p->bit -= 8;
        if (p->pos == 255) {
            p->pos = 0;
            p->blk = next[p->blk];
        } else {
            p->pos++;
        }
    }
}

/* @draft 0x044500 us f_044500
   WHAT IT DOES: Reads the next n bits of channel c (right-aligned) and moves past them. */
Code CCodec::f_044500(Chan *c, int n)
{
    Pos p = c->rd;
    Word w;
    w.b[3] = 0;
    for (int k = 2; k >= 0; k--) {
        w.b[k] = data[p.pos + (p.blk << 8)];
        if (p.pos == 255) {
            p.pos = 0;
            p.blk = next[p.blk];
        } else {
            p.pos++;
        }
    }
    w.w >>= 8 - p.bit;
    w.h[1] = 0;
    w.w <<= n;
    Code r;
    r.bits = w.h[1];
    r.len = n;
    f_04449c(&c->rd, n);
    return r;
}

/* @implements 0x044608 us f_044608
   WHAT IT DOES: The size channel ch takes when saved: its bytes plus an 11-byte header. */
int CCodec::f_044608(int ch)
{
    return chan[ch].m32 + 11;
}

/* @implements 0x04461c us f_04461c
   WHAT IT DOES: Starts saving channel ch: rewinds it and sets the serialiser to its first
   state. */
void CCodec::f_04461c(int ch)
{
    chan[ch].rd.Set(chan[ch].m4);
    chan[ch].m56 = 12;
}

/* @draft 0x044644 us f_044644
   WHAT IT DOES: The next byte of channel ch's saved form: a serialiser that gives the channel
   number, its flag, its bit count, the written and put byte counts, then the data bytes; 0 once
   done (and after the last data byte it rewinds the channel). */
int CCodec::f_044644(int ch)
{
    unsigned char r = 0;
    Word t;
    switch (chan[ch].m56) {
    case 0:
        r = 0;
        break;
    case 1:
        r = data[chan[ch].rd.pos + (chan[ch].rd.blk << 8)];
        if (chan[ch].rd.blk == chan[ch].wr.blk && chan[ch].rd.pos == chan[ch].wr.pos) {
            f_044cd4(ch);
            chan[ch].m56--;
        } else if (chan[ch].rd.pos == 255) {
            chan[ch].rd.pos = 0;
            chan[ch].rd.blk = next[chan[ch].rd.blk];
        } else {
            chan[ch].rd.pos++;
        }
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        t.w = chan[ch].m36;
        r = t.b[5 - chan[ch].m56];
        chan[ch].m56--;
        break;
    case 6:
    case 7:
    case 8:
    case 9:
        t.w = chan[ch].m32;
        r = t.b[9 - chan[ch].m56];
        chan[ch].m56--;
        break;
    case 10:
        r = chan[ch].wr.bit;
        chan[ch].m56--;
        break;
    case 11:
        r = chan[ch].m0;
        chan[ch].m56--;
        break;
    case 12:
        r = ch;
        chan[ch].m56--;
        break;
    }
    return r;
}

/* @draft 0x0447ac us f_0447ac
   WHAT IT DOES: Loads saved channels from len bytes at p (the form f_044644 gives): each
   channel's header, then its data copied into fresh blocks. Returns how many channels were
   loaded. */
int CCodec::f_0447ac(unsigned char *p, int len)
{
    unsigned char *end = p + len;
    int n = 0;
    while (p != end) {
        int ch = *p++;
        Chan *c = &chan[ch];
        if (c->m0 != 0)
            f_044c3c(ch);
        c->m0 = *p++;
        c->wr.bit = *p++;
        unsigned char w[4];
        w[0] = *p++;
        w[1] = *p++;
        w[2] = *p++;
        w[3] = *p++;
        c->m32 = *(int *)w;
        w[0] = *p++;
        w[1] = *p++;
        w[2] = *p++;
        w[3] = *p++;
        c->m36 = *(int *)w;
        if (c->m0 == 0) {
            p += c->m32;
            continue;
        }
        int b = f_0441e4();
        c->m4 = b;
        c->rd.Set(b);
        int left = c->m32;
        while (left != 0) {
            if (left > 256) {
                unsigned char *d = &data[c->rd.blk << 8];
                for (int k = 0; k < 256; k++)
                    *d++ = *p++;
                int nb = f_0441e4();
                next[c->rd.blk] = nb;
                c->rd.blk = nb;
                left -= 256;
            } else {
                c->wr.pos = left - 1;
                unsigned char *d = &data[c->rd.blk << 8];
                for (int k = 0; k < left; k++)
                    *d++ = *p++;
                c->wr.blk = c->rd.blk;
                left = 0;
            }
        }
        f_044cd4(ch);
        n++;
    }
    return n;
}

/* @implements 0x0449c0 us f_0449c0
   WHAT IT DOES: Puts byte v into channel ch (-1 once the buffer has overflowed). */
int CCodec::f_0449c0(int ch, unsigned char v)
{
    if (m3084 != 0)
        return -1;
    f_044e5c(ch, v);
    chan[ch].m44 = 1;
    chan[ch].m36++;
    return 0;
}

/* @implements 0x044a28 us f_044a28
   WHAT IT DOES: Ends a frame of channel ch: writes out a pending zero run. */
int CCodec::f_044a28(int ch)
{
    f_044fcc(ch);
    chan[ch].m44 = 0;
    return 0;
}

/* @implements 0x044a68 us f_044a68
   WHAT IT DOES: Gets the next byte of channel ch. */
int CCodec::f_044a68(int ch)
{
    Chan *c = &chan[ch];
    int r = f_04506c(c);
    c->m40++;
    return r;
}

/* @implements 0x044aa4 us f_044aa4
   WHAT IT DOES: Sets the packer up on n blocks of buf (at most 512): all blocks free, every
   channel closed. */
int CCodec::f_044aa4(unsigned char *buf, int n)
{
    if (n > 512)
        return -1;
    for (int k = 0; k < n; k++) {
        list[k] = n - 1 - k;
        next[k] = 0;
    }
    count = n;
    data = buf;
    for (int c = 0; c < 16; c++)
        chan[c].Init();
    m3084 = 0;
    return 0;
}

/* @implements 0x044b44 us f_044b44
   WHAT IT DOES: Opens channel ch for writing in the given mode (non-zero) with a fresh block;
   -1 when it is already open. */
int CCodec::f_044b44(int ch, int mode)
{
    if (chan[ch].m0 != 0 || mode == 0)
        return -1;
    Chan *c = &chan[ch];
    c->m0 = 0;
    c->m4 = 0;
    c->m32 = 1;
    c->m36 = 0;
    c->m40 = 0;
    c->m44 = 0;
    c->m48 = 0;
    c->m52 = 0;
    c->wr.Clear();
    c->rd.Clear();
    chan[ch].m0 = mode;
    chan[ch].m60.w = 0;
    int b = f_0441e4();
    c->rd.blk = c->wr.blk = c->m4 = b;
    f_044230(*c);
    return 0;
}

/* @implements 0x044c3c us f_044c3c
   WHAT IT DOES: Closes channel ch and frees its blocks. */
void CCodec::f_044c3c(int ch)
{
    if (chan[ch].m0 == 0)
        return;
    int b = chan[ch].m4;
    chan[ch].m0 = 0;
    while (chan[ch].wr.blk != b) {
        f_04420c(b);
        b = next[b];
    }
    f_04420c(b);
    chan[ch].m44 = 0;
    m3084 = 0;
}

/* @implements 0x044cd4 us f_044cd4
   WHAT IT DOES: Rewinds channel ch for reading and reads its first 16 bits ahead. */
void CCodec::f_044cd4(int ch)
{
    chan[ch].rd.Set(chan[ch].m4);
    chan[ch].m40 = 0;
    chan[ch].m52 = 0;
    Code r;
    r = f_044500(&chan[ch], 16);
    Word *m = &chan[ch].m60;
    m->h[1] = 0;
    m->h[0] = r.bits;
}

/* @implements 0x044d30 us f_044d30
   WHAT IT DOES: -1 when the free blocks may not last the frame (fewer than the open, written
   channels whose block is nearly full), else 0. */
int CCodec::f_044d30()
{
    int n = 0;
    for (int k = 0; k < 16; k++) {
        if (chan[k].m0 != 0 && chan[k].m44 != 0 && chan[k].wr.pos >= 254)
            n++;
    }
    if (f_044228() < n)
        return -1;
    return 0;
}

/* @implements 0x044d98 us f_044d98
   WHAT IT DOES: Nothing. */
void CCodec::f_044d98() {}

/* @implements 0x044da0 us __static_initialization_and_destruction_0
   WHAT IT DOES: Makes (and at exit destroys) the library object below.
   @implements 0x044e1c us _GLOBAL__I
   WHAT IT DOES: Static construction of this object file.
   @implements 0x044e3c us _GLOBAL__D
   WHAT IT DOES: Static destruction of this object file. */
CLibObject D_240ffc;

/* The channel coding methods, inline and emitted out of line after the static
   initialisation.
   @draft 0x044e5c us f_044e5c
   WHAT IT DOES: Writes byte v to channel ch: zero bytes are counted into a run (written as a run
   code every 256), any other byte first writes the pending run, then its own code.
   @draft 0x044fcc us f_044fcc
   WHAT IT DOES: Writes a pending zero run of channel ch.
   @draft 0x04506c us f_04506c
   WHAT IT DOES: Reads the next byte of channel c: from a pending zero run, or by decoding the
   bits read ahead and refilling them. */
