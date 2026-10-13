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

struct CarState;
struct CarPacket;

class CNetRacePacket {
public:
    void f_083edc(int t);
    int f_083f1c(int *a, int *b, int *c);
    void f_083fa8(unsigned int ch, CarState *car, void *b);
    int f_084048(unsigned int ch, CarState *car, void *b);
    void f_0840f4(CStartingGridManager *g);
    int f_084150(CStartingGridManager *g);
    void f_0841e0(CarState *car, void *b, char *out);
    int f_084580(char *in, CarState *car, void *b);
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
void CNetRacePacket::f_083fa8(unsigned int ch, CarState *car, void *b)
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
int CNetRacePacket::f_084048(unsigned int ch, CarState *car, void *b)
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
