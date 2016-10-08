#include <stdio.h>

// Count blanks, tabs, newlines

int main() {

    int c, nblanks, ntabs, nnlines;
    nblanks = 0;
    ntabs = 0;
    nnlines = 0;
    while((c = getchar()) != EOF) {
	if (c == '\n') nnlines++;
	else if (c == '\t') ntabs++;
	else if (c == ' ') nblanks++;
	else {
	    continue;
	}
    }

    printf("blanks:%6d\ttabs:%6d\tnewlines:%6d\n", nblanks, ntabs, nnlines); 
}
