#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"



//  hash function for authors 
int hashAuthor(int id) {

    return id % TABLE_SIZE;
}


int hashPaper(int id) {

    return id % TABLE_SIZE;
}





//  create functions
DTB2Author* createP2Author(int id) {

    //  allocate memory
    DTB2Author* newAuthor = malloc(sizeof(DTB2Author));

    //  error handling
    if (newAuthor == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    //  initialize fields
    newAuthor->authorID = id;
    newAuthor->papers = NULL;
    newAuthor->next = NULL;

    return newAuthor;

}


DTB2Paper* createP2Paper(int id) {


    //  allocate memory
    DTB2Paper* newPaper = malloc(sizeof(DTB2Paper));

    // error handling
    if(newPaper == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    //  initialize fields
    newPaper->paperID = id;
    newPaper->authors = NULL;
    newPaper->next = NULL;

    return newPaper;
}


//  insert functions
void insertAuthorHash(AuthorHashTable* ht, int id) {

    //  get bucket index
    int index = hashAuthor(id);

    //  check if author already exists
    DTB2Author* current = ht->table[index];

    while (current != NULL) {

        
        if (current->authorID == id) {
            return; //  duplicate author found 
        }

        current = current->next;
    }

    //  create a new author
    DTB2Author* newAuthor = createP2Author(id);

    if (newAuthor == NULL) {
        return;
    }

    //  insert author at beginning of collision chain
    newAuthor->next = ht->table[index];
    ht->table[index] = newAuthor;

}

void insertPaperHash(PaperHashTable* ht, int id) {


    //  get the bucket index
    int index = hashPaper(id);

    //  check if  the paper already exists
    DTB2Paper* current = ht->table[index];

    while (current != NULL) {

        if (current->paperID == id) {
            return; //  duplicate Paper found
        }

        current = current->next;
    }

    //  create a new paper
    DTB2Paper* newPaper = createP2Paper(id);

    if (newPaper == NULL) {
        return;
    }

    //  insert paper at the beginning of the collision chain
    newPaper->next = ht->table[index];
    ht->table[index] = newPaper;

}


//  find functions
DTB2Author* findAuthorHash(AuthorHashTable* ht, int id) {
   
    //  get bucket index
    int index = hashAuthor(id);

    //  start at beginning of collision chain
    DTB2Author* current = ht->table[index];

    //  traverse linked list
    while (current != NULL) {

        //  author found
        if (current->authorID == id) {
            return current;
        }

        current = current->next;
    }

    //  author not found
    return NULL;


}

DTB2Paper* findPaperHash(PaperHashTable* ht, int id) {

    //  get bucket index
    int index = hashPaper(id);

    //  start at beginning of collision chain
    DTB2Paper* current = ht->table[index];

    //  traverse linked list
    while (current != NULL) {

        //  paper found
        if (current->paperID == id) {
            return current;
        }

        current = current->next;
    }

    //  paper not found
    return NULL;
}


