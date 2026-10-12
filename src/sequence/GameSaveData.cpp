/* The saved game and the memory stick requests (retail 0x01908c to 0x01c1e4). The game's
   settings, records and progress live in one global object, Sequence::CGameSaveData, which
   writes itself into a byte stream and reads itself back; a replay or ghost is written the same
   way by Sequence::CReplaySaveData. The stream signs what its objects wrote with a CRC-32. The
   memory stick object starts the system save and load dialogs with such a stream and turns
   their outcome into the flags the menus show. The object file ends with its static
   constructor and, emitted out of line, the saved game's assignment and size. */

#include <stdio.h>

extern "C" {
int sceRtcGetCurrentTick(unsigned long long *tick);
}

int f_01c260(void);
const char *f_01c26c(const char *name);
void f_00d354(void *log, int level, const char *fmt, ...);
extern "C" void f_00600c(void);
int f_00222c(const char *name, const char *package);
void *f_005c34(void *loader, const char *name);
void f_01c7a4(void *sound, int channel, int volume);

extern char D_245178[];
extern char D_1dd6b0[];
extern char D_23bb4c[];
extern const char *D_1d1654[];
extern const char *D_1d1670[];
extern const char *D_1d168c[];
extern const char *D_1d16a8[];
extern const char *D_1d16c4[];
extern char D_1d16e0[][8];

/* A file of the data packages: its size is the word at +12. */
struct FileEntry {
    int m0[3];
    int size;
    int m16[2];
};
extern FileEntry D_1c0614[];

/* A data package: one archive file from the disc, whose entries are looked up by name. */
class CPackage {
public:
    void *f_002acc(const char *name);
};
extern CPackage D_2301d4;

/* The system save data dialog. */
class CSaveData {
public:
    void f_00612c();
    void f_0061a0(void *buf, int bufSize, int size);
    void f_0061b0(const char *title, const char *savedataTitle, const char *detail);
    void f_006260(void *buf, int size);
    void f_006274(void *buf, int size);
    void f_006288(void *buf, int size);
    void f_00629c();
    void f_006394(int n);
    void f_0063b4(int n);
    void f_0063d8(int n);
    void f_0063fc(int n);
    void f_006420(int first, int count);
    void f_0064dc(int first, int count);
    void f_006658();
    int f_006664();
    int f_006680();
    void f_006728();
    char m0[1480];
    int result;
};
extern CSaveData D_1e38f4;

/* The pad controller, for its button layout. */
class CController {
public:
    void f_042e1c(int layout);
};
extern CController D_1d8910[];

/* The game mode job, for its random number generator. */
struct GameModeJobView {
    unsigned int Rand()
    {
        seed = seed * 0x19660d + 0x3c6ef35f;
        return seed;
    }
    int m0[4];
    unsigned int seed;
};
extern GameModeJobView D_1e8ec4;

/* The two game state words the race uses. */
struct SavedPair {
    int a;
    int b;
};
extern SavedPair D_1d1a94;

/* @implements 0x01908c us f_01908c
   WHAT IT DOES: Returns the CRC-32 of a block of bytes, building the lookup table on the
   stack first. */
unsigned int f_01908c(const unsigned char *p, int n)
{
    unsigned int table[256];
    unsigned int i, j, c;

    for (i = 0; i < 256; i++) {
        c = i;
        for (j = 0; j < 8; j++) {
            if (c & 1)
                c = (c >> 1) ^ 0xedb88320;
            else
                c >>= 1;
        }
        table[i] = c;
    }
    c = 0xffffffff;
    while (--n >= 0)
        c = (c >> 8) ^ table[(c & 0xff) ^ *p++];
    return ~c;
}

/* @implements 0x019128 us f_019128
   WHAT IT DOES: Copies four bytes. */
void f_019128(unsigned char *d, const unsigned char *s)
{
    unsigned int i;

    for (i = 0; i < 4; i++)
        *d++ = *s++;
}

/* @implements 0x019150 us f_019150
   WHAT IT DOES: Puts a four byte value into the stream's byte order; on this machine it is
   already in it, so it does nothing. */
void f_019150(void *p)
{
}

/* @implements 0x019158 us f_019158
   WHAT IT DOES: Returns whether two four byte values are equal. */
int f_019158(unsigned char *a, unsigned char *b)
{
    unsigned int i;

    f_019150(a);
    f_019150(b);
    for (i = 0; i < 4; i++) {
        if (*b++ != *a++)
            return 0;
    }
    return 1;
}

class CSaveStream;

namespace System {
/* One object a save stream writes and reads. Size is the number of bytes it writes, Save and
   Load write and read it, the other three give the texts the save dialog shows. */
class CSaveDataBase {
public:
    virtual int Size() = 0;
    virtual int Save(CSaveStream *s) = 0;
    virtual int Load(CSaveStream *s) = 0;
    virtual const char *f_019494();
    virtual const char *Text1() = 0;
    virtual const char *Text2() = 0;
    int version;
    unsigned char *start;
};
}

