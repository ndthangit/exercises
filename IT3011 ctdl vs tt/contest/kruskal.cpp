/*
Problem: Minimum Spanning Tree - Kruskal
________________________________________
Description
Given a undirected connected graph G=(V,E) where V={1,…,N}. Each edge (u,v)∈E(u,v)∈E has weight w(u,v)w(u,v). Compute minimum spanning tree of G.
Input
•	Line 1: N and M (1≤N,M≤105) in which NN is the number of nodes and MM is the number of edges.
•	Line i+1 (i=1,…,M): contains 3 positive integers u, v, and w where w is the weight of edge (u,v)
Output
Write the weight of the minimum spanning tree found.
Example
Input
5 8 1 2 1 1 3 4 1 5 1 2 4 2 2 5 1 3 4 3 3 5 3 4 5 2
Output
7
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    int parentA = find_set(a);
    int parentB = find_set(b);
    if (parentA != parentB) {
        if (rank[parentA] < rank[parentB])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main() {
    int n;
    cin >> n;
    vector<Edge> edges;
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++)
        make_set(i);

    int cost = 0;
    vector<Edge> result;
    for (Edge e : edges) {
        if (find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            result.push_back(e);
            union_sets(e.u, e.v);
        }
    }

    cout << "Cost: " << cost << endl;
    for (Edge e : result) {
        cout << e.u << " " << e.v << endl;
    }

    return 0;
}

