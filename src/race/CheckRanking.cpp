/* The race ranking checker (retail 0x0edc98 to 0x0eee20, "Component::CCheckRanking"). It keeps
   one 28-byte standing record per car of the race (the car, its lap, its distance along the
   course, two finishing times and a finished flag), sorts the records into race order after
   every update and copies the sorted cars into a standing table. It also writes the finishing
   order and times into the race result (D_240800) and decides each car's final time when the
   leader crosses the line. */

extern "C" {
void f_00d354(void *log, int level, const char *fmt, ...);
}
extern char D_245178[];

struct Pair {
    int a;
    int b;
};

/* A car (made elsewhere); only the fields read here. */
struct CCar {
    char p0[76];
    int m76;         /* taking part in the ranking */
    int m80;         /* state flags: bit 0 finished, bit 1 the player's car */
    char p84[8];
    Pair m92;        /* copied into the race result */
    char p100[24];
    int m124;        /* finish recorded */
    char p128[2000];
    char m2128[16];  /* the course position tracker */
    float m2144;     /* distance along the lap */
    char p2148[64];
    int m2212;       /* laps done */
};

/* The car job controller (src/race/CarJobCtrl.cpp). */
struct CCarJobCtrlPSP {
    char p0[12];
    int m12;  /* the player's cars */
    int m16;  /* the other cars */
    CCar *f_03b518(int i);
    CCar *f_03b530(int i);
};

/* The race state's lap timing record. */
struct RaceLaps {
    char p0[1188];
    int m1188[298];  /* the best time per lap and sector, three sectors a lap */
    int m2380;       /* current sector */
    int m2384;
    int m2388;       /* current lap */
    float m2392[3];  /* where each sector ends */
    int m2404;       /* sectors */
};

/* The current race (made elsewhere). */
struct Race {
    char p0[36];
    int m36;  /* laps of the race */
    char p40[8];
    int m48;  /* race clock */
    char p52[148];
    RaceLaps *m200;
};
extern Race *D_2408f0;

/* The race result (see src/sequence/SingleRaceModeJob.cpp). */
struct RaceResult {
    int m0;
    int count;
    Pair car[14];
    int time[14];
};
extern RaceResult D_240800;

extern int D_27ecd8; /* lap offset added to every car's lap count */
extern int D_27ecdc; /* the ranking is by laps */

extern "C" int f_0a8d5c(void *pos, float *at, int a, int b, int c);

namespace Component {

/* One car's standing record. */
struct Entry {
    CCar *car;
    int lap;
    float dist;
    int time;   /* finishing time used by the first order */
    int time2;  /* finishing time used by the second order */
    int done;   /* finished */
    int index;  /* the car's number in the controller */

    int f_0edcf0(int lap, int time, int done, float dist);
    int f_0edd74(int lap, int time, int done, float dist);
    void f_0eddf8();
};

class CCheckRanking {
public:
    CCheckRanking();
    ~CCheckRanking();
    void InitCheckRanking(CCarJobCtrlPSP *ctrl, Pair laps, int single, float f);
    void f_0ee178();
    void f_0ee1d8(int from);
    void f_0ee3cc();
    void f_0ee584();
    void f_0ee624();
    int f_0ee66c();
    CCar *f_0ee6b8();
    void f_0ee704(int time, int time2);
    void f_0ee76c();
    void f_0ee788();
    void f_0ee7a4();
    void f_0eec50();

    Entry *m_pSortBuffers;
    int m4;
    CCar *m8;  /* the player's car */
    Pair m12;
    int m20;
    CCar **m_pStandingCarBuffer;
    CCarJobCtrlPSP *m28;
    float m32;
};

}

using namespace Component;

/* @draft 0x0edc98 us f_0edc98
   WHAT IT DOES: Compares record a with record b in the first order (by the first finishing
   time): returns nonzero when b is ahead of a.
   Remaining difference: retail keeps b in a1 and loads the lap into v0 (moved into a1 in the
   call slot); this build copies b into v0 first. Argument order and locals do not change it. */
extern "C" int f_0edc98(Entry *a, Entry *b)
{
    return a->f_0edcf0(b->lap, b->time, b->done, b->dist);
}

/* @draft 0x0edcc4 us f_0edcc4
   WHAT IT DOES: The same comparison in the second order (by the second finishing time).
   Remaining difference: the same register choice for b as 0x0edc98. */
