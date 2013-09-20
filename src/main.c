
#include <stdlib.h>
#include "main.h"
#include <errno.h>
#include <string.h>
#include <omp.h>

char read_buffer[100];
expand_array input_data;
int limit = 0;
int line_cnt = 0;

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
    int targetNode, i;
    int value = 0;
    bool nodeStat;
    data_parcel localBuffer;
    errno = 0;

#ifdef DEBUG   
    loop = 1;
#endif

    total_len = 0;
    init_workforce(argc, argv);
    expand_array_init(&input_data);

    if (isLeader()) {

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


        while ((limit == 0 || limit > line_cnt)
                && (fgets(read_buffer, 100, input_file) != NULL)) {
            value = atoi(read_buffer);
            targetNode = getnode_val(value);
            if (targetNode == 0) {
                expand_array_put(&input_data, value);
            } else {
                nodePush(targetNode, value);
            }

            line_cnt++;
        }
        end_work();
    } else {

        while (1) {
            nodeStat = nodeRecieve(0, &localBuffer);
            if (nodeStat) {
                for (i = 0; i < localBuffer.size; i++) {
                    expand_array_put(&input_data, localBuffer.data[i]);
                }
            } else {
                break;
            }
        }

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
    MPI_Barrier(MPI_COMM_WORLD);
    sort(input_data.data, buffer, input_data.largest_index);
    MPI_Barrier(MPI_COMM_WORLD);

    if (isLeader()) {
        write_file(output_file, input_data.data, input_data.largest_index);
        gather_work(output_file);
        fclose(input_file);
        fclose(output_file);
    } else {
        for (int i = 0; i < input_data.largest_index; i++) {
            nodePush(0, input_data.data[i]);
        }
        finish_node(0);
    }

    expand_array_free(&input_data);

    teardown_workforce();
    free(buffer);

    printf("Done!\n");
    return 0;
}
