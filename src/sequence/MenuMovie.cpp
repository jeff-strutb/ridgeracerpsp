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
        char *e = p + *(int *)&t.a;
        char **slot = &at<char *>(self, 2396 + *(int *)&t.b * 4);
        *slot = e;
        f_0230e0(e);
        i++;
    } while (*(int *)&t.h > i);
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


/* @draft 0x06dac0 us f_06dac0
   WHAT IT DOES: answers a menu-slot query by code (34..83) with argument b from the parent object at self+12: scans the slot flags (+2236, +1400, +5661) for a duplicate of b, compares indexed byte tables (+3704/+2336, +3752/+5662), tests slot flag pairs (+2296/+1460, +2236/+1400), returns table bytes (+2176, +5721 plus 1, +3656, +2322, +2324, +1505 for b == 100); 0 for unknown codes. */
int f_06dac0(void *self, int a, int b)
{
    switch (a) {
    case 34: {
        a = 0;
        if ((unsigned)(b - 1) < 7) {
            char *o = at<char *>(self, 12);
            int i = 1;
            int n = at<unsigned char>(o, 6624);
            if (i < n) {
                char *p = o;
                do {
                    if (at<unsigned char>(p + i, 2236) != 0 && at<unsigned char>(p + i, 1400) != 0 && at<unsigned char>(p + i, 5661) == b)
                        goto out34;
                    i++;
                } while (i < n);
            }
            a = 1;
        }
    out34:
        break;
    }
    case 35: {
        a = 0;
        if (b >= 0) {
            char *o = at<char *>(self, 12);
            char *p = o + b;
            if (at<int>(o, 2336) < at<unsigned char>(p, 3704))
                a = 11;
            else
                a = at<unsigned char>(p, 2176);
        }
        break;
    }
    case 36: {
        a = 0;
        char *o = at<char *>(self, 12);
        int n = at<unsigned char>(o, 6624);
        int i = 1;
        if (i < n) {
            int c = at<unsigned char>(b + o, 3752);
            char *p = o + 5662;
            do {
                if (!(*(unsigned char *)p < c))
                    return 1;
                i++;
                p++;
            } while (i < n);
        }
        break;
    }
    case 40: {
        a = 0;
        if (b >= 0) {
            char *p = at<char *>(self, 12) + b;
            if (at<unsigned char>(p, 2296) == 0)
                a = 1;
            else if (at<unsigned char>(p, 1460) != 0)
                a = 0;
            else
                a = 1;
        }
        break;
    }
    case 44: {
        a = 0;
        if (b >= 0) {
            char *p = at<char *>(self, 12) + b;
            if (at<unsigned char>(p, 2236) == 0)
                a = 1;
            else if (at<unsigned char>(p, 1400) != 0)
                a = 0;
            else
                a = 1;
        }
        break;
    }
    case 64:
        a = 0;
        if (b >= 0)
            a = at<unsigned char>(at<char *>(self, 12) + b, 5721) + 1;
        break;
    case 51:
    case 65:
        a = 0;
        if (b >= 0)
            a = at<unsigned char>(at<char *>(self, 12) + b, 3656);
        break;
    case 38:
    case 83:
        if ((unsigned)b < 7)
            a = at<unsigned char>(at<char *>(self, 12) + b, 2322);
        else if ((unsigned)(b - 7) < 3)
            a = at<unsigned char>(at<char *>(self, 12) + b, 2324);
        else if (b == 100)
            a = at<unsigned char>(at<char *>(self, 12), 1505);
        else
            a = 0;
        break;
    default:
        a = 0;
        break;
    }
    return a;
}


/* @draft 0x072e1c us f_072e1c
   WHAT IT DOES: fills the buffer out according to the kind f_0780e0(out) reports: kind 5 copies the 292 bytes at self+1216, kind 10 the 324 bytes at self+1508, kind 18 two words (+7244, +2352), kind 21 three words (+2360..+2368), kind 24 one word (+2376), kind 27 the count at +928 followed by that many words from +932; returns 1 when handled, else 0.
   Remaining difference: the kind-18 arm loads and stores its two words in a different order (4 words). */
