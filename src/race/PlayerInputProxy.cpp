/* The player input proxy object file (retail 0x037b78 to 0x038734, "CPlayerInputProxy::Do").
   It stands between a controller and the car. In write mode it reads the controller's gas,
   brake, steering, shift and side brake each frame and packs the change since the last frame
   into a replay stream; in read mode it unpacks the stream and rebuilds the same inputs, so a
   recorded run (a ghost) drives exactly as it was driven. */

extern "C" {
void f_043fa4(void *);
void f_043fdc(void *);
void f_00d354(void *log, int level, const char *fmt, ...);
}
extern char D_245178[];
extern signed char D_240bf8[];

/* The controller (made elsewhere). */
struct CCustomController {
    int m0;
    signed char m4;
    signed char m5;
    char m6[114];
    int f_043aa0(int ch);
    int f_043a0c(int ch);
    int f_043498();
    int f_04361c(int ch);
    int f_0434f0();
    int f_042f40();
    int f_0432f8();
    int f_0436d0(int ch);
    int f_0437cc(int ch);
};
extern CCustomController D_1d8910[];

/* The packer's dictionary (made and destroyed by the packer code). */
struct CodecDict {
    char m0[16];
    CodecDict() { f_043fa4(this); }
    ~CodecDict() { f_043fdc(this); }
};

/* Three counters of a packer channel. */
struct CodecCount {
    int a;
    int b;
    int c;
    void Clear()
    {
        a = 0;
        b = 0;
        c = 0;
    }
};

/* One channel of the packer. */
struct CodecChannel {
    int m0;
    int m4;
    CodecCount in;
    CodecCount out;
    int m32;
    int m36;
    int m40;
    int m44;
    char m48;
    int m52;
    int m56;
    int m60;
    CodecChannel()
    {
        m0 = 0;
        m4 = 0;
        m32 = 1;
        m36 = 0;
        m40 = 0;
        m44 = 0;
        m48 = 0;
        m52 = 0;
        in.Clear();
        out.Clear();
        m60 = 0;
    }
};

/* The packer: 16 channels of bytes packed into one stream. */
struct Codec {
    char m0[2056];
    CodecChannel ch[16];
    CodecDict dict;

    void f_0449c0(int i, int byte);
    void f_044a28(int i);
    int f_044a68(int i);
    void f_044aa4(void *work, int n);
    void f_044b44(int i, int a);
    void f_044c3c(int i);
    void f_044cd4(int i);
};

/* The inputs of one frame. */
struct InputFrame {
    int gas;
    int brake;
    int handle;
    int shift;
    int sideBrake;
    int rawGas;
    int rawBrake;
    int rawHandle;
    int gear;
    int buttons;
};

class CPlayerInputProxy {
public:
    int mode;   /* 0 records, 1 plays back */
    int mirror; /* steering is mirrored */
    CCustomController *pad;
    Codec codec;
    InputFrame last;
    char work[0x20000];

    CPlayerInputProxy();
    ~CPlayerInputProxy();
    void f_037d28(CCustomController *p);
    void f_037d30(int n, int a);
    void f_037d50();
    void f_037d6c(int m, int mirrored);
    void Do();
    void f_038604();
    void f_0386a8();
};

/* The kind of a controller channel: 255 when it is not fitted. */
static inline int Kind(int raw)
{
    return raw == 255 ? 255 : raw & 15;
}

/* @implements 0x037b78 us _ZN17CPlayerInputProxyC2Ev
   WHAT IT DOES: Makes an input proxy: clears the packer's channels, makes its dictionary and
   hands the packer the proxy's work buffer. */
CPlayerInputProxy::CPlayerInputProxy()
{
    codec.f_044aa4(work, 512);
}

/* @implements 0x037c34 us _ZN17CPlayerInputProxyC1Ev
   WHAT IT DOES: The same constructor, for a complete object. */

/* @implements 0x037cf0 us _ZN17CPlayerInputProxyD2Ev
   WHAT IT DOES: Destroys an input proxy (its packer's dictionary). */
CPlayerInputProxy::~CPlayerInputProxy()
{
}

/* @implements 0x037d0c us _ZN17CPlayerInputProxyD1Ev
   WHAT IT DOES: The same destructor, for a complete object. */

/* @implements 0x037d28 us f_037d28
   WHAT IT DOES: Sets the controller the proxy reads. */
void CPlayerInputProxy::f_037d28(CCustomController *p)
{
    pad = p;
}

