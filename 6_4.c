#include <stdio.h>
#include <stdlib.h> // For exit
#include <string.h> // For strcmp

#include "readinput.c"

#define HASHSIZE 16384
#define MAXTEXTLEN 100

/*
    Write a program that prints the distinct words in its input sorted into decreasing order
    of frequency of occurrence. Precede each word by its count.

    Idea: use a priority queue (max heap) with counts of words as keys. A corresponding hash table with 
    words as keys can be used to access elements of the heap to increase counts (keys) as necessary.
    Sort using heap sort in the end.
*/



struct word {
    char *text;
    int count; // Priority for the priority queue.
    int heapIndex; // Index in the heap's array.
};

struct htentry{
    struct word *w;
    struct htentry *next;
};

// Hash table declaration.
static struct htentry *hashtable[HASHSIZE];

struct word * wordAlloc(char *text) {

    struct word *p;
    p = (struct word *) malloc(sizeof(struct word));
    if (p == NULL) {
	fprintf(stderr, "Error: couldn't allocate space for new struct word.\n");
	exit(1);
    }

    p->text = (char *) malloc (strlen(text)+1);
    if (p->text == NULL) {
	fprintf(stderr, "Error: couldn't allocate space for new struct word.\n");
	exit(1);
    }

    strcpy(p->text, text);
    p->count = 1;
    // Heap index is properly set upon insertion into heap.
    p->heapIndex = -1;

    return p;
}

/*********** Heap Functions ***********/

// Assuming heap indexing starts at 0, not 1.
int parent(int i) {
    if (i > 0) 
        return (i-1)/2;
    else
        return -1;
}
int left(int i) {
    return (i << 1) + 1;
}
int right(int i) {
    return (i << 1) + 2;
}

// Swap entries at index1 and index2, and swap the indices in their structs. 
void swap(struct word *data[], int index1, int index2) {
    if (index1 == index2) {
	return;
    }
    struct word *tmp;
    int tmp2;

    tmp2 = data[index1]->heapIndex;
    data[index1]->heapIndex = data[index2]->heapIndex;
    data[index2]->heapIndex = tmp2;

    tmp = data[index1];
    data[index1] = data[index2];
    data[index2] = tmp;

}

// Given that trees rooted at left(i) and right(i) are already heaps,
// make the tree rooted at i a heap. 
void maxHeapify(struct word *data[], int i, int heapSize) {
    if (heapSize < 2) return;

    int largest = i;
    int leftIndex = left(i);
    int rightIndex = right(i);

    if ((leftIndex < heapSize) && (data[leftIndex]->count > data[rightIndex]->count)) {
	largest = leftIndex;
    }
    if ((rightIndex < heapSize) && (data[rightIndex]->count > data[largest]->count)) {
	largest = rightIndex;
    }
    if (largest != i) {
	swap(data, largest, i);
	maxHeapify(data, largest, heapSize);
    }
}

// Covert heap into sorted array.
void heapSort(struct word *data[], int heapSize) {
    if (heapSize < 2) return;
    
    int lastIndex;
    int i; 
    for (lastIndex = heapSize-1; lastIndex > 0; lastIndex--) {
	swap(data, 0, lastIndex);
	maxHeapify(data, 0, lastIndex);
    }
}

// Increase the key of an element of the heap, and reheapify as necessary.
void maxHeapIncreaseKey(struct word *data[], struct word *p, int newKey) {
    if (p == NULL) {
	fprintf(stderr, "Error: attempting to increase key of nonexistent structure (NULL).\n");
	exit(1);
    }

    if (newKey < p->count) {
	fprintf(stderr, "Error: new key cannot be less than old key.\n");
	exit(1);
    }

    p->count = newKey;
    int i = p->heapIndex;
    while ((i > 0) && (data[parent(i)]->count < p->count)) {
        //printf("SWAP!\n");
	swap(data, i, parent(i));
	i = parent(i);
    }       
}

// Inserts a new struct into the heap. Increments the heap size.
// This function does not check if index will exceed bounds. (Checked in main).
void maxHeapInsert(struct word *data[], struct word *p, int *heapSize) {

    *heapSize += 1;
    data[*heapSize-1] = p;
    p->heapIndex = *heapSize - 1;
    maxHeapIncreaseKey(data, p, 1);

}

/*********** Hash Table Functions ***********/

// Taken from djb2 hash
unsigned int hash(char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++) != '\0')
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % HASHSIZE);
}

struct htentry * htlookup(char *key) {

    struct htentry *p;
    for(p = hashtable[hash(key)]; p != NULL; p=p->next) {
        if (strcmp(p->w->text, key) == 0) {
            return p;
        }
    }
    return NULL;
}

// Inserts new htentry into hashtable.
// Returns the newly created struct word * that needs to be inserted into the heap.
struct word * htinsert(char *key) {

    struct htentry *p = htlookup(key);

    if (p != NULL) {                    // Key already in table, do nothing.
        return NULL;
    }

    unsigned int hashval = hash(key);   
    struct word *w = wordAlloc(key);

    // Add new entry to the head of the list
    p = (struct htentry *) malloc(sizeof(struct htentry));
    p->w = w;
    p->next = hashtable[hashval];
    hashtable[hashval] = p;

    return p->w;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Please provide exactly one argument");
    }
    FILE *fin;
    char text[MAXTEXTLEN+1];
    int textlen, i;

    fin = fopen(argv[1], "r");
    if (fin == NULL) {
	fprintf(stderr, "Error: couldn't open file.\n");
	exit(1);
    }

    struct word *newWord;
    struct htentry *htp;
    // Perhaps should make this struct word ** to be able to resize it with realloc if necessary.
    int heapSpace = 10000;
    struct word *heap[heapSpace];
    int heapSize = 0;

    while ((textlen = getword(fin, text, MAXTEXTLEN)) > 0) {
        //printf("%s\n", text);
	if ((htp = htlookup(text)) == NULL) {
	    newWord = htinsert(text);
	    if (heapSize < heapSpace) {
	        maxHeapInsert(heap, newWord, &heapSize);
	    }
	    else {
		fprintf(stderr, "Error: max heap (priority queue) size reached.\n");
		exit(1);
	    }
	}
	else {
	    //printf("%s %d\n", htp->w->text, htp->w->count);
	    maxHeapIncreaseKey(heap, htp->w, (htp->w->count) + 1);
	}
	/*for(i = 0; i < heapSize; i++) {
	    printf("%d %s\n", heap[i]->count, heap[i]->text);
	}
	printf("\n");
	*/
    }

    heapSort(heap, heapSize);
    for(i = heapSize-1; i >= 0; i--) {
	printf("%d %s\n", heap[i]->count, heap[i]->text);
    }
    return 0;
}
