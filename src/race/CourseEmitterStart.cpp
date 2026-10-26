/* A course sound emitter is started at a position (retail 0x0e767c to 0x0e7718). The emitter
   list (D_27eac0) is the one reset by 0x0e764c: four emitters of 64 bytes, one per sound kind.
   Starting one moves its current position to the previous one, stores the new position and
   stamps the emitter with the global count D_23faec. */

struct Vec4 {
    float x, y, z, w;
};

struct Emitter {
    int id;                 /* the stamp: the count when the emitter was last started */
    int m4[3];
    Vec4 prev;              /* the position of the last start (+16) */
    Vec4 cur;               /* the position given to the start (+32) */
    int m48[4];
};

extern "C" void f_027e0c(void);

extern int D_23faec;        /* the count stamped into an emitter */

/* @draft 0x0e767c us f_0e767c
   WHAT IT DOES: Starts the emitter of the given kind at (x, y, z). Its previous position
   becomes the old current one, and the new position is stored with its w word; the
   stamp is the count. Unless the stamp is below the count less one, the three words after
   the position are cleared first (otherwise f_027e0c runs). */
extern "C" void f_0e767c(void *emitters, int kind, float x, float y, float z)
{
    Emitter *e = (Emitter *)emitters + kind;
    int n = D_23faec;

    e->cur.x = x;
    e->cur.y = y;
    e->cur.z = z;
    if (e->id < n - 1) {
        e->m48[0] = 0;
        e->m48[1] = 0;
        e->m48[2] = 0;
    } else {
        f_027e0c();
    }
    e->id = n;
    e->prev = e->cur;
}
