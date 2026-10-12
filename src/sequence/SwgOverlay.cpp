/* The Swg overlay (retail 0x017968 to 0x017bd4): the scene object that shows the "Swg" scene
   with its "SwgTex" textures over the race, started and stopped with the race effects, and
   polled each frame for the message it produces. Also the empty setup of the race setup's car
   slots and the accessor of the overlay object. */

extern "C" {
void f_075e70(void *);
void f_075f34(void *);
void f_07a88c(void *);
void f_07a908(void *);
void f_09299c(void);
}

/* The two players' cars of the race setup. */
struct Slot {
    int a;
    int b;
};
struct Cars {
    Slot e[2];
    void f_017968();
};

/* A message read from the overlay (made and destroyed by the message code). */
struct SwgMessage {
    int m0;
    int m4;
    int value;
    char m12[20];
    SwgMessage() { f_07a88c(this); }
    ~SwgMessage() { f_07a908(this); }
    void f_07a968();
};

/* The overlay scene object (made and destroyed by the scene code). */
class CSwg {
public:
    char m0[0x3f0];
    CSwg() { f_075e70(this); }
    ~CSwg() { f_075f34(this); }
    int f_06c61c();
    void f_06c91c();
    void f_06c954(int a, int b);
    void f_0760a0(SwgMessage *m, int a);
    void f_0760fc(int scene, int tex);
    void f_076290();
};

/* The part of the sequence manager used here: it finds a scene by name. */
class CSequence {
public:
    int f_005c34(const char *name);
};

/* The part of the screen object used here. */
struct Screen {
    int m0[2];
    int m8;
    int m12;
};

extern CSequence D_1dd6b0;
extern Screen D_2301b0;
extern bool D_2301ac;
extern unsigned char D_1d1650;

CSwg D_22fdbc;

/* @implements 0x017968 us f_017968
   WHAT IT DOES: Sets up the race setup's car slots: nothing to do. */
void Cars::f_017968()
{
}

/* @implements 0x017970 us f_017970
   WHAT IT DOES: Returns the overlay object. */
CSwg *f_017970()
{
    return &D_22fdbc;
}

/* @implements 0x01797c us f_01797c
   WHAT IT DOES: Starts the overlay once: finds the "Swg" scene and its "SwgTex" textures in
   the sequence manager, loads them into the overlay and places it on the screen. */
void f_01797c()
{
    if (D_2301ac)
        return;
    D_2301ac = 1;
    D_1d1650 = 0;
    int scene = D_1dd6b0.f_005c34("Swg");
    int tex = D_1dd6b0.f_005c34("SwgTex");
    D_22fdbc.f_0760fc(scene, tex);
    D_22fdbc.f_06c954(D_2301b0.m8, D_2301b0.m12);
}

/* @implements 0x017a20 us f_017a20
   WHAT IT DOES: One frame of the overlay: after a message was taken last frame it lets the
   overlay go on; then, when the overlay has a message ready, reads it and returns its value
   (0 when there is none). */
int f_017a20()
{
    int r;

    if (D_1d1650) {
        D_1d1650 = 0;
        D_22fdbc.f_06c91c();
    }
    if (!D_22fdbc.f_06c61c())
        return 0;
    SwgMessage m;
    m.f_07a968();
    D_22fdbc.f_0760a0(&m, 0);
    r = m.value;
    D_1d1650 = 1;
    return r;
}

/* @implements 0x017ad8 us f_017ad8
   WHAT IT DOES: Stops the overlay when it is running and frees its scene. */
void f_017ad8()
{
    if (!D_2301ac)
        return;
    D_2301ac = 0;
    D_22fdbc.f_076290();
    f_09299c();
}

/* @implements 0x017b18 us __static_initialization_and_destruction_0
   WHAT IT DOES: Builds the overlay object at program start and tears it down at exit. */

/* @implements 0x017b94 us _GLOBAL__I_
   WHAT IT DOES: The program-start hook that builds the overlay object. */

/* @implements 0x017bb4 us _GLOBAL__D_
   WHAT IT DOES: The program-exit hook that tears it down. */
