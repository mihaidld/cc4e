#include <stdio.h>
#include <stdlib.h> //for atol, atoi
#include <string.h> //for strcmp
#include <unistd.h>
#include <sys/types.h> // for open/creat
#include <sys/stat.h>
#include <fcntl.h>

// K&R 1978 C8 read any number of bytes from any arbitrary place in a file.

int get(int fd, long pos, char *buf, int n);
void error(char *s1, char *s2);

int main(int argc, char *argv[])
{
    int f1, n, m;
    long from;

    if (argc != 4)
        error("usage: seek filename from n", NULL);

    /* try to open file with name pointed to by second arg in read mode (0)
    if error f1 gets -1 so exit with error message where we plugin name of file */
    if ((f1 = open(argv[1], 0)) == -1)
        error("seek: can't open %s", argv[1]);

    /*try to convert third arg into long. If error atol returns 0
    To distinguish between returned 0 from error and actual "0"
    compare strings*/
    if ((from = atol(argv[2])) == 0)
        if (strcmp(argv[2], "0") != 0)
            error("seek: %s must be positive integer", argv[2]);
    if (from < 0)
        error("seek: %s must be positive integer", argv[2]);
    if ((n = atoi(argv[3])) <= 0)
        error("seek: %s must be non-zero positive integer", argv[3]);

    /*buffer to read into*/
    char buff[n];

    // try read from file descriptor f1 up to n bytes (actually m) from position from into buff
    m = get(f1, from, buff, n);

    // try to write m bytes from buff to file descriptor 1 (stdout)
    // if error write doesn't return n so exit
    if (write(1, buff, m) != m)
        error("seek: write error", NULL);

    printf("\n");
    exit(0);
}

int get(int fd, long pos, char *buf, int n)
{
    // move into file linked to file descriptor fd to offeset pos from beginning (0)
    lseek(fd, pos, 0);

    // read up to n bytes starting from new position into buff
    return (read(fd, buf, n));
}

// print error message and exit program with status 1
void error(char *s1, char *s2)
{
    // s1 is control string, s2 is the value plugged in e.g. filename
    printf(s1, s2);
    printf("\n");
    exit(1);
}