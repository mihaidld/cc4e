#include <stdio.h>
#define MAX_LINE 1000

int get_line(char s[], int lim);
int index(char s[], char t[]);

/* search location of substring in string K&R 1978 C5
allow two optional arguments:
-x (for "except") to signal the inversion,
-n ("number") to request line numbering, then the command
the pattern must be the last argument
e.g. find -x -n the or find -nx the
*/
int main(int argc, char *argv[])
{
    // array of chars to store line copied from input
    char line[MAX_LINE], *s;
    // counter for line number
    long lineno = 0;
    // variables as boolean for checking flag options
    int use_except = 0;
    int use_number = 0;

    // Get option values from command line arguments
    /*to check use of the flags inside all command line arguments
    we decrement argc while it is still greater than 0 since we are not
    interested in argv[0] (the name of the program).

    In the same time we access elements of argv using pointer arithmetic
    (*++argv)[0] or **++argv
    increment argv to point to next element in array of pointers,
    acces the pointer pointed to by new argv, then access first char
    which must be '-' for a flag

    argv is a pointer to a pointer so argv++ offsets by 8 bytes (size of pointer)
    to point to next pointer
    argv[0] or *argv is a pointer to char so argv[0]++ offsets by 1 byte (size of char)
    to point to next char
    */
    while (--argc > 0 && (*++argv)[0] == '-')
    {
        // for each argument starting with '-' check all chars by setting s
        // to point to next char after '-' and increment after
        // till it points to end of argument ('\0')
        for (s = argv[0] + 1; *s != '\0'; s++)
        {
            // based on char flag update variables
            switch (*s)
            {
            case 'x':
                use_except = 1;
                break;
            case 'n':
                use_number = 1;
                break;
            // if not x or n alert and set argc to 0 to stop current loop
            // and not execute code below
            default:
                printf("find: illegal option %c.\n", *s);
                argc = 0;
                break;
            }
        }
    }

    // if all goes well argc should reach 1 and argv is pointing now to last string: the pattern
    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
    {
        // while we read lines from input (0 if no input on that line)
        while (get_line(line, MAX_LINE) > 0)
        {
            lineno++;
            /* if line contains pattern index will return a positive number
            so comparison expression will evaluate to 1, if not to 0
            we print the line if use_except hasn't same value as has_pattern
            int has_pattern = index(line, argv[1]) >= 0 */
            if ((index(line, *argv) >= 0) != use_except)
            {
                // if flag to print also line number
                if (use_number)
                    printf("%li: ", lineno);
                printf("%s", line);
            }
        }
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