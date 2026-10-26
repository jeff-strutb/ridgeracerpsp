/* The looping leaf-blow sound's stop (retail 0x0ec35c). The loop has nothing to release when
   the event ends. */

struct LeafLoop;

/* @implements 0x0ec35c us f_0ec35c
   WHAT IT DOES: Nothing (the loop's stop hook). */
void f_0ec35c(struct LeafLoop *s)
{
}
