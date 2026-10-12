/* The front end's screen manager (retail 0x017bd4 to 0x01908c). One global object drives the
   menu screens: it opens the screen layer for the requested menu, loads that menu's package,
   hands it the settings the game prepared, steps it until the player is done and closes it
   again. The object file also owns the menu objects themselves, the settings objects that are
   copied into them, the message text package and the loading screen; its static constructor
   and destructor build and tear them all down. */

void f_0030c8(void *loader, int n);
void f_005554(void *loader, int n);
int f_0056d0(void *loader);
const char *f_01c26c(const char *name);
void f_08a71c(int, int);
void f_08a998(void);
void f_092d10(void);
void f_09299c(void);
void f_096408(void *);
void f_097680(void *, int, int);

void f_07183c(void *);
void f_071d18(void *);
void f_075e70(void *);
void f_075f34(void *);
void f_075304(void *);
void f_0754a0(void *);
void f_07ab2c(void *);
void f_07aba8(void *);
void f_07a314(void *);
void f_07a390(void *);
void f_078bf8(void *);
void f_078c74(void *);
void f_079478(void *);
void f_0794f4(void *);
void f_07a558(void *);
void f_07a5d4(void *);
void f_07a744(void *);
void f_07a7c0(void *);
void f_0786b8(void *);
void f_078734(void *);
void f_07a88c(void *);
void f_07a908(void *);
void f_07a9d8(void *);
void f_07aa54(void *);
void f_0792a0(void *);
void f_07931c(void *);
void f_07a08c(void *);
void f_07a108(void *);

/* A data package: one archive file from the disc, whose entries are looked up by name. */
class CPackage {
public:
    CPackage() { m0 = -1; }
    ~CPackage() { f_0026cc(); }
    void f_00260c(const char *name, int a, int b);
    void f_0026cc();
    void f_002734(int a);
    void *f_002acc(const char *name);
    int m0;
    int m4[69];
};

/* The loader that owns the menu packages. */
CPackage *f_005a38(void *loader, const char *name);
extern char D_1dd6b0[];

namespace An {
/* The animation player part of a menu. */
class CSwgSub {
public:
    CSwgSub();
    virtual ~CSwgSub();
    virtual void s2();
    int m4[3];
};
}

namespace Select {
/* The base of every menu screen layer: it is given settings (v2), handed its animation and
   texture (v5) or only a new texture (v4), closed (v8) and asked what the player did (v10). */
class CBaseMenu {
public:
    CBaseMenu();
    virtual ~CBaseMenu();
    virtual void v2(void *msg, int arg);
    virtual void v3(void *msg, int arg);
    virtual void v4(void *tex);
    virtual void v5(void *swg, void *tex);
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual int v10(int what);
    int f_06c61c();
    void f_06c954(void *text, void *textTex);
    char m4[456 - 4];
};

class CStartMenu : public CBaseMenu {
public:
    class CSub : public An::CSwgSub {
    public:
        virtual void s2();
    };
    virtual void v2(void *msg, int arg);
    int m456;
    CSub sub;
    char m476[524 - 476];
};

class CLoading : public CBaseMenu {
public:
    class CSub : public An::CSwgSub {
    public:
        virtual void s2();
    };
    virtual void v2(void *msg, int arg);
    void f_076328(void *swg, void *tex);
    void f_07649c();
    CSub sub;
    bool m472;
    char m473[516 - 473];
};
}

/* The other three menus, built and destroyed by their own object files. */
struct MainMenu {
    MainMenu() { f_07183c(this); }
    ~MainMenu() { f_071d18(this); }
    void f_073fa8();
    char m[0x1dd4];
};
struct PauseMenu {
    PauseMenu() { f_075e70(this); }
    ~PauseMenu() { f_075f34(this); }
    char m[0x3f0];
};
struct ResultMenu {
    ResultMenu() { f_075304(this); }
    ~ResultMenu() { f_0754a0(this); }
    char m[0x110c];
};

/* The first word of every settings object is its vtable pointer, which a copy leaves alone. */
struct VtPtr {
    void *p;
    VtPtr &operator=(const VtPtr &) { return *this; }
};

/* The settings objects the game fills in and the screen manager hands to a menu. They share
   a base whose only field is a word every one of them carries. */
