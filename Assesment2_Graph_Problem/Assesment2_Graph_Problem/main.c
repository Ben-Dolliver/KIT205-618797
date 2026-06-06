#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "graph.h"


int main() {

    srand((unsigned int)time(NULL));

    printf("-----[Week 8 Graphs Start]----- \n\n");

    //  standard test for all outputs
    test_all();

    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

