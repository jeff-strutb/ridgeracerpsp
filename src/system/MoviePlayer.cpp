/* The movie player object file (retail 0x08a3c0 to 0x08c3e4): plays a PMF movie through
   sceMpeg with a display, a read, a movie and (for movies with sound) a sound thread. One
   player exists at a time (D_242b90); the state globals tell the game whether a movie is
   starting, playing or finished. The introduction movies carry hard subtitles, a timing
   table read from the MovieHardSub package and drawn over the movie. The object file ends
   with a small two-ended buffer allocator and the "movie" variable-length memory pool the
   decoder buffers come from. */

#include "psp/kernel.h"

extern "C" {
int strcmp(const char *, const char *);
int iprintf(const char *, ...);
void *malloc(unsigned int size);
void free(void *p);
SceUID sceKernelCreateVpl(const char *name, int part, unsigned int attr, unsigned int size, void *opt);
int sceKernelDeleteVpl(SceUID uid);
int sceKernelAllocateVpl(SceUID uid, unsigned int size, void **data, unsigned int *timeout);
SceUID sceKernelCreateSema(const char *name, unsigned int attr, int init, int max, void *opt);
int sceKernelDeleteSema(SceUID sema);
int sceKernelWaitSema(SceUID sema, int count, unsigned int *timeout);
int sceKernelSignalSema(SceUID sema, int count);
SceUID sceKernelCreateThread(const char *name, int (*entry)(SceSize, void *), int prio, int stack, unsigned int attr, void *opt);
int sceKernelStartThread(SceUID thid, SceSize arglen, void *argp);
int sceKernelWaitThreadEnd(SceUID thid, unsigned int *timeout);
int sceKernelTerminateDeleteThread(SceUID thid);
SceUID sceKernelGetThreadId(void);
int sceKernelGetThreadCurrentPriority(void);
int sceMpegInit(void);
int sceMpegFinish(void);
int sceMpegRingbufferQueryMemSize(int packets);
int sceMpegRingbufferConstruct(void *ring, int packets, void *data, int size, int (*cb)(void *, int, void *), void *param);
void sceMpegRingbufferDestruct(void *ring);
int sceMpegRingbufferAvailableSize(void *ring);
int sceMpegQueryMemSize(int mode);
int sceMpegCreate(void *mpeg, void *data, int size, void *ring, int width, int mode, int ddrtop);
void sceMpegDelete(void *mpeg);
int sceMpegQueryStreamOffset(void *mpeg, void *buf, unsigned int *offset);
int sceMpegQueryStreamSize(void *buf, int *size);
void *sceMpegRegistStream(void *mpeg, int type, int num);
int sceMpegUnRegistStream(void *mpeg, void *stream);
void *sceMpegMallocAvcEsBuf(void *mpeg);
void sceMpegFreeAvcEsBuf(void *mpeg, void *buf);
int sceMpegQueryAtracEsSize(void *mpeg, int *es, int *out);
int sceMpegInitAu(void *mpeg, void *buf, void *au);
int sceMpegGetAvcAu(void *mpeg, void *stream, void *au, int *attr);
int sceMpegGetAtracAu(void *mpeg, void *stream, void *au, void *attr);
int sceMpegFlushAllStream(void *mpeg);
int sceMpegAvcDecode(void *mpeg, void *au, int width, void *buf, int *n);
int sceMpegAvcDecodeStop(void *mpeg, int width, void *buf, int *n);
int sceMpegAtracDecode(void *mpeg, void *au, void *buf, int init);
}

void *f_125c4c(unsigned int align, unsigned int size);
void f_021720(void);
void f_021750(void);
void f_021e20(int psm, unsigned int fill);
void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...);
int f_01c260(void);
int f_06cafc(void *font, int id, int a);
void f_06ccf8(void *font, int x, int y, int id, float sx, float sy, float r, float g, float b, float a, int w);
int f_08c9d4(SceSize args, void *argp);
int f_08d190(SceSize args, void *argp);
int f_08cef8(SceSize args, void *argp);

extern char D_24517c[];
extern void *D_242b50;

