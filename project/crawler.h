#ifndef CRAWLER_H
#define CRAWLER_H

#include "index.h"
#define MAX_ADDR_LENGTH 1000

extern int totalNumPages;

// Function prototypes
void crawlPages(const char *urlFile, int maxPages, long seed);
struct listNode {
    char addr[MAX_ADDR_LENGTH];
    struct listNode* next;
};

int getLink(const char* srcAddr, char* link, const int maxLinkLength);

int contains(const struct listNode* pNode, const char* addr);
void insertBack(struct listNode* pNode, const char* addr);
void printAddresses(const struct listNode* pNode);
void destroyList(struct listNode* pNode);
#endif // CRAWLER_H
