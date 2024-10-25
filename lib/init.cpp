#include "../include/shortest_path.h"

void shortest_path::init(unsigned int dot, unsigned int start) {
    time[start] = 0; ///< 起点到起点的时间为0

    for (unsigned int i = 1; i <= dot; i += 1) {
        pre[i] = i; ///< 将每个节点的前驱设为自身
    }

    return;
}