/* Movie state shared with the game. */
extern int D_1d46ec;   /* 1 while playing; the game writes -10 to stop the movie */
extern int D_1d46f0;   /* 0 while a short stream read is being retried */
extern int D_1d46f4;
extern int D_1d46f8;   /* the movie has sound */
extern int D_1d46fc;   /* draw the subtitles */
extern void *D_242b68; /* the frame buffer being decoded into */
extern int D_242b6c;   /* setup error: 0, 1 (file) or 5 (decoder) */
extern int D_242b70;   /* 0 starting, 1 playing, 2 finished */
extern int D_242b74;   /* 1 while a player exists, -1 just after it ended */
extern int D_242b78;   /* frames played */
extern int D_242b7c;   /* the movie number */

/* A data package: one archive file from the disc, whose entries are looked up by name. */
class CPackage {
public:
    CPackage() { m0 = -1; }
    ~CPackage() { f_0026cc(); }
    void f_00260c(const char *name, int a, int b);
    void f_0026cc();
    void f_002734(int a);
    char *f_002acc(const char *name);
    int m0;
    int m4[69];
};

/* The hard subtitle table. */
class CMovieHardSub {
public:
    CMovieHardSub();
    ~CMovieHardSub();
    int Load();
    void Clear(char *buf, int n);
    int Draw();

    int start[15];
    int end[15];
    int id[15];
    int count;
    int m184;
    int m188;
    int m192;
    int m196;
    float m200;
    int m204;
    int m208;
    float m212;
    float m216;
};

/* The movie stream file (its own object file). */
class CMovieFile {
public:
    CMovieFile() { fd = -1; }
    int f_08d2b0(const char *name, int mode);
    int f_08d2b8(const char *name, int mode);
    int f_08d2f8();
    int f_08d334(void *buf, int size);
    long long f_08d36c(long long offset, int whence);

    int fd;
};

/* The display ring (MovieDisplay.cpp). */
class CMovieDisplay {
public:
    CMovieDisplay(int size, int n, SceUID sync);
    ~CMovieDisplay();
    int f_08c7ac();
    int f_08c824(void **out);
    int f_08c868();
    int f_08c8e0();
    int Space() { return *count - *filled; }

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
    int busy;
};

/* The stream feeder (MpegFeeder.cpp). */
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

/* The sound queue (AudioQueue.cpp). */
class CAudioQueue {
public:
    CAudioQueue(int size, int count, int arg);
    ~CAudioQueue();
    int f_08cd90();
    int f_08cdc8(void **out);
    int f_08ce0c();
    int Space() { return *count - *filled; }

    SceUID sema;
    int *quit;
    void **bufs;
    int *write;
    int *read;
    int *filled;
    int *count;
    int m28;
};

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

/* The streams the movie thread decodes. */
struct MovieStreams {
    void *video;
    void *videoAu;
    void *audio;
    void *audioAu;
};

class CMoviePlayer {
public:
    CMoviePlayer(const char *name, int sound);
    ~CMoviePlayer();
    int Update();
    int Start(const char *name);
    int Ready();
    int FindStream(void *mpeg, CMovieFile *f, int *size);
    int Decode(void *ring, MovieStreams *s);

    int mpeg;
    char ring[44];
    void *video;
    void *audio;
    char videoAu[24];
    char audioAu[24];
    CMovieFile file;
    int m108[3];
    int ringSize;
    int mpegSize;
    int streamSize;
    int atracSize;
    int atracOut;
    MovieStreams streams;
    void *avcBuf;
    void *ringData;
    void *mpegData;
    void *atracBuf;
    SceUID displayThread;
    SceUID readThread;
    SceUID soundThread;
    SceUID movieThread;
    SceUID syncSema;
    int priority;
    int movie;
    int frames;
};

extern CMovieDisplay *D_242b84;
extern CAudioQueue *D_242b88;
extern CMpegFeeder *D_242b8c;
extern CMoviePlayer *D_242b90;
extern CMovieHardSub *D_242b94;
extern CMovieVpl *D_242b9c;


int f_08be98(void *data, int packets, void *param);
int f_08ba74(SceSize args, void *argp);

/* @implements 0x08a3c0 us _ZN13CMovieHardSubC2Ev
   WHAT IT DOES: Empties the table and sets the subtitle drawing defaults (position 240, 236,
   width 246, scale 0.8, fade over 10 frames). */
/* @implements 0x08a41c us _ZN13CMovieHardSubC1Ev
   WHAT IT DOES: The same constructor (complete object version). */
