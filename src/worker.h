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

int rank, size;
void init_workforce(int argc, char *argv[]);
void teardown_workforce();
bool isLeader();
void worker_push(int worker, int value);
void end_work();


#endif	/* WORKER_H */

