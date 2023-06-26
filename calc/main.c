#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100 // Maximum size for string storing operand or operator

// reverse Polish calculator
int main(void)
{
    int type;
    char s[MAXOP];
    double op2;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        // commutative operation + and * doesn't matter order elements popped
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        // to preserve order pop latest and store it in op2, then pop former
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
            {
                push(pop() / op2);
            }
            else
            {
                printf("error: 0 divisor.\n");
            }
            break;
        // print result after a tab
        /*.8g double argument g is converted to f (float) with the maximum number of significant digits
        as 8 -> 8 digits in total before and after . (e.g. 1111.1111 or 11.111111)
        .8f double argument f with the number of digits after the decimal-point character
        is equal to the precision 8 (e.g. 1111.11111111 or 11.11111111)*/
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s.\n", s);
        }
    }

    return 0;
}