CMovieHardSub::CMovieHardSub()
{
    m184 = 240;
    m188 = 236;
    m192 = 246;
    m196 = 1;
    m200 = 0.8f;
    m204 = 1;
    m208 = 10;
    m212 = 1.0f;
    count = 0;
    m216 = m212 / m208;
}

/* @implements 0x08a478 us _ZN13CMovieHardSubD2Ev
   WHAT IT DOES: The empty destructor. */
/* @implements 0x08a480 us _ZN13CMovieHardSubD1Ev
   WHAT IT DOES: The same (complete object version). */
CMovieHardSub::~CMovieHardSub()
{
}

/* @draft 0x08a488 us _ZN13CMovieHardSub4LoadEv
   WHAT IT DOES: Opens the MovieHardSub package and parses its Hardsub text: for each "STR"
   line it reads the start, end and id numbers into the next table entry; "END" stores the
   entry count. An unknown word prints an error and returns 1; otherwise returns 0.
   Remaining difference: retail reads the third number's digits with lbu and keeps the byte
   in a register (seb at the compare and at the add, as for the word copy loop); every
   spelling tried gives lb, which shifts the register choice of all three numbers. */
int CMovieHardSub::Load()
{
    char line[128];
    CPackage pkg;
    char word[64];
    int n = 0;

    pkg.f_00260c("MovieHardSub", 0, 0);
    pkg.f_002734(0);
    char *p = pkg.f_002acc("Hardsub");
    if (*p) {
        do {
            int i;
            int a, b, c;
            Clear(word, 64);
            for (i = 0; *p != ' ' && *p != '\n'; i++) {
                word[i] = *p;
                p++;
            }
            p++;
            if (strcmp("END", word) == 0) {
                count = n;
                break;
            }
            if (strcmp("STR", word) != 0) {
                iprintf("ERROR : (work)%s\n", word);
                pkg.f_0026cc();
                return 1;
            }
            a = 0;
            while (*p != ' ') {
                a = a * 10 + *p - '0';
                p++;
            }
            p++;
            b = 0;
            while (*p != ' ') {
                b = b * 10 + *p - '0';
                p++;
            }
            p++;
            c = 0;
            char ch = *p;
            while (ch != '\n') {
                p++;
                c = c * 10 + ch - '0';
                ch = *p;
            }
            start[n] = a;
            end[n] = b;
            id[n] = c;
            p++;
            n++;
        } while (*p);
    }
    pkg.f_0026cc();
    return 0;
}

/* @implements 0x08a6f8 us _ZN13CMovieHardSub5ClearEPci
   WHAT IT DOES: Zeroes n bytes of buf. */
void CMovieHardSub::Clear(char *buf, int n)
{
    for (int i = 0; i < n; i++)
        buf[i] = 0;
}

/* The movie files by number. */
const char *D_1d4700[] = {
    "Movie/opening.pmf",
    "Movie/introduction.pmf",
    "Movie/intro_eng.pmf",
    "Movie/intro_fre.pmf",
    "Movie/intro_spa.pmf",
    "Movie/intro_ger.pmf",
    "Movie/intro_ita.pmf",
    "Movie/e3.pmf",
    "Movie/rage.pmf",
    "Movie/r4.pmf",
    "Movie/rave.pmf",
    "Movie/namcomuseum.pmf",
    "Movie/ending.pmf",
};

/* @implements 0x08a71c us f_08a71c
   WHAT IT DOES: Starts movie number movie (1 picks the introduction in the system
   language) unless a player already exists: creates the player and marks it running.
   Returns 0. */
int f_08a71c(int movie, int sound)
{
    if (D_242b74 == -1 || D_242b74 == 0) {
        D_1d46ec = 1;
        if (movie == 1) {
            switch (f_01c260()) {
            case 2:
                D_242b7c = 3;
                break;
            case 0:
            case 1:
            default:
                D_242b7c = 2;
                break;
            case 3:
                D_242b7c = 4;
                break;
            case 4:
                D_242b7c = 5;
                break;
            case 5:
                D_242b7c = 6;
                break;
            }
        } else {
            D_242b7c = movie;
        }
        D_242b90 = new CMoviePlayer(D_1d4700[D_242b7c], sound);
        D_242b90->movie = D_242b7c;
        D_242b74 = 1;
    }
    return 0;
}

/* @implements 0x08a864 us f_08a864
   WHAT IT DOES: Steps the running movie once per game frame and draws its subtitles.
   Returns 1 while it plays; when it has finished, frees the player and the subtitles and
   returns -1; returns 0 when no movie runs. */
