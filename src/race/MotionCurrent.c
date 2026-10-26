/* The current motion record's id (retail 0x0cb688 to 0x0cb694): one word in .bss at 0x251dbc
   that the map manager sets before it loads each motion pack of a course. */

extern int D_251dbc;

/* @implements 0x0cb688 us f_0cb688
   WHAT IT DOES: Stores the motion record id in the current motion word at 0x251dbc. */
void f_0cb688(int id)
{
    D_251dbc = id;
}
