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
    int weight;     //  vertex weight 

    
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



    //  create and initialise in-degree out degree and sums 
    int* indegree = malloc(G.V * sizeof(int));
    int* outdegree = malloc(G.V * sizeof(int));
    double* sums = malloc(G.V * sizeof(double));

    //  error handling 
    if (indegree == NULL || outdegree == NULL || sums == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    //  initialise an arrays
    for (int i = 0; i < G.V; i++) {
        indegree[i] = 0;
        outdegree[i] = 0;
        sums[i] = 0.0;
    }



    //  loop for calculating the in-degrees
    for (int i = 0; i < G.V; i++) {
        
        //  current node of graph
        Node* current = G.edges[i].head;

        //  loop untill at end of list adding to in-degree
        while (current != NULL) {

            // edge going INTO destination
            indegree[current->to]++;
            // edge going OUT from i
            outdegree[i]++;

            current = current->next;
        }
    }

    //  print in-degrees
    printf("\nIn-Degrees:\n");

    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i, indegree[i]);
    }


    //  finish & shutdown code 

    //  free all edge nodes
    for (int i = 0; i < G.V; i++) {
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

