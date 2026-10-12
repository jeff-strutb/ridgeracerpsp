/* Retail 0x002fe8 to 0x00322c: one step of the decoder for the packed format of RRP.DAT, and
   the accessors of a record of settings made of single values and tables of value pairs. */

#include <string.h>

/* The decoder of the packed format; it keeps no state of its own. */
struct Lz {
    void f_002fe8(unsigned char **dst, unsigned char **src);
};

/* @implements 0x002fe8 us f_002fe8
   WHAT IT DOES: Decodes one token of the packed format. A 16 bit code above 0xfeff is a run of
   1 to 256 literal bytes copied from the input; any other code copies 3 to 34 bytes from 1 to
   2048 bytes back in the output. Both pointers are advanced. */
void Lz::f_002fe8(unsigned char **dst, unsigned char **src)
{
    int code;

    code = *(*src)++;
    code |= *(*src)++ << 8;
    if (code > 0xfeff) {
        int n = (code & 0xff) + 1;
        memmove(*dst, *src, n);
        *src += n;
        *dst += n;
    } else {
        int len = (code & 0x1f) + 3;
        int dist = (code >> 5) + 1;
        int i;
        for (i = 0; i < len; i++)
            (*dst)[i] = (*dst)[i - dist];
        *dst += len;
    }
}

/* Two values kept together. */
struct Pair {
    int a;
    int b;
    Pair() { a = 0; }
};

/* The record of settings. */
struct Settings {
    int m0;
    int m4;
    int m8;
    Pair m12;
    unsigned char m20;
    Pair first[16];
    int m152;
    Pair second[16];
    int m284;
    int m288;
    int m292;
    Pair third[16];

    void f_0030c0(int v);
    void f_0030c8(int v);
    void f_0030d0(Pair p);
    void f_0030ec(unsigned char v);
    void f_0030f4();
    void f_003150(int i, Pair p);
    void f_00317c(int i, Pair p);
    void f_0031a8(int v);
    int f_0031b0();
    int f_0031b8();
    Pair f_0031c0();
    unsigned char f_0031d4();
    Pair f_0031dc(int i);
    Pair f_003200(int i);
    int f_003224();
};

/* @implements 0x0030c0 us f_0030c0
   WHAT IT DOES: Sets the first single value. */
void Settings::f_0030c0(int v)
{
    m4 = v;
}

/* @implements 0x0030c8 us f_0030c8
   WHAT IT DOES: Sets the second single value. */
void Settings::f_0030c8(int v)
{
    m8 = v;
}

/* @implements 0x0030d0 us f_0030d0
   WHAT IT DOES: Sets the pair of values. */
void Settings::f_0030d0(Pair p)
{
    m12 = p;
}

/* @implements 0x0030ec us f_0030ec
   WHAT IT DOES: Sets the flag. */
void Settings::f_0030ec(unsigned char v)
{
    m20 = v;
}

/* @draft 0x0030f4 us f_0030f4
   WHAT IT DOES: Clears the first value of every pair in the first two tables. */
void Settings::f_0030f4()
{
    int i;

    for (i = 0; i < 2; i++) {
        first[i] = Pair();
        second[i] = Pair();
    }
    for (i = 0; i < 15; i++) {
        first[i] = Pair();
        second[i] = Pair();
    }
}

/* @implements 0x003150 us f_003150
   WHAT IT DOES: Sets one pair of the first table. */
void Settings::f_003150(int i, Pair p)
{
    first[i] = p;
}

/* @implements 0x00317c us f_00317c
   WHAT IT DOES: Sets one pair of the third table. */
void Settings::f_00317c(int i, Pair p)
{
    third[i] = p;
}

/* @implements 0x0031a8 us f_0031a8
   WHAT IT DOES: Sets the third single value. */
void Settings::f_0031a8(int v)
{
    m288 = v;
}

/* @implements 0x0031b0 us f_0031b0
   WHAT IT DOES: Returns the first single value. */
int Settings::f_0031b0()
{
    return m4;
}

/* @implements 0x0031b8 us f_0031b8
   WHAT IT DOES: Returns the second single value. */
int Settings::f_0031b8()
{
    return m8;
}

/* @implements 0x0031c0 us f_0031c0
   WHAT IT DOES: Returns the pair of values. */
Pair Settings::f_0031c0()
{
    return m12;
}

/* @implements 0x0031d4 us f_0031d4
   WHAT IT DOES: Returns the flag. */
unsigned char Settings::f_0031d4()
{
    return m20;
}

/* @implements 0x0031dc us f_0031dc
   WHAT IT DOES: Returns one pair of the first table. */
Pair Settings::f_0031dc(int i)
{
    return first[i];
}

/* @implements 0x003200 us f_003200
   WHAT IT DOES: Returns one pair of the third table. */
Pair Settings::f_003200(int i)
{
    return third[i];
}

/* @implements 0x003224 us f_003224
   WHAT IT DOES: Returns the third single value. */
int Settings::f_003224()
{
    return m288;
}
