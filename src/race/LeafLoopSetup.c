/* The looping leaf-blow sound's setup (retail 0x0ec254 to 0x0ec2cc). The object file holds
   the reset of a global's three words (the bss block at 0x27eca4), the one-line caller of
   that reset with the fixed arguments, the two empty start and stop hooks of the leaves, and the
   loop state's init that the event's first frame runs. The loop state is the 'snd' field of the
   shared object (EventJob.cpp, CEvent33). */

struct LeafLoop {
    int m0;
    unsigned char m4;
    char m5[3];
    char m8[12];
    char m20[12];
    unsigned char m32;
    unsigned char m33;
    unsigned char m34;
    unsigned char m35;
    unsigned char m36;
};

/* Three words in .bss at 0x27eca4. */
struct LeafReset {
    int m0;
    int m4;
    int m8;
};
extern struct LeafReset D_27eca4;

/* @implements 0x0ec254 us f_0ec254
   WHAT IT DOES: When a is 1 and b is 0xffff, clears the three words of the block at 0x27eca4
   (retail stores the third before the second). */
void f_0ec254(int a, int b)
{
    int ok = (b == 0xffff) & (a == 1);
    if (ok) {
        D_27eca4.m0 = 0;
        D_27eca4.m4 = 0;
        D_27eca4.m8 = 0;
    }
}

/* @implements 0x0ec288 us f_0ec288
   WHAT IT DOES: Calls f_0ec254 with a = 1 and b = 0xffff. */
void f_0ec288(void)
{
    f_0ec254(1, 0xffff);
}

/* @implements 0x0ec2a8 us f_0ec2a8
   WHAT IT DOES: Nothing (the leaves' start hook). */
void f_0ec2a8(struct LeafLoop *s)
{
}

/* @implements 0x0ec2b0 us f_0ec2b0
   WHAT IT DOES: Nothing (the leaves' stop hook). */
void f_0ec2b0(struct LeafLoop *s)
{
}

/* @implements 0x0ec2b8 us f_0ec2b8
   WHAT IT DOES: Starts the loop: clears its frame counter (+0), copies the byte at +4 into
   the threshold byte (+36) and clears the byte at +35. */
void f_0ec2b8(struct LeafLoop *s)
{
    unsigned char r = s->m4;
    s->m35 = 0;
    s->m36 = r;
    s->m0 = 0;
}
