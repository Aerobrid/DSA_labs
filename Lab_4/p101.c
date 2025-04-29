#include <stdio.h>              // input/output like printf()
#include <stdlib.h>             // for using malloc() and free()
#include <stdbool.h>            // for the "true" or "false" we will return 

// Definition for a binary tree node from leetcode problem
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Creates a new tree node through heap dynamic memory allocation
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// helper function that recursively checks if tree is mirrored or not
bool isMirror(struct TreeNode* t1, struct TreeNode* t2) {
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    return (t1->val == t2->val) && isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

// jumpstarts the process by checking first case, if not true, pass the job on to isMirror()
bool isSymmetric(struct TreeNode* root) {
    if (root == NULL) return true;
    return isMirror(root->left, root->right);
}

// Free the memory allocated for each tree node recursively given root
void freeTree(struct TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    // Example tree (not a BST, just a BT)
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->right = newNode(4);
    root->right->left = newNode(4);
    root->right->right = newNode(3);

    // Test the function using an if statement since it returns a boolean
    if (isSymmetric(root)) {
        printf("The tree is symmetric.\n");
    } else {
        printf("The tree is not symmetric.\n");
    }

    // Free the memory allocated for tree
    freeTree(root);

    return 0;
}
