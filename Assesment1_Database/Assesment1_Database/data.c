#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"

#define MAX_AUTHORS 100
#define MAX_PAPERS 100
#define FILE_NAME "test.txt"




int createRandAuthor(FILE* file) {

    // random author ID
    int authorID = rand() % MAX_AUTHORS + 1;

    // write to file
    fprintf(file, "AUTHOR ID %d\n", authorID);

    return authorID;
}



int createRandPaper(FILE* file) {

    // random paper ID
    int paperID = rand() % MAX_PAPERS + 1000;

    // write to file
    fprintf(file, "PAPER %d\n", paperID);

    return paperID;
}


void clearData() {

    FILE* file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf("Failed to clear file\n");
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
        printf("%s", line);
    }

    fclose(file);

}


void create_data() {

    // seed random
    srand((unsigned int)time(NULL));

    // open file
    FILE* file = fopen("test.txt", "w");

    if (file == NULL) {

        printf("Error opening file\n");
        return;

    }


    // create random authors
    for (int i = 0; i < MAX_AUTHORS; i++) {

        createRandAuthor(file);
    }


    // create random papers
    for (int i = 0; i < MAX_PAPERS; i++) {

        createRandPaper(file);
    }


    fclose(file);

    printf("\nData written to test.txt\n");

    return;

}