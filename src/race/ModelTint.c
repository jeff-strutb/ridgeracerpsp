/* The model tint (retail 0x0cb358 to 0x0cb3f4, the object file after the car manager): a
   model's colour scaled by a tint level. */

#define INT(p, off) (*(unsigned int *)((char *)(p) + (off)))

/* @draft 0x0cb358 us f_0cb358
   WHAT IT DOES: Sets model m's tint (+1632) and its tinted colour (+1616): the model colour
   (+1612) itself for white (0xffffff), black for 0, else each of its three bytes scaled by the
   tint's low byte over 255.
   Remaining difference (24 words): register choice only; retail keeps the colour in v1 and
   multiplies the middle byte first (products in a0, v0, a2), then ors low | middle. */
void f_0cb358(char *m, unsigned int tint)
{
    unsigned int c, k, r;

    INT(m, 1632) = tint;
    if (tint == 0xffffff) {
        r = INT(m, 1612);
    } else {
        k = tint & 0xff;
        if (tint != 0) {
            c = INT(m, 1612);
            r = ((c & 0xff) * k / 255) | (((c >> 8) & 0xff) * k / 255 << 8) | ((c >> 16) * k / 255 << 16);
        } else {
            INT(m, 1616) = 0;
            return;
        }
    }
    INT(m, 1616) = r;
}
