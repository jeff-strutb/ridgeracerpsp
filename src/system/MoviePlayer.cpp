/* The movie player object file (retail 0x08a71c to 0x08c3e4): plays a PMF movie through
   sceMpeg with a display, a read, a movie and (for movies with sound) a sound thread. One
   player exists at a time (D_242b90); the state globals tell the game whether a movie is
   starting, playing or finished. The object file ends with a small two-ended buffer
   allocator and the "movie" variable-length memory pool the decoder buffers come from. */

#include "psp/kernel.h"

extern "C" {
SceUID sceKernelCreateVpl(const char *name, int part, unsigned int attr, unsigned int size, void *opt);
int sceKernelDeleteVpl(SceUID uid);
int sceKernelAllocateVpl(SceUID uid, unsigned int size, void **data, unsigned int *timeout);
}

/* A buffer handed out from both ends: low allocations move cur up from start, high ones
   move top down from end. */
class CMovieArena {
public:
    void Init(int size, int base);
    void Free();
    int Get(int size, int high);
    int GetAligned(int align, int size);
    void Reset();

    int size;
    int base;
    int start;
    int end;
    int cur;
    int top;
};

/* The "movie" variable-length memory pool. */
class CMovieVpl {
public:
    CMovieVpl();
    ~CMovieVpl();
    void *Alloc(int size);
    void *AllocAligned(int align, int size);

    SceUID id;
};

/* @implements 0x08c1c0 us _ZN11CMovieArena4InitEii
   WHAT IT DOES: Sets the buffer to size bytes at base and empties it. */
void CMovieArena::Init(int n, int b)
{
    base = b;
    size = n;
    start = b;
    end = b + n;
    cur = b;
    top = b + n;
}

/* @implements 0x08c1e0 us _ZN11CMovieArena4FreeEv
   WHAT IT DOES: Forgets the buffer. */
void CMovieArena::Free()
{
    base = 0;
    top = 0;
    cur = 0;
}

/* @implements 0x08c1f0 us _ZN11CMovieArena3GetEii
   WHAT IT DOES: Takes n bytes from the high end (high != 0) or the low end; returns their
   address. */
int CMovieArena::Get(int n, int high)
{
    int r;
    if (high) {
        top = top - n;
        r = top;
    } else {
        r = cur;
        cur = r + n;
    }
    return r;
}

/* @implements 0x08c21c us _ZN11CMovieArena10GetAlignedEii
   WHAT IT DOES: Takes n bytes from the low end at the next multiple of align. */
int CMovieArena::GetAligned(int align, int n)
{
    int mask = align > 0 ? align - 1 : 0;
    int r = cur;
    r = (r + mask) & ~mask;
    cur = r + n;
    return r;
}

/* @implements 0x08c250 us _ZN11CMovieArena5ResetEv
   WHAT IT DOES: Empties the buffer. */
void CMovieArena::Reset()
{
    cur = start;
    top = end;
}

/* @implements 0x08c264 us _ZN9CMovieVplC2Ev
   WHAT IT DOES: Creates the 256 KB "movie" pool in user partition 2. */
/* @implements 0x08c2a4 us _ZN9CMovieVplC1Ev
   WHAT IT DOES: The same constructor (complete object version). */
CMovieVpl::CMovieVpl()
{
    id = sceKernelCreateVpl("movie", 2, 0, 0x40000, 0);
}

/* @implements 0x08c2e4 us _ZN9CMovieVplD2Ev
   WHAT IT DOES: Deletes the pool if it was created. */
/* @implements 0x08c30c us _ZN9CMovieVplD1Ev
   WHAT IT DOES: The same destructor (complete object version). */
CMovieVpl::~CMovieVpl()
{
    if (id > 0)
        sceKernelDeleteVpl(id);
}

/* @implements 0x08c334 us _ZN9CMovieVpl5AllocEi
   WHAT IT DOES: Allocates size bytes from the pool without waiting; 0 when that fails. */
void *CMovieVpl::Alloc(int n)
{
    void *p;
    if (id <= 0)
        return 0;
    if (sceKernelAllocateVpl(id, n, &p, 0) != 0)
        return 0;
    return p;
}

/* @implements 0x08c378 us _ZN9CMovieVpl12AllocAlignedEii
   WHAT IT DOES: Allocates size bytes plus align from the pool and returns the first multiple
   of align inside; 0 when the allocation fails. */
void *CMovieVpl::AllocAligned(int align, int n)
{
    void *p;
    int mask = align > 0 ? align - 1 : 0;
    if (id > 0) {
        if (sceKernelAllocateVpl(id, n + align, &p, 0) != 0)
            return 0;
    }
    return (void *)(((int)p + mask) & ~mask);
}
