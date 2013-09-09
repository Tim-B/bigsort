#include "expand_array.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Initializes an expandable array. Sets the initial size as 100.
 * 
 * @param array a pointer to an expand array struct.
 */
void expand_array_init(expand_array *array) {
    array->data = malloc(sizeof(int) * 100);
    array->assigned_size = 100;
    array->largest_index = 0;
}

/**
 * Puts an element into the end of an expandable array.
 * 
 * If the array is too small the size is doubled automatically.
 * 
 * @param array the expand_array instance to use.
 * @param value the value to be inserted into the array.
 */
void expand_array_put(expand_array* array, int value) {
    if(array->largest_index >= array->assigned_size) {
        array->assigned_size = array->assigned_size * 2;
        array->data = realloc(array->data, sizeof(int) * array->assigned_size);
    }
    array->data[array->largest_index] = value;
    array->largest_index++;
}

/**
 * Frees an expandable array instance
 * 
 * @param array the array to free
 */
void expand_array_free(expand_array *array) {
    free(array->data);
}
