#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>  
#include "index.h"
#include "crawler.h"

#define MAX_QUERY_LENGTH 1000

// Function prototypes
void processQuery(struct wordNode* root, const char* query);
double calculateTFIDF(struct wordNode* root, const char* term, const int totalNumTerms);
int findTermIndex(struct wordNode* root, const char* term);

int main(int argc, char* argv[]) {
    // Check command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <urlFile> <maxPages> <seed>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* urlFile = argv[1];
    int maxPages = atoi(argv[2]);
    long seed = atol(argv[3]);

    // Perform web crawling
    struct wordNode* root = NULL;
    crawlPages(urlFile, maxPages, seed);

    // Query phase
    // char query[MAX_QUERY_LENGTH];

    // while (1) {
    //     printf("\nEnter a web query: ");
    //     char* res = fgets(query, MAX_QUERY_LENGTH, stdin);

    //     // Remove newline character from the end of the query
    //     query[strcspn(query, "\n")] = '\0';

    //     // Check if the query is empty
    //     if (res == NULL) {
    //         printf("Exiting the program\n");
    //         break;
    //     }

    //     // Check if the query contains only lowercase letters and whitespace
    //     int validQuery = 1;
    //     for (int i = 0; i < strlen(query); i++) {
    //         if (!islower(query[i]) && !isspace(query[i])) {
    //             fprintf(stderr, "Please enter a query containing only lower-case letters.\n");
    //             validQuery = 0;
    //             break;
    //         }
    //     }

    //     if (validQuery) {
    //         processQuery(root, query);
    //     }
    // }

    // Free trie memory
    freeTrieMemory(root);

    return EXIT_SUCCESS;
}

// void processQuery(struct wordNode* root, const char* query) {
//     printf("Query is \"%s\".\n", query);

// // Tokenize the query into terms
// char* term = strtok((char*)query, " ");
// int numTerms = 0;

// // Initialize array to store IDF scores
// double idfScores[MAX_WORD_SIZE];
// memset(idfScores, 0, sizeof(idfScores));

// // Calculate IDF scores for each term in the query
// while (root != NULL && term != NULL && numTerms < MAX_WORD_SIZE) {
//     int termIndex = findTermIndex(root, term);
//     if (termIndex != -1) {
//         idfScores[numTerms] = log((double)totalNumPages / (1.0 + root->children[termIndex]->occurrence));
//         term = strtok(NULL, " ");
//         numTerms++;
//     } else {
//         fprintf(stderr, "Term '%s' not found in the index.\n", term);
//         break;
//     }
// }


//     // Print IDF scores
//     printf("IDF scores are\n");
//     for (int i = 0; i < numTerms; i++) {
//         printf("IDF(%s): %f\n", root->children[i]->term, idfScores[i]);
//     }

//     // Initialize array to store TF-IDF scores
//     double tfidfScores[MAX_WORD_SIZE];
//     memset(tfidfScores, 0, sizeof(tfidfScores));

//     // Calculate TF-IDF scores for each web page
//     if (root != NULL) {
//     for (int i = 0; i < root->occurrence; i++) {
//         double score = 0.0;

//         for (int j = 0; j < numTerms; j++) {
//             score += calculateTFIDF(root, root->children[j]->term, totalNumPages);
//         }

//         tfidfScores[i] = score;
//     }
// }

//     // Print web pages with the highest TF-IDF scores
//     printf("Web pages:\n");
//     for (int i = 0; i < 3; i++) {
//         double maxScore = -1.0;
//         int maxIndex = -1;
//         if(root != NULL){
//         for (int j = 0; j < root->occurrence; j++) {
//             if (tfidfScores[j] > maxScore) {
//                 maxScore = tfidfScores[j];
//                 maxIndex = j;
//             }
//         }    
//         }
    
//         if (maxIndex != -1) {
//             printf("%d. %s (score: %f)\n", i + 1, root->children[maxIndex]->term, maxScore);
//             tfidfScores[maxIndex] = -1.0; // Mark as visited
//         }
//     }
// }

// double calculateTFIDF(struct wordNode* root, const char* term, const int totalNumPages) {
//     int termIndex = findTermIndex(root, term);

//     if (termIndex != -1) {
//         double tf = (double)root->children[termIndex]->occurrence / root->occurrence;
//         double idf = log((double)totalNumPages / (1.0 + root->children[termIndex]->occurrence));

//         return tf * idf;
//     } else {
//         // Term not found, assume its occurrence is zero
//         return 0.0;
//     }
// }


// int findTermIndex(struct wordNode* root, const char* term) {
//     for (int i = 0; i < root->occurrence; i++) {
//         if (strcmp(root->children[i]->term, term) == 0) {
//             return i;
//         }
//     }
//     return -1;  // Term not found
// }