extern "C" int f_0edcc4(Entry *a, Entry *b)
{
    return a->f_0edcf0(b->lap, b->time2, b->done, b->dist);
}

/* @implements 0x0edcf0 us f_0edcf0
   WHAT IT DOES: Returns 1 when a car with the given lap, distance, first finishing time and
   finished flag is ahead of this record: more laps wins; on equal laps two finished cars
   compare times, a finished car is ahead of a running one only when the ranking is by laps,
   and two running cars compare distance. */
int Entry::f_0edcf0(int l, int t, int f, float d)
{
    if (l < lap)
        return 1;
    if (lap < l)
        return 0;
    if (done) {
        if (f) {
            if (t < time)
                return 0;
            return time < t;
        }
        return D_27ecdc == 0;
    }
    if (f)
        return D_27ecdc != 0;
    if (d < dist)
        return 1;
    return 0;
}

/* @implements 0x0edd74 us f_0edd74
   WHAT IT DOES: The same test with the second finishing time. */
int Entry::f_0edd74(int l, int t, int f, float d)
{
    if (l < lap)
        return 1;
    if (lap < l)
        return 0;
    if (done) {
        if (f) {
            if (t < time2)
                return 0;
            return time2 < t;
        }
        return D_27ecdc == 0;
    }
    if (f)
        return D_27ecdc != 0;
    if (d < dist)
        return 1;
    return 0;
}

/* @implements 0x0eddf8 us f_0eddf8
   WHAT IT DOES: Until the car has finished, copies its distance along the lap and (when the
   ranking is by laps) its lap count plus the lap offset into the record; otherwise the lap is
   zero. */
void Entry::f_0eddf8()
{
    if (!done) {
        CCar *c = car;
        dist = c->m2144;
        if (D_27ecdc)
            lap = c->m2212 + D_27ecd8;
        else
            lap = 0;
    }
}

/* @implements 0x0ede40 us _ZN9Component13CCheckRankingC2Ev
   WHAT IT DOES: Clears the record and standing buffers (base object constructor). */
/* @implements 0x0ede54 us _ZN9Component13CCheckRankingC1Ev
   WHAT IT DOES: Clears the record and standing buffers (complete object constructor). */
CCheckRanking::CCheckRanking()
{
    m_pSortBuffers = 0;
    m4 = 0;
    m8 = 0;
    m_pStandingCarBuffer = 0;
}

/* @implements 0x0ede68 us _ZN9Component13CCheckRankingD2Ev
   WHAT IT DOES: Frees the record and standing buffers (base object destructor). */
/* @implements 0x0edec0 us _ZN9Component13CCheckRankingD1Ev
   WHAT IT DOES: Frees the record and standing buffers (complete object destructor). */
CCheckRanking::~CCheckRanking()
{
    if (m_pSortBuffers)
        delete[] m_pSortBuffers;
    if (m_pStandingCarBuffer)
        delete[] m_pStandingCarBuffer;
}

/* @draft 0x0edf18 us InitCheckRanking
   WHAT IT DOES: Builds one record per car of the controller (warning and freeing first when
   the buffers already exist) and the standing table, sets the ranking to be by laps and clears
   the race's lap counters. The first record is the player's car; in a single player race the
   other records are the controller's other cars, otherwise the second record is the player's
   second car. Every record starts unfinished with both times at three hours. Then sorts.
   Remaining difference: allocation (retail keeps this in s1, the race in s2 and the three-hour
   constant in s0, with a second copy of the constant made for the loop), and retail forms
   the loop's record address after the car lookup call. The control flow and the stores match. */
