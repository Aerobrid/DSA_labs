#include <stdio.h>      // for things like input/output, NULL, etc.
#include <stdlib.h>     // for things like malloc(), realloc(), etc.

// from leetcode problem
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void preorderHelper(struct TreeNode* root, int* result, int* index) {
    // if node has nothing in it, return back, we have reached farthest node
    if (root == NULL) {
        return;
    }
    
    // visit node and add to result array (preorder: root -> left -> right)
    // remember to dereference the index parameter (was returnSize argument) and increment it for next node value
    result[*index] = root->val;
    (*index)++;
    
    // traverse the left subtree
    preorderHelper(root->left, result, index);
    
    // traverse the right subtree
    preorderHelper(root->right, result, index);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    // result array
    // set size large enough to accommodate the traversal of many trees, an array of 100 integers will do
    int* result = (int*)malloc(100 * sizeof(int));
    
    // array starts with index 0 and the size 0 (reset to 0 since it might've not been 0 in first place)
    *returnSize = 0;
    
    // perform the preorder traversal
    preorderHelper(root, result, returnSize);
    
    // return the result array
    return result;
}

void inorderHelper(struct TreeNode* root, int* result, int* index) {
    // if node has nothing in it, return back, we have reached farthest node
    if (root == NULL) {
        return;
    }

    // traverse the left subtree
    inorderHelper(root->left, result, index);

    // visit node and add to result array (inorder: left -> root -> right)
    // remember to dereference the index parameter (was returnSize argument) and increment it for next node value
    result[*index] = root->val;
    (*index)++;
    
    // traverse the right subtree
    inorderHelper(root->right, result, index);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    // result array
    // set size large enough to accommodate the traversal of many trees, an array of 100 integers will do
    int* result = (int*)malloc(100 * sizeof(int));
    
    // array starts with index 0 and size 0 (reset to 0 since it might've not been 0 in first place)
    *returnSize = 0;
    
    // perform inorder traversal
    inorderHelper(root, result, returnSize);
    
    // return result array
    return result;
}

// creates new node (will be initialized in main)
struct TreeNode* Node(int value){
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// recursively frees tree, feed it the root
void FreeNode(struct TreeNode* root){
    // if pointer pointing to node is NULL begin recursive ascent
    if(root == NULL){
        return;
    }
    // for left-subtree
    FreeNode(root->left);
    // for right-subtree
    FreeNode(root->right);
    
    // free node (last action to do)
    free(root);
}

// create tree in main, perform traversals, then free it
int main() {
    struct TreeNode* root = Node(8);
    root->left = Node(3);
    root->right = Node(10);
    root->left->left = Node(1);
    root->left->right = Node(6);

    // initially uninitialized, then increased/reset by reference in traversal functions
    int returnSize;

    // Use preorderTraversal(), which creates array, calls upon its respective helper which returns traversed array, and print it out using loop
    int* preorderResult = preorderTraversal(root, &returnSize);
    printf("Preorder Traversal: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", preorderResult[i]);
    }
    printf("\n");
    
    // need to free the result array
    free(preorderResult); 

    // Use inorderTraversal(), which creates array, calls upon its respective helper which returns traversed array, and print it out using loop
    int* inorderResult = inorderTraversal(root, &returnSize);
    printf("Inorder Traversal: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", inorderResult[i]);
    }
    printf("\n");
    
    // need to free the result array
    free(inorderResult);

    // Also free the tree at end
    FreeNode(root);

    return 0;
}