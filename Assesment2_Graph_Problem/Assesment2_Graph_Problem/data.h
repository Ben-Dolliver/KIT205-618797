#ifndef DATA_H
#define DATA_H

#define MAX_AUTHORS 100
#define MAX_PAPERS 100
#define PAPER_FILE "test_papers.txt"
#define EDGES_FILE "test_edges.txt"
#define SAMPLE_SIZE 20

void create_data();
void create_papers();
void create_edges();
void print_data();
void clear_data();
#endif