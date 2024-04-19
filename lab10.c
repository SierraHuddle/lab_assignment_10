// Sierra Huddle
// Lab 10 Assignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// expected output: 
// the input file repeated
// notaword: 2
// ucf: 4
// no: 0
// note: 2
// corg: 0


// Trie structure
struct Trie {
    struct Trie *children[26];
    int count; // for occurrences
};

// Function prototypes
struct Trie *createTrie();
void insert(struct Trie *pTrie, char *word);
int numberOfOccurances(struct Trie *pTrie, char *word); 
struct Trie *deallocateTrie(struct Trie *pTrie);
int readDictionary(char *filename, char **pInWords);

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    if (node) {
        for (int i = 0; i < 26; ++i) {
            node->children[i] = NULL;
        }
        node->count = 0;
    }
    return node;
}

// Inserts the word into the trie structure
void insert(struct Trie *pTrie, char *word) {
    //if null return
    if (pTrie == NULL || word == NULL) {
        return;
    }

    struct Trie *current = pTrie;
    for (int i = 0; word[i] != '\0'; ++i) {
        // turn character to index
        int index = word[i] - 'a'; 
        if (current->children[index] == NULL) {
            current->children[index] = createTrie();
        }

        current = current->children[index];
    }
    // end and increment count
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    // null, return 
    if (pTrie == NULL || word == NULL) {
        return 0;
    }

    struct Trie *current = pTrie;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    
    if (pTrie == NULL) {
        return NULL;
    }
    // traverse
    for (int i = 0; i < 26; ++i) {
        if (pTrie->children[i] != NULL) {
            deallocateTrie(pTrie->children[i]);
        }
    }
    //free memory
    free(pTrie);
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    int count = 0;
    char word[100];
    //read from file 
    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }

    fclose(file);
    return count;
}

// stays the same 
int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}