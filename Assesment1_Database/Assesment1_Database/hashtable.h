#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "bst.h"

#define TABLE_SIZE 101



//  author struct
typedef struct DTB2Author {
    int authorID;

    // BST of papers
    PaperNode* papers;

    // collision chain
    struct DTB2Author* next;
} DTB2Author;



//  paper struct 
typedef struct DTB2Paper {
    int paperID;

    // BST of authors
    AuthorNode* authors;

    // collision chain
    struct DTB2Paper* next;
} DTB2Paper;



typedef struct AuthorHashTable {
    DTB2Author* table[TABLE_SIZE];

} AuthorHashTable;


typedef struct PaperHashTable {
    DTB2Paper* table[TABLE_SIZE];

} PaperHashTable;



//  hash functions
int hashAuthor(int id);
int hashPaper(int id);


//  create functions
DTB2Author* createP2Author(int id);
DTB2Paper* createP2Paper(int id);


//  insert functions
void insertAuthorHash(AuthorHashTable* ht, int id);
void insertPaperHash(PaperHashTable* ht, int id);


//  find functions
DTB2Author* findAuthorHash(AuthorHashTable* ht, int id);
DTB2Paper* findPaperHash(PaperHashTable* ht, int id);



#endif