/* The replay camera shake (retail 0x082970 to 0x082e34): a speed dependent rumble read from
   a noise table, a damped spring kicked by hits on the car and a second spring kicked by
   landings. */

extern "C" float sqrtf(float);

/* The parts of a car the shake reads. */
struct ShakeCar {
    char p0[6024];
    float speed;
    char p6028[4076];
    float landing;
    char p10108[4];
    union {
        float f;
        int i;
    } hit;
};

/* Signed noise samples. */
extern const signed char D_1aa5f4[256];

class CCamShake {
public:
    void Reset1();
    void Update1();
    void Clear3();
    void Reset3();
    void Update3();
    void Clear2();
    void Reset2();
    void Update2();
    void Init(ShakeCar *c);
    void f_082df8();
    void Update();

    unsigned char noise;
    float rumble;
    float rumbleX;
    float rumbleY;
    float hitTime;
    float hitPos;
    float hitVel;
    float landKick;
    float landTime;
    float landPos;
    float landVel;
    ShakeCar *car;
};

/* @implements 0x082970 us _ZN9CCamShake6Reset1Ev
   WHAT IT DOES: Stops the rumble. */
void CCamShake::Reset1()
{
    noise = 0;
    rumble = 0;
    rumbleX = 0;
    rumbleY = 0;
}

/* @draft 0x082984 us _ZN9CCamShake7Update1Ev
   REMAINING DIFFERENCE: the noise index registers (retail keeps the next index in a1 and
   steps it in place before the byte store) and the order of the rumble and noise stores.
   Post-increments on the member and an int index stepped in place were tried.
   WHAT IT DOES: The rumble: zero at low speed, rising to full strength 38.9 units of speed
   later, times the next two noise samples. */
void CCamShake::Update1()
{
    float t = -27.7777996f - car->speed;
    if (t < 0)
        t = 0;
    else {
        t = t / 38.8889198f;
        if (1.0f < t)
            t = 1.0f;
    }
    int i = noise;
    int j = i + 1;
    float a = D_1aa5f4[i] * 0.0608999953f;
    float b = D_1aa5f4[(unsigned char)j] * 0.0548099987f;
    rumble = t;
    noise = j + 1;
    rumbleX = a * t;
    rumbleY = b * t;
}

/* @implements 0x082a48 us _ZN9CCamShake6Clear3Ev
   WHAT IT DOES: Stops the landing spring. */
void CCamShake::Clear3()
{
    landKick = 0;
    landTime = 0;
    landVel = 0;
}

/* @implements 0x082a58 us _ZN9CCamShake6Reset3Ev
   WHAT IT DOES: Resets the landing spring. */
void CCamShake::Reset3()
{
    Clear3();
}

/* @implements 0x082a74 us _ZN9CCamShake7Update3Ev
   WHAT IT DOES: The landing spring: a landing starts 0.4 seconds of bounce with a kick
   scaled by its strength; while it runs the spring is integrated with a damping that grows
   with the square root of large velocities. */
void CCamShake::Update3()
{
    if (car->landing != 0 && landTime <= 0) {
        landPos = 0;
        landTime = 0.4f;
        landVel = (car->landing * 0.8f + 0.2f) * 50.0f;
    }
    if (0 < landTime) {
        float x;
        landTime = landTime - 1.0f / 60;
        if (landTime < 0)
            landTime = 0;
        landPos = landPos + landVel;
        landVel = landVel - landPos * 0.3f;
        x = landVel * 0.05f;
        if (x < 0)
            x = -x;
        if (1.0f < x)
            x = sqrtf(x);
        landVel = landVel - landVel * 0.22f * x;
    } else
        landPos = 0;
}

/* @implements 0x082bd4 us _ZN9CCamShake6Clear2Ev
   WHAT IT DOES: Stops the hit spring. */
void CCamShake::Clear2()
{
    hitTime = 0;
    hitVel = 0;
}

/* @implements 0x082be0 us _ZN9CCamShake6Reset2Ev
   WHAT IT DOES: Resets the hit spring. */
void CCamShake::Reset2()
{
    Clear2();
}

/* @draft 0x082bfc us _ZN9CCamShake7Update2Ev
   REMAINING DIFFERENCE: the hit test's block layout and scheduling differ throughout; retail
   rereads the hit as a float after clearing it as an int (so the kick sees zero).
   WHAT IT DOES: The hit spring: a hit harder than 1.11 starts half a second of shake kicked
   sideways in proportion to its strength (the car's hit is cleared once read); while it runs
   the spring is integrated as for landings. */
void CCamShake::Update2()
{
    float v = car->hit.f;
    car->hit.i = 0;
    if (1.111112f < v || v < -1.111112f) {
        float w = car->hit.f;
        if (hitTime <= w) {
            float a;
            hitPos = w;
            hitTime = 0.5f;
            a = v;
            if (v < w)
                a = -v;
            a = (a - 1.111112f) / 5.55556011f;
            if (1.0f < a)
                a = 1.0f;
            a = a * 0.4f + 0.6f;
            hitVel = a * (w < v ? 50.0f : -50.0f);
        }
    }
    if (0 < hitTime) {
        float x;
        hitTime = hitTime - 1.0f / 60;
        if (hitTime < 0)
            hitTime = 0;
        hitPos = hitPos + hitVel;
        hitVel = hitVel - hitPos * 0.3f;
        x = hitVel / 20.0f;
        if (x < 0)
            x = -x;
        if (1.0f < x)
            x = sqrtf(x);
        hitVel = hitVel - hitVel * 0.2f * x;
    } else
        hitPos = 0;
}

/* @implements 0x082dc0 us _ZN9CCamShake4InitEP8ShakeCar
   WHAT IT DOES: Attaches the shake to a car and resets all three parts. */
void CCamShake::Init(ShakeCar *c)
{
    car = c;
    Reset1();
    Reset2();
    Reset3();
}

/* @implements 0x082df8 us _ZN9CCamShake8f_082df8Ev
   WHAT IT DOES: Nothing. */
void CCamShake::f_082df8()
{
}

/* @implements 0x082e00 us _ZN9CCamShake6UpdateEv
   WHAT IT DOES: Steps the rumble, the hit spring and the landing spring. */
void CCamShake::Update()
{
    Update1();
    Update2();
    Update3();
}
