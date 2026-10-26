/* The render setup object file (retail 0x0d710c to 0x0d71f8 in the part this file covers): the
   model and texture initialisers, which report a failure with a message, and the thin wrappers
   that hand their argument on to a loader. The object's larger function, which is not here,
   sets up the cylinder map and scissor buffers. */

extern "C" {
int f_0fe990(void *self);
int f_126f1c(const char *fmt, ...);
void *f_022d00(void *file, int id);
void *f_022de4(int area, void *file, int id);
void f_0cbd88(void *self);
void f_0231c8(void *self);
}

/* @implements 0x0d710c us f_0d710c
   WHAT IT DOES: An empty function (a virtual stub with nothing to do). */
extern "C" void f_0d710c(void *self)
{
}

/* @implements 0x0d7114 us f_0d7114
   WHAT IT DOES: An empty function (the same stub as 0x0d710c). */
extern "C" void f_0d7114(void *self)
{
}

/* @implements 0x0d711c us f_0d711c
   WHAT IT DOES: Initialises the model through 0x0fe990; when that reports failure, logs
   "Model Init Failed" through 0x126f1c. */
extern "C" void f_0d711c(void *self)
{
    if (f_0fe990(self) == 0)
        f_126f1c("Model Init Failed");
}

/* @implements 0x0d7154 us f_0d7154
   WHAT IT DOES: Initialises a texture: an id of -1 goes through 0x022d00 with the object,
   any other id through 0x022de4 with the id and the object; when the result is null it logs
   "Texture Init Failed" through 0x126f1c. */
extern "C" void f_0d7154(void *self, int unused, int id)
{
    void *r;
    if (id == -1) {
        r = f_022d00(self, 0);
        if (r == 0)
            f_126f1c("Texture Init Failed");
        return;
    }
    r = f_022de4(id, self, 0);
    if (r == 0)
        f_126f1c("Texture Init Failed");
}

/* @implements 0x0d71b8 us f_0d71b8
   WHAT IT DOES: Passes its argument on to 0x0cbd88. */
extern "C" void f_0d71b8(void *self)
{
    f_0cbd88(self);
}

/* @implements 0x0d71d4 us f_0d71d4
   WHAT IT DOES: Passes its argument on to 0x0231c8. */
extern "C" void f_0d71d4(void *self)
{
    f_0231c8(self);
}

/* @implements 0x0d71f0 us f_0d71f0
   WHAT IT DOES: An empty function (the same stub as 0x0d710c). */
extern "C" void f_0d71f0(void *self)
{
}
