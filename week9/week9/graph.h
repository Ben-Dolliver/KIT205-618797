#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    int to;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} EdgeList;

typedef struct {
    int V;
    EdgeList* edges;
} Graph;

void add_edge(Graph* self, int from, int to, int w);

double* calculate_pagerank(Graph* self, int iterations);

#endif