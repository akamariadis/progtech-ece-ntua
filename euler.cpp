#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
    int M, N, a, b, odd = 0;
    map<int, vector<int>> graph;
    set<int> Set;
    set<int> oddSet;
    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        Set.insert(a);
        Set.insert(b);
    }
    for (auto it: Set) {
        if ((graph[it].size()%2) != 0) {
            odd++;
            oddSet.insert(it);
        }
    }
    if (odd == 0) {
        cout << "CYCLE" << endl;
    }
    else if (odd == 2) {
        cout << "PATH";
        for (auto it: oddSet) {
            cout << " " << it;
        }
        cout << endl;
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}