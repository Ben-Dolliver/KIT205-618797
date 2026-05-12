
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


//  Method to add a new edge node to the graph 
void add_edge(Graph* self, int from, int to, int w) {

    // allocate memory for new node
    Node* newNode = malloc(sizeof(Node));


    // error handling 
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // set node values
    newNode->to = to;
    newNode->weight = w;

    // insert at beginning of adjacency list
    newNode->next = self->edges[from].head;
    self->edges[from].head = newNode;
}




int main() {

    Graph G;        //  graph
    int result;     //  result
    int in;         //  verices in 
    int out;        //  vertices out
    int weight;     //  vertex 
    double d = 0.85;//  damping factor


    printf("-----[Week 8 Graphs Start]----- \n\n");

    // Open file and error check 
    FILE* file = fopen("C:/Users/Ben Dover/Documents/School/KIT205/datasets/musae_git_edges.csv", "r");
    if (file == NULL) {
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


    //  for loop to add all nodes with values from data file to the graph 

    while (fscanf_s(file, "%d,%d",
        &in, &out) == 2) {

        add_edge(&G, in, out, 0);
    }

    printf("Vertices: %d\n", G.V);


    //  create and initialise in-degree, out-degree, sums, and page-rank
    int* indegree = malloc(G.V * sizeof(int));
    int* outdegree = malloc(G.V * sizeof(int));
    double* sums = malloc(G.V * sizeof(double));
    double* pagerank = malloc(G.V * sizeof(double));


    //  error handling 
    if (!indegree || !outdegree || !sums || !pagerank) {
        printf("Memory allocation failed\n");
        return 1;
    }

    //  initialise an arrays
    for (int i = 0; i < G.V; i++) {

        indegree[i] = 0;
        outdegree[i] = 0;
        sums[i] = 0.0;
        pagerank[i] = 1.0;
    }

    //  loop for calculating the in-degrees
    for (int i = 0; i < G.V; i++) {


        //  for current node of graph loop untill at end of list adding to in-degree and out degree
        for (Node* current = G.edges[i].head; current != NULL; current = current->next) {

            indegree[current->to]++;    //  edge going INTO destination
            outdegree[i]++;              //  edge going OUT from i
        }
    }


    //  calculate sums
    for (int i = 0; i < G.V; i++) {
        for (Node* current = G.edges[i].head; current != NULL; current = current->next) {

            //  calculate sigma sums
            if (outdegree[i] > 0) {
                sums[current->to] += pagerank[i] / outdegree[i];
            }
        }
    }

    //  apply damping
    for (int i = 0; i < G.V; i++) {
        pagerank[i] = (1.0 - d) + (d * sums[i]);
    }

    printf("\nIn-Degrees:\n");  //  print in-degrees


    /*  finish & shutdown   */ 

    //  free all edge nodes
    for (int i = 0; i < G.V; i++) {
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

    fclose(file);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;
}

