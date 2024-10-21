#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using std::cout;
using std::endl;
using std::min;
using std::vector;
using std::stack;

class shortest_path {
private:
    vector<vector<unsigned int>> &graph;
    vector<unsigned int> &pre;
    vector<unsigned int> &time;
    vector<bool> &book;
    stack<unsigned int> path;

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