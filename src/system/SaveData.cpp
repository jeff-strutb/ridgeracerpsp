/* The memory stick and the system save and load dialog (retail 0x006040 to 0x0067b4): watching
   the stick, measuring its free space, and the one save data request the game hands to the
   system utility. The two functions at 0x006774 and 0x006794 are the object file's own static
   constructor and destructor entry points, which the compiler generates. */

#include <stdio.h>
#include <string.h>
#include "psp/kernel.h"

extern "C" {
int sceIoDevctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
int sceUtilitySavedataInitStart(void *params);
int sceUtilitySavedataGetStatus(void);
int sceUtilitySavedataUpdate(int unknown);
int sceUtilitySavedataShutdownStart(void);
}

int f_006024(int arg1, int arg2, void *common);
int f_01c260(void);
const char *f_10bdac(void);
void f_021b9c(void);

/* The part of the main loop job this object file reads: a flag byte set while the game is
   held (the system menu or a suspend) and the utility dialog must not be advanced. */
struct MainLoopJobView {
    char m0[14];
    unsigned char held;
};
extern MainLoopJobView *D_1d88a0;

struct MsSize {
    unsigned int maxClusters;
    unsigned int m4;
    unsigned int freeClusters;
    unsigned int sectorSize;
    unsigned int sectorCount;
};

struct SavedataFileData {
    void *buf;
    int bufSize;
    int size;
    int unknown;
};

struct SavedataSFOParam {
    char title[128];
    char savedataTitle[128];
    char detail[1024];
    unsigned char parentalLevel;
    char pad[3];
};

struct SavedataParam {
    int size;
    int language;
    int buttonSwap;
    int graphicsThread;
    int accessThread;
    int fontThread;
    int soundThread;
    int result;
    int reserved[4];
    int mode;
    int bind;
    int overwrite;
    char gameName[16];
    char saveName[20];
    char *saveNameList;
    char fileName[16];
    void *dataBuf;
    int dataBufSize;
    int dataSize;
    SavedataSFOParam sfoParam;
    SavedataFileData icon0FileData;
    SavedataFileData icon1FileData;
    SavedataFileData pic1FileData;
    SavedataFileData snd0FileData;
    int focus;
};

class CSaveData {
public:
    CSaveData() { f_00612c(); }
    ~CSaveData() {}
    void f_00612c();
    void f_0061a0(void *buf, int bufSize, int size);
    void f_0061b0(const char *title, const char *savedataTitle, const char *detail);
    void f_006260(void *buf, int size);
    void f_006274(void *buf, int size);
    void f_006288(void *buf, int size);
    void f_00629c();
    void f_0062ac();
    void f_006300(int n);
    void f_006328();
    void f_00634c(int n);
    void f_006394(int n);
    void f_0063b4(int n);
    void f_0063d8(int n);
    void f_0063fc(int n);
    void f_006420(int first, int count);
    void f_0064dc(int first, int count);
    void f_00659c(int first, int count);
    void f_006658();
    int f_006664();
    int f_006680();

    SavedataParam param;
    int result;
    char names[1024][20];
};

/* @implements 0x006040 us f_006040
   WHAT IT DOES: Registers a callback with the memory stick driver so the game hears when a
   stick is inserted or removed. */
void f_006040(void)
{
    SceUID cb = sceKernelCreateCallback("MS", f_006024, 0);
    sceIoDevctl("mscmhc0:", 0x02015804, &cb, 4, 0, 0);
}

/* @draft 0x006094 us f_006094
   WHAT IT DOES: Returns the free space on the memory stick in kilobytes, or -1 when the stick
   cannot be asked. */
int f_006094(void)
{
    MsSize info;
    MsSize *p = &info;
    int cluster;

    if (sceIoDevctl("ms0:", 0x02425818, &p, 4, 0, 0) != 0)
        return -1;
    cluster = info.sectorSize * info.sectorCount;
    if (cluster < 1024)
        return info.freeClusters * cluster / 1024;
    return info.freeClusters * (cluster / 1024);
}