int f_08a864(void)
{
    if (D_242b74 == 1 && D_242b90) {
        if (D_242b90->Update() == 1) {
            D_242b74 = -1;
            if (D_242b7c >= 1 && D_242b7c <= 6)
                delete D_242b94;
            delete D_242b90;
            D_1d46f4 = 1;
            D_242b90 = 0;
            return -1;
        }
        if (D_242b7c >= 1 && D_242b7c <= 6)
            D_242b94->Draw();
        D_242b78++;
        return 1;
    }
    if (D_242b74 == -1)
        D_242b74 = 0;
    return 0;
}

/* @implements 0x08a998 us f_08a998
   WHAT IT DOES: Asks the running movie to stop. */
void f_08a998(void)
{
    if (D_242b74 == 1)
        D_1d46ec = -10;
}

/* @implements 0x08a9c0 us f_08a9c0
   WHAT IT DOES: Returns the movie state (1 while a movie runs). */
int f_08a9c0(void)
{
    return D_242b74;
}

/* @draft 0x08a9cc us _ZN12CMoviePlayerC2EPKci
   WHAT IT DOES: Sets the movie up: the memory pool, sceMpeg with its ring buffer and the
   video (and sound) streams, the display ring, the stream feeder, the sound queue, the
   subtitles for the introduction movies and the four threads; then opens the file and
   starts playing. A failure records 5 (decoder) or 1 (file) in D_242b6c and marks the movie
   finished. */
/* @draft 0x08ae24 us _ZN12CMoviePlayerC1EPKci
   WHAT IT DOES: The same constructor (complete object version).
   Remaining difference (both versions): register allocation and block order of the failure
   paths (retail keeps several globals' high halves in saved registers and stores the error
   code from one shared tail); the call sequence is the same. */
CMoviePlayer::CMoviePlayer(const char *name, int sound)
{
    displayThread = 0;
    readThread = 0;
    soundThread = 0;
    movieThread = 0;
    syncSema = 0;
    avcBuf = 0;
    D_1d46f8 = sound;
    D_242b6c = 0;
    D_242b70 = 0;
    ringData = 0;
    mpegData = 0;
    atracBuf = 0;
    frames = 0;
    D_242b9c = new CMovieVpl;
    priority = sceKernelGetThreadCurrentPriority();
    if (sceMpegInit() != 0)
        goto fail;
    ringSize = sceMpegRingbufferQueryMemSize(320);
    if (ringSize < 0)
        goto fail;
    mpegSize = sceMpegQueryMemSize(0);
    if (mpegSize < 0)
        goto fail;
    ringData = malloc(ringSize);
    if (!ringData)
        goto fail;
    mpegData = D_242b9c->Alloc(mpegSize);
    if (!mpegData)
        goto fail;
    if (sceMpegRingbufferConstruct(ring, 320, ringData, ringSize, f_08be98, &file) != 0)
        goto fail;
    if (sceMpegCreate(this, mpegData, mpegSize, ring, 512, 0, 0) != 0)
        goto fail;
    video = sceMpegRegistStream(this, 0, 0);
    if (!video)
        goto fail;
    if (D_1d46f8) {
        audio = sceMpegRegistStream(this, 1, 0);
        if (!audio)
            goto fail;
    }
    avcBuf = sceMpegMallocAvcEsBuf(this);
    if (!avcBuf)
        goto fail;
    if (sceMpegInitAu(this, avcBuf, videoAu) != 0)
        goto fail;
    if (D_1d46f8) {
        if (sceMpegQueryAtracEsSize(this, &atracSize, &atracOut) != 0)
            goto fail;
        atracBuf = f_125c4c(64, atracSize);
        if (!atracBuf)
            goto fail;
        if (sceMpegInitAu(this, atracBuf, audioAu) != 0)
            goto fail;
    }
    streams.video = video;
    streams.videoAu = videoAu;
    streams.audio = audio;
    streams.audioAu = audioAu;
    syncSema = sceKernelCreateSema("sync_sema", 0, 0, 1, 0);
    D_242b84 = new CMovieDisplay(0x88000, 4, syncSema);
    D_242b8c = new CMpegFeeder(ring);
    D_242b88 = new CAudioQueue(atracOut, 10, syncSema);
    if (D_242b7c >= 1 && D_242b7c <= 6) {
        D_242b94 = new CMovieHardSub;
        D_242b94->Load();
    }
    displayThread = sceKernelCreateThread("displayThread", f_08c9d4, 62, 2048, 0, 0);
    readThread = sceKernelCreateThread("readThread", f_08d190, 65, 2048, 0, 0);
    movieThread = sceKernelCreateThread("movieThread", f_08ba74, 63, 2048, 0, 0);
    if (D_1d46f8)
        soundThread = sceKernelCreateThread("soundThread", f_08cef8, 61, 2048, 0, 0);
    if (file.f_08d2b0(name, 1) < 0) {
        D_242b6c = 1;
        goto done;
    }
    sceKernelChangeThreadPriority(sceKernelGetThreadId(), 64);
    if (Start(name) == -1) {
        D_242b6c = 1;
        goto done;
    }
    goto done;
fail:
    D_242b6c = 5;
done:
    if (D_242b6c)
        D_242b70 = 2;
}

