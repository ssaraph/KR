#include <stdio.h>
#include <string.h>


// Copy at most n characters of ct to s, padding with '\0''s if ct has fewer
// than n characters.
char * mystrncpy(char *s, char *ct, unsigned int n) {

    unsigned int i = 0;
    char *scpy = s;

/*
    while ((i < n) && ((*s = *ct) != '\0')) {  // NOTE: here, the order of the boolean tests is important (check i before making assignment)
    	s++;
	ct++;
	i++;
    }
    s++;
    ct++;
    i++;
*/

    // OR
    
    while((i++ < n) && ((*s++ = *ct++) != '\0'))
    	;

    // OR

/*
    while (i < n) {
	*s = *ct;
	if (*ct == '\0') {
	    break;
	}
	s++;
	ct++;
	i++;
    }
    s++;
    ct++;
    i++;
*/

    while (i < n) {
	*s = '\0';
	s++;
	i++;
    }
    return scpy;

}

// Append at most n characters of ct to s, padding with '\0''s if ct has fewer
// than n characters.
char * mystrncat(char *s, char *ct, unsigned int n) {

    int slen = strlen(s);
    char *scpy = s;

    int i = 0;

    s = s + slen;
    while ((i++ < n) && ((*s++ = *ct++) != '\0'))
    	;

    while (i < n) {
	*s = '\0';
	s++;
	i++;
    }

    return scpy;
}

// Compare at most n characters of cs to ct. Return <0 if cs<ct, 0 if cs==ct, >0 if cs>ct;
// n = 0 compares the first character like n = 1;
int mystrncmp(char *cs, char *ct, unsigned int n) {

    int i = 1;

    while((i < n) && (*cs == *ct)) {
        if (*cs == '\0') {
	    return 0;		// Both strings are the up to and including the null terminator.
	}
	cs++;
	ct++;
	i++;
    }

    return *cs - *ct;
}

int main() {

    char s1[24] = "xxxxxxxxxxxxxxxxxx";
    char s2[24] = "zzzz       zzzzzzz";
    char s3[100] = "";

    // mystrncpy
    printf("%s\n", s1);
    printf("%s\n", mystrncpy(s1, s2, 5));
    printf("%s\n", mystrncpy(s1, s2, 10));
    printf("%s\n", mystrncpy(s1, s2, 23));

    printf("\n");

    // mystrncat
    printf("%s\n", mystrncat(s3, "Hello ", 7));
    printf("%s\n", mystrncat(s3, "World ", 7 ));
    printf("%s\n", mystrncat(s3, "Some stuffs", 20));

    printf("\n");

    // mystrncmp
    printf("%d\n", mystrncmp("abcdef", "abcef", 4));
    printf("%d\n", mystrncmp("abcef", "abcdef", 4));
    printf("%d\n", mystrncmp("abcdef", "abcef", 3));
    printf("%d\n", mystrncmp("abcdef", "abcef", 10));



// Standard library strncpy comparison
/*
    char s3[24] = "xxxxxxxxxxxxxxxxx";
    char s4[24] = "zzzz";

    printf("%s\n", s3);
    printf("%s\n", strncpy(s3, s4, 8));
    //printf("%s\n", strncpy(s3, s4, 25));		// Causes "Abort Trap: 6"

    int i;
    for (i = 0; i < sizeof(s3); i++) {
	printf("i:%d %d\n", i, s3[i]);
    }
*/
}
