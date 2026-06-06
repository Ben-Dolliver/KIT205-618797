#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



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


//  specific problem unit test 
void investigate_path_length() {


    printf("\n=== INVESTIGATION: Graph Size vs Edge Count vs Avg Path Length ===\n");
    printf("%-10s %-10s %-10s %-10s\n",
        "Nodes", "MaxEdges", "AvgPath", "Connected%");
    printf("------------------------------------------\n");

    //  chosen graph sizes and edge counts to test
    int sizes[] = { 10, 50, 200, 400 };
    int maxEdges[] = { 5, 10, 15, 20 };

	//  loop through combinations of sizes and edge counts
    for (int s = 0; s < 4; s++) {
        for (int e = 0; e < 4; e++) {
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



// ─── Unit Tests for Graph Data Structure ──────────────────────

int test_add_edge() {
    printf("\nTEST: add_edge...\n");

    Graph G;
    G.V = 3;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));

    printf("  Creating graph with %d vertices\n", G.V);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
        printf("  Initialised vertex %d\n", i);
    }

    printf("  Adding edge 0 -> 1 (weight=5)\n");
    add_edge(&G, 0, 1, 5);

    printf("  Verifying edge exists...\n");
    if (G.edges[0].head == NULL) {
        printf("FAIL (no edge created)\n");
        free_graph(&G);
        return 1;
    }

    printf("    Found edge\n");
    printf("    Destination = %d\n", G.edges[0].head->to);
    printf("    Weight      = %d\n", G.edges[0].head->weight);

    if (G.edges[0].head->to != 1) {
        printf("FAIL (wrong destination)\n");
        free_graph(&G);
        return 1;
    }

    if (G.edges[0].head->weight != 5) {
        printf("FAIL (wrong weight)\n");
        free_graph(&G);
        return 1;
    }

    printf("  Freeing graph\n");
    free_graph(&G);

    printf("PASS\n\n");
    return 0;
}

int test_add_multiple_edges() {
    printf("TEST: add_multiple_edges...\n");

    Graph G;
    G.V = 3;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));

    printf("  Creating graph with %d vertices\n", G.V);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
        printf("  Initialised vertex %d\n", i);
    }

    printf("  Adding edge 0 -> 1 (weight=3)\n");
    add_edge(&G, 0, 1, 3);

    printf("  Adding edge 0 -> 2 (weight=7)\n");
    add_edge(&G, 0, 2, 7);

    printf("  Traversing adjacency list for node 0\n");

    int count = 0;
    for (Node* cur = G.edges[0].head; cur != NULL; cur = cur->next) {
        printf("    Edge %d: 0 -> %d (weight=%d)\n",
            count + 1,
            cur->to,
            cur->weight);
        count++;
    }

    printf("  Total edges found = %d\n", count);
    printf("  Expected edges    = 2\n");

    if (count != 2) {
        printf("FAIL (expected 2 edges, got %d)\n", count);
        free_graph(&G);
        return 1;
    }

    printf("  Edge count verified\n");

    free_graph(&G);

    printf("PASS\n");
    return 0;
}

int test_directed_edge() {
    printf("\nTEST: edges are directed...\n");

    Graph G;
    G.V = 3;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));

    printf("  Creating graph with %d vertices\n", G.V);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
        printf("  Initialised vertex %d\n", i);
    }

    printf("  Adding edge 0 -> 1 (weight=5)\n");
    add_edge(&G, 0, 1, 5);

    printf("\n  Current adjacency lists:\n");

    for (int i = 0; i < G.V; i++) {
        printf("    Node %d:", i);

        Node* cur = G.edges[i].head;

        if (cur == NULL)
            printf(" (none)");

        while (cur != NULL) {
            printf(" -> %d(w=%d)",
                cur->to,
                cur->weight);
            cur = cur->next;
        }

        printf("\n");
    }

    printf("\n  Checking that edge 0 -> 1 exists...\n");

    if (G.edges[0].head == NULL) {
        printf("FAIL (edge 0->1 missing)\n");
        free_graph(&G);
        return 1;
    }

    printf("    Found edge 0 -> %d\n",
        G.edges[0].head->to);

    printf("  Checking that reverse edge 1 -> 0 does NOT exist...\n");

    if (G.edges[1].head != NULL) {
        printf("FAIL (reverse edge 1->0 should not exist)\n");
        free_graph(&G);
        return 1;
    }

    printf("    No reverse edge found\n");

    free_graph(&G);

    printf("PASS\n");
    return 0;
}

