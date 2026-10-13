/* The game packet processor (retail 0x082e34 to 0x083990): received network packets sorted
   by data type into ring queues (eight 32 byte channel queues, a 24 byte queue and a 16 byte
   queue), read back by the game, and the one global processor's static construction. The
   queue template's methods are defined outside the class, so they are not inlined and are
   emitted at the end of the file (the last two, 0x083990 and 0x083a18, fall in the next
   object file row). */

extern "C" void *memcpy(void *, const void *, unsigned int);
extern "C" int iprintf(const char *, ...);

/* The network session object. */
extern char D_241810[];
extern "C" int f_086a60(void *net, int to, int type, void *data, int size);

/* A ring queue of records. Pushing onto a full queue drops the oldest record. */
template <class T> struct Queue {
    int head;
    int tail;
    int size;
    T *buf;

    void Create(int n);
    int Pop(T *out);
    void Push(const T *in);
    int Last(T *out);
};

/* @implements 0x083948 us _ZN5QueueI5Rec32E6CreateEi
   WHAT IT DOES: Allocates a queue of n channel records and empties it. */
template <class T> void Queue<T>::Create(int n)
{
    buf = new T[n];
    size = n;
    tail = 0;
    head = 0;
}

/* @implements 0x0835d4 us _ZN5QueueI5Rec24E3PopEPS0_
   WHAT IT DOES: Takes the oldest record off the queue; returns -1 when the queue is empty, 1
   otherwise. */
/* @implements 0x083654 us _ZN5QueueI5Rec16E3PopEPS0_
   WHAT IT DOES: The same for the 16 byte records. */
template <class T> int Queue<T>::Pop(T *out)
{
    if (tail == head)
        return -1;
    *out = buf[head];
    head++;
    if (head >= size)
        head = 0;
    return 1;
}

/* @implements 0x0836bc us _ZN5QueueI5Rec32E4PushEPKS0_
   WHAT IT DOES: Adds a record at the tail; when the queue was full the oldest record is
   dropped. */
/* @implements 0x083758 us _ZN5QueueI5Rec24E4PushEPKS0_
   WHAT IT DOES: The same for the 24 byte records. */
/* @implements 0x0837ec us _ZN5QueueI5Rec16E4PushEPKS0_
   WHAT IT DOES: The same for the 16 byte records. */
template <class T> void Queue<T>::Push(const T *in)
{
    buf[tail] = *in;
    tail++;
    if (tail >= size)
        tail = 0;
    if (tail == head) {
        head = tail + 1;
        if (head >= size)
            head = 0;
    }
}

/* @implements 0x083868 us _ZN5QueueI5Rec24E4LastEPS0_
   WHAT IT DOES: Copies the newest record out without removing it; returns -1 when the queue
   is empty, 1 otherwise. */
/* @implements 0x0838e4 us _ZN5QueueI5Rec16E4LastEPS0_
   WHAT IT DOES: The same for the 16 byte records. */
template <class T> int Queue<T>::Last(T *out)
{
    int i = tail - 1;
    if (i < 0)
        i = size - 1;
    *out = buf[i];
    return tail == head ? -1 : 1;
}

/* @implements 0x08353c us _ZN5QueueI5Rec24E6CreateEi
   WHAT IT DOES: Allocates a queue of n 24 byte records and empties it. */
/* @implements 0x08358c us _ZN5QueueI5Rec16E6CreateEi
   WHAT IT DOES: Allocates a queue of n 16 byte records and empties it. */

/* Queue records: the sender's id and the packet data. */
struct Rec32 {
    int id;
    char data[28];
};
struct Rec24 {
    int id;
    char data[20];
};
struct Rec16 {
    int id;
    char data[12];
};

/* A packet's data type: its queue, the channel (the low byte of the header) and its size. */
struct PacketInfo {
    int type;
    int ch;
    int size;
};

/* A four byte sender stamp. */
struct Stamp {
    char c[4];
};

class GamePacketProc {
public:
    GamePacketProc();
    ~GamePacketProc();
    void Init();
    void Clear();
    void Put(PacketInfo info, int id, const void *src);
    int Get(PacketInfo info, int *id, void *dst);
    int GetLast(PacketInfo info, int *id, void *dst);
    void Receive(int from, int header, char *data, int size);

