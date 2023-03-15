/* this is a simple implementation of the collatz conjecture with
   recursion. The program reads a number from the user and gives
   back the number of steps it takes for that number to reach
   number 1 */
#include <stdio.h>
#include <stdlib.h>

int collatz_steps(unsigned long long int number);

int main (int argc, char **argv){
    unsigned long long int number = -1;
    int number_of_steps = 0;

    while (number != 0){
        /* asks users to type a number */
        printf("Type a number (type 0 to exit): ");
        scanf("%llu", &number);

        /* calls the function */
        number_of_steps = collatz_steps(number);

        printf("%d steps.\n\n", number_of_steps);
    }

    return 0;
}

int collatz_steps(unsigned long long int number){

    if (number == 1)
        return 0;
    else if (number % 2 == 0)
        return 1 + collatz_steps(number /= 2);
    else
        return 1 + collatz_steps((number * 3) + 1);
}
