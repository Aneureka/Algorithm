/**
 * 【题目描述】
 *     给出n个节点编号为0,1,2,...,n-1组成的无向图，已知它是二部图。找出编号为0所在的一部按顺序打印。
 *     二部图不存在多个联通片，所以结果唯一。
 *
 * 【输入】
 *     n行，每行第一个字段表示该节点，后面的字段表示该节点的邻居。每一行最后有一个空格。
 *
 * 【输出】
 *     编号为0所在的一部按顺序打印。
 *
 * 【样例输入】
 *     0 2 3 4
 *     1 2
 *     2 1 0
 *     3 0
 *     4 0
 *
 * 【样例输出】
 *     0
 *     1
 *
 */


#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
using namespace std;

#define WHITE (-1)
#define RED 0
#define BLUE 1

int main() {

    vector<vector<int> > neighbor;

    string line;
    int t_vertex, t_neighbor;
    while (getline(cin, line)) {
        stringstream ss;
        ss << line;
        ss >> t_vertex;
        vector<int> t;
        while (ss >> t_neighbor) {
            t.push_back(t_neighbor);
        }
        neighbor.push_back(t);
    }


    long n = neighbor.size();
    vector<int> color;
    for (long i = 0; i < n; ++i) {
        color.push_back(WHITE);
    }

    queue<int> q_vertex;
    q_vertex.push(0);
    color[0] = RED;
    while (!q_vertex.empty()) {
        int v = q_vertex.front();
        q_vertex.pop();
        vector<int> v_neighbor = neighbor[v];
        for (long i = 0; i < v_neighbor.size(); ++i) {
            int w = v_neighbor[i];
            if (color[w] == WHITE) {
                color[w] = 1 - color[v];
                q_vertex.push(w);
            }
            else if (color[w] == color[v]) {
                return -1;
            }
        }
    }


    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    for (int i = 0; i < n; ++i) {
        if (color[i] == RED)
            cout << i << endl;
    }

}