/* The byte stream a save is written into and read from: a buffer, the read or write position
   and the objects it holds; the first four bytes are the signature of the rest. */
class CSaveStream {
public:
    CSaveStream() { count = 0; }
    ~CSaveStream() { f_019228(); }
    void f_0191c4(int n);
    void f_019228();
    void f_019264(System::CSaveDataBase *item);
    int f_019280();
    void f_0192f8();
    int f_0193a8();
    void Put8(unsigned char v)
    {
        unsigned char *p = cur;
        *p = v;
        cur = p + 1;
    }
    void Put32(unsigned int v)
    {
        Put8(v);
        Put8(v >> 8);
        Put8(v >> 16);
        Put8(v >> 24);
    }
    unsigned char Get8()
    {
        unsigned char v = *cur;
        cur++;
        return v;
    }
    void Get32(int &v)
    {
        v = Get8();
        v |= Get8() << 8;
        v |= Get8() << 16;
        v |= Get8() << 24;
    }
    int size;
    unsigned char *buf;
    unsigned char *cur;
    int count;
    System::CSaveDataBase *items[4];
};

namespace Sequence {
struct Tri {
    int v[3];
};

/* The saved game: settings, records, unlocked items and the player's name. */
class CGameSaveData : public System::CSaveDataBase {
public:
    CGameSaveData();
    virtual int Size() { return 0x3f00; }
    virtual int Save(CSaveStream *s);
    virtual int Load(CSaveStream *s);
    virtual const char *Text1();
    virtual const char *Text2();
    void f_01959c();
    void f_019628();
    void f_0196cc();
    void f_019994(const char *name);

    int m12;
    int m16;
    int m20;
    int m24[336];
    int m1368[336];
    Tri m2712[3][336];
    int m14808;
    int m14812;
    int m14816;
    int m14820;
    int m14824;
    int m14828;
    int m14832;
    int m14836;
    int m14840;
    int m14844;
    int m14848;
    int m14852;
    int m14856;
    int m14860;
    int m14864;
    int m14868;
    int m14872[48];
    int m15064[60];
    int m15304[28];
    int m15416[10];
    int m15456;
    int m15460;
    int m15464;
    int m15468;
    int m15472;
    int m15476;
    int m15480;
    int m15484[48];
    int m15676;
    unsigned int m15680;
    int m15684;
    int m15688;
    int m15692;
    int m15696;
    int m15700;
    int m15704;
    int m15708;
    int m15712;
    char name[8];
    int m15724;
    int m15728;
    int m15732;
    int m15736;
    int m15740;
    int m15744;
    int m15748;
    int m15752;
    bool m15756;
};

/* A replay or ghost: a block of bytes with its size. */
class CReplaySaveData : public System::CSaveDataBase {
public:
    virtual int Size();
    virtual int Save(CSaveStream *s);
    virtual int Load(CSaveStream *s);
    virtual const char *Text1();
    virtual const char *Text2();
    unsigned char *data;
    int size;
    int m20;
};
}

/* The memory stick requests: the last result code, what went wrong, and the stream and
   objects of the request in progress. */
struct MemoryStick {
    int result;
    bool noStick;
    bool full;
    bool missing;
    bool broken;
    CSaveStream *stream;
    Sequence::CGameSaveData *game;
    Sequence::CReplaySaveData *replay;
    unsigned char *replayData;
    int replaySize;
    const char *replayText;
    int loadedSize;

    int f_01a900();
    int f_01a90c();
    void f_01a91c(bool automatic);
    int f_01abf4();
    void f_01ad04(bool automatic);
    int f_01ae50();
    void f_01afa8();
    int f_01b1ac();
    void f_01b284();
    int f_01b3b8();
    void f_01b4e8(int slot);
    int f_01b6fc();
    void f_01b7d4(int slot);
    int f_01b91c();
    void f_01ba4c();
    int f_01ba88();
    void f_01bb3c();
    int f_01bc5c();
};

Sequence::CGameSaveData D_233f70;
Sequence::CGameSaveData D_237d00;
MemoryStick D_23ba90;
Sequence::CReplaySaveData D_23bab4;

/* @implements 0x0191c4 us f_0191c4
   WHAT IT DOES: Gives the stream a cleared buffer of the given size and starts at its
   beginning. */
void CSaveStream::f_0191c4(int n)
{
    size = n;
    buf = new unsigned char[n];
    for (int i = 0; i < size; i++)
        buf[i] = 0;
    cur = buf;
}

/* @implements 0x019228 us f_019228
   WHAT IT DOES: Frees the stream's buffer. */
void CSaveStream::f_019228()
{
    if (buf) {
        delete[] buf;
        buf = 0;
    }
}

/* @implements 0x019264 us f_019264
   WHAT IT DOES: Adds an object to the stream. */
void CSaveStream::f_019264(System::CSaveDataBase *item)
{
    items[count++] = item;
}

/* @implements 0x019280 us f_019280
   WHAT IT DOES: Returns the number of bytes the stream's objects need, with the signature. */