struct MenuData {
    VtPtr vt;
    int m4;
};
struct StartMenuData : MenuData {
    StartMenuData() { f_07ab2c(this); }
    ~StartMenuData() { f_07aba8(this); }
    int m8;
    bool m12;
};
struct ResultMenuHead : MenuData {
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
};
struct ResultMenuData : ResultMenuHead {
    ResultMenuData() { f_07a314(this); }
    ~ResultMenuData() { f_07a390(this); }
    int m32[24];
    int m128;
    int m132;
    int m136[12];
    int m184[15];
    int m244;
    int m248;
    int m252;
    int m256;
    int m260;
    int m264;
    unsigned short m268;
    short m270[5];
    int m280;
    int m284;
    bool m288;
    bool m289;
    bool m290;
    bool m291;
};
struct Data233c20 : MenuData {
    Data233c20() { f_078bf8(this); }
    ~Data233c20() { f_078c74(this); }
    int m8[12];
    bool m56;
    float m60;
    int m64;
};
struct Data233c64 : MenuData {
    Data233c64() { f_079478(this); }
    ~Data233c64() { f_0794f4(this); }
    bool m8;
};
struct Options : MenuData {
    Options() { f_07a558(this); }
    ~Options() { f_07a5d4(this); }
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    bool m28;
    bool m29;
    bool m30;
    char m31[8];
    char m39[18];
    char m57[18];
    bool m75;
    int m76;
    int m80;
    int m84[60];
};
struct Data233db4 : MenuData {
    Data233db4() { f_07a744(this); }
    ~Data233db4() { f_07a7c0(this); }
    int m8;
    int m12;
};
struct ScreenMsg : MenuData {
    ScreenMsg() { f_0786b8(this); }
    ~ScreenMsg() { f_078734(this); }
    bool m8;
    bool m9;
};
struct Data233dd0 : MenuData {
    Data233dd0() { f_07a88c(this); }
    ~Data233dd0() { f_07a908(this); }
    int m8;
    int m12;
    bool m16;
    int m20;
};
struct Data233de8 : MenuData {
    Data233de8() { f_07a9d8(this); }
    ~Data233de8() { f_07aa54(this); }
    bool m8;
    int m12;
    unsigned char m16;
    bool m17;
    bool m18;
    int m20;
};
struct Data233e00Head : MenuData {
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
    int m40;
    int m44;
    int m48;
};
struct Data233e00 : Data233e00Head {
    Data233e00() { f_0792a0(this); }
    ~Data233e00() { f_07931c(this); }
    int m52;
    int m56;
    int m60;
    int m64;
    int m68;
    int m72;
    int m76;
    int m80;
    int m84;
    int m88;
    bool m92;
    char m93[16];
    int m112;
    int m116;
    int m120;
    int m124;
};
struct Data233e80 : MenuData {
    Data233e80() { f_07a08c(this); }
    ~Data233e80() { f_07a108(this); }
    int m8;
    int m12[56];
};

/* The wireless result screen's player list, created while that menu is open. */
struct WirelessResult {
    int f_088b58(Select::CBaseMenu *menu);
    int f_088bc8();
    int f_088bd4();
    int f_088bdc();
    int m0;
    bool done;
    char m5[32 - 5];
};

extern int D_1d46f0;
extern int D_1d8920;
extern unsigned char D_2413b8;
extern char D_242cb0[];
extern char D_242e14[];

/* The screen manager. kind is the menu wanted (9 start, 10 main, 11 pause, 12 result, 13
   wireless result, 14 wireless result with the player list); phase steps through opening,
   loading, running and closing it. */
struct ScreenMgr {
    Select::CBaseMenu *layer;
    bool m4;
    bool m5;
    void *text;
    void *textTex;
    int phase;
    int request;
    int result;
    int kind;
    bool reopen;
    bool m33;

    void f_017be0();
    void f_017bfc();
    void f_017c88();
    void f_017cb8();
    void f_017ccc();
    void f_017d64();
    void f_017d94();
    void f_017de0();
    void f_017e1c(const StartMenuData &d);
    void f_017e40(const ResultMenuData &d);
    void f_018004(const Data233c20 &d);
    void f_018070(const Data233c64 &d);
    void f_01808c(const Options &d);
    void f_0182c0(const Data233db4 &d);
    void f_0182e4(const ScreenMsg &d);
    void f_018308(const Data233dd0 &d);
    void f_01833c(const Data233de8 &d);
    void f_018380(const Data233e00 &d);
    void f_0184e8(const Data233e80 &d);
    void f_018540();
    void f_01869c();
    void f_018784();
    int f_01896c();
    void f_018a48();
    void f_018abc(int k);
    void f_018af8();
    void f_018b04();
    void f_018b10();
    void f_018b48();
};

