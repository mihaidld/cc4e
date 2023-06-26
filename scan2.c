#include <stdio.h>

// scanf with control string and conversion specifications
// scanf stops when it exhausts its control string, or when some input fails to match the control specification
// K&R 1978 C7 calculator with scanf

int main(void)
{
    double sum, v;
    // store mismatched character to clear buffer
    char c;
    sum = 0;
    // store number of matches and assignments of scanf
    int matched;
    // scan input, store its return value in matched and assign input value to v
    //  if EOF (-1) end loop
    while ((matched = scanf("%lf", &v)) != EOF)
    {
        // error checking for mismatch input to expected float when match == 0
        if (!matched)
        {
            // clear buffer into c so scanf can look for new float
            scanf("%c", &c);
            printf("error: expected float input instead of %c\n", c);
        }
        // received float input so sum up and print the updated sum
        else
        {
            printf("\t%.2f\n", sum += v);
        }
    }
}