/* @implements 0x08b27c us _ZN12CMoviePlayer6UpdateEv
   WHAT IT DOES: Once the display ring is full and the stream buffered, starts the display;
   while playing, shows the next frame and counts frames. Returns 1 once the movie has
   finished, else 0. */
int CMoviePlayer::Update()
{
    if (D_242b70 == 0) {
        if (Ready() == 0)
            D_242b70 = 1;
    }
    if (D_242b70 == 1)
        D_242b84->f_08c8e0();
    if (D_242b70 == 2)
        return 1;
    if (D_242b70 == 1) {
        if (D_1d46f0)
            frames++;
    }
    return 0;
}

/* @implements 0x08b32c us _ZN12CMoviePlayerD2Ev
   WHAT IT DOES: Tears the movie down as far as it was set up: stops and deletes the threads
   and frees the display ring, feeder and sound queue (after a full start), then frees the
   decoder, its buffers and the memory pool, restores the thread priority and clears the
   screen. */
/* @implements 0x08b598 us _ZN12CMoviePlayerD1Ev
   WHAT IT DOES: The same destructor (complete object version). */
CMoviePlayer::~CMoviePlayer()
{
    int r;
    switch (D_242b6c) {
    case 0:
    case 1:
        file.f_08d2f8();
        if (D_1d46f8)
            r = sceKernelWaitThreadEnd(soundThread, 0);
        if (r < 0)
            iprintf("Error : wait sound thread end %x\n", r);
        if (D_1d46f8)
            sceKernelTerminateDeleteThread(soundThread);
        while (D_242b84->busy == 1)
            ;
        sceKernelTerminateDeleteThread(displayThread);
        sceKernelTerminateDeleteThread(readThread);
        sceKernelTerminateDeleteThread(movieThread);
        delete D_242b8c;
        D_242b8c = 0;
        delete D_242b88;
        D_242b88 = 0;
        delete D_242b84;
        D_242b84 = 0;
    case 5:
        sceKernelDeleteSema(syncSema);
        if (D_1d46f8 && atracBuf)
            free(atracBuf);
        sceMpegFreeAvcEsBuf(this, avcBuf);
        sceMpegUnRegistStream(this, video);
        if (D_1d46f8)
            sceMpegUnRegistStream(this, audio);
        sceMpegDelete(this);
        sceMpegRingbufferDestruct(ring);
        sceMpegFinish();
        if (ringData)
            free(ringData);
        D_242b70 = 2;
        sceKernelChangeThreadPriority(sceKernelGetThreadId(), priority);
        delete D_242b9c;
        D_242b9c = 0;
        f_021e20(1, 0);
        break;
    }
}

/* @implements 0x08b804 us _ZN12CMoviePlayer5StartEPKc
   WHAT IT DOES: Opens the movie file (retrying until it opens), finds the stream in it
   (retrying likewise), resets the display ring and the feeder and starts the threads. */
int CMoviePlayer::Start(const char *name)
{
    while (file.f_08d2b8(name, 1) < 0)
        ;
    while (FindStream(this, &file, &streamSize) != 0)
        ;
    if (D_1d46f8)
        D_242b88->f_08cd90();
    D_242b84->f_08c7ac();
    D_242b8c->f_08d17c(streamSize);
    if (D_1d46f8)
        sceKernelStartThread(soundThread, 32, D_242b88);
    sceKernelStartThread(displayThread, 44, D_242b84);
    sceKernelStartThread(readThread, 16, D_242b8c);
    sceKernelStartThread(movieThread, 204, this);
    return 0;
}

