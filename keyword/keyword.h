#define MAXWORD 20
#define LETTER 'a'
#define DIGIT '0'

// structure to encapsulate C keyword and its counter
typedef struct
{
    char *keyword;
    int keycount;
} key;

// prototypes
int getword(char *w, int lim);
int binary(char *word, key tab[], int n);
int getch(void);
void ungetch(int c);