    int m0;
    Queue<Rec32> ch[8];
    Queue<Rec24> q24;
    Queue<Rec16> q16;
};


/* @implements 0x082e34 us f_082e34
   WHAT IT DOES: The name of a data type for the error text (empty in this build). */
const char *f_082e34(int type)
{
    return "";
}

/* @implements 0x082e40 us f_082e40
   WHAT IT DOES: The name of a channel (empty in this build). */
const char *f_082e40(int ch)
{
    return "";
}

/* @implements 0x082e4c us f_082e4c
   WHAT IT DOES: Debug dump of the queues (compiled out). */
void f_082e4c()
{
}

/* @implements 0x082e54 us f_082e54
   WHAT IT DOES: Debug dump of a packet (compiled out). */
void f_082e54()
{
}

/* @implements 0x082e5c us _ZN14GamePacketProcC2Ev
   WHAT IT DOES: Base object constructor: sets up the queues. */
/* @implements 0x082e78 us _ZN14GamePacketProcC1Ev
   WHAT IT DOES: Complete object constructor: sets up the queues. */
GamePacketProc::GamePacketProc()
{
    Init();
}

/* @implements 0x082e94 us _ZN14GamePacketProc4InitEv
   WHAT IT DOES: Allocates four records for each channel queue, three for the 24 byte queue and
   twenty for the 16 byte queue, and clears the counter. */
void GamePacketProc::Init()
{
    int i;
    for (i = 0; i < 8; i++)
        ch[i].Create(4);
    q24.Create(3);
    q16.Create(20);
    m0 = 0;
}

/* @implements 0x082f00 us _ZN14GamePacketProcD2Ev
   WHAT IT DOES: Base object destructor: empties the queues. */
/* @implements 0x082f1c us _ZN14GamePacketProcD1Ev
   WHAT IT DOES: Complete object destructor: empties the queues. */
GamePacketProc::~GamePacketProc()
{
    Clear();
}

/* @implements 0x082f38 us _ZN14GamePacketProc5ClearEv
   WHAT IT DOES: Discards every queued record. */
void GamePacketProc::Clear()
{
    int i;
    for (i = 0; i < 8; i++) {
        Rec32 r;
        int ret;
        do
            ret = ch[i].Pop(&r);
        while (ret != -1);
    }
    {
        Rec24 r;
        int ret;
        do
            ret = q24.Pop(&r);
        while (ret != -1);
    }
    {
        Rec16 r;
        int ret;
        do
            ret = q16.Pop(&r);
        while (ret != -1);
    }
}

/* @implements 0x082fec us f_082fec
   WHAT IT DOES: Decodes a packet header: the data type from bits 8 to 15 selects the queue and
   size from the table, the low byte is the channel. */
void f_082fec(int header, PacketInfo *info)
{
    /* The data types: queue, channel and data size. */
    static const PacketInfo D_1a75c4[4] = {
        {0, 0, 28},
        {1, 0, 17},
        {2, 0, 4},
        {3, 0, 12},
    };
    const PacketInfo *t = &D_1a75c4[(header & 0xff00) >> 8];
    info->type = t->type;
    info->ch = header & 0xff;
    info->size = t->size;
}

/* @implements 0x083028 us _ZN14GamePacketProc3PutE10PacketInfoiPKv
   WHAT IT DOES: Queues a packet's data with its sender id on the queue its type selects
   (a channel queue for type 0, valid channels only). */
void GamePacketProc::Put(PacketInfo info, int id, const void *src)
{
    switch (info.type) {
    case 0: {
        Rec32 r;
        memcpy(r.data, src, info.size);
        r.id = id;
        if ((unsigned)info.ch < 8)
            ch[info.ch].Push(&r);
        break;
    }
    case 1: {
        Rec24 r;
        memcpy(r.data, src, info.size);
        r.id = id;
        q24.Push(&r);
        break;
    }
    case 3: {
        Rec16 r;
        memcpy(r.data, src, info.size);
        r.id = id;
        q16.Push(&r);
        break;
    }
    }
}

