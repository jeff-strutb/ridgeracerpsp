/* The menu settings objects (retail 0x076f98 to 0x07ab80): the base Select::CMenuData and the
   settings object of every menu, each with its constructors, destructors and Init, which sets
   the menu's id in the base word and resets the menu's own fields. The constructors run Init
   directly. Functions are in retail order, which is this file's definition order. */

extern "C" void *memset(void *, int, unsigned int);

/* The music text table: three lists of 40 text ids (titles, artists, and the third list),
   indexed by track number. */
struct MusicText {
    int title[40];
    int artist[40];
    int third[40];
};

extern "C" {

/* @implements 0x077b0c us f_077b0c
   WHAT IT DOES: Maps a disc (1 to 5) and a track on it (1 to 7) to a track number: tracks 1 to
   6 of disc n are 6(n-1)+1 to 6n, track 7 of disc n is 30+n. Disc 6 gives 255; anything else
   gives 0. */
int f_077b0c(MusicText *t, int disc, int track)
{
    if (disc == 7)
        return 0;
    if (disc == 6)
        return 255;
    switch (disc) {
    case 1:
        switch (track) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 6:
            return 6;
        case 7:
            return 31;
        }
        break;
    case 2:
        switch (track) {
        case 1:
            return 7;
        case 2:
            return 8;
        case 3:
            return 9;
        case 4:
            return 10;
        case 5:
            return 11;
        case 6:
            return 12;
        case 7:
            return 32;
        }
        break;
    case 3:
        switch (track) {
        case 1:
            return 13;
        case 2:
            return 14;
        case 3:
            return 15;
        case 4:
            return 16;
        case 5:
            return 17;
        case 6:
            return 18;
        case 7:
            return 33;
        }
        break;
    case 4:
        switch (track) {
        case 1:
            return 19;
        case 2:
            return 20;
        case 3:
            return 21;
        case 4:
            return 22;
        case 5:
            return 23;
        case 6:
            return 24;
        case 7:
            return 34;
        }
        break;
    case 5:
        switch (track) {
        case 1:
            return 25;
        case 2:
            return 26;
        case 3:
            return 27;
        case 4:
            return 28;
        case 5:
            return 29;
        case 6:
            return 30;
        case 7:
            return 35;
        }
        break;
    }
    return 0;
}

/* @implements 0x077d38 us f_077d38
   WHAT IT DOES: Maps a track number (1 to 48) to its slot in a repeating order of twelve:
   7, 9, 4, 10, 3, 5, 8, 11, 2, 6, 1, 12; 0 for anything else. */
int f_077d38(MusicText *t, int n)
{
    switch (n) {
    case 11: case 23: case 35: case 47:
        return 1;
    default:
        return 0;
    case 1: case 13: case 25: case 37:
        return 7;
    case 2: case 14: case 26: case 38:
        return 9;
    case 3: case 15: case 27: case 39:
        return 4;
    case 4: case 16: case 28: case 40:
        return 10;
    case 5: case 17: case 29: case 41:
        return 3;
    case 6: case 18: case 30: case 42:
        return 5;
    case 7: case 19: case 31: case 43:
        return 8;
    case 8: case 20: case 32: case 44:
        return 11;
    case 9: case 21: case 33: case 45:
        return 2;
    case 10: case 22: case 34: case 46:
        return 6;
    case 12: case 24: case 36: case 48:
        return 12;
    }
}

/* @implements 0x077dc4 us f_077dc4
   WHAT IT DOES: Returns the text id of entry n of the 0x01036e10 text block. */
int f_077dc4(MusicText *t, int n)
{
    return n + 0x01036e10;
}

/* @implements 0x077dd4 us f_077dd4
   WHAT IT DOES: Returns the text id of entry n of the 0x01038198 text block. */
int f_077dd4(MusicText *t, int n)
{
    return n + 0x01038198;
}

/* @implements 0x077de4 us f_077de4
   WHAT IT DOES: Returns the text id of a disc's track from list which (0 titles, 1 artists, 2
   the third list); 0 for any other list. */
int f_077de4(MusicText *t, int disc, int track, int which)
{
    switch (which) {
    case 0:
        return t->title[f_077b0c(t, disc, track)];
    case 1:
        return t->artist[f_077b0c(t, disc, track)];
    case 2:
        return t->third[f_077b0c(t, disc, track)];
    }
    return 0;
}