int test_free_graph() {
    printf("\nTEST: free_graph...\n");

    Graph G;
    G.V = 3;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));

    printf("  Creating graph with %d vertices\n", G.V);

    for (int i = 0; i < G.V; i++) {
        G.edges[i].head = NULL;
    }

    printf("  Adding edge 0 -> 1 (weight=5)\n");
    add_edge(&G, 0, 1, 5);

    printf("  Adding edge 1 -> 2 (weight=3)\n");
    add_edge(&G, 1, 2, 3);

    printf("\n  Graph contents before free:\n");

    for (int i = 0; i < G.V; i++) {
        printf("    Node %d:", i);

        Node* cur = G.edges[i].head;

        if (cur == NULL)
            printf(" (none)");

        while (cur != NULL) {
            printf(" -> %d(w=%d)",
                cur->to,
                cur->weight);
            cur = cur->next;
        }

        printf("\n");
    }

    printf("\n  Calling free_graph()\n");

    free_graph(&G);

    printf("  Graph state after free:\n");
    printf("    V      = %d\n", G.V);
    printf("    edges  = %p\n", (void*)G.edges);
    printf("    papers = %p\n", (void*)G.papers);

    printf("\n  Verifying cleanup...\n");

    if (G.V != 0) {
        printf("FAIL (V should be 0 after free, got %d)\n", G.V);
        return 1;
    }

    if (G.edges != NULL) {
        printf("FAIL (edges should be NULL after free)\n");
        return 1;
    }

    if (G.papers != NULL) {
        printf("FAIL (papers should be NULL after free)\n");
        return 1;
    }

    printf("    Vertex count reset\n");
    printf("    Edge array freed\n");
    printf("    Paper array freed\n");

    printf("PASS\n");
    return 0;
}

int test_load_papers() {
    printf("\nTEST: load_papers... ");

    //  create small known papers file
    FILE* f = fopen("test_unit_papers.txt", "w");
    if (!f) {
        printf("FAIL (could not create test file)\n");
        return 1;
    }
    fprintf(f, "id paperID authorID year\n");
    fprintf(f, "0 11111 101 2000\n");
    fprintf(f, "1 22222 102 2010\n");
    fprintf(f, "2 33333 103 2020\n");
    fclose(f);

    Graph G;
    G.V = 3;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    printf("\n Loading papers from test_unit_papers.txt\n");
    load_papers(&G, "test_unit_papers.txt");

    printf("  Papers loaded:\n");
    for (int i = 0; i < G.V; i++) {
        printf("    [%d] paperID=%d authorID=%d year=%d\n",
            i,
            G.papers[i].paperID,
            G.papers[i].authorID,
            G.papers[i].year);
    }

    //  verify known values loaded correctly
    if (G.papers[0].paperID != 11111) {
        printf("FAIL (expected paperID 11111, got %d)\n",
            G.papers[0].paperID);
        free_graph(&G);
        return 1;
    }
    if (G.papers[1].year != 2010) {
        printf("FAIL (expected year 2010, got %d)\n",
            G.papers[1].year);
        free_graph(&G);
        return 1;
    }
    if (G.papers[2].authorID != 103) {
        printf("FAIL (expected authorID 103, got %d)\n",
            G.papers[2].authorID);
        free_graph(&G);
        return 1;
    }
    free_graph(&G);
    printf("PASS\n");
    return 0;
}