int CSaveStream::f_019280()
{
    int n = 4;

    for (int i = 0; i < count; i++)
        n += items[i]->Size();
    return n;
}

/* @implements 0x0192f8 us f_0192f8
   WHAT IT DOES: Writes every object into the stream after room for the signature, then signs
   what they wrote with its CRC-32. */
void CSaveStream::f_0192f8()
{
    unsigned char *sig = cur;
    unsigned char *body = sig + 4;
    unsigned int crc;

    cur = body;
    for (int i = 0; i < count; i++)
        items[i]->Save(this);
    crc = f_01908c(body, cur - body);
    f_019150(&crc);
    f_019128(sig, (unsigned char *)&crc);
}

/* @implements 0x0193a8 us f_0193a8
   WHAT IT DOES: Reads every object back from the stream and checks the signature. Returns 0,
   or -1 (with a message in the log) when an object's version or the signature is wrong. */
int CSaveStream::f_0193a8()
{
    unsigned char *sig = cur;
    unsigned char *body = sig + 4;
    unsigned int crc;

    cur = body;
    for (int i = 0; i < count; i++) {
        if (items[i]->Load(this)) {
            f_00d354(D_245178, 4, "DataVersion Error!\n");
            return -1;
        }
    }
    crc = f_01908c(body, cur - body);
    if (f_019158((unsigned char *)&crc, sig))
        return 0;
    f_00d354(D_245178, 4, "WholeSignature Error!\n");
    return -1;
}

/* @implements 0x019494 us f_019494
   WHAT IT DOES: Returns the game's title in the console's language, as the save dialog shows
   it. */
const char *System::CSaveDataBase::f_019494()
{
    return D_1d1654[f_01c260()];
}

/* @implements 0x0194c4 us f_0194c4
   WHAT IT DOES: When the game has a saved game, returns whether its state differs from the
   copy taken at the last save or load, byte by byte (that is, whether there is anything new
   to save). */
int f_0194c4(void)
{
    int changed = 0;

    if (D_233f70.m15704) {
        const char *a = (const char *)&D_233f70;
        const char *b = (const char *)&D_237d00;
        for (unsigned int i = 0; i < sizeof(Sequence::CGameSaveData); i++) {
            if (*a++ != *b++)
                return 1;
        }
        changed = 0;
    }
    return changed;
}

/* @implements 0x01951c us _ZN8Sequence13CGameSaveData5Text1
   WHAT IT DOES: Returns the saved game's title for the save dialog, in the console's
   language. */
const char *Sequence::CGameSaveData::Text1()
{
    return D_1d1670[f_01c260()];
}

/* @implements 0x01954c us _ZN8Sequence13CGameSaveData5Text2
   WHAT IT DOES: Returns the saved game's description for the save dialog, in the console's
   language. */
const char *Sequence::CGameSaveData::Text2()
{
    return D_1d16c4[f_01c260()];
}

/* @implements 0x01958c us _ZN8Sequence13CGameSaveDataC1Ev
   WHAT IT DOES: Constructs a saved game. The base object constructor the compiler emits just
   before it, at 0x01957c, is missing from the function map (it is counted as the end of the
   previous function), so it carries no tag. */
Sequence::CGameSaveData::CGameSaveData()
{
}

/* @implements 0x01959c us f_01959c
   WHAT IT DOES: Applies the loaded settings: the button layout, the three sound volumes and
   the two race settings words. */
void Sequence::CGameSaveData::f_01959c()
{
    D_1d8910[0].f_042e1c(m15724 - 1);
    f_01c7a4(D_23bb4c, 1, m15688);
    f_01c7a4(D_23bb4c, 0, m15692);
    f_01c7a4(D_23bb4c, 2, m15696);
    D_1d1a94.a = m12;
    D_1d1a94.b = m16;
}

/* @implements 0x019628 us f_019628
   WHAT IT DOES: Unlocks everything: every car, course, colour and item, and sets every
   course's rank to the highest. */
void Sequence::CGameSaveData::f_019628()
{
    int i;

    m15472 = 1;
    m15676 = 1;
    m15476 = 1;
    for (i = 0; i < 48; i++)
        m14872[i] = 1;
    for (i = 0; i < 60; i++)
        m15064[i] = 1;
    for (i = 0; i < 28; i++)
        m15304[i] = 1;
    for (i = 0; i < 10; i++)
        m15416[i] = 1;
    for (i = 0; i < 48; i++)
        m15484[i] = 10;
}

/* @implements 0x0196cc us f_0196cc
   WHAT IT DOES: Resets the saved game to a new game: default settings and records, nothing
   unlocked but the starting items, a random player name, miles for an English console, and
   the current time and a random number as the save's identity. */
