/* program implementation of merge sort where it
   reads a list of numbers from a file, whose name
   is inputed as a command line argument*/
#include <stdio.h>
#include <stdlib.h>

/* function declarations */
void print_list(int *array, int total);
void merge(int *array, int r, int m, int l);
void merge_sort(int *array, int r, int l);

int main (int argc, char **argv){
    int num, i = 0, total = 0;
    int *array;
    FILE *list = fopen(argv[1], "r");

    /* reads file to check the amount of data */
    while ((fscanf(list, "%d", &num)) == 1)
        total++;

    /* allocates memory */
    array = calloc(total, sizeof(int));

    fclose(list);
    list = fopen(argv[1], "r");

    /* stores numbers in an array */
    while ((fscanf(list, "%d", &num)) == 1){
        array[i] = num;
        i++;
    }

    /* prints unsorted list */
    printf("The given list is: \n");
    print_list(array, total);

    /* calls merge sort */
    merge_sort(array, 0, total - 1);

    /* prints sorted list */
    printf("\nThe sorted list is: \n");
    print_list(array, total);

    return 0;
}

/* prints list */
void print_list(int *array, int total){
    int i;

    for (i = 0; i < total; i++)
        printf("%d\n", array[i]);
}

void merge_sort(int *array, int l, int r){
    if (l < r){
        int m = (l + r) / 2;

        merge_sort(array, l, m);
        merge_sort(array, m + 1, r);

        merge(array, l, m, r);
    }
}

void merge(int *array, int l, int m, int r){
    int i, j = 0, k = l;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *left, *right;

    right = calloc(n2, sizeof(int));
    left = calloc(n1, sizeof(int));

    for (i = 0; i < n1; i++)
        left[i] = array[l + i];
    for (i = 0; i < n2; i++)
        right[i] = array[m + 1 + i];

    i = 0;
    while (i < n1 && j < n2){
        if (left[i] <= right[j]){
            array[k] = left[i];
            i++; 
        }
        else{
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < n2){
        array[k] = right[j];
        j++;
        k++;
    }
}