void CCheckRanking::InitCheckRanking(CCarJobCtrlPSP *ctrl, Pair laps, int single, float f)
{
    Race *race = D_2408f0;

    if (m_pSortBuffers) {
        delete[] m_pSortBuffers;
        f_00d354(D_245178, 16, "Warning(%s): %s\n", "Component::CCheckRanking::InitCheckRanking",
                 "re-create m_pSortBuffers because already exist");
    }
    if (m_pStandingCarBuffer) {
        delete[] m_pStandingCarBuffer;
        f_00d354(D_245178, 16, "Warning(%s): %s\n", "Component::CCheckRanking::InitCheckRanking",
                 "re-create m_pStandingCarBuffer because already exist");
    }
    m4 = ctrl->m12 + ctrl->m16;
    m_pSortBuffers = new Entry[m4];
    m12 = laps;
    m20 = 0;
    m_pStandingCarBuffer = new CCar *[m4];
    D_27ecdc = 1;
    race->m200->m2388 = 0;
    race->m200->m2380 = 0;
    m8 = ctrl->f_03b518(0);
    m_pSortBuffers[0].car = m8;
    m_pSortBuffers[0].done = 0;
    m_pSortBuffers[0].time = 10800000;
    m_pSortBuffers[0].time2 = 10800000;
    m_pSortBuffers[0].f_0eddf8();
    m_pSortBuffers[0].index = -1;
    if (!single) {
        for (int i = 1; i < m4; i++) {
            m_pSortBuffers[i].car = ctrl->f_03b530(i - 1);
            m_pSortBuffers[i].index = i - 1;
            m_pSortBuffers[i].done = 0;
            m_pSortBuffers[i].time = 10800000;
            m_pSortBuffers[i].time2 = 10800000;
            m_pSortBuffers[i].f_0eddf8();
        }
    } else {
        m_pSortBuffers[1].car = ctrl->f_03b518(1);
        m_pSortBuffers[1].time2 = 10800000;
        m_pSortBuffers[1].done = 0;
        m_pSortBuffers[1].time = 10800000;
        m_pSortBuffers[1].index = 0;
        m_pSortBuffers[1].f_0eddf8();
    }
    f_0ee1d8(0);
    m28 = ctrl;
    m32 = f;
}

/* @implements 0x0ee178 us f_0ee178
   WHAT IT DOES: Refreshes every record from its car. */
void CCheckRanking::f_0ee178()
{
    for (int i = 0; i < m4; i++)
        m_pSortBuffers[i].f_0eddf8();
}

/* @draft 0x0ee1d8 us f_0ee1d8
   WHAT IT DOES: Insertion-sorts the records after index from into the first order, from the
   back: each record moves down past the records it is ahead of (records of cars not taking
   part stop the move), then copies the sorted cars into the standing table.
   Remaining difference: retail keeps this in s5 and the moving record pointer in s6 (swapped
   here), and loads the distance before the guard of the inner loop. */
void CCheckRanking::f_0ee1d8(int from)
{
    Entry *e = m_pSortBuffers;
    int i, j;

    if (!e)
        return;
    for (i = m4 - 1; from < i; i--) {
        int time = e[i - 1].time;
        int time2 = e[i - 1].time2;
        int done = e[i - 1].done;
        int index = e[i - 1].index;
        CCar *car = e[i - 1].car;
        int lap = e[i - 1].lap;
        float dist = e[i - 1].dist;
        for (j = i; j < m4; j++) {
            if (!e[i].car->m76)
                break;
            if (car->m76 && !e[j].f_0edcf0(lap, time, done, dist))
                break;
            e[j - 1] = e[j];
        }
        if (j != i) {
            e[j - 1].car = car;
            e[j - 1].lap = lap;
            e[j - 1].dist = dist;
            e[j - 1].time = time;
            e[j - 1].time2 = time2;
            e[j - 1].done = done;
            e[j - 1].index = index;
        }
    }
    for (i = 0; i < m4; i++)
        m_pStandingCarBuffer[i] = e[i].car;
}

/* @draft 0x0ee3cc us f_0ee3cc
   WHAT IT DOES: The same insertion sort of all the records in the second order, without the
   standing table copy.
   Remaining difference: the order of the loads of the moved record and of two closing stores. */
void CCheckRanking::f_0ee3cc()
{
    Entry *e = m_pSortBuffers;
    int i, j;

    if (!e)
        return;
    for (i = m4 - 1; i > 0; i--) {
        CCar *car = e[i - 1].car;
        int lap = e[i - 1].lap;
        float dist = e[i - 1].dist;
        int time = e[i - 1].time;
        int time2 = e[i - 1].time2;
        int done = e[i - 1].done;
        int index = e[i - 1].index;
        for (j = i; j < m4; j++) {
            if (!e[i].car->m76)
                break;
            if (car->m76 && !e[j].f_0edd74(lap, time2, done, dist))
                break;
            e[j - 1] = e[j];
        }
        if (j != i) {
            e[j - 1].car = car;
            e[j - 1].lap = lap;
            e[j - 1].dist = dist;
            e[j - 1].time = time;
            e[j - 1].time2 = time2;
            e[j - 1].done = done;
            e[j - 1].index = index;
        }
    }
}

/* @implements 0x0ee584 us f_0ee584
   WHAT IT DOES: Sorts, then writes the finishing order into the race result: the number of
   cars, each car's result pair and its second finishing time (-1 when it has not
   finished). */
