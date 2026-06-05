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


//  find the shortest distance to a selectd node using Dijkstra's algorithm
int* dijkstra(Graph* self, int src) {

    int V = self->V;
    int* distance = malloc(V * sizeof(int));
    int* visited = malloc(V * sizeof(int));
	int current;          //  current node being processed 
	int w;                //  weight of edge
	int v;                //  destination node of edge

    //  initialise all starting distances to infinity 
    for (int i = 0; i < V; i++) {
        distance[i] = 999999;
        visited[i] = 0;
    }
    distance[src] = 0;

    for (int i = 0; i < V - 1; i++) {
        //  find unvisited node with smallest the distance
        current = -1;
        for (int j = 0; j < V; j++) {
            if (!visited[j] && (current == -1 || distance[j] < distance[current]))
                current = j;
        }
        if (distance[current] == 999999) break;  //   remaining nodes unreachable
        visited[current] = 1;

        //  update neighbours
        for (Node* cur = self->edges[current].head; cur != NULL; cur = cur->next) {
            v = cur->to;
            w = cur->weight; 
            if (!visited[v] && distance[current] + w < distance[v]) {
                distance[v] = distance[current] + w;
            }
        }
    }
    free(visited);
    return distance;
}

//  show shortest path from source to destination using Dijkstra's algorithm
void dijkstra_print(Graph* self, int src, int dest) {
    int* dist = dijkstra(self, src);

    printf("\nShortest path from %d to %d: ", src, dest);

    if (dist[dest] == 999999)
        printf("no path found\n");

    else {
    printf("years %d\n", dist[dest]);
    }

    free(dist);
}



//  load papers from file into graph
void load_papers(Graph* self, const char* filename) {

    int idx,        //  paper variable    
        paperID,    
        authorID,   
        year;       


    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening papers file: %s\n", filename);
        return;
    }

    //  skip header line
    char buffer[512];
    fgets(buffer, sizeof(buffer), file);

    while (fscanf_s(file, "%d %d %d %d", &idx, &paperID, &authorID, &year) == 4) {
        if (idx >= 0 && idx < self->V) {
            self->papers[idx].id = idx;
            self->papers[idx].paperID = paperID;
            self->papers[idx].authorID = authorID;
            self->papers[idx].year = year;
        }
    }
    fclose(file);


}

void print_papers(Graph* self) {

    printf("\nPapers:\n");
	for (int i = 0; i < self->V; i++) {
		Paper* p = &self->papers[i];
		printf("ID: %d, PaperID: %d, AuthorID: %d, Year: %d\n", p->id, p->paperID, p->authorID, p->year);
	}
}

//  load edges from file into graph
//  edge weight is the difference in publication year between two papers
void load_edges(Graph* self, const char* filename) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening edges file: %s\n", filename);
        return;
    }

    //  skip header line
    char buffer[512];
    fgets(buffer, sizeof(buffer), file);


	// for each line read from file, add edge to graph with weight as year difference
    int from, to;
    int count = 0;    //  debug counter

    while (fscanf_s(file, "%d %d", &from, &to) == 2) {
        if (from >= 0 && from < self->V &&
            to >= 0 && to < self->V) {
            //  weight = absolute year difference between papers
            int weight = abs(self->papers[from].year - self->papers[to].year);
            add_edge(self, from, to, weight);
            count++;

        }
    }

    fclose(file);
    printf("Loaded edges from %s\n", filename);
    printf("Loaded %d edges from %s\n", count, filename);

}

//  print specific paper
void print_paper(Graph* self, int id) {

    if (id < 0 || id >= self->V) {
        printf("Invalid paper ID: %d\n", id);
        return;
    }
    printf("  [%d] PaperID: %d | AuthorID: %d | Year: %d\n",
        id,
        self->papers[id].paperID,
        self->papers[id].authorID,
        self->papers[id].year);
}

//  print all nodes linked to specific node 
void print_adjacent(Graph* self, int id) {

	//  invalid
    if (id < 0 || id >= self->V) {
        printf("Invalid node ID: %d\n", id);
        return;
    }

    printf("\nPaper %d cites:\n", id);
    print_paper(self, id);

    Node* current = self->edges[id].head;
    //  no references 
    if (current == NULL) {
        printf("  No citations\n");
        return;
    }

    //  loop through all connected nodes
    while (current != NULL) {
        printf("  --> ");
        print_paper(self, current->to);
        current = current->next;
    }
}


void print_indegrees(Graph* self) {

    //  allocate in degrees and error check 
    int* indegree = malloc(self->V * sizeof(int));
    if (!indegree) {
        printf("Memory allocation failed\n");
        return;
    }

    //  initialise all in degree to 0
    for (int i = 0; i < self->V; i++) indegree[i] = 0;

    //  count incoming edges for each node
    for (int i = 0; i < self->V; i++) {
        for (Node* current = self->edges[i].head; current != NULL; current = current->next) {
            indegree[current->to]++;
        }
    }

    //  print results
    printf("\nIn-Degrees:\n");
    for (int i = 0; i < self->V; i++) {
        printf("  [%d] PaperID: %d | References: %d\n",
            i,
            self->papers[i].paperID,
            indegree[i]);
    }

    free(indegree);
}