/* The race packet object file (retail 0x083edc to 0x085344): the messages consoles exchange
   during a wireless race. A car's state is packed into a 28-byte channel packet (position
   and speed as fixed point bit fields, the heading as 16-bit angles, the input flags, and
   a checksum) and unpacked on the other side; the starting grid travels as a type 1 packet,
   timing as types 2 and 3. Packets are sent through the network session (D_241810) and read
   back from the game packet processor's queues (D_241760). After them come the car state
   copies between the race and the packets, and the smoothing of a remote car towards the
   last state received. */

extern "C" {
void f_09b070(float *out, const void *rot, int n);
}

/* A packet's data type: its queue, the channel and its size (see GamePacketProc.cpp). */
struct PacketInfo {
    int type;
    int ch;
    int size;
};

/* A packet as sent: the header word (the data type in bits 8 to 15, the channel in the
   low byte) and the data. */
struct Packet {
    int header;
    char data[28];
};

extern "C" void f_082fec(int header, PacketInfo *info);

/* The game packet processor (D_241760) and its Get and GetLast. */
struct GamePacketProc;
extern GamePacketProc D_241760;
extern "C" int f_083110(GamePacketProc *p, PacketInfo info, int *id, void *dst);
extern "C" int f_08321c(GamePacketProc *p, PacketInfo info, int *id, void *dst);

/* The network session (D_241810): sends a packet to an address. */
struct NetSession {
    char m0[96];
    char self[8];
    void f_086a60(const char *to, int header, const void *data, int size);
};
extern NetSession D_241810;

/* The broadcast address. */
extern char D_1d3d1c[];

class CStartingGridManager {
public:
    int f_083d20(char *d);
    void f_083dac(char *s);
};

/* A position or velocity vector, and an orientation (a type of its own, so copies of the
   two kinds may be interleaved). */
struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));
struct Rot4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

/* Vector arithmetic on positions; the results are points (w = 1). */
static inline Vec4 operator*(float t, const Vec4 &v)
{
    Vec4 r;
    r.x = t * v.x;
    r.y = t * v.y;
    r.z = t * v.z;
    r.w = 1.0f;
    return r;
}
static inline Vec4 operator/(const Vec4 &v, float d)
{
    Vec4 r;
    r.x = v.x / d;
    r.y = v.y / d;
    r.z = v.z / d;
    r.w = 1.0f;
    return r;
}
static inline Vec4 operator+(const Vec4 &p, const Vec4 &v)
{
    Vec4 r;
    r.x = p.x + v.x;
    r.y = p.y + v.y;
    r.z = p.z + v.z;
    r.w = 1.0f;
    return r;
}

/* Four bytes copied as one block. */
struct Bytes4 {
    char b[4];
};

/* Writes the sum of n words as four bytes. */
static inline void PutSum(char *d, const int *w, unsigned int n)
{
    int sum = 0;
    for (unsigned int i = 0; i < 6; i++)
        sum += w[i];
    *(Bytes4 *)d = *(Bytes4 *)&sum;
}

/* The parts of a race car read and written here. */
struct CCar {
    char m0[144];
    Vec4 pos;
    Vec4 vel;
    char m176[32];
    Rot4 rot;
    char m224[1520];
    float m1744;
    float m1748;
    char m1752[84];
    float m1836;
    char m1840[256];
    float m2096;
    int m2100;
    int m2104;
    int m2108;
    int m2112;
    int m2116;
    int m2120;
};

/* A car's state as exchanged between consoles. */
struct CarState {
    float m0;
    float m4;
    float m8;
    float m12;
    char m16[16];
    int m32;
    bool m36;
    bool m37;
    bool m38;
    bool m39;
    bool m40;
    bool m41;
    bool m42;
    Vec4 pos;
    Vec4 vel;
    Rot4 rot;

    void Set(const Vec4 &p, const Vec4 &v, const Rot4 &r)
    {
        pos = p;
        rot = r;
        vel = v;
    }
    void Get(Vec4 &p, Vec4 &v, Rot4 &r)
    {
        p = pos;
        r = rot;
        v = vel;
    }
    /* A point one velocity step on from p. */
    Vec4 Step(const Vec4 &p)
    {
        Vec4 r;
        r.x = p.x + vel.x;
        r.y = p.y + vel.y;
        r.z = p.z + vel.z;
        r.w = 1.0f;
        return r;
    }
    void f_0849a4(CCar *car);
    void f_084ad0(CCar *car);
    void f_084bd8(int t);
    void f_084c88();
};

class CNetRacePacket {
public:
    void f_083edc(int t);
    int f_083f1c(int *a, int *b, int *c);
    void f_083fa8(unsigned int ch, CarState *car, char *b);
    int f_084048(unsigned int ch, CarState *car, char *b);
    void f_0840f4(CStartingGridManager *g);
    int f_084150(CStartingGridManager *g);
    void f_0841e0(CarState *st, char *id, char *out);
    int f_084580(char *in, CarState *car, char *b);
    int f_084968(CStartingGridManager *g, char *out);
    void f_084988(char *in, CStartingGridManager *g);
};

