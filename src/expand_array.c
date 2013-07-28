#include "expand_array.h"
#include <stdio.h>
#include <stdlib.h>

void expand_array_init(expand_array *array) {
    array->data = malloc(sizeof(int) * 100);
    array->assigned_size = 100;
    array->largest_index = 0;
}

void expand_array_put(expand_array* array, int value) {
    array->largest_index++;
    if(array->largest_index >= array->assigned_size) {
        array->assigned_size = array->assigned_size * 2;
        array->data = realloc(array->data, sizeof(int) * array->assigned_size);
    }
    array->data[array->largest_index] = value;
}

void expand_array_free(expand_array *array) {
    free(array->data);
}
