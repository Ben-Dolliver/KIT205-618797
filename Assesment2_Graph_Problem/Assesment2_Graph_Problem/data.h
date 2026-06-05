#ifndef DATA_H
#define DATA_H

#define MAX_AUTHORS 10000
#define MAX_PAPERS 10000
#define PAPER_FILE "test_papers.txt"
#define EDGES_FILE "test_edges.txt"
#define SAMPLE_SIZE 20

void create_data(int numPapers, int numAuthors, int maxEdges);
void create_papers(int numPapers, int numAuthors);
void create_edges(int numPapers, int maxEdges);
void print_data();
void clear_data();
#endif