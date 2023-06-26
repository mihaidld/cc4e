#include <stdio.h>
#include <cs50.h>

// print a number recursively as a character string
// K&R 1978 C4
void printd(int num);

int main(void)
{
    int n;
    printf("Num: ");
    scanf("%i", &n);
    printf("Num entered: ");
    printd(n);
    printf("\n");
}

void printd(int num)
{
    // handle sign: put char - and change num to positive
    if (num < 0)
    {
        putchar('-');
        num = -num;
    }

    // base case reached when num reduced by factor 10 decreases to 0
    if (num == 0)
    {
        return;
    }

    // call printd for leading digits thenprint trailing digit
    // print all characters except for last one
    printd(num / 10);

    // print last character = remainder to 10 + '0'
    printf("%c", num % 10 + '0');
}