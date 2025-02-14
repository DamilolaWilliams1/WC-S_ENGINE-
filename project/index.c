#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "index.h"

void initializeNode(struct wordNode** root)
{
  //Allocate memory for the root, if needed, and initialize root's fields.
  if(*root == NULL) *root = malloc(sizeof(struct wordNode));

  (*root)->occurrence = 0;
  (*root)->children = malloc(sizeof(struct wordNode*) * 26);

  //Set the children pointers to NULL.
  for(int i = 0; i < 26; i++){
    (*root)->children[i] = NULL;
  }
}

 struct wordNode* indexPage(const char* url, int* pTotalNumTerms)
{
  //initialize the buffer and associated variables.
  char buffer[Buffsize];
  int sizeRead = -1;
  char word[MAX_WORD_SIZE];
  //word start and end values for later loop.
  int start = 0;
  int end = 0;

  //Initialize the trie.
  struct wordNode *root = malloc(sizeof(struct wordNode));
  if (root == NULL) {
    return NULL;
}
  initializeNode(&root);

  //Receive the text to be parsed and check for success.
  sizeRead = getText(url, buffer, Buffsize);
  if(sizeRead == -1) return NULL;
  
  printf("%s\n",url);

  int sumOfTermCounts = 0;

  //parse the buffer into substrings until all start index reaches the size of the read.
  while(start < sizeRead){
    
    //Increment end as long as the current character is alphabetical.
    while(tolower(buffer[end]) > 96 && tolower(buffer[end]) < 123 && end < sizeRead){
      end++;
    }

    int length = end - start;

    if(length > 0){

      //Copy the string from buffer into word. End with '\0'.
      strncpy(word, buffer + start, length);
      word[length] = '\0';
      
      //Convert to lowercase.
      for(int i = 0; i < length; i++){
        word[i] = tolower(word[i]);
      }

      //Print the word and add its occurence.
      printf("\t%s\n", word);
      addWordOccurrence(word, length, root);
      sumOfTermCounts++;
      start = end;
    }

    //Advance the start and end indices together.
    start++;
    end = start;
  }

  *pTotalNumTerms = sumOfTermCounts;
  return root;
}

int addWordOccurrence(const char* addWord, const int wordLength, struct wordNode* root)
{
  //Increment Occurrence when the wordlength is 0.
  if (wordLength == 0) {
        root->occurrence++;
        return 0;
    }

  //Create int to refer to letter's index and create
  int letter = tolower(addWord[0]) - 'a';
  if (root->children[letter] == NULL) {    
      initializeNode(&(root->children[letter]));
  }

  //Pass in the next node, increment the word pointer, decrement the wordLength and recurse.
  return addWordOccurrence(addWord + 1, wordLength - 1, root->children[letter]);
}

int freeTrieMemory(struct wordNode* root)
{ 
  if(root != NULL){
  //Free every child node first
  for(int i = 0; i < 26; i++){
    if(root->children[i] != NULL){
      freeTrieMemory(root->children[i]);
    }
  }
  
  //Free the children pointer and root last.
  free(root->children);
  free(root);
  }
  return 0;
}

/* You should not need to modify this function */
int getText(const char* srcAddr, char* buffer, const int bufSize){
  FILE *pipe;
  int bytesRead;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getText.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n",
	    buffer);
    return 0;
  }

  bytesRead = fread(buffer, sizeof(char), bufSize-1, pipe);
  buffer[bytesRead] = '\0';

  pclose(pipe);

  return bytesRead;
}