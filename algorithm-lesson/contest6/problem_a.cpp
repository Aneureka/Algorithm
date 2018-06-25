/**
 * 【题目描述】
 *     现实版：
 *     计算机系的小雷同学是个背包客，他打算暑假有时间去环游中国。
 *     他的想法得到了家里的支持，爸爸决定赞助他一张机票送他前往他的第一个目的地。
 *     小雷并不是一个贪小便宜的人，所以他自然不会买最贵的机票前往乌鲁木齐（躺枪）。
 *     他也不是一个计划狂，随性的他希望游完第一个城市之后再决定下一步去哪里，而他又希望有一个美好的开始，不至于像去了三亚的天涯海角之后无路可走，所以他打算将他的第一个目的地定为有航线能通往最多城市的国内机场所在地。
 *     小雷的叔叔告诉他，如果这样的话那么他只能选择飞往北京了。但是小雷并不相信这个结论，于是他搜集了国内各个城市之间的航线图，自己尝试用专业知识对这个问题进行建模。
 *     他把每一个城市定义为图内的一个顶点，城市之间的航线采用有向边来表示。例如，城市A有飞往城市B的航班，那么在图中就存在一条从A指向B的有向边。
 *     建模完成之后问题来了，如何利用小雷的模型，计算出哪一个城市是他的第一个最佳旅行目的地呢？
 *
 *     抽象版：
 *     给定一个有向图G，一个点 v 的影响力定义为图G中可以从 v 可达的顶点的个数（不包括自身）。
 *     问题：找出图G中影响力最大的顶点。
 *
 *     注：结果不一定唯一。
 *
 * 【输入】
 *     图G，以邻接表的形式。
 *     点的标号从0到n-1，总共n个点，于是有n行输入。
 *     第 i 行的输入为与编号 i-1 这个点相邻的点们的标号，以空格隔开，行尾无空格。如样例输入中第2行为“2 3”，表示点1到点2有一条边，点1到点3有一条边。
 *
 *     注：本次输入处理比之前难度更大一些，不会告诉你总共有多少个点，每一行也不会告诉你该点有多少个邻居，请发挥你的聪明才智，运用种种编程技巧处理这样的输入。
 *
 * 【输出】
 *     第一行：图G中影响力最大的点的影响力。
 *
 *     第二行：图G中影响力最大的点的标号。如果结果不唯一，依照标号从小到大输出，中间以空格隔开。
 *
 *     请注意：在最后一个标号之后也请加上空格！
 *
 * 【样例输入】
 *     1
 *     2 3
 *     0
 *     4
 *     5
 *     3
 *
 * 【样例输出】
 *     5
 *     0 1 2
 *
 * 【提示】
 *     关于不定长度输入的处理，可以参考之前作业的IO说明。
 *     一个点的影响力，不包括自身。
 *
 */

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include <set>
#include <algorithm>
using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

void draw_white(vector<int>& color, int n) {
    bool empty = color.empty();
    for (int i = 0; i < n; ++i) {
        if (empty)
            color.push_back(WHITE);
        else
            color[i] = WHITE;
    }
}

void dfs(const vector<vector<int> >& graph, vector<int>& color, stack<int>& s, int v) {
    color[v] = GRAY;
    vector<int> v_neighbor = graph[v];
    for (int i = 0; i < v_neighbor.size(); ++i) {
        int w = v_neighbor[i];
        if (color[w] == WHITE) {
            dfs(graph, color, s, w);
        }
    }
    s.push(v);
    color[v] = BLACK;
}

void dfs_t(const vector<vector<int> >& graph, vector<int>& color, vector<int>& at_scc, vector<vector<int> >& graph_scc, vector<int>& scc_size, int v, int scc) {
    color[v] = GRAY;
    if (scc < 0) {
        // add "-1" to initialize
        vector<int> t; t.push_back(-1);
        graph_scc.push_back(t);
        scc_size.push_back(1);
        at_scc[v] = scc_size.size() - 1;
    } else {
        scc_size[scc_size.size()-1] += 1;
        at_scc[v] = scc;
    }

    vector<int> v_neighbor = graph[v];
    for (int i = 0; i < v_neighbor.size(); ++i) {
        int w = v_neighbor[i];
        if (color[w] == WHITE) {
            dfs_t(graph, color, at_scc, graph_scc, scc_size, w, at_scc[v]);
        }
        else if (color[w] == BLACK) {
            graph_scc[at_scc[w]].push_back(at_scc[v]);
        }
    }
    color[v] = BLACK;
}

