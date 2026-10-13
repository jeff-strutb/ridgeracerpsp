/* The stream base object file (retail 0x09450c to 0x095660, Stream::CStreamBase). One streamed
   sound (music or the radio DJ) played through the sound library's stream functions: it
   selects a stream channel and a pack file, starts, readies, fades, pre-loads, pauses and
   stops the stream, places the play cursor, and swaps between two channels for a cross fade.
   Every failure is reported through the (empty) debug print. */

#include <string.h>

void f_093f90(const char *fmt, ...);

extern "C" {
int f_110f58(int stream, const char *name, int id);
int f_111160(int stream, const char *name, int id);
int f_1117d0(int stream, const char *name, int id, int fade);
int f_111acc(int stream, const char *name, int id, int buf, int size);
int f_111ae8(int stream, const char *name, int id, int fade, int buf, int size);
int f_1115ac(int stream, int cursor);
int f_111228(int stream);
int f_111868(int stream, int fade);
int f_1112b0(int stream, int fade);
int f_111030(int stream);
int f_1110c8(int stream, int pause);
int f_111774(int stream, int volume);
int f_1113e4(int stream, void *info);
int f_111900(int stream, int cursor);
void f_0956dc(int stream);
}

/* The stream library's state (its own object file). */
struct CStreamState {
    int m0;
};
extern CStreamState *D_242ca4;

/* The stream data packs (their own object file). */
class CStreamData {
public:
    int f_095a94(int pack);
    int f_095b10(int pack);
    int f_095bc4(int pack, int a);
    int f_095974(int pack, int a, char *name);
    int f_09590c(int pack, int a);
};
extern CStreamData *D_242ca0;

/* A stream's parameters as the library reports them. */
struct StreamInfo {
    int m0[4];
    unsigned short m16;     /* play state: 0 stopped, 2 ready, 3 playing */
    unsigned short m18;
    int m20[3];
    int m32;                /* play cursor */
    int m36;
    int m40;
    int m44;
};

/* Which packs have their own header data. */
extern const int D_1a936c[] = { 0 };
/* The pack files. */
extern const char *const D_1a93a4[] = { "disc0:/PSP_GAME/USRDIR/Data/Sound/bgm_nps_pack.bin" };

namespace Stream {

class CStreamBase {
public:
    CStreamBase();
    virtual ~CStreamBase();
    int f_094604(int ch, int pack);
    int f_0946b4(int ch);
    int f_094704(int pack);
    int f_094768(int a);
    int f_094804(int a);
    int f_0948a0(int a, int fade);
    int f_094948(int a, int buf);
    int f_094a34(int a, int fade, int buf);
    int f_094b34(int a, int cursor);
    int f_094ba0(int a, int cursor);
    int f_094c0c(int a, int cursor, int fade);
    int f_094c7c();
    int f_094cec(int fade);
    int f_094d6c(int fade);
    int f_094db0();
    int f_094df4();
    int f_094e44();
    int f_094e94(int volume);
    int f_094ed8(int cursor);
    int f_094f84();
    int f_094fb0();
    int f_094fd8();
    int f_095004(int ch);
    void f_09505c();
    int f_095090(int ch);
    int f_0950ec(int a, int fade);
    int f_09510c(int a, int cursor, int fade);
    int f_0951f4(int a, int fade);
    int f_09525c(int a, int fade);
    int f_09527c(int a, int cursor, int fade);
    int f_095330();
    int f_0953a8();
    int f_0953b4(int a);
    int f_0953e0();
    int f_095404();
    int f_095448();
    int f_0954ac(int a);
    int f_09550c(int a);
    int f_095538(int a);
    int f_095598(int size);
    int f_095624(int cursor, int stereo);

