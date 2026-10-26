/* Object file at retail 0x0bd328 to 0x0bd400 (the eh object TU 224 and its gap TU 225): a
   chain of small reset calls on one record. The first function resets a global block when its
   two arguments match a fixed pair; the record reset calls two sub-reset helpers, one of which
   is an empty stub; the last function is the fixed-pair call with arguments 1 and 0xffff. */

extern "C" {
void f_0bd39c(void *p);
void f_0bd3d8(void *p);
void f_0bd36c(void *p);
void f_0bd3a4(void *p);
void f_0bd328(int a, int b);
}

extern char D_2456e0[];

/* @implements 0x0bd328 us f_0bd328
   WHAT IT DOES: when a is 1 and b is 0xffff, resets the block at D_2456e0 through f_0bd36c. */
extern "C" void f_0bd328(int a, int b)
{
    if (b == 0xffff && a == 1) {
        f_0bd36c(D_2456e0);
    }
}

/* @implements 0x0bd36c us f_0bd36c
   WHAT IT DOES: resets the record at p+1632 and calls the sub-reset helper on the record. */
extern "C" void f_0bd36c(void *p)
{
    f_0bd3a4(p);
    f_0bd39c((char *)p + 1632);
}

/* @implements 0x0bd39c us f_0bd39c
   WHAT IT DOES: empty stub. */
extern "C" void f_0bd39c(void *p)
{
}

/* @implements 0x0bd3a4 us f_0bd3a4
   WHAT IT DOES: calls the reset helper on p+576, then on the record at p+1056. */
extern "C" void f_0bd3a4(void *p)
{
    f_0bd39c((char *)p + 576);
    f_0bd3d8((char *)p + 1056);
}

/* @implements 0x0bd3d8 us f_0bd3d8
   WHAT IT DOES: empty stub. */
extern "C" void f_0bd3d8(void *p)
{
}

/* @implements 0x0bd3e0 us f_0bd3e0
   WHAT IT DOES: calls f_0bd328 with a = 1 and b = 0xffff. */
extern "C" void f_0bd3e0(void)
{
    f_0bd328(1, 0xffff);
}
