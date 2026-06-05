#include "tests.h"
#include <stdio.h>
#include <stdlib.h>




int graph_test(Graph* G) {

	//  initialise graph and edge variables         #### pass from main currently ####
    /*
    Graph G;
    int in, out;

	//  allocate variables for graph and edges
    G.V = MAX_PAPERS;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;
    */

    //  load papers and edges from generated files
    load_papers(&G, PAPER_FILE);
    load_edges(&G, EDGES_FILE);

    printf("Vertices: %d\n", G->V);

    //  calculate in-degrees
    int* indegree = malloc(G->V * sizeof(int));
    if (!indegree) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
	for (int i = 0; i < G->V; i++) indegree[i] = 0;  //  initialise indegree array

	//  loop through edges and count in-degrees
    for (int i = 0; i < G->V; i++) {
        for (Node* current = G->edges[i].head; current != NULL; current = current->next) {
            indegree[current->to]++;
        }
    }

	//  print in-degrees for each vertex
    printf("\nIn-Degrees:\n");
    for (int i = 0; i < G->V; i++) {
        printf("Vertex %d: %d\n", i, indegree[i]);
    }


    //  free data 
    free(indegree);
    free_graph(&G);
    return 0;
}

//  chosen algorithm test  
//  testing for dijkstra's algorithm, currently using a simple graph with known shortest paths
int test_dijkstra() {

    printf("\n=== TEST: Dijkstra's Algorithm ===\n");
    int passed = 0;
    int failed = 0;

    //  build a small chosen graph to verify against
    //  independent of the main graph G
    Graph T;
    T.V = 5;
    T.edges = malloc(T.V * sizeof(EdgeList));
    T.papers = malloc(T.V * sizeof(Paper));
    for (int i = 0; i < T.V; i++) {
        T.edges[i].head = NULL;
        T.papers[i].year = 2000 + i;  //  years 2000-2004
    }

    //  0 --(4)--> 1 --(3)--> 4
    //  0 --(2)--> 2 --(1)--> 3 --(5)--> 4
    //  shortest path 0 to 4 will be 0->2->3->4 = 8
    
    add_edge(&T, 0, 1, 4);
    add_edge(&T, 0, 2, 2);
    add_edge(&T, 1, 4, 3);
    add_edge(&T, 2, 3, 1);
    add_edge(&T, 3, 4, 5);

    int* dist = dijkstra(&T, 0);

	


    printf("TEST 1: source distance is 0... ");
    if (dist[0] == 0) {
        printf("PASS\n");
        passed++;
    }
    else {
        printf("FAIL (expected 0, got %d)\n", dist[0]);
        failed++;
    }

    printf("TEST 2: direct edge 0->1 costs 4... ");
    if (dist[1] == 4) {
        printf("PASS\n");
        passed++;
    }
    else {
        printf("FAIL (expected 4, got %d)\n", dist[1]);
        failed++;
    }

    //  0->2->3 = 2+1 = 3
    printf("TEST 3: cumulative path 0->2->3 costs 3... ");
    if (dist[3] == 3) {
        printf("PASS\n");
        passed++;
    }
    else {
        printf("FAIL (expected 3, got %d)\n", dist[3]);
        failed++;
    }

    //  shortest path test
    //  0->1->4 = 4+3 = 7
    //  0->2->3->4 = 2+1+5 = 8
    //  dijkstra should pick 7
    printf("TEST 4: shortest path 0->4 picks cheaper route (7)... ");
    if (dist[4] == 7) {
        printf("PASS\n");
        passed++;
    }
    else {
        printf("FAIL (expected 7, got %d)\n", dist[4]);
        failed++;
    }

    //  unreachable node test
    //  no edges point TO node 0 from anywhere
    //  so if we run from node 4, node 0 should be unreachable
    free(dist);
    dist = dijkstra(&T, 4);
    printf("TEST 5: unreachable node stays at 999999... ");
    if (dist[0] == 999999) {
        printf("PASS\n");
        passed++;
    }
    else {
        printf("FAIL (expected 999999, got %d)\n", dist[0]);
        failed++;
    }


    printf("TEST 6: same source and dest costs 0... ");
    if (dist[4] == 0) {
        printf("PASS\n");
        passed++;
    }
    else {
        printf("FAIL (expected 0, got %d)\n", dist[4]);
        failed++;
    }

    free(dist);
    free_graph(&T);

    //  summary
    printf("\nDijkstra tests: %d passed, %d failed\n", passed, failed);
    return failed;

}




//  Cannot be used currently for assignment algorithm but might become useful for something adjacent 
int pageRank_test(Graph* self, int iterations) {

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

//  
void investigate_path_length() {


    printf("\n=== INVESTIGATION: Graph Size vs Edge Count vs Avg Path Length ===\n");
    printf("%-10s %-10s %-10s %-10s\n",
        "Nodes", "MaxEdges", "AvgPath", "Connected%");
    printf("------------------------------------------\n");

    //  chosen graph sizes and edge counts to test
    int sizes[] = { 100, 500, 1000 };
    int maxEdges[] = { 5, 10, 15 };

	//  loop through combinations of sizes and edge counts
    for (int s = 0; s < 3; s++) {
        for (int e = 0; e < 3; e++) {
            int numPapers = sizes[s];
            int numEdges = maxEdges[e];

            //  generate graph with these parameters
            create_data(numPapers, numPapers / 5, numEdges);


            //  load into graph
            Graph G;
            G.V = numPapers;
            G.edges = malloc(G.V * sizeof(EdgeList));
            G.papers = malloc(G.V * sizeof(Paper));
            for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

            load_papers(&G, PAPER_FILE);
            load_edges(&G, EDGES_FILE);

            //  calculate average path length
            double avg = average_shortest_path(&G);

            //  calculate connectivity percentage
            int reachable = 0;
            int total = 0;
            for (int i = 0; i < G.V; i++) {
                int* dist = dijkstra(&G, i);
                for (int j = 0; j < G.V; j++) {
                    if (i != j) {
                        total++;
                        if (dist[j] != 999999) reachable++;
                    }
                }
                free(dist);
            }
            double connectivity = (double)reachable / total * 100;


            printf("%-10d %-10d %-10.2f %-10.1f%%\n",
                numPapers, numEdges, avg, connectivity);

            free_graph(&G);

        }


    }
}
