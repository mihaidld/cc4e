#include <stdio.h>

// Binary search K&R Kernighan & Ritchie, C programming 1978
// with while loop

int search(int length, int array[], int searched);
void print_array(int length, int array[]);

// BINARY SEARCH
int main(void)
{
    int len = 11;
    int arr[] = {1, 2, 28, 42, 54, 71, 73, 87, 97, 98, 100};
    // Print initial array
    print_array(len, arr);

    int x;
    printf("Number to search: ");
    scanf("%i", &x);

    int position = search(len, arr, x);
    if (position >= 0)
        printf("Found %i at index %i.\n", x, position);
    else
        printf("Not found.\n");
}

// get index of searched if found or -1 if not found
int search(int length, int array[], int searched)
{
    // variables to store indices of extremities of (sub)array to search and its middle
    int low, high, mid;

    low = 0;
    high = length - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        // update high if searched is in the left half
        if (searched < array[mid])
            high = mid - 1;
        // update low if searched is in the right half
        else if (searched > array[mid])
            low = mid + 1;
        // found match
        else
            return mid;
    }

    return -1;
}

// Prints array
void print_array(int length, int array[])
{
    printf("[");
    for (int i = 0; i < length - 1; i++)
    {
        printf("%i, ", array[i]);
    }
    printf("%i]\n", array[length - 1]);
}