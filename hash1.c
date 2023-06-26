#include <stdio.h>
#include <stdlib.h>

const int LONGEST_WORD = 50;
const int NUMBER_OF_BUCKETS = 26;

// Define data type struct alias node
typedef struct node
{
    char word[LONGEST_WORD + 1];
    struct node *next;
}
node;

int main(void)
{
    node *hash_table[NUMBER_OF_BUCKETS];
}