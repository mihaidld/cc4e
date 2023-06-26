#include <stdio.h>
#include <unistd.h>

#define BUFFSIZE 512 // block size for buffer

// K&R 1978 C8 copy from stdin to stdout with file descriptors

int main(void)
{
    /*buffer to read into, then read from
    For number of bytes to read/write two most common values are:
    1, which means one character at a time ("unbuffered"), and
    512, which corresponds to a physical blocksize on many peripheral devices
    */
    char buff[BUFFSIZE];

    // number of bytes actually read/written
    int n;

    // read from file descriptor 0 (stdin) up to BUFFSIZE bytes, actually n bytes into buff
    while ((n = read(0, buff, BUFFSIZE)) > 0)
    {
        // write n bytes from buff to file descriptor 1 (stdout)
        write(1, buff, n);
    }
}