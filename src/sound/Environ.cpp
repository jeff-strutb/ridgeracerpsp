/* The environment sound object file (retail 0x096e18 to 0x0970e4): one global CEnviron
   that owns a small tone record and a sound player sub-object (0x0fa28c). Start plays the
   record's sound through the player and logs it; Stop logs and stops the environment
   sound. The static data's startup and shutdown entries close the object file; the tone
   record's methods are their own object file (EnvBank.cpp). */

extern "C" {
void f_093f90(const char *fmt, ...);
void f_0fa28c(void *player);
int f_0fa354(void *player, int handle, int tone);
void f_10d408(int handle, int *id);
void f_0fa7ac(void);
}

struct CEnvBank {
    CEnvBank();
    void f_0970d8();

    int m0;
    unsigned short m4;
};

struct CEnvPlayer {
    CEnvPlayer() { f_0fa28c(this); }
    ~CEnvPlayer() {}
    int m0;
};

class CEnviron {
public:
    CEnviron();
    ~CEnviron();
    void f_096f68();
    int f_096f70();
    void f_096fdc();

    CEnvBank *m0;
    CEnvPlayer m4;
};

static CEnviron D_242dec;

/* @implements 0x096e18 us _ZN8CEnvironC2Ev
   WHAT IT DOES: Constructs the player sub-object, allocates the tone record and clears it
   (base object constructor). */
/* @implements 0x096e84 us _ZN8CEnvironC1Ev
   WHAT IT DOES: Same as the base object constructor (complete object constructor). */
CEnviron::CEnviron()
{
    m0 = new CEnvBank;
    m0->f_0970d8();
}

/* @implements 0x096ef0 us _ZN8CEnvironD2Ev
   WHAT IT DOES: Frees the tone record if there is one (base object destructor). */
/* @implements 0x096f2c us _ZN8CEnvironD1Ev
   WHAT IT DOES: Same as the base object destructor (complete object destructor). */
CEnviron::~CEnviron()
{
    if (m0) {
        delete m0;
        m0 = 0;
    }
}

/* @implements 0x096f68 us f_096f68
   WHAT IT DOES: Nothing (empty step). */
void CEnviron::f_096f68()
{
}

/* @implements 0x096f70 us f_096f70
   WHAT IT DOES: Starts the environment sound: plays the record's handle on the player with
   tone 0, looks up the handle's id, logs handle, id, tone and the player's result, and
   returns that result. */
int CEnviron::f_096f70()
{
    int handle = m0->m4;
    int ret = f_0fa354(&m4, handle, 0);
    int id;
    f_10d408(handle, &id);
    f_093f90("Sound: CEnviron: Start: handle:%d id:%d tone:%d ret:%d\n", handle, id, 0, ret);
    return ret;
}

/* @implements 0x096fdc us f_096fdc
   WHAT IT DOES: Logs and stops the environment sound. */
void CEnviron::f_096fdc()
{
    f_093f90("Sound: CEnviron: Stop\n");
    f_0fa7ac();
}

/* @implements 0x097004 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the global environment object at startup and destroys it at
   shutdown. */
/* @implements 0x097080 us _GLOBAL__I_
   WHAT IT DOES: Startup entry of the object file's static data. */
/* @implements 0x0970a0 us _GLOBAL__D_
   WHAT IT DOES: Shutdown entry of the object file's static data. */
