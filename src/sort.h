/* 
 * File:   sort.h
 * Author: tim
 *
 * Created on 19 September 2013, 11:03 AM
 */

#ifndef SORT_H
#define	SORT_H

#include "global.h"

void sort(int *buffer, int* list, int len);
void merge(int *list, int start, int middle, int end, int *buffer);

#endif	/* SORT_H */

