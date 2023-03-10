/* program for sorting number with bubble sort, the program reads a file
   whose name is inputted from the command line argument */
#include <stdio.h>
#include <stdlib.h>

/* declaring functions */
void print_list(int *list, int total);
void bubble_sort(int *list, int total);

int main (int argc, char **argv){
    int i = 0, total = 0, num, *list;
    FILE *file = fopen(argv[1], "r");

    /* checking size of file */
    while (fscanf(file, "%d", &num) == 1)
        total++;

    /* allocating memory */
    list = calloc(total, sizeof(int));
    fclose(file);

    /* adding numbers to arrys to be sorted */
    file = fopen(argv[1], "r");
    while (fscanf(file, "%d", &num) == 1){
        list[i] = num;
        i++;
    }

    printf("Unsorted list: \n");
    print_list(list, total);

    /* sort list */
    bubble_sort(list, total);

    printf("\nSorted list: \n");
    print_list(list, total);

    return 0;
}

/* function that prints the list */
void print_list(int *list, int total){
    int i;

    for (i = 0; i < total; i++)
        printf("%d ", list[i]);
}

/* implementation of bubble sort */
void bubble_sort(int *list, int total){
    int i, j, temp;

    for (i = 0; i < total - 1; i++)
        for (j = 0; j < total - i - 1; j++)
            if (list[j] > list[j + 1]){
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
}