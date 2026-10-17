/* The race overlay's piece list (retail 0x0f52a4 to 0x0f6534). It holds up to 32 of the
   overlay's pieces (Fj::C2DDecorationBase objects: lap counter, position, timers, the course
   map, the meters...), creates the set of pieces each kind of overlay shows, binds, steps,
   draws and frees them, and passes the overlay's messages on to them. The list belongs to an
   overlay (Fj::CRace2DBase), whose race kind, settings and timers it reads through small
   accessors. */

extern "C" {
void f_101998(void *b);
void f_1019cc(void *b);
void f_101c70(void *piece, unsigned char on);
}

/* The game's settings that pause the race. */
struct GameFlags {
    char m0[11];
    unsigned char m11;
    unsigned char m12;
};
extern GameFlags *D_1d88a0;

/* The race in progress (null outside a race). */
struct RaceInfo {
    char m0[20];
    int m20;   /* the race's kind */
};
extern RaceInfo *D_2407fc;
extern int D_1d3d3c;

namespace Fj {

class C2DList;

/* A piece of the overlay (src/race/Decoration2D.cpp). */
class C2DDecorationBase {
public:
    virtual ~C2DDecorationBase();
    virtual int f_101f44();
    virtual void f_101f4c();
    virtual void f_101f54();
    virtual void f_101b1c(void *group, C2DList *list);
    virtual void Free() = 0;
    virtual void f_101b54();
    virtual void f_101f5c();
    virtual void v9();
    virtual void v10();
    virtual void v11(float t);
};

/* The overlay the list belongs to. */
struct COwner {
    char m0[8];
    int m8;
    int m12;
    int m16;
    int m20;
    int m24;
    int m28;   /* the race kind */
    int m32;
    int m36;
    int m40;
    char m44[1540];
    void *m1584;  /* the sprite group */
};

class C2DList {
public:
    int f_0f52a4(int kind, COwner *owner);
    int f_0f5380(COwner *owner);
    int f_0f5520(COwner *owner);
    int f_0f56c0(COwner *owner);
    int f_0f5854(COwner *owner);
    int f_0f59f4(COwner *owner);
    int f_0f5a14(COwner *owner);
    int f_0f5a34();
    int f_0f5ac8();
    void f_0f5b70();
    void f_0f5be8();
    void f_0f5c08();
    void f_0f5ce4(int id);
    int f_0f62e4(C2DDecorationBase *p);
    void f_0f6314(int id, unsigned char on);
    int f_0f63a8();
    int f_0f63c0();
    int f_0f63d8();
    int f_0f63f0();
    int f_0f6408();
    int f_0f6420();
    int f_0f6438();
    int f_0f6450();
    int f_0f6468();
    int f_0f6494();
    void f_0f64c0(int v);
    int f_0f64d8();
    void f_0f64f4(int v);
    int f_0f6508();
    void f_0f6520();

