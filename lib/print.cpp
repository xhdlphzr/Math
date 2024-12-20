#include "../include/shortest_path.h"

void shortest_path::print(unsigned int start, unsigned int to) {
    /// 到达起点, 输出并返回
    if (start == to) {
        cout << start << " ";
        return;
    } else {
        print(start, pre[to]);
        cout << to << " ";
    }

    return;
}