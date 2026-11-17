/* The course sound emitters (retail 0x0ca584 to 0x0ca814, the object file after the engine
   sound curve): each emitter builds two 128-entry tables per sound of its database record from
   the engine curve (0x0ca1a8), and frees them again. */

/* A sound of an emitter's database record (96 bytes, after a 16-byte header). */
struct EmitterRec {
    short m0;
    char m2[6];
    short a[10];
    short b[10];
    short c[10];
    short d[10];
    char m88[5];
    char flag;
    char m94[2];
};

/* An emitter's database record: the number of sounds, then the sounds. */
struct EmitterData {
    short count;
    char m2[14];
    EmitterRec rec[1];
};

/* The two tables of one sound (52-byte stride in the emitter). */
struct EmitterCurve {
    float *lo;
    float *hi;
    char m8[44];
};

extern "C" {
float f_0ca1a8(void *ctx, int xi, short *a, short *b);
extern const float D_1ad580;    /* 127.0 */
extern const float D_1ad584;    /* 0.001 */
}

/* A sound emitter placed on the course (836 bytes). */
struct CEmitter {
    EmitterData *data;
    char m4[44];
    EmitterCurve curve[15];
    char m828[8];

    void f_0ca584(int kind, void *rec);
    void f_0ca77c();
};

/* @implements 0x0ca584 us _ZN8CEmitter8f_0ca584EiPv
   WHAT IT DOES: Takes database record rec: for each of its sounds allocates the two 128-entry
   tables and fills them from the engine curve every 10 units (the first scaled from 0..127,
   the second offset by 0.001), and clears the sound's flag byte. For kind nonzero (the map's
   own emitter) it sets the ten sounds' fixed ids and their 562 setting. */
void CEmitter::f_0ca584(int kind, void *rec)
{
    int e;
    int j;

    data = (EmitterData *)rec;
    for (e = 0; e < data->count; e++) {
        curve[e].hi = new float[128];
        curve[e].lo = new float[128];
        for (j = 0; j < 128; j++) {
            curve[e].hi[j] = f_0ca1a8(this, j * 10, data->rec[e].c, data->rec[e].d) / D_1ad580;
            curve[e].lo[j] = f_0ca1a8(this, j * 10, data->rec[e].a, data->rec[e].b) + D_1ad584;
        }
        data->rec[e].flag = 0;
    }
    if (kind) {
        data->rec[0].m0 = 562;
        data->rec[0].flag = 17;
        data->rec[1].m0 = 562;
        data->rec[1].flag = 18;
        data->rec[2].m0 = 562;
        data->rec[2].flag = 32;
        data->rec[3].m0 = 562;
        data->rec[3].flag = 6;
        data->rec[4].m0 = 562;
        data->rec[4].flag = 6;
        data->rec[5].m0 = 562;
        data->rec[5].flag = 1;
        data->rec[6].m0 = 562;
        data->rec[6].flag = 1;
        data->rec[7].m0 = 562;
        data->rec[7].flag = 11;
        data->rec[8].m0 = 562;
        data->rec[8].flag = 29;
        data->rec[9].m0 = 562;
        data->rec[9].flag = 30;
    }
}

/* @implements 0x0ca77c us _ZN8CEmitter8f_0ca77cEv
   WHAT IT DOES: Frees the two tables of each of the record's sounds. */
void CEmitter::f_0ca77c()
{
    int i;

    for (i = 0; i < data->count; i++) {
        if (curve[i].lo)
            delete[] curve[i].lo;
        if (curve[i].hi)
            delete[] curve[i].hi;
    }
}
