#include <stdio.h>
#include <stdlib.h>

#include "database2.h"
#include "hashtable.h"
#include "bst.h"


void database2_testing() {

	P2Database* db =  createP2Database();

    printf("\n[adding authors]\n");

    addP2Author(db, 101);
    addP2Author(db, 102);


    printf("\n[adding papers]\n");

    addP2Paper(db, 2001);
    addP2Paper(db, 2002);


    printf("\n[linking authorship]\n");

    addP2Authorship(db, 101, 2001);
    addP2Authorship(db, 101, 2002);

    addP2Authorship(db, 102, 2001);

    printf("\n--------[printing results]--------\n");

    printP2Authors(db);
    printP2Papers(db);

    printP2PapersByAuthor(db, 101);
    printP2AuthorsByPaper(db, 2001);

}



P2Database* createP2Database() {

    //  allocate memory for the database
    P2Database* db = malloc(sizeof(P2Database));

    //  error handling
    if (db == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    //  initialize author hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        db->authors.table[i] = NULL;
    }

    //  initialize paper hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        db->papers.table[i] = NULL;
    }

    return db;
}


void addP2Author(P2Database* db, int authorID) {
    insertAuthorHash(&db->authors, authorID);
}

void addP2Paper(P2Database* db, int paperID) {
    insertPaperHash(&db->papers, paperID);
}


//  link authorship function
void addP2Authorship(P2Database* db, int authorID, int paperID) {
    
    //  find author
    DTB2Author* author = findAuthorHash(&db->authors, authorID);

    //  find paper
    DTB2Paper* paper = findPaperHash(&db->papers, paperID);

    //  check if both exist
    if (author == NULL || paper == NULL) {
        printf("Author or Paper not found\n");
        return;
    }

    //  insert paper into author's BST
    author->papers = insertPaperBST(author->papers, paperID);

    //  insert author into paper's BST
    paper->authors = insertAuthorBST(paper->authors, authorID);

}



//  print functions
void printP2Authors(P2Database* db) {

    printf("\nAuthors\n");

    // traverse hash table
    for (int i = 0; i < TABLE_SIZE; i++) {

        DTB2Author* current = db->authors.table[i];

        // traverse collision chain
        while (current != NULL) {

            printf("Author ID: %d\n", current->authorID);

            current = current->next;
        }
    }
}

void printP2Papers(P2Database* db) {

    printf("\nPapers\n");

    //  traverse hash table
    for (int i = 0; i < TABLE_SIZE; i++) {

        DTB2Paper* current = db->papers.table[i];

        //  traverse collision chain
        while (current != NULL) {

            printf("Paper ID: %d\n", current->paperID);

            current = current->next;
        }
    }
}

void printP2PapersByAuthor(P2Database* db, int authorID) {
    
    //  find author in hash table
    DTB2Author* author = findAuthorHash(&db->authors, authorID);

    //  error checking
    if (author == NULL) {
        printf("Author not found\n");
        return;
    }

    printf("\nPapers by Author ID %d\n", authorID);

    //  print the author's paper BST
    printPaperBST(author->papers);

}

void printP2AuthorsByPaper(P2Database* db, int paperID) {
    
    //  find paper in hash table
    DTB2Paper* paper = findPaperHash(&db->papers, paperID);

    //  error checking
    if (paper == NULL) {
        printf("Paper not found\n");
        return;
    }

    printf("\nAuthors for Paper ID %d\n", paperID);

    //  print the paper's author BST
    printAuthorBST(paper->authors);
}



