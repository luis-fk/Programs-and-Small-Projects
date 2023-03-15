/* implementation of a binary tree that also uses inorder
   traversal to count the number of nodes. The program reads
   a list of values from a file, whose name is giving as a
   command line argument*/
#include <stdio.h>
#include <stdlib.h>

/* declaration of the struct that is the base of our
   binary tree */
typedef struct tree{
    int value;
    struct tree *right;
    struct tree *left;
} tree;

/* function declarations */
tree *create_node(int num);
tree *insert_value(tree *root, int num);
int count(tree *root, int *num);

int main (int argc, char **argv){
    int num;
    tree *root = NULL;
    FILE *file = fopen(argv[1], "r");

    /* insert values into the tree */
    while (fscanf(file, "%d", &num) == 1)
        root = insert_value(root, num);

    num = 0;
    /* count the number of nodes */
    num = count(root, &num);
    
    printf("The number of nodes is: %d\n", num);

    return 0;
}

/* creates node */
tree *create_node(int num){
    tree *temp;
    temp = calloc(1, sizeof(tree));
    temp->value = num;

    return temp;
}

/* insert values into the tree */
tree *insert_value(tree *root, int num){
    if (root == NULL)
        root = create_node(num);
    else if (num <= root->value)
        root->left = insert_value(root->left, num);
    else
        root->right = insert_value(root->right, num);

    return root;
}

/* count the number of nodes using inorder traversal */
int count(tree *root, int *num){
    if (root == NULL)
        return *num;
    
    count(root->left, num);
    *num += 1;
    count(root->right, num);

    return *num;
}
