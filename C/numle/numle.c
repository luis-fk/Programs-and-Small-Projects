/* this program works just like Wordle, but with number. Here a random number 
   from 0 to 99999 will be generated and the user will have 5 chances of
   guessing this number */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void split_digits (int senha, int *digitos, int size, int parameter);
int compare (int *number, int *try);
void print(int digit, int parameter);

/* - the frequency array keeps track of how many times a number appears on the number 
   to be guessed and the try from the user. This is necessary because in cases where the try
   from the user has a number appearing more times than the actual number, we don't compare it
   multiple times. For instance, if the number is 10001 and the try is 10000, we should only say
   that the first digit (1) is in the correct position and give no information about the extra 1
   on the last digit.

   - digits_number and digits_try store the digits of the number and the try from the user

   - checked is an arrays that keeps track is a number has already been checked or not so we
     dont repeat ourselves */
int frequency[10], digits_number[5], digits_try[5], checked[5];
int try, matches, printed = 0;

int main (int argc, char **argv){
    int number, size_number, size_try, check, i, j;

    /* generating the number and spliting its digits into an array */
    srand(time(0));
    number = rand() % 99999;

    /* check the size of the number generated */
    size_number = log10(number) + 1;

    for (i = 0; i < 5; i++){
        /* queries user for their guess */
        printf("Try number %d: ", i + 1);
        scanf("%d", &try);

        /* checks if the guesse is equal to the number generated */
        if (number == try){
            printf("You got it!\n");
            return 0;
        }

        /* reset arrays */
        for (j = 0; j < 10; j++)
            frequency[j] = 0;
        for (j = 0; j < 5; j++)
            checked[j] = 0;

        /* split the number and puts it in an array*/
        size_try = log10(try) + 1;
        split_digits(number, digits_number, size_number, 0);
        split_digits(try, digits_try, size_try, 1);

        /* function that compares the two numbers*/
        check = compare(digits_number, digits_try);
        if (matches == 0)
            printf("No matches for %d!", try);

        printf("\n");
    }

    return 0;
}

void split_digits (int number, int *digits, int size, int parameter){
    int i;

    for (i = size; i > 0; i--){
        digits[i - 1] = number % 10;
        frequency[number % 10]++;
        number /= 10; 
    }

    /* a parameter is passed to this function just to differentiate between
       the number and the try from the user. This for loop below is used in
       cases where the guess from the user or the number itself don't have
       5 digits. This is necessary so the program below does not confuse
       extra 0s at the end of number*/
    for(i = size; i < 5; i++){
        digits[i] = 99 + parameter;
    }
}

int compare (int *number, int *try){
    int i, j, check;
    matches = 0;

    for (i = 0; i < 5; i++){
        check = -1;
        for (j = 0; j < 5; j++){
            /* if the two numbers are the same, have the same index, the frequency matches and it
               hasn't been cheked yet, the number is in the correct position */
            if (try[i] == number[j] &&  i == j && frequency[try[i]] > 1 && checked[i] == 0){
                check = 1;
                break;
            }
            /* if the two numbers are the same, have different indexes, the frequency matches and
               it hasn't been checked yet, then the number from the try is in the incorrect positon.
               However, the function doesn't break here because it can still have a correct match
               from the if condition above*/
            if (try[i] == number[j] && i != j && frequency[try[i]] > 1 && checked[i] == 0)
                check = 0;
        }
        /* depending on which "if" condition in the function compare got
        triggered, we call the function to print a correct, incorrect 
        or no message*/    
        if (check == 1)
            print(i, 1);
        else if (check == 0)
            print(i, 0);
        else
            continue;

        frequency[try[i]] -= 2;
        checked[i] = 1;
        matches++; 
    }
    return check;
}

void print(int digit, int parameter){
    printed++;
    /* if parameter is 1, then the number in a certain position is in its correct position.*/
    if (parameter == 1){
        if (digit == 0)
            printf ("%dst digit in the correct position for %d!\n", digit + 1, try);
        else if (digit == 1)
            printf ("%dnd digit in the correct position for %d!\n", digit + 1, try);
        else if (digit == 2)
            printf ("%drd digit in the correct position for %d!\n", digit + 1, try);
        else
            printf ("%dth digit in the correct position for %d!\n", digit + 1, try);
        
        return;
    }
    else{
        /* if the paremeter is 0, then the number in a certain position is in its incorrect position*/
        if (digit == 0)
            printf ("%dst digit in the incorrect position for %d!\n", digit + 1, try);
        else if (digit == 1)
            printf ("%dnd digit in the incorrect position for %d!\n", digit + 1, try);
        else if (digit == 2)
            printf ("%drd digit in the incorrect position for %d!\n", digit + 1, try);
        else
            printf ("%dth digit in the incorrect position for %d!\n", digit + 1, try);

        return;
    }    
}