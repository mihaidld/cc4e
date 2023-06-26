#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
#define SIZE 10

// K&R 2nd Chap 5 get ints from user input

/* getint performs free-format input conversion by breaking a stream of characters
into integer values, one integer per call.
Sets as side effect the integer value it found.
Returns EOF for end of file, 0 if the next input is not a number,
and a positive value if the input contains a valid number
*/

int getch(void);
void ungetch(int c);
int getint(int *pi);

static char buf[BUFSIZE];
static int bufp = 0;

int main(void)
{
    int n, array[SIZE];
    // get value in loop test with getint and print value in loop body
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        printf("int %i at position %i\n", array[n], n);
    printf("\n");
}

// get next char from input into *pi if only ints separated by space
// 1 2 -4 312 -213
int getint(int *pi)
{
    int c, sign;

    // skip whitespace
    while (isspace(c = getch()))
        ;

    // if current char is not a sign, EOF or digit
    // put char back to input and return 0
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c);
        return 0;
    }

    // sign if not present, by default is positive 1
    sign = c == '-' ? -1 : 1;

    // if current char is sign get next char
    if (c == '+' || c == '-')
        c = getch();

    // if found char digits construct int value from chars
    for (*pi = 0; isdigit(c); c = getch())
        *pi = 10 * *pi + c - '0';

    // set sign
    *pi *= sign;

    // after recording int value at *pi, put char back to input and
    // return current char which is no longer a digit
    if (c != EOF)
        ungetch(c);
    return c;
}

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