int f_072e1c(void *self, void *out)
{
    switch (f_0780e0(out)) {
    case 5:
        __builtin_memcpy((char *)out, (char *)self + 1216, 292);
        break;
    case 10:
        __builtin_memcpy((char *)out, (char *)self + 1508, 324);
        break;
    case 18:
        at<int>(out, 8) = at<int>(self, 7244);
        at<int>(out, 12) = at<int>(self, 2352);
        break;
    case 21:
        at<int>(out, 8) = at<int>(self, 2360);
        at<int>(out, 12) = at<int>(self, 2364);
        at<int>(out, 16) = at<int>(self, 2368);
        break;
    case 24:
        at<int>(out, 8) = at<int>(self, 2376);
        break;
    case 27: {
        at<int>(out, 28) = at<int>(self, 928);
        for (int i = 0; i < at<int>(self, 928); i++) {
            int o = i * 4;
            int v = at<int>((char *)(o + (unsigned)self), 932);
            at<int>((char *)(o + (unsigned)out), 8) = v;
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}


void *memset(void *, int, unsigned int);
int sceUtilityOskInitStart(void *);
int f_01c260(void);
extern unsigned short D_1d3320[];
extern int D_1d3310[];
extern int D_241434[];
extern int D_2413c0[];
extern int D_241400[];
/* @draft 0x073840 us f_073840
   WHAT IT DOES: opens the on-screen keyboard: clears and fills the 64-character title buffer D_1d3320 from the zero-terminated string in, clears the result block D_241434 and the 7-character initial text D_1d3310 and fills the latter from the signed bytes of init, then builds the OSK parameter block D_2413c0 (size 64, language from f_01c260 mapped to 0/2/3/4/1, one data block D_241400 pointing at the buffers) and calls sceUtilityOskInitStart; returns 0.
   Remaining difference: data-address high parts are held in different callee-saved registers (retail s5/s3/s4) and the language-selection tail is 20 bytes shorter. */
int f_073840(void *unused, const unsigned short *in, const signed char *init)
{
    unsigned short *d = D_1d3320;
    int i, x;
    memset(D_1d3320, 0, 128);
    while (*in)
        *d++ = *in++;
    D_241434[3] = 0;
    D_241434[0] = 0;
    D_241434[1] = 0;
    D_241434[2] = 0;
    D_1d3310[0] = 0;
    D_1d3310[1] = 0;
    D_1d3310[2] = 0;
    D_1d3310[3] = 0;
    for (i = 0; i < 7; i++)
        ((short *)D_1d3310)[i] = init[i];
    memset(D_2413c0, 0, 64);
    D_2413c0[0] = 64;
    if (f_01c260() == 0)
        x = 0;
    else if ((x = f_01c260()) == 2)
        ;
    else if ((x = f_01c260()) == 3)
        ;
    else if ((x = f_01c260()) == 4)
        ;
    else
        x = 1;
    D_2413c0[1] = x;
    D_241400[12] = 7;
    D_2413c0[4] = 19;
    D_2413c0[6] = 16;
    D_2413c0[3] = 17;
    D_2413c0[5] = 18;
    D_241400[4] = 13;
    D_241400[9] = 8;
    D_241400[6] = 1;
    D_241400[7] = (int)D_1d3320;
    D_241400[8] = (int)D_1d3310;
    D_241400[10] = (int)D_241434;
    D_2413c0[2] = 1;
    D_2413c0[8] = 0;
    D_2413c0[9] = 0;
    D_2413c0[12] = 1;
    D_2413c0[13] = (int)D_241400;
    D_241400[1] = 0;
    D_241400[3] = 0;
    D_241400[2] = 0;
    D_241400[5] = 1;
    D_241400[11] = 0;
    D_241400[0] = 1;
    sceUtilityOskInitStart(D_2413c0);
    return 0;
}


int sceUtilityOskGetStatus(void);
int sceUtilityOskUpdate(int);
int sceUtilityOskShutdownStart(void);
int sceCtrlSetSamplingMode(int);
void f_021b9c(void);
int f_097524(void *);
void f_097878(void *, int, int);
extern int D_24142c;
extern char D_242e14[];
extern int D_2413a8;
/* @draft 0x073c88 us f_073c88
   WHAT IT DOES: per-frame update of the on-screen keyboard screen: while the keyboard is open (flag at +7512) it follows sceUtilityOskGetStatus (running: update; finished: close it, pick the result mode from D_24142c and copy up to seven result characters into the name field at +1539, or +1863 when +3652 is 1, padding with zero up to eight; shutting down: start the shutdown); otherwise it polls the pad type, tracks the button state at +7236 and +7532/+7533 and tells the pad object when it changes. Returns 1 while the keyboard is up, 0 otherwise.
   Remaining difference: 3 words longer (prologue and case-exit layout). */
int f_073c88(void *self)
{
    char *s = (char *)self;
    int p, n, v;
    if (at<unsigned char>(s, 7512)) {
        switch (sceUtilityOskGetStatus()) {
        case 2:
            f_021b9c();
            sceUtilityOskUpdate(1);
            return 1;
        case 0:
            at<unsigned char>(s, 7512) = 0;
            sceCtrlSetSamplingMode(1);
            v = D_24142c;
            if (v == 1)
                goto mode2;
            if (v < 2) {
                if (v != 0)
                    return 1;
            mode2:
                at<int>(s, 7508) = 2;
                return 1;
            }
            if (v != 2)
                return 1;
            at<int>(s, 7508) = 1;
            n = 0;
            {
                unsigned short *src = (unsigned short *)D_241434;
                char *d = s + 1539;
                do {
                    if (*src == 0)
                        break;
                    if (at<int>(s, 3652) == 1)
                        at<char>(d, 324) = *(unsigned char *)src;
                    else
                        *d = *(unsigned char *)src;
                    n++;
                    src++;
                    d++;
                } while (n < 7);
            }
            if (n == 0)
                return 1;
            if (n < 8) {
                char *d = s + n + 1539;
                do {
                    if (at<int>(s, 3652) == 1)
                        at<char>(d, 324) = 0;
                    else
                        *d = 0;
                    n++;
                    d++;
                } while (n < 8);
            }
            return 1;
        case 3:
            sceUtilityOskShutdownStart();
            return 1;
        case 1:
        case 4:
            return 1;
        }
        return 1;
    }
    {
        int (*fn)(void *, int) = (int (*)(void *, int))at<void **>(*(void **)self, 40);
        fn(self, 6);
    }
    p = f_097524(D_242e14);
    if (p == 2)
        at<unsigned char>(s, 7532) = 1;
    v = at<int>(s, 7236);
    if (v != p) {
        if (v != -1)
            f_097878(D_242e14, p, at<unsigned char>(s, 7532));
        at<int>(s, 7236) = p;
        if (p == 6)
            D_2413a8 = 1;
        else
            D_2413a8 = 0;
    }
    if (at<unsigned char>(s, 7532) == at<unsigned char>(s, 7533))
        return 0;
    f_097878(D_242e14, at<int>(s, 7236), at<unsigned char>(s, 7532));
    at<unsigned char>(s, 7533) = at<unsigned char>(s, 7532);
    return 0;
}


void f_0e7858_v(void) __asm__("f_0e7858");
void f_0e798c(void);
void f_04b4d8(void *, const char *, int);
void f_04b5c8(void *, const char *, const char *, int);
void f_04b664(void *, const char *, int);
void f_097680(void *, int, int);
extern char D_242e14[];
extern char D_1a57fc[]; /* "rrm_307" */
extern char D_1a5804[]; /* "r999_UNDERBAR" */
extern char D_1a5814[]; /* "OPTION_ICON_GAME" */
extern char D_1a5828[]; /* "OPTION_ICON_AV" */
extern char D_1a5838[]; /* "Cours006" */
extern char D_1a5844[]; /* "Cours005" */
extern char D_1a5850[]; /* "Cours004" */
extern char D_1a585c[]; /* "Cours003" */
extern char D_1a5868[]; /* "Cours002" */
extern char D_1a5874[]; /* "Cours001" */
extern char D_1a5880[]; /* "MiniLogoPro" */
extern char D_1a588c[]; /* "Navi1" */
extern char D_1a5894[]; /* "Navi2" */
extern char D_1a589c[]; /* "Navi3" */
extern char D_1a58a4[]; /* "Navi4" */
extern char D_1a58ac[]; /* "Navi5" */
extern char D_1a58b4[]; /* "Navi6" */
extern char D_1a58bc[]; /* "MINI_LOGO1" */
extern char D_1a58c8[]; /* "Navi7" */
extern char D_1a58d0[]; /* "Navi0" */
extern char D_1a6058[]; /* "MiniGameEnd" */
/* @draft 0x073a44 us f_073a44
   WHAT IT DOES: when the screen's load flag (+7524) is set and the pad word D_245194 has bit 0 but not bit 3, clears the flag and registers twenty named movie parts (option icons, rrm_307, the course and navigation frames, the mini logo) on the sub-object at self+4 with f_04b4d8, then names the mini-game end clip and starts it, and refreshes the pad object D_242e14 with the stored state (+7236, +7532).
   Remaining difference: the pad word is loaded into v0 instead of v1 (5 words). */
void f_073a44(void *self)
{
    char *s = (char *)self;
    if (at<unsigned char>(s, 7524) == 0)
        return;
    f_0e7858_v();
    unsigned int pad = D_245194;
    if ((pad & 1) == 0)
        return;
    if ((pad & 8) != 0)
        return;
    f_0e798c();
    {
        void *s0 = s + 4;
        at<unsigned char>(s, 7524) = 0;
        f_04b4d8(s0, D_1a5814, 1);
        f_04b4d8(s0, D_1a5828, 1);
        f_04b4d8(s0, D_1a57fc, 1);
        f_04b4d8(s0, D_1a5804, 1);
        f_04b4d8(s0, D_1a5838, 1);
        f_04b4d8(s0, D_1a5844, 1);
        f_04b4d8(s0, D_1a5850, 1);
        f_04b4d8(s0, D_1a585c, 1);
        f_04b4d8(s0, D_1a5868, 1);
        f_04b4d8(s0, D_1a5874, 1);
        f_04b4d8(s0, D_1a5880, 1);
        f_04b4d8(s0, D_1a588c, 1);
        f_04b4d8(s0, D_1a5894, 1);
        f_04b4d8(s0, D_1a589c, 1);
        f_04b4d8(s0, D_1a58a4, 1);
        f_04b4d8(s0, D_1a58ac, 1);
        f_04b4d8(s0, D_1a58b4, 1);
        f_04b4d8(s0, D_1a58bc, 1);
        f_04b4d8(s0, D_1a58c8, 1);
        f_04b4d8(s0, D_1a58d0, 1);
        f_04b5c8(s0, D_1a57fc, D_1a6058, 0);
        f_04b664(s0, D_1a57fc, 0);
        f_097680(D_242e14, at<int>(s, 7236), at<unsigned char>(s, 7532));
    }
}


extern int D_24139c;
extern unsigned char D_2413a0;
extern int D_2413a4;
int f_0722bc(char *, unsigned, int, int, int *, unsigned char *, int *, unsigned, unsigned, int *, int *);
/* @implements 0x072080 us f_072080
   WHAT IT DOES: asks f_0722bc to fill a 96,000-byte table, a 24-entry list and a count; on the first use it copies 24 bytes from the list's words, seeds the generator D_24139c from D_2413a4 once, then picks a row of the table by random number modulo the count, bumps each of its 24 bytes until one wraps to zero, collects those values into X, and writes them to out in a random (Fisher-Yates style) order; returns how many were collected. */
int f_072080(char *a0, unsigned a1, int a2, int *out)
{
    unsigned char A[96000];
    int X[24];
    int Y[24];
    int z;
    int flag;
    unsigned j, k;
    z = 0;
    flag = 0;
    f_0722bc(a0, a1, a2, 0, X, A, &flag, 0, 0, Y, &z);
    if (flag == 0) {
        for (j = 0; j < 24; j++)
            A[j] = (unsigned char)Y[j];
        flag = 1;
    }
    if (D_2413a0 == 0) {
        D_2413a0 = 1;
        D_24139c = D_2413a4;
    }
    D_24139c = D_24139c * 1664525 + 1013904223;
    unsigned char *row = (unsigned char *)((unsigned)D_24139c % (unsigned)flag * 24 + (unsigned)A);
    for (j = 0; j < 24; j++) {
        int v = row[j] + 1;
        row[j] = v;
        unsigned char c = v;
        if (c == 0)
            break;
        X[j] = c;
    }
    for (k = 0; k < j; k++) {
        D_24139c = D_24139c * 1664525 + 1013904223;
        unsigned r = (unsigned)D_24139c % (unsigned)(j - k);
        int t = X[r];
        X[r] = X[j - 1 - k];
        out[k] = t;
    }
    return j;
}

void f_06b6fc(int);
void f_07a19c(void *);
/* @draft 0x0756b4 us f_0756b4
   WHAT IT DOES: loads saved state from the buffer p according to the kind f_0780e0(p) reports: kind 3 copies 24 bytes to self+1012, mirrors the word at +1024 into +880 (calling f_0929b4 with 10 when it is 3 and the byte at +1030 is set) and calls f_06b6fc with the byte at +1028; kind 8 copies 128 bytes to self+884 and the word at +900 into +4356; kind 15 copies 236 bytes to self+1036 and calls f_07a19c on it; returns 1 when handled, else 0.
   Remaining difference: the result is carried in v1 and moved to v0 at the shared return, 8 bytes longer than retail. */
int f_0756b4(void *self, void *p)
{
    char *s = (char *)self;
    switch ((unsigned)f_0780e0(p)) {
    case 3: {
        __builtin_memcpy(s + 1012, p, 24);
        int v = at<int>(s, 1024);
        at<int>(s, 880) = v;
        if (v == 3 && at<unsigned char>(s, 1030))
            f_0929b4(f_092970(), 10);
        f_06b6fc(at<char>(s, 1028));
        return 1;
    }
    case 8:
        __builtin_memcpy(s + 884, p, 128);
        at<int>(s, 4356) = at<int>(s, 900);
        return 1;
    case 15:
        __builtin_memcpy(s + 1036, p, 236);
        f_07a19c(s + 1036);
        return 1;
    }
    return 0;
}

/* @draft 0x0722bc us f_0722bc
   WHAT IT DOES: a recursive search for ordered picks of up to 24 entries: for each candidate depth it adds the entry at obj+(idx*26+depth)*4+4832 to a running total (base), skips totals above the limit, records the best total below it with its choice list in Y, and when the total is more than 60000 below the limit appends the choice list as a 24-byte row of table A (padded with 0xff, counter *cnt up to 3800); otherwise recurses one level deeper; returns 1 as soon as the row count is exhausted or a deeper call succeeds. */
int f_0722bc(char *obj, unsigned limit, int idx, int base, int *X, unsigned char *A, int *cnt, unsigned depth, unsigned n, int *Y, int *best)
{
    int r = 0;
    if (n < 24 && depth < 24) {
        int c = idx * 26;
        int *pX = X + n;
        unsigned lim28 = limit - 60000;
        do {
            if ((unsigned)*cnt >= 3800) {
                r = 1;
                break;
            }
            unsigned a3 = base + at<int>(obj, (c + depth) * 4 + 4832) + 20000;
            if (limit < a3)
                continue;
            if (a3 < limit) {
                if ((unsigned)*best < a3) {
                    unsigned i;
                    *best = a3;
                    for (i = 0; i <= n; i++)
                        Y[i] = X[i];
                    for (i = n + 1; i < 24; i++)
                        Y[i] = -1;
                }
            }
            *pX = depth;
            if (lim28 < a3) {
                unsigned i;
                for (i = 0; i <= n; i++)
                    A[*cnt * 24 + i] = (unsigned char)X[i];
                for (i = n + 1; i < 24; i++)
                    A[*cnt * 24 + i] = 0xff;
                *cnt = *cnt + 1;
            } else if (f_0722bc(obj, limit, idx, a3, X, A, cnt, depth + 1, n + 1, Y, best)) {
                r = 1;
                break;
            }
        } while (++depth < 24);
    }
    return r;
}
}
}

/* ---- menuH ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* menuH fragment: TU 119 large menu movie functions. */
namespace menuH {
template <class T> inline T &at(void *p, unsigned int off) { return *(T *)((char *)p + off); }
extern "C" {
int atoi(const char *);
void *f_092970(void);
void f_0929b4(void *, int);
void *f_092ce4(void);
void f_092d40(void *, int);

/* @implements 0x06b7b4 us f_06b7b4
   WHAT IT DOES: parses the number after the 5-char prefix of the name with atoi and
   maps it through a big switch to a table index; selects the type-A or type-B
   record getter (f_092970 / f_092ce4) and passes the index to its setter
   (f_0929b4 / f_092d40); unknown numbers use type A index 1. */
void f_06b7b4(const char *name)
{
    switch (atoi(name + 5)) {
    case 100001001:
        { void *r = f_092ce4(); f_092d40(r, 3); } return;
    case 100001002:
        { void *r = f_092ce4(); f_092d40(r, 4); } return;
    case 100001003:
        { void *r = f_092ce4(); f_092d40(r, 5); } return;
    case 100001004:
        { void *r = f_092ce4(); f_092d40(r, 6); } return;
    case 100001005:
        { void *r = f_092ce4(); f_092d40(r, 7); } return;
    case 100001006:
        { void *r = f_092ce4(); f_092d40(r, 8); } return;
    case 100001007:
        { void *r = f_092ce4(); f_092d40(r, 11); } return;
    case 100001008:
        { void *r = f_092970(); f_0929b4(r, 6); } return;
    case 100001009:
        { void *r = f_092970(); f_0929b4(r, 9); } return;
    case 100001011:
        { void *r = f_092970(); f_0929b4(r, 2); } return;
    case 100001014:
        { void *r = f_092970(); f_0929b4(r, 23); } return;
    case 110001001:
        { void *r = f_092970(); f_0929b4(r, 24); } return;
    case 110001002:
        { void *r = f_092970(); f_0929b4(r, 25); } return;
    case 130001001:
        { void *r = f_092ce4(); f_092d40(r, 33); } return;
    case 130001002:
        { void *r = f_092ce4(); f_092d40(r, 34); } return;
    case 130001003:
        { void *r = f_092ce4(); f_092d40(r, 28); } return;
    case 130001004:
        { void *r = f_092ce4(); f_092d40(r, 27); } return;
    case 130001005:
        { void *r = f_092ce4(); f_092d40(r, 29); } return;
    case 130001006:
        { void *r = f_092ce4(); f_092d40(r, 30); } return;
    case 130001007:
        { void *r = f_092ce4(); f_092d40(r, 31); } return;
    case 130001008:
        { void *r = f_092ce4(); f_092d40(r, 32); } return;
    case 130001009:
        { void *r = f_092ce4(); f_092d40(r, 35); } return;
    case 130001010:
        { void *r = f_092ce4(); f_092d40(r, 36); } return;
    case 130001011:
        { void *r = f_092ce4(); f_092d40(r, 25); } return;
    case 130001012:
        { void *r = f_092ce4(); f_092d40(r, 26); } return;
    case 130001013:
        { void *r = f_092ce4(); f_092d40(r, 45); } return;
    case 130001014:
        { void *r = f_092ce4(); f_092d40(r, 46); } return;
    case 130001015:
        { void *r = f_092ce4(); f_092d40(r, 40); } return;
    case 130001016:
        { void *r = f_092ce4(); f_092d40(r, 39); } return;
    case 130001017:
        { void *r = f_092ce4(); f_092d40(r, 41); } return;
    case 130001018:
        { void *r = f_092ce4(); f_092d40(r, 42); } return;
    case 130001019:
        { void *r = f_092ce4(); f_092d40(r, 43); } return;
    case 130001020:
        { void *r = f_092ce4(); f_092d40(r, 44); } return;
    case 130001021:
        { void *r = f_092ce4(); f_092d40(r, 47); } return;
    case 130001022:
        { void *r = f_092ce4(); f_092d40(r, 48); } return;
    case 130001023:
        { void *r = f_092ce4(); f_092d40(r, 37); } return;
    case 130001024:
        { void *r = f_092ce4(); f_092d40(r, 38); } return;
    case 140001001:
        { void *r = f_092ce4(); f_092d40(r, 49); } return;
    case 140001002:
        { void *r = f_092ce4(); f_092d40(r, 50); } return;
    case 140001003:
        { void *r = f_092ce4(); f_092d40(r, 51); } return;
    case 140001004:
        { void *r = f_092ce4(); f_092d40(r, 52); } return;
    case 140001005:
        { void *r = f_092ce4(); f_092d40(r, 53); } return;
    case 140001006:
        { void *r = f_092ce4(); f_092d40(r, 54); } return;
    case 140001007:
        { void *r = f_092ce4(); f_092d40(r, 55); } return;
    case 140001008:
        { void *r = f_092ce4(); f_092d40(r, 56); } return;
    case 140001009:
        { void *r = f_092ce4(); f_092d40(r, 57); } return;
    case 140001010:
        { void *r = f_092ce4(); f_092d40(r, 58); } return;
    case 140001011:
        { void *r = f_092ce4(); f_092d40(r, 59); } return;
    case 140001012:
        { void *r = f_092ce4(); f_092d40(r, 60); } return;
    case 140001013:
        { void *r = f_092ce4(); f_092d40(r, 61); } return;
    case 140001014:
        { void *r = f_092ce4(); f_092d40(r, 62); } return;
    case 140001015:
        { void *r = f_092ce4(); f_092d40(r, 63); } return;
    case 140001016:
        { void *r = f_092ce4(); f_092d40(r, 64); } return;
    case 140001017:
        { void *r = f_092ce4(); f_092d40(r, 65); } return;
    case 140001018:
        { void *r = f_092ce4(); f_092d40(r, 66); } return;
    case 140001019:
        { void *r = f_092ce4(); f_092d40(r, 67); } return;
    case 140001020:
        { void *r = f_092ce4(); f_092d40(r, 68); } return;
    case 140001021:
        { void *r = f_092ce4(); f_092d40(r, 69); } return;
    case 140001022:
        { void *r = f_092ce4(); f_092d40(r, 70); } return;
    case 200001001:
        { void *r = f_092ce4(); f_092d40(r, 1); } return;
    case 200001002:
        { void *r = f_092ce4(); f_092d40(r, 1); } return;
    case 200001006:
        { void *r = f_092ce4(); f_092d40(r, 0); } return;
    case 200001009:
        { void *r = f_092ce4(); f_092d40(r, 0); } return;
    case 200001010: case 200001011: case 200001012:
        { void *r = f_092970(); f_0929b4(r, 0); } return;
    case 200001013:
        { void *r = f_092970(); f_0929b4(r, 22); } return;
    case 200001014:
        { void *r = f_092970(); f_0929b4(r, 23); } return;
    case 200003001:
        { void *r = f_092970(); f_0929b4(r, 4); } return;
    case 200006001:
        { void *r = f_092970(); f_0929b4(r, 10); } return;
    case 200006002:
        { void *r = f_092ce4(); f_092d40(r, 72); } return;
    case 200006003:
        { void *r = f_092970(); f_0929b4(r, 12); } return;
    case 200007001:
        { void *r = f_092ce4(); f_092d40(r, 9); } return;
    case 200007002:
        { void *r = f_092970(); f_0929b4(r, 13); } return;
    case 200100001:
        { void *r = f_092970(); f_0929b4(r, 34); } return;
    case 300001001:
        { void *r = f_092ce4(); f_092d40(r, 23); } return;
    case 300001002:
        { void *r = f_092970(); f_0929b4(r, 9); } return;
    case 300001003:
        { void *r = f_092ce4(); f_092d40(r, 21); } return;
    case 300001004:
        { void *r = f_092970(); f_0929b4(r, 5); } return;
    case 300001100:
        { void *r = f_092970(); f_0929b4(r, 4); } return;
    case 300002001:
        { void *r = f_092ce4(); f_092d40(r, 71); } return;
    case 300003001:
        { void *r = f_092ce4(); f_092d40(r, 24); } return;
    case 300005001:
        { void *r = f_092ce4(); f_092d40(r, 15); } return;
    case 300005002:
        { void *r = f_092ce4(); f_092d40(r, 16); } return;
    case 400003001:
        { void *r = f_092ce4(); f_092d40(r, 12); } return;
    case 400003002:
        { void *r = f_092970(); f_0929b4(r, 26); } return;
    case 400012001:
        { void *r = f_092ce4(); f_092d40(r, 13); } return;
    case 400012005:
        { void *r = f_092ce4(); f_092d40(r, 14); } return;
    case 500001001:
        { void *r = f_092ce4(); f_092d40(r, 22); } return;
    case 600001001:
        { void *r = f_092970(); f_0929b4(r, 20); } return;
    case 600002001:
        { void *r = f_092970(); f_0929b4(r, 17); } return;
    case 600004001:
        { void *r = f_092970(); f_0929b4(r, 19); } return;
    case 600005001:
        { void *r = f_092970(); f_0929b4(r, 27); } return;
    case 600006004:
        { void *r = f_092970(); f_0929b4(r, 28); } return;
    case 600009001:
        { void *r = f_092970(); f_0929b4(r, 29); } return;
    case 600011001:
        { void *r = f_092970(); f_0929b4(r, 30); } return;
    case 600011002:
        { void *r = f_092970(); f_0929b4(r, 31); } return;
    case 600012001:
        { void *r = f_092970(); f_0929b4(r, 32); } return;
    case 600015001:
        { void *r = f_092970(); f_0929b4(r, 33); } return;
    case 800004001:
        { void *r = f_092ce4(); f_092d40(r, 10); } return;
    case 800004002:
        { void *r = f_092970(); f_0929b4(r, 14); } return;
    case 100001010:
    default:
        break;
    }
    { void *r = f_092970(); f_0929b4(r, 1); }
}

extern char D_1a5d88[]; /* "%d" */
extern char D_1a5e08[]; /* "%03d" */
extern char D_1a5e28[]; /* "%02d" */
extern char D_1a61fc[]; /* "%02d:%02d.%03d" */
extern char D_1a620c[]; /* "+%02d:%02d.%03d" */
extern char D_1a621c[]; /* "+%02d.%03d" */
extern float D_1a52a4;
extern float D_1d3140;
extern unsigned int D_24518c;
int sprintf(char *, const char *, ...);
void *f_04b280(void *);
void f_046894(void *, int, int);
void f_0468e8(void *, int, char *, int);
int f_046c8c(void *, int, int);
void *f_0477b0(void *, int, int, float, float, float, float, int, int, void *);
void *f_046de0(void *, int, int, float, float, float, float, int, int, void *);
void f_049188(void *, int, int, float, float, float, float, int, int, int, int, void *, void *);
void f_07b018(void *, int, int, float, float, float, float, int, void *);
int f_06e86c(int);
int f_06e888(int);
int f_06b714(int);
void f_07ac1c(void *);
void f_07ac38(void *, int);
void f_07ac40(void *, int);

#define D77(id) f_0477b0(o, (int)x, (int)y, xa, xb, xc, xd, (id), 480, at<char *>(self, 12) + 44)
#define D46(id) f_046de0(o, (int)x, (int)y, xa, xb, xc, xd, (id), 480, at<char *>(self, 12) + 44)
#define DZ77(id) f_0477b0(o, (int)x, (int)y, D_1a52a4, 0.0f, 0.0f, D_1a52a4, (id), 480, at<char *>(self, 12) + 44)
#define DZ46(id) f_046de0(o, (int)x, (int)y, D_1a52a4, 0.0f, 0.0f, D_1a52a4, (id), 480, at<char *>(self, 12) + 44)

#define PT3(tv0) { int tv = (tv0); int s1 = tv / 1000; sprintf(buf, D_1a5e08, tv % 1000); f_0468e8(o, 2, buf, 0); \
    sprintf(buf, D_1a5e28, s1 % 60); f_0468e8(o, 1, buf, 0); sprintf(buf, D_1a5e28, s1 / 60); f_0468e8(o, 0, buf, 0); }

/* @draft 0x074430 us f_074430
   WHAT IT DOES: menu movie text/sprite dispatcher: parses the number after the first four
   characters of the name and, depending on it, prints strings from the parent's
   records (results, lap times as mm:ss.ms, ids), selects a glyph with f_046894 or draws a sprite
   with f_0477b0 / f_046de0 / the text style f_07b018; numbers above 99999999 run the
   f_049188 scroll path. Returns 1 when something was drawn, 0 otherwise.
   Remaining difference: 3372 vs 3572 bytes; callee-saved allocation differs (6 saved s registers against retail's 5: the multiply-by-reciprocal temporaries of the time splitting get their own registers) and the shared sprite-draw tails are not all merged. */
int f_074430(void *self, char *name, float x, float y, float xa, float xb, float xc, float xd)
{
    char buf[256];
    char ts[16];
    f_07ac1c(ts);
    f_07ac40(ts, 0);
    f_07ac38(ts, (int)at<char *>(self, 12) + 44);
    void *o = f_04b280(at<char *>(self, 12) + 4);
    char *nm = name + 4;
    int n = atoi(nm);
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
        f_049188(o, (int)x, (int)y, xa, xb, xc, xd, n, 0, 480, 150, p + 44, p + 444);
        return 1;
    }
    switch (n) {
    case 0x2dcab0: {
        int t = at<int>(at<char *>(self, 12), 900);
        if (t >= 25)
            t -= 24;
        f_046894(o, 0, t + 0xc66128);
        return 0;
    }
    case 0x4c5ecc: {
        int t = at<int>(at<char *>(self, 12), 904);
        if (t == 255)
            return 1;
        f_046894(o, 0, f_06e888(t));
        return 0;
    }
    case 0x4c5ecd: {
        int t = at<int>(at<char *>(self, 12), 904);
        if (t != 255) {
            f_046894(o, 0, f_06e86c(t));
            return 0;
        }
        sprintf(buf, D_1a5d88, at<int>(at<char *>(self, 12), 1000));
        f_0468e8(o, 0, buf, 0);
        D77(0xe4e5d1);
        return 1;
    }
    case 0x4c5ed1: {
        char *p = at<char *>(self, 12);
        int t = at<int>(p, 904);
        if (t == 255)
            return 1;
        f_046894(o, 0, at<unsigned char>(p, 1368 + t) + 0xd5af24);
        return 0;
    }
    case 0x4c5ed5: {
        char *p = at<char *>(self, 12);
        unsigned int t;
        if (at<int>(p, 904) == 255) {
            f_046894(o, 0, at<int>(p, 900) + 0xc66510);
            p = at<char *>(self, 12);
            unsigned int a = at<unsigned int>(p, 908);
            if (a == 1)
                t = 0x4c5ece;
            else
                t = a + 0x4c5ed3;
            if (a >= 7)
                t = a + 0x895855;
            if (at<unsigned int>(p, 1004) == a)
                t = 0x89582e;
        } else {
            f_046894(o, 0, at<unsigned char>(p, 1416 + at<int>(p, 904) * 10 + at<int>(p, 908)) + 0xc66510);
            p = at<char *>(self, 12);
            unsigned int a = at<unsigned int>(p, 908);
            if (a == 1)
                t = 0x4c5ece;
            else
                t = a + 0x4c5ed3;
            if (a == at<unsigned char>(p, 1272 + at<int>(p, 904)))
                t = 0x89582e;
        }
        D77(t);
        return 1;
    }
    case 0x89582d: {
        char *p = at<char *>(self, 12);
        int a = at<int>(p, 908);
        if (a == at<unsigned char>(p, 1272 + at<int>(p, 904))) {
            D77(0x89582e);
            return 1;
        }
        sprintf(buf, D_1a5d88, a);
        f_0468e8(o, 0, buf, 0);
        return 0;
    }
    case 0x895831: {
        char *p = at<char *>(self, 12);
        if ((unsigned)(at<int>(p, 904) - 19) < 3) {
            if (at<int>(p, 892) == 1)
                D46(0x89582f);
            else
                D46(0x895830);
            return 1;
        }
        f_046894(o, 0, at<int>(p, 892) + n);
        return 0;
    }
    case 0x89584f: {
        char *p = at<char *>(self, 12);
        f_046894(o, 0, at<unsigned char>(p, 3277 + at<int>(p, 896)) + 0xd5af24);
        f_046894(o, 1, at<int>(at<char *>(self, 12), 896) + 0xd5a750);
        return 0;
    }
    case 0x895850:
    case 0x895851:
    case 0x895852: {
        char *p = at<char *>(self, 12);
        if (at<int>(p, 972) == n - 0x89584f) {
            DZ77(n);
            return 1;
        }
        return 0;
    }
    case 0x895853: {
        if (!at<unsigned char>(at<char *>(self, 12), 976))
            return 0;
        DZ77(n);
        return 1;
    }
    case 0x895854:
    case 0x895855:
    case 0x895856:
    case 0x895857: {
        int idx = n - 0x895854;
        int t;
        char *p = at<char *>(self, 12);
        if (idx == 3) {
            if (at<int>(p, 880) == idx) {
                t = at<int>(p, 968);
                PT3(t);
                {
                    float z = D_1a52a4;
                    f_0477b0(o, 196, 136, 0.0f, 0.0f, 0.0f, z, 0x89586e, 240, at<char *>(self, 12) + 44);
                    f_0477b0(o, 308, 136, 0.0f, 0.0f, 0.0f, z, n, 240, at<char *>(self, 12) + 44);
                }
            }
            p = at<char *>(self, 12);
            t = at<int>(p, 912);
        } else
            t = at<int>(p, 916 + idx * 4);
        if (t == 0) {
            D77(0x895844);
            return 1;
        }
        PT3(t);
        {
            char *q = at<char *>(self, 12);
            int k = n - 0x895853;
            if (at<int>(q, 972) == k || (k == 4 && at<unsigned char>(q, 976))) {
                DZ77(n);
                return 1;
            }
        }
        return 0;
    }
    case 0x895858:
    case 0x895859:
    case 0x89585a:
    case 0x89585b: {
        int idx = n - 0x895858;
        char *p = at<char *>(self, 12);
        int t;
        if (idx == 3)
            t = at<int>(p, 940);
        else
            t = at<int>(p, 944 + idx * 4);
        if (t == 0) {
            D77(0x895846);
            return 1;
        }
        {
            int v = f_06b714(t);
            int s0 = v / 1000;
            sprintf(buf, D_1a5e08, v - s0 * 1000);
            f_0468e8(o, 1, buf, 0);
            sprintf(buf, D_1a5e08, s0);
            f_0468e8(o, 0, buf, 0);
        }
        {
            char *q = at<char *>(self, 12);
            int k = n - 0x895857;
            if (at<int>(q, 972) == k || (k == 4 && at<unsigned char>(q, 976))) {
                DZ77(n);
                return 1;
            }
        }
        return 0;
    }
    case 0x895c24:
    case 0x895c25:
    case 0x895c26:
    case 0x895c27:
    case 0x895c28:
    case 0x895c29:
    case 0x895c2a:
    case 0x895c2b: {
        char *rec = at<char *>(self, 12) + (n - 0x895c24) * 28;
        if (!at<char>(rec, 1064))
            return 1;
        f_046894(o, 0, at<int>(rec, 1048) + 0x895c13);
        return 0;
    }
    case 0x895c2c:
    case 0x895c2d:
    case 0x895c2e:
    case 0x895c2f:
    case 0x895c30:
    case 0x895c31:
    case 0x895c32:
    case 0x895c33: {
        char *rec = at<char *>(self, 12) + (n - 0x895c2c) * 28;
        if (!at<char>(rec, 1064))
            return 1;
        f_07b018(ts, (int)x, (int)y, xa, xb, xc, xd, 0, rec + 1064);
        return 1;
    }
    case 0x895c34:
    case 0x895c35:
    case 0x895c36:
    case 0x895c37:
    case 0x895c38:
    case 0x895c39:
    case 0x895c3a:
    case 0x895c3b: {
        int idx = n - 0x895c34;
        char *c0 = at<char *>(self, 12);
        char *rec = c0 + idx * 28;
        if (!at<char>(rec, 1064))
            return 1;
        int t;
        if (idx == 0)
            t = at<int>(c0, 1056);
        else
            t = at<int>(rec, 1056);
        if (t == 0) {
            f_046894(o, 0, 0x895844);
            return 0;
        }
        {
            int s = t / 1000;
            int ms = t - s * 1000;
            int m = s / 60;
            int sec = s - m * 60;
            if (idx == 0)
                sprintf(buf, D_1a61fc, m, sec, ms);
            else if (m > 0)
                sprintf(buf, D_1a620c, m, sec, ms);
            else
                sprintf(buf, D_1a621c, sec, ms);
        }
        f_07b018(ts, (int)x, (int)y, xa, xb, xc, xd, 0, buf);
        return 1;
    }
    case 0x895c42: {
        char *p = at<char *>(self, 12);
        f_046894(o, 0, at<int>(p, 4356) + 0xc66510);
        if (at<unsigned char>(at<char *>(self, 12), 1020))
            DZ46(0x895c42);
        else
            DZ46(0x895c43);
        return 1;
    }
    case 0x896401:
        f_0468e8(o, 0, at<char *>(self, 12) + 977, 0);
        return 0;
    }
    return 0;
}
}
}

