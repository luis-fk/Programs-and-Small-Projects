/* recursive function that counts how many digits in a number */
#include <stdio.h>

int num_dig (int num);

int main (){
    int num = -1;

    while (num != 0){
        printf("Type the number (0 to exit): ");
        scanf("%d", &num);

        num = num_dig(num);

        printf("Digits: %d\n", num);
    }
    
    return 0;
}

/* recursive function */
int num_dig (int num){

    if (num < 10)
        return 1;
    else
        return 1 + num_dig((num - (num % 10)) / 10);
}