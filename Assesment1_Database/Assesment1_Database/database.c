#include <stdio.h>
#include <stdlib.h>

#include "database.h"




void databaseTesting() {
    
    printf("\n\n    ------[database 1 testing]------\n");


    Database* db = createDatabase();


    printf("\n[adding authors]\n");

    addAuthor(db, 101);
    addAuthor(db, 102);


    printf("\n[adding papers]\n");

    addPaper(db, 2001);
    addPaper(db, 2002);


    printf("\n[linking authorship]\n");

    addAuthorship(db, 101, 2001);
    addAuthorship(db, 101, 2002);

    addAuthorship(db, 102, 2001);

    printf("\n-----[printing results]-----\n");

    printAuthors(db);
    printPapers(db);

    printPapersByAuthor(db, 101);
    printAuthorsByPaper(db, 2001);

    printf("\n  ------[database 1 testing complete]------\n");

}


Database* createDatabase() {

    Database* db = malloc(sizeof(Database));

    if (db == NULL) {

        printf("Memory allocation failed\n");
        return NULL;
    }

    db->authorHead = NULL;
    db->paperHead = NULL;

    return db;

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
    author->papers = insertPaperBST(author->papers, paperID);


    // insert author into paper's BST
    paper->authors = insertAuthorBST(paper->authors, authorID);

}


//  Print all authors in database 
void printAuthors(Database* db) {

    Author* current = db->authorHead;
    printf("\nAuthors \n");

    while (current != NULL) {

        printf("Author ID: %d\n", current->authorID);

        current = current->next;
    }
}


//  Print all papers in database
void printPapers(Database* db) {

    Paper* current = db->paperHead;
    printf("\nPapers\n");

    while (current != NULL) {

        printf("Paper ID: %d\n", current->paperID);

        current = current->next;
    }
}


//  print the bst of papers of specific author
void printPapersByAuthor(Database* db, int authorID) {

    //  find author in linked list
    Author* author = findAuthor(db, authorID);

    //  error checking
    if (author == NULL) {

        printf("Author not found\n");
        return;
    }

    printf("\nPapers by Author ID %d\n", authorID);

    //  print the author's paper BST
    printPaperBST(author->papers);
}

//  print the bst of authors of specific paper
void printAuthorsByPaper(Database* db, int paperID) {

    //  find paper in linked list
    Paper* paper = findPaper(db, paperID);

    //  error checking
    if (paper == NULL) {

        printf("Paper not found\n");
        return;
    }

    printf("\nAuthors for Paper ID %d\n", paperID);

    //  print the paper's author BST
    printAuthorBST(paper->authors);
}




