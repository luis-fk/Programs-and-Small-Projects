/* implementation of a simple linked list */

#include <stdio.h>
#include <stdlib.h>

/* struct that stores a valaue and implements
   the linked list */
typedef struct node {
    int value;
    struct node *next;
} node_t;

/* declaring functions */
void printlist (node_t *head);
node_t *create_new_node (int value);

int main (){
    node_t *head = NULL, *tmp;
    int total, current, i;

    /* queries user for amount of data to be stored */
    printf("Number of data: ");
    scanf("%d", &total);

    for (i = 0; i < total; i++){
        /* queries user for the data */
        printf("Data %d: ", i + 1);
        scanf("%d", &current);

        /* creates new node and insert value into the list */
        tmp = create_new_node(current);
        tmp->next = head;
        head = tmp;
    }

    /* print list */
    printlist (head);

    return 0;
}

/* function that prints the values in the linked list */
void printlist (node_t *head){
    node_t *temporary = head;

    while (temporary != NULL){
        printf("%d - ", temporary->value);
        temporary = temporary->next;
    }
    printf("\n");
}

/* creates a new node */
node_t *create_new_node (int value){
    node_t *result = calloc(1, sizeof(node_t));
    result->value = value;
    return result;
}
