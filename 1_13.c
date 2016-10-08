#include <stdio.h>
#define IN 1 // Inside of a word
#define OUT 0 // Outside of a word
#define SIZE 12 // Histogram size

int main() {

    int c;
    int state = OUT;

    int wordLen = 0;
    int histogram[SIZE]; //Histogram of word lengths. Last position is for SIZE+.

    int i, j;
    // Initialize histogram
    for(i = 0; i < SIZE; i++) {
	histogram[i] = 0;
    }

    while ((c = getchar()) != EOF) {
	if (c == ' ' || c == '\n' || c == '\t') {
	    if (state == IN) {
	    	state = OUT;
		if (wordLen < SIZE+1) {
		    histogram[wordLen-1] += 1;
		}
		else {
		    histogram[SIZE-1] += 1;	
		}
		wordLen = 0;
	    }
	}
	else {
	    state = IN;	
	    wordLen += 1;
	}
    }

    for(i = 0; i < SIZE; i++) {
	printf("%2d: ", i+1);
	for (j = 0; j < histogram[i]; j++) {
	    printf("*");
	}
	printf("\n");
    }

}
