#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

enum state {UNVISITED, VISITED, EXPLORED};

class Graph {
public:
    Graph(int V) {
        vertices = V;
    }
    ~Graph() {
        gr.clear();
    }
    void addEdge(int u, int v) {
        gr[u].insert(v);
    }

    bool cycle(vector<int> &path) {
        vector<state> status(vertices);
        int Pos = -1, Parent = -1;
        bool flag = false;
        vector <int> p(vertices);
        for (int i = 0; i < vertices; ++i) {
            p[i] = -1;
            status[i] = UNVISITED;
        }
        for (int i = 0; i < vertices; ++i) {
            if (status[i] == UNVISITED) {
                dfs_help(i, p, status, Pos, Parent);
            }
            if (Pos != -1) {
                flag = true;
                break;
            }
        }
        if (flag) {
            path.push_back(Pos);
            while (Parent != path[0]) {
                path.push_back(Parent);
                Parent = p[Parent];
            }
            reverse(path.begin(), path.end());
            return true;
        }
        else return false;
    }
private:
    map<int, set<int>> gr;
    int vertices;
    void dfs_help (int i, vector<int> &p, vector<state> &status, int &pos, int &parent) {
        status[i] = VISITED;
        for (auto it: gr[i]) {
            if (pos > -1) break;
            if (status[it] == UNVISITED) {
                p[it] = i;
                dfs_help(it, p, status, pos, parent);
            }
            else if (status[it] == VISITED) {
                pos = it;
                parent = i;
                break;
            }
        }
        status[i] = EXPLORED;
    }
};