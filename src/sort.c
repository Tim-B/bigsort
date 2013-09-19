#include "sort.h"
#include <string.h>
#include <omp.h>

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
