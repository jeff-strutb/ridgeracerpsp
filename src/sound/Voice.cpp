/* The sound voice object file (retail 0x0fa284 to 0x0fa7f0; its debug prints say "CVoice"
   and "CVoiceMgr"). A 36 byte voice wraps the sound library's voice calls (key on by bank
   id or handle, volume, pan, pitch, fades, finished test) and reports their error codes;
   the voice manager's calls pause, resume and key off every voice. */

void f_093f90(const char *fmt, ...);

extern "C" {
/* The sound library (nuSound). */
int f_10bf04(int pause);
int f_10c004(unsigned short bank, unsigned short tone, void *voice);
int f_10c09c(unsigned short bank, unsigned short tone, int a, int b, void *voice, float vol);
int f_10c158(unsigned short bank, unsigned short tone, void *voice);
int f_10c5a4(void *voice);
int f_10c65c(void);
int f_10c6fc(void *voice, short a, short b);
int f_10c764(void *voice, int vol);
int f_10c7b4(short pan, void *voice);
int f_10c810(short pitch, void *voice);
int f_10c86c(void *voice);
int f_10ed74(int time, void *voice);
int f_10ed90(unsigned short bank, unsigned short tone, int time, void *voice, float vol);
int f_10ee20(int time, void *voice);
}

class CVoice {
public:
    CVoice();
    int f_0fa294(unsigned int key);
    int f_0fa2e8(unsigned short bank, unsigned short tone);
    int f_0fa354(unsigned short bank, unsigned short tone);
    int f_0fa3c0(unsigned short bank, unsigned short tone, float vol);
    int f_0fa458();
    int f_0fa47c(int vol);
    int f_0fa4c0(short pan);
    int f_0fa510(short pitch);
    int f_0fa560(short a, short b);
    int f_0fa5a8(int time);
    int f_0fa5f4(int time);
    int f_0fa640(unsigned short bank, unsigned short tone, int time, float vol);
    int f_0fa6d4();

    int m0[2];
    int m8;
    int m12[6];
};

/* The voice manager. */
struct CVoiceMgr {
    static int f_0fa724();
    static int f_0fa768();
    static int f_0fa7ac();
};

/* @implements 0x0fa284 us _ZN6CVoiceC2Ev
   WHAT IT DOES: Makes an idle voice (base object constructor). */
/* @implements 0x0fa28c us _ZN6CVoiceC1Ev
   WHAT IT DOES: The same, complete object constructor. */
CVoice::CVoice()
{
    m8 = 0;
}

/* @implements 0x0fa294 us f_0fa294
   WHAT IT DOES: Keys on the tone of a packed bank and tone key. Returns -1 on an error. */
