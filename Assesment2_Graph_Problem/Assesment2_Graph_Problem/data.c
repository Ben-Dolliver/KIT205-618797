#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

#define MAX_AUTHORS 100
#define MAX_PAPERS 100
#define FILE_NAME "test_papers.txt"

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


void clearData() {

    FILE* file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf_s("Failed to clear file\n");
        return;
    }

    fclose(file);
}


void printData() {

    FILE* file = fopen(FILE_NAME, "r");

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


//  create test_papers.txt 
void create_papers() {

    //  reset tracking arrays
    paperCount = 0;
    authorCount = 0;
    memset(usedPaperIDs, 0, sizeof(usedPaperIDs));
    memset(usedAuthorIDs, 0, sizeof(usedAuthorIDs));

    srand((unsigned int)time(NULL));

    FILE* file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error opening file: %s\n", FILE_NAME);
        return;
    }

    //  header line - skipped by load_papers
    fprintf(file, "id paperID authorID year\n");

    //  pre-generate unique author IDs
    int authors[MAX_AUTHORS];
    for (int i = 0; i < MAX_AUTHORS; i++) {
        authors[i] = rand_author_id();
    }

    //  write each paper — space separated to match fscanf_s "%d %d %d %d"
    for (int i = 0; i < MAX_PAPERS; i++) {
        int paperID = rand_paper_id();
        int authorID = authors[rand() % MAX_AUTHORS];  //  pick random existing author
        int year = rand() % 30 + 1994;             //  1994 - 2024

        fprintf(file, "%d %d %d %d\n", i, paperID, authorID, year);
    }

    fclose(file);
    printf("Papers written to %s (%d papers, %d authors)\n",
        FILE_NAME, MAX_PAPERS, MAX_AUTHORS);
}