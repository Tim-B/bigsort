#include "worker.h"
#include <stdio.h>

bool isLeader() {
    return rank == 0;
}

void init_workforce(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    init_distribute(size);

    printf("Hello from %i of %i\n", rank, size);
}

void teardown_workforce() {
    MPI_Finalize();
}

void worker_push(int worker, int value) {
    
}

void gather_work(FILE *fp) {
    MPI_Status status;
    int mpiBuffer;
    for(int i = 1; i < size; i++) {
        while(1) {
            MPI_Recv(&mpiBuffer, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if(status.MPI_TAG == END_TAG) {
                break;
            }
            fprintf(fp, "%i\n", mpiBuffer);
        }
    }
}

void end_work() {
    int nothing = 0;
    for(int i = 1; i < size; i++) {
        MPI_Send(&nothing, 0, MPI_INT, i, END_TAG, MPI_COMM_WORLD);
    }
}