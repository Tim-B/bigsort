/* 
 * File:   helper.h
 * Author: tim
 *
 * Created on 19 September 2013, 11:04 AM
 */

#ifndef HELPER_H
#define	HELPER_H

#include <stdio.h>

int min(int a, int b);

void print_list(int *input, int len);

void write_file(FILE *fp, int* input, int len);

void gather_work(FILE *fp);

#endif	/* HELPER_H */

