/* The polygon clipping object files (retail 0x029b58 to 0x02bbc0). Course geometry is sent to
   the graphics engine as triangle strips. Strips that cross the clip planes are cut here
   before they are written into the display list: each vertex is tested against four planes
   (the rows of a plane matrix set from the view each frame) and the strips are rebuilt from
   the parts inside. The object files also keep the camera position, a view direction and a
   scale used to push distant vertices along that direction. */

/* A plane: normal and distance. */
struct Plane {
    float x, y, z, w;
};

/* The four clip planes. */
struct PlaneSet {
    Plane p[4];
};

struct Vector4 {
    float x, y, z, w;
};

extern PlaneSet D_23fb00;
extern Vector4 D_23fb80;
extern Vector4 D_23fb90;
extern float D_23fba0;

/* @implements 0x02b67c us f_02b67c
   WHAT IT DOES: Sets the four clip planes from the given plane matrix. */
void f_02b67c(const PlaneSet *m)
{
    D_23fb00.p[0] = m->p[0];
    D_23fb00.p[1] = m->p[1];
    D_23fb00.p[2] = m->p[2];
    D_23fb00.p[3] = m->p[3];
}

/* @implements 0x02b714 us f_02b714
   WHAT IT DOES: Sets the four clip planes from the given plane matrix, then moves each plane
   by the given distance along its own second axis (the fourth component becomes minus the
   second times the distance). */
void f_02b714(const PlaneSet *m, float d)
{
    D_23fb00.p[0] = m->p[0];
    D_23fb00.p[1] = m->p[1];
    D_23fb00.p[2] = m->p[2];
    D_23fb00.p[3] = m->p[3];
    D_23fb00.p[0].w = -D_23fb00.p[0].y * d;
    D_23fb00.p[1].w = -D_23fb00.p[1].y * d;
    D_23fb00.p[2].w = -D_23fb00.p[2].y * d;
    D_23fb00.p[3].w = -D_23fb00.p[3].y * d;
}

/* @implements 0x02b7e4 us f_02b7e4
   WHAT IT DOES: Returns the four clip planes. */
PlaneSet *f_02b7e4(void)
{
    return &D_23fb00;
}

/* @implements 0x02b7f0 us f_02b7f0
   WHAT IT DOES: Sets the camera position. */
void f_02b7f0(const Vector4 *v)
{
    D_23fb80 = *v;
}

/* @implements 0x02b81c us f_02b81c
   WHAT IT DOES: Sets the direction distant vertices are pushed along. */
void f_02b81c(const Vector4 *v)
{
    D_23fb90 = *v;
}

/* @implements 0x02b848 us f_02b848
   WHAT IT DOES: Sets how far distant vertices are pushed per unit of distance. */
void f_02b848(float s)
{
    D_23fba0 = s;
}

extern "C" {
void f_028b3c(void *save);
void f_028b74(const void *save);
}
void f_027e6c(Vector4 *out, const Vector4 *in, float t);

/* A strip vertex: texture coordinates and colour, then the position. */
struct StripVertex {
    int m0[3];
    float pos[3];
};

/* @draft 0x02b854 us f_02b854
   WHAT IT DOES: Copies a display list of triangle strips into a new list and a new vertex
   buffer, pushing every vertex away from the camera along the push direction by its distance
   from the camera times the push scale. The camera position used is first adjusted for the
   given mode. The source list is a header of four words, then per strip its vertex address
   (base and offset commands) and its primitive command, up to a return command. For each strip
   the new list gets base, vertex address and triangle strip commands pointing at the moved
   vertices. The ends of both outputs are returned through the last two arguments. The VFPU
   matrices the routine uses are saved and restored around it.
   Remaining difference (23 words, all register choice): the strip vertex count is allocated to
   a2 and the vertex offset word to a1 (retail the reverse), the hoisted command constants take
   t3 to t6 in another order, and the 0xff mask is scheduled after the base mask. */
