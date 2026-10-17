/* A model package object file (retail 0x0fe990 to 0x0fea38). A loaded package holds a count
   of parts and a table of their offsets from the package's start; setting it up turns the
   offsets into pointers, sets up each part and the package, and writes the data cache back
   so the graphics hardware sees the result. */

extern "C" {
void sceKernelDcacheWritebackAll(void);
void f_0cbaa0(void *pack);
void f_0cbdc8(void *part);
void f_0cbfb0(void *part);
void f_0cbfc8(void);
}

/* A loaded package. */
struct Pack {
    short m0[3];
    unsigned short n;   /* parts */
    int part[1];        /* offsets from the package's start, then pointers */
};

/* @implements 0x0fe990 us f_0fe990
   WHAT IT DOES: Sets a loaded package up in place: relocates each part's offset to a
   pointer and sets the part up, then sets up the package and writes the data cache back.
   Returns the package. */
Pack *f_0fe990(Pack *p)
{
    for (int i = 0; i < p->n; i++) {
        p->part[i] += (int)p;
        f_0cbdc8((void *)p->part[i]);
    }
    f_0cbaa0(p);
    sceKernelDcacheWritebackAll();
    return p;
}

/* @implements 0x0fea0c us f_0fea0c
   WHAT IT DOES: Hands part i of a set up package to f_0cbfb0 (empty in retail), then calls
   f_0cbfc8. */
void f_0fea0c(Pack *p, int i)
{
    f_0cbfb0((void *)p->part[i]);
    f_0cbfc8();
}
