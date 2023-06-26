#include <stdio.h>
#include <ctype.h>

/* Use redirections for input and output
K&R 1978 C7
program maps its input to lower case

prog <infile (e.g. ./char <a.txt)
gets input from file instead of default user terminal (stdin)

prog >outfile (e.g. ./char >a.txt)
redirects output to file instead of default user terminal (stdout)

otherprog | prog (e.g. ./char | ./char1)
Through piping standard input for prog comes from the standard output of otherprog */

/*To convert multiple files, use utility cat to collect the files:
cat file1 file2 ... | lower >output
e.g. cat hash1.c | ./lower >a.txt
*/
int main(void)
{
    int c;

    while ((c = getchar()) != EOF)
        // printf("%c", c);
        putchar(isupper(c) ? tolower(c) : c);
}