#include <stdio.h>
#include <stdlib.h>


#include "bst.h"


void testBST() {

    printf("\n\n    ------[BST testing]------\n");


    //  create empty BSTs
    PaperNode* paperRoot = NULL;
    AuthorNode* authorRoot = NULL;


    //  insert papers

    printf("\n[adding papers]\n");

    paperRoot = insertPaperBST(paperRoot, 2001);
    paperRoot = insertPaperBST(paperRoot, 2005);
    paperRoot = insertPaperBST(paperRoot, 2003);


    //  insert authors

    printf("\n[adding authors]\n");

    authorRoot = insertAuthorBST(authorRoot, 101);
    authorRoot = insertAuthorBST(authorRoot, 105);
    authorRoot = insertAuthorBST(authorRoot, 103);


    //  print BSTs

    printf("\n-----[printing results]-----\n");

    printf("\nPaper BST\n");
    printPaperBST(paperRoot);

    printf("\nAuthor BST\n");
    printAuthorBST(authorRoot);

    printf("\n  ------[BST testing complete]------\n");

}



PaperNode* createPaperNode(int id) {

    PaperNode* node = malloc(sizeof(PaperNode));

    node->paperID = id;
    node->left = NULL;
    node->right = NULL;

    return node;
}


AuthorNode* createAuthorNode(int id) {

    AuthorNode* node = malloc(sizeof(AuthorNode));

    node->authorID = id;
    node->left = NULL;
    node->right = NULL;

    return node;

}

PaperNode* insertPaperBST(PaperNode* root, int id) {

    if (root == NULL)
        return createPaperNode(id);

    if (id < root->paperID)
        root->left = insertPaperBST(root->left, id);

    else if (id > root->paperID)
        root->right = insertPaperBST(root->right, id);

    return root;
}


AuthorNode* insertAuthorBST(AuthorNode* root, int id) {

    if (root == NULL)
        return createAuthorNode(id);

    if (id < root->authorID)
        root->left = insertAuthorBST(root->left, id);

    else if (id > root->authorID)
        root->right = insertAuthorBST(root->right, id);

    return root;
}

//  print papers of author using inorder traversal 
void printPaperBST(PaperNode* root) {

    // base case
    if (root == NULL) {
        return;
    }

    // print left subtree
    printPaperBST(root->left);

    // print current node
    printf("Paper ID: %d\n", root->paperID);

    // print right subtree
    printPaperBST(root->right);
}


//  print authors of paper using inorder traversal 
void printAuthorBST(AuthorNode* root) {

    // base case
    if (root == NULL) {
        return;
    }

    // print left subtree
    printAuthorBST(root->left);

    // print current node
    printf("Author ID: %d\n", root->authorID);

    // print right subtree
    printAuthorBST(root->right);
}

