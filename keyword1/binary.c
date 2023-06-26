#include <stdio.h>
#include <string.h>

#include "keyword.h"

// binary search for a word in array of structs key of size n
// returns pointer to element type key if found or NULL if not found
key *binary(char *word, key tab[], int n)
{

    // condition to store comparison between word and keyword in struct pointed to
    // by mid to reuse for else if test
    int cond;

    // pointers to start, end and middle elements of sorted array
    key *low, *high, *mid;
    // low = &tab[0];
    low = tab;
    high = &tab[n - 1];

    // low is now pointing to first element whilee high to last element

    while (low <= high)
    {
        /*we can not add 2 pointers so to get pointer to middle element
        we divide 2 pointers high and low to get an integer size of the array minus 1 element in bytes
        and divide int by 2 to go to the half then add pointer low to int half to get pointer to middle element*/
        mid = low + (high - low) / 2;
        // compare string word with value of member keyword in midle struct pointed to by mid
        // assign return value to cond, compare assignement residual value to 0
        if ((cond = strcmp(word, mid->keyword)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }

    return NULL;
}