/* @implements 0x00612c us f_00612c
   WHAT IT DOES: Clears the save data request and fills in the dialog's common settings: the
   console's language (one language the dialog lacks falls back to English), the confirm
   button and the four utility thread priorities. */
void CSaveData::f_00612c()
{
    int language;

    memset(&param, 0, sizeof(param));
    param.size = sizeof(param);
    language = f_01c260();
    if (language == 6)
        language = 1;
    param.language = language;
    param.buttonSwap = 1;
    param.graphicsThread = 17;
    param.accessThread = 19;
    param.fontThread = 18;
    param.soundThread = 16;
}

/* @implements 0x0061a0 us f_0061a0
   WHAT IT DOES: Sets the buffer the saved game is written from or read into. */
void CSaveData::f_0061a0(void *buf, int bufSize, int size)
{
    param.dataBuf = buf;
    param.dataBufSize = bufSize;
    param.dataSize = size;
}

/* @draft 0x0061b0 us f_0061b0
   WHAT IT DOES: Sets the three texts the system shows for the save (the game title, the save's
   title and its details) and marks it suitable for all ages. */
void CSaveData::f_0061b0(const char *title, const char *savedataTitle, const char *detail)
{
    memcpy(param.sfoParam.title, title, strlen(title) + 1);
    memcpy(param.sfoParam.savedataTitle, savedataTitle, strlen(savedataTitle) + 1);
    memcpy(param.sfoParam.detail, detail, strlen(detail) + 1);
    param.sfoParam.parentalLevel = 1;
}

/* @implements 0x006260 us f_006260
   WHAT IT DOES: Sets the icon image shown for the save. */
void CSaveData::f_006260(void *buf, int size)
{
    param.icon0FileData.buf = buf;
    param.icon0FileData.bufSize = size;
    param.icon0FileData.size = size;
    param.icon0FileData.unknown = 0;
}

/* @implements 0x006274 us f_006274
   WHAT IT DOES: Sets the animated icon shown for the save. */
void CSaveData::f_006274(void *buf, int size)
{
    param.icon1FileData.buf = buf;
    param.icon1FileData.bufSize = size;
    param.icon1FileData.size = size;
    param.icon1FileData.unknown = 0;
}

/* @implements 0x006288 us f_006288
   WHAT IT DOES: Sets the background picture shown behind the save. */
void CSaveData::f_006288(void *buf, int size)
{
    param.pic1FileData.buf = buf;
    param.pic1FileData.bufSize = size;
    param.pic1FileData.size = size;
    param.pic1FileData.unknown = 0;
}

/* @implements 0x00629c us f_00629c
   WHAT IT DOES: Gives the save no background sound. */
void CSaveData::f_00629c()
{
    param.snd0FileData.buf = 0;
    param.snd0FileData.bufSize = 0;
    param.snd0FileData.size = 0;
}

/* @implements 0x0062ac us f_0062ac
   WHAT IT DOES: Copies the game's product code into the request as the save's game name. */
void CSaveData::f_0062ac()
{
    int n = strlen(f_10bdac());
    memcpy(param.gameName, f_10bdac(), n);
    param.gameName[n] = 0;
}

/* @implements 0x006300 us f_006300
   WHAT IT DOES: Names the save slot by its number, as three digits. */
void CSaveData::f_006300(int n)
{
    sprintf(param.saveName, "%03d", n);
}

/* @implements 0x006328 us f_006328
   WHAT IT DOES: Names the file inside the save folder. */
void CSaveData::f_006328()
{
    sprintf(param.fileName, "DATA.BIN");
}

/* @implements 0x00634c us f_00634c
   WHAT IT DOES: Fills in the game name, the slot and the file name for one slot, and puts the
   dialog's cursor on its default entry. */
