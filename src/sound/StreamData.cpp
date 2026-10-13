/* The stream data object file (retail 0x095704 to 0x095c1c, Stream::CStreamData): the pack
   file headers of the streamed sounds (one pack) and the pre-load buffers that go with them.
   It answers how many files a pack holds, where a file starts and what it is called, and
   passes the pre-load requests on to its CStreamPreLoad. */

#include <string.h>

void f_093f90(const char *fmt, ...);

extern "C" {
int f_114a4c(void *header);
int f_114a70(void *header, int file);
}

/* Packs whose files are fixed rather than listed in a header (none). */
extern const int D_1a9778[] = { 0 };
/* Each pack's file name prefix. */
extern const char *const D_1a977c[] = { 0 };

int f_095c04(int pack);
char *f_095c14(int pack, int file);

namespace Stream {

/* The pre-load buffers (their own object file). */
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
    int f_095f08(int pack, int a);
    void *m0;
    void *m4;
};

class CStreamData {
public:
    CStreamData();
    ~CStreamData();
    int f_095854(int pack, void *header);
    int f_095890(int pack);
    int f_09590c(int pack, int file);
    int f_095974(int pack, int file, char *out);
    int f_095a1c(int pack, void *buf);
    int f_095a58(int pack);
    int f_095a94(int pack);
    int f_095ad4(int pack, void *header);
    int f_095b10(int pack);
    int f_095b4c(int pack);
    int f_095b88(int pack);
    int f_095bc4(int pack, int a);

    void *m0;               /* the pack header */
    CStreamPreLoad *m4;
};

/* @implements 0x095704 us _ZN6Stream11CStreamDataC2Ev
   WHAT IT DOES: Makes the pack data with no header and a new pre-load object (base object
   constructor). */
/* @implements 0x09575c us _ZN6Stream11CStreamDataC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CStreamData::CStreamData()
{
    m0 = 0;
    m4 = new CStreamPreLoad;
}

/* @implements 0x0957b4 us _ZN6Stream11CStreamDataD2Ev
   WHAT IT DOES: Deletes the pre-load object (base object destructor). */
/* @implements 0x095804 us _ZN6Stream11CStreamDataD1Ev
   WHAT IT DOES: The same (complete object destructor). */
CStreamData::~CStreamData()
{
    delete m4;
    m4 = 0;
}

/* @implements 0x095854 us f_095854
   WHAT IT DOES: Registers a pack's header. Returns 0, or -1 for a bad pack. */
int CStreamData::f_095854(int pack, void *header)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamData: SetPackHeader Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    m0 = header;
    return 0;
}

/* @draft 0x095890 us f_095890
   WHAT IT DOES: Returns the number of files in a pack, or -1.
   Remaining difference: retail returns each result straight in v0 with its own epilogue
   jump; here the results meet in v1 and are moved to v0. */
int CStreamData::f_095890(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamData: GetFileNum Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (D_1a9778[pack]) {
        int n = f_095c04(pack);
        if (n >= 0)
            return n;
        f_093f90("StreamData: GetFileNum Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (!m0) {
        f_093f90("StreamData: GetFileNum Failed! Pack[%d] has not been Registered yet.\n", pack);
        return -1;
    }
    return f_114a4c(m0);
}

/* @draft 0x09590c us f_09590c
   WHAT IT DOES: Returns where a file of a pack starts, or -1.
   Remaining difference: retail loads the unregistered pack message's address before the
   header test (lui/addiu, beqz into the shared log call); here the call path comes first and
   the address is loaded in the log block. */
int CStreamData::f_09590c(int pack, int file)
{
    int r;
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamData: GetOffset Failed! Invalid PackID[%d]\n", pack);
        r = -1;
    } else if (D_1a9778[pack]) {
        r = 0;
    } else if (m0) {
        r = f_114a70(m0, file);
    } else {
        f_093f90("StreamData: GetOffset Failed! Pack[%d] has not been Registered yet.\n", pack);
        r = -1;
    }
    return r;
}

/* @implements 0x095974 us f_095974
   WHAT IT DOES: Builds a file's name (the pack's prefix, the file's name and ".nps"). Returns
   0, or -1 for a bad file. */
int CStreamData::f_095974(int pack, int file, char *out)
{
    char *name = f_095c14(pack, file);
    if (!name) {
        f_093f90("StreamData: GetFileName Failed! Invalid FileNo[%d]\n", file);
        return -1;
    }
    strcpy(out, D_1a977c[pack]);
    strcat(out, name);
    strcat(out, ".nps");
    return 0;
}

/* @implements 0x095a1c us f_095a1c
   WHAT IT DOES: Gives a pack its pre-load buffer. Returns the result, or -1. */
int CStreamData::f_095a1c(int pack, void *buf)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadSethBuff Failed! CStreamPreLoad is NULL \n");
        return -1;
    }
    return m4->f_095ce0(pack, buf);
}

/* @implements 0x095a58 us f_095a58
   WHAT IT DOES: Takes a pack's pre-load buffer away. Returns the result, or -1. */
int CStreamData::f_095a58(int pack)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadResethBuff Failed! CStreamPreLoad is NULL \n");
        return -1;
    }
    return m4->f_095d44(pack);
}

/* @implements 0x095a94 us f_095a94
   WHAT IT DOES: Whether a pack's pre-load header is registered. */
int CStreamData::f_095a94(int pack)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadIsHeaderRegistered Failed! CStreamPreLoad is NULL \n");
        return 0;
    }
    return m4->f_095de8(pack);
}

/* @implements 0x095ad4 us f_095ad4
   WHAT IT DOES: Registers a pack's pre-load header. Returns the result, or -1. */
int CStreamData::f_095ad4(int pack, void *header)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadSetHeader Failed! CStreamPreLoad is NULL \n");
        return -1;
    }
    return m4->f_095d8c(pack, header);
}

/* @implements 0x095b10 us f_095b10
   WHAT IT DOES: Returns a pack's pre-load unit size, or -1. */
int CStreamData::f_095b10(int pack)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadGetUnitSize Failed! CStreamPreLoad is NULL \n");
        return -1;
    }
    return m4->f_095e24(pack);
}

/* @implements 0x095b4c us f_095b4c
   WHAT IT DOES: Returns a pack's number of pre-loaded streams, or -1. */
int CStreamData::f_095b4c(int pack)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadGetStreamNum Failed! CStreamPreLoad is NULL \n");
        return -1;
    }
    return m4->f_095e70(pack);
}

/* @implements 0x095b88 us f_095b88
   WHAT IT DOES: Returns a pack's pre-load size, or -1. */
int CStreamData::f_095b88(int pack)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadGetPackSize Failed! CStreamPreLoad is NULL \n");
        return -1;
    }
    return m4->f_095ebc(pack);
}

/* @implements 0x095bc4 us f_095bc4
   WHAT IT DOES: Returns the address of a stream in a pack's pre-load buffer, or 0. */
int CStreamData::f_095bc4(int pack, int a)
{
    if (!m4) {
        f_093f90("StreamData: PreLoadSearchBuff Failed! CStreamPreLoad is NULL \n");
        return 0;
    }
    return m4->f_095f08(pack, a);
}

}

/* @implements 0x095c04 us f_095c04
   WHAT IT DOES: The number of files of a fixed pack: 30, or -1 for a bad pack. */
int f_095c04(int pack)
{
    return pack != 0 ? -1 : 30;
}

/* @implements 0x095c14 us f_095c14
   WHAT IT DOES: The name of a file of a fixed pack; there are no names (0). */
char *f_095c14(int pack, int file)
{
    return 0;
}
