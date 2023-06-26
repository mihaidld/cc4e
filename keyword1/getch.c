#include <stdio.h>

#define BUFSIZE 100

// a shared buffer
static char buf[BUFSIZE];
// buffer position records position of current char in the buffer
// next free position in buffer
static int bufp = 0;

// delivers the next input character to be considered
int getch(void)
{
    // reads from the buffer if there is anything there and
    // decrements buffer position afterwards
    // or calls getchar if the buffer is empty
    return (bufp > 0 ? buf[--bufp] : getchar());
}

// remembers the characters put back on the input,
// so that subsequent calls to getch will return them before reading new input
// puts the pushed-back characters into buffer
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}