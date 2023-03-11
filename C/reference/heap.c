/* simple implementation of heap sort */
#include <stdio.h>
#include <stdlib.h>

void heapsort(int *array, int n);
void swap(int *a, int *b);
void heapify(int *array, int total, int i);
void print_list(int *array, int total);

int main (int argc, char **argv){
    int i = 0, total = 0, num, *array;
    FILE *list = fopen(argv[1], "r");

    /* counts the total amount of numbers to be sorted */
    while (fscanf(list, "%d", &num) == 1)
        total++;

    /* allocates memoery */
    array = calloc(total, sizeof(int));

    fclose(list);
    list = fopen(argv[1], "r");

    /* add the numbers onto the array */
    while (fscanf(list, "%d", &num) == 1){
        array[i] = num;
        i++;
    }

    /* prints list */
    printf("The unsorted list is: \n");
    print_list(array, total);

    /* calls the function to be sorted */
    heapsort(array, total);

    /* prints sorted list */
    printf("\nThe sorted list is: \n");
    print_list(array, total);

    return 0;
}

/* basic workings of the heapify function */
void heapsort(int *array, int total){
    int i;

    for (i = (total / 2) - 1; i >= 0; i--)
        heapify(array, total, i);

    for (i = total - 1; i >= 0; i--){
        swap(&array[0], &array[i]);

        heapify(array, i, 0);
    }
}

/* simply swap numbers using pointers */
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int *array, int total, int i){
    /* heap sort is explained as a binary tree normally, but an
       array can be treated as a binary tree using the formula
       (2 * i) + 1 and (2 * i) + 2 for left and right elements */
    int largest = i, left = (2 * i) + 1, right = (2 * i) + 2;

    if (left < total && array[left] > array[largest])
        largest = left;

    if (right < total && array[right] > array[largest])
        largest = right;

    if (largest != i){
        swap(&array[i], &array[largest]);
        heapify(array, total, largest);
    }
}

/* prints list */
void print_list(int *array, int total){
    int i;

    for (i = 0; i < total; i++)
        printf("%d ", array[i]);
}
