/* The file loading object file (retail 0x001570 to 0x002fe8): the asynchronous disc reader,
   the table of packages and files inside RRP.DAT, the loaders that place a package or a single
   file in memory, the queue of compressed blocks waiting to be unpacked, and System::CLoadJob,
   the job that services all of it once per frame. */

#include <stdlib.h>
#include <string.h>

extern "C" {
int sceIoReadAsync(int fd, void *buf, int size);
int sceIoLseekAsync(int fd, long long offset, int whence);
void sceKernelDcacheWritebackAll(void);
int sceKernelCheckCallback(void);
int sceKernelDelayThread(int usec);
unsigned int sceKernelGetSystemTimeLow(void);

int f_027850(const char *name, int flags, int mode);
int f_02793c(int fd);
int f_027958(int fd, void *buf, int size);
int f_02799c(int fd);
int f_027bac(int fd, int wait, long long *res);
void f_087f34(void *);
}

/* A mark in a two ended heap: which end, and how far it had grown. */
struct Mark {
    int side;
    int pos;
};

extern "C" {
Mark f_0996b0(void *heap, int side);
void *f_099684(void *heap, int size, int fromTop);
void f_0996dc(void *heap, Mark m);
}

typedef int (*IoDone)(int fd, int result, int arg);

/* One package of RRP.DAT (36 bytes). */
struct Package {
    const char *name;
    int sector;
    short sectors;
    short first;
    short last;
    short packed;
    int packedSize;
    int size;
    int extra;
    int bufSize;
    char wanted;
};

/* One file inside a package (24 bytes). */
struct File {
    const char *name;
    int sector;
    short sectors;
    short pad;
    int size;
    int offset;
    char wanted;
};

/* One entry of the list of what to load (8 bytes). */
struct Wanted {
    const char *file;
    const char *package;
};

/* A read request for the load job (48 bytes). */
struct Request {
    int type;
    void *owner;
    void *buf;
    const char *name;
    int file;
    int size;
    int sector;
    int sectors;
    short first;
    short last;
    int packedSize;
    unsigned char *packed;
    unsigned char *dest;
};

/* A compressed block being unpacked (16 bytes). */
struct Unpack {
    unsigned char *end;
    unsigned char *src;
    unsigned char *base;
    unsigned char *dst;
};

/* The queue of blocks waiting to be unpacked. */
struct UnpackQueue {
    Unpack work[32];
    Request req[32];
    int head;
    int tail;
    unsigned char timed;
    UnpackQueue() { head = 0; tail = 0; timed = 0; }
    bool Empty() { return tail == head; }
};

/* A package placed in memory. */
struct PackageLoader {
    int package;
    void *raw;
    unsigned char *buf;
    void *files[64];
    void *heap;
    Mark mark;
};

/* A single file placed in memory. */
struct FileLoader {
    int file;
    void *raw;
    unsigned char *buf;
    void *data;
    void *heap;
    Mark mark;
};

namespace Ng {
class CJob {
public:
    virtual void Begin() = 0;
    virtual int Step() = 0;
    virtual void End() = 0;
};
}

/* The load job's queue of reads. */
struct RequestRing {
    Request e[256];
    int head;
    int tail;
    RequestRing() { head = 0; tail = 0; }
    bool Empty() { return tail == head; }
    Request &Front() { return e[head]; }
    void Pop()
    {
        if (tail != head)
            head = (head + 1) & 0xff;
    }
    void Push(Request r)
    {
        e[tail++] = r;
        tail = (unsigned char)tail;
    }
};

namespace System {
class CLoadJob : public Ng::CJob {
public:
    CLoadJob() { busy = 0; }
    virtual void Begin();
    virtual int Step();
    virtual void End();
    void Push(Request r) { ring.Push(r); }
    void Add(const Request &r) { ring.Push(r); }
    Request cur;
    RequestRing ring;
    unsigned char busy;
};
}

