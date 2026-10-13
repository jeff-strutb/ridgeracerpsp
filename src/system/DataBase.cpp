/* The game database object file (retail 0x03680c to 0x036cb8, DB::CDataBase). A database is
   one table loaded from a package: a header of counts and offsets, the column names, the row
   names, each column's type and data offset, and the cells. Cells are found by column and row
   name; text cells hold an offset to the string, and a text cell may hold a comma separated
   list. */

#include <string.h>

/* The size of a cell of each column type; types 5 and 6 are text (an offset to the string). */
extern const int D_1a211c[];

/* The value of the last text cell read (copied, as cells are not aligned). */
int D_24063c;
/* One field of a comma separated text cell. */
char D_240640[256];

namespace DB {

class CDataBase {
public:
    virtual ~CDataBase() {}
    virtual int Set(void *data);
    virtual int f_0368d8();
    virtual int f_0368e0();
    virtual char *Data() { return (char *)m36; }
    virtual void Clear();

    int Find(const char *name, int *names, unsigned int n);
    char *Get(const char *col, const char *row, int colAdd, int rowAdd);
    char *Lookup(const char *key, int add, int *names, unsigned int n);
    char *Cell(int col, int row);
    char *Field(const char *col, const char *row, int idx);
    int Fields(const char *col, const char *row);

    unsigned int cols;   /* number of columns */
    unsigned int rows;   /* number of rows */
    /* The addresses of the table's lists, kept as plain words: each column's type, each
       column's data offset, the column names and the row names (offsets), and two more. */
    int type;
    int offset;
    int colName;
    int rowName;
    int m28;
    int m32;
    int m36;             /* the loaded table */
};

/* @implements 0x03680c us _ZN2DB9CDataBase3SetEPv
   WHAT IT DOES: Takes a loaded table: clears the database, keeps the table and, when there is
   one, reads the column and row counts from its header and turns its six offsets into
   pointers. Returns whether a table was given. */
int CDataBase::Set(void *data)
{
    Clear();
    int *h = (int *)data;
    int ok = 0;
    m36 = (int)h;
    if (h) {
        ok = 1;
        cols = h[0];
        rows = h[1];
        type = (int)h + h[2];
        offset = (int)h + h[3];
        colName = (int)h + h[4];
        rowName = (int)h + h[5];
        m28 = (int)h + h[6];
        m32 = (int)h + h[7];
    }
    return ok;
}

/* @implements 0x0368b0 us _ZN2DB9CDataBase5ClearEv
   WHAT IT DOES: Forgets the table and every pointer into it. */
void CDataBase::Clear()
{
    cols = 0;
    rows = 0;
    type = 0;
    offset = 0;
    colName = 0;
    rowName = 0;
    m28 = 0;
    m32 = 0;
    m36 = 0;
}

/* @implements 0x0368d8 us _ZN2DB9CDataBase8f_0368d8Ev
   WHAT IT DOES: A virtual hook that does nothing here; returns 0. */
int CDataBase::f_0368d8()
{
    return 0;
}

/* @implements 0x0368e0 us _ZN2DB9CDataBase8f_0368e0Ev
   WHAT IT DOES: A second virtual hook that does nothing here; returns 0. */
int CDataBase::f_0368e0()
{
    return 0;
}

/* @implements 0x0368e8 us _ZN2DB9CDataBase3GetEPKcS2_ii
   WHAT IT DOES: Finds a cell by column and row name, each moved on by a number of columns or
   rows; returns 0 when either name is not in the table. */
char *CDataBase::Get(const char *col, const char *row, int colAdd, int rowAdd)
{
    int c = Find(col, (int *)colName, cols);
    if (c < 0)
        return 0;
    int r = Find(row, (int *)rowName, rows);
    if (r < 0)
        return 0;
    return Cell(c + colAdd, r + rowAdd);
}

/* @implements 0x036984 us _ZN2DB9CDataBase6LookupEPKciPij
   WHAT IT DOES: Finds the entry named key in a name list (the first one when key is null or
   not found, the one past the end) and returns the name add entries further on. */
char *CDataBase::Lookup(const char *key, int add, int *names, unsigned int n)
{
    unsigned int i = 0;
    if (key) {
        for (; i < n; i++) {
            if (strcmp((char *)(m36 + names[i]), key) == 0)
                break;
        }
    }
    return (char *)(m36 + names[i + add]);
}

/* @implements 0x036a3c us _ZN2DB9CDataBase4FindEPKcPij
   WHAT IT DOES: Returns the index of a name in a name list, 0 for a null name, -1 when it is
   not there. */
int CDataBase::Find(const char *name, int *names, unsigned int n)
{
    unsigned int i = 0;
    if (!name)
        return 0;
    for (; i < n; i++) {
        if (strcmp((char *)(m36 + names[i]), name) == 0)
            return i;
    }
    return -1;
}

/* @implements 0x036ad0 us _ZN2DB9CDataBase4CellEii
   WHAT IT DOES: Returns the address of a cell; for a text cell, the address of its string. */
char *CDataBase::Cell(int col, int row)
{
    int t = ((int *)type)[col];
    char *p = (char *)(((int *)offset)[col] + m36 + D_1a211c[t] * row);
    if (t == 5 || t == 6) {
        memcpy(&D_24063c, p, D_1a211c[0]);
        return (char *)(m36 + D_24063c);
    }
    return p;
}

/* @implements 0x036b6c us _ZN2DB9CDataBase5FieldEPKcS2_i
   WHAT IT DOES: Returns field idx of a comma separated text cell, copied into a buffer; with a
   negative idx, the whole cell. */
char *CDataBase::Field(const char *col, const char *row, int idx)
{
    char *s = Get(col, row, 0, 0);
    char *end = s + strlen(s);
    char *start = s;
    int n = 0;
    if (idx < 0)
        return s;
    while (s <= end) {
        if (*s++ == ',') {
            if (n == idx)
                break;
            n++;
            start = s;
        }
    }
    strncpy(D_240640, start, s - start - 1);
    return D_240640;
}

/* @implements 0x036c10 us _ZN2DB9CDataBase6FieldsEPKcS2_
   WHAT IT DOES: Returns the number of fields of a comma separated text cell. */
int CDataBase::Fields(const char *col, const char *row)
{
    char *s = Get(col, row, 0, 0);
    char *end = s + strlen(s);
    int n = 1;
    while (s <= end) {
        if (*s++ == ',')
            n++;
    }
    return n;
}

}

extern const int D_1a211c[] = { 4, 1, 2, 4, 4, 4, 4 };

/* @implements 0x036c78 us _ZN2DB9CDataBaseD1Ev
   WHAT IT DOES: The destructor (nothing to free). */

/* @implements 0x036c88 us _ZN2DB9CDataBaseD0Ev
   WHAT IT DOES: The deleting destructor. */

/* @implements 0x036cb0 us _ZN2DB9CDataBase4DataEv
   WHAT IT DOES: Returns the loaded table. */
