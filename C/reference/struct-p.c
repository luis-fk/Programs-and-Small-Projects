/* implementation of a struct and an array of structs */
#include <stdio.h>
#include <stdlib.h>

/* struct person that can have 3 different people */
struct person {
    int age;
    int height;
    int weight;
    char *name;
} person[3];

int main ()
{
    struct person *p = person;
    int i;

    /* giving values to person 1 */
    person[1].age = 12;
    person[1].height = 149;
    person[1].weight = 78;
    person[1].name = "David";

    /* giving values to person 2 */
    person[2].age = 32;
    person[2].height = 189;
    person[2].weight = 98;
    person[2].name = "Jack";

    /* printing info for all people */
    for (i = 1; i < 3; i++)
    {
        printf("Age: %d\n", (p + i)->age);
        printf("Height: %d\n", (p + i)->height);
        printf("Weight: %d\n", (p + i)->weight);
        printf("Name: %s\n", (p + i)->name);
        printf("\n");
    }

    return 0;
}