ScreenMgr D_2301b0;
CPackage D_2301d4;
Select::CStartMenu D_2302ec;
MainMenu D_2304f8;
PauseMenu D_2322cc;
ResultMenu D_2326bc;
WirelessResult *D_2337c4;
Select::CLoading D_2337c8;
CPackage D_2339cc;
void *D_233ae4;
void *D_233ae8;
StartMenuData D_233aec;
ResultMenuData D_233afc;
Data233c20 D_233c20;
Data233c64 D_233c64;
Options D_233c70;
Data233db4 D_233db4;
ScreenMsg D_233dc4;
Data233dd0 D_233dd0;
Data233de8 D_233de8;
Data233e00 D_233e00;
Data233e80 D_233e80;
int D_233f6c;

/* @implements 0x017bd4 us f_017bd4
   WHAT IT DOES: Returns the main menu object. */
MainMenu *f_017bd4()
{
    return &D_2304f8;
}

/* @implements 0x017be0 us f_017be0
   WHAT IT DOES: Marks the menu package as loaded (once), so the loading screen is not set up
   again. */
void ScreenMgr::f_017be0()
{
    if (!m4) {
        m4 = 1;
        m5 = 0;
    }
}

/* @implements 0x017bfc us f_017bfc
   WHAT IT DOES: Shows the loading screen. The first time after it was requested, it first
   hands the loading screen its animation and texture from the menu package. */
void ScreenMgr::f_017bfc()
{
    if (m5) {
        m5 = 0;
        void *swg = D_2301d4.f_002acc("Swg");
        D_2337c8.f_076328(swg, D_2301d4.f_002acc("SwgTex"));
    }
    D_2337c8.f_06c61c();
}

/* @implements 0x017c88 us f_017c88
   WHAT IT DOES: Asks for the loading screen to be shown again from the start. */
void ScreenMgr::f_017c88()
{
    m5 = 1;
    D_2337c8.m472 = 1;
    D_2337c8.f_07649c();
}

/* @implements 0x017cb8 us f_017cb8
   WHAT IT DOES: Clears the flag that the menu package is loaded. */
void ScreenMgr::f_017cb8()
{
    if (m4)
        m4 = 0;
}

/* @implements 0x017ccc us f_017ccc
   WHAT IT DOES: Loads the message list package for the console's language and looks up the
   message text and its texture, which every menu draws its words from. */
void ScreenMgr::f_017ccc()
{
    D_2339cc.f_00260c(f_01c26c("MsgList"), 0, 0);
    D_2339cc.f_002734(0);
    D_233ae4 = D_2339cc.f_002acc("Text");
    D_233ae8 = D_2339cc.f_002acc("TextTex");
    text = D_233ae4;
    textTex = D_233ae8;
}

/* @implements 0x017d64 us f_017d64
   WHAT IT DOES: Releases the message list package. */
void ScreenMgr::f_017d64()
{
    D_2339cc.f_0026cc();
    D_233ae4 = 0;
    D_233ae8 = 0;
}

/* @implements 0x017d94 us f_017d94
   WHAT IT DOES: Sets the screen manager up when the game starts: no menu, nothing requested,
   then loads the message text and the menu package. */
void ScreenMgr::f_017d94()
{
    request = 6;
    kind = -1;
    phase = 0;
    result = 0;
    m4 = 0;
    layer = 0;
    f_017ccc();
    f_017be0();
}

/* @implements 0x017de0 us f_017de0
   WHAT IT DOES: Shuts the screen manager down and releases its packages. */
void ScreenMgr::f_017de0()
{
    request = 6;
    phase = 0;
    result = 0;
    f_017cb8();
    f_017d64();
}

/* @implements 0x017e1c us f_017e1c
   WHAT IT DOES: Stores the settings for the start menu. */
void ScreenMgr::f_017e1c(const StartMenuData &d)
{
    D_233aec = d;
}

/* @draft 0x017e40 us f_017e40
   WHAT IT DOES: Stores the settings for the race result menu.
   Remaining difference: the copy after the arrays (offsets 244 to 291) is scheduled with every
   load first and needs s1 to s4; retail interleaves the loads and stores and saves only s0.
   As one flat class the copy is not inlined at all (more than 22 member statements). */
void ScreenMgr::f_017e40(const ResultMenuData &d)
{
    D_233afc = d;
}

/* @implements 0x018004 us f_018004
   WHAT IT DOES: Stores one block of the main menu's settings. */
void ScreenMgr::f_018004(const Data233c20 &d)
{
    D_233c20 = d;
}

/* @implements 0x018070 us f_018070
   WHAT IT DOES: Stores one block of the main menu's settings. */
void ScreenMgr::f_018070(const Data233c64 &d)
{
    D_233c64 = d;
}

/* @implements 0x01808c us f_01808c
   WHAT IT DOES: Stores the option settings shown by the main menu. */
