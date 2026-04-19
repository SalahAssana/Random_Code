#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000
#define MAX_RULES 256

typedef struct {
    char axiom[MAX_LENGTH];
    char rules[MAX_RULES][MAX_LENGTH];
} LSystem;

void generateFractal(LSystem* lsystem, int iterations) {
    char currentString[MAX_LENGTH];
    strcpy(currentString, lsystem->axiom);

    for (int i = 0; i < iterations; i++) {
        char newString[MAX_LENGTH];
        int newSize = 0;
        for (int j = 0; j < strlen(currentString); j++) {
            if (currentString[j] == 'F') {
                for (int k = 0; k < strlen(lsystem->rules[0]); k++) {
                    newString[newSize++] = lsystem->rules[0][k];
                }
            } else {
                newString[newSize++] = currentString[j];
            }
        }
        strcpy(currentString, newString);
    }

    printf("%s\n", currentString);
}

int main() {
    LSystem lsystem;
    strcpy(lsystem.axiom, "FX");
    strcpy(lsystem.rules[0], "+X--F+");
    strcpy(lsystem.rules[1], "--FX+");
    generateFractal(&lsystem, 5);

    return 0;
}