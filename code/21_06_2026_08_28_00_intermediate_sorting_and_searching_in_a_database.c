#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define a structure to represent a record in the CSV file
typedef struct {
    char name[50];
    int age;
    float height;
} Record;

// Function to read data from a CSV file and store it in an array of records
Record* readCSVFile(const char* filename, int* numRecords) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    *numRecords = 0;
    Record* records = NULL;

    // Read the CSV file line by line
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        // Split the line into individual fields using commas as delimiters
        char* field = strtok(line, ",");
        int i = 0;
        Record record;
        strcpy(record.name, field);
        while (field != NULL) {
            if (i == 0) {
                record.age = atoi(field);
            } else if (i == 1) {
                record.height = atof(field);
            }
            field = strtok(NULL, ",");
            i++;
        }

        // Allocate memory for the new record
        Record* newRecord = (Record*)malloc(sizeof(Record));
        *newRecord = record;

        // Add the new record to the array of records
        if (*numRecords == 0) {
            records = (Record*)malloc(sizeof(Record));
            records[0] = *newRecord;
            *numRecords = 1;
        } else {
            Record* temp = (Record*)malloc((size_t)*numRecords * sizeof(Record));
            memcpy(temp, records, (size_t)*numRecords * sizeof(Record));
            free(records);
            records = temp;
            records[(*numRecords)++] = *newRecord;
        }
    }

    fclose(file);

    return records;
}

// Function to sort the array of records using bubble sort
void sortRecords(Record* records, int numRecords) {
    for (int i = 0; i < numRecords - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < numRecords - i - 1; j++) {
            if (records[j].age > records[j + 1].age) {
                Record temp = records[j];
                records[j] = records[j + 1];
                records[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Function to search for a record with a given name using linear search
Record* findRecordByName(Record* records, int numRecords, const char* name) {
    for (int i = 0; i < numRecords; i++) {
        if (strcmp(records[i].name, name) == 0)
            return &records[i];
    }
    return NULL;
}

// Function to print the contents of an array of records
void printRecords(Record* records, int numRecords) {
    for (int i = 0; i < numRecords; i++) {
        printf("Name: %s, Age: %d, Height: %.2f\n", records[i].name, records[i].age, records[i].height);
    }
}

int main() {
    int numRecords;
    Record* records = readCSVFile("data.csv", &numRecords);

    if (records == NULL) {
        return 1;
    }

    sortRecords(records, numRecords);

    char targetName[] = "John";
    Record* targetRecord = findRecordByName(records, numRecords, targetName);
    if (targetRecord != NULL)
        printf("Found record: Name: %s, Age: %d, Height: %.2f\n", targetRecord->name, targetRecord->age, targetRecord->height);

    printRecords(records, numRecords);

    for (int i = 0; i < numRecords; i++)
        free(&records[i]);

    free(records);
    return 0;
}