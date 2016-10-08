#include <stdio.h>


void squeeze(char s1[], char s2[]);
int contains(char s[], char c);

int main() {

    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz"; 
    char vowels[6] = "aeiou";

    squeeze(alphabet, vowels);
    printf("%s\n", alphabet);

    return 0;
}

// Deletes each char in s1 that matches a char in s2
void squeeze(char s1[], char s2[]) {

    int i, j;
    i = j = 0;

    while (s1[i] != '\0') {
	if (contains(s2, s1[i]) == 0) {
	    s1[j] = s1[i];
	    j++;
	}
	i++;
    }
    s1[j] = '\0';

}

int contains(char s[], char c) {

    int i;
    for(i = 0; s[i] != '\0'; i++) {
	if (s[i] == c) {
	    return 1;
	}
    }
    return 0;
}
