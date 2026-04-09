// list_wk5.h
#pragma once

//TODO: change data type to char*
//Hint: use following typedef to make code clearer
typedef char* String;

typedef struct listNode {
	String data;
	struct listNode* next;
} *ListNodePtr;

typedef struct list {
	ListNodePtr head;
} List;


List new_list();

// print complete list
void print_list(List* self);

// inert node at front 
void insert_at_front(List* self, String data);

// delete node from the list 
void delete_from_list(List* self, String data);

// destroy the list 
void destroy_list(List* self);

// Function to test the program 
void list_test();