    int m4;         /* the default channel */
    int m8;         /* the stream channel in use */
    int m12;        /* the stream's data id */
    char m16[256];  /* the pack file's name */
    int m272;       /* pre-load buffer size */
    int m276;
    int m280;       /* the pack in use */
    int m284;       /* cross fade mode */
    int m288;       /* the other channel of a cross fade */
};

/* @implements 0x09450c us _ZN6Stream11CStreamBaseC2Ev
   WHAT IT DOES: Makes a stream with no channel, no pack and no cross fade (base object
   constructor). */
/* @implements 0x094540 us _ZN6Stream11CStreamBaseC1Ev
   WHAT IT DOES: The same (complete object constructor). */
CStreamBase::CStreamBase()
{
    m4 = -1;
    m8 = -1;
    m12 = 0;
    m272 = 0;
    m276 = -1;
    m280 = -1;
    m284 = 0;
    m288 = -1;
}

/* @implements 0x094574 us _ZN6Stream11CStreamBaseD2Ev
   WHAT IT DOES: Forgets the channels and the cross fade (base object destructor). */
/* @implements 0x09459c us _ZN6Stream11CStreamBaseD1Ev
   WHAT IT DOES: The same (complete object destructor). */
/* @implements 0x0945c4 us _ZN6Stream11CStreamBaseD0Ev
   WHAT IT DOES: The same, then frees the object (deleting destructor). */
CStreamBase::~CStreamBase()
{
    m4 = -1;
    m8 = -1;
    m12 = 0;
    m284 = 0;
    m288 = -1;
}

/* @implements 0x094604 us f_094604
   WHAT IT DOES: Selects the default channel, sizes the pre-load buffer from the pack's
   pre-load header when one is registered, and selects the pack file. Returns 0, or -1 for a
   bad channel. */
int CStreamBase::f_094604(int ch, int pack)
{
    if (f_0946b4(ch) < 0) {
        f_093f90("StreamBase: Init Failed\n");
        return -1;
    }
    if (D_242ca0 && D_242ca0->f_095a94(pack) == 1) {
        int size = D_242ca0->f_095b10(pack);
        if (size > 0)
            f_095598(size);
    }
    f_094704(pack);
    return 0;
}

/* @implements 0x0946b4 us f_0946b4
   WHAT IT DOES: Selects the stream channel (only channel 0 exists), making it the default
   when there is none. Returns 0, or -1 for a bad channel. */
int CStreamBase::f_0946b4(int ch)
{
    int r;
    if (ch < 0 || ch >= 1) {
        f_093f90("StreamBase: Set Ch Failed! Invalid Ch[%d]\n", ch);
        r = -1;
    } else {
        m8 = ch;
        if (m4 < 0)
            m4 = ch;
        r = 0;
    }
    return r;
}

/* @implements 0x094704 us f_094704
   WHAT IT DOES: Selects the pack file (only pack 0 exists) and takes its name. Returns 0, or
   -1 for a bad pack or the pack already in use. */
int CStreamBase::f_094704(int pack)
{
    if (pack < 0 || pack >= 1) {
        f_093f90("StreamBase: SetPackFile Failed! Invalid PackID[%d]\n", pack);
        return -1;
    }
    if (m280 != pack) {
        strcpy(m16, D_1a93a4[pack]);
        m280 = pack;
        return 0;
    }
    return -1;
}

/* @implements 0x094768 us f_094768
   WHAT IT DOES: Starts the stream. Returns 0, or -1. */
int CStreamBase::f_094768(int a)
{
    if (D_242ca4->m0 != 1)
        return -1;
    if (f_095538(a) < 0) {
        f_093f90("StreamBase: Start Failed!\n");
        return -1;
    }
    int r = f_110f58(m8, m16, m12);
    if (r < 0) {
        f_093f90("StreamBase: Start Failed! nuSoundStreamStart ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_0956dc(m8);
    return 0;
}

/* @implements 0x094804 us f_094804
   WHAT IT DOES: Readies the stream without playing it. Returns 0, or -1. */
int CStreamBase::f_094804(int a)
{
    if (D_242ca4->m0 != 1)
        return -1;
    if (f_095538(a) < 0) {
        f_093f90("StreamBase: Ready Failed!\n");
        return -1;
    }
    int r = f_111160(m8, m16, m12);
    if (r < 0) {
        f_093f90("StreamBase: Ready Failed! nuSoundStreamReady ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_0956dc(m8);
    return 0;
}

/* @implements 0x0948a0 us f_0948a0
   WHAT IT DOES: Starts the stream with a fade in. Returns 0, or -1. */
int CStreamBase::f_0948a0(int a, int fade)
{
    if (D_242ca4->m0 != 1)
        return -1;
    if (f_095538(a) < 0) {
        f_093f90("StreamBase: FadeStart Failed!\n");
        return -1;
    }
    int r = f_1117d0(m8, m16, m12, fade);
    if (r < 0) {
        f_093f90("StreamBase: Ready Failed! nuSoundStreamFadeStart ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_0956dc(m8);
    return 0;
}

/* @draft 0x094948 us f_094948
   WHAT IT DOES: Starts the stream from a pre-load buffer; without a buffer or a buffer size
   it starts it normally. Returns 0, or -1.
   Remaining difference: the error string addresses. Retail computes the pre-load error's
   address at its log block (lui in the bltz slot) and the start error's before its bgez, and
   uses bltzl for the first failure; here it is the other way round. */
int CStreamBase::f_094948(int a, int buf)
{
    int r;
    if (D_242ca4->m0 != 1)
        return -1;
    if (f_095538(a) < 0) {
        f_093f90("StreamBase: StartPreLoad Failed!\n");
        return -1;
    }
    if (buf == 0) {
        f_093f90("StreamBase: Warning: StartPreLoad Failed! Not Alloc Buff\n");
    } else if (m272 > 0) {
        r = f_111acc(m8, m16, m12, buf, m272);
        if (r < 0) {
            f_093f90("StreamBase: StartPreLoad Failed! nuSoundStreamStartPreLoad ERROR CODE:0x%x\n", r);
            return -1;
        }
        f_0956dc(m8);
        return 0;
    } else {
        f_093f90("StreamBase: Warning: StartPreLoad Failed! Invalid BuffSize[%d]\n");
    }
    r = f_110f58(m8, m16, m12);
    if (r < 0) {
        f_093f90("StreamBase: StartPreLoad Failed! nuSoundStreamStart ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_0956dc(m8);
    return 0;
}

/* @draft 0x094a34 us f_094a34
   WHAT IT DOES: Starts the stream with a fade in from a pre-load buffer; without a buffer or
   a buffer size it fades it in normally. Returns 0, or -1.
   Remaining difference: as for f_094948 (error string address placement and bltzl). */
int CStreamBase::f_094a34(int a, int fade, int buf)
{
    int r;
    if (D_242ca4->m0 != 1)
        return -1;
    if (f_095538(a) < 0) {
        f_093f90("StreamBase: FadeStartPreLoad Failed!\n");
        return -1;
    }
    if (buf == 0) {
        f_093f90("StreamBase: Warning: FadeStartPreLoad Failed! Not Alloc Buff\n");
    } else if (m272 > 0) {
        r = f_111ae8(m8, m16, m12, fade, buf, m272);
        if (r < 0) {
            f_093f90("StreamBase: FadeStartPreLoad Failed! nuSoundStreamFadeStartPreLoad ERROR CODE:0x%x\n", r);
            return -1;
        }
        f_0956dc(m8);
        return 0;
    } else {
        f_093f90("StreamBase: Warning: FadeStartPreLoad Failed! Invalid BuffSize[%d]\n");
    }
    r = f_1117d0(m8, m16, m12, fade);
    if (r < 0) {
        f_093f90("StreamBase: FadeStartPreLoad Failed! nuSoundStreamFadeStart ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_0956dc(m8);
    return 0;
}

/* @implements 0x094b34 us f_094b34
   WHAT IT DOES: Starts the stream and places its play cursor. Returns 0, or -1. */
int CStreamBase::f_094b34(int a, int cursor)
{
    if (f_094768(a) < 0)
        return -1;
    int r = f_1115ac(m8, cursor);
    if (r < 0) {
        f_093f90("StreamBase: StartSetCursor Failed! nuSoundStreamSetPlayCursor ERROR CODE:0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094ba0 us f_094ba0
   WHAT IT DOES: Readies the stream and places its play cursor. Returns 0, or -1. */
int CStreamBase::f_094ba0(int a, int cursor)
{
    if (f_094804(a) < 0)
        return -1;
    int r = f_1115ac(m8, cursor);
    if (r < 0) {
        f_093f90("StreamBase: ReadySetCursor Failed! nuSoundStreamSetPlayCursor ERROR CODE:0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094c0c us f_094c0c
   WHAT IT DOES: Fades the stream in and places its play cursor. Returns 0, or -1. */
int CStreamBase::f_094c0c(int a, int cursor, int fade)
{
    if (f_0948a0(a, fade) < 0)
        return -1;
    int r = f_1115ac(m8, cursor);
    if (r < 0) {
        f_093f90("StreamBase: FadeStartSetCursor Failed! nuSoundStreamSetPlayCursor ERROR CODE:0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094c7c us f_094c7c
   WHAT IT DOES: Plays a readied stream. Returns 0, or -1. */
int CStreamBase::f_094c7c()
{
    if (!f_094f84()) {
        f_093f90("StreamBase: Go Failed! Status is Not Ready \n");
        return -1;
    }
    int r = f_111228(m8);
    if (r < 0) {
        f_093f90("StreamBase: Go Failed! nuSoundStreamGo ERROR CODE:0x%x\n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094cec us f_094cec
   WHAT IT DOES: Plays a readied stream with a fade in. Returns 0, or -1. */
int CStreamBase::f_094cec(int fade)
{
    if (!f_094f84()) {
        f_093f90("StreamBase: FadeGo Failed! Status is Not Ready \n");
        return -1;
    }
    int r = f_111868(m8, fade);
    if (r < 0) {
        f_093f90("StreamBase: FadeGo Failed! nuSoundStreamFadeGo ERROR CODE:0x%x\n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094d6c us f_094d6c
   WHAT IT DOES: Fades the stream out. Returns 0, or -1. */
int CStreamBase::f_094d6c(int fade)
{
    int r = f_1112b0(m8, fade);
    if (r < 0) {
        f_093f90("StreamBase: FadeOut Failed! nuSoundStreamFadeOut ERROR CODE:0x%x\n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094db0 us f_094db0
   WHAT IT DOES: Stops the stream. Returns 0, or -1. */
int CStreamBase::f_094db0()
{
    int r = f_111030(m8);
    if (r < 0) {
        f_093f90("StreamBase: Stop Failed! nuSoundStreamStop ERROR CODE:0x%x\n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094df4 us f_094df4
   WHAT IT DOES: Pauses the stream. Returns 0, or -1. */
int CStreamBase::f_094df4()
{
    int r = f_1110c8(m8, 1);
    if (r < 0) {
        f_093f90("StreamBase: PausOn Failed! nuSoundStreamSetPause ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_093f90("StreamBase: PauseOn\n");
    return 0;
}

/* @implements 0x094e44 us f_094e44
   WHAT IT DOES: Resumes the stream. Returns 0, or -1. */
int CStreamBase::f_094e44()
{
    int r = f_1110c8(m8, 0);
    if (r < 0) {
        f_093f90("StreamBase: PausOff Failed! nuSoundStreamSetPause ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_093f90("StreamBase: PauseOff\n");
    return 0;
}

/* @implements 0x094e94 us f_094e94
   WHAT IT DOES: Changes the stream's volume. Returns 0, or -1. */
int CStreamBase::f_094e94(int volume)
{
    int r = f_111774(m8, volume);
    if (r < 0) {
        f_093f90("StreamBase: ChangeVolume Failed! nuSoundStreamChangeVolume ERROR CODE:0x%x\n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x094ed8 us f_094ed8
   WHAT IT DOES: Starts the stream again from a saved cursor. Returns 0, or -1. */
int CStreamBase::f_094ed8(int cursor)
{
    if (D_242ca4->m0 != 1)
        return -1;
    if (cursor < 0) {
        f_093f90("StreamBase: StartContinue Failed! Invalid Cursor[%d]\n", cursor);
        return -1;
    }
    int r = f_110f58(m8, m16, m12);
    if (r < 0) {
        f_093f90("StreamBase: StartContinue Failed! nuSoundStreamStart ERROR CODE:0x%x\n", r);
        return -1;
    }
    f_1115ac(m8, f_095624(cursor, 0));
    return 0;
}

/* @implements 0x094f84 us f_094f84
   WHAT IT DOES: Whether the stream is ready. */
int CStreamBase::f_094f84()
{
    StreamInfo info;
    f_1113e4(m8, &info);
    return info.m16 == 2;
}

/* @implements 0x094fb0 us f_094fb0
   WHAT IT DOES: Whether the stream is stopped. */
int CStreamBase::f_094fb0()
{
    StreamInfo info;
    f_1113e4(m8, &info);
    return info.m16 == 0;
}

/* @implements 0x094fd8 us f_094fd8
   WHAT IT DOES: Whether the stream is playing. */
int CStreamBase::f_094fd8()
{
    StreamInfo info;
    f_1113e4(m8, &info);
    return info.m16 == 3;
}

/* @implements 0x095004 us f_095004
   WHAT IT DOES: Turns on cross fade mode with the given channel as the other one. Returns 0,
   or -1 for a bad channel or the default channel. */
int CStreamBase::f_095004(int ch)
{
    int r;
    if (ch < 0 || ch >= 1) {
        f_093f90("StreamBase: SetCrossFadeCh Failed! Invalid Ch[%d]\n", ch);
        r = -1;
    } else if (m4 == ch) {
        f_093f90("StreamBase: SetCrossFadeCh Failed! Ch[%d] equal Default\n", ch);
        r = -1;
    } else {
        m284 = 1;
        m288 = ch;
        r = 0;
    }
    return r;
}

/* @implements 0x09505c us f_09505c
   WHAT IT DOES: Turns cross fade mode off and goes back to the default channel. */
void CStreamBase::f_09505c()
{
    f_0946b4(m4);
    m288 = -1;
    m284 = 0;
}

/* @implements 0x095090 us f_095090
   WHAT IT DOES: Sets the other channel of a cross fade. Returns 0, or -1. */
int CStreamBase::f_095090(int ch)
{
    if (!m284) {
        f_093f90("StreamBase: Set AnotherCh Failed! Not CrossFade Mode\n");
        return -1;
    }
    if (ch < 0 || ch >= 1) {
        f_093f90("StreamBase: Set AnotherCh Failed! Invalid Ch[%d]\n", ch);
        return -1;
    }
    m288 = ch;
    return 0;
}

/* @implements 0x0950ec us f_0950ec
   WHAT IT DOES: Cross fades to a stream from its start. */
int CStreamBase::f_0950ec(int a, int fade)
{
    return f_09510c(a, 0, fade);
}

/* @implements 0x09510c us f_09510c
   WHAT IT DOES: Cross fades to a stream: fades the current channel out, swaps to the other
   channel and fades the new stream in there (at a cursor when one is given). Outside cross
   fade mode it simply starts the stream. Returns 0, or -1. */
int CStreamBase::f_09510c(int a, int cursor, int fade)
{
    int r;
    if (m284) {
        f_094d6c(fade);
        int old = m8;
        f_0946b4(m288);
        m288 = old;
        if (cursor) {
            if (f_094c0c(a, cursor, fade) < 0)
                return -1;
        } else {
            if (f_0948a0(a, fade) < 0)
                return -1;
        }
    } else {
        f_093f90("StreamBase: Cannot CrossFade! Not CrossFade Mode\n");
        if (cursor) {
            if (f_094b34(a, cursor) < 0)
                return -1;
        } else {
            if (f_094768(a) < 0)
                return -1;
        }
    }
    return 0;
}

/* @implements 0x0951f4 us f_0951f4
   WHAT IT DOES: Cross fades to a stream at the current stream's play position. */
int CStreamBase::f_0951f4(int a, int fade)
{
    StreamInfo info;
    f_1113e4(m8, &info);
    return f_09510c(a, f_095624(info.m32, 1), fade);
}

/* @implements 0x09525c us f_09525c
   WHAT IT DOES: Swaps channels to a stream from its start. */
int CStreamBase::f_09525c(int a, int fade)
{
    return f_09527c(a, 0, fade);
}

/* @implements 0x09527c us f_09527c
   WHAT IT DOES: Fades the current channel out, swaps to the other channel and starts the new
   stream there without a fade (at a cursor when one is given). Returns 0, or -1. */
int CStreamBase::f_09527c(int a, int cursor, int fade)
{
    int r;
    if (m284) {
        f_094d6c(fade);
        int old = m8;
        f_0946b4(m288);
        m288 = old;
    } else {
        f_093f90("StreamBase: Cannot CrossFade! Not CrossFade Mode\n");
    }
    if (cursor) {
        if (f_094b34(a, cursor) < 0)
            return -1;
    } else {
        if (f_094768(a) < 0)
            return -1;
    }
    return 0;
}

/* @implements 0x095330 us f_095330
   WHAT IT DOES: Exchanges the stream channel and the other cross fade channel. Returns 0, or
   -1. */
int CStreamBase::f_095330()
{
    int other = m288;
    if (f_095090(m8) < 0) {
        f_093f90("StreamBase: ExchangeCh Failed! SetAnotherCh Error\n");
        return -1;
    }
    if (f_0946b4(other) < 0) {
        f_093f90("StreamBase: ExchangeCh Failed! SetStreamCh Error\n");
        return -1;
    }
    return 0;
}

/* @implements 0x0953a8 us f_0953a8
   WHAT IT DOES: Whether a pre-load buffer size is set. */
int CStreamBase::f_0953a8()
{
    return m272 > 0;
}

/* @implements 0x0953b4 us f_0953b4
   WHAT IT DOES: Asks the stream data about an entry of the current pack (0x095bc4). */
int CStreamBase::f_0953b4(int a)
{
    return D_242ca0->f_095bc4(m280, a);
}

/* @implements 0x0953e0 us f_0953e0
   WHAT IT DOES: Returns the stream's parameter at +40 (its length). */
int CStreamBase::f_0953e0()
{
    StreamInfo info;
    f_1113e4(m8, &info);
    return info.m40;
}

/* @implements 0x095404 us f_095404
   WHAT IT DOES: Returns what is left to play: the length less the converted play cursor. */
int CStreamBase::f_095404()
{
    StreamInfo info;
    f_1113e4(m8, &info);
    int done = f_111900(m8, info.m32);
    return info.m40 - done;
}

/* @implements 0x095448 us f_095448
   WHAT IT DOES: Returns the play cursor, or -1 when the stream is not playing. */
int CStreamBase::f_095448()
{
    StreamInfo info;
    int r = f_1113e4(m8, &info);
    if (r < 0) {
        f_093f90("StreamBase: GetPlayCursor Failed! nuSoundGetParam ERROR CODE:0x%x\n", r);
        return -1;
    }
    if (info.m16 == 0) {
        f_093f90("StreamBase: GetPlayCursor Failed! Not Play\n");
        return -1;
    }
    return info.m32;
}

/* @implements 0x0954ac us f_0954ac
   WHAT IT DOES: For a pack with header data, sets up the stream data's header for an entry.
   Returns 0, or -1. */
int CStreamBase::f_0954ac(int a)
{
    int r;
    if (D_1a936c[m280])
        r = D_242ca0->f_095974(m280, a, m16) < 0 ? -1 : 0;
    else
        r = 0;
    return r;
}

/* @implements 0x09550c us f_09550c
   WHAT IT DOES: Returns the stream data's id of an entry of the current pack. */
int CStreamBase::f_09550c(int a)
{
    return D_242ca0->f_09590c(m280, a);
}

/* @implements 0x095538 us f_095538
   WHAT IT DOES: Selects an entry of the current pack as the stream's data. Returns 0, or -1. */
int CStreamBase::f_095538(int a)
{
    if (f_0954ac(a) < 0)
        return -1;
    int id = f_09550c(a);
    m12 = id;
    if (id < 0)
        return -1;
    m276 = a;
    return 0;
}

/* @implements 0x095598 us f_095598
   WHAT IT DOES: Sets the pre-load buffer size, rounded down to whole 2048 byte sectors.
   Returns 0, or -1 for a size that is not positive. */
int CStreamBase::f_095598(int size)
{
    int rem = size % 2048;
    if (size <= 0) {
        f_093f90("StreamBase: SetPreLoadBuffSize Failed! Invalid Size:%d\n", size);
        return -1;
    }
    if (rem > 0)
        f_093f90("StreamBase: Warning: SetPreLoadBuffSize Size:%d Remainder:%d\n", size, rem);
    m272 = size - rem;
    return 0;
}

/* @implements 0x095624 us f_095624
   WHAT IT DOES: Converts a play cursor into a data position: per channel (two for stereo),
   in 16 sample blocks of 28 bytes. */
int CStreamBase::f_095624(int cursor, int stereo)
{
    int n = stereo ? 2 : 1;
    return cursor / n / 16 * 28;
}

}
