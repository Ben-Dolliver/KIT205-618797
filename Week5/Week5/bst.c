#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

// create an empty bst
BST new_bst() {
	BST temp;
	temp.root = NULL;
	return temp;
}

// recursive function to find a value and return the containing node
BSTNodePtr find_bst_node(BSTNodePtr self, int n) {
	if (self == NULL || (n == self->data_item)) { /* not present, or here */
		return self;
	}
	else if (n < self->data_item) {
		return find_bst_node(self->left, n);
	}
	else {
		return find_bst_node(self->right, n);
	}
}

// find a value in the tree and return the node
BSTNodePtr find_bst(BST* self, int n) {
	return find_bst_node(self->root, n);
}

// recursive function to insert a value
BSTNodePtr insert_bst_node(BSTNodePtr self, int n) {
	if (self == NULL) { /* found where to put it*/
		self = malloc(sizeof * self);
		self->data_item = n;
		self->left = self->right = NULL;
	}
	else if (n < self->data_item) {
		self->left = insert_bst_node(self->left, n);
	}
	else if (n > self->data_item) {
		self->right = insert_bst_node(self->right, n);
	}
	return self;
}

// insert a value into the tree
void insert_bst(BST* self, int n) {
	self->root = insert_bst_node(self->root, n);
}

// helper function for delete
BSTNodePtr min_node(BSTNodePtr self) {
	BSTNodePtr current = self;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// recursive function to delete a value
BSTNodePtr delete_bst_node(BSTNodePtr self, int n) {
	if (self != NULL) {
		if (n == self->data_item) { // found item 
			if (self->left != NULL && self->right != NULL) {
				// two child case 
				BSTNodePtr successor = min_node(self->right);
				self->data_item = successor->data_item;
				self->right = delete_bst_node(self->right, self->data_item);
			}
			else { // one or zero child case 
				BSTNodePtr to_free = self;
				if (self->left) {
					self = self->left;
				}
				else {
					self = self->right;
				}
				free(to_free);
			}
		}
		else if (n < self->data_item) {
			self->left = delete_bst_node(self->left, n);
		}
		else {
			self->right = delete_bst_node(self->right, n);
		}
	}
	return self;
}

// delete a value from the tree
void delete_bst(BST* self, int n) {
	self->root = delete_bst_node(self->root, n);
}

// recursive function to print in order
void print_in_order_bst_node(BSTNodePtr self) {
	if (self == NULL) {
		printf("_");
	}
	else {
		printf("(");
		print_in_order_bst_node(self->left);
		printf(" %d ", self->data_item);
		print_in_order_bst_node(self->right);
		printf(")");
	}
}

// print the tree in order
void print_in_order_bst(BST* self) {
	print_in_order_bst_node(self->root);
}

// recursive function to detroy all node
void destroy_bst_node(BSTNodePtr self) {
	if (self != NULL) {
		destroy_bst_node(self->left);
		self->left = NULL;
		destroy_bst_node(self->right);
		self->right = NULL;
		free(self);
	}
}

// destroy the tree
void destroy_bst(BST* self) {
	destroy_bst_node(self->root);
	self->root = NULL;
}



/*
	pre order traversal methods
*/
void print_pre_order_bst_node(BSTNodePtr self) {

	if (self == NULL) {
		printf("_");
	}

	else {
		printf("(");
		printf(" %d ", self->data_item);          // ROOT first
		print_pre_order_bst_node(self->left);     // then LEFT
		print_pre_order_bst_node(self->right);    // then RIGHT
		printf(")");
	}
}

void print_pre_order_bst(BST* self) {
	print_pre_order_bst_node(self->root);
}



/*
	post order first traversal methods
*/
void print_post_order_bst_node(BSTNodePtr self) {
	
	if (self == NULL) {
		printf("_");
	}

	else {
		printf("(");
		print_post_order_bst_node(self->left);    // LEFT first
		print_post_order_bst_node(self->right);   // then RIGHT
		printf(" %d ", self->data_item);          // ROOT last
		printf(")");
	}
}

void print_post_order_bst(BST* self) {
	print_post_order_bst_node(self->root);
}




void bst_adhoc_test() {
	BST tree = new_bst();
	int quit = 0;
	int data;
	while (quit == 0) {
		printf("Enter some data: ");
		scanf_s("%d", &data);
		if (data != 0) {
			insert_bst(&tree, data);
		}
		else {
			quit = 1;
		}
	}

	// testing of the functions 
	printf("\nprinting in order traversal\n");
	print_in_order_bst(&tree);
	
	printf("\n\nprinting pre order traversal\n");
	print_pre_order_bst(&tree);
	
	printf("\n\nprinting post order traversal\n");
	print_post_order_bst(&tree);
}


int height_bst_node(BSTNodePtr self) {
	// base case: empty tree
	if (self == NULL) {
		return -1;  // standard definition: empty tree = -1
	}

	// recursive calls
	int left_height = height_bst_node(self->left);
	int right_height = height_bst_node(self->right);

	// return max + 1
	if (left_height > right_height) {
		return left_height + 1;
	}
	else {
		return right_height + 1;
	}
}


int height_bst(BST* self) {
	if (self == NULL) {
		return 0; 
	}
	return height_bst_node(self->root);
}


void bst_test() {

	printf("[bst test start]\n\n");
	BST tree = new_bst();


	// Insert
	printf("Inserting values:\n");
	insert_bst(&tree, 5);
	insert_bst(&tree, 3);
	insert_bst(&tree, 7);
	insert_bst(&tree, 2);
	insert_bst(&tree, 4);
	insert_bst(&tree, 6);
	insert_bst(&tree, 8);

	printf("In-order :\n");
	print_in_order_bst(&tree);
	printf("\n\n");

	// ---- Test find ----
	printf("Find test:\n");
	BSTNodePtr found = find_bst(&tree, 4);
	if (found != NULL && found->data_item == 4) {
		printf("PASS: Found 4\n");
	}
	else {
		printf("FAIL: Did not find 4\n");
	}

	BSTNodePtr not_found = find_bst(&tree, 10);
	if (not_found == NULL) {
		printf("PASS: 10 not found\n");
	}
	else {
		printf("FAIL: Unexpectedly found 10\n");
	}
	printf("\n");

	// ---- Test traversal ----
	printf("Pre-order:\n");
	print_pre_order_bst(&tree);
	printf("\n");

	printf("Post-order:\n");
	print_post_order_bst(&tree);
	printf("\n\n");

	// ---- Test delete: leaf node ----
	printf("Delete leaf (2):\n");
	delete_bst(&tree, 2);
	print_in_order_bst(&tree);
	printf("\n\n");

	// ---- Test delete: two children ----
	printf("Delete node with two children (5):\n");
	delete_bst(&tree, 5);
	print_in_order_bst(&tree);
	printf("\n\n");

	// ---- Test Height ----
	printf("\nHeight test:\n");
	int h = height_bst(&tree);
	printf("Height of tree: %d\n", h);

	// ---- Test destroy ----
	printf("Destroy tree:\n");
	destroy_bst(&tree);
	if (tree.root == NULL) {
		printf("PASS: Tree destroyed\n");
	}
	else {
		printf("FAIL: Tree not destroyed\n");
	}



}


