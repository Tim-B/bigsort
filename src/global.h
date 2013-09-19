/* 
 * File:   global.h
 * Author: tim
 *
 * Created on 19 September 2013, 11:14 AM
 */

#ifndef GLOBAL_H
#define	GLOBAL_H
#include <limits.h>
#include <stdbool.h>

#define PROGRESS_TAG 1
#define END_TAG 2

#define MIN(a,b) (((a)<(b))?(a):(b))

#define LOWER_LIM INT_MIN
#define UPPER_LIM INT_MAX


#include "helper.h"

#ifdef DEBUG
int *global_buffer, *global_input;
int loop;
#endif

int total_len;

#endif	/* GLOBAL_H */

