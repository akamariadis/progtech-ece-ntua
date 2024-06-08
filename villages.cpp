#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

struct node {
    int parent;
    int rank;
};

int search(vector<node>& nodes, int i) {
    if (nodes[i].parent != i)
        nodes[i].parent = search(nodes, nodes[i].parent);
    return nodes[i].parent;
}

void union(vector<node>& nodes, int x, int y) {
    int xRoot = search(nodes, x);
    int yRoot = search(nodes, y);

    if(nodes[xRoot].rank < nodes[yRoot].rank)
        nodes[xRoot].parent = yRoot;
    else if(nodes[xRoot].rank > nodes[yRoot].rank)
        nodes[yRoot].parent = xRoot;
    else {
        nodes[yRoot].parent = xRoot;
        nodes[xRoot].rank++;
    }
}

int main () {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    int cnt = N;
    vector<node> nodes(N + 1);
    for (int i = 1; i <= N; i++) {
        nodes[i].parent = i;
        nodes[i].rank = 0;
    }
    for (int i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        union(nodes, A, B);
    }
    for (int i = 1; i <= N; i++)
        if (nodes[i].parent != i) cnt--;
    int min = cnt - K;
    if (min < 1) cout << "1" << endl;
    else cout << min << endl;
    return 0;
}  
