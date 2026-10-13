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
    int f_044e5c(int ch, unsigned char v)
    {
        Chan *c = &chan[ch];
        if (v == 0) {
            c->m52++;
            if (c->m52 < 256)
                return 1;
            Code k = huff.f_0440e0(0, c->m52 - 1);
            k.bits <<= 16 - k.len;
            f_0443e0(ch, k);
            c->m52 -= 256;
            return 1;
        }
        if (c->m52 != 0) {
            Code k = huff.f_0440e0(0, c->m52 - 1);
            k.bits <<= 16 - k.len;
            f_0443e0(ch, k);
            c->m52 = 0;
        }
        Code k = huff.f_0440e0(v, 0);
        k.bits <<= 16 - k.len;
        f_0443e0(ch, k);
        return 1;
    }
    int f_044fcc(int ch)
    {
        Chan *c = &chan[ch];
        if (c->m52 != 0) {
            Code k = huff.f_0440e0(0, c->m52 - 1);
            k.bits <<= 16 - k.len;
            f_0443e0(ch, k);
            c->m52 = 0;
        }
        return 1;
    }
    int f_04506c(Chan *c)
    {
        int r = 0;
        if (c->m52 != 0) {
            c->m52--;
            return r;
        }
        Code q;
        q.bits = c->m60.h[0];
        int len = huff.f_044128(&q);
        c->m52 = q.len;
        r = (unsigned char)q.bits;
        q = f_044500(c, len);
        c->m60.w <<= len;
        c->m60.h[0] |= q.bits;
        c->m60.h[1] = 0;
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

/* @draft 0x044014 us f_044014
   WHAT IT DOES: Builds the symbol table: for every code of every length, finds the symbol with
   that code and length and records it at the code's index. */
void CHuffman::f_044014()
{
    for (int k = 0; D_1d2d04[k].len != 0; k++) {
        for (int j = 0; j < D_1d2d04[k].n; j++) {
            int s;
            for (s = 0; s < 512; s++) {
                if (D_1d1d04[s].len == D_1d2d04[k].len && D_1d1d04[s].bits == D_1d2d04[k].first + j)
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
