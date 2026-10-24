/* The DJ radio's shared helpers (retail 0x10ab7c to 0x10ac24): the stream channel each of the
   four speakers plays on, and the check that no speaker holds a channel. */

void f_093f90(const char *fmt, ...);

/* The speakers' stream channels. */
static const int D_1b25b0[4] = {0, 0, 0, 0};

/* @draft 0x10ab7c us _Z8f_10ab7ci
   WHAT IT DOES: Returns a speaker's stream channel, or -1 for an invalid speaker.
   DRAFT: one word short: retail sign-extends into v1 and copies it to a1 for the print;
   here the sign extension lands in a1 directly. */
int f_10ab7c(int n)
{
    signed char speaker = n;

    if ((unsigned char)speaker < 4)
        return D_1b25b0[speaker];
    f_093f90("RadioCommon: GetPlayCh Failed! Invalid Speaker:%d\n", speaker);
    return -1;
}

/* @implements 0x10abd0 us _Z8f_10abd0v
   WHAT IT DOES: Returns 0 when no speaker holds a stream channel, else -1. */
int f_10abd0(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (D_1b25b0[i] != 0) {
            f_093f90("RadioCommon: CheckPlayCh Failed! Invalid StreamCh:%d Speaker:%d\n", D_1b25b0[i], i);
            return -1;
        }
    }
    return 0;
}
