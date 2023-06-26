#include <stdio.h>
#include "calc.h"

#define MAXVAL 100 // Maximum number of values in the stack (depth of val stack)

// value stack
/*
K&R 2nd C4
The variables sp and stack are for the private use of the functions in their source file,
and are not meant to be accessed by anything else.
The static declaration, applied to an external variable or function,
limits the scope of that object to the rest of the source file being compiled.
External static thus provides a way to hide names like stack and sp in the push-pop combination,
which must be external so they can be shared, yet which should not be visible to users of push and pop.
*/
static double val[MAXVAL];
// stack pointer initialized at 0
static int sp = 0;

// push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
    {
        // save f in stack then increment sp for next push
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can't push %g.\n", f);
    }
}

// pop top value from val and return it
double pop(void)
{
    if (sp > 0)
    {
        // decrement sp and return latest element (at index new sp)
        return val[--sp];
    }
    else
    {
        printf("error: empty stack.\n");
        return 0.0;
    }
}