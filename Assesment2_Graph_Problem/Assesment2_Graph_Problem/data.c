#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"


static const char* topics[] = { "Graph", "Network", "Citation", "Algorithm", "Data Structure",
                                  "Shortest Path", "Neural", "Sorting", "Tree", "Search" };
static const char* methods[] = { "Analysis", "Survey", "Review", "Study", "Investigation",
                                  "Comparison", "Evaluation", "Approach", "Framework", "Model" };


//  arrays to track used IDs to prevent duplicates
static int usedPaperIDs[MAX_PAPERS];
static int usedAuthorIDs[MAX_AUTHORS];
static int paperCount = 0;
static int authorCount = 0;

//  generate a random paper title from word banks
void rand_title(char* buffer) {
    int t = rand() % 10;
    int m = rand() % 10;
    sprintf_s(buffer, 128, "%s %s", topics[t], methods[m]);
}

//  needs to seperate each check because otherwise it would not allow
//  for same paper and author ID
//  check if paper ID already exists
int paper_id_exists(int id) {
    for (int i = 0; i < paperCount; i++) {
        if (usedPaperIDs[i] == id) return 1;
    }
    return 0;
}

//  check if author ID already exists
int author_id_exists(int id) {
    for (int i = 0; i < authorCount; i++) {
        if (usedAuthorIDs[i] == id) return 1;
    }
    return 0;
}


//  generate unique random paper ID
int rand_paper_id() {
    int id;
    do {
        id = rand() % 90000 + 10000;   //  5 digit ID 10000 - 99999
    } while (paper_id_exists(id));
    usedPaperIDs[paperCount++] = id;
    return id;
}

//  generate unique random author ID
int rand_author_id() {
    int id;
    do {
        id = rand() % 900 + 100;       //  3 digit ID 100 - 999
    } while (author_id_exists(id));
    usedAuthorIDs[authorCount++] = id;
    return id;
}

//  clear all data from file 
void clearData() {

    FILE* file = fopen(PAPER_FILE, "w");

    if (file == NULL) {
        printf_s("Failed to clear file\n");
        return;
    }

    fclose(file);
}

// print all of the data 
void printData() {

    FILE* file = fopen(PAPER_FILE, "r");

    if (file == NULL) {
        printf("Failed to open file\n");
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf_s("%s", line);
    }

    fclose(file);

}


//  create test_papers.txt data
void create_papers() {

    //  reset tracking arrays
    paperCount = 0;
    authorCount = 0;
    memset(usedPaperIDs, 0, sizeof(usedPaperIDs));
    memset(usedAuthorIDs, 0, sizeof(usedAuthorIDs));

    srand((unsigned int)time(NULL));

	//  error check 
    FILE* file = fopen(PAPER_FILE, "w");
    if (!file) {
        printf("Error opening file: %s\n", PAPER_FILE);
        return;
    }

    //  header line
    fprintf(file, "id paperID authorID year\n");

    //  pre-generate unique author IDs
    int authors[MAX_AUTHORS];
    for (int i = 0; i < MAX_AUTHORS; i++) {
        authors[i] = rand_author_id();
    }

    //  write each paper 
    for (int i = 0; i < MAX_PAPERS; i++) {
        int paperID = rand_paper_id();
        int authorID = authors[rand() % MAX_AUTHORS];  
        int year = rand() % 30 + 1994;             //  1994 - 2024

        fprintf(file, "%d %d %d %d\n", i, paperID, authorID, year);
    }

    fclose(file);
    printf("Papers written to %s (%d papers, %d authors)\n",
        PAPER_FILE, MAX_PAPERS, MAX_AUTHORS);
}



//  create test_edges.txt data with random edges between papers
void create_edges() {

    srand((unsigned int)time(NULL));

	//  error check
    FILE* file = fopen(EDGES_FILE, "w");
    if (!file) {
        printf("Error opening file: %s\n", EDGES_FILE);
        return;
    }

    //  header line 
    fprintf(file, "from,to\n");

    //  each paper gets 1-20 random outgoing edges
    for (int i = 0; i < MAX_PAPERS; i++) {
        int numEdges = rand() % 20 + 1;
        for (int j = 0; j < numEdges; j++) {
            int to = rand() % MAX_PAPERS;
            //  avoid self loops
            if (to != i) {
                fprintf(file, "%d,%d\n", i, to);
            }
        }
    }

    fclose(file);
    printf("Edges written to %s\n", EDGES_FILE);
}

//  create both files
void create_data() {
    create_papers();
    create_edges();
}