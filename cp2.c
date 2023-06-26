#include <stdio.h>
#include <unistd.h>    // for read/write
#include <stdlib.h>    // for exit
#include <sys/types.h> // for open/creat
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 512 // block size for buffer
#define PMODE 0644   // permission mode for new file 644 RW owner, R group, others

// K&R 1978 C8 copy from file1 to file2 with file descriptors

void error(char *s1, char *s2);

int main(int argc, char *argv[])
{
    // file descriptors and bumber of bytes read/written
    int f1, f2, n;

    // buffer to read into, then read from
    char buff[BUFFSIZE];

    // check for number of command line arguments
    if (argc != 3)
        error("usage: cp from to", NULL);

    /* try to open file with name pointed to by second arg in read mode (0)
    if error f1 gets -1 so exit with error message where we plugin name of file */
    if ((f1 = open(argv[1], 0)) == -1)
        error("cp: can't open %s", argv[1]);

    /* try to create file with name pointed to by third arg with access rights 644
    if error f2 gets -1 so exit with error message where we plugin name of file */
    if ((f2 = creat(argv[2], PMODE)) == -1)
        error("cp: can't create %s", argv[2]);

    // all well so read from file assigned file descriptor f1 up to BUFFSIZE bytes, actually n bytes into buff
    while ((n = read(f1, buff, BUFFSIZE)) > 0)
    {
        // try to write n bytes from buff to file assigned file descriptor f2
        // if error write doesn't return n so exit
        if (write(f2, buff, n) != n)
            error("cp: write error", NULL);
    }

    exit(0);
}

// print error message and exit program with status 1
void error(char *s1, char *s2)
{
    // s1 is control string, s2 is the value plugged in e.g. filename
    printf(s1, s2);
    printf("\n");
    exit(1);
}