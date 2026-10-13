/* The display timing settings' object file (retail 0x0992fc to 0x09936c): the base part's
   constructors, which set the default frame layout, and three empty methods. The whole
   object lives in the main loop's file (D_1d88a4). */

struct f_0992fc_t {
    f_0992fc_t();
    int m0[15];
};

struct CDisplayTiming : f_0992fc_t {
    void f_099354(int a, int b);
    void f_09935c();
    void f_099364();
    int m60;
};

/* @implements 0x0992fc us _ZN10f_0992fc_tC2Ev
   WHAT IT DOES: Sets the default settings (base object constructor). */
/* @implements 0x099328 us _ZN10f_0992fc_tC1Ev
   WHAT IT DOES: Same as the base object constructor (complete object constructor). */
f_0992fc_t::f_0992fc_t()
{
    m0[1] = 248;
    m0[2] = 4;
    m0[3] = 480;
    m0[5] = 128;
    m0[12] = 5;
}

/* @implements 0x099354 us f_099354
   WHAT IT DOES: Nothing (the setting it takes is not used). */
void CDisplayTiming::f_099354(int a, int b)
{
}

/* @implements 0x09935c us f_09935c
   WHAT IT DOES: Nothing. */
void CDisplayTiming::f_09935c()
{
}

/* @implements 0x099364 us f_099364
   WHAT IT DOES: Nothing. */
void CDisplayTiming::f_099364()
{
}