/* @draft 0x083110 us _ZN14GamePacketProc3GetE10PacketInfoPiPv
   REMAINING DIFFERENCE: the result and the id pointer swap saved registers (retail keeps
   id in s2 and the result in s1). Per-case result locals, a break/return layout and an
   inline helper were tried.
   WHAT IT DOES: Takes the oldest record of a type's queue, copying its data out and its
   sender id to *id; returns -1 when there is none. */
int GamePacketProc::Get(PacketInfo info, int *id, void *dst)
{
    int ret;
    switch (info.type) {
    case 0:
        if ((unsigned)info.ch >= 8)
            return -1;
        {
            Rec32 r;
            ret = ch[info.ch].Pop(&r);
            memcpy(dst, r.data, info.size);
            *id = r.id;
        }
        break;
    case 1: {
        Rec24 r;
        ret = q24.Pop(&r);
        memcpy(dst, r.data, info.size);
        *id = r.id;
        break;
    }
    case 3: {
        Rec16 r;
        ret = q16.Pop(&r);
        memcpy(dst, r.data, info.size);
        *id = r.id;
        break;
    }
    default:
        return -1;
    }
    return ret;
}

/* @draft 0x08321c us _ZN14GamePacketProc7GetLastE10PacketInfoPiPv
   REMAINING DIFFERENCE: the same saved register swap as Get.
   WHAT IT DOES: The same as above for the newest record, which stays queued. */
int GamePacketProc::GetLast(PacketInfo info, int *id, void *dst)
{
    int ret;
    switch (info.type) {
    case 0:
        if ((unsigned)info.ch >= 8)
            return -1;
        {
            Rec32 r;
            ret = ch[info.ch].Last(&r);
            memcpy(dst, r.data, info.size);
            *id = r.id;
        }
        break;
    case 1: {
        Rec24 r;
        ret = q24.Last(&r);
        memcpy(dst, r.data, info.size);
        *id = r.id;
        break;
    }
    case 3: {
        Rec16 r;
        ret = q16.Last(&r);
        memcpy(dst, r.data, info.size);
        *id = r.id;
        break;
    }
    default:
        return -1;
    }
    return ret;
}

/* A reply to a type 2 packet: the sender's stamp and a time 50 earlier. */
struct Reply {
    Stamp stamp;
    int time;
};

/* @draft 0x083328 us _ZN14GamePacketProc7ReceiveEiiPci
   REMAINING DIFFERENCE: the stamp byte copies take their registers in another order (retail
   v0, v1, t0, t1), and for type 2 retail computes the time before copying the stamp and
   stores it in the send call's slot. Named char fields, a byte-wise copy method and a
   pointer local were tried.
   WHAT IT DOES: Handles a received packet. A packet shorter than its type's size is reported
   and dropped. Type 2 is answered at once with a type 3 packet carrying the sender's stamp and
   the counter less 50 (not below zero); type 3 has the local stamp written into it; every
   other packet is queued. */
void GamePacketProc::Receive(int from, int header, char *data, int size)
{
    PacketInfo info;
    f_082fec(header, &info);
    if (size < info.size) {
        iprintf("GamePacketProc::ERROR: size=%d, ndh.DataType=%d(%s), DataSize=%d\n", size,
                info.type, f_082e34(info.type), info.size);
        return;
    }
    if (info.type == 2) {
        PacketInfo r;
        Reply rep;
        int t;
        f_082fec(0x300, &r);
        t = m0 - 50;
        if (t < 0)
            t = 0;
        rep.stamp = *(Stamp *)data;
        rep.time = t;
        f_086a60(D_241810, from, 0x300, &rep, r.size);
    } else if (info.type == 3) {
        Stamp *d = (Stamp *)(data + 8);
        *d = *(Stamp *)this;
        Put(info, 0, data);
    } else {
        Put(info, 0, data);
    }
}

GamePacketProc D_241760;

/* @implements 0x083480 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global packet processor at start up and destroys it at exit. */
/* @implements 0x0834fc us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
/* @implements 0x08351c us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */
