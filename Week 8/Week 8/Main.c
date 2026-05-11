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
    FILE* file = fopen("graph.txt", "r");
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
    while (fscanf_s(file, "%d,%d,%d",
        &in, &out, &weight) == 3) {

        add_edge(&G, in, out, weight);
    }

    printf("Vertices: %d\n", G.V);



    //  create and initialise in-degree array
    int* indegree = malloc(G.V * sizeof(int));

    //  error handling 
    if (indegree == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    //  initialise an array of in-degrees
    for (int i = 0; i < G.V; i++) {
        indegree[i] = 0;
    }



    //  loop for calculating the in-degrees
    for (int i = 0; i < G.V; i++) {
        
        //  current node of graph
        Node* current = G.edges[i].head;

        //  loop untill at end of list adding to in-degree
        while (current != NULL) {
            indegree[current->to]++;
            current = current->next;
        }
    }

    // print in-degrees
    printf("\nIn-Degrees:\n");

    for (int i = 0; i < G.V; i++) {
        printf("Vertex %d: %d\n", i, indegree[i]);
    }


    // finish & shutdown code 
    fclose(file);
    printf("\n-----[Week 8 Graphs Finish]----- \n\n");
    return 0;   
}

