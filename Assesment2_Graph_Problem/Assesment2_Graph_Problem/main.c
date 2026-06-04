#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "graph.h"



int main() {

    printf("-----[Week 8 Graphs Start]----- \n\n");

    create_data();  //  create the data files before testing 


  /*  Graph G;
    G.V = 20;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;*/

    graph_test();
    //test_dijkstra();

	//load_papers(&G, "test_papers.txt");
	//print_papers(&G);

    printf("\n-----[Week 8 Graphs Finish]----- \n\n");

    return 0;
}

