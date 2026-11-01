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

/* @implements 0x06e86c us f_06e86c
   WHAT IT DOES: Adds two to a value at or above 40, then adds a constant 0xe4e5a8. */
int f_06e86c(int a)
{
    if (a >= 40)
        a += 2;
    return a + 0xe4e5a8;
}

/* @implements 0x06e888 us f_06e888
   WHAT IT DOES: Adds one when the value is at or above 40, then adds a constant 0xe4e990. */
int f_06e888(int a)
{
    int z = a < 40;
    int r = a + (z == 0);
    return r + 0xe4e990;
}

/* @implements 0x06e8a8 us f_06e8a8
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

/* @implements 0x073fa8 us f_073fa8
   WHAT IT DOES: Calls the routine at 0x02326c with 2, then the routine at 0x01dee4 with the
   word at offset 512. */
void f_073fa8(void *self)
{
    f_02326c(2);
    f_01dee4(at<int>(self, 512));
}

/* @implements 0x06ca64 us f_06ca64
   WHAT IT DOES: Passes the sub-object at offset 4 through 0x04b280, then calls 0x046894 with
   the result and the two arguments. */
void f_06ca64(void *self, int a1, int a2)
{
    f_046894(f_04b280((char *)self + 4), a1, a2);
}

/* @implements 0x06caa8 us f_06caa8
   WHAT IT DOES: Passes the sub-object at offset 4 through 0x04b280, then calls 0x0468e8 with
   the result and the three arguments. */
void f_06caa8(void *self, int a1, int a2, int a3)
{
    f_0468e8(f_04b280((char *)self + 4), a1, a2, a3);
}

/* @implements 0x06cafc us f_06cafc
   WHAT IT DOES: Passes the sub-object at offset 4 through 0x04b280, then calls 0x046d50 with
   the result and the two arguments. */
void f_06cafc(void *self, int a1, int a2)
{
    f_046d50(f_04b280((char *)self + 4), a1, a2);
}

/* @implements 0x073ea0 us f_073ea0
   WHAT IT DOES: Sets up the WirelessMenu entry with the WirelessLanError text, then clears
   its second entry through the routine at 0x04b664. */
void f_073ea0(void *self)
{
    f_04b5c8((char *)self + 4, D_1a6078, D_1a6088, 0);
    f_04b664((char *)self + 4, D_1a6078, 0);
}

/* @implements 0x073ef8 us f_073ef8
   WHAT IT DOES: Sets up the WirelessMenu entry with the WirelessSwitchOFFType2 text, then
   clears its second entry through the routine at 0x04b664. */
void f_073ef8(void *self)
{
    f_04b5c8((char *)self + 4, D_1a6078, D_1a609c, 0);
    f_04b664((char *)self + 4, D_1a6078, 0);
}

/* @implements 0x073f50 us f_073f50
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
            if (v2) {
                f_04b290(sub);
                r = s0;
            }
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

/* @implements 0x0769b8 us f_0769b8
   WHAT IT DOES: For code 3, takes the word at offset 456 of the object, clears it and returns the old value; otherwise returns 0. */
