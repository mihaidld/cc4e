#include <stdio.h>
#include <unistd.h>    // for read/write
#include <stdlib.h>    // for calloc/free
#include <sys/types.h> // for open/creat
#include <sys/stat.h>
#include <fcntl.h>

// K&R 1978 C8
// implementation of fopen and fclose (open and close file with file pointer) and
// getc and putc (get char from and put char into file pointer)
// added suffix _new to distinguish from names in stdio.h

#define _BUFFSIZE_NEW 5 // buffer size
#define _NFILE_NEW 20   // max number of files opened in same time

#define _READ_NEW 01    // file open for reading last bit is 1 0000 0001
#define _WRITE_NEW 02   // file open for writing or apending second last bit is 1 0000 0010
#define _UNBUF_NEW 04   // file open unbuffered third bit is 1 0000 0100
#define _BIGBUF_NEW 010 // octal 10 big buffer allocated forth bit is 1 0000 1000
#define _EOF_NEW 020    // octal 020 (decimal 16) encountered EOF on this file fifth bit is 1 0001 0000
#define _ERR_NEW 040    // octal 040 (decimal 32) encountered error on this file when read sixth bit is 1 0010 0000
#define NULL_NEW 0
#define EOF_NEW (-1)
#define PMODE_NEW 0644 // octal 644 permission mode for new files R/W for owner (6), and R for group, others (4)

/*if cnt decremented in file still >=0 we get char pointed to by ptr in file and increment ptr
if no more chars in buffer fill buffer with fillbuf and get char returned by it*/
#define getc_new(p) (--(p)->cnt >= 0 ? *(p)->ptr++ : _fillbuf_new(p))
#define getchar_new() getc_new(stdin_new)
/*if cnt decremented in file still >=0 we set char pointed to by ptr in file to char x and increment ptr
if no count reached 0 flush buffer and set first char in buffer to x*/
#define putc_new(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf_new((x), p))
#define putchar_new(x) putc_new(x, stdout_new)

// create struct file with its members (info)
typedef struct _iobuf_new
{
    char *ptr;  // pointer to next char in file
    int cnt;    // number of chars left
    char *base; // pointer to beginning of buffer
    int flag;   // mode file access: e.g. read, write, unbuffered, reached EOF, encountered error
    int fd;     // file descriptor referencing this file
} FILE_NEW;

// define array of files size 20, initialize first 3 elements, the other 17 are set to 0
FILE_NEW _iob_new[_NFILE_NEW] = {
    {NULL_NEW, 0, NULL_NEW, _READ_NEW, 0},              // stdin in read mode file descriptor 0
    {NULL_NEW, 0, NULL_NEW, _WRITE_NEW, 1},             // stdout in write mode
    {NULL_NEW, 0, NULL_NEW, _WRITE_NEW | _UNBUF_NEW, 2} // stderr in write mode unbuffered
};

// first 3 files opened by system for the program
#define stdin_new &_iob_new[0]  // standard input points at first element of array
#define stdout_new &_iob_new[1] // standard output points at second element of array
#define stderr_new &_iob_new[0] // standard error points at first element of array

int _fillbuf_new(FILE_NEW *fp);
int _flushbuf_new(int c, FILE_NEW *fp);
FILE_NEW *fopen_new(char *name, char *mode);
void fclose_new(FILE_NEW *fp);
void fflush_new(void);

int main(int argc, char *argv[])
{
    // store char in c
    int c;
    // open files
    FILE_NEW *infile1 = fopen_new("b.txt", "r");
    FILE_NEW *infile2 = fopen_new("a.txt", "r");
    FILE_NEW *infile3 = fopen_new("c.txt", "w");

    // read from file1 and write to stdout and file3
    while ((c = getc_new(infile1)) != EOF_NEW)
    {
        putchar_new(c);
        putc_new(c, infile3);
    }

    // read from file2 and write to stdout and file3
    while ((c = getc_new(infile2)) != EOF_NEW)
    {
        putchar_new(c);
        putc_new(c, infile3);
    }

    // close files (including flush output buffers)
    fclose_new(infile1);
    fclose_new(infile2);
    fclose_new(infile3);
}

