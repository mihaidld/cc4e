#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 20
#define LETTER 'a'
#define DIGIT '0'
#define BUFSIZE 100

// Count the occurrences of all the words in some input
// as per K&R 1978 C6

/* Binary Search Tree  = root is larger than left child and smaller than right child
To find out whether a new word is already in the tree, one starts at the root
and compares the new word to the word stored at that node.
If they match, the question is answered affirmatively.
If the new word is less than the tree word, the search continues at the left child;
otherwise the right child is investigated.
If there is no child in the required direction, the new word is not in the tree,
and in fact the proper place for it to be is the missing child. */

typedef struct _node
{
    char *word; // pointer to word
    int count;  // counter
    struct _node *left;
    struct _node *right;
} node;

// a shared buffer
static char buf[BUFSIZE];
// buffer position records position of current char in the buffer
// next free position in buffer
static int bufp = 0;

node *tree(node *p, char *w);
void print_tree(node *p);
void free_tree(node *p);
int getword(char *w, int lim);
int type(int c);
int getch(void);
void ungetch(int c);

// word frequency count
int main(void)
{
    // Create empty tree
    node *root = NULL;

    // store chars from getword and type returned
    char word[MAXWORD];
    int t;

    // read words with getword, then check and install them in the tree with tree
    while ((t = getword(word, MAXWORD)) != EOF)
        if (t == LETTER)
            // assign pointer returned by tree to root
            root = tree(root, word);

    // print tree
    print_tree(root);

    // Free tree
    free_tree(root);

    return 0;
}

// check for word w in tree p, if found increment count inside node
// if not add node with initial count to 1
node *tree(node *p, char *w)
{
    // store result of comparison between p->word and w
    int cond;
    // pointer to text
    char *pc;

    /* Base cases: the word either matches something already in the tree
    (in which case the count is incremented),
    or a null pointer is encountered, indicating that a node must be created
    and added to the tree. If a new node is created, tree returns a pointer to it,
    which is installed in the parent node */

    // we reached a base case NULL so add node to the tree
    if (p == NULL)
    {
        // allocate memory for struct node and for chars of w + NULL terminator
        // cast into expected pointer returned value of malloc
        p = (node *)malloc(sizeof(node));
        pc = (char *)malloc(strlen(w) + 1);

        /* to handle errors for available space we need that root be global variable
        updated by main, but also accessible to tree in order to call inside
        free_tree(root) is malloc returns NULL */

        // copy w into dedicated space pointed to by pc and store pc into member word
        strcpy(pc, w);
        p->word = pc;

        // initialize count to 1 and left and child pointers
        p->count = 1;
        p->left = p->right = NULL;
    }
    // set cond and if word searched is same as one in node pointed to by p increment its count
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        p->count++;
    }
    // if word searched is before update left subtree to take into account w
    // either find it and increment or create new node
    else if (cond < 0)
    {
        p->left = tree(p->left, w);
    }
    // if word searched is after update right subtree
    else
    {
        p->right = tree(p->right, w);
    }

    return p;
}

void print_tree(node *p)
{
    // Base case of recursion, we reached a leaf
    if (p == NULL)
    {
        return;
    }
    // Print left subtree (and its children which are before than p->word)
    print_tree(p->left);

    // Print p->word
    printf("%4i %s\n", p->count, p->word);

    // Print right subtree (and its children which are after than p->word)
    print_tree(p->right);
}

void free_tree(node *p)
{
    if (p == NULL)
    {
        return;
    }
    // free left child (and recursively all of its descendants), then right child, word then free me
    free_tree(p->left);
    free_tree(p->right);
    free(p->word);
    free(p);
}

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

// delivers the next input character to be considered
int getch(void)
{
    // reads from the buffer if there is anything there and
    // decrements buffer position afterwards
    // or calls getchar if the buffer is empty
    return (bufp > 0 ? buf[--bufp] : getchar());
}

// remembers the characters put back on the input,
// so that subsequent calls to getch will return them before reading new input
// puts the pushed-back characters into buffer
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}