#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hash.c"

#define MAXWORDLEN 100

/* Write a cross-referencer that prints a list of all words in a document, 
and for each word, a list of the line numbers on which it occurs. Remove noise
words like "and", "the" etc. */

// I choose to use a binary tree to store the words because I want to print the
// words and counts in lex order. If order was unimportant, it would probably be better
// to use a hash function and an array. The tree may be unbalanced (no rotations).

// I'm using a linked list for the line numbers of each word, but I could use a tree
// for this as well. 

// Optional: Write nonrecursive addToTree.

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
    struct lnode *lineNumbers;
};

struct lnode {
    int ln;		// Line number
    struct lnode *next;
};

// Allocate space for new lnode
struct lnode * lalloc(int ln) {

    struct lnode *p;

    if ((p = (struct lnode *) malloc(sizeof(struct lnode))) != NULL) {
    	p->ln = ln;
    	p->next = NULL;
	return p;
    }
    fprintf(stderr, "Error: couldn't allocate space for new list node\n");
    exit(1);
}

// Insert a new lnode in the line number list
struct lnode * linsert(struct lnode *head, int ln) {

    struct lnode *p, *tmp;

    if (head == NULL) {
	p = lalloc(ln);
	return p;
    }

    p = head;

    if (ln < p->ln) {
	head = lalloc(ln);
	head->next = p;
	return head;
    }
    else if (ln == p->ln) {
	return head;		// Do nothing
    }
    
    while ((p->next != NULL) && (ln > p->next->ln)) {
	p = p->next;
    }
    if (p->next == NULL) {
	p->next = lalloc(ln);
    }
    else if (ln < p->next->ln) {
	tmp = lalloc(ln);
	tmp->next = p->next;
	p->next = tmp;
    }
    /*
    else if (ln == p->next->ln)
    */
    return head;
}

// Allocate space for new tnode
struct tnode * talloc(char *word, int ln) {

    struct tnode *p;

    if ((p = (struct tnode *) malloc(sizeof(struct tnode))) != NULL) {
	if ((p->word = (char *) malloc(strlen(word) + 1)) != NULL) { // Leave space for '\0'
	    strcpy(p->word, word);
	    p->count = 1;
	    p->left = NULL;
	    p->right = NULL;
	    p->lineNumbers = lalloc(ln);
	    return p;
	}
    }
    fprintf(stderr, "Error: couldn't allocate space for new tree node\n");
    exit(1);

}

// Recursive version
struct tnode * addToTreeR(struct tnode *startNode, char *word, int ln) {

    int cond;

    if (startNode == NULL) {
	startNode = talloc(word, ln);
    }
    else if ((cond = strcmp(startNode->word, word)) == 0) {  	// Words match
	startNode->count += 1;
	startNode->lineNumbers = linsert(startNode->lineNumbers, ln);
    }
    else if (cond < 0) {   					// startNode->word comes first alphabetically
	startNode->right = addToTreeR(startNode->right, word, ln);
    }
    else {  		   					// word comes first alphabetically
	startNode->left = addToTreeR(startNode->left, word, ln);
    }
    return startNode;						// If startNode was NULL, originally, the newly allocated node is returned.
    								// Else startNode is the same as the value passed in.
}

// I am considering words to be continuous strings of alphabetic characters.
// Returns length of word, or EOF. This can be changed with the definition of a word.
int getword(char *word, unsigned int maxlen, int *ln) {

    int c;
    unsigned int i = 0;

    while (!isalpha(c = getc(stdin)) && (c != EOF)) {
	if (c == '\n') {
	    *ln += 1;		// Increment line number
	}
    }
    if (c == EOF) {
	return EOF;
    }
    else {
	*word++ = c;
	i++;
    }
    while (isalpha(c = getc(stdin))) {		// If the word is too long, keep reading until the end of the word
        if (i < maxlen) {			// but only consider the first part of it as a word;
	    *word++ = c;
	}
        i = i + 1;
    }
    ungetc(c, stdin);
    *word = '\0';

    return i;
}

void listprint(struct lnode *p) {
    while (p != NULL) {
	printf("%d ", p->ln);
	p = p->next;
    }
}

// In order tree traversal
void treeprint(struct tnode *p) {
    if (p != NULL) {
	treeprint(p->left);
	printf("%s count:%d ", p->word, p->count);
	printf("lines: ");
	listprint(p->lineNumbers);
	printf("\n");
	treeprint(p->right);
    }
}

// Function to check if word is a "noise word" that we ignore
int isNoise(char *word) {
    if (htlookup(word) != NULL) {
	return 1;
    }
    return 0;
}

int main() {

    int len;			// Length of word read
    int ln = 1;			// Current line number
    char word[MAXWORDLEN+1]; 	// Buffer to store read word

    struct tnode *root = NULL;

    char *noiseWords[] = {"a", "an", "the"};
    int i;
    for(i = 0; i < (sizeof(noiseWords)/sizeof(char *)); i++) {
	htadd(noiseWords[i], 0);				// The value doesn't matter
    }

    while ((len = getword(word, MAXWORDLEN, &ln)) != EOF) {
        if (!isNoise(word)) {
	    root = addToTreeR(root, word, ln);
	}
    }

    treeprint(root);

    return 0;

}