/* The decoder of the packed format; it keeps no state of its own. */
struct Lz {
    void f_002fe8(unsigned char **dst, unsigned char **src);
};

/* @implements 0x002edc us f_002edc
   WHAT IT DOES: Unpacks a compressed block, 100 steps at a time, until it is done or the time
   budget (in microseconds) runs out. Returns whether the block is finished. */
static inline unsigned int Now()
{
    volatile unsigned int t = sceKernelGetSystemTimeLow();
    return t;
}
static inline int f_002edc(Unpack *u, int budget)
{
    Lz lz;
    unsigned int start;
    int n;

    if (budget == 0x7fffffff) {
        while (u->src < u->end)
            lz.f_002fe8(&u->dst, &u->src);
    } else {
        start = Now();
        while ((int)(Now() - start) <= budget) {
            for (n = 0; n < 100; n++) {
                if (!(u->src < u->end))
                    goto done;
                lz.f_002fe8(&u->dst, &u->src);
            }
        }
    }
done:
    return u->src == u->end;
}


extern "C" {
int f_001088(void *job);
void f_002a74(PackageLoader *l, int file);
void f_002de4(FileLoader *l);
}

extern void *D_1d88a0;
extern char D_241810[];

extern IoDone D_1d9c30;
extern int D_1d9c34;
extern int D_1d9c38;
extern int D_1d9c3c;
extern unsigned char D_1d9c40;
extern int D_1d9c44;
extern int D_1d9c48;
extern void *D_1d9c4c;
extern int D_1d9c50;
extern int D_1d9c54;
extern int D_1d9c58;

extern int D_1b8c00;
extern Package D_1b8c04[];
extern File D_1c0614[];
extern int D_1d106c;
extern int D_1d1070;
extern int D_1dd4ac;
extern Wanted D_1dd4b0[64];

UnpackQueue D_1d9c5c;
System::CLoadJob D_1da468;

