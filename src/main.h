/* 
 * File:   main.h
 * Author: tim
 *
 * Created on 27 July 2013, 10:24 AM
 */

#ifndef MAIN_H
#define	MAIN_H
#include <stdio.h>
#include "expand_array.h"

FILE *input_file, *output_file;
void sort(int *buffer, int* list, int len);
void merge(int *left, int left_len, int* right, int right_len, int *buffer);
void print_list(int *input, int len);
void write_file(FILE *fp, int* input, int len);

#endif	/* MAIN_H */