/* ---- menuG ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 119 fragment by worker menuG. */
namespace menuG {

template <typename T>
inline T &at(void *p, unsigned int off)
{
    return *(T *)((char *)p + off);
}
inline void *operator new(unsigned int, void *p) { return p; }

extern "C" {
int f_0740ec(void *);
void f_097ba8(void *);
extern char D_242e14[];
extern unsigned int D_24518c;
extern double D_1a6230;
extern int D_1a52d4[];

#define PTR ((void *)at<int>(self, 12))
#define Q(T, o) at<T>(PTR, o)

/* @draft 0x06cfec us f_06cfec
   WHAT IT DOES: answers a query code (0..250) about the owner object at self+12: a switch returning (and for many codes consuming or clearing) fields of it: flags, list counts and the stacked index lists at +872/+900/+7252, bracket tests of the value at +2336 against three thresholds, and a float scaled to a threshold table; unknown codes return 0.
   Remaining difference: register choices in the small arms and 80 bytes of size (structure of the switch arms matches). */
int f_06cfec(void *self, unsigned int cmd)
{
    int tmp[8];
    int tbl[8];
    switch (cmd) {
    case 1:
        { cmd = Q(unsigned char, 2164); goto out; }
    case 2: {
        int v = Q(int, 7508);
        if (!v)
            { cmd = 0; goto out; }
        Q(int, 7508) = 0;
        { cmd = v; goto out; }
    }
    case 3:
        { cmd = Q(int, 1224); goto out; }
    case 4:
        { cmd = Q(unsigned char, 1537); goto out; }
    case 7: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        int n = Q(unsigned char, 4376);
        for (int i = 1; i < n; i++)
            if (Q(unsigned char, 2176 + i) != 10)
                { cmd = 0; goto out; }
        { cmd = 1; goto out; }
    }
    case 8:
        { cmd = 1; goto out; }
    case 9:
        if (Q(int, 1240) != 255)
            { cmd = 0; goto out; }
        if (Q(int, 1348))
            { cmd = 1; goto out; }
        { cmd = 0; goto out; }
    case 11:
        { cmd = Q(int, 1588); goto out; }
    case 12:
        if (Q(unsigned char, 1504))
            { cmd = 1; goto out; }
        Q(unsigned char, 1504) = 1;
        { cmd = 0; goto out; }
    case 13:
        if (!Q(unsigned char, 866))
            { cmd = 0; goto out; }
        Q(unsigned char, 866) = 0;
        { cmd = 1; goto out; }
    case 14: {
        int i = 1;
        int n = Q(unsigned char, 4376);
        Q(int, 868) = 0;
        for (; i < n; i++) {
            if (Q(unsigned char, 2176 + i) == 10 && !Q(unsigned char, 1352 + i)) {
                Q(unsigned char, 1352 + i) = 1;
                break;
            }
        }
        if (i == Q(unsigned char, 4376))
            { cmd = 0; goto out; }
        Q(int, 868) = i;
        { cmd = i; goto out; }
    }
    case 15: {
        int k = Q(int, 868);
        if (!k)
            { cmd = 0; goto out; }
        int n = Q(unsigned char, 4376);
        int cur = Q(unsigned char, 4377 + k);
        for (int i = 1; i < n; i++) {
            if (cur == Q(unsigned char, 4377 + i) && Q(unsigned char, 2176 + i) != 10)
                { cmd = 0; goto out; }
        }
        { cmd = Q(unsigned char, 4377 + Q(int, 868)); goto out; }
    }
    case 16:
        { cmd = Q(unsigned char, 4328 + Q(int, 868)) == 1; goto out; }
    case 17:
        if (Q(unsigned char, 4328 + Q(int, 868)) != 1)
            { cmd = 0; goto out; }
        { cmd = Q(unsigned char, 4280 + Q(int, 868)); goto out; }
    case 18:
        { cmd = Q(unsigned char, 4328 + Q(int, 868)) == 2; goto out; }
    case 19:
        if (Q(unsigned char, 4328 + Q(int, 868)) != 2)
            { cmd = 0; goto out; }
        { cmd = Q(unsigned char, 4280 + Q(int, 868)); goto out; }
    case 20:
        { cmd = Q(unsigned char, 4328 + Q(int, 868)) == 3; goto out; }
    case 21:
        if (Q(unsigned char, 4328 + Q(int, 868)) != 3)
            { cmd = 0; goto out; }
        { cmd = Q(unsigned char, 4280 + Q(int, 868)); goto out; }
    case 22:
        { cmd = Q(unsigned char, 4328 + Q(int, 868)) == 4; goto out; }
    case 23:
        if (Q(unsigned char, 4328 + Q(int, 868)) != 4)
            { cmd = 1; goto out; }
        { cmd = Q(unsigned char, 4280 + Q(int, 868)); goto out; }
    case 24: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        Q(int, 896) = 0;
        Q(int, 876) = 0;
        Q(int, 880) = 0;
        Q(int, 884) = 0;
        Q(int, 888) = 0;
        Q(int, 892) = 0;
        Q(int, 872) = 0;
        int n = Q(unsigned char, 5660);
        for (int i = 1; i < n; i++) {
            if (Q(unsigned char, 2296 + i) && !Q(unsigned char, 1460 + i)) {
                int k = Q(int, 872);
                Q(unsigned char, 1460 + i) = 1;
                Q(int, 872) = k + 1;
                Q(int, 876 + k * 4) = i;
            }
        }
        { cmd = Q(int, 872); goto out; }
    }
    case 25: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        int v = Q(int, 872);
        if (v <= 0)
            { cmd = 0; goto out; }
        v--;
        int r = Q(int, 876 + v * 4);
        Q(int, 872) = v;
        { cmd = r; goto out; }
    }
    case 26: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        int d = Q(int, 2336) - Q(unsigned char, 3656 + Q(int, 868));
        if (d < Q(unsigned char, 6732) && Q(int, 2336) >= Q(unsigned char, 6732))
            { cmd = 1; goto out; }
        if (d >= Q(unsigned char, 6733))
            { cmd = 0; goto out; }
        if (Q(int, 2336) >= Q(unsigned char, 6733))
            { cmd = 1; goto out; }
        { cmd = 0; goto out; }
    }
    case 27: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        int d = Q(int, 2336) - Q(unsigned char, 3656 + Q(int, 868));
        if (d < Q(unsigned char, 6732) && Q(int, 2336) >= Q(unsigned char, 6732))
            { cmd = 2; goto out; }
        if (d < Q(unsigned char, 6733) && Q(int, 2336) >= Q(unsigned char, 6733))
            { cmd = 3; goto out; }
        if (d >= Q(unsigned char, 6734))
            { cmd = 0; goto out; }
        if (Q(int, 2336) >= Q(unsigned char, 6734))
            { cmd = 4; goto out; }
        { cmd = 0; goto out; }
    }
    case 28: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        Q(int, 924) = 0;
        Q(int, 904) = 0;
        Q(int, 908) = 0;
        Q(int, 912) = 0;
        Q(int, 916) = 0;
        Q(int, 920) = 0;
        Q(int, 900) = 0;
        int n = Q(unsigned char, 4376);
        int t = Q(int, 2336);
        int d = t - Q(unsigned char, 3656 + Q(int, 868));
        for (int i = 1; i < n; i++) {
            int c = Q(unsigned char, 3704 + i);
            if (d < c && Q(int, 2336) >= c) {
                tmp[Q(int, 900)] = i;
                Q(int, 900) = Q(int, 900) + 1;
            }
        }
        int m = Q(int, 900);
        if (m > 0) {
            for (int k = 0; k < m; k++)
                Q(int, 900 + (m - k) * 4) = tmp[k];
        }
        { cmd = 0; goto out; }
    }
    case 29: {
        if (!Q(int, 868))
            { cmd = 0; goto out; }
        int v = Q(int, 900);
        if (v <= 0)
            { cmd = 0; goto out; }
        v--;
        int r = Q(int, 904 + v * 4);
        Q(int, 900) = v;
        { cmd = r; goto out; }
    }
    case 30: {
        __builtin_memcpy(tbl, D_1a52d4, 32);
        self = PTR;
        unsigned t = (unsigned)((double)at<float>(self, 2228) * D_1a6230);
        at<int>(self, 7252) = 0;
        for (int j = 0; j < 10; j++)
            at<int>(self, 7256 + j * 4) = 0;
        for (int i = 0; i < 8; i++) {
            if (!at<unsigned char>(self, 1486 + i) && !(t < (unsigned)tbl[i])) {
                int k = at<int>(self, 7252);
                at<unsigned char>(self, 1486 + i) = 1;
                at<int>(self, 7256 + k * 4) = i + 1;
                at<int>(self, 7252) = k + 1;
            }
        }
        { cmd = at<int>(self, 7252); goto out; }
    }
    case 31: {
        int v = Q(int, 7252);
        if (v <= 0)
            { cmd = 0; goto out; }
        v--;
        int r = Q(int, 7256 + v * 4);
        Q(int, 7252) = v;
        { cmd = r; goto out; }
    }
    case 32:
        { cmd = 0; goto out; }
    case 33:
        if (!(Q(int, 2336) < Q(unsigned char, 6734)))
            { cmd = 4; goto out; }
        if (!(Q(int, 2336) < Q(unsigned char, 6733)))
            { cmd = 3; goto out; }
        { cmd = 2 - (Q(int, 2336) < Q(unsigned char, 6732)); goto out; }
    case 41: {
        unsigned v = Q(unsigned, 1232);
        if (v < 25)
            { cmd = v; goto out; }
        { cmd = v - 24; goto out; }
    }
    case 42:
        { cmd = Q(int, 1228); goto out; }
    case 43:
        { cmd = Q(int, 7516); goto out; }
    case 45:
        { cmd = Q(int, 1224); goto out; }
    case 47:
        if (!(D_24518c & 1))
            { cmd = 0; goto out; }
        if (Q(unsigned char, 1505))
            { cmd = 1; goto out; }
        { cmd = 0; goto out; }
    case 48:
        { cmd = Q(int, 1240); goto out; }
    case 49:
        { cmd = 0; goto out; }
    case 50:
        { cmd = Q(unsigned char, 4377 + Q(int, 1240)); goto out; }
    case 52:
        { cmd = Q(unsigned char, 1536); goto out; }
    case 58:
        { cmd = Q(int, 1584); goto out; }
    case 59:
        { cmd = Q(int, 2352); goto out; }
    case 61:
        { cmd = Q(int, 1516); goto out; }
    case 62:
        { cmd = Q(int, 1520); goto out; }
    case 63:
        { cmd = Q(int, 1524); goto out; }
    case 66:
        { cmd = Q(unsigned char, 7524) == 0; goto out; }
    case 68: {
        int v = Q(int, 1232);
        if (v >= 25)
            v -= 24;
        { cmd = v; goto out; }
    }
    case 69:
        { cmd = Q(unsigned char, 1506); goto out; }
    case 71: {
        Q(int, 952) = 0;
        Q(int, 932) = 0;
        Q(int, 936) = 0;
        Q(int, 940) = 0;
        Q(int, 944) = 0;
        Q(int, 948) = 0;
        Q(int, 928) = 0;
        Q(int, 532) = 0;
        int n = Q(unsigned char, 6624);
        for (int i = 1; i < n; i++) {
            if (Q(unsigned char, 2236 + i) && !Q(unsigned char, 1400 + i)) {
                int k = Q(int, 928);
                Q(unsigned char, 1400 + i) = 1;
                Q(int, 928) = k + 1;
                Q(int, 932 + k * 4) = i;
            }
        }
        if (Q(int, 928) == 0)
            f_097ba8(D_242e14);
        { cmd = Q(int, 928); goto out; }
    }
    case 72:
        { cmd = Q(unsigned char, 865) == 0; goto out; }
    case 73:
        if (!Q(unsigned char, 3636))
            { cmd = 1; goto out; }
        Q(unsigned char, 865) = 0;
        Q(unsigned char, 3636) = 0;
        { cmd = 0; goto out; }
    case 5:
    case 74:
    case 77:
    case 78:
    case 79:
        if (!Q(unsigned char, 453))
            { cmd = 0; goto out; }
        Q(unsigned char, 453) = 0;
        { cmd = 1; goto out; }
    case 84: {
        int i = Q(unsigned char, 6624) - 1;
        if (!Q(unsigned char, 2236 + i))
            { cmd = 0; goto out; }
        if (!Q(unsigned char, 1400 + i))
            { cmd = 1; goto out; }
        { cmd = 0; goto out; }
    }
    case 85:
        { cmd = Q(int, 7244); goto out; }
    case 86:
        { cmd = Q(unsigned char, 1505); goto out; }
    case 87:
        Q(unsigned char, 864) = 1;
        if (Q(int, 532) != Q(int, 928))
            { cmd = 1; goto out; }
        Q(unsigned char, 864) = 0;
        { cmd = 0; goto out; }
    case 201:
        f_0740ec(PTR);
        { cmd = 0; goto out; }
    case 202:
        if (!Q(unsigned char, 2372))
            { cmd = 0; goto out; }
        Q(unsigned char, 2372) = 0;
        { cmd = 1; goto out; }
    case 203:
        { cmd = Q(int, 7476); goto out; }
    case 204:
        { cmd = Q(unsigned char, 2380); goto out; }
    case 206:
        { cmd = Q(unsigned char, 2372); goto out; }
    case 207:
        { cmd = Q(int *, 7500)[Q(int, 2376)]; goto out; }
    case 208:
        { cmd = Q(int, 7304); goto out; }
    case 209:
        { cmd = Q(unsigned char, 2388); goto out; }
    case 210:
        if (!Q(unsigned char, 2357))
            { cmd = 0; goto out; }
        Q(unsigned char, 2357) = 0;
        { cmd = 1; goto out; }
    case 211:
        { cmd = Q(unsigned char, 2356); goto out; }
    case 222:
        { cmd = 8; goto out; }
    case 250:
        { cmd = Q(unsigned char, 3752 + Q(int, 1240)); goto out; }
    default:
        cmd = 0;
    }
out:
    return cmd;
}

extern int sprintf(char *, const char *, ...);
void f_078e4c(void *);
void f_01c7a4(void *, int);
void f_005720(void *);
void f_113488(int);
void f_08a71c(int, int);
void *_Znwj(unsigned);
void f_088b58(void *, void *);
int f_01c260(void *);
void f_073840(void *, int, void *);
void f_01dee4(int);
void f_0e7768(int);
void f_04b4d8(void *, const char *, int);
int f_077d38(void *, int);
int f_077b0c(void *, int);
int f_072080(void *, int, int, void *);
extern char D_1a57a8[];
extern char D_1a57f8[];
extern unsigned D_24139c;
extern unsigned char D_2413a0;
extern unsigned D_2413a4;
extern char D_23bb4c[];
extern int D_1d46f4;
extern int D_242b78;
extern char D_1dd6b0[];
extern void *D_242b50;
extern void *D_2413ac;
extern int D_1d326c[];
extern char D_1a57fc[], D_1a5804[], D_1a5814[], D_1a5828[], D_1a5838[], D_1a5844[];
extern char D_1a5850[], D_1a585c[], D_1a5868[], D_1a5874[], D_1a5880[], D_1a588c[];
extern char D_1a5894[], D_1a589c[], D_1a58a4[], D_1a58ac[], D_1a58b4[], D_1a58bc[];
extern char D_1a58c8[], D_1a58d0[];

struct B324 { int w[81]; };

/* @draft 0x06dcb0 us f_06dcb0
   WHAT IT DOES: applies a menu command (code 0..288, with a value) to the owner object at self+12: a switch that stores the value into fields of it (+1224, +1240, +1232, +2360..+2392, ...), picks a random banner string with a linear congruential generator and prints it with sprintf, starts the sub-menu action via f_08a71c for values 1..8 of command 81, loads the resource names for value 900 of command 99, and for command 99 maps a second switch on the value to state bytes and words (+7232, +7532, +3644, ...).
   Remaining difference: instruction scheduling and register choice in the small arms; the f_077d38 calls are not tail-merged as in retail (28 bytes shorter overall). */
void f_06dcb0(void *self, unsigned cmd, int v)
{
    char str[80];
    switch (cmd) {
    case 1:
        if (v == 0) {
            void *p = PTR;
            at<int>(p, 3652) = 1;
            __builtin_memcpy(str, D_1a57a8, 80);
            if (!D_2413a0) {
                D_2413a0 = 1;
                D_24139c = D_2413a4;
            }
            D_24139c = D_24139c * 0x19660d + 0x3c6ef35f;
            sprintf((char *)p + 1863, D_1a57f8, str + (D_24139c % 10) * 8);
        } else {
            at<int>(PTR, 3648) = 2;
            at<int>(PTR, 3652) = 0;
        }
        break;
    case 3:
        at<int>(PTR, 1224) = v;
        break;
    case 5:
        if (v != 0) {
            void *p = PTR;
            if (at<int>(p, 3652)) {
                f_078e4c((char *)p + 2168);
                *(B324 *)((char *)PTR + 1508) = *(B324 *)((char *)PTR + 1832);
                at<int>(PTR, 3648) = 1;
                at<int>(PTR, 3652) = 0;
                at<int>(PTR, 3644) = 1;
            }
        }
        break;
    case 9:
        at<unsigned char>(PTR, 1536) = v != 0;
        break;
    case 15:
        if (v == 0)
            v = 1;
        at<int>(PTR, 7244) = v;
        break;
    case 61:
        at<int>(PTR, 1516) = v;
        f_01c7a4(D_23bb4c, 1);
        break;
    case 62:
        at<int>(PTR, 1520) = v;
        f_01c7a4(D_23bb4c, 0);
        break;
    case 63:
        at<int>(PTR, 1524) = v;
        f_01c7a4(D_23bb4c, 2);
        break;
    case 81:
        if (D_1d46f4 == 1) {
            void *p = PTR;
            D_1d46f4 = 0;
            D_242b78 = 0;
            at<int>(p, 7528) = v;
            f_005720(D_1dd6b0);
            f_097ba8(D_242e14);
            f_113488(0);
            if ((unsigned)v < 9) {
                int k;
                switch (v) {
                case 1:
                    k = 0;
                    goto tail;
                case 2:
                    at<unsigned char>(PTR, 36) = 1;
                    f_08a71c(1, 1);
                    D_242b50 = PTR;
                    break;
                case 3:
                    k = 13;
                    goto tail;
                case 4:
                    k = 9;
                    goto tail;
                case 5:
                    k = 8;
                    goto tail;
                case 6:
                    k = 7;
                    goto tail;
                case 7:
                    k = 10;
                tail:
                    at<unsigned char>(PTR, 36) = 1;
                    f_08a71c(k, 1);
                    break;
                case 8:
                    at<unsigned char>(PTR, 36) = 1;
                    if (!D_2413ac) {
                        void *o = _Znwj(32);
                        D_2413ac = o;
                        f_088b58(o, PTR);
                    }
                    f_08a71c(12, 1);
                    break;
                }
            }
        }
        break;
    case 94:
        at<int>(PTR, 7520) = v;
        break;
    case 95: {
        void *p = PTR;
        at<float>(self, 36) = 1.5707964f;
        int old = at<int>(p, 1212);
        at<unsigned char>(p, 505) = 0;
        at<int>(p, 1204) = v;
        if (old == v && v != 0) {
            if (old != 0 && at<unsigned char>(p, 7513))
                break;
        }
        at<int>(p, 1208) = at<int>(p, 1204);
        at<int>(p, 1212) = v;
        if (v == 0)
            f_01dee4(at<int>(p, 512));
        at<unsigned char>(p, 7513) = 0;
        break;
    }
    case 99: {
        void *p = PTR;
        at<int>(p, 7228) = v;
        switch (v) {
        case 200:
            at<int>(p, 7232) = 1;
            break;
        case 204: {
            at<unsigned char>(p, 7512) = 1;
            int r = f_01c260(p);
            f_073840(PTR, D_1d326c[r], (char *)PTR + 1863);
            break;
        }
        case 300:
            at<int>(p, 7232) = 2;
            break;
        case 301:
            at<int>(p, 7232) = 3;
            break;
        case 302:
            at<int>(p, 7232) = 4;
            break;
        case 303:
            at<int>(p, 7232) = 5;
            break;
        case 304:
            at<int>(p, 7232) = 6;
            break;
        case 305:
            at<int>(p, 7232) = 7;
            break;
        case 306:
            at<int>(p, 7232) = 9;
            break;
        case 307:
            at<int>(p, 7232) = 8;
            break;
        case 310: {
            at<unsigned char>(p, 7512) = 1;
            int r = f_01c260(p);
            f_073840(PTR, D_1d326c[r], (char *)PTR + 1539);
            break;
        }
        case 319:
            at<int>(p, 3644) = 8;
            break;
        case 521:
            if (at<unsigned char>(p, 504))
                at<int>(p, 3640) = 7;
            at<int>(p, 1208) = -1;
            at<unsigned char>(p, 504) = 0;
            at<int>(p, 1212) = 0;
            break;
        case 524:
        case 527:
            at<unsigned char>(p, 7532) = 1;
            at<unsigned char>(p, 2389) = 0;
            break;
        case 525:
            at<unsigned char>(p, 504) = 1;
            at<int>(p, 3640) = 6;
            break;
        case 550:
        case 653:
            at<unsigned char>(p, 7532) = 2;
            break;
        case 555:
            if (at<int>(p, 7236) != 3)
                at<unsigned char>(p, 505) = 0;
            at<unsigned char>(p, 2389) = 0;
            at<unsigned char>(p, 7532) = 3;
            break;
        case 560:
            if (at<int>(p, 7236) != 3)
                at<unsigned char>(p, 505) = 0;
            break;
        case 662:
            at<unsigned char>(p, 7532) = 3;
            break;
        case 801:
            at<unsigned char>(p, 7532) = 1;
            at<int>(p, 1208) = -1;
            at<unsigned char>(p, 504) = 0;
            at<int>(p, 1212) = 0;
            break;
        case 803:
            at<int>(p, 3644) = 7;
            break;
        case 900:
            f_0e7768(0);
            at<unsigned char>(PTR, 7524) = 1;
            f_04b4d8((char *)PTR + 4, D_1a57fc, 1);
            f_04b4d8((char *)PTR + 4, D_1a5804, 1);
            f_04b4d8((char *)PTR + 4, D_1a5814, 0);
            f_04b4d8((char *)PTR + 4, D_1a5828, 0);
            f_04b4d8((char *)PTR + 4, D_1a5838, 0);
            f_04b4d8((char *)PTR + 4, D_1a5844, 0);
            f_04b4d8((char *)PTR + 4, D_1a5850, 0);
            f_04b4d8((char *)PTR + 4, D_1a585c, 0);
            f_04b4d8((char *)PTR + 4, D_1a5868, 0);
            f_04b4d8((char *)PTR + 4, D_1a5874, 0);
            f_04b4d8((char *)PTR + 4, D_1a5880, 0);
            f_04b4d8((char *)PTR + 4, D_1a588c, 0);
            f_04b4d8((char *)PTR + 4, D_1a5894, 0);
            f_04b4d8((char *)PTR + 4, D_1a589c, 0);
            f_04b4d8((char *)PTR + 4, D_1a58a4, 0);
            f_04b4d8((char *)PTR + 4, D_1a58ac, 0);
            f_04b4d8((char *)PTR + 4, D_1a58b4, 0);
            f_04b4d8((char *)PTR + 4, D_1a58bc, 0);
            f_04b4d8((char *)PTR + 4, D_1a58c8, 0);
            f_04b4d8((char *)PTR + 4, D_1a58d0, 0);
            f_097ba8(D_242e14);
            break;
        }
        break;
    }
    case 100:
        at<int>(PTR, 1240) = v;
        break;
    case 101: {
        void *p = PTR;
        int sel = at<int>(p, 1240);
        at<int>(p, 1244) = v;
        at<int>(p, 7516) = at<unsigned char>(p, 3752 + sel);
        int r;
        if (sel == 21)
            r = 27;
        else
            r = f_077d38((char *)p + 6736, at<unsigned char>(p, 3800 + sel * 10 + v));
        at<int>(p, 1500) = r;
        break;
    }
    case 102: {
        at<int>(self, 20) = v * 60000;
        void *p = PTR;
        at<int>(p, 1344) = f_072080(p, at<int>(self, 20), at<int>(self, 16), (char *)p + 1248);
        void *q = PTR;
        at<int>(q, 1348) = v;
        int a1 = at<int>(q, 1248);
        int w = at<int>(self, 16);
        at<int>(q, 1240) = 255;
        at<int>(q, 7516) = w;
        at<int>(q, 1244) = 1;
        at<int>(q, 1500) = f_077d38((char *)q + 6736, a1);
        break;
    }
    case 103:
        at<int>(self, 16) = v;
        break;
    case 104:
        at<int>(PTR, 1244) = 1;
        at<int>(PTR, 1240) = 255;
        break;
    case 105: {
        void *p = PTR;
        at<int>(p, 1232) = v;
        at<int>(p, 1500) = f_077d38((char *)p + 6736, v);
        break;
    }
    case 106:
        at<int>(PTR, 7516) = v;
        break;
    case 107:
        at<int>(PTR, 1228) = v;
        break;
    case 108:
        at<int>(PTR, 1236) = v;
        break;
    case 109:
        at<unsigned char>(PTR, 1506) = v == 0;
        break;
    case 117:
        at<int>(PTR, 1584) = v;
        break;
    case 119:
        if (v) {
            at<int>(PTR, 3644) = 9;
            f_097ba8(D_242e14);
        }
        break;
    case 120:
        at<unsigned char>(PTR, 1537) = v != 0;
        break;
    case 121:
        if (v == 1 || v == 2)
            at<int>(PTR, 3644) = 5;
        else if (v == 3)
            at<int>(PTR, 3644) = 6;
        else if (v == 4)
            at<int>(PTR, 3644) = 8;
        break;
    case 123: {
        void *p = PTR;
        int a = at<int>(p, 7236);
        if (a != 8 && a != 3)
            at<unsigned char>(p, 505) = 1;
        break;
    }
    case 124:
        at<int>(PTR, 2352) = v;
        break;
    case 125: {
        void *p = PTR;
        at<int>(p, 1500) = f_077b0c((char *)p + 6736, at<int>(p, 7244));
        break;
    }
    case 126:
        at<unsigned char>(PTR, 1507) = v != 0;
        break;
    case 127:
        at<int>(PTR, 7248) = v;
        break;
    case 201:
        at<int>(PTR, 7516) = v;
        at<int>(PTR, 2364) = v;
        break;
    case 202:
        at<int>(PTR, 2360) = v;
        at<int>(PTR, 2392) = 1;
        at<int>(PTR, 2384) = 0;
        break;
    case 203:
        at<int>(PTR, 2392) = 2;
        at<int>(PTR, 2384) = 1;
        break;
    case 204:
        at<int>(PTR, 2376) = v;
        break;
    case 205: {
        void *p = PTR;
        int k = v * 4;
        at<int>(p, 2392) = 5;
        at<int>(p, 2376) = v;
        at<int>(p, 7516) = *(int *)(at<int>(p, 7500) + k);
        int a1 = *(int *)(at<int>(p, 7504) + k);
        at<int>(p, 1232) = a1;
        at<int>(p, 2360) = *(int *)(at<int>(p, 7496) + k);
        at<int>(p, 1500) = f_077d38((char *)p + 6736, a1);
        break;
    }
    case 207:
        at<unsigned char>(PTR, 2372) = 0;
        at<int>(PTR, 2392) = v ? 6 : 7;
        break;
    case 208: {
        void *p = PTR;
        at<int>(p, 2368) = v;
        at<int>(p, 1232) = v;
        at<int>(p, 1500) = f_077d38((char *)p + 6736, v);
        break;
    }
    case 209:
        at<int>(PTR, 2392) = 8;
        break;
    case 288:
        at<int>(PTR, 2392) = 9;
        break;
    }
}
}
}

/* ---- menuJ ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* menuJ fragment: TU 119 menu movie scene function f_0702cc. */
namespace menuJ {
template <class T> inline T &at(void *p, unsigned int off) { return *(T *)((char *)p + off); }
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"
static inline float VSin(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvsin.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}
static inline float VCos(float a)
{
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvcos.s S401, S400\n\tsv.s S401, %0" VFPU_END
                     : "=m"(r) : "m"(a) : "memory");
    return r;
}
struct V4 { float v[4]; };
struct C8 { float v[8]; };
struct V2 { float x, z; };
struct I9 { int v[9]; };
struct S4 { short v[4]; };
struct S6 { short v[6]; };

extern "C" {
int sprintf(char *, const char *, ...);
void _ZdlPv(void *);
extern V4 D_1a5e70, D_1a5e80;
extern I9 D_1a5e30;
extern S4 D_1a5e54;
extern S6 D_1a5e5c;
extern char D_1a5e90[]; /* "%02d/25]" */
extern char D_1a5e9c[]; /* "[" */
extern char D_1a5d88[]; /* "%d" */
extern unsigned int D_245194;
extern char D_242e14[];

void f_021720(void);
void f_021750(void);
int f_0216d8(void);
void f_0216e8(int);
void f_01f234(void *, int);
void f_01e5d0(void *, void *);
void f_0cc170(float, float, float);
void f_0cc3e4(void *);
float f_0cd3cc(float);
void f_118380(float);
void f_11817c(int);
void f_1166d4(int);
void f_116898(int);
void f_118e30(int, int, int, int, int);
void f_118738(int, int);
void f_1187d8(int, int);
void f_1187fc(int, float);
int f_0cac88(int, int, void *, int);
void f_026bc8(void *, int, int, int);
int f_01fad0(int);
int f_01f9bc(int);
int f_01f9d8(int);
int f_01f9f4(int);
void f_07ac1c(void *);
void f_07ac38(void *, void *);
void f_07ac40(void *, int);
void f_07cb24(void *, int, int, float, float, float, float, int, char *);
void f_113488(int);
void f_0e5740(void *);
void f_0e5a1c(void *);
void f_0e5a60(void *, float);
float f_0e62d0(void *);
void f_097680(void *, int, int);
void *f_04b280(void *);
void f_046894(void *, int, int);
void f_0468e8(void *, int, char *, int);
void *f_0477b0(void *, int, int, float, float, float, float, int, int, void *);
void *f_048410(void *, int, int, float, float, float, float, int, int, void *, float, float);
int f_01c260(void);
void f_023198(void *, int);
void f_022400(void *, void *, int);
void f_02231c(void *, int);
int f_06b714(int);
}

static inline void geSetup(float z)
{
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
    f_1166d4(5);
    f_116898(7);
    f_116898(9);
    f_118738(7, 1);
    f_1187d8(1, 1);
    f_1187fc(0, z);
    f_116898(10);
    f_116898(5);
    f_116898(7);
    f_1166d4(9);
    f_116898(10);
    f_116898(1);
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
}

static inline void rot2(V2 v, float a, float *o0, float *o2)
{
    *o0 = v.x * VCos(a) - v.z * VSin(a);
    *o2 = v.x * VSin(a) + v.z * VCos(a);
}

extern "C" {

/* @draft 0x0702cc us f_0702cc
   WHAT IT DOES: menu movie 3D scene step for mode (0..5) of the parent record: mode 3 advances the
   intro fade/transition object (counter at +532, timer float at +528) drawing the fade rectangles,
   progress sprites and labels and releasing the object at the end; the other modes set up the
   camera and light (fov 60, or 45 in mode 4), project the selected model with the colour pair
   chosen from the per-slot tables, and for modes 1 and 5 draw the "NN/25]" page counter.
   Remaining difference: 1083 of 1169 words differ (same size class, 4664 vs 4676 bytes; mnemonic sequence ~89% aligned): callee-saved register
   assignment differs (mode/self/parent in s5/s7/s2 against retail s4/s5/s1), retail spills the
   live flag (sp+484) and the pointer at +508 (sp+480) while this keeps them in registers, the
   text object shares its stack slot with the VFPU sin/cos temporaries in retail, and the
   shared tails (page-counter epilogue, case-1/5 colour setup) are laid out differently. */
void f_0702cc(void *self, int mode)
{
    char *p;
    if (mode == 3) {
        p = at<char *>(self, 12);
        void *obj = at<void *>(p, 524);
        if (!obj)
            return;
        int cur = at<int>(p, 532);
        if (cur == at<int>(p, 928))
            return;
        float t = at<float>(p, 528);
        if (t == -3.0f) {
            if (at<unsigned char>(p, 865))
                return;
            at<int>(p, 532) = cur + 1;
            at<unsigned char>(p, 865) = 1;
            f_113488(0);
            p = at<char *>(self, 12);
            if (at<int>(p, 532) != at<int>(p, 928))
                return;
            at<int>(p, 532) = 0;
            at<int>(p, 928) = 0;
            f_0e5740(obj);
            _ZdlPv(obj);
            p = at<char *>(self, 12);
            at<int>(p, 932) = -1;
            at<unsigned char>(p, 864) = 1;
            at<int>(p, 524) = 0;
            f_097680(D_242e14, at<int>(p, 7236), at<unsigned char>(p, 7532));
            return;
        }
        float z = 0.0f;
        if (z <= t) {
            f_021750();
            f_0e5a60(obj, at<float>(at<char *>(self, 12), 528));
            f_021720();
            geSetup(z);
            p = at<char *>(self, 12);
            int sel = at<int>(p, 932 + at<int>(p, 532) * 4);
            void *o = f_04b280(p + 4);
            p = at<char *>(self, 12);
            if (360.0f < at<float>(p, 528)) {
                I9 tbl = D_1a5e30;
                int a = (int)((at<float>(p, 528) - 360.0f) * 255.0f / 60.0f);
                if (a > 255)
                    a = 255;
                int idx = tbl.v[at<unsigned char>(p + sel, 5721)];
                void *tex = at<void *>(p + idx * 4, 2396);
                S4 q = D_1a5e54;
                S6 r;
                r.v[0] = 0; r.v[1] = 0; r.v[2] = 0; r.v[3] = 96; r.v[4] = 128; r.v[5] = 0;
                f_023198(tex, 0);
                f_022400(&r, &q, (a << 24) + 0xffffff);
                p = at<char *>(self, 12);
            }
            if (360.0f < at<float>(p, 528)) {
                int w = (int)((at<float>(p, 528) - 360.0f) * 460.0f / 90.0f);
                if (w > 460)
                    w = 460;
                w += 10;
                S6 r;
                r.v[0] = 10; r.v[1] = 250; r.v[2] = 0; r.v[3] = w; r.v[4] = 251; r.v[5] = 0;
                f_02231c(&r, -1);
            }
            f_1166d4(9);
            int y = 420;
            if (f_01c260() == 2 || f_01c260() == 4)
                y = 390;
            f_0477b0(o, y, 254, 1.0f, 1.0f, 1.0f, 1.0f, 0x4c6a82, 480,
                     at<char *>(self, 12) + 44);
            p = at<char *>(self, 12);
            float tm = at<float>(p, 528);
            if (30.0f < tm) {
                float k = (float)((double)(tm - 30.0f) * 0.1);
                float one = 1.0f;
                float a = one;
                if (240.0f < tm)
                    a -= (tm - 240.0f) / 60.0f;
                if (a < 0.0f)
                    a = 0.0f;
                f_048410(o, 50, 70, one, one, one, a, 0x4c6a81, 480, p + 44, k, 0.2f);
                p = at<char *>(self, 12);
            }
            if (480.0f < at<float>(p, 528)) {
                float k = (float)((double)(at<float>(p, 528) - 480.0f) * 0.1);
                f_046894(o, 0, at<unsigned char>(p + sel, 5661) + 0xd5af24);
                f_046894(o, 1, sel + 0xd5a750);
                float one = 1.0f;
                f_048410(o, 12, 226, one, one, one, one, 0x2dd27f, 480,
                         at<char *>(self, 12) + 44, k, 0.2f);
                p = at<char *>(self, 12);
            }
            if (630.0f < at<float>(p, 528)) {
                float k = (float)((double)(at<float>(p, 528) - 630.0f) * 0.1);
                f_046894(o, 0, at<unsigned char>(p + sel, 5841) + 0xd5af21);
                float one = 1.0f;
                f_048410(o, 12, 254, one, one, one, one, 0x2dd280, 480,
                         at<char *>(self, 12) + 44, k, 0.2f);
                p = at<char *>(self, 12);
            }
            if (700.0f < at<float>(p, 528)) {
                char buf[256];
                float k = (float)((double)(at<float>(p, 528) - 700.0f) * 0.1);
                sprintf(buf, D_1a5d88, f_06b714(at<int>(p + sel * 4, 6144)));
                f_0468e8(o, 0, buf, 0);
                float one = 1.0f;
                f_048410(o, 150, 254, one, one, one, one, 0x2dd281, 480,
                         at<char *>(self, 12) + 44, k, 0.2f);
                p = at<char *>(self, 12);
            }
            if (at<float>(p, 528) < 100.0f) {
                int a = (int)(255.0f - at<float>(p, 528) * 255.0f / 100.0f);
                if (a > 255)
                    a = 255;
                S6 r = D_1a5e5c;
                f_02231c(&r, a << 24);
            }
            float lim = f_0e62d0(obj) - 100.0f;
            p = at<char *>(self, 12);
            if (lim <= at<float>(p, 528)) {
                float lim2 = f_0e62d0(obj) - 100.0f;
                int a = (int)((at<float>(at<char *>(self, 12), 528) - lim2) * 255.0f / 100.0f);
                if (a > 255)
                    a = 255;
                S6 r = D_1a5e5c;
                f_02231c(&r, a << 24);
                p = at<char *>(self, 12);
            }
        } else {
            geSetup(z);
            S6 r = D_1a5e5c;
            f_02231c(&r, 0xff000000);
            f_1166d4(9);
            p = at<char *>(self, 12);
        }
        float nv = at<float>(p, 528) + 1.0f;
        at<float>(p, 528) = nv;
        if ((D_245194 & 0x6000) && 0.0f < nv)
            at<float>(p, 528) = f_0e62d0(obj);
        if (f_0e62d0(obj) <= at<float>(at<char *>(self, 12), 528)) {
            p = at<char *>(self, 12);
            at<float>(p, 528) = -6.0f;
            f_0e5a1c(obj);
        }
        return;
    }

    p = at<char *>(self, 12);
    if (!at<int>(p, 1204))
        return;
    if (!at<unsigned char>(p, 7513))
        return;
    if (mode == 1) {
        if (at<int>(p, 7228) != 555 && at<int>(p, 7236) == 3 && !at<unsigned char>(p, 2389)) {
            at<unsigned char>(p, 7532) = 2;
            at<unsigned char>(p, 2389) = mode;
        }
        p = at<char *>(self, 12);
    }
    V4 cam = D_1a5e70;
    V4 rot = D_1a5e80;
    C8 c;
    c.v[0] = 0; c.v[1] = 0; c.v[2] = 0; c.v[3] = 0; c.v[4] = 0; c.v[5] = 0; c.v[6] = 0; c.v[7] = 0;
    int live = 1;
    int cur = 0;
    float fov = 60.0f;
    if (mode == 4) {
        cam.v[1] = 1500.0f;
        cam.v[2] = 5680.0f;
        rot.v[0] = -0.2f;
        fov = 45.0f;
    }
    float ang = at<float>(self, 36);
    c.v[5] = ang;
    at<float>(self, 36) = ang + 0.0087266443f;
    char *ps = at<char *>(p, 516);
    char *cs = at<char *>(p, 512);
    int *lt = (int *)(cs + 1968);
    char *c288 = c288;
    char *pl = at<char *>(p, 1192);
    int q508 = at<int>(p, 508);
    f_021750();
    f_021720();
    f_118380(50.0f);
    float lv[3];
    lv[0] = 0.24789f; lv[1] = 0.8369f; lv[2] = -0.488006f;
    at<float>(cs, 1936) = lv[0];
    at<float>(cs, 1940) = lv[1];
    at<float>(cs, 1944) = lv[2];
    at<int>(cs, 1968) = 0xaaaaaa;
    lt[2] = 0xaaaaaa;
    at<int>(cs, 1984) = 0x8c8c8c;
    f_1166d4(11);
    f_116898(12);
    f_116898(13);
    f_116898(14);
    f_1166d4(10);
    f_11817c(0xff000000);
    at<int>(ps, 0) = 0;
    at<int>(ps, 4) = 0;
    at<int>(ps, 8) = 0;
    float h = fov * 3.1415927f / 180.0f * 0.5f;
    at<float>(ps, 480) = h;
    float tn = f_0cd3cc(h);
    int W = 480, H = 272;
    at<float>(ps, 484) = 1.7647059f;
    at<float>(ps, 488) = 300.0f;
    at<float>(ps, 492) = 2000000.0f;
    at<int>(ps, 516) = 2048;
    at<int>(ps, 512) = 2048;
    at<int>(ps, 504) = at<int>(ps, 500) * W;
    at<int>(ps, 508) = H;
    at<float>(ps, 496) = 1.0f / tn;
    at<float>(ps, 520) = (float)W * 0.5f;
    at<float>(ps, 524) = (float)H * 0.5f;
    *(V4 *)ps = cam;
    f_0cc170(-rot.v[0], -rot.v[1], -rot.v[2]);
    f_0cc3e4(ps);
    f_021750();
    f_01f234(cs, 1911);
    int i;
    switch (mode) {
    case 0:
    case 3:
        break;
    case 1: {
        p = at<char *>(self, 12);
        i = at<int>(p, 1204);
        if (at<unsigned char>(p + i, 2236) && at<unsigned char>(p + i, 1400)) {
            cur = at<int>(p, 1204);
            break;
        }
        goto reset;
    }
    case 2:
        cur = at<int>(at<char *>(self, 12), 1204);
        break;
    case 4:
        cur = at<int>(at<char *>(self, 12), 1228);
        break;
    case 5: {
        p = at<char *>(self, 12);
        i = at<int>(p, 1204);
        if ((i - 1) % 9 < 3 && i != 57) {
            cur = at<int>(p, 1204);
            break;
        }
        if (at<unsigned char>(p + i, 2236) && at<unsigned char>(p + i, 1400)) {
            cur = at<int>(p, 1204);
            break;
        }
    reset:
        f_021720();
        lt[2] = 0;
        at<int>(cs, 1968) = 0;
        at<int>(cs, 1984) = 0;
        f_021750();
        live = 0;
        at<int>(c288, 12) = 0;
        p = at<char *>(self, 12);
        cur = at<int>(p, 1204);
        break;
    }
    default:
        break;
    }
    if (pl) {
        rot2(*(V2 *)(pl + 4), at<float>(self, 36) * 0.6366197f, &c.v[0], &c.v[2]);
    }
    *(C8 *)cs = c;
    f_01e5d0(cs, ps + 288);
    p = at<char *>(self, 12);
    {
        int m = at<unsigned char>(p + at<int>(p, 1204), 5781);
        at<int>(c288, 8) = (m == 3) ? 0 : m;
    }
    if (cur && live) {
        int m = at<unsigned char>(p + cur, 5781);
        if (m == 3)
            m = 0;
        int key = at<int>(p + cur * 4, 1592);
        if (key != 0) {
            int v = f_01fad0(key - 1);
            at<int>(c288, 1616) = v;
            at<int>(c288, 1612) = v;
            p = at<char *>(self, 12);
            int a = f_01f9bc(at<int>(p + cur * 4, 1592) - 1);
            p = at<char *>(self, 12);
            int b = f_01f9d8(at<int>(p + cur * 4, 1592) - 1);
            p = at<char *>(self, 12);
            int d = f_01f9f4(at<int>(p + cur * 4, 1592) - 1);
            f_026bc8(cs + 2000, a, b, d);
        } else {
            unsigned char *e = (unsigned char *)(at<char *>(cs, 288) + m * 4);
            int col = e[160] | (e[161] << 8) | (e[162] << 16);
            at<int>(c288, 1616) = col;
            at<int>(c288, 1612) = col;
            f_026bc8(cs + 2000, e[148], e[149], e[150]);
        }
    }
    {
        int v = f_0216d8();
        f_0216e8(f_0cac88(q508, 2, ps, v));
    }
    f_021720();
    if (mode == 1 || mode == 5) {
        if (cur && live) {
            geSetup(0.0f);
            char buf[256];
            char ts[48];
            sprintf(buf, D_1a5e90, at<int>(at<char *>(self, 12) + cur * 4, 1592) + 1);
            f_07ac1c(ts);
            f_07ac40(ts, 0);
            f_07ac38(ts, at<char *>(self, 12) + 44);
            sprintf(buf, D_1a5e90, at<int>(at<char *>(self, 12) + cur * 4, 1592) + 1);
            float one = 1.0f;
            f_07cb24(ts, 474, 38, 0.0f, 0.0f, 0.0f, one, 2, buf);
            f_07cb24(ts, 428, 38, 0.0f, 0.0f, 0.0f, one, 2, D_1a5e9c);
            if (D_245194 & 1) {
                p = at<char *>(self, 12);
                if (at<int>(p, 7228) != 551) {
                    unsigned int *k = (unsigned int *)(p + cur * 4 + 1592);
                    unsigned int nv = *k + 1;
                    *k = nv;
                    if (nv >= 25)
                        *k = 0;
                }
            }
        }
    }
}

}
}

/* ---- menuI ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* menuI fragment: TU 119 large menu movie function f_06e8c8. */
namespace menuI {
template <class T> inline T &at(void *p, unsigned int off) { return *(T *)((char *)p + off); }
struct Win { int w[4]; };
extern "C" {
int atoi(const char *);
int sprintf(char *, const char *, ...);
void f_07ac1c(void *);
void f_07ac38(void *, void *);
int f_04b280(void *);
int f_046c8c(int, int, int);
int f_049188(int, int, int, float, float, float, float, int, int, int, int, void *, void *);
void f_046894(int, int, int);
void f_0468e8(int, int, const char *, int);
void f_046910(int, int, const char *, int);
void f_046de0(int, int, int, float, float, float, float, int, int, void *);
void f_0477b0(int, int, int, float, float, float, float, int, int, void *);
void f_047248(int, int, int, int, int, void *, float, float, float, float, float, float);
int f_077de4(void *, int, int, int);
int f_06b748(int);
int f_06b708(void);
int f_06b714(int);
int f_06e888(int);
int f_06e86c(int);
int f_06e8a8(int);
void f_07b018(void *, int, int, int, float, float, float, float, char *);
extern unsigned D_24518c[];
extern char D_2400c5;
extern float D_1d3140, D_1a51d8, D_1a51dc, D_1a51e0, D_1a51e4, D_1a51e8;
extern char D_1a5d80[]; /* "%d.%03d" */
extern char D_1a5d88[]; /* "%d" */
extern char D_1a5d8c[]; /* "999+" */
extern char D_1a5d9c[]; /* "9999K+/9999M" */
extern char D_1a5dac[]; /* "9999K+/%04dM" */
extern char D_1a5dbc[]; /* "WT%02d.CS%02d.CR/%d/%d/%d/%d/%d/%d.SP.%d.PC%c." */
extern char D_1a5dec[]; /* "WF%s.D%s.C%c." */
extern char D_1a5dfc[]; /* "%04dK/%04dM" */
extern char D_1a5e08[]; /* "%03d" */
extern char D_1a5e10[]; /* "%s   %d%%(%d)" */
extern char D_1a5e20[]; /* "%d %s" */
extern char D_1a5e28[]; /* "%02d" */
struct SA { unsigned w; unsigned char b; char z[11]; };
struct SB { unsigned w0, w1, w2; unsigned char b; char z[3]; };
struct T8 { int v[8]; };
extern T8 D_1a52d4;

/* @draft 0x06e8c8 us f_06e8c8
   WHAT IT DOES: menu movie item draw/update for one numbered widget. Parses the item id after the 4-char
   prefix of the name with atoi and dispatches over a large case list: ids of 100000000 and up pick a text id
   (through f_046894), run the common scroll update (f_046c8c / f_049188), or draw (f_0477b0); smaller ids
   either return early or build a text id / formatted number string (sprintf) and print it with f_046894 /
   f_0468e8 / f_046910, or draw a sprite with f_046de0 / f_047248; id 5001006 builds the win-record
   strings (WT.. / WF..) and draws them with f_07b018. Returns 1 when it drew a sprite or finished early,
   0 after printing text.
   Remaining difference: complete transcription of every case (6,432 of 6,660 bytes, frame size and prologue
   equal); the compare tree shapes differ (retail's case sets have extra nodes that fall to the default, one is
   emulated by the balance-only 0x6500000 label; the main n<=99999999 switch root is 0x4c5ecd in retail),
   the sb 452(t1) store is placed after the first compare instead of before it, and shared tails are
   scheduled differently. */
int f_06e8c8(void *self, const char *name, float fx, float fy, float f2, float f3, float f4, float f5)
{
    char buf[256];
    Win w;
    int mode = 3;
    f_07ac1c(&w);
    if (at<int>(self, 4) == 0)
        mode = 1;
    else if (at<int>(self, 4) == 20)
        mode = 2;
    f_07ac38(&w, (char *)at<void *>(self, 12) + 44);
    int h = f_04b280((char *)at<void *>(self, 12) + 4);
    int n = atoi(name + 4);
    int s2;
    if (n > 99999999) {
        void *d = at<void *>(self, 12);
        at<unsigned char>(d, 452) = 1;
        switch (n) {
        case 0x623b768:
            s2 = f_077de4((char *)d + 6736, at<int>(d, 7244), at<int>(d, 7248), 2);
            goto setid;
        case 0x623af99:
            s2 = at<unsigned char>(d, at<int>(d, 1228) + 5661) + 0x6cb9408;
            goto setid;
        case 0x623abb1:
            s2 = at<int>(d, 1232) + 0x6bc49f8;
            goto setid;
        case 0x623b384:
            if (at<int>(d, 7236) == 6) {
                int a3 = at<int>(d, 1204);
                if ((a3 - 1) % 9 >= 3 || a3 == 57) {
                    if (!at<unsigned char>(d, 2236 + a3))
                        return 1;
                    if (!at<unsigned char>(d, 1400 + a3))
                        return 1;
                }
            }
            s2 = at<int>(d, at<int>(d, 7520) * 4 + 5904);
            goto setid;
        case 0x623b767:
            s2 = at<int>(d, 7244) + 0x6f95ac8;
            if (s2 == 0x6f95ace)
                s2 = 0x6f95ad0;
            else if (s2 == 0x6f95acf)
                s2 = 0x6f95ad1;
            goto setid;
        case 0x633111b:
            s2 = f_06b748(at<int>(d, 2352));
            if (s2 == 255)
                s2 = 0x6331115;
            else if (s2 == 0)
                s2 = 0x6331113;
            else
                s2 += 0x6bc49f8;
            goto setid;
        case 0x6423fcf:
            s2 = f_06e8a8(at<int>(d, 1240));
            goto setid;
        case 0x6332881:
            if (!D_2400c5)
                goto draw;
            f_0477b0(h, (int)fx, (int)fy, f2, f3, f4, f5, 0x6332884, 480, (char *)d + 44);
            return 1;
        case 0x6500000: /* balance-only: retail tree has one more case that falls to the default */
        default:
            goto draw;
        }
    setid:
        f_046894(h, 0, s2);
        if (s2 != at<int>(self, 44)) {
            at<int>(self, 44) = s2;
            at<int>(at<void *>(self, 12), 444) = 0;
            at<int>(at<void *>(self, 12), 448) = 0;
        }
    draw:
        {
            int v = f_046c8c(h, n, 480);
            if (n != at<int>(self, 40)) {
                at<int>(self, 40) = n;
                at<int>(at<void *>(self, 12), 444) = 0;
                at<int>(at<void *>(self, 12), 448) = 0;
            }
            if (v < 480)
                return 0;
            d = at<void *>(self, 12);
            if (D_24518c[3] & 0x100)
                at<int>(d, 448) = 121;
            if (at<int>(d, 448) < 121) {
                at<int>(d, 448) = at<int>(d, 448) + 1;
            } else {
                unsigned p = D_24518c[0];
                if (p & 0x200)
                    at<float>(d, 444) += D_1d3140;
                else if (p & 0x100)
                    at<float>(d, 444) -= D_1d3140 + D_1d3140;
                else
                    at<float>(d, 444) -= D_1d3140;
            }
            f_049188(h, (int)fx, (int)fy, f2, f3, f4, f5, n, 0, 480, 150, (char *)d + 44, &at<float>(d, 444));
            return 1;
        }
    } else {
        void *d = at<void *>(self, 12);
        if (at<unsigned char>(d, 505)) {
            switch (n) {
            case 0x2dcaaf ... 0x2dcab0:
            case 0x2dce9a ... 0x2dcea0:
            case 0x2dd27f ... 0x2dd281:
            case 0x2dd285:
            case 0x2dda51:
            case 0x2dda57:
            case 0x4c85df:
                return 1;
            }
        }
        if (at<unsigned char>(d, 2389)) {
            switch (n) {
            case 0x4c5ecd ... 0x4c5ece:
            case 0x4c5ed1:
            case 0x4c5ed5 ... 0x4c5ed9:
            case 0x4c62b1 ... 0x4c62b3:
            case 0x4c9961:
            case 0xe4e991:
                return 1;
            }
        }
        if (at<unsigned char>(d, 7524))
            return 1;
        switch (n) {
        case 0x4c5ecd:
            s2 = f_06e86c(at<int>(d, 1240));
            goto t0;
        case 0x3d3019:
            s2 = f_06b748(at<int>(d, 2352));
            if (s2 == 0)
                s2 = 0x3d3012;
            else if (s2 == 255)
                s2 = 0x3d3014;
            else
                s2 += 0xc66128;
            goto t0;
        case 0x5beb41:
        case 0x4c669d:
        case 0x4c5ecf:
        case 0x5bc04b:
        case 0x5b9d28:
        case 0x5b9d29:
        case 0x2dd663 ... 0x2dd664:
            return 0;
        case 0x1e9fd9:
            f_046910(h, 0, (char *)d + (at<int>(d, 3652) == 1 ? 1863 : 1539), 0);
            return 0;
        case 0x4c4f2b:
        case 0x4c5312:
            f_046910(h, 0, (char *)d + 1539, 0);
            return 0;
        case 0x4c5311:
            f_046910(h, 0, (char *)d + 1539, 0);
            return 0;
        case 0x2dcab0:
        case 0x5c1253:
            s2 = at<int>(d, 1232);
            if (s2 >= 25)
                s2 -= 24;
            s2 += 0xc66128;
            goto t0;
        case 0x2dcaaf:
            s2 = at<int>(d, 1232);
            if (s2 >= 25)
                s2 -= 24;
            if (f_06b708()) {
                float q = (float)at<unsigned>(d, s2 * 4 + 4620) / D_1a51d8;
                int ip = (int)q;
                int fr = (int)((q - (float)ip) * D_1a51dc);
                sprintf(buf, D_1a5d80, ip, fr % 1000);
                f_0468e8(h, 0, buf, 0);
                return 0;
            }
            s2 = f_06b714(at<int>(d, s2 * 4 + 4620));
            goto pnum;
        case 0x3d301a:
            s2 = f_06b748(at<int>(d, 2352));
            if (s2 == 255 || s2 == 0)
                return 1;
            if (f_06b708()) {
                float q = (float)at<unsigned>(d, s2 * 4 + 4620) / D_1a51d8;
                int ip = (int)q;
                int fr = (int)((q - (float)ip) * D_1a51dc);
                sprintf(buf, D_1a5d80, ip, fr % 1000);
                f_0468e8(h, 0, buf, 0);
                return 0;
            }
            s2 = f_06b714(at<int>(d, s2 * 4 + 4620));
            goto pnum;
        case 0x2dd27b: {
            int v = at<int>(d, 1204);
            if (v == 58) {
                f_046de0(h, (int)fx, (int)fy, f2, f3, f4, f5, 0x2dd287, 480, (char *)d + 44);
                return 1;
            }
            s2 = f_06e888(at<int>(d, v * 4 + 6384));
            f_046894(h, 0, s2);
            void *dd = at<void *>(self, 12);
            s2 = f_06e86c(at<int>(dd, at<int>(dd, 1204) * 4 + 6384));
            f_046894(h, 1, s2);
            return 0;
        }
        case 0x2dd27f:
            s2 = at<unsigned char>(d, at<int>(d, 7520) + 5661) + 0xd5af24;
            f_046894(h, 0, s2);
            s2 = at<int>(at<void *>(self, 12), 7520) + 0xd5a750;
            f_046894(h, 1, s2);
            return 0;
        case 0x2dd280:
            s2 = at<unsigned char>(d, at<int>(d, 7520) + 5841) + 0xd5af21;
            goto t0;
        case 0x2dd281:
            s2 = f_06b714(at<int>(d, at<int>(d, 7520) * 4 + 6144));
            goto pnum;
        case 0x2dd665:
            s2 = f_077de4((char *)d + 6736, at<int>(d, 7244), at<int>(d, 7248), 1);
            if (s2 == 0)
                return 1;
            goto t0;
        case 0x2dd666:
            s2 = at<int>(d, 7244) + 0x1036e10;
            goto t0;
        case 0x2dda50:
            s2 = f_06e86c(at<int>(d, 1240));
            goto t0;
        case 0x2dda51:
            s2 = at<int>(d, 1236) + n;
            goto t0;
        case 0x2dda57: {
            int v = at<int>(d, 1500);
            if (v == 0)
                s2 = 0x1037224;
            else if (v == 255)
                s2 = 0x103819e;
            else
                s2 = v + 0x10371ff;
            goto t0;
        }
        case 0x3d14c1 ... 0x3d14c3:
            return 1;
        case 0x3d2844:
            s2 = at<int>(d, 7244) + 0x1036a28;
            goto t0;
        case 0x4c4f2c:
            f_0468e8(h, 0, (char *)d + 1547, 0);
            return 0;
        case 0x4c4f2d:
            f_0468e8(h, 0, (char *)d + 1565, 0);
            return 0;
        case 0x4c5313: {
            int a0 = at<int>(d, 868);
            if (a0 == 0)
                return 1;
            s2 = f_06e888(a0);
            f_046894(h, 0, s2);
            s2 = f_06e86c(at<int>(at<void *>(self, 12), 868));
            f_046894(h, 1, s2);
            return 0;
        }
        case 0x4c5314: {
            unsigned b = at<unsigned char>(d, at<int>(d, 868) + 4377);
            if (b < 4)
                s2 = b + n;
            else
                s2 = 0x4c532b;
            goto t0;
        }
        case 0x4c4f2e: {
            SA sa;
            SB sb;
            int cnt[7];
            sa.w = *(unsigned *)D_1a5d8c;
            sa.b = D_1a5d8c[4];
            sb.w0 = ((unsigned *)D_1a5d9c)[0];
            sb.w1 = ((unsigned *)D_1a5d9c)[1];
            sb.w2 = ((unsigned *)D_1a5d9c)[2];
            sb.b = D_1a5d9c[12];
            for (int q = 0; q < 7; q++)
                cnt[q] = 0;
            for (int q = 0; q < 11; q++)
                sa.z[q] = 0;
            for (int q = 0; q < 3; q++)
                sb.z[q] = 0;
            int c1 = 0, c2 = 0, i;
            int sg7 = '-', sg8 = '-';
            int n1 = at<unsigned char>(d, 4376);
            for (i = 1; i < n1; i++)
                if (at<int>(d, 2336) >= at<unsigned char>(d, 3704 + i))
                    c1++;
            int n2 = at<unsigned char>(d, 5660);
            for (i = 1; i < n2; i++)
                if (at<unsigned char>(d, 2296 + i))
                    c2 += at<unsigned char>(d, 1460 + i) != 0;
            int *p = cnt;
            for (i = 1; i < at<unsigned char>(d, 6624);) {
                int j = i;
                if ((i - 1) % 9 == 0 && i != 1)
                    p++;
                i++;
                if (at<unsigned char>(d, 2236 + j) && at<unsigned char>(d, 1400 + j))
                    *p += 1;
            }
            if (at<unsigned char>(d, 2293) && at<unsigned char>(d, 1457))
                sg7 = '+';
            unsigned a2 = at<unsigned>(d, 2232);
            if (a2 < 1000)
                sprintf((char *)&sa, D_1a5e08, a2);
            float fv = at<float>(at<void *>(self, 12), 2228);
            if (fv < D_1a51e0) {
                int a = (int)(fv * D_1a51e4);
                if (a < 10000)
                    sprintf((char *)&sb, D_1a5dfc, a, (int)fv);
                else
                    sprintf((char *)&sb, D_1a5dac, (int)fv);
            }
            if (c1 == at<unsigned char>(at<void *>(self, 12), 4376) - 1 && c2 == 24 && cnt[0] == 9 &&
                cnt[1] == 9 && cnt[2] == 9 && cnt[3] == 9 && cnt[4] == 9 && cnt[5] == 9 && cnt[6] == 4)
                sg8 = '+';
            int xi = (int)fx, yi = (int)fy;
            sprintf(buf, D_1a5dbc, c1, c2, cnt[0], cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], cnt[6], sg7);
            f_07b018(&w, xi, yi, mode, f2, f3, f4, f5, buf);
            sprintf(buf, D_1a5dec, (char *)&sa, (char *)&sb, sg8);
            f_07b018(&w, xi, yi + 10, mode, f2, f3, f4, f5, buf);
            return 1;
        }
        case 0x4c5319: {
            char *a = (char *)d + at<int>(d, 868);
            if (at<unsigned char>(a, 4328) != 1)
                return 1;
            int v = at<unsigned char>(a, 4280);
            if (v == 58) {
                f_046de0(h, (int)fx, (int)fy, f2, f3, f4, f5, 0x4c5328, 480, (char *)d + 44);
                return 1;
            }
            s2 = at<unsigned char>(d, v + 5661) + n;
            f_046894(h, 0, s2);
            void *dd = at<void *>(self, 12);
            s2 = at<unsigned char>(dd, at<int>(dd, 868) + 4280) + 0xd5a368;
            f_046894(h, 1, s2);
            return 0;
        }
        case 0x4c5321:
            s2 = at<int>(d, at<int>(d, 872) * 4 + 876) + 0xc66128;
            goto t0;
        case 0x4c5322:
            s2 = at<unsigned char>(d, at<int>(d, 868) + 4280) + 0x112ac68;
            goto t0;
        case 0x4c5323: {
            char *a = (char *)d + at<int>(d, 868);
            int a0 = at<unsigned char>(a, 4328);
            s2 = at<unsigned char>(a, 4280);
            if (a0 == 3) {
                if (s2 == 1)
                    s2 = 3;
                else if (s2 == a0)
                    s2 = 4;
                else if (s2 == 4)
                    s2 = 1;
            } else if (a0 == 4)
                s2 += 4;
            s2 += 0x112b050;
            goto t0;
        }
        case 0x4c5324: {
            if (at<int>(d, at<int>(d, 7252) * 4 + 7256) <= 0)
                return 1;
            T8 tbl = D_1a52d4;
            s2 = at<int>(d, at<int>(d, 7252) * 4 + 7256) - 1;
            f_046894(h, 0, tbl.v[s2]);
            return 0;
        }
        case 0x4c5325: {
            int idx = at<int>(d, 868);
            if (idx <= 0)
                return 1;
            int a1 = at<int>(d, 2336);
            int lo = at<unsigned char>(d, 6733);
            int a2 = a1 - at<unsigned char>(d, idx + 3656);
            if (a2 < lo) {
                if (!(a1 < lo)) {
                    f_046de0(h, (int)fx, (int)fy, f2, f3, f4, f5, 0x4c532a, 480, (char *)d + 44);
                    return 1;
                }
            }
            int hi = at<unsigned char>(d, 6734);
            if (!(a2 < hi))
                return 0;
            if (at<int>(d, 2336) < hi)
                return 0;
            f_046de0(h, (int)fx, (int)fy, f2, f3, f4, f5, n + 7, 480, (char *)d + 44);
            return 1;
        }
        case 0x4c5326: {
            int k = at<int>(d, at<int>(d, 900) * 4 + 904);
            if (k <= 0)
                return 1;
            if (k < 10)
                s2 = 0x4c5315;
            else if (k < 24)
                s2 = 0x4c5316;
            else
                s2 = 0x4c5317 + (k >= 40 ? 0x14 : 0);
            f_046894(h, 0, s2);
            void *dd = at<void *>(self, 12);
            s2 = f_06e888(at<int>(dd, at<int>(dd, 900) * 4 + 904));
            f_046894(h, 1, s2);
            dd = at<void *>(self, 12);
            s2 = f_06e86c(at<int>(dd, at<int>(dd, 900) * 4 + 904));
            f_046894(h, 2, s2);
            return 0;
        }
        case 0x4c5327:
            s2 = (int)(at<float>(d, 2228) * D_1a51e4);
            if (s2 >= 10000)
                s2 = 9999;
            s2 = f_06b714(s2);
            goto pnum;
        case 0x4c5329:
        case 0x4c62b4:
        case 0xe4e5d1:
        case 0xe4f188:
            s2 = at<int>(d, 1348);
            goto pnum;
        case 0x4c62be:
            s2 = at<int>(d, 1344);
            goto pnum;
        case 0x4c5ecc:
            s2 = f_06e888(at<int>(d, 1240));
            goto t0;
        case 0x4c5ece:
            s2 = at<unsigned char>(d, at<int>(d, 1240) * 10 + 3801) + 0xc66510;
            goto t0;
        case 0x4c5ed1:
            if (at<int>(d, 1240) == 255)
                s2 = at<unsigned char>(d, at<int>(d, 1228) + 5661);
            else
                s2 = at<unsigned char>(d, at<int>(d, 1240) + 3752);
            s2 += 0xd5af24;
            goto t0;
        case 0x4c5ed5 ... 0x4c5ed9:
            s2 = at<unsigned char>(d, at<int>(d, 1240) * 10 + (n - 0x4c5ed3) + 3800) + 0xc66510;
            goto t0;
        case 0x4c62b5:
            s2 = at<int>(self, 16) + 0x2dce91;
            goto t0;
        case 0x4c85df: {
            int v = at<int>(d, 1228);
            if (v == 0)
                return 1;
            s2 = v + 0xd5a750;
            goto t0;
        }
        case 0x5c1252:
            s2 = at<int>(d, 2364) + 0xd5af24;
            goto t0;
        case 0x5c163f: {
            void *a1 = at<void *>(d, 7480);
            if (a1 == 0)
                return 1;
            void *t4 = at<void *>(d, 7488);
            if (t4 == 0)
                return 1;
            void *v1 = at<void *>(d, 7492);
            if (v1 == 0)
                return 1;
            int off = at<int>(d, 2376) * 4;
            s2 = at<int>(v1, off);
            if (s2 >= 1000)
                s2 = 999;
            sprintf(buf, D_1a5e10, at<const char *>(a1, off), at<int>(t4, off), s2);
            f_07b018(&w, (int)fx, (int)fy, mode, f2, f3, f4, f5, buf);
            return 1;
        }
        case 0x5c164a ... 0x5c1651: {
            int k = n - 0x5c164a;
            char *e = (char *)d + k * 8;
            if (*(signed char *)(e + 7308) == 0)
                return 1;
            sprintf(buf, D_1a5e20, k + 1, e + 7308);
            f_07b018(&w, (int)fx, (int)fy, 0, f2, f3, f4, f5, buf);
            return 1;
        }
        case 0x5c1652 ... 0x5c1659: {
            int k = n - 0x5c1652;
            if (*(signed char *)((char *)d + k * 8 + 7308) == 0)
                return 1;
            sprintf(buf, D_1a5d88, at<int>(d, k * 4 + 7404));
            f_0468e8(h, 0, buf, 0);
            s2 = at<int>(at<void *>(self, 12), k * 4 + 7372);
            if (s2 >= 1000)
                s2 = 999;
            sprintf(buf, D_1a5e08, s2);
            f_0468e8(h, 1, buf, 0);
            return 0;
        }
        case 0x5c3194: {
            void *v1 = at<void *>(d, 7484);
            if (v1 == 0)
                return 1;
            sprintf(buf, D_1a5d88, at<int>(v1, at<int>(d, 2376) * 4));
            f_0468e8(h, 0, buf, 0);
            void *dd = at<void *>(self, 12);
            sprintf(buf, D_1a5d88, 8 - at<int>(at<void *>(dd, 7484), at<int>(dd, 2376) * 4));
            f_0468e8(h, 1, buf, 0);
            return 0;
        }
        case 0x5c3197:
            sprintf(buf, D_1a5e28, at<int>(d, 2376) + 1);
            f_0468e8(h, 0, buf, 0);
            return 0;
        case 0x5c3199: {
            void *a0 = at<void *>(d, 7500);
            if (a0 == 0)
                return 1;
            if (at<int>(d, 7496) == 0)
                return 1;
            s2 = at<int>(a0, at<int>(d, 2376) * 4) + 0xd5af24;
            f_046894(h, 0, s2);
            void *dd = at<void *>(self, 12);
            s2 = at<int>(at<void *>(dd, 7496), at<int>(dd, 2376) * 4) + 0x5c319d;
            f_046894(h, 1, s2);
            return 0;
        }
        case 0x5c319c: {
            void *a0 = at<void *>(d, 7504);
            if (a0 == 0)
                return 1;
            s2 = at<int>(a0, at<int>(d, 2376) * 4) + 0xc66128;
            goto t0;
        }
        case 0x5c6073 ... 0x5c607a: {
            int k = n - 0x5c6073;
            if (*(signed char *)((char *)d + k * 8 + 7308) == 0)
                return 1;
            int v = at<int>(d, k * 4 + 7436);
            if (v != 0)
                s2 = v + 0xd5a750;
            else
                s2 = 0x5c607b;
            goto t0;
        }
        case 0x5c7bca:
            f_047248(h, (int)fx, (int)fy, 0x5c7bca, 480, (char *)d + 44, D_1a51e8, D_1a51e8, f2, f3, f4, f5);
            return 1;
        case 0x1038581 ... 0x1038586:
            s2 = n + at<int>(d, 7244) * 6 - 4999;
            goto t0;
        case 0x1038587:
            f_046894(h, 0, 0x1037225);
            return 0;
        default:
            return 0;
        }
    t0:
        f_046894(h, 0, s2);
        return 0;
    pnum:
        sprintf(buf, D_1a5d88, s2);
        f_0468e8(h, 0, buf, 0);
        return 0;
    }
}
}
}

/* ---- menuF ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 119 fragment by worker menuF. */
namespace menuF {
template <typename T>
inline T &at(void *p, unsigned int off)
{
    return *(T *)((char *)p + off);
}
struct B4 { signed char c0, c1, c2, c3; };
struct Sub { char b[28]; void *link; };
extern "C" {
extern char D_242e14[];
void f_04a620(void *);
void f_04a648(void *, int, void *, int, int, int, int);
void f_04b8a0(void *, void *, int);
void f_06b7b4(void);
void f_0230e0(void *);
void f_07a3f0(void *);
void f_078e4c(void *);
void f_07a634(void *);
void f_078358(void *);
void f_078794(void *);
void f_0784a8(void *);
void f_079afc(void *);
void f_079930(void *);
void f_076f98(void *);
void f_077ecc(void *);
void f_0974cc(void *);
void f_097680(void *, int, int);

/* @draft 0x0731a0 us f_0731a0
   Remaining difference: o8 chain register (sll v0 vs a1), order of the two address adds in the table loop and the loop test register.
   WHAT IT DOES: initialises the menu object: sets up the sub-object at self+4 (f_04a620), links self+456 and self, sets the 300 slots at self+2396 to -1, loads the packed table at p into those slots (calling f_0230e0 on each), registers with f_04a648 and f_04b8a0, runs the member initialisers (f_07a3f0, f_078e4c, f_07a634 x2, f_078358, f_078794, f_0784a8, f_079afc, f_079930, f_076f98, f_077ecc), clears many fields and starts the D_242e14 object (f_0974cc, f_097680). */
void f_0731a0(void *self, int a, char *p)
{
    Sub *sub = (Sub *)((char *)self + 4);
    f_04a620(sub);
    sub->link = (char *)self + 456;
    at<void *>(self, 468) = self;
    struct { B4 h, a, b; } t;
    t.h = *(B4 *)(p + 4);
    unsigned off = ((*(volatile int *)&t.h & 1) == 0) * 8;
    unsigned o8 = off + 8;
    int i;
    for (i = 0; i < 300; i++)
        at<int>(self, 2396 + i * 4) = -1;
    i = 0;
    if (*(int *)&t.h > 0) {
    char *q = (char *)(o8 + (unsigned)p);
    do {
        t.a = *(B4 *)q;
        t.b = *(B4 *)(q + 4);
        q += 8;
        char *e = p + *(int *)&t.a;
        at<char *>(self, 2396 + *(int *)&t.b * 4) = e;
        f_0230e0(e);
        i++;
    } while (i < *(int *)&t.h);
    }
    f_04a648((void *)sub, a, (char *)self + 2396, 0, 0, 0, 0);
    f_04b8a0((void *)sub, (void *)f_06b7b4, 0);
    at<int>(self, 7516) = 0;
    at<char>(self, 504) = 0;
    at<char>(self, 2389) = 0;
    f_07a3f0((char *)self + 1216);
    f_078e4c((char *)self + 2168);
    f_07a634((char *)self + 1508);
    f_07a634((char *)self + 1832);
    f_078358((char *)self + 1172);
    f_078794((char *)self + 2156);
    f_0784a8((char *)self + 536);
    at<int>(self, 2364) = 1;
    at<int>(self, 2368) = 1;
    at<char>(self, 866) = 0;
    at<char>(self, 36) = 0;
    at<char>(self, 453) = 0;
    at<char>(self, 454) = 0;
    at<char>(self, 7524) = 0;
    at<int>(self, 7508) = 0;
    at<char>(self, 7512) = 0;
    at<char>(self, 7513) = 0;
    at<int>(self, 444) = 0;
    at<int>(self, 448) = 0;
    at<char>(self, 3636) = 0;
    at<int>(self, 3640) = 0;
    at<char>(self, 864) = 0;
    at<int>(self, 3644) = 0;
    at<int>(self, 3648) = 0;
    at<int>(self, 3652) = 0;
    at<char>(self, 2356) = 0;
    at<char>(self, 2357) = 0;
    at<int>(self, 2360) = 0;
    at<char>(self, 2372) = 0;
    at<int>(self, 2376) = 0;
    at<char>(self, 2380) = 0;
    at<char>(self, 2388) = 0;
    at<char>(self, 520) = 0;
    at<int>(self, 2392) = 0;
    f_079afc((char *)self + 7468);
    f_079930((char *)self + 7296);
    at<int>(self, 7236) = -1;
    at<char>(self, 7533) = 1;
    at<int>(self, 7232) = 1;
    at<char>(self, 7532) = 1;
    at<int>(self, 1204) = 0;
    at<int>(self, 1208) = 0;
    at<int>(self, 1200) = 0;
    at<int>(self, 1212) = 0;
    at<int>(self, 7216) = 0;
    at<int>(self, 7220) = 0;
    at<int>(self, 7224) = 0;
    at<int>(self, 7228) = 0;
    at<int>(self, 7520) = 0;
    f_076f98((char *)self + 3656);
    f_077ecc((char *)self + 6736);
    f_0974cc(D_242e14);
    f_097680(D_242e14, 1, -1);
}

void f_06c540(void *);
void f_06c590(void *);
void f_04a560(void *);
void f_04a580(void *);
void _ZdlPv(void *);
void f_0783cc(void *);  void f_078448(void *);
void f_07827c(void *);  void f_0782f8(void *);
void f_07a314(void *);  void f_07a390(void *);
void f_07a558(void *);  void f_07a5d4(void *);
void f_0786b8(void *);  void f_078734(void *);
void f_078d70(void *);  void f_078dec(void *);
void f_07a744(void *);  void f_07a7c0(void *);
void f_079854(void *);  void f_0798d0(void *);
void f_079a20(void *);  void f_079a9c(void *);
void f_0201d4(void *) throw();
float f_0cd3cc(float);
void f_0ca814(void *);
void f_0caa5c(void *, int, int, int, int);
extern char D_1a64c8[];
extern char D_1a6530[];
extern const float D_1a5268, D_1a526c, D_1a5270, D_1a5274, D_1a5278, D_1a527c, D_1a5280;

struct XBase {
    char b[456];
    XBase() { f_06c540(this); *(void **)this = D_1a64c8; }
    ~XBase() { f_06c590(this); }
};
struct XSub {
    void *vt;
    char b1[20];
    int f24, f28, f32;
    char b2[44];
    XSub() {
        f_04a560(this);
        *(void **)this = D_1a6530;
        f32 = 0;
        f28 = 0;
        f24 = 0;
    }
    ~XSub() { *(void **)this = D_1a6530; f_04a580(this); }
};
#define XMEM(N, SZ, C, D) struct N { char b[SZ]; N() { C(this); } ~N() { D(this); } };
XMEM(XM1, 636, f_0783cc, f_078448)
XMEM(XM2, 44, f_07827c, f_0782f8)
XMEM(XM3, 292, f_07a314, f_07a390)
XMEM(XM4, 324, f_07a558, f_07a5d4)
XMEM(XM5, 324, f_07a558, f_07a5d4)
XMEM(XM6, 12, f_0786b8, f_078734)
XMEM(XM7, 172, f_078d70, f_078dec)
XMEM(XM8, 4956, f_07a744, f_07a7c0)
XMEM(XM9, 172, f_079854, f_0798d0)
XMEM(XM10, 8, f_079a20, f_079a9c)
struct X12 { int a, b, c; X12() { a = 0; b = 0; c = 0; } };
struct X2736 { char b[2736]; X2736() { f_0201d4(this); } };
struct X576 {
    char b[576];
    X576() __attribute__((always_inline));
};
inline X576::X576() {
        at<int>(this, 500) = 1;
        at<int>(this, 0) = 0;
        at<int>(this, 4) = 0;
        at<int>(this, 8) = 0;
        float f = D_1a5268 * D_1a526c;
        at<float>(this, 480) = f;
        float r = f_0cd3cc(f);
        int w = 480;
        int h = 272;
        at<float>(this, 496) = D_1a5270 / r;
        at<float>(this, 484) = D_1a5274;
        at<float>(this, 488) = D_1a5278;
        at<float>(this, 492) = D_1a527c;
        at<int>(this, 504) = at<int>(this, 500) * w;
        at<int>(this, 516) = 2048;
        at<float>(this, 532) = D_1a5280;
        at<float>(this, 528) = D_1a5280;
        at<float>(this, 520) = (float)w * D_1a526c;
        at<float>(this, 524) = (float)h * D_1a526c;
        at<int>(this, 512) = 2048;
        at<int>(this, 508) = h;
    }
struct XDer : XBase {
    XSub sub;
    XM1 m1;
    char p1[1172 - 536 - 636];
    XM2 m2;
    char p2[1216 - 1172 - 44];
    XM3 m3;
    char p3[1508 - 1216 - 292];
    XM4 m4;
    char p4[1832 - 1508 - 324];
    XM5 m5;
    char p5[2156 - 1832 - 324];
    XM6 m6;
    char p6[2168 - 2156 - 12];
    XM7 m7;
    char p7[2340 - 2168 - 172];
    XM8 m8;
    char p8[7296 - 2340 - 4956];
    XM9 m9;
    char p9[7468 - 7296 - 172];
    XM10 m10;
    void *operator new(unsigned int, void *p) { return p; }
    XDer() __attribute__((always_inline));
};
inline XDer::XDer() {
        X12 *o12 = new X12;
        at<void *>(this, 508) = o12;
        X2736 *o27 = new X2736;
        at<void *>(this, 512) = o27;
        X576 *o57 = new X576;
        at<void *>(this, 516) = o57;
        at<char>(this, 520) = 0;
        f_0ca814(at<void *>(this, 508));
        f_0caa5c(at<void *>(this, 508), 0, at<int>(this, 512), 0, 0);
    }


extern const float D_1a5284, D_1a5288, D_1a528c, D_1a5290, D_1a5294, D_1a5298, D_1a529c;
struct Y576 {
    char b[576];
    Y576() __attribute__((always_inline));
};
inline Y576::Y576() {
        at<int>(this, 500) = 1;
        at<int>(this, 0) = 0;
        at<int>(this, 4) = 0;
        at<int>(this, 8) = 0;
        float f = D_1a5284 * D_1a5288;
        at<float>(this, 480) = f;
        float r = f_0cd3cc(f);
        int w = 480;
        int h = 272;
        at<float>(this, 496) = D_1a528c / r;
        at<float>(this, 484) = D_1a5290;
        at<float>(this, 488) = D_1a5294;
        at<float>(this, 492) = D_1a5298;
        at<int>(this, 504) = at<int>(this, 500) * w;
        at<int>(this, 516) = 2048;
        at<float>(this, 532) = D_1a529c;
        at<float>(this, 528) = D_1a529c;
        at<float>(this, 520) = (float)w * D_1a5288;
        at<float>(this, 524) = (float)h * D_1a5288;
        at<int>(this, 512) = 2048;
        at<int>(this, 508) = h;
    }
struct YDer : XBase {
    XSub sub;
    XM1 m1;
    char p1[1172 - 536 - 636];
    XM2 m2;
    char p2[1216 - 1172 - 44];
    XM3 m3;
    char p3[1508 - 1216 - 292];
    XM4 m4;
    char p4[1832 - 1508 - 324];
    XM5 m5;
    char p5[2156 - 1832 - 324];
    XM6 m6;
    char p6[2168 - 2156 - 12];
    XM7 m7;
    char p7[2340 - 2168 - 172];
    XM8 m8;
    char p8[7296 - 2340 - 4956];
    XM9 m9;
    char p9[7468 - 7296 - 172];
    XM10 m10;
    void *operator new(unsigned int, void *p) { return p; }
    YDer() __attribute__((always_inline));
};
inline YDer::YDer() {
        X12 *o12 = new X12;
        at<void *>(this, 508) = o12;
        X2736 *o27 = new X2736;
        at<void *>(this, 512) = o27;
        Y576 *o57 = new Y576;
        at<void *>(this, 516) = o57;
        at<char>(this, 520) = 0;
        f_0ca814(at<void *>(this, 508));
        f_0caa5c(at<void *>(this, 508), 0, at<int>(this, 512), 0, 0);
    }


/* @draft 0x071510 us f_071510
   Remaining difference: retail keeps a dead 'li a1,1' live across the screen-record init (register numbering of a0/a2/a3 shifts by one after it) and alternates spill temps differently (mine v0/v1).
   WHAT IT DOES: constructs a menu object in place: base menu constructor, vtable, the sub-object at +456, ten member objects (f_0783cc, f_07827c, f_07a314, f_07a558 x2, f_0786b8, f_078d70, f_07a744, f_079854, f_079a20), then allocates a 12-byte record, a 2736-byte object and a 576-byte screen-size record (480x272 scaled by D_1a526c) into fields 508/512/516 and starts them with f_0ca814 and f_0caa5c. */
void f_071510(void *self) { new (self) XDer; }

/* @draft 0x07183c us f_07183c
   Remaining difference: retail keeps a dead 'li a1,1' live across the screen-record init (register numbering of a0/a2/a3 shifts by one after it) and alternates spill temps differently (mine v0/v1).
   WHAT IT DOES: twin of f_071510 using the float constants at D_1a5284..D_1a529c: constructs the menu object in place (base, sub-object, ten members, 12-byte record, 2736-byte object, 576-byte screen record) and starts it with f_0ca814 and f_0caa5c. */
void f_07183c(void *self) { new (self) YDer; }

extern unsigned char *D_1d88a0;
extern float D_1d3140;
extern const float D_1a51d0;
extern unsigned D_2413a4;
extern int D_2413b4;
extern char D_2413b8;
extern int D_2413bc;
extern int D_24518c;
extern char D_1d3290[];
extern char D_1d32d0[];
void f_04b290(void *);
void f_04ad54(void *);
void f_04b2b4(void *);
void f_021720(void);
void f_021750(void);
void f_116898(int);
void f_1166d4(int);
void f_1187d8(int, int);
void f_11610c(void *);
int f_093330(void);
void f_0933f8(int, int);
#define VT(self, i) ((*(int (***)(void *, ...))(self))[i])

/* @draft 0x06c61c us f_06c61c
   Remaining difference: retail reloads the lock byte (+36) into a1 before the D_2413bc store on the join paths (4 bytes larger, delay slots differ); the D_1d3290/D_1d32d0 address hi part is formed in a0 in retail (v1/v0 here).
   WHAT IT DOES: per-frame update of a menu object: returns 1 if it has no sub-object; if the lock byte at +36 is set it calls virtual slot 9 and returns 0. Otherwise, when the global D_1d88a0 flag is clear it polls the sub-object (f_04b290, f_04ad54), calls virtual slot 10 with 6 and runs a button-sequence detector (state D_2413b4 advanced by masks 0x80, 0x10, 0x100, 0x20, 0x8000, 0x1000 and finally 0x200, which calls f_0933f8(f_093330(), 10) and sets byte +454). Then, unless locked, it either adds D_1a51d0 to the float D_1d3140 or calls virtual slot 14 and, if that returns 0, redraws (f_021720, f_116898, f_1187d8, f_11610c, f_04b2b4, f_021750, f_1166d4), calls slot 15 and returns the sub-object word at +16. */
int f_06c61c(void *self)
{
    char *sub = (char *)self + 4;
    char *dp;
    if (at<int>(self, 4) == 0)
        return 1;
    if (at<unsigned char>(self, 36) != 0) {
        VT(self, 9)(self);
        return 0;
    }
    at<char>(self, 452) = 0;
    if (D_1d88a0[12] == 0)
        goto slow;
check:
    if (at<unsigned char>(self, 36) != 0)
        return 0;
    if (D_1d88a0[14] != 0) {
        D_1d3140 += D_1a51d0;
        return 0;
    }
    if (VT(self, 14)(self) != 0)
        return 0;
    f_021720();
    f_116898(1);
    f_1187d8(0, 0);
    dp = (D_2413a4 & 1) ? D_1d3290 : D_1d32d0;
    f_11610c(dp);
    D_2413a4 = D_2413a4 + 1;
    f_04b2b4(sub);
    D_1d3140 = D_1a51d0;
    f_021750();
    f_1166d4(1);
    f_1187d8(1, 1);
    VT(self, 15)(self);
    if (at<unsigned char>(self, 452) == 0) {
        at<int>(self, 444) = 0;
        at<int>(self, 448) = 0;
    }
    D_2413b8 = 0;
    return at<int>(sub, 16);
slow:
    f_04b290(sub);
    f_04ad54(sub);
    if (VT(self, 10)(self, 6) != 1 || at<unsigned char>(self, 454) != 0) {
        D_2413b4 = 0;
        goto check;
    }
    {
        int s3 = D_24518c;
        if ((D_2413bc != s3) & (s3 != 0)) {
            if (D_2413b4 == 0 && (s3 & 0x80))
                D_2413b4 = 1;
            else if (D_2413b4 == 1 && (s3 & 0x10))
                D_2413b4 = 2;
            else if (D_2413b4 == 2 && (s3 & 0x100))
                D_2413b4 = 3;
            else if (D_2413b4 == 3 && (s3 & 0x20))
                D_2413b4 = 4;
            else if (D_2413b4 == 4 && (s3 & 0x8000))
                D_2413b4 = 5;
            else if (D_2413b4 == 5 && (s3 & 0x1000))
                D_2413b4 = 6;
            else if (D_2413b4 == 6 && (s3 & 0x200)) {
                D_2413b4 = 0;
                f_0933f8(f_093330(), 10);
                at<char>(self, 454) = 1;
            } else
                D_2413b4 = 0;
        }
        D_2413bc = s3;
    }
    goto check;
}

int f_0780e0(void *);
void f_04b5c8(void *, void *, void *, int);
void f_04b664(void *, void *, int);
void f_097ba8(void *);
void f_06b6fc(int);
void f_078f20(void *, void *);
void f_01dee4(void *);
void f_02326c(int);
void f_022de4(int, int, int);
void f_022d00(int, int);
void f_01dbc4(void *, int, int, int, int);
void f_0e55c0(void *);
void f_0e5760(void *, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
int f_00222c(void *, void *);
void *f_005a38(void *, void *);
void *f_002acc(void *, void *);
void f_113424(int, void *, int);
float f_01c858(void *, int);
void f_1135b8(int, float);
extern char D_1a5eb8[]; /* "_root" */
extern char D_1a5ec0[]; /* "rrm_300" */
extern char D_1a5ec8[]; /* "rrm_800" */
extern char D_1a5ed0[]; /* "rrm_500" */
extern char D_1a5ed8[]; /* "rrm_600" */
extern char D_1a5ee0[]; /* "ATRAC" */
extern char D_1a5ee8[]; /* "SoundCarGetTruck" */
extern char D_1a5efc[]; /* "SoundCarGet" */
extern char D_1a5f08[]; /* "SoundCarGetPlane" */
extern char D_1c0614[];
extern char D_1dd6b0[];
extern char D_23bb4c[];
extern const float D_1a52a0;

struct X1136 { char b[1136]; X1136() { f_0e55c0(this); } };

/* @draft 0x07251c us f_07251c
   Remaining difference: case 5 store order/constant registers, case 26 holds the sound object in v0/t1 differently and loads the 18 call arguments in another order, 4 bytes shorter overall (copy-loop scheduling).
   WHAT IT DOES: loads saved menu state from the record p according to the kind f_0780e0(p) reports (4..28): kind 5 copies 292 bytes to self+1216 and, by the mode word at p+280, loads one of the rrm_300/800/500/600 sub-menus and starts the sound state (f_097680); kinds 4/11 copy 12 bytes to +2156, 10 copies 324 bytes to +1508 and calls f_06b6fc, 13 copies 40 bytes to +7468, 16/23/28 copy a byte flag, 19 copies 48 bytes and a float, 20 copies 28 bytes and restarts the menu sound, 25 copies 172 bytes to +7296, 26 copies 328 bytes to +536, creates the 1136-byte sound object if needed, starts it and plays the ATRAC SoundCarGet(Truck/Plane) sound; returns 1 when handled, else 0. */
int f_07251c(char *self, char *p)
{
    switch (f_0780e0(p)) {
    case 5:
        __builtin_memcpy(self + 1216, p, 292);
        switch (at<int>(p, 280)) {
        case 2:
            at<int>(self, 7232) = 2;
            f_04b5c8(self + 4, D_1a5eb8, D_1a5ec0, 0);
            f_04b664(self + 4, D_1a5eb8, 0);
            f_097ba8(D_242e14);
            f_097680(D_242e14, 2, -1);
            break;
        case 3:
            f_04b5c8(self + 4, D_1a5eb8, D_1a5ec8, 0);
            f_04b664(self + 4, D_1a5eb8, 0);
            at<int>(self, 7232) = 5;
            at<int>(self, 1224) = 3;
            f_097ba8(D_242e14);
            f_097680(D_242e14, 5, -1);
            break;
        case 4:
            f_04b5c8(self + 4, D_1a5eb8, D_1a5ec8, 0);
            f_04b664(self + 4, D_1a5eb8, 0);
            at<int>(self, 7232) = 4;
            at<int>(self, 1224) = 2;
            f_097ba8(D_242e14);
            f_097680(D_242e14, 4, -1);
            break;
        case 5:
            f_04b5c8(self + 4, D_1a5eb8, D_1a5ed0, 0);
            f_04b664(self + 4, D_1a5eb8, 0);
            at<int>(self, 1224) = 1;
            at<char>(self, 866) = 1;
            at<int>(self, 7232) = 3;
            f_097ba8(D_242e14);
            f_097680(D_242e14, 3, -1);
            break;
        case 6:
            f_04b5c8(self + 4, D_1a5eb8, D_1a5ed8, 0);
            f_04b664(self + 4, D_1a5eb8, 0);
            at<int>(self, 1224) = 4;
            at<int>(self, 7232) = 6;
            f_097680(D_242e14, 6, -1);
            break;
        case 0:
        case 1:
        case 7:
            break;
        }
        goto one;
    case 10:
        __builtin_memcpy(self + 1508, p, 324);
        f_06b6fc(at<char>(self, 1583));
        goto one;
    case 4:
    case 11:
        __builtin_memcpy(self + 2156, p, 12);
        goto one;
    case 12:
        goto one;
    case 13:
        at<char>(self, 2372) = 1;
        __builtin_memcpy(self + 7468, p, 40);
        goto one;
    case 16:
        at<char>(self, 2357) = 1;
        at<char>(self, 2356) = at<unsigned char>(p, 8);
        goto one;
    case 19: {
        int i = 0;
        char *d = self + 2176;
        do {
            unsigned char v = at<unsigned char>(p + i, 8);
            i++;
            *d++ = v;
        } while (i < 48);
        unsigned char b = at<unsigned char>(p, 56);
        int w = at<int>(p, 64);
        float f = at<float>(p, 60);
        at<char>(self, 2224) = b;
        at<float>(self, 2228) = f;
        at<int>(self, 2232) = w;
        f_078f20(self + 2168, self + 3656);
        goto one;
    }
    case 20: {
        at<int>(self, 1212) = at<int>(self, 1204);
        at<char>(self, 7513) = 1;
        void *h = at<void *>(self, 512);
        __builtin_memcpy(self + 1172, p, 28);
        f_01dee4(h);
        f_02326c(2);
        f_022de4(2, at<int>(self, 1188), 0);
        int a = at<int>(self, 1196);
        if (a != 0 && at<unsigned char>(self, 520) == 0) {
            f_022d00(a, 1911);
            at<char>(self, 520) = 1;
        }
        f_01dbc4(h, at<int>(self, 1180), 2, at<int>(self, 1184), 0);
        goto one;
    }
    case 23:
        at<char>(self, 2372) = 1;
        at<char>(self, 2380) = at<unsigned char>(p, 8);
        goto one;
    case 25:
        __builtin_memcpy(self + 7296, p, 172);
        goto one;
    case 26: {
        void *obj = at<void *>(self, 524);
        if (obj == 0) {
            X1136 *n = new X1136;
            obj = n;
            at<void *>(self, 524) = n;
            at<int>(self, 532) = 0;
        }
        char *e = self + at<int>(self, 932 + at<int>(self, 532) * 4);
        unsigned char k1 = e[5781];
        unsigned char k2 = e[5661];
        k1 = k1 != 3 ? k1 : 0;
        __builtin_memcpy(self + 536, p, 328);
        at<float>(self, 528) = D_1a52a0;
        f_0e5760(obj, at<int>(self, 544), at<int>(self, 584), at<int>(self, 564), at<int>(self, 604), at<int>(self, 624),
                 at<int>(self, 644), at<int>(self, 664), at<int>(self, 684), at<int>(self, 704), at<int>(self, 724),
                 at<int>(self, 744), at<int>(self, 764), at<int>(self, 784), at<int>(self, 804), at<int>(self, 824),
                 at<int>(self, 844), k1);
        int r = f_00222c(D_1a5ee0, k2 == 7 ? D_1a5f08 : D_1a5ee8);
        int x = at<int>(D_1c0614 + r * 24, 12);
        f_113424(0, f_002acc(f_005a38(D_1dd6b0, D_1a5efc), D_1a5ee0), x);
        f_1135b8(0, f_01c858(D_23bb4c, 1));
        at<char>(self, 3636) = 1;
        f_04b290(self + 4);
        goto one;
    }
    case 28:
        at<char>(self, 2372) = 1;
        at<char>(self, 2388) = at<unsigned char>(p, 8);
        goto one;
    }
    return 0;
one:
    return 1;
}
}
}
#undef VT
#undef XMEM
