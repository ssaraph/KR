#include <stdio.h>

int main() {

    int space = 0;
    int c;
    while ((c = getchar()) != EOF) {
	if (c == ' ') {
	    if (space == 1) {
		continue;
	    }
	    space = 1;
	}
	else {
	    space = 0;
	}
	putchar(c);
    }
}
