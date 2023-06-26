#include <stdio.h>
#include <ctype.h>
#include <string.h>

int atoi(char s[]);
double atof(char s[]);
int htoi(char s[]);
void itoa(int n, char s[]);
void itoh(int n, char s[]);
void itob(int n, char s[]);
void reverse(char t[]);
void reverse_recursive(char t[]);
void itoa_recursive(int n, char s[]);

int main(void)
{
    char s[] = "    -12345";
    int i = atoi(s);
    printf("decimal string s %s to int %i\n", s, i);

    char s1[] = "10a";
    int j = htoi(s1);
    printf("hex string s1 %s to int %i\n", s1, j);

    char s2[10];
    itoa(i, s2);
    printf("int i %i to decimal string %s\n", i, s2);

    char s3[10];
    itoh(j, s3);
    printf("int j %i to hex string %s\n", j, s3);

    char s4[10];
    itob(j, s4);
    printf("int j %i to binary string %s\n", j, s4);

    char s5[] = "    -12.345";
    double d = atof(s5);
    printf("decimal string s %s to double %f\n", s5, d);

    char s6[10];
    itoa_recursive(i, s6);
    printf("int i %i recursively to decimal string %s\n", i, s6);

    char t[] = "abcd";
    reverse(t);
    printf("reversed abcd is %s\n", t);
    char t1[] = "abcd";
    reverse_recursive(t1);
    printf("reversed recursively abcd is %s\n", t1);

    printf("%.5s\n", "abreviation");
}

// converts a string of digits into its numeric equivalent.
// as per K & R 1978 chap 3
// copes with optional leading white space and an optional + or - sign
int atoi(char s[])
{
    // n = stores the corresponding integer that will be returned
    int i, n, sign;
    // skip left whitespace
    for (i = 0; s[i] == ' ' || s[i] == '\t' || s[i] == '\n'; i++)
        ;

    // sign if not present, by default is positive 1
    sign = 1;

    // s[i] is now not a whitespace, can be +, - or directly a digit
    // if a sign update sign and increment afterwards i using postfix s[i++]
    if (s[i] == '+' || s[i] == '-')
        sign = s[i++] == '+' ? 1 : -1;

    // check for digit characters
    // if found digit multiply number already found by 10 and add integer corresponding to character (e.g. '1' - '0' == 1)
    for (n = 0; s[i] >= '0' && s[i] <= '9'; i++)
    {
        n = n * 10 + s[i] - '0';
    }

    return sign * n;
}

