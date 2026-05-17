#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "bst.h"
#include "hashtable.h"
#include "database.h"
#include "database2.h"



void performanceTesting() {

    printf("\n------[performance testing]------\n");

    Database* db = createDatabase();        //  database 1 testing set
    P2Database* db2 = createP2Database();   //  database 2 testing set

    clock_t start = clock();                //  start of testing
    clock_t end = clock();                  //  end of testing 

    double executionTime;                   //  time of execution for test 1
    double executionTime2;                  //  time of execution for test 1
    double min;                             //  the lower of the execution times

    const int TEST_SIZE = 10000;            //  size of tesing data


    start = clock();
    // add authors
    for (int i = 0; i < TEST_SIZE; i++) {
        addAuthor(db, i);
    }

    // add papers
    for (int i = 0; i < TEST_SIZE; i++) {
        addPaper(db, i + 10000);
    }

    // link authorship
    for (int i = 0; i < TEST_SIZE; i++) {
        addAuthorship(db, i, i + 10000);
    }

    end = clock();
    executionTime = ((double)(end - start))/ CLOCKS_PER_SEC;

    printf("\nProject 1 Execution Time: %f seconds\n", executionTime);


    start = clock();


    // add authors
    for (int i = 0; i < TEST_SIZE; i++) {
        addP2Author(db2, i);
    }


    // add papers
    for (int i = 0; i < TEST_SIZE; i++) {
        addP2Paper(db2, i + 10000);
    }

    // link authorship
    for (int i = 0; i < TEST_SIZE; i++) {
        addP2Authorship(db2, i, i + 10000);
    }

    end = clock();
    executionTime2 = ((double)(end - start)) / CLOCKS_PER_SEC;
   
    printf("Project 2 Execution Time: %f seconds\n", executionTime2);

    min = (executionTime < executionTime2) ? executionTime : executionTime2;
    Sleep(3000);

    printf("...and the winner is: \n");
    Sleep(2000);

    printf(". ");
    Sleep(2000);

    printf(". ");
    Sleep(2000);

    printf(". ");
    Sleep(2000);


    printf((executionTime < executionTime2) ? "Project 1!!!!\n":"Project 2!!!!\n");
    Sleep(3000);


    printf("\n------[performance testing complete]------\n");



}







//  bst tests
void testBST() {

    printf("\n\n    ------[BST testing]------\n");


    //  create empty BSTs
    PaperNode* paperRoot = NULL;
    AuthorNode* authorRoot = NULL;


    //  insert papers

    printf("\n[adding papers]\n");

    paperRoot = insertPaperBST(paperRoot, 2001);
    paperRoot = insertPaperBST(paperRoot, 2005);
    paperRoot = insertPaperBST(paperRoot, 2003);


    //  insert authors

    printf("\n[adding authors]\n");

    authorRoot = insertAuthorBST(authorRoot, 101);
    authorRoot = insertAuthorBST(authorRoot, 105);
    authorRoot = insertAuthorBST(authorRoot, 103);


    //  print BSTs

    printf("\n-----[printing results]-----\n");

    printf("\nPaper BST\n");
    printPaperBST(paperRoot);

    printf("\nAuthor BST\n");
    printAuthorBST(authorRoot);

    printf("\n  ------[BST testing complete]------\n");

}

//  hashtable tests
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

    printf("Author 101 Hash Index: %d\n", hashAuthor(101));
    printf("Paper 2001 Hash Index: %d\n", hashPaper(2001));


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


//  database 2 tests
void database2_testing() {

    printf("\n\n    ------[database 2 testing]------\n");


    P2Database* db = createP2Database();

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

    printf("\n-----[printing results]-----\n");

    printP2Authors(db);
    printP2Papers(db);

    printP2PapersByAuthor(db, 101);
    printP2AuthorsByPaper(db, 2001);

    printf("\n  ------[database 2 testing complete]------\n");


}


//  database tests
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


//  do all test functions
void testAll() {

    databaseTesting();
    database2_testing();
    testBST();
    hashtableTesting();
    performanceTesting();


}