void Sequence::CGameSaveData::f_0196cc()
{
    int i, j;
    unsigned long long tick;

    m20 = 0;
    m12 = 20000;
    m16 = 2000;
    for (i = 0; i < 336; i++) {
        m24[i] = 0x525d7d;
        m1368[i] = 0x1b747f;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 336; j++) {
            m2712[i][j].v[0] = 0x7fffffff;
            m2712[i][j].v[1] = 0x7fffffff;
            m2712[i][j].v[2] = 0x7fffffff;
        }
    }
    m14808 = 1;
    m14812 = 1;
    m14816 = 1;
    m14820 = 1;
    m14824 = 1;
    m14828 = 1;
    m14832 = 1;
    m14836 = 1;
    m14840 = 1;
    m14844 = 1;
    m14848 = 1;
    m14852 = 1;
    m14856 = 1;
    m14860 = 1;
    m14864 = 1;
    m14868 = 0;
    for (i = 0; i < 48; i++)
        m14872[i] = 0;
    for (i = 0; i < 60; i++)
        m15064[i] = 0;
    for (i = 0; i < 28; i++)
        m15304[i] = 0;
    for (i = 0; i < 10; i++)
        m15416[i] = 0;
    m15456 = 1;
    m15460 = 1;
    m15464 = 1;
    m15468 = 1;
    m15472 = 0;
    m15476 = 0;
    m15480 = 1;
    for (i = 0; i < 48; i++)
        m15484[i] = 0;
    m15676 = 0;
    m15680 = 0;
    m15684 = 0;
    m15688 = 100;
    m15692 = 100;
    m15696 = 100;
    m15700 = 0;
    m15704 = 0;
    m15708 = 1;
    m15712 = 1;
    f_019994(D_1d16e0[D_1e8ec4.Rand() % 10]);
    if (f_01c260() == 6)
        m15728 = 1;
    else
        m15728 = 0;
    m15724 = 1;
    m15732 = 0;
    m15736 = 1;
    m15740 = 1;
    m15064[1] = 1;
    m15064[2] = 1;
    m15064[3] = 1;
    m15304[1] = 1;
    m15304[3] = 1;
    m15304[5] = 1;
    m15304[7] = 1;
    m15304[9] = 1;
    m15304[11] = 1;
    sceRtcGetCurrentTick(&tick);
    m15744 = tick >> 32;
    m15748 = tick;
    m15756 = 0;
    m15752 = D_1e8ec4.Rand();
}

/* @implements 0x019994 us f_019994
   WHAT IT DOES: Sets the player's name (seven characters). */
void Sequence::CGameSaveData::f_019994(const char *s)
{
    for (int i = 0; i < 7; i++)
        name[i] = s[i];
    name[7] = 0;
}

/* @implements 0x0199c0 us _ZN8Sequence13CGameSaveData4Save
   WHAT IT DOES: Writes the saved game into the stream, little endian, after its version byte,
   and pads it to its fixed size with zeros. */
int Sequence::CGameSaveData::Save(CSaveStream *s)
{
    int i, j;

    start = s->cur;
    version = 105;
    s->Put8(105);
    s->Put32(m12);
    s->Put32(m16);
    s->Put8(m20);
    for (i = 0; i < 336; i++) {
        s->Put32(m24[i]);
        s->Put32(m1368[i]);
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 336; j++) {
            s->Put32(m2712[i][j].v[0]);
            s->Put32(m2712[i][j].v[1]);
            s->Put32(m2712[i][j].v[2]);
        }
    }
    s->Put8(m14808);
    s->Put8(m14812);
    s->Put8(m14816);
    s->Put8(m14820);
    s->Put8(m14824);
    s->Put8(m14828);
    s->Put8(m14832);
    s->Put8(m14836);
    s->Put8(m14840);
    s->Put8(m14844);
    s->Put8(m14848);
    s->Put8(m14852);
    s->Put8(m14856);
    s->Put8(m14860);
    s->Put8(m14864);
    s->Put32(m14868);
    for (i = 0; i < 48; i++)
        s->Put8(m14872[i]);
    for (i = 0; i < 60; i++)
        s->Put8(m15064[i]);
    for (i = 0; i < 28; i++)
        s->Put8(m15304[i]);
    for (i = 0; i < 10; i++)
        s->Put8(m15416[i]);
    s->Put8(m15456);
    s->Put8(m15460);
    s->Put8(m15464);
    s->Put8(m15468);
    s->Put8(m15472);
    s->Put8(m15476);
    s->Put8(m15480);
    for (i = 0; i < 48; i++)
        s->Put8(m15484[i]);
    s->Put8(m15676);
    s->Put32(m15680);
    s->Put32(m15684);
    s->Put8(m15688);
    s->Put8(m15692);
    s->Put8(m15696);
    s->Put32(m15700);
    s->Put8(m15704);
    s->Put8(m15708);
    s->Put8(m15712);
    for (i = 0; i < 8; i++)
        s->Put8(name[i]);
    s->Put8(m15728);
    s->Put8(m15724);
    s->Put8(m15732);
    s->Put8(m15736);
    s->Put8(m15740);
    s->Put32(m15744);
    s->Put32(m15748);
    s->Put32(m15752);
    for (i = start - s->cur + 0x3f00; i > 0; i--)
        s->Put8(0);
    return 0;
}