void dfs_scc(const vector<vector<int> >& graph, const vector<int>& scc_size, vector<int>& color, vector<int>& impact, int v, int cur_scc) {
    color[v] = GRAY;
    impact[cur_scc] += scc_size[v];
    vector<int> v_neighbor = graph[v];
    for (int i = 0; i < v_neighbor.size(); ++i) {
        int w = v_neighbor[i];
        if (color[w] == WHITE) {
            dfs_scc(graph, scc_size, color, impact, w, cur_scc);
        }
    }
    color[v] = BLACK;
}

void dfs_wrapper(const vector<vector<int> >& graph, vector<int>& color, stack<int>& s) {
    int n = graph.size();
    draw_white(color, n);
    for (int i = 0; i < n; ++i) {
        if (color[i] == WHITE) {
            dfs(graph, color, s, i);
        }
    }
}

void dfs_t_wrapper(const vector<vector<int> >& graph, vector<int>& color, vector<int>& at_scc, vector<vector<int> >& graph_scc, vector<int>& scc_size, stack<int>& s) {
    int n = graph.size();
    draw_white(color, n);
    for (int i = 0; i < n; ++i) {
        at_scc.push_back(-1);
    }
    while (!s.empty()) {
        int i = s.top();
        s.pop();
        if (color[i] == WHITE) {
            dfs_t(graph, color, at_scc, graph_scc, scc_size, i, -1);
        }
    }
    // delete "-1" at the begin of the neighbor
    for (int i = 0; i < graph_scc.size(); ++i) {
        graph_scc[i].erase(graph_scc[i].begin());
    }
}

void dfs_scc_wrapper(const vector<vector<int> >& graph, const vector<int>& scc_size, vector<int>& color, vector<int>& impact) {
    int n = graph.size();
    for (int i = 0; i < n; ++i) {
        draw_white(color, n);
        dfs_scc(graph, scc_size, color, impact, i, i);
    }
}

void print_n(const vector<vector<int> >& graph) {
    for (int i = 0; i < graph.size(); ++i) {
        vector<int> t_n = graph[i];
        for (int j = 0; j < t_n.size(); ++j) {
            cout << t_n[j] << " ";
        }
        cout << endl;
    }
}

void print_stack(const stack<int>& s) {
    stack<int> temp = s;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }

    cout << endl;
}

int main() {

    vector<vector<int> > graph;

    string line;
    int t_neighbor;
    while (getline(cin, line)) {
        stringstream ss;
        ss << line;
        vector<int> t;
        while (ss >> t_neighbor) {
            t.push_back(t_neighbor);
        }
        graph.push_back(t);
    }

    // perform dfs at graph and store vertex in stack
    vector<int> color;
    stack<int> s;
    dfs_wrapper(graph, color, s);

    // transpose graph gT
    int n = graph.size();
    vector<vector<int> > graph_t(n);
    for (int i = 0; i < n; ++i) {
        vector<int> t = graph[i];
        for (int j = 0; j < t.size(); ++j) {
            graph_t[t[j]].push_back(i);
        }
    }

    // perform dfs at transposed graph and get transposed scc graph
    vector<int> color_t;
    vector<int> at_scc;
    vector<vector<int> > graph_scc;
    vector<int> scc_size;
    dfs_t_wrapper(graph_t, color_t, at_scc, graph_scc, scc_size, s);

    // now we have [scc graph], [vertex-scc assignment], [scc sizes]
    // so we can calculate impact of each scc, use dfs to achieve it
    int n_scc = graph_scc.size();
    vector<int> impact(n_scc);
    vector<int> color_scc;
    dfs_scc_wrapper(graph_scc, scc_size, color, impact);

    // get the max impact [inclusive]
    int max_impact = -1;
    set<int> max_scc_set;
    for (int i = 0; i < n_scc; ++i) {
        if (impact[i] > max_impact) {
            max_impact = impact[i];
            max_scc_set.clear();
            max_scc_set.insert(i);
        }
        else if (impact[i] == max_impact) {
            max_scc_set.insert(i);
        }
    }
    max_impact = max_impact > 0 ? max_impact-1 : 0;


    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << max_impact << endl;
    for (int i = 0; i < n; ++i) {
        if (max_scc_set.find(at_scc[i]) != max_scc_set.end()) {
            cout << i << " ";
        }
    }
    cout << endl;
}