void CCheckRanking::f_0ee584()
{
    f_0ee1d8(0);
    D_240800.count = m4;
    for (int i = 0; i < m4; i++) {
        Pair p = m_pSortBuffers[i].car->m92;
        D_240800.car[i] = p;
        if (m_pSortBuffers[i].done)
            D_240800.time[i] = m_pSortBuffers[i].time2;
        else
            D_240800.time[i] = -1;
    }
}

/* @implements 0x0ee624 us f_0ee624
   WHAT IT DOES: Frees the records and clears the buffer, the count and the player's car. */
void CCheckRanking::f_0ee624()
{
    if (m_pSortBuffers)
        delete[] m_pSortBuffers;
    m_pSortBuffers = 0;
    m4 = 0;
    m8 = 0;
}

/* @implements 0x0ee66c us f_0ee66c
   WHAT IT DOES: Returns the player's car's place in the standing (0 with no records, -1 when
   it is not found). */
int CCheckRanking::f_0ee66c()
{
    if (!m_pSortBuffers)
        return 0;
    for (int i = 0; i < m4; i++)
        if (m8 == m_pSortBuffers[i].car)
            return i;
    return -1;
}

/* @implements 0x0ee6b8 us f_0ee6b8
   WHAT IT DOES: Returns the first car in the standing flagged as the player's (state bit
   1), or 0. */
CCar *CCheckRanking::f_0ee6b8()
{
    if (!m_pSortBuffers)
        return 0;
    for (int i = 0; i < m4; i++) {
        CCar *c = m_pSortBuffers[i].car;
        if (c->m80 & 2)
            return c;
    }
    return 0;
}

/* @implements 0x0ee704 us f_0ee704
   WHAT IT DOES: Marks the player's car's record finished with the two given times and a
   zero distance. */
void CCheckRanking::f_0ee704(int t, int t2)
{
    int i = f_0ee66c();
    if (i >= 0) {
        m_pSortBuffers[i].time2 = t2;
        m_pSortBuffers[i].done = 1;
        m_pSortBuffers[i].time = t;
        m_pSortBuffers[i].dist = 0;
    }
}

/* @implements 0x0ee76c us f_0ee76c
   WHAT IT DOES: Runs the race's ranking step (0x0ee7a4). */
void CCheckRanking::f_0ee76c()
{
    f_0ee7a4();
}

/* @implements 0x0ee788 us f_0ee788
   WHAT IT DOES: Runs the time attack ranking step (0x0eec50). */
void CCheckRanking::f_0ee788()
{
    f_0eec50();
}

/* @draft 0x0ee7a4 us f_0ee7a4
   WHAT IT DOES: The race ranking step. Refreshes the records and sorts the cars after the
   leading cars whose finish is already recorded. Once a car has finished, every unfinished
   car still running is given its finishing time (the race clock plus the time the position
   tracker says it needs to reach the line) when it is on the last lap. Before that, it
   watches the leader: while the race is short of the last sector of a lap, it takes the
   smallest time any running car needs to reach the current sector's end (stopping at a car
   already past it) and, when one is close (under 51), records the clock plus that time as
   the sector's best time and moves to the next sector; at the last sector of a lap other
   than the last it does the same for the line and moves to the next lap; on the last lap it
   gives every car on that lap reaching the line its finishing time, recording the first as
   the race's best and marking the ranking finished.
   Remaining difference: the frame and allocation (the same remainder hoisting as 0x0eec50),
   not yet compared block by block. */
