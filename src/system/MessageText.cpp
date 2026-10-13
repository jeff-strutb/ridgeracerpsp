/* The message text object file (retail 0x07d74c to 0x07df70). A loaded message file holds
   text in glyph codes: a header, per font tables mapping character codes to glyph codes, an
   id table and the strings. Eight argument slots hold either a string converted to glyph
   codes or the id of another message. A message is laid out into lines of positioned glyphs,
   expanding arguments and nested messages and aligning each line. */

#include <stdio.h>

/* One font's entry in the message file header (32 bytes). */
struct MsgFontEnt {
    int m0;
    int m4;
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
};

/* The message file header. */
struct MsgHdr {
    int nfont;
    int nmsg;
    int ids;
    int m12;
    MsgFontEnt font[1];
};

/* One font's tables, resolved to addresses. */
struct MsgFont {
    char *m0;
    char *m4;
    char *m8;
};

/* One message id and its string's offset (in glyph codes). */
struct MsgId {
    int id;
    int off;
};

/* An argument slot: a glyph code string, or {-1, -1} followed by a message id. */
union MsgArg {
    short text[32];
    struct {
        short m0;
        short m2;
        int id;
    } ref;
};

/* One positioned glyph of a laid out line (16 bytes). */
struct MsgGlyph {
    short x;
    short m2;
    short m4[6];
};

struct CMessageText {
    CMessageText();
    ~CMessageText();

    int nmsg;
    int nfont;
    MsgHdr *hdr;
    MsgFontEnt *fontEnt;
    MsgFont font[32];
    MsgId *ids;
    short *strs;
    int m408;
    MsgArg arg[8];
};

extern short D_1d3a3c[];

extern "C" void f_07d89c(CMessageText *m, int slot, const char *s, int unused);
extern "C" short *f_07deec(CMessageText *m, int id);
extern "C" void f_07dec4(CMessageText *m, MsgGlyph *g, int n, int dx);

/* @implements 0x07d74c us _ZN12CMessageTextC2Ev
   WHAT IT DOES: Base object constructor: no message file loaded. */
/* @implements 0x07d754 us _ZN12CMessageTextC1Ev
   WHAT IT DOES: Complete object constructor, the same. */
CMessageText::CMessageText()
{
    hdr = 0;
}

/* @implements 0x07d75c us _ZN12CMessageTextD2Ev
   WHAT IT DOES: Base object destructor: nothing to free. */
/* @implements 0x07d764 us _ZN12CMessageTextD1Ev
   WHAT IT DOES: Complete object destructor, the same. */
CMessageText::~CMessageText()
{
}

/* @implements 0x07d76c us f_07d76c
   WHAT IT DOES: Attaches a loaded message file: takes the counts from its header, resolves
   each font's three tables and the id and string tables to addresses, names the eight
   argument slots "ARG 0" to "ARG 7" and sets the limit at +408 to 100000. Returns 0. */
extern "C" int f_07d76c(CMessageText *m, MsgHdr *h)
{
    char buf[32];
    int i;
    int ids;

    m->hdr = h;
    m->nfont = h->nfont;
    m->nmsg = h->nmsg;
    m->fontEnt = h->font;
    ids = h->ids;
    for (i = 0; i < m->nfont; i++) {
        m->font[i].m0 = (char *)m->hdr + m->fontEnt[i].m4;
        m->font[i].m4 = (char *)m->hdr + m->fontEnt[i].m8;
        m->font[i].m8 = (char *)m->hdr + m->fontEnt[i].m12;
    }
    m->ids = (MsgId *)((char *)m->hdr + ids);
    m->strs = (short *)(m->ids + m->nmsg);
    for (i = 0; i < 8; i++) {
        sprintf(buf, "ARG %d", i);
        f_07d89c(m, i, buf, 0);
    }
    m->m408 = 100000;
    return 0;
}

/* @implements 0x07d878 us f_07d878
   WHAT IT DOES: Detaches the message file. */
extern "C" void f_07d878(CMessageText *m)
{
    m->hdr = 0;
}

/* @implements 0x07d880 us f_07d880
   WHAT IT DOES: Makes an argument slot refer to another message by id. */
extern "C" void f_07d880(CMessageText *m, int slot, int id)
{
    m->arg[slot].text[1] = m->arg[slot].text[0] = -1;
    m->arg[slot].ref.id = id;
}

/* @draft 0x07d89c us f_07d89c
   WHAT IT DOES: Sets an argument slot to an ASCII string converted to the small font's glyph
   codes: capitals from 2, lower case from 28, digits from 54, '.' as 127 and anything else as
   1; the string is ended with 0.
   REMAINING DIFFERENCE: the control flow and the lbu/seb loads match; retail keeps the
   capital test in v1 and the glyph value in v0 and puts the lower case sltiu in the first
   branch's delay slot, where this build puts the -63 add (register allocation order). */
extern "C" void f_07d89c(CMessageText *m, int slot, const char *s, int unused)
{
    short *d = m->arg[slot].text;
    int i;

    for (i = 0; s[i]; i++) {
        if ((unsigned char)(s[i] - 'A') < 26)
            *d = s[i] - 'A' + 2;
        else if ((unsigned char)(s[i] - 'a') < 26)
            *d = s[i] - 'a' + 28;
        else if ((unsigned char)(s[i] - '0') < 10)
            *d = s[i] - '0' + 54;
        else if (s[i] == '.')
            *d = 127;
        else
            *d = 1;
        d++;
    }
    *d = 0;
}
