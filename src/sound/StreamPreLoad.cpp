/* The stream pre-load object file (retail 0x095cb8 to 0x095f84, Stream::CStreamPreLoad): the
   pre-load header and buffer of the streamed sound pack (one pack). The header tells the
   unit size, the number of streams, the pack size and where each stream sits in the
   buffer. */

void f_093f90(const char *fmt, ...);

extern "C" {
int f_114ac0(void *header);
int f_114ae4(void *header);
int f_114b08(void *header);
int f_114b2c(void *header, int stream);
}

namespace Stream {

class CStreamPreLoad {
public:
    CStreamPreLoad();
    ~CStreamPreLoad();
    int f_095ce0(int pack, void *buf);
    int f_095d44(int pack);
    int f_095d8c(int pack, void *header);
    int f_095de8(int pack);
    int f_095e24(int pack);
    int f_095e70(int pack);
    int f_095ebc(int pack);
    char *f_095f08(int pack, int stream);

    void *m0;   /* the pre-load header */
    char *m4;   /* the pre-load buffer */
};

/* @implements 0x095cb8 us _ZN6Stream14CStreamPreLoadC2Ev
   WHAT IT DOES: Makes the pre-load data with no header and no buffer (base object
   constructor). */
/* @implements 0x095cc4 us _ZN6Stream14CStreamPreLoadC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CStreamPreLoad::CStreamPreLoad()
{
    m0 = 0;
    m4 = 0;
}

/* @implements 0x095cd0 us _ZN6Stream14CStreamPreLoadD2Ev
   WHAT IT DOES: Nothing to release (base object destructor). */
/* @implements 0x095cd8 us _ZN6Stream14CStreamPreLoadD1Ev
   WHAT IT DOES: Nothing to release (complete object destructor). */
CStreamPreLoad::~CStreamPreLoad()
{
}

/* @implements 0x095ce0 us f_095ce0
   WHAT IT DOES: Takes the pack's pre-load buffer. Returns 0, or -1 for a bad pack or no
   buffer. */
int CStreamPreLoad::f_095ce0(int pack, void *buf)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: SetBuff Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (!buf) {
        f_093f90("StreamPreLoad: SetBuff Failed! Buffer is NULL\n");
        return -1;
    }
    m4 = (char *)buf;
    f_093f90("StreamPreLoad: PackID[%d] SetBuff[0x%x]\n", pack, buf);
    return 0;
}

/* @implements 0x095d44 us f_095d44
   WHAT IT DOES: Forgets the pack's pre-load buffer. Returns 0, or -1 for a bad pack. */
int CStreamPreLoad::f_095d44(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: ResetBuff Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    m4 = 0;
    f_093f90("StreamPreLoad: PackID[%d] ResetBuff\n", pack);
    return 0;
}

/* @implements 0x095d8c us f_095d8c
   WHAT IT DOES: Registers the pack's pre-load header. Returns 0, or -1 for a bad pack. */
int CStreamPreLoad::f_095d8c(int pack, void *header)
{
    if (pack >= 0 && pack < 1) {
        f_093f90("StreamPreLoad: SetHeader PackID[%d]\n", pack);
        m0 = header;
    } else {
        f_093f90("StreamPreLoad: SetHeader Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    return 0;
}

/* @implements 0x095de8 us f_095de8
   WHAT IT DOES: Whether the pack's pre-load header is registered. */
int CStreamPreLoad::f_095de8(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: IsHeaderRegistered Failed! Invalid PackID[%d]\n", pack);
        return 0;
    }
    return m0 != 0;
}

/* @implements 0x095e24 us f_095e24
   WHAT IT DOES: Returns the pack's pre-load unit size, or -1. */
int CStreamPreLoad::f_095e24(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: GetUnitSize Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (!m0) {
        f_093f90("StreamPreLoad: GetUnitSize Failed! Pack[%d] has not been Registered yet.\n", pack);
        return -1;
    }
    return f_114ac0(m0);
}

/* @implements 0x095e70 us f_095e70
   WHAT IT DOES: Returns the pack's number of pre-loaded streams, or -1. */
int CStreamPreLoad::f_095e70(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: GetStreamNum Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (!m0) {
        f_093f90("StreamPreLoad: GetStreamNum Failed! Pack[%d] has not been Registered yet.\n", pack);
        return -1;
    }
    return f_114ae4(m0);
}

/* @implements 0x095ebc us f_095ebc
   WHAT IT DOES: Returns the pack's pre-load size, or -1. */
int CStreamPreLoad::f_095ebc(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: GetPackSize Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (!m0) {
        f_093f90("StreamPreLoad: GetPackSize Failed! Pack[%d] has not been Registered yet.\n", pack);
        return -1;
    }
    return f_114b08(m0);
}

/* @draft 0x095f08 us f_095f08
   WHAT IT DOES: Returns where a stream sits in the pack's pre-load buffer, or 0.
   Remaining difference: retail keeps the header loaded for the test in v1 and passes it to
   the lookup, with the success path out of line after the shared log call; here the layout
   and the header's register differ. */
char *CStreamPreLoad::f_095f08(int pack, int stream)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamPreLoad: SearchBuffAddr Failed! Invalid PackID[%d]\n", pack);
    } else if (!m0) {
        f_093f90("StreamPreLoad: SearchBuffAddr Failed! Pack[%d] has not been Registered yet.\n", pack);
    } else if (m4) {
        int off = f_114b2c(m0, stream);
        if (off < 0)
            return 0;
        return m4 + off;
    } else {
        f_093f90("StreamPreLoad: SearchBuffAddr Failed! Buff[%d] has not been Registered yet.\n", pack);
    }
    return 0;
}

}
