/* The plain 9-bit coder (retail 0x045128 to 0x0451b4): the same interface as the Huffman
   coder (Huffman.cpp), with every symbol coded in 9 bits: a byte as itself, a zero run as
   0x100 plus its length. Nothing in the game calls it. */

/* A symbol's code and its length; when decoding, len holds the zero-run length. */
struct Code {
    void Set(unsigned short b, int l)
    {
        bits = b;
        len = l;
    }
    unsigned short bits;
    int len;
};

union Word {
    void Set(unsigned short v)
    {
        h[1] = 0;
        h[0] = v;
    }
    unsigned int w;
    unsigned short h[2];
    unsigned char b[4];
};

class CRawCoder {
public:
    Code f_045128(unsigned char run, unsigned char sym);
    int f_045168(Code *c);
};

/* @implements 0x045128 us f_045128
   WHAT IT DOES: The 9-bit code of a zero run (when run is given) or of a byte. */
Code CRawCoder::f_045128(unsigned char run, unsigned char sym)
{
    Code r;
    if (run != 0)
        r.Set(run | 0x100, 9);
    else
        r.Set(sym, 9);
    return r;
}

/* @implements 0x045168 us f_045168
   WHAT IT DOES: Decodes the 9-bit code at the top of c->bits into a byte (bits) or a zero run
   (len). Returns the code length, 9. */
int CRawCoder::f_045168(Code *c)
{
    Word w;
    w.Set(c->bits);
    w.w <<= 9;
    if (w.b[3] != 0) {
        c->len = 0;
        c->bits = w.b[2];
    } else {
        c->bits = 0;
        c->len = w.b[2];
    }
    return 9;
}
