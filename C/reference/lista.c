/* this program takes a list of numbers, orders the list
   using bubble sort, adds these numbers into a linked list
   and removes reppeated values from said list*/
#include <stdio.h>
#include <stdlib.h>

/* struct that stores a value and implements the linked list */
typedef struct list {
    int num;
    struct list *next;
} list;

/* declaring function */
list *new_node(int num);
void *organize(list *head);
void *print(list *head);

int main (){
    int total, i, j, num, *array;
    list *head = NULL, *temp = NULL;

    /* queries user for amount of data to be processed */
    printf("Enter de amount of data: ");
    scanf("%d", &total);

    /* allocates memory */
    array = calloc(total, sizeof(int));

    /* stores numbers in an array */
    for (i = 0; i < total; i++){
        printf("Type the number %d: ", i + 1);
        scanf("%d", &num);
        array[i] = num;
    }

    /* sort numbers */
    for (i = 0; i < total - 1; i++)
        for (j = 0; j < total - i - 1; j++)
            if (array[j] > array[j + 1]){
                num = array[j];
                array[j] = array[j + 1];
                array[j + 1] = num;
            }

    /* insert numbers into a linked list */
    for (i = 0; i < total; i++){
        temp = new_node(array[i]);
        temp->next = head;
        head = temp;
    }

    /* calls functions to remove repetead numbers and to print the values */
    organize(head);
    print(head);

    return 0;
}

/* creates new node */
list *new_node (int num){
    list *node = calloc(1, sizeof(list));
    node->num = num;
    return node;
}

/* removes repeated values */
void *organize(list *head){
    list *temp = head, *temp2 = NULL;
    while (temp->next != NULL){
        if (temp->num == temp->next->num){
            temp2 = temp;

            while (temp->num == temp->next->num ){
                temp = temp->next;

                if (temp->next == NULL)
                    break;
            }

        temp2->next = temp->next;
        }

        temp = temp->next;
    }
}

/* prints list */
void *print(list *head){
    list *temp = head;

    while (temp != NULL){
        printf("%d ", temp->num);
        temp = temp->next;
    }
}
