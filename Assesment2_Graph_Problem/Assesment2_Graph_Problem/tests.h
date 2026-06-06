#include "graph.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>

//	testing for dijkstra's algorithm 
int test_dijkstra();
int run_graph_tests();
void investigate_path_length();

//	large scale dataset testing
void run_evaluation();

//	graph tests
int test_load_edges();
int test_load_papers();
int test_free_graph();
int test_directed_edge();
int test_add_multiple_edges();
int test_add_edge();


//  standard all testing output
void test_all();