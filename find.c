#include <stdio.h>
#define MAX_LINE 1000

// search location of substring in string K&R 1978 C5

int get_line(char s[], int lim);
int index(char s[], char t[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: find pattern\n");
        return 1;
    }

    // array of chars to store line copied from input
    char line[MAX_LINE];

    // while we read lines from input (0 if no input on that line)
    while (get_line(line, MAX_LINE) > 0)
    {
        // if line contains pattern "the" we print it
        if (index(line, argv[1]) >= 0)
            printf("%s", line);
    }
}

// get line from input and copy it into array line and return no. of chars
// if no input only s[0] = '\0' and 0 returned
// like getline in stdio.h
int get_line(char s[], int lim)
{
    int i, c;
    // iterate till lim - 1 to leave place for NULL
    // use c to store char from input as long as we didn't reach EOF or newline
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    // if stopped because of new line copy newline and increment i
    if (c == '\n')
        s[i++] = c;
    // add NULL at the end
    s[i] = '\0';

    return i;
}

// search for location of substring t inside string s or return -1 if not found
// like index in stdio.h for first occurence of char c in string s
int index(char s[], char t[])
{
    int i, j, k;
    // iterate over chars in string s till we reach NULL
    for (i = 0; s[i] != '\0'; i++)
    {
        // iterate over chars in t and compare chars in t with chars in s starting with i that we reached
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        // if we reach NULL in t that means we stopped the loop after all chars from t matched and reached end of t
        if (t[k] == '\0')
            // return position i of first match of substring
            return i;
    }

    return -1;
}