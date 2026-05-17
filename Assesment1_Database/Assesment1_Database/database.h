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





// FUNCTION DECLARATIONS
void databaseTesting();


//  create functions
Author* createAuthor(int id);
Paper* createPaper(int id);
Database* createDatabase();

//  find functions
Author* findAuthor(Database* db, int id);
Paper* findPaper(Database* db, int id);

//  add functions
void addAuthor(Database* db, int id);
void addPaper(Database* db, int id);

//  linking function
void addAuthorship(Database* db, int authorID, int paperID);

//  print functions
void printAuthors(Database* db);
void printPapers(Database* db);

void printPapersByAuthor(Database* db, int authorID);
void printAuthorsByPaper(Database* db, int paperID);
