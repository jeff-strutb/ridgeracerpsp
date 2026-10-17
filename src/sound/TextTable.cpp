/* The text table reader (retail 0x114d34 to 0x11529c): parses "Name = value, value, ..."
   lines of a text file, up to a terminator line, into up to 128 named rows, and returns a
   row's values as strings or numbers. Tabs, spaces and commas separate values; '/' starts a
   comment. Used by the mixer configuration loader (0x10e198). */

extern "C" {
int strlen(const char *s);
int strncmp(const char *a, const char *b, unsigned int n);
int strcmp(const char *a, const char *b);
char *strcpy(char *d, const char *s);
int atoi(const char *s);
void f_125b5c(int status) __attribute__((noreturn)); /* exit */
}

/* A row: its name, the line it was read from and its value count (40 bytes). */
struct TextRow {
    char name[32];
    const char *line;
    int n;
};

static inline int IsBlank(char c)
{
    return c == '\t' || c == ' ';
}

static inline int IsWord(char c)
{
    return c != '\t' && c != ' ';
}

static inline int IsEol(char c)
{
    return c == '\n' || c == '\r';
}

class CReader {
public:
    TextRow rows[128];
    char buf[512];
    int count;

    CReader(const char *text, const char *end);
    ~CReader();
    bool f_114db4(const char *name);
    int f_114dd4(const char *name);
    char *f_114e00(const char *name, int i);
    char *f_114ee8(const char *name);
    int f_114f04(const char *name, int i);
    int f_114f3c(const char *text, const char *end);
    TextRow *f_114fe0(const char *name);
    void f_115060();
    int f_115068(const char *line);
    int f_115180(const char *s, int n, char *out);
};

/* @implements 0x114d34 us _ZN7CReaderC2EPKcS1_
   WHAT IT DOES: Starts empty and, given a text and its terminator line, parses it. */
/* @implements 0x114d6c us _ZN7CReaderC1EPKcS1_
   WHAT IT DOES: The complete-object form of the same constructor. */
CReader::CReader(const char *text, const char *end)
{
    count = 0;
    if (text && end)
        f_114f3c(text, end);
}

/* @implements 0x114da4 us _ZN7CReaderD2Ev
   WHAT IT DOES: Destroys the reader (it owns nothing). */
/* @implements 0x114dac us _ZN7CReaderD1Ev
   WHAT IT DOES: The complete-object form of the same destructor. */
CReader::~CReader()
{
}

/* @implements 0x114db4 us f_114db4
   WHAT IT DOES: Returns whether row name exists. */
bool CReader::f_114db4(const char *name)
{
    return f_114fe0(name) != 0;
}

/* @implements 0x114dd4 us f_114dd4
   WHAT IT DOES: Returns row name's value count, -1 if there is no such row. */
int CReader::f_114dd4(const char *name)
{
    TextRow *r = f_114fe0(name);

    if (r)
        return r->n;
    return -1;
}

/* @draft 0x114e00 us f_114e00
   WHAT IT DOES: Returns value i of row name as a string in the reader's buffer, or with i -1
   everything after the '=' to the end of the line; 0 if there is no such row. 
   DRAFT: 28 words differ: retail keeps i in s1 (reused for the buffer pointer) and the reader
   in s0, and copies the rest of the line through a0/a2; here those registers are swapped. */
char *CReader::f_114e00(const char *name, int i)
{
    TextRow *r = f_114fe0(name);

    if (!r)
        return 0;
    if (i == -1) {
        const char *s = r->line;
        char *d = buf;
        while (*s != '=')
            s++;
        s++;
        while (*s != '\r' && *s != '\n')
            *d++ = *s++;
        *d = 0;
        return buf;
    }
    f_115180(r->line, i + 2, buf);
    return buf;
}

/* @implements 0x114ee8 us f_114ee8
   WHAT IT DOES: Returns row name's whole value text. */
char *CReader::f_114ee8(const char *name)
{
    return f_114e00(name, -1);
}

/* @implements 0x114f04 us f_114f04
   WHAT IT DOES: Returns value i of row name as a number, 0 if there is no such row. */
int CReader::f_114f04(const char *name, int i)
{
    char *s = f_114e00(name, i);

    if (s)
        return atoi(s);
    return 0;
}

/* @implements 0x114f3c us f_114f3c
   WHAT IT DOES: Parses the text line by line up to the terminator line; returns 0, or the
   first failing line's code (1 for a repeated name, 2 for a line without '='). */
int CReader::f_114f3c(const char *text, const char *end)
{
    int r;

    f_115060();
    for (;;) {
        if (strncmp(text, end, strlen(end)) == 0)
            return 0;
        r = f_115068(text);
        if (r)
            return r;
        while (*text != '\n')
            text++;
        text++;
    }
}

/* @implements 0x114fe0 us f_114fe0
   WHAT IT DOES: Finds row name. */
TextRow *CReader::f_114fe0(const char *name)
{
    int i;

    for (i = 0; i < count; i++)
        if (strcmp(rows[i].name, name) == 0)
            return &rows[i];
    return 0;
}

/* @implements 0x115060 us f_115060
   WHAT IT DOES: Empties the reader. */
void CReader::f_115060()
{
    count = 0;
}

/* @draft 0x115068 us f_115068
   WHAT IT DOES: Parses one line into a new row: its name, '=' and the values that follow.
   Returns 0 (also for a blank line), 1 if the name is already a row, 2 without the '='.
   A 129th row ends the program. 
   DRAFT: 33 words differ: retail keeps the buffer pointer in s1 and the row in s2 (swapped
   here) and places the value-count loop out of line after the return-2 jump. */
int CReader::f_115068(const char *line)
{
    char *b = buf;
    TextRow *r = &rows[count];

    f_115180(line, 0, b);
    if (b[0] == 0)
        return 0;
    if (f_114db4(b))
        return 1;
    strcpy(r->name, b);
    r->line = line;
    f_115180(line, 1, b);
    if (b[0] != '=')
        return 2;
    if (b[1] == 0) {
        r->n = 0;
        while (f_115180(line, r->n + 2, b))
            r->n++;
        if (++count == 128)
            f_125b5c(-1);
        return 0;
    }
    return 2;
}

/* @draft 0x115180 us f_115180
   WHAT IT DOES: Copies the n-th field of a line (fields split by tabs, spaces and commas) to
   out; returns 1 if the line has that field, 0 at the end of the line or a '/' comment. 
   DRAFT: the loops and tests match; the two "return 0" blocks stay separate in retail (here
   cross-jumped) and the end-of-line test's setup is scheduled differently. */
int CReader::f_115180(const char *s, int n, char *out)
{
    int i;

    *out = 0;
    for (i = 0; i <= n; i++) {
        for (;;) {
            if (!(IsBlank(*s) || *s == ',' || *s == '\n' || *s == '\r' || *s == '/'))
                break;
            if (IsEol(*s))
                return 0;
            if (*s == '/')
                return 0;
            s++;
        }
        for (;;) {
            if (!(IsWord(*s) && *s != ',' && *s != '\r' && *s != '\n'))
                break;
            if (i == n)
                *out++ = *s++;
            else
                s++;
        }
        if (i == n) {
            *out = 0;
            return 1;
        }
    }
    return 0;
}
