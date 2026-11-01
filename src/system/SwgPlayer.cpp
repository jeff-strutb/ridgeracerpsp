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

/* Named by its retail address: the file's own string pool does not hold retail's neighbours. */
extern char D_1a3278[]; /* "sound" */

/* @implements 0x0622b0 us f_0622b0
   WHAT IT DOES: Returns the name string "sound". */
const char *f_0622b0(void *p)
{
    (void)p;
    return D_1a3278;
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
/* The command names live in the object file's string pool between literals of functions not
   yet written; named by their retail addresses so this file's own pool keeps retail's order. */
extern char D_1a2d04[]; /* "_SWGKEYREPEATON" */
extern char D_1a2d14[]; /* "_SWGKEYREPEATOFF" */
extern char D_1a2d28[]; /* "_SWGEND" */

/* @implements 0x04dd14 us f_04dd14
   WHAT IT DOES: handles the _SWGKEYREPEATON/_SWGKEYREPEATOFF/_SWGEND command names by setting the matching flag, else forwards the name to the default handler through the vtable. */
void f_04dd14(char *s, int i) {
    char **names = (char **)W(s, 12);
    if (strcmp(names[i], D_1a2d04) == 0) {
        int p = W(s, 24);
        if (p) *(char*)p = 1; else dflt(s, i);
    } else if (strcmp(((char **)W(s, 12))[i], D_1a2d14) == 0) {
        int p = W(s, 24);
        if (p) *(char*)p = 0; else dflt(s, i);
    } else if (strcmp(((char **)W(s, 12))[i], D_1a2d28) == 0) {
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

/* @implements 0x04eaa0 us f_04eaa0
   WHAT IT DOES: destructor of a container object: stores its vtable, clears the list member, frees it and runs the base destructor. */

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
 ~Lst(){ Node *h = head; f_04e4b4(h);} };
struct Outer : Base { int b[5]; Lst m; ~Outer() { m.clear(); } };
struct G4eaa0 { ~G4eaa0() {} };
void f_04eaa0(Outer *o){
  {
    G4eaa0 g;
    *(void**)o = D_1a3698;
  }
  o->~Outer();
}

/* @draft 0x04eb44 us f_04eb44
   WHAT IT DOES: deleting twin of the container destructor, also freeing the block header at -4.
   Deleting twin of f_04eaa0 (frees the block header at -4 afterwards). Remaining difference: 4 words at the tail (retail leaves a nop in the _Unwind_Resume delay slot and puts move a0,s0 before it; ours fills the slot, 172 vs 176 bytes). */
extern "C" void f_04e4b4_nt3b(void *) throw() __asm__("f_04e4b4");
void f_04eb44(Outer *o){
  {
    G4eaa0 g;
    *(void**)o = D_1a3698;
  }
  o->~Outer();
  f_04e4b4_nt3b((char*)o - 4);
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
        char *e = *(char **)(s + 36) + a1 * 172;
        if (a4 <= 0 || a5 <= 0) {
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
    ~Hdr65b30() { void *h = hdr; f_04e4b4(h); }
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
        Hdr65b30 *mp = &m;
        if (mp->cnt) {
            f_04ee68(mp, W(mp->hdr, 4));
            mp->cnt = 0;
            *(void **)((char *)mp->hdr + 8) = mp->hdr;
            *(void **)((char *)mp->hdr + 4) = 0;
            *(void **)((char *)mp->hdr + 12) = mp->hdr;
        }
    }
};

/* @implements 0x065b30 us f_065b30
   WHAT IT DOES: destructor of the tree container: empties the tree and frees its header node. */
void f_065b30(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
}

/* @implements 0x065e10 us f_065e10
   WHAT IT DOES: destructor of the tree container (twin of f_065b30): empties the tree and frees its header node. */
void f_065e10(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
}

/* @implements 0x065bd4 us f_065bd4
   WHAT IT DOES: deleting destructor of the tree container: runs the destructor, then calls f_05db44(self). */
void f_065bd4(void *o)
{
    ((Tr65b30 *)o)->~Tr65b30();
    f_05db44(o);
}

/* @implements 0x065eb4 us f_065eb4
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
        void *a = (void *)W(p, 4); void *b = (void *)W(p, 8);
        *(void **)this = D_1a3e50;
        f_0606a0(a, b, 0);
    }
};

/* @implements 0x062528 us f_062528
   WHAT IT DOES: destructor: stores vtable D_1a3e50, calls f_0606a0 on the member at +24, destroys it (f_060670), then destroys the base (f_04e8d8). */
void f_062528(void *o)
{
    ((D062528 *)o)->~D062528();
}

/* @implements 0x062220 us f_062220
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

/* @implements 0x0625ac us f_0625ac
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

/* ---- swg4c ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 wave 3, worker swg4c */
namespace swg4c {
extern "C" {

void f_15f12c(void *, int);
void f_04e4b4(void *);
struct Tmp16 { int w[4]; ~Tmp16() {} };

struct Lsn { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(void *); };
struct Own { virtual void v0(); virtual void v1(); };
struct Cfg { char pad[40]; unsigned fl; };
struct Cf0 { int p0, p1, p2; Cfg *cfg; char pad[216]; Lsn *lsn; };
struct Par { int p0; Cf0 *c; };
struct Obj { virtual void v0(); int p[3]; Own *own; char pad[312]; int x; };

/* @draft 0x05a258 us f_05a258
   WHAT IT DOES: calls f_15f12c(obj,1), invokes the object's first virtual slot, then if a flag in the owner's config is set and the object has a field at 332 notifies the owner's listener through virtual slot 6, releases the object kept at +16 through its slot 1 and finishes with f_04e4b4. */
void f_05a258(Par *self, Obj *o) {
    Tmp16 t;
    f_15f12c(o, 1);
    Own *k = o->own;
    o->v0();
    if ((self->c->cfg->fl & 1) && o->x) self->c->lsn->a6(o);
    if (k) k->v1();
    f_04e4b4(o);
}

void *f_04dfa0(unsigned);
void *memmove(void *, const void *, unsigned);
void f_1312d4(const char *);
extern char D_1a3074[];

/* @draft 0x05b780 us f_05b780
   WHAT IT DOES: vector reserve: throws when n exceeds the maximum size; when the capacity is below n allocates a new block, memmoves the old elements, frees the old block and sets begin, end and capacity. */
void f_05b780(char *v, unsigned n) {
    if (n > 0x3fffffff) f_1312d4(D_1a3074);
    char *b = *(char **)(v + 4);
    if ((unsigned)((*(char **)(v + 12) - b) >> 2) < n) {
        char *e = *(char **)(v + 8);
        char *nb = (char *)f_04dfa0(n * 4);
        unsigned cnt = e - b;
        memmove(nb, b, cnt);
        if (*(char **)(v + 4)) f_04e4b4(*(char **)(v + 4));
        *(char **)(v + 12) = nb + n * 4;
        *(char **)(v + 8) = nb + (cnt >> 2) * 4;
        *(char **)(v + 4) = nb;
    }
}

int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
void f_04eee8(void *s, void *tag);
char *f_05e404(unsigned *, void *, unsigned);
extern char D_1a309c[];
struct G2 { int w[4]; ~G2() {} };

/* @implements 0x05c7dc us f_05c7dc
   WHAT IT DOES: string reserve: returns when the rep already has enough capacity and is unshared; otherwise throws on a size above the maximum, clones the rep to the larger capacity with f_05e404, drops the old rep's reference under interrupt suspend (freeing it when it hits zero) and installs the new data pointer. */
void f_05c7dc(char **self, unsigned n) {
    unsigned *rep = (unsigned *)(*self - 12);
    if (!(rep[1] < n) && (int)rep[2] <= 0) return;
    if (n > 0x3ffffffc) f_1312d4(D_1a309c);
    unsigned *r0 = (unsigned *)(*self - 12);
    unsigned len = r0[0];
    if (n < len) n = len;
    G2 g;
    char *nd = f_05e404(r0, &g, n - len);
    char *s0 = *self;
    char *s2 = s0 - 12;
    int intr = sceKernelCpuSuspendIntr();
    volatile int *c = (volatile int *)(s0 - 4);
    int s1 = *c;
    *c += -1;
    sceKernelCpuResumeIntr(intr);
    if (s1 <= 0) f_04eee8(s2, &g);
    *self = nd;
}

/* @draft 0x05fadc us f_05fadc
   WHAT IT DOES: string assignment: when the two handles differ, takes a copy of the source (sharing its rep by bumping the count under interrupt suspend, or cloning an unshareable one with f_05e404), drops the old rep's reference (freeing it at zero) and installs the new data pointer; returns the destination. */
char **f_05fadc(char **self, char **a) throw() {
    char *s0 = *a;
    char *rp = s0 - 12;
    if (*self - 12 != rp) {
        char *r;
        G2 g; G2 g1;
        if (*(int *)(rp + 8) < 0) {
            r = f_05e404((unsigned *)rp, &g, 0);
        } else {
            int st = sceKernelCpuSuspendIntr();
            volatile int *c = (volatile int *)(s0 - 4);
            int o = *c; (void)o;
            *c += 1;
            sceKernelCpuResumeIntr(st);
            r = s0;
        }
        char *d0 = *self;
        char *d2 = d0 - 12;
        int intr = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(d0 - 4);
        int s1 = *c;
        *c += -1;
        sceKernelCpuResumeIntr(intr);
        if (s1 <= 0) f_04eee8(d2, &g);
        *self = r;
    }
    return self;
}

char *f_061be0(unsigned, char *, char *);

struct Vec { int pad; int *b, *e, *c; };

/* @draft 0x05b858 us f_05b858
   WHAT IT DOES: vector assignment: when the source differs, either allocates a new block of the source's size via f_061be0 and frees the old one, or memmoves the source elements over the existing storage (the head over the used part and the tail past the end); sets the end pointer and returns this. */
Vec *f_05b858(Vec *self, Vec *x) {
    if (x != self) {
        unsigned n = x->e - x->b;
        if ((unsigned)(self->c - self->b) < n) {
            int *nb = (int *)f_061be0(n, (char *)x->b, (char *)x->e);
            if (self->b) f_04e4b4(self->b);
            self->b = nb;
            self->c = nb + n;
        } else {
            unsigned sz = self->e - self->b;
            if (sz < n) {
                memmove(self->b, x->b, sz * 4);
                memmove(self->e, x->b + (self->e - self->b), (x->e - x->b - (self->e - self->b)) * 4);
            } else {
                memmove(self->b, x->b, (x->e - x->b) * 4);
            }
        }
        self->e = self->b + n;
    }
    return self;
}

struct Str {
    char *p;
    Str() {}
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
unsigned strlen(const char *);
extern char D_291400[];
void f_061a08(Str *, unsigned, unsigned, const char *, unsigned);
void f_05c8d0(Str *, Str *);

/* @draft 0x05a44c us f_05a44c
   WHAT IT DOES: string concatenation of a C string and a string: starts the result as a shared empty rep (bumping its count under interrupt suspend), reserves the combined length, copies the C string in with f_061a08 and appends the second string with f_05c8d0. */
Str f_05a44c(const char *s, Str &b) throw() {
    unsigned n = strlen(s);
    Str r;
    {
        char *e = D_291400;
        int st = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(e + 8);
        int o = *c; (void)o;
        *c += 1;
        sceKernelCpuResumeIntr(st);
        r.p = e + 12;
    }
    f_05c7dc(&r.p, n + *(unsigned *)(b.p - 12));
    f_061a08(&r, *(unsigned *)(r.p - 12), 0, s, n);
    f_05c8d0(&r, &b);
    return r;
}

int f_05dcb8(void *, void *);
void f_064c6c(char **);
void f_064d8c(int *, char *, char *, char *, void *);
struct InsRes { int a, b; };
InsRes *f_061528(InsRes *, char *, void *);

/* @draft 0x05e068 us f_05e068
   WHAT IT DOES: ordered-tree unique insert with a position hint: when the hint is the leftmost node or the end, or the key falls between the hint's predecessor and the hint, inserts there with f_064d8c; otherwise falls back to the plain unique insert f_061528 and stores its iterator in *out. */
int *f_05e068(int *out, char *t, char **pos, void *key) {
    char *hd = *(char **)(t + 4);
    if (*pos == *(char **)(hd + 8)) {
        if (*(int *)(t + 8) != 0 && f_05dcb8(key, *pos + 16) & 0xff) {
            f_064d8c(out, t, *pos, *pos, key);
            return out;
        }
    } else if (*pos == hd) {
        if (f_05dcb8(*(char **)(*pos + 12) + 16, key) & 0xff) {
            f_064d8c(out, t, 0, *(char **)(*(char **)(t + 4) + 12), key);
            return out;
        }
    } else {
        char *before = *pos;
        f_064c6c(&before);
        if ((f_05dcb8(before + 16, key) & 0xff) && (f_05dcb8(key, *pos + 16) & 0xff)) {
            if (*(int *)(before + 12) == 0) f_064d8c(out, t, 0, before, key);
            else f_064d8c(out, t, *pos, *pos, key);
            return out;
        }
    }
    InsRes r;
    f_061528(&r, t, key);
    *out = r.a;
    return out;
}

void f_06523c(int *, char *, char *, char *, void *);
InsRes *f_0616fc(InsRes *, char *, void *);

/* @draft 0x05e834 us f_05e834
   WHAT IT DOES: ordered-tree unique insert with a position hint: when the hint is the leftmost node or the end, or the key falls between the hint's predecessor and the hint, inserts there with f_06523c; otherwise falls back to the plain unique insert f_0616fc and stores its iterator in *out. */
int *f_05e834(int *out, char *t, char **pos, void *key) {
    char *hd = *(char **)(t + 4);
    if (*pos == *(char **)(hd + 8)) {
        if (*(int *)(t + 8) != 0 && f_05dcb8(key, *pos + 16) & 0xff) {
            f_06523c(out, t, *pos, *pos, key);
            return out;
        }
    } else if (*pos == hd) {
        if (f_05dcb8(*(char **)(*pos + 12) + 16, key) & 0xff) {
            f_06523c(out, t, 0, *(char **)(*(char **)(t + 4) + 12), key);
            return out;
        }
    } else {
        char *before = *pos;
        f_064c6c(&before);
        if ((f_05dcb8(before + 16, key) & 0xff) && (f_05dcb8(key, *pos + 16) & 0xff)) {
            if (*(int *)(before + 12) == 0) f_06523c(out, t, 0, before, key);
            else f_06523c(out, t, *pos, *pos, key);
            return out;
        }
    }
    InsRes r;
    f_0616fc(&r, t, key);
    *out = r.a;
    return out;
}
}
}

/* ---- swg5a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment by worker swg5a. */
namespace swg5a {

struct Cn { int a, b; float x, y; int c; };
struct Gp { unsigned a, b, c, d; };
struct Msg { int t; char c; };
extern "C" {
extern Gp D_24518c;
extern char D_1d8910;
void f_04325c(void *);
void f_04316c(void *);
int f_04311c(void *);
void f_04afc8(int *);
int f_04320c(void *);
void f_15bbac(void *, void *);
void *f_021b38(int);
void f_116dfc(int, int, int, int, void *);
extern float D_1a2b08;
void f_046620(void *, int);
void f_0455e8(float, float, float, float, void *, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
void f_0455cc(void *);
void f_1166d4(int);
void f_11839c(int);
void f_116898(int);
void f_0454d4(void *);
static inline unsigned cv4(float f) { return (unsigned)(f * D_1a2b08); }
void f_1181c0(unsigned);
extern float D_1a2b5c, D_1a2af8, D_1a2b00;
static inline unsigned cv3(float f) { return (unsigned)(f * D_1a2b00); }
static inline unsigned cv2(float f) { return (unsigned)(f * D_1a2af8); }
static inline unsigned cv(float f) { return (unsigned)(f * D_1a2b5c); }

/* @draft 0x04ca04 us f_04ca04
   WHAT IT DOES: builds the four corner points of entry a1 from its source rectangle interpolated by (sx,sy), offsets them by (dx,dy), and stores the scaled min x at +80 and max x plus one at +84. */
void f_04ca04(char *s, int a1, float sx, float sy, float dx, float dy) {
    if (*(int *)(s + 32) >= a1) {
    char *e = *(char **)(s + 36) + a1 * 172;
    float *f = (float *)e;
    Cn *c = (Cn *)e;
    float x0 = f[23];
    f[12] = f[25];
    f[8] = f[28];
    float y0 = f[27];
    float x1 = x0 + (f[24] - x0) * sx;
    float y1 = y0 + (f[29] - y0) * sy;
    c[0].x = x0;
    c[3].x = x1;
    c[3].y = y1;
    c[1].x = x1;
    c[0].y = y0;
    c[2].y = y1;
    for (int i = 0; i < 4; i++) {
        c[i].x += dx;
        c[i].y += dy;
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

/* @draft 0x04c668 us f_04c668
   WHAT IT DOES: converts the four floats (r,g,b,a) times a constant to unsigned bytes, packs them into one 32-bit color and stores it into the five vertex color slots of entry a1. */
void f_04c668(char *s, int a1, float r, float g, float b, float a) {
    if (*(int *)(s + 32) >= a1) {
    char *e = *(char **)(s + 36) + a1 * 172;
    unsigned c = cv(r) & 0xff;
    c |= (cv(g) & 0xff) << 8;
    c |= (cv(b) & 0xff) << 16;
    c |= cv(a) << 24;
    *(unsigned *)(e + 4) = c;
    *(unsigned *)(e + 88) = c;
    *(unsigned *)(e + 64) = c;
    *(unsigned *)(e + 44) = c;
    *(unsigned *)(e + 24) = c;
    }
}

/* @draft 0x0459d0 us f_0459d0
   WHAT IT DOES: allocates a 64-byte block, fills four 16-byte vertex records from three arrays of packed words (bytes copied to +4, +8, +12) and a color packed from four float arrays scaled by a constant (bytes at +0), submits it with f_116dfc and returns its ninth argument. */
int f_0459d0(int a0, unsigned *p0, unsigned *p1, unsigned *p2, float *q0, float *q1, float *q2, float *q3, int r) {
    unsigned char *t = (unsigned char *)f_021b38(64);
    unsigned char *d = t;
    for (int i = 0; i < 4; i++, d += 16) {
        unsigned v = p0[i];
        d[6] = v >> 16;
        d[7] = v >> 24;
        d[4] = v;
        d[5] = v >> 8;
        v = p1[i];
        d[10] = v >> 16;
        d[11] = v >> 24;
        d[8] = v;
        d[9] = v >> 8;
        v = p2[i];
        d[13] = v >> 8;
        d[14] = v >> 16;
        d[15] = v >> 24;
        d[12] = v;
        unsigned c = cv2(q0[i]) & 0xff;
        c |= (cv2(q1[i]) & 0xff) << 8;
        c |= (cv2(q2[i]) & 0xff) << 16;
        c |= cv2(q3[i]) << 24;
        d[1] = c >> 8;
        d[2] = c >> 16;
        d[3] = c >> 24;
        d[0] = c;
    }
    f_116dfc(4, 0x80019c, 4, 0, t);
    return r;
}

/* @draft 0x045c14 us f_045c14
   WHAT IT DOES: allocates a 32-byte block, fills two 16-byte vertex records from three arrays of packed words (bytes copied to +4, +8, +12) and a color packed from four float arrays scaled by a constant (bytes at +0), submits it with f_116dfc and returns its ninth argument. */
int f_045c14(int a0, unsigned *p0, unsigned *p1, unsigned *p2, float *q0, float *q1, float *q2, float *q3, int r) {
    unsigned char *t = (unsigned char *)f_021b38(32);
    unsigned char *d = t;
    for (int i = 0; i < 2; i++, d += 16) {
        unsigned v = p0[i];
        d[6] = v >> 16;
        d[7] = v >> 24;
        d[4] = v;
        d[5] = v >> 8;
        v = p1[i];
        d[10] = v >> 16;
        d[11] = v >> 24;
        d[8] = v;
        d[9] = v >> 8;
        v = p2[i];
        d[13] = v >> 8;
        d[14] = v >> 16;
        d[15] = v >> 24;
        d[12] = v;
        unsigned c = cv3(q0[i]) & 0xff;
        c |= (cv3(q1[i]) & 0xff) << 8;
        c |= (cv3(q2[i]) & 0xff) << 16;
        c |= cv3(q3[i]) << 24;
        d[1] = c >> 8;
        d[2] = c >> 16;
        d[3] = c >> 24;
        d[0] = c;
    }
    f_116dfc(1, 0x80019c, 2, 0, t);
    return r;
}

/* @draft 0x04afc8 us f_04afc8
   WHAT IT DOES: reads the pad state words and the stick axis, then sends one direction/command key code (w, x, a, d, e, c, s, f) through f_15bbac to the target held in a0 according to the held direction bits, followed by q, z, r and v for the button bits 0x1, 0x8, 0x100 and 0x200. */
void f_04afc8(int *p) {
    Msg m;
    unsigned s1 = D_24518c.d;
    unsigned s5 = D_24518c.a;
    unsigned s3 = D_24518c.c;
    void *s4 = (void *)*p;
    f_04325c(&D_1d8910);
    int s2 = f_04320c(&D_1d8910);
    int v1 = s2;
#define SEND(ch) { m.t = 5; m.c = (ch); f_15bbac(s4, &m); }
    if (s1 & 0x10) goto W;
    if (s1 & 0x40) goto X;
    if (s2 > 0) goto W;
    if (s2 < 0) goto X;
    if (s1 & 0x80) { SEND(97) goto T; }
    if (s1 & 0x20) { SEND(100) goto T; }
    if (v1 < 0) { SEND(97) goto T; }
    if (v1 > 0) { SEND(100) goto T; }
    if ((s3 & 0x1000) && !(s5 & 0xe000)) SEND(101)
    else if ((s3 & 0x4000) && !(s5 & 0xb000)) SEND(99)
    else if ((s3 & 0x8000) && !(s5 & 0x7000)) SEND(115)
    else if ((s3 & 0x2000) && !(s5 & 0xd000)) SEND(102)
    goto T;
W:  SEND(119) goto T;
X:  SEND(120)
T:
    if (s3 & 0x1) SEND(113)
    if (s3 & 0x8) SEND(122)
    if (s3 & 0x100) SEND(114)
    if (s3 & 0x200) SEND(118)
#undef SEND
}

/* @draft 0x04ad54 us f_04ad54
   WHAT IT DOES: if the byte at +24 is set defers to f_04afc8; otherwise reads the pad state word and the stick axis and sends one direction/command key code (w, x, a, d, e, c, s, f) through f_15bbac to the target held in a0 according to the held direction bits, followed by q, z, r and v for the button bits 0x1, 0x8, 0x100 and 0x200. */
void f_04ad54(char *p) {
    if (p[24]) { f_04afc8((int *)p); return; }
    Msg m;
        unsigned s5 = D_24518c.a;
    unsigned s3 = D_24518c.c;
    void *s4 = (void *)*(int *)p;
    f_04316c(&D_1d8910);
    int s2 = f_04311c(&D_1d8910);
    int v1 = s2;
#define SEND(ch) { m.t = 5; m.c = (ch); f_15bbac(s4, &m); }
    if (s3 & 0x10) goto W;
    if (s3 & 0x40) goto X;
    if (s2 > 0) goto W;
    if (s2 < 0) goto X;
    if (s3 & 0x80) { SEND(97) goto T; }
    if (s3 & 0x20) { SEND(100) goto T; }
    if (v1 < 0) { SEND(97) goto T; }
    if (v1 > 0) { SEND(100) goto T; }
    if ((s3 & 0x1000) && !(s5 & 0xe000)) SEND(101)
    else if ((s3 & 0x4000) && !(s5 & 0xb000)) SEND(99)
    else if ((s3 & 0x8000) && !(s5 & 0x7000)) SEND(115)
    else if ((s3 & 0x2000) && !(s5 & 0xd000)) SEND(102)
    goto T;
W:  SEND(119) goto T;
X:  SEND(120)
T:
    if (s3 & 0x1) SEND(113)
    if (s3 & 0x8) SEND(122)
    if (s3 & 0x100) SEND(114)
    if (s3 & 0x200) SEND(118)
#undef SEND
}

/* @draft 0x0463a4 us f_0463a4
   WHAT IT DOES: unless the second argument exceeds 480 or the seventh is negative, packs four float components into one 32-bit color, builds a 20-byte record of ten 16-bit values from the integer arguments, passes the color to f_1181c0, submits the record with f_116dfc and returns 0. */
int f_0463a4(float r, float g, float b, float a, int a0, int x, int p2, int p3, int p4, int p5, int p6, int p7, unsigned s0, unsigned s1, unsigned s2) {
    if ((x > 480) | (p6 < 0)) return 0;
    unsigned c = cv4(r) & 0xff;
    c |= (cv4(g) & 0xff) << 8;
    c |= (cv4(b) & 0xff) << 16;
    c |= cv4(a) << 24;
    unsigned char *t = (unsigned char *)f_021b38(20);
    unsigned short v0 = p4, v1 = p5, v2 = x, v3 = p2, v4 = p3, v5 = s1, v6 = s2, v7 = p6, v8 = p7, v9 = s0;
    t[7] = v3 >> 8; t[17] = v8 >> 8; t[9] = v4 >> 8; t[19] = v9 >> 8; t[5] = v2 >> 8;
    t[15] = v7 >> 8; t[1] = v0 >> 8; t[11] = v5 >> 8; t[3] = v1 >> 8; t[13] = v6 >> 8;
    t[4] = v2; t[14] = v7; t[6] = v3; t[16] = v8; t[8] = v4; t[18] = v9; t[0] = v0; t[10] = v5; t[2] = v1; t[12] = v6;
    f_1181c0(c);
    f_116dfc(6, 0x800102, 2, 0, t);
    return 0;
}

/* @draft 0x049b90 us f_049b90
   WHAT IT DOES: looks up the sprite record of the index at a1+12, scales its width and height by the 2x2 matrix and translation in a2 to get four corner points (with texture coordinates 0..w, 0..h), re-selects the record's palette byte when it changed, and submits the quad through f_0455e8 unless mode (a2+96) is 2; in mode 1 with the +80 field equal to 1 it instead runs the f_0455cc bracket and the virtual call at slot 7 of the object at +28. */
void f_049b90(char *s2, char *s3, char *s1) {
    char *a1 = *(char **)(s2 + 4);
    char *rec = *(char **)(a1 + 40) + *(int *)(s3 + 12) * 12;
    float m0 = *(float *)(s1 + 0), m1 = *(float *)(s1 + 4);
    float m4 = *(float *)(s1 + 16), m5 = *(float *)(s1 + 20);
    float tx = *(float *)(s1 + 48), ty = *(float *)(s1 + 52);
    int w = *(short *)(rec + 4), h = *(short *)(rec + 6);
    float fw = (float)w, fh = (float)h;
    int X[4], Y[4], U[4], V[4];
    X[0] = (int)tx;
    Y[0] = (int)ty;
    X[1] = (int)(fw * m0 + tx);
    Y[1] = (int)(fw * m1 + ty);
    X[2] = (int)(fw * m0 + fh * m4 + tx);
    Y[2] = (int)(fw * m1 + fh * m5 + ty);
    X[3] = (int)(fh * m4 + tx);
    Y[3] = (int)(fh * m5 + ty);
    U[0] = 0; V[0] = 0; U[1] = w; V[1] = 0; U[2] = w; V[2] = h; U[3] = 0; V[3] = h;
    int pal = ((signed char *)rec)[8];
    int *tab = *(int **)(a1 + 240);
    if (*(int *)(s2 + 8) != pal) {
        *(int *)(s2 + 8) = pal;
        f_046620(s2 + 12, pal);
    }
    int mode = *(int *)(s1 + 96);
    if (mode == 2) return;
    if (mode == 1 && (int)*(float *)(s1 + 80) == 1) {
        if (*(int *)(s2 + 28)) {
            void *o = s2 + 12;
            f_0455cc(o);
            f_1166d4(10);
            f_1166d4(1);
            f_11839c(0);
            void **obj = *(void ***)(s2 + 28);
            ((void (*)(void *, int))((void **)*obj)[7])(obj, (int)*(float *)(s1 + 84));
            f_116898(10);
            f_116898(1);
            f_0454d4(o);
        }
        return;
    }
    f_0455e8(*(float *)(s1 + 64), *(float *)(s1 + 68), *(float *)(s1 + 72), *(float *)(s1 + 76), s2 + 12,
             X[0], Y[0], -1, U[0], V[0],
             X[1], Y[1], -1, U[1], V[1],
             X[2], Y[2], -1, U[2], V[2],
             X[3], Y[3], -1, U[3], V[3],
             tab[*(int *)(s3 + 12)]);
}

}
}

/* ---- swg4b ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg4b: untagged functions of the SWG player (rest_b2). */
namespace swg4b {
extern "C" {
void *f_154448(void*,void*,void*,int); void f_05cbd4(void*); extern char D_1a4900[], D_1a3b70[];
void f_05dd24(void*,void*,void*); void f_05e264(void*,int);
void *f_04dfa0(unsigned); void f_04ed28(void*); void f_05e394(void*,void*,void*,void*);
void f_05f64c(void*,void*,void*); void f_05dd24(void*,void*,void*); void f_05e264(void*,int); void f_05dbf4(void*,void*,void*); void f_05dddc(void*,void*,void*);
extern char D_1a4060[]; extern char D_1a4320[];
struct Em { ~Em(){} };
struct H { int *o; int *cnt; ~H(){ f_04ed28(this);} };
struct PP { void *p; ~PP(){} };
struct Pair { PP p; int *cnt; Pair(void *o){ p.p=o; cnt=0; if(o){ cnt=(int*)f_04dfa0(4); *cnt=1; } } ~Pair(){ f_04ed28(this);} };
struct ObB {
  void *vt; int x; char c;
  static void *operator new(unsigned n){ unsigned *p=(unsigned*)f_04dfa0(n+4); *p=n+4; return p+1; }
  static void operator delete(void*) {}
  ObB(int v){ Em e; vt = D_1a4060; x = 0; c = v; }
};
struct ObI {
  void *vt; int x; int c;
  static void *operator new(unsigned n){ unsigned *p=(unsigned*)f_04dfa0(n+4); *p=n+4; return p+1; }
  static void operator delete(void*) {}
  ObI(int v){ Em e; vt = D_1a4320; x = 0; c = v; }
};
extern char D_1a4270[];
struct ObD {
  void *vt; int x; double c;
  static void *operator new(unsigned n){ unsigned *p=(unsigned*)f_04dfa0(n+4); *p=n+4; return p+1; }
  static void operator delete(void*) {}
  ObD(double v){ Em e; vt = D_1a4270; x = 0; c = v; }
};
struct R { int *a; int *c; ~R(){ f_04ed28(this);} };
struct It { int *p; It(){} It(const It&o){p=o.p;} };

/* @implements 0x055220 us f_055220
   WHAT IT DOES: copies the counted handle found two links down the chain at +328 (bumping its refcount), calls f_05f64c with that chain, then calls virtual slot 22 on the handle's object and returns the result.
   The last scratch-slot store is a plain (non-volatile) store written before b, so sched2 puts it last and dbr can move it into the call's delay slot. */
int f_055220(char *p) {
  H h; volatile int t[4]; int out[4]; int b;
  char *q = p + 328;
  int a = *(int*)(q+4);
  t[0]=a; __asm__ volatile("":::"memory");
  int *v = *(int**)(a+4);
  int *c=(int*)v[3]; h.o=(int*)v[2]; h.cnt=c; t[0]=(int)v; if(c) ++*c;
  t[0]=a;
  int w=*(int*)(a+4);
  *(int*)&t[0]=w; b=w;
  f_05f64c(out,q,&b);
  void **vt=*(void***)h.o;
  return ((int(*)(void*))vt[22])(h.o);
}

/* @draft 0x052b54 us f_052b54
   WHAT IT DOES: allocates a ref-counted boolean object holding the flag argument, then calls f_05e394 with it and the sub-object at +328, releasing the holder afterwards.
   Remaining difference: one missing landing pad and vtable/size store order (27 of 50 words). */
void f_052b54(char *s, int v){
  char *q = s+328;
  Pair pr(new ObB(v&0xff));
  int out[8]; int a;
  a = *(int*)(q+4);
  f_05e394(out+4, q, &a, &pr);
}

/* @draft 0x052cf4 us f_052cf4
   WHAT IT DOES: like f_052b54 with an integer-valued object: allocates a ref-counted object holding the argument and calls f_05e394 with it.
   Remaining difference: same as f_052b54. */
void f_052cf4(char *s, int v){
  char *q = s+328;
  Pair pr(new ObI(v));
  int out[8]; int a;
  a = *(int*)(q+4);
  f_05e394(out+4, q, &a, &pr);
}

/* @draft 0x04f35c us f_04f35c
   WHAT IT DOES: looks up a key in the map: returns a copy (refcount bumped) of the found handle, or a null handle when absent.
   Remaining difference: stack slot of the end iterator and prologue order (18 of 51 words). */
R *f_04f35c(R *out, char *t, void *k) {
  R r;
  f_05dbf4(&r, t, k);
  if (r.a) { out->a = r.a; out->c = r.c; if (r.c) ++*r.c; return out; }
  char *s = t + 8;
  It b;
  f_05dddc(&b, s, k);
  It e0; e0.p = *(int**)(s+4); It e(e0);
  if (b.p == e0.p) { out->a = 0; out->c = 0; return out; }
  out->c = (int*)b.p[9]; out->a = (int*)b.p[8];
  if (out->c) ++*out->c;
  return out;
}

/* @draft 0x052c1c us f_052c1c
   WHAT IT DOES: like f_052b54 with a double-valued object: allocates a ref-counted object holding the double argument and calls f_05e394 with it.
   Remaining difference: same as f_052b54. */
void f_052c1c(char *s, int u, double v){
  char *q = s+328;
  Pair pr(new ObD(v));
  int out[8]; int a;
  a = *(int*)(q+4);
  f_05e394(out+4, q, &a, &pr);
}

static inline bool is2(int x){ return x == 2; }
/* @draft 0x04f718 us f_04f718
   WHAT IT DOES: finds the entry for the key in the map at +24; if it exists and its object's kind field is 2, stores three arguments into the player (+44, +52, +48), calls f_05e264 on the object and then virtual slot 43 with kind 2; otherwise returns a null handle.
   Remaining difference: callee-saved register choice for the two trailing arguments and an extra iterator stack store (38 of 55 words). */
R *f_04f718(R *out, char *self, int v, void *key, int x, int y) {
  It b; char *sm = self+24;
  f_05dd24(&b, sm, key);
  It e0; e0.p = *(int**)(sm+4); It e(e0);
  if (b.p != e.p) {
    int *o = (int*)b.p[8];
    if (is2(o[1])) {
      *(int*)(self+44) = v;
      *(int*)(self+52) = y;
      *(int*)(self+48) = x;
      f_05e264(o, x);
      void **vt = *(void***)self;
      ((void(*)(R*,void*,int,void*))vt[43])(out, self, 2, (void*)((int*)b.p)[8]);
      return out;
    }
  }
  out->a = 0; out->c = 0;
  return out;
}

/* @draft 0x04f874 us f_04f874
   WHAT IT DOES: looks up the list for a class tag in the argument object through f_154448 and calls virtual slot 14 of this object for each element, passing the element key and a copy (refcount bumped) of its handle, destroying the copy afterwards.
   Remaining difference: retail rebuilds the iterator address each pass and has a trailing landing pad (47 of 53 words). */
void f_04f874(char *self, void *obj) {
  if (!obj) return;
  char *r = (char*)f_154448(obj, D_1a4900, D_1a3b70, 0);
  if (!r) return;
  int *s0 = *(int**)(r+12);
  It it; it.p = (int*)s0[2];
  while (it.p != s0) {
    int *n = it.p;
    R h; h.a = (int*)n[8]; h.c = (int*)n[9]; if (h.c) ++*h.c;
    void **vt = *(void***)self;
    ((void(*)(void*,void*,R*))vt[14])(self, n+4, &h);
    f_05cbd4(&it);
  }
}

/* @draft 0x0540a0 us f_0540a0
   WHAT IT DOES: calls virtual slot 25 of the object, then copies the counted handle two links down the chain at +328 (bumping its refcount), calls f_05f64c with that chain, and calls virtual slot 18 of the handle's object with the +328 sub-object.
   Remaining difference: same stack-store ordering as f_055220. */
void f_0540a0(char *p) {
  H h; volatile int t[4]; int out[4]; volatile int b;
  char *q = p + 328;
  void **pv = *(void***)p;
  ((void(*)(void*))pv[25])(p);
  int a = *(int*)(q+4);
  t[0]=a; __asm__ volatile("":::"memory");
  int *v = *(int**)(a+4);
  int *c=(int*)v[3]; h.o=(int*)v[2]; h.cnt=c; t[0]=(int)v; if(c) ++*c;
  t[0]=a;
  int w=*(int*)(a+4);
  b=w; t[0]=w;
  f_05f64c(out,q,(int*)&b);
  void **vt=*(void***)h.o;
  ((void(*)(void*,void*))vt[18])(h.o, q);
}

/* @draft 0x05414c us f_05414c
   WHAT IT DOES: same as f_0540a0 but calls virtual slot 19 of the handle's object.
   Remaining difference: same as f_0540a0. */
void f_05414c(char *p) {
  H h; volatile int t[4]; int out[4]; volatile int b;
  char *q = p + 328;
  void **pv = *(void***)p;
  ((void(*)(void*))pv[25])(p);
  int a = *(int*)(q+4);
  t[0]=a; __asm__ volatile("":::"memory");
  int *v = *(int**)(a+4);
  int *c=(int*)v[3]; h.o=(int*)v[2]; h.cnt=c; t[0]=(int)v; if(c) ++*c;
  t[0]=a;
  int w=*(int*)(a+4);
  b=w; t[0]=w;
  f_05f64c(out,q,(int*)&b);
  void **vt=*(void***)h.o;
  ((void(*)(void*,void*))vt[19])(h.o, q);
}

struct Em2 { ~Em2(){} };
extern int D_1a2be8[5]; extern const char *D_1a2c08[5];
unsigned slen(const char*) __asm__("strlen");
struct E { int a, b, c, d; };
struct A5 { int v[5]; };
struct B5 { const char *v[5]; };
/* @draft 0x04e74c us f_04e74c
   WHAT IT DOES: copies two five-entry tables from rodata (values and name strings), stores the argument at +60, allocates a 100-byte block (size header 100) kept at +56 and fills five 16-byte records {value, 2, strlen(name) or 0, index}, then a sixth record {0, 1, 0, 0}.
   Remaining difference: retail keeps a second 16-byte temporary below the record temporary (frame 128 vs 112), the trailing landing pad is missing (91 of 93 words). */
void f_04e74c(char *self, int arg) {
  A5 a = *(A5*)D_1a2be8; B5 b = *(B5*)D_1a2c08;
  *(int*)(self+60) = arg;
  unsigned *p = (unsigned*)f_04dfa0(100);
  *p = 100;
  E *blk = (E*)(p+1);
  *(E**)(self+56) = blk;
  E t; int i = 0;
  do {
    Em2 em; int x = a.v[i]; const char *s = b.v[i];
    int len = s ? slen(s) : 0;
    t.a = x; t.b = 2; t.c = len; t.d = i;
    blk[i] = t;
    i++;
  } while (i < 5);
  t.b = 1; t.c = 0; t.d = 0;
  blk[5].a = 0; blk[5].b = t.b; blk[5].c = t.c; blk[5].d = t.d;
}

}
}

/* ---- swg5d ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 wave 3 worker swg5d (rest_d3) */
namespace swg5d {
extern "C" {
struct Tmp16 { int w[4]; ~Tmp16() {} };
struct G2 { int w[4]; ~G2() {} };
struct It2 {
    void **p;
    void *&operator*() { return *p; }
    It2 &operator++() { ++p; return *this; }
    bool operator!=(const It2 &o) const { return p != o.p; }
};
void *memcpy(void *, const void *, unsigned);
char *f_065060(unsigned, void *);
void f_1310e8(const char *);
extern char D_1a3234[];
extern char D_291400[];
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
void *f_05db08(unsigned n);
void f_05db44(void *);
void f_05daa4(void *, void *);
void f_05e394(void *, void *, void *, void *);
void f_04ed28(void *);
void f_04e4b4(void *);
/* @draft 0x061cc8 us f_061cc8
   WHAT IT DOES: builds a string rep from a char range [b,e): for an empty range shares the static empty rep (bumping its count under interrupt suspend); otherwise throws on a null begin, allocates a rep, copies the characters, stores the length and terminates it.
   Remaining difference: register allocation of the saved registers (35/55 words) */
char *f_061cc8(char *b, char *e, void *a, int x) throw() {
    Tmp16 t;
    if (b == e) {
        char *rp = D_291400;
        int st = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(rp + 8);
        int o = *c; (void)o;
        *c += 1;
        sceKernelCpuResumeIntr(st);
        return rp + 12;
    }
    if (!b) f_1310e8(D_1a3234);
    unsigned n = e - b;
    char *r = f_065060(n, a);
    char *d = r + 12;
    memcpy(d, b, n);
    *(unsigned *)r = n;
    d[n] = 0;
    return d;
}
/* @draft 0x061620 us f_061620
   WHAT IT DOES: twin of f_061cc8: builds a string rep from a char range [b,e): for an empty range shares the static empty rep (bumping its count under interrupt suspend); otherwise throws on a null begin, allocates a rep, copies the characters, stores the length and terminates it.
   Remaining difference: register allocation of the saved registers (35/55 words) */
char *f_061620(char *b, char *e, void *a, int x) throw() {
    Tmp16 t;
    if (b == e) {
        char *rp = D_291400;
        int st = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(rp + 8);
        int o = *c; (void)o;
        *c += 1;
        sceKernelCpuResumeIntr(st);
        return rp + 12;
    }
    if (!b) f_1310e8(D_1a3234);
    unsigned n = e - b;
    char *r = f_065060(n, a);
    char *d = r + 12;
    memcpy(d, b, n);
    *(unsigned *)r = n;
    d[n] = 0;
    return d;
}
void f_04e930(void *, void *);
void f_05cbd4(void *);
char *f_05cc58(void *, void *, void *, void *);
struct It4 { int *p; int pad[3]; It4() {} It4(const It4 &o) { p = o.p; } It4 operator++(int) { It4 t(*this); f_05cbd4(this); return t; } };
/* @draft 0x064f10 us f_064f10
   WHAT IT DOES: tree range erase: when the range is the whole tree it empties it (f_04e930 and the header reset); otherwise it unlinks each node in [first,last) with f_05cc58, destroys its value (f_04ed28), frees it (f_04e4b4) and decrements the count.
   Remaining difference: block layout of the clear branch versus the loop (57/62 words) */
void f_064f10(char *t, char **first, char **last) {
    char *hdr = *(char **)(t + 4);
    It4 b; b.p = *(int **)(hdr + 8);
    It4 e; e.p = (int *)hdr;
    if (*first == (char *)b.p && *last == hdr) {
        if (*(int *)(t + 8)) {
            f_04e930(t, *(char **)(hdr + 4));
            *(int *)(t + 8) = 0;
            *(char **)(*(char **)(t + 4) + 8) = *(char **)(t + 4);
            *(char **)(*(char **)(t + 4) + 4) = 0;
            *(char **)(*(char **)(t + 4) + 12) = *(char **)(t + 4);
        }
    } else {
        while (*first != *last) {
            It4 c = (*(It4 *)first)++;
            char *hh = *(char **)(t + 4);
            char *n = f_05cc58(c.p, hh + 4, hh + 8, hh + 12);
            f_04ed28(n + 32);
            f_04e4b4(n);
            *(int *)(t + 8) -= 1;
        }
    }
}
struct E { const char *name; int a, b, c; E() {} };
extern char D_291418[];
extern E D_291900[];
extern char D_1a3388[], D_1a3390[], D_1a339c[], D_1a33a8[], D_1a33b0[], D_1a33bc[], D_1a33c4[];
static inline void ini(E *p, int a, int b, int c) { p->a = a; p->b = b; p->c = c; }
/* @draft 0x065c80 us f_065c80
   WHAT IT DOES: one-time initialisation (guarded by the byte at D_291418) of the 8-entry table at D_291900 (name string, kind and three integers per entry: attachSound, getPan, getVolume, setPan, setVolume, start, stop and a terminator); returns the table.
   Remaining difference: store scheduling and pointer CSE of the entries */
E *f_065c80(void) {
    if (!D_291418[0]) {
        ini(D_291900 + 0, 2, 1, 0);
        ini(D_291900 + 1, 2, 0, 1);
        ini(D_291900 + 2, 2, 0, 2);
        ini(D_291900 + 3, 2, 1, 3);
        ini(D_291900 + 4, 2, 1, 4);
        ini(D_291900 + 5, 2, -1, 5);
        ini(D_291900 + 6, 2, -2, 6);
        ini(D_291900 + 7, 1, 0, 0);
        D_291900[0].name = D_1a3390;
        D_291900[1].name = D_1a3388;
        D_291900[2].name = D_1a339c;
        D_291900[3].name = D_1a33a8;
        D_291900[4].name = D_1a33b0;
        D_291900[5].name = D_1a33bc;
        D_291900[6].name = D_1a33c4;
        D_291900[7].name = 0;
        D_291418[0] = 1;
    }
    return D_291900;
}
void f_1312d4(const char *);
void f_131378(const char *);
extern char D_1a3260[];
char **f_062050(char **, char *, char *, char *, char *);
char **f_062108(char **, char *, char *, char *, char *, int);
inline bool lt5(unsigned a, unsigned b) { return a < b; }
/* @implements 0x061a08 us f_061a08
   WHAT IT DOES: basic_string::replace(pos, n1, s, n2): throws out_of_range when pos exceeds the length and length_error when the result would be too long, clamps n1 to the tail, then calls the safe replace (f_062050) when the string is shared or the source lies outside it, else the overlapping replace (f_062108). */
char **f_061a08(char **self, unsigned pos, unsigned n1, char *s, unsigned n2) {
    unsigned size = *(unsigned *)(*self - 12);
    if (pos > size) f_131378(D_1a3260);
    unsigned rem = size - pos;
    if (!(n1 < rem)) n1 = rem;
    if (0x3ffffffc - n2 < size - n1) f_1312d4(D_1a3260);
    char *d = *self;
    if (*(int *)(d - 4) > 0 || lt5((unsigned)s, (unsigned)d) || lt5((unsigned)(d + size), (unsigned)s))
        goto safe;
    return f_062108(self, d + pos, d + pos + n1, s, s + n2, 0);
safe:
    return f_062050(self, d + pos, d + pos + n1, s, s + n2);
}
int memcmp(const void *, const void *, unsigned) throw();
void f_05db84(void *);
char *f_15c098(int, int, int);
struct S { char *p; int pad[3]; S() {} S(const S &o) { p = o.p; } ~S() { f_05db84(this); } };
void f_05a3e8(S *, char *, void *);
void f_05e4a8(S *, int);
typedef void (*VF)(S *, void *);
typedef S (*VFR)(void *);
inline const unsigned &mn(const unsigned &a, const unsigned &b) { if (b < a) return b; return a; }
inline bool eqsa(S &s1, S &s2) {
    const char *d1 = s1.p;
    unsigned la = *(unsigned *)(d1 - 12);
    unsigned lb = *(unsigned *)(s2.p - 12);
    int r = memcmp(d1, s2.p, mn(la, lb));
    if (!r) r = la - lb;
    return r == 0;
}
inline bool eqs2a(S &s1, S &s2) {
    const char *d2 = s2.p;
    unsigned la = *(unsigned *)(s1.p - 12);
    unsigned lb = *(unsigned *)(d2 - 12);
    int r = memcmp(s1.p, d2, mn(la, lb));
    if (!r) r = la - lb;
    return r == 0;
}
/* @draft 0x0646c0 us f_0646c0
   WHAT IT DOES: compares a string with the name string of the argument object (virtual call at +84): builds the left string from the member at +16 (a literal copy when it is -1, else a lookup through f_15c098/f_05a3e8) or takes the string member at +28 when the flag byte at +8 is set, then compares them with memcmp and the length difference; returns whether they are equal.
   Remaining difference: stack slot of the length pair and one landing pad arrangement (24/94 words) */
bool f_0646c0(unsigned char *self, int *other) {
    bool res;
    S t1;
    if (self[8]) {
        (*(VF *)(*other + 84))(&t1, other);
        res = eqs2a(*(S *)((char *)self + 28), t1);
    } else {
        int k = *(int *)((char *)self + 16);
        if (k == -1) f_05e4a8(&t1, *(int *)((char *)self + 24));
        else {
            Tmp16 g;
            f_05a3e8(&t1, f_15c098(*(int *)(*(int *)((char *)self + 12) + 4), 7, k), &g);
        }
        S t2 = (*(VFR *)(*other + 84))(other);
        res = eqsa(t1, t2);
    }
    return res;
}
inline bool eqsb(S &s1, S &s2) {
    const char *d1 = s1.p;
    unsigned la = *(unsigned *)(d1 - 12);
    unsigned lb = *(unsigned *)(s2.p - 12);
    int r = memcmp(d1, s2.p, mn(la, lb));
    if (!r) r = la - lb;
    return r < 0;
}
inline bool eqs2b(S &s1, S &s2) {
    const char *d2 = s2.p;
    unsigned la = *(unsigned *)(s1.p - 12);
    unsigned lb = *(unsigned *)(d2 - 12);
    int r = memcmp(s1.p, d2, mn(la, lb));
    if (!r) r = la - lb;
    return r < 0;
}
/* @draft 0x064838 us f_064838
   WHAT IT DOES: compares a string with the name string of the argument object (virtual call at +84): builds the left string from the member at +16 (a literal copy when it is -1, else a lookup through f_15c098/f_05a3e8) or takes the string member at +28 when the flag byte at +8 is set, then compares them with memcmp and the length difference; returns whether the left is less than the right.
   Remaining difference: stack slot of the length pair and one landing pad arrangement (24/94 words) */
bool f_064838(unsigned char *self, int *other) {
    bool res;
    S t1;
    if (self[8]) {
        (*(VF *)(*other + 84))(&t1, other);
        res = eqs2b(*(S *)((char *)self + 28), t1);
    } else {
        int k = *(int *)((char *)self + 16);
        if (k == -1) f_05e4a8(&t1, *(int *)((char *)self + 24));
        else {
            Tmp16 g;
            f_05a3e8(&t1, f_15c098(*(int *)(*(int *)((char *)self + 12) + 4), 7, k), &g);
        }
        S t2 = (*(VFR *)(*other + 84))(other);
        res = eqsb(t1, t2);
    }
    return res;
}
inline bool eqsc(S &s1, S &s2) {
    const char *d1 = s1.p;
    unsigned la = *(unsigned *)(d1 - 12);
    unsigned lb = *(unsigned *)(s2.p - 12);
    int r = memcmp(d1, s2.p, mn(la, lb));
    if (!r) r = la - lb;
    return r > 0;
}
inline bool eqs2c(S &s1, S &s2) {
    const char *d2 = s2.p;
    unsigned la = *(unsigned *)(s1.p - 12);
    unsigned lb = *(unsigned *)(d2 - 12);
    int r = memcmp(s1.p, d2, mn(la, lb));
    if (!r) r = la - lb;
    return r > 0;
}
/* @draft 0x0649b0 us f_0649b0
   WHAT IT DOES: compares a string with the name string of the argument object (virtual call at +84): builds the left string from the member at +16 (a literal copy when it is -1, else a lookup through f_15c098/f_05a3e8) or takes the string member at +28 when the flag byte at +8 is set, then compares them with memcmp and the length difference; returns whether the left is greater than the right.
   Remaining difference: stack slot of the length pair and one landing pad arrangement (24/94 words) */
bool f_0649b0(unsigned char *self, int *other) {
    bool res;
    S t1;
    if (self[8]) {
        (*(VF *)(*other + 84))(&t1, other);
        res = eqs2c(*(S *)((char *)self + 28), t1);
    } else {
        int k = *(int *)((char *)self + 16);
        if (k == -1) f_05e4a8(&t1, *(int *)((char *)self + 24));
        else {
            Tmp16 g;
            f_05a3e8(&t1, f_15c098(*(int *)(*(int *)((char *)self + 12) + 4), 7, k), &g);
        }
        S t2 = (*(VFR *)(*other + 84))(other);
        res = eqsc(t1, t2);
    }
    return res;
}
}
}

/* ---- swg6a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg6a: untagged functions of the SWG player (big_e, big_a). */

namespace swg6a {
extern "C" {
void *f_04dfa0(unsigned n);
void *f_05db08(unsigned n);
void f_05daa4(void *self, void *a1);
void f_05db44(void *);
void f_04ed28(void *);
void *f_15c098(void *, int, int);
int f_15c07c(void *, int, int);
void *f_154448(void *, void *, void *, int);
void f_15fb50(void *, int);
void *f_15faf0(void *, int);
void *f_15fa60(void *, void *);
void f_05f374(void *, void *, int);
char *f_05f0b8(void *, void *);
void f_05f524(void *, void *, void *);
void f_05df24(void *, void *);
void f_05f6a8(void *, unsigned, void *);
void f_05f954(void *, void *, void *);
void f_05f998(void *, void *, void *, void *);
void f_05f5dc(void *, void *, void *);
void f_06b050(void *, int);
extern char D_1a4900[], D_1a493c[], D_1a4d14[];
}

struct Ref { int a, b; Ref(void *p); ~Ref() {} };
inline Ref::Ref(void *p) { f_05daa4(this, p); }
struct It4 { int *p; It4() {} It4(const It4 &o) { p = o.p; } };
struct Pr { int k, v; };
struct Hd { int a, b; ~Hd() { f_04ed28(this); } };
struct Obj64 {
    char pad[64];
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    Obj64(void *x) { f_05f374(this, x, 1); }
};

extern "C" {
/* @draft 0x0678b0 us f_0678b0
   WHAT IT DOES: registers a new child object for the slot index (taken modulo 16384) under the player: reads the character id from the stream argument, resolves it through the player, finds the object of the given type, creates a node and a 64-byte holder for it, appends the node to the player's list at +348 with the given 16-byte record, passes the handle to two virtual calls, stores the node in the object's slot vector (growing it) and records the slot index in the object's map at +48.    Remaining difference: stack-slot layout of the locals (X lives at 112 instead of 176), register assignment of s5/s6, and the delay-slot scheduling of the slot-vector lookup. */
void f_0678b0(char *self, char *obj, int *strm, int *rec, int idx, int *flag)
{
    int s2 = idx;
    if (idx >= 16384) s2 = idx - 16384;
    int ch;
    void *pl = *(void **)(self + 4);
    if (strm[1] == -1) {
        int *sb = (int *)strm[3];
        *(char *)((char *)sb + *(int *)(*(int *)sb - 12)) = D_1a4d14[0];
        ch = *sb;
    } else {
        ch = (int)f_15c098((void *)((int *)strm[0])[1], 7, strm[1]);
    }
    int s0 = f_15c07c(pl, 4, ch);
    if (s0 == -1) return;
    if (!obj) return;
    char *s1 = (char *)f_154448(obj, D_1a4900, D_1a493c, 0);
    if (!s1) return;
    char *s5 = s1 + 32;
    void *s4 = ((void *(**)(void *))*(void **)s1)[9](s1);
    void *a0 = 0;
    if (s2 < (unsigned)((*(int *)(s5 + 8) - *(int *)(s5 + 4)) >> 2))
        a0 = ((void **)*(void **)(s1 + 36))[s2];
    if (a0) f_15fb50(a0, 0);
    void *X = f_15faf0(s4, s0);
    Obj64 *o = new Obj64(X);
    Ref r(o);
    *(int *)((char *)X + 332) = r.a;
    {
        Hd h;
        h.a = *(int *)(self + 372);
        h.b = *(int *)(self + 376);
        if (h.b) ++*(int *)h.b;
        ((void (**)(void *, void *, void *))*(void **)r.a)[14]((void *)r.a, self + 152, &h);
    }
    if (*flag) ((void (**)(void *, int))*(void **)r.a)[17]((void *)r.a, *flag);
    char *s3 = f_05f0b8(self + 348, &X);
    int rec2[4] = {rec[0], rec[1], rec[2], rec[3]};
    {
        Hd h;
        h.a = r.a; h.b = r.b;
        if (h.b) ++*(int *)h.b;
        int out[6];
        f_05f524(out, rec2, &h);
        *(int *)s3 = out[0]; *(int *)(s3 + 12) = out[3];
        *(int *)(s3 + 4) = out[1]; *(int *)(s3 + 8) = out[2];
        f_05df24(s3 + 16, out + 4);
    }
    {
        Hd h;
        h.a = r.a; h.b = r.b;
        if (h.b) ++*(int *)h.b;
        ((void (**)(void *, void *, void *))*(void **)s1)[14](s1, rec, &h);
    }
    void *k = X;
    if (!(s2 < (unsigned)((*(int *)(s5 + 8) - *(int *)(s5 + 4)) >> 2))) {
        int z = 0;
        f_05f6a8(s5, s2 + 1, &z);
    }
    *(void **)(*(char **)(s1 + 36) + s2 * 4) = k;
    char *m = s1 + 48;
    int *it;
    f_05f954(&it, m, &k);
    int *hd = *(int **)(m + 4);
    if (it == hd || (unsigned)k < (unsigned)it[4]) {
        int *res;
        int pr[2] = {(int)k, 0};
        f_05f998(&res, m, &it, pr);
        it = res;
    }
    it[5] = s2;
}
/* @draft 0x06b0f0 us f_06b0f0
   WHAT IT DOES: for a non-null object, resolves its node through the player's table, and when the node has a parent object, looks the parent up in the player's list at +348, narrows it with a checked cast and frees the previous slot entry; then creates a 64-byte holder and handle for the node, passes the handle to a virtual call, appends a record copy to the list, and when a parent exists passes the handle to the parent's virtual call, stores the node in the parent's slot vector (growing it) and records the slot index in the parent's map at +48.    Remaining difference: unchecked; the dead stores of the first lookup (sp+0) are not reproduced and the local layout is not matched. */
void f_06b0f0(char *self, char *obj, int *rec, int idx)
{
    int s3 = idx;
    if (idx >= 16384) s3 = idx - 16384;
    char *s4 = 0;
    if (!obj) return;
    void *q = *(void **)(*(char **)(self + 344) + 4);
    void *pa = *(void **)((char *)q + 8);
    void *v = ((void *(**)(void *))*(void **)pa)[9](pa);
    char *X0 = (char *)f_15fa60(obj, v);
    int p192 = *(int *)(X0 + 20);
    if (p192) {
        char *n = f_05f0b8(self + 348, &p192);
        void *a0 = *(void **)(n + 16);
        void *r0 = 0;
        if (a0) r0 = f_154448(a0, D_1a4900, D_1a493c, 0);
        s4 = (char *)r0;
        char *vec = s4 + 32;
        void *sl = 0;
        if ((unsigned)s3 < (unsigned)((*(int *)(vec + 8) - *(int *)(vec + 4)) >> 2))
            sl = ((void **)*(void **)(s4 + 36))[s3];
        if (sl) f_15fb50(sl, 0);
    }
    Obj64 *o = new Obj64(X0);
    Ref r(o);
    *(int *)(X0 + 332) = r.a;
    {
        Hd h;
        h.a = *(int *)(self + 372);
        h.b = *(int *)(self + 376);
        if (h.b) ++*(int *)h.b;
        ((void (**)(void *, void *, void *))*(void **)r.a)[14]((void *)r.a, self + 152, &h);
    }
    char *s1 = f_05f0b8(self + 348, &X0);
    int rec2[4] = {rec[0], rec[1], rec[2], rec[3]};
    {
        Hd h;
        h.a = r.a; h.b = r.b;
        if (h.b) ++*(int *)h.b;
        int out[6];
        f_05f524(out, rec2, &h);
        *(int *)s1 = out[0]; *(int *)(s1 + 12) = out[3];
        *(int *)(s1 + 4) = out[1]; *(int *)(s1 + 8) = out[2];
        f_05df24(s1 + 16, out + 4);
    }
    if (p192) {
        {
            Hd h;
            h.a = r.a; h.b = r.b;
            if (h.b) ++*(int *)h.b;
            ((void (**)(void *, void *, void *))*(void **)s4)[14](s4, rec, &h);
        }
        char *vec = s4 + 32;
        void *k = X0;
        if (!((unsigned)s3 < (unsigned)((*(int *)(vec + 8) - *(int *)(vec + 4)) >> 2))) {
            int z = 0;
            f_05f6a8(vec, s3 + 1, &z);
        }
        *(void **)(*(char **)(s4 + 36) + s3 * 4) = k;
        char *m = s4 + 48;
        int *it;
        f_05f954(&it, m, &k);
        int *hd = *(int **)(m + 4);
        if (it == hd || (unsigned)k < (unsigned)it[4]) {
            int *res;
            int pr[2] = {(int)k, 0};
            f_05f998(&res, m, &it, pr);
            it = res;
        }
        it[5] = s3;
    }
}
/* @draft 0x068bc0 us f_068bc0
   WHAT IT DOES: when both objects share the same non-zero parent, finds the parent in the player's list, narrows it with a checked cast, looks both objects up in the parent's map at +48 for their slot indices, removes both entries (f_06b050), then stores each object into the other's slot of the slot vector (growing it as needed) and records the swapped slot index in the map.    Remaining difference: callee-saved register assignment (parent pointer lands in s5 instead of s3, the two slot indices swap s5/s7) and 12 bytes of size. */
void f_068bc0(char *self, char *a, char *b)
{
    int k = *(int *)(a + 20);
    if (!k) return;
    if (k != *(int *)(b + 20)) return;
    char *n = f_05f0b8(self + 348, &k);
    void *pa0 = *(void **)(n + 16);
    char *par = pa0 ? (char *)f_154448(pa0, D_1a4900, D_1a493c, 0) : 0;
    char *m = par + 48;
    It4 i0; It4 i16; It4 i32; It4 i48; Pr p64; It4 i80; Pr p96;
    char *ka = a; char *kb = b;
    f_05f5dc(&i0, m, &ka);
    int s7 = -1;
    int *hd = *(int **)(m + 4);
    i16.p = hd;
    if (i0.p != hd) s7 = i0.p[5];
    f_05f5dc(&i16, m, &kb);
    int s5 = -1;
    hd = *(int **)(m + 4);
    i0.p = hd;
    if (i16.p != hd) s5 = i16.p[5];
    if ((s5 | s7) < 0) return;
    f_06b050(par, (int)a);
    f_06b050(par, (int)b);
    char *vec = par + 32;
    unsigned sz = (unsigned)((*(int *)(vec + 8) - *(int *)(vec + 4)) >> 2);
    if (!((unsigned)s5 < sz)) {
        int z = 0;
        f_05f6a8(vec, s5 + 1, &z);
    }
    char *ka2 = a;
    (*(char ***)(par + 36))[s5] = ka2;
    f_05f954(&i16, m, &ka2);
    hd = *(int **)(m + 4);
    int *t = i16.p;
    i0.p = hd;
    if (t == hd || (unsigned)ka2 < (unsigned)t[4]) {
        p64.k = (int)ka2; p64.v = 0;
        i80.p = t;
        i48.p = t;
        f_05f998(&i32, m, &i80, &p64);
        i16.p = i32.p;
        t = i32.p;
    }
    t[5] = s5;
    sz = (unsigned)((*(int *)(vec + 8) - *(int *)(vec + 4)) >> 2);
    if (!((unsigned)s7 < sz)) {
        int z = 0;
        f_05f6a8(vec, s7 + 1, &z);
    }
    char *kb2 = b;
    (*(char ***)(par + 36))[s7] = kb2;
    f_05f954(&i80, m, &kb2);
    hd = *(int **)(m + 4);
    t = i80.p;
    i48.p = hd;
    if (t == hd || (unsigned)kb2 < (unsigned)t[4]) {
        p96.k = (int)kb2; p96.v = 0;
        i0.p = t;
        i16.p = t;
        f_05f998(&i32, m, &i0, &p96);
        i80.p = i32.p;
        t = i32.p;
    }
    t[5] = s7;
}
}
}

/* ---- swg6c ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 wave 4, worker swg6c */
namespace swg6c {
extern "C" {

void *f_04dfa0(int);
int rand(void);
extern char D_1a4320[];
void f_04ed28(void *);
void f_04e4b4(void *);
void f_04e8c0(void *);
void f_04e8d8(void *);
int f_05df80(void *, void *);
void f_05f64c(void *, void *, void *);
void f_05e394(void *, void *, void *, void *);
void f_05daa4(void *, void *);
void f_05daec(void *);
void f_05db84(void *);
void f_05e4a8(void *, void *);
void f_05a61c(void *, void *, void *);
void *f_154448(void *, void *, void *, int);
int f_15c098(void *, int);
int iprintf(const char *, ...);
void *f_05b964(void *, void *, void *, void *, int);
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
extern char D_291400[];
extern char D_1a3014[], D_1a301c[], D_1a3024[], D_1a302c[], D_1a4060[], D_1a4270[], D_1a43d0[];
extern char D_1a3760[], D_1a3d60[], D_1a4900[], D_1a4960[], D_1a4d14[];

/* reference-counted pointer pair: object and a heap count; the destructor is f_04ed28 */
struct Ref {
    char *p;
    int *rc;
    ~Ref() { f_04ed28(this); }
};
struct Tag { char *p0; int b; int p2; char *p3; };
struct StrH { char *p; StrH() {} StrH(const StrH &a) { f_05e4a8(this, (void *)&a); } };
struct P8 { int a, b; };
struct Pa { virtual char m() = 0; };
struct Pb { virtual P8 m() = 0; };
struct Pc { virtual StrH m() = 0; };
typedef char (Pa::*PmA)();
typedef P8 (Pb::*PmB)();
typedef StrH (Pc::*PmC)();

static inline void *vf(void *p, int i) { return (*(void ***)p)[i]; }
static inline char *top(char *t) { return *(char **)(*(char **)(t + 4) + 4); }
static inline void ref_load(Ref *r, char *t) {
    char *n = top(t);
    r->p = *(char **)(n + 8);
    r->rc = *(int **)(n + 12);
    if (r->rc) *r->rc += 1;
}
static inline void pop(char *t) {
    char out[16];
    char *it = top(t);
    f_05f64c(out, t, &it);
}
static inline void push(char *t, Ref *h) {
    char out[16];
    int pos = *(int *)(t + 4);
    f_05e394(out, t, &pos, h);
}
static inline char *empty_str() {
    char *s = D_291400;
    int st = sceKernelCpuSuspendIntr();
    *(int *)(s + 8) += 1;
    sceKernelCpuResumeIntr(st);
    return s + 12;
}
/* empty tree header: node allocated and linked to itself */
static inline void init_map(char *m) {
    *(int *)(m + 4) = 0;
    int *n = (int *)f_04dfa0(40);
    *(int **)(m + 4) = n;
    n[1] = 0;
    *(int *)(m + 8) = 0;
    n[2] = (int)n;
    n[0] = 0;
    n[3] = (int)n;
}

/* @draft 0x05aaf8 us f_05aaf8
   WHAT IT DOES: ActionScript context native-call dispatcher. Asks the called object (virtual +80) for a tag, then compares it with the name entries at +168..+248 of the context. +168 and +216 run virtual hooks +264 and +268. +184, +200 and +232 pop the argument on top of the stack at +328, call a pointer-to-member getter on the next argument (char, 8-byte pair or string), pop that many further entries and push a new boxed value object (vtables D_1a4060, D_1a4270, D_1a43d0). +248 pops its arguments and pushes a new 60-byte object configured via virtual +56 with the context's reference at +380. Otherwise it looks the tag up with f_05a61c and, if the result casts (f_154448) builds a 28-byte object and hands it to f_05b964; if not it prints the "ASContextImpl::NewInternal" diagnostic via iprintf and discards the arguments. Always finishes with virtual +68 on the context and returns the hidden result pointer.
   Remaining difference: not compared; draft transcription of the whole body, register allocation and landing-pad layout will differ. */
char *f_05aaf8(char *s0, char *s6, void **a2) {
    Tag tag;
    void *obj = *a2;
    ((void (*)(Tag *, void *, void *))vf(obj, 20))(&tag, obj, s0);
    char *t = s0 + 328;
    if (f_05df80(&tag, s0 + 168)) {
        ((void (*)(void *))vf(s0, 66))(s0);
        ((void (*)(void *))vf(s0, 17))(s0);
        return s6;
    }
    if (f_05df80(&tag, s0 + 184)) {
        PmA pm = *(PmA *)D_1a3014;
        Ref a;
        ref_load(&a, t);
        pop(t);
        int n = ((int (*)(void *))vf(a.p, 23))(a.p);
        int *o = (int *)f_04dfa0(16);
        o[0] = 16;
        int *ob = o + 1;
        char v = 0;
        if (n > 0) {
            Pa *tg = (Pa *)*(char **)(top(t) + 8);
            v = (tg->*pm)();
        }
        ob[0] = (int)D_1a4060;
        *(char *)(ob + 2) = v;
        ob[1] = 0;
        for (int i = 0; i < n; i++) pop(t);
        Ref h;
        f_05daa4(&h, ob);
        push(t, &h);
        ((void (*)(void *))vf(s0, 17))(s0);
        return s6;
    }
    if (f_05df80(&tag, s0 + 200)) {
        PmB pm = *(PmB *)D_1a301c;
        Ref a;
        ref_load(&a, t);
        pop(t);
        int n = ((int (*)(void *))vf(a.p, 23))(a.p);
        int *o = (int *)f_04dfa0(20);
        o[0] = 20;
        int *ob = o + 1;
        P8 v;
        v.a = 0;
        v.b = 0;
        if (n > 0) {
            Pb *tg = (Pb *)*(char **)(top(t) + 8);
            v = (tg->*pm)();
        }
        ob[0] = (int)D_1a4270;
        ob[2] = v.a;
        ob[3] = v.b;
        ob[1] = 0;
        for (int i = 0; i < n; i++) pop(t);
        Ref h;
        f_05daa4(&h, ob);
        push(t, &h);
        ((void (*)(void *))vf(s0, 17))(s0);
        return s6;
    }
    if (f_05df80(&tag, s0 + 216)) {
        ((void (*)(void *))vf(s0, 67))(s0);
        ((void (*)(void *))vf(s0, 17))(s0);
        return s6;
    }
    if (f_05df80(&tag, s0 + 232)) {
        PmC pm = *(PmC *)D_1a3024;
        Ref a;
        ref_load(&a, t);
        pop(t);
        int n = ((int (*)(void *))vf(a.p, 23))(a.p);
        int *o = (int *)f_04dfa0(36);
        o[0] = 36;
        int *ob = o + 1;
        StrH str;
        bool have = true;
        if (n > 0) {
            Pc *tg = (Pc *)*(char **)(top(t) + 8);
            str = (tg->*pm)();
        } else {
            str.p = empty_str();
        }
        ob[0] = (int)D_1a43d0;
        *(char *)(ob + 2) = 1;
        ob[4] = -1;
        ob[1] = 0;
        ob[3] = 0;
        ob[5] = 0;
        ob[6] = 0;
        f_05e4a8(ob + 7, &str);
        have = false;
        f_05db84(&str);
        for (int i = 0; i < n; i++) pop(t);
        Ref h;
        f_05daa4(&h, ob);
        push(t, &h);
        f_05daec(&h);
        ((void (*)(void *))vf(s0, 17))(s0);
        return s6;
    }
    if (f_05df80(&tag, s0 + 248)) {
        char *a1 = *(char **)(top(t) + 8);
        int n = ((int (*)(void *))vf(a1, 23))(a1);
        pop(t);
        while (n > 0) { n--; pop(t); }
        int *o = (int *)f_04dfa0(60);
        o[0] = 60;
        char *s1 = (char *)(o + 1);
        char *s3 = (char *)(o + 3);
        *(char **)s1 = D_1a3760;
        *(int *)(s1 + 4) = 0;
        *(int *)(s3 + 4) = 0;
        init_map(s3);
        *(char **)s1 = D_1a3d60;
        *(char **)(s1 + 24) = D_1a43d0;
        *(char *)(s1 + 32) = 1;
        *(int *)(s1 + 40) = -1;
        *(int *)(s1 + 36) = 0;
        *(int *)(s1 + 44) = 0;
        *(int *)(s1 + 48) = 0;
        *(int *)(s1 + 28) = 0;
        *(char **)(s1 + 52) = empty_str();
        {
            Ref r;
            r.p = *(char **)(s0 + 380);
            r.rc = *(int **)(s0 + 384);
            if (r.rc) *r.rc += 1;
            ((void (*)(void *, void *, Ref *))vf(s1, 14))(s1, s0 + 152, &r);
        }
        Ref h;
        h.p = s1;
        h.rc = 0;
        int *c = (int *)f_04dfa0(4);
        *c = 1;
        h.rc = c;
        push(t, &h);
        return s6;
    }
    Ref r;
    f_05a61c(&r, s0, &tag);
    void *s3;
    if (r.p && (s3 = f_154448(r.p, D_1a4900, D_1a4960, 0)) != 0) {
        char *o = (char *)f_04dfa0(28);
        *(int *)o = 28;
        char *s2 = o + 4;
        char *s1 = o + 12;
        *(char **)s2 = D_1a3760;
        *(int *)(s2 + 4) = 0;
        init_map(s1);
        Ref r2;
        r2.p = s2;
        r2.rc = 0;
        if (s2) {
            int *c = (int *)f_04dfa0(4);
            *c = 1;
            r2.rc = c;
        }
        {
            Ref out;
            ((void (*)(Ref *, void *, void *))vf(s3, 13))(&out, s3, s0 + 120);
            ((void (*)(void *, void *, Ref *))vf(s2, 14))(s2, s0 + 152, &out);
        }
        Ref cp;
        cp.p = r2.p;
        cp.rc = r2.rc;
        if (cp.rc) *cp.rc += 1;
        s6 = (char *)f_05b964(s0, &cp, s3, s6, 1);
        return s6;
    }
    long s1;
    if (tag.b == -1) {
        char *a1 = tag.p3;
        char *vt = *(char **)a1;
        *(char *)(vt + *(int *)(vt - 12)) = *D_1a4d14;
        s1 = *(int *)a1;
    } else {
        s1 = f_15c098(*(char **)(tag.p0 + 4), 7);
    }
    iprintf(D_1a302c, s1, ((void *(*)(void *))vf(r.p, 7))(r.p));
    {
        Ref a;
        ref_load(&a, t);
        int n = ((int (*)(void *))vf(a.p, 23))(a.p);
        pop(t);
        for (int i = 0; i < n; i++) pop(t);
    }
    ((void (*)(void *))vf(s0, 17))(s0);
    ((void (*)(void *))vf(s0, 17))(s0);
    return s6;
}

/* @draft 0x05687c us f_05687c
   WHAT IT DOES: takes a reference to the top argument of the stack at +328 and pops it, asks it (virtual +80) for a tag, looks the tag up with f_05a61c and casts the result with f_154448, then calls f_05b964 with a copy of the reference pair at +288 and returns its result.
   Remaining difference: the iterator temporaries (retail keeps a stack-slot iterator at sp+16 and a 144-byte frame; ours is 128), 88/93 words differ. */
char *f_05687c(char *s0, char *s2) {
    Ref a;
    ref_load(&a, s0 + 328);
    pop(s0 + 328);
    Tag tag;
    ((void (*)(Tag *, void *, void *))vf(a.p, 20))(&tag, a.p, s0);
    Ref r;
    f_05a61c(&r, s0, &tag);
    void *c = 0;
    if (r.p) c = f_154448(r.p, D_1a4900, D_1a4960, 0);
    struct Ref16 : Ref { int pad[2]; } cp;
    cp.p = *(char **)(s0 + 288);
    cp.rc = *(int **)(s0 + 292);
    if (cp.rc) *cp.rc += 1;
    return (char *)f_05b964(s0, &cp, c, s2, 0);
}

struct It { char *n; It() {} It(const It &o) { n = o.n; } };
static inline It begin_it(char *t) { It r; r.n = *(char **)(t + 4); r.n = *(char **)(r.n + 4); return r; }
static inline void load(Ref *a, const It &b) {
    a->p = *(char **)(b.n + 8);
    a->rc = *(int **)(b.n + 12);
    if (a->rc) *a->rc += 1;
}
static inline It erase(char *t, It pos) { It r; f_05f64c(&r, t, &pos); return r; }
static inline It end_it(char *t) { It r; r.n = *(char **)(t + 4); return r; }
static inline It insert(char *t, It pos, Ref *h) { It r; f_05e394(&r, t, &pos, h); return r; }

/* @draft 0x058c10 us f_058c10
   WHAT IT DOES: pops the top argument off the stack at +328 and asks it for a count (virtual +92), then pushes a new 16-byte boxed object (vtable D_1a4320) holding rand() modulo that count (zero when the count is zero).
   Remaining difference: the stack-slot iterator temporaries (size 364 vs 388); the iterator class does not yet reproduce retail's 16/32/48 slot layout. */
void f_058c10(char *s) {
    char *t = s + 328;
    Ref a;
    load(&a, begin_it(t));
    erase(t, begin_it(t));
    int n = ((int (*)(void *))vf(a.p, 23))(a.p);
    int *o = (int *)f_04dfa0(16);
    o[0] = 16;
    int *ob = o + 1;
    int r = rand();
    int v = 0;
    if (n) v = r % n;
    ob[0] = (int)D_1a4320;
    ob[2] = v;
    ob[1] = 0;
    Ref h;
    h.p = (char *)ob;
    h.rc = 0;
    if (ob) { int *c = (int *)f_04dfa0(4); *c = 1; h.rc = c; }
    insert(t, end_it(t), &h);
}

}  // extern "C"
}  // namespace swg6c

/* ---- swg6b ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg6b: large untagged functions of the SWG player (big_b). */
namespace swg6b {
extern "C" {
#define Q6(o, off) (*(int *)((char *)(o) + (off)))
void *f_04dfa0(unsigned); void f_04ed28(void *); void f_04e4b4(void *); void f_04eee8(void *, void *);
void f_05f4d0(void *, void *, void *); void f_05daa4(void *, void *);
int f_15c0f0(int, int); int f_15c07c(int, int, void *);
void f_05f1f4(void *, void *, void *); void f_05f238(void *, void *, void *, void *);
void f_05a3e8(void *, void *, void *); void f_05e540(void *, void *, void *);
int sprintf(char *, const char *, ...);
unsigned sceKernelCpuSuspendIntr(void); void sceKernelCpuResumeIntr(unsigned);
extern char D_1a3760[], D_1a41c0[];
struct Em6 { ~Em6() {} };
struct Hd6 { int *p; int *c; ~Hd6() { f_04ed28(this); } };
struct Str6 {
  char *p;
  ~Str6() {
    Em6 g; char *s0 = p; char *s2 = s0 - 12;
    unsigned intr = sceKernelCpuSuspendIntr();
    volatile int *c = (volatile int *)(s0 - 4);
    int s1 = *c; *c += -1;
    sceKernelCpuResumeIntr(intr);
    if (s1 <= 0) f_04eee8(s2, &g);
  }
};
/* the 68-byte object built by f_050e04: a vtable, a tree header, the owner key and a sub-object */
struct Obj6 {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  Obj6(void *owner) {
    Em6 e;
    Q6(this, 0) = (int)D_1a3760;
    Q6(this, 4) = 0; Q6(this, 12) = 0;
    int *n = (int *)f_04dfa0(40);
    Q6(this, 12) = (int)n; n[1] = 0;
    Q6(this, 0) = (int)D_1a41c0;
    n[2] = (int)n; n[3] = (int)n;
    Q6(this, 24) = (int)owner;
    Q6(this, 16) = 0; n[0] = 0;
    *((char *)this + 28) = 0;
    Q6(this, 36) = 0; Q6(this, 40) = 0; Q6(this, 44) = 0;
    int pad[16];
    f_05f4d0((char *)this + 48, (char *)&owner - 4, pad);
  }
};
struct Pr6 {
  Obj6 *p; int *cnt;
  Pr6(Obj6 *o) { p = o; cnt = 0; if (o) { cnt = (int *)f_04dfa0(4); *cnt = 1; } }
  ~Pr6() { f_04ed28(this); }
};
/* find the node for *kp in the tree, inserting a default entry (key, 4 zero-ish words, empty handle) when absent */
static inline char *slot6(char *tree, int *kp) {
  char *it;
  f_05f1f4(&it, tree, kp);
  char *end = *(char **)(tree + 4);
  if (it == end || (unsigned)*kp < (unsigned)Q6(it, 16)) {
    int tmp[6]; char *hint = it, *res;
    tmp[0] = 0; tmp[1] = -1; tmp[2] = 0; tmp[3] = 0;
    f_05daa4(&tmp[4], 0);
    int pr[7];
    pr[0] = *kp; pr[1] = tmp[0]; pr[2] = tmp[1]; pr[3] = tmp[2]; pr[4] = tmp[3]; pr[5] = tmp[4]; pr[6] = tmp[5];
    if (pr[6]) ++*(int *)pr[6];
    f_05f238(&res, tree, &hint, pr);
    it = res;
    f_04ed28(&pr[5]);
    f_04ed28(&tmp[4]);
  }
  return it;
}

extern char D_1a2e94[]; /* "_mc%p_" */

/* @draft 0x050e04 us f_050e04
   WHAT IT DOES: builds a new 68-byte child object keyed by the argument object and stores it at +332 of that object; hands the object a copy of the player's counted handle (+372/+376) through virtual slot 14; then registers a four-word record {player, id, tree, name} in the map at +348 under the argument object's key (the id comes from f_15c0f0 for the argument's slot at +164, or from a generated "_mc%p_" name looked up through f_15c07c and the string map at +8), and finally, when the argument has a parent at +20, looks that parent up (inserting a default if absent) and calls virtual slot 14 of the parent's registered handle with the record and the object holder; with no parent the holder is stored into the player at +280.
   Remaining difference: not scored; raw transcription of the tree insert helpers with open-coded copies, landing pads and register allocation unmatched. */
void f_050e04(char *self, char *P) {
  Pr6 pr(new Obj6(P));
  Q6(P, 332) = (int)pr.p;
  Hd6 h; h.p = (int *)Q6(self, 372); h.c = (int *)Q6(self, 376);
  if (h.c) ++*h.c;
  ((void (*)(void *, void *, void *))(*(void ***)pr.p)[14])(pr.p, self + 152, &h);
  int rec[4];
  rec[0] = 0; rec[1] = -1; rec[2] = 0; rec[3] = 0;
  int id = Q6(P, 164);
  if (id == -1) {
    char buf[64];
    sprintf(buf, D_1a2e94, P);
    int r = f_15c07c(Q6(self, 4), 7, buf);
    if (r == -1) {
      Str6 s; char tag[16];
      f_05a3e8(&s, buf, tag);
      char *res[2];
      f_05e540(res, self + 8, &s);
      rec[0] = (int)self; rec[1] = r; rec[2] = (int)(self + 8); rec[3] = (int)(res[0] + 16);
    } else {
      rec[0] = (int)self; rec[1] = r; rec[2] = 0; rec[3] = 0;
    }
  } else {
    int r = f_15c0f0(Q6(self, 4), id);
    rec[0] = (int)self; rec[1] = r; rec[2] = 0; rec[3] = 0;
  }
  char *tree = self + 348;
  int key = (int)P;
  char *node = slot6(tree, &key);
  {
    Hd6 t; t.p = pr.p ? (int *)pr.p : 0; t.c = pr.cnt;
    if (t.c) ++*t.c;
    Hd6 t2 = t; if (t2.c) ++*t2.c;
    Q6(node, 20) = rec[0]; Q6(node, 24) = rec[1]; Q6(node, 28) = rec[2]; Q6(node, 32) = rec[3];
    if (node + 36 != (char *)&t2) {
      f_04ed28(node + 36);
      Q6(node, 40) = (int)t2.c; Q6(node, 36) = (int)t2.p;
      if (t2.c) ++*t2.c;
    }
  }
  int par = Q6(P, 20);
  if (par) {
    int pk = par;
    char *pn = slot6(tree, &pk);
    Hd6 c; c.p = (int *)pr.p; c.c = pr.cnt; if (c.c) ++*c.c;
    void *o = (void *)Q6(pn, 36);
    ((void (*)(void *, void *, void *))(*(void ***)o)[14])(o, rec, &c);
  } else {
    char *m = self + 280;
    if (m != (char *)&pr) {
      f_04ed28(m);
      Q6(m, 4) = (int)pr.cnt; Q6(self, 280) = (int)pr.p;
      if (pr.cnt) ++*pr.cnt;
    }
  }
}


void f_05f64c(void *, void *, void *); void f_05e394(void *, void *, void *, void *);
void f_05e4a8(void *, void *); int f_15c098(int, int);
void f_05a44c(void *, const char *, void *); void f_05a578(void *, void *, void *); void f_05fadc(void *, void *);
extern char D_291400[], D_1a43d0[], D_1a2e9c[], D_1a2ea0[];
struct Ob36 {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  Ob36(void *path) {
    Em6 e;
    Q6(this, 0) = (int)D_1a43d0; Q6(this, 16) = -1; Q6(this, 4) = 0;
    *((char *)this + 8) = 1;
    Q6(this, 12) = 0; Q6(this, 24) = 0;
    f_05e4a8((char *)this + 28, path);
  }
};
struct Pr36 {
  Ob36 *p; int *cnt;
  Pr36(Ob36 *o) { p = o; cnt = 0; if (o) { cnt = (int *)f_04dfa0(4); *cnt = 1; } }
  ~Pr36() { f_04ed28(this); }
};
/* @draft 0x051ecc us f_051ecc
   WHAT IT DOES: builds the dotted path name of a chain of parent objects: starting from a copy of the handle two links down the chain at +328, walks the owner chain (virtual slot 9 of the handle, then the parent link at +20 of each registered record found or defaulted in the map at +348), prepending each record's name (the stored string, or one built from the owner's id through f_15c098) and a separator chosen by whether more parents follow; then allocates a 36-byte named object holding the resulting string and hands it to f_05e394 with the +328 sub-object.
   Remaining difference: not scored beyond the draft; the empty-string setup is open-coded and the iterator copies, landing pads and register allocation are not matched. */
void f_051ecc(char *self) {
  char *q = self + 328;
  Hd6 h; int out[4]; int b;
  int a = Q6(q, 4);
  int *v = *(int **)(a + 4);
  h.p = (int *)v[2]; h.c = (int *)v[3]; if (h.c) ++*h.c;
  b = *(int *)(a + 4);
  f_05f64c(out, q, &b);
  Str6 path;
  unsigned intr = sceKernelCpuSuspendIntr();
  int *g = (int *)D_291400;
  int old = g[2]; g[2] = old + 1;
  sceKernelCpuResumeIntr(intr);
  path.p = D_291400 + 12;
  int s0 = ((int (*)(void *))(*(void ***)h.p)[9])(h.p);
  if (s0) {
    char *tree = self + 348;
    do {
      int key = s0;
      char *node = slot6(tree, &key);
      s0 = Q6(s0, 20);
      Str6 nm, t1, t2;
      if (Q6(node, 24) == -1) {
        f_05e4a8(&nm, (void *)Q6(node, 32));
      } else {
        int o = Q6(node, 20);
        int r = f_15c098(Q6(o, 4), 7);
        char tag[16];
        f_05a3e8(&nm, (void *)r, tag);
      }
      f_05a44c(&t1, s0 ? D_1a2ea0 : D_1a2e9c, &nm);
      f_05a578(&t2, &t1, &path);
      f_05fadc(&path, &t2);
    } while (s0);
  }
  Pr36 pr(new Ob36(&path));
  int out2[4]; int a2 = Q6(q, 4);
  f_05e394(out2, q, &a2, &pr);
}


void *f_154448(void *, void *, void *, int); void *f_15fa60(int, void *); void f_15fb50(void *, int);
void *f_05db08(int); void f_05f374(void *, void *, int); void f_05dc90(void *, void *); void f_05daec(void *);
char *f_05f0b8(void *, void *); void f_05f524(void *, void *, void *); void f_05df24(void *, void *); void f_05db68(void *);
void f_05f6a8(void *, int, void *); void f_05f954(void *, void *, void *); void f_05f998(void *, void *, void *, void *);
extern char D_1a4900[], D_1a493c[];
struct Rc4 { int w[4]; };
/* take the counted handle two links down the chain at q+4 (what f_05f64c is then asked about) */
static inline void grab6(Hd6 &h, char *q, void *out) {
  int a = Q6(q, 4);
  int *v = *(int **)(a + 4);
  h.p = (int *)v[2]; h.c = (int *)v[3];
  if (h.c) ++*h.c;
  int b = *(int *)(a + 4);
  f_05f64c(out, q, &b);
}
/* @draft 0x0517f8 us f_0517f8
   WHAT IT DOES: takes three copies of the counted handle two links down the chain at +328; finds the registered parent of the object chain (virtual slot 9, f_15fa60), builds a 64-byte child object (f_05f374) wrapped in a counted handle, stores it at +332 of the child's owner, hands it the player's handle (+372) through virtual slot 14 and records {record, handle} in the map at +348; when the owner has a parent, looks that parent up in the same map (defaulting it), casts its handle's object with __dynamic_cast, notifies it through virtual slot 14 with the record, grows its element vector (+32) to the slot index (virtual slot 23 of the first handle, minus 16384 when not below it), stores the owner there and records the index in its map at +48.
   Remaining difference: not scored beyond the draft; temporaries are open-coded, landing pads and register allocation are not matched. */
void f_0517f8(char *self) {
  char *q = self + 328;
  Hd6 h0, h1, h2; int o0[4];
  grab6(h0, q, o0); grab6(h1, q, o0); grab6(h2, q, o0);
  int s0 = ((int (*)(void *))(*(void ***)h2.p)[9])(h2.p);
  Rc4 r96 = ((Rc4 (*)(void *, void *))(*(void ***)h1.p)[20])(h1.p, self);
  int s3 = ((int (*)(void *))(*(void ***)h0.p)[23])(h0.p);
  if (s3 >= 16384) s3 -= 16384;
  if (s0) {
    int *t = (int *)Q6(self, 344);
    void *a1 = (void *)((int *)t[1])[2];
    ((int (*)(void *))(*(void ***)a1)[9])(a1);
    char *P = (char *)f_15fa60(s0, a1);
    int parent = Q6(P, 20);
    char *s5 = 0;
    if (parent) {
      char *tree = self + 348;
      char *node = slot6(tree, &parent);
      void *n = (void *)Q6(node, 36);
      s5 = n ? (char *)f_154448(n, D_1a4900, D_1a493c, 0) : 0;
      char *vec = s5 + 32;
      unsigned sz = (unsigned)(Q6(vec, 8) - Q6(vec, 4)) >> 2;
      void *e = 0;
      if ((unsigned)s3 < sz) e = (void *)((int *)Q6(s5, 36))[s3];
      if (e) f_15fb50(e, 0);
    }
    void *o = f_05db08(64);
    f_05f374(o, P, 1);
    Hd6 r; f_05daa4(&r, o);
    Q6(P, 332) = (int)r.p;
    char t1[8];
    f_05dc90(t1, self + 372);
    ((void (*)(void *, void *, void *))(*(void ***)r.p)[14])(r.p, self + 152, t1);
    f_05daec(t1);
    int *val = (int *)f_05f0b8(self + 348, &P);
    Rc4 rc = r96;
    char t2[8]; f_05dc90(t2, &r);
    int ent[8];
    f_05f524(ent, &rc, t2);
    val[0] = ent[0]; val[1] = ent[1]; val[2] = ent[2]; val[3] = ent[3];
    f_05df24(val + 4, ent + 4);
    f_05db68(ent);
    f_05daec(t2);
    if (parent) {
      char t3[8];
      f_05dc90(t3, &r);
      ((void (*)(void *, void *, void *))(*(void ***)s5)[14])(s5, &r96, t3);
      f_05daec(t3);
      char *vec = s5 + 32;
      unsigned sz = (unsigned)(Q6(vec, 8) - Q6(vec, 4)) >> 2;
      int Pv = (int)P;
      if (!((unsigned)s3 < sz)) { int zero = 0; f_05f6a8(vec, s3 + 1, &zero); }
      ((int *)Q6(s5, 36))[s3] = Pv;
      char *m = s5 + 48;
      char *it; f_05f954(&it, m, &Pv);
      char *end = *(char **)(m + 4);
      if (it == end || (unsigned)Pv < (unsigned)Q6(it, 16)) {
        int pr[2]; char *hint = it, *res;
        pr[0] = Pv; pr[1] = 0;
        f_05f998(&res, m, &hint, pr);
        it = res;
      }
      Q6(it, 20) = s3;
    }
    f_05daec(&r);
  }
}


void f_05b780(void *, int); void f_05b858(void *, void *); void f_06053c(void *, void *, void *); void f_04ea4c(void *, void *, void *);
extern char D_1a3fb0[], D_1a3698[];
struct Pt6 {
  void *p; int *cnt;
  Pt6(void *o) { p = o; cnt = 0; if (o) { cnt = (int *)f_04dfa0(4); *cnt = 1; } }
  ~Pt6() { f_04ed28(this); }
};
static inline void tree6(void *o, int base) {
  int *n = (int *)f_04dfa0(40);
  Q6(o, base + 4) = (int)n; n[1] = 0;
}
struct ObA6 {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObA6(void *a, void *b, int n) {
    Em6 e;
    Q6(this, 0) = (int)D_1a3760; Q6(this, 4) = 0; Q6(this, 12) = 0;
    int *nd = (int *)f_04dfa0(40);
    Q6(this, 12) = (int)nd; nd[1] = 0;
    Q6(this, 0) = (int)D_1a3fb0;
    nd[2] = (int)nd; Q6(this, 16) = 0; nd[3] = (int)nd;
    Q6(this, 28) = (int)b; nd[0] = 0; Q6(this, 24) = (int)a;
    Q6(this, 36) = 0; Q6(this, 40) = 0; Q6(this, 44) = 0;
    f_05b780((char *)this + 32, n);
  }
  ObA6(ObA6 *src) {
    Em6 e;
    Q6(this, 0) = (int)D_1a3760; Q6(this, 4) = 0; Q6(this, 12) = 0;
    int *nd = (int *)f_04dfa0(40);
    Q6(this, 12) = (int)nd; nd[1] = 0;
    Q6(this, 0) = (int)D_1a3fb0;
    Q6(this, 16) = 0; nd[2] = (int)nd;
    Q6(this, 36) = 0; Q6(this, 40) = 0;
    nd[3] = (int)nd; Q6(this, 24) = Q6(src, 24); Q6(this, 28) = Q6(src, 28); nd[0] = 0;
    Q6(this, 44) = 0;
    if (Q6(src, 36) != Q6(src, 40)) f_05b858((char *)this + 32, (char *)src + 32);
  }
};
struct ObB6 {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObB6() {
    Em6 e;
    Q6(this, 0) = (int)D_1a3760; Q6(this, 4) = 0; Q6(this, 12) = 0;
    int *nd = (int *)f_04dfa0(40);
    Q6(this, 12) = (int)nd; nd[1] = 0;
    Q6(this, 0) = (int)D_1a3698;
    nd[2] = (int)nd; Q6(this, 16) = 0; nd[3] = (int)nd; nd[0] = 0;
    int tag[16]; int junk;
    f_04ea4c((char *)this + 24, &junk, tag);
  }
};
/* @draft 0x056390 us f_056390
   WHAT IT DOES: builds three small ref-counted tree objects: object A (52 bytes, owner and extra key, an n-entry vector of unaligned little-endian words read from the byte buffer), object B (60 bytes, an empty second tree) whose virtual slot 42 is called with the player, and object C (a copy of A); registers B at +136 through B's virtual slot 14 and B again at +120 through A's slot 14, then either (id == -1) hands A to f_05e394 with the +328 sub-object, or sends the record {player, id} and A to virtual slot 14 of the object two links down the player's chain at +344.
   Remaining difference: not scored beyond the draft; the vector push_back is open-coded and landing pads, temporaries and register allocation are not matched. */
void f_056390(char *self, void *x, int id, int n, const unsigned char *bytes) {
  ObA6 *A = new ObA6(self, x, n);
  int *v = (int *)((char *)A + 32);
  int val;
  for (int i = 0; i < n; i++) {
    val = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
    int *end = (int *)v[2];
    if (end == (int *)v[3]) f_06053c(v, end, &val);
    else { if (end) *end = val; v[2] = (int)(end + 1); }
    bytes += 4;
  }
  ObB6 *B = new ObB6;
  ((void (*)(void *, void *))(*(void ***)B)[42])(B, self);
  ObA6 *C = new ObA6(A);
  {
    Pt6 pc(C);
    ((void (*)(void *, void *, void *))(*(void ***)B)[14])(B, self + 136, &pc);
  }
  {
    Pt6 pb(B);
    ((void (*)(void *, void *, void *))(*(void ***)A)[14])(A, self + 120, &pb);
  }
  if (id == -1) {
    char *q = self + 328;
    Pt6 pa(A);
    int out[8]; int a = Q6(q, 4);
    f_05e394(out + 6, q, &a, &pa);
  } else {
    int *t = (int *)Q6(self, 344);
    int *v1 = (int *)t[1];
    int rec[4];
    rec[0] = (int)self; rec[1] = id; rec[2] = 0; rec[3] = 0;
    void *o = (void *)v1[2];
    Pt6 pa(A);
    ((void (*)(void *, void *, void *))(*(void ***)o)[14])(o, rec, &pa);
  }
}


int f_05df80(void *, void *); extern const char *D_1d2d7c[20]; extern char D_1a4110[];
struct Ob12 {
  void *vt; int x;
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  Ob12() { Em6 e; vt = D_1a4110; x = 0; }
};
static inline int vcall0(void *o, int slot) { return ((int (*)(void *))(*(void ***)o)[slot])(o); }
/* @draft 0x053534 us f_053534
   WHAT IT DOES: takes two copies of the counted handle two links down the chain at +328; when the second handle's object is of kind 7 and the record it returns (virtual slot 20) is accepted by f_05df80 against the player's key at +24, replaces the second handle with the one two links down the +344 chain; then asks the second object (virtual slot 13) for a handle from a record, which is either the first object's record (virtual slot 20) or, when the second is kind 10, the first is not kind 7 and its slot-23 index is below 20, a record built from the name D_1d2d7c[index] (looked up with f_15c07c, or inserted in the string map at +8); the resulting handle, or a new 12-byte object when it is null, is passed to f_05e394 with the +328 sub-object.
   Remaining difference: not scored beyond the draft; landing pads, temporaries and register allocation are not matched. */
void f_053534(char *self) {
  char *q = self + 328;
  Hd6 h0, h1; int o0[4];
  grab6(h0, q, o0); grab6(h1, q, o0);
  if (vcall0(h1.p, 6) == 7) {
    Rc4 r = ((Rc4 (*)(void *, void *))(*(void ***)h1.p)[20])(h1.p, self);
    if (f_05df80(&r, self + 24)) {
      int *t = (int *)Q6(self, 344);
      int *s3 = (int *)t[1];
      if ((char *)&h1 != (char *)(s3 + 2)) {
        f_04ed28(&h1);
        h1.p = (int *)s3[2]; h1.c = (int *)s3[3];
        if (h1.c) ++*h1.c;
      }
    }
  }
  void *s3 = h1.p;
  int rec[4];
  int idx;
  if (vcall0(s3, 6) == 10 && vcall0(h0.p, 6) != 7 && (unsigned)(idx = vcall0(h0.p, 23)) < 20) {
    const char *name = D_1d2d7c[idx];
    int r = f_15c07c(Q6(self, 4), 7, (void *)name);
    rec[0] = (int)self; rec[1] = r; rec[2] = 0; rec[3] = 0;
    if (r == -1) {
      Str6 st; char tag[16]; char *res[2];
      f_05a3e8(&st, (void *)name, tag);
      f_05e540(res, self + 8, &st);
      rec[2] = (int)(self + 8); rec[3] = (int)(res[0] + 16);
    }
  } else {
    *(Rc4 *)rec = ((Rc4 (*)(void *, void *))(*(void ***)h0.p)[20])(h0.p, self);
  }
  Hd6 res = ((Hd6 (*)(void *, void *))(*(void ***)s3)[13])(s3, rec);
  Hd6 pr;
  if (res.p) {
    pr.p = res.p; pr.c = res.c;
    if (pr.c) ++*pr.c;
  } else {
    Ob12 *o = new Ob12;
    pr.p = (int *)o; pr.c = 0;
    if (o) { pr.c = (int *)f_04dfa0(4); *pr.c = 1; }
  }
  int out[4]; int a = Q6(q, 4);
  f_05e394(out, q, &a, &pr);
}


/* out = o->slot13(*r), with the self-assignment guard of the handle's operator= */
static inline void asg6(Hd6 &out, void *o, Rc4 *r) {
  Hd6 t = ((Hd6 (*)(void *, void *))(*(void ***)o)[13])(o, r);
  if (&out != &t) {
    f_04ed28(&out);
    out.p = t.p; out.c = t.c;
    if (out.c) ++*out.c;
  }
}
/* @draft 0x0530a8 us f_0530a8
   WHAT IT DOES: takes two copies of the counted handle two links down the chain at +328 and asks the second one's object (virtual slot 20) for a record of the player; then offers the record to a series of candidate objects (the ones at +272, +288, each node of the list at +340, then +264) through virtual slot 13 until one returns a non-null handle, and gives that candidate (or, when none does, the object of the list's last node) a copy of the first handle together with the record through virtual slot 14.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation are not matched. */
void f_0530a8(char *self) {
  char *q = self + 328;
  Hd6 h0, h1; int o0[4];
  grab6(h0, q, o0); grab6(h1, q, o0);
  Rc4 r80 = ((Rc4 (*)(void *, void *))(*(void ***)h1.p)[20])(h1.p, self);
  Hd6 out; out.p = 0; out.c = 0;
  void *tgt = (void *)Q6(self, 272);
  asg6(out, tgt, &r80);
  if (!out.p) {
    tgt = (void *)Q6(self, 288);
    asg6(out, tgt, &r80);
    if (!out.p) {
      int *lst = (int *)(self + 340);
      int *head = (int *)lst[1];
      int *n = (int *)head[0];
      tgt = 0;
      while (n != head) {
        asg6(out, (void *)n[2], &r80);
        if (out.p) { tgt = (void *)n[2]; break; }
        n = (int *)n[0];
      }
      if (!tgt) {
        tgt = (void *)Q6(self, 264);
        asg6(out, tgt, &r80);
        if (!out.p) tgt = (void *)((int *)((int *)lst[1])[1])[2];
      }
    }
  }
  Hd6 c; c.p = h0.p; c.c = h0.c;
  if (c.c) ++*c.c;
  ((void (*)(void *, void *, void *))(*(void ***)tgt)[14])(tgt, &r80, &c);
}

}
}
#undef Q6

/* ---- swg6d ---- */
#undef W
#undef B
#undef FLD
#undef DBL
namespace swg6d { extern "C" {
void *f_05db08(int);
void f_05daa4(void *, void *);
void f_05e394(void *, void *, void *, void *);
void f_04ed28(void *);
extern char D_1a4480[];
struct Holder { int a, b; ~Holder() { f_04ed28(this); } };
struct Itr { char *p; Itr(char*q){p=q;} Itr(const Itr&o){p=o.p;} };
struct It { char *p; It(char*q){p=q;} It(const It&o){p=o.p;} };
/* @draft 0x062e80 us f_062e80
   WHAT IT DOES: allocates an 8-byte object holding the D_1a4480 vtable and a zero, wraps it in a Holder, inserts the keyed entry into the tree with f_05e394, then walks the element array at +28..+32 of the first argument (8-byte entries) inserting each into the tree.
   Remaining difference: stack layout of the insert temporaries and the iterator slot; two landing pads missing */
void f_062e80(char *s0, char *s) {
    int *p = (int *)f_05db08(8);
    p[0] = (int)D_1a4480;
    p[1] = 0;
    Holder h;
    f_05daa4(&h, p);
    int out[4];
    int v = *(int *)(s + 4);
    f_05e394(out, s, &v, &h);
    Itr it(*(char **)(s0 + 28));
    char *end = *(char **)(s0 + 32);
    while (it.p != end) {
        int out2[4];
        int v2 = *(int *)(s + 4);
        f_05e394(out2, s, &v2, it.p);
        it.p += 8;
    }
}
extern char D_1a4320[];
struct Vec8 { int a, b, c; int size() { return (c - b) >> 3; } };
/* @draft 0x062d5c us f_062d5c
   WHAT IT DOES: builds the same 8-byte keyed entry as f_062e80 and inserts it, then for each index of the 8-byte-element vector at +24 allocates a 12-byte object (vtable D_1a4320, zero, index), wraps it in a Holder and inserts it into the tree with f_05e394.
   Remaining difference: register allocation (object and key pointers swapped between s0/s1) and landing-pad placement */
void f_062d5c(char *s0, char *s) {
    int *p = (int *)f_05db08(8);
    p[0] = (int)D_1a4480;
    p[1] = 0;
    {
    Holder h;
    f_05daa4(&h, p);
    int out[4];
    int v = *(int *)(s + 4);
    f_05e394(out, s, &v, &h);
    }
    Vec8 *vec = (Vec8 *)(s0 + 24);
    unsigned i = 0;
    for (;;) {
        if (!(i < (unsigned)vec->size())) break;
        int *q = (int *)f_05db08(12);
        q[0] = (int)D_1a4320;
        q[1] = 0;
        Holder h;
        f_05daa4(&h, q);
        q[2] = i;
        int v2 = *(int *)(s + 4);
        int out2[4];
        f_05e394(out2, s, &v2, &h);
        i++;
    }
}

struct Itn { char *p; Itn() {} Itn(const Itn &o) { p = o.p; } };
struct Key { void **a; int b; };
struct Obj { void **vt; int x, y; };
struct KObj { void **vt; };
struct Er { char *p; Er() {} Er(const Er &o) { p = o.p; } };
Er f_05c790(char *self, Itn it);
class VK { public: virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(void *); };
class VE { public: virtual void d0(); };
/* @draft 0x061458 us f_061458
   WHAT IT DOES: walks the circular list whose header is at self+4; for each node whose element's field at +4 equals the key's second word, calls the element's virtual slot 0, the key object's virtual slot 3 with the element, then erases the node with f_05c790 (list remove-by-owner loop).
   Remaining difference: register choice and scheduling in the first iteration (a1/a2, one load order), an extra nop vs move in the virtual-call slot */
void f_061458(char *self, Key *kp) {
    Key key = *kp;
    Key *kk = &key;
    char *hdr = *(char **)(self + 4);
    Itn it; it.p = *(char **)hdr;
    Itn end; end.p = hdr;
    while (it.p != end.p) {
        Itn nx(it);
        nx.p = *(char **)it.p;
        char *e = *(char **)(it.p + 8);
        if (*(int *)(e + 4) == kk->b) {
            (*(VE **)e)->d0();
            ((VK *)kk->a)->m3(e);
            f_05c790(self, it);
        }
        it = nx;
    }
}

struct R4 { int w0, w1, w2, w3; };
struct Pr { char *p; bool f; Pr() {} Pr(const Pr &o) { p = o.p; f = o.f; } };
struct P2 { int a, b; P2() {} P2(const P2 &o) { a = o.a; b = o.b; } };
extern unsigned char D_1a4d14;
int f_15c07c(int, int, char *);
void f_05e540(Pr *, void *, void *);
/* @draft 0x06435c us f_06435c
   WHAT IT DOES: returns a 16-byte result by hidden pointer: if the flag byte at +8 is clear it copies the 16 bytes at +12 out; otherwise it terminates the string at +28 with the D_1a4d14 byte, stores the f_15c07c(x[1], 7, str) status, and on -1 looks up the position with f_05e540 and fills the result's last two words.
   Remaining difference: stack layout of the temporaries (retail keeps pair at sp+0, copies at 16/48) and register allocation; retail path structure partly differs */
R4 f_06435c(char *o, char *x) {
    R4 r;
    if (*(unsigned char *)(o + 8) == 0) {
        r.w0 = *(int *)(o + 12); r.w1 = *(int *)(o + 16);
        r.w2 = *(int *)(o + 20); r.w3 = *(int *)(o + 24);
        return r;
    }
    r.w0 = (int)x;
    r.w2 = 0;
    r.w3 = 0;
    char *d = *(char **)(o + 28);
    d[*(int *)(d - 12)] = D_1a4d14;
    r.w1 = f_15c07c(*(int *)(x + 4), 7, *(char **)(o + 28));
    if (r.w1 == -1) {
        Pr q;
        volatile P2 tp;
        tp.a = r.w0 + 8;
        f_05e540(&q, (void *)tp.a, o + 28);
        Pr c1(q);
        Pr c2(c1);
        tp.b = (int)(q.p + 16);
        r.w3 = tp.b;
        r.w2 = tp.a;
    }
    return r;
}

extern unsigned char D_1a4d14;
extern char D_1a43d0[];
int f_15c098(int, int);
void f_05a3e8(void *, int, void *);
void f_05e4a8(void *, void *);
int f_06264c(void *);
void f_05db84(void *);
void f_04e8c0(void *);
void f_05daa4(void *, void *);
void f_05df24(void *, void *);
void f_04ed28(void *);
struct StrT { int w; ~StrT() { f_05db84(this); } };
struct Sx {
    char *vt; int w4; unsigned char b8; int w12, w16, w20, w24; int s28;
    ~Sx() { vt = D_1a43d0; f_05db84(&s28); f_04e8c0(this); }
};
/* @draft 0x062bd4 us f_062bd4
   WHAT IT DOES: builds a source string pointer (via f_15c098 when the key at +4 is not -1, else by terminating the string held through the pointer at +12), wraps it in a COW string with f_05a3e8, builds a local stream-like object (vtable D_1a43d0, byte flag 1, field -1, string copy via f_05e4a8), gets an index from f_06264c, destroys the object, then stores a default Holder into slot idx (8-byte stride) of the array at self+28 with f_05df24.
   Remaining difference: stack slot layout of the locals, landing-pad blocks and the register for the source pointer; 74 of 98 words differ */
void f_062bd4(char *self, int *a) {
    StrT tmp;
    int g[4];
    int src;
    if (a[1] != -1) {
        src = f_15c098(*(int *)(a[0] + 4), 7);
    } else {
        int *x = (int *)a[3];
        char *d = *(char **)x;
        d[*(int *)(d - 12)] = D_1a4d14;
        src = *x;
    }
    f_05a3e8(&tmp, src, g);
    int idx;
    {
    Sx o;
    o.vt = D_1a43d0;
    o.b8 = 1;
    o.w16 = -1;
    o.w4 = 0; o.w12 = 0; o.w20 = 0; o.w24 = 0;
    f_05e4a8(&o.s28, &tmp);
    idx = f_06264c(&o);
    }
    char *ptr = *(char **)(self + 28) + idx * 8;
    Holder h;
    f_05daa4(&h, 0);
    f_05df24(ptr, &h);
}

struct KEnt { const char *name; int a, b, c; };
extern char D_291688[];
extern KEnt D_291694[11];
extern char D_1a34c0[]; /* "DOWN" */
extern char D_1a34c8[]; /* "UP" */
extern char D_1a34cc[]; /* "RIGHT" */
extern char D_1a34d4[]; /* "LEFT" */
extern char D_1a34dc[]; /* "SPACE" */
extern char D_1a34e4[]; /* "BACKSPACE" */
extern char D_1a34f0[]; /* "getCode" */
extern char D_1a34f8[]; /* "isDown" */
extern char D_1a3500[]; /* "addListener" */
extern char D_1a350c[]; /* "removeListener" */
static inline void ini(KEnt *e, int a, int b, int c) { e->a = a; e->c = c; e->b = b; }
/* @draft 0x0665bc us f_0665bc
   WHAT IT DOES: on first call fills the static 11-entry key-name table at D_291694 (name pointer plus three ints per 16-byte entry, names DOWN/UP/RIGHT/LEFT/SPACE/BACKSPACE/getCode/isDown/addListener/removeListener, codes 0 to 9, null terminator entry), sets the init flag, and returns the table.
   Remaining difference: instruction scheduling and constant register sharing (retail keeps 1 and 2 in a2/a3 from function entry) */
KEnt *f_0665bc(void) {
    if (!D_291688[0]) {
        KEnt *t = D_291694;
        ini(&t[0], 0, 0, 0);
        ini(&t[1], 0, 0, 1);
        ini(&t[2], 0, 0, 2);
        ini(&t[3], 0, 0, 3);
        ini(&t[4], 0, 0, 4);
        ini(&t[5], 0, 0, 5);
        ini(&t[6], 2, 0, 6);
        ini(&t[7], 2, 1, 7);
        ini(&t[8], 2, 1, 8);
        ini(&t[9], 2, 1, 9);
        ini(&t[10], 1, 0, 0);
        t[0].name = D_1a34c8;
        t[1].name = D_1a34c0;
        t[2].name = D_1a34cc;
        t[3].name = D_1a34d4;
        t[4].name = D_1a34dc;
        t[5].name = D_1a34e4;
        t[6].name = D_1a34f0;
        t[7].name = D_1a34f8;
        t[8].name = D_1a3500;
        t[9].name = D_1a350c;
        t[10].name = 0;
        D_291688[0] = 1;
    }
    return D_291694;
}
}}

/* ---- swg7c ---- */
#undef W
#undef B
#undef FLD
#undef DBL
namespace swg7c {
extern "C" {
void *f_04dfa0(int);
void f_04ed28(void *);
void f_04e4b4(void *);
void f_05daa4(void *, void *);
void f_05db84(void *);
void f_05e4a8(void *, void *);
void f_05dff0(void *, void *, void *);
void f_064e98(void *, void *, void *);
void f_064f10(void *, void *, void *);
void f_05cbd4(void *);
void f_064c6c(void *);
void f_05f64c(void *, void *, void *);
void f_05e394(void *, void *, void *, void *);
void f_04e8c0(void *);
extern char D_1a3760[];
struct RbN { int color; RbN *parent, *left, *right; };
void f_064cfc(RbN *, RbN **);
void f_064d44(RbN *, RbN **);
void f_04eda0(void *);
void f_04ee08(void *, void *);
void f_04ec74(void *, void *);
extern char D_1a4530[], D_1a4678[];
void f_061da4(void *, void *, void *, int);
void f_061e30(void *, void *, void *, int);
void f_04e65c2(void *, void *, int) __asm__("f_04e65c");
void f_061c38(void *, void *, void *, int);
void f_1312d4(const char *);
extern char D_1a3074[]; /* "vector::reserve" */
void f_0654a0(void *, void *, void *, void *, void *);
void f_061910(void *, void *, void *);
void f_065348(void *, void *, void *, void *, void *);
void f_0617f4(void *, void *, void *);
void f_05f1f4(void *, void *, void *);
bool f_160a30(void *, int);
void f_05c790(void *, void *, void *);
void f_05a3e8(void *, void *, void *);
void f_05e540(void *, void *, void *);
int f_15c07c(void *, int);
struct It4 { int p; It4() {} It4(const It4 &o) { p = o.p; } };
struct RefH { int p, rc; RefH() {} RefH(void *x) { f_05daa4(this, x); } RefH(const RefH &o) { p = o.p; rc = o.rc; if (rc) ++*(int *)rc; } ~RefH() { f_04ed28(this); } };
struct Val24 { int a, b, c, d; RefH r; Val24() : r((void *)0) {} };
struct KV28 { int key; Val24 v; };
struct KV28;
It4 *f_05f238(It4 *, char *, It4 *, unsigned *);
struct KV28;
It4 *f_05f238(It4 *, char *, It4 *, unsigned *);
struct Pair4 { It4 a, b; };
/* @draft 0x05e2c4 us f_05e2c4
   WHAT IT DOES: erases every entry of the tree that matches a key: finds the equal range of the key (f_05dff0 / f_064e98), counts the entries in it by stepping an iterator (f_05cbd4) until it reaches the end of the range, then erases the range (f_064f10) and returns the count.
   Remaining difference: not compared. */
int f_05e2c4(char *self, void *key) {
    It4 a, b;
    f_05dff0(&a, self, key);
    f_064e98(&b, self, key);
    Pair4 pr;
    pr.a = a;
    pr.b = b;
    b = pr.a;
    a = pr.b;
    It4 cur = a, last = b;
    int n = 0;
    while (cur.p != last.p) { f_05cbd4(&cur); n++; }
    last = pr.a;
    cur = pr.b;
    f_064f10(self, &last, &cur);
    return n;
}

struct Tmp { char *p; ~Tmp() { f_05db84(this); } };
struct G2 { int w[4]; ~G2() {} };
struct Rs { int a; char b; Rs() {} Rs(const Rs &o) { a = o.a; b = o.b; } };
struct E8 { int a, b; E8() {} E8(const E8 &o) { a = o.a; b = o.b; } };
/* @draft 0x05e6cc us f_05e6cc
   WHAT IT DOES: initialises a tree-map iterator/handle: stores the owning object, looks the name up with f_15c07c (id 7) and stores the id; when the id is -1 it builds a temporary string from the name (f_05a3e8), inserts it into the owner's tree at +8 (f_05e540) and stores the tree and the new entry address (+16) in the handle. The temporary string is destroyed with f_05db84.
   Remaining difference: not compared. */
void f_05e6cc(int *self, char *owner, void *name) {
    self[0] = (int)owner;
    self[2] = 0;
    self[3] = 0;
    int v = f_15c07c(*(void **)(owner + 4), 7);
    self[1] = v;
    if (v == -1) {
        char *m = *(char **)self + 8;
        G2 g;
        Tmp t;
        f_05a3e8(&t, name, &g);
        Rs r;
        f_05e540(&r, m, &t);
        E8 e;
        e.a = (int)m;
        e.b = r.a + 16;
        *(E8 *)(self + 2) = e;
        Rs r2(r);
        Rs r3(r);
    }
}

extern char D_1a3760[], D_1a41c0[];
/* @draft 0x05f374 us f_05f374
   WHAT IT DOES: constructs a movie-clip style object: base part (vtable D_1a3760, an empty tree at +8 with an allocated 40-byte header node linked to itself), then the derived vtable D_1a41c0, a pointer at +24, a flag byte at +28, an empty four-word vector at +32 and a second empty tree at +48 with a 24-byte header node linked to itself.
   Remaining difference: the three landing pads (base destroy f_04e8c0, vector buffer free f_04e4b4, map destroy f_04e8d8) are not reproduced. */
void f_05f374(char *s0, char *a1, int flag) {
    *(char **)s0 = D_1a3760;
    *(int *)(s0 + 4) = 0;
    *(int *)(s0 + 12) = 0;
    int *n = (int *)f_04dfa0(40);
    *(int **)(s0 + 12) = n;
    n[1] = 0;
    *(char **)s0 = D_1a41c0;
    int *h = *(int **)(s0 + 12);
    h[2] = (int)h;
    int *h2 = *(int **)(s0 + 12);
    *(char **)(s0 + 24) = a1;
    h2[3] = (int)h2;
    *(char *)(s0 + 28) = (char)flag;
    *(int *)(s0 + 16) = 0;
    n[0] = 0;
    *(int *)(s0 + 36) = 0;
    *(int *)(s0 + 40) = 0;
    *(int *)(s0 + 44) = 0;
    *(int *)(s0 + 52) = 0;
    int *m = (int *)f_04dfa0(24);
    *(int **)(s0 + 52) = m;
    m[1] = 0;
    int *m1 = *(int **)(s0 + 52);
    *(int *)(s0 + 56) = 0;
    m1[2] = (int)m1;
    int *m2 = *(int **)(s0 + 52);
    m[0] = 0;
    m2[3] = (int)m2;
}

/* @draft 0x05c698 us f_05c698
   WHAT IT DOES: walks the list at +4 of the object; for each node it tests the node's value against the first word of the range argument (f_160a30); on a match it calls the value's virtual +0 and then virtual +12 of the second word with the value, and erases that node (f_05c790). Steps to the next link saved before the erase.
   Remaining difference: not compared. */
void f_05c698(char *self, int *rng) {
    int r[2];
    r[1] = rng[1];
    r[0] = rng[0];
    int *hdr = *(int **)(self + 4);
    It4 it, nx, end;
    it.p = *hdr;
    end.p = (int)hdr;
    while (it.p != end.p) {
        nx.p = it.p;
        char *v = *(char **)(it.p + 8);
        nx.p = *(int *)it.p;
        bool hit = f_160a30(v, r[0]);
        if (hit) {
            (*(void (**)(void *))*(void **)v)(v);
            void *o = (void *)r[1];
            (*(void (**)(void *, void *))((char *)*(void **)o + 12))(o, v);
        }
        if (hit) {
            It4 out, a;
            a.p = it.p;
            f_05c790(&out, self, &a);
        }
        it = nx;
    }
}

/* @draft 0x05f0b8 us f_05f0b8
   WHAT IT DOES: map subscript: finds the entry for the key (f_05f1f4); when it is the end or its key is greater than the requested one, builds a default value (zero fields, -1, an empty counted reference) and inserts the key/value pair at that position with f_05f238; returns the address of the value (+20) of the found or inserted node.
   Remaining difference: not compared. */
char *f_05f0b8(char *self, unsigned *key) {
    It4 pos;
    f_05f1f4(&pos, self, key);
    int end = *(int *)(self + 4);
    if (pos.p != end && !(*key < *(unsigned *)(pos.p + 16))) return (char *)pos.p + 20;
    Val24 v;
    v.a = 0;
    v.b = -1;
    v.c = 0;
    v.d = 0;
    KV28 kv;
    kv.key = *key;
    kv.v = v;
    It4 h;
    h.p = pos.p;
    It4 res;
    f_05f238(&res, self, &h, (unsigned *)&kv);
    pos = res;
    return (char *)pos.p + 20;
}

/* @draft 0x05f238 us f_05f238
   WHAT IT DOES: red-black tree unique insert with a position hint. At the leftmost position it inserts there when the tree is non-empty and the key is smaller; at the end position it inserts after the rightmost when that key is smaller; otherwise it steps the hint back one (f_064c6c) and inserts between neighbours when the key fits, choosing the left or right slot by the predecessor's right child. In every other case it falls back to the plain unique insert (f_0617f4). Result is written through the first argument.
   Remaining difference: not compared. */
It4 *f_05f238(It4 *out, char *self, It4 *pos, unsigned *v) {
    char *hdr = *(char **)(self + 4);
    char *p = (char *)pos->p;
    if (p == *(char **)(hdr + 8)) {
        if (*(int *)(self + 8) != 0 && *v < *(unsigned *)(p + 16)) {
            f_065348(out, self, p, p, v);
            return out;
        }
    } else if (p == hdr) {
        char *rm = *(char **)(p + 12);
        if (*(unsigned *)(rm + 16) < *v) {
            f_065348(out, self, 0, rm, v);
            return out;
        }
    } else {
        It4 before;
        before.p = (int)p;
        f_064c6c(&before);
        char *b = (char *)before.p;
        if (*(unsigned *)(b + 16) < *v && *v < *(unsigned *)(p + 16)) {
            if (*(int *)(b + 12) == 0) f_065348(out, self, 0, b, v);
            else f_065348(out, self, p, p, v);
            return out;
        }
    }
    It4 r;
    f_0617f4(&r, self, v);
    out->p = r.p;
    return out;
}

/* @draft 0x05f998 us f_05f998
   WHAT IT DOES: red-black tree unique insert with a position hint. At the leftmost position it inserts there when the tree is non-empty and the key is smaller; at the end position it inserts after the rightmost when that key is smaller; otherwise it steps the hint back one (f_064c6c) and inserts between neighbours when the key fits, choosing the left or right slot by the predecessor's right child. In every other case it falls back to the plain unique insert (f_061910). Result is written through the first argument.
   Remaining difference: not compared. */
It4 *f_05f998(It4 *out, char *self, It4 *pos, unsigned *v) {
    char *hdr = *(char **)(self + 4);
    char *p = (char *)pos->p;
    if (p == *(char **)(hdr + 8)) {
        if (*(int *)(self + 8) != 0 && *v < *(unsigned *)(p + 16)) {
            f_0654a0(out, self, p, p, v);
            return out;
        }
    } else if (p == hdr) {
        char *rm = *(char **)(p + 12);
        if (*(unsigned *)(rm + 16) < *v) {
            f_0654a0(out, self, 0, rm, v);
            return out;
        }
    } else {
        It4 before;
        before.p = (int)p;
        f_064c6c(&before);
        char *b = (char *)before.p;
        if (*(unsigned *)(b + 16) < *v && *v < *(unsigned *)(p + 16)) {
            if (*(int *)(b + 12) == 0) f_0654a0(out, self, 0, b, v);
            else f_0654a0(out, self, p, p, v);
            return out;
        }
    }
    It4 r;
    f_061910(&r, self, v);
    out->p = r.p;
    return out;
}

static inline void destroy_r(char *f, char *l) { for (;;) { if (f == l) break; f_04ed28(f); f += 8; } }
/* @draft 0x05be04 us f_05be04
   WHAT IT DOES: vector reserve for a vector of 8-byte counted references (start +4, finish +8, end of storage +12): throws length_error "vector::reserve" above 0x1fffffff elements; if the capacity is smaller, allocates n*8 bytes, copies the elements over (f_061c38, freeing the new block and rethrowing on an exception), destroys the old elements (f_04ed28), frees the old block (f_04e4b4) and installs the new start/finish/end.
   Remaining difference: not compared. */
void f_05be04(int *v, unsigned n) {
    if (n > 0x1fffffff) f_1312d4(D_1a3074);
    if ((v[3] - v[1]) >> 3 < n) {
        char *s2 = (char *)v[1];
        char *s0 = (char *)v[2];
        int cnt = (s0 - s2) >> 3;
        char *tmp = (char *)f_04dfa0(n * 8);
        try {
            f_061c38(s2, s0, tmp, 0);
        } catch (...) {
            if (tmp) f_04e4b4(tmp);
            throw;
        }
        destroy_r((char *)v[1], (char *)v[2]);
        if (v[1]) f_04e4b4((void *)v[1]);
        v[3] = (int)(tmp + n * 8);
        v[2] = (int)(tmp + cnt * 8);
        v[1] = (int)tmp;
    }
}

struct E44 { char b[44]; };
static inline void destroy_44(E44 *f, E44 *l) {
    for (;;) {
        if (f == l) break;
        (*(void (**)(void *))*(void **)f)(f);
        f++;
    }
}
/* @draft 0x05bfe4 us f_05bfe4
   WHAT IT DOES: vector reserve for a vector of 44-byte polymorphic elements (start +4, finish +8, end of storage +12): throws length_error "vector::reserve" above 0x5d1745d elements; if the capacity is smaller, allocates n*44 bytes, copies the elements over (f_061da4, freeing the new block and rethrowing on an exception), calls each old element's virtual +0, frees the old block (f_04e4b4) and installs the new start/finish/end.
   Remaining difference: not compared. */
void f_05bfe4(int *v, unsigned n) {
    if (n > 0x5d1745d) f_1312d4(D_1a3074);
    if ((E44 *)v[3] - (E44 *)v[1] < (int)n) {
        E44 *s1 = (E44 *)v[1];
        E44 *s0 = (E44 *)v[2];
        int cnt = s0 - s1;
        E44 *tmp = (E44 *)f_04dfa0(n * 44);
        try {
            f_061da4(s1, s0, tmp, 0);
        } catch (...) {
            if (tmp) f_04e4b4(tmp);
            throw;
        }
        destroy_44((E44 *)v[1], (E44 *)v[2]);
        if (v[1]) f_04e4b4((void *)v[1]);
        v[1] = (int)tmp;
        v[3] = (int)(tmp + n);
        v[2] = (int)(tmp + cnt);
    }
}

struct E56 { char b[56]; };
/* @draft 0x05c154 us f_05c154
   WHAT IT DOES: vector reserve for a vector of 56-byte elements (start +4, finish +8, end of storage +12): throws length_error "vector::reserve" above the maximum element count; if the capacity is smaller, allocates n*56 bytes, copies the elements over (f_061e30, freeing the new block and rethrowing on an exception), destroys the old range (f_04e65c), frees the old block (f_04e4b4) and installs the new start/finish/end.
   Remaining difference: not compared. */
void f_05c154(int *v, unsigned n) {
    if (n > 0x4924924) f_1312d4(D_1a3074);
    if ((E56 *)v[3] - (E56 *)v[1] < (int)n) {
        E56 *s1 = (E56 *)v[1];
        E56 *s0 = (E56 *)v[2];
        int cnt = s0 - s1;
        E56 *tmp = (E56 *)f_04dfa0(n * 56);
        try {
            f_061e30(s1, s0, tmp, 0);
        } catch (...) {
            if (tmp) f_04e4b4(tmp);
            throw;
        }
        f_04e65c2((void *)v[1], (void *)v[2], 0);
        if (v[1]) f_04e4b4((void *)v[1]);
        v[3] = (int)(tmp + n);
        v[2] = (int)(tmp + cnt);
        v[1] = (int)tmp;
    }
}

struct HRef { char *p; int *rc; ~HRef() { f_04ed28(this); } };
struct HTag { char *p0; int b; int p2; char *p3; };
static inline void *vfn(void *p, int i) { return (*(void ***)p)[i]; }
static inline char *top_(char *t) { return *(char **)(*(char **)(t + 4) + 4); }
static inline void ref_load_(HRef *r, char *t) {
    char *n = top_(t);
    r->p = *(char **)(n + 8);
    r->rc = *(int **)(n + 12);
    if (r->rc) *r->rc += 1;
}
static inline void pop_(char *t) {
    char out[16];
    char *it = top_(t);
    f_05f64c(out, t, &it);
}
static inline void push_(char *t, HRef *h) {
    char out[16];
    int pos = *(int *)(t + 4);
    f_05e394(out, t, &pos, h);
}
static inline void init_map_(char *m) {
    *(int *)(m + 4) = 0;
    int *n = (int *)f_04dfa0(40);
    *(int **)(m + 4) = n;
    n[1] = 0;
    *(int *)(m + 8) = 0;
    n[2] = (int)n;
    n[0] = 0;
    n[3] = (int)n;
}

struct RefD { char *p; int *rc; ~RefD() { f_04ed28(this); } };
struct VecD3 { int a, b, c; ~VecD3() { f_04eda0(this); f_04e4b4((void *)b); } };
struct VecD2 { int a, b; ~VecD2() { f_04eda0(this); f_04e4b4((void *)b); } };
struct MapE { int a; int *hdr; int cnt;
    ~MapE() { if (cnt) f_04ee08(this, (void *)hdr[1]); cnt = 0; hdr[2] = (int)hdr; hdr[1] = 0; hdr[3] = (int)hdr; f_04e4b4(hdr); } };
struct MapE16 { int a; int *hdr; int cnt; int d;
    ~MapE16() { if (cnt) f_04ee08(this, (void *)hdr[1]); cnt = 0; hdr[2] = (int)hdr; hdr[1] = 0; hdr[3] = (int)hdr; f_04e4b4(hdr); } };
struct MapF { int a; int *hdr; int cnt;
    ~MapF() { if (cnt) f_04ec74(this, (void *)hdr[1]); cnt = 0; hdr[2] = (int)hdr; hdr[1] = 0; hdr[3] = (int)hdr; f_04e4b4(hdr); } };
struct CtxBase { char *vt; ~CtxBase() { vt = D_1a4678; } };
struct Ctx : CtxBase {
    int pad4;
    MapF m8;
    char pad20[244];
    RefD r264, r272, r280, r288;
    RefD ra[4];
    VecD3 v328;
    VecD2 v340;
    MapE16 m348;
    VecD2 v364;
    RefD r372, r380;
    ~Ctx() { vt = D_1a4530; }
};
/* @draft 0x05d368 us f_05d368
   WHAT IT DOES: destructor of the ActionScript context object: sets the derived vtable (D_1a4530), then destroys the members from the last to the first (two counted references at +380 and +372, the vector at +364, the tree at +348, the vectors at +340 and +328, the array of four references at +296, the references at +288..+264, and the tree at +8) and finally stores the base vtable D_1a4678. The landing pads destroy the not yet destroyed members when one destructor throws.
   Remaining difference: not compared. */
void f_05d368(Ctx *self) {
    self->~Ctx();
}

/* @draft 0x05d6dc us f_05d6dc
   WHAT IT DOES: second copy of the context object destructor (same member destruction sequence as f_05d368, at a different address).
   Remaining difference: not compared. */
void f_05d6dc(Ctx *self) {
    self->~Ctx();
}

/* @draft 0x05cc58 us f_05cc58
   WHAT IT DOES: red-black tree node removal with rebalancing (the standard rebalance-for-erase): unlinks node z, substituting its in-order successor when it has two children, then recolours and rotates (f_064cfc rotate left, f_064d44 rotate right) up from the replacement until the black-height is restored; the root, leftmost and rightmost slots are passed by address (leftmost and rightmost are updated when z was one of them). Returns z.
   Remaining difference: not compared. */
RbN *f_05cc58(RbN *z, RbN **root, RbN **lm, RbN **rm) {
    RbN *y = z;
    RbN *x;
    RbN *xp;
    if (y->left == 0) x = y->right;
    else if (y->right == 0) x = y->left;
    else {
        y = y->right;
        while (y->left != 0) y = y->left;
        x = y->right;
    }
    if (y != z) {
        z->left->parent = y;
        y->left = z->left;
        if (y != z->right) {
            xp = y->parent;
            if (x) x->parent = y->parent;
            y->parent->left = x;
            y->right = z->right;
            z->right->parent = y;
        } else xp = y;
        if (*root == z) *root = y;
        else if (z->parent->left == z) z->parent->left = y;
        else z->parent->right = y;
        y->parent = z->parent;
        int c = y->color;
        y->color = z->color;
        z->color = c;
        y = z;
    } else {
        xp = y->parent;
        if (x) x->parent = y->parent;
        if (*root == z) *root = x;
        else if (z->parent->left == z) z->parent->left = x;
        else z->parent->right = x;
        if (*lm == z) {
            if (z->right == 0) *lm = z->parent;
            else {
                RbN *t = x;
                while (t->left) t = t->left;
                *lm = t;
            }
        }
        if (*rm == z) {
            if (z->left == 0) *rm = z->parent;
            else {
                RbN *t = x;
                while (t->right) t = t->right;
                *rm = t;
            }
        }
    }
    if (y->color != 0) {
        while (x != *root && (x == 0 || x->color == 1)) {
            if (x == xp->left) {
                RbN *w = xp->right;
                if (w->color == 0) {
                    w->color = 1;
                    xp->color = 0;
                    f_064cfc(xp, root);
                    w = xp->right;
                }
                if ((w->left == 0 || w->left->color == 1) && (w->right == 0 || w->right->color == 1)) {
                    w->color = 0;
                    x = xp;
                    xp = xp->parent;
                } else {
                    if (w->right == 0 || w->right->color == 1) {
                        if (w->left) w->left->color = 1;
                        w->color = 0;
                        f_064d44(w, root);
                        w = xp->right;
                    }
                    w->color = xp->color;
                    xp->color = 1;
                    if (w->right) w->right->color = 1;
                    f_064cfc(xp, root);
                    break;
                }
            } else {
                RbN *w = xp->left;
                if (w->color == 0) {
                    w->color = 1;
                    xp->color = 0;
                    f_064d44(xp, root);
                    w = xp->left;
                }
                if ((w->right == 0 || w->right->color == 1) && (w->left == 0 || w->left->color == 1)) {
                    w->color = 0;
                    x = xp;
                    xp = xp->parent;
                } else {
                    if (w->left == 0 || w->left->color == 1) {
                        if (w->right) w->right->color = 1;
                        w->color = 0;
                        f_064cfc(w, root);
                        w = xp->left;
                    }
                    w->color = xp->color;
                    xp->color = 1;
                    if (w->left) w->left->color = 1;
                    f_064d44(xp, root);
                    break;
                }
            }
        }
        if (x) x->color = 1;
    }
    return y;
}

/* @draft 0x05cfe8 us f_05cfe8
   WHAT IT DOES: deleting destructor of the ActionScript context object: runs the same member destruction sequence as f_05d368 and then frees the allocation, which starts 4 bytes before the object (the size word written by the allocator), with f_04e4b4.
   Remaining difference: not compared. */
void f_05cfe8(Ctx *self) {
    self->~Ctx();
    f_04e4b4((char *)self - 4);
}

/* @draft 0x057c08 us f_057c08
   WHAT IT DOES: builds a new 28-byte dictionary object (base vtable D_1a3760 plus an empty tree) from the argument stack at +328: pops the count argument and asks it for a number n (virtual +92); then n times pops a value and a key, asks the key for its name tag (virtual +20) and stores the value under it with the object's virtual +56; finally wraps the object in a new counted reference and pushes it on the stack.
   Remaining difference: not compared; the stack-slot iterator temporaries of the pop/push helpers do not reproduce retail's 224-byte frame. */
void f_057c08(char *s3) {
    char *t = s3 + 328;
    HRef a;
    ref_load_(&a, t);
    pop_(t);
    int n = ((int (*)(void *))vfn(a.p, 23))(a.p);
    int *o = (int *)f_04dfa0(28);
    o[0] = 28;
    char *s4 = (char *)(o + 1);
    char *s1 = (char *)(o + 3);
    *(char **)s4 = D_1a3760;
    *(int *)(s4 + 4) = 0;
    init_map_(s1);
    for (int i = 0; i < n; i++) {
        HRef b;
        ref_load_(&b, t);
        pop_(t);
        HRef c;
        ref_load_(&c, t);
        pop_(t);
        HTag tag;
        ((void (*)(HTag *, void *, void *))vfn(c.p, 20))(&tag, c.p, s3);
        HRef cp;
        cp.p = b.p;
        cp.rc = b.rc;
        if (cp.rc) *cp.rc += 1;
        ((void (*)(void *, void *, HRef *))vfn(s4, 14))(s4, &tag, &cp);
    }
    HRef h;
    h.p = s4;
    h.rc = 0;
    if (s4) {
        int *cnt = (int *)f_04dfa0(4);
        *cnt = 1;
        h.rc = cnt;
    }
    push_(t, &h);
}

}  // extern "C"
}  // namespace swg7c

/* ---- swg7b ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg7b: large untagged functions of the SWG player (big_b, second half). */
namespace swg7b {
extern "C" {
#define Q7(o, off) (*(int *)((char *)(o) + (off)))
void *f_04dfa0(unsigned); void f_04ed28(void *); void f_04e4b4(void *); void f_04eee8(void *, void *);
void f_05daa4(void *, void *);
int f_15c0f0(int, int); int f_15c07c(int, int, void *);
void f_05a3e8(void *, void *, void *); void f_05e540(void *, void *, void *);
void f_05f64c(void *, void *, void *); int f_05df80(void *, void *);
unsigned sceKernelCpuSuspendIntr(void); void sceKernelCpuResumeIntr(unsigned);
extern int D_1d2d7c[];
struct Em7 { ~Em7() {} };
struct Rc7 { int w[4]; };
/* the virtual interface of the movie-clip / character objects (slot numbers are retail vtable slots) */
struct Str7 {
  char *p;
  ~Str7() {
    Em7 g; char *s0 = p; char *s2 = s0 - 12;
    unsigned intr = sceKernelCpuSuspendIntr();
    volatile int *c = (volatile int *)(s0 - 4);
    int s1 = *c; *c += -1;
    sceKernelCpuResumeIntr(intr);
    if (s1 <= 0) f_04eee8(s2, &g);
  }
};
struct Vo;
struct Hd7 { Vo *p; int *c; ~Hd7() { f_04ed28(this); } };
struct Vo {
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual int s6();
  virtual char *s7();
  virtual void s8();
  virtual int s9();
  virtual Vo *s10();
  virtual void *s11();
  virtual void s12(void *);
  virtual Hd7 s13(void *);
  virtual void s14(void *, void *);
  virtual void s15();
  virtual void s16(void *);
  virtual void s17();
  virtual void s18();
  virtual void s19();
  virtual Rc7 s20(void *);
  virtual Str7 s21();
  virtual int s22();
  virtual int s23();
  virtual double s24();
  virtual void s25();
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void s32();
  virtual void s33();
  virtual void s34();
  virtual void s35();
  virtual void s36();
  virtual void s37();
  virtual int s38(void *);
  virtual void s39();
  virtual void s40();
  virtual int *s41();
  virtual void s42(void *);
  virtual void s43();
  virtual void s44();
  virtual int s45(void *, void *, void *);
};
static inline void grab7(Hd7 &h, char *q, void *out) {
  int a = Q7(q, 4);
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  if (h.c) ++*h.c;
  int b = *(int *)(a + 4);
  f_05f64c(out, q, &b);
}

/* @draft 0x0539dc us f_0539dc
   WHAT IT DOES: takes three copies of the counted handle two links down the chain at +328; while the second-chain object is a type-7 node it asks it (virtual slot 20) for the registration record and, when f_05df80 accepts the record against +24, replaces the handle with the next one in the list at +344; then builds a record {player, id, tree, name} (virtual slot 20 of the matching handle, or for a type-10 object whose partner is not type 7 and whose index is below 20 the id from f_15c07c on the name in the table at D_1d2d7c, falling back to a name-map lookup) and passes it, with a copy of the first handle, to virtual slot 14 of the current object.
   Remaining difference: not scored; handle temporaries are open-coded copies, landing pads and register allocation unmatched. */
void f_0539dc(char *self) {
  char *q = self + 328;
  Hd7 h0, h1, h2; int o[4];
  grab7(h0, q, o); grab7(h1, q, o); grab7(h2, q, o);
  Rc7 rec;
  Vo *s0;
  if (h2.p->s6() == 7) goto seven;
again:
  s0 = h2.p;
  if (s0->s6() == 10) {
    if (h1.p->s6() != 7) {
      int x = h1.p->s23();
      if ((unsigned)x < 20) {
        int nm = D_1d2d7c[x];
        rec.w[0] = (int)self; rec.w[2] = 0; rec.w[3] = 0;
        rec.w[1] = f_15c07c(Q7(self, 4), 7, (void *)nm);
        if (rec.w[1] == -1) {
          Str7 s; char tag[16];
          f_05a3e8(&s, (void *)nm, tag);
          char *res[2];
          f_05e540(res, self + 8, &s);
          rec.w[2] = (int)(self + 8); rec.w[3] = (int)(res[0] + 16);
        }
        goto fin;
      }
    }
  }
  rec = h1.p->s20(self);
fin:
  {
    Hd7 c; c.p = h0.p; c.c = h0.c; if (c.c) ++*c.c;
    s0->s14(&rec, &c);
  }
  return;
seven:
  rec = h2.p->s20(self);
  if (f_05df80(&rec, self + 24)) {
    char *nd = *(char **)(Q7(self, 344) + 4);
    if (&h2 != (Hd7 *)(nd + 8)) {
      f_04ed28(&h2);
      h2.p = *(Vo **)(nd + 8); h2.c = *(int **)(nd + 12);
      if (h2.c) ++*h2.c;
    }
  }
  goto again;
}

/* --- f_0502bc: native-call marshalling --- */
void *f_04ebf4(void *, int);
extern char *D_1a2c08[5]; extern char *D_1a2e60[5]; extern char D_1a4320[]; extern char D_1a4270[];
extern void *D_1a2e74[];
struct T5 { char *w[5]; };
struct Cb {
  virtual void c0(); virtual void c1(); virtual int c2(int); virtual int c3(int, int); virtual float c4(int);
  virtual void c5(int, int); virtual void c6(int, float);
};
struct ObI {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObI(int v) { Q7(this, 4) = 0; Q7(this, 0) = (int)D_1a4320; Q7(this, 8) = v; }
};
struct ObF {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObF(float v) { double d = v; Q7(this, 0) = (int)D_1a4270; *(double *)((char *)this + 8) = d; Q7(this, 4) = 0; }
};
struct Pr7 {
  void *p; int *cnt;
  Pr7(void *o) { p = o; cnt = 0; if (o) { cnt = (int *)f_04dfa0(4); *cnt = 1; } }
  ~Pr7() { f_04ed28(this); }
};
struct Ar { Vo *o; int x; };

/* @draft 0x0502bc us f_0502bc
   WHAT IT DOES: marshals the arguments of a native call: for the descriptor's kind (0..4, at +12) it reads the argument format string, gathers the call's arguments (objects at +52, count at +48) into a temporary word buffer, converting 'I' arguments through virtual slot 23 and 'F' ones through slot 24 (double to float), then dispatches on the kind to one of five virtual methods of the target object at +60 (void/int/float results, optionally with a float parameter), frees the buffer and wraps the result by the kind's return format ('I' as a 16-byte integer object, 'F' as a 20-byte float object, otherwise an empty handle).
   Remaining difference: not scored beyond the draft; stack layout of the format tables and register allocation unmatched. */
Pr7 f_0502bc(char *args, int unused, char *desc) {
  unsigned kind = Q7(desc, 12);
  if (kind < 5) {
    T5 af = *(T5 *)D_1a2c08;
    T5 rf = *(T5 *)D_1a2e60;
    float fv = 0;
    int iv = 0;
    int *buf = 0;
    int n = Q7(args, 48);
    if (n > 0) {
      buf = (int *)f_04ebf4(args, n * 4);
      int *w = buf;
      for (int i = 0; i < Q7(args, 48); i++) {
        int c = af.w[kind][i];
        if (c == 73) {
          *w++ = (*(Ar **)(args + 52))[i].o->s23();
        } else if (c == 70) {
          *(float *)w++ = (float)(*(Ar **)(args + 52))[i].o->s24();
        }
      }
    }
    Cb *t = *(Cb **)(args + 60);
    if (t) {
      switch (kind) {
        case 0: t->c5(buf[0], buf[1]); break;
        case 1: iv = buf[1]; t->c6(buf[0], *(float *)&iv); break;
        case 2: iv = t->c2(buf[0]); break;
        case 3: fv = t->c4(buf[0]); break;
        case 4: iv = t->c3(buf[0], buf[1]); break;
      }
    }
    if (buf) f_04e4b4((char *)buf - 4);
    int c = rf.w[kind][0];
    if (c == 70) return Pr7(new ObF(fv));
    if (c == 73) return Pr7(new ObI(iv));
  }
  return Pr7(0);
}

/* --- f_04e1a0: constructor of the player core object --- */
void f_04ec74(void *, void *); void f_04eda0(void *); void f_04ee08(void *, void *);
extern char D_1a4530[]; extern char D_1a4678[];
struct Hn { int *p; int *c; Hn() { p = 0; c = 0; } ~Hn() { f_04ed28(this); } };
struct Ent7 { int a, b, c, d; Ent7() { a = 0; b = -1; c = 0; d = 0; } };
struct NdA { int a, b, c, d, e; };
struct TrA {
  int pad; NdA *h; int n;
  TrA() { pad = 0; h = (NdA *)f_04dfa0(20); h->b = 0; n = 0; h->c = (int)h; h->a = 0; h->d = (int)h; }
  ~TrA() {
    if (n) { f_04ec74(this, (void *)h->b); n = 0; h->c = (int)h; h->b = 0; h->d = (int)h; }
    f_04e4b4(h);
  }
};
struct TrB {
  int pad; int *h;
  TrB() { h = (int *)f_04dfa0(16); h[1] = (int)h; h[0] = (int)h; }
  ~TrB() { f_04eda0(this); f_04e4b4((void *)h); }
};
struct TrC {
  int pad; int *h; int n;
  TrC() { h = 0; h = (int *)f_04dfa0(44); h[1] = 0; n = 0; h[2] = (int)h; h[0] = 0; h[3] = (int)h; }
  ~TrC() {
    if (n) { f_04ee08(this, (void *)h[1]); n = 0; h[2] = (int)h; h[1] = 0; h[3] = (int)h; }
    f_04e4b4(h);
  }
};
struct TrD {
  int pad; int *h;
  TrD() { h = (int *)f_04dfa0(16); h[1] = (int)h; h[0] = (int)h; }
  ~TrD() { f_04e4b4(h); }
};
struct CoreB { void *vt; CoreB() { vt = D_1a4678; } ~CoreB() {} };
struct Core : CoreB {
  TrA tree8; Ent7 ent[14]; char u1[16];
  Hn h264, h272, h280, h288; Hn arr[4];
  TrB t328; TrB t340; TrC t348; TrD t364; Hn h372; int w380, w384;
  inline __attribute__((always_inline)) Core() { vt = D_1a4530; w384 = 0; w380 = 0; }
};
inline void *operator new(unsigned, void *p) throw() { return p; }

/* @draft 0x04e1a0 us f_04e1a0
   WHAT IT DOES: constructs the player core object in place: sets its vtable, builds the empty tree at +8, the fourteen {0,-1,0,0} slot records at +24, the counted-handle members at +264..+288 and the four-handle array at +296, the empty trees at +328, +340, +348 and +364, and the handle and words at +372..+384.
   Remaining difference: not scored beyond the draft; the exception cleanup pads are generated from member destructors and are not matched. */
void f_04e1a0(void *self) { new (self) Core; }

/* --- f_04f940: emits the dotted names of a list of owners --- */
void f_05e394(void *, void *, void *, void *); void f_05e4a8(void *, void *); int f_15c098(int, int);
void f_05cbd4(void *);
extern char D_1a4480[]; extern char D_1a43d0[];
struct ObN {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObN() { Q7(this, 0) = (int)D_1a4480; Q7(this, 4) = 0; }
};
struct Ob37 {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  Ob37(void *path) {
    Em7 e;
    Q7(this, 0) = (int)D_1a43d0; Q7(this, 16) = -1; Q7(this, 4) = 0;
    *((char *)this + 8) = 1;
    Q7(this, 12) = 0; Q7(this, 24) = 0;
    f_05e4a8((char *)this + 28, path);
  }
};

/* @draft 0x04f940 us f_04f940
   WHAT IT DOES: first reports an empty 8-byte marker object to f_05e394 for the target at the second argument; then walks the list of owner records hanging off +12 of the first argument, and for each builds a 36-byte named object from the record's name (the stored string at +28, or one built from the owner's id at +16 through f_15c098 when the index at +20 is not -1) and reports it to f_05e394 the same way.
   Remaining difference: not scored beyond the draft; landing pads, flag for the conditional delete and register allocation unmatched. */
void f_04f940(char *self, char *tgt) {
  {
    Pr7 pr(new ObN);
    int o[4]; int a = Q7(tgt, 4);
    f_05e394(o, tgt, &a, &pr);
  }
  char *end = (char *)Q7(self, 12);
  char *it = (char *)Q7(end, 8);
  while (it != end) {
    {
      Str7 s; char tag[16];
      if (Q7(it, 20) == -1) f_05e4a8(&s, (void *)Q7(it, 28));
      else f_05a3e8(&s, (void *)f_15c098(Q7(Q7(it, 16), 4), 7), tag);
      Pr7 pr(new Ob37(&s));
      int o[4]; int a = Q7(tgt, 4);
      f_05e394(o, tgt, &a, &pr);
    }
    f_05cbd4(&it);
  }
}

/* --- f_04f428: register a record with its owner, falling back to the local map --- */
void f_05dff0(void *, void *, void *); void f_05e068(void *, void *, void *, void *); int f_05dcb8(void *, void *);
void *f_154448(void *, void *, void *, int);
extern char D_1a4900[]; extern char D_1a3b7c[];
static inline bool eqk(int *a, int *b) {
  int x = a[1], y = b[1];
  if (x == -1 && y == -1) return a[3] == b[3];
  if (x == -1 || y == -1) return false;
  return x == y;
}

/* @draft 0x04f428 us f_04f428
   WHAT IT DOES: offers the record (four words) and a counted handle to the owner at +4 through its virtual slot 45; when the owner accepts, returns 1 at once. Otherwise finds the record's key in the map at +8 (inserting {record, empty handle} when absent), stores the handle in the entry, and, if the handle's object (virtual slot 10) carries an identical registration key at +152, casts the handle's object with __dynamic_cast and reports it through virtual slot 12 of this object (or the result of the handle's virtual slot 11 when there is no cast). Always returns 1.
   Remaining difference: not scored beyond the draft; handle copies and landing pads are open-coded, register allocation unmatched. */
int f_04f428(Vo *self, int *rec, Hd7 *h) {
  bool found = false;
  {
    Hd7 hc; hc.p = h->p; hc.c = h->c; if (hc.c) ++*hc.c;
    if (Q7(self, 4)) {
      Hd7 c; c.p = hc.p; c.c = hc.c; if (c.c) ++*c.c;
      int r = ((Vo *)Q7(self, 4))->s45(self, rec, &c);
      found = r != 0;
    }
  }
  if (found) return 1;
  char *tr = (char *)self + 8;
  char *it; f_05dff0(&it, tr, rec);
  char *end = *(char **)(tr + 4);
  if (it == end || f_05dcb8(rec, it + 16)) {
    int pair[6]; char *hint = it, *res;
    pair[0] = rec[0]; pair[1] = rec[1]; pair[2] = rec[2]; pair[3] = rec[3]; pair[4] = 0; pair[5] = 0;
    f_05e068(&res, tr, &hint, pair);
    it = res;
    f_04ed28(&pair[4]);
  }
  char *dst = it + 32;
  if (dst != (char *)h) {
    f_04ed28(dst);
    Q7(it, 32) = (int)h->p; Q7(it, 36) = (int)h->c;
    if (h->c) ++*h->c;
  }
  Vo *o = h->p->s10();
  if (o) {
    int *k = (int *)((char *)o + 152);
    if (eqk(k, rec)) {
      void *x = 0;
      if (h->p) x = f_154448(h->p, D_1a4900, D_1a3b7c, 0);
      if (x) self->s12(x); else self->s12(h->p->s11());
    }
  }
  return 1;
}

/* --- f_04d8a4: allocator dump --- */
int iprintf(const char *, ...); void f_126f1c(const char *);
extern char D_1a2c28[], D_1a2c38[], D_1a2c40[], D_1a2c48[], D_1a2c54[], D_1a2c64[], D_1a2c74[], D_1a2c80[], D_1a2c8c[];
extern char D_1a2c94[], D_1a2ca0[], D_1a2cb0[], D_1a2cc0[], D_1a2cd0[], D_1a2ce4[], D_1a2cf4[];
extern unsigned D_291424; extern int D_291744, D_291420, D_291668, D_29166c;
extern int **D_291690; extern int *D_291410; extern int *D_29174c;

/* @draft 0x04d8a4 us f_04d8a4
   WHAT IT DOES: prints a dump of the "lwalloc" small-block allocator: for every size class the free-list length and bytes held, then each free block address, then the used list and the leak list with each block's size (rounded to the class size plus a 16-byte header), and finally the allocator statistics (total, max used, header, free, used and leak byte counts).
   Remaining difference: not scored beyond the draft; list-walk loop shapes and register allocation unmatched. */
void f_04d8a4(void) {
  int freeb = 0, usedb = 0, leakb = 0;
  unsigned i;
  int *p;
  f_126f1c(D_1a2c28);
  f_126f1c(D_1a2c38);
  if (D_291424) {
    for (i = 0; i < D_291424; i++) {
      iprintf(D_1a2c48, i);
      int cnt = 0;
      for (p = D_291690[i]; p; p = (int *)*p) cnt++;
      int sz = 1 << (i + D_291744 + 1);
      int tot = (sz + 16) * cnt;
      iprintf(D_1a2c54, sz, 16, cnt, tot);
      freeb += tot;
      for (p = D_291690[i]; p; p = (int *)*p) iprintf(D_1a2c64, p);
    }
  }
  f_126f1c(D_1a2c40);
  for (p = D_291410; p; p = (int *)*p) {
    iprintf(D_1a2c74, p, p[2]);
    unsigned n = p[2];
    int sz = (n + 15) & -16;
    if (n < D_291424) sz = 1 << (n + D_291744 + 1);
    iprintf(D_1a2c80, sz, 16);
    usedb += sz + 16;
  }
  f_126f1c(D_1a2c8c);
  for (p = D_29174c; p; p = (int *)*p) {
    iprintf(D_1a2c74, p, p[2]);
    unsigned n = p[2];
    int sz = (n + 15) & -16;
    if (n < D_291424) sz = 1 << (n + D_291744 + 1);
    iprintf(D_1a2c80, sz, 16);
    leakb += sz + 16;
  }
  f_126f1c(D_1a2c94);
  iprintf(D_1a2ca0, D_291420);
  iprintf(D_1a2cb0, D_291420 - D_291668);
  iprintf(D_1a2cc0, D_291424 << 2);
  iprintf(D_1a2cd0, freeb, D_29166c);
  iprintf(D_1a2ce4, usedb);
  iprintf(D_1a2cf4, leakb);
}

/* --- f_05152c: unregister an object from the player --- */
void f_05f56c(void *, void *, void *); void f_05f1f4(void *, void *, void *); void f_05f238(void *, void *, void *, void *);
void f_05f5dc(void *, void *, void *); void *f_05cc58(void *, void *, void *, void *);
extern char D_1a493c[];
/* find the node for *kp in the tree, inserting a default entry (key, 4 zero-ish words, empty handle) when absent */
static inline char *slot7(char *tree, int *kp) {
  char *it;
  f_05f1f4(&it, tree, kp);
  char *end = *(char **)(tree + 4);
  if (it == end || (unsigned)*kp < (unsigned)Q7(it, 16)) {
    int tmp[6]; char *hint = it, *res;
    tmp[0] = 0; tmp[1] = -1; tmp[2] = 0; tmp[3] = 0;
    f_05daa4(&tmp[4], 0);
    int pr[7];
    pr[0] = *kp; pr[1] = tmp[0]; pr[2] = tmp[1]; pr[3] = tmp[2]; pr[4] = tmp[3]; pr[5] = tmp[4]; pr[6] = tmp[5];
    if (pr[6]) ++*(int *)pr[6];
    f_05f238(&res, tree, &hint, pr);
    it = res;
    f_04ed28(&pr[5]);
    f_04ed28(&tmp[4]);
  }
  return it;
}

/* @draft 0x05152c us f_05152c
   WHAT IT DOES: removes an object from the player's registry: looks the object up in the map at +348 and, when present, finds its parent's entry (defaulting it), casts the parent's handle object with __dynamic_cast, clears the parent's child-vector slot that holds the object, erases the object from the parent's index map at +48, asks the parent for its registered handle (virtual slot 13) and, when that handle's object is the removed one, tells the parent to drop the record (virtual slot 16); finally erases the object's own entry from the map at +348, destroying its handle and node.
   Remaining difference: not scored beyond the draft; handle temporaries and landing pads are open-coded, register allocation unmatched. */
void f_05152c(char *self, char *P) {
  char *tree = self + 348;
  int key = (int)P;
  char *it0;
  f_05f56c(&it0, tree, &key);
  char *end = *(char **)(tree + 4);
  if (it0 != end) {
    int par = Q7(P, 20);
    if (par) {
      char *pn = slot7(tree, &par);
      char *o = (char *)Q7(pn, 36);
      char *tgt = 0;
      if (o) tgt = (char *)f_154448(o, D_1a4900, D_1a493c, 0);
      char *m = tgt + 48;
      int k2 = (int)P;
      char *it3;
      f_05f5dc(&it3, m, &k2);
      char *e3 = *(char **)(m + 4);
      if (it3 != e3) {
        int idx = Q7(it3, 20);
        int *slot = &((int *)Q7(tgt, 36))[idx];
        if (*slot == k2) *slot = 0;
        void *nd = f_05cc58(it3, e3 + 4, e3 + 8, e3 + 12);
        f_04e4b4(nd);
        Q7(m, 8) = Q7(m, 8) - 1;
      }
      Hd7 t = ((Vo *)tgt)->s13(it0 + 20);
      if (t.p->s9() == key) ((Vo *)tgt)->s16(it0 + 20);
    }
    char *e = *(char **)(tree + 4);
    char *nd = (char *)f_05cc58(it0, e + 4, e + 8, e + 12);
    f_04ed28(nd + 36);
    f_04e4b4(nd);
    Q7(tree, 8) = Q7(tree, 8) - 1;
  }
}

/* --- f_050018: rebuild the name-to-id map from the owner's name table --- */
void f_05e7bc(void *, void *, void *); void f_05e834(void *, void *, void *, void *); void f_04ee68(void *, void *);

/* @draft 0x050018 us f_050018
   WHAT IT DOES: stores the argument at +40 and empties the name map at +24; then asks this object (virtual slot 41) for its table of 16-byte entries and, for every entry up to the first null name, builds a record {name, id, tree, key} (the id from f_15c07c on the name, or, when that is -1, a string-map key built through f_05a3e8/f_05e540 on the map at +8 of the name's owner) and inserts it into the map at +24 unless an equal key is already there.
   Remaining difference: not scored beyond the draft; the tree-find/insert inlines, landing pads and registers are open-coded. */
void f_050018(Vo *self, char *tbl) {
  char *tree = (char *)self + 24;
  Q7(self, 40) = (int)tbl;
  if (Q7(tree, 8)) {
    f_04ee68(tree, (void *)((int *)Q7(tree, 4))[1]);
    Q7(tree, 8) = 0;
    int *h = (int *)Q7(tree, 4);
    h[2] = (int)h; h[1] = 0; h[3] = (int)h;
  }
  int *e = self->s41();
  if (e) {
    char *nm = (char *)*e;
    while (nm) {
      int rec[4];
      rec[0] = (int)nm; rec[2] = 0; rec[3] = 0;
      rec[1] = f_15c07c(Q7(tbl, 4), 7, nm);
      if (rec[1] == -1) {
        char *s3 = nm + 8;
        Str7 s; char tag[16];
        f_05a3e8(&s, nm, tag);
        char *res[2];
        f_05e540(res, s3, &s);
        rec[2] = (int)s3; rec[3] = (int)(res[0] + 16);
      }
      char *it; f_05e7bc(&it, tree, rec);
      char *end = *(char **)(tree + 4);
      if (it == end || f_05dcb8(rec, it + 16)) {
        int pair[5]; char *hint = it, *res;
        pair[0] = rec[0]; pair[1] = rec[1]; pair[2] = rec[2]; pair[3] = rec[3]; pair[4] = 0;
        f_05e834(&res, tree, &hint, pair);
        it = res;
      }
      e += 4;
      nm = (char *)*e;
    }
  }
}

/* --- f_053e2c --- */
extern char D_1a4110[];
struct ObM {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObM() { Q7(this, 0) = (int)D_1a4110; Q7(this, 4) = 0; }
};

/* @draft 0x053e2c us f_053e2c
   WHAT IT DOES: picks a counted handle to pass along (when the flag is set, a copy of the handle two links down the chain at +328; otherwise a fresh empty 8-byte marker object), finds the chain's current object with f_05f64c, asks the second handle's object (virtual slot 20) for its registration record against this object, and hands the record plus a copy of the picked handle to virtual slot 14 of the found object.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_053e2c(char *self, unsigned flag) {
  char *q = self + 328;
  Hd7 hold; hold.p = 0; hold.c = 0;
  int o[4];
  if (flag & 0xff) {
    int *a = *(int **)(q + 4);
    int *v = (int *)a[1];
    if ((char *)&hold != (char *)(v + 2)) {
      f_04ed28(&hold);
      hold.p = (Vo *)v[2]; hold.c = (int *)v[3];
      if (hold.c) ++*hold.c;
    }
  } else {
    Pr7 pr(new ObM);
    if ((char *)&hold != (char *)&pr) {
      f_04ed28(&hold);
      hold.p = (Vo *)pr.p; hold.c = pr.cnt;
      if (hold.c) ++*hold.c;
    }
  }
  int b = *(int *)(Q7(q, 4) + 4);
  f_05f64c(o, q, &b);
  Hd7 h1;
  {
    int a = Q7(q, 4);
    int *v = *(int **)(a + 4);
    h1.p = (Vo *)v[2]; h1.c = (int *)v[3];
    if (h1.c) ++*h1.c;
    int b2 = *(int *)(a + 4);
    f_05f64c(o, q, &b2);
  }
  Vo *s0 = (Vo *)o[0];
  Rc7 rec = h1.p->s20(self);
  Hd7 c; c.p = hold.p; c.c = hold.c; if (c.c) ++*c.c;
  s0->s14(&rec, &c);
}

/* --- f_05582c --- */
/* @draft 0x05582c us f_05582c
   WHAT IT DOES: takes the counted handle two links down the chain at +328, asks its object for its name (virtual slot 7), builds a string from it, wraps the string in a 36-byte named object held by a counted handle, and reports it to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copy, landing pads and register allocation unmatched. */
void f_05582c(char *self) {
  char *q = self + 328;
  Hd7 h; int o[4];
  grab7(h, q, o);
  Str7 s; char tag[16];
  f_05a3e8(&s, h.p->s7(), tag);
  Pr7 pr(new Ob37(&s));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_054574 --- */
extern char D_1a4060[]; extern unsigned char D_1d2dc8[];
struct ObT {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObT(bool b) { Q7(this, 0) = (int)D_1a4060; Q7(this, 4) = 0; *((char *)this + 8) = b; }
};

/* @draft 0x054574 us f_054574
   WHAT IT DOES: takes two counted handles from the chain at +328, looks up the pair of their object types (virtual slot 6) in the 14-byte-per-row compatibility table at D_1d2dc8 and, when the table allows it, asks the second object whether it accepts the first (virtual slot 38); wraps the yes/no answer in a 12-byte flag object held by a counted handle and reports it to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_054574(char *self) {
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  int t0 = h0.p->s6();
  int t1 = h1.p->s6();
  bool ok = false;
  if (D_1d2dc8[t1 * 14 + t0]) ok = h1.p->s38(h0.p) != 0;
  Pr7 pr(new ObT(ok));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_0555d4 --- */
/* @draft 0x0555d4 us f_0555d4
   WHAT IT DOES: takes the counted handle two links down the chain at +328, obtains its object's name string by value (virtual slot 21), wraps it in a 36-byte named object held by a counted handle and reports it to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copy, landing pads and register allocation unmatched. */
void f_0555d4(char *self) {
  char *q = self + 328;
  Hd7 h; int o[4];
  grab7(h, q, o);
  Str7 s = h.p->s21();
  Pr7 pr(new Ob37(&s));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_050754: first-use setup of the root clip --- */
void f_05e980(void); void f_05dc90(void *, void *); void f_05daec(void *); void f_05e6cc(void *, void *, void *);
extern char D_1a3760[]; extern char D_1a2e90[];
struct ObR {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObR() {
    Em7 e;
    Q7(this, 0) = (int)D_1a3760; Q7(this, 4) = 0; Q7(this, 12) = 0;
    int *n = (int *)f_04dfa0(40);
    Q7(this, 12) = (int)n; n[1] = 0;
    Q7(this, 16) = 0; n[2] = (int)n; n[0] = 0; n[3] = (int)n;
  }
};
struct HdR { Vo *p; int *c; HdR(Vo *o) { p = o; c = 0; if (o) { c = (int *)f_04dfa0(4); *c = 1; } } ~HdR() { f_04ed28(this); } };

/* @draft 0x050754 us f_050754
   WHAT IT DOES: once per player (when the root object at +388 exists and the done-flag at +392 is clear): runs f_05e980, tells the root object about this player (virtual slot 42), builds an empty 24-byte registry object held by a counted handle, hands it a copy of its own handle plus the player's key record at +152 through virtual slot 14, then creates the "SWG" record with f_05e6cc and registers that too, and finally sets the done-flag.
   Remaining difference: not scored beyond the draft; handle copies are via f_05dc90/f_05daec, landing pads and register allocation unmatched. */
void f_050754(char *self) {
  if (Q7(self, 388) && !*(char *)(self + 392)) {
    f_05e980();
    ((Vo *)Q7(self, 388))->s42(self);
    HdR root((Vo *)Q7(self, 388));
    Pr7 pr(new ObR);
    Vo *o = (Vo *)pr.p;
    char t[8];
    f_05dc90(t, &root);
    o->s14(self + 152, t);
    f_04ed28(t);
    char rec[16];
    f_05e6cc(rec, self, D_1a2e90);
    f_05dc90(t, &pr);
    o->s14(rec, t);
    f_05daec(t);
    *(char *)(self + 392) = 1;
  }
}

/* --- f_056168 --- */
static inline Hd7 two7(Vo *h, char *self) {
  Hd7 r1 = h->s13(self + 152);
  return r1.p->s13(self + 136);
}

/* @draft 0x056168 us f_056168
   WHAT IT DOES: takes two counted handles from the chain at +328, resolves the second one's registered handle for the key at +152 and that one's for the key at +136 (virtual slot 13 each time), then wraps whether the result is the same object as the first handle in a 12-byte flag object held by a counted handle and reports it to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_056168(char *self) {
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  Hd7 r2 = two7(h1.p, self);
  bool same = h0.p == r2.p;
  Pr7 pr(new ObT(same));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_055d80 --- */
/* @draft 0x055d80 us f_055d80
   WHAT IT DOES: takes two counted handles from the chain at +328, asks the first object (virtual slot 20) for the registration record of this player, has the second object resolve a handle for that record (virtual slot 13), notes whether that handle's object type (virtual slot 6) is other than 3, tells the second object to drop the record (virtual slot 16), and reports the flag as a 12-byte flag object held by a counted handle to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_055d80(char *self) {
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  Rc7 rec = h0.p->s20(self);
  bool flag;
  {
    Hd7 r = h1.p->s13(&rec);
    flag = r.p->s6() != 3;
  }
  h1.p->s16(&rec);
  Pr7 pr(new ObT(flag));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_054e28 / f_054c08 --- */
/* @draft 0x054e28 us f_054e28
   WHAT IT DOES: takes two counted handles from the chain at +328 and reports to f_05e394, as a 12-byte flag object held by a counted handle, whether either object answers true to virtual slot 22 (the second is asked first, the first only when the second says no).
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_054e28(char *self) {
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  bool flag = false;
  if (h1.p->s22()) flag = true;
  else if (h0.p->s22()) flag = true;
  Pr7 pr(new ObT(flag));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* @draft 0x054c08 us f_054c08
   WHAT IT DOES: takes two counted handles from the chain at +328 and reports to f_05e394, as a 12-byte flag object held by a counted handle, whether both objects answer true to virtual slot 22 (the second is asked first, the first only when the second says yes).
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_054c08(char *self) {
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  bool flag = false;
  if (h1.p->s22()) { if (h0.p->s22()) flag = true; }
  Pr7 pr(new ObT(flag));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_054358 / f_0547d0 / f_0549ec: member-pointer predicate wrappers --- */
extern char D_1a2fc4[], D_1a2fcc[], D_1a2fd4[];
typedef char (Vo::*Pm7)(Vo *);
struct Rf7 { void *p; int *c; Rf7(void *o) { f_05daa4(this, o); } ~Rf7() { f_04ed28(this); } };
struct ObT2 {
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  ObT2(char b) { Q7(this, 0) = (int)D_1a4060; *((char *)this + 8) = b; Q7(this, 4) = 0; }
};

/* @draft 0x054358 us f_054358
   WHAT IT DOES: takes two counted handles from the chain at +328, calls the member function whose pointer is stored at D_1a2fc4 on the second object with the first object as argument, stores the result in a 12-byte flag object held by a counted handle and reports it to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_054358(char *self) {
  Pm7 pm = *(Pm7 *)D_1a2fc4;
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  Rf7 pr(new ObT2((h1.p->*pm)(h0.p)));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* @draft 0x0547d0 us f_0547d0
   WHAT IT DOES: same as f_054358 with the member function pointer at D_1a2fcc: calls it on the second object with the first as argument and reports the result as a flag object to f_05e394.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_0547d0(char *self) {
  Pm7 pm = *(Pm7 *)D_1a2fcc;
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  Rf7 pr(new ObT2((h1.p->*pm)(h0.p)));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* @draft 0x0549ec us f_0549ec
   WHAT IT DOES: same as f_054358 with the member function pointer at D_1a2fd4: calls it on the second object with the first as argument and reports the result as a flag object to f_05e394.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_0549ec(char *self) {
  Pm7 pm = *(Pm7 *)D_1a2fd4;
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  Rf7 pr(new ObT2((h1.p->*pm)(h0.p)));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

/* --- f_055bc0 --- */
int f_05aaf8(void *, void *, void *, void *);
/* @draft 0x055bc0 us f_055bc0
   WHAT IT DOES: takes two counted handles from the chain at +328, makes a copy of each, and returns f_05aaf8(this, arg, copy of the first, copy of the second).
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
int f_055bc0(char *self, void *arg) {
  char *q = self + 328;
  Hd7 h0, h1; int o[4];
  grab7(h0, q, o);
  grab7(h1, q, o);
  Hd7 c0; c0.p = h0.p; c0.c = h0.c; if (c0.c) ++*c0.c;
  Hd7 c1; c1.p = h1.p; c1.c = h1.c; if (c1.c) ++*c1.c;
  return f_05aaf8(self, arg, &c0, &c1);
}

/* --- f_055fa4 --- */
/* @draft 0x055fa4 us f_055fa4
   WHAT IT DOES: takes a counted handle from the chain at +328, asks its object (virtual slot 20) for the registration record of this player, has the root object stored at +288 resolve a handle for that record (virtual slot 13), notes whether that handle's object type (virtual slot 6) is other than 3, tells the root object to drop the record (virtual slot 16), and reports the flag as a 12-byte flag object held by a counted handle to f_05e394 with the chain sub-object.
   Remaining difference: not scored beyond the draft; handle copies, landing pads and register allocation unmatched. */
void f_055fa4(char *self) {
  char *q = self + 328;
  Hd7 h0; int o[4];
  grab7(h0, q, o);
  Rc7 rec = h0.p->s20(self);
  bool flag;
  {
    Hd7 r = ((Vo *)Q7(self, 288))->s13(&rec);
    flag = r.p->s6() != 3;
  }
  ((Vo *)Q7(self, 288))->s16(&rec);
  Pr7 pr(new ObT(flag));
  int o2[4]; int a2 = Q7(q, 4);
  f_05e394(o2, q, &a2, &pr);
}

}
}

/* ---- swg7a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg7a: untagged functions of the SWG player (big_e, big_a). */

namespace swg7a {
extern "C" {
void *f_05db08(unsigned n);
void f_05daa4(void *self, void *a1);
void f_05db44(void *);
void f_04ed28(void *);
void f_05df24(void *, void *);
void f_05e6cc(void *, int, void *);
void f_15f1e8(void *, float *, float *);
void f_15f238(void *, float *, float *);
void f_05db84(void *);
void f_05e4a8(void *, void *);
void f_05fadc(void *, void *);
void f_05a3e8(void *, const char *, void *);
char *f_05f0b8(void *, void *);
char *f_15c098(void *, int, int);
void f_04e8c0(void *) throw();
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
extern char D_291400[], D_1a43d0[], D_1a2e9c[], D_1a2ea0[];
int f_15c0f0(int, int);
void *f_154448(void *, void *, void *, int);
void f_06b050(void *, int);
void f_15fb50(void *, int);
void f_05f6a8(void *, unsigned, void *);
void f_05f954(void *, void *, void *);
void f_05f998(void *, void *, void *, void *);
void f_04e6d0(void *);
void f_0604dc(void *);
void f_05b780(void *, int);
void f_06053c(void *, void *, void *);
void *f_04dfa0(unsigned n);
extern char D_1a3760[], D_1a3fb0[];
extern char D_1a4900[], D_1a4990[], D_1a493c[];
extern char D_1a4270[], D_1a35bc[], D_1a35c0[];
}

struct Rf {
    int a, b;
    Rf() {}
    Rf(void *p) { f_05daa4(this, p); }
    ~Rf() { f_04ed28(this); }
    Rf &operator=(const Rf &o) { f_05df24(this, (void *)&o); return *this; }
};
struct NumD {
    void *vt; int z; double d;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    NumD(double x) { vt = (void *)D_1a4270; d = x; z = 0; }
};
struct VA { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void *v9(); };
struct VB { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual Rf v13(void *k); virtual void v14(void *k, const Rf &r); };
struct VC { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual double v24(); };

struct Tmp16 { int w[4]; ~Tmp16() {} };
struct StrT {
    char *p;
    StrT() {}
    ~StrT() { f_05db84(this); }
    StrT &operator=(const StrT &o) { f_05fadc(this, (void *)&o); return *this; }
};
extern "C" {
StrT f_05a44c(const char *, const StrT &);
StrT f_05a578(const StrT &, const StrT &);
}
struct NameStr : StrT {
    NameStr(char *node, Tmp16 &tg) {
        if (*(int *)(node + 4) == -1) {
            f_05e4a8(this, node + 12);
        } else {
            f_05a3e8(this, f_15c098(((void **)*(void **)node)[1], 7, *(int *)(node + 4)), &tg);
        }
    }
};
struct It4 { int *p; It4() {} It4(const It4 &o) { p = o.p; } };
struct Pr { int k, v; };
struct ObjBase { void *vt; int z; unsigned char b; int w[4]; ~ObjBase() { f_04e8c0(this); } };
struct ObjS : ObjBase {
    StrT s;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    ObjS(StrT &a) {
        vt = D_1a43d0; b = 1; w[0] = -1;
        z = 0; w[1] = 0; w[2] = 0; w[3] = 0;
        f_05e4a8(&s, &a);
    }
};
struct Key4 { int a, b, c, d; };
struct ObjR : ObjBase {
    StrT s;
    static void *operator new(unsigned n) { return f_05db08(n); }
    static void operator delete(void *p) { f_05db44(p); }
    void fin(const Key4 &k) {
        Tmp16 g;
        vt = D_1a43d0; z = 0; b = 0;
        w[0] = k.a; w[1] = k.b; w[2] = k.c; w[3] = k.d;
        char *e = D_291400;
        int st = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(e + 8);
        int o = *c; (void)o;
        *c += 1;
        sceKernelCpuResumeIntr(st);
        s.p = e + 12;
    }
    ObjR(char *self, char *v) {
        Key4 k;
        k.a = *(int *)(self + 40); k.b = f_15c0f0(*(int *)(self + 56), *(int *)(v + 164)); k.c = 0; k.d = 0;
        fin(k);
    }
    ObjR(char *self) {
        Key4 k;
        f_05e6cc(&k, *(int *)(self + 40), D_1a2e9c);
        fin(k);
    }
};
struct ObjSt : ObjS {
    ObjSt(StrT &a) : ObjS(a) {}
    ~ObjSt() { vt = D_1a43d0; }
};
struct VS { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual StrT v21(); };
struct B8c0 { void *vt; int x; B8c0() { vt = D_1a3760; x = 0; } ~B8c0() { f_04e8c0(this); } };
struct M6d0 {
    int w8; int *hdr; int cnt; int w20;
    M6d0() {
        hdr = 0;
        int *nd = (int *)f_04dfa0(40);
        hdr = nd; nd[1] = 0;
        nd[2] = (int)nd; cnt = 0; nd[3] = (int)nd; nd[0] = 0;
    }
    ~M6d0() { f_04e6d0(this); }
};
struct Mid : B8c0 { M6d0 m; ~Mid() __asm__("f_04e8d8"); };
struct VecM { int pad; int *b, *e, *c; ~VecM() { f_0604dc(this); } };
struct Fin6b4 : Mid {
    int a24, a28;
    VecM vec;
    Fin6b4(int a1, int a2, int n, unsigned char *p) __attribute__((always_inline));
};
inline Fin6b4::Fin6b4(int a1, int a2, int n, unsigned char *p) {
    vt = D_1a3fb0;
    a24 = a1; a28 = a2;
    vec.b = 0; vec.e = 0; vec.c = 0;
    f_05b780(&vec, n);
    for (int i = 0; i < n; i++) {
        int val = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
        p += 4;
        if (vec.e == vec.c) {
            f_06053c(&vec, vec.e, &val);
        } else {
            if (vec.e) *vec.e = val;
            vec.e++;
        }
    }
}
inline void *operator new(unsigned, void *p) { return p; }

extern "C" {
/* @implements 0x0682fc us f_0682fc
   WHAT IT DOES: looks up two keyed values (D_1a35bc, D_1a35c0) in the object's table through its virtual getter, and when the first yields a handle, reads two doubles from it, builds two boxed double values and stores them under the keys through the object's virtual setter; always returns an empty handle. */
Rf f_0682fc(char *self)
{
    VA *va = *(VA **)(self + 44);
    void *s0 = va->v9();
    char k1[16];
    f_05e6cc(k1, *(int *)(self + 40), D_1a35bc);
    Rf h(0);
    VB *vb = **(VB ***)(self + 52);
    h = vb->v13(k1);
    if (!h.a) return Rf(0);
    float fa = (float)((VC *)h.a)->v24();
    char k2[16];
    f_05e6cc(k2, *(int *)(self + 40), D_1a35c0);
    vb = **(VB ***)(self + 52);
    h = vb->v13(k2);
    if (!h.a) return Rf(0);
    float fb = (float)((VC *)h.a)->v24();
    f_15f1e8(s0, &fa, &fb);
    VB *p1 = **(VB ***)(self + 52);
    p1->v14(k1, Rf(new NumD(fa)));
    VB *p2 = **(VB ***)(self + 52);
    p2->v14(k2, Rf(new NumD(fb)));
    return Rf(0);
}
/* @implements 0x067ebc us f_067ebc
   WHAT IT DOES: looks up two keyed values (D_1a35bc, D_1a35c0) in the object's table through its virtual getter, and when the first yields a handle, reads two doubles from it, builds two boxed double values and stores them under the keys through the object's virtual setter; always returns an empty handle. */
Rf f_067ebc(char *self)
{
    VA *va = *(VA **)(self + 44);
    void *s0 = va->v9();
    char k1[16];
    f_05e6cc(k1, *(int *)(self + 40), D_1a35bc);
    Rf h(0);
    VB *vb = **(VB ***)(self + 52);
    h = vb->v13(k1);
    if (!h.a) return Rf(0);
    float fa = (float)((VC *)h.a)->v24();
    char k2[16];
    f_05e6cc(k2, *(int *)(self + 40), D_1a35c0);
    vb = **(VB ***)(self + 52);
    h = vb->v13(k2);
    if (!h.a) return Rf(0);
    float fb = (float)((VC *)h.a)->v24();
    f_15f238(s0, &fa, &fb);
    VB *p1 = **(VB ***)(self + 52);
    p1->v14(k1, Rf(new NumD(fa)));
    VB *p2 = **(VB ***)(self + 52);
    p2->v14(k2, Rf(new NumD(fb)));
    return Rf(0);
}
/* @draft 0x068ff8 us f_068ff8
   WHAT IT DOES: builds a dotted path string for an object: starts from an empty string, walks the parent chain from the object's first link (virtual slot 9 of the object at +44), and for each parent looks up its record in the map at +348 of the owner, takes its stored name or the name built from the id (f_15c098/f_05a3e8), joins it with a separator ("." style D_1a2ea0 when more parents follow, D_1a2e9c otherwise) in front of the string built so far, and finally returns a new 32-byte string object (vtable D_1a43d0) holding the result, wrapped in a handle.
   Remaining difference: the compiler threads the s0==0 separator test into a duplicated loop tail, and the string temporaries take s3..s5 in a different order. */
Rf f_068ff8(char *self)
{
    StrT r;
    {
        char *e = D_291400;
        int st = sceKernelCpuSuspendIntr();
        volatile int *c = (volatile int *)(e + 8);
        int o = *c; (void)o;
        *c += 1;
        sceKernelCpuResumeIntr(st);
        r.p = e + 12;
    }
    VA *va = *(VA **)(self + 44);
    char *s0 = (char *)va->v9();
    if (s0) {
        do {
            int key = (int)s0;
            s0 = *(char **)(s0 + 20);
            char *node = f_05f0b8(*(char **)(self + 40) + 348, &key);
            Tmp16 tg;
            r = f_05a578(f_05a44c(s0 ? D_1a2ea0 : D_1a2e9c, NameStr(node, tg)), r);
        } while (s0);
    }
    return Rf(new ObjS(r));
}
/* @draft 0x068588 us f_068588
   WHAT IT DOES: takes the first parent of the object (virtual slot 9 of the object at +44) and returns a handle to a new 32-byte string object (vtable D_1a43d0) holding an empty string and a four-word record: when the parent's id at +164 is set the record is {object's key at +40, f_15c0f0(object's table at +56, id), 0, 0}, otherwise it is built by f_05e6cc from the key and D_1a2e9c.
   Remaining difference: landing pads and frame (retail 560 bytes, the build 464). */
Rf f_068588(char *self)
{
    VA *va = *(VA **)(self + 44);
    char *v = (char *)va->v9();
    if (*(int *)(v + 164) != -1)
        return Rf(new ObjR(self, v));
    return Rf(new ObjR(self));
}
/* @draft 0x067024 us f_067024
   WHAT IT DOES: when the object has a parent at +44 that casts (f_154448) to the target type, builds a string through virtual slot 21 of the object's helper at +52, puts it in a temporary string object (vtable D_1a43d0, flag 1, id -1), copies the temporary's flag byte and four words into the target at +24 and assigns its string to the target's string at +52 (f_05fadc), then destroys the temporary; always returns an empty handle.
   Remaining difference: block order (retail places the shared empty-handle return before the body), s0/s1 swapped, 8 bytes of size. */
Rf f_067024(char *self)
{
    char *p = *(char **)(self + 44);
    if (!p) return Rf(0);
    char *t = (char *)f_154448(p, D_1a4900, D_1a4990, 0);
    if (!t) return Rf(0);
    VS *vs = **(VS ***)(self + 52);
    StrT str = vs->v21();
    ObjSt o(str);
    *(unsigned char *)(t + 32) = o.b;
    *(int *)(t + 28) = o.z;
    *(int *)(t + 36) = o.w[0]; *(int *)(t + 40) = o.w[1];
    *(int *)(t + 44) = o.w[2]; *(int *)(t + 48) = o.w[3];
    f_05fadc(t + 52, &o.s);
    return Rf(0);
}
/* @draft 0x068e6c us f_068e6c
   WHAT IT DOES: when the object has a non-zero parent at +20, finds the parent in the owner's list at +348, narrows it with a checked cast, frees the previous entry of its slot vector at the given index (f_15fb50), removes the object from the parent (f_06b050), then stores the object into that slot (growing the vector as needed) and records the index in the parent's map at +48. */
void f_068e6c(char *self, char *obj, unsigned idx)
{
    int k = *(int *)(obj + 20);
    if (k) {
    char *n = f_05f0b8(self + 348, &k);
    void *pa0 = *(void **)(n + 16);
    char *par = 0;
    if (pa0) par = (char *)f_154448(pa0, D_1a4900, D_1a493c, 0);
    char *vec = par + 32;
    void *sl = 0;
    if (idx < (unsigned)((*(int *)(vec + 8) - *(int *)(vec + 4)) >> 2))
        sl = ((void **)*(void **)(par + 36))[idx];
    if (sl) f_15fb50(sl, 0);
    f_06b050(par, (int)obj);
    char *ko = obj;
    if (!(idx < (unsigned)((*(int *)(vec + 8) - *(int *)(vec + 4)) >> 2))) {
        int z = 0;
        f_05f6a8(vec, idx + 1, &z);
    }
    (*(char ***)(par + 36))[idx] = ko;
    char *m = par + 48;
    It4 i0; It4 i16; It4 i32; It4 i48; Pr p64; It4 i80;
    f_05f954(&i0, m, &ko);
    int *hd = *(int **)(m + 4);
    i16.p = hd;
    int *t = i0.p;
    if (t == hd || (unsigned)ko < (unsigned)t[4]) {
        p64.k = (int)ko; p64.v = 0;
        i80.p = t;
        i48.p = t;
        f_05f998(&i32, m, &i80, &p64);
        i0.p = i32.p;
        t = i0.p;
    }
    t[5] = idx;
    }
}
/* @draft 0x06b4a4 us f_06b4a4
   WHAT IT DOES: constructor of a table object: stores the vtables D_1a3760 then D_1a3fb0, builds an empty 40-byte tree header node (f_04dfa0), keeps the two leading arguments at +24 and +28, reserves room (f_05b780) for count entries in the vector at +32 and fills it with count little-endian 32-bit words read from the byte pointer, using f_06053c when the vector is full.
   Remaining difference: landing-pad block layout (12 bytes) and a smaller frame than retail's 80 bytes. */
void f_06b4a4(void *self, int a1, int a2, int n, unsigned char *p)
{
    new (self) Fin6b4(a1, a2, n, p);
}
}
}

/* ---- swg8a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment by worker swg8a. */
namespace swg8a {
template <class T> static inline T &Y(void *p, int o) { return *(T *)((char *)p + o); }
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"
static inline float VCos(float a) {
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvcos.s S401, S400\n\tsv.s S401, %0" VFPU_END : "=m"(r) : "m"(a) : "memory");
    return r;
}
static inline float VSin(float a) {
    float r;
    __asm__ volatile(VFPU_BEGIN "lv.s S400, %1\n\tvsin.s S401, S400\n\tsv.s S401, %0" VFPU_END : "=m"(r) : "m"(a) : "memory");
    return r;
}
extern "C" {
void *f_04dfa0(unsigned);
void f_04b724(void *);
int f_15a754(void *);
void f_04e694(void *, void *);
void f_15b170(void *, void *, void *, void *, void *, void *, void *, int, int);
void f_15ba88(void *);
void f_15ba34(void *, void *);
void f_04e1a0(void *);
void *f_154448(void *, void *, void *, int);
void f_04ea4c(void *, void *, void *);
void *f_04ebf4(void *, int);
unsigned strlen(const char *);
extern int D_1a3958, D_1a3a78, D_1a3a10, D_1a39d0, D_1a3810, D_1a3760, D_1a3698, D_1a35d0;
extern int D_1a2be8[5], D_1a2c08[5];
extern char D_1a3b18[], D_1a3b64[];
extern int D_24100c;
void f_046620(void *, int);
void f_04637c(void *, int);
void f_04639c(void *);
int f_07dacc(int, int, void *, int);
void f_0463a4(void *, int, int, int, int, int, int, int, int, int, int, float, float, float, float);
extern float D_1a2b10, D_1a2b50, D_1a2b54, D_1a2b58, D_1a2b7c, D_1a2b80, D_1a2b84, D_1a2b88, D_1a2b8c, D_1a2b90;

/* @draft 0x04a648 us f_04a648
   WHAT IT DOES: builds a player movie instance: allocates its three holder objects (when not supplied), creates the 332-byte movie object, optionally builds a 68-byte text-style record with five 16-byte entries from two constant tables, and copies the two index arrays of the source data into the holder.
   Remaining difference: transcribed with plain pointer arithmetic; exception landing pads and exact register allocation not reproduced. */
int f_04a648(char *out, char *data, int x, int unused, char *t0, char *t1, char *t2) {
    f_04b724(out);
    if (!data || !f_15a754(data)) return 0;
    int *s6 = (int *)f_04dfa0(80);
    s6[0] = (int)&D_1a3958;
    Y<int>(s6, 16) = 0; Y<int>(s6, 20) = 0; Y<int>(s6, 24) = 0;
    Y<int>(s6, 32) = 0; Y<int>(s6, 36) = 0; Y<int>(s6, 40) = 0;
    char buf[64];
    f_04e694((char *)s6 + 44, buf);
    char *h2;
    if (!t2) {
        Y<int>(out, 4) = 1;
        h2 = 0;
        char *p = (char *)f_04dfa0(32);
        if (p) {
            h2 = p;
            Y<int>(p, 0) = (int)&D_1a3a78;
            Y<int>(p, 24) = (int)&D_24100c;
            Y<int>(p, 20) = 0;
        }
        Y<int>(h2, 28) = Y<int>(out, 28);
    } else {
        h2 = t2;
        Y<int>(out, 4) = 0;
    }
    char *s1;
    if (!t1) {
        Y<int>(out, 8) = 1;
        s1 = 0;
        char *p = (char *)f_04dfa0(16);
        if (p) { s1 = p; Y<int>(p, 0) = (int)&D_1a3a10; }
        Y<int>(s1, 12) = 0; Y<int>(s1, 8) = 0;
    } else {
        s1 = t1;
        Y<int>(out, 8) = 0;
    }
    char *s4;
    if (!t0) {
        Y<int>(out, 12) = 1;
        s4 = 0;
        char *p = (char *)f_04dfa0(28);
        if (p) { s4 = p; Y<int>(p, 0) = (int)&D_1a39d0; }
        Y<int>(s4, 16) = 0;
        Y<int>(s4, 20) = 0;
        Y<int>(s4, 16) = Y<int>(out, 28);
        Y<int>(s4, 8) = 0; Y<int>(s4, 12) = 0; Y<int>(s4, 24) = 0;
    } else {
        s4 = t0;
        Y<int>(out, 12) = 0;
    }
    char *s2 = 0;
    char *m = (char *)f_04dfa0(332);
    if (m) {
        f_15b170(m, s6, data, h2, s1, 0, s4, 60, 0);
        s2 = m;
    }
    if (Y<int>(Y<char *>(s2, 12), 40) & 1) {
        char *q = (char *)f_04dfa0(400);
        Y<int>(q, 0) = 400;
        char *r = q + 4;
        f_04e1a0(r);
        Y<int>(q, 4) = (int)&D_1a3810;
        Y<int>(r, 388) = 0;
        Y<char>(r, 392) = 0;
        f_15ba34(s2, r);
    }
    {
        char *a0 = Y<char *>(s2, 232);
        char *found = 0;
        if (a0) found = (char *)f_154448(a0, D_1a3b18, D_1a3b64, 0);
        if (found) {
            int s6o = Y<int>(out, 28);
            char *p = (char *)f_04dfa0(68);
            char *s0 = p + 12, *s5 = p + 4;
            Y<int>(p, 0) = 68;
            Y<int>(p, 4) = (int)&D_1a3760;
            Y<int>(s5, 4) = 0;
            Y<int>(s0, 4) = 0;
            char *n = (char *)f_04dfa0(40);
            Y<char *>(s0, 4) = n;
            Y<int>(n, 4) = 0;
            Y<int>(s5, 0) = (int)&D_1a3698;
            Y<char *>(Y<char *>(s0, 4), 8) = Y<char *>(s0, 4);
            Y<int>(s0, 8) = 0;
            Y<char *>(Y<char *>(s0, 4), 12) = Y<char *>(s0, 4);
            char b2[16], b3[16], b4[16];
            Y<int>(n, 0) = 0;
            f_04ea4c(s5 + 24, b2, b3);
            int ta[5], tb[5];
            for (int k = 0; k < 5; k++) ta[k] = D_1a2be8[k];
            for (int k = 0; k < 5; k++) tb[k] = D_1a2c08[k];
            Y<int>(s5, 0) = (int)&D_1a35d0;
            Y<char *>(found, 388) = s5;
            Y<int>(s5, 60) = s6o;
            Y<int>(s5, 56) = 0;
            char *a5 = (char *)f_04ebf4(s5, 96);
            Y<char *>(s5, 56) = a5;
            int ent[4];
            for (int i = 0; i < 5; i++) {
                const char *str = (const char *)tb[i];
                int len = 0;
                if (str) { len = strlen(str); a5 = Y<char *>(s5, 56); }
                ent[0] = ta[i];
                ent[1] = 2;
                ent[2] = len;
                ent[3] = i;
                int *dst = (int *)(a5 + i * 16);
                dst[0] = ent[0]; dst[1] = ent[1]; dst[2] = ent[2]; dst[3] = ent[3];
            }
            ent[1] = 1; ent[2] = 0; ent[3] = 0; ent[0] = 0;
            Y<int>(a5, 80) = 0;
            Y<int>(a5, 84) = ent[1];
            Y<int>(a5, 88) = ent[2];
            Y<int>(a5, 92) = ent[3];
        }
        f_15ba88(s2);
        int cnt = (Y<int>(s2, 44) - Y<int>(s2, 40)) >> 2;
        if (cnt * (int)0xaaaaaaab > 0) Y<int>(s2, 240) = x;
        Y<char *>(out, 0) = s2;
        if (Y<int>(out, 12)) {
            int n0 = Y<int>(data, 144);
            Y<char *>(s4, 20) = out + 16;
            Y<char *>(s4, 24) = out + 24;
            int off = Y<int>(data, 148);
            if (n0 > 0) {
                int *d = (int *)f_04dfa0(n0 * 4);
                Y<int *>(s4, 8) = d;
                int *src = (int *)(off + data);
                for (int i = 0; i < n0; i++) d[i] = (int)(data + src[i]);
            }
            int n1 = Y<int>(data, 168);
            int off1 = Y<int>(data, 172);
            if (n1 > 0) {
                int *d = (int *)f_04dfa0(n1 * 4);
                Y<int *>(s4, 12) = d;
                int *src = (int *)(off1 + data);
                for (int i = 0; i < n1; i++) d[i] = (int)(data + src[i]);
            }
        }
        return 1;
    }
    return 1;
}

/* @draft 0x047248 us f_047248
   WHAT IT DOES: lays out and emits one line of text glyph quads: looks up (or loads, via f_07dacc) the font page for key a3/a4 in a 20-entry cache of the context, then walks the font's groups and their 16-byte glyph entries, scaling widths by sx, accumulating a justified x position and a running maximum y, and calls f_0463a4 for each glyph; returns 1, or 0 if w>=481 or the load fails.
   Remaining difference: not yet scored against retail register allocation. */
int f_047248(char *ctx, int w, int ox, int key, int key2, int *tab, float sx, float sy, float c1, float c2, float c3, float c4) {
    if (!(w < 481)) return 0;
    int a7 = Y<int>(ctx, 0);
    int idx = Y<int>(ctx, 20);
    char *P = Y<char *>(ctx, 24) + idx * 0xaf20;
    Y<int>(ctx, 8) = Y<int>(ctx, idx * 4 + 828);
    if (key != Y<int>(ctx, idx * 4 + 28) || Y<int>(ctx, idx * 4 + 748) != key2 || Y<unsigned char>(ctx, 908)) {
        int r = f_07dacc(a7, key, P, key2);
        Y<int>(ctx, 8) = r;
        if (r == -1) return 0;
        Y<int>(ctx, idx * 4 + 828) = r;
        Y<int>(ctx, idx * 4 + 28) = key;
        Y<int>(ctx, idx * 4 + 748) = key2;
    }
    int nx = idx + 1;
    Y<unsigned char>(ctx, 908) = 0;
    Y<int>(ctx, 20) = nx < 20 ? nx : 0;
    char buf[32];
    int s5 = Y<int>(ctx, 8);
    f_046620(buf, -1);
    f_04637c(buf, tab[Y<int>(ctx, 8)]);
    int maxy = 0, prevmax = 0, j = 0;
    if (Y<int>(P, 0) > 0) {
        int s8 = Y<short>(P, 10);
        float fw = (float)w;
        char *g = P;
        do {
            int gx = Y<short>(g, 8);
            float f20 = 0;
            for (int i = 0; i < Y<int>(g, 4); i++) {
                int x0 = Y<short>(g, 12 + i * 16), x1 = Y<short>(g, 16 + i * 16);
                f20 += (float)(x1 - x0) * sx;
            }
            f20 = fw - f20 * D_1a2b10;
            char *e = g;
            for (int i = 0; i < Y<int>(g, 4); i++, e += 16) {
                int x0 = Y<short>(e, 12), x1 = Y<short>(e, 16);
                int v3 = Y<short>(e, 14), v2 = Y<short>(e, 18);
                int rowA = v3 / 1000, rowB = v2 / 1000;
                v3 -= rowA * 1000;
                v2 -= rowB * 1000;
                if (rowA != s5) {
                    s5 = rowA;
                    f_04639c(buf);
                    f_04637c(buf, tab[Y<int>(ctx, 8) + rowA * 10]);
                }
                int dy = v2 - v3;
                int dx = (int)((float)(x1 - x0) * sx);
                int ypos = s8 + (int)((float)dy * sy) + ox;
                int px0 = (int)((float)gx + f20);
                int a2v = s8 + ox;
                int px1;
                if (i == Y<int>(g, 4) - 1) {
                    gx += dx;
                    px1 = (int)((float)gx + f20);
                } else {
                    int lh8 = Y<short>(e, 8), lh24 = Y<short>(e, 24);
                    gx += dx;
                    px1 = (int)((float)gx + f20);
                    gx = gx + lh24 - (lh8 + (x1 - x0));
                }
                if (ypos > maxy) maxy = ypos;
                f_0463a4(buf, px0, a2v, -1, x0, v3, px1, ypos, -1, x1, v2, c1, c2, c3, c4);
            }
            if (maxy == 0) maxy = prevmax;
            j++;
            ox = maxy + 1;
            prevmax = maxy;
            g += 6404;
        } while (j < Y<int>(P, 0));
    }
    f_04639c(buf);
    return 1;
}

/* @draft 0x04c4c8 us f_04c4c8
   WHAT IT DOES: rotates the four corner points of entry a1 about the point (cx,cy) offset by the entry's first corner, using the vector unit's sine and cosine of the angle, writes the rotated corners into the entry's vertex slots, and stores the scaled min x at +80 and max x plus one at +84. */
void f_04c4c8(char *s, int a1, float cx, float cy, float ang) {
    if (Y<int>(s, 32) >= a1) {
        char *e = Y<char *>(s, 36) + a1 * 172;
        float *f = (float *)e;
        cx = cx + f[23];
        cy = cy + f[27];
        ang = ang * D_1a2b50;
        for (int i = 0; i < 4; i++) {
            float dx = f[23 + i] - cx;
            f[2 + i * 5] = dx * VCos(ang) - (f[27 + i] - cy) * VSin(ang) + cx;
            float dx2 = f[23 + i] - cx;
            f[3 + i * 5] = dx2 * VSin(ang) + (f[27 + i] - cy) * VCos(ang) + cy;
        }
        float lo = f[2];
        if (f[7] < lo) lo = f[7];
        if (f[12] < lo) lo = f[12];
        if (f[17] < lo) lo = f[17];
        *(int *)(e + 80) = (int)(lo * D_1a2b54);
        float hi = f[2];
        if (hi < f[7]) hi = f[7];
        if (hi < f[12]) hi = f[12];
        if (hi < f[17]) hi = f[17];
        *(int *)(e + 84) = (int)((hi + D_1a2b58) * D_1a2b54);
    }
}

/* @draft 0x04cb48 us f_04cb48
   WHAT IT DOES: scales the corner offsets of entry a1 by (sx,sy) about the point (cx,cy), rotates them with the vector unit's sine and cosine of the angle, writes four rotated vertices at +8/+12, +28/+32, +68/+72 and +48/+52, and stores the scaled min x at +80 and max x plus one at +84. */
void f_04cb48(char *s, int a1, float cx, float cy, float ang, float sx, float sy) {
    if (Y<int>(s, 32) >= a1) {
        char *e = Y<char *>(s, 36) + a1 * 172;
        float *f = (float *)e;
        float u0 = -(cx * sx), v0 = -(cy * sy);
        float x0 = f[23], y0 = f[27];
        float u1 = (f[24] - x0) * sx + u0;
        float v1 = (f[29] - y0) * sy + v0;
        cx = cx + x0;
        cy = cy + y0;
        ang = ang * D_1a2b7c;
        float x00 = u0 * VCos(ang) - v0 * VSin(ang) + cx;
        f[2] = x00;
        f[3] = u0 * VSin(ang) + v0 * VCos(ang) + cy;
        float x10 = u1 * VCos(ang) - v0 * VSin(ang) + cx;
        f[7] = x10;
        f[8] = u1 * VSin(ang) + v0 * VCos(ang) + cy;
        float x11 = u1 * VCos(ang) - v1 * VSin(ang) + cx;
        f[17] = x11;
        f[18] = u1 * VSin(ang) + v1 * VCos(ang) + cy;
        float x01 = u0 * VCos(ang) - v1 * VSin(ang) + cx;
        f[12] = x01;
        f[13] = u0 * VSin(ang) + v1 * VCos(ang) + cy;
        float lo = x00;
        if (x10 < lo) lo = x10;
        if (x01 < lo) lo = x01;
        if (x11 < lo) lo = x11;
        *(int *)(e + 80) = (int)(lo * D_1a2b80);
        float hi = x00;
        if (hi < x10) hi = x10;
        if (hi < x01) hi = x01;
        if (hi < x11) hi = x11;
        *(int *)(e + 84) = (int)((hi + D_1a2b84) * D_1a2b80);
    }
}

/* @draft 0x04ce2c us f_04ce2c
   WHAT IT DOES: like f_04cb48 but the rotation centre is the translation point (tx+cx, ty+cy) rather than the entry corner; scales the corner offsets of entry a1 by (sx,sy) about the point (cx,cy), rotates them with the vector unit's sine and cosine of the angle, writes four rotated vertices at +8/+12, +28/+32, +68/+72 and +48/+52, and stores the scaled min x at +80 and max x plus one at +84. */
void f_04ce2c(char *s, int a1, float cx, float cy, float ang, float sx, float sy, float tx, float ty) {
    if (Y<int>(s, 32) >= a1) {
        char *e = Y<char *>(s, 36) + a1 * 172;
        float *f = (float *)e;
        float u0 = -(cx * sx), v0 = -(cy * sy);
        float x0 = f[23], y0 = f[27];
        float u1 = (f[24] - x0) * sx + u0;
        float v1 = (f[29] - y0) * sy + v0;
        float ex = tx + cx;
        float ey = ty + cy;
        ang = ang * D_1a2b88;
        float x00 = u0 * VCos(ang) - v0 * VSin(ang) + ex;
        f[2] = x00;
        f[3] = u0 * VSin(ang) + v0 * VCos(ang) + ey;
        float x10 = u1 * VCos(ang) - v0 * VSin(ang) + ex;
        f[7] = x10;
        f[8] = u1 * VSin(ang) + v0 * VCos(ang) + ey;
        float x11 = u1 * VCos(ang) - v1 * VSin(ang) + ex;
        f[17] = x11;
        f[18] = u1 * VSin(ang) + v1 * VCos(ang) + ey;
        float x01 = u0 * VCos(ang) - v1 * VSin(ang) + ex;
        f[12] = x01;
        f[13] = u0 * VSin(ang) + v1 * VCos(ang) + ey;
        float lo = x00;
        if (x10 < lo) lo = x10;
        if (x01 < lo) lo = x01;
        if (x11 < lo) lo = x11;
        *(int *)(e + 80) = (int)(lo * D_1a2b8c);
        float hi = x00;
        if (hi < x10) hi = x10;
        if (hi < x01) hi = x01;
        if (hi < x11) hi = x11;
        *(int *)(e + 84) = (int)((hi + D_1a2b90) * D_1a2b8c);
    }
}

/* @draft 0x04699c us f_04699c
   WHAT IT DOES: emits unscaled text glyph quads for a font page P: for each group (stride 6404) and each 16-byte glyph entry it splits the packed row numbers by 1000, switches the glyph style via f_04639c/f_04637c when the row changes, positions the glyph at (ox + entry offset, oy + entry offset) and calls f_0463a4; the next group starts one line below the maximum y reached; returns 1. */
int f_04699c(int unused, int ox, int oy, char *P, int row0, int *tab, float c1, float c2, float c3, float c4) {
    char buf[32];
    int maxy = 0;
    int s4 = row0;
    f_046620(buf, -1);
    f_04637c(buf, tab[row0]);
    int j = 0;
    if (Y<int>(P, 0) > 0) {
        char *g = P;
        do {
            char *e = g;
            for (int i = 0; i < Y<int>(g, 4); i++, e += 16) {
                int x0 = Y<short>(e, 12), v3 = Y<short>(e, 14), x1 = Y<short>(e, 16), v2 = Y<short>(e, 18);
                int rowA = v3 / 1000;
                if (rowA != s4) {
                    s4 = rowA;
                    f_04639c(buf);
                    f_04637c(buf, tab[row0 + rowA * 10]);
                }
                int rowB = v2 / 1000;
                v3 -= rowA * 1000;
                v2 -= rowB * 1000;
                int lh8 = Y<short>(e, 8);
                int px1 = lh8 + (x1 - x0) + ox;
                int px0 = lh8 + ox;
                int lh10 = Y<short>(e, 10);
                int a2v = lh10 + oy;
                int ypos = lh10 + (v2 - v3) + oy;
                if (ypos > maxy) maxy = ypos;
                f_0463a4(buf, px0, a2v, -1, x0, v3, px1, ypos, -1, x1, v2, c1, c2, c3, c4);
            }
            j++;
            oy = maxy + 1;
            g += 6404;
        } while (j < Y<int>(P, 0));
    }
    f_04639c(buf);
    return 1;
}
}
}

/* ---- swg8c ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 wave 4, worker swg8c */
namespace swg8c {
extern "C" {

void f_04ed28(void *);
void f_05f64c(void *, void *, void *);
void f_05e394(void *, void *, void *, void *);
struct Ref {
    char *p;
    int *rc;
    ~Ref() { f_04ed28(this); }
};

void f_05e4a8(void *, void *) throw();
void f_04eee8(void *s, void *tag);
int sceKernelCpuSuspendIntr(void);
void sceKernelCpuResumeIntr(int);
extern char D_1a4d14[];
struct G2 { int w[4]; ~G2() {} };
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
typedef Str (*VFs)(char *);
static inline void *vf8(void *p, int i) { return (*(void ***)p)[i]; }
int f_15e078(int, char *);

void *memmove(void *, const void *, unsigned);
void *f_04dfa0(int);
void f_04e4b4(void *);
void f_06544c(unsigned *, unsigned *, const unsigned *);
unsigned *f_06547c(unsigned *, unsigned, const unsigned *);
unsigned *f_0618ec(unsigned *, unsigned, const unsigned *);
struct Vec8 { int pad; unsigned *b, *e, *c; };
inline const unsigned &mx8(const unsigned &a, const unsigned &b) { if (a < b) return b; return a; }
struct It { char *n; It() {} It(const It &o) { n = o.n; } };

/* @implements 0x059000 us f_059000
   WHAT IT DOES: pops the argument stack at +328 once, loads the next top as a reference-counted handle, pops it, calls virtual slot 22 on the object and, when it returns nonzero, pops four more entries; then pops once more and releases the handle. */
void f_059000(char *s) {
    char *t = s + 328;
    It it, r, arg;
    Ref a;
    it.n = *(char **)(t + 4);
    arg.n = (it.n = *(char **)(it.n + 4));
    f_05f64c(&r, t, &arg);
    arg.n = *(char **)(t + 4);
    char *nd = *(char **)(arg.n + 4);
    a.rc = *(int * volatile *)(nd + 12);
    a.p = *(char * volatile *)(nd + 8);
    arg.n = nd;
    if (a.rc) *a.rc += 1;
    arg.n = *(char **)(t + 4);
    it.n = (arg.n = *(char **)(arg.n + 4));
    f_05f64c(&r, t, &it);
    if (((int (*)(void *))(*(void ***)a.p)[22])(a.p)) {
        arg.n = *(char **)(t + 4);
        it.n = (arg.n = *(char **)(arg.n + 4));
        f_05f64c(&r, t, &it);
        arg.n = *(char **)(t + 4);
        it.n = (arg.n = *(char **)(arg.n + 4));
        f_05f64c(&r, t, &it);
        arg.n = *(char **)(t + 4);
        it.n = (arg.n = *(char **)(arg.n + 4));
        f_05f64c(&r, t, &it);
        arg.n = *(char **)(t + 4);
        it.n = (arg.n = *(char **)(arg.n + 4));
        f_05f64c(&r, t, &it);
    }
    arg.n = *(char **)(t + 4);
    it.n = (arg.n = *(char **)(arg.n + 4));
    f_05f64c(&r, t, &it);
}

int memcmp(const void *, const void *, unsigned) throw();
void f_064c6c(void *);
int *f_0650fc(int *, char *, char *, char *, void *);
inline const unsigned &min8(const unsigned &a, const unsigned &b) { if (b < a) return b; return a; }
struct Sp8 { char *p; };
inline bool cmp8(Sp8 &ka, Sp8 &kb) {
    char *ap = ka.p;
    char *bp = kb.p;
    const unsigned a = *(unsigned *)(ap - 12);
    const unsigned b = *(unsigned *)(bp - 12);
    int r = memcmp(ap, bp, min8(a, b));
    if (!r) r = a - b;
    return r < 0;
}
struct NodeIt8 { char *n; int pad[3]; };
struct InsRes8 { char *it; unsigned char ok; };

/* @draft 0x05e540 us f_05e540
   Remaining difference: the string length compare reloads its lengths after memcmp and the frame is 16 bytes short.
   WHAT IT DOES: unique insert into the string keyed tree: walks down comparing the key string with memcmp and the length difference, checks the predecessor for an equal key, and either inserts through f_0650fc (returning the new node and 1) or returns the existing node and 0. */
InsRes8 *f_05e540(InsRes8 *out, char *t, Sp8 *key) {
    char *x;
    char *y = *(char **)(t + 4);
    x = *(char **)(y + 4);
    int comp = 1;
    Sp8 k = *key;
    while (x) {
        y = x;
        comp = cmp8(k, *(Sp8 *)(x + 16));
        x = comp ? *(char **)(x + 8) : *(char **)(x + 12);
    }
    NodeIt8 j;
    NodeIt8 lm;
    NodeIt8 r;
    j.n = y;
    if (comp) {
        lm.n = *(char **)(*(char **)(t + 4) + 8);
        if (j.n != lm.n)
            f_064c6c(&j);
        else
            goto ins;
    }
    if (!cmp8(*(Sp8 *)(j.n + 16), *key)) {
        out->ok = 0;
        out->it = j.n;
        return out;
    }
ins:
    {
        f_0650fc((int *)&r, t, x, y, key);
        out->ok = 1;
        out->it = r.n;
    }
    return out;
}

extern char D_1a4320[];
struct ObL {
    void *vt; int x; int c;
    static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
    static void operator delete(void *p) { f_04e4b4((unsigned *)p - 1); }
    ObL(const Str &s) { vt = D_1a4320; x = 0; c = *(int *)(s.p - 12); }
};
struct RefN {
    char *p; int *rc;
    RefN(char *o) { p = o; rc = 0; if (o) { int *c = (int *)f_04dfa0(4); *c = 1; rc = c; } }
    ~RefN() { f_04ed28(this); }
};
static inline void ins8(It *out, char *t, It *pos, const RefN &h) {
    pos->n = *(char **)(t + 4);
    f_05e394(out, t, pos, (void *)&h);
}

extern char D_1a3958[], D_1a3ad0[];
void f_060c80(void *, void *, void *);
void f_05da50(void *);
void f_04e65c(void *, void *, int);
struct Lm { int pad; char *hd; ~Lm() { f_05da50(this); f_04e4b4(hd); } };
struct Vb { int pad; char *b, *e, *c; ~Vb() { f_04e65c(b, e, 0); if (b) f_04e4b4(b); } };
struct Vc {
    int pad; char *b, *e, *c;
    ~Vc() {
        for (char *p = b; p != e; p += 44) ((void (*)(void *))vf8(p, 0))(p);
        if (b) f_04e4b4(b);
    }
};
struct Tmp16 { int w[4]; ~Tmp16() {} };
struct Base9 { void *vt; ~Base9() { vt = D_1a3ad0; } };
struct Obj9 : Base9 {
    int w[2];
    Vc c;
    Vb b;
    Lm a;
    ~Obj9() {
        vt = D_1a3958;
        char *s0 = (char *)this + 44;
        void *out[4];
        void *x;
        x = *(void **)(*(char **)(s0 + 4));
        void *y = *(void **)x;
        out[0] = y;
        Tmp16 tmp;
        f_060c80(out, &x, this);
        f_05da50(s0);
    }
};

void f_059848(void *);
struct Obj9b : Base9 {
    int w[2];
    Vc c;
    Vb b;
    Lm a;
    static void operator delete(void *p) { f_04e4b4(p); }
    ~Obj9b() {
        vt = D_1a3958;
        f_059848(this);
    }
};

/* @draft 0x058a44 us f_058a44
   Remaining difference: one word, the inlined string destructor on the unwind path uses blez where retail has blezl (branch likely).
   WHAT IT DOES: pops the top argument as a handle; asks the object at the next entry of the list at +344 (virtual slot 9) for a value, then if the handle's type (slot 6) is 7 and the value is nonzero, fetches its name string (slot 21), terminates it and passes it to f_15e078, otherwise returns slot 23 of the handle minus one; returns -1 for the null value case. */
int f_058a44(char *s) {
    char *t = s + 328;
    Ref a;
    It it, r, arg;
    it.n = *(char **)(t + 4);
    char *nd = *(char **)(it.n + 4);
    a.rc = *(int * volatile *)(nd + 12);
    a.p = *(char * volatile *)(nd + 8);
    it.n = nd;
    if (a.rc) *a.rc += 1;
    it.n = *(char **)(t + 4);
    arg.n = (it.n = *(char **)(it.n + 4));
    f_05f64c(&r, t, &arg);
    arg.n = *(char **)(s + 344);
    char *n2 = *(char **)(arg.n + 4);
    char *o = *(char **)(n2 + 8);
    arg.n = n2;
    int obj = ((int (*)(void *))vf8(o, 9))(o);
    int res = -1;
    if (((int (*)(void *))vf8(a.p, 6))(a.p) == 7) {
        if (obj) {
            Str str = (*(VFs *)(*(char **)a.p + 84))(a.p);
            str.p[*(int *)(str.p - 12)] = D_1a4d14[0];
            res = f_15e078(obj, str.p);
        }
    } else {
        res = ((int (*)(void *))vf8(a.p, 23))(a.p) - 1;
    }
    return res;
}

/* @draft 0x05f774 us f_05f774
   Remaining difference: register allocation only (retail keeps the vector in s2 and reuses s1 for the element count in the in-place path; here x lives in s4), 4 bytes longer.
   WHAT IT DOES: vector fill insert: inserts n copies of *x at pos in a vector of 4-byte elements; when the spare capacity suffices it shifts the tail up with memmove and fills (uninitialized fill for the part past the old end), otherwise allocates a block of size old + max(old, n), memmoves the head, fills, memmoves the tail, frees the old block and updates begin, end and capacity. */
void f_05f774(Vec8 *v, unsigned *pos, unsigned n, const unsigned *x) {
    if (n != 0) {
        if ((unsigned)(v->c - v->e) >= n) {
            unsigned xc = *x;
            unsigned *old = v->e;
            unsigned ab = (char *)old - (char *)pos;
            unsigned after = (int)ab >> 2;
            if (n < after) {
                memmove(old, old - n, (char *)old - (char *)(old - n));
                v->e += n;
                memmove(old - (old - n - pos), pos, (old - n - pos) * 4);
                f_06544c(pos, pos + n, &xc);
            } else {
                f_06547c(old, n - after, &xc);
                v->e += n - after;
                memmove(v->e, pos, ab);
                v->e += after;
                f_06544c(pos, old, &xc);
            }
        } else {
            unsigned osz = v->e - v->b;
            unsigned len = osz + mx8(osz, n);
            unsigned *nb = (unsigned *)f_04dfa0(len * 4);
            unsigned bytes = (char *)pos - (char *)v->b;
            memmove(nb, v->b, bytes);
            unsigned *p = f_0618ec((unsigned *)((char *)nb + bytes), n, x);
            unsigned tail = (char *)v->e - (char *)pos;
            memmove(p, pos, tail);
            if (v->b) f_04e4b4(v->b);
            v->c = nb + len;
            v->e = (unsigned *)((char *)p + tail);
            v->b = nb;
        }
    }
}

/* @draft 0x057f2c us f_057f2c
   Remaining difference: retail guards the allocated block with a conditional-free flag (s6) across the name call and keeps the string at sp+96 with its tag at sp+80; here the new-expression leaves no guard (512 vs 544 bytes).
   WHAT IT DOES: pops the top argument as a handle, asks its object (virtual slot 21) for a name string, builds a 12-byte value object (vtable D_1a4320, zero, the string's length) wrapped in a counted handle and pushes it on the argument stack; frees the string and the temporaries. */
void f_057f2c(char *s) {
    char *t = s + 328;
    Ref a;
    It it, r, arg;
    it.n = *(char **)(t + 4);
    char *nd = *(char **)(it.n + 4);
    a.rc = *(int * volatile *)(nd + 12);
    a.p = *(char * volatile *)(nd + 8);
    it.n = nd;
    if (a.rc) *a.rc += 1;
    it.n = *(char **)(t + 4);
    arg.n = (it.n = *(char **)(it.n + 4));
    f_05f64c(&r, t, &arg);
    ins8(&arg, t, &r, RefN((char *)new ObL((*(VFs *)(*(char **)a.p + 84))(a.p))));
}

/* @draft 0x059890 us f_059890
   Remaining difference: 452 vs 508 bytes; retail has a separate unwind stub per member-destructor call site (six small landing pads), here they merge; the vtable store is scheduled differently.
   WHAT IT DOES: destructor: sets the derived vtable D_1a3958, empties the list at +44 (f_060c80 over its range, then f_05da50 and freeing its head), destroys the byte-range vector at +28, runs the virtual destructor slot of every 44-byte element of the vector at +12 and frees it, then sets the base vtable D_1a3ad0. */
void f_059890(Obj9 *o) {
    o->~Obj9();
}

/* @draft 0x059a8c us f_059a8c
   Remaining difference: 424 vs 488 bytes; same missing per-call-site unwind stubs as f_059890.
   WHAT IT DOES: deleting destructor of the object destroyed by f_059890: sets the derived vtable D_1a3958, empties the list at +44 through f_059848, destroys the members (list, byte-range vector, virtual-destructor element vector), sets the base vtable D_1a3ad0 and frees the object with f_04e4b4. */
void f_059a8c(Obj9b *o) {
    o->~Obj9b();
    Obj9b::operator delete(o);
}

}  // extern "C"
}  // namespace swg8c

/* ---- swg8bd ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment swg8bd: large untagged functions of the SWG player (big_b, second half). */
namespace swg8bd {
extern "C" {
#define Q7(o, off) (*(int *)((char *)(o) + (off)))
void *f_04dfa0(unsigned); void f_04ed28(void *); void f_04e4b4(void *); void f_04eee8(void *, void *);
void f_05daa4(void *, void *);
int f_15c0f0(int, int); int f_15c07c(int, int, void *);
void f_05a3e8(void *, void *, void *); void f_05e540(void *, void *, void *);
void f_05f64c(void *, void *, void *); int f_05df80(void *, void *);
unsigned sceKernelCpuSuspendIntr(void); void sceKernelCpuResumeIntr(unsigned);
extern int D_1d2d7c[];
struct Em7 { ~Em7() {} };
struct Rc7 { int w[4]; };
/* the virtual interface of the movie-clip / character objects (slot numbers are retail vtable slots) */
struct Str7 {
  char *p;
  ~Str7() {
    Em7 g; char *s0 = p; char *s2 = s0 - 12;
    unsigned intr = sceKernelCpuSuspendIntr();
    volatile int *c = (volatile int *)(s0 - 4);
    int s1 = *c; *c += -1;
    sceKernelCpuResumeIntr(intr);
    if (s1 <= 0) f_04eee8(s2, &g);
  }
};
struct Vo;
struct Hd7 { Vo *p; int *c; ~Hd7() { f_04ed28(this); } };
struct Hr {
  Vo *p; int *c;
  Hr(Vo *a, int *b) { p = a; c = b; }
  Hr(const Hr &o) { p = o.p; c = o.c; if (c) ++*c; }
  ~Hr() { f_04ed28(this); }
};
struct Hu { Vo *p; int *c; ~Hu() { f_04ed28(this); } };
struct Vo {
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual void s3();
  virtual void s4();
  virtual void s5();
  virtual int s6();
  virtual char *s7();
  virtual void s8();
  virtual int s9();
  virtual Vo *s10();
  virtual void *s11();
  virtual void s12(void *);
  virtual Hr s13(void *);
  virtual void s14(void *, void *);
  virtual void s15();
  virtual void s16(void *);
  virtual void s17();
  virtual void s18();
  virtual void s19();
  virtual Rc7 s20(void *);
  virtual Str7 s21();
  virtual int s22();
  virtual int s23();
  virtual double s24();
  virtual void s25();
  virtual void s26();
  virtual void s27();
  virtual void s28();
  virtual void s29();
  virtual void s30();
  virtual void s31();
  virtual void s32();
  virtual void s33();
  virtual void s34();
  virtual void s35();
  virtual void s36();
  virtual void s37();
  virtual int s38(void *);
  virtual void s39();
  virtual void s40();
  virtual int *s41();
  virtual void s42(void *);
  virtual Hr s43(int);
  virtual void s44();
  virtual int s45(void *, void *, void *);
};
static inline void grab7(Hd7 &h, char *q, void *out) {
  int a = Q7(q, 4);
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  if (h.c) ++*h.c;
  int b = *(int *)(a + 4);
  f_05f64c(out, q, &b);
}

void *f_154448(void *, void *, void *, int); void *f_15fb50(void *, int);
extern char D_1a4900[]; extern char D_1a493c[];

/* @draft 0x051df8 us f_051df8
   WHAT IT DOES: takes a counted handle two links down the chain at +328, casts its object with f_154448 (tags D_1a4900/D_1a493c) and, if that succeeds, passes virtual slot 9 of the result to f_15fb50 with a flag of 1; then releases the handle.
   Remaining difference: retail emits the cast-success call out of line (bnezl, jump back); ours inline, and the landing pad ends in _Unwind_Resume (27 of 53 words). */
void f_051df8(char *self) {
  Hd7 h; int buf[4]; int out[4]; int b;
  char *q = self + 328;
  int a = Q7(q, 4);
  buf[0] = a;
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  buf[0] = (int)v;
  if (h.c) ++*h.c;
  buf[0] = a;
  int t = Q7(a, 4);
  buf[0] = t;
  b = t;
  f_05f64c(out, q, &b);
  if (!h.p) return;
  Vo *r = (Vo *)f_154448(h.p, D_1a4900, D_1a493c, 0);
  if (!r) return;
  int x = r->s9();
  f_15fb50((void *)x, 1);
}
void f_05dd24(void *, void *, void *);
struct Ia { char *n; int pad[3]; };
struct Ib { char *n; int pad[7]; };
/* @draft 0x04f248 us f_04f248
   WHAT IT DOES: asks the object (virtual slot 13) for a counted handle for the key; if it is non-null returns a copy. Otherwise looks the key up in the map at +24; when the entry is missing or its payload state is 2 it returns an empty handle, else stores the third argument at +44, clears +48 and returns the result of virtual slot 43 with 0.
   Remaining difference: saved-register assignment (22 of 69 words). */
Hr f_04f248(Vo *self, int unused, int val, void *key) {
  Hr t = self->s13(key);
  if (t.p) return Hr(t);
  Ia it; Ib end;
  char *m = (char *)self + 24;
  f_05dd24(&it, m, key);
  end.n = *(char **)(m + 4);
  if (it.n != end.n) {
    char *nd = *(char **)(it.n + 32);
    if ((*(int *)(nd + 4) ^ 2) != 0) {
      Q7(self, 44) = val; Q7(self, 48) = 0;
      return self->s43(0);
    }
  }
  return Hr(0, 0);
}
void f_05a61c(void *, void *, void *);
/* @draft 0x0524dc us f_0524dc
   WHAT IT DOES: takes the counted handle two links down the chain at +328, asks its object (virtual slot 20) for a record, looks the record up with f_05a61c, and if the found object (virtual slot 9) yields a non-null value passes it to virtual slot 10 of this object; returns that value.
   Remaining difference: retail places the buffer b at sp+48 before the two temporaries, ours after (34 of 70 words). */
int f_0524dc(Vo *self) {
  Hd7 h; int buf[4]; int out[4]; int b[4];
  char *q = (char *)self + 328;
  int a = Q7(q, 4);
  buf[0] = a;
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  buf[0] = (int)v;
  if (h.c) ++*h.c;
  buf[0] = a;
  int t = Q7(a, 4);
  buf[0] = t;
  b[0] = t;
  f_05f64c(out, q, b);
  Hu r2;
  Rc7 rec = h.p->s20(self);
  f_05a61c(&r2, self, &rec);
  int x = r2.p->s9();
  if (x) ((Vo *)self)->s10();
  return x;
}
void f_05e394(void *, void *, void *, void *);
/* @draft 0x052f84 us f_052f84
   WHAT IT DOES: takes the counted handle two links down the chain at +328, asks its object (virtual slot 20) for a record, looks the record up with f_05a61c, and passes the chain, the +328 output buffer and the found handle to f_05e394.
   Remaining difference: stack slot order and saved-register allocation (52 of 73 words). */
void f_052f84(Vo *self) {
  Hd7 h; int buf[4]; int out[4]; int b;
  char *q = (char *)self + 328;
  int a = Q7(q, 4);
  buf[0] = a;
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  buf[0] = (int)v;
  if (h.c) ++*h.c;
  buf[0] = a;
  int t = Q7(a, 4);
  buf[0] = t;
  b = t;
  f_05f64c(out, q, &b);
  Hu r2;
  Rc7 rec = h.p->s20(self);
  f_05a61c(&r2, self, &rec);
  out[0] = Q7(q, 4);
  f_05e394(&b, q, out, &r2);
}
extern char D_1a4480[];
void f_05cbd4(void *);
struct Ob12 {
  void *vt; int x;
  static void *operator new(unsigned n) { unsigned *p = (unsigned *)f_04dfa0(n + 4); *p = n + 4; return p + 1; }
  static void operator delete(void *p) { f_04e4b4((char *)p - 4); }
  Ob12() { Em7 e; vt = D_1a4480; x = 0; }
};
struct Pq { void *p; int *cnt;
  Pq(void *o) { p = o; cnt = 0; if (o) { cnt = (int *)f_04dfa0(4); *cnt = 1; } }
  ~Pq() { f_04ed28(this); } };
struct Ik { int *n; Ik() {} Ik(const Ik &o) { n = o.n; } };
/* @draft 0x04fc40 us f_04fc40
   WHAT IT DOES: creates a new 8-byte object (vtable D_1a4480) in a counted handle, calls f_05e394 with it and the argument, then walks the circular list headed at the node in field +12 of this object and calls f_05e394 again for the value of every node.
   Remaining difference: retail frame is 144 bytes with the two word buffers at sp+48/64 (32 bytes of unexplained slots below), ours 128 (56 of 74 words). */
void f_04fc40(char *self, char *arg) {
  Pq pr(new Ob12);
  int b[4]; int out[4];
  out[0] = Q7(arg, 4);
  f_05e394(b, arg, out, &pr);
  Ik it, end;
  int *head = *(int **)(self + 12);
  it.n = (int *)head[2]; end.n = head;
  while (it.n != end.n) {
    b[0] = Q7(arg, 4);
    f_05e394(out, arg, b, it.n + 8);
    f_05cbd4(&it);
  }
}
extern char D_1a3b70[];
/* @draft 0x0525f4 us f_0525f4
   WHAT IT DOES: takes the counted handle two links down the chain at +328, builds the +328 output buffer with f_05f64c, and casts the handle's object with f_154448 (tags D_1a4900/D_1a3b70); passes the sub-object at +340 to f_05e394 together with the handle when the cast works, or with the address of the node at +8 of the +340 chain otherwise; then returns the result of virtual slot 9 of the handle's object.
   Remaining difference: block layout (retail puts the cast-succeeded call out of line) and saved-register assignment (71 of 75 words). */
int f_0525f4(Vo *self) {
  Hd7 h; int buf[4]; int out[4]; int b;
  char *q = (char *)self + 328;
  int a = Q7(q, 4);
  buf[0] = a;
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  buf[0] = (int)v;
  if (h.c) ++*h.c;
  buf[0] = a;
  int t = Q7(a, 4);
  buf[0] = t;
  b = t;
  f_05f64c(out, q, &b);
  void *c = 0;
  if (h.p) c = f_154448(h.p, D_1a4900, D_1a3b70, 0);
  char *q2 = (char *)self + 340;
  if (!c) {
    int w = Q7(q2, 4);
    b = w;
    int w1 = Q7(w, 4);
    out[0] = w;
    b = w1;
    f_05e394(&b, q2, out, (char *)w1 + 8);
  } else {
    out[0] = Q7(q2, 4);
    f_05e394(&b, q2, out, &h);
  }
  return h.p->s9();
}
void f_04eda0(void *);
struct Rz {
  int *p; int *c; int pad[6];
  Rz() { p = 0; c = 0; }
  ~Rz() { f_04ed28(this); }
  Rz &operator=(const Rz &o) {
    if (this != &o) { f_04ed28(this); c = o.c; p = o.p; if (c) ++*c; }
    return *this;
  }
};
/* @implements 0x050cc4 us f_050cc4
   WHAT IT DOES: resets the object: replaces the counted handle at +272 with an empty one, clears the container at +328 (f_04eda0), empties the four handles at +296 + 8*i, clears the container at +340 and empties the handle at +288. */
void f_050cc4(char *self) {
  { Rz t; *(Rz *)(self + 272) = t; }
  f_04eda0(self + 328);
  for (int i = 0; i < 4; i++) { Rz t; *(Rz *)(self + 296 + i * 8) = t; }
  f_04eda0(self + 340);
  { Rz t; *(Rz *)(self + 288) = t; }
}
void f_04ee68(void *, void *); void f_04e8d8(void *);
extern char D_1a3698[]; extern char D_1a35d0[];
struct Node1 { Node1 *l; Node1 *p; Node1 *r; Node1 *q; };
struct Lst1 { int pad; Node1 *head; int size;
  void clear() { if (size) { f_04ee68(this, head->p); size = 0; head->r = head; head->p = 0; head->q = head; } }
  ~Lst1() { Node1 *h = head; f_04e4b4(h); } };
struct BaseT { void *vt; int w[5]; ~BaseT() { f_04e8d8(this); } };
struct Tr1 : BaseT { Lst1 m; ~Tr1() { vt = D_1a3698; m.clear(); } };
struct Tr3 : Tr1 { int pad3[5]; char *buf; static void operator delete(void *p) { f_04e4b4((char *)p - 4); } ~Tr3() { vt = D_1a35d0; if (buf) f_04e4b4(buf - 4); } };
/* @draft 0x04ef20 us f_04ef20
   WHAT IT DOES: destructor of a tree container with an owned buffer at +56: sets the derived vtable, frees the buffer (pointer minus its 4-byte header) if present, then runs the tree container destructor (empty the tree at +24, free its header node, base destructor).
   Remaining difference: landing-pad registers and the trailing cleanup chain (25 of 84 words; 304 vs 336 bytes). */
struct Tmp16 { int w[4]; ~Tmp16() {} };
void f_04ef20(Tr3 *o) { Tmp16 g; o->~Tr3(); }
/* @draft 0x052dfc us f_052dfc
   WHAT IT DOES: takes the counted handle two links down the chain at +328 twice (the second time in a second counted slot), builds the output buffers with f_05e394/f_05f64c over the +328 sub-object, and calls f_05e394 on it once with each handle.
   Remaining difference: register allocation and the order of the stack stores (53 of 85 words). */
void f_052dfc(char *self) {
  Hd7 h; int x16[4]; int out[4]; int x48[4]; Hd7 h2;
  char *q = self + 328;
  int a = Q7(q, 4);
  x16[0] = a;
  int *v = *(int **)(a + 4);
  h.p = (Vo *)v[2]; h.c = (int *)v[3];
  x16[0] = (int)v;
  if (h.c) ++*h.c;
  x16[0] = a;
  int t = Q7(a, 4);
  x16[0] = t;
  x48[0] = t;
  f_05f64c(out, q, x48);
  int a2 = Q7(q, 4);
  x48[0] = a2;
  int *v2 = *(int **)(a2 + 4);
  x48[0] = (int)v2;
  h2.p = (Vo *)v2[2]; h2.c = (int *)v2[3];
  if (h2.c) ++*h2.c;
  x48[0] = a2;
  int t2 = Q7(a2, 4);
  x16[0] = t2;
  x48[0] = t2;
  f_05f64c(out, q, x16);
  out[0] = Q7(q, 4);
  f_05e394(x48, q, out, &h);
  out[0] = Q7(q, 4);
  f_05e394(x48, q, out, &h2);
}
/* @draft 0x04f070 us f_04f070
   WHAT IT DOES: deleting destructor of the tree container with an owned buffer: runs the destructor of f_04ef20 and then frees the object (pointer minus its 4-byte header).
   Remaining difference: same landing-pad chain as f_04ef20 (32 of 87 words). */
void f_04f070(Tr3 *o) { Tmp16 g; o->~Tr3(); Tr3::operator delete(o); }
int f_05aaf8(void *, void *, void *, void *);
struct Hq { Vo *p; int *c; Hq(const Hd7 &o) { c = o.c; p = o.p; if (c) ++*c; } ~Hq() { f_04ed28(this); } };
struct Rq { int *p; int *c; int pad[6]; Rq() { p = 0; c = 0; } ~Rq() { f_04ed28(this); } };
/* @draft 0x055a98 us f_055a98
   WHAT IT DOES: takes the counted handle two links down the chain at +328, builds the +328 output buffer with f_05f64c, then calls f_05aaf8 with this object, the argument, a counted copy of the handle and an empty handle, returning its result.
   Remaining difference: 2 words (the spill of the chain pointer to sp+16 is scheduled after the next load in ours). */
int f_055a98(char *self, void *arg) {
  Hd7 h; int buf[4]; int out[4]; int b[4];
  char *q = self + 328;
  int a = Q7(q, 4);
  buf[0] = a;
  int *v = *(int **)(a + 4);
  h.c = (int *)v[3]; h.p = (Vo *)v[2];
  buf[0] = (int)v;
  if (h.c) ++*h.c;
  buf[0] = a;
  int t = Q7(a, 4);
  buf[0] = t;
  b[0] = t;
  f_05f64c(out, q, b);
  Hq cp(h);
  Rq e;
  return f_05aaf8(self, arg, &cp, &e);
}
}
}

/* ---- swg9a ---- */
#undef W
#undef B
#undef FLD
#undef DBL
/* TU 117 fragment by worker swg9a. */
namespace swg9a {
template <class T> static inline T &Y(void *p, int o) { return *(T *)((char *)p + o); }
extern "C" {
void f_023198(int, int);
void *f_021b38(int);
void f_1181c0(unsigned);
void f_116dfc(int, int, int, int, void *);
extern float D_1a2af0;
static inline unsigned cvp(float f) { return (unsigned)(f * D_1a2af0); }
void f_046620(void *, int);
void f_04637c(void *, void *);
void f_04639c(void *);
int f_07dacc(void *, int, int, int);
void f_0463a4(float, float, float, float, void *, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
#define MAX(a, b) ((a) > (b) ? (a) : (b))
void *memcpy(void *, const void *, unsigned);
void *f_02347c(int);
int f_0e7114(int, void *);
int f_0e71d4(int, void *);
int f_0cb3f4(int, int, void *, int);
extern int D_1d2d74, D_1d2d78;
extern float D_1a2b14;
extern float D_1a2b18;
extern float D_1a2b20, D_1a2b24, D_1a2b28, D_1a2b2c;
static inline unsigned cvq(float f) { return (unsigned)(f * D_1a2b2c); }
extern char D_1a2c1c[]; /* "NotSWGFILE" */
extern char D_1a3b18[], D_1a3b64[];
extern int D_1a3958, D_1a3a40, D_1a3a10, D_1a39d0, D_1a3810, D_1a3760, D_1a3698, D_1a35d0, D_24100c;
void f_126f1c(char *);
void *f_04dfa0(unsigned);
void f_04b724(void *);
int f_15a754(void *);
void f_04e694(void *, void *);
void f_15b170(void *, void *, void *, void *, void *, void *, void *, int, int);
void f_15ba88(void *);
void f_15ba34(void *, void *);
void f_04e1a0(void *);
void *f_154448(void *, void *, void *, int);
void f_04ea4c(void *, void *, void *);
void f_04e74c(void *, int);

/* @draft 0x0455e8 us f_0455e8
   WHAT IT DOES: unless the last argument is -1, packs four float components into one 32-bit color, calls f_023198 with the last argument, builds a 40-byte record of twenty 16-bit values stored as low/high byte pairs, passes the color to f_1181c0, submits the record with f_116dfc and returns 0. */
int f_0455e8(float r, float g, float b, float a, int x0, unsigned short p1, unsigned short p2, unsigned short p3, unsigned short p4, unsigned short p5, unsigned short p6, unsigned short p7, unsigned short p8, unsigned short p9, unsigned short p10, unsigned short p11, unsigned short p12, unsigned short p13, unsigned short p14, unsigned short p15, unsigned short p16, unsigned short p17, unsigned short p18, unsigned short p19, unsigned short p20, int idx) {
    if (idx != -1) {
        unsigned c = cvp(r) & 0xff;
        c |= (cvp(g) & 0xff) << 8;
        c |= (cvp(b) & 0xff) << 16;
        c |= cvp(a) << 24;
        f_023198(idx, 0);
        char *o = (char *)f_021b38(40);
#define PR(p, lo, hi) Y<unsigned char>(o, lo) = (p); Y<unsigned char>(o, hi) = (p) >> 8;
        PR(p1, 4, 5) PR(p2, 6, 7) PR(p3, 8, 9) PR(p4, 0, 1) PR(p5, 2, 3) PR(p6, 14, 15) PR(p7, 16, 17)
        PR(p8, 18, 19) PR(p9, 10, 11) PR(p10, 12, 13) PR(p11, 34, 35) PR(p12, 36, 37) PR(p13, 38, 39)
        PR(p14, 30, 31) PR(p15, 32, 33) PR(p16, 24, 25) PR(p17, 26, 27) PR(p18, 28, 29) PR(p19, 20, 21) PR(p20, 22, 23)
#undef PR
        f_1181c0(c);
        f_116dfc(4, 0x800102, 4, 0, o);
    }
    return 0;
}


/* @draft 0x045f8c us f_045f8c
   Remaining difference: retail advances the list pointer after every word; the draft lets the compiler merge the increments.
   WHAT IT DOES: writes GE display-list words for one drawable entry: lets f_0e7114 or f_0e71d4 emit its own commands for entry types 1 and 2, emits the blend-state words when the cached mode changes, selects texture/palette words through f_02347c and f_0cb3f4 when the cached texture differs, then copies the 80-byte vertex block to a new buffer and emits its vertex-address words and either a per-index or a ranged draw command list; returns the advanced list pointer. */
int f_045f8c(int *st, char *e, int *tbl, int dl) {
    int *p;
    if (e[164] == 1) dl = f_0e7114(dl, e);
    else if (e[164] == 2) dl = f_0e71d4(dl, e);
    p = (int *)dl;
    if (st[1] != *(int *)(e + 168)) {
        int m = *(int *)(e + 168);
        if (m == 1) {
            *p++ = 0xdf0000a2; *p++ = 0xe0000000; *p++ = 0xe10000ff;
        } else if (m == 2) {
            *p++ = 0xdf0002a2; *p++ = 0xe0000000; *p++ = 0xe10000ff;
        } else {
            *p++ = 0xdf000032; *p++ = 0xe0000000; *p++ = 0xe1000000;
        }
        st[1] = *(int *)(e + 168);
    }
    if (st[0] != *(int *)(e + 124)) {
        int *c = *(int **)(e + 124);
        int *d = c;
        if (*(int *)(e + 132)) d = (int *)f_02347c(tbl[*(int *)(e + 132)]);
        if (*(int *)(e + 156)) p = (int *)f_0cb3f4(*(int *)(e + 156), *(int *)(e + 160), d, (int)p);
        unsigned w = d[55];
        if (w) { *p++ = ((w >> 24) & 0xf) << 16 | 0x10000000; *p++ = (w & 0xffffff) | 0x0a000000; }
        c = *(int **)(e + 124);
        w = c[56];
        if (w) { *p++ = ((w >> 24) & 0xf) << 16 | 0x10000000; *p++ = (w & 0xffffff) | 0x0a000000; }
        st[0] = *(int *)(e + 124);
    }
    char *t = (char *)f_021b38(80);
    memcpy(t, e, 80);
    *p++ = D_1d2d78;
    *p++ = (((unsigned)t >> 24) & 0xf) << 16 | 0x10000000;
    unsigned a3 = ((unsigned)t & 0xffffff) | 0x01000000;
    if (*(unsigned char *)(e + 137)) {
        *p++ = (*(int *)(e + 140) | *(int *)(e + 144) << 10) | 0xd4000000;
        *p++ = (*(int *)(e + 148) | *(int *)(e + 152) << 10) | 0xd5000000;
        *p++ = a3;
        *p++ = D_1d2d74;
    } else {
        for (int i = *(int *)(e + 80); i < *(int *)(e + 84); i++) {
            *p++ = (i << 6) | 0xd4000000;
            *p++ = ((i << 6) + 63) | 0xd5043c00;
            *p++ = a3;
            *p++ = D_1d2d74;
        }
    }
    *p++ = 0xd4000000;
    *p++ = 0xd5043ddf;
    return (int)p;
}


/* @draft 0x046de0 us f_046de0
   WHAT IT DOES: like f_0477b0 but centres each group: for every group of 16-byte entries it sums the halfword spans (end - start), starts x at x minus half that width, and draws the entries with f_0463a4; keeps the running maximum row bottom (falling back to the previous group's when zero) and starts the next group one row below it; returns 1 on success, 0 otherwise.
   Remaining difference: volatile locals only approximate the retail stack-resident variables; the argument slots of f_0463a4 the retail leaves unwritten are passed as zero. */
int f_046de0(char *s0, int x, int y, int key, int k2, int *tbl0, float r, float g, float b, float a) {
    char *volatile s = s0; int *volatile tbl = tbl0;
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *volatile p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    volatile int mx = 0; int pmx = 0;
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    volatile int i = 0;
    if (*(int *)p > 0) {
        int off = 0;
        do {
            int w = 0;
            {
                char *e = p + off;
                for (int k = 0; k < *(int *)(p + off + 4); k++, e += 16) w += ((short *)e)[8] - ((short *)e)[6];
            }
            int x0 = x - w / 2;
            if (*(int *)(p + off + 4) > 0) {
                char *e = p + off;
                int j = 0;
                do {
                    int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
                    int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
                    j++;
                    int q = a1 / 1000;
                    if (q != cur) {
                        cur = q;
                        f_04639c(it);
                        f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
                    }
                    int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
                    int yy = ((short *)e)[5], xx = ((short *)e)[4];
                    int ex = xx + (v16 - v12) + x0;
                    int ey = yy + (r2 - r1) + y;
                    mx = MAX(mx, ey);
                    f_0463a4(r, g, b, a, it, xx + x0, yy + y, -1, v12, r1, ex, ey, -1, v16, r2, 0, xx + x0, ex, 0, 0, yy + y, ey);
                    e += 16;
                } while (j < *(int *)(p + off + 4));
            }
            if (mx == 0) mx = pmx;
            off += 6404;
            i++;
            pmx = mx;
            y = mx + 1;
        } while (i < *(int *)p);
    }
    f_04639c(it);
    return 1;
}


/* @draft 0x0477b0 us f_0477b0
   WHAT IT DOES: unless x exceeds 480, loads (or reuses the cached) clip record for the key pair through f_07dacc, advances the ring index (20 slots), then walks the record's groups of 16-byte entries, switching the lookup via f_04637c whenever the thousands digit of a halfword changes, and draws each entry with f_0463a4 using the given colour; returns 1 on success, 0 otherwise.
   Remaining difference: volatile locals only approximate the retail stack-resident variables; the three argument slots of f_0463a4 the retail leaves unwritten are passed as zero. */
int f_0477b0(char *s0, int x, int y, int key, int k2, int *tbl0, float r, float g, float b, float a) {
    char *volatile s = s0; int *volatile tbl = tbl0;
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *volatile p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    volatile int mx = 0;
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    volatile int i = 0;
    if (*(int *)p > 0) {
        int off = 0;
        do {
            if (*(int *)(p + off + 4) > 0) {
                char *e = p + off;
                int j = 0;
                do {
                    int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
                    int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
                    j++;
                    int q = a1 / 1000;
                    if (q != cur) {
                        cur = q;
                        f_04639c(it);
                        f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
                    }
                    int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
                    int yy = ((short *)e)[5], xx = ((short *)e)[4];
                    int ex = xx + (v16 - v12) + x;
                    int ey = yy + (r2 - r1) + y;
                    mx = MAX(mx, ey);
                    f_0463a4(r, g, b, a, it, xx + x, yy + y, -1, v12, r1, ex, ey, -1, v16, r2, 0, xx + x, ex, 0, 0, yy + y, ey);
                    e += 16;
                } while (j < *(int *)(p + off + 4));
            }
            off += 6404;
            i++;
            y = mx + 1;
        } while (i < *(int *)p);
    }
    f_04639c(it);
    return 1;
}


/* @draft 0x047b84 us f_047b84
   WHAT IT DOES: like f_0477b0 with an extra per-group x offset array: unless x exceeds 480, loads (or reuses the cached) clip record for the key pair through f_07dacc, advances the ring index, then draws each group's 16-byte entries with f_0463a4 shifted by x plus the group's offset, starting each next group one row below the running maximum bottom; returns 1 on success, 0 otherwise.
   Remaining difference: volatile locals only approximate the retail stack-resident variables; the argument slots of f_0463a4 the retail leaves unwritten are passed as zero. */
int f_047b84(char *s0, int x, int y, int key, int *xs, int k2, int *tbl0, float r, float g, float b, float a) {
    char *volatile s = s0; int *volatile tbl = tbl0;
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *volatile p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    volatile int mx = 0;
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    volatile int i = 0;
    if (*(int *)p > 0) {
        int off = 0;
        do {
            if (*(int *)(p + off + 4) > 0) {
                char *e = p + off;
                int j = 0;
                do {
                    int x1 = x + xs[i];
                    int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
                    int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
                    j++;
                    int q = a1 / 1000;
                    if (q != cur) {
                        cur = q;
                        f_04639c(it);
                        f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
                    }
                    int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
                    int yy = ((short *)e)[5], xx = ((short *)e)[4];
                    int ex = xx + (v16 - v12) + x1;
                    int ey = yy + (r2 - r1) + y;
                    mx = MAX(mx, ey);
                    f_0463a4(r, g, b, a, it, xx + x1, yy + y, -1, v12, r1, ex, ey, -1, v16, r2, 0, xx + x1, ex, 0, 0, yy + y, ey);
                    e += 16;
                } while (j < *(int *)(p + off + 4));
            }
            off += 6404;
            i++;
            y = mx + 1;
        } while (i < *(int *)p);
    }
    f_04639c(it);
    return 1;
}


/* @draft 0x047f7c us f_047f7c
   WHAT IT DOES: scaled variant of the clip-record text drawer: unless x exceeds 480, loads (or reuses the cached) clip record, then for each group of 16-byte entries scales each entry's width by sx and height by sy, advances a running x by the scaled width plus the gap to the next entry, and draws it with f_0463a4; the next group starts one row below the running maximum bottom; returns 1 on success, 0 otherwise.
   Remaining difference: volatile locals only approximate the retail stack-resident variables; unwritten stack slots of the f_0463a4 call passed as zero. */
int f_047f7c(char *s0, int x, int y, int key, int k2, int *tbl0, float sx, float sy, float r, float g, float b, float a) {
    char *volatile s = s0; int *volatile tbl = tbl0;
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *volatile p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    int mx = 0;
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    int i = 0;
    if (*(int *)p > 0) {
        int off = 0;
        int vy = ((short *)p)[5];
        do {
            char *gb = p + off;
            int n = *(int *)(gb + 4);
            int curx = ((short *)gb)[4];
            int Y1 = vy + y;
            if (n > 0) {
                char *e = gb;
                int j = 0;
                do {
                    int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
                    int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
                    int q = a1 / 1000;
                    if (q != cur) {
                        cur = q;
                        f_04639c(it);
                        f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
                    }
                    int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
                    int dh = r2 - r1, dw = v16 - v12;
                    int X = curx + x;
                    int sh = (int)((float)dh * sy), sw = (int)((float)dw * sx);
                    int Y2 = vy + sh + y;
                    curx += sw;
                    int X2 = curx + x;
                    if (j != n - 1) curx = curx + ((short *)e)[12] - (((short *)e)[4] + dw);
                    mx = MAX(mx, Y2);
                    f_0463a4(r, g, b, a, it, X, Y1, -1, v12, r1, X2, Y2, -1, v16, r2, 0, X, X2, 0, 0, Y1, Y2);
                    j++;
                    e += 16;
                } while (j < *(int *)(gb + 4));
            }
            off += 6404;
            i++;
            y = mx + 1;
        } while (i < *(int *)p);
    }
    f_04639c(it);
    return 1;
}

/* @draft 0x048410 us f_048410
   WHAT IT DOES: like f_0477b0 but fades the alpha: each entry multiplies the running alpha by (lim - t) clamped to 0..D_1a2b14, where t grows by step per entry, before drawing it with f_0463a4; returns 1 on success, 0 otherwise.
   Remaining difference: volatile locals only approximate the retail stack-resident variables; the argument slots of f_0463a4 the retail leaves unwritten are passed as zero. */
int f_048410(char *s0, int x, int y, int key, int k2, int *tbl0, float r, float g, float b, float a, float lim, float step) {
    float t = 0;
    char *volatile s = s0; int *volatile tbl = tbl0;
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *volatile p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    int mx = 0;
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    volatile int i = 0;
    if (*(int *)p > 0) {
        int off = 0;
        do {
            if (*(int *)(p + off + 4) > 0) {
                char *e = p + off;
                int j = 0;
                do {
                    int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
                    int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
                    j++;
                    int q = a1 / 1000;
                    if (q != cur) {
                        cur = q;
                        f_04639c(it);
                        f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
                    }
                    int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
                    int yy = ((short *)e)[5], xx = ((short *)e)[4];
                    int ex = xx + (v16 - v12) + x;
                    int ey = yy + (r2 - r1) + y;
                    mx = MAX(mx, ey);
                    float f = lim - t;
                    t += step;
                    if (f < 0) f = 0;
                    if (f > D_1a2b14) f = D_1a2b14;
                    a *= f;
                    f_0463a4(r, g, b, a, it, xx + x, yy + y, -1, v12, r1, ex, ey, -1, v16, r2, 0, xx + x, ex, 0, 0, yy + y, ey);
                    e += 16;
                } while (j < *(int *)(p + off + 4));
            }
            off += 6404;
            i++;
            y = mx + 1;
        } while (i < *(int *)p);
    }
    f_04639c(it);
    return 1;
}


/* @draft 0x048838 us f_048838
   WHAT IT DOES: scaled and fading variant of the clip-record text drawer: like f_047f7c, but before drawing each entry multiplies the running alpha by (lim - t) clamped to 0..D_1a2b18, with t growing by step per entry; returns 1 on success, 0 otherwise.
   Remaining difference: volatile locals only approximate the retail stack-resident variables; unwritten stack slots of the f_0463a4 call passed as zero. */
int f_048838(char *s0, int x, int y, int key, int k2, int *tbl0, float sx, float sy, float r, float g, float b, float a, float lim, float step) {
    float t = 0;
    char *volatile s = s0; int *volatile tbl = tbl0;
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *volatile p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    int mx = 0;
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    int i = 0;
    if (*(int *)p > 0) {
        int off = 0;
        int vy = ((short *)p)[5];
        do {
            char *gb = p + off;
            int n = *(int *)(gb + 4);
            int curx = ((short *)gb)[4];
            int Y1 = vy + y;
            if (n > 0) {
                char *e = gb;
                int j = 0;
                do {
                    int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
                    int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
                    int q = a1 / 1000;
                    if (q != cur) {
                        cur = q;
                        f_04639c(it);
                        f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
                    }
                    int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
                    int dh = r2 - r1, dw = v16 - v12;
                    int X = curx + x;
                    int sh = (int)((float)dh * sy), sw = (int)((float)dw * sx);
                    int Y2 = vy + sh + y;
                    curx += sw;
                    int X2 = curx + x;
                    if (j != n - 1) curx = curx + ((short *)e)[12] - (((short *)e)[4] + dw);
                    mx = MAX(mx, Y2);
                    float f = lim - t;
                    if (f < 0) f = 0;
                    if (f > D_1a2b18) f = D_1a2b18;
                    a *= f;
                    t += step;
                    f_0463a4(r, g, b, a, it, X, Y1, -1, v12, r1, X2, Y2, -1, v16, r2, 0, X, X2, 0, 0, Y1, Y2);
                    j++;
                    e += 16;
                } while (j < *(int *)(gb + 4));
            }
            off += 6404;
            i++;
            y = mx + 1;
        } while (i < *(int *)p);
    }
    f_04639c(it);
    return 1;
}

/* @draft 0x048d1c us f_048d1c
   WHAT IT DOES: scrolling clipped text: unless x exceeds 480, loads (or reuses the cached) clip record, measures the total width of its entries plus pad, wraps the scroll float at *scroll into (-width, 0], and draws each 16-byte entry with f_0463a4 shifted by x plus the scroll, wrapping it around the width and clipping it against the window [x, x + k2) (entries wholly outside are skipped); returns 1 on success, 0 otherwise.
   Remaining difference: unwritten stack slots of the f_0463a4 call passed as zero; the retail keeps the four rectangle values in stack slots. */
int f_048d1c(char *s, int x, int y, int key, int k2, int pad, int *tbl, float *scroll, float r, float g, float b, float a) {
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    float sc = *scroll;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    int n = *(int *)(p + 4);
    int fx0 = ((short *)p)[4];
    short *last = (short *)(p + n * 16 - 16);
    int vy = last[7];
    int W = (last[4] - fx0) + (last[8] - last[6]) + pad;
    if (sc > 0) { sc -= (float)W; *scroll = sc; }
    if (sc < (float)-W) { sc += (float)W; *scroll = sc; }
    if (n > 0) {
        char *e = p;
        for (int j = 0; j < *(int *)(p + 4); j++, e += 16) {
            int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
            int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
            int q = a1 / 1000;
            if (q != cur) {
                cur = q;
                f_04639c(it);
                f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
            }
            int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
            int X = (int)((float)(((short *)e)[4] + x) + sc);
            if (X < x - (v16 - v12)) X = X + W;
            else if (x + W < X) X = X - W;
            int X2 = (v16 - v12) + X;
            int Y1 = vy + y, Y2 = (r2 - r1) + vy + y;
            if (X2 < x) continue;
            if (x + k2 < X) continue;
            if (X < x) { v12 = v12 + (x - X); X = x; }
            if (x + k2 < X2) { v16 = v16 - (X2 - x - k2); X2 = x + k2; }
            f_0463a4(r, g, b, a, it, X, Y1, -1, v12, r1, X2, Y2, -1, v16, r2, 0, X, X2, 0, 0, Y1, Y2);
        }
    }
    f_04639c(it);
    return 1;
}

/* @draft 0x049188 us f_049188
   WHAT IT DOES: scrolling clipped text: unless x exceeds 480, loads (or reuses the cached) clip record, measures the total width of its entries (the vertical origin comes from the first entry) plus pad, wraps the scroll float at *scroll into (-width, 0], and draws each 16-byte entry with f_0463a4 shifted by x plus the scroll , wrapping it around the width and clipping it against the window [L, L + k2) (entries wholly outside are skipped); returns 1 on success, 0 otherwise.
   Remaining difference: unwritten stack slots of the f_0463a4 call passed as zero; the retail keeps the four rectangle values in stack slots. */
int f_049188(char *s, int x, int y, int key, int L, int k2, int pad, int *tbl, float *scroll, float r, float g, float b, float a) {
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    float sc = *scroll;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    int n = *(int *)(p + 4);
    int fx0 = ((short *)p)[4];
    short *last = (short *)(p + n * 16 - 16);
    int vy = ((short *)p)[5];
    int W = (last[4] - fx0) + (last[8] - last[6]) + pad;
    if (sc > 0) { sc -= (float)W; *scroll = sc; }
    if (sc < (float)-W) { sc += (float)W; *scroll = sc; }
    if (n > 0) {
        char *e = p;
        for (int j = 0; j < *(int *)(p + 4); j++, e += 16) {
            int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
            int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
            int q = a1 / 1000;
            if (q != cur) {
                cur = q;
                f_04639c(it);
                f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
            }
            int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
            int X = (int)((float)(((short *)e)[4] + x) + sc);
            if (X < x - (v16 - v12)) X = X + W;
            else if (x + W < X) X = X - W;
            int X2 = (v16 - v12) + X;
            int Y1 = vy + y, Y2 = (r2 - r1) + vy + y;
            if (X2 < L) continue;
            if (L + k2 < X) continue;
            if (X < L) { v12 = v12 + (L - X); X = L; }
            if (L + k2 < X2) { v16 = v16 - (X2 - L - k2); X2 = L + k2; }
            f_0463a4(r, g, b, a, it, X, Y1, -1, v12, r1, X2, Y2, -1, v16, r2, 0, X, X2, 0, 0, Y1, Y2);
        }
    }
    f_04639c(it);
    return 1;
}

/* @draft 0x049600 us f_049600
   WHAT IT DOES: scaled scrolling clipped text: like f_048d1c but the entry widths are scaled by sx and heights by sy (the total width, positions and clip adjustments all use the scaled values; the vertical origin comes from the first entry), wrapping the scroll float at *scroll and clipping each entry against [x, x + k2) before drawing it with f_0463a4; returns 1 on success, 0 otherwise.
   Remaining difference: unwritten stack slots of the f_0463a4 call passed as zero. */
int f_049600(char *s, int x, int y, int key, int k2, int pad, int *tbl, float *scroll, float sx, float sy, float r, float g, float b, float a) {
    void *o = *(void **)s;
    int it[4];
    if (x > 480) return 0;
    int idx = *(int *)(s + 20);
    char *p = *(char **)(s + 24) + idx * 0xaf20;
    *(int *)(s + 8) = *(int *)(s + 828 + idx * 4);
    if (key != *(int *)(s + 28 + idx * 4) || *(int *)(s + 748 + idx * 4) != k2 || *(unsigned char *)(s + 908)) {
        int h = f_07dacc(o, key, (int)p, k2);
        *(int *)(s + 8) = h;
        if (h == -1) return 0;
        idx = *(int *)(s + 20);
        *(int *)(s + 828 + idx * 4) = h;
        *(int *)(s + 28 + idx * 4) = key;
        *(int *)(s + 748 + idx * 4) = k2;
    }
    *(unsigned char *)(s + 908) = 0;
    *(int *)(s + 20) = (idx + 1 < 20) ? idx + 1 : 0;
    float sc = *scroll;
    f_046620(it, -1);
    int cur = *(int *)(s + 8);
    f_04637c(it, (void *)tbl[*(int *)(s + 8)]);
    int n = *(int *)(p + 4);
    int fx0 = ((short *)p)[4];
    short *last = (short *)(p + n * 16 - 16);
    int vy = ((short *)p)[5];
    int W = (int)((float)((last[4] - fx0) + (last[8] - last[6])) * sx) + pad;
    if (sc > 0) { sc -= (float)W; *scroll = sc; }
    if (sc < (float)-W) { sc += (float)W; *scroll = sc; }
    if (n > 0) {
        char *e = p;
        for (int j = 0; j < *(int *)(p + 4); j++, e += 16) {
            int a1 = ((short *)e)[7], a2 = ((short *)e)[9];
            int v12 = ((short *)e)[6], v16 = ((short *)e)[8];
            int q = a1 / 1000;
            if (q != cur) {
                cur = q;
                f_04639c(it);
                f_04637c(it, (void *)tbl[*(int *)(s + 8) + q * 10]);
            }
            int r1 = a1 - a1 / 1000 * 1000, r2 = a2 - a2 / 1000 * 1000;
            int X = (int)((float)(((short *)e)[4] - fx0) * sx + (float)fx0) + x;
            X = (int)((float)X + sc);
            if ((float)X < (float)x - (float)(v16 - v12) * sx) X = X + W;
            else if (x + W < X) X = X - W;
            int X2 = (int)((float)(v16 - v12) * sx) + X;
            int Y1 = vy + y, Y2 = vy + (int)((float)(r2 - r1) * sy) + y;
            if (X2 < x) continue;
            if (x + k2 < X) continue;
            if (X < x) { v12 = v12 + (int)((float)(x - X) / sx); X = x; }
            if (x + k2 < X2) { v16 = v16 - (int)((float)(X2 - x - k2) / sx); X2 = x + k2; }
            f_0463a4(r, g, b, a, it, X, Y1, -1, v12, r1, X2, Y2, -1, v16, r2, 0, X, X2, 0, 0, Y1, Y2);
        }
    }
    f_04639c(it);
    return 1;
}

/* @draft 0x049fcc us f_049fcc
   WHAT IT DOES: appends a transformed textured quad to the 172-byte entry array at s+28 (count at s+32): if the array is missing it only bumps the count; otherwise it looks up the source's 12-byte rectangle record, transforms its four corners with the 2x3 matrix at m, fills the four 20-byte vertices (texture coordinates, packed colour from m[16..19], depth, positions), stores the scaled bounding-box columns, the texture handle, clears the state fields, sets the mode byte and bumps the count. */
#define EN(T, o) Y<T>(Y<char *>(s, 28) + Y<int>(s, 32) * 172, o)
void f_049fcc(char *s, char *src, float *m) {
    if (!Y<int>(s, 28)) {
        Y<int>(s, 32) += 1;
        return;
    }
    char *own = Y<char *>(s, 4);
    short *rec = (short *)(Y<char *>(own, 40) + Y<int>(src, 12) * 12);
    int hh = rec[3], ww = rec[2];
    float fa = (float)ww, fb = (float)hh;
    float x0 = m[12], x1 = fa * m[0] + m[12], x2 = fa * m[0] + fb * m[4] + m[12], x3 = fb * m[4] + m[12];
    float y0 = m[13], y1 = fa * m[1] + m[13], y2 = fa * m[1] + fb * m[5] + m[13], y3 = fb * m[5] + m[13];
    int uv[8];
    float col[4];
    uv[1] = ww; uv[2] = ww; uv[0] = 0; uv[3] = 0; uv[4] = 0; uv[5] = 0;
    uv[6] = hh; uv[7] = hh;
    col[0] = m[16]; col[1] = m[17]; col[2] = m[18]; col[3] = m[19];
    int *tex = Y<int *>(own, 240);
    EN(char, 164) = 0;
    EN(int, 156) = 0;
    EN(int, 132) = 0;
    EN(int, 124) = tex[Y<int>(src, 12)];
    EN(float, 92) = x0; EN(float, 96) = x1; EN(float, 100) = x3; EN(float, 104) = x2;
    EN(float, 8) = x0; EN(float, 28) = x1; EN(float, 48) = x3; EN(float, 68) = x2;
    EN(float, 108) = y0; EN(float, 112) = y1; EN(float, 116) = y3; EN(float, 120) = y2;
    EN(float, 12) = y0; EN(float, 32) = y1; EN(float, 52) = y3; EN(float, 72) = y2;
    float lo = x0;
    if (x1 < lo) lo = x1;
    if (x2 < lo) lo = x2;
    if (x3 < lo) lo = x3;
    EN(int, 80) = (int)(lo * D_1a2b20);
    float hi = x0;
    if (hi < x1) hi = x1;
    if (hi < x2) hi = x2;
    if (hi < x3) hi = x3;
    EN(int, 84) = (int)((hi + D_1a2b24) * D_1a2b20);
    EN(float, 76) = D_1a2b28; EN(float, 16) = D_1a2b28; EN(float, 36) = D_1a2b28; EN(float, 56) = D_1a2b28;
    EN(unsigned short, 0) = uv[0]; EN(unsigned short, 40) = uv[3]; EN(unsigned short, 20) = uv[1];
    EN(unsigned short, 2) = uv[4]; EN(unsigned short, 60) = uv[2]; EN(unsigned short, 22) = uv[5];
    EN(unsigned short, 42) = uv[7]; EN(unsigned short, 62) = uv[6];
    unsigned c = cvq(col[0]) & 0xff;
    c |= (cvq(col[1]) & 0xff) << 8;
    c |= (cvq(col[2]) & 0xff) << 16;
    c |= cvq(col[3]) << 24;
    EN(unsigned, 88) = c;
    int mi = (int)m[3];
    EN(unsigned, 4) = EN(unsigned, 88);
    EN(unsigned, 24) = EN(unsigned, 88);
    EN(unsigned, 44) = EN(unsigned, 88);
    EN(unsigned, 64) = EN(unsigned, 88);
    EN(int, 128) = mi;
    EN(char, 136) = 1;
    EN(int, 140) = 0;
    EN(char, 137) = 0;
    EN(int, 148) = 0;
    EN(int, 144) = 0;
    EN(int, 152) = 0;
    EN(int, 168) = 0;
    Y<int>(s, 32) += 1;
}
#undef EN

/* @draft 0x04b9c4 us f_04b9c4
   WHAT IT DOES: builds a player movie instance from an SWG file image: rejects a missing or invalid file (printing the NotSWGFILE message), allocates the parser state and the three always-new holder objects, creates the 332-byte movie object with f_15b170, builds a 400-byte extension record when the movie flags say so, attaches a 68-byte text-style record when the named clip is found, resolves the array of texture handles through f_02347c and stores the movie, the handle array and the extra argument into the owner; returns 1.
   Remaining difference: transcribed with plain pointer arithmetic; exception landing pads and exact register allocation not reproduced. */
int f_04b9c4(char *out, char *data, int *tex, int a3, int a4) {
    f_04b724(out);
    if (!data) return 0;
    if (!f_15a754(data)) {
        f_126f1c(D_1a2c1c);
        return 0;
    }
    int *s3 = (int *)f_04dfa0(80);
    s3[0] = (int)&D_1a3958;
    Y<int>(s3, 16) = 0; Y<int>(s3, 20) = 0; Y<int>(s3, 24) = 0;
    Y<int>(s3, 32) = 0; Y<int>(s3, 36) = 0; Y<int>(s3, 40) = 0;
    char buf[64];
    f_04e694((char *)s3 + 44, buf);
    Y<int>(out, 4) = 1;
    char *h2 = 0;
    char *p = (char *)f_04dfa0(36);
    if (p) {
        h2 = p;
        Y<int>(p, 0) = (int)&D_1a3a40;
        Y<int>(p, 24) = (int)&D_24100c;
        Y<int>(p, 28) = 0;
    }
    Y<int>(out, 8) = 1;
    char *s2 = 0;
    p = (char *)f_04dfa0(16);
    if (p) { s2 = p; Y<int>(p, 0) = (int)&D_1a3a10; }
    Y<int>(out, 12) = 1;
    Y<int>(s2, 12) = 0;
    Y<int>(s2, 8) = 0;
    char *s0 = 0;
    p = (char *)f_04dfa0(28);
    if (p) { s0 = p; Y<int>(p, 0) = (int)&D_1a39d0; }
    Y<int>(s0, 16) = 0;
    Y<int>(s0, 20) = 0;
    Y<int>(s0, 16) = Y<int>(out, 28);
    Y<int>(s0, 8) = 0; Y<int>(s0, 12) = 0; Y<int>(s0, 24) = 0;
    char *m = 0;
    p = (char *)f_04dfa0(332);
    if (p) {
        f_15b170(p, s3, data, h2, s2, 0, s0, 60, 0);
        m = p;
    }
    if (!(Y<int>(Y<char *>(m, 12), 40) & 1)) {
    } else {
        char *q = (char *)f_04dfa0(400);
        Y<int>(q, 0) = 400;
        char *r = q + 4;
        f_04e1a0(r);
        Y<int>(q, 4) = (int)&D_1a3810;
        Y<int>(r, 388) = 0;
        f_15ba34(m, r);
        Y<char>(r, 392) = 0;
    }
    char *found = 0;
    if (Y<char *>(m, 232)) found = (char *)f_154448(Y<char *>(m, 232), D_1a3b18, D_1a3b64, 0);
    if (found) {
        int own = Y<int>(out, 28);
        char *t = (char *)f_04dfa0(68);
        Y<int>(t, 0) = 68;
        char *st = t + 12, *sb = t + 4;
        Y<int>(t, 4) = (int)&D_1a3760;
        Y<int>(sb, 4) = 0;
        char *n = (char *)f_04dfa0(40);
        Y<int>(st, 4) = 0;
        Y<char *>(st, 4) = n;
        Y<int>(n, 4) = 0;
        Y<int>(sb, 0) = (int)&D_1a3698;
        Y<char *>(Y<char *>(st, 4), 8) = Y<char *>(st, 4);
        Y<int>(st, 8) = 0;
        Y<char *>(Y<char *>(st, 4), 12) = Y<char *>(st, 4);
        char b2[16], b3[16];
        Y<int>(n, 0) = 0;
        f_04ea4c(sb + 24, b3, b2);
        Y<int>(sb, 0) = (int)&D_1a35d0;
        Y<char *>(found, 388) = sb;
        f_04e74c(sb, own);
        Y<int>(sb, 56) = 0;
    }
    f_15ba88(m);
    {
        int i = 0;
        char *mm = m + 40;
        if (((Y<int>(mm, 4) - Y<int>(m, 40)) >> 2) * (int)0xaaaaaaab > 0) {
            int *q = tex;
            do {
                *q = (int)f_02347c(*q);
                i++;
                q++;
            } while (i < ((Y<int>(mm, 4) - Y<int>(m, 40)) >> 2) * (int)0xaaaaaaab);
            Y<int *>(m, 240) = tex;
        }
    }
    Y<int>(out, 52) = a4;
    Y<char *>(out, 0) = m;
    Y<int>(out, 40) = a3;
    return 1;
}
}
}
