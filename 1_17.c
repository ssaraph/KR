#include <stdio.h>
#define FILTERSIZE 5 // Only print lines with length >= FILTERSIZE
#define BUFSIZE 80

// Program prints input lines of length exceeding BUFSIZE

void filterInput();

int main() {

    filterInput();

}

void filterInput() {

    char buffer[BUFSIZE];
    int c = 0;
    int i;
    int bufExceeded = 0;

    do {
        i = 0;
        while ((i < BUFSIZE-1) && ((c = getchar()) != '\n') && (c != EOF)) {
	    buffer[i] = c;
	    i = i + 1;
        }
        if (c == '\n') {
	    buffer[i] = c;
	    buffer[i+1] = '\0'; // Null terminate the character array
	    if ((bufExceeded) || (i >= FILTERSIZE)) {
	        printf("%s", buffer);
	        bufExceeded = 0;
	    }
        }
        else if (i >= BUFSIZE-1) {
	    buffer[i] = '\0';
	    bufExceeded = 1;
	    printf("%s", buffer);
        }
    } while (c != EOF);
}
