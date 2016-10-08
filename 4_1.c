#include <stdio.h>
#include <string.h>

// Returns the index of the rightmost occurrence of t in s. -1 if no occurrence.
int strrindex(char s[], char t[]) {

    int slen, tlen;
    slen = strlen(s);
    tlen = strlen(t);

    if ((tlen == 0) || (tlen > slen)) {
	return -1;
    }

    int i, j, k;
    for(i = slen - tlen; i > 0; i--) {

	for(j = i, k = 0; (t[k] != '\0') && (t[k] == s[j]); k++, j++)
	    ;
	
	if (t[k] == '\0') {
	    return i;
	}
    }

    return -1;
}

int main() {

	char s[] = "A pastime of mine is pantomime nightly at nine.";
	char t[] = "ime";
	char u[] = "ine";
	char v[] = "lime";

	printf("%d\n", strrindex(s, t));
	printf("%d\n", strrindex(s, u));
	printf("%d\n", strrindex(s, v));

}
