/* The heap statistics object file (retail 0x09923c to 0x0992fc): the main loop's heap
   monitor reads newlib's mallinfo and estimates the heap's top from a probe allocation. */

#include <malloc.h>
#include <stdlib.h>

struct CMemoryStats {
    void f_0992ac();
    void f_09923c();

    int top;
    struct mallinfo info;
};

/* @implements 0x09923c us f_09923c
   WHAT IT DOES: Reads the heap statistics (mallinfo) into the monitor. */
void CMemoryStats::f_09923c()
{
    info = mallinfo();
}

/* @implements 0x0992ac us f_0992ac
   WHAT IT DOES: Reads the heap statistics, then estimates the heap's start: the address of
   a freshly allocated (and freed) byte less the arena size in use. */
void CMemoryStats::f_0992ac()
{
    f_09923c();
    top = (int)malloc(1);
    free((void *)top);
    top = top - (info.arena - info.keepcost);
}
