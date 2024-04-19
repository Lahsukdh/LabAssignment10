//Kushal Dhakal
//Lab Assignment 10
// 4-19-2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct TrieNode
{
    int count;
    struct TrieNode *children[26];
}node;

// Trie structure
typedef struct Trie
{	
    node *root;
} trie;


node* createNode(){
    node* nodePtr = (node*) malloc(sizeof(node));
    nodePtr->count = 0;
    for(int i = 0; i < 26; i++){
        nodePtr->children[i] = NULL;
    }
    return nodePtr;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int ind;
    node *nodePtr = pTrie->root;
    
    for (int i = 0; i < strlen(word); i++) {
        ind = word[i] - 'a';
        if (!(nodePtr->children[ind])) {
            nodePtr->children[ind] = createNode();
        }
        nodePtr = nodePtr->children[ind];
    }
    nodePtr->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int ind;
    node *nodePtr = pTrie->root;

    for (int i = 0; i < strlen(word); i++) {
        ind = word[i] - 'a';
        if (!nodePtr->children[ind])
            return 0; 
        nodePtr = nodePtr->children[ind];
    }
    return nodePtr->count;
}


void deallocateNode(node *pNode)
{
    for (int i = 0; i < 26; i++) {
        if (pNode->children[i])
            deallocateNode(pNode->children[i]);
    }
    free(pNode);
}

// deallocate the trie structure
trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie != NULL) {
        deallocateNode(pTrie->root);
        free(pTrie);
    }
    return NULL;
}

// Initializes a trie structure
trie *createTrie()
{
    trie *triePtr = (trie*)malloc(sizeof(trie));
    triePtr->root = createNode();
    return triePtr;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fPtr = fopen(filename, "r");
    int numWords;
    fscanf(fPtr, "%d", &numWords);
    char buffer[101];
    for (int i = 0; i < numWords; i++) {
        fscanf(fPtr, "%100s", buffer);
        pInWords[i] = strdup(buffer);
    }
    fclose(fPtr);
    return numWords;
}

int main(void)
{
	char *inWords[256];

    //read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}

    trie *pTrie = createTrie();
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