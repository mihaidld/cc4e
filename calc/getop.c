#include <stdio.h>
#include <ctype.h>
#include "calc.h"

// fetch next numeric operand or operator
int getop(char s[])
{
    int c, i;
    // skip blanks and tabs, but not newline which requires result
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    // loop stopped so s[0] = c was updated to not a bloank or tab, possibly an operator or mewline
    // add NULL to complete string
    s[1] = '\0';

    // if not a number (c is not a digit or decimal point '.' from a fractional number)
    // return character (an operator, newline or other)
    if (!isdigit(c) && c != '.')
    {
        return c;
    }

    // collect string of digits (which optional decimal point)
    // s[0] is already assigned digit or '.' so we get next char assign it to c
    // the assign it to s[1] and check if a digit
    i = 0;
    // collect integer part
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    // collect fractional part
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    // add NULL char to terminate string
    s[i] = '\0';

    // push c back onto the input since we found a non digit by calling getch
    // so we put it back for it to be retrived next time with getch
    if (c != EOF)
        ungetch(c);

    // s was updated as a side effect, return signal that a number was collected in s
    return NUMBER;
}