/* The pack file object files (retail 0x0299b0 to 0x029b58): a reader for a block of data files
   packed into one buffer. The pack starts with a header (the entry count, a value kept as is,
   and the offset of the name table), followed at +16 by one record per entry holding its
   offset from the start of the pack and its size. The name table holds the entry names as
   consecutive zero terminated strings, in entry order. */

#include <string.h>

struct PackEntry {
    int offset;
    int size;
};

struct PackHeader {
    int count;
    int m4;
    int names;
    int m12;
    PackEntry entries[1];
};

class PackFile {
public:
    PackFile();
    PackFile(void *data);
    void f_0299f8(void *data);
    void f_029a18();
    int f_029a44();
    int f_029a4c(int i);
    void *f_029a60(int i);
    void *f_029a7c(const char *name);
    const char *f_029b20(int i);

    char *m0;
    const char *m4;
    PackEntry *m8;
    int m12;
    int m16;
};

/* @implements 0x0299b0 us _ZN8PackFileC2Ev
   WHAT IT DOES: Makes an empty reader with no pack attached (base object constructor). */
/* @implements 0x0299b8 us _ZN8PackFileC1Ev
   WHAT IT DOES: Makes an empty reader with no pack attached (complete object constructor). */
PackFile::PackFile()
{
    m0 = 0;
}

/* @implements 0x0299c0 us _ZN8PackFileC2EPv
   WHAT IT DOES: Makes a reader over the given pack (base object constructor). */
/* @implements 0x0299dc us _ZN8PackFileC1EPv
   WHAT IT DOES: Makes a reader over the given pack (complete object constructor). */
PackFile::PackFile(void *data)
{
    f_0299f8(data);
}

/* @implements 0x0299f8 us f_0299f8
   WHAT IT DOES: Attaches the reader to a pack in memory and reads its header. */
void PackFile::f_0299f8(void *data)
{
    m0 = (char *)data;
    f_029a18();
}

/* @implements 0x029a18 us f_029a18
   WHAT IT DOES: Reads the pack header: where the entry records and the name table are, and
   how many entries there are. */
void PackFile::f_029a18()
{
    PackHeader *h = (PackHeader *)m0;
    m8 = h->entries;
    m12 = h->count;
    m16 = h->m4;
    m4 = m0 + h->names;
}

/* @implements 0x029a44 us f_029a44
   WHAT IT DOES: Returns the number of entries. */
int PackFile::f_029a44()
{
    return m12;
}

/* @implements 0x029a4c us f_029a4c
   WHAT IT DOES: Returns the size of entry i. */
int PackFile::f_029a4c(int i)
{
    return m8[i].size;
}

/* @implements 0x029a60 us f_029a60
   WHAT IT DOES: Returns the address of entry i's data. */
void *PackFile::f_029a60(int i)
{
    return m0 + m8[i].offset;
}

/* @implements 0x029a7c us f_029a7c
   WHAT IT DOES: Looks an entry up by name and returns its data, or 0 if no entry has that
   name. */
void *PackFile::f_029a7c(const char *name)
{
    const char *s = m4;
    int i;

    for (i = 0; i < m12; i++) {
        if (strcmp(s, name) == 0)
            return f_029a60(i);
        while (*s)
            s++;
        s++;
    }
    return 0;
}

/* @implements 0x029b20 us f_029b20
   WHAT IT DOES: Returns the name of entry i. */
const char *PackFile::f_029b20(int i)
{
    const char *s = m4;
    int j;

    for (j = 0; j < i; j++) {
        while (*s)
            s++;
        s++;
    }
    return s;
}
