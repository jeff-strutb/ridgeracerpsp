/* The sound pack file reader, nuCPackFile (retail 0x115800 to 0x1158d8): three getters on a
   pack's data header. Each one returns a field of the header or an entry of its offset table,
   and reports a null header or a bad file number (passed to the format) through the debug print (0x1157c8) and
   returns -1. A file's offset comes back shifted left by 11 bits. */

extern "C" void f_1157c8(const char *fmt, ...);

/* The pack data header: the file count at +4, the unit size at +12 and the offset table
   from +16. */
struct PackDataHeader {
    int m0;
    int count;
    int m8;
    int unitSize;
    int offsets[1];
};

class CNuCPackFile {
public:
    int f_115800(PackDataHeader *h);
    int f_115834(PackDataHeader *h, int fileNo);
    int f_1158a4(PackDataHeader *h);
};

/* @implements 0x115800 us f_115800
   WHAT IT DOES: Returns the pack's file count, or -1 with an error print for a null header. */
int CNuCPackFile::f_115800(PackDataHeader *h)
{
    if (h == 0) {
        f_1157c8("nuCPackFile: Error: GetFileNum Failed! Data Addr is NULL\n");
        return -1;
    }
    return h->count;
}

/* @implements 0x115834 us f_115834
   WHAT IT DOES: Returns a file's offset in bytes (its table entry shifted left by 11), or -1
   with an error print for a null header or a file number outside 0 to the count. */
int CNuCPackFile::f_115834(PackDataHeader *h, int fileNo)
{
    if (h == 0) {
        f_1157c8("nuCPackFile: Error: GetOffset Failed! Data Addr is NULL\n");
        return -1;
    }
    if (fileNo < 0 || fileNo >= h->count) {
        f_1157c8("nuCPackFile: Error: GetOffset Failed!Invalid FileNo[%d]\n", fileNo);
        return -1;
    }
    /* The byte offset written as a shift puts the header first in the add, as retail. */
    return *(int *)((char *)h + (fileNo << 2) + 16) << 11;
}

/* @implements 0x1158a4 us f_1158a4
   WHAT IT DOES: Returns the pack's unit size, or -1 with an error print for a null header. */
int CNuCPackFile::f_1158a4(PackDataHeader *h)
{
    if (h == 0) {
        f_1157c8("nuCPackFile: Error: GetUnitSize Failed! Data Addr is NULL\n");
        return -1;
    }
    return h->unitSize;
}
