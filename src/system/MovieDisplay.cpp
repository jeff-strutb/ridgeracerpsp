/* The movie display object file (retail 0x08c3e4 to 0x08cb30): a ring of decoded frame
   buffers that the movie thread fills and the display thread shows once per vertical
   blank. The ring's counters live in globals so both threads share them; three semaphores
   start the display, lock the counters and pace the decoder. */

#include "psp/kernel.h"

extern "C" {
SceUID sceKernelCreateSema(const char *name, unsigned int attr, int init, int max, void *opt);
int sceKernelDeleteSema(SceUID sema);
int sceKernelWaitSema(SceUID sema, int count, unsigned int *timeout);
int sceKernelSignalSema(SceUID sema, int count);
int sceKernelPollSema(SceUID sema, int count);
int sceKernelExitThread(int status);
int sceDisplayWaitVblankStart(void);
void *malloc(unsigned int size);
void free(void *p);
}

void *f_125c4c(unsigned int align, unsigned int size);
void f_021720(void);
void f_021750(void);
void f_021e20(int psm, unsigned int fill);
void f_022ac8(int psm, int sx, int sy, int height, int width, int srcw, void *src, int dx, int dy);

extern int D_242ba4;
extern int D_242ba8;
extern int D_242bac;
extern int D_242bb0;
extern int D_242bb4;
extern int D_242bb8;
extern int D_242bbc;
extern int D_1d47a8;

/* The display object's data; the display thread works on a copy of it. */
struct SMovieDisplay {
    SceUID start;
    SceUID lock;
    SceUID wait;
    int *quit;
    void **bufs;
    int *write;
    int *read;
    int *filled;
    int *count;
    SceUID sync;
    int m40;
};

class CMovieDisplay : public SMovieDisplay {
public:
    CMovieDisplay(int size, int n, SceUID sync);
    ~CMovieDisplay();
    int Reset();
    int Front(void **out);
    int Push();
    int Show();
};

/* @implements 0x08c3e4 us _ZN13CMovieDisplayC2Eiii
   WHAT IT DOES: Clears the screen, creates the start, lock and display wait semaphores,
   allocates n frame buffers of size bytes (16 byte aligned) and points the counters at the
   shared globals. */
/* @implements 0x08c528 us _ZN13CMovieDisplayC1Eiii
   WHAT IT DOES: The same constructor (complete object version). */
CMovieDisplay::CMovieDisplay(int size, int n, SceUID s)
{
    f_021e20(3, 0);
    start = sceKernelCreateSema("start_sema", 0, 0, 1, 0);
    lock = sceKernelCreateSema("lock_sema", 0, 1, 1, 0);
    wait = sceKernelCreateSema("display_wait_sema", 0, 0, 1, 0);
    bufs = (void **)malloc(n * 4);
    for (int i = 0; i < n; i++) {
        void **slot = (void **)(i * 4 + (int)bufs);
        *slot = f_125c4c(16, size);
    }
    sync = s;
    D_242bb4 = n;
    quit = &D_242ba4;
    write = &D_242ba8;
    read = &D_242bac;
    filled = &D_242bb0;
    count = &D_242bb4;
    m40 = 0;
}

/* @implements 0x08c66c us _ZN13CMovieDisplayD2Ev
   WHAT IT DOES: Frees the frame buffers and deletes the semaphores. */
/* @implements 0x08c70c us _ZN13CMovieDisplayD1Ev
   WHAT IT DOES: The same destructor (complete object version). */
CMovieDisplay::~CMovieDisplay()
{
    if (bufs) {
        for (int i = 0; i < *count; i++) {
            if (bufs[i])
                free(bufs[i]);
        }
        free(bufs);
    }
    sceKernelDeleteSema(start);
    sceKernelDeleteSema(lock);
    sceKernelDeleteSema(wait);
}

/* @implements 0x08c7ac us _ZN13CMovieDisplay5ResetEv
   WHAT IT DOES: Empties the ring and the frame counters and takes back any pending signal of
   the start, display wait and sync semaphores. Returns 0. */
int CMovieDisplay::Reset()
{
    D_242bb8 = 0;
    D_242bbc = 0;
    *quit = 0;
    *write = 0;
    *read = 0;
    *filled = 0;
    sceKernelPollSema(start, 1);
    sceKernelPollSema(wait, 1);
    sceKernelPollSema(sync, 1);
    return 0;
}

/* @implements 0x08c824 us _ZN13CMovieDisplay5FrontEPPv
   WHAT IT DOES: Returns the number of free buffers; when there is one, *out is the next
   buffer to decode into, else 0. */
int CMovieDisplay::Front(void **out)
{
    int n = *count - *filled;
    if (n > 0)
        *out = bufs[*write];
    else
        *out = 0;
    return n;
}

/* @implements 0x08c868 us _ZN13CMovieDisplay4PushEv
   WHAT IT DOES: Queues the decoded buffer: one more filled, the write index advanced round
   the ring, under the lock. Returns 0. */
int CMovieDisplay::Push()
{
    sceKernelWaitSema(lock, 1, 0);
    (*filled)++;
    *write = (*write + 1) % *count;
    sceKernelSignalSema(lock, 1);
    return 0;
}

/* @implements 0x08c8e0 us _ZN13CMovieDisplay4ShowEv
   WHAT IT DOES: Copies the next frame buffer to the screen. Every second call it releases
   the buffer (one fewer filled, never below 0) and signals the display wait semaphore.
   Returns 0. */
int CMovieDisplay::Show()
{
    void *buf = bufs[(*write + 1) % *count];
    f_021720();
    f_022ac8(3, 0, 0, 272, 480, 512, buf, 0, 0);
    f_021750();
    D_1d47a8 = !D_1d47a8;
    if (D_1d47a8) {
        sceKernelWaitSema(lock, 1, 0);
        if (--*filled < 0)
            *filled = 0;
        sceKernelSignalSema(lock, 1);
        sceKernelSignalSema(wait, 1);
    }
    return 0;
}

/* @implements 0x08c9d4 us f_08c9d4
   WHAT IT DOES: The display thread. It gets a copy of the display object, waits for the
   start signal, signals the sync semaphore once and waits vertical blanks (counting them)
   until the quit flag is set, then signals again and counts down the filled buffers once
   per lock until fewer than two remain, and exits. */
int f_08c9d4(SceSize args, void *argp)
{
    SMovieDisplay *p = (SMovieDisplay *)argp;
    SMovieDisplay d = *p;
    int first = 1;

    sceKernelWaitSema(d.start, 1, 0);
    while (*p->quit == 0) {
        if (first) {
            sceKernelSignalSema(d.sync, 1);
            first = 0;
        }
        sceDisplayWaitVblankStart();
        D_242bb8++;
    }
    sceKernelSignalSema(d.sync, 1);
    while (*p->filled >= 2) {
        sceKernelWaitSema(d.lock, 1, 0);
        (*d.filled)--;
        sceKernelSignalSema(d.lock, 1);
        D_242bb8++;
    }
    sceKernelExitThread(0);
    return 0;
}