/* @implements 0x037d30 us f_037d30
   WHAT IT DOES: Sets the controller the proxy reads to the numbered one. */
void CPlayerInputProxy::f_037d30(int n, int a)
{
    pad = &D_1d8910[n];
}

/* @implements 0x037d50 us f_037d50
   WHAT IT DOES: Finishes a recording (see f_038604). */
void CPlayerInputProxy::f_037d50()
{
    f_038604();
}

/* @implements 0x037d6c us f_037d6c
   WHAT IT DOES: Starts recording (mode 0) or playing back (mode 1): opens the nine packer
   channels for writing or reading and clears the last frame's inputs. */
void CPlayerInputProxy::f_037d6c(int m, int mirrored)
{
    mirror = mirrored;
    mode = m;
    switch (m) {
    case 0:
        codec.f_044c3c(0);
        codec.f_044c3c(1);
        codec.f_044c3c(2);
        codec.f_044c3c(3);
        codec.f_044c3c(4);
        codec.f_044c3c(5);
        codec.f_044c3c(6);
        codec.f_044c3c(7);
        codec.f_044c3c(8);
        codec.f_044b44(0, 1);
        codec.f_044b44(1, 1);
        codec.f_044b44(2, 1);
        codec.f_044b44(3, 1);
        codec.f_044b44(4, 1);
        codec.f_044b44(5, 1);
        codec.f_044b44(6, 1);
        codec.f_044b44(7, 1);
        codec.f_044b44(8, 1);
        last.gas = 0;
        last.brake = 0;
        last.handle = 0;
        last.shift = 0;
        last.sideBrake = 0;
        last.rawGas = 0;
        last.rawBrake = 0;
        last.rawHandle = 0;
        last.gear = 0;
        last.buttons = 0;
        break;
    case 1:
        codec.f_044cd4(0);
        codec.f_044cd4(1);
        codec.f_044cd4(2);
        codec.f_044cd4(3);
        codec.f_044cd4(4);
        codec.f_044cd4(5);
        codec.f_044cd4(6);
        codec.f_044cd4(7);
        codec.f_044cd4(8);
        last.gas = 0;
        last.brake = 0;
        last.handle = 0;
        last.shift = 0;
        last.sideBrake = 0;
        last.rawGas = 0;
        last.rawBrake = 0;
        last.rawHandle = 0;
        last.gear = 0;
        last.buttons = 0;
        break;
    }
}

/* @draft 0x037f48 us _ZN17CPlayerInputProxy2DoEv
   WHAT IT DOES: Runs one frame. Recording, it reads the controller's gas, brake and steering
   (analogue or digital, by the kind of each control; an unknown kind logs a warning and reads
   as 0), the shift and side brake, the current gear and the button bits, and packs each
   input's change since the last frame into its channel (steering as two bytes). Playing back,
   it unpacks the changes, adds them to the last frame's inputs and splits the button bits
   back into the shift and side brake. */
