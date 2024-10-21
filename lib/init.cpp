#include "../include/shortest_path.h"

void shortest_path::init(unsigned int dot, unsigned int start) {
    time[start] = 0;

    for (unsigned int i = 1; i <= dot; i += 1) {
        pre[i] = i;
    }

    return;
}