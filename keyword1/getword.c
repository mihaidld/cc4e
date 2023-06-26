#include <stdio.h>
#include <ctype.h>
#include "keyword.h"

int type(int c);

/* get next word from input
returns the next "word" from the input, where a word is either a string
of letters and digits beginning with a letter, or a single character.
The type of the object is returned as a function value; it is LETTER
if the token is a word, EOF for end of file, or the character itself if it is non-alphabetic.*/
int getword(char *w, int lim)
{
    // store character and its type
    int c, t;

    // Check for first letter of word, if not letter append NULL char and return char
    if (type(c = *w++ = getch()) != LETTER)
    {
        *w = '\0';
        return c;
    }

    /* loop decrementing lim: first iteration --lim is 19, last iteration 1 (since 0 is false)
    19 iterations since we already occupied first char in w with first letter.
    Last char will be '\0' even if we continue to get letters or digits*/
    while (--lim)
    {
        // Get next char into w, c and check its type
        t = type(c = *w++ = getch());
        if (t != LETTER && t != DIGIT)
        {
            // push c back onto the input since we found a non letter and non digit by calling getch
            // so we put it back for it to be retrived next time with getch
            ungetch(c);
            break;
        }
    };

    /* w is pointing now at next char after non-letter and non-digit if we break
    from loop or at any character after using all chars in word w after end of loop.
    while w - 1 is pointing to that char
    so change it to NULL terminating and return LETTER since we finished the word*/
    *(w - 1) = '\0';

    // w was updated as a side effect, return signal that a word was retrieved in w
    return LETTER;
}

// Get type of char and return LETTER if letter, DIGIT if digit or actual char if other
int type(int c)
{
    if (isalpha(c))
        return LETTER;
    else if (isdigit(c))
        return DIGIT;
    else
        return c;
}