/* @implements 0x019e7c us _ZN8Sequence13CGameSaveData4Load
   WHAT IT DOES: Reads the saved game back from the stream. Returns -1 if the version byte is
   not this version's; otherwise skips the padding, clears the one value that must not
   survive a load and sets miles for an English console. */
int Sequence::CGameSaveData::Load(CSaveStream *s)
{
    int i, j;

    start = s->cur;
    version = s->Get8();
    if (version != 105)
        return -1;
    s->Get32(m12);
    s->Get32(m16);
    m20 = s->Get8();
    for (i = 0; i < 336; i++) {
        s->Get32(m24[i]);
        s->Get32(m1368[i]);
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 336; j++) {
            s->Get32(m2712[i][j].v[0]);
            s->Get32(m2712[i][j].v[1]);
            s->Get32(m2712[i][j].v[2]);
        }
    }
    m14808 = s->Get8();
    m14812 = s->Get8();
    m14816 = s->Get8();
    m14820 = s->Get8();
    m14824 = s->Get8();
    m14828 = s->Get8();
    m14832 = s->Get8();
    m14836 = s->Get8();
    m14840 = s->Get8();
    m14844 = s->Get8();
    m14848 = s->Get8();
    m14852 = s->Get8();
    m14856 = s->Get8();
    m14860 = s->Get8();
    m14864 = s->Get8();
    s->Get32(m14868);
    for (i = 0; i < 48; i++)
        m14872[i] = s->Get8();
    for (i = 0; i < 60; i++)
        m15064[i] = s->Get8();
    for (i = 0; i < 28; i++)
        m15304[i] = s->Get8();
    for (i = 0; i < 10; i++)
        m15416[i] = s->Get8();
    m15456 = s->Get8();
    m15460 = s->Get8();
    m15464 = s->Get8();
    m15468 = s->Get8();
    m15472 = s->Get8();
    m15476 = s->Get8();
    m15480 = s->Get8();
    for (i = 0; i < 48; i++)
        m15484[i] = s->Get8();
    m15676 = s->Get8();
    s->Get32((int &)m15680);
    s->Get32(m15684);
    m15688 = s->Get8();
    m15692 = s->Get8();
    m15696 = s->Get8();
    s->Get32(m15700);
    m15704 = s->Get8();
    m15708 = s->Get8();
    m15712 = s->Get8();
    for (i = 0; i < 8; i++)
        name[i] = s->Get8();
    m15728 = s->Get8();
    m15724 = s->Get8();
    m15732 = s->Get8();
    m15736 = s->Get8();
    m15740 = s->Get8();
    s->Get32(m15744);
    s->Get32(m15748);
    s->Get32(m15752);
    s->cur = start + 0x3f00;
    m14868 = 0;
    if (f_01c260() == 6)
        m15728 = 1;
    else
        m15728 = 0;
    return 0;
}

/* @implements 0x01a758 us _ZN8Sequence15CReplaySaveData5Text1
   WHAT IT DOES: Returns the replay's title for the save dialog, in the console's language. */
const char *Sequence::CReplaySaveData::Text1()
{
    return D_1d168c[f_01c260()];
}

/* @implements 0x01a788 us _ZN8Sequence15CReplaySaveData5Text2
   WHAT IT DOES: Returns the replay's description for the save dialog, in the console's
   language. */
const char *Sequence::CReplaySaveData::Text2()
{
    return D_1d16c4[f_01c260()];
}

/* @implements 0x01a7b8 us _ZN8Sequence15CReplaySaveData4Size
   WHAT IT DOES: Returns the bytes a replay writes: its version, its size and its data. */
int Sequence::CReplaySaveData::Size()
{
    return size + 5;
}

/* @implements 0x01a7c4 us _ZN8Sequence15CReplaySaveData4Save
   WHAT IT DOES: Writes the replay into the stream: its version byte, its size and its
   bytes. */
int Sequence::CReplaySaveData::Save(CSaveStream *s)
{
    start = s->cur;
    s->Put8(104);
    s->Put32(size);
    for (int i = 0; i < size; i++)
        s->Put8(data[i]);
    return 0;
}

/* @implements 0x01a840 us _ZN8Sequence15CReplaySaveData4Load
   WHAT IT DOES: Reads a replay back from the stream into its buffer. Returns -1 if the version
   byte is not a replay's. */
int Sequence::CReplaySaveData::Load(CSaveStream *s)
{
    start = s->cur;
    version = s->Get8();
    if (version != 104)
        return -1;
    s->Get32(size);
    for (int i = 0; i < size; i++)
        data[i] = s->Get8();
    return 0;
}

/* @implements 0x01a900 us f_01a900
   WHAT IT DOES: Returns whether the last request succeeded. */
int MemoryStick::f_01a900()
{
    return result == 0;
}

/* @implements 0x01a90c us f_01a90c
   WHAT IT DOES: Returns whether the last request was cancelled by the player. */
int MemoryStick::f_01a90c()
{
    return result == 1;
}

