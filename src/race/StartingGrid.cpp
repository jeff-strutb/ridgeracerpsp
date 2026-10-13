/* The starting grid manager (retail 0x083990 to 0x083edc): during a wireless race entry, the
   host hands out one entry number per console that joins and, once everyone is in, deals the
   starting grid positions out in a random order. The manager is a small byte record: the
   number of places, a taken flag per entry, a flag per entry for "this is my own console"
   and the grid position dealt to each entry. The record travels between consoles as a
   17-byte message (the count, the taken flags and the positions). Before it (0x083990 to
   0x083a9c) sit two methods of the packet processor's ring queue for 32-byte records. */

#include <stdlib.h>

extern "C" {
int f_126f1c(const char *fmt, ...);
unsigned int sceKernelGetSystemTimeLow(void);
}

/* The game packet processor's ring queue (see src/system/GamePacketProc.cpp), whose 32-byte
   record instantiation's Pop and Last are emitted here. */
template <class T> struct Queue {
    int head;
    int tail;
    int size;
    T *buf;

    int Pop(T *out);
    int Last(T *out);
};

/* A channel record: the sender's id and the packet data. */
struct Rec32 {
    int id;
    char data[28];
};

/* @implements 0x083990 us _ZN5QueueI5Rec32E3PopEPS0_
   WHAT IT DOES: Takes the oldest record out of the queue into out. Returns 1, or -1 when
   the queue is empty. */
template <class T> int Queue<T>::Pop(T *out)
{
    int r = -1;
    if (tail != head) {
        r = 1;
        *out = buf[head];
        if (++head >= size)
            head = 0;
    }
    return r;
}

/* @implements 0x083a18 us _ZN5QueueI5Rec32E4LastEPS0_
   WHAT IT DOES: Copies the newest record in the queue into out without taking it. Returns -1
   when the queue is empty (the copy is then of a stale slot), otherwise 1. */
template <class T> int Queue<T>::Last(T *out)
{
    int i = tail - 1;
    if (i < 0)
        i = size - 1;
    *out = buf[i];
    return tail == head ? -1 : 1;
}

template int Queue<Rec32>::Pop(Rec32 *out);
template int Queue<Rec32>::Last(Rec32 *out);

struct Flags8 {
    signed char f[8];
};

/* The record sent to the other consoles. */
struct GridMsg {
    signed char count;
    Flags8 taken;
    Flags8 pos;
};

class CStartingGridManager {
public:
    CStartingGridManager();
    ~CStartingGridManager();

    void f_083af4(int n);
    int f_083b5c();
    int f_083bd4(int id);
    void f_083c18();
    int f_083ce4();
    int f_083d18();
    void f_083d20(GridMsg *d);
    void f_083dac(GridMsg *s);
    void f_083e38();
    void f_083e58(unsigned int id);
    int f_083e98();

    signed char count;
    signed char taken[8];
    signed char mine[8];
    signed char pos[8];
};

/* @implements 0x083a9c us _ZN20CStartingGridManagerC2Ev
   WHAT IT DOES: Seeds the random numbers from the system clock. */
/* @implements 0x083ac0 us _ZN20CStartingGridManagerC1Ev
   WHAT IT DOES: The complete-object copy of the constructor above. */
CStartingGridManager::CStartingGridManager()
{
    srand(sceKernelGetSystemTimeLow());
}

/* @implements 0x083ae4 us _ZN20CStartingGridManagerD2Ev
   WHAT IT DOES: Nothing to release. */
/* @implements 0x083aec us _ZN20CStartingGridManagerD1Ev
   WHAT IT DOES: The complete-object copy of the destructor above. */
CStartingGridManager::~CStartingGridManager()
{
}

/* @implements 0x083af4 us f_083af4
   WHAT IT DOES: Starts a new entry for n places (at most 8): no entry is taken and no grid
   position is dealt. */
