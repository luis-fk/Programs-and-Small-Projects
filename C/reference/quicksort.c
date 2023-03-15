/* implementation of quicksort that reads numbers from 
   a file whose name is inputted as a command line
   argument */
#include <stdio.h>
#include <stdlib.h>

/* functions declarations */
void print_list(int *array, int total);
void quicksort(int *array, int low, int high);
int partition(int *array, int low, int high);
void swap(int *a, int *b);

int main (int argc, char **argv){
    int i = 0, num, total = 0, *array;
    FILE *list = fopen(argv[1], "r");

    /* counting the amount of numbers in the data set */
    while (fscanf(list, "%d", &num) == 1)
        total++;

    /* allocating memory */
    array = calloc(total, sizeof(int));

    fclose(list);
    list = fopen(argv[1], "r");

    /* adding number onto an array */
    while (fscanf(list, "%d", &num) == 1){
        array[i] = num;
        i++;
    }

    /* prints unsorted list */
    printf("Unsorted list: \n");
    print_list(array, total);

    /* calls quicksort */
    quicksort(array, 0, total - 1);

    /* prints sorted list */
    printf("\nSorted list: \n");
    print_list(array, total);

    return 0;
}

/* print function */
void print_list(int *array, int total){
    int i;

    for (i = 0; i < total; i++)
        printf("%d ", array[i]);
}

/* function that creates the partitions for quicksort and
   works recursively */
void quicksort(int *array, int low, int high){
    if (low < high){
        int pivot = partition(array, low, high);

        quicksort(array, low, pivot - 1);

        quicksort(array, pivot + 1, high);
    }
}

/* compares the partions */
int partition(int *array, int low, int high){
    int pivot = array[high];
    int i = (low - 1);
    int j;

    for (j = low; j < high; j++){
        if (array[j] <= pivot){
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

/* swap values */
void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}