    C2DDecorationBase *piece[32];
    int count;
    COwner *owner;
    char blink[20];
};

/* @implements 0x0f52a4 us _ZN2Fj7C2DList8f_0f52a4EiPNS_6COwnerE
   WHAT IT DOES: Sets the list up for an overlay: clears it, creates the pieces of the given
   kind of overlay (0 to 3 the race overlays, 4 and 5 the movie overlays), binds them to the
   overlay and resets the list's blink. Returns 1. */
int C2DList::f_0f52a4(int kind, COwner *o)
{
    owner = o;
    f_0f5be8();
    switch (kind) {
    case 4:
        f_0f5a14(owner);
        break;
    case 0:
        f_0f5380(owner);
        break;
    case 1:
        f_0f5520(owner);
        break;
    case 2:
        f_0f56c0(owner);
        break;
    case 3:
        f_0f5854(owner);
        break;
    case 5:
        f_0f59f4(owner);
        break;
    }
    f_0f5c08();
    f_101998(blink);
    return 1;
}

/* @implements 0x0f5380 us _ZN2Fj7C2DList8f_0f5380EPNS_6COwnerE
   WHAT IT DOES: Creates the pieces of the first race overlay: the common pieces, piece 8 and
   piece 20, then the course map for the race kind (18 for kind 20, 19 for kind 21, 17 for
   kinds 2, 4, 6, 11, 13, 15, 18 and 19, otherwise 16). Returns 1. */
int C2DList::f_0f5380(COwner *o)
{
    f_0f5ce4(3);
    f_0f5ce4(4);
    f_0f5ce4(5);
    f_0f5ce4(6);
    f_0f5ce4(7);
    f_0f5ce4(11);
    f_0f5ce4(12);
    f_0f5ce4(13);
    f_0f5ce4(15);
    f_0f5ce4(23);
    f_0f5ce4(1);
    f_0f5ce4(8);
    f_0f5ce4(20);
    if (f_0f63c0() == 20)
        f_0f5ce4(18);
    else if (f_0f63c0() == 21)
        f_0f5ce4(19);
    else if (f_0f63c0() == 2 || f_0f63c0() == 4 || f_0f63c0() == 6 || f_0f63c0() == 11 ||
             f_0f63c0() == 13 || f_0f63c0() == 15 || f_0f63c0() == 18 || f_0f63c0() == 19)
        f_0f5ce4(17);
    else
        f_0f5ce4(16);
    return 1;
}

/* @implements 0x0f5520 us _ZN2Fj7C2DList8f_0f5520EPNS_6COwnerE
   WHAT IT DOES: Creates the pieces of the second race overlay: as the first, with piece 10 in
   place of piece 8. Returns 1. */
int C2DList::f_0f5520(COwner *o)
{
    f_0f5ce4(3);
    f_0f5ce4(4);
    f_0f5ce4(5);
    f_0f5ce4(6);
    f_0f5ce4(7);
    f_0f5ce4(11);
    f_0f5ce4(12);
    f_0f5ce4(13);
    f_0f5ce4(15);
    f_0f5ce4(23);
    f_0f5ce4(1);
    f_0f5ce4(10);
    f_0f5ce4(20);
    if (f_0f63c0() == 20)
        f_0f5ce4(18);
    else if (f_0f63c0() == 21)
        f_0f5ce4(19);
    else if (f_0f63c0() == 2 || f_0f63c0() == 4 || f_0f63c0() == 6 || f_0f63c0() == 11 ||
             f_0f63c0() == 13 || f_0f63c0() == 15 || f_0f63c0() == 18 || f_0f63c0() == 19)
        f_0f5ce4(17);
    else
        f_0f5ce4(16);
    return 1;
}

/* @implements 0x0f56c0 us _ZN2Fj7C2DList8f_0f56c0EPNS_6COwnerE
   WHAT IT DOES: Creates the pieces of the third race overlay: the common pieces, pieces 2 and 8
   (no piece 1 or 20), then the course map for the race kind. Returns 1. */
int C2DList::f_0f56c0(COwner *o)
{
    f_0f5ce4(3);
    f_0f5ce4(4);
    f_0f5ce4(5);
    f_0f5ce4(6);
    f_0f5ce4(7);
    f_0f5ce4(11);
    f_0f5ce4(12);
    f_0f5ce4(13);
    f_0f5ce4(15);
    f_0f5ce4(23);
    f_0f5ce4(2);
    f_0f5ce4(8);
    if (f_0f63c0() == 20)
        f_0f5ce4(18);
    else if (f_0f63c0() == 21)
        f_0f5ce4(19);
    else if (f_0f63c0() == 2 || f_0f63c0() == 4 || f_0f63c0() == 6 || f_0f63c0() == 11 ||
             f_0f63c0() == 13 || f_0f63c0() == 15 || f_0f63c0() == 18 || f_0f63c0() == 19)
        f_0f5ce4(17);
    else
        f_0f5ce4(16);
    return 1;
}

/* @implements 0x0f5854 us _ZN2Fj7C2DList8f_0f5854EPNS_6COwnerE
   WHAT IT DOES: Creates the pieces of the fourth race overlay: as the first, with piece 9 in
   place of piece 8. Returns 1. */
int C2DList::f_0f5854(COwner *o)
{
    f_0f5ce4(3);
    f_0f5ce4(4);
    f_0f5ce4(5);
    f_0f5ce4(6);
    f_0f5ce4(7);
    f_0f5ce4(11);
    f_0f5ce4(12);
    f_0f5ce4(13);
    f_0f5ce4(15);
    f_0f5ce4(23);
    f_0f5ce4(1);
    f_0f5ce4(9);
    f_0f5ce4(20);
    if (f_0f63c0() == 20)
        f_0f5ce4(18);
    else if (f_0f63c0() == 21)
        f_0f5ce4(19);
    else if (f_0f63c0() == 2 || f_0f63c0() == 4 || f_0f63c0() == 6 || f_0f63c0() == 11 ||
             f_0f63c0() == 13 || f_0f63c0() == 15 || f_0f63c0() == 18 || f_0f63c0() == 19)
        f_0f5ce4(17);
    else
        f_0f5ce4(16);
    return 1;
}

/* @implements 0x0f59f4 us _ZN2Fj7C2DList8f_0f59f4EPNS_6COwnerE
   WHAT IT DOES: Creates the piece of the second movie overlay (piece 21). Returns 1. */
int C2DList::f_0f59f4(COwner *o)
{
    f_0f5ce4(21);
    return 1;
}

/* @implements 0x0f5a14 us _ZN2Fj7C2DList8f_0f5a14EPNS_6COwnerE
   WHAT IT DOES: Creates the piece of the first movie overlay (piece 22). Returns 1. */
int C2DList::f_0f5a14(COwner *o)
{
    f_0f5ce4(22);
    return 1;
}

/* @draft 0x0f5a34 us _ZN2Fj7C2DList8f_0f5a34Ev
   WHAT IT DOES: Frees every piece (its own release, then deletes it) and empties the list.
   Returns 1.
   Remaining difference: retail loads each piece into v1 (its vtable through v1, the call
   through v0); here v0 and v1 are swapped. A piece pointer local makes it worse. */
int C2DList::f_0f5a34()
{
    for (int i = 0; i < 32; i++) {
        if (piece[i]) {
            piece[i]->Free();
            delete piece[i];
            piece[i] = 0;
        }
    }
    count = 0;
    return 1;
}

/* @draft 0x0f5ac8 us _ZN2Fj7C2DList8f_0f5ac8Ev
   WHAT IT DOES: Steps the list once a frame unless the game is paused: advances the blink
   and steps every piece. Returns 0.
   Remaining difference: retail keeps the count in a1 and each piece in v1; here v1 and v0
   (the draw loop, the same code without the pause test, matches). */
int C2DList::f_0f5ac8()
{
    GameFlags *g = D_1d88a0;
    if (g->m11 || g->m12)
        return 0;
    f_1019cc(blink);
    for (int i = 0; i < count; i++)
        if (piece[i])
            piece[i]->f_101b54();
    return 0;
}

/* @implements 0x0f5b70 us _ZN2Fj7C2DList8f_0f5b70Ev
   WHAT IT DOES: Draws every piece. */
void C2DList::f_0f5b70()
{
    for (int i = 0; i < count; i++)
        if (piece[i])
            piece[i]->f_101f5c();
}

/* @implements 0x0f5be8 us _ZN2Fj7C2DList8f_0f5be8Ev
   WHAT IT DOES: Empties the list. */
void C2DList::f_0f5be8()
{
    for (int i = 0; i < 32; i++)
        piece[i] = 0;
    count = 0;
}

/* @draft 0x0f5c08 us _ZN2Fj7C2DList8f_0f5c08Ev
   WHAT IT DOES: Binds every piece to the overlay's sprite group and the list and, during a
   race, starts every piece's animation at time zero.
   Remaining difference: the registers of the first loop's call setup (piece in v1, the
   overlay pointer loaded first). */
void C2DList::f_0f5c08()
{
    for (int i = 0; i < count; i++)
        if (piece[i])
            piece[i]->f_101b1c(owner->m1584, this);
    if (D_2407fc) {
        for (int i = 0; i < count; i++)
            if (piece[i])
                piece[i]->v11(0);
    }
}

/* @draft 0x0f62e4 us _ZN2Fj7C2DList8f_0f62e4EPNS_17C2DDecorationBaseE
   WHAT IT DOES: Adds a piece to the list (up to 31). Returns its place, or -1 when the list
   is full.
   Remaining difference: allocation; retail sets the -1 result first into t0 and builds the
   slot address in a2 and the new count in a3 (here a3, a2 and v0, the -1 in the branch
   slot). */
int C2DList::f_0f62e4(C2DDecorationBase *p)
{
    int r = -1;
    int n = count;
    if (n != 31) {
        piece[n] = p;
        r = n;
        count = n + 1;
    }
    return r;
}

/* @implements 0x0f6314 us _ZN2Fj7C2DList8f_0f6314Eih
   WHAT IT DOES: Passes an on/off message to every piece whose id is id. */
void C2DList::f_0f6314(int id, unsigned char on)
{
    for (int i = 0; i < count; i++)
        if (piece[i]->f_101f44() == id)
            f_101c70(piece[i], on);
}

/* @implements 0x0f63a8 us _ZN2Fj7C2DList8f_0f63a8Ev
   WHAT IT DOES: The overlay's word at +24 (0 without an overlay). */
int C2DList::f_0f63a8()
{
    if (owner)
        return owner->m24;
    return 0;
}

/* @implements 0x0f63c0 us _ZN2Fj7C2DList8f_0f63c0Ev
   WHAT IT DOES: The overlay's race kind (0 without an overlay). */
int C2DList::f_0f63c0()
{
    if (owner)
        return owner->m28;
    return 0;
}

/* @implements 0x0f63d8 us _ZN2Fj7C2DList8f_0f63d8Ev
   WHAT IT DOES: The overlay's word at +32 (0 without an overlay). */
int C2DList::f_0f63d8()
{
    if (owner)
        return owner->m32;
    return 0;
}

/* @implements 0x0f63f0 us _ZN2Fj7C2DList8f_0f63f0Ev
   WHAT IT DOES: The overlay's word at +16 (0 without an overlay). */
int C2DList::f_0f63f0()
{
    if (owner)
        return owner->m16;
    return 0;
}

/* @implements 0x0f6408 us _ZN2Fj7C2DList8f_0f6408Ev
   WHAT IT DOES: The overlay's word at +20 (0 without an overlay). */
int C2DList::f_0f6408()
{
    if (owner)
        return owner->m20;
    return 0;
}

/* @implements 0x0f6420 us _ZN2Fj7C2DList8f_0f6420Ev
   WHAT IT DOES: The overlay's word at +12 (0 without an overlay). */
int C2DList::f_0f6420()
{
    if (owner)
        return owner->m12;
    return 0;
}

/* @implements 0x0f6438 us _ZN2Fj7C2DList8f_0f6438Ev
   WHAT IT DOES: The overlay's word at +8 (0 without an overlay). */
int C2DList::f_0f6438()
{
    if (owner)
        return owner->m8;
    return 0;
}

/* @implements 0x0f6450 us _ZN2Fj7C2DList8f_0f6450Ev
   WHAT IT DOES: The overlay's word at +36 (0 without an overlay). */
int C2DList::f_0f6450()
{
    if (owner)
        return owner->m36;
    return 0;
}

/* @draft 0x0f6468 us _ZN2Fj7C2DList8f_0f6468Ev
   WHAT IT DOES: Returns 1 when a race is running and it is of kind 1.
   Remaining difference: retail loads the compared kind 1 separately from the result's 1
   (li a0,1 and li v0,1); here one register holds both. The same spelling for kind 2
   (0x0f6494) is byte-exact. */
int C2DList::f_0f6468()
{
    int r = 1;
    if (!D_2407fc || D_2407fc->m20 != 1)
        r = 0;
    return r;
}

/* @implements 0x0f6494 us _ZN2Fj7C2DList8f_0f6494Ev
   WHAT IT DOES: Returns 1 when a race is running and it is of kind 2. */
int C2DList::f_0f6494()
{
    int r = 1;
    if (!D_2407fc || D_2407fc->m20 != 2)
        r = 0;
    return r;
}

/* @implements 0x0f64c0 us _ZN2Fj7C2DList8f_0f64c0Ei
   WHAT IT DOES: With an overlay, sets the shared overlay setting D_1d3d3c. */
void C2DList::f_0f64c0(int v)
{
    if (owner)
        D_1d3d3c = v;
}

/* @implements 0x0f64d8 us _ZN2Fj7C2DList8f_0f64d8Ev
   WHAT IT DOES: The shared overlay setting D_1d3d3c (1 without an overlay). */
int C2DList::f_0f64d8()
{
    if (owner)
        return D_1d3d3c;
    return 1;
}

/* @implements 0x0f64f4 us _ZN2Fj7C2DList8f_0f64f4Ei
   WHAT IT DOES: With an overlay, sets its word at +40. */
void C2DList::f_0f64f4(int v)
{
    if (owner)
        owner->m40 = v;
}

/* @implements 0x0f6508 us _ZN2Fj7C2DList8f_0f6508Ev
   WHAT IT DOES: The overlay's word at +40 (0 without an overlay). */
int C2DList::f_0f6508()
{
    if (owner)
        return owner->m40;
    return 0;
}

/* @implements 0x0f6520 us _ZN2Fj7C2DList8f_0f6520Ev
   WHAT IT DOES: With an overlay, clears its word at +40. */
void C2DList::f_0f6520()
{
    if (owner)
        owner->m40 = 0;
}

}