void ScreenMgr::f_01808c(const Options &d)
{
    D_233c70 = d;
}

/* @implements 0x0182c0 us f_0182c0
   WHAT IT DOES: Stores one block of the main menu's settings. */
void ScreenMgr::f_0182c0(const Data233db4 &d)
{
    D_233db4 = d;
}

/* @implements 0x0182e4 us f_0182e4
   WHAT IT DOES: Stores the notice the main menu shows. */
void ScreenMgr::f_0182e4(const ScreenMsg &d)
{
    D_233dc4 = d;
}

/* @implements 0x018308 us f_018308
   WHAT IT DOES: Stores the settings for the pause menu. */
void ScreenMgr::f_018308(const Data233dd0 &d)
{
    D_233dd0 = d;
}

/* @implements 0x01833c us f_01833c
   WHAT IT DOES: Stores the first block of the result menus' settings. */
void ScreenMgr::f_01833c(const Data233de8 &d)
{
    D_233de8 = d;
}

/* @draft 0x018380 us f_018380
   WHAT IT DOES: Stores the second block of the result menus' settings.
   Remaining difference: retail copies the words 8 to 88 in one scattered schedule (8 to 20
   loaded first and stored together last, the pairs 24/28, 36/40, 44/48, 52/56 stored
   together); the member grouping that gives it is not found. As one flat class the copy is
   not inlined (more than 22 member statements). */
void ScreenMgr::f_018380(const Data233e00 &d)
{
    D_233e00 = d;
}

/* @implements 0x0184e8 us f_0184e8
   WHAT IT DOES: Stores the third block of the result menus' settings. */
void ScreenMgr::f_0184e8(const Data233e80 &d)
{
    D_233e80 = d;
}

/* @implements 0x018540 us f_018540
   WHAT IT DOES: Hands the open menu the settings stored for it. */
void ScreenMgr::f_018540()
{
    switch (kind) {
    case 9:
        layer->v2(&D_233aec, 0);
        break;
    case 10:
        layer->v2(&D_233afc, 0);
        layer->v2(&D_233c20, 0);
        layer->v2(&D_233c64, 0);
        layer->v2(&D_233c70, 0);
        layer->v2(&D_233db4, 0);
        layer->v2(&D_233dc4, 0);
        break;
    case 11:
        layer->v2(&D_233dd0, 0);
        break;
    case 12:
    case 13:
    case 14:
        layer->v2(&D_233de8, 0);
        layer->v2(&D_233e00, 0);
        layer->v2(&D_233e80, 0);
        break;
    }
}

/* @implements 0x01869c us f_01869c
   WHAT IT DOES: Makes the requested menu the current screen layer and tells the package
   loader which menu package to load. */
void ScreenMgr::f_01869c()
{
    switch (kind) {
    case 9:
        f_0030c8(D_1dd6b0, 10);
        layer = &D_2302ec;
        break;
    case 10:
        f_0030c8(D_1dd6b0, 12);
        layer = (Select::CBaseMenu *)&D_2304f8;
        break;
    case 11:
        f_0030c8(D_1dd6b0, 14);
        layer = (Select::CBaseMenu *)&D_2322cc;
        break;
    case 12:
    case 14:
        f_0030c8(D_1dd6b0, 13);
        layer = (Select::CBaseMenu *)&D_2326bc;
        break;
    case 13:
        f_0030c8(D_1dd6b0, 15);
        layer = (Select::CBaseMenu *)&D_2326bc;
        break;
    }
    f_005554(D_1dd6b0, 1);
}

/* @implements 0x018784 us f_018784
   WHAT IT DOES: Once the menu package is loaded, gives the menu its animation and texture and
   the message text (or, when the menu is only being reopened, a new texture and a sound), and
   for the wireless result menu creates the list of players. Unless reopened, the menu then
   gets its settings. */
void ScreenMgr::f_018784()
{
    CPackage *pkg = 0;

    switch (kind) {
    case 9:
        pkg = f_005a38(D_1dd6b0, f_01c26c("StartMenu"));
        break;
    case 10:
        pkg = f_005a38(D_1dd6b0, f_01c26c("MainMenu"));
        break;
    case 11:
        pkg = f_005a38(D_1dd6b0, f_01c26c("PauseMenu"));
        break;
    case 12:
        pkg = f_005a38(D_1dd6b0, f_01c26c("ResultMenu"));
        break;
    case 13:
        pkg = f_005a38(D_1dd6b0, f_01c26c("WirelessResultMenu"));
        break;
    case 14:
        pkg = f_005a38(D_1dd6b0, f_01c26c("ResultMenu"));
        break;
    }
    if (!reopen) {
        void *swg;
        if (kind == 10)
            swg = D_2301d4.f_002acc("MainSwg");
        else
            swg = pkg->f_002acc("Swg");
        layer->v5(swg, pkg->f_002acc("SwgTex"));
        layer->f_06c954(D_233ae4, D_233ae8);
    } else {
        layer->v4(pkg->f_002acc("SwgTex"));
        f_097680(D_242e14, 8, -1);
    }
    switch (kind) {
    case 10:
        break;
    case 14:
        f_096408(D_242cb0);
        WirelessResult *w = new WirelessResult;
        D_2337c4 = w;
        w->f_088b58(layer);
        f_08a71c(12, 1);
        m33 = 0;
        break;
    }
    if (!reopen)
        f_018540();
    reopen = 0;
}