FILE_NEW *fopen_new(char *name, char *mode)
{
    // store file descriptor found and file pointer to be returned
    int fd;
    FILE_NEW *fp;

    // check correct mode: first char of mode is 'r', 'w' or 'a'
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    // send to stderr error message
    {
        fprintf(stderr, "illegal mode %s opening %s\n", mode, name);
        exit(1);
    }

    // find free slot in _iob after stdin, stdout, stderror and any open files
    for (fp = _iob_new; fp < _iob_new + _NFILE_NEW; fp++)
        // check that last 2 bits in flag are 0. if so found slot
        if ((fp->flag & (_READ_NEW | _WRITE_NEW)) == 0)
            break;

    // check that we finished loop by break not after checking all elements in array
    // and all slots are taken (20 files open already)
    if (fp >= _iob_new + _NFILE_NEW)
        return (NULL_NEW);

    // if write mode we create file
    //  if already created gets truncated to 0, overwritten
    if (*mode == 'w')
        fd = creat(name, PMODE_NEW);
    else if (*mode == 'a')
    {
        // if append try top open it in write mode (1)
        //  if error to open it, doesn't exist so create it
        if ((fd = open(name, 1)) == -1)
            fd = creat(name, PMODE_NEW);
        // in any case go to to offset 0 from end of file (2)
        lseek(fd, 0L, 2);
    }
    // if read mode open it in read mode (0)
    else
        fd = open(name, 0);

    // could not access file after creat or open
    if (fd == -1)
        return (NULL_NEW);

    // set info in FILE count 0 and base NULL
    fp->base = NULL_NEW;
    fp->cnt = 0;
    fp->fd = fd;

    // set in flag for new open file to READ if read mode or WRITE if append or write
    /* make sure last 2 bits are 0, no need since we already knew that when we broke from loop)
    flag & ~(0000 0011) : flag & 1111 1100 : xxxx xx00 */
    // fp->flag &= ~(_READ_NEW | _WRITE_NEW);

    // set last bits of flag to 01 if read, or 10 if append, write
    fp->flag |= (*mode == 'r') ? _READ_NEW : _WRITE_NEW;

    return fp;
}

// allocate and fill input buffer
int _fillbuf_new(FILE_NEW *fp)
{
    // private (static) array of chars size 20 for unbuffered input
    // one char per file in case we cannot allocate 512 bytes with calloc
    static char smallbuf[_NFILE_NEW];

    /*check file open in read mode and
    didn't encounter an error or reached EOF using flags */
    if ((fp->flag & _READ_NEW) == 0 || (fp->flag & (_EOF_NEW | _ERR_NEW)) != 0)
        return EOF_NEW;

    // find buffer space
    while (fp->base == NULL)
        // flag unbuffered is set set base to point to
        // allocated char in private array at index fd
        if (fp->flag & _UNBUF_NEW)
            fp->base = &smallbuf[fp->fd];
        // try to allocate big buffer 512 bytes
        else if ((fp->base = calloc(1, _BUFFSIZE_NEW)) == NULL)
            // can't get big buf (512 bytes on th heap) so set flag to UNBUF for next iteration
            fp->flag |= _UNBUF_NEW;
        else
            // got big buf so set flag to BIGBUF
            fp->flag |= _BIGBUF_NEW;

    // (re)set ptr to point to same first char of buffer as base
    fp->ptr = fp->base;
    /*try to read from file into buffer 1 byte if flag UNBUF set or 512 bytes if not
    and set count to number of bytes read
    (max 512, -1 in case of error, 0 if reached EOF,
    between 1 and 512 if close to the end)*/
    fp->cnt = read(fp->fd, fp->ptr, fp->flag & _UNBUF_NEW ? 1 : _BUFFSIZE_NEW);

    // decrement count and set flags ERROR and EOF
    // according to returned valeu of read -1 (error) and 0 (EOF)
    if (--fp->cnt < 0)
    { // read returned 0 so decremented cnt is now -1
        if (fp->cnt == -1)
            fp->flag |= _EOF_NEW;
        else
            fp->flag |= _ERR_NEW;
        // reset cnt to 0 if EOF or error
        fp->cnt = 0;
        return EOF_NEW;
    }

    // all is well so get char pointed to by ptr
    // then increment ptr to point to next char in buffer
    return (*fp->ptr++);
}

