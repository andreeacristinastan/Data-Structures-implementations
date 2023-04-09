/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

b_node_t* lca(b_node_t* root, int a, int b) {
    if(root == NULL) {
        return NULL;
    }

    if(root == NULL || *(int *)root->data == b || *(int*)root->data == a) {
        return root;
    }

    b_node_t* left = lca(root->left, a, b);
    b_node_t* right = lca(root->right, a, b);

    if(left != NULL && right != NULL) {
        return root;
    }

    if(left == NULL && right ==NULL) {
        return NULL;
    }

    if(left == NULL && right != NULL) {
        return right;
    }

    if(right == NULL && left != NULL) {
        return left;
    }

    return NULL;
}

int main(void)
{
    /* TODO */

     b_tree_t *binary_tree;

    binary_tree = b_tree_create(sizeof(int));

    read_tree(binary_tree);

    int a, b;
    scanf("%d %d", &a, &b);

    printf("%d\n", *(int*)lca(binary_tree->root, a, b)->data);

    b_tree_free(binary_tree, free);
}