/* @implements 0x01896c us f_01896c
   WHAT IT DOES: Runs one frame of the open menu and returns what it reports (zero while the
   player is still busy). The wireless result menu with the player list first waits until the
   list is done or the player presses a button, then frees the list and turns into the plain
   result menu. */
int ScreenMgr::f_01896c()
{
    if (kind == 14) {
        D_2337c4->f_088bd4();
        D_2337c4->f_088bdc();
        if (!m33) {
            if (D_2337c4->done || (D_1d8920 & 2) || D_2413b8)
                m33 = 1;
        }
        if (!m33 || !D_1d46f0)
            return 0;
        D_2337c4->f_088bc8();
        delete D_2337c4;
        f_08a998();
        kind = 12;
    }
    return layer->f_06c61c();
}

/* @implements 0x018a48 us f_018a48
   WHAT IT DOES: Closes the open menu (unless it is only being reopened) and forgets which menu
   was open; closing the main menu also stops two of its sound and display effects. */
void ScreenMgr::f_018a48()
{
    if (!reopen)
        layer->v8();
    if (kind == 10) {
        f_092d10();
        f_09299c();
    }
    kind = -1;
}

/* @implements 0x018abc us f_018abc
   WHAT IT DOES: Requests a menu. If that menu is already open it is only given its settings
   again. */
void ScreenMgr::f_018abc(int k)
{
    if (kind == k) {
        f_018540();
    } else {
        request = 7;
        kind = k;
        result = 0;
    }
}

/* @implements 0x018af8 us f_018af8
   WHAT IT DOES: Asks the open menu to finish. */
void ScreenMgr::f_018af8()
{
    request = 8;
}

/* @implements 0x018b04 us f_018b04
   WHAT IT DOES: Marks the next menu as a reopening of the current one. */
void ScreenMgr::f_018b04()
{
    reopen = 1;
}

/* @implements 0x018b10 us f_018b10
   WHAT IT DOES: Lets the main menu, if it is the one open, react to a change of screen. */
void ScreenMgr::f_018b10()
{
    if (kind == 10)
        D_2304f8.f_073fa8();
}

/* @implements 0x018b48 us f_018b48
   WHAT IT DOES: Steps the screen manager once a frame: waits for a menu request, opens the
   menu, waits for its package, sets it up, runs it until the player is done or it is asked
   to finish, then, after the package loader is idle (and at least three frames later),
   closes it and waits for the next request. */
void ScreenMgr::f_018b48()
{
    for (;;) {
        switch (phase) {
        case 0:
            if (request != 7)
                return;
            request = 6;
            phase = 1;
            break;
        case 1:
            f_01869c();
            phase = 2;
            break;
        case 2:
            if (f_0056d0(D_1dd6b0))
                return;
            phase = 3;
            break;
        case 3:
            f_018784();
            phase = 4;
            break;
        case 4:
            if (request == 8) {
                request = 6;
                result = 1;
            } else {
                result = f_01896c();
            }
            if (!result)
                return;
            phase = 5;
            D_233f6c = 0;
            return;
        case 5:
            D_233f6c++;
            if (f_0056d0(D_1dd6b0) && kind != 9)
                return;
            if (D_233f6c < 3)
                return;
            f_018a48();
            phase = 0;
            break;
        }
    }
}

/* @implements 0x018cac us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, builds the menus, the loading screen, the two packages (each
   starting with no file) and the settings objects; at shutdown, destroys them in reverse. */

/* @implements 0x018f8c us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x018fac us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */

/* @implements 0x018fcc us _ZN6Select8CLoadingC1Ev
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The loading screen's constructor as the startup code calls it. */

/* @implements 0x01902c us _ZN6Select10CStartMenuC1Ev
   (the compiler emits it outside .text, in a link once section)
   WHAT IT DOES: The start menu's constructor as the startup code calls it. */
