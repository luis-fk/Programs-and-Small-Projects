/* this program reads a list of numbers from a file with command
line arguments and put them into a binary tree. You are also
able to search for a specific number in the tree and check
if it exists in the tree */
#include <stdio.h>
#include <stdlib.h>

/* create the binary tree that takes integers */
typedef struct tree {
    int value;
    struct tree *left;
    struct tree *right;
} tree;

/* declaring functions */
tree *createnode(int value);
tree *insert (tree *root, int data);
int search (tree *root, int data);

int main(int argc, char **argv) {
    int num;
    FILE *file = fopen(argv[1], "r"); /* open file */
    tree *root = NULL;

    /* scans the file and adds each number to the tree */
    while (fscanf(file, "%d", &num) == 1) 
        root = insert(root, num);

    /* search for number */
    printf("Number to search: ");
    scanf("%d", &num);

    if (search(root, num) == 1)
        printf("Found\n");
    else
        printf("Not found\n");

    return 0;
}

/* function that creates a node */
tree *createnode(int value) {
    /* calling calloc sinze it already initializes left and right 
       node with NULL*/
    tree *newnode = calloc(1, sizeof(tree)); 
    newnode->value = value;

    return newnode;
}

/* insert value into the tree recursively */
tree *insert(tree *root, int data) {
    if (root == NULL)
        root = createnode(data);
    else if (data <= root->value)
        root->left = insert(root->left, data);
    else
        root->right = insert (root->right, data);

    return root;
}

/* search for a number in the tree recursively */
int search (tree *root, int data) {
    if (root == NULL)
        return 0;
    else if (root->value == data)
        return 1;
    else if (data <= root->value)
        return search (root->left, data);
    else return search (root->right, data);
}