int test_load_edges() {

    printf("\nTEST: load_edges... ");

    //  create small known papers file first (needed for year weights)
    FILE* f = fopen("test_unit_papers.txt", "w");
    fprintf(f, "id paperID authorID year\n");
    fprintf(f, "0 11111 101 2000\n");
    fprintf(f, "1 22222 102 2005\n");
    fprintf(f, "2 33333 103 2010\n");
    fclose(f);

    //  create small known edges file
    FILE* e = fopen("test_unit_edges.txt", "w");
    fprintf(e, "from,to,weight\n");
    fprintf(e, "1 0 5\n");   // weight = 2005 - 2000 = 5
    fprintf(e, "2 1 5\n");   // weight = 2010 - 2005 = 5
    fclose(e);

    Graph G;
    G.V = 3;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    load_papers(&G, "test_unit_papers.txt");

    printf("  Loading edges from test_unit_edges.txt\n");
    load_edges(&G, "test_unit_edges.txt");

    printf("  Adjacency lists:\n");

    for (int i = 0; i < G.V; i++) {
        printf("    Node %d:", i);

        Node* cur = G.edges[i].head;

        if (!cur)
            printf(" (none)");

        while (cur) {
            printf(" -> %d(w=%d)",
                cur->to,
                cur->weight);
            cur = cur->next;
        }

        printf("\n");
    }
    printf("  Adjacency lists:\n");

    for (int i = 0; i < G.V; i++) {
        printf("    Node %d:", i);

        Node* cur = G.edges[i].head;

        if (!cur)
            printf(" (none)");

        while (cur) {
            printf(" -> %d(w=%d)",
                cur->to,
                cur->weight);
            cur = cur->next;
        }

        printf("\n");
    }
    //  verify edge 1->0 exists with weight 5
    if (G.edges[1].head == NULL) {
        printf("FAIL (edge 1->0 missing)\n\n");
        free_graph(&G);
        return 1;
    }
    if (G.edges[1].head->weight != 5) {
        printf("FAIL (expected weight 5, got %d)\n\n",
            G.edges[1].head->weight);
        free_graph(&G);
        return 1;
    }
    free_graph(&G);
    printf("PASS\n\n");
    return 0;
}

//  run all graph data structure tests
int run_graph_tests() {
    printf("\n=== Unit Tests: Graph Data Structure ===\n");
    int failures = 0;
    failures += test_add_edge();
    failures += test_add_multiple_edges();
    failures += test_directed_edge();
    failures += test_free_graph();
    failures += test_load_papers();
    failures += test_load_edges();
    printf(failures == 0
        ? "All graph tests passed\n"
        : "%d graph test(s) failed\n", failures);
    return failures;
}



