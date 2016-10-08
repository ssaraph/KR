#include <stdlib.h>
#define HASHSIZE 1024

/* Hash table implementation for 6_3.c
   Not generalized, just using a fixed size
   hashtable for this problem.  */

static struct htentry *hashtable[HASHSIZE];  	// static makes hashtable inaccessible outside of
   						// this file, as well as initializing values to NULL.
struct htentry {
    char *key;
    int val;
    struct htentry *next;
};

// Taken from djb2 hash
unsigned int hash(char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % HASHSIZE);
}

struct htentry * htentryAlloc(char *key, int val) {

    struct htentry *p;
    
    if ((p = (struct htentry *) malloc(sizeof(struct htentry))) != NULL) {
        printf("1\n");
	if((p->key = (char *) malloc(strlen(key)+1)) != NULL) {
	    strcpy(p->key, key);
	    p->val = val;
	    p->next = NULL;
	    return p;
	}
    }
    fprintf(stderr, "Error: couldn't allocate space for new htentry\n");
    exit(1);
}

struct htentry * htlookup(char *key) {

    struct htentry *p;
    for(p = hashtable[hash(key)]; p != NULL; p=p->next) {
	if (strcmp(p->key, key) == 0) {
	    return p;
	}
    }
    return NULL;
}

void htadd(char *key, int val) {

    struct htentry *p = htlookup(key);

    if (p != NULL) {			// Key already in table, update value
	p->val = val;
	return;
    }

    unsigned int hashval = hash(key);	// Add new entry to the head of the list
    p = htentryAlloc(key, val);
    p->next = hashtable[hashval];
    hashtable[hashval] = p;
}
