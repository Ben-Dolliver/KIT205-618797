#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "graph.h"


int main() {

    //  initialise values 
    int numPapers = 500;
    int numAuthors = 50;
    int maxEdges = 20;



    printf("-----[Week 8 Graphs Start]----- \n\n");

	//test_dijkstra();
    create_data(numPapers, numAuthors, maxEdges);

    Graph G;
    G.V = numPapers;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    load_papers(&G, PAPER_FILE);
    load_edges(&G, EDGES_FILE);

	print_paper(&G, 25);   
    print_paper_citations(&G, 25);

    //graph_test(&G);      // pass G in
    print_references(&G);
    print_papers(&G);
    dijkstra_print(&G, 0, 100);



    //free_graph(&G);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

