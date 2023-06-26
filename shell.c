#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Establish range of numbers
const int MIN = 1;
const int MAX = 100;

void print_array(int length, int array[]);

// SHELL SORT (as per K&R 1978 chap 3)

/* In early stages, far-apart elements are compared (largest gap is half the count of elements so compare and swap
 * first to middle, second to middle + 1...),
 * rather than adjacent ones, as in simple interchange sorts (e.g. bubble sort).
 * This tends to eliminate large amounts of disorder quickly,
 * so later stages have less work to do.
 * The interval between compared elements is gradually decreased to one
 * (at every outter loop iteration split in half),
 * at which point the sort effectively becomes an adjacent interchange method. */

int main(void)
{
    // Generate random numbers array
    int count;
    printf("Number of elements: ");
    scanf("%i", &count);
    int numbers[count];

    // Use current time as seed for random generator
    srand(time(0));
    for (int i = 0; i < count; i++)
    {
        numbers[i] = (rand() % (MAX - MIN + 1)) + MIN;
    }

    // Print unsorted array
    print_array(count, numbers);

    // Shell sort
    int gap, i, j, temp;

    // 3 nested loops
    /* The outermost loop controls the gap between compared elements,
    shrinking it from count / 2 by a factor of two each pass until it becomes zero.*/
    for (gap = count / 2; gap > 0; gap /= 2)
        // The middle loop compares each pair of elements that is separated by gap;
        for (i = gap; i < count; i++)
            /*the innermost loop reverses any that are out of order.
            Since gap is eventually reduced to one, all elements are eventually ordered correctly.
            j starts at 0 so compare numbers[0] with numbers[0 + gap],
            then 1 numbers[1] with numbers[1 + gap]...*/
            for (j = i - gap; j >= 0 && numbers[j] > numbers[j + gap]; j -= gap)
            {
                temp = numbers[j];
                numbers[j] = numbers[j + gap];
                numbers[j + gap] = temp;
            }

    // Print sorted array
    print_array(count, numbers);
}

// Prints array
void print_array(int length, int array[])
{
    printf("[");
    for (int i = 0; i < length; i++)
    {
        if (i < length - 1)
        {
            printf("%i, ", array[i]);
        }
        else
        {
            printf("%i", array[i]);
        }
    }
    printf("]\n");
}