int f_0769b8(char *self, int code)
{
    int r = 0;
    if (code == 3) {
        int v = FIELD(int, self, 456);
        if (v)
            FIELD(int, self, 456) = 0;
        r = v;
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

/* ---- menuC ---- */
namespace menuC {

template <typename T>
inline T &at(void *p, unsigned int off)
{
    return *(T *)((char *)p + off);
}

extern "C" {
extern unsigned int D_245194;
void f_06c540(void *);
void f_06c590(void *);
void f_04a560(void *);
void f_04a580(void *);
extern char D_1a6388[];
extern char D_1a63f0[];
extern char D_1a6490[];
extern char D_1a6428[];
void f_07931c(void *);
void f_0792a0(void *);
void f_07a9d8(void *);
void f_07a08c(void *);
void f_07aa54(void *);
void f_07a108(void *);
extern char D_1a62e8[];
extern char D_1a6350[];
extern char D_1a6248[];
extern char D_1a62b0[];
void _ZdlPv(void *);
}

struct MBase {
    char b[456];
    MBase() { f_06c540(this); }
    ~MBase() { f_06c590(this); }
};
struct MSub {
    char b[8];
    MSub() { f_04a560(this); *(void **)this = D_1a63f0; }
    ~MSub() { *(void **)this = D_1a63f0; f_04a580(this); }
};
struct MDer : MBase {
    MDer() {
        *(void **)this = D_1a6388;
        f_04a560((char *)this + 456);
        *(void **)((char *)this + 456) = D_1a63f0;
    }
    ~MDer() {
        *(void **)this = D_1a6388;
        *(void **)((char *)this + 456) = D_1a63f0;
        f_04a580((char *)this + 456);
    }
};
#define MENU_CLASS(N, VT1, VT2, OFF) \
    struct N : MBase { \
        ~N() { \
            *(void **)this = VT1; \
            *(void **)((char *)this + OFF) = VT2; \
            f_04a580((char *)this + OFF); \
        } \
    };
MENU_CLASS(MD1, D_1a6388, D_1a63f0, 456)
MENU_CLASS(MD2, D_1a62e8, D_1a6350, 456)
MENU_CLASS(MD3, D_1a6248, D_1a62b0, 460)
struct MB2 : MBase {
    char b[884 - 456];
    MB2() {
        *(void **)this = D_1a6428;
        char *sub = (char *)this + 456;
        f_04a560(sub);
        *(void **)((char *)this + 456) = D_1a6490;
        sub[16] = 0;
    }
    ~MB2() {
        *(void **)((char *)this + 456) = D_1a6490;
        f_04a580((char *)this + 456);
    }
};
struct NBase {
    char b[456];
    NBase() { f_06c540(this); *(void **)this = D_1a6428; }
    ~NBase() { f_06c590(this); }
};
struct NSub {
    char b[428];
    NSub() { f_04a560(this); *(void **)this = D_1a6490; b[16] = 0; }
    ~NSub() { *(void **)this = D_1a6490; f_04a580(this); }
};
struct MM3 { char c[128]; MM3() { f_0792a0(this); } ~MM3() { f_07931c(this); } };
struct MM2 { char c[24]; MM2() { f_07a9d8(this); } ~MM2() { f_07aa54(this); } };
struct MM1 { char c[8]; MM1() { f_07a08c(this); } ~MM1() { f_07a108(this); } };
struct MN : MB2 {
    MM3 m3;
    MM2 m2;
    MM1 m1;
    ~MN() { *(void **)this = D_1a6428; }
};
struct MN2 : NBase, NSub {
    MM3 m3;
    MM2 m2;
    MM1 m1;
};
struct B4 { signed char c0, c1, c2, c3; };
struct B8 { B4 a; B4 b; };
inline void *operator new(unsigned int, void *p) { return p; }

extern "C" {
void *f_092970(void);
void f_0929b4(void *, int);
int f_0780e0(void *);
void f_0231c8(int);
void f_04b724(void *);
void f_0230e0(void *);
void *f_04b280(void *);
void f_1166d4(int);
void f_116898(int);
void *f_0477b0(void *, int, int, float, float, float, float, int, int, void *);
void *f_046de0(void *, int, int, float, float, float, float, int, int, void *);
void *f_047248(void *, int, int, float, float, float, float, float, float, int, int, void *);
void *f_048410(void *, int, int, float, float, float, float, int, int, void *, float, float);
void *f_048d1c(void *, int, int, float, float, float, float, int, int, int, void *, int);
int f_0e7858(int);
void f_0e7768(void);
void f_0e798c(void);
extern bool D_241444;
void f_0452cc(void);
int f_04311c(void *);
int f_006018(void);
extern char D_1d8910[];

/* @implements 0x076760 us f_076760
   WHAT IT DOES: copies the byte at src+12 into self+522 and the word at src+8 into self+476, returning 0. */
int f_076760(void *self, void *src)
{
    at<bool>(self, 522) = at<bool>(src, 12);
    at<int>(self, 476) = at<int>(src, 8);
    return 0;
}

/* @implements 0x07655c us f_07655c
   WHAT IT DOES: handles a menu event: code 99 with value 314 sets the flag at parent+521, code 111 sets the word at parent+456 to 1. */
void f_07655c(void *self, int a, int b)
{
    if (a == 99) {
        if (b == 314) {
            void *o = at<void *>(self, 12);
            at<char>(o, 521) = 1;
        }
    } else if (a == 111) {
        void *o = at<void *>(self, 12);
        at<int>(o, 456) = 1;
    }
}

/* @implements 0x076004 us f_076004
   WHAT IT DOES: if bit 3 of D_245194 is set, sets the words at self+20 and self+952 to 1 and calls f_0929b4 on the f_092970 object with 0. */
void f_076004(void *self)
{
    if (D_245194 & 8) {
        at<int>(self, 20) = 1;
        at<int>(self, 952) = 1;
        f_0929b4(f_092970(), 0);
    }
}

/* @implements 0x07604c us f_07604c
   WHAT IT DOES: if f_0780e0(p) returns 1, copies the word at p+12 into self+956 and returns 1, else returns 0. */
int f_07604c(void *self, void *p)
{
    int r = 0;
    if (f_0780e0(p) == 1) {
        at<int>(self, 956) = at<int>(p, 12);
        r = 1;
    }
    return r;
}

/* @implements 0x075e10 us f_075e10
   WHAT IT DOES: constructs the menu object in place (base constructor f_06c540, then vtables and the sub-object at +456). */
void f_075e10(void *self) { new (self) MDer; }

/* @implements 0x075e70 us f_075e70
   WHAT IT DOES: constructs the menu object in place (twin of f_075e10). */
void f_075e70(void *self) { new (self) MDer; }

/* @implements 0x075ed0 us f_075ed0
   WHAT IT DOES: destroys the menu object: resets the vtables, destroys the sub-object at +456 (f_04a580), then the base (f_06c590). */
void f_075ed0(MDer *self) { self->~MDer(); }

/* @implements 0x075f34 us f_075f34
   WHAT IT DOES: destroys the menu object (twin of f_075ed0). */
void f_075f34(MDer *self) { self->~MDer(); }

/* @implements 0x076c14 us f_076c14
   WHAT IT DOES: destroys the menu object, storing its vtables and destroying the sub-object at +456 and the base. */
void f_076c14(MD2 *self) { self->~MD2(); }

/* @implements 0x076d60 us f_076d60
   WHAT IT DOES: destroys the menu object, storing its vtables and destroying the sub-object at +460 and the base. */
void f_076d60(MD3 *self) { self->~MD3(); }

/* @implements 0x075f98 us f_075f98
   WHAT IT DOES: destroys the menu object and then frees its memory with operator delete. */
void f_075f98(MD1 *self) { self->~MD1(); _ZdlPv(self); }

/* @implements 0x076c78 us f_076c78
   WHAT IT DOES: destroys the menu object and then frees its memory with operator delete. */
void f_076c78(MD2 *self) { self->~MD2(); _ZdlPv(self); }

/* @implements 0x076dc4 us f_076dc4
   WHAT IT DOES: destroys the menu object and then frees its memory with operator delete. */
void f_076dc4(MD3 *self) { self->~MD3(); _ZdlPv(self); }

/* @implements 0x0760a0 us f_0760a0
   WHAT IT DOES: if f_0780e0(p) returns 1, stores self+956 into p+12 and self+952 into p+8 and returns 1, else returns 0. */
int f_0760a0(void *self, void *p)
{
    int r = 0;
    if (f_0780e0(p) == 1) {
        at<int>(p, 12) = at<int>(self, 956);
        at<int>(p, 8) = at<int>(self, 952);
        r = 1;
    }
    return r;
}

/* @implements 0x076290 us f_076290
   WHAT IT DOES: releases the ten handles at self+968 that are not -1 via f_0231c8, then calls f_04b724 on the sub-object at self+4. */
void f_076290(void *self)
{
    for (int i = 0; i < 10; i++) {
        int v = at<int>(self, 968 + i * 4);
        if (v != -1)
            f_0231c8(v);
    }
    f_04b724((char *)self + 4);
}

/* @implements 0x075bd0 us f_075bd0
   WHAT IT DOES: releases the 101 handles at self+476 that are not -1 via f_0231c8, then calls f_04b724 on self+4 and f_0452cc. */
void f_075bd0(void *self)
{
    for (int i = 0; i < 101; i++) {
        int v = at<int>(self, 476 + i * 4);
        if (v != -1)
            f_0231c8(v);
    }
    f_04b724((char *)self + 4);
    f_0452cc();
}

/* @implements 0x074398 us f_074398
   WHAT IT DOES: handles a menu event: code 112 maps values 1..4 to 2,4,1,3 stored at parent+4352, code 115 stores the value at parent+1024. */
void f_074398(void *self, int a, int b)
{
    switch (a) {
    case 112:
        if (b == 1)
            at<int>(at<void *>(self, 12), 4352) = 2;
        else if (b == 2)
            at<int>(at<void *>(self, 12), 4352) = 4;
        else if (b == 3)
            at<int>(at<void *>(self, 12), 4352) = 1;
        else if (b == 4)
            at<int>(at<void *>(self, 12), 4352) = 3;
        break;
    case 113:
        break;
    case 115:
        at<int>(at<void *>(self, 12), 1024) = b;
        break;
    }
}

/* @implements 0x075620 us f_075620
   WHAT IT DOES: when self+880 is 4 and the flag at self+1020 is set, steps the selection at self+4356 by the sign of f_04311c(D_1d8910), wrapping it to the range 1..24. */
void f_075620(void *self)
{
    if (at<int>(self, 880) == 4 && at<bool>(self, 1020)) {
        int r = f_04311c(D_1d8910);
        if (r < 0)
            at<int>(self, 4356) = at<int>(self, 4356) - 1;
        else if (r > 0)
            at<int>(self, 4356) = at<int>(self, 4356) + 1;
        int v = at<int>(self, 4356);
        if (v >= 25) {
            at<int>(self, 4356) = 1;
            v = 1;
        }
        if (v <= 0)
            at<int>(self, 4356) = 24;
    }
}

/* @implements 0x0764b8 us f_0764b8
   WHAT IT DOES: answers a query code: 4 returns the byte at parent+522, 5 returns and clears the flag at parent+453, 75 returns the word at parent+476, 100 returns f_006018(), 111 sets parent+456 to 1; else 0. */
int f_0764b8(void *self, int a)
{
    int r;
    switch (a) {
    case 4:
        r = at<bool>(at<void *>(self, 12), 522);
        break;
    case 5: {
        void *o = at<void *>(self, 12);
        if (at<bool>(o, 453)) {
            r = 1;
            at<bool>(o, 453) = 0;
        } else
            r = 0;
        break;
    }
    case 75:
        r = at<int>(at<void *>(self, 12), 476);
        break;
    case 100:
        r = f_006018();
        break;
    case 111:
        at<int>(at<void *>(self, 12), 456) = 1;
    default:
        r = 0;
        break;
    }
    return r;
}

/* @implements 0x0753e4 us f_0753e4
   WHAT IT DOES: destroys the composite menu object, resetting its vtable and destroying its member sub-objects and base. */
void f_0753e4(MN *self) { self->~MN(); }

/* @implements 0x0754a0 us f_0754a0
   WHAT IT DOES: destroys the composite menu object (twin of f_0753e4). */
void f_0754a0(MN *self) { self->~MN(); }

/* @implements 0x07363c us f_07363c
   WHAT IT DOES: reads a packed table header at p+4 and, for each entry, sets the slot at self+2396+index*4 to -1. */
void f_07363c(void *self, char *p)
{
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        at<int>(self, 2396 + *(int *)&t.b * 4) = -1;
        i++;
    } while (i < *(int *)&t.h);
    }
}


/* @implements 0x07555c us f_07555c
   WHAT IT DOES: destroys the composite menu object and then frees its memory with operator delete. */
void f_07555c(MN *self) { self->~MN(); _ZdlPv(self); }

/* @draft 0x076904 us f_076904
   WHAT IT DOES: if the flags at self+521 and 523 allow, initialises the f_0e7768 helper once, polls f_0e7858(1) and on the pending condition calls f_0e798c, sets self+20 to 1 and clears the flags at +520 and +521; returns 0 or 1. */
int f_076904(void *self)
{
    if (!at<bool>(self, 521))
        return 0;
    if (!at<bool>(self, 523))
        return 1;
    if (!D_241444) {
        f_0e7768();
        D_241444 = 1;
    }
    int a = f_0e7858(1);
    if (at<bool>(self, 520) && ((D_245194 & 1) || a)) {
        f_0e798c();
        at<int>(self, 20) = 1;
        at<bool>(self, 520) = 0;
        at<bool>(self, 521) = 0;
    }
    return 0;
}


/* @implements 0x06cb40 us f_06cb40
   WHAT IT DOES: fetches the object at self+4 with f_04b280 and, bracketed by f_1166d4(9) and f_116898(9), calls f_0477b0 with the arguments and self+44, returning its result. */
void *f_06cb40(void *self, int a1, int a2, float x0, float x1, float x2, float x3, int a3, int a4)
{
    void *o = f_04b280((char *)self + 4);
    f_1166d4(9);
    void *r = f_0477b0(o, a1, a2, x0, x1, x2, x3, a3, a4, (char *)self + 44);
    f_116898(9);
    return r;
}

/* @implements 0x06cc1c us f_06cc1c
   WHAT IT DOES: fetches the object at self+4 with f_04b280 and, bracketed by f_1166d4(9) and f_116898(9), calls f_046de0 with the arguments and self+44, returning its result. */
void *f_06cc1c(void *self, int a1, int a2, float x0, float x1, float x2, float x3, int a3, int a4)
{
    void *o = f_04b280((char *)self + 4);
    f_1166d4(9);
    void *r = f_046de0(o, a1, a2, x0, x1, x2, x3, a3, a4, (char *)self + 44);
    f_116898(9);
    return r;
}

/* @implements 0x06ccf8 us f_06ccf8
   WHAT IT DOES: fetches the object at self+4 with f_04b280 and, bracketed by f_1166d4(9) and f_116898(9), calls f_047248 with the arguments and self+44, returning its result. */
void *f_06ccf8(void *self, int a1, int a2, float x0, float x1, float x2, float x3, float x4, float x5, int a3, int a4)
{
    void *o = f_04b280((char *)self + 4);
    f_1166d4(9);
    void *r = f_047248(o, a1, a2, x0, x1, x2, x3, x4, x5, a3, a4, (char *)self + 44);
    f_116898(9);
    return r;
}

/* @implements 0x06cdf4 us f_06cdf4
   WHAT IT DOES: fetches the object at self+4 with f_04b280 and, bracketed by f_1166d4(9) and f_116898(9), calls f_048410 with the arguments and self+44, returning its result. */
void *f_06cdf4(void *self, int a1, int a2, float x0, float x1, float x2, float x3, int a3, int a4, float x4, float x5)
{
    void *o = f_04b280((char *)self + 4);
    f_1166d4(9);
    void *r = f_048410(o, a1, a2, x0, x1, x2, x3, a3, a4, (char *)self + 44, x4, x5);
    f_116898(9);
    return r;
}

/* @implements 0x06cef0 us f_06cef0
   WHAT IT DOES: fetches the object at self+4 with f_04b280 and, bracketed by f_1166d4(9) and f_116898(9), calls f_048d1c with the arguments and self+44, returning its result. */
void *f_06cef0(void *self, int a1, int a2, float x0, float x1, float x2, float x3, int a3, int a4, int a5, int a6)
{
    void *o = f_04b280((char *)self + 4);
    f_1166d4(9);
    void *r = f_048d1c(o, a1, a2, x0, x1, x2, x3, a3, a4, a5, (char *)self + 44, a6);
    f_116898(9);
    return r;
}


/* @implements 0x075224 us f_075224
   WHAT IT DOES: constructs the composite menu object in place (base, sub-object, then the three member objects). */
void f_075224(void *self) { new (self) MN2; }

/* @implements 0x075304 us f_075304
   WHAT IT DOES: constructs the composite menu object in place (twin of f_075224). */
void f_075304(void *self) { new (self) MN2; }


/* @implements 0x075910 us f_075910
   WHAT IT DOES: if f_0780e0(p) returns 3, copies 24 bytes from self+1012 to p, stores self+4356 at self+1032 and returns 1, else returns 0. */
int f_075910(void *self, void *p)
{
    int r = 0;
    if (f_0780e0(p) == 3) {
        __builtin_memcpy(p, (char *)self + 1012, 24);
        at<int>(self, 1032) = at<int>(self, 4356);
        r = 1;
    }
    return r;
}


/* @draft 0x07354c us f_07354c
   WHAT IT DOES: reads a packed table header at p+4 and, for each entry, stores the pointer p+offset into the slot at self+2396+index*4 and calls f_0230e0 on it. */
void f_07354c(void *self, char *p)
{
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char **slot = &at<char *>(self, 2396 + *(int *)&t.b * 4);
        char *e = p + *(int *)&t.a;
        *slot = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
}

/* @implements 0x074150 us f_074150
   WHAT IT DOES: takes and clears a pending value: a switch on the kind (1..9) returns the field it names (words at +3640, +2392, +3644, +3648, +1208, a byte at +454 and a slot indexed by +532) and zeroes it, or 2 / the word at +7232 for kind 6. */
int f_074150(void *self, unsigned int k)
{
    int v;
    switch (k) {
    case 1:
        v = at<int>(self, 3640);
        if (v) at<int>(self, 3640) = 0;
        return v;
    case 2:
        v = at<int>(self, 2392);
        if (v == 8) return 8;
        if (v) at<int>(self, 2392) = 0;
        return v;
    case 3:
        v = at<int>(self, 3644);
        if (v) at<int>(self, 3644) = 0;
        return v;
    case 4:
        v = at<int>(self, 3648);
        if (v) at<int>(self, 3648) = 0;
        return v;
    case 6:
        if ((unsigned)(at<int>(self, 7228) - 300) < 8) return 2;
        return at<int>(self, 7232);
    case 7:
        v = at<int>(self, 1208);
        if (v) at<int>(self, 1208) = 0;
        return v;
    case 8:
        if (at<unsigned char>(self, 864)) {
            int i = at<int>(self, 532);
            at<unsigned char>(self, 864) = 0;
            return at<int>(self, 932 + i * 4);
        }
        return 0;
    case 9:
        v = at<unsigned char>(self, 454);
        at<unsigned char>(self, 454) = 0;
        return v;
    default:
        return 0;
    }
}

void f_04b25c(void *);
void f_04b23c(void *, void *);
/* @draft 0x06c954 us f_06c954
   WHAT IT DOES: initialises the sub-object at self+4, reads a packed table header at p+4 and for each entry stores the pointer p+offset into the slot at self+44+index*4 and calls f_0230e0 on it, then calls f_04b23c(self+4, self+44). */
void f_06c954(void *self, int a, char *p)
{
    f_04b25c((char *)self + 4);
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 44 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
    f_04b23c((char *)self + 4, (char *)self + 44);
}

/* @draft 0x07343c us f_07343c
   WHAT IT DOES: sets the 300 slots at self+2396 to -1, then reads a packed table header at p+4 and for each entry stores the pointer p+offset into the slot at self+2396+index*4 and calls f_0230e0 on it. */
void f_07343c(void *self, char *p)
{
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    int off = ((*(int *)&t.h & 1) == 0) * 8 + 8;
    for (int k = 0; k < 300; k++)
        at<int>(self, 2396 + k * 4) = -1;
    char *q = p + off;
    for (int i = 0; i < *(int *)&t.h; i++) {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 2396 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
    }
}

void *f_092ce4(void);
void f_092d40(void *, int);
void f_08a998(void);
void f_023250(int);
void f_02326c(int);
void f_01dee4(int);
void f_097ba8(void *);
void f_0974f8(void *);
void f_0e5740(void *);
extern char D_242e14[];
/* @implements 0x073fd8 us f_073fd8
   WHAT IT DOES: tears down the menu: calls f_092d40(f_092ce4(), 15) unless the state at +1224 is 3, closes f_08a998 if the byte at +36 is set, releases the 300 handles at self+2396 that are not -1, clears the flag at +520 (calling f_023250 first if set), shuts down the helpers and frees the object at self+524. */
void f_073fd8(void *self)
{
    if (at<int>(self, 1224) != 3)
        f_092d40(f_092ce4(), 15);
    if (at<bool>(self, 36))
        f_08a998();
    for (int i = 0; i < 300; i++) {
        int v = at<int>(self, 2396 + i * 4);
        if (v != -1)
            f_0231c8(v);
    }
    f_04b724((char *)self + 4);
    if (at<bool>(self, 520))
        f_023250(1911);
    at<bool>(self, 520) = 0;
    f_02326c(2);
    f_01dee4(at<int>(self, 512));
    f_097ba8(D_242e14);
    f_0974f8(D_242e14);
    void *o = at<void *>(self, 524);
    if (o) {
        f_0e5740(o);
        _ZdlPv(o);
    }
    at<void *>(self, 524) = 0;
}

void f_04a620(void *);
void f_04a648(void *, int, void *, int, int, int, int);
void f_04b8a0(void *, void *, int);
void f_06b7b4(void);
/* @draft 0x076328 us f_076328
   WHAT IT DOES: initialises the menu object: sets up the sub-object at self+4 (f_04a620), links self+456 and self, sets the ten slots at self+476 to -1, loads the packed table at p into those slots (calling f_0230e0 on each), then registers with f_04a648 and f_04b8a0 and clears the bytes at +36 and +472. */
void f_076328(void *self, int a, char *p)
{
    char *sub = (char *)self + 4;
    f_04a620(sub);
    at<void *>(self, 468) = self;
    at<void *>(sub, 28) = (char *)self + 456;
    for (int k = 0; k < 10; k++)
        at<int>(self, 476 + k * 4) = -1;
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 476 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
    f_04a648(sub, a, (char *)self + 476, 0, 0, 0, 0);
    f_04b8a0(sub, (void *)f_06b7b4, 0);
    at<char>(self, 472) = 0;
    at<char>(self, 36) = 0;
}

void f_076f98(void *);
/* @draft 0x0759f0 us f_0759f0
   WHAT IT DOES: initialises the menu object: sets up the sub-object at self+4 (f_04a620), links self+456 and self, sets the 101 slots at self+476 to -1, loads the packed table at p into those slots (calling f_0230e0 on each), registers with f_04a648 and f_04b8a0, runs f_076f98 on self+1272 and clears the bytes at +453 and +36. */
void f_0759f0(void *self, int a, char *p)
{
    char *sub = (char *)self + 4;
    f_04a620(sub);
    at<void *>(self, 468) = self;
    at<void *>(sub, 28) = (char *)self + 456;
    for (int k = 0; k < 101; k++)
        at<int>(self, 476 + k * 4) = -1;
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 476 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
    f_04a648(sub, a, (char *)self + 476, 0, 0, 0, 0);
    f_04b8a0(sub, (void *)f_06b7b4, 0);
    f_076f98((char *)self + 1272);
    at<char>(self, 453) = 0;
    at<char>(self, 36) = 0;
}

void f_077ecc(void *);
/* @draft 0x0760fc us f_0760fc
   WHAT IT DOES: initialises the menu object: sets up the sub-object at self+4 (f_04a620), links self+456 and self, sets the ten slots at self+968 to -1, loads the packed table at p into those slots (calling f_0230e0 on each), registers with f_04a648 and f_04b8a0, clears the words at +956 and +960 and the bytes at +964 and +36, and runs f_077ecc on self+472. */
void f_0760fc(void *self, int a, char *p)
{
    char *sub = (char *)self + 4;
    f_04a620(sub);
    at<void *>(self, 468) = self;
    at<void *>(sub, 28) = (char *)self + 456;
    for (int k = 0; k < 10; k++)
        at<int>(self, 968 + k * 4) = -1;
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 968 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
    f_04a648(sub, a, (char *)self + 968, 0, 0, 0, 0);
    f_04b8a0(sub, (void *)f_06b7b4, 0);
    at<int>(self, 956) = 0;
    f_077ecc((char *)self + 472);
    at<int>(self, 960) = 0;
    at<char>(self, 964) = 0;
    at<char>(self, 36) = 0;
}

extern char D_1a5ffc[];
extern char D_1a602c[];
/* @implements 0x073010 us f_073010
   WHAT IT DOES: maps a glyph code to a character: 1..26 give 'A'..'Z' (code+64), 27..52 give 'a'..'z' (code+70), 53..99 index a 48-byte table, 100..109 give '0'..'9', 255 gives a space and the rest index a 44-byte table. */
signed char f_073010(void *self, int c)
{
    char t1[48];
    char t2[44];
    if ((unsigned)(c - 1) < 26)
        return c + 64;
    if ((unsigned)(c - 27) < 26)
        return c + 70;
    if ((unsigned)(c - 53) < 47) {
        __builtin_memcpy(t1, D_1a5ffc, 48);
        return t1[c - 53];
    }
    if ((unsigned)(c - 100) < 10)
        return c - 52;
    if (c == 255)
        return 32;
    __builtin_memcpy(t2, D_1a602c, 44);
    return t2[c - 110];
}

/* @draft 0x076778 us f_076778
   WHAT IT DOES: initialises the menu object: sets up the sub-object at self+4 (f_04a620), links self+460 and self (at +472), sets the ten slots at self+480 to -1, loads the packed table at p into those slots (calling f_0230e0 on each), registers with f_04a648 and f_04b8a0, sets the byte at +522 to 1 and clears the flags at +523, +521, +520, +36, +453 and the word at +476. */
void f_076778(void *self, int a, char *p)
{
    char *sub = (char *)self + 4;
    f_04a620(sub);
    at<void *>(self, 472) = self;
    at<void *>(sub, 28) = (char *)self + 460;
    for (int k = 0; k < 10; k++)
        at<int>(self, 480 + k * 4) = -1;
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 480 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
    f_04a648(sub, a, (char *)self + 480, 0, 0, 0, 0);
    f_04b8a0(sub, (void *)f_06b7b4, 0);
    at<char>(self, 522) = 1;
    at<char>(self, 523) = 0;
    at<int>(self, 476) = 0;
    at<char>(self, 521) = 0;
    at<char>(self, 520) = 0;
    at<char>(self, 36) = 0;
    at<char>(self, 453) = 0;
}

int atoi(const char *);
int f_046c8c(void *, int, int);
void f_049188(void *, int, int, float, float, float, float, int, int, int, int, void *, void *);
extern unsigned int D_24518c;
extern float D_1d3140;
/* @implements 0x075c74 us f_075c74
   WHAT IT DOES: parses the number after the first four characters of the string; if it is above 99999999, flags the parent, measures it with f_046c8c and, when the result reaches 480, nudges the value at parent+444 by D_1d3140 according to the buttons in D_24518c (or bumps the counter at +448 up to 120) and calls f_049188 with the converted coordinates, returning 1; otherwise returns 0. */
int f_075c74(void *self, char *s, float x0, float x1, float x2, float x3, float x4, float x5)
{
    void *o = f_04b280((char *)at<void *>(self, 12) + 4);
    int n = atoi(s + 4);
    if (n > 99999999) {
        at<char>(at<void *>(self, 12), 452) = 1;
        if (f_046c8c(o, n, 480) < 480)
            return 0;
        char *p = at<char *>(self, 12);
        int c = at<int>(p, 448);
        if (c > 120) {
            if (D_24518c & 0x100)
                at<float>(p, 444) += D_1d3140;
            else if (D_24518c & 0x200)
                at<float>(p, 444) -= D_1d3140 + D_1d3140;
            else
                at<float>(p, 444) -= D_1d3140;
        } else
            at<int>(p, 448) = c + 1;
        f_049188(o, (int)x0, (int)x1, x2, x3, x4, x5, n, 0, 480, 150, p + 44, p + 444);
        return 1;
    }
    return 0;
}

extern char D_1a64c8[];
extern char D_1a6530[];
void f_02326c(int);
void f_01dee4(int);
void f_0ca98c(int);
void f_079a9c(void *);
void f_0798d0(void *);
void f_07a7c0(void *);
void f_078dec(void *);
void f_078734(void *);
void f_07a5d4(void *);
void f_07a390(void *);
void f_0782f8(void *);
void f_078448(void *);
struct PS { char b[80]; ~PS() { *(void **)this = D_1a6530; f_04a580(this); } };
struct PA { char b[1172 - 536]; ~PA() { f_078448(this); } };
struct PB { char b[1216 - 1172]; ~PB() { f_0782f8(this); } };
struct PC { char b[1508 - 1216]; ~PC() { f_07a390(this); } };
struct PD { char b[1832 - 1508]; ~PD() { f_07a5d4(this); } };
struct PE { char b[2156 - 1832]; ~PE() { f_07a5d4(this); } };
struct PF { char b[2168 - 2156]; ~PF() { f_078734(this); } };
struct PG { char b[2340 - 2168]; ~PG() { f_078dec(this); } };
struct PH { char b[7296 - 2340]; ~PH() { f_07a7c0(this); } };
struct PI { char b[7468 - 7296]; ~PI() { f_0798d0(this); } };
struct PJ { char b[8]; ~PJ() { f_079a9c(this); } };
struct PBase : MBase {
    PS s;
    PA a;
    PB b;
    PC c;
    PD d;
    PE e;
    PF f;
    PG g;
    PH h;
    PI i;
    PJ j;
    __attribute__((always_inline)) ~PBase() {
        *(void **)this = D_1a64c8;
        f_02326c(2);
        f_01dee4(at<int>(this, 512));
        f_0ca98c(at<int>(this, 508));
        _ZdlPv(at<void *>(this, 516));
        void *n1 = at<void *>(this, 512);
        at<int>(this, 516) = 0;
        _ZdlPv(n1);
        void *n2 = at<void *>(this, 508);
        at<int>(this, 512) = 0;
        _ZdlPv(n2);
        at<int>(this, 508) = 0;
    }
};
/* @implements 0x071b68 us f_071b68
   WHAT IT DOES: destroys the menu object: stores its vtable, shuts down the helpers, frees and clears the three buffers at +516, +512 and +508, destroys the eleven member objects (+7468 down to +536), the sub-object at +456 and the base. */
void f_071b68(PBase *self) { self->~PBase(); }

/* @implements 0x071d18 us f_071d18
   WHAT IT DOES: destroys the menu object (twin of f_071b68). */
void f_071d18(PBase *self) { self->~PBase(); }

/* @implements 0x071ec8 us f_071ec8
   WHAT IT DOES: destroys the menu object (as f_071b68) and then frees its memory with operator delete. */
void f_071ec8(PBase *self) { self->~PBase(); _ZdlPv(self); }

/* @draft 0x07659c us f_07659c
   WHAT IT DOES: like f_075c74 but only runs when the parent's flag at +520 or +521 is set: parses the number after the first four characters of the string and, if it is above 99999999, measures it with f_046c8c (code 0x6332882 or 0x6332883 by the +520 flag); on a short result draws with f_0477b0, else steps the value at parent+444 down by D_1d3140 (or the counter at +448) and draws with f_049188; returns 1 (0 for a small number). */
int f_07659c(void *self, char *s, float x0, float x1, float x2, float x3, float x4, float x5)
{
    void *o = f_04b280((char *)at<void *>(self, 12) + 4);
    int n = atoi(s + 4);
    if (n > 99999999) {
        char *p = at<char *>(self, 12);
        if (!at<bool>(p, 520) && !at<bool>(p, 521))
            return 1;
        n = at<bool>(p, 520) ? 0x6332882 : 0x6332883;
        at<char>(p, 452) = 1;
        if (f_046c8c(o, n, 480) < 480) {
            int ia = (int)x0 - 3;
            int ib = (int)x1;
            f_0477b0(o, ia, ib, x2, x3, x4, x5, n, 480, at<char *>(self, 12) + 44);
        } else {
            p = at<char *>(self, 12);
            int k = at<int>(p, 448);
            if (k > 120)
                at<float>(p, 444) -= D_1d3140;
            else
                at<int>(p, 448) = k + 1;
            int ia = (int)x0;
            int ib = (int)x1;
            f_049188(o, ia, ib, x2, x3, x4, x5, n, 0, 480, 150, p + 44, p + 444);
        }
        return 1;
    }
    return 0;
}


extern bool D_2413b8;
extern char *D_2413ac;
extern int D_1d46f0;
extern int D_242b78;
extern int D_242b50;
extern char D_242e14[];
int f_08a9c0(void);
void f_088bd4(void);
void f_088bdc(void *);
void f_088bc8(void);
void f_08a998(void);
void f_097680(void *, int, int);

/* @draft 0x0736f0 us f_0736f0
   WHAT IT DOES: per-frame check of the menu movie player: when the pending state is 8 it pokes the global helper object, then decides from the input flags and the poll result whether playback ended; if so it logs, tears down the helper object and resets the flag. */
void f_0736f0(char *self)
{
    if (at<int>(self, 7528) == 8) {
        if (D_2413ac) {
            f_088bd4();
            f_088bdc(D_2413ac);
        }
    }
    unsigned flags = D_245194;
    int d = f_08a9c0();
    if (at<int>(self, 7528) == 8 && D_2413ac)
        d = (at<unsigned char>(D_2413ac, 4) ? -1 : 0) | 1;
    if ((flags & 0xf008) || D_2413b8)
        d = -1;
    if (!(d == -1 && D_1d46f0 == 1 && D_242b78 >= 30)) {
        if (!D_2413b8)
            return;
    }
    f_097680(D_242e14, at<int>(self, 7236), at<unsigned char>(self, 7532));
    at<char>(self, 36) = 0;
    if (D_2413ac) {
        f_088bc8();
        _ZdlPv(D_2413ac);
        D_2413ac = 0;
    }
    f_08a998();
    D_242b50 = 0;
}


/* @draft 0x074240 us f_074240
   WHAT IT DOES: answers a menu state query by code (10..77) from the parent object at self+12: returns and clears a flag, indexed byte tables, a 1..12 cycling index, fields at +1024, +996, +1044 and +1030 and several equality/non-zero tests; 0 for unknown codes. */
int f_074240(void *self, int a)
{
    int r, t, k, off;
    char *o;
    switch (a) {
    case 10: {
        void *o = at<void *>(self, 12);
        if (at<bool>(o, 453)) {
            r = 1;
            at<bool>(o, 453) = 0;
        } else
            r = 0;
        break;
    }
    case 11: {
        void *o = at<void *>(self, 12);
        int v = at<int>(o, 904);
        if (v == 255)
            r = 0;
        else
            r = at<unsigned char>(o, v + 1993);
        break;
    }
    case 12: {
        void *o = at<void *>(self, 12);
        int v = at<int>(o, 900) - 1;
        t = v % 12;
        goto add1;
    }
    case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: {
        k = a - 21;
        off = k * 28;
        t = at<int>(at<char *>(self, 12) + off, 1060);
    add1:
        r = t + 1;
        break;
    }
    case 45:
        r = at<int>(at<void *>(self, 12), 1024);
        break;
    case 46:
        r = at<int>(at<void *>(self, 12), 904) == 255;
        break;
    case 54:
        r = at<int>(at<void *>(self, 12), 912) != 0;
        break;
    case 55: {
        void *o = at<void *>(self, 12);
        int v = at<int>(o, 904);
        r = at<int>(o, 908) == at<unsigned char>(o, v + 1272);
        break;
    }
    case 56:
        r = at<int>(at<void *>(self, 12), 996);
        break;
    case 57:
        r = at<int>(at<void *>(self, 12), 1044);
        break;
    case 53:
    case 61:
        r = at<unsigned char>(at<void *>(self, 12), 1030);
        break;
    case 77:
        r = at<unsigned char>(at<void *>(self, 12), 1020) ^ 1;
        break;
    default:
        r = 0;
        break;
    }
    return r;
}

}
}
