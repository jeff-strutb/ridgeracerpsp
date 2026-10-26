/* The Rally-X mini game's set up, shut down and screen set up (retail 0x0e7768 to 0x0e79b0).
   The game's package (D_1d8bb8) holds the texture "RallyXTex" and the six maps Map1 to Map6;
   the maps are kept in D_27ebd8 for the game. The screen set up turns the screen's flag word
   into the state bits passed to f_02ea2c, then writes the first display list commands for the
   sprites (through the list cursor of 0x0e79b0) and reports whether the two sound flags are set. */

class CPackage {
public:
    void *f_002acc(const char *name);
};
extern CPackage D_1d8bb8;

extern "C" {
void f_02e264(void *arg);
void *f_022d00(void *file, int id);
int f_001088(int id);
int f_02ea2c(int bits);
void f_021720(void);
void f_023158(int id);
void f_118738(int a, int b);
void f_1166d4(int n);
void f_021750(void);
int f_0216d8(void);
void f_0216e8(void *p);
void f_02ebc8(void);
void f_02e9e8(void);
void f_023250(int id);
int f_0e79bc(void);
void f_0e79b0(int p);
}

extern int D_1d88a0;        /* the game's texture-set id */
extern int D_27ebd4;        /* the result of f_001088 */
extern void *D_27ebd8[6];   /* the six maps */
extern int D_24518c;       /* the screen flag word */
extern signed char D_2400c3;
extern signed char D_2400c4;

/* @implements 0x0e7768 us f_0e7768
   WHAT IT DOES: Loads the game's texture "RallyXTex" from the package and uses it for the
   texture set, then loads the six maps into D_27ebd8, sets up the screen with the argument
   and stores the texture-set result in D_27ebd4. */
void f_0e7768(void *arg)
{
    void *tex = D_1d8bb8.f_002acc("RallyXTex");

    f_022d00(tex, 0x5000000);
    D_27ebd8[0] = D_1d8bb8.f_002acc("Map1");
    D_27ebd8[1] = D_1d8bb8.f_002acc("Map2");
    D_27ebd8[2] = D_1d8bb8.f_002acc("Map3");
    D_27ebd8[3] = D_1d8bb8.f_002acc("Map4");
    D_27ebd8[4] = D_1d8bb8.f_002acc("Map5");
    D_27ebd8[5] = D_1d8bb8.f_002acc("Map6");
    f_02e264(arg);
    D_27ebd4 = f_001088(D_1d88a0);
}

/* @draft 0x0e7858 us f_0e7858
   WHAT IT DOES: Sets up the screen. The flag word's bits are mapped to nine state bits (1 to
   0x200) which f_02ea2c takes; the display is set up, the first display list commands are
   written through the list cursor, and the result is 1 when both sound flags are set. */
int f_0e7858(void)
{
    int v = D_24518c;
    int a = 0;

    if (v & 0x10)
        a = 1;
    if (v & 0x40)
        a |= 2;
    if (v & 0x80)
        a |= 4;
    if (v & 0x20)
        a |= 8;
    if (v & 0x2000)
        a |= 0x10;
    if (v & 0x8)
        a |= 0x20;
    if (v & 0x200)
        a |= 0x40;
    if (v & 0x100)
        a |= 0x80;
    if (v & 0x4000)
        a |= 0x100;
    if (v & 0x1000)
        a |= 0x200;
    f_02ea2c(a);
    f_021720();
    f_023158(0x5000000);
    f_118738(0, 0);
    f_1166d4(4);
    f_021750();
    f_0e79b0(f_0216d8());
    f_02ebc8();
    {
        int *p = (int *)f_0e79bc();

        *p = 0xd4000000;
        p++;
        *p = 0xd5043ddf;
        f_0216e8(p + 1);
    }
    if (D_2400c3 && D_2400c4)
        return 1;
    return 0;
}

/* @implements 0x0e798c us f_0e798c
   WHAT IT DOES: Shuts the screen set up down: f_02e9e8 and the release of the texture set
   with f_023250. */
void f_0e798c(void)
{
    f_02e9e8();
    f_023250(0x5000000);
}
