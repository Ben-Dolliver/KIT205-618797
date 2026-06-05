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
    create_data(1000, 1000, 20);


	//print_paper(&G, 25);   
 //   print_paper_citations(&G, 25);

 //   //graph_test(&G);      // pass G in
 //   print_references(&G);
 //   print_papers(&G);
 //   dijkstra_print(&G, 0, 100);




    //free_graph(&G);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

