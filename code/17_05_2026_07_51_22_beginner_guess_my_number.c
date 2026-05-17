#include <stdio.h>
#include <stdlib.h>

int main() {
    int low = 1;
    int high = 100; // assuming the number is between 1 and 100
    int guess;

    printf("Think of a number between 1 and 100.\n");
    printf("I will try to guess it.\n");

    while(1) {
        guess = (low + high)/2;
        printf("Is your number %d? (yes/no/less): ", guess);

        char response[10];
        fgets(response, sizeof(response), stdin);
        response[strcspn(response, "\n")] = 0; // remove newline character

        if(strcmp(response, "yes") == 0) {
            printf("I guessed it! The number was %d.\n", guess);
            break;
        }
        else if(strcmp(response, "less") == 0) {
            low = guess + 1;
        }
        else {
            high = guess - 1;
        }
    }

    return 0;
}