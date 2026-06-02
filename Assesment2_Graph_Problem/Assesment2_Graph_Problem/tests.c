#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

int graph_test() {

    Graph G;        //  graph
    int result;     //  result
    int in;         //  verices in 
    int out;        //  vertices out
    //int weight;     //  vertex  weight, redundant currently 


    // Open file and error check 
    //FILE* file = fopen("../../datasets/musae_git_edges.csv", "r");
    FILE* file = fopen("test.txt", "r");

    if (!file) {    //  Error handling
        printf("Error opening file!\n");
        return 1;
    }

    // reads number of vertices and adjacency 
    result = fscanf_s(file, "%d", &G.V);
    G.edges = malloc(G.V * sizeof(EdgeList));


    //  initialise lists
    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }


    //  while loop to add all nodes with values from data file to the 
    while (fscanf_s(file, "%d,%d", &in, &out) == 2) {
        add_edge(&G, in, out, 0);
    }

    printf("Vertices: %d\n", G.V);

    //  create and initialise in-degree
    int* indegree = malloc(G.V * sizeof(int));


    if (!indegree) {    //  Error handling 
        printf("Memory allocation failed\n");
        return 1;
    }

    //  initialise in degree arrays
    for (int i = 0; i < G.V; i++) {
        indegree[i] = 0;
    }

    //  loop for calculating the in-degrees
    for (int i = 0; i < G.V; i++) {

        //  for current node of graph loop untill at end of list adding to in-degree 
        for (Node* current = G.edges[i].head; current != NULL; current = current->next) {
            indegree[current->to]++;    //  edge going INTO destination
        }
    }

    printf("\nIn-Degrees:\n");


    /*  finish & shutdown   */
    //  free all edge nodes
	free_graph(&G);

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



