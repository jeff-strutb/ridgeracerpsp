/* The sound pack globals (retail 0x114a4c to 0x114bec): the pack file directory reader
   (D_2826d4, 0x115800) and the preload pack reader (D_2826d8, 0x114bfc), constructed at
   start up, and the plain functions the sound code calls them through. */

class CPackFile;
class CPackPreload;

extern "C" {
void f_1157f8(CPackFile *p);    /* CPackFile's constructor */
void f_114bf4(CPackPreload *p); /* CPackPreload's constructor */
}

class CPackFile {
public:
    CPackFile() { f_1157f8(this); }
    ~CPackFile() {}
    int f_115800(void *data);
    int f_115834(void *data, int i);
    int f_1158a4(void *data);
};

class CPackPreload {
public:
    CPackPreload() { f_114bf4(this); }
    ~CPackPreload() {}
    int f_114bfc(void *data);
    int f_114c30(void *data);
    int f_114c64(void *data);
    int f_114ca4(void *data, int id);
};

CPackFile D_2826d4;
CPackPreload D_2826d8;

extern "C" {
/* @implements 0x114a4c us f_114a4c
   WHAT IT DOES: Returns the number of files in a pack file. */
int f_114a4c(void *data)
{
    return D_2826d4.f_115800(data);
}

/* @implements 0x114a70 us f_114a70
   WHAT IT DOES: Returns file i's offset in a pack file. */
int f_114a70(void *data, int i)
{
    return D_2826d4.f_115834(data, i);
}

/* @implements 0x114a9c us f_114a9c
   WHAT IT DOES: Returns a pack file's unit size. */
int f_114a9c(void *data)
{
    return D_2826d4.f_1158a4(data);
}

/* @implements 0x114ac0 us f_114ac0
   WHAT IT DOES: Returns a preload pack's unit size. */
int f_114ac0(void *data)
{
    return D_2826d8.f_114bfc(data);
}

/* @implements 0x114ae4 us f_114ae4
   WHAT IT DOES: Returns a preload pack's stream count. */
int f_114ae4(void *data)
{
    return D_2826d8.f_114c30(data);
}

/* @implements 0x114b08 us f_114b08
   WHAT IT DOES: Returns a preload pack's size. */
int f_114b08(void *data)
{
    return D_2826d8.f_114c64(data);
}

/* @implements 0x114b2c us f_114b2c
   WHAT IT DOES: Returns stream id's offset in a preload pack. */
int f_114b2c(void *data, int id)
{
    return D_2826d8.f_114ca4(data, id);
}
}

/* @implements 0x114b58 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the two pack readers at start up. */
/* @implements 0x114bac us _GLOBAL__I
   WHAT IT DOES: The start up entry for this file's static data. */
/* @implements 0x114bcc us _GLOBAL__D
   WHAT IT DOES: The shutdown entry for this file's static data. */
