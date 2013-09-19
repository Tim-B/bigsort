#include "global.h"
#include "distribute.h"

int interval; 
int nodes;

void init_distribute(int num_nodes) {
    nodes = num_nodes;
    interval = (UPPER_LIM / num_nodes) * 2;
}

int getnode_val(int val) {
    int node = 0;
    for(int i = 0; i < UPPER_LIM; i += interval) {
        if(val < i) {
            return node;
        }
        node++;
        if(node == nodes) {
            return nodes - 1;
        }
    }
    return nodes - 1; 
}