# 城市路径规划中的Dijkstra算法

## Why Dijkstra?

为什么不使用其他的算法呢？

其他的Floyd, Bellman或者A*也都十分好用啊

原因如下:

1. 非常~~灵动~~有扩展性
2. 复杂度较低
3. 极其稳定

## Many Parts

本程序分为以下部分：

1. 主程序 (提供数据)
2. class shortest_path类定义
3. init初始化函数实现
4. dijkstra最短路径函数实现
5. print输出函数实现

## Part 1 主程序

这里使用了邻接矩阵进行存储城市路径的有向图

```cpp
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../include/shortest_path.h"

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ifstream;
    using std::string;
    using std::vector;

    const unsigned int INF = 99999999;
    const unsigned int LIGHT_TIME = 1;
    unsigned int dot, side; ///< 点数和边数
    unsigned int start, end; ///< 起点和终点
    string input_file;
    ifstream map;

    cin >> input_file;
    cin >> start >> end;

    if (input_file == "car") {
        map = ifstream("../input/map_car.txt");
    }

    if (input_file == "slow_car") {
        map = ifstream("../input/map_slow_car.txt");
    }

    if (input_file == "people") {
        map = ifstream("../input/map_people.txt");
    }

    map >> dot >> side;

    vector<vector<unsigned int>> gragh(dot + 1, vector<unsigned int>(dot + 1, 0)); ///< 邻接矩阵
    vector<unsigned int> time(dot + 1, INF); ///< 最短时间数组
    vector<unsigned int> pre(dot + 1, 0); ///< 前驱节点数组
    vector<bool> book(dot + 1, false); ///< 标记数组

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
    obj.print(start, end); ///< 打印路径
    cout << endl << time[end] << endl;

    system("pause");
    
    return 0;
}
```

## Part 2 shortest_path类定义

```cpp
#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;
using std::min;
using std::vector;

class shortest_path {
private:
    vector<vector<unsigned int>> &graph;
    vector<unsigned int> &time;
    vector<unsigned int> &pre;
    vector<bool> &book;

public:
    shortest_path(vector<vector<unsigned int>> &_gragh, vector<unsigned int> &_pre, vector<unsigned int> &_time, vector<bool> &_book) : graph(_gragh), pre(_pre), time(_time), book(_book) {}

    /**
     * @brief 初始化
     * @param dot 点数
     * @param start 起点
     */
    void init(unsigned int dot, unsigned int start);

    /**
     * @brief Dijkstra求最短时间
     * @param INF 无穷大
     * @param LIGHT_TIME 红绿灯时间
     * @param dot 点数
     */
    void dijkstra(const unsigned int INF, const unsigned int LIGHT_TIME, unsigned int dot);

    /**
     * @brief 打印路径
     * @param start 起点
     * @param to 通向的点
     */
    void print(unsigned int start, unsigned int to);
};

#endif
```

## Part 3 init函数实现

```cpp
#include "../include/shortest_path.h"

void shortest_path::init(unsigned int dot, unsigned int start) {
    time[start] = 0; ///< 起点到起点的时间为0

    for (unsigned int i = 1; i <= dot; i += 1) {
        pre[i] = i; ///< 将每个节点的前驱设为自身
    }

    return;
}
```

## Part 4 dijkstra函数实现

很重要的一点, 我们使用了前驱数组进行记录来输出 (参照下文)

```cpp
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
```

## Part 5 print函数实现

值得一提的是, 这里使用了上文提到的前驱数组, 使用递归进行了输出 (参照上文)

```cpp
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
```

## 使用指南

```bash
make run
```

接下来一行：四种类型 (car, slow_car, bike, people)

再来一行：起点和终点

如上, 在命令行输入以上命令即可 (tips: 需要make, 如果没有, 请参照下文)

```bash
g++ .\src\main.cpp .\lib\init.cpp .\lib\dijkstra.cpp .\lib\print.cpp -o .\build\main.exe
.\build\main.exe
```

没有的话就输入如上数据就可以了 (没有g++就没办法了)

## 贡献名单

### 开发者

1. xhdlphzr
2. computer-6-2024

### 审核

1. xhdlphzr