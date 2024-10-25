/*
Given a undirected connected graph G=(V,E) where V={1,…,N}. Each edge (u,v)∈E(u,v)∈E has weight w(u,v)w(u,v). Compute minimum spanning tree of G.
Input
Line 1: N and M (1≤N,M≤10
5
) in which NN is the number of nodes and MM is the number of edges.
Line i+1 (i=1,…,M): contains 3 positive integers u, v, and w where w is the weight of edge (u,v)
Output
Write the weight of the minimum spanning tree found.
Example
Input
5 8
1 2 1
1 3 4
1 5 1
2 4 2
2 5 1
3 4 3
3 5 3
4 5 2
Output
7
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
public:
    vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
        return false;
    }
};

int kruskalMST(int N, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    UnionFind uf(N);
    int mstWeight = 0, edgesUsed = 0;

    for (const auto& edge : edges) {
        if (uf.unite(edge.u - 1, edge.v - 1)) {
            mstWeight += edge.weight;
            edgesUsed++;
            if (edgesUsed == N - 1) break;
        }
    }

    return mstWeight;
}

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    int result = kruskalMST(N, edges);
    cout << result << endl;

    return 0;
}
