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
