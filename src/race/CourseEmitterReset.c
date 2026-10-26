/* The course's sound emitter list (retail 0x0e764c to 0x0e767c): four emitters of 64 bytes
   each, one per sound kind, at the global D_27eac0. The reset marks every emitter as unused,
   and the two hooks that follow it on the course's start and stop paths do nothing. */

struct Emitter {
    int id;                 /* -9999 when the slot is unused */
    int m4[3];
    float prev[4];          /* the position of the last sound (+16) */
    float cur[4];           /* the position given to the sound (+32) */
    int m48[4];
};

/* @implements 0x0e764c us f_0e764c
   WHAT IT DOES: Marks all four emitters of the list as unused by setting each id to -9999. */
void f_0e764c(void *p)
{
    struct Emitter *e = (struct Emitter *)p;
    int id = -9999;
    int n = 3;

    do {
        e->id = id;
        e++;
    } while (--n >= 0);
}

/* @implements 0x0e766c us f_0e766c
   WHAT IT DOES: The course's stop hook for the emitter list: nothing to release. */
void f_0e766c(void *p)
{
    (void)p;
}

/* @implements 0x0e7674 us f_0e7674
   WHAT IT DOES: The course's per-frame hook for the emitter list: nothing to do. */
void f_0e7674(void *p)
{
    (void)p;
}
