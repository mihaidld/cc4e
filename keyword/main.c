#include <stdio.h>
#include "keyword.h"

/* number of keywords is the array size divided by the size of one array element*/
#define NKEYS (sizeof(keytable) / sizeof(key)) // number of C keywords

// array of struct key with C keywords and their count occurence
// each struct initialized in braces
key keytable[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}};

// count C keywords K&R 1978 C6
int main(void)
{
    // store index of found keyword in array keytable
    int n;

    // store type of word from input
    int t;

    // store word retrieved with getword to be searched in keytab
    char word[MAXWORD];

    /* getword copies word by word from input into array of chars word and returns type of the word
    if found a word returns LETTER */
    while ((t = getword(word, MAXWORD)) != EOF)
        if (t == LETTER)
            /*binary search for word in keytable and get its index
            if found (>= 0) increment keyCount for this keyword */
            if ((n = binary(word, keytable, NKEYS)) >= 0)
                keytable[n].keycount++;

    // print count results for each keyword present
    for (n = 0; n < NKEYS; n++)
        if (keytable[n].keycount > 0)
            printf("%4i %s\n", keytable[n].keycount, keytable[n].keyword);
}