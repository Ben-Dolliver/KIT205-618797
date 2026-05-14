#include <stdio.h>
#include <stdlib.h>

#include "bst.h"




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



