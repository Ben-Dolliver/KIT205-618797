#include <stdio.h>
#include <stdlib.h>

#include "database.h"



Database* createDatabase(int id) {

}

//  Creates an author from author ID leaves papers empty
Author* createAuthor(int id) {
    Author* author = malloc(sizeof(Author));

    author->authorID = id;
    author->papers = NULL;
    author->next = NULL;
    return author;
}


//  Creates an Paper from Paper ID leaves authors empty
Paper* createPaper(int id) {

    Paper* paper = malloc(sizeof(Paper));

    paper->paperID = id;
    paper->authors = NULL;
    paper->next = NULL;

    return paper;
}






//  adds a new author into the database 
void addAuthor(Database* db, int id) {

    if (findAuthor(db, id) != NULL)
        return;

    Author* newAuthor = createAuthor(id);

    newAuthor->next = db->authorHead;
    db->authorHead = newAuthor;
}


//  Adds paper node to database 
void addPaper(Database* db, int id) {

    if (findPaper(db, id) != NULL)
        return;

    Paper* newPaper = createPaper(id);

    newPaper->next = db->paperHead;
    db->paperHead = newPaper;
}



Author* findAuthor(Database* db, int id) {
    Author* current = db->authorHead;

    while (current != NULL) {

        if (current->authorID == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

Paper* findPaper(Database* db, int id) {

    Paper* current = db->paperHead;

    while (current != NULL) {

        if (current->paperID == id) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}



void addAuthorship(Database* db, int authorID, int paperID) {

    // find author in linked list
    Author* author = findAuthor(db, authorID);

    // find paper in linked list
    Paper* paper = findPaper(db, paperID);

    // error checking
    if (author == NULL || paper == NULL) {

        printf("Author or Paper not found\n");
        return;
    }

    // insert paper into author's BST
    author->papers =
        insertPaperBST(author->papers, paperID);


    // insert author into paper's BST
    paper->authors =
        insertAuthorBST(paper->authors, authorID);

}

void printAuthors(Database* db) {
}

void printPapers(Database* db) {
}

void printPapersByAuthor(Database* db, int authorID) {
}

void printAuthorsByPaper(Database* db, int paperID) {
}