/* allocate buffer for output and empties it when full
gets called when trying to put first char into the file (since empty buffer)
when buffer is full (1 or 512 bytes) and also when file is closed
and all output buffers are flushed (emptied) */
int _flushbuf_new(int c, FILE_NEW *fp)
{
    // private (static) array of chars size 20 for unbuffered input
    // one char per file in case we cannot allocate 512 bytes with calloc
    static char smallbuf[_NFILE_NEW];

    /*check file open in write or append mode and
    didn't encounter an error using flags,
    if error return EOF*/
    if ((fp->flag & _WRITE_NEW) == 0 || (fp->flag & _ERR_NEW) != 0)
        return EOF_NEW;

    // find buffer space
    while (fp->base == NULL)
        // flag unbuffered is set set base to point to
        // allocated char in private array at index fd
        if (fp->flag & _UNBUF_NEW)
        {
            fp->base = fp->ptr = &smallbuf[fp->fd];
            fp->cnt = 1;
        }
        // try to allocate big buffer 512 bytes
        else if ((fp->base = fp->ptr = calloc(1, _BUFFSIZE_NEW)) == NULL)
            // can't get big buf (512 bytes on th heap) so set flag to UNBUF for next iteration
            fp->flag |= _UNBUF_NEW;
        else
        {
            // got big buf so set flag to BIGBUF
            fp->flag |= _BIGBUF_NEW;
            fp->cnt = _BUFFSIZE_NEW;
        }

    // get number of bytes input into buffer (pointer substraction)
    int n = fp->ptr - fp->base;

    /*branch not used during first call when putting first char into buffer
    try to write from buffer into file 1 byte if flag UNBUF set or 512 bytes if not
    and check number bytes written is n, if error set flag*/
    if (fp->ptr > fp->base)
    {
        if (write(fp->fd, fp->base, n) != n)
        {
            // write n bytes returned value different than n
            fp->flag |= _ERR_NEW;
            // reset cnt to 0 if error
            fp->cnt = 0;
            return EOF_NEW;
        }

        // all is well so (re)set ptr to point to same first char of buffer as base
        fp->ptr = fp->base;
        fp->cnt = n;
    }

    // decrement count, put char in new buffer and return it
    // except if c is EOF when function called by fflush
    if (c != EOF_NEW)
    {
        fp->cnt--;
        *(fp)->ptr++ = c;
    }

    return c;
}

// close file
void fclose_new(FILE_NEW *fp)
{
    // flush all written buffers
    fflush_new();

    // free space allocated with calloc if buffered (flag BIGBUF set)
    if (fp->flag & _BIGBUF_NEW)
        free(fp->base);

    // reset flag to 0 so slot can be reused for next open file
    fp->flag = 0;
    // close file descriptor, so that it no longer refers to any file and may be reused
    close(fp->fd);
}

// flush all output buffers
void fflush_new(void)
{
    // iterate over all open files
    for (FILE_NEW *fp = _iob_new; fp < _iob_new + _NFILE_NEW; fp++)
        // flush buffer for all files in written mode (e.g. stdout)
        // use any character e.g. '\n' since it will not be written , just to call _flushbuf
        if (fp->flag & _WRITE_NEW)
            _flushbuf_new(EOF_NEW, fp);
}