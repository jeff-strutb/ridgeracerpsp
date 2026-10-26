/* Menu movie object file (retail 0x06b7b4 to 0x076e90, TU 119): the front end's
   menu screens drive SWG movies (the _root timeline, Navi and course frames, the option icons,
   the wireless and mini-game screens) and format the time, size and percentage strings shown
   in them. Each part below was written separately in its own namespace; the functions keep C
   linkage under their retail addresses. */

/* ---- menuA ---- */
/* TU 119 fragment A (menuA): retail 0x06b7b4 to 0x075bd0, the functions of at most 256 bytes.
   The menu and sequence UI objects: vtable-setting constructors and destructors that call a base
   sub-object at offset 4, small field setters, the wireless menu setup, and a few table helpers.
   Functions are in retail address order within this fragment. */

namespace menuA {

/* Typed access to a field at a byte offset of an object. */
template <typename T>
inline T &at(void *p, unsigned int off)
{
    return *(T *)((char *)p + off);
}

extern "C" {

extern char D_1a6568[];
extern char D_1a6078[];
extern char D_1a6088[];
extern char D_1a609c[];
extern char D_1a60b4[];
extern bool D_2413b8;

void f_04a5f4(void *);
void f_04a618(void *);
void f_04ad30(void *);
void f_04b2d4(void *);
void *f_04b280(void *);
void f_046894(void *, int, int);
void f_046d50(void *, int, int);
void f_0468e8(void *, int, int, int);
void f_04b5c8(void *, const char *, const char *, int);
void f_04b664(void *, const char *, int);
void f_04b290(void *);
void f_02326c(int);
void f_01dee4(int);
void f_079930(void *);
void f_079afc(void *);

/* @implements 0x06e864 us f_06e864
   WHAT IT DOES: Empty function: returns at once. */
void f_06e864(void)
{
}

/* @implements 0x073198 us f_073198
   WHAT IT DOES: Empty function: returns at once. */
void f_073198(void)
{
}

/* @implements 0x074428 us f_074428
   WHAT IT DOES: Empty function: returns at once. */
void f_074428(void)
{
}

/* @implements 0x075b6c us f_075b6c
   WHAT IT DOES: Empty function: returns at once. */
void f_075b6c(void)
{
}

/* @implements 0x06c530 us f_06c530
   WHAT IT DOES: Sets the global flag at 0x2413b8 to true. */
void f_06c530(void)
{
    D_2413b8 = true;
}

/* @implements 0x06c91c us f_06c91c
   WHAT IT DOES: Forwards to the routine at 0x04ad30 on the sub-object at offset 4. */
void f_06c91c(void *self)
{
    f_04ad30((char *)self + 4);
}

/* @implements 0x06c938 us f_06c938
   WHAT IT DOES: Forwards to the routine at 0x04b2d4 on the sub-object at offset 4. */
void f_06c938(void *self)
{
    f_04b2d4((char *)self + 4);
}

/* @draft 0x06e86c us f_06e86c
   WHAT IT DOES: Adds two to a value at or above 40, then adds a constant 0xe4e5a8. */
int f_06e86c(int a)
{
    if (a >= 40)
        a += 2;
    return a + 0xe4e5a8;
}

/* @draft 0x06e888 us f_06e888
   WHAT IT DOES: Adds one when the value is at or above 40, then adds a constant 0xe4e990. */
int f_06e888(int a)
{
    int z = a < 40;
    int r = a + (z == 0);
    return r + 0xe4e990;
}

/* @draft 0x06e8a8 us f_06e8a8
   WHAT IT DOES: Adds one when the value is at or above 40, then adds a constant 0x6dace78. */
int f_06e8a8(int a)
{
    int z = a < 40;
    int r = a + (z == 0);
    return r + 0x6dace78;
}

/* @implements 0x06c540 us f_06c540
   WHAT IT DOES: Base object constructor: sets the vtable at 0x1a6568 and constructs the
   sub-object at offset 4 with the routine at 0x04a5f4. */
void f_06c540(void *self)
{
    *(void **)self = (void *)D_1a6568;
    f_04a5f4((char *)self + 4);
}

/* @implements 0x06c568 us f_06c568
   WHAT IT DOES: Complete object constructor, the same as the base object one. */
void f_06c568(void *self)
{
    *(void **)self = (void *)D_1a6568;
    f_04a5f4((char *)self + 4);
}

/* @implements 0x06c590 us f_06c590
   WHAT IT DOES: Base object destructor: restores the vtable and destroys the sub-object at
   offset 4 with the routine at 0x04a618. */
void f_06c590(void *self)
{
    *(void **)self = (void *)D_1a6568;
    f_04a618((char *)self + 4);
}

/* @implements 0x06c5b8 us f_06c5b8
   WHAT IT DOES: Complete object destructor, the same as the base object one. */
void f_06c5b8(void *self)
{
    *(void **)self = (void *)D_1a6568;
    f_04a618((char *)self + 4);
}

/* @implements 0x06c5e0 us f_06c5e0
   WHAT IT DOES: Deleting destructor: restores the vtable, destroys the sub-object at offset 4,
   then frees the object. */
void f_06c5e0(void *self)
{
    *(void **)self = (void *)D_1a6568;
    f_04a618((char *)self + 4);
    ::operator delete(self);
}

/* @draft 0x073fa8 us f_073fa8
   WHAT IT DOES: Calls the routine at 0x02326c with 2, then the routine at 0x01dee4 with the
   word at offset 512. */
void f_073fa8(void *self)
{
    f_02326c(2);
    f_01dee4(at<int>(self, 512));
}

/* @draft 0x06ca64 us f_06ca64
   WHAT IT DOES: Passes the sub-object at offset 4 through 0x04b280, then calls 0x046894 with
   the result and the two arguments. */
void f_06ca64(void *self, int a1, int a2)
{
    f_046894(f_04b280((char *)self + 4), a1, a2);
}

/* @draft 0x06caa8 us f_06caa8
   WHAT IT DOES: Passes the sub-object at offset 4 through 0x04b280, then calls 0x0468e8 with
   the result and the three arguments. */
void f_06caa8(void *self, int a1, int a2, int a3)
{
    f_0468e8(f_04b280((char *)self + 4), a1, a2, a3);
}

/* @draft 0x06cafc us f_06cafc
   WHAT IT DOES: Passes the sub-object at offset 4 through 0x04b280, then calls 0x046d50 with
   the result and the two arguments. */
void f_06cafc(void *self, int a1, int a2)
{
    f_046d50(f_04b280((char *)self + 4), a1, a2);
}

/* @draft 0x073ea0 us f_073ea0
   WHAT IT DOES: Sets up the WirelessMenu entry with the WirelessLanError text, then clears
   its second entry through the routine at 0x04b664. */
void f_073ea0(void *self)
{
    f_04b5c8((char *)self + 4, D_1a6078, D_1a6088, 0);
    f_04b664((char *)self + 4, D_1a6078, 0);
}

/* @draft 0x073ef8 us f_073ef8
   WHAT IT DOES: Sets up the WirelessMenu entry with the WirelessSwitchOFFType2 text, then
   clears its second entry through the routine at 0x04b664. */
void f_073ef8(void *self)
{
    f_04b5c8((char *)self + 4, D_1a6078, D_1a609c, 0);
    f_04b664((char *)self + 4, D_1a6078, 0);
}

/* @draft 0x073f50 us f_073f50
   WHAT IT DOES: Sets up the WirelessMenu entry with the WirelessCError text, then clears its
   second entry through the routine at 0x04b664. */
void f_073f50(void *self)
{
    f_04b5c8((char *)self + 4, D_1a6078, D_1a60b4, 0);
    f_04b664((char *)self + 4, D_1a6078, 0);
}

/* @draft 0x075b74 us f_075b74
   WHAT IT DOES: For kind 3 only: reads the word at offset 4352, and if it is nonzero clears it
   and, when the word at offset 4 is set, calls 0x04b290 on the sub-object at offset 4. Returns
   the word read, or 0. */
int f_075b74(void *self, int kind)
{
    int r = 0;
    if (kind == 3) {
        int s0 = at<int>(self, 4352);
        char *sub = (char *)self + 4;
        r = s0;
        if (s0) {
            int v2 = at<int>(self, 4);
            at<int>(self, 4352) = 0;
            if (v2)
                f_04b290(sub);
        }
    }
    return r;
}

/* @draft 0x0740ec us f_0740ec
   WHAT IT DOES: Resets the object: clears the word at 2392, runs the routines at 0x079930 and
   0x079afc on two sub-objects, sets the byte at 7532 and the flag words, clears the flag bytes,
   and returns 0. */
int f_0740ec(void *self)
{
    at<int>(self, 2392) = 0;
    f_079930((char *)self + 7296);
    f_079afc((char *)self + 7468);
    int one = 1;
    at<bool>(self, 7532) = true;
    at<int>(self, 2360) = 0;
    at<int>(self, 2364) = one;
    at<int>(self, 2368) = one;
    at<bool>(self, 2372) = false;
    at<bool>(self, 2380) = false;
    at<bool>(self, 2388) = false;
    at<int>(self, 2376) = 0;
    at<bool>(self, 2357) = false;
    at<bool>(self, 2356) = false;
    return 0;
}

} /* extern "C" */

} /* namespace menuA */

