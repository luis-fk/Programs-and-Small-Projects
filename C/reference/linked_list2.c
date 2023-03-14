/* implementation of a linked list that insert the elements
   in the correct order in the list */
#include <stdio.h>
#include <stdlib.h>

/* struct that stores a value and pointer to the next
   item on the linked list */
typedef struct data {
    int val;
    struct data *next;
} data;

/* function declarations */
data *get_new_data (int val);
void print_data(data *val, int total);

int main (){
    data *head = NULL, *temp = NULL, *p = NULL;
    int total, current, i;

    /* queries user for amount of data to be inserted */
    printf("Number of data: ");
    scanf("%d", &total);

    /* scans for the data */
    for(i = 0; i < total; i++){
        printf("Data %d: ", i + 1);
        scanf("%d", &current);

        /* creates a node and stores value */
        temp = get_new_data(current);
        
        /* shift elements to the back of the linked list */
        if (head == NULL)
            head = temp;
        else{
            p = head;
            while (p->next != NULL)
                p = p->next;
            p->next = temp;
        }
    }

    /* prints the lisst */
    print_data(head, total);

    return 0;
}

/* creates a node */
data *get_new_data (int num){
    data *result = calloc(1, sizeof(data));
    result->val = num;
    return result;
}

/* prints the data */
void print_data(data *head, int total){
    data *temp = head;

    while (temp != NULL){
        printf("%d  ", temp->val);
        temp = temp->next;
    }
}
