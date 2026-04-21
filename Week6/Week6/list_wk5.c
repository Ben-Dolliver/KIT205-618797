// list_wk5.c
#define _CRT_SECURE_NO_WARNINGS	// making it ignore "scanf may not be safe"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_wk5.h"


//TODO: change data type to char*

List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// after changing to char*:
// -- need to change printf for string
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%s", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

// after changing to char*:
// -- check how long data parameter is (strlen)
// -- allocate just enough memory for newNode->data (malloc)
// -- copy string from parameter into newNode->data (strcpy)
void insert_at_front(List* self, String data) {
	ListNodePtr new_node = malloc(sizeof * new_node);
	
	new_node->data = malloc(strlen(data) + 1);
	strcpy(new_node->data, data);
	

	new_node->next = self->head;
	self->head = new_node;
}

// after changing to char*:
// -- change test in if statement to string compare (strcmp)
// -- free current->data (memory allocated for string) before freeing current
void delete_from_list(List* self, String data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (strcmp(current->data, data) == 0) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current->data);
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;

				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// after changing to char*:
// -- need to free memory allocated for string before freeing node
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;

		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}



void list_test() {

	
	printf("Testing insert_at_front... \n");
	List list = new_list();	// Create new list

	// Create a list with values a, b, c, d, e
	insert_at_front(&list, "a");
	insert_at_front(&list, "b");
	insert_at_front(&list, "c");
	insert_at_front(&list, "d");
	insert_at_front(&list, "e");

	// compare expected to true result
	printf("Expected: e, d, c, b, a\n");

	printf("result: ");
	print_list(&list);



}



