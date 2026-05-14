#include <stdio.h>
#include <stdlib.h>

#include "database.h"

Author* createAuthor(int id) {
    Author* author = malloc(sizeof(Author));

    author->authorID = id;
    author->papers = NULL;
    author->next = NULL;
    return author;
}


Paper* createPaper(int id) {

    Paper* paper = malloc(sizeof(Paper));

    paper->paperID = id;
    paper->authors = NULL;
    paper->next = NULL;

    return paper;
}







void addAuthor(Database* db, int id) {

    if (findAuthor(db, id) != NULL)
        return;

    Author* newAuthor = createAuthor(id);

    newAuthor->next = db->authorHead;
    db->authorHead = newAuthor;
}

void addPaper(Database* db, int id) {

    if (findPaper(db, id) != NULL)
        return;

    Paper* newPaper = createPaper(id);

    newPaper->next = db->paperHead;
    db->paperHead = newPaper;
}



