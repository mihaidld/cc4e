#include <stdio.h>
// define macro with arguments, parenthesis are important for substition
#define max(A, B) ((A) > (B) ? (A) : (B))
// define macro swap with \ for block structure interchanges its two int arguments
#define swap(type, x, y) \
    {                    \
        type z = x;      \
        x = y;           \
        y = z;           \
    }

// K&R 1978 C4
// macro substitution expands into in-line code during pre=processing thus avoiding the overhead of a function call at runtime

int main(void)
{
    int p = 1, q = 2, r = 3, s = 4;

    int x = max(p + q, r + s);
    /*this line, during pre-processing and macro expansion will be replaced by:
    int x = ((p + q) > (r + s) ? (p + q) : (r + s))*/
    printf("x %i\n", x);

    swap(int, p, s);
    /*this line, during pre-processing and macro expansion will be replaced by:
    {type z = x; x = y; y = z;}*/
    x = max(p + q, r + s);
    printf("x %i\n", x);
}