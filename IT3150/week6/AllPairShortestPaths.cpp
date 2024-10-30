/*Given a directed graph G = (V, E) in which V = {1, 2, ..., n} is the set of nodes, and w(u,v) is the weight (length) of the arc(u,v). Compute d(u,v) - the length of the shortest path from u to v in G, for all u,v in V.
Input
Line 1: contains 2 positive integers n and m (1 <= n,m <= 10000)
Line i+1 (i = 1, 2, ..., m): contains 3 positive integers u, v, w in which w is the weight of the arc (u,v) (1 <= w <= 1000)
Output
Line i (i = 1, 2, ..., n): wirte the ith row of the matrix d (if there is not any path from node i to node j, then d(i,j) = -1)
Example
Input
4 9
1 2 9
1 3 7
1 4 2
2 1 1
2 4 5
3 4 6
3 2 2
4 1 5
4 2 8
Output
0 9 7 2
1 0 8 3
3 2 0 5
5 8 12 0*/
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const long long infinite = 1e15, limit = 1e5 + 5;

vector<pair<long long, long long>> graph[limit];
long long dist[limit];

long long minDis(long long beginNode, long long endNode) {
    for (long long i = 1; i < limit; i++) {
        dist[i] = infinite;
    }

    set<pair<long long, long long>> st;
    dist[beginNode] = 0;
    st.insert(make_pair(0, beginNode));

    while (!st.empty()) {
        long long vertex = st.begin()->second;
        st.erase(st.begin());

        if (vertex == endNode) {
            return dist[endNode];
        }

        for (auto &edge : graph[vertex]) {
            long long next = edge.first, dis = edge.second;
            if (dist[next] > dist[vertex] + dis) {
                st.erase(make_pair(dist[next], next));
                dist[next] = dist[vertex] + dis;
                st.insert(make_pair(dist[next], next));
            }
        }
    }

    return (dist[endNode] == infinite ? -1 : dist[endNode]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long quantityOfVertex, quantityOfEdges;
    cin >> quantityOfVertex >> quantityOfEdges;

    for (long long i = 0; i < quantityOfEdges; i++) {
        long long firstVertex, secondVertex, distance;
        cin >> firstVertex >> secondVertex >> distance;
        graph[firstVertex].push_back(make_pair(secondVertex, distance));
    }

    for (long long i = 1; i <= quantityOfVertex; i++) {
        for (long long j = 1; j <= quantityOfVertex; j++) {
            cout << minDis(i, j) << " ";
        }
        cout << endl;
    }

    return 0;
}