//  converts a string of hexadecimal digits into its equivalent integer value.
// The allowable digits are 0 through 9, a through f, and A through F.
int htoi(char s[])
{
    int n = 0;

    // check for hex characters
    // if found hex multiply number already found by 16 and add integer corresponding to character (e.g. '1' - '0' == 1)
    for (int i = 0; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'); i++)
    {
        // if decimal digit
        if (s[i] >= '0' && s[i] <= '9')
        {
            n = n * 16 + s[i] - '0';
        }
        // else if (s[i] >= 'a' && s[i] <= 'f')
        // {
        //     n = n * 16 + s[i] - 'a' + 10;
        // }
        // else
        // {
        //     n = n * 16 + s[i] - 'A' + 10;
        // }
        // if letter digit a - f, convert to lower and add 10 and difference to lower 'a'
        else
        {
            n = n * 16 + tolower(s[i]) - 'a' + 10;
        }
    }

    return n;
}

// converts a number to a character string (the inverse of atoi)
void itoa(int n, char s[])
{
    int i, sign;
    // record the sign as n (positive or negative) and check if sign is negative
    // if so make n positive
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    // generate string backwards from int by looking at int digits starting from the last
    do
    {
        // get next digit as char set to remainder of division by 10 converted into corresponding char
        // then increment i
        s[i++] = n % 10 + '0';
    }
    // in the test reduce n by factor 10 and check if new n > 0
    while ((n /= 10) > 0);

    // add '-' sign if negative int
    // then increment i
    if (sign < 0)
        s[i++] = '-';
    // add NULL terminating
    s[i] = '\0';

    // reverse string
    reverse(s);
}

// converts a number to a character string (the inverse of atoi) recursively
// K&R 1978 Exercise 4-7
void itoa_recursive(int n, char s[])
{
    /* static variables remain in existence rather than
    coming and going each time the function is activated.
    Internal static variables provide private, permanent storage within a single function.*/

    // define i as static so it can be retain its value in the scope of the function
    // during next function calls
    static int i = 0;
    // get the sign and if is negative set first char to '-' and
    // make n positive
    if (n < 0)
    {
        n = -n;
        s[i++] = '-';
    }
    // base case reached when n reduced by factor 10 decreases to 0
    if (n == 0)
    {
        return;
    }

    // call itself for leading digits then set trailing digit and NULL
    // set all characters of s except for last one
    itoa_recursive(n / 10, s);

    // print last character = remainder to 10 + '0'
    s[i++] = n % 10 + '0';
    s[i] = '\0';
}

// converts a number to a character hex string (the inverse of htoi)
void itoh(int n, char s[])
{
    int i, sign;
    // record the sign as n (positive or negative) and check if sign is negative
    // if so make n positive
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    // generate string backwards from int by looking at int digits starting from the last
    char *digits = "0123456789abcdef";
    do
    {
        // get next digit as char set to remainder of division by 16 converted into corresponding char
        // then increment i
        s[i++] = digits[n % 16];
    }
    // in the test reduce n by factor 16 and check if new n > 0
    while ((n /= 16) > 0);

    // add '-' sign if negative int
    // then increment i
    if (sign < 0)
        s[i++] = '-';
    // add NULL terminating
    s[i] = '\0';

    // reverse string
    reverse(s);
}

// converts a number to a character binary string (the inverse of btoi)
void itob(int n, char s[])
{
    int i, sign;
    // record the sign as n (positive or negative) and check if sign is negative
    // if so make n positive
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    // generate string backwards from int by looking at int digits starting from the last
    do
    {
        // get next digit as char set to remainder of division by 2 converted into corresponding char
        // then increment i
        s[i++] = n % 2 + '0';
    }
    // in the test reduce n by factor 2 and check if new n > 0
    while ((n /= 2) > 0);

    // add '-' sign if negative int
    // then increment i
    if (sign < 0)
        s[i++] = '-';
    // add NULL terminating
    s[i] = '\0';

    // reverse string
    reverse(s);
}

// reverse string
void reverse(char t[])
{
    // char to store temporary value for swap
    char c;

    // loop till the middle of the char array to swap chars simmetrical on each side
    for (int i = 0, n = strlen(t); i < n / 2; i++)
    {
        c = t[i];
        t[i] = t[n - 1 - i];
        t[n - 1 - i] = c;
    }
    return;
}

// reverse string recursively
// K&R 1978 Exercise 4-8
void reverse_recursive(char t[])
{
    // define i as static so it can be retain its value in the scope of the function
    // during next function calls
    static int i = 0;
    int n = strlen(t);

    // base case when i reaches half of string's length
    if (i >= n / 2)
    {
        return;
    }

    // swap chars at indices i and n - 1 - i then increment i for next function call
    char c;

    c = t[i];
    t[i] = t[n - 1 - i];
    t[n - 1 - i] = c;

    i++;

    // call itself for next i
    reverse_recursive(t);
}

// converts a string of digits into its double-precision floating point number equivalent.
// as per K & R 1978 chap 4
// copes with optional leading white space, an optional + or - sign
// and decimal point, and the presence or absence of either integer part or fractional part.
double atof(char s[])
{
    // val stores the accumulated number (without fractional part)
    // power stores 10 ^ number of digits after .
    double val, power;
    int i, sign;
    // skip left whitespace
    for (i = 0; s[i] == ' ' || s[i] == '\t' || s[i] == '\n'; i++)
        ;

    // sign if not present, by default is positive 1
    sign = 1;

    // s[i] is now not a whitespace, can be +, - or directly a digit
    // if a sign update sign and increment afterwards i using postfix s[i++]
    if (s[i] == '+' || s[i] == '-')
        sign = s[i++] == '+' ? 1 : -1;

    // check for digit characters in integer part of the number
    // if found digit multiply number already found by 10 and add integer corresponding to character (e.g. '1' - '0' == 1)
    for (val = 0; s[i] >= '0' && s[i] <= '9'; i++)
    {
        val = val * 10 + s[i] - '0';
    }

    // i was already incremented, check for . delimiter
    // if found just increment i
    if (s[i] == '.')
    {
        i++;
    }
    // check for digit characters in fractional part of the number
    // if found digit multiply number already found by 10 and add integer corresponding to character (e.g. '1' - '0' == 1)
    // in the same time, since we are after the . increase power by factor 10
    for (power = 1; s[i] >= '0' && s[i] <= '9'; i++)
    {
        val = val * 10 + s[i] - '0';
        power *= 10;
    }

    return sign * val / power;
}