#include "worker.h"
#include <stdio.h>
#include <stdlib.h>

bool isLeader() {
    return rank == 0;
}

int getWorkforceSize() {
    return size;
}

int getMyRank() {
    return rank;
}

void init_workforce(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int count[2] = {PARCEL_SIZE, 1};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};

    MPI_Aint offsets[2];

    offsets[0] = offsetof(data_parcel, data);
    offsets[1] = offsetof(data_parcel, size);


    MPI_Type_create_struct(2, count, offsets, types, &mpi_parcel);
    MPI_Type_commit(&mpi_parcel);

    init_distribute(size);

    data_buffers = malloc(size * sizeof (data_parcel));

    for (int i = 0; i < size; i++) {
        data_buffers[i].size = 0;
    }

    printf("Hello from %i of %i\n", rank, size);
}

void teardown_workforce() {
    free(data_buffers);
    MPI_Type_free(&mpi_parcel);
    MPI_Finalize();
}

void gather_work(FILE *fp) {
    bool nodeStat;
    data_parcel localBuffer;
    int i, j;
    for (i = 1; i < size; i++) {
        while (1) {
            nodeStat = nodeRecieve(i, &localBuffer);
            if (nodeStat) {
                for (j = 0; j < localBuffer.size; j++) {
                    fprintf(fp, "%i\n", localBuffer.data[j]);
                }
            } else {
                break;
            }
        }
    }
}

void end_work() {
    for (int i = 1; i < size; i++) {
        finish_node(i);
    }
}

void finish_node(int node) {
    int nothing = 0;
    nodeSendParcel(node);
    MPI_Send(&nothing, 0, MPI_INT, node, END_TAG, MPI_COMM_WORLD);
}

void nodePush(int node, int value) {
    data_buffers[node].data[data_buffers[node].size] = value;
    data_buffers[node].size++;
    if (data_buffers[node].size == PARCEL_SIZE) {
        nodeSendParcel(node);
    }
}

void nodeSendParcel(int node) {
    MPI_Send(&data_buffers[node], 1, mpi_parcel, node, PROGRESS_TAG, MPI_COMM_WORLD);
    data_buffers[node].size = 0;
}

bool nodeRecieve(int node, data_parcel *parcel) {
    MPI_Status status;
    MPI_Recv(parcel, 1, mpi_parcel, node, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    return status.MPI_TAG != END_TAG;
}