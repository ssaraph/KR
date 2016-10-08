#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void push(double *stack, int *sp, double value);
double pop(double *stack, int *sp);

// Determine if argument is a number
int isNumber(char *arg);
// Determine if argument is an operator (and which operator)
int operator(char *arg);

// As of now, this command line calculator assumes binary operators +, -, *, and /, and floating
// point operands. It doesn't currently check for overflow.
// NOTE: It did not occur to me until after writing this that "*" is used as a wildcard on the command line.
// Cumbersome as it is, enter "\*" for multiply... (I could choose some other character for multiply I suppose).

int main(int argc, char *argv[]) {

    // This is sufficient stack size. (Not necessary).
    double mystack[argc];
    int sp = 0;

    int i;
    double operand1, operand2;

    for(i = 1; i < argc; i++) {
	if (isNumber(argv[i])) {
	    push(mystack, &sp, strtod(argv[i], NULL));
	}
	else {
	    switch (operator(argv[i])) {
	    case 0:  // Addition
	        operand2 = pop(mystack, &sp);
		operand1 = pop(mystack, &sp);
		push(mystack, &sp, operand1+operand2);
	        break;
	    case 1:  // Subtraction 
	        operand2 = pop(mystack, &sp);
		operand1 = pop(mystack, &sp);
		push(mystack, &sp, operand1-operand2);
	        break;
	    case 2:  // Multiplication
	        operand2 = pop(mystack, &sp);
		operand1 = pop(mystack, &sp);
		push(mystack, &sp, operand1*operand2);
	        break;
	    case 3:  // Division
	        operand2 = pop(mystack, &sp);
		operand1 = pop(mystack, &sp);
		if (operand2 != 0.0) {
		    push(mystack, &sp, operand1/operand2);
		}
		else {
		    printf("Error: division by 0\n");
		    exit(1);
		}
	        break;
	    default:
	        printf("Error: unrecognized argument number %d \n", i);
		exit(1);
	        break;
	    }
	}
    }

    printf("Result: %lf\n", pop(mystack, &sp));
}

// Not worrying about exceeding stack size since stack was allocated to be of 
// sufficient size.
void push(double *stack, int *sp, double value) {
    // Equivalent to stack[sp] = value
    *(stack + *sp) = value;
    *sp += 1;
}

double pop(double *stack, int *sp) {
    if (*sp < 1) {
	printf("Error: popping empty stack\n");
	exit(1);
    }
    *sp -= 1;
    return *(stack + *sp);
}

// Would be better to use a regular expression instead
int isNumber(char *arg) {

    int sign;
    char *argcpy = arg;

    if (*arg == '+' || *arg == '-') {
        sign = *arg == '-' ? -1 : 1;
        arg += 1;
    }

    if (!isdigit(*arg)) {
        // Not a number
	return 0;
    }

    while (isdigit(*arg)) {
        arg += 1;
    }
    if (*arg == '\0') {
        // Number
	return 1;
    }
    else if (*arg == '.') {
    	arg += 1;
	while(isdigit(*arg)) {
	    arg += 1;
	}
	if (*arg == '\0') {
	    // Number
	    return 1;
	}
	else {
	    // Not a number
	    return 0;
	}
    }
    else {
        // Not a number
	return 0;
    }

}

int operator(char *arg) {

    if (!strcmp(arg, "+")) {
        //printf("add\n");
	return 0;
    }
    else if (!strcmp(arg, "-")) {
        //printf("sub\n");
	return 1;
    }
    else if (!strcmp(arg, "*")) {
        //printf("mul\n");
	return 2;
    }
    else if (!strcmp(arg, "/")) {
        //printf("div\n");
	return 3;
    }
    else {
    	// Unrecognized token
	return -1;
    }
}
