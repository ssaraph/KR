#include <stdio.h>

int lower(int c) {
    return ((c >= 'A') && (c <= 'Z')) ? (c-'A'+'a') : c;
}
int main() {

    char letters[55] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPWRSTUVWXYZ";

    int i;
    for(i = 0; i < 55; i++) {
	printf("%c", lower(letters[i]));
    }
    printf("\n");

    return 0;
}
