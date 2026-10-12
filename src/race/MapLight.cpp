/* The course lighting object file (retail 0x02c93c to 0x02db68). Reflection mapping of the
   reflective course meshes on the vector unit (each vertex gets sphere map coordinates from
   the camera position and its normal), and the light the course casts on a car: the car's
   position is looked up in two sets of shadow polygons, whose vertex colours give the light
   intensity there, and the course's light colours are blended from it into the packed
   ambient, diffuse and specular colours the car is drawn with. */

#include <math.h>

extern "C" {
int f_126f1c(const char *fmt, ...);
void f_028b3c(void *save);
void f_028b74(void *save);
void f_02db68(void *buf, int size, int x, int y, int color, const char *fmt, ...);
}

/* The vector unit code is written in assembly with the assembler's reordering off. */
#define VFPU_BEGIN ".set push\n\t.set noreorder\n\t"
#define VFPU_END "\n\t.set pop"

struct Vec4 {
    float x, y, z, w;
} __attribute__((aligned(16)));

extern "C" Vec4 *f_027e6c(Vec4 *d, const Vec4 *a, float s);

/* The camera position (x, y, z) and, in w, the reflection's horizontal turn. */
extern Vec4 D_23ffb0;
extern float D_23ffbc;

/* Constants for the reflection: 0, 0.5, 1 and 2. */
extern Vec4 D_1d1a80;

/* @implements 0x02c93c us f_02c93c
   WHAT IT DOES: Sets the reflection's horizontal turn from an angle in radians (as a fraction
   of a full turn, which moves the reflection texture sideways). */
extern "C" void f_02c93c(float angle)
{
    D_23ffbc = angle / 3.14159f * 0.5f;
}

/* @implements 0x02c960 us f_02c960
   WHAT IT DOES: Records the camera position the reflections are computed from. */
extern "C" void f_02c960(float *pos)
{
    D_23ffb0.x = pos[0];
    D_23ffb0.y = pos[1];
    D_23ffb0.z = pos[2];
}

/* A set of shadow polygons (another object file's class): loaded from course data, freed, and
   searched for the polygons under a point. */
extern "C" {
void f_0c6078(void *set, void *data);
void f_0c61b4(void *set);
int f_0c6580(void *set, void **found, int max, float x, float z);
}
struct PolySet {
    PolySet()
    {
        m0 = 0;
        m4 = 0;
        m8 = 0;
        m12 = 0;
        m16 = 0;
        m20 = 0;
    }
    ~PolySet() { f_0c61b4(this); }
    int m0, m4, m8, m12, m16, m20;
};
struct ShadowSet : PolySet {
    ~ShadowSet() { f_0c61b4(this); }
};

/* The light on the car: the two shadow polygon sets (the second holds the light intensity),
   then the colours worked out each frame. */
class MapLight {
public:
    MapLight() {}
    ShadowSet m0;
    ShadowSet m24;
    bool m48;
    bool m49;
    unsigned int m52[6];
    unsigned int m76;
    Vec4 m80;
    float m96;
    float m100;
    float m104;
    float m108;
    Vec4 m112;
    int m128;
};

/* @implements 0x02cec4 us f_02cec4
   WHAT IT DOES: Loads the course's two shadow polygon sets, when the course has them, and
   records which are present. */
extern "C" void f_02cec4(MapLight *l, void *light, void *shadow)
{
    if (*(int *)light) {
        f_0c6078(&l->m24, light);
        l->m49 = 1;
    } else {
        l->m49 = 0;
    }
    if (*(int *)shadow) {
        f_0c6078(&l->m0, shadow);
        l->m48 = 1;
    } else {
        l->m48 = 0;
    }
}

/* @implements 0x02d370 us f_02d370
   WHAT IT DOES: Packs a colour of three components (0 to 1) into GE colour bytes. */
extern "C" unsigned int f_02d370(Vec4 *c)
{
    return (int)(c->x * 255.0f) | (int)(c->y * 255.0f) << 8 | (int)(c->z * 255.0f) << 16;
}

/* @implements 0x02d3bc us f_02d3bc
   WHAT IT DOES: Packs a colour of four components (0 to 1) into GE colour bytes. */
extern "C" unsigned int f_02d3bc(Vec4 *c)
{
    return (int)(c->x * 255.0f) | (int)(c->y * 255.0f) << 8 | (int)(c->z * 255.0f) << 16 |
           (int)(c->w * 255.0f) << 24;
}

MapLight D_23ffc0;

/* @implements 0x02da28 us __static_initialization_and_destruction_0
   WHAT IT DOES: Constructs the course light at start up (empty shadow polygon sets) and frees
   its shadow polygons at exit. */
/* @implements 0x02db28 us _GLOBAL__I
   WHAT IT DOES: Runs the start up half of the above. */
/* @implements 0x02db48 us _GLOBAL__D
   WHAT IT DOES: Runs the exit half of the above. */
