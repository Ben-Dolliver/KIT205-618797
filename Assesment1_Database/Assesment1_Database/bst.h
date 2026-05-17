#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>



//  paper BST node
typedef struct PaperNode {

    int paperID;

    struct PaperNode* left;
    struct PaperNode* right;

} PaperNode;


//  author BST node
typedef struct AuthorNode {

    int authorID;

    struct AuthorNode* left;
    struct AuthorNode* right;

} AuthorNode;




//  Create functions
PaperNode* createPaperNode(int id);
AuthorNode* createAuthorNode(int id);


//  Insert functions
PaperNode* insertPaperBST(PaperNode* root, int id);
AuthorNode* insertAuthorBST(AuthorNode* root, int id);


// print functions
void printPaperBST(PaperNode* root);
void printAuthorBST(AuthorNode* root);


#endif