void CCheckRanking::f_0ee7a4()
{
    Race *race = D_2408f0;
    int best = 51;
    RaceLaps *g = race->m200;
    int clock = race->m48;
    int sectors = g->m2404;
    int lap = g->m2388;
    int sector = g->m2380;
    int k = 0;
    int i;

    f_0ee178();
    if (m_pSortBuffers[0].car->m124 == 1) {
        do
            k++;
        while (m_pSortBuffers[k].car->m124 == 1);
    }
    f_0ee1d8(k);
    if (k) {
        for (i = k; i < m4; i++) {
            if (m_pSortBuffers[i].done)
                continue;
            CCar *c = m_pSortBuffers[i].car;
            if (c->m80 & 1)
                continue;
            float at = 0;
            int t = clock + f_0a8d5c(c->m2128, &at, 50, 3, clock % 3);
            if (m_pSortBuffers[i].lap == race->m36) {
                m_pSortBuffers[i].time2 = t;
                m_pSortBuffers[i].done = 1;
                m_pSortBuffers[i].time = t;
                m_pSortBuffers[i].dist = 0;
                m_pSortBuffers[i].car->m124 = 1;
            }
        }
        return;
    }
    if (sector != sectors - 1) {
        float end = race->m200->m2392[sector];
        for (i = 0; i < m4; i++) {
            CCar *c = m_pSortBuffers[i].car;
            if (c->m80 & 1)
                continue;
            float at = end;
            int r = f_0a8d5c(c->m2128, &at, 50, 3, clock % 3);
            m_pSortBuffers[i].time = r;
            if (r < -2)
                break;
            if (r < best)
                best = r;
        }
        if (best < 51) {
            g = race->m200;
            g->m1188[lap * 3 + sector] = clock + best;
            g->m2380++;
        }
        return;
    }
    if (lap != race->m36 - 1) {
        for (i = 0; i < m4; i++) {
            CCar *c = m_pSortBuffers[i].car;
            if (c->m80 & 1)
                continue;
            float at = 0;
            int r = f_0a8d5c(c->m2128, &at, 50, 3, clock % 3);
            m_pSortBuffers[i].time = r;
            if (r < -2)
                break;
            if (r < best)
                best = r;
        }
        if (best < 51) {
            g = race->m200;
            g->m1188[lap * 3 + sector] = clock + best;
            g->m2388++;
            g->m2380 = 0;
        }
        return;
    }
    for (i = 0; i < m4; i++) {
        CCar *c = m_pSortBuffers[i].car;
        float at = 0;
        int r = f_0a8d5c(c->m2128, &at, 50, 3, clock % 3);
        m_pSortBuffers[i].time = r;
        if (r < -2)
            continue;
        if (m_pSortBuffers[i].lap != race->m36)
            continue;
        if (!(m_pSortBuffers[i].car->m80 & 1)) {
            int t = clock + r;
            if (r < best) {
                g = race->m200;
                best = r;
                g->m1188[lap * 3 + sector] = t;
                g->m2380 = 0;
                g->m2388 = race->m36;
            }
            m_pSortBuffers[i].time2 = t;
            m_pSortBuffers[i].done = 1;
            m_pSortBuffers[i].time = t;
            m_pSortBuffers[i].dist = 0;
            m_pSortBuffers[i].car->m124 = 1;
            m20 = 1;
        }
    }
}

/* @draft 0x0eec50 us f_0eec50
   WHAT IT DOES: The time attack ranking step: refreshes the records, sorts the cars after the
   leading cars whose finish is already recorded, and gives every unfinished running car on
   the last lap its finishing time (the race clock plus the time the position tracker says it
   needs to reach the line), recording the finish on the car.
   Remaining difference: retail hoists only the multiply and sign of clock / 3 out of the loop
   and computes the remainder straight into the fifth argument register each pass (one more
   saved register, a 64-byte frame); this build hoists the whole quotient. */
void CCheckRanking::f_0eec50()
{
    Race *race = D_2408f0;
    int clock = race->m48;
    int k = 0;
    int i;

    f_0ee178();
    int n = m4;
    if (n > 0 && m_pSortBuffers[0].car->m124 == 1) {
        do
            k++;
        while (k < n && m_pSortBuffers[k].car->m124 == 1);
    }
    f_0ee1d8(k);
    for (i = k; i < m4; i++) {
        if (m_pSortBuffers[i].done)
            continue;
        CCar *c = m_pSortBuffers[i].car;
        if (c->m80 & 1)
            continue;
        float at = 0;
        int t = clock + f_0a8d5c(c->m2128, &at, 50, 3, clock % 3);
        if (m_pSortBuffers[i].lap == race->m36) {
            m_pSortBuffers[i].time2 = t;
            m_pSortBuffers[i].done = 1;
            m_pSortBuffers[i].time = t;
            m_pSortBuffers[i].dist = 0;
            m_pSortBuffers[i].car->m124 = 1;
        }
    }
}

/* @implements 0x0eede0 us f_0eede0
   WHAT IT DOES: Converts a sector distance into a time: zero when count is not positive,
   otherwise x * 10800 * n / count * 1.024. */
extern "C" float f_0eede0(int count, int n, float x)
{
    if (count <= 0)
        return 0;
    return x * 10800.0f * n / count * 1.024f;
}
