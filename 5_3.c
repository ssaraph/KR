#include <stdio.h>
#include <string.h>

// Concatenates t onto s.
// Makes no assumptions about the size of strings t and s! Responsibility of user to
// make sure that t will fit into the space allocatd for s.
void mystrcat(char *s, char *t) {

    int slen = strlen(s);
    s = s + slen;
    for(; *t != '\0'; t++, s++)
    	*s = *t;
    *s = '\0';
    // Could have done any of these instead: (See K&R 5.5)
    /*
    for(; (*s = *t) != '\0'; t++, s++)
    	;

    while((*s++ = *t++) != '\0')
    	;
    while((*s++ = *t++))					// ++ increments the pointers after the assignment
    	;							// While loop terminates when *t == NULL i.e. '\0' i.e. 0
    */


}

int main() {

    char s[30] = "Today I feel ";
    char t[100] = "lovely";
    char *u = " and evil";

    printf("%s\n",s);
    mystrcat(s,t);
    printf("%s\n",s);
    mystrcat(s,u);
    printf("%s\n",s);
    mystrcat(s,". Wow.");
    printf("%s\n",s);
    //mystrcat(s," Overflowwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww"); // Causes "Abort trap: 6"

}