extern "C" {

/* @implements 0x001570 us f_001570
   WHAT IT DOES: Starts an asynchronous read of the open file, remembering the function to call
   when it completes and its argument, and counts the bytes asked for. */
int f_001570(int fd, void *buf, int size, IoDone done, int arg)
{
    D_1d9c38 += size;
    D_1d9c30 = done;
    D_1d9c34 = arg;
    sceIoReadAsync(fd, buf, size);
    return 0;
}

/* @implements 0x0015ac us f_0015ac
   WHAT IT DOES: Starts an asynchronous seek in the open file, remembering the function to call
   when it completes and its argument. */
int f_0015ac(int fd, int offset, int whence, IoDone done, int arg)
{
    D_1d9c30 = done;
    D_1d9c34 = arg;
    sceIoLseekAsync(fd, offset, whence);
    return 0;
}

/* @implements 0x0015f8 us f_0015f8
   WHAT IT DOES: Reads a whole file into a newly allocated buffer and returns it, storing its
   size if asked; when the file cannot be opened it returns nothing and a size of 0. */
void *f_0015f8(const char *name, int *sizeOut)
{
    int fd, size;
    void *buf;

    fd = f_027850(name, 0, 2);
    if (fd < 0) {
        *sizeOut = 0;
        return 0;
    }
    size = f_02799c(fd);
    buf = malloc(size);
    f_027958(fd, buf, size);
    f_02793c(fd);
    sceKernelDcacheWritebackAll();
    if (sizeOut)
        *sizeOut = size;
    return buf;
}

/* @implements 0x001698 us f_001698
   WHAT IT DOES: Polls the asynchronous read or seek in progress. When it has finished it calls
   the completion function with the bytes transferred (0 on an error). Returns 0 when nothing is
   in progress, 1 otherwise. */
int f_001698(void)
{
    long long res;
    int r;

    if (D_1d9c44 == 0 && D_1d9c40 == 0)
        return 0;
    r = f_027bac(D_1d9c3c, 1, &res);
    if (r == 0) {
        if (D_1d9c30)
            D_1d9c30(D_1d9c3c, (int)res, D_1d9c34);
    } else if (r < 0) {
        if (D_1d9c30)
            D_1d9c30(D_1d9c3c, 0, D_1d9c34);
    }
    return 1;
}

/* @implements 0x001744 us f_001744
   WHAT IT DOES: Completion of a plain file read: closes the file, makes the data visible to
   the hardware and marks the reader idle. */
int f_001744(int unused, int result, int fd)
{
    D_1d9c30 = 0;
    f_02793c(fd);
    sceKernelDcacheWritebackAll();
    D_1d9c40 = 0;
    return 0;
}

/* @implements 0x00177c us f_00177c
   WHAT IT DOES: Returns the size of a file; stops the game if it cannot be opened. */
int f_00177c(const char *name)
{
    int fd, size;

    fd = f_027850(name, 0, 2);
    if (fd < 0)
        for (;;)
            ;
    size = f_02799c(fd);
    f_02793c(fd);
    return size;
}

/* @implements 0x0017d4 us f_0017d4
   WHAT IT DOES: Opens a file and starts reading it into the buffer in the background; the file
   is closed when the read completes. Stops the game if the file cannot be opened. */
void f_0017d4(void *buf, const char *name, int size)
{
    int fd;

    fd = f_027850(name, 0, 2);
    if (fd < 0)
        for (;;)
            ;
    D_1d9c40 = 1;
    D_1d9c3c = fd;
    D_1d9c44 = 0;
    D_1d9c48 = f_001570(fd, buf, size, f_001744, fd);
}

/* @implements 0x001860 us f_001860
   WHAT IT DOES: Reads a whole file into a newly allocated buffer through the asynchronous
   reader, waiting for it, and returns the buffer (and its size if asked). */
void *f_001860(const char *name, int *sizeOut)
{
    int size;
    void *buf;

    size = f_00177c(name);
    buf = malloc(size);
    f_0017d4(buf, name, size);
    while (f_001698())
        ;
    if (sizeOut)
        *sizeOut = size;
    return buf;
}

/* @implements 0x0018dc us f_0018dc
   WHAT IT DOES: Completion of a read from RRP.DAT: if fewer bytes arrived than asked for it
   reads again, otherwise the reader is idle and the data is made visible to the hardware. */
int f_0018dc(int fd, int result, int arg)
{
    D_1d9c30 = 0;
    if (result == D_1d9c50) {
        D_1d9c44 = 0;
        D_1d9c58 = 0;
        sceKernelDcacheWritebackAll();
    } else {
        D_1d9c58 = 1;
        D_1d9c48 = f_001570(D_1d9c3c, D_1d9c4c, D_1d9c50, f_0018dc, 0);
    }
    return 0;
}

/* @implements 0x00195c us f_00195c
   WHAT IT DOES: Completion of a seek in RRP.DAT: if it did not reach the wanted position it
   seeks again, otherwise it starts reading the wanted bytes. */
int f_00195c(int fd, int result, int arg)
{
    D_1d9c30 = 0;
    if (result == D_1d9c54) {
        D_1d9c58 = 0;
        D_1d9c48 = f_001570(D_1d9c3c, D_1d9c4c, D_1d9c50, f_0018dc, 0);
    } else {
        D_1d9c58 = 1;
        D_1d9c48 = f_0015ac(D_1d9c3c, D_1d9c54, 0, f_00195c, 0);
    }
    return 0;
}

/* @implements 0x0019f4 us f_0019f4
   WHAT IT DOES: Starts reading a run of 2048 byte sectors of RRP.DAT into the buffer in the
   background: a seek, then the read. */
void f_0019f4(void *buf, int sector, int sectors)
{
    D_1d9c4c = buf;
    D_1d9c50 = sectors << 11;
    D_1d9c54 = sector << 11;
    D_1d9c44 = 1;
    D_1d9c48 = f_0015ac(D_1d9c3c, sector << 11, 0, f_00195c, 0);
}

/* @implements 0x001a60 us f_001a60
   WHAT IT DOES: Adds a compressed block that has just been read to the unpack queue: where the
   packed bytes start and end and where the unpacked data goes. */
void f_001a60(UnpackQueue *q, Request r)
{
    q->req[q->tail] = r;
    int t = q->tail;
    unsigned char *p = q->req[t].packed;
    int n = q->req[t].packedSize;
    unsigned char *d = q->req[t].dest;
    Unpack *u = &q->work[t];
    u->end = p + n;
    u->src = p;
    u->base = d;
    u->dst = d;
    q->tail = (t + 1) & 31;
}

/* @implements 0x001b3c us f_001b3c
   WHAT IT DOES: Unpacks the block at the head of the queue for whatever time is left in this
   frame (or without limit when the queue is not timed). When the block is done it records where
   each file of its package now lies and moves to the next block. */
void f_001b3c(UnpackQueue *q)
{
    int budget;
    Request *r;
    int i;

    if (!q->Empty()) {
        budget = 15800 - f_001088(D_1d88a0);
        if (budget < 0)
            budget = 15800;
        if (q->timed == 0)
            budget = 0x7fffffff;
        if (f_002edc(&q->work[q->head], budget)) {
            r = &q->req[q->head];
            for (i = r->first; i < r->last; i++)
                f_002a74((PackageLoader *)r->owner, i);
            q->head = (q->head + 1) & 31;
        }
    }
}

}

