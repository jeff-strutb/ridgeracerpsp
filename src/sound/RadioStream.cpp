/* The radio DJ's stream player object file (retail 0x0f970c to 0x0f99c8). The 8 byte object
   pairs two voice channels (AvPlayerManager.cpp's CVoice) that play a script's sound file
   together; most of its stream controls are empty in the retail build and report success. */

extern "C" {
/* The voice channel (its own object file). */
void f_0fa28c(void *voice);
int f_0fa354(void *voice, unsigned short bank, unsigned short file);
void f_0fa458(void *voice);
int f_0fa6d4(void *voice);
int f_0fa724(void);
int f_0fa768(void);

/* The DJ interface (RadioInterface.cpp): the voice bank in use. */
int f_0943b4(void *iface);
}

extern char D_242c90[];

namespace Radio {

/* A voice channel. */
struct CVoice {
    CVoice() { f_0fa28c(this); }
    char m0[36];
};

class CStream {
public:
    CStream();
    ~CStream();
    int f_0f98a4(int table, int file);
    int f_0f990c();
    void f_0f9914();
    int f_0f9944();
    int f_0f9960();
    int f_0f997c(int ch, int b);
    int f_0f9984(int ch);
    int f_0f998c();
    int f_0f99a8();
    int f_0f99b0(int file, int r);
    int f_0f99b8();
    int f_0f99c0(int file);

    CVoice *m0;
    CVoice *m4;
};

/* @implements 0x0f970c us _ZN5Radio7CStreamC2Ev
   WHAT IT DOES: Creates the two voice channels (base object constructor). */
/* @implements 0x0f9778 us _ZN5Radio7CStreamC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CStream::CStream()
{
    m0 = new CVoice;
    m4 = new CVoice;
}

/* @implements 0x0f97e4 us _ZN5Radio7CStreamD2Ev
   WHAT IT DOES: Deletes the two voice channels (base object destructor). */
/* @implements 0x0f9844 us _ZN5Radio7CStreamD1Ev
   WHAT IT DOES: The same, complete object destructor. */
CStream::~CStream()
{
    if (m0)
        delete m0;
    m0 = 0;
    if (m4)
        delete m4;
    m4 = 0;
}

/* @implements 0x0f98a4 us f_0f98a4
   WHAT IT DOES: Loads a sound file of the voice bank in use into both voice channels. */
int CStream::f_0f98a4(int table, int file)
{
    unsigned short bank = f_0943b4(D_242c90);
    f_0fa354(m4, bank, file);
    return f_0fa354(m0, bank, file);
}

/* @implements 0x0f990c us f_0f990c
   WHAT IT DOES: Starting the stream: nothing to do, returns 0. */
int CStream::f_0f990c()
{
    return 0;
}

/* @implements 0x0f9914 us f_0f9914
   WHAT IT DOES: Stops both voice channels. */
void CStream::f_0f9914()
{
    f_0fa458(m4);
    f_0fa458(m0);
}

/* @implements 0x0f9944 us f_0f9944
   WHAT IT DOES: Pauses the voice output. */
int CStream::f_0f9944()
{
    return f_0fa724();
}

/* @implements 0x0f9960 us f_0f9960
   WHAT IT DOES: Resumes the voice output. */
int CStream::f_0f9960()
{
    return f_0fa768();
}

/* @implements 0x0f997c us f_0f997c
   WHAT IT DOES: Setting up a stream channel: nothing to do, returns 0. */
int CStream::f_0f997c(int ch, int b)
{
    return 0;
}

/* @implements 0x0f9984 us f_0f9984
   WHAT IT DOES: Choosing a stream channel: nothing to do, returns 0. */
int CStream::f_0f9984(int ch)
{
    return 0;
}

/* @implements 0x0f998c us f_0f998c
   WHAT IT DOES: Tells whether the first voice channel has finished. */
int CStream::f_0f998c()
{
    return f_0fa6d4(m0);
}

/* @implements 0x0f99a8 us f_0f99a8
   WHAT IT DOES: Tells whether the stream is ready: always 1. */
int CStream::f_0f99a8()
{
    return 1;
}

/* @implements 0x0f99b0 us f_0f99b0
   WHAT IT DOES: Taking a preloaded file: nothing to do, returns 0. */
int CStream::f_0f99b0(int file, int r)
{
    return 0;
}

/* @implements 0x0f99b8 us f_0f99b8
   WHAT IT DOES: Tells whether files are preloaded: always 0. */
int CStream::f_0f99b8()
{
    return 0;
}

/* @implements 0x0f99c0 us f_0f99c0
   WHAT IT DOES: The preloaded copy of a file: always 0 (none). */
int CStream::f_0f99c0(int file)
{
    return 0;
}

}
