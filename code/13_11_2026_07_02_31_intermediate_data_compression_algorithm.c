#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 4096
#define BUFFER_SIZE 1024

typedef struct {
    int code;
    char *literal;
} DictEntry;

DictEntry dict[MAX_DICT_SIZE];
int dict_size = 0;
int max_code = 0;

void add_to_dict(int code, char *literal) {
    if (dict_size < MAX_DICT_SIZE) {
        dict[dict_size].code = code;
        dict[dict_size].literal = malloc(strlen(literal) + 1);
        strcpy(dict[dict_size].literal, literal);
        dict_size++;
    }
}

int find_in_dict(char *buffer, int buffer_len) {
    for (int i = 0; i < dict_size; i++) {
        if (!strcmp(dict[i].literal, buffer)) {
            return dict[i].code;
        }
    }
    return -1;
}

void compress(char *input, char *output) {
    FILE *in_file = fopen(input, "r");
    FILE *out_file = fopen(output, "w");

    int buffer_len = 0;
    char buffer[BUFFER_SIZE];

    while (fread(buffer + buffer_len, 1, BUFFER_SIZE - buffer_len, in_file)) {
        buffer_len += fread(buffer + buffer_len, 1, BUFFER_SIZE - buffer_len, in_file);

        for (int i = 0; i < buffer_len; i++) {
            int code = find_in_dict(buffer + i, 1);
            if (code == -1) {
                code = max_code++;
                add_to_dict(code, buffer + i);
                fwrite(&code, sizeof(int), 1, out_file);
            } else {
                fwrite(&code, sizeof(int), 1, out_file);
            }
        }
    }

    fclose(in_file);
    fclose(out_file);
}

void decompress(char *input, char *output) {
    FILE *in_file = fopen(input, "r");
    FILE *out_file = fopen(output, "w");

    int code;
    while (fread(&code, sizeof(int), 1, in_file)) {
        if (code > max_code) {
            code -= 256; // reset to previous dictionary entry
            add_to_dict(max_code++, buffer);
        }

        char *literal = dict[code].literal;
        fwrite(literal, strlen(literal), 1, out_file);

        free(literal);
    }

    fclose(in_file);
    fclose(out_file);
}

int main() {
    compress("input.txt", "output.lzw");
    decompress("output.lzw", "output.txt");

    return 0;
}