/* @implements 0x01a91c us f_01a91c
   WHAT IT DOES: Starts saving the game: writes the saved game into a new stream and opens the
   save dialog (automatic, or letting the player confirm) with the game's texts, the player's
   name and distance driven (in miles on an English console) and the menu package's icons and
   picture. */
void MemoryStick::f_01a91c(bool automatic)
{
    char detail[1024];

    if (f_01c260() == 6)
        sprintf(detail, D_1d16c4[f_01c260()], D_233f70.name, (int)(D_233f70.m15680 / 1609.34f));
    else
        sprintf(detail, D_1d16c4[f_01c260()], D_233f70.name, D_233f70.m15680 / 1000);
    stream = new CSaveStream;
    stream->f_0191c4(0x4000);
    stream->f_019264(&D_233f70);
    stream->f_0192f8();
    D_1e38f4.f_00612c();
    unsigned char *buf = stream->buf;
    D_1e38f4.f_0061a0(buf, 0x4000, stream->f_019280());
    D_1e38f4.f_0061b0(D_233f70.f_019494(), D_233f70.Text1(), detail);
    void *p, *q;
    p = D_2301d4.f_002acc("Icon0");
    D_1e38f4.f_006260(p, D_1c0614[f_00222c("Icon0", f_01c26c("MainMenuSwg"))].size);
    p = D_2301d4.f_002acc("Icon1");
    D_1e38f4.f_006274(p, D_1c0614[f_00222c("Icon1", f_01c26c("MainMenuSwg"))].size);
    q = D_2301d4.f_002acc("Pic");
    D_1e38f4.f_006288(q, D_1c0614[f_00222c("Pic", f_01c26c("MainMenuSwg"))].size);
    D_1e38f4.f_00629c();
    if (automatic)
        D_1e38f4.f_0063b4(0);
    else
        D_1e38f4.f_0063fc(0);
    D_1e38f4.f_006664();
}

/* @implements 0x01abf4 us f_01abf4
   WHAT IT DOES: Runs the save dialog for a frame. When it has closed, records its result
   (no memory stick, or not enough space) and, after a successful save, marks the game saved
   and keeps a copy of what was saved. Returns whether the dialog has closed. */
int MemoryStick::f_01abf4()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110381:
        case (int)0x80110382:
            noStick = 1;
            break;
        case (int)0x80110383:
            full = 1;
            break;
        }
        if (f_01a900()) {
            D_233f70.m15756 = 1;
            D_237d00 = D_233f70;
            f_00600c();
        }
        delete stream;
    }
    return r;
}

/* @implements 0x01ad04 us f_01ad04
   WHAT IT DOES: Starts loading the game: prepares a new saved game object and stream and
   opens the load dialog (automatic, or letting the player confirm). */
void MemoryStick::f_01ad04(bool automatic)
{
    game = new Sequence::CGameSaveData;
    stream = new CSaveStream;
    stream->f_0191c4(0x4000);
    stream->f_019264(game);
    D_1e38f4.f_00612c();
    D_1e38f4.f_0061a0(stream->buf, 0x4000, 0x4000);
    D_1e38f4.f_0061b0(D_233f70.f_019494(), D_233f70.Text1(), D_233f70.Text2());
    D_1e38f4.f_006260(0, 0);
    D_1e38f4.f_006274(0, 0);
    D_1e38f4.f_006288(0, 0);
    if (automatic)
        D_1e38f4.f_006394(0);
    else
        D_1e38f4.f_0063d8(0);
    D_1e38f4.f_006664();
}

/* @implements 0x01ae50 us f_01ae50
   WHAT IT DOES: Runs the load dialog for a frame. When it has closed, records its result (no
   memory stick, or no saved game) and, if the load succeeded and the data is intact, makes it
   the game's state, keeps a copy and applies its settings; damaged data is reported as
   broken. Returns whether the dialog has closed. */
int MemoryStick::f_01ae50()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110301:
        case (int)0x80110302:
            noStick = 1;
            break;
        case (int)0x80110306:
            break;
        case (int)0x80110307:
            missing = 1;
            break;
        }
        if (f_01a900()) {
            if (!stream->f_0193a8()) {
                D_233f70 = *game;
                D_233f70.m15756 = 1;
                D_237d00 = D_233f70;
                D_233f70.f_01959c();
                f_00600c();
            } else {
                broken = 1;
                result = 0x80110306;
            }
        }
        delete game;
        delete stream;
    }
    return r;
}

/* @implements 0x01afa8 us f_01afa8
   WHAT IT DOES: Starts saving a replay: writes it into a new stream and opens the save dialog
   on a list of 99 slots, with the replay's texts and the result menu's icons and picture. */
