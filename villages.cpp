#include <iostream>
#include <vector>

using namespace std;

struct node {
    int parent;
    int rank;
};

int Find(vector<node>& nodes, int i) {
    if (nodes[i].parent != i)
        nodes[i].parent = Find(nodes, nodes[i].parent);
    return nodes[i].parent;
}

void Union(vector<node>& nodes, int x, int y) {
    int xRoot = Find(nodes, x);
    int yRoot = Find(nodes, y);

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
    int ind = N;
    vector<node> nodes(N + 1);
    for (int i = 1; i <= N; i++) {
        nodes[i].parent = i;
        nodes[i].rank = 0;
    }
    for (int i = 0; i < M; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        Union(nodes, A, B);
    }
    for (int i = 1; i <= N; i++) {
        if (nodes[i].parent != i)
            ind--;
    }
    int min = ind - K;
    if (min < 1) {
        printf("%d\n", 1);
    }
    else {
        printf("%d\n", min);
    }
    return 0;

}  