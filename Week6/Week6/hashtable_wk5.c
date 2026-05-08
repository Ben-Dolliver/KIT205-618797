// hashtable_wk5.c
#define _CRT_SECURE_NO_WARNINGS	// making it ignore "scanf may not be safe"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable_wk5.h"

HashTable create_hashtable(int n) {
	HashTable newtable;

	newtable.size = n;

	// allocate array of Lists
	newtable.table = malloc(n * sizeof(List));

	// initialise each list
	for (int i = 0; i < n; i++) {
		newtable.table[i] = new_list();
	}

	return newtable;
}

int hash(String key, int size) {
	unsigned long h = 0; // unsigned long, so that when it wraps it's still positive
	int n = strlen(key);

	for (int i = 0; i < n; i++) {
		// multiply by 32 (<<5) and add ascii value
		h = (h << 5) + (int)(key[i]);
	}
	return h % size;
}

void hash_insert(HashTable* self, String key) {
	// 1. find the list to insert into using hash
	// 2. call list function to insert into that list

	int index = hash(key, self->size);
	insert_at_front(&(self->table[index]), key);

}

void hash_remove(HashTable* self, String key) {
	int index = hash(key, self->size);
	delete_from_list(&(self->table[index]), key);
}

void hash_print(HashTable* self) {
	for (int i = 0; i < self->size; i++) {
		printf("%d: ", i);
		print_list(&(self->table[i]));
	}
}

void hash_destroy(HashTable* self) {
	for (int i = 0; i < self->size; i++) {
		destroy_list(&(self->table[i]));
	}
	free(self->table);
	self->table = NULL;
	self->size = 0;
}

void hash_adhoc_test() {
	int command = 1;
	HashTable table = create_hashtable(11);
	char buffer[100];
	char find[100];

	printf("\n		====[ Starting hash adhoc test ]====");


	while (command) {
		printf("\nEnter 0 to quit \nEnter 1 to insert \nEnter 2 to remove \nEnter 3 to print  \nChoice: ");
		scanf("%d", &command);
		switch (command) {
		case 1:
			printf("Instert string: ");
			scanf("%s", buffer, 100);
			hash_insert(&table, buffer);
			break;
		case 2: // TODO: remove
			printf("Instert string to be deleted: ");
			scanf("%s", find);
			hash_remove(&table, find);
			break;
		case 3: // TODO: print
			hash_print(&table);
			break;
		default:
			printf("Invalid input \n");
			break;
		}
		printf("\n");
	}
	// TODO: destroy
	hash_destroy(&table);
}