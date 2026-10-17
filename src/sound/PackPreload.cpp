/* The preload pack reader, nuCPackPreload (retail 0x114bec to 0x114d34): reads the header of
   a pack of preloaded sound streams (a count, a unit size and the stream ids), reporting a
   missing header or a bad id through the debug print (0x1157c8). */

extern "C" void f_1157c8(const char *fmt, ...);

struct PreloadHeader {
    int m0;
    int count;
    int unitSize;
    int m12;
    int ids[1];
};

class CPackPreload {
public:
    CPackPreload();
    int f_114bfc(PreloadHeader *h);
    int f_114c30(PreloadHeader *h);
    int f_114c64(PreloadHeader *h);
    int f_114ca4(PreloadHeader *h, int id);
};

/* @implements 0x114bec us _ZN12CPackPreloadC2Ev
   WHAT IT DOES: Constructs the reader (it has no state). */
/* @implements 0x114bf4 us _ZN12CPackPreloadC1Ev
   WHAT IT DOES: The complete-object form of the same constructor. */
CPackPreload::CPackPreload()
{
}

/* @implements 0x114bfc us f_114bfc
   WHAT IT DOES: Returns the pack's unit size, or -1 without a header. */
int CPackPreload::f_114bfc(PreloadHeader *h)
{
    if (h == 0) {
        f_1157c8("nuSound Error: nuCPackPreload: GetUnitSize Failed! Header Addr is NULL\n");
        return -1;
    }
    return h->unitSize;
}

/* @implements 0x114c30 us f_114c30
   WHAT IT DOES: Returns the pack's stream count, or -1 without a header. */
int CPackPreload::f_114c30(PreloadHeader *h)
{
    if (h == 0) {
        f_1157c8("nuSound Error: nuCPackPreload: GetStreamNum Failed! Header Addr is NULL\n");
        return -1;
    }
    return h->count;
}

/* @implements 0x114c64 us f_114c64
   WHAT IT DOES: Returns the pack's size (unit size times count), or -1 without a header. */
int CPackPreload::f_114c64(PreloadHeader *h)
{
    if (h == 0) {
        f_1157c8("nuSound Error: nuCPackPreload: GetPackSize Failed! Header Addr is NULL\n");
        return -1;
    }
    return h->unitSize * h->count;
}

/* @implements 0x114ca4 us f_114ca4
   WHAT IT DOES: Returns stream id's offset in the pack (its index times the unit size), or
   -1 without a header, for a negative id or an id not in the pack. */
int CPackPreload::f_114ca4(PreloadHeader *h, int id)
{
    int i;

    if (h == 0) {
        f_1157c8("nuSound Error: nuCPackPreload: GetOffset Failed! Header Addr is NULL\n");
        return -1;
    }
    if (id < 0) {
        f_1157c8("nuSound Error: nuCPackPreload: GetOffset Failed! Invalid FileNo:%d\n", id);
        return -1;
    }
    for (i = 0; i < h->count; i++)
        if (id == h->ids[i])
            return h->unitSize * i;
    return -1;
}