/* @implements 0x083edc us f_083edc
   WHAT IT DOES: Sends a type 2 (timing request) packet carrying t to this console's own
   session address. */
void CNetRacePacket::f_083edc(int t)
{
    PacketInfo info;
    f_082fec(0x200, &info);
    D_241810.f_086a60(D_241810.self, 0x200, &t, info.size);
}

/* @implements 0x083f1c us f_083f1c
   WHAT IT DOES: Takes the oldest type 3 (timing reply) packet: its three words go to a, b
   and c. Returns -1 when there is none. */
int CNetRacePacket::f_083f1c(int *a, int *b, int *c)
{
    PacketInfo info;
    struct {
        int id;
        int d[3];
    } rec;
    f_082fec(0x300, &info);
    int r = f_083110(&D_241760, info, &rec.id, rec.d);
    if (r == -1)
        return -1;
    *a = rec.d[0];
    *b = rec.d[1];
    *c = rec.d[2];
    return r;
}

/* @implements 0x083fa8 us f_083fa8
   WHAT IT DOES: Packs a car's state and broadcasts it on channel ch (0 to 7). */
void CNetRacePacket::f_083fa8(unsigned int ch, CarState *car, char *b)
{
    Packet pkt;
    PacketInfo info;
    if (ch < 8) {
        pkt.header = ch & 0xff;
        f_082fec(pkt.header, &info);
        f_0841e0(car, b, pkt.data);
        D_241810.f_086a60(D_1d3d1c, pkt.header, pkt.data, sizeof pkt.data);
    }
}

/* @implements 0x084048 us f_084048
   WHAT IT DOES: Unpacks the newest car state received on channel ch. Returns the unpack's
   result (0 when the checksum agrees), or -1 when there is no packet. */
int CNetRacePacket::f_084048(unsigned int ch, CarState *car, char *b)
{
    PacketInfo info;
    struct {
        int id;
        char d[28];
    } rec;
    if (ch >= 8)
        return -1;
    f_082fec(ch & 0xff, &info);
    if (f_08321c(&D_241760, info, &rec.id, rec.d) == -1)
        return -1;
    return f_084580(rec.d, car, b);
}

/* @implements 0x0840f4 us f_0840f4
   WHAT IT DOES: Broadcasts the starting grid as a type 1 packet. */
void CNetRacePacket::f_0840f4(CStartingGridManager *g)
{
    Packet pkt;
    PacketInfo info;
    pkt.header = 0x100;
    f_084968(g, pkt.data);
    f_082fec(pkt.header, &info);
    D_241810.f_086a60(D_1d3d1c, pkt.header, pkt.data, info.size);
}

/* @implements 0x084150 us f_084150
   WHAT IT DOES: Takes the oldest starting grid packet into g. Returns -1 when there is
   none. */
int CNetRacePacket::f_084150(CStartingGridManager *g)
{
    PacketInfo info;
    struct {
        int id;
        char d[28];
    } rec;
    f_082fec(0x100, &info);
    int r = f_083110(&D_241760, info, &rec.id, rec.d);
    if (r == -1)
        return -1;
    f_084988(rec.d, g);
    return r;
}

/* @draft 0x0841e0 us f_0841e0
   WHAT IT DOES: Packs a car state into a 28-byte packet: the sender id (4 bytes); the
   position (x and z offset by 2^21 in 22 bits each, y offset by 120000 and halved in 18
   bits) with two flags (8 bytes); the velocity (x and z times 16 offset by 32768 in 16 bits,
   y times 16 offset by 2048 in 12 bits) with four flags (6 bytes); the orientation as three
   16-bit angles (6 bytes); and the sum of the first 24 bytes as words (4 bytes).
   Remaining differences: retail keeps the 2^21 constant's high half in a1 and the first
   flag pair in a0 (this source swaps them), and its checksum loop compares against 6 held
   in a register (li t2,6 / sltu) where this source gets sltiu; a local, an inline helper's
   parameter and a reassigned variable for the bound all fold to the immediate. */
