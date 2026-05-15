#include <stdio.h>
#include "database.h"
#include "data.h"


int main() {
	Database db;


	printf("\n--------[database program start]--------\n");
	db.authorHead = NULL;
	db.paperHead = NULL;
	create_data();
	printData();
	

	




	return 0;
}