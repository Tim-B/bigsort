/* 
 * File:   expand_array.h
 * Author: tim
 *
 * Created on 28 July 2013, 3:08 PM
 */

#ifndef EXPAND_ARRAY_H
#define	EXPAND_ARRAY_H

typedef struct {
    int* data;
    int largest_index;
    int assigned_size;
} expand_array;

void expand_array_init(expand_array *array);
void expand_array_put(expand_array* array, int value);
void expand_array_free(expand_array *array);

#endif	/* EXPAND_ARRAY_H */

