#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "crawler.h"

int totalNumPages = 0;


int getLink(const char* srcAddr, char* link, const int maxLinkLength){
    const int bufSize = 30000;
    char buffer[bufSize];

    int numLinks = 0;

    FILE *pipe;

    snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getLinks.py", srcAddr);

    pipe = popen(buffer, "r");
    if(pipe == NULL){
        fprintf(stderr, "ERROR: could not open the pipe for command %s\n", buffer);
        return 0;
    }

    fscanf(pipe, "%d\n", &numLinks);

    if(numLinks > 0){
        int linkNum;
        double r = (double)rand() / ((double)RAND_MAX + 1.0);

        for(linkNum=0; linkNum<numLinks; linkNum++){
            fgets(buffer, bufSize, pipe);

            if(r < (linkNum + 1.0) / numLinks){
                break;
            }
        }

        /* copy the address from buffer to link */
        strncpy(link, buffer, maxLinkLength);
        link[maxLinkLength-1] = '\0';

        /* get rid of the newline */
        {
            char* pNewline = strchr(link, '\n');
            if(pNewline != NULL){
                *pNewline = '\0';
            }
        }
    }

    pclose(pipe);

    if(numLinks > 0){
        return 1;
    }
    else{
        return 0;
    }
}
void crawlPages(const char* urlFile, int maxPages, long seed) {
    FILE* file = fopen(urlFile, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening URL file: %s\n", urlFile);
        return;
    }

    srand(seed);
    
    int n = 0; // Number of pages indexed
    char startAddr[MAX_ADDR_LENGTH];
    char newAddr[MAX_ADDR_LENGTH];
    int numHops;

    printf("Indexing...\n");

    struct listNode* visitedList;

    strncpy(startAddr, urlFile, MAX_ADDR_LENGTH);
    startAddr[MAX_ADDR_LENGTH - 1] = '\0';

    visitedList = malloc(sizeof(struct listNode));
    if (visitedList == NULL) {
        fprintf(stderr, "ERROR: could not allocate memory for the list node\n");
        exit(EXIT_FAILURE);
    }
    strncpy(visitedList->addr, startAddr, MAX_ADDR_LENGTH);
    visitedList->next = NULL;

    while (fscanf(file, "%s %d", startAddr, &numHops) == 2 && n < maxPages) {
        int hopNum = 0;

        while (1) {
            if (!contains(visitedList, startAddr)) {
                int totalNumTerms;
                struct wordNode* root = indexPage(startAddr, &totalNumTerms);
                freeTrieMemory(root);
                
                insertBack(visitedList, startAddr);
                totalNumPages++;
                n++;
            }

            hopNum++;

            if (hopNum <= numHops && n < maxPages) {
                int res = getLink(startAddr, newAddr, MAX_ADDR_LENGTH);
                if (!res) {
                    break;
                } else {
                    strncpy(startAddr, newAddr, MAX_ADDR_LENGTH); // Update startAddr with newAddr
                }
            } else {
                break;
            }
        }
    }

    destroyList(visitedList);
    fclose(file);
}





/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains(const struct listNode *pNode, const char *addr){
    if (pNode == NULL) {
        return 0;
    }
    if (strcmp(pNode->addr, addr) == 0) {
        return 1;
    }
    return contains(pNode->next, addr);
};

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(struct listNode *pNode, const char *addr){
    if (pNode->next == NULL) {
        struct listNode *newNode = malloc(sizeof(struct listNode));
        if (newNode == NULL) {
            fprintf(stderr, "ERROR: could not allocate memory for a new node\n");
            exit(-2);
        }
        strncpy(newNode->addr, addr, MAX_ADDR_LENGTH);
        newNode->next = NULL;
        pNode->next = newNode;
    } else {
        insertBack(pNode->next, addr);
    }
};

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList(struct listNode *pNode){
    if (pNode == NULL) {
        return;
    }
    destroyList(pNode->next);
    free(pNode);
};

