/* The movie stream feeder object file (retail 0x08d0a4 to 0x08d2b8): the semaphore the movie
   decoder sleeps on, and the thread that keeps the MPEG ring buffer filled from the stream,
   2048 byte packets at a time, signalling the decoder after each fill. */

#include "psp/kernel.h"

extern "C" {
SceUID sceKernelCreateSema(const char *name, unsigned int attr, int init, int max, void *opt);
int sceKernelDeleteSema(SceUID sema);
int sceKernelSignalSema(SceUID sema, int count);
int sceKernelDelayThread(unsigned int usec);
int sceKernelExitThread(int status);
int sceMpegRingbufferAvailableSize(void *ring);
int sceMpegRingbufferPut(void *ring, int packets, int available);
}

extern int D_242bdc;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* What the feeder thread is given: the stream size, the decoder's semaphore, the ring buffer
   and the shared state word (2 stops the thread; set to 1 when the whole stream is in). */
struct FeedArgs {
    int total;
    SceUID sema;
    void *ring;
    int *state;
};

class CMpegFeeder {
public:
    CMpegFeeder(void *ring);
    ~CMpegFeeder();
    int f_08d17c(int s);

    int m0;
    SceUID sema;
    void *ring;
    int *state;
};

/* @implements 0x08d0a4 us _ZN11CMpegFeederC2EPv
   WHAT IT DOES: Constructs the feeder: keeps the ring buffer, points at the shared state word
   and creates the decoder's semaphore. */
/* @implements 0x08d0f4 us _ZN11CMpegFeederC1EPv
   WHAT IT DOES: The same constructor (complete object version). */
CMpegFeeder::CMpegFeeder(void *r)
{
    ring = r;
    state = &D_242bdc;
    sema = sceKernelCreateSema("decode_sleep_sema", 0, 0, 1, 0);
}

/* @implements 0x08d144 us _ZN11CMpegFeederD2Ev
   WHAT IT DOES: Destroys the decoder's semaphore. */
/* @implements 0x08d160 us _ZN11CMpegFeederD1Ev
   WHAT IT DOES: The same destructor (complete object version). */
CMpegFeeder::~CMpegFeeder()
{
    sceKernelDeleteSema(sema);
}

/* @implements 0x08d17c us f_08d17c
   WHAT IT DOES: Clears the shared state word and records s. Returns 0. */
int CMpegFeeder::f_08d17c(int s)
{
    *state = 0;
    m0 = s;
    return 0;
}

/* @draft 0x08d190 us f_08d190
   WHAT IT DOES: The feeder thread: until told to stop, puts as many packets of the stream as
   the ring buffer has room for (32 at most), signals the decoder, marks the stream complete
   once it is all in, and sleeps 100 microseconds.
   Remaining difference: the packet count. Retail keeps it in v0 (the put's result, zeroed on
   each skip path) and computes the remaining size after the size test; here it gets its own
   register, zeroed ahead of the test, and the remaining size is computed early. */
int f_08d190(SceSize args, void *argp)
{
    FeedArgs *p = (FeedArgs *)argp;
    FeedArgs a = *p;
    int done = 0;
    while (*p->state != 2) {
        int avail = sceMpegRingbufferAvailableSize(a.ring);
        int n;
        if (avail > 0) {
            if (done < a.total) {
                n = sceMpegRingbufferPut(a.ring, avail >= 32 ? 32 : MIN(avail, a.total - done),
                                         avail);
                if (n < 0)
                    break;
            } else
                n = 0;
        } else
            n = 0;
        done += n << 11;
        sceKernelSignalSema(a.sema, 1);
        if (done == a.total) {
            if (*a.state == 0)
                *a.state = 1;
        }
        sceKernelDelayThread(100);
    }
    sceKernelExitThread(0);
    return 0;
}

/* @implements 0x08d2b0 us f_08d2b0
   WHAT IT DOES: Nothing (returns 1). */
int f_08d2b0()
{
    return 1;
}
