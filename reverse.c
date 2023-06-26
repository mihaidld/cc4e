#include <stdio.h>
#include <string.h>

char *copy(char s1[], char s2[]);
void str_copy(char *dest, char *src);
void reverse(char t[]);

int main(void)
{
    char t[1000];

    // copy(t, "Hello world");
    str_copy(t, "Hello world");
    printf("%s\n", t);
    reverse(t);
    printf("%s\n", t);

    reverse(copy(t, "XY"));
    printf("%s\n", t);

    reverse(copy(t, "Even"));
    printf("%s\n", t);

    reverse(copy(t, "Odd"));
    printf("%s\n", t);

    reverse(copy(t, "civic"));
    printf("%s\n", t);
}

// copy strings using char arrays
// copy s2 from s1; assume s2 big enough
char *copy(char s2[], char s1[])
{
    for (int i = 0; (s2[i] = s1[i]); i++)
        ;
    return s2;
}

// copy strings using char pointers
/* K&R 1978 C5 implementation of strcpy with 2 char pointers
Initially destination and source are char pointers pointing at first char of the string.
Eveything is done in the test: put in the char pointed to by dest the char value pointed to by src
The assignment has a residual value of the char, if the char has not the int value 0 (the \0 NULL terminator)
then the test is true so we increment char pointers using pointer arithmetic by 1 * size of type pointed (char so 1)
and execute body of the loop which is an empty statement. The '\0' is also copied before loop ends. */
void str_copy(char *dest, char *src)
{
    while ((*dest++ = *src++))
        ;
}

// reverses the characters in a string. Reverse the string in place.
void reverse(char t[])
{
    // char to store temporary value for swap
    char c;

    // loop till the middle of the char array to swap chars simmetrical on each side
    for (int i = 0, n = strlen(t); i < n / 2; i++)
    {
        c = t[i];
        t[i] = t[n - 1 - i];
        t[n - 1 - i] = c;
    }
    return;
}