void CStartingGridManager::f_083af4(int n)
{
    count = n;
    if (count >= 9) {
        f_126f1c("CStartingGridManager:Err in Begin()");
        count = 8;
    }
    for (int i = 0; i < 8; i++) {
        taken[i] = 0;
        pos[i] = -1;
    }
}

/* @implements 0x083b5c us f_083b5c
   WHAT IT DOES: Hands out the first free entry number and marks it taken. Returns -1 when
   all places are taken. */
int CStartingGridManager::f_083b5c()
{
    int n = f_083ce4();
    if ((n >= count) | (n >= 9))
        return -1;
    for (int i = 0; i < 8; i++) {
        if (taken[i] == 0) {
            taken[i] = 1;
            return i;
        }
    }
    return -1;
}

/* @implements 0x083bd4 us f_083bd4
   WHAT IT DOES: Takes the given entry number. Returns it, or -1 (with an error message) when
   it was taken already. */
int CStartingGridManager::f_083bd4(int id)
{
    if (taken[id] == 0) {
        taken[id] = 1;
    } else {
        f_126f1c("CANNOT GET STARTING GRID ID");
        id = -1;
    }
    return id;
}

/* @implements 0x083c18 us f_083c18
   WHAT IT DOES: Deals the grid positions 1, 2, 3... to the taken entries in a random order:
   each round picks one of the entries still without a position at random. As in retail, a
   round that finds no such entry stores its position one byte past the array. */
void CStartingGridManager::f_083c18()
{
    int n = f_083ce4();
    int k = 0;
    do {
        int r = rand() % (n - k);
        int i, c;
        k++;
        for (i = 0, c = 0; i < 8; i++) {
            if (taken[i] == 1 && pos[i] == -1) {
                if (r == c)
                    break;
                c++;
            }
        }
        pos[i] = k;
    } while (n - k > 0);
}

/* @implements 0x083ce4 us f_083ce4
   WHAT IT DOES: Counts the taken entries. */
int CStartingGridManager::f_083ce4()
{
    int n = 0;
    for (int i = 0; i < 8; i++)
        if (taken[i] == 1)
            n++;
    return n;
}

/* @implements 0x083d18 us f_083d18
   WHAT IT DOES: The size of the message the manager is sent as. */
int CStartingGridManager::f_083d18()
{
    return 17;
}

/* @implements 0x083d20 us f_083d20
   WHAT IT DOES: Writes the message: the place count, the taken flags and the positions. */
void CStartingGridManager::f_083d20(GridMsg *d)
{
    d->count = count;
    *(Flags8 *)d->taken.f = *(Flags8 *)taken;
    *(Flags8 *)d->pos.f = *(Flags8 *)pos;
}

/* @implements 0x083dac us f_083dac
   WHAT IT DOES: Reads a received message back into the manager. */
void CStartingGridManager::f_083dac(GridMsg *s)
{
    count = s->count;
    *(Flags8 *)taken = s->taken;
    *(Flags8 *)pos = s->pos;
}

/* @implements 0x083e38 us f_083e38
   WHAT IT DOES: Clears the "my own console" flags. */
void CStartingGridManager::f_083e38()
{
    for (int i = 0; i < 8; i++)
        mine[i] = 0;
}

/* @implements 0x083e58 us f_083e58
   WHAT IT DOES: Marks an entry number as this console's own (an error message when it is out
   of range). */
void CStartingGridManager::f_083e58(unsigned int id)
{
    if (id < 8)
        mine[id] = 1;
    else
        f_126f1c("CStartingGridManager::CheckMyID Error");
}

/* @implements 0x083e98 us f_083e98
   WHAT IT DOES: Finds the first taken entry that is not this console's own and marks it as
   own (the flag is copied from the taken flag). Returns its number, or -1. */
int CStartingGridManager::f_083e98()
{
    for (int i = 0; i < 8; i++) {
        int t = taken[i];
        if (t == 1 && mine[i] == 0) {
            mine[i] = t;
            return i;
        }
    }
    return -1;
}
