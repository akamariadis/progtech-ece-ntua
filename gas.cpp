#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int n) {
        vertices = n;
    }
    int size() {
        return vertices;
    }
    void addEdge(int u, int v, int l) {
        adj[u].push_back(make_pair(v, l));
        adj[v].push_back(make_pair(u, l));
    }

    bool find_route(int u, vector<bool> &status, vector<int> &bc, int b, int c, vector<int> &g) {
        if (u == b) {
            bc.push_back(u);
            return true;
        }
        status[u] = true;
        for (auto v: adj[u]) {
            if (!status[v.first]) {
                if (v.second <= c) {
                    if (find_route(v.first, status, bc, b, c, g)) {
                        bc.push_back(u);
                        g.push_back(v.second);
                        return true;
                    }
                }
            }
        }
        return false;
    }
private:
    map<int, vector<pair<int, int>>> adj;
    int vertices;
};

int main () {
    int N, M, U, V, L, Q, A, B, C;
    cin >> N >> M;
    Graph g(N);
    for (int i = 0; i < M; ++i) {
        cin >> U >> V >> L;
        g.addEdge(U, V, L);
    }
    cin >> Q;
    for (int k = 0; k < Q; ++k) {
        cin >> A >> B >> C;
        vector<bool> status(g.size(), false);
        vector<int> b; vector<int> gas;
        int fills = 1;
        g.find_route(A, status, b, B, C, gas);
        bool flag = false;
        if (b.size() > 0) {
            flag = true;
        }
        int currentGas = C;
        gas.push_back(0);
        for (int i = gas.size() - 1; i >= 0; --i) {
            currentGas = currentGas - gas[i];
            if ((currentGas == 0 || (currentGas - gas[i - 1]) < 0) && i != 0) {
                currentGas = C;
                fills++;
            }
        }
        if (!flag) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << "POSSIBLE: " << fills << " fill(s),";
            for (int i = b.size() - 1; i >= 0; --i) {
                cout << " " << b[i];
            }
            cout << endl;
        }
    }
    return 0;
}