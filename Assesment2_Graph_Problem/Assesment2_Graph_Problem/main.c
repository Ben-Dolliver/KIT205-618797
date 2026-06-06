#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "graph.h"


int main() {

    srand((unsigned int)time(NULL));

    printf("-----[Week 8 Graphs Start]----- \n\n");

    investigate_path_length();
	test_dijkstra();
    run_graph_tests();
    //create_data(1000, 1000, 20);
    run_evaluation();





    //free_graph(&G);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

