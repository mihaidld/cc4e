#include <stdio.h>
#include <string.h>

#include "keyword.h"

// binary search for a word in array of structs key of size n
// returns index if found or -1 if not found
int binary(char *word, key tab[], int n)
{
    // indices for start, end and middle of sorted array
    int low, high, mid;

    // condition to store comparison between word and keyword at index mid
    // in key tab to reuse for else if test
    int cond;
    low = 0;
    high = n - 1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        // compare strings, assign return value to cond, compare assignemt residula value to 0
        if ((cond = strcmp(word, tab[mid].keyword)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}