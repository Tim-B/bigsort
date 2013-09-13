
#include <stdlib.h>
#include "main.h"
#include <errno.h>
#include <stdlib.h> 
#include <string.h>
#include <omp.h>
#include "expand_array.h"

char read_buffer[100];
expand_array input_data;
int total_len = 0;
int limit = 0;
int line_cnt = 0;

#ifdef DEBUG
int *global_buffer, *global_input;
int loop = 1;
#endif

/**
 * Mergesort based sorting algorithm designed for large datasets
 * 
 * References:
 * http://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Merge_sort#C
 * http://rosettacode.org/wiki/Sorting_algorithms/Merge_sort#C
 * https://gist.github.com/codeblocks/898596
 * 
 * @param argc arguments: inputfile outputfile [limit]
 * @param argv number of arguments (3 or 4)
 * @return 
 */
int main(int argc, char *argv[]) {
    int value = 0;
    errno = 0;

    if (argc < 3 || argc > 4) {
        printf("Usage is %s inputfile outputfile [limit]\n", argv[0]);
        return 1;
    }

    if (argc == 4) {
        limit = atoi(argv[3]);
        printf("Limit %i\n", limit);
    }

    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("File %s could not be opened for reading\n", argv[1]);
        perror("Message");
        return 2;
    }

    output_file = fopen(argv[2], "w+");
    if (output_file == NULL) {
        printf("File %s could not be opened for writing\n", argv[2]);
        perror("Message");
        return 3;
    }

    expand_array_init(&input_data);

    while ((limit == 0 || limit > line_cnt)
            && (fgets(read_buffer, 100, input_file) != NULL)) {
        value = atoi(read_buffer);
        expand_array_put(&input_data, value);
        line_cnt++;
    }

    int *buffer = malloc(sizeof (int) * input_data.largest_index);
    memcpy(buffer, input_data.data, sizeof (int) * input_data.largest_index);


#ifdef DEBUG
    total_len = input_data.largest_index;
    global_buffer = buffer;
    global_input = input_data.data;
    int nthreads;
    nthreads = omp_get_num_threads();
    printf("Number of threads %i\n", nthreads);
#endif

    // print_list(input_data, LEN);
    sort(input_data.data, buffer, input_data.largest_index);
    // print_list(input_data, LEN);

    free(buffer);

    write_file(output_file, input_data.data, input_data.largest_index);

    expand_array_free(&input_data);

    fclose(input_file);
    fclose(output_file);

    printf("Done!\n");
    return 0;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

/**
 * Perform recursive step on bot        h halfs of the dataset.
 * 
 * @param buffer 
 * @param list
 * @param len
 */
void sort(int *list, int* buffer, int len) {
    int i, j;

    for (i = 1; i < len; i *= 2) {
#pragma omp parallel for private(j)
        for (j = i; j < len; j += 2 * i) {
            merge(list, j - i, j, min(i + j, len), buffer);
        }
        memcpy(list, buffer, sizeof (int) * len);
    }

}

/**
 * Merge two arrays into a third array (in this case two are probably
 * the same physical array but treated as separate).
 * 
 * @param left The first array
 * @param left_len The length of the first array
 * @param right The second array
 * @param right_len The length of the second array
 * @param buffer The array to merged into
 */
void merge(int *list, int start, int middle, int end, int *buffer) {
    
#ifdef DEBUG
    int tid;
    printf("*******\n");
    tid = omp_get_thread_num();
    printf("Loop: %i thread %i of %i\n", loop++, tid, omp_get_num_threads());
#endif
    int left_i, right_i, i;

    left_i = start;
    right_i = middle;
    i = start;

    while (left_i < middle && right_i < end) {
        if (list[left_i] < list[right_i]) {
            buffer[i++] = list[left_i++];
        } else {
            buffer[i++] = list[right_i++];
        }
    }

    /* 
     * Whichever list finished first, the other list must be copied back
     * too.
     */
    while (left_i < middle) {
        buffer[i++] = list[left_i++];
    }

    while (right_i < end) {
        buffer[i++] = list[right_i++];
    }



#ifdef DEBUG
    printf("Input \n");
    print_list(global_input, total_len);
    printf("Buffer \n");
    print_list(global_buffer, total_len);
    printf("*******\n");
    printf("Start %i, middle %i, end %i, len %i \n", start, middle, end, (end - start));
#endif

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