void CPlayerInputProxy::Do()
{
    switch (mode) {
    case 0: {
        InputFrame s;
        int k, d, hi;

        s.rawGas = pad->f_043aa0(2);
        switch (Kind(s.rawGas)) {
        case 2:
            s.gas = pad->f_043498();
            break;
        case 0:
            s.gas = pad->f_04361c(2) * 255;
            break;
        case 255:
            s.gas = 0;
            break;
        default:
            f_00d354(D_245178, 16, "Warning(%s): %s = 0x%x\n", "CPlayerInputProxy::Do write-mode", "DeviceGas", s.rawGas);
            s.gas = 0;
            break;
        }
        s.rawBrake = pad->f_043aa0(3);
        switch (Kind(s.rawBrake)) {
        case 2:
            s.brake = pad->f_0434f0();
            break;
        case 0:
            s.brake = pad->f_04361c(3) * 255;
            break;
        case 255:
            s.brake = 0;
            break;
        default:
            f_00d354(D_245178, 16, "Warning(%s): %s = 0x%x\n", "CPlayerInputProxy::Do write-mode", "DeviceBrake", s.rawBrake);
            s.brake = 0;
            break;
        }
        s.rawHandle = pad->f_043aa0(0);
        switch (Kind(s.rawHandle)) {
        case 1:
            k = pad->f_042f40();
            if (mirror)
                k = -k;
            s.handle = k;
            break;
        case 3:
            s.handle = pad->f_0432f8();
            break;
        case 255:
            s.handle = 0;
            break;
        default:
            f_00d354(D_245178, 16, "Warning(%s): %s = 0x%x\n", "CPlayerInputProxy::Do write-mode", "DeviceHandle", s.rawHandle);
            s.handle = 0;
            break;
        }
        k = pad->f_043a0c(4);
        switch (k) {
        case 1:
            s.shift = pad->f_0436d0(4);
            break;
        case 255:
            s.shift = 0;
            break;
        default:
            f_00d354(D_245178, 16, "Warning(%s): %s = %d\n", "CPlayerInputProxy::Do write-mode", "DeviceShift", k);
            s.shift = 0;
            break;
        }
        k = pad->f_043a0c(6);
        switch (k) {
        case 0:
            s.sideBrake = pad->f_0437cc(6);
            break;
        case 255:
            s.sideBrake = 0;
            break;
        default:
            f_00d354(D_245178, 16, "Warning(%s): %s = %d\n", "CPlayerInputProxy::Do write-mode", "DeviceSideBrake", k);
            s.sideBrake = 0;
            break;
        }
        {
            CCustomController *p = pad;
            s.gear = D_240bf8[p->m4] != -1 ? p->m5 : 3;
        }
        s.buttons = (s.sideBrake << 2) | (s.shift < 0 ? 3 : s.shift);

        d = s.gas - last.gas;
        if (d < 0)
            d += 256;
        codec.f_0449c0(0, d & 0xff);
        d = s.brake - last.brake;
        if (d < 0)
            d += 256;
        codec.f_0449c0(1, d & 0xff);
        d = s.handle - last.handle;
        if (d < 0)
            d += 0x10000;
        hi = d / 256;
        codec.f_0449c0(2, d & 0xff);
        codec.f_0449c0(3, hi & 0xff);
        d = s.rawGas - last.rawGas;
        if (d < 0)
            d += 256;
        codec.f_0449c0(4, d & 0xff);
        d = s.rawBrake - last.rawBrake;
        if (d < 0)
            d += 256;
        codec.f_0449c0(5, d & 0xff);
        d = s.rawHandle - last.rawHandle;
        if (d < 0)
            d += 256;
        codec.f_0449c0(6, d & 0xff);
        d = s.gear - last.gear;
        if (d < 0)
            d += 256;
        codec.f_0449c0(7, d & 0xff);
        d = s.buttons - last.buttons;
        if (d < 0)
            d += 256;
        codec.f_0449c0(8, d & 0xff);
        last = s;
        break;
    }
    case 1: {
        int d, b;

        last.gas = (codec.f_044a68(0) + last.gas) % 256;
        last.brake = (codec.f_044a68(1) + last.brake) % 256;
        d = codec.f_044a68(2);
        d += codec.f_044a68(3) << 8;
        if (d > 32767)
            d -= 0x10000;
        last.handle += d;
        last.rawGas = (codec.f_044a68(4) + last.rawGas) % 256;
        last.rawBrake = (codec.f_044a68(5) + last.rawBrake) % 256;
        last.rawHandle = (codec.f_044a68(6) + last.rawHandle) % 256;
        last.gear = (codec.f_044a68(7) + last.gear) % 256;
        last.buttons = (codec.f_044a68(8) + last.buttons) % 256;
        b = last.buttons & 3;
        if (b == 3)
            last.shift = -1;
        else
            last.shift = b;
        last.sideBrake = (last.buttons >> 2) & 1;
        break;
    }
    }
}

/* @implements 0x038604 us f_038604
   WHAT IT DOES: When recording, flushes the nine packer channels. */
void CPlayerInputProxy::f_038604()
{
    if (mode == 0) {
        codec.f_044a28(0);
        codec.f_044a28(1);
        codec.f_044a28(2);
        codec.f_044a28(3);
        codec.f_044a28(4);
        codec.f_044a28(5);
        codec.f_044a28(6);
        codec.f_044a28(7);
        codec.f_044a28(8);
    }
}

/* @implements 0x0386a8 us f_0386a8
   WHAT IT DOES: Resets the nine packer channels. */
void CPlayerInputProxy::f_0386a8()
{
    codec.f_044c3c(0);
    codec.f_044c3c(1);
    codec.f_044c3c(2);
    codec.f_044c3c(3);
    codec.f_044c3c(4);
    codec.f_044c3c(5);
    codec.f_044c3c(6);
    codec.f_044c3c(7);
    codec.f_044c3c(8);
}
