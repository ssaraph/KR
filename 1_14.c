#include <stdio.h>
#define IN 1
#define OUT 0

int main() {

    int c;
    int lc = 0; // Letter count

    int letters[26]; // Individual letter counts
    float frequencies[26]; // Letter frequencies

    int i, j;
    // Initialize letters
    for(i = 0; i < 26; i++) {
	letters[i] = 0;
	frequencies[i] = 0.0;
    }

    while ((c = getchar()) != EOF) {
        // Uppercase ascii
	if ((c < 91) && (c >= 65)) {
	    lc += 1;
	    letters[c-65] += 1;
	}
	// Lowercase ascii
	else if ((c < 124) && (c >= 97)) {
	    lc += 1;
	    letters[c-97] += 1;
	}
    }

    // Calculate frequencies
    for(i = 0; i < 26; i++) {
	frequencies[i] = (letters[i] * 1.0)/lc; // Convert to float
    }

    for (i = 0; i < 26; i++) {
	printf("%c ", i+65);
	printf("%.4f: ", frequencies[i]);
	for (j = 0; j < frequencies[i]*100.0; j++) {
	    printf("*");
	}
	printf("\n");
    }

}
