#include <stdio.h>

/* Write a function that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits
unchanged */

// p starts at 0 (unit's digit p = 0)
unsigned int setbits(unsigned int x, int p, int n, unsigned int y) {

    // Rightmost n bits of y
    //unsigned int righty = y & ~(~0 << n);

    return ((((~0 << n) | (y & (~(~0 << n)))) << (p-n+1)) & (x | ((~(~0 << n)) << (p-n+1))));

}

int main () {

    int a = 0b00001100111100000000000000000000;
    int b = 0b00000000000000000000000001111111;
 
    printf("%x\n", setbits(a,15, 7, b));

}
