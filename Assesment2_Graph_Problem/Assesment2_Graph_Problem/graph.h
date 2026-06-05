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
    int id;
    int paperID;
    int authorID;
    int year;
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

//  papers functions 
void load_papers(Graph* self, const char* filename);
void load_edges(Graph* self, const char* filename);

//  print functions
void print_references(Graph* self);
void print_papers(Graph* self);
void print_paper_citations(Graph* self, int id);
void print_paper(Graph* self, int id);


#endif