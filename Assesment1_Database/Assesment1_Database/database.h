#define DATABASE_H
#define DATABASE_H

#include "bst.h"


//  Author struct
typedef struct Author {
    int authorID;

    PaperNode* papers;
    struct Author* next;

} Author;

//  Paper struct
typedef struct Paper {
    int paperID;

    AuthorNode* authors;
    struct Paper* next;

} Paper;


//  Database struct
typedef struct Database {

    Author* authorHead;
    Paper* paperHead;

} Database;




// =========================
// FUNCTION DECLARATIONS
// =========================

Author* createAuthor(int id);
Paper* createPaper(int id);

Author* findAuthor(Database* db, int id);
Paper* findPaper(Database* db, int id);

void addAuthor(Database* db, int id);
void addPaper(Database* db, int id);

void addAuthorship(Database* db, int authorID, int paperID);

void printAuthors(Database* db);
void printPapers(Database* db);

void printPapersByAuthor(Database* db, int authorID);
void printAuthorsByPaper(Database* db, int paperID);