/* @draft 0x08b910 us _ZN12CMoviePlayer5ReadyEv
   WHAT IT DOES: Once every display buffer is filled and the stream is either fully read or
   the ring buffer full, signals the display thread to start and returns 0; else -1.
   Remaining difference: the result register. Retail sets v0 directly (li v0,-1 in the branch
   slots, move v0,zero after the signal); here it is a2 with a move at the exit. The goto
   spelling is needed for retail's reload of D_242b84 on the state path. */
int CMoviePlayer::Ready()
{
    if (*D_242b84->filled != *D_242b84->count)
        return -1;
    if (*D_242b8c->state == 1)
        goto start;
    if (sceMpegRingbufferAvailableSize(D_242b8c->ring))
        return -1;
start:
    sceKernelSignalSema(D_242b84->start, 1);
    return 0;
}

/* @implements 0x08b98c us _ZN12CMoviePlayer10FindStreamEPvP10CMovieFilePi
   WHAT IT DOES: Reads the PMF header from the start of the file, gets the stream's offset
   and size from it and seeks the file to the stream. Returns 0, or -1 on any failure. */
int CMoviePlayer::FindStream(void *mpeg, CMovieFile *f, int *size)
{
    char head[2048];
    unsigned int offset;

    if (f->f_08d36c(0, 0) < 0)
        return -1;
    if (f->f_08d334(head, 2048) < 2048)
        return -1;
    if (sceMpegQueryStreamOffset(mpeg, head, &offset) != 0)
        return -1;
    if (sceMpegQueryStreamSize(head, size) != 0)
        return -1;
    if (f->f_08d36c(0, 0) < 0)
        return -1;
    if (f->f_08d36c(offset, 0) < 0)
        return -1;
    return 0;
}

/* @draft 0x08ba74 us f_08ba74
   WHAT IT DOES: The movie thread: runs the decoder on its copy of the player. When the movie
   ends normally it waits for the other threads to end and returns 0; otherwise it flushes the
   streams when asked to (10) and returns 1.
   Remaining difference: retail keeps the result in a1 (set to 0 in the slots of the thread
   waits, 1 after the flush) and returns through one exit; here it goes straight to v0. A
   result variable, reusing r and a default of 1 all give v0. */
int f_08ba74(SceSize args, void *argp)
{
    CMoviePlayer *p = (CMoviePlayer *)argp;
    int r = p->Decode(p->ring, &p->streams);
    if (r != 0) {
        if (r == 10)
            sceMpegFlushAllStream(p);
        return 1;
    }
    if (D_1d46f8)
        sceKernelWaitThreadEnd(p->soundThread, 0);
    sceKernelWaitThreadEnd(p->displayThread, 0);
    sceKernelWaitThreadEnd(p->readThread, 0);
    return 0;
}

/* @draft 0x08bb10 us _ZN12CMoviePlayer6DecodeEPvP12MovieStreams
   WHAT IT DOES: The decode loop: while the movie plays, decodes sound units into free sound
   buffers and video frames into free display buffers, waiting for the feeder when nothing
   could be decoded; stops when the stream has been read and the ring buffer drained. Then
   finishes the decoder into one last display buffer and sets the quit flags. Returns the
   play status (0 at a normal end), or -1 on a decoder error.
   Remaining difference: the loop layout. Retail threads the feeder wait tests into the loop
   top and keeps the status in s1; the control flow written here is a first transcription. */
