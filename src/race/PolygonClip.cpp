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
