#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include "../include/shortest_path.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ifstream;
    using std::vector;

    ifstream map("../input/map.txt");
    ifstream pth("../input/pth.txt");

    const unsigned int INF = 99999999;
    const unsigned int LIGHT_TIME = 1;
    unsigned int dot, side; ///< 点数和边数
    unsigned int start, end; ///< 起点和终点

    map >> dot >> side;
    pth >> start >> end;

    vector<vector<unsigned int>> gragh(dot + 1, vector<unsigned int>(dot + 1, 0)); ///< 邻接矩阵兼动态规划矩阵
    vector<unsigned int> pre(dot + 1, 0);
    vector<unsigned int> time(dot + 1, INF);
    vector<bool> book(dot + 1, false);

    /// 初始化
    for (unsigned int i = 1; i <= dot; i += 1) {
        for (unsigned int j = 1; j <= dot; j += 1) {
            if (i != j) {
                gragh[i][j] = INF;
            }
        }
    }

    /// 有向图设置
    for (unsigned int i = 1; i <= side; i += 1) {
        unsigned int from, to, time; ///< 边的起点、终点和所需时间
        map >> from >> to >> time;

        gragh[from][to] = time; ///< 有向图设置
    }

    shortest_path obj(gragh, pre, time, book); ///< 创造实例
    obj.init(dot, start); ///< 初始化time数组
    obj.dijkstra(INF, LIGHT_TIME, dot); ///< 最短路径算法
    obj.print(start, end); ///< 打印路径和时间
    cout << endl << time[end] << endl;

    system("pause");
    
    return 0;
}