/* this program reads a list of names from a file, hashes the name, and
   returns an index from 0 to 9, if the index is already taken, a linked
   list is used to store names with the same index */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hash_function(char *name);

/* declaration of the struct with the attribute name and
   the struct person for the linked list */
typedef struct person{
    char name[20];
    struct person *next;
} person;

int main(int argc, char **argv){
    char current_name[20];
    int hash_value, num = 0;
    person **list, *node;
    FILE *text = fopen(argv[1], "r");

    /* reads and keeps track of the number of names in the list */
    while (fscanf(text, "%20s", current_name) == 1)
        num++;

    fclose(text);
    /* allocate memory */
    list = calloc(num, sizeof(person));

    text = fopen(argv[1], "r");

    while (fscanf(text, "%20s", current_name) == 1){
        /* call hash function and receive the index */
        hash_value = hash_function(current_name);

        /* create node and copy name into the node */
        node = calloc(1, sizeof(person));
        strcpy(node->name, current_name);

        /* if index is NULL, store node at the beginning of linked list */
        if (list[hash_value] == NULL){
            list[hash_value] = node;
            continue;
        }

        /* if index is not NULL, store the value at the next node in the linked list */
        node->next = list[hash_value];
        list[hash_value] = node;   
    }

    /* searches if a name exists in the linked list */
    while (current_name[0] != '0'){
        /* asks for the name */
        printf("Type the name you want to look for (type 0 to exit): ");
        scanf("%s", current_name);
        /* call hash function */
        hash_value = hash_function(current_name);
        
        /* searches the index of the array for the name */
        node = list[hash_value];
        while (node != NULL){
            if (strcmp(current_name, node->name) == 0)
                break;
            else
                node = node->next;
        }

        if (node == NULL){
            printf("Name not found!\n\n");
            continue;
        }

        printf("%s was found!\n\n", node->name);
    }
    
    return 0;
}

/* simple hash function that takes the lenght of a name, adds the ASCII
   values of its characters and takes the modulo 10 of the number */
int hash_function(char *name){
    int number = 0, length, i;
    length = strlen(name);

    for (i = 0; i < length; i++)
        number += name[i];

    number = number % 10;

    return number;
}

    