/* The NU Sound bank list (retail 0x10d44c to 0x10db1c): up to 64 sound banks copied into
   one aligned buffer, each slot holding the bank's name, its copy in the buffer and its
   header, and a table of every bank's tones. One global instance (D_27f170), used through
   the plain functions at the end of the file. Banks are released last in, first out.
   Errors: 0x80000021 when the buffer is full, 0x8000001c when every slot is taken,
   0x8000001d when no bank is loaded, 0x8000000f for an unknown name, 0x80000010 for an
   empty or out of range slot. */

extern "C" {
void *f_125c4c(unsigned int align, unsigned int size); /* memalign */
void free(void *p) throw();
void *memcpy(void *d, const void *s, unsigned int n) throw();
void f_1105b4(const char *msg);
}

/* A tone of a bank (80 bytes). */
struct BankTone {
    char p0[24];
    unsigned short rate;
    char p1a[26];
    char *data;
    char p38[24];
};

/* A bank's header; its tones follow it. */
struct BankHeader {
    char c0;
    char kind;              /* '3' marks a bank flagged for the caller */
    char c2;
    char rate;              /* 'p': tones recorded at 44.1 kHz, rescaled to 48 kHz once */
    char p4[2];
    unsigned short name;
    unsigned short count;
    char pa[2];
    unsigned int size;
};

struct BankSlot {
    int name;               /* -1 for a free slot */
    int data;               /* the bank's copy in the buffer */
    BankHeader *hdr;
};

class CBankList {
public:
    BankSlot slot[64];
    BankTone *tone[64][196];
    unsigned int cap;
    unsigned int used;
    char *buf;
    int flag[64];

    ~CBankList() {}
    void f_10d44c(unsigned int size);
    void f_10d4b0();
    int f_10d4d4(BankHeader *h, void *src, unsigned short *id);
    int f_10d6f8();
    unsigned short f_10d76c(int i);
    int f_10d788(unsigned short name);
    int f_10d7c0(unsigned short i);
    void f_10d810();
    void f_10d858(unsigned short i, int a);
    BankTone *f_10d860(unsigned short i, unsigned short n);
    int f_10d8e4(unsigned short i);
};

CBankList *D_27f170;

/* @implements 0x10d44c us _ZN9CBankList8f_10d44cEj
   WHAT IT DOES: Allocates the bank buffer and frees every slot. */
void CBankList::f_10d44c(unsigned int size)
{
    int i;

    cap = size;
    buf = (char *)f_125c4c(16, size);
    used = 0;
    for (i = 0; i < 64; i++) {
        slot[i].name = -1;
        slot[i].data = 0;
        slot[i].hdr = 0;
    }
}

/* @implements 0x10d4b0 us _ZN9CBankList8f_10d4b0Ev
   WHAT IT DOES: Frees the bank buffer. */
void CBankList::f_10d4b0()
{
    free(buf);
}

/* @draft 0x10d4d4 us _ZN9CBankList8f_10d4d4EP10BankHeaderPvPt
   WHAT IT DOES: Copies a bank (its data at src) into the buffer, takes the first free slot
   for it (its index returned in *id) and records where each of its tones is; tones recorded
   at 44.1 kHz have their rates rescaled to 48 kHz.
   DRAFT: two words: retail stores the slot's header before its data address (the data
   store in the jump's slot); here the scheduler's register-pressure rank puts the data
   store first. The count is read through a copy of the header pointer, which is then
   advanced to the tones, as retail keeps both.
   sched1 trace (-fsched-verbose=4): the hdr store (insn 103) has no input dependences and
   only an anti dependence to the jump, so it waits from t=4; at t=8 it loses to the *id
   store (93, same priority, earlier luid) as retail also has, and at t=11 it loses to the
   data store (120) on reg weight: 120 kills the data value and, as the last use in source
   order, the slot pointer (weight -2) against 0. Retail picks hdr at t=11, which needs hdr's
   weight <= data's while keeping the *id store ahead of it at t=8; moving hdr after data in
   source only ties the weights (-1/-1) and the luid then still picks data. No source shape
   found that satisfies both picks; no change made. */
int CBankList::f_10d4d4(BankHeader *bank, void *src, unsigned short *id)
{
    BankHeader *h = bank;
    int i, j, rescale;
    BankTone *t;

    if (cap < used + bank->size)
        return 0x80000021;
    for (i = 0; i < 64; i++) {
        if (slot[i].name == -1) {
            slot[i].name = bank->name;
            *id = i;
            slot[i].hdr = bank;
            slot[i].data = (int)(buf + used);
            break;
        }
    }
    if (i == 64) {
        f_1105b4("NU Sound:bank error BANK FULL.\n");
        return 0x8000001c;
    }
    if (bank->kind == '3')
        flag[*id] = 1;
    else
        flag[*id] = 0;
    memcpy(buf + used, src, bank->size);
    used += bank->size;
    rescale = 0;
    if (bank->rate == 'p') {
        bank->rate = 'P';
        rescale = 1;
    }
    bank++;
    for (j = 0; j < h->count; j++) {
        t = (BankTone *)bank + j;
        tone[*id][j] = t;
        t->data = (char *)slot[*id].data;
        if (rescale)
            t->rate = (int)(t->rate * 48.0f / 44.1f + 1.0f);
    }
    return 0;
}

