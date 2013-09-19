#include "helper.h"

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}



/**
 * Helper function to print an array. Useful for debugging.
 * 
 * @param input the array to print.
 * @param len the length of the array.
 */
void print_list(int *input, int len) {
    printf("=========\n");
    for (int i = 0; i < len; i++) {
        printf("%i : %i \n", i, input[i]);
    }
    printf("=========\n");
}

/**
 * Writes an array to file.
 * 
 * @param fp a file pointer to the file.
 * @param input the array to be written.
 * @param len the length of that array in elements.
 */
void write_file(FILE *fp, int* input, int len) {
    for (int i = 0; i < len; i++) {
        fprintf(fp, "%i\n", input[i]);
    }
}