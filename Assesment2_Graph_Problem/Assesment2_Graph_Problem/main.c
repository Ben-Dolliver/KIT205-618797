#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "graph.h"


int main() {
    printf("-----[Week 8 Graphs Start]----- \n\n");

    create_data();

    

    Graph G;
    G.V = MAX_PAPERS;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    load_papers(&G, PAPER_FILE);
    load_edges(&G, EDGES_FILE);

	//print_paper(&G, 83);   
	//print_adjacent(&G, 14);

    //graph_test(&G);      // pass G in
    print_indegrees(&G);
    print_papers(&G);
    dijkstra_print(&G, 0, 10);

    free_graph(&G);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