int CMoviePlayer::Decode(void *rb, MovieStreams *s)
{
    int attr;
    void *abuf;
    int vattr;
    void *vbuf;
    int n;
    int first = 1;
    int status = D_1d46ec;

    while (status == 1) {
        if (*D_242b8c->state == 1) {
            status = 0;
            if (sceMpegRingbufferAvailableSize(rb) == 320)
                break;
        }
        if (D_1d46f8 == 1 && D_242b88->Space() > 0
            && sceMpegGetAtracAu(this, s->audio, s->audioAu, &attr) == 0) {
            D_242b88->f_08cdc8(&abuf);
            if (sceMpegAtracDecode(this, s->audioAu, abuf, first) != 0) {
                D_242b70 = 2;
                return -1;
            }
            if (!first)
                D_242b88->f_08ce0c();
            first = 0;
        } else if (*D_242b8c->state != 1 && sceMpegRingbufferAvailableSize(D_242b8c->ring) != 0) {
            sceKernelWaitSema(D_242b8c->sema, 1, 0);
        }
        int r;
        if (D_242b84->Space() > 0 && (r = sceMpegGetAvcAu(this, s->video, s->videoAu, &vattr)) == 0) {
            D_242b84->f_08c824(&vbuf);
            D_242b68 = vbuf;
            if (sceMpegAvcDecode(this, s->videoAu, 512, &D_242b68, &n) != 0) {
                D_242b70 = 2;
                return -1;
            }
            if (n == 1)
                D_242b84->f_08c868();
        } else {
            if (D_242b84->Space() > 0 && r != (int)0x80618001)
                return -1;
            if (*D_242b8c->state != 1 && sceMpegRingbufferAvailableSize(D_242b8c->ring) != 0)
                sceKernelWaitSema(D_242b8c->sema, 1, 0);
        }
        if (*D_242b8c->state == 1 || sceMpegRingbufferAvailableSize(D_242b8c->ring) == 0)
            sceKernelWaitSema(D_242b8c->sema, 1, 0);
        status = D_1d46ec;
    }
    D_242b70 = 2;
    sceKernelSignalSema(D_242b84->start, 1);
    *D_242b8c->state = 2;
    if (D_1d46f8)
        *D_242b88->quit = 1;
    while (D_242b84->f_08c824(&vbuf) <= 0)
        sceKernelWaitSema(D_242b84->wait, 1, 0);
    D_242b68 = vbuf;
    if (sceMpegAvcDecodeStop(this, 512, &D_242b68, &n) != 0)
        return -1;
    if (n > 0)
        D_242b84->f_08c868();
    *D_242b84->quit = 1;
    return status;
}

/* @draft 0x08be98 us f_08be98
   WHAT IT DOES: The ring buffer callback: reads packets 2048 byte packets of the stream into
   data. A read that ends inside a packet is retried (holding the display) until it ends on a
   packet boundary. Returns the number of packets read.
   Remaining difference: retail computes r % 2048 before the r != -1 test and joins both with
   and; here the -1 test branches first. */
int f_08be98(void *data, int packets, void *param)
{
    CMovieFile *f = (CMovieFile *)param;
    int unit = 2048;
    int size = packets << 11;
    int r = f->f_08d334(data, size);
    if (r != -1 && r % unit != 0) {
        sceKernelWaitSema(D_242b84->wait, 1, 0);
        D_1d46f0 = 0;
        do
            r = f->f_08d334(data, size);
        while (r % unit != 0);
        D_1d46f0 = 1;
        sceKernelSignalSema(D_242b84->wait, 1);
    }
    return r / unit;
}

/* @draft 0x08bfa8 us _ZN13CMovieHardSub4DrawEv
   WHAT IT DOES: Draws the subtitles whose time span holds the player's frame count: the
   message (one line lower when it has a single line) with its shadow offsets for modes 1
   and 2, after a debug print of the alpha. Returns 0.
   Remaining difference: retail counts the entries down in s2 with a pointer step and keeps
   1.0 in f20; the loop and register choice here differ. */
int CMovieHardSub::Draw()
{
    int frame = D_242b90->frames;
    for (int i = 0; i < count; i++) {
        if (frame < start[i] || end[i] < frame)
            continue;
        int lines = 2;
        if (D_1d46fc)
            lines = f_06cafc(D_242b50, id[i], 0);
        int y;
        if (lines == 1)
            y = m192;
        else
            y = m188;
        f_021720();
        if (m204 == 2 && D_1d46fc)
            f_06ccf8(D_242b50, m184 - m196, y - m196, id[i], m200, m200, 1.0f, 1.0f, 1.0f, m212, 0);
        if (m204 > 0 && D_1d46fc)
            f_06ccf8(D_242b50, m184 + m196, y + m196, id[i], m200, m200, 1.0f, 1.0f, 1.0f, m212, 0);
        f_02db68(D_24517c, 0x400000, 2, 10, 0, "m_nAlpha : %.2f", m212);
        if (D_1d46fc)
            f_06ccf8(D_242b50, m184, y, id[i], m200, m200, 0.0f, 0.0f, 0.0f, m212, 480);
        f_021750();
    }
    return 0;
}

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
