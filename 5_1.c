#include <stdio.h>
#include <ctype.h> // isspace, isdigit, etc

// Get next integer from input into *pn
int getint(int *pn) {

    int c, c2, sign;

    while(isspace(c = getc(stdin)))	// Skip whitespace
    	;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        // Next token is not a number
    	ungetc(c, stdin);
	return 0; 			// Indicates not a number
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
	c2 = getc(stdin);
	if (!isdigit(c2)) {
	    ungetc(c2, stdin);
	    ungetc(c, stdin);
	    return 0;
	}
	else {
	    c = c2;
	}
    }

    int flag = 0;

    for(*pn = 0; isdigit(c); c = getc(stdin)) {
	*pn = 10 * *pn + (c - '0');
	flag = 1;
    }
    *pn *= sign;

    if (c != EOF) {
	ungetc(c, stdin);
    }
    return flag;

}

int main() {

    int n;

    while (getint(&n) > 0) {
	printf("%d\n", n);
    }
}
