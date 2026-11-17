/* The race random seed (retail 0x0c2a08 to 0x0c2a40, the object file before the race random
   numbers): seeds the first generator of RaceRandom.c from the system clock. */

extern "C" {
extern unsigned int D_245ed0;   /* the seed the first generator is restarted from */
extern unsigned int D_245ed4;   /* the first generator's state */
unsigned int sceKernelGetSystemTimeLow(void);
}

/* @implements 0x0c2a08 us f_0c2a08
   WHAT IT DOES: Seeds the first race generator and its restart seed with the low 16 bits of
   the system clock. */
extern "C" void f_0c2a08(void)
{
    volatile unsigned int t = sceKernelGetSystemTimeLow();
    D_245ed4 = D_245ed0 = t & 0xffff;
}