/* @implements 0x077e74 us f_077e74
   WHAT IT DOES: Returns entry n of list which (0 titles, 1 artists, 2 the third list); 0 for
   any other list. */
int f_077e74(MusicText *t, int n, int which)
{
    switch (which) {
    case 0:
        return t->title[n];
    case 1:
        return t->artist[n];
    case 2:
        return t->third[n];
    }
    return 0;
}

/* @implements 0x077ecc us f_077ecc
   WHAT IT DOES: Fills the music text table: clears all three lists, numbers titles 1 to 35 and
   third-list entries 1 to 30 from their text blocks (31 to 35 share one id), numbers artists 1
   to 6 and sets the rest of the artists one by one. */
void f_077ecc(MusicText *t)
{
    int i;

    for (i = 0; i < 40; i++) {
        t->title[i] = 0;
        t->artist[i] = 0;
        t->third[i] = 0;
    }
    for (i = 1; i < 36; i++)
        t->title[i] = i + 0x010371ff;
    for (i = 1; i < 31; i++)
        t->third[i] = i + 0x06f95eb0;
    for (; i < 36; i++)
        t->third[i] = 0x06f95edb;
    for (i = 1; i < 7; i++)
        t->artist[i] = i + 0x010375e0;
    t->artist[7] = 0x010375e3;
    t->artist[8] = 0x010375e6;
    t->artist[9] = 0x010375e7;
    t->artist[10] = 0x010375e8;
    t->artist[11] = 0x010375e9;
    t->artist[12] = 0x010375ea;
    t->artist[13] = 0x010375e1;
    t->artist[14] = 0x010375e1;
    t->artist[15] = 0x010375e2;
    t->artist[16] = 0x010375e5;
    t->artist[17] = 0x010375e8;
    t->artist[18] = 0x010375e9;
    t->artist[19] = 0x010375ef;
    t->artist[20] = 0x010375f0;
    t->artist[21] = 0x010375f1;
    t->artist[22] = 0x010375f2;
    t->artist[23] = 0x010375f3;
    t->artist[24] = 0x010375f3;
    t->artist[25] = 0x010375f3;
    t->artist[26] = 0x010375f3;
    t->artist[27] = 0x010375f3;
    t->artist[28] = 0x010375f4;
    t->artist[29] = 0x010375f4;
    t->artist[30] = 0x010375f4;
}

}


