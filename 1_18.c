#include <stdio.h>

#define BUFSIZE 1000

/* "Write a program to remove trailing blanks and tabs from each line of input,
    and to delete entirely blank lines */

int getLine(char buffer[], int bufsize);
int processLine(char buffer[], int linesize);

int main() {

    char buffer[BUFSIZE];
    int nc, printFlag;

    while(((nc = getLine(buffer, BUFSIZE)) != 0)) {
	printFlag = processLine(buffer, nc);	
	if (printFlag) {
	    printf("%s", buffer);
	}
    }
}

// Returns number of characters in buffer
int getLine(char buffer[], int bufsize) {

    int c;
    int i;

    // NOTE: Boolean expressions like the one in the test condition for the for loop below are evaluated left to right.
    // Evaluation stops when the result boolean value is known. Order is important in this case (check bufsize first,
    // then read character before checking its value.
    for(i = 0; ((i < bufsize-1) && ((c = getchar()) != EOF) && (c != '\n')); i++) { 
	buffer[i] = c;
    }

    if (c == '\n') {
	buffer[i] = '\n';
	buffer[i+1] = '\0';
	return i;
    }
    else if (i >= bufsize-1) {
	buffer[i] = '\0';
	return i;
    }
    else {
	return 0; // Indiciate EOF
    }
}

// Removes trailing blanks, tabs, and deletes entirely blank lines.
// Return value indicates whether line should be printed.
int processLine(char buffer[], int linesize) {

    int i;
    if (buffer[linesize] == '\n') {
	for(i=linesize-1; (((buffer[i] == '\t') || (buffer[i] == ' ')) && (i >= 0)); i--)
	    ;
	if (i > -1) {
	    buffer[i+1] = '\n';
	    buffer[i+2] = '\0';
	    return 1;
	}
	else {
	    return 0;
	}
    }
    else {
    	// Check if entire line is blank 
	for(i = 0; ((i < linesize) && ((buffer[i] == ' ') || (buffer[i] == '\t'))); i++)
	    ;
	// Line length exceeds bufsize but also contains only blanks so far. Don't know whether to print. (Going to assume line is blank in this case);
	if (i == linesize) {
	    return 0;
	}
	else {
	    return 1;
	}
    }
}

