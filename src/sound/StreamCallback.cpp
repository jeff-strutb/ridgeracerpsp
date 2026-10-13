/* The stream callback object file (retail 0x095660 to 0x095704): the sound library's stream
   loop callback and the per channel loop counters it keeps (one stream channel). */

void f_093f90(const char *fmt, ...);

/* How many times each stream channel has looped. */
int D_242c9c[1];

void f_0956f8();

/* @implements 0x095660 us f_095660
   WHAT IT DOES: The stream loop callback: counts a loop of channel 0 and reports it. */
void f_095660(int ch)
{
    if (ch == 0) {
        D_242c9c[ch]++;
        f_093f90("StreamCallback: Stream[%d] LoopCnt:%d \n", ch, D_242c9c[ch]);
    }
}

/* @implements 0x0956a8 us f_0956a8
   WHAT IT DOES: Clears the loop counters. */
void f_0956a8()
{
    f_0956f8();
}

/* @implements 0x0956c4 us f_0956c4
   WHAT IT DOES: Returns a channel's loop count. */
int f_0956c4(int ch)
{
    return D_242c9c[ch];
}

/* @implements 0x0956dc us f_0956dc
   WHAT IT DOES: Clears a channel's loop count. */
int f_0956dc(int ch)
{
    D_242c9c[ch] = 0;
    return 0;
}

/* @implements 0x0956f8 us f_0956f8
   WHAT IT DOES: Clears every channel's loop count. */
void f_0956f8()
{
    int i;
    for (i = 0; i < 1; i++)
        D_242c9c[i] = 0;
}