void run_evaluation() {
    printf("\n=== Evaluation: Moderately Sized Citation Network ===\n");

    int numPapers = 5000;
    int numAuthors = 5000;
    int maxEdges = 15;

    printf("Graph parameters:\n");
    printf("  Papers:  %d\n", numPapers);
    printf("  Authors: %d\n", numAuthors);
    printf("  Max citations per paper: %d\n\n", maxEdges);

    //  generate and load graph
    create_data(numPapers, numAuthors, maxEdges);

    Graph G;
    G.V = numPapers;
    G.edges = malloc(G.V * sizeof(EdgeList));
    G.papers = malloc(G.V * sizeof(Paper));
    for (int i = 0; i < G.V; i++) G.edges[i].head = NULL;

    load_papers(&G, PAPER_FILE);
    load_edges(&G, EDGES_FILE);

    // ─── 1. Basic Graph Statistics ────────────────────────────
    printf("--- Graph Statistics ---\n");

    //  count total edges
    int totalEdges = 0;
    int maxIndegree = 0;
    int maxOutdegree = 0;
    int isolated = 0;
    int* indegree = malloc(G.V * sizeof(int));
    int* outdegree = malloc(G.V * sizeof(int));
    for (int i = 0; i < G.V; i++) {
        indegree[i] = 0;
        outdegree[i] = 0;
    }
    for (int i = 0; i < G.V; i++) {
        for (Node* cur = G.edges[i].head; cur != NULL; cur = cur->next) {
            totalEdges++;
            outdegree[i]++;
            indegree[cur->to]++;
        }
    }
    for (int i = 0; i < G.V; i++) {
        if (indegree[i] > maxIndegree)  maxIndegree = indegree[i];
        if (outdegree[i] > maxOutdegree) maxOutdegree = outdegree[i];
        if (indegree[i] == 0 && outdegree[i] == 0) isolated++;
    }
    printf("  Total edges:       %d\n", totalEdges);
    printf("  Avg edges/paper:   %.2f\n", (double)totalEdges / G.V);
    printf("  Max in-degree:     %d\n", maxIndegree);
    printf("  Max out-degree:    %d\n", maxOutdegree);
    printf("  Isolated nodes:    %d\n\n", isolated);
    free(indegree);
    free(outdegree);

    // ─── 2. Most Cited Papers ─────────────────────────────────
    printf("--- Top 5 Most Cited Papers ---\n");
    int* citations = malloc(G.V * sizeof(int));
    for (int i = 0; i < G.V; i++) citations[i] = 0;
    for (int i = 0; i < G.V; i++) {
        for (Node* cur = G.edges[i].head; cur != NULL; cur = cur->next) {
            citations[cur->to]++;
        }
    }
    //  find top 5 by simple selection
    for (int t = 0; t < 5; t++) {
        int best = 0;
        for (int i = 1; i < G.V; i++) {
            if (citations[i] > citations[best]) best = i;
        }
        printf("  [%d] PaperID: %d | AuthorID: %d | Year: %d | Citations: %d\n",
            best,
            G.papers[best].paperID,
            G.papers[best].authorID,
            G.papers[best].year,
            citations[best]);
        citations[best] = -1;   //  exclude from next search
    }
    free(citations);
    printf("\n");

    // ─── 3. Shortest Path Examples ────────────────────────────
    printf("--- Shortest Path Examples (Dijkstra's) ---\n");

    //  find a few interesting pairs to demonstrate
    int pairs[4][2] = {
        {0,   numPapers - 1},   //  first to last
        {0,   numPapers / 4},   //  first to quarter
        {numPapers / 4, numPapers / 2},   //  quarter to half
        {numPapers / 2, numPapers - 1}    //  half to last
    };

    for (int p = 0; p < 4; p++) {
        int src = pairs[p][0];
        int dest = pairs[p][1];
        int* dist = dijkstra(&G, src);

        printf("  From [%d] Year:%d  To [%d] Year:%d  -->  ",
            src, G.papers[src].year,
            dest, G.papers[dest].year);

        if (dist[dest] == 999999)
            printf("No path found\n");
        else
            printf("Cost: %d (year-weighted distance)\n", dist[dest]);

        free(dist);
    }
    printf("\n");

    // ─── 4. Connectivity Analysis ─────────────────────────────
    printf("--- Connectivity Analysis ---\n");
    int reachable = 0;
    int total = G.V * (G.V - 1);

    //  sample 50 random source nodes for speed
    for (int s = 0; s < 50; s++) {
        int src = rand() % G.V;
        int* dist = dijkstra(&G, src);
        for (int j = 0; j < G.V; j++) {
            if (j != src && dist[j] != 999999) reachable++;
        }
        free(dist);
    }
    double connectivity = (double)reachable / (50 * (G.V - 1)) * 100;
    printf("  Estimated connectivity: %.1f%%\n\n", connectivity);

    // ─── 5. Average Shortest Path ─────────────────────────────
    printf("--- Average Shortest Path ---\n");
    double avg = average_shortest_path(&G);
    if (avg < 0)
        printf("  No paths found\n");
    else
        printf("  Average year-weighted path length: %.2f\n\n", avg);

    // ─── 6. Sample In/Out Degrees ─────────────────────────────
    printf("--- Sample of Papers (first %d) ---\n", SAMPLE_SIZE);
    print_papers(&G);

    free_graph(&G);
    printf("\n=== Evaluation Complete ===\n");
}