/* @implements 0x10d6f8 us _ZN9CBankList8f_10d6f8Ev
   WHAT IT DOES: Releases the most recently loaded bank and its space in the buffer. */
int CBankList::f_10d6f8()
{
    BankHeader *h = 0;
    int i;

    for (i = 63; i >= 0; i--) {
        if (slot[i].name != -1) {
            h = slot[i].hdr;
            slot[i].name = -1;
            slot[i].data = 0;
            slot[i].hdr = 0;
            break;
        }
    }
    if (i == -1)
        return 0x8000001d;
    used -= h->size;
    return 0;
}

/* @implements 0x10d76c us _ZN9CBankList8f_10d76cEi
   WHAT IT DOES: Returns the number of tones in slot i's bank. */
unsigned short CBankList::f_10d76c(int i)
{
    return slot[i].hdr->count;
}

/* @implements 0x10d788 us _ZN9CBankList8f_10d788Et
   WHAT IT DOES: Returns the slot holding the bank with this name. */
int CBankList::f_10d788(unsigned short name)
{
    int i;

    for (i = 0; i < 64; i++)
        if ((unsigned short)slot[i].name == name)
            return i;
    return 0x8000000f;
}

/* @implements 0x10d7c0 us _ZN9CBankList8f_10d7c0Et
   WHAT IT DOES: Returns 0 when slot i holds a bank. */
int CBankList::f_10d7c0(unsigned short i)
{
    if (i >= 64)
        return 0x80000010;
    if (slot[i].name == -1 || slot[i].hdr == 0)
        return 0x80000010;
    return 0;
}

/* @implements 0x10d810 us _ZN9CBankList8f_10d810Ev
   WHAT IT DOES: Releases every bank. */
void CBankList::f_10d810()
{
    int i;

    for (i = 0; i < 64; i++)
        if (f_10d6f8() < 0)
            break;
}

/* @implements 0x10d858 us _ZN9CBankList8f_10d858Eti
   WHAT IT DOES: Nothing. */
void CBankList::f_10d858(unsigned short i, int a)
{
}

/* @implements 0x10d860 us _ZN9CBankList8f_10d860Ett
   WHAT IT DOES: Returns tone n of slot i's bank, or 0. */
BankTone *CBankList::f_10d860(unsigned short i, unsigned short n)
{
    if (f_10d7c0(i) == 0 && n < f_10d76c(i))
        return tone[i][n];
    return 0;
}

/* @implements 0x10d8e4 us _ZN9CBankList8f_10d8e4Et
   WHAT IT DOES: Returns slot i's flag (set for banks of kind '3'). */
int CBankList::f_10d8e4(unsigned short i)
{
    return flag[i];
}

extern "C" {
/* @implements 0x10d900 us f_10d900
   WHAT IT DOES: Creates the bank list with a buffer of this size. */
void f_10d900(unsigned int size)
{
    D_27f170 = new CBankList;
    D_27f170->f_10d44c(size);
}

/* @implements 0x10d93c us f_10d93c
   WHAT IT DOES: Frees the bank buffer and deletes the bank list. */
void f_10d93c(void)
{
    D_27f170->f_10d4b0();
    delete D_27f170;
    D_27f170 = 0;
}

/* @implements 0x10d988 us f_10d988
   WHAT IT DOES: Loads a bank. */
int f_10d988(BankHeader *h, void *src, unsigned short *id)
{
    return D_27f170->f_10d4d4(h, src, id);
}

/* @implements 0x10d9bc us f_10d9bc
   WHAT IT DOES: Releases the most recently loaded bank. */
int f_10d9bc(void)
{
    return D_27f170->f_10d6f8();
}

/* @implements 0x10d9dc us f_10d9dc
   WHAT IT DOES: Nothing (the bank list's empty method). */
void f_10d9dc(unsigned short i, int a)
{
    D_27f170->f_10d858(i, a);
}

/* @implements 0x10da0c us f_10da0c
   WHAT IT DOES: Releases every bank. */
void f_10da0c(void)
{
    D_27f170->f_10d810();
}

/* @implements 0x10da30 us f_10da30
   WHAT IT DOES: Returns 0 when slot i holds a bank. */
int f_10da30(unsigned short i)
{
    return D_27f170->f_10d7c0(i);
}

/* @implements 0x10da58 us f_10da58
   WHAT IT DOES: Returns the number of tones in slot i's bank. */
unsigned short f_10da58(int i)
{
    return D_27f170->f_10d76c(i);
}

/* @implements 0x10da7c us f_10da7c
   WHAT IT DOES: Returns the slot holding the bank with this name. */
int f_10da7c(unsigned short name)
{
    return D_27f170->f_10d788(name);
}

/* @implements 0x10daa4 us f_10daa4
   WHAT IT DOES: Returns tone n of slot i's bank, or 0. */
BankTone *f_10daa4(unsigned short i, unsigned short n)
{
    return D_27f170->f_10d860(i, n);
}

/* @implements 0x10dad4 us f_10dad4
   WHAT IT DOES: Returns slot i's flag. */
int f_10dad4(unsigned short i)
{
    return D_27f170->f_10d8e4(i);
}

/* @implements 0x10dafc us f_10dafc
   WHAT IT DOES: Creates the bank list; returns 0. */
int f_10dafc(unsigned int size)
{
    f_10d900(size);
    return 0;
}
}