void CNetRacePacket::f_0841e0(CarState *st, char *id, char *out)
{
    char *p = out;
    *(Bytes4 *)p = *(Bytes4 *)id;
    p += 4;
    int fl = (st->m36 << 1) | st->m37;
    unsigned int x = (unsigned int)(st->pos.x + 2097152.0f);
    unsigned int z = (unsigned int)(st->pos.z + 2097152.0f);
    unsigned int y = (unsigned int)((st->pos.y + 120000.0f) * 0.5f);
    p[0] = x;
    p[1] = x >> 8;
    p[2] = ((x >> 16) & 0x3f) | ((z & 3) << 6);
    p[3] = z >> 2;
    p[4] = z >> 10;
    p[5] = ((z >> 18) & 0xf) | ((y & 0xf) << 4);
    p[6] = y >> 4;
    p[7] = ((y >> 12) & 0x3f) | ((fl & 3) << 6);

    p = out + 12;
    fl = (st->m38 << 3) | (st->m39 << 2) | (st->m40 << 1) | st->m41;
    unsigned int vx = (unsigned int)(st->vel.x * 16.0f + 32768.0f);
    unsigned int vz = (unsigned int)(st->vel.z * 16.0f + 32768.0f);
    unsigned int vy = (unsigned int)(st->vel.y * 16.0f + 2048.0f);
    p[0] = vx;
    p[1] = vx >> 8;
    p[2] = vz;
    p[3] = vz >> 8;
    p[4] = vy;
    p[5] = ((vy & 0xf00) >> 8) | ((fl & 0xf) << 4);

    p = out + 18;
    float a[3];
    f_09b070(a, &st->rot, 4);
    unsigned int ax = (short)(a[0] * 10430.378f);
    unsigned int ay = (short)(a[1] * 10430.378f);
    unsigned int az = (short)(a[2] * 10430.378f);
    p[0] = ax;
    p[1] = ax >> 8;
    p[2] = ay;
    p[3] = ay >> 8;
    p[4] = az;
    p[5] = az >> 8;

    p = out + 24;
    int sum = 0;
    for (unsigned int i = 0; i < 6; i++)
        sum += ((int *)out)[i];
    *(Bytes4 *)p = *(Bytes4 *)&sum;
}

/* @implements 0x084968 us f_084968
   WHAT IT DOES: Writes the starting grid's message. (Declared here as returning the copy's
   int, which the caller ignores; the void spelling changes the caller's schedule.) */
int CNetRacePacket::f_084968(CStartingGridManager *g, char *out)
{
    return g->f_083d20(out);
}

/* @implements 0x084988 us f_084988
   WHAT IT DOES: Reads a starting grid message into g. */
void CNetRacePacket::f_084988(char *in, CStartingGridManager *g)
{
    g->f_083dac(in);
}

/* @implements 0x0849a4 us f_0849a4
   WHAT IT DOES: Takes a car's state for sending: position, velocity, orientation, and six
   flags from its controls (whether each is engaged). */
void CarState::f_0849a4(CCar *car)
{
    Set(car->pos, car->vel, car->rot);
    if (car->m2108 == 1)
        m36 = 1;
    else
        m36 = 0;
    if (car->m2096 < 0.01f)
        m37 = 0;
    else
        m37 = 1;
    if (car->m2104)
        m38 = 1;
    else
        m38 = 0;
    if (car->m1744 < 0.01f)
        m39 = 0;
    else
        m39 = 1;
    if (car->m1748 < 0.01f)
        m40 = 0;
    else
        m40 = 1;
    if (car->m2120)
        m41 = 1;
    else
        m41 = 0;
}

/* @implements 0x084ad0 us f_084ad0
   WHAT IT DOES: Applies a received state to a car: position, velocity, orientation, and the
   controls from the six flags. */
void CarState::f_084ad0(CCar *car)
{
    Get(car->pos, car->vel, car->rot);
    if (m36)
        car->m1836 = 100.0f;
    else
        car->m1836 = 0;
    if (m37)
        car->m2096 = 1.0f;
    else
        car->m2096 = 0;
    if (m38)
        car->m2104 = 1;
    else
        car->m2104 = 0;
    if (m39)
        car->m1744 = 1.0f;
    else
        car->m1744 = 0;
    if (m40)
        car->m1748 = 1.0f;
    else
        car->m1748 = 0;
    if (m41)
        car->m2120 = 1;
    else
        car->m2120 = 0;
}

/* @implements 0x084bd8 us f_084bd8
   WHAT IT DOES: Moves the state's position ahead by the velocity over n frames (the velocity
   is per 16 units of time, 50 frames to the unit; a negative n counts as 0), and clears the
   frame counter. */
void CarState::f_084bd8(int n)
{
    if (n < 0)
        n = 0;
    float t = n / 50.0f;
    m32 = 0;
    Vec4 p;
    p = pos + t * vel / 16.0f;
    pos = p;
}

/* @implements 0x084c88 us f_084c88
   WHAT IT DOES: Moves the state's position on by one step of its velocity. */
void CarState::f_084c88()
{
    pos = Step(pos);
}

/* @implements 0x085320 us f_085320
   WHAT IT DOES: Returns an empty name (debug text compiled out). */
const char *f_085320()
{
    return "";
}

/* @implements 0x08532c us f_08532c
   WHAT IT DOES: Returns an empty name (debug text compiled out). */
const char *f_08532c()
{
    return "";
}

/* @implements 0x085338 us f_085338
   WHAT IT DOES: Returns an empty name (debug text compiled out). */
const char *f_085338()
{
    return "";
}
