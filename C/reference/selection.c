/* implementation of selection sort that reads numbers
   from a file whose name is given as a command line
   argument */
#include <stdio.h>
#include <stdlib.h>

/* function declarations */
void print_list(int *array, int total);
void selection(int *array, int total);

int main (int argc, char **argv){
    int i = 0, total = 0, num, *array;
    FILE *list = fopen(argv[1], "r");

    /* counts the number of data to be sorted */
    while (fscanf(list, "%d", &num) == 1)
        total++;
    
    fclose(list);

    /* allocates memory */
    array = calloc(total, sizeof(int));
    
    list = fopen(argv[1], "r");

    /* adds numbers into the array */
    while (fscanf(list, "%d", &num) == 1){
        array[i] = num;
        i++;
    }

    /* prints unsorted list */
    printf("Unsorted list: \n");
    print_list(array, total);

    /* sort the list */
    selection(array, total);

    /* prints sorted list */
    printf("\nSorted list: \n");
    print_list(array, total);

    return 0;
}

/* prints list */
void print_list(int *array, int total){
    int i;

    for (i = 0; i < total; i++)
        printf("%d ", array[i]);
}

/* implementation of selection sort */
void selection(int *array, int total){
    int i, j, min, temp;

    for (i = 0; i < total - 1; i++){
        min = i;
        for (j = i + 1; j < total; j++)
            if (array[j] < array[min])
                min = j;

        
        if (min != i){
            temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }
}