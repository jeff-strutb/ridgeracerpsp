/* The two ended heap object file (retail 0x0995e0 to 0x099718): a memory block (given, or
   allocated here) handed out from both ends. Each end can be marked and later released
   back to its mark; a reset returns both ends to the block's limits. */

#include <stdlib.h>

typedef struct StackHeap {
    int size;
    char *owned;
    char *base;
    char *limit;
    char *end[2];
} StackHeap;

/* A mark in a two ended heap: which end, and how far it had grown. */
typedef struct Mark {
    int side;
    char *pos;
} Mark;

/* @implements 0x0995e0 us f_0995e0
   WHAT IT DOES: Sets the heap up on a block of the given size; without a block, allocates
   one (and owns it). Both ends start at the block's limits. */
void f_0995e0(StackHeap *h, int size, char *block)
{
    if (block == 0) {
        block = malloc(size);
        h->owned = block;
    }
    h->size = size;
    h->base = block;
    h->limit = block + size;
    h->end[0] = h->base;
    h->end[1] = h->limit;
}

/* @implements 0x099640 us f_099640
   WHAT IT DOES: Frees the block if the heap owns it and clears the ends. */
void f_099640(StackHeap *h)
{
    if (h->owned) {
        free(h->owned);
        h->owned = 0;
        h->end[1] = 0;
        h->end[0] = 0;
    }
}

/* @implements 0x099684 us f_099684
   WHAT IT DOES: Takes a size from the bottom end (returning its start) or from the top end
   (returning the new top). */
char *f_099684(StackHeap *h, int size, int fromTop)
{
    char *p;
    if (fromTop) {
        h->end[1] -= size;
        p = h->end[1];
    } else {
        p = h->end[0];
        h->end[0] = p + size;
    }
    return p;
}

/* @implements 0x0996b0 us f_0996b0
   WHAT IT DOES: Returns a mark of one end's current position. */
Mark f_0996b0(StackHeap *h, int side)
{
    Mark m;
    Mark r;
    m.side = side;
    m.pos = h->end[side];
    r = m;
    return r;
}

/* @implements 0x0996cc us f_0996cc
   WHAT IT DOES: Returns the free space between the two ends. */
int f_0996cc(StackHeap *h)
{
    return h->end[1] - h->end[0];
}

/* @implements 0x0996dc us f_0996dc
   WHAT IT DOES: Releases an end back to a mark. */
void f_0996dc(StackHeap *h, Mark m)
{
    h->end[m.side] = m.pos;
}

/* @implements 0x0996fc us f_0996fc
   WHAT IT DOES: Returns both ends to the block's limits. */
void f_0996fc(StackHeap *h)
{
    h->end[0] = h->base;
    h->end[1] = h->limit;
}

/* @implements 0x099710 us f_099710
   WHAT IT DOES: Nothing (an empty check). */
void f_099710(StackHeap *h)
{
}
