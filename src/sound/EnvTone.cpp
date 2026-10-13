/* The environment sound's tone record (retail 0x0970c0 to 0x0970e4): a word and a handle,
   both cleared by the constructors and by the clear method. Its own object file, placed
   after the environment object's static data entries. */

struct CEnvTone {
    CEnvTone();
    void f_0970d8();

    int m0;
    unsigned short m4;
};

/* @implements 0x0970c0 us _ZN8CEnvToneC2Ev
   WHAT IT DOES: Clears the tone record (base object constructor). */
/* @implements 0x0970cc us _ZN8CEnvToneC1Ev
   WHAT IT DOES: Clears the tone record (complete object constructor). */
CEnvTone::CEnvTone()
{
    m0 = 0;
    m4 = 0;
}

/* @implements 0x0970d8 us f_0970d8
   WHAT IT DOES: Clears the tone record's word and handle. */
void CEnvTone::f_0970d8()
{
    m0 = 0;
    m4 = 0;
}
