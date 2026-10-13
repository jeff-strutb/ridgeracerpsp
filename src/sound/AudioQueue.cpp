/* The movie sound queue object file (retail 0x08cb30 to 0x08d0a4): a ring of PCM buffers the
   movie decoder fills and an output thread plays on audio channel 1, guarded by a semaphore.
   The ring's counters live in globals so the thread and the decoder share them. */

#include "psp/kernel.h"

extern "C" {
SceUID sceKernelCreateSema(const char *name, unsigned int attr, int init, int max, void *opt);
int sceKernelDeleteSema(SceUID sema);
int sceKernelWaitSema(SceUID sema, int count, unsigned int *timeout);
int sceKernelSignalSema(SceUID sema, int count);
}

int f_119dc8(int channel, int samples);
int f_119f80(int channel, int left, int right, void *buf);
void *f_08c334(void *heap, int size);
void *f_08c378(void *heap, int align, int size);
extern void *D_242b9c;

extern int D_242bc0;
extern int D_242bc4;
extern int D_242bc8;
extern int D_242bcc;
extern int D_242bd0;
extern int D_242bd4;
extern int D_242bd8;

class CAudioQueue {
public:
    CAudioQueue(int size, int count, int arg);
    ~CAudioQueue();
    int f_08cd90();
    int f_08cdc8(void **out);
    int f_08ce0c();
    int f_08ce84();

    SceUID sema;
    int *quit;
    void **bufs;
    int *write;
    int *read;
    int *filled;
    int *count;
    int m28;
};

/* @draft 0x08cb30 us _ZN11CAudioQueueC2Eiii
   WHAT IT DOES: Constructs the queue: reserves the audio channel, creates the lock semaphore,
   allocates count buffers of size bytes and points the counters at the shared globals.
   Remaining difference: only the order of the closing stores. Retail stores +28, the buffer
   count global, +4, +12, +16, +20 and +24 last; no statement order tried gives that. */
/* @draft 0x08cc44 us _ZN11CAudioQueueC1Eiii
   WHAT IT DOES: The same constructor (complete object version); the same difference. */
CAudioQueue::CAudioQueue(int size, int n, int arg)
{
    f_119dc8(1, 2048);
    sema = sceKernelCreateSema("sound_lock_sema", 0, 1, 1, 0);
    bufs = (void **)f_08c334(D_242b9c, n * 4);
    for (int i = 0; i < n; i++) {
        void **slot = (void **)(i * 4 + (int)bufs);
        *slot = f_08c378(D_242b9c, 64, size);
    }
    D_242bd0 = n;
    quit = &D_242bc0;
    write = &D_242bc4;
    read = &D_242bc8;
    filled = &D_242bcc;
    count = &D_242bd0;
    m28 = arg;
}

/* @implements 0x08cd58 us _ZN11CAudioQueueD2Ev
   WHAT IT DOES: Destroys the lock semaphore. */
/* @implements 0x08cd74 us _ZN11CAudioQueueD1Ev
   WHAT IT DOES: The same destructor (complete object version). */
CAudioQueue::~CAudioQueue()
{
    sceKernelDeleteSema(sema);
}

/* @implements 0x08cd90 us f_08cd90
   WHAT IT DOES: Empties the queue and clears the play and stall counters. Returns 0. */
int CAudioQueue::f_08cd90()
{
    D_242bd4 = 0;
    D_242bd8 = 0;
    *quit = 0;
    *write = 0;
    *read = 0;
    *filled = 0;
    return 0;
}

/* @implements 0x08cdc8 us f_08cdc8
   WHAT IT DOES: Returns how many buffers are free and gives the next one to fill (none when
   the queue is full). */
int CAudioQueue::f_08cdc8(void **out)
{
    int n = *count - *filled;
    if (n > 0)
        *out = bufs[*write];
    else
        *out = 0;
    return n;
}

/* @implements 0x08ce0c us f_08ce0c
   WHAT IT DOES: Queues the buffer just filled (under the lock) and moves the fill position
   on. Returns 0. */
int CAudioQueue::f_08ce0c()
{
    sceKernelWaitSema(sema, 1, 0);
    (*filled)++;
    sceKernelSignalSema(sema, 1);
    *write = (*write + 1) % *count;
    return 0;
}

/* @implements 0x08ce84 us f_08ce84
   WHAT IT DOES: Plays the next queued buffer at full volume on channel 1 and moves the play
   position on. Returns 0. */
int CAudioQueue::f_08ce84()
{
    f_119f80(1, 0x8000, 0x8000, bufs[*read]);
    *read = (*read + 1) % *count;
    return 0;
}