void CSaveData::f_00634c(int n)
{
    f_0062ac();
    f_006300(n);
    f_006328();
    param.focus = 0;
}

/* @implements 0x006394 us f_006394
   WHAT IT DOES: Prepares an automatic load of one slot. */
void CSaveData::f_006394(int n)
{
    param.mode = 0;
    f_00634c(n);
}

/* @implements 0x0063b4 us f_0063b4
   WHAT IT DOES: Prepares an automatic save to one slot. */
void CSaveData::f_0063b4(int n)
{
    param.mode = 1;
    f_00634c(n);
}

/* @implements 0x0063d8 us f_0063d8
   WHAT IT DOES: Prepares a load of one slot through the dialog. */
void CSaveData::f_0063d8(int n)
{
    param.mode = 2;
    f_00634c(n);
}

/* @implements 0x0063fc us f_0063fc
   WHAT IT DOES: Prepares a save to one slot through the dialog. */
void CSaveData::f_0063fc(int n)
{
    param.mode = 3;
    f_00634c(n);
}

/* @implements 0x006420 us f_006420
   WHAT IT DOES: Prepares a load dialog that lists count slots numbered from first, so the
   player picks which save to load. */
void CSaveData::f_006420(int first, int count)
{
    int i;

    param.mode = 4;
    f_0062ac();
    for (i = 0; i < count; i++)
        sprintf(names[i], "%03d", first + i);
    if (i < 1024)
        names[i][0] = 0;
    param.saveNameList = names[0];
    f_006328();
}

/* @implements 0x0064dc us f_0064dc
   WHAT IT DOES: Prepares a save dialog that lists count slots numbered from first, so the
   player picks where to save, with the cursor on the first entry. */
void CSaveData::f_0064dc(int first, int count)
{
    int i;

    param.mode = 5;
    f_0062ac();
    for (i = 0; i < count; i++)
        sprintf(names[i], "%03d", first + i);
    if (i < 1024)
        names[i][0] = 0;
    param.saveNameList = names[0];
    f_006328();
    param.focus = 0;
}

/* @implements 0x00659c us f_00659c
   WHAT IT DOES: Prepares a delete dialog that lists count slots numbered from first. */
void CSaveData::f_00659c(int first, int count)
{
    int i;

    param.mode = 6;
    f_0062ac();
    for (i = 0; i < count; i++)
        sprintf(names[i], "%03d", first + i);
    if (i < 1024)
        names[i][0] = 0;
    param.saveNameList = names[0];
    f_006328();
}

/* @implements 0x006658 us f_006658
   WHAT IT DOES: Switches the request to the size query mode. */
void CSaveData::f_006658()
{
    param.mode = 7;
}

/* @implements 0x006664 us f_006664
   WHAT IT DOES: Opens the system save data dialog with the prepared request. */
int CSaveData::f_006664()
{
    return sceUtilitySavedataInitStart(&param);
}

/* @draft 0x006680 us f_006680
   WHAT IT DOES: Advances the save data dialog by one frame (not while the game is held). When
   the dialog has closed it keeps the outcome and returns 1; while it is on screen it draws it;
   when the player has finished it starts closing it. */
int CSaveData::f_006680()
{
    int r;

    if (D_1d88a0->held)
        return 0;
    f_021b9c();
    r = 0;
    switch (sceUtilitySavedataGetStatus()) {
    case 0:
        result = param.result;
        r = 1;
        break;
    case 2:
        r = sceUtilitySavedataUpdate(1);
        break;
    case 3:
        r = sceUtilitySavedataShutdownStart();
        break;
    }
    return r;
}

/* @implements 0x006728 us f_006728
   WHAT IT DOES: Does nothing. */
void f_006728(void)
{
}

CSaveData D_1e38f4;

/* @implements 0x006730 us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, prepares the save data request's common settings. */

/* @implements 0x006774 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x006794 us _GLOBAL__D_
   WHAT IT DOES: The shutdown entry for this file's static data. */
