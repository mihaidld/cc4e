#include <stdio.h>

/*https://www.cc4e.com/
Using 'extern' data storage class
function called bump() uses an extern variable so that
the first time it is called, it returns int 0,
the next time it returns 1 and so on.*/

int main(void)
{
    // declaration of function bump of type int (returns an int) so it can be used in main
    int bump(void);
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
    printf("bump() returns %d\n", bump());
}

// definition of function bump
int bump(void)
{
    // declaration of int variable i which is defined outside this scope
    extern int i;
    // i is returned, then incremented
    return i++;
}

// definition of int i and initialization
int i = 0;