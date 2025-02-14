#ifndef INDEX_H
#define INDEX_H

#define Buffsize 30000
#define MAX_WORD_SIZE 100

// Define trie node structure
struct wordNode {
    char* term;
    int occurrence;
    struct wordNode** children;
};

// Function prototypes
void initializeNode(struct wordNode** root);

struct wordNode* indexPage(const char* url, int* pTotalNumTerms);

int addWordOccurrence(const char* addWord, const int wordLength, struct wordNode* trieRoot);

int freeTrieMemory(struct wordNode* root);

int getText(const char* srcAddr, char* buffer, const int bufSize);

#endif // INDEX_H
