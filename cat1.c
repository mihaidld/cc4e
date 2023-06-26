#include <stdio.h>
#include <stdlib.h>

/*K&R 1978 C7 implementation cat to concatenate files.
if there are command-line arguments, they are processed in order.
If there are no arguments, the standard input is processed
Error handling with error message sent to stderr
*/

void file_copy(FILE *fp);

int main(int argc, char *argv[])
{
    // store pointer to file
    FILE *fp;

    // no command line arguments, get input from stdin (enter into terminal)
    if (argc == 1)
        file_copy(stdin);
    else
        // loop for all command line arguments file1 file2 ...
        while (--argc > 0)
            /*increment argv to point to next char pointer in the array
            and get that char pointer pointed to by updated argv
            try to open file specified at command line argument n in read mode */
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                /* First solution: if returned pointer is NULL print error message and break */
                // printf("cat: can't open %s\n", *argv);
                // break;

                /* Better solution: if program output is redirected to another file
                or is piped to become input for another program
                the error message printed can be overlooked since
                it doesn't go to stdout anymore (viewed in the terminal)
                With stderr diagnostic output produced by fprintf goes onto stderr,
                so it finds its way to the user's terminal instead of disappearing
                down a pipeline or into an output file

                e.g. ./cat1 cat.c char.c char1.c | ../week5/lower>a.txt
                only contents from valid files cat.c and char.c are copied onto stdout
                which is piped into program lower with output redirected onto file a.txt
                error message for char1.c goes onto stderr and printed to terminal:
                cat: can't open char1.c*/
                fprintf(stderr, "cat: can't open %s\n", *argv);
                // exit program with status 1 (not ok) which can be tested by next program (thisprog | nextprog)
                // exit also calls fclose for each open output file, to flush out any buffered output
                exit(1);
            }
            else
            {
                // copy input from file pointer fp into stdout
                file_copy(fp);
                printf("\n");
                // close connection to file opened freeing the file pointer for another file.
                fclose(fp);
            }
    // exit program with status 0
    exit(0);
}

void file_copy(FILE *fp)
{
    // store character to read into and write from
    int c;

    // get next char from file pointer fp, as long as we don't reach EOF
    // then put char c in stdout file pointer (display on terminal)
    while ((c = getc(fp)) != EOF)
        putc(c, stdout);
}