#include <stdio.h>
#include "database.h"
#include "data.h"






int main() {

	printf("\n--------[database program start]--------\n");

	create_data();
	printData();

	/*
	
	Database db = createDatabase();

	addAuthor(&db, 101);
	addAuthor(&db, 102);

	addPaper(&db, 2001);
	addPaper(&db, 2002);

	addAuthorship(&db, 101, 2001);
	addAuthorship(&db, 101, 2002);

	addAuthorship(&db, 102, 2001);

	
	*/

	




	return 0;
}