/* The NU Sound bank API wrappers (retail 0x10d334 to 0x10d44c, a gap row with no unwind
   information): loading a bank into the bank list, a bank status query, a bank lookup that
   passes its id on, and two wrappers that call the routines at 0x10c65c, 0x10da0c and
   0x10d9bc. The bank list itself is in SoundBank.cpp. The callee names are the ones
   SoundBank.cpp and SasVoice.c use. */

/* Loads a bank into the bank list; the id receives the new slot. Returns the load's error,
   or 0x80000000 when no id pointer was given. */
int f_10d988(void *h, void *src, unsigned short *id);
int f_10d9bc(void);
void f_10d9dc(unsigned short h, int *id);
void f_10da0c(void);
int f_10da30(unsigned short bank);
void f_10c65c(void);

/* @implements 0x10d334 us f_10d334
   WHAT IT DOES: Loads a bank (its header, its source data and the slot id it gets back): the
   load's own result, or 0x80000000 when no id pointer was given. */
int f_10d334(void *h, void *src, unsigned short *id)
{
    int r = 0x80000000;

    if (id)
        r = f_10d988(h, src, id);
    return r;
}

/* @implements 0x10d360 us f_10d360
   WHAT IT DOES: Runs the sound system's helper routine at 0x10d9bc and returns its result. */
int f_10d360(void)
{
    return f_10d9bc();
}

/* @implements 0x10d37c us f_10d37c
   WHAT IT DOES: Reads the status of bank ch into *status: 3 when the bank is loaded (the
   lookup at 0x10da30 succeeds), else 0. Returns 0x8000001f for a bank number past 63, or
   0x80000024 when no status pointer was given. */
int f_10d37c(unsigned short ch, unsigned short *status)
{
    if (ch >= 64)
        return 0x8000001f;
    if (!status)
        return 0x80000024;
    if (f_10da30(ch))
        *status = 0;
    else
        *status = 3;
    return 0;
}

/* @implements 0x10d3e0 us f_10d3e0
   WHAT IT DOES: Calls the routines at 0x10c65c and 0x10da0c in turn and returns 0. */
int f_10d3e0(void)
{
    f_10c65c();
    f_10da0c();
    return 0;
}

/* @implements 0x10d408 us f_10d408
   WHAT IT DOES: Looks up bank h (a handle below 64) and passes it with the id pointer to the
   routine at 0x10d9dc, then returns 0. Returns 0x8000001f for a handle past 63, or
   0x80000023 when no id pointer was given. */
int f_10d408(unsigned short h, int *id)
{
    if (h >= 64)
        return 0x8000001f;
    if (!id)
        return 0x80000023;
    f_10d9dc(h, id);
    return 0;
}
