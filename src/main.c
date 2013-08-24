
#include <stdlib.h>
#include "main.h"
#include <errno.h>
#include <stdlib.h> 
#include <string.h>
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

void sort(int *buffer, int* list, int len) {
    int mid = len / 2;

    if (len <= 1) {
        return;
    }

    sort(list, buffer, mid);
    sort(list + mid, buffer + mid, len - mid);

    merge(list, mid, list + mid, len - mid, buffer);
}

void merge(int *left, int left_len, int* right, int right_len, int *buffer) {
    int left_i, right_i, i;

    left_i = 0;
    right_i = 0;
    i = 0;

    while (left_i < left_len && right_i < right_len) {
        if (left[left_i] < right[right_i]) {
            buffer[i++] = left[left_i++];
        } else {
            buffer[i++] = right[right_i++];
        }
    }

    /* 
     * Whichever list finished first, the other list must be copied back
     * too.
     */
    while (left_i < left_len) {
        buffer[i++] = left[left_i++];
    }

    while (right_i < right_len) {
        buffer[i++] = right[right_i++];
    }
#ifdef DEBUG
    printf("*******\n");
    printf("Loop: %i\n", loop++);
    printf("Input \n");
    print_list(global_input, total_len);
    printf("Buffer \n");
    print_list(global_buffer, total_len);
    printf("*******\n");
#endif
}

void print_list(int *input, int len) {
    printf("=========\n");
    for (int i = 0; i < len; i++) {
        printf("%i : %i \n", i, input[i]);
    }
    printf("=========\n");
}

void write_file(FILE *fp, int* input, int len) {
    for (int i = 0; i < len; i++) {
        fprintf(fp, "%i\n", input[i]);
    }
}