/* @implements 0x001c1c us CLoadJob5Begin
   WHAT IT DOES: Starts the load job with nothing in progress. */
void System::CLoadJob::Begin()
{
    busy = 0;
}

/* @draft 0x001c24 us CLoadJob4Step
   WHAT IT DOES: Runs once per frame. It services system callbacks and the unpack queue; when a
   read has finished it records the result (a single file is ready, a package's files are
   placed, or a compressed package is queued for unpacking) and then starts the next queued
   read, from RRP.DAT or from a loose file. Never reports itself finished. */
int System::CLoadJob::Step()
{
    Request *r;

    sceKernelCheckCallback();
    f_001b3c(&D_1d9c5c);
    if (busy == 1) {
        if (f_001698())
            return 0;
        busy = 0;
        ring.Pop();
        if (cur.type == 1) {
            f_002de4((FileLoader *)cur.owner);
        } else if (cur.type == 2) {
            if (D_1b8c00 == 2) {
                if (cur.packedSize) {
                    f_001a60(&D_1d9c5c, cur);
                } else {
                    int i;
                    for (i = cur.first; i < cur.last; i++)
                        f_002a74((PackageLoader *)cur.owner, i);
                }
            } else {
                f_002a74((PackageLoader *)cur.owner, cur.file);
            }
        }
    }
    r = &cur;
    if (!ring.Empty()) {
        busy = 1;
        *r = ring.Front();
        if (D_1b8c00 == 2)
            f_0019f4(cur.buf, cur.sector, cur.sectors);
        else
            f_0017d4(cur.buf, cur.name, cur.size);
    }
    return 0;
}

/* @implements 0x001e2c us CLoadJob3End
   WHAT IT DOES: Nothing to do when the load job stops. */
void System::CLoadJob::End()
{
}