void f_02b854(int mode, StripVertex *out, unsigned int *dl, const unsigned int *cmds,
              StripVertex **outEnd, unsigned int **dlEnd)
{
    char save[192];
    Vector4 cam;
    unsigned int c;

    f_028b3c(save);
    *dl++ = *cmds++;
    *dl++ = *cmds++;
    *dl++ = *cmds++;
    *dl++ = *cmds++;
    f_027e6c(&cam, &D_23fb80, (float)(1 - mode));
    __asm__ volatile(
        "lv.q C730.q, %0\n"
        "\tlv.s S720.s, %1\n"
        "\tlv.q C710.q, %2"
        : : "m"(cam), "m"(D_23fba0), "m"(D_23fb90));
    do {
        c = *cmds++;
        unsigned int lo = *cmds++;
        StripVertex *src = (StripVertex *)(((c & 0xff0000) << 8) | (lo & 0xffffff));
        unsigned int prim = *cmds++;
        int n;

        *dl++ = ((((int)out >> 24) & 0xf) << 16) | 0x10000000;
        *dl++ = ((unsigned int)out & 0xffffff) | 0x01000000;
        n = prim & 0xff;
        *dl++ = n | 0x04040000;
        do {
            if (n > 3) {
                __asm__ volatile(
                    "lv.s S000.s, 12(%0)\n\tlv.s S001.s, 16(%0)\n\tlv.s S002.s, 20(%0)\n"
                    "\tlv.s S200.s, 36(%0)\n\tlv.s S201.s, 40(%0)\n\tlv.s S202.s, 44(%0)\n"
                    "\tlv.s S400.s, 60(%0)\n\tlv.s S401.s, 64(%0)\n\tlv.s S402.s, 68(%0)\n"
                    "\tvsub.t C010.t, C000.t, C730.t\n"
                    "\tvsub.t C210.t, C200.t, C730.t\n"
                    "\tvsub.t C410.t, C400.t, C730.t\n"
                    "\tlw $8, 0(%0)\n\tlw $9, 4(%0)\n"
                    "\tvdot.t S020.s, C010.t, C010.t\n"
                    "\tlw $10, 8(%0)\n"
                    "\tvdot.t S220.s, C210.t, C210.t\n"
                    "\tvdot.t S420.s, C410.t, C410.t\n"
                    "\tsw $8, 0(%1)\n\tsw $9, 4(%1)\n"
                    "\tvsqrt.s S020.s, S020.s\n"
                    "\tsw $10, 8(%1)\n"
                    "\tvsqrt.s S220.s, S220.s\n"
                    "\tvsqrt.s S420.s, S420.s\n"
                    "\tlw $8, 24(%0)\n\tlw $9, 28(%0)\n\tlw $10, 32(%0)\n"
                    "\tvmul.s S020.s, S020.s, S720.s\n"
                    "\tvmul.s S220.s, S220.s, S720.s\n"
                    "\tvmul.s S420.s, S420.s, S720.s\n"
                    "\tsw $8, 24(%1)\n\tsw $9, 28(%1)\n\tsw $10, 32(%1)\n"
                    "\tvscl.t C100.t, C710.t, S020.s\n"
                    "\tvscl.t C300.t, C710.t, S220.s\n"
                    "\tvscl.t C500.t, C710.t, S420.s\n"
                    "\tlw $8, 48(%0)\n\tlw $9, 52(%0)\n\tlw $10, 56(%0)\n"
                    "\tvadd.t C100.t, C000.t, C100.t\n"
                    "\tvadd.t C300.t, C200.t, C300.t\n"
                    "\tvadd.t C500.t, C400.t, C500.t\n"
                    "\tsw $8, 48(%1)\n\tsw $9, 52(%1)\n\tsw $10, 56(%1)\n"
                    "\tsv.s S100.s, 12(%1)\n\tsv.s S101.s, 16(%1)\n\tsv.s S102.s, 20(%1)\n"
                    "\tsv.s S300.s, 36(%1)\n\tsv.s S301.s, 40(%1)\n\tsv.s S302.s, 44(%1)\n"
                    "\tsv.s S500.s, 60(%1)\n\tsv.s S501.s, 64(%1)\n\tsv.s S502.s, 68(%1)"
                    : : "r"(src), "r"(out) : "$8", "$9", "$10", "memory");
                n -= 3;
                out += 3;
                src += 3;
            } else if (n > 2) {
                __asm__ volatile(
                    "lv.s S000.s, 12(%0)\n\tlv.s S001.s, 16(%0)\n\tlv.s S002.s, 20(%0)\n"
                    "\tlv.s S200.s, 36(%0)\n\tlv.s S201.s, 40(%0)\n\tlv.s S202.s, 44(%0)\n"
                    "\tvsub.t C010.t, C000.t, C730.t\n"
                    "\tvsub.t C210.t, C200.t, C730.t\n"
                    "\tlw $8, 0(%0)\n\tlw $9, 4(%0)\n\tlw $10, 8(%0)\n"
                    "\tvdot.t S020.s, C010.t, C010.t\n"
                    "\tvdot.t S220.s, C210.t, C210.t\n"
                    "\tsw $8, 0(%1)\n\tsw $9, 4(%1)\n\tsw $10, 8(%1)\n"
                    "\tvsqrt.s S020.s, S020.s\n"
                    "\tvsqrt.s S220.s, S220.s\n"
                    "\tlw $8, 24(%0)\n\tlw $9, 28(%0)\n\tlw $10, 32(%0)\n"
                    "\tvmul.s S020.s, S020.s, S720.s\n"
                    "\tvmul.s S220.s, S220.s, S720.s\n"
                    "\tsw $8, 24(%1)\n\tsw $9, 28(%1)\n\tsw $10, 32(%1)\n"
                    "\tvscl.t C100.t, C710.t, S020.s\n"
                    "\tvscl.t C300.t, C710.t, S220.s\n"
                    "\tvadd.t C100.t, C000.t, C100.t\n"
                    "\tvadd.t C300.t, C200.t, C300.t\n"
                    "\tsv.s S100.s, 12(%1)\n\tsv.s S101.s, 16(%1)\n\tsv.s S102.s, 20(%1)\n"
                    "\tsv.s S300.s, 36(%1)\n\tsv.s S301.s, 40(%1)\n\tsv.s S302.s, 44(%1)"
                    : : "r"(src), "r"(out) : "$8", "$9", "$10", "memory");
                n -= 2;
                out += 2;
                src += 2;
            } else {
                __asm__ volatile(
                    "lv.s S000.s, 12(%0)\n\tlv.s S001.s, 16(%0)\n\tlv.s S002.s, 20(%0)\n"
                    "\tvsub.t C010.t, C000.t, C730.t\n"
                    "\tlw $8, 0(%0)\n\tlw $9, 4(%0)\n\tlw $10, 8(%0)\n"
                    "\tvdot.t S020.s, C010.t, C010.t\n"
                    "\tvsqrt.s S020.s, S020.s\n"
                    "\tsw $8, 0(%1)\n\tsw $9, 4(%1)\n\tsw $10, 8(%1)\n"
                    "\tvmul.s S020.s, S020.s, S720.s\n"
                    "\tvscl.t C100.t, C710.t, S020.s\n"
                    "\tvadd.t C100.t, C000.t, C100.t\n"
                    "\tsv.s S100.s, 12(%1)\n\tsv.s S101.s, 16(%1)\n\tsv.s S102.s, 20(%1)"
                    : : "r"(src), "r"(out) : "$8", "$9", "$10", "memory");
                n--;
                out++;
                src++;
            }
        } while (n != 0);
    } while ((*cmds >> 24) != 11);
    *outEnd = out;
    *dlEnd = dl;
    f_028b74(save);
}
