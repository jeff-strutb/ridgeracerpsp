/* The SWG player (retail 0x0451b4 to 0x06b7b4): a Flash-style movie and ActionScript runtime
   (ASContextImpl, its number, string and property handler classes, movie clip properties such
   as _x, _alpha and _currentframe, key names and the Math object), with the std::basic_string
   and std::vector instantiations it uses. Each part below was written separately in its own
   namespace; the functions keep C linkage under their retail addresses. */

/* ---- swgA ---- */
/* TU 117 fragment by worker swgA: retail 0x0451b4..0x04d19c (the Flash/ActionScript
   player range, C++ with exceptions). This fragment transcribes the functions up to
   64 bytes in that range: small getters and setters, vtable stores, empty and
   forwarding destructors, and thin wrappers around the movie-clip and property
   handlers. Callees outside this fragment are declared extern "C" with their retail
   addresses. */

namespace swgA {

extern "C" {

extern int D_241000;
extern char D_1a3998[];

void f_04d8a4(void);
void f_118738(int, int);
void f_1166d4(int);
void f_0221e8(int);
void f_023198(void *, int);
void f_04670c(void *);
void f_0467ec(void *);
void f_07d76c(void *);
void f_07d89c(void *);
void f_07d948(void *);
void f_07da28(void *);
int f_07dacc(void *, int, int, int);
void f_0454d4(void *);
void f_15ba88(void *);
void f_15bd20(void *, float);
void f_15bee8(void *, int);
void f_15bbac(void *, void *);
void f_15c07c(void *, int, int);
void f_15c870(void *, int, int);
void f_15ca34(void *, int, int);
void f_15d2e4(void *, int, int, int);
void f_15d0ac(void *, int, int, int);
void f_15d124(void *, int, int, int);
void f_15cef8(void *, int, int);
void f_15ced4(void *, int, int);
void f_046878(char *);
void f_046c78(char *);
void f_04a610(void *);
void f_04a620(void *);
void _ZdlPv(void *);

/* @implements 0x0453d0 us f_0453d0
   WHAT IT DOES: if the global at D_241000 is set, calls f_04d8a4. */
void f_0453d0(void) {
    if (D_241000) f_04d8a4();
}

/* @implements 0x04559c us f_04559c
   WHAT IT DOES: calls f_118738(7, 1), then f_1166d4(1) and f_1166d4(6). */
void f_04559c(void) {
    f_118738(7, 1);
    f_1166d4(1);
    f_1166d4(6);
}

/* @implements 0x0455cc us f_0455cc
   WHAT IT DOES: calls f_0221e8(4). */
void f_0455cc(void) {
    f_0221e8(4);
}

/* @implements 0x04637c us f_04637c
   WHAT IT DOES: passes its second argument to f_023198 with a zero second argument. */
void f_04637c(void *self, void *x) {
    (void)self;
    f_023198(x, 0);
}

/* @implements 0x04639c us f_04639c
   WHAT IT DOES: returns immediately. */
void f_04639c(void *self) {
    (void)self;
}

/* @implements 0x046684 us f_046684
   WHAT IT DOES: zeroes the words at offsets 24, 0 and 4 of the object, then calls f_04670c on it. */
void f_046684(int *s) {
    s[0] = 0;
    s[1] = 0;
    s[6] = 0;
    f_04670c(s);
}

/* @implements 0x0466ac us f_0466ac
   WHAT IT DOES: zeroes the words at offsets 24, 0 and 4 of the object, then calls f_04670c on it. */
void f_0466ac(int *s) {
    s[0] = 0;
    s[1] = 0;
    s[6] = 0;
    f_04670c(s);
}

/* @implements 0x0466d4 us f_0466d4
   WHAT IT DOES: calls f_0467ec on the object. */
void f_0466d4(void *s) {
    f_0467ec(s);
}

/* @implements 0x0466f0 us f_0466f0
   WHAT IT DOES: calls f_0467ec on the object. */
void f_0466f0(void *s) {
    f_0467ec(s);
}

/* @implements 0x04686c us f_04686c
   WHAT IT DOES: stores the value into the word at offset 408 of the object the first word points to. */
void f_04686c(char **self, int v) {
    *(int *)(*self + 408) = v;
}

/* @implements 0x046878 us f_046878
   WHAT IT DOES: calls f_07d76c with the object pointer loaded from the first word of the object. */
void f_046878(char *s) {
    f_07d76c(*(void **)s);
}

/* @implements 0x0468e8 us f_0468e8
   WHAT IT DOES: sets the byte flag at offset 908 and calls f_07d89c on the object held in the first word. */
void f_0468e8(char *s) {
    void *o = *(void **)s;
    s[908] = 1;
    f_07d89c(o);
}

/* @implements 0x046910 us f_046910
   WHAT IT DOES: sets the byte flag at offset 908 and calls f_07d948 on the object held in the first word. */
void f_046910(char *s) {
    void *o = *(void **)s;
    s[908] = 1;
    f_07d948(o);
}

/* @implements 0x046938 us f_046938
   WHAT IT DOES: sets the byte flag at offset 908 and calls f_07da28 on the object held in the first word. */
void f_046938(char *s) {
    void *o = *(void **)s;
    s[908] = 1;
    f_07da28(o);
}

/* @implements 0x046960 us f_046960
   WHAT IT DOES: calls f_07dacc on the object with the arguments rotated, and stores its result through the pointer argument a2. */
void f_046960(char *s, int a1, int *a2, int a3, int t0) {
    *a2 = f_07dacc(*(void **)s, a3, a1, t0);
}

/* @implements 0x046c78 us f_046c78
   WHAT IT DOES: clears the byte flag at offset 908 and the word at offset 20. */
void f_046c78(char *s) {
    *(int *)(s + 20) = 0;
    s[908] = 0;
}

/* @implements 0x046c84 us f_046c84
   WHAT IT DOES: returns the word at offset 20 of the object. */
int f_046c84(char *s) {
    return *(int *)(s + 20);
}

/* @implements 0x049b38 us f_049b38
   WHAT IT DOES: sets the word at offset 8 to -1, calls f_046c78 on the object at offset 24, then calls f_0454d4 on the sub-object at offset 12. */
void f_049b38(char *s) {
    *(int *)(s + 8) = -1;
    f_046c78(*(char **)(s + 24));
    f_0454d4(s + 12);
}

/* @implements 0x049b74 us f_049b74
   WHAT IT DOES: calls f_1166d4(1). */
void f_049b74(void) {
    f_1166d4(1);
}

/* @implements 0x04a500 us f_04a500
   WHAT IT DOES: calls the function pointer in the word at offset 8 with the second argument and returns its result; returns the (null) pointer value itself, zero, when there is none. */
int f_04a500(char *s, void *a1) {
    int r = *(int *)(s + 8);
    if (r)
        r = ((int (*)(void *))r)(a1);
    return r;
}

/* @implements 0x04a530 us f_04a530
   WHAT IT DOES: calls the function pointer in the word at offset 12 with the second argument and returns its result; returns the (null) pointer value itself, zero, when there is none. */
int f_04a530(char *s, void *a1) {
    int r = *(int *)(s + 12);
    if (r)
        r = ((int (*)(void *))r)(a1);
    return r;
}

/* @implements 0x04a560 us f_04a560
   WHAT IT DOES: stores the vtable address D_1a3998 into the first word of the object. */
void f_04a560(void **self) {
    *self = D_1a3998;
}

/* @implements 0x04a570 us f_04a570
   WHAT IT DOES: stores the vtable address D_1a3998 into the first word of the object. */
void f_04a570(void **self) {
    *self = D_1a3998;
}

/* @implements 0x04a580 us f_04a580
   WHAT IT DOES: stores the vtable address D_1a3998 into the first word of the object. */
void f_04a580(void **self) {
    *self = D_1a3998;
}

/* @implements 0x04a590 us f_04a590
   WHAT IT DOES: stores the vtable address D_1a3998 into the first word of the object. */
void f_04a590(void **self) {
    *self = D_1a3998;
}

/* @implements 0x04a5a0 us f_04a5a0
   WHAT IT DOES: deleting destructor: stores the vtable address D_1a3998 into the object and calls operator delete on it. */
void f_04a5a0(void **self) {
    *self = D_1a3998;
    _ZdlPv(self);
}

/* @implements 0x04a5c8 us f_04a5c8
   WHAT IT DOES: returns immediately. */
void f_04a5c8(void *self) {
    (void)self;
}

/* @implements 0x04a5d0 us f_04a5d0
   WHAT IT DOES: returns immediately. */
void f_04a5d0(void *self) {
    (void)self;
}

/* @implements 0x04a5d8 us f_04a5d8
   WHAT IT DOES: calls f_04a620 on the object. */
void f_04a5d8(void *s) {
    f_04a620(s);
}

/* @implements 0x04a5f4 us f_04a5f4
   WHAT IT DOES: calls f_04a620 on the object. */
void f_04a5f4(void *s) {
    f_04a620(s);
}

/* @implements 0x04a610 us f_04a610
   WHAT IT DOES: returns immediately. */
void f_04a610(void *self) {
    (void)self;
}

/* @implements 0x04a618 us f_04a618
   WHAT IT DOES: returns immediately. */
void f_04a618(void *self) {
    (void)self;
}

/* @implements 0x04a620 us f_04a620
   WHAT IT DOES: sets the byte flag at offset 24 and clears the words at offsets 0 to 20 and 28 of the object. */
void f_04a620(void *obj) {
    char *s = (char *)obj;
    int *p = (int *)obj;
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[7] = 0;
    s[24] = 1;
}

/* @implements 0x04ad30 us f_04ad30
   WHAT IT DOES: clears the word at offset 16 and calls f_15ba88 on the object held in the first word. */
void f_04ad30(char *s) {
    void *o = *(void **)s;
    *(int *)(s + 16) = 0;
    f_15ba88(o);
}

/* @implements 0x04b234 us f_04b234
   WHAT IT DOES: returns immediately. */
void f_04b234(void *self) {
    (void)self;
}

/* @implements 0x04b23c us f_04b23c
   WHAT IT DOES: stores the argument into the word at offset 20 of the record at offset 224 of the object the first word points to. */
void f_04b23c(char *s, int a1) {
    char *p = *(char **)s;
    char *q = *(char **)(p + 224);
    *(int *)(q + 20) = a1;
}

/* @implements 0x04b24c us f_04b24c
   WHAT IT DOES: returns the word at offset 20 of the record at offset 224 of the object the first word points to. */
int f_04b24c(char *s) {
    char *p = *(char **)s;
    char *q = *(char **)(p + 224);
    return *(int *)(q + 20);
}

/* @implements 0x04b25c us f_04b25c
   WHAT IT DOES: calls f_046878 on the object pointer at offset 24 of the record at offset 224 of the object the first word points to. */
void f_04b25c(char *s) {
    char *p = *(char **)s;
    char *q = *(char **)(p + 224);
    f_046878(*(char **)(q + 24));
}

/* @implements 0x04b280 us f_04b280
   WHAT IT DOES: returns the word at offset 24 of the record at offset 224 of the object the first word points to. */
int f_04b280(char *s) {
    char *p = *(char **)s;
    char *q = *(char **)(p + 224);
    return *(int *)(q + 24);
}

/* @implements 0x04b290 us f_04b290
   WHAT IT DOES: calls f_15bd20 on the object with the constant 1.0f. */
void f_04b290(char *s) {
    f_15bd20(*(void **)s, 1.0f);
}

/* @implements 0x04b2b4 us f_04b2b4
   WHAT IT DOES: calls f_15bee8 on the object with a zero second argument. */
void f_04b2b4(char *s) {
    f_15bee8(*(void **)s, 0);
}

/* @implements 0x04b2d4 us f_04b2d4
   WHAT IT DOES: when the argument is non-zero, sets the byte at offset 1 of the object held in the first word to 1; otherwise clears the byte at offset 1 of the object itself. */
void f_04b2d4(char *s, int a1) {
    char *p = *(char **)s;
    if (a1) {
        p[1] = 1;
    } else {
        p[1] = 0;
    }
}

struct L04b2f0 {
    int a;
    float b;
    float c;
    bool d;
};

/* @implements 0x04b2f0 us f_04b2f0
   WHAT IT DOES: builds a local record {1, x, y, false} from its two float arguments and passes it to f_15bbac with the object. */

void f_04b2f0(char *s, float x, float y) {
    L04b2f0 l;
    l.a = 1;
    l.b = x;
    l.c = y;
    l.d = false;
    f_15bbac(*(void **)s, &l);
}

/* @implements 0x04b324 us f_04b324
   WHAT IT DOES: calls f_15c07c on the object with the constant 3 and the argument. */
void f_04b324(char *s, int a1) {
    f_15c07c(*(void **)s, 3, a1);
}

/* @implements 0x04b348 us f_04b348
   WHAT IT DOES: calls f_15c870 on the object with the argument and a zero third argument. */
void f_04b348(char *s, int a1) {
    f_15c870(*(void **)s, a1, 0);
}

/* @implements 0x04b444 us f_04b444
   WHAT IT DOES: calls f_15ca34 on the object with the argument and a zero third argument. */
void f_04b444(char *s, int a1) {
    f_15ca34(*(void **)s, a1, 0);
}

/* @implements 0x04b4b4 us f_04b4b4
   WHAT IT DOES: calls f_15d2e4 on the object with the argument, the second argument truncated to a byte, and a zero fourth argument. */
void f_04b4b4(char *s, int a1, int a2) {
    f_15d2e4(*(void **)s, a1, (unsigned char)a2, 0);
}

/* @implements 0x04b528 us f_04b528
   WHAT IT DOES: calls f_15d0ac on the object with the three arguments, the last one as a boolean. */
void f_04b528(char *s, int a1, int a2, int a3) {
    f_15d0ac(*(void **)s, a1, a2, a3 != 0);
}

/* @implements 0x04b5a8 us f_04b5a8
   WHAT IT DOES: calls f_15d124 on the object with the three arguments, the last one as a boolean. */
void f_04b5a8(char *s, int a1, int a2, int a3) {
    f_15d124(*(void **)s, a1, a2, a3 != 0);
}

/* @implements 0x04b644 us f_04b644
   WHAT IT DOES: calls f_15cef8 on the object with the argument and the second argument as a boolean. */
void f_04b644(char *s, int a1, int a2) {
    f_15cef8(*(void **)s, a1, a2 != 0);
}

/* @implements 0x04b6b4 us f_04b6b4
   WHAT IT DOES: calls f_15ced4 on the object with the argument and the second argument as a boolean. */
void f_04b6b4(char *s, int a1, int a2) {
    f_15ced4(*(void **)s, a1, a2 != 0);
}

/* @implements 0x04b8a0 us f_04b8a0
   WHAT IT DOES: when the record at offset 228 of the object the first word points to is present and the word at offset 8 of the object is set, stores the two arguments into that record at offsets 12 and 8. */
void f_04b8a0(char *s, int a1, int a2) {
    char *p = *(char **)s;
    char *q = *(char **)(p + 228);
    if (!q) return;
    if (!*(void **)(s + 8)) return;
    *(int *)(q + 8) = a1;
    *(int *)(q + 12) = a2;
}

/* @implements 0x04b95c us f_04b95c
   WHAT IT DOES: calls f_04a610 on the object. */
void f_04b95c(void *s) {
    f_04a610(s);
}

/* @implements 0x04b978 us f_04b978
   WHAT IT DOES: calls f_04a610 on the object. */
void f_04b978(void *s) {
    f_04a610(s);
}

/* @implements 0x04b994 us f_04b994
   WHAT IT DOES: calls f_04a620 on the object, then clears the words at offsets 48, 36 and 40. */
void f_04b994(char *s) {
    f_04a620(s);
    *(int *)(s + 36) = 0;
    *(int *)(s + 40) = 0;
    *(int *)(s + 48) = 0;
}

/* @implements 0x04c07c us f_04c07c
   WHAT IT DOES: when the count at offset 32 is at least the index, stores the second argument at offset 168 of the element of the 172-byte array at offset 36. */
void f_04c07c(char *s, int a1, int a2) {
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        *(int *)(e + 168) = a2;
    }
}

/* @implements 0x04c104 us f_04c104
   WHAT IT DOES: when the count at offset 32 is at least the index, stores the second argument at offset 132 of the element of the 172-byte array at offset 36. */
void f_04c104(char *s, int a1, int a2) {
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        *(int *)(e + 132) = a2;
    }
}

/* @implements 0x04c130 us f_04c130
   WHAT IT DOES: when the count at offset 32 is at least the index, stores the third and second arguments at offsets 160 and 156 of the element of the 172-byte array at offset 36. */
void f_04c130(char *s, int a1, int a2, int a3) {
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        *(int *)(e + 156) = a2;
        *(int *)(e + 160) = a3;
    }
}

/* @implements 0x04c248 us f_04c248
   WHAT IT DOES: when the count at offset 32 is at least the index, stores the second argument as a byte at offset 136 of the element of the 172-byte array at offset 36. */
void f_04c248(char *s, int a1, int a2) {
    unsigned char b = (unsigned char)a2;
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        *(unsigned char *)(e + 136) = b;
    }
}

/* @implements 0x04c388 us f_04c388
   WHAT IT DOES: when the count at offset 32 is at least the index, reads the floats at offsets 8 and 12 of the element of the 172-byte array at offset 36 and stores them through the two pointer arguments when those are non-null. */
void f_04c388(char *s, int a1, float *a2, float *a3) {
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        float f0 = *(float *)(e + 8);
        float f1 = *(float *)(e + 12);
        if (a2) *a2 = f0;
        if (a3) *a3 = f1;
    }
}

/* @implements 0x04d110 us f_04d110
   WHAT IT DOES: when the count at offset 32 is at least the index, stores the second argument at offset 124 of the element of the 172-byte array at offset 36. */
void f_04d110(char *s, int a1, int a2) {
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        *(int *)(e + 124) = a2;
    }
}

/* @implements 0x04d13c us f_04d13c
   WHAT IT DOES: returns the word at offset 124 of the element of the 172-byte array at offset 36, or -1 when the index is past the count at offset 32. */
int f_04d13c(char *s, int a1) {
    int r = -1;
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        r = *(int *)(e + 124);
    }
    return r;
}

/* @implements 0x04d16c us f_04d16c
   WHAT IT DOES: when the count at offset 32 is at least the index, sets the byte flag at offset 164 of the element of the 172-byte array at offset 36 to 1. */
void f_04d16c(char *s, int a1) {
    if (*(int *)(s + 32) >= a1) {
        char *e = *(char **)(s + 36) + a1 * 172;
        *(unsigned char *)(e + 164) = 1;
    }
}

}  // extern "C"

}  // namespace swgA

/* ---- swgB ---- */
/* TU 117 fragment swgB: retail 0x04d19c..0x04ffc4 (Flash/ActionScript player, ASContext and
   property-handler classes). Small accessors, vtable stores, empty destructors and thunks first,
   then the larger bodies. */

#define FLD(T, p, o) (*(T *)((char *)(p) + (o)))

namespace swgB {

struct GuardE { ~GuardE() {} };

extern "C" {

extern char D_1a3ad0[];
extern char D_1a3ab0[];
extern char D_1a47f0[];
extern char D_1a47c0[];
extern char D_1a4828[];
extern char D_1a3810[];

void f_1166d4(int);
void f_021750(void);
void f_04d68c(int, int);
void *f_04dfa0(void *);
void f_04e4b4(void *);
void f_05d6dc(void *);
void f_05e2c4(void *);
void _ZdlPv(void *);
void f_021720(void);
void f_116898(int);
void f_118e30(int, int, int, int, int);
void f_0466ac(void *);
void f_0466f0(void *);
void f_05e1b4(void *);
void f_04e930(void *, char *);
void f_04ed28(char *);
void f_04e6d0(char *);
void f_04ee08(char *, char *);
void f_04ee68(char *, char *);
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
extern int D_291424;
extern char D_291400[];
extern char D_24100c[];
extern char D_1a3760[];
extern char D_1a4480[];

/* @implements 0x04d19c us f_04d19c
   WHAT IT DOES: when the index a1 is not below the count at +32, sets the byte at +164 of the
   172-byte entry a1 in the array at +36 to 2. */
void f_04d19c(void *self, int a1) {
    if (!(FLD(int, self, 32) < a1)) {
        unsigned char *b = (unsigned char *)FLD(char *, self, 36) + a1 * 172;
        b[164] = 2;
    }
}

/* @implements 0x04d3b4 us f_04d3b4
   WHAT IT DOES: calls f_1166d4(1) and then f_021750(). */
void f_04d3b4(void) {
    f_1166d4(1);
    f_021750();
}

/* @implements 0x04d708 us f_04d708
   WHAT IT DOES: calls f_04d68c(1, 0xffff). */
void f_04d708(void) {
    f_04d68c(1, 0xffff);
}

/* @implements 0x04d728 us f_04d728
   WHAT IT DOES: calls f_04d68c(0, 0xffff). */
void f_04d728(void) {
    f_04d68c(0, 0xffff);
}

/* @implements 0x04d748 us f_04d748
   WHAT IT DOES: stores the vtable address D_1a3ad0 into the object (constructor body with no
   base or members). */
void f_04d748(void *self) {
    *(void **)self = D_1a3ad0;
}

/* @implements 0x04d758 us f_04d758
   WHAT IT DOES: stores the vtable address D_1a3ad0 into the object, then frees the object
   with operator delete (deleting destructor). */
void f_04d758(void *self) {
    *(void **)self = D_1a3ad0;
    _ZdlPv(self);
}

/* @implements 0x04d780 us f_04d780
   WHAT IT DOES: stores the second argument at offset 4 of the object. */
void f_04d780(void *self, int v) {
    FLD(int, self, 4) = v;
}

/* @implements 0x04d788 us f_04d788
   WHAT IT DOES: stores the second argument at offset 4 of the object. */
void f_04d788(void *self, int v) {
    FLD(int, self, 4) = v;
}

/* @implements 0x04d790 us f_04d790
   WHAT IT DOES: stores the second argument at offset 4 of the object. */
void f_04d790(void *self, int v) {
    FLD(int, self, 4) = v;
}

/* @implements 0x04d798 us f_04d798
   WHAT IT DOES: stores the vtable address D_1a3ab0 into the object. */
void f_04d798(void *self) {
    *(void **)self = D_1a3ab0;
}

/* @implements 0x04d7a8 us f_04d7a8
   WHAT IT DOES: stores the vtable address D_1a3ab0 into the object, then frees the object
   with operator delete (deleting destructor). */
void f_04d7a8(void *self) {
    *(void **)self = D_1a3ab0;
    _ZdlPv(self);
}

/* @implements 0x04d7d0 us f_04d7d0
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d7d0(void *self) {
    (void)self;
}

/* @implements 0x04d7d8 us f_04d7d8
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d7d8(void *self) {
    (void)self;
}

/* @implements 0x04d7e0 us f_04d7e0
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d7e0(void *self) {
    (void)self;
}

/* @implements 0x04d7e8 us f_04d7e8
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d7e8(void *self) {
    (void)self;
}

/* @implements 0x04d7f0 us f_04d7f0
   WHAT IT DOES: returns 0. */
int f_04d7f0(void) {
    return 0;
}

/* @implements 0x04d7f8 us f_04d7f8
   WHAT IT DOES: returns 0. */
int f_04d7f8(void) {
    return 0;
}

/* @implements 0x04d800 us f_04d800
   WHAT IT DOES: returns the float constant 0.0. */
float f_04d800(void) {
    return 0.0f;
}

/* @implements 0x04d80c us f_04d80c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d80c(void *self) {
    (void)self;
}

/* @implements 0x04d814 us f_04d814
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d814(void *self) {
    (void)self;
}

/* @implements 0x04d81c us f_04d81c
   WHAT IT DOES: returns 1. */
int f_04d81c(void) {
    return 1;
}

/* @implements 0x04d824 us f_04d824
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04d824(void *self) {
    (void)self;
}

/* @implements 0x04db8c us f_04db8c
   WHAT IT DOES: stores the vtable address D_1a47f0 into the object. */
void f_04db8c(void *self) {
    *(void **)self = D_1a47f0;
}

/* @implements 0x04db9c us f_04db9c
   WHAT IT DOES: stores the vtable address D_1a47f0 into the object, then frees it with
   operator delete (deleting destructor). */
void f_04db9c(void *self) {
    *(void **)self = D_1a47f0;
    _ZdlPv(self);
}

/* @implements 0x04dbc4 us f_04dbc4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dbc4(void *self) {
    (void)self;
}

/* @implements 0x04dbcc us f_04dbcc
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dbcc(void *self) {
    (void)self;
}

/* @implements 0x04dbd4 us f_04dbd4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dbd4(void *self) {
    (void)self;
}

/* @implements 0x04dbdc us f_04dbdc
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dbdc(void *self) {
    (void)self;
}

/* @implements 0x04dbe4 us f_04dbe4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dbe4(void *self) {
    (void)self;
}

/* @implements 0x04dbec us f_04dbec
   WHAT IT DOES: stores the vtable address D_1a47f0 into the object. */
void f_04dbec(void *self) {
    *(void **)self = D_1a47f0;
}

/* @implements 0x04dbfc us f_04dbfc
   WHAT IT DOES: stores the vtable address D_1a47f0 into the object, then frees it with
   operator delete (deleting destructor). */
void f_04dbfc(void *self) {
    *(void **)self = D_1a47f0;
    _ZdlPv(self);
}

/* @implements 0x04dc24 us f_04dc24
   WHAT IT DOES: sets the word at offset 32 of the object to 0. */
void f_04dc24(void *self) {
    FLD(int, self, 32) = 0;
}

/* @implements 0x04dc2c us f_04dc2c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc2c(void *self) {
    (void)self;
}

/* @implements 0x04dc34 us f_04dc34
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc34(void *self) {
    (void)self;
}

/* @implements 0x04dc3c us f_04dc3c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc3c(void *self) {
    (void)self;
}

/* @implements 0x04dc44 us f_04dc44
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc44(void *self) {
    (void)self;
}

/* @implements 0x04dc4c us f_04dc4c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc4c(void *self) {
    (void)self;
}

/* @implements 0x04dc54 us f_04dc54
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc54(void *self) {
    (void)self;
}

/* @implements 0x04dc5c us f_04dc5c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dc5c(void *self) {
    (void)self;
}

/* @implements 0x04dc64 us f_04dc64
   WHAT IT DOES: stores the vtable address D_1a47c0 into the object, then frees it with
   operator delete (deleting destructor). */
void f_04dc64(void *self) {
    *(void **)self = D_1a47c0;
    _ZdlPv(self);
}

/* @implements 0x04dc8c us f_04dc8c
   WHAT IT DOES: stores the vtable address D_1a47c0 into the object. */
void f_04dc8c(void *self) {
    *(void **)self = D_1a47c0;
}

/* @implements 0x04dc9c us f_04dc9c
   WHAT IT DOES: returns 0. */
int f_04dc9c(void *self) {
    (void)self;
    return 0;
}

/* @implements 0x04dca4 us f_04dca4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dca4(void *self) {
    (void)self;
}

/* @implements 0x04dcac us f_04dcac
   WHAT IT DOES: returns 0. */
int f_04dcac(void *self) {
    (void)self;
    return 0;
}

/* @implements 0x04dcb4 us f_04dcb4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dcb4(void *self) {
    (void)self;
}

/* @implements 0x04dcbc us f_04dcbc
   WHAT IT DOES: stores the vtable address D_1a4828 into the object. */
void f_04dcbc(void *self) {
    *(void **)self = D_1a4828;
}

/* @implements 0x04dccc us f_04dccc
   WHAT IT DOES: stores the vtable address D_1a4828 into the object, then frees it with
   operator delete (deleting destructor). */
void f_04dccc(void *self) {
    *(void **)self = D_1a4828;
    _ZdlPv(self);
}

/* @implements 0x04dcf4 us f_04dcf4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dcf4(void *self) {
    (void)self;
}

/* @implements 0x04dcfc us f_04dcfc
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dcfc(void *self) {
    (void)self;
}

/* @implements 0x04dd04 us f_04dd04
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dd04(void *self) {
    (void)self;
}

/* @implements 0x04dd0c us f_04dd0c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04dd0c(void *self) {
    (void)self;
}

/* @implements 0x04de00 us f_04de00
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04de00(void *self) {
    (void)self;
}

/* @implements 0x04de08 us f_04de08
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04de08(void *self) {
    (void)self;
}

/* @implements 0x04df90 us f_04df90
   WHAT IT DOES: returns 0. */
int f_04df90(void *self) {
    (void)self;
    return 0;
}

/* @implements 0x04df98 us f_04df98
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04df98(void *self) {
    (void)self;
}

/* @implements 0x04e638 us f_04e638
   WHAT IT DOES: if the second argument is non-null, passes it to f_04e4b4. */
void f_04e638(void *self, void *a1) {
    (void)self;
    if (a1) {
        f_04e4b4(a1);
    }
}

/* @draft 0x04e65c us f_04e65c
   WHAT IT DOES: walks a range of 56-byte records from the first argument to the second; each
   record whose word at +12 does not equal the word at +16 advances that word by 36 until it
   does.
   Remaining difference: 12/17 words differ, first at +0x0; size 68 vs 56. */
void f_04e65c(char *a0, char *a1) {
    while (a0 != a1) {
        int end = FLD(int, a0, 16);
        int cur = FLD(int, a0, 12);
        if (cur == end) {
            a0 += 56;
        } else {
            cur += 36;
            while (cur != end) {
                cur += 36;
            }
            a0 += 56;
        }
    }
}

/* @implements 0x04e694 us f_04e694
   WHAT IT DOES: allocates a 12-byte node, stores it in the object at +4, and makes it a
   self-linked node (its words at 0 and +4 point at itself).
   Remaining difference: 4/15 words differ, first at +0x24; size 52 vs 60. */
struct GuardC694 {
    int a;
    void *b;
    GuardE m;
    GuardC694() {
        void *p = f_04dfa0((void *)12);
        b = p;
        *(void **)p = p;
        FLD(void *, p, 4) = p;
    }
};
inline void *operator new(unsigned, void *p) { return p; }
void f_04e694(void *self) {
    new (self) GuardC694;
}

/* @implements 0x04e8c0 us f_04e8c0
   WHAT IT DOES: stores the vtable address D_1a3ab0 into the object.
   */
void f_04e8c0(void *self) {
    GuardE g;
    *(void **)self = D_1a3ab0;
}

/* @implements 0x04ebf4 us f_04ebf4
   WHAT IT DOES: allocates a node for the pointer a1+4, stores that pointer in the node and
   returns the node address plus 4.
   Remaining difference: 10/15 words differ, first at +0x0; size 52 vs 60. */
char *f_04ebf4(void *a0, char *a1) {
    (void)a0;
    GuardE g;
    char *s0 = a1 + 4;
    char *v0 = (char *)f_04dfa0(s0);
    *(char **)v0 = s0;
    return v0 + 4;
}

/* @implements 0x04eec0 us f_04eec0
   WHAT IT DOES: stores the vtable address D_1a3810 into the object, then calls the base
   destructor f_05d6dc (declared throw() so the guard needs no landing pad). */
extern "C" void f_05d6dc_nt(void *) throw() __asm__("f_05d6dc");
void f_04eec0(void *self) {
    GuardE g;
    *(void **)self = D_1a3810;
    f_05d6dc_nt(self);
}

/* @implements 0x04eee8 us f_04eee8
   WHAT IT DOES: calls f_04e4b4 on the object; a throw() function, so the exception path is
   __cxa_call_unexpected.
   */
void f_04eee8(void *self) throw() {
    GuardE g;
    f_04e4b4(self);
}

/* @implements 0x04f1cc us f_04f1cc
   WHAT IT DOES: returns 13. */
int f_04f1cc(void *self) {
    (void)self;
    return 13;
}

/* @draft 0x04f1d4 us f_04f1d4
   WHAT IT DOES: returns the string "propertyhandler".
   Remaining difference: the code matches, but in the whole object file the literal is followed by
   another part's "sound..." string where retail has a zero word; the literals between 0x04ffc4
   and 0x05c698 are not written yet. */
const char *f_04f1d4(void *self) {
    (void)self;
    return "propertyhandler";
}

/* @implements 0x04f228 us f_04f228
   WHAT IT DOES: returns 0. */
int f_04f228(void *self) {
    (void)self;
    return 0;
}

/* @implements 0x04f230 us f_04f230
   WHAT IT DOES: returns the word at offset 40 of the object. */
int f_04f230(void *self) {
    return FLD(int, self, 40);
}

/* @implements 0x04f238 us f_04f238
   WHAT IT DOES: returns the word at offset 4 of the object. */
int f_04f238(void *self) {
    return FLD(int, self, 4);
}

/* @implements 0x04f240 us f_04f240
   WHAT IT DOES: stores the second argument at offset 4 of the object. */
void f_04f240(void *self, int v) {
    FLD(int, self, 4) = v;
}

/* @implements 0x04f858 us f_04f858
   WHAT IT DOES: calls f_05e2c4 on the object's sub-object at offset 8. */
void f_04f858(char *self) {
    f_05e2c4(self + 8);
}

/* @implements 0x04ff50 us f_04ff50
   WHAT IT DOES: returns 0. */
int f_04ff50(void *self) {
    (void)self;
    return 0;
}

/* @implements 0x04ff58 us f_04ff58
   WHAT IT DOES: returns 0. */
int f_04ff58(void *self) {
    (void)self;
    return 0;
}

/* @implements 0x04ff60 us f_04ff60
   WHAT IT DOES: calls the virtual function in vtable slot 23 of the object and returns its
   int result converted to double. */
double f_04ff60(void *self) {
    void **vt = *(void ***)self;
    int r = ((int (*)(void *))vt[23])(self);
    return (double)r;
}

/* @implements 0x04ff8c us f_04ff8c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ff8c(void *self) {
    (void)self;
}

/* @implements 0x04ff94 us f_04ff94
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ff94(void *self) {
    (void)self;
}

/* @implements 0x04ff9c us f_04ff9c
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ff9c(void *self) {
    (void)self;
}

/* @implements 0x04ffa4 us f_04ffa4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ffa4(void *self) {
    (void)self;
}

/* @implements 0x04ffac us f_04ffac
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ffac(void *self) {
    (void)self;
}

/* @implements 0x04ffb4 us f_04ffb4
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ffb4(void *self) {
    (void)self;
}

/* @implements 0x04ffbc us f_04ffbc
   WHAT IT DOES: empty body (an empty virtual function). */
void f_04ffbc(void *self) {
    (void)self;
}

/* @draft 0x04d1cc us f_04d1cc
   WHAT IT DOES: returns early when the index a1 exceeds the count at +32; otherwise takes the entry a1
   (172 bytes each, array at +36) and writes the difference of two float pairs into a2 and a3 when
   those pointers are non-null.
   Remaining difference: 20/22 words differ, first at +0x8; size 84 vs 88. */
void f_04d1cc(char *self, int a1, float *a2, float *a3) {
    if (FLD(int, self, 32) < a1) {
        return;
    }
    char *p = FLD(char *, self, 36) + a1 * 172;
    if (a2) {
        *a2 = FLD(float, p, 96) - FLD(float, p, 92);
    }
    if (a3) {
        *a3 = FLD(float, p, 116) - FLD(float, p, 108);
    }
}

/* @implements 0x04d350 us f_04d350
   WHAT IT DOES: calls f_021720, then f_116898 with the values 5, 7, 9, 10 and 1, then f_118e30
   with (0, 2, 3, 0, 0), and finally f_1166d4(4). */
void f_04d350(void) {
    f_021720();
    f_116898(5);
    f_116898(7);
    f_116898(9);
    f_116898(10);
    f_116898(1);
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
}

/* @draft 0x04d648 us f_04d648
   WHAT IT DOES: clears the word at +48; if the pointer at +36 is non-null, passes it to f_04e4b4;
   then clears the pointer at +36.
   Remaining difference: 10/17 words differ, first at +0x18; size 60 vs 68. */
void f_04d648(char *self) {
    void *v = FLD(void *, self, 36);
    FLD(int, self, 48) = 0;
    if (v) {
        f_04e4b4(v);
    }
    FLD(void *, self, 36) = 0;
}

/* @implements 0x04d68c us f_04d68c
   WHAT IT DOES: calls f_0466ac on the global D_24100c when a0 is 1 and a1 is 0xffff; calls f_0466f0
   on it when a0 is 0 and a1 is 0xffff.
   Remaining difference: 2/31 words differ, first at +0x1c; size 124 vs 124. */
void f_04d68c(int a0, int a1) {
    if ((a1 == 0xffff) & (a0 == 1)) {
        f_0466ac(D_24100c);
    }
    if ((a1 == 0xffff) & (a0 == 0)) {
        f_0466f0(D_24100c);
    }
}

/* @draft 0x04d82c us f_04d82c
   WHAT IT DOES: returns the bit index of the most significant set bit of a0 (a normalising shift
   search), compared against a limit at D_291424; returns 0 for a0 == 0 and -1 when the result
   reaches the limit.
   Remaining difference: 31/31 words differ, first at +0x0; size 124 vs 120. */
int f_04d82c(int a0) {
    unsigned a2 = ((unsigned)(a0 - 256) >> 16) & 8;
    if (a0 == 0) {
        return 0;
    }
    unsigned x = (unsigned)a0 << a2;
    unsigned a1 = ((x - 4096u) >> 16) & 4;
    x <<= a1;
    unsigned v = (x - 16384u) >> 16;
    a2 += a1;
    a1 = v & 2;
    unsigned y = x << a1;
    unsigned w = (y >> 14) & ~(y >> 15);
    a2 += a1;
    int r = (int)(w - a2) + 13;
    return (r < D_291424) ? r : -1;
}

/* @draft 0x04e6d0 us f_04e6d0
   WHAT IT DOES: if the word at +8 is non-zero, runs f_04e930 on the node at +4 and relinks the
   node at +4 to itself (clears its +4 and +8 links, sets its +12 to itself); then passes the node
   at +4 to f_04e4b4.
   Remaining difference: 26/31 words differ, first at +0x10; size 88 vs 124. */
void f_04e6d0(char *s) {
    if (FLD(int, s, 8) != 0) {
        f_04e930(s, FLD(char *, FLD(char *, s, 4), 4));
        void *v = FLD(void *, s, 4);
        FLD(int, s, 8) = 0;
        *(void **)((char *)v + 8) = v;
        FLD(int, FLD(void *, s, 4), 4) = 0;
        v = FLD(void *, s, 4);
        *(void **)((char *)v + 12) = v;
    }
    f_04e4b4(FLD(void *, s, 4));
}

/* @implements 0x04e8d8 us f_04e8d8
   WHAT IT DOES: sets the vtable address D_1a3760 into the object, runs f_04e6d0 on the sub-object at
   +8 and then the base destructor f_04e8c0 on the object. */
struct Base8c0 {
    int vt, x;
    ~Base8c0() { f_04e8c0(this); }
};
struct Mem6d0 {
    ~Mem6d0() { f_04e6d0((char *)this); }
};
struct Der8d8 : Base8c0 {
    Mem6d0 m;
    ~Der8d8() { *(void **)this = D_1a3760; }
};
void f_04e8d8(char *a0) {
    GuardE g;
    ((Der8d8 *)a0)->~Der8d8();
}

/* @implements 0x04e930 us f_04e930
   WHAT IT DOES: walks a singly linked list of nodes starting at a1 (link at +8, child at +12): for each
   node recurses on its child, runs f_04ed28 on the node's +32 sub-object and frees the node with
   f_04e4b4. */
void f_04e930(void *s2, char *s1) {
    if (s1) {
        do {
            f_04e930(s2, FLD(char *, s1, 12));
            char *s0 = FLD(char *, s1, 8);
            f_04ed28(s1 + 32);
            f_04e4b4(s1);
            s1 = s0;
        } while (s1);
    }
}

/* @implements 0x04e990 us f_04e990
   WHAT IT DOES: sets the vtable address D_1a3760 into the object, runs f_04e6d0 on the sub-object at +8
   and then the base destructor f_04e8c0 on the object. */
void f_04e990(char *a0) {
    GuardE g;
    ((Der8d8 *)a0)->~Der8d8();
}

/* @draft 0x04e9e8 us f_04e9e8
   WHAT IT DOES: sets the vtable address D_1a3760, runs f_04e6d0 on the sub-object at +8, the base
   destructor f_04e8c0 on the object and then frees the object at -4 with f_04e4b4.
   Remaining difference: 1 word (the landing pad fills the _Unwind_Resume delay slot with move a0,s0; retail has a nop there and the move before). */
extern "C" void f_04e4b4_nt(void *) throw() __asm__("f_04e4b4");
void f_04e9e8(char *a0) {
    GuardE g;
    ((Der8d8 *)a0)->~Der8d8();
    f_04e4b4_nt(a0 - 4);
}

/* @draft 0x04ea4c us f_04ea4c
   WHAT IT DOES: clears the word at +4, allocates a 36-byte node, links the object's +4 and +8 to it
   and makes the node self-linked (+4 and +12 point at itself).
   Remaining difference: 13/21 words differ, first at +0x20; size 72 vs 84. */
void f_04ea4c(char *a0) {
    FLD(int, a0, 4) = 0;
    char *v0 = (char *)f_04dfa0((void *)36);
    FLD(void *, a0, 4) = v0;
    FLD(int, v0, 4) = 0;
    void *v3 = FLD(void *, a0, 4);
    FLD(int, a0, 8) = 0;
    FLD(void *, v3, 8) = v3;
    char *a = FLD(char *, a0, 4);
    *(int *)v0 = 0;
    FLD(void *, a, 12) = a;
}

/* @draft 0x04ec30 us f_04ec30
   WHAT IT DOES: sets the vtable address D_1a3810 into the object, calls f_05d6dc on the object, then
   frees the object at -4 with f_04e4b4.
   Remaining difference: 3 words of prologue scheduling (retail puts sw v0 after addiu sp, move s0,a0 before the call and addiu s0,-4 in its delay slot). */
extern "C" void f_04e4b4_nt(void *) throw() __asm__("f_04e4b4");
void f_04ec30(char *a0) {
    GuardE g;
    *(void **)a0 = D_1a3810;
    f_05d6dc(a0);
    a0 -= 4;
    f_04e4b4_nt(a0);
}

/* @draft 0x04ed28 us f_04ed28
   WHAT IT DOES: releases the reference-counted object at +4: decrements its count at +0 and, when
   it reaches zero, frees it with f_04e4b4 and calls its virtual slot 1; then clears the object's
   +0 and +4 links.
   Remaining difference: 23/30 words differ, first at +0x0; size 112 vs 120. */
void f_04ed28(char *s) {
    char *p = FLD(char *, s, 4);
    if (p) {
        int v = FLD(int, p, 0) - 1;
        FLD(int, p, 0) = v;
        if (v == 0) {
            f_04e4b4(p);
            void *a = FLD(void *, s, 0);
            if (a) {
                void **vt = *(void ***)a;
                ((void (*)(void *))vt[1])(a);
            }
        }
        FLD(void *, s, 0) = 0;
        FLD(void *, s, 4) = 0;
    }
}

/* @draft 0x04eda0 us f_04eda0
   WHAT IT DOES: walks the circular list headed at the word at +4 of the argument; for each node runs
   f_04ed28 on its +8 sub-object and frees the node with f_04e4b4; then makes the head self-linked.
   Remaining difference: 25/27 words differ, first at +0x0; size 108 vs 104. */
void f_04eda0(char *a0) {
    char *v0 = FLD(char *, a0, 4);
    char *s1 = FLD(char *, v0, 0);
    if (s1 != v0) {
        do {
            char *s0 = s1;
            char *next = FLD(char *, s1, 0);
            f_04ed28(s1 + 8);
            f_04e4b4(s0);
            s1 = next;
        } while (s1 != FLD(char *, a0, 4));
    }
    FLD(void *, v0, 4) = v0;
    *(void **)v0 = v0;
}

/* @implements 0x04ee08 us f_04ee08
   WHAT IT DOES: recursively destroys a tree of nodes (child at +12, link at +8): for each node in the
   chain it recurses on the child, runs f_04ed28 on the node's +36 sub-object and frees the node. */
void f_04ee08(char *s2, char *s1) {
    if (s1) {
        do {
            f_04ee08(s2, FLD(char *, s1, 12));
            char *s0 = FLD(char *, s1, 8);
            f_04ed28(s1 + 36);
            f_04e4b4(s1);
            s1 = s0;
        } while (s1);
    }
}

/* @implements 0x04ee68 us f_04ee68
   WHAT IT DOES: recursively destroys a chain of nodes (child at +12, link at +8): recurses on the child,
   then frees the node with f_04e4b4. */
void f_04ee68(char *s2, char *s1) {
    if (s1) {
        do {
            f_04ee68(s2, FLD(char *, s1, 12));
            char *s0 = FLD(char *, s1, 8);
            f_04e4b4(s1);
            s1 = s0;
        } while (s1);
    }
}

/* @draft 0x04f1e0 us f_04f1e0
   WHAT IT DOES: allocates a 12-byte block, stores the vtable address D_1a4480 at its +4, the size 12 at its
   +0 and clears the word at +8; returns the address of its +4 sub-object.
   Remaining difference: 12/18 words differ, first at +0x0; size 64 vs 72. */
void *f_04f1e0(void) {
    char *p = (char *)f_04dfa0((void *)12);
    char *a1 = p + 4;
    FLD(void *, p, 4) = D_1a4480;
    FLD(int, p, 0) = 12;
    FLD(int, a1, 4) = 0;
    return a1;
}

/* @draft 0x04f7ec us f_04f7ec
   WHAT IT DOES: loads a reference-counted pair through f_05e1b4 into a local, stores the pair in the
   object (incrementing the count of the second when present), releases the local with f_04ed28 and
   returns the object; a null first word clears both fields.
   Remaining difference: 20/27 words differ, first at +0x0; size 100 vs 108. */
char *f_04f7ec(char *self) {
    void *t[2];
    f_05e1b4(t);
    if (t[0]) {
        FLD(void *, self, 0) = t[0];
        FLD(void *, self, 4) = t[1];
        if (t[1]) {
            FLD(int, t[1], 0) += 1;
        }
    } else {
        FLD(void *, self, 0) = 0;
        FLD(void *, self, 4) = 0;
    }
    f_04ed28((char *)t);
    return self;
}

/* @draft 0x04fd68 us f_04fd68
   WHAT IT DOES: suspends interrupts, increments the counter at +8 of the global D_291400, resumes
   interrupts, stores the address of the global's +12 sub-object into the pointer argument and returns
   that argument.
   Remaining difference: 26/29 words differ, first at +0x0; size 84 vs 116. */
void *f_04fd68(void *a0) {
    char *s0 = (char *)D_291400;
    int st = sceKernelCpuSuspendIntr();
    FLD(int, s0, 8) += 1;
    sceKernelCpuResumeIntr(st);
    *(void **)a0 = s0 + 12;
    return a0;
}

}  // extern "C"

}  // namespace swgB

#undef FLD

/* ---- swgC ---- */
/* TU 117 fragment, retail 0x04ffc4 to 0x05c698 (swgC worker): Flash/ActionScript player
   functions in the SWG object model. Most are trivial: empty hooks, zero or constant
   getters, field getters at fixed offsets, and wrappers that pass a .rodata name string
   to a shared callee. The larger ones build small stack temporaries and call the
   list, string and property helpers. Only the functions of 128 bytes or less are transcribed so far (44 of 123 in the range). */

namespace swgC {

extern "C" {

extern const char D_1a2e88[];
extern const char D_1a2f6c[];
extern const char D_1a2f74[];
extern const char D_1a2f7c[];
extern const char D_1a2f84[];
extern const char D_1a2f8c[];
extern const char D_1a2f94[];
extern const char D_1a2f9c[];
extern const char D_1a2fa4[];
extern const char D_1a2fac[];
extern const char D_1a2fb4[];
extern const char D_1a2fbc[];
extern const char D_1a2fdc[];
extern const char D_1a2fe4[];

void f_05fce4(void *self, const char *name);
void f_0602c0(void *self, const char *name);
void f_060b14(void *self, void *arg, int flag);
void f_04e4b4(void *p);
void *f_04dfa0(void *p);
void f_061458(void *obj, void *pair);
void f_0613e8(void *out, void *obj, int *a, void *b);
void f_050018(void);
void f_05f64c(void *out, void *obj, int *a);
void f_05e394(void *out, void *obj, int *a, void *b);
void f_060c80(void *out, void *a, void *obj);
void f_05da50(void *obj);
void *f_061620(char *s, char *end, int len, int z);
unsigned int strlen(const char *s);

/* @implements 0x04ffc4 us f_04ffc4
   WHAT IT DOES: Empty hook (returns at once); the object is not used. */
void f_04ffc4(void *p)
{
    (void)p;
}

/* @implements 0x04ffcc us f_04ffcc
   WHAT IT DOES: Empty hook (returns at once); the object is not used. */
void f_04ffcc(void *p)
{
    (void)p;
}

/* @implements 0x04ffd4 us f_04ffd4
   WHAT IT DOES: Empty hook (returns at once); the object is not used. */
void f_04ffd4(void *p)
{
    (void)p;
}

/* @implements 0x04ffdc us f_04ffdc
   WHAT IT DOES: Empty hook (returns at once); the object is not used. */
void f_04ffdc(void *p)
{
    (void)p;
}

/* @implements 0x04ffe4 us f_04ffe4
   WHAT IT DOES: Empty hook (returns at once); the object is not used. */
void f_04ffe4(void *p)
{
    (void)p;
}

/* @implements 0x04ffec us f_04ffec
   WHAT IT DOES: Empty hook (returns at once); the object is not used. */
void f_04ffec(void *p)
{
    (void)p;
}

/* @implements 0x04fff4 us f_04fff4
   WHAT IT DOES: Returns 1 when the two words are equal, else 0. */
int f_04fff4(int a, int b)
{
    return a == b;
}

/* @implements 0x050000 us f_050000
   WHAT IT DOES: Returns zero; the object is not used. */
int f_050000(void *p)
{
    (void)p;
    return 0;
}

/* @implements 0x050008 us f_050008
   WHAT IT DOES: Returns zero; the object is not used. */
int f_050008(void *p)
{
    (void)p;
    return 0;
}

/* @implements 0x050010 us f_050010
   WHAT IT DOES: Returns the word at +56 of the object (a field read). */
int f_050010(int *p)
{
    return *(int *)((char *)p + 56);
}

/* @implements 0x050718 us f_050718
   WHAT IT DOES: Returns zero; the object is not used. */
int f_050718(void *p)
{
    (void)p;
    return 0;
}

/* @implements 0x050738 us f_050738
   WHAT IT DOES: Returns the constant 8; the object is not used. */
int f_050738(void *p)
{
    (void)p;
    return 8;
}

/* @implements 0x05074c us f_05074c
   WHAT IT DOES: Returns zero; the object is not used. */
int f_05074c(void *p)
{
    (void)p;
    return 0;
}

/* @implements 0x050740 us f_050740
   WHAT IT DOES: Returns the .rodata name "object" (the ActionScript type name). */
const char *f_050740(void *p)
{
    (void)p;
    return D_1a2e88;
}

/* @implements 0x05a3e0 us f_05a3e0
   WHAT IT DOES: Returns the address of the sub-object at offset 52 of the object. */
char *f_05a3e0(char *p)
{
    return p + 52;
}

/* Empty-bodied local whose destructor is inline: it makes the calls below sit in an
   EH region (the landing pad only resumes unwinding), as in retail. */
struct Guard4 {
    int w[4];
    ~Guard4() {}
};

/* @implements 0x050720 us f_050720
   WHAT IT DOES: Zeroes the two words of the object through a temporary and returns the object. */
struct Pair2 {
    int a, b;
};

void *f_050720(Pair2 *p)
{
    Pair2 t = {0, 0};
    *p = t;
    return p;
}

/* @implements 0x05a360 us f_05a360
   WHAT IT DOES: Returns the element at index i of the array held at +32 of the object
   (elements are 56 bytes). */
char *f_05a360(char *p, int i)
{
    return *(char **)(p + 32) + i * 56;
}

/* @implements 0x0502a0 us f_0502a0
   WHAT IT DOES: Calls f_050018 with no arguments. */
void f_0502a0(void)
{
    f_050018();
}

/* @implements 0x059188 us f_059188
   WHAT IT DOES: Calls f_060b14 with the object and argument, flag 1. */
void f_059188(void *p, void *arg)
{
    f_060b14(p, arg, 1);
}

/* @implements 0x0591a4 us f_0591a4
   WHAT IT DOES: Calls f_060b14 with the object and argument, flag 0. */
void f_0591a4(void *p, void *arg)
{
    f_060b14(p, arg, 0);
}

/* @implements 0x0541f8 us f_0541f8
   WHAT IT DOES: Passes the name string D_1a2f6c to f_05fce4 for this object. */
void f_0541f8(void *p)
{
    f_05fce4(p, D_1a2f6c);
}

/* @implements 0x054218 us f_054218
   WHAT IT DOES: Passes the name string D_1a2f74 to f_05fce4 for this object. */
void f_054218(void *p)
{
    f_05fce4(p, D_1a2f74);
}

/* @implements 0x054238 us f_054238
   WHAT IT DOES: Passes the name string D_1a2f7c to f_05fce4 for this object. */
void f_054238(void *p)
{
    f_05fce4(p, D_1a2f7c);
}

/* @implements 0x054258 us f_054258
   WHAT IT DOES: Passes the name string D_1a2f84 to f_05fce4 for this object. */
void f_054258(void *p)
{
    f_05fce4(p, D_1a2f84);
}

/* @implements 0x054278 us f_054278
   WHAT IT DOES: Passes the name string D_1a2f8c to f_05fce4 for this object. */
void f_054278(void *p)
{
    f_05fce4(p, D_1a2f8c);
}

/* @implements 0x054298 us f_054298
   WHAT IT DOES: Passes the name string D_1a2f94 to f_05fce4 for this object. */
void f_054298(void *p)
{
    f_05fce4(p, D_1a2f94);
}

/* @implements 0x0542b8 us f_0542b8
   WHAT IT DOES: Passes the name string D_1a2f9c to f_05fce4 for this object. */
void f_0542b8(void *p)
{
    f_05fce4(p, D_1a2f9c);
}

/* @implements 0x0542d8 us f_0542d8
   WHAT IT DOES: Passes the name string D_1a2fa4 to f_05fce4 for this object. */
void f_0542d8(void *p)
{
    f_05fce4(p, D_1a2fa4);
}

/* @implements 0x0542f8 us f_0542f8
   WHAT IT DOES: Passes the name string D_1a2fac to f_05fce4 for this object. */
void f_0542f8(void *p)
{
    f_05fce4(p, D_1a2fac);
}

/* @implements 0x054318 us f_054318
   WHAT IT DOES: Passes the name string D_1a2fb4 to f_05fce4 for this object. */
void f_054318(void *p)
{
    f_05fce4(p, D_1a2fb4);
}

/* @implements 0x054338 us f_054338
   WHAT IT DOES: Passes the name string D_1a2fbc to f_05fce4 for this object. */
void f_054338(void *p)
{
    f_05fce4(p, D_1a2fbc);
}

/* @implements 0x05504c us f_05504c
   WHAT IT DOES: Passes the name string D_1a2fdc to f_0602c0 for this object. */
void f_05504c(void *p)
{
    f_0602c0(p, D_1a2fdc);
}

/* @implements 0x05506c us f_05506c
   WHAT IT DOES: Passes the name string D_1a2fe4 to f_0602c0 for this object. */
void f_05506c(void *p)
{
    f_0602c0(p, D_1a2fe4);
}

/* @implements 0x059cb0 us f_059cb0
   WHAT IT DOES: Calls f_04e4b4 with the pointer 4 bytes below the argument. */
void f_059cb0(void *p, char *q)
{
    Guard4 g;
    (void)p;
    f_04e4b4(q - 4);
}

/* @implements 0x05a3b0 us f_05a3b0
   WHAT IT DOES: Packs the object and its argument into a two-word temporary and passes
   the temporary to f_061458 with the sub-object at +44. */
void f_05a3b0(void *p, void *q)
{
    void *tmp[2];
    tmp[0] = p;
    tmp[1] = q;
    f_061458((char *)p + 44, tmp);
}

/* @implements 0x052f4c us f_052f4c
   WHAT IT DOES: Passes the sub-object at +328 and the value chain +328 -> +4 -> +4 to
   f_05f64c, with the output buffer at sp+16.
   */
void f_052f4c(char *p)
{
    char *q = p + 328;
    int buf[4];
    int out[4];
    int b;
    int v = *(int *)(q + 4);
    buf[0] = v;
    int w = *(int *)(v + 4);
    buf[0] = w;
    b = w;
    f_05f64c(out, q, &b);
}

/* @draft 0x05a378 us f_05a378
   WHAT IT DOES: Passes the sub-object at +44, its word at +4 and the argument (by
   address) to f_0613e8 with a 16-byte output buffer.    Remaining difference: 2 words (the spill of arg at sp+32 sits before addiu a3 in retail, after it in ours); the word buffer is 16 bytes so the frame matches.
   */
void f_05a378(char *p, int arg)
{
    char *q = p + 44;
    int out[4];
    int v[4];
    v[0] = *(int *)(q + 4);
    f_0613e8(out, q, v, &arg);
}

/* @implements 0x059c74 us f_059c74
   WHAT IT DOES: Calls f_04dfa0 to allocate a block, stores the pointer 4 bytes past the
   argument at its start, and returns the block advanced by 4. */
void *f_059c74(void *p, char *q)
{
    Guard4 g;
    char *s = q + 4;
    char **r = (char **)f_04dfa0(s);
    *r = s;
    (void)p;
    return (char *)r + 4;
}

/* @implements 0x052b14 us f_052b14
   WHAT IT DOES: Passes the output buffer, obj+328, the word at obj+328+4 and the
   sub-object at obj+296+index*8 to f_05e394.    Remaining difference: argument setup order: retail sets a2 (sp+16) before a0 (sp); ours the reverse (2 of 16 words differ, first at +0x24).
   */
void f_052b14(char *p, int idx)
{
    char *q = p + 328;
    int L1[4];
    int L2[4];
    L2[0] = *(int *)(q + 4);
    f_05e394(L1, q, L2, p + 296 + idx * 8);
}

/* @implements 0x052dbc us f_052dbc
   WHAT IT DOES: Passes the chain obj+328 -> +4 -> +4 value and its advanced pointer to
   f_05e394.    Remaining difference: store/load order: retail loads the inner word before storing the outer one to sp+16; ours stores first (2 of 16 words differ, first at +0x20).
   */
void f_052dbc(char *p)
{
    char *q = p + 328;
    int L1[4];
    int L2[4];
    int x = *(int *)(q + 4);
    L1[0] = x;
    int v = *(int *)(x + 4);
    L2[0] = x;
    L1[0] = v;
    f_05e394(L1, q, L2, (char *)v + 8);
}

/* @draft 0x059848 us f_059848
   WHAT IT DOES: Reads the chain obj+44 -> +4 -> word 0, passes the value and the
   pointer to f_060c80, then calls f_05da50 on the sub-object at +44.    Remaining difference: 11 of 19 words differ, first at +0x1c: the stack layout of the chain temporaries is not matched (size 76 vs 72).
   */
void f_059848(char *p)
{
    char *s0 = p + 44;
    int out[4];
    void *x = *(void **)(*(char **)(s0 + 4));
    void *y = *(void **)x;
    out[0] = (int)y;
    f_060c80(out, &x, p);
    f_05da50(s0);
}

/* @draft 0x05a30c us f_05a30c
   WHAT IT DOES: Returns the element at index idx (44-byte records) of the array at +16 of
   the object, or null when idx is negative or not below the element count (the count is
   (end - begin) / 4 computed with a multiply by the constant 0xba2e8ba3).    Remaining difference: all 21 words differ: the constant-division count and branch order are not matched yet (size 76 vs 84).
   */
char *f_05a30c(char *p, int idx)
{
    char *r = 0;
    if (idx >= 0) {
        int begin = *(int *)(p + 12 + 4);
        int end = *(int *)(p + 12 + 8);
        int n = (end - begin) >> 2;
        if (idx < n * (int)0xba2e8ba3) {
            char *base = *(char **)(p + 16);
            r = base + idx * 44;
        }
    }
    return r;
}

/* @implements 0x05a3e8 us f_05a3e8
   WHAT IT DOES: Calls f_061620 with the string and its end (strlen, or -1 for a null
   string), the length argument and 0, and stores the result in the first word of out. */
void f_05a3e8(void *out, char *s, int len)
{
    char *end = (char *)-1;
    if (s)
        end = s + strlen(s);
    *(void **)out = f_061620(s, end, len, 0);
}

/* @draft 0x052720 us f_052720
   WHAT IT DOES: Passes the sub-object at +340 and the value chain at +340 -> +4 -> +4
   to f_05f64c, then calls virtual slot 9 of the object reached through the +340 chain
   (obj+4 -> +4 -> +8).    Remaining difference: 5 of 26 words differ, first at +0x28: the store/load order in the second half of the chain and the virtual-call setup.
   */
void f_052720(char *p)
{
    char *s0 = p + 340;
    int buf[4];
    int out[4];
    int b;
    int a = *(int *)(s0 + 4);
    buf[0] = a;
    b = *(int *)(a + 4);
    buf[0] = b;
    f_05f64c(out, s0, &b);
    int c = *(int *)(s0 + 4);
    b = c;
    int d = *(int *)(c + 4);
    void *obj = *(void **)(d + 8);
    b = d;
    void **vt = *(void ***)obj;
    ((void (*)(void *))vt[9])(obj);
}


}
}

/* ---- swgD ---- */
/* TU 117 fragment, retail 0x05c698 to 0x0624e4 (swgD worker): small Flash/ActionScript
   player functions in the SWG object model: vtable-pointer stores, getters and setters of
   object fields, deleting destructors that store a class vtable and call operator delete,
   and a few list and table helpers. Functions are in retail address order. */

void operator delete(void *);

namespace swgD {

extern "C" {

extern char D_1a4888[];
extern char D_1a4878[];
extern char D_1a4828[];
extern char D_1a47f0[];
extern char D_1a47c0[];
extern char D_1a4678[];
extern char D_1a4868[];
extern char D_1a3278[];

void f_04ed28(void *);
void f_04e4b4(void *);
extern "C" void *memset(void *, int, unsigned int);
void *f_04dfa0(unsigned);
void f_04e8c0(void *);
void f_05db84(void *);
void f_060920(void *);

/* @implements 0x05fad4 us f_05fad4
   WHAT IT DOES: Returns the word at +24 of the object (a field read). */
int f_05fad4(int *p)
{
    return p[6];
}

/* @implements 0x0602b8 us f_0602b8
   WHAT IT DOES: Returns zero; the object is not used. */
int f_0602b8(void *p)
{
    (void)p;
    return 0;
}

/* @implements 0x0604d4 us f_0604d4
   WHAT IT DOES: Empty function. */
void f_0604d4(void *p)
{
    (void)p;
}

/* @implements 0x0622a8 us f_0622a8
   WHAT IT DOES: Returns the constant 11. */
int f_0622a8(void *p)
{
    (void)p;
    return 11;
}

/* @implements 0x0622b0 us f_0622b0
   WHAT IT DOES: Returns the name string "sound". */
const char *f_0622b0(void *p)
{
    (void)p;
    return "sound";
}

/* @implements 0x05ca08 us f_05ca08
   WHAT IT DOES: Stores the vtable pointer of one class of the Flash object family into the
   object's first word. */
void f_05ca08(void **p)
{
    *(char **)p = D_1a4888;
}

/* @implements 0x05ca40 us f_05ca40
   WHAT IT DOES: Stores the vtable pointer of another class of the family into the first word. */
void f_05ca40(void **p)
{
    *(char **)p = D_1a4878;
}

/* @implements 0x05caf4 us f_05caf4
   WHAT IT DOES: Stores the vtable pointer of another class of the family into the first word. */
void f_05caf4(void **p)
{
    *(char **)p = D_1a4828;
}

/* @implements 0x05cb2c us f_05cb2c
   WHAT IT DOES: Stores the vtable pointer of another class of the family into the first word. */
void f_05cb2c(void **p)
{
    *(char **)p = D_1a47f0;
}

/* @implements 0x05cb64 us f_05cb64
   WHAT IT DOES: Stores the vtable pointer of another class of the family into the first word. */
void f_05cb64(void **p)
{
    *(char **)p = D_1a47c0;
}

/* @implements 0x05cb9c us f_05cb9c
   WHAT IT DOES: Stores the vtable pointer of another class of the family into the first word. */
void f_05cb9c(void **p)
{
    *(char **)p = D_1a4678;
}

/* @implements 0x062408 us f_062408
   WHAT IT DOES: Reads element i of the int array held at +20 of the object. */
int f_062408(int *p, int i)
{
    int *a = (int *)p[5];
    return a[i];
}

/* @implements 0x06241c us f_06241c
   WHAT IT DOES: Reads element i of the int array held at +24 of the object. */
int f_06241c(int *p, int i)
{
    int *a = (int *)p[6];
    return a[i];
}

/* @implements 0x062430 us f_062430
   WHAT IT DOES: Writes v into element i of the int array held at +20 of the object. */
void f_062430(int *p, int i, int v)
{
    int *a = (int *)p[5];
    a[i] = v;
}

/* @implements 0x05daec us f_05daec
   WHAT IT DOES: Calls f_04ed28 on the object. */
void f_05daec(void *p)
{
    f_04ed28(p);
}

/* @implements 0x05db68 us f_05db68
   WHAT IT DOES: Calls f_04ed28 on the sub-object at +16 of the object. */
void f_05db68(char *p)
{
    f_04ed28(p + 16);
}

/* @implements 0x05ca18 us f_05ca18
   WHAT IT DOES: Deleting destructor of a class of the family: stores its vtable pointer and
   frees the object with operator delete. */
void f_05ca18(void **p)
{
    *(char **)p = D_1a4888;
    operator delete(p);
}

/* @implements 0x05ca50 us f_05ca50
   WHAT IT DOES: Deleting destructor of another class of the family: stores its vtable and
   frees the object. */
void f_05ca50(void **p)
{
    *(char **)p = D_1a4878;
    operator delete(p);
}

/* @implements 0x05cb04 us f_05cb04
   WHAT IT DOES: Deleting destructor of another class of the family: stores its vtable and
   frees the object. */
void f_05cb04(void **p)
{
    *(char **)p = D_1a4828;
    operator delete(p);
}

/* @implements 0x05cb3c us f_05cb3c
   WHAT IT DOES: Deleting destructor of another class of the family: stores its vtable and
   frees the object. */
void f_05cb3c(void **p)
{
    *(char **)p = D_1a47f0;
    operator delete(p);
}

/* @implements 0x05cb74 us f_05cb74
   WHAT IT DOES: Deleting destructor of another class of the family: stores its vtable and
   frees the object. */
void f_05cb74(void **p)
{
    *(char **)p = D_1a47c0;
    operator delete(p);
}

/* @implements 0x05cbac us f_05cbac
   WHAT IT DOES: Deleting destructor of another class of the family: stores its vtable and
   frees the object. */
void f_05cbac(void **p)
{
    *(char **)p = D_1a4678;
    operator delete(p);
}

/* @implements 0x05dc90 us f_05dc90
   WHAT IT DOES: Copies the two-word link of a list node and, when the node is not empty,
   bumps the count word of the node it now points at. */
void f_05dc90(int *p, int *q)
{
    int v2 = q[0];
    int v3 = q[1];
    p[1] = v3;
    p[0] = v2;
    if (v3)
        ((int *)v3)[0]++;
}

/* @implements 0x062444 us f_062444
   WHAT IT DOES: Calls virtual slot 5 (+20) of the object held in the sub-object at +4. */
void f_062444(int *p, int a1, int a2, int a3, int a4, unsigned char a5)
{
    int *s = (int *)p[1];
    void (*fn)(int *, int, int, int, int, unsigned char) =
        (void (*)(int *, int, int, int, int, unsigned char))((int **)s)[0][5];
    fn(s, a1, a2, a3, a4, a5);
}

/* @implements 0x05f4a0 us f_05f4a0
   WHAT IT DOES: Releases the object at +4 through f_04e4b4 when that pointer is non-null. */
struct SwgDM { ~SwgDM() {} };
struct SwgD5f4a0 {
    int a;
    void *b;
    SwgDM m;
    ~SwgD5f4a0() { if (!b) return; f_04e4b4(b); }
};
void f_05f4a0(int *p)
{
    ((SwgD5f4a0 *)p)->~SwgD5f4a0();
}

/* @implements 0x0604dc us f_0604dc
   WHAT IT DOES: Releases the object at +4 through f_04e4b4 when that pointer is non-null. */
struct SwgD0604dc {
    int a;
    void *b;
    SwgDM m;
    ~SwgD0604dc() { if (!b) return; f_04e4b4(b); }
};
void f_0604dc(int *p)
{
    ((SwgD0604dc *)p)->~SwgD0604dc();
}

/* @implements 0x06050c us f_06050c
   WHAT IT DOES: Releases the object at +4 through f_04e4b4 when that pointer is non-null. */
struct SwgD06050c {
    int a;
    void *b;
    SwgDM m;
    ~SwgD06050c() { if (!b) return; f_04e4b4(b); }
};
void f_06050c(int *p)
{
    ((SwgD06050c *)p)->~SwgD06050c();
}

/* @implements 0x060670 us f_060670
   WHAT IT DOES: Releases the object at +4 through f_04e4b4 when that pointer is non-null. */
struct SwgD060670 {
    int a;
    void *b;
    SwgDM m;
    ~SwgD060670() { if (!b) return; f_04e4b4(b); }
};
void f_060670(int *p)
{
    ((SwgD060670 *)p)->~SwgD060670();
}

/* @implements 0x05ca78 us f_05ca78
   WHAT IT DOES: Sets the vtable pointer, walks the 8-byte-stride node chain from the field at +16
   up to the end at +20, then sets the vtable pointer of a related class. */
void f_05ca78(int *p)
{
    int *end = (int *)p[5];
    int *cur = (int *)p[4];
    p[0] = (int)D_1a4868;
    if (cur != end) {
        do {
            cur += 2;
        } while (cur != end);
    }
    p[0] = (int)D_1a4878;
}

/* @implements 0x0623d0 us f_0623d0
   WHAT IT DOES: Swaps the buffer pointers at +20 and +24 of the object and zeroes the buffer
   at +24 (word count at +8, four bytes each). */
void *f_0623d0(int *p)
{
    int *buf = (int *)p[6];
    int old = p[5];
    p[5] = (int)buf;
    p[6] = old;
    return memset(buf, 0, p[2] << 2);
}

/* @implements 0x0618ec us f_0618ec
   WHAT IT DOES: Copies n words from the source to the destination and returns the end of the
   destination. */
int *f_0618ec(int *d, int n, int *s)
{
    if (n != 0) {
        do {
            *d = *s;
            n--;
            d++;
        } while (n != 0);
    }
    return d;
}

/* @implements 0x0606a0 us f_0606a0
   WHAT IT DOES: Calls f_04ed28 on each 8-byte element from first up to last. */
void f_0606a0(char *first, char *last)
{
    char *p = first;
    if (p != last) {
        do {
            f_04ed28(p);
            p += 8;
        } while (p != last);
    }
}

/* @draft 0x05f1f4 us f_05f1f4
   WHAT IT DOES: Looks up the first tree node whose unsigned key at +16 is not less than the
   given key (a lower bound on the map's tree from its header). Writes the node to the result
   slot and returns the slot.    Remaining difference: retail keeps a move v0,a0 in the delay slot of the empty-tree branch and an andi on the comparison result; the body is 64 bytes against retail's 68. */
int **f_05f1f4(int **out, int **map, unsigned *key)
{
    int *y = (int *)map[1];
    int *x = (int *)y[1];
    unsigned k = *key;
    while (x) {
        unsigned char lt = (unsigned)x[4] < k;
        if (lt) {
            x = (int *)x[3];
        } else {
            y = x;
            x = (int *)x[2];
        }
    }
    *out = (int *)y;
    return out;
}

/* @draft 0x05f954 us f_05f954
   WHAT IT DOES: Same lower-bound tree lookup as f_05f1f4, with the key read from the
   pointer argument.    Remaining difference: same tree lookup as f_05f1f4: the same 4-byte shortfall and the branch layout differ. */
int **f_05f954(int **out, int **map, unsigned *key)
{
    int *y = (int *)map[1];
    int *x = (int *)y[1];
    unsigned k = *key;
    while (x) {
        unsigned char lt = (unsigned)x[4] < k;
        if (lt) {
            x = (int *)x[3];
        } else {
            y = x;
            x = (int *)x[2];
        }
    }
    *out = (int *)y;
    return out;
}

/* @implements 0x05caac us f_05caac
   WHAT IT DOES: Deleting destructor of a class of the family: sets the vtable pointer, walks
   the node chain from +16 up to +20 in 8-byte steps, sets the final vtable pointer and frees
   the object. */
void f_05caac(int *p)
{
    int *end = (int *)p[5];
    int *cur = (int *)p[4];
    p[0] = (int)D_1a4868;
    if (cur != end) {
        do {
            cur += 2;
        } while (cur != end);
    }
    p[0] = (int)D_1a4878;
    operator delete(p);
}

/* @draft 0x05daa4 us f_05daa4
   WHAT IT DOES: Constructor of a small holder object: stores the first argument in word 0, zeroes
   word 1, and when the argument is non-zero allocates a 4-byte cell holding 1 and points word 1
   at it.    Remaining difference: retail saves s0 and uses a 32-byte frame with an EH landing pad for the allocated cell; ours has no frame and no landing pad. */
void f_05daa4(int *p, int a1)
{
    p[0] = a1;
    p[1] = 0;
    if (a1) {
        int *q = (int *)f_04dfa0(4);
        *q = 1;
        p[1] = (int)q;
    }
}

/* @draft 0x05f524 us f_05f524
   WHAT IT DOES: Copies a six-word record from the source into the destination, taking the
   sixth word from the second argument, and bumps the count word of that last pointer when it
   is non-null.    Remaining difference: the loads of the source words are scheduled in a different order than retail's (t0 first, then the pointer word). */
void f_05f524(int *d, int *s, int *t)
{
    int *u = (int *)t[1];
    d[1] = s[1];
    d[0] = s[0];
    d[2] = s[2];
    d[3] = s[3];
    d[4] = t[0];
    d[5] = (int)u;
    if (u)
        u[0]++;
}

/* @implements 0x05c790 us f_05c790
   WHAT IT DOES: Links the node found at the pointer in the third argument into the list whose
   head is the node's first word, stores the result in the return slot and calls f_04e4b4 on
   that node. */
int *f_05c790(int *p, int a1, int **a2)
{
    int *x = a2[0];
    int *n = (int *)x[0];
    int *v = (int *)x[1];
    (void)a1;
    n[1] = (int)v;
    v[0] = (int)n;
    f_04e4b4(x);
    p[0] = (int)n;
    return p;
}

/* @draft 0x061c38 us f_061c38
   WHAT IT DOES: Copies the nodes of a range into a destination array, bumping the count of
   each copied node's shared pointer, and returns the end of the destination.    Remaining difference: 2 words, retail loads both words before the first store (lw v1,4 sits before sw v0,0). */
int *f_061c38(int *f, int *l, int *d)
{
    if (f != l) {
        do {
            if (d) {
                d[0] = f[0];
                int *q = (int *)f[1];
                d[1] = (int)q;
                if (q)
                    q[0]++;
            }
            f += 2;
            d += 2;
        } while (f != l);
    }
    return d;
}

/* @implements 0x06246c us f_06246c
   WHAT IT DOES: Calls virtual slot 6 of the object held in the sub-object at +4. */
void f_06246c(int *p)
{
    int *s = (int *)p[1];
    void (*fn)(int *) = (void (*)(int *))((int **)s)[0][6];
    fn(s);
}

/* @implements 0x062494 us f_062494
   WHAT IT DOES: Calls virtual slot 7 of the object held in the sub-object at +4. */
void f_062494(int *p)
{
    int *s = (int *)p[1];
    void (*fn)(int *) = (void (*)(int *))((int **)s)[0][7];
    fn(s);
}

/* @implements 0x0624bc us f_0624bc
   WHAT IT DOES: Calls virtual slot 12 of the object held in the sub-object at +4. */
void f_0624bc(int *p)
{
    int *s = (int *)p[1];
    void (*fn)(int *) = (void (*)(int *))((int **)s)[0][12];
    fn(s);
}

} /* extern "C" */

} /* namespace swgD */

/* ---- swgE ---- */
/* TU 117 fragment swgE: retail 0x0624e4 to 0x065008. ActionScript value objects (SWG):
   the Undefined, Boolean, Integer, Float, Null, String and StackPosValue classes, their
   vtables at 0x1a3f00..0x1a4480, the type-name getters, the value setters and the
   copy-and-new helpers. Each object word at 0 is the vptr; the value fields sit at +8. */

namespace swgE {

#define W(o, off) (*(int *)((char *)(o) + (off)))
#define B(o, off) (*(unsigned char *)((char *)(o) + (off)))

typedef int (*vfn_t)(void *);
typedef double (*dfn_t)(void *);

/* Link node of the sibling list (the m0 word is the list head at *a1). */
struct Lnk {
    Lnk *m0;
    Lnk *m4;
    Lnk *m8;
    Lnk *m12;
};

struct Tmp16 {
    int w[4];
    ~Tmp16() {}
};

#define DBL(o, off) (*(double *)((char *)(o) + (off)))

extern "C" {

extern char D_1a3280[];
extern char D_1a3288[];
extern char D_1a3294[];
extern char D_1a32a0[];
extern char D_1a32ac[];
extern char D_1a32c4[];
extern char D_1a32d0[];
extern char D_1a3360[];
extern char D_1a3368[];
extern char D_1a3f00[];
extern char D_1a4060[];
extern char D_1a4110[];
extern char D_1a4270[];
extern char D_1a4320[];
extern char D_1a4480[];

void f_04e8c0(void *self);
void f_05db44(void *self);
void *f_05db08(unsigned int size);
void f_164e34(long long v);
int f_164ab0(long long a, long long b);

/* @implements 0x062504 us f_062504
   WHAT IT DOES: Returns the word at +32 of the object (the element count of its array). */
int f_062504(void *o)
{
    return W(o, 32);
}

/* @implements 0x062520 us f_062520
   WHAT IT DOES: Clears the word at +32. */
void f_062520(void *o)
{
    W(o, 32) = 0;
}

/* @implements 0x062638 us f_062638
   WHAT IT DOES: Virtual type tag returning 9. */
int f_062638(void *o)
{
    return 9;
}

/* @implements 0x062fd0 us f_062fd0
   WHAT IT DOES: Virtual type tag returning 1. */
int f_062fd0(void *o)
{
    return 1;
}

/* @implements 0x063024 us f_063024
   WHAT IT DOES: Empty virtual function. */
void f_063024(void *o)
{
}

/* @implements 0x063120 us f_063120
   WHAT IT DOES: Virtual type tag returning 12. */
int f_063120(void *o)
{
    return 12;
}

/* @implements 0x063194 us f_063194
   WHAT IT DOES: Virtual type tag returning 4. */
int f_063194(void *o)
{
    return 4;
}

/* @implements 0x063238 us f_063238
   WHAT IT DOES: Returns the byte flag at +8. */
int f_063238(void *o)
{
    return B(o, 8);
}

/* @implements 0x063240 us f_063240
   WHAT IT DOES: Returns the byte flag at +8 (the same as its neighbour). */
int f_063240(void *o)
{
    return B(o, 8);
}

/* @implements 0x0634a0 us f_0634a0
   WHAT IT DOES: Virtual type tag returning 3. */
int f_0634a0(void *o)
{
    return 3;
}

/* @implements 0x06351c us f_06351c
   WHAT IT DOES: Virtual function returning 0. */
int f_06351c(void *o)
{
    return 0;
}

/* @implements 0x0638e4 us f_0638e4
   WHAT IT DOES: Virtual type tag returning 10. */
int f_0638e4(void *o)
{
    return 10;
}

/* @implements 0x063958 us f_063958
   WHAT IT DOES: Virtual type tag returning 6. */
int f_063958(void *o)
{
    return 6;
}

/* @implements 0x063e14 us f_063e14
   WHAT IT DOES: Virtual type tag returning 5. */
int f_063e14(void *o)
{
    return 5;
}

/* @implements 0x063ec4 us f_063ec4
   WHAT IT DOES: Returns the word at +8 (the integer value). */
int f_063ec4(void *o)
{
    return W(o, 8);
}

/* @implements 0x0642ac us f_0642ac
   WHAT IT DOES: Virtual type tag returning 7. */
int f_0642ac(void *o)
{
    return 7;
}

/* @implements 0x064b90 us f_064b90
   WHAT IT DOES: Virtual type tag returning 2. */
int f_064b90(void *o)
{
    return 2;
}

/* @implements 0x064c0c us f_064c0c
   WHAT IT DOES: Virtual function returning 0. */
int f_064c0c(void *o)
{
    return 0;
}

/* @implements 0x062640 us f_062640
   WHAT IT DOES: Returns the type-name string "array". */
const char *f_062640(void *o)
{
    return D_1a3280;
}

/* @implements 0x062fd8 us f_062fd8
   WHAT IT DOES: Returns the type-name string "stackpos". */
const char *f_062fd8(void *o)
{
    return D_1a3288;
}

/* @implements 0x063128 us f_063128
   WHAT IT DOES: Returns the type-name string "function". */
const char *f_063128(void *o)
{
    return D_1a32a0;
}

/* @implements 0x06319c us f_06319c
   WHAT IT DOES: Returns the type-name string "boolean". */
const char *f_06319c(void *o)
{
    return D_1a32ac;
}

/* @implements 0x0634a8 us f_0634a8
   WHAT IT DOES: Returns the type-name string "undefined". */
const char *f_0634a8(void *o)
{
    return D_1a3294;
}

/* @implements 0x0638ec us f_0638ec
   WHAT IT DOES: Returns the type-name string "movieclip". */
const char *f_0638ec(void *o)
{
    return D_1a32c4;
}

/* @implements 0x063960 us f_063960
   WHAT IT DOES: Returns the type-name string "number". */
const char *f_063960(void *o)
{
    return D_1a32d0;
}

/* @implements 0x063e1c us f_063e1c
   WHAT IT DOES: Returns the type-name string "number" (the same as f_063960). */
const char *f_063e1c(void *o)
{
    return D_1a32d0;
}

/* @implements 0x0642b4 us f_0642b4
   WHAT IT DOES: Returns the type-name string "string". */
const char *f_0642b4(void *o)
{
    return D_1a3360;
}

/* @implements 0x064b98 us f_064b98
   WHAT IT DOES: Returns the type-name string "null". */
const char *f_064b98(void *o)
{
    return D_1a3368;
}

/* @implements 0x063a68 us f_063a68
   WHAT IT DOES: Returns the 64-bit value stored at +8 (two words, +8 and +12). */
long long f_063a68(void *o)
{
    return *(long long *)((char *)o + 8);
}

/* @implements 0x063eb8 us f_063eb8
   WHAT IT DOES: Returns whether the integer at +8 is nonzero. */
int f_063eb8(void *o)
{
    return W(o, 8) != 0;
}

/* @implements 0x063ecc us f_063ecc
   WHAT IT DOES: Increments the integer at +8. */
void f_063ecc(void *o)
{
    W(o, 8)++;
}

/* @implements 0x063edc us f_063edc
   WHAT IT DOES: Decrements the integer at +8. */
void f_063edc(void *o)
{
    W(o, 8)--;
}

/* @implements 0x06250c us f_06250c
   WHAT IT DOES: Returns element i of the pointer array at +28. */
int f_06250c(void *o, int i)
{
    return ((int *)W(o, 28))[i];
}

/* @implements 0x0624e4 us f_0624e4
   WHAT IT DOES: Appends a word to the pointer array at +28 and bumps the count at +32. */
void f_0624e4(void *o, void *v)
{
    int n = W(o, 32);
    ((void **)W(o, 28))[n] = v;
    W(o, 32) = n + 1;
}

/* @implements 0x063a48 us f_063a48
   WHAT IT DOES: Passes the 64-bit value at +8 to f_164e34. */
void f_063a48(void *o)
{
    f_164e34(*(long long *)((char *)o + 8));
}

/* @implements 0x062f70 us f_062f70
   WHAT IT DOES: Destructor of the StackPosValue class: sets its vtable and runs the base destructor. */
void f_062f70(void *o)
{
    *(void **)o = D_1a3f00;
    f_04e8c0(o);
}

/* @implements 0x062f98 us f_062f98
   WHAT IT DOES: Deleting destructor of the StackPosValue class: runs the base destructor and frees the object. */
void f_062f98(void *o)
{
    *(void **)o = D_1a3f00;
    f_04e8c0(o);
    f_05db44(o);
}

/* @implements 0x063134 us f_063134
   WHAT IT DOES: Destructor of the Boolean class: sets its vtable and runs the base destructor. */
void f_063134(void *o)
{
    *(void **)o = D_1a4060;
    f_04e8c0(o);
}

/* @implements 0x06315c us f_06315c
   WHAT IT DOES: Deleting destructor of the Boolean class. */
void f_06315c(void *o)
{
    *(void **)o = D_1a4060;
    f_04e8c0(o);
    f_05db44(o);
}

/* @implements 0x063440 us f_063440
   WHAT IT DOES: Destructor of the Undefined class: sets its vtable and runs the base destructor. */
void f_063440(void *o)
{
    *(void **)o = D_1a4110;
    f_04e8c0(o);
}

/* @implements 0x063468 us f_063468
   WHAT IT DOES: Deleting destructor of the Undefined class. */
void f_063468(void *o)
{
    *(void **)o = D_1a4110;
    f_04e8c0(o);
    f_05db44(o);
}

/* @implements 0x0638f8 us f_0638f8
   WHAT IT DOES: Destructor of the Float class: sets its vtable and runs the base destructor. */
void f_0638f8(void *o)
{
    *(void **)o = D_1a4270;
    f_04e8c0(o);
}

/* @implements 0x063920 us f_063920
   WHAT IT DOES: Deleting destructor of the Float class. */
void f_063920(void *o)
{
    *(void **)o = D_1a4270;
    f_04e8c0(o);
    f_05db44(o);
}

/* @implements 0x063db4 us f_063db4
   WHAT IT DOES: Destructor of the Integer class: sets its vtable and runs the base destructor. */
void f_063db4(void *o)
{
    *(void **)o = D_1a4320;
    f_04e8c0(o);
}

/* @implements 0x063ddc us f_063ddc
   WHAT IT DOES: Deleting destructor of the Integer class. */
void f_063ddc(void *o)
{
    *(void **)o = D_1a4320;
    f_04e8c0(o);
    f_05db44(o);
}

/* @implements 0x064b30 us f_064b30
   WHAT IT DOES: Destructor of the Null class: sets its vtable and runs the base destructor. */
void f_064b30(void *o)
{
    *(void **)o = D_1a4480;
    f_04e8c0(o);
}

/* @implements 0x064b58 us f_064b58
   WHAT IT DOES: Deleting destructor of the Null class. */
void f_064b58(void *o)
{
    *(void **)o = D_1a4480;
    f_04e8c0(o);
    f_05db44(o);
}

/* @implements 0x0634b4 us f_0634b4
   WHAT IT DOES: Allocates an 8-byte Undefined object, sets its vtable and clears its second word. */
void *f_0634b4(void)
{
    void *p = f_05db08(8);
    *(void **)p = D_1a4110;
    W(p, 4) = 0;
    return p;
}

/* @implements 0x064ba4 us f_064ba4
   WHAT IT DOES: Allocates an 8-byte Null object, sets its vtable and clears its second word. */
void *f_064ba4(void)
{
    void *p = f_05db08(8);
    *(void **)p = D_1a4480;
    W(p, 4) = 0;
    return p;
}

/* @implements 0x062fe4 us f_062fe4
   WHAT IT DOES: Allocates a 12-byte StackPosValue, copies the word at +8 of the source and clears +4. */
extern "C" void *f_05db08_nt(unsigned) throw() __asm__("f_05db08");
struct G62fe4 { ~G62fe4() {} };
void *f_062fe4(void *o)
{
    G62fe4 g;
    void *p = f_05db08_nt(12);
    W(p, 8) = W(o, 8);
    *(void **)p = D_1a3f00;
    W(p, 4) = 0;
    return p;
}

/* @implements 0x0631a8 us f_0631a8
   WHAT IT DOES: Allocates a 12-byte Boolean, copies the flag byte at +8 of the source and clears +4. */
void *f_0631a8(void *o)
{
    void *p = f_05db08(12);
    B(p, 8) = B(o, 8);
    *(void **)p = D_1a4060;
    W(p, 4) = 0;
    return p;
}

/* @implements 0x063320 us f_063320
   WHAT IT DOES: Virtual call on the argument (slot 22); the flag at +8 becomes the nonzero test of its XOR with the result. */
void f_063320(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[22](a);
    B(o, 8) = (B(o, 8) ^ r) != 0;
}

/* @implements 0x063360 us f_063360
   WHAT IT DOES: Virtual call on the argument (slot 22); returns whether the flag at +8 equals its result. */
int f_063360(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[22](a);
    return B(o, 8) == r;
}

/* @implements 0x063a08 us f_063a08
   WHAT IT DOES: Passes the 64-bit value at +8 and zero to f_164ab0 and returns whether it is nonzero. */
int f_063a08(void *o)
{
    int res = 0;
    if (f_164ab0(*(long long *)((char *)o + 8), 0))
        res = 1;
    return res;
}

/* @implements 0x063e28 us f_063e28
   WHAT IT DOES: Allocates a 12-byte Integer, copies the word at +8 of the source and clears +4. */
void *f_063e28(void *o)
{
    void *p = f_05db08(12);
    W(p, 8) = W(o, 8);
    *(void **)p = D_1a4320;
    W(p, 4) = 0;
    return p;
}

/* @implements 0x063f64 us f_063f64
   WHAT IT DOES: Virtual call on the argument (slot 23); multiplies the integer at +8 by the result. */
void f_063f64(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) * r;
}

/* @implements 0x0641f8 us f_0641f8
   WHAT IT DOES: Virtual call on the argument (slot 23); returns whether the integer at +8 equals its result. */
int f_0641f8(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    return W(o, 8) == r;
}

/* @implements 0x064274 us f_064274
   WHAT IT DOES: Virtual call on the argument (slot 23); returns whether its result is less than the integer at +8. */
int f_064274(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    return r < W(o, 8);
}

/* @implements 0x063eec us f_063eec
   WHAT IT DOES: Virtual call on the argument (slot 23); adds its result to the integer at +8. */
void f_063eec(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) + r;
}

/* @implements 0x063f28 us f_063f28
   WHAT IT DOES: Virtual call on the argument (slot 23); subtracts its result from the integer at +8. */
void f_063f28(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) - r;
}

/* @implements 0x06405c us f_06405c
   WHAT IT DOES: Virtual call on the argument (slot 23); ANDs the integer at +8 with its result. */
void f_06405c(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) & r;
}

/* @implements 0x064098 us f_064098
   WHAT IT DOES: Virtual call on the argument (slot 23); ORs the integer at +8 with its result. */
void f_064098(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) | r;
}

/* @implements 0x0640d4 us f_0640d4
   WHAT IT DOES: Virtual call on the argument (slot 23); XORs the integer at +8 with its result. */
void f_0640d4(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) ^ r;
}

/* @implements 0x064110 us f_064110
   WHAT IT DOES: Virtual call on the argument (slot 23); shifts the integer at +8 left by its result. */
void f_064110(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) << r;
}

/* @implements 0x06414c us f_06414c
   WHAT IT DOES: Virtual call on the argument (slot 23); shifts the integer at +8 right (arithmetic) by its result. */
void f_06414c(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) >> r;
}

/* @implements 0x064238 us f_064238
   WHAT IT DOES: Virtual call on the argument (slot 23); returns whether the integer at +8 is less than its result. */
int f_064238(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    return W(o, 8) < r;
}


#define DBL(o, off) (*(double *)((char *)(o) + (off)))

typedef int (*vfn_t)(void *);
typedef double (*dfn_t)(void *);

extern char D_1a32b4[];
extern char D_1a32bc[];
extern char D_1a331c[];
extern char D_1a32d8[];
extern char D_1a3320[];
extern double D_1a4d18;
extern double D_1a4d20;
extern char D_1a4270[];
extern char D_1a3f00[];

void f_05a3e8(void *self, const char *s, void *tmp);
int f_15e1f0(void *a, void *b);
int f_161d88(void *a, void *b);
int f_164a28(double a, double b);
int f_164b38(double a, double b);
int f_164c48(double a, double b);
int f_15fb50(void *a, int b);
int sprintf(char *buf, const char *fmt, ...);
int iprintf(const char *fmt, ...);
double __adddf3(double a, double b);
double __subdf3(double a, double b);
double __muldf3(double a, double b);
void f_0604dc(void *self);
void f_04e8d8(void *self);
void *f_05db08(unsigned int size);

/* @implements 0x063a74 us f_063a74
   WHAT IT DOES: Adds the constant double at D_1a4d18 to the double value at +8. */
void f_063a74(void *o)
{
    DBL(o, 8) = __adddf3(DBL(o, 8), D_1a4d18);
}

/* @implements 0x063ab8 us f_063ab8
   WHAT IT DOES: Subtracts the constant double at D_1a4d20 from the double value at +8. */
void f_063ab8(void *o)
{
    DBL(o, 8) = __subdf3(DBL(o, 8), D_1a4d20);
}

/* @implements 0x063248 us f_063248
   WHAT IT DOES: Virtual call on the argument (slot 22); the flag at +8 becomes the OR of its old value and the result, as a bool. */
void f_063248(void *o, void *a)
{
    unsigned char b = B(o, 8);
    int r = ((vfn_t *)*(void **)a)[22](a);
    B(o, 8) = (b | r) != 0;
}

/* @implements 0x063290 us f_063290
   WHAT IT DOES: Virtual call on the argument (slot 22); the flag at +8 becomes the AND of its old value and the result, as a bool. */
void f_063290(void *o, void *a)
{
    unsigned char b = B(o, 8);
    int r = ((vfn_t *)*(void **)a)[22](a);
    B(o, 8) = (b & r) != 0;
}

/* @implements 0x0632d8 us f_0632d8
   WHAT IT DOES: Virtual call on the argument (slot 22); the flag at +8 becomes the OR of its old value and the result, as a bool (the same as f_063248). */
void f_0632d8(void *o, void *a)
{
    unsigned char b = B(o, 8);
    int r = ((vfn_t *)*(void **)a)[22](a);
    B(o, 8) = (b | r) != 0;
}

/* @draft 0x06396c us f_06396c
   WHAT IT DOES: Allocates a 16-byte Float, copies the two value words at +8 and +12 of the source and clears +4.
   Remaining difference: instruction order after the allocation; retail loads the source words and the vptr in a different interleaving. */
void *f_06396c(void *o)
{
    void *p = f_05db08(16);
    int a = W(o, 8);
    int b = W(o, 12);
    W(p, 8) = a;
    W(p, 12) = b;
    *(void **)p = D_1a4270;
    W(p, 4) = 0;
    return p;
}

/* @implements 0x064014 us f_064014
   WHAT IT DOES: Virtual call on the argument (slot 23); the integer at +8 becomes its remainder modulo the result. */
void f_064014(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    W(o, 8) = W(o, 8) % r;
}

/* @implements 0x064cfc us f_064cfc
   WHAT IT DOES: Moves the sibling node at +12 of this node into the position of this node in the list whose head is at *a1, and relinks its child. */
void f_064cfc(Lnk *self, Lnk **head)
{
    Lnk *n = self->m12;
    Lnk *c = n->m8;
    self->m12 = c;
    if (c)
        c->m4 = self;
    n->m4 = self->m4;
    if (self == *head) {
        *head = n;
    } else {
        Lnk *p = self->m4;
        if (self == p->m8)
            p->m8 = n;
        else
            p->m12 = n;
    }
    n->m8 = self;
    self->m4 = n;
}

/* @implements 0x064d44 us f_064d44
   WHAT IT DOES: Mirror of f_064cfc: moves the node at +8 of this node into its position in the list whose head is at *a1. */
void f_064d44(Lnk *self, Lnk **head)
{
    Lnk *n = self->m8;
    Lnk *c = n->m12;
    self->m8 = c;
    if (c)
        c->m4 = self;
    n->m4 = self->m4;
    if (self == *head) {
        *head = n;
    } else {
        Lnk *p = self->m4;
        if (self == p->m12)
            p->m12 = n;
        else
            p->m8 = n;
    }
    n->m12 = self;
    self->m4 = n;
}

/* @implements 0x0633a0 us f_0633a0
   WHAT IT DOES: If the flag at +8 is clear, asks the argument (slot 22) and returns 1 when it is nonzero; otherwise returns 0. */
int f_0633a0(void *o, void *a)
{
    int res = 0;
    if (B(o, 8) == 0) {
        if (((vfn_t *)*(void **)a)[22](a))
            res = 1;
    }
    return res;
}

/* @implements 0x0633f0 us f_0633f0
   WHAT IT DOES: If the flag at +8 is set, asks the argument (slot 22) and returns 1 when it returns zero; otherwise returns 0. */
int f_0633f0(void *o, void *a)
{
    int res = 0;
    if (B(o, 8) != 0) {
        if (!((vfn_t *)*(void **)a)[22](a))
            res = 1;
    }
    return res;
}

/* @implements 0x063afc us f_063afc
   WHAT IT DOES: Adds the double returned by the argument (slot 24) to the double value at +8. */
void f_063afc(void *o, void *a)
{
    double r = ((dfn_t *)*(void **)a)[24](a);
    DBL(o, 8) = __adddf3(DBL(o, 8), r);
}

/* @implements 0x063b4c us f_063b4c
   WHAT IT DOES: Subtracts the double returned by the argument (slot 24) from the double value at +8. */
void f_063b4c(void *o, void *a)
{
    double r = ((dfn_t *)*(void **)a)[24](a);
    DBL(o, 8) = __subdf3(DBL(o, 8), r);
}

/* @implements 0x063b9c us f_063b9c
   WHAT IT DOES: Multiplies the double value at +8 by the double returned by the argument (slot 24). */
void f_063b9c(void *o, void *a)
{
    double r = ((dfn_t *)*(void **)a)[24](a);
    DBL(o, 8) = __muldf3(DBL(o, 8), r);
}

/* @implements 0x063ca0 us f_063ca0
   WHAT IT DOES: Returns 1 when the double at +8 equals the double returned by the argument (slot 24). */
int f_063ca0(void *o, void *a)
{
    int res = 0;
    double r = ((dfn_t *)*(void **)a)[24](a);
    if (f_164a28(DBL(o, 8), r) == 0)
        res = 1;
    return res;
}

/* @implements 0x063cfc us f_063cfc
   WHAT IT DOES: Returns 1 when the double at +8 is less than the double returned by the argument (slot 24). */
int f_063cfc(void *o, void *a)
{
    int res = 0;
    double r = ((dfn_t *)*(void **)a)[24](a);
    if (f_164c48(DBL(o, 8), r) < 0)
        res = 1;
    return res;
}

/* @implements 0x063d58 us f_063d58
   WHAT IT DOES: Returns 1 when the double at +8 is greater than the double returned by the argument (slot 24). */
int f_063d58(void *o, void *a)
{
    int res = 0;
    double r = ((dfn_t *)*(void **)a)[24](a);
    if (f_164b38(DBL(o, 8), r) > 0)
        res = 1;
    return res;
}

/* @implements 0x063524 us f_063524
   WHAT IT DOES: Returns whether the argument and this object give the same value for the slot-6 query. */
int f_063524(void *o, void *a)
{
    int ra = ((vfn_t *)*(void **)a)[6](a);
    int rt = ((vfn_t *)*(void **)o)[6](o);
    return ra == rt;
}

/* @implements 0x064c14 us f_064c14
   WHAT IT DOES: Same as f_063524: returns whether the argument and this object give the same slot-6 result. */
int f_064c14(void *o, void *a)
{
    int ra = ((vfn_t *)*(void **)a)[6](a);
    int rt = ((vfn_t *)*(void **)o)[6](o);
    return ra == rt;
}

/* @implements 0x0639b4 us f_0639b4
   WHAT IT DOES: Formats the double value at +8 of the argument with "%g" and sets this object from the string. */
void *f_0639b4(void *o, void *a)
{
    char buf[32];
    Tmp16 t;
    sprintf(buf, D_1a32d8, DBL(a, 8));
    f_05a3e8(o, buf, &t);
    return o;
}

/* @implements 0x063e68 us f_063e68
   WHAT IT DOES: Formats the integer at +8 of the argument with "%d" and sets this object from the string. */
void *f_063e68(void *o, void *a)
{
    char buf[32];
    Tmp16 t;
    sprintf(buf, D_1a331c, W(a, 8));
    f_05a3e8(o, buf, &t);
    return o;
}

/* @implements 0x063fa4 us f_063fa4
   WHAT IT DOES: Integer division of the value at +8 by the argument (slot 23); a zero divisor prints a warning and sets 0x7fffffff. */
void f_063fa4(void *o, void *a)
{
    int r = ((vfn_t *)*(void **)a)[23](a);
    if (r == 0) {
        iprintf(D_1a3320, W(o, 8));
        W(o, 8) = 0x7fffffff;
    } else {
        W(o, 8) = W(o, 8) / r;
    }
}





/* @implements 0x06302c us f_06302c
   WHAT IT DOES: Sets this object from the string "undefined" through f_05a3e8, with a temporary whose destructor is empty, and returns the object. */
void *f_06302c(void *o)
{
    Tmp16 t;
    f_05a3e8(o, D_1a3294, &t);
    return o;
}

/* @implements 0x0634e0 us f_0634e0
   WHAT IT DOES: Sets this object from the string "undefined" through f_05a3e8 (the same as f_06302c) and returns the object. */
void *f_0634e0(void *o)
{
    Tmp16 t;
    f_05a3e8(o, D_1a3294, &t);
    return o;
}

/* @implements 0x064bd0 us f_064bd0
   WHAT IT DOES: Sets this object from the string "null" through f_05a3e8 and returns the object. */
void *f_064bd0(void *o)
{
    Tmp16 t;
    f_05a3e8(o, D_1a3368, &t);
    return o;
}

}  /* extern "C" */

}  /* namespace swgE */

/* ---- swgF ---- */
/* TU 117 fragment swgF: retail 0x065008..0x06b6fc (Flash/ActionScript player, SWG).
   Covers the small helpers and wrappers in that range: fill and copy loops, the
   reference-counted node link helpers, the AS object constructor wrappers that
   forward a constant tag, and the node allocators. */

namespace swgF {

extern "C" {
void *f_15f754(void *);
void *f_15f6f8(void *);
void *f_15f798(void *);
void *f_15f6dc(void *);
void *f_15fb50(void *, unsigned);
void f_05e394(void *, void *, void *, void *);
void f_05df24(void *, void *);
extern char D_1a4320;
extern char D_1a4270;
extern unsigned D_1a4d38;
extern unsigned D_1a4d3c;
extern unsigned D_1a4d40;
extern unsigned D_1a4d44;
extern unsigned D_1a4d58;
extern unsigned D_1a4d5c;
extern unsigned D_1a4d60;
extern unsigned D_1a4d64;
extern unsigned D_1a4d70;
extern unsigned D_1a4d74;
extern unsigned D_1a4d78;
extern unsigned D_1a4d7c;
extern unsigned D_1a4d48;
extern unsigned D_1a4d4c;
extern unsigned D_1a4d50;
extern unsigned D_1a4d54;
extern char D_1d2ec8;
extern char D_1d2f00;
extern char D_1d3018;
void f_05e4a8(void *, void *);
void *f_04dfa0(unsigned n);
void f_0698e4(void *self, void *a1, void *a2, unsigned tag);
void *f_05db08(unsigned n);
void f_05daa4(void *self, void *a1);
void f_069ea0(void *a0, void *a1);
void *f_061620(void *a0, void *a1, void *a2, void *a3);
void f_04e4b4(void *self);
void _Unwind_Resume(void *e);
}

/* @implements 0x06547c us f_06547c
   WHAT IT DOES: fills n consecutive words at dst with the word at src and returns the advanced destination pointer. */
extern "C" unsigned *f_06547c(unsigned *dst, unsigned n, const unsigned *src) {
    while (n != 0) {
        *dst = *src;
        dst++;
        n--;
    }
    return dst;
}

/* @draft 0x06544c us f_06544c
   Remaining difference: the retail copy keeps the running destination in a stack slot (stored at entry and exit) and the loop has a 48-byte shape; this body is 36 bytes.
   WHAT IT DOES: copies the words from src into the range [first, last) with a running pointer kept in a stack slot. */
extern "C" void f_06544c(unsigned *first, unsigned *last, const unsigned *src) {
    unsigned *cur = first;
    if (first == last) {
        return;
    }
    do {
        *cur = *src;
        cur++;
    } while (cur != last);
}

/* @implements 0x0698b8 us f_0698b8
   WHAT IT DOES: forwards to the shared constructor helper with tag 0 and returns the object pointer. */
extern "C" void *f_0698b8(void *self, void *a1, void *a2) {
    f_0698e4(self, a1, a2, 0);
    return self;
}

/* @implements 0x069a20 us f_069a20
   WHAT IT DOES: forwards to the shared constructor helper with tag 1 and returns the object pointer. */
extern "C" void *f_069a20(void *self, void *a1, void *a2) {
    f_0698e4(self, a1, a2, 1);
    return self;
}

/* @implements 0x069a4c us f_069a4c
   WHAT IT DOES: forwards to the shared constructor helper with tag 2 and returns the object pointer. */
extern "C" void *f_069a4c(void *self, void *a1, void *a2) {
    f_0698e4(self, a1, a2, 2);
    return self;
}

/* @implements 0x069a78 us f_069a78
   WHAT IT DOES: forwards to the shared constructor helper with tag 3 and returns the object pointer. */
extern "C" void *f_069a78(void *self, void *a1, void *a2) {
    f_0698e4(self, a1, a2, 3);
    return self;
}

/* @implements 0x069aa4 us f_069aa4
   WHAT IT DOES: forwards to the shared constructor helper with tag 4 and returns the object pointer. */
extern "C" void *f_069aa4(void *self, void *a1, void *a2) {
    f_0698e4(self, a1, a2, 4);
    return self;
}

/* @draft 0x0655a4 us f_0655a4
   Remaining difference: retail returns through a restored frame of 56 bytes with the ra reload scheduled after the null test; this body is 60 bytes.
   WHAT IT DOES: allocates a 12-byte node and, when the node is non-null, stores the first word of the source at its third word. Returns nothing. */
extern "C" void f_0655a4(void *unused, unsigned *src) {
    unsigned *node = (unsigned *)f_04dfa0(12);
    if (node + 2 != 0) {
        node[2] = *src;
    }
}

/* @implements 0x065634 us f_065634
   WHAT IT DOES: calls f_061620 with the arguments rotated one slot and a zero fourth argument, then stores the result word at offset 0 of the object. */
extern "C" void f_065634(void **self, void *a1, void *a2, void *a3) {
    *self = f_061620(a1, a2, a3, 0);
}

/* @draft 0x065a5c us f_065a5c
   Remaining difference: retail tests the count before the loop and the loop is 68 bytes; this loop body is 64 bytes and the order of the reference-count update differs.
   WHAT IT DOES: copies n two-word entries from src to dst, skipping the stores when the destination entry is null, and bumps the reference count word of each non-null second word. Returns the advanced destination. */
extern "C" unsigned *f_065a5c(unsigned *dst, unsigned n, const unsigned *src) {
    if (n == 0) {
        return dst;
    }
    do {
        if (dst != 0) {
            unsigned a = src[0];
            unsigned b = src[1];
            dst[0] = a;
            dst[1] = b;
            if (b != 0) {
                (*(unsigned *)b)++;
            }
        }
        n--;
        dst += 2;
    } while (n != 0);
    return dst;
}

/* @draft 0x065aec us f_065aec
   Remaining difference: same as f_065a5c: the retail loop is 68 bytes; this loop body is 64 bytes.
   WHAT IT DOES: copies n two-word entries from src to dst, skipping the stores when the destination entry is null, and bumps the reference count word of each non-null second word. Returns the advanced destination. */
extern "C" unsigned *f_065aec(unsigned *dst, unsigned n, const unsigned *src) {
    if (n == 0) {
        return dst;
    }
    do {
        if (dst != 0) {
            unsigned a = src[0];
            unsigned b = src[1];
            dst[0] = a;
            dst[1] = b;
            if (b != 0) {
                (*(unsigned *)b)++;
            }
        }
        n--;
        dst += 2;
    } while (n != 0);
    return dst;
}

/* @draft 0x065008 us f_065008
   Remaining difference: retail stores the source pair in the other order and reloads the second word; the body is 88 bytes against 92.
   WHAT IT DOES: allocates a 16-byte node, copies the two-word pair from the source into the node at offset 8 and bumps the reference count when the second word is non-null. Returns the node. */
extern "C" void *f_065008(void *unused, unsigned *src) {
    unsigned *node = (unsigned *)f_04dfa0(16);
    unsigned *p = node + 2;
    if (p != 0) {
        unsigned b = src[1];
        p[1] = b;
        node[2] = src[0];
        if (b != 0) {
            (*(unsigned *)b)++;
        }
    }
    return node;
}

/* @draft 0x066fe0 us f_066fe0
   Remaining difference: retail keeps the sub-object pointer in a register and stores the pair through it; the store offsets are the same but the schedule is 68 bytes against 64.
   WHAT IT DOES: allocates a 24-byte node and, when the node's sub-pair slot is non-null, copies the two-word source pair into it at offset 16. Returns the node. */
extern "C" void *f_066fe0(void *unused, unsigned *src) {
    unsigned *node = (unsigned *)f_04dfa0(24);
    unsigned *p = node + 4;
    if (p != 0) {
        node[4] = src[0];
        p[1] = src[1];
    }
    return node;
}

/* @implements 0x069e5c us f_069e5c
   WHAT IT DOES: calls f_069ea0 with the two sub-object fields of the source object (the field at +40 offset by 364, and the field at +52) and then clears the reference-count link of this object through f_05daa4. Returns this. */
extern "C" void *f_069e5c(void *self, unsigned *obj) {
    f_069ea0((void *)(obj[10] + 364), (void *)obj[13]);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x0687b8 us f_0687b8
   WHAT IT DOES: calls virtual slot 9 on the object held at +44 of the source, passes the result to f_15f754, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_0687b8(void *self, unsigned *obj) {
    void *v = (void *)obj[11];
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    f_15f754(r);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x068898 us f_068898
   WHAT IT DOES: calls virtual slot 9 on the object held at +44 of the source, passes the result to f_15f6f8, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_068898(void *self, unsigned *obj) {
    void *v = (void *)obj[11];
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    f_15f6f8(r);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x0688e8 us f_0688e8
   WHAT IT DOES: calls virtual slot 9 on the object held at +44 of the source, passes the result to f_15f798, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_0688e8(void *self, unsigned *obj) {
    void *v = (void *)obj[11];
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    f_15f798(r);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x068ab8 us f_068ab8
   WHAT IT DOES: calls virtual slot 9 on the object held at +44 of the source, passes the result to f_15f6dc, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_068ab8(void *self, unsigned *obj) {
    void *v = (void *)obj[11];
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    f_15f6dc(r);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x068938 us f_068938
   WHAT IT DOES: calls virtual slot 9 on the object held at +44 of the source, passes the result to f_15fb50 with a flag of 1, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_068938(void *self, unsigned *obj) {
    void *v = (void *)obj[11];
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    f_15fb50(r, 1);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x067e14 us f_067e14
   Remaining difference: the retail landing pad (jal _Unwind_Resume after the body) is not emitted.
   Remaining difference: the retail landing pad (jal _Unwind_Resume after the body) is not emitted.
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320, zeroes its two words after the vtable and hands it to f_05daa4 together with this. Returns this. */
struct SwgFM { ~SwgFM() {} };
struct SwgFC {
    SwgFM m;
    SwgFC() {
        unsigned *n = (unsigned *)f_05db08(12);
        n[0] = (unsigned)&D_1a4320;
        n[1] = 0;
        n[2] = 0;
        f_05daa4(this, n);
    }
};
inline void *operator new(unsigned, void *p) { return p; }

extern "C" void *f_067e14(void *self) {
    new (self) SwgFC;
    return self;
}

/* @implements 0x067e68 us f_067e68
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320, zeroes its two words after the vtable and hands it to f_05daa4 together with this. Returns this. */
struct SwgFC067e68 {
    SwgFM m;
    SwgFC067e68() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[1] = 0;
    n[2] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_067e68(void *self) {
    new (self) SwgFC067e68;
    return self;
}

/* @implements 0x069ad0 us f_069ad0
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320 and tag 38 in its third word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069ad0 {
    SwgFM m;
    SwgFC069ad0() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[2] = 38;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069ad0(void *self) {
    new (self) SwgFC069ad0;
    return self;
}

/* @implements 0x069b28 us f_069b28
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320 and tag 40 in its third word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069b28 {
    SwgFM m;
    SwgFC069b28() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[2] = 40;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069b28(void *self) {
    new (self) SwgFC069b28;
    return self;
}

/* @implements 0x069b80 us f_069b80
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320 and tag 39 in its third word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069b80 {
    SwgFM m;
    SwgFC069b80() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[2] = 39;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069b80(void *self) {
    new (self) SwgFC069b80;
    return self;
}

/* @implements 0x069bd8 us f_069bd8
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320 and tag 37 in its third word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069bd8 {
    SwgFM m;
    SwgFC069bd8() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[2] = 37;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069bd8(void *self) {
    new (self) SwgFC069bd8;
    return self;
}

/* @implements 0x069c30 us f_069c30
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320 and tag 32 in its third word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069c30 {
    SwgFM m;
    SwgFC069c30() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[2] = 32;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069c30(void *self) {
    new (self) SwgFC069c30;
    return self;
}

/* @implements 0x069c88 us f_069c88
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320 and tag 8 in its third word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069c88 {
    SwgFM m;
    SwgFC069c88() {
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)&D_1a4320;
    n[2] = 8;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069c88(void *self) {
    new (self) SwgFC069c88;
    return self;
}

/* @draft 0x069ce0 us f_069ce0
   WHAT IT DOES: allocates a 12-byte object with the rodata vtable at D_1a4320, takes the byte at offset 328 of the object held at +56 of the source as its tag word, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC069ce0 {
    SwgFM m;
    SwgFC069ce0(unsigned *obj) {
    unsigned *n = (unsigned *)f_05db08(12);
    unsigned char *src = (unsigned char *)obj[14];
    n[0] = (unsigned)&D_1a4320;
    n[2] = (unsigned)(int)(signed char)src[328];
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_069ce0(void *self, unsigned *obj) {
    new (self) SwgFC069ce0(obj);
    return self;
}

/* @implements 0x069e08 us f_069e08
   WHAT IT DOES: calls f_05e394 with two stack temporaries, the first receiving the sub-object at +40 offset by 364 and the second holding that sub-object's second word, and the object's field at +52, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_069e08(void *self, unsigned *obj) {
    unsigned L1[4];
    unsigned L2[4];
    unsigned *sub = (unsigned *)(obj[10] + 364);
    L2[0] = sub[1];
    f_05e394(L1, sub, L2, (void *)obj[13]);
    f_05daa4(self, 0);
    return self;
}

/* @draft 0x06a534 us f_06a534
   WHAT IT DOES: allocates a 16-byte object with the rodata vtable at D_1a4270 and the two words of the rodata globals D_1a4d38 and D_1a4d3c after it, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC06a534 {
    SwgFM m;
    SwgFC06a534() {
        unsigned *n = (unsigned *)f_05db08(16);
        unsigned y = D_1a4d3c;
        unsigned x = D_1a4d38;
        n[0] = (unsigned)&D_1a4270;
        n[2] = x;
        n[3] = y;
        n[1] = 0;
        f_05daa4(this, n);
    }
};
extern "C" void *f_06a534(void *self) {
    new (self) SwgFC06a534;
    return self;
}

/* @draft 0x06a7b8 us f_06a7b8
   WHAT IT DOES: allocates a 16-byte object with the rodata vtable at D_1a4270 and the two words of the rodata globals D_1a4d40 and D_1a4d44 after it, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC06a7b8 {
    SwgFM m;
    SwgFC06a7b8() {
    unsigned *n = (unsigned *)f_05db08(16);
    n[0] = (unsigned)&D_1a4270;
    n[2] = D_1a4d40;
    n[3] = D_1a4d44;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_06a7b8(void *self) {
    new (self) SwgFC06a7b8;
    return self;
}

/* @draft 0x06a8f0 us f_06a8f0
   WHAT IT DOES: allocates a 16-byte object with the rodata vtable at D_1a4270 and the two words of the rodata globals D_1a4d58 and D_1a4d5c after it, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC06a8f0 {
    SwgFM m;
    SwgFC06a8f0() {
    unsigned *n = (unsigned *)f_05db08(16);
    n[0] = (unsigned)&D_1a4270;
    n[2] = D_1a4d58;
    n[3] = D_1a4d5c;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_06a8f0(void *self) {
    new (self) SwgFC06a8f0;
    return self;
}

/* @draft 0x06aa50 us f_06aa50
   WHAT IT DOES: allocates a 16-byte object with the rodata vtable at D_1a4270 and the two words of the rodata globals D_1a4d60 and D_1a4d64 after it, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC06aa50 {
    SwgFM m;
    SwgFC06aa50() {
    unsigned *n = (unsigned *)f_05db08(16);
    n[0] = (unsigned)&D_1a4270;
    n[2] = D_1a4d60;
    n[3] = D_1a4d64;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_06aa50(void *self) {
    new (self) SwgFC06aa50;
    return self;
}

/* @draft 0x06aecc us f_06aecc
   WHAT IT DOES: allocates a 16-byte object with the rodata vtable at D_1a4270 and the two words of the rodata globals D_1a4d70 and D_1a4d74 after it, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC06aecc {
    SwgFM m;
    SwgFC06aecc() {
    unsigned *n = (unsigned *)f_05db08(16);
    n[0] = (unsigned)&D_1a4270;
    n[2] = D_1a4d70;
    n[3] = D_1a4d74;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_06aecc(void *self) {
    new (self) SwgFC06aecc;
    return self;
}

/* @draft 0x06af34 us f_06af34
   WHAT IT DOES: allocates a 16-byte object with the rodata vtable at D_1a4270 and the two words of the rodata globals D_1a4d78 and D_1a4d7c after it, hands it to f_05daa4 together with this, and returns this. */
struct SwgFC06af34 {
    SwgFM m;
    SwgFC06af34() {
    unsigned *n = (unsigned *)f_05db08(16);
    n[0] = (unsigned)&D_1a4270;
    n[2] = D_1a4d78;
    n[3] = D_1a4d7c;
    n[1] = 0;
    f_05daa4(this, n);
    
    }
};
extern "C" void *f_06af34(void *self) {
    new (self) SwgFC06af34;
    return self;
}

/* @draft 0x066e94 us f_066e94
   Remaining difference: retail wraps the sub-object call in a try block with a catch that calls f_04e4b4 and rethrows; this body has no EH region (80 bytes against 112).
   Remaining difference: the retail landing pad (catch, call f_04e4b4, rethrow) is not emitted; the body is the same.
   WHAT IT DOES: allocates a 20-byte node, and when its sub-object at offset 16 is non-null, calls f_05e4a8 on that sub-object with the source argument. Returns the node. */
extern "C" void *f_066e94(void *unused, void *a1) {
    unsigned *n = (unsigned *)f_04dfa0(20);
    unsigned *p = n + 4;
    if (p != 0) {
        f_05e4a8(p, a1);
    }
    return n;
}

/* @draft 0x066e1c us f_066e1c
   Remaining difference: retail copies the six source words in its own register order; this body is 124 bytes against 120.
   WHAT IT DOES: allocates a 40-byte node and, when its sub-object at offset 16 is non-null, copies the source's first five words and a sixth pointer into it, bumping that pointer's reference count when non-null. Returns the node. */
extern "C" void *f_066e1c(void *unused, unsigned *src) {
    unsigned *n = (unsigned *)f_04dfa0(40);
    unsigned *p = n + 4;
    if (p != 0) {
        unsigned w5 = src[5];
        p[1] = src[1];
        n[4] = src[0];
        n[6] = src[2];
        n[7] = src[3];
        n[8] = src[4];
        n[9] = w5;
        if (w5 != 0) {
            (*(unsigned *)w5)++;
        }
    }
    return n;
}

/* @implements 0x0672b0 us f_0672b0
   WHAT IT DOES: when the object at +228 of the source's child is non-null, calls its virtual slot 23 on the object at +52 and passes that result to its virtual slot 6, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_0672b0(void *self, unsigned *obj) {
    unsigned *s = (unsigned *)((unsigned *)obj[14])[57];
    if (s != 0) {
        void *o = (void *)((unsigned *)obj[13])[0];
        void *r = ((void *(*)(void *))((void **)*(void **)o)[23])(o);
        ((void (*)(void *, void *))((void **)*(void **)s)[6])(s, r);
    }
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x067320 us f_067320
   WHAT IT DOES: when the object at +228 of the source's child is non-null, calls its virtual slot 23 on the object at +52 and passes that result to its virtual slot 8, then clears this object's link through f_05daa4. Returns this. */
extern "C" void *f_067320(void *self, unsigned *obj) {
    unsigned *s = (unsigned *)((unsigned *)obj[14])[57];
    if (s != 0) {
        void *o = (void *)((unsigned *)obj[13])[0];
        void *r = ((void *(*)(void *))((void **)*(void **)o)[23])(o);
        ((void (*)(void *, void *))((void **)*(void **)s)[8])(s, r);
    }
    f_05daa4(self, 0);
    return self;
}
/* @draft 0x065aa0 us f_065aa0
   Remaining difference: retail keeps the loop cursor and the next pointer in two registers (two moves per iteration) and the body is 76 bytes; this body is 72 bytes with one register.
   WHAT IT DOES: copies the two-word entries from [first, last) to dst, bumping the reference count of each non-null second word; returns the advanced dst. */
struct SwgFPair {
    unsigned w0;
    unsigned *w1;
};

extern "C" SwgFPair *f_065aa0(SwgFPair *first, SwgFPair *last, SwgFPair *dst) {
    if (first == last) {
        return dst;
    }
    SwgFPair *cur = first;
    do {
        if (dst != 0) {
            dst->w0 = cur->w0;
            dst->w1 = cur->w1;
            if (cur->w1 != 0) {
                *cur->w1 = *cur->w1 + 1;
            }
        }
        cur++;
        dst++;
    } while (cur != last);
    return dst;
}

/* @implements 0x0655dc us f_0655dc
   WHAT IT DOES: walks a singly linked list of nodes (next at +8, child at +12), recursing into each child and then releasing the node through f_04e4b4. */
extern "C" void f_0655dc(void *self, unsigned *node) {
    while (node != 0) {
        f_0655dc(self, (unsigned *)node[3]);
        unsigned *next = (unsigned *)node[2];
        f_04e4b4(node);
        node = next;
    }
}

/* @draft 0x066f04 us f_066f04
   Remaining difference: not yet compared word by word.
   WHAT IT DOES: allocates a 36-byte record and, when the record's inner pointer is not null, copies five words from the source record into its words 4 through 8. */
extern "C" void f_066f04(void *unused, unsigned *src) {
    (void)unused;
    unsigned *q = (unsigned *)((char *)f_04dfa0(36) + 16);
    if (q != 0) {
        q[4] = src[4];
        q[3] = src[3];
        q[0] = src[0];
        q[1] = src[1];
        q[2] = src[2];
    }
}
/* @draft 0x0659fc us f_0659fc
   Remaining difference: the retail loop keeps the cursor in v0 across iterations and only spills it around the call; this volatile cursor reloads it at the loop head and the prologue order differs.
   WHAT IT DOES: calls f_05df24 on every 8-byte element from first up to last, passing the arg each time, and returns last. */
extern "C" void *f_0659fc(void *first, void *last, void *arg) {
    void *volatile cur = first;
    while (cur != last) {
        f_05df24(cur, arg);
        cur = (void *)((char *)cur + 8);
    }
    return cur;
}

/* @draft 0x06a820 us f_06a820
   Remaining difference: the 8-byte _Unwind_Resume landing pad (the cleanup for the 16-byte record) is not modelled, and the compiler picks a different register for the first rodata word (a0 where retail uses a2).
   WHAT IT DOES: allocates a 16-byte record, stores the vtable at word 0 and two rodata words at words 2 and 3, clears word 1, and hands it to f_05daa4 together with self; returns self. */
extern "C" void *f_06a820(void *self) {
    unsigned *n = (unsigned *)f_05db08(16);
    unsigned w2 = D_1a4d48;
    unsigned w3 = D_1a4d4c;
    n[0] = (unsigned)&D_1a4270;
    n[2] = w2;
    n[3] = w3;
    n[1] = 0;
    f_05daa4(self, n);
    return self;
}

/* @draft 0x06a888 us f_06a888
   Remaining difference: the 8-byte _Unwind_Resume landing pad (the cleanup for the 16-byte record) is not modelled, and the compiler picks a different register for the first rodata word (a0 where retail uses a2).
   WHAT IT DOES: allocates a 16-byte record, stores the vtable at word 0 and two rodata words at words 2 and 3, clears word 1, and hands it to f_05daa4 together with self; returns self. */
extern "C" void *f_06a888(void *self) {
    unsigned *n = (unsigned *)f_05db08(16);
    unsigned w2 = D_1a4d50;
    unsigned w3 = D_1a4d54;
    n[0] = (unsigned)&D_1a4270;
    n[2] = w2;
    n[3] = w3;
    n[1] = 0;
    f_05daa4(self, n);
    return self;
}
/* @draft 0x065d94 us f_065d94
   Remaining difference: not yet compared word by word.
   WHAT IT DOES: looks up the pointer-to-member entry in table D_1d2ec8 at the index in desc+12, applies its this-adjustment to obj, dispatches through the pointer directly or through the vtable when the adjustment's low bit is set, and returns self. */
extern "C" void *f_065d94(void *self, unsigned char *obj, void *a2, unsigned *desc) {
    unsigned *e = (unsigned *)((char *)&D_1d2ec8 + desc[3] * 8);
    unsigned adj = e[1];
    unsigned ptr = e[0];
    volatile unsigned adjSlot = adj;
    unsigned char *thisp = obj + ((int)adj >> 1);
    void *fn;
    if ((*(volatile unsigned char *)&adjSlot & 1) != 0) {
        unsigned *vt = *(unsigned **)thisp;
        fn = *(void **)((char *)vt + ptr);
    } else {
        fn = (void *)ptr;
    }
    ((void (*)(void *, void *, void *, void *))fn)(self, thisp, a2, thisp);
    return self;
}

/* @draft 0x0663f0 us f_0663f0
   Remaining difference: not yet compared word by word.
   WHAT IT DOES: looks up the pointer-to-member entry in table D_1d2f00 at the index in desc+12, applies its this-adjustment to obj, dispatches through the pointer directly or through the vtable when the adjustment's low bit is set, and returns self. */
extern "C" void *f_0663f0(void *self, unsigned char *obj, void *a2, unsigned *desc) {
    unsigned *e = (unsigned *)((char *)&D_1d2f00 + desc[3] * 8);
    unsigned adj = e[1];
    unsigned ptr = e[0];
    volatile unsigned adjSlot = adj;
    unsigned char *thisp = obj + ((int)adj >> 1);
    void *fn;
    if ((*(volatile unsigned char *)&adjSlot & 1) != 0) {
        unsigned *vt = *(unsigned **)thisp;
        fn = *(void **)((char *)vt + ptr);
    } else {
        fn = (void *)ptr;
    }
    ((void (*)(void *, void *, void *, void *))fn)(self, thisp, a2, thisp);
    return self;
}

/* @draft 0x066728 us f_066728
   Remaining difference: not yet compared word by word.
   WHAT IT DOES: looks up the pointer-to-member entry in table D_1d3018 at the index in desc+12, applies its this-adjustment to obj, dispatches through the pointer directly or through the vtable when the adjustment's low bit is set, and returns self. */
extern "C" void *f_066728(void *self, unsigned char *obj, void *a2, unsigned *desc) {
    unsigned *e = (unsigned *)((char *)&D_1d3018 + desc[3] * 8);
    unsigned adj = e[1];
    unsigned ptr = e[0];
    volatile unsigned adjSlot = adj;
    unsigned char *thisp = obj + ((int)adj >> 1);
    void *fn;
    if ((*(volatile unsigned char *)&adjSlot & 1) != 0) {
        unsigned *vt = *(unsigned **)thisp;
        fn = *(void **)((char *)vt + ptr);
    } else {
        fn = (void *)ptr;
    }
    ((void (*)(void *, void *, void *, void *))fn)(self, thisp, a2, thisp);
    return self;
}

} /* namespace swgF */

/* ---- swg2b ---- */
/* TU 117 fragment by worker swg2b: retail 0x05c8d0..0x05dc90 range (C++ with exceptions).
   Partial: only the functions analysed so far are transcribed, all as drafts. */

namespace swg2b {

extern "C" {

void f_04e4b4(void *p);
void *f_04dfa0(void *n);
void f_04ed28(void *s);
void f_04eee8(void *s, void *tag);
void f_05daa4(void *s, int z);
void f_05c7dc(void *a, void *b);
void f_05c950(void *a, char *e1, char *e2, char *b, char *e3);
void f_05daa4(void *s, int z);
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);

}

struct G2 {
    int w[4];
    ~G2() {}
};

struct Pr {
    void *a;
    void *b;
    Pr() {}
    Pr(const Pr &o) {
        a = o.a;
        b = o.b;
        if (b) ++*(int *)b;
    }
    ~Pr();
};

extern "C" {

/* @implements 0x05db44 us f_05db44
   WHAT IT DOES: calls f_04e4b4 on the pointer minus 4.
   Remaining difference: not yet compared. */
void f_05db44(char *a0) {
    G2 g;
    f_04e4b4(a0 - 4);
}

/* @implements 0x05db08 us f_05db08
   WHAT IT DOES: allocates a node through f_04dfa0 for the pointer at +4, stores that pointer in it
   and returns the node address plus 4.
   Remaining difference: not yet compared. */
void *f_05db08(char *a0) {
    G2 g;
    char *s0 = a0 + 4;
    char **v0 = (char **)f_04dfa0(s0);
    *v0 = s0;
    return (char *)v0 + 4;
}

/* @implements 0x05da50 us f_05da50
   WHAT IT DOES: frees each node of the circular list headed at +4 with f_04e4b4, then makes the
   head self-linked. */
void f_05da50(char *a0) {
    char *head = *(char **)(a0 + 4);
    char *s0 = *(char **)head;
    if (s0 != head) {
        do {
            char *t = s0;
            s0 = *(char **)s0;
            f_04e4b4(t);
            head = *(char **)(a0 + 4);
        } while (s0 != head);
    }
    *(char **)head = head;
    *(char **)(head + 4) = head;
}

/* @draft 0x05dcb8 us f_05dcb8
   WHAT IT DOES: compares two keys whose word at +4 may be -1 (empty); when both are set returns
   the signed less-than of the +4 words, otherwise decides by the +12 words.
   Remaining difference: not yet compared. */
int f_05dcb8(char *a0, char *a1) {
    int v1 = *(int *)(a0 + 4);
    if (v1 != -1) {
        int v0 = *(int *)(a1 + 4);
        if (v0 != -1) return v1 < v0;
        return 1;
    }
    if (*(int *)(a1 + 4) != -1) return 0;
    return (unsigned)*(int *)(a0 + 12) < (unsigned)*(int *)(a1 + 12);
}

/* @draft 0x05db84 us f_05db84
   WHAT IT DOES: reads the object at the first word of *a0, decrements its counter at -4 inside an
   interrupt-disabled section, and calls f_04eee8 when the old counter was zero or less.
   Remaining difference: not yet compared. */
void f_05db84(char **a0) {
    G2 g;
    char *s0 = *a0;
    char *s2 = s0 - 12;
    int intr = sceKernelCpuSuspendIntr();
    int s1 = *(int *)(s0 - 4);
    *(int *)(s0 - 4) = *(int *)(s0 - 4) - 1;
    sceKernelCpuResumeIntr(intr);
    if (s1 <= 0) f_04eee8(s2, &g);
}

/* @draft 0x05c8d0 us f_05c8d0
   WHAT IT DOES: appends the string at *a1 to the string at *a0 (rep layout: length at -12,
   capacity at -8), growing through f_05c7dc when the capacity is too small.
   Remaining difference: not yet compared. */
void f_05c8d0(char **a0, char **a1) {
    char *A = *a0;
    char *B = *a1;
    if ((unsigned)*(int *)(A - 8) < (unsigned)(*(int *)(B - 12) + *(int *)(A - 12))) {
        f_05c7dc(a0, a1);
        B = *a1;
        A = *a0;
    }
    char *endA = A + *(int *)(A - 12);
    char *endB = B + *(int *)(B - 12);
    f_05c950(a0, endA, endA, B, endB);
}

/* @draft 0x052788 us f_052788
   WHAT IT DOES: releases the reference slot at this + index*8 + 296 and reloads it from the
   node held at +332 of the object, bumping the refcount of the new block.
   Remaining difference: not yet compared. */
void f_052788(char *a0, unsigned a1) {
    char *s3 = a0 + (a1 << 3);
    char *s1 = s3 + 296;
    char *v0 = *(char **)(a0 + 332);
    char *s0 = *(char **)(v0 + 4);
    char *s2 = s0 + 8;
    if (s1 == s2) return;
    f_04ed28(s1);
    *(char **)s1 = *(char **)(s0 + 8);
    char *v1 = *(char **)(s2 + 4);
    if (v1) {
        *(char **)(s1 + 4) = v1;
        ++*(int *)v1;
    }
}

/* @draft 0x05cbd4 us f_05cbd4
   WHAT IT DOES: advances a tree iterator (node word at *a0, parent at +4, left at +8, right at
   +12) to its in-order successor, as _Rb_tree_increment does.
   Remaining difference: not yet compared. */
void f_05cbd4(char **a0) {
    char *x = *a0;
    if (*(char **)(x + 12)) {
        *a0 = *(char **)(x + 12);
        while (*(char **)(*a0 + 8)) *a0 = *(char **)(*a0 + 8);
        return;
    }
    char *y = *(char **)(x + 4);
    if (x == *(char **)(y + 12)) {
        *a0 = y;
        for (;;) {
            y = *(char **)(y + 4);
            char *xx = *a0;
            if (xx != *(char **)(y + 12)) break;
            *a0 = y;
        }
        if (*(char **)(*a0 + 12) != y) *a0 = y;
        return;
    }
    if (*(char **)(x + 12) != y) *a0 = y;
}

/* @draft 0x05de94 us f_05de94
   WHAT IT DOES: when the object at +4 of a0 is non-null, copies the pair at a2 into a local
   (taking a reference), calls its virtual slot 45 with a0 as this, and releases the local.
   Remaining difference: not yet compared. */
int f_05de94(char *a0, void *a1, Pr *a2) {
    char *obj = *(char **)(a0 + 4);
    if (!obj) return 0;
    Pr tmp(*a2);
    typedef int (*vf)(void *, void *, void *, void *);
    int s0 = ((vf)(*(void ***)obj)[45])(obj, a0, a1, &tmp);
    return s0 != 0;
}

/* @draft 0x05dbf4 us f_05dbf4
   WHAT IT DOES: when the object at +4 of a1 is non-null, asks its virtual slot 44 for a pair,
   stores that pair in the object at a0 (with a reference) or clears a0 through f_05daa4.
   Remaining difference: not yet compared. */
void *f_05dbf4(char *s0, char *a1, void *a2) {
    char *obj = *(char **)(a1 + 4);
    if (!obj) {
        f_05daa4(s0, 0);
        return s0;
    }
    Pr tmp;
    typedef void (*vf)(void *, void *, void *, void *);
    ((vf)(*(void ***)obj)[44])(&tmp, obj, a1, a2);
    if (!tmp.a) {
        f_04ed28(&tmp);
        f_05daa4(s0, 0);
        return s0;
    }
    *(void **)s0 = tmp.a;
    *(void **)(s0 + 4) = tmp.b;
    if (tmp.b) ++*(int *)tmp.b;
    f_04ed28(&tmp);
    return s0;
}

}

Pr::~Pr() {
    f_04ed28(this);
}

}

/* ---- swg2c ---- */
/* TU 117 fragment swg2c: retail 0x05df24..0x061cc8 (the Flash/ActionScript player range,
   C++ with exceptions). Shared-pointer style copy and release helpers, list and vector
   helpers, and the ASContextImpl property hook trace and insert wrappers. Callees outside
   this fragment are declared extern "C" with their retail addresses. */

namespace swg2c {

extern "C" {

extern char D_1a43d0[];
extern char D_1a3134[];
extern char D_1a30d0[];

void *f_04dfa0(void *);
void f_04e4b4(void *);
void f_04e8c0(void *);
void f_04ed28(char *);
void f_05db84(void *);
char *f_05f708(char *, char *, char *, int);
void f_05f774(char *, char *, int, int);
void f_060920(void *, unsigned, unsigned, unsigned);
void *memmove(void *, const void *, unsigned);
int iprintf(const char *, ...);
void _Unwind_Resume(void *);
void *f_065008(void *, void *);
void *f_0655a4(void *, void *);
unsigned char f_05dcb8(char *, void *);
void f_05db44(void *);

/* @draft 0x061c7c us f_061c7c
   WHAT IT DOES: copies the 8-byte entries from the first argument up to the second into the
   destination array, bumping the reference count of each copied second word. */
void *f_061c7c(char *first, char *last, char *d) {
    if (first == last) return d;
    char *p = first;
    do {
        if (d) {
            char *s = *(char **)(p + 4);
            *(char **)(d + 4) = s;
            *(char **)d = *(char **)p;
            if (s) (*(int *)s)++;
        }
        p += 8;
        d += 8;
    } while (p != last);
    return d;
}

/* @draft 0x060ac4 us f_060ac4
   WHAT IT DOES: if the count stored at -4 of the buffer is positive, calls f_060920 on the
   object with zero arguments; then stores -1 at -4 of the buffer. */
void f_060ac4(char **s) {
    char *v = *s;
    if (*(int *)(v - 4) > 0) {
        f_060920(s, 0, 0, 0);
        v = *s;
    }
    *(int *)(v - 4) = -1;
}

/* @draft 0x05f4d0 us f_05f4d0
   WHAT IT DOES: clears the word at +4 of the object, allocates a 24-byte self-linked list head
   and stores it at +4, then clears the word at +8 and links the head to itself.
   Remaining difference: landing pad not yet reproduced. */
void f_05f4d0(char *self) {
    *(void **)(self + 4) = 0;
    void *n = f_04dfa0((void *)24);
    *(void **)(self + 4) = n;
    *(void **)((char *)n + 4) = 0;
    *(void **)(self + 8) = 0;
    *(void **)((char *)n + 8) = n;
    *(void **)n = 0;
    *(void **)((char *)n + 12) = n;
}

/* @draft 0x061b28 us f_061b28
   WHAT IT DOES: stores the vtable address D_1a43d0 into the object, constructs the sub-object at
   +28 with f_05db84, then runs the base destructor f_04e8c0 on the object.
   Remaining difference: landing pad not yet reproduced. */
void f_061b28(char *s) {
    *(void **)s = D_1a43d0;
    f_05db84(s + 28);
    f_04e8c0(s);
}

/* @draft 0x061be0 us f_061be0
   WHAT IT DOES: allocates n four-byte elements and copies the bytes from the first pointer up to
   the second into them with memmove; returns the new block. */
void *f_061be0(void *self, unsigned n, char *first, char *last) {
    (void)self;
    unsigned count = (unsigned)(last - first);
    void *d = f_04dfa0((void *)(n << 2));
    memmove(d, first, count);
    return d;
}

/* @draft 0x05f64c us f_05f64c
   WHAT IT DOES: moves the node at the pointer held in the third argument into the object
   given first: takes the node's next link, relinks the neighbour, runs f_04ed28 on the node's
   sub-object, frees the node with f_04e4b4, and stores the link into the first argument. */
void *f_05f64c(char *self, int unused, char **pp) {
    (void)unused;
    char *s0 = *pp;
    char *s1 = *(char **)s0;
    *(char **)(s1 + 4) = *(char **)(s0 + 4);
    f_04ed28(s0 + 8);
    *(char **)(*(char **)(s0 + 4)) = s1;
    f_04e4b4(s0);
    *(char **)self = s1;
    return self;
}

/* @implements 0x05e264 us f_05e264
   WHAT IT DOES: property hook trace: reports the value at +8 of the object through iprintf,
   choosing the format from the sign of that value and whether it matches the argument. */
void f_05e264(char *self, int a1) {
    char **t = (char **)self;
    int v1 = *(int *)(self + 8);
    int lim = -v1 - 1;
    int v0 = a1 < lim;
    if (v1 < 0) {
        if (v0) iprintf(D_1a3134, *t, -v1, a1);
    } else {
        if (v1 != a1) iprintf(D_1a30d0, *t, v1, a1);
    }
}

/* @draft 0x05f6a8 us f_05f6a8
   WHAT IT DOES: inserts the value (third argument) at index i of the vector held at the object:
   with i below the element count it calls f_05f708 at the element pointer, otherwise f_05f774
   with the end pointer and the excess count.
   Remaining difference: draft from the listing, not yet compared. */
void f_05f6a8(char *self, unsigned i, int x) {
    char *begin = *(char **)(self + 4);
    char *end = *(char **)(self + 8);
    unsigned count = (unsigned)(end - begin) >> 2;
    char *pos = begin + (i << 2);
    if (i < count) {
        f_05f708(self, pos, end, x);
    } else {
        f_05f774(self, end, (int)(i - count), x);
    }
}

/* @implements 0x05df24 us f_05df24
   WHAT IT DOES: copy assignment of a reference-counted pointer pair: when the source is a
   different object, releases this object with f_04ed28, copies the two words from the source
   and bumps the count of the second word's target. */
void *f_05df24(char *self, char *o) {
    if (self != o) {
        f_04ed28(self);
        char *v0 = *(char **)o;
        char *v1 = *(char **)(o + 4);
        *(char **)(self + 4) = v1;
        *(char **)self = v0;
        if (v1) (*(int *)v1)++;
    }
    return self;
}

/* @draft 0x061b80 us f_061b80
   WHAT IT DOES: stores the vtable address D_1a43d0 into the object, constructs the sub-object at
   +28 with f_05db84 and runs the base destructor f_04e8c0, then calls f_05db44 on the object.
   Remaining difference: landing pad not yet reproduced. */
void f_061b80(char *s) {
    *(void **)s = D_1a43d0;
    f_05db84(s + 28);
    f_04e8c0(s);
    f_05db44(s);
}

/* @implements 0x05f708 us f_05f708
   WHAT IT DOES: erases the range from the second pointer up to the third from the vector (the
   first argument): moves the tail down with memmove, then lowers the end pointer at +8 by the
   erased byte count rounded to whole words; returns the first pointer. */
char *f_05f708(char *self, char *pos, char *end, int x) {
    (void)x;
    char *v = *(char **)(self + 8);
    memmove(pos, end, (unsigned)(v - end));
    int n = (((int)(end - pos)) >> 2) << 2;
    *(char **)(self + 8) = *(char **)(self + 8) - n;
    return pos;
}

/* @draft 0x05df80 us f_05df80
   WHAT IT DOES: compares two tagged values: when both keys at +4 are not -1 it returns whether
   they are equal; otherwise it returns 0 unless both are -1, and then compares the words at +12.
   Remaining difference: branch shape not yet matched. */
int f_05df80(char *self, char *o) {
    int a = *(int *)(self + 4);
    if (a != -1) {
        int b = *(int *)(o + 4);
        if (b != -1) return (a ^ b) == 0;
        return 0;
    }
    if (*(int *)(o + 4) != -1) return 0;
    return *(int *)(self + 12) == *(int *)(o + 12);
}

/* @implements 0x05e394 us f_05e394
   WHAT IT DOES: allocates a node from the two arguments with f_065008 and links it into the
   list before the node the third argument points to, then stores the node into the first
   argument and returns that.
   Remaining difference: draft from the listing, not yet compared. */
char *f_05e394(char *self, void *a1, char **pp, void *a3) {
    char *n = (char *)f_065008(a1, a3);
    *(char **)n = *pp;
    *(char **)(n + 4) = *(char **)(*pp + 4);
    *(char **)(*(char **)(*pp + 4)) = n;
    *(char **)(*pp + 4) = n;
    *(char **)self = n;
    return self;
}

/* @draft 0x05f56c us f_05f56c
   WHAT IT DOES: lower-bound search in the tree whose header is the second argument: walks from
   the root (the header's +4 word) comparing node keys at +16 with the key pointed to by the
   third argument; stores the best node, or the header when there is none, into the first
   argument and returns it.
   Remaining difference: draft from the listing, not yet compared. */
char *f_05f56c(char *res, char *hdr, unsigned *key) {
    char *head = *(char **)(hdr + 4);
    char *node = *(char **)(head + 4);
    char *best = head;
    while (node) {
        if (*(unsigned *)(node + 16) < *key) {
            node = *(char **)(node + 12);
        } else {
            best = node;
            node = *(char **)(node + 8);
        }
    }
    if (best != head && !(*key < *(unsigned *)(best + 16))) {
        *(char **)res = best;
    } else {
        *(char **)res = head;
    }
    return res;
}

/* @draft 0x05f5dc us f_05f5dc
   WHAT IT DOES: lower-bound search in the same tree form as f_05f56c (a second copy of the
   same walk): stores the best node, or the header, into the first argument and returns it.
   Remaining difference: draft from the listing, not yet compared. */
char *f_05f5dc(char *res, char *hdr, unsigned *key) {
    char *head = *(char **)(hdr + 4);
    char *node = *(char **)(head + 4);
    char *best = head;
    while (node) {
        if (*(unsigned *)(node + 16) < *key) {
            node = *(char **)(node + 12);
        } else {
            best = node;
            node = *(char **)(node + 8);
        }
    }
    if (best != head && !(*key < *(unsigned *)(best + 16))) {
        *(char **)res = best;
    } else {
        *(char **)res = head;
    }
    return res;
}

/* @implements 0x0613e8 us f_0613e8
   WHAT IT DOES: same node insertion as f_05e394, allocating through f_0655a4 instead of
   f_065008: builds a node from the two arguments, links it before the node the third argument
   points to, stores it into the first argument and returns that. */
char *f_0613e8(char *self, void *a1, char **pp, void *a3) {
    char *n = (char *)f_0655a4(a1, a3);
    *(char **)n = *pp;
    *(char **)(n + 4) = *(char **)(*pp + 4);
    *(char **)(*(char **)(*pp + 4)) = n;
    *(char **)(*pp + 4) = n;
    *(char **)self = n;
    return self;
}

/* @draft 0x05dff0 us f_05dff0
   WHAT IT DOES: tree search for the key pointer in the third argument from the root (the
   second argument's header at +4, its own root at +4); walks right when the node test
   f_05dcb8 is true and left otherwise, keeping the last left-turn node; stores it into the
   first argument and returns that.
   Remaining difference: draft from the listing, not yet compared. */
char *f_05dff0(char *self, char *a1, void *a2) {
    char *s1 = *(char **)(a1 + 4);
    char *s0 = *(char **)(s1 + 4);
    if (s0) {
        do {
            if (f_05dcb8(s0 + 16, a2)) {
                s0 = *(char **)(s0 + 12);
            } else {
                s1 = s0;
                s0 = *(char **)(s0 + 8);
            }
        } while (s0);
    }
    *(char **)self = s1;
    return self;
}

}  // extern "C"

}  // namespace swg2c

/* ---- swg3e ---- */
/* TU 117 fragment swg3e: untagged functions of the SWG Flash/ActionScript player (list_04). */

namespace swg3e {


extern "C" {
void *f_04dfa0(unsigned n);
void *f_05db08(unsigned n);
void f_05daa4(void *self, void *a1);
void f_05db44(void *);
double f_1259cc(void);
int f_06b624(void *, void *, void *);
void f_15f714(void *, void *);
void f_15f6f8(void *);
extern char D_1a4320[];
extern char D_1a4270[];
extern char D_1a4060[];
int f_15e0f4(void *);
void f_15f190(void *, float *, float *);
void f_15f1bc(void *, float *, float *);
double f_11c6d8(double, double);
double f_11cd44(double, double);
void f_068bc0(void *, void *, int);
void f_068e6c(void *, void *, int);
int f_15c278(void *, int);
}

struct Ref { int a, b; Ref(void *p); ~Ref() {} };
inline Ref::Ref(void *p) { f_05daa4(this, p); }
struct NumD {
    void *vt; int z; double d;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumD(double x) { vt = (void *)D_1a4270; d = x; z = 0; }
};
struct NumI {
    void *vt; int z; int v;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumI(int x) { vt = (void *)D_1a4320; v = x; z = 0; }
};
extern "C" {
double f_11c448(double);
double f_11c590(double);
double f_11b514(double);
double f_11bafc(double);
double f_11bce8(double);
double f_11c848(double);
double f_11be14(double);
double f_11cba8(double);
double f_11c018(double);
double f_11d280(double);
double f_11c12c(double);
}

inline double vc(char *obj) {
    void *a = **(void ***)(obj + 52);
    return ((double (*)(void *))((void **)*(void **)a)[24])(a);
}

extern "C" {
int f_15e128(void *);
}

inline double vc2(char *obj) {
    void *a = ((void **)*(void **)(obj + 52))[2];
    return ((double (*)(void *))((void **)*(void **)a)[24])(a);
}

inline void *vc9(char *obj) {
    void *v = *(void **)(obj + 44);
    return ((void *(*)(void *))((void **)*(void **)v)[9])(v);
}

struct NumB {
    void *vt; int z; char b;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumB(char x) { vt = (void *)D_1a4060; b = x; z = 0; }
};
struct Ref0 { int a, b; ~Ref0() {} };
struct H { int a; int *rc; H(const H &o) { a = o.a; rc = o.rc; if (rc) ++*rc; } };
struct V { int w0, w1, w2, w3, w4, w5; int *rc; V(const V &o) { int *r = o.rc; w0 = o.w0; w1 = o.w1; w2 = o.w2; w3 = o.w3; w4 = o.w4; w5 = o.w5; rc = r; if (rc) ++*rc; } };
struct N { int l, r, p, q; V v; };
inline void *operator new(unsigned, void *p) throw() { return p; }
struct Num {
    void *vt; int z; double d;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    Num() { double t = f_1259cc(); vt = (void *)D_1a4270; d = t; z = 0; }
};

extern "C" {

double f_11c448(double);
double f_11c590(double);
double f_11b514(double);
double f_11bafc(double);
double f_11bce8(double);
double f_11c848(double);
double f_11be14(double);
double f_11cba8(double);
double f_11c018(double);
double f_11d280(double);
double f_11c12c(double);

/* @implements 0x0671b0 us f_0671b0
   WHAT IT DOES: builds a 12-byte integer value object (vtable D_1a4320) holding the result of a virtual call on the object at +228 of the one at +56 (0 when absent) and stores it into the returned reference through f_05daa4. */
Ref0 f_0671b0(char *obj) {
    void *p = *(void **)(*(char **)(obj + 56) + 228);
    int v = 0;
    if (p) v = ((int (*)(void *))((void **)*(void **)p)[5])(p);
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)D_1a4320;
    n[2] = v;
    n[1] = 0;
    Ref0 r;
    f_05daa4(&r, n);
    return r;
}

/* @implements 0x067230 us f_067230
   WHAT IT DOES: builds a 12-byte integer value object (vtable D_1a4320) holding the result of a virtual call on the object at +228 of the one at +56 (0 when absent) and stores it into the returned reference through f_05daa4. */
Ref0 f_067230(char *obj) {
    void *p = *(void **)(*(char **)(obj + 56) + 228);
    int v = 0;
    if (p) v = ((int (*)(void *))((void **)*(void **)p)[7])(p);
    unsigned *n = (unsigned *)f_05db08(12);
    n[0] = (unsigned)D_1a4320;
    n[2] = v;
    n[1] = 0;
    Ref0 r;
    f_05daa4(&r, n);
    return r;
}

/* @implements 0x0694bc us f_0694bc
   WHAT IT DOES: builds a 16-byte double value object (vtable D_1a4270) from a float field of the object at +56 and stores it into the returned reference through f_05daa4. */
Ref0 f_0694bc(char *obj) {
    float f = *(float *)(*(char **)(obj + 56) + 288);
    unsigned *n = (unsigned *)f_05db08(16);
    double d = f;
    n[0] = (unsigned)D_1a4270;
    ((double *)n)[1] = d;
    n[1] = 0;
    Ref0 r;
    f_05daa4(&r, n);
    return r;
}

/* @implements 0x069738 us f_069738
   WHAT IT DOES: builds a 16-byte double value object (vtable D_1a4270) from a float field of the object at +56 and stores it into the returned reference through f_05daa4. */
Ref0 f_069738(char *obj) {
    float f = *(float *)(*(char **)(obj + 56) + 292);
    unsigned *n = (unsigned *)f_05db08(16);
    double d = f;
    n[0] = (unsigned)D_1a4270;
    ((double *)n)[1] = d;
    n[1] = 0;
    Ref0 r;
    f_05daa4(&r, n);
    return r;
}

/* @implements 0x0681cc us f_0681cc
   WHAT IT DOES: calls virtual slot 9 on the object at +44, converts through f_06b624 and f_15f714 (and f_15f6f8 in the second form), then clears the returned reference through f_05daa4; returns the result slot. */
void *f_0681cc(void *self, char *obj) {
    void *v = *(void **)(obj + 44);
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    int t = f_06b624(*(void **)(obj + 40), r, *(void **)(obj + 52));
    f_15f714(r, &t);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x06a958 us f_06a958
   WHAT IT DOES: asks a virtual predicate on the object at +52 and returns a reference-counted handle copy of either its first or its second handle (offset 0 or 8), incrementing the refcount. */
H f_06a958(char *obj) {
    char *p = *(char **)(obj + 52);
    void *a = *(void **)p;
    int r = ((int (*)(void *, int))((void **)*(void **)a)[40])(a, *(int *)(p + 8));
    const H &s = r ? *(H *)*(char **)(obj + 52) : *(H *)(*(char **)(obj + 52) + 8);
    return s;
}

/* @implements 0x06a9d4 us f_06a9d4
   WHAT IT DOES: asks a virtual predicate on the object at +52 and returns a reference-counted handle copy of either its first or its second handle (offset 0 or 8), incrementing the refcount. */
H f_06a9d4(char *obj) {
    char *p = *(char **)(obj + 52);
    void *a = *(void **)p;
    int r = ((int (*)(void *, int))((void **)*(void **)a)[39])(a, *(int *)(p + 8));
    const H &s = r ? *(H *)*(char **)(obj + 52) : *(H *)(*(char **)(obj + 52) + 8);
    return s;
}

/* @implements 0x06aba4 us f_06aba4
   WHAT IT DOES: allocates a 16-byte double value object whose value comes from f_1259cc and stores it into the returned reference, with a delete cleanup if the constructor throws. */
Ref f_06aba4(void) {
    Ref r(new Num);
    return r;
}

/* @draft 0x066f5c us f_066f5c
   WHAT IT DOES: allocates a 44-byte tree node and copy-constructs the 28-byte value (six words plus a refcounted pointer) at node+16 from the source, incrementing the refcount. */
N *f_066f5c(int unused, V *src) {
    N *n = (N *)f_04dfa0(44);
    new (&n->v) V(*src);
    return n;
}

/* @implements 0x068148 us f_068148
   WHAT IT DOES: calls virtual slot 9 on the object at +44, converts through f_06b624 and f_15f714 (and f_15f6f8 in the second form), then clears the returned reference through f_05daa4; returns the result slot. */
void *f_068148(void *self, char *obj) {
    void *v = *(void **)(obj + 44);
    void *r = ((void *(*)(void *))((void **)*(void **)v)[9])(v);
    int t = f_06b624(*(void **)(obj + 40), r, *(void **)(obj + 52));
    f_15f714(r, &t);
    f_15f6f8(r);
    f_05daa4(self, 0);
    return self;
}

/* @implements 0x06a0c4 us f_06a0c4
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a0c4(char *obj) {
    Ref r(new NumD(f_11c448(vc(obj))));
    return r;
}

/* @implements 0x06a178 us f_06a178
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a178(char *obj) {
    Ref r(new NumD(f_11c590(vc(obj))));
    return r;
}

/* @implements 0x06a22c us f_06a22c
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a22c(char *obj) {
    Ref r(new NumD(f_11b514(vc(obj))));
    return r;
}

/* @implements 0x06a3cc us f_06a3cc
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a3cc(char *obj) {
    Ref r(new NumD(f_11bafc(vc(obj))));
    return r;
}

/* @implements 0x06a480 us f_06a480
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a480(char *obj) {
    Ref r(new NumD(f_11bce8(vc(obj))));
    return r;
}

/* @implements 0x06a59c us f_06a59c
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a59c(char *obj) {
    Ref r(new NumD(f_11c848(vc(obj))));
    return r;
}

/* @implements 0x06a650 us f_06a650
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a650(char *obj) {
    Ref r(new NumD(f_11be14(vc(obj))));
    return r;
}

/* @implements 0x06a704 us f_06a704
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06a704(char *obj) {
    Ref r(new NumD(f_11cba8(vc(obj))));
    return r;
}

/* @implements 0x06ad64 us f_06ad64
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06ad64(char *obj) {
    Ref r(new NumD(f_11c018(vc(obj))));
    return r;
}

/* @implements 0x06ae18 us f_06ae18
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06ae18(char *obj) {
    Ref r(new NumD(f_11d280(vc(obj))));
    return r;
}

/* @implements 0x06af9c us f_06af9c
   WHAT IT DOES: Math function wrapper: applies a libm routine to the double returned by virtual slot 24 of the object at +52 and returns it as a new double value object in the returned reference. */
Ref f_06af9c(char *obj) {
    Ref r(new NumD(f_11c12c(vc(obj))));
    return r;
}

/* @implements 0x067d60 us f_067d60
   WHAT IT DOES: calls virtual slot 9 on the object at +44, passes it to f_15e128 and returns the integer in a new 12-byte value object stored in the returned reference. */
Ref f_067d60(char *obj) {
    void *x = vc9(obj);
    Ref r(new NumI(f_15e128(x)));
    return r;
}

/* @implements 0x069248 us f_069248
   WHAT IT DOES: calls virtual slot 9 on the object at +44, passes it to f_15e128 and returns the integer in a new 12-byte value object stored in the returned reference. */
Ref f_069248(char *obj) {
    void *x = vc9(obj);
    Ref r(new NumI(f_15e128(x)));
    return r;
}

/* @implements 0x0676d0 us f_0676d0
   WHAT IT DOES: calls virtual slot 9 on the object at +44, passes it to f_15e0f4, adds 1 and returns the integer in a new 12-byte value object stored in the returned reference. */
Ref f_0676d0(char *obj) {
    void *x = vc9(obj);
    Ref r(new NumI(f_15e0f4(x) + 1));
    return r;
}
/* @implements 0x069d48 us f_069d48
   WHAT IT DOES: builds a 12-byte byte-value object (vtable D_1a4060) from f_15c278 applied to the field at +56 and the byte result of virtual slot 22 of the object at +52. */
Ref f_069d48(char *obj) {
    Ref r(new NumB(f_15c278(*(void **)(obj + 56), (char)((int (*)(void *))((void **)*(void **)**(void ***)(obj + 52))[23])(**(void ***)(obj + 52)))));
    return r;
}

/* @implements 0x068b08 us f_068b08
   WHAT IT DOES: dispatches on a virtual result of the object at +52: calls f_068bc0 when nonzero, otherwise f_068e6c with another virtual result, then clears the returned reference. */
void *f_068b08(void *self, char *obj) {
    void *x = vc9(obj);
    void *a = **(void ***)(obj + 52);
    int r = ((int (*)(void *))((void **)*(void **)a)[9])(a);
    if (r) {
        f_068bc0(*(void **)(obj + 40), x, r);
    } else {
        void *b = **(void ***)(obj + 52);
        f_068e6c(*(void **)(obj + 40), x, ((int (*)(void *))((void **)*(void **)b)[23])(b));
    }
    f_05daa4(self, 0);
    return self;
}
/* @implements 0x06a2e0 us f_06a2e0
   WHAT IT DOES: binary Math function wrapper (atan2 or pow): applies it to the doubles from virtual slot 24 of the two objects at +52 and returns a new double value object in the returned reference. */
Ref f_06a2e0(char *obj) {
    Ref r(new NumD(f_11c6d8(vc(obj), vc2(obj))));
    return r;
}

/* @implements 0x06aab8 us f_06aab8
   WHAT IT DOES: binary Math function wrapper (atan2 or pow): applies it to the doubles from virtual slot 24 of the two objects at +52 and returns a new double value object in the returned reference. */
Ref f_06aab8(char *obj) {
    Ref r(new NumD(f_11cd44(vc(obj), vc2(obj))));
    return r;
}

/* @draft 0x0692fc us f_0692fc
   WHAT IT DOES: byte property accessor: when the flag is clear returns the byte at +171 of the object at +44 wrapped in a new value object, otherwise sets that byte from a virtual call and clears the reference. */
Ref0 f_0692fc(char *obj, int a2) {
    char *x = (char *)vc9(obj);
    Ref0 r;
    if (!a2) {
        NumB *n = new NumB((unsigned char)x[171]);
        f_05daa4(&r, n);
        return r;
    }
    void *a = **(void ***)(obj + 52);
    x[171] = ((int (*)(void *))((void **)*(void **)a)[22])(a);
    f_05daa4(&r, 0);
    return r;
}
/* @draft 0x0693c0 us f_0693c0
   WHAT IT DOES: float property accessor: fetches two floats via f_15f190 and returns one as a double value object when the flag is clear, otherwise sets it from a virtual double result via f_15f1bc. */
Ref0 f_0693c0(char *obj, int a2) {
    float a, b, c;
    void *x = vc9(obj);
    f_15f190(x, &a, &b);
    Ref0 r;
    if (!a2) {
        unsigned *n = (unsigned *)f_05db08(16);
        double d = a;
        n[0] = (unsigned)D_1a4270;
        ((double *)n)[1] = d;
        n[1] = 0;
        f_05daa4(&r, n);
    } else {
    c = (float)vc(obj);
    f_15f1bc(x, &c, &b);
    f_05daa4(&r, 0);
    }
    return r;
}
/* @draft 0x06963c us f_06963c
   WHAT IT DOES: float property accessor: fetches two floats via f_15f190 and returns one as a double value object when the flag is clear, otherwise sets it from a virtual double result via f_15f1bc. */
Ref0 f_06963c(char *obj, int a2) {
    float a, b, c;
    void *x = vc9(obj);
    f_15f190(x, &a, &b);
    Ref0 r;
    if (!a2) {
        unsigned *n = (unsigned *)f_05db08(16);
        double d = b;
        n[0] = (unsigned)D_1a4270;
        ((double *)n)[1] = d;
        n[1] = 0;
        f_05daa4(&r, n);
    } else {
    c = (float)vc(obj);
    f_15f1bc(x, &a, &c);
    f_05daa4(&r, 0);
    }
    return r;
}
} }

/* ---- swg3c ---- */
/* TU 117 wave 3, worker swg3c */
namespace swg3c {
extern "C" {

struct Str;
int f_05dcb8(char *, void *);
void f_04eee8(void *s, void *tag);
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
void f_05e4a8(Str *, Str *) throw();
void f_05c8d0(Str *, Str *);
struct G2 { int w[4]; ~G2() {} };
/* COW string handle: the data pointer; the inline destructor drops the rep's reference. */
struct Str {
    char *p;
    Str() {}
    Str(Str &a) { f_05e4a8(this, &a); }
    Str(const Str &a) { f_05e4a8(this, (Str *)&a); }
    ~Str() {
        G2 g;
        char *s0 = p;
        char *s2 = s0 - 12;
        int intr = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(s0 - 4);
        int s1 = *c;
        *c += -1;
        sceKernelCpuResumeIntr(intr);
        if (s1 <= 0) f_04eee8(s2, &g);
    }
};

/* @implements 0x05e7bc us f_05e7bc
   WHAT IT DOES: descends the tree from the root comparing keys with f_05dcb8, going left when the node is not less than the key, and stores the lowest node not less than the key in *out (lower bound). */
char *f_05e7bc(char **out, char *tree, void *key) {
    char *r = *(char **)(tree + 4);
    char *n = *(char **)(r + 4);
    while (n) {
        if (!(f_05dcb8(n + 16, key) & 0xff)) { r = n; n = *(char **)(n + 8); }
        else n = *(char **)(n + 12);
    }
    *out = r;
    return (char *)out;
}

void *f_05db08(int);
void f_05daa4(void *, void *);
void f_05e394(void *, void *, void *, void *);
void f_04ed28(void *);
extern char D_1a4480[];
struct Holder { int a, b; ~Holder() { f_04ed28(this); } };

/* @draft 0x05fbdc us f_05fbdc
   WHAT IT DOES: allocates an 8-byte object via f_05db08 holding the D_1a4480 vtable and a zero, wraps it in a Holder via f_05daa4, and inserts the keyed entry into the tree with f_05e394.
   Remaining difference: missing: second empty landing pad, 8 bytes */
void f_05fbdc(void *unused, char *s) {
    int *p = (int *)f_05db08(8);
    p[0] = (int)D_1a4480;
    p[1] = 0;
    Holder h;
    f_05daa4(&h, p);
    int out[4];
    int v = *(int *)(s + 4);
    f_05e394(out, s, &v, &h);
}

/* @draft 0x05fc60 us f_05fc60
   WHAT IT DOES: allocates an 8-byte object via f_05db08 holding the D_1a4480 vtable and a zero, wraps it in a Holder via f_05daa4, and inserts the keyed entry into the tree with f_05e394. */
void f_05fc60(void *unused, char *s) {
    int *p = (int *)f_05db08(8);
    p[0] = (int)D_1a4480;
    p[1] = 0;
    Holder h;
    f_05daa4(&h, p);
    int out[4];
    int v = *(int *)(s + 4);
    f_05e394(out, s, &v, &h);
}

void *memcpy(void *, const void *, unsigned);
char *f_065060(unsigned);
char *f_05e404(unsigned *, void *, unsigned);


/* @draft 0x05e404 us f_05e404
   WHAT IT DOES: creates a string rep with room for the current length plus extra (doubling capacity for large reps), copies the old characters and length in and terminates it, returning the data pointer.
   Remaining difference: string rep create/grow; register allocation and the capacity branch layout differ */
char *f_05e404(unsigned *s, void *unused, unsigned extra) {
    extra += s[0];
    unsigned n = extra;
    unsigned c = s[1];
    int big = (n < 4068) ^ 1;
    if (big & (c < n)) {
        c <<= 1;
        if (c < n) c = n;
    } else c = n;
    char *r = f_065060(c);
    char *d = r + 12;
    if (s[0]) memcpy(d, (char *)s + 12, s[0]);
    *(unsigned *)r = s[0];
    d[s[0]] = 0;
    return d;
}

/* @implements 0x05a578 us f_05a578
   WHAT IT DOES: copies the first string into the result and appends the second with f_05c8d0, returning the result (string concatenation). */
Str f_05a578(Str &a, Str &b) {
    Str r(a);
    f_05c8d0(&r, &b);
    return r;
}

/* @draft 0x05e4a8 us f_05e4a8
   WHAT IT DOES: copies a string handle: when the rep is marked unshareable it clones via f_05e404, otherwise it bumps the rep reference count under interrupt suspend and shares it.
   Remaining difference: string copy: share the rep or clone it via f_05e404; landing-pad order differs, 7/38 words */
void f_05e4a8(Str *out, Str *a) throw() {
    char *s0 = a->p;
    char *rep = s0 - 12;
    char *r;
    if (*(int *)(rep + 8) < 0) {
        G2 g; G2 g0; G2 g1;
        r = f_05e404((unsigned *)rep, &g, 0);
    } else {
        int st = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(s0 - 4);
        int o = *c; (void)o;
        *c += 1;
        sceKernelCpuResumeIntr(st);
        r = s0;
    }
    out->p = r;
}

extern char D_1a3084[];
void f_131378(const char *);
char *f_061cc8(char *, char *, void *, int);

/* @draft 0x05bf40 us f_05bf40
   WHAT IT DOES: constructs a substring from pos and count, calling the out_of_range throw helper when pos exceeds the length, clamping the count to the remainder and building the new rep via f_061cc8.
   Remaining difference: string substr constructor with the out_of_range check; min select and frame differ */
void f_05bf40(char **out, char **src, unsigned pos, unsigned n) {
    G2 g; G2 g0;
    if (pos > *(unsigned *)(*src - 12)) f_131378(D_1a3084);
    char *d = *src;
    unsigned rest = *(unsigned *)(d - 12) - pos;
    unsigned c = n; if (!(n < rest)) c = rest;
    char *b = d + pos;
    *out = f_061cc8(b, b + c, &g, 0);
}


typedef Holder (*VF1e1b4)(char *self, char *obj, int a2, int cnt, int beg);
/* @implements 0x05e1b4 us f_05e1b4
   WHAT IT DOES: asks the object's owner (virtual call at +184) to look up a reference-counted pair for the given range; if found, stores it in the output with its count incremented, otherwise initialises the output as empty with f_05daa4. */
int *f_05e1b4(int *out, char *obj, int k, char *r) {
    char *t = *(char **)(obj + 4);
    if (t) {
        Holder h = (*(VF1e1b4 *)(*(char **)t + 184))(t, obj, k, (*(int *)(r + 8) - *(int *)(r + 4)) >> 3, *(int *)(r + 4));
        if (h.a) {
            out[0] = h.a;
            out[1] = h.b;
            if (h.b) ++*(int *)h.b;
            return out;
        }
    }
    f_05daa4(out, 0);
    return out;
}

void *memcpy(void *, const void *, unsigned);
extern char D_1a30b4[];
void f_1312d4(const char *);
void f_060920(char **, int, int, unsigned);
/* @draft 0x05c950 us f_05c950
   WHAT IT DOES: replaces the character range [b,e) of a string with the source range [sb,se): throws via f_1312d4 when the new length is too large, resizes the gap with f_060920 and copies the source in with memcpy.
   Remaining difference: string replace(range, range); only the max_size compare constant form differs */
char **f_05c950(char **s, char *b, char *e, char *sb, char *se) {
    unsigned n = se - sb;
    unsigned olen = e - b;
    if (n >= 0x3ffffffc) f_1312d4(D_1a30b4);
    int off = b - *s;
    f_060920(s, off, olen, n);
    if (n) memcpy(*s + off, sb, n);
    return s;
}

/* @draft 0x05dd24 us f_05dd24
   WHAT IT DOES: tree find: takes the lower bound of the key with f_05dcb8, and returns the header (end) if no node matches or the key is less than the found node, else the found node.
   Remaining difference: tree find; frame and loop match, prologue register choice and the two tail calls differ */
char **f_05dd24(char **out, char *tree, void *key) {
    char *hd = *(char **)(tree + 4);
    char *y = hd;
    char *x = *(char **)(hd + 4);
    while (x) {
        if (!(f_05dcb8(x + 16, key) & 0xff)) { y = x; x = *(char **)(x + 8); }
        else x = *(char **)(x + 12);
    }
    struct { char *j; int pad[3]; char *e; } L;
    L.j = y;
    L.e = *(char **)(tree + 4);
    char **pj = &L.j;
    if (*pj == L.e) *out = L.e;
    else if (f_05dcb8((char *)key, *pj + 16) & 0xff) *out = *(char **)(tree + 4);
    else *out = L.j;
    return out;
}

/* @draft 0x05dddc us f_05dddc
   WHAT IT DOES: tree find: takes the lower bound of the key with f_05dcb8, and returns the header (end) if no node matches or the key is less than the found node, else the found node. */
char **f_05dddc(char **out, char *tree, void *key) {
    char *hd = *(char **)(tree + 4);
    char *y = hd;
    char *x = *(char **)(hd + 4);
    while (x) {
        if (!(f_05dcb8(x + 16, key) & 0xff)) { y = x; x = *(char **)(x + 8); }
        else x = *(char **)(x + 12);
    }
    struct { char *j; int pad[3]; char *e; } L;
    L.j = y;
    L.e = *(char **)(tree + 4);
    char **pj = &L.j;
    if (*pj == L.e) *out = L.e;
    else if (f_05dcb8((char *)key, *pj + 16) & 0xff) *out = *(char **)(tree + 4);
    else *out = L.j;
    return out;
}

extern char D_1a2e9c[];
extern char D_1a4d14[];
typedef Str (*VFs)(char *);
/* @draft 0x05977c us f_05977c
   WHAT IT DOES: returns D_1a2e9c when the list at +332 is empty; otherwise asks the last element for its name string (virtual call at +84), writes the D_1a4d14 terminator byte after its length and returns the data pointer, releasing the temporary string.
   Remaining difference: last element's name string via vtable +84, terminator written; the retail frame also keeps the list iterator in memory at sp+16, not reproduced */
char *f_05977c(char *obj) {
    char *head = *(char **)(obj + 332);
    if (*(char **)head == head) return D_1a2e9c;
    char *it = *(char **)(head + 4);
    char *v = *(char **)(it + 8);
    Str s = (*(VFs *)(*(char **)v + 84))(v);
    s.p[*(int *)(s.p - 12)] = D_1a4d14[0];
    return s.p;
}
}
}

/* ---- swg3b ---- */
/* TU 117 fragment by worker swg3b (list_01). */
namespace swg3b {

extern "C" {

int strcmp(const char*, const char*);
#define W(o, off) (*(int *)((char *)(o) + (off)))
static inline void dflt(char *s, int i) {
    void *o = (void *)W(s, 16);
    if (o) {
        void **vt = *(void ***)o;
        ((void (*)(void *, char *))vt[10])(o, ((char **)W(s, 12))[i]);
    }
}
/* @implements 0x04dd14 us f_04dd14
   WHAT IT DOES: handles the _SWGKEYREPEATON/_SWGKEYREPEATOFF/_SWGEND command names by setting the matching flag, else forwards the name to the default handler through the vtable. */
void f_04dd14(char *s, int i) {
    char **names = (char **)W(s, 12);
    if (strcmp(names[i], "_SWGKEYREPEATON") == 0) {
        int p = W(s, 24);
        if (p) *(char*)p = 1; else dflt(s, i);
    } else if (strcmp(((char **)W(s, 12))[i], "_SWGKEYREPEATOFF") == 0) {
        int p = W(s, 24);
        if (p) *(char*)p = 0; else dflt(s, i);
    } else if (strcmp(((char **)W(s, 12))[i], "_SWGEND") == 0) {
        int p = W(s, 20);
        if (p) *(int*)p = 1; else dflt(s, i);
    } else dflt(s, i);
}



int iprintf(const char *, ...);
extern unsigned D_291680, D_291420, D_291410, D_291424, D_291744, D_291748, D_29166c, D_29174c;
extern unsigned *D_291690;
extern char D_1a2db0[], D_1a2e14[], D_1a2ddc[];
/* @draft 0x04e4b4 us f_04e4b4
   WHAT IT DOES: frees a block in the lightweight allocator, validating alignment and range, unlinking it and returning it to a free list or the heap top.
   lwalloc free. Remaining difference: the block size is held in a0 where retail uses a1 (50 of 97 words differ). */
void f_04e4b4(void *pp) {
    unsigned p = (unsigned)pp;
    if (p == 0) return;
    unsigned *b = (unsigned *)(p - 16);
    if ((unsigned)b & 15) { iprintf(D_1a2db0, p); return; }
    if (b[3]) { iprintf(D_1a2e14, b[3], 0); return; }
    unsigned lo = D_291680;
    unsigned hi = lo + D_291420;
    if (p < lo || !(p < hi)) { iprintf(D_1a2ddc, lo, p, hi); return; }
    unsigned *pv = (unsigned *)b[1];
    if (pv) pv[0] = b[0];
    unsigned *nx = (unsigned *)b[0];
    if (nx) nx[1] = (unsigned)pv;
    if (D_291410 == (unsigned)b) D_291410 = (unsigned)nx;
    unsigned sz = b[2];
    unsigned tot = (sz < D_291424 ? 1u << (sz + D_291744 + 1) : (sz + 15) & ~15u) + 16;
    if (D_291748 == (unsigned)b + tot) { D_291748 = (unsigned)b; D_29166c += tot; return; }
    if (sz < D_291424) { unsigned *t = &D_291690[sz]; b[0] = *t; *t = (unsigned)b; return; }
    unsigned *h = (unsigned *)D_29174c;
    if (h) h[1] = (unsigned)b;
    b[1] = 0;
    b[0] = D_29174c;
    D_29174c = (unsigned)b;
}

/* @draft 0x04eaa0 us f_04eaa0
   WHAT IT DOES: destructor of a container object: stores its vtable, clears the list member, frees it and runs the base destructor.
   Remaining difference: the exception landing pad keeps the member pointer in a third saved register (s2) instead of reusing s0. */

extern char D_1a3698[];
void f_04ee68(void*,void*); void f_04e8d8(void*);
void f_04e4b4(void *);
struct Base { int a; ~Base() { f_04e8d8(this);} };
struct Node { Node*l; Node*p; Node*r; Node*q; };
struct Lst { int pad; Node *head; int size;
 void clear(){
  if (size) {
    f_04ee68(this, head->p);
    size=0;
    head->r = head;
    head->p = 0;
    head->q = head;
  } }
 ~Lst(){ f_04e4b4(head);} };
struct Outer : Base { int b[5]; Lst m; ~Outer() { m.clear(); } };
void f_04eaa0(Outer *o){
  *(void**)o = D_1a3698;
  o->~Outer();
}

/* @draft 0x04eb44 us f_04eb44
   WHAT IT DOES: deleting twin of the container destructor, also freeing the block header at -4.
   Deleting twin of f_04eaa0 (frees the block header at -4 afterwards). Same remaining difference. */
void f_04eb44(Outer *o){
  *(void**)o = D_1a3698;
  o->~Outer();
  f_04e4b4((char*)o - 4);
}



extern char D_1a4480[];
void *f_04dfa0(unsigned); void f_04ed28(void*); void f_05e394(void*,void*,void*,void*);
struct Em { ~Em(){} };
struct Ob {
  void *vt; int x;
  static void *operator new(unsigned n){ unsigned *p=(unsigned*)f_04dfa0(n+4); *p=n+4; return p+1; }
  static void operator delete(void*) {}
  Ob(){ Em e; vt = D_1a4480; x = 0; }
};
struct Pair { Ob *p; int *cnt; Pair(Ob *o){ p=o; cnt=0; if(o){ Em e; cnt=(int*)f_04dfa0(4); *cnt=1; } } ~Pair(){ f_04ed28(this);} };
/* @draft 0x0529a4 us f_0529a4
   WHAT IT DOES: allocates a ref-counted object, then calls f_05e394 with it and a field of the player, releasing the holder afterwards.
   Remaining difference: register assignment (retail keeps the object pointer in s1 and the exception pointer in s0) and one missing landing pad (26 of 46 words differ). */
void f_0529a4(char *s){
  char *q = s+328;
  Pair pr(new Ob);
  int out[8]; int a;
  a = *(int*)(q+4);
  f_05e394(out+4, q, &a, &pr);
}

/* @draft 0x04ec74 us f_04ec74
   WHAT IT DOES: releases a tree of nodes: recurses on the child, decrements the refcount of each node's payload under interrupt suspend, and frees the node.
   Tree release. Remaining difference: register assignment only (10 of 45 words): retail keeps the context in s4, the count in s2, the block in s3. */
unsigned sceKernelCpuSuspendIntr(void); void sceKernelCpuResumeIntr(unsigned);
void f_04eee8(void*, void*);
void f_04ec74(void *a, int *n) {
  Em e;
  while (n) {
    f_04ec74(a, (int*)n[3]);
    int *k = (int*)n[4];
    int nx = n[2];
    void *blk = k-3;
    unsigned i = sceKernelCpuSuspendIntr();
    int c = ((volatile int*)k)[-1];
    k[-1] = k[-1] - 1;
    sceKernelCpuResumeIntr(i);
    if (c <= 0) { f_04eee8(blk, &e); }
    f_04e4b4(n);
    n = (int*)nx;
  }
}

extern char D_1a4110[];
struct Ob2 {
  void *vt; int x;
  static void *operator new(unsigned n){ unsigned *p=(unsigned*)f_04dfa0(n+4); *p=n+4; return p+1; }
  static void operator delete(void*) {}
  Ob2(){ Em e; vt = D_1a4110; x = 0; }
};
struct Pair2 { Ob2 *p; int *cnt; Pair2(Ob2 *o){ p=o; cnt=0; if(o){ Em e; cnt=(int*)f_04dfa0(4); *cnt=1; } } ~Pair2(){ f_04ed28(this);} };
/* @draft 0x052a5c us f_052a5c
   WHAT IT DOES: like f_0529a4 with another object class: allocates a ref-counted object and calls f_05e394 with it.
   Same shape as f_0529a4 with another vtable; same remaining differences (scheduling and the first landing pad). */
void f_052a5c(char *s){
  char *q = s+328;
  Pair2 pr(new Ob2);
  int out[8]; int a;
  a = *(int*)(q+4);
  f_05e394(out+4, q, &a, &pr);
}

void f_05dd24(void*, void*, int); void f_05e264(void*, int);
struct R5 { int a, b, c, d; };
struct It5 { int n, p[3]; };
/* @draft 0x050650 us f_050650
   WHAT IT DOES: looks up an entry in the map at +24; if its payload state is 1, stores the three arguments into the player, notifies the payload, makes a virtual call and returns 1, else returns 0.
   Remaining difference: register allocation and scheduling (31 of 50 words). */
int f_050650(char *s, int x, int y, int z) {
  It5 it; char *m = s + 24;
  f_05dd24(&it, m, y);
  int r = 0;
  It5 end; end.n = W(m, 4);
  if (it.n != end.n) {
    char *nd = (char *)W(it.n, 32);
    if (W(nd, 4) == 1) {
      W(s, 48) = 1; W(s, 44) = x; W(s, 52) = z;
      f_05e264(nd, 1);
      void **vt = *(void ***)W(s, 0);
      R5 t = ((R5 (*)(void *, int, int))vt[43])(s, 1, W(it.n, 32));
      f_04ed28(&t);
      return 1;
    }
  }
  return r;
}

}
}

/* ---- swg3a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment by worker swg3a. */
namespace swg3a {

struct Rec16 { int a, b, c, d; };
inline void *operator new(unsigned, void *p) { return p; }

extern "C" {
void f_04a5d8(void *);
void f_04a610(void *);
void f_04b994(void *);
int f_15c07c(void *, int, int);
void f_15d2e4(void *, int, int, int);
void f_15cef8(void *, int, int);
void f_15ced4(void *, int, int);
void f_07d880a(void *) asm("f_07d880");
void f_15c870d(void *, int, int, float, float) asm("f_15c870");
void f_15d0ac(void *, int, int, int);
void f_15d124(void *, int, int, int);
void f_118e30(int, int, int, int, int);
void f_1166d4(int);
void f_04d648(void *);
void f_04b290(void *);
void f_04b2b4(void *);
void *f_04dfa0(int);
void *f_15bfe4(void *, int);
void f_15f190(void *, float *, float *);
void f_07d764(void *);
void _ZdlPv(void *);
void f_021720(void);
void f_021750(void);
void f_045400a(void *) asm("f_045400");
void f_04559ca(void *) asm("f_04559c");
void f_045e58(void *, void *);
int f_07dacc(void *, int, int, int);
void f_116898(int);
void f_118738(int, int);
void f_1187d8(int, int);
void f_1187fc(int, float);
extern void *D_241000;
extern void *D_241004;
void _ZdaPv(void *);
void f_07d754(void *);
void f_0459d0(void *, void *, void *, void *, void *, void *, void *, void *, int);
void *memset(void *, int, unsigned);
extern int D_291424, D_291680, D_291690, D_291420, D_291668, D_29166c, D_291748, D_29174c, D_291410;
void f_045c14(void *, void *, void *, void *, void *, void *, void *, void *, int);
}
void operator delete[](void *) throw();
extern "C" {
}

struct B { B() { f_04a5d8(this); } ~B() { f_04a610(this); } };
struct D : B { D() { f_04b994(this); } };

extern "C" {

/* @implements 0x04b8cc us f_04b8cc
   WHAT IT DOES: placement-constructs a derived player object in the storage passed in (base ctor helper f_04a5d8, then f_04b994). */
void f_04b8cc(void *s) {
    new (s) D;
}

/* @implements 0x04b914 us f_04b914
   WHAT IT DOES: twin of f_04b8cc: placement-constructs the derived object in the passed storage. */
void f_04b914(void *s) {
    new (s) D;
}

/* @implements 0x04b4d8 us f_04b4d8
   WHAT IT DOES: resolves the movie-clip id for a1 via f_15c07c and passes it with the byte a2 to f_15d2e4 on the player's object. */
void f_04b4d8(char *s, int a1, unsigned char a2) {
    void *o = *(void **)s;
    f_15d2e4(o, f_15c07c(o, 3, a1), a2, 0);
}

/* @implements 0x04b664 us f_04b664
   WHAT IT DOES: resolves the clip id for a1 and calls f_15cef8 with the boolean a2 != 0. */
void f_04b664(char *s, int a1, int a2) {
    void *o = *(void **)s;
    f_15cef8(o, f_15c07c(o, 3, a1), a2 != 0);
}

/* @implements 0x04b6d4 us f_04b6d4
   WHAT IT DOES: resolves the clip id for a1 and calls f_15ced4 with the boolean a2 != 0. */
void f_04b6d4(char *s, int a1, int a2) {
    void *o = *(void **)s;
    f_15ced4(o, f_15c07c(o, 3, a1), a2 != 0);
}


/* @draft 0x046894 us f_046894
   WHAT IT DOES: stores a2 into the 20-int-wide table at s+108 indexed by a1 and the row at s+20, sets the dirty byte at s+908 if it changed, then calls f_07d880 on the player's object. */
void f_046894(char *s, int a1, int a2) {
    int *p = (int *)(s + 108) + (a1 * 20 + *(int *)(s + 20));
    if (*p != a2) {
        *p = a2;
        *(char *)(s + 908) = 1;
    }
    f_07d880a(*(void **)s);
}

/* @implements 0x045378 us f_045378
   WHAT IT DOES: if the global D_241000 is set, frees the array D_241004 (if any) and clears both globals. */
void f_045378(void) {
    if (D_241000) {
        if (D_241004) _ZdaPv(D_241004);
        D_241004 = 0;
        D_241000 = 0;
    }
}

/* @implements 0x04b368 us f_04b368
   WHAT IT DOES: resolves the clip id for a1 and calls f_15c870 with 0 and the floats x, y. */
void f_04b368(char *s, int a1, float x, float y) {
    void *o = *(void **)s;
    f_15c870d(o, f_15c07c(o, 3, a1), 0, x, y);
}

/* @implements 0x04b548 us f_04b548
   WHAT IT DOES: resolves the clip id for a1 and calls f_15d0ac with a2 and the boolean a3 != 0. */
void f_04b548(char *s, int a1, int a2, int a3) {
    void *o = *(void **)s;
    f_15d0ac(o, f_15c07c(o, 3, a1), a2, a3 != 0);
}

/* @implements 0x04b5c8 us f_04b5c8
   WHAT IT DOES: resolves clip ids for a1 and a2 and calls f_15d124 with both and the boolean a3 != 0. */
void f_04b5c8(char *s, int a1, int a2, int a3) {
    void *o = *(void **)s;
    int x = f_15c07c(o, 3, a1);
    int y = f_15c07c(o, 0, a2);
    f_15d124(o, x, y, a3 != 0);
}

/* @implements 0x04b3c8 us f_04b3c8
   WHAT IT DOES: looks up the object for clip a1; if found, fetches its two floats with f_15f190 and stores them through a2 and a3. */
void f_04b3c8(char *s, int a1, float *a2, float *a3) {
    void *o = *(void **)s;
    void *r = f_15bfe4(o, f_15c07c(o, 3, a1));
    float x, y;
    if (r) {
        f_15f190(r, &x, &y);
        *a2 = x;
        *a3 = y;
    }
}

/* @implements 0x046620 us f_046620
   WHAT IT DOES: selects a blend mode by m (1, 2 or default), sets it with f_118e30, then calls f_1166d4(4). */
void f_046620(void *s, int m) {
    switch (m) {
    case 1: f_118e30(0, 2, 10, 0, 255); break;
    case 2: f_118e30(2, 2, 10, 0, 255); break;
    default: f_118e30(0, 2, 3, 0, 0); break;
    }
    f_1166d4(4);
}

/* @implements 0x04c160 us f_04c160
   WHAT IT DOES: if index a1 is within the entry count at s+32, copies a 16-byte record (selected by a2) into the entry's halfword fields at four positions. */
void f_04c160(char *s, int a1, int a2) {
    if (*(int *)(s + 32) >= a1) {
        Rec16 *r = (Rec16 *)(*(char **)(s + 40) + a2 * 16);
        unsigned short *e = (unsigned short *)(*(char **)(s + 36) + a1 * 172);
        e[0] = r->a; e[10] = r->c; e[1] = r->b; e[20] = r->a; e[30] = r->c; e[11] = r->b; e[21] = r->d;
        e[31] = r->d;
    }
}

/* @implements 0x04bef8 us f_04bef8
   WHAT IT DOES: initialises the player's entry table: runs setup helpers, counts entries, allocates count*172 bytes, stores the block in the player and its owner, and recounts. */
void f_04bef8(char *s) {
    f_04d648(s);
    char *q = *(char **)(*(char **)s + 224);
    f_04b290(s);
    *(int *)(q + 32) = 0;
    f_04b2b4(s);
    int n = *(int *)(q + 32);
    *(int *)(s + 32) = n;
    void *p = f_04dfa0(n * 172);
    *(void **)(s + 36) = p;
    *(void **)(q + 28) = p;
    *(int *)(q + 32) = 0;
    f_04b2b4(s);
}

/* @draft 0x04c0a8 us f_04c0a8
   WHAT IT DOES: if index a1 is valid, either clears the entry's flag byte (a4 or a5 not positive) or stores a2..a5 into the entry and sets the flag byte. */
void f_04c0a8(char *s, int a1, int a2, int a3, int a4, int a5) {
    if (*(int *)(s + 32) >= a1) {
        int bad = a4 <= 0 || a5 <= 0;
        char *e = *(char **)(s + 36) + a1 * 172;
        if (bad) {
            *(char *)(e + 137) = 0;
        } else {
            *(int *)(e + 152) = a5;
            *(char *)(e + 137) = 1;
            *(int *)(e + 140) = a2;
            *(int *)(e + 144) = a3;
            *(int *)(e + 148) = a4;
        }
    }
}


/* @implements 0x0467ec us f_0467ec
   WHAT IT DOES: destroys the player's objects: runs f_07d764 and deletes the first, deletes the second, delete[]s the third, clearing each pointer. */
void f_0467ec(char *s) {
    void *a = *(void **)s;
    void *b = *(void **)(s + 4);
    if (a) {
        f_07d764(a);
        _ZdlPv(a);
        *(void **)s = 0;
    }
    if (b) {
        _ZdlPv(b);
        *(void **)(s + 4) = 0;
    }
    b = *(void **)(s + 24);
    if (b) {
        _ZdaPv(b);
        *(void **)(s + 24) = 0;
    }
}


/* @implements 0x04c1c8 us f_04c1c8
   WHAT IT DOES: same as f_04c160 but takes the 16-byte record by value. */
void f_04c1c8(char *s, int a1, Rec16 r) {
    if (*(int *)(s + 32) >= a1) {
        unsigned short *e = (unsigned short *)(*(char **)(s + 36) + a1 * 172);
        e[0] = r.a; e[10] = r.c; e[1] = r.b; e[20] = r.a; e[30] = r.c; e[11] = r.b; e[21] = r.d;
        e[31] = r.d;
    }
}

/* @implements 0x046d50 us f_046d50
   WHAT IT DOES: caches a lookup: if the key pair (a1, a2) differs from the cached one, calls f_07dacc, stores the result (returns 0 on -1) and the key; returns the first int of the buffer. */
int f_046d50(char *s, int a1, int a2) {
    int *p = *(int **)(s + 4);
    void *o = *(void **)s;
    if (a1 != *(int *)(s + 12) || *(int *)(s + 16) != a2) {
        int r = f_07dacc(o, a1, (int)p, a2);
        *(int *)(s + 8) = r;
        if (r == -1) return 0;
        *(int *)(s + 12) = a1;
        *(int *)(s + 16) = a2;
    }
    return *p;
}

/* @draft 0x04d2c0 us f_04d2c0
   WHAT IT DOES: draws all entries: starts a batch (f_021720), initialises a context, calls f_045e58 for every entry whose flag byte at +136 is set, closes the context and ends the batch (f_021750). */
void f_04d2c0(char *s) {
    int i = 0;
    int o[4];
    f_021720();
    f_045400a(o);
    for (i = 0; i < *(int *)(s + 32); ) {
        char *e = *(char **)(s + 36) + i * 172;
        i++;
        if (*(unsigned char *)(e + 136)) f_045e58(o, e);
    }
    f_04559ca(o);
    f_021750();
}


/* @implements 0x045400 us f_045400
   WHAT IT DOES: initialises a draw-state struct: sets its first two words to -1, sets the blend mode via f_118e30 and calls f_1166d4(4). */
void f_045400(int *p) {
    p[0] = -1;
    p[1] = -1;
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
    f_1166d4(5);
    f_116898(7);
    f_116898(9);
    f_118738(7, 1);
    f_1187d8(1, 1);
    f_1187fc(0, 0.0f);
    f_116898(10);
    f_116898(5);
    f_116898(7);
    f_1166d4(9);
    f_116898(10);
    f_116898(1);
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
    f_116898(6);
}

/* @implements 0x0454d4 us f_0454d4
   WHAT IT DOES: sets p[0] to -1 and issues a fixed sequence of GPU state calls (f_118e30, f_1166d4, f_116898, f_118738, f_1187d8, f_1187fc) ending in the default blend mode. */
void f_0454d4(int *p) {
    p[0] = -1;
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
    f_1166d4(5);
    f_116898(7);
    f_116898(9);
    f_118738(7, 1);
    f_1187d8(1, 1);
    f_1187fc(0, 0.0f);
    f_116898(10);
    f_116898(5);
    f_116898(7);
    f_1166d4(9);
    f_116898(10);
    f_116898(1);
    f_118e30(0, 2, 3, 0, 0);
    f_1166d4(4);
}

/* @draft 0x04d224 us f_04d224
   WHAT IT DOES: counts entries whose id at +128 equals the clip id for a1, stores the count through out if given, and returns the index of the first match or -1. */
int f_04d224(char *s, int a1, int *out) {
    int cnt = 0, found = -1, i;
    void *o = *(void **)s;
    char *e = *(char **)(s + 36);
    int id = f_15c07c(o, 3, a1);
    int n = *(int *)(s + 32);
    for (i = 0; i < n; i++, e += 172) {
        if (id == *(int *)(e + 128)) {
            if (found == -1) found = i;
            cnt++;
        }
    }
    if (out) *out = cnt;
    return found;
}

/* @implements 0x04d4c4 us f_04d4c4
   WHAT IT DOES: packs twelve float arguments into seven 16-byte vectors on the stack (one of them zero) and calls f_045c14 with an output buffer and them. */
void f_04d4c4(float x1, float x2, float x4, float x5, float x6, float x7,
              float y1, float y2, float y4, float y5, float y6, float y7) {
    float o[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4];
    v1[0] = x1; v1[1] = y1;
    v2[0] = x2; v2[1] = y2;
    v3[0] = 0; v3[1] = 0;
    v4[0] = x4; v4[1] = y4;
    v5[0] = x5; v5[1] = y5;
    v6[0] = x6; v6[1] = y6;
    v7[0] = x7; v7[1] = y7;
    f_045c14(o, v1, v2, v3, v4, v5, v6, v7, 0);
}

/* @implements 0x0452cc us f_0452cc
   WHAT IT DOES: if D_241000 is set, clears the D_291680 buffer, derives the 16-byte-aligned end, and resets the allocation pointers and counters. */
void f_0452cc(void) {
    if (D_241000) {
        int n = D_291424 << 2;
        D_291690 = D_291680;
        memset((void *)D_291680, 0, n);
        int base = D_291680;
        int e = (base + n + 15) & -16;
        int a = D_291420 - (e - base);
        D_29166c = a;
        D_29174c = 0;
        D_291410 = 0;
        D_291668 = a;
        D_291748 = e;
    }
}

/* @draft 0x046c8c us f_046c8c
   WHAT IT DOES: looks up the clip data with f_07dacc, caches the key (a1, a2); if the result is a type-1 list, returns the sum of (end - start) halfword spans over its 16-byte records, else 0. */
int f_046c8c(char *s, int a1, int a2) {
    int *p = *(int **)(s + 4);
    int r = f_07dacc(*(void **)s, a1, (int)p, a2);
    *(int *)(s + 8) = r;
    if (r == -1) return 0;
    *(int *)(s + 12) = a1;
    *(int *)(s + 16) = a2;
    if (*p != 1) return 0;
    int sum = 0, i;
    volatile int sp_[2];
    short *q = (short *)(p + 1);
    for (i = 0; i < p[1]; i++, q += 8) {
        int x = q[4], y = q[6];
        sp_[0] = x;
        sp_[1] = y;
        sum += y - x;
    }
    return sum;
}

}

extern "C" void *f_1534a4(unsigned) __asm__("_Znwj");
extern "C" void *f_153558(unsigned) __asm__("_Znaj");
struct Obj924 {
    char pad[924];
    Obj924() { f_07d754(this); }
    static void *operator new(unsigned n) { return f_1534a4(n); }
    static void operator delete(void *p) { _ZdlPv(p); }
};

extern "C" {
/* @implements 0x04670c us f_04670c
   WHAT IT DOES: resets the cache keys at s+12/s+16 to -1; if neither object pointer (s+0, s+4) exists yet, allocates and constructs the 924-byte object, a 0xaf20-byte buffer and a 0xdae80-byte array, fills the 10x20 int table at s+28 with -1 and clears the byte at s+908 and the word at s+20. */
void f_04670c(int *s) {
    s[3] = -1;
    s[4] = -1;
    if (s[0] == 0 && s[1] == 0) {
        Obj924 *o = new Obj924;
        s[1] = (int)f_1534a4(0xaf20);
        s[0] = (int)o;
        s[6] = (int)f_153558(0xdae80);
        int i;
        for (i = 0; i < 20; i++) {
            s[7 + i] = -1;
            s[27 + i] = -1;
            s[47 + i] = -1;
            s[67 + i] = -1;
            s[87 + i] = -1;
            s[107 + i] = -1;
            s[127 + i] = -1;
            s[147 + i] = -1;
            s[167 + i] = -1;
            s[187 + i] = -1;
        }
        s[5] = 0;
        *(char *)((char *)s + 908) = 0;
    }
}

/* @implements 0x04d3d8 us f_04d3d8
   WHAT IT DOES: packs twenty-eight float arguments into seven 4-float vectors on the stack (the third all zero) and calls f_0459d0 with an output buffer and them. */
void f_04d3d8(float x1, float x2, float x4, float x5, float x6, float x7,
              float y1, float y2, float y4, float y5, float y6, float y7,
              float z1, float z2, float z4, float z5, float z6, float z7,
              float w1, float w2, float w4, float w5, float w6, float w7) {
    float o[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4];
    v1[0] = x1; v1[1] = y1; v1[2] = z1; v1[3] = w1;
    v2[0] = x2; v2[1] = y2; v2[2] = z2; v2[3] = w2;
    v3[0] = 0; v3[1] = 0; v3[2] = 0; v3[3] = 0;
    v4[0] = x4; v4[1] = y4; v4[2] = z4; v4[3] = w4;
    v5[0] = x5; v5[1] = y5; v5[2] = z5; v5[3] = w5;
    v6[0] = x6; v6[1] = y6; v6[2] = z6; v6[3] = w6;
    v7[0] = x7; v7[1] = y7; v7[2] = z7; v7[3] = w7;
    f_0459d0(o, v1, v2, v3, v4, v5, v6, v7, 0);
}

/* @draft 0x04c910 us f_04c910
   WHAT IT DOES: if index a1 is valid, interpolates two coordinates of the entry between its stored endpoints by fx and fy, stores them in the entry, then computes the integer min cell (min/64) and max cell ((max+63)/64) of the interpolated x against the entry's bounds into +80 and +84. */
void f_04c910(char *s, int a1, float fx, float fy) {
    if (*(int *)(s + 32) < a1) return;
    {
        char *e = *(char **)(s + 36) + a1 * 172;
        float t0 = *(float *)(e + 92), t1 = *(float *)(e + 96);
        float u0 = *(float *)(e + 108), u1 = *(float *)(e + 116);
        float x = t0 + (t1 - t0) * fx;
        float y = u0 + (u1 - u0) * fy;
        float lo = *(float *)(e + 8);
        float m = lo, c = lo;
        *(float *)(e + 28) = x;
        *(float *)(e + 72) = y;
        *(float *)(e + 68) = x;
        *(float *)(e + 52) = y;
        if (x < m) m = x;
        float hi = *(float *)(e + 48);
        if (hi < m) m = hi;
        if (x < m) m = x;
        *(int *)(e + 80) = (int)(m * 0.015625f);
        if (c < x) c = x;
        if (c < hi) c = hi;
        if (c < x) c = x;
        *(int *)(e + 84) = (int)((c + 63.0f) * 0.015625f);
    }
}

}
}

/* ---- swg3d ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment by worker swg3d (list_03). */
namespace swg3d {

#define W(o, off) (*(int *)((char *)(o) + (off)))
#define B(o, off) (*(unsigned char *)((char *)(o) + (off)))
typedef int (*vfn_t)(void *);
typedef double (*dfn_t)(void *);
#define DBL(o, off) (*(double *)((char *)(o) + (off)))

struct Tmp16 {
    int w[4];
    ~Tmp16() {}
};
struct NodeIt { void *n; int pad[3]; };
struct InsRes { void *it; unsigned char ok; };
struct Empty { ~Empty() {} };
struct It2 {
    void **p;
    void *&operator*() { return *p; }
    It2 &operator++() { ++p; return *this; }
    bool operator!=(const It2 &o) const { return p != o.p; }
};

extern "C" {

extern char D_1a32b4[];
extern char D_1a32bc[];
extern char D_1a3fb0[];
extern char D_1a3d60[];
extern char D_1a43d0[];
extern char D_1a4d14[];
extern char D_1a30b4[];
extern char D_1a4868[];
extern char D_1a32dc[];
extern double D_1a4d28;
extern char D_1a3698[];
extern char D_1a3370[];

void f_05a3e8(void *self, const char *s, void *tmp);
void f_0604dc(void *self);
void f_04e8d8(void *self);
void f_05db44(void *self);
int f_15fb50(void *a, int b);
int f_161d88(void *a, void *b);
int f_15e1f0(void *a, void *b);
char *f_15c098(void *a, int b, int c);
int f_05dcb8(void *a, void *b);
void f_05db84(void *o);
void f_04e8c0(void *o) throw();
void f_06523c(void *out, void *t, void *x, void *y, void *key);
void f_064d8c(void *out, void *t, void *x, void *y, void *key);
void f_060920(void *s, int pos, int n1, int n2);
void *memcpy(void *d, const void *s, unsigned n);
int f_15ea7c(void *a, void *b);
int f_164a28(double a, double b);
int iprintf(const char *fmt, ...);
int f_12937c(void *a, int b);
int f_129590(void *a, int b, int c);
void f_04ee68(void *a, int b);
void f_04e4b4(void *p);
void f_064c6c(char **it);
void *f_04dfa0(unsigned n);
void f_1312d4(const char *s);

/* @implements 0x0631e8 us f_0631e8
   WHAT IT DOES: calls f_05a3e8(self, string, tmp) with D_1a32b4 if byte 8 of the argument is set, else D_1a32bc, and returns self. */
void *f_0631e8(void *o, void *a)
{
    Tmp16 t;
    f_05a3e8(o, B(a, 8) ? D_1a32b4 : D_1a32bc, &t);
    return o;
}

struct B04e8d8 {
    ~B04e8d8() { f_04e8d8(this); }
};
struct D0630c0 : B04e8d8 {
    ~D0630c0() { f_0604dc((char *)this + 32); }
};

/* @implements 0x0630c0 us f_0630c0
   WHAT IT DOES: destructor: stores the vtable D_1a3fb0, destroys the member at +32 (f_0604dc) and the base (f_04e8d8), then calls f_05db44(self). */
void f_0630c0(void *o)
{
    *(void **)o = D_1a3fb0;
    ((D0630c0 *)o)->~D0630c0();
    f_05db44(o);
}

/* @implements 0x063880 us f_063880
   WHAT IT DOES: walks the pointer vector at +36..+40 and calls f_15fb50(item, 0) on every non-null element. */
void f_063880(void *o)
{
    It2 it; it.p = (void **)W(o, 36);
    It2 e; e.p = (void **)W(o, 40);
    for (; it != e; ++it) {
        if (*it)
            f_15fb50(*it, 0);
    }
}

/* @implements 0x0637a4 us f_0637a4
   WHAT IT DOES: walks the pointer vector at +36..+40 and calls f_161d88(owner at +24, item) on every non-null element. */
void f_0637a4(void *o)
{
    It2 it; it.p = (void **)W(o, 36);
    It2 e; e.p = (void **)W(o, 40);
    for (; it != e; ++it) {
        if (*it)
            f_161d88((void *)W(o, 24), *it);
    }
}

/* @implements 0x063810 us f_063810
   WHAT IT DOES: walks the pointer vector at +36..+40 and calls f_15e1f0(item, arg) on every non-null element. */
void f_063810(void *o, void *a)
{
    It2 it; it.p = (void **)W(o, 36);
    It2 e; e.p = (void **)W(o, 40);
    for (; it != e; ++it) {
        if (*it)
            f_15e1f0(*it, a);
    }
}

/* @implements 0x064188 us f_064188
   WHAT IT DOES: asks the argument object (virtual slot 23) for a level n; if n > 0 divides the int at +8 by 2^n. */
void f_064188(void *o, void *a)
{
    int n = ((vfn_t *)*(void **)a)[23](a);
    if (n > 0) {
        int d = 2;
        for (int i = 1; i < n; i++)
            d *= 2;
        W(o, 8) = W(o, 8) / d;
    }
}

/* @implements 0x0644d0 us f_0644d0
   WHAT IT DOES: returns whether a stream-like object is good: from the buffer at +28 if byte 8 is set, else reads the next character through f_15c098 (or the cached one) and returns whether it is non-zero. */
int f_0644d0(void *o)
{
    if (B(o, 8))
        return W(W(o, 28), -12) != 0;
    char *r;
    int c = W(o, 16);
    if (c == -1) {
        char **p = (char **)W(o, 24);
        *(*p + W(*p, -12)) = D_1a4d14[0];
        r = *p;
    } else {
        r = f_15c098((void *)W(W(o, 12), 4), 7, c);
    }
    return *r != 0;
}

/* @implements 0x064e98 us f_064e98
   WHAT IT DOES: tree lower-bound search: descends from the root of tree t comparing key with f_05dcb8 and stores the best node into *out, returning out. */
void *f_064e98(void **out, void *t, void *key)
{
    char *best = (char *)W(t, 4);
    char *n = (char *)W(best, 4);
    while (n) {
        if (f_05dcb8(key, n + 16) & 0xff) {
            best = n;
            n = (char *)W(n, 8);
        } else {
            n = (char *)W(n, 12);
        }
    }
    *out = best;
    return out;
}

struct B1_21a0 { int w[6]; ~B1_21a0() { f_04e8d8(this); } };
struct B2_21a0 { void *vt; int w[6]; ~B2_21a0() { f_04e8c0(this); } };
struct M_21a0 { int w[1]; ~M_21a0() { f_05db84(this); } };
struct D_21a0 : B1_21a0, B2_21a0 {
    M_21a0 m;
    ~D_21a0() {}
};

/* @implements 0x0621a0 us f_0621a0
   WHAT IT DOES: destructor body: stores vtables D_1a3d60 and D_1a43d0, then destroys the member (f_05db84) and the two bases (f_04e8c0, f_04e8d8). */
void f_0621a0(void *o)
{
    D_21a0 *d = (D_21a0 *)o;
    *(void **)o = D_1a3d60;
    ((B2_21a0 *)d)->vt = D_1a43d0;
    d->~D_21a0();
}

/* @implements 0x064548 us f_064548
   WHAT IT DOES: returns f_12937c(stream, 0) on the buffer at +28 if byte 8 is set, else fetches the next character via f_15c098 or the cached one and returns f_12937c on it. */
int f_064548(void *o)
{
    if (B(o, 8)) {
        char *q = (char *)W(o, 28);
        *(q + W(q, -12)) = D_1a4d14[0];
        return f_12937c((void *)W(o, 28), 0);
    }
    void *r;
    int c = W(o, 16);
    if (c == -1) {
        char **p = (char **)W(o, 24);
        *(*p + W(*p, -12)) = D_1a4d14[0];
        r = *p;
    } else {
        r = f_15c098((void *)W(W(o, 12), 4), 7, c);
    }
    return f_12937c(r, 0);
}

/* @implements 0x06264c us f_06264c
   WHAT IT DOES: returns f_129590(stream, 0, 0) on the buffer at +28 if byte 8 is set, else fetches the next character via f_15c098 or the cached one and returns f_129590 on it. */
int f_06264c(void *o)
{
    if (B(o, 8)) {
        char *q = (char *)W(o, 28);
        *(q + W(q, -12)) = D_1a4d14[0];
        return f_129590((void *)W(o, 28), 0, 0);
    }
    void *r;
    int c = W(o, 16);
    if (c == -1) {
        char **p = (char **)W(o, 24);
        *(*p + W(*p, -12)) = D_1a4d14[0];
        r = *p;
    } else {
        r = f_15c098((void *)W(W(o, 12), 4), 7, c);
    }
    return f_129590(r, 0, 0);
}

/* @draft 0x065060 us f_065060
   WHAT IT DOES: allocates a string buffer for a capacity (rounded to the allocator size classes, calling f_1312d4 on overflow) and returns it. */
void *f_065060(unsigned cap)
{
    if (cap > 0x3ffffffc)
        f_1312d4(D_1a3370);
    unsigned adj = cap + 29;
    if (adj > 4096) {
        cap += (-(adj & 0xfff)) & 0xfff;
    } else if (cap + 13 > 128) {
        cap += (-(adj & 0x7f)) & 0x7f;
    }
    int *p = (int *)f_04dfa0(cap + 13);
    p[1] = cap;
    p[0] = 0;
    p[2] = 0;
    return p;
}

struct Hdr65b30 {
    int w0;
    void *hdr;
    int cnt;
    ~Hdr65b30() { f_04e4b4(hdr); }
};
struct Base65b30 {
    void *vt;
    int w[5];
    ~Base65b30() { f_04e8d8(this); }
};
struct Tr65b30 : Base65b30 {
    Hdr65b30 m;
    ~Tr65b30() {
        vt = D_1a3698;
        if (m.cnt) {
            f_04ee68(&m, W(m.hdr, 4));
            m.cnt = 0;
            W(m.hdr, 8) = (int)m.hdr;
            W(m.hdr, 4) = 0;
            W(m.hdr, 12) = (int)m.hdr;
        }
    }
};

/* @draft 0x065b30 us f_065b30
   WHAT IT DOES: destructor of the tree container: empties the tree and frees its header node. */
void f_065b30(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
}

/* @draft 0x065e10 us f_065e10
   WHAT IT DOES: destructor of the tree container (twin of f_065b30): empties the tree and frees its header node. */
void f_065e10(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
}

/* @draft 0x065bd4 us f_065bd4
   WHAT IT DOES: deleting destructor of the tree container: runs the destructor, then calls f_05db44(self). */
void f_065bd4(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
    f_05db44(o);
}

/* @draft 0x065eb4 us f_065eb4
   WHAT IT DOES: deleting destructor of the tree container (twin of f_065bd4): runs the destructor, then calls f_05db44(self). */
void f_065eb4(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
    f_05db44(o);
}

struct T44 {
    void *vt;
    int w[10];
};

/* @draft 0x061ee0 us f_061ee0
   WHAT IT DOES: assignment copy of a range of 44-byte records from [first, last) to res, returning the end of res. */
T44 *f_061ee0(T44 *first, T44 *last, T44 *res)
{
    for (; first != last; ++first, ++res) {
        if (res) {
            res->w[0] = first->w[0];
            res->w[1] = first->w[1];
            res->w[2] = first->w[2];
            res->w[3] = first->w[3];
            res->w[4] = first->w[4];
            res->w[5] = first->w[5];
            res->w[6] = first->w[6];
            res->w[7] = first->w[7];
            res->w[8] = first->w[8];
            res->w[9] = first->w[9];
            res->vt = D_1a4868;
        }
    }
    return res;
}

struct T56 {
    int w[14];
};

/* @draft 0x061e30 us f_061e30
   WHAT IT DOES: assignment copy of a range of 56-byte records from [first, last) to res, returning the end of res. */
T56 *f_061e30(T56 *first, T56 *last, T56 *res)
{
    for (; first != last; ++first, ++res) {
        if (res)
            *res = *first;
    }
    return res;
}

/* @implements 0x0636fc us f_0636fc
   WHAT IT DOES: walks the pointer vector at +36..+40; for each non-null item either calls f_15fb50(item, 0) or f_15ea7c(owner at +24, item) depending on byte 340 of the item, then calls f_15fb50 again if that byte is set. */
void f_0636fc(void *o)
{
    It2 it; it.p = (void **)W(o, 36);
    It2 e; e.p = (void **)W(o, 40);
    for (; it != e; ++it) {
        if (*it) {
            if (B(*it, 340))
                f_15fb50(*it, 0);
            else
                f_15ea7c((void *)W(o, 24), *it);
            if (B(*it, 340))
                f_15fb50(*it, 0);
        }
    }
}

/* @implements 0x063bec us f_063bec
   WHAT IT DOES: asks the argument (virtual slot 24) for a double r; if f_164a28(r, 0.0) is non-zero divides the double at +8 by r, else prints it with iprintf and sets it to D_1a4d28. */
void f_063bec(void *o, void *a)
{
    double r = ((dfn_t *)*(void **)a)[24](a);
    if (f_164a28(r, 0.0) != 0) {
        DBL(o, 8) = DBL(o, 8) / r;
    } else {
        iprintf(D_1a32dc, DBL(o, 8));
        DBL(o, 8) = D_1a4d28;
    }
}

/* @draft 0x062050 us f_062050
   WHAT IT DOES: string replace: checks the new length against the limit (f_1312d4 on overflow), calls f_060920 to open a gap at the iterator position, memcpy's the new characters in and returns self. */
void *f_062050(char **self, char *i1, char *i2, char *k1, char *k2)
{
    unsigned n2 = k2 - k1;
    unsigned n1 = i2 - i1;
    if (n2 < 0x3ffffffcU) {
    } else {
        f_1312d4(D_1a30b4);
    }
    int pos = i1 - *self;
    f_060920(self, pos, n1, n2);
    if (n2)
        memcpy(*self + pos, k1, n2);
    return self;
}

/* @draft 0x0616fc us f_0616fc
   WHAT IT DOES: ordered-tree unique insert: looks up key and, if absent, inserts a new node via f_06523c/f_064d8c; writes the iterator and a was-inserted flag to out. */
InsRes *f_0616fc(InsRes *out, char *t, void *key)
{
    char *x;
    char *y = (char *)W(t, 4);
    x = (char *)W(y, 4);
    int comp = 1;
    while (x) {
        y = x;
        comp = f_05dcb8(key, x + 16) & 0xff;
        x = (char *)(comp ? W(x, 8) : W(x, 12));
    }
    NodeIt j;
    j.n = y;
    if (comp) {
        NodeIt lm;
        lm.n = (void *)W(W(t, 4), 8);
        if (j.n != lm.n)
            f_064c6c((char **)&j);
        else
            goto ins;
    }
    if (!(f_05dcb8((char *)j.n + 16, key) & 0xff)) {
        out->ok = 0;
        out->it = j.n;
        return out;
    }
ins:
    {
        NodeIt r;
        f_06523c(&r, t, x, y, key);
        out->ok = 1;
        out->it = r.n;
    }
    return out;
}

/* @draft 0x061528 us f_061528
   WHAT IT DOES: ordered-tree unique insert (twin of f_0616fc): looks up key and, if absent, inserts a new node; writes the iterator and a was-inserted flag to out. */
InsRes *f_061528(InsRes *out, char *t, void *key)
{
    char *x;
    char *y = (char *)W(t, 4);
    x = (char *)W(y, 4);
    int comp = 1;
    while (x) {
        y = x;
        comp = f_05dcb8(key, x + 16) & 0xff;
        x = (char *)(comp ? W(x, 8) : W(x, 12));
    }
    NodeIt j;
    j.n = y;
    if (comp) {
        NodeIt lm;
        lm.n = (void *)W(W(t, 4), 8);
        if (j.n != lm.n)
            f_064c6c((char **)&j);
        else
            goto ins;
    }
    if (!(f_05dcb8((char *)j.n + 16, key) & 0xff)) {
        out->ok = 0;
        out->it = j.n;
        return out;
    }
ins:
    {
        NodeIt r;
        f_064d8c(&r, t, x, y, key);
        out->ok = 1;
        out->it = r.n;
    }
    return out;
}

extern char D_1a3e10[];
extern char D_1a4888[];
extern char D_1a3e50[];
void f_0606a0(void *a, void *b, int c);
void f_060670(void *p);

struct VB4888 { ~VB4888() { *(void **)this = D_1a4888; } };
struct D0622bc : VB4888 {
    ~D0622bc() {
        Tmp16 tt;
        *(void **)this = D_1a3e10;
        void *c = (void *)W(this, 4);
        ((int (*)(void *, int))((void **)*(void **)c)[3])(c, W(this, 28));
        c = (void *)W(this, 4);
        ((int (*)(void *, int))((void **)*(void **)c)[3])(c, W(this, 12));
        c = (void *)W(this, 4);
        ((int (*)(void *, int))((void **)*(void **)c)[3])(c, W(this, 16));
    }
};

/* @implements 0x0622bc us f_0622bc
   WHAT IT DOES: destructor: stores vtable D_1a3e10, releases three entries (+28, +12, +16) through virtual slot 3 of the object at +4, then stores vtable D_1a4888. */
void f_0622bc(void *o)
{
    ((D0622bc *)o)->~D0622bc();
}

struct M060670 { int w[6]; ~M060670() { f_060670(this); } };
struct D062528 : B04e8d8 {
    int w[6];
    M060670 m;
    ~D062528() {
        M060670 *p = &m;
        *(void **)this = D_1a3e50;
        f_0606a0((void *)W(p, 4), (void *)W(p, 8), 0);
    }
};

/* @draft 0x062528 us f_062528
   WHAT IT DOES: destructor: stores vtable D_1a3e50, calls f_0606a0 on the member at +24, destroys it (f_060670), then destroys the base (f_04e8d8). */
void f_062528(void *o)
{
    ((D062528 *)o)->~D062528();
}

/* @draft 0x062220 us f_062220
   WHAT IT DOES: deleting destructor: same as f_0621a0, then calls f_05db44(self). */
void f_062220(void *o)
{
    D_21a0 *d = (D_21a0 *)o;
    *(void **)o = D_1a3d60;
    ((B2_21a0 *)d)->vt = D_1a43d0;
    d->~D_21a0();
    f_05db44(o);
}

struct Sub44 { int a, b, c; };
struct E44 {
    void *vt; int w1, w2, w3, w4; int b, c; int d1, d2, d3, d4;
};
/* @draft 0x061da4 us f_061da4
   WHAT IT DOES: uninitialized copy: copy-constructs 44-byte records (vtable D_1a4868 plus fields) from [first, last) into dest and returns the end of dest. */
void *f_061da4(char *first, char *last, char *dest)
{
    for (; first != last; first += 44, dest += 44) {
        if (dest) {
            E44 *s = (E44 *)first, *d = (E44 *)dest;
            Sub44 *ss = (Sub44 *)&s->w4, *ds = (Sub44 *)&d->w4;
            d->vt = D_1a4868;
            ds->c = ss->c; ds->b = ss->b;
            d->w1 = s->w1; d->w2 = s->w2; d->w3 = s->w3; d->w4 = s->w4;
            d->d1 = s->d1; d->d2 = s->d2; d->d3 = s->d3; d->d4 = s->d4;
        }
    }
    return dest;
}

/* @draft 0x0625ac us f_0625ac
   WHAT IT DOES: deleting destructor: same as f_062528, then calls f_05db44(self). */
void f_0625ac(void *o)
{
    ((D062528 *)o)->~D062528();
    f_05db44(o);
}

/* @draft 0x062340 us f_062340
   WHAT IT DOES: deleting destructor: same as f_0622bc, then calls f_04e4b4(self). */
void f_062340(void *o)
{
    ((D0622bc *)o)->~D0622bc();
    f_04e4b4(o);
}

/* @draft 0x064c6c us f_064c6c
   WHAT IT DOES: red-black tree iterator increment: moves the node pointer in *it to its in-order successor. */
void f_064c6c(char **it)
{
    char *n = *it;
    char *x;
    if (W(n, 0) == 0 && W(W(n, 4), 4) == (int)n) {
        *it = (char *)W(n, 12);
        return;
    }
    x = (char *)W(n, 8);
    if (x) {
        char *y = x;
        while ((y = (char *)W(y, 12))) x = y;
        *it = x;
        return;
    }
    char *p = (char *)W(n, 4);
    if (W(p, 8) == (int)n) {
        *it = p;
        for (;;) {
            p = (char *)W(p, 4);
            if (*it != (char *)W(p, 8)) break;
            *it = p;
        }
    }
    *it = p;
}

/* @draft 0x060c80 us f_060c80
   WHAT IT DOES: walks a list from *it to *end, calling virtual slot 0 on each element's payload (at +8) and virtual slot 3 of dst with it; returns dst. */
void *f_060c80(int **it, int **end, void *dst)
{
    while (*it != *end) {
        void *e = (void *)(*it)[2];
        ((vfn_t *)*(void **)e)[0](e);
        ((int (*)(void *, void *))((void **)*(void **)dst)[3])(dst, e);
        *it = (int *)**it;
    }
    return dst;
}

void f_065634(void *o, void *a, void *b, void *c);
int f_05c950(void *a, void *b, void *c, int d, int e);
struct L062108 { int w[4]; ~L062108() { f_05db84(this); } };

/* @draft 0x062108 us f_062108
   WHAT IT DOES: builds a temporary via f_065634, then calls f_05c950(a, b, c, t, t + t[-12]) with its first word and returns the result, destroying the temporary (f_05db84). */
int f_062108(void *a, void *b, void *c, void *d, void *e)
{
    L062108 l;
    Tmp16 w2;
    f_065634(&l, d, e, &w2);
    int t = l.w[0];
    return f_05c950(a, b, c, t, t + W(t, -12));
}

extern char D_1a41c0[];
void f_0655dc(void *t, int n);
void f_05f4a0(void *p);
struct HdrA { int a; int hdr; ~HdrA() { f_04e4b4((void *)hdr); } };
struct Tree063 : HdrA {
    int cnt;
    ~Tree063() {
        if (cnt) {
            f_0655dc(this, W(hdr, 4));
            cnt = 0;
            W(hdr, 8) = hdr;
            W(hdr, 4) = 0;
            W(hdr, 12) = hdr;
        }
    }
};
struct M05f4a0 { int w[4]; ~M05f4a0() { f_05f4a0(this); } };
struct D06357c : B04e8d8 {
    int w[8];
    M05f4a0 m;
    Tree063 t;
    ~D06357c() { *(void **)this = D_1a41c0; }
};

/* @draft 0x06357c us f_06357c
   WHAT IT DOES: destructor: stores vtable D_1a41c0, empties the tree member at +48 (f_0655dc, reset header), frees its header (f_04e4b4), destroys the member at +32 (f_05f4a0) and the base (f_04e8d8). */
void f_06357c(void *o)
{
    ((D06357c *)o)->~D06357c();
}

struct E56 {
    int w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10, w11, w12, w13;
};
/* @draft 0x061f88 us f_061f88
   WHAT IT DOES: uninitialized copy: copies 56-byte records from [first, last) into dest and returns the end of dest. */
void *f_061f88(char *first, char *last, char *dest)
{
    for (; first != last; first += 56, dest += 56) {
        if (dest) {
            E56 *s = (E56 *)first, *d = (E56 *)dest;
            Sub44 *ss = (Sub44 *)&s->w3, *ds = (Sub44 *)&d->w3;
            ds->c = ss->c;
            d->w0 = s->w0; d->w1 = s->w1; d->w2 = s->w2; d->w3 = s->w3;
            ds->b = ss->b;
            d->w6 = s->w6; d->w7 = s->w7; d->w8 = s->w8; d->w9 = s->w9;
            d->w10 = s->w10; d->w11 = s->w11; d->w12 = s->w12; d->w13 = s->w13;
        }
    }
    return dest;
}

void f_05df24(void *d, void *s);
void f_04ed28(void *p);
struct Rng8 { char *b; char *c; };
/* @draft 0x065670 us f_065670
   WHAT IT DOES: vector erase of [first, last) with 8-byte elements: assigns the tail down with f_05df24, destroys the vacated elements with f_04ed28, shrinks the end pointer at +8 and returns first. */
char *f_065670(void *v, char *first, char *last)
{
    char *s = last;
    char *d = first;
    int n = (W(v, 8) - (int)last) >> 3;
    for (; n > 0; --n) {
        f_05df24(d, s);
        s += 8; d += 8;
    }
    char *end = (char *)W(v, 8);
    Rng8 r; r.b = d; r.c = d;
    char *c = r.c;
    while (c != end) {
        f_04ed28(c);
        r.c += 8;
        c = r.c;
    }
    W(v, 8) = W(v, 8) - (((last - first) >> 3) << 3);
    return first;
}

void f_05e4a8(void *s, int a);
void f_05fadc(void *a, void *b);
void f_05c8d0(void *a, void *b);
/* @draft 0x0645e0 us f_0645e0
   WHAT IT DOES: on first call (flag byte 8) builds a string from the cached character or f_15c098/f_05e4a8 and stores it at +28 via f_05fadc; then builds a string through virtual slot 21 of the argument and stores it at +28 via f_05c8d0. */
void f_0645e0(void *o, void *a)
{
    char *p = (char *)o + 28;
    if (!B(o, 8)) {
        char *q = p;
        int c = W(o, 16);
        B(o, 8) = 1;
        L062108 s;
        if (c == -1) {
            f_05e4a8(&s, W(o, 24));
        } else {
            Tmp16 t;
            f_05a3e8(&s, (char *)f_15c098((void *)W(W(o, 12), 4), 7, c), &t);
        }
        f_05fadc(q, &s);
    }
    L062108 s2;
    ((void (*)(void *, void *))((void **)*(void **)a)[21])(&s2, a);
    f_05c8d0(p, &s2);
}

}
}

/* ---- swg4e ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg4e: untagged functions of the SWG player (rest_e). */

namespace swg4e {


extern "C" {
void *f_04dfa0(unsigned n);
void *f_05db08(unsigned n);
void f_05daa4(void *self, void *a1);
void f_05db44(void *);
double f_1259cc(void);
int f_06b624(void *, void *, void *);
void f_15f714(void *, void *);
void f_15f6f8(void *);
extern char D_1a4320[];
extern char D_1a4270[];
extern char D_1a4060[];
int f_15e0f4(void *);
void f_15f190(void *, float *, float *);
void f_15f1bc(void *, float *, float *);
double f_11c6d8(double, double);
double f_11cd44(double, double);
void f_068bc0(void *, void *, int);
void f_068e6c(void *, void *, int);
int f_15c278(void *, int);
}

struct Ref { int a, b; Ref(void *p); ~Ref() {} };
inline Ref::Ref(void *p) { f_05daa4(this, p); }
struct NumD {
    void *vt; int z; double d;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumD(double x) { vt = (void *)D_1a4270; d = x; z = 0; }
};
struct NumI {
    void *vt; int z; int v;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumI(int x) { vt = (void *)D_1a4320; v = x; z = 0; }
};
extern "C" {
double f_11c448(double);
double f_11c590(double);
double f_11b514(double);
double f_11bafc(double);
double f_11bce8(double);
double f_11c848(double);
double f_11be14(double);
double f_11cba8(double);
double f_11c018(double);
double f_11d280(double);
double f_11c12c(double);
}

inline double vc(char *obj) {
    void *a = **(void ***)(obj + 52);
    return ((double (*)(void *))((void **)*(void **)a)[24])(a);
}

extern "C" {
int f_15e128(void *);
}

inline double vc2(char *obj) {
    void *a = ((void **)*(void **)(obj + 52))[2];
    return ((double (*)(void *))((void **)*(void **)a)[24])(a);
}

inline void *vc9(char *obj) {
    void *v = *(void **)(obj + 44);
    return ((void *(*)(void *))((void **)*(void **)v)[9])(v);
}

struct NumB {
    void *vt; int z; char b;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumB(char x) { vt = (void *)D_1a4060; b = x; z = 0; }
};
struct Ref0 { int a, b; ~Ref0() {} };
struct H { int a; int *rc; H(const H &o) { a = o.a; rc = o.rc; if (rc) ++*rc; } };
struct V { int w0, w1, w2, w3, w4, w5; int *rc; V(const V &o) { int *r = o.rc; w0 = o.w0; w1 = o.w1; w2 = o.w2; w3 = o.w3; w4 = o.w4; w5 = o.w5; rc = r; if (rc) ++*rc; } };
struct N { int l, r, p, q; V v; };
inline void *operator new(unsigned, void *p) throw() { return p; }
struct Num {
    void *vt; int z; double d;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    Num() { double t = f_1259cc(); vt = (void *)D_1a4270; d = t; z = 0; }
};

extern "C" {

double f_11c448(double);
double f_11c590(double);
double f_11b514(double);
double f_11bafc(double);
double f_11bce8(double);
double f_11c848(double);
double f_11be14(double);
double f_11cba8(double);
double f_11c018(double);
double f_11d280(double);
double f_11c12c(double);

struct Sx3 { int a, b, c; };
struct Pa { };
typedef Sx3 (Pa::*PMf)(void *);
extern PMf D_1d3068[];
struct Xi { int p[3]; int idx; };
/* @draft 0x066c60 us f_066c60
   WHAT IT DOES: looks up a pointer-to-member-function in the table D_1d3068 indexed by the field at +12 of the third argument and calls it on the second argument (adjusted by the stored delta, virtual dispatch when the delta's low bit is set) with the first argument passed through; returns the struct result. Remaining difference: callee pointer lives in v0 instead of v1 (7 of 31 words). */
Sx3 f_066c60(Pa *a, void *u, Xi *x) {
    PMf m = D_1d3068[x->idx];
    return (a->*m)(u);
}

struct It4 { int *p; It4() {} It4(const It4 &o) { p = o.p; } void inc() { p = (int *)*p; } It4 &operator=(const It4 &o) { p = o.p; return *this; } };
void f_05f64c(void *, void *, void *);
/* @draft 0x069ea0 us f_069ea0
   WHAT IT DOES: walks the circular list headed at the sentinel in field +4 and erases (f_05f64c) every node whose value at +8 equals the key pointed to by the second argument. Remaining difference: iterator temporaries stack layout (22 of 34 words). */
void f_069ea0(int *l, int **k) {
    It4 first; It4 end; It4 tmp[4]; It4 arg;
    end.p = (int *)l[1];
    first.p = (int *)*end.p;
    while (first.p != end.p) {
        It4 nx(first);
        nx.inc();
        if (*k == (int *)first.p[2]) { arg = first; f_05f64c(tmp, l, &arg); }
        first = nx;
    }
}

char *f_05f0b8(void *, void *);
/* @draft 0x068808 us f_068808
   WHAT IT DOES: returns a reference-counted handle copied from the entry the player's object at +40 holds for the key (virtual slot 9 of the +44 object, field +20): looked up through f_05f0b8 when the key is non-zero, otherwise the default handle at +280; the count is incremented. Remaining difference: the loads are after the join instead of in each branch (21 of 36 words). */
H f_068808(char *self, char *o) {
    void *v = *(void **)(o + 44);
    char *w = ((char *(*)(void *))((void **)*(void **)v)[9])(v);
    int k = *(int *)(w + 20);
    H *s;
    if (k) s = (H *)(f_05f0b8(*(char **)(o + 40) + 348, &k) + 16);
    else s = (H *)(*(char **)(o + 40) + 280);
    return *s;
}

void f_05f5dc(void *, void *, void *);
void *f_05cc58(void *, void *, void *, void *);
void f_04e4b4(void *);
/* @implements 0x06b050 us f_06b050
   WHAT IT DOES: finds the node for the key in the tree at +48 (f_05f5dc); if found, clears the slot of the table at +36 indexed by the node's field +20 when it still holds the key, unlinks the node (f_05cc58), frees it (f_04e4b4) and decrements the tree's count at +8. */
void f_06b050(char *self, int k) {
    It4 out; It4 end; It4 c1; It4 c2;
    char *t = self + 48;
    f_05f5dc(&out, t, &k);
    int *hdr = *(int **)(t + 4); int *n = out.p;
    end.p = hdr;
    if (n != hdr) {
        int **slot = (int **)(*(char **)(self + 36) + n[5] * 4);
        if ((int)*slot == k) *slot = 0;
        c1.p = n;
        c2.p = n;
        f_04e4b4(f_05cc58(n, hdr + 1, hdr + 2, hdr + 3));
        --*(int *)(t + 8);
    }
}

struct Sx { int w[4]; Sx(const Sx &o) { w[0] = o.w[0]; } };
struct Q2 {
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
 virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
 virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
 virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual Sx s20(void *); virtual void s21(); virtual void s22(); virtual int s23();
};
void f_06b0f0(void *, int, void *, int);
/* @implements 0x067cbc us f_067cbc
   WHAT IT DOES: calls virtual slot 20 of the object at +52 (with the object at +40, result into a local), virtual slot 23 of its second element, and passes the slot-9 result of the +44 object, the local and that value with the +40 object to f_06b0f0; returns an empty reference through f_05daa4. */
Ref f_067cbc(char *o) {
    void *v = *(void **)(o + 44);
    int s1 = ((int (*)(void *))((void **)*(void **)v)[9])(v);
    Q2 *a = **(Q2 ***)(o + 52);
    Sx sp = a->s20(*(void **)(o + 40));
    Q2 *d = ((Q2 **)*(void **)(o + 52))[2];
    int x = d->s23();
    f_06b0f0(*(void **)(o + 40), s1, &sp, x);
    return Ref(0);
}

void f_05db84(void *);
void f_15fb94(int, int);
extern char D_1a4d14[];
struct Sd { int w[4]; ~Sd() { f_05db84(this); } };
struct Q {
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
 virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
 virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
 virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
 virtual void s20(); virtual Sd s21();
};
/* @implements 0x068248 us f_068248
   WHAT IT DOES: obtains the output stream object from virtual slot 21 of the object at +52, stores the character at D_1a4d14 into its virtual base, passes the slot-9 result of the +44 object and the stream to f_15fb94, destroys the stream (f_05db84) and returns an empty reference. */
Ref f_068248(char *o) {
    void *v = *(void **)(o + 44);
    int s1 = ((int (*)(void *))((void **)*(void **)v)[9])(v);
    Q *a = **(Q ***)(o + 52);
    {
        Sd sp = a->s21();
        int *vt = (int *)sp.w[0];
        *((char *)vt + vt[-3]) = D_1a4d14[0];
        f_15fb94(s1, sp.w[0]);
    }
    return Ref(0);
}

struct Pv { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(const void *); };
extern char D_1a2e9c[];
inline const void *sdstr(const Sd &s) {
    int *vt = (int *)s.w[0];
    *((char *)vt + vt[-3]) = D_1a4d14[0];
    return (const void *)s.w[0];
}
/* @implements 0x0674e8 us f_0674e8
   WHAT IT DOES: if the object at +228 of the one at +56 exists, calls its virtual slot 4 with a string: when the count at +48 is positive, the text of a stream obtained from virtual slot 21 of the +52 object (a character stored into its virtual base), otherwise the constant string D_1a2e9c; the temporary stream is destroyed afterwards; returns an empty reference. */
Ref f_0674e8(char *o) {
    Pv *p = *(Pv **)(*(char **)(o + 56) + 228);
    if (p) {
        p->s4(*(int *)(o + 48) > 0 ? sdstr((**(Q ***)(o + 52))->s21()) : (const void *)D_1a2e9c);
    }
    return Ref(0);
}

extern double D_1a4d30;
/* @implements 0x0675cc us f_0675cc
   WHAT IT DOES: with the slot-9 result of the +44 object: when the flag is zero returns a reference to a new double object holding the float at +140 times 100; otherwise stores the slot-24 value of the +52 object divided by 100 into the float at +140 and returns an empty reference. */
Ref f_0675cc(char *o, int flag) {
    char *s = (char *)vc9(o);
    if (flag == 0) {
        return Ref(new NumD(*(float *)(s + 140) * 100.0f));
    }
    *(float *)(s + 140) = (float)(vc(o) / D_1a4d30);
    return Ref(0);
}

struct T64 { float x; float pad[4]; float y; };
/* @implements 0x069538 us f_069538
   WHAT IT DOES: reads the two floats at +64 and +84 of the slot-9 object of the +44 object; with a zero flag returns a reference to a new double object holding the first, otherwise stores the slot-24 value of the +52 object as the first float, writes the second back and returns an empty reference. */
Ref f_069538(char *o, int flag) {
    char *s = (char *)vc9(o);
    T64 *t = (T64 *)(s + 64);
    float x = t->x;
    float y = t->y;
    if (flag == 0) return Ref(new NumD(x));
    t->x = (float)vc(o);
    t->y = y;
    return Ref(0);
}
/* @implements 0x0697b4 us f_0697b4
   WHAT IT DOES: as f_069538 with the roles of the two floats swapped: the second float (+84) is read or replaced by the slot-24 value and the first (+64) is written back unchanged. */
Ref f_0697b4(char *o, int flag) {
    char *s = (char *)vc9(o);
    T64 *t = (T64 *)(s + 64);
    float x = t->x;
    float y = t->y;
    if (flag == 0) return Ref(new NumD(y));
    t->y = (float)vc(o);
    t->x = x;
    return Ref(0);
}

float cosf(float);
float sinf(float);
/* @implements 0x06898c us f_06898c
   WHAT IT DOES: with a zero flag returns a reference to a new double object holding the angle float at +160 of the slot-9 object; otherwise stores the slot-24 value of the +52 object there, converts degrees to radians and writes the 2x2 rotation (cos, sin, -sin, cos) into the matrix floats at +64. */
Ref f_06898c(char *o, int flag) {
    char *s = (char *)vc9(o);
    if (flag == 0) return Ref(new NumD(*(float *)(s + 160)));
    float *m = (float *)(s + 64);
    float a = (float)vc(o);
    m[24] = a;
    float r = a * 3.1415927f / 180.0f;
    float c = cosf(r);
    float sn = sinf(r);
    m[5] = c;
    m[0] = c;
    m[1] = sn;
    m[4] = -sn;
    return Ref(0);
}

void f_04ed28(void *);
void f_0678b0(void *, void *, void *, void *, int, void *);
struct Hd {
    int a; int *rc;
    Hd(void *p) { f_05daa4(this, p); }
    Hd(const Hd &o) { a = o.a; rc = o.rc; if (rc) ++*rc; }
    ~Hd() { f_04ed28(this); }
};
/* @implements 0x067788 us f_067788
   WHAT IT DOES: builds two stream-like results from virtual slot 20 of the first and third elements of the +52 table (with the +40 object), takes the slot-23 value of its fifth element, makes a handle (a copy of the one at +24 of the table when the mode at +48 is 4, otherwise empty) and passes everything with the +40 and +44 objects to f_0678b0; destroys the handle and returns an empty reference. */
Ref f_067788(char *o) {
    void **tb = *(void ***)(o + 52);
    Q2 *a = (Q2 *)tb[0];
    Sx sp0 = a->s20(*(void **)(o + 40));
    Q2 *b = (Q2 *)((void **)*(void **)(o + 52))[2];
    Sx sp16 = b->s20(*(void **)(o + 40));
    Q2 *d = (Q2 *)((void **)*(void **)(o + 52))[4];
    int x = d->s23();
    {
        Hd h = (*(int *)(o + 48) == 4) ? Hd(*(Hd *)((char *)*(void **)(o + 52) + 24)) : Hd(0);
        f_0678b0(*(void **)(o + 40), *(void **)(o + 44), &sp0, &sp16, x, &h);
    }
    return Ref(0);
}

extern double D_1a4d68;
int f_164e34(double);
/* @implements 0x06ac38 us f_06ac38
   WHAT IT DOES: takes the slot-24 value of the +52 object, rounds it to an integer (floor, plus one when the fractional part is at least D_1a4d68) and returns a reference to a new integer object holding it. */
Ref f_06ac38(char *o) {
    double d = vc(o);
    double fl = f_11be14(d);
    int i = f_164e34(fl);
    if (d - fl >= D_1a4d68) return Ref(new NumI(i + 1));
    return Ref(new NumI(i));
}

void *f_154448(void *, void *, void *, int);
void f_15f10c(void *, void *, int);
int f_15f11c(void *, void *);
void f_06b4a4(void *, void *, int, int, int);
extern char D_1a4900[];
extern char D_1a4960[];
struct Ob48 {
    char b[48];
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    Ob48(char *o, int c, int d, int e) { f_06b4a4(this, *(void **)(o + 40), c, d, e); }
};
/* @draft 0x0698e4 us f_0698e4
   WHAT IT DOES: with a non-zero flag, runs a dynamic cast of the first element of the +52 table and passes the slot-9 object, the argument and the cast result's field +28 (or -1) to f_15f10c, returning an empty reference; with a zero flag, returns a reference to a new 48-byte object built by f_06b4a4 from the +40 object and the f_15f11c conversion of the argument. */
Ref f_0698e4(char *o, int flag, void *arg) {
    void *s = vc9(o);
    if (flag) {
        void *t = **(void ***)(o + 52);
        char *r;
        if (t && (r = (char *)f_154448(t, D_1a4900, D_1a4960, 0))) f_15f10c(s, arg, *(int *)(r + 28));
        else f_15f10c(s, arg, -1);
        return Ref(0);
    }
    return Ref(new Ob48(o, f_15f11c(s, arg), 0, 0));
}

struct Rn { int color; Rn *parent; Rn *left; Rn *right; };
void f_064cfc(Rn *, Rn **);
void f_064d44(Rn *, Rn **);
/* @implements 0x066cdc us f_066cdc
   WHAT IT DOES: red-black tree rebalance after an insert: colours the new node red, then repeatedly recolours or rotates (f_064cfc left, f_064d44 right) while its parent is red, and finally colours the root black. */
void f_066cdc(Rn *x, Rn **root) {
    x->color = 0;
    while (x != *root && x->parent->color == 0) {
        if (x->parent == x->parent->parent->left) {
            Rn *y = x->parent->parent->right;
            if (y && y->color == 0) {
                x->parent->color = 1;
                y->color = 1;
                x->parent->parent->color = 0;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    f_064cfc(x, root);
                }
                x->parent->color = 1;
                x->parent->parent->color = 0;
                f_064d44(x->parent->parent, root);
            }
        } else {
            Rn *y = x->parent->parent->left;
            if (y && y->color == 0) {
                x->parent->color = 1;
                y->color = 1;
                x->parent->parent->color = 0;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    f_064d44(x, root);
                }
                x->parent->color = 1;
                x->parent->parent->color = 0;
                f_064cfc(x->parent->parent, root);
            }
        }
    }
    (*root)->color = 1;
}

extern char D_1a4990[];
inline int vc2i(char *obj) {
    void *a = ((void **)*(void **)(obj + 52))[2];
    return ((int (*)(void *))((void **)*(void **)a)[23])(a);
}
struct Pw {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(const void *, int, float);
};
/* @implements 0x067390 us f_067390
   WHAT IT DOES: when the object at +228 of the +56 object and the +44 object both exist and the +44 object dynamic-casts to the target class, obtains the text of a stream from its virtual slot 21 (a character stored into the stream's virtual base), reads an optional float (the slot-24 value when the count at +48 is positive) and an integer (1, or the slot-23 value when the count is at least 2), and passes text, integer and float to virtual slot 3 of the +228 object; destroys the stream and returns an empty reference. */
Ref f_067390(char *o) {
    Pw *p = *(Pw **)(*(char **)(o + 56) + 228);
    if (p && *(void **)(o + 44)) {
        char *r = (char *)f_154448(*(void **)(o + 44), D_1a4900, D_1a4990, 0);
        if (r) {
            Sd sp = ((Q *)(r + 24))->s21();
            int *vt = (int *)sp.w[0];
            *((char *)vt + vt[-3]) = D_1a4d14[0];
            const void *str = (const void *)sp.w[0];
            float f = 0.0f;
            if (*(int *)(o + 48) > 0) f = (float)vc(o);
            int a = *(int *)(o + 48) < 2 ? 1 : vc2i(o);
            p->s3(str, a, f);
        }
    }
    return Ref(0);
}

inline int vc2323(char *obj) {
    void *a = **(void ***)(obj + 52);
    return ((int (*)(void *))((void **)*(void **)a)[23])(a);
}
inline int iabs(int v) { return v < 0 ? -v : v; }
/* @implements 0x069f28 us f_069f28
   WHAT IT DOES: absolute value of the number held by the +52 object: when its type code (virtual slot 6) is 6 returns a reference to a new double object holding the absolute value of the slot-24 value, otherwise to a new integer object holding the absolute value of the slot-23 value. */
Ref f_069f28(char *o) {
    void *a = **(void ***)(o + 52);
    if (((int (*)(void *))((void **)*(void **)a)[6])(a) == 6) {
        double d = vc(o);
        if (d >= 0.0) return Ref(new NumD(d));
        return Ref(new NumD(-d));
    }
    return Ref(new NumI(iabs(vc2323(o))));
}
}}

/* ---- swg4a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment by worker swg4a. */
namespace swg4a {

extern "C" {
extern int D_241000, D_241008;
extern void *D_241004;
extern unsigned D_291680, D_291420, D_291410, D_291424, D_291744, D_291748, D_29166c, D_29174c, D_291668;
extern unsigned *D_291690;
void *f_153558(unsigned) __asm__("_Znaj");
int f_04d82c(int);
void *memset(void *, int, unsigned);
int f_046c8c(void *, int);
void f_046de0a(void *, int, int, int, int, int, float, float, float, float) __asm__("f_046de0");
void f_0477b0a(void *, int, int, int, int, int, float, float, float, float) __asm__("f_0477b0");
void f_04e4b4(void *);
void f_15b670(void *);
#define VC(o, k) ((*(void (***)(void *))(o))[k](o))
void f_024aec(int);
void *f_021b38(int);
void f_118d04(int, int, int, int);
void f_116dfc(int, int, int, int, void *);
void *memcpy(void *, const void *, unsigned);
void f_021720(void) throw();
void f_021750(void) throw();
void f_045400(void *) throw();
void f_04559c(void *) throw();
int f_0216d8(void) throw();
void f_0216e8(int) throw();
int f_0e71d4(int, void *) throw();
int f_0e7114(int, void *) throw();
int f_045f8c(void *, void *, int, int) throw();


/* @draft 0x04c3c8 us f_04c3c8
   WHAT IT DOES: offsets the four corner points of entry a1 by (x,y) and stores the scaled min x and max x. */
void f_04c3c8(char *s, int a1, float x, float y) {
    if (*(int *)(s + 32) < a1) return;
    float *f = (float *)(*(char **)(s + 36) + a1 * 172);
    for (int i = 0; i < 4; i++) {
        f[2 + 5 * i] = f[23 + i] + x;
        f[3 + 5 * i] = f[27 + i] + y;
    }
    char *e = (char *)f;
    float lo = f[2];
    if (f[7] < lo) lo = f[7];
    if (f[12] < lo) lo = f[12];
    if (f[17] < lo) lo = f[17];
    *(int *)(e + 80) = (int)(lo * 0.015625f);
    float hi = f[2];
    if (hi < f[7]) hi = f[7];
    if (hi < f[12]) hi = f[12];
    if (hi < f[17]) hi = f[17];
    *(int *)(e + 84) = (int)((hi + 1.0f) * 0.015625f);
}

/* @implements 0x04d548 us f_04d548
   WHAT IT DOES: runs the f_0216d8 bracketed pass over the entries of the 172-byte array, dispatching each by its flags to f_045f8c, f_0e7114 or f_0e71d4, then closes with f_0216e8. */
void f_04d548(char *s) {
    int loc[4];
    int v, i;
    unsigned char *e;
    f_021720();
    f_045400(loc);
    f_021750();
    e = *(unsigned char **)(s + 36);
    v = f_0216d8();
    for (i = 0; i < *(int *)(s + 32); i++, e += 172) {
        if (e[136]) {
            v = f_045f8c(loc, e, *(int *)(s + 52), v);
        } else if (e[164] == 1) {
            v = f_0e7114(v, e);
        } else if (e[164] == 2) {
            v = f_0e71d4(v, e);
        }
    }
    f_0216e8(v);
    f_021720();
    f_04559c(loc);
    f_021750();
}

/* @draft 0x04c278 us f_04c278
   WHAT IT DOES: shifts the four corner points of entry a1 so the first lands at (x,y), then stores the scaled min x at +80 and the scaled max x plus one at +84. */
void f_04c278(char *s, int a1, float x, float y) {
    if (*(int *)(s + 32) >= a1) {
    char *e = *(char **)(s + 36) + a1 * 172;
    float *f = (float *)e;
    x -= f[23]; y -= f[27];
    for (int i = 0; i < 4; i++) {
        f[2 + 5 * i] = f[23 + i] + x;
        f[3 + 5 * i] = f[27 + i] + y;
    }
    float lo = f[2];
    if (f[7] < lo) lo = f[7];
    if (f[12] < lo) lo = f[12];
    if (f[17] < lo) lo = f[17];
    *(int *)(e + 80) = (int)(lo * 0.015625f);
    float hi = f[2];
    if (hi < f[7]) hi = f[7];
    if (hi < f[12]) hi = f[12];
    if (hi < f[17]) hi = f[17];
    *(int *)(e + 84) = (int)((hi + 1.0f) * 0.015625f);
    }
}
/* @draft 0x04bf6c us f_04bf6c
   WHAT IT DOES: loads the four corner points of entry a1 from the 16-byte records at a2 (floats plus truncated shorts), then stores the scaled min x at +80 and max x plus one at +84. */
void f_04bf6c(char *s, int a1, float *p) {
    if (*(int *)(s + 32) >= a1) {
    char *e = *(char **)(s + 36) + a1 * 172;
    float *f = (float *)e;
    for (int i = 0; i < 4; i++) {
        ((short *)f)[10 * i] = (int)p[2];
        f[2 + 5 * i] = p[0];
        ((short *)f)[10 * i + 1] = (int)p[3];
        f[3 + 5 * i] = p[1];
        p += 4;
    }
    float lo = f[2];
    if (f[7] < lo) lo = f[7];
    if (f[12] < lo) lo = f[12];
    if (f[17] < lo) lo = f[17];
    *(int *)(e + 80) = (int)(lo * 1.0f);
    float hi = f[2];
    if (hi < f[7]) hi = f[7];
    if (hi < f[12]) hi = f[12];
    if (hi < f[17]) hi = f[17];
    *(int *)(e + 84) = (int)((hi + 1.0f) * 1.0f);
    }
}

/* @implements 0x045e58 us f_045e58
   WHAT IT DOES: when the cached value at offset 0 differs from the one at 124 of the descriptor a1, calls f_024aec and updates it; copies the 80-byte descriptor into a block from f_021b38 and, for each index from a1[80] up to a1[84], calls f_118d04 and f_116dfc; returns 0. */
int f_045e58(int *s, char *a1) {
    if (*s != *(int *)(a1 + 124)) {
        f_024aec(*(int *)(a1 + 124));
        *s = *(int *)(a1 + 124);
    }
    void *t = f_021b38(80);
    __builtin_memcpy(t, a1, 80);
    int i = *(int *)(a1 + 80);
    if (i < *(int *)(a1 + 84)) {
        do {
            f_118d04(i << 6, 0, 64, 272);
            f_116dfc(4, 0x80019e, 4, 0, t);
            i++;
        } while (i < *(int *)(a1 + 84));
    }
    return 0;
}

/* @draft 0x04c7b8 us f_04c7b8
   WHAT IT DOES: for the 172-byte entry a1, packs four float channels (scaled by 255 and converted to unsigned bytes) from the four arrays a2,a3,t0,t1 into one word per corner at offset 4 + 20*i. */
void f_04c7b8(char *s, int a1, float *r, float *g, float *b, float *a) {
    if (*(int *)(s + 32) >= a1) {
        unsigned *w = (unsigned *)(*(char **)(s + 36) + a1 * 172 + 4);
        for (int i = 0; i < 4; i++) {
            unsigned x = (unsigned char)(unsigned)(r[i] * 255.0f);
            x |= (unsigned)(unsigned char)(unsigned)(g[i] * 255.0f) << 8;
            x |= (unsigned)(unsigned char)(unsigned)(b[i] * 255.0f) << 16;
            x |= (unsigned)(a[i] * 255.0f) << 24;
            *w = x;
            w += 5;
        }
    }
}

/* @draft 0x04b724 us f_04b724
   WHAT IT DOES: tears down the sub-objects owned by the object at s[0]: frees the entry at +236 (clearing its two fields, virtual destructor, f_04e4b4) when s[12] is set, likewise the ones at +228 and +224 under s[8] and s[4], then destroys and frees the object itself, calls virtual slot 1 on the members at +232 and +220 and clears s[0]. */
void f_04b724(char *s) {
    char *p = *(char **)s;
    if (p) {
        char *a = *(char **)(p + 236);
        char *e = *(char **)(p + 220);
        char *c = *(char **)(p + 224);
        char *b = *(char **)(p + 228);
        if (a && *(int *)(s + 12)) {
            if (*(void **)(a + 8)) f_04e4b4(*(void **)(a + 8));
            *(int *)(a + 8) = 0;
            if (*(void **)(a + 12)) f_04e4b4(*(void **)(a + 12));
            *(int *)(a + 12) = 0;
            VC(a, 0);
            f_04e4b4(a);
        }
        if (b && *(int *)(s + 8)) {
            VC(b, 0);
            f_04e4b4(b);
        }
        if (c && *(int *)(s + 4)) {
            VC(c, 0);
            f_04e4b4(c);
        }
        if (p) {
            f_15b670(p);
            f_04e4b4(p);
        }
        void *d = *(void **)(p + 232);
        if (d) VC(d, 1);
        if (e) VC(e, 1);
        *(int *)s = 0;
    }
}

/* @draft 0x049e0c us f_049e0c
   WHAT IT DOES: positions and draws a text/glyph record: truncates the object's x and y at +48/+52, shifts x by the record's width (full for type 20, half for type 40) via f_046c8c, then draws through f_0477b0 (types 0/20/40) or f_046de0 with the object's four colour floats at +64..+76 scaled by the record's four bytes over 255. */
void f_049e0c(char *s, unsigned char *r, int a2, char *o) {
    int x = (int)*(float *)(o + 48);
    int y = (int)*(float *)(o + 52);
    unsigned t = *(unsigned short *)(r + 6);
    if (t == 0) {
        goto A;
    } else if (t == 20) {
        x -= f_046c8c(*(void **)(s + 24), *(int *)r);
        goto A;
    } else if (t == 40) {
        x -= f_046c8c(*(void **)(s + 24), *(int *)r) / 2;
        goto A;
    }
    f_046de0a(*(void **)(s + 24), x, y, *(int *)r, 480, *(int *)(s + 20),
              *(float *)(o + 64) * ((float)r[20] / 255.0f), *(float *)(o + 68) * ((float)r[21] / 255.0f),
              *(float *)(o + 72) * ((float)r[22] / 255.0f), *(float *)(o + 76) * ((float)r[23] / 255.0f));
    return;
A:
    f_0477b0a(*(void **)(s + 24), x, y, *(int *)r, 480, *(int *)(s + 20),
              *(float *)(o + 64) * ((float)r[20] / 255.0f), *(float *)(o + 68) * ((float)r[21] / 255.0f),
              *(float *)(o + 72) * ((float)r[22] / 255.0f), *(float *)(o + 76) * ((float)r[23] / 255.0f));
}

/* @draft 0x0451b4 us f_0451b4
   WHAT IT DOES: one-time init of the SWG player's heap: returns 1 when D_241000 is already set; otherwise allocates the a0-byte arena (f_153558), sets up the 10-bucket free-list table (memset), computes the aligned remaining size and publishes the arena globals, sets D_241000 and returns 0. */
int f_0451b4(unsigned a0) {
    if (D_241000) return 1;
    void *p = f_153558(a0);
    D_241004 = p;
    D_291680 = (unsigned)p;
    D_291424 = 10;
    D_291420 = a0;
    D_291744 = f_04d82c(16) - 1;
    unsigned n = D_291424 << 2;
    D_291690 = (unsigned *)D_291680;
    memset((void *)D_291680, 0, n);
    unsigned e = (D_291680 + n + 15) & ~15u;
    unsigned r = D_291420 - (e - D_291680);
    D_291668 = r;
    D_241008 = a0;
    D_241000 = 1;
    D_29166c = r;
    D_291748 = e;
    D_29174c = 0;
    D_291410 = 0;
    return 0;
}

}
}

/* ---- swg4d ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 wave 3 worker swg4d (rest_d2) */
namespace swg4d {
extern "C" {
struct Tmp16 { int w[4]; ~Tmp16() {} };
struct It2 {
    void **p;
    void *&operator*() { return *p; }
    It2 &operator++() { ++p; return *this; }
    bool operator!=(const It2 &o) const { return p != o.p; }
};
void *f_05db08(unsigned n);
void f_05db44(void *);
void f_04e8c0(void *) throw();
void f_04e8d8(void *);
void f_04e4b4(void *);
void f_04ee68(void *, void *);
void f_05e4a8(void *, void *);
extern char D_1a43d0[];
extern char D_1a3698[];
extern char D_1a41c0[];
}
struct Base0 { void *vt; int z; unsigned char b; int w[4]; ~Base0() { f_04e8c0(this); } };
struct Obj0 : Base0 {
    int s;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    Obj0(Obj0 *o) {
        z = 0;
        vt = D_1a43d0;
        b = ((Base0*)o)->b; w[0]=o->w[0]; w[1]=o->w[1]; w[2]=o->w[2]; w[3]=o->w[3];
        f_05e4a8(&s, &o->s);
    }
};
extern "C" {
/* @draft 0x0642c0 us f_0642c0
   WHAT IT DOES: clones an object: allocates 32 bytes, copies the byte and four words and the string member. */
void *f_0642c0(Obj0 *o) { return new Obj0(o); }
}

struct Node1 { Node1*l; Node1*p; Node1*r; Node1*q; };
struct Lst1 { int pad; Node1 *head; int size;
 void clear(){
  if (size) {
    f_04ee68(this, head->p);
    size=0;
    head->r = head;
    head->p = 0;
    head->q = head;
  } }
 ~Lst1(){ Node1 *h = head; f_04e4b4(h);} };
struct BaseT { void *vt; int w[5]; ~BaseT() { f_04e8d8(this); } };
struct Tr1 : BaseT { Lst1 m; ~Tr1() { vt = D_1a3698; m.clear(); } };
void f_05f4a0(void *);
void f_0655dc(void *, void *);
struct Lst2 { int pad; Node1 *head; int size;
 void clear(){
  if (size) {
    f_0655dc(this, head->p);
    size=0;
    head->r = head;
    head->p = 0;
    head->q = head;
  } }
 ~Lst2(){ Node1 *h = head; f_04e4b4(h);} };
struct M32 { int w[4]; ~M32() { f_05f4a0(this); } };
struct Tr2 : BaseT { int pad2[2]; M32 m32; Lst2 m; ~Tr2() { vt = D_1a41c0; m.clear(); } };
extern "C" {
/* @implements 0x06646c us f_06646c
   WHAT IT DOES: destructor of a tree container: empties the tree and frees its header node. */
void f_06646c(Tr1 *o) { o->~Tr1(); }
/* @implements 0x0667a4 us f_0667a4
   WHAT IT DOES: destructor of a tree container (twin of f_06646c): empties the tree and frees its header node. */
void f_0667a4(Tr1 *o) { o->~Tr1(); }
/* @implements 0x066510 us f_066510
   WHAT IT DOES: deleting destructor of the tree container: runs the destructor, then frees the object with f_05db44. */
void f_066510(Tr1 *o) { o->~Tr1(); f_05db44(o); }
/* @implements 0x066848 us f_066848
   WHAT IT DOES: deleting destructor of the tree container (twin of f_066510). */
void f_066848(Tr1 *o) { o->~Tr1(); f_05db44(o); }
/* @implements 0x063638 us f_063638
   WHAT IT DOES: deleting destructor of a tree container with an extra member at +32: empties the tree at +48, frees its header, destroys the member and base, then frees the object with f_05db44. */
void f_063638(Tr2 *o) { o->~Tr2(); f_05db44(o); }
inline bool lt4d(unsigned a, unsigned b) { return a < b; }
char *f_066f5c(void *, void *);
void f_066cdc(void *, void *);
/* @implements 0x065348 us f_065348
   WHAT IT DOES: tree insert helper: creates a node for the key with f_066f5c, links it as the left or right child of y (updating the header's leftmost/rightmost), rebalances with f_066cdc, bumps the count and returns the iterator in *out. */
int *f_065348(int *out, char *t, char *x, char *y, void *key) {
    char *z;
    if (y == *(char **)(t + 4) || x != 0 || lt4d(*(unsigned *)key, *(unsigned *)(y + 16))) {
        z = f_066f5c(t, key);
        *(char **)(y + 8) = z;
        if (y == *(char **)(t + 4)) {
            *(char **)(y + 4) = z;
            *(char **)(*(char **)(t + 4) + 12) = z;
        } else if (y == *(char **)(*(char **)(t + 4) + 8)) {
            *(char **)(*(char **)(t + 4) + 8) = z;
        }
    } else {
        z = f_066f5c(t, key);
        *(char **)(y + 12) = z;
        if (y == *(char **)(*(char **)(t + 4) + 12))
            *(char **)(*(char **)(t + 4) + 12) = z;
    }
    *(char **)(z + 4) = y;
    *(char **)(z + 8) = 0;
    *(char **)(z + 12) = 0;
    f_066cdc(z, *(char **)(t + 4) + 4);
    *(int *)(t + 8) += 1;
    *(char **)out = z;
    return out;
}
char *f_066fe0(void *, void *);
char *f_066f04(void *, void *);
char *f_066e1c(void *, void *);
int f_05dcb8(void *, void *);
/* @implements 0x0654a0 us f_0654a0
   WHAT IT DOES: tree insert helper (twin of f_065348): creates a node for the key with f_066fe0, links it as the left or right child of y (updating the header's leftmost/rightmost), rebalances with f_066cdc, bumps the count and returns the iterator in *out. */
int *f_0654a0(int *out, char *t, char *x, char *y, void *key) {
    char *z;
    if (y == *(char **)(t + 4) || x != 0 || lt4d(*(unsigned *)key, *(unsigned *)(y + 16))) {
        z = f_066fe0(t, key);
        *(char **)(y + 8) = z;
        if (y == *(char **)(t + 4)) {
            *(char **)(y + 4) = z;
            *(char **)(*(char **)(t + 4) + 12) = z;
        } else if (y == *(char **)(*(char **)(t + 4) + 8)) {
            *(char **)(*(char **)(t + 4) + 8) = z;
        }
    } else {
        z = f_066fe0(t, key);
        *(char **)(y + 12) = z;
        if (y == *(char **)(*(char **)(t + 4) + 12))
            *(char **)(*(char **)(t + 4) + 12) = z;
    }
    *(char **)(z + 4) = y;
    *(char **)(z + 8) = 0;
    *(char **)(z + 12) = 0;
    f_066cdc(z, *(char **)(t + 4) + 4);
    *(int *)(t + 8) += 1;
    *(char **)out = z;
    return out;
}
/* @implements 0x06523c us f_06523c
   WHAT IT DOES: tree insert helper (twin of f_065348): creates a node for the key with f_066f04, links it as the left or right child of y (updating the header's leftmost/rightmost), rebalances with f_066cdc, bumps the count and returns the iterator in *out. */
int *f_06523c(int *out, char *t, char *x, char *y, void *key) {
    char *z;
    if (y == *(char **)(t + 4) || x != 0 || (f_05dcb8(key, y + 16) & 0xff)) {
        z = f_066f04(t, key);
        *(char **)(y + 8) = z;
        if (y == *(char **)(t + 4)) {
            *(char **)(y + 4) = z;
            *(char **)(*(char **)(t + 4) + 12) = z;
        } else if (y == *(char **)(*(char **)(t + 4) + 8)) {
            *(char **)(*(char **)(t + 4) + 8) = z;
        }
    } else {
        z = f_066f04(t, key);
        *(char **)(y + 12) = z;
        if (y == *(char **)(*(char **)(t + 4) + 12))
            *(char **)(*(char **)(t + 4) + 12) = z;
    }
    *(char **)(z + 4) = y;
    *(char **)(z + 8) = 0;
    *(char **)(z + 12) = 0;
    f_066cdc(z, *(char **)(t + 4) + 4);
    *(int *)(t + 8) += 1;
    *(char **)out = z;
    return out;
}
/* @implements 0x064d8c us f_064d8c
   WHAT IT DOES: tree insert helper (twin of f_065348): creates a node for the key with f_066e1c, links it as the left or right child of y (updating the header's leftmost/rightmost), rebalances with f_066cdc, bumps the count and returns the iterator in *out. */
int *f_064d8c(int *out, char *t, char *x, char *y, void *key) {
    char *z;
    if (y == *(char **)(t + 4) || x != 0 || (f_05dcb8(key, y + 16) & 0xff)) {
        z = f_066e1c(t, key);
        *(char **)(y + 8) = z;
        if (y == *(char **)(t + 4)) {
            *(char **)(y + 4) = z;
            *(char **)(*(char **)(t + 4) + 12) = z;
        } else if (y == *(char **)(*(char **)(t + 4) + 8)) {
            *(char **)(*(char **)(t + 4) + 8) = z;
        }
    } else {
        z = f_066e1c(t, key);
        *(char **)(y + 12) = z;
        if (y == *(char **)(*(char **)(t + 4) + 12))
            *(char **)(*(char **)(t + 4) + 12) = z;
    }
    *(char **)(z + 4) = y;
    *(char **)(z + 8) = 0;
    *(char **)(z + 12) = 0;
    f_066cdc(z, *(char **)(t + 4) + 4);
    *(int *)(t + 8) += 1;
    *(char **)out = z;
    return out;
}
int memcmp(const void *, const void *, unsigned);
char *f_066e94(void *, void *);
inline const unsigned &min4d(const unsigned &a, const unsigned &b) { return a <= b ? a : b; }
struct Sp4d { char *p; };
inline int cmp4d(Sp4d &ka, Sp4d &kb) {
    char *ap = ka.p;
    unsigned a = *(unsigned *)(ap - 12);
    unsigned b = *(unsigned *)(kb.p - 12);
    int r = memcmp(ap, kb.p, min4d(a, b));
    if (!r) r = a - b;
    return r;
}
/* @draft 0x0650fc us f_0650fc
   WHAT IT DOES: tree insert helper (twin of f_065348): creates a node for the key with f_066e94, links it as the left or right child of y (updating the header's leftmost/rightmost), rebalances with f_066cdc, bumps the count and returns the iterator in *out. */
int *f_0650fc(int *out, char *t, char *x, char *y, void *key) {
    char *z;
    if (y == *(char **)(t + 4) || x != 0 || (cmp4d(*(Sp4d *)key, *(Sp4d *)(y + 16)) < 0)) {
        z = f_066e94(t, key);
        *(char **)(y + 8) = z;
        if (y == *(char **)(t + 4)) {
            *(char **)(y + 4) = z;
            *(char **)(*(char **)(t + 4) + 12) = z;
        } else if (y == *(char **)(*(char **)(t + 4) + 8)) {
            *(char **)(*(char **)(t + 4) + 8) = z;
        }
    } else {
        z = f_066e94(t, key);
        *(char **)(y + 12) = z;
        if (y == *(char **)(*(char **)(t + 4) + 12))
            *(char **)(*(char **)(t + 4) + 12) = z;
    }
    *(char **)(z + 4) = y;
    *(char **)(z + 8) = 0;
    *(char **)(z + 12) = 0;
    f_066cdc(z, *(char **)(t + 4) + 4);
    *(int *)(t + 8) += 1;
    *(char **)out = z;
    return out;
}
void f_064c6c(void *);
struct NodeIt4 { char *n; int pad[3]; };

/* @draft 0x0617f4 us f_0617f4
   WHAT IT DOES: unique insert into the tree: walks down comparing the key, finds the insertion parent, checks the predecessor for an equal key and either inserts through f_065348 (returning the node and 1) or returns the existing node and 0. */
struct InsRes4 { char *it; unsigned char ok; };
InsRes4 *f_0617f4(InsRes4 *out, char *t, unsigned *key) {
    char *x;
    char *y = *(char **)(t + 4);
    x = *(char **)(y + 4);
    int comp = 1;
    while (x) {
        y = x;
        comp = lt4d(*key, *(unsigned *)(x + 16));
        x = comp ? *(char **)(x + 8) : *(char **)(x + 12);
    }
    NodeIt4 j;
    NodeIt4 lm;
    NodeIt4 r;
    j.n = y;
    if (comp) {
        lm.n = *(char **)(*(char **)(t + 4) + 8);
        if (j.n != lm.n)
            f_064c6c(&j);
        else
            goto ins;
    }
    if (!lt4d(*(unsigned *)(j.n + 16), *key)) {
        out->ok = 0;
        out->it = j.n;
        return out;
    }
ins:
    {
        f_065348((int *)&r, t, x, y, key);
        out->ok = 1;
        out->it = r.n;
    }
    return out;
}
/* @draft 0x061910 us f_061910
   WHAT IT DOES: unique insert into the tree (twin of f_0617f4, inserting through f_0654a0): finds the insertion parent, checks the predecessor for an equal key and either inserts (returning the node and 1) or returns the existing node and 0. */
InsRes4 *f_061910(InsRes4 *out, char *t, unsigned *key) {
    char *x;
    char *y = *(char **)(t + 4);
    x = *(char **)(y + 4);
    int comp = 1;
    while (x) {
        y = x;
        comp = lt4d(*key, *(unsigned *)(x + 16));
        x = comp ? *(char **)(x + 8) : *(char **)(x + 12);
    }
    NodeIt4 j;
    NodeIt4 lm;
    NodeIt4 r;
    j.n = y;
    if (comp) {
        lm.n = *(char **)(*(char **)(t + 4) + 8);
        if (j.n != lm.n)
            f_064c6c(&j);
        else
            goto ins;
    }
    if (!lt4d(*(unsigned *)(j.n + 16), *key)) {
        out->ok = 0;
        out->it = j.n;
        return out;
    }
ins:
    {
        f_0654a0((int *)&r, t, x, y, key);
        out->ok = 1;
        out->it = r.n;
    }
    return out;
}
struct E44 { void **vt; int w1, w2, w3, w4, w5, w6, w7, w8, w9, w10; };
struct P44 { E44 *p; };
/* @draft 0x060d18 us f_060d18
   WHAT IT DOES: vector erase of the range [first,last) of 44-byte elements: moves the tail down over it field by field, runs the virtual destructor (slot 0) of the vacated tail elements and shrinks the end pointer; returns first. */
E44 *f_060d18(char *v, E44 *first, E44 *last) {
    int n = *(E44 **)(v + 8) - last;
    E44 *d = first;
    E44 *s = last;
    for (; n > 0; --n) {
        d->w1 = s->w1; d->w2 = s->w2; d->w3 = s->w3; d->w4 = s->w4;
        d->w7 = s->w7; d->w8 = s->w8; d->w9 = s->w9; d->w10 = s->w10;
        d->w6 = s->w6; d->w5 = s->w5;
        ++d; ++s;
    }
    P44 b, e;
    b.p = d;
    e.p = d;
    E44 *end = *(E44 **)(v + 8);
    if (b.p != end) {
        do {
            void *o = e.p;
            (*(void (**)(void *))*e.p->vt)(o);
            ++e.p;
        } while (e.p != end);
    }
    *(E44 **)(v + 8) = end - (last - first);
    return first;
}
}
}