extern "C" {

/* @implements 0x001e34 us f_001e34
   WHAT IT DOES: Waits until every queued read and every queued unpack has finished, stepping
   the load job by hand and keeping the pad alive meanwhile. */
void f_001e34(System::CLoadJob *job)
{
    while (job->busy || !job->ring.Empty() || !D_1d9c5c.Empty()) {
        job->Step();
        f_087f34(D_241810);
        sceKernelDelayThread(100);
    }
}

/* @implements 0x001ecc us f_001ecc
   WHAT IT DOES: Allocates a buffer the size of a loose file and queues a read of the file into
   it; returns the buffer, and its size if asked. */
void *f_001ecc(const char *name, int *sizeOut)
{
    int size;
    void *buf;

    size = f_00177c(name);
    buf = malloc(size);
    Request r = { 0, 0, buf, name, 0, size };
    D_1da468.Add(r);
    if (sizeOut)
        *sizeOut = size;
    return buf;
}

/* @implements 0x001ff4 us f_001ff4
   WHAT IT DOES: Switches loading to the RRP.DAT archive: opens it (stopping the game if it is
   missing), makes it the reader's file and clears every load request. */
void f_001ff4(void)
{
    void f_002304(void);

    D_1b8c00 = 2;
    D_1dd4ac = f_027850("RRP.DAT", 0, 2);
    if (D_1dd4ac < 0)
        for (;;)
            ;
    D_1d9c3c = D_1dd4ac;
    f_002304();
}

/* @implements 0x00204c us f_00204c
   WHAT IT DOES: Closes the RRP.DAT archive if loading uses it. */
void f_00204c(void)
{
    if (D_1b8c00 == 2)
        f_02793c(D_1dd4ac);
}

/* @implements 0x002084 us f_002084
   WHAT IT DOES: Finds a package by name; -1 if there is none. */
int f_002084(const char *name)
{
    int i;

    for (i = 0; i < D_1d106c; i++)
        if (strcmp(D_1b8c04[i].name, name) == 0)
            return i;
    return -1;
}

/* @implements 0x002108 us f_002108
   WHAT IT DOES: Returns the memory a package needs. From RRP.DAT that is its sectors, or for a
   compressed package the larger of its sectors and its unpacked size plus the packed data,
   with room for alignment; the result is remembered. */
int f_002108(int i)
{
    if (D_1b8c00 == 2) {
        if (D_1b8c04[i].packed == 0) {
            D_1b8c04[i].bufSize = D_1b8c04[i].sectors << 11;
        } else {
            int a = D_1b8c04[i].size + D_1b8c04[i].extra;
            if (a < D_1b8c04[i].sectors << 11)
                a = D_1b8c04[i].sectors << 11;
            D_1b8c04[i].bufSize = a + 127;
        }
    }
    return D_1b8c04[i].bufSize;
}

/* @implements 0x002184 us f_002184
   WHAT IT DOES: Finds a file by name among the files of one package; -1 if it is not there. */
int f_002184(const char *name, int package)
{
    int i;
    int last = D_1b8c04[package].last;

    for (i = D_1b8c04[package].first; i < last; i++)
        if (strcmp(D_1c0614[i].name, name) == 0)
            return i;
    return -1;
}

/* @implements 0x00222c us f_00222c
   WHAT IT DOES: Finds a file by its name and its package's name. */
int f_00222c(const char *name, const char *package)
{
    return f_002184(name, f_002084(package));
}

/* @implements 0x002260 us f_002260
   WHAT IT DOES: Finds a file by name among all files; -1 if there is none. */
int f_002260(const char *name)
{
    int i;

    for (i = 0; i < D_1d1070; i++)
        if (strcmp(D_1c0614[i].name, name) == 0)
            return i;
    return -1;
}

/* @implements 0x0022e4 us f_0022e4
   WHAT IT DOES: Returns the size of a file. */
int f_0022e4(int i)
{
    return D_1c0614[i].size;
}

/* @implements 0x002304 us f_002304
   WHAT IT DOES: Clears every package and file wanted mark and the list of what to load. */
void f_002304(void)
{
    int i;

    for (i = 0; i < D_1d106c; i++)
        D_1b8c04[i].wanted = 0;
    for (i = 0; i < D_1d1070; i++)
        D_1c0614[i].wanted = 0;
    for (i = 0; i < 64; i++) {
        D_1dd4b0[i].file = 0;
        D_1dd4b0[i].package = 0;
    }
}

/* @implements 0x002380 us f_002380
   WHAT IT DOES: Marks one file of a package as wanted. */
void f_002380(const char *name, const char *package)
{
    D_1c0614[f_002184(name, f_002084(package))].wanted = 1;
}

/* @implements 0x0023d4 us f_0023d4
   WHAT IT DOES: Marks a whole package as wanted. */
void f_0023d4(const char *package)
{
    D_1b8c04[f_002084(package)].wanted = 1;
}

/* @implements 0x002410 us f_002410
   WHAT IT DOES: Builds the list of what to load from the wanted marks: a whole package when it
   is wanted or every one of its files is, otherwise each wanted file on its own. */
void f_002410(void)
{
    int n = 0;
    int i, j;

    for (i = 0; i < D_1d106c; i++) {
        if (!D_1b8c04[i].wanted) {
            int first = D_1b8c04[i].first, last = D_1b8c04[i].last;
            if (first == last)
                continue;
            for (j = first; j < last; j++)
                if (!D_1c0614[j].wanted)
                    break;
            if (j < last) {
                for (j = first; j < last; j++) {
                    if (D_1c0614[j].wanted == 1) {
                        D_1dd4b0[n].file = D_1c0614[j].name;
                        D_1dd4b0[n].package = D_1b8c04[i].name;
                        n++;
                    }
                }
                continue;
            }
        }
        D_1dd4b0[n].package = D_1b8c04[i].name;
        D_1dd4b0[n].file = 0;
        n++;
    }
}

/* @implements 0x002550 us f_002550
   WHAT IT DOES: Returns one entry of the list of what to load. */
void f_002550(int i, const char **file, const char **package)
{
    *file = D_1dd4b0[i].file;
    *package = D_1dd4b0[i].package;
}

/* @implements 0x002574 us f_002574
   WHAT IT DOES: Adds up the memory every entry of the list of what to load needs, with room
   for each to be aligned. */
int f_002574(void)
{
    int total = 0;
    int i;
    const char *file, *package;

    for (i = 0; i < 64; i++) {
        f_002550(i, &file, &package);
        if (package) {
            if (file == 0)
                total += f_002108(f_002084(package)) + 127;
            else
                total += f_0022e4(f_00222c(file, package)) + 127;
        }
    }
    return total;
}

/* @implements 0x00260c us f_00260c
   WHAT IT DOES: Prepares to load a package: finds it and allocates its buffer, from the given
   heap or with malloc, aligned to 128 bytes; no file of it is placed yet. */
void f_00260c(PackageLoader *l, const char *name, void *heap, int fromTop)
{
    int size;
    int i;

    l->heap = heap;
    l->package = f_002084(name);
    size = f_002108(l->package);
    if (l->heap) {
        Mark m = f_0996b0(l->heap, 0);
        l->mark = m;
        l->raw = f_099684(l->heap, size + 127, fromTop);
    } else {
        l->raw = malloc(size + 127);
    }
    l->buf = (unsigned char *)(((int)l->raw + 127) & -128);
    for (i = 0; i < 64; i++)
        l->files[i] = 0;
}

/* @implements 0x0026cc us f_0026cc
   WHAT IT DOES: Releases a package's buffer, back to its heap or with free. */
void f_0026cc(PackageLoader *l)
{
    if (l->package == -1)
        return;
    l->package = -1;
    if (l->heap)
        f_0996dc(l->heap, l->mark);
    else
        free(l->raw);
    l->raw = 0;
}

/* @draft 0x002734 us f_002734
   WHAT IT DOES: Queues the read of a package from RRP.DAT unless all its files are already
   placed. A compressed package is read to the end of its buffer, to be unpacked to the start.
   Unless asked not to, it waits for the loading to finish. */
void f_002734(PackageLoader *l, unsigned char nowait)
{
    int n = -(D_1b8c04[l->package].first - D_1b8c04[l->package].last);
    int i;

    for (i = 0; i < n; i++)
        if (l->files[i] == 0)
            break;
    if (i >= n)
        return;
    if (D_1b8c00 == 2) {
        Package *p = &D_1b8c04[l->package];
        if (p->packed == 0) {
            Request r = { D_1b8c00, l, l->buf, 0, 0, 0, p->sector, p->sectors, p->first, p->last };
            D_1da468.Add(r);
        } else {
            unsigned char *at = (unsigned char *)(((int)(l->buf + p->size + p->extra - (p->sectors << 11)) + 127) & -128);
            Request r = { D_1b8c00, l, at, 0, 0, 0, p->sector, p->sectors, p->first, p->last,
                          p->packedSize, at + (p->sectors << 11) - p->packedSize, l->buf };
            D_1da468.Add(r);
        }
    }
    if (!nowait)
        f_001e34(&D_1da468);
}

/* @implements 0x002a74 us f_002a74
   WHAT IT DOES: Records where one file of a loaded package lies in its buffer. */
void f_002a74(PackageLoader *l, int file)
{
    int off = D_1c0614[file].offset;
    l->files[file - D_1b8c04[l->package].first] = l->buf + off;
}

/* @implements 0x002acc us f_002acc
   WHAT IT DOES: Returns where a file of a loaded package lies; 0 if it is not in the
   package. */
void *f_002acc(PackageLoader *l, const char *name)
{
    int i = f_002184(name, l->package);

    if (i < 0)
        return 0;
    return l->files[i - D_1b8c04[l->package].first];
}

/* 0x002b34 f_002b34 (byte-exact; its tag lives in the control set, src/control/batch5.c)
   WHAT IT DOES: Prepares to load a single file: finds it and allocates its buffer, from the
   given heap or with malloc, aligned to 128 bytes. */
void f_002b34(FileLoader *l, const char *name, int unused, void *heap, int fromTop)
{
    int size;

    l->heap = heap;
    l->data = 0;
    l->file = f_002260(name);
    size = f_0022e4(l->file);
    if (l->heap) {
        Mark m = f_0996b0(l->heap, 0);
        l->mark = m;
        l->raw = f_099684(l->heap, size + 127, fromTop);
    } else {
        l->raw = malloc(size + 127);
    }
    l->buf = (unsigned char *)(((int)l->raw + 127) & -128);
}

/* @implements 0x002be8 us f_002be8
   WHAT IT DOES: Releases a single file's buffer, back to its heap or with free. */
void f_002be8(FileLoader *l)
{
    if (l->file == -1)
        return;
    l->file = -1;
    if (l->heap)
        f_0996dc(l->heap, l->mark);
    else
        free(l->raw);
    l->raw = 0;
}

/* @implements 0x002c50 us f_002c50
   WHAT IT DOES: Queues the read of a single file from RRP.DAT unless it is already loaded and,
   unless asked not to, waits for the loading to finish. */
void f_002c50(FileLoader *l, unsigned char nowait)
{
    if (l->data)
        return;
    if (D_1b8c00 == 2) {
        File *f = &D_1c0614[l->file];
        Request r = { 1, l, l->buf, 0, 0, 0, f->sector, f->sectors, l->file, l->file + 1, 0, 0, 0 };
        D_1da468.Add(r);
    }
    if (!nowait)
        f_001e34(&D_1da468);
}

/* @implements 0x002de4 us f_002de4
   WHAT IT DOES: Records where a single file's data starts once it is read: the sector read
   from RRP.DAT starts the file's offset within its first sector early. */
void f_002de4(FileLoader *l)
{
    if (D_1b8c00 != 2) {
        l->data = l->buf;
        return;
    }
    if (l->file == -1) {
        l->data = 0;
        return;
    }
    l->data = l->buf + D_1c0614[l->file].offset % 2048;
}

/* @implements 0x002e5c us f_002e5c
   WHAT IT DOES: Returns a single file's data, or 0 while it is not loaded. */
void *f_002e5c(FileLoader *l)
{
    return l->data;
}

}

/* @draft 0x002e64 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the unpack queue and the load job, both empty. */

/* @implements 0x002ebc us _GLOBAL__I
   WHAT IT DOES: Runs the constructors of this object file's globals at startup. */
