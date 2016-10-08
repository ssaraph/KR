#include <stdio.h>
#include <string.h>

// Returns 1 if s ends with t. 0 otherwise. 
int strend(char *s, char *t) {

    int tlen = strlen(t);
    int slen = strlen(s);
    char *p;

    if (tlen > slen) {
	return 0;
    }

    p = s + slen - tlen;

    while((*p == *t) && (*t != '\0')) {
	p++;
	t++;
    }
/*
    // OR

    while((*t != '\0') && (*p++ == *t++))
    	;
*/

    if (*t == '\0') {
	return 1;
    }
    return 0;

}

int main() {

    printf("%d\n", strend("amazing", "zing"));
    printf("%d\n", strend("amazingly", "zing"));
    printf("%d\n", strend("amazing", "amazing"));
    printf("%d\n", strend("amazing", "amazingly"));

}
