#ifndef PROTOTYPE2_H
#define PROTOTYPE2_H

#include "hashtable.h"


// project 2 database
typedef struct P2Database {

    AuthorHashTable authors;
    PaperHashTable papers;

} P2Database;


//  database functions 
P2Database* createP2Database();

//testing function
void database2_testing();

//  add functions 
void addP2Author(P2Database* db, int authorID);
void addP2Paper(P2Database* db, int paperID);


//  link authorship function
void addP2Authorship(P2Database* db, int authorID, int paperID);



//  print functions
void printP2Authors(P2Database* db);
void printP2Papers(P2Database* db);
void printP2PapersByAuthor(P2Database* db, int authorID);
void printP2AuthorsByPaper(P2Database* db, int paperID);

#endif