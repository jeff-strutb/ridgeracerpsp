/* The start menu's settings object, Select::CStartMenuData (retail 0x07ab80 to 0x07ac1c): its
   destructors and its reset. The constructors sit at the end of the menu data object file
   before it; these follow in the gap after it. */

namespace Select {

/* The base of every menu settings object (constructors and destructors in the menu data
   object file). */
struct CMenuData {
    CMenuData();
    virtual ~CMenuData();
    virtual void Init() = 0;
    int m4;
};

struct CStartMenuData : CMenuData {
    CStartMenuData();
    ~CStartMenuData();
    void Init();
    int m8;
    bool m12;
};

/* @implements 0x07ab80 us _ZN6Select14CStartMenuDataD2Ev
   WHAT IT DOES: Base object destructor: restores the vtable and runs the menu data base's
   destructor. */
/* @implements 0x07aba8 us _ZN6Select14CStartMenuDataD1Ev
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
/* @implements 0x07abd0 us _ZN6Select14CStartMenuDataD0Ev
   WHAT IT DOES: Deleting destructor: destroys the object and frees it. */
CStartMenuData::~CStartMenuData()
{
}

/* @implements 0x07ac08 us _ZN6Select14CStartMenuData4InitEv
   WHAT IT DOES: Resets the settings: both words cleared and the flag at +12 set. */
void CStartMenuData::Init()
{
    m4 = 0;
    m8 = 0;
    m12 = 1;
}

}
