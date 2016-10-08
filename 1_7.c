#include <stdio.h>

// EOF is a "symbolic constant" i.e. a macro defined in stdio.h.

void ex1(void);
void ex2(void);

int main() {

    printf("%d\n", EOF);
    ex1();
}

void ex1() {

    int c;
    // getchar reads from stdin
    c = getchar();
    while (c != EOF) {
	// putchar writes to stdin
	putchar(c);
	c = getchar();
    }
}

// NOTE: Expressions have values, including assignment exressions.
// The value of an assigment expression is the value that is assigned to
// the LHS. Hence ex2 does the same thing as ex1. 

void ex2() {

    int c;
    while ((c = getchar()) != EOF) {
	putchar(c);
    }
}
