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


//  generate a random paper title from word banks
void rand_title(char* buffer) {
    int t = rand() % 10;
    int m = rand() % 10;
    sprintf_s(buffer, 128, "%s %s", topics[t], methods[m]);
}

//  check if the given ID already exists in the file for either an AUTHOR or PAPER entry
int exists(FILE* file, int id) {

    int currentID;
    char type[20];

    rewind(file);

    while (fscanf_s(file, "%19s %d", type, (unsigned)_countof(type), &currentID) == 2) {

        // compare AUTHOR  or PAPER entries
        if (strcmp(type, "AUTHOR") == 0 ||
            strcmp(type, "PAPER") == 0) {

            if (currentID == id) {

                return 1;
            }
        }
    }

    return 0;
}

int createRandAuthor(FILE* file) {

    int unique = 0;     //  unique identifier 
    int authorID;       //  ID of Author 



    // random author ID
    while (!unique) {
        authorID = rand() % MAX_AUTHORS + 100;
        unique = !exists(file, authorID);

    }

    // move back to end before writing
    fseek(file, 0, SEEK_END);

    // write to file
    fprintf(file, "AUTHOR %d\n", authorID);

    return authorID;
}



int createRandPaper(FILE* file) {

	int unique = 0;     //  is is the paper ID unique
    int paperID;        //  ID of the paper


    // generate unique paper ID
    while (!unique) {

        paperID = rand() % 100000 + 1000;
        unique = !exists(file, paperID);
    }


    //  move to end of file before writing
    fseek(file, 0, SEEK_END);

    //  write paper to file
    fprintf(file, "PAPER %d\n", paperID);

    return paperID;
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


void create_data() {

    //  seed random
    srand((unsigned int)time(NULL));

    //  open file
    FILE* file = fopen("test_papers.txt", "w");

    if (file == NULL) {

        printf_s("Error opening file\n");
        return;

    }

    //  write header
    fprintf_s(file, "id,paperID,authorID,year\n");


    //  write each paper
    for (int i = 0; i < MAX_PAPERS; i++) {
        char title[128];
        int author;
        int paper;
        int  year = rand() % 30 + 1994;   // 1994 - 2024


        //  create random authors
        author = createRandAuthor(file);


        //  create random papers
        paper = createRandPaper(file);
        
        fprintf_s(file, "%d,%s,%s,%d\n", i, paper, author, year);
    }




    fclose(file);

    printf("\nData written to test.txt\n");

    return;

}