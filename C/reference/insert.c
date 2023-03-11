/* simple implementation of insertion sort which reads numbers
   from a text file using command line arguments for its name*/
#include <stdio.h>
#include <stdlib.h>

/* declaring functions */
void print_list(int *array, int total);
void insert(int *array, int total);

int main (int argc, char **argv){
    int i = 0, total = 0, num, *array;
    FILE *list = fopen(argv[1], "r");

    /* counts the total amount of numbers */
    while (fscanf(list, "%d", &num) == 1)
        total++;
    
    fclose(list);
    /* allocates memory */
    array = calloc(total, sizeof(int));

    /* insert numbers into the array */
    list = fopen(argv[1], "r");
    while (fscanf(list, "%d", &num) == 1){
        array[i] = num;
        i++;
    }

    /* prints unsorted list */
    printf("Unsorted list: \n");
    print_list(array, total);

    /* calling the function to sort numbers */
    insert(array, total);

    /* prints sorted list */
    printf("\nSorted list: \n");
    print_list(array, total);

    return 0;
}

/* simple function to print the list */
void print_list(int *array, int total){
    int i;

    for (i = 0; i < total; i++)
        printf("%d ", array[i]);
}

/* implementation of insertion sort */
void insert(int *array, int total){
    int i, j, temp;

    for (i = 1; i < total; i ++){
        temp = array[i];
        j = i - 1;

        while (temp < array[j] && j >= 0){
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}