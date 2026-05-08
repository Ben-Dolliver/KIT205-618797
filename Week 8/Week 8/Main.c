#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    Graph G;
    int result;

    FILE* file = fopen("graph.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    result = fscanf_s(file, "%d", &G.V);
    G.edges = malloc(G.V * sizeof(EdgeList));


    // initialise lists
    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }

    printf("Vertices: %d\n", G.V);

    fclose(file);
    return 0;
}