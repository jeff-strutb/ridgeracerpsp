/* The race database object file (retail 0x037abc to 0x037b78): the database the main loop
   fills from the "Race" package (sequence numbers, course numbers, car settings). The file
   holds only the object; its constructor and destructor are DB::CDataBase's inline ones. */

namespace DB {
class CDataBase {
public:
    CDataBase() { Clear(); }
    virtual ~CDataBase() {}
    virtual int Set(void *data);
    virtual int f_0368d8();
    virtual int f_0368e0();
    virtual char *Data() { return (char *)m36; }
    virtual void Clear();

    unsigned int cols;
    unsigned int rows;
    int type;
    int offset;
    int colName;
    int rowName;
    int m28;
    int m32;
    int m36;
};
}

DB::CDataBase D_2407d0;

/* @implements 0x037abc us __static_initialization_and_destruction_0
   WHAT IT DOES: At startup, constructs the race database (empty); at exit, destroys it. */

/* @implements 0x037b38 us _GLOBAL__I_
   WHAT IT DOES: The startup entry for this file's static data. */

/* @implements 0x037b58 us _GLOBAL__D_
   WHAT IT DOES: The exit entry for this file's static data. */
