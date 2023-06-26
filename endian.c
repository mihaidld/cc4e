#include <stdio.h>

// https://www.cc4e.com/ endianness K&R 1978 C2
int main(void)
{
    // allocate 12 bytes for char array
    char s[] = "Hello world";
    // take same storage and pretend it's an integer array
    int *si = (int *)&s;

    /* take same storage and pretend it's an integer array
     characters are stuck into 4 byte integers in a little endian way
     (least significant byte at the left at lowest address)

     Storing chars:
     smaller address        ->      higher address
     address a address a+1 address a+2 address a+3
     H         e           l           l
     48        65          6c          6c


     Reading 4 bytes of int Intel x86 little endian processor
     least signigicant bytes        <-  most signigicant bytes

     assumes least significant bytes are the left and most significant bytes are at the right
     so number must be 6c6c6548
     */
    printf(" l l e H  o w - o 00 d l r\n");
    // print each int as hex number with each field of min width 8 spaces using 0 padding
    printf("%08x %08x %08x\n\n", si[0], si[1], si[2]);

    // Easy byte Access with C using chars to get 'e'
    printf("%c %08x\n\n", s[1], s[1]); // get 2nd char of char array

    // Multi-step access char 'e' using chars packed in integer (like words before C), mask and shifting
    int mask, masked, ch;
    // 1 Make mask 8 bits of 1's 00000000 00000000 00000000 11111111 left shifted by 8 positions 00000000 00000000 11111111 00000000
    // or 0000ff00
    mask = 0xff << 8;
    printf("%08x\n", mask);
    // 2 mask out char 'e' by hiding all others bits of first int (make them 0) except for the 8 bits corresponding to char 'e' with & (bitwise and)
    masked = si[0] & mask;
    printf("%08x\n", masked);

    // 3 get char in wrong position (above 255) by shifting back 8 positions to right 00006500 -> 00000065
    ch = masked >> 8;
    printf("%c %08x\n", ch, ch);

    // Other direction int 101 (hex 65) is stored 65 00 00 00
    int i = 0x65;
    char *pc = (char *)&i;
    printf("int i %08x's 4 bytes stored as characters are %02x %02x %02x %02x\n", i, *pc, *(pc + 1), *(pc + 2), *(pc + 3));
}