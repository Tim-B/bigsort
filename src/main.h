/* 
 * File:   main.h
 * Author: tim
 *
 * Created on 27 July 2013, 10:24 AM
 */

#ifndef MAIN_H
#define	MAIN_H
#include <stdio.h>
#include "global.h"
#include "worker.h"
#include "sort.h"
#include "expand_array.h"
#include "distribute.h"

FILE *input_file, *output_file;
void print_list(int *input, int len);
void write_file(FILE *fp, int* input, int len);

#endif	/* MAIN_H */

