#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// Function to create and return a new empty list.
List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// Function to print the contents of a list.
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%d", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

void option_insert(List* self) {
	int input; //scanf input
	
	printf("\nEnter a number to insert (0 to exit): ");
	scanf_s("%d", &input);

	// add to list until user exits 
	while (input != 0) {

		insert_in_order(self, input);

		printf("Enter a number to insert (0 to exit): ");
		scanf_s("%d", &input);
	}
}

void option_delete(List* self) {
	int input;	// scanf input

	printf("\nEnter a number to delete (0 to exit): ");
	scanf_s("%d", &input);

	// delete from the list until user exits 
	while (input != 0) {

		delete_list(self, input);

		printf("Enter a number to delete (0 to exit): ");
		scanf_s("%d", &input);
	}
}

void option_print(List* self) {

	printf("\nCurrent list: ");
	print_list(self);
}

List reverse(List* self) {

	List new_list_result = new_list();	// temp list to be reversed

	// through the old list adding to the new list
	ListNodePtr current = self->head;
	while (current != NULL) {
		insert_at_front(&new_list_result, current->data);
		current = current->next;
	}

	return new_list_result;
}

List merge(List* list1, List* list2) {
	List result = new_list();	// new list to merge old lists into 

	ListNodePtr current = list1->head;
	while (current != NULL) {
		insert_in_order(&result, current->data);
		current = current->next;
	}

	current = list2->head;
	while (current != NULL) {
		insert_in_order(&result, current->data);
		current = current->next;
	}

	return result;
}

void list_test() {

	List list = new_list();	// Create new list
	printf("Testing insert_at_front... \n");

	// Create a list with values 0, 2, 7, 3, 5
	insert_at_front(&list,5);
	insert_at_front(&list, 3);
	insert_at_front(&list, 7);
	insert_at_front(&list, 2);
	insert_at_front(&list, 0);

	// compare expected to true result
	printf("Expected: 0, 2, 7, 3, 5 \n");
	
	printf("result: ");
	print_list(&list);



}

void list_adhoc_test() {

	List my_list = new_list();	// main list 
	int input;					// scanf input
	int quit = 0;				// quitting variable
	printf("[List adhoc test]\n");

	while (!quit) {
		int option;		// option number
		
		// Menu display and input
		printf("\nEnter 0 to quit \nEnter 1 to insert \nEnter 2 to delete \nEnter 3 to print \nEnter 4 to reverse \nChoice: ");
		scanf_s("%d", &option);

		// 
		switch (option) {
		case 0:
			quit = 1;
			break;

		case 1:
			option_insert(&my_list);
			break;

		case 2:
			option_delete(&my_list);
			break;

		case 3:
			option_print(&my_list);
			break;

		case 4:
			my_list = reverse(&my_list);
			printf("\nList has been reversed\n");
			break;


		default:
			printf("Invalid option. Try again.\n");
			break;
		}
	}
	// start testing once done 
	

	// reverse test
	printf("\n--- Testing reverse ---\n");
	List reversed = reverse(&my_list);
	print_list(&reversed);

	// merge test
	printf("\n--- Testing merge ---\n");

	// create and add to 2 new lists
	List list1 = new_list();
	List list2 = new_list();

	insert_in_order(&list1, 1);
	insert_in_order(&list1, 3);
	insert_in_order(&list1, 5);

	insert_in_order(&list2, 2);
	insert_in_order(&list2, 4);
	insert_in_order(&list2, 6);

	// show finish list
	printf("List 1: ");
	print_list(&list1);

	printf("List 2: ");
	print_list(&list2);

	// merge and show finished products
	List merged = merge(&list1, &list2);

	printf("Merged: ");
	print_list(&merged);

	// cleanup
	destroy_list(&reversed);
	destroy_list(&list1);
	destroy_list(&list2);
	destroy_list(&merged);
	destroy_list(&my_list);
}

// Function to insert a new node with given data at the front of the list.
void insert_at_front(List* self, int data) {
	ListNodePtr new_node = malloc(sizeof * new_node);

	new_node->data = data;
	new_node->next = self->head;
	self->head = new_node;
}

// Function to insert a new node with given data in the list in ascending order.
void insert_in_order(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = data;
	new_node->next = NULL;

	while (current != NULL && current->data < data) {
		prev = current;
		current = current->next;
	}

	if (current == self->head) { // at front
		new_node->next = current;
		self->head = new_node;
	}
	else {                     // middle
		new_node->next = current;
		prev->next = new_node;
	}
}

// Function to delete the first occurrence of a node with given data from the list.
void delete_list(List* self, int data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (current->data == data) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
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

// Function to free the memory allocated to a list and all its nodes.
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;
		current = current->next;
		free(to_free);
	}
	self->head = NULL;
}