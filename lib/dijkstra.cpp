#include "../include/shortest_path.h"

void shortest_path::dijkstra(const unsigned int INF, const unsigned int LIGHT_TIME, unsigned int dot) {
    for (unsigned int i = 1; i < dot; i += 1) {
        unsigned int min = 99999999;
        unsigned int from = -1;

        /// 寻找蓝点 (已知最短路径)
        for (unsigned int j = 1; j <= dot; j += 1) {
            if (book[j] == false && time[j] < min) {
                min = time[j];
                from = j;
            } 
        }

        if (from == -1) {
            return;
        }

        book[from] = true;

        /// 更新时间和前驱节点
        for (unsigned int to = 1; to <= dot; to += 1) {
            if (book[to] == false && graph[from][to] < INF && time[from] + graph[from][to] + LIGHT_TIME < time[to]) {
                time[to] = time[from] + graph[from][to] + LIGHT_TIME;
                pre[to] = from;
            }
        }
    }

    return;
}