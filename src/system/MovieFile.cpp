/* The movie file reader object file (retail 0x08d2b8 to 0x08d394): the movie player's access to
   its stream file through the disc file routines (open, close, read, write and seek). */

int f_027850(const char *name, int write, int mode);
int f_02793c(int fd);
int f_027958(int fd, void *buf, int size);
int f_027c00(int fd, const void *buf, int size);
int f_027974(int fd, int offset, int whence);

class CMovieFile {
public:
    int f_08d2b8(const char *name);
    int f_08d2f8();
    int f_08d32c();
    int f_08d334(void *buf, int size);
    int f_08d350(const void *buf, int size);
    long long f_08d36c(long long offset, int whence);

    int fd;
};

/* @implements 0x08d2b8 us f_08d2b8
   WHAT IT DOES: Opens the named file for reading. Returns 1, or -1 when it cannot be opened. */
int CMovieFile::f_08d2b8(const char *name)
{
    fd = f_027850(name, 0, 0);
    return fd < 0 ? -1 : 1;
}

/* @implements 0x08d2f8 us f_08d2f8
   WHAT IT DOES: Closes the file when it is open. Returns the close's result, or -1. */
int CMovieFile::f_08d2f8()
{
    int r = -1;
    if (fd >= 0)
        r = f_02793c(fd);
    return r;
}

/* @implements 0x08d32c us f_08d32c
   WHAT IT DOES: Nothing (returns 1). */
int CMovieFile::f_08d32c()
{
    return 1;
}

/* @implements 0x08d334 us f_08d334
   WHAT IT DOES: Reads size bytes from the file. */
int CMovieFile::f_08d334(void *buf, int size)
{
    return f_027958(fd, buf, size);
}

/* @implements 0x08d350 us f_08d350
   WHAT IT DOES: Writes size bytes to the file. */
int CMovieFile::f_08d350(const void *buf, int size)
{
    return f_027c00(fd, buf, size);
}

/* @implements 0x08d36c us f_08d36c
   WHAT IT DOES: Moves the file position. Returns the new position. */
long long CMovieFile::f_08d36c(long long offset, int whence)
{
    return f_027974(fd, offset, whence);
}
