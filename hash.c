#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Table-lookup with hash table
// as per K&R 1978 C6

#define HASHSIZE 100

// Define data type struct alias node to store name, definition and next
typedef struct node
{
    char *name;
    char *definition;
    struct node *next;
} node;

// array of pointers to nodes
node *hashtab[HASHSIZE];

int hash(char *s);
node *lookup(char *s);
node *install(char *n, char *d);
void free_list(node *head);
void free_table(void);
void print_table(void);

int main(void)
{
    node *np;
    // install names and definitions
    np = install("language", "C");
    install("day", "Monday");
    install("month", "January");
    if (np != NULL)
        printf("found definition %s for name %s\n", np->definition, np->name);
    np = install("language", "Python");
    if (np != NULL)
        printf("found definition %s for name %s\n", np->definition, np->name);

    // print full table
    print_table();

    // free table
    free_table();
}

// Hash function calculates sum of char values modulo array size
// returns index of hashtable where to search/insert name s
int hash(char *s)
{
    int hashval;
    for (hashval = 0; *s != '\0'; s++)
    {
        hashval += *s;
    }
    return hashval % HASHSIZE;
}

// search for name s in hash table and return pointer to node
// containing name s, or NULL if not found
node *lookup(char *s)
{
    // set pointer to value of element array at index returned by hash
    node *np = hashtab[hash(s)];

    // search singly linked list pointed to by element array
    // for node including name till found or end and return np
    while (np != NULL)
    {
        // Compare strings
        if (strcmp(s, np->name) == 0) // found so break
            break;
        // not found so reset np to point to next node in list
        np = np->next;
    }
    // return np wich is either NULL or pointing to a node
    return np;
}

// install in hash table name n with definition d
node *install(char *n, char *d)
{
    // search if already there
    node *p;
    char *np;
    char *dp;
    int hashval;

    // not in the hash table yet
    if ((p = lookup(n)) == NULL)
    {
        // allocate memory for struct node and for chars of s and t + NULL terminator
        // cast into expected pointer returned value of malloc
        // error check for memory allocation
        p = (node *)malloc(sizeof(node));
        if (p == NULL)
            return NULL;
        np = (char *)malloc(strlen(n) + 1);
        if (np == NULL)
            return NULL;

        // copy into dedicated space pointed to by np and store np into member name
        strcpy(np, n);
        // set new node member values name to point to newly allocated space
        // where chars were copied into from n and next to first node in corresponding linked list
        p->name = np;

        // insert new node at the beginning of list at index hashval
        hashval = hash(p->name);
        p->next = hashtab[hashval];
        hashtab[hashval] = p;
    }
    // already there so remove previous definition
    else
    {
        free(p->definition);
    }

    // add new definition
    dp = (char *)malloc(strlen(d) + 1);
    if (dp == NULL)
        return NULL;
    strcpy(dp, d);
    p->definition = dp;

    return p;
}

// frees linked list starting with hash table element
void free_list(node *head)
{
    // Base case for reaching end of the list
    if (head == NULL)
    {
        return;
    }

    // Destroy rest of the list then free my members, then free me
    free_list(head->next);

    free(head->name);
    free(head->definition);

    free(head);
}

// frees hash table using free_list
void free_table(void)
{
    for (int i = 0; i < HASHSIZE; i++)
    {
        free_list(hashtab[i]);
    }
}

// print table definitions
void print_table(void)
{
    node *p;
    printf("\nTable defintions \n");
    for (int i = 0; i < HASHSIZE; i++)
        for (p = hashtab[i]; p != NULL; p = p->next)
            printf("%s : %s\n", p->name, p->definition);
}