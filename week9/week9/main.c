
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


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

            for (Node* current = self->edges[i].head;
                current != NULL;
                current = current->next) {

                if (outdegree[i] > 0) {

                    sums[current->to] +=
                        pagerank[i] / outdegree[i];
                }
            }
        }

        // apply damping factor
        for (int i = 0; i < self->V; i++) {

            pagerank[i] =
                (1.0 - d) +
                (d * sums[i]);
        }
    }



    //  free data and return 
    free(outdegree);
    free(sums);
    return pagerank;
    free(pagerank);
}




int main() {

    Graph G;        //  graph
    int result;     //  result
    int in;         //  verices in 
    int out;        //  vertices out
    //int weight;     //  vertex  weight, redundant currently 


    printf("-----[Week 8 Graphs Start]----- \n\n");

    // Open file and error check 
    //FILE* file = fopen("C:/Users/Ben Dover/Documents/School/KIT205/datasets/musae_git_edges.csv", "r");
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



    double* pagerank = calculate_pagerank(&G, 10);

    
    if (!pagerank) {    //  Error handling 
        printf("Error in pagerank\n");
        return 1;
    }

    printf("\nPageRanks:\n");

    for (int i = 0; i < 20 && i < G.V; i++) {   //  print pagerank 
        printf("Vertex %d: %.4f\n", i, pagerank[i]);
    }


    printf("\nIn-Degrees:\n");  
    /*  finish & shutdown   */ 

    //  free all edge nodes
    for (int i = 0; i < G.V; i++) {

        // print vertex in-degrees 
        printf("Vertex %d: %d\n", i, indegree[i]);
        Node* current = G.edges[i].head;

        //  loop through all nodes clearing data
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }


    //  free arrays
    free(G.edges);
    free(indegree);
    free(pagerank);
    fclose(file);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