int CVoice::f_0fa294(unsigned int key)
{
    int r = f_10c004(key >> 16, key, this);
    if (r < 0) {
        f_093f90("CVoice: KeyOn Failed! nuSoundKeyOnID Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa2e8 us f_0fa2e8
   WHAT IT DOES: Keys on a tone of a bank given by id. Returns -1 on an error. */
int CVoice::f_0fa2e8(unsigned short bank, unsigned short tone)
{
    int r = f_10c004(bank, tone, this);
    if (r < 0) {
        f_093f90("CVoice: KeyOnID Failed! nuSoundKeyOnID ErrorCode[0x%x] BankId[%d] ToneNo[%d]\n", r,
                 bank, tone);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa354 us f_0fa354
   WHAT IT DOES: Keys on a tone of a bank given by handle. Returns -1 on an error. */
int CVoice::f_0fa354(unsigned short bank, unsigned short tone)
{
    int r = f_10c158(bank, tone, this);
    if (r < 0) {
        f_093f90("CVoice: KeyOnHandle Failed! nuSoundKeyOnHandle ErrorCode[0x%x] BankHandle[%d] "
                 "ToneNo[%d]\n",
                 r, bank, tone);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa3c0 us f_0fa3c0
   WHAT IT DOES: Keys on a tone of a bank given by id at a volume. Returns -1 on an error. */
int CVoice::f_0fa3c0(unsigned short bank, unsigned short tone, float vol)
{
    int r = f_10c09c(bank, tone, 0, 0, this, vol);
    if (r < 0) {
        f_093f90("CVoice: KeyOnID Failed! nuSoundKeySetOnID ErrorCode[0x%x] BankId[%d] ToneNo[%d] "
                 "Vol[%f]\n",
                 r, bank, tone, vol);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa458 us f_0fa458
   WHAT IT DOES: Keys the voice off. Returns -1 on an error. */
int CVoice::f_0fa458()
{
    return f_10c5a4(this) < 0 ? -1 : 0;
}

/* @implements 0x0fa47c us f_0fa47c
   WHAT IT DOES: Sets the voice's volume. Returns -1 on an error. */
int CVoice::f_0fa47c(int vol)
{
    int r = f_10c764(this, vol);
    if (r < 0) {
        f_093f90("CVoice: SetVol Failed! nuSoundSetVol Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa4c0 us f_0fa4c0
   WHAT IT DOES: Sets the voice's pan. Returns -1 on an error. */
int CVoice::f_0fa4c0(short pan)
{
    int r = f_10c7b4(pan, this);
    if (r < 0) {
        f_093f90("CVoice: SetPan Failed! nuSoundSetPan Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa510 us f_0fa510
   WHAT IT DOES: Sets the voice's pitch. Returns -1 on an error. */
int CVoice::f_0fa510(short pitch)
{
    int r = f_10c810(pitch, this);
    if (r < 0) {
        f_093f90("CVoice: SetPitch Failed! nuSoundSetPitch Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa560 us f_0fa560
   WHAT IT DOES: Sets the voice's volume, pan and pitch together. Returns -1 on an error. */
int CVoice::f_0fa560(short a, short b)
{
    int r = f_10c6fc(this, a, b);
    if (r < 0) {
        f_093f90("CVoice: SetVolPanPitch Failed! nuSoundSetVolPanPitch Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa5a8 us f_0fa5a8
   WHAT IT DOES: Fades the voice. Returns -1 on an error. */
int CVoice::f_0fa5a8(int time)
{
    int r = f_10ed74(time, this);
    if (r < 0) {
        f_093f90("CVoice: Fade Failed! nuSoundFade Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa5f4 us f_0fa5f4
   WHAT IT DOES: Fades the voice out and keys it off. Returns -1 on an error. */
int CVoice::f_0fa5f4(int time)
{
    int r = f_10ee20(time, this);
    if (r < 0) {
        f_093f90("CVoice: FadeKeyOff Failed! nuSoundFadeKeyOff Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa640 us f_0fa640
   WHAT IT DOES: Keys on a tone of a bank given by id, fading in to a volume. Returns -1 on
   an error. */
int CVoice::f_0fa640(unsigned short bank, unsigned short tone, int time, float vol)
{
    int r = f_10ed90(bank, tone, time, this, vol);
    if (r < 0) {
        f_093f90("CVoice: FadeKeyOnID Failed! nuSoundFadeKeyOnID Error Code: 0x%x BankId[%d] "
                 "ToneNo[%d] Vol[%f]\n",
                 r, bank, tone, vol);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa6d4 us f_0fa6d4
   WHAT IT DOES: Tells whether the voice has finished (an error counts as finished). */
int CVoice::f_0fa6d4()
{
    int r = f_10c86c(this);
    switch (r) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        f_093f90("CVoice: IsFinished Failed! nuSoundVoiceIsFinished Error Code: 0x%x \n", r);
        return 1;
    }
}

/* @implements 0x0fa724 us f_0fa724
   WHAT IT DOES: Pauses every voice. Returns -1 on an error. */
int CVoiceMgr::f_0fa724()
{
    int r = f_10bf04(1);
    if (r < 0) {
        f_093f90("CVoiceMgr: SetPauseOn Failed! nuSoundSetPauseMode Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa768 us f_0fa768
   WHAT IT DOES: Resumes every voice. Returns -1 on an error. */
int CVoiceMgr::f_0fa768()
{
    int r = f_10bf04(0);
    if (r < 0) {
        f_093f90("CVoiceMgr: SetPauseOff Failed! nuSoundSetPauseMode Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}

/* @implements 0x0fa7ac us f_0fa7ac
   WHAT IT DOES: Keys off every voice. Returns -1 on an error. */
int CVoiceMgr::f_0fa7ac()
{
    int r = f_10c65c();
    if (r < 0) {
        f_093f90("CVoiceMgr: KeyOffAll Failed! nuSoundKeyAllOff Error Code: 0x%x \n", r);
        return -1;
    }
    return 0;
}
