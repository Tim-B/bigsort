/* 
 * File:   worker.h
 * Author: tim
 *
 * Created on 19 September 2013, 11:46 AM
 */

#ifndef WORKER_H
#define	WORKER_H
#include <mpi.h>
#include "global.h"
#include "distribute.h"

#define PARCEL_SIZE 100

typedef struct {
    int data[PARCEL_SIZE];
    int size;
} data_parcel;

int rank, size;
void init_workforce(int argc, char *argv[]);
void teardown_workforce();
bool isLeader();
void worker_push(int worker, int value);
void end_work();
int getWorkforceSize();
void nodePush(int node, int value);
void nodeSendParcel(int node);
bool nodeRecieve(int node, data_parcel *parcel);
int getMyRank();
void finish_node(int node);

MPI_Datatype mpi_parcel;
data_parcel mpiBuffer;
data_parcel *data_buffers;

#endif	/* WORKER_H */

