#ifndef DATA_H
#define DATA_H

#define MAX_AUTHORS 100000
#define MAX_PAPERS 100000
#define PAPER_FILE "test_papers.txt"
#define EDGES_FILE "test_edges.txt"
#define SAMPLE_SIZE 20

//  create papers and edges
void create_data(int numPapers, int numAuthors, int maxEdges);
//  create dataset of papers file 
void create_papers(int numPapers, int numAuthors);
//  create dataset of edges file
void create_edges(int numPapers, int maxEdges);

void print_data();
void clear_data();
#endif