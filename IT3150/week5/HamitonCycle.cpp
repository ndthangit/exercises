/*
Given an undirected graph G = (V,E). Write a program to check if G is a Hamiltonian graph.
Input
Line 1: a positive integer T (number of graphs)
Subsequent lines are information about T graphs, each has the following format:
Line 1: n and m (number of nodes and edges)
Line i+1 (i = 1, 2, ..., m): u and v : two end points of the ith edge
Output
In the ith line, write 1 if the corresponding is a Hamiltonian graph, and write 0, otherwise
Example
Input
2
5 5
1 2
1 3
2 4
2 5
3 5
7 13
1 3
1 5
1 7
2 4
2 5
2 6
3 4
3 5
3 7
4 6
4 7
5 7
6 7

Output
0
1
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Backtracking function to check for Hamiltonian cycle
bool isHamiltonianCycle(const vector<vector<int>>& graph, vector<int>& path, int pos) {
    int n = graph.size();
    // Base case: If all vertices are included in the path, check if there is an edge back to the start
    if (pos == n) {
        return find(graph[path[pos - 1]].begin(), graph[path[pos - 1]].end(), path[0]) != graph[path[pos - 1]].end();
    }

    // Try different vertices as the next candidate in the Hamiltonian cycle
    for (int vertex = 1; vertex < n; vertex++) {
        // Check if vertex is not already in the path and is adjacent to the last vertex in the path
        if (find(path.begin(), path.begin() + pos, vertex) == path.begin() + pos &&
            find(graph[path[pos - 1]].begin(), graph[path[pos - 1]].end(), vertex) != graph[path[pos - 1]].end()) {
            path[pos] = vertex;
            if (isHamiltonianCycle(graph, path, pos + 1)) {
                return true;
            }
            // Backtrack
            path[pos] = -1;
        }
    }
    return false;
}

// Function to check if the graph has a Hamiltonian cycle
bool hasHamiltonianCycle(int n, const vector<pair<int, int>>& edges) {
    // Build adjacency list
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge.first - 1].push_back(edge.second - 1);
        graph[edge.second - 1].push_back(edge.first - 1);
    }

    // Initialize path with starting vertex
    vector<int> path(n, -1);
    path[0] = 0; // Start from vertex 0

    // Use backtracking to check for Hamiltonian cycle
    return isHamiltonianCycle(graph, path, 1);
}

int main() {
    int T;
    cin >> T;
    vector<int> results;

    for (int t = 0; t < T; t++) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            edges[i] = {u, v};
        }

        // Check if the graph is Hamiltonian and store the result
        results.push_back(hasHamiltonianCycle(n, edges) ? 1 : 0);
    }

    // Output results
    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isHamiltonianCycle(const vector<vector<int>>& graph, vector<int>& path, int pos) {
    int n = graph.size();
    if (pos == n) {
        return find(graph[path[pos - 1]].begin(), graph[path[pos - 1]].end(), path[0]) != graph[path[pos - 1]].end();
    }

    for (int vertex = 1; vertex < n; vertex++) {
        if (find(path.begin(), path.begin() + pos, vertex) == path.begin() + pos &&
            find(graph[path[pos - 1]].begin(), graph[path[pos - 1]].end(), vertex) != graph[path[pos - 1]].end()) {
            path[pos] = vertex;
            if (isHamiltonianCycle(graph, path, pos + 1)) {
                return true;
            }
            path[pos] = -1;
        }
    }
    return false;
}

bool hasHamiltonianCycle(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> graph(n);
    for (const auto& edge : edges) {
        graph[edge.first - 1].push_back(edge.second - 1);
        graph[edge.second - 1].push_back(edge.first - 1);
    }

    vector<int> path(n, -1);
    path[0] = 0; 

    return isHamiltonianCycle(graph, path, 1);
}

int main() {
    int T;
    cin >> T;
    vector<int> results;

    for (int t = 0; t < T; t++) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m);

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            edges[i] = {u, v};
        }

        results.push_back(hasHamiltonianCycle(n, edges) ? 1 : 0);
    }

    for (int result : results) {
        cout << result << endl;
    }

    return 0;
}

