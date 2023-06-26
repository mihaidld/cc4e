#include <stdio.h>

#define DIGITS 10

// count digits, space chars and other characters in input
// https://www.cc4e.com/book/chap01.md
int main(void)
{
    // c is the buffer to copy into character read
    // i is used for iterating
    // store counters for digits in an array
    int c, i, nwhite, nother;
    int ndigits[DIGITS];

    // counters set to 0
    nwhite = nother = 0;
    for (i = 0; i < DIGITS; i++)
    {
        ndigits[i] = 0;
    }

    // iterate over input
    while ((c = getchar()) != EOF)
    {
        // check for digits and increment element at index c - '0' = convert ASCII value to int
        if (c >= '0' && c <= '9')
        {
            ndigits[c - '0']++;
        }
        // check for space
        else if (c == ' ' || c == '\t' || c == '\n')
        {
            nwhite++;
        }
        else
        {
            nother++;
        }
    }
    // print digits
    printf("digits =");
    for (i = 0; i < DIGITS; i++)
    {
        printf(" %d", ndigits[i]);
    }
    // print rest of counters
    printf("\nwhite space = %d, other = %d\n", nwhite, nother);
}