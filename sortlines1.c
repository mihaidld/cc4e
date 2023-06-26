#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINES 100     // max lines to be sorted
#define MAX_LINE 1000 // max length of a line

int get_line(char s[], int lim);
void sort(char *array[], int len, int (*comp)(), void (*exch)());
int numcmp(char *s1, char *s2);
// Pass argument px as pointer to char pointer or array of pointers
void swap(char **px, char **py);
// void swap(char *px[], char *py[]);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void freelines(char *lineptr[], int nlines);

/* sort a set of text lines
 * optional argument -n: sort the input lines numerically instead of lexicographically.
 * based on K&R 1978 C5
 * pass as  arguments to functions pointers to other functions
 * read all the lines of input, sort them, print them in order */
int main(int argc, char *argv[])
{
    // array of pointers, each one pointing to a text line
    char *lineptr[LINES];

    // number of lines read
    int nlines;

    // use numeric sort by default 0
    // set to 1 if command line argument "-n"
    int numeric = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;

    /* if numeric, sort array of pointers by leading numeric values
    if not sort lexigographically*/
    if ((nlines = readlines(lineptr, LINES)) >= 0)
    {
        if (numeric)
            // numcmp is passed by reference so a pointer to the function, not the function
            sort(lineptr, nlines, numcmp, swap);
        else
            sort(lineptr, nlines, strcmp, swap);

        writelines(lineptr, nlines);
        freelines(lineptr, nlines);
    }
    else
    {
        // no need to free memory in this case in main
        // since it was already done inside readlines
        printf("error: input too big to sort\n");
    }
}

/* get line from input and copy it into array line and return no. of chars
 * if no input only s[0] = '\0' and 0 returned
 * like getline in stdio.h */
int get_line(char s[], int lim)
{
    int i, c;
    // iterate till lim - 1 to leave place for NULL
    // use c to store char from input as long as we didn't reach EOF or newline
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    // if stopped because of newline copy newline and increment i
    if (c == '\n')
        s[i++] = c;
    // add NULL at the end
    s[i] = '\0';

    return i;
}

/* read input lines */
int readlines(char *lineptr[], int maxlines)
{
    // array of chars to store line copied from input
    char line[MAX_LINE];

    // pointer to char to store address of line
    char *p;

    // length of each line
    int len;
    // counter of lines read
    int nlines = 0;

    // while we read lines from input (0 if no input on that line)
    while ((len = get_line(line, MAX_LINE)) > 0)
    {
        // if too many lines were input free memory then return -1
        if (nlines > maxlines)
        {
            freelines(lineptr, nlines);
            return -1;
        }
        /* len is the length of the string including new line, without '\0',
        it's enough to malloc len since before copying line into p we remove the newline,
        p stores pointer to a chunk of len bytes allocated on the heap
        if malloc returns NULL after we already malloc'ed,
        we weren't able to store the latest text line so
        free memory and send signal error -1 */
        else if ((p = malloc(len)) == NULL)
        {
            freelines(lineptr, nlines);
            return -1;
        }
        /* all is fine so replace newline (copied by get_line from input)
        by NULL to indicate the end of a string, copy string from line to p,
        store p in array of pointers and increment nlines*/
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

/* print lines*/
void writelines(char *lineptr[], int nlines)
{
    printf("\nSorted lines:\n");
    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* free memory */
void freelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        free(lineptr[i]);
}

// SHELL SORT (as per K&R 1978 chap 3)

/* pass as arguments pointers to functions:
 * comp is a pointer to a function returning an int */
void sort(char *array[], int len, int (*comp)(), void (*exch)())
{
    int gap, i, j;

    for (gap = len / 2; gap > 0; gap /= 2)
        for (i = gap; i < len; i++)
            for (j = i - gap; j >= 0; j -= gap)
            {
                // *comp accesses the function pointed to by comp
                // inportant parenthessis around (*comp)
                if ((*comp)(array[j], array[j + gap]) <= 0)
                    break;
                /* *exch accesses the function pointed to by exch
                we pass by reference as arguments the address of pointer to char array[j]
                not the pointer directly*/
                (*exch)(&array[j], &array[j + gap]);
            }
}

// compare two strings numerically
int numcmp(char *s1, char *s2)
{
    // convert strings to floats
    double v1 = atof(s1);
    double v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

// interchange pointer values pointed to by px and py
/*arguments are pointers to char pointers*/
void swap(char **px, char **py)
{
    /* temp must be same type as *px: pointer to char.
    Go to the value pointed to by px and get the value stored in array
    at index i which is the address of first char of the string 1.
    Store in temp the address of string 1. Store in array at index i
    the address of string 2, then in array at index j, the address of string 1.
    The values of elements at indices i and j which are pointers to chars
    are swapped.

    px is the address of element of array of pointers at index i 0x789
    *px is char pointer storing the address of string 1 0x123
    string 1 "100" is situated at 0x123,
    py is storing address of element at index j 0x792
    *py stores the address of string 2 "20" situated at 0x456 */
    char *temp = *px;
    // temp is storing now 0x123
    *px = *py;
    // *px is storing 0x134
    *py = temp;
    // *py is 0x123
}

/* px is array of pointers to char
*px is px[0] the value of first element which is pointer to char
char (*px)[] where px is pointer to array of chars or pointer to char
would not work because we pass the address of the pointer to char
and access it inside the function using pointer to ... or array of ... */
// void swap(char *px[], char *py[])
// {
//     char *temp = *px;
//     *px = *py;
//     *py = temp;
// }