/* ---- menuB ---- */
/* Object fragment menuB: retail 0x075bd0..0x076f98 of TU 119 (plus TU 120's gap at 0x076e90..0x076f98).
   The Select menu layers (CBaseMenu and its derived CLoading and CStartMenu): their constructors and
   destructors, their virtual method slots and the small accessors and loops around them. */

namespace menuB {

#define FIELD(T, p, off) (*(T *)((char *)(p) + (off)))

extern "C" {

void f_0231c8(void *p);
void f_04b724(void *p);
void f_0452cc(void *p);
void f_06c540(void *p);
void f_06c590(void *p);
void f_04a560(void *p);
void f_04a580(void *p);
void _ZdlPv(void *p);
extern int D_24139c;
extern char D_1a6530[];
extern char D_1a6490[];
extern char D_1a63f0[];
extern char D_1a6350[];
extern char D_1a62b0[];
void f_0769fc(int a, int b);

/* @implements 0x075c48 us f_075c48
   WHAT IT DOES: Virtual method slot that does nothing and returns 0. */
int f_075c48(void *self) { return 0; }

/* @implements 0x075c6c us f_075c6c
   WHAT IT DOES: Virtual method slot that does nothing. */
void f_075c6c(void *self) { }

/* @implements 0x076280 us f_076280
   WHAT IT DOES: Virtual method slot that does nothing. */
void f_076280(void *self) { }

/* @implements 0x076288 us f_076288
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076288(void *self) { return 0; }

/* @implements 0x076320 us f_076320
   WHAT IT DOES: Virtual method slot that does nothing. */
void f_076320(void *self) { }

/* @implements 0x076a44 us f_076a44
   WHAT IT DOES: Empty virtual method slot. */
void f_076a44(void *self) { }

/* @implements 0x076a4c us f_076a4c
   WHAT IT DOES: Empty virtual method slot. */
void f_076a4c(void *self) { }

/* @implements 0x076a54 us f_076a54
   WHAT IT DOES: Empty virtual method slot. */
void f_076a54(void *self) { }

/* @implements 0x076a5c us f_076a5c
   WHAT IT DOES: Empty virtual method slot. */
void f_076a5c(void *self) { }

/* @implements 0x076a64 us f_076a64
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076a64(void *self) { return 0; }

/* @implements 0x076a6c us f_076a6c
   WHAT IT DOES: Empty virtual method slot. */
void f_076a6c(void *self) { }

/* @implements 0x076a74 us f_076a74
   WHAT IT DOES: Empty virtual method slot. */
void f_076a74(void *self) { }

/* @implements 0x076a7c us f_076a7c
   WHAT IT DOES: Empty virtual method slot. */
void f_076a7c(void *self) { }

/* @implements 0x076a84 us f_076a84
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076a84(void *self) { return 0; }

/* @implements 0x076a8c us f_076a8c
   WHAT IT DOES: Empty virtual method slot. */
void f_076a8c(void *self) { }

/* @implements 0x076a94 us f_076a94
   WHAT IT DOES: Empty virtual method slot. */
void f_076a94(void *self) { }

/* @implements 0x076a9c us f_076a9c
   WHAT IT DOES: Empty virtual method slot. */
void f_076a9c(void *self) { }

/* @implements 0x076aa4 us f_076aa4
   WHAT IT DOES: Empty virtual method slot. */
void f_076aa4(void *self) { }

/* @implements 0x076aac us f_076aac
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076aac(void *self) { return 0; }

/* @implements 0x076ab4 us f_076ab4
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076ab4(void *self) { return 0; }

/* @implements 0x076abc us f_076abc
   WHAT IT DOES: Empty virtual method slot. */
void f_076abc(void *self) { }

/* @implements 0x076ac4 us f_076ac4
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076ac4(void *self) { return 0; }

/* @implements 0x076b2c us f_076b2c
   WHAT IT DOES: Returns the address of the sub-object at offset 3656 of the object. */
void *f_076b2c(char *self) { return self + 3656; }

/* @implements 0x076b34 us f_076b34
   WHAT IT DOES: Returns the address of the sub-object at offset 6736 of the object. */
void *f_076b34(char *self) { return self + 6736; }

/* @implements 0x076b9c us f_076b9c
   WHAT IT DOES: Stores a word at offset 4356 of the object. */
void f_076b9c(char *self, int v) { FIELD(int, self, 4356) = v; }

/* @implements 0x076ba4 us f_076ba4
   WHAT IT DOES: Reads the word at offset 4356 of the object. */
int f_076ba4(char *self) { return FIELD(int, self, 4356); }

/* @implements 0x076c0c us f_076c0c
   WHAT IT DOES: Returns the address of the byte flag block at offset 472 of the object. */
void *f_076c0c(char *self) { return self + 472; }

/* @implements 0x076d50 us f_076d50
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076d50(void *self) { return 0; }

/* @implements 0x076d58 us f_076d58
   WHAT IT DOES: Virtual method slot that returns 0. */
int f_076d58(void *self) { return 0; }

/* @implements 0x076d44 us f_076d44
   WHAT IT DOES: Sets the flag byte at offset 472 of the object to 1. */
void f_076d44(char *self) { FIELD(unsigned char, self, 472) = 1; }

/* @implements 0x075c50 us f_075c50
   WHAT IT DOES: For message code 116, stores the value into a word of the object reached through the pointer at offset 12. */
void f_075c50(char *self, int code, int val)
{
    if (code == 116) {
        char *p = FIELD(char *, self, 12);
        FIELD(int, p, 952) = val;
    }
}

/* @implements 0x07649c us f_07649c
   WHAT IT DOES: Calls the sub-object's function at offset 4 of the object. */
void f_07649c(char *self)
{
    f_04b724(self + 4);
}

/* @implements 0x0769e0 us f_0769e0
   WHAT IT DOES: Calls the sub-object's function at offset 4 of the object. */
void f_0769e0(char *self)
{
    f_04b724(self + 4);
}

/* @implements 0x076300 us f_076300
   WHAT IT DOES: When the flag argument is zero, reads the flag byte at offset 472 of the object reached through the pointer at offset 12, clears it, and returns the old value; otherwise returns 0. */
int f_076300(char *self, int flag)
{
    int v = 0;
    if (flag == 0) {
        char *p = FIELD(char *, self, 12);
        v = FIELD(unsigned char, p, 472);
        if (v) FIELD(unsigned char, p, 472) = 0;
    }
    return v;
}

/* @implements 0x076a24 us f_076a24
   WHAT IT DOES: Calls the shared check at 0x0769fc with the arguments 1 and 0xffff. */
void f_076a24(void *self)
{
    f_0769fc(1, 0xffff);
}

/* @draft 0x0769b8 us f_0769b8
   WHAT IT DOES: For code 3, takes the word at offset 456 of the object, clears it and returns the old value; otherwise returns 0.
   Remaining difference: retail copies the loaded word into the result register in the branch delay slot and shares one return; this form places the clear before the store and the return differently (44 vs 40 bytes). */
int f_0769b8(char *self, int code)
{
    int r = 0;
    if (code == 3) {
        int v = FIELD(int, self, 456);
        if (v) {
            r = v;
            FIELD(int, self, 456) = 0;
        }
    }
    return r;
}

/* @implements 0x0769fc us f_0769fc
   WHAT IT DOES: When the arguments are 1 and 0xffff, clears a word in the static area at 0x24139c. */
void f_0769fc(int a, int b)
{
    if ((b == 0xffff) & (a == 1)) D_24139c = 0;
}

/* @implements 0x076acc us f_076acc
   WHAT IT DOES: Destructor of a menu sub-object (vtable 0x1a6530): stores its vtable and destroys the animation base part. */
void f_076acc(char *self)
{
    *(void **)self = D_1a6530;
    f_04a580(self);
}

/* @implements 0x076af4 us f_076af4
   WHAT IT DOES: Deleting destructor of the sub-object at 0x076acc: destroys it and frees the storage. */
void f_076af4(char *self)
{
    *(void **)self = D_1a6530;
    f_04a580(self);
    _ZdlPv(self);
}

/* @implements 0x076b3c us f_076b3c
   WHAT IT DOES: Destructor of a menu sub-object (vtable 0x1a6490): stores its vtable and destroys the animation base part. */
void f_076b3c(char *self)
{
    *(void **)self = D_1a6490;
    f_04a580(self);
}

/* @implements 0x076b64 us f_076b64
   WHAT IT DOES: Deleting destructor of the sub-object at 0x076b3c: destroys it and frees the storage. */
void f_076b64(char *self)
{
    *(void **)self = D_1a6490;
    f_04a580(self);
    _ZdlPv(self);
}

/* @implements 0x076bac us f_076bac
   WHAT IT DOES: Destructor of a menu sub-object (vtable 0x1a63f0): stores its vtable and destroys the animation base part. */
void f_076bac(char *self)
{
    *(void **)self = D_1a63f0;
    f_04a580(self);
}

/* @implements 0x076bd4 us f_076bd4
   WHAT IT DOES: Deleting destructor of the sub-object at 0x076bac: destroys it and frees the storage. */
void f_076bd4(char *self)
{
    *(void **)self = D_1a63f0;
    f_04a580(self);
    _ZdlPv(self);
}

/* @implements 0x076ce4 us f_076ce4
   WHAT IT DOES: Destructor of a menu sub-object (vtable 0x1a6350): stores its vtable and destroys the animation base part. */
void f_076ce4(char *self)
{
    *(void **)self = D_1a6350;
    f_04a580(self);
}

/* @implements 0x076d0c us f_076d0c
   WHAT IT DOES: Deleting destructor of the sub-object at 0x076ce4: destroys it and frees the storage. */
void f_076d0c(char *self)
{
    *(void **)self = D_1a6350;
    f_04a580(self);
    _ZdlPv(self);
}

/* @implements 0x076e30 us f_076e30
   WHAT IT DOES: Destructor of a menu sub-object (vtable 0x1a62b0): stores its vtable and destroys the animation base part. */
void f_076e30(char *self)
{
    *(void **)self = D_1a62b0;
    f_04a580(self);
}

/* @implements 0x076e58 us f_076e58
   WHAT IT DOES: Deleting destructor of the sub-object at 0x076e30: destroys it and frees the storage. */
void f_076e58(char *self)
{
    *(void **)self = D_1a62b0;
    f_04a580(self);
    _ZdlPv(self);
}

}  /* extern "C" */

}  /* namespace menuB */
