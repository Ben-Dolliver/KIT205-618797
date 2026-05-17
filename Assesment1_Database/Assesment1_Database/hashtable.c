#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"


//  hash function for authors 
int hashAuthor(int id) {

    return id % TABLE_SIZE;
}


int hashPaper(int id) {

    return id % TABLE_SIZE;
}





//  create functions
DTB2Author* createP2Author(int id) {

}


DTB2Paper* createP2Paper(int id) {

}
