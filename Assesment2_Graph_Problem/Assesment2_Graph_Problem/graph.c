#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//  Method to add a new edge node to the graph 
void add_edge(Graph* self, int from, int to, int w) {

    // allocate memory for new node
    Node* newNode = malloc(sizeof(Node));


    //   Error handling 
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }

    //  set node values
    newNode->to = to;
    newNode->weight = w;

    //  insert at beginning of adjacency list
    newNode->next = self->edges[from].head;
    self->edges[from].head = newNode;
}



//  Cannot be used as algorithm but will keep here anyways may become useful in some way 
double* calculate_pagerank(Graph* self, int iterations) {

    double d = 0.85;    //  damping factor 

    //  allocate arrays
    int* outdegree = malloc(self->V * sizeof(int));
    double* pagerank = malloc(self->V * sizeof(double));
    double* sums = malloc(self->V * sizeof(double));

    //  allocation error handling 
    if (!outdegree || !sums || !pagerank) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    //  initialise out-degree and page-rank arrays
    for (int i = 0; i < self->V; i++) {
        outdegree[i] = 0;
        pagerank[i] = 1.0;
    }

    //  for current node of graph loop untill at end of list adding to out degree
    for (int i = 0; i < self->V; i++) {
        for (Node* current = self->edges[i].head; current != NULL; current = current->next) {
            outdegree[i]++; //  edge going OUT from i
        }
    }

    //  PageRank iterations
    for (int k = 0; k < iterations; k++) {

        //  reset sums at start of loop 
        for (int i = 0; i < self->V; i++) {
            sums[i] = 0.0;
        }

        //  calculate sums
        for (int i = 0; i < self->V; i++) {

            for (Node* current = self->edges[i].head; current != NULL; current = current->next) {
                if (outdegree[i] > 0)
                    sums[current->to] += pagerank[i] / outdegree[i];
            }
        }
    }

    // apply damping factor
    for (int i = 0; i < self->V; i++) {
        pagerank[i] = (1.0 - d) + (d * sums[i]);
    }


    //  free data and return 
    free(outdegree);
    free(sums);
    return pagerank;
    free(pagerank);
}


// free memory 
void free_graph(Graph* self) {

    for (int i = 0; i < self->V; i++) {
        Node* current = self->edges[i].head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(self->edges);
    free(self->papers);
    self->edges = NULL;
    self->papers = NULL;
    self->V = 0;
}


//  Cannot be used currently for assignment algorithm but might become useful for something adjacent 
int pageRank_test(Graph* self, int iterations){

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