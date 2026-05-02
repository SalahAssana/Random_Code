#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define URL "http://example.com"
#define MAX_LENGTH 1000

int main() {
    FILE *file = fopen("output.txt", "w");
    
    if(file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    char buffer[MAX_LENGTH];
    
    // Send request to the URL
    FILE *fp = popen("curl -s %s", "r");
    if (fp == NULL) {
        printf("Error opening pipe!\n");
        return 1;
    }
    
    while(fgets(buffer, MAX_LENGTH, fp) != NULL) {
        fprintf(file, "%s", buffer);
    }
    
    pclose(fp);
    fclose(file);
    
    return 0;
}