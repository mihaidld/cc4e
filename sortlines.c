#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINES 100     // max lines to be sorted
#define MAX_LINE 1000 // max length of a line

int get_line(char s[], int lim);
void sort(char *arr[], int len);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void freelines(char *lineptr[], int nlines);

/* sort a set of text lines into alphabetic order
 * (like UNIX utility sort which prints to output sorted lines
 * without changing the input file e.g. sort file.txt)
 * based on K&R 1978 C5
 * read all the lines of input, sort them, print them in order */
int main(void)
{
    // array of pointers, each one pointing to a text line
    char *lineptr[LINES];

    // number of lines read
    int nlines;

    /*set nlines to number of lines read
    if positive, sort array of pointers, print them sorted and free memory
    if negative (-1) print error message*/
    if ((nlines = readlines(lineptr, LINES)) >= 0)
    {
        sort(lineptr, nlines);
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

/* In early stages, far-apart elements are compared (largest gap is half the count of elements so compare and swap
 * first to middle, second to middle + 1...),
 * rather than adjacent ones, as in simple interchange sorts (e.g. bubble sort).
 * This tends to eliminate large amounts of disorder quickly,
 * so later stages have less work to do.
 * The interval between compared elements is gradually decreased to one
 * (at every outter loop iteration split in half),
 * at which point the sort effectively becomes an adjacent interchange method. */
void sort(char *array[], int len)
{
    // Shell sort
    int gap, i, j;
    // temp must be same type as elements: char pointer
    char *temp;

    // 3 nested loops
    /* The outermost loop controls the gap between compared elements,
    shrinking it from length / 2 by a factor of two each pass until it becomes zero.*/
    for (gap = len / 2; gap > 0; gap /= 2)
        // The middle loop compares each pair of elements that is separated by gap;
        for (i = gap; i < len; i++)
            /*the innermost loop reverses any that are out of order.
            Since gap is eventually reduced to one, all elements are eventually ordered correctly.
            j starts at 0 so compare strings array[0] with array[0 + gap],
            then 1 array[1] with array[1 + gap]...*/
            for (j = i - gap; j >= 0; j -= gap)
            {
                // if string 1 is alphabetically before or same as string 2
                // no need to swap so break loop, if not swap pointers
                if (strcmp(array[j], array[j + gap]) <= 0)
                    break;
                temp = array[j];
                array[j] = array[j + gap];
                array[j + gap] = temp;
            }
}