void MemoryStick::f_01afa8()
{
    char *ld = D_1dd6b0;
    void *p, *q;
    D_23bab4.data = replayData;
    D_23bab4.size = replaySize;
    stream = new CSaveStream;
    stream->f_0191c4(0x80000);
    stream->f_019264(&D_23bab4);
    stream->f_0192f8();
    D_1e38f4.f_00612c();
    unsigned char *buf = stream->buf;
    D_1e38f4.f_0061a0(buf, 0x4000, stream->f_019280());
    D_1e38f4.f_0061b0(D_23bab4.f_019494(), D_23bab4.Text1(), replayText);
    p = f_005c34(ld, "RIcon0");
    D_1e38f4.f_006260(p, D_1c0614[f_00222c("RIcon0", f_01c26c("ResultMenu"))].size);
    p = f_005c34(ld, "RIcon1");
    D_1e38f4.f_006274(p, D_1c0614[f_00222c("RIcon1", f_01c26c("ResultMenu"))].size);
    q = f_005c34(ld, "Pic");
    D_1e38f4.f_006288(q, D_1c0614[f_00222c("Pic", f_01c26c("ResultMenu"))].size);
    D_1e38f4.f_00629c();
    D_1e38f4.f_0064dc(100, 99);
    D_1e38f4.f_006664();
}

/* @implements 0x01b1ac us f_01b1ac
   WHAT IT DOES: Runs the replay save dialog for a frame and, when it has closed, records its
   result. Returns whether the dialog has closed. */
int MemoryStick::f_01b1ac()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110381:
        case (int)0x80110382:
            noStick = 1;
            break;
        case (int)0x80110383:
            full = 1;
            break;
        }
        delete stream;
    }
    return r;
}

/* @implements 0x01b284 us f_01b284
   WHAT IT DOES: Starts loading a replay into the given buffer: opens the load dialog on a list
   of 99 slots. */
void MemoryStick::f_01b284()
{
    replay = new Sequence::CReplaySaveData;
    replay->data = replayData;
    replay->size = replaySize;
    stream = new CSaveStream;
    stream->f_0191c4(0x80000);
    stream->f_019264(replay);
    D_1e38f4.f_00612c();
    D_1e38f4.f_0061a0(stream->buf, 0x80000, 0x80000);
    D_1e38f4.f_0061b0(D_23bab4.f_019494(), D_23bab4.Text1(), D_23bab4.Text2());
    D_1e38f4.f_006260(0, 0);
    D_1e38f4.f_006274(0, 0);
    D_1e38f4.f_006288(0, 0);
    D_1e38f4.f_006420(100, 99);
    D_1e38f4.f_006664();
}

/* @implements 0x01b3b8 us f_01b3b8
   WHAT IT DOES: Runs the replay load dialog for a frame. When it has closed, records its
   result and, if the replay is intact, its size; damaged data is reported as broken. Returns
   whether the dialog has closed. */
int MemoryStick::f_01b3b8()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110301:
        case (int)0x80110302:
            noStick = 1;
            break;
        case (int)0x80110306:
            broken = 1;
            break;
        case (int)0x80110307:
            missing = 1;
            break;
        }
        if (f_01a900()) {
            if (!stream->f_0193a8()) {
                loadedSize = replay->size;
            } else {
                broken = 1;
                result = 0x80110306;
            }
        }
        delete replay;
        delete stream;
    }
    return r;
}

/* @implements 0x01b4e8 us f_01b4e8
   WHAT IT DOES: Starts saving a ghost to the given course's slot: writes it into a new stream
   and opens the save dialog with the ghost's texts and the result menu's icons and
   picture. */
void MemoryStick::f_01b4e8(int slot)
{
    char *ld = D_1dd6b0;
    D_23bab4.data = replayData;
    D_23bab4.size = replaySize;
    stream = new CSaveStream;
    stream->f_0191c4(0x80000);
    stream->f_019264(&D_23bab4);
    stream->f_0192f8();
    D_1e38f4.f_00612c();
    unsigned char *buf = stream->buf;
    D_1e38f4.f_0061a0(buf, 0x4000, stream->f_019280());
    const char *title = D_23bab4.f_019494();
    D_1e38f4.f_0061b0(title, D_1d16a8[f_01c260()], replayText);
    void *p, *q;
    p = f_005c34(ld, "GIcon0");
    D_1e38f4.f_006260(p, D_1c0614[f_00222c("GIcon0", f_01c26c("ResultMenu"))].size);
    p = f_005c34(ld, "GIcon1");
    D_1e38f4.f_006274(p, D_1c0614[f_00222c("GIcon1", f_01c26c("ResultMenu"))].size);
    q = f_005c34(ld, "Pic");
    D_1e38f4.f_006288(q, D_1c0614[f_00222c("Pic", f_01c26c("ResultMenu"))].size);
    D_1e38f4.f_0063fc(slot + 200);
    D_1e38f4.f_006664();
}

/* @implements 0x01b6fc us f_01b6fc
   WHAT IT DOES: Runs the ghost save dialog for a frame and, when it has closed, records its
   result. Returns whether the dialog has closed. */
int MemoryStick::f_01b6fc()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110381:
        case (int)0x80110382:
            noStick = 1;
            break;
        case (int)0x80110383:
            full = 1;
            break;
        }
        delete stream;
    }
    return r;
}

