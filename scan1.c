#include <stdio.h>

// scanf with control string and conversion specifications
// scanf stops when it exhausts its control string, or when some input fails to match the control specification
// K&R 1978 C7

int main(void)
{
    int x, matched;
    float y;
    char name[50];
    char c, d, e, f;
    /* input: 56789 0123 45a72
    An input field is a string of non-white space characters;
    it extends either to the next white space character or until the field width, if specified, is exhausted
    With width 2 x gets 56, new input field becomes 789 assigned to y
    Next input field is skipped because of *
    With width 2 name gets "45"
    The next call to any input routine (e.g. getchar() will begin searching at the letter a
    scanf returns the number of successfully matched and assigned input items: x, y and name*/

    FILE *p = stdin;
    FILE *t = stdout;
    matched = scanf("%2i %f %*i %2s", &x, &y, name);
    printf("x %i, y %f, name %s, matched %i\n", x, y, name, matched);
    c = getchar();
    // push c back to stream, but only one pushback is guaranteed
    ungetc(c, stdin);
    d = getchar();
    e = getchar();
    printf("c %c, d %c, e %c\n", c, d, e);
}