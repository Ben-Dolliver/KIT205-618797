#include "tests.h"
#include <stdio.h>
#include <stdlib.h>




int graph_test() {

	//  initialise graph and edge variables
    Graph G;
    int in, out;

	//  allocate variables for graph and edges
    G.V = MAX_PAPERS;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    //  load papers and edges from generated files
    load_papers(&G, PAPER_FILE);
    load_edges(&G, EDGES_FILE);

    printf("Vertices: %d\n", G.V);

    //  calculate in-degrees
    int* indegree = malloc(G.V * sizeof(int));
    if (!indegree) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
	for (int i = 0; i < G.V; i++) indegree[i] = 0;  //  initialise indegree array
    for (int i = 0; i < G.V; i++) {
        for (Node* current = G.edges[i].head; current != NULL; current = current->next) {
            indegree[current->to]++;
        }
    }

	//  print in-degrees for each vertex
    printf("\nIn-Degrees:\n");
    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i, indegree[i]);
    }


    //  free data 
    free(indegree);
    free_graph(&G);
    return 0;
}

//    testing for dijkstra's algorithm, currently using a simple graph with known shortest paths
int test_dijkstra() {

    printf("TEST: dijkstra... ");

    Graph G;
    G.V = 4;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    add_edge(&G, 0, 1, 1);
    add_edge(&G, 1, 2, 2);
    add_edge(&G, 0, 2, 10);  // longer direct path
    add_edge(&G, 2, 3, 1);

    int* dist = dijkstra(&G, 0);

    dijkstra_print(&G, 0, 3);
    
    if (dist[2] != 3) {
        printf("FAIL (expected 3, got %d)\n", dist[2]);
        free(dist);
        free_graph(&G);
        return 1;
    }


	

    free(dist);
    free_graph(&G);
    printf("PASS\n");
    return 0;
}




//  Cannot be used currently for assignment algorithm but might become useful for something adjacent 
int pageRank_test(Graph* self, int iterations) {

    Graph G = *self;        //  graph


    double* pagerank = calculate_pagerank(&G, 10);

    if (!pagerank) {    //  Error handling 
        printf("Error in pagerank\n");
        return 1;
    }

    printf("\nPageRanks:\n");

    //  modify this one for display length c.g. (i < 20 &&)
    for (int i = 0; i < G.V; i++) {   //  print pagerank 
        printf("Vertex %d: %.4f\n", i, pagerank[i]);
    }

    free(pagerank);

    return 0;
}



