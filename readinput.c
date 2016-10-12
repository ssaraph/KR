#include <stdio.h>
#include <ctype.h> // For isalpha

// Read from fin up to maxlines number of lines into char *lines[].
int readlines(FILE *fin, char *lines[], int maxlines) {

    int nlines = 0;
    int lineSize;
    size_t lineCap = 0;  // size_t is just unsigned long

    // getline returns the number of characters written to the buffer, excluding '\0'.
    // See man page for getline. It allocates more space for the line if necessary.
    // Line capacity is 0 for each line since we haven't allocated space for any line.
    while ((nlines < maxlines) && ((lineSize = getline(&lines[nlines], &lineCap, fin)) > 0)) {
	nlines += 1;
    }

    if (nlines == maxlines) {
	fprintf(stderr, "Warning: max number of input lines reached. Ignoring further input.\n");
    }
    return nlines;
}

// Read from fin up to max number of ints into data[].
int readints(FILE *fin, int data[], int max) {

    int nints = 0;
    
    while((nints < max) && (fscanf(fin, "%d", data+nints) > 0)){
	nints += 1;
    }

    if (nints == max) {
	fprintf(stderr, "Warning: max number of input integers reached. Ignoring further input.\n");
    }
    return nints;
}

// I am considering words to be continuous strings of alphabetic characters.
// Returns length of word, or EOF. This can be changed with the definition of a word.
// Note: char *word should have at least maxlen+1 spaces. (For '\0').
int getword(FILE *fin, char *word, unsigned int maxlen) {
    
    int c;
    unsigned int i = 0;
    
    // Skip nonalpha
    while (!isalpha(c = getc(fin)) && (c != EOF))
    	;

    if (c == EOF) {
	return EOF;
    }
    else {
	*word++ = c;
	i++;
    }
    while (isalpha(c = getc(fin))) {  		// If the word is too long, keep reading until the end of the word
	if (i < maxlen) {			// but only consider the efirst part of it as a word.
	    *word++ = c;
	}
	i++;
    }
    ungetc(c, fin);
    *word = '\0';

    return i;
}
