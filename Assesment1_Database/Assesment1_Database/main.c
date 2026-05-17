#include <stdio.h>
#include "database.h"
#include "data.h"
#include "database2.h"
#include "bst.h"
#include "hashtable.h"







int main() {

	printf("\n				--------[DATABASE PROGRAM START]--------\n\n\n\n");

	//create_data();
	//printData();

	databaseTesting();
	database2_testing(); 
	testBST();
	
	hashtableTesting();


	printf("\n\n\n\n				--------[DATABASE PROGRAM END]--------\n");


	return 0;
}