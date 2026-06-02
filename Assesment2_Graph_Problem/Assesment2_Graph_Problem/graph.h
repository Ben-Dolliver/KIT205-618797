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

//  academic paper structure
typedef struct {
    int   id;
    char  title[256];
    char  author[128];
    int   year;
} Paper;    

typedef struct {
    int        V;
    EdgeList* edges;
    Paper* papers; // array of papers 
} Graph;


//  dijkstra algorithm functions 
int* dijkstra(Graph* self, int src);
void dijkstra_print(Graph* self, int src, int dest);

//  generic graph functions
void free_graph(Graph* self);
void add_edge(Graph* self, int from, int to, int w);
double* calculate_pagerank(Graph* self, int iterations); // obsolete 

#endif