/* @implements 0x01b7d4 us f_01b7d4
   WHAT IT DOES: Starts loading the ghost of the given course into the given buffer, without a
   dialog. */
void MemoryStick::f_01b7d4(int slot)
{
    replay = new Sequence::CReplaySaveData;
    replay->data = replayData;
    replay->size = replaySize;
    stream = new CSaveStream;
    stream->f_0191c4(0x80000);
    stream->f_019264(replay);
    D_1e38f4.f_00612c();
    D_1e38f4.f_0061a0(stream->buf, 0x80000, 0x80000);
    const char *title = D_23bab4.f_019494();
    D_1e38f4.f_0061b0(title, D_1d16a8[f_01c260()], D_23bab4.Text2());
    D_1e38f4.f_006260(0, 0);
    D_1e38f4.f_006274(0, 0);
    D_1e38f4.f_006288(0, 0);
    D_1e38f4.f_006394(slot + 200);
    D_1e38f4.f_006664();
}

/* f_01b91c (0x01b91c): its tag stays with the compiler control set (src/control/batch6.c)
   until that copy moves here.
   WHAT IT DOES: Runs the ghost load for a frame, like the replay load. Returns whether it has
   finished. */
int MemoryStick::f_01b91c()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110301:
        case (int)0x80110302:
            noStick = 1;
            break;
        case (int)0x80110306:
            broken = 1;
            break;
        case (int)0x80110307:
            missing = 1;
            break;
        }
        if (f_01a900()) {
            if (!stream->f_0193a8()) {
                loadedSize = replay->size;
            } else {
                broken = 1;
                result = 0x80110306;
            }
        }
        delete replay;
        delete stream;
    }
    return r;
}

/* @implements 0x01ba4c us f_01ba4c
   WHAT IT DOES: Starts asking the system how much space the memory stick has. */
void MemoryStick::f_01ba4c()
{
    D_1e38f4.f_00612c();
    D_1e38f4.f_006658();
    D_1e38f4.f_006664();
}

/* @implements 0x01ba88 us f_01ba88
   WHAT IT DOES: Runs the space query for a frame and, when it has finished, records whether
   the memory stick is missing or unusable. Returns whether it has finished. */
int MemoryStick::f_01ba88()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110341:
        case (int)0x80110342:
            noStick = 1;
            break;
        case (int)0x80110343:
            break;
        case (int)0x80110344:
            break;
        case (int)0x80110345:
            break;
        case (int)0x80110346:
            break;
        case (int)0x80110347:
            missing = 1;
            break;
        }
    }
    return r;
}

/* @implements 0x01bb3c us f_01bb3c
   WHAT IT DOES: Starts reading the saved game back without a dialog, to compare it with the
   game's state. */
void MemoryStick::f_01bb3c()
{
    game = new Sequence::CGameSaveData;
    stream = new CSaveStream;
    stream->f_0191c4(0x4000);
    stream->f_019264(game);
    D_1e38f4.f_00612c();
    D_1e38f4.f_0061a0(stream->buf, 0x4000, 0x4000);
    D_1e38f4.f_0061b0(D_233f70.f_019494(), D_233f70.Text1(), D_233f70.Text2());
    D_1e38f4.f_006260(0, 0);
    D_1e38f4.f_006274(0, 0);
    D_1e38f4.f_006288(0, 0);
    D_1e38f4.f_006394(0);
    D_1e38f4.f_006664();
}

/* @implements 0x01bc5c us f_01bc5c
   WHAT IT DOES: Runs that read for a frame. When it has finished, records its result and
   reports the saved game as broken if it is damaged or is not the game's own save (its time
   and random identity differ). Returns whether it has finished. */
int MemoryStick::f_01bc5c()
{
    int r = D_1e38f4.f_006680();

    if (r) {
        D_1e38f4.f_006728();
        noStick = 0;
        full = 0;
        missing = 0;
        broken = 0;
        result = D_1e38f4.result;
        switch (result) {
        case (int)0x80110301:
        case (int)0x80110302:
            noStick = 1;
            break;
        case (int)0x80110306:
            break;
        case (int)0x80110307:
            missing = 1;
            break;
        }
        if (f_01a900()) {
            if (!stream->f_0193a8()) {
                if (D_233f70.m15744 != game->m15744 || D_233f70.m15748 != game->m15748
                    || D_233f70.m15752 != game->m15752)
                    broken = 1;
                else
                    f_00600c();
            } else {
                broken = 1;
                result = 0x80110306;
            }
        }
        delete game;
        delete stream;
    }
    return r;
}

/* @implements 0x01bdc4 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the saved game, its copy and the replay object. */

/* @implements 0x01be24 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x01be44 us _ZN8Sequence13CGameSaveDataaSERKS0_
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: Copies a saved game, all but its vtable pointer. */

/* @implements 0x01c1dc us _ZN8Sequence13CGameSaveData4SizeEv
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: Returns the fixed number of bytes a saved game takes in a save. */