namespace Select {

struct CMenuData {
    CMenuData();
    virtual ~CMenuData();
    virtual void Init() = 0;
    int Type() const;
    int m4;
};
struct CTextureMenuData : CMenuData {
    CTextureMenuData();
    ~CTextureMenuData();
    void Init();
    int m8;
};
struct CCarObjMenuData : CMenuData {
    CCarObjMenuData();
    ~CCarObjMenuData();
    void Init();
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
};
struct CCarGetObjMenuData : CMenuData {
    CCarGetObjMenuData();
    ~CCarGetObjMenuData();
    void Init();
    int m8[16][5];
};
struct CCarGetNumberMenuData : CMenuData {
    CCarGetNumberMenuData();
    ~CCarGetNumberMenuData();
    void Init();
    int m8[5];
    int m28;
};
struct CSaveMenuData : CMenuData {
    CSaveMenuData();
    ~CSaveMenuData();
    void Init();
    bool m8;
    bool m9;
};
struct CGhostSaveMenuData : CMenuData {
    CGhostSaveMenuData();
    ~CGhostSaveMenuData();
    void Init();
    bool m8;
    bool m9;
    int m12;
};
struct CSoundMenuData : CMenuData {
    CSoundMenuData();
    ~CSoundMenuData();
    void Init();
    bool m8;
    int m12;
    int m16;
    int m20;
    int m24;
};
struct CBestTimeData : CMenuData {
    CBestTimeData();
    ~CBestTimeData();
    void Init();
    char m8[0xd200];
};
struct CMainMenuSetData : CMenuData {
    CMainMenuSetData();
    ~CMainMenuSetData();
    void Init();
    int m8[12];
    bool m56;
    int m60;
    int m64;
};
struct CMainMenuSetData2 : CMainMenuSetData {
    CMainMenuSetData2();
    ~CMainMenuSetData2();
    void Init();
};
struct CRaceResultData : CMenuData {
    CRaceResultData();
    ~CRaceResultData();
    void Init();
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28[14];
    int m84;
    int m88;
    bool m92;
    char m93[16];
    int m112;
    int m116;
    int m120;
    int m124;
};
struct CWirelessLanSwitchData : CMenuData {
    CWirelessLanSwitchData();
    ~CWirelessLanSwitchData();
    void Init();
    bool m8;
};
struct CWirelessRaceOpenData : CMenuData {
    CWirelessRaceOpenData();
    ~CWirelessRaceOpenData();
    void Init();
    int m8;
    int m12;
    int m16;
};
struct CWirelessRaceOpenOpponentData : CMenuData {
    CWirelessRaceOpenOpponentData();
    ~CWirelessRaceOpenOpponentData();
    void Init();
    int m8;
    int m12;
    int m16;
    int m20;
};
struct CWirelessRaceEntryListData : CMenuData {
    CWirelessRaceEntryListData();
    ~CWirelessRaceEntryListData();
    void Init();
    int m8;
    char m12[64];
    int m76[24];
};
struct CWirelessRaceListData : CMenuData {
    CWirelessRaceListData();
    ~CWirelessRaceListData();
    void Init();
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
    int m32;
    int m36;
};
struct CWirelessRacePermData : CMenuData {
    CWirelessRacePermData();
    ~CWirelessRacePermData();
    void Init();
    bool m8;
};
struct CWirelessRaceEntryInfoData : CMenuData {
    CWirelessRaceEntryInfoData();
    ~CWirelessRaceEntryInfoData();
    void Init();
    bool m8;
};
struct CWirelessRaceEntryData : CMenuData {
    CWirelessRaceEntryData();
    ~CWirelessRaceEntryData();
    void Init();
    int m8;
};
struct CWirelessOpponentListData : CMenuData {
    CWirelessOpponentListData();
    ~CWirelessOpponentListData();
    void Init();
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;
};
struct CWirelessRaceResultData : CMenuData {
    CWirelessRaceResultData();
    ~CWirelessRaceResultData();
    void Init();
    int m8;
    char m12[224];
};
struct CMainMenuData : CMenuData {
    CMainMenuData();
    ~CMainMenuData();
    void Init();
};
struct COptionMenuData : CMenuData {
    COptionMenuData();
    ~COptionMenuData();
    void Init();
};
struct CMusicPlayerData : CMenuData {
    CMusicPlayerData();
    ~CMusicPlayerData();
    void Init();
    int m8;
    int m12;
};
struct CPauseMenuData : CMenuData {
    CPauseMenuData();
    ~CPauseMenuData();
    void Init();
    int m8;
    int m12;
    bool m16;
    int m20;
};
struct CResultMenuData : CMenuData {
    CResultMenuData();
    ~CResultMenuData();
    void Init();
    bool m8;
    int m12;
    bool m16;
    bool m17;
    bool m18;
};
struct CStartMenuData : CMenuData {
    CStartMenuData();
    ~CStartMenuData();
    void Init();
    int m8;
    bool m12;
};

/* @implements 0x078078 us _ZN6Select9CMenuDataC2Ev
   WHAT IT DOES: Base object constructor: sets the vtable. */
/* @implements 0x078088 us _ZN6Select9CMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CMenuData::CMenuData()
{
}

/* @implements 0x078098 us _ZN6Select9CMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable. */
/* @implements 0x0780a8 us _ZN6Select9CMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x0780b8 us _ZN6Select9CMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CMenuData::~CMenuData()
{
}

/* @implements 0x0780e0 us _ZNK6Select9CMenuData4TypeEv
   WHAT IT DOES: Returns the menu id kept in the base word. */
int CMenuData::Type() const
{
    return m4;
}

/* @implements 0x0780e8 us _ZN6Select16CTextureMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the texture menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07813c us _ZN6Select16CTextureMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CTextureMenuData::CTextureMenuData()
{
    Init();
}

/* @implements 0x078190 us _ZN6Select16CTextureMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x0781b8 us _ZN6Select16CTextureMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x0781e0 us _ZN6Select16CTextureMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CTextureMenuData::~CTextureMenuData()
{
}

/* @implements 0x078218 us _ZN6Select16CTextureMenuData4InitEv
   WHAT IT DOES: Sets the menu id (4) and clears the word at +8. */
void CTextureMenuData::Init()
{
    m4 = 4;
    m8 = 0;
}

/* @implements 0x078228 us _ZN6Select15CCarObjMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the car model menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07827c us _ZN6Select15CCarObjMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CCarObjMenuData::CCarObjMenuData()
{
    Init();
}

/* @implements 0x0782d0 us _ZN6Select15CCarObjMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x0782f8 us _ZN6Select15CCarObjMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x078320 us _ZN6Select15CCarObjMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CCarObjMenuData::~CCarObjMenuData()
{
}

/* @implements 0x078358 us _ZN6Select15CCarObjMenuData4InitEv
   WHAT IT DOES: Sets the menu id (20) and clears the five words after it. */
void CCarObjMenuData::Init()
{
    m4 = 20;
    m8 = 0;
    m12 = 0;
    m16 = 0;
    m20 = 0;
    m24 = 0;
}

/* @implements 0x078378 us _ZN6Select18CCarGetObjMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the car award menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x0783cc us _ZN6Select18CCarGetObjMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CCarGetObjMenuData::CCarGetObjMenuData()
{
    Init();
}

/* @implements 0x078420 us _ZN6Select18CCarGetObjMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x078448 us _ZN6Select18CCarGetObjMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x078470 us _ZN6Select18CCarGetObjMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CCarGetObjMenuData::~CCarGetObjMenuData()
{
}

/* @implements 0x0784a8 us _ZN6Select18CCarGetObjMenuData4InitEv
   WHAT IT DOES: Sets the menu id (26) and clears the 16 rows of five words. */
void CCarGetObjMenuData::Init()
{
    int i;

    m4 = 26;
    for (i = 0; i < 5; i++) {
        m8[0][i] = 0;
        m8[1][i] = 0;
        m8[2][i] = 0;
        m8[3][i] = 0;
        m8[4][i] = 0;
        m8[5][i] = 0;
        m8[6][i] = 0;
        m8[7][i] = 0;
        m8[8][i] = 0;
        m8[9][i] = 0;
        m8[10][i] = 0;
        m8[11][i] = 0;
        m8[12][i] = 0;
        m8[13][i] = 0;
        m8[14][i] = 0;
        m8[15][i] = 0;
    }
}

/* @implements 0x078508 us _ZN6Select21CCarGetNumberMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the car award count menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07855c us _ZN6Select21CCarGetNumberMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CCarGetNumberMenuData::CCarGetNumberMenuData()
{
    Init();
}

/* @implements 0x0785b0 us _ZN6Select21CCarGetNumberMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x0785d8 us _ZN6Select21CCarGetNumberMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x078600 us _ZN6Select21CCarGetNumberMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CCarGetNumberMenuData::~CCarGetNumberMenuData()
{
}

/* @implements 0x078638 us _ZN6Select21CCarGetNumberMenuData4InitEv
   WHAT IT DOES: Sets the menu id (27) and clears the five words at +8 and the word at +28. */
void CCarGetNumberMenuData::Init()
{
    int i;

    m4 = 27;
    m28 = 0;
    for (i = 0; i < 5; i++)
        m8[i] = 0;
}

/* @implements 0x078664 us _ZN6Select13CSaveMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the save menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x0786b8 us _ZN6Select13CSaveMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CSaveMenuData::CSaveMenuData()
{
    Init();
}

/* @implements 0x07870c us _ZN6Select13CSaveMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x078734 us _ZN6Select13CSaveMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07875c us _ZN6Select13CSaveMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CSaveMenuData::~CSaveMenuData()
{
}

/* @implements 0x078794 us _ZN6Select13CSaveMenuData4InitEv
   WHAT IT DOES: Sets the menu id (11) and clears both flags. */
void CSaveMenuData::Init()
{
    m4 = 11;
    m8 = 0;
    m9 = 0;
}

/* @implements 0x0787a8 us _ZN6Select18CGhostSaveMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the ghost save menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x0787fc us _ZN6Select18CGhostSaveMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CGhostSaveMenuData::CGhostSaveMenuData()
{
    Init();
}

/* @implements 0x078850 us _ZN6Select18CGhostSaveMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x078878 us _ZN6Select18CGhostSaveMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x0788a0 us _ZN6Select18CGhostSaveMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CGhostSaveMenuData::~CGhostSaveMenuData()
{
}

/* @implements 0x0788d8 us _ZN6Select18CGhostSaveMenuData4InitEv
   WHAT IT DOES: Sets the menu id (12), clears both flags and sets the word at +12 to 1. */
void CGhostSaveMenuData::Init()
{
    m4 = 12;
    m8 = 0;
    m9 = 0;
    m12 = 1;
}

/* @implements 0x0788f4 us _ZN6Select14CSoundMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the sound menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x078948 us _ZN6Select14CSoundMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CSoundMenuData::CSoundMenuData()
{
    Init();
}

/* @implements 0x07899c us _ZN6Select14CSoundMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x0789c4 us _ZN6Select14CSoundMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x0789ec us _ZN6Select14CSoundMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CSoundMenuData::~CSoundMenuData()
{
}

/* @implements 0x078a24 us _ZN6Select14CSoundMenuData4InitEv
   WHAT IT DOES: Sets the menu id (2), clears the flag, sets the word at +12 to 1 and clears the three after it. */
void CSoundMenuData::Init()
{
    m12 = 1;
    m4 = 2;
    m20 = 0;
    m24 = 0;
    m8 = 0;
    m16 = 0;
}

/* @implements 0x078a48 us _ZN6Select13CBestTimeDataC2Ev
   WHAT IT DOES: Base object constructor of the best time table settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x078a9c us _ZN6Select13CBestTimeDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CBestTimeData::CBestTimeData()
{
    Init();
}

/* @implements 0x078af0 us _ZN6Select13CBestTimeDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x078b18 us _ZN6Select13CBestTimeDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x078b40 us _ZN6Select13CBestTimeDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CBestTimeData::~CBestTimeData()
{
}

/* @implements 0x078b78 us _ZN6Select13CBestTimeData4InitEv
   WHAT IT DOES: Sets the menu id (17) and clears the 0xd200-byte table. */
void CBestTimeData::Init()
{
    m4 = 17;
    memset(m8, 0, sizeof m8);
}

/* @implements 0x078ba4 us _ZN6Select16CMainMenuSetDataC2Ev
   WHAT IT DOES: Base object constructor of the main menu set-up settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x078bf8 us _ZN6Select16CMainMenuSetDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CMainMenuSetData::CMainMenuSetData()
{
    Init();
}

/* @implements 0x078c4c us _ZN6Select16CMainMenuSetDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x078c74 us _ZN6Select16CMainMenuSetDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x078c9c us _ZN6Select16CMainMenuSetDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CMainMenuSetData::~CMainMenuSetData()
{
}

/* @implements 0x078cd4 us _ZN6Select16CMainMenuSetData4InitEv
   WHAT IT DOES: Sets the menu id (19) and clears every field. */
void CMainMenuSetData::Init()
{
    m4 = 19;
    m8[0] = 0;
    m8[1] = 0;
    m8[2] = 0;
    m8[3] = 0;
    m8[4] = 0;
    m8[5] = 0;
    m8[6] = 0;
    m8[7] = 0;
    m8[8] = 0;
    m8[9] = 0;
    m8[10] = 0;
    m8[11] = 0;
    m60 = 0;
    m64 = 0;
    m56 = 0;
}

/* @draft 0x078d1c us _ZN6Select17CMainMenuSetData2C2Ev
   WHAT IT DOES: Base object constructor of the second main menu set-up settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @draft 0x078d70 us _ZN6Select17CMainMenuSetData2C1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CMainMenuSetData2::CMainMenuSetData2()
{
    Init();
}

/* @implements 0x078dc4 us _ZN6Select17CMainMenuSetData2D2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x078dec us _ZN6Select17CMainMenuSetData2D1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x078e14 us _ZN6Select17CMainMenuSetData2D0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CMainMenuSetData2::~CMainMenuSetData2()
{
}

/* @implements 0x07924c us _ZN6Select15CRaceResultDataC2Ev
   WHAT IT DOES: Base object constructor of the race result settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x0792a0 us _ZN6Select15CRaceResultDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CRaceResultData::CRaceResultData()
{
    Init();
}

/* @implements 0x0792f4 us _ZN6Select15CRaceResultDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07931c us _ZN6Select15CRaceResultDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079344 us _ZN6Select15CRaceResultDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CRaceResultData::~CRaceResultData()
{
}

/* @implements 0x07937c us _ZN6Select15CRaceResultData4InitEv
   WHAT IT DOES: Sets the menu id (8), the five words at +8 to 1 and the one at +88 to -1, and clears every other field. */
void CRaceResultData::Init()
{
    m4 = 8;
    m8 = 1;
    m12 = 1;
    m16 = 1;
    m20 = 1;
    m88 = -1;
    m28[0] = 0;
    m28[1] = 0;
    m28[2] = 0;
    m28[3] = 0;
    m28[4] = 0;
    m28[5] = 0;
    m28[6] = 0;
    m28[7] = 0;
    m28[8] = 0;
    m28[9] = 0;
    m28[10] = 0;
    m28[11] = 0;
    m28[12] = 0;
    m28[13] = 0;
    m92 = 0;
    m24 = 1;
    memset(m93, 0, sizeof m93);
    m112 = 0;
    m116 = 0;
    m124 = 0;
    m84 = 0;
    m120 = 0;
}

/* @implements 0x079424 us _ZN6Select22CWirelessLanSwitchDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless switch settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079478 us _ZN6Select22CWirelessLanSwitchDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessLanSwitchData::CWirelessLanSwitchData()
{
    Init();
}

/* @implements 0x0794cc us _ZN6Select22CWirelessLanSwitchDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x0794f4 us _ZN6Select22CWirelessLanSwitchDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07951c us _ZN6Select22CWirelessLanSwitchDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessLanSwitchData::~CWirelessLanSwitchData()
{
}

/* @implements 0x079554 us _ZN6Select22CWirelessLanSwitchData4InitEv
   WHAT IT DOES: Sets the menu id (16) and sets the flag. */
void CWirelessLanSwitchData::Init()
{
    m4 = 16;
    m8 = 1;
}

/* @implements 0x079568 us _ZN6Select21CWirelessRaceOpenDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race open settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x0795bc us _ZN6Select21CWirelessRaceOpenDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceOpenData::CWirelessRaceOpenData()
{
    Init();
}

/* @implements 0x079610 us _ZN6Select21CWirelessRaceOpenDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079638 us _ZN6Select21CWirelessRaceOpenDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079660 us _ZN6Select21CWirelessRaceOpenDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceOpenData::~CWirelessRaceOpenData()
{
}

/* @implements 0x079698 us _ZN6Select21CWirelessRaceOpenData4InitEv
   WHAT IT DOES: Sets the menu id (21), clears the word at +8 and sets the two after it to 1. */
void CWirelessRaceOpenData::Init()
{
    m4 = 21;
    m8 = 0;
    m12 = 1;
    m16 = 1;
}

/* @implements 0x0796b4 us _ZN6Select29CWirelessRaceOpenOpponentDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race open opponent settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079708 us _ZN6Select29CWirelessRaceOpenOpponentDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceOpenOpponentData::CWirelessRaceOpenOpponentData()
{
    Init();
}

/* @implements 0x07975c us _ZN6Select29CWirelessRaceOpenOpponentDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079784 us _ZN6Select29CWirelessRaceOpenOpponentDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x0797ac us _ZN6Select29CWirelessRaceOpenOpponentDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceOpenOpponentData::~CWirelessRaceOpenOpponentData()
{
}

/* @implements 0x0797e4 us _ZN6Select29CWirelessRaceOpenOpponentData4InitEv
   WHAT IT DOES: Sets the menu id (22) and clears the four words after it. */
void CWirelessRaceOpenOpponentData::Init()
{
    m4 = 22;
    m8 = 0;
    m12 = 0;
    m16 = 0;
    m20 = 0;
}

/* @implements 0x079800 us _ZN6Select26CWirelessRaceEntryListDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race entry list settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079854 us _ZN6Select26CWirelessRaceEntryListDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceEntryListData::CWirelessRaceEntryListData()
{
    Init();
}

/* @implements 0x0798a8 us _ZN6Select26CWirelessRaceEntryListDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x0798d0 us _ZN6Select26CWirelessRaceEntryListDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x0798f8 us _ZN6Select26CWirelessRaceEntryListDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceEntryListData::~CWirelessRaceEntryListData()
{
}

/* @implements 0x079930 us _ZN6Select26CWirelessRaceEntryListData4InitEv
   WHAT IT DOES: Sets the menu id (25) and clears every field. */
void CWirelessRaceEntryListData::Init()
{
    m4 = 25;
    m8 = 0;
    memset(m12, 0, sizeof m12);
    m76[0] = 0;
    m76[1] = 0;
    m76[2] = 0;
    m76[3] = 0;
    m76[4] = 0;
    m76[5] = 0;
    m76[6] = 0;
    m76[7] = 0;
    m76[8] = 0;
    m76[9] = 0;
    m76[10] = 0;
    m76[11] = 0;
    m76[12] = 0;
    m76[13] = 0;
    m76[14] = 0;
    m76[15] = 0;
    m76[16] = 0;
    m76[17] = 0;
    m76[18] = 0;
    m76[19] = 0;
    m76[20] = 0;
    m76[21] = 0;
    m76[22] = 0;
    m76[23] = 0;
}

/* @implements 0x0799cc us _ZN6Select21CWirelessRaceListDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race list settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079a20 us _ZN6Select21CWirelessRaceListDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceListData::CWirelessRaceListData()
{
    Init();
}

/* @implements 0x079a74 us _ZN6Select21CWirelessRaceListDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079a9c us _ZN6Select21CWirelessRaceListDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079ac4 us _ZN6Select21CWirelessRaceListDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceListData::~CWirelessRaceListData()
{
}

/* @implements 0x079afc us _ZN6Select21CWirelessRaceListData4InitEv
   WHAT IT DOES: Sets the menu id (13) and clears every word but the one at +24. */
void CWirelessRaceListData::Init()
{
    m4 = 13;
    m8 = 0;
    m16 = 0;
    m12 = 0;
    m20 = 0;
    m28 = 0;
    m32 = 0;
    m36 = 0;
}

/* @implements 0x079b24 us _ZN6Select21CWirelessRacePermDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race permission settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079b78 us _ZN6Select21CWirelessRacePermDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRacePermData::CWirelessRacePermData()
{
    Init();
}

/* @implements 0x079bcc us _ZN6Select21CWirelessRacePermDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079bf4 us _ZN6Select21CWirelessRacePermDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079c1c us _ZN6Select21CWirelessRacePermDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRacePermData::~CWirelessRacePermData()
{
}

/* @implements 0x079c54 us _ZN6Select21CWirelessRacePermData4InitEv
   WHAT IT DOES: Sets the menu id (23) and clears the flag. */
void CWirelessRacePermData::Init()
{
    m4 = 23;
    m8 = 0;
}

/* @implements 0x079c64 us _ZN6Select26CWirelessRaceEntryInfoDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race entry information settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079cb8 us _ZN6Select26CWirelessRaceEntryInfoDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceEntryInfoData::CWirelessRaceEntryInfoData()
{
    Init();
}

/* @implements 0x079d0c us _ZN6Select26CWirelessRaceEntryInfoDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079d34 us _ZN6Select26CWirelessRaceEntryInfoDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079d5c us _ZN6Select26CWirelessRaceEntryInfoDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceEntryInfoData::~CWirelessRaceEntryInfoData()
{
}

/* @implements 0x079d94 us _ZN6Select26CWirelessRaceEntryInfoData4InitEv
   WHAT IT DOES: Sets the menu id (28) and clears the flag. */
void CWirelessRaceEntryInfoData::Init()
{
    m4 = 28;
    m8 = 0;
}

/* @implements 0x079da4 us _ZN6Select22CWirelessRaceEntryDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race entry settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079df8 us _ZN6Select22CWirelessRaceEntryDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceEntryData::CWirelessRaceEntryData()
{
    Init();
}

/* @implements 0x079e4c us _ZN6Select22CWirelessRaceEntryDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079e74 us _ZN6Select22CWirelessRaceEntryDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079e9c us _ZN6Select22CWirelessRaceEntryDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceEntryData::~CWirelessRaceEntryData()
{
}

/* @implements 0x079ed4 us _ZN6Select22CWirelessRaceEntryData4InitEv
   WHAT IT DOES: Sets the menu id (24) and clears the word at +8. */
void CWirelessRaceEntryData::Init()
{
    m4 = 24;
    m8 = 0;
}

/* @implements 0x079ee4 us _ZN6Select25CWirelessOpponentListDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless opponent list settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x079f38 us _ZN6Select25CWirelessOpponentListDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessOpponentListData::CWirelessOpponentListData()
{
    Init();
}

/* @implements 0x079f8c us _ZN6Select25CWirelessOpponentListDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x079fb4 us _ZN6Select25CWirelessOpponentListDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x079fdc us _ZN6Select25CWirelessOpponentListDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessOpponentListData::~CWirelessOpponentListData()
{
}

/* @implements 0x07a014 us _ZN6Select25CWirelessOpponentListData4InitEv
   WHAT IT DOES: Sets the menu id (14) and clears the six words after it. */
void CWirelessOpponentListData::Init()
{
    m4 = 14;
    m8 = 0;
    m12 = 0;
    m16 = 0;
    m20 = 0;
    m24 = 0;
    m28 = 0;
}

/* @implements 0x07a038 us _ZN6Select23CWirelessRaceResultDataC2Ev
   WHAT IT DOES: Base object constructor of the wireless race result settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07a08c us _ZN6Select23CWirelessRaceResultDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CWirelessRaceResultData::CWirelessRaceResultData()
{
    Init();
}

/* @implements 0x07a0e0 us _ZN6Select23CWirelessRaceResultDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07a108 us _ZN6Select23CWirelessRaceResultDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07a130 us _ZN6Select23CWirelessRaceResultDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CWirelessRaceResultData::~CWirelessRaceResultData()
{
}

/* @implements 0x07a168 us _ZN6Select23CWirelessRaceResultData4InitEv
   WHAT IT DOES: Sets the menu id (15), clears the word at +8 and the 224-byte table after it. */
void CWirelessRaceResultData::Init()
{
    m4 = 15;
    m8 = 0;
    memset(m12, 0, sizeof m12);
}

/* @draft 0x07a2c0 us _ZN6Select13CMainMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the main menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @draft 0x07a314 us _ZN6Select13CMainMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CMainMenuData::CMainMenuData()
{
    Init();
}

/* @implements 0x07a368 us _ZN6Select13CMainMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07a390 us _ZN6Select13CMainMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07a3b8 us _ZN6Select13CMainMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CMainMenuData::~CMainMenuData()
{
}

/* @draft 0x07a504 us _ZN6Select15COptionMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the option menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @draft 0x07a558 us _ZN6Select15COptionMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
COptionMenuData::COptionMenuData()
{
    Init();
}

/* @implements 0x07a5ac us _ZN6Select15COptionMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07a5d4 us _ZN6Select15COptionMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07a5fc us _ZN6Select15COptionMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
COptionMenuData::~COptionMenuData()
{
}

/* @implements 0x07a6f0 us _ZN6Select16CMusicPlayerDataC2Ev
   WHAT IT DOES: Base object constructor of the music player settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07a744 us _ZN6Select16CMusicPlayerDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CMusicPlayerData::CMusicPlayerData()
{
    Init();
}

/* @implements 0x07a798 us _ZN6Select16CMusicPlayerDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07a7c0 us _ZN6Select16CMusicPlayerDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07a7e8 us _ZN6Select16CMusicPlayerDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CMusicPlayerData::~CMusicPlayerData()
{
}

/* @implements 0x07a820 us _ZN6Select16CMusicPlayerData4InitEv
   WHAT IT DOES: Sets the menu id (18) and both words after it to 1. */
void CMusicPlayerData::Init()
{
    m4 = 18;
    m8 = 1;
    m12 = 1;
}

/* @implements 0x07a838 us _ZN6Select14CPauseMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the pause menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07a88c us _ZN6Select14CPauseMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CPauseMenuData::CPauseMenuData()
{
    Init();
}

/* @implements 0x07a8e0 us _ZN6Select14CPauseMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07a908 us _ZN6Select14CPauseMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07a930 us _ZN6Select14CPauseMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CPauseMenuData::~CPauseMenuData()
{
}

/* @implements 0x07a968 us _ZN6Select14CPauseMenuData4InitEv
   WHAT IT DOES: Sets the menu id (1) and clears every field. */
void CPauseMenuData::Init()
{
    m4 = 1;
    m8 = 0;
    m12 = 0;
    m16 = 0;
    m20 = 0;
}

/* @implements 0x07a984 us _ZN6Select15CResultMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the result menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07a9d8 us _ZN6Select15CResultMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CResultMenuData::CResultMenuData()
{
    Init();
}

/* @implements 0x07aa2c us _ZN6Select15CResultMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the base's destructor. */
/* @implements 0x07aa54 us _ZN6Select15CResultMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07aa7c us _ZN6Select15CResultMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CResultMenuData::~CResultMenuData()
{
}

/* @implements 0x07aab4 us _ZN6Select15CResultMenuData4InitEv
   WHAT IT DOES: Sets the menu id (3), clears the flags and sets the word at +12 to 1. */
void CResultMenuData::Init()
{
    m4 = 3;
    m12 = 1;
    m17 = 0;
    m18 = 0;
    m8 = 0;
    m16 = 0;
}

/* @implements 0x07aad8 us _ZN6Select14CStartMenuDataC2Ev
   WHAT IT DOES: Base object constructor of the start menu settings: builds the base, sets the
   vtable and resets the settings with Init. */
/* @implements 0x07ab2c us _ZN6Select14CStartMenuDataC1Ev
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
CStartMenuData::CStartMenuData()
{
    Init();
}

}
