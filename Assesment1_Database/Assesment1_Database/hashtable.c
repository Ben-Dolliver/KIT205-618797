#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"


void hashtableTesting() {

    printf("\n\n    ------[hashtable testing]------\n");

    //  create hash tables
    AuthorHashTable authorHT;
    PaperHashTable paperHT;


    //  initialize author table
    for (int i = 0; i < TABLE_SIZE; i++) {
        authorHT.table[i] = NULL;
    }


    //  initialize paper table
    for (int i = 0; i < TABLE_SIZE; i++) {
        paperHT.table[i] = NULL;
    }


    printf("\n[testing hash functions]\n\n");

    printf("Author 101 Hash Index: %d\n",hashAuthor(101));
    printf("Paper 2001 Hash Index: %d\n",hashPaper(2001));


    printf("\n[testing create functions]\n\n");

    DTB2Author* testAuthor = createP2Author(999);
    DTB2Paper* testPaper = createP2Paper(888);


    if (testAuthor != NULL) {
        printf("Author Created\n");
        printf("Author ID: %d\n",
            testAuthor->authorID);
    }


    if (testPaper != NULL) {
        printf("Paper Created\n");
        printf("Paper ID: %d\n",
            testPaper->paperID);
    }

    //  adding authors
    printf("\n[adding authors]\n\n");
    insertAuthorHash(&authorHT, 101);
    insertAuthorHash(&authorHT, 102);


    //  adding paper
    printf("\n[adding papers]\n\n");
    insertPaperHash(&paperHT, 2001);
    insertPaperHash(&paperHT, 2002);


    printf("\n[finding author]\n\n");
    DTB2Author* foundAuthor = findAuthorHash(&authorHT, 101);

    if (foundAuthor != NULL) {
        printf("Author Found\n");
        printf("Author ID: %d\n",
            foundAuthor->authorID);
    }

    else {
        printf("Author Not Found\n");
    }


    printf("\n[finding paper]\n\n");

    DTB2Paper* foundPaper = findPaperHash(&paperHT, 2001);

    if (foundPaper != NULL) {
        printf("Paper Found\n");
        printf("Paper ID: %d\n",
            foundPaper->paperID);
    }

    else {
        printf("Paper Not Found\n");
    }


    printf("\n[testing missing records]\n\n");


    DTB2Author* missingAuthor = findAuthorHash(&authorHT, 9999);

    if (missingAuthor == NULL) {
        printf("Missing Author Returned NULL\n");
    }

    DTB2Paper* missingPaper = findPaperHash(&paperHT, 9999);

    if (missingPaper == NULL) {
        printf("Missing Paper Returned NULL\n");
    }


    printf("\n  ------[hashtable testing complete]------\n");
}



//  hash function for authors 
int hashAuthor(int id) {

    return